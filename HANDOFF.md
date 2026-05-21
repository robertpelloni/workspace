# Workspace Handoff — v3.75.0

**Date**: 2026-05-21
**Version**: 3.75.0
**Commit**: 4c896eda4

## Session Summary

### Step 1: Sync
- **0 feature branches merged into main** (all already merged)
- **1 upstream merge**: ksm-v2 (34)
- **2 reverse-syncs**: bobeditpro feature branches (3 each)
- **4 submodules committed**: auto_dj_script, hymnmania, ksm-v2, slsk
- **3 submodule pointers updated**
- **4 stale PRs closed** on GitHub

### Step 2: Analysis
- **hymnmania**: NEW edge_extractor.py (+93/-4) — audio feature extraction pipeline
- **auto_dj_script**: Continued DSP refinement — core.py + dsp.py (+83/-25)
- **hymnmania Udio API**: Still being actively refined
- **slsk**: Minor fix (+1)
- **Stale PR cleanup**: 4 PRs that were manually merged now properly closed on GitHub

### Steps 3-5: Documentation & Version
- CHANGELOG.md updated for v3.75.0
- Version: 3.74.0 → 3.75.0

### Step 6: Commit & Push
- ✅ Pushed to origin/main

### Step 7: Build
- Pending

## Key Observations
1. **hymnmania edge_extractor.py** — new audio feature extraction, likely for music analysis
2. **auto_dj_script** continues very active DSP development — 4th consecutive session with changes
3. **ksm-v2** 34 upstream commits is a consistent recurring pattern
4. **Stale PR cleanup** — good hygiene, prevents confusion about what's merged
5. **Very quiet session** — most repos clean and stable

## Known Issues
1. **bobfilez**: pybind11 directory recursion — skipped
2. **bg**: Skipped due to submodule merge complexity
3. **tabby/jules-15161538455472121726**: Diverged 68 vs 25 — still unresolved
4. **topaz-ffmpeg/master**: Diverged from upstream
5. **openclaw-config**: 115 commits ahead of upstream
6. **borg**: 170 open dependabot PRs — deferred

## Recommendations
1. hymnmania edge_extractor.py should be tested with real audio
2. auto_dj_script DSP changes need validation with real DJ sets
3. Consider closing more stale PRs across the workspace
4. Workspace is very stable — can focus on feature testing
