# Project Memory: Bobtrax Omni-Workspace

## 1. Project Architecture & Vision
*   **Monolithic Ecosystem:** Bobtrax is a meta-project serving as a unified command center orchestrating multiple major open-source audio workstations (DAWs) through git submodules.
*   **Integrated Submodules:**
    *   **Ardour** (Digital audio workstation, uses Waf)
    *   **LMMS** (Digital audio workstation, uses CMake)
    *   **MusE Sequencer** (MIDI/Audio sequencer, uses CMake)
    *   **Zrythm** (Automated DAW, uses CMake/Meson)
*   **The UI Layer (`bobui`):** A custom UI submodule that is currently a mirror/fork of **QtBase** (Qt 6 core). The long-term vision is for `bobui` to evolve into the unified frontend launcher and interface layer connecting these DAWs together.

## 2. Infrastructure & Tooling Decisions
*   **Unified Build System (`build.sh`):** A bash script at the root abstracts the varying build dependencies (CMake vs. Waf) across the submodules, supporting specific build flags like `--only-lmms` for targeted compilations.
*   **Continuous Integration (`ci.yml`):** A robust GitHub Actions pipeline pulls all submodules recursively, installs heavy audio/UI packages (ALSA, JACK, GTK3, Sndfile, etc.), and executes the unified `build.sh` to prevent regressions.
*   **Interim Launchers (`launcher.py` and `gui_launcher.py`):** 
    *   Because `bobui` is currently just QtBase and lacks frontend logic, interim launchers bridge the gap.
    *   `launcher.py` acts as a unified CLI launcher, and `gui_launcher.py` provides a lightweight Tkinter-based graphical window.
    *   *Design Pattern:* Both spawn the compiled DAW binaries as detached child processes via `subprocess.run/Popen`. This insulates the user's music sessions from launcher crashes.

## 3. Strict Documentation & Versioning Patterns
*   **The Universal Rulebook:** The core instructions (`docs/UNIVERSAL_LLM_INSTRUCTIONS.md`) govern all LLM actions (Claude, Gemini, GPT) across the monorepo to ensure consistency.
*   **Single Source of Truth Versioning:** The `VERSION.md` file tracks the single absolute version of the ecosystem (currently `1.0.5`). 
*   **Synchronized Update Cycle:** Every feature or task completed requires:
    1. Bumping the semantic version in `VERSION.md`.
    2. Prepending a detailed entry in `CHANGELOG.md`.
    3. Documenting the changes in `TODO.md` and `ROADMAP.md`.
    4. Committing with the version referenced.
*   **Context Passing:** `MEMORY.md` and `HANDOFF.md` act as state-preservation files between sessions and different AI agents.

## 4. Future Directions (From IDEAS.md & ROADMAP.md)
*   **Inter-process Communication (IPC):** Establishing a shared state between the varying DAWs.
*   **Cross-DAW Plugin Wrapping:** Creating a bridge to share VST/LV2 plugins across LMMS, Ardour, etc.
*   **AI Integration:** Injecting Small Language Models (SLMs) for autonomous mixing assistance and stem separation into the `bobui` layer.
*   **WebAssembly Porting:** Exploring WASM compilation of core C/C++ audio engines for browser-based collaboration.