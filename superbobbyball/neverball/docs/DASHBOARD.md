# Project Dashboard

## Project Structure

This repository contains the source code for **Neverball**, a 3D rolling ball game engine, now evolving to support Super Monkey Ball feature parity.

### Directory Layout

*   **`ball/`**: Core game logic for Neverball.
    *   `game_server.c`: Main physics simulation and game rules loop.
    *   `game_client.c`: Client-side state interpolation and visual management.
    *   `game_draw.c`: Rendering logic.
    *   `st_*.c`: Game states (e.g., `st_play.c` for gameplay, `st_title.c` for menus, `st_party.c` for party modes).
    *   `progress.c`: Player progression, saving, and scoring stats.
*   **`putt/`**: Source code for Neverputt (minigolf companion game).
*   **`share/`**: Shared engine code used by both Ball and Putt.
    *   `solid_sim_sol.c`: Physics engine (collision detection, rigid body dynamics).
    *   `video.c`: OpenGL rendering context management.
    *   `gui.c`: Widget-based GUI system.
    *   `cmd.c`: Command queue protocol for Client-Server communication.
    *   `geom.c`: Geometry loading and management.
*   **`data/`**: Game assets (levels `.sol`, textures, sounds, fonts).
*   **`dist/`**: Distribution files (icons, desktop entries).
*   **`po/`**: Localization files.
*   **`scripts/`**: Utility scripts (versioning, asset processing).

## Dependencies

Neverball does not use Git submodules. Instead, it relies on system-installed libraries.

| Library | Version Requirement | Purpose | Location |
| :--- | :--- | :--- | :--- |
| **SDL2** | 2.0+ | Windowing, Input, Audio, Context | System Lib |
| **OpenGL** | 1.2+ (GLES supported) | Rendering | System Lib |
| **libpng** | 1.6+ | Texture Loading | System Lib |
| **libjpeg** | 6b+ | Texture Loading | System Lib |
| **libvorbis** | Any | Audio Decoding | System Lib |
| **libcurl** | 7.x+ | Networking (Addons/Fetch) | System Lib |
| **Freetype** | 2.x | Font Rendering | System Lib |
| **PhysFS** | 3.x (Optional) | Virtual Filesystem | System Lib |
| **Gettext** | Any | Localization | System Lib |

## Build Status

*   **Current Branch:** `jules-16650573998442292503-005e549a`
*   **Version:** 1.6.1-dev (Campaign Engine Update)
*   **Recent Features:**
    *   Campaign Hub Engine (`GAME_WARP` logic).
    *   Party Mode Menu (`st_party`).
    *   Story Cutscenes (`st_story`).
    *   Split-screen Multiplayer Architecture.
