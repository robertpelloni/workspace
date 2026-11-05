# United Beats Technology - Umbrella Analysis v4 (Addendum)**Date:** 2026-11-04
**Supersedes:** UNITED_BEATS_UMBRELLA_v3.md (2026-11-03) - v3 rankings stand; this addendum scores only the 16 repos added in Protocol #275 (117 -> 133 scope)
**Method:** Same Potential (Market 25% + 3yr Upside 25%) vs Execution (Existing 25% + Likelihood 25%) lens as v3. See v3 for the top-12 ranked table.

## New-repo scores
| Repo | Mkt | Pot | -> Potential | Exist | Like | -> Execution | Combined | Verdict |
|---|---|---|---|---|---|---|---|---|
| CodeWhale-Extensions | 7 | 8 | 7.5 | 6 | 6 | 6.0 | 6.75 | BET - best of the 16, real Rust codebase |
| unitedbeats_site | 4 | 5 | 4.5 | 7 | 8 | 7.5 | 6.00 | BRAND INFRA - live, AdSense, keep |
| bobble (OmniCore spec) | 9 | 8 | 8.5 | 1 | 4 | 2.5 | 5.50 | SPEC BET - huge TAM, zero code |
| newz (spec) | 7 | 7 | 7.0 | 1 | 4 | 2.5 | 4.75 | SPEC - crowded TAM, no code |
| autositcom (spec) | 6 | 7 | 6.5 | 1 | 3 | 2.0 | 4.25 | SPEC - ties to sitcom IP hold |
| webapp_factory (spec) | 6 | 6 | 6.0 | 1 | 3 | 2.0 | 4.00 | SPEC - factory dream, no code |
| DataStreamBrowser | 2 | 3 | 2.5 | 5 | 6 | 5.5 | 4.00 | ARCHIVE - micro-utility, works |
| ADSFileSystem | 2 | 3 | 2.5 | 5 | 6 | 5.5 | 4.00 | ARCHIVE - micro-utility, works |
| Folderum3-The-Last-Attempt | 2 | 4 | 3.0 | 4 | 5 | 4.5 | 3.75 | ARCHIVE - joke forum, curiosity value |
| mparty (scaffolding) | 3 | 5 | 4.0 | 3 | 4 | 3.5 | 3.75 | ARCHIVE - 3 scripts, no ROM output |
| explorerexedecompiled | 3 | 4 | 3.5 | 2 | 3 | 2.5 | 3.00 | ARCHIVE - blocked, no output files |
| educational_video_pipeline (spec) | 5 | 6 | 5.5 | 1 | 3 | 2.0 | 3.75 | SPEC - transcript only |
| sales_bot (spec) | 5 | 6 | 5.5 | 1 | 3 | 2.0 | 3.75 | SPEC - design doc only |
| succubus.red (spec) | 4 | 5 | 4.5 | 1 | 2 | 1.5 | 3.00 | ARCHIVE - companion-chat transcript |
| make_elon_laugh (spec) | 2 | 3 | 2.5 | 1 | 2 | 1.5 | 2.00 | ARCHIVE - joke bot, never run |
| borg (placeholder) | - | - | - | - | - | - | - | STRUCTURAL - empty; code lives in workspace/hyperharness/HyperNexus |

## What changes in v3

- Nothing in the top-12 order changes. Highest new combined score (CodeWhale-Extensions 6.75) ties bobtrader/bobcoin (6.75), below aimoneymachine (7.00): a Bet, not a Star.
- bobble has the highest Potential (8.5) of any new repo but Execution 2.5 keeps it a spec-bet: revisit only after HyperNexus API ships (same gate as skillzhub).
- autositcom folds into the existing sitcom-IP hold (v3 rank 12) as its production mechanism, not a separate line.
- Remainder go to Archive / maintain-only. Do not staff, do not merge except trivially.

## Capital allocation

Unchanged from v3 ($1.9M/12mo, 60/25/10/5/0). Zero new staffing for any of the 16. CodeWhale-Extensions gets alignment review only: it overlaps HyperNexus agent-runtime and borg orchestration - decide merge-or-align before any spend.

## Risks added

- Spec-repo count keeps growing (9 of 16 are docs-only). Every Jules/autopilot run that writes transcripts-as-README creates a repo that looks like progress but scores Execution 1-2. Gate future repo creation on runnable code.
- Stale submodule pins break every Jules recursive clone. Fixed this round: bobmani (8 pins), f-zerox/bobcoin. Still open: linthesia/pianogame, ksm-v2/CoTaskLib (+siblings), TormentNexus/borg (different owner). Rule: never commit a gitlink the remote does not advertise - verify with ls-remote first.
- borg placeholder vs real borg code in three places (workspace, hyperharness, HyperNexus apps/borg-extension): pick the canonical home in the HyperNexus API milestone or the confusion compounds.
