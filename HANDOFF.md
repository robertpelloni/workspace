# Workspace Sync Protocol v3.8.0 — HANDOFF

**Date**: 2026-04-26  
**Protocol Version**: 3.8.0  
**Previous Version**: 3.7.0  

## Session Summary

### What Was Done
1. **Fetched** all 53+ repos across workspace and bobmani/ subdirectories
2. **Discovered** 67+ local feature branches + 3 new remote-only branches
3. **Forward-merged** 5 feature branches into their defaults (bobsgameonlinejava×3, bg, bobmani/itgmania massive merge)
4. **Upstream synced** 3 repos: topaz-ffmpeg (+6 FFmpeg), bobmani/ksm-v2 (+2, resolved 2 conflicts), bobmani/arrowvortex (+1, resolved README conflict)
5. **Pulled** fwber +47 commits (major feature update)
6. **Reverse-synced** all behind feature branches (bobmani/ksm-v2 ×2 branches, bobmani/itgmania all branches)
7. **Updated submodules** across all repos (3 repos had changes: bobtrax, bobmani/bobmania, bobmani/ksm-v2)
8. **Committed** and **pushed** 12 default branches + 16 feature branches
9. **Verified** jules-autopilot build: 390KB index, **11.82s** (fastest ever!)
10. **Updated** VERSION 3.8.0, CHANGELOG, HANDOFF

### Forward Merges This Session

| Repo | Branch | Commits | Default | Result |
|------|--------|---------|---------|--------|
| bobsgameonlinejava | jules-8356211922684761209 | +12 | main | ✅ Clean (AI project analysis, new submodules) |
| bobsgameonlinejava | fix-build-and-backport-* | +1 | main | ✅ Clean (reverse sync cleanup) |
| bobsgameonlinejava | modernize-codebase-final | +1 | main | ✅ Clean (reverse sync cleanup) |
| bg | jules-1394303886104622315 | +5 | master | ✅ Clean (AI memory commits) |
| bobmani/itgmania | main→release | +240 | release | ✅ Massive upstream StepMania sync |

### Upstream Syncs

| Repo | Source | Commits | Conflicts | Resolution |
|------|--------|---------|-----------|------------|
| topaz-ffmpeg | FFmpeg master | +6 | None | Clean merge |
| bobmani/ksm-v2 | kshootmania develop | +2 | ResultScene.cpp, NocoUI sub | Took upstream (NocoUI Int params) |
| bobmani/arrowvortex | uvcat7 release | +1 | README.md | Kept both (Linux build + nightly) |

### Push Results

#### Default Branches (12 pushed, 3 blocked)
| Repo | Status | Commits |
|------|--------|---------|
| bg | ✅ pushed | +6 |
| bobbybookmarks | ✅ pushed | +1 |
| bobsgameonlinejava | ✅ pushed | +16 |
| bobtrax | ✅ pushed | +1 |
| topaz-ffmpeg | ✅ pushed | +7 |
| bobmani/arrowvortex | ✅ pushed | +2 |
| bobmani/beatoraja | ✅ pushed | +1 |
| bobmani/ksm-v2 | ✅ pushed | develop (new!) |
| antigravity-cli | ❌ 403 | krmslmz org |
| computer-use-preview | ❌ 403 | google-gemini org |
| superai | ⏳ timeout | 1968 commits, 1GB+ pack |

#### Feature Branches (16 pushed)
antigravity-autopilot/release/5.1.1(+2), bobgui/master(+2479), bobsgameonlinejava/fix-build(+16), bobsgameonlinejava/modernize(+16), hyperharness/deep-wire(+1), jules-autopilot/hypercode-sync(+10), jules-autopilot/jules-17764958(+3), MarbleBlast/main(+1), npp/disable-autocomplete(+1), npp/jules-36468(+1), OpenMBU/master(+1), topaz-ffmpeg/master(+14), bobmani/arrowvortex/main(+1), bobmani/itgmania/main(+240), bobmani/ksm-v2/configurable-songs(+5)

### Build Status
- **jules-autopilot**: ✅ 390KB index, **11.82s build** (fastest recorded!)
  - Vite v6.4.2, 3016 modules
  - Code-split with React.lazy() for 10 view components
  - Warning: empty vendor-react chunk (cosmetic, from v3.4.0 code-split)

### Known Blockers (Unchanged since v3.4.0)
1. **antigravity-cli**: 403 from krmslmz org → Fix: fork to robertpelloni
2. **computer-use-preview**: 403 from google-gemini → Third-party, read-only
3. **superai**: 1968 commits ahead, 1GB+ pack → Needs SSH or GitHub API

### Persistent Submodule Issues (Non-blocking)
- antigravity-autopilot: AntigravityMobile refs error
- bg: bobsgameweb clone failure (directory exists)
- bobfilez: libs/image-hash remote branch missing
- bobmani/arrowvortex: lib/ddc clone failure (directory exists)
- bobmani/beatoraja: index merge state / bad .gitmodules line 7
- hypercode: bad config line 101 in .gitmodules (via borg worktree)
- superai: bad config line 101 in .gitmodules, archive/litellm revision missing

### Notable Events This Session
- **borg/cloud-orchestrator-sync**: Discovered new remote branch (+3 commits, cloud orchestrator + prompt library features). Merge blocked by hypercode worktree lock issues. Recommend handling separately when borg/hypercode worktree is stable.
- **bobgui/master**: Finally pushed after accumulating +2479 commits since v2.x — was blocked due to rename from bobgui→master branch.
- **fwber**: Major pull of +47 commits (auto-save, PhotoEditor, LocationMatcher, profile page split for SSR fix).
- **bobmani/ksm-v2**: First ever develop branch push to origin — was only tracking master before.

---

## Submodule Inventory

### Repos with Submodules

| Repo | Submodule Count | Key Submodules |
|------|----------------|----------------|
| antigravity-autopilot | 11 | AUTO-ALL-AntiGravity, AntiBridge, AntigravityMobile, Claude-Autopilot |
| bg | 3 | bobsgameonlinejava (nested: 42 subs) |
| bobdesk | 3 | dictionaries, helpcontent2, translations |
| bobeditpro | 2 | bobui, muse_framework |
| bobfilez | 172 | FFmpeg, ImageMagick, opencv, openssl, zlib, libheif, libvips, calibre, hashcat, raylib, rapidjson, sqlite, and 160+ more |
| bobgui | 2 | bobui, btk |
| bobsaver | 6 | JWildfire, MilkDrop3, apophysis-j, electricsheep, geiss, projectm |
| bobsgameonlinejava | 46 | bobcoin, aseprite, LibreSprite, PixiEditor, Pixelorama, tiled, blockbench, defold, love2d, phaser, voidsprite, and 34 more |
| bobtorrent | 2 | bobcoin, qbittorrent |
| bobtrader | 44 | 30+ crypto trading bots and tools |
| bobtrax | 5 | ardour, bobui, muse, zynaddsubfx, reaper (nested: lmms with 20+ sub-subs) |
| bobui | 2 | juce, ultimatepp |
| borg/hypercode | 39 | Various MCP server submodules |
| btk | 3 | bobui-reference (nested: juce, ultimatepp), juce, ultimatepp |
| f-zerox | 5 | bobcoin, asm-differ, asm-processor, ido5.3_cc, splat |
| geany | 6 | bobgui, bobui (nested), btk (nested) |
| hyperharness | 41 | adrenaline, aider, claude-code, cursor-agent, gpt-engineer, llamafile, opencode |
| mk64 | 6 | bobcoin, doxygen-awesome-css, asm-differ, fast64, decomp-permuter, torch |
| npp | 4 | bobgui, bobui (nested), btk (nested), textfx |
| opencode-autopilot | 13 | Various coding agent submodules |
| pi-mono | 9 | aider, opencode-cli, and 7 more |
| superai | 33 | adrenaline, aider, claude-code, cursor-agent, litellm, and 28 more |
| tabby | 1 | (internal) |
| topaz-ffmpeg | 0 | (standalone FFmpeg fork, 561 commits ahead of upstream) |
| bobmani/arrowvortex | 2 | odcnn, libddc |
| bobmani/beatoraja | 1 | lr2oraja-endlessdream |
| bobmani/bobmania | 2 | Themes/Simply-Love-SM5, Themes/Simply Love |
| bobmani/ddc | 2 | ddc_onset, ffr-difficulty-model |
| bobmani/itgmania | 15 | ffmpeg, hidapi, libjpeg-turbo, libpng, libtomcrypt, libtommath, libusb, mbedtls (nested: framework, tf-psa-crypto), ogg, vorbis, zlib, bobcoin, Simply-Love-SM5, Simply Love |
| bobmani/ksm-v2 | 5 | CoTaskLib, NocoUI, ksmaxis, and 2 more |
| bobmani/linthesia | 1 | pianogame |

### Total Submodule Count: ~500+ across all repos

---

## Project Structure

```
C:/Users/hyper/workspace/
├── antigravity-autopilot/    (11 subs) - AI orchestration
├── antigravity-cli/          (403)     - CLI tool (krmslmz)
├── antigravity-jules-orchestration/ (uninit) - Jules orchestration
├── agentirc/                 - IRC bot
├── bg/                       (3 subs) - bob's game (massive, nested 42 subs)
├── bobbybookmarks/           - Bookmark manager
├── bobcoin/                  - Cryptocurrency
├── bobdesk/                  (3 subs) - LibreOffice fork
├── bobeditpro/               (2 subs) - Audacity fork (upstream: audacity/audacity)
├── bobfilez/                 (172 subs!) - File organizer
├── bobgui/                   (2 subs) - GUI framework
├── bobium/                   - IoT platform
├── bobsaver/                 (6 subs) - Screensaver engine
├── bobsgameonlinejava/       (46 subs) - Java game
├── bobtorrent/               (2 subs) - Torrent client (upstream: qbittorrent)
├── bobtrader/                (44 subs) - Crypto trading
├── bobtrax/                  (5 subs) - Music production (ardour, lmms, zrythm, muse, reaper)
├── bobui/                    (2 subs) - UI component library (juce, ultimatepp)
├── bobzilla/                 - Project tracker
├── bobzzite/                 - Website builder
├── borg/                     (39 subs) - hypercode worktree
├── btk/                      (3 subs) - Business toolkit
├── CLIProxyAPIPlus/          - CLI proxy
├── computer-use-preview/     (403) - Google Gemini (read-only)
├── dupeguru/                 - Duplicate file finder
├── f-zerox/                  (5 subs) - F-Zero X decompilation
├── frontend-sdl-cpp/         - SDL C++ frontend
├── fwber/                    - Personal site (auto-save, PhotoEditor)
├── geany/                    (6 subs) - Text editor fork
├── hyperharness/             (41 subs) - AI agent harness
├── jules-autopilot/          - Main app (Vite + React, 390KB code-split, 11.82s build)
├── Maestro/                  (7 feat) - AI orchestrator
├── MarbleBlast/              - Marble Blast mod
├── mcp-superassistant/       (1 sub) - MCP assistant
├── mk64/                     (6 subs) - Mario Kart 64 decompilation
├── neverball/                - Neverball fork
├── npp/                      (4 subs) - Notepad++ fork
├── onetool-mcp/              - MCP tool
├── OmniRoute/                (403, detached) - Third-party routing
├── openclaw-config/          - Config manager (forked from TechNickAI)
├── openclaw-dashboard/       - Dashboard UI
├── opencode-autopilot/       (13 subs) - Code autopilot
├── OpenMBU/                  - Marble Blast Ultra fork
├── picard/                   - MusicBrainz Picard fork
├── pi-mono/                  (9 subs) - Pi monorepo
├── raindropioapp/            - Raindrop.io app
├── sm64coopdx/               - SM64 co-op fork
├── superai/                  (33 subs, 1968 ahead) - AI super-agent
├── superpowers/              - Power tool suite
├── supersaber/               - Beat Saber mod
├── tabby/                    (1 sub) - Terminal emulator (upstream: Eugeny/tabby)
├── topaz-ffmpeg/             - FFmpeg fork (TopazLabs, 561 ahead of upstream)
├── VERSION                   - 3.8.0
├── CHANGELOG.md              - Full changelog
├── HANDOFF.md                - This file
├── bobmani/                  - Rhythm game subprojects
│   ├── arrowvortex/          (2 subs) - ArrowVortex fork (upstream: uvcat7)
│   ├── beatoraja/            (1 sub)  - Beatoraja fork
│   ├── bobmania/             (2 subs) - StepMania fork
│   ├── ddc/                  (2 subs) - DDC tools
│   ├── ddc_onset/            - DDC onset detection
│   ├── ffr-difficulty-model/ - FFR difficulty model
│   ├── hymnmania/            - Hymnmania
│   ├── itgmania/             (15 subs) - ITGmania fork
│   ├── ksm-v2/               (5 subs) - KSM v2 (upstream: kshootmania)
│   ├── leraine-studio/       - Leraine studio
│   ├── linthesia/            (1 sub)  - Linthesia fork
│   ├── pianogame/            - Piano game
│   └── Simply-Love-SM5/      - Simply Love theme
```

### Next Steps (Recommendations)
1. **Fork antigravity-cli** from krmslmz to robertpelloni (same pattern as openclaw-config)
2. **Merge borg/cloud-orchestrator-sync** into main (3 commits: prompt library, workspace tracker, cleanup) — needs clean hypercode worktree state
3. **Fix hypercode/.gitmodules** line 101 (bad config)
4. **Push superai** via SSH or GitHub API (1968 commits, 1GB+ pack)
5. **Fix bobmani/beatoraja** .gitmodules line 7 and index merge state
6. **Clean empty vendor-react chunk** in jules-autopilot build
7. **Investigate 11.82s build** — consistently improving (was 16.99s → 11.92s → 11.82s)

### Version History
| Version | Date | Forward Merges | Upstream Syncs | Build Time |
|---------|------|----------------|----------------|------------|
| v3.6.0 | 2026-04-17 | 0 | 0 | 16.99s |
| v3.7.0 | 2026-04-24 | 3 | 1 (topaz-ffmpeg) | 11.92s |
| **v3.8.0** | **2026-04-26** | **5** | **3** | **11.82s** |
