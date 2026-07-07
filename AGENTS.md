# Agents Protocol

> **CRITICAL: ALL AGENTS MUST READ `docs/UNIVERSAL_LLM_INSTRUCTIONS.md` BEFORE PROCEEDING.**


This file serves as a reference point for multi-agent workflows (Claude -> Gemini -> GPT).








1.  **Handoffs:** Agents communicate primarily through `HANDOFF.md`. When your turn finishes, document exactly what you did, what failed, and what the next agent must do.
2.  **Specializations:**
    *   **Gemini:** Speed, recursive scripts, massive context processing, repo maintenance.
    *   **Claude:** Deep implementation, UI/UX perfection, documentation, styling.
    *   **GPT:** Architecture, systemic debugging, strict type enforcement.
3.  **Iteration Cycle:** Read -> Strategize -> Execute -> Validate -> Commit -> Handoff. Never stop the party.


## Brain — Agent Memory

This project uses Brain for agent memory management.

**Start here when orienting:** Read `.memory/main.md` for the project roadmap, key decisions, and open problems.
Read `.memory/AGENTS.md` for the full Brain protocol reference.
Tools: memory_commit, memory_branch (create/switch/merge)
