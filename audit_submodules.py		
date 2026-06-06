import subprocess
import os

def run_command(cmd, cwd=None):
    try:
        result = subprocess.run(cmd, shell=True, capture_output=True, text=True, cwd=cwd)
        return result.stdout.strip(), result.stderr.strip()
    except Exception as e:
        return "", str(e)

def audit_repo(repo_path):
    print(f"\n--- Auditing {repo_path} ---")
    
    # Get all submodules
    output, _ = run_command("git submodule status --recursive", cwd=repo_path)
    if not output:
        print("No submodules found or error running command.")
        return

    submodules = []
    for line in output.splitlines():
        parts = line.split()
        if len(parts) >= 2:
            sha = parts[0].strip('+-')
            path = parts[1]
            submodules.append((sha, path))

    for sha, path in submodules:
        sub_full_path = os.path.join(repo_path, path)
        if not os.path.exists(os.path.join(sub_full_path, '.git')):
            print(f"[!] Submodule {path} not initialized at {sub_full_path}")
            continue
            
        # Check if the commit exists on the remote
        # We try to fetch the commit directly
        stdout, stderr = run_command(f"git fetch origin {sha}", cwd=sub_full_path)
        if "fatal" in stderr and "not our ref" in stderr:
            print(f"[X] INVALID REF: {path} points to {sha} which is missing on remote!")
            
            # Suggest a fix: find the nearest branch (master/main/develop)
            branch_out, _ = run_command("git remote show origin", cwd=sub_full_path)
            branch = "main"
            if "HEAD branch: master" in branch_out:
                branch = "master"
            elif "HEAD branch: develop" in branch_out:
                branch = "development" # or develop
            
            print(f"    Suggested fix: git checkout origin/{branch} && git add {path}")
        else:
            print(f"[OK] {path} is valid.")

repos = [
    "C:/Users/hyper/workspace/bobmani/itgmania",
    "C:/Users/hyper/workspace/bg/bobsgameonlinejava",
    "C:/Users/hyper/workspace/bobfilez"
]

for repo in repos:
    if os.path.exists(repo):
        audit_repo(repo)
    else:
        print(f"Path not found: {repo}")
