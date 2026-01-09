# AGENTS & WORKSPACE INTELLIGENCE

**Generated:** 2026-01-08
**Context:** Multi-project AI Orchestration Environment

## INSTALLED AGENTS

| Agent | Location | Status | Type | Notes |
|---|---|---|---|---|
| **Junie** | `~/bin/junie` | ✅ Verified | CLI | Global binary |
| **II-Agent** | `./ii-agent` | ✅ Verified | Local | Python .venv verified |
| **Trae-Agent** | `./trae-agent` | ✅ Verified | Local | Installed via `uv`, version 0.1.0 |

## EXPLORATION FINDINGS

### 🐍 Python Projects (AIOS)
- **Convention Deviation**: The `aios` repository largely lacks standard `src/` directory structures, placing modules in root or ad-hoc subdirectories.
- **Dependency Management**: Modern tooling (`uv`) is being introduced, but legacy `pip`/`requirements.txt` usage persists.

### 📦 Node/JS Projects (Fwber, AIOS Web)
- **Package Managers**: Mixed usage of `pnpm` (preferred) and `npm`. Lockfile contention observed in some submodules.
- **Frameworks**: Next.js 14 observed in newer modules (`fwber`, `opencode-autopilot`), legacy Express/Node elsewhere.

### ⚙️ C++ Projects (ArrowVortex, Filez, ITGMania)
- **Build Systems**: Inconsistent build systems across projects.
  - `ArrowVortex`: CMake
  - `ITGMania`: Autotools/Makefiles (legacy ITG fork)
  - `Filez`: Qt/qmake & CMake hybrid
- **Tooling**: `vcpkg` is present in root but integration varies by project.

## RECOMMENDATIONS
1. **Standardization**: Enforce `src/` layout for new Python modules in `aios`.
2. **Consolidation**: Standardize on `pnpm` for all JS/TS projects to save disk space and reduce conflicts.
3. **Migration**: Move legacy Makefiles to CMake where feasible for `ITGMania` to unify C++ tooling.
