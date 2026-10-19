"""Throttled Suno generation - ONE upload per hymn, MANY sub-genre covers.

WHY (2026-09-21): Suno's pitch-invariant ACRCloud matches our OWN prior uploads, so
uploading the same hymn again (even at a different speed) is rejected with "COPYRIGHT
MATCH". Proof: 32 hymns each produced exactly 1 cover (Full-On) and ALL 7 other sub-genre
uploads of the same hymn were blocked - a clean (1 done, 7 blocked) pattern.

So each hymn is uploaded exactly ONCE, and every sub-genre cover is generated from that
single reference via the Cover flow (same tempo, different style prompt + genre EQ).

    python suno_throttle.py --rebuild     # rebuild hymn-level queue
    python suno_throttle.py --status
    python suno_throttle.py --run         # process N hymns (default 1)

Upload speed targets the Full-On BPM (flagship, 2x weight). All sub-genres inherit that
tempo; the prompt + mastering differentiate the sound.
"""
import os, re, sys, json, time, subprocess

sys.stdout.reconfigure(encoding="utf-8", errors="replace")
ROOT = os.path.dirname(os.path.abspath(__file__))
PY = sys.executable
GEN = os.path.join(ROOT, "generated")
MIDI_DIR = os.path.join(ROOT, "submodules", "ableton_psytrance_hymn_creator",
                        "hymnmania_src", "hymn_remaker", "input")
RENDER = os.path.join(ROOT, "scripts", "audio_synthesis_render_midi_to_sine_wave_clean.py")
QUEUE = os.path.join(ROOT, ".upload_queue.json")
STATE = os.path.join(ROOT, ".throttle_state.json")
TEMPO = os.path.join(ROOT, ".psytrance_tempo.json")
SUB = os.path.join(ROOT, "psytrance_subgenres.json")

HYMNS_PER_RUN = 1
FULLON_TARGET = 142


def jload(p, d):
    if os.path.exists(p):
        try:
            return json.load(open(p, encoding="utf-8"))
        except Exception:
            pass
    return d


def jsave(p, o):
    json.dump(o, open(p, "w", encoding="utf-8"), indent=1)


def safe(h):
    return re.sub(r"[^A-Za-z0-9]+", "_", h).strip("_")


def midi_for(hymn):
    p = os.path.join(MIDI_DIR, hymn + ".mid")
    if os.path.exists(p):
        return p
    want = re.sub(r"[^a-z0-9]", "", hymn.lower())
    for f in os.listdir(MIDI_DIR):
        if f.lower().endswith(".mid") and re.sub(r"[^a-z0-9]", "", f[:-4].lower()) == want:
            return os.path.join(MIDI_DIR, f)
    return None


def subgenres():
    return {k: v for k, v in jload(SUB, {}).items() if not k.startswith("_")}


def rebuild():
    """Hymn-level queue: one entry per hymn, all sub-genres generated from one upload."""
    sg = subgenres()
    tstate = jload(TEMPO, {})
    hymns = [h for h, v in tstate.items() if v.get("natural_bpm") and midi_for(h)]
    # group OLD (hymn x genre) jobs by hymn so we can migrate every already-done cover
    old_by_hymn = {}
    for j in jload(QUEUE, []):
        old_by_hymn.setdefault(j.get("hymn"), []).append(j)
    jobs = []
    for h in hymns:
        nat = tstate[h]["natural_bpm"]
        speed = round(max(0.5, min(3.0, FULLON_TARGET / nat)), 3)
        gens = {}
        upload_id = None
        for oj in old_by_hymn.get(h, []):
            g = oj.get("genre")
            if oj.get("upload_id"):
                upload_id = oj["upload_id"]
            if g and oj.get("status") == "done":
                gens[g] = {"clip": oj.get("clip"), "status": "done"}
        # recover done status from files on disk (the old queue was already overwritten
        # by an earlier --rebuild, so the state is gone but the covers still exist)
        for g in sg:
            if g not in gens and os.path.exists(os.path.join(GEN, f"{safe(h)}_10x_{g}_A_cover.mp3")):
                gens[g] = {"clip": None, "status": "done"}
        jobs.append({"hymn": h, "natural_bpm": nat, "speed": speed,
                     "upload_id": upload_id, "gens": gens, "status": "pending"})
    jobs.sort(key=lambda j: j["hymn"])
    jsave(QUEUE, jobs)
    print(f"queue rebuilt: {len(jobs)} hymns x {len(sg)} sub-genres "
          f"(1 upload + {len(sg)} covers each)")
    return jobs


def _covers_left(job):
    sg = subgenres()
    return [g for g in sg if not job.get("gens", {}).get(g, {}).get("status") == "done"]


def status():
    q = jload(QUEUE, [])
    sg = subgenres()
    uploaded = sum(1 for j in q if j.get("upload_id"))
    covers = sum(1 for j in q for g in j.get("gens", {}) if j["gens"][g].get("status") == "done")
    print(f"hymns in queue : {len(q)}")
    print(f"uploaded       : {uploaded}")
    print(f"covers done    : {covers}  (target {len(q)*len(sg)})")
    print(f"sub-genres     : {', '.join(sg)}")


def _upload(hymn, speed, midi):
    wav = os.path.join(ROOT, "mp3_input", f"_thr_{safe(hymn)}.wav")
    if not (os.path.exists(wav) and os.path.getsize(wav) > 100000):
        subprocess.run([PY, RENDER, "--midi", midi, "--wav", wav, "--speed", str(speed)],
                       capture_output=True, text=True, timeout=900)
    if not os.path.exists(wav):
        return None
    from upload_helper import upload_with_fallback
    cid = upload_with_fallback(wav)
    if not cid or cid == "BLOCKED":
        return None
    return cid


def run(n=HYMNS_PER_RUN):
    q = jload(QUEUE, [])
    if not q:
        print("queue empty - run --rebuild"); return
    sg = subgenres()
    todo = [j for j in q if _covers_left(j) and j.get("status") != "blocked"]
    # fresh hymns first (0 gens -> need upload + all 8 covers); partial hymns after
    todo.sort(key=lambda j: len(j.get("gens", {})))
    n = min(n, len(todo))
    print(f"processing {n} hymn(s) of {len(todo)} with work left")
    for j in todo[:n]:
        hymn = j["hymn"]
        print(f"\n=== {hymn} (speed {j['speed']}x -> target {FULLON_TARGET} BPM) ===", flush=True)
        # 1) ensure the hymn is uploaded (ONCE)
        if not j.get("upload_id"):
            midi = midi_for(hymn)
            if not midi:
                print("  no midi"); continue
            print("  uploading...", flush=True)
            uid = _upload(hymn, j["speed"], midi)
            if not uid:
                j["upload_tries"] = j.get("upload_tries", 0) + 1
                if j["upload_tries"] >= 3:
                    j["status"] = "blocked"
                    print("  BLOCKED after 3 upload tries (melody/self-match) - parking")
                else:
                    print(f"  upload FAILED (try {j['upload_tries']}) - will retry later")
                jsave(QUEUE, q)
                continue
            j["upload_id"] = uid
            print(f"  uploaded: {uid}")
            jsave(QUEUE, q)
            time.sleep(30)
        # 2) generate + capture each remaining sub-genre
        for g in _covers_left(j):
            out = os.path.join(GEN, f"{safe(hymn)}_10x_{g}_A_cover.mp3")
            print(f"  [{g}] generating...", flush=True)
            gm = subprocess.run([PY, os.path.join(ROOT, "gen_only.py"), g, j["upload_id"], hymn],
                                capture_output=True, text=True, timeout=1800)
            m = re.search(r"CLIPS:([0-9a-f,\-]+)", gm.stdout or "")
            if not m:
                print(f"    generation failed"); continue
            clip = m.group(1).split(",")[0]
            try:
                subprocess.run([PY, os.path.join(ROOT, "cap_cycle.py"), clip, out],
                               capture_output=True, text=True, timeout=900)
            except subprocess.TimeoutExpired:
                print("    capture timed out"); continue
            if os.path.exists(out):
                try:
                    from master_cover import master
                    master(out, out, g)
                except Exception as e:
                    print(f"    mastering skipped: {e}")
                j.setdefault("gens", {})[g] = {"clip": clip, "status": "done"}
                jsave(QUEUE, q)
                print(f"    -> {os.path.basename(out)}", flush=True)
            else:
                print("    capture failed")
            time.sleep(15)
    jsave(QUEUE, q)
    print("\ndone.")


def main():
    a = sys.argv[1:]
    if "--rebuild" in a:
        rebuild(); return
    if "--status" in a:
        status(); return
    if "--run" in a:
        n = HYMNS_PER_RUN
        if "--n" in a:
            n = int(a[a.index("--n") + 1])
        run(n); return
    status()


if __name__ == "__main__":
    main()
