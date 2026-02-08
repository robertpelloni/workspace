#!/usr/bin/env python3
"""Clean up remaining dirty submodules by committing changes and pushing."""

import subprocess, os

WORKSPACE = r"C:\Users\hyper\workspace"
env = os.environ.copy()
env["GIT_TERMINAL_PROMPT"] = "0"


def run(cmd, cwd, timeout=60):
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
    except:
        return -1, "", "error"


def clean_sub(path, msg="chore: auto-commit local changes"):
    full = os.path.join(WORKSPACE, path.replace("/", os.sep))
    if not os.path.isdir(full):
        print(f"  SKIP {path}: not found")
        return False

    # First recursively clean nested submodules
    rc, out, _ = run("git submodule status", full)
    if rc == 0 and out:
        for line in out.splitlines():
            parts = line.strip().split()
            if len(parts) >= 2:
                nested = parts[1]
                nested_full = os.path.join(full, nested.replace("/", os.sep))
                if os.path.isdir(nested_full):
                    # Try to update nested submodule
                    run("git submodule update --init --recursive", full, timeout=120)
                    break  # One update --init --recursive handles all

    # Check if there are changes
    rc, status, _ = run("git status --porcelain", full)
    if not status:
        print(f"  CLEAN {path}")
        return True

    # Add and commit
    run("git add -A", full)
    rc, _, err = run(f'git commit -m "{msg}"', full)
    if rc != 0:
        if "nothing to commit" in (err or ""):
            print(f"  CLEAN {path} (nothing to commit)")
            return True
        print(f"  COMMIT-FAIL {path}: {err[:60]}")
        return False

    # Get current branch
    rc, branch, _ = run("git branch --show-current", full)
    if not branch:
        branch = "main"

    # Push
    rc, _, err = run(f"git push origin {branch}", full, timeout=90)
    if rc == 0 or "up-to-date" in (err or "").lower():
        print(f"  PUSHED {path} ({branch})")
        return True
    else:
        print(f"  PUSH-FAIL {path}: {err[:80]}")
        return False


# Process submodules with direct file modifications first
print("=== Phase 1: Direct file modifications ===")
direct_mods = [
    ("Azure.Cybersecurity", "chore: commit CI and test updates"),
    ("antigravity-jules-orchestration", "chore: commit dashboard and readme updates"),
    ("bobmani/bobmania", "chore: commit dashboard updates"),
    ("bobmani/linthesia", "chore: update .gitmodules"),
    ("bobmani/beatoraja", "chore: update changelog, roadmap, version, gitmodules"),
]
for path, msg in direct_mods:
    print(f"\n[{path}]")
    clean_sub(path, msg)

# Process submodules with nested submodule dirt
print("\n=== Phase 2: Nested submodule cleanup ===")
# For these, we need to go into nested subs first
nested_parents = [
    # (parent, [(nested_path, commit_msg)])
    (
        "Alti.Assistant",
        [
            ("Alti.Assistant.Backend", "chore: auto-commit changes"),
            ("Alti.Assistant.Frontend", "chore: auto-commit changes"),
            ("external/CopilotKit", "chore: auto-commit changes"),
        ],
    ),
    (
        "Merk.Mobile",
        [
            ("Backend", "chore: auto-commit changes"),
            ("Frontend", "chore: auto-commit changes"),
            ("flutter", "chore: auto-commit changes"),
            ("website", "chore: auto-commit changes"),
        ],
    ),
    (
        "bg",
        [
            ("bobsgameonlinejava", "chore: auto-commit changes"),
            ("okgame", "chore: auto-commit changes"),
        ],
    ),
    (
        "bobfilez",
        [
            ("ai-file-sorter", "chore: auto-commit changes"),
        ],
    ),
    ("bobmani/itgmania", []),  # nested subs are external, just update
    (
        "bobsaver",
        [
            ("BeatDrop", "chore: auto-commit changes"),
        ],
    ),
]

for parent, nested_list in nested_parents:
    parent_full = os.path.join(WORKSPACE, parent.replace("/", os.sep))
    print(f"\n[{parent}]")

    if not os.path.isdir(parent_full):
        print(f"  SKIP: not found")
        continue

    # First try to update nested submodules
    print(f"  Updating nested submodules...")
    run("git submodule update --init --recursive", parent_full, timeout=180)

    # Clean each nested submodule
    for nested, msg in nested_list:
        nested_full = os.path.join(parent_full, nested.replace("/", os.sep))
        if os.path.isdir(nested_full):
            rc, status, _ = run("git status --porcelain", nested_full)
            if status:
                run("git add -A", nested_full)
                run(f'git commit -m "{msg}"', nested_full)
                # Get branch
                rc, branch, _ = run("git branch --show-current", nested_full)
                if branch:
                    run(f"git push origin {branch}", nested_full, timeout=60)
                    print(f"  Cleaned nested: {nested}")
                else:
                    print(f"  Nested {nested}: detached HEAD, skipping push")

    # Now commit+push the parent
    clean_sub(parent, "chore: sync nested submodules and local changes")

# Process build artifact submodules
print("\n=== Phase 3: Build artifacts ===")
build_subs = [
    ("Tickerstone", "chore: commit build artifacts"),
    ("bobtorrent", "chore: commit gradle artifacts"),
]
for path, msg in build_subs:
    print(f"\n[{path}]")
    clean_sub(path, msg)

# Clean remaining
print("\n=== Phase 4: Remaining ===")
remaining = [
    "borg",
    "coin.project",
    "cointrade",
    "rental.home",
    "antigravity-autopilot",
]
for path in remaining:
    print(f"\n[{path}]")
    clean_sub(path, "chore: sync changes")

print("\n=== DONE ===")
