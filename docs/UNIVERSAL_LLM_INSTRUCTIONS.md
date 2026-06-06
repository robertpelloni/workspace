# Universal LLM Instructions — Omni-Workspace

> **MANDATORY PROTOCOL:** This document is the absolute source of truth for all AI agents (Claude, Gemini, GPT, etc.) operating within this monorepo. Proprietary model files (e.g., `CLAUDE.md`, `GEMINI.md`) must only contain model-specific overrides and MUST reference this document.

## 1. Core Operating Mandates

### 1.1 Process Preservation (CRITICAL)
- **NEVER** kill or terminate active background processes unless explicitly instructed. 
- Always audit the process list (`Get-WmiObject Win32_Process`) before performing operations that might conflict.
- Priority PIDs: Deep Research workers, Build Orchestrators, Azure Log Tailers.

### 1.2 Zero-Loss Integration
- **Feature Parity:** No code is left behind. All feature branches (especially those prefixed with `feature/`, `fix/`, or created by `Jules`) must be intelligently merged into the primary branch.
- **Intelligent Conflict Resolution:** Solve conflicts by merging functionalities rather than blindly picking one side. Er on the side of caution.
- **Binary Integrity:** Never delete or overwrite successfully compiled binaries or `.build_success` markers.

### 1.3 Atomic Documentation
- **Versioning:** Every significant build pass or synchronization MUST increment the `VERSION` file.
- **Changelog:** Maintain a detailed history in `CHANGELOG.md`. Reference the version bump in commit messages.
- **Handoffs:** Every session MUST conclude with a detailed `HANDOFF.md` documenting findings, changes, and memories for the next model cycle.

## 2. Workspace Architecture

### 2.1 Directory Structure
- `Maestro/`: TechLead orchestrator and multi-agent service core.
- `borg/`: The autonomous IDE infrastructure and "Council of Supervisors."
- `research/`: Centralized cluster for untracked experimental projects and scratchpads.
- `bg/`: Game engine and backend services (OkGame, BobCoin).
- `antigravity-autopilot/`: Mobile and web UI bridge.
- `topaz-ffmpeg/`: High-performance video processing core.

### 2.2 Submodule Management
- All referenced projects and packages must be added as git submodules where appropriate.
- Maintain `SUBMODULE_DASHBOARD.md` with versions, commit dates, and build status.
- Every submodule must have an `IDEAS.md` for high-intelligence future goals.

## 3. Engineering Standards

### 3.1 Code Quality
- **Self-Documenting:** Use comprehensive comments explaining the *why* behind logic, findings, side effects, and non-working alternate methods.
- **Validation:** Every change requires empirical evidence. Run integration tests (`tests/test_workspace.py`) and verify build status in `build_all.log`.
- **Linting:** Respect local `.eslintrc`, `.prettierrc`, and `tsconfig.json` settings. Fix style issues before pushing.

### 3.2 Automation First
- Prefer scripts (`python build_all.py`, `scripts/sync_all_submodules.py`) over manual repetitive tasks.
- If a pattern is discovered (e.g., repeating conflict types), automate the resolution.

## 4. Vision Alignment
Refer to `VISION.md` for the ultimate project direction. We are building a **Self-Healing, Federated AI Monorepo**—a true end-to-end autonomous development pipeline.
