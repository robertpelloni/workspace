# Workspace Handoff — v3.59.0

**Date**: 2026-05-19
**Version**: 3.59.0
**Commit**: 6ff753ae2

## Session Summary

### Step 1: Sync
- **0 feature branches merged into main**
- **1 upstream merge**: ksm-v2 (34)
- **0 reverse-syncs**
- **4 submodules committed**: bobbybookmarks, ksm-v2, jules-autopilot, onetool-mcp

### Step 2: Analysis
- **bobbybookmarks** continuing AI tooling development — _harness_report.py, _list_harness_tools.py
- **jules-autopilot** now has .exe~ in .gitignore — stops tracking the large backend binary
- **onetool-mcp** got Jules session files (+506) — .jules/memory/ and .jules/sessions/
- **pi-mono, tabby, hyperharness** all clean — quiet session
- Script timed out during topaz-ffmpeg upstream fetch — large repo slow to fetch

### Steps 3-5: Documentation & Version
- CHANGELOG.md updated for v3.59.0
- Version: 3.58.0 → 3.59.0

### Step 6: Commit & Push
- ✅ Pushed to origin/main

### Step 7: Build
- Pending

## Key Observations
1. **jules-autopilot** .exe~ binary was being tracked — now gitignored (good cleanup)
2. **bobbybookmarks** building out AI harness tooling
3. **onetool-mcp** accumulating Jules session files (similar to fwber earlier)
4. Several repos are now consistently clean between sessions — stabilization working
5. topaz-ffmpeg upstream fetch is very slow — may need to increase timeout

## Known Issues
1. **bobfilez**: pybind11 directory recursion (mitigated with .gitignore)
2. **bg/okgame**: Build artifacts not gitignored
3. **borg**: Still committing metamcp.db binary periodically
4. **tabby/jules**: Branch diverged (59 vs 25)
5. **topaz-ffmpeg/master**: Diverged from upstream (601 vs 1)
6. **topaz-ffmpeg**: Upstream fetch causes timeout — need longer timeout

## Recommendations
1. Increase timeout for topaz-ffmpeg upstream fetch to 300s
2. Add .gitignore for onetool-mcp .jules/sessions/ (very large)
3. jules-autopilot .exe~ fix is good — consider similar for other repos with binaries
