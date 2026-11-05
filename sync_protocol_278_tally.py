#!/usr/bin/env python3
import json
from pathlib import Path
ROOT = Path(r"C:\Users\hyper\workspace")
merged = []
for f in ["sync_protocol_278_merge_results.json", "sync_protocol_278_phase2_results.json", "sync_protocol_278_final_results.json"]:
    for e in json.loads((ROOT / f).read_text(encoding="utf-8")):
        if e.get("action", "").startswith("merged"):
            merged.append(f"{e['repo']}: {e.get('branch','')}")
print(f"FORWARD MERGES (incl. -X theirs): {len(merged)}")
for m in merged:
    print(" -", m)
rem = json.loads((ROOT / "sync_protocol_278_remaining.json").read_text(encoding="utf-8"))
fin = json.loads((ROOT / "sync_protocol_278_final_results.json").read_text(encoding="utf-8"))
still = [e for e in fin if e["action"] == "conflict-final"]
print(f"\nSTILL CONFLICTED (retained): {len(still)}")
for e in still:
    print(" -", e["repo"], e["branch"])

