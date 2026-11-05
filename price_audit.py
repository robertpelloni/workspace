#!/usr/bin/env python3
"""Enumerate every price-like string across the HyperNexus / TormentNexus sites.

Pricing is spread over several hand-maintained static pages, so before changing
anything it is worth knowing exactly where each number lives.
"""

import glob
import html
import re

ROOTS = [
    "/var/www/hypernexus.site",
    "/var/www/tormentnexus.site",
    "/var/www/cloud.hypernexus.site",
]

# $5, $5.00, $50 / seat / mo, $100/seat/yr ...
PRICE = re.compile(r"\$\s?\d+(?:\.\d{1,2})?(?:\s*/\s*[A-Za-z][A-Za-z ]{0,14})?")

# things that look like prices but are not (JS/CSS noise)
NOISE = {"$0", "$ 0"}


def main():
    for root in ROOTS:
        files = sorted(glob.glob(root + "/*.html")) + sorted(
            glob.glob(root + "/blog/*.html")
        )
        for path in files:
            try:
                s = open(path, encoding="utf-8", errors="replace").read()
            except OSError as exc:
                print(f"  ! {path}: {exc}")
                continue
            hits = {}
            for m in PRICE.finditer(s):
                t = " ".join(html.unescape(m.group(0)).split())
                if t in NOISE:
                    continue
                hits[t] = hits.get(t, 0) + 1
            if hits:
                short = path.replace("/var/www/", "")
                print(f"--- {short} ---")
                for t, n in sorted(hits.items(), key=lambda kv: (-kv[1], kv[0])):
                    print(f"     {n:3d}x  {t[:58]}")
        print()


if __name__ == "__main__":
    main()
