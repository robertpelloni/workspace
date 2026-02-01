import subprocess
import os
import sys

def run_command(cmd, cwd):
    try:
        # print(f"Running: {cmd} in {cwd}")
        result = subprocess.run(cmd, cwd=cwd, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        # print(f"Error in {cwd}: {e.stderr}")
        raise e

def get_default_branch(cwd):
    try:
        output = run_command("git remote show origin", cwd)
        for line in output.split('\n'):
            if "HEAD branch:" in line:
                return line.split(":")[1].strip()
    except:
        # Try to guess
        try:
            branches = run_command("git branch -r", cwd)
            if "origin/main" in branches:
                return "main"
            if "origin/master" in branches:
                return "master"
        except:
            pass
    return "main"

def get_current_branch(cwd):
    try:
        return run_command("git rev-parse --abbrev-ref HEAD", cwd)
    except:
        return None

def process_repo(path):
    print(f"Processing {path}...")
    full_path = os.path.abspath(path)
    
    if not os.path.exists(full_path):
        print(f"Skipping {path}, does not exist.")
        return

    # Check if it is a git repo
    if not os.path.exists(os.path.join(full_path, ".git")) and not os.path.isfile(os.path.join(full_path, ".git")):
         print(f"Skipping {path}, not a git repo.")
         return

    # Commit any current changes on the current branch first
    current_branch = get_current_branch(full_path)
    if not current_branch:
        print(f"Could not determine branch for {path}")
        return

    print(f"Current branch: {current_branch}")

    # Check for changes and commit them to current branch
    try:
        status = run_command("git status --porcelain", full_path)
        if status:
            print(f"Changes detected in {path} on {current_branch}. Committing...")
            run_command("git add .", full_path)
            run_command(f'git commit -m "chore: save progress on {current_branch}"', full_path)
            # Push the feature branch too, just in case
            try:
                run_command(f"git push origin {current_branch}", full_path)
            except:
                print(f"Failed to push {current_branch} in {path}, maybe no upstream.")
    except Exception as e:
        print(f"Error checking status/committing in {path}: {e}")

    default_branch = get_default_branch(full_path)
    print(f"Default branch: {default_branch}")

    if current_branch != default_branch:
        print(f"Merging {current_branch} into {default_branch}...")
        try:
            run_command(f"git checkout {default_branch}", full_path)
            run_command(f"git pull origin {default_branch}", full_path)
            
            # Merge
            try:
                run_command(f"git merge {current_branch}", full_path)
                print("Merge successful.")
            except subprocess.CalledProcessError:
                print("Merge conflict detected. Attempting to resolve favoring changes...")
                # Try to resolve conflicts? 
                # For now, let's abort and try Xtheirs? User said "without losing progress". 
                # Usually Xtheirs might lose 'main' progress if they conflict.
                # But typically we want the feature branch changes.
                run_command("git merge --abort", full_path)
                # Fail gracefully?
                print(f"CRITICAL: Merge conflict in {path}. Left on {default_branch}. Please resolve manually.")
                # Switch back to feature branch?
                run_command(f"git checkout {current_branch}", full_path)
                return

            run_command(f"git push origin {default_branch}", full_path)
            
            # Switch back to feature branch? Or stay on main?
            # User said "merge it into main". Usually implies we move forward with main.
            # But let's stay on main to ensure parent repo sees the commit on main.
            
        except Exception as e:
            print(f"Failed to merge in {path}: {e}")
            # Try to recover
            try:
                run_command(f"git checkout {current_branch}", full_path)
            except:
                pass
    else:
        # Already on default branch
        try:
            run_command(f"git pull origin {default_branch}", full_path)
            # Check if we have unpushed commits (we might have committed above)
            # or if pull brought new things.
            # If we committed above, we need to push.
            run_command(f"git push origin {default_branch}", full_path)
            print(f"Updated {default_branch} in {path}.")
        except Exception as e:
            print(f"Failed to update {default_branch} in {path}: {e}")

def main():
    # Get submodules
    submodules = []
    try:
        # Use git submodule status --recursive which is safer/easier to parse
        # It might return non-zero if some submodules are broken, but we can still use the output
        try:
            output = subprocess.check_output("git submodule status --recursive", shell=True, text=True)
        except subprocess.CalledProcessError as e:
            output = e.output # Use whatever output we got

        for line in output.split('\n'):
            line = line.strip()
            if not line:
                continue
            # Output format: [+-U]<sha1> <path> (<describe>)
            parts = line.split()
            if len(parts) >= 2:
                submodules.append(parts[1])

    except Exception as e:
        print(f"Error listing submodules: {e}")
    
    # Filter empty and remove duplicates
    submodules = list(set([s.strip() for s in submodules if s.strip()]))
    
    # Sort by length descending to process deepest first
    submodules.sort(key=len, reverse=True)
    
    # Add root at the end
    submodules.append(".")

    for sm in submodules:
        if sm == ".":
            path = "."
        else:
            path = sm
        
        process_repo(path)

if __name__ == "__main__":
    main()
