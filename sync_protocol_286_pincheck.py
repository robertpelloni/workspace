#!/usr/bin/env python3
"""Check staged submodule pointers point at commits published on their origin (avoid stale pins)."""
import subprocess
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")

def run(cmd, cwd, timeout=60):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception:
        return -2, "TIMEOUT"

def main():
    rc, out = run("git diff --cached --name-only", ROOT, 60)
    staged = [l.strip() for l in out.splitlines() if l.strip()]
    bad = []
    for rel in staged:
        p = ROOT / rel
        if not (p / ".git").exists():
            continue
        rc2, head = run("git rev-parse HEAD", p, 15)
        head = head.strip()
        if not head:
            continue
        # is HEAD reachable from any origin branch?
        rc3, out3 = run(f"git branch -r --contains {head}", p, 30)
        if rc3 != 0 or not out3.strip():
            bad.append((rel, head[:12]))
            print(f"UNPUBLISHED PIN {rel} {head[:12]}", flush=True)
    print(f"\nPINCHECK DONE: {len(bad)} unpublished", flush=True)
    Path("sync_protocol_286_unpublished.txt").write_text("\n".join(f"{a} {b}" for a, b in bad), encoding="utf-8")

if __name__ == "__main__":
    main()





