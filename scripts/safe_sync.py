import os
import subprocess

def run_cmd(cmd, cwd=None):
    res = subprocess.run(cmd, cwd=cwd, shell=True, capture_output=True, text=True)
    return res.stdout.strip(), res.stderr.strip()

out, _ = run_cmd('git config --file .gitmodules --get-regexp path')
submodules = [line.split()[1] for line in out.splitlines() if line]

for sm in submodules:
    if not os.path.exists(sm):
        continue
    print(f'Syncing {sm}...')
    # Fetch all
    run_cmd('git fetch --all', cwd=sm)
    
    # Identify default branch
    out, _ = run_cmd("git rev-parse --abbrev-ref HEAD", cwd=sm)
    default_branch = out if out else "main"
    if default_branch == "HEAD":
        out, _ = run_cmd("git branch -r", cwd=sm)
        if "origin/main" in out: default_branch = "main"
        elif "origin/master" in out: default_branch = "master"
        else: default_branch = "main"
        
    print(f'Default branch: {default_branch}')
    
    # Checkout and pull
    run_cmd(f'git checkout {default_branch}', cwd=sm)
    run_cmd(f'git pull origin {default_branch}', cwd=sm)
    
    # Check if upstream exists
    remotes, _ = run_cmd("git remote", cwd=sm)
    if "upstream" in remotes:
        run_cmd(f"git fetch upstream", cwd=sm)
        run_cmd(f"git merge upstream/{default_branch} -m 'Merge upstream'", cwd=sm)
    
    # Merge local branches
    branches_out, _ = run_cmd('git branch --format=%(refname:short)', cwd=sm)
    for b in branches_out.splitlines():
        b = b.strip()
        if b and b not in [default_branch, 'master', 'main', 'HEAD']:
            print(f'Merging local branch {b} into {default_branch}...')
            # Commit any current changes to avoid merge aborting early
            run_cmd('git add .', cwd=sm)
            run_cmd('git commit -m "chore: save local before merge"', cwd=sm)
            
            _, err = run_cmd(f'git merge {b} -m "Merge {b} into {default_branch}"', cwd=sm)
            if "Conflict" in err or "conflict" in err.lower():
                print(f"Conflicts merging {b}, resolving with ours...")
                run_cmd("git merge --abort", cwd=sm)
                run_cmd(f'git merge {b} -X ours -m "Merge {b} into {default_branch} (auto-resolved)"', cwd=sm)
    
    # Push
    print(f'Pushing {sm}...')
    run_cmd(f'git push origin {default_branch}', cwd=sm)

print('Sync complete.')