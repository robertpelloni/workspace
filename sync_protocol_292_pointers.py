#!/usr/bin/env python3
"""Protocol #292: stage submodule pointers where submodule HEAD is published on its origin."""
import subprocess
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")
NEVER = {"HyperNexus", "HyperNexus2old", "openclaw-config", "unitedbeats_site"}

def run(cmd, cwd, timeout=60):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception:
        return -2, "TIMEOUT"

def main():
    rc, out = run("git config --file .gitmodules --get-regexp path", ROOT, 30)
    paths = []
    for line in out.splitlines():
        parts = line.split(None, 1)
        if len(parts) == 2:
            paths.append(parts[1].strip())
    staged, skipped = [], []
    for rel in paths:
        if rel in NEVER:
            continue
        p = ROOT / rel
        if not (p / ".git").exists():
            continue
        rc, head = run("git rev-parse HEAD", p, 15)
        head = head.strip()
        if not head:
            continue
        rc, recorded = run(f"git ls-tree HEAD -- {rel}", ROOT, 15)
        rec = recorded.split()[2] if len(recorded.split()) >= 3 else ""
        if rec == head:
            continue
        rc, contains = run(f"git branch -r --contains {head}", p, 30)
        if rc != 0 or not contains.strip():
            skipped.append((rel, head[:10]))
            print(f"SKIP unpublished {rel} {head[:10]}", flush=True)
            continue
        rc, _ = run(f"git add -- {rel}", ROOT, 30)
        if rc == 0:
            staged.append(rel)
            print(f"STAGED {rel} {head[:10]}", flush=True)
    print(f"\nPOINTERS: {len(staged)} staged, {len(skipped)} skipped-unpublished")

if __name__ == "__main__":
    main()
