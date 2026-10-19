"""Generate + upload UNIQUE custom thumbnails for YouTube videos.
Each thumbnail uses a DIFFERENT random Magnific clip + genre/hymn text overlay,
so no two videos share the same image.

Usage: python youtube_thumbnails.py [count]
  count = max thumbnails to set (default 50, quota ~200/day)
"""
import os, sys, subprocess, json, random, time, re
from google.oauth2.credentials import Credentials
from google.auth.transport.requests import Request
from googleapiclient.discovery import build
from googleapiclient.http import MediaFileUpload

ROOT = os.path.dirname(os.path.abspath(__file__))
CLIP_DIR = os.path.join(ROOT, "pipeline_output", "magnific_videos")
THUMB_DIR = os.path.join(ROOT, "pipeline_output", "thumbnails")
os.makedirs(THUMB_DIR, exist_ok=True)

GENRE_COLORS = {
    "Psytrance": "purple", "Dubstep": "red", "Deep House": "gold",
    "Drum and Bass": "cyan", "Chiptune": "green", "Gabba": "orange",
    "Detroit Techno": "silver", "Detroit House": "gold",
    "Hardstyle Trance": "yellow", "Hardstyle": "yellow", "Synthwave": "magenta",
}

def get_service():
    with open(os.path.join(ROOT, "token.json")) as f:
        data = json.load(f)
    creds = Credentials.from_authorized_user_info(data, ["https://www.googleapis.com/auth/youtube"])
    if not creds.valid:
        creds.refresh(Request())
    return build("youtube", "v3", credentials=creds)

def make_thumbnail(background_clip, genre, hymn, out_path):
    """Create a unique thumbnail: random Magnific clip + text overlay."""
    color = GENRE_COLORS.get(genre, "white")
    # Use a random start time in the clip for variety
    subprocess.run(["ffmpeg", "-y", "-loglevel", "error",
        "-ss", str(random.uniform(0, 5)), "-i", background_clip, "-vframes", "1",
        "-vf", f"scale=1280:720:force_original_aspect_ratio=increase,crop=1280:720,"
        f"drawtext=text='RESURRECTING':fontcolor={color}:fontsize=44:fontfile=/Windows/Fonts/impact.ttf:x=20:y=20:borderw=3:bordercolor=black,"
        f"drawtext=text='BEATS':fontcolor={color}:fontsize=52:fontfile=/Windows/Fonts/impact.ttf:x=20:y=70:borderw=3:bordercolor=black,"
        f"drawtext=text='{genre}':fontcolor=white:fontsize=30:fontfile=/Windows/Fonts/impact.ttf:x=20:y=130:borderw=2:bordercolor=black,"
        f"drawtext=text='{hymn}':fontcolor=white@0.9:fontsize=24:fontfile=/Windows/Fonts/tahoma.ttf:x=20:y=168:borderw=2:bordercolor=black",
        out_path], capture_output=True)
    return os.path.exists(out_path) and os.path.getsize(out_path) > 5000

def run(limit=50):
    yt = get_service()
    clips = [os.path.join(CLIP_DIR, f) for f in os.listdir(CLIP_DIR) if f.endswith((".mp4", ".webm"))]
    if not clips:
        print("No Magnific clips!")
        return
    
    # Track which clips we've used (to avoid repeats)
    used = set()
    
    done = 0
    page_token = None
    while done < limit:
        req = yt.search().list(part="snippet", forMine=True, maxResults=50, type="video", order="date", pageToken=page_token).execute()
        items = [i for i in req.get("items", []) if "snippet" in i]
        for item in items:
            if done >= limit:
                break
            vid = item["id"]["videoId"]
            title = item["snippet"]["title"]
            
            # Extract genre + hymn
            genre = "Psytrance"
            for g in GENRE_COLORS:
                if g.lower() in title.lower():
                    genre = g
                    break
            hymn = title.split("Remix:")[1].split("(")[0].strip() if "Remix:" in title else title.split(" - ")[-1][:30]
            
            # Pick a UNIQUE background clip (different from already-used)
            available = [c for c in clips if c not in used]
            if not available:
                used.clear()
                available = clips
            bg = random.choice(available)
            used.add(bg)
            
            thumb = os.path.join(THUMB_DIR, f"{vid}.jpg")
            if make_thumbnail(bg, genre, hymn, thumb):
                try:
                    yt.thumbnails().set(videoId=vid, media_body=MediaFileUpload(thumb)).execute()
                    done += 1
                    print(f"[{done}] {genre} - {hymn[:30]}")
                except Exception as e:
                    err = str(e)
                    if "quota" in err.lower() or "403" in err:
                        print(f"QUOTA at {done} thumbnails")
                        return done
                    pass
            time.sleep(0.4)
        
        page_token = req.get("nextPageToken")
        if not page_token:
            break
    
    return done

if __name__ == "__main__":
    count = int(sys.argv[1]) if len(sys.argv) > 1 else 50
    print(f"Generating {count} unique thumbnails...")
    n = run(count)
    print(f"\n{n} thumbnails set!")
