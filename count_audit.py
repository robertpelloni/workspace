#!/usr/bin/env python3
"""Find every tool/skill count claim on the sites, with context.

Different pages were written at different times and quote different catalogue
sizes (14,250+ / 20,000+ / 7,000+), so this lists them all so they can be
reconciled to one number.
"""

import glob
import html
import re

PATTERNS = [
    r"20,000\s*\+?",
    r"7,000\s*\+?",
    r"14,250\s*\+?",
    r"5,700\s*\+?",
    r"\b47\s+MCP",
]

ROOTS = [
    "/var/www/hypernexus.site",
    "/var/www/tormentnexus.site",
    "/var/www/cloud.hypernexus.site",
]


def main():
    for root in ROOTS:
        for path in sorted(glob.glob(root + "/*.html")):
            try:
                s = open(path, encoding="utf-8", errors="replace").read()
            except OSError:
                continue
            for pat in PATTERNS:
                for m in re.finditer(pat, s):
                    lo, hi = max(0, m.start() - 95), min(len(s), m.end() + 70)
                    ctx = " ".join(
                        html.unescape(re.sub(r"<[^>]+>", " ", s[lo:hi])).split()
                    )
                    print(
                        f"  {path.replace('/var/www/', ''):<42} {m.group(0):<9} {ctx[:130]}"
                    )
        print()


if __name__ == "__main__":
    main()
