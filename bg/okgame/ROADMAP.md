# Project Roadmap

## Status: Active Development
**Current Version:** 0.1.8

## In Progress
*   [ ] **Split large files** (BobsGameMenus.cpp, CustomGameEditor.cpp, GameLogic.cpp)

## Completed Features
*   [x] **CI/CD Pipeline (0.1.8)**
    *   [x] GitHub Actions workflow for Windows (VS2022) and Linux (GCC)
    *   [x] Submodule and build caching
    *   [x] Artifact upload for build outputs
*   [x] **Documentation Overhaul (0.1.7)**
    *   [x] Comprehensive AGENTS.md with architecture, conventions, code map.
    *   [x] Subdirectory AGENTS.md for Engine, Puzzle, Utility.
    *   [x] Complete SUBMODULES.md dashboard (89 submodules).
    *   [x] Standardized LLM instruction files.
*   [x] **Submodule Updates**
    *   [x] Update all submodules to latest upstream.
    *   [x] Fix broken submodule references (e.g., `lib/CLove`).
*   [x] **Refactoring**
    *   [x] `std::shared_ptr` migration for `BobsGame` textures.
*   [x] **Documentation**
    *   [x] Centralized Versioning (`VERSION.md`).
    *   [x] Universal LLM Instructions (`LLM_INSTRUCTIONS.md`).
    *   [x] Submodule Dashboard (`SUBMODULES.md`).
*   [x] Basic Engine Architecture (SDL2 based)
*   [x] Submodule Integration (Extensive library support)
*   [x] Initial Visualizer Submodules Added
*   [x] **Visualizer Integration**
    *   [x] Build System Update (`CMakeLists.txt` for `lib/projectm`)
    *   [x] Render Loop Integration (`BobsGame::render`)
    *   [x] Audio Input Feed (`AudioManager` -> `projectM::pcm_add`)
    *   [x] Preset Loading & Texture Paths

## Planned Features (Backlog)
*   **Game Modes**
    *   More game mode features, modes, and goals.
    *   Custom themes, sounds, and music.
*   **Multiplayer**
    *   Better multiplayer lobby with chat.
    *   Matchmaking by region or rank.
    *   Server verification.
    *   Spectator mode, replays, challenge replay.
*   **Platform Support**
    *   Android, iOS, and Browser support.
*   **Tournament Features**
    *   Ladders, regional and global.

## Technical Debt
*   [ ] Split large files: BobsGameMenus.cpp (212KB), CustomGameEditor.cpp (220KB), GameLogic.cpp (163KB)
*   [ ] Add namespaces to codebase
*   [ ] Clean up remaining raw pointers in networking code
*   [x] ~~Add CI/CD pipeline~~ (completed 0.1.8)

## Maintenance
*   [ ] Update all submodules to latest upstream.
*   [ ] Merge feature branches.
*   [ ] Continuous Integration/Deployment setup.
