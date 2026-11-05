# United Beats Technology — Umbrella Analysis v5 (Addendum)
**Date:** 2026-11-05
**By:** muse-wonder-1.0 in muse on BOBPC in ~/workspace
**Supersedes:** UNITED_BEATS_UMBRELLA_v4.md (2026-11-04) — v3 top-12 rankings stand except re-scores below
**Scope:** 133 submodules as one umbrella org under United Beats Technology. 132/133 initialized (hypercode = stale .gitmodules entry, no gitlink)
**Trigger:** Protocol #277 (v5.287.0) — 91 forward merges pushed across ~45 repos, 35+ defaults sync-merged with origin

## What Protocol #277 changed for scoring

Several v4 verdicts were scored when repos held only specs/transcripts. Merged Jules/feature work now gives them real code, raising Execution (Existing + Likelihood):

| Repo | v4 Combined | Change in #277 | Re-score (Exist/Like -> Exec) | New Combined | Verdict |
|---|---|---|---|---|---|
| educational_video_pipeline | 3.75 SPEC | +67-commit automated-video-pipeline + dashboard merged | 1/3 -> 4/5 = 4.5 | ~5.0 | BET (small) — real pipeline, unproven output |
| mparty | 3.75 ARCHIVE | +58-commit ai-pipeline + 30-commit jules merged | 3/4 -> 5/5 = 5.0 | ~4.5 | WATCH — code exists, ROM/output still unproven |
| webapp_factory | 4.00 SPEC | +41-commit autonomous-utility-factory + dashboard merged | 1/3 -> 4/4 = 4.0 | ~5.0 | BET (small) — factory thesis now testable |
| sales_bot | 3.75 SPEC | 2 jules branches merged; sirens (+40) still conflicted/retained | 1/3 -> 3/4 = 3.5 | ~4.5 | WATCH — partial; finish sirens merge first |
| succubus.red | 3.00 ARCHIVE | 4 branches merged (viewport/mic, vision/tray, VRM fixes) | 1/2 -> 4/4 = 4.0 | ~4.25 | WATCH — companion product now runnable |
| make_elon_laugh | 2.00 ARCHIVE | +46-commit emperor-musk-bot merged | 1/2 -> 3/3 = 3.0 | ~2.75 | ARCHIVE — code does not fix joke-bot TAM |
| bobble | 5.50 SPEC BET | dependabot + jules-1130 (+10) merged | 1/4 -> 3/4 = 3.5 | ~6.0 | SPEC BET (stronger) — still gated on HyperNexus API |
| newz | 4.75 SPEC | omnifeed scaffolding + unified-dashboard merged | 1/4 -> 3/4 = 3.5 | ~5.25 | SPEC BET — crowded TAM unchanged |

## Stars / Bets / Cash Cows — unchanged, with notes

- **Stars:** fwber (8.75 — #277 merged 2 Jules dashboard branches after +81 origin sync; still closest to launch), HyperNexus (8.25 — cloud-dashboard orphan branch remains deferred by rule; no main merges without Robert), realestatecrm (+198 sync), marketing_agent, hymnmania (nested bobmani/hymnmania +86 sync conflicted — open item, not a score change)
- **Bets:** skillzhub (gated on HyperNexus API), gods-eye-view ($20k course; highest per-unit revenue), bobmani-unified (itgmania +2 branches merged in #277; beatoraja pointer ambiguity open), freellm API (temp-main +2/-253 conflicted both strategies — merge cost rising, decide cherry-pick vs abandon), CodeWhale-Extensions (6.75 — merge-or-align vs HyperNexus still undecided; #277 left upstream branches untouched per rule)
- **Cash Cows:** aimoneymachine_site, bobtrader/bobcoin, bobfilez/bobeditpro — maintain. pi-mono/jules-autopilot remain internal infra (pi-mono build regression from #277 phase-20 merge was caught by build.bat, fixed, tested, pushed `003713106`)

## Deferred with real work at risk (all branches retained, nothing deleted)

1. sales_bot `jules-project-sirens` (+40) — finish before any sales_bot spend
2. bobmani/itgmania `jules-12512815185672744343` (+30) and veilid `jules-scaffold-0.1.0` Gold Master (+17/-84)
3. freellm `temp-main`, slsk `jules-57044827041196387` — small but aging; cherry-pick window narrows each protocol
4. _fix repos (bg_fix, bobfilez_fix, bobsgameonlinejava_fix) push-rejected — local syncs retained; needs explicit force-with-lease decision from Robert
5. openclaw-config / openclaw-dashboard — foreign remotes (TechNickAI / tugcantopaloglu), push denied; treat as read-only mirrors

## Capital allocation

Unchanged: $1.9M/12mo at 60/25/10/5/0 (v3). No new staffing from re-scores — every uplift is Execution +1 to +2 on small bases; none crosses into Star territory. The v4 spec-repo warning still applies, with one amendment: in #277 the specs largely *became* code via Jules branches, which validates the pipeline but shifts the risk from "no code" to "unreviewed code" — merged via feature-wins conflict resolution, build-verified only where build.bat reaches (4 OK / 0 fail / 1 skip).

## Corrections folded in (Bobbi, muse.ai, 2026-11-05)

Bobbi reviewed this as a lane report — not a Robert decision, not Muse-verified — and declined to endorse re-scores (no verified market data in her record; commit counts are not market validation). Corrections accepted:

1. **Count universe:** 133 is explained, not continuous with older counts. .gitmodules declared 117 through Protocol #274; Protocol #275 (2026-11-03) registered 16 genuinely-missing robertpelloni repos → 133. 132 initialized in #277.
2. **Pricing separation:** $1.99 trial / $5 seat / $200 founding are HyperNexus terms only. fwber premium is tentative (~$5/mo, still to discuss) — never apply HyperNexus pricing to fwber.
3. **Org shape:** United Beats is umbrella AND standalone businesses (Robert, Oct 26). This doc scores the umbrella view; standalone P&Ls remain separate.
4. **Build scope:** "4 OK / 0 fail / 1 skip" = hyperharness.exe, pi-mono.exe, tabby-backend.exe, tabby-native.exe built; tormentnexus skipped (submodule not initialized).
5. **Ranking tension:** Robert's Oct 29 direction was showcase ALL major projects, archive NOTHING. Rankings here are capital-sequencing only — Archive verdict means "no new staffing," never deletion or shelving of the showcase.
6. **Hard limits confirmed standing:** no merges to main without Robert's direct word in main chat; no prospect contact without approved list + copy + live proof + billing verification + separate send go; no spending in Robert's name. Launch order (fwber vs gods-eye-view) and disposition of the 5 retained branches are Robert's decisions, not agent decisions.

## Gemini second opinion (2026-11-05, signed-out 3.5 Flash-Lite)

Gemini disagreed with the uplifts: build-level verification after feature-wins merges proves compilation, not functional viability or market fitness. It would hold educational_video_pipeline at 3.75 until runtime/user proof, and would not move capital from Stars (fwber, HyperNexus) into these Bets. **Disposition:** all 8 re-scores in this addendum are therefore marked PROVISIONAL — Execution uplift capped at +1 (not +2) pending a runnable-output check (demo, tests beyond build, or live URL) per repo. First repo to produce runtime proof gets its full re-score restored in v6.

## Coordination asks

- **Bobbi (muse.ai):** validate re-scores; confirm HyperNexus hard limits still stand; fwber vs gods-eye-view launch order; disposition of 5 retained conflict branches
- **Gemini:** independent re-score of the 8 uplifted repos; challenge the "specs became code" amendment; flag any Star/Bet you would demote

*Prepared for United Beats Technology strategic planning. Final decisions: Robert Pelloni.*
