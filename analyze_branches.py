import subprocess
import os

def run_command(cmd, cwd=None):
    try:
        process = subprocess.Popen(cmd, shell=True, cwd=cwd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        return process.returncode, stdout.decode().strip(), stderr.decode().strip()
    except Exception as e:
        return -1, "", str(e)

def get_unique_commits(path, branch, remote_branch):
    # Check if there are commits on 'branch' not in 'remote_branch'
    code, out, err = run_command(f"git log {remote_branch}..{branch} --oneline", cwd=path)
    if code == 0 and out:
        return out.splitlines()
    return []

def main():
    submodules_raw_code, submodules_raw, _ = run_command("git submodule foreach --recursive \"pwd\"")
    if submodules_raw_code != 0:
        print("Failed to list submodules")
        return

    for line in submodules_raw.splitlines():
        if line.startswith("Entering '"):
            sub_path = line[10:-1]
            print(f"\nAnalyzing {sub_path}...")
            
            # Get current branch
            _, branch, _ = run_command("git rev-parse --abbrev-ref HEAD", cwd=sub_path)
            print(f"  Current branch: {branch}")
            
            # Check for local changes
            _, status, _ = run_command("git status --short", cwd=sub_path)
            if status:
                print(f"  LOCAL CHANGES DETECTED:\n{status}")
            
            # Check for unique commits compared to origin/main or origin/master
            for base in ["origin/main", "origin/master", "upstream/main", "upstream/master"]:
                commits = get_unique_commits(sub_path, branch, base)
                if commits:
                    print(f"  Unique commits vs {base}: {len(commits)}")
                    # print first 3
                    for c in commits[:3]:
                        print(f"    {c}")

if __name__ == "__main__":
    main()
