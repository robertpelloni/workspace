import os
import subprocess
import configparser

def run_command(cmd, cwd=None):
    try:
        result = subprocess.run(cmd, cwd=cwd, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        print(f"Error running command: {cmd}")
        print(f"Error output: {e.stderr}")
        return None

def prune_broken_submodules():
    if not os.path.exists(".gitmodules"):
        print("No .gitmodules file found.")
        return

    config = configparser.ConfigParser()
    config.read(".gitmodules")

    sections_to_remove = []

    for section in config.sections():
        path = config.get(section, "path", fallback=None)
        if path and not os.path.exists(path):
            print(f"Broken submodule detected: {section} at path '{path}'")
            sections_to_remove.append((section, path))

    for section, path in sections_to_remove:
        submodule_name = section.replace('submodule "', '').replace('"', '')
        print(f"Pruning submodule '{submodule_name}'...")
        
        # Deinit the submodule
        run_command(f"git submodule deinit -f \"{path}\"")
        
        # Remove from .gitmodules and git index
        run_command(f"git rm -f \"{path}\"")
        
        # Manually remove the .git/modules directory if it exists
        git_modules_dir = os.path.join(".git", "modules", submodule_name)
        if os.path.exists(git_modules_dir):
            import shutil
            shutil.rmtree(git_modules_dir)
            print(f"Removed .git/modules/{submodule_name}")

    if not sections_to_remove:
        print("No broken submodules found.")
    else:
        print(f"Pruned {len(sections_to_remove)} broken submodules.")

if __name__ == "__main__":
    prune_broken_submodules()
