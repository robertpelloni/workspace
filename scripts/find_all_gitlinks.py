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
    print("Searching for all gitlinks (160000) in the workspace...")
    submodules = ["."] + get_submodules()
    for sub in submodules:
        stdout, _, _ = run_command("git ls-files -s", cwd=sub if sub != "." else None)
        for line in stdout.splitlines():
            if line.startswith("160000"):
                print(f"[{sub}] {line}")
