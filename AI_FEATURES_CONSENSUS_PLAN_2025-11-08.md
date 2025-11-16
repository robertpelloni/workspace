# AI Feature Roadmap Consensus (2025-11-08)

This document synthesizes a multi-model consensus (OpenAI GPT‑5 Pro, Google Gemini 2.5 Pro, X.AI Grok‑4) on the next 12 months of features for our social/dating platform. It produces a single prioritized backlog, milestone plan with metrics, cross-cutting priorities, an AI-specific roadmap, and concrete next steps that reflect a realistic Laravel + JS team.

## Summary of Consensus
- Strong agreement: prioritize the core loop (onboarding → matching → messaging) and safety before advanced AI and monetization.
- Avoid overloading Milestone 1; phase monetization and heavier AI later.
- Build analytics and experimentation early to iterate with data.
- Trust & Safety must be proactive, multimodal, and include human-in-the-loop.
- Use feature flags/kill‑switches and vendor fallbacks to control risk.

---

## Single Prioritized Backlog (P0 / P1 / P2)

### P0 — Must‑Have (Viability & Trust)
1) Core Matching & Discovery v1 (ranked feed + likes/matches)
- Start with rule‑based ranking and filters; prepare hooks for embeddings later.
- Impact: High. Effort: Medium. Risks: cold start. Deps: Profile data, filters.

2) Onboarding & Profile Completion
- AI prompts for bios; photo guidance; minimal friction FTUE.
- Impact: High. Effort: Medium. Risks: over‑templated copy. Deps: current gen service.

3) Real‑time Messaging MVP (+ basic presence)
- WebSockets (Pusher or Laravel WebSockets); spam/NSFW pre‑send checks; block/report enforced.
- Impact: High. Effort: Medium. Risks: abuse vectors. Deps: safety, rate limits.

4) Moderation Pipeline v2 (text + image) with human review
- Vendors (e.g., Hive/Rekognition/Google) + reviewer console; pre‑send nudges; post‑hoc triage.
- Impact: High. Effort: Med‑High. Risks: FP/FN, cost. Deps: vendor APIs, ops workflow.

5) Notifications (push/email) for matches/messages
- Impact: High. Effort: Low‑Med. Risks: deliverability, noise. Deps: FCM/APNS/Web Push, mail.

6) Analytics & Experimentation Foundations
- Event schema, funnels, dashboards; feature flags and A/B tests.
- Impact: High. Effort: Medium. Risks: analytics debt. Deps: GA4/Amplitude + flags.

7) Anti‑Abuse Hardening
- Rate limits/quotas; device fingerprinting (privacy‑aware); OTP/email/phone verification gates; ban‑evasion controls.
- Impact: High. Effort: Medium. Risks: friction, privacy. Deps: verification vendors optional.

8) Feature Flags, Kill‑Switches, Vendor Fallbacks
- Toggle providers, disable risky features instantly; graceful degrade to baseline.
- Impact: High. Effort: Low. Risks: config drift. Deps: flag service or config.

Note on payments: Basic subscriptions were proposed as P0 by one model; to prevent M1 overload, we schedule this in P1.

### P1 — Growth & Monetization (High Impact)
1) Subscriptions + Payments (Stripe) + Entitlements
- “Plus” tier; experiments: boosts, superlikes, rewinds; fair caps.
- Impact: High. Effort: Medium. Risks: pay‑to‑win perception. Deps: Stripe, entitlement store.

2) Recommendations v2 (Embeddings + Bandits)
- Move from rules to embeddings (pgvector) with fairness constraints; explore/exploit with risk caps.
- Impact: High. Effort: Medium. Risks: bias. Deps: vector db/jobs.

3) Verification & Trust (selfie liveness + phone/email)
- Badges, higher ranking for verified; careful UX to reduce drop‑off.
- Impact: High. Effort: Medium. Risks: friction. Deps: Persona/Onfido.

4) Voice Notes & Short Video Intros
- Authenticity boost; requires audio/video moderation; storage/CDN.
- Impact: Med‑High. Effort: Medium. Risks: moderation load/cost.

5) Community Boards/Events Expansion
- Events with RSVP; board quality controls with AI moderation.
- Impact: Medium. Effort: Medium. Risks: spam/liability.

6) Growth Loops
- Referrals/invites; waitlist unlocks. Anti‑fraud protections.
- Impact: Med‑High. Effort: Low‑Med. Risks: farming.

### P2 — Differentiation & Scale (Later)
1) Video Chat with Safety
- Timeboxed calls, blur, report; real‑time moderation signals.
- Effort: High. Risks: live abuse. Deps: WebRTC.

2) Internationalization + Multilingual AI
- Localized gen/moderation; cultural/quality sensitivity.
- Effort: Med‑High. Risks: model quality variance.

3) Advanced Safety
- Behavioral risk scoring; device fingerprinting expansion; honeytokens.
- Effort: Medium. Risks: privacy.

4) Data Products & Insights (Opt‑in)
- Weekly recap, match insights, date ideas.
- Effort: Low‑Med. Risks: creepiness; must be opt‑in.

5) Platform SDK / Public API (selective)
- For partners/creators; TBD post‑PMF.

---

## Milestones & Success Metrics

### M1 (Months 0–4): MVP Engagement + Trust (Ship P0)
- Metrics: Activation (profile ≥80% completion) ≥45%; TTFM ≤72h; D1 ≥30%, D7 ≥15%; match→conversation ≥40%; 95% of reports triaged <12h; p95 message send <200ms; incident rate <2/1k DAU.

### M2 (Months 5–8): Growth + Monetization (Ship P1)
- Metrics: MAU +50% vs M1; D7 ≥20%; subscription conversion ≥3–5%; ARPPU ≥$18; verification adoption ≥40% new users; moderation P/R >0.85/0.8.

### M3 (Months 9–12): Scale + Differentiation (Begin P2)
- Metrics: DAU/MAU ≥0.22; churn −20% vs M2; incidents/1k DAU −30%; intl retention ≥90% of primary cohort; API uptime 99.9%.

---

## Cross‑Cutting Priorities (NFR)
- Privacy: Minimization; PII encryption at rest/in transit; consent for AI; retention controls; DSR tooling; opt‑out of training; transparent policies.
- Reliability/Perf: SLOs (99.9% API, p95 <300ms); queues and backpressure; circuit breakers/timeouts; autoscaling; idempotent payments.
- Security/Trust: RBAC + audited admin; secret management; 2FA for staff; anti‑scraping; fraud detection; age gate; pentest pre‑GA.
- Accessibility: WCAG 2.2 AA; captions, keyboard nav, contrast; localization‑ready UI.

---

## AI‑Specific Roadmap
- Generation: Expand prompts; tone checks; template humanization; continue baseline fallback to avoid sameness.
- Moderation: Multimodal (text/image/audio/video); pre‑send nudges; post‑hoc triage; appeals; threshold tuning; vendor fallback rotation; cost caps.
- Personalization: Onboarding vectors; embeddings + bandits with fairness constraints; diversity in top‑N; cold‑start strategies.
- Analytics/Ops: Labeled eval sets; offline harness; AB platform with kill‑switch; drift and FP/FN monitoring; annotation program; privacy‑preserving logs.

---

## Dependencies & Infrastructure
- WebSockets: Pusher or Laravel WebSockets.
- Queues/Cache: Redis (Horizon recommended).
- Vector Store: Postgres + pgvector (M2).
- Moderation Vendors: Text + image in M1; audio/video added M1→M2.
- Notifications: FCM/APNS + Web Push.
- Device Fingerprinting: Privacy‑aware (e.g., light‑touch FPJS or server heuristics). 
- Payments: Stripe billing + entitlement store (M2).

---

## Risks & Mitigations
- Moderation cost/latency: Add provider budgets, caching, batch APIs; short‑circuit low‑risk.
- Bias/fairness in recommendations: Diverse top‑N, constraints, audits; user controls.
- Abuse/fraud: Strong rate limits, OTP/phone/email verification, device heuristics, honeytokens.
- Privacy and compliance: DSR processing, consent management, retention policies.
- Over‑scope M1: Keep payments and embeddings to M2; enforce feature flags and gates.

---

## Implementation Plan (High‑Level Epics)
- E1: Onboarding & Profile Completion (forms, AI prompts, media upload, validation)
- E2: Matching & Discovery v1 (feed, filters, likes/matches; backend APIs; simple ranker)
- E3: Messaging MVP (WS infra; send/receive; pre‑send checks; blocked UX)
- E4: Moderation v2 (vendors integration; reviewer console; pre‑send nudges)
- E5: Notifications (push/email; delivery configs; user preferences)
- E6: Analytics & Experimentation (events schema; dashboards; flags; A/B)
- E7: Anti‑Abuse & Feature Flags (rate limits; device signals; kill‑switch)
- E8: Monetization (M2) (Stripe; entitlements; premium features)
- E9: Recommendations v2 (M2) (embeddings; ranker; fairness constraints)
- E10: Verification (M2) (selfie/phone/email; badging; ranking uplift)

---

## Immediate Next Steps (Weeks 1–4)
1) Define events schema + set up flags/experimentation.
2) Build Matching v1 (rule‑based) + feed UI and APIs.
3) Stand up Messaging MVP with spam/NSFW pre‑send check and report/block enforcement.
4) Integrate text/image moderation vendor + simple reviewer console.
5) Implement push/email notifications for matches/messages.
6) Add anti‑abuse: request quotas, device heuristic, OTP/email verify wall.
7) Draft privacy policy and in‑product disclosures for AI usage.

---

Prepared via multi‑model consensus (GPT‑5 Pro, Gemini 2.5 Pro, Grok‑4) and tailored to the current Laravel stack and AI pipeline state.
