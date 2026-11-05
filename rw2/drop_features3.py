#!/usr/bin/env python3
"""Round 3: the two CRLF integration pages round 1 could not match.

Round 1 built its feature-card pattern with literal \\n, which can never match
the \\r\\n line endings on kiro and windsurf. This uses \\s* throughout.
"""

import os
import re
import sys

DRY = "--apply" not in sys.argv
HERE = os.path.dirname(os.path.abspath(__file__))

FILES = ["h_kiro-with-hypernexus.html", "h_windsurf-with-hypernexus.html"]

PAT = (r'<div class="feature-card">\s*<div class="feature-icon">🔄</div>\s*'
       r'<h4>LLM Waterfall</h4>\s*<p>[^<]*</p>\s*</div>\s*')


def main():
    cache, problems = {}, []
    for f in FILES:
        path = os.path.join(HERE, f)
        try:
            with open(path, encoding="utf-8", newline="") as fh:
                cache[path] = fh.read()
        except OSError as exc:
            problems.append(f"{f}: cannot read ({exc})")
            continue
        new, n = re.subn(PAT, "", cache[path], flags=re.S)
        print(f"  {'ok ' if n == 1 else '!! '}{n}x  {f}")
        if n != 1:
            problems.append(f"{f}: expected 1 removal, got {n}")
            continue
        cache[path] = new

    print()
    if problems:
        for p in problems:
            print("  PROBLEM: " + p)
    if DRY:
        print("dry run: nothing written")
        return 1 if problems else 0

    for path, text in cache.items():
        try:
            with open(path, "w", encoding="utf-8", newline="") as fh:
                fh.write(text)
        except OSError as exc:
            print(f"  !! write failed {os.path.basename(path)}: {exc}")
            return 1
    print(f"  wrote {len(cache)} files")
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
