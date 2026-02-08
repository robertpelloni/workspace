# VISION.md — Robert Pelloni's Unified Development Ecosystem

> **Version:** Synchronized with `VERSION` (currently 1.2.0)
> **Last Updated:** 2026-02-08
> **Author:** Robert Pelloni (@robertpelloni)

---

## Table of Contents

1. [The Big Picture](#1-the-big-picture)
2. [Philosophy](#2-philosophy)
3. [Domain Architecture](#3-domain-architecture)
4. [The AIOS Meta-Orchestrator](#4-the-aios-meta-orchestrator)
5. [The Bob Ecosystem](#5-the-bob-ecosystem)
6. [Rhythm Games](#6-rhythm-games)
7. [Game Engines & Games](#7-game-engines--games)
8. [Web Applications](#8-web-applications)
9. [Developer & Automation Tools](#9-developer--automation-tools)
10. [AI Agent Infrastructure](#10-ai-agent-infrastructure)
11. [Technology Strategy](#11-technology-strategy)
12. [Integration Architecture](#12-integration-architecture)
13. [Long-Term Roadmap](#13-long-term-roadmap)
14. [Guiding Principles](#14-guiding-principles)

---

## 1. The Big Picture

This workspace is a **centralized monorepo and orchestration hub** — a single unified repository that houses, manages, and interconnects Robert Pelloni's entire software portfolio. It spans multiple domains including artificial intelligence, rhythm games, game engines, web applications, cryptocurrency, desktop utilities, and development tooling.

The monorepo currently contains **60+ root-level submodules** and **273+ nested submodules** (primarily within the AIOS project), representing one of the most ambitious indie developer ecosystems in existence.

### What Makes This Unique

- **One Developer, Many Domains:** This isn't a company — it's one person's 20+ year vision spanning games, AI, web, crypto, and tools, unified under a coherent orchestration strategy.
- **AI-First Development:** The entire ecosystem is being built, maintained, and evolved using AI agent orchestration as a force multiplier for a single developer.
- **History Matters:** Projects like bob's game (2004–present), ArrowVortex, and ITGmania have deep histories. The monorepo preserves and continues these legacies while modernizing them.
- **Integration Over Isolation:** Everything connects. Bobcoin rewards players of ITGmania. AIOS orchestrates development of fwber. ArrowVortex creates charts for ITGmania. The ecosystem is a web, not a list.

---

## 2. Philosophy

### 2.1 Proof of Health
The foundational philosophy that ties the ecosystem together. Rather than traditional proof-of-work (which wastes energy), **Proof of Health** bridges physical activity with digital value:

- **Proof of Dance:** Arcade rhythm game machines serve as "mining oracles" — physical exertion on a dance pad generates cryptocurrency rewards.
- **Proof of Play:** Any game in the ecosystem can generate bobcoin rewards proportional to verifiable gameplay.
- **Physical/Digital Bridge:** Real-world activity (dance, exercise, play) fuels digital economy (bobcoin).
- **Anti-Hoarding:** High-velocity token design encourages spending and circulation.

### 2.2 Completeness Through Aggregation
Rather than building everything from scratch, the strategy is to **aggregate the best existing tools** and integrate them:
- Fork and improve proven open-source projects
- Unify under the "bob" brand where appropriate
- Maintain upstream compatibility for community benefit
- Let each project keep its identity while adding integration points

### 2.3 Autonomous Self-Maintenance
The ecosystem should be **self-documenting, self-testing, and self-improving** through AI agents:
- AI agents maintain documentation and dashboards automatically
- Multi-model consensus ensures quality decisions
- Continuous integration tests everything that can be tested
- Session handoff protocols ensure continuity across agent sessions

### 2.4 Sacred History
Games and tools with community adoption are **sacred** — their identity, branding, and community trust are preserved:
- ITGmania stays ITGmania (not "bobmania")
- ArrowVortex stays ArrowVortex
- StepMania upstream contributions flow back
- Community themes and content are maintained

---

## 3. Domain Architecture

The workspace is organized into distinct domains with clear boundaries:

```
C:\Users\hyper\workspace\
│
├── aios/                          # 🧠 AI BRAIN — Meta-Orchestrator (273+ nested submodules)
│
├── bobmani/                       # 🎵 RHYTHM GAMES
│   ├── itgmania/                  #   Tournament-grade StepMania fork
│   ├── bobmania/                  #   Experimental StepMania fork (5.1+)
│   ├── arrowvortex/               #   Simfile/chart editor
│   ├── beatoraja/                 #   BMS/IIDX simulator
│   ├── linthesia/                 #   Piano learning (Rust)
│   ├── pianogame/                 #   Historical piano game
│   ├── ddc/                       #   Auto-chart generation
│   ├── ddc_onset/                 #   Audio onset detection
│   ├── ffr-difficulty-model/      #   Difficulty calculation
│   ├── Simply-Love-SM5/           #   Popular SM theme
│   ├── hymnmania/                 #   Hymnal rhythm game
│   ├── ksm-v2/                    #   K-Shoot Mania clone
│   └── leraine-studio/            #   Chart editor
│
├── bobcoin/                       # 💰 PROOF OF HEALTH CRYPTO
├── bobfilez/                      # 📁 FILE ORGANIZER (Qt/C++)
├── bobsaver/                      # 🔐 PASSWORD MANAGER
├── bobtorrent/                    # 📥 P2P FILE SHARING
├── bobtrader/                     # 📊 TRADING TOOLS
├── bobui/                         # 🎨 UI COMPONENT LIBRARY
├── bobium/                        # 🌐 CHROMIUM FORK (de-Googled)
├── bobzilla/                      # 🦊 FIREFOX FORK (privacy)
├── bobeditpro/                    # ✏️ CODE EDITOR
│
├── fwber/                         # ❤️ DATING PLATFORM (Laravel 12 + Next.js)
│
├── bg/                            # 🎮 BOB'S GAME (the original)
├── sm64coopdx/                    # 🍄 SUPER MARIO 64 CO-OP
├── mk64/                         # 🏎️ MARIO KART 64 DECOMP
├── superbobbyball/                # ⚾ SUPER MONKEY BALL STYLE
│
├── raindropioapp/                 # 🔖 BOOKMARK MANAGER
├── topaz-ffmpeg/                  # 🎬 VIDEO AI + FFMPEG
├── musicbrainz-soulseek-downloader/ # 🎶 MUSIC DOWNLOADER
├── brobocallz/                    # 📞 COMMUNICATION TOOL
│
├── antigravity-autopilot/         # 🤖 AI AGENT AUTOMATION
├── antigravity-jules-orchestration/ # 🤖 JULES ORCHESTRATION
├── jules-autopilot/               # 🤖 JULES AUTOMATION
├── opencode-autopilot/            # 🤖 OPENCODE AUTOMATION
├── claude-mem/                    # 🧠 CLAUDE MEMORY
├── metamcp/                       # 🔌 META MCP PROXY
├── mcp-superassistant/            # 🔌 MCP SUPERASSISTANT
├── mcpenetes/                     # 🔧 MCP UTILITIES
├── borg/                          # 🤖 MULTI-AGENT ORCHESTRATION
│
├── Alti.Assistant/                # 📱 (mnmballa2323 - external)
├── Chamber.Law/                   # ⚖️ (mnmballa2323 - external)
├── ...                            # 📦 More mnmballa2323 projects
│
├── docs/                          # 📖 DOCUMENTATION
├── scripts/                       # ⚙️ AUTOMATION SCRIPTS
└── logs/                          # 📋 SESSION LOGS & HANDOFFS
```

### Domain Rules
1. **AI/Agent/MCP work** → ALWAYS in `aios/`
2. **Rhythm game work** → In `bobmani/` subdirectories
3. **Bob-branded products** → Root level, each in own submodule
4. **External/collaborative** → Root level, documented separately
5. **No duplication** — A repo exists in exactly ONE place
6. **Bobcoin isolation** — Crypto references stay in `bobcoin/`, never leak into other projects

---

## 4. The AIOS Meta-Orchestrator

The AI Operating System (AIOS) is the **brain of the ecosystem** — a meta-orchestrator that manages AI agents, MCP servers, tools, and cross-project coordination.

### Architecture
```
aios/
├── packages/
│   ├── core/          # Fastify v5 backend — Managers, Agents, MCP Hub
│   └── ui/            # Next.js 14 + Vite dashboard (localhost:3000)
├── submodules/        # 100+ AI tools, models, agents
├── references/        # MCP repos, research, specifications
└── docs/              # AIOS-specific documentation
```

### Key Capabilities
- **Universal MCP Hub:** Central registry for all Model Context Protocol servers
- **Progressive Disclosure:** Hides tools until needed to manage cognitive load
- **Agent Economy:** Autonomous agents develop features across all projects
- **Multi-Model Consensus:** Debate patterns across Claude, GPT, Gemini, Grok with weighted averaging
- **Swiss Army Knife Strategy:** Mount any CLI tool as a plugin (Gemini CLI, Aider, Claude Code, Goose, etc.)
- **Code Mode:** Sandboxed execution environment for safe code generation
- **Memory Orchestrator:** Persistent memory across sessions via Chroma, mem0, Serena

### Technology Stack
- **Backend:** Node.js 18+, Fastify v5, Socket.io, TRPC, SQLite/PostgreSQL
- **Frontend:** Next.js 14+, Tailwind CSS, shadcn/ui
- **Package Management:** pnpm workspaces
- **Vector Search:** pgvector/Chroma for embeddings
- **Startup:** `pnpm run start:all` → http://localhost:3000

### AIOS Submodule Categories (273+ total)
- AI Models & Inference (Ollama, llama.cpp, vLLM, etc.)
- MCP Servers (zen, serena, chroma, tavily, chrome-devtools, etc.)
- Agent Frameworks (AutoGen, Amplifier, smolagents, etc.)
- CLI Tools (aichat, claude-code, gemini-cli, goose, etc.)
- Memory & Knowledge (mem0, chroma, serena, knowledge graphs)
- Code Analysis (serena, code-indexer, ast-grep, etc.)
- Browser & Web (browser-use, playwright, puppeteer, etc.)

---

## 5. The Bob Ecosystem

The "Bob Ecosystem" is a unified product suite where all bob-branded products are interconnected through shared services and the bobcoin economic layer.

### Active Products (Code Exists)
| Product | Status | Stack | Purpose |
|---------|--------|-------|---------|
| **bobcoin** | Active | Solana, Node.js, TS | Proof of Health cryptocurrency |
| **bobfilez** | Active | Qt 6, C++ | Desktop file organizer (rebrand of filez) |
| **bobsaver** | Active | — | Password manager |
| **bg** (bob's game) | Active | Java, Gradle, Lua | 2D MMORPG — Robert's signature game |

### Initialized Products (Repos Created)
| Product | Status | Stack | Purpose |
|---------|--------|-------|---------|
| **bobtorrent** | Init | — | P2P file sharing (blockchain incentivized) |
| **bobtrader** | Init | — | Trading tools and portfolio management |
| **bobui** | Init | — | Shared UI component library |
| **bobium** | Init | Chromium | De-Googled privacy browser |
| **bobzilla** | Init | Firefox | Privacy-focused Firefox fork |
| **bobeditpro** | Init | — | Code editor |

### Planned Products (Aspirational)
| Product | Vision |
|---------|--------|
| **boblang** | Custom programming language |
| **bob++** | C++ extension/dialect |
| **bobvm** | Custom virtual machine |
| **bobuntu** | Linux distribution |
| **bobzzite** | Gaming OS (Bazzite/Fedora fork) |
| **bobos** | Custom operating system — the ultimate goal |

### Integration Architecture
```
bobcoin ←→ ALL bob products
  ↕
proof-of-play ←→ itgmania, bob's game, games
  ↕
bobtorrent ←→ bobfilez (distributed storage)
  ↕
bobui ←→ ALL products with UI
```

---

## 6. Rhythm Games

The rhythm game ecosystem is one of the most mature domains, with deep community ties and tournament-grade software.

### Two StepMania Fork Strategy

#### ITGmania (Stable Fork)
- **Base:** StepMania 3.95 (arcade-proven)
- **Target:** Arcade cabinets, tournaments, competitive play
- **Key Features:** NotITG Lua/Mod support, tournament features, legacy compatibility
- **Philosophy:** Stability over features — this is what players trust on cabinets
- **Community:** Active tournament scene, dedicated player base

#### StepMania Experimental Fork (bobmania)
- **Base:** StepMania 5.1+ (modern codebase)
- **Target:** Home users, online players, experimental features
- **Key Features:** Modernization, global ranking, DDR A feature parity
- **Long-Term:** Eventual merge into "Definitive StepMania" combining both forks

### Supporting Tools
| Tool | Purpose | Stack |
|------|---------|-------|
| **ArrowVortex** | Simfile/chart editor (Robert's creation) | Qt/C++ |
| **DDC** | Automatic chart generation from audio | Python |
| **DDC Onset** | Audio onset detection for DDC | Python |
| **FFR Difficulty Model** | Chart difficulty calculation | Python |
| **Simply Love SM5** | Most popular StepMania theme | Lua |
| **Leraine Studio** | Alternative chart editor | — |

### Other Rhythm Games
| Game | Purpose | Stack |
|------|---------|-------|
| **beatoraja** | BMS/IIDX simulator (Japanese arcade) | Java, libGDX |
| **linthesia** | Piano learning game | Rust |
| **pianogame** | Historical Synthesia-like | C++ |
| **hymnmania** | Hymnal rhythm game | — |
| **ksm-v2** | K-Shoot Mania clone | — |

---

## 7. Game Engines & Games

### bob's game (bg/)
Robert Pelloni's signature project — a 2D MMORPG that has been in development since 2004. One of the longest-running indie game projects in history.
- **Stack:** Java, Gradle, Lua scripting
- **History:** Originally for Nintendo DS, then Steam, now modernized
- **Integration:** Players earn bobcoin through gameplay (Proof of Play)

### Other Games
| Game | Purpose | Stack |
|------|---------|-------|
| **sm64coopdx** | Super Mario 64 co-op multiplayer | C (N64 decomp) |
| **mk64** | Mario Kart 64 decompilation | C (N64 decomp) |
| **superbobbyball** | Super Monkey Ball style game | — |
| **okgame** | Cross-platform puzzle game engine | C++ |

### Historical/Reference Games (in AIOS or archived)
- **hellven** — Unity game
- **neverball** — Open source marble game
- **MarbleBlast/OpenMBU** — Marble Blast Ultra reimplementation
- **JWildfire** — Fractal flame generator
- **f-zerox** — F-Zero X decompilation

---

## 8. Web Applications

### FWBer (fwber/)
A **dating platform** built with a modern full-stack architecture:

- **Backend:** Laravel 12, PHP 8.3, Sanctum authentication
- **Frontend:** Next.js, Tailwind CSS
- **Architecture:** Strict API-first, RESTful, Service Layer pattern, DTOs
- **Database:** MySQL with spatial queries for proximity matching
- **Key Features:**
  - Avatar Mode (privacy-first matching)
  - Real-time communication via WebSockets
  - Achievement system
  - Photo reveals and group matching
  - Merchant integration and bulletins
- **AI Scope (Minimal):** Avatar generation, basic matching, profile suggestions, content moderation
- **NOT an AI product** — AI orchestration is development tooling only, not user-facing features

### robertpelloni.com
Personal website and portfolio.

---

## 9. Developer & Automation Tools

| Tool | Purpose | Why Selected |
|------|---------|-------------|
| **raindropioapp** | Bookmark/link management | Research and reference organization |
| **topaz-ffmpeg** | Video AI + FFmpeg integration | Video processing pipeline |
| **musicbrainz-soulseek-downloader** | Music metadata + P2P download | Music library management |
| **brobocallz** | Communication tool | Voice/messaging utility |
| **copyparty** | File sharing server | Quick file distribution |
| **ccmanager** | Container/config management | DevOps tooling |
| **changesets** | Monorepo version management | Coordinated releases |

---

## 10. AI Agent Infrastructure

### Agent Automation Repos
These repos automate AI coding workflows:

| Repo | Purpose |
|------|---------|
| **antigravity-autopilot** | Antigravity (this tool) automation scripts |
| **antigravity-jules-orchestration** | Coordinating Jules + Antigravity workflows |
| **jules-autopilot** | Google Jules AI automation |
| **opencode-autopilot** | OpenCode AI automation |
| **claude-mem** | Claude persistent memory management |
| **borg** | Multi-agent orchestration framework |

### MCP Infrastructure
| Repo | Purpose |
|------|---------|
| **metamcp** | Meta MCP proxy for routing between servers |
| **mcp-superassistant** | MCP SuperAssistant UI/tools |
| **mcpenetes** | MCP utility functions and helpers |

### Multi-Model Consensus
The workspace uses a **multi-model consensus** approach for critical decisions:
- **Claude:** Architecture, planning, documentation
- **Gemini:** Speed, performance, large-context analysis
- **GPT:** Code generation, testing, algorithms
- **Grok:** Creative solutions, alternative perspectives
- Weighted tier averaging ensures no single model dominates decisions

---

## 11. Technology Strategy

### Languages & Frameworks
| Domain | Primary Stack | Secondary |
|--------|--------------|-----------|
| AI/Orchestration | TypeScript, Node.js, Python | Rust, Go |
| Rhythm Games | C++ (CMake/Autotools) | Lua (scripting) |
| Game Engines | C++, Java, C | Lua, Python |
| Web (Backend) | PHP 8.3 (Laravel 12) | Node.js (Fastify) |
| Web (Frontend) | Next.js, React, Tailwind | — |
| Desktop Tools | Qt/C++ | Electron |
| Crypto | Solana, TypeScript | — |
| Piano Games | Rust, C++ | — |

### Package Management Strategy
- **Node.js:** Standardize on `pnpm` (faster, efficient disk usage)
- **Python:** Use `uv` as primary (fast), `pip` as fallback
- **C++:** `vcpkg` for dependencies, CMake for builds
- **Java:** Gradle

### Build System Migration Plan
- **ITGmania:** Migrate from Makefiles/Autotools → CMake
- **AIOS:** Consolidate on pnpm workspaces
- **Python projects:** Standardize on `src/` layout with pyproject.toml

---

## 12. Integration Architecture

### Cross-Project Connections
```
┌─────────────────────────────────────────────────┐
│                    AIOS                          │
│            (Meta-Orchestrator)                   │
│                                                  │
│  Manages development of ALL projects             │
│  via AI agents, MCP servers, tools               │
└──────┬───────┬───────┬───────┬───────┬──────────┘
       │       │       │       │       │
       ▼       ▼       ▼       ▼       ▼
   ┌──────┐┌──────┐┌──────┐┌──────┐┌──────┐
   │fwber ││rhythm││games ││bob   ││tools │
   │      ││games ││      ││eco   ││      │
   └──────┘└──┬───┘└──┬───┘└──┬───┘└──────┘
              │       │       │
              ▼       ▼       ▼
         ┌─────────────────────────┐
         │       BOBCOIN           │
         │   (Economic Layer)      │
         │                         │
         │ Proof of Dance/Play     │
         │ Rewards for all games   │
         │ Payment for services    │
         └─────────────────────────┘
```

### Data Flow
1. **AIOS** orchestrates development across all projects
2. **ArrowVortex** creates charts → **ITGmania** plays them
3. **DDC** auto-generates charts → feeds into ITGmania/StepMania
4. **Games** generate Proof of Play → **bobcoin** rewards players
5. **bobtorrent** distributes content ← **bobfilez** organizes it
6. **bobcoin** provides payment layer for all bob products

---

## 13. Long-Term Roadmap

### Phase 1: Foundation (v1.0–v1.2) — CURRENT
- ✅ Monorepo structure established
- ✅ 60+ root submodules integrated
- ✅ AIOS meta-orchestrator initialized
- ✅ Documentation framework in place
- ✅ AI agent automation operational
- ✅ fwber Phase 4B complete
- 🔄 Submodule cleanup and synchronization
- 🔄 Documentation comprehensive rewrite

### Phase 2: Consolidation (v1.3–v1.9)
- Standardize build systems (CMake, pnpm, uv)
- Enforce src/ layout for all Python projects
- Complete fwber Phase 4C (feature flags, moderation)
- ITGmania CMake migration
- AIOS dashboard UI polish
- Unified CLI for workspace management

### Phase 3: Integration (v2.0–v2.9)
- Bobcoin Proof of Play integration with ITGmania
- AIOS agent swarm for autonomous development
- Cross-project bobcoin payment layer
- bobtorrent + bobfilez distributed storage
- bobui shared component library across all web products

### Phase 4: The Bob Ecosystem (v3.0+)
- bobium browser release
- bobzilla browser release
- bobeditpro code editor
- bobzzite gaming OS
- Full bob product suite operational

### Phase 5: The Ultimate Vision (v10.0+)
- boblang programming language
- bobvm virtual machine
- bobos operating system
- Fully autonomous self-improving software ecosystem
- All bob products dominate their categories
- Physical arcade machines as bobcoin mining oracles worldwide

---

## 14. Guiding Principles

1. **One Developer, Infinite Ambition:** This is Robert Pelloni's life work. Every project serves the larger vision, even if the timeline spans decades.

2. **AI as Force Multiplier:** AI agents don't replace the developer — they amplify one person into an army. The AI builds, tests, documents, and maintains while Robert architects and directs.

3. **Quality Through Community:** Fork the best, contribute back, maintain upstream compatibility. The open-source community is a partner, not a resource to exploit.

4. **History is Sacred:** bob's game, ArrowVortex, ITGmania — these projects have histories and communities. They are preserved and honored, not discarded or recklessly rebranded.

5. **Integration Creates Value:** A file organizer alone is a commodity. A file organizer that syncs with P2P sharing, earns crypto, and integrates with a gaming OS — that's an ecosystem.

6. **Ship, Then Perfect:** Version numbers go up, not promises. Working software today beats perfect software never.

7. **Document Everything:** If it's not documented, it doesn't exist. Every decision, every library choice, every integration point is recorded for future sessions and future agents.

8. **Never Stop:** Autonomy mandate applies to humans too. Fix the bug, ship the feature, merge the branch, move on. Momentum is everything.

---

*This document is the definitive vision statement for Robert Pelloni's unified development ecosystem. It is maintained as a living document and updated whenever strategic direction changes. For technical protocols, see `docs/LLM_INSTRUCTIONS.md`. For current priorities, see `ROADMAP.md`.*
