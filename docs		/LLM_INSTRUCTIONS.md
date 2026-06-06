# Unified LLM Instructions — Master Protocol

> **Version:** Synchronized with `VERSION` file (currently 1.2.0)
> **Last Updated:** 2026-02-08
> **Owner:** Robert Pelloni (@robertpelloni)
> **Scope:** ALL AI models/agents working on this monorepo

---

## Table of Contents

1. [Overview & Vision](#1-overview--vision)
2. [Core Mandates](#2-core-mandates)
3. [Versioning Protocol](#3-versioning-protocol)
4. [Submodule Management Protocol](#4-submodule-management-protocol)
5. [Branch & Fork Management](#5-branch--fork-management)
6. [Git Workflow](#6-git-workflow)
7. [Documentation Protocol](#7-documentation-protocol)
8. [Session Protocol](#8-session-protocol)
9. [Model-Specific Roles](#9-model-specific-roles)
10. [Project Taxonomy](#10-project-taxonomy)
11. [Library & Dependency Reference](#11-library--dependency-reference)
12. [Anti-Patterns](#12-anti-patterns)
13. [Quick Reference Card](#13-quick-reference-card)

---

## 1. Overview & Vision

This workspace is **Robert Pelloni's unified development ecosystem** — a centralized monorepo and orchestration hub managing 60+ root-level submodules and 273+ nested submodules across multiple domains:

- **AI/Agents/MCP** — The AIOS meta-orchestrator (`aios/`)
- **Rhythm Games** — ITGmania, StepMania, ArrowVortex, beatoraja, and more (`bobmani/`)
- **Game Engines & Games** — okgame, Bob's Game Online, sm64coopdx, mk64, and more
- **Web Applications** — FWBer (dating platform), robertpelloni.com
- **Bob Ecosystem** — bobcoin, bobfilez, bobsaver, bobtorrent, bobui, bobium, bobzilla, and more
- **Developer Tools** — filez, raindropioapp, copyparty, ccmanager
- **External/Collaborative** — mnmballa2323 projects (Chamber.Law, Stone.Ledger, etc.)

**Ultimate Vision:** A highly autonomous, self-maintaining, and self-improving software ecosystem where AI agents seamlessly collaborate to build, test, deploy, and document complex software across all domains. See `VISION.md` for the complete vision document.

---

## 2. Core Mandates

### 2.1 Autonomy
- **Proceed autonomously** for as long as possible. Do not ask for confirmation unless a critical, irreversible destructive action is about to be taken.
- Complete a feature → commit → push → continue to the next feature **without stopping**.
- Fix errors encountered along the way and continue. Do not halt on non-critical errors.
- If approaching session/context limits, initiate the **Session Handoff Protocol** (§8).

### 2.2 Conventions
- Rigorously adhere to existing project conventions. **Analyze surrounding code first.**
- Follow language-specific standards: PSR-12 (PHP), Prettier (JS/TS), PEP 8 (Python), project-specific (C++).
- Use Conventional Commits: `feat:`, `fix:`, `docs:`, `style:`, `refactor:`, `test:`, `chore:`.

### 2.3 Testing
- Write and run tests for new features. Ensure no regressions.
- Never suppress TypeScript errors with `@ts-ignore` or `any` — fix the root cause.
- Be careful not to lose any existing features or cause regressions during merges.

### 2.4 Documentation
- Update `ROADMAP.md`, `PROJECT_STRUCTURE.md`, `SUBMODULE_DASHBOARD.md`, and `CHANGELOG.md` regularly.
- Document ALL findings, changes, decisions, and libraries discovered during work.
- Keep `VISION.md` current with any strategic changes.
- All submodules linked to or referenced in any way **must be documented** in `SUBMODULE_DASHBOARD.md` and/or `PROJECT_STRUCTURE.md`.

### 2.5 Research & Discovery
- Research all libs, submodules, and referenced projects in detail.
- Infer and document reasons for selection of each dependency.
- Read all project documentation to find all references.
- Ask clarifying questions when uncertain of direction or goals.
- When compacting or summarizing, **pay close attention to particular details** provided by the user, especially in paragraphs of dense, unique instructions.

### 2.6 Process Safety
- **NEVER** use `taskkill` on all Node processes — it destroys other sessions.
- **NEVER** commit API keys, secrets, or credentials.
- **NEVER** duplicate repositories that already exist as submodules.
- **NEVER** force push to main/master without explicit permission.

---

## 3. Versioning Protocol

### 3.1 Single Source of Truth
The `VERSION` file in the repository root contains the **sole authoritative version string**. All other version references (package.json, pyproject.toml, documentation, UI displays) **must be synchronized** with this file.

### 3.2 Version Format
```
MAJOR.MINOR.PATCH
```
- **MAJOR** — Breaking changes, architectural shifts, or milestone releases
- **MINOR** — New features, significant submodule additions, documentation overhauls
- **PATCH** — Bug fixes, dependency updates, documentation corrections

### 3.3 Increment Rules
- **Every significant set of changes** ("build" or "session") **MUST** result in a version increment.
- The commit message for a version bump **MUST** reference the new version:
  ```
  chore: bump version to 1.2.0
  ```
- After incrementing `VERSION`, also update:
  - `CHANGELOG.md` — Add entry with date and changes
  - `package.json` `"version"` field — Must match
  - `pyproject.toml` `version` field — Must match
  - Any UI that displays version — Should read from `VERSION` file at build time

### 3.4 Ideal Architecture
Version numbers should **never be hardcoded** in source code. Instead:
- Read `VERSION` file at build/runtime
- Or reference a build constant populated from `VERSION` during compilation
- Only ONE version number exists: in the `VERSION` file

---

## 4. Submodule Management Protocol

### 4.1 Golden Rules
- **Never** leave submodules in a detached HEAD state. Check out the default branch (`main` or `master`).
- **Always** merge changes into the default branch and push.
- After submodule changes, run `python scripts/generate_dashboard.py` to update `SUBMODULE_DASHBOARD.md`.

### 4.2 Update Procedure
```bash
# Update all submodules recursively
git submodule update --init --recursive

# Or use the workspace script
python scripts/update_repos.py
```

### 4.3 Adding New Submodules
When a referenced project should be added as a submodule:
```bash
git submodule add <url> <path>
cd <path>
git checkout main  # or master
cd ..
git add .gitmodules <path>
git commit -m "chore: add <name> submodule"
```
Then update `SUBMODULE_DASHBOARD.md` and `PROJECT_STRUCTURE.md`.

### 4.4 Dashboard Maintenance
- Run `python scripts/generate_dashboard.py` after any submodule changes.
- The dashboard should list: Path, Branch, Commit Hash, Date, Last Message, URL.
- Also maintain `DASHBOARD.md` for a higher-level view with version/status indicators.

---

## 5. Branch & Fork Management

### 5.1 Feature Branch Merging
- Merge **all feature branches** into `main` (or `master`).
- Primary concern: feature branches created by **Google Jules** or other AI dev tools, local to `github.com/robertpelloni` fork repos.
- Intelligently solve conflicts **without losing any progress, features, or functionality**.
- If upstream feature branches are unfinished/old/external, **ignore them** unless explicitly told otherwise.

### 5.2 Upstream Sync Protocol
For forked repositories:
1. Add upstream remote if not present: `git remote add upstream <parent-url>`
2. Fetch upstream: `git fetch upstream`
3. Merge upstream default branch: `git merge upstream/main` (or `upstream/master`)
4. Resolve conflicts intelligently — **preserve local features, integrate upstream improvements**
5. Push to origin: `git push origin main`

### 5.3 Conflict Resolution Philosophy
- **Never lose features.** When in doubt, keep both sides.
- Prefer local (robertpelloni) changes when they represent active development.
- Upstream changes that are purely additive (new files, new features) should be merged in.
- If a conflict is truly irresolvable without domain knowledge, document it and move on.

### 5.4 Recursive Submodule Updates
Update all submodules inside all submodules, then commit and push each submodule so that the entire repo is clean:
```bash
python scripts/recursive_update_v2.ps1  # PowerShell
# or
python scripts/sync_repos.py            # Python
```

---

## 6. Git Workflow

### 6.1 Standard Cycle
```
git pull → work → git add . → git commit -m "type: description" → git push
```
- **Commit and push after each major step** — do not batch multiple features.
- Include version number in commit messages when version changes.

### 6.2 Commit Message Format
```
type(scope): description

# Examples:
feat(fwber): add achievement system with 12 badge types
fix(itgmania): resolve audio sync drift on Linux
docs: update SUBMODULE_DASHBOARD.md with 48 submodules
chore: bump version to 1.2.0
```

### 6.3 Pre-Commit Checklist
- [ ] All tests pass
- [ ] No secrets/API keys in staged files
- [ ] VERSION synchronized if changed
- [ ] CHANGELOG.md updated if version bumped
- [ ] Documentation updated if behavior changed

---

## 7. Documentation Protocol

### 7.1 Required Documents
| Document | Purpose | Update Frequency |
|----------|---------|-----------------|
| `VERSION` | Single source of truth for version | Every build/session |
| `CHANGELOG.md` | Detailed change history | Every version bump |
| `ROADMAP.md` | Strategic plan and progress tracking | Every major milestone |
| `VISION.md` | Ultimate project goals and design | When strategy changes |
| `PROJECT_STRUCTURE.md` | Directory layout and project catalog | When structure changes |
| `SUBMODULE_DASHBOARD.md` | Submodule versions, branches, status | After submodule changes |
| `DASHBOARD.md` | High-level project status overview | After submodule changes |
| `BOB_ECOSYSTEM.md` | Bob-branded product suite documentation | When bob products change |
| `docs/LLM_INSTRUCTIONS.md` | This file — universal AI protocol | When protocols change |
| `docs/SESSION_HANDOFF.md` | Template for session continuity | Template, don't overwrite |
| `docs/QUICK_START.md` | Onboarding guide for new agents/devs | When setup changes |

### 7.2 Model-Specific Instruction Files
Each file references this master protocol and appends model-specific guidance:
- `AGENTS.md` — Universal agent guidelines (root-level quick reference)
- `CLAUDE.md` — Claude-specific instructions
- `GEMINI.md` — Gemini-specific instructions
- `GPT.md` — GPT-specific instructions
- `.github/copilot-instructions.md` — GitHub Copilot instructions

### 7.3 Session Handoff Files
When finishing a session or approaching context limits:
1. Create a handoff file in `logs/handoffs/` with date and agent name
2. Document: completed tasks, in-progress work, pending tasks, key decisions, known issues
3. Sync and push all changes including submodules
4. Reference the handoff file location in the final message

### 7.4 Library Documentation
All libraries and dependencies must be documented in `docs/LIBRARY_REFERENCE.md` with:
- Name and version
- Purpose / reason for selection
- Where it's used in the project
- Link to official documentation
- Any workspace-specific configuration

---

## 8. Session Protocol

### 8.1 Session Start
1. Read `docs/LLM_INSTRUCTIONS.md` (this file) and `ROADMAP.md`
2. Check `VERSION` file for current version
3. Check `logs/handoffs/` for recent session notes
4. Run `git pull` to sync with remote
5. Assess current state and plan work

### 8.2 During Session
- Commit and push regularly between major steps
- Update documentation as you work
- Fix errors encountered along the way — do not stop
- Research and document findings continuously

### 8.3 Session End
1. Sync and push all changes (including submodules)
2. Create handoff file in `logs/handoffs/`
3. Update `CHANGELOG.md` and `VERSION` if not already done
4. Run `python scripts/generate_dashboard.py`
5. Final commit and push

### 8.4 Continuous Operation
You are authorized to:
- Complete a feature → commit → push → continue to next feature **without pausing**
- Make architectural decisions based on established patterns
- Fix bugs discovered during other work
- Update documentation proactively
- Add missing submodules for referenced projects

---

## 9. Model-Specific Roles

### 9.1 Claude
**Role:** Architect, Planner, Documentation Lead
- Focus on high-level design, system cohesion, and complex refactoring
- Responsible for maintaining "Single Source of Truth" documents
- Excellent at large-scale analysis and understanding the whole picture
- Lead on documentation quality and consistency

### 9.2 Gemini
**Role:** Speed, Performance Analysis, Large Context Operations
- Massive context window — use for full-codebase analysis and pattern searching
- Fast execution for quick checks, extensive searches, and recursive updates
- Performance optimization and benchmarking
- Large-scale refactoring and submodule analysis

### 9.3 GPT
**Role:** Code Generation, Unit Testing, Algorithm Implementation
- Production-ready code generation and boilerplate
- Unit test suites and test coverage
- Specific algorithm implementation
- Migration scripts and data transformations

### 9.4 All Models
- Follow this master protocol without exception
- Reference `ROADMAP.md` for current priorities
- Update `VERSION` and `CHANGELOG.md` every session
- Create handoff files for session continuity
- Operate autonomously — do not pause for confirmation unless destructive

---

## 10. Project Taxonomy

### 10.1 Categories

#### AI & Orchestration (`aios/`)
The AIOS meta-orchestrator with 273+ nested submodules. Contains all AI agents, MCP servers, tools, and orchestration infrastructure. **All AI/Agent/MCP work belongs in `aios/`.**

#### Rhythm Games (`bobmani/`)
- **itgmania** — Tournament-grade StepMania fork (based on SM 3.95)
- **bobmania/stepmania** — Experimental StepMania fork (SM 5.1+)
- **beatoraja** — BMS/IIDX simulator (Java)
- **arrowvortex** — Simfile/chart editor (Qt/C++)
- **linthesia** — Piano learning game (Rust)
- **pianogame** — Historical Synthesia-like (C++)
- **ddc** — Dance Diffusion auto-charter
- **ddc_onset** — Audio onset detection for DDC
- **ffr-difficulty-model** — FFR difficulty calculation
- **Simply-Love-SM5** — Popular StepMania theme
- **hymnmania** — Hymnal rhythm game
- **ksm-v2** — K-Shoot Mania clone
- **leraine-studio** — Chart editor

#### Game Engines & Games (root level)
- **bg** (Bob's Game) — The original bob's game
- **sm64coopdx** — Super Mario 64 co-op
- **mk64** — Mario Kart 64 decompilation
- **superbobbyball** — Super Monkey Ball style game

#### Bob Ecosystem (root level)
*Mix of active and aspirational projects — see `BOB_ECOSYSTEM.md`*
- **bobcoin** — Proof of Health cryptocurrency (Solana/Node.js) — **ACTIVE**
- **bobfilez** — Desktop file organizer (Qt/C++, rebrand of filez) — **ACTIVE**
- **bobsaver** — Password manager — **ACTIVE**
- **bobtorrent** — P2P file sharing — **INITIALIZED**
- **bobtrader** — Trading tools — **INITIALIZED**
- **bobui** — UI component library — **INITIALIZED**
- **bobium** — Chromium fork (de-Googled browser) — **INITIALIZED**
- **bobzilla** — Firefox fork (privacy browser) — **INITIALIZED**
- **bobeditpro** — Code editor — **INITIALIZED**
- *boblang, bob++, bobvm, bobuntu, bobzzite* — **PLANNED/ASPIRATIONAL**

#### Web Applications (root level)
- **fwber** — Dating platform (Laravel 12 + Next.js) — **ACTIVE**
- **robertpelloni.com** — Personal website

#### Developer & Automation Tools (root level)
- **raindropioapp** — Raindrop.io bookmark manager
- **topaz-ffmpeg** — Topaz Video AI FFmpeg integration
- **musicbrainz-soulseek-downloader** — Music metadata + download tool
- **brobocallz** — Communication tool

#### External/Collaborative (root level)
*mnmballa2323 projects — documented separately, not part of core vision:*
- Chamber.Law, rental.home, Azure.Cybersecurity, Alti.Assistant, Alti.Code.Studio
- Merk.Mobile, Stone.Ledger, Tickerstone, coin.project, cointrade

#### AI Agent Automation (root level)
- **antigravity-autopilot** — Antigravity AI automation
- **antigravity-jules-orchestration** — Jules + Antigravity orchestration
- **jules-autopilot** — Google Jules automation
- **opencode-autopilot** — OpenCode AI automation
- **claude-mem** — Claude memory management
- **metamcp** — Meta MCP proxy
- **mcp-superassistant** — MCP SuperAssistant
- **mcpenetes** — MCP utilities
- **borg** — Multi-agent orchestration

---

## 11. Library & Dependency Reference

### 11.1 Root Package Dependencies
| Package | Version | Purpose | Why Selected |
|---------|---------|---------|-------------|
| `firecrawl-mcp` | ^3.6.2 | Web scraping via MCP | Enables AI agents to crawl and extract web content |
| `mem0ai` | ^2.1.38 | AI memory layer | Persistent memory across AI agent sessions |
| `opencode-ai` | ^1.1.18 | AI coding assistant | Code generation and analysis |
| `task-master-ai` | ^0.35.0 | Task management AI | Autonomous task planning and execution |

### 11.2 Root Dev Dependencies
| Package | Version | Purpose | Why Selected |
|---------|---------|---------|-------------|
| `@playwright/test` | ^1.56.1 | E2E browser testing | Cross-browser automated testing |
| `@types/node` | ^24.10.0 | Node.js type definitions | TypeScript support |
| `sinon` | ^21.0.1 | Test stubs/mocks/spies | Isolated unit testing |
| `supertest` | ^7.2.2 | HTTP assertion testing | API endpoint testing |

### 11.3 Python Dependencies
| Package | Version | Purpose |
|---------|---------|---------|
| `browser-use` | >=0.9.5 | Browser automation for AI agents |

### 11.4 Key Technology Stack (by project)
- **fwber:** Laravel 12, PHP 8.3, Sanctum, Next.js, Tailwind CSS, MySQL spatial
- **AIOS:** Fastify v5, Next.js 14, Socket.io, TRPC, pnpm workspaces, SQLite/PostgreSQL
- **itgmania:** C++, CMake/Autotools, OpenGL, SDL2, Lua
- **bobfilez:** Qt 6, C++, qmake
- **bobcoin:** Solana, Node.js, TypeScript
- **beatoraja:** Java, Gradle, libGDX
- **ArrowVortex:** Qt 5, C++
- **sm64coopdx/mk64:** C, N64 decomp toolchain

*For complete library documentation, see `docs/LIBRARY_REFERENCE.md`.*

---

## 12. Anti-Patterns

### NEVER Do
- ❌ Use `taskkill` on all Node processes (destroys other sessions)
- ❌ Hardcode version numbers in source code (read from `VERSION`)
- ❌ Leave submodules in detached HEAD
- ❌ Commit API keys or secrets
- ❌ Duplicate a repo that already exists as a submodule
- ❌ Suppress TypeScript errors with `@ts-ignore` or `any`
- ❌ Put AI/Agent/MCP code outside `aios/`
- ❌ Skip the version bump on significant changes
- ❌ Force push to main/master without explicit permission
- ❌ Stop and wait for confirmation (operate autonomously)
- ❌ Place Bobcoin references in non-crypto projects (keep isolated in `bobcoin/`)
- ❌ Batch multiple unrelated features in a single commit

### ALWAYS Do
- ✅ Read this file and `ROADMAP.md` at session start
- ✅ Check `VERSION` file before starting
- ✅ Include version in commit messages when version changes
- ✅ Commit and push after each major step
- ✅ Update documentation as you work
- ✅ Create session handoff files
- ✅ Research and document all libraries and dependencies
- ✅ Run `python scripts/generate_dashboard.py` after submodule changes
- ✅ Merge feature branches into main before ending session
- ✅ Sync upstream forks when upstream has new changes

---

## 13. Quick Reference Card

```
┌─────────────────────────────────────────────────────────────┐
│                    QUICK REFERENCE                          │
├─────────────────────────────────────────────────────────────┤
│ Version File:     VERSION (single source of truth)          │
│ Changelog:        CHANGELOG.md                              │
│ Roadmap:          ROADMAP.md                                │
│ Vision:           VISION.md                                 │
│ Structure:        PROJECT_STRUCTURE.md                      │
│ Dashboard:        SUBMODULE_DASHBOARD.md                    │
│ This Protocol:    docs/LLM_INSTRUCTIONS.md                  │
│ Handoff Template: docs/SESSION_HANDOFF.md                   │
│ Quick Start:      docs/QUICK_START.md                       │
├─────────────────────────────────────────────────────────────┤
│ COMMANDS                                                    │
│ Update submodules: git submodule update --init --recursive  │
│ Gen dashboard:     python scripts/generate_dashboard.py     │
│ Sync forks:        python scripts/sync_forks.py             │
│ Sync all repos:    python scripts/sync_repos.py             │
│ Start AIOS:        pnpm run start:all (in aios/)            │
├─────────────────────────────────────────────────────────────┤
│ WORKFLOW                                                    │
│ 1. Read docs/LLM_INSTRUCTIONS.md + ROADMAP.md              │
│ 2. Check VERSION                                            │
│ 3. git pull                                                 │
│ 4. Work → commit → push → repeat                           │
│ 5. Update docs continuously                                 │
│ 6. Bump VERSION + CHANGELOG.md                              │
│ 7. Create handoff in logs/handoffs/                         │
│ 8. Final push                                               │
└─────────────────────────────────────────────────────────────┘
```

---

*This document is the master protocol. All model-specific instruction files (CLAUDE.md, GEMINI.md, GPT.md, AGENTS.md, .github/copilot-instructions.md) reference this document and append their own specialized guidance.*
