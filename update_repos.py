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
        return "main" # Fallback
    return "main"

def process_repo(path):
    print(f"Processing {path}...")
    full_path = os.path.abspath(path)
    
    if not os.path.exists(full_path):
        print(f"Skipping {path}, does not exist.")
        return

    # Check if it is a git repo
    if not os.path.exists(os.path.join(full_path, ".git")) and not os.path.isfile(os.path.join(full_path, ".git")):
         # .git can be a file in submodules
         print(f"Skipping {path}, not a git repo.")
         return

    # Check for changes
    try:
        status = run_command("git status --porcelain", full_path)
    except Exception as e:
        print(f"Failed to get status for {path}: {e}")
        return

    if not status:
        print(f"No changes in {path}.")
        return

    print(f"Changes detected in {path}.")
    
    # Detect branch
    branch = get_default_branch(full_path)
    print(f"Detected branch: {branch}")

    try:
        # Checkout branch
        run_command(f"git checkout {branch}", full_path)
        # Pull latest (in case we were behind)
        run_command("git pull", full_path)
        # Add all
        run_command("git add .", full_path)
        # Check status again to see if there is anything to commit
        status_after_add = run_command("git status --porcelain", full_path)
        if status_after_add:
            # Commit
            run_command('git commit -m "chore: update submodules"', full_path)
            # Push
            run_command("git push", full_path)
            print(f"Successfully updated {path}.")
        else:
            print(f"Nothing to commit in {path} after checkout/pull.")
            # If we just pulled and it matched what was there, fine. 
            # But wait, if 'git add .' added nothing, it implies the checkout/pull reverted the changes?
            # Or the changes were already in the branch?
            # If `git status` showed dirty before, it was likely a submodule pointer change.
            # `git add .` stages it.
            # So `status_after_add` should be non-empty.
            pass
            
    except Exception as e:
        print(f"Failed to update {path}: {e}")

def main():
    # Get submodules
    try:
        # Use single quotes for the command to avoid interpolation issues
        output = subprocess.check_output("git submodule foreach --recursive --quiet 'echo $displaypath'", shell=True, text=True)
        submodules = output.strip().split('\n')
    except Exception as e:
        print(f"Error listing submodules: {e}")
        submodules = []

    # Filter empty
    submodules = [s.strip() for s in submodules if s.strip()]
    
    # Sort by length descending
    submodules.sort(key=len, reverse=True)
    
    # Add root at the end (last to be processed)
    submodules.append(".")

    for sm in submodules:
        if sm == ".":
            path = "."
        else:
            path = sm
        
        process_repo(path)

if __name__ == "__main__":
    main()
