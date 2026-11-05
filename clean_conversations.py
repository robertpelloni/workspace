#!/usr/bin/env python3
"""Clean the combined Rob/Lum conversations.

What it does
------------
* speaker turns    — turns the inline "Speaker 1 / Speaker 2" markers into real
                     line-separated turns, and drops runs of the same label
* word fixes       — repairs ASR mishearings that were verified in context
                     (hypernexis -> HyperNexus, tournexia -> TormentNexus, ...)
* stutters         — collapses duplicated adjacent words and 2-word phrases
* punctuation      — normalises spacing around punctuation, tidies runs left
                     behind by the stutter pass
* capitalisation   — sentence-initial capitals, "i" -> "I"
* terminals        — a full stop at the end of a turn that has none

Deliberately conservative: it will not invent sentence boundaries inside a
ramble, because guessing wrong is worse than leaving one long turn.

Input : ~/Videos/combined_conversations.txt
Output: ~/Videos/combined_conversations_clean.txt
"""

import os
import re
import sys
import time

V = os.path.abspath(
    os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "Videos")
)
SRC = os.path.join(V, "combined_conversations.txt")
OUT = os.path.join(V, "combined_conversations_clean.txt")

# ---------------------------------------------------------------- corrections
# Only entries verified by reading the surrounding context.
CORRECTIONS = [
    (r"\bhypernexis\b", "HyperNexus"),
    (r"\bhypernaxis\b", "HyperNexus"),
    (r"\bhypernexus\b", "HyperNexus"),
    (r"\bhyper nexus\b", "HyperNexus"),
    (r"\btournexia\b", "TormentNexus"),
    (r"\btorment nexis\b", "TormentNexus"),
    (r"\balum studios?\b", "LM Studio"),
    (r"(?<![\w'])\bcolumn\b(?![\w'])(?=[.,]?\s+We were talking about)", "Columbine"),
    (r"\bim\b", "I'm"),
    (r"\bi\b", "I"),
    (r"\bi'm\b", "I'm"),
    (r"\bi've\b", "I've"),
    (r"\bi'll\b", "I'll"),
    (r"\bi'd\b", "I'd"),
    (r"\bdont\b", "don't"),
    (r"\bcant\b", "can't"),
    (r"\bwont\b", "won't"),
    (r"\bdoesnt\b", "doesn't"),
    (r"\bdidnt\b", "didn't"),
    (r"\bisnt\b", "isn't"),
    (r"\bwasnt\b", "wasn't"),
    (r"\bwouldnt\b", "wouldn't"),
    (r"\bcouldnt\b", "couldn't"),
    (r"\bshouldnt\b", "shouldn't"),
    (r"\bthats\b", "that's"),
    (r"\bwhats\b", "what's"),
    (r"\btheres\b", "there's"),
    (r"\btheyre\b", "they're"),
    (r"\byoure\b", "you're"),
    (r"\byouve\b", "you've"),
    (r"\bweve\b", "we've"),
    (r"\bits\b(?=\s+(?:not|a|the|just|like|going|gonna|really|so|been|about))", "it's"),
]

TAG_RE = re.compile(r"\*[^*]*\*|\[[^\]]*\]", re.S)
SPEAKER_RE = re.compile(r"(?i)\bspeaker\s*([0-9]+)\b\s*:?\s*")
WORD_RE = re.compile(r"([A-Za-z0-9']+)")
TERMINAL = (".", "!", "?", "…")


def collapse_repeats(text, rounds=6):
    """Drop duplicated adjacent words / 2-word phrases.

    Only tokens containing a letter take part, so digit runs such as the
    "09" in a date are never mistaken for a stutter.
    """

    def alpha(tok):
        return any(c.isalpha() for c in tok)

    for _ in range(rounds):
        parts = WORD_RE.split(text)
        widx = list(range(1, len(parts), 2))
        wl = [parts[i].lower() for i in widx]
        drop = set()

        j = 0
        while j + 3 < len(wl):
            if (
                wl[j] == wl[j + 2]
                and wl[j + 1] == wl[j + 3]
                and alpha(wl[j])
                and alpha(wl[j + 1])
            ):
                drop.add(widx[j + 2])
                drop.add(widx[j + 3])
                j += 4
            else:
                j += 1

        surviving = [i for i in widx if i not in drop]
        sl = [parts[i].lower() for i in surviving]
        for k in range(len(surviving) - 1):
            if sl[k] == sl[k + 1] and alpha(sl[k]):
                drop.add(surviving[k + 1])

        if not drop:
            break
        for i in sorted(drop, reverse=True):
            parts[i] = ""
        text = "".join(parts)
    return text


def fix_spacing(text):
    """Normalise spaces and punctuation spacing. Newlines untouched."""
    text = re.sub(r"[ \t]+", " ", text)
    text = re.sub(r" +([.,!?;:])", r"\1", text)
    text = re.sub(r"([.,!?;:])(?=[A-Za-z])", r"\1 ", text)
    text = re.sub(r"\.{3,}", "…", text)
    for _ in range(8):
        before = text
        text = re.sub(r"([,;:])(?:[ \t]*\1)+", r"\1", text)
        text = re.sub(r"\.[ \t]*\.", ".", text)
        text = re.sub(r",[ \t]*,", ",", text)
        text = re.sub(r",[ \t]*([.!?…])", r"\1", text)
        text = re.sub(r"([.!?…])[ \t]*,", r"\1", text)
        text = re.sub(r"([;:])[ \t]*([.,;:!?…])", r"\2", text)
        if text == before:
            break
    text = re.sub(r"\s+([’'])", r"\1", text)
    text = re.sub(r"([(])\s+", r"\1", text)
    # punctuation pile-ups the ASR emits: "right?." "Nothing.??.???"
    text = re.sub(r"([?!])\.[?!.]*", r"\1", text)
    text = re.sub(r"\.\?+", "?", text)
    text = re.sub(r"([?!])\1{1,}", r"\1", text)
    # stray dash-led fragments: "- Yeah." at the start of a line -> "Yeah."
    text = re.sub(r"(?m)^\s*-\s*", "", text)
    text = re.sub(r"\s*-\s*(?=[A-Z])", " ", text)
    return text


def capitalise(text):
    """Capitalise sentence starts, including after speaker labels."""
    # after a terminal + space
    text = re.sub(
        r"([.!?…]\s+)([a-z])", lambda m: m.group(1) + m.group(2).upper(), text
    )
    # start of each line
    text = re.sub(
        r"(?m)^(Speaker \d+:\s*)([a-z])",
        lambda m: m.group(1) + m.group(2).upper(),
        text,
    )
    text = re.sub(r"(?m)^([a-z])", lambda m: m.group(1).upper(), text)
    return text


def apply_corrections(text):
    for pat, rep in CORRECTIONS:
        text = re.sub(pat, rep, text)
    return text


def protect_tags(text):
    """Swap *music* / [laughs] spans for private-use placeholder characters.

    The stutter pass works on words, so collapsing a run of "*music* *music*"
    would delete the word and leave the surrounding asterisks as "**". The
    placeholders are not word characters, so they pass through untouched.
    """
    tags = []

    def keep(match):
        tags.append(match.group(0))
        return chr(0xE000 + len(tags) - 1)

    return TAG_RE.sub(keep, text), tags


def restore_tags(text, tags):
    for i, tag in enumerate(tags):
        text = text.replace(chr(0xE000 + i), tag)
    return text


def collapse_sentence_loops(text, rounds=8):
    """Collapse a sentence repeated back-to-back.

    Whisper-style ASR gets stuck and re-emits the same line hundreds of times
    (the source has "He doesn't really know what he's fighting." 516 times).
    Word-level collapsing cannot see that, so it is done here.
    """
    for _ in range(rounds):
        before = text
        text = re.sub(r"(?i)\b([^.!?\n]{15,180}[.!?])(?:\s*\1)+", r"\1", text)
        if text == before:
            break
    return text


def clean_turn(txt):
    """Clean the text of one speaker turn."""
    # ASR line wrapping is not punctuation: join wrapped lines into the turn
    s = re.sub(r"\s*\n\s*", " ", txt)
    s = apply_corrections(s)
    s = collapse_sentence_loops(s)

    s, tags = protect_tags(s)
    s = collapse_repeats(s)
    s = fix_spacing(s)
    s = capitalise(s)
    s = restore_tags(s, tags)

    # residue of a collapsed word: a token that is now only punctuation
    s = re.sub(r"(?:^|\s)[.,;:!?…\-–—]+(?=\s|$)", " ", s)
    s = re.sub(r"\s{2,}", " ", s).strip()
    # a full stop after a closing tag reads wrong ("*music*.")
    s = re.sub(r"(\*[^*\n]+\*|\[[^\]\n]+\])[ \t]*\.$", r"\1", s)
    return s


def clean_body(body):
    """Clean one transcript body, preserving its speaker-turn structure.

    Punctuation is applied per *turn*, not per line. The raw ASR output is hard
    wrapped mid-sentence, so punctuating each line would drop full stops into
    the middle of a sentence ("...nothing else in the. Same category...").
    """
    t = body

    # 0. drop the per-file header the combine step emitted ("File : ... bytes
    #    modified <date>" plus its rule line). It carries no spoken content and
    #    the date is a duplication magnet for the stutter pass.
    t = re.sub(r"(?m)^File\s*:.*\n=+\s*\n", "", t, count=1)
    t = re.sub(r"(?m)^=+\s*$", "", t)
    t = re.sub(r"(?m)^\s*-\s*", "", t)  # stray leading dashes on ASR lines
    t = t.strip()

    # 1. mark speaker turns inline, then split on them
    t = SPEAKER_RE.sub(lambda m: "\x01" + m.group(1) + "\x01", t)
    parts = re.split(r"\x01(\d+)\x01", t)

    turns = []
    if parts[0].strip():
        turns.append((None, parts[0]))
    for i in range(1, len(parts), 2):
        turns.append((parts[i], parts[i + 1] if i + 1 < len(parts) else ""))

    # 2. clean each turn, merging consecutive turns by the same speaker
    merged = []
    for num, txt in turns:
        if merged and merged[-1][0] == num:
            merged[-1] = (num, merged[-1][1] + " " + txt)
        else:
            merged.append((num, txt))

    out = []
    for num, txt in merged:
        s = clean_turn(txt)
        if num:
            s = "Speaker " + num + ": " + s
        s = s.rstrip()
        if (
            s
            and s[-1] not in TERMINAL
            and not s.endswith(":")
            and not s.endswith(("*", "]"))
        ):
            s += "."
        if s.strip():
            out.append(s)

    out_text = "\n\n".join(out).strip()

    # A loop that alternates speakers ("... X. Speaker 4: X. Speaker 2: X. ...")
    # slips past the per-turn pass above, because each copy sits in its own turn.
    for _ in range(8):
        before = out_text
        out_text = re.sub(
            r"(?i)([^.!?\n]{15,180}[.!?])(?:[ \t]*(?:\n\n)?Speaker \d+:[ \t]*\1)+",
            r"\1",
            out_text,
        )
        if out_text == before:
            break

    return out_text.strip()


def main():
    if not os.path.isfile(SRC):
        print(f"error: {SRC} not found — run combine_conversations.py first")
        return 1
    try:
        with open(SRC, encoding="utf-8") as fh:
            src = fh.read()
    except OSError as exc:
        print(f"error: cannot read {SRC}: {exc}")
        return 1

    # split the combined document into (header, blocks)
    bar = "=" * 78
    parts = re.split(r"(?m)^\[(\d+)/(\d+)\]\s+(.+)$", src)
    # parts = [preamble, n, total, name, body, n, total, name, body, ...]

    if len(parts) < 5:
        print("error: could not parse the combined file (no [n/total] blocks)")
        return 1

    preamble = parts[0]
    blocks = []
    for i in range(1, len(parts), 4):
        n, total, name, body = parts[i], parts[i + 1], parts[i + 2], parts[i + 3]
        # body ends with the trailing bar before the next "[n/total]"
        body = re.sub(r"\n?" + re.escape(bar) + r"\s*$", "", body)
        blocks.append((n, total, name.strip(), body))

    stats = []
    cleaned_blocks = []
    for n, total, name, body in blocks:
        cleaned = clean_body(body)
        stats.append((name, len(body), len(cleaned)))
        cleaned_blocks.append((n, total, name, cleaned))

    total = len(cleaned_blocks)
    stamp = time.strftime("%Y-%m-%d %H:%M:%S")

    try:
        out_fh = open(OUT, "w", encoding="utf-8", newline="\n")
    except OSError as exc:
        print(f"error: cannot write {OUT}: {exc}")
        return 1

    with out_fh as fh:
        fh.write(bar + "\n")
        fh.write("COMBINED CONVERSATIONS — CLEANED\n")
        fh.write(f"Generated : {stamp}\n")
        fh.write("Source    : combined_conversations.txt\n")
        fh.write(f"Files     : {total} conversations\n")
        fh.write(
            "Cleaning  : speaker turns split onto their own lines; ASR word fixes\n"
        )
        fh.write(
            "            (HyperNexus, TormentNexus, LM Studio, Columbine, contractions);\n"
        )
        fh.write(
            "            stutters collapsed; punctuation spacing normalised; sentence\n"
        )
        fh.write(
            "            capitals and terminal full stops added. Sentence boundaries\n"
        )
        fh.write("            inside a ramble are left alone rather than guessed at.\n")
        fh.write(bar + "\n\n")

        fh.write("CONTENTS\n")
        fh.write("-" * 78 + "\n")
        for i, (n, _t, name, cleaned) in enumerate(cleaned_blocks, 1):
            fh.write(f"{i:4d}. {name:<46} {len(cleaned):>9,} chars\n")
        fh.write("\n")

        for i, (n, _t, name, cleaned) in enumerate(cleaned_blocks, 1):
            fh.write("\n" + bar + "\n")
            fh.write(f"[{i}/{total}]  {name}\n")
            fh.write(bar + "\n\n")
            fh.write(cleaned if cleaned else "(empty)")
            fh.write("\n")

        fh.write("\n" + bar + "\n")
        fh.write(f"END — {total} cleaned conversations\n")
        fh.write(bar + "\n")

    before = sum(s[1] for s in stats)
    after = sum(s[2] for s in stats)
    print(f"wrote {OUT}")
    print(f"  conversations : {total}")
    print(f"  chars before  : {before:,}")
    print(f"  chars after   : {after:,}   ({(after - before) / before * 100:+.1f}%)")
    print(f"  out bytes     : {os.path.getsize(OUT):,}")
    print()

    # proof the corrections landed
    print("=== correction check ===")
    cleaned_all = "".join(b[3] for b in cleaned_blocks)
    for term in [
        "HyperNexus",
        "TormentNexus",
        "LM Studio",
        "Columbine",
        "hypernexis",
        "tournexia",
        "alum studios",
    ]:
        print(f"  {cleaned_all.count(term):5d}  {term}")
    print()
    print("=== sample: first 500 chars of block 1 ===")
    print(
        "  "
        + (cleaned_blocks[0][3][:500].replace("\n", "\n  ") if cleaned_blocks else "")
    )
    return 0


if __name__ == "__main__":
    sys.exit(main())
