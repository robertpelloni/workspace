# TODO — Omni-Workspace v5.20.1

**Current:** v5.20.1 • 270 submodules across workspace • 2026-06-19

## 🎯 v5.13.0 Milestone: Production Hardening

The ROADMAP calls for **Phase 4: Production Hardening** — this is the next frontier. With all upstreams synced and all feature branches merged, the workspace must now shift from consolidation to stability, security, and observability.

### Top Priority
- [ ] **Resolve 283 GitHub Dependabot vulnerabilities** — Critical security debt across workspace
- [ ] **Clean massive dirty state in tormentnexus (3,929 files)** — `.pi-lens/cache` artifacts, temp scripts, uncommitted MCP config changes
- [ ] **Clean ArrowVortex dirty state (980 files)** — Submodule conflict in lib/ddc, pending merge resolution
- [ ] **Finalize TormentNexus MCP protocol** — Cross-module communication, MCP aggregator stability, alwaysOn servers
- [ ] **Revisit bobeditpro upstream** — 94 commits behind Audacity, 25+ conflicts in core audio/UI files (deferred x3)
- [ ] **Revisit topaz-ffmpeg upstream** — 15+ libswscale conflicts with FFmpeg (deferred x3)

---

## 🔐 Security (Critical)

- [ ] **Dependabot vulnerability triage** — Categorize 283 vulns by severity (critical, high, medium, low)
- [ ] **Fix critical/high vulns** — Focus on: jules-autopilot (vite, axios), borg (express, lodash), web apps
- [ ] **npm audit pass** — Run `npm audit fix` across all Node.js projects
- [ ] **pip audit pass** — Run `pip audit` or `safety check` across Python projects
- [ ] **Docker image scanning** — Audit container images for known CVEs
- [ ] **Establish Dependabot alert response SLA** — 48h for critical, 7d for high

---

## 🧹 Workspace Hygiene

### Dirty Repo Cleanup

| Project | Dirty Files | Action Required |
|---------|-------------|-----------------|
| tormentnexus | 3,929 | Add `.pi-lens/cache/`, `*.tmp`, `akb*`, `_llm_*` to `.gitignore`, then commit |
| ArrowVortex | 0 | ✅ Clean - untracked build artifacts only (odcnn/, src/) |
| WebAI-to-API | 30 | Review, commit or discard changes |
| fwber | 0 | ✅ Clean - feature branch merged and pushed |
| jules-autopilot | 0 | ✅ Clean - axios upgraded and pushed |

- [ ] **Update global `.gitignore`** — Add patterns for pi-lens cache, temp scripts, database files, `$null`
- [ ] **Commit critical uncommitted work** — Review dirty files in each repo for genuine changes vs. artifacts
- [ ] **Remove orphaned directories** — `metamcp/`, `tormentnexus2/`, `tormentnexus_temp/`, `.tmp-adb-mysql/` if no longer needed
- [ ] **Rebuild workspace index** — `workspace_index.db` may be stale

### Upstream Sync

- [ ] **bobeditpro upstream merge (Audacity)** — Blocked by 25+ conflicts. Dedicated session needed with manual conflict resolution in core audio/UI files
- [ ] **topaz-ffmpeg upstream merge (FFmpeg)** — 15+ conflicts in libswscale. Dedicated session needed
- [ ] **bobfilez history reconciliation** — Unrelated history with robertpel83/FileOrganizer. Consider replacing with fresh fork
- [ ] **raindropioapp history reconciliation** — Unrelated history with raindropio/app. Consider replacing with fresh fork
- [ ] **bobmani/arrowvortex lib/ddc conflict** — Submodule vs embedded files in lib/ddc. Determine canonical source
- [ ] **Transition remaining HTTP origins to SSH** — The 5 remaining HTTP submodule URLs for consistent auth

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

- [ ] **Update ROADMAP.md** — Move Completed items to history, update Phase 4 with current status
- [ ] **Update SUBMODULE_INVENTORY.md** — Current as of v5.12.0, but needs verification pass
- [ ] **Update DASHBOARD.md** — Last updated 2026-03-20 (90+ days stale). Re-scan all repos
- [ ] **Create per-project READMEs** — 40+ repos lack a README; critical for onboarding
- [ ] **Document sync protocol** — executive_sync.py, fetch_all.py, sync_main.ps1 — purpose and usage
- [ ] **Update handoff templates** — HANDOFF.md needs modernization for v5.x processes
- [ ] **Centralize IDEAS_STAGING.md** — Merge MASTER_IDEAS.md, IDEAS_STAGING.md into docs/ideas/

---

## ♻️ Disk & Resource Management

- [ ] **Remove stale build artifacts** — Large binaries (ultratrader.exe removed, check for others)
- [ ] **Compress/archive old logs** — `logs/` directory may contain GBs of debug output
- [ ] **Review workspace disk usage** — 125 repos × avg 500MB = significant footprint. Identify candidates for LFS
- [ ] **Migrate game assets to Git LFS** — MarbleBlast, supersaber, sm64coopdx binaries
- [ ] **Clean unused Docker images** — `docker system prune -a` after containerization pass

---

## 📊 Metrics Dashboard

| Metric | Current | Target | Status |
|--------|---------|--------|--------|
| Submodules Synced | 65/65 | 65/65 | ✅ Current |
| Upstreams Current | 12/16 | 16/16 | ⚠️ 4 deferred |
| Feature Branches Merged | 100% | 100% | ✅ v5.20.0 — Maestro, pi-mono, aimoneymachine_site, fcdm, jules-autopilot, bobfilez |
| Dependabot Vulnerabilities (Root) | 283 | 0 | 🔴 Critical |
| TormentNexus Vulnerabilities | 1,114 | 0 | 🔴 Critical (22 critical, 456 high) |
| jules-autopilot axios vulns | ✅ Fixed | 0 | ✅ 4+ high vulns fixed |
| TormentNexus security patches | ✅ 42+ pkgs updated | N/A | ✅ vite, mcp-sdk, lodash, axios, undici, path-to-regexp |
| connectTimeoutMs source fix | ✅ 30s→60s | N/A | ✅ MCPAggregator.ts aligned with dist |
| Dirty Repos | 2 | 0 | ⚠️ WebAI-to-API (30 files) |
| Dirty Files Total | ~30 | 0 | ⚠️ Needs cleanup |
| Port 4100 (TormentNexus) | ✅ Up | ✅ Up | ✅ |
| MCP Servers Connected | 4/56 | 6+ | ⚠️ Improving |
| Tools Available | 46 | 63+ | ⚠️ Improving |
| Documentation Staleness | 90+ days | < 30 days | ⚠️ Needs update |

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

*Last updated: 2026-06-19*
*Previous: v5.20.0 — Dual-Direction Merge Engine*
*Next: v5.20.1 — Submodule fix pass: 7 broken submodule references repaired*
- Verify build output after 5.13.6 sync
