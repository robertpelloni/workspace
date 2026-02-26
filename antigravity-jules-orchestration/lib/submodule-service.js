
import fs from 'fs/promises';
import path from 'path';
import { exec, spawn } from 'child_process';
import util from 'util';

const execAsync = util.promisify(exec);

export class SubmoduleService {
    constructor(workspaceRoot) {
        this.workspaceRoot = workspaceRoot;
        this.submodulesDir = path.join(workspaceRoot, 'borg', 'submodules');
        this.runningProcesses = new Map();
    }

    async listSubmodules() {
        try {
            const entries = await fs.readdir(this.submodulesDir, { withFileTypes: true });
            const submodules = [];

            for (const entry of entries) {
                if (entry.isDirectory()) {
                    const submodulePath = path.join(this.submodulesDir, entry.name);
                    const info = await this.getSubmoduleInfo(submodulePath);
                    submodules.push({
                        name: entry.name,
                        path: submodulePath,
                        ...info
                    });
                }
            }
            return submodules;
        } catch (error) {
            console.error('Error listing submodules:', error);
            return [];
        }
    }

    async getSubmoduleInfo(submodulePath) {
        const info = {
            type: 'unknown',
            configFiles: [],
            scripts: {},
            gitStatus: null
        };

        try {
            const files = await fs.readdir(submodulePath);

            // Detect type and config
            if (files.includes('package.json')) {
                info.type = 'node';
                info.configFiles.push('package.json');
                const pkg = JSON.parse(await fs.readFile(path.join(submodulePath, 'package.json'), 'utf-8'));
                info.scripts = pkg.scripts || {};
            } else if (files.includes('Cargo.toml')) {
                info.type = 'rust';
                info.configFiles.push('Cargo.toml');
                // Rust scripts are less standard, maybe look for Makefile or just cargo run
                info.scripts = { build: 'cargo build', test: 'cargo test' };
            } else if (files.includes('pyproject.toml') || files.includes('requirements.txt')) {
                info.type = 'python';
                if (files.includes('pyproject.toml')) info.configFiles.push('pyproject.toml');
            }

            // Check for common config files
            for (const file of files) {
                if (file.endsWith('.yaml') || file.endsWith('.yml') || file.endsWith('.json') || file === '.env' || file.endsWith('.toml') || file.toLowerCase() === 'readme.md' || file.toLowerCase() === 'architecture.md') {
                    if (!info.configFiles.includes(file)) {
                        info.configFiles.push(file);
                    }
                }
            }

            // Get Git Status
            if (files.includes('.git')) {
                info.gitStatus = await this.getGitStatus(submodulePath);
            }

        } catch (error) {
            console.error(`Error getting info for ${submodulePath}:`, error);
        }
        return info;
    }

    async getGitStatus(cwd) {
        try {
            const branch = (await execAsync('git symbolic-ref --short HEAD', { cwd })).stdout.trim();
            const commit = (await execAsync('git rev-parse --short HEAD', { cwd })).stdout.trim();
            const status = (await execAsync('git status --porcelain', { cwd })).stdout.trim();
            const isDirty = status.length > 0;
            return { branch, commit, isDirty };
        } catch (e) {
            return { error: 'Git info unavailable' };
        }
    }

    async getConfigFile(submoduleName, filename) {
        const filePath = path.join(this.submodulesDir, submoduleName, filename);
        // Security check: ensure filePath is within submodulesDir
        if (!filePath.startsWith(this.submodulesDir)) {
            throw new Error('Invalid file path');
        }
        return await fs.readFile(filePath, 'utf-8');
    }

    async updateConfigFile(submoduleName, filename, content) {
        const filePath = path.join(this.submodulesDir, submoduleName, filename);
        if (!filePath.startsWith(this.submodulesDir)) {
            throw new Error('Invalid file path');
        }
        await fs.writeFile(filePath, content, 'utf-8');
        return { success: true };
    }

    async executeScriptStream(submoduleName, scriptName, command, socket) {
        const cwd = path.join(this.submodulesDir, submoduleName);
        if (!cwd.startsWith(this.submodulesDir)) {
            socket.send(JSON.stringify({ type: 'error', data: 'Invalid path' }));
            socket.close();
            return;
        }

        const processId = `${submoduleName}:${scriptName}`;

        // Check if process is already running
        if (this.runningProcesses.has(processId)) {
            const running = this.runningProcesses.get(processId);

            // Send history to new client
            socket.send(JSON.stringify({ type: 'system', data: `Attaching to running process (PID: ${running.pid})...\n` }));
            for (const msg of running.history) {
                socket.send(JSON.stringify(msg));
            }

            // Add client to active set
            running.clients.add(socket);

            socket.on('close', () => {
                running.clients.delete(socket);
                // Do NOT kill process on disconnect - it's persistent now
            });

            return;
        }

        // Start new process
        const [cmd, ...args] = command.split(' ');

        try {
            const childProcess = spawn(cmd, args, { cwd, shell: true });

            const processState = {
                pid: childProcess.pid,
                submoduleName,
                scriptName,
                startTime: Date.now(),
                process: childProcess,
                clients: new Set([socket]),
                history: []
            };

            this.runningProcesses.set(processId, processState);

            const broadcast = (msg) => {
                // Add to history (limit to 100 lines)
                processState.history.push(msg);
                if (processState.history.length > 1000) {
                    processState.history.shift();
                }

                // Send to all clients
                for (const client of processState.clients) {
                    if (client.readyState === 1) { // WebSocket.OPEN
                        client.send(JSON.stringify(msg));
                    }
                }
            };

            childProcess.stdout.on('data', (data) => {
                const text = data.toString();
                broadcast({ type: 'stdout', data: text });
            });

            childProcess.stderr.on('data', (data) => {
                const text = data.toString();
                broadcast({ type: 'stderr', data: text });
            });

            childProcess.on('close', (code) => {
                broadcast({ type: 'exit', code });
                // Close all clients
                for (const client of processState.clients) {
                    client.close();
                }
                this.runningProcesses.delete(processId);
            });

            childProcess.on('error', (err) => {
                broadcast({ type: 'error', data: err.message });
                for (const client of processState.clients) {
                    client.close();
                }
                this.runningProcesses.delete(processId);
            });

            // Handle initial client disconnect
            socket.on('close', () => {
                processState.clients.delete(socket);
            });

        } catch (err) {
            socket.send(JSON.stringify({ type: 'error', data: err.message }));
            socket.close();
        }
    }

    getRunningProcesses() {
        return Array.from(this.runningProcesses.values()).map(p => ({
            id: `${p.submoduleName}:${p.scriptName}`,
            submoduleName: p.submoduleName,
            scriptName: p.scriptName,
            pid: p.pid,
            startTime: p.startTime,
            clientCount: p.clients.size
        }));
    }

    killProcess(processId) {
        const processState = this.runningProcesses.get(processId);
        if (processState) {
            processState.process.kill();
            return true;
        }
    }
}
