#!/usr/bin/env python3
"""Fix bcs (bobfilez/libs/btk) external pins: compute published merge-base
targets for bqt-reference/juce/ultimatepp, plumbing-commit on bcs main,
then re-pin libs/btk in bobfilez main."""
import subprocess, os, sys, re, tempfile
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")
BTK = ROOT / "bobfilez" / "libs" / "btk"
BOBFILEZ = ROOT / "bobfilez"

def run(cmd, cwd, env=None, timeout=600, check=True):
    if isinstance(env, int):
        timeout, env = env, None
    e = dict(os.environ)
    if env:
        e.update(env)
    p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True, env=e)
    out = (p.stdout or "").strip()
    if check and p.returncode != 0:
        print(f"FAIL: {cmd}\n{out}\n{(p.stderr or '')[:400]}")
        sys.exit(1)
    return out

def tip(url):
    out = run(f"git ls-remote {url} HEAD", ROOT, 180)
    return out.split()[0]

def mergebase_target(local, recorded, url):
    run("git fetch origin -q --prune", local, timeout=1200)
    t = tip(url)
    rc_mb = subprocess.run(f"git merge-base {recorded} {t}", cwd=str(local), capture_output=True, text=True, shell=True)
    mb = (rc_mb.stdout or "").strip()
    if rc_mb.returncode == 0 and re.fullmatch(r"[0-9a-f]{40}", mb):
        return mb
    return t

def plumbing(repo, branch, pins, message):
    run(f"git fetch origin -q {branch}:refs/remotes/origin/{branch}", repo)
    base = run(f"git rev-parse origin/{branch}", repo)
    with tempfile.TemporaryDirectory() as d:
        env = {"GIT_INDEX_FILE": str(Path(d) / "index")}
        run(f"git read-tree origin/{branch}", repo, env)
        for path, sha in pins.items():
            run(f"git update-index --cacheinfo 160000,{sha},{path}", repo, env)
        tree = run("git write-tree", repo, env)
        commit = run(f'git commit-tree {tree} -p {base} -m "{message}"', repo, env)
    run(f"git push origin {commit}:{branch}", repo)
    print(f"{repo.name} {branch}: {base[:10]} -> {commit[:10]}")
    return commit

def main():
    pins = {
        "external/bqt-reference": mergebase_target(BTK / "external" / "bqt-reference", "94501ec824d355fd0f8b57c8ecd21166b419837b", "https://github.com/robertpelloni/bqt"),
        "external/juce": mergebase_target(BTK / "external" / "juce", "abd9515a7a1591f2f2823608a6053bf3c2f90b58", "https://github.com/juce-framework/JUCE"),
        "external/ultimatepp": mergebase_target(BTK / "external" / "ultimatepp", "b337b159fccf54ef282ee20ee8c75689124b73e7", "https://github.com/ultimatepp/ultimatepp"),
    }
    print(pins)
    bcs_commit = plumbing(BTK, "master", pins, "fix: re-pin externals to published commits (Jules recursive clone)")
    bf_commit = plumbing(BOBFILEZ, "main", {"libs/btk": bcs_commit}, "fix: re-pin libs/btk (externals fixed)")
    print(f"BCS={bcs_commit}")
    print(f"BOBFILEZ={bf_commit}")

if __name__ == "__main__":
    main()

