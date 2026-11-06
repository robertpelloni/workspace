#!/usr/bin/env python3
"""Protocol #279: regenerate STRUCTURAL_MAP.md (table format) with current submodule HEADs."""
import re, subprocess
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")
gm = (ROOT / ".gitmodules").read_text(encoding="utf-8", errors="replace")
paths = re.findall(r"^\s*path\s*=\s*(.+?)\s*$", gm, re.M)
urls = {}
for m in re.finditer(r'\[submodule "[^"]+"\]\s*\n\s*path\s*=\s*(.+?)\s*\n\s*url\s*=\s*(.+?)\s*$', gm, re.M):
    urls[m.group(1).strip()] = m.group(2).strip()

lines = ["# STRUCTURAL MAP - Submodules", "",
         "Generated: 2026-11-05 (Protocol #279, full regen)", "",
         "| Submodule | Remote URL | Commit |", "|---|---|---|"]
init = 0
for p in paths:
    url = urls.get(p, "N/A")
    try:
        r = subprocess.run(["git", "rev-parse", "HEAD"], cwd=str(ROOT / p),
                           capture_output=True, text=True, timeout=15)
        commit = r.stdout.strip()[:12] if r.returncode == 0 and r.stdout.strip() else "not initialized"
    except Exception:
        commit = "not initialized"
    if commit != "not initialized":
        init += 1
    lines.append(f"| {p} | {url} | {commit} |")
lines += ["", f"Initialized: {init}/{len(paths)}"]
(ROOT / "STRUCTURAL_MAP.md").write_text("\n".join(lines), encoding="utf-8")
print(f"MAP DONE {init}/{len(paths)}")


