#!/usr/bin/env python3
"""Audit Jules stale-pin failures: compare recorded gitlink SHA vs remote-advertised refs."""
import subprocess
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")

CASES = [
    ("f-zerox", "tools/asm-differ", "2bf661ca52a9dc8f73876daeca68c6b4130940ae"),
    ("geiss", "aios", "200a29131b72ff87c3464bdb53b5b554f6371958"),
    ("hyperharness", "adrenaline", "c341e2700509e9591349d763ac0702e661e31671"),
    ("itgmania", "Themes/Simply-Love-SM5", "9ccc8dca9032e74dfd1889610ab447b3b1898e7c"),
    ("bobtorrent", "bobcoin", "09c5012d0eb305b80d909b2d4a376897a63091e6"),
    ("okgame", "lib/libmidi", None),
    ("bobsaver", "JWildfire", "244a0d1f482359317b41cc6db52bc144c06e41de"),
    ("superdawmcp", "third_party/dawpilot-mcp", None),
    ("linthesia", "pianogame", "fc1ec8d36552654d8f1f6f8d53dcb912c5a5f2af"),
]

def run(cmd, cwd=None, timeout=60):
    try:
        p = subprocess.run(cmd, cwd=str(cwd) if cwd else None, capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception as e:
        return -2, f"TIMEOUT {e}"

for parent, sub, jules_sha in CASES:
    ppath = ROOT / parent
    print(f"\n=== {parent} :: {sub} (jules pin {str(jules_sha)[:12]})")
    if not (ppath / ".git").exists():
        print("  PARENT NOT A REPO locally"); continue
    rc, out = run(f"git ls-tree HEAD {sub}", ppath, 30)
    print(f"  gitlink: {out.strip()[:90]}")
    rc, url = run(f"git config --file .gitmodules --get submodule.{sub}.url", ppath, 15)
    url = url.strip()
    print(f"  url: {url}")
    if not url:
        # try submodule name lookup by path
        rc, out2 = run("git config --file .gitmodules --list", ppath, 15)
        for line in out2.splitlines():
            if sub in line:
                print(f"    cfg: {line.strip()}")
    if url:
        rc, out = run(f"git ls-remote {url} HEAD refs/heads/main refs/heads/master refs/heads/develop", None, 60)
        lines = [l for l in out.splitlines() if l.strip()]
        print(f"  ls-remote rc={rc}:")
        for l in lines[:6]:
            print(f"    {l[:80]}")
        if rc != 0:
            print(f"    ERR: {out[-250:]}")
