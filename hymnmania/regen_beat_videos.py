"""Regenerate July-era beat videos with the current composer (waveform + intro/outro).
Local-only — zero YouTube API quota. Run: python regen_beat_videos.py [--force] [limit]
"""
import os, sys, json, time, re

os.environ["PATH"] = (
    r"C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin"
    + os.pathsep + os.environ.get("PATH", ""))

import quick_composer as qc

ROOT = os.path.dirname(os.path.abspath(__file__))
GEN = os.path.join(ROOT, "generated")
OUT = os.path.join(ROOT, "pipeline_output", "beat_videos")

# Canonical piece names (display name used for thumbnail text)
PIECES = [
    ("amazinggrace", "Amazing Grace"),
    ("canonind", "Canon in D"),
    ("canon in d", "Canon in D"),
    ("canon", "Canon in D"),
    ("clairdelune", "Clair de Lune"),
    ("clair de lune", "Clair de Lune"),
    ("clair", "Clair de Lune"),
    ("howgreatthouart", "How Great Thou Art"),
    ("how great", "How Great Thou Art"),
    ("thy word", "Thy Word"),
    ("neon valse", "Neon Valse"),
    ("toccatafugue", "Toccata and Fugue in D minor"),
    ("toccata", "Toccata and Fugue in D minor"),
    ("furelise", "Für Elise"),
    ("moonlight", "Moonlight Sonata"),
    ("nocturne", "Nocturne Op. 9 No. 2"),
    ("dyens", "Valse en Skaï"),
]

# Genre detection from filename -> genre tag used by composer (matches GENRE_STYLES keys)
# Keys are matched against the filename with spaces/underscores REMOVED so concatenated
# names work: DetroitHouse -> Detroit House, DeepHouseGroove -> Deep House, etc.
GENRES = [
    ("psytrance", "Psytrance"),
    ("drumandbass", "Drum and Bass"),
    ("drumandbas", "Drum and Bass"),
    ("dnb", "Drum and Bass"),
    ("deephouse", "Deep House"),
    ("detroithouse", "Detroit House"),
    ("detroittechno", "Detroit Techno"),
    ("detroitcircuit", "Detroit Techno"),
    ("dubstep", "Dubstep"),
    ("brostep", "Dubstep"),
    ("chiptune", "Chiptune"),
    ("8bit", "Chiptune"),
    ("hardstyle", "Hardstyle Trance"),
    ("synthwave", "Synthwave"),
    ("gabba", "Gabba"),
    ("hardcore", "Gabba"),
    ("neon", "Synthwave"),
]

def piece_name(fn):
    fl = fn.lower().replace("_", " ")
    for key, name in PIECES:
        if key in fl:
            return name
    return None

def genre_tag(fn):
    # strip spaces and underscores so concatenated names match
    fl = "".join(ch for ch in fn.lower() if ch not in " _-()")
    for key, g in GENRES:
        if key in fl:
            return g
    return None

def main():
    force = "--force" in sys.argv
    limit = None
    for a in sys.argv[1:]:
        if a.isdigit():
            limit = int(a)

    regen_list = json.load(open(os.path.join(ROOT, ".regen_list.json")))

    done, skipped, failed = 0, 0, 0
    start = time.time()
    for i, cover in enumerate(regen_list, 1):
        if limit and done + skipped + failed >= limit:
            break
        fn = os.path.join(GEN, cover)
        base = cover.replace("_cover.mp3", "")
        out_fp = os.path.join(OUT, f"{base}_cover_beatsynced.mp4")
        if not os.path.exists(out_fp):
            out_fp = os.path.join(OUT, f"{base}_beatsynced.mp4")

        hymn = piece_name(cover)
        genre = genre_tag(cover)

        # delete old output so composer regenerates
        if os.path.exists(out_fp):
            if force:
                os.remove(out_fp)
            else:
                skipped += 1
                print(f"[{i}/{len(regen_list)}] SKIP (exists, use --force): {cover[:55]}")
                continue

        print(f"[{i}/{len(regen_list)}] REGEN {cover[:55]}  hymn={hymn} genre={genre}")
        try:
            r = qc.compose(fn, hymn or "Track", genre or "Electronic")
            if r and os.path.exists(r):
                done += 1
                mb = os.path.getsize(r) // 1024 // 1024
                print(f"    OK -> {os.path.basename(r)} ({mb}MB)")
            else:
                failed += 1
                print(f"    FAILED compose returned {r}")
        except Exception as e:
            failed += 1
            print(f"    ERROR: {str(e)[:100]}")

    el = time.time() - start
    print(f"\n=== DONE: {done} regenerated, {skipped} skipped (no --force), {failed} failed in {el/60:.1f} min ===")

if __name__ == "__main__":
    main()
