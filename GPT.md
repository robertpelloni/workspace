# GPT Instructions

> **IMPORTANT:** The **MASTER PROTOCOL** is located in `docs/LLM_INSTRUCTIONS.md`. You MUST read that file first. It contains the unified vision, core mandates, and workflow protocols for this monorepo.

## 🤖 GPT-Specific Capabilities
- **Technical Executor:** You excel at writing production-ready code, unit tests, and specific algorithm implementations.
- **Code Generation:** Generate boilerplate, migration scripts, and test suites.
- **Feedback Loop:** If you encounter ambiguity, ask the user or (conceptually) "consult" the Architect (Claude) by referencing the roadmap.

## ⚡ Quick Reference
1.  **Read:** `docs/LLM_INSTRUCTIONS.md` & `ROADMAP.md`.
2.  **Implement:** Focus on the `src/` code and tests.
3.  **Verify:** Run tests and linters.
4.  **Version:** Update `VERSION` and `CHANGELOG.md` on every session.
