# Workspace Handoff — v3.66.0

**Date**: 2026-05-20
**Version**: 3.66.0
**Commit**: b5fc36ffb

## Session Summary (covering v3.65.0 + v3.66.0)

### Step 1: Sync
- **0 feature branches merged into main** (no ahead-of-main branches)
- **2 upstream merges**: ksm-v2 (34), openclaw-config (1)
- **9 reverse-syncs**: openclaw-config (3), bobtorrent (2), jules-autopilot (2), tabby (2)
- **11 submodules committed**: auto_dj_script, hymnmania, ksm-v2, borg, bobtorrent, jules-autopilot, planet_fitness_stepmaniax_agent, slsk
- **12 submodule pointers updated**

### Step 2: Analysis
- **borg** had a massive update (+3,455/-2,252 lines) — dashboard refactoring, new toon.go module
- **auto_dj_script** got 3 Jules commits + new `.pi/` AI framework directory
- **bobmani/hymnmania** also got `.pi/` AI framework files — new pattern
- **`.pi/` directories** are a new AI tool framework appearing in repos (similar to `.jules/`)
  - Contains: agents/supervisor.md, memory-blocks/agent.md, memory-blocks/user.md, taskplane.json
- **planet_fitness_stepmaniax_agent** keeps re-tracking .jules/sessions/ — needs permanent fix
- **openclaw-config** upstream divergence resolved (now 113 vs 0 after 1 commit merge)
- **tabby/jules** divergence still 63 vs 25

### Steps 3-5: Documentation & Version
- CHANGELOG.md updated for v3.65.0 + v3.66.0
- Version: 3.64.0 → 3.66.0

### Step 6: Commit & Push
- ✅ Pushed to origin/main

### Step 7: Build
- Pending

## Key Observations
1. **New `.pi/` AI framework** appearing in auto_dj_script and hymnmania — different from .jules/
2. **borg** is very active — massive dashboard refactor (+3,455/-2,252 lines)
3. **planet_fitness_stepmaniax_agent** keeps re-tracking .jules/sessions/ — the .gitignore isn't being respected during Jules runs
4. **openclaw-config** upstream now just 1 commit behind (was 3)
5. **auto_dj_script** got DSP improvements (autodj/dsp.py +21 lines)

## Known Issues
1. **bobfilez**: pybind11 directory recursion — skipped
2. **bg**: Skipped due to submodule merge complexity
3. **tabby/jules-15161538455472121726**: Diverged 63 vs 25 — worsening
4. **topaz-ffmpeg/master**: Diverged from upstream
5. **planet_fitness_stepmaniax_agent**: .jules/sessions/ keeps getting re-tracked — Jules overwrites .gitignore?
6. **.pi/ directories**: New AI tool pattern — need to decide if these should be gitignored like .jules/sessions/

## Recommendations
1. Add `.pi/tasks/` and `.pi/memory-blocks/` to .gitignore (keep `.pi/agents/` tracked as they're config)
2. Investigate why planet_fitness_stepmaniax_agent keeps re-tracking .jules/sessions/
3. Consider gitignoring `.pi/` entirely similar to `.jules/sessions/` if these are ephemeral
4. borg dashboard refactoring is significant — worth testing
5. tabby/jules divergence needs manual intervention (63 vs 25)
