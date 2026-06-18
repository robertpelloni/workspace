# Memory: LiteLLM Control Panel Architectural Observations (Go Transition)

## Codebase Traits
- **Language:** Go (Golang)
- **Concurrency:** Goroutines and Channels for benchmarking and request queueing.
- **GUI Framework:** `systray` (System Tray), Web-based or Fyne for dashboards.
- **Networking:** Native `net/http` for the OpenAI-compatible proxy.
- **Storage:** SQLite (via `go-sqlite3` or `modernc.org/sqlite`) for persistent tracking.

## Design Preferences
- **Buffered Gateway:** Implementation of a request queue to ensure "Highly Stable Network" behavior.
- **Decoupled Architecture:** Benchmarking engine runs independently of the proxy server.
- **Favor Large Models:** Strict >= 100B parameter filter (configurable).
- **Circuit Breaking:** Failure counts used to temporarily isolate unstable models.
- **LiteLLM Compatibility:** Maintaining full OpenAI-format support for seamless drop-in replacement.

## Discovered Optimizations
- Using Go's `http.ReverseProxy` as a base for the gateway logic.
- Implementing a custom `RoundTripper` to handle retries, fallbacks, and buffering.
- Go's native compilation provides a single, portable binary for easy deployment.
