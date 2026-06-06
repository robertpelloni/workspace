import os
import subprocess
import datetime
import sys

# Unbuffered output
sys.stdout.reconfigure(encoding='utf-8')

ROOT_DIR = os.getcwd()
OUTPUT_FILE = "SUBMODULE_DASHBOARD.md"

def run_command(cmd, cwd):
    try:
        result = subprocess.run(
            cmd, cwd=cwd, shell=True, 
            stdout=subprocess.PIPE, stderr=subprocess.PIPE, 
            text=True, encoding='utf-8', errors='replace'
        )
        return result.stdout.strip()
    except Exception as e:
        return None

def get_git_info(path):
    if not os.path.exists(os.path.join(path, ".git")) and not os.path.isfile(os.path.join(path, ".git")):
        return None

    info = {}
    info['hash'] = run_command("git rev-parse --short HEAD", path)
    info['branch'] = run_command("git rev-parse --abbrev-ref HEAD", path)
    info['date'] = run_command("git log -1 --format=%cd --date=short", path)
    
    msg = run_command("git log -1 --format=%s", path)
    if msg:
        info['message'] = (msg[:50] + "...") if len(msg) > 50 else msg
    
    info['url'] = run_command("git config --get remote.origin.url", path)
    return info

def scan_submodules_recursive(current_dir, base_path=""):
    """Recursively find all git repositories within the workspace."""
    found = []
    
    # Use git submodule status --recursive to get all paths
    output = run_command("git submodule status --recursive", current_dir)
    if output:
        for line in output.split('\n'):
            line = line.strip()
            if not line: continue
            
            # Format is typically: [+/-/ ]hash path (branch)
            # We just need the path which is the second or third part
            parts = line.split()
            # If line starts with status prefix (+, -, U), path is parts[1]
            # If no prefix, path is parts[1]
            if parts[0] in ['+', '-', 'U']:
                path = parts[1]
            else:
                path = parts[1]
                
            found.append(path)
    return found

def generate_dashboard():
    print("Generating Recursive Dashboard...")
    
    lines = []
    lines.append("# Submodule Dashboard (Recursive)")
    lines.append(f"**Last Updated:** {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
    lines.append("This document tracks the status of all submodules and nested repositories in the workspace.\n")
    
    lines.append("| Path | Branch | Commit | Date | Message |")
    lines.append("| :--- | :--- | :--- | :--- | :--- |")
    
    submodule_paths = scan_submodules_recursive(ROOT_DIR)
    
    # Sort paths for readability
    submodule_paths.sort()
    
    for sub_path in submodule_paths:
        abs_path = os.path.join(ROOT_DIR, sub_path)
        if os.path.exists(abs_path):
            info = get_git_info(abs_path)
            if info:
                row = f"| `{sub_path}` | {info.get('branch', 'N/A')} | `{info.get('hash', 'N/A')}` | {info.get('date', 'N/A')} | {info.get('message', '')} |"
                lines.append(row)
    
    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))
    
    print(f"Dashboard saved to {OUTPUT_FILE}")

if __name__ == "__main__":
    generate_dashboard()
