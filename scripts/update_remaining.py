#!/usr/bin/env python3
"""Process remaining submodules that weren't covered in the first run."""

import subprocess, os, sys, json

WORKSPACE = r"C:\Users\hyper\workspace"
REMAINING = [
    "mcp-superassistant",
    "mcpenetes",
    "opencode-autopilot",
    "bg",
    "Alti.Assistant",
    "Alti.Code.Studio",
    "Merk.Mobile",
    "Stone.Ledger",
    "Tickerstone",
    "coin.project",
    "cointrade",
    "MCP_SuperAssistant",
    "antigravity-autopilot",
    "antigravity-jules-orchestration",
    "bobmani/ffr-difficulty-model",
    "bobmani/leraine-studio",
    "bobmani/ddc",
    "bobmani/arrowvortex",
    "bobmani/ddc_onset",
    "bobmani/Simply-Love-SM5",
]
# Nested submodules inside antigravity-autopilot
NESTED_AG = [
    "antigravity-autopilot/AUTO-ALL-AntiGravity",
    "antigravity-autopilot/yoke-antigravity",
    "antigravity-autopilot/auto-accept-agent",
    "antigravity-autopilot/antigravity-auto-accept",
]

env = os.environ.copy()
env["GIT_TERMINAL_PROMPT"] = "0"


def run(cmd, cwd, timeout=90):
    try:
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
    run("git fetch --all --prune", full, timeout=90)

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
    rc, _, _ = run(f"git pull origin {db} --no-edit", full, timeout=90)

    rp = is_robertpelloni(full)

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
    rc, _, err = run(f"git push origin {db}", full, timeout=90)
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


results = {"ok": [], "fail": [], "skip": []}
all_subs = REMAINING + NESTED_AG

for i, sub in enumerate(all_subs):
    print(f"\n[{i + 1}/{len(all_subs)}] {sub}")
    r = process(sub)
    results.get(r, results["fail"]).append(sub)

print(f"\n{'=' * 50}")
print(
    f"OK: {len(results['ok'])} | FAIL: {len(results['fail'])} | SKIP: {len(results['skip'])}"
)
if results["fail"]:
    print(f"Failed: {', '.join(results['fail'])}")
if results["skip"]:
    print(f"Skipped: {', '.join(results['skip'])}")
