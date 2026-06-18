# Changelog

## [4.5.0] - 2025-05-22
### Added
- Modular Go architecture replacing the legacy Python implementation.
- Highly Stable Proxy Gateway with internal request queueing and worker pools.
- SQLite-backed request persistence for zero-drop connection reliability.
- Embedded Web Dashboard with Chart.js analytics and WebSocket log streaming.
- Health check endpoints (`/health`, `/health/liveness`, `/health/readiness`).
- Side-by-side Model Comparison UI.
- Integrated `freellm` as a submodule for architecture parity.

### Fixed
- Fixed closure capture issues in `cmd/app/main.go` that prevented compilation.
- Resolved missing `/api/providers/health` endpoint for dashboard statistics.
- Improved database migration safety for `cost_saved` column addition.

### Changed
- Transitioned to `modernc.org/sqlite` for pure-Go database functionality.
- Unified API key management for 14+ LLM providers.
- Optimized benchmarking engine for lower memory footprint using goroutines.

## [3.0.0] - 2025-05-21
### Added
- Initial Go port foundations.
- Basic benchmarking engine.
- SQLite schema migration logic.
