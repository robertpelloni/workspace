#!/usr/bin/env python3
"""Protocol #278 final verify: list branches still holding unique (cherry+) work vs local default."""
import subprocess, json
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")
SKIP_REPOS = {"openclaw-config", "HyperNexus2old", "HyperNexus", "unitedbeats_site"}

def run(cmd, cwd, timeout=30):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception:
        return -2, "TIMEOUT"

def main():
    triage = json.loads((ROOT / "sync_protocol_278_triage.json").read_text(encoding="utf-8"))
    remaining = []
    for r in triage:
        rel, default = r["repo"], r.get("default")
        if not default or rel in SKIP_REPOS:
            continue
        path = ROOT / rel
        if not (path / ".git").exists():
            continue
        for f in r.get("features", []):
            br = f["branch"]
            if any(s in br for s in ["heads/upstream/", "upstream/", "gh-pages", "cloud-dashboard"]):
                continue
            if rel == "bobeditpro" and br == "main":
                continue
            rc, out = run(f"git cherry {default} {br}", path, 30)
            plus = sum(1 for l in out.splitlines() if l.startswith("+"))
            if plus > 0:
                remaining.append({"repo": rel, "branch": br, "cherry_plus": plus})
                print(f"UNMERGED {rel} {br} cherry+{plus}", flush=True)
    (ROOT / "sync_protocol_278_remaining.json").write_text(json.dumps(remaining, indent=2), encoding="utf-8")
    print(f"\nREMAINING UNMERGED: {len(remaining)}", flush=True)

if __name__ == "__main__":
    main()

