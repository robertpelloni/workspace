# Changelog

## [1.6.1-dev] - Campaign Engine & Party Update

### Added
- **Campaign Hub Engine:** Implemented `GAME_WARP` logic allowing level transitions via in-game switches, enabling non-linear Hub World navigation.
- **Story Mode:** Added `st_story` state for narrative cutscenes (static image + text).
- **Party Mode Menu:** Dedicated menu for selecting party games (Target, Fight, Race, Billiards, Bowling).
- **Split-Screen Support:** Refactored engine (`game_server`, `game_client`, `game_draw`) to support up to 4 local players with independent viewports.
- **Monkey Billiards:** New game mode with 16-ball physics, cue stick rendering, and pocket logic.
- **Monkey Bowling:** New game mode with pin physics and frame scoring.
- **Monkey Fight:** New game mode with punch mechanics (`CMD_PUNCH`) and knockback.
- **Monkey Target:** New game mode with flight physics (lift/drag), landing zones, and instrument HUD.

### Changed
- Refactored `game_server.c` to handle arrays of player states (`server_player`).
- Updated `game_draw.c` to support "Ghost Rendering" and multiple viewports.
- Input system now routes events via `device_id` to specific players.

### Fixed
- Fixed build error by adding `st_story.o` and `st_party.o` to Makefile.
