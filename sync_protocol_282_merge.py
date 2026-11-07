#!/usr/bin/env python3
"""Protocol #282 executor: Phase A fast-forward stale defaults; Phase B forward-merge features; Phase C reverse-merge leftovers.
Exclusions: upstream mirrors (hermes heads/upstream, fwber heads/upstream), deferred orphans (HyperNexus cloud-dashboard, HyperNexus2old), openclaw-config (push denied, local-ahead), bobeditpro main (Audacity upstream).
"""
import subprocess, json
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")
SKIP_REPOS = {"openclaw-config", "HyperNexus2old", "HyperNexus", "hypercode", "ArrowVortex"}
SKIP_BRANCH_SUBSTR = ["heads/upstream/", "upstream/", "gh-pages", "cloud-dashboard-mcp-sse", "backup/", "freellm-linux", "clean-freellm", "jules-12512815185672744343"]

def run(cmd, cwd, timeout=180):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception as e:
        return -2, f"TIMEOUT {e}"

def is_clean(path):
    rc, out = run("git status --porcelain -uno", path, 30)
    return rc == 0 and not out.strip()

def current_branch(path):
    rc, out = run("git rev-parse --abbrev-ref HEAD", path, 15)
    return out.strip()

def main():
    triage = json.loads((ROOT / "sync_protocol_282_triage.json").read_text(encoding="utf-8"))
    log = []

    # Phase A: fast-forward behind-only defaults
    for r in triage:
        rel, default, ff = r["repo"], r.get("default"), r.get("ff") or ""
        if not default or rel in SKIP_REPOS:
            continue
        path = ROOT / rel
        if not (path / ".git").exists():
            continue
        if "0 ahead" not in ff or "behind origin" not in ff:
            continue
        behind = 0
        try:
            behind = int(ff.split("behind")[0].strip().split()[-1])
        except Exception:
            pass
        if behind <= 0:
            continue
        if not is_clean(path):
            log.append({"repo": rel, "phase": "FF", "action": "defer-dirty", "ff": ff})
            print(f"FF DEFER-DIRTY {rel} ({ff})", flush=True)
            continue
        cur = current_branch(path)
        if cur != default:
            rc, out = run(f"git checkout {default}", path, 60)
            if rc != 0:
                log.append({"repo": rel, "phase": "FF", "action": "fail-checkout", "detail": out[-200:]})
                print(f"FF FAIL-CHECKOUT {rel}", flush=True)
                continue
        rc, out = run(f"git merge --ff-only origin/{default}", path, 120)
        act = "ff-ok" if rc == 0 else "ff-fail"
        log.append({"repo": rel, "phase": "FF", "action": act, "ff": ff})
        print(f"FF {act.upper()} {rel} ({ff})", flush=True)

    # Phase B: forward merges (smallest cherry+ first per repo for maturity order)
    for r in triage:
        rel, default = r["repo"], r.get("default")
        if not default or rel in SKIP_REPOS:
            continue
        feats = [f for f in r.get("features", [])
                 if not any(s in f["branch"] for s in SKIP_BRANCH_SUBSTR)
                 and not (rel == "bobeditpro" and f["branch"] == "main")]
        if not feats:
            continue
        path = ROOT / rel
        if not (path / ".git").exists():
            continue
        for f in sorted(feats, key=lambda x: x["cherry_plus"]):
            br = f["branch"]
            if not is_clean(path):
                log.append({"repo": rel, "phase": "MERGE", "branch": br, "action": "defer-dirty"})
                print(f"MERGE DEFER-DIRTY {rel} {br}", flush=True)
                continue
            if current_branch(path) != default:
                rc, out = run(f"git checkout {default}", path, 60)
                if rc != 0:
                    log.append({"repo": rel, "phase": "MERGE", "branch": br, "action": "fail-checkout"})
                    print(f"MERGE FAIL-CHECKOUT {rel} {br}", flush=True)
                    continue
            rc, out = run(f"git merge --no-ff {br} -m \"merge: {br} into {default} (Protocol #282)\"", path, 240)
            if rc == 0:
                rc2, out2 = run(f"git push origin {default}", path, 180)
                act = "merged+pushed" if rc2 == 0 else "merged-push-fail"
                log.append({"repo": rel, "phase": "MERGE", "branch": br, "action": act,
                            "cherry_plus": f["cherry_plus"], "detail": (out2[-200:] if rc2 != 0 else "")})
                print(f"MERGE {act.upper()} {rel} {br}", flush=True)
            else:
                run("git merge --abort", path, 30)
                log.append({"repo": rel, "phase": "MERGE", "branch": br, "action": "conflict-aborted",
                            "cherry_plus": f["cherry_plus"], "behind": f["behind"]})
                print(f"MERGE CONFLICT {rel} {br} (retained)", flush=True)

    # Phase C: reverse-merge updated default into conflicted/local branches with substantial unique work
    merged_repos = {e["repo"] for e in log if e["phase"] == "MERGE" and e["action"].startswith("merged")}
    for e in list(log):
        if e["phase"] != "MERGE" or e["action"] != "conflict-aborted":
            continue
        if (e.get("cherry_plus") or 0) < 10:
            continue
        rel, br = e["repo"], e["branch"]
        path = ROOT / rel
        default = next((r.get("default") for r in triage if r["repo"] == rel), None)
        if not default or not is_clean(path):
            continue
        local_br = br[7:] if br.startswith("origin/") else br
        if br.startswith("origin/"):
            rc, out = run(f"git checkout -B {local_br} {br}", path, 60)
        else:
            rc, out = run(f"git checkout {local_br}", path, 60)
        if rc != 0:
            e["reverse"] = "fail-checkout"
            continue
        rc, out = run(f"git merge --no-ff {default} -m \"merge: {default} back into {local_br} (Protocol #282 reverse)\"", path, 240)
        if rc == 0:
            rc2, _ = run(f"git push origin {local_br}", path, 180)
            e["reverse"] = "reverse-merged+pushed" if rc2 == 0 else "reverse-merged-push-fail"
        else:
            run("git merge --abort", path, 30)
            e["reverse"] = "reverse-conflict-aborted"
        run(f"git checkout {default}", path, 60)
        print(f"REVERSE {e['reverse']} {rel} {local_br}", flush=True)

    (ROOT / "sync_protocol_282_merge_results.json").write_text(json.dumps(log, indent=2), encoding="utf-8")
    m = [e for e in log if e["phase"] == "MERGE" and e["action"].startswith("merged")]
    ff = [e for e in log if e["phase"] == "FF" and e["action"] == "ff-ok"]
    print(f"\nSUMMARY: {len(ff)} fast-forwards, {len(m)} forward merges", flush=True)

if __name__ == "__main__":
    main()



