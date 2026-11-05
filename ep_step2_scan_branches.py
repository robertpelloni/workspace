#!/usr/bin/env python3
"""EP Step 2: Scan own repos for unmerged feature branches. Skips giant third-party forks."""
import subprocess, re, json
from pathlib import Path
from collections import defaultdict

ROOT = Path(r"C:\Users\hyper\workspace")

# Giant third-party forks to skip entirely (protocol: ignore upstream feature branches)
SKIP_REPOS = {
    "bgtk", "FFmpeg", "topaz-ffmpeg", "jdk", "llvm-project", "bdwgc",
    "browser-use", "grammars-v4", "geany", "npp", "tabby", "timidity",
    "element-web", "muse", "projectM-upstream", "stepmania", "itgmania",
    "beatoraja", "linthesia", "ksm-v2", "neverball", "MarbleBlast",
    "OpenMBU", "sm64coopdx", "mk64", "f-zerox", "ArrowVortex",
}

IGNORE_REF = [
    r"upstream/", r"origin/dependabot/", r"gh-pages",
    r"remotes/upstream/", r"remotes/origin/dependabot/",
    r"HEAD",
]

def run(cmd, cwd, timeout=30):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception:
        return -2, "TIMEOUT"

def load_paths():
    gm = (ROOT / ".gitmodules").read_text(encoding="utf-8", errors="replace")
    return re.findall(r"^\s*path\s*=\s*(.+?)\s*$", gm, re.M)

def is_ignored(ref):
    return any(re.search(p, ref) for p in IGNORE_REF)

def scan_repo(path_rel):
    path = ROOT / path_rel
    if not (path / ".git").exists():
        return []
    rc, out = run("git rev-parse --abbrev-ref HEAD", path, 15)
    current = out.strip()
    if not current or current == "HEAD":
        current = "main"
    rc, out = run("git for-each-ref --format='%(refname:short)' refs/heads/ refs/remotes/", path, 30)
    branches = [b.strip() for b in out.splitlines() if b.strip()]
    results = []
    for br in branches:
        if is_ignored(br) or br == current:
            continue
        # Normalize: prefer local over remote tracking duplicates
        if br.startswith("origin/") and br[7:] in [b for b in branches if not b.startswith("origin/")]:
            continue
        rc_a, out_a = run(f'git rev-list --count {current}..{br}', path, 15)
        try:
            ahead = int((out_a or "0").strip() or "0")
        except ValueError:
            continue
        if ahead <= 0:
            continue
        rc_b, out_b = run(f'git rev-list --count {br}..{current}', path, 15)
        try:
            behind = int((out_b or "0").strip() or "0")
        except ValueError:
            behind = 0
        rc_s, out_s = run(f'git log --oneline {current}..{br} -5', path, 15)
        subjects = [l.strip() for l in (out_s or "").splitlines() if l.strip()][:5]
        results.append({
            "repo": path_rel,
            "branch": br,
            "current": current,
            "ahead": ahead,
            "behind": behind,
            "subjects": subjects,
        })
    return results

def main():
    paths = load_paths()
    all_repos = ["."] + paths
    all_features = []
    scanned = 0
    for p in all_repos:
        name = p if p != "." else "(root)"
        base = name.split("/")[0] if "/" in name else name
        if base in SKIP_REPOS or name in SKIP_REPOS:
            print(f"[skip] {name}", flush=True)
            continue
        scanned += 1
        print(f"[{scanned}] {name} ...", end=" ", flush=True)
        feats = scan_repo(p)
        if feats:
            print(f"{len(feats)} feature branches", flush=True)
            all_features.extend(feats)
        else:
            print("clean", flush=True)

    print(f"\n=== TOTAL: {len(all_features)} feature branches with unique commits (scanned {scanned} repos) ===\n", flush=True)
    by_repo = defaultdict(list)
    for f in all_features:
        by_repo[f["repo"]].append(f)
    for repo in sorted(by_repo.keys()):
        print(f"\n## {repo}", flush=True)
        for f in sorted(by_repo[repo], key=lambda x: -x["ahead"]):
            print(f"  [{f['ahead']} ahead, {f['behind']} behind] {f['branch']}", flush=True)
            for s in f["subjects"][:3]:
                print(f"      {s}", flush=True)

    out_path = ROOT / "ep_step2_features.json"
    out_path.write_text(json.dumps(all_features, indent=2), encoding="utf-8")
    print(f"\nSaved to {out_path}", flush=True)

if __name__ == "__main__":
    main()
