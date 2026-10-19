"""Generate covers for every psytrance SUB-GENRE, each tempo-matched to its own BPM target.

Uses psytrance_subgenres.json for the per-sub-genre BPM target:
    Full-On 142 | Goa 135 | Progressive 132 | Darkpsy 150
    Forest 143 | Hi-Tech 165 | Psychill 105 | Zenonesque 130

Tempo rule (measured):   cover_bpm = natural_bpm x speed
so                       speed     = target_bpm / natural_bpm

natural_bpm is the hymn's cover tempo at speed 1.0, cached in .psytrance_tempo.json
(seeded from the existing 1.0x psytrance covers).

  python gen_subgenre.py --plan                   # show what would run
  python gen_subgenre.py --genre psytrance_fullon # one sub-genre, all hymns
  python gen_subgenre.py --hymn "Adventist Youth" --genre psytrance_fullon
  python gen_subgenre.py --n 5                    # 5 (hymn, subgenre) jobs, priority order

Costs 10 credits per generation. Verification is octave-safe (kick-band autocorrelation).
"""
import os, re, sys, json, time, subprocess
sys.stdout.reconfigure(encoding="utf-8", errors="replace")

ROOT = os.path.dirname(os.path.abspath(__file__))
PY = sys.executable
GEN = os.path.join(ROOT, "generated")
MIDI_DIR = os.path.join(ROOT, "submodules", "ableton_psytrance_hymn_creator",
                        "hymnmania_src", "hymn_remaker", "input")
RENDER = os.path.join(ROOT, "scripts", "audio_synthesis_render_midi_to_sine_wave_clean.py")
TEMPO_STATE = os.path.join(ROOT, ".psytrance_tempo.json")
SUB_STATE = os.path.join(ROOT, ".subgenre_runs.json")
CFG = os.path.join(ROOT, "psytrance_subgenres.json")


def subgenres():
    d = json.load(open(CFG, encoding="utf-8"))
    return {k: v for k, v in d.items() if not k.startswith("_")}


def safe(h):
    return re.sub(r"[^A-Za-z0-9]+", "_", h).strip("_")


def tempo(f, dur=60):
    """Octave-safe kick-band tempo via autocorrelation of the low-band envelope."""
    import librosa, numpy as np, warnings
    warnings.filterwarnings("ignore")
    y, sr = librosa.load(f, sr=22050, duration=dur)
    S = np.abs(librosa.stft(y, n_fft=2048))
    fr = librosa.fft_frequencies(sr=sr)
    env = librosa.util.normalize(S[fr < 160].sum(axis=0))
    env = env - env.mean()
    ac = np.correlate(env, env, "full")[len(env) - 1:]
    ac = ac / ac[0]
    se = sr / 512.0
    cands = []
    for lag in range(int(se * 60 / 200), int(se * 60 / 50)):
        if 0 < lag < len(ac) and ac[lag] > ac[lag - 1] and ac[lag] > ac[lag + 1] and ac[lag] > 0.12:
            cands.append((float(ac[lag]), 60.0 * se / lag))
    if not cands:
        return None
    return round(cands[0][1])


def midi_for(hymn):
    p = os.path.join(MIDI_DIR, hymn + ".mid")
    if os.path.exists(p):
        return p
    want = re.sub(r"[^a-z0-9]", "", hymn.lower())
    for f in os.listdir(MIDI_DIR):
        if f.lower().endswith(".mid") and re.sub(r"[^a-z0-9]", "", f[:-4].lower()) == want:
            return os.path.join(MIDI_DIR, f)
    return None


def load_json(p, default):
    if os.path.exists(p):
        try:
            return json.load(open(p, encoding="utf-8"))
        except Exception:
            pass
    return default


def main():
    args = sys.argv[1:]
    sg = subgenres()
    tstate = load_json(TEMPO_STATE, {})
    sstate = load_json(SUB_STATE, {})

    # hymns we have a natural tempo for (from the 1.0x psytrance covers)
    hymns = [h for h, v in tstate.items() if v.get("natural_bpm") and midi_for(h)]
    only_hymn = None
    only_genre = None
    for i, a in enumerate(args):
        if a == "--hymn":
            only_hymn = args[i + 1]
        if a == "--genre":
            only_genre = args[i + 1]
    if only_hymn:
        hymns = [h for h in hymns if h == only_hymn]

    genres = [only_genre] if only_genre else list(sg)
    # order: Full-On first (flagship), then the rest
    genres.sort(key=lambda g: (-sg[g]["weight"], g))

    jobs = []
    for h in hymns:
        for g in genres:
            out = os.path.join(GEN, f"{safe(h)}_10x_{g}_A_cover.mp3")
            if os.path.exists(out) and os.path.getsize(out) > 500000:
                continue
            jobs.append((h, g, out))

    if "--plan" in args:
        from collections import Counter
        c = Counter(g for _, g, _ in jobs)
        print(f"hymns={len(hymns)} sub-genres={len(genres)} | pending jobs={len(jobs)}")
        for g in genres:
            print(f"   {sg[g]['label']:22s} {sg[g]['bpm']:>4} BPM  pending {c.get(g,0)}")
        return

    n = 999
    for a in args:
        if a.isdigit():
            n = int(a)
    print(f"jobs pending: {len(jobs)} | doing {min(n,len(jobs))}")
    made = 0
    for i, (hymn, g, out) in enumerate(jobs[:n], 1):
        target = sg[g]["bpm"]
        nat = tstate[hymn]["natural_bpm"]
        speed = round(max(0.5, min(3.0, target / nat)), 3)
        print(f"\n[{i}/{min(n,len(jobs))}] {hymn} / {sg[g]['label']} "
              f"(natural {nat} -> target {target}, speed {speed})", flush=True)
        midi = midi_for(hymn)
        wav = os.path.join(ROOT, "mp3_input", f"_sg_{safe(hymn)}_{g}_{speed}.wav")
        if not (os.path.exists(wav) and os.path.getsize(wav) > 100000):
            subprocess.run([PY, RENDER, "--midi", midi, "--wav", wav, "--speed", str(speed)],
                           capture_output=True, text=True, timeout=900)
        if not os.path.exists(wav):
            print("   render failed"); continue
        from upload_helper import upload_with_fallback
        cid = upload_with_fallback(wav)
        if not cid or cid == "BLOCKED":
            print(f"   upload failed/blocked ({cid})"); continue
        gm = subprocess.run([PY, os.path.join(ROOT, "gen_only.py"), g, cid, hymn],
                            capture_output=True, text=True, timeout=1500)
        cm = re.search(r"CLIPS:([0-9a-f,\-]+)", gm.stdout or "")
        if not cm:
            print("   generation failed"); continue
        clip = cm.group(1).split(",")[0]
        try:
            subprocess.run([PY, os.path.join(ROOT, "cap_cycle.py"), clip, out],
                           capture_output=True, text=True, timeout=900)
        except subprocess.TimeoutExpired:
            print("   capture timed out - skipping this one", flush=True)
            continue
        if os.path.exists(out):
            b = tempo(out)
            lo, hi = sg[g]["range"]
            ok = b is not None and lo <= b <= hi
            sstate.setdefault(hymn, {})[g] = {"clip": clip, "bpm": b, "speed": speed,
                                              "target": target, "ok": bool(ok)}
            json.dump(sstate, open(SUB_STATE, "w", encoding="utf-8"), indent=1)
            print(f"   -> {b} BPM  {'IN RANGE' if ok else 'off (target '+str(target)+')'}", flush=True)
            if ok:
                made += 1
    print(f"\ndone. in-range covers produced: {made}")


if __name__ == "__main__":
    main()
