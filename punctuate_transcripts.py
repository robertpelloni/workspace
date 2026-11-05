#!/usr/bin/env python3
"""Give the under-punctuated transcripts real sentence punctuation, using a
local LM Studio model.

The deterministic cleaner in clean_conversations.py handles spacing, capitals,
terminal full stops, stutters and ASR loops, but it deliberately refuses to
guess where sentences end inside an unpunctuated ramble. Some recordings have
no punctuation at all in the source, which leaves them unreadable.

This pass sends those blocks to a local model and asks it to add punctuation
and capitalisation *without changing a single word*. Every chunk is verified
afterwards: the word sequence must match the input exactly, or the chunk is
discarded and the original kept. Nothing is invented and nothing is dropped.

Output: ~/Videos/combined_conversations_final.txt
"""

import json
import os
import re
import sys
import time
import urllib.request

V = os.path.abspath(
    os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "Videos")
)
SRC = os.path.join(V, "combined_conversations_clean.txt")
OUT = os.path.join(V, "combined_conversations_final.txt")

ENDPOINT = "http://127.0.0.1:1234/v1/chat/completions"
MODEL = "gemma-4-e2b-it-ultra-uncensored-heretic-ud"

# blocks below this many punctuation marks per 100 chars get the LLM treatment
DENSITY_THRESHOLD = 1.2
CHUNK_CHARS = 320

INSTRUCTIONS = (
    "Punctuate and capitalise this speech-to-text transcript.\n"
    "Rules:\n"
    "- Keep every word exactly as it is, in the same order, including profanity.\n"
    "- Do not add, remove, replace, censor or reorder any word.\n"
    "- ONLY add punctuation (. , ? !) and capital letters.\n"
    "- KEEP the 'Speaker N:' labels at the start of each turn, exactly as written.\n"
    "- Do not fix or join words (write 'chat gpt', not 'ChatGPT').\n"
    "- Output ONLY the punctuated text. No options, no explanation, no quotes,\n"
    "  no markdown, no headings.\n\n"
)


def words_of(text):
    """Comparable word stream: speaker labels excluded.

    The model is told to keep them, but a dropped "Speaker 1" should not make
    an otherwise perfect chunk fail verification. Everything else must match
    exactly, in order.
    """
    text = re.sub(r"(?i)\bspeaker\s*\d+\b", " ", text)
    return re.findall(r"[a-z0-9']+", text.lower())


def call_model(text, timeout=240):
    body = {
        "model": MODEL,
        "messages": [{"role": "user", "content": INSTRUCTIONS + text}],
        "temperature": 0.0,
        "max_tokens": 2000,
        "reasoning_effort": "none",  # without this the model burns ~300 thinking tokens
    }
    req = urllib.request.Request(
        ENDPOINT,
        data=json.dumps(body).encode(),
        headers={"Content-Type": "application/json"},
    )
    try:
        raw = urllib.request.urlopen(req, timeout=timeout).read().decode()
        d = json.loads(raw)
        return (d["choices"][0]["message"].get("content") or "").strip()
    except (OSError, ValueError, KeyError, IndexError) as exc:
        raise RuntimeError(
            f"LM Studio call failed: {type(exc).__name__}: {exc}"
        ) from exc


def chunk_turns(text, limit=CHUNK_CHARS):
    """Split into chunks of at most `limit` characters.

    Turns are the natural unit, but a block with no blank lines is one giant
    paragraph, so anything still too long is cut at a word boundary.
    """
    units = []
    for turn in re.split(r"\n\s*\n", text):
        t = turn.strip()
        if not t:
            continue
        while len(t) > limit:
            cut = t.rfind(" ", 0, limit)
            if cut <= 0:
                cut = limit
            units.append(t[:cut].rstrip())
            t = t[cut:].lstrip()
        if t:
            units.append(t)

    chunks, cur = [], ""
    for u in units:
        if cur and len(cur) + len(u) + 2 > limit:
            chunks.append(cur)
            cur = u
        else:
            cur = (cur + "\n\n" + u) if cur else u
    if cur:
        chunks.append(cur)
    return chunks


def punctuate_chunk(chunk, stats, depth=0):
    """Punctuate one chunk, verifying the words survive.

    Larger chunks make this small model drop words, so a mismatch is not
    treated as a failure: the chunk is halved and retried, down to a floor.
    Only if that still fails is the original text kept.
    """
    w_in = words_of(chunk)
    if not w_in:
        return chunk  # nothing but tags/labels

    stats["chunks"] += 1
    try:
        result = call_model(chunk)
    except Exception as exc:
        print(f"      ! model error: {str(exc)[:70]}")
        result = None

    if result is not None and words_of(result) == w_in:
        stats["ok"] += 1
        return result

    # too big / altered — split and retry
    if depth < 3 and len(chunk) > 140:
        parts = chunk_turns(chunk, limit=max(120, len(chunk) // 2))
        if len(parts) > 1:
            stats["resplit"] += 1
            return "\n\n".join(punctuate_chunk(p, stats, depth + 1) for p in parts)

    stats["rejected"] += 1
    print(f"      ! kept original ({len(w_in)} words)")
    return chunk


def punctuate(text):
    """Return (new_text, stats)."""
    stats = {"chunks": 0, "ok": 0, "rejected": 0, "resplit": 0}
    return "\n\n".join(punctuate_chunk(c, stats) for c in chunk_turns(text)), stats


def density(body):
    core = re.sub(r"(?m)^Speaker \d+:\s*", "", body)
    if len(core) < 60:
        return 99.0
    return len(re.findall(r"[.,!?;:]", core)) / len(core) * 100


def main():
    if not os.path.isfile(SRC):
        print(f"error: {SRC} not found — run clean_conversations.py first")
        return 1
    try:
        with open(SRC, encoding="utf-8") as fh:
            src = fh.read()
    except OSError as exc:
        print(f"error: cannot read {SRC}: {exc}")
        return 1

    # check the model is reachable
    try:
        urllib.request.urlopen("http://127.0.0.1:1234/v1/models", timeout=10)
    except Exception as exc:
        print(f"error: LM Studio not reachable on 127.0.0.1:1234 ({exc})")
        return 1

    bar = "=" * 78
    parts = re.split(r"(?m)^\[(\d+)/(\d+)\]\s+(.+)$", src)
    if len(parts) < 5:
        print("error: could not parse blocks")
        return 1

    preamble = parts[0]
    blocks = []
    for i in range(1, len(parts), 4):
        name = parts[i + 2].strip()
        body = parts[i + 3]
        body = re.sub(r"\n?" + re.escape(bar) + r"\s*$", "", body)
        blocks.append((name, body.strip("\n")))

    todo = [(n, b) for n, b in blocks if density(b) < DENSITY_THRESHOLD]
    print(f"blocks total          : {len(blocks)}")
    print(
        f"below {DENSITY_THRESHOLD} marks/100 chars : {len(todo)}  <- will be punctuated"
    )
    print(f"chars to process      : {sum(len(b) for _, b in todo):,}")
    print(f"model                 : {MODEL}")
    print()

    t0 = time.time()
    fixed = {}
    for idx, (name, body) in enumerate(todo, 1):
        d = density(body)
        print(f"  [{idx}/{len(todo)}] {name}  ({len(body):,} chars, {d:.2f} marks/100)")
        new, st = punctuate(body)
        fixed[name] = new
        print(
            f"        chunks={st['chunks']} ok={st['ok']} rejected={st['rejected']}"
            f"  elapsed={time.time() - t0:.0f}s"
        )
        sys.stdout.flush()

    stamp = time.strftime("%Y-%m-%d %H:%M:%S")
    try:
        fh_out = open(OUT, "w", encoding="utf-8", newline="\n")
    except OSError as exc:
        print(f"error: cannot write {OUT}: {exc}")
        return 1

    with fh_out as fh:
        fh.write(bar + "\n")
        fh.write("COMBINED CONVERSATIONS — FINAL\n")
        fh.write(f"Generated : {stamp}\n")
        fh.write(f"Files     : {len(blocks)} conversations\n")
        fh.write("Pipeline  : 1) filtered to Rob/Lum conversations only\n")
        fh.write(
            "            2) deterministic clean (spacing, stutters, ASR-loop removal,\n"
        )
        fh.write("               capitals, terminal full stops, verified word fixes)\n")
        fh.write(
            "            3) local-model punctuation pass on the "
            f"{len(todo)} under-punctuated blocks, with\n"
        )
        fh.write(
            "               every chunk verified word-for-word against the input\n"
        )
        fh.write(bar + "\n\n")

        fh.write("CONTENTS\n")
        fh.write("-" * 78 + "\n")
        for i, (name, body) in enumerate(blocks, 1):
            b = fixed.get(name, body)
            tag = "  [punctuated]" if name in fixed else ""
            fh.write(f"{i:4d}. {name:<44} {len(b):>9,} chars{tag}\n")
        fh.write("\n")

        for i, (name, body) in enumerate(blocks, 1):
            b = fixed.get(name, body)
            fh.write("\n" + bar + "\n")
            fh.write(f"[{i}/{len(blocks)}]  {name}\n")
            fh.write(bar + "\n\n")
            fh.write(b if b.strip() else "(empty)")
            fh.write("\n")

        fh.write("\n" + bar + "\n")
        fh.write(f"END — {len(blocks)} conversations\n")
        fh.write(bar + "\n")

    print()
    print(f"wrote {OUT}  ({os.path.getsize(OUT):,} bytes)")
    print(f"  total time: {(time.time() - t0) / 60:.1f} min")
    return 0


if __name__ == "__main__":
    sys.exit(main())
