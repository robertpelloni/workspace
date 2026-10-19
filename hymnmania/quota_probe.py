"""Measure the ACTUAL YouTube Data API daily upload quota for this project.

Uploads tiny (2s) PRIVATE test videos repeatedly until the API returns
quotaExceeded, then reports how many were possible and DELETES every test video.

  python quota_probe.py            # probe from 0 up to max_probe
  python quota_probe.py 200        # probe up to 200 uploads

Notes
-----
* videos.insert costs 1,600 units. Default Google quota = 10,000/day (6 uploads).
* This project has historically managed 118 uploads/day, so its quota has been raised;
  the probe finds the current ceiling.
* The probe CONSUMES the rest of today's upload budget - run it when you don't need
  to post real content (it resets at midnight Pacific Time).
* Every test video is uploaded as `private` and deleted at the end.
"""
import os, sys, json, time, subprocess, tempfile
sys.stdout.reconfigure(encoding="utf-8", errors="replace")

FFM = r"C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe"


def make_test_video(path):
    """2s tiny black video with a beep — smallest real upload."""
    subprocess.run([FFM, "-y", "-loglevel", "error", "-f", "lavfi", "-i",
                    "color=c=black:s=320x240:d=2", "-f", "lavfi", "-i",
                    "sine=frequency=440:duration=2", "-shortest",
                    "-c:v", "libx264", "-preset", "ultrafast", "-crf", "35",
                    "-c:a", "aac", "-b:a", "64k", path], capture_output=True)
    return os.path.exists(path)


def main():
    max_probe = int(sys.argv[1]) if len(sys.argv) > 1 else 250
    import post_to_youtube as p
    from googleapiclient.http import MediaFileUpload

    yt = p.get_service()
    tmp = os.path.join(tempfile.gettempdir(), "_quota_probe.mp4")
    if not make_test_video(tmp):
        print("could not build test video")
        return
    print(f"test video: {os.path.getsize(tmp)} bytes")

    uploaded = []
    try:
        for i in range(1, max_probe + 1):
            body = {
                "snippet": {"title": f"QUOTA PROBE {i} (delete me)", "categoryId": "10"},
                "status": {"privacyStatus": "private"},
            }
            try:
                media = MediaFileUpload(tmp, chunksize=1024 * 1024, resumable=False)
                req = yt.videos().insert(part="snippet,status", body=body, media_body=media)
                resp = req.execute()
                vid = resp.get("id")
                uploaded.append(vid)
                print(f"  upload {i:3d}: OK  ({i * 1600:,} units)  {vid}")
            except Exception as e:
                msg = str(e)
                if "uploadLimitExceeded" in msg:
                    print(f"\n*** YOUTUBE UPLOAD LIMIT HIT after {i - 1} successful uploads ***")
                    print("    This is YouTube's PLATFORM limit (uploadLimitExceeded), not API quota.")
                    print(f"    => this channel can upload ~{i - 1} videos per day (full + shorts combined).")
                    break
                if "quotaExceeded" in msg:
                    print(f"\n*** API QUOTA EXHAUSTED after {i - 1} uploads "
                          f"(~{(i - 1) * 1600:,} units) ***")
                    break
                print(f"  upload {i:3d}: other error: {msg[:130]}")
                time.sleep(2)
    finally:
        print(f"\ncleaning up {len(uploaded)} test video(s)...")
        for vid in uploaded:
            try:
                yt.videos().delete(id=vid).execute()
            except Exception:
                pass
        print("done. Deleted all probe videos.")


if __name__ == "__main__":
    main()
