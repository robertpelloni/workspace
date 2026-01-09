# Workspace Vision

**Author:** Robert Pelloni  
**Last Updated:** 2026-01-09  
**Version:** 1.0

---

## Executive Summary

This workspace is a **unified development ecosystem** that consolidates all of Robert Pelloni's projects, tools, and AI infrastructure into a single monorepo. The architecture follows a clear organizational principle: **each domain has its home**, and submodules are placed where they logically belong rather than scattered at root level.

---

## Core Philosophy

### 1. Hierarchical Organization by Domain

The workspace is not a flat collection of repositories. It's a **structured hierarchy** where:

- **Root level** contains primary projects and domain containers
- **Nested submodules** belong inside their parent domain
- **No duplication** - a repo exists in exactly one logical location

### 2. Domain Ownership

| Domain | Container | Contents |
|--------|-----------|----------|
| **AI/Agents/MCP** | `aios/` | All AI agents, MCP servers, orchestration tools, OpenHands, agent frameworks |
| **Rhythm Games** | Root + `itgmania/` + `stepmania/` | Core engines at root, themes/noteskins inside their parent |
| **Game Engines** | Root + `okgame/` + `BobsGameOnline/` | Core engines at root, visualizers and plugins inside their parent |
| **Web Apps** | Root | Standalone applications |
| **Infrastructure** | Root + `aios/` | Build tools at root, AI infra in aios |
| **Crypto** | `bobcoin/` + `aios/` | Bobcoin project, with aios having its own bobcoin reference |

### 3. The AIOS Principle

`aios/` is the **AI Operating System** - the meta-orchestrator and brain of the workspace. It contains:

- **273+ nested submodules** organized by function
- **All MCP implementations** (Model Context Protocol servers)
- **All AI agent frameworks** (OpenHands, AutoGen, claude-squad, etc.)
- **Authentication providers** for AI services
- **Research and experimental AI projects**

**Key Rule:** If it's AI/agent/MCP-related and not a primary user-facing tool, it belongs in `aios/`.

---

## Organizational Rules

### What Belongs at Root Level

1. **Primary projects** you actively develop (itgmania, fwber, okgame, BobsGameOnline)
2. **Standalone applications** with their own release cycle
3. **Domain containers** (aios)
4. **Infrastructure tools** used across projects (servers, vcpkg, playwright)
5. **The bobcoin project** (primary crypto work)

### What Belongs in AIOS

1. **All MCP servers and tools** (40+ repositories)
2. **AI agent frameworks** (OpenHands, AutoGen, goose, etc.)
3. **AI orchestration tools** (claude-squad, Switchboard, etc.)
4. **AI authentication** (anthropic, openai, gemini providers)
5. **AI research projects**
6. **Plugin systems for AI tools**

### What Belongs in Parent Projects

| Item | Parent | Reasoning |
|------|--------|-----------|
| Simply-Love-SM5 (theme) | `itgmania/` or `stepmania/` | Themes belong with their game engine |
| Music visualizers (MilkDrop3, projectm) | `okgame/` or `BobsGameOnline/` | Visual plugins for game engines |
| lr2oraja variants | Not needed | Already have `beatoraja/` |
| Game-specific mods | Their respective game | Mods belong with their game |

### What Gets Removed

1. **Duplicates** - If it exists in `aios/`, don't duplicate at root
2. **Irrelevant projects** - Resume-Matcher has no place here
3. **Deprecated forks** - If upstream is better, remove the fork

---

## Project Categories

### Rhythm Games Ecosystem

The rhythm game ecosystem is a **core focus**:

```
Root Level:
├── itgmania/          # Primary: Tournament-grade StepMania fork
├── stepmania/         # Reference: Upstream StepMania
├── beatoraja/         # BMS/IIDX-style rhythm game
├── ArrowVortex/       # Simfile editor (essential tool)
├── linthesia/         # Piano learning (Synthesia-like)
├── Neothesia/         # Rust-based piano learning
└── pianogame/         # Original Synthesia source (historical)

Inside itgmania/ and stepmania/:
├── Themes/Simply-Love-SM5/   # Popular community theme
├── NoteSkins/                # Visual note styles
└── Songs/                    # Simfile packs
```

**Vision:** Build the definitive rhythm game development environment with:
- Tournament-ready game engine (itgmania)
- Professional simfile editing (ArrowVortex with DDC ML integration)
- BMS support (beatoraja)
- Piano/keyboard learning (linthesia, Neothesia)

### Game Development Ecosystem

```
Root Level:
├── okgame/            # Primary: Multiplayer puzzle engine
├── BobsGameOnline/    # Primary: 2D MMORPG
├── hellven/           # Unity game project
├── sm64coopdx/        # Super Mario 64 multiplayer
├── f-zerox/           # F-Zero X decompilation
├── mk64/              # Mario Kart 64 decompilation
├── neverball/         # Tilt ball game
├── MarbleBlast/       # Marble Blast Gold
├── OpenMBU/           # Marble Blast Ultra
└── JWildfire/         # Fractal flame editor

Inside okgame/ and BobsGameOnline/:
├── visualizers/       # MilkDrop3, projectm integrations
├── plugins/           # Game-specific extensions
└── assets/            # Shared game assets
```

**Vision:** Preserve and enhance classic games while building original titles:
- **okgame** - The flagship puzzle game engine
- **BobsGameOnline** - 2D MMORPG with Java client/server
- **Decompilations** - Preserve gaming history (sm64, f-zerox, mk64)
- **Physics games** - Marble Blast series, neverball

### AI Operating System (AIOS)

```
aios/
├── references/
│   ├── agents/        # OpenHands, claude-squad, maestro, etc.
│   ├── auth/          # anthropic, copilot, gemini, openai-codex
│   ├── config/        # Configuration templates
│   ├── mcp/           # ALL MCP implementations (40+)
│   ├── misc/          # Utilities
│   ├── plugins/       # OpenCode plugins
│   └── research/      # AI research projects
├── submodules/        # Core integrations
└── packages/          # Internal packages
```

**Vision:** Create a **self-improving AI development environment**:
- **MCP orchestration** - Coordinate multiple AI tools via Model Context Protocol
- **Agent swarms** - Multiple AI agents working together
- **Memory systems** - Persistent context across sessions (mem0, supermemory)
- **Multi-model support** - Claude, GPT, Gemini, Grok, Qwen all accessible

### Crypto (Bobcoin)

```
Root Level:
└── bobcoin/           # Proof of Health cryptocurrency

Inside aios/:
└── submodules/bobcoin/  # AIOS reference to bobcoin
```

**Vision:** Bobcoin is a **Proof of Health** cryptocurrency - a novel consensus mechanism. It has its own dedicated space and is referenced (not duplicated) where needed.

**Important:** Bobcoin references should ONLY appear in:
- `bobcoin/` - The primary project
- `aios/` - As a reference for AI integration
- NOT in unrelated projects (ArrowVortex, raindropioapp, etc.)

---

## Technical Architecture

### Submodule Strategy

1. **Shallow clones** for large repositories (topaz-ffmpeg, game decompilations)
2. **Full clones** for actively developed projects
3. **Depth 1** for reference-only repositories

### Git Operations

Due to 67+ root submodules and 273+ nested in aios:
- Use targeted commands (`git ls-files -m`) instead of `git status`
- Remove `.git/index.lock` if operations hang
- Batch submodule operations when possible

### Version Management

- Root workspace has its own VERSION file
- Each submodule maintains independent versioning
- CHANGELOG.md tracks workspace-level changes
- SUBMODULE_DASHBOARD.md tracks submodule inventory

---

## Future Roadmap

### Short-term (v1.1.0)
- [ ] Standardize build systems across C++ projects (CMake + vcpkg)
- [ ] Consolidate Node.js projects to pnpm
- [ ] Complete AIOS MCP orchestration

### Medium-term (v1.2.0)
- [ ] Unified CLI for workspace management
- [ ] Web UI for project visualization
- [ ] Automated upstream sync for all forks

### Long-term (v2.0.0+)
- [ ] Fully autonomous agent swarm
- [ ] Self-healing submodule management
- [ ] Global knowledge graph across all projects
- [ ] Cross-project feature parity automation

---

## Guiding Principles

1. **Everything has a home** - No orphan repositories at root
2. **No duplication** - One source of truth per project
3. **AI is centralized** - All AI/MCP/agent work lives in `aios/`
4. **Games are sacred** - Rhythm games and game engines are core focus
5. **History matters** - Preserve decompilations and legacy code
6. **Bobcoin is isolated** - Crypto only where it belongs
7. **Tools serve projects** - Infrastructure exists to support development

---

## Quick Reference

### Adding New Repositories

| Type | Location | Example |
|------|----------|---------|
| AI/Agent/MCP | `aios/references/` | New MCP server |
| Rhythm game theme | `itgmania/` or `stepmania/` | New theme pack |
| Game visualizer | `okgame/` or `BobsGameOnline/` | Music visualizer |
| Standalone app | Root | New web application |
| Game decompilation | Root | New N64 decomp |

### Removing Repositories

Before removing, verify:
1. Is it duplicated elsewhere? → Remove duplicate
2. Is it in the wrong location? → Move, don't remove
3. Is it truly unused? → Remove entirely

---

*This document represents the architectural vision for the workspace. All organizational decisions should align with these principles.*
