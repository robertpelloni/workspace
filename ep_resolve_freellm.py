#!/usr/bin/env python3
"""Resolve freellm cherry-pick AA conflicts: real files -> theirs, .pi-lens cache -> drop."""
import subprocess
from pathlib import Path

REPO = Path(r"C:\Users\hyper\workspace\freellm")

def run(cmd, timeout=30):
    p = subprocess.run(cmd, cwd=str(REPO), capture_output=True, text=True, timeout=timeout, shell=True)
    return p.returncode, (p.stdout or "") + (p.stderr or "")

rc, out = run("git status --short")
conflicts = []
for line in out.splitlines():
    if line.startswith("AA ") or line.startswith("UU ") or line.startswith("DD "):
        conflicts.append(line[3:].strip())

print(f"Found {len(conflicts)} conflicted files")

real_files = [f for f in conflicts if not f.startswith(".pi-lens")]
cache_files = [f for f in conflicts if f.startswith(".pi-lens")]

print(f"  real files -> theirs: {real_files}")
print(f"  cache files -> drop: {len(cache_files)}")

for f in real_files:
    rc, o = run(f'git checkout --theirs "{f}"')
    rc, o = run(f'git add "{f}"')
    print(f"  resolved {f}")

for f in cache_files:
    rc, o = run(f'git rm -f --cached "{f}"')
    print(f"  dropped {f}")

rc, out = run("git status --short")
remaining = [l for l in out.splitlines() if l[:2] in ("AA", "UU", "DD", "AU", "UA", "DU", "UD")]
print(f"\nRemaining conflicts: {len(remaining)}")
for l in remaining[:5]:
    print(f"  {l}")

if not remaining:
    print("Ready to cherry-pick --continue")
