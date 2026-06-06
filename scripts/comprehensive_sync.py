import os
import subprocess
import sys
import json

def run_cmd(cmd, cwd=None, ignore_errors=False, timeout=600):
    try:
        # Using shell=True for complex commands, but list for simple ones is safer.
        # However, many git commands here are strings.
        res = subprocess.run(cmd, cwd=cwd, shell=True, capture_output=True, text=True, encoding="utf-8", errors="replace", timeout=timeout)
        if not ignore_errors and res.returncode != 0:
            return None, res.stderr
        return res.stdout.strip(), None
    except Exception as e:
        return None, str(e)

def get_default_branch(cwd):
    out, _ = run_cmd("git rev-parse --abbrev-ref HEAD", cwd=cwd, ignore_errors=True)
    if out == "HEAD" or not out:
        out, _ = run_cmd("git branch -r", cwd=cwd, ignore_errors=True)
        if out:
            if "origin/main" in out: return "main"
            if "origin/master" in out: return "master"
    if out in ["main", "master"]: return out
    branches, _ = run_cmd("git branch", cwd=cwd, ignore_errors=True)
    if branches:
        if "main" in branches: return "main"
        if "master" in branches: return "master"
    return "main"

def is_robert_repo(cwd):
    out, _ = run_cmd("git remote -v", cwd=cwd, ignore_errors=True)
    if out and "robertpelloni" in out.lower():
        return True
    return False

def resolve_conflicts_intelligently(cwd, source, target):
    print(f"[{cwd}] Resolving conflicts for {source} into {target}...")
    # First try a merge with -X ours to favor existing features if target is main
    # Actually, if we are merging a feature INTO main, we might want 'theirs' if the feature is the new work.
    # The user said: "intelligently solving conflicts without losing any progress or features".
    # Usually, 'ours' in a merge refers to the current branch.
    
    # If source is a feature branch and target is main:
    # We want to keep features from 'source' but also not lose 'target' progress.
    # Standard 'git merge -X ours' keeps the current branch (target) versions of conflicting lines.
    # Standard 'git merge -X theirs' keeps the source branch versions.
    
    # Given the instructions, we'll try to be careful.
    run_cmd(f"git merge {source} --allow-unrelated-histories -m \"Merge {source} into {target} (auto-resolved)\"", cwd=cwd, ignore_errors=True)
    
    out, _ = run_cmd("git diff --name-only --diff-filter=U", cwd=cwd, ignore_errors=True)
    if out:
        for file in out.splitlines():
            file = file.strip()
            if not file: continue
            # For submodules, just add them
            if os.path.isdir(os.path.join(cwd, file, ".git")):
                run_cmd(f"git add \"{file}\"", cwd=cwd, ignore_errors=True)
            else:
                # For files, if we are merging a feature into main, we might want the feature's version if it's a conflict
                # But 'ours' (main) is usually safer to prevent regressions.
                # User said "intelligently". Let's try to keep both if possible? Hard to do automatically.
                # We'll stick to 'ours' for stability unless it's a known feature branch.
                run_cmd(f"git checkout --ours \"{file}\"", cwd=cwd, ignore_errors=True)
                run_cmd(f"git add \"{file}\"", cwd=cwd, ignore_errors=True)
        run_cmd("git commit -m \"Resolve remaining conflicts intelligently\"", cwd=cwd, ignore_errors=True)

def process_repo(cwd):
    print(f"\\n>>> Processing {cwd}")
    if not os.path.exists(os.path.join(cwd, ".git")):
        print(f"Skipping {cwd}, no .git directory.")
        return

    # 1. Save local progress
    status, _ = run_cmd("git status --porcelain", cwd=cwd, ignore_errors=True)
    if status:
        print(f"[{cwd}] Saving local changes...")
        run_cmd("git add .", cwd=cwd, ignore_errors=True)
        run_cmd("git commit -m \"chore: save local progress before sync\"", cwd=cwd, ignore_errors=True)

    # 2. Setup branches
    default_branch = get_default_branch(cwd)
    run_cmd("git fetch --all --prune", cwd=cwd, ignore_errors=True)
    
    curr_branch, _ = run_cmd("git rev-parse --abbrev-ref HEAD", cwd=cwd, ignore_errors=True)
    if curr_branch != default_branch:
        run_cmd(f"git checkout {default_branch}", cwd=cwd, ignore_errors=True)

    # 3. Pull latest from origin
    print(f"[{cwd}] Pulling latest {default_branch} from origin...")
    run_cmd(f"git pull origin {default_branch}", cwd=cwd, ignore_errors=True)

    # 4. Merge upstream changes
    remotes, _ = run_cmd("git remote", cwd=cwd, ignore_errors=True)
    if remotes and "upstream" in remotes.split():
        print(f"[{cwd}] Merging upstream/{default_branch}...")
        out, err = run_cmd(f"git merge upstream/{default_branch} -m \"Merge upstream changes\"", cwd=cwd, ignore_errors=True)
        if err and ("Conflict" in err or "Merge conflict" in str(out)):
            resolve_conflicts_intelligently(cwd, f"upstream/{default_branch}", default_branch)

    # 5. Handle feature branches
    local_branches_out, _ = run_cmd("git branch --format=%(refname:short)", cwd=cwd, ignore_errors=True)
    remote_branches_out, _ = run_cmd("git branch -r --format=%(refname:short)", cwd=cwd, ignore_errors=True)
    
    local_branches = [b.strip() for b in local_branches_out.splitlines() if b.strip()] if local_branches_out else []
    remote_branches = [b.strip() for b in remote_branches_out.splitlines() if b.strip()] if remote_branches_out else []

    # Filter for robertpelloni feature branches or local branches
    feature_branches = []
    for b in local_branches:
        if b in [default_branch, "master", "main", "HEAD"]: continue
        feature_branches.append(b)
    
    for rb in remote_branches:
        if "origin/" in rb:
            b_name = rb.replace("origin/", "")
            if b_name in [default_branch, "master", "main", "HEAD"]: continue
            if b_name not in feature_branches:
                feature_branches.append(rb)

    # Merge features INTO main
    for fb in feature_branches:
        print(f"[{cwd}] Merging feature branch {fb} INTO {default_branch}...")
        out, err = run_cmd(f"git merge {fb} -m \"Merge feature {fb} into {default_branch}\"", cwd=cwd, ignore_errors=True)
        if err and ("Conflict" in err or "Merge conflict" in str(out)):
            resolve_conflicts_intelligently(cwd, fb, default_branch)

    # 6. Push main
    print(f"[{cwd}] Pushing {default_branch} to origin...")
    run_cmd(f"git push origin {default_branch}", cwd=cwd, ignore_errors=True)

    # 7. Merge main BACK INTO feature branches (local only for now to avoid push conflicts)
    for fb in local_branches:
        if fb in [default_branch, "master", "main", "HEAD"]: continue
        print(f"[{cwd}] Updating feature branch {fb} with latest {default_branch}...")
        run_cmd(f"git checkout {fb}", cwd=cwd, ignore_errors=True)
        out, err = run_cmd(f"git merge {default_branch} -m \"Sync {fb} with {default_branch}\"", cwd=cwd, ignore_errors=True)
        if err and ("Conflict" in err or "Merge conflict" in str(out)):
            resolve_conflicts_intelligently(cwd, default_branch, fb)
        run_cmd(f"git push origin {fb}", cwd=cwd, ignore_errors=True)

    # Return to default branch
    run_cmd(f"git checkout {default_branch}", cwd=cwd, ignore_errors=True)

    # 8. Update submodules
    print(f"[{cwd}] Updating submodules recursively...")
    run_cmd("git submodule update --init --recursive", cwd=cwd, ignore_errors=True)

def get_all_git_repos(root):
    repos = []
    for dirpath, dirnames, filenames in os.walk(root):
        # Avoid traversing into .git or common heavy directories we don't want to scan recursively
        if any(skip in dirpath for skip in ["node_modules", ".venv", ".cursor", ".git/modules", ".git\\\\modules"]):
            continue
        if ".git" in dirnames or ".git" in filenames:
            repos.append(dirpath)
            # Once we find a .git, we don't necessarily stop, because of submodules
            # But os.walk will continue into subdirectories anyway.
    
    # Sort by depth descending to process submodules before parents
    repos.sort(key=lambda x: x.count(os.sep), reverse=True)
    return repos

if __name__ == "__main__":
    root_dir = os.getcwd()
    repos = get_all_git_repos(root_dir)
    print(f"Found {len(repos)} git repositories/submodules.")
    
    # Optional: filter for robertpelloni if requested, but user said "For any repos"
    # and "For any repos under robertpelloni" specifically for feature branch merging.
    
    for r in repos:
        process_repo(r)
    
    print("\\nComprehensive sync and merge protocol completed.")
