#!/usr/bin/env python3
"""Merge origin default into the 3 push-failed bobmani-tree repos and push."""
import subprocess
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")
REPOS = [
    ROOT / "bobmani" / "hymnmania" / "submodules" / "ableton_psytrance_hymn_creator",
    ROOT / "bobmani" / "hymnmania",
    ROOT / "bobmani" / "linthesia",
]

def run(cmd, cwd, timeout=240):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception as e:
        return -2, f"TIMEOUT {e}"

for rp in REPOS:
    name = str(rp.relative_to(ROOT))
    rc, branch = run("git rev-parse --abbrev-ref HEAD", rp, 15)
    branch = branch.strip()
    run("git fetch origin", rp, 180)
    rc, out = run(f"git merge --no-ff origin/{branch} -m \"merge: origin/{branch} sync (re-pin)\"", rp, 240)
    if rc != 0:
        # resolve gitlink conflicts by keeping our staged pins: abort, then merge -X ours
        run("git merge --abort", rp, 30)
        rc, out = run(f"git merge --no-ff -X ours origin/{branch} -m \"merge: origin/{branch} sync (re-pin, local-wins)\"", rp, 240)
    if rc != 0:
        run("git merge --abort", rp, 30)
        print(f"MERGE_FAIL {name}: {out[-250:]}", flush=True)
        continue
    rc, out = run(f"git push origin {branch}", rp, 240)
    rc2, head = run("git rev-parse HEAD", rp, 15)
    print(f"{'PUSHED' if rc==0 else 'PUSH_FAIL'} {name} {branch} {head.strip()[:12]} {out[-150:] if rc!=0 else ''}", flush=True)
print("PUSHFAIL_FIX_DONE")
