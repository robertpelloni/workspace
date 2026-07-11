# Project Architecture, Patterns, and Decisions

## 1. The Core Paradigm Shift
* **Legacy Archival:** The original C++ `PianoGame` repository (with OpenGL and MIDI dependencies) has been fully archived into the `legacy/` directory. This preserves its history while entirely clearing the root for a massive architectural pivot.
* **New Vision:** The repository is transforming into the "Ultimate Agentic Coding Harness," a universal AI pair programming environment designed to surpass and integrate over 40+ existing CLI/TUI/Web tools.

## 2. Multi-Language Parity Strategy
* **Five Target Stacks:** To achieve true universality and native environment integration, the harness is being built simultaneously across five completely different languages:
  * **Rust:** Configured with `Cargo` (`Cargo.toml`).
  * **Go:** Configured with Go Modules (`go.mod` using `go 1.20`).
  * **C#:** Configured as a `.NET 8.0` Console application (`Harness.csproj`).
  * **Java:** Configured via `Maven` (`pom.xml`).
  * **TypeScript:** Configured with Node.js (`package.json`, TypeScript 5, Node 20 types).
* **Parity Goal:** Every single feature (LLM routing, git integration, AST parsing, web scraping) must be ported 1-to-1 across all five architectures.

## 3. Submodule Ingestion Engine
* **The "Harness of Harnesses":** Rather than reinventing the wheel, the project's current phase involves cloning the source code of existing top-tier AI tools as Git submodules into the `submodules/` directory.
* **First Target (Aider):** The `aider` repository has been successfully ingested. An analysis (`AIDER_ANALYSIS.md`) revealed core features required for the port: AST mapping, native git commit generation, LiteLLM wrapper abstraction, and self-correcting lint/test loops.

## 4. Strict Documentation Governance
The root folder serves as the central brain for continuous autonomous execution, strictly maintaining the following documents:
* **`VISION.md` & `ROADMAP.md`:** Outlines the long-term milestones (e.g., Phase 1: Ingestion, Phase 2: Multi-Language Scaffolding).
* **`TODO.md`:** The granular, immediate checklist. The agent *must* update this as tasks are completed.
* **`VERSION.md` & `CHANGELOG.md`:** The global truth for the application's version (`1.0.0-agentic-alpha.1`). No hardcoded versions exist in the application logic.
* **`MEMORY.md` & `HANDOFF.md`:** Used for LLM-to-LLM session handoffs to ensure unstoppable autonomy without context degradation.

## 5. Execution Directives
* **Autopilot Rule:** Execution must be continuous. The system commits and pushes to Git after every major feature without pausing for user confirmation.
* **Commit Standards:** Every commit message must explicitly reference the exact version string from `VERSION.md`.
* **Build Hygiene:** `.gitignore` has been thoroughly configured to prevent the massive influx of build artifacts (`target/`, `node_modules/`, `bin/`, `obj/`) from polluting the repository.

## 6. Next Immediate Steps (From `TODO.md`)
* The foundational scaffolding and the first submodule ingestion are complete.
* The next step is to ingest the second target repository (e.g., Claude Code, Opencode, or similar) as a submodule, analyze its unique features, and document them to continue building the ultimate feature-parity master list.