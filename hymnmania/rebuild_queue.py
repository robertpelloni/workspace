"""Rebuild the beat videos that the scheduler is about to post, using the mastered covers.

The scheduler posts from the queue, ordered by genre ratio. After the mastering fix the
covers are correct but the beat videos still carry the OLD thin audio, so only the queued
items need rebuilding - not the whole 164-item backlog.

    python rebuild_queue.py --list
    python rebuild_queue.py --shard 0/4
"""
import os, sys, time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
ROOT = os.path.dirname(os.path.abspath(__file__))
GEN = os.path.join(ROOT, "generated")
BEATS = os.path.join(ROOT, "pipeline_output", "beat_videos")


def stale_queue_items(verbose=True):
    import post_to_youtube as p
    from scheduler_v2 import get_queue
    q = get_queue(verbose=False)
    out = []
    for b in q:
        vid = os.path.join(BEATS, b)
        cov = os.path.join(GEN, b[:-4].replace("_beatsynced", "") + ".mp3")
        if not os.path.exists(cov):
            if verbose:
                print(f"  no cover for {b[:50]}")
            continue
        try:
            if os.path.getmtime(vid) >= os.path.getmtime(cov):
                continue                  # already rebuilt from the mastered cover
        except OSError:
            # another shard is mid-rebuild (compose(force=True) deletes first) - skip it
            continue
        try:
            t, a, y, cls, g, sp, var = p.detect(os.path.basename(cov))
        except Exception:
            continue
        if not t or not g:
            continue
        out.append((os.path.basename(cov), t, g, b))
    return out


def main():
    a = sys.argv[1:]
    if "--list" in a:
        work = stale_queue_items()
        for f, t, g, b in work:
            print(f"  {g:26s} {t}")
        print(f"stale queued items: {len(work)}")
        return
    # Build the work list ONCE from a snapshot file so parallel shards cannot overlap.
    # (Recomputing per shard raced against in-flight rebuilds and duplicated work.)
    snap = os.path.join(ROOT, ".rebuild_work.json")
    if "--shard" in a:
        import json
        if not os.path.exists(snap):
            print("no snapshot - run 'python rebuild_queue.py --snapshot' first")
            return
        work = [tuple(x) for x in json.load(open(snap))]
        s = a[a.index("--shard") + 1]
        i, m = (int(x) for x in s.split("/"))
        work = [w for j, w in enumerate(work) if j % m == i]
    else:
        work = stale_queue_items()
        if "--snapshot" in a:
            import json
            json.dump(work, open(snap, "w"))
            print(f"snapshot written: {len(work)} items")
            return
    lim = next((int(x) for x in a if x.isdigit()), None)
    if lim:
        work = work[:lim]
    print(f"rebuilding {len(work)} queued item(s)", flush=True)
    import quick_composer as qc
    ok = 0
    for i, (f, t, g, b) in enumerate(work, 1):
        print(f"[{i}/{len(work)}] {t} / {g}", flush=True)
        try:
            out = qc.compose(os.path.join(GEN, f), t, g, force=True)
            if out and os.path.exists(out):
                ok += 1
                print(f"   -> {os.path.basename(out)} "
                      f"({os.path.getsize(out)//1048576}MB)", flush=True)
        except Exception as e:
            print(f"   failed: {str(e)[:70]}", flush=True)
    print(f"\nrebuilt {ok}/{len(work)}")


if __name__ == "__main__":
    main()
