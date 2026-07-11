import os
import subprocess
import sys
import json
import time

LOG_FILE = "sync_log.txt"

def log(msg):
    print(msg)
    try:
        with open(LOG_FILE, "a", encoding="utf-8") as f:
            f.write(f"[{time.strftime('%Y-%m-%d %H:%M:%S')}] {msg}\n")
    except:
        pass

def run_cmd(cmd, cwd=None, ignore_errors=True, timeout=600):
    try:
        res = subprocess.run(cmd, cwd=cwd, shell=True, capture_output=True, text=True, encoding="utf-8", errors="replace", timeout=timeout)
        if not ignore_errors and res.returncode != 0:
            return None, f"Error: {res.stderr}"
        return res.stdout.strip(), None
    except subprocess.TimeoutExpired:
        log(f"TIMEOUT: {cmd} in {cwd}")
        return None, "Timeout"
    except Exception as e:
        return None, str(e)

def get_default_branch(cwd):
    branches_out, _ = run_cmd("git branch -a", cwd=cwd)
    if not branches_out: return "main"
    if "remotes/origin/main" in branches_out: return "main"
    if "remotes/origin/master" in branches_out: return "master"
    if "* main" in branches_out: return "main"
    if "* master" in branches_out: return "master"
    out, _ = run_cmd("git rev-parse --abbrev-ref HEAD", cwd=cwd)
    return out if out and out != "HEAD" else "main"

def resolve_conflicts(cwd, strategy="theirs"):
    out, _ = run_cmd("git diff --name-only --diff-filter=U", cwd=cwd)
    if out:
        for file in out.splitlines():
            file = file.strip()
            if not file: continue
            run_cmd(f"git checkout --{strategy} \"{file}\"", cwd=cwd)
            run_cmd(f"git add \"{file}\"", cwd=cwd)
        run_cmd("git commit -m \"Intelligent conflict resolution\"", cwd=cwd)

def sync_repo(cwd, is_root=False):
    log(f"Processing: {cwd}")
    if not os.path.exists(os.path.join(cwd, ".git")): 
        log(f"Skipping {cwd}, no .git")
        return

    # Stash
    log(f"[{cwd}] Stashing local changes...")
    run_cmd("git stash --include-untracked", cwd=cwd)

    # 1. Fetch
    log(f"[{cwd}] Fetching...")
    run_cmd("git fetch --all --tags --prune", cwd=cwd)

    default_branch = get_default_branch(cwd)
    run_cmd(f"git checkout {default_branch}", cwd=cwd)

    # 2. Upstream Sync
    remotes, _ = run_cmd("git remote", cwd=cwd)
    if remotes and "upstream" in remotes.split():
        log(f"[{cwd}] Syncing with upstream...")
        out, _ = run_cmd(f"git merge upstream/{default_branch} -m \"Sync upstream\"", cwd=cwd)
        if out and "Conflict" in out:
            resolve_conflicts(cwd, strategy="theirs")

    # 3. Recursive Submodule Update (only if root or top level)
    if is_root:
        log(f"[{cwd}] Recursive submodule update...")
        # Note: this can be very slow
        run_cmd("git submodule update --init --recursive", cwd=cwd, timeout=1200)

    # 4. Dual-Direction Merge
    local_branches_out, _ = run_cmd("git branch --format=%(refname:short)", cwd=cwd)
    local_branches = [b.strip() for b in local_branches_out.splitlines() if b.strip()] if local_branches_out else []
    
    skip_branches = [default_branch, "main", "master", "HEAD"]
    
    for fb in local_branches:
        if fb in skip_branches: continue
        
        # Forward Merge: feature -> main
        log(f"[{cwd}] Forward Merge: {fb} -> {default_branch}")
        run_cmd(f"git checkout {default_branch}", cwd=cwd)
        out, _ = run_cmd(f"git merge {fb} -m \"Forward merge {fb}\"", cwd=cwd)
        if out and "Conflict" in out:
            resolve_conflicts(cwd, strategy="theirs")
            
        # Reverse Merge: main -> feature
        log(f"[{cwd}] Reverse Merge: {default_branch} -> {fb}")
        run_cmd(f"git checkout {fb}", cwd=cwd)
        out, _ = run_cmd(f"git merge {default_branch} -m \"Reverse merge {default_branch}\"", cwd=cwd)
        if out and "Conflict" in out:
            resolve_conflicts(cwd, strategy="theirs")

    # Back to default
    run_cmd(f"git checkout {default_branch}", cwd=cwd)

    # Pop Stash
    log(f"[{cwd}] Popping stash...")
    run_cmd("git stash pop", cwd=cwd)

def find_repos(root):
    repos = [root]
    out, _ = run_cmd("git submodule --quiet foreach --recursive \"echo $displaypath\"", cwd=root)
    if out:
        for path in out.splitlines():
            full_path = os.path.join(root, path.strip())
            if os.path.exists(full_path):
                repos.append(full_path)
    return list(set(repos))

if __name__ == "__main__":
    root_dir = os.getcwd()
    with open(LOG_FILE, "a", encoding="utf-8") as f:
        f.write(f"Sync RESTARTED at {time.strftime('%Y-%m-%d %H:%M:%S')}\n")

    if os.path.exists("remaining_repos.txt"):
        with open("remaining_repos.txt", "r", encoding="utf-8") as f:
            all_repos = [line.strip() for line in f if line.strip()]
        # os.remove("remaining_repos.txt") # Keep it for safety in case of another crash
    elif len(sys.argv) > 1:
        all_repos = [os.path.abspath(r) for r in sys.argv[1:] if os.path.exists(r)]
    else:
        all_repos = find_repos(root_dir)
        all_repos.sort(key=lambda x: x.count(os.sep))
    
    for repo in all_repos:
        is_root = (repo == root_dir)
        try:
            sync_repo(repo, is_root)
        except Exception as e:
            log(f"CRITICAL ERROR processing {repo}: {e}")

    log("EXECUTIVE SYNC Step 1 & 2 Completed.")
