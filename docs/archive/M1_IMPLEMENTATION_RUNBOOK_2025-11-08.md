# Milestone 1 Implementation Runbook (2025-11-08)

This runbook translates the consensus roadmap into concrete, operational steps with acceptance criteria, roll-forward/backward procedures, and observability hooks. It is intentionally pragmatic and scoped to 4 weeks.

## Scope (M1)
- E1 Onboarding + Profile v1
- E2 Matching Feed v1 (rule-based)
- E3 Messaging MVP (WebSocket)
- E4 Moderation v2 (vendor + reviewer console)
- E5 Event Schema + Analytics Foundations
- E6 Anti-Abuse Base (throttles, flags)

## Operating Principles
- Feature flags for every shipped surface
- Progressive delivery: dark launch → internal → 5% → 25% → 100%
- Telemetry is part of Done (dashboard or it didn’t happen)

## Environment Checklist
- [ ] Secrets set for moderation vendor(s)
- [ ] WebSocket infra reachable from edge (reverse proxy updated)
- [ ] Centralized logging sink (app + worker + WS server)
- [ ] Metrics store available (dashboards provisioned)
- [ ] Alerting channels configured (on-call rota)

## E5 First: Event Schema & Flags (Week 1)
- Deliverables
  - [ ] Event schema v0: user.signup, user.profile.completed, feed.viewed, message.sent, message.received, moderation.flagged, moderation.actioned
  - [ ] Server and worker emitters with validation tests
  - [ ] Feature flag service (in-memory adapter + file-backed dev adapter)
  - [ ] Daily data integrity check job + report
- Acceptance Criteria
  - [ ] Dashboard: signup → profile completion funnel
  - [ ] CI checks block on event contract tests
- Rollback
  - Disable emitters via env flag; keep schema files for forward-only changes

## E1: Onboarding + Profile v1
- Deliverables
  - [ ] Minimal profile model (age range, location region, key interests)
  - [ ] Guided onboarding stepper with save-as-you-go
  - [ ] Privacy: explicit consent capture for data use
- Acceptance Criteria
  - [ ] >=80% profile completion in test cohort
  - [ ] Validations enforced server-side
- Rollback
  - Feature flag OFF → fall back to legacy profile view (if any); otherwise gate behind invite-only

## E2: Matching Feed v1 (Rule-based)
- Deliverables
  - [ ] Candidate generator (simple filters: distance, age, preferences)
  - [ ] Ranking heuristics (freshness, mutual interests)
  - [ ] API endpoints + pagination; basic UI list with actions
- Acceptance Criteria
  - [ ] CTR ≥ 5% on first 20 suggestions
  - [ ] p95 < 400ms for feed endpoint
- Rollback
  - Gate endpoint behind flag; return empty feed placeholder when OFF

## E3: Messaging MVP (WebSocket)
- Deliverables
  - [ ] Authenticated WS connection (token w/ TTL)
  - [ ] Message send/receive with delivery receipts
  - [ ] Safety filters pre-send (block lists, basic content checks)
- Acceptance Criteria
  - [ ] 95% delivery < 2s (p95)
  - [ ] 0 known message loss in soak test (6h)
- Rollback
  - Disable WS entrypoint; fall back to polling (if available)

## E4: Moderation v2
- Deliverables
  - [ ] Vendor integration (text/image), graceful degradation
  - [ ] Reviewer console (queue, actions, audit log)
  - [ ] Auto-actions for severe violations
- Acceptance Criteria
  - [ ] <1% severe violation escape rate in sampled review
  - [ ] Mean time to action < 10 minutes (business hours)
- Rollback
  - Switch to conservative rules-only mode; queue items for later review

## E6: Anti-Abuse Base
- Deliverables
  - [ ] Rate limits (per route/user), IP/device fingerprinting (lightweight)
  - [ ] Manual user actions: mute/block/suspend with audit trail
  - [ ] Suspicious pattern detectors (burst send, link spam)
- Acceptance Criteria
  - [ ] 0 critical spam floods escaping throttle during pilot
  - [ ] Alerts when risk score exceeds threshold
- Rollback
  - Disable aggressive detectors; keep manual controls

## Observability
- Dashboards
  - [ ] Funnel: signup → profile → first message
  - [ ] Messaging latency (send→receive p50/p95)
  - [ ] Moderation volumes & outcomes
  - [ ] Abuse signals (throttle hits, blocks)
- Alerts
  - [ ] WS error rate > 2% (5 min)
  - [ ] Moderation backlog > N
  - [ ] Feed latency p95 > 800ms

## Delivery Cadence
- Weekly checkpoints (Fri): scope health, metrics review, next-week goals
- Daily standup: blockers, risks, plan to green
- WIP limit: max 3 concurrent epics; use feature flags to pause safely

## Readiness Gates
- [ ] Staging soak test ≥ 6 hours with synthetic load
- [ ] Disaster rollback drill executed once per week
- [ ] Security review for new endpoints/queues

## Appendix
- Source roadmap: `AI_FEATURES_CONSENSUS_PLAN_2025-11-08.md`
- Prior stabilization details: `CONTENT_GENERATION_SERVICE_STABILIZATION_2025-11-08.md`
- Session state: `SESSION_SUMMARY_2025-11-08.md`
