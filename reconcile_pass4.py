#!/usr/bin/env python3
"""
Reconciliation Pass 4 — Fresh fetch, find new unmerged feature branches.
v5.250.0 → v5.251.0

Skips repos already fully merged in prior passes; focuses on new activity.
"""

import subprocess
import shlex
import json
from datetime import datetime
from pathlib import Path

WORKSPACE = Path(r"C:\Users\hyper\workspace")
LOG_FILE = WORKSPACE / "merge_pass4.log"
STATE_FILE = WORKSPACE / "merge_pass4_state.json"

# Upstream forks or repos with massive numbers of branches to skip
SKIP_REPOS = {
    "bgtk", "bobium", "bqt", "element-web", "FFmpeg", "jdk", "llvm-project",
    "stepmania", "geany", "npp", "electricsheep", "browser-use",
    "openclaw-config", "openclaw-dashboard", "projectM-upstream",
    "apophysis-j", "timidity", "projectm", "bdwgc", "grammars-v4",
    "tabby", "mk64", "sm64coopdx", "neverball", "MarbleBlast", "OpenMBU",
    "mcp-superassistant", "pi-mono", "topaz-ffmpeg", "warp", "TurntUpToddler",
    "bobmania", "ksm-v2", "bobmani/arrowvortex", "bobmani/beatoraja",
    "bobmani/itgmania", "bobmani/Simply-Love-SM5", "bobmani/ksm-v2",
}

MAX_BRANCHES_PER_REPO = 25


def run(args, cwd=None, timeout=60):
    if isinstance(args, str):
        args = shlex.split(args)
    try:
        r = subprocess.run(args, capture_output=True, text=True, cwd=cwd, timeout=timeout)
        return r.returncode == 0, r.stdout.strip(), r.stderr.strip()
    except (subprocess.TimeoutExpired, OSError) as e:
        if isinstance(e, subprocess.TimeoutExpired):
            return False, "", "TIMEOUT"
        return False, "", str(e)


def log(msg):
    safe_msg = msg.replace("\u2713", "[OK]").replace("\u2717", "[FAIL]")
    try:
        print(safe_msg)
    except UnicodeEncodeError:
        print(safe_msg.encode("ascii", "replace").decode())
    try:
        with open(LOG_FILE, "a", encoding="utf-8") as f:
            f.write(msg + "\n")
    except OSError:
        pass


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
    ok, out, _ = run(["git", "rev-parse", "--abbrev-ref", "HEAD"], cwd=repo_path)
    if ok and out != "HEAD":
        return out
    return "main"


def load_state():
    try:
        with open(STATE_FILE, encoding="utf-8") as f:
            return json.load(f)
    except (OSError, json.JSONDecodeError):
        return {"completed": [], "merged": {}}


def save_state(state):
    try:
        with open(STATE_FILE, "w", encoding="utf-8") as f:
            json.dump(state, f, indent=2)
    except OSError:
        pass


def process_submodule(sub_path, state):
    if sub_path in state.get("completed", []):
        return {"path": sub_path, "status": "already_done", "merges": [], "pushed": False}

    repo_name = Path(sub_path).name
    if repo_name in SKIP_REPOS or sub_path in SKIP_REPOS:
        log(f"  SKIP (upstream fork): {sub_path}")
        return {"path": sub_path, "status": "skipped_upstream", "merges": [], "pushed": False}

    full_path = str(WORKSPACE / sub_path)
    if not (WORKSPACE / sub_path).exists():
        return {"path": sub_path, "status": "missing", "merges": [], "pushed": False}

    ok, _, _ = run(["git", "rev-parse", "--git-dir"], cwd=full_path)
    if not ok:
        return {"path": sub_path, "status": "not_git", "merges": [], "pushed": False}

    # Fetch
    run(["git", "fetch", "--all", "--prune"], cwd=full_path, timeout=180)

    default_branch = get_default_branch(full_path)

    ok, _, _ = run(["git", "checkout", default_branch], cwd=full_path)
    if not ok:
        run(["git", "checkout", "-b", default_branch, f"origin/{default_branch}"], cwd=full_path)

    run(["git", "pull", "origin", default_branch, "--no-edit"], cwd=full_path, timeout=120)

    ok, out, _ = run(["git", "branch", "-r"], cwd=full_path)
    if not ok:
        return {"path": sub_path, "status": "no_remote", "merges": [], "pushed": False}

    branches = []
    for line in out.split("\n"):
        line = line.strip()
        if not line or "HEAD" in line or "upstream/" in line.lower():
            continue
        if "origin/" in line:
            branch = line.replace("origin/", "").strip()
            if branch and branch != default_branch:
                branches.append(branch)

    if len(branches) > MAX_BRANCHES_PER_REPO:
        log(f"  SKIP (too many branches: {len(branches)}): {sub_path}")
        return {"path": sub_path, "status": "skipped_many_branches", "merges": [], "pushed": False}

    if not branches:
        return {"path": sub_path, "status": "clean", "merges": [], "pushed": False}

    merged_branches = []
    failed_branches = []
    safe_chars = set("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_./")

    for branch in branches:
        if not all(c in safe_chars for c in branch):
            failed_branches.append(branch)
            continue

        ok, out, _ = run(
            ["git", "log", f"{default_branch}..origin/{branch}", "--oneline"],
            cwd=full_path,
        )
        unique_commits = len([l for l in out.split("\n") if l.strip()]) if ok else 0
        if unique_commits == 0:
            continue

        log(f"  [{sub_path}] MERGE: {branch} ({unique_commits} unique commits)")

        ok, _, err = run(
            ["git", "merge", f"origin/{branch}", "--no-edit",
             "-m", f"merge: {branch} into {default_branch} (pass 4)"],
            cwd=full_path, timeout=120,
        )
        if ok:
            log("    [OK] Merged successfully")
            merged_branches.append(branch)
        else:
            run(["git", "merge", "--abort"], cwd=full_path)

            ok2, out2, _ = run(
                ["git", "log", f"{default_branch}..origin/{branch}", "--format=%H"],
                cwd=full_path,
            )
            if ok2 and out2:
                commits = [c.strip() for c in out2.split("\n") if c.strip()]
                cherry_picked = 0
                for commit in commits:
                    if not all(c in "0123456789abcdef" for c in commit):
                        continue
                    cp_ok, _, _ = run(["git", "cherry-pick", commit, "--no-edit"], cwd=full_path, timeout=30)
                    if cp_ok:
                        cherry_picked += 1
                    else:
                        run(["git", "cherry-pick", "--abort"], cwd=full_path)
                if cherry_picked > 0:
                    log(f"    [OK] Cherry-picked {cherry_picked}/{len(commits)} commits")
                    merged_branches.append(f"{branch} (cherry-pick)")
                else:
                    log("    [FAIL] Could not merge or cherry-pick")
                    failed_branches.append(branch)
            else:
                log("    [FAIL] Could not merge")
                failed_branches.append(branch)

    pushed = False
    if merged_branches:
        ok, _, err = run(["git", "push", "origin", default_branch], cwd=full_path, timeout=120)
        if ok:
            log(f"  [OK] Pushed {sub_path}")
            pushed = True
        else:
            log(f"  [FAIL] Push failed {sub_path}: {err[:200]}")

    for branch_info in merged_branches:
        branch = branch_info.replace(" (cherry-pick)", "").strip()
        if all(c in safe_chars for c in branch):
            run(["git", "push", "origin", "--delete", branch], cwd=full_path, timeout=30)

    return {
        "path": sub_path,
        "status": "processed",
        "default_branch": default_branch,
        "merges": merged_branches,
        "failed": failed_branches,
        "pushed": pushed,
    }


def main():
    try:
        with open(LOG_FILE, "w", encoding="utf-8") as f:
            f.write(f"=== RECONCILIATION PASS 4 — {datetime.now()} ===\n\n")
    except OSError:
        print("Warning: Could not write log file")

    log(f"Starting Reconciliation Pass 4 from {WORKSPACE}")

    state = load_state()
    already_done = len(state.get("completed", []))
    if already_done > 0:
        log(f"Resuming from previous run ({already_done} already completed)")

    submodules = get_submodules()
    log(f"Found {len(submodules)} submodules in .gitmodules")

    results = []
    total_merges = 0
    total_pushes = 0

    for i, sub in enumerate(submodules, 1):
        log(f"\n[{i}/{len(submodules)}] Processing: {sub}")
        result = process_submodule(sub, state)
        results.append(result)

        if result["merges"]:
            total_merges += len(result["merges"])
            if sub not in state["merged"]:
                state["merged"][sub] = []
            state["merged"][sub].extend(result["merges"])

        if result["pushed"]:
            total_pushes += 1

        if sub not in state.get("completed", []):
            state.setdefault("completed", []).append(sub)
            save_state(state)

    log(f"\n{'=' * 60}")
    log("RECONCILIATION PASS 4 SUMMARY")
    log(f"{'=' * 60}")
    log(f"Total submodules processed: {len(submodules)}")
    log(f"Total branches merged: {total_merges}")
    log(f"Total repos pushed: {total_pushes}")

    merged_repos = [r for r in results if r["merges"]]
    if merged_repos:
        log("\nRepos with merges:")
        for r in merged_repos:
            log(f"  {r['path']}: {', '.join(r['merges'])}")

    failed_repos = [r for r in results if r.get("failed")]
    if failed_repos:
        log("\nRepos with failed merges:")
        for r in failed_repos:
            log(f"  {r['path']}: {', '.join(r['failed'])}")

    skipped = [r for r in results if "skip" in r["status"]]
    log(f"\nSkipped repos: {len(skipped)}")
    log(f"\nLog saved to: {LOG_FILE}")

    print("\n=== MERGE RESULTS ===")
    print(f"Merges: {total_merges}")
    print(f"Pushes: {total_pushes}")
    print(f"Skipped: {len(skipped)}")

    return results


if __name__ == "__main__":
    results = main()
