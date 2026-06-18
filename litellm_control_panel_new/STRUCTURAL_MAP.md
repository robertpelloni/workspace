# Structural Map: FreeLLM (Go Edition)

## Core Logic
- `cmd/app/main.go`: Entry point, system tray management, background worker orchestration, and single-instance enforcement.
- `internal/engine/`: Concurrent benchmarking engine, TTFT measurement, and weighted scoring logic.
- `internal/proxy/`: OpenAI-compatible stable gateway with request queueing (in-memory & disk-backed), routing, and multi-model rotation.
- `internal/db/`: SQLite data layer for rankings, usage logging, stability metrics, and queue persistence.
- `internal/config/`: YAML configuration management (hot-reloading) and Windows-specific registry integration.

## UI Components (Embedded Web Server)
- `internal/ui/server.go`: HTTP/WebSocket server for API and dashboard assets.
- `internal/ui/static/`: Embedded HTML, CSS, and JavaScript for the monitoring dashboard.
- `internal/ui/static/js/app.js`: Frontend logic for real-time charts, WebSocket logs, and interactive testing.

## Documentation & Governance
- `VISION.md`: Project goals and connection stability philosophy.
- `MEMORY.md`: Architectural traits and design decisions.
- `ROADMAP.md`: Long-term structural milestones.
- `TODO.md`: Immediate tasks and completed features.
- `VERSION.md`: Current version (v4.1.0).
- `CHANGELOG.md`: Detailed feature and fix history.

## Submodules
- `freellm_repo/`: Official FreeLLM repository for parity reference and integration.
