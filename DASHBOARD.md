# Project Dashboard

This dashboard provides a high-level overview of the project structure, including active submodules, their current status, and recent significant changes. It serves as a navigational aid and status report for developers working in this workspace.

## Project Structure Overview

The workspace is a mono-repo style collection of various tools, agents, applications, and libraries, primarily focused on AI orchestration, game development, and productivity tools.

Key high-level directories and their purposes:

*   **`AIOS/`**: The AI Operating System core.
*   **`opencode-autopilot/`**: The primary autopilot interface, recently migrated to a Next.js web application.
*   **`fwber/`**: A significant project component (Framework/Backend reference).
*   **`submodules/`**: Contains various Git submodules integrated into the project (e.g., `mcp-manager`).
*   **`tools/`**: Utility scripts and configuration files.
*   **`AI_COORDINATION/`**: Documentation and plans regarding AI model consensus and coordination.
*   **`consolidated-skills/`**: A collection of skill definitions and documentation for AI agents.

## Active Submodules

The following table lists the Git submodules currently initialized and tracked in this repository, along with their current version/commit hash.

| Submodule Name | Path | Description | Version/Status |
| :--- | :--- | :--- | :--- |
| **AIOS** | `AIOS` | AI Operating System Core | `19f9bee` (main) |
| **AirSim** | `AirSim` | Simulator for drones, cars and more | `1344870` (v1.1.8) |
| **ArrowVortex** | `ArrowVortex` | Rhythm game simulator/editor | `9e867fa` (v1.0.1) |
| **BobsGameOnline** | `BobsGameOnline` | Online game project | `4f3015f` (main) |
| **FileOrganizer** | `FileOrganizer` | File organization utility | `470c27b` (v2.1.0) |
| **JWildfire** | `JWildfire` | Java fractal flame editor | `999faa6` (master) |
| **LibreChat** | `LibreChat` | Enhanced ChatGPT Clone | `cda6d58` (v0.8.2-rc1) |
| **Neothesia** | `Neothesia` | Rhythm game focused on VSRG | `698a3f4` (v0.3.1) |
| **OmniParser** | `OmniParser` | Screen parsing tool for AI agents | `b0d5c9f` (v.2.0.1) |
| **Resume-Matcher** | `Resume-Matcher` | Resume matching utility | `8780069` (0.1.2) |
| **VERT** | `VERT` |  | `1dac5f6` (main) |
| **aichat** | `aichat` | All-in-one AI CLI tool | `ce3205d` (v0.30.0) |
| **beatoraja** | `beatoraja` | BMS player (Java) | `e510c73` (0.7.6) |
| **bobcoin** | `bobcoin` | Cryptocurrency project | `cdcaf43` (main) |
| **ccmanager** | `ccmanager` |  | `e06dd9d` (v2.9.2) |
| **changesets** | `changesets` | Monorepo versioning tool | `9657b26` (7.0.13) |
| **cherry-studio** | `cherry-studio` | AI Desktop Client | `dfbfc28` (v1.7.0-alpha.2) |
| **copyparty** | `copyparty` | Portable file server | `e9ab040` (v0.7.3) |
| **ddc** | `ddc` | Dance Dance Convolution | `01b1e69` (v1.0) |
| **echogarden** | `echogarden` | Speech synthesis tool | `7a60d1b` (v2.10.1) |
| **ffr-difficulty-model**| `ffr-difficulty-model`| Difficulty calculation model | `8422b3f` (master) |
| **fwber** | `fwber` | Framework/Backend | `9ee3b62` (v1.0.0-rc1) |
| **hellven** | `hellven` |  | `ae5d8ee` (main) |
| **itgmania** | `itgmania` | StepMania fork for ITG | `d1ae7a4` (v0.8.0) |
| **kapture** | `kapture` | Screen recording/capture | `a9ea1d9` (v2.0.0) |
| **libjxl** | `libjxl` | JPEG XL image format reference | `9174e63` (v0.11-snapshot) |
| **lootbox** | `lootbox` |  | `0ddfea5` (main) |
| **onyx** | `onyx` |  | `19b485c` (v1.8.0-beta.1) |
| **openevolve** | `openevolve` | Evolutionary algorithm framework | `970812a` (v0.2.18) |
| **plandex** | `plandex` | AI coding engine | `e2d7720` (cli/v2.2.1) |
| **raindrop-io-mcp** | `raindrop-io-mcp-server`| Raindrop.io MCP Integration | `7d52959` (main) |
| **raindropioapp** | `raindropioapp` | Raindrop.io Application | `459c0ad` (latest) |
| **robertpelloni.com** | `robertpelloni.com` | Personal website | `c92ccd5` (main) |
| **servers** | `servers` | MCP Server implementations | `c7c5497` (typescript-0.6.2) |
| **software-agent-sdk**| `software-agent-sdk` | SDK for software agents | `7ef3881` (1.0.0) |
| **stepmania** | `stepmania` | Rhythm game engine | `52a1dc3` (v5.1.0) |
| **mcp-manager** | `submodules/mcp-manager`| Model Context Protocol Manager | `66b4d03` (main) |
| **vcpkg** | `vcpkg` | C++ Library Manager | `0e39c10` (2022.02.02) |
| **web-ui** | `web-ui` | Web Interface | `7eb62d4` (v3.0.0) |
| **witsy** | `witsy` |  | `b9e169f` (v3.0.4) |

*Note: Many other submodules are defined in `.gitmodules` but may not be currently initialized or checked out in this specific environment.*

## Recent Changes & Status

### **`opencode-autopilot` Transformation**
The `opencode-autopilot` project has recently undergone a major architectural shift.
*   **Previous State:** Python/CLI based automation tool.
*   **Current State:** It has been converted into a **Next.js** web application.
*   **Structure:**
    *   `app/`: Contains the Next.js app router pages and layouts.
    *   `lib/`: Shared utility libraries.
    *   `public/`: Static assets.
    *   `package.json`: Updated with Next.js, React, and other frontend dependencies.
*   **Goal:** To provide a modern, web-based interface for the autopilot's capabilities, improving usability and accessibility.

### **General Workspace**
*   The workspace continues to integrate a diverse set of tools via submodules, allowing for a centralized development environment for AI and gaming projects.
*   Documentation files in the root (like `AI_FEATURES_CONSENSUS_PLAN_2025-11-08.md`) indicate ongoing high-level planning for AI features and orchestration.
