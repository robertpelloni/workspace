# Changelog

All notable changes to this project will be documented in this file.

## [1.0.10] - 2026-01-13

### Verified
- Audited fwber MISSING_FEATURES.md - confirmed 11 of 16 features are COMPLETE
- Achievements UI, Proximity Chatrooms, Bulletin Boards, Profile Views, Paid Photo Reveals, Share-to-Unlock, Message Reactions, Group Matching, Matchmaker Bounties, Extended Viral Content, Merchant Discovery - all implemented
- Remaining: Content Unlock System UI, E2E Encryption, Group Events, DAU Analytics, Gift System Enhancement, Merchant Analytics Dashboard

### Changed
- Synchronized all submodules with upstream
- Updated documentation to reflect current feature completion status

### Technical
- fwber Phase 4B complete - all critical frontend UIs implemented
- filez Java port functional with 30 passing tests
- aios Phase 8 in progress (ecosystem expansion)

## [1.0.9] - 2026-01-09

### Added
- Added audio/music production submodules: zrythm, lmms, timidity, ardour, audacity
- Added graphics libraries: nanovg, GWEN, bonsai
- Added rhythm games: leraine-studio, ksm-v2
- Added utilities: picard (music tagger), qBittorrent, PowerTrader_AI
- Updated SUBMODULE_DASHBOARD.md to 79 root submodules

## [1.0.7] - 2026-01-09

### Added
- filez Java 21 port (filez-java/) with multi-module Gradle structure
- Java implementations: NioFileScanner, JavaHasher, SQLite database layer
- JNI stubs for BLAKE3/XXHash64 with auto-fallback to pure Java
- 30 JUnit 5 tests for Java port

## [1.0.6] - 2026-01-09

### Added
- Added `linthesia` (robertpelloni/linthesia) as root submodule - music learning game
- Added game submodules: `hellven`, `sm64coopdx`, `mk64`, `f-zerox`, `neverball`
- Created `SUBMODULE_DASHBOARD.md` with comprehensive 25-submodule inventory and structure overview

### Changed
- Synced all submodules with remote repositories
- Updated project structure documentation

## [1.0.5] - 2026-01-08

### Added
- Created `scripts/orchestrate_agents.py`: A CLI tool to orchestrate `trae-agent` and `ii-agent` using `uv` and `subprocess`.
- Refactored `aios/openevolve` to use standard `src/` directory layout (Moved `openevolve` package to `src/openevolve`).

### Fixed
- Verified `trae-agent` and `ii-agent` installation and registered them in `AGENTS.md`.
- Updated `pyproject.toml` in `openevolve` to support the new `src` layout.

## [1.0.4] - 2026-01-08

### Fixed
- Repaired `trae-agent` installation (cloned to root, fixed submodule path).
- Fixed recursive submodule definitions in `aios`, `bobcoin`, `filez`.
- Resolved merge conflicts in `jules-autopilot` and `opencode-autopilot`.

### Added
- Created `AGENTS.md` to track installed agents and environment findings.
- Updated `DASHBOARD.md` with comprehensive 519-submodule inventory.

## [1.0.3] - 2026-01-07

### Fixed
- Resolved recursive submodule issues in `Neothesia` (merge conflicts) and `OpenQode` (broken gitlinks).
- Fixed `aios` submodule pointers to correctly track nested dependencies.

### Added
- Created `PROJECT_STRUCTURE.md` providing a comprehensive dashboard of all recursive submodules.
- Integrated `openevolve` directly into `aios` structure.

## [1.0.2] - 2026-01-02

### Changed
- Converted `opencode-autopilot` to a Next.js application.
- Setup Vercel-compatible API routes.
- Migrated Supervisor and Council logic to the new structure.

## [1.0.1] - 2025-12-31

### Added
- Created `DASHBOARD.md` to track submodule status and project structure.
- Created `VERSION` file for single source of truth for versioning.
- Added `scripts/update_and_dashboard.py` and `scripts/generate_dashboard_only.py` for automation.

### Changed
- Updated documentation to reflect project structure.
- Attempted submodule updates (ongoing).

## [1.0.0] - Initial Release
- Initial project setup with various AI agent submodules.
