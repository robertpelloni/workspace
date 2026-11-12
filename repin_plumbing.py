#!/usr/bin/env python3
"""Re-pin gitlinks on a repo's remote branch via plumbing (read-tree/commit-tree),
without touching the working tree. Usage:
  repin_plumbing.py <repo_rel> <remote_branch> <message> path=sha [path=sha...]
Pushes the new commit to the same branch name on origin."""
import subprocess, sys, os, tempfile
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")

def run(cmd, cwd, env=None, timeout=300):
    e = dict(os.environ)
    if env:
        e.update(env)
    p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True, env=e)
    out = ((p.stdout or "") + (p.stderr or "")).strip()
    if p.returncode != 0:
        print(f"FAIL: {cmd}\n{out}")
        sys.exit(1)
    return out

def main():
    repo_rel, branch, message = sys.argv[1], sys.argv[2], sys.argv[3]
    pins = dict(kv.split("=", 1) for kv in sys.argv[4:])
    repo = ROOT / repo_rel
    run("git fetch origin -q", repo)
    base = run(f"git rev-parse origin/{branch}", repo)
    print(f"base origin/{branch} = {base}")
    with tempfile.TemporaryDirectory() as d:
        idx = str(Path(d) / "index")
        env = {"GIT_INDEX_FILE": idx}
        run(f"git read-tree origin/{branch}", repo, env)
        for path, sha in pins.items():
            run(f"git update-index --cacheinfo 160000,{sha},{path}", repo, env)
        tree = run("git write-tree", repo, env)
        commit = run(f'git commit-tree {tree} -p {base} -m "{message}"', repo, env)
    print(f"new commit = {commit}")
    out = run(f"git push origin {commit}:{branch}", repo)
    print(out)
    print(f"REPIN_DONE {repo_rel} {branch} {commit}")

if __name__ == "__main__":
    main()
