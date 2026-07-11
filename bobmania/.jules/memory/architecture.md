reponse:default_api:read_file{result:# TODO - Immediate Tasks & Bug Fixes

## 1. Engine Stability & Bug Fixes
- [ ] **Memory Management:** Continue auditing manual memory management in legacy engine parts.
- [ ] **Async Networking:** Transition `BobcoinBridge` and `AssetSyncManager` to non-blocking network calls to prevent frame stutters.

## 2. Feature Completion
- [ ] **Tournament Brackets:** Implement visual bracket rendering in `ScreenTournamentLadder`.
- [ ] **P2P Swarm:** Move beyond stubs to actual `libtorrent` integration for pack distribution.

## 3. UI & UX Improvements
- [ ] **Skin Customization:** Add a dedicated UI for managing purchased NoteSkins and Avatars.
- [ ] **Chat Polishing:** Implement emojis and rich text in the global chat.
}reponse:default_api:read_file{result:# Unified StepMania Roadmap

## Milestone 1: The Unified Dashboard (Completed)
- [x] Create ScreenDashboard as the central hub.
- [x] Integrate Gym, Market, and Tournament shortcuts.
- [x] Implement basic Bobcoin wallet UI.

## Milestone 2: Economy & Engine Parity (Completed)
- [x] Functional Bobcoin JSON-RPC Bridge.
- [x] Mine Fix (DinsFire64) and Phantom Hold Fix.
- [x] Ghost NoteField for replays.
- [x] Persistent ELO tracking in Gym.

## Milestone 3: Tournament Mode & Advanced Networking (In Progress)
- [ ] **Visual Brackets**: Render the tournament ladder dynamically in Lua.
- [ ] **Async Network Architecture**: Move all blocking RPC calls to background threads.
- [ ] **P2P Content Swarm**: Implement libtorrent for decentralized song pack distribution.

## Milestone 4: Career & Social (Planned)
- [ ] **Mission Mode**: Full quest system with unlockable rewards.
- [ ] **Global Chat**: Cross-server communication with rich media.
- [ ] **Guilds**: Create and manage player teams.

## Milestone 5: Polish & Deployment (Future)
- [ ] CI/CD for automated builds on Windows, Linux, and macOS.
- [ ] Unified Installer and Launcher.
}
## Unified StepMania: Architecture, Patterns, and Decisions

### Core Architecture: The Singleton Manager Pattern
Unified StepMania is built on a robust **Singleton Manager** architecture. All high-level subsystems are encapsulated in global managers that are initialized and destroyed in `src/StepMania.cpp`. This centralizes control and ensures that engine state is accessible throughout the codebase, including via Lua.
*   **Key Managers:** `ECONOMYMAN`, `GYMMAN`, `TOURNAMENTMAN`, `SWARMMAN`, `ASSETSYNCMAN`, `UNIFIED_NET`, `SPECTATORMAN`, `REPLAYMAN`.
*   **Ownership:** Modern managers use `std::unique_ptr` for safe lifecycle management.
*   **Engine Integration:** Managers hook into the main `GameLoop` for frame-by-frame updates, critical for real-time features like heart rate monitoring and network packet handling.

### Networking & Economy (Bobcoin)
The project integrates a virtual economy powered by **Bobcoin**, designed for a "Play-to-Earn" ecosystem.
*   **`BobcoinBridge`**: A JSON-RPC client using `EzSockets` to interact with Bobcoin nodes. It is currently transitioning from blocking to **asynchronous** calls using worker threads to prevent gameplay stutters.
*   **`UnifiedNetwork`**: A unified packet system for all game networking (Tournaments, Spectator TV, Chat). It uses a callback-based architecture, allowing subsystems to register for specific packet IDs.
*   **`AssetSyncManager`**: Synchronizes player data (Economy balances, Gym profiles) with the cloud using background file transfers.

### Gameplay Parity & Simulation
A primary directive is to unify logic from diverse StepMania forks:
*   **Mine & Hold Fixes**: Incorporates the "DinsFire64 Mine Fix" and "Phantom Hold Fix" to ensure competitive integrity.
*   **Ghost NoteField**: A specialized system in `Player.cpp` that allows for the real-time visualization of replays (ghosts) alongside the active player, improving the competitive and training experience.
*   **Wife3/MSD**: Ongoing integration of Etterna-style scoring and difficulty calculation metrics.

### Fitness & Gym Mode
Unified StepMania includes a dedicated **Gym Mode** focused on physical health.
*   **`GymManager`**: Manages biometric profiles (Weight, BMI, ELO) and workout history. Crucially, this is decoupled from the main player `Profile` to ensure privacy and specialized tracking.
*   **Heart Rate Integration**: Support for native heart rate monitors (`WinRT`/`BlueZ`), with a robust mock driver for testing that simulates heart rate variability based on gameplay intensity.

### Developer Experience & Extension
*   **Lua-First Design**: Almost all C++ manager functionality is exposed to Lua via `Luna` bindings. This empowers theme developers to build rich, reactive UIs without needing to touch core engine code.
*   **VFS (RageFile)**: All file I/O, including centralized versioning in `VERSION.md`, uses the `RageFile` virtual filesystem for cross-platform stability.
*   **Modernization Directive**: The codebase is being actively refactored to use C++17 standards, replacing legacy raw pointers and manual memory management with modern equivalents.

### Roadmap Priorities
The project is currently moving into **Milestone 3: Advanced Networking & Tournament UI**, focusing on non-blocking RPC calls, dynamic visual brackets, and P2P content distribution via `libtorrent`.

---

### Revised Plan

1. *Transition `BobcoinBridge` to non-blocking network calls using `RageWorkerThread`.*
   - Refactor `BobcoinBridge` to queue RPC requests and handle responses via callbacks, ensuring the main gameplay thread never stalls.
2. *Implement visual bracket rendering in `ScreenTournamentLadder`.*
   - Develop the logic to translate tournament ladder data into a visual structure and expose it via Lua for the theme to render.
3. *Complete pre commit steps.*
   - Ensure proper testing, verification, review, and reflection are done.
4. *Submit the change.*
   - Once all tests pass and features are verified, I will submit the changes.