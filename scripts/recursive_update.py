import os
import subprocess
import sys

def run_command(cmd, cwd, check=True):
    try:
        # print(f"EXEC: {cmd} in {cwd}")
        result = subprocess.run(cmd, cwd=cwd, shell=True, check=check, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        # print(f"FAIL: {cmd} in {cwd} -> {e.stderr}")
        if check:
            raise e
        return None

def get_submodules():
    # Returns list of (path, url, branch)
    # We use git submodule status --recursive to get paths
    submodules = []
    try:
        output = run_command("git submodule status --recursive", os.getcwd())
        for line in output.split('\n'):
            if not line.strip(): continue
            parts = line.strip().split()
            path = parts[1]
            submodules.append(path)
    except Exception as e:
        print(f"Error listing submodules: {e}")
    return submodules

def determine_default_branch(cwd):
    # Try to find the default branch (main/master/develop)
    remotes = run_command("git branch -r", cwd)
    if not remotes: return "main"
    
    candidates = ["origin/main", "origin/master", "origin/develop"]
    for cand in candidates:
        if cand in remotes:
            return cand.split('/')[1]
    
    # Fallback to whatever HEAD points to if available
    try:
        head = run_command("git symbolic-ref refs/remotes/origin/HEAD", cwd)
        return head.split('/')[-1]
    except:
        pass

    return "main"

def process_repo(path):
    full_path = os.path.abspath(path)
    print(f"Processing: {path}")
    
    if not os.path.exists(full_path):
        print(f"  [WARN] Path does not exist: {path}")
        return

    # Check if it's a git repo
    if not os.path.exists(os.path.join(full_path, ".git")) and not os.path.isfile(os.path.join(full_path, ".git")):
        print(f"  [WARN] Not a git repo: {path}")
        return

    try:
        # Fetch all
        run_command("git fetch --all", full_path, check=False)

        default_branch = determine_default_branch(full_path)
        
        # Get current branch
        try:
            current_branch = run_command("git symbolic-ref --short HEAD", full_path)
        except:
            current_branch = None # Detached HEAD

        print(f"  Branch: {current_branch} (Default: {default_branch})")

        # Logic:
        # If detached, checkout default.
        # If on feature branch, merge to default.
        # Pull default.
        # Push default.

        target_branch = default_branch
        
        if current_branch and current_branch != default_branch:
             # We are on a named branch that is not default. Assume feature branch.
             print(f"  [INFO] Merging feature branch '{current_branch}' into '{default_branch}'")
             
             # Checkout default
             run_command(f"git checkout {default_branch}", full_path)
             run_command(f"git pull origin {default_branch}", full_path)
             
             # Merge
             try:
                 run_command(f"git merge {current_branch}", full_path)
             except subprocess.CalledProcessError:
                 print(f"  [ERROR] Merge conflict in {path}. Aborting merge.")
                 run_command("git merge --abort", full_path)
                 return
        elif not current_branch:
            # Detached HEAD
            print(f"  [INFO] Detached HEAD. Checking out {default_branch}")
            try:
                run_command(f"git checkout {default_branch}", full_path)
            except:
                # If local branch doesn't exist, create tracking
                try:
                    run_command(f"git checkout -b {default_branch} origin/{default_branch}", full_path)
                except:
                     print(f"  [ERROR] Could not checkout {default_branch}")
                     return

        # Now we are on default_branch. Pull.
        print(f"  [INFO] Pulling {default_branch}")
        try:
            run_command(f"git pull origin {default_branch}", full_path)
        except:
            print(f"  [WARN] Pull failed (no upstream?)")

        # Check for uncommitted changes (including submodule updates from children)
        status = run_command("git status --porcelain", full_path)
        if status:
            print(f"  [INFO] Changes detected. Committing...")
            run_command("git add .", full_path)
            try:
                run_command('git commit -m "chore: update submodules and merge features"', full_path)
            except:
                pass # Nothing to commit?

        # Push
        print(f"  [INFO] Pushing {default_branch}")
        try:
            run_command(f"git push origin {default_branch}", full_path)
        except:
             print(f"  [WARN] Push failed. Trying to set upstream.")
             try:
                 run_command(f"git push -u origin {default_branch}", full_path)
             except Exception as e:
                 print(f"  [ERROR] Push failed: {e}")

    except Exception as e:
        print(f"  [ERROR] Processing failed for {path}: {e}")

def main():
    root_dir = os.getcwd()
    submodules = get_submodules()
    
    # Sort by length descending (leaves first)
    submodules.sort(key=len, reverse=True)
    
    # Process submodules
    for sm in submodules:
        process_repo(sm)
        
    # Process root
    process_repo(".")

if __name__ == "__main__":
    main()
