# Workspace Handoff — v4.4.0

**Date**: 2026-05-27
**Version**: 4.4.0
**Commit**: pending

## 🔑 Protocol Milestone: Stash-Before-Reset Debuted

The new `git stash --include-untracked` step before `git reset --hard` was successfully
deployed this cycle. **87 stash-pops** restored working tree changes across all repos.
The openclaw-dashboard `.gitignore` fix — which had been lost every cycle since v4.1.0 —
**SURVIVED the reset for the first time** because the stash captured it.

### Updated Auto-Commit Protocol (v4.4.0+)
```
1. git add -A && git commit      (auto-commit)
2. git push origin $db           (push to remote)
3. git stash --include-untracked (SAFETY NET: capture remaining WT changes)
4. git reset --hard origin/$db   (reset to remote HEAD)
5. git stash pop                 (restore stashed changes)
```

### Stash Conflict Resolution (4 conflicts this cycle)
When `git stash pop` produces conflicts, resolve by keeping the stashed (local) version:
```
git checkout --theirs <conflicted-file>
git add <conflicted-file>
git stash drop
```

## Session Summary

### STEP 1: Upstream Tracking & Submodule Sanitization
- **Root fetch**: ✅
- **Submodule fetch**: 85/90 direct; 5 individually handled
- **Upstream sync**: 2 new upstream merges:
  - **bobeditpro**: upstream/master (8 commits — GetEffects UI, SamplePacks, qsTrc)
  - **topaz-ffmpeg**: upstream/master (4 commits — TLS security: DTLS gating, GnuTLS crash, ff_tls_parse_host)
- **Submodule updates**: 88 reset + 2 hang-prone (ref plumbing)
- **Auto-committed**: 9 repos, 8 pushed — **0 data loss**
- **Stash-pops**: 87 successful, 4 conflicts resolved

### STEP 2: Dual-Direction Intelligent Merge Engine

**Upstream Merges (2)**:
| Repo | Upstream | Commits | Content |
|------|----------|---------|---------|
| bobeditpro | upstream/master | 8 | GetEffects dialog, SamplePacks, qsTrc plural forms |
| topaz-ffmpeg | upstream/master | 4 | TLS: DTLS gating, GnuTLS crash, host URI parsing |

**Forward Merges (3 branches, 2 repos)**:
| Repo | Branch | Commits | Files | Result |
|------|--------|---------|-------|--------|
| bobgui | amolenaar/macos-fix-shortcuts | 1 | 3 | ✅ |
| bobgui | amolenaar/macos-fullscreen-crash-backport | 71 | 62 | ✅ (4 conflicts, resolved ours) |
| borg | dependabot/npm_and_yarn | 1 | 4 | ✅ |

**Reverse Merges**: 0

**Branch Cleanup**: 9+ remote branches deleted

### .gitignore Audit: ✅ 0 ISSUES
- **openclaw-dashboard**: `memory/` fix SURVIVED the reset (stash-before-reset preserved it!)
- Previous cycles: 4 consecutive recurrences. **First cycle it survived.**

### Notable Remote Activity
- **jules-autopilot**: Session priority overhaul (FAILED > PAUSED/IDLE/COMPLETE > IN_PROGRESS, 1hr cooldown)
- **superdawmcp**: v2.8.0 (SDK Specialization & Logic Pro Feedback)
- **.agent**: v11.8.0 release

### STEP 3: Workspace Cleanup & Build
- Scripts: start.bat ✅, build_all.bat ✅
- Version: 4.3.1 → **4.4.0**
- Submodule pointers: 8 updated
- Pushed: bobeditpro, topaz-ffmpeg, bobgui, borg

## Known Issues
1. **bobfilez**: git operations hang (pybind11 nested submodule recursion)
2. **bobsgameweb**: `git fetch` fails (invalid index-pack); use ref plumbing
3. **bobbybookmarks**: gc/repack timeout; workaround: `gc.auto=0` + shallow fetch
4. **element-web**: Only `git fetch origin develop` works
5. **fwber**: Orphan repo, 51 behind upstream
6. **borg**: upstream OhMyOpenCode/aios deleted (404)
7. **OmniRoute**: 5+ release branches too diverged to merge
8. **openclaw-dashboard**: No push access; .gitignore fix survived via stash but needs fork for permanence
9. **bobgui/amolenaar/fix-dnd-macos-26**: 10 conflicts, deferred (97 ahead)
10. **bobgui/amolenaar/macos-26-native-controls-backport**: 103 ahead, large
11. **bobgui/adwaita**: 151 files, failed in v4.2.0
12. **242 GitHub security vulnerabilities** (3 critical)
