#!/usr/bin/env python3
"""Combine every per-video/audio ASR transcript in ~/Videos into one document.

Includes only files that are transcripts of a media file:
  - YYYYMMDD_HHMMSS.txt  (screen-recording / camera ASR, 78 of them)
  - IMG_*.txt            (iPhone video ASR)
  - the ASMR audio transcripts
  - the tactiq YouTube transcript

Excludes, by design:
  - existing bundles (combined_transcript.txt, video_transcripts*.txt) — would recurse
  - LLM-cleaned derivatives (transcript.txt, transcript1..5.txt) — duplicate content
  - non-transcripts (cookies.txt, ytdl-archive.txt, 4chan.txt, speaker_mapping_report.txt)

Writes: ~/Videos/combined_video_transcripts.txt
"""

import os
import re
import sys
import time

V = os.path.abspath(
    os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "Videos")
)
OUT = os.path.join(V, "combined_video_transcripts.txt")

# exact names to leave out, with the reason
EXCLUDE = {
    # existing bundles — including them would nest the whole thing
    "combined_transcript.txt": "existing bundle",
    "video_transcripts.txt": "existing bundle",
    "video_transcripts_corrected.txt": "existing bundle",
    # LLM-cleaned derivatives of the raw transcripts — would duplicate
    "transcript.txt": "cleaned derivative",
    "transcript1.txt": "cleaned derivative",
    "transcript2.txt": "cleaned derivative",
    "transcript3.txt": "cleaned derivative",
    "transcript4.txt": "cleaned derivative",
    "transcript5.txt": "cleaned derivative",
    # not transcripts
    "cookies.txt": "not a transcript",
    "ytdl-archive.txt": "not a transcript",
    "4chan.txt": "not a transcript",
    "speaker_mapping_report.txt": "not a transcript",
}

MEDIA_EXT = (".mp4", ".mov", ".mkv", ".webm", ".m4v", ".mp3", ".m4a", ".wav", ".aac")


def read_text(path):
    """Read as UTF-8, falling back to cp1252 so one odd byte cannot abort."""
    try:
        with open(path, encoding="utf-8") as fh:
            return fh.read()
    except UnicodeDecodeError:
        with open(path, encoding="cp1252", errors="replace") as fh:
            return fh.read()


def main():
    if not os.path.isdir(V):
        print(f"error: {V} not found")
        return 1

    media = {}
    txts = []
    try:
        entries = sorted(os.listdir(V))
    except OSError as exc:
        print(f"error: cannot list {V}: {exc}")
        return 1

    for name in entries:
        p = os.path.join(V, name)
        if not os.path.isfile(p):
            continue
        stem, ext = os.path.splitext(name)
        if ext.lower() in MEDIA_EXT:
            media[stem] = name
        elif ext.lower() == ".txt":
            txts.append(name)

    included, skipped = [], []
    for name in txts:
        if name in EXCLUDE:
            skipped.append((name, EXCLUDE[name]))
            continue
        included.append(name)

    # order: timestamped first (chronological), then IMG_, then the rest alphabetically
    def sort_key(n):
        stem = os.path.splitext(n)[0]
        if re.match(r"^\d{8}_\d{6}$", stem):
            return (0, stem)
        if stem.startswith("IMG_"):
            return (1, stem)
        return (2, stem.lower())

    included.sort(key=sort_key)

    total_bytes = sum(os.path.getsize(os.path.join(V, n)) for n in included)
    stamp = time.strftime("%Y-%m-%d %H:%M:%S")

    try:
        out_fh = open(OUT, "w", encoding="utf-8", newline="\n")
    except OSError as exc:
        print(f"error: cannot write {OUT}: {exc}")
        return 1

    with out_fh as fh:
        bar = "=" * 78
        fh.write(bar + "\n")
        fh.write("COMBINED VIDEO TRANSCRIPTS\n")
        fh.write(f"Generated: {stamp}\n")
        fh.write("Source   : ~/Videos\n")
        fh.write(f"Files    : {len(included)}\n")
        fh.write(f"Size     : {total_bytes:,} bytes\n")
        fh.write(bar + "\n\n")

        # ---- contents ----
        fh.write("CONTENTS\n")
        fh.write("-" * 78 + "\n")
        for i, name in enumerate(included, 1):
            stem = os.path.splitext(name)[0]
            mate = media.get(stem)
            sz = os.path.getsize(os.path.join(V, name))
            tail = f"  [{mate}]" if mate else "  [no media file]"
            fh.write(f"{i:4d}. {name:<58} {sz:>9,} B{tail}\n")
        fh.write("\n")

        if skipped:
            fh.write("EXCLUDED FROM THIS COMBINE\n")
            fh.write("-" * 78 + "\n")
            for name, why in skipped:
                fh.write(f"      {name:<58} ({why})\n")
            fh.write("\n")

        # ---- bodies ----
        for i, name in enumerate(included, 1):
            p = os.path.join(V, name)
            stem = os.path.splitext(name)[0]
            mate = media.get(stem)
            size = os.path.getsize(p)
            mtime = time.strftime(
                "%Y-%m-%d %H:%M:%S", time.localtime(os.path.getmtime(p))
            )
            body = read_text(p).strip("\n")

            fh.write("\n" + bar + "\n")
            fh.write(f"[{i}/{len(included)}]  {name}\n")
            fh.write(f"Media : {mate if mate else '(none found)'}\n")
            fh.write(f"File  : {size:,} bytes   modified {mtime}\n")
            fh.write(bar + "\n\n")
            fh.write(body if body else "(empty transcript)")
            fh.write("\n")

        fh.write("\n" + bar + "\n")
        fh.write(f"END — {len(included)} transcripts combined\n")
        fh.write(bar + "\n")

    print(f"wrote {OUT}")
    print(f"  transcripts combined : {len(included)}")
    print(f"  source bytes         : {total_bytes:,}")
    print(f"  output bytes         : {os.path.getsize(OUT):,}")
    print(f"  excluded             : {len(skipped)}")
    print()
    print("  included, by category:")
    cats = {"timestamped": 0, "IMG_": 0, "other": 0}
    for n in included:
        stem = os.path.splitext(n)[0]
        if re.match(r"^\d{8}_\d{6}$", stem):
            cats["timestamped"] += 1
        elif stem.startswith("IMG_"):
            cats["IMG_"] += 1
        else:
            cats["other"] += 1
    for k, v in cats.items():
        print(f"    {k:<12} {v}")
    print()
    print("  'other' files included:")
    for n in included:
        stem = os.path.splitext(n)[0]
        if not re.match(r"^\d{8}_\d{6}$", stem) and not stem.startswith("IMG_"):
            print(f"    {n[:74]}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
