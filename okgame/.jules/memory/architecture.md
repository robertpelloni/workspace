### 1. Architectural Mission
*   **Context:** `okgame` is the definitive C++ reference implementation of the "unified puzzle engine" and RPG framework, originally developed in Java (LibGDX) and TypeScript.
*   **1:1 Parity Standard:** The primary mandate is strict functional, logical, and data parity with the Java reference implementation (`lib/bobsgameonlinejava`). This ensures the C++ version remains a drop-in replacement, consuming the same `gameData` bundles and maintaining frame-perfect state synchronization.
*   **Operating Philosophy:** Autopilot execution with continuous documentation updates and seamless wiring of backend data structures to GWEN-based frontend UI components.

### 2. Core Technical Foundation
*   **Graphics & Windowing:**
    *   **Backend:** OpenGL 3.3 Core Profile.
    *   **Abstraction Layer:** SDL3 (migrated from SDL2) for window management, hardware input, and event polling.
    *   **Reactive Visuals:** Integration of **projectM** and **MilkDrop3** for music-synced shader effects.
*   **UI Framework:**
    *   **GWEN (`Gwen::Controls`):** Utilizes a customized `TexturedBase` skin to provide a windowed "OS-within-a-game" aesthetic. This supports complex menus, tabbed editors, and interactive forms natively in C++.
*   **Memory Management:**
    *   **Smart Pointers:** Pervasive use of `std::shared_ptr` (aliased as `sp<T>`) and `std::make_shared` (aliased as `ms<T>`) in `oktypes.h` to ensure safe object lifecycles across state transitions.

### 3. Engineering Patterns & Standards
*   **ECS (Entity Component System):**
    *   **Entities:** Managed as unique numeric IDs within a centralized `World`.
    *   **Components:** Logic-less data containers (e.g., `Transform`, `Sprite`, `EventSheet`, `Combat`).
    *   **Systems:** Dedicated logic units (`VisualScriptSystem`, `BehaviorSystem`, `CombatSystem`, `RenderSystem`) that process filtered entity sets.
*   **Data-Driven Visual Scripting:**
    *   **EventSheet Architecture:** A hierarchical system of Blocks, Conditions, and Actions defined in data. Executed at runtime by the ECS, mirroring the Java reference's logic.
*   **Serialization & Asset Loading:**
    *   **Compatibility:** C++ classes implement `initFromString` methods that parse text configuration to match Java behavior exactly.
    *   **Pipeline:** `GameDataLoader` handles runtime decompression of Base64-encoded Zlib data using `miniz` and `lz4`, populating the engine's resource managers.

### 4. Key Subsystems
*   **RPG Engine:** Managed via `RPGDatabase.h`, centralizing Actors, Items, Enemies, and Maps.
*   **Puzzle Kernel:** Governed by a monolithic `GameType` structure defining all grid-based mechanics, gravity rules, and randomizers.
*   **Input Mapping:** `ControlsManager` provides an abstraction layer between hardware events and high-level game states (e.g., `BGCLIENT_UP_HELD`).
*   **Combat System:** A turn-based state machine integrated into the ECS for entity interactions.

---

### Revised Plan for Phase 2: Engine Polish and Feature Parity

1. *Refine the Combat System.*
   - Expand the current `CombatSystem` state machine to support complex interactions (Items, Skills) defined in the ported `RPGDatabase`.
2. *Expand Map and Sprite Editors.*
   - Implement detailed property editing in `RPGEditorControl` for Map and Sprite data, moving beyond simple list views to match the Java editor's depth.
3. *Modernize Rendering Pipeline.*
   - Update RPG engine and Puzzle renderer calls to utilize SDL3 vertex arrays for improved performance.
4. *Verify Multiplayer Logic Parity.*
   - Audit the WebSocket communication in `NetworkManager.cpp` to ensure 1:1 message format parity with the Java/TypeScript implementations.
5. *Complete pre-commit steps.*
   - Ensure proper testing, verification, review, and reflection are done.
6. *Submit the change.*