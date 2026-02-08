#!/usr/bin/env python3
"""Process remaining submodules starting from rental.home."""

import subprocess, os, sys, json, re

WORKSPACE = r"C:\Users\hyper\workspace"
REMAINING = [
    "rental.home",
    "bobmani/bobmania",
    "bobmani/itgmania",
    "bobmani/beatoraja",
    "bobmani/hymnmania",
    "bobmani/ksm-v2",
    "bobmani/linthesia",
    "bobmani/pianogame",
    "Azure.Cybersecurity",
    "claude-mem",
    "metamcp",
    "mcp-superassistant",
    "mcpenetes",
    "bobmani/ffr-difficulty-model",
    "bobmani/leraine-studio",
    "bobmani/ddc",
    "bobmani/arrowvortex",
    "opencode-autopilot",
    "bobmani/ddc_onset",
    "bobmani/Simply-Love-SM5",
    "antigravity-jules-orchestration",
    "antigravity-autopilot",
    "bg",
    "MCP_SuperAssistant",
    "Alti.Assistant",
    "Alti.Code.Studio",
    "Merk.Mobile",
    "Stone.Ledger",
    "Tickerstone",
    "coin.project",
    "cointrade",
]

env = os.environ.copy()
env["GIT_TERMINAL_PROMPT"] = "0"


def run(cmd, cwd, timeout=300):
    try:
        print(f"Running: {cmd} in {cwd}")
        r = subprocess.run(
            cmd,
            cwd=cwd,
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
    rc, out, _ = run("git branch -r", path)
    if "origin/main" in (out or ""):
        return "main"
    return "master"


def get_feature_branches(path):
    rc, out, _ = run("git branch -r", path)
    if rc != 0 or not out:
        return []
    branches = []
    for line in out.splitlines():
        b = line.strip()
        if "->" in b or not b.startswith("origin/"):
            continue
        name = b.replace("origin/", "")
        if name in ("main", "master", "HEAD", "develop", "release"):
            continue
        branches.append(name)
    return branches


def is_robertpelloni(path):
    rc, out, _ = run("git remote get-url origin", path)
    return "robertpelloni" in (out or "").lower()


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


def process(subpath):
    full = os.path.join(WORKSPACE, subpath.replace("/", os.sep))
    if not os.path.isdir(full):
        print(f"  SKIP {subpath}: directory not found")
        return "skip"

    has_git = os.path.isdir(os.path.join(full, ".git")) or os.path.isfile(
        os.path.join(full, ".git")
    )
    if not has_git:
        print(f"  INIT {subpath}...")
        run(f'git submodule update --init "{subpath}"', WORKSPACE, timeout=180)
        has_git = os.path.isdir(os.path.join(full, ".git")) or os.path.isfile(
            os.path.join(full, ".git")
        )
        if not has_git:
            print(f"  SKIP {subpath}: could not initialize")
            return "skip"

    print(f"  FETCH {subpath}...")
    run("git fetch --all --prune", full, timeout=120)

    db = get_default_branch(full)
    rc, current, _ = run("git branch --show-current", full)

    if current != db:
        run("git stash", full)
        rc, _, err = run(f"git checkout {db}", full)
        if rc != 0:
            rc, _, _ = run(f"git checkout -b {db} origin/{db}", full)
            if rc != 0:
                print(f"  FAIL {subpath}: cannot checkout {db}")
                return "fail"

    print(f"  PULL {subpath} origin/{db}...")
    rc, _, _ = run(f"git pull origin {db} --no-edit", full, timeout=120)

    rp = is_robertpelloni(full)
    rc, url, _ = run("git remote get-url origin", full)

    # Sync upstream if fork
    if rp:
        upstream_url = check_upstream(full, url)
        if upstream_url:
            print(f"  Fork detected! Upstream: {upstream_url}")
            rc, _, _ = run("git remote get-url upstream", full)
            if rc != 0:
                run(f"git remote add upstream {upstream_url}", full)
            else:
                run(f"git remote set-url upstream {upstream_url}", full)

            print(f"  Fetching upstream...")
            rc, _, err = run("git fetch upstream", full, timeout=120)
            if rc == 0:
                # Try to merge upstream default branch
                upstream_branch = db
                # Check if upstream has this branch
                rc_check, out_check, _ = run(
                    f"git branch -r --list upstream/{db}", full
                )
                if rc_check != 0 or not out_check:
                    # Fallback swap
                    alt = "master" if db == "main" else "main"
                    rc_alt, out_alt, _ = run(
                        f"git branch -r --list upstream/{alt}", full
                    )
                    if rc_alt == 0 and out_alt:
                        upstream_branch = alt

                print(f"  Merging upstream/{upstream_branch}...")
                rc, out, err = run(
                    f'git merge upstream/{upstream_branch} --no-edit -m "chore: sync upstream changes"',
                    full,
                )
                if rc != 0:
                    if "CONFLICT" in (err + out):
                        print(f"  Upstream merge conflict, keeping ours...")
                        run("git checkout --ours .", full)
                        run("git add -A", full)
                        run(
                            'git commit --no-edit -m "chore: sync upstream (resolved conflicts keeping local)"',
                            full,
                        )
                    else:
                        run("git merge --abort", full)
                        print(f"  Upstream merge failed: {err}")

    # Merge feature branches for robertpelloni repos
    if rp:
        branches = get_feature_branches(full)
        for br in branches:
            print(f"  MERGE {subpath}: origin/{br} -> {db}")
            rc, out, err = run(
                f'git merge origin/{br} --no-edit -m "chore: merge {br} into {db}"',
                full,
            )
            if rc != 0:
                if "CONFLICT" in (out + err):
                    run("git checkout --theirs .", full)
                    run("git add -A", full)
                    run(
                        f'git commit --no-edit -m "chore: merge {br} (resolved conflicts)"',
                        full,
                    )
                    print(f"  MERGED {br} with conflict resolution")
                else:
                    run("git merge --abort", full)
                    print(f"  SKIP merge {br}: {err[:60]}")
            else:
                if "Already up to date" not in out:
                    print(f"  MERGED {br}")

    # Push
    print(f"  PUSH {subpath}...")
    rc, _, err = run(f"git push origin {db}", full, timeout=120)
    if (
        rc == 0
        or "up-to-date" in (err or "").lower()
        or "Everything up-to-date" in (err or "")
    ):
        print(f"  OK {subpath}")
        return "ok"
    else:
        print(f"  PUSH-FAIL {subpath}: {err[:80]}")
        return "push-fail"


results = {"ok": [], "fail": [], "skip": [], "push-fail": []}

for i, sub in enumerate(REMAINING):
    print(f"\n[{i + 1}/{len(REMAINING)}] {sub}")
    r = process(sub)
    results.get(r, results["fail"]).append(sub)

print(f"\n{'=' * 50}")
print(
    f"OK: {len(results['ok'])} | FAIL: {len(results['fail'])} | SKIP: {len(results['skip'])} | PUSH-FAIL: {len(results['push-fail'])}"
)
if results["fail"]:
    print(f"Failed: {', '.join(results['fail'])}")
if results["push-fail"]:
    print(f"Push Failed: {', '.join(results['push-fail'])}")
if results["skip"]:
    print(f"Skipped: {', '.join(results['skip'])}")
