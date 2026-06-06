# Quick Start Guide

**For New Contributors & AI Agents**  
**Version:** 1.0.6  
**Last Updated:** 2026-01-09

---

## 30-Second Overview

This workspace is a **519+ submodule monorepo** containing:
- **AIOS**: AI Operating System / Meta-Orchestrator
- **Rhythm Games**: ITGMania, StepMania, ArrowVortex
- **Game Engines**: okgame, BobsGameOnline, sm64coopdx
- **Web Apps**: fwber (dating), copyparty (file server)

**Central Command**: Everything AI-related lives in `aios/`

---

## First Steps

### 1. Clone & Bootstrap

```bash
# Clone with submodules (warning: 500+ repos)
git clone --recursive https://github.com/robertpelloni/workspace.git
cd workspace

# Or shallow clone for faster setup
git clone --depth 1 https://github.com/robertpelloni/workspace.git
cd workspace
git submodule update --init --depth 1
```

### 2. Install Dependencies

```bash
# Node.js projects (pnpm required)
npm install -g pnpm
pnpm install

# Python projects
pip install uv
uv sync

# C++ projects (ITGMania, etc.)
# See individual project READMEs
```

### 3. Start AIOS Dashboard

```bash
cd aios
pnpm install
pnpm run start:all
# Dashboard: http://localhost:3000
```

---

## Directory Map

```
workspace/
├── aios/                    # 🧠 AI Brain (Meta-Orchestrator)
│   ├── packages/
│   │   ├── core/           # Fastify backend
│   │   └── ui/             # Next.js dashboard
│   ├── submodules/         # 273+ AI/MCP tools
│   └── docs/               # AI-specific docs
│
├── itgmania/               # 🎮 Tournament rhythm game
├── stepmania/              # 🎮 Modern StepMania fork
├── ArrowVortex/            # 🛠️ Simfile editor
│
├── okgame/                 # 🎮 Puzzle game engine
├── BobsGameOnline/         # 🎮 2D MMORPG
├── sm64coopdx/             # 🎮 SM64 multiplayer
│
├── fwber/                  # 🌐 Dating platform
├── filez/                  # 🛠️ File deduplication
│
├── docs/                   # 📚 Root documentation
│   ├── VISION_DOCUMENT.md  # Complete vision
│   ├── VISION_MASTER.md    # Core philosophy
│   └── QUICK_START.md      # This file
│
├── VERSION                 # Current version (1.0.6)
├── CHANGELOG.md            # Version history
└── ROADMAP.md              # Development roadmap
```

---

## Key Commands

### AIOS

| Command | Description |
|---------|-------------|
| `pnpm run start:all` | Start backend + frontend |
| `pnpm run dev` | Development mode with hot reload |
| `pnpm run build` | Production build |
| `pnpm run test` | Run test suite |

### Git (Submodules)

| Command | Description |
|---------|-------------|
| `git submodule update --init --recursive` | Initialize all submodules |
| `git submodule foreach git pull origin main` | Update all submodules |
| `git submodule status` | Check submodule states |

### Python (in aios/)

| Command | Description |
|---------|-------------|
| `uv sync` | Install Python dependencies |
| `python scripts/generate_submodules_json.py` | Regenerate submodule index |

---

## For AI Agents

### Session Protocol

1. **Always check VERSION first**: `cat VERSION`
2. **Include version in commits**: `git commit -m "v1.0.6: description"`
3. **Commit after major changes**: Don't batch everything at the end
4. **Document findings**: Update relevant docs as you work

### Where Things Live

| Task | Location |
|------|----------|
| AI/Agent/MCP work | `aios/` (ALWAYS) |
| Rhythm game changes | Root or `itgmania/`/`stepmania/` |
| Game engine work | Root or `okgame/`/`BobsGameOnline/` |
| Documentation | `docs/` or project-specific `docs/` |
| Scripts | `scripts/` |

### Anti-Patterns (Don't Do)

- ❌ Never use `taskkill` on all Node processes
- ❌ Never duplicate repos that should be submodules
- ❌ Never suppress TypeScript errors with `as any`
- ❌ Never commit without version number

### Handoff Protocol

When approaching session limits:
1. Document current state in a session note
2. List incomplete tasks
3. Commit all work-in-progress
4. Update CHANGELOG if significant changes made

---

## Project-Specific Guides

### AIOS Development

```bash
cd aios/packages/core
pnpm dev                    # Backend on :4000

cd aios/packages/ui
pnpm dev                    # Frontend on :3000
```

**Key Files:**
- `packages/core/src/index.ts` - Backend entry
- `packages/ui/src/app/` - Next.js App Router pages
- `submodules/` - External tools (don't modify directly)

### ITGMania Development

```bash
cd itgmania
# See Build/README.md for platform-specific instructions
```

**Note:** ITGMania uses Makefiles (migrating to CMake in v1.1.0)

### fwber Development

```bash
# Backend
cd fwber/fwber-backend
composer install
php artisan serve           # API on :8000

# Frontend
cd fwber/fwber-frontend
pnpm install
pnpm dev                    # UI on :3000
```

---

## Architecture Quick Reference

### AIOS Stack

```
┌─────────────────────────────────┐
│         Next.js UI (:3000)      │
├─────────────────────────────────┤
│    Fastify + Socket.io (:4000)  │
├─────────────────────────────────┤
│  Managers (Agent, Memory, MCP)  │
├─────────────────────────────────┤
│      273+ Submodule Tools       │
└─────────────────────────────────┘
```

### The Three Pillars

```
     BOBCOIN              AIOS              GAMES
        │                   │                  │
   Proof of            AI Meta-           Rhythm +
    Health            Orchestrator         Engines
        │                   │                  │
        └───────────────────┼──────────────────┘
                            │
                    UNIFIED ECOSYSTEM
```

---

## Getting Help

1. **Vision/Strategy**: `docs/VISION_DOCUMENT.md`
2. **Technical Architecture**: `aios/DESIGN.md`
3. **Integration Details**: `aios/docs/ECOSYSTEM_INTEGRATION.md`
4. **Submodule Index**: `aios/docs/SUBMODULE_INDEX.csv`
5. **Changelog**: `CHANGELOG.md`

---

## Current Sprint Focus (v1.1.0)

| Priority | Task | Status |
|----------|------|--------|
| High | Python `src/` layout standardization | 🔄 In Progress |
| High | pnpm consolidation | 🔄 In Progress |
| High | CMake migration for C++ | 📋 Planned |
| Medium | trae-agent integration | 📋 Planned |
| Medium | Upstream sync automation | 📋 Planned |

---

*Welcome to the workspace. Build something amazing.*
