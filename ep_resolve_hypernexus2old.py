#!/usr/bin/env python3
"""Batch-resolve all HyperNexus2old add/add conflicts: take ours (587 local commits)."""
import subprocess
from pathlib import Path

REPO = Path(r"C:\Users\hyper\workspace\HyperNexus2old")

def run(cmd, timeout=60):
    p = subprocess.run(cmd, cwd=str(REPO), capture_output=True, text=True, timeout=timeout, shell=True)
    return p.returncode, (p.stdout or "") + (p.stderr or "")

rc, out = run("git diff --name-only --diff-filter=U")
conflicts = [l.strip() for l in out.splitlines() if l.strip()]
print(f"Found {len(conflicts)} conflicted files")

if not conflicts:
    print("No conflicts remaining")
else:
    # Batch checkout --ours
    batch_size = 50
    for i in range(0, len(conflicts), batch_size):
        batch = conflicts[i:i+batch_size]
        quoted = " ".join(f'"{f}"' for f in batch)
        rc, o = run(f"git checkout --ours {quoted}", timeout=120)
        rc, o = run(f"git add {quoted}", timeout=120)
        print(f"  resolved batch {i//batch_size + 1} ({len(batch)} files)")

rc, out = run("git diff --name-only --diff-filter=U")
remaining = [l.strip() for l in out.splitlines() if l.strip()]
print(f"Remaining conflicts: {len(remaining)}")
if remaining:
    for f in remaining[:5]:
        print(f"  {f}")
else:
    print("All resolved - ready to commit")
