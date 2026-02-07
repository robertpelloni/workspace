# Changelog

All notable changes to the **Antigravity Autopilot (Unified)** extension will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [4.0.0] - 2026-02-07

### Added
- **Unified Architecture**: Merged `AUTO-ALL`, `auto-accept`, and `yoke` logic into a single codebase.
- **Configurable Strategies**: Choose between `Simple` (Command) and `CDP` (Browser) drivers.
- **Autonomous Loop**: Full integration of the Yoke agent loop with goal tracking.
- **Project Manager**: Jira/GitHub task sync and local `@fix_plan.md` support.
- **Advanced Configuration**: New settings for `threadWaitInterval`, `autoApproveDelay`, and `bumpMessage`.
- **"Expand <" Fix**: Browser script now intelligently expands collapsed UI sections.
- **Chat "Bump"**: Agent can keep threads alive by sending configured "bump" messages.

### Changed
- **Package Structure**: Moved to `antigravity-autopilot-unified`.
- **Documentation**: Comprehensive overhaul of `LLM_INSTRUCTIONS`, `VISION`, and `DASHBOARD`.

### Fixed
- **UI Blocking**: Resolved issue where agent would get stuck on "Step Requires Input - Expand <".
- **Lint Errors**: Fixed Typescript errors in `cdp-strategy.ts`.
