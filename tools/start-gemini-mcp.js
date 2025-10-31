#!/usr/bin/env node
const fs = require('fs');
const path = require('path');
const { spawn } = require('child_process');

function loadDotEnv(dotenvPath) {
  try {
    if (!fs.existsSync(dotenvPath)) return;
    const content = fs.readFileSync(dotenvPath, 'utf8');
    for (const rawLine of content.split(/\r?\n/)) {
      const line = rawLine.trim();
      if (!line || line.startsWith('#')) continue;
      const idx = line.indexOf('=');
      if (idx === -1) continue;
      const key = line.slice(0, idx).trim();
      let value = line.slice(idx + 1).trim();
      if ((value.startsWith('"') && value.endsWith('"')) || (value.startsWith('\'') && value.endsWith('\''))) {
        value = value.slice(1, -1);
      }
      if (!(key in process.env)) process.env[key] = value;
    }
  } catch (err) {
    console.error('[gemini-mcp wrapper] Failed to load .env:', err.message);
  }
}

(function main() {
  // Load .env from repository/workspace root when present
  const cwdEnv = process.cwd();
  const dotenvPath = path.resolve(cwdEnv, '.env');
  loadDotEnv(dotenvPath);

  // Determine platform-specific executable
  const isWindows = process.platform === 'win32';
  const exe = isWindows ? 'gemini-mcp.cmd' : 'gemini-mcp';

  const child = spawn(exe, process.argv.slice(2), {
    stdio: 'inherit',
    shell: true,
  });

  child.on('exit', (code, signal) => {
    if (signal) {
      process.kill(process.pid, signal);
    } else {
      process.exit(code ?? 0);
    }
  });
})();


