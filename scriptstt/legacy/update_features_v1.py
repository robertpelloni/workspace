import subprocess
import os
import sys

sys.stdout.reconfigure(encoding='utf-8')
sys.stderr.reconfigure(encoding='utf-8')

PROCESSED_FILE = "processed_features_v1.txt"
FAILED_LOG = "failed_features_v1.log"

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

def run_command(cmd, cwd, ignore_errors=False, timeout=300):
    try:
        result = subprocess.run(cmd, cwd=cwd, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, encoding='utf-8', errors='replace', timeout=timeout)
        return result.stdout.strip()
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

def is_robert_repo(cwd):
    remotes_v = run_command("git remote -v", cwd, ignore_errors=True)
    return remotes_v and "robertpelloni" in remotes_v.lower()

def auto_resolve_merge(cwd, branch, target_branch):
    run_command("git merge --abort", cwd, ignore_errors=True)
    merge_cmd = f"git merge {branch} -X ours -m 'Merge {branch} into {target_branch} to update feature branch'"
    print(f"[{cwd}] Merge failed, attempting auto-resolve with -X ours...")
    run_command(merge_cmd, cwd, ignore_errors=True)
    ps_cmd = f'powershell -c "git diff --name-only --diff-filter=U | ForEach-Object {{ if (Test-Path \\"$_/.git\\") {{ git reset HEAD $_; git checkout -- $_ }} elseif (!(Test-Path $_)) {{ git rm -f $_ }} else {{ git add $_ }} }}; git commit --allow-empty -m \\"Update {target_branch} from {branch}\\""'
    run_command(ps_cmd, cwd, ignore_errors=True)

def process_repo(name, cwd, processed_set):
    norm_path = normalize_path(cwd)
    for skip in SKIPPED_REPOS:
        if skip in name or skip in cwd: return
    if norm_path in processed_set: return

    if not os.path.exists(cwd) or not (os.path.isdir(os.path.join(cwd, ".git")) or os.path.isfile(os.path.join(cwd, ".git"))):
         return

    default_branch = get_default_branch(cwd)
    local_branches = get_local_branches(cwd)
    feature_branches = [b for b in local_branches if b not in [default_branch, "master", "main", "HEAD"]]

    if not feature_branches:
        save_processed(cwd)
        processed_set.add(norm_path)
        return

    print(f"\n>>> Updating Feature Branches in: {name} at {cwd}")
    status = run_command("git status --porcelain", cwd, ignore_errors=True)
    if status:
        run_command("git add .", cwd)
        run_command('git commit -m "chore: save progress before feature update"', cwd)

    orig_branch = get_current_branch(cwd)
    for feature in feature_branches:
        print(f"Updating feature branch '{feature}' from {default_branch}...")
        res = run_command(f"git checkout {feature}", cwd, ignore_errors=True)
        if res is None: continue
        merge_res = run_command(f"git merge {default_branch}", cwd, timeout=120)
        if merge_res is None: auto_resolve_merge(cwd, default_branch, feature)
        if is_robert_repo(cwd):
            print(f"Pushing updated feature branch {feature} to origin...")
            run_command(f"git push origin {feature}", cwd, ignore_errors=True, timeout=120)

    run_command(f"git checkout {orig_branch}", cwd, ignore_errors=True)
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
            if len(parts) >= 2: submodules.append((parts[1], os.path.join(cwd, parts[1])))
    for sub_path, sub_abs_path in submodules: process_recursive(f"{name}/{sub_path}", sub_abs_path, visited, processed_set)
    process_repo(name, cwd, processed_set)

def main():
    root_path = os.getcwd()
    processed_set = load_processed()
    visited = set()
    process_recursive("ROOT", root_path, visited, processed_set)
    if os.path.exists(PROCESSED_FILE): os.remove(PROCESSED_FILE)

if __name__ == "__main__": main()
