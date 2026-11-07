#!/usr/bin/env python3
from pathlib import Path
ROOT = Path(r"C:\Users\hyper\workspace")

p = ROOT / "TODO.md"
t = p.read_text(encoding="utf-8", errors="replace")
block = """
### Protocol #280 Outcomes (2026-11-06)
- 39 forward merges pushed; pi-mono dashboard re-merged and build/pkg-ai tests re-verified green; Maestro + MilkDrop3_fix pushed
- [ ] 5 retained conflict branches (freellm, slsk +11, veilid, itgmania +27, sales_bot sirens +40) - Robert decision: cherry-pick / dedicated / abandon
- [ ] unitedbeats_site dashboard branch (+7) - merge after local site work is committed
"""
if "Protocol #280 Outcomes" not in t:
    lines = t.splitlines(True)
    lines.insert(4, block)
    p.write_text("".join(lines), encoding="utf-8")
print("TODO ok")

p = ROOT / "ROADMAP.md"
t = p.read_text(encoding="utf-8", errors="replace")
if "Protocol #280" not in t:
    t = t.replace("## Current Status (v5.288.0)",
                  "## Current Status (v5.288.0)\n\n**Protocol #280 (2026-11-06):** 39 forward merges pushed; pi-mono dashboard re-merged, build/tests green; 5 conflict branches retained for Robert's disposition decision.", 1)
    p.write_text(t, encoding="utf-8")
print("ROADMAP ok")

p = ROOT / ".memory" / "main.md"
t = p.read_text(encoding="utf-8", errors="replace")
t = t.replace("## Current State (v5.287.0)", "## Current State (v5.288.0)")
if "- [x] v5.288.0" not in t:
    t = t.replace("- [ ] 62 GitHub vulnerabilities",
                  "- [x] v5.289.0 - Protocol #279: 34 forward merges, pi-mono regression restored, 5 branches retained\n- [ ] 62 GitHub vulnerabilities", 1)
    p.write_text(t, encoding="utf-8")
print("MEMORY ok")



