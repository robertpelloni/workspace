import os
import subprocess
import datetime

def run_cmd(cmd, cwd=None):
    res = subprocess.run(cmd, cwd=cwd, shell=True, capture_output=True, text=True)
    return res.stdout.strip()

out = run_cmd('git config --file .gitmodules --get-regexp path')
submodules = [line.split()[1] for line in out.splitlines() if line]

def get_git_info(cwd):
    if not os.path.exists(cwd):
        return None
    branch = run_cmd("git rev-parse --abbrev-ref HEAD", cwd)
    commit = run_cmd("git log -1 --format='%h'", cwd)
    date = run_cmd("git log -1 --format='%cd' --date=short", cwd)
    msg = run_cmd("git log -1 --format='%s'", cwd)
    version = ""
    version_file = os.path.join(cwd, "VERSION")
    if os.path.exists(version_file):
        try:
            with open(version_file, "r", encoding="utf-8") as f:
                version = f.read().strip()
        except Exception:
            pass
    return {"branch": branch, "commit": commit, "date": date, "msg": msg, "version": version}

md = f"""# Omni-Workspace Submodule Dashboard
**Last Updated:** {datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")}

## Project Directory Structure Explanation
This monorepo serves as a unified workspace and orchestrator for dozens of independent microservices, libraries, desktop applications, and AI agents.
*   **`Root/`**: Contains the global orchestration scripts, universal documentation (`LLM_INSTRUCTIONS.md`, `ROADMAP.md`), and the workspace-level configuration.
*   **`.gemini/`, `.claude/`, etc.**: AI agent configuration and context directories.
*   **AI Agent Projects**: Folders like `borg`, `metamcp`, `jules-autopilot`, `antigravity-autopilot` contain specialized multi-modal and autonomous agents.
*   **Full-Stack Apps**: Folders like `Chamber.Law`, `bobeditpro`, `bobfilez` contain entire standalone full-stack applications.
*   **Shared Libraries**: Other directories include shared utilities and libraries nested across the ecosystem.

## Submodule Status & Versions

| Path | Version | Branch | Commit | Date | Message |
| :--- | :--- | :--- | :--- | :--- | :--- |
"""

for sm in submodules:
    info = get_git_info(sm)
    if info:
        v = info['version'] if info['version'] else "N/A"
        msg = info['msg'][:50] + ("..." if len(info['msg']) > 50 else "")
        md += f"| {sm} | {v} | {info['branch']} | {info['commit']} | {info['date']} | {msg} |\n"

with open("SUBMODULE_DASHBOARD.md", "w", encoding="utf-8") as f:
    f.write(md)
print("Dashboard updated.")