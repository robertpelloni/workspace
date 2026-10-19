"""Generate TRUE psytrance covers by tempo-matching the Suno input.

PROBLEM (measured 2026-09-15): Suno follows the REFERENCE AUDIO's tempo, not the BPM in
the genre prompt. Our sine renders are at the hymn's natural tempo (~96-130 BPM), so a
"145 BPM psytrance" prompt produced ~103 BPM tracks. Only 4 of 27 psytrance covers
actually landed in the psytrance range (135-155).

FIX: the relationship is LINEAR — cover_bpm = natural_bpm x speed.
  1. quick-probe a 1.0x cover to measure the hymn's natural cover tempo
  2. speed = TARGET_BPM / measured
  3. re-render the MIDI sine at that speed, upload, generate psytrance
  4. capture + verify the result is in range

  python gen_psytrance_tempo.py --probe <hymn>          # just measure
  python gen_psytrance_tempo.py <hymn>                  # full corrected run
  python gen_psytrance_tempo.py --batch 5               # do the next 5 hymns

Costs 10 credits per generation (plus the probe capture, which is free).
"""
import os, re, sys, json, time, subprocess, glob
sys.stdout.reconfigure(encoding="utf-8", errors="replace")

ROOT = os.path.dirname(os.path.abspath(__file__))
PY = sys.executable
MIDI_DIR = os.path.join(ROOT, "submodules", "ableton_psytrance_hymn_creator",
                        "hymnmania_src", "hymn_remaker", "input")
RENDER = os.path.join(ROOT, "scripts", "audio_synthesis_render_midi_to_sine_wave_clean.py")
STATE = os.path.join(ROOT, ".psytrance_tempo.json")
TARGET_BPM = 145.0          # classic full-on psytrance
RANGE = (135.0, 155.0)


def load():
    if os.path.exists(STATE):
        try:
            return json.load(open(STATE, encoding="utf-8"))
        except Exception:
            pass
    return {}


def save(d):
    json.dump(d, open(STATE, "w", encoding="utf-8"), indent=1)


def safe(h):
    return re.sub(r"[^A-Za-z0-9]+", "_", h).strip("_")


def bpm_of(path, dur=60):
    """Kick-band tempo estimate. Beat-trackers suffer octave errors on dance music
    (a 152 BPM psytrance kick gets reported as 99); measuring the low-band onsets
    directly is far more reliable."""
    import librosa, numpy as np, warnings
    warnings.filterwarnings("ignore")
    y, sr = librosa.load(path, sr=22050, duration=dur)
    S = np.abs(librosa.stft(y, n_fft=2048))
    freqs = librosa.fft_frequencies(sr=sr)
    low = S[freqs < 160].sum(axis=0)
    env = librosa.util.normalize(low)
    ons = librosa.onset.onset_detect(onset_envelope=env, sr=sr, units="time",
                                     backtrack=False, delta=0.05)
    if len(ons) < 8:
        t = float(np.asarray(librosa.beat.beat_track(y=y, sr=sr)[0]).ravel()[0])
        return round(t), "beat"
    io = np.diff(ons)
    med = float(np.median(io))
    b = 60.0 / med if med > 0 else 0
    # octave-correct into a sensible dance range
    while b and b > 190: b /= 2
    while b and b < 70: b *= 2
    return round(b), "kick"


def probe(clip_id, tag):
    """Capture ~26s of a clip (free) just to measure its tempo."""
    out = os.path.join(ROOT, "generated", f"_probe_{tag}.mp3")
    if not (os.path.exists(out) and os.path.getsize(out) > 200000):
        r = subprocess.run([PY, os.path.join(ROOT, "cap_single_full.py"), clip_id, out],
                           capture_output=True, text=True, timeout=900)
        if not os.path.exists(out):
            # fall back to the page-cycling capture (will be trimmed)
            subprocess.run([PY, os.path.join(ROOT, "cap_cycle.py"), clip_id, out],
                           capture_output=True, text=True, timeout=1200)
    if os.path.exists(out) and os.path.getsize(out) > 200000:
        b, _ = bpm_of(out)
        return b
    return None


def first_clip_for(hymn):
    """Find a 1.0x psytrance clip id for this hymn from the sprint bank."""
    for f in (".promo_sprint.json", ".promo_sprint_r2.json"):
        p = os.path.join(ROOT, f)
        if not os.path.exists(p):
            continue
        d = json.load(open(p, encoding="utf-8")).get("hymns", {})
        v = d.get(hymn)
        if v and (v.get("covers") or {}).get("psytrance"):
            return v["covers"]["psytrance"][0]
    return None


def main():
    args = sys.argv[1:]
    st = load()
    if "--probe" in args:
        hymn = args[args.index("--probe") + 1]
        cid = first_clip_for(hymn)
        print(f"{hymn}: clip={cid}")
        if cid:
            b = probe(cid, safe(hymn))
            print(f"  measured 1.0x cover tempo: {b} BPM -> speed for {TARGET_BPM:.0f} = {TARGET_BPM/b:.3f}")
            st.setdefault(hymn, {})["natural_bpm"] = b
            save(st)
        return

    n = 1
    for a in args:
        if a.isdigit():
            n = int(a)
    # pick hymns that have a psytrance clip and aren't done yet
    hymns = []
    for f in (".promo_sprint.json",):
        p = os.path.join(ROOT, f)
        if not os.path.exists(p):
            continue
        d = json.load(open(p, encoding="utf-8")).get("hymns", {})
        for hymn, v in d.items():
            if (v.get("covers") or {}).get("psytrance") and v.get("upload") not in (None, "BLOCKED"):
                hymns.append(hymn)
    done = {k for k, v in st.items() if v.get("final_bpm") and RANGE[0] <= v["final_bpm"] <= RANGE[1]}
    todo = [h for h in sorted(hymns) if h not in done]
    print(f"hymns with psytrance clips: {len(hymns)} | already correct: {len(done)} | todo: {len(todo)}")
    for hymn in todo[:n]:
        e = st.setdefault(hymn, {})
        midi = os.path.join(MIDI_DIR, hymn + ".mid")
        if not os.path.exists(midi):
            print(f"SKIP {hymn}: no MIDI"); continue
        # 1. measure natural tempo (probe an existing 1.0x cover)
        if not e.get("natural_bpm"):
            cid = first_clip_for(hymn)
            b = probe(cid, safe(hymn)) if cid else None
            if not b:
                print(f"SKIP {hymn}: probe failed"); continue
            e["natural_bpm"] = b
            save(st)
            print(f"{hymn}: natural={b} BPM")
        speed = round(TARGET_BPM / e["natural_bpm"], 3)
        speed = max(0.5, min(3.0, speed))
        e["speed"] = speed
        # 2. render at that speed
        wav = os.path.join(ROOT, "mp3_input", f"_psy_{safe(hymn)}_{speed}.wav")
        if not (os.path.exists(wav) and os.path.getsize(wav) > 100000):
            subprocess.run([PY, RENDER, "--midi", midi, "--wav", wav, "--speed", str(speed)],
                           capture_output=True, text=True, timeout=900)
        if not os.path.exists(wav):
            print(f"SKIP {hymn}: render failed"); continue
        # 3. upload
        r = subprocess.run([PY, os.path.join(ROOT, "upload_robust2.py"), wav, "2"],
                           capture_output=True, text=True, timeout=900)
        out = (r.stdout or "") + (r.stderr or "")
        m = re.search(r"VERIFIED:.*?([0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12})", out)
        if not m:
            print(f"SKIP {hymn}: upload failed ({out.strip()[-80:]})"); continue
        e["upload"] = m.group(1); save(st)
        # 4. generate + capture
        print(f"{hymn}: speed={speed} upload={m.group(1)[:8]} -> generating...", flush=True)
        g = subprocess.run([PY, os.path.join(ROOT, "gen_only.py"), "psytrance", m.group(1), hymn],
                           capture_output=True, text=True, timeout=1500)
        gm = re.search(r"CLIPS:([0-9a-f,\-]+)", g.stdout or "")
        if not gm:
            print(f"  generation failed"); continue
        clip = gm.group(1).split(",")[0]
        e["clip"] = clip; save(st)
        target_mp3 = os.path.join(ROOT, "generated", f"{safe(hymn)}_10x_psytrance_A_cover.mp3")
        subprocess.run([PY, os.path.join(ROOT, "cap_cycle.py"), clip, target_mp3],
                       capture_output=True, text=True, timeout=1500)
        if os.path.exists(target_mp3):
            b, how = bpm_of(target_mp3)
            e["final_bpm"] = b; save(st)
            ok = RANGE[0] <= b <= RANGE[1]
            print(f"  RESULT {hymn}: {b} BPM ({how})  {'IN RANGE' if ok else 'STILL OFF'}", flush=True)
    print(f"\ndone. state: {STATE}")


if __name__ == "__main__":
    main()
