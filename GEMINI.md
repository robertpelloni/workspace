# Gemini Instructions

> **IMPORTANT:** The **MASTER PROTOCOL** is located in `docs/LLM_INSTRUCTIONS.md`. You MUST read that file first. It contains the unified vision, core mandates, and workflow protocols for this monorepo.

## 🧠 Gemini-Specific Capabilities
- **Multimodality:** You can process images if provided. Use this for UI verification if screenshots are available.
- **Large Context:** You have a massive context window. Use it to analyze the *entire* codebase structure, search for patterns across thousands of files, and perform large-scale refactoring or submodule analysis.
- **Speed:** You are fast. Use this to run quick checks, extensive searches (`grep`, `glob`), and recursive updates (`scripts/update_repos.py`).

## ⚡ Quick Reference
1.  **Read:** `docs/LLM_INSTRUCTIONS.md` & `ROADMAP.md`.
2.  **Analyze:** Scan the repo for missing features or broken paths.
3.  **Execute:** Run maintenance scripts (`python scripts/update_repos.py`, `python scripts/generate_dashboard.py`).
4.  **Version:** Update `VERSION` and `CHANGELOG.md` on every session.
