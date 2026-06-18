import os
import subprocess

def get_git_origin(repo_path):
    try:
        res = subprocess.run(
            ["git", "-C", repo_path, "remote", "get-url", "origin"],
            capture_output=True,
            text=True,
            check=True,
            encoding="utf-8",
            errors="replace"
        )
        return res.stdout.strip()
    except Exception:
        return None

def find_all_git_repos(root_dir):
    repos = []
    for dirpath, dirnames, filenames in os.walk(root_dir):
        # Skip common directories to avoid slow scans
        skip_dirs = [".venv", "node_modules", ".cursor", ".gemini", ".git"]
        # Modify dirnames in-place to avoid walking into skipped directories
        dirnames[:] = [d for d in dirnames if d not in skip_dirs]
        
        if ".git" in dirnames or os.path.exists(os.path.join(dirpath, ".git")):
            origin = get_git_origin(dirpath)
            repos.append((dirpath, origin))
    return repos

def main():
    root = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
    print(f"Scanning for Git repositories in: {root}")
    repos = find_all_git_repos(root)
    print(f"Found {len(repos)} Git repositories:")
    for path, origin in sorted(repos, key=lambda x: x[0]):
        rel_path = os.path.relpath(path, root)
        print(f"{rel_path} -> {origin}")

if __name__ == "__main__":
    main()
