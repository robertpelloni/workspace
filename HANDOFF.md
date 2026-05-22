# Workspace Handoff — v3.90.0

**Date**: 2026-05-22
**Version**: 3.90.0
**Commit**: pending

## Session Summary

### STEP 1: Upstream Tracking & Submodule Sanitization
- **66 repos fetched** (excluded: topaz-ffmpeg, bobfilez, bg, Maestro)
- **1 upstream merge**: ksm-v2 (34 commits, recurring)
- All repos up to date

### STEP 2: Dual-Direction Intelligent Merge Engine
- **0 forward merges**
- **3 reverse merges**:
  - hymnmania `feat/comprehensive-docs-and-tts-params` (2 commits behind → current)
  - hymnmania `feature/web-ui-and-parallelization` (2 commits behind → current)
  - jules-autopilot `jules-17764958747146694232-3d7c3856` (2 commits behind → current)
- **3 repos with uncommitted changes** auto-committed:
  - auto_dj_script, borg, ksm-v2

### STEP 3: Submodule Pointer Updates (4)
| Submodule | Old | New | Delta |
|-----------|-----|-----|-------|
| auto_dj_script | `aae84db` | `dd16635` | +14/-19 (core refactor) |
| bobmani/hymnmania | `014dd16` | `4337b20` | reverse merge catch-up |
| borg | `64aeb33` | `a0be1fd` | +55/-20 (SessionImport, LanceDB) |
| jules-autopilot | `d5ca77e` | `9e6f9bc` | reverse merge catch-up |

### borg → hypercode Migration Status
- **Project name: hypercode** (confirmed by user)
- Migration still in progress — some files will merge wrong until complete
- v3.88.0: Full borg→hypercode rename (1249 files)
- v3.89.0: Partial revert `memoryRouter.hypercode.ts` → `memoryRouter.borg.ts`
- v3.90.0: No naming changes this session — LanceDB + SessionImport focus
- Remaining: Need to complete full rename pass and prevent upstream reverts

## Known Issues
1. **bobfilez**: pybind11 infinite directory recursion — skipped
2. **bg**: Submodule merge complexity — skipped
3. **Maestro**: git operations timeout — skipped
4. **topaz-ffmpeg**: Diverged from upstream — skipped
5. **borg/hypercode**: Migration incomplete — some files still reference borg, upstream may reintroduce old names
6. **tabby/jules**: Diverged branches — unresolved
7. **openclaw-config**: 115 commits ahead of upstream
8. **236 GitHub security vulnerabilities**

## Recommendations
1. **borg/hypercode**: Complete the migration — do a full audit for remaining "borg" references
2. **borg/hypercode**: Watch for upstream merges that revert hypercode→borg renames
3. **jules-autopilot**: `jules-17764958747146694232` branch is current — evaluate for forward merge
4. **auto_dj_script**: Still refactoring — hold release tag until stable
5. **hymnmania**: Feature branches consistently caught up — evaluate for forward merge
