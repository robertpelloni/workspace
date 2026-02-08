# ROADMAP — Robert Pelloni Workspace Monorepo

> **Version:** 1.2.0
> **Last Updated:** 2026-02-08
> **Status Key:** ✅ Complete | 🔄 In Progress | 📋 Planned | 💡 Aspirational

---

## Current Version: v1.2.0

### Recent Milestones
- ✅ **v1.2.0** (2026-02-08) — Comprehensive documentation rewrite: all LLM instruction files, VISION.md, LIBRARY_REFERENCE.md, PROJECT_STRUCTURE.md
- ✅ **v1.1.2** (2026-02-03) — Fixed okgame libs, BobsGameOnline GeoIP2, bobfilez Local-File-Organizer
- ✅ **v1.1.0** (2026-02-02) — 250+ submodule sync, docs overhaul, dashboard automation, scripts

---

## Short-Term (v1.3.x — Next 2 Weeks)

### Documentation & Governance
- 📋 Complete docs/QUICK_START.md update to reference v1.2.0 changes
- 📋 Audit all submodules for missing documentation entries
- 📋 Verify all non-submodule dirs (brobocallz, makemoney, superbobbyball, musicbrainz-soulseek-downloader) — add as submodules or document as local-only
- 📋 Remove or repurpose the `undefined/` directory
- 📋 Deduplicate MCP_SuperAssistant vs mcp-superassistant

### Build & Infrastructure
- 📋 Enforce `src/` layout for all Python projects in workspace
- 📋 Standardize on `pnpm` for all Node.js/TypeScript projects
- 📋 Begin ITGmania CMake migration (from Autotools/Makefiles)
- 📋 Fix consensus_gate.js CI workflow (currently references potentially missing state file)
- 📋 Automate VERSION sync across package.json and pyproject.toml (build script)

### Submodule Health
- 📋 Run full `python scripts/sync_forks.py` to sync all forks with upstream
- 📋 Merge all robertpelloni feature branches (created by Jules/AI tools) into main
- 📋 Resolve all detached HEAD states in nested submodules
- 📋 Update SUBMODULE_DASHBOARD.md with all 48+ submodules accurate

---

## Medium-Term (v1.4–v1.9 — Next 1–3 Months)

### AIOS Meta-Orchestrator
- 📋 AIOS dashboard UI polish — improve Next.js frontend
- 📋 Universal MCP Hub — centralized registry for all MCP servers
- 📋 Agent orchestration improvements — better multi-agent coordination
- 📋 Progressive Disclosure UI — hide tools until needed
- 📋 Memory consolidation — unify Chroma, mem0, Serena into single memory layer

### FWBer Dating Platform
- 🔄 **Phase 4C** — Feature flags, dynamic routes, merchant analytics, real content moderation
- 📋 **Phase 5** — Subscriptions/Payments integration
- 📋 **Phase 6** — Voice/Video chat
- 📋 **Phase 7** — Community features and growth loops

### Rhythm Games
- 📋 ITGmania build system migration to CMake
- 📋 ArrowVortex Qt 5 → Qt 6 migration
- 📋 DDC auto-charter integration improvements
- 📋 Simply Love SM5 theme updates for ITGmania compatibility
- 📋 beatoraja upstream sync and improvements

### Bob Ecosystem
- 📋 bobfilez feature completion (file organization, tagging, search)
- 📋 bobcoin testnet deployment and Proof of Play prototype
- 📋 bobsaver core password management features
- 📋 bobtorrent P2P protocol design and implementation

### Developer Experience
- 📋 Unified CLI tool for workspace management (`bob` command)
- 📋 Pre-commit hooks for VERSION sync validation
- 📋 Automated session handoff file generation
- 📋 CI/CD pipeline for main workspace (not just subprojects)

---

## Long-Term (v2.0–v2.9 — 3–12 Months)

### Integration Layer
- 💡 Bobcoin Proof of Play integration with ITGmania
- 💡 Cross-project bobcoin payment layer
- 💡 bobtorrent + bobfilez distributed storage integration
- 💡 bobui shared component library across all web products
- 💡 Unified authentication across all bob products

### AIOS Agent Swarm
- 💡 Autonomous agent swarm for continuous development
- 💡 Agent marketplace for community-contributed agents
- 💡 Knowledge graph across all projects
- 💡 Multi-model consensus for architectural decisions
- 💡 Self-healing infrastructure (auto-fix failing builds/tests)

### Games
- 💡 Bob's Game (bg) modernization and Steam update
- 💡 sm64coopdx custom levels and mods
- 💡 superbobbyball gameplay completion
- 💡 "Definitive StepMania" — merge ITGmania + bobmania forks

---

## Aspirational (v3.0+ — 1+ Years)

### Bob Product Suite
- 💡 bobium browser release (de-Googled Chromium)
- 💡 bobzilla browser release (privacy Firefox)
- 💡 bobeditpro code editor
- 💡 bobzzite gaming OS (Bazzite/Fedora fork)

### The Ultimate Vision (v10.0+)
- 💡 boblang programming language
- 💡 bobvm virtual machine
- 💡 bobos operating system
- 💡 Physical arcade machines as bobcoin mining oracles
- 💡 Fully autonomous self-improving software ecosystem

---

## Completed Milestones

### v1.2.0 (2026-02-08)
- ✅ Comprehensive documentation rewrite (8 files)
- ✅ Universal LLM_INSTRUCTIONS.md master protocol (13 sections)
- ✅ VISION.md detailed vision document (14 sections)
- ✅ LIBRARY_REFERENCE.md dependency catalog
- ✅ PROJECT_STRUCTURE.md complete directory catalog
- ✅ Version sync across VERSION, package.json, pyproject.toml
- ✅ All model-specific files reference master protocol

### v1.1.x (2026-02-02 – 2026-02-03)
- ✅ 250+ submodule synchronization
- ✅ Dashboard automation scripts
- ✅ Recursive update scripts (PowerShell + Python)
- ✅ Fork sync script
- ✅ Consensus gate CI workflow

### v1.0.x (2026-01-04 – 2026-01-15)
- ✅ Monorepo structure established
- ✅ 60+ root submodules integrated
- ✅ AIOS meta-orchestrator initialized
- ✅ fwber Phase 4B complete (achievements, chatrooms, photo reveals, etc.)
- ✅ Agent orchestrator CLI
- ✅ Submodule dashboard generation

### FWBer Phase 4B (Complete)
- ✅ Achievement system with badge types
- ✅ Chatrooms
- ✅ Photo reveals
- ✅ Merchant integration
- ✅ Share-unlock mechanics
- ✅ Bulletin board
- ✅ Profile view tracking
- ✅ Group matching
- ✅ Reactions system
- ✅ Viral content mechanics
- ✅ Bounty system

---

## Priority Matrix

| Priority | Category | Next Action |
|----------|----------|------------|
| 🔴 HIGH | Submodule Health | Sync all forks, merge feature branches, fix detached HEADs |
| 🔴 HIGH | Infrastructure | Fix VERSION auto-sync, CI pipeline |
| 🟡 MEDIUM | FWBer | Phase 4C feature flags and moderation |
| 🟡 MEDIUM | AIOS | Dashboard UI, MCP Hub |
| 🟡 MEDIUM | Rhythm Games | ITGmania CMake migration |
| 🟢 LOW | Bob Ecosystem | bobcoin testnet, bobtorrent design |
| 🟢 LOW | Games | bg modernization, sm64coopdx mods |

---

*This roadmap is maintained as a living document. For the complete project vision, see `VISION.md`. For technical protocols, see `docs/LLM_INSTRUCTIONS.md`.*
