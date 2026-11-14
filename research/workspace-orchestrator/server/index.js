const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const { spawn, execFile } = require('child_process');
const path = require('path');
const fs = require('fs');
const net = require('net');
const http = require('http');
const getPort = require('get-port');

const app = express();
const PORT = Number(process.env.PORT) || 2999;
const WORKSPACE_ROOT = path.resolve(__dirname, '../../../');
const CLIENT_DIR = path.resolve(__dirname, '../client');

app.use(cors());
app.use(bodyParser.json());
app.use(express.static(CLIENT_DIR));

const processes = new Map(); // name -> { child, pid, port, status, logs, startedAt, engine }

// Lower a Windows process priority to BelowNormal so background tasks never starve interactive apps
function setBelowNormalPriority(pid) {
    if (!pid || process.platform !== 'win32') return;
    const psCmd = `try { $p = Get-Process -Id ${Number(pid)} -ErrorAction SilentlyContinue; if ($p) { $p.PriorityClass = 'BelowNormal' } } catch {}`;
    const child = spawn('powershell.exe', ['-NoProfile', '-NonInteractive', '-WindowStyle', 'Hidden', '-Command', psCmd], {
        windowsHide: true,
        stdio: 'ignore'
    });
    child.unref();
}

// Lower our own server priority on startup
setBelowNormalPriority(process.pid);

// Canonical Go Services from start.bat (7 projects, 10 binaries)
const GO_SERVICES = [
    {
        id: 'tabby-backend',
        project: 'tabby-go',
        exe: 'tabby-backend.exe',
        cwd: 'tabby/tabby-go',
        buildArgs: ['build', '-buildvcs=false', '-o', 'tabby-backend.exe', './cmd/tabby-backend'],
        desc: 'Tabby Go terminal multiplexer, SSH session manager, and PTY backend daemon.'
    },
    {
        id: 'tabby-native',
        project: 'tabby-go',
        exe: 'tabby-native.exe',
        cwd: 'tabby/tabby-go',
        buildArgs: ['build', '-buildvcs=false', '-o', 'tabby-native.exe', './cmd/tabby-native'],
        desc: 'Tabby Go native OS integration host for shell profiles and local pipes.'
    },
    {
        id: 'tabby-wails',
        project: 'tabby-go',
        exe: 'tabby-wails.exe',
        cwd: 'tabby/tabby-go',
        buildCwd: 'tabby/tabby-go/wails-app',
        buildArgs: ['build', '-buildvcs=false', '-o', '../tabby-wails.exe', '.'],
        gui: true,
        desc: 'Tabby Go desktop GUI shell powered by Wails.'
    },
    {
        id: 'hermes-agent-go',
        project: 'hermes-agent',
        exe: 'hermes-agent-go.exe',
        cwd: 'hermes-agent',
        buildArgs: ['build', '-buildvcs=false', '-ldflags=-s -w', '-o', 'hermes-agent-go.exe', './cmd/hermes'],
        desc: 'Self-improving autonomous AI agent with MCP client, skill runner, and persistent memory.'
    },
    {
        id: 'hyperharness',
        project: 'hyperharness',
        exe: 'hyperharness.exe',
        cwd: 'hyperharness',
        buildArgs: ['build', '-buildvcs=false', '-ldflags=-s -w', '-o', 'hyperharness.exe', '.'],
        desc: 'Multi-model AI control plane, coding harness, and tool execution router.'
    },
    {
        id: 'pi-go',
        project: 'pi-mono',
        exe: 'pi-go.exe',
        cwd: 'pi-mono',
        buildArgs: ['build', '-buildvcs=false', '-ldflags=-s -w', '-o', 'pi-go.exe', './cmd/pi'],
        desc: 'Pi-Mono Go agent runtime with provider failover and autonomous cron scheduler.'
    },
    {
        id: 'npp-go',
        project: 'npp-go',
        exe: 'npp-go.exe',
        cwd: 'npp/go-port',
        buildArgs: ['build', '-buildvcs=false', '-ldflags=-s -w', '-o', 'npp-go.exe', './cmd/ultra'],
        desc: 'Notepad++ Ultra Go backend providing LSP bridge, syntax engine, and buffer commands.'
    },
    {
        id: 'npp_bqt',
        project: 'npp-go',
        exe: 'npp_bqt.exe',
        cwd: 'npp/bqt',
        buildArgs: ['build', '-buildvcs=false', '-o', 'npp_bqt.exe', '.'],
        gui: true,
        desc: 'Notepad++ BQT cross-platform native desktop editor shell.'
    },
    {
        id: 'warp-go',
        project: 'warp',
        exe: 'warp-go.exe',
        cwd: 'warp',
        buildArgs: ['build', '-buildvcs=false', '-ldflags=-s -w', '-o', 'warp-go.exe', './cmd/warp'],
        gui: true,
        desc: 'Warp Go GPU-accelerated block terminal, PTY runner, and integrated code editor.'
    },
    {
        id: 'hyper-go',
        project: 'hyper',
        exe: 'hyper-go.exe',
        cwd: 'hyper',
        buildArgs: ['build', '-buildvcs=false', '-ldflags=-s -w', '-o', 'hyper-go.exe', '.'],
        gui: true,
        desc: 'Hyper Go extensible terminal emulator with plugin architecture and custom UI.'
    }
];

// Infrastructure ports monitored in the Executive Telemetry bar
const INFRA_PORTS = [
    { port: 2999, name: 'Workspace Control Center', role: 'Unified Dashboard & Process Orchestrator', url: 'http://localhost:2999' },
    { port: 7778, name: 'HyperNexus Engine', role: 'Go Control Plane API & WebSocket Daemon', url: 'http://localhost:7778' },
    { port: 7779, name: 'HyperNexus Web UI', role: 'Next.js Multi-Agent Federation Console', url: 'http://localhost:7779' },
    { port: 8082, name: 'Jules Autopilot API', role: 'Autonomous PR, Fleet & Session Dispatcher', url: 'http://localhost:8082' },
    { port: 3006, name: 'Jules Autopilot UI', role: 'Jules Fleet Monitoring Web Interface', url: 'http://localhost:3006' },
    { port: 9222, name: 'MS Edge CDP Bridge', role: 'Multi-Agent Browser Coordination Bus (Bobbi/Gemini/GPT)', url: 'http://127.0.0.1:9222/json/version' }
];

const ALLOWED_DOCS = {
    'HANDOFF.md': 'HANDOFF.md',
    'ROADMAP.md': 'ROADMAP.md',
    'TODO.md': 'TODO.md',
    'CHANGELOG.md': 'CHANGELOG.md',
    'VISION.md': 'VISION.md',
    'MEMORY.md': 'MEMORY.md',
    'DEPLOY.md': 'DEPLOY.md',
    'IDEAS.md': 'IDEAS.md',
    'MASTER_IDEAS.md': 'MASTER_IDEAS.md',
    'UNITED_BEATS_UMBRELLA_v7.md': 'UNITED_BEATS_UMBRELLA_v7.md',
    'SUBMODULE_DASHBOARD.md': 'SUBMODULE_DASHBOARD.md'
};

function probeTcpPort(port, host = '127.0.0.1', timeoutMs = 450) {
    return new Promise((resolve) => {
        const socket = new net.Socket();
        let settled = false;
        const done = (online) => {
            if (!settled) {
                settled = true;
                socket.destroy();
                resolve(online);
            }
        };
        socket.setTimeout(timeoutMs);
        socket.once('connect', () => done(true));
        socket.once('timeout', () => done(false));
        socket.once('error', () => done(false));
        socket.connect(port, host);
    });
}

function fetchJsonLocal(url, timeoutMs = 600) {
    return new Promise((resolve) => {
        const req = http.get(url, { timeout: timeoutMs }, (res) => {
            let raw = '';
            res.on('data', (c) => { raw += c; });
            res.on('end', () => {
                try { resolve(JSON.parse(raw)); } catch { resolve(null); }
            });
        });
        req.on('error', () => resolve(null));
        req.on('timeout', () => { req.destroy(); resolve(null); });
    });
}

let cachedTasklist = { ts: 0, map: new Map() };
function getRunningProcessesWin() {
    if (process.platform !== 'win32') return Promise.resolve(new Map());
    const now = Date.now();
    if (now - cachedTasklist.ts < 2500) return Promise.resolve(cachedTasklist.map);
    return new Promise((resolve) => {
        execFile('tasklist', ['/FO', 'CSV', '/NH'], { windowsHide: true, timeout: 4000, maxBuffer: 4 * 1024 * 1024 }, (err, stdout) => {
            const procMap = new Map();
            if (!err && stdout) {
                const lines = stdout.split(/\r?\n/);
                for (const line of lines) {
                    if (!line.startsWith('"')) continue;
                    const parts = line.split('","');
                    if (parts.length >= 2) {
                        const img = parts[0].replace(/^"/, '').toLowerCase();
                        const pid = parseInt(parts[1], 10);
                        if (!procMap.has(img)) procMap.set(img, []);
                        if (!Number.isNaN(pid)) procMap.get(img).push(pid);
                    }
                }
            }
            cachedTasklist = { ts: now, map: procMap };
            resolve(procMap);
        });
    });
}

function readGitHeadFast(repoDir) {
    try {
        let gitDir = path.join(repoDir, '.git');
        if (!fs.existsSync(gitDir)) return { branch: 'uninitialized', sha: '—' };
        const st = fs.statSync(gitDir);
        if (st.isFile()) {
            const content = fs.readFileSync(gitDir, 'utf8').trim();
            if (content.startsWith('gitdir:')) {
                const rel = content.slice(7).trim();
                gitDir = path.resolve(repoDir, rel);
            }
        }
        const headPath = path.join(gitDir, 'HEAD');
        if (!fs.existsSync(headPath)) return { branch: 'unknown', sha: '—' };
        const headRaw = fs.readFileSync(headPath, 'utf8').trim();
        if (headRaw.startsWith('ref:')) {
            const refRel = headRaw.slice(4).trim();
            const branch = refRel.replace(/^refs\/heads\//, '');
            const refFile = path.join(gitDir, refRel);
            if (fs.existsSync(refFile)) {
                const sha = fs.readFileSync(refFile, 'utf8').trim().slice(0, 8);
                return { branch, sha };
            }
            const packedPath = path.join(gitDir, 'packed-refs');
            if (fs.existsSync(packedPath)) {
                const packed = fs.readFileSync(packedPath, 'utf8');
                const line = packed.split(/\r?\n/).find((l) => l.endsWith(' ' + refRel));
                if (line) return { branch, sha: line.split(' ')[0].slice(0, 8) };
            }
            return { branch, sha: '—' };
        }
        return { branch: 'detached', sha: headRaw.slice(0, 8) };
    } catch {
        return { branch: 'unknown', sha: '—' };
    }
}

function categorizeProject(name) {
    const n = name.toLowerCase();
    if (/agent|jules|hermes|hyper|pi-mono|nexus|claw|claude|gemini|llm|mcp|prompt|skill|mem|sirens|sales_bot|brobocallz|orchestrator/.test(n)) {
        return 'AI & Agents';
    }
    if (/beat|mani|itg|stepmania|arrowvortex|dj|ableton|vst|milkdrop|projectm|timidity|tidal|spot|subsonic|funkwhale|soulseek/.test(n)) {
        return 'Rhythm & Audio';
    }
    if (/geany|npp|bqt|btk|bgtk|bcs|tabby|warp|code|cursor/.test(n)) {
        return 'IDEs & Toolkits';
    }
    if (/bobsgame|ball|mparty|rom|emu|poker|saver|roud/.test(n)) {
        return 'Games & Engines';
    }
    return 'Web & Platforms';
}

function parseSubmodulesFast() {
    const gmPath = path.join(WORKSPACE_ROOT, '.gitmodules');
    if (!fs.existsSync(gmPath)) return [];
    const raw = fs.readFileSync(gmPath, 'utf8');
    const blocks = raw.split(/\[submodule\s+"([^"]+)"\]/g);
    const subs = [];
    for (let i = 1; i < blocks.length; i += 2) {
        const name = blocks[i];
        const body = blocks[i + 1] || '';
        const pMatch = body.match(/^\s*path\s*=\s*(.+)$/m);
        const uMatch = body.match(/^\s*url\s*=\s*(.+)$/m);
        const bMatch = body.match(/^\s*branch\s*=\s*(.+)$/m);
        const subPath = pMatch ? pMatch[1].trim() : name;
        const url = uMatch ? uMatch[1].trim() : '';
        const trackedBranch = bMatch ? bMatch[1].trim() : '';
        const absPath = path.join(WORKSPACE_ROOT, subPath);
        const { branch, sha } = readGitHeadFast(absPath);

        let version = '—';
        for (const vf of ['VERSION', 'VERSION.md', 'package.json']) {
            const vp = path.join(absPath, vf);
            if (fs.existsSync(vp)) {
                try {
                    if (vf === 'package.json') {
                        const pkg = JSON.parse(fs.readFileSync(vp, 'utf8'));
                        if (pkg.version) { version = pkg.version; break; }
                    } else {
                        const first = fs.readFileSync(vp, 'utf8').split(/\r?\n/).find((l) => l.trim() && !l.startsWith('#'));
                        if (first) { version = first.trim().slice(0, 24); break; }
                    }
                } catch {}
            }
        }

        subs.push({
            name,
            path: subPath,
            absPath,
            url,
            owner: url.includes('robertpelloni') ? 'robertpelloni' : (url.split('/')[3] || 'external'),
            branch,
            trackedBranch,
            sha,
            version,
            category: categorizeProject(subPath)
        });
    }
    return subs;
}

function discoverProjects() {
    const projects = [];
    const searchDirs = [
        WORKSPACE_ROOT,
        path.join(WORKSPACE_ROOT, 'research'),
        path.join(WORKSPACE_ROOT, 'superbobbyball')
    ];
    const seenPaths = new Set();

    searchDirs.forEach((baseDir) => {
        if (!fs.existsSync(baseDir)) return;
        let items = [];
        try { items = fs.readdirSync(baseDir); } catch { return; }

        items.forEach((item) => {
            if (item.startsWith('.') || item === 'node_modules' || item === 'archive' || item === 'backups') return;
            const itemPath = path.join(baseDir, item);
            if (seenPaths.has(itemPath)) return;
            let stat;
            try { stat = fs.statSync(itemPath); } catch { return; }
            if (!stat.isDirectory()) return;
            seenPaths.add(itemPath);

            let projectType = 'native';
            let version = '—';
            let description = '';
            let scripts = [];
            let hasExe = false;

            const pkgPath = path.join(itemPath, 'package.json');
            if (fs.existsSync(pkgPath)) {
                try {
                    const pkg = JSON.parse(fs.readFileSync(pkgPath, 'utf8'));
                    projectType = 'node';
                    version = pkg.version || '—';
                    description = pkg.description || '';
                    scripts = Object.keys(pkg.scripts || {});
                } catch {}
            } else if (fs.existsSync(path.join(itemPath, 'go.mod'))) {
                projectType = 'go';
            } else if (fs.existsSync(path.join(itemPath, 'Cargo.toml'))) {
                projectType = 'rust';
            } else if (fs.existsSync(path.join(itemPath, 'CMakeLists.txt'))) {
                projectType = 'cpp';
            } else if (fs.existsSync(path.join(itemPath, 'pyproject.toml')) || fs.existsSync(path.join(itemPath, 'requirements.txt'))) {
                projectType = 'python';
            } else {
                return;
            }

            if (version === '—') {
                const vFile = path.join(itemPath, 'VERSION');
                if (fs.existsSync(vFile)) {
                    try { version = fs.readFileSync(vFile, 'utf8').trim().slice(0, 20); } catch {}
                }
            }

            const checkExe = (dir) => {
                if (!fs.existsSync(dir)) return false;
                try {
                    return fs.readdirSync(dir).some((f) => f.toLowerCase().endsWith('.exe'));
                } catch {
                    return false;
                }
            };

            hasExe = checkExe(itemPath) ||
                checkExe(path.join(itemPath, 'bin')) ||
                checkExe(path.join(itemPath, 'build', 'Release')) ||
                checkExe(path.join(itemPath, 'target', 'release')) ||
                checkExe(path.join(itemPath, 'dist'));

            projects.push({
                name: baseDir === WORKSPACE_ROOT ? item : `${path.basename(baseDir)}/${item}`,
                path: itemPath,
                relPath: path.relative(WORKSPACE_ROOT, itemPath).replace(/\\/g, '/'),
                type: projectType,
                category: categorizeProject(item),
                version,
                description,
                scripts,
                hasExe
            });
        });
    });

    return projects.sort((a, b) => a.name.localeCompare(b.name));
}

async function getGoServiceStates() {
    const procMap = await getRunningProcessesWin();
    return GO_SERVICES.map((svc) => {
        const exePath = path.join(WORKSPACE_ROOT, svc.cwd, svc.exe);
        const exists = fs.existsSync(exePath);
        let sizeMb = null;
        if (exists) {
            try { sizeMb = +(fs.statSync(exePath).size / (1024 * 1024)).toFixed(1); } catch {}
        }
        const pids = procMap.get(svc.exe.toLowerCase()) || [];
        return {
            ...svc,
            exePath,
            built: exists,
            sizeMb,
            running: pids.length > 0,
            pids
        };
    });
}

// --- API ROUTES ---

app.get('/api/overview', async (req, res) => {
    let version = 'unknown';
    try { version = fs.readFileSync(path.join(WORKSPACE_ROOT, 'VERSION'), 'utf8').trim(); } catch {}
    const rootGit = readGitHeadFast(WORKSPACE_ROOT);
    const submodules = parseSubmodulesFast();
    const initializedCount = submodules.filter((s) => s.branch !== 'uninitialized').length;

    const [portStatuses, goStates] = await Promise.all([
        Promise.all(INFRA_PORTS.map(async (p) => {
            const online = p.port === PORT ? true : await probeTcpPort(p.port);
            let meta = null;
            if (online && p.port === 9222) {
                const tabs = await fetchJsonLocal('http://127.0.0.1:9222/json/list');
                if (Array.isArray(tabs)) {
                    meta = `${tabs.filter((t) => t.type === 'page').length} tabs`;
                }
            }
            return { ...p, online, meta };
        })),
        getGoServiceStates()
    ]);

    res.json({
        version,
        branch: rootGit.branch,
        sha: rootGit.sha,
        workspaceRoot: WORKSPACE_ROOT,
        orchestratorPid: process.pid,
        priority: 'BelowNormal',
        submodulesTotal: submodules.length,
        submodulesInitialized: initializedCount,
        goServicesRunning: goStates.filter((g) => g.running).length,
        goServicesBuilt: goStates.filter((g) => g.built).length,
        goServicesTotal: goStates.length,
        managedProcessesRunning: processes.size,
        ports: portStatuses,
        timestamp: new Date().toISOString()
    });
});

app.get('/api/go-services', async (req, res) => {
    const states = await getGoServiceStates();
    res.json(states);
});

app.post('/api/go-services/start', async (req, res) => {
    const { id } = req.body || {};
    const targets = id === 'all' ? GO_SERVICES : GO_SERVICES.filter((s) => s.id === id);
    if (!targets.length) return res.status(400).json({ error: 'Unknown Go service id' });

    const launched = [];
    for (const svc of targets) {
        const cwd = path.join(WORKSPACE_ROOT, svc.cwd);
        const exePath = path.join(cwd, svc.exe);
        if (!fs.existsSync(exePath)) continue;
        const child = spawn(exePath, [], {
            cwd,
            detached: true,
            windowsHide: !svc.gui,
            stdio: 'ignore'
        });
        setBelowNormalPriority(child.pid);
        child.unref();
        launched.push({ id: svc.id, pid: child.pid });
    }
    cachedTasklist.ts = 0;
    res.json({ success: true, launched });
});

app.post('/api/go-services/stop', async (req, res) => {
    const { id } = req.body || {};
    const targets = id === 'all' ? GO_SERVICES : GO_SERVICES.filter((s) => s.id === id);
    if (!targets.length) return res.status(400).json({ error: 'Unknown Go service id' });

    await Promise.all(targets.map((svc) => new Promise((resolve) => {
        if (process.platform === 'win32') {
            execFile('taskkill', ['/F', '/IM', svc.exe], { windowsHide: true }, () => resolve());
        } else {
            execFile('pkill', ['-f', svc.exe], () => resolve());
        }
    })));
    cachedTasklist.ts = 0;
    res.json({ success: true, stopped: targets.map((t) => t.id) });
});

app.post('/api/go-services/build', async (req, res) => {
    const { id } = req.body || {};
    const targets = id === 'all' ? GO_SERVICES : GO_SERVICES.filter((s) => s.id === id);
    if (!targets.length) return res.status(400).json({ error: 'Unknown Go service id' });

    const results = [];
    for (const svc of targets) {
        const buildDir = path.join(WORKSPACE_ROOT, svc.buildCwd || svc.cwd);
        if (!fs.existsSync(buildDir)) {
            results.push({ id: svc.id, ok: false, error: 'Directory missing' });
            continue;
        }
        // eslint-disable-next-line no-await-in-loop
        const r = await new Promise((resolve) => {
            const buildEnv = { ...process.env };
            if (!buildEnv.GOCACHE && fs.existsSync('D:\\agent-cache')) {
                buildEnv.GOCACHE = 'D:\\agent-cache\\go-build';
                buildEnv.GOTMPDIR = 'D:\\agent-cache\\go-tmp';
            }
            const child = spawn('go', svc.buildArgs, { cwd: buildDir, env: buildEnv, windowsHide: true });
            setBelowNormalPriority(child.pid);
            let stderr = '';
            child.stderr.on('data', (d) => { stderr += d.toString(); });
            child.on('close', (code) => resolve({ id: svc.id, ok: code === 0, error: code === 0 ? null : stderr.slice(0, 400) }));
            child.on('error', (e) => resolve({ id: svc.id, ok: false, error: e.message }));
        });
        results.push(r);
    }
    res.json({ success: results.every((r) => r.ok), results });
});

app.get('/api/submodules', (req, res) => {
    res.json(parseSubmodulesFast());
});

app.get('/api/docs/:doc', (req, res) => {
    const rel = ALLOWED_DOCS[req.params.doc];
    if (!rel) return res.status(404).json({ error: 'Document not registered' });
    const full = path.join(WORKSPACE_ROOT, rel);
    if (!fs.existsSync(full)) return res.status(404).json({ error: `${rel} not found on disk` });
    const content = fs.readFileSync(full, 'utf8');
    const stat = fs.statSync(full);
    res.json({ name: req.params.doc, updatedAt: stat.mtime.toISOString(), sizeBytes: stat.size, content });
});

app.get('/api/projects', (req, res) => {
    const projects = discoverProjects();
    res.json(projects.map((p) => ({
        ...p,
        isRunning: processes.has(p.name),
        port: processes.has(p.name) ? processes.get(p.name).port : null
    })));
});

app.post('/api/start', async (req, res) => {
    const { name, path: projectPath, engine } = req.body || {};
    if (!name || !projectPath) return res.status(400).json({ error: 'Missing name or path' });
    if (processes.has(name)) {
        return res.status(400).json({ error: 'Project already running' });
    }

    try {
        const port = await getPort();
        const env = { ...process.env, PORT: port.toString() };
        let cmd = process.platform === 'win32' ? 'npm.cmd' : 'npm';
        let args = ['run', 'dev'];

        const pkgPath = path.join(projectPath, 'package.json');
        if (fs.existsSync(pkgPath)) {
            const pkg = JSON.parse(fs.readFileSync(pkgPath, 'utf8'));
            const script = pkg.scripts && pkg.scripts.dev ? 'dev' : (pkg.scripts && pkg.scripts.start ? 'start' : null);
            if (script) args = ['run', script];
        }

        if (engine === 'bun') cmd = 'bun';

        const child = spawn(cmd, args, {
            cwd: projectPath,
            env,
            shell: true,
            windowsHide: true
        });
        setBelowNormalPriority(child.pid);

        const processData = {
            port,
            pid: child.pid,
            engine: engine || 'node',
            startedAt: new Date().toISOString(),
            status: 'running',
            logs: `[Orchestrator] Spawned ${name} (${cmd} ${args.join(' ')}) on PORT=${port} at BelowNormal priority\n`,
            child
        };

        child.stdout.on('data', (data) => {
            processData.logs += data.toString();
            if (processData.logs.length > 20000) processData.logs = processData.logs.slice(-20000);
        });

        child.stderr.on('data', (data) => {
            processData.logs += `[STDERR] ${data.toString()}`;
            if (processData.logs.length > 20000) processData.logs = processData.logs.slice(-20000);
        });

        child.on('close', (code) => {
            processData.logs += `\n[Orchestrator] Exited with code ${code}\n`;
            processes.delete(name);
        });

        processes.set(name, processData);
        res.json({ success: true, port, pid: child.pid });
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.post('/api/stop', (req, res) => {
    const { name } = req.body || {};
    if (!processes.has(name)) {
        return res.status(400).json({ error: 'Project not running' });
    }

    const { child } = processes.get(name);
    if (process.platform === 'win32') {
        spawn('taskkill', ['/pid', String(child.pid), '/f', '/t'], { windowsHide: true });
    } else {
        child.kill('SIGTERM');
    }
    processes.delete(name);
    res.json({ success: true });
});

app.post('/api/open-folder', (req, res) => {
    const { path: projectPath } = req.body || {};
    if (!projectPath || !fs.existsSync(projectPath)) {
        return res.status(400).json({ error: 'Folder does not exist' });
    }
    const command = process.platform === 'darwin' ? 'open' : (process.platform === 'win32' ? 'explorer.exe' : 'xdg-open');
    const child = spawn(command, [projectPath], { detached: true, windowsHide: false, stdio: 'ignore' });
    child.unref();
    res.json({ success: true });
});

app.post('/api/run-exe', (req, res) => {
    const { path: projectPath } = req.body || {};
    if (!projectPath) return res.status(400).json({ error: 'Missing project path' });
    const searchPaths = [
        projectPath,
        path.join(projectPath, 'bin'),
        path.join(projectPath, 'build', 'Release'),
        path.join(projectPath, 'target', 'release'),
        path.join(projectPath, 'dist'),
        path.join(projectPath, 'build_output')
    ];

    let foundExe = null;
    for (const sp of searchPaths) {
        if (fs.existsSync(sp)) {
            const spFiles = fs.readdirSync(sp);
            const exe = spFiles.find((f) => f.toLowerCase().endsWith('.exe'));
            if (exe) {
                foundExe = path.join(sp, exe);
                break;
            }
        }
    }

    if (foundExe) {
        const child = spawn(foundExe, [], { cwd: projectPath, detached: true, stdio: 'ignore' });
        setBelowNormalPriority(child.pid);
        child.unref();
        res.json({ success: true, exe: foundExe, pid: child.pid });
    } else {
        res.status(400).json({ error: 'No executable (.exe) found in project build paths' });
    }
});

app.get('/api/logs/:name', (req, res) => {
    const proc = processes.get(req.params.name);
    res.json({ logs: proc ? proc.logs : 'No active logs recorded for this project.' });
});

app.post('/api/shutdown', (req, res) => {
    for (const [, proc] of processes.entries()) {
        if (proc.child && proc.child.pid) {
            if (process.platform === 'win32') {
                spawn('taskkill', ['/pid', String(proc.child.pid), '/f', '/t'], { windowsHide: true });
            } else {
                proc.child.kill('SIGTERM');
            }
        }
    }
    processes.clear();
    res.json({ success: true, message: 'Shutting down Workspace Control Center backend...' });
    setTimeout(() => process.exit(0), 250);
});

const server = app.listen(PORT, () => {
    console.log(`Omni-Workspace Control Center v2.0.0 running at http://localhost:${PORT} (Priority: BelowNormal)`);
});

module.exports = { app, server };
