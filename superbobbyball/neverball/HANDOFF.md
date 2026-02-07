# Session Handoff Log

**Date:** (Current Date)
**Branch:** `jules-16650573998442292503-005e549a`
**Version:** 1.6.1-dev

## Recent Accomplishments
*   **Campaign Hub:** Implemented `GAME_WARP` in `game_server.c` and `st_play.c` to allow level transitions via switches.
*   **Story Mode:** Added `st_story` for static cutscenes.
*   **Documentation:** Created `docs/DASHBOARD.md`, `VERSION`, and updated `CHANGELOG.md`.

## Current Context
*   The project is in **Phase 2** (Deluxe Expansion).
*   We are focusing on **Hub World** and **Party Game** features.
*   The `GAME_WARP` logic works conceptually but lacks a specific "Hub Level" asset to verify fully.

## Next Steps
1.  **Character Stats (Phase 3.1):** The codebase currently treats all balls identically. We need to implement `struct character_stats` to differentiate players (e.g., Heavy/Fast vs Light/Accurate).
2.  **Hub Geometry:** Create a basic `.sol` level for the Hub to test the warp logic.
3.  **UI:** Update the Party Menu or Character Select to allow choosing these stats.
