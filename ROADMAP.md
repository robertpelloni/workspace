# Project Roadmap

## Current Status (v1.0.6)
- [x] **Git Repair**: Fixed recursive submodule definitions (`aios`, `bobcoin`, `filez`) and resolved merge conflicts.
- [x] **Agent Setup**: Installed and verified `trae-agent` (local), `ii-agent` (local), and `junie` (global).
- [x] **Inventory**: Generated comprehensive `SUBMODULE_DASHBOARD.md` listing 82 root submodules (273+ nested in aios).
- [x] **Structure Analysis**: Created `AGENTS.md` identifying project-specific conventions and deviations.
- [x] **Game Submodules**: Added linthesia, hellven, sm64coopdx, f-zerox, neverball, mk64, MarbleBlast, OpenMBU game engines.
- [x] **Music Tools**: Added ardour, audacity, picard, qBittorrent, zrythm, lmms, timidity.
- [x] **Visualizers**: Added JWildfire, apophysis-j, electricsheep, bonsai fractal/visualization tools.
- [x] **Video Tools**: Added topaz-ffmpeg (TopazLabs AI video enhancement fork).
- [x] **Bobcoin Cleanup**: Removed inappropriate crypto references from non-crypto projects (ArrowVortex, raindropioapp).
- [x] **Documentation**: Created session handoffs, updated CHANGELOG, synchronized VERSION.

## Discovered Forgotten Features (Audit 2026-01-09)

### 🔴 Critical Priority (fwber - Backend Complete, Frontend Missing)
- [ ] **Achievements System** - Gamification UI needed (`fwber/docs/MISSING_FEATURES.md`)
- [ ] **Proximity Chatrooms** - Core social feature partially implemented
- [ ] **Paid Photo Reveals** - Monetization feature
- [ ] **Merchant Promotions Discovery** - Local commerce integration

### 🟡 High Priority
- [ ] **Share-to-Unlock System** - Viral growth mechanism
- [ ] **Bulletin Boards** - Community discussion (routes commented out in fwber)
- [ ] **Profile View Tracking** - "Who viewed you" feature
- [ ] **AI Wingman Chat Suggestions** - Phase 4 roadmap item

### 🟢 Medium Priority
- [ ] **Content Unlock System** - Flexible monetization
- [ ] **Group-to-Group Matching** - Group dynamics feature
- [ ] **Message Reactions** - Modern messaging UX
- [ ] **Extended Viral Content** - Fortunes, cosmic matches
- [ ] **Bobcoin Mining Integration** - aios Phase 6 (`aios/ROADMAP.md`)
- [ ] **Video Deduplication** - filez Tier 3 (`filez/docs/VISION.md`)

### 🔵 Low Priority
- [ ] **Download Accelerator** - copyparty enhancement
- [ ] **Config GUI** - copyparty web configuration
- [ ] **AI Sorter Userscript** - raindropioapp integration
- [ ] **Infrastructure Automation** - CI/CD improvements

## Short-term Goals (v1.1.0)
- [ ] **Standardization**:
    - [ ] Enforce `src/` layout for new Python modules in `aios`.
    - [ ] Consolidate Node.js projects to use `pnpm` exclusively.
- [ ] **Build Unification**:
    - [ ] Migrate legacy Makefiles in `ITGMania` to CMake where feasible.
    - [ ] Standardize `vcpkg` integration across C++ projects.
- [ ] **Agent Orchestration**:
    - [ ] Integrate `trae-agent` into the central orchestration loop.
    - [ ] Establish communication protocol between `ii-agent` and `aios`.
- [ ] **Submodule Sync**:
    - [ ] Merge upstream changes for all forked repositories.
    - [ ] Add mk64 (Mario Kart 64 decompilation) when available.

## Medium-term Goals (v1.2.0)
- [ ] **Unified Interface**: Create a CLI or Web UI wrapper that exposes key functionalities of the underlying submodules.
- [ ] **Performance Optimization**: Analyze and optimize the build and update process for the large number of submodules.
- [ ] **AIOS Integration**: Complete MCP server orchestration with mcp_zen consensus and mcp_chroma vector memory.

## Long-term Vision (v2.0.0+)
- [ ] **Fully Autonomous Agent Swarm**: Enable agents to self-update, self-heal, and collaborate on complex tasks without human intervention.
- [ ] **Marketplace Integration**: Allow dynamic addition/removal of capabilities via an extension marketplace.
- [ ] **Global Knowledge Graph**: Implement a shared memory structure accessible by all agents.
- [ ] **Cross-Project Feature Parity**: Integrate best features from all competing libraries into unified interfaces.

---

## Reference Documents
- `fwber/docs/MISSING_FEATURES.md` - Detailed fwber feature gaps
- `fwber/docs/ROADMAP.md` - fwber Phase 4-5 plans
- `aios/ROADMAP.md` - AIOS Phase 6-7 plans
- `filez/docs/VISION.md` - filez Tier 3 features
- `docs/archive/AI_FEATURES_CONSENSUS_PLAN_2025-11-08.md` - Multi-model consensus roadmap
