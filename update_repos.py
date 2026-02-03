import subprocess
import os
import sys

# Unbuffered output
sys.stdout.reconfigure(encoding='utf-8')
sys.stderr.reconfigure(encoding='utf-8')

def run_command(cmd, cwd, ignore_errors=False, timeout=None):
    try:
        print(f"[{cwd}] Executing: {cmd}")
        # Use shell=True for windows command compatibility
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
        print(f"[{cwd}] Command timed out: {cmd}")
        return None
    except subprocess.CalledProcessError as e:
        if not ignore_errors:
            print(f"[{cwd}] Error: {e.stderr.strip()}")
            # Don't raise, just return None to allow script to continue
            return None
        return None
    except Exception as e:
        print(f"[{cwd}] Unexpected error: {e}")
        return None

def get_submodules_recursive(root_path):
    """
    Returns a list of (relative_path, absolute_path) for all submodules,
    sorted by depth (deepest first).
    """
    submodules = []
    
    # Try to get all submodules recursively using git
    # We use 'git submodule status --recursive' which lists all initialized and uninitialized submodules
    # if they are known to the index.
    print(f"Scanning for submodules in {root_path}...")
    output = run_command("git submodule status --recursive", root_path, ignore_errors=True)
    
    if output:
        for line in output.split('\n'):
            # Format: [ -+]sha1 path (describe)
            # e.g. " 4ab591... ChamberLaw (heads/main)"
            parts = line.strip().split()
            if len(parts) >= 2:
                path = parts[1]
                abs_path = os.path.join(root_path, path)
                submodules.append((path, abs_path))
    
    # Sort by depth (number of separators), descending
    # This ensures we process children before parents
    submodules.sort(key=lambda x: x[0].replace('\\', '/').count('/'), reverse=True)
    
    return submodules

def get_default_branch(cwd):
    # Try to detect default branch
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

def process_repo(name, cwd):
    print(f"\n--- Processing {name} ---")
    
    if not os.path.exists(cwd):
        print(f"Directory {cwd} does not exist. Initializing...")
        # If it doesn't exist, we need to initialize it from the parent? 
        # Actually 'git submodule update --init' in parent should create it.
        # But we are processing depth-first. 
        # If this is a nested submodule, its parent exists (because we process deepest first? No, wait.)
        # If we sort by depth descending:
        # a/b/c
        # a/b
        # a
        # We process a/b/c first. If 'a/b' is not initialized, 'a/b/c' won't exist.
        # So we actually need to ensure parents are initialized before processing children?
        # BUT we need to commit children before parents.
        # This is the tricky part.
        
        # Strategy:
        # 1. We must ensure the submodule exists.
        #    We can try `git submodule update --init --recursive` at root, but that timed out.
        #    Maybe we assume the list we got from `git submodule status` implies they are at least known.
        
        # If the directory doesn't exist, we can't run git commands inside it.
        # We should probably run `git submodule update --init <path>` from the *parent* repo.
        # But determining the parent repo for a deep path is slightly complex.
        
        # For now, let's skip non-existent directories, 
        # BUT if we want to be thorough, we should initialize them.
        return

    # 1. Initialize/Update current submodule to ensure we have a working tree
    # run_command("git submodule update --init", cwd, ignore_errors=True) 
    # ^ No, we can't run this inside the submodule easily if it's bare or messy.
    # Actually, we usually run this from the parent. 
    # Let's assume the user wants to clean up *existing* checkouts mostly. 
    
    current_branch = get_current_branch(cwd)
    print(f"Current branch: {current_branch}")

    # 2. Check for uncommitted changes
    status = run_command("git status --porcelain", cwd, ignore_errors=True)
    if status:
        print(f"Uncommitted changes in {name}. Committing...")
        run_command("git add .", cwd)
        run_command('git commit -m "chore: save progress"', cwd)
    
    # 3. Determine target branch
    default_branch = get_default_branch(cwd)
    print(f"Target branch: {default_branch}")
    
    # 4. Handle detached HEAD or Feature Branch
    if current_branch == "HEAD":
        print(f"Repo is in detached HEAD state.")
        # Checkout default branch
        run_command(f"git checkout {default_branch}", cwd, ignore_errors=True)
        # Pull latest
        run_command(f"git pull origin {default_branch}", cwd, ignore_errors=True)
    elif current_branch != default_branch:
        print(f"Merging {current_branch} into {default_branch}...")
        run_command(f"git checkout {default_branch}", cwd, ignore_errors=True)
        run_command(f"git pull origin {default_branch}", cwd, ignore_errors=True)
        run_command(f"git merge {current_branch}", cwd, ignore_errors=True)
    else:
        print(f"Already on {default_branch}. Pulling...")
        run_command(f"git pull origin {default_branch}", cwd, ignore_errors=True)

    # 5. Push
    print(f"Pushing {default_branch}...")
    run_command(f"git push origin {default_branch}", cwd, ignore_errors=True)

def main():
    root_path = os.getcwd()
    print(f"Root: {root_path}")
    
    # 1. Scan
    submodules = get_submodules_recursive(root_path)
    print(f"Found {len(submodules)} submodules.")
    
    if not submodules:
        print("No submodules found or git error.")
        # Fallback: Just process root?
    
    # 2. Process Submodules (Deepest First)
    # This allows us to commit changes in children, then when we get to parents, 
    # the parent sees a modified submodule commit and can commit that.
    for rel_path, abs_path in submodules:
        process_repo(rel_path, abs_path)
        
    # 3. Process Root
    process_repo("ROOT", root_path)
    
    print("\nDone.")

if __name__ == "__main__":
    main()
