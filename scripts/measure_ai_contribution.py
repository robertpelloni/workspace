import os
import subprocess
import json
import re
import datetime

AI_PATTERNS = [
    r"bot",
    r"claude",
    r"gemini",
    r"copilot",
    r"maestro",
    r"symphony",
    r"opencode"
]

def run_cmd(cmd, cwd=None):
    try:
        res = subprocess.run(cmd, cwd=cwd, shell=True, capture_output=True, text=True, encoding='utf-8', errors='ignore')
        return res.stdout.strip()
    except Exception as e:
        print(f"    [!] Error running command {cmd} in {cwd}: {e}")
        return ""

def is_ai(author_name, author_email):
    full = f"{author_name} {author_email}".lower()
    for pattern in AI_PATTERNS:
        if re.search(pattern, full):
            return True
    return False

def get_stats():
    print("[*] Analyzing workspace-wide contributions (AI vs Human)...")
    
    # Get all submodules including root
    submodules = [{"name": "ROOT", "path": "."}]
    out = run_cmd('git config --file .gitmodules --get-regexp path')
    for line in out.splitlines():
        if not line: continue
        try:
            parts = line.split()
            name = parts[0].replace('submodule.', '').replace('.path', '')
            path = parts[1]
            submodules.append({"name": name, "path": path})
        except: continue

    report = {
        "summary": {
            "ai_commits": 0,
            "human_commits": 0,
            "ai_additions": 0,
            "human_additions": 0,
            "ai_deletions": 0,
            "human_deletions": 0
        },
        "by_submodule": {}
    }

    for sub in submodules:
        path = os.path.join(os.getcwd(), sub['path'])
        if not os.path.exists(os.path.join(path, ".git")):
            continue
            
        print(f"  [+] Processing {sub['name']}...")
        
        try:
            # Use --max-count to prevent infinite loops or huge memory usage if needed, 
            # but for a full report we want everything.
            # Using --no-merges to avoid double counting additions from merges if they are represented that way.
            log_cmd = 'git log --no-merges --format="%an|%ae" --shortstat'
            process = subprocess.Popen(log_cmd, cwd=path, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, encoding='utf-8', errors='ignore')
            
            sub_stats = {
                "ai_commits": 0,
                "human_commits": 0,
                "ai_additions": 0,
                "human_additions": 0,
                "ai_deletions": 0,
                "human_deletions": 0
            }
            
            current_author_ai = False
            for line in process.stdout:
                line = line.strip()
                if "|" in line:
                    parts = line.split("|")
                    name = parts[0]
                    email = parts[1] if len(parts) > 1 else ""
                    current_author_ai = is_ai(name, email)
                    if current_author_ai:
                        sub_stats["ai_commits"] += 1
                        report["summary"]["ai_commits"] += 1
                    else:
                        sub_stats["human_commits"] += 1
                        report["summary"]["human_commits"] += 1
                elif "insertion" in line or "deletion" in line:
                    additions = 0
                    deletions = 0
                    match_add = re.search(r"(\d+) insertion", line)
                    match_del = re.search(r"(\d+) deletion", line)
                    if match_add: additions = int(match_add.group(1))
                    if match_del: deletions = int(match_del.group(1))
                    
                    if current_author_ai:
                        sub_stats["ai_additions"] += additions
                        sub_stats["ai_deletions"] += deletions
                        report["summary"]["ai_additions"] += additions
                        report["summary"]["ai_deletions"] += deletions
                    else:
                        sub_stats["human_additions"] += additions
                        sub_stats["human_deletions"] += deletions
                        report["summary"]["human_additions"] += additions
                        report["summary"]["human_deletions"] += deletions
            
            process.wait()
            report["by_submodule"][sub['name']] = sub_stats
        except Exception as e:
            print(f"    [!] Error processing {sub['name']}: {e}")

    return report

def save_report(report):
    try:
        with open("AI_CONTRIBUTION_REPORT.json", "w") as f:
            json.dump(report, f, indent=4)
        
        # Generate Markdown summary
        s = report["summary"]
        total_commits = s["ai_commits"] + s["human_commits"]
        total_lines = s["ai_additions"] + s["human_additions"]
        
        ai_commit_pct = (s["ai_commits"] / total_commits * 100) if total_commits > 0 else 0
        ai_line_pct = (s["ai_additions"] / total_lines * 100) if total_lines > 0 else 0

        md = f"""# AI Contribution Report
**Date:** {datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")}

## Global Summary
| Metric | AI Agent | Human | Total | AI % |
| :--- | :--- | :--- | :--- | :--- |
| **Commits** | {s["ai_commits"]} | {s["human_commits"]} | {total_commits} | {ai_commit_pct:.1f}% |
| **Lines Added** | {s["ai_additions"]} | {s["human_additions"]} | {total_lines} | {ai_line_pct:.1f}% |
| **Lines Deleted** | {s["ai_deletions"]} | {s["human_deletions"]} | {s["ai_deletions"] + s["human_deletions"]} | - |

## By Submodule
| Submodule | AI Commits | Human Commits | AI Lines | Human Lines |
| :--- | :--- | :--- | :--- | :--- |
"""
        for name, stats in sorted(report["by_submodule"].items()):
            md += f"| **{name}** | {stats['ai_commits']} | {stats['human_commits']} | {stats['ai_additions']} | {stats['human_additions']} |\n"

        with open("AI_CONTRIBUTION_REPORT.md", "w", encoding="utf-8") as f:
            f.write(md)
        print(f"[OK] Reports generated: AI_CONTRIBUTION_REPORT.json, AI_CONTRIBUTION_REPORT.md")
    except Exception as e:
        print(f"[!] Error saving reports: {e}")

if __name__ == "__main__":
    report = get_stats()
    save_report(report)
