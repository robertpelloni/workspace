# PROJECT_STRUCTURE
**Last Updated:** 2026-02-08

## Overview
This document catalogs the current layout of Robert Pelloni’s monorepo, covering every root-level submodule, local project, and supporting configuration file. The sections below organize the estate by domain, highlight the stack for each component, and surface how the pieces fit together so contributors can find every subproject from one central narrative.

## Visual Layout
```
/
├─ docs/ (LLM instructions, references, archives)
├─ scripts/ (automation helpers, sync/generate recipes)
├─ logs/ (session logs + handoffs)
├─ ai & orchestration: borg/, aios/, claude-mem/, metamcp/, mcp-superassistant/, mcpenetes/
├─ AI agent automation: antigravity-autopilot/, antigravity-jules-orchestration/, jules-autopilot/, opencode-autopilot/
├─ bobmani/
│  ├─ bobmania/
│  ├─ itgmania/
│  ├─ beatoraja/
│  ├─ arrowvortex/
│  ├─ linthesia/
│  ├─ pianogame/
│  ├─ ddc/
│  ├─ ddc_onset/
│  ├─ ffr-difficulty-model/
│  ├─ Simply-Love-SM5/
│  ├─ hymnmania/
│  ├─ ksm-v2/
│  └─ leraine-studio/
├─ bob ecosystem: bobcoin/, bobeditpro/, bobfilez/, bobium/, bobsaver/, bobtorrent/, bobtrader/, bobui/, bobzilla/
├─ rhythm and game engines: bg/, mk64/, sm64coopdx/, superbobbyball/
├─ web applications: fwber/, raindropioapp/
├─ external/collaborative: Alti.Assistant/, Alti.Code.Studio/, Azure.Cybersecurity/, Chamber.Law/, Merk.Mobile/, Stone.Ledger/, Tickerstone/, coin.project/, cointrade/
├─ developer tools: musicbrainz-soulseek-downloader/, topaz-ffmpeg/
├─ research & experiments: research/ (brobocallz, context_portal, makemoney, workspace-orchestrator)
├─ infrastructure: mk64/, cointrade/, bobmani/ (shared)
├─ config roots: VERSION, CHANGELOG.md, ROADMAP.md, VISION.md, BOB_ECOSYSTEM.md, AGENTS.md, CLAUDE.md, GEMINI.md, GPT.md,
│  package.json, pyproject.toml, playwright.config.ts, codebuff.json, workspace.code-workspace, .gitmodules, .github/copilot-instructions.md
└─ miscellaneous: undefined/
```

## AI & Orchestration
| Path | Description | Stack / Language | Status |
| --- | --- | --- | --- |
| `aios/` | Meta-orchestration brain for MCP, managers, agents, and dashboards. | Fastify v5, Next.js 14, pnpm workspace, Python helpers | Active |
| `borg/` | Multi-agent choreography bus used by AIOS to route jobs between agents. | Node.js, pnpm, custom agent framework | Experimental |
| `claude-mem/` | Claude memory management tooling and persistence helpers. | Node.js, TypeScript, SQLite | Active |
| `metamcp/` | Meta MCP proxy layer for bridging orchestration and external MCP servers. | TypeScript, Fastify-compatible API | Active |
| `mcp-superassistant/` | Core MCP SuperAssistant entry point (alias `MCP_SuperAssistant/`). | TypeScript, pnpm, TRPC | Active |
| `mcpenetes/` | MCP utilities, health checks, and supporting scripts for SuperAssistant. | TypeScript, Bash | Maintained |

## Rhythm Games (bobmani/)
| Path | Description | Stack / Language | Status |
| --- | --- | --- | --- |
| `bobmani/` | Container for rhythm game assets and collaborative tooling. | Mixed (C++, Java, Rust, Python) | Active |
| `bobmani/bobmania/` | Experimental StepMania 5.1+ fork with modern features. | C++, CMake, OpenGL | Active |
| `bobmani/itgmania/` | Tournament-grade StepMania fork (SM 3.95 lineage). | C++, Autotools, Lua | Active |
| `bobmani/beatoraja/` | BMS/IIDX simulator targeting precision play. | Java, Gradle, libGDX | Maintenance |
| `bobmani/arrowvortex/` | Chart editor for simfiles; Qt + C++ codebase. | C++, Qt 5 | Active |
| `bobmani/linthesia/` | Piano-learning rhythm game with Rust tooling. | Rust, Bevy | Active |
| `bobmani/pianogame/` | Historical Synthesia-style piano training experience. | C++ | Maintenance |
| `bobmani/ddc/` | Dance Diffusion auto-charter service. | Python, ML models | Research |
| `bobmani/ddc_onset/` | Audio onset detection engine for DDC. | Python, Librosa | Research |
| `bobmani/ffr-difficulty-model/` | FFR difficulty calculation engine. | Python, TensorFlow | Active |
| `bobmani/Simply-Love-SM5/` | Popular StepMania theme maintained in the suite. | Lua, StepMania theme files | Active |
| `bobmani/hymnmania/` | Hymnal-focused rhythm game demonstration. | C++ | Maintenance |
| `bobmani/ksm-v2/` | K-Shoot Mania clone for fast chart play. | C++ | Active |
| `bobmani/leraine-studio/` | Chart editor tailored to Bob's Game rhythm levels. | C++, Qt | Active |

## Bob Ecosystem Products
| Path | Description | Stack / Language | Status |
| --- | --- | --- | --- |
| `bobcoin/` | Proof-of-health cryptocurrency (Solana + Node.js). | Solana, Node.js, TypeScript | Active |
| `bobeditpro/` | Code editor with Bob’s Game-inspired UX. | Electron, TypeScript | Initializing |
| `bobfilez/` | Desktop file organizer (Qt/C++ rebrand of filez). | C++, Qt 6 | Active |
| `bobium/` | Chromium fork that strips Google services. | C++, Chromium build | Maintenance |
| `bobsaver/` | Password manager for secure storage. | Electron/Node.js | Active |
| `bobtorrent/` | Peer-to-peer file sharing client. | Node.js, WebTorrent | Maintained |
| `bobtrader/` | Trading tools and dashboards. | Node.js, TypeScript | Initializing |
| `bobui/` | UI component library for Bob projects. | React, TypeScript | Active |
| `bobzilla/` | Privacy-focused Firefox fork. | C++, Mozilla toolchain | Maintenance |

## Game Engines & Games
| Path | Description | Stack / Language | Status |
| --- | --- | --- | --- |
| `bg/` | Bob’s signature 2D MMORPG and world-building engine. | C++, Custom engine | Active |
| `mk64/` | Mario Kart 64 decompilation project. | C, N64 toolchain | Active |
| `sm64coopdx/` | Super Mario 64 cooperative multiplayer extension. | C, Custom N64 tooling | Active |
| `superbobbyball/` | Super Monkey Ball-inspired physics showcase. | C++, Unity? | Prototyping |

## Web Applications
| Path | Description | Stack / Language | Status |
| --- | --- | --- | --- |
| `fwber/` | Dating platform with Laravel 12 backend + Next.js frontend. | PHP 8.3, Laravel, Next.js, Tailwind | Active |
| `raindropioapp/` | Raindrop.io bookmark manager adaptation. | Node.js, TypeScript, React | Maintained |

## Developer Tools
| Path | Description | Stack / Language | Status |
| --- | --- | --- | --- |
| `musicbrainz-soulseek-downloader/` | Music metadata enrichment + download helper. | Python | Maintenance |
| `topaz-ffmpeg/` | Topaz Video AI + FFmpeg integration for enhancements. | FFmpeg, Topaz SDK | Tooling |

## Research & Experiments (research/)
| Path | Description | Stack / Language | Status |
| --- | --- | --- | --- |
| `brobocallz/` | Communication tool for distributed teams. | Node.js? (local) | Research |
| `makemoney/` | Financial experimentation workspace. | Python + JS mix | Research |
| `context_portal/` | Context management and persistent storage research. | Python, SQLite | Research |
| `workspace-orchestrator/` | Client-server orchestration prototype. | Node.js, Next.js | Research |

## External/Collaborative (mnmballa2323)
| Path | Description | Stack / Language | Status |
| --- | --- | --- | --- |
| `Alti.Assistant/` | Mnmballa2323 mobile assistant submodule. | Mobile stack | Active |
| `Alti.Code.Studio/` | Code studio for mnmballa2323 tools. | Web IDE, TypeScript | Active |
| `Azure.Cybersecurity/` | Cybersecurity training sandbox. | .NET / Azure services | Active |
| `Chamber.Law/` | Legal platform for collaborative law workflows. | Web stack | Active |
| `Merk.Mobile/` | Mobile app for mnmballa2323 collaborations. | Flutter/React Native? | Active |
| `Stone.Ledger/` | Ledger/accounting system for partners. | SQL-backed web app | Active |
| `Tickerstone/` | Stock ticker visualization for investors. | Web dashboard | Active |
| `coin.project/` | Cryptocurrency research initiative. | Node.js + Web UI | Research |
| `cointrade/` | Cryptocurrency trading workspace. | Trading APIs + JS | Research |

## AI Agent Automation
| Path | Description | Stack / Language | Status |
| --- | --- | --- | --- |
| `antigravity-autopilot/` | Antigravity AI automation runtime. | Node.js, TypeScript | Active |
| `antigravity-jules-orchestration/` | Jules + Antigravity orchestration binding. | TypeScript, orchestrator scripts | Active |
| `jules-autopilot/` | Google Jules automation project. | Node.js, Automation APIs | Active |
| `opencode-autopilot/` | OpenCode AI automation tooling. | Node.js, TypeScript | Active |

## MCP Infrastructure
| Path | Description | Stack / Language | Status |
| --- | --- | --- | --- |
| `mcp-superassistant/` | Central MCP SuperAssistant (also `MCP_SuperAssistant/`). | TypeScript, pnpm, TRPC | Active |
| `mcpenetes/` | MCP utilities and support scripts. | TypeScript | Active |
| `metamcp/` | Proxy to MCP servers and cross-agent approval. | TypeScript | Active |

## Support & Configuration
| Path | Description | Stack / Language | Status |
| --- | --- | --- | --- |
| `docs/` | Workspace-wide documentation hub (LLM instructions, archives, handoffs). | Markdown | Active |
| `scripts/` | Automation helpers (`generate_dashboard.py`, `sync_forks.py`, `recursive_update_v2.ps1`). | Python, PowerShell | Active |
| `logs/` | Session logs and handoff artifacts. | Markdown, text | Active |
| `VERSION` | Single version source of truth. | Text | Active |
| `CHANGELOG.md` | Changelog tracking version history. | Markdown | Active |
| `ROADMAP.md` | Strategic progress notes. | Markdown | Active |
| `VISION.md` | Long-term vision. | Markdown | Active |
| `BOB_ECOSYSTEM.md` | Notes on the Bob-branded product set. | Markdown | Maintained |
| `AGENTS.md` | Agent quick-reference guide. | Markdown | Active |
| `CLAUDE.md` | Claude-specific instructions. | Markdown | Active |
| `GEMINI.md` | Gemini-specific instructions. | Markdown | Active |
| `GPT.md` | GPT-specific instructions. | Markdown | Active |
| `package.json` | Node workspace manifest. | JSON | Active |
| `pyproject.toml` | Python workspace manifest. | TOML | Active |
| `playwright.config.ts` | Playwright end-to-end test config. | TypeScript | Active |
| `codebuff.json` | Workspace generator config. | JSON | Active |
| `workspace.code-workspace` | VS Code workspace definition. | JSON | Active |
| `.gitmodules` | Submodule mapping. | Git config | Active |
| `.github/copilot-instructions.md` | Copilot guidance. | Markdown | Active |

