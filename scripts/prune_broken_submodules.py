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
        return

    # Get all paths in .gitmodules
    gitmodules_path = os.path.join(target_dir, ".gitmodules")
    mapped_paths = []
    if os.path.exists(gitmodules_path):
        with open(gitmodules_path, "r") as f:
            for line in f:
                if "path =" in line:
                    mapped_paths.append(line.split("=")[-1].strip())
    
    # Identify and prune broken mappings
    for path in submodule_paths:
        if path not in mapped_paths:
            print(f"[!] Pruning broken submodule mapping: {path}")
            run_command(f"git rm --cached {path}", cwd=target_dir)
            # If it's a directory, we might need to remove it if it's empty or just a ghost
            full_path = os.path.join(target_dir, path)
            if os.path.isdir(full_path) and not os.listdir(full_path):
                try:
                    os.rmdir(full_path)
                except:
                    pass

    # Recursively handle submodules that ARE correctly mapped
    for path in mapped_paths:
        full_path = os.path.join(target_dir, path)
        if os.path.isdir(full_path) and os.path.exists(os.path.join(full_path, ".git")):
            prune_broken_submodules(full_path)

if __name__ == "__main__":
    # Start pruning from the root
    prune_broken_submodules(os.getcwd())
    print("[OK] Submodule audit and prune complete.")
