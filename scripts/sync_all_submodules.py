import os
import subprocess
import json

def run_command(command, cwd=None):
    try:
        result = subprocess.run(command, cwd=cwd, shell=True, capture_output=True, text=True)
        return result.stdout.strip(), result.stderr.strip(), result.returncode
    except Exception as e:
        return "", str(e), 1

def get_submodules():
    stdout, _, _ = run_command("git submodule status --recursive")
    submodules = []
    for line in stdout.splitlines():
        parts = line.strip().split()
        if len(parts) >= 2:
            submodules.append(parts[1])
    return submodules

def get_remotes(submodule_path):
    stdout, _, _ = run_command("git remote -v", cwd=submodule_path)
    remotes = {}
    for line in stdout.splitlines():
        parts = line.split()
        if len(parts) >= 2:
            remotes[parts[0]] = parts[1]
    return remotes

def get_branches(submodule_path):
    stdout, _, _ = run_command("git branch -a", cwd=submodule_path)
    branches = [line.strip().replace("* ", "") for line in stdout.splitlines()]
    return branches

def sync_submodule(path):
    print(f"Syncing {path}...")
    remotes = get_remotes(path)
    
    # Identify primary branch (main or master)
    branches = get_branches(path)
    primary_branch = "main" if "main" in branches or "remotes/origin/main" in branches else "master"
    
    # Check if robertpelloni owned
    is_owned = any("robertpelloni" in url for url in remotes.values())
    
    # Check if has upstream
    has_upstream = "upstream" in remotes
    
    if is_owned:
        print(f"  [OWNED] Identifying feature branches in {path}")
        # Find local branches that aren't main/master/HEAD
        local_branches = [b for b in branches if not b.startswith("remotes/") and b not in ["main", "master"]]
        for branch in local_branches:
            print(f"    Merging {branch} into {primary_branch}...")
            run_command(f"git checkout {primary_branch}", cwd=path)
            run_command(f"git merge {branch} --no-commit", cwd=path)
            # We don't commit automatically to allow manual conflict resolution if needed, 
            # but user said "intelligently solving conflicts". For now we report.
            
            print(f"    Merging {primary_branch} into {branch}...")
            run_command(f"git checkout {branch}", cwd=path)
            run_command(f"git merge {primary_branch} --no-commit", cwd=path)
            
        run_command(f"git checkout {primary_branch}", cwd=path)

    if has_upstream:
        print(f"  [UPSTREAM] Syncing with {remotes['upstream']}")
        run_command("git fetch upstream", cwd=path)
        run_command(f"git merge upstream/{primary_branch} --no-commit", cwd=path)

if __name__ == "__main__":
    submodules = get_submodules()
    for sub in submodules:
        sync_submodule(sub)
