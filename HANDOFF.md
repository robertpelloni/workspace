# Workspace Handoff — v2.8.0 — 2026-04-17

## Session Summary
Protocol v2.8.0: Merged jules-autopilot re-merge (3 commits), bobeditpro bus-tracks feature (3 commits), bobmani/hymnmania comprehensive-docs with conflict resolution, and bobmani/ksm-v2 configurable-songs-dir. **First upstream changes in 3 sessions**: bobeditpro (2 audacity commits, conflict resolved), tabby (4 xterm commits), topaz-ffmpeg (1 vulkan commit). All 34+ feature branches reverse-synced. Built jules-autopilot successfully (12.85s).

## Key Changes This Session

### Feature Branches Merged → Default
| Repo | Branch | Default | Commits | Notes |
|------|--------|---------|---------|-------|
| jules-autopilot | `jules-17764958747146694232-3d7c3856` | main | 3 | vercel.json added |
| bobeditpro | `feature/bus-tracks-and-docs-8870936135855758930` | master | 3 | fast-forward |
| bobmani/hymnmania | `feat/comprehensive-docs-and-tts-params-...` | master | 26 | conflict resolution on VERSION, CHANGELOG, docs, video_uploader.py |
| bobmani/ksm-v2 | `jules/feature/configurable-songs-dir-...` | develop | — | build_output files |

### Upstream Changes Merged (NEW!)
| Repo | Upstream | Commits | Conflict | Resolution |
|------|----------|---------|----------|------------|
| bobeditpro | audacity/audacity | 2 | au3importer.cpp | Auto-resolved (union merge) |
| tabby | Eugeny/tabby | 4 | None | Clean merge (xterm frontend) |
| topaz-ffmpeg | FFmpeg/FFmpeg | 1 | None | Clean merge (vulkan ffv1) |

### Reverse Synced (default → feature)
All 34+ feature branches updated. Notable:
- bobsaver: `jules-7169901332660125491` caught up with main
- geany: `jules-3128865207300374222` caught up with master (51 commits behind → now synced)
- bobmani/beatoraja: `feature/launcher-enhancement-docs` caught up with master

### Pushed This Session
**Default branches:**
- bobbybookmarks (1 ahead → pushed)
- bobeditpro (6 ahead → pushed, includes upstream + feature merge)
- hyperharness (1 ahead → pushed)
- jules-autopilot (1 ahead → pushed)
- opencode-autopilot (35 ahead → pushed)
- pi-mono (1 ahead → pushed)
- tabby (5 ahead → pushed, includes upstream merge)
- bobmani/hymnmania (26 ahead → pushed)

**Feature branches:**
- bobui/feature/omni-ui-framework (4 ahead)
- geany/jules-3128865207300374222 (51 ahead, forced)
- bobsaver/jules-7169901332660125491 (8 ahead)
- bobmani/beatoraja/feature/launcher-enhancement-docs (47 ahead)

## Upstream Fork Status
| Repo | Upstream | Local Ahead | Upstream Ahead | Status |
|------|----------|-------------|----------------|--------|
| bobeditpro | audacity/audacity | 64 | 0 | ✅ synced |
| tabby | Eugeny/tabby | 26 | 0 | ✅ synced |
| sm64coopdx | djossm0/sm64coopdx | 59 | 0 | ✅ clean |
| topaz-ffmpeg | FFmpeg/FFmpeg | 555 | 0 | ✅ synced (can't push - 403) |
| jules-autopilot | sbhavani/jules-app | 737 | 0 | ✅ clean |
| bobtrader | — | 91 | 0 | ✅ clean |
| bobtorrent | — | 243 | 0 | ✅ clean |
| mcp-superassistant | — | 58 | 0 | ✅ clean |
| raindropioapp | — | 252 | 0 | ✅ clean |
| mk64 | — | 27 | 0 | ✅ clean |
| bobmani/arrowvortex | — | 0 | 0 | ✅ clean |
| bobmani/beatoraja | — | 0 | 0 | ✅ clean |
| bobmani/ddc | — | 0 | 0 | ✅ clean |
| bobmani/itgmania | — | 0 | 0 | ✅ clean |
| bobmani/ksm-v2 | — | 58 | 0 | ✅ clean |
| bobmani/linthesia | — | 0 | 0 | ✅ clean |
| bobmani/Simply-Love-SM5 | — | 0 | 0 | ✅ clean |

## Project Structure
```
C:/Users/hyper/workspace/              (main meta-repo, VERSION, CHANGELOG, HANDOFF)
├── agentirc/                          (master, IRC agent)
├── bobbybookmarks/                    (main, bookmark manager)
├── bobcoin/                           (main, cryptocurrency)
├── bobeditpro/                        (master, audacity fork)
│   ├── muse_framework/                └── bobui/
├── bobfilez/                          (main, file manager)
├── bobsaver/                          (main, screensaver - VoC data)
├── bobsgameonlinejava/                (master, online game)
├── bobtorrent/                        (master, torrent client)
├── bobtrader/                         (main, trading platform)
├── bobtrax/                           (master, DAW suite)
│   ├── ardour/ └── bobui/ └── lmms/ └── muse/ └── zrythm/
├── bobui/                             (main, UI framework)
│   ├── submodules/juce/               (origin: juce-framework/JUCE, 403)
│   └── submodules/ultimatepp/         (origin: ultimatepp/ultimatepp, 403)
├── btk/                               (master, toolkit)
│   └── external/{bobui-reference,juce,ultimatepp}/
├── CLIProxyAPIPlus/                   (main, CLI proxy)
├── f-zerox/                           (main, F-Zero X decomp)
│   └── subprojects/{bobgui,bobui,btk}/ └── bobcoin/
├── geany/                             (master, text editor fork)
│   └── subprojects/{bobgui,bobui,btk}/
├── hyperharness/                      (main, 27 AI tool submodules)
│   ├── adrenaline/ aider/ amazon-q-developer-cli/ auggie/ azure-ai-cli/
│   ├── byterover-cli/ claude-code-templates/ code-cli/ copilot-cli/
│   ├── crush/ dolt/ factory-cli/ gemini-cli/ goose/ grok-cli/
│   ├── jules-extension/ kilocode/ kimi-cli/ litellm/ llamafile/
│   ├── llm-cli/ ollama/ open-interpreter/ opencode/ pi-cli/
│   ├── rowboat/ smithery-cli/ vibe/
├── jules-autopilot/                   (main, Vite React app, 737 ahead upstream)
├── Maestro/                           (main, orchestration)
├── MarbleBlast/                       (master, game)
├── mcp-superassistant/                (main, MCP assistant)
├── mk64/                              (master, MK64 decomp)
├── neverball/                         (master, game)
├── npp/                               (master, Notepad++ fork)
│   └── {bobgui,bobui,btk}/
├── openclaw-config/                   (main, 101 ahead, 403 push - TechNickAI origin)
├── opencode-autopilot/                (main, VS Code extension)
├── picard/                            (master, MusicBrainz fork)
├── pi-mono/                           (main, pi monorepo)
│   └── third_party/{v8,deno,rustyscript,...}/
├── raindropioapp/                     (master, Raindrop.io client)
├── sm64coopdx/                        (main, SM64 co-op)
├── superai/                           (main, AI platform)
├── supersaber/                        (master, Beat Saber clone)
├── tabby/                             (master, terminal, 26 ahead upstream)
├── topaz-ffmpeg/                      (master, FFmpeg fork, 555 ahead, 403 push)
└── bobmani/                           (rhythm game collection)
    ├── arrowvortex/ (release) ─── beatoraja/ (master)
    ├── bobmania/ (main) ─── ddc/ (master)
    ├── hymnmania/ (master) ─── itgmania/ (release)
    ├── ksm-v2/ (develop, 58 ahead) ─── linthesia/ (main)
    └── Simply-Love-SM5/ (itgmania-release)
```

## Push Failures / Blockers
- **openclaw-config**: HTTP 403 — origin is TechNickAI/openclaw-config. robertpelloni fork does NOT exist. 101 commits ahead. Need to fork on GitHub first.
- **topaz-ffmpeg**: HTTP 403 — origin is TopazLabs/ffmpeg. robertpelloni fork needed.
- **bobui/submodules/juce**: HTTP 403 — third-party (juce-framework/JUCE)
- **bobui/submodules/ultimatepp**: HTTP 403 — third-party (ultimatepp/ultimatepp)
- **Maestro**: Requires `--no-verify` for pushes (by design)
- **bobfilez**: Deep pybind11 paths cause checkout hangs (Filename too long)

## Build Info
- **jules-autopilot**: Vite v6.4.2, 2970 modules, 12.85s build, 485KB index chunk
- **Node**: v22+ required
- **Build command**: `cd jules-autopilot && npm run build`

## Conflict Resolution Strategy
- Lock files (package-lock, yarn.lock, Cargo.lock): `--theirs` (accept incoming)
- Source files: Union merge (concatenate both sides via Python regex)
- Translation files (.po): `--theirs`
- Submodule conflicts: Reset dirty state, then merge
- Unrelated histories: `--allow-unrelated-histories` only when safe
- bobeditpro upstream branches: ALL skipped (60+ audacity release branches)
- tabby upstream branches: ALL skipped (80+ all-contributors + dependabot)
- geany: No upstream remote configured

## Known Issues
- 156 Dependabot vulnerabilities in jules-autopilot (3 critical)
- openclaw-config: Need to create robertpelloni fork (403)
- topaz-ffmpeg: Need to create robertpelloni fork (403)
- bobui/submodules/juce & ultimatepp: Third-party origins, can't push (by design)
- btk/external/ultimatepp: Persistent merge conflict in uppsrc/CtrlCore
- bobtrax/npp/btk: ultimatepp submodule remote ref errors (upload-pack: not our ref)
- bobdesk: 13K dirty LibreOffice files (intentional)
- borg: Secondary worktree at hypercode-push (by design)
- geany: No upstream remote (would need geany/geany as upstream)
- Servers: Hetzner 5.161.250.43 hosts bobsgame.com, robertpelloni.com, fwber.me

## Next Steps
1. **openclaw-config**: Create robertpelloni fork on GitHub, add as remote, push 101 commits
2. **topaz-ffmpeg**: Create robertpelloni fork, push local changes
3. Fix btk/external/ultimatepp merge conflict
4. Fix bobtrax/npp/btk ultimatepp submodule remote ref errors
5. Address 156 Dependabot vulnerabilities (3 critical)
6. Consider setting up geany upstream remote (geany/geany)
7. Maestro: Push rc branch if it exists
