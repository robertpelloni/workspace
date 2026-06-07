import os
import subprocess
import sys

def run_cmd(cmd, cwd=None, ignore_errors=False, timeout=300):
    try:
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
    return out if out else "main"

def is_robert_repo(cwd):
    out, _ = run_cmd("git remote -v", cwd=cwd, ignore_errors=True)
    if out and "robertpelloni" in out.lower():
        return True
    return False

def resolve_conflicts_intelligently(cwd, branch, default_branch):
    print(f"[{cwd}] Resolving conflicts for {branch} into {default_branch}...")
    run_cmd("git merge --abort", cwd=cwd, ignore_errors=True)
    
    # Favor our changes to not lose features
    merge_cmd = f"git merge {branch} --allow-unrelated-histories -X ours -m \"Merge {branch} into {default_branch} (auto-resolved)\""
    stdout, stderr = run_cmd(merge_cmd, cwd=cwd, ignore_errors=True)
    
    # If still conflicting (binary files, deletions)
    out, _ = run_cmd("git diff --name-only --diff-filter=U", cwd=cwd, ignore_errors=True)
    if out:
        for file in out.splitlines():
            file = file.strip()
            if not file: continue
            if os.path.isdir(os.path.join(cwd, file, ".git")):
                run_cmd(f"git add \"{file}\"", cwd=cwd, ignore_errors=True)
            else:
                run_cmd(f"git checkout --ours \"{file}\"", cwd=cwd, ignore_errors=True)
                run_cmd(f"git add \"{file}\"", cwd=cwd, ignore_errors=True)
        run_cmd("git commit -m \"Resolve remaining conflicts\"", cwd=cwd, ignore_errors=True)

def process_repo(cwd):
    print(f"\\n>>> Processing {cwd}")
    status, _ = run_cmd("git status --porcelain", cwd=cwd, ignore_errors=True)
    if status:
        run_cmd("git add .", cwd=cwd, ignore_errors=True)
        run_cmd("git commit -m \"chore: save local progress before sync\"", cwd=cwd, ignore_errors=True)

    default_branch = get_default_branch(cwd)
    run_cmd("git fetch --all", cwd=cwd, ignore_errors=True)

    out, err = run_cmd(f"git checkout {default_branch}", cwd=cwd, ignore_errors=True)
    if err:
        run_cmd(f"git checkout -b {default_branch} --track origin/{default_branch}", cwd=cwd, ignore_errors=True)
    
    run_cmd(f"git pull origin {default_branch}", cwd=cwd, ignore_errors=True)

    remotes, _ = run_cmd("git remote", cwd=cwd, ignore_errors=True)
    if remotes and "upstream" in remotes.split():
        remote_branches, _ = run_cmd("git branch -r", cwd=cwd, ignore_errors=True)
        if remote_branches and f"upstream/{default_branch}" in remote_branches:
            print(f"[{cwd}] Merging upstream/{default_branch}...")
            out, err = run_cmd(f"git merge upstream/{default_branch} -m \"Merge upstream\"", cwd=cwd, ignore_errors=True)
            if err and ("Conflict" in err or "Merge conflict" in str(out)):
                resolve_conflicts_intelligently(cwd, f"upstream/{default_branch}", default_branch)

    if is_robert_repo(cwd):
        local_branches_out, _ = run_cmd("git branch --format=%(refname:short)", cwd=cwd, ignore_errors=True)
        if local_branches_out:
            local_branches = [b.strip() for b in local_branches_out.splitlines() if b.strip()]
            for b in local_branches:
                if b in [default_branch, "master", "main", "HEAD"]: continue
                print(f"[{cwd}] Merging local feature branch: {b}")
                out, err = run_cmd(f"git merge {b} -m \"Merge {b}\"", cwd=cwd, ignore_errors=True)
                if err and ("Conflict" in err or "Merge conflict" in str(out)):
                    resolve_conflicts_intelligently(cwd, b, default_branch)

        remote_branches_out, _ = run_cmd("git branch -r", cwd=cwd, ignore_errors=True)
        if remote_branches_out:
            remote_branches = [b.strip() for b in remote_branches_out.splitlines() if b.strip() and b.startswith("origin/") and "HEAD" not in b]
            for rb in remote_branches:
                b_name = rb.replace("origin/", "")
                if b_name in [default_branch, "master", "main"]: continue
                print(f"[{cwd}] Merging remote feature branch: {rb}")
                out, err = run_cmd(f"git merge {rb} -m \"Merge {rb}\"", cwd=cwd, ignore_errors=True)
                if err and ("Conflict" in err or "Merge conflict" in str(out)):
                    resolve_conflicts_intelligently(cwd, rb, default_branch)

        print(f"[{cwd}] Pushing to origin...")
        run_cmd(f"git push origin {default_branch}", cwd=cwd, ignore_errors=True)

def get_all_git_repos(root):
    repos = []
    for dirpath, dirnames, filenames in os.walk(root):
        if any(skip in dirpath for skip in ["node_modules", "temp_defihacklabs", "vibeship-scanner", "voidsprite", ".venv", ".cursor", ".git\\\\modules"]):
            continue
        if ".git" in dirnames or ".git" in filenames:
            repos.append(dirpath)
    repos.sort(key=lambda x: x.count(os.sep), reverse=True)
    return repos

if __name__ == "__main__":
    root_dir = os.getcwd()
    repos = get_all_git_repos(root_dir)
    print(f"Found {len(repos)} repositories.")
    for r in repos:
        process_repo(r)
    print("All done.")

