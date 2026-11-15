#!/usr/bin/env python3
"""Protocol #285 docs: version bump v5.294.0 + CHANGELOG/HANDOFF/ROADMAP/TODO."""
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")
DATE = "2026-11-12"
NEW = "v5.294.0"

for name in ["VERSION", "VERSION.current"]:
    (ROOT / name).write_text(NEW + "\n", encoding="utf-8")
(ROOT / "VERSION.md").write_text(f"# VERSION\n\n**Current:** {NEW}\n**Updated:** {DATE}\n", encoding="utf-8")
print("version files ok")

summary = ("35 fast-forwards pushed, Maestro swept, hyperharness origin-sync pushed, "
           "1 reverse merge pushed, 38 submodule pointers staged, 4 branches retained, 0 forward merges needed")

p = ROOT / "CHANGELOG.md"
t = p.read_text(encoding="utf-8", errors="replace")
entry = f"""## [{NEW}] - {DATE} - Protocol #285: Repository Sync & Intelligent Merge

### Synced
- **Submodules**: {summary}. Feature-branch inventory had already converged via parallel leader lanes (#281-#284) plus this lane's #284; this run fast-forwarded every default branch that lagged its published tip.
- Reverse: main merged back into `bobmani/itgmania jules-12512815185672744343` and pushed.

### Retained for Robert (untouched, no deletions)
- 4 conflict branches, conflict both directions, never forced: bobfilez `backup/wip-leader-sync-20261107` (+1), freellm `temp-main` (+2), veilid `jules-scaffold-0.1.0` (+17), hyperporn `backup/wip-leader-sync-20261107` (+2)
- Excluded: HyperNexus + HyperNexus2old (sibling Antigravity/Codex lanes; fetch/status only), openclaw-config (foreign remote), unitedbeats_site (site lane), unpublished root pointers not staged

### Coordination
- Caught up on latest Antigravity sessions (`ff90f2fd` HyperNexus v1.0.48 shipped; `8e716423` RealEstateCRM build lane) and Codex Desktop rollout `01a1d0bc` (died at start: missing `MODEL_API_KEY`; live Codex lane runs via kernel bus id `codex-desktop-laptop`).
- HyperNexus code + running kernel both v1.0.48, fetch-verified 0/0 vs GitLab origin/main.

"""
lines = t.splitlines(True)
lines.insert(2, entry)
p.write_text("".join(lines), encoding="utf-8")
print("CHANGELOG ok")

p = ROOT / "HANDOFF.md"
t = p.read_text(encoding="utf-8", errors="replace")
handoff = f"""# HANDOFF - {NEW} - {DATE} - Protocol #285: Repository Sync & Intelligent Merge

## Session - Protocol #285 (this session)

### Steps 1-2 (ledgers `sync_protocol_285_*`)
- Scan/triage: 155 actionable before upstream filtering (warp dominates). {summary}.
- Remaining verified unmerged = exactly 4 branches, all conflict-final both directions, retained (list in CHANGELOG {NEW}).
- Root pointers staged with published-only pincheck; build below.
- Build: fill after running build.bat, do not clean binaries.

### Coordination
- Leader bus id `muse-wonder-leader`; Codex `codex-desktop-laptop` registered and acked; Antigravity `ff90f2fd`/`8e716423` read for catch-up. Coordination loop cron `e6b40ba9` checks CDP + bus + HyperNexus fetch sync every 17 min.
- Build: see Build section above.

## Prior
"""
if "Protocol #285" not in t[:200]:
    p.write_text(handoff + t, encoding="utf-8")
print("HANDOFF ok")

p = ROOT / "ROADMAP.md"
t = p.read_text(encoding="utf-8", errors="replace")
if "Protocol #285" not in t:
    block = f"## Current Status ({NEW})\n\n**Protocol #285 ({DATE}):** {summary}. 4 conflict branches retained for Robert.\n\n"
    t = t.replace("## Current Status", block, 1) if "## Current Status" in t else block + t
    p.write_text(t, encoding="utf-8")
p = ROOT / "TODO.md"
t = p.read_text(encoding="utf-8", errors="replace")
if "Protocol #285" not in t:
    block = (f"### Protocol #285 Outcomes ({DATE})\n\n- [x] {NEW} - Protocol #285: {summary}\n"
             "- [ ] Robert: disposition 4 retained conflict branches; umbrella v6 corrections window still open with Bobbi\n\n")
    p.write_text(block + t, encoding="utf-8")
print("ROADMAP/TODO ok")
print("docs done")
