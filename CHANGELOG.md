# Changelog

All notable changes to this project will be documented in this file.

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
