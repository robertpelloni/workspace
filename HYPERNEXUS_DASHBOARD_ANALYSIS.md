# HyperNexus Dashboard — Consolidation Analysis (Leader, 2026-11-26)

Source: live inventory of `HyperNexus/apps/web/src/app/dashboard/` (55+ pages) + kernel overview (`GET :7778/api/system/overview`, healthy v1.0.84). Owner lane: HyperNexus dashboard lane. The elevated `:7779` rebuild remains Robert-gated; this analysis + non-elevated fixes are the deliverable until he rules.

## Finding: fragmentation is the main UX defect

55 top-level pages for one operator console. Related concepts are split across near-duplicate pages (memory ×4, sessions ×3, metrics ×3), so high-value actions are buried. Consolidate to **7 value-ordered sections**, each one page with in-page tabs/panels instead of subpages:

| Order | Section (one page) | Absorbs current pages | Why first |
|---|---|---|---|
| 1 | **Ops** (default landing) | health, pulse, observability, metrics, logs-metrics, events | "Is it alive, what's it doing, what's broken" is the daily-driver question |
| 2 | **Sessions** | session, sessions, squads, swarm, council, director, mesh | Coordination is the product's core act |
| 3 | **Memory** | memory, memory-search, memory-analytics, brain, knowledge, library, cold-archive, chronicle | One search box, one graph, archive as a tab |
| 4 | **Tools** | mcp, tool-console, tool-karma, cli-harnesses, skills, prompts, workflows | Progressive disclosure: 3–5 tools per step, rest searchable |
| 5 | **Code** | code, submodules, tests, inspector, architecture | RepoGraph + sweep results in one place |
| 6 | **Business** | commercial, billing, plans, marketplace, outreach, operator-apis, api-keys, account | Money surfaces grouped, off the operator's daily path |
| 7 | **System** | settings, security, audit, runtime, healer, evolution, integrations, imports, browser, browser-extension, claude-chrome, cloud-dev, cloud-orchestrator, context, research, reader, deerflow, workshop, manual (→ Help) | Rarely touched; keep out of the way |

Rules: every current route redirects to its section anchor (no broken links); every control gets a descriptive label + tooltip where the action is irreversible or jargon-heavy (tenant delete, key rotation, session kill); no feature is dropped — consolidation is regrouping, not removal.

## System tray (exists — verify + extend)

`HyperNexus/go/internal/systray/` (Windows): popup menu already shows version header, status line, and last-10 log lines. Verify and, if missing, add in this order: **Open Dashboard**, **Restart Kernel**, **Quit Servers** (real quit of kernel + sidecar, not just hiding the icon). Heavyweight actions from the tray run below-normal priority.

## Logs/build watch (leader spot-check, 2026-11-26)

- Kernel `:7778` healthy: sidecar ok, bus routes fast (p95 ≤ 10ms), memory store 8,483 entries, zero route errors in the sampled window.
- Build gate (workspace `build.bat`): 4 OK / 0 failed / 1 skipped at v5.348.0.
- Known not-running items: `:7779` elevated dashboard (Robert's rebuild call), marketing_agent production (deliberately stopped since Nov 22; restart is Robert's, wakes draft-only), Codex Desktop local rollout (needs MODEL_API_KEY in its GUI env).

## Acceptance for the owner lane

1. Section map implemented with redirects; old URLs keep working.
2. Dashboard sweep passes (lane reported 155/155 on the current layout — re-run after regrouping).
3. Tray: Open/Restart/Quit verified live with log evidence.
4. Report DONE/BLOCKED on the bus with commit hashes; before/after page-count in the report (55+ → 7).
