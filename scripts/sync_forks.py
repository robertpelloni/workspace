#!/usr/bin/env python3
"""
Sync Forks Script
=================

This script iterates through all Git submodules in the current workspace.
For each submodule, it checks if it is a GitHub fork.
If it is a fork, it:
1. Adds the upstream parent repository as a remote named 'upstream'.
2. Fetches the latest changes from upstream.
3. Merges the upstream default branch into the local branch.
4. If conflicts occur:
   - It stages the files WITH conflict markers (<<<<<<<, =======, >>>>>>>).
   - Commits them with a warning message.
   - This ensures no code is lost ("don't lose features") and keeps the repo synced,
     even if the build is temporarily broken ("ok to break the build").
5. Pushes the changes to the origin (your fork).

Usage:
    python3 scripts/sync_forks.py
"""

import subprocess
import json
import os
import sys
import re

# Timeout for git commands in seconds
TIMEOUT = 300 

def run_command(command, cwd=None, env=None, timeout=TIMEOUT):
    """Runs a shell command and returns the output. Raises on failure unless check=False."""
    try:
        # Set environment to non-interactive to avoid hanging on prompts
        my_env = os.environ.copy()
        if env:
            my_env.update(env)
        my_env["GIT_TERMINAL_PROMPT"] = "0"
        
        result = subprocess.run(
            command,
            cwd=cwd,
            env=my_env,
            shell=True,
            capture_output=True,
            text=True,
            timeout=timeout
        )
        return result
    except subprocess.TimeoutExpired:
        print(f"Error: Command '{command}' timed out after {timeout}s")
        # Return a dummy failed result
        return subprocess.CompletedProcess(args=command, returncode=124, stdout="", stderr="TimeoutExpired")
    except Exception as e:
        print(f"Error running command '{command}': {e}")
        return None

def get_submodules():
    """Returns a list of submodule paths by parsing .gitmodules directly."""
    print("Scanning for submodules...")
    # Use git config to list all submodule paths defined in .gitmodules
    # Output format: submodule.name.path path/to/module
    res = run_command("git config --file .gitmodules --get-regexp path", timeout=30)
    
    paths = []
    if res and res.returncode == 0:
        lines = res.stdout.strip().splitlines()
        for line in lines:
            parts = line.split(' ', 1)
            if len(parts) == 2:
                path = parts[1].strip()
                if "Usershyper" not in path:
                    paths.append(path)
    
    # Also attempt recursive status to catch nested ones effectively
    res_recursive = run_command("git submodule status --recursive", timeout=60)
    if res_recursive and res_recursive.returncode == 0:
        recursive_paths = []
        for line in res_recursive.stdout.splitlines():
            # Output format: -commit_hash path/to/module (branch)
            parts = line.strip().split()
            if len(parts) >= 2:
                path = parts[1]
                if "Usershyper" not in path:
                    recursive_paths.append(path)
        # return unique sorted paths
        return sorted(list(set(paths + recursive_paths)), key=len, reverse=True)

    return paths

def get_remote_url(path):
    res = run_command("git config --get remote.origin.url", cwd=path, timeout=10)
    if res and res.returncode == 0:
        return res.stdout.strip()
    return None

def get_repo_info(owner, repo):
    """Uses gh cli to check if repo is a fork."""
    cmd = f"gh repo view {owner}/{repo} --json isFork,parent,defaultBranchRef"
    res = run_command(cmd, timeout=30)
    if res and res.returncode == 0:
        return json.loads(res.stdout)
    return None

def sync_submodule(path):
    print(f"\n[{path}] Inspecting...")
    
    if not os.path.exists(path):
        print(f"[{path}] Directory not found. Skipping.")
        return

    url = get_remote_url(path)
    if not url:
        print(f"[{path}] No remote URL found.")
        return

    match = re.search(r"github\.com[:/]([^/]+)/([^/.]+?)(\.git)?$", url)
    if not match:
        print(f"[{path}] Not a GitHub repository ({url}). Skipping.")
        return

    owner, repo_name = match.group(1), match.group(2)
    full_repo = f"{owner}/{repo_name}"

    try:
        info = get_repo_info(owner, repo_name)
    except:
        print(f"[{path}] Could not retrieve info for {full_repo}. Skipping.")
        return

    if not info:
        print(f"[{path}] Access denied or repo not found: {full_repo}")
        return

    if not info.get("isFork"):
        print(f"[{path}] Not a fork. Skipping.")
        return

    try:
        # Construct parent URL manually as 'url' key might be missing in 'parent' object
        p_owner = info["parent"]["owner"]["login"]
        p_name = info["parent"]["name"]
        parent_url = f"https://github.com/{p_owner}/{p_name}"
        default_branch = info["defaultBranchRef"]["name"]
    except KeyError as e:
        print(f"[{path}] Error parsing repo info: missing key {e}. Info: {json.dumps(info)}")
        return

    print(f"[{path}] Detected fork of {parent_url} (Default: {default_branch})")

    # 1. Checkout default branch
    checkout = run_command(f"git checkout {default_branch}", cwd=path)
    if checkout.returncode != 0:
        print(f"[{path}] Could not checkout {default_branch}. Attempting master...")
        run_command("git checkout master", cwd=path)
    
    # 2. Add Upstream
    run_command(f"git remote add upstream {parent_url}", cwd=path)
    run_command(f"git remote set-url upstream {parent_url}", cwd=path)

    # 3. Fetch
    print(f"[{path}] Fetching upstream...")
    fetch = run_command("git fetch upstream", cwd=path, timeout=600) # Give more time for large fetches
    if fetch.returncode != 0:
        print(f"[{path}] Failed to fetch upstream. Stderr: {fetch.stderr}")
        return

    # 4. Merge
    print(f"[{path}] Attempting merge from upstream/{default_branch}...")
    merge = run_command(f"git merge upstream/{default_branch} --no-edit", cwd=path)

    if merge.returncode == 0:
        # Success
        if "Already up to date" in merge.stdout:
            print(f"[{path}] Already up to date.")
        else:
            print(f"[{path}] Merge successful.")
            run_command("git push", cwd=path)
            print(f"[{path}] Pushed to origin.")
    else:
        # Conflict!
        print(f"[{path}] !! MERGE CONFLICT DETECTED !!")
        print(f"[{path}] Resolution Strategy: Committing conflict markers to preserve all features.")
        
        # Use -A to stage all changes including deletions
        run_command("git add -A", cwd=path)
        
        # Commit with --no-verify to skip hooks
        commit_msg = f"Merge upstream/{default_branch} (Conflict Markers Preserved)"
        commit = run_command(f"git commit --no-verify -m \"{commit_msg}\"", cwd=path)
        
        if commit.returncode == 0:
            run_command("git push", cwd=path)
            print(f"[{path}] Pushed conflicted state to origin. MANUAL RESOLUTION REQUIRED.")
        else:
            print(f"[{path}] Failed to commit conflicts. Stderr: {commit.stderr}")
            print(f"[{path}] Aborting merge to be safe.")
            run_command("git merge --abort", cwd=path)

def main():
    submodules = get_submodules()
    print(f"Found {len(submodules)} submodules.")
    
    for path in submodules:
        sync_submodule(path)

    print("\n\nAll submodules processed.")
    print("Updating workspace pointers...")
    run_command("git add .")
    run_command("git commit -m \"Update forked submodules from upstream parents (auto-sync)\"")
    run_command("git push")

if __name__ == "__main__":
    main()