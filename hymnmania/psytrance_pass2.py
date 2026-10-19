"""SECOND PASS - fix psytrance covers that missed the 135-155 BPM target.

Pass 1 used  speed = 145 / natural_bpm  where natural_bpm came from a beat-tracker
reading of the 1.0x cover. Those readings suffered octave errors, so ~half the covers
landed off-target.

Pass 2 measures the ACTUAL current tempo of each regenerated cover (robust
autocorrelation on the kick band, octave-corrected), then applies a corrective
multiplier:   extra_speed = TARGET / measured_actual
   new_speed   = old_speed * extra_speed

  python psytrance_pass2.py          # fix all off-target psytrance covers
  python psytrance_pass2.py 10       # just 10
"""
import os, re, sys, json, time, subprocess
sys.stdout.reconfigure(encoding="utf-8", errors="replace")

ROOT = os.path.dirname(os.path.abspath(__file__))
PY = sys.executable
GEN = os.path.join(ROOT, "generated")
MIDI_DIR = os.path.join(ROOT, "submodules", "ableton_psytrance_hymn_creator",
                        "hymnmania_src", "hymn_remaker", "input")
RENDER = os.path.join(ROOT, "scripts", "audio_synthesis_render_midi_to_sine_wave_clean.py")
STATE = os.path.join(ROOT, ".psytrance_tempo.json")
TARGET = 145.0
LO, HI = 135.0, 155.0


def tempo(f, dur=60):
    """Robust kick-band tempo: autocorrelation of the low-band onset envelope.
    Returns None if no clear periodicity in a dance-plausible range."""
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
    for lag in range(int(se * 60 / 200), int(se * 60 / 60)):
        if 0 < lag < len(ac) and ac[lag] > ac[lag - 1] and ac[lag] > ac[lag + 1] and ac[lag] > 0.12:
            cands.append((float(ac[lag]), 60.0 * se / lag))
    if not cands:
        return None
    top = [c for c in cands if 125 <= c[1] <= 200]
    return round(top[0][1] if top else cands[0][1])


def safe(h):
    return re.sub(r"[^A-Za-z0-9]+", "_", h).strip("_")


def midi_for(hymn):
    for cand in (hymn + ".mid", ):
        p = os.path.join(MIDI_DIR, cand)
        if os.path.exists(p):
            return p
    # try normalised match
    want = re.sub(r"[^a-z0-9]", "", hymn.lower())
    for f in os.listdir(MIDI_DIR):
        if not f.lower().endswith(".mid"):
            continue
        if re.sub(r"[^a-z0-9]", "", f[:-4].lower()) == want:
            return os.path.join(MIDI_DIR, f)
    return None


def main():
    args = sys.argv[1:]
    n = 999
    for a in args:
        if a.isdigit():
            n = int(a)
    st = json.load(open(STATE, encoding="utf-8"))

    todo = []
    for hymn, v in st.items():
        cov = os.path.join(GEN, f"{safe(hymn)}_10x_psytrance_A_cover.mp3")
        if not os.path.exists(cov):
            continue
        b = tempo(cov)
        if b is None or not (LO <= b <= HI):
            todo.append((hymn, v.get("speed", 1.0), b))
    todo.sort(key=lambda x: abs((x[2] or 100) - TARGET), reverse=True)
    print(f"off-target psytrance covers: {len(todo)} (will fix {min(n,len(todo))})")

    fixed = 0
    for i, (hymn, old_speed, measured) in enumerate(todo[:n], 1):
        midi = midi_for(hymn)
        if not midi:
            print(f"[{i}] {hymn}: no MIDI, skip"); continue
        if measured is None:
            print(f"[{i}] {hymn}: tempo undetectable, skip"); continue
        extra = TARGET / measured
        new_speed = round(max(0.5, min(3.0, old_speed * extra)), 3)
        print(f"[{i}/{len(todo[:n])}] {hymn}: {measured} BPM, speed {old_speed} -> {new_speed}", flush=True)
        wav = os.path.join(ROOT, "mp3_input", f"_psy2_{safe(hymn)}_{new_speed}.wav")
        if not (os.path.exists(wav) and os.path.getsize(wav) > 100000):
            subprocess.run([PY, RENDER, "--midi", midi, "--wav", wav, "--speed", str(new_speed)],
                           capture_output=True, text=True, timeout=900)
        if not os.path.exists(wav):
            print("   render failed"); continue
        from upload_helper import upload_with_fallback
        cid = upload_with_fallback(wav)
        if not cid or cid == "BLOCKED":
            print(f"   upload failed ({cid})"); continue
        g = subprocess.run([PY, os.path.join(ROOT, "gen_only.py"), "psytrance", cid, hymn],
                           capture_output=True, text=True, timeout=1500)
        gm = re.search(r"CLIPS:([0-9a-f,\-]+)", g.stdout or "")
        if not gm:
            print("   generation failed"); continue
        clip = gm.group(1).split(",")[0]
        try:
            subprocess.run([PY, os.path.join(ROOT, "cap_cycle.py"), clip, cov],
                           capture_output=True, text=True, timeout=900)
        except subprocess.TimeoutExpired:
            print("   capture timed out - skipping this one", flush=True)
            continue
        b = tempo(cov)
        st.setdefault(hymn, {})["speed"] = new_speed
        st[hymn]["final_bpm"] = b
        st[hymn]["pass"] = 2
        json.dump(st, open(STATE, "w", encoding="utf-8"), indent=1)
        ok = b is not None and LO <= b <= HI
        if ok:
            fixed += 1
        print(f"   -> {b} BPM  {'IN RANGE ✅' if ok else 'still off'}", flush=True)
    print(f"\nsecond pass fixed {fixed}")


if __name__ == "__main__":
    main()
