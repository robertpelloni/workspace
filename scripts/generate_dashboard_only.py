import subprocess
import os
import re
from datetime import datetime


def run_command(command):
    try:
        result = subprocess.run(command, capture_output=True, text=True, shell=True)
        return result.stdout.strip()
    except Exception:
        return "Unknown"


def get_submodules():
    submodules = []
    if os.path.exists(".gitmodules"):
        with open(".gitmodules", "r") as f:
            content = f.read()

        matches = re.finditer(
            r'\[submodule "(.*?)"\]\s*path = (.*?)\s*url = (.*?)\s',
            content,
            re.MULTILINE | re.DOTALL,
        )
        for match in matches:
            name = match.group(1).strip()
            path = match.group(2).strip()
            url = match.group(3).strip()
            submodules.append({"name": name, "path": path, "url": url})
    return submodules


def generate_dashboard(submodules):
    print("Generating Dashboard...")
    dashboard_content = "# Project Dashboard\n\n"
    dashboard_content += (
        f"**Last Updated:** {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n\n"
    )
    dashboard_content += "## Project Structure & Submodules\n\n"
    dashboard_content += "| Name | Path | Version | Status |\n"
    dashboard_content += "|---|---|---|---|\n"

    for sub in submodules:
        path = sub["path"]
        if not os.path.exists(path):
            dashboard_content += (
                f"| {sub['name']} | `{path}` | *Not Initialized* | ❌ |\n"
            )
            continue

        # Get version/commit
        commit_hash = run_command(f'git -C "{path}" rev-parse --short HEAD')
        if not commit_hash:
            commit_hash = "Unknown"

        # Get status (simple check if clean)
        status_out = run_command(f'git -C "{path}" status --porcelain')
        status = "🟢 Clean" if not status_out else "⚠️ Modified"

        dashboard_content += f"| [{sub['name']}]({sub['url']}) | `{path}` | `{commit_hash}` | {status} |\n"

    dashboard_content += "\n## Directory Layout Explanation\n\n"
    dashboard_content += (
        "- **Root**: Contains main configuration and orchestration logic.\n"
    )
    dashboard_content += "- **Submodules**: Located in their respective directories, containing standalone tools or agents.\n"

    with open("DASHBOARD.md", "w", encoding="utf-8") as f:
        f.write(dashboard_content)
    print("DASHBOARD.md created.")


if __name__ == "__main__":
    submodules = get_submodules()
    generate_dashboard(submodules)
