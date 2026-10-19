"""Re-master covers whose genre EQ never actually applied.

Context: `master_cover.master()` originally rendered in place, and ffmpeg cannot read and
write the same path - it silently no-ops. So covers captured before the 2026-09-17 fix are
unmastered (low end ~15-20%, highs ~50% instead of ~41% / ~26%).

This scans generated/*_cover.mp3, measures the low-end share, and masters anything below
the threshold. Safe to re-run: already-mastered files are detected and skipped.

    python master_batch.py --check      # report only
    python master_batch.py              # fix everything under the threshold
    python master_batch.py 20           # fix at most 20
"""
import glob, os, sys, warnings

warnings.filterwarnings("ignore")
ROOT = os.path.dirname(os.path.abspath(__file__))
GEN = os.path.join(ROOT, "generated")
LOW_THRESHOLD = 33.0     # % of energy below 250 Hz; mastered psytrance lands ~41%


def low_end(fp, dur=60):
    import librosa, numpy as np
    y, sr = librosa.load(fp, sr=22050, duration=dur)
    S = np.abs(librosa.stft(y, n_fft=2048))
    fr = librosa.fft_frequencies(sr=sr)
    return 100.0 * S[fr < 250].sum() / S.sum()


def genre_of(name):
    n = name.lower()
    for g in ["fullon", "psytrance", "goa", "dark", "forest", "hitech", "psychill", "zenonesque"]:
        if g in n:
            return "psytrance"
    return "default"


def main():
    a = sys.argv[1:]
    check = "--check" in a
    limit = next((int(x) for x in a if x.isdigit()), None)

    from master_cover import master
    files = sorted(glob.glob(os.path.join(GEN, "*_cover.mp3")))
    todo = []
    for f in files:
        if os.path.getsize(f) < 500_000:
            continue
        try:
            le = low_end(f)
        except Exception:
            continue
        if le < LOW_THRESHOLD:
            todo.append((f, le))
    print(f"scanned {len(files)} covers | {len(todo)} need mastering (<{LOW_THRESHOLD}% low end)")
    if check:
        for f, le in todo[:30]:
            print(f"   {le:5.1f}%  {os.path.basename(f)}")
        return
    if limit:
        todo = todo[:limit]
    fixed = 0
    for f, le in todo:
        before = le
        master(f, f, genre_of(os.path.basename(f)))
        try:
            after = low_end(f)
        except Exception:
            after = None
        if after and after > before + 5:
            fixed += 1
            print(f"   {os.path.basename(f)[:50]:50s} {before:5.1f}% -> {after:5.1f}%")
        else:
            print(f"   {os.path.basename(f)[:50]:50s} {before:5.1f}% -> FAILED")
    print(f"\nmastered {fixed}/{len(todo)}")


if __name__ == "__main__":
    main()
