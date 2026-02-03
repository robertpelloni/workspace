import subprocess
import os
import sys
import signal

# Unbuffered output
sys.stdout.reconfigure(encoding='utf-8')
sys.stderr.reconfigure(encoding='utf-8')

PROCESSED_FILE = "processed_repos.txt"
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
        f.write(f"{path}\n")
        f.flush()

def run_command(cmd, cwd, ignore_errors=False, timeout=120):
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
        print(f"[{cwd}] Command timed out ({timeout}s): {cmd}")
        return None
    except subprocess.CalledProcessError as e:
        if not ignore_errors:
            print(f"[{cwd}] Error running '{cmd}': {e.stderr.strip()}")
        return e.stdout.strip() if e.stdout else None
    except Exception as e:
        print(f"[{cwd}] Unexpected error: {e}")
        return None

def get_default_branch(cwd):
    branches = run_command("git branch -r", cwd, ignore_errors=True)
    if branches:
        if "origin/main" in branches:
            return "main"
        if "origin/master" in branches:
            return "master"
    return "main"

def get_current_branch(cwd):
    branch = run_command("git rev-parse --abbrev-ref HEAD", cwd, ignore_errors=True)
    if branch:
        return branch.strip()
    return "HEAD"

def process_repo(name, cwd, processed_set):
    norm_path = normalize_path(cwd)
    
    # Check skipped
    for skip in SKIPPED_REPOS:
        if skip in name or skip in cwd:
            print(f"Skipping blacklisted repo: {name}")
            return

    if norm_path in processed_set:
        return

    print(f"\n--- Processing {name} ---")
    
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

    # Check for uncommitted changes
    status = run_command("git status --porcelain", cwd, ignore_errors=True)
    if status:
        print(f"Uncommitted changes in {name}. Committing...")
        run_command("git add .", cwd)
        run_command('git commit -m "chore: save progress"', cwd)
    
    default_branch = get_default_branch(cwd)
    print(f"Target branch: {default_branch}")
    
    if current_branch == "HEAD":
        print(f"Repo is in detached HEAD state.")
        # Try to checkout default
        res = run_command(f"git checkout {default_branch}", cwd, ignore_errors=True)
        if res is not None:
            run_command(f"git pull origin {default_branch}", cwd, ignore_errors=True)
        else:
            print("Failed to checkout default branch. Skipping pull/push.")
            
    elif current_branch != default_branch:
        print(f"Merging {current_branch} into {default_branch}...")
        res = run_command(f"git checkout {default_branch}", cwd, ignore_errors=True)
        if res is not None:
            run_command(f"git pull origin {default_branch}", cwd, ignore_errors=True)
            try:
                run_command(f"git merge {current_branch}", cwd, timeout=60)
            except:
                 print("Merge failed. Aborting.")
                 run_command("git merge --abort", cwd, ignore_errors=True)
        else:
             print("Failed to checkout default branch.")

    else:
        # Already on default
        run_command(f"git pull origin {default_branch}", cwd, ignore_errors=True)

    print(f"Pushing {default_branch}...")
    run_command(f"git push origin {default_branch}", cwd, ignore_errors=True, timeout=60)
    
    save_processed(cwd)
    processed_set.add(norm_path)

def process_recursive(name, cwd, visited, processed_set):
    norm_path = normalize_path(cwd)
    
    # Check skipped
    for skip in SKIPPED_REPOS:
        if skip in name or skip in cwd:
            # print(f"Skipping recursion into blacklisted: {name}")
            return

    if norm_path in processed_set:
        return

    if cwd in visited:
        return
    visited.add(cwd)
    
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
    
    processed_set = load_processed()
    print(f"Loaded {len(processed_set)} processed repos.")
    
    visited = set()
    process_recursive("ROOT", root_path, visited, processed_set)
    
    # Finally process root
    process_repo("ROOT", root_path, processed_set)
    
    print("\nDone.")

if __name__ == "__main__":
    main()
