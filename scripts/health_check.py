import os
import json
import subprocess

GRAPH_FILE = "workspace_graph.json"
HEALTH_FILE = "workspace_health.json"

def run_check(cmd, cwd):
    try:
        result = subprocess.run(
            cmd, cwd=cwd, shell=True, capture_output=True, 
            text=True, timeout=30
        )
        return result.returncode == 0
    except:
        return False

def probe_node(path):
    # Check if node_modules exists
    if os.path.exists(os.path.join(path, "node_modules")):
        return "🟢 Healthy"
    # Check if package.json exists but no modules
    if os.path.exists(os.path.join(path, "package.json")):
        return "🟡 Needs Init"
    return "🔴 Missing Config"

def probe_python(path):
    # Check for venv or requirements
    if os.path.exists(os.path.join(path, "venv")) or os.path.exists(os.path.join(path, ".venv")):
        return "🟢 Healthy"
    if os.path.exists(os.path.join(path, "requirements.txt")) or os.path.exists(os.path.join(path, "pyproject.toml")):
        return "🟡 Needs Init"
    return "🔴 Missing Config"

def probe_rust(path):
    # Check if target directory exists (indicating a build has happened)
    if os.path.exists(os.path.join(path, "target")):
        return "🟢 Healthy"
    if os.path.exists(os.path.join(path, "Cargo.toml")):
        return "🟡 Needs Build"
    return "🔴 Missing Config"

def probe_generic(path):
    if os.path.exists(os.path.join(path, ".git")):
        return "🟢 Repo OK"
    return "⚪ Unknown"

def check_health():
    if not os.path.exists(GRAPH_FILE):
        print(f"Error: {GRAPH_FILE} not found.")
        return

    with open(GRAPH_FILE, "r", encoding="utf-8") as f:
        graph = json.load(f)

    health_data = {}
    print("Probing Workspace Health...")

    root_dir = os.getcwd()

    for name, info in graph.items():
        rel_path = info["path"]
        abs_path = os.path.normpath(os.path.join(root_dir, rel_path))
        stack = info.get("build_system", "Unknown").lower()
        
        if not os.path.isdir(abs_path):
            health_data[name] = "🔴 Missing Dir"
            continue

        status = "⚪ Unknown"
        if "node" in stack:
            status = probe_node(abs_path)
        elif "python" in stack:
            status = probe_python(abs_path)
        elif "rust" in stack or "cargo" in stack:
            status = probe_rust(abs_path)
        else:
            status = probe_generic(abs_path)
            
        health_data[name] = status
        # print(f"[{name}] -> {status}")

    with open(HEALTH_FILE, "w", encoding="utf-8") as f:
        json.dump(health_data, f, indent=4)

    print(f"Health data saved to {HEALTH_FILE}")
    return health_data

if __name__ == "__main__":
    check_health()
