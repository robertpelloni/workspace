#!/usr/bin/env python3
"""Force-update ALL submodule pointers to their remote branch HEADs across all repos."""

import subprocess
import os

REPOS = [
    ("C:/Users/hyper/workspace/bobmani/itgmania", "release"),
    ("C:/Users/hyper/workspace/bg/bobsgameonlinejava", "main"),
    ("C:/Users/hyper/workspace/bobfilez", "main"),
    ("C:/Users/hyper/workspace/bg", "master"),
    ("C:/Users/hyper/workspace", "main"),
]

def run(cmd, cwd=None, timeout=60):
    """Run command as list or string."""
    if isinstance(cmd, str):
        r = subprocess.run(cmd, shell=True, capture_output=True, text=True, cwd=cwd, timeout=timeout)
    else:
        r = subprocess.run(cmd, capture_output=True, text=True, cwd=cwd, timeout=timeout)
    return r.stdout.strip(), r.returncode

def get_submodules(repo_path):
    out, rc = run(['git', 'config', '-f', '.gitmodules', '--get-regexp', r'submodule\..*\.path'], cwd=repo_path)
    subs = []
    for line in out.splitlines():
        parts = line.strip().split()
        if len(parts) >= 2:
            subs.append(parts[1])
    return subs

def get_default_branch(sub_path):
    for branch in ["origin/main", "origin/master", "origin/develop"]:
        sha, rc = run(['git', 'rev-parse', branch], cwd=sub_path)
        if rc == 0 and sha and "TIMEOUT" not in sha:
            return branch, sha
    return None, None

def update_submodule(repo_path, sub_path):
    full_path = os.path.join(repo_path, sub_path)
    if not os.path.isdir(full_path):
        return "SKIP_NOT_DIR"
    
    recorded, _ = run(['git', 'ls-tree', 'HEAD', sub_path], cwd=repo_path)
    if not recorded:
        return "SKIP_NOT_IN_TREE"
    parts = recorded.split()
    recorded_sha = parts[2] if len(parts) >= 3 else None
    if not recorded_sha:
        return "SKIP_NO_SHA"
    
    branch, head_sha = get_default_branch(full_path)
    if not branch:
        return "SKIP_NO_BRANCH"
    
    if recorded_sha == head_sha:
        return "OK_ALREADY"
    
    # Force checkout to the remote branch HEAD
    run(['git', 'checkout', '-f', branch], cwd=full_path, timeout=30)
    
    new_sha, _ = run(['git', 'rev-parse', 'HEAD'], cwd=full_path)
    if new_sha == head_sha:
        return f"UPDATED to {head_sha[:12]}"
    else:
        return f"FAILED still {new_sha[:12]} vs {head_sha[:12]}"

def main():
    for repo_path, branch in REPOS:
        if not os.path.isdir(repo_path):
            print(f"\n=== SKIP: {repo_path} (not found) ===")
            continue
        
        gm = os.path.join(repo_path, ".gitmodules")
        if not os.path.exists(gm):
            print(f"\n=== SKIP: {repo_path} (no .gitmodules) ===")
            continue
        
        print(f"\n{'='*60}")
        print(f"=== {repo_path} ({branch}) ===")
        print(f"{'='*60}")
        
        subs = get_submodules(repo_path)
        if not subs:
            print("  No submodules found")
            continue
        
        updated = 0
        failed = 0
        skipped = 0
        
        for sub_path in subs:
            result = update_submodule(repo_path, sub_path)
            if "UPDATED" in result:
                updated += 1
                print(f"  + {sub_path}: {result}")
            elif "FAILED" in result:
                failed += 1
                print(f"  X {sub_path}: {result}")
            elif "OK_ALREADY" in result:
                pass
            else:
                skipped += 1
        
        print(f"\n  Summary: {updated} updated, {failed} failed, {skipped} skipped")
        
        if updated > 0:
            run(['git', 'add', '-A'], cwd=repo_path)
            out, _ = run(['git', 'diff', '--cached', '--stat'], cwd=repo_path)
            if out:
                msg = f"Update {updated} submodule pointers to branch HEADs"
                _, rc = run(['git', 'commit', '-m', msg], cwd=repo_path)
                if rc == 0:
                    print(f"  Committed: {msg}")
                    _, rc = run(f"git push origin {branch} --force", cwd=repo_path, timeout=120)
                    if rc == 0:
                        print(f"  Pushed to {branch}")
                    else:
                        print(f"  PUSH FAILED to {branch}")

if __name__ == "__main__":
    main()
    print("\n=== Done! ===")
