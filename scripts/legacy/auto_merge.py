import os
import subprocess
import sys

def run_cmd(cmd, cwd=None, check=True):
    # print(f"[{cwd or '.'}] Running: {cmd}")
    res = subprocess.run(cmd, cwd=cwd, shell=True, capture_output=True, text=True, encoding='utf-8', errors='replace')
    if check and res.returncode != 0:
        raise Exception(f"Command '{cmd}' failed in {cwd} with exit code {res.returncode}:
{res.stderr}
{res.stdout}")
    return res.stdout.strip(), res.stderr.strip(), res.returncode

def is_git_repo(path):
    return os.path.isdir(os.path.join(path, '.git')) or os.path.isfile(os.path.join(path, '.git'))

def get_default_branch(path):
    out, _, _ = run_cmd("git rev-parse --abbrev-ref HEAD", cwd=path, check=False)
    if out == "HEAD" or not out:
        out, _, _ = run_cmd("git branch -r", cwd=path, check=False)
        if "origin/main" in out: return "main"
        if "origin/master" in out: return "master"
        return "main"
    if out in ['main', 'master']:
        return out
    # if currently on a feature branch, try to check if main or master exists
    branches, _, _ = run_cmd("git branch", cwd=path, check=False)
    if "main" in branches: return "main"
    if "master" in branches: return "master"
    return out

def get_all_repos(root_path):
    repos = []
    for dirpath, dirnames, filenames in os.walk(root_path):
        if '.git' in dirnames or '.git' in filenames:
            repos.append(dirpath)
    # Sort by depth so we can process children first or parent first.
    # The user said "Update all submodules inside all submodules and then commit and push each submodule so that the entire repo is clean."
    # Bottom-up approach:
    repos.sort(key=lambda x: len(x.split(os.sep)), reverse=True)
    return repos

def process_repo(repo_path):
    print(f"
Processing {repo_path}")
    
    # Check for uncommitted changes
    out, _, _ = run_cmd("git status --porcelain", cwd=repo_path, check=False)
    if out:
        print(f"Uncommitted changes in {repo_path}. Committing...")
        run_cmd("git add .", cwd=repo_path)
        run_cmd('git commit -m "chore: save local progress"', cwd=repo_path, check=False)

    default_branch = get_default_branch(repo_path)
    
    # fetch all
    run_cmd("git fetch --all", cwd=repo_path, check=False)
    
    # checkout default branch
    _, _, rc = run_cmd(f"git checkout {default_branch}", cwd=repo_path, check=False)
    if rc != 0:
        run_cmd(f"git checkout -b {default_branch} --track origin/{default_branch}", cwd=repo_path, check=False)
    
    # pull origin
    run_cmd(f"git pull origin {default_branch}", cwd=repo_path, check=False)

    # Handle upstream
    remotes, _, _ = run_cmd("git remote", cwd=repo_path, check=False)
    if "upstream" in remotes.split():
        out, _, _ = run_cmd("git branch -r", cwd=repo_path, check=False)
        if f"upstream/{default_branch}" in out:
            print("Merging upstream...")
            _, err, rc = run_cmd(f"git merge upstream/{default_branch}", cwd=repo_path, check=False)
            if rc != 0:
                print(f"CONFLICT in upstream merge in {repo_path}")
                return False

    # Get local branches to merge
    out, _, _ = run_cmd("git branch --format=%(refname:short)", cwd=repo_path, check=False)
    local_branches = [b.strip() for b in out.split('
') if b.strip()]
    
    # For any repos under robertpelloni, we want to merge local branches and remote branches that belong to robertpelloni
    remotes_v, _, _ = run_cmd("git remote -v", cwd=repo_path, check=False)
    is_robertpelloni = "robertpelloni" in remotes_v.lower()

    for branch in local_branches:
        if branch in [default_branch, "master", "main", "HEAD"]:
            continue
        print(f"Merging local branch {branch} into {default_branch}...")
        _, err, rc = run_cmd(f"git merge {branch}", cwd=repo_path, check=False)
        if rc != 0:
            print(f"CONFLICT merging local branch {branch} in {repo_path}")
            return False

    # Get remote branches to merge? "merge any and all feature branches also local to robertpelloni into main"
    if is_robertpelloni:
        out, _, _ = run_cmd("git branch -r", cwd=repo_path, check=False)
        remote_branches = [b.strip() for b in out.split('
') if b.strip()]
        for rb in remote_branches:
            if "origin/" in rb and not "HEAD" in rb:
                branch_name = rb.replace("origin/", "")
                if branch_name not in [default_branch, "master", "main"]:
                    print(f"Merging remote branch {rb} into {default_branch}...")
                    _, err, rc = run_cmd(f"git merge {rb}", cwd=repo_path, check=False)
                    if rc != 0:
                        print(f"CONFLICT merging remote branch {rb} in {repo_path}")
                        return False

    # commit and push
    out, _, _ = run_cmd("git status --porcelain", cwd=repo_path, check=False)
    if out:
        run_cmd("git add .", cwd=repo_path)
        run_cmd('git commit -m "chore: merge feature branches and upstream"', cwd=repo_path, check=False)
    
    if is_robertpelloni:
        print(f"Pushing {repo_path} to origin...")
        run_cmd(f"git push origin {default_branch}", cwd=repo_path, check=False)
        # Push to upstream as well if we have write access? Probably just origin.
    
    return True

def main():
    repos = get_all_repos(os.getcwd())
    for repo in repos:
        # Ignore skipped directories
        if any(skip in repo for skip in ["node_modules", "temp_defihacklabs", "borg", "vibeship-scanner", "voidsprite", ".venv", ".git\modules", ".cursor"]):
            continue
        if not process_repo(repo):
            print(f"Stopping at {repo} due to conflicts. Please resolve manually.")
            sys.exit(1)
    
    print("All repos processed successfully.")

if __name__ == "__main__":
    main()
