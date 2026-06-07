import os
import subprocess
import json
import logging

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(message)s')

def run_git(cmd, cwd=None, check=False, env=None):
    try:
        logging.debug(f"Running in {cwd or '.'}: {cmd}")
        # Need to use shell=True on Windows for basic git commands, or use a list
        process = subprocess.run(cmd, cwd=cwd, shell=True, capture_output=True, text=True, env=env)
        if check and process.returncode != 0:
            logging.error(f"Command failed: {cmd}\nOutput: {process.stderr}")
        return process.returncode, process.stdout.strip(), process.stderr.strip()
    except Exception as e:
        logging.error(f"Exception running {cmd}: {e}")
        return -1, "", str(e)

def get_submodules(cwd):
    _, out, _ = run_git("git config --file .gitmodules --get-regexp path", cwd=cwd)
    paths = []
    for line in out.splitlines():
        if line:
            parts = line.split()
            if len(parts) == 2:
                paths.append(parts[1])
    return paths

def get_all_submodules_recursive(base_path="."):
    all_paths = []
    def traverse(current_base):
        paths = get_submodules(current_base)
        for p in paths:
            full_path = os.path.join(current_base, p)
            all_paths.append(full_path)
            traverse(full_path)
    traverse(base_path)
    return all_paths

def fetch_all(path):
    logging.info(f"Fetching all in {path}")
    run_git("git fetch --all --tags", cwd=path)

def get_primary_branch(path):
    _, out, _ = run_git("git branch -r", cwd=path)
    if "origin/main" in out:
        return "main"
    elif "origin/master" in out:
        return "master"
    return "main"

def sync_upstream_to_main(path, primary_branch):
    logging.info(f"Syncing upstream to {primary_branch} in {path}")
    # Get current branch
    _, current, _ = run_git("git branch --show-current", cwd=path)
    if not current:
        logging.warning(f"Detached HEAD in {path}, checking out {primary_branch}")
        run_git(f"git checkout {primary_branch}", cwd=path)
        current = primary_branch
    
    # Commit local changes just in case
    _, status, _ = run_git("git status --porcelain", cwd=path)
    if status:
        run_git("git add .", cwd=path)
        run_git('git commit -m "chore: auto checkpoint before sync"', cwd=path)
    
    if current != primary_branch:
        run_git(f"git checkout {primary_branch}", cwd=path)
    
    run_git(f"git pull origin {primary_branch} --rebase", cwd=path)

def process_repo(path):
    logging.info(f"--- Processing Repo: {path} ---")
    if not os.path.exists(os.path.join(path, ".git")):
        logging.warning(f"No .git found in {path}")
        return
        
    fetch_all(path)
    primary_branch = get_primary_branch(path)
    sync_upstream_to_main(path, primary_branch)
    
    # Dual-Direction Merge
    _, branches_out, _ = run_git("git branch --format='%(refname:short)'", cwd=path)
    branches = [b for b in branches_out.splitlines() if b and b != primary_branch]
    
    for branch in branches:
        # Ignore old upstream branches implicitly, we are only iterating local branches here.
        logging.info(f"  Intelligent Merge for branch: {branch}")
        
        # Forward Merge: Feature -> Main
        run_git(f"git checkout {primary_branch}", cwd=path)
        code, out, err = run_git(f"git merge {branch} --no-edit", cwd=path)
        if code != 0:
            logging.warning(f"  Conflict in forward merge ({branch} -> {primary_branch}). Resolving using both...")
            run_git("git merge --abort", cwd=path)
            # Add all as conflict resolution
            run_git(f"git merge {branch} -X ours --no-edit", cwd=path) # Prefer main if conflicts
        
        # Reverse Merge: Main -> Feature
        run_git(f"git checkout {branch}", cwd=path)
        code, out, err = run_git(f"git merge {primary_branch} --no-edit", cwd=path)
        if code != 0:
            logging.warning(f"  Conflict in reverse merge ({primary_branch} -> {branch}). Resolving...")
            run_git("git merge --abort", cwd=path)
            run_git(f"git merge {primary_branch} -X theirs --no-edit", cwd=path) # Prefer main
            
    # Return to primary branch
    run_git(f"git checkout {primary_branch}", cwd=path)

def main():
    # 1. Root Repo Sync
    process_repo(".")
    
    # 2. Update submodules recursively
    logging.info("Updating all submodules recursively...")
    # Using python subprocess to avoid the bash alias issue
    run_git("git submodule update --init --recursive --remote")
    
    # 3. Process each submodule
    submodules = get_all_submodules_recursive()
    for sub in submodules:
        process_repo(sub)

if __name__ == '__main__':
    main()
