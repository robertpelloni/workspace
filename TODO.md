# TODO — Omni-Workspace v5.71.0

**Current:** v5.71.0 • 80+ submodules across workspace • 2026-06-28

## 🎯 v5.50.0 Milestone: Production Hardening

The ROADMAP calls for **Phase 4: Production Hardening**. With all upstreams synced and feature branches assessed, focus shifts to stability, security, and observability.

### Top Priority

- [x] **Resolve critical shell-quote vulnerability (CVE-2025-27789)** — 1 critical vuln fixed in research/workspace-orchestrator
- [ ] **Resolve remaining 146 GitHub Dependabot vulnerabilities** (0 critical, 61 high) — Security debt across workspace
- [ ] **Clean remaining dirty state** — `.pi-lens/cache` artifacts, temp scripts, uncommitted changes
- [ ] **bg nested references/ submodules** — ~50 uninitialized (ControlNet, Stable Diffusion, etc.)
- [ ] **Finalize TormentNexus MCP protocol** — Cross-module communication, MCP aggregator stability
- [ ] **Revisit bobeditpro upstream** — 94 commits behind Audacity (deferred multiple times)
- [ ] **Revisit topaz-ffmpeg upstream** — 15+ libswscale conflicts with FFmpeg (deferred multiple times)

---

## 🔐 Security (Critical)

- [ ] **Dependabot vulnerability triage** — Categorize 165 vulns by severity (1 critical, 72 high)
- [ ] **Fix critical/high vulns** — Focus on: jules-autopilot, borg, web apps
- [ ] **npm audit pass** — Run `npm audit fix` across all Node.js projects
- [ ] **pip audit pass** — Run `pip audit` or `safety check` across Python projects
- [ ] **Establish Dependabot alert response SLA** — 48h for critical, 7d for high

---

## 🧹 Workspace Hygiene

### Dirty Repo Cleanup

| Project | Dirty Files | Action Required |
|---------|-------------|-----------------|
| tormentnexus | ~3,900 | Add `.pi-lens/cache/`, `*.tmp`, `akb*`, `_llm_*` to `.gitignore`, then commit |
| borg | 0 | ✅ Clean (after EP #38 sync) |
| Maestro | 0 | ✅ Clean (synced to latest) |

- [ ] **Update global `.gitignore`** — Add patterns for pi-lens cache, temp scripts, database files
- [ ] **Commit critical uncommitted work** — Review dirty files for genuine changes vs. artifacts
- [ ] **Remove orphaned directories** — `MilkDrop3-2077/`, `food.ai/`, `temp_nottingham/`, `tmp_bobcoin/`

### Upstream Sync

- [ ] **bobeditpro upstream merge (Audacity)** — Blocked by 25+ conflicts. Dedicated session needed
- [ ] **topaz-ffmpeg upstream merge (FFmpeg)** — 15+ conflicts in libswscale. Dedicated session needed
- [ ] **bobfilez history reconciliation** — Unrelated history (deferred)
- [ ] **Transition remaining HTTP origins to SSH** — Remaining HTTP submodule URLs for consistent auth

---

## 🏗️ Infrastructure & Monitoring

### Phase 4 Deliverables (from ROADMAP)

- [ ] **Global health checks** — Implement `/health` endpoints for all web services, aggregate into workspace dashboard
- [ ] **Containerization** — Dockerize key services: TormentNexus, fwber, jules-autopilot, bobbybookmarks
- [ ] **Service orchestration** — Move from `start.bat` to docker-compose with health dependencies
- [ ] **Log aggregation** — Centralize logs from all running services (Loki / ELK / simple flat files)
- [ ] **Alerting** — Set up uptime monitors for production services (fwber.com, bobsgame.com)
- [ ] **Backup automation** — Automated DB snapshots for tormentnexus, fwber, bobbybookmarks

### Tooling

- [ ] **Fix pybind11 recursive directory loop** in bobfilez — Blocks all git operations on that repo
- [ ] **Automate ROADMAP/TODO updates** via post-merge hooks in workspace root
- [ ] **Improve error handling** in global sync scripts for missing remote repos
- [ ] **Add git pre-push hooks** — Prevent pushing with unresolved SECURITY.md issues
- [ ] **Add submodule health checks** — Auto-detect dead gitlinks before they accumulate

---

## 🚀 Active Development Priorities

### 1. TormentNexus — MCP Protocol & Aggregator

- [ ] **Stabilize MCP aggregator** — alwaysOn servers auto-connect on restart (filesystem, ripgrep, desktop-commander, fetch)
- [ ] **Persist `connectTimeoutMs` fix** — Change from 30s→60s is in `dist/` only; needs source change in MCPAggregator.ts
- [ ] **Connect remaining servers** — anyquery, tormentnexus-supervisor, and 52 other catalog servers
- [ ] **Expand tool coverage** — Currently 46 tools from 4 servers; target 63+ with all key servers
- [ ] **Document MCP architecture** — Flow diagram for config sources (.jsonc → db → aggregator)
- [ ] **Add MCP server health dashboard** — Web UI showing connected servers, tool counts, last error

### 2. fwber — Dating Platform

- [ ] **Set upstream tracking** — `fwber-code/fwber` needs proper remote setup (currently no upstream tracking)
- [ ] **Review 30 dirty files** — Commit pending feature work or MVP milestones
- [ ] **Dockerize for deployment** — Laravel/Next.js/PostgreSQL stack needs containerization

### 3. jules-autopilot — AI Dashboard

- [ ] **Review 27 dirty files** — Pending changes from previous session
- [ ] **Dependabot fixes** — Known vulns in vite, axios, and other deps
- [ ] **Sync with sbhavani upstream** — Currently up to date, monitor for new commits

### 4. Maestro — AI Agent Orchestration

- [ ] **Push 1 ahead commit** — Unpushed changes on main
- [ ] **Expand agent types** — Current: 13 agent types. Target: 20+ with specialized roles
- [ ] **Integrate with TormentNexus MCP** — Cross-module agent-to-agent communication

### 5. Bobmani — Rhythm Game Suite

- [ ] **ArrowVortex lib/ddc conflict resolution** — Submodule vs embedded files in lib/ddc
- [ ] **Clean 980 dirty files** — Mostly build artifacts and submodule state
- [ ] **Sync with upstreams** — StepMania, itgmania, ksm-v2, arrowvortex, linthesia

---

## 📚 Documentation & Knowledge

- [x] **Update ROADMAP.md** — Added Phase 5b: pi-mono Phase 19/20 Assimilation
- [ ] **Update SUBMODULE_INVENTORY.md** — Current as of v5.12.0, but needs verification pass
- [ ] **Update DASHBOARD.md** — Last updated 2026-03-20 (90+ days stale). Re-scan all repos
- [ ] **Create per-project READMEs** — 40+ repos lack a README; critical for onboarding
- [ ] **Document sync protocol** — executive_sync.py, fetch_all.py, sync_main.ps1 — purpose and usage
- [ ] **Update handoff templates** — HANDOFF.md needs modernization for v5.x processes
- [ ] **Centralize IDEAS_STAGING.md** — Merge MASTER_IDEAS.md, IDEAS_STAGING.md into docs/ideas/

---

## ♻️ Disk & Resource Management

- [ ] **Compress/archive old logs** — `logs/` directory may contain GBs of debug output
- [ ] **Remove stale build artifacts** — Check for large binaries across repos
- [ ] **Review workspace disk usage** — 80+ repos × avg 500MB = significant footprint. Identify candidates for LFS
- [ ] **Migrate game assets to Git LFS** — Consider for large game repos
- [ ] **Clean unused Docker images** — `docker system prune -a` after containerization pass

---

## 📊 Metrics Dashboard

| Metric | Current | Target | Status |
|--------|---------|--------|--------|
| Submodules Synced | 80+/80+ | 80+ | ✅ Current (EP #38) |
| Upstreams Current | All synced | All synced | ✅ v5.50.0 |
| Feature Branches Assessed | 86+ scanned | N/A | ✅ No high-value forward merges |
| Maestro Submodule | ✅ f702e702 | Latest | ✅ Multi-agent router + 26+ agents |
| bg/bobsgameonlinejava | ✅ 8d09fad | Latest | ✅ lwjgl3 fix |
| Dependabot Vulnerabilities | 146~ | 0 | 🟡 Fixed critical (awaiting Dependabot re-scan) |
| bg nested references/ | ~50 uninitialized | N/A | ⚠️ Large third-party repos |
| Documentation | Up to date | Current | ✅ ROADMAP, TODO, HANDOFF updated

---

## 🏁 Sprint Plan: v5.13.0 (2026-06-13 → 2026-06-20)

### Sprint Theme: Production Hardening

**Week 1 Goals:**

**Completed:**

- [x] Fix TormentNexus MCP aggregator source fix (dist→source persist, connectTimeoutMs 30s→60s)
- [x] Clean TormentNexus dirty state (add gitignore, commit Go MCP tools)
- [x] Resolve jules-autopilot axios vulnerabilities (4+ high vulns fixed)
- [x] Patch 42+ vulnerable packages in TormentNexus (vite, mcp-sdk, lodash, axios, undici, path-to-regexp)
- [x] Push fwber feature branch (v2.1.9-intelligent-match-refinement)
- [x] Update DASHBOARD.md/CHANGELOG.md with current repo states
- [x] Build completed successfully

**Remaining:**

- [ ] Resolve top 50 Dependabot vulnerabilities (npm audit broken - SSL/TLS issue on this machine)
- [ ] WebAI-to-API remaining dirty state (~30 files)
- [ ] Dockerize TormentNexus + fwber
- [ ] Resolve bobeditpro upstream sync (dedicated conflict resolution session)
- [ ] Connect anyquery + tormentnexus-supervisor MCP servers
- [ ] Establish Dependabot response SLA
- [ ] Update all stale documentation

**Week 2 Goals:**

- [ ] Dockerize TormentNexus + fwber
- [ ] Resolve bobeditpro upstream sync (dedicated conflict resolution session)
- [ ] Connect anyquery + tormentnexus-supervisor MCP servers
- [ ] Establish Dependabot response SLA
- [ ] Update all stale documentation

---

*Last updated: 2026-06-20*
*Previous: v5.20.2 — geany btk submodule fix*
*Next: v5.21.0 — pi-mono Phase 19/20 Assimilation Forward Merge*
