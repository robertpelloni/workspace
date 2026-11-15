# Omni-Workspace Ideas & High-Leverage Improvements

*Last Updated: 2026-11-14 (v5.309.0 — Protocol #300)*

> See also [MASTER_IDEAS.md](MASTER_IDEAS.md) for the long-horizon architectural charter. This file tracks concrete, near-term engineering improvements surfaced across recent Executive Protocols.

## 1. Control Center (`:2999`) & System Tray Enhancements
- **Live Session Bus Feed in `:2999`:** Add a read-only panel in `research/workspace-orchestrator` polling `HyperNexus` `/api/agent-memory/recent` so recent `session-bus` messages across Muse, Antigravity, and Codex appear alongside port telemetry.
- **One-Click Pincheck & Divergence Badge:** Surface `ahead/behind` counts per submodule in the `:2999` Submodule Matrix using background `git for-each-ref` snapshots.
- **Windows Startup Shortcut Toggle:** Add an optional "Run Tray on Login" toggle in `tray_controller.ps1` (writing/removing a shortcut in `%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup` only when explicitly toggled by Robert).

## 2. Quota-Resilient Multi-Harness Failover
- **Automatic Rate-Limit Handover:** When a primary harness hits provider quota exhaustion (such as Muse `429 Subscription quota exhausted`), emit a structured `[bus-msg] HANDOVER_REQUEST` on `session-bus.mjs` so Antigravity, Pi-Mono (`pi-go.exe`), or Codex picks up the in-flight `sync_protocol_NNN` ledger automatically without losing a beat.

## 3. Submodule & Security Hygiene
- **Deep Recursive `HEAD..<ref>` Audit in Control Center:** Integrate the Protocol #300 509-submodule recursive scanner (`HEAD..<ref>` across nested submodules and `SKIP_REPOS` overrides) into Control Center `:2999` so feature branches hidden behind stale `origin/HEAD` pointers are immediately visible.
- **Automated Dependabot Batch Verifier:** Run isolated test-builds on incoming Dependabot PR branches in a `D:\agent-cache` worktree before merging.
- **HyperNexus SQLite Quiesce Helper:** Add a clean `/api/admin/checkpoint` endpoint to HyperNexus `:7778` to flush WAL + snapshot `tormentnexus.db` safely during a scheduled 2-minute maintenance window.
