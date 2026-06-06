# Dependencies and Submodule Analysis

**Last Updated:** 2026-02-24

This document outlines the detailed research and inferred reasoning behind the selection of various libraries, submodules, and referenced projects within the Robert Pelloni Monorepo ecosystem. 

## 1. Top-Level Libraries & Frameworks

### **Browser Use (`browser-use`)**
- **Type:** Python Library (`pyproject.toml`)
- **Version:** `>=0.9.5`
- **Inferred Purpose:** Facilitates autonomous AI browser interaction and web scraping. Critical for agents within this ecosystem (like `agent-browser` skills and `borg`) that need to visually inspect or interact with web UIs, automate tasks across platforms, or gather live data.

### **Playwright (`@playwright/test`)**
- **Type:** NPM `devDependencies`
- **Version:** `^1.56.1`
- **Inferred Purpose:** Used extensively for end-to-end testing and forms the backbone of the `computeruse` and browser automation extensions in this monorepo. It powers the Model Context Protocol (MCP) server that grants AI agents the ability to navigate, click, and evaluate web pages contextually.

### **AI Core Frameworks (`mem0ai`, `opencode-ai`, `task-master-ai`)**
- **Type:** NPM `dependencies`
- **Inferred Purpose:** 
  - `mem0ai`: Likely powers the persistent memory layers across sessions (e.g., `claude-mem`).
  - `opencode-ai`: Provides the baseline agentic reasoning or API interaction capabilities for the automated development loops.
  - `task-master-ai`: Used for the orchestration and task delegation aspects (possibly tied into `Maestro` or `Spec-Flow` workflows).

### **Firecrawl (`firecrawl-mcp`)**
- **Type:** NPM `dependencies`
- **Inferred Purpose:** Integrates Firecrawl as an MCP server, giving agents the ability to scrape, crawl, and extract clean markdown from websites efficiently. Crucial for the `web_search` and deep research tools.

## 2. Core Submodules Breakdown

### **AI Orchestration & Agents**
*   **`aios` & `borg`:** The "AI Operating System" and multi-agent choreography bus. Built to route jobs between specialized agents (like GPT, Claude, and Gemini) using a centralized trpc/fastify backend.
*   **`metamcp` & `mcp-superassistant`:** The Model Context Protocol (MCP) infrastructure. `metamcp` acts as a proxy for cross-agent tool approval, while `superassistant` is the primary interface for tool execution.
*   **`antigravity-autopilot` & `jules-autopilot`:** Specialized orchestration runtimes. Jules appears to be a Google-driven development loop, while Antigravity is a robust background task executor.

### **Rhythm Games (`bobmani/*`)**
*   **`bobmania` & `itgmania`:** C++ forks of StepMania 5.1 and 3.95 respectively. Kept for legacy support and modern feature testing in arcade-style environments.
*   **`beatoraja`:** Java-based BMS simulator for precision rhythm gaming.
*   **`ddc` & `ddc_onset`:** Python-based machine learning models (Dance Diffusion) for automated beatmap/chart generation.

### **Full-Stack Ecosystem Applications**
*   **`fwber`:** A dating platform leveraging Laravel and Next.js, demonstrating traditional full-stack web application management within the monorepo.
*   **`bobcoin`:** A Solana/Node.js based cryptocurrency project ("Proof-of-health"), showing blockchain integration.
*   **`bobeditpro` & `bobfilez`:** Electron and Qt/C++ based desktop applications customized for a unified "Bob" user experience.

### **Collaborative/Partner Projects (mnmballa2323)**
*   **`Chamber.Law`:** Web-based collaborative legal workflow platform.
*   **`cointrade`:** A cryptocurrency trading platform leveraging various API integrations.
*   **`Azure.Cybersecurity`:** A .NET/Azure based sandbox for cybersecurity training.
*   **`Alti.Assistant` & `Alti.Code.Studio`:** Web IDEs and mobile assistants developed collaboratively.

## 3. Inferring the Monorepo Strategy
The sheer scale of this monorepo indicates a **"Federated Micro-Frontends/Microservices"** architecture, glued together by AI. Instead of maintaining separate CI/CD pipelines and context boundaries, all projects are forced into a single tree. This allows powerful AI agents (like Gemini with its 1M+ context window) to analyze sweeping architectural changes, execute coordinated refactors across dozens of disparate codebases (e.g., updating a shared UI library in `bobui` and instantly rippling it to `fwber` and `bobeditpro`), and maintain holistic project awareness.
