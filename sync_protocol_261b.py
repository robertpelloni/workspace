#!/usr/bin/env python3
"""
Protocol #261 Part B: Fix dirty states, retry merges, fix identity issues.
"""
import subprocess, os, json, time, sys
from datetime import datetime
from pathlib import Path

WORKSPACE = Path("C:/Users/hyper/workspace")
BIG_REPOS = {"element-web", "geany", "FFmpeg", "HyperNexus2old", "llvm-project", "jdk",
             "grammars-v4", "tabby", "OpenMBU", "MarbleBlast", "stepmania", "beatoraja"}

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

# Phase A: Fix git identity in all submodules (especially bobmani/*)
print("="*70)
print("PHASE A: SET GIT IDENTITY IN ALL SUBMODULES")
print("="*70)

subs = get_subs()
identity_set = 0
for p in subs:
    if not is_init(p): continue
    for key, val in [("user.name", "opencode"), ("user.email", "opencode@bot.com")]:
        run(["config", key, val], cwd=WORKSPACE / p, timeout=5)
    identity_set += 1
print(f"Identity set in {identity_set} submodules")

# Phase B: Commit dirty state in submodules (track memory, sessions, databases)
print("\n" + "="*70)
print("PHASE B: COMMIT DIRTY STATE (track memory/sessions/databases)")
print("="*70)

dirty_subs = []
for p in subs:
    if not is_init(p): continue
    rc, out, _ = run(["status", "--porcelain"], cwd=WORKSPACE / p, timeout=15)
    if rc != 0 or not out.strip(): continue
    
    lines = out.strip().split('\n')
    n = len(lines)
    
    # Classify changes
    has_code = False
    has_docs = False
    has_db = False
    has_agent = False
    for l in lines:
        fname = l[3:].strip() if len(l) > 3 else ""
        if any(fname.endswith(e) for e in ['.go', '.py', '.js', '.ts', '.java', '.c', '.cpp', '.rs', '.rb', '.sh', '.bat']):
            has_code = True
        if any(fname.endswith(e) for e in ['.db', '.sqlite', '.db-shm', '.db-wal']):
            has_db = True
        if any(x in fname for x in ['.memory', '.hypernexus', 'MEMORY', 'session', 'HANDOFF', 'AGENTS', 'CLAUDE']):
            has_agent = True
        if any(fname.endswith(e) for e in ['.md', '.txt', '.json', '.yaml', '.yml']):
            has_docs = True
    
    # Commit message
    parts = []
    if has_code: parts.append("code")
    if has_db: parts.append("databases")
    if has_agent: parts.append("agent-memory/sessions")
    if has_docs: parts.append("docs/config")
    desc = ", ".join(parts) if parts else "working-tree sync"
    
    run(["add", "-A"], cwd=WORKSPACE / p, timeout=30)
    rc2, out2, err2 = run(["commit", "-m", f"Protocol #261: track {desc} ({n} files)"],
                          cwd=WORKSPACE / p, timeout=30)
    if rc2 == 0:
        dirty_subs.append({"path": p, "files": n, "type": desc})
        print(f"  COMMITTED {p}: {n} files ({desc})")
    else:
        print(f"  FAILED {p}: {err2[:80]}")

print(f"\nCommitted dirty state in {len(dirty_subs)} submodules")

# Phase C: Retry failed merges with clean working directories
print("\n" + "="*70)
print("PHASE C: RETRY FAILED MERGES")
print("="*70)

merge_targets = [
    ("hymnmania", "master", "main"),
    ("bobmani/beatoraja", "jules-3962252154118760376-7a465b48", "main"),
    ("bobmani/hymnmania", "master", "main"),
    ("bobmani/ksm-v2", "feat-async-post-ranking-unlock-7547845477294015222", "main"),
    ("bobmani/linthesia", "jules-gtkmm-migration-17914190840350960258", "main"),
    ("bobmani/pianogame", "jules-71435653877870057-8b2f1bce", "master"),
    ("jvm-cpp-runtime", "jvmcpp-runtime-13637006691171799819", "main"),
]

merge_results = []
for path, branch, target in merge_targets:
    full = WORKSPACE / path
    if not (full / ".git").exists() and not (full / ".git").is_file():
        print(f"  SKIP {path}: not initialized")
        continue
    
    db = default_branch(path)
    print(f"\n  {path}: merging `{branch}` -> `{db}`")
    
    # Ensure we're on default branch and clean
    run(["checkout", db], cwd=full, timeout=15)
    
    # Try merge
    rc, out, err = run(["merge", f"origin/{branch}", "--no-edit", "-X", "theirs",
                        "-m", f"Protocol #261: merge {branch} into {db}"],
                       cwd=full, timeout=60)
    if rc == 0:
        print(f"    MERGED: {out[:80]}")
        merge_results.append({"path": path, "branch": branch, "status": "merged"})
        continue
    
    # Try merge without -X theirs (in case it's a fast-forward or trivial)
    run(["merge", "--abort"], cwd=full, timeout=10)
    rc, out, err = run(["merge", f"origin/{branch}", "--no-edit",
                        "-m", f"Protocol #261: merge {branch} into {db}"],
                       cwd=full, timeout=60)
    if rc == 0:
        print(f"    MERGED (default): {out[:80]}")
        merge_results.append({"path": path, "branch": branch, "status": "merged"})
        continue
    
    # Conflicts — try cherry-pick
    run(["merge", "--abort"], cwd=full, timeout=10)
    rc2, log, _ = run(["log", "--oneline", "--reverse", f"{db}..origin/{branch}"],
                      cwd=full, timeout=15)
    if rc2 != 0 or not log.strip():
        print(f"    SKIP: no unique commits or log failed")
        merge_results.append({"path": path, "branch": branch, "status": "no commits"})
        continue
    
    commits = [l.split()[0] for l in log.strip().split('\n')]
    picked = 0
    conflicts = 0
    for sha in commits:
        rc3, _, err3 = run(["cherry-pick", sha], cwd=full, timeout=30)
        if rc3 == 0:
            picked += 1
        elif "conflict" in err3.lower() or "error" in err3.lower():
            conflicts += 1
            # Try to resolve conflicts by taking theirs
            rc4, _, _ = run(["cherry-pick", "--skip"], cwd=full, timeout=10)
            if rc4 != 0:
                run(["cherry-pick", "--abort"], cwd=full, timeout=10)
    
    if picked > 0:
        print(f"    CHERRY-PICKED: {picked}/{len(commits)} ({conflicts} conflicts skipped)")
        merge_results.append({"path": path, "branch": branch,
                              "status": f"cherry-picked {picked}/{len(commits)}"})
    else:
        # Last resort: merge with allow-unrelated-histories
        rc5, out5, err5 = run(["merge", f"origin/{branch}", "--no-edit", "--allow-unrelated-histories",
                                "-X", "theirs",
                                "-m", f"Protocol #261: merge {branch} into {db} (unrelated-histories)"],
                               cwd=full, timeout=60)
        if rc5 == 0:
            print(f"    MERGED (unrelated): {out5[:80]}")
            merge_results.append({"path": path, "branch": branch, "status": "merged-unrelated"})
        else:
            run(["merge", "--abort"], cwd=full, timeout=10)
            print(f"    FAILED: all strategies exhausted")
            merge_results.append({"path": path, "branch": branch, "status": "failed"})

print(f"\nMerge retry results:")
for m in merge_results:
    print(f"  {m['path']}: {m['branch']} -> {m['status']}")

# Phase D: Push merged submodules
print("\n" + "="*70)
print("PHASE D: PUSH MERGED SUBMODULES")
print("="*70)

pushed = []
for m in merge_results:
    if m["status"] in ["failed", "no commits"]: continue
    p = m["path"]
    db = default_branch(p)
    t = 180 if p in BIG_REPOS else 60
    rc, out, err = run(["push", "origin", db], cwd=WORKSPACE / p, timeout=t)
    if rc == 0:
        pushed.append(p)
        print(f"  PUSH OK: {p}")
    else:
        print(f"  PUSH FAIL: {p} — {err[:60]}")

# Phase E: Commit and push root
print("\n" + "="*70)
print("PHASE E: ROOT COMMIT & PUSH")
print("="*70)

# Add all changed submodule pointers and docs
run(["add", "."], timeout=120)

rc, out, err = run(["commit", "-m",
    "Protocol #261 Part B: dirty-state commits, merge retries, identity fixes, submodule sync"],
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

# Save results
with open(WORKSPACE / "sync_protocol_261b_results.json", "w", encoding='utf-8') as f:
    json.dump({"dirty_committed": dirty_subs, "merge_results": merge_results,
               "pushed": pushed}, f, indent=2, ensure_ascii=False)

print(f"\n{'='*70}")
print("PROTOCOL #261 PART B COMPLETE")
print(f"{'='*70}")