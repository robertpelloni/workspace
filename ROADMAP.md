# Project Roadmap

## Current Status (v1.0.4)
- [x] **Git Repair**: Fixed recursive submodule definitions (`aios`, `bobcoin`, `filez`) and resolved merge conflicts.
- [x] **Agent Setup**: Installed and verified `trae-agent` (local), `ii-agent` (local), and `junie` (global).
- [x] **Inventory**: Generated comprehensive `DASHBOARD.md` listing 519 active submodules.
- [x] **Structure Analysis**: Created `AGENTS.md` identifying project-specific conventions and deviations.

## Short-term Goals (v1.1.0)
- [ ] **Standardization**:
    - [ ] Enforce `src/` layout for new Python modules in `aios`.
    - [ ] Consolidate Node.js projects to use `pnpm` exclusively.
- [ ] **Build Unification**:
    - [ ] Migrate legacy Makefiles in `ITGMania` to CMake where feasible.
    - [ ] Standardize `vcpkg` integration across C++ projects.
- [ ] **Agent Orchestration**:
    - [ ] Integrate `trae-agent` into the central orchestration loop.
    - [ ] Establish communication protocol between `ii-agent` and `aios`.

## Medium-term Goals (v1.2.0)
- [ ] **Unified Interface**: Create a CLI or Web UI wrapper that exposes key functionalities of the underlying submodules.
- [ ] **Performance Optimization**: Analyze and optimize the build and update process for the large number of submodules.

## Long-term Vision (v2.0.0+)
- [ ] **Fully Autonomous Agent Swarm**: Enable agents to self-update, self-heal, and collaborate on complex tasks without human intervention.
- [ ] **Marketplace Integration**: Allow dynamic addition/removal of capabilities via an extension marketplace.
- [ ] **Global Knowledge Graph**: Implement a shared memory structure accessible by all agents.
