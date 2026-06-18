# Project Summary: PianoGame (formerly Synthesia)

## Architecture & Technology Stack
- **Language:** C++
- **Graphics/UI:** OpenGL
- **MIDI Parsing:** Custom `libmidi` library embedded in the project.
- **Platform Support:** The project uses native OS APIs. It has a Visual Studio `.sln` and `.vcproj` setup for Windows (`registry.cpp`, `<Windows.h>`) and an Xcode `.xcodeproj` setup for MacOS (`Carbon/Carbon.h`). It lacks a unified build system (like CMake) and does not compile natively on Linux out of the box.

## Design Patterns & Decisions
- **State Management:** The application uses a GameStateManager to switch between different modes (e.g., `State_Title`, `State_Playing`, `State_TrackSelection`, `State_Stats`). Each state handles its own rendering and logic update loop.
- **Configuration:** User settings are managed via the `UserSettings` namespace, which abstracts the underlying OS configuration storage (e.g., Windows Registry or MacOS CFPreferences).
- **String Handling:** Due to the complexities of handling cross-platform strings in older C++, the project heavily relies on macros like `STRING()` and `WSTRING()`, as well as a utility file `string_util.h` for `std::wstring` conversions.
- **Hardcoding (Legacy):** Many settings and display values were historically hardcoded (e.g., `LeadIn` and `LeadOut` timing for songs). A major ongoing refactoring pattern is identifying these static constants and migrating them to `UserSettings` or separate configuration files.
- **Testing:** There are no automated unit tests. Testing relies on manual execution based on test plans documented in `testing/test_plan.txt`.

## Documentation & Versioning
- **Documentation Strategy:** Comprehensive documentation is maintained in the `docs/` directory, including `VISION.md`, `ROADMAP.md`, `TODO.md`, `CHANGELOG.md`, `VERSION.md`, `HANDOFF.md`, and `DEPLOY.md`.
- **Versioning:** The single source of truth for versions is meant to be standardized. Currently, the version is manually synchronized between `docs/VERSION.md`, `docs/CHANGELOG.md`, the C++ header `src/version.h` (`PianoGameVersionString`), and the `nsis_installer_script.nsi`.
- **AI Agent Instructions:** Project guidelines for AI assistants are kept in `docs/AGENTS.md` (general project guidelines) with specific files for models like `CLAUDE.md`, `GEMINI.md`, and `GPT.md`.

## Key Limitations & Tradeoffs
- Cross-platform development is hindered by direct dependencies on OS-specific windowing and system APIs rather than a cross-platform abstraction layer (like SDL or GLFW).
- Lack of continuous integration (CI) or automated tests means visual and behavioral verification must be performed manually.
- Memory management occasionally uses raw pointers that require manual deletion, which is noted in various TODO comments across the codebase as technical debt.