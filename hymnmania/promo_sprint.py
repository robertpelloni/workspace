"""PROMO SPRINT — generate as many covers as possible while v6 is CREDIT-FREE.

Suno currently offers credit-free v6 creation for a limited window (see suno.com/account).
Generation is the only step that costs credits; rendering, uploading, capturing and posting
are all free. So the optimal play is to STOCKPILE covers during the promo and capture /
compose / post them afterwards.

This driver, per hymn:
  1. renders the MIDI -> sine WAV            (free)
  2. uploads the WAV to Suno                 (free)
  3. generates a cover for EVERY genre       (FREE during promo)
  4. records every resulting clip id to .promo_sprint.json (for later capture)

Usage:
  python promo_sprint.py                 # all fresh hymns, all genres
  python promo_sprint.py --limit 5       # only the first 5 hymns
  python promo_sprint.py --genres psytrance,synthwave
  python promo_sprint.py --list          # show what would run
"""
import os, sys, re, json, glob, time, subprocess, datetime
sys.stdout.reconfigure(encoding="utf-8", errors="replace")

ROOT = os.path.dirname(os.path.abspath(__file__))
PY = sys.executable
MIDI_DIR = os.path.join(ROOT, "submodules", "ableton_psytrance_hymn_creator",
                        "hymnmania_src", "hymn_remaker", "input")
SINE_DIR = os.path.join(ROOT, "mp3_input")
RENDER = os.path.join(ROOT, "scripts", "audio_synthesis_render_midi_to_sine_wave_clean.py")
ROUND = 1
for _a in sys.argv:
    if _a.startswith("--round"):
        ROUND = int(_a.split("=")[1]) if "=" in _a else 2
STATE = os.path.join(ROOT, ".promo_sprint_r%d.json" % ROUND)
ROUND1_STATE = os.path.join(ROOT, ".promo_sprint.json")

# genres supported by gen_only.py (all 11)
ALL_GENRES = ["psytrance", "deep_house", "synthwave", "drum_and_bass", "gabba",
              "dubstep", "chiptune", "hardstyle", "japanese_hardcore_techno",
              "detroit_techno", "detroit_house"]

BLOCKED = {"brighten", "kumbayah", "ohappyday", "happyday", "leyenda",
           "justoverthemountains", "jotm", "praisehim"}


def load_state():
    if os.path.exists(STATE):
        try:
            return json.load(open(STATE, encoding="utf-8"))
        except Exception:
            pass
    st = {"hymns": {}, "started": datetime.datetime.now().isoformat(), "round": ROUND}
    # round 2+: reuse the uploads already made in round 1 (uploads are free)
    if ROUND > 1 and os.path.exists(ROUND1_STATE):
        try:
            r1 = json.load(open(ROUND1_STATE, encoding="utf-8"))
            for name, v in r1.get("hymns", {}).items():
                if v.get("upload") and v["upload"] != "BLOCKED":
                    st["hymns"][name] = {"upload": v["upload"], "covers": {}}
            print("seeded %d uploads from round 1" % len(st["hymns"]))
        except Exception as e:
            print("seed err", str(e)[:50])
    return st


def save_state(s):
    json.dump(s, open(STATE, "w", encoding="utf-8"), indent=1)


def already_covered():
    """normalised names that already have a cover mp3."""
    out = set()
    for f in os.listdir(os.path.join(ROOT, "generated")):
        if f.endswith(".mp3"):
            out.add(re.sub(r"[^a-z0-9]", "", f.lower())[:16])
    return out


def fresh_hymns():
    files = sorted(glob.glob(os.path.join(MIDI_DIR, "*.mid")))
    covered = already_covered()
    hymns = []
    for p in files:
        name = os.path.splitext(os.path.basename(p))[0]
        n = re.sub(r"[^a-z0-9]", "", name.lower())
        if any(b in n for b in BLOCKED):
            continue
        if n[:16] in covered:
            continue
        # skip obvious classical
        if re.search(r"bach|brahms|elgar|vivaldi|albeniz|handel|book1-|book2-|notebook|toccata", n):
            continue
        hymns.append((name, p))
    return hymns


def render(midi, name):
    wav = os.path.join(SINE_DIR, re.sub(r"[^A-Za-z0-9]+", "_", name) + "_sine.wav")
    if os.path.exists(wav) and os.path.getsize(wav) > 100000:
        return wav
    r = subprocess.run([PY, RENDER, "--midi", midi, "--wav", wav],
                       capture_output=True, text=True, timeout=600)
    return wav if os.path.exists(wav) and os.path.getsize(wav) > 100000 else None


def upload(wav):
    r = subprocess.run([PY, os.path.join(ROOT, "upload_robust2.py"), wav, "3"],
                       capture_output=True, text=True, timeout=900)
    out = (r.stdout or "") + (r.stderr or "")
    if "VERIFIED" in out:
        m = re.search(r"VERIFIED:.*?([0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12})", out)
        if m:
            return m.group(1)
    if "COPYRIGHT" in out.upper():
        return "BLOCKED"
    return None


def gen_cover(genre, upload_id, hymn):
    r = subprocess.run([PY, os.path.join(ROOT, "gen_only.py"), genre, upload_id, hymn],
                       capture_output=True, text=True, timeout=1200)
    out = (r.stdout or "")
    m = re.search(r"CLIPS:([0-9a-f,\-]+)", out)
    if m:
        return [c for c in m.group(1).split(",") if c]
    return []


def main():
    args = sys.argv[1:]
    if "--list" in args:
        h = fresh_hymns()
        print(f"{len(h)} fresh hymns x {len(ALL_GENRES)} genres = {len(h)*len(ALL_GENRES)} covers possible")
        for n, _ in h[:40]:
            print("  ", n)
        return
    genres = ALL_GENRES
    for a in args:
        if a.startswith("--genres"):
            genres = a.split("=")[1].split(",") if "=" in a else ALL_GENRES
    limit = None
    if "--limit" in args:
        limit = int(args[args.index("--limit") + 1])

    hymns = fresh_hymns()
    state = load_state()
    if ROUND > 1:
        # only work hymns we already have an upload for (skip the blocked ones entirely)
        hymns = [(n, m) for (n, m) in hymns if state["hymns"].get(n, {}).get("upload")]
        print("round %d: %d hymns with a valid upload (blocked ones skipped)" % (ROUND, len(hymns)))
    if limit:
        hymns = hymns[:limit]
    print(f"SPRINT: {len(hymns)} hymns x {len(genres)} genres = up to {len(hymns)*len(genres)} covers")
    print(f"promo window is limited — generating now\n")

    made = 0
    for i, (name, midi) in enumerate(hymns, 1):
        st = state["hymns"].setdefault(name, {"upload": None, "covers": {}})
        if st.get("upload") == "BLOCKED":
            print(f"[{i}/{len(hymns)}] {name}: BLOCKED earlier, skipping")
            continue
        # 1-2. render + upload once
        if not st.get("upload"):
            wav = render(midi, name)
            if not wav:
                print(f"[{i}/{len(hymns)}] {name}: render failed")
                continue
            up = upload(wav)
            st["upload"] = up
            save_state(state)
            if up == "BLOCKED":
                print(f"[{i}/{len(hymns)}] {name}: COPYRIGHT BLOCKED")
                continue
            if not up:
                print(f"[{i}/{len(hymns)}] {name}: upload failed")
                continue
            print(f"[{i}/{len(hymns)}] {name}: uploaded {up}")
        up = st["upload"]
        # 3. one cover per genre.  gen_only.py returns ALL clips belonging to this
        #    upload (every genre so far), so diff against what we already know to
        #    keep the per-genre mapping correct.
        known = set()
        for g in st.get("covers", {}):
            known.update(st["covers"][g])
        for g in genres:
            if g in st["covers"] and st["covers"][g]:
                known.update(st["covers"][g])
                continue
            t0 = time.time()
            all_clips = gen_cover(g, up, name)
            new = [c for c in all_clips if c not in known]
            known.update(all_clips)
            st["covers"][g] = new
            save_state(state)
            made += len(new)
            print(f"    {g}: {len(new)} new clip(s) in {time.time()-t0:.0f}s "
                  f"-> {','.join(c[:8] for c in new)}", flush=True)
    print(f"\nSPRINT DONE. newly generated clips: {made}")
    print(f"state: {STATE}")


if __name__ == "__main__":
    main()
