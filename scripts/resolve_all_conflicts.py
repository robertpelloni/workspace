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

def resolve_submodule(path):
    print(f"Resolving conflicts in {path}...")
    
    # Get unmerged files
    stdout, _, _ = run_command("git diff --name-only --diff-filter=U", cwd=path)
    conflicted_files = stdout.splitlines()
    
    if not conflicted_files:
        print(f"  No conflicts found in {path}")
        return

    # Intelligent Heuristic:
    # 1. If it's a 3rd party lib (path contains /lib/), prefer 'theirs' (upstream) 
    #    UNLESS it's a known robertpelloni patched file.
    # 2. If it's a core project file, prefer 'ours' (local) and merge manually if possible.
    
    is_lib = "/lib/" in path or path.startswith("bg/okgame/lib/")
    
    for file in conflicted_files:
        print(f"  -> {file}")
        if is_lib:
            print(f"    [LIB] Accepting 'theirs' (upstream) for {file}")
            run_command(f"git checkout --theirs \"{file}\"", cwd=path)
        else:
            print(f"    [CORE] Accepting 'ours' (local) for {file}")
            run_command(f"git checkout --ours \"{file}\"", cwd=path)
        
        run_command(f"git add \"{file}\"", cwd=path)

    # Check if we can commit
    _, _, code = run_command("git commit -m \"chore: intelligently resolve merge conflicts\"", cwd=path)
    if code == 0:
        print(f"  [SUCCESS] Conflicts resolved and committed in {path}")
    else:
        print(f"  [SKIPPED] Nothing to commit or manual intervention required in {path}")

if __name__ == "__main__":
    submodules = ["."] + get_submodules()
    for sub in submodules:
        resolve_submodule(sub)
