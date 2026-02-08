# Changelog

All notable changes to the Robert Pelloni Workspace Monorepo will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

Version numbers are synchronized with the `VERSION` file (single source of truth).

---

## [1.2.0] - 2026-02-08

### Added
- **Comprehensive VISION.md** — Full project vision document with 14 sections covering philosophy, domain architecture, Bob Ecosystem, rhythm games, technology strategy, integration architecture, and long-term roadmap
- **Universal LLM_INSTRUCTIONS.md** — Complete master protocol (13 sections) covering versioning, submodule management, branch/fork management, git workflow, documentation protocol, session protocol, model-specific roles, project taxonomy, library reference, and anti-patterns
- **LIBRARY_REFERENCE.md** — Detailed documentation of all libraries and dependencies with reasons for selection (pending)
- **docs/QUICK_START.md** version reference updated

### Changed
- **AGENTS.md** — Complete rewrite with structured sections: General Guidelines, Common Commands, User Directives, Versioning Rules, Anti-Patterns, and Goal
- **CLAUDE.md** — Complete rewrite with Claude-specific persona, capabilities, quick reference, session checklist, mandates, versioning protocol, handoff protocol, anti-patterns, submodule management, and branch/fork merging protocol
- **GEMINI.md** — Complete rewrite with Gemini-specific capabilities (large context, speed, performance), workflow recommendations, session checklist, and key commands. Removed inappropriate Bobcoin references
- **GPT.md** — Complete rewrite with GPT-specific role (Technical Executor), capabilities, session checklist, testing guidelines, and workflow expectations
- **.github/copilot-instructions.md** — Complete rewrite with master protocol reference and full ByteRover CLI command reference
- **VERSION** — Bumped from 1.1.2 → 1.2.0
- **package.json** — Version synced to 1.2.0 (was 1.0.0, out of sync)
- **pyproject.toml** — Version synced to 1.2.0 (was 0.1.0, out of sync), description updated

### Fixed
- Version desynchronization between VERSION (1.1.2), package.json (1.0.0), and pyproject.toml (0.1.0) — all now at 1.2.0
- Bobcoin references removed from GEMINI.md (ArrowVortex is a simfile editor, not crypto)

---

## [1.1.2] - 2026-02-03

### Fixed
- okgame library compilation issues
- BobsGameOnline GeoIP2 database integration
- bobfilez Local-File-Organizer submodule references

---

## [1.1.1] - 2026-02-02

### Changed
- Unified documentation across all instruction files
- Regenerated SUBMODULE_DASHBOARD.md
- Fixed multiple submodule reference issues

---

## [1.1.0] - 2026-02-02

### Added
- Massive submodule integration (250+ submodules synchronized)
- Dashboard automation via `scripts/generate_dashboard.py`
- Recursive update scripts (`scripts/recursive_update_v2.ps1`, `scripts/sync_repos.py`)
- Fork synchronization script (`scripts/sync_forks.py`)
- Consensus gate CI workflow (`scripts/consensus_gate.js`)

### Changed
- Complete documentation overhaul
- SUBMODULE_DASHBOARD.md now auto-generated
- All submodules checked out to default branches (no detached HEADs)

---

## [1.0.10] - 2026-01-15

### Changed
- fwber security audit and hardening
- Dependency updates across web stack

---

## [1.0.9] - 2026-01-14

### Added
- Audio/music/graphics submodules (echogarden, libjxl, topaz-ffmpeg)
- musicbrainz-soulseek-downloader integration

---

## [1.0.7] - 2026-01-12

### Added
- filez Java port initialization (bobfilez)
- Desktop file organizer rebranding

---

## [1.0.6] - 2026-01-10

### Added
- linthesia (Rust piano game) submodule
- Game submodules: sm64coopdx, mk64, neverball, MarbleBlast
- QUICK_START.md for new contributors and AI agents

---

## [1.0.5] - 2026-01-09

### Added
- `scripts/orchestrate_agents.py` — Agent orchestrator CLI for Trae and II agents
- Agent SDK integration

---

## [1.0.4] - 2026-01-08

### Fixed
- trae-agent configuration and startup issues

---

## [1.0.3] - 2026-01-07

### Fixed
- Recursive submodule initialization failures
- Detached HEAD states in nested submodules

---

## [1.0.2] - 2026-01-06

### Added
- opencode-autopilot with Next.js frontend

---

## [1.0.1] - 2026-01-05

### Added
- SUBMODULE_DASHBOARD.md initial generation
- VERSION file as single source of truth
- DASHBOARD.md project status overview

---

## [1.0.0] - 2026-01-04

### Added
- Initial monorepo structure
- Core submodule integration (aios, fwber, itgmania, bobcoin, okgame)
- Documentation framework (README, ROADMAP, PROJECT_STRUCTURE)
- Script infrastructure (update_repos.py, generate_dashboard.py)
- CI/CD configuration (Playwright tests, consensus gate)

---

[1.2.0]: https://github.com/robertpelloni/workspace/compare/v1.1.2...v1.2.0
[1.1.2]: https://github.com/robertpelloni/workspace/compare/v1.1.1...v1.1.2
[1.1.1]: https://github.com/robertpelloni/workspace/compare/v1.1.0...v1.1.1
[1.1.0]: https://github.com/robertpelloni/workspace/compare/v1.0.10...v1.1.0
[1.0.10]: https://github.com/robertpelloni/workspace/compare/v1.0.9...v1.0.10
[1.0.9]: https://github.com/robertpelloni/workspace/compare/v1.0.7...v1.0.9
[1.0.7]: https://github.com/robertpelloni/workspace/compare/v1.0.6...v1.0.7
[1.0.6]: https://github.com/robertpelloni/workspace/compare/v1.0.5...v1.0.6
[1.0.5]: https://github.com/robertpelloni/workspace/compare/v1.0.4...v1.0.5
[1.0.4]: https://github.com/robertpelloni/workspace/compare/v1.0.3...v1.0.4
[1.0.3]: https://github.com/robertpelloni/workspace/compare/v1.0.2...v1.0.3
[1.0.2]: https://github.com/robertpelloni/workspace/compare/v1.0.1...v1.0.2
[1.0.1]: https://github.com/robertpelloni/workspace/compare/v1.0.0...v1.0.1
[1.0.0]: https://github.com/robertpelloni/workspace/releases/tag/v1.0.0
