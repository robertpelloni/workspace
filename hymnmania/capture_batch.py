"""Batch-capture covers from the promo-sprint clip bank into generated/*.mp3.

Reads .promo_sprint.json (round 1) and .promo_sprint_r2.json (round 2), and for each
(hymn, genre) setting captures a clip to:
    generated/<Hymn>_10x_<genre>_<A|B>_cover.mp3

Resumable (skips files that already exist) and interleaves genres so the library
stays varied. Uses cap_cycle.py (page-cycling MediaRecorder capture, seek-confirmed).

  python capture_batch.py            # capture 12 covers
  python capture_batch.py 24         # capture 24
  python capture_batch.py 12 psytrance,synthwave   # only these genres
"""
import os, re, sys, json, time, subprocess
sys.stdout.reconfigure(encoding="utf-8", errors="replace")

ROOT = os.path.dirname(os.path.abspath(__file__))
GEN = os.path.join(ROOT, "generated")
PY = sys.executable

# priority order - on-brand genres first
PRIORITY = ["psytrance", "synthwave", "deep_house", "drum_and_bass", "gabba",
            "dubstep", "chiptune", "hardstyle", "detroit_techno",
            "detroit_house", "japanese_hardcore_techno"]

# genres detectable by post_to_youtube.detect()
GENRE_TOKEN = {
    "psytrance": "psytrance", "synthwave": "synthwave", "deep_house": "deep_house",
    "drum_and_bass": "drum_and_bass", "gabba": "gabba", "dubstep": "dubstep",
    "chiptune": "chiptune", "hardstyle": "hardstyle",
    "detroit_techno": "detroit_techno", "detroit_house": "detroit_house",
    "japanese_hardcore_techno": "japanese_hardcore_techno",
}


def safe_name(h):
    return re.sub(r"[^A-Za-z0-9]+", "_", h).strip("_")


def load_bank():
    """[(hymn, genre, clip_id)] deduped, ordered by genre priority then hymn."""
    bank = []
    seen = set()
    for f in (".promo_sprint.json", ".promo_sprint_r2.json"):
        p = os.path.join(ROOT, f)
        if not os.path.exists(p):
            continue
        d = json.load(open(p, encoding="utf-8")).get("hymns", {})
        for hymn, v in d.items():
            for g, clips in (v.get("covers") or {}).items():
                if not clips:
                    continue
                cid = clips[0]
                key = (hymn, g)
                if key in seen:
                    continue
                seen.add(key)
                bank.append((hymn, g, cid))
    order = {g: i for i, g in enumerate(PRIORITY)}
    bank.sort(key=lambda x: (order.get(x[1], 99), x[0]))
    return bank


def out_path(hymn, genre, slot):
    return os.path.join(GEN, f"{safe_name(hymn)}_10x_{GENRE_TOKEN.get(genre, genre)}_{slot}_cover.mp3")


def main():
    args = sys.argv[1:]
    n = int(args[0]) if args and args[0].isdigit() else 12
    genres = None
    for a in args:
        if "," in a:
            genres = set(a.split(","))
    bank = load_bank()
    if genres:
        bank = [b for b in bank if b[1] in genres]
    # build worklist: A slot first, then B slot (second clip) as backup
    todo = []
    for hymn, g, cid in bank:
        pa = out_path(hymn, g, "A")
        if not (os.path.exists(pa) and os.path.getsize(pa) > 500000):
            todo.append((hymn, g, cid, "A", pa))
    print(f"bank={len(bank)} settings | need capture={len(todo)} | will do {min(n,len(todo))}")
    made = 0
    for i, (hymn, g, cid, slot, path) in enumerate(todo[:n], 1):
        t0 = time.time()
        print(f"\n[{i}/{min(n,len(todo))}] {hymn} / {g} ({cid[:8]})", flush=True)
        r = subprocess.run([PY, os.path.join(ROOT, "cap_cycle.py"), cid, path],
                           capture_output=True, text=True, timeout=1500)
        out = (r.stdout or "") + (r.stderr or "")
        m = re.search(r"RESULT duration=(\d+)s centroid=([\d.]+) loop_check=([\d.]+)", out)
        if m:
            dur, cen, loop = int(m.group(1)), float(m.group(2)), float(m.group(3))
            ok = os.path.exists(path) and cen > 1000 and loop <= 0.9
            print(f"   -> {dur}s centroid={cen} loop={loop} {'OK' if ok else 'REJECT'}", flush=True)
            if not ok:
                try:
                    os.remove(path)
                except Exception:
                    pass
                continue
            made += 1
        else:
            print("   -> no RESULT line;", out.strip().splitlines()[-1][:90] if out.strip() else "no output", flush=True)
        print(f"   ({time.time()-t0:.0f}s)", flush=True)
    print(f"\ncaptured {made} cover(s)")


if __name__ == "__main__":
    main()
