#!/usr/bin/env python3
"""Print the raw HTML around each waterfall / local-first mention.

Unlike the audit this does not strip tags - the point is to see the exact
element boundaries so removals can be anchored to whole cards, table rows,
list items and testimonials rather than just the words.

Usage: python extract_blocks.py <file> [pattern ...]
"""

import re
import sys

DEFAULT = [
    r"LLM [Ww]aterfall",
    r"[Ww]aterfall [Ff]ailover",
    r"[Ww]aterfall [Cc]ascad",
    r"[Mm]odel [Cc]ascading",
    r"[Rr]esilient LLM",
    r"[Ll]ocal-[Ff]irst",
]

path = sys.argv[1]
pats = sys.argv[2:] or DEFAULT
try:
    with open(path, encoding="utf-8", errors="replace") as fh:
        s = fh.read()
except OSError as exc:
    print(f"cannot read {path}: {exc}")
    sys.exit(1)

hits = []
for p in pats:
    for m in re.finditer(p, s):
        hits.append(m.start())
hits.sort()

merged = []
for h in hits:
    if merged and h - merged[-1][1] < 400:
        merged[-1][1] = h
    else:
        merged.append([h, h])

for lo, hi in merged:
    a, b = max(0, lo - 420), min(len(s), hi + 260)
    print("=" * 78)
    print(f"L{s[:a].count(chr(10)) + 1}-{s[:b].count(chr(10)) + 1}")
    print("=" * 78)
    print(s[a:b])
    print()
