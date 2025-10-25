#!/usr/bin/env node
'use strict';
const { spawn } = require('node:child_process');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');

function log(msg) {
  // Prefer explicit path from env; otherwise fall back to a safe TEMP file
  let fp = process.env.MCP_WRAPPER_LOG;
  if (!fp || fp.length === 0) {
    try {
      fp = path.join(os.tmpdir(), 'mcp_seq_wrapper.log');
    } catch (e) {
      return; // If even TEMP is unavailable, silently skip logging
    }
  }
  try {
    fs.appendFileSync(fp, new Date().toISOString() + ' ' + String(msg) + os.EOL, { encoding: 'utf8' });
  } catch (e) {
    // ignore logging failures
  }
}

function q(arg) {
  if (arg == null) return '';
  const s = String(arg);
  if (s.length === 0) return '""';
  // For cmd.exe, quote with double-quotes and escape embedded quotes by doubling them.
  if (/[ \t"&<>^]/.test(s)) {
    return '"' + s.replace(/"/g, '""') + '"';
  }
  return s;
}

function makeCmdString(npxPath, pkg, extra) {
  return [q(npxPath), '-y', pkg, ...extra.map(q)].join(' ');
}

function startChild(pkg, extra) {
  const npxPath = process.env.NPX_CMD || 'C:\\\\Program Files\\\\nodejs\\\\npx.cmd';

  // Build a single shell command line; let Node spawn with shell:true so cmd.exe is handled by Node.
  // Quote npx path explicitly; quote args as needed.
  const argsPart = [pkg, ...extra].map(q).join(' ');
  const cmdLine = `"${npxPath}" -y ${argsPart}`.trim();

  log(`node.version=${process.version}`);
  log(`spawn.shell=true cmdLine=${cmdLine}`);
  log(`env.NPX_CMD=${process.env.NPX_CMD || ''}`);

  const child = spawn(cmdLine, {
    shell: true,
    stdio: ['pipe','pipe','inherit'],
    windowsHide: true
  });

  return { child, npxPath, cmdString: cmdLine };
}

// Robust, case-insensitive header detection with BOM/whitespace tolerance
function findHandshakeStart(buffer) {
  const txt = buffer.toString('latin1'); // headers are ASCII
  const ltxt = txt.toLowerCase();
  const cl = ltxt.indexOf('content-length:');
  const ct = ltxt.indexOf('content-type:');
  let idx = -1;
  if (cl >= 0 && ct >= 0) idx = Math.min(cl, ct);
  else idx = (cl >= 0 ? cl : ct);

  if (idx >= 0) return Buffer.byteLength(txt.slice(0, idx), 'latin1');

  // Some servers omit headers and start directly with JSON
  const brace = buffer.indexOf(123); // '{'
  if (brace !== -1) return brace;

  // Detect header terminator
  const sep = ltxt.indexOf('\r\n\r\n');
  if (sep >= 0) {
    const firstNonWs = ltxt.search(/[^\r\n\t ]/);
    return firstNonWs >= 0 ? firstNonWs : sep;
  }

  return -1;
}

function stdoutFilter(child) {
  let started = false;
  let buffer = Buffer.alloc(0);

  child.stdout.on('data', (chunk) => {
    log(`stdout.chunk.bytes=${chunk.length}`);
    if (started) {
      process.stdout.write(chunk);
      return;
    }
    buffer = Buffer.concat([buffer, chunk]);
    const idx = findHandshakeStart(buffer);
    if (idx !== -1) {
      started = true;
      const out = buffer.slice(idx);
      log(`handshake.start.emitted_bytes=${out.length}`);
      process.stdout.write(out);
      buffer = Buffer.alloc(0);
    } else if (buffer.length > 16384) {
      buffer = buffer.slice(-16384);
    }
  });

  child.stdout.on('end', () => {
    log(`stdout.end started=${started} buffered_bytes=${buffer.length}`);
    buffer = Buffer.alloc(0);
  });
}

function wireIO(child) {
  try {
    process.stdin.on('data', (d) => {
      log(`stdin.chunk.bytes=${d.length}`);
    });
  } catch {}
  process.stdin.pipe(child.stdin);
  child.stdin.on('error', (e) => { log(`stdin.error=${String(e)}`); });

  stdoutFilter(child);

  child.on('exit', (code, signal) => {
    log(`child.exit code=${code} signal=${signal || ''}`);
    if (signal) {
      try { process.kill(process.pid, signal); } catch {}
      process.exit(128);
    } else {
      process.exit(code == null ? 0 : code);
    }
  });

  child.on('error', (err) => {
    log(`child.error ${String(err)}`);
    try { process.stderr.write(String(err) + '\\n'); } catch {}
    process.exit(127);
  });

  ['SIGINT','SIGTERM','SIGHUP'].forEach(sig => {
    process.on(sig, () => { log(`signal.forward ${sig}`); try { child.kill(sig); } catch {} });
  });
}

function main() {
  const argv = process.argv.slice(2);
  if (argv.length < 1) {
    process.stderr.write('Usage: node mcp_npx_quiet.js <package> [args...]\\n');
    process.exit(64);
    return;
  }
  const pkg = argv[0];
  const extra = argv.slice(1);
  const { child } = startChild(pkg, extra);
  wireIO(child);
}

main();