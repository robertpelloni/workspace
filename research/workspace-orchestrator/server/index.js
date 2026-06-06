const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const { spawn } = require('child_process');
const path = require('path');
const fs = require('fs');
const getPort = require('get-port');

const app = express();
const PORT = 2999;
const WORKSPACE_ROOT = path.resolve(__dirname, '../../');

app.use(cors());
app.use(bodyParser.json());

const processes = new Map(); // name -> { child, port, status, logs }

function discoverProjects() {
    const projects = [];
    const searchDirs = [WORKSPACE_ROOT, path.join(WORKSPACE_ROOT, 'superbobbyball')];

    searchDirs.forEach(baseDir => {
        if (!fs.existsSync(baseDir)) return;
        
        const items = fs.readdirSync(baseDir);
        items.forEach(item => {
            const itemPath = path.join(baseDir, item);
            if (fs.statSync(itemPath).isDirectory() && !item.startsWith('.')) {
                let projectType = 'unknown';
                let version = 'unknown';
                let scripts = [];
                let hasExe = false;

                const pkgPath = path.join(itemPath, 'package.json');
                if (fs.existsSync(pkgPath)) {
                    try {
                        const pkg = JSON.parse(fs.readFileSync(pkgPath, 'utf8'));
                        projectType = 'node';
                        version = pkg.version || 'unknown';
                        scripts = Object.keys(pkg.scripts || {});
                    } catch (e) {}
                }

                // Check for executables
                const checkExe = (dir) => {
                    if (!fs.existsSync(dir)) return false;
                    try {
                        const files = fs.readdirSync(dir);
                        for (const f of files) {
                            if (f.endsWith('.exe')) return true;
                            // Check for linux binaries without extension
                            const stat = fs.statSync(path.join(dir, f));
                            if (!stat.isDirectory() && (stat.mode & 0o111) && !f.includes('.')) return true; 
                        }
                    } catch(e) {}
                    return false;
                };

                hasExe = checkExe(itemPath) || 
                         checkExe(path.join(itemPath, 'build', 'Release')) || 
                         checkExe(path.join(itemPath, 'target', 'release')) ||
                         checkExe(path.join(itemPath, 'dist'));

                if (projectType === 'node' || hasExe || fs.existsSync(path.join(itemPath, 'CMakeLists.txt')) || fs.existsSync(path.join(itemPath, 'Cargo.toml'))) {
                    projects.push({
                        name: item,
                        path: itemPath,
                        type: projectType,
                        version: version,
                        scripts: scripts,
                        hasExe: hasExe
                    });
                }
            }
        });
    });
    return projects;
}

app.get('/api/projects', (req, res) => {
    const projects = discoverProjects();
    res.json(projects.map(p => ({
        ...p,
        isRunning: processes.has(p.name),
        port: processes.has(p.name) ? processes.get(p.name).port : null
    })));
});

app.post('/api/start', async (req, res) => {
    const { name, path: projectPath, engine } = req.body;
    if (processes.has(name)) {
        return res.status(400).json({ error: 'Project already running' });
    }

    try {
        const port = await getPort();
        console.log(`Starting ${name} on port ${port} using ${engine}...`);

        const env = { ...process.env, PORT: port.toString() };
        let cmd = 'npm';
        let args = ['run', 'dev'];

        const pkgPath = path.join(projectPath, 'package.json');
        if (fs.existsSync(pkgPath)) {
            const pkg = JSON.parse(fs.readFileSync(pkgPath, 'utf8'));
            const script = pkg.scripts && pkg.scripts.dev ? 'dev' : (pkg.scripts && pkg.scripts.start ? 'start' : null);
            if (script) args = ['run', script];
        }

        if (engine === 'bun') {
            cmd = 'bun';
        } else if (engine === 'node') {
            cmd = process.platform === 'win32' ? 'npm.cmd' : 'npm';
        } else {
            cmd = process.platform === 'win32' ? 'npm.cmd' : 'npm'; // Default
        }

        const child = spawn(cmd, args, {
            cwd: projectPath,
            env,
            shell: true
        });

        const processData = {
            port,
            status: 'running',
            logs: '',
            child
        };

        child.stdout.on('data', (data) => {
            processData.logs += data.toString();
            if (processData.logs.length > 10000) processData.logs = processData.logs.slice(-10000);
        });

        child.stderr.on('data', (data) => {
            processData.logs += `ERROR: ${data.toString()}`;
        });

        child.on('close', (code) => {
            console.log(`${name} exited with code ${code}`);
            processes.delete(name);
        });

        processes.set(name, processData);
        res.json({ success: true, port });
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.post('/api/stop', (req, res) => {
    const { name } = req.body;
    if (!processes.has(name)) {
        return res.status(400).json({ error: 'Project not running' });
    }

    const { child } = processes.get(name);
    if (process.platform === 'win32') {
        spawn('taskkill', ['/pid', child.pid, '/f', '/t']);
    } else {
        process.kill(-child.pid, 'SIGKILL'); // Requires detached process usually, or just kill the child
        child.kill('SIGKILL');
    }
    processes.delete(name);
    res.json({ success: true });
});

app.post('/api/open-folder', (req, res) => {
    const { path: projectPath } = req.body;
    let command;
    switch (process.platform) {
        case 'darwin': command = 'open'; break;
        case 'win32': command = 'explorer'; break;
        default: command = 'xdg-open'; break;
    }
    spawn(command, [projectPath], { detached: true, shell: true });
    res.json({ success: true });
});

app.post('/api/run-exe', (req, res) => {
    const { path: projectPath } = req.body;
    const searchPaths = [
        projectPath,
        path.join(projectPath, 'build', 'Release'),
        path.join(projectPath, 'target', 'release'),
        path.join(projectPath, 'dist'),
        path.join(projectPath, 'build_output')
    ];
    
    let foundExe = null;
    for (const sp of searchPaths) {
        if (fs.existsSync(sp)) {
            const spFiles = fs.readdirSync(sp);
            const exe = spFiles.find(f => {
                if (f.endsWith('.exe')) return true;
                if (process.platform !== 'win32') {
                    try {
                        const stat = fs.statSync(path.join(sp, f));
                        return !stat.isDirectory() && (stat.mode & 0o111) && !f.includes('.');
                    } catch(e) { return false; }
                }
                return false;
            });
            if (exe) {
                foundExe = path.join(sp, exe);
                break;
            }
        }
    }

    if (foundExe) {
        spawn(foundExe, [], { cwd: projectPath, detached: true, shell: true });
        res.json({ success: true, exe: foundExe });
    } else {
        res.status(400).json({ error: 'No executable found' });
    }
});

app.get('/api/logs/:name', (req, res) => {
    const proc = processes.get(req.params.name);
    res.json({ logs: proc ? proc.logs : 'No logs available' });
});

app.listen(PORT, () => {
    console.log(`Workspace Orchestrator Backend running at http://localhost:${PORT}`);
});