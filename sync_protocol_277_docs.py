#!/usr/bin/env python3
from pathlib import Path
ROOT = Path(r"C:\Users\hyper\workspace")

# TODO: insert Protocol #277 outcomes after header line 3 block
p = ROOT / "TODO.md"
t = p.read_text(encoding="utf-8", errors="replace")
block = """
### Protocol #277 Outcomes (2026-11-05)
- 91 forward merges pushed across ~45 repos (bcs x5, pi-mono dashboard, succubus.red x4, new-repo Jules waves); 35+ defaults sync-merged with origin
- [ ] freellm `temp-main` (+2/-253) — conflicts both strategies, dedicated session
- [ ] slsk `jules-57044827041196387` (+7) + sync-conflict — dedicated session
- [ ] veilid `jules-scaffold-0.1.0` Gold Master (+17/-84) — dedicated session
- [ ] bobmani/itgmania `jules-12512815185672744343` (+30) — dedicated session
- [ ] sales_bot `jules-project-sirens` (+40) — dedicated session
- [ ] bobmani/hymnmania origin sync (+86 conflicts); bobmani sync-conflict; beatoraja checkout ambiguity
- [ ] _fix repos push-rejected (bg_fix, bobfilez_fix, bobsgameonlinejava_fix) — local syncs retained, needs force-with-lease decision
"""
if "Protocol #277 Outcomes" not in t:
    lines = t.splitlines(True)
    lines.insert(4, block)
    p.write_text("".join(lines), encoding="utf-8")
print("TODO ok")

# ROADMAP: add #277 row to workspace merges area (append after Current Status header block)
p = ROOT / "ROADMAP.md"
t = p.read_text(encoding="utf-8", errors="replace")
if "Protocol #277" not in t:
    t = t.replace("## Current Status (v5.287.0)",
                  "## Current Status (v5.287.0)\n\n**Protocol #277 (2026-11-05):** 91 forward merges pushed (~45 repos incl. bcs x5, pi-mono, succubus.red, educational_video_pipeline, mparty, make_elon_laugh, webapp_factory); 132/133 submodules initialized; 5 conflict-final branches retained for dedicated sessions (freellm temp-main, slsk, veilid scaffold, itgmania jules-1251, sales_bot sirens).", 1)
    p.write_text(t, encoding="utf-8")
print("ROADMAP ok")

# .memory/main.md: bump state + milestone
p = ROOT / ".memory" / "main.md"
t = p.read_text(encoding="utf-8", errors="replace")
t = t.replace("## Current State (v5.286.13)", "## Current State (v5.287.0)")
if "v5.287.0" not in t.split("## Milestones")[0].split("Current State")[1][:2000]:
    pass
if "- [x] v5.287.0" not in t:
    t = t.replace("- [ ] 62 GitHub vulnerabilities",
                  "- [x] v5.287.0 - Protocol #277: 91 forward merges (~45 repos), 21 submodules initialized (132/133), 35+ defaults synced, 5 conflict-final branches deferred\n- [ ] 62 GitHub vulnerabilities", 1)
    p.write_text(t, encoding="utf-8")
print("MEMORY ok")
