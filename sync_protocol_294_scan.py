#!/usr/bin/env python3
"""Protocol #281: parallel fetch + feature-branch scan across root submodules."""
import subprocess, re, json
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor, as_completed
from collections import defaultdict

ROOT = Path(r"C:\Users\hyper\workspace")
SKIP_FETCH = set()  # fetch everything; scan skips giant forks below
SCAN_SKIP = {
    "bgtk", "FFmpeg", "topaz-ffmpeg", "jdk", "llvm-project", "bdwgc",
    "browser-use", "grammars-v4", "geany", "npp", "tabby", "timidity",
    "element-web", "muse", "projectM-upstream", "stepmania", "itgmania",
    "beatoraja", "linthesia", "ksm-v2", "neverball",
}

def run(cmd, cwd, timeout=90):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception as e:
        return -2, f"TIMEOUT/ERR {e}"

def load_paths():
    gm = (ROOT / ".gitmodules").read_text(encoding="utf-8", errors="replace")
    return re.findall(r"^\s*path\s*=\s*(.+?)\s*$", gm, re.M)

def fetch_one(rel):
    p = ROOT / rel
    if not (p / ".git").exists():
        return (rel, "NOT_INIT", "")
    rc, out = run("git fetch --all --tags --prune", p, 120)
    return (rel, "OK" if rc == 0 else "FAIL", (out or "")[-300:])

def scan_repo(path_rel):
    path = ROOT / path_rel
    if not (path / ".git").exists():
        return []
    rc, out = run("git rev-parse --abbrev-ref HEAD", path, 15)
    current = out.strip()
    if not current or current == "HEAD":
        # fall back to main/master detection
        rc2, out2 = run("git branch --format=%(refname:short)", path, 15)
        local = [b.strip() for b in out2.splitlines() if b.strip()]
        current = "main" if "main" in local else ("master" if "master" in local else "main")
    rc, out = run("git for-each-ref --format=%(refname:short) refs/heads/ refs/remotes/", path, 30)
    branches = [b.strip() for b in out.splitlines() if b.strip()]
    results = []
    for br in branches:
        if br == current or br.endswith("/HEAD") or "upstream/" in br or br.startswith("remotes/upstream"):
            continue
        if br.startswith("origin/") and br[7:] in branches:
            continue
        rc_a, out_a = run(f"git rev-list --count {current}..{br}", path, 15)
        try:
            ahead = int((out_a or "0").strip() or "0")
        except ValueError:
            continue
        if ahead <= 0:
            continue
        rc_b, out_b = run(f"git rev-list --count {br}..{current}", path, 15)
        try:
            behind = int((out_b or "0").strip() or "0")
        except ValueError:
            behind = 0
        rc_s, out_s = run(f"git log --oneline {current}..{br} -5", path, 15)
        subjects = [l.strip() for l in (out_s or "").splitlines() if l.strip()][:5]
        rc_c, out_c = run(f"git cherry {current} {br}", path, 20)
        cherry_plus = sum(1 for l in (out_c or "").splitlines() if l.startswith("+"))
        results.append({"repo": path_rel, "branch": br, "current": current,
                        "ahead": ahead, "behind": behind, "cherry_plus": cherry_plus,
                        "subjects": subjects})
    return results

def main():
    paths = load_paths()
    print(f"Submodules in .gitmodules: {len(paths)}", flush=True)
    fetch_results = []
    with ThreadPoolExecutor(max_workers=8) as ex:
        futs = {ex.submit(fetch_one, p): p for p in paths}
        for i, f in enumerate(as_completed(futs), 1):
            rel, st, tail = f.result()
            fetch_results.append({"path": rel, "status": st, "tail": tail})
            if st != "OK":
                print(f"[fetch {i}/{len(paths)}] {rel}: {st}", flush=True)
    ok = sum(1 for r in fetch_results if r["status"] == "OK")
    print(f"FETCH SUMMARY: {ok}/{len(paths)} OK", flush=True)
    (ROOT / "sync_protocol_294_fetch.json").write_text(json.dumps(fetch_results, indent=2), encoding="utf-8")

    all_features = []
    for p in paths:
        base = p.split("/")[0]
        if base in SCAN_SKIP or p in SCAN_SKIP:
            continue
        feats = scan_repo(p)
        all_features.extend(feats)
        if feats:
            print(f"[scan] {p}: {len(feats)}", flush=True)
    print(f"\n=== TOTAL feature branches with unique commits: {len(all_features)} ===", flush=True)
    by_repo = defaultdict(list)
    for f in all_features:
        by_repo[f["repo"]].append(f)
    for repo in sorted(by_repo):
        for f in sorted(by_repo[repo], key=lambda x: -x["ahead"]):
            print(f"  {repo} :: {f['branch']} [{f['ahead']} ahead, {f['behind']} behind, cherry+ {f['cherry_plus']}]", flush=True)
    (ROOT / "sync_protocol_294_features.json").write_text(json.dumps(all_features, indent=2), encoding="utf-8")
    print("Saved sync_protocol_294_features.json", flush=True)

if __name__ == "__main__":
    main()





