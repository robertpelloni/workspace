# Changelog

## [0.1.1] - Massive Rust Port Initialization
- Resolved missing `Cargo.toml` error by officially initializing the central Cargo workspace.
- Updated core project directives (ROADMAP, TODO, VISION) to mandate the translation and consolidation of all previous submodules into this massive Rust app.

## [0.1.0] - Initial Setup
- Created baseline documentation scaffolding.
## [0.1.2] - FFR Difficulty Model Scaffolding
- Synced submodules to local workspace.
- Initialized Rust port for the `ffr-difficulty-model`.
- Scaffolded predictor and feature calculation interfaces.

## [0.1.3] - 2024-06-21
### Added
- Ported `NoteList` and `NoteSet` structures from `arrowvortex` to safe Rust.
- Ported `TimingData`, `Event`, and `Signature` structures from `arrowvortex`.
### Fixed
- Fixed the `.sm` file parser (`load_sm.rs`) to use the encapsulated `NoteList::append` method.
- Resolved compilation recovery errors with the Segment code logic.

## [0.1.4] - 2024-06-21
### Added
- Ported `dataset_json.py` from `ddc` to `DatasetJsonGenerator` in native Rust.
- Included the `rand` crate to handle random dataset shuffling natively.

## [0.1.5] - 2024-06-21
### Added
- Ported `create_splits.py` from `ddc` to `DatasetSplitter` in native Rust `create_splits.rs`.

## [0.1.6] - 2024-06-21
### Added
- Ported `util.py` logic from `ddc_onset` into `src/ddc_onset/util.rs`.
- Implemented native Rust peak-finding algorithms and 1D Hamming convolution (replacing `scipy` dependencies).

## [0.1.7] - 2024-06-21
### Added
- Ported `constants.py` from `ddc_onset` into native Rust `constants.rs`.

## [0.1.8] - 2024-06-22
### Refined
- Replaced stub CNN logic in `src/ddc_onset/cnn.rs` with explicitly typed `Conv2dDef`, `MaxPool2dDef`, and `LinearDef` structural outlines for `PlacementCNN` boundary iteration without PyTorch dependency bloat.

## [0.1.9] - 2024-06-22
### Added
- Ported `util.py` logic from `ddc` into native Rust string sanitizers (`ezname`) in `src/ddc/util.rs`.

## [0.1.17] - 2024-06-22
### Fixed
- Reconciled and sanitized the `git` submodule pointers across branches to ensure safe merging of `main` without destroying detached heads (`beatoraja`, `bobmania`, `hymnmania`).

## [1.0.0] - 2024-06-24
### Changed
- Major architectural pivot: Transitioned core orchestration structure to a **Go-first architecture** representing "Jules Autopilot".
- Overrode legacy monolithic tracking; established `backend-go` entry point serving API/JSON manifest parameters.

## [1.0.1] - 2024-06-25
### Added
- Linked the `backend-go` runtime directly to a local `SQLite` driver instance utilizing `gorm.io/gorm`.
- Auto-migrated `MemoryChunk` and `Session` database struct bounds per the dual-layer RAG indexing roadmap requirements.
