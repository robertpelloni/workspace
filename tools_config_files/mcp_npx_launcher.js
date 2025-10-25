#!/usr/bin/env node
'use strict';
const { spawn } = require('node:child_process');

function q(arg) {
  if (arg == null) return '';
  const s = String(arg);
  if (s.length === 0) return '""';
  if (/[ \t"&|<>^]/.test(s)) {
    return '"' + s.replace(/"/g, '\\"') + '"';
  }
  return s;
}

function main() {
  const argv = process.argv.slice(2);
  if (argv.length < 1) {
    process.stderr.write('Usage: node mcp_npx_launcher.js <package> [args...]\\n');
    process.exit(64);
    return;
  }
  const pkg = argv[0];
  const extra = argv.slice(1);

  const npxPath = process.env.NPX_CMD || 'C:\\\\Program Files\\\\nodejs\\\\npx.cmd';

  // Build a single command string for cmd.exe /c
  const cmdString = [q(npxPath), '-y', pkg, ...extra.map(q)].join(' ');

  // Spawn through cmd.exe to execute the .cmd reliably under CreateProcess
  const child = spawn(process.env.ComSpec || 'C:\\\\Windows\\\\System32\\\\cmd.exe',
    ['/d', '/s', '/c', cmdString],
    {
      stdio: 'inherit',
      windowsHide: true
    });

  child.on('exit', (code, signal) => {
    if (signal) {
      // Map termination signal to non-zero exit
      try { process.kill(process.pid, signal); } catch {}
      process.exit(128);
    } else {
      process.exit(code == null ? 0 : code);
    }
  });

  child.on('error', (err) => {
    try {
      process.stderr.write(String(err) + '\\n');
    } catch {}
    process.exit(127);
  });

  // Forward common signals to child so Codex lifecycle is preserved
  const forward = (sig) => {
    try { child.kill(sig); } catch {}
  };
  ['SIGINT','SIGTERM','SIGHUP'].forEach((sig) => {
    process.on(sig, () => forward(sig));
  });
}

// Do not log anything before the MCP server handshake.
main();