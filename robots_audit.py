#!/usr/bin/env python3
"""Find indexable pages that our own robots.txt is blocking.

Google Search Console says "Blocked by robots.txt". The definitive test is to
take every URL the site advertises in its sitemaps and run it through the
robots.txt rules exactly the way Google's crawler does (longest-match wins,
`*` wildcard, `$` end-anchor, User-agent groups). Whatever a sitemap lists but
robots.txt blocks is a real self-inflicted conflict.

Usage:  python robots_audit.py [site ...]      (default: known sites)
"""

import io
import re
import sys
import urllib.error
import urllib.request

# console output may be cp1252 on Windows and these transcripts are not
if isinstance(sys.stdout, io.TextIOWrapper):
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")

UA = "Mozilla/5.0 (robots-audit; +https://example.invalid)"
SITES = ["robertpelloni.com", "aimoneymachine.site", "unitedbeats.org"]


def fetch(url, timeout=25):
    req = urllib.request.Request(url, headers={"User-Agent": UA})
    with urllib.request.urlopen(req, timeout=timeout) as resp:
        return resp.status, resp.read().decode("utf-8", "replace")


# ---------------------------------------------------------------- robots.txt

def parse_robots(text):
    """Return {user_agent: [rules]}, each rule (allow_bool, pattern)."""
    groups = {}
    agents, rules, last_was_agent = [], [], False
    for raw in text.splitlines():
        line = raw.split("#", 1)[0].strip()
        if not line:
            continue
        if ":" not in line:
            continue
        field, _, value = line.partition(":")
        field, value = field.strip().lower(), value.strip()

        if field == "user-agent":
            if not last_was_agent and (agents or rules):
                for a in agents:
                    groups.setdefault(a.lower(), []).extend(rules)
                agents, rules = [], []
            agents.append(value)
            last_was_agent = True
        elif field in ("allow", "disallow"):
            if not agents:
                continue
            rules.append((field == "allow", value))
            last_was_agent = False
    for a in agents:
        groups.setdefault(a.lower(), []).extend(rules)
    return groups


def rule_matches(pattern, path):
    """Google-style match; returns specificity (len of literal parts) or -1."""
    if pattern == "":
        return -1
    p = pattern
    end_anchor = p.endswith("$")
    if end_anchor:
        p = p[:-1]
    # escape everything, then restore * and ?
    rx = re.escape(p).replace(r"\*", ".*")
    rx = "^" + rx + ("$" if end_anchor else "")
    if re.match(rx, path):
        return len(pattern.replace("*", "").replace("$", ""))
    return -1


def is_allowed(groups, path):
    """Return (allowed, reason) using longest-match precedence."""
    rules = groups.get("googlebot") or groups.get("*") or []
    if not rules:
        return True, "no rules"
    best_spec, best_allow, best_pat = -1, True, "(none)"
    for allow, pat in rules:
        spec = rule_matches(pat, path)
        if spec < 0:
            continue
        if spec > best_spec or (spec == best_spec and allow and not best_allow):
            best_spec, best_allow, best_pat = spec, allow, pat
    if best_spec < 0:
        return True, "no matching rule"
    return best_allow, f"{'Allow' if best_allow else 'Disallow'}: {best_pat}"


# ------------------------------------------------------------------ sitemaps

def sitemap_urls(root, depth=0, seen=None):
    if seen is None:
        seen = set()
    if root in seen or depth > 3:
        return []
    seen.add(root)
    try:
        _, body = fetch(root)
    except (urllib.error.URLError, OSError) as exc:
        print(f"    ! cannot fetch {root}: {exc}")
        return []

    locs = re.findall(r"<loc>\s*([^<\s]+)\s*</loc>", body)
    if "<sitemapindex" in body:
        out = []
        for loc in locs:
            out.extend(sitemap_urls(loc, depth + 1, seen))
        return out
    return locs


def main():
    sites = sys.argv[1:] or SITES
    for site in sites:
        print("=" * 78)
        print(f"SITE: {site}")
        print("=" * 78)

        try:
            _, robots = fetch(f"https://{site}/robots.txt")
        except (urllib.error.HTTPError, urllib.error.URLError, OSError) as exc:
            print(f"  robots.txt: NOT SERVED ({exc})  -> everything is crawlable")
            print()
            continue

        groups = parse_robots(robots)
        print(f"  robots.txt user-agents: {', '.join(groups) or '(none)'}")
        for a, rl in groups.items():
            print(f"    [{a}]")
            for allow, pat in rl:
                print(f"       {'Allow' if allow else 'Disallow'}: {pat}")

        sm = re.search(r"(?im)^\s*Sitemap:\s*(\S+)", robots)
        roots = [sm.group(1)] if sm else [f"https://{site}/wp-sitemap.xml",
                                          f"https://{site}/sitemap_index.xml"]
        print(f"\n  sitemaps: {', '.join(roots)}")

        urls = []
        for root in roots:
            urls.extend(sitemap_urls(root))
        urls = list(dict.fromkeys(urls))
        print(f"  sitemap URLs found: {len(urls)}")

        if not urls:
            print("  (no sitemap URLs — cannot cross-check)")
            print()
            continue

        blocked = []
        for u in urls:
            m = re.match(r"https?://[^/]+(/.*)?$", u)
            path = m.group(1) if m and m.group(1) else "/"
            allowed, why = is_allowed(groups, path)
            if not allowed:
                blocked.append((u, why))

        print(f"\n  >>> INDEXABLE URLS BLOCKED BY robots.txt: {len(blocked)}")
        for u, why in blocked[:40]:
            print(f"      {u}\n          by  {why}")
        if len(blocked) > 40:
            print(f"      ... and {len(blocked)-40} more")
        if not blocked:
            print("      none — the sitemap and robots.txt agree")

        # which patterns are doing the damage
        if blocked:
            tally = {}
            for _, why in blocked:
                tally[why] = tally.get(why, 0) + 1
            print("\n  culprits:")
            for why, n in sorted(tally.items(), key=lambda kv: -kv[1]):
                print(f"      {n:5d}x  {why}")
        print()


if __name__ == "__main__":
    main()
