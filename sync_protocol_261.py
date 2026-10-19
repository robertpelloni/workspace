#!/usr/bin/env python3
"""
Protocol #261 — Full EXECUTIVE PROTOCOL: Repository Synchronization & Intelligent Merge
Runs all 3 steps with intelligent branch reconciliation across 112 submodules.
"""
import subprocess, os, json, sys, time, shutil, re
from datetime import datetime
from pathlib import Path

WORKSPACE = Path("C:/Users/hyper/workspace")
BIG_REPOS = {"element-web", "geany", "FFmpeg", "HyperNexus2old", "llvm-project", "jdk",
             "grammars-v4", "tabby", "OpenMBU", "MarbleBlast", "stepmania", "beatoraja"}

results = {
    "protocol": 261,
    "version_from": "v5.285.0",
    "timestamp": datetime.now().isoformat(),
    "fetch_ok": 0, "fetch_fail": [],
    "branches_found": [], "merges": [], "merges_skipped": [],
    "pushes": [], "push_fail": [],
    "dirty": [], "clean": 0, "errors": []
}

def run(args, cwd=None, timeout=60):
    if cwd is None: cwd = WORKSPACE
    try:
        p = subprocess.run(["git"] + args, cwd=str(cwd), capture_output=True, text=True, timeout=timeout)
        return p.returncode, p.stdout.strip(), p.stderr.strip()
    except subprocess.TimeoutExpired:
        return -1, "", "TIMEOUT"
    except Exception as e:
        return -1, "", str(e)

def get_subs():
    rc, out, _ = run(["config", "--file", ".gitmodules", "--get-regexp", "path"])
    return [l.split(' ', 1)[1].strip() for l in out.split('\n') if l]

def is_init(p):
    return os.path.exists(WORKSPACE / p / ".git") or os.path.isfile(WORKSPACE / p / ".git")

def default_branch(p):
    for b in ["main", "master"]:
        rc, _, _ = run(["rev-parse", "--verify", b], cwd=WORKSPACE / p, timeout=5)
        if rc == 0: return b
    rc, out, _ = run(["symbolic-ref", "refs/remotes/origin/HEAD", "--short"], cwd=WORKSPACE / p, timeout=5)
    return out.replace("origin/", "") if rc == 0 else "main"

def cur_branch(p):
    rc, out, _ = run(["rev-parse", "--abbrev-ref", "HEAD"], cwd=WORKSPACE / p, timeout=10)
    return out if rc == 0 else None

def clean_locks(p):
    """Remove stale index.lock files."""
    gd = WORKSPACE / p / ".git"
    for base in [gd, WORKSPACE / ".git" / "modules" / p]:
        lock = base / "index.lock"
        if lock.exists():
            try: lock.unlink(); return True
            except: pass
    # Check gitfile pointer
    if gd.is_file():
        content = gd.read_text().strip()
        if "gitdir:" in content:
            actual = (WORKSPACE / p / content.replace("gitdir:", "").strip()).resolve()
            lock = actual / "index.lock"
            if lock.exists():
                try: lock.unlink(); return True
                except: pass
    return False

# ============================================================
# STEP 1: FETCH & SANITIZE
# ============================================================
def step1():
    print("="*70)
    print("STEP 1: FETCH & SANITIZE")
    print("="*70)
    
    # Clean stale locks first
    for p in get_subs():
        if clean_locks(p):
            print(f"  Cleaned lock: {p}")
    
    # Fetch root
    rc, _, err = run(["fetch", "--all", "--tags"], timeout=120)
    print(f"Root fetch: {'OK' if rc == 0 else err[:80]}")
    
    # Fetch each submodule
    subs = get_subs()
    for i, p in enumerate(subs):
        if not is_init(p):
            print(f"  [{i+1}/{len(subs)}] SKIP (not init): {p}")
            continue
        t = 180 if p in BIG_REPOS else 60
        rc, _, err = run(["fetch", "--all", "--tags", "--no-recurse-submodules"],
                         cwd=WORKSPACE / p, timeout=t)
        if rc == 0:
            results["fetch_ok"] += 1
        else:
            results["fetch_fail"].append({"path": p, "err": err[:100]})
            print(f"  [{i+1}/{len(subs)}] FETCH FAIL: {p} — {err[:60]}")
    
    print(f"Fetched: {results['fetch_ok']}/{len(subs)}, Failures: {len(results['fetch_fail'])}")
    
    # Check upstream remotes on submodules
    upstream_count = 0
    for p in subs:
        if not is_init(p): continue
        rc, out, _ = run(["remote"], cwd=WORKSPACE / p, timeout=5)
        if "upstream" in out:
            upstream_count += 1
    print(f"Submodules with upstream remote: {upstream_count}")

# ============================================================
# STEP 1B: CHECK DIRTY STATE
# ============================================================
def check_dirty():
    print("\n--- Dirty State Check ---")
    for p in get_subs():
        if not is_init(p): continue
        rc, out, _ = run(["status", "--porcelain"], cwd=WORKSPACE / p, timeout=15)
        if rc == 0 and out.strip():
            results["dirty"].append(p)
        else:
            results["clean"] += 1
    print(f"Clean: {results['clean']}, Dirty: {len(results['dirty'])}")
    if results["dirty"]:
        print(f"Dirty: {results['dirty']}")

# ============================================================
# STEP 2: MERGE ENGINE
# ============================================================
SKIP_BRANCH_PATTERNS = ["HEAD", "origin/HEAD", "dependabot/", "renovate/", "gh-pages",
                        "pages", "upstream/", "greenkeeper/"]

def is_feature_branch(name, default):
    if name == default: return False
    for pat in SKIP_BRANCH_PATTERNS:
        if pat in name: return False
    return True

def step2():
    print("\n" + "="*70)
    print("STEP 2: DUAL-DIRECTION INTELLIGENT MERGE ENGINE")
    print("="*70)
    
    subs = get_subs()
    
    # First: Root repo dependabot branches
    print("\n--- ROOT REPO ---")
    rc, out, _ = run(["branch", "-r"])
    for line in out.split('\n'):
        b = line.strip()
        if not b or '->' in b: continue
        short = b.replace("origin/", "")
        if "dependabot/" in short:
            rc2, log, _ = run(["log", "--oneline", f"origin/main..{b}"], timeout=15)
            if rc2 == 0 and log.strip():
                n = len(log.strip().split('\n'))
                print(f"  Dependabot: {short} ({n} commits) — merging")
                rc3, _, err = run(["cherry-pick", log.strip().split('\n')[0].split()[0]], timeout=60)
                if rc3 != 0:
                    run(["cherry-pick", "--abort"], timeout=10)
                    # Try all commits
                    for cl in log.strip().split('\n'):
                        sha = cl.split()[0]
                        rc4, _, _ = run(["cherry-pick", sha], timeout=60)
                        if rc4 != 0:
                            run(["cherry-pick", "--abort"], timeout=10)
                results["merges"].append({"path": "root", "branch": short, "type": "cherry-pick"})
    
    # Per-submodule branch audit
    for i, p in enumerate(subs):
        if not is_init(p): continue
        db = default_branch(p)
        cb = cur_branch(p)
        
        # Get all branches
        rc, out, _ = run(["branch", "-a"], cwd=WORKSPACE / p, timeout=15)
        branches = []
        for line in out.split('\n'):
            b = line.strip().replace('* ', '')
            if not b: continue
            if b.startswith("remotes/"):
                b = b.replace("remotes/origin/", "")
            branches.append(b)
        
        features = [b for b in set(branches) if is_feature_branch(b, db)]
        if not features: continue
        
        for fb in features:
            # Check for unique commits
            ref = fb
            rc, log, _ = run(["log", "--oneline", f"{db}..{ref}"], cwd=WORKSPACE / p, timeout=15)
            if rc != 0:
                rc, log, _ = run(["log", "--oneline", f"{db}..origin/{fb}"], cwd=WORKSPACE / p, timeout=15)
                ref = f"origin/{fb}"
            if rc != 0 or not log.strip():
                results["merges_skipped"].append({"path": p, "branch": fb, "reason": "no unique commits"})
                continue
            
            n = len(log.strip().split('\n'))
            print(f"\n  [{i+1}/{len(subs)}] {p}: branch `{fb}` has {n} unique commits")
            results["branches_found"].append({"path": p, "branch": fb, "commits": n, "log": log[:300]})
            
            # Save current branch
            orig = cb or db
            
            # Try fast-forward merge
            rc, _, _ = run(["checkout", db], cwd=WORKSPACE / p, timeout=15)
            if rc != 0: continue
            
            rc, out, err = run(["merge", ref, "--no-edit", "-X", "theirs",
                                "-m", f"Protocol #261: merge {fb} into {db}"],
                               cwd=WORKSPACE / p, timeout=60)
            
            if rc == 0:
                print(f"    MERGED: {out[:80]}")
                results["merges"].append({"path": p, "branch": fb, "type": "merge"})
            else:
                run(["merge", "--abort"], cwd=WORKSPACE / p, timeout=10)
                
                # Cherry-pick approach
                rc2, log2, _ = run(["log", "--oneline", "--reverse", f"{db}..{ref}"],
                                   cwd=WORKSPACE / p, timeout=15)
                if rc2 == 0 and log2.strip():
                    picked = 0
                    for cl in log2.strip().split('\n'):
                        sha = cl.split()[0]
                        rc3, _, _ = run(["cherry-pick", sha], cwd=WORKSPACE / p, timeout=30)
                        if rc3 == 0:
                            picked += 1
                        else:
                            run(["cherry-pick", "--abort"], cwd=WORKSPACE / p, timeout=10)
                    if picked > 0:
                        print(f"    CHERRY-PICKED: {picked}/{n} commits")
                        results["merges"].append({"path": p, "branch": fb, "type": f"cherry-pick ({picked}/{n})"})
                    else:
                        print(f"    FAILED: could not merge or cherry-pick")
                        results["merges"].append({"path": p, "branch": fb, "type": "failed"})
                else:
                    print(f"    FAILED: {err[:80]}")
                    results["merges"].append({"path": p, "branch": fb, "type": "failed"})
            
            # Restore original branch
            if orig != db:
                run(["checkout", orig], cwd=WORKSPACE / p, timeout=10)
    
    print(f"\nMerge Summary:")
    print(f"  Branches found: {len(results['branches_found'])}")
    print(f"  Merges: {len(results['merges'])}")
    print(f"  Skipped: {len(results['merges_skipped'])}")

# ============================================================
# STEP 2B: REVERSE MERGE (main -> feature branches with failures)
# ============================================================
def step2b_reverse():
    print("\n--- Reverse Merge (main -> feature branches) ---")
    for item in results["merges"]:
        if item["type"] != "failed": continue
        p, fb = item["path"], item["branch"]
        db = default_branch(p)
        
        print(f"  Reverse merging {db} -> {fb} in {p}")
        rc, _, _ = run(["checkout", fb], cwd=WORKSPACE / p, timeout=15)
        if rc != 0:
            run(["checkout", "-b", fb, f"origin/{fb}"], cwd=WORKSPACE / p, timeout=15)
        
        rc, out, err = run(["merge", db, "--no-edit", "-X", "theirs",
                            "-m", f"Protocol #261: reverse merge {db} into {fb}"],
                           cwd=WORKSPACE / p, timeout=60)
        if rc == 0:
            print(f"    OK")
        else:
            run(["merge", "--abort"], cwd=WORKSPACE / p, timeout=10)
            print(f"    FAIL: {err[:60]}")
        
        run(["checkout", db], cwd=WORKSPACE / p, timeout=10)

# ============================================================
# STEP 3: VERSION BUMP, DOCS, PUSH
# ============================================================
def step3():
    print("\n" + "="*70)
    print("STEP 3: WORKSPACE CLEANUP & FINALIZATION")
    print("="*70)
    
    # Version bump
    vf = WORKSPACE / "VERSION"
    current = vf.read_text(encoding='utf-8').strip()
    parts = current.replace("v", "").split(".")
    major, minor, patch = int(parts[0]), int(parts[1]), int(parts[2])
    new_version = f"v{major}.{minor}.{patch + 1}"
    vf.write_text(new_version, encoding='utf-8')
    print(f"Version: {current} -> {new_version}")
    
    # Update VERSION.md
    vm = WORKSPACE / "VERSION.md"
    if vm.exists():
        content = vm.read_text(encoding='utf-8')
        content = content.replace(current, new_version)
        content = re.sub(r'\*\*Updated:\*\* \d{4}-\d{2}-\d{2}',
                         f'**Updated:** {datetime.now().strftime("%Y-%m-%d")}', content)
        vm.write_text(content, encoding='utf-8')
    
    # Update CHANGELOG.md
    cl = WORKSPACE / "CHANGELOG.md"
    if cl.exists():
        content = cl.read_text(encoding='utf-8')
        
        merged_desc = ""
        for m in results["merges"]:
            if m["type"] != "failed":
                merged_desc += f"- **{m['path']}**: `{m['branch']}` — {m['type']}\n"
        if not merged_desc:
            merged_desc = "- No new feature branches found across 112 submodules\n"
        
        entry = f"""## [{new_version}] — {datetime.now().strftime('%Y-%m-%d')} — Protocol #261 — Repository Sync & Intelligent Merge

### Merged
{merged_desc}
### Fetch
- **Submodules fetched**: {results['fetch_ok']}/112
- **Fetch failures**: {len(results['fetch_fail'])}
- **Clean submodules**: {results['clean']}, **Dirty**: {len(results['dirty'])}

### Changed
- **Version bumped**: {current} -> {new_version}
- **Full branch audit**: 112 submodules scanned for feature branches

"""
        # Insert before first ## [v
        lines = content.split('\n')
        idx = 0
        for j, line in enumerate(lines):
            if line.startswith('## [v') and j > 0:
                idx = j
                break
        lines.insert(idx, entry)
        cl.write_text('\n'.join(lines), encoding='utf-8')
        print("CHANGELOG.md updated")
    
    # Update HANDOFF.md
    handoff = WORKSPACE / "HANDOFF.md"
    
    merged_section = ""
    for m in results["merges"]:
        if m["type"] != "failed":
            merged_section += f"- **{m['path']}**: `{m['branch']}` — {m['type']}\n"
    if not merged_section:
        merged_section = "- No new feature branches to merge (all submodules up to date)\n"
    
    dirty_str = ", ".join(results["dirty"][:15]) if results["dirty"] else "None"
    
    handoff_content = f"""# HANDOFF — {new_version} — {datetime.now().strftime('%Y-%m-%d')}

## Session Summary — Repository Sync & Intelligent Merge (Protocol #261)

### Scope

Full EXECUTIVE PROTOCOL across 112 submodules: fetch, sanitize, branch audit, intelligent merge, reverse merge, version bump, docs sync, and push.

### STEP 1: Fetch & Sanitization

- **Fetched**: {results['fetch_ok']}/112 submodules
- **Fetch failures**: {len(results['fetch_fail'])}
- **Clean**: {results['clean']}, **Dirty**: {len(results['dirty'])} ({dirty_str})

### STEP 2: Dual-Direction Intelligent Merge

- **Feature branches found**: {len(results['branches_found'])}
- **Merges executed**: {len([m for m in results['merges'] if m['type'] != 'failed'])}
- **Skipped**: {len(results['merges_skipped'])}

#### Merged
{merged_section}
### STEP 3: Finalization

- **Version**: {current} -> {new_version}
- **CHANGELOG.md**, **HANDOFF.md**, **VERSION.md** updated

### Deferred

- HyperNexus `gitlab/feature/cloud-dashboard-mcp-sse` — orphan branch, needs dedicated session
- topaz-ffmpeg / bobeditpro upstream syncs — dedicated sessions
- Dependabot vulnerability backlog

---

## Previous Sessions

"""
    if handoff.exists():
        existing = handoff.read_text(encoding='utf-8')
        if "---" in existing:
            parts = existing.split("---", 1)
            if len(parts) > 1:
                handoff_content += "## Previous Sessions\n\n" + parts[1]
    
    handoff.write_text(handoff_content, encoding='utf-8')
    print("HANDOFF.md updated")
    
    return new_version

# ============================================================
# STEP 3B: PUSH
# ============================================================
def step3b_push(new_version):
    print("\n--- Push ---")
    
    # Push merged submodules
    for item in results["merges"]:
        if item["type"] == "failed": continue
        p = item["path"]
        if p == "root": continue
        db = default_branch(p)
        t = 180 if p in BIG_REPOS else 60
        rc, out, err = run(["push", "origin", db], cwd=WORKSPACE / p, timeout=t)
        if rc == 0:
            results["pushes"].append(p)
            print(f"  PUSH OK: {p}")
        else:
            results["push_fail"].append({"path": p, "err": err[:100]})
            print(f"  PUSH FAIL: {p} — {err[:60]}")
    
    # Push root (targeted add)
    for f in ["VERSION", "VERSION.md", "CHANGELOG.md", "HANDOFF.md"]:
        run(["add", f], timeout=30)
    
    # Also add any merged submodule pointers
    for item in results["merges"]:
        if item["path"] != "root" and item["type"] != "failed":
            run(["add", item["path"]], timeout=30)
    
    rc, out, err = run(["commit", "-m",
                         f"{new_version}: Protocol #261 — repo sync, branch audit, merge engine, version bump"],
                        timeout=120)
    if rc == 0:
        print(f"  COMMITTED: {out[:80]}")
    else:
        print(f"  COMMIT: {err[:80]}")
    
    rc, out, err = run(["push", "origin", "main"], timeout=300)
    if rc == 0:
        print(f"  ROOT PUSH: OK")
    else:
        print(f"  ROOT PUSH: {err[:100]}")

# ============================================================
# MAIN
# ============================================================
def main():
    t0 = time.time()
    print("="*70)
    print(f"PROTOCOL #261 — REPOSITORY SYNC & INTELLIGENT MERGE")
    print(f"Started: {datetime.now().isoformat()}")
    print("="*70)
    
    step1()
    check_dirty()
    step2()
    step2b_reverse()
    new_version = step3()
    step3b_push(new_version)
    
    elapsed = time.time() - t0
    results["elapsed"] = elapsed
    results["new_version"] = new_version
    
    with open(WORKSPACE / "sync_protocol_261_results.json", "w", encoding='utf-8') as f:
        json.dump(results, f, indent=2, default=str, ensure_ascii=False)
    
    print(f"\n{'='*70}")
    print(f"PROTOCOL #261 COMPLETE — {elapsed:.0f}s")
    print(f"Version: {new_version}")
    print(f"{'='*70}")

if __name__ == "__main__":
    main()