import os
import subprocess
import datetime

# Unbuffered output
import sys
sys.stdout.reconfigure(encoding='utf-8')

ROOT_DIR = os.getcwd()
OUTPUT_FILE = "SUBMODULE_DASHBOARD.md"

def run_command(cmd, cwd):
    try:
        result = subprocess.run(
            cmd, cwd=cwd, shell=True, check=True, 
            stdout=subprocess.PIPE, stderr=subprocess.PIPE, 
            text=True, encoding='utf-8', errors='replace'
        )
        return result.stdout.strip()
    except:
        return None

def get_git_info(path):
    if not os.path.exists(os.path.join(path, ".git")) and not os.path.isfile(os.path.join(path, ".git")):
        return None

    info = {}
    
    # Commit Hash
    info['hash'] = run_command("git rev-parse --short HEAD", path)
    
    # Branch
    info['branch'] = run_command("git rev-parse --abbrev-ref HEAD", path)
    
    # Last Commit Date
    info['date'] = run_command("git log -1 --format=%cd --date=short", path)
    
    # Last Commit Message
    msg = run_command("git log -1 --format=%s", path)
    if msg:
        info['message'] = msg[:50] + "..." if len(msg) > 50 else msg
    
    # Remote URL
    info['url'] = run_command("git config --get remote.origin.url", path)
    
    return info

def generate_dashboard():
    print("Generating Dashboard...")
    
    lines = []
    lines.append("# Submodule Dashboard")
    lines.append(f"**Last Updated:** {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
    lines.append("This document tracks the status of all submodules in the workspace.\n")
    
    lines.append("| Path | Branch | Commit | Date | Message |")
    lines.append("| :--- | :--- | :--- | :--- | :--- |")
    
    # Get list of submodules
    # We use 'git submodule status --recursive' to find them
    submodules_output = run_command("git submodule status", ROOT_DIR)
    
    if submodules_output:
        for line in submodules_output.split('\n'):
            parts = line.strip().split()
            if len(parts) >= 2:
                # parts[1] is the path
                sub_path = parts[1]
                abs_path = os.path.join(ROOT_DIR, sub_path)
                
                if os.path.exists(abs_path):
                    info = get_git_info(abs_path)
                    if info:
                        # Markdown table row
                        # Path | Branch | Hash | Date | Message
                        row = f"| `{sub_path}` | {info.get('branch', 'N/A')} | `{info.get('hash', 'N/A')}` | {info.get('date', 'N/A')} | {info.get('message', '')} |"
                        lines.append(row)
    
    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))
    
    print(f"Dashboard saved to {OUTPUT_FILE}")

if __name__ == "__main__":
    generate_dashboard()
