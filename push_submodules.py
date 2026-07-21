#!/usr/bin/env python3
"""Push all submodules that have unpulled changes."""
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
    print(f"Checking {len(subs)} submodules for unpulled commits...")
    
    pushed = 0
    for sub in subs:
        full_path = str(WORKSPACE / sub)
        if not (WORKSPACE / sub).exists():
            continue
        
        ok, _, _ = run(["git", "rev-parse", "--git-dir"], cwd=full_path)
        if not ok:
            continue
        
        branch = get_default_branch(full_path)
        
        # Check if local is ahead of remote
        ok, local_sha, _ = run(["git", "rev-parse", f"origin/{branch}"], cwd=full_path)
        if not ok:
            continue
        
        ok, head_sha, _ = run(["git", "rev-parse", "HEAD"], cwd=full_path)
        if not ok:
            continue
        
        if head_sha != local_sha:
            # Check if local has commits not in remote
            ok, ahead, _ = run(["git", "rev-list", "--count", f"origin/{branch}..HEAD"], cwd=full_path)
            try:
                ahead_count = int(ahead) if ahead else 0
            except ValueError:
                ahead_count = 0
            if ok and ahead_count > 0:
                print(f"  PUSH: {sub} ({ahead} commits ahead)")
                ok, _, err = run(["git", "push", "origin", branch], cwd=full_path, timeout=120)
                if ok:
                    print("    OK")
                    pushed += 1
                else:
                    print(f"    FAIL: {err[:100]}")
    
    print(f"\nPushed {pushed} submodules")

if __name__ == "__main__":
    main()
