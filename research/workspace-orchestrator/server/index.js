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

// Canonical Go Services from start.bat (9 projects, 12 binaries)
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
        desc: 'Tabby Go desktop GUI shell powered by Wails (v1.0.285).'
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
        desc: 'Warp Go GPU-accelerated block terminal, command palette, and integrated editor (v0.3.2).'
    },
    {
        id: 'hyper-go',
        project: 'hyper',
        exe: 'hyper-go.exe',
        cwd: 'hyper',
        buildArgs: ['build', '-buildvcs=false', '-ldflags=-s -w', '-o', 'hyper-go.exe', '.'],
        gui: true,
        desc: 'Hyper Go v1.2.0 terminal emulator with Mission Control, SSH manager, and MCP integration.'
    },
    {
        id: 'freellm',
        project: 'freellm',
        exe: 'freellm.exe',
        cwd: 'freellm',
        buildArgs: ['build', '-buildvcs=false', '-ldflags=-s -w', '-o', 'freellm.exe', './cmd/app'],
        gui: true,
        desc: 'FreeLLM survival-of-the-fittest multi-provider LLM router with Windows System Tray.'
    },
    {
        id: 'bobtk',
        project: 'bgtk',
        exe: 'bobtk.exe',
        cwd: 'bgtk/go',
        buildArgs: ['build', '-buildvcs=false', '-ldflags=-s -w', '-o', 'bobtk.exe', '.'],
        runArgs: ['-serve'],
        desc: 'BobTK v1.8.0 6-pillar cross-platform audio/visual/AI framework & live web dashboard.'
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

function postJsonLocal(url, bodyObj, timeoutMs = 2500) {
    return new Promise((resolve) => {
        try {
            const payload = JSON.stringify(bodyObj);
            const u = new URL(url);
            const req = http.request({
                hostname: u.hostname,
                port: u.port,
                path: u.pathname + u.search,
                method: 'POST',
                timeout: timeoutMs,
                headers: {
                    'Content-Type': 'application/json',
                    'Content-Length': Buffer.byteLength(payload)
                }
            }, (res) => {
                let raw = '';
                res.on('data', (c) => { raw += c; });
                res.on('end', () => {
                    try { resolve({ status: res.statusCode, data: JSON.parse(raw) }); }
                    catch { resolve({ status: res.statusCode, data: null }); }
                });
            });
            req.on('error', () => resolve({ status: 0, data: null }));
            req.on('timeout', () => { req.destroy(); resolve({ status: 0, data: null }); });
            req.write(payload);
            req.end();
        } catch {
            resolve({ status: 0, data: null });
        }
    });
}

const OWNED_ORGS = new Set(['robertpelloni', 'unitedbeatsllc', 'fwberllc', 'realestatecrmllc', 'mdmatk']);
const DESKTOP_GIT = 'C:\\Users\\hyper\\AppData\\Local\\GitHubDesktop\\app-3.6.11\\resources\\app\\git\\cmd\\git.exe';
let cachedRootPins = { ts: 0, map: new Map() };
const gitDivergenceCache = new Map(); // subPath -> { ahead, behind, originRef, actionableBranches, actionableSample, scannedAt }
let divergenceScanState = { running: false, lastCompletedAt: null, scannedCount: 0 };

function getGitBin() {
    return fs.existsSync(DESKTOP_GIT) ? DESKTOP_GIT : 'git';
}

function execGitAsync(cwd, args, timeoutMs = 6000) {
    return new Promise((resolve) => {
        execFile(getGitBin(), args, { cwd, windowsHide: true, timeout: timeoutMs, maxBuffer: 2 * 1024 * 1024 }, (err, stdout) => {
            if (err) return resolve({ ok: false, stdout: '' });
            return resolve({ ok: true, stdout: String(stdout || '').trim() });
        });
    });
}

const ACTIONABLE_BRANCH_RE = /(^|\/)(jules[-/]|.*-\d{15,22}$|backup\/wip)/i;
const OWNED_AUTHOR_RE = /(robert\s*pelloni|robertpelloni|google-labs-jules|jules\[bot\]|unitedbeats|fwber|hypernexus|tormentnexus|antigravity)/i;

async function scanSubmoduleDivergenceOne(sub) {
    if (!sub || sub.branch === 'uninitialized' || !fs.existsSync(sub.absPath)) return;
    const candidates = [];
    if (sub.branch && sub.branch !== 'detached' && sub.branch !== 'unknown') {
        candidates.push(`origin/${sub.branch}`);
    }
    for (const fallback of ['origin/main', 'origin/master', 'origin/develop', 'origin/release']) {
        if (!candidates.includes(fallback)) candidates.push(fallback);
    }

    let originRef = null;
    let behind = 0;
    let ahead = 0;
    for (const ref of candidates) {
        // eslint-disable-next-line no-await-in-loop
        const lr = await execGitAsync(sub.absPath, ['rev-list', '--left-right', '--count', `${ref}...HEAD`], 4500);
        if (lr.ok && lr.stdout) {
            const parts = lr.stdout.split(/\s+/);
            if (parts.length === 2) {
                behind = parseInt(parts[0], 10) || 0;
                ahead = parseInt(parts[1], 10) || 0;
                originRef = ref;
                break;
            }
        }
    }

    let actionableBranches = 0;
    let actionableSample = [];
    if (sub.isOwned) {
        const unmerged = await execGitAsync(
            sub.absPath,
            ['for-each-ref', '--format=%(refname:short)|%(authorname)|%(authoremail)', '--no-merged=HEAD', 'refs/remotes/origin/'],
            5000
        );
        if (unmerged.ok && unmerged.stdout) {
            const filtered = [];
            for (const rawLine of unmerged.stdout.split(/\r?\n/)) {
                const [bRaw, authorName = '', authorEmail = ''] = rawLine.split('|');
                const b = (bRaw || '').trim();
                if (!b || b === 'origin/HEAD' || b === 'origin' || b === originRef || b === 'origin/gh-pages') continue;
                if (b.includes('dependabot/') || b.startsWith('origin/upstream/')) continue;
                if (ACTIONABLE_BRANCH_RE.test(b) || OWNED_AUTHOR_RE.test(`${authorName} ${authorEmail}`)) {
                    filtered.push(b);
                }
            }
            actionableBranches = filtered.length;
            actionableSample = filtered.slice(0, 6).map((b) => b.replace(/^origin\//, ''));
        }
    }

    gitDivergenceCache.set(sub.path, {
        ahead,
        behind,
        originRef,
        actionableBranches,
        actionableSample,
        scannedAt: new Date().toISOString()
    });
}

async function refreshGitDivergenceSnapshot() {
    if (divergenceScanState.running) return divergenceScanState;
    divergenceScanState.running = true;
    try {
        const subs = parseSubmodulesFast();
        const queue = subs.filter((s) => s.branch !== 'uninitialized');
        let idx = 0;
        const concurrency = 6;
        const workers = Array.from({ length: concurrency }, async () => {
            while (idx < queue.length) {
                const current = queue[idx];
                idx += 1;
                // eslint-disable-next-line no-await-in-loop
                await scanSubmoduleDivergenceOne(current);
            }
        });
        await Promise.all(workers);
        divergenceScanState.lastCompletedAt = new Date().toISOString();
        divergenceScanState.scannedCount = queue.length;
    } catch {} finally {
        divergenceScanState.running = false;
    }
    return divergenceScanState;
}

function getRootPinnedShasSync() {
    const now = Date.now();
    if (now - cachedRootPins.ts < 12000 && cachedRootPins.map.size > 0) return cachedRootPins.map;
    try {
        const { execFileSync } = require('child_process');
        const gitBin = fs.existsSync(DESKTOP_GIT) ? DESKTOP_GIT : 'git';
        const out = execFileSync(gitBin, ['ls-tree', 'HEAD'], {
            cwd: WORKSPACE_ROOT,
            encoding: 'utf8',
            windowsHide: true,
            timeout: 2500
        });
        const pinMap = new Map();
        for (const line of out.split(/\r?\n/)) {
            if (!line.startsWith('160000 ')) continue;
            const tabIdx = line.indexOf('\t');
            if (tabIdx === -1) continue;
            const sha = line.slice(0, tabIdx).split(/\s+/)[2] || '';
            const subPath = line.slice(tabIdx + 1).trim();
            if (sha && subPath) pinMap.set(subPath, sha.slice(0, 8));
        }
        cachedRootPins = { ts: now, map: pinMap };
        return pinMap;
    } catch {
        return cachedRootPins.map;
    }
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
    const pinMap = getRootPinnedShasSync();
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
        const pinnedSha = pinMap.get(subPath) || '—';
        const ownerRaw = (url.split('/')[3] || 'external').replace(/\.git$/i, '');
        const isOwned = OWNED_ORGS.has(ownerRaw.toLowerCase());

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

        // Also recognize hymnmania junction to bobmani/hymnmania when top-level dir lacks direct .git
        let resolvedAbsPath = absPath;
        let resolvedGit = { branch, sha };
        if (resolvedGit.branch === 'uninitialized' && subPath === 'hymnmania') {
            const junctionTarget = path.join(WORKSPACE_ROOT, 'bobmani', 'hymnmania');
            if (fs.existsSync(junctionTarget)) {
                resolvedAbsPath = junctionTarget;
                resolvedGit = readGitHeadFast(junctionTarget);
            }
        }
        const div = gitDivergenceCache.get(subPath) || null;
        let nestedCount = 0;
        const nestedGmPath = path.join(resolvedAbsPath, '.gitmodules');
        if (resolvedGit.branch !== 'uninitialized' && fs.existsSync(nestedGmPath)) {
            try {
                const ngmRaw = fs.readFileSync(nestedGmPath, 'utf8');
                const matches = ngmRaw.match(/\[submodule\s+"[^"]+"\]/g);
                nestedCount = matches ? matches.length : 0;
            } catch {}
        }

        subs.push({
            name,
            path: subPath,
            absPath: resolvedAbsPath,
            url,
            owner: ownerRaw,
            isOwned,
            branch: resolvedGit.branch,
            trackedBranch,
            sha: resolvedGit.sha,
            pinnedSha,
            pinSynced: resolvedGit.branch !== 'uninitialized' && pinnedSha !== '—' ? resolvedGit.sha === pinnedSha : null,
            ahead: div ? div.ahead : null,
            behind: div ? div.behind : null,
            originRef: div ? div.originRef : null,
            actionableBranches: div ? div.actionableBranches : null,
            actionableSample: div ? div.actionableSample : [],
            nestedCount,
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
        controlCenterVersion: '2.3.0',
        branch: rootGit.branch,
        sha: rootGit.sha,
        workspaceRoot: WORKSPACE_ROOT,
        orchestratorPid: process.pid,
        priority: 'BelowNormal',
        submodulesTotal: submodules.length,
        submodulesInitialized: initializedCount,
        submodulesNestedTotal: submodules.reduce((acc, s) => acc + (s.nestedCount || 0), 0),
        submodulesPinDrifted: submodules.filter((s) => s.pinSynced === false).length,
        submodulesDiverged: submodules.filter((s) => (s.ahead || 0) > 0 || (s.behind || 0) > 0).length,
        divergenceScan: divergenceScanState,
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
        const child = spawn(exePath, svc.runArgs || [], {
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

app.post('/api/submodules/refresh-divergence', (req, res) => {
    refreshGitDivergenceSnapshot();
    res.json({ ok: true, state: divergenceScanState });
});

async function getRepoSubmodulePinsAsync(repoDir) {
    const pinMap = new Map();
    const out = await execGitAsync(repoDir, ['ls-tree', 'HEAD'], 3000);
    if (!out.ok || !out.stdout) return pinMap;
    for (const line of out.stdout.split(/\r?\n/)) {
        if (!line.startsWith('160000 ')) continue;
        const tabIdx = line.indexOf('\t');
        if (tabIdx === -1) continue;
        const sha = line.slice(0, tabIdx).split(/\s+/)[2] || '';
        const subPath = line.slice(tabIdx + 1).trim();
        if (sha && subPath) pinMap.set(subPath, sha.slice(0, 8));
    }
    return pinMap;
}

app.get('/api/submodules/nested', async (req, res) => {
    const targetRel = String(req.query.path || '').trim();
    const rootSubs = parseSubmodulesFast();
    const rootSub = rootSubs.find((s) => s.path === targetRel);
    if (!rootSub) {
        return res.status(404).json({ error: 'Root submodule not found' });
    }

    const items = [];
    const visited = new Set();
    const maxDepth = 4;

    async function walkNested(parentAbs, relPrefix, depth) {
        if (depth > maxDepth || !fs.existsSync(parentAbs)) return;
        let realParent = parentAbs;
        try { realParent = fs.realpathSync(parentAbs); } catch {}
        const visitKey = `${realParent.toLowerCase()}::${depth}`;
        if (visited.has(visitKey)) return;
        visited.add(visitKey);

        const gmPath = path.join(parentAbs, '.gitmodules');
        if (!fs.existsSync(gmPath)) return;
        let raw = '';
        try { raw = fs.readFileSync(gmPath, 'utf8'); } catch { return; }
        const pinMap = await getRepoSubmodulePinsAsync(parentAbs);
        const blocks = raw.split(/\[submodule\s+"([^"]+)"\]/g);

        for (let i = 1; i < blocks.length; i += 2) {
            const name = blocks[i];
            const body = blocks[i + 1] || '';
            const pMatch = body.match(/^\s*path\s*=\s*(.+)$/m);
            const uMatch = body.match(/^\s*url\s*=\s*(.+)$/m);
            const childRel = pMatch ? pMatch[1].trim() : name;
            const url = uMatch ? uMatch[1].trim() : '';
            const childAbs = path.join(parentAbs, childRel);
            const displayPath = relPrefix ? `${relPrefix}/${childRel}` : childRel;
            const ownerRaw = (url.split('/')[3] || 'external').replace(/\.git$/i, '');
            const isOwned = OWNED_ORGS.has(ownerRaw.toLowerCase());
            const gitInfo = readGitHeadFast(childAbs);
            const pinnedSha = pinMap.get(childRel) || '—';
            const initialized = gitInfo.branch !== 'uninitialized';

            const entry = {
                name,
                path: displayPath,
                childRel,
                absPath: childAbs,
                depth,
                url,
                owner: ownerRaw,
                isOwned,
                branch: gitInfo.branch,
                sha: gitInfo.sha,
                pinnedSha,
                pinSynced: initialized && pinnedSha !== '—' ? gitInfo.sha === pinnedSha : null,
                initialized,
                ahead: null,
                behind: null,
                originRef: null,
                actionableBranches: 0,
                actionableSample: []
            };
            items.push(entry);

            if (initialized && items.length < 260) {
                // eslint-disable-next-line no-await-in-loop
                await walkNested(childAbs, displayPath, depth + 1);
            }
        }
    }

    await walkNested(rootSub.absPath, '', 1);

    // Run bounded parallel divergence & unmerged-branch scan across initialized nested repos (up to 72 per request)
    const initQueue = items.filter((it) => it.initialized).slice(0, 72);
    let qIdx = 0;
    const workers = Array.from({ length: 8 }, async () => {
        while (qIdx < initQueue.length) {
            const cur = initQueue[qIdx];
            qIdx += 1;
            const cands = [];
            if (cur.branch && cur.branch !== 'detached' && cur.branch !== 'unknown') {
                cands.push(`origin/${cur.branch}`);
            }
            for (const fb of ['origin/main', 'origin/master', 'origin/develop', 'origin/release']) {
                if (!cands.includes(fb)) cands.push(fb);
            }
            for (const ref of cands) {
                // eslint-disable-next-line no-await-in-loop
                const lr = await execGitAsync(cur.absPath, ['rev-list', '--left-right', '--count', `${ref}...HEAD`], 3000);
                if (lr.ok && lr.stdout) {
                    const pts = lr.stdout.split(/\s+/);
                    if (pts.length === 2) {
                        cur.behind = parseInt(pts[0], 10) || 0;
                        cur.ahead = parseInt(pts[1], 10) || 0;
                        cur.originRef = ref;
                        break;
                    }
                }
            }
            if (cur.isOwned) {
                // eslint-disable-next-line no-await-in-loop
                const um = await execGitAsync(
                    cur.absPath,
                    ['for-each-ref', '--format=%(refname:short)|%(authorname)|%(authoremail)', '--no-merged=HEAD', 'refs/remotes/origin/'],
                    3000
                );
                if (um.ok && um.stdout) {
                    const matched = [];
                    for (const ln of um.stdout.split(/\r?\n/)) {
                        const [bRaw, aName = '', aMail = ''] = ln.split('|');
                        const b = (bRaw || '').trim();
                        if (!b || b === 'origin/HEAD' || b === 'origin' || b === cur.originRef || b === 'origin/gh-pages') continue;
                        if (b.includes('dependabot/') || b.startsWith('origin/upstream/')) continue;
                        if (ACTIONABLE_BRANCH_RE.test(b) || OWNED_AUTHOR_RE.test(`${aName} ${aMail}`)) {
                            matched.push(b.replace(/^origin\//, ''));
                        }
                    }
                    cur.actionableBranches = matched.length;
                    cur.actionableSample = matched.slice(0, 5);
                }
            }
        }
    });
    await Promise.all(workers);

    return res.json({
        parent: {
            path: rootSub.path,
            branch: rootSub.branch,
            sha: rootSub.sha,
            owner: rootSub.owner,
            url: rootSub.url
        },
        totalNested: items.length,
        initializedNested: items.filter((i) => i.initialized).length,
        divergedNested: items.filter((i) => (i.ahead || 0) > 0 || (i.behind || 0) > 0).length,
        driftedNested: items.filter((i) => i.pinSynced === false).length,
        items
    });
});

app.get('/api/session-bus', async (req, res) => {
    const includeTests = req.query.includeTests === '1';
    const hnBase = (process.env.HYPERNEXUS_URL || 'http://127.0.0.1:7778').replace(/\/$/, '');
    const payload = await fetchJsonLocal(`${hnBase}/api/memory/scratchpad/get`, 1500);
    if (!payload || typeof payload !== 'object') {
        return res.json({ online: false, sessions: [], messages: [], totalRawSessions: 0 });
    }
    const map = payload.scratchpad || (payload.data && payload.data.scratchpad) || {};
    const rawSessions = [];
    const rawMessages = [];

    for (const [k, v] of Object.entries(map)) {
        if (typeof v !== 'string') continue;
        if (k.startsWith('bus:reg:')) {
            try { rawSessions.push(JSON.parse(v)); } catch {}
        } else if (k.startsWith('bus:msg:') || k.startsWith('bus:out:')) {
            try {
                const parsed = JSON.parse(v);
                parsed.kind = k.startsWith('bus:out:') ? 'reply' : 'msg';
                rawMessages.push(parsed);
            } catch {}
        }
    }

    const isTestNoise = (s) => /^(xop-|bus-selftest-|w-spark-|w-wonder-|coord-mwh)/i.test(String(s || ''));
    const sessions = rawSessions
        .filter((s) => includeTests || (!isTestNoise(s.id) && !/test/i.test(s.harness || '')))
        .sort((a, b) => (b.ts || 0) - (a.ts || 0));

    const messages = rawMessages
        .filter((m) => includeTests || (!isTestNoise(m.from) && !isTestNoise(m.to)))
        .sort((a, b) => (b.ts || 0) - (a.ts || 0))
        .slice(0, 40);

    return res.json({
        online: true,
        sessions,
        messages,
        totalRawSessions: rawSessions.length
    });
});

app.post('/api/session-bus/send', async (req, res) => {
    const { from = 'control-center-ui', to = '*', text = '' } = req.body || {};
    const cleanText = String(text).trim();
    if (!cleanText) return res.status(400).json({ error: 'Message text is required' });
    const hnBase = (process.env.HYPERNEXUS_URL || 'http://127.0.0.1:7778').replace(/\/$/, '');
    const msgId = `bm-${Date.now().toString(36)}`;
    const record = { msg: msgId, from: String(from).trim() || 'control-center-ui', to: String(to).trim() || '*', text: cleanText, ts: Date.now() };
    const r = await postJsonLocal(`${hnBase}/api/memory/scratchpad/set`, {
        key: `bus:msg:${msgId}`,
        value: JSON.stringify(record)
    }, 3000);
    if (r.status !== 200) {
        return res.status(502).json({ error: 'HyperNexus :7778 scratchpad unreachable' });
    }
    return res.json({ ok: true, msg: msgId, record });
});

app.get('/api/session-bus/handover', async (req, res) => {
    const hnBase = (process.env.HYPERNEXUS_URL || 'http://127.0.0.1:7778').replace(/\/$/, '');
    const payload = await fetchJsonLocal(`${hnBase}/api/memory/scratchpad/get`, 1500);
    const map = (payload && (payload.scratchpad || (payload.data && payload.data.scratchpad))) || {};
    let latest = null;
    if (typeof map['bus:ledger:latest'] === 'string') {
        try { latest = JSON.parse(map['bus:ledger:latest']); } catch {}
    }
    res.json({ online: Boolean(payload), ledger: latest });
});

app.post('/api/session-bus/handover', async (req, res) => {
    const { from = 'control-center-ui', reason = 'CHECKPOINT', note = '' } = req.body || {};
    let version = 'unknown';
    try { version = fs.readFileSync(path.join(WORKSPACE_ROOT, 'VERSION'), 'utf8').trim(); } catch {}
    const rootGit = readGitHeadFast(WORKSPACE_ROOT);
    const subs = parseSubmodulesFast();
    const goStates = await getGoServiceStates();
    const ledger = {
        kind: 'HANDOVER_LEDGER',
        from: String(from).trim() || 'control-center-ui',
        reason: String(reason).trim() || 'CHECKPOINT',
        version,
        controlCenterVersion: '2.3.0',
        rootBranch: rootGit.branch,
        rootSha: rootGit.sha,
        submodulesInitialized: subs.filter((s) => s.branch !== 'uninitialized').length,
        submodulesTotal: subs.length,
        submodulesNestedTotal: subs.reduce((acc, s) => acc + (s.nestedCount || 0), 0),
        submodulesPinDrifted: subs.filter((s) => s.pinSynced === false).length,
        goServicesBuilt: goStates.filter((g) => g.built).length,
        goServicesTotal: goStates.length,
        note: String(note || '').trim(),
        ts: Date.now(),
        isoTime: new Date().toISOString()
    };

    const hnBase = (process.env.HYPERNEXUS_URL || 'http://127.0.0.1:7778').replace(/\/$/, '');
    const msgId = `bm-${Date.now().toString(36)}`;
    const text = `[HANDOVER_${ledger.reason}] ${ledger.version} @ ${ledger.rootSha} (${ledger.submodulesInitialized}/${ledger.submodulesTotal} root + ${ledger.submodulesNestedTotal} nested submodules, ${ledger.goServicesBuilt}/${ledger.goServicesTotal} Go built, ${ledger.submodulesPinDrifted} drifted pins)${ledger.note ? ' — ' + ledger.note : ''}`;
    const [rLedger, rMsg] = await Promise.all([
        postJsonLocal(`${hnBase}/api/memory/scratchpad/set`, { key: 'bus:ledger:latest', value: JSON.stringify(ledger) }, 3000),
        postJsonLocal(`${hnBase}/api/memory/scratchpad/set`, {
            key: `bus:msg:${msgId}`,
            value: JSON.stringify({ msg: msgId, from: ledger.from, to: '*', text, ts: ledger.ts })
        }, 3000)
    ]);
    if (rLedger.status !== 200 || rMsg.status !== 200) {
        return res.status(502).json({ error: 'HyperNexus :7778 scratchpad unreachable' });
    }
    return res.json({ ok: true, msg: msgId, ledger });
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
    console.log(`Omni-Workspace Control Center v2.3.0 running at http://localhost:${PORT} (Priority: BelowNormal)`);
    setTimeout(() => { refreshGitDivergenceSnapshot(); }, 1200);
    const divTimer = setInterval(() => { refreshGitDivergenceSnapshot(); }, 90000);
    if (typeof divTimer.unref === 'function') divTimer.unref();
});

module.exports = { app, server };
