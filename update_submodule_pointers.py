#!/usr/bin/env python3
"""Update all submodule pointers to latest remote HEAD after merges."""
import subprocess
import shlex
from pathlib import Path

WORKSPACE = Path(r"C:\Users\hyper\workspace")

def run(args, cwd=None, timeout=60):
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

def get_default_branch(repo_path):
    ok, out, _ = run(["git", "symbolic-ref", "refs/remotes/origin/HEAD"], cwd=repo_path)
    if ok and out:
        return out.split("/")[-1]
    ok, _, _ = run(["git", "rev-parse", "--verify", "origin/main"], cwd=repo_path)
    if ok:
        return "main"
    ok, _, _ = run(["git", "rev-parse", "--verify", "origin/master"], cwd=repo_path)
    if ok:
        return "master"
    return "main"

def main():
    subs = get_submodules()
    print(f"Found {len(subs)} submodules")
    
    updated = 0
    for sub in subs:
        full_path = str(WORKSPACE / sub)
        if not (WORKSPACE / sub).exists():
            continue
        
        ok, _, _ = run(["git", "rev-parse", "--git-dir"], cwd=full_path)
        if not ok:
            continue
        
        # Fetch and checkout latest
        run(["git", "fetch", "origin"], cwd=full_path, timeout=60)
        branch = get_default_branch(full_path)
        
        # Get remote HEAD
        ok, remote_sha, _ = run(["git", "rev-parse", f"origin/{branch}"], cwd=full_path)
        if not ok:
            continue
        
        # Get current HEAD
        ok, local_sha, _ = run(["git", "rev-parse", "HEAD"], cwd=full_path)
        if not ok:
            continue
        
        if remote_sha != local_sha:
            # Update to latest
            ok, _, _ = run(["git", "checkout", branch], cwd=full_path)
            if not ok:
                ok, _, _ = run(["git", "checkout", "-b", branch, f"origin/{branch}"], cwd=full_path)
            run(["git", "reset", "--hard", f"origin/{branch}"], cwd=full_path, timeout=30)
            print(f"  UPDATED: {sub} ({branch})")
            updated += 1
    
    print(f"\nUpdated {updated} submodule pointers")

if __name__ == "__main__":
    main()
