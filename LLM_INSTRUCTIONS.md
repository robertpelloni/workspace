# Unified LLM Instructions

## 1. Overview & Vision
This document is the **single source of truth** for all AI models (Claude, GPT, Gemini, etc.) working on the Robert Pelloni Monorepo. This workspace acts as a centralized manager for a vast ecosystem of projects including AI operating systems (`aios`), game engines (`itgmania`, `okgame`), web platforms (`fwber`), and various tools.

**Ultimate Vision:** To create a highly autonomous, self-maintaining, and self-improving software ecosystem where AI agents can seamlessly collaborate to build, test, and deploy complex software across multiple domains (AI, Gaming, Web, Audio/Video).

## 2. Core Mandates

*   **Autonomy:** Proceed autonomously for as long as possible. Do not ask for confirmation unless a critical, irreversible destructive action is about to be taken (and even then, explain clearly).
*   **Conventions:** Rigorously adhere to existing project conventions. Analyze surrounding code first.
*   **Versioning:**
    *   **Single Source of Truth:** The `VERSION` file in the root directory contains the current version number.
    *   **Increment on Build:** Every significant set of changes (a "build" or "session") MUST result in a version increment.
    *   **Changelog:** Update `CHANGELOG.md` with every version bump.
    *   **Commit Message:** The version bump commit message must reference the new version (e.g., `chore: bump version to 1.2.3`).
*   **Submodules:**
    *   This project relies heavily on submodules.
    *   **Never** leave submodules in a detached HEAD state if possible. Merge changes into the default branch (`main` or `master`) and push.
    *   Use `scripts/generate_dashboard.py` (or equivalent) to keep `SUBMODULE_DASHBOARD.md` up to date.
*   **Testing:** Write and run tests for new features. Ensure no regressions.
*   **Documentation:**
    *   Update `ROADMAP.md` and `PROJECT_STRUCTURE.md` regularly.
    *   Document all inputs, findings, and decisions in session handoff notes.

## 3. Workflow Protocols

### A. Feature Implementation
1.  **Analyze:** Read `ROADMAP.md` and `LLM_INSTRUCTIONS.md`. Search the codebase to understand the context.
2.  **Plan:** Select a feature. Break it down into atomic steps.
3.  **Execute:** Implement the feature using available tools.
    *   *Self-Correction:* If an error occurs, fix it immediately. Do not stop to ask the user.
4.  **Verify:** Run tests. Ensure code compiles/runs.
5.  **Commit:** `git add .`, `git commit -m "feat: <description>"`, `git push`.
6.  **Loop:** Proceed to the next feature without pausing.

### B. Repo Maintenance
1.  **Update:** Run update scripts to sync submodules.
2.  **Merge:** Merge feature branches into `main`.
3.  **Fix:** Resolve merge conflicts favoring the "new" or "local" changes if they represent progress.

## 4. Model-Specific Roles

*   **Claude:** Architect, Planner, Documentation Lead. Excellent at large-scale refactoring and "understanding" the whole picture.
*   **Gemini:** Speed, Performance Analysis, Large Context Operations (like full-repo scans), Scripting.
*   **GPT:** Code Generation, Unit Testing, specific algorithm implementation.

## 5. Directory Structure
*   `docs/`: Workspace-level documentation.
*   `scripts/`: Maintenance scripts (`update_repos.py`, `generate_dashboard.py`).
*   `logs/`: Operation logs.
*   `aios/`: AI Operating System (Submodule).
*   `itgmania/`, `okgame/`: Game Engines.
*   `fwber/`: Web Platform.

## 6. Handoff Protocol
When finishing a session:
1.  Sync/Push all changes.
2.  Create a detailed handoff file in `logs/handoffs/` explaining what was done, what is pending, and any specific context for the next agent.