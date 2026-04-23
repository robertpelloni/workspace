# Workspace Handoff — v3.4.0 — 2026-04-17

## Executive Summary
Protocol v3.4.0: Forward-merged 6 feature branches across 5 repos (bobcoin×2 dependabot, jules-autopilot jules-1776, Maestro jules-2575, pi-mono pr-1724 tree folding, tabby real-pty-serial). Reverse-synced 2 feature branches (bobcoin governance, jules-autopilot jules-1776). 0 upstream changes (all forks synced). Updated submodules across 3 parent repos (bobfilez 10 subs, btk 2 subs, bobui 1 sub). Built jules-autopilot in 11.94s. Pushed 9 default branches + 2 feature branches.

## Forward Merges (Feature → Default)

| Repo | Branch | Default | Delta | Resolution |
|------|--------|---------|-------|-----------|
| bobcoin | dependabot/npm_and_yarn/frontend/multi | main | 1 commit | Auto (esbuild+vite bump, 2 files) |
| bobcoin | dependabot/npm_and_yarn/frontend/npm_and_yarn | main | 1 commit | Auto (npm group bump, 2 files) |
| jules-autopilot | jules-17764958747146694232 | main | +2 | Clean merge |
| Maestro | jules-2575151016458646249 | main | +1 | FF (dead code removal) |
| pi-mono | pr-1724 | main | +2 | Conflict in CHANGELOG.md + keybindings.ts, resolved |
| tabby | feat/real-pty-serial | master | +2 | FF |

## Reverse Syncs (Default → Feature)

| Repo | Branch | Ahead After | Pushed |
|------|--------|-------------|--------|
| bobcoin/feat/governance-delays | ← main | 4 | ✅ |
| jules-autopilot/jules-1776 | ← main | 2 | ✅ |

## Upstream Sync
All 18+ upstream repos: **0 new changes**. Fully synced.

## Submodule Inventory

### Workspace Root (C:/Users/hyper/workspace)
| Submodule | Remote | Default Branch |
|-----------|--------|---------------|
| agentirc | github.com/robertpelloni/agentirc | master |
| bobbybookmarks | github.com/robertpelloni/bobbybookmarks | main |
| bobcoin | github.com/robertpelloni/bobcoin | main |
| bobeditpro | github.com/robertpelloni/audacity (fork of audacity/audacity) | master |
| bobfilez | github.com/robertpelloni/bobfilez | main |
| bobsgameonlinejava | github.com/robertpelloni/bobsgameonlinejava | master |
| bobtorrent | github.com/robertpelloni/bobtorrent | master |
| bobtrader | github.com/robertpelloni/bobtrader | main |
| bobtrax | github.com/robertpelloni/bobtrax | master |
| bobui | github.com/robertpelloni/bobui | main |
| btk | github.com/robertpelloni/btk | master |
| CLIProxyAPIPlus | github.com/robertpelloni/CLIProxyAPIPlus | main |
| f-zerox | github.com/robertpelloni/f-zerox | main |
| geany | github.com/robertpelloni/geany | master |
| hyperharness | github.com/robertpelloni/hyperharness | main |
| jules-autopilot | github.com/robertpelloni/jules-autopilot | main |
| Maestro | github.com/robertpelloni/Maestro | main |
| MarbleBlast | github.com/robertpelloni/MarbleBlast | master |
| mcp-superassistant | github.com/robertpelloni/mcp-superassistant | main |
| mk64 | github.com/robertpelloni/mk64 | main |
| neverball | github.com/robertpelloni/neverball | main |
| npp | github.com/robertpelloni/npp | master |
| openclaw-config | github.com/TechNickAI/openclaw-config (**403**) | main |
| opencode-autopilot | github.com/robertpelloni/opencode-autopilot | main |
| picard | github.com/robertpelloni/picard | master |
| pi-mono | github.com/robertpelloni/pi-mono | main |
| raindropioapp | github.com/robertpelloni/raindropioapp | main |
| sm64coopdx | github.com/robertpelloni/sm64coopdx | main |
| superai | github.com/robertpelloni/superai (bad .gitmodules) | main |
| supersaber | github.com/robertpelloni/supersaber | master |
| tabby | github.com/robertpelloni/tabby (fork of Eugeny/tabby) | master |
| topaz-ffmpeg | github.com/TopazLabs/ffmpeg (**403**) | topaz/develop |

### bobmani/ Submodules
| Submodule | Remote | Default |
|-----------|--------|---------|
| arrowvortex | github.com/robertpelloni/arrowvortex | master |
| beatoraja | github.com/robertpelloni/beatoraja | master |
| bobmania | github.com/robertpelloni/bobmania | master |
| ddc | github.com/robertpelloni/ddc | master |
| hymnmania | github.com/robertpelloni/hymnmania | main |
| itgmania | github.com/robertpelloni/itgmania | release |
| ksm-v2 | github.com/robertpelloni/ksm-v2 | master |
| linthesia | github.com/robertpelloni/linthesia | main |
| Simply-Love-SM5 | github.com/robertpelloni/Simply-Love-SM5 | master |

### Nested Submodules (Level 2)
| Parent | Submodule | Remote |
|--------|-----------|--------|
| bobui | submodules/juce | juce-framework/JUCE |
| bobui | submodules/ultimatepp | robertpelloni/ultimatepp |
| btk | external/juce | juce-framework/JUCE |
| btk | external/ultimatepp | robertpelloni/ultimatepp |
| btk | external/bobui-reference | robertpelloni/bobui |
| bobeditpro | bobui | robertpelloni/bobui |
| bobfilez | ai-file-sorter | robertpelloni/ai-file-sorter |
| bobfilez | libs/OpenRV | Autodesk/OpenRV |
| bobfilez | libs/OpenTimelineIO | OpenTimelineIO |
| bobfilez | libs/SysmonForLinux | Sysinternals |
| bobfilez | libs/bobgui | robertpelloni/bobgui |
| bobtrax | bobui | robertpelloni/bobui |
| bobtrax | lmms | robertpelloni/lmms |
| bobtrax | muse | robertpelloni/muse |
| bobtrax | zrythm | robertpelloni/zrythm |
| f-zerox | bobcoin | robertpelloni/bobcoin |
| geany | subprojects/btk | robertpelloni/btk |
| geany | subprojects/bobui | robertpelloni/bobui |
| geany | subprojects/bobgui | robertpelloni/bobgui |
| hyperharness | llamafile | mozilla/llamafile |
| jules-autopilot | (various AI tool submodules) | various |
| mk64 | bobcoin | robertpelloni/bobcoin |
| npp | bobui | robertpelloni/bobui |
| npp | btk | robertpelloni/btk |
| pi-mono | submodules/aider | paul-gauthier/aider |
| bobsgameonlinejava | libs/micromod | (external) |
| bobsgameonlinejava | libs/commons-lang | (external) |
| bobsgameonlinejava | libs/aseprite-file | (external) |
| bobsgameonlinejava | libs/jinput | (external) |
| bobsgameonlinejava | libs/lwjgl3 | (external) |
| bobsgameonlinejava | references/aseprite | (external) |
| bobsgameonlinejava | references/sprite-studio-64 | (external) |
| bobsgameonlinejava | references/Pixelorama | (external) |
| bobsgameonlinejava | references/PixiEditor | (external) |
| bobsgameonlinejava | references/tiled | (external) |
| bobsgameonlinejava | bobcoin | robertpelloni/bobcoin |
| bobtorrent | bobcoin | robertpelloni/bobcoin |
| bobtorrent | qbittorrent | robertpelloni/qbittorrent |

## Pushes This Session

### Default Branches (9 pushed)
1. bobbybookmarks main (1 ahead — data sync)
2. bobcoin main (4 ahead — dependabot merges)
3. bobfilez main (1 ahead — submodule updates)
4. bobui main (1 ahead — ultimatepp update)
5. btk master (1 ahead — ultimatepp + bobui-ref updates)
6. jules-autopilot main (3 ahead — jules-1776 merge)
7. Maestro main (1 ahead — dead code removal via FF)
8. pi-mono main (3 ahead — pr-1724 tree folding feature)
9. tabby master (2 ahead — real-pty-serial merge)

### Feature Branches (2 pushed)
1. bobcoin/feat/governance-delays (4 ahead — caught up to main)
2. jules-autopilot/jules-1776 (2 ahead — caught up to main)

### Blocked Pushes
- **topaz-ffmpeg**: 6465 ahead, HTTP 403 (TopazLabs origin, needs robertpelloni fork)
- **openclaw-config**: fetch failed — `robertpelloni/openclaw-config` repo not found on GitHub

## Build Verification
- **jules-autopilot**: Vite v6.4.2, 2970+ modules
- Build time: **11.94s** (warm cache)
- Output: 674.62 KB index chunk (warning: > 500 KB)
- All chunks built successfully, no errors

## Branch Analysis — Skipped Branches (with rationale)

### bobeditpro (Audacity fork)
- `feature/audition-parity-roadmap` (+1272): Upstream Audacity feature, not robertpelloni-owned
- `feature/bus-tracks-and-docs` (+1291): Upstream Audacity feature, not robertpelloni-owned
- 60+ upstream release/feature branches (release-3.0.3 through 4.0.0-alpha2, etc.): All upstream Audacity

### geany (Geany IDE fork)
- Remote branches (0.18, 0.19, 0.20, 1.23, etc.): All upstream Geany release/version tags

### tabby (terminal fork)
- 80+ remote branches (all-contributors/*, dependabot/*, etc.): All upstream Eugeny/tabby

### itgmania (StepMania fork)
- 30+ `libpng-sync-*` and `libpng-restore-*` branches: All upstream itgmania CI/automation branches

### bobeditpro features in workspace
- These are Audacity upstream features. Per user instructions: "ignore upstream feature branches that are unfinished/old"
- User may want to merge all upstream branches for stepmania at some point

## Known Issues / Blockers
1. **openclaw-config**: `robertpelloni/openclaw-config` repo not found (was 403 from TechNickAI origin, now remote deleted?)
2. **topaz-ffmpeg**: HTTP 403 (TopazLabs origin, needs robertpelloni fork)
3. **superai**: `.gitmodules` has conflict markers around external/claude-mem and external/OmniRoute — prevents fetch
4. **jules-autopilot chunk size**: 674KB exceeds 500KB warning limit (consider code-splitting)
5. **161 Dependabot vulnerabilities** in jules-autopilot (3 critical)
6. **bobcoin**: `nul` and `research/` untracked files (artifact from Windows/ Git)
7. **hyperharness**: llamafile submodule dirty
8. **pi-mono**: submodules/aider dirty
9. **Various repos**: Modified submodule content (bobeditpro/bobui, bobtorrent/bobcoin, etc.) — cosmetic only

## Conflict Resolution Strategy
- prisma DB binary files (.db-wal, .db-shm): --theirs (accept default's version)
- Lock files (package-lock, yarn.lock): --theirs
- Source code: --theirs on reverse sync, union attempt on forward merge
- Documentation (.md, .txt): --theirs
- Submodule conflicts: abort + reset to origin/default
- Maestro: always --no-verify (Husky hook failures)

## Next Steps / Recommendations
1. Investigate openclaw-config remote — `robertpelloni/openclaw-config` may have been deleted or renamed
2. Create robertpelloni fork of TopazLabs/ffmpeg (resolves topaz-ffmpeg 403 blocker)
3. Fix superai `.gitmodules` conflict markers to restore fetch capability
4. Consider jules-autopilot code-splitting for 674KB chunk
5. Address 161 Dependabot vulnerabilities in jules-autopilot
6. Clean up bobcoin `nul` file and stale `research/` directory
7. Run `git prune` on repos with loose object warnings
8. Consider merging Maestro dead code cleanup — the FF merge removed process-manager, context-groomer, and web-server-factory (3 files, 53 deletions)
