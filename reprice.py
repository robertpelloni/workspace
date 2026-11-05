#!/usr/bin/env python3
"""Retarget the HyperNexus / TormentNexus pricing to the $1.99 intro rate.

Every rule is anchored to an exact string and reports how many times it fired,
so a pattern that silently stops matching is visible rather than a no-op. The
crossed-out "original" prices ($10/seat/mo, $100/seat/yr) are deliberately left
alone - they are the strikethrough reference price, not the current price.

Run with --apply to write; default is a dry run.
"""

import os
import sys

DRY = "--apply" not in sys.argv

HERE = os.path.dirname(os.path.abspath(__file__))

# (file, old, new, expected occurrences)
RULES = [
    # ---- checkout amount actually sent to Stripe (cents) ----
    (
        "hn_index_a.html",
        "price_amount:window.__price_amount||500",
        "price_amount:window.__price_amount||199",
        1,
    ),
    (
        "hn_index_b.html",
        "price_amount:window.__price_amount||500",
        "price_amount:window.__price_amount||199",
        1,
    ),
    (
        "hn_index.html",
        "price_amount:window.__price_amount||500",
        "price_amount:window.__price_amount||199",
        1,
    ),
    (
        "hn_index_a.html",
        "window.__price_amount = isYearly ? 5000 : 500;",
        "window.__price_amount = isYearly ? 1999 : 199;",
        1,
    ),
    (
        "hn_index_b.html",
        "window.__price_amount = isYearly ? 5000 : 500;",
        "window.__price_amount = isYearly ? 1999 : 199;",
        1,
    ),
    # ---- homepage price widget: A / B variants ----
    (
        "hn_index_a.html",
        'id="price-display">$5 <span',
        'id="price-display">$1.99 <span',
        1,
    ),
    (
        "hn_index_b.html",
        'id="price-display">$5 <span',
        'id="price-display">$1.99 <span',
        1,
    ),
    (
        "hn_index_a.html",
        "priceDisplay.textContent = isYearly ? '$50 ' : '$5 ';",
        "priceDisplay.textContent = isYearly ? '$19.99 ' : '$1.99 ';",
        1,
    ),
    (
        "hn_index_b.html",
        "priceDisplay.textContent = isYearly ? '$50 ' : '$5 ';",
        "priceDisplay.textContent = isYearly ? '$19.99 ' : '$1.99 ';",
        1,
    ),
    (
        "hn_index_a.html",
        '"That\'s $4.17/month. Save 17% vs monthly."',
        '"That\'s $1.67/month. Save 16% vs monthly."',
        1,
    ),
    (
        "hn_index_b.html",
        '"That\'s $4.17/month. Save 17% vs monthly."',
        '"That\'s $1.67/month. Save 16% vs monthly."',
        1,
    ),
    # ---- index.html: defaults to showing the yearly price, never sets
    #      __price_amount (so the ||fallback is what Stripe actually gets) ----
    (
        "hn_index.html",
        '<div class="price-amount">$50 <span class="period">/ seat / year</span></div>',
        '<div class="price-amount">$19.99 <span class="period">/ seat / year</span></div>',
        1,
    ),
    (
        "hn_index.html",
        'n.nodeValue.replace(/\\$[\\d,]+/, "$50")',
        'n.nodeValue.replace(/\\$[\\d,]+/, "$19.99")',
        1,
    ),
    (
        "hn_index.html",
        'n.nodeValue.replace(/\\$[\\d,]+/, "$5");',
        'n.nodeValue.replace(/\\$[\\d,]+/, "$1.99");',
        1,
    ),
    # ---- indexB.html: orphan legacy page, old string-replace toggle ----
    (
        "hn_indexB.html",
        '<div class="price-amount">$50 <span class="period">/ seat / year</span>',
        '<div class="price-amount">$19.99 <span class="period">/ seat / year</span>',
        1,
    ),
    ("hn_indexB.html", '.replace("$5","$50")', '.replace("$1.99","$19.99")', 1),
    ("hn_indexB.html", '.replace("$50","$5")', '.replace("$19.99","$1.99")', 1),
    # ---- pricing.html ----
    (
        "hn_pricing.html",
        "$50/seat for local license",
        "$1.99/seat/month for local license",
        1,
    ),
    (
        "hn_pricing.html",
        'opacity: 0.8">Save 17%</span>',
        'opacity: 0.8">Save 16%</span>',
        1,
    ),
    (
        "hn_pricing.html",
        'priceValue.textContent = isYearly ? "50" : "5";',
        'priceValue.textContent = isYearly ? "19.99" : "1.99";',
        1,
    ),
    (
        "hn_pricing.html",
        '"That\'s $4.17/month. Save 17% vs monthly."',
        '"That\'s $1.67/month. Save 16% vs monthly."',
        1,
    ),
    (
        "hn_pricing.html",
        'compPrice.textContent = isYearly ? "$50/yr" : "$5/mo";',
        'compPrice.textContent = isYearly ? "$19.99/yr" : "$1.99/mo";',
        1,
    ),
    (
        "hn_pricing.html",
        '<span id="comparison-price">$5/mo</span>',
        '<span id="comparison-price">$1.99/mo</span>',
        1,
    ),
    # static first-paint value, separate from the JS that rewrites it on toggle
    (
        "hn_pricing.html",
        '<span class="dollar">$</span><span id="price-value">5</span>',
        '<span class="dollar">$</span><span id="price-value">1.99</span>',
        1,
    ),
    # the actual cents sent to Stripe, on first load AND on toggle
    (
        "hn_pricing.html",
        'window.__price_amount = __pricing_plan === "yearly" ? 5000 : 500;',
        'window.__price_amount = __pricing_plan === "yearly" ? 1999 : 199;',
        1,
    ),
    (
        "hn_pricing.html",
        "window.__price_amount = isYearly ? 5000 : 500;",
        "window.__price_amount = isYearly ? 1999 : 199;",
        1,
    ),
    (
        "cl_cloud_login_a.html",
        'window.__price_amount = __pricing_plan === "yearly" ? 5000 : 500;',
        'window.__price_amount = __pricing_plan === "yearly" ? 1999 : 199;',
        1,
    ),
    (
        "cl_cloud_login_a.html",
        "window.__price_amount = isYearly ? 5000 : 500;",
        "window.__price_amount = isYearly ? 1999 : 199;",
        1,
    ),
    (
        "cl_cloud_login_b.html",
        'window.__price_amount = __pricing_plan === "yearly" ? 5000 : 500;',
        'window.__price_amount = __pricing_plan === "yearly" ? 1999 : 199;',
        1,
    ),
    (
        "cl_cloud_login_b.html",
        "window.__price_amount = isYearly ? 5000 : 500;",
        "window.__price_amount = isYearly ? 1999 : 199;",
        1,
    ),
    # ---- checkout.html ----
    (
        "hn_checkout.html",
        '<span class="price">$50</span>',
        '<span class="price">$19.99</span>',
        1,
    ),
    ("hn_checkout.html", "Pay $50/year", "Pay $19.99/year", 2),
    # ---- account / download / get-started / testimonials ----
    ("hn_account.html", "Professional — $50/yr", "Professional — $19.99/yr", 1),
    ("hn_download.html", "$50/year", "$19.99/year", 1),
    (
        "hn_get-started.html",
        '<span class="amount">$50</span>',
        '<span class="amount">$19.99</span>',
        1,
    ),
    ("hn_get-started.html", "Buy as Guest ($50/yr)", "Buy as Guest ($19.99/yr)", 1),
    (
        "hn_testimonials.html",
        '<div class="stat-value">$50/yr</div>',
        '<div class="stat-value">$19.99/yr</div>',
        1,
    ),
    ("hn_testimonials.html", "Get Started — $50/year", "Get Started — $19.99/year", 1),
    # ---- TormentNexus ----
    (
        "tn_pricing.html",
        '<div class="price">$5 <span>/ seat / month</span></div>',
        '<div class="price">$1.99 <span>/ seat / month</span></div>',
        1,
    ),
    (
        "tn_download.html",
        "Get HyperNexus Pro — $50/yr",
        "Get HyperNexus Pro — $19.99/yr",
        1,
    ),
    # ---- cloud login pages ----
    (
        "cl_cloud_login_a.html",
        '<span id="price-label">$5/mo</span>',
        '<span id="price-label">$1.99/mo</span>',
        1,
    ),
    (
        "cl_cloud_login_b.html",
        '<span id="price-label">$5/mo</span>',
        '<span id="price-label">$1.99/mo</span>',
        1,
    ),
    (
        "cl_cloud_login_a.html",
        'priceLabel.textContent = isYearly ? "$50/yr" : "$5/mo";',
        'priceLabel.textContent = isYearly ? "$19.99/yr" : "$1.99/mo";',
        1,
    ),
    (
        "cl_cloud_login_b.html",
        'priceLabel.textContent = isYearly ? "$50/yr" : "$5/mo";',
        'priceLabel.textContent = isYearly ? "$19.99/yr" : "$1.99/mo";',
        1,
    ),
]


def main():
    cache = {}
    problems = []
    fired = {}

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
        fired[(fname, old)] = n
        if n != want:
            problems.append(f"{fname}: expected {want}x, found {n}x -> {old[:70]!r}")
            continue
        cache[path] = s.replace(old, new)

    print("=== replacement report ===")
    for (fname, old), n in fired.items():
        flag = "ok " if n else "!! "
        print(f"  {flag}{n}x  {fname:<24} {old[:62]}")
    print()

    if problems:
        print("=== PROBLEMS ===")
        for p in problems:
            print("  " + p)
        print()
        if DRY:
            print("(dry run - nothing written)")
            return 1

    if DRY:
        print("dry run: nothing written. Re-run with --apply")
        return 0 if not problems else 1

    for path, text in cache.items():
        try:
            with open(path, "w", encoding="utf-8", newline="") as fh:
                fh.write(text)
        except OSError as exc:
            print(f"  !! failed to write {os.path.basename(path)}: {exc}")
            return 1
        print(f"  wrote {os.path.basename(path)}")
    return 0 if not problems else 1


if __name__ == "__main__":
    sys.exit(main())
