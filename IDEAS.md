# Omni-Workspace Ideas & High-Leverage Improvements

*Last Updated: 2026-11-15 (v5.311.0 — Protocol #302)*

> See also [MASTER_IDEAS.md](MASTER_IDEAS.md) for the long-horizon architectural charter. This file tracks concrete, near-term engineering improvements surfaced across recent Executive Protocols.

## 1. Control Center (`:2999`) & System Tray Enhancements
- **Shipped in `v2.1.0`–`v2.2.0` (Protocols #301–#302):**
  - [x] **Live Session Bus Feed & Broadcast in `:2999`:** Added `GET /api/session-bus` & `POST /api/session-bus/send` polling HyperNexus `:7778` scratchpad (`bus:reg:*`, `bus:msg:*`) with selftest noise filtering and live broadcast composer.
  - [x] **Root Pin Alignment / Drift Badges & Multi-Org Ownership:** Added `PINNED` / `DRIFT` badges (`git ls-tree HEAD`) and multi-org recognition (`robertpelloni`, `UnitedBeatsLLC`, `FWBerLLC`, `RealEstateCRMLLC`) across the 134-submodule matrix, plus expanded Go binary management from `10` to `12` (`freellm.exe` + `bobtk.exe`).
  - [x] **Windows Startup Shortcut Toggle:** Added optional `"Run Tray on Windows Login"` toggle in `tray_controller.ps1`.
  - [x] **Async `ahead/behind` Origin Divergence & Actionable Branch Scanner (`v2.2.0`):** Added 6-worker background scanner (`refreshGitDivergenceSnapshot` + `POST /api/submodules/refresh-divergence`), `hymnmania` junction detection (`133/134`), and Section 4 `Origin / Branches` column & filters.
- **Next Up (`v2.3.0`):** Add one-click nested-submodule (`509`-repo) deep divergence & health drill-down drawer per root submodule in `:2999`.

## 2. Quota-Resilient Multi-Harness Failover
- **Automatic Rate-Limit Handover:** When a primary harness hits provider quota exhaustion (such as Muse `429 Subscription quota exhausted`), emit a structured `[bus-msg] HANDOVER_REQUEST` on `session-bus.mjs` so Antigravity, Pi-Mono (`pi-go.exe`), or Codex picks up the in-flight `sync_protocol_NNN` ledger automatically without losing a beat.

## 3. Submodule & Security Hygiene
- **Deep Recursive `HEAD..<ref>` Audit in Control Center:** Integrate the Protocol #300 509-submodule recursive scanner (`HEAD..<ref>` across nested submodules and `SKIP_REPOS` overrides) into Control Center `:2999` so feature branches hidden behind stale `origin/HEAD` pointers are immediately visible.
- **Automated Dependabot Batch Verifier:** Run isolated test-builds on incoming Dependabot PR branches in a `D:\agent-cache` worktree before merging.
- **HyperNexus SQLite Quiesce Helper:** Add a clean `/api/admin/checkpoint` endpoint to HyperNexus `:7778` to flush WAL + snapshot `tormentnexus.db` safely during a scheduled 2-minute maintenance window.
