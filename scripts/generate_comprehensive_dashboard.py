import os
import subprocess
import datetime

def run(cmd, cwd=None):
    try:
        res = subprocess.run(cmd, shell=True, cwd=cwd, capture_output=True, text=True, timeout=5)
        return res.stdout.strip()
    except Exception:
        return ""

def get_git_info(cwd):
    if not os.path.exists(os.path.join(cwd, ".git")):
        return None
    branch = run("git rev-parse --abbrev-ref HEAD", cwd)
    commit = run("git log -1 --format='%h'", cwd)
    date = run("git log -1 --format='%cd' --date=short", cwd)
    msg = run("git log -1 --format='%s'", cwd)
    version = ""
    version_file = os.path.join(cwd, "VERSION")
    if os.path.exists(version_file):
        try:
            if os.path.isfile(version_file):
                with open(version_file, "r", encoding="utf-8") as f:
                    version = f.read().strip()
        except Exception:
            pass
    return {"branch": branch, "commit": commit, "date": date, "msg": msg, "version": version}

def generate_dashboard():
    root = os.getcwd()
    repos = []
    for dirpath, dirnames, filenames in os.walk(root):
        # Prune unwanted directories to speed up traversal
        dirnames[:] = [d for d in dirnames if not any(skip in d for skip in ["node_modules", ".venv", "temp_", "build", "dist", ".git", ".cursor", "__pycache__", "bobdesk", "topaz-ffmpeg"])]
        if ".git" in dirnames or ".git" in filenames:
            rel_path = os.path.relpath(dirpath, root)
            if rel_path == ".": rel_path = "Root"
            info = get_git_info(dirpath)
            if info:
                info["path"] = rel_path
                repos.append(info)
                
    repos.sort(key=lambda x: (x["path"].count(os.sep), x["path"]))
    
    md = f"""# Submodule Dashboard & Project Structure
**Last Updated:** {datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")}

## Project Directory Structure Explanation
This monorepo serves as a unified workspace and orchestrator for dozens of independent microservices, libraries, desktop applications, and AI agents.
*   **`Root/`**: Contains the global orchestration scripts (`sync_and_merge.py`, `intelligent_sync_all.py`), universal documentation (`LLM_INSTRUCTIONS.md`, `ROADMAP.md`), and the workspace-level `package.json` / configuration files.
*   **`.gemini/`, `.claude/`, etc.**: AI agent configuration and context directories managing instructions and local extensions for LLMs.
*   **AI Agent Projects**: Folders like `borg`, `metamcp`, `jules-autopilot`, `antigravity-autopilot`, `mcp-superassistant` contain specialized multi-modal and autonomous agents leveraging MCP (Model Context Protocol).
*   **Full-Stack Apps**: Folders like `Chamber.Law`, `cointrade`, `bobeditpro`, `bobfilez` contain entire standalone full-stack applications with their own submodules.
*   **Shared Libraries**: Other directories include shared utilities and libraries nested across the ecosystem.

## Submodule Status & Versions

| Path | Version | Branch | Commit | Date | Message |
| :--- | :--- | :--- | :--- | :--- | :--- |
"""
    for r in repos:
        v = r['version'] if r['version'] else "N/A"
        msg = r['msg'][:50] + ("..." if len(r['msg']) > 50 else "")
        md += f"| {r['path']} | {v} | {r['branch']} | {r['commit']} | {r['date']} | {msg} |\n"
        
    with open("SUBMODULE_DASHBOARD.md", "w", encoding="utf-8") as f:
        f.write(md)
    print("Done")

if __name__ == "__main__":
    generate_dashboard()
