# Changelog

## [1.3.4] - 2026-02-24
### Added
- **Deep Submodule Analysis & Synchronization:** Executed massive orchestration task across all nested submodules and linked projects. Updated, merged upstream changes (including forks), and safely integrated local feature branches created by AI developer tools (under `robertpelloni`). Resolved conflicts and committed changes to keep entire repo clean and progressive without losing features.
- **Documentation Overhaul:** Reanalyzed the project history. Comprehensively updated the roadmap, documentation, and TODOs to track missing features. Auto-generated and refined `SUBMODULE_DASHBOARD.md` to detail all submodules, versions, dates, build numbers, and the architectural directory layout.
- **Handoff Documentation:** Detailed conversation, findings, and memories logged in `HANDOFF.md` to maintain context for future iterations.

## [1.3.3] - 2026-02-22
### Added
- **Intelligent Submodule Synchronization:** Created `sync_and_merge.py` for massive, bidirectional feature merging. This script handles updating submodules, pulling from upstream forks, merging feature branches into main, merging main into feature branches, and resolving basic conflicts automatically using `-X ours` to prevent losing feature development progress.
- **Directory Structure Dashboard:** Rewrote `SUBMODULE_DASHBOARD.md` to include a clear explanation of the monorepo's architectural layout and top-level submodules.
### Fixed
- Fixed several broken `.gitmodules` mappings (e.g., `AUTO-ALL-AntiGravity`, `Snaype.Desktop`) that were causing `git submodule status --recursive` to fail.

## [1.3.2] - 2026-02-22
### Added
- **Holistic Workspace Audit:** Performed a recursive health scan across the entire monorepo, mapping the status of all 50+ submodules.
- **Submodule Dashboard Sync:** Refreshed `SUBMODULE_DASHBOARD.md` with the latest version tags (`antigravity-autopilot` v5.2.55, `metamcp` v3.7.0, `jules-autopilot` v0.8.8) and commit metadata.
- **Index Reconciliation:** Identified critical drift in `jules-autopilot` and `antigravity-autopilot` where submodule HEADs were significantly ahead of the root's tracked commit index.

## [1.3.1] - 2026-02-19
### Added
- **Phase 2 Implementation:** Created `scripts/propagate_instructions.py` which resiliently pushed the `docs/UNIVERSAL_LLM_INSTRUCTIONS.md` to **1,558** repositories and submodules across the entire workspace tree.
- **Recursive Dashboarding:** Upgraded `scripts/generate_dashboard.py` to recursively map every sub-submodule, providing total visibility into the fleet's branch and commit status.

## [1.3.0] - 2026-02-19
### Changed
- **Documentation Architecture:** Replaced individual model instructions with a centralized `docs/UNIVERSAL_LLM_INSTRUCTIONS.md` and updated `GEMINI.md`, `CLAUDE.md`, `GPT.md`, and `AGENTS.md` to reference it.
- **Global Synchronization:** Successfully ran `update_repos_v3.py` across 500+ repositories, syncing with origins and merging viable upstream changes.
- **Repo Repair:** Re-initialized and fixed broken submodules (`qwen.project`, `cointrade`, `metamcp`, `bobeditpro`).
- **Conflict Resolution:** Manually resolved complex "detached HEAD" states and purged API keys from `metamcp` history.
- **Cleanup:** Removed large binary files (`antigravity-autopilot.7z`) and stale worktrees (`.borg` folders) that were blocking pushes.
