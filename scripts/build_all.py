import os
import subprocess
import json
import argparse

def run_command(command, cwd=None):
    try:
        print(f"Executing: {command} in {cwd if cwd else os.getcwd()}")
        result = subprocess.run(command, shell=True, cwd=cwd, text=True, capture_output=True)
        if result.returncode == 0:
            print(f"Success: {command}")
            return True, result.stdout
        else:
            print(f"Error ({result.returncode}): {result.stderr}")
            return False, result.stderr
    except Exception as e:
        print(f"Exception: {str(e)}")
        return False, str(e)

def build_project(name, data):
    path = data.get("path")
    build_system = data.get("build_system", "").lower()
    
    if not path or not os.path.exists(path):
        print(f"Skipping {name}: Path not found.")
        return False

    print(f"\n--- Building {name} ({build_system}) ---")
    
    success = True
    
    # Node.js Build (Pre-check for Bun in jules-autopilot)
    if "node" in build_system:
        if "jules-autopilot" in name or os.path.exists(os.path.join(path, "bun.lockb")):
            print("Using Bun for Node build...")
            s, _ = run_command("bun install", cwd=path)
            if s:
                if os.path.exists(os.path.join(path, "prisma")):
                    run_command("npx prisma generate", cwd=path)
                s, _ = run_command("npm run build", cwd=path)
            success = s
        else:
            print("Using NPM for Node build...")
            s, _ = run_command("npm install", cwd=path)
            if s:
                s, _ = run_command("npm run build", cwd=path)
            success = s

    # Python Build (Check for requirements.txt)
    elif "python" in build_system:
        if os.path.exists(os.path.join(path, "requirements.txt")):
            success, _ = run_command("pip install -r requirements.txt", cwd=path)
        elif os.path.exists(os.path.join(path, "pyproject.toml")):
            success, _ = run_command("pip install .", cwd=path)

    # CMake / Make Build
    elif "cmake" in build_system:
        build_dir = os.path.join(path, "build")
        if not os.path.exists(build_dir):
            os.makedirs(build_dir)
        s, _ = run_command("cmake ..", cwd=build_dir)
        if s:
            s, _ = run_command("cmake --build .", cwd=build_dir)
        success = s

    elif "make" in build_system:
        success, _ = run_command("make", cwd=path)

    return success

def main():
    parser = argparse.ArgumentParser(description="Workspace-wide Build Orchestrator")
    parser.add_argument("--project", help="Build a specific project only")
    args = parser.parse_args()

    # Ensure graph is up to date
    if not os.path.exists("workspace_graph.json"):
        from map_workspace import map_workspace
        map_workspace()
    
    with open("workspace_graph.json", "r", encoding="utf-8") as f:
        graph = json.load(f)

    results = {}
    
    if args.project:
        if args.project in graph:
            success = build_project(args.project, graph[args.project])
            results[args.project] = "Success" if success else "Failed"
        else:
            print(f"Project '{args.project}' not found in workspace_graph.json")
            return
    else:
        # Build all projects in order (ROOT last)
        projects = list(graph.keys())
        if "ROOT" in projects:
            projects.remove("ROOT")
            projects.append("ROOT")
            
        for name in projects:
            success = build_project(name, graph[name])
            results[name] = "Success" if success else "Failed"

    print("\n--- Final Build Report ---")
    print(json.dumps(results, indent=4))
    
    with open("build_results.json", "w", encoding="utf-8") as f:
        json.dump(results, f, indent=4)

if __name__ == "__main__":
    main()
