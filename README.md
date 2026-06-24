🛠️ ALPHA SOFTWARE UNDER CONSTRUCTION — Use at your own risk. Backwards compatibility not guaranteed.

╔══════════════════════════════════════════════════════════════════════════════╗
║                                                                              ║
║                     ██╗   ██╗███╗   ██╗██████╗ ███████╗██████╗              ║
║                     ██║   ██║████╗  ██║██╔══██╗██╔════╝██╔══██╗             ║
║                     ██║   ██║██╔██╗ ██║██║  ██║█████╗  ██████╔╝             ║
║                     ██║   ██║██║╚██╗██║██║  ██║██╔══╝  ██╔══██╗             ║
║                     ╚██████╔╝██║ ╚████║██████╔╝███████╗██║  ██║             ║
║                      ╚═════╝ ╚═╝  ╚═══╝╚═════╝ ╚══════╝╚═╝  ╚═╝             ║
║                                                                              ║
║                     ██████╗ ██████╗ ███╗   ██╗███████╗████████╗██████╗      ║
║                    ██╔════╝██╔═══██╗████╗  ██║██╔════╝╚══██╔══╝██╔══██╗     ║
║                    ██║     ██║   ██║██╔██╗ ██║███████╗   ██║   ██████╔╝     ║
║                    ██║     ██║   ██║██║╚██╗██║╚════██║   ██║   ██╔══██╗     ║
║                    ╚██████╗╚██████╔╝██║ ╚████║███████║   ██║   ██║  ██║     ║
║                     ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝   ╚═╝   ╚═╝  ╚═╝     ║
║                                                                              ║
║                     █████╗ ██╗     ██████╗ ██╗  ██╗ █████╗                  ║
║                    ██╔══██╗██║     ██╔══██╗██║  ██║██╔══██╗                 ║
║                    ███████║██║     ██████╔╝███████║███████║                 ║
║                    ██╔══██║██║     ██╔═══╝ ██╔══██║██╔══██║                 ║
║                    ██║  ██║███████╗██║     ██║  ██║██║  ██║                 ║
║                    ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝                 ║
║                                                                              ║
║                    ╔══════════════════════════════════════╗                  ║
║                    ║     ⚠️  ALPHA SOFTWARE  ⚠️           ║                  ║
║                    ║  EXPECT BREAKING CHANGES & BUGS     ║                  ║
║                    ║  NOT READY FOR PRODUCTION USE       ║                  ║
║                    ╚══════════════════════════════════════╝                  ║
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝

# Robert Pelloni's Omni-Workspace (Monorepo)

**Version:** v5.38.0 | **Repos:** 125+ | **Submodules:** 90 | **AI & Human Lines:** 198M+

---

## Overview

This is a **centralized federated monorepo and orchestration hub** for Robert Pelloni's complete software ecosystem — spanning AI agent infrastructure, rhythm games, web platforms, cryptocurrency, desktop applications, browser forks, game engines, and developer tools. It serves as both the unified workspace and the **AI-orchestrated automation layer** that syncs, builds, merges, and deploys across 125+ repositories.

> **Core Philosophy:** "No code left behind" — every AI-generated feature branch is intelligently merged in. A multi-model AI pipeline (Claude → Gemini → GPT → DeepSeek) autonomously maintains the entire ecosystem.

---

## Domain Breakdown

### 🤖 AI & Agent Orchestration

| Project | Description | Stack |
|---------|-------------|-------|
| **TormentNexus** | Central MCP aggregator — 46 tools, 4+ servers, port 4100 | TypeScript, Go |
| **mcp-superassistant** | 14-package MCP SuperAssistant (turbo build 56s) | TypeScript, pnpm, TRPC |
| **metamcp** | MCP proxy layer for cross-agent tool routing | TypeScript |
| **aios** | Meta-orchestrator "AI Operating System" for MCP/agents | Fastify v5, Next.js 14 |
| **borg** | Multi-agent choreography bus | Node.js, pnpm |
| **jules-autopilot** | Google Jules AI automation runtime | TypeScript monorepo |
| **antigravity-autopilot** | VS Code extension / background task executor | TypeScript |
| **opencode-autopilot** | OpenCode AI automation | Node.js/Bun |
| **Maestro** | TechLead orchestrator & multi-agent UI | TypeScript/Electron |
| **claude-mem** | Persistent memory management for Claude | Node.js, SQLite |
| **pi-mono** | Pi coding agent monorepo integration | TypeScript |

### 🎮 Rhythm Games (bobmani/)

| Project | Description | Stack | Build Status |
|---------|-------------|-------|:------------:|
| **bobmania** | Experimental StepMania 5.1+ fork | C++, OpenGL | 🟢 |
| **itgmania** | Tournament-grade StepMania 3.95 fork | C++, Lua | 🟢 |
| **beatoraja** | BMS/IIDX simulator (1300+ errors fixed) | Java 21, JavaFX | 🟢 Fixed |
| **arrowvortex** | Simfile chart editor | C++, Qt 5 | 🟢 |
| **ddc** | Dance Diffusion ML auto-charter | Python | 🟢 |
| **ddc_onset** | Audio onset detection for DDC | Python | 🟢 |
| **ffr-difficulty-model** | FFR difficulty calculation | Python/TensorFlow | 🟢 |
| **ksm-v2** | K-Shoot Mania clone | C++ | 🟢 |
| **leraine-studio** | Chart editor for Bob's Game | C++, Qt | 🟢 |
| **linthesia** | Piano-learning rhythm game | Rust, Bevy | 🟢 |
| **hymnmania** | Hymnal-focused rhythm game | C++ | 🟢 |
| **Simply-Love-SM5** | Popular StepMania theme | Lua | 🟢 |
| **pianogame** | Synthesia-style piano trainer | C++ | 🟢 |

### 🌐 Bob Ecosystem (Desktop & Web)

| Product | Description | Stack | Status |
|---------|-------------|-------|:------:|
| **bobcoin** | Proof-of-health cryptocurrency on Solana | Solana, Node.js | 🟢 Active |
| **bobtorrent** | P2P file sharing client | Node.js, WebTorrent | 🟢 Active |
| **bobfilez** | Desktop file organizer | Qt/C++ | 🟢 Active |
| **bobeditpro** | Audio editor (Audacity fork) | C++, Audacity | 🟡 Forked |
| **bobsaver** | Password manager | Electron/Node.js | 🟢 Active |
| **bobtrader** | AI trading system | Python, ML | 🟡 Initializing |
| **bobbybookmarks** | Bookmark manager | Python/Flask | 🟢 Active |
| **bcs** | Build toolkit (renamed from `btk`) | — | 🟢 Active |
| **bgtk** | GUI toolkit (renamed from `bobgui`) | C++/GTK fork | 🟢 Active |
| **bqt** | UI component library (renamed from `bobui`) | C++/Qt fork | 🟢 Active |
| **bobium** | Chromium browser (de-Googled) | C++, Chromium | 🟡 Forked |
| **bobzilla** | Firefox browser (privacy fork) | C++, Mozilla | 🟡 Forked |
| **bobzzite** | Gaming OS (Bazzite/Fedora Atomic) | Container | 🟡 Init |
| **bobsaver/JWildfire** | Fractal flame renderer | Java 21, Gradle | 🟢 Built |

### 🌐 Web Applications

| Project | Description | Stack |
|---------|-------------|-------|
| **fwber** | Dating platform | Laravel 12, Next.js, PostgreSQL |
| **raindropioapp** | Bookmark manager | Node.js, React, Webpack |
| **bobsgameonlinejava** | Classic Bob's Game Online | Java/Gradle, Lua |
| **bobsgameweb** | Web frontend for Bob's Game | Web |

### 🎲 Game Engines & Games

| Project | Description | Stack | Build |
|---------|-------------|-------|:----:|
| **bg** | Bob's 2D MMORPG engine | Custom C++ | 🟢 |
| **okgame** | Cross-platform game engine | C++ | 🟢 |
| **sm64coopdx** | SM64 cooperative multiplayer | C/N64 | 🟢 |
| **mk64** | Mario Kart 64 decompilation | C/Make | 🟢 |
| **f-zerox** | F-Zero X decompilation | C++/CMake | 🟢 |
| **neverball** | 3D rolling-ball puzzle | C/Make | 🟢 |
| **MarbleBlast** | Marble Blast Gold fork | Node/TS | 🔴 Dep |
| **OpenMBU** | Marble Blast Ultra engine | C++/CMake | 🟢 |
| **supersaber** | Beat Saber clone | Node/Webpack | 🔴 Dep |
| **superpowers** | Game engine | HTML5/TS | 🟢 |

### 🛠️ Developer & Multimedia Tools

| Project | Description | Stack | Build |
|---------|-------------|-------|:----:|
| **picard** | MusicBrainz audio tagging | Python/PyQt | 🟢 |
| **topaz-ffmpeg** | Topaz Video AI + FFmpeg | C/Make | 🟢 |
| **npp** | Notepad++ fork | C++/MSVC | 🟢 |
| **geany** | Text editor | C | 🟢 |
| **tabby** | Modern terminal emulator | TypeScript/Electron | 🟢 |
| **dupeguru** | Duplicate file finder | Python/PyQt | 🟢 |
| **CLIProxyAPIPlus** | CLI proxy for API management | Node.js | 🟢 |
| **superdawmcp** | DAW MCP integration | — | 🟢 |
| **auto_dj_script** | Automated DJ mixing | Python | 🟢 |
| **MilkDrop3** | Winamp visualizer | — | 🟢 |
| **projectm** | Music visualizer | — | 🟢 |
| **Geiss** | Winamp visualizer | — | 🟢 |
| **ableton_psytrance_hymn_creator** | Psytrance + hymn music generation | — | 🟢 |

### 🤖 AI Automation Agents

| Project | Description |
|---------|-------------|
| **agentirc** | IRC bot (Chainlit/Python) |
| **enterprise_sales_bot** | Sales automation |
| **psytrance_night_outreach_agent** | Event outreach |
| **planet_fitness_stepmaniax_agent** | Fitness + rhythm game agent |
| **hermes-agent** | Messenger agent |
| **aimoneymachine_site** | AI money machine concepts (renamed from `fully_automated_gay_luxury_space_communism`) |

### 🎵 Audio Visualizers & Music

| Project | Description |
|---------|-------------|
| **MilkDrop3** | Classic Winamp visualization |
| **projectm** | MilkDrop-compatible open-source visualizer |
| **Geiss** | Winamp visualization plugin |
| **JWildfire** | Fractal flame renderer (Java/Gradle) |
| **Apophysis-J** | Fractal flame editor |

### 🔗 Partner Projects (mnmballa2323)

| Project | Description |
|---------|-------------|
| **Chamber.Law** | Collaborative legal workflow platform |
| **Stone.Ledger** | Ledger/accounting system |
| **Azure.Cybersecurity** | Cybersecurity training (.NET/Azure) |
| **Alti.Assistant** | Mobile assistant application |
| **Alti.Code.Studio** | Collaborative code studio |
| **Merk.Mobile** | Mobile app development |
| **Tickerstone** | Stock ticker visualization |
| **cointrade** | Cryptocurrency trading platform |

---

## 🧰 Automation Layer

### Executive Protocols

The workspace operates via numbered automated sync/merge/build cycles:

| Protocol | Date | Action |
|----------|------|--------|
| **EP #9** | 2026-06-18 | Fixed submodule refs, removed stale entries, repo renames |
| **EP #7** | 2026-06-18 | Full fetch, 270 submodules scanned, broken gitlinks repaired |
| **EP #3** | 2026-06-15 | Full sync re-executed, all repos fetched |
| **EP #1** | 2026-06-13 | Initial full sync + feature branch merge |

### Key Scripts (`scripts/`)

- `intelligent_sync_all.py` — Smart sync with conflict detection
- `dual_merge_engine.py` — Bidirectional merge automation
- `resolve_all_conflicts.py` — Automated conflict resolution
- `generate_dashboard.py` — Submodule state dashboard
- `measure_ai_contribution.py` — AI vs human commit metrics
- `health_check.py` — Service health verification
- `workspace_indexer.py` — Workspace file indexing

### Infrastructure

- **Docker Compose**: LiteLLM proxy (port 4000) + PostgreSQL + Prometheus
- **MCP Protocol**: TormentNexus aggregates 4+ MCP servers, 46 tools
- **CI/CD**: GitHub Actions (Playwright tests, consensus gate)
- **Monitoring**: Prometheus, health checks, workspace dashboard

---

## 📊 Key Metrics

| Metric | Value |
|--------|-------|
| **Total repositories** | 125+ |
| **Git submodules (root)** | 65 |
| **Nested submodules (total)** | ~270 |
| **Total codebase** | ~198 million lines |
| **AI-generated lines** | 24.1 million (12.2%) |
| **AI commits** | 2,589 / 708,528 total |
| **Build pass rate** | ~80% verified clean |
| **MCP tools available** | 46 |
| **Open Dependabot alerts** | ~170 (being triaged) |
| **Current version** | v5.17.0 |

---

## 🗺️ Roadmap

| Phase | Status |
|-------|:------:|
| **1. Consolidation** — Unify submodules, fix pointers | ✅ Complete |
| **2. Feature Branch Resolution** — Merge all AI branches | ✅ Complete |
| **3. Global Build Orchestration** — Build pipelines connected | ✅ Complete |
| **4. Production Hardening** — Security, health, containers | 🔜 In Progress |
| **5. Full Autonomy** — Zero-touch prompt-to-deploy | ⏳ Future |

---

## 🔄 Repos Renamed on GitHub

The following repositories have been renamed (old URLs redirect to new):

| Old Name | New Name | Redirect |
|----------|----------|:--------:|
| `robertpelloni/bobui` | `robertpelloni/bqt` | ✅ 301 |
| `robertpelloni/bobgui` | `robertpelloni/bgtk` | ✅ 301 |
| `robertpelloni/btk` | `robertpelloni/bcs` | ✅ 301 |
| `robertpelloni/litellm_control_panel` | `robertpelloni/freellm` | ✅ 301 |
| `robertpelloni/fully_automated_gay_luxury_space_communism` | `robertpelloni/aimoneymachine_site` | ✅ 301 |
| `robertpelloni/hypercode` | `MDMAtk/TormentNexus` | ✅ 301 (transferred) |
| `robertpelloni/tormentnexus` | `MDMAtk/TormentNexus` | ✅ 301 (transferred) |
| `robertpelloni/TormentNexus` | `MDMAtk/TormentNexus` | ✅ 301 (transferred) |

## 🗑️ Deregistered Submodules (GitHub 404 — Deleted)

These repositories were deleted from GitHub. Removed from `.gitmodules` and git index. Local data preserved on disk.

| Repository | Local Size | Reason |
|------------|:----------:|--------|
| `robertpelloni/bobdesk` | 4.4 GB | LibreOffice fork, deleted from GitHub |
| `robertpelloni/OmniRoute` | 2.9 GB | Routing engine, deleted from GitHub |
| `robertpelloni/antigravity-autopilot` | 2.4 GB | AI automation, deleted from GitHub |
| `robertpelloni/litellm` | — | LLM proxy fork, deleted from GitHub |
| `robertpelloni/antigravity-jules-orchestration` | 217 MB | Jules orchestration, deleted from GitHub |
| `robertpelloni/WebAI-to-API` | 183 MB | Web API proxy, deleted from GitHub |
| `robertpelloni/Cli-Proxy-API-Management-Center` | 156 MB | API management UI, deleted from GitHub |
| `robertpelloni/claude-mem` | 332 MB | Claude memory, deleted from GitHub |
| `robertpelloni/raindropioapp` | — | Raindrop.io fork, deleted from GitHub |
| `robertpelloni/metamcp` | — | MCP proxy, deleted from GitHub |
| `robertpelloni/picard` | — | MusicBrainz fork, deleted from GitHub |
| `robertpelloni/CLIProxyAPIPlus` | 15 MB | CLI proxy, deleted from GitHub |
| `robertpelloni/antigravity-cli` | 28 MB | CLI tool (krmslmz), upstream deleted |
| `robertpelloni/opencode-autopilot` | — | AI autopilot, deleted from GitHub |
| `robertpelloni/computer-use-preview` | 131 KB | Google Gemini tool, upstream deleted |
| `robertpelloni/mcpenetes` | 654 KB | MCP utilities, deleted from GitHub |
| `robertpelloni/dupeguru` | 3.4 MB | Duplicate file finder fork, deleted from GitHub |
| `robertpelloni/frontend-sdl-cpp` | — | SDL frontend, deleted from GitHub |
| `robertpelloni/superpowers` | — | Game engine, deleted from GitHub |

### Stale Entries (removed in v5.15.0)

- `brokeragentworkflow`, `explorerexedecompiled`, `forclosureworkflow`
- `re-agent-workflow-media-1`, `p2p_service_marketplace`
- `realestateleadcaller`, `theta-data-api`, `socialmediacontentplanner`

## 📁 Submodules Removed from Workspace Index

| Submodule | Reason |
|-----------|--------|
| `.agent` (sickn33/antigravity-awesome-skills) | No longer tracked as submodule |
| `tormentnexus/submodules/serena` | Nested submodule removed |

---

## Development Philosophy

- **Independent Contexts**: Each subproject has its own documentation, goals, and tasks
- **AI Orchestration**: Multi-model coordination for rapid development
- **Flat Organization**: Projects as top-level directories or submodules
- **Zero Data Loss**: All feature branches intelligently merged, never discarded
- **Version Governance**: Single `VERSION` file as source of truth

---

*Note: This repository is synced on GitHub as a consolidated view of Robert Pelloni's original work at [github.com/robertpelloni](https://github.com/robertpelloni).*
