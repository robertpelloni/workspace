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

def get_submodules(cwd):
    # Returns list of paths relative to cwd
    submodules = []
    try:
        # git ls-files --stage | grep ^160000
        # Output: 160000 <hash> <stage> <path>
        output = run_command("git ls-files --stage", cwd)
        if output:
            for line in output.split('\n'):
                if line.startswith("160000"):
                    parts = line.split('\t')
                    if len(parts) >= 2:
                        path = parts[1]
                        submodules.append(path)
    except Exception as e:
        print(f"Error listing submodules in {cwd}: {e}")
    return submodules

def determine_default_branch(cwd):
    try:
        remotes = run_command("git branch -r", cwd)
        if not remotes: return "main"
        
        candidates = ["origin/main", "origin/master", "origin/develop"]
        for cand in candidates:
            if cand in remotes:
                return cand.split('/')[1]
        
        # Fallback to whatever HEAD points to if available
        head = run_command("git symbolic-ref refs/remotes/origin/HEAD", cwd)
        if head:
            return head.split('/')[-1]
    except:
        pass
    return "main"

def process_repo(path):
    full_path = os.path.abspath(path)
    print(f"Processing: {path}")
    
    if "baw" in path.split(os.sep) or "borg" in path.split(os.sep):
        print(f"  [INFO] Skipping {path} (excluded)")
        return

    if not os.path.exists(full_path):
        print(f"  [WARN] Path does not exist: {path}")
        return

    # Check if it's a git repo
    if not os.path.exists(os.path.join(full_path, ".git")) and not os.path.isfile(os.path.join(full_path, ".git")):
        print(f"  [WARN] Not a git repo: {path}")
        return

    # Recurse first (depth-first)
    submodules = get_submodules(full_path)
    for sm in submodules:
        process_repo(os.path.join(full_path, sm))

    try:
        # Update current repo
        print(f"  Updating {path}...")
        
        # Fetch all
        run_command("git fetch --all", full_path, check=False)

        default_branch = determine_default_branch(full_path)
        
        # Get current branch
        try:
            current_branch = run_command("git symbolic-ref --short HEAD", full_path)
        except:
            current_branch = None # Detached HEAD

        print(f"  Branch: {current_branch} (Default: {default_branch})")

        if current_branch and current_branch != default_branch:
             print(f"  [INFO] Merging feature branch '{current_branch}' into '{default_branch}'")
             run_command(f"git checkout {default_branch}", full_path)
             run_command(f"git pull origin {default_branch}", full_path)
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
                try:
                    run_command(f"git checkout -b {default_branch} origin/{default_branch}", full_path)
                except:
                     print(f"  [ERROR] Could not checkout {default_branch}")
                     return

        # Now on default_branch. Pull.
        print(f"  [INFO] Pulling {default_branch}")
        try:
            run_command(f"git pull origin {default_branch}", full_path)
        except:
            print(f"  [WARN] Pull failed (no upstream?)")

        # Check for uncommitted changes
        status = run_command("git status --porcelain", full_path)
        if status:
            print(f"  [INFO] Changes detected. Committing...")
            try:
                # We need to add everything.
                # If we are in root, 'git add .' might fail on 'bobtorrent/nul'.
                # But we can try 'git add -u' (updates known) + 'git add .' (new).
                # Or just 'git add .' and ignore errors?
                run_command("git add .", full_path)
                run_command('git commit -m "chore: update submodules and merge features"', full_path)
            except Exception as e:
                print(f"  [WARN] Commit failed: {e}")

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
    # Start from root
    process_repo(".")

if __name__ == "__main__":
    main()