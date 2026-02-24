import os
import json
import configparser

def detect_build_system(path):
    systems = []
    if os.path.exists(os.path.join(path, "package.json")):
        systems.append("node")
    if os.path.exists(os.path.join(path, "Cargo.toml")):
        systems.append("rust")
    if os.path.exists(os.path.join(path, "pyproject.toml")) or os.path.exists(os.path.join(path, "requirements.txt")):
        systems.append("python")
    if os.path.exists(os.path.join(path, "go.mod")):
        systems.append("go")
    if os.path.exists(os.path.join(path, "CMakeLists.txt")):
        systems.append("cmake")
    if os.path.exists(os.path.join(path, "Makefile")):
        systems.append("make")
    
    return ", ".join(systems) if systems else "Unknown"

def map_workspace():
    root = os.getcwd()
    graph = {}
    
    print("Mapping Workspace Dependencies (Optimized)...")
    
    # Get submodules from .gitmodules
    submodules = []
    if os.path.exists(".gitmodules"):
        config = configparser.ConfigParser()
        config.read(".gitmodules")
        for section in config.sections():
            path = config.get(section, "path", fallback=None)
            if path:
                submodules.append(path)

    # Always include the root
    project_dirs = ["."] + submodules
    
    for rel_path in project_dirs:
        abs_path = os.path.normpath(os.path.join(root, rel_path))
        if not os.path.isdir(abs_path):
            continue
            
        name = rel_path if rel_path != "." else "ROOT"
        build_system = detect_build_system(abs_path)
        is_git_repo = os.path.exists(os.path.join(abs_path, ".git"))
        
        graph[name] = {
            "path": rel_path,
            "build_system": build_system,
            "is_git_repo": is_git_repo
        }

    with open("workspace_graph.json", "w", encoding="utf-8") as f:
        json.dump(graph, f, indent=4)
    
    print(f"Mapped {len(graph)} top-level and submodule nodes to workspace_graph.json")
    return graph

if __name__ == "__main__":
    map_workspace()
