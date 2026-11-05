#!/usr/bin/env python3
"""Round 2: the same two phrases on the pages round 1 did not reach.

Round 1 fixed the homepages, tables and integration pages. This handles the
rest: the cloud A/B variant, docs landing, home_router metadata, the dedicated
testimonials page, and the TormentNexus pages.

Cards are matched with a newline-agnostic regex - two of the integration pages
are CRLF, and a literal \\n in the pattern silently fails on those.
"""

import os
import re
import sys

DRY = "--apply" not in sys.argv
HERE = os.path.dirname(os.path.abspath(__file__))

TARGETS = [
    "c_index_b.html",
    "h_compare.html",
    "h_cursor-with-hypernexus.html",
    "h_docs_index.html",
    "h_home_router.html",
    "h_index.html",
    "h_index_a.html",
    "h_index_b.html",
    "h_live.html",
    "h_testimonials.html",
    "t_compare.html",
    "t_download.html",
    "t_index.html",
    "t_index_live.html",
    "t_v2.html",
    "t_xenocide.html",
]

CARD_CASCADING_RE = (
    r'<div class="feature"><div class="feature-icon">🌊</div>'
    r"<h3>Resilient Model Cascading</h3><p>Ensure uninterrupted coding by automatically "
    r"routing around rate limits \(429s/5xx\) down a waterfall chain to local Ollama "
    r"backups\.</p></div>\s*"
)

TESTIMONIAL_INDEX = """<div style="padding:24px;background:var(--glass);border:1px solid var(--glass-border);border-radius:12px">
            <p style="color:var(--text);font-size:15px;margin-bottom:16px;font-style:italic">"The waterfall failover saved us during an OpenAI outage. Our agents kept working on local Ollama while everyone else was down."</p>
            <div style="display:flex;align-items:center;gap:12px">
              <div style="width:36px;height:36px;border-radius:50%;background:linear-gradient(135deg,#4cd964,#4dc9f6)"></div>
              <div>
                <div style="font-size:14px;font-weight:600;color:#fff">DevOps Lead</div>
                <div style="font-size:13px;color:var(--text-secondary)">Enterprise SaaS</div>
              </div>
            </div>
          </div>
"""

TESTIMONIAL_PAGE = """<div class="testimonial">
                <div class="stars">★★★★★</div>
                <p class="testimonial-text">The LLM waterfall is a game-changer. When OpenAI rate-limited us, we seamlessly fell back to local Ollama. Zero downtime during our busiest sprint.</p>
                <div class="testimonial-author">
                    <div class="author-avatar">DL</div>
                    <div class="author-info">
                        <div class="author-name">DevOps Lead</div>
                        <div class="author-role">Fortune 500 Company</div>
                    </div>
                </div>
            </div>

"""

ROW_HN_WF = (
    "          <tr>\n            <td>LLM Waterfall</td>\n"
    '            <td><span class="check">✓ Auto-failover</span></td>\n'
    '            <td><span class="cross">✗</span></td>\n'
    '            <td><span class="cross">✗</span></td>\n'
    '            <td><span class="cross">✗</span></td>\n          </tr>\n'
)

EXACT = [
    # ---- cloud A/B variant -------------------------------------------------
    (
        "c_index_b.html",
        "                <li>🔄 <strong>LLM Waterfall Failover</strong> — Cascades from NVIDIA NIM → OpenRouter → local Ollama on any 429/5xx error</li>\n",
        "",
        1,
    ),
    # ---- compare table row that round 1 built to the wrong shape -----------
    ("h_compare.html", ROW_HN_WF, "", 1),
    # ---- cursor integration: the "reliability" bullet ----------------------
    (
        "h_cursor-with-hypernexus.html",
        "                <li><strong>Developers who want reliability</strong> — LLM waterfall ensures your agents never go down</li>\n",
        "",
        1,
    ),
    # ---- docs landing -----------------------------------------------------
    (
        "h_docs_index.html",
        "multi-agent orchestration. Local-first. Open source.",
        "multi-agent orchestration. Open source.",
        1,
    ),
    (
        "h_docs_index.html",
        '  <div class="card">\n    <h3><span class="emoji">🌊</span> LLM Waterfall</h3>\n'
        "    <p>Cascading failover: NVIDIA NIM → OpenRouter → Local Ollama. Never blocked by rate limits or outages.</p>\n  </div>\n",
        "",
        1,
    ),
    # ---- home_router metadata --------------------------------------------
    (
        "h_home_router.html",
        "reach the model. Local-first, 38+ clients.",
        "reach the model. 38+ clients.",
        1,
    ),
    (
        "h_home_router.html",
        "14,250+ MCP servers. Local-first, 38+ clients.",
        "14,250+ MCP servers. 38+ clients.",
        1,
    ),
    # ---- homepage second testimonial --------------------------------------
    ("h_index.html", TESTIMONIAL_INDEX, "", 1),
    ("h_index_a.html", TESTIMONIAL_INDEX, "", 1),
    ("h_index_b.html", TESTIMONIAL_INDEX, "", 1),
    # ---- dedicated testimonials page --------------------------------------
    ("h_testimonials.html", TESTIMONIAL_PAGE, "", 1),
    # ---- TormentNexus ------------------------------------------------------
    (
        "t_compare.html",
        '<tr><td>LLM Waterfall</td><td class="check">3-tier auto</td><td class="cross">No</td><td class="cross">No</td><td class="cross">No</td><td class="cross">No</td></tr>\n',
        "",
        1,
    ),
    (
        "t_compare.html",
        '<td>Self-Hosted</td><td class="check">Local-first</td>',
        '<td>Self-Hosted</td><td class="check">Self-hosted</td>',
        1,
    ),
    (
        "t_download.html",
        '<span class="check">✓</span> Local-first, privacy focused',
        '<span class="check">✓</span> Privacy focused',
        1,
    ),
    (
        "t_index.html",
        "the open-source, local-first MCP router for AI agents",
        "the open-source MCP router for AI agents",
        1,
    ),
    (
        "t_index.html",
        "5,700+ skills, LLM waterfall failover. Works with",
        "5,700+ skills. Works with",
        1,
    ),
    (
        "t_index.html",
        ", AI orchestration, LLM waterfall, local-first AI, open source AI",
        ", AI orchestration, open source AI",
        1,
    ),
    (
        "t_index.html",
        "~60% smaller context, local-first, open source.",
        "~60% smaller context, open source.",
        1,
    ),
    (
        "t_index.html",
        "~60% smaller context. Local-first. Open source.",
        "~60% smaller context. Open source.",
        1,
    ),
    (
        "t_index.html",
        "TormentNexus is a local-first cognitive control plane. It routes",
        "TormentNexus is a cognitive control plane. It routes",
        1,
    ),
    (
        "t_index_live.html",
        "Resilient Cascade",
        "Resilient Cascade",
        1,
    ),  # placeholder, handled below
]

REGEX = [
    # feature cards, newline-agnostic (two pages are CRLF)
    (
        r'<div class="feature">\s*<div class="feature-icon">🌊</div>\s*<h3>Resilient Model Cascading</h3>\s*'
        r"<p>Ensure uninterrupted coding by automatically routing around rate limits \(429s/5xx\) down a waterfall "
        r"chain to local Ollama backups\.</p>\s*</div>\s*",
        "",
        ["h_live.html", "c_index_b.html"],
        (0, 2),
    ),
    # TormentNexus capability card
    (
        r'<div class="feature">\s*<div class="icon">🌊</div>\s*<h3>Resilient LLM Waterfall</h3>\s*<p>.*?</p>\s*'
        r'<div class="tag">[^<]*</div>\s*</div>\s*',
        "",
        ["t_index.html"],
        (0, 1),
    ),
    # TormentNexus xenocide/heritage pages: the [03] LLM WATERFALL cap card
    (
        r'<div class="cap-card">\s*<div class="cap-card-icon"><span class="num">\[03\]</span> ✦ LLM WATERFALL</div>\s*'
        r"<h3>Resilient Cascade</h3>\s*<p>.*?</p>\s*</div>\s*",
        "",
        ["t_index_live.html", "t_v2.html", "t_xenocide.html"],
        (0, 1),
    ),
    (
        r'<div class="phase-desc">MCP tool routing\. LLM waterfall\. Provider catalog\.',
        '<div class="phase-desc">MCP tool routing. Provider catalog.',
        ["t_index_live.html", "t_v2.html", "t_xenocide.html"],
        (0, 1),
    ),
]


def main():
    cache, problems, report = {}, [], []

    for fname, old, new, want in EXACT:
        if old == new:
            continue
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
        lo, hi = (want, want) if isinstance(want, int) else want
        n = cache[path].count(old)
        report.append((fname, old.splitlines()[0][:58], n, lo, hi))
        if not (lo <= n <= hi):
            problems.append(f"{fname}: expected {lo}-{hi}, found {n} -> {old[:58]!r}")
            continue
        cache[path] = cache[path].replace(old, new)

    print("=== exact ===")
    for fname, label, n, lo, hi in report:
        if n:
            print(f"  {'ok ' if lo <= n <= hi else '!! '}{n}x  {fname:<36} {label}")
    print()

    print("=== regex ===")
    for pat, rep, files, (lo, hi) in REGEX:
        for f in files:
            path = os.path.join(HERE, f)
            if path not in cache:
                try:
                    with open(path, encoding="utf-8", newline="") as fh:
                        cache[path] = fh.read()
                except OSError as exc:
                    problems.append(f"{f}: cannot read ({exc})")
                    continue
            cache[path], n = re.subn(pat, rep, cache[path], flags=re.S)
            if n:
                print(f"  {n:3d}x  {f:<36} {pat[:56]}")
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
            print(f"  !! write failed {os.path.basename(path)}: {exc}")
            return 1
    print(f"  wrote {len(cache)} files")
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
