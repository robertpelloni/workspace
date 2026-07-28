#!/usr/bin/env python3
"""
Comprehensive Repository Synchronization & Intelligent Merge Engine
Handles 112+ submodules recursively
"""
import subprocess
import os
import json
from datetime import datetime

WORKSPACE = r"C:\Users\hyper\workspace"
LOG_FILE = os.path.join(WORKSPACE, "merge_sync_log.json")

def run_git(cmd, cwd=WORKSPACE, timeout=60):
    """Run git command and return output"""
    try:
        r = subprocess.run(
            ["git"] + cmd,
            cwd=cwd,
            capture_output=True,
            text=True,
            timeout=timeout,
            creationflags=subprocess.CREATE_NO_WINDOW if hasattr(subprocess, "CREATE_NO_WINDOW") else 0
        )
        return r.stdout.strip(), r.stderr.strip(), r.returncode
    except subprocess.TimeoutExpired:
        return "", "TIMEOUT", 1
    except Exception as e:
        return "", str(e), 1

def get_submodules():
    """Get all submodules from .gitmodules"""
    submodules = []
    try:
        with open(os.path.join(WORKSPACE, ".gitmodules"), "r") as f:
            current = {}
            for line in f:
                line = line.strip()
                if line.startswith("[submodule"):
                    if current:
                        submodules.append(current)
                    name = line.split('"')[1]
                    current = {"name": name}
                elif line.startswith("path = "):
                    current["path"] = line.split("= ", 1)[1]
                elif line.startswith("url = "):
                    current["url"] = line.split("= ", 1)[1]
            if current:
                submodules.append(current)
    except Exception as e:
        print(f"Error reading .gitmodules: {e}")
    return submodules

def fetch_submodule(sub):
    """Fetch all remotes for a submodule"""
    path = os.path.join(WORKSPACE, sub["path"])
    if not os.path.exists(path):
        return {"status": "missing"}
    
    # Fetch origin
    out, err, code = run_git(["fetch", "--all", "--tags"], cwd=path, timeout=30)
    
    # Get branches
    out, err, code = run_git(["branch", "-a"], cwd=path)
    branches = [b.strip().replace("* ", "") for b in out.split("\n") if b.strip() and not b.strip().startswith("HEAD")]
    
    # Get current branch
    out, _, _ = run_git(["branch", "--show-current"], cwd=path)
    current = out.strip()
    
    return {
        "status": "ok",
        "current_branch": current,
        "branches": branches,
        "remote_branches": [b for b in branches if b.startswith("remotes/origin/")],
        "local_branches": [b for b in branches if not b.startswith("remotes/")]
    }

def merge_feature_branches(sub, dry_run=False):
    """Merge feature branches into main"""
    path = os.path.join(WORKSPACE, sub["path"])
    results = []
    
    if not os.path.exists(path):
        return [{"status": "missing"}]
    
    # Get current branch
    out, _, _ = run_git(["branch", "--show-current"], cwd=path)
    current = out.strip()
    
    # Get all remote branches
    out, _, _ = run_git(["branch", "-r"], cwd=path)
    remote_branches = [b.strip() for b in out.split("\n") if b.strip() and "HEAD" not in b]
    
    # Get local branches
    out, _, _ = run_git(["branch"], cwd=path)
    local_branches = [b.strip().replace("* ", "") for b in out.split("\n") if b.strip()]
    
    # Find feature branches (not main/master)
    feature_branches = []
    for b in remote_branches:
        if "origin/main" in b or "origin/master" in b:
            continue
        branch_name = b.replace("origin/", "")
        feature_branches.append({"remote": b, "local": branch_name})
    
    # Also check local branches
    for b in local_branches:
        if b in ["main", "master", current]:
            continue
        if not any(fb["local"] == b for fb in feature_branches):
            feature_branches.append({"remote": None, "local": b})
    
    if not feature_branches:
        return [{"status": "no_feature_branches"}]
    
    # Ensure we're on main/master
    main_branch = "main" if "main" in local_branches else "master"
    if current != main_branch:
        run_git(["checkout", main_branch], cwd=path)
    
    # Fetch latest
    run_git(["fetch", "--all"], cwd=path, timeout=30)
    
    # Pull latest main
    run_git(["pull", "origin", main_branch], cwd=path, timeout=30)
    
    merged = []
    skipped = []
    conflicts = []
    
    for fb in feature_branches:
        branch = fb["local"]
        
        # Skip if branch is main/master
        if branch in ["main", "master"]:
            continue
        
        # Check if branch has unique commits
        if fb["remote"]:
            # Checkout local tracking branch
            out, err, code = run_git(["checkout", "-b", branch, fb["remote"]], cwd=path)
            if code != 0:
                # Branch exists locally, just checkout
                run_git(["checkout", branch], cwd=path)
        else:
            run_git(["checkout", branch], cwd=path)
        
        # Get commits ahead of main
        out, _, _ = run_git(["log", f"{main_branch}..{branch}", "--oneline"], cwd=path)
        ahead_commits = [l for l in out.split("\n") if l.strip()]
        
        if not ahead_commits:
            skipped.append({"branch": branch, "reason": "no_unique_commits"})
            run_git(["checkout", main_branch], cwd=path)
            continue
        
        # Try merge
        out, err, code = run_git(["merge", main_branch, "--no-edit"], cwd=path, timeout=30)
        
        if code == 0:
            # Merge successful, now merge into main
            run_git(["checkout", main_branch], cwd=path)
            out, err, code = run_git(["merge", branch, "--no-edit"], cwd=path, timeout=30)
            
            if code == 0:
                merged.append({
                    "branch": branch,
                    "commits": len(ahead_commits),
                    "first_commit": ahead_commits[0] if ahead_commits else ""
                })
            else:
                # Conflict on main merge - abort and try cherry-pick
                run_git(["merge", "--abort"], cwd=path)
                
                # Cherry-pick individual commits
                cherry_picked = 0
                for commit_line in ahead_commits:
                    commit_hash = commit_line.split()[0]
                    out, err, code = run_git(["cherry-pick", commit_hash], cwd=path, timeout=30)
                    if code == 0:
                        cherry_picked += 1
                    else:
                        run_git(["cherry-pick", "--abort"], cwd=path)
                
                if cherry_picked > 0:
                    merged.append({
                        "branch": branch,
                        "method": "cherry-pick",
                        "commits": cherry_picked,
                        "total": len(ahead_commits)
                    })
                else:
                    conflicts.append({
                        "branch": branch,
                        "commits": len(ahead_commits),
                        "error": err[:200]
                    })
        else:
            # Conflict on feature branch merge - abort
            run_git(["merge", "--abort"], cwd=path)
            conflicts.append({
                "branch": branch,
                "commits": len(ahead_commits),
                "error": err[:200]
            })
            run_git(["checkout", main_branch], cwd=path)
    
    return {
        "merged": merged,
        "skipped": skipped,
        "conflicts": conflicts,
        "total_branches": len(feature_branches)
    }

def main():
    print("=" * 60)
    print("REPOSITORY SYNCHRONIZATION & INTELLIGENT MERGE ENGINE")
    print("=" * 60)
    
    # Step 1: Get all submodules
    submodules = get_submodules()
    print(f"\nFound {len(submodules)} submodules")
    
    results = {}
    total_merged = 0
    total_conflicts = 0
    
    for i, sub in enumerate(submodules):
        name = sub["name"]
        path = os.path.join(WORKSPACE, sub["path"])
        
        if not os.path.exists(path):
            print(f"[{i+1}/{len(submodules)}] {name}: MISSING")
            results[name] = {"status": "missing"}
            continue
        
        print(f"[{i+1}/{len(submodules)}] {name}...", end=" ", flush=True)
        
        # Fetch
        fetch_result = fetch_submodule(sub)
        if fetch_result["status"] == "missing":
            print("MISSING")
            results[name] = fetch_result
            continue
        
        # Merge feature branches
        merge_result = merge_feature_branches(sub)
        
        if isinstance(merge_result, dict) and "merged" in merge_result:
            merged_count = len(merge_result["merged"])
            conflict_count = len(merge_result["conflicts"])
            total_merged += merged_count
            total_conflicts += conflict_count
            
            if merged_count > 0:
                print(f"MERGED {merged_count} branches")
            elif conflict_count > 0:
                print(f"CONFLICTS: {conflict_count}")
            else:
                print("OK (no feature branches)")
        else:
            print("OK")
        
        results[name] = {
            "fetch": fetch_result,
            "merge": merge_result
        }
    
    # Save results
    with open(LOG_FILE, "w") as f:
        json.dump({
            "timestamp": datetime.now().isoformat(),
            "total_submodules": len(submodules),
            "total_merged": total_merged,
            "total_conflicts": total_conflicts,
            "results": results
        }, f, indent=2)
    
    print("\n" + "=" * 60)
    print(f"SUMMARY:")
    print(f"  Total submodules: {len(submodules)}")
    print(f"  Branches merged: {total_merged}")
    print(f"  Conflicts: {total_conflicts}")
    print(f"  Log: {LOG_FILE}")
    print("=" * 60)

if __name__ == "__main__":
    main()
