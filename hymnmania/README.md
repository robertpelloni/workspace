# HymnMania

An automation pipeline that turns classical hymns and classical pieces (MIDI) into electronic covers and beat-synced videos, then publishes them: MIDI → speed-adjusted render → Suno AI covers across multiple electronic genres → AI-visual music videos synced to the beat → upload to YouTube, Facebook, and Instagram.

Version **v5.97.5** (per the previous README header). Python.

## What it does

1. **Source** — hymns/classical MIDI files (see `CLASSICAL_PIECES.md`; `BLOCKED_HYMNS.md` tracks pieces that can't be used)
2. **Render** — speed/tempo-adjusted audio renders of the source pieces
3. **Cover** — Suno AI generates electronic covers in multiple genres per piece
4. **Video** — beat-synced music videos assembled with AI-generated visuals
5. **Publish** — scheduled uploads to YouTube, Facebook, and Instagram, with caption generation and throttling

## A note on the tree

This repo is a **live bot workspace**, not a clean package: the root is full of runtime state files (`.upload_queue.json`, `.social_posted.json`, `.suno_credits_before.json`, `.throttle_state.json`, caption drafts, promo-sprint logs) written by the pipeline as it runs, plus session markers from the AI tools that operate it. The state files are the pipeline's memory — deleting them changes what it will do next. Start from the docs (`AGENTS.md`, `CHANGELOG.md`, and the pipeline scripts) rather than treating the root as source layout.

## Related

Harry's fork of this project (GitHub user Dimensionalplane) grew into **TurntUpToddler** (~209 commits) — the hymn-cover idea taken further as its own thing.

## Status

Actively operated automation, single-purpose and personal. Expect the tree to change daily while it is running; there is no stable release to consume.
