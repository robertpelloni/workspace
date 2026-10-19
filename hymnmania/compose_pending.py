"""Compose beat videos for any captured cover that doesn't have one yet.

The scheduler posts BEAT VIDEOS (pipeline_output/beat_videos/*.mp4), so every
captured cover in generated/*.mp3 must be composed first.

  python compose_pending.py           # compose all pending
  python compose_pending.py 10        # compose at most 10
  python compose_pending.py --list    # just show what's pending
"""
import os, sys, subprocess, time
sys.stdout.reconfigure(encoding="utf-8", errors="replace")

os.environ["PATH"] = (
    r"C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin"
    + os.pathsep + os.environ.get("PATH", ""))

ROOT = os.path.dirname(os.path.abspath(__file__))
GEN = os.path.join(ROOT, "generated")
BEATS = os.path.join(ROOT, "pipeline_output", "beat_videos")

sys.path.insert(0, ROOT)


def pending():
    import post_to_youtube as p
    out = []
    for f in sorted(os.listdir(GEN)):
        if not f.endswith(".mp3"):
            continue
        src = os.path.join(GEN, f)
        if os.path.getsize(src) < 500_000:
            continue
        beat = os.path.join(BEATS, f[:-4] + "_beatsynced.mp4")
        if os.path.exists(beat) and os.path.getsize(beat) > 1_000_000:
            # rebuild if the source cover is NEWER than the beat video (stale output)
            if os.path.getmtime(beat) >= os.path.getmtime(src):
                continue
        # skip hymns removed from the pool (Suno-blocked / degraded) and classical
        bkey = f.lower().replace("_", "").replace("-", "").replace(" ", "")
        try:
            from scheduler_v2 import BLOCKED_HYMNS, EXCLUDE_CLASSICAL
        except Exception:
            BLOCKED_HYMNS, EXCLUDE_CLASSICAL = set(), False
        if any(k in bkey for k in BLOCKED_HYMNS):
            continue
        try:
            t, a, y, cls, g, sp, var = p.detect(f)
        except Exception:
            continue
        if not t or not g:
            continue
        if EXCLUDE_CLASSICAL and "classical" in (t or "").lower():
            continue
        out.append((f, t, g))
    return out


def main():
    args = sys.argv[1:]
    if "--list" in args:
        for f, t, g in pending():
            print(f"  {g:26s} {t}")
        print(f"pending: {len(pending())}")
        return
    n = None
    for a in args:
        if a.isdigit():
            n = int(a)
    work = pending()
    # --shard N/M  -> this process takes every Mth item starting at N (parallel rebuilds)
    if "--shard" in args:
        s = args[args.index("--shard") + 1]
        i, m = (int(x) for x in s.split("/"))
        work = [w for j, w in enumerate(work) if j % m == i]
    if n:
        work = work[:n]
    print(f"composing {len(work)} beat video(s)")
    import quick_composer as qc
    ok = 0
    for i, (f, title, genre) in enumerate(work, 1):
        t0 = time.time()
        print(f"[{i}/{len(work)}] {title} / {genre}", flush=True)
        try:
            out = qc.compose(os.path.join(GEN, f), title, genre, force=True)
            sz = os.path.getsize(out) // 1048576 if out and os.path.exists(out) else 0
            print(f"   -> {os.path.basename(out) if out else 'FAILED'} ({sz}MB, {time.time()-t0:.0f}s)", flush=True)
            if sz > 1:
                ok += 1
        except Exception as e:
            print(f"   -> ERROR {str(e)[:70]}", flush=True)
    print(f"\ncomposed {ok}/{len(work)}")


if __name__ == "__main__":
    main()
