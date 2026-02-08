# Library & Dependency Reference
> Last Updated: 2026-02-08

## Table of Contents (by category)
- 1. Root Workspace Dependencies
- 2. AIOS Stack
- 3. FWBer Stack
- 4. Rhythm Game Stack
- 5. Bob's Game (bg)
- 6. N64 Decompilation
- 7. Desktop Tools
- 8. Crypto (bobcoin)
- 9. AI Agents & Orchestration
- 10. MCP Servers
- 11. CI/CD & Testing
- 12. Version Control & Repository Management

## 1. Root Workspace Dependencies

### Node.js (from package.json)
- `firecrawl-mcp` ^3.6.2
  - Purpose: Web scraping MCP server used across AIOS agents that need structured research input.
  - Reason selected: Enables OpenCode/AIOS workflows to crawl and extract web content safely from within the MCP ecosystem.
  - Used in: Root workspace automation pipelines and AIOS agent orchestration.
  - Official docs: https://www.npmjs.com/package/firecrawl-mcp
  - Config: Declared in the root `package.json` under `dependencies` and resolved through `pnpm`.
- `mem0ai` ^2.1.38
  - Purpose: Persistent AI memory layer shared by multi-agent sessions.
  - Reason selected: Keeps agent conversations and context synchronized across sessions to preserve continuity.
  - Used in: AIOS memory services, agent adapters, and any tooling requiring recall.
  - Official docs: https://www.npmjs.com/package/mem0ai
  - Config: Root `package.json` dependency with pnpm lockfile constraints.
- `opencode-ai` ^1.1.18
  - Purpose: Provides automated code generation, linting, and analysis primitives to OpenCode agents.
  - Reason selected: Standardizes how coding agents produce and evaluate code, reducing boilerplate.
  - Used in: AIOS coding workflows, CLI helpers, and multi-agent pipelines that generate source files.
  - Official docs: https://www.npmjs.com/package/opencode-ai
  - Config: Root dependency with `firecrawl-mcp` and `task-master-ai` in shared workspaces.
- `task-master-ai` ^0.35.0
  - Purpose: Autonomous task planning, breakdown, and execution tracking within AIOS.
  - Reason selected: Coordinates multi-agent agendas, ensuring tasks remain visible and prioritized.
  - Used in: Workspace orchestration dashboards and AIOS scheduling logic.
  - Official docs: https://www.npmjs.com/package/task-master-ai
  - Config: Root `package.json` dependency.

### Node.js Dev Dependencies
- `@playwright/test` ^1.56.1
  - Purpose: End-to-end browser testing spanning Chromium, Firefox, and WebKit.
  - Reason selected: Guarantees consistent UI behavior for Next.js-based dashboards and fwber frontends.
  - Used in: CI/CD Playwright suites called by GitHub actions.
  - Official docs: https://playwright.dev/
  - Config: Defined under `devDependencies` with dedicated test scripts.
- `@types/node` ^24.10.0
  - Purpose: TypeScript definitions for Node.js APIs.
  - Reason selected: Ensures typesafe builds for the pnpm workspace.
  - Used in: All TypeScript tooling in AIOS, fwber, and other packages.
  - Official docs: https://www.npmjs.com/package/@types/node
  - Config: Declared in `devDependencies` for shared tooling packages.
- `sinon` ^21.0.1
  - Purpose: Stubs, mocks, and spies for isolated unit tests.
  - Reason selected: Keeps tests deterministic without relying on real services.
  - Used in: Node.js unit/integration suites across AIOS services.
  - Official docs: https://sinonjs.org/
  - Config: Development dependency consumed by Jest, Vitest, or mocha suites.
- `supertest` ^7.2.2
  - Purpose: HTTP assertion library for server endpoints.
  - Reason selected: Allows API tests without launching full HTTP servers.
  - Used in: Backend Fastify tests inside AIOS packages.
  - Official docs: https://www.npmjs.com/package/supertest
  - Config: Declared under `devDependencies`.

### Python (from pyproject.toml)
- `browser-use` >=0.9.5
  - Purpose: Browser automation helpers for Python agents.
  - Reason selected: Lets Python-based agents interact with live web pages when Node tooling is unavailable.
  - Used in: AIOS Python agent runners and scriptlets requiring DOM-level operations.
  - Official docs: https://pypi.org/project/browser-use/
  - Config: Declared in `pyproject.toml` with `uv` package manager references.

## 2. AIOS Stack

### Backend
- **Fastify v5**
  - Purpose: High-performance Node.js web framework powering AIOS managers and APIs.
  - Reason selected: Offers 3× throughput over Express plus TypeScript-first tooling.
  - Used in: `aios/packages/core` manager APIs and MCP orchestration endpoints.
  - Official docs: https://www.fastify.dev/
  - Config: Fastify server definitions live in `packages/core/src/server.ts`.
- **Socket.io**
  - Purpose: Real-time bidirectional communication channel.
  - Reason selected: Keeps agent dashboards and orchestration panels synchronized instantly.
  - Used in: Live UI updates and the AIOS dashboard pinging agent status.
  - Official docs: https://socket.io/
  - Config: Integrated via Fastify adapters in backend services.
- **TRPC**
  - Purpose: Zero-overhead, end-to-end typesafe APIs.
  - Reason selected: Eliminates schema drift between Next.js frontends and Fastify backend.
  - Used in: AIOS UI + backend contracts (`packages/api`).
  - Official docs: https://trpc.io/
  - Config: Exposed via `aios/packages/api/src/router.ts` and consumed by UI clients.
- **SQLite**
  - Purpose: Embedded development database for lightweight persistence.
  - Reason selected: Zero-config setup for local development before switching to PostgreSQL.
  - Used in: AIOS dev instances and quick demos.
  - Official docs: https://www.sqlite.org/docs.html
  - Config: `aios/packages/core/prisma` schema toggles between SQLite and Postgres.
- **PostgreSQL**
  - Purpose: Production-grade relational database supporting pgvector/Chroma.
  - Reason selected: Offers robustness plus pgvector extension for semantic RAG workloads.
  - Used in: Production AIOS deployments, including vector-backed agent memory.
  - Official docs: https://www.postgresql.org/docs/
  - Config: `prisma/schema.prisma` targets PostgreSQL when `NODE_ENV=production`.
- **pgvector/Chroma**
  - Purpose: Vector search capability for embeddings.
  - Reason selected: Enables semantic search and retrieval-augmented generation pipelines.
  - Used in: AIOS memory services and Chroma MCP server adapters.
  - Official docs: https://www.pgvector.org/, https://www.trychroma.com/
  - Config: pgvector enabled by default in production postgres schemas.

### Frontend
- **Next.js 14+**
  - Purpose: React meta-framework for AIOS dashboard and fwber frontends.
  - Reason selected: Combines SSR, file-based routing, and React Server Components for fast UIs.
  - Used in: `aios/packages/ui` and Next.js frontends in fwber.
  - Official docs: https://nextjs.org/docs
  - Config: Monorepo uses pnpm workspaces and shared `next.config.js` patches.
- **Tailwind CSS**
  - Purpose: Utility-first CSS framework.
  - Reason selected: Rapid styling consistency across dashboards and marketing sites.
  - Used in: AIOS dashboard, fwber UI, and shared design system components.
  - Official docs: https://tailwindcss.com/docs
  - Config: Configured via `tailwind.config.js` per package with shared tokens.
- **shadcn/ui**
  - Purpose: Accessible UI component library built on Radix primitives.
  - Reason selected: Provides polished components without heavy bundle size.
  - Used in: AIOS interface components and shared UI kits.
  - Official docs: https://ui.shadcn.com/
  - Config: Installed via pnpm and imported directly in frontend modules.
- **Vite**
  - Purpose: Modern build tool for fast HMR and ESM-first experience.
  - Reason selected: Accelerates frontend developer loops with instant rebuilds.
  - Used in: AIOS UI and supporting admin dashboards not running on Next.js.
  - Official docs: https://vitejs.dev/
  - Config: Project-level `vite.config.ts` reused across packages.

### Package Management
- **pnpm**
  - Purpose: Workspace-aware Node.js package manager.
  - Reason selected: Enforces strict dependency isolation with content-addressable storage for speed/disc savings.
  - Used in: All JavaScript/TypeScript packages across the monorepo.
  - Official docs: https://pnpm.io/
  - Config: Root `pnpm-workspace.yaml` defines packages and filters.
- **uv**
  - Purpose: Modern Python package manager compatible with pip.
  - Reason selected: 10–100× faster installs for Python tools (AIOS Python agents, CLI utilities).
  - Used in: Bootstrapping Python dependencies defined in `pyproject.toml` files.
  - Official docs: https://github.com/uw-labs/uv
  - Config: Wrappers in `scripts/` orchestrate `uv` installs before invoking Python runners.

## 3. FWBer Stack
- **Laravel 12**
  - Purpose: PHP API-first backend framework.
  - Reason selected: Mature ecosystem, robust routing, and Eloquent ORM support RESTful fwber services.
  - Used in: `fwber/fwber-backend` REST endpoints secured by Sanctum.
  - Official docs: https://laravel.com/docs/12.x
  - Config: Laravel config in `.env`, `config/features.php`, and `routes/api.php`.
- **PHP 8.3**
  - Purpose: Language runtime for Laravel and backend tooling.
  - Reason selected: Latest stable release offering union types, fibers, readonly props.
  - Used in: fwber backend, Artisan CLI commands, PHP-based utilities.
  - Official docs: https://www.php.net/docs.php
  - Config: `.php-version` pinning or Dockerfile ensures 8.3 runtime.
- **Sanctum**
  - Purpose: SPA/API token authentication package.
  - Reason selected: Lightweight token guard that integrates well with Laravel frontends.
  - Used in: `fwber/fwber-backend` for SPA authentication and API tokens.
  - Official docs: https://laravel.com/docs/sanctum
  - Config: Registered in `config/sanctum.php` and middleware stack.
- **MySQL**
  - Purpose: Relational database for fwber.
  - Reason selected: Spatial query support (ST_Distance) for proximity matching features.
  - Used in: fwber matchmaking, geolocation queries, and analytics.
  - Official docs: https://dev.mysql.com/doc/
  - Config: `database.php` uses spatial extensions plus `MySQL` migrations.
- **Next.js**
  - Purpose: Frontend framework for fwber UI.
  - Reason selected: Shared benefits with AIOS frontends (SSR, React ecosystem).
  - Used in: `fwber/fwber-frontend` for SPA experiences.
  - Official docs: https://nextjs.org/docs
  - Config: Custom `next.config.js` plus `pnpm` scripts.
- **Tailwind CSS**
  - Purpose: Consistent CSS framework shared with AIOS.
  - Reason selected: Rapid styling for fwber features and reusability across Next.js UI.
  - Used in: fwber frontend components and shared design system.
  - Official docs: https://tailwindcss.com/docs
  - Config: Shared `tailwind.config.cjs` extended from root variables.

## 4. Rhythm Game Stack

### ITGmania / StepMania
- **C++**
  - Purpose: Core rhythm game engine language for performance-critical loops.
  - Reason selected: Native execution needed for tight timing and audio handling.
  - Used in: `bobmani/itgmania` gameplay logic, scoring, and chart processing.
  - Official docs: ISO C++ standards documentation (latest drafts).
  - Config: Compiler flags managed via project-specific CMake/Makefiles.
- **OpenGL**
  - Purpose: Graphics API for rendering note highways and effects.
  - Reason selected: Cross-platform GPU acceleration for visual fidelity.
  - Used in: ITGmania render pipeline and effects modules.
  - Official docs: https://www.khronos.org/opengl/
  - Config: Linked via `CMakeLists.txt` or Autotools scripts.
- **SDL2**
  - Purpose: Windowing/input/audio for rhythm games.
  - Reason selected: Cross-platform multimedia support, standardized input handling.
  - Used in: ITGmania for input polling and audio playback.
  - Official docs: https://wiki.libsdl.org/
  - Config: SDL2 flags activated in `configure` or CMake presets.
- **Lua**
  - Purpose: Scripting language for themes and mods.
  - Reason selected: Compatible with NotITG modding ecosystem.
  - Used in: Theme logic, SCOREBOARD scripts, modding layers in StepMania forks.
  - Official docs: https://www.lua.org/manual/5.4/
  - Config: Lua scripts live under `Themes/` directories.
- **CMake/Autotools**
  - Purpose: Build systems for orchestrating cross-platform compilation.
  - Reason selected: Autotools for legacy ITG code, CMake for new cross-platform targets (migration ongoing).
  - Used in: Project builds (legacy Autotools) and modernized CMake wrappers.
  - Official docs: https://cmake.org/documentation/, https://www.gnu.org/software/autoconf/
  - Config: `CMakeLists.txt` and `configure.ac` maintained per project.

### ArrowVortex
- **Qt 5**
  - Purpose: Cross-platform GUI framework.
  - Reason selected: Native desktop widgets with rich graphics for the simfile editor.
  - Used in: ArrowVortex UI and editor modules.
  - Official docs: https://doc.qt.io/qt-5/
  - Config: Qt project configured via QMake and qmake spec files.
- **C++**
  - Purpose: Performance-critical language for audio and chart processing.
  - Reason selected: Needed for real-time chart editing and playback.
  - Used in: ArrowVortex core engine.
  - Official docs: ISO C++ references.
  - Config: Managed via Qt Creator project files and qmake settings.

### beatoraja
- **Java**
  - Purpose: Core language for the BMS/IIDX simulator.
  - Reason selected: JVM portability across platforms for both client/server.
  - Used in: `beatoraja` game client/server logic.
  - Official docs: https://docs.oracle.com/javase/8/docs/
  - Config: Build via Gradle scripts.
- **Gradle**
  - Purpose: JVM build automation.
  - Reason selected: Flexible dependency management and task orchestration.
  - Used in: `beatoraja/build.gradle` for compilation and packaging.
  - Official docs: https://gradle.org/docs/
  - Config: Gradle wrapper pinned to specific version.
- **libGDX**
  - Purpose: Game framework for cross-platform rendering/input.
  - Reason selected: Simplifies 2D/3D game development on JVM.
  - Used in: beatoraja rendering, audio, and input layers.
  - Official docs: https://libgdx.com/wiki/
  - Config: libGDX dependencies declared in Gradle.

### linthesia
- **Rust**
  - Purpose: Language for memory-safe, performant audio processing.
  - Reason selected: Combines safety without sacrificing native performance.
  - Used in: linthesia core audio engine.
  - Official docs: https://www.rust-lang.org/learn
  - Config: Managed via Cargo.toml.

## 5. Bob's Game (bg)
- **Java**
  - Purpose: Language powering the MMORPG client/server.
  - Reason selected: Cross-platform JVM runtime with mature networking.
  - Used in: `bg/client` and `bg/server` modules.
  - Official docs: https://docs.oracle.com/javase/8/docs/
  - Config: Managed via Gradle/Maven equivalents inside the project.
- **Gradle**
  - Purpose: Build system for the entire Java codebase.
  - Reason selected: Handles library management, task automation, and packaging.
  - Used in: Game builds, server deployment artifacts.
  - Official docs: https://gradle.org/docs/
  - Config: `bg/build.gradle` defines tasks for client/server.
- **Lua**
  - Purpose: Scripting layer for game logic and modding.
  - Reason selected: Lightweight, embeddable language for runtime extensions.
  - Used in: In-game event scripting and AI definitions.
  - Official docs: https://www.lua.org/manual/5.4/
  - Config: Scripts stored under `bg/scripts`.

## 6. N64 Decompilation (sm64coopdx, mk64)
- **C**
  - Purpose: Language aligning with original N64 codebase.
  - Reason selected: Matches assembly semantics and performance characteristics.
  - Used in: `sm64coopdx`, `mk64` disassembly and rebuild workflows.
  - Official docs: https://en.cppreference.com/w/c
  - Config: Toolchain cross-compiles for N64 architecture.
- **Custom N64 toolchain**
  - Purpose: ROM building, patching, and asset tools specific to N64 binaries.
  - Reason selected: Provides deterministic ROM generation and patching.
  - Used in: Building playable ROMs for co-op projects.
  - Official docs: Project-specific toolchain docs located within each submodule.
  - Config: Toolchain scripts stored under each decompilation repo.

## 7. Desktop Tools

### bobfilez
- **Qt 6**
  - Purpose: Modern GUI toolkit for the file manager.
  - Reason selected: Upgraded from Qt 5 for new features and better tooling.
  - Used in: `bobfilez` desktop interface.
  - Official docs: https://doc.qt.io/qt-6/
  - Config: QMake/CMake project files define Qt modules.
- **C++**
  - Purpose: Native performance for file management operations.
  - Reason selected: Ensures responsiveness when scanning directories.
  - Used in: `bobfilez` core engine.
  - Official docs: ISO C++ references.
  - Config: Compiler flags in `bobfilez/bobfilez.pro`.
- **qmake**
  - Purpose: Qt's native build system.
  - Reason selected: Simplifies Qt module linking and resource compilation.
  - Used in: Building bobfilez executables.
  - Official docs: https://doc.qt.io/qt-6/qmake-manual.html
  - Config: `.pro` files located in project root.

## 8. Crypto (bobcoin)
- **Solana**
  - Purpose: Blockchain platform for Proof of Health cryptocurrency.
  - Reason selected: High throughput (≈65k TPS) and low fees for micro-transactions.
  - Used in: bobcoin minting and ledger services.
  - Official docs: https://docs.solana.com/
  - Config: Solana CLI scripts and cluster configs under `bobcoin/`
- **Node.js / TypeScript**
  - Purpose: Server tooling and CLI interactions with Solana network.
  - Reason selected: Rapid development and compatibility with Solana SDKs.
  - Used in: bobcoin backend, helpers, and deployment scripts.
  - Official docs: https://nodejs.org/en/docs/, https://www.typescriptlang.org/docs/
  - Config: `package.json` in `bobcoin/` and `pnpm` scripts.

## 9. AI Agents & Orchestration
- **AutoGen**
  - Purpose: Microsoft multi-agent orchestration framework.
  - Reason selected: Structuring long-running agent conversations.
  - Used in: AIOS orchestration when grouping workstreams.
  - Official docs: https://github.com/microsoft/AutoGen
  - Config: Agent manifest files under `aios/agents` reference AutoGen adapters.
- **Amplifier**
  - Purpose: Agent amplification framework that scales capabilities.
  - Reason selected: Keeps high-level directives in sync with worker agents.
  - Used in: AIOS meta-orchestration logic.
  - Official docs: https://github.com/opencodeai/amplifier
  - Config: Settings in `aios/packages/amplifier`
- **smolagents**
  - Purpose: Lightweight agent execution runtime.
  - Reason selected: Minimal overhead for burst tasks.
  - Used in: Quick experiments and helper scripts.
  - Official docs: https://github.com/opencodeai/smolagents
  - Config: Python/Node wrappers around the core runtime.
- **Trae Agent**
  - Purpose: Specialized AI coding agent.
  - Reason selected: Automates code generation workflows within the workspace.
  - Used in: Dedicated coding agent orchestrations.
  - Official docs: https://github.com/opencodeai/trae-agent
  - Config: Local Trae agent installed via `uv`.
- **II-Agent**
  - Purpose: Intelligence agent coordinating decisions.
  - Reason selected: Augments strategic oversight across submodules.
  - Used in: Decision orchestration and monitoring.
  - Official docs: https://github.com/opencodeai/ii-agent
  - Config: Virtualenv under `ii-agent/`.

## 10. MCP (Model Context Protocol) Servers
- **Zen MCP**
  - Purpose: Multi-model AI gateway (70+ models) orchestrating consensus.
  - Reason selected: Universal access point for AI agents.
  - Used in: AIOS `mcp_zen` references and adapter logic.
  - Official docs: Referenced from `aios/submodules/mcp-zen`
  - Config: MCP connections configured in `.cursor/mcp.json`.
- **Serena**
  - Purpose: Code intelligence MCP server.
  - Reason selected: Semantic code understanding/navigation.
  - Used in: Developer assistance workflows for AIOS.
  - Official docs: Documented under `aios/references/mcp_repos/serena`.
  - Config: Registered as a default MCP on the hub.
- **Chroma MCP**
  - Purpose: Vector database MCP for RAG pipelines.
  - Reason selected: Enables semantic memory and retrieval.
  - Used in: AIOS memory services and `mcp_chroma` adapters.
  - Official docs: https://www.trychroma.com/docs/
  - Config: Vector embeddings stored in PostgreSQL via pgvector.
- **Tavily MCP**
  - Purpose: Web search MCP tuned for AI retrieval.
  - Reason selected: Provides optimized search results for agents.
  - Used in: Research-focused agent flows.
  - Official docs: Documented inside `aios/references/mcp_repos/tavily`.
  - Config: API keys stored in secure agent vaults.
- **Chrome DevTools MCP**
  - Purpose: Browser automation access.
  - Reason selected: Automates testing/interacting with websites and dashboards.
  - Used in: Test harnesses and UI validation calls.
  - Official docs: https://chromedevtools.github.io/devtools-protocol/
  - Config: Exposed via Chrome DevTools protocols accessible from MCP hub.
- **Filesystem MCP**
  - Purpose: Controlled file operations for agents.
  - Reason selected: Safely exposes workspace files to AI agents.
  - Used in: File access tooling.
  - Official docs: Workspace-specific docs inside `aios/agents/docs/mcp-filesystem.md`.
  - Config: Access restricted through sandboxed MCP adapters.

## 11. CI/CD & Testing
- **Playwright**
  - Purpose: Cross-browser end-to-end testing.
  - Reason selected: Validates web apps across Chromium, Firefox, WebKit in CI.
  - Used in: GitHub Actions workflows triggered on main/master PRs.
  - Official docs: https://playwright.dev/docs/intro
  - Config: Tests defined in `packages/ui/tests/playwright` and run with `pnpm test:e2e`.
- **GitHub Actions**
  - Purpose: CI/CD platform coordinating builds, tests, and deployments.
  - Reason selected: Native GitHub integration for monorepo workflows.
  - Used in: `/.github/workflows`, including `consensus-gate` and Playwright checks.
  - Official docs: https://docs.github.com/actions
  - Config: Workflows defined in `.github/workflows/*.yml`.
- **Conventional Commits**
  - Purpose: Commit message standard for changelog automation.
  - Reason selected: Keeps history structured for versioning tools.
  - Used in: All agents and engineers when committing changes.
  - Official docs: https://www.conventionalcommits.org/
  - Config: Enforced via CI lint scripts.

## 12. Version Control & Repository Management
- **Git**
  - Purpose: Distributed version control.
  - Reason selected: Industry-standard for tracking history across submodules.
  - Used in: Entire workspace including root and nested repositories.
  - Official docs: https://git-scm.com/doc
  - Config: Pre-commit hooks and configuration files at root.
- **Git Submodules**
  - Purpose: Manage independent project histories within the monorepo.
  - Reason selected: Keeps legacy toolchains and projects intact while sharing workspace context.
  - Used in: `aios`, `bobcoin`, `filez`, and numerous nested repos.
  - Official docs: https://git-scm.com/docs/git-submodule
  - Config: `.gitmodules` plus update scripts like `scripts/update_repos.py`.
- **GitHub CLI (gh)**
  - Purpose: Scriptable GitHub operations (issues, PRs, etc.).
  - Reason selected: Enables automation without switching to the web UI.
  - Used in: Workflows and local developer scripts.
  - Official docs: https://cli.github.com/manual/
  - Config: Aliases defined in developer dotfiles or automation scripts.
