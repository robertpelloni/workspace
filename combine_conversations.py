#!/usr/bin/env python3
"""Combine only the transcripts that are the user's own conversations.

Rob (the user) talks with "Lum". Anything that is a recording of somebody
else's material — a documentary, a YouTube video, an ad, a song, game audio,
or one of the ASMR/porn audios — is left out, as is anything with no actual
speech in it.

Writes: ~/Videos/combined_conversations.txt
Prints: a full breakdown of what was kept and what was dropped, with reasons.
"""

import os
import re
import sys
import time

V = os.path.abspath(
    os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "Videos")
)
OUT = os.path.join(V, "combined_conversations.txt")

# --- dropped because it is adult/ASMR audio, not the user's conversation -----
ADULT = {
    "BeatrixVale [F4M] HFO Precum Milking [Mommy-Domme][hands free orgasm]"
    "[msub][Fdom][gentle femdom][binaural][ASMR][precum milking] .txt": "adult ASMR audio",
    "Obey-Submit-My-Good-Boy-MP3.txt": "adult ASMR audio",
    "The-Ultimate-Cuckold-Experience-F4M-Tied-to-Chair-Fdom-Femdom-Cuckold-NTR-"
    "Emotional-Sadism-Mindbreak-Orgy-Voyeur-SPH-Humiliation-Size-Comparison-"
    "Blowjob-Big-Cock-Worship-PIV-Creampie-Cleanup-Good-Boy-1.txt": "adult ASMR audio",
    "Ultimate Cuckold Experience F4M Tied to Chair Fdom Femdom Cuckold NTR "
    "Emotional Sadism Mindbreak Orgy Voyeur SPH Humiliation Size Comparison "
    "Blowjob Big Cock Worship PIV  Cleanup Good Boy.txt": "adult ASMR audio",
    "[F4M] - Drop for Teacher - [Variant][Binaural];[Script];[Fdom][Hypnosis].txt": "adult ASMR audio",
    "[F4M] - Take Your Medicine - [Variant][All Parts][Binaural][Haptic];[Script "
    "Fill][broken][Alz];[Series][Take Your Medicine][#1];[Fdom][Hypnosis][ASMR].txt": "adult ASMR audio",
    "[F4M] 2 Hours of Therapy with Penelope [Over 2 Hours] [Possible Multiple HFO] "
    "[Hypnosis] [CNC] [ASMR] [Deep trance] [Gentle Fdom] [Snaps] [Drugged] [Trigger "
    "play] [English Accent] [Relentless] [Throb [Twitch] [Vibration S.txt": "adult ASMR audio",
    "[F4M] You Cant Stop Me [HFO] [Binaurals] [Hypnosis] [ASMR] [Female Domination] "
    "[Snaps] [Layers] [Triggers] [Accent] [Two Versions] [Power and Control] [buzz] "
    "[Drop] [Power] [Throb] [Helpless] [trigger play] [whisper].txt": "adult ASMR audio",
    "[F4M] [Script Fill] 'Milking Time, at the Femboy Farm!~' [Gentle Femdom] [MDlb] "
    "[Milking] [Femboy] [All-Fours Handjob] [Assplay] [Livestock-Play] [Cow-Boy] [SPE] "
    "[Small Penis Praise Tease] [Encouragement] [Strapon] [As.txt": "adult ASMR audio",
    "[F4S] - Submissive Sissy Slut - [Script Fill][u_SuckMyScript];[Fdom][Hypnosis].txt": "adult ASMR audio",
}

# --- dropped because the content is somebody else's, not their conversation --
THIRD_PARTY = {
    "20260820_215506.txt": "Lindsay Lohan / Paris Hilton documentary narration",
    "IMG_2949.txt": "'This is a production of the U.S. Department of State' — a government video",
    "tactiq-free-transcript-_CL19Vq_ers.txt": "tactiq YouTube transcript of someone else's video",
}

# --- dropped because they are derivatives / not transcripts -----------------
NOT_TRANSCRIPTS = {
    "combined_video_transcripts.txt": "my own previous output",
    "combined_transcript.txt": "earlier bundle",
    "video_transcripts.txt": "earlier bundle",
    "video_transcripts_corrected.txt": "earlier bundle",
    "transcript.txt": "LLM-cleaned derivative",
    "transcript1.txt": "LLM-cleaned derivative",
    "transcript2.txt": "LLM-cleaned derivative",
    "transcript3.txt": "LLM-cleaned derivative",
    "transcript4.txt": "LLM-cleaned derivative",
    "transcript5.txt": "LLM-cleaned derivative",
    "cookies.txt": "not a transcript",
    "ytdl-archive.txt": "not a transcript",
    "4chan.txt": "not a transcript",
    "speaker_mapping_report.txt": "not a transcript",
}

# words that survive tag-stripping and mean "nobody actually spoke"
MUSIC_WORDS = {
    "music",
    "song",
    "sings",
    "singing",
    "sing",
    "plays",
    "playing",
    "applause",
    "laughs",
    "laughter",
    "burps",
    "sigh",
    "sighs",
    "coughs",
    "noise",
    "silence",
    "inaudible",
    "indistinct",
}


def read_text(path):
    try:
        with open(path, encoding="utf-8") as fh:
            return fh.read()
    except UnicodeDecodeError:
        with open(path, encoding="cp1252", errors="replace") as fh:
            return fh.read()


def speech_words(text):
    """Words that represent actual spoken content, with audio tags removed."""
    t = text
    t = re.sub(r"\*[^*]*\*", " ", t)  # *music*, *Sigh*
    t = re.sub(r"\[[^\]]*\]", " ", t)  # [Music]
    t = re.sub(r"(?im)^\s*speaker\s*\d+\s*$", " ", t)  # speaker labels
    t = re.sub(r"(?i)\bspeaker\s*\d+\b", " ", t)
    t = re.sub(r"[^\w']+", " ", t)
    words = [w for w in t.split() if w]
    keep = [w for w in words if w.lower() not in MUSIC_WORDS]
    return keep


def main():
    if not os.path.isdir(V):
        print(f"error: {V} not found")
        return 1

    try:
        entries = sorted(os.listdir(V))
    except OSError as exc:
        print(f"error: cannot list {V}: {exc}")
        return 1

    all_txt = [
        f
        for f in entries
        if f.lower().endswith(".txt") and os.path.isfile(os.path.join(V, f))
    ]

    kept, dropped = [], []
    for name in all_txt:
        if name in ADULT:
            dropped.append((name, ADULT[name]))
            continue
        if name in THIRD_PARTY:
            dropped.append((name, THIRD_PARTY[name]))
            continue
        if name in NOT_TRANSCRIPTS:
            dropped.append((name, NOT_TRANSCRIPTS[name]))
            continue

        text = read_text(os.path.join(V, name))
        words = speech_words(text)
        if len(words) < 3:
            preview = " ".join(text.split())[:44]
            dropped.append((name, f"no speech ({len(words)} word(s): {preview!r})"))
            continue
        kept.append(name)

    def sort_key(n):
        stem = os.path.splitext(n)[0]
        if re.match(r"^\d{8}_\d{6}$", stem):
            return (0, stem)
        if stem.startswith("IMG_"):
            return (1, stem)
        return (2, stem.lower())

    kept.sort(key=sort_key)
    dropped.sort(key=lambda x: x[0])

    total = sum(os.path.getsize(os.path.join(V, n)) for n in kept)
    stamp = time.strftime("%Y-%m-%d %H:%M:%S")

    try:
        fh_out = open(OUT, "w", encoding="utf-8", newline="\n")
    except OSError as exc:
        print(f"error: cannot write {OUT}: {exc}")
        return 1

    with fh_out as fh:
        bar = "=" * 78
        fh.write(bar + "\n")
        fh.write("COMBINED CONVERSATIONS\n")
        fh.write(f"Generated : {stamp}\n")
        fh.write("Source    : ~/Videos\n")
        fh.write(f"Files     : {len(kept)} conversations\n")
        fh.write(f"Size      : {total:,} bytes\n")
        fh.write(
            "Filter    : only recordings of Rob and Lum talking. Adult/ASMR audio,\n"
        )
        fh.write(
            "            third-party video narration, songs/game audio and silent\n"
        )
        fh.write("            clips are excluded. See below for the full drop list.\n")
        fh.write(bar + "\n\n")

        fh.write("CONTENTS\n")
        fh.write("-" * 78 + "\n")
        for i, name in enumerate(kept, 1):
            sz = os.path.getsize(os.path.join(V, name))
            fh.write(f"{i:4d}. {name:<46} {sz:>9,} B\n")
        fh.write("\n")

        fh.write("EXCLUDED\n")
        fh.write("-" * 78 + "\n")
        for name, why in dropped:
            fh.write(f"      {name[:52]:<52} {why[:74]}\n")
        fh.write("\n")

        for i, name in enumerate(kept, 1):
            p = os.path.join(V, name)
            body = read_text(p).strip("\n")
            mtime = time.strftime(
                "%Y-%m-%d %H:%M:%S", time.localtime(os.path.getmtime(p))
            )
            fh.write("\n" + bar + "\n")
            fh.write(f"[{i}/{len(kept)}]  {name}\n")
            fh.write(f"File : {os.path.getsize(p):,} bytes   modified {mtime}\n")
            fh.write(bar + "\n\n")
            fh.write(body if body else "(empty)")
            fh.write("\n")

        fh.write("\n" + bar + "\n")
        fh.write(f"END — {len(kept)} conversations, {len(dropped)} excluded\n")
        fh.write(bar + "\n")

    print(f"wrote {OUT}")
    print(f"  kept    : {len(kept)} conversations, {total:,} bytes")
    print(f"  dropped : {len(dropped)}")
    print(f"  output  : {os.path.getsize(OUT):,} bytes")
    print()
    print("=== DROPPED ===")
    for name, why in dropped:
        print(f"  {name[:50]:<50} {why[:70]}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
