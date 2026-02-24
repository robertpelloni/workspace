import os
import subprocess

def run(cmd, cwd=None):
    try:
        res = subprocess.run(cmd, shell=True, cwd=cwd, capture_output=True, text=True, timeout=120)
        return res.stdout.strip(), res.stderr.strip()
    except Exception as e:
        return "", str(e)

def is_robert_repo(cwd):
    out, err = run("git remote -v", cwd)
    return "robertpelloni" in out.lower()

def get_default_branch(cwd):
    out, err = run("git symbolic-ref refs/remotes/origin/HEAD", cwd)
    if out:
        return out.split("/")[-1].strip()
    branches, _ = run("git branch", cwd)
    if "main" in branches: return "main"
    return "master"

def intelligent_merge(cwd, source, target):
    print(f"Merging {source} into {target} in {cwd}...")
    run("git merge --abort", cwd)
    out, err = run(f'git merge {source} --allow-unrelated-histories -X ours -m "Merge {source} into {target}"', cwd)
    if "conflict" in out.lower() or "conflict" in err.lower() or "CONFLICT" in out:
        status, _ = run("git status --porcelain", cwd)
        for line in status.splitlines():
            if len(line) > 3 and (line.startswith("UU") or line.startswith("AA") or line.startswith("DU") or line.startswith("UD")):
                file = line[3:].strip()
                run(f'git checkout --ours "{file}"', cwd)
                run(f'git add "{file}"', cwd)
        run(f'git commit -m "Resolve conflicts merging {source} into {target}"', cwd)

def process_repo(cwd):
    if not os.path.isdir(os.path.join(cwd, ".git")): return
    print(f"\n>>> Processing {cwd}")
    
    # Save local progress
    status, _ = run("git status --porcelain", cwd)
    if status:
        run("git add .", cwd)
        run('git commit -m "chore: save local progress before sync"', cwd)
        
    main_branch = get_default_branch(cwd)
    run("git fetch --all", cwd)
    run(f"git checkout {main_branch}", cwd)
    run(f"git pull origin {main_branch}", cwd)
    
    # Upstream merge
    remotes, _ = run("git remote", cwd)
    if "upstream" in remotes:
        run("git fetch upstream", cwd)
        intelligent_merge(cwd, f"upstream/{main_branch}", main_branch)
        
    if is_robert_repo(cwd):
        out, _ = run("git branch -a", cwd)
        branches = set()
        for line in out.splitlines():
            b = line.strip().replace("* ", "")
            if "->" in b: continue
            if b.startswith("remotes/origin/"):
                b = b.replace("remotes/origin/", "")
            elif b.startswith("remotes/upstream/"):
                continue
            if b != main_branch and b != "HEAD" and not b.startswith("dependabot") and "gh-pages" not in b:
                branches.add(b)
                
        # Merge features to main
        for b in branches:
            run(f"git checkout {main_branch}", cwd)
            intelligent_merge(cwd, f"origin/{b}" if "origin/" not in b else b, main_branch)
            
        # Merge main to features
        for b in branches:
            res_out, res_err = run(f"git checkout {b}", cwd)
            if "error" in res_err.lower() or "did not match" in res_err.lower():
                run(f"git checkout -b {b} origin/{b}", cwd)
            intelligent_merge(cwd, main_branch, b)
            run(f"git push origin {b}", cwd)
            
        run(f"git checkout {main_branch}", cwd)
        run(f"git push origin {main_branch}", cwd)

def process_recursive(cwd, visited=None):
    if visited is None: visited = set()
    real_cwd = os.path.realpath(cwd)
    if real_cwd in visited: return
    visited.add(real_cwd)
    
    # Skip huge/problematic directories
    if "node_modules" in cwd or ".venv" in cwd or "temp_" in cwd: return
    
    process_repo(cwd)
    out, _ = run("git submodule status", cwd)
    for line in out.splitlines():
        if not line.strip(): continue
        parts = line.strip().split()
        if len(parts) >= 2:
            sub_path = os.path.join(cwd, parts[1])
            if os.path.isdir(sub_path):
                process_recursive(sub_path, visited)

if __name__ == '__main__':
    root = os.getcwd()
    process_recursive(root)
    print("ALL SYNC DONE.")