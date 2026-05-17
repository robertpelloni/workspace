# Workspace Handoff — v3.49.0

**Date**: 2026-05-16
**Version**: 3.49.0
**Commit**: 33fbce7bd

## Session Summary

### Step 1: Sync
- **0 new feature branches** merged into main
- **1 upstream merge**: ksm-v2 (33 commits — consistent daily upstream activity)
- **6 reverse-syncs**: bobbybookmarks (3), tabby (2), topaz-ffmpeg (1)
- **3 submodules committed**: ksm-v2, hyperharness, pi-mono

### Step 2: Analysis
- **hyperharness** rapidly expanding TUI: new commands.go, entries.go, renderer.go, theme.go modules (+943/-678 lines)
- **pi-mono** very active: 8 new Go packages in one session (+1351 lines) — bashexecutor, childprocess, cli/args, imageresize, mime, pathsutil, sdk, sleeputil
- **ksm-v2** consistently gets 33 upstream commits every session — upstream is very active
- **tabby** jules branch diverged (17 vs 25 commits) — may need manual resolution

### Step 3-4: Documentation
- CHANGELOG.md updated for v3.49.0

### Step 5: Version
- 3.48.0 → 3.49.0

### Step 6: Commit & Push
- ✅ Pushed to origin/main

### Step 7: Build
- Pending

## Key Observations
1. **pi-mono** is the most actively developed submodule — averaging 8-12 new Go packages per session
2. **hyperharness** TUI is being refactored into modular components (commands, entries, renderer, theme)
3. **ksm-v2** gets 33 upstream commits every session — consider if this is a permanent pattern
4. **tabby/jules** branch has diverged (17 vs 25) — will need manual resolution eventually
5. **topaz-ffmpeg/master** continues to diverge from upstream (594 vs 14)

## Known Issues (Unchanged)
1. **bobfilez**: pybind11 directory recursion causes git operations to hang
2. **bg/okgame**: Build artifacts not properly gitignored
3. **borg**: Committing lancedb binary data — should be gitignored
4. **tabby/jules**: Branch diverged from origin

## Recommendations
1. Add `.gitignore` entries across repos for binary files (atlas.db, metamcp.db, lancedb/)
2. Consider automating ksm-v2 upstream merge since it happens every session
3. Tabby jules branch needs manual conflict resolution
