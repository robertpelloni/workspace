# TODO: LiteLLM Control Panel (Go Transition)

## Milestone 4.x Tasks
- [ ] Implement Response Transformation Layer (map back to OpenAI format).
- [ ] Externalize all provider endpoints to `litellm-config.yaml`.
- [ ] Implement Redis auth and connection pool settings.
- [ ] Add unit tests for `internal/ui` API endpoints.
- [ ] Implement disk-backed persistent logs (archive old logs).

## Completed (Go Milestone)
- [x] Disk-backed request queue (pending_requests table).
- [x] Visual Analytics with Chart.js.
- [x] WebSocket log streaming.
- [x] Side-by-side Model Comparison.
- [x] Proactive Health Monitor.
- [x] USD Cost Savings tracking.
- [x] Quick Query interactive chat.
- [x] Go implementation of all core providers (12+).
- [x] Request prioritization (X-LiteLLM-Priority).
- [x] Redis Caching support.
- [x] Global search in web dashboard.
- [x] Embedded static assets (go:embed).
