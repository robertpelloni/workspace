# Changelog

All notable changes to this project will be documented in this file.

## [0.1.5] - 2025-12-27

### Changed
- **Submodules**: Updated all submodules to latest upstream versions and merged upstream changes.
- **Dashboard**: Updated `docs/dashboard.md` with latest submodule status and project structure explanation.
- **Maintenance**: Merged all feature branches into `main` and ensured clean state.

## [0.1.4] - 2025-12-27

### Changed
- **Environment**: Standardized development environment on Java 21 to resolve Gradle 8.8 compatibility issues.
- **Documentation**: Consolidated and updated `LLM_INSTRUCTIONS.md` to serve as the single source of truth for all AI models.
- **Documentation**: Updated `docs/dashboard.md` with current submodule hashes and build status.

## [0.1.3] - 2025-12-26

### Added
- **Project Merging**: Implemented full project merging capabilities. Users can now merge maps, tilesets, palettes, sprites, and other data from another project zip file into the current project.
- **Documentation**: Updated `LLM_INSTRUCTIONS.md` with strict versioning protocols.
- **Dashboard**: Updated `docs/dashboard.md` with latest submodule status.

### Changed
- **Submodules**: Updated all submodules to latest upstream versions.
- **Branches**: Merged all local feature branches into `main`.
- **Versioning**: Incremented version to 0.1.3.

## [0.1.2] - 2025-12-25

### Added
- **Import Image to Tileset**: New feature in `Tileset Tools` menu allowing users to import BMP/PNG images directly into the tileset. Supports appending or overwriting, and automatically matches or adds colors to the palette.
- **Pattern Fill**: `MapCanvas` now supports filling a selection with a pattern from the tileset selection (tiling).
- **Random Sprite Export**: Added "Export Random Sprites" to Sprite Editor to export sprites marked as random.
- **Grid Layout**: Sprite Editor now displays frames in a responsive grid layout instead of a single line.
- **Palette Synchronization**: Implemented synchronized sorting and color addition across all tileset palettes to maintain consistency when modifying the master palette.

### Changed
- **Optimized Redo**: Improved performance of the Redo operation in `MapCanvas`.
- **Documentation**: Updated `dashboard.md`, `LLM_INSTRUCTIONS.md`, and `ROADMAP.md`.
- **Versioning**: Project now references `VERSION.md`.

### Fixed
- Fixed `GameSave.java` compilation errors (previous session).
- Fixed `SEFrameCanvas` painting logic.

## [0.1.1] - 2025-12-25

### Fixed
- Resolved compilation errors in `GameSave.java` by removing duplicate methods and fixing structure.
- Fixed duplicate field definitions in `CustomGameEditor.java`.
- Fixed missing method calls in `GLUtils.java` by correcting `BitmapFont` import.
- Fixed missing variables in `GameLogic.java`.

## [0.1.0] - 2025-12-25

### Added
- `docs/dashboard.md`: Project dashboard with submodule status and structure explanation.
- `VERSION.md`: Single source of truth for project version.
- `LLM_INSTRUCTIONS.md`: Unified instructions for AI assistants.

### Changed
- Merged feature branches:
    - `modernize-codebase-final-polish`
    - `modernize-codebase-polish`
    - `modernize-codebase-polish-2`
    - `modernize-java-project-part-2`
    - `new-feature-branch`
- Updated all submodules to latest upstream versions.
- Fixed `cpp_repo` submodule issue.
