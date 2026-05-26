# Workspace Handoff — v4.0.0

**Date**: 2026-05-25
**Version**: 4.0.0
**Commit**: pending

## Session Summary

This release marks the transition from v3.x to v4.0.0, reflecting 99 minor releases of continuous automated workspace maintenance.

### STEP 1: Upstream Tracking & Submodule Sanitization
- **Root fetch**: ✅
- **Submodule fetch**: 85/90 direct; 5 individually handled
- **Upstream sync**: No new upstream commits (all repos current)
- **Submodule updates**: 88 reset to origin/HEAD + 2 hang-prone repos handled separately
- **Auto-committed dirty repos**: 11
- **⚠️ Critical Discovery**: 7 auto-commits were lost during `git reset --hard origin/HEAD` because the auto-commit was ahead of origin. All 7 were recovered from reflog via cherry-pick and pushed successfully.

### STEP 2: Dual-Direction Intelligent Merge Engine

**Forward Merges (5 branches, 2 repos)**:
| Repo | Branch | Result | Notes |
|------|--------|--------|-------|
| bobgui | BUG_tooltip_position_CLEAN | ✅ | Upstream GTK tooltip fix |
| bobgui | 665-entry-textview-deselect-text-on-focus-out-4 | ✅ | **Recovered from v3.99.0 failure** — manual ours resolution |
| borg | dependabot/go_modules/.../go_modules-dfc5a1b899 | ✅ | Manual: deleted files updated by dependabot |
| borg | dependabot/npm_and_yarn/.../npm_and_yarn-2c1d5278f8 | ✅ | Manual: 12 deleted files |
| borg | dependabot/npm_and_yarn/.../npm_and_yarn-baa0c179e2 | ✅ | Manual: 9 deleted files |

**Failed Forward Merges (0)**:
- All attempted merges succeeded this cycle

**Carried Failures (not attempted)**:
- OmniRoute/release/v3.4.9 — 60 conflicts, too diverged (2917 files, 700k+ lines)
- OmniRoute/release/v3.5.0 — too diverged (2928 files, 650k+ lines)
- OmniRoute/release/v3.5.1–v3.5.3 — 0 unique files (divergent commit trees)

**Reverse Merges**: 0 (no active feature branches with unique content)

**Branch Cleanup**:
- 31 remote branches deleted
- 1 local branch deleted (topaz-ffmpeg/master)
- Total: 32

### .gitignore Audit
- **openclaw-dashboard**: Fixed — `memory/` blanket ignore changed to `memory/*.json`, `*.db`, `*.log`. Fix is local-only (no push access to upstream tugcantopaloglu repo; robertpelloni fork doesn't exist).
- All other repos: clean (no issues)

### Auto-Commit Recovery (Critical)
7 repos had auto-commits lost during `git reset --hard`:
| Repo | Lost SHA | Content | Status |
|------|----------|---------|--------|
| bobtorrent | 1ae6c95 | submodule pointer updates (bobcoin, qbittorrent) | ✅ Recovered |
| bobtrader | c14f726 | submodule pointer updates | ✅ Recovered |
| bobui | 90f7c15e725 | ultimatepp submodule update | ✅ Recovered |
| btk | 4a2637a6c | 3 external submodule updates | ✅ Recovered |
| opencode-autopilot | b03aef2 | .jules/memory/architecture.md | ✅ Recovered |
| pi-mono | 436677d2 | borg.db | ✅ Recovered |
| slsk_discography_downloader_script | 22f5a51 | discography_webapp/run_server.sh | ✅ Recovered |

### STEP 3: Workspace Cleanup & Build
- Scripts: start.bat ✅, build_all.bat ✅
- Version: 3.99.0 → **4.0.0**
- Submodule pointers: 14 updated
- Pushed: bobgui, borg, bobtorrent, bobtrader, bobui, btk, opencode-autopilot, pi-mono, slsk_discography_downloader_script

## Known Issues
1. **bobfilez**: git operations hang (pybind11 nested submodule recursion)
2. **bobsgameweb**: `git fetch` returns "invalid index-pack output"; HEAD matches origin/master
3. **element-web**: Only `git fetch origin develop` works
4. **fwber**: Orphan repo, 51 behind upstream
5. **borg**: upstream OhMyOpenCode/aios deleted (404)
6. **OmniRoute**: 5+ release branches too diverged to merge
7. **openclaw-dashboard**: No push access to upstream fork
8. **242 GitHub security vulnerabilities** (3 critical)
9. **⚠️ Auto-commit loss risk**: The reset-to-origin step can destroy auto-committed changes. Recommend: push auto-commits BEFORE resetting, or change the protocol to use `git stash` + `git stash pop` instead of auto-commit + reset.
