"""Post all composed beat videos to YouTube sequentially."""
import os, sys, time, glob
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import post_to_youtube as p

VDIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "pipeline_output", "beat_videos")

# videos to post (exclude ones already posted)
jobs = [
    "Jesus_Comes_With_Power_10x_chiptune_A_cover_beatsynced.mp4",
    "Jesus_Comes_With_Power_10x_deep_house_A_cover_beatsynced.mp4",
    "Jesus_Comes_With_Power_10x_detroit_house_A_cover_beatsynced.mp4",
    "Jesus_Comes_With_Power_10x_detroit_techno_A_cover_beatsynced.mp4",
    "Jesus_Comes_With_Power_10x_drum_and_bass_A_cover_beatsynced.mp4",
    "Jesus_Comes_With_Power_10x_dubstep_A_cover_beatsynced.mp4",
    "Jesus_Comes_With_Power_10x_gabba_A_cover_beatsynced.mp4",
    "Jesus_Comes_With_Power_10x_hardstyle_A_cover_beatsynced.mp4",
    "Jesus_Comes_With_Power_10x_japanese_hardcore_techno_A_cover_beatsynced.mp4",
    "Jesus_Comes_With_Power_10x_synthwave_A_cover_beatsynced.mp4",
]

service = p.get_service()
for i, fn in enumerate(jobs, 1):
    src = os.path.join(VDIR, fn)
    if not os.path.exists(src):
        print(f"[{i}/10] MISSING: {fn}")
        continue
    title = p.build_title(fn)
    print(f"\n[{i}/10] Uploading: {fn}")
    try:
        vid = p.upload(service, src, title)
        print(f"  OK https://youtu.be/{vid}")
    except Exception as e:
        print(f"  FAIL: {str(e)[:80]}")
    time.sleep(2)

print("\nALL DONE")
