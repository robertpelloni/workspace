# Workspace Handoff — v3.63.0

**Date**: 2026-05-20
**Version**: 3.63.0
**Commit**: 02c9448cd

## Session Summary

### Step 1: Sync
- **1 feature branch merged into main**: MarbleBlast/jules (with --allow-unrelated-histories)
- **2 upstream merges**: bobeditpro (26 Audacity upstream), ksm-v2 (34)
- **16 reverse-syncs**: across bobgui, bobtorrent, bobtrader, bobtrax, geany, hyperharness, neverball, npp, pi-mono, tabby
- **3 submodules committed**: bobsaver, native-fy, planet_fitness_stepmaniax_agent
- **5 submodule pointers updated**

### Step 2: Analysis
- **bobeditpro** got a big upstream merge (26 commits) — significant Audacity changes
- **Many feature branches were reverse-synced** — 16 branches caught up to main
- **MarbleBlast** jules branch had unrelated histories — resolved with --allow-unrelated-histories
- **bg** jules branch merge failed due to nested submodule conflicts — left on master
- **tabby/jules** still significantly diverged (61 vs 25) — reverse-sync only partially helps
- **bobsaver** got .gitignore and projectm pointer update committed
- **native-fy and planet_fitness_stepmaniax_agent** got Jules architecture.md updates

### Steps 3-5: Documentation & Version
- CHANGELOG.md updated for v3.63.0
- Version: 3.62.0 → 3.63.0

### Step 6: Commit & Push
- ✅ Pushed to origin/main

### Step 7: Build
- Pending

## Key Observations
1. **bobeditpro upstream merge (26)** — largest Audacity upstream sync in recent sessions
2. **16 reverse-syncs** — many feature branches are being kept up to date with main
3. **bg** is too complex for auto-merge due to nested submodules (okgame, bobsgameweb, bobsgameonlinejava)
4. **tabby/jules** divergence is severe (61 vs 25) — may need manual resolution eventually
5. **MarbleBlast** jules branch had unrelated histories — resolved by allowing, then cleaning up

## Known Issues
1. **bobfilez**: pybind11 directory recursion — still needs targeted git add approach
2. **bg/okgame**: Build artifacts not gitignored
3. **bg/jules-1394303886104622315**: Merge failed (nested submodule conflicts) — needs manual resolution
4. **tabby/jules-15161538455472121726**: Severely diverged (61 vs 25) — needs manual intervention
5. **topaz-ffmpeg/master**: Diverged from upstream
6. **npp** has bobui and btk as uncommitted submodule pointer changes (recursive submodule issue)

## Recommendations
1. bg jules branch needs manual submodule resolution — this is a known complex case
2. tabby jules divergence is growing — consider force-resetting the branch to master + reapplying
3. bobeditpro upstream sync is healthy — keep monitoring for breaking changes
4. npp's bobui/btk submodule pointers are changing frequently — this is a nested submodule pattern
