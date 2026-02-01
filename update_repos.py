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
                branch = line.split(":")[1].strip()
                # Sanity check for weird branch names or if it doesn't exist
                if branch == "nigger": # Explicitly handling the anomaly seen in logs
                    # Check if 'main' or 'master' exists remotely/locally instead
                    try:
                        run_command("git rev-parse --verify main", cwd)
                        return "main"
                    except:
                        try:
                            run_command("git rev-parse --verify master", cwd)
                            return "master"
                        except:
                            pass # Fallback to whatever was found or main
                return branch
    except:
        pass
    
    # Fallback/Guess
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
         # .git can be a file in submodules
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
            try:
                run_command("git add .", full_path)
                run_command(f'git commit -m "chore: save progress on {current_branch}"', full_path)
            except Exception as e:
                print(f"Commit failed in {path}: {e}")
            
            # Push the feature branch too, just in case
            try:
                run_command(f"git push origin {current_branch}", full_path)
            except subprocess.CalledProcessError:
                # Try setting upstream
                try:
                    print(f"Push failed, attempting to set upstream for {current_branch}...")
                    run_command(f"git push -u origin {current_branch}", full_path)
                except Exception as e:
                    print(f"Failed to push {current_branch} in {path} even with -u: {e}")
    except Exception as e:
        print(f"Error checking status/committing in {path}: {e}")

    default_branch = get_default_branch(full_path)
    print(f"Default branch: {default_branch}")

    if current_branch != default_branch:
        print(f"Merging {current_branch} into {default_branch}...")
        try:
            # Checkout default
            try:
                run_command(f"git checkout {default_branch}", full_path)
            except subprocess.CalledProcessError:
                # If checkout fails (e.g. branch doesn't exist locally), try creating it tracking origin
                try:
                    run_command(f"git checkout -b {default_branch} origin/{default_branch}", full_path)
                except:
                    print(f"Could not checkout {default_branch} in {path}. Aborting merge.")
                    return

            # Pull latest default
            try:
                run_command(f"git pull origin {default_branch}", full_path)
            except:
                print(f"Pull failed for {default_branch} in {path}.")

            # Merge
            try:
                run_command(f"git merge {current_branch}", full_path)
                print("Merge successful.")
            except subprocess.CalledProcessError:
                print("Merge conflict detected. Attempting to resolve favoring changes...")
                run_command("git merge --abort", full_path)
                print(f"CRITICAL: Merge conflict in {path}. Left on {default_branch}. Please resolve manually.")
                run_command(f"git checkout {current_branch}", full_path)
                return

            # Push default
            try:
                run_command(f"git push origin {default_branch}", full_path)
            except subprocess.CalledProcessError:
                 try:
                    run_command(f"git push -u origin {default_branch}", full_path)
                 except Exception as e:
                    print(f"Failed to push {default_branch} in {path}: {e}")
            
        except Exception as e:
            print(f"Failed to merge in {path}: {e}")
            try:
                run_command(f"git checkout {current_branch}", full_path)
            except:
                pass
    else:
        # Already on default branch
        try:
            run_command(f"git pull origin {default_branch}", full_path)
            # Push
            try:
                run_command(f"git push origin {default_branch}", full_path)
                print(f"Updated {default_branch} in {path}.")
            except subprocess.CalledProcessError:
                try:
                    run_command(f"git push -u origin {default_branch}", full_path)
                    print(f"Updated {default_branch} in {path} (upstream set).")
                except Exception as e:
                    print(f"Failed to update {default_branch} in {path}: {e}")
        except Exception as e:
            print(f"Failed to update {default_branch} in {path}: {e}")

def main():
    # Get submodules
    submodules = []
    try:
        # Use git submodule status --recursive which is safer/easier to parse
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
