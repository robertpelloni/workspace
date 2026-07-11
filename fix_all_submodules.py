#!/usr/bin/env python3
"""
Comprehensive submodule fix: update ALL submodules in ALL repos
to point to the HEAD of their default branch, so --shallow-submodules works.
"""
import subprocess
import os
import sys

def run(cmd, cwd=None, check=False):
    r = subprocess.run(cmd, shell=True, capture_output=True, text=True, cwd=cwd)
    if check and r.returncode != 0:
        print(f"  CMD FAILED: {cmd}")
        print(f"  stderr: {r.stderr.strip()}")
    return r.stdout.strip(), r.stderr.strip(), r.returncode

def get_default_branch(path):
    """Get the default branch of a repo."""
    out, _, _ = run("git remote show origin", cwd=path)
    for line in out.splitlines():
        if "HEAD branch:" in line:
            return line.split("HEAD branch:")[1].strip()
    # fallback
    out, _, _ = run("git branch -r --points-at HEAD", cwd=path)
    if "origin/master" in out:
        return "master"
    if "origin/main" in out:
        return "main"
    return "main"

def get_submodules(repo_path):
    """Get list of submodule paths from .gitmodules."""
    out, _, _ = run("git config --file .gitmodules --get-regexp path", cwd=repo_path)
    subs = []
    for line in out.splitlines():
        parts = line.split()
        if len(parts) == 2:
            subs.append(parts[1])
    return subs

def fix_submodule(repo_path, sub_path):
    """Fix a single submodule by pointing it to origin/HEAD."""
    full_path = os.path.join(repo_path, sub_path)
    
    if not os.path.isdir(full_path):
        return "SKIP", "Directory missing"
    
    # Get the default branch
    branch = get_default_branch(full_path)
    
    # Fetch latest
    out, err, rc = run(f"git fetch origin {branch}", cwd=full_path)
    if rc != 0:
        # Try fetching without branch spec
        out, err, rc = run("git fetch origin", cwd=full_path)
        if rc != 0:
            return "FAIL", f"fetch failed: {err[:100]}"
    
    # Get the HEAD commit of the default branch
    head_sha, _, rc = run(f"git rev-parse origin/{branch}", cwd=full_path)
    if rc != 0 or not head_sha:
        return "FAIL", f"rev-parse failed for origin/{branch}"
    
    # Get the currently recorded SHA in the parent
    recorded_sha, _, _ = run(f"git ls-tree HEAD {sub_path}", cwd=repo_path)
    if recorded_sha:
        recorded_sha = recorded_sha.split()[2] if len(recorded_sha.split()) >= 3 else ""
    
    if recorded_sha == head_sha:
        return "OK", f"already at {head_sha[:8]} ({branch})"
    
    # Checkout the branch HEAD
    out, err, rc = run(f"git checkout origin/{branch}", cwd=full_path)
    if rc != 0:
        return "FAIL", f"checkout failed: {err[:100]}"
    
    # Stage the submodule pointer update in parent
    run(f"git add {sub_path}", cwd=repo_path)
    
    return "UPDATED", f"{recorded_sha[:8]} -> {head_sha[:8]} ({branch})"

def fix_repo(repo_path, branch_name):
    """Fix all submodules in a repo."""
    print(f"\n{'='*60}")
    print(f"FIXING: {repo_path} (branch: {branch_name})")
    print(f"{'='*60}")
    
    # Ensure we're on the right branch
    run(f"git checkout {branch_name}", cwd=repo_path)
    
    subs = get_submodules(repo_path)
    if not subs:
        print("  No submodules found")
        return False
    
    changes_made = False
    updated = 0
    failed = 0
    
    for sub_path in subs:
        status, msg = fix_submodule(repo_path, sub_path)
        icon = {"OK": "[OK]", "UPDATED": "[UP]", "FAIL": "[!!]", "SKIP": "[--]"}[status]
        print(f"  {icon} {sub_path}: {msg}")
        if status == "UPDATED":
            changes_made = True
            updated += 1
        elif status == "FAIL":
            failed += 1
    
    # Also fix nested submodules recursively
    for sub_path in subs:
        full_path = os.path.join(repo_path, sub_path)
        nested_subs = get_submodules(full_path)
        if nested_subs:
            print(f"\n  --- Nested in {sub_path} ---")
            for ns in nested_subs:
                status, msg = fix_submodule(full_path, ns)
                icon = {"OK": "[OK]", "UPDATED": "[UP]", "FAIL": "[!!]", "SKIP": "[--]"}[status]
                print(f"    {icon} {ns}: {msg}")
                if status == "UPDATED":
                    run(f"git add {ns}", cwd=full_path)
                    # Re-add parent submodule to pick up nested changes
                    run(f"git add {sub_path}", cwd=repo_path)
                    changes_made = True
                    updated += 1
                elif status == "FAIL":
                    failed += 1
    
    if changes_made:
        # Commit
        out, _, rc = run(
            'git commit -m "Fix all submodule pointers to branch HEADs for shallow clone compatibility"',
            cwd=repo_path
        )
        if rc == 0:
            print(f"\n  COMMITTED changes ({updated} submodules updated)")
        else:
            print(f"\n  Commit result: {out}")
        
        # Push
        out, err, rc = run(f"git push origin {branch_name} --force", cwd=repo_path)
        if rc == 0:
            print(f"  PUSHED to origin/{branch_name}")
        else:
            print(f"  PUSH FAILED: {err[:200]}")
    else:
        print(f"\n  No changes needed ({updated} updated, {failed} failed)")
    
    return changes_made

# Repos to fix
repos = [
    (r"C:\Users\hyper\workspace\bobmani\itgmania", "release"),
    (r"C:\Users\hyper\workspace\bg\bobsgameonlinejava", "main"),
    (r"C:\Users\hyper\workspace\bg", "master"),
    (r"C:\Users\hyper\workspace\bobfilez", "main"),
]

total_changes = 0
for repo_path, branch in repos:
    if os.path.isdir(repo_path):
        if fix_repo(repo_path, branch):
            total_changes += 1
    else:
        print(f"SKIP: {repo_path} not found")

print(f"\n{'='*60}")
print(f"Total repos updated: {total_changes}")
print(f"{'='*60}")
