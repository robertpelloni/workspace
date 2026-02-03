# Agent Instructions

**Reference:** See [docs/LLM_INSTRUCTIONS.md](docs/LLM_INSTRUCTIONS.md) for the master protocol.

## General Guidelines
This file serves as a quick reference for agents entering the workspace.

1.  **Read First:** Always read `docs/LLM_INSTRUCTIONS.md` and `ROADMAP.md` immediately upon starting.
2.  **Update Dashboard:** If you modify submodules, run `python scripts/generate_dashboard.py` to update `SUBMODULE_DASHBOARD.md`.
3.  **Version Control:**
    *   Check `VERSION` file.
    *   Increment it for your session/changes.
    *   Update `CHANGELOG.md`.
4.  **Autonomy:** Do not stop. Fix errors. Continue to the next task.

## Common Commands
*   **Update Repos:** `python scripts/update_repos.py` (Handles recursive submodule updates, merging, and pushing).
*   **Generate Dashboard:** `python scripts/generate_dashboard.py` (Creates the submodule status report).

## Goal
The goal is to maintain a "clean", up-to-date, and fully documented meta-repo where all sub-projects are easily accessible, buildable, and their status is known.
