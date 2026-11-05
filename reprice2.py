#!/usr/bin/env python3
"""Second reprice pass: the files the first pass missed, plus tool-count claims.

The first pass covered the pages named in the request (indexes, cloud logins,
pricing). This one sweeps the whole site for the same two problems:

  1. our own old price ($5/mo, $50/year) still on integration landing pages,
     comparison tables, the cloud account page and the cloud A/B variant
  2. a competing catalogue size (20,000+ and 7,000+) that contradicts the
     14,250+ MCP servers / 5,700+ skills used everywhere else

Competitor prices ($10/mo Copilot, $20/mo Cursor, $15/mo Windsurf, $240 and
$120 per year) and a customer testimonial that says "47 MCP servers" are
deliberately untouched.

Run with --apply to write.
"""

import os
import sys

DRY = "--apply" not in sys.argv
HERE = os.path.dirname(os.path.abspath(__file__))

INTEGRATION = [
    "hn_claude-code-with-hypernexus.html",
    "hn_copilot-with-hypernexus.html",
    "hn_cursor-with-hypernexus.html",
    "hn_gemini-cli-with-hypernexus.html",
    "hn_kiro-with-hypernexus.html",
    "hn_windsurf-with-hypernexus.html",
]

RULES = []

# 1. the integration landing pages all price HyperNexus at $5/mo
for f in INTEGRATION:
    RULES += [
        (f, "Get Started — $5/mo", "Get Started — $1.99/mo", 2),
        (f, "+ $5/mo<", "+ $1.99/mo<", 1),
    ]

RULES += [
    # 2. comparison tables and remaining pages
    (
        "hn_compare.html",
        '<span class="price">$50/year</span>',
        '<span class="price">$19.99/year</span>',
        1,
    ),
    ("hn_compare.html", "Get Started — $50/year", "Get Started — $19.99/year", 1),
    (
        "hn_live.html",
        '<div class="price-amount">$5 <span class="period">/ seat / mo</span></div>',
        '<div class="price-amount">$1.99 <span class="period">/ seat / mo</span></div>',
        1,
    ),
    (
        "cl_index_b.html",
        '<div class="price-amount">$5 <span class="period">/ seat / mo</span></div>',
        '<div class="price-amount">$1.99 <span class="period">/ seat / mo</span></div>',
        1,
    ),
    ("cl_index_b.html", '.replace("$5","$50")', '.replace("$1.99","$19.99")', 1),
    ("cl_index_b.html", '.replace("$50","$5")', '.replace("$19.99","$1.99")', 1),
    ("cl_account.html", "Professional — $5/mo", "Professional — $1.99/mo", 1),
    ("tn_compare.html", "Free / $5/seat", "Free / $1.99/seat", 1),
    # 3. one catalogue size everywhere: 14,250+ MCP servers, 5,700+ skills
    ("hn_checkout.html", "20,000+ MCP tools", "14,250+ MCP servers", 1),
    ("hn_download.html", "20,000+ MCP Tools", "14,250+ MCP servers", 1),
    ("hn_get-started.html", "20,000+ MCP tool integrations", "14,250+ MCP servers", 1),
    ("hn_pricing.html", "20,000+ MCP tool integrations", "14,250+ MCP servers", 1),
    (
        "hn_pricing.html",
        '<td class="check">✓ 20,000+</td>',
        '<td class="check">✓ 14,250+</td>',
        1,
    ),
    (
        "hn_compare.html",
        '<span class="check">✓ 20,000+</span>',
        '<span class="check">✓ 14,250+</span>',
        1,
    ),
    (
        "hn_testimonials.html",
        '<div class="stat-value">20,000+</div>',
        '<div class="stat-value">14,250+</div>',
        1,
    ),
    (
        "tn_legacy.html",
        "7,000+ MCP servers assimilated. 5,500+ handlers.",
        "14,250+ MCP servers assimilated. 5,700+ skills.",
        1,
    ),
    (
        "tn_legacy.html",
        '<div class="stat-num">7,000+</div>',
        '<div class="stat-num">14,250+</div>',
        1,
    ),
    (
        "tn_legacy.html",
        "MCP Router: 7,000+ servers indexed",
        "MCP Router: 14,250+ servers indexed",
        1,
    ),
]


def main():
    cache, problems, report = {}, [], []

    for fname, old, new, want in RULES:
        path = os.path.join(HERE, fname)
        if path not in cache:
            if not os.path.isfile(path):
                problems.append(f"{fname}: file not found")
                continue
            try:
                with open(path, encoding="utf-8", newline="") as fh:
                    cache[path] = fh.read()
            except OSError as exc:
                problems.append(f"{fname}: cannot read ({exc})")
                continue

        s = cache[path]
        n = s.count(old)
        report.append((fname, old, n, want))
        if n != want:
            problems.append(f"{fname}: expected {want}x, found {n}x -> {old[:60]!r}")
            continue
        cache[path] = s.replace(old, new)

    print("=== report ===")
    for fname, old, n, want in report:
        ok = "ok " if n == want else "!! "
        print(f"  {ok}{n}x  {fname:<36} {old[:52]}")
    print()

    if problems:
        print("=== PROBLEMS ===")
        for p in problems:
            print("  " + p)
        print()

    if DRY:
        print("dry run: nothing written")
        return 1 if problems else 0

    for path, text in cache.items():
        try:
            with open(path, "w", encoding="utf-8", newline="") as fh:
                fh.write(text)
        except OSError as exc:
            print(f"  !! failed to write {os.path.basename(path)}: {exc}")
            return 1
    print(f"  wrote {len(cache)} files")
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
