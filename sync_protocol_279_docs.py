#!/usr/bin/env python3
from pathlib import Path
ROOT = Path(r"C:\Users\hyper\workspace")

p = ROOT / "TODO.md"
t = p.read_text(encoding="utf-8", errors="replace")
block = """
### Protocol #279 Outcomes (2026-11-05)
- 34 forward merges pushed; pi-mono dashboard branch merged + clean-room handler regression restored (build+pkg/ai tests green); _fix repos published
- [ ] 5 retained conflict branches (freellm, slsk +11, veilid, itgmania +27, sales_bot sirens +40) - Robert decision: cherry-pick / dedicated / abandon
- [ ] unitedbeats_site dashboard branch (+7) - merge after local site work is committed
"""
if "Protocol #279 Outcomes" not in t:
    lines = t.splitlines(True)
    lines.insert(4, block)
    p.write_text("".join(lines), encoding="utf-8")
print("TODO ok")

p = ROOT / "ROADMAP.md"
t = p.read_text(encoding="utf-8", errors="replace")
if "Protocol #279" not in t:
    t = t.replace("## Current Status (v5.288.0)",
                  "## Current Status (v5.288.0)\n\n**Protocol #279 (2026-11-05):** 34 forward merges pushed; pi-mono dashboard merged with handler regression restored; 5 conflict branches retained for Robert's disposition decision.", 1)
    p.write_text(t, encoding="utf-8")
print("ROADMAP ok")

p = ROOT / ".memory" / "main.md"
t = p.read_text(encoding="utf-8", errors="replace")
t = t.replace("## Current State (v5.287.0)", "## Current State (v5.288.0)")
if "- [x] v5.288.0" not in t:
    t = t.replace("- [ ] 62 GitHub vulnerabilities",
                  "- [x] v5.288.0 - Protocol #279: 36 forward merges, beatoraja master closed (+125), _fix repos published, 129/133 fetched\n- [ ] 62 GitHub vulnerabilities", 1)
    p.write_text(t, encoding="utf-8")
print("MEMORY ok")

