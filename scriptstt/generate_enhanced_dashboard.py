import os
import subprocess
import datetime
import json
import sys

# Unbuffered output
sys.stdout.reconfigure(encoding='utf-8')

ROOT_DIR = os.getcwd()
OUTPUT_FILE = "SUBMODULE_DASHBOARD.md"
GRAPH_FILE = "workspace_graph.json"
HEALTH_FILE = "workspace_health.json"

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
    info['hash'] = run_command("git rev-parse --short HEAD", path)
    info['branch'] = run_command("git rev-parse --abbrev-ref HEAD", path)
    info['date'] = run_command("git log -1 --format=%cd --date=short", path)
    
    msg = run_command("git log -1 --format=%s", path)
    if msg:
        info['message'] = (msg[:50] + "...") if len(msg) > 50 else msg
    
    return info

def generate_dashboard():
    print("Generating Live Health Dashboard...")
    
    graph = {}
    if os.path.exists(GRAPH_FILE):
        with open(GRAPH_FILE, "r", encoding="utf-8") as f:
            graph = json.load(f)

    health = {}
    if os.path.exists(HEALTH_FILE):
        with open(HEALTH_FILE, "r", encoding="utf-8") as f:
            health = json.load(f)

    lines = []
    lines.append("# Submodule Dashboard & Tech Stack")
    lines.append(f"**Last Updated:** {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    lines.append("\nThis document tracks the **Health**, **Tech Stack**, and **Git Status** of all submodules.\n")
    
    lines.append("| Health | Path | Tech Stack | Branch | Commit | Message |")
    lines.append("| :--- | :--- | :--- | :--- | :--- | :--- |")
    
    # Sort by path
    sorted_nodes = sorted(graph.keys())
    
    for name in sorted_nodes:
        node = graph[name]
        rel_path = node['path']
        abs_path = os.path.normpath(os.path.join(ROOT_DIR, rel_path))
        
        if os.path.exists(abs_path):
            info = get_git_info(abs_path)
            if info:
                stack = node.get('build_system', 'Unknown')
                status = health.get(name, "⚪ Unknown")
                row = f"| {status} | `{rel_path}` | **{stack}** | {info.get('branch', 'N/A')} | `{info.get('hash', 'N/A')}` | {info.get('message', '')} |"
                lines.append(row)
    
    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))
    
    print(f"Live Dashboard saved to {OUTPUT_FILE}")

if __name__ == "__main__":
    generate_dashboard()
