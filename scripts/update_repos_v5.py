import subprocess
import os
import sys

sys.stdout.reconfigure(encoding='utf-8')
sys.stderr.reconfigure(encoding='utf-8')

PROCESSED_FILE = "processed_repos_v5.txt"
FAILED_LOG = "failed_repos_v5.log"

SKIPPED_REPOS = ["voidsprite", "temp_defihacklabs", "vibeship-scanner", "borg"]

def normalize_path(path): return os.path.normpath(os.path.abspath(path)).lower()

def load_processed():
    if os.path.exists(PROCESSED_FILE):
        with open(PROCESSED_FILE, "r", encoding="utf-8") as f:
            return set(normalize_path(line.strip()) for line in f if line.strip())
    return set()

def save_processed(path):
    with open(PROCESSED_FILE, "a", encoding="utf-8") as f:
        f.write(path + chr(10))
        f.flush()

def log_failure(path, reason):
    with open(FAILED_LOG, "a", encoding="utf-8") as f:
        f.write(f"{path}: {reason}" + chr(10))
        f.flush()

def run_command(cmd, cwd, ignore_errors=False, timeout=300):
    try:
        result = subprocess.run(cmd, cwd=cwd, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, encoding='utf-8', errors='replace', timeout=timeout)
        return result.stdout.strip()
    except subprocess.TimeoutExpired: return None
    except subprocess.CalledProcessError: return None
    except Exception: return None

def get_default_branch(cwd):
    try:
        remotes = run_command("git remote show origin", cwd, ignore_errors=True, timeout=10)
        if remotes:
            for line in remotes.split(chr(10)):
                if "HEAD branch:" in line: return line.split("HEAD branch:")[1].strip()
    except: pass
    branches = run_command("git branch -r", cwd, ignore_errors=True)
    if branches:
        if "origin/main" in branches: return "main"
        if "origin/master" in branches: return "master"
    return "main"

def get_current_branch(cwd):
    branch = run_command("git rev-parse --abbrev-ref HEAD", cwd, ignore_errors=True)
    return branch.strip() if branch else "HEAD"

def get_local_branches(cwd):
    output = run_command("git branch --format=%(refname:short)", cwd, ignore_errors=True)
    if output: return [b.strip().strip("'").strip('"') for b in output.split(chr(10)) if b.strip()]
    return []

def get_remote_robert_branches(cwd):
    output = run_command("git branch -r", cwd, ignore_errors=True)
    branches = []
    if output:
        for b in output.split(chr(10)):
            b = b.strip()
            if "origin/" in b and "HEAD" not in b: branches.append(b)
    return branches

def is_robert_repo(cwd):
    remotes_v = run_command("git remote -v", cwd, ignore_errors=True)
    return remotes_v and "robertpelloni" in remotes_v.lower()

def auto_resolve_merge(cwd, branch, default_branch):
    run_command("git merge --abort", cwd, ignore_errors=True)
    
    # Safe formatting without internal nested quotes causing SyntaxError
    merge_cmd = f"git merge {branch} --allow-unrelated-histories -X ours -m 'Merge {branch} into {default_branch}'"
    run_command(merge_cmd, cwd, ignore_errors=True)
    
    ps_cmd = f'powershell -c "git diff --name-only --diff-filter=U | ForEach-Object {{ if (Test-Path \\"$_/.git\\") {{ git reset HEAD $_; git checkout -- $_ }} elseif (!(Test-Path $_)) {{ git rm -f $_ }} else {{ git add $_ }} }}; git commit --allow-empty -m \\"Merge {branch} into {default_branch}\\""'
    run_command(ps_cmd, cwd, ignore_errors=True)

def process_repo(name, cwd, processed_set):
    norm_path = normalize_path(cwd)
    for skip in SKIPPED_REPOS:
        if skip in name or skip in cwd: return
    if norm_path in processed_set: return

    print(f"\n>>> Starting Processing: {name} at {cwd}")
    if not os.path.exists(cwd):
        save_processed(cwd)
        processed_set.add(norm_path)
        return

    if not os.path.exists(os.path.join(cwd, ".git")) and not os.path.isfile(os.path.join(cwd, ".git")):
         save_processed(cwd)
         processed_set.add(norm_path)
         return

    git_dir = run_command("git rev-parse --git-dir", cwd, ignore_errors=True)
    if git_dir and os.path.exists(os.path.join(cwd, git_dir, "MERGE_HEAD")):
        print(f"[{cwd}] Repo is mid-merge! Auto-resolving...")
        # Since we don't know the branch, just abort
        run_command("git merge --abort", cwd, ignore_errors=True)

    current_branch = get_current_branch(cwd)
    status = run_command("git status --porcelain", cwd, ignore_errors=True)
    if status:
        run_command("git add .", cwd)
        run_command('git commit -m "chore: save progress before update"', cwd)

    default_branch = get_default_branch(cwd)

    if current_branch != default_branch:
        res = run_command(f"git checkout {default_branch}", cwd, ignore_errors=True)
        if res is None:
            res = run_command(f"git checkout -b {default_branch} --track origin/{default_branch}", cwd, ignore_errors=True)  
            if res is None:
                save_processed(cwd)
                processed_set.add(norm_path)
                return

    run_command(f"git pull origin {default_branch}", cwd, ignore_errors=True)

    remotes = run_command("git remote", cwd, ignore_errors=True)
    if remotes and "upstream" in remotes.split():
        upstream_branch_ref = f"upstream/{default_branch}"
        remote_branches = run_command("git branch -r", cwd, ignore_errors=True)
        if remote_branches and upstream_branch_ref in remote_branches:
            run_command("git fetch upstream", cwd)
            merge_res = run_command(f"git merge {upstream_branch_ref}", cwd, timeout=120)
            if merge_res is None:
                auto_resolve_merge(cwd, upstream_branch_ref, default_branch)

    local_branches = get_local_branches(cwd)
    for branch in local_branches:
        if branch in [default_branch, "master", "main", "HEAD"]: continue
        print(f"Attempting to merge local branch '{branch}' into {default_branch}...")
        merge_res = run_command(f"git merge {branch}", cwd, timeout=120)
        if merge_res is None:
            auto_resolve_merge(cwd, branch, default_branch)

    if is_robert_repo(cwd):
        remote_branches = get_remote_robert_branches(cwd)
        for rb in remote_branches:
            branch_name = rb.replace("origin/", "")
            if branch_name in [default_branch, "master", "main"]: continue
            if branch_name in local_branches: continue
            print(f"Attempting to merge remote branch '{rb}' into {default_branch}...")
            merge_res = run_command(f"git merge {rb}", cwd, timeout=120)
            if merge_res is None:
                auto_resolve_merge(cwd, rb, default_branch)

    if is_robert_repo(cwd):
        run_command(f"git push origin {default_branch}", cwd, ignore_errors=True, timeout=120)

    save_processed(cwd)
    processed_set.add(norm_path)

def process_recursive(name, cwd, visited, processed_set):
    norm_path = normalize_path(cwd)
    for skip in SKIPPED_REPOS:
        if skip in name or skip in cwd: return
    if norm_path in processed_set: return

    try: real_cwd = os.path.realpath(cwd)
    except: return

    if real_cwd in visited: return
    visited.add(real_cwd)

    output = run_command("git submodule status", cwd, ignore_errors=True)
    submodules = []
    if output:
        for line in output.split(chr(10)):
            parts = line.strip().split()
            if len(parts) >= 2:
                sub_path = parts[1]
                sub_abs_path = os.path.join(cwd, sub_path)
                submodules.append((sub_path, sub_abs_path))

    for sub_path, sub_abs_path in submodules:
        process_recursive(f"{name}/{sub_path}", sub_abs_path, visited, processed_set)

    if name != "ROOT":
        process_repo(name, cwd, processed_set)

def main():
    root_path = os.getcwd()
    # To carry over from v4
    if os.path.exists("processed_repos_v4.txt") and not os.path.exists(PROCESSED_FILE):
        import shutil
        shutil.copy("processed_repos_v4.txt", PROCESSED_FILE)
        
    processed_set = load_processed()
    visited = set()
    process_recursive("ROOT", root_path, visited, processed_set)
    process_repo("ROOT", root_path, processed_set)

    if os.path.exists(PROCESSED_FILE): os.remove(PROCESSED_FILE)
    if os.path.exists(FAILED_LOG): os.remove(FAILED_LOG)

if __name__ == "__main__":
    main()
