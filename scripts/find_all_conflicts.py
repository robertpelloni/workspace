import os
import subprocess

def run_command(command, cwd=None):
    try:
        result = subprocess.run(command, cwd=cwd, shell=True, capture_output=True, text=True)
        return result.stdout.strip(), result.stderr.strip(), result.returncode
    except Exception as e:
        return "", str(e), 1

def get_submodules():
    stdout, _, _ = run_command("git submodule status --recursive")
    submodules = []
    for line in stdout.splitlines():
        parts = line.strip().split()
        if len(parts) >= 2:
            submodules.append(parts[1])
    return submodules

if __name__ == "__main__":
    print("Checking for unmerged paths in all submodules...")
    submodules = ["."] + get_submodules()
    for sub in submodules:
        stdout, _, _ = run_command("git diff --name-only --diff-filter=U", cwd=sub if sub != "." else None)
        if stdout:
            print(f"\n[CONFLICTS] {sub}:")
            for line in stdout.splitlines():
                print(f"  {line}")
