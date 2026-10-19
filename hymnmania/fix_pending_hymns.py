"""Auto-fix pending hymns: upload sine MP3s to Suno (retrying until Suno accepts),
then generate REAL genre covers, rebuild beat videos from the real covers.

Handles the 3 hymns whose beat videos are currently sheet-music (never got Suno covers):
  - Just Over The Mountains (Deep House)
  - O Happy Day (Dubstep)
  - When Love Shines In (Synthwave)

Suno's upload endpoint is intermittently down (2026-09-03), so this retries uploads
in a loop until they succeed, then runs the verified cover-generation + capture.

Usage: python fix_pending_hymns.py [--loop]  (--loop = keep retrying forever)
"""
import os, sys, json, time, subprocess
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

ROOT = os.path.dirname(os.path.abspath(__file__))
import requests
from playwright.sync_api import sync_playwright

SUNO = "https://studio-api-prod.suno.com"

# hymns to fix: (sine_mp3, hymn_label, genre_key, genre_display)
TARGETS = [
    ("mp3_input/Just_Over_The_Mountains_1.0x.mp3", "Just_Over_The_Mountains", "deep_house", "Deep House"),
    ("mp3_input/O_Happy_Day_1.0x.mp3", "O_Happy_Day", "dubstep", "Dubstep"),
    ("mp3_input/When_Love_Shines_In_1.0x.mp3", "When_Love_Shines_In", "synthwave", "Synthwave"),
]

def check_uploaded(sine_mp3):
    """Find the upload clip id for a sine mp3 (chirp-chirp in feed), or None."""
    stem = os.path.basename(sine_mp3).split(".")[0].lower()
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9333")
        page = next((p for p in b.contexts[0].pages if "suno.com" in p.url), None)
        if not page:
            b.close()
            return None
        tok = page.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}")
        if not tok:
            b.close()
            return None
        hdr = {"Authorization": "Bearer " + str(tok)}
        for pg in range(0, 10):
            try:
                r = requests.get(SUNO + "/api/feed/?limit=50&page=" + str(pg), headers=hdr, timeout=20)
            except Exception:
                break
            if r.status_code != 200:
                break
            clips = r.json() if isinstance(r.json(), list) else r.json().get("clips", [])
            for c in clips:
                if stem in str(c.get("title", "")).lower() and c.get("model_name") == "chirp-chirp":
                    b.close()
                    return c.get("id")
            if len(clips) < 50:
                break
        b.close()
        return None

def ensure_uploaded(sine_mp3, max_tries=40):
    """Retry uploading until success. Returns upload clip id."""
    stem = os.path.basename(sine_mp3).split(".")[0]
    cid = check_uploaded(sine_mp3)
    if cid:
        print(f"  {stem}: already uploaded ({cid[:12]})", flush=True)
        return cid
    for attempt in range(max_tries):
        print(f"  {stem}: uploading (attempt {attempt+1})...", flush=True)
        r = subprocess.run([sys.executable, os.path.join(ROOT, "upload_sine_retry.py"), sine_mp3, "1"],
                           capture_output=True, timeout=420)
        out = (r.stdout or b"").decode("utf-8", errors="replace")
        if "SUCCESS" in out:
            cid = check_uploaded(sine_mp3)
            if cid:
                print(f"  {stem}: UPLOADED ({cid[:12]})", flush=True)
                return cid
        print(f"    attempt {attempt+1} failed — waiting 90s before retry", flush=True)
        time.sleep(90)
    return None

def generate_cover(upload_cid, hymn, genre_key, genre_display, max_tries=5):
    """Generate a real genre cover using the verified gen_capture_genre flow."""
    out = os.path.join(ROOT, "generated", f"{hymn}_10x_{genre_key}_A_cover.mp3")
    if os.path.exists(out) and os.path.getsize(out) > 1000000:
        print(f"  {hymn}: cover exists ({os.path.getsize(out)//1024}KB)", flush=True)
        return out
    for attempt in range(max_tries):
        print(f"  {hymn}: generating {genre_display} cover (attempt {attempt+1})...", flush=True)
        r = subprocess.run([sys.executable, os.path.join(ROOT, "gen_capture_genre.py"),
                            genre_key, upload_cid, hymn], capture_output=True, timeout=700)
        out_txt = (r.stdout or b"").decode("utf-8", errors="replace")
        print("    " + out_txt.strip().replace("\n", "\n    ")[-400:], flush=True)
        if os.path.exists(out) and os.path.getsize(out) > 1000000:
            print(f"  {hymn}: cover generated ({os.path.getsize(out)//1024}KB)", flush=True)
            return out
    return None

def rebuild_beat_video(hymn, genre_key, genre_display):
    """Rebuild the beat video from the REAL cover (replaces the sine version)."""
    cover = os.path.join(ROOT, "generated", f"{hymn}_10x_{genre_key}_A_cover.mp3")
    if not os.path.exists(cover):
        return False
    # find the old sine beat video and remove it
    old_bv = os.path.join(ROOT, "pipeline_output", "beat_videos", f"{hymn}_1.0x_beatsynced.mp4")
    if os.path.exists(old_bv):
        os.remove(old_bv)
        print(f"  removed old sine beat video: {os.path.basename(old_bv)}", flush=True)
    # compose new beat video from the real cover
    import quick_composer as qc
    out = qc.compose(cover, hymn.replace("_", " "), genre_display)
    print(f"  beat video rebuilt: {os.path.basename(out) if out else 'FAILED'}", flush=True)
    return bool(out)

def main():
    loop = "--loop" in sys.argv
    while True:
        all_done = True
        for sine_mp3, hymn, genre_key, genre_display in TARGETS:
            # check if already has real cover
            cover = os.path.join(ROOT, "generated", f"{hymn}_10x_{genre_key}_A_cover.mp3")
            bv = os.path.join(ROOT, "pipeline_output", "beat_videos", f"{hymn}_1.0x_beatsynced.mp4")
            if os.path.exists(cover) and os.path.getsize(cover) > 1000000:
                print(f"{hymn}: already has real cover — {('skipping' if os.path.exists(bv) else 'rebuilding beat video')}", flush=True)
                if not os.path.exists(bv):
                    rebuild_beat_video(hymn, genre_key, genre_display)
                continue
            print(f"\n=== {hymn} ===", flush=True)
            cid = ensure_uploaded(sine_mp3)
            if not cid:
                print(f"  {hymn}: upload still failing — Suno upload endpoint down", flush=True)
                all_done = False
                continue
            cover_out = generate_cover(cid, hymn, genre_key, genre_display)
            if not cover_out:
                print(f"  {hymn}: cover generation failed", flush=True)
                all_done = False
                continue
            rebuild_beat_video(hymn, genre_key, genre_display)
        if not loop:
            break
        if all_done:
            print("\nALL HYMNS FIXED — done!", flush=True)
            break
        print("\nSuno upload may be down — retrying in 3 minutes...", flush=True)
        time.sleep(180)

if __name__ == "__main__":
    main()
