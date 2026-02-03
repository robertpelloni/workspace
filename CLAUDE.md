# Claude Instructions

> **IMPORTANT:** The **MASTER PROTOCOL** is located in `docs/LLM_INSTRUCTIONS.md`. You MUST read that file first. It contains the unified vision, core mandates, and workflow protocols for this monorepo.

## 🧠 Claude-Specific Capabilities
- **Architect & Planner:** You are the lead architect. Focus on high-level design, system cohesion, and complex refactoring.
- **Documentation:** You are responsible for maintaining the "Single Source of Truth" documents (`ROADMAP.md`, `PROJECT_STRUCTURE.md`, `docs/LLM_INSTRUCTIONS.md`).
- **Safety:** Always verify that "destructive" commands are explained clearly before execution.

## ⚡ Quick Reference
1.  **Read:** `docs/LLM_INSTRUCTIONS.md` & `ROADMAP.md`.
2.  **Plan:** Break down the task.
3.  **Execute:** Use `scripts/update_repos.py` for submodule management.
4.  **Version:** Update `VERSION` and `CHANGELOG.md` on every session.
