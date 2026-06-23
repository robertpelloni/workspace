# main

**Purpose:** Main project memory branch

## Commit 2026-06-23 — Executive Protocol #27 (v5.39.0)

**Branch Purpose:** Main project memory — tracks all executive sync protocols, submodule health, and feature branch reconciliation.

**Previous Progress Summary:** Protocols #12-#26 established the dual-direction merge pattern: forward-merge useful feature branches into main, reverse-merge main into branches not yet ready. Submodule fix passes resolved ~50+ stale gitlink pins across bg, bobsgameonlinejava, geany, bcs chains. 14 new submodules registered in v5.35.0. Duplicate TormentNexus/tormentnexus consolidated. Maestro gitlinks repaired in v5.38.0.

**This Commit's Contribution:**

- **enterprise_sales_bot stash resolved** — `git stash pop` caused 3 conflicting files (hypernexus_site/index.html, tormentnexus_site/index.html, .memory/state.yaml). Resolved by accepting stash version (1494 lines vs 925 HEAD — newer comprehensive rewrite). Dropped stale stash. Committed as `558b1a7`.
- **hymnmania OAuth secret scrub** — Google Client ID `407494756283-...` and Secret `GOCSPX--...` found in `.memory/branches/main/log.md` from earlier agent sessions. Used `sed` to replace with `[REDACTED]`, `git commit --amend`, `git push --force-with-lease`. Also tracked classical_midis.db, YouTube OAuth code, video generator.
- **jules-autopilot forward-merged** — Branch `jules-4852916069977232082-be6d9c55` (3 commits ahead of main: session cache fix, UNDER CONSTRUCTION banners). Fast-forward merged into main via `git merge`, pushed.
- **projectM-upstream .gitignore** — Added `build_msvc/` to .gitignore for local MSVC build artifacts. Kept as local-only change (tracks upstream repo).
- **Submodule sync** — ArrowVortex, Maestro, MilkDrop3 updated to latest tracking commits via `git submodule update --remote --recursive`.
- **Version v5.38.0 → v5.39.0** — Updated VERSION, VERSION.md, start.bat, build.bat, CHANGELOG.md, ROADMAP.md, HANDOFF.md.
- **Build verification** — All 5 Go binaries built: tormentnexus.exe (20.6MB), hyperharness.exe (26.7MB), pi-mono.exe (17.5MB), tabby-backend.exe (9.5MB), tabby-native.exe (2.9MB). Binaries preserved.
- **Root commit**: `69b3159fff` pushed to origin/main.
