#!/usr/bin/env python3
"""List every remaining $5/$50-style price with context, across all site files.

After the $1.99 reprice this is the check for anything that still advertises the
old price - integration landing pages ("x-with-hypernexus"), comparison tables,
and so on.
"""

import glob
import html
import re

ROOTS = [
    "/var/www/hypernexus.site",
    "/var/www/tormentnexus.site",
    "/var/www/cloud.hypernexus.site",
]

# the old money, as it would appear if still present
OLD = re.compile(r"\$\s?(?:5(?![\d.])|50(?![\d,]))(?:/|\s)?(?:mo|month|yr|year|seat)?")


def main():
    for root in ROOTS:
        for path in sorted(glob.glob(root + "/*.html")):
            try:
                s = open(path, encoding="utf-8", errors="replace").read()
            except OSError:
                continue
            rows = []
            for m in OLD.finditer(s):
                lo, hi = max(0, m.start() - 105), min(len(s), m.end() + 55)
                ctx = " ".join(html.unescape(re.sub(r"<[^>]+>", " ", s[lo:hi])).split())
                rows.append((m.group(0), ctx))
            if rows:
                print(f"--- {path.replace('/var/www/', '')} ({len(rows)}x) ---")
                seen = set()
                for tok, ctx in rows:
                    if ctx in seen:
                        continue
                    seen.add(ctx)
                    print(f"    [{tok}] {ctx[:150]}")
                print()


if __name__ == "__main__":
    main()
