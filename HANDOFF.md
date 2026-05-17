# Workspace Handoff — v3.47.0

**Date**: 2026-05-16
**Version**: 3.47.0
**Commit**: a4985e8f2

## Session Summary

### Step 1: Sync
- **0 new feature branches** merged into main
- **1 upstream merge**: ksm-v2 (33 commits)
- **0 reverse-syncs** needed this session
- **6 submodules committed**: ksm-v2, fwber, hyperharness, pi-mono, picard, tabby

### Step 2: Analysis
- **hyperharness** actively developing control plane (detector.go) and TUI (dashboard, slash, tree browser)
- **pi-mono** removed pi-go binary, refactored cmd/pi/main.go
- **picard** cleaned up discography_webapp (removed -5027 lines of Python/Rust code)
- **tabby** wails app frontend expanding with patch_features.py
- **ksm-v2** upstream remains very active (33 more commits)

### Step 3-4: Documentation
- CHANGELOG.md updated for v3.47.0
- SUBMODULES.md from v3.45.0 still current (71 submodules)

### Step 5: Version
- 3.46.0 → 3.47.0

### Step 6: Commit & Push
- ✅ Pushed to origin/main

### Step 7: Build Verification
- Pending (recommended: jules-autopilot vite build)

## Key Observations
1. **picard** removed discography_webapp — likely moved to standalone or different service
2. **hyperharness** added controlplane/detector.go — new monitoring capability
3. **pi-mono** cleaned up pi-go binary (was tracked in git, now removed)
4. **ksm-v2** kson upstream_develop keeps needing merge — upstream is very active
5. **bobbybookmarks** feature branches still 4 ahead of main (reverse-sync already done)

## Known Issues (Unchanged)
1. **bobfilez**: pybind11 directory recursion causes git operations to hang
2. **bg/okgame**: Build artifacts not properly gitignored
3. **borg**: Committing lancedb binary data — should be gitignored
4. **topaz-ffmpeg**: master branch diverged from upstream

## Recommendations
1. Add `.gitignore` in borg for: `data/lancedb/`, `metamcp.db-shm`, `bin/borg.exe~`
2. Consider whether picard discography_webapp was intentionally removed or should be restored
3. ksm-v2 upstream merge needs to be done each session — consider automating
4. pi-mono pi-go binary should not have been tracked — verify .gitignore covers it
