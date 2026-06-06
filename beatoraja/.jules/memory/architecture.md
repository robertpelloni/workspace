## Project Architecture & Patterns
`beatoraja` is a cross-platform rhythm game simulator built in Java (Java 21 LTS) and managed via Gradle (v8.8 wrapper). Its core rendering and input loops run on **LibGDX** (migrating to LWJGL 3 backend) while its configuration launcher operates via **JavaFX**.

### 1. Structural Paradigm
* **Monolithic Controllers to Managers**: Historically anchored by the `MainController.java` god-class, the application is actively refactoring into discrete, purpose-built singletons/managers:
    * `InputManager`: Abstracts generic keyboard/controller input and gamepad polling.
    * `UpdateManager`: Dedicated thread handling SQLite interactions for songs/tables.
    * `DownloadManager`: Orchestrates background web crawling and IPFS peer streaming.
    * `ScreenshotManager`: Handles real-time screenshot capturing and Twitter4J sharing.
* **Database & Persistence**: Game state (IR connections, player preferences) uses simple config models (`Config`, `PlayerConfig`). Gameplay outcomes (`ScoreData`) and song metadata are persisted locally using **SQLite** mapped through Apache Commons `DBUtils`.
* **State Machine Approach**: Playback transitions are strictly modeled as finite states (`STATE_SELECTMUSIC`, `STATE_PLAYBMS`, `STATE_RESULT`, etc.).

### 2. Audio Engine
* Abstracted into a generic `<T>` format hierarchy via `PCM.java` (e.g. `FloatPCM`, `ShortDirectPCM`).
* Backends rely on raw streaming streams. Supports modern codecs natively via bindings like `jflac-codec` and `OggInputStream` from the `com.badlogic.gdx.backends.lwjgl3` package.
* Supports legacy `jasiohost` configurations, but moving towards unified `PortAudio` / `GdxSoundDriver`.

### 3. Rendering & Skinning Engine
* **Visuals**: Uses traditional 2D accelerated batching via LibGDX `SpriteBatch` (which is often wrapped or overridden as `SkinObjectRenderer` in the Skin hierarchy).
* **Skin Formats**: Inherits standard LR2 CSV skin parsers but modernizes the approach using JSON and dynamic Lua mappings.
* **Property Binding**: Variables like `NUMBER_TARGET2_SCORE` or `NUMBER_FAST_NOTES` are calculated within the backend (e.g., `JudgeManager`, `ScoreData`) and pushed to the renderer via `IntegerPropertyFactory` and `BooleanPropertyFactory`.

### 4. Format Decoding (BMS & Osu!)
* Maintains robust legacy parsing for BMS/BME/PMS formats utilizing the external `jbms-parser`.
* Includes an `OsuDecoder.java` that intercepts `.osu` Mania charts. This dynamically evaluates hit objects, decodes `CircleSize` into 4K-9K mapping properties, creates approximations for sliders, and dynamically translates `[Events]` blocks into `BMSModel` background layers (BGA), essentially making Osu! files identical to BMS files within the core loop.

### 5. Custom Systems
* **Arena Mode**: Real-time multiplayer implemented via TCP JSON packet exchange (`ArenaManager`). Syncs selected song hashes, real-time score variants (`score2`), and lobby configurations natively without a distinct matchmaking service.
* **Missions/Step-Up**: Robust, serializable mission criteria tracking implemented in `StepUpManager` and `MissionManager`, mapped to UI visual targets.

## Key Decisions & Directives

1. **Strict Versioning Protocol**: Java classes should **never** hardcode version strings. The absolute source of truth is `VERSION.md`. The project dynamically scans the classpath or local disk to read this at runtime (specifically constructed inside `MainController`).
2. **`bobcoin` Eradication**: As explicitly guided by the system owner, the `bobcoin` submodule and all references to it have been strictly prohibited and forcefully removed from the codebase and `.gitmodules`.
3. **Skipping Tests**: While JUnit 5 infrastructure exists (`ScoreDataTest`, `ArenaManagerTest`, etc.), authoring new tests is skipped to heavily favor rapid feature iteration, unless absolutely necessary for safety.
4. **Documentation Driven Output**: Agents must heavily document context via markdown at the root level (`VISION.md`, `ROADMAP.md`, `MEMORY.md`, `TODO.md`, `CHANGELOG.md`). System instructions for specific models (Claude, Gemini, GPT) are also dynamically maintained here.
5. **Modernization Quirks**: The recent transition from LWJGL 2 to LWJGL 3 within LibGDX broke heavily coupled classes (specifically generic bounding on `PCM.java` and overrides like `SkinObjectRenderer`). When working within the `skin` or `audio` packages, extreme care must be taken with legacy backend imports.