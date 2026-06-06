import os
import subprocess

def run_command(cmd, cwd=None):
    try:
        result = subprocess.run(cmd, cwd=cwd, shell=True, capture_output=True, text=True)
        return result.stdout.strip(), result.stderr.strip()
    except Exception as e:
        return "", str(e)

def prune_broken_submodules(target_dir):
    print(f"[*] Auditing submodules in: {target_dir}")
    
    # Get all 160000 entries in the index
    index_files, _ = run_command("git ls-files --stage", cwd=target_dir)
    submodule_paths = []
    for line in index_files.splitlines():
        if line.startswith("160000"):
            path = line.split("\t")[-1]
            submodule_paths.append(path)
    
    if not submodule_paths:
        return False

    # Get all paths in .gitmodules
    gitmodules_path = os.path.join(target_dir, ".gitmodules")
    mapped_paths = []
    if os.path.exists(gitmodules_path):
        with open(gitmodules_path, "r") as f:
            for line in f:
                if "path =" in line:
                    mapped_paths.append(line.split("=")[-1].strip())
    
    changed = False
    
    # Identify and prune broken mappings
    for path in submodule_paths:
        if path not in mapped_paths:
            print(f"[!] Pruning broken submodule mapping: {path}")
            run_command(f"git rm --cached -r {path}", cwd=target_dir)
            # Force remove directory if it exists and is problematic
            full_path = os.path.join(target_dir, path)
            if os.path.isdir(full_path):
                # Try to remove it using shell to handle locking/permissions better
                run_command(f"rmdir /s /q \"{full_path}\"")
            changed = True

    # Recursively handle submodules that ARE correctly mapped
    for path in mapped_paths:
        full_path = os.path.join(target_dir, path)
        if os.path.isdir(full_path) and os.path.exists(os.path.join(full_path, ".git")):
            if prune_broken_submodules(full_path):
                # If a nested submodule changed, we need to stage it in this parent
                print(f"[*] Staging changes from nested submodule: {path}")
                run_command(f"git add {path}", cwd=target_dir)
                changed = True

    if changed:
        print(f"[*] Committing repairs in: {target_dir}")
        run_command("git add .gitmodules", cwd=target_dir)
        run_command('git commit -m "chore: prune broken nested submodules"', cwd=target_dir)
        return True
    
    return False

if __name__ == "__main__":
    # Start pruning from the root
    prune_broken_submodules(os.getcwd())
    print("[OK] Recursive submodule audit and commit complete.")
