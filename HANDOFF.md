# Workspace Handoff — v3.98.0

**Date**: 2026-05-25
**Version**: 3.98.0
**Commit**: pending

## Session Summary

### STEP 1: Upstream Tracking & Submodule Sanitization
- **Root fetch**: ✅ Completed
- **Submodule fetch**: 84/90 direct; bobui + borg (tag force); element-web (targeted develop); fwber (main only); bobfilez + bobsgameweb (separate)
- **Upstream merges**: 1 — topaz-ffmpeg (13 upstream/master commits)
  - Vulkan FFV1 rangecoder encoding fix
  - mjpegdec bayer width handling simplification
  - vorbisdsp inverse coupling fix (cmpleps → cmpltps)
  - swscale packed30togbra10/gbr16ptopacked30 fix for GBRP 10/12 bit MSB
  - liboapvenc APV profile derivation and validation
- **Submodule updates**: All 90 reset to origin/HEAD (clean working directories)
- **Note**: Step 1.3's `git reset --hard origin/$db` undid the initial upstream merge.
  The merge was re-applied in Step 2 and pushed successfully.

### STEP 2: Dual-Direction Intelligent Merge Engine
- **Forward merges**: 0 (all branches fully contained)
- **Reverse merges**: 0 (no active branches with unique content)
- **Local branches deleted**: 28 (across 17 repos)
- **Remote branches deleted**: 114 (across 25+ repos)
- **Total branch cleanup**: 142 branches

**Key remote branch cleanups**:
- Maestro: 5 branches (borg-assimilation, cue-polish, 2 fix branches, rc)
- bobgui: 8 branches (GTK bugfix branches from upstream)
- bobmani/*: 10 branches (arrowvortex, beatoraja, bobmania, hymnmania, itgmania, ksm-v2, linthesia, pianogame)
- openclaw-config: 8 branches (feat branches, budget-guard, claude-code-skill)
- topaz-ffmpeg: 8 branches (8.0/linux-*, feature/astra, feature/oiio3, feature/ort)
- pi-mono: 4 branches (badlogic-main, feat/plannotator, 2 jules branches)

### STEP 3: Workspace Cleanup & Build
- Scripts: start.bat ✅, build_all.bat ✅
- Version: 3.97.0 → 3.98.0
- Submodule pointers: 90 updated
- Pushed: topaz-ffmpeg (topaz/develop + master)

## Pushed Repos
- topaz-ffmpeg (topaz/develop: e0f798e → 56c881a, master: 34f322d → fc1a89d)

## Known Issues
1. **bobfilez**: git operations hang (pybind11 nested recursion)
2. **bobsgameweb**: `git status` hangs on nested libs/lwjgl3
3. **element-web**: Only `git fetch origin develop` works
4. **fwber**: Orphan repo, 51 behind upstream — cannot merge upstream (would re-introduce secrets)
5. **borg**: upstream OhMyOpenCode/aios deleted (404)
6. **242 GitHub security vulnerabilities** (3 critical)
