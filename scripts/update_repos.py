import subprocess
import os
import sys
import shutil

# Unbuffered output
sys.stdout.reconfigure(encoding='utf-8')
sys.stderr.reconfigure(encoding='utf-8')

# Constants
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.dirname(SCRIPT_DIR)
PROCESSED_FILE = os.path.join(ROOT_DIR, "processed_repos.txt")

SKIPPED_REPOS = [
    "voidsprite", 
    "temp_defihacklabs",
    "vibeship-scanner", 
    "borg",
    "node_modules", 
    ".venv",
    "Milkwave",
    "bg/bobsgameonlinejava"
]

def normalize_path(path):
    return os.path.normpath(os.path.abspath(path)).lower()

def load_processed():
    processed = set()
    if os.path.exists(PROCESSED_FILE):
        try:
            with open(PROCESSED_FILE, "r", encoding="utf-8") as f:
                for line in f:
                    line = line.strip()
                    if line:
                        processed.add(normalize_path(line))
        except:
            pass
    return processed

def save_processed(path):
    with open(PROCESSED_FILE, "a", encoding="utf-8") as f:
        f.write(f"{path}\n")
        f.flush()

def make_long_path(path):
    if os.name == 'nt':
        abs_path = os.path.abspath(path)
        if not abs_path.startswith('\\\\?\\'):
            if abs_path.startswith('\\\\'):
                return '\\\\?\\UNC\\' + abs_path[2:]
            return '\\\\?\\' + abs_path
    return os.path.abspath(path)

def run_command(cmd, cwd, ignore_errors=False, timeout=600):
    try:
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
            print(f"[{cwd}] Command failed: {cmd}")
            print(f"Stderr: {e.stderr.strip()}")
        return None
    except Exception as e:
        print(f"[{cwd}] Unexpected error: {e}")
        return None

def get_default_branch(cwd):
    try:
        remotes = run_command("git remote show origin", cwd, ignore_errors=True, timeout=10)
        if remotes:
            for line in remotes.split('\n'):
                if "HEAD branch:" in line:
                    return line.split("HEAD branch:")[1].strip()
    except:
        pass

    branches = run_command("git branch -r", cwd, ignore_errors=True)
    if branches:
        if "origin/main" in branches:
            return "main"
        if "origin/master" in branches:
            return "master"
        if "origin/develop" in branches:
            return "develop"
    return "main"

def get_current_branch(cwd):
    branch = run_command("git rev-parse --abbrev-ref HEAD", cwd, ignore_errors=True)
    if branch:
        return branch.strip()
    return "HEAD"

def get_upstream_branch(cwd, target_branch):
    """
    Finds the matching branch on upstream.
    Priorities:
    1. upstream/{target_branch}
    2. upstream/main
    3. upstream/master
    """
    try:
        remote_branches = run_command("git branch -r", cwd, ignore_errors=True)
        if not remote_branches:
            return None
        
        branches = [b.strip() for b in remote_branches.split('\n')]
        
        # Check specific branch
        if f"upstream/{target_branch}" in branches:
            return f"upstream/{target_branch}"
        
        # Fallbacks
        if "upstream/main" in branches:
            return "upstream/main"
        if "upstream/master" in branches:
            return "upstream/master"
        if "upstream/develop" in branches:
            return "upstream/develop"
            
    except:
        pass
    return None

def process_repo(name, cwd, processed_set):
    norm_path = normalize_path(cwd)
    
    for skip in SKIPPED_REPOS:
        if skip in name or skip in cwd:
            return

    if norm_path in processed_set:
        return

    print(f"\n>>> Processing: {name}")
    
    long_cwd = make_long_path(cwd)
    
    if not os.path.exists(long_cwd):
        print(f"Directory {cwd} does not exist. Skipping.")
        return

    git_dir = os.path.join(long_cwd, ".git")
    if not os.path.exists(git_dir) and not os.path.isfile(git_dir):
         print(f"Not a git repo: {cwd}")
         return

    # Check for uncommitted changes
    status = run_command("git status --porcelain", cwd, ignore_errors=True)
    if status:
        print(f"  Uncommitted changes detected in {name}. Committing 'chore: save progress'...")
        run_command("git add .", cwd)
        run_command('git commit -m "chore: save progress"', cwd, ignore_errors=True)

    current_branch = get_current_branch(cwd)
    default_branch = get_default_branch(cwd)
    print(f"  Branch: {current_branch} -> {default_branch}")

    # Switch to default branch
    if current_branch != default_branch:
        res = run_command(f"git checkout {default_branch}", cwd, ignore_errors=True)
        if res is None:
            # Try to fetch first
            run_command("git fetch origin", cwd)
            res = run_command(f"git checkout {default_branch}", cwd, ignore_errors=True)
            if res is None:
                # Try to create track
                run_command(f"git checkout -b {default_branch} --track origin/{default_branch}", cwd, ignore_errors=True)

    # Pull Origin
    print(f"  Pulling origin {default_branch}...")
    run_command(f"git pull origin {default_branch}", cwd, ignore_errors=True)

    # Merge Upstream
    remotes = run_command("git remote", cwd, ignore_errors=True)
    if remotes and "upstream" in remotes.split():
        print(f"  Upstream detected. Fetching...")
        run_command("git fetch upstream", cwd)
        
        upstream_ref = get_upstream_branch(cwd, default_branch)
        if upstream_ref:
            print(f"  Merging {upstream_ref}...")
            try:
                # Use --no-edit to avoid opening editor, but if conflicts occur, git will exit with error
                res = run_command(f"git merge {upstream_ref} --no-edit", cwd)
                if res is None:
                     # This usually means conflict or 'not something we can merge' (handled by get_upstream_branch ideally)
                     print("  ! Merge failed (conflict or error). Aborting to preserve state.")
                     run_command("git merge --abort", cwd, ignore_errors=True)
                else:
                    print("  Upstream merge successful.")
            except:
                 print("  ! Exception during merge. Aborting.")
                 run_command("git merge --abort", cwd, ignore_errors=True)
        else:
            print(f"  Could not find matching upstream branch for {default_branch}.")

    # Merge Local Feature Branches (RobertPelloni logic)
    remotes_v = run_command("git remote -v", cwd, ignore_errors=True)
    is_my_repo = remotes_v and "robertpelloni" in remotes_v.lower()

    if is_my_repo:
        branches_out = run_command("git branch --format=%(refname:short)", cwd, ignore_errors=True)
        if branches_out:
            local_branches = branches_out.split('\n')
            for branch in local_branches:
                branch = branch.strip()
                if not branch: continue
                # Skip default/special branches
                if branch in [default_branch, "HEAD", "master", "main", "develop", "origin/HEAD"]: continue
                if branch.startswith("origin/"): continue
                
                # Check if already merged
                is_ancestor = run_command(f"git merge-base --is-ancestor {branch} {default_branch}", cwd, ignore_errors=True)
                if is_ancestor is not None:
                     # Already merged
                     continue
                
                print(f"  Merging local feature branch: {branch} into {default_branch}...")
                try:
                    res = run_command(f"git merge {branch} --no-edit", cwd)
                    if res is None:
                        print(f"  ! Conflict merging {branch}. Aborting.")
                        run_command("git merge --abort", cwd, ignore_errors=True)
                    else:
                        print(f"  Successfully merged {branch}.")
                except:
                    run_command("git merge --abort", cwd, ignore_errors=True)

    # Push
    if is_my_repo:
        print(f"  Pushing {default_branch} to origin...")
        run_command(f"git push origin {default_branch}", cwd, ignore_errors=True)
    
    save_processed(cwd)
    processed_set.add(norm_path)

def process_recursive(name, cwd, visited, processed_set):
    norm_path = normalize_path(cwd)
    
    for skip in SKIPPED_REPOS:
        if skip in name or skip in cwd:
            return

    if norm_path in processed_set:
        return

    real_cwd = os.path.realpath(cwd)
    if real_cwd in visited:
        return
    visited.add(real_cwd)
    
    # Initialize submodules so we can see them
    run_command("git submodule update --init", cwd, ignore_errors=True)

    output = run_command("git submodule status", cwd, ignore_errors=True)
    
    submodules = []
    if output:
        for line in output.split('\n'):
            parts = line.strip().split()
            if len(parts) >= 2:
                sub_path = parts[1]
                sub_abs_path = os.path.join(cwd, sub_path)
                submodules.append((sub_path, sub_abs_path))
    
    # Depth-first: Process children
    for sub_path, sub_abs_path in submodules:
        process_recursive(f"{name}/{sub_path}", sub_abs_path, visited, processed_set)
    
    # Process self
    if name != "ROOT": 
        process_repo(name, cwd, processed_set)

def main():
    print(f"Root: {ROOT_DIR}")
    
    # Don't delete PROCESSED_FILE if we want to resume
    # But for this specific run request, maybe we should clear it?
    # No, since we want to resume from the timeout, we should KEEP it.
    
    processed_set = load_processed()
    print(f"Loaded {len(processed_set)} processed repos.")
    
    visited = set()
    
    print("Starting recursive update...")
    process_recursive("ROOT", ROOT_DIR, visited, processed_set)
    
    # Finally process root
    process_repo("ROOT", ROOT_DIR, processed_set)
    
    print("\nAll done.")

if __name__ == "__main__":
    main()
