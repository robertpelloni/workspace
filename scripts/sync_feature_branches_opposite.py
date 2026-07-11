import os
import subprocess

def run_cmd(cmd, cwd=None, ignore_errors=False):
    try:
        res = subprocess.run(cmd, cwd=cwd, shell=True, capture_output=True, text=True, encoding="utf-8", errors="replace")
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

def sync_opposite(cwd):
    if not is_robert_repo(cwd):
        return
    print(f"\\n>>> Processing opposite sync for {cwd}")
    default_branch = get_default_branch(cwd)
    local_branches_out, _ = run_cmd("git branch --format=%(refname:short)", cwd=cwd, ignore_errors=True)
    if local_branches_out:
        local_branches = [b.strip() for b in local_branches_out.splitlines() if b.strip()]
        for b in local_branches:
            if b in [default_branch, "master", "main", "HEAD"]: continue
            print(f"[{cwd}] Merging {default_branch} into {b}...")
            # checkout branch
            run_cmd(f"git checkout {b}", cwd=cwd, ignore_errors=True)
            # merge default_branch
            out, err = run_cmd(f"git merge {default_branch} -X theirs -m \"Catch up feature branch with {default_branch}\"", cwd=cwd, ignore_errors=True)
            if err and ("Conflict" in err or "Merge conflict" in str(out)):
                # If conflict, resolve with theirs (main)
                run_cmd("git merge --abort", cwd=cwd, ignore_errors=True)
                run_cmd(f"git merge {default_branch} --allow-unrelated-histories -X theirs -m \"Auto-resolve catch up\"", cwd=cwd, ignore_errors=True)
                # Resolve remaining
                out, _ = run_cmd("git diff --name-only --diff-filter=U", cwd=cwd, ignore_errors=True)
                if out:
                    for file in out.splitlines():
                        file = file.strip()
                        if not file: continue
                        run_cmd(f"git checkout --theirs \"{file}\"", cwd=cwd, ignore_errors=True)
                        run_cmd(f"git add \"{file}\"", cwd=cwd, ignore_errors=True)
                    run_cmd("git commit -m \"Resolve remaining conflicts\"", cwd=cwd, ignore_errors=True)
            # Push the feature branch
            run_cmd(f"git push origin {b}", cwd=cwd, ignore_errors=True)
        # Restore default branch
        run_cmd(f"git checkout {default_branch}", cwd=cwd, ignore_errors=True)

def get_all_git_repos(root):
    repos = []
    for dirpath, dirnames, filenames in os.walk(root):
        if any(skip in dirpath for skip in ["node_modules", "temp_", "build", "dist", ".venv", ".cursor", ".git\\modules", "borg", "fwber", "bg"]):
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
        sync_opposite(r)
    print("Opposite sync all done.")