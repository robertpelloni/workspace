#!/usr/bin/env python3
"""Scan all submodules for broken references (commits that don't exist in remote)."""
import subprocess
import shlex
from pathlib import Path

WORKSPACE = Path(r"C:\Users\hyper\workspace")

def run(args, cwd=None, timeout=30):
    if isinstance(args, str):
        args = shlex.split(args)
    try:
        r = subprocess.run(args, capture_output=True, text=True, cwd=cwd, timeout=timeout)
        return r.returncode == 0, r.stdout.strip(), r.stderr.strip()
    except (subprocess.TimeoutExpired, OSError):
        return False, "", "error"

def get_submodules():
    gitmodules = WORKSPACE / ".gitmodules"
    subs = []
    try:
        with open(gitmodules, encoding="utf-8") as f:
            for line in f:
                line = line.strip()
                if line.startswith("path"):
                    subs.append(line.split("=", 1)[1].strip())
    except OSError:
        pass
    return subs

def check_submodule(sub_path):
    """Check if a submodule's HEAD commit exists in its remote."""
    full_path = str(WORKSPACE / sub_path)
    if not (WORKSPACE / sub_path).exists():
        return None
    
    ok, _, _ = run(["git", "rev-parse", "--git-dir"], cwd=full_path)
    if not ok:
        return None
    
    # Get the commit the parent repo expects
    ok, expected, _ = run(["git", "ls-tree", "HEAD", sub_path], cwd=str(WORKSPACE))
    if not ok or not expected:
        return None
    
    # Extract commit hash from ls-tree output
    parts = expected.split()
    if len(parts) < 3:
        return None
    commit_hash = parts[2]
    
    # Check if this commit exists in the remote
    ok, _, err = run(["git", "cat-file", "-t", commit_hash], cwd=full_path, timeout=10)
    if ok:
        return None  # Commit exists locally
    
    # Try fetching and checking again
    run(["git", "fetch", "origin"], cwd=full_path, timeout=60)
    ok, _, _ = run(["git", "cat-file", "-t", commit_hash], cwd=full_path, timeout=10)
    if ok:
        return None  # Commit exists after fetch
    
    return commit_hash

def main():
    subs = get_submodules()
    print(f"Scanning {len(subs)} submodules for broken references...")
    
    broken = []
    for sub in subs:
        bad_commit = check_submodule(sub)
        if bad_commit:
            print(f"  BROKEN: {sub} - commit {bad_commit[:12]} not found")
            broken.append((sub, bad_commit))
    
    if broken:
        print(f"\nFound {len(broken)} broken submodule references:")
        for sub, commit in broken:
            print(f"  {sub}: {commit}")
    else:
        print("\nAll submodule references are valid!")

if __name__ == "__main__":
    main()
