#!/usr/bin/env python3
"""List every 'LLM waterfall' / 'local-first' style mention with context.

These are being pulled from the marketing copy, so the point of this is to see
exactly which bullets, table rows and meta lines carry them before editing -
some are list items that must be removed whole, not just reworded.
"""

import glob
import html
import re

ROOTS = [
    "/var/www/hypernexus.site",
    "/var/www/tormentnexus.site",
    "/var/www/cloud.hypernexus.site",
]

PATTERNS = [
    r"LLM [Ww]aterfall",
    r"[Ww]aterfall [Ff]ailover",
    r"[Ww]aterfall [Cc]ascad",
    r"[Mm]odel [Cc]ascading",
    r"[Rr]esilient LLM",
    r"[Ll]ocal-[Ff]irst",
    r"[Ll]ocal [Ff]irst",
    r"[Ff]ull offline",
    r"[Oo]ffline\b",
    r"[Aa]ir-[Gg]apped",
]


def main():
    for root in ROOTS:
        for path in sorted(glob.glob(root + "/**/*.html", recursive=True)):
            if "/blog/" in path:
                continue  # dated editorial with its own titles/slugs - not marketing copy
            try:
                s = open(path, encoding="utf-8", errors="replace").read()
            except OSError:
                continue
            rows = []
            for pat in PATTERNS:
                for m in re.finditer(pat, s):
                    lo, hi = max(0, m.start() - 105), min(len(s), m.end() + 70)
                    ctx = " ".join(
                        html.unescape(re.sub(r"<[^>]+>", " ", s[lo:hi])).split()
                    )
                    rows.append((m.group(0), ctx, pat))
            if not rows:
                continue
            print(f"--- {path.replace('/var/www/', '')} ({len(rows)}) ---")
            seen = set()
            for tok, ctx, pat in rows:
                key = ctx[:110]
                if key in seen:
                    continue
                seen.add(key)
                print(f"    [{tok}] {ctx[:145]}")
            print()


if __name__ == "__main__":
    main()
