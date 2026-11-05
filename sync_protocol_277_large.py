#!/usr/bin/env python3
import subprocess
def run(cmd, timeout=120):
    p = subprocess.run(cmd, shell=True, capture_output=True, text=True, timeout=timeout)
    return p.stdout
out = run("git diff-tree -r --no-commit-id HEAD")
big = []
for line in out.splitlines():
    parts = line.split("\t")
    if len(parts) < 2:
        continue
    meta = parts[0].split()
    if len(meta) < 4 or meta[0].endswith("160000"):
        continue
    sha = meta[3]
    if sha == "0" * 40:
        continue
    sz = run(f"git cat-file -s {sha}", 30).strip()
    try:
        n = int(sz)
    except Exception:
        continue
    if n > 20_000_000:
        big.append((n, parts[1]))
for n, f in sorted(big, reverse=True):
    print(f"{n/1e6:.1f} MB  {f}")
print("LARGE DONE", len(big))
