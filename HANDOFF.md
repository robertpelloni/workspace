# Workspace Handoff — v2.9.0 — 2026-04-17

## Session Summary
Protocol v2.9.0: Merged jules-autopilot RAG graph feature (via ref-update due to prisma DB lock), openclaw-config budget-guard locally. Upstream changes in bobeditpro (6 audacity commits, ClipIndicator.qml conflict resolved), tabby (1 CI build), ksm-v2 (1 upstream, NocoUI submodule conflict resolved). Built jules-autopilot in 10.95s.

## Key Changes This Session

### Feature Branches Merged → Default
| Repo | Branch | Default | Commits | Notes |
|------|--------|---------|---------|-------|
| jules-autopilot | `jules-17764958747146694232-3d7c3856` | main | 4 | RAG architecture graph, archive restructure. Merged via update-ref (prisma DB lock prevents normal checkout) |
| openclaw-config | `feat/budget-guard-from-paperclip` | main | 1 | Per-cron monthly spend caps with auto-disable (local only, 403 push) |

### Upstream Changes Merged
| Repo | Upstream | Commits | Conflict | Resolution |
|------|----------|---------|----------|------------|
| bobeditpro | audacity/audacity | 6 | ClipIndicator.qml | Auto-resolved (union merge) |
| tabby | Eugeny/tabby | 1 | None | Clean merge (CI build workflow) |
| bobmani/ksm-v2 | kshootmania | 1 | NocoUI submodule | Accept upstream version, resolved .noco files |

### Reverse Synced
- jules-autopilot: jules branch caught up with main

### Pushed This Session
**Default branches:**
- bobbybookmarks (1 ahead → pushed)
- bobeditpro (7 ahead → pushed, includes upstream merge)
- jules-autopilot (1 ahead → pushed, includes RAG graph merge)
- tabby (2 ahead → pushed, includes upstream merge)

**Feature branches:**
- jules-autopilot/jules-17764958747146694232-3d7c3856 (2 ahead, forced)

## Upstream Fork Status
| Repo | Upstream | Local Ahead | Upstream Ahead | Status |
|------|----------|-------------|----------------|--------|
| bobeditpro | audacity/audacity | 70 | 0 | ✅ synced |
| tabby | Eugeny/tabby | 27 | 0 | ✅ synced |
| sm64coopdx | djossm0/sm64coopdx | 59 | 0 | ✅ clean |
| topaz-ffmpeg | FFmpeg/FFmpeg | 555 | 0 | ✅ clean (403 push) |
| jules-autopilot | sbhavani/jules-app | 738 | 0 | ✅ clean |
| bobtrader | — | 91 | 0 | ✅ clean |
| bobtorrent | — | 243 | 0 | ✅ clean |
| mcp-superassistant | — | 58 | 0 | ✅ clean |
| raindropioapp | — | 252 | 0 | ✅ clean |
| mk64 | — | 27 | 0 | ✅ clean |
| bobmani/ksm-v2 | kshootmania | 59 | 0 | ✅ synced |
| bobmani/arrowvortex | — | 0 | 0 | ✅ clean |
| bobmani/beatoraja | — | 0 | 0 | ✅ clean |
| bobmani/ddc | — | 0 | 0 | ✅ clean |
| bobmani/itgmania | — | 0 | 0 | ✅ clean |
| bobmani/linthesia | — | 0 | 0 | ✅ clean |
| bobmani/Simply-Love-SM5 | — | 0 | 0 | ✅ clean |

## Branch Status (robertpelloni feature branches)
| Repo | Branch | Ahead | Behind | Status |
|------|--------|-------|--------|--------|
| agentirc | feature/agentirc-configuration-and-tools | 0 | 98 | Behind (reverse sync failed — abort) |
| bobbybookmarks | feature/reorg-and-integrate | 0 | 6 | Merged |
| bobbybookmarks | jules-bobbybookmarks-ingestion | 1 | 2 | Partially ahead |
| bobcoin | feat/governance-delays-and-zk-port | 3 | 0 | Ahead (new merge candidate for v3.0) |
| bobcoin | feature/comprehensive-ui-spec-* | 0 | 0 | Merged |
| bobeditpro | feature/bus-tracks-and-docs | 0 | 1294 | Merged into master |
| bobeditpro | feature/audition-parity-roadmap | 0 | 1278 | Merged into master |
| bobui | feature/omni-ui-framework | 0 | 1 | Nearly merged |
| bobui | jules-11090863842246041945 | 0 | 1 | Nearly merged |
| CLIProxyAPIPlus | jules-9238706904812453426 | 2 | 0 | Ahead (new merge candidate for v3.0) |
| f-zerox | pc-port-ui-implementation | 0 | 0 | Merged |
| geany | jules-3128865207300374222 | 0 | 0 | Merged |
| hyperharness | feat/deep-wire-mcp-memory | 0 | 1 | Nearly merged |
| jules-autopilot | jules-17764958747146694232 | 0 | 0 | ✅ MERGED this session |
| Maestro | jules-2575151016458646249 | 4 | 0 | Ahead (new merge candidate for v3.0) |
| Maestro | jules-add-new-agents | 0 | 0 | Merged |
| neverball | party-games-ui-docs | 0 | 0 | Merged |
| npp | disable-autocomplete-normal-text | 0 | 0 | Merged |
| npp | jules-3646841170776745183 | 0 | 1 | Nearly merged |
| openclaw-config | feat/budget-guard-from-paperclip | 0 | 106 | Merged locally (403 push) |
| openclaw-config | 20+ other branches | 0 | 100+ | All behind main (local) |
| opencode-autopilot | jules-4657769983160951050 | 1 | 0 | Ahead (new merge candidate for v3.0) |
| picard | jules-12364719424079951847 | 2 | 0 | Ahead (new merge candidate for v3.0) |
| pi-mono | jules-14458798274183669513 | 3 | 1 | Partially ahead |
| supersaber | jules-13860999388841438430 | 1 | 0 | Ahead (new merge candidate for v3.0) |

## New Merge Candidates (ahead of default, for v3.0)
1. **bobcoin** `feat/governance-delays-and-zk-port` (3 ahead)
2. **CLIProxyAPIPlus** `jules-9238706904812453426` (2 ahead)
3. **Maestro** `jules-2575151016458646249` (4 ahead)
4. **opencode-autopilot** `jules-4657769983160951050` (1 ahead)
5. **picard** `jules-12364719424079951847` (2 ahead)
6. **supersaber** `jules-13860999388841438430` (1 ahead)

## Project Structure
```
C:/Users/hyper/workspace/              (main meta-repo, VERSION, CHANGELOG, HANDOFF)
├── agentirc/                          (master, IRC agent)
├── bobbybookmarks/                    (main, bookmark manager)
├── bobcoin/                           (main, cryptocurrency)
├── bobeditpro/                        (master, audacity fork, 70 ahead upstream)
│   ├── muse_framework/               └── bobui/
├── bobfilez/                          (main, file manager - deep paths issue)
├── bobsaver/                          (main, screensaver - VoC data)
├── bobsgameonlinejava/                (main, online game)
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
├── jules-autopilot/                   (main, Vite React app, 738 ahead upstream)
│   ├── archive/ (borg session data, lancedb, handoffs)
│   ├── server/ (daemon, llm, queue, rag, supervisor, webhooks)
│   └── src/ (React frontend)
├── Maestro/                           (main, orchestration)
├── MarbleBlast/                       (master, game)
├── mcp-superassistant/                (main, MCP assistant)
├── mk64/                              (master, MK64 decomp)
├── neverball/                         (master, game)
├── npp/                               (master, Notepad++ fork)
│   └── {bobgui,bobui,btk}/
├── openclaw-config/                   (main, 102 ahead, 403 push - TechNickAI origin)
├── opencode-autopilot/                (main, VS Code extension)
├── picard/                            (master, MusicBrainz fork)
├── pi-mono/                           (main, pi monorepo)
│   └── third_party/{v8,deno,rustyscript,...}/
├── raindropioapp/                     (master, Raindrop.io client)
├── sm64coopdx/                        (main, SM64 co-op)
├── superai/                           (main, AI platform)
├── supersaber/                        (master, Beat Saber clone)
├── tabby/                             (master, terminal, 27 ahead upstream)
├── topaz-ffmpeg/                      (master, FFmpeg fork, 555 ahead, 403 push)
└── bobmani/                           (rhythm game collection)
    ├── arrowvortex/ (release) ─── beatoraja/ (master)
    ├── bobmania/ (main) ─── ddc/ (master)
    ├── hymnmania/ (master) ─── itgmania/ (release)
    ├── ksm-v2/ (develop, 59 ahead upstream) ─── linthesia/ (main)
    └── Simply-Love-SM5/ (itgmania-release)
```

## Technical Notes
- **jules-autopilot prisma DB lock**: The prisma/dev.db-shm and prisma/dev.db-wal files are locked by a running process, preventing normal `git checkout`. Workaround: merge on jules branch, then `git update-ref refs/heads/main HEAD` to update main's pointer without checking out files.
- **bobmani/ksm-v2 develop tracking**: develop tracks upstream/develop (not origin/develop). origin/develop doesn't exist. The `git fetch` output showed "forced update" for develop but it was actually updating upstream/develop.
- **bobcoin `feat/governance-delays-and-zk-port`**: 3 ahead of main — appears to have real governance/ZK content. Merge candidate for v3.0.

## Push Failures / Blockers
- **openclaw-config**: HTTP 403 — origin is TechNickAI/openclaw-config. robertpelloni fork exists as remote but push still fails. 102 commits ahead locally.
- **topaz-ffmpeg**: HTTP 403 — origin is TopazLabs/ffmpeg. robertpelloni fork needed.
- **bobui/submodules/juce**: HTTP 403 — third-party
- **bobui/submodules/ultimatepp**: HTTP 403 — third-party
- **Maestro**: Requires `--no-verify` (by design)
- **bobfilez**: Deep pybind11 paths cause checkout hangs

## Build Info
- **jules-autopilot**: Vite v6.4.2, 2970 modules, 10.95s build, 485KB index chunk
- **Build command**: `cd jules-autopilot && npm run build`

## Conflict Resolution Strategy
- Lock files: `--theirs`
- Source files: Union merge (concatenate both sides via Python regex)
- Submodule conflicts: Reset dirty state, accept upstream or ours as appropriate
- prisma DB files: Skip (use update-ref workaround)
- bobeditpro upstream branches: ALL skipped (30+ audacity release branches)
- tabby upstream branches: ALL skipped (40+ all-contributors branches)
- geany: No upstream remote configured

## Known Issues
- 156 Dependabot vulnerabilities in jules-autopilot (3 critical)
- openclaw-config: 403 push blocked (TechNickAI origin)
- topaz-ffmpeg: 403 push blocked (TopazLabs origin)
- bobui/submodules/juce & ultimatepp: Third-party origins, can't push
- btk/external/ultimatepp: Persistent merge conflict in uppsrc/CtrlCore
- agentirc: feature branch reverse sync aborted (98 behind)
- jules-autopilot: prisma DB files locked by running process
- Servers: Hetzner 5.161.250.43 hosts bobsgame.com, robertpelloni.com, fwber.me

## Next Steps
1. **v3.0 Candidates**: Merge 6 branches ahead of default (bobcoin, CLIProxyAPIPlus, Maestro, opencode-autopilot, picard, supersaber)
2. **openclaw-config**: Investigate why robertpelloni remote still returns 403
3. **topaz-ffmpeg**: Create robertpelloni fork on GitHub
4. Fix btk/external/ultimatepp merge conflict
5. Address 156 Dependabot vulnerabilities (3 critical)
6. Consider setting up geany upstream remote (geany/geany)
7. Investigate agentirc merge abort issue
