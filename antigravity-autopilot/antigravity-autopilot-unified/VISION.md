# Project Vision - Antigravity Autopilot

## The Ultimate Goal
**Antigravity Autopilot** is designed to be the definitive "Agentic IDE Assistant". It transcends simple autocomplete or chat interfaces by becoming a proactive, autonomous partner in software development.

Our vision is a system where the developer acts as the "Architect" and "Reviewer", while Antigravity handles the "Implementation" and "Verification".

## Core Principles
1.  **Autonomy**: The agent should be capable of multi-step reasoning, planning, and execution without constant hand-holding. It should detect errors, attempt fixes, and only escalate when stuck.
2.  **Immersiveness**: The agent lives *inside* the IDE. It sees what you see (File Explorer, Terminal, Editor tabs) and interacts naturally via click, type, and command.
3.  **Robustness**: Unlike fragile scripts, Antigravity uses the Chrome DevTools Protocol (CDP) to interface directly with the IDE's core, ensuring reliability even when the UI changes or is hidden.
4.  **Configurability**: Every developer has a unique workflow. Antigravity must be deeply customizable—from simple "auto-accept" to complex "multi-agent swarms".

## Design Philosophy
*   **Unified Experience**: A single extension replaces disparate tools. One configuration source, one status bar, one mental model.
*   **Transparent Operation**: The user should always know what the agent is doing (via Status Bar, Output Logs, and visual overlays). "Magic" is good, "Mystery" is bad.
*   **Safety First**: Circuit breakers, improved error handling, and hard limits (max loops, banned commands) ensure the agent never goes rogue.

## Roadmap to Utopia
### Phase 1: Foundation (Current)
*   Unified Extension Architecture.
*   Robust CDP Integration.
*   Basic Autonomous Loop.

### Phase 2: Intelligence (Next)
*   **Memory**: Long-term semantic memory of the codebase and user preferences.
*   **Planning**: Hierarchical task decomposition (Goal -> Steps -> Actions).
*   **Learning**: The agent learns from user corrections and improves its strategies over time.

### Phase 3: Collaboration (Future)
*   **Swarm Mode**: Multiple specialized agents (Architect, Coder, Tester) working in parallel on different files.
*   **Voice Interface**: Natural language conversation for complex architectural discussions.
*   **Real-time Collaboration**: Live pairing with remote humans and other AI agents.
