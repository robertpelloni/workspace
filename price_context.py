#!/usr/bin/env python3
"""Show every price with its surrounding context, per file."""

import glob
import html
import re
import sys

PRICE = re.compile(r"\$\s?\d+(?:\.\d{1,2})?")


def strip(t):
    return " ".join(html.unescape(re.sub(r"<[^>]+>", " ", t)).split())


def main():
    for path in sys.argv[1:]:
        for f in glob.glob(path):
            try:
                s = open(f, encoding="utf-8", errors="replace").read()
            except OSError as exc:
                print(f"! {f}: {exc}")
                continue
            print("=" * 76)
            print(f"FILE: {f}")
            print("=" * 76)
            for m in PRICE.finditer(s):
                lo, hi = max(0, m.start() - 260), min(len(s), m.end() + 160)
                ctx = strip(s[lo:hi])
                print(f"  ...{ctx[-330:]}")
                print()
            print()


if __name__ == "__main__":
    main()
