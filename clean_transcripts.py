#!/usr/bin/env python3
"""
Clean up transcripts.txt into readable paragraphs.

IMPORTANT: <br> tags and WordPress block markup are PRESERVED exactly.
Only the text *between* tags is cleaned.

Input:  ~/Downloads/transcripts.txt
Output: ~/Downloads/transcripts_clean.txt   (WordPress-ready, markup intact)
        ~/Downloads/transcripts_clean_plain.txt  (readable plain text preview)

Transformations (text only, never tags):
  - Collapse consecutive repeated words (stutters): "is is" -> "is"
  - Collapse repeated 2-word phrases: "you know you know" -> "you know"
  - Normalize spacing / punctuation spacing
  - Capitalize sentence starts, standalone "i" -> "I"
  - For raw ASR sections, insert conservative sentence-ending periods
"""

import os
import re

SRC = os.path.expanduser(r"~\Downloads\transcripts.txt")
OUT_TXT = os.path.expanduser(r"~\Downloads\transcripts_clean.txt")
OUT_PLAIN = os.path.expanduser(r"~\Downloads\transcripts_clean_plain.txt")

# ------------------------------------------------------------------ tags

# Matches wp comments first, then any html/open/close tag
TAG_RE = re.compile(r"<!--.*?-->|</?[a-zA-Z][^>]*>", re.S)
SENTINEL_RE = re.compile(r"\x00(\d+)\x00")
WORD_RE = re.compile(r"([A-Za-z0-9']+)")


def protect_tags(text):
    """Replace every tag with a \\x00N\\x00 sentinel; return (text, tags)."""
    tags = []

    def _sub(m):
        tags.append(m.group(0))
        return f"\x00{len(tags) - 1}\x00"

    return TAG_RE.sub(_sub, text), tags


def restore_tags(text, tags):
    """Put the original tags back in place of sentinels."""

    def _sub(m):
        try:
            i = int(m.group(1))
        except (TypeError, ValueError):
            return m.group(0)
        return tags[i] if 0 <= i < len(tags) else m.group(0)

    return SENTINEL_RE.sub(_sub, text)


def protect(text):
    return protect_tags(text)


# Separator = whitespace or a tag sentinel
SEP = r"(?:\s|\x00\d+\x00)"

PRONOUN_MAP = {
    "i": "I",
    "i'm": "I'm",
    "i've": "I've",
    "i'll": "I'll",
    "i'd": "I'd",
    "im": "I'm",
    "ive": "I've",
    "ill": "I'll",
    "id": "I'd",
}

# Words that commonly begin a new spoken sentence (used for raw ASR only)
SENTENCE_STARTERS = {
    "i",
    "you",
    "we",
    "they",
    "he",
    "she",
    "it",
    "that",
    "this",
    "the",
    "but",
    "so",
    "because",
    "and",
    "like",
    "well",
    "okay",
    "yeah",
    "no",
    "what",
    "when",
    "where",
    "why",
    "how",
    "who",
    "if",
    "then",
    "now",
    "there",
    "here",
    "just",
    "really",
    "actually",
    "basically",
    "maybe",
    "probably",
    "obviously",
    "anyway",
    "however",
    "though",
    "although",
    "can",
    "do",
    "does",
    "did",
    "is",
    "are",
    "was",
    "were",
    "have",
    "has",
    "had",
    "would",
    "could",
    "should",
    "will",
    "let",
    "look",
    "listen",
    "see",
    "know",
    "think",
    "mean",
    "get",
    "got",
    "go",
    "going",
    "come",
    "right",
    "ok",
    "sorry",
    "thank",
    "thanks",
    "please",
    "hey",
    "hi",
    "yes",
    "never",
    "always",
    "sometimes",
    "everybody",
    "everyone",
    "somebody",
    "someone",
    "nobody",
    "nothing",
    "everything",
    "something",
    "anything",
    "people",
    "kids",
    "god",
    "jesus",
    "man",
    "dude",
    "bro",
}

TERMINAL = (".", "!", "?", "…")


# --------------------------------------------------------- text transforms


def collapse_repeats(text, rounds=6):
    """Drop duplicated adjacent words / 2-word phrases. Tags are untouched."""
    for _ in range(rounds):
        parts = WORD_RE.split(text)
        widx = list(range(1, len(parts), 2))
        wl = [parts[i].lower() for i in widx]
        drop = set()

        # 2-word phrase repeats: "you know you know" -> "you know"
        j = 0
        while j + 3 < len(wl):
            if wl[j] == wl[j + 2] and wl[j + 1] == wl[j + 3]:
                drop.add(widx[j + 2])
                drop.add(widx[j + 3])
                j += 4
            else:
                j += 1

        # single-word repeats on whatever survived
        surviving = [i for i in widx if i not in drop]
        sl = [parts[i].lower() for i in surviving]
        for k in range(len(surviving) - 1):
            if sl[k] == sl[k + 1]:
                drop.add(surviving[k + 1])

        if not drop:
            break
        for i in sorted(drop, reverse=True):
            parts[i] = ""
        text = "".join(parts)
    return text


def fix_spacing(text):
    """Normalize spaces/tabs and punctuation spacing. Newlines/tags untouched."""
    text = re.sub(r"[ \t]+", " ", text)
    text = re.sub(r" +([.,!?;:])", r"\1", text)  # no space before
    text = re.sub(r"([.,!?;:])(?=[A-Za-z])", r"\1 ", text)  # space after
    text = re.sub(r"\.{3,}", "…", text)
    # collapse punctuation runs left behind by word collapsing (loop: long
    # runs such as "It's, it's, it's," leave many commas that need several passes)
    for _ in range(8):
        before = text
        text = re.sub(r"([,;:])(?:[ \t]*\1)+", r"\1", text)  # ",,,," -> ","
        text = re.sub(r"\.[ \t]*\.", ".", text)
        text = re.sub(r",[ \t]*,", ",", text)
        text = re.sub(r",[ \t]*([.!?…])", r"\1", text)  # "Yeah,." -> "Yeah."
        text = re.sub(r"([.!?…])[ \t]*,", r"\1", text)  # "Yeah.," -> "Yeah."
        text = re.sub(r"([;:])[ \t]*([.,;:!?…])", r"\2", text)
        text = re.sub(r"([,;:])[ \t]+([.!?…])", r"\2", text)
        if text == before:
            break
    text = re.sub(r"(?:…[ \t]*\.)|(?:\.\s*…)", "…", text)
    text = re.sub(r"\s+([’'])", r"\1", text)
    text = re.sub(r"([(])\s+", r"\1", text)
    return text


def looks_raw(line):
    """True for unpunctuated, mostly-lowercase ASR output lines."""
    body = SENTINEL_RE.sub("", line).strip()
    letters = re.sub(r"[^A-Za-z]", "", body)
    if len(letters) < 8:
        return False
    if body.endswith(TERMINAL):
        return False
    punct = sum(body.count(c) for c in ".!?,;:")
    upper = sum(1 for c in letters if c.isupper())
    return punct == 0 and (upper / len(letters)) < 0.06


def polish_raw_line(line):
    """Capitalize a raw ASR line and give it a terminal period."""
    if not looks_raw(line):
        return line

    # trailing tags (e.g. <br>) that must stay at the very end
    m_tail = re.search(rf"(?:{SEP})*$", line)
    tail = m_tail.group(0) if m_tail else ""
    head = line[: len(line) - len(tail)] if tail else line

    head = head.strip()
    if not head:
        return line

    # capitalize first alphabetic character
    m_first = re.search(r"[a-zA-Z]", head)
    if m_first:
        i = m_first.start()
        head = head[:i] + head[i].upper() + head[i + 1 :]

    if not head.endswith(TERMINAL):
        head += "."
    return head + tail


def capitalize(text):
    """Capitalize sentence starts (across tags) and fix lowercase pronouns."""

    def _pron(m):
        w = m.group(0).lower()
        return PRONOUN_MAP.get(w, m.group(0))

    text = re.sub(
        r"\b(i|i'm|i've|i'll|i'd|im|ive|ill|id)\b", _pron, text, flags=re.IGNORECASE
    )

    def _cap(m):
        return m.group(1) + m.group(2).upper()

    text = re.sub(rf"(^|[.!?…](?:{SEP})+)([a-z])", _cap, text)
    return text


def add_periods(text, min_gap=8):
    """Apply per-line ASR polish to a block of protected text."""
    return "\n".join(polish_raw_line(ln) for ln in text.split("\n"))


def to_plain(text):
    """Render the markup version as readable plain text (for preview only)."""
    tags = [t for t in TAG_RE.findall(text)]
    out = text
    # paragraph-ish break for double <br>, line break for single
    out = re.sub(r"(?:<br\s*/?>\s*){2,}", "\n\n", out)
    out = re.sub(r"<br\s*/?>", "\n", out)
    out = TAG_RE.sub("", out)
    out = re.sub(r"\n{3,}", "\n\n", out)
    out = "\n".join(ln.strip() for ln in out.split("\n"))
    out = re.sub(r"\n{3,}", "\n\n", out)
    return out.strip(), len(tags)


def clean_document(text):
    """Clean one document/section, preserving all markup."""
    protected, tags = protect(text)

    protected = collapse_repeats(protected)
    protected = fix_spacing(protected)
    protected = add_periods(protected)
    protected = capitalize(protected)
    # collapse again last, then re-tidy the punctuation it may leave behind
    protected = collapse_repeats(protected)
    protected = fix_spacing(protected)

    return restore_tags(protected, tags)


def main():
    try:
        with open(SRC, encoding="utf-8", errors="replace") as f:
            content = f.read()
    except OSError as exc:
        print(f"ERROR: cannot read {SRC}: {exc}")
        return

    # Split on FILE: markers but keep them in the output
    pieces = re.split(r"(FILE:\s*\S+?\.txt)", content)
    out = [clean_document(pieces[0])]
    for i in range(1, len(pieces) - 1, 2):
        marker, body = pieces[i], pieces[i + 1]
        out.append(marker)
        out.append(clean_document(body))

    cleaned = "".join(out)

    try:
        with open(OUT_TXT, "w", encoding="utf-8", newline="") as f:
            f.write(cleaned)
    except OSError as exc:
        print(f"ERROR: cannot write {OUT_TXT}: {exc}")
        return

    plain, ntags = to_plain(cleaned)
    try:
        with open(OUT_PLAIN, "w", encoding="utf-8", newline="") as f:
            f.write(plain + "\n")
    except OSError as exc:
        print(f"ERROR: cannot write {OUT_PLAIN}: {exc}")
        return

    before = content.count("<br")
    after = cleaned.count("<br")
    print(f"<br> tags before : {before}")
    print(f"<br> tags after  : {after}")
    print(
        f"wp:paragraph     : {content.count('wp:paragraph')} -> "
        f"{cleaned.count('wp:paragraph')}"
    )
    print(f"chars            : {len(content):,} -> {len(cleaned):,}")
    print(f"Wrote: {OUT_TXT}")
    print(f"Wrote: {OUT_PLAIN}")


if __name__ == "__main__":
    main()
