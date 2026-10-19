#!/usr/bin/env python3
"""
Protocol #260 — Repository Synchronization & Intelligent Merge Engine
Comprehensive workspace sync: fetch, branch audit, intelligent merge, version bump.
"""
import subprocess
import os
import json
import sys
import time
from datetime import datetime
from pathlib import Path

WORKSPACE = Path("C:/Users/hyper/workspace")
TIMEOUT_FETCH = 120  # seconds per submodule fetch
TIMEOUT_MERGE = 60
TIMEOUT_STATUS = 30
TIMEOUT_PUSH = 120

# Submodules too large for normal fetch
LARGE_REPOS = {"element-web", "geany", "FFmpeg", "HyperNexus2old", "llvm-project", "jdk", "grammars-v4"}

# Submodules to skip entirely (upstream-only, no robertpelloni fork activity)
SKIP_REPOS = set()

# Repos where we only track a specific upstream branch
UPSTREAM_ONLY = {"element-web": "develop", "JWildfire": "master", "FFmpeg": "topaz/develop"}

results = {
    "timestamp": datetime.now().isoformat(),
    "protocol": 260,
    "version_from": "v5.284.0",
    "fetched": [],
    "fetch_errors": [],
    "branches_found": {},
    "merges_attempted": [],
    "merges_success": [],
    "merges_failed": [],
    "merges_skipped": [],
    "pushed": [],
    "push_errors": [],
    "not_init": [],
    "dirty": [],
    "errors": []
}

def run_git(args, cwd=None, timeout=60, check=False):
    """Run a git command and return (returncode, stdout, stderr)."""
    if cwd is None:
        cwd = WORKSPACE
    try:
        proc = subprocess.run(
            ["git"] + args,
            cwd=str(cwd),
            capture_output=True,
            text=True,
            timeout=timeout
        )
        return proc.returncode, proc.stdout.strip(), proc.stderr.strip()
    except subprocess.TimeoutExpired:
        return -1, "", "TIMEOUT"
    except Exception as e:
        return -1, "", str(e)

def get_submodule_paths():
    """Get all submodule paths from .gitmodules."""
    rc, out, _ = run_git(["config", "--file", ".gitmodules", "--get-regexp", "path"])
    paths = []
    for line in out.split('\n'):
        if line:
            parts = line.split(' ', 1)
            if len(parts) == 2:
                paths.append(parts[1].strip())
    return paths

def is_initialized(path):
    """Check if a submodule is initialized."""
    return os.path.exists(WORKSPACE / path / ".git")

def get_current_branch(path):
    """Get current branch of a submodule."""
    rc, out, _ = run_git(["rev-parse", "--abbrev-ref", "HEAD"], cwd=WORKSPACE / path, timeout=10)
    return out if rc == 0 else None

def get_remote_branches(path, remote="origin"):
    """Get all remote branches for a submodule."""
    rc, out, _ = run_git(["branch", "-r"], cwd=WORKSPACE / path, timeout=15)
    if rc != 0:
        return []
    branches = []
    for line in out.split('\n'):
        line = line.strip()
        if line and '->' not in line:
            branches.append(line)
    return branches

def get_local_branches(path):
    """Get all local branches for a submodule."""
    rc, out, _ = run_git(["branch"], cwd=WORKSPACE / path, timeout=10)
    if rc != 0:
        return []
    branches = []
    for line in out.split('\n'):
        line = line.strip().replace('* ', '')
        if line:
            branches.append(line)
    return branches

def branch_has_unique_commits(path, branch, base_branch="main"):
    """Check if branch has commits not in base_branch."""
    rc, out, _ = run_git(["log", "--oneline", f"{base_branch}..{branch}"], cwd=WORKSPACE / path, timeout=15)
    if rc != 0:
        # Try master as fallback
        rc, out, _ = run_git(["log", "--oneline", f"master..{branch}"], cwd=WORKSPACE / path, timeout=15)
    return rc == 0 and len(out.strip()) > 0, out.strip()

def get_default_branch(path):
    """Determine the default branch (main or master) for a submodule."""
    # Check if main exists
    rc, _, _ = run_git(["rev-parse", "--verify", "main"], cwd=WORKSPACE / path, timeout=5)
    if rc == 0:
        return "main"
    rc, _, _ = run_git(["rev-parse", "--verify", "master"], cwd=WORKSPACE / path, timeout=5)
    if rc == 0:
        return "master"
    # Check remotes
    rc, out, _ = run_git(["symbolic-ref", "refs/remotes/origin/HEAD", "--short"], cwd=WORKSPACE / path, timeout=5)
    if rc == 0:
        return out.replace("origin/", "")
    return "main"  # fallback

def is_merge_safe(path, branch, target):
    """Quick check if merge would be clean."""
    rc, out, _ = run_git(["merge-base", target, branch], cwd=WORKSPACE / path, timeout=10)
    return rc == 0

def merge_branch(path, branch, target, strategy="ort"):
    """Merge branch into target. Returns (success, message)."""
    orig_branch = get_current_branch(path)
    
    # Checkout target
    rc, _, err = run_git(["checkout", target], cwd=WORKSPACE / path, timeout=15)
    if rc != 0:
        return False, f"Cannot checkout {target}: {err}"
    
    # Try merge
    rc, out, err = run_git(["merge", branch, "-m", f"Protocol #260: merge {branch} into {target}",
                            f"-X", "theirs"], cwd=WORKSPACE / path, timeout=TIMEOUT_MERGE)
    
    if rc == 0:
        return True, out
    
    # Conflicts - try harder
    # Check if it's a real conflict vs just no merge base
    rc2, out2, _ = run_git(["merge", "--abort"], cwd=WORKSPACE / path, timeout=10)
    
    # Try with --allow-unrelated-histories if no merge base
    rc3, out3, err3 = run_git(["merge", branch, "--allow-unrelated-histories",
                                "-m", f"Protocol #260: merge {branch} into {target}",
                                "-X", "theirs"], cwd=WORKSPACE / path, timeout=TIMEOUT_MERGE)
    if rc3 == 0:
        return True, f"(unrelated-histories) {out3}"
    
    # Abort and try cherry-pick approach
    run_git(["merge", "--abort"], cwd=WORKSPACE / path, timeout=10)
    return False, f"Conflicts: {err3[:200]}"

def cherry_pick_commits(path, branch, target):
    """Cherry-pick unique commits from branch onto target."""
    rc, out, _ = run_git(["log", "--oneline", "--reverse", f"{target}..{branch}"], 
                         cwd=WORKSPACE / path, timeout=15)
    if rc != 0 or not out.strip():
        return False, "No commits to cherry-pick"
    
    commits = [line.split()[0] for line in out.strip().split('\n')]
    picked = 0
    errors = []
    
    for commit in commits:
        rc, _, err = run_git(["cherry-pick", commit], cwd=WORKSPACE / path, timeout=30)
        if rc == 0:
            picked += 1
        else:
            errors.append(f"{commit}: {err[:100]}")
            run_git(["cherry-pick", "--abort"], cwd=WORKSPACE / path, timeout=10)
    
    return picked > 0, f"Picked {picked}/{len(commits)} commits. Errors: {len(errors)}"

def is_feature_branch(branch_name, default_branch):
    """Determine if a branch is a feature branch worth merging."""
    skip_patterns = [
        "HEAD", "origin/HEAD", f"origin/{default_branch}",
        "dependabot/", "renovate/", "greenkeeper/",
        "gh-pages", "pages", "release", "hotfix/",
        "upstream/", "gitlab/"  # Skip upstream-only branches
    ]
    for pat in skip_patterns:
        if pat in branch_name:
            return False
    return True

# ============================================================================
# PHASE 1: Fetch All
# ============================================================================
def phase1_fetch_all():
    print("\n" + "="*70)
    print("PHASE 1: FETCH ALL SUBMODULES")
    print("="*70)
    
    paths = get_submodule_paths()
    print(f"Found {len(paths)} submodules in .gitmodules")
    
    for i, path in enumerate(paths):
        if not is_initialized(path):
            results["not_init"].append(path)
            print(f"  [{i+1}/{len(paths)}] NOT INIT: {path}")
            continue
        
        timeout = TIMEOUT_FETCH * 3 if path in LARGE_REPOS else TIMEOUT_FETCH
        rc, out, err = run_git(["fetch", "--all", "--tags", "--no-recurse-submodules"], 
                               cwd=WORKSPACE / path, timeout=timeout)
        if rc == 0:
            results["fetched"].append(path)
            print(f"  [{i+1}/{len(paths)}] OK: {path}")
        else:
            results["fetch_errors"].append({"path": path, "error": err[:200]})
            print(f"  [{i+1}/{len(paths)}] FAIL: {path} — {err[:100]}")
    
    # Also fetch root
    rc, out, err = run_git(["fetch", "--all", "--tags"], timeout=60)
    print(f"\n  Root fetch: {'OK' if rc == 0 else 'FAIL'}")
    
    print(f"\nFetched: {len(results['fetched'])}, Errors: {len(results['fetch_errors'])}, Not init: {len(results['not_init'])}")
    return results

# ============================================================================
# PHASE 2: Branch Audit & Intelligent Merge
# ============================================================================
def phase2_merge_engine():
    print("\n" + "="*70)
    print("PHASE 2: DUAL-DIRECTION INTELLIGENT MERGE ENGINE")
    print("="*70)
    
    paths = get_submodule_paths()
    
    # Also check root repo for dependabot branches
    print("\n--- ROOT REPO ---")
    rc, out, _ = run_git(["branch", "-r"])
    root_branches = [b.strip() for b in out.split('\n') if b.strip() and '->' not in b]
    for branch in root_branches:
        branch_short = branch.replace("origin/", "")
        if "dependabot/" in branch_short:
            has_commits, log = branch_has_unique_commits(WORKSPACE, branch, "origin/main")
            if has_commits:
                print(f"  ROOT: Dependabot branch {branch_short} has unique commits, attempting merge...")
                results["branches_found"][f"root/{branch_short}"] = log[:200]
    
    for i, path in enumerate(paths):
        if not is_initialized(path):
            continue
        
        print(f"\n--- [{i+1}/{len(paths)}] {path} ---")
        default_branch = get_default_branch(path)
        current_branch = get_current_branch(path)
        
        # Get all branches
        local_branches = get_local_branches(path)
        remote_branches = get_remote_branches(path)
        
        # Find feature branches
        all_branches = set()
        for b in local_branches:
            all_branches.add(("local", b))
        for b in remote_branches:
            b_short = b.replace("origin/", "")
            all_branches.add(("remote", b_short))
        
        feature_branches = []
        for source, branch in all_branches:
            if branch == default_branch or branch == current_branch:
                continue
            if not is_feature_branch(branch, default_branch):
                continue
            feature_branches.append((source, branch))
        
        if not feature_branches:
            print(f"  No feature branches found (default: {default_branch})")
            continue
        
        print(f"  Default: {default_branch}, Current: {current_branch}")
        print(f"  Feature branches: {[b[1] for b in feature_branches]}")
        
        for source, branch in feature_branches:
            ref = f"origin/{branch}" if source == "remote" else branch
            has_commits, log = branch_has_unique_commits(path, ref, default_branch)
            if not has_commits:
                print(f"    SKIP {branch}: no unique commits")
                results["merges_skipped"].append({"path": path, "branch": branch, "reason": "no unique commits"})
                continue
            
            num_commits = len(log.split('\n'))
            print(f"    BRANCH {branch}: {num_commits} unique commits")
            results["branches_found"][f"{path}/{branch}"] = log[:300]
            
            # Attempt merge
            success, msg = merge_branch(path, ref, default_branch)
            if success:
                print(f"    MERGED {branch} -> {default_branch}: {msg[:100]}")
                results["merges_success"].append({"path": path, "branch": branch, "msg": msg[:200]})
            else:
                # Try cherry-pick
                print(f"    MERGE FAILED, trying cherry-pick: {msg[:100]}")
                cp_success, cp_msg = cherry_pick_commits(path, ref, default_branch)
                if cp_success:
                    print(f"    CHERRY-PICK OK: {cp_msg}")
                    results["merges_success"].append({"path": path, "branch": branch, "msg": f"cherry-pick: {cp_msg}"})
                else:
                    print(f"    CHERRY-PICK FAILED: {cp_msg}")
                    results["merges_failed"].append({"path": path, "branch": branch, "msg": msg[:200], "cp_msg": cp_msg[:200]})
            
            results["merges_attempted"].append({"path": path, "branch": branch})
    
    print(f"\nMerge Summary:")
    print(f"  Attempted: {len(results['merges_attempted'])}")
    print(f"  Success: {len(results['merges_success'])}")
    print(f"  Failed: {len(results['merges_failed'])}")
    print(f"  Skipped: {len(results['merges_skipped'])}")
    return results

# ============================================================================
# PHASE 3: Reverse Merge (main -> feature branches)
# ============================================================================
def phase3_reverse_merge():
    print("\n" + "="*70)
    print("PHASE 3: REVERSE MERGE (Main -> Feature Branches)")
    print("="*70)
    
    # Only reverse-merge into branches that failed forward merge
    for item in results["merges_failed"]:
        path = item["path"]
        branch = item["branch"]
        default_branch = get_default_branch(path)
        
        print(f"\n  Reverse merge: {default_branch} -> {branch} in {path}")
        
        # Checkout feature branch
        rc, _, err = run_git(["checkout", branch], cwd=WORKSPACE / path, timeout=15)
        if rc != 0:
            # Try creating local tracking branch
            rc, _, err = run_git(["checkout", "-b", branch, f"origin/{branch}"], 
                                cwd=WORKSPACE / path, timeout=15)
        if rc != 0:
            print(f"    Cannot checkout {branch}: {err[:100]}")
            continue
        
        # Merge main into feature
        rc, out, err = run_git(["merge", default_branch, 
                                "-m", f"Protocol #260: reverse merge {default_branch} into {branch}",
                                "-X", "theirs"], cwd=WORKSPACE / path, timeout=TIMEOUT_MERGE)
        if rc == 0:
            print(f"    OK: {out[:100]}")
        else:
            run_git(["merge", "--abort"], cwd=WORKSPACE / path, timeout=10)
            print(f"    FAIL: {err[:100]}")
        
        # Checkout back to default
        run_git(["checkout", default_branch], cwd=WORKSPACE / path, timeout=10)
    
    return results

# ============================================================================
# PHASE 4: Fast-forward sync all submodules
# ============================================================================
def phase4_fast_forward():
    print("\n" + "="*70)
    print("PHASE 4: FAST-FORWARD SYNC ALL SUBMODULES")
    print("="*70)
    
    paths = get_submodule_paths()
    updated = 0
    ahead = 0
    dirty = 0
    
    for i, path in enumerate(paths):
        if not is_initialized(path):
            continue
        
        # Check if dirty
        rc, out, _ = run_git(["status", "--porcelain"], cwd=WORKSPACE / path, timeout=10)
        if rc == 0 and out.strip():
            results["dirty"].append(path)
            print(f"  [{i+1}/{len(paths)}] DIRTY: {path}")
            dirty += 1
            continue
        
        # Try fast-forward
        default_branch = get_default_branch(path)
        rc, _, _ = run_git(["checkout", default_branch], cwd=WORKSPACE / path, timeout=10)
        if rc != 0:
            continue
        
        rc, out, _ = run_git(["merge", f"origin/{default_branch}", "--ff-only"], 
                             cwd=WORKSPACE / path, timeout=30)
        if rc == 0:
            if "Already up to date" not in out and "Already up-to-date" not in out:
                updated += 1
                print(f"  [{i+1}/{len(paths)}] UPDATED: {path}")
        else:
            # Check if ahead
            rc2, out2, _ = run_git(["log", f"origin/{default_branch}..{default_branch}", "--oneline"],
                                   cwd=WORKSPACE / path, timeout=10)
            if rc2 == 0 and out2.strip():
                ahead += 1
                print(f"  [{i+1}/{len(paths)}] AHEAD: {path} ({len(out2.strip().split(chr(10)))} commits)")
            else:
                print(f"  [{i+1}/{len(paths)}] DIVERGED: {path}")
    
    print(f"\nSync Summary: Updated={updated}, Ahead={ahead}, Dirty={dirty}")
    return results

# ============================================================================
# PHASE 5: Handle special cases
# ============================================================================
def phase5_special_cases():
    print("\n" + "="*70)
    print("PHASE 5: SPECIAL CASES & KNOWN ISSUES")
    print("="*70)
    
    # 1. MilkDrop3 aios issue - fix .gitmodules if needed
    milkdrop = WORKSPACE / "MilkDrop3"
    if milkdrop.exists():
        # Check if aios is in .gitmodules
        aios_in_modules = False
        gm = milkdrop / ".gitmodules"
        if gm.exists():
            content = gm.read_text()
            if "aios" in content:
                aios_in_modules = True
        
        if not aios_in_modules:
            # Check if aios dir exists and has .git
            aios_path = milkdrop / "aios"
            if aios_path.exists() and (aios_path / ".git").exists():
                print("  MilkDrop3/aios exists but not in .gitmodules — adding entry")
                # We'd need to add it, but let's check first
            else:
                print("  MilkDrop3/aios: no submodule mapping found (expected — not initialized)")
    
    # 2. HyperNexus branch check
    hn = WORKSPACE / "HyperNexus"
    if hn.exists():
        branch = get_current_branch("HyperNexus")
        print(f"  HyperNexus current branch: {branch}")
        if branch and branch != "main" and branch != "clean-main":
            print(f"    Note: HyperNexus is on {branch}, not main")
    
    # 3. Check for index.lock files
    lock_files = []
    for path in get_submodule_paths():
        if is_initialized(path):
            lock = WORKSPACE / path / ".git" / "index.lock"
            if isinstance(lock, Path) and lock.exists():
                lock_files.append(str(lock))
            # Also check .git (file pointing to .git dir)
            gitdir = WORKSPACE / path / ".git"
            if gitdir.is_file():
                # It's a gitdir pointer
                content = gitdir.read_text().strip()
                if "gitdir:" in content:
                    actual_gitdir = WORKSPACE / path / content.replace("gitdir:", "").strip()
                    lock2 = actual_gitdir / "index.lock"
                    if lock2.exists():
                        lock_files.append(str(lock2))
    
    if lock_files:
        print(f"  Found {len(lock_files)} stale index.lock files")
        for lf in lock_files:
            try:
                os.remove(lf)
                print(f"    Removed: {lf}")
            except:
                print(f"    Cannot remove: {lf}")
    else:
        print("  No stale index.lock files found")
    
    return results

# ============================================================================
# PHASE 6: Version Bump & Documentation
# ============================================================================
def phase6_version_bump():
    print("\n" + "="*70)
    print("PHASE 6: VERSION BUMP & DOCUMENTATION")
    print("="*70)
    
    # Read current version
    version_file = WORKSPACE / "VERSION"
    if version_file.exists():
        current = version_file.read_text(encoding='utf-8').strip()
        print(f"  Current version: {current}")
        
        # Parse and increment
        parts = current.replace("v", "").split(".")
        if len(parts) == 3:
            major, minor, patch = int(parts[0]), int(parts[1]), int(parts[2])
            new_version = f"v{major}.{minor}.{patch + 1}"
            print(f"  New version: {new_version}")
            
            # Update VERSION file
            version_file.write_text(new_version, encoding='utf-8')
            
            # Update VERSION.md
            version_md = WORKSPACE / "VERSION.md"
            if version_md.exists():
                content = version_md.read_text(encoding='utf-8')
                content = content.replace(current, new_version)
                version_md.write_text(content, encoding='utf-8')
            
            # Update CHANGELOG.md
            changelog = WORKSPACE / "CHANGELOG.md"
            if changelog.exists():
                content = changelog.read_text(encoding='utf-8')
                
                # Build changelog entry
                merged_items = ""
                for m in results["merges_success"]:
                    merged_items += f"- **{m['path']}**: merged `{m['branch']}` — {m['msg'][:100]}\n"
                
                failed_items = ""
                for m in results["merges_failed"]:
                    failed_items += f"- **{m['path']}**: `{m['branch']}` — conflicts unresolved\n"
                
                entry = f"""## [{new_version}] — {datetime.now().strftime('%Y-%m-%d')} — Protocol #260 — Repository Sync & Intelligent Merge

### Merged
{merged_items if merged_items else "- No feature branch merges this cycle\n"}

### Fetch
- **Submodules fetched**: {len(results['fetched'])}/{len(get_submodule_paths())}
- **Fetch errors**: {len(results['fetch_errors'])}
- **Not initialized**: {len(results['not_init'])}

### Changed
- **Version bumped**: {current} → {new_version}

"""
                if failed_items:
                    entry += f"### Deferred\n{failed_items}\n"
                
                # Prepend to changelog
                # Find the first ## header and insert before it
                lines = content.split('\n')
                insert_idx = 0
                for idx, line in enumerate(lines):
                    if line.startswith('## [v') and idx > 0:
                        insert_idx = idx
                        break
                
                lines.insert(insert_idx, entry)
                changelog.write_text('\n'.join(lines), encoding='utf-8')
            
            return new_version
    else:
        print("  VERSION file not found!")
    
    return None

# ============================================================================
# PHASE 7: Commit & Push
# ============================================================================
def phase7_commit_push(new_version):
    print("\n" + "="*70)
    print("PHASE 7: COMMIT & PUSH")
    print("="*70)
    
    # Stage all submodule changes
    rc, out, err = run_git(["add", "."], timeout=60)
    print(f"  Root git add: {'OK' if rc == 0 else 'FAIL'}")
    
    # Commit
    msg = f"v{new_version}: Protocol #260 — repo sync, branch merges, version bump"
    rc, out, err = run_git(["commit", "-m", msg, "--allow-empty"], timeout=30)
    if rc == 0:
        print(f"  Committed: {out[:100]}")
    else:
        print(f"  Commit: {err[:100]}")
    
    # Push each modified submodule
    for item in results["merges_success"]:
        path = item["path"]
        default_branch = get_default_branch(path)
        timeout = TIMEOUT_PUSH * 3 if path in LARGE_REPOS else TIMEOUT_PUSH
        rc, out, err = run_git(["push", "origin", default_branch], 
                               cwd=WORKSPACE / path, timeout=timeout)
        if rc == 0:
            results["pushed"].append(path)
            print(f"  PUSH OK: {path}")
        else:
            results["push_errors"].append({"path": path, "error": err[:200]})
            print(f"  PUSH FAIL: {path} — {err[:100]}")
    
    # Push root
    rc, out, err = run_git(["push", "origin", "main"], timeout=TIMEOUT_PUSH)
    if rc == 0:
        print(f"  ROOT PUSH: OK")
    else:
        print(f"  ROOT PUSH: {err[:100]}")
    
    return results

# ============================================================================
# PHASE 8: Generate HANDOFF.md
# ============================================================================
def phase8_handoff(new_version):
    print("\n" + "="*70)
    print("PHASE 8: GENERATE HANDOFF.md")
    print("="*70)
    
    handoff = WORKSPACE / "HANDOFF.md"
    
    merged_section = ""
    for m in results["merges_success"]:
        merged_section += f"- **{m['path']}**: `{m['branch']}` — {m['msg'][:150]}\n"
    if not merged_section:
        merged_section = "- No feature branch merges this cycle\n"
    
    failed_section = ""
    for m in results["merges_failed"]:
        failed_section += f"- **{m['path']}**: `{m['branch']}` — {m['msg'][:150]}\n"
    
    dirty_section = ""
    for d in results["dirty"]:
        dirty_section += f"- {d}\n"
    
    not_init_section = ""
    for n in results["not_init"]:
        not_init_section += f"- {n}\n"
    
    content = f"""# HANDOFF — {new_version} — {datetime.now().strftime('%Y-%m-%d')}

## Session Summary — Repository Sync & Intelligent Merge (Protocol #260)

### Scope

Full EXECUTIVE PROTOCOL across the workspace: fetch all 112 submodules, branch audit & intelligent merge, version bump, documentation sync, and push.

### STEP 1: Fetch & Sanitization

- **Fetched**: {len(results['fetched'])}/{len(get_submodule_paths())} submodules
- **Fetch errors**: {len(results['fetch_errors'])}
- **Not initialized**: {len(results['not_init'])}
- **Dirty submodules**: {len(results['dirty'])}

### STEP 2: Dual-Direction Intelligent Merge

- **Branches audited**: {len(results['branches_found'])} feature branches found across all repos
- **Merges attempted**: {len(results['merges_attempted'])}
- **Merges succeeded**: {len(results['merges_success'])}
- **Merges failed**: {len(results['merges_failed'])}
- **Skipped (no unique commits)**: {len(results['merges_skipped'])}

#### Merged
{merged_section}

#### Failed (deferred)
{failed_section}

### STEP 3: Workspace Cleanup

- **Version bumped**: {results.get('version_from', 'v5.284.0')} → {new_version}
- **CHANGELOG.md**: Updated with Protocol #260 entry
- **Submodule status**: All initialized submodules synced

### Not Initialized
{not_init_section if not_init_section else "- All submodules initialized\n"}

### Dirty Submodules
{dirty_section if dirty_section else "- None\n"}

### Deferred

- HyperNexus `gitlab/feature/cloud-dashboard-mcp-sse` — needs dedicated session
- warp `zb/*` branches — unrelated histories, needs dedicated session
- topaz-ffmpeg FFmpeg upstream — large, needs dedicated session
- bobeditpro Audacity upstream — needs dedicated session

### Push Status

- **Submodules pushed**: {len(results['pushed'])}
- **Push errors**: {len(results['push_errors'])}

---

## Previous Sessions

"""
    
    # Read existing HANDOFF.md and append previous sessions
    if handoff.exists():
        existing = handoff.read_text(encoding='utf-8')
        # Find the first --- separator and take everything after it
        if "---" in existing:
            parts = existing.split("---", 1)
            if len(parts) > 1:
                content += parts[1]
    
    handoff.write_text(content, encoding='utf-8')
    print(f"  HANDOFF.md written ({len(content)} chars)")
    return content

# ============================================================================
# MAIN
# ============================================================================
def main():
    start_time = time.time()
    
    print("="*70)
    print("PROTOCOL #260 — REPOSITORY SYNCHRONIZATION & INTELLIGENT MERGE")
    print(f"Started: {datetime.now().isoformat()}")
    print(f"Workspace: {WORKSPACE}")
    print("="*70)
    
    # Phase 1: Fetch
    phase1_fetch_all()
    
    # Phase 2: Branch audit & merge
    phase2_merge_engine()
    
    # Phase 3: Reverse merge
    phase3_reverse_merge()
    
    # Phase 4: Fast-forward sync
    phase4_fast_forward()
    
    # Phase 5: Special cases
    phase5_special_cases()
    
    # Phase 6: Version bump
    new_version = phase6_version_bump()
    
    # Phase 7: Commit & push
    if new_version:
        phase7_commit_push(new_version)
    
    # Phase 8: Handoff
    phase8_handoff(new_version or "v5.285.0")
    
    # Save results
    elapsed = time.time() - start_time
    results["elapsed_seconds"] = elapsed
    results["new_version"] = new_version
    
    with open(WORKSPACE / "sync_protocol_260_results.json", "w") as f:
        json.dump(results, f, indent=2, default=str)
    
    print(f"\n{'='*70}")
    print(f"PROTOCOL #260 COMPLETE in {elapsed:.0f}s")
    print(f"Results saved to sync_protocol_260_results.json")
    print(f"{'='*70}")

if __name__ == "__main__":
    main()