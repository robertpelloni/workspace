#!/usr/bin/env python3
"""Generate structural map of all submodules with their remote URLs, commits, and locations."""

import subprocess
import shlex
from pathlib import Path
from datetime import datetime

WORKSPACE = Path(r"C:\Users\hyper\workspace")


def run(args, cwd=None, timeout=30):
    if isinstance(args, str):
        args = shlex.split(args)
    try:
        r = subprocess.run(
            args, capture_output=True, text=True, cwd=cwd, timeout=timeout
        )
        return r.returncode == 0, r.stdout.strip(), r.stderr.strip()
    except (subprocess.TimeoutExpired, OSError) as e:
        return False, "", str(e)


def get_submodules():
    gitmodules = WORKSPACE / ".gitmodules"
    subs = []
    try:
        with open(gitmodules, encoding="utf-8") as f:
            for line in f:
                line = line.strip()
                if line.startswith("path"):
                    subs.append(line.split("=", 1)[1].strip())
    except OSError:
        pass
    return subs


def get_submodule_url(path):
    ok, out, _ = run(
        ["git", "config", "--file", ".gitmodules", f"submodule.{path}.url"],
        cwd=str(WORKSPACE),
    )
    return out if ok else "N/A"


def get_submodule_commit(path):
    full_path = str(WORKSPACE / path)
    ok, out, _ = run(["git", "rev-parse", "HEAD"], cwd=full_path, timeout=10)
    return out[:12] if ok else "not initialized"


def main():
    subs = get_submodules()
    now = datetime.now().strftime("%Y-%m-%d %H:%M")

    lines = []
    lines.append(f"# Structural Map — Generated {now}")
    lines.append(f"# Total submodules: {len(subs)}")
    lines.append("")
    lines.append(f"{'Path':<50} {'URL':<65} {'Commit':<14} {'Status'}")
    lines.append(f"{'-' * 50} {'-' * 65} {'-' * 14} {'-' * 10}")

    initialized = 0
    for sub in subs:
        url = get_submodule_url(sub)
        commit = get_submodule_commit(sub)
        status = "OK" if commit != "not initialized" else "MISSING"
        if status == "OK":
            initialized += 1
        lines.append(f"{sub:<50} {url:<65} {commit:<14} {status}")

    lines.append("")
    lines.append(f"# Initialized: {initialized}/{len(subs)}")

    output = "\n".join(lines)
    print(output)

    try:
        with open(WORKSPACE / "STRUCTURAL_MAP.md", "w", encoding="utf-8") as f:
            f.write(output)
        print("\nSaved to STRUCTURAL_MAP.md")
    except OSError:
        pass


if __name__ == "__main__":
    main()
