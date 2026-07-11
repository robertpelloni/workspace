import os
import subprocess

def run_command(cmd, cwd=None):
    try:
        result = subprocess.run(cmd, cwd=cwd, shell=True, capture_output=True, text=True)
        return result.stdout.strip(), result.stderr.strip()
    except Exception as e:
        return "", str(e)

def audit_dir(target_dir):
    # Check if this is a git repo
    is_git = os.path.isdir(os.path.join(target_dir, ".git")) or os.path.isfile(os.path.join(target_dir, ".git"))
    
    if is_git:
        print(f"[*] Auditing: {target_dir}")
        
        # Get all 160000 entries in the index
        index_files, _ = run_command("git ls-files --stage", cwd=target_dir)
        submodule_paths = []
        for line in index_files.splitlines():
            if line.startswith("160000"):
                path = line.split("\t")[-1]
                submodule_paths.append(path)
        
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
                print(f"[!] Pruning broken submodule mapping: {path} in {target_dir}")
                run_command(f"git rm --cached -r \"{path}\"", cwd=target_dir)
                # If it's a directory, we might need to remove it if it's empty or just a ghost
                full_path = os.path.join(target_dir, path)
                if os.path.isdir(full_path):
                    # Try to remove it using shell
                    run_command(f"rmdir /s /q \"{full_path}\"")

    # Walk all subdirectories to find more directories (might contain git repos)
    try:
        entries = os.listdir(target_dir)
    except Exception:
        return

    for entry in entries:
        full_entry_path = os.path.join(target_dir, entry)
        if os.path.isdir(full_entry_path) and entry != ".git" and entry != "node_modules":
            audit_dir(full_entry_path)

if __name__ == "__main__":
    root_path = os.getcwd()
    audit_dir(root_path)
    print("[OK] Deep tree submodule audit and prune complete.")
