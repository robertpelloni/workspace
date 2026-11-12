#!/usr/bin/env python3
from pathlib import Path
ROOT = Path(r"C:\Users\hyper\workspace")

# TODO: insert block preserving original bytes/newlines
p = ROOT / "TODO.md"
data = p.read_bytes()
text = data.decode("utf-8", errors="replace")
if "Protocol #283 Outcomes" not in text:
    nl = "\r\n" if "\r\n" in text else "\n"
    block_lines = [
        "",
        "### Protocol #283 Outcomes (2026-11-07)",
        "- 42 forward merges pushed, 28 fast-forwards, 65 submodule pointers staged; root FF to origin #282 (v5.291.0) then bumped to v5.292.0",
        "- [ ] 5 retained conflict branches (freellm temp-main +2, veilid scaffold +17, itgmania jules-1251 +27, bobfilez backup +1, hyperporn backup +2) - Robert decision: cherry-pick / dedicated / abandon",
        "- [ ] Repair system Git (mingw64 tree incomplete) - GitHub Desktop git is the working fallback",
        "- [ ] unitedbeats_site dashboard branch - merge after local site work is committed",
        "",
    ]
    block = nl.join(block_lines)
    lines = text.splitlines(True)
    lines.insert(4, block)
    p.write_bytes("".join(lines).encode("utf-8"))
print("TODO ok")

# CHANGELOG: move v5.292 block above v5.291 header
p = ROOT / "CHANGELOG.md"
text = p.read_text(encoding="utf-8", errors="replace")
start = text.find("## [v5.292.0]")
end = text.find("### Synced", start)
# block = from start to the blank line before '### Retained' section end: find next '## [' after start
nxt = text.find("\n## [", start + 10)
if start > 0 and nxt > start:
    block = text[start:nxt].rstrip() + "\n"
    rest = text[:start].rstrip() + "\n" + text[nxt + 1:]
    # rest currently begins with v5.291 header line (first line) - put block first
    p.write_text(block + "\n" + rest.lstrip("\n"), encoding="utf-8")
    print("CHANGELOG reordered")
else:
    print(f"CHANGELOG reorder skipped start={start} nxt={nxt}")
print("FIX DONE")
