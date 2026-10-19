"""Master a captured cover so it actually sounds like its genre.

WHY: Suno's Cover flow preserves the reference sine's melodic character, so covers come out
melody-forward and BRIGHT. Measured on a Full-On psytrance cover:

    low end (sub+kick+bass) : 20.0%      highs >2k : 42.4%    centroid 2437
    (real psytrance has the low end DOMINATING - kick+bass+sub > 45%)

Applying a genre EQ curve:

    low end : 45.2%      highs >2k : 20.4%    centroid 1330

So we post-process every capture with a genre-appropriate EQ curve.

    python master_cover.py <in.mp3> [out.mp3] [--genre psytrance]
"""
import os, subprocess, sys

FFM = r"C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe"

# EQ curves: (freq, Q, gain_dB). Negative gain cuts the melody/harsh highs so the
# kick and bass can take over the mix.
CURVES = {
    "psytrance": [
        (55, 1.2, 7), (90, 1.2, 5), (120, 1.5, 4),          # sub + kick + rolling bass
        (3000, 1.5, -6), (7000, 1.5, -7), (11000, 1.5, -6),  # tame the bright melody/FX
    ],
    "default": [
        (60, 1.2, 4), (110, 1.3, 3),
        (4000, 1.5, -3), (9000, 1.5, -4),
    ],
}
# every psytrance sub-genre shares the psytrance curve
for _sg in ["psytrance_fullon", "goa_trance", "psytrance_progressive", "psytrance_dark",
            "psytrance_forest", "psytrance_hitech", "psytrance_psychill", "psytrance_zenonesque"]:
    CURVES[_sg] = CURVES["psytrance"]


def curve_for(genre):
    g = (genre or "").lower()
    if g in CURVES:
        return CURVES[g]
    if "psy" in g or "goa" in g:
        return CURVES["psytrance"]
    return CURVES["default"]


def master(in_fp, out_fp=None, genre=None):
    """Apply the genre EQ curve. Returns the output path (or the input if it failed).

    NOTE: ffmpeg CANNOT read and write the same path - it silently no-ops, leaving the
    file untouched while still exiting looking successful. That made every in-place
    "mastered" call a no-op (caught 2026-09-17). So when in==out we render to a temp file
    and atomically replace the original.
    """
    same_file = out_fp is None or os.path.abspath(in_fp) == os.path.abspath(out_fp)
    if out_fp is None:
        base, ext = os.path.splitext(in_fp)
        out_fp = f"{base}_mastered{ext}"
        same_file = False
    target = out_fp + ".tmp.mp3" if same_file else out_fp

    chain = ",".join(f"equalizer=f={f}:t=q:w={q}:g={g}" for f, q, g in curve_for(genre))
    # gentle limiter so the extra low end does not clip
    chain += ",alimiter=limit=0.95"
    r = subprocess.run([FFM, "-y", "-loglevel", "error", "-i", in_fp, "-af", chain,
                        "-b:a", "320k", target], capture_output=True)
    if not (os.path.exists(target) and os.path.getsize(target) > 100_000):
        if os.path.exists(target) and same_file:
            try:
                os.remove(target)
            except OSError:
                pass
        return in_fp
    if same_file:
        try:
            os.replace(target, in_fp)
        except OSError:
            return in_fp
    return out_fp


if __name__ == "__main__":
    a = [x for x in sys.argv[1:] if not x.startswith("--")]
    g = None
    if "--genre" in sys.argv:
        g = sys.argv[sys.argv.index("--genre") + 1]
    src = a[0]
    dst = a[1] if len(a) > 1 else None
    print(master(src, dst, g))
