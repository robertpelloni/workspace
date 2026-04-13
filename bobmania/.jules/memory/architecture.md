# Unified StepMania: AI Developer Memory & Context

## Project Architecture & Patterns

1. **The "Manager" Pattern:**
   To avoid polluting the core engine (`src/StepMania.cpp`, `src/ScreenGameplay.cpp`) with endless conditional logic, all new features are encapsulated in global C++ Singleton Managers located in `src/` subdirectories (e.g., `src/Economy/EconomyManager.cpp`, `src/Gym/GymManager.cpp`, `src/Network/StreamManager.cpp`). 
   *   These managers are instantiated and deleted in `sm_main` within `src/StepMania.cpp`.
   *   They are hooked into the main update loop via `src/GameLoop.cpp`.
   *   They are bound to the Lua state using `Luna<T>`, allowing the UI to call them safely.
   *   They must be registered in the respective `CMakeData-singletons.cmake` files.

2. **Strict UI Separation (Lua 5.1):**
   *   The C++ backend handles pure logic (networking, math, hardware I/O, scoring).
   *   The Lua frontend (`Themes/default/`) handles **100%** of the user interface. We do not hardcode menus or UI elements in C++.
   *   We **rigidly enforce** Lua 5.1 sandboxing to maintain absolute compatibility with thousands of legacy StepMania 5.x themes and noteskins. Do not use Lua 5.3+ syntax (like true integers or bitwise operators).

3. **External Dependencies (The `extern/` folder):**
   *   We use vendored libraries for maximum cross-platform build stability without requiring users to configure package managers.
   *   Key dependencies include: `jsoncpp` (Network/Marketplace parsing), `zlib` (Content Swarm unpacking), `lua-5.1` (Scripting engine), and `bobcoin` (The mock cryptocurrency backbone).
   *   Hardware stubs (like FFmpeg for `StreamManager` or Bluetooth for `HeartRateManager`) must be carefully `#ifdef`'d or mocked entirely if the headers are missing on certain CI platforms to prevent build failures.

4. **Universal Configuration & Versioning:**
   *   The single source of truth for the version is the `VERSION` file in the repository root.
   *   Every commit must increment the version and include the version bump in the message (e.g., `chore: Add feature XYZ (v5.7.3)`).
   *   `Docs/UNIVERSAL_LLM_INSTRUCTIONS.md` (symlinked/referenced by `LLM_UNIVERSAL.md`, `AGENTS.md`, etc.) is the master guide for all AI developers. This prevents model drift and conflicting instructions between Claude, Gemini, and GPT.

5. **Modding & Gameplay Merges (The "Unified" Goal):**
   *   **Competitive Parity:** We use Etterna's `Wife3` (J4) scoring logic, integrated loosely into `ScoreKeeperNormal.cpp` and `PlayerStageStats`.
   *   **Visual Modding Parity:** We support NotITG-style visual hooks, including `ActorMultiVertex`, `ActorFrameTexture`, and Lua GLSL Shader manipulation.

6. **File I/O Safety:**
   *   Always use StepMania's `RageFile` wrapper for file operations to ensure cross-platform compatibility and correct virtual filesystem pathing (e.g., locking writes strictly to the `Save/` directory). Never use raw `std::fstream`.

## Recent Decisions & Developments

*   **Massive Conflict Resolution:** Successfully resolved over 90 nested, multi-layered Git merge conflicts across the codebase (`src/`, `CMake/`, `extern/`) caused by attempting to merge divergent forks (Etterna, ITGMania, NotITG) simultaneously. 
*   **Hardware Drivers for Gym Mode:** Decided to implement an `IHeartRateDriver` abstraction layer. `HeartRateManager` currently uses a `HeartRateDriver_Mock` (a sine wave generator simulating 80-140 BPM) to prevent the game loop from crashing or blocking while actual OS-level Bluetooth drivers (BlueZ/WinRT) are developed in Phase 2.
*   **CI Constraints & Maintenance:** GitHub Actions runners frequently deprecate older environments (e.g., macOS 13, Node 20). The CI workflows (`.github/workflows/ci.yml`) have been dynamically updated to target `macos-14` and to gracefully skip missing documentation files (`xmllint` checks on Lua.xml) rather than failing the entire build suite.
*   **Backend Stubs:** Transitioned the `EconomyManager` from parsing local XML ledgers to a pure RPC client stub. This prepares the system to bind directly to an actual `libbobcoin` blockchain node in the next development phase.