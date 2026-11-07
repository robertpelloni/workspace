#!/usr/bin/env python3
"""Protocol #282 triage v2: compare branches against ORIGIN default (not stale local HEAD).
Classifies: FF (local default behind origin), FEATURE (unique work vs origin default), DEPENDABOT, SKIP.
"""
import subprocess, re, json
from pathlib import Path
from collections import defaultdict

ROOT = Path(r"C:\Users\hyper\workspace")
# Third-party forks / upstream-mirrored: ignore their upstream feature branches per protocol
SKIP_REPOS = {
    "bgtk", "FFmpeg", "topaz-ffmpeg", "jdk", "llvm-project", "bdwgc",
    "browser-use", "grammars-v4", "geany", "npp", "tabby", "timidity",
    "element-web", "muse", "projectM-upstream", "stepmania", "itgmania",
    "beatoraja", "warp", "hyper", "CodeWhale-Extensions",
}

def run(cmd, cwd, timeout=60):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception:
        return -2, "TIMEOUT"

def load_paths():
    gm = (ROOT / ".gitmodules").read_text(encoding="utf-8", errors="replace")
    return re.findall(r"^\s*path\s*=\s*(.+?)\s*$", gm, re.M)

def origin_default(path):
    rc, out = run("git symbolic-ref refs/remotes/origin/HEAD", path, 15)
    ref = out.strip()
    if ref.startswith("refs/remotes/origin/"):
        return ref[len("refs/remotes/origin/"):]
    for cand in ("main", "master"):
        rc, _ = run(f"git rev-parse --verify origin/{cand}", path, 15)
        if rc == 0:
            return cand
    return None

def triage_repo(rel):
    path = ROOT / rel
    if not (path / ".git").exists():
        return {"repo": rel, "status": "NOT_INIT", "features": []}
    default = origin_default(path)
    if not default:
        return {"repo": rel, "status": "NO_ORIGIN_DEFAULT", "features": []}
    oref = f"origin/{default}"
    # local default divergence
    rc, out = run(f"git rev-list --left-right --count {default}...{oref}", path, 20)
    ff = ""
    try:
        a, b = out.split()
        ff = f"local {default}: {a} ahead / {b} behind origin"
    except Exception:
        pass
    rc, out = run("git for-each-ref --format=%(refname:short) refs/heads/ refs/remotes/origin/", path, 30)
    branches = [b.strip() for b in out.splitlines() if b.strip()]
    feats = []
    for br in branches:
        if br in (default, oref, "origin", "origin/HEAD") or br.endswith("/HEAD"):
            continue
        if "/gh-pages" in br or br.endswith("gh-pages"):
            continue
        if br.startswith("origin/") and br[7:] in branches:
            continue
        rc_a, out_a = run(f"git rev-list --count {oref}..{br}", path, 20)
        try:
            ahead = int((out_a or "0").strip() or "0")
        except ValueError:
            continue
        if ahead <= 0:
            continue
        rc_c, out_c = run(f"git cherry {oref} {br}", path, 30)
        cherry_plus = sum(1 for l in (out_c or "").splitlines() if l.startswith("+"))
        if cherry_plus <= 0:
            continue
        rc_b, out_b = run(f"git rev-list --count {br}..{oref}", path, 20)
        try:
            behind = int((out_b or "0").strip() or "0")
        except ValueError:
            behind = 0
        kind = "dependabot" if "dependabot" in br else "feature"
        feats.append({"branch": br, "ahead": ahead, "behind": behind,
                      "cherry_plus": cherry_plus, "kind": kind})
    return {"repo": rel, "status": "OK", "default": default, "ff": ff, "features": feats}

def main():
    paths = load_paths()
    results = []
    for p in paths:
        base = p.split("/")[0]
        if base in SKIP_REPOS or p in SKIP_REPOS:
            continue
        r = triage_repo(p)
        results.append(r)
        if r.get("features"):
            print(f"{p} (default {r.get('default')}, {r.get('ff')}): {len(r['features'])} actionable", flush=True)
            for f in r["features"]:
                print(f"    [{f['kind']}] {f['branch']} +{f['ahead']}/-{f['behind']} cherry+{f['cherry_plus']}", flush=True)
    (ROOT / "sync_protocol_282_triage.json").write_text(json.dumps(results, indent=2), encoding="utf-8")
    total = sum(len(r.get("features", [])) for r in results)
    print(f"\nTRIAGE TOTAL actionable: {total}", flush=True)

if __name__ == "__main__":
    main()



