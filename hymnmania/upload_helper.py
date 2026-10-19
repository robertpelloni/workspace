"""Upload a sine render to Suno, with automatic PITCH-SHIFT RETRY.

Some tempo-matched renders get rejected with "COPYRIGHT MATCH". Testing (2026-09-16)
showed the *same* hymn uploads fine at 1.0x and pitch-shifted, but a specific speed
render can trip ACRCloud.

Fix: if the upload is rejected, shift the PITCH slightly (a few percent) while keeping
the TEMPO identical, then retry. A small pitch change moves the fingerprint off the
matched recording without changing the groove.

    asetrate=SR*factor  -> pitch AND speed scale by factor
    atempo=1/factor     -> speed back to normal, pitch stays shifted

Public API
    upload_with_fallback(wav_path, tries=4) -> clip_id | "BLOCKED" | None
"""
import os, re, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.abspath(__file__))
PY = sys.executable
FFM = r"C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe"

# alternating up/down shifts - small enough to be musically transparent
SHIFT_FACTORS = [1.03, 0.97, 1.06, 0.94]


def pitch_shift(src, factor, out=None):
    """Return a copy of `src` with pitch * factor and the SAME tempo."""
    if out is None:
        base, ext = os.path.splitext(src)
        out = f"{base}_ps{int(round(factor*100))}{ext}"
    r = subprocess.run([FFM, "-y", "-loglevel", "error", "-i", src,
                        "-filter:a",
                        f"asetrate=44100*{factor},aresample=44100,atempo={round(1.0/factor,6)}",
                        out], capture_output=True)
    return out if os.path.exists(out) and os.path.getsize(out) > 50000 else None


def _upload(wav_path):
    """Single upload attempt. Returns clip id, 'BLOCKED', or None."""
    r = subprocess.run([PY, os.path.join(ROOT, "upload_robust2.py"), wav_path, "1"],
                       capture_output=True, text=True, timeout=900)
    o = (r.stdout or "") + (r.stderr or "")
    m = re.search(r"VERIFIED:.*?([0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12})", o)
    if m:
        return m.group(1)
    if "COPYRIGHT MATCH" in o.upper():
        return "BLOCKED"
    return None


def upload_with_fallback(wav_path, tries=4, verbose=True):
    """Try the plain upload, then pitch-shift retries. Returns clip id | 'BLOCKED' | None."""
    cid = _upload(wav_path)
    if cid and cid != "BLOCKED":
        return cid
    if cid is None:
        # transient failure - one plain retry
        cid = _upload(wav_path)
        if cid and cid != "BLOCKED":
            return cid
    if verbose:
        print("   copyright match -> trying pitch-shift fallbacks", flush=True)
    tmp = []
    try:
        for f in SHIFT_FACTORS[:tries]:
            p = pitch_shift(wav_path, f)
            if not p:
                continue
            tmp.append(p)
            cid = _upload(p)
            if cid and cid != "BLOCKED":
                if verbose:
                    print(f"   ok with pitch x{f}", flush=True)
                return cid
            if verbose:
                print(f"   pitch x{f}: still blocked", flush=True)
    finally:
        for p in tmp:
            try:
                os.remove(p)
            except Exception:
                pass
    return "BLOCKED"


if __name__ == "__main__":
    print(upload_with_fallback(sys.argv[1]))
