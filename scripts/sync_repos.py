import os
import subprocess
import sys

# Configuration
ROOT_DIR = os.getcwd()
TARGET_USER = "robertpelloni"


def run_command(command, cwd):
    """Runs a shell command in a specific directory."""
    try:
        result = subprocess.run(
            command, cwd=cwd, shell=True, capture_output=True, text=True
        )
        return result
    except Exception as e:
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
    print(f"\nProcessing: {path}")

    # 1. Status Check & Auto-Commit
    status = run_command("git status --porcelain", path)
    if status and status.stdout.strip():
        print(f"  [DIRTY] Found uncommitted changes in {path}")
        run_command("git add .", path)
        commit = run_command(
            'git commit -m "chore: auto-save uncommitted changes during massive refactor"',
            path,
        )
        if commit.returncode == 0:
            print("  [ACTION] Committed changes.")
            push = run_command("git push origin HEAD", path)
            if push.returncode == 0:
                print("  [ACTION] Pushed changes.")
            else:
                print(f"  [ERROR] Push failed: {push.stderr}")
    else:
        print("  [CLEAN] No uncommitted changes.")

    # 2. Robert Pelloni Feature Branch Hunt
    remote_url = get_remote_url(path)
    if TARGET_USER.lower() in remote_url.lower():
        print(f"  [TARGET] Owned by {TARGET_USER}. Checking branches...")
        run_command("git fetch --all", path)

        # Get current branch
        curr = run_command("git branch --show-current", path)
        current_branch = curr.stdout.strip() if curr else ""

        # Check for unmerged feature branches is complex.
        # For now, let's ensure we are on main/master and up to date.

        target_branch = "main"
        # Check if master exists instead
        branches = run_command("git branch -r", path)
        if (
            branches
            and "origin/master" in branches.stdout
            and "origin/main" not in branches.stdout
        ):
            target_branch = "master"

        print(f"  [INFO] Target branch is {target_branch}")

        # If we are on a feature branch (not main/master/HEAD)
        if current_branch and current_branch not in ["main", "master", "HEAD"]:
            print(f"  [BRANCH] Currently on feature branch: {current_branch}")
            # Try to switch to target and merge
            print(
                f"  [ACTION] Checking out {target_branch} and merging {current_branch}..."
            )
            run_command(f"git checkout {target_branch}", path)
            run_command(f"git pull origin {target_branch}", path)

            merge = run_command(f"git merge {current_branch}", path)
            if merge.returncode == 0:
                print(f"  [SUCCESS] Merged {current_branch} into {target_branch}")
                run_command(f"git push origin {target_branch}", path)
            else:
                print(f"  [CONFLICT] Merge conflict or failure. Aborting merge.")
                run_command("git merge --abort", path)
                run_command(f"git checkout {current_branch}", path)  # Switch back

    # 3. Pull latest changes (Global Update)
    # We do this for everyone to ensure we are up to date
    # Only pull if we are on a valid branch
    curr = run_command("git branch --show-current", path)
    if curr and curr.stdout.strip():
        branch = curr.stdout.strip()
        print(f"  [UPDATE] Pulling latest for branch {branch}...")
        pull = run_command(f"git pull origin {branch}", path)
        if pull.returncode != 0:
            print(
                f"  [WARN] Pull failed (might be detached head or diverged): {pull.stderr}"
            )


def recursive_crawl(start_path):
    # Walk the directory tree
    # We used os.walk but we need to be careful not to traverse into .git folders themselves
    # or loop infinitely with symlinks (though rare in submodules).

    git_repos = []

    for root, dirs, files in os.walk(start_path):
        if ".git" in dirs:
            # This directory is a git repo root
            git_repos.append(root)
            # Don't traverse into .git
            dirs.remove(".git")

            # Important: os.walk descends into subdirs.
            # If a repo is inside another repo (submodule), we want to process it.
            # But the 'root' itself is the repo path.

    return git_repos


if __name__ == "__main__":
    print("Starting Deep Synchronization...")

    # 1. Find all repos
    repos = recursive_crawl(ROOT_DIR)

    # Sort by length of path descending so we handle deepest leaves first?
    # Actually, usually we update leaves first, then parents.
    # But for 'status check' order doesn't matter much.
    # For 'committing pointers', we MUST do leaves first.
    repos.sort(key=lambda x: len(x), reverse=True)

    print(f"Found {len(repos)} repositories.")

    for repo in repos:
        # Skip the root repo for the very end (manual step)
        if os.path.abspath(repo) == os.path.abspath(ROOT_DIR):
            continue

        handle_repo(repo)

    print("\n[DONE] Child processing complete. Ready for Root update.")
