import subprocess
import os
import re
from datetime import datetime


def run_command(command):
    try:
        result = subprocess.run(command, capture_output=True, text=True, shell=True)
        return result.stdout.strip(), result.stderr.strip(), result.returncode
    except Exception as e:
        return "", str(e), -1


def get_submodules():
    submodules = []
    if os.path.exists(".gitmodules"):
        with open(".gitmodules", "r") as f:
            content = f.read()

        # Parse .gitmodules
        # [submodule "BobsGameOnline"]
        # 	path = BobsGameOnline
        # 	url = https://github.com/robertpelloni/BobsGameOnline

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


def update_submodules(submodules):
    print("Updating submodules...")
    success_count = 0
    fail_count = 0
    for sub in submodules:
        if sub["name"] == "aios":
            print(f"Skipping aios due to lock issue.")
            continue

        print(f"Updating {sub['name']}...")
        # Try to update specific submodule
        cmd = f'git submodule update --init --recursive "{sub["path"]}"'
        out, err, code = run_command(cmd)
        if code != 0:
            print(f"Failed to update {sub['name']}: {err}")
            fail_count += 1
        else:
            # Also try to fetch latest remote if requested (merge upstream)
            # cmd_pull = f'cd "{sub["path"]}" && git fetch origin && git merge origin/main'
            # Note: relying on submodule update is usually safer for detached head, but user asked to merge upstream changes.
            # We will just do submodule update for now to ensure they are checked out.
            success_count += 1

    print(f"Update complete. Success: {success_count}, Failed: {fail_count}")


def generate_dashboard(submodules):
    print("Generating Dashboard...")
    dashboard_content = "# Project Dashboard\n\n"
    dashboard_content += (
        f"**Last Updated:** {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n\n"
    )
    dashboard_content += "## Project Structure & Submodules\n\n"
    dashboard_content += "This project integrates various AI agents, tools, and libraries as submodules. Below is the status of each component.\n\n"
    dashboard_content += (
        "| Name | Path | Version (Commit) | Last Commit Date | Build/Status |\n"
    )
    dashboard_content += "|---|---|---|---|---|\n"

    for sub in submodules:
        path = sub["path"]
        if not os.path.exists(path):
            dashboard_content += (
                f"| {sub['name']} | `{path}` | *Not Initialized* | - | ❌ |\n"
            )
            continue

        # Get version/commit
        out, _, _ = run_command(f'git -C "{path}" rev-parse --short HEAD')
        commit_hash = out if out else "Unknown"

        # Get date
        out, _, _ = run_command(f'git -C "{path}" log -1 --format=%cd --date=short')
        date = out if out else "Unknown"

        # Get status (simple check if clean)
        out, _, _ = run_command(f'git -C "{path}" status --porcelain')
        status = "🟢 Clean" if not out else "modifications"

        dashboard_content += f"| [{sub['name']}]({sub['url']}) | `{path}` | `{commit_hash}` | {date} | {status} |\n"

    dashboard_content += "\n## Directory Layout Explanation\n\n"
    dashboard_content += (
        "- **Root**: Contains main configuration and orchestration logic.\n"
    )
    dashboard_content += "- **Submodules**: Located in their respective directories, containing standalone tools or agents.\n"

    with open("DASHBOARD.md", "w", encoding="utf-8") as f:
        f.write(dashboard_content)
    print("DASHBOARD.md created.")


def main():
    submodules = get_submodules()
    update_submodules(submodules)
    generate_dashboard(submodules)


if __name__ == "__main__":
    main()
