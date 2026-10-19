"""Generate + capture a real genre cover for a hymn upload, with robust retries.
Usage: python gen_cover_robust.py <genre_key> <upload_clip_id> <hymn_name> [attempts]
"""
import sys, os, json, time, subprocess
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
ROOT = os.path.dirname(os.path.abspath(__file__))

def main():
    genre = sys.argv[1]
    upload_cid = sys.argv[2]
    hymn = sys.argv[3]
    attempts = int(sys.argv[4]) if len(sys.argv) > 4 else 4
    out = os.path.join(ROOT, "generated", f"{hymn}_10x_{genre}_A_cover.mp3")
    # if already exists and big, skip
    if os.path.exists(out) and os.path.getsize(out) > 1000000:
        print(f"cover already exists: {out} ({os.path.getsize(out)//1024}KB)")
        return True
    for attempt in range(attempts):
        print(f"\n=== {hymn} {genre} attempt {attempt+1}/{attempts} ===", flush=True)
        r = subprocess.run([sys.executable, os.path.join(ROOT, "gen_capture_genre.py"),
                            genre, upload_cid, hymn], capture_output=True, timeout=700)
        out_txt = (r.stdout or b"").decode("utf-8", errors="replace")
        err_txt = (r.stderr or b"").decode("utf-8", errors="replace")
        # show last relevant lines
        lines = [l for l in out_txt.split("\n") if l.strip()]
        for l in lines[-5:]:
            print("  " + l, flush=True)
        if os.path.exists(out) and os.path.getsize(out) > 1000000:
            print(f"SUCCESS: {out}", flush=True)
            return True
        if "TargetClosedError" in err_txt or "Connection" in err_txt:
            print("  CDP hiccup — waiting 20s and retrying", flush=True)
            time.sleep(20)
        else:
            time.sleep(10)
    print("FAILED after " + str(attempts) + " attempts", flush=True)
    return False

if __name__ == "__main__":
    ok = main()
    print("RESULT: " + str(ok))
