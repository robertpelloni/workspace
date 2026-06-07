# The Complete Vision of Robert Pelloni's Workspace

**Author:** Robert Pelloni  
**Document Version:** 1.0  
**Last Updated:** 2026-01-09  
**Status:** Canonical Reference

---

## Executive Summary

This workspace represents a **unified development ecosystem** spanning 519+ submodules across multiple domains: AI orchestration, rhythm games, game engines, web applications, cryptocurrency, and developer tools. At its heart lies a singular vision: **bridging the physical and digital worlds through health, gaming, and autonomous AI systems**.

The three pillars of this vision are:

2. **AIOS** — An AI Operating System that orchestrates all development and tools
3. **The Game Ecosystem** — Rhythm games and engines that serve as both entertainment and mining infrastructure

---

## Part I: The Philosophy

### 1.1 Proof of Health: The Core Innovation



**How It Works:**
- **Mining Oracles**: Arcade dance machines and exercise equipment verify physical exertion
- **High-Velocity Economy**: Anti-hoarding design keeps tokens flowing through the community
- **Physical/Digital Bridge**: Real-world activity generates digital value

**Technical Foundation:**
- Privacy layer based on Monero/Solana for speed + anonymity
- Arcade machines double as Tor nodes, distributed storage (MegaTorrents), and game servers

### 1.2 Completeness via Aggregation

The AI ecosystem is fragmented. Dozens of competing tools (Claude, GPT, Gemini, Aider, etc.) each excel at different tasks. Rather than compete, we **aggregate**.

> "In a fragmented AI ecosystem, we solve fragmentation by aggregating best-in-class tools into a single orchestration layer."

**The Game Engine Philosophy:**
Like Unity or Unreal abstracts away platform differences, AIOS abstracts AI tools:
- **Abstraction Layers**: Standard interfaces for Memory, Agent, and Tool
- **Adapters**: Thin wrappers around submodules (mem0, claude-code, aider)
- **Hot-Swappability**: Swap components without changing the interface

### 1.3 Hierarchical Organization

Every project has a logical home. The workspace follows strict organizational principles:

| Domain | Container | Contents |
|--------|-----------|----------|
| **AI/Agents/MCP** | `aios/` | All AI agents, MCP servers, orchestration tools |
| **Rhythm Games** | Root + `itgmania/` + `stepmania/` | Core engines at root, themes inside parent |
| **Game Engines** | Root + `okgame/` + `BobsGameOnline/` | Engines at root, plugins inside parent |
| **Web Applications** | Root | Standalone applications (fwber, copyparty) |

**Guiding Principles:**
1. Everything has a home — no orphan repositories
2. No duplication — one source of truth per project
3. AI is centralized — all AI/MCP/agent work lives in `aios/`
4. Games are sacred — rhythm games and engines are core focus
5. History matters — preserve decompilations and legacy code

---

## Part II: The Architecture

### 2.1 AIOS: The AI Operating System

AIOS is the **central nervous system** of the workspace — a Meta-Orchestrator for the Model Context Protocol (MCP).

```
┌─────────────────────────────────────────────────────────────────┐
│                         AIOS (Brain)                            │
├─────────────────────────────────────────────────────────────────┤
│  ┌───────────────┐  ┌───────────────┐  ┌───────────────┐       │
│  │   Universal   │  │   Progressive │  │    Agent      │       │
│  │     Hub       │  │   Disclosure  │  │   Economy     │       │
│  └───────────────┘  └───────────────┘  └───────────────┘       │
│                                                                  │
│  ┌───────────────────────────────────────────────────────────┐  │
│  │                    Hub/Proxy/Router                        │  │
│  │  ┌─────────┐  ┌─────────┐  ┌─────────┐  ┌─────────┐      │  │
│  │  │ Fastify │  │Socket.io│  │  TRPC   │  │Next.js  │      │  │
│  │  │ Backend │  │ Realtime│  │   API   │  │Dashboard│      │  │
│  │  └─────────┘  └─────────┘  └─────────┘  └─────────┘      │  │
│  └───────────────────────────────────────────────────────────┘  │
│                                                                  │
│  ┌─────────────────────────────────────────────────────────────┐│
│  │                      273+ Submodules                        ││
│  │  agents/ | auth/ | plugins/ | mcp/ | research/ | tools/    ││
│  └─────────────────────────────────────────────────────────────┘│
└─────────────────────────────────────────────────────────────────┘
```

**Core Components:**

| Component | Purpose |
|-----------|---------|
| **Universal Hub** | Aggregates tools from local MCP servers, remote instances, internal capabilities |
| **Progressive Disclosure** | Hides tools until needed (100k → 2k tokens context savings) |
| **Agent Executor** | ReAct loop for autonomous agents defined in JSON schemas |
| **Memory Orchestrator** | Multi-provider memory (local, cloud, browser) with semantic search |
| **Code Mode** | Sandboxed execution for complex workflows |

### 2.2 The Swiss Army Knife Strategy

Instead of building one tool, we orchestrate many. AIOS acts as the "Motherboard" that mounts CLI tools as plugins:

| CLI Tool | Primary Strength | Integration Role |
|----------|------------------|------------------|
| **Gemini CLI** | Google ecosystem, multimodal | Default Gemini driver |
| **Aider** | SOTA code editing, Repo Map | Complex refactoring |
| **Claude Code** | Anthropic integration | Claude model tasks |
| **Goose** | Developer-centric agent | Autonomous dev tasks |
| **KiloCode** | Memory Bank architecture | Long-term project state |
| **Fabric** | Patterns for wisdom extraction | Summarization, analysis |
| **Amp** | Oracle + Librarian | Deep reasoning, search |

**Feature Parity Goals:**
- **Oracle Tool**: Route complex queries to reasoning models (o1/r1)
- **Librarian Tool**: Query external repos via GitHub search
- **Toolboxes**: Drop scripts into `.aios/toolbox/` for auto-registration
- **Repo Map**: AST-based repository mapping (inspired by Aider)

### 2.3 Multi-Model Consensus

Critical decisions shouldn't rely on a single model. AIOS implements debate patterns:

```
┌─────────────────────────────────────────────────────────────┐
│                    Consensus Engine                          │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│   ┌─────────┐    ┌─────────┐    ┌─────────┐                │
│   │ Claude  │    │  GPT    │    │ Gemini  │                │
│   │  4.5    │    │   5.2   │    │  2.5    │                │
│   └────┬────┘    └────┬────┘    └────┬────┘                │
│        │              │              │                      │
│        └──────────────┼──────────────┘                      │
│                       ▼                                      │
│              ┌────────────────┐                             │
│              │   Debate &     │                             │
│              │   Consensus    │                             │
│              └────────────────┘                             │
│                       │                                      │
│                       ▼                                      │
│              ┌────────────────┐                             │
│              │ Final Output   │                             │
│              └────────────────┘                             │
└─────────────────────────────────────────────────────────────┘
```

---

## Part III: The Ecosystem

### 3.1 Rhythm Games: The Mining Infrastructure


```
Rhythm Game Ecosystem
├── itgmania/              # Tournament-grade StepMania fork (stable)
├── beatoraja/             # BMS/IIDX-style rhythm game
├── ArrowVortex/           # Professional simfile editor
│   └── DDC Integration    # ML-powered auto-charting
├── linthesia/             # Piano learning (Synthesia-like)
├── Neothesia/             # Rust-based piano learning
└── pianogame/             # Original Synthesia source (historical)
```

**ITGMania** = Stability, tournament play, cabinet performance  
**ArrowVortex** = Content creation, ML-assisted charting, Lua scripting

### 3.2 Game Development Ecosystem

Beyond rhythm games, the workspace preserves gaming history and builds new experiences:

```
Game Engines & Preservation
├── okgame/                # Flagship multiplayer puzzle engine
├── BobsGameOnline/        # 2D MMORPG (Java client/server)
├── hellven/               # Unity game project
├── sm64coopdx/            # Super Mario 64 multiplayer
├── f-zerox/               # F-Zero X decompilation
├── mk64/                  # Mario Kart 64 decompilation
├── neverball/             # Tilt ball physics game
├── MarbleBlast/           # Marble Blast Gold
├── OpenMBU/               # Marble Blast Ultra
└── JWildfire/             # Fractal flame editor
```

**Philosophy**: Preserve gaming history through decompilations while building original titles.

### 3.3 Web Applications

Production-ready applications demonstrating the full stack:

| Project | Description | Stack |
|---------|-------------|-------|
| **fwber** | Privacy-first dating platform with AI avatars | Laravel 12 + Next.js 14 |
| **copyparty** | Multi-protocol file server | Python |
| **robertpelloni.com** | Personal portfolio | Web |

### 3.4 Developer Tools

Infrastructure supporting the entire ecosystem:

| Tool | Purpose |
|------|---------|
| **filez** | Cross-platform file deduplication with perceptual hashing |
| **ccmanager** | AI coding session manager across Git worktrees |
| **changesets** | Versioning and changelog automation |
| **supertorrent** | BitTorrent tracker implementation |
| **topaz-ffmpeg** | AI video enhancement (TopazLabs fork) |

---

## Part IV: The Roadmap

### 4.1 Completed Milestones (v1.0.0 → v1.0.6)

✅ **Foundation**
- Monorepo structure with pnpm workspaces
- Core service (Fastify + Socket.io)
- UI shell (Next.js App Router)
- Basic managers (Agents, Skills, Hooks, Prompts)

✅ **Enhancement**
- Universal LLM instructions
- Documentation consolidation
- Versioning system (VERSION, CHANGELOG, sync scripts)
- Submodule status dashboard

✅ **Multi-Platform**
- CLI wrapper for Claude/Gemini orchestration
- VSCode extension
- Chrome extension

✅ **Advanced Features**
- Multi-CLI orchestration (PipelineTool)
- RAG with VectorStore + MemoryManager
- Agent execution via ReAct loop
- Code Mode sandbox

✅ **Intelligence & Autonomy**
- Memory consolidation
- Autonomous loops (LoopManager)
- Deep research agent
- Auth & security

✅ **Economy Integration**
- Node Manager (Tor, Torrent, Storage)
- Miner CLI (`super-ai mine`)
- Physical mining (Serial/GPIO for "Proof of Dance")

### 4.2 Short-Term Goals (v1.1.0)

| Goal | Status | Details |
|------|--------|---------|
| Python standardization | 🔄 | Enforce `src/` layout in aios |
| Node.js consolidation | 🔄 | Use pnpm exclusively |
| CMake migration | 🔄 | Move ITGMania from Makefiles |
| vcpkg integration | 🔄 | Standardize C++ dependencies |
| trae-agent integration | 🔄 | Central orchestration loop |
| ii-agent communication | 🔄 | Protocol with aios |

### 4.3 Medium-Term Goals (v1.2.0)

- **Unified CLI/Web UI**: Single interface for all workspace functionalities
- **Performance optimization**: Build/update process for 500+ submodules
- **MCP orchestration**: Complete mcp_zen consensus + mcp_chroma vector memory
- **Upstream sync automation**: Keep all forks current

### 4.4 Long-Term Vision (v2.0.0+)

```
┌─────────────────────────────────────────────────────────────────┐
│                    THE ULTIMATE VISION                          │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │            Fully Autonomous Agent Swarm                  │   │
│  │   • Self-updating agents                                 │   │
│  │   • Self-healing systems                                 │   │
│  │   • Collaborative task execution                         │   │
│  │   • No human intervention required                       │   │
│  └─────────────────────────────────────────────────────────┘   │
│                            │                                    │
│                            ▼                                    │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │              Global Knowledge Graph                      │   │
│  │   • Shared memory across all agents                      │   │
│  │   • Cross-project intelligence                           │   │
│  │   • Semantic understanding of entire workspace           │   │
│  └─────────────────────────────────────────────────────────┘   │
│                            │                                    │
│                            ▼                                    │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │            Extension Marketplace                         │   │
│  │   • Dynamic capability addition                          │   │
│  │   • Community-contributed tools                          │   │
│  │   • One-click integration                                │   │
│  └─────────────────────────────────────────────────────────┘   │
│                            │                                    │
│                            ▼                                    │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │         Cross-Project Feature Parity                     │   │
│  │   • Best features from all libraries unified             │   │
│  │   • Automatic capability discovery                       │   │
│  │   • Zero-config integration                              │   │
│  └─────────────────────────────────────────────────────────┘   │
│                                                                  │
└─────────────────────────────────────────────────────────────────┘
```

---

## Part V: Integration Strategies

### 5.1 Browser Connectivity
- **Foundation**: MCP-SuperAssistant codebase
- **Goal**: AIOS interacts directly with web pages and browser events
- **Implementation**: WebSocket/StreamingHTTP server

### 5.2 Data Sources
- **NotebookLM**: Direct data source via MCP
- **VoiceMode**: Voice coding capabilities
- **Memory Systems**: mem0, cognee, supermemory integration

### 5.3 Autonomous Agents
- **mux**: Jules-like interface for long-running tasks
- **smolagents**: Cloud/local agentic development loops
- **OpenHands**: Full autonomous coding agent

### 5.4 Protocol Standards
- **MCP**: Model Context Protocol for tool communication
- **A2A**: Agent-to-Agent protocol for external agent communication
- **ACP**: Agent Communication Protocol

---

## Part VI: The Unified Experience

### What Success Looks Like

**For a Developer:**
1. Open terminal, run `aios start`
2. Dashboard shows all 519 submodules, health status, agent activity
3. Ask: "Refactor the authentication in fwber"
4. AIOS dispatches Aider for code changes, Claude for review, Gemini for tests
5. Multi-model consensus validates the changes
6. Automatic commit, PR creation, deployment

**For a Gamer:**
1. Step on dance pad connected to ITGMania cabinet
2. Play songs, burn calories
3. Arcade machine validates physical exertion
5. Tokens usable in BobsGameOnline MMORPG economy
6. Cabinet simultaneously serves as Tor node and game server

**For the Ecosystem:**
1. Self-healing: Agents detect broken submodules, create PRs to fix
2. Self-improving: Knowledge graph grows with every interaction
3. Self-expanding: Marketplace discovers and integrates new tools
4. Self-documenting: All changes logged, versioned, searchable

---

## Appendix A: Project Inventory

### Root-Level Projects (Primary)

| Project | Type | Status | Description |
|---------|------|--------|-------------|
| aios | AI/Orchestration | Active | Meta-Orchestrator for MCP |
| itgmania | Rhythm Game | Active | Tournament-grade StepMania fork |
| ArrowVortex | Tool | Active | Simfile editor with ML |
| okgame | Game Engine | Active | Multiplayer puzzle engine |
| BobsGameOnline | Game | Active | 2D MMORPG |
| fwber | Web App | Active | Privacy-first dating platform |
| filez | Tool | Active | File deduplication engine |
| hellven | Game | Active | Unity game project |

### AIOS Submodule Categories

| Category | Count | Examples |
|----------|-------|----------|
| MCP Servers | 40+ | metamcp, mcpenetes, mcp-shark |
| AI Agents | 30+ | OpenHands, claude-squad, goose |
| Auth Providers | 10+ | anthropic, openai, gemini |
| Plugins | 20+ | opencode-plugins, skills |
| Research | 15+ | OpenCoder, OpenCodeEval |
| CLI Tools | 10+ | aider, gemini-cli, kilocode |

---

## Appendix B: Technical Specifications

### Backend Stack
- **Runtime**: Node.js 18+
- **Framework**: Fastify v5
- **Realtime**: Socket.io
- **API**: TRPC
- **Database**: SQLite (local), PostgreSQL (production)
- **Vector Store**: pgvector, Chroma

### Frontend Stack
- **Framework**: Next.js 14+ (App Router)
- **Styling**: Tailwind CSS
- **Components**: shadcn/ui
- **State**: React Context + hooks

### Build Systems
- **Monorepo**: pnpm workspaces
- **C++**: CMake + vcpkg
- **Python**: uv, pip
- **Versioning**: Unified VERSION file + CHANGELOG

---

## Appendix C: Glossary

| Term | Definition |
|------|------------|
| **AIOS** | AI Operating System — the meta-orchestrator |
| **MCP** | Model Context Protocol — standard for AI tool communication |
| **Progressive Disclosure** | Hiding tools until needed to save context |
| **Swiss Army Knife** | Strategy of aggregating CLI tools rather than competing |
| **Mining Oracle** | Arcade machine that verifies physical exertion |
| **ReAct Loop** | Reasoning + Acting pattern for autonomous agents |
| **Hub/Proxy/Router** | Core architecture pattern of AIOS |

---

*This document represents the complete vision for the workspace. All development decisions should align with these principles and goals.*

**Document Hash**: Generated 2026-01-09  
**Next Review**: Upon reaching v2.0.0 milestone
