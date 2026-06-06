import os
import shutil

ROOT_DIR = os.getcwd()
SOURCE_FILE = os.path.join(ROOT_DIR, "docs", "UNIVERSAL_LLM_INSTRUCTIONS.md")

def find_git_repos(root):
    """Find all directories containing a .git file or folder, recursively."""
    repos = []
    for dirpath, dirnames, filenames in os.walk(root):
        # Skip the root itself
        if dirpath == root:
            continue
            
        # Check if this directory is a git repo
        if ".git" in dirnames or ".git" in filenames:
            repos.append(dirpath)
            
        # Optimization: Don't dive into .git folders or node_modules
        if ".git" in dirnames:
            dirnames.remove(".git")
        if "node_modules" in dirnames:
            dirnames.remove("node_modules")
            
    return repos

def propagate():
    if not os.path.exists(SOURCE_FILE):
        print(f"Error: Source file {SOURCE_FILE} not found!")
        return

    print(f"Resiliently Propagating Universal Instructions from {SOURCE_FILE}...")
    
    repo_paths = find_git_repos(ROOT_DIR)
    count = 0
    
    for repo_path in repo_paths:
        target_docs_dir = os.path.join(repo_path, "docs")
        target_file = os.path.join(target_docs_dir, "UNIVERSAL_LLM_INSTRUCTIONS.md")
        
        try:
            if not os.path.exists(target_docs_dir):
                os.makedirs(target_docs_dir)
            
            shutil.copy2(SOURCE_FILE, target_file)
            # print(f"Copied to: {os.path.relpath(repo_path, ROOT_DIR)}/docs/")
            count += 1
        except Exception as e:
            rel_path = os.path.relpath(repo_path, ROOT_DIR)
            print(f"Failed to copy to {rel_path}: {e}")

    print(f"\nDone. Propagated instructions to {count} repositories/submodules.")

if __name__ == "__main__":
    propagate()
