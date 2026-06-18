import os
import subprocess
import sys

def run_cmd(cmd, cwd=None, ignore_errors=False, timeout=600):
    try:
        res = subprocess.run(cmd, cwd=cwd, shell=True, capture_output=True, text=True, encoding="utf-8", errors="replace", timeout=timeout)
        if not ignore_errors and res.returncode != 0:
            return None, res.stderr
        return res.stdout.strip(), None
    except Exception as e:
        return None, str(e)

def get_default_branch(cwd):
    # Try to find main or master
    branches_out, _ = run_cmd("git branch -a", cwd=cwd, ignore_errors=True)
    if not branches_out: return "main"
    
    if "remotes/origin/main" in branches_out: return "main"
    if "remotes/origin/master" in branches_out: return "master"
    if "* main" in branches_out: return "main"
    if "* master" in branches_out: return "master"
    
    # Fallback to current branch
    out, _ = run_cmd("git rev-parse --abbrev-ref HEAD", cwd=cwd, ignore_errors=True)
    return out if out and out != "HEAD" else "main"

def resolve_conflicts(cwd, source, target, strategy="ours"):
    print(f"[{cwd}] Resolving conflicts: {source} -> {target} using strategy {strategy}")
    # Strategy 'ours' means we keep the current branch's version (target)
    # Strategy 'theirs' means we keep the source branch's version
    
    out, _ = run_cmd("git diff --name-only --diff-filter=U", cwd=cwd, ignore_errors=True)
    if out:
        for file in out.splitlines():
            file = file.strip()
            if not file: continue
            if os.path.isdir(os.path.join(cwd, file, ".git")):
                # Submodule conflict, usually just add it
                run_cmd(f"git add \"{file}\"", cwd=cwd, ignore_errors=True)
            else:
                run_cmd(f"git checkout --{strategy} \"{file}\"", cwd=cwd, ignore_errors=True)
                run_cmd(f"git add \"{file}\"", cwd=cwd, ignore_errors=True)
        run_cmd(f"git commit -m \"Resolve conflicts intelligently ({strategy})\"", cwd=cwd, ignore_errors=True)

def process_repo(cwd):
    print(f"\n>>> DUAL-DIRECTION MERGE ENGINE: {cwd}")
    if not os.path.exists(os.path.join(cwd, ".git")):
        print(f"Skipping {cwd}, no .git directory.")
        return

    # 1. Fetch
    print(f"[{cwd}] Fetching all...")
    run_cmd("git fetch --all --tags --prune", cwd=cwd, ignore_errors=True)

    default_branch = get_default_branch(cwd)
    print(f"[{cwd}] Default branch identified: {default_branch}")

    # 2. Sync default branch
    run_cmd(f"git checkout {default_branch}", cwd=cwd, ignore_errors=True)
    run_cmd(f"git pull origin {default_branch}", cwd=cwd, ignore_errors=True)

    remotes, _ = run_cmd("git remote", cwd=cwd, ignore_errors=True)
    if remotes and "upstream" in remotes.split():
        print(f"[{cwd}] Merging upstream/{default_branch}...")
        out, err = run_cmd(f"git merge upstream/{default_branch} -m \"Merge upstream changes\"", cwd=cwd, ignore_errors=True)
        if err and ("Conflict" in err or "Merge conflict" in str(out)):
            resolve_conflicts(cwd, f"upstream/{default_branch}", default_branch, strategy="theirs") # Favor upstream for base branch

    # 3. Identify feature branches
    local_branches_out, _ = run_cmd("git branch --format=%(refname:short)", cwd=cwd, ignore_errors=True)
    remote_branches_out, _ = run_cmd("git branch -r --format=%(refname:short)", cwd=cwd, ignore_errors=True)
    
    local_branches = [b.strip() for b in local_branches_out.splitlines() if b.strip()] if local_branches_out else []
    remote_branches = [b.strip() for b in remote_branches_out.splitlines() if b.strip()] if remote_branches_out else []

    feature_branches = []
    # We look for branches that aren't the default or common ones
    skip_branches = [default_branch, "master", "main", "HEAD", "origin/HEAD"]
    
    for b in local_branches:
        if b in skip_branches: continue
        if b not in feature_branches: feature_branches.append(b)
        
    for rb in remote_branches:
        if any(skip in rb for skip in skip_branches): continue
        if "origin/" in rb:
            b_name = rb.replace("origin/", "")
            if b_name not in skip_branches and b_name not in feature_branches:
                feature_branches.append(rb)

    # 4. Forward Merge: feature -> default
    for fb in feature_branches:
        print(f"[{cwd}] FORWARD MERGE: {fb} -> {default_branch}")
        run_cmd(f"git checkout {default_branch}", cwd=cwd, ignore_errors=True)
        out, err = run_cmd(f"git merge {fb} -m \"Forward merge {fb} into {default_branch}\"", cwd=cwd, ignore_errors=True)
        if err and ("Conflict" in err or "Merge conflict" in str(out)):
            # When merging feature into default, we want to keep features but avoid breaking default.
            # Strategy 'theirs' might be better to get the new features.
            resolve_conflicts(cwd, fb, default_branch, strategy="theirs")

    # 5. Push default branch
    print(f"[{cwd}] Pushing {default_branch}...")
    run_cmd(f"git push origin {default_branch}", cwd=cwd, ignore_errors=True)

    # 6. Reverse Merge: default -> feature
    # Only for local feature branches (that we can push)
    for fb in local_branches:
        if fb in skip_branches: continue
        print(f"[{cwd}] REVERSE MERGE: {default_branch} -> {fb}")
        run_cmd(f"git checkout {fb}", cwd=cwd, ignore_errors=True)
        out, err = run_cmd(f"git merge {default_branch} -m \"Reverse merge {default_branch} into {fb}\"", cwd=cwd, ignore_errors=True)
        if err and ("Conflict" in err or "Merge conflict" in str(out)):
            # When merging default back into feature, we want to favor the default branch's stability
            resolve_conflicts(cwd, default_branch, fb, strategy="theirs")
        
        print(f"[{cwd}] Pushing feature branch {fb}...")
        run_cmd(f"git push origin {fb}", cwd=cwd, ignore_errors=True)

    # Return to default branch
    run_cmd(f"git checkout {default_branch}", cwd=cwd, ignore_errors=True)

if __name__ == "__main__":
    if len(sys.argv) > 1:
        repos = sys.argv[1:]
    else:
        # Default to root if no args
        repos = [os.getcwd()]
        
    for r in repos:
        abs_path = os.path.abspath(r)
        process_repo(abs_path)
