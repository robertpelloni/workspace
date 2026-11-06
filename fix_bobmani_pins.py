#!/usr/bin/env python3
"""Recursive stale-pin audit+fix for bobmani tree (all nesting levels). Inner repos first, then bobmani, report heads."""
import subprocess, json, tempfile, shutil
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor, as_completed

ROOT = Path(r"C:\Users\hyper\workspace")
BOB = ROOT / "bobmani"

def run(cmd, cwd=None, timeout=180):
    try:
        p = subprocess.run(cmd, cwd=str(cwd) if cwd else None, capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception as e:
        return -2, f"TIMEOUT {e}"

def find_repos(base, maxdepth=3):
    repos = [base]
    def walk(d, depth):
        if depth > maxdepth:
            return
        for child in sorted(d.iterdir()):
            if not child.is_dir() or child.name == ".git":
                continue
            if (child / ".git").exists():
                repos.append(child)
            walk(child, depth + 1)
    walk(base, 1)
    return repos

def gitlinks(path):
    rc, out = run("git ls-tree -r HEAD", path, 60)
    links = []
    for line in out.splitlines():
        meta, _, p = line.partition("\t")
        parts = meta.split()
        if len(parts) >= 3 and parts[0] == "160000":
            links.append((p.strip(), parts[2]))
    return links

def urls_for(path):
    rc, cfg = run("git config --file .gitmodules --list", path, 30)
    entries = {}
    for line in cfg.splitlines():
        if "=" not in line:
            continue
        k, v = line.split("=", 1)
        kp = k.split(".")
        if len(kp) >= 3 and kp[0] == "submodule":
            entries.setdefault(".".join(kp[1:-1]), {})[kp[-1]] = v.strip()
    urls = {}
    for e in entries.values():
        if "path" in e and "url" in e:
            u = e["url"]
            if u.startswith("git@github.com:"):
                u = "https://github.com/" + u[len("git@github.com:"):]
            urls[e["path"]] = u
    return urls, entries

def resolve_relative(url, parent_path):
    if url.startswith("../"):
        rc, origin_url = run("git remote get-url origin", parent_path, 15)
        origin_url = origin_url.strip()
        if origin_url.startswith("git@github.com:"):
            origin_url = "https://github.com/" + origin_url[len("git@github.com:"):]
        if "github.com/" in origin_url:
            return origin_url.rsplit("/", 1)[0] + "/" + url[3:]
    return url

def check_url(url, shas):
    tmp = Path(tempfile.mkdtemp(prefix="bmpin_"))
    try:
        rc, out = run(f"git clone --bare --filter=blob:none --no-checkout {url} repo", tmp, 300)
        if rc != 0:
            return {s: "DEAD" for s in shas}, ""
        repo = tmp / "repo"
        rc, tip = run("git rev-parse HEAD", repo, 30)
        tip = tip.strip()
        res = {}
        for s in shas:
            rc1, _ = run(f"git cat-file -t {s}", repo, 30)
            if rc1 != 0:
                res[s] = "MISSING"
                continue
            rc2, _ = run(f"git merge-base --is-ancestor {s} HEAD", repo, 30)
            res[s] = "OK" if rc2 == 0 else "UNREACHABLE"
        return res, tip
    finally:
        shutil.rmtree(tmp, ignore_errors=True)

def default_branch(path):
    rc, out = run("git symbolic-ref refs/remotes/origin/HEAD", path, 15)
    ref = out.strip()
    if ref.startswith("refs/remotes/origin/"):
        return ref[len("refs/remotes/origin/"):]
    for cand in ("main", "master", "release"):
        rc, _ = run(f"git rev-parse --verify origin/{cand}", path, 15)
        if rc == 0:
            return cand
    return "main"

def remove_section(path, subpath, entries):
    for name, e in entries.items():
        if e.get("path") == subpath:
            run(f"git config --file .gitmodules --remove-section submodule.{name}", path, 30)
            return name
    return None

def main():
    repos = find_repos(BOB)
    print(f"repos in tree: {[str(r.relative_to(ROOT)) for r in repos]}", flush=True)
    items = []  # (repo_path, sub, sha, url, entries)
    url_shas = {}
    repo_info = {}
    for rp in repos:
        links = gitlinks(rp)
        if not links:
            continue
        urls, entries = urls_for(rp)
        repo_info[str(rp)] = entries
        for sub, sha in links:
            url = resolve_relative(urls.get(sub, ""), rp)
            items.append((rp, sub, sha, url))
            if url:
                url_shas.setdefault(url, set()).add(sha)
    print(f"gitlinks: {len(items)}, urls: {len(url_shas)}", flush=True)
    results = {}
    with ThreadPoolExecutor(max_workers=8) as ex:
        futs = {ex.submit(check_url, u, sorted(s)): u for u, s in url_shas.items()}
        for f in as_completed(futs):
            u = futs[f]
            results[u] = f.result()
    fixes = {}
    for rp, sub, sha, url in items:
        if not url:
            print(f"NO_URL {rp.relative_to(ROOT)} :: {sub}", flush=True)
            continue
        res, tip = results.get(url, ({}, ""))
        st = res.get(sha, "UNKNOWN")
        if st != "OK":
            fixes.setdefault(str(rp), []).append((sub, sha, tip, st, url))
            print(f"BAD {rp.relative_to(ROOT)} :: {sub} {st} pin {sha[:12]} tip {tip[:12]}", flush=True)
    # Apply deepest repos first
    new_heads = {}
    for rp_str in sorted(fixes.keys(), key=lambda s: -s.count("\\")):
        rp = Path(rp_str)
        branch = default_branch(rp)
        rc, cur = run("git rev-parse --abbrev-ref HEAD", rp, 15)
        if cur.strip() != branch:
            rc, out = run(f"git checkout {branch}", rp, 60)
            if rc != 0:
                print(f"CHECKOUT_FAIL {rp.relative_to(ROOT)} {branch}: {out[-150:]}", flush=True)
                continue
        entries = repo_info.get(rp_str, {})
        for sub, sha, tip, st, url in fixes[rp_str]:
            if st == "DEAD":
                run(f"git update-index --force-remove -- {sub}", rp, 30)
                remove_section(rp, sub, entries)
                run("git add .gitmodules", rp, 30)
                print(f"REMOVED DEAD {rp.relative_to(ROOT)} :: {sub}", flush=True)
            else:
                run(f"git update-index --cacheinfo 160000,{tip},{sub}", rp, 30)
                print(f"REPIN {rp.relative_to(ROOT)} :: {sub} -> {tip[:12]}", flush=True)
        rc, out = run('git commit --no-verify -m "fix: re-pin submodules to published commits (Jules recursive clone)"', rp, 120)
        if rc != 0:
            print(f"COMMIT_FAIL {rp.relative_to(ROOT)}: {out[-200:]}", flush=True)
            continue
        rc, out = run(f"git push origin {branch}", rp, 240)
        rc2, head = run("git rev-parse HEAD", rp, 15)
        new_heads[rp_str] = head.strip()
        print(f"{'PUSHED' if rc==0 else 'PUSH_FAIL'} {rp.relative_to(ROOT)} {branch} {head.strip()[:12]} {out[-150:] if rc!=0 else ''}", flush=True)
    (ROOT / "fix_bobmani_results.json").write_text(json.dumps(new_heads, indent=2), encoding="utf-8")
    print("BOBMANI_FIX_DONE", flush=True)

if __name__ == "__main__":
    main()
