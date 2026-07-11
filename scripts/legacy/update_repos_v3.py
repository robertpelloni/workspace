import subprocess
import os
import sys
import time

# Unbuffered output
sys.stdout.reconfigure(encoding='utf-8')
sys.stderr.reconfigure(encoding='utf-8')

PROCESSED_FILE = "processed_repos_v3.txt"
FAILED_LOG = "failed_repos_v3.log"

SKIPPED_REPOS = [
    "voidsprite", 
    "temp_defihacklabs",
    "vibeship-scanner", 
    "borg" 
]

def normalize_path(path):
    return os.path.normpath(os.path.abspath(path)).lower()

def load_processed():
    if os.path.exists(PROCESSED_FILE):
        with open(PROCESSED_FILE, "r", encoding="utf-8") as f:
            return set(normalize_path(line.strip()) for line in f if line.strip())
    return set()

def save_processed(path):
    with open(PROCESSED_FILE, "a", encoding="utf-8") as f:
        f.write(path + "\n")
        f.flush()

def log_failure(path, reason):
    with open(FAILED_LOG, "a", encoding="utf-8") as f:
        f.write(f"{path}: {reason}\n")
        f.flush()

def run_command(cmd, cwd, ignore_errors=False, timeout=300):
    try:
        # print(f"[{cwd}] Executing: {cmd}")
        result = subprocess.run(
            cmd, 
            cwd=cwd, 
            shell=True, 
            check=True, 
            stdout=subprocess.PIPE, 
            stderr=subprocess.PIPE, 
            text=True, 
            encoding='utf-8', 
            errors='replace',
            timeout=timeout
        )
        return result.stdout.strip()
    except subprocess.TimeoutExpired:
        msg = f"Command timed out ({timeout}s): {cmd}"
        print(f"[{cwd}] {msg}")
        return None
    except subprocess.CalledProcessError as e:
        if not ignore_errors:
            print(f"[{cwd}] Error running '{cmd}': {e.stderr.strip()}")
        return None
    except Exception as e:
        print(f"[{cwd}] Unexpected error: {e}")
        return None

def get_default_branch(cwd):
    # Try to find the default branch from remote info
    try:
        remotes = run_command("git remote show origin", cwd, ignore_errors=True, timeout=10)
        if remotes:
            for line in remotes.split('\n'):
                if "HEAD branch:" in line:
                    return line.split("HEAD branch:")[1].strip()
    except:
        pass

    # Fallback to checking local/remote branches
    branches = run_command("git branch -r", cwd, ignore_errors=True)
    if branches:
        if "origin/main" in branches:
            return "main"
        if "origin/master" in branches:
            return "master"
    
    # Last fallback
    return "main"

def get_current_branch(cwd):
    branch = run_command("git rev-parse --abbrev-ref HEAD", cwd, ignore_errors=True)
    if branch:
        return branch.strip()
    return "HEAD"

def get_local_branches(cwd):
    output = run_command("git branch --format=%(refname:short)", cwd, ignore_errors=True)
    if output:
        # Remove any surrounding quotes that might appear in some shell environments
        return [b.strip().strip("'").strip('"') for b in output.split('\n') if b.strip()]
    return []

def process_repo(name, cwd, processed_set):
    norm_path = normalize_path(cwd)
    
    # Check skipped
    for skip in SKIPPED_REPOS:
        if skip in name or skip in cwd:
            print(f"Skipping blacklisted repo: {name}")
            return

    if norm_path in processed_set:
        return

    print(f"\n>>> Starting Processing: {name} at {cwd}")
    
    if not os.path.exists(cwd):
        print(f"Directory {cwd} does not exist. Skipping.")
        save_processed(cwd)
        processed_set.add(norm_path)
        return

    if not os.path.exists(os.path.join(cwd, ".git")) and not os.path.isfile(os.path.join(cwd, ".git")):
         print(f"{cwd} is not a git repo. Skipping.")
         save_processed(cwd)
         processed_set.add(norm_path)
         return

    current_branch = get_current_branch(cwd)
    print(f"Current branch: {current_branch}")

    # Check for uncommitted changes and commit them if present
    status = run_command("git status --porcelain", cwd, ignore_errors=True)
    if status:
        print(f"Uncommitted changes in {name}. Committing...")
        run_command("git add .", cwd)
        run_command('git commit -m "chore: save progress before update"', cwd)
    
    default_branch = get_default_branch(cwd)
    print(f"Target branch: {default_branch}")
    
    # 1. Checkout Default Branch
    if current_branch != default_branch:
        print(f"Checking out {default_branch}...")
        res = run_command(f"git checkout {default_branch}", cwd, ignore_errors=True)
        if res is None:
            # Maybe the default branch is not local yet?
            print(f"Failed to checkout {default_branch} locally. Trying to track origin/{default_branch}...")
            res = run_command(f"git checkout -b {default_branch} --track origin/{default_branch}", cwd, ignore_errors=True)
            if res is None:
                msg = f"Failed to checkout {default_branch}. Skipping."
                print(msg)
                log_failure(cwd, msg)
                save_processed(cwd)
                processed_set.add(norm_path)
                return

    # 2. Pull Origin (Sync Fork)
    print(f"Pulling origin {default_branch}...")
    pull_res = run_command(f"git pull origin {default_branch}", cwd, ignore_errors=True)
    if pull_res is None:
        log_failure(cwd, "Git pull origin failed")

    # 3. Merge Upstream (Sync Parent) if 'upstream' remote exists
    remotes = run_command("git remote", cwd, ignore_errors=True)
    if remotes and "upstream" in remotes.split():
        # Check if upstream branch exists
        upstream_branch_ref = f"upstream/{default_branch}"
        remote_branches = run_command("git branch -r", cwd, ignore_errors=True)
        
        if remote_branches and upstream_branch_ref in remote_branches:
            print(f"Upstream remote detected and {upstream_branch_ref} exists. Fetching and merging...")
            run_command("git fetch upstream", cwd)
            try:
                merge_res = run_command(f"git merge {upstream_branch_ref}", cwd, timeout=120)
                if merge_res is None:
                    raise Exception("Merge failed")
            except:
                 msg = "Upstream merge failed/conflict. Aborting upstream merge."
                 print(msg)
                 log_failure(cwd, msg)
                 run_command("git merge --abort", cwd, ignore_errors=True)
        else:
            print(f"Upstream remote detected but {upstream_branch_ref} not found. Skipping upstream merge.")

    # 4. Merge ALL Local Feature Branches
    local_branches = get_local_branches(cwd)
    for branch in local_branches:
        if branch in [default_branch, "master", "main", "HEAD"]:
            continue
        
        # Determine if it's a "feature" branch that needs merging
        # e.g. not a protected release branch? For now assume all non-default are candidates per user request
        
        print(f"Attempting to merge local branch '{branch}' into {default_branch}...")
        try:
            merge_res = run_command(f"git merge {branch}", cwd, timeout=120)
            if merge_res is None:
                 print(f"Merge failed for {branch}. Aborting.")
                 run_command("git merge --abort", cwd, ignore_errors=True)
        except:
             msg = f"Feature merge failed for branch {branch}. Aborting."
             print(msg)
             log_failure(cwd, msg)
             run_command("git merge --abort", cwd, ignore_errors=True)

    # 5. Push to Origin (only if it's a robertpelloni repo or fork)
    remotes_v = run_command("git remote -v", cwd, ignore_errors=True)
    if remotes_v and "robertpelloni" in remotes_v.lower():
        print(f"Pushing {default_branch} to origin...")
        run_command(f"git push origin {default_branch}", cwd, ignore_errors=True, timeout=120)
    else:
        print(f"Skipping push for non-robertpelloni repo: {name}")
    
    save_processed(cwd)
    processed_set.add(norm_path)
    print(f"<<< Finished Processing: {name}")

def process_recursive(name, cwd, visited, processed_set):
    norm_path = normalize_path(cwd)
    
    # Check skipped
    for skip in SKIPPED_REPOS:
        if skip in name or skip in cwd:
            # print(f"Skipping recursion into blacklisted: {name}")
            return

    if norm_path in processed_set:
        return

    # Use realpath to handle symbolic links and self-referencing submodules (./././)
    try:
        real_cwd = os.path.realpath(cwd)
    except:
        return
        
    if real_cwd in visited:
        return
    visited.add(real_cwd)
    
    print(f"Scanning {name}...")
    
    # Get direct submodules
    output = run_command("git submodule status", cwd, ignore_errors=True)
    
    submodules = []
    if output:
        for line in output.split('\n'):
            parts = line.strip().split()
            if len(parts) >= 2:
                sub_path = parts[1]
                sub_abs_path = os.path.join(cwd, sub_path)
                submodules.append((sub_path, sub_abs_path))
    
    # Process children FIRST (Post-Order)
    for sub_path, sub_abs_path in submodules:
        process_recursive(f"{name}/{sub_path}", sub_abs_path, visited, processed_set)
    
    # Process self
    if name != "ROOT": 
        process_repo(name, cwd, processed_set)

def main():
    root_path = os.getcwd()
    print(f"Root: {root_path}")
    
    # Clear logs if new run
    if not os.path.exists(PROCESSED_FILE):
        if os.path.exists(FAILED_LOG):
            os.remove(FAILED_LOG)

    processed_set = load_processed()
    print(f"Loaded {len(processed_set)} processed repos.")
    
    visited = set()
    process_recursive("ROOT", root_path, visited, processed_set)
    
    # Finally process root
    process_repo("ROOT", root_path, processed_set)
    
    print("\nDone.")

if __name__ == "__main__":
    main()
