#!/usr/bin/env python3
"""Drop 'LLM waterfall' and 'local-first' from the marketing copy.

Both were listed as not-important selling points. Elements are removed whole
rather than just having the words deleted, so no empty card, table row or
collapsed FAQ is left behind:

  - feature cards  ('Resilient Model Cascading', 'LLM Waterfall')
  - the hero bullet
  - comparison-table rows ('LLM Waterfall', 'Local-First')
  - the 'How does the LLM Waterfall work?' FAQ entry
  - testimonials whose entire point is the waterfall
  - meta / og / twitter / JSON-LD lines reworded to drop both phrases

Two rule kinds, because the pages are hand-maintained and vary:
  EXACT  - anchored strings, so a silent no-match is visible
  REGEX  - phrase rewrites for the metadata lines that differ per page

Deliberately untouched:
  - blog posts (dated editorial; several are *about* local-first, so editing
    them would gut the article - their titles and slugs are the article)
  - changelog.html (a historical record of what shipped)
  - air-gapped / offline / VPC copy (a separate enterprise-security claim)
  - testimonials that do not mention these features

Run with --apply to write.
"""

import os
import re
import sys

DRY = "--apply" not in sys.argv
HERE = os.path.dirname(os.path.abspath(__file__))

MARKETING = [
    "h_index.html", "h_index_a.html", "h_index_b.html", "h_indexB.html",
    "h_pricing.html", "h_compare.html", "h_home_router.html", "h_live.html",
    "h_testimonials.html", "h_docs_index.html", "h_changelog.html",
    "h_claude-code-with-hypernexus.html", "h_copilot-with-hypernexus.html",
    "h_cursor-with-hypernexus.html", "h_gemini-cli-with-hypernexus.html",
    "h_kiro-with-hypernexus.html", "h_windsurf-with-hypernexus.html",
    "t_index.html", "t_compare.html", "t_download.html",
    "t_index_live.html", "t_v2.html", "t_xenocide.html",
    "c_index_b.html",
]

CARD_CASCADING = ('                <div class="feature"><div class="feature-icon">🌊</div>'
                  '<h3>Resilient Model Cascading</h3><p>Ensure uninterrupted coding by automatically '
                  'routing around rate limits (429s/5xx) down a waterfall chain to local Ollama backups.</p></div>\n\n')

BULLET_WATERFALL = ('                <li><span style="font-size:22px;filter:drop-shadow(0 0 8px rgba(0,200,100,0.8)) '
                    'drop-shadow(0 0 16px rgba(0,200,100,0.4))">🔄</span> <strong>LLM Waterfall Failover</strong> — '
                    'Optionally cascade from OpenAI → OpenRouter → local Ollama on any 429/5xx error, observe and '
                    'track the flow</li>\n')

TF_CARD = ('<div class="feature-card">\n'
           '                    <div class="feature-icon">🔄</div>\n'
           '                    <h4>LLM Waterfall</h4>\n')

FAQ_WATERFALL = ('''<details style="background:#f8fafc;border:1px solid #e2e8f0;border-radius:8px;padding:16px 20px">
                    <summary style="font-weight:600;font-size:15px;color:#0f172a;cursor:pointer;list-style:none;display:flex;justify-content:space-between;align-items:center">
                        How does the LLM Waterfall work?
                        <span style="font-size:18px;color:#94a3b8;transition:transform 0.2s">+</span>
                    </summary>
                    <p style="margin-top:12px;font-size:14px;color:#475569;line-height:1.7">When your primary LLM provider (e.g., OpenAI) returns a 429 rate-limit or 5xx error, HyperNexus automatically cascades the request to your configured fallback chain: NVIDIA NIM → OpenRouter → local Ollama/LM Studio. Zero downtime inference.</p>
                </details>
''')

# testimonials whose whole point is the waterfall
TESTIMONIAL_A = ('''                <div style="background:#fff;padding:24px;border-radius:12px;border:1px solid #e2e8f0;box-shadow:0 1px 3px rgba(0,0,0,0.05)">
                    <div style="display:flex;gap:4px;margin-bottom:12px">
                        <span style="color:#facc15">★</span><span style="color:#facc15">★</span><span style="color:#facc15">★</span><span style="color:#facc15">★</span><span style="color:#facc15">★</span>
                    </div>
                    <p style="color:#475569;font-size:15px;line-height:1.7;margin-bottom:16px">"The LLM waterfall is a game-changer. When OpenAI rate-limited us, we seamlessly fell back to local Ollama. Zero downtime during our busiest sprint."</p>
                    <div style="display:flex;align-items:center;gap:12px">
                        <div style="width:40px;height:40px;border-radius:50%;background:linear-gradient(135deg,#10b981,#34d399)"></div>
                        <div>
                            <div style="font-weight:600;font-size:14px;color:#0f172a">DevOps Lead</div>
                            <div style="font-size:13px;color:#64748b">Fortune 500 Company</div>
                        </div>
                    </div>
                </div>
''')

TESTIMONIAL_B = ('''<div style="padding:24px;background:var(--glass);border:1px solid var(--glass-border);border-radius:12px">
            <p style="color:var(--text);font-size:15px;margin-bottom:16px;font-style:italic">"The waterfall failover saved us during an OpenAI outage. Our agents kept working on local Ollama while everyone else was down."</p>
''')

ROW_HN = ('          <tr>\n            <td>%s</td>\n            <td><span class="check">%s</span></td>\n'
          '            <td><span class="cross">✗</span></td>\n            <td><span class="cross">✗</span></td>\n'
          '            <td>%s</td>\n          </tr>\n')
ROW_PR = ('        <tr>\n          <td>%s</td>\n          <td class="check">%s</td>\n'
          '          <td class="x">✗</td>\n          <td class="x">✗</td>\n        </tr>\n')

EXACT = []

# ---- homepages ----------------------------------------------------------
HOMEPAGES = ["h_index.html", "h_index_a.html", "h_index_b.html", "h_indexB.html"]
for f in HOMEPAGES:
    EXACT += [(f, CARD_CASCADING, "", 1), (f, BULLET_WATERFALL, "", 1)]
    EXACT += [(f, "— a local-first control plane that reads", "— a control plane that reads", (0, 1))]
    EXACT += [(f, ", LLM waterfall, local-first AI,", ",", (0, 1))]
    EXACT += [(f, '        "Resilient LLM Waterfall Failover",\n', "", (0, 1))]
for f in ("h_index_a.html", "h_index_b.html"):
    EXACT += [(f, TESTIMONIAL_A, "", 1), (f, FAQ_WATERFALL, "", 1)]

# ---- tables -------------------------------------------------------------
for f in ("h_compare.html", "h_pricing.html"):
    row_wf = ROW_HN % ("LLM Waterfall", "✓ Auto-failover", "—")
    row_lf = ROW_HN % ("Local-First", "✓ Full offline", "Partial")
    row_pr_wf = ROW_PR % ("LLM Waterfall", "✓ Auto-failover")
    row_pr_lf = ROW_PR % ("Local-First", "✓ Full offline")
    EXACT += [(f, row_wf, "", (0, 1)), (f, row_lf, "", (0, 1))]
    EXACT += [(f, row_pr_wf, "", (0, 1)), (f, row_pr_lf, "", (0, 1))]

# ---- integration landing pages -----------------------------------------
for f in ("h_claude-code-with-hypernexus.html", "h_copilot-with-hypernexus.html",
          "h_cursor-with-hypernexus.html", "h_gemini-cli-with-hypernexus.html",
          "h_kiro-with-hypernexus.html", "h_windsurf-with-hypernexus.html"):
    EXACT += [
        (f, ", LLM waterfall failover,", ",", 1),
        (f, "Add progressive tool routing, persistent memory, and resilient LLM failover on top.",
            "Add progressive tool routing, skill suggestions, and persistent memory on top.", 1),
    ]
    # the whole "LLM Waterfall" feature card in the grid
    s_path = os.path.join(HERE, f)
    if os.path.isfile(s_path):
        try:
            # newline="" matters: two of these pages are CRLF, and universal
            # newline translation would build a fragment that can never match.
            with open(s_path, encoding="utf-8", newline="") as fh:
                body = fh.read()
        except OSError:
            body = ""
        m = re.search(r'<div class="feature-card">\n\s*<div class="feature-icon">🔄</div>\n\s*<h4>LLM Waterfall</h4>\n'
                      r'\s*<p>[^<]*</p>\n\s*</div>\n', body)
        if m:
            EXACT.append((f, m.group(0), "", 1))

# ---- REGEX phrase rewrites (metadata varies per page) -------------------
REGEX = [
    (r"Local-first cognitive control plane", "Cognitive control plane", 1, 4),
    (r"HyperNexus is a local-first cognitive control plane", "HyperNexus is a cognitive control plane", 0, 2),
    (r"Yes\. HyperNexus is local-first — all ", "Yes. All ", 0, 2),
    (r", LLM waterfall failover\.", ".", 0, 4),
    (r", LLM waterfall failover,", ",", 0, 4),
    (r", and resilient LLM failover\.", ".", 0, 4),
    (r"persistent memory, LLM failover, enterprise AI", "persistent memory, enterprise AI", 0, 4),
    (r"persistent memory, LLM waterfall failover", "persistent memory", 0, 4),
    (r", local-first\.", ".", 0, 6),
    (r", local-first and open source\.", " and open source.", 0, 4),
]


def main():
    cache, problems, exact_report, regex_report = {}, [], [], []

    for fname, old, new, want in EXACT:
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
        exact_report.append((fname, old.splitlines()[0][:56], n, lo, hi))
        if not (lo <= n <= hi):
            problems.append(f"{fname}: expected {lo}-{hi}, found {n} -> {old[:60]!r}")
            continue
        cache[path] = cache[path].replace(old, new)

    for path in list(cache):
        text = cache[path]
        for pat, rep, lo, hi in REGEX:
            text, n = re.subn(pat, rep, text)
            if n:
                regex_report.append((os.path.basename(path), pat, n))
        cache[path] = text

    print("=== exact removals ===")
    for fname, label, n, lo, hi in exact_report:
        ok = "ok " if lo <= n <= hi else "!! "
        if n:
            print(f"  {ok}{n}x  {fname:<38} {label}")
    print()

    if regex_report:
        print("=== regex rewrites ===")
        for fname, pat, n in regex_report:
            print(f"  {n:3d}x  {fname:<38} {pat[:56]}")
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
