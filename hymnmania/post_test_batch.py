"""Post 8 full videos + 2 shorts (test batch) with the CORRECTED covers.
Usage: python post_test_batch.py
"""
import os, sys, time, json
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import post_to_youtube as p

VDIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "pipeline_output", "beat_videos")

jobs = json.load(open(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".post_test_jobs.json")))

service = p.get_service()

# 1. Post 8 FULL videos
print("=" * 60)
print("POSTING 8 FULL VIDEOS")
print("=" * 60)
results_full = []
for i, fn in enumerate(jobs['full'], 1):
    src = os.path.join(VDIR, fn)
    if not os.path.exists(src):
        print(f"[{i}/8] MISSING: {fn}")
        continue
    title = p.build_title(fn)
    print(f"\n[{i}/8] FULL: {title}")
    try:
        vid = p.upload(service, src, title)
        results_full.append(vid)
        print(f"  OK https://youtu.be/{vid}")
    except Exception as e:
        print(f"  FAIL: {str(e)[:80]}")
    time.sleep(2)

# 2. Make + post 2 SHORTS
print("\n" + "=" * 60)
print("MAKING + POSTING 2 SHORTS")
print("=" * 60)
results_short = []
for i, fn in enumerate(jobs['short'], 1):
    src = os.path.join(VDIR, fn)
    title = p.build_title(fn)
    print(f"\n[{i}/2] SHORT: {title}")
    try:
        # convert to vertical 9:16 short
        import subprocess
        os.makedirs(os.path.join(os.path.dirname(VDIR), 'shorts'), exist_ok=True)
        vp = os.path.join(os.path.dirname(VDIR), 'shorts', fn.replace('.mp4', '_short.mp4'))
        if not os.path.exists(vp):
            r = subprocess.run(['ffmpeg', '-y', '-loglevel', 'error', '-i', src,
                '-vf', 'crop=ih*9/16:ih,scale=1080:1920',
                '-c:v', 'libx264', '-preset', 'medium', '-crf', '23',
                '-c:a', 'aac', '-b:a', '128k', '-t', '60', vp], capture_output=True)
            if r.returncode != 0:
                print(f"  convert fail: {r.stderr.decode()[-150:]}")
                continue
        vid = p.upload(service, vp, title, is_short=True)
        results_short.append(vid)
        print(f"  OK https://youtu.be/{vid}")
    except Exception as e:
        print(f"  FAIL: {str(e)[:80]}")
    time.sleep(2)

print("\n" + "=" * 60)
print(f"TOTAL: {len(results_full)} full + {len(results_short)} shorts posted")
for v in results_full:
    print(f"  FULL https://youtu.be/{v}")
for v in results_short:
    print(f"  SHORT https://youtu.be/{v}")
