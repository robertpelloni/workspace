# Workspace Submodule Structural Map

**Generated**: 2026-05-21 | **Version**: 3.91.0 | **Submodules**: 71

## Project Structure

```
robertpelloni/workspace/          ← Root monorepo (main)
├── bobmani/                      ← Bob Mania family (music/games)
│   ├── hymnmania/               ← Hymn Remaker (AI music: Suno + Udio)
│   ├── ksm-v2/                  ← KSM (Konami StepMania variant)
│   ├── pianogame/               ← Piano learning game
│   └── bobmania/                ← Bob Mania central
├── bobeditpro/                   ← Audacity fork (DAW editor)
├── borg/                         ← AI assistant framework
├── jules-autopilot/             ← Jules session manager (Vite/Go)
├── hyperharness/                 ← Cloud orchestrator + agents
├── pi-mono/                      ← Plannotator + PI tools
├── OmniRoute/                    ← AI proxy router
├── tabby/                        ← Terminal (Wails/Go)
├── auto_dj_script/              ← Auto DJ (Python DSP mixing)
├── slsk_discography_downloader_script/ ← SoulSeek downloader
├── bobbybookmarks/              ← Bookmark service (Go/Fiber)
├── bobcoin/                      ← Cryptocurrency (Go/Next.js)
├── bobgui/                       ← GUI toolkit (bobtk Go port)
├── bobtorrent/                   ← Torrent manager (Go)
├── bobui/                        ← UI component library (Svelte)
├── fwber/                        ← Fediverse server (ActivityPub)
├── realestatecrm/               ← Real Estate CRM (Next.js)
├── MarbleBlast/                  ← Marble Blast game
├── mk64/                         ← Mario Kart 64 enhancement
├── sm64coopdx/                  ← Super Mario 64 coop
├── supersaber/                   ← Beat Saber clone
├── f-zerox/                      ← F-Zero X (N64)
├── dupeguru/                     ← Duplicate file finder
├── agentirc/                     ← IRC bot (Go)
├── litellm/                      ← LiteLLM proxy
├── onetool-mcp/                  ← MCP tool server
├── native-fy/                    ← Native desktop framework
├── skillzhub/                    ← Skills marketplace
├── planet_fitness_stepmaniax_agent/ ← StepManiaX agent
├── Maestro/                      ← Maestro orchestration
├── openclaw-config/              ← OpenClaw configuration
├── topaz-ffmpeg/                 ← FFmpeg fork
├── bobfilez/                     ← File management (pybind11 issues)
├── bg/                           ← BG game suite (merge complexity)
├── itgmania/                     ← In The Groove StepMania
├── stepmania/                    ← StepMania (upstream tracking)
├── projectm/                     ← ProjectM visualizer
├── zrythm/                       ← Zrythm DAW
├── btk/                          ← BTK toolkit
├── bobaver/                      ← Screen saver
├── bobserver/                    ← Server infrastructure
├── aider/                        ← Aider AI coding
├── llamafile/                    ← Llamafile inference
└── ... (71 total submodules)
```

## Submodule Registry

| Submodule | Source | Default Branch |
|-----------|--------|---------------|
| auto_dj_script | robertpelloni/auto_dj_script | main |
| bobeditpro | robertpelloni/bobeditpro (↑audacity/audacity) | master |
| bobmani/hymnmania | robertpelloni/hymnmania | master |
| bobmani/ksm-v2 | robertpelloni/ksm-v2 (↑ksm-v2) | release |
| borg | robertpelloni/borg | main |
| jules-autopilot | robertpelloni/jules-autopilot | main |
| hyperharness | robertpelloni/hyperharness | main |
| pi-mono | robertpelloni/pi-mono | main |
| OmniRoute | robertpelloni/OmniRoute | main |
| tabby | robertpelloni/tabby (↑TabbyML/tabby) | master |
| slsk_discography_downloader_script | robertpelloni/slsk_discography_downloader_script | main |
| bobcoin | robertpelloni/bobcoin | main |
| bobui | robertpelloni/bobui | main |
| fwber | robertpelloni/fwber | main |
| realestatecrm | robertpelloni/realestatecrm | main |

## Known Skip List
- **topaz-ffmpeg**: Diverged from upstream, manual intervention needed
- **bobfilez**: pybind11 directory recursion causes git timeout
- **bg**: Submodule merge complexity, requires manual resolution

