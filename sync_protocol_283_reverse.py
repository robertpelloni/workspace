#!/usr/bin/env python3
"""Protocol #281 reverse: merge updated default back into retained feature branches (cherry+ >= 10)."""
import subprocess
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")
JOBS = [
    ("veilid_reddit_facebook", "main", "jules-scaffold-0.1.0-18345075036601368068"),
    ("bobmani/itgmania", "main", "jules-12512815185672744343-3c9d3dde"),
]

def run(cmd, cwd, timeout=240):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception as e:
        return -2, f"TIMEOUT {e}"

for rel, default, branch in JOBS:
    path = ROOT / rel
    run("git fetch origin --prune --quiet", path, 120)
    rc, out = run(f"git checkout {branch}", path, 60)
    if rc != 0:
        print(f"REV CHECKOUTFAIL {rel} {branch}: {out[-200:]}", flush=True)
        continue
    rc, out = run(f"git merge --no-ff {default} -m \"merge: {default} into {branch} (Protocol #281 reverse)\"", path, 240)
    if rc != 0:
        run("git merge --abort", path, 30)
        print(f"REV CONFLICT {rel} {branch} (retained, no reverse)", flush=True)
        run(f"git checkout {default}", path, 60)
        continue
    rc, out = run(f"git push origin {branch}", path, 180)
    print(f"REV {'PUSHED' if rc == 0 else 'PUSHFAIL'} {rel} {branch}", flush=True)
    run(f"git checkout {default}", path, 60)
print("REVERSE DONE")

