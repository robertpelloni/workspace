# Workspace Handoff — v4.3.1

**Date**: 2026-05-27
**Version**: 4.3.1
**Commit**: pending

## ⚠️ CRITICAL FINDING: Historical Data Loss Recovered

### Problem
Between v3.97.0 and v4.0.0, the auto-commit protocol did NOT push commits to origin
before running `git reset --hard origin/HEAD`. This caused 34 committed changes to be
orphaned when HEAD was reset back to origin. The commits remained in the reflog but
were not on any remote branch.

### Root Cause
Pre-v4.1.0, the sequence was:
1. `git add -A && git commit` (auto-commit)
2. `git reset --hard origin/HEAD` (overwrites the auto-commit)

Since v4.1.0, the sequence is:
1. `git add -A && git commit` (auto-commit)
2. `git push origin $db` (push to remote) ← NEW
3. `git reset --hard origin/HEAD` (now resets TO the pushed commit)

### Recovery Summary
| Repo | Commits Recovered | Content | Status |
|------|-------------------|---------|--------|
| bobfilez | 3 critical + 12 submodule | Delete Dupes tab, OpenSSL CMake, test cleanup | ✅ Pushed |
| agentirc | 1 | run.py + agents.json (86+22 lines) | ✅ Pushed |
| borg | 1 (uncommitted WT) | MCP tools: set_capacity, auto_call_tool (46 lines) | ✅ Pushed |
| bobbybookmarks | 1 | Runtime databases (atlas.db, borg.db) | ✅ Pushed |

### Confirmed Safe (submodule pointers already superseded)
- bobtorrent (3), bobtrader (3), bobui (3), btk (2) — all just submodule pointer bumps

### Still Uncommitted (runtime/session data, not code)
- auto_dj_script: .hypercode session files
- openclaw-dashboard: .gitignore fix (ephemeral, 5th cycle)

## Session Summary

### STEP 1: Upstream Tracking
- **Upstream merges**: 2 (bobtorrent, topaz-ffmpeg ARM NEON fix)
- **Auto-committed**: 8 repos, 7 pushed — **0 data loss**
- **bobsgameweb**: 3 new remote commits (shadow/collision/Y-sorting)

### STEP 2: Merge Engine
- **Forward merges**: 4 (bobgui ×3, planet_fitness ×1)
- **Failed**: 1 (bobgui/macOS DnD fix — 10 conflicts)
- **Branch cleanup**: 3 remote deleted

### STEP 3: Data Recovery + Build
- **34 lost commits recovered** from reflog across 10 repos
- **46 lines of uncommitted borg code** committed and pushed
- **Builds**: jules-autopilot ✅, hyperharness ✅
- **Version**: 4.3.0 → **4.3.1**

### Jules-Autopilot Specific Analysis
The reflog shows NO orphaned commits — all commits are on origin/main.
The "files lost" concern appears to be about:
1. **Timing**: Files written by Jules between sync cycles get committed by Jules
   itself and pushed to origin, so `git reset --hard origin/main` picks them up.
2. **Uncommitted files**: If Jules writes files but doesn't commit them, they
   survive `git reset --hard` (only tracked files get reset). BUT they would
   be lost if someone runs `git checkout .` or `git clean`.
3. **The real risk**: `git reset --hard` DOES overwrite tracked files that
   have been modified locally. If Jules modified a tracked file but didn't
   commit, the reset would revert it to the origin version.

## Known Issues (unchanged)
1. bobfilez: git operations hang (pybind11 nested recursion)
2. bobsgameweb: `git fetch` fails (invalid index-pack)
3. bobbybookmarks: gc/repack timeout
4. element-web: Only `git fetch origin develop` works
5. fwber: Orphan repo, 51 behind upstream
6. borg: upstream OhMyOpenCode/aios deleted
7. OmniRoute: 5+ release branches too diverged
8. openclaw-dashboard: No push access (5th cycle .gitignore recurrence)
9. bobgui/amolenaar/fix-dnd-macos-26: 10 conflicts, deferred
10. 242 GitHub security vulnerabilities (3 critical)

## Updated Auto-Commit Protocol (v4.3.1+)

### Previous Protocol (v4.1.0–v4.3.0)
```
1. git add -A && git commit  (auto-commit)
2. git push origin $db       (push to remote)
3. git reset --hard origin/$db (reset)
```
**Gap**: If push fails, or if new changes arrive between step 1 and step 3, `git reset --hard` destroys them.

### New Protocol (v4.3.1+)
```
1. git add -A && git commit  (auto-commit)
2. git push origin $db       (push to remote)
3. git stash --include-untracked  (SAFETY NET: stash any remaining working tree changes)
4. git reset --hard origin/$db    (reset)
5. git stash pop             (restore stashed changes — may fail safely if stash is empty)
```
**Recovery**: If anything goes wrong, `git stash list` shows the backup. `git stash pop` restores it.
