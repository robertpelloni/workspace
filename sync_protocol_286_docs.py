#!/usr/bin/env python3
"""Protocol #286 docs: version bump v5.295.0 + CHANGELOG/HANDOFF/ROADMAP/TODO. Written fresh for #286."""
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")
DATE = "2026-11-13"
NEW = "v5.295.0"
OLD = "v5.294.0"

for name in ["VERSION", "VERSION.current"]:
    (ROOT / name).write_text(NEW + "\n", encoding="utf-8")
(ROOT / "VERSION.md").write_text(f"# VERSION\n\n**Current:** {NEW}\n**Updated:** {DATE}\n", encoding="utf-8")
print("version files ok")

summary = ("0 fast-forwards needed (all defaults already at published tips), 0 forward merges, "
           "Maestro push confirmed up-to-date, jules-autopilot dirty-state commit pushed (+1), "
           "fwber v2.3.70 dirty-state commit pushed (version sync + useWebRTC), "
           "4 submodule pointers staged (fwber, jules-autopilot, realestatecrm, marketing_agent), pincheck 0 unpublished, "
           "4 branches retained conflict-final")

p = ROOT / "CHANGELOG.md"
t = p.read_text(encoding="utf-8", errors="replace")
entry = f"""## [{NEW}] - {DATE} - Protocol #286: Repository Sync & Intelligent Merge

### Synced
- **Submodules**: {summary}. Scan/triage covered 114 repos; unique branches remained only in upstream mirrors (fwber/hermes-agent `heads/upstream/*`, filtered), dependabot branches (filtered), excluded lanes, and the 4 retained conflicts below.
- Reverse: veilid scaffold reverse-merge attempted, conflict-aborted (retained, no reverse). `bobmani/itgmania jules-12512815185672744343` verified fully contained in `release` (cherry 0), no reverse needed.
- Origin sync: hyperporn origin-sync attempted (`+2/-3`), conflict-final, retained diverged; electricsheep/neverball upstream defaults unchanged (push up-to-date).

### Retained for Robert (untouched, no deletions)
- 4 conflict branches, conflict both directions (plain, `-X theirs`, reverse), never forced: bobfilez `backup/wip-leader-sync-20261107` (+1), freellm `temp-main` (+2), veilid `jules-scaffold-0.1.0` (+17), hyperporn `backup/wip-leader-sync-20261107` (+2)
- Excluded: HyperNexus + HyperNexus2old (sibling lanes; fetch/status only from leader lane), openclaw-config / openclaw-dashboard (foreign/diverged), unitedbeats_site (site lane), unpublished root pointers not staged (openclaw-dashboard, projectM-upstream, hyperporn skipped by pincheck guard)

### Coordination
- Leader bus id `muse-wonder-leader`; CDP check-ins to Bobbi (muse.ai) verified sent (composer cleared); Bobbi reviewing proposal PDFs, no v6 ruling yet (usage). Robert instruction recorded: always deploy on protocol close-out.
- HyperNexus code + running kernel both v1.0.53, fetch-verified 0/0 vs origin/main; supervisor session still degraded (consecutiveFailures 0).

"""
lines = t.splitlines(True)
lines.insert(2, entry)
p.write_text("".join(lines), encoding="utf-8")
print("CHANGELOG ok")

p = ROOT / "HANDOFF.md"
t = p.read_text(encoding="utf-8", errors="replace")
handoff = f"""# HANDOFF - {NEW} - {DATE} - Protocol #286: Repository Sync & Intelligent Merge

## Session - Protocol #286 (this session)

### Steps 1-2 (ledgers `sync_protocol_286_*`)
- Scan/triage: 114 repos. {summary}.
- Remaining verified unmerged = 4 retained branches + 1 dependabot (planet_fitness, filtered as upstream/dependabot), all retained (list in CHANGELOG {NEW}).
- Root pointers staged with published-only pincheck (0 unpublished); STRUCTURAL_MAP regenerated 132/133 (hypercode not initialized).
- fwber dirty commit `cae36e90e`: FWBer lane v2.3.70 version-string sync across VERSION/package files + `useWebRTC.ts` hook update, committed as track-dirty-state and pushed (repo moved notice: FWBerLLC/fwber).
- Build/deploy: fill after running build.bat; do not clean binaries. Deploy = root push + build verification per Robert's always-deploy instruction (2026-11-13).

### Coordination
- Leader bus id `muse-wonder-leader`; Codex `codex-desktop-laptop`, Antigravity `antigravity-gemini`, `muse-code-coord` registered. Coordination loop checks CDP + bus + HyperNexus fetch sync every ~17 min.
- HyperNexus supervisor fix from earlier session remains uncommitted in shared HyperNexus working tree (sibling lanes own that commit); leader lane fetch/status only there.

## Prior
"""
if "Protocol #286" not in t[:200]:
    p.write_text(handoff + t, encoding="utf-8")
print("HANDOFF ok")

p = ROOT / "ROADMAP.md"
t = p.read_text(encoding="utf-8", errors="replace")
if "Protocol #286" not in t:
    block = f"## Current Status ({NEW})\n\n**Protocol #286 ({DATE}):** {summary}. 4 conflict branches retained for Robert. Always-deploy is now the standing close-out rule.\n\n"
    t = t.replace("## Current Status", block, 1) if "## Current Status" in t else block + t
    p.write_text(t, encoding="utf-8")
p = ROOT / "TODO.md"
t = p.read_text(encoding="utf-8", errors="replace")
if "Protocol #286" not in t:
    block = (f"### Protocol #286 Outcomes ({DATE})\n\n- [x] {NEW} - Protocol #286: {summary}\n"
             "- [ ] Robert: disposition 4 retained conflict branches; umbrella v6 corrections window still open with Bobbi\n"
             "- [ ] Verify pi-mono `go build ./...` + `go test ./pkg/ai/` (not re-run in #283-#286; build.bat compiles pi-mono only)\n\n")
    p.write_text(block + t, encoding="utf-8")
print("ROADMAP/TODO ok")
print("docs done")
