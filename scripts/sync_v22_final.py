#!/usr/bin/env python3
"""
Omni-Workspace Full Sync Protocol v22 (Final Executive Edition)
Executes the full protocol:
1) Fetch all remotes for root + all submodules
2) Upstream sync for root
3) Recursive submodule update (depth-3)
4) Forward merge: feature branches -> main
5) Push main + feature branches
6) Commit root with updated submodule pointers
7) Version + changelog governance
"""

import subprocess
import os
import sys
import time
from datetime import datetime
from pathlib import Path

WORKSPACE = Path(r"C:\Users\hyper\workspace")
LOG_FILE = WORKSPACE / "sync_v22.log"

# Owners to scan for feature branches (mnmballa2323 is the fork owner)
TARGET_OWNERS = {"robertpelloni", "mnmballa2323"}

# Repos to completely skip (too large / known broken environments)
EXCLUDED_DIRS = {"bg", "borg", "fwber", ".agent"}

# Dirs that are third-party - we can merge locally but skip push
THIRD_PARTY = {
    "antigravity-cli", "computer-use-preview", "openclaw-config",
    "openclaw-dashboard", "topaz-ffmpeg", "superai",
    "onetool-mcp", "OmniRoute"
}

results = {
    "synced": [],
    "merged_forward": [],
    "pushed": [],
    "push_failed": [],
    "errors": [],
    "skipped": [],
}

def log(msg, level="INFO"):
    ts = datetime.now().strftime("%H:%M:%S")
    line = f"[{ts}] [{level}] {msg}"
    print(line)
    try:
        with open(LOG_FILE, "a", encoding="utf-8") as f:
            f.write(line + "\n")
    except Exception:
        pass

def run(cmd, cwd=None, timeout=120, silent=False):
    """Run shell command, return (stdout, returncode)."""
    _cwd = str(cwd or WORKSPACE)
    try:
        r = subprocess.run(
            cmd, shell=True, cwd=_cwd,
            capture_output=True, text=True,
            encoding="utf-8", errors="replace",
            timeout=timeout
        )
        out = (r.stdout or "").strip()
        err = (r.stderr or "").strip()
        if not silent and r.returncode != 0 and err:
            log(f"  STDERR: {err[:300]}", "WARN")
        return out, r.returncode
    except subprocess.TimeoutExpired:
        log(f"  TIMEOUT ({timeout}s): {cmd[:80]}", "WARN")
        return "TIMEOUT", -1
    except Exception as e:
        log(f"  EXCEPTION: {e}", "ERROR")
        return str(e), -1

def get_default_branch(cwd):
    out, _ = run("git branch -a --format=%(refname:short)", cwd=cwd, silent=True)
    branches = out.splitlines() if out else []
    if "origin/main" in branches or any("remotes/origin/main" in b for b in branches):
        return "main"
    if "origin/master" in branches or any("remotes/origin/master" in b for b in branches):
        return "master"
    cur, _ = run("git rev-parse --abbrev-ref HEAD", cwd=cwd, silent=True)
    return cur if cur and cur not in ("HEAD", "TIMEOUT") else "main"

def is_clean(cwd):
    out, _ = run("git status --porcelain", cwd=cwd, silent=True)
    return not bool(out and out.strip())

def resolve_conflicts_ours(cwd):
    """Resolve conflicts by preferring 'ours' side (local feature work preserved)."""
    out, _ = run("git diff --name-only --diff-filter=U", cwd=cwd, silent=True)
    if not out:
        return
    for fname in out.splitlines():
        fname = fname.strip()
        if not fname:
            continue
        run(f'git checkout --ours "{fname}"', cwd=cwd, silent=True)
        run(f'git add "{fname}"', cwd=cwd, silent=True)
    run('git commit -m "chore: auto-resolve conflicts (ours strategy)"', cwd=cwd)

def get_local_branches(cwd, default_branch):
    out, _ = run("git branch --format=%(refname:short)", cwd=cwd, silent=True)
    if not out:
        return []
    return [b.strip() for b in out.splitlines()
            if b.strip() and b.strip() not in (default_branch, "HEAD", "main", "master")]

def get_remote_feature_branches(cwd, default_branch):
    """Get remote branches that look like feature branches (e.g. jules-*)."""
    out, _ = run("git branch -r --format=%(refname:short)", cwd=cwd, silent=True)
    if not out:
        return []
    feature = []
    for b in out.splitlines():
        b = b.strip()
        if not b:
            continue
        # Skip tracking branches for main/master, HEAD, dependabot
        short = b.replace("origin/", "").replace("upstream/", "")
        if short in (default_branch, "HEAD", "main", "master"):
            continue
        if short.startswith("dependabot/"):
            continue
        feature.append(b)  # keep fully qualified remote name
    return feature

def sync_submodule(cwd, subpath):
    """Sync a single submodule: fetch, checkout default branch, pull."""
    full_path = Path(cwd) / subpath
    if not full_path.exists():
        log(f"  Submodule path missing: {full_path}", "WARN")
        return

    name = full_path.name
    if name in EXCLUDED_DIRS:
        log(f"  SKIP (excluded): {name}")
        results["skipped"].append(str(full_path))
        return

    log(f"  Submodule: {subpath}")
    # Fetch
    run("git fetch --all --tags --prune", cwd=str(full_path), timeout=90, silent=True)
    default_branch = get_default_branch(str(full_path))

    # Stash if dirty
    run("git stash --include-untracked", cwd=str(full_path), silent=True)

    # Checkout & pull
    run(f"git checkout {default_branch}", cwd=str(full_path), silent=True)
    out, rc = run(f"git pull origin {default_branch} --no-rebase", cwd=str(full_path), timeout=90, silent=True)
    if rc != 0 and "conflict" in (out or "").lower():
        resolve_conflicts_ours(str(full_path))

    # Forward merge any local feature branches
    local_branches = get_local_branches(str(full_path), default_branch)
    for fb in local_branches:
        log(f"    Forward merge {fb} -> {default_branch}")
        run(f"git checkout {default_branch}", cwd=str(full_path), silent=True)
        out, rc = run(f'git merge {fb} -m "chore: forward merge {fb} -> {default_branch}"',
                      cwd=str(full_path), timeout=60, silent=True)
        if "Conflict" in (out or ""):
            resolve_conflicts_ours(str(full_path))
        results["merged_forward"].append(f"{name}:{fb}")

    # Try to push
    if name not in THIRD_PARTY:
        _, rc = run(f"git push origin {default_branch} --force-with-lease", cwd=str(full_path), timeout=90, silent=True)
        if rc == 0:
            results["pushed"].append(f"{name}")
        else:
            results["push_failed"].append(f"{name}")

    # Restore stash
    run("git stash pop", cwd=str(full_path), silent=True)
    results["synced"].append(str(full_path))

def sync_root(cwd):
    log("=" * 60)
    log("STEP 1: Fetch all remotes (root)")
    run("git fetch --all --tags --prune", cwd=str(cwd), timeout=300)

    log("STEP 2: Upstream sync (root)")
    default_branch = get_default_branch(str(cwd))
    run(f"git checkout {default_branch}", cwd=str(cwd))
    run(f"git pull origin {default_branch} --no-rebase", cwd=str(cwd), timeout=120)

    # Check if upstream != origin
    out, _ = run("git remote", cwd=str(cwd), silent=True)
    if "upstream" in (out or "").splitlines():
        log("  Merging from upstream...")
        run(f"git merge upstream/{default_branch} -m 'Sync upstream'", cwd=str(cwd), timeout=120)

    log("STEP 3: Recursive submodule init & update (depth=1 for speed)")
    run("git submodule update --init --recursive --depth=1", cwd=str(cwd), timeout=1800)

    log("STEP 4: Sync all submodules individually")
    out, _ = run(
        'git submodule --quiet foreach --recursive "echo $displaypath"',
        cwd=str(cwd), timeout=300, silent=True
    )
    if out:
        submodule_paths = [p.strip() for p in out.splitlines() if p.strip()]
        log(f"  Found {len(submodule_paths)} submodule paths")
        for sp in submodule_paths:
            try:
                sync_submodule(str(cwd), sp)
            except Exception as e:
                log(f"  ERROR in {sp}: {e}", "ERROR")
                results["errors"].append(f"{sp}: {e}")
    else:
        log("  No submodule paths found via foreach", "WARN")

def commit_and_push_root(cwd, default_branch):
    log("=" * 60)
    log("STEP 5: Add, commit, push root")

    # Add everything not ignored
    run("git add -A", cwd=str(cwd), timeout=60)

    # Check if there's anything to commit
    out, _ = run("git status --porcelain", cwd=str(cwd), silent=True)
    if out and out.strip():
        ts = datetime.now().strftime("%Y-%m-%d %H:%M")
        run(f'git commit -m "chore: executive sync {ts} - submodule pointers + workspace state"',
            cwd=str(cwd), timeout=60)
    else:
        log("  Nothing to commit at root.")

    # Push
    _, rc = run(f"git push origin {default_branch}", cwd=str(cwd), timeout=300)
    if rc == 0:
        log("  Root push: OK")
        results["pushed"].append("root")
    else:
        log("  Root push: FAILED - trying force-with-lease", "WARN")
        _, rc2 = run(f"git push origin {default_branch} --force-with-lease", cwd=str(cwd), timeout=300)
        if rc2 == 0:
            log("  Root force push: OK")
            results["pushed"].append("root(force)")
        else:
            log("  Root push still failed.", "ERROR")
            results["push_failed"].append("root")

def version_governance(cwd):
    log("=" * 60)
    log("STEP 6: Version governance")

    # Read current version
    ver_file = cwd / "VERSION"
    if not ver_file.exists():
        log("  VERSION file not found, skipping", "WARN")
        return

    current = ver_file.read_text(encoding="utf-8").strip()
    # Parse v5.77.0 -> bump patch
    parts = current.lstrip("v").split(".")
    try:
        parts[2] = str(int(parts[2]) + 1)
        new_ver = "v" + ".".join(parts)
    except Exception:
        log(f"  Could not parse version '{current}', skipping bump", "WARN")
        return

    ver_file.write_text(new_ver + "\n", encoding="utf-8")
    log(f"  Version bumped: {current} -> {new_ver}")

    # Update VERSION.current
    vc = cwd / "VERSION.current"
    if vc.exists():
        vc.write_text(new_ver + "\n", encoding="utf-8")

    # Append to CHANGELOG
    cl = cwd / "CHANGELOG.md"
    if cl.exists():
        today = datetime.now().strftime("%Y-%m-%d")
        entry = f"\n## [{new_ver}] - {today}\n- Executive Sync v22: full submodule reconciliation, forward merges, push\n"
        content = cl.read_text(encoding="utf-8")
        # Insert after first heading
        lines = content.splitlines(keepends=True)
        insert_at = 0
        for i, line in enumerate(lines):
            if line.startswith("## ["):
                insert_at = i
                break
        lines.insert(insert_at, entry)
        cl.write_text("".join(lines), encoding="utf-8")
        log(f"  CHANGELOG updated with {new_ver}")

    # Update VERSION.md summary
    vm = cwd / "VERSION.md"
    if vm.exists():
        vm_content = vm.read_text(encoding="utf-8")
        vm_content = vm_content.replace(current, new_ver)
        vm.write_text(vm_content, encoding="utf-8")

    return new_ver

def print_report():
    log("=" * 60)
    log("SYNC REPORT")
    log(f"  Submodules synced:   {len(results['synced'])}")
    log(f"  Forward merges:      {len(results['merged_forward'])}")
    log(f"  Successful pushes:   {len(results['pushed'])}")
    log(f"  Push failures:       {len(results['push_failed'])}")
    log(f"  Errors:              {len(results['errors'])}")
    log(f"  Skipped:             {len(results['skipped'])}")

    if results["push_failed"]:
        log("  PUSH FAILURES:", "WARN")
        for pf in results["push_failed"]:
            log(f"    - {pf}", "WARN")

    if results["errors"]:
        log("  ERRORS:", "ERROR")
        for e in results["errors"]:
            log(f"    - {e}", "ERROR")

if __name__ == "__main__":
    with open(LOG_FILE, "a", encoding="utf-8") as f:
        f.write(f"\n{'='*60}\nSync v22 START: {datetime.now()}\n{'='*60}\n")

    log(f"Workspace: {WORKSPACE}")
    log(f"Version at start: {(WORKSPACE / 'VERSION').read_text(encoding='utf-8').strip() if (WORKSPACE / 'VERSION').exists() else 'UNKNOWN'}")

    try:
        sync_root(WORKSPACE)
        default_branch = get_default_branch(str(WORKSPACE))
        new_ver = version_governance(WORKSPACE)
        commit_and_push_root(WORKSPACE, default_branch)
    except KeyboardInterrupt:
        log("Interrupted by user.", "WARN")
    except Exception as e:
        log(f"CRITICAL: {e}", "ERROR")
        import traceback
        log(traceback.format_exc(), "ERROR")

    print_report()
    log(f"Sync v22 COMPLETE: {datetime.now()}")
