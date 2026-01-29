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

def run_command(command, cwd=None, env=None):
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
            text=True
        )
        return result
    except Exception as e:
        print(f"Error running command '{command}': {e}")
        return None

def get_submodules():
    """Returns a list of submodule paths."""
    print("Scanning for submodules...")
    # git submodule foreach returns output like "Entering 'path/to/module'" which is noisy
    # cleaner way is to parse .gitmodules or use git config
    res = run_command("git submodule foreach --recursive --quiet \"echo $displaypath\"")
    if res and res.returncode == 0:
        paths = res.stdout.strip().splitlines()
        # Filter out known problematic paths if any
        return [p for p in paths if "Usershyper" not in p]
    return []

def get_remote_url(path):
    res = run_command("git config --get remote.origin.url", cwd=path)
    if res and res.returncode == 0:
        return res.stdout.strip()
    return None

def get_repo_info(owner, repo):
    """Uses gh cli to check if repo is a fork."""
    cmd = f"gh repo view {owner}/{repo} --json isFork,parent,defaultBranchRef"
    res = run_command(cmd)
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

    # Parse owner/repo
    # Supports https://github.com/owner/repo.git or git@github.com:owner/repo.git
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

    parent_url = info["parent"]["url"]
    default_branch = info["defaultBranchRef"]["name"]
    print(f"[{path}] Detected fork of {parent_url} (Default: {default_branch})")

    # 1. Checkout default branch
    checkout = run_command(f"git checkout {default_branch}", cwd=path)
    if checkout.returncode != 0:
        print(f"[{path}] Could not checkout {default_branch}. Attempting master...")
        run_command("git checkout master", cwd=path)
    
    # 2. Add Upstream
    run_command(f"git remote add upstream {parent_url}", cwd=path)
    run_command(f"git remote set-url upstream {parent_url}", cwd=path) # Ensure it's correct if already exists

    # 3. Fetch
    print(f"[{path}] Fetching upstream...")
    fetch = run_command("git fetch upstream", cwd=path)
    if fetch.returncode != 0:
        print(f"[{path}] Failed to fetch upstream.")
        return

    # 4. Merge
    print(f"[{path}] Attempting merge from upstream/{default_branch}...")
    # --no-edit accepts default message. --no-ff preserves history visibility.
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
        
        # We don't abort. We add the files (which contain <<<< ==== >>>> markers)
        run_command("git add .", cwd=path)
        
        # Commit
        commit_msg = f"Merge upstream/{default_branch} (Conflict Markers Preserved)"
        commit = run_command(f"git commit -m \"{commit_msg}\"", cwd=path)
        
        if commit.returncode == 0:
            run_command("git push", cwd=path)
            print(f"[{path}] Pushed conflicted state to origin. MANUAL RESOLUTION REQUIRED.")
        else:
            print(f"[{path}] Failed to commit conflicts. Aborting merge to be safe.")
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
