#!/usr/bin/env python3
"""Apply fix_bobfilez_audit.json repins to bobfilez main via plumbing, push."""
import subprocess, os, sys, json, tempfile
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")
REPO = ROOT / "bobfilez"

def run(cmd, cwd, env=None, timeout=300):
    e = dict(os.environ)
    if env:
        e.update(env)
    p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True, env=e)
    out = (p.stdout or "").strip()
    if p.returncode != 0:
        print(f"FAIL: {cmd}\n{out}\n{(p.stderr or '')[:500]}")
        sys.exit(1)
    return out

def main():
    data = json.loads((ROOT / "fix_bobfilez_audit.json").read_text(encoding="utf-8"))
    repins = data["repins"]
    print(f"applying {len(repins)} repins")
    run("git fetch origin -q", REPO)
    base = run("git rev-parse origin/main", REPO)
    with tempfile.TemporaryDirectory() as d:
        env = {"GIT_INDEX_FILE": str(Path(d) / "index")}
        run("git read-tree origin/main", REPO, env)
        for r in repins:
            run(f"git update-index --cacheinfo 160000,{r['to']},{r['path']}", REPO, env)
        tree = run("git write-tree", REPO, env)
        commit = run(f'git commit-tree {tree} -p {base} -m "fix: re-pin 163 submodules to published commits (Jules recursive clone)"', REPO, env)
    out = run(f"git push origin {commit}:main", REPO)
    print(out)
    print(f"BOBFILEZ_REPIN {base[:10]} -> {commit}")

if __name__ == "__main__":
    main()
