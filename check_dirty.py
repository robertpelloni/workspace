#!/usr/bin/env python3
"""Check and commit dirty submodules."""

import subprocess
import shlex
from pathlib import Path

WORKSPACE = Path(r"C:\Users\hyper\workspace")


def run(args, cwd=None, timeout=60):
    if isinstance(args, str):
        args = shlex.split(args)
    try:
        r = subprocess.run(
            args, capture_output=True, text=True, cwd=cwd, timeout=timeout
        )
        return r.returncode == 0, r.stdout.strip(), r.stderr.strip()
    except (subprocess.TimeoutExpired, OSError):
        return False, "", "error"


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


def get_default_branch(repo_path):
    ok, out, _ = run(["git", "symbolic-ref", "refs/remotes/origin/HEAD"], cwd=repo_path)
    if ok and out:
        return out.split("/")[-1]
    ok, _, _ = run(["git", "rev-parse", "--verify", "origin/main"], cwd=repo_path)
    if ok:
        return "main"
    ok, _, _ = run(["git", "rev-parse", "--verify", "origin/master"], cwd=repo_path)
    if ok:
        return "master"
    return "main"


def main():
    subs = get_submodules()
    print(f"Checking {len(subs)} submodules for dirty state...")

    committed = 0
    for sub in subs:
        full_path = str(WORKSPACE / sub)
        if not (WORKSPACE / sub).exists():
            continue

        ok, _, _ = run(["git", "rev-parse", "--git-dir"], cwd=full_path)
        if not ok:
            continue

        # Check for dirty working directory
        ok, status, _ = run(["git", "status", "--porcelain"], cwd=full_path, timeout=30)
        if not ok or not status.strip():
            continue

        # Filter out submodule pointer changes (M in first column)
        lines = [l for l in status.split("\n") if l.strip()]
        commitable = [
            l for l in lines if not l.startswith(" M")
        ]  # Skip modified-in-worktree only

        if not commitable:
            continue

        branch = get_default_branch(full_path)

        print(f"  DIRTY: {sub} ({len(commitable)} changes)")
        for l in commitable[:5]:
            print(f"    {l.strip()}")

        # Stage and commit
        ok, _, _ = run(["git", "add", "-A"], cwd=full_path)
        ok, _, _ = run(
            [
                "git",
                "commit",
                "-m",
                "auto: commit dirty working directory before reconciliation",
            ],
            cwd=full_path,
        )
        if ok:
            ok, _, _ = run(["git", "push", "origin", branch], cwd=full_path, timeout=60)
            if ok:
                print("    PUSHED")
                committed += 1
            else:
                print("    PUSH FAILED")
        else:
            print("    NOTHING TO COMMIT")

    print(f"\nCommitted and pushed {committed} dirty submodules")


if __name__ == "__main__":
    main()
