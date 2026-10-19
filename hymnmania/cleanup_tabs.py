"""Close stale CDP browser tabs so the social browser does not choke.

WHY: every social run leaves its tabs open. By 2026-09-16 the port-9222 browser had
**237 tabs / 81 msedge processes**, and `BrowserType.connect_over_cdp` began timing out
after 180 s even though /json/version still answered - i.e. the browser was up but too
clogged to drive. That silently broke every TikTok / FB Reel / IG post.

Keeps one tab per port. Run it before social posting, and it is called automatically by
scheduler_v2's ensure_browser().

    python cleanup_tabs.py            # both ports
    python cleanup_tabs.py 9222       # one port
"""
import json, sys, time, urllib.request

PORTS = [9222]   # social browser only - 9333 tabs are managed by cap_cycle.py,
                 # and pruning it too hard left that browser unreachable (2026-09-16).

def tabs(port):
    d = json.load(urllib.request.urlopen(f"http://127.0.0.1:{port}/json/list", timeout=8))
    return d


def clean(port, keep=2, rounds=3, verbose=True):
    """Close everything but `keep` pages. Returns (before, after)."""
    before = None
    for _ in range(rounds):
        try:
            d = tabs(port)
        except Exception as e:
            if verbose:
                print(f"  {port}: unreachable ({e})")
            return before, None
        if before is None:
            before = len(d)
        pages = [t for t in d if t.get("type") == "page"]
        keep_ids = {t["id"] for t in pages[:keep]}
        closed = 0
        for t in d:
            if t["id"] in keep_ids:
                continue
            try:
                urllib.request.urlopen(f"http://127.0.0.1:{port}/json/close/{t['id']}", timeout=3)
                closed += 1
            except Exception:
                pass
        if verbose:
            print(f"  {port}: closed {closed}")
        if closed == 0:
            break
        time.sleep(3)
    try:
        after = len(tabs(port))
    except Exception:
        after = None
    if verbose:
        print(f"  {port}: {before} -> {after} entries")
    return before, after


if __name__ == "__main__":
    ports = [int(a) for a in sys.argv[1:] if a.isdigit()] or PORTS
    for p in ports:
        clean(p)
