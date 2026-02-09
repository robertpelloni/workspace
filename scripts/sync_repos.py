import os
import subprocess
import sys

# Configuration
ROOT_DIR = os.getcwd()
TARGET_USER = "robertpelloni"
TIMEOUT = 60  # seconds per command

def run_command(command, cwd):
    """Runs a shell command in a specific directory."""
    try:
        # print(f"[{cwd}] Executing: {command}")
        result = subprocess.run(
            command, cwd=cwd, shell=True, capture_output=True, text=True, timeout=TIMEOUT
        )
        return result
    except subprocess.TimeoutExpired:
        print(f"  [TIMEOUT] Command '{command}' timed out after {TIMEOUT}s")
        return None
    except Exception as e:
        print(f"  [ERROR] Execution failed: {e}")
        return None


def is_git_repo(path):
    """Checks if a directory is a git repository."""
    return os.path.exists(os.path.join(path, ".git"))


def get_remote_url(path):
    """Gets the origin remote URL."""
    res = run_command("git remote get-url origin", path)
    if res and res.returncode == 0:
        return res.stdout.strip()
    return ""


def handle_repo(path):
    # print(f"\nProcessing: {path}")

    # 1. Status Check & Auto-Commit
    status = run_command("git status --porcelain", path)
    if status and status.stdout.strip():
        print(f"\n{path}: [DIRTY] Found uncommitted changes.")
        run_command("git add .", path)
        commit = run_command(
            'git commit -m "chore: auto-save uncommitted changes during massive refactor"',
            path,
        )
        if commit and commit.returncode == 0:
            print(f"{path}: [ACTION] Committed changes.")
            push = run_command("git push origin HEAD", path)
            if push and push.returncode == 0:
                print(f"{path}: [ACTION] Pushed changes.")
            else:
                stderr = push.stderr if push else "Unknown error"
                print(f"{path}: [ERROR] Push failed: {stderr}")
    # else:
    #     print(f"{path}: [CLEAN]")

    # 2. Robert Pelloni Feature Branch Hunt
    remote_url = get_remote_url(path)
    if TARGET_USER.lower() in remote_url.lower():
        # print(f"{path}: [TARGET] Owned by {TARGET_USER}.")
        run_command("git fetch --all", path)

        # Get current branch
        curr = run_command("git branch --show-current", path)
        current_branch = curr.stdout.strip() if curr else ""

        target_branch = "main"
        # Check if master exists instead
        branches = run_command("git branch -r", path)
        if branches and "origin/master" in branches.stdout and "origin/main" not in branches.stdout:
            target_branch = "master"

        # If we are on a feature branch (not main/master/HEAD)
        if current_branch and current_branch not in ["main", "master", "HEAD", target_branch]:
            print(f"{path}: [BRANCH] Currently on feature branch: {current_branch}")
            # Try to switch to target and merge
            print(f"{path}: [ACTION] Checking out {target_branch} and merging {current_branch}...")
            
            run_command(f"git checkout {target_branch}", path)
            run_command(f"git pull origin {target_branch}", path)

            merge = run_command(f"git merge {current_branch}", path)
            if merge and merge.returncode == 0:
                print(f"{path}: [SUCCESS] Merged {current_branch} into {target_branch}")
                run_command(f"git push origin {target_branch}", path)
            else:
                print(f"{path}: [CONFLICT] Merge conflict or failure. Aborting merge.")
                run_command("git merge --abort", path)
                run_command(f"git checkout {current_branch}", path)  # Switch back

    # 3. Pull latest changes (Global Update)
    curr = run_command("git branch --show-current", path)
    if curr and curr.stdout.strip():
        branch = curr.stdout.strip()
        # print(f"{path}: [UPDATE] Pulling latest for branch {branch}...")
        pull = run_command(f"git pull origin {branch}", path)
        if pull and pull.returncode != 0:
             # Only warn if it's a real error, not just 'up to date'
             pass


def recursive_crawl(start_path):
    git_repos = []
    
    ignore_dirs = {
        '.git', 'node_modules', 'dist', 'build', '.venv', 'venv', 
        'target', '__pycache__', 'bin', 'obj', '.idea', '.vscode', 
        'pkg', 'vendor', 'Debug', 'Release', 'x64', 'x86'
    }

    print("Scanning for repositories...")
    for root, dirs, files in os.walk(start_path):
        dirs[:] = [d for d in dirs if d not in ignore_dirs]

        if ".git" in dirs or ".git" in files:
            git_repos.append(root)
            if ".git" in dirs:
                dirs.remove(".git")

    return git_repos


if __name__ == "__main__":
    print("Starting Deep Synchronization...")

    repos = recursive_crawl(ROOT_DIR)
    # Sort: process children first?
    repos.sort(key=lambda x: len(x), reverse=True)

    print(f"Found {len(repos)} repositories. Processing...")

    for i, repo in enumerate(repos):
        if os.path.abspath(repo) == os.path.abspath(ROOT_DIR):
            continue
        
        # print(f"[{i+1}/{len(repos)}] {repo}")
        try:
            handle_repo(repo)
        except Exception as e:
            print(f"{repo}: [ERROR] {e}")

    print("\n[DONE] Child processing complete.")