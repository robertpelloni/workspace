import os
import subprocess
import datetime
import json

def run_cmd(cmd, cwd=None):
    try:
        res = subprocess.run(cmd, cwd=cwd, shell=True, capture_output=True, text=True, encoding='utf-8', errors='ignore')
        return res.stdout.strip()
    except:
        return ""

def get_ai_stats():
    if os.path.exists("AI_CONTRIBUTION_REPORT.json"):
        try:
            with open("AI_CONTRIBUTION_REPORT.json", "r") as f:
                return json.load(f)
        except:
            return None
    return None

def get_submodule_info(ai_report):
    print("[*] Gathering high-resolution submodule data...")
    submodules = []
    
    # Get top-level submodules
    out = run_cmd('git config --file .gitmodules --get-regexp path')
    for line in out.splitlines():
        if not line: continue
        parts = line.split()
        name = parts[0].replace('submodule.', '').replace('.path', '')
        path = parts[1]
        
        full_path = os.path.join(os.getcwd(), path)
        
        # 1. Version
        version = "N/A"
        for v_file in ["VERSION", "VERSION.md", "package.json", "pyproject.toml"]:
            v_path = os.path.join(full_path, v_file)
            if os.path.exists(v_path):
                if v_file.endswith(".json"):
                    try:
                        with open(v_path, 'r') as f:
                            version = json.load(f).get('version', 'N/A')
                    except: pass
                elif v_file.endswith(".toml"):
                    try:
                        with open(v_path, 'r') as f:
                            for l in f:
                                if 'version =' in l:
                                    version = l.split('=')[1].strip().strip('"').strip("'")
                                    break
                    except: pass
                else:
                    try:
                        with open(v_path, 'r') as f:
                            version = f.read().strip()
                    except: pass
                if version != "N/A": break

        # 2. Build Status
        build_success = os.path.exists(os.path.join(full_path, ".build_success"))
        status = "✅ Success" if build_success else "⏳ Pending"
        
        # 3. Commit Info
        commit_hash = run_cmd("git rev-parse --short HEAD", cwd=full_path)
        commit_date = run_cmd("git log -1 --format=%ai", cwd=full_path).split(' ')[0]
        commit_msg = run_cmd("git log -1 --format=%s", cwd=full_path)
        if len(commit_msg) > 40: commit_msg = commit_msg[:37] + "..."

        # 4. AI Contribution
        ai_pct = "0.0%"
        if ai_report and "by_submodule" in ai_report:
            sub_ai = ai_report["by_submodule"].get(name)
            if sub_ai:
                total = sub_ai["ai_commits"] + sub_ai["human_commits"]
                if total > 0:
                    ai_pct = f"{(sub_ai['ai_commits'] / total * 100):.1f}%"

        submodules.append({
            "name": name,
            "path": path,
            "version": version,
            "status": status,
            "commit": commit_hash,
            "date": commit_date,
            "message": commit_msg,
            "ai_pct": ai_pct
        })
    
    return submodules

def generate_dashboard(submodules, ai_report):
    now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    
    md = f"""# Omni-Workspace Advanced Dashboard
**Last Updated:** {now}
**Project Version:** {open('VERSION').read().strip() if os.path.exists('VERSION') else 'N/A'}

## Project Directory Structure
The workspace is organized into several functional clusters:
- **Root**: Core orchestration scripts, configuration, and global documentation.
- **`antigravity-autopilot/`**: Autonomous agent frameworks and automation tools.
- **`bg/`**: The "bob's game" ecosystem, including engine components and legacy references.
- **`bobmani/`**: Rhythm game ecosystem (StepMania/ITGmania themes and tools).
- **`bobsaver/`**: Visualizer ecosystem (MilkDrop, JWildfire, projectM).
- **`docs/`**: Unified project requirements, design, and research documentation.
- **`scripts/`**: Automation, synchronization, and maintenance utilities.
"""

    if ai_report:
        s = ai_report["summary"]
        total_commits = s["ai_commits"] + s["human_commits"]
        ai_commit_pct = (s["ai_commits"] / total_commits * 100) if total_commits > 0 else 0
        md += f"""
## AI Contribution Summary
- **AI-Generated Commits:** {s['ai_commits']} ({ai_commit_pct:.1f}% of total)
- **AI-Added Lines:** {s['ai_additions']:,}
- **AI-Deleted Lines:** {s['ai_deletions']:,}
"""

    md += f"""
## Submodule Inventory ({len(submodules)} total)

| Submodule | Version | Status | AI% | Commit | Date | Latest Change |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
"""
    
    for s in sorted(submodules, key=lambda x: x['name'].lower()):
        md += f"| **{s['name']}** | `{s['version']}` | {s['status']} | {s['ai_pct']} | `{s['commit']}` | {s['date']} | {s['message']} |\n"

    with open("SUBMODULE_DASHBOARD.md", "w", encoding="utf-8") as f:
        f.write(md)
    print("[OK] Advanced dashboard generated with AI metrics.")

if __name__ == "__main__":
    ai_report = get_ai_stats()
    subs = get_submodule_info(ai_report)
    generate_dashboard(subs, ai_report)
