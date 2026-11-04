# United Beats Technology — Umbrella Analysis v3
**Date:** 2026-11-03
**By:** muse-spark-1.3-contributor in Codex
**Supersedes:** UNITED_BEATS_RATING_v2.md (2026-11-01), UNITED_BEATS_STRATEGY.md (2026-10-25)
**Scope:** 117 submodules as one umbrella org

## Method — Potential vs Execution

Requested prioritization: potential market + value versus existing value + likelihood.

- **Potential Score (50%) = Market Size (25%) + 3yr Upside / Potential (25%)**
- **Execution Score (50%) = Existing Value (25%) + Likelihood to Ship (25%)**
- Profitability and Completeness from v2 folded in as tie-breakers, not primary rank drivers.

Reuses v2 0-10 scores where available, reassessed for 117-project scope.

## Quadrant Map

```
High Potential ^
  9 |  HyperNexus   skillzhub
  8 |  fwber  marketing_agent  bobmani  gods-eye-view
  7 |  aimoneymachine  bobtrader/bobcoin  freellm
  6 |  hymnmania  realestatecrm  sitcom IP  veilid mcp?
  5 |  games-archive  creative-tools  infra-forks
      -------------------------------------------------> High Execution
       5    6    7    8    9
```

- **Stars (High Potential + High Execution):** fwber, HyperNexus, realestatecrm, marketing_agent, hymnmania
- **Bets (High Potential + Low Execution):** skillzhub, gods-eye-view, bobmani-unified, freellm API
- **Cash Cows (Low Potential + High Execution):** aimoneymachine_site, bobtrader/bobcoin hold, bobfilez/bobeditpro maintain
- **Archive (Low + Low):** 20+ games, creative tools, infra forks, one-offs

## Re-ranked Table (Potential vs Execution)

| Rank | Project | Mkt | Pot | -> Potential | Exist | Like | -> Execution | Combined | v2 Score | Move |
|---|---|---|---|---|---|---|---|---|---|---|
| 1 | fwber dating SaaS | 10 | 9 | 9.5 | 8 | 8 | 8.0 | 8.75 | 8.80 | hold |
| 2 | HyperNexus AI platform | 9 | 10 | 9.5 | 7 | 7 | 7.0 | 8.25 | 8.10 | hold |
| 3 | marketing_agent | 8 | 9 | 8.5 | 6 | 8 | 7.0 | 7.75 | 7.55 | up |
| 4 | skillzhub 5776 skills | 8 | 9 | 8.5 | 7 | 6 | 6.5 | 7.50 | 7.35 | up |
| 5 | realestatecrm SaaS | 8 | 7 | 7.5 | 8 | 8 | 8.0 | 7.75 | 7.55 | up* |
| 6 | hymnmania 11k hymns | 6 | 8 | 7.0 | 9 | 9 | 9.0 | 8.00 | 7.35 | up* |
| 7 | bobmani rhythm (focus beatoraja+itgmania) | 7 | 8 | 7.5 | 8 | 7 | 7.5 | 7.50 | 7.05 | up |
| 8 | gods-eye-view course | 5 | 7 | 6.0 | 7 | 6 | 6.5 | 6.25 | 7.15 | down |
| 9 | aimoneymachine_site funnel | 6 | 7 | 6.5 | 7 | 8 | 7.5 | 7.00 | 6.80 | hold |
| 10 | freellm cost layer | 8 | 7 | 7.5 | 5 | 6 | 5.5 | 6.50 | new | new |
| 11 | bobtrader / bobcoin | 9 | 6 | 7.5 | 7 | 5 | 6.0 | 6.75 | 6.55 | hold |
| 12 | bob_and_lum_sitcom IP | 6 | 8 | 7.0 | 8 | 7 | 7.5 | 7.25 | 6.45 | up |

*Execution-heavy winners rise when likelihood weighted equally with potential: hymnmania and realestatecrm outrank pure-potential bets.

## Why This Ordering

1. **fwber stays #1:** Only project with near-term recurring SaaS + huge TAM + shippable now (v2.3.39). Potential 9.5 and Execution 8.0 both top-tier.
2. **HyperNexus #2 on moat:** Highest Potential (9.5) with platform TAM $50B+, but Execution 7.0 caps it until token verify + API docs ship.
3. **marketing_agent jumps:** It is the launcher for #1/#2. Potential 8.5, Execution 7.0. Fund it as growth cost-center, not standalone P&L.
4. **skillzhub as bet:** Same Potential as marketing_agent but Execution 6.5. Do not staff until HyperNexus API live; then marketplace take-rate.
5. **hymnmania undervalued in v2:** Execution 9.0 is highest in org (11,470 hymns, daily_scheduler, 197 YouTube + 81 vertical). Low Mkt (6) hides brand-engine value. Keep on autopilot, zero staffing.
6. **gods-eye-view drops:** $400k/cohort is real but Mkt 5 + Like 6 + heavy lift = bet, not star. Defer cohort 2 until fwber live.
7. **bobmani narrowed:** 11 subprojects as one org is unshippable. As beatoraja + itgmania only, Execution 7.5 works. Rest to maintenance.
8. **freellm new entry:** Internal LLM cost optimization becomes external API only after HyperNexus. Potential 7.5 alone does not justify spin-out now.

## Umbrella Structure (One Org)

```
United Beats Technology (parent)
+-- Social / Consumer (fwber flagship, 60% focus)
+-- AI Platform (HyperNexus + skillzhub + freellm + mcp-superassistant, 25% focus)
+-- Music / Brand (hymnmania autopilot + bobmani focused + bobtrax, 10% focus)
+-- Services (realestatecrm + marketing_agent + aimoneymachine_site, 5% + growth engine)
+-- Education / High-ticket (gods-eye-view deferred)
+-- Hold (bobtrader/bobcoin cycle, dao, sitcom IP)
+-- Archive / Maintain-only (20+ games, creative tools, infra forks)
```

## Capital Allocation (12mo, $1.9M plan from v2 reaffirmed)

- 60% fwber beta + payments + onboarding (wk 1-4) -> 1k users / 90d
- 25% HyperNexus token verify + API + docs (wk 1-4) -> 100 devs / 6mo
- 10% marketing_agent campaigns for both (wk 5-12)
- 5% hymnmania autopilot (no staffing), sitcom IP held for audience
- 0% new staffing for skillzhub / gods-eye-view / games until Stars ship

## Archive List (Maintain-only, no merges unless trivial)

Games: MarbleBlast, OpenMBU, bobsgameonline/java/web, f-zerox, mk64, sm64coopdx, neverball, okgame, ai_game_engine, bobsaver, bobzilla, bobzzite, supersaber. Creative: ArrowVortex, geiss, apophysis-j, JWildfire, GWEN, bgtk, bqt, bcs, multimousergy. Infra forks: FFmpeg, topaz-ffmpeg, llvm-project, jdk, grammars-v4, libjruntime, jvm-cpp-runtime, bdwgc, element-web, geany, npp, warp, tokdiet, tabby. Content one-offs: foone_datetime_short, hyperporn PMV.

## Risks

- fwber auth/login 401 recurrence + payment integration still gating.
- HyperNexus muse-spark 403 attestation blocker in pi harness (today) — needs pay-as-you-go key or Muse Code client path.
- bobmani scope creep if all 11 subprojects staffed; lock to 2.
- Hetzner disk pressure seen Oct 26 (100% on us-east-ubuntu-2-8-80) — monitor /opt + binlogs.

*Needs Robert sign-off. Bobbi validation on market comps pending.*
