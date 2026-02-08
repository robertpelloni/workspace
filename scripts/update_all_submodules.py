#!/usr/bin/env python3
"""
Comprehensive Submodule Update Script v2
- Updates all submodules recursively
- Merges feature branches into default branch for robertpelloni repos
- Syncs upstream forks
- Pushes all changes
"""

import subprocess
import os
import sys
import json
import re
from datetime import datetime

WORKSPACE = r"C:\Users\hyper\workspace"
LOG_FILE = os.path.join(WORKSPACE, "logs", "submodule_update.log")
RESULTS = {
    "success": [],
    "failed": [],
    "skipped": [],
    "merged_branches": [],
    "upstream_synced": [],
}

os.makedirs(os.path.join(WORKSPACE, "logs"), exist_ok=True)


def log(msg, level="INFO"):
    ts = datetime.now().strftime("%H:%M:%S")
    line = f"[{ts}] [{level}] {msg}"
    print(line, flush=True)
    with open(LOG_FILE, "a", encoding="utf-8") as f:
        f.write(line + "\n")


def run(cmd, cwd=None, timeout=120):
    """Run a command, return (returncode, stdout, stderr)"""
    env = os.environ.copy()
    env["GIT_TERMINAL_PROMPT"] = "0"
    try:
        r = subprocess.run(
            cmd,
            cwd=cwd or WORKSPACE,
            capture_output=True,
            text=True,
            timeout=timeout,
            env=env,
            shell=True,
        )
        return r.returncode, r.stdout.strip(), r.stderr.strip()
    except subprocess.TimeoutExpired:
        return -1, "", "TIMEOUT"
    except Exception as e:
        return -1, "", str(e)


def get_default_branch(path):
    """Determine default branch (main or master)"""
    rc, out, _ = run("git branch -r --list origin/main", cwd=path)
    if rc == 0 and "origin/main" in out:
        return "main"
    rc, out, _ = run("git branch -r --list origin/master", cwd=path)
    if rc == 0 and "origin/master" in out:
        return "master"
    # Check local branches
    rc, out, _ = run("git branch --list main", cwd=path)
    if rc == 0 and "main" in out:
        return "main"
    return "master"


def get_remote_url(path):
    """Get origin remote URL"""
    rc, out, _ = run("git remote get-url origin", cwd=path)
    return out if rc == 0 else ""


def is_robertpelloni(url):
    return "robertpelloni" in url.lower()


def is_mnmballa(url):
    return "mnmballa" in url.lower()


def get_feature_branches(path):
    """Get remote feature branches (not main/master/HEAD)"""
    rc, out, _ = run("git branch -r --list 'origin/*'", cwd=path)
    if rc != 0 or not out:
        return []
    branches = []
    for line in out.splitlines():
        b = line.strip()
        if "->" in b:
            continue
        name = b.replace("origin/", "")
        if name in ("main", "master", "HEAD", "develop", "release"):
            continue
        # Skip branches that look like upstream (not Jules/AI)
        branches.append(name)
    return branches


def check_upstream(path, url):
    """Check if repo is a fork and get upstream URL using gh CLI"""
    # Extract owner/repo from URL
    match = re.search(r"github\.com[:/]([^/]+/[^/.]+)", url)
    if not match:
        return None
    repo_slug = match.group(1).rstrip(".git")
    rc, out, _ = run(
        f'gh repo view {repo_slug} --json parent -q ".parent.owner.login + \\"/\\" + .parent.name"',
        cwd=path,
        timeout=30,
    )
    if rc == 0 and out and "/" in out and out != "/":
        return f"https://github.com/{out}.git"
    return None


def process_submodule(path, full_path):
    """Process a single submodule"""
    log(f"Processing: {path}")

    if not os.path.isdir(os.path.join(full_path, ".git")) and not os.path.isfile(
        os.path.join(full_path, ".git")
    ):
        log(f"  Not initialized, attempting init...", "WARN")
        rc, _, err = run(
            f'git submodule update --init "{path}"', cwd=WORKSPACE, timeout=180
        )
        if rc != 0:
            log(f"  Failed to init: {err}", "ERROR")
            RESULTS["skipped"].append(f"{path} (not initialized)")
            return

    url = get_remote_url(full_path)
    if not url:
        log(f"  No remote URL found", "WARN")
        RESULTS["skipped"].append(f"{path} (no remote)")
        return

    is_rp = is_robertpelloni(url)

    # Step 1: Fetch all remotes
    log(f"  Fetching all remotes...")
    rc, _, err = run("git fetch --all --prune", cwd=full_path, timeout=120)
    if rc != 0:
        log(f"  Fetch failed: {err}", "WARN")

    # Step 2: Determine and checkout default branch
    default_branch = get_default_branch(full_path)
    log(f"  Default branch: {default_branch}")

    # Check current state
    rc, current, _ = run("git branch --show-current", cwd=full_path)
    rc2, status, _ = run("git status --porcelain", cwd=full_path)

    if current != default_branch:
        # Stash any changes first
        if status:
            log(f"  Stashing local changes...")
            run("git stash", cwd=full_path)

        log(f"  Checking out {default_branch}...")
        rc, _, err = run(f"git checkout {default_branch}", cwd=full_path)
        if rc != 0:
            # Try creating tracking branch
            rc, _, err = run(
                f"git checkout -b {default_branch} origin/{default_branch}",
                cwd=full_path,
            )
            if rc != 0:
                log(f"  Cannot checkout {default_branch}: {err}", "ERROR")
                RESULTS["failed"].append(f"{path} (checkout failed)")
                return

    # Step 3: Pull latest from origin
    log(f"  Pulling latest from origin/{default_branch}...")
    rc, _, err = run(
        f"git pull origin {default_branch} --no-edit", cwd=full_path, timeout=120
    )
    if rc != 0:
        log(f"  Pull failed: {err}", "WARN")
        # Try to abort merge if in progress
        run("git merge --abort", cwd=full_path)

    # Step 4: For robertpelloni repos, merge feature branches
    if is_rp:
        branches = get_feature_branches(full_path)
        if branches:
            log(
                f"  Found {len(branches)} feature branch(es): {', '.join(branches[:10])}"
            )
            for branch in branches:
                log(f"  Merging origin/{branch} into {default_branch}...")
                rc, out, err = run(
                    f'git merge origin/{branch} --no-edit -m "chore: merge feature branch {branch} into {default_branch}"',
                    cwd=full_path,
                )
                if rc != 0:
                    if (
                        "CONFLICT" in err
                        or "conflict" in err.lower()
                        or "CONFLICT" in out
                    ):
                        log(
                            f"  Conflict merging {branch}, attempting auto-resolve...",
                            "WARN",
                        )
                        # Accept both sides - prefer keeping all changes
                        run("git checkout --theirs .", cwd=full_path)
                        run("git add -A", cwd=full_path)
                        rc2, _, _ = run(
                            f'git commit --no-edit -m "chore: merge {branch} with conflict resolution (kept theirs)"',
                            cwd=full_path,
                        )
                        if rc2 == 0:
                            RESULTS["merged_branches"].append(
                                f"{path}:{branch} (with conflict resolution)"
                            )
                            log(f"  Merged {branch} with conflict resolution")
                        else:
                            run("git merge --abort", cwd=full_path)
                            log(f"  Failed to resolve conflicts for {branch}", "ERROR")
                    else:
                        run("git merge --abort", cwd=full_path)
                        log(f"  Merge failed for {branch}: {err}", "WARN")
                else:
                    RESULTS["merged_branches"].append(f"{path}:{branch}")
                    log(f"  Merged {branch} successfully")

    # Step 5: Sync upstream for forks
    if is_rp:
        upstream_url = check_upstream(full_path, url)
        if upstream_url:
            log(f"  Fork detected! Upstream: {upstream_url}")
            # Add upstream remote if not exists
            rc, _, _ = run("git remote get-url upstream", cwd=full_path)
            if rc != 0:
                run(f"git remote add upstream {upstream_url}", cwd=full_path)
            else:
                run(f"git remote set-url upstream {upstream_url}", cwd=full_path)

            log(f"  Fetching upstream...")
            rc, _, err = run("git fetch upstream", cwd=full_path, timeout=120)
            if rc == 0:
                # Determine upstream default branch
                upstream_branch = default_branch
                rc_check, out_check, _ = run(
                    f"git branch -r --list upstream/{default_branch}", cwd=full_path
                )
                if (
                    rc_check != 0
                    or not out_check
                    or f"upstream/{default_branch}" not in out_check
                ):
                    # Try the other branch
                    alt = "master" if default_branch == "main" else "main"
                    rc_alt, out_alt, _ = run(
                        f"git branch -r --list upstream/{alt}", cwd=full_path
                    )
                    if rc_alt == 0 and out_alt and f"upstream/{alt}" in out_alt:
                        upstream_branch = alt

                log(f"  Merging upstream/{upstream_branch}...")
                rc, out, err = run(
                    f'git merge upstream/{upstream_branch} --no-edit -m "chore: sync upstream changes"',
                    cwd=full_path,
                )
                if rc != 0:
                    if "CONFLICT" in (err + out):
                        log(
                            f"  Upstream merge conflict, keeping ours (local features)...",
                            "WARN",
                        )
                        run("git checkout --ours .", cwd=full_path)
                        run("git add -A", cwd=full_path)
                        rc2, _, _ = run(
                            'git commit --no-edit -m "chore: sync upstream (resolved conflicts keeping local)"',
                            cwd=full_path,
                        )
                        if rc2 == 0:
                            RESULTS["upstream_synced"].append(
                                f"{path} (with conflict resolution)"
                            )
                        else:
                            run("git merge --abort", cwd=full_path)
                            log(f"  Failed to resolve upstream conflicts", "ERROR")
                    elif "Already up to date" in (out + err):
                        log(f"  Already up to date with upstream")
                    else:
                        run("git merge --abort", cwd=full_path)
                        log(f"  Upstream merge failed: {err}", "WARN")
                else:
                    if "Already up to date" not in out:
                        RESULTS["upstream_synced"].append(path)
                        log(f"  Upstream synced successfully")
                    else:
                        log(f"  Already up to date with upstream")
            else:
                log(f"  Failed to fetch upstream: {err}", "WARN")

    # Step 6: Push changes
    log(f"  Pushing to origin/{default_branch}...")
    rc, _, err = run(f"git push origin {default_branch}", cwd=full_path, timeout=120)
    if rc == 0:
        RESULTS["success"].append(path)
        log(f"  Push successful")
    else:
        if "Everything up-to-date" in err or "up to date" in err.lower():
            RESULTS["success"].append(path)
            log(f"  Already up to date")
        else:
            log(f"  Push failed: {err}", "WARN")
            RESULTS["failed"].append(f"{path} (push failed: {err[:80]})")

    # Step 7: Update nested submodules
    rc, out, _ = run("git submodule status", cwd=full_path)
    if rc == 0 and out:
        nested_count = len([l for l in out.splitlines() if l.strip()])
        if nested_count > 0:
            log(f"  Updating {nested_count} nested submodule(s)...")
            run("git submodule update --init --recursive", cwd=full_path, timeout=300)


def main():
    log("=" * 60)
    log("COMPREHENSIVE SUBMODULE UPDATE - START")
    log(f"Workspace: {WORKSPACE}")
    log("=" * 60)

    # Parse .gitmodules
    gitmodules_path = os.path.join(WORKSPACE, ".gitmodules")
    submodules = []
    current = {}
    with open(gitmodules_path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if line.startswith("[submodule"):
                if current:
                    submodules.append(current)
                current = {}
            elif "=" in line:
                key, val = line.split("=", 1)
                current[key.strip()] = val.strip()
        if current:
            submodules.append(current)

    log(f"Found {len(submodules)} submodules in .gitmodules")

    # Process each submodule
    for i, sub in enumerate(submodules):
        path = sub.get("path", "")
        if not path:
            continue
        full_path = os.path.join(WORKSPACE, path.replace("/", os.sep))
        log(f"\n--- [{i + 1}/{len(submodules)}] {path} ---")
        try:
            process_submodule(path, full_path)
        except Exception as e:
            log(f"  Exception: {e}", "ERROR")
            RESULTS["failed"].append(f"{path} (exception: {str(e)[:80]})")

    # Print summary
    log("\n" + "=" * 60)
    log("SUMMARY")
    log("=" * 60)
    log(f"Success: {len(RESULTS['success'])}")
    log(f"Failed: {len(RESULTS['failed'])}")
    log(f"Skipped: {len(RESULTS['skipped'])}")
    log(f"Feature branches merged: {len(RESULTS['merged_branches'])}")
    log(f"Upstream synced: {len(RESULTS['upstream_synced'])}")

    if RESULTS["merged_branches"]:
        log("\nMerged branches:")
        for b in RESULTS["merged_branches"]:
            log(f"  - {b}")

    if RESULTS["upstream_synced"]:
        log("\nUpstream synced:")
        for s in RESULTS["upstream_synced"]:
            log(f"  - {s}")

    if RESULTS["failed"]:
        log("\nFailed:")
        for f in RESULTS["failed"]:
            log(f"  - {f}")

    if RESULTS["skipped"]:
        log("\nSkipped:")
        for s in RESULTS["skipped"]:
            log(f"  - {s}")

    # Write JSON results
    results_path = os.path.join(WORKSPACE, "logs", "submodule_update_results.json")
    with open(results_path, "w", encoding="utf-8") as f:
        json.dump(RESULTS, f, indent=2)
    log(f"\nResults saved to {results_path}")


if __name__ == "__main__":
    main()
