import os, subprocess, configparser, sys

def run(cmd, cwd=None, timeout=120):
    try:
        r = subprocess.run(cmd, shell=True, cwd=cwd, capture_output=True, text=True, encoding="utf-8", errors="replace", timeout=timeout)
        return r.returncode, r.stdout.strip(), r.stderr.strip()
    except subprocess.TimeoutExpired:
        return -1, "", "TIMEOUT"
    except Exception as e:
        return -1, "", str(e)

def sync_repo(path):
    name = os.path.basename(path)
    print(f"\n{'='*60}\n>>> {name}\n{'='*60}")
    
    # Stash/save
    run("git add -A && git commit -m \"chore: auto-save before sync\"", cwd=path)
    
    # Fetch
    rc, out, err = run("git fetch --all --prune --quiet", cwd=path)
    if rc == -1 and "TIMEOUT" in err:
        print(f"  SKIP: fetch timed out")
        return
    
    # Get default branch
    rc, out, err = run("git rev-parse --abbrev-ref HEAD", cwd=path)
    branch = out if out in ("main", "master") else "main"
    
    # Ensure on default branch
    run(f"git checkout {branch}", cwd=path)
    
    # Pull origin
    rc, out, err = run(f"git pull origin {branch} --ff-only", cwd=path)
    if rc != 0:
        rc, out, err = run(f"git pull origin {branch} --no-edit", cwd=path)
    print(f"  pull origin/{branch}: {'OK' if rc == 0 else 'SKIP'}")
    
    # Merge upstream if present
    rc, out, err = run("git remote", cwd=path)
    if "upstream" in (out or "").split():
        rc2, out2, err2 = run(f"git merge upstream/{branch} --no-edit", cwd=path)
        if rc2 != 0:
            # Resolve conflicts with ours
            run("git diff --name-only --diff-filter=U", cwd=path)
            rc3, files, _ = run("git diff --name-only --diff-filter=U", cwd=path)
            if files:
                for f in files.splitlines():
                    run(f"git checkout --ours \"{f}\"", cwd=path)
                    run(f"git add \"{f}\"", cwd=path)
                run("git commit --no-edit", cwd=path)
        print(f"  merge upstream/{branch}: {'OK' if rc2 == 0 else 'resolved'}")
    
    # Push
    rc, out, err = run(f"git push origin {branch}", cwd=path)
    print(f"  push: {'OK' if rc == 0 else 'SKIP'}")

def main():
    root = os.getcwd()
    config = configparser.ConfigParser()
    config.read(".gitmodules")
    
    repos = []
    for section in config.sections():
        path = config.get(section, "path", fallback=None)
        if path and os.path.isdir(os.path.join(root, path)):
            repos.append(os.path.join(root, path))
    
    # Also sync root
    print(f"Found {len(repos)} submodules. Syncing...")
    
    # Sync root first
    sync_repo(root)
    
    for repo_path in repos:
        sync_repo(repo_path)
    
    print("\n\nDone. All submodules synced.")

if __name__ == "__main__":
    main()
