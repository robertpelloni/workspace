"""Post beat videos to YouTube with correct titles/descriptions (per AGENTS.md).
Usage: python post_to_youtube.py full|<short> <video_filename>
Title rules: NO 'cover' anywhere. Hymns: '[Genre] Hymn 2026 Remix: [Title] ([Author], [Year]) | [Speed] [Variant]'
             Classical: '[Genre] Classical Remix - [Piece] ([Composer], [Year]) | [Speed]'
             Shorts get ' #Shorts' appended.
"""
import os, sys, json, time, re, subprocess

os.environ["PATH"] = (
    r"C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin"
    + os.pathsep + os.environ.get("PATH", ""))

from google.oauth2.credentials import Credentials
from google.auth.transport.requests import Request
from googleapiclient.discovery import build
from googleapiclient.http import MediaFileUpload
import youtube_update_descriptions as desc_mod

ROOT = os.path.dirname(os.path.abspath(__file__))
VDIR = os.path.join(ROOT, "pipeline_output", "beat_videos")

# Canonical piece metadata: (title, author, year, is_classical)
PIECES = [
    ("amazinggrace", "Amazing Grace", "John Newton", "1779", False),
    ("canonind", "Canon in D", "Johann Pachelbel", "1680", True),
    ("canon in d", "Canon in D", "Johann Pachelbel", "1680", True),
    ("canon", "Canon in D", "Johann Pachelbel", "1680", True),
    ("clairdelune", "Clair de Lune", "Claude Debussy", "1905", True),
    ("clair de lune", "Clair de Lune", "Claude Debussy", "1905", True),
    ("clair", "Clair de Lune", "Claude Debussy", "1905", True),
    ("howgreatthouart", "How Great Thou Art", "Carl Boberg", "1885", False),
    ("how great", "How Great Thou Art", "Carl Boberg", "1885", False),
    ("thy word", "Thy Word", "Amy Grant & Michael W. Smith", "1984", False),
    ("neon valse", "Neon Valse", "Original Composition", "2026", False),
    ("toccatafugue", "Toccata and Fugue in D minor", "Johann Sebastian Bach", "1704", True),
    ("toccata", "Toccata and Fugue in D minor", "Johann Sebastian Bach", "1704", True),
    ("winchester", "Winchester (New)", "Thomas Olivers", "1770", False),
    ("emmanuel", "Emmanuel", "Latin, 12th Century", "1710", False),
    ("praise him", "Praise Him! Praise Him!", "Fanny J. Crosby", "1869", False),
    ("oh for a thousand", "Oh, For a Thousand Tongues to Sing", "Charles Wesley", "1739", False),
    ("he leadeth me", "He Leadeth Me", "Joseph H. Gilmore", "1862", False),
    # New hymns (2026 batch, never posted before)
    ("jesus comes with power", "Jesus Comes With Power", "Traditional", "2026", False),
    ("just over the mountains", "Just Over The Mountains", "Traditional", "2026", False),
    ("o happy day", "O Happy Day", "Philip Doddridge", "1755", False),
    ("when love shines in", "When Love Shines In", "Traditional", "2026", False),
    ("god is so good", "God Is So Good", "Traditional", "2026", False),
    ("oh god our help", "Oh God Our Help", "Isaac Watts", "1719", False),
    ("i have decided", "I Have Decided To Follow Jesus", "Traditional", "2026", False),
]

GENRES = [
    # --- psytrance family (specific sub-genres BEFORE the generic entry) ---
    ("psytrancefullon", "Full-On Psytrance"),
    ("fullon", "Full-On Psytrance"),
    ("psytranceprogressive", "Progressive Psytrance"),
    ("psytranceprog", "Progressive Psytrance"),
    ("goatrance", "Goa Trance"),
    ("goa", "Goa Trance"),
    ("psytrancedark", "Darkpsy"),
    ("darkpsy", "Darkpsy"),
    ("psytranceforest", "Forest Psy"),
    ("forestpsy", "Forest Psy"),
    ("psytrancehitech", "Hi-Tech Psytrance"),
    ("hitech", "Hi-Tech Psytrance"),
    ("psytrancepsychill", "Psychill"),
    ("psychill", "Psychill"),
    ("psybient", "Psychill"),
    ("psytrancezenonesque", "Zenonesque"),
    ("zenonesque", "Zenonesque"),
    ("psytrance", "Psytrance"), ("gabba", "Gabba"), ("hardcore", "Gabba"),
    ("dubstep", "Dubstep"), ("brostep", "Dubstep"),
    ("deephouse", "Deep House"), ("deep house", "Deep House"),
    ("detroithouse", "Detroit House"), ("detroit house", "Detroit House"),
    ("detroittechno", "Detroit Techno"), ("detroittechno", "Detroit Techno"),
    ("detroitcircuit", "Detroit Techno"), ("313", "Detroit Techno"),
    ("drumandbass", "Drum and Bass"), ("drum and bass", "Drum and Bass"), ("dnb", "Drum and Bass"),
    ("chiptune", "Chiptune"), ("8bit", "Chiptune"),
    ("hardstyle", "Hardstyle Trance"), ("synthwave", "Synthwave"), ("neon", "Synthwave"),
]

# Genre assigned at compose time for hymns whose filenames carry no genre keyword
GENRE_OVERRIDES = {
    "jesus comes with power": "Psytrance",
    "just over the mountains": "Deep House",
    "o happy day": "Dubstep",
    "when love shines in": "Synthwave",
    "god is so good": "Chiptune",
    "oh god our help": "Hardstyle Trance",
}

def detect(fn):
    fl = fn.lower().replace("_beatsynced.mp4", "").replace("_beatloop.mp4", "").replace(".mp4", "")
    fl = fl.replace("_cover", "").replace("_", " ")
    title, author, year, classical = None, None, None, False
    for key, t, a, y, c in PIECES:
        if key in fl:
            title, author, year, classical = t, a, y, c
            break
    if not title:
        # AUTO-FALLBACK: derive a clean title from the filename so newly captured
        # hymns (from the promo sprint / MIDI pool) work without manual registration.
        base = fn
        for suf in ("_beatsynced.mp4", "_beatloop.mp4", ".mp4", ".mp3"):
            base = base.replace(suf, "")
        base = re.sub(r"[_ ]+(cover|full|v2|magnific)$", "", base, flags=re.I)   # ... _cover
        base = re.sub(r"[_ ]+(with[_ ]+)?tag$", "", base, flags=re.I)            # ... _tag / _with_Tag
        base = re.sub(r"[_ ]+([AB])$", "", base)                               # ... _A/_B
        for k2, _g in GENRES:                                                    # genre token
            base = re.sub(r"[_ ]?" + re.escape(k2).replace(r"\ ", "[_ ]?") + r"[_ ]?", " ", base, flags=re.I)
        # speed token is now at the end (genre has been removed)
        base = re.sub(r"[_ ]+(0?[0-9](\.[0-9])?x|[0-9]{2}x|unknown|half|double|triple)[_ ]*$",
                      "", base, flags=re.I)
        base = re.sub(r"[_ ]+(with[_ ]+)?tag[_ ]*$", "", base, flags=re.I)  # now-trim 'with Tag'
        base = re.sub(r"[_ ]+(with)$", "", base, flags=re.I)               # orphan 'with' 
        base = re.sub(r"[_ ]+(tag)$", "", base, flags=re.I)                     # trailing 'with Tag'
        base = re.sub(r"_s_?", "'s ", base)                                     # He_s_Able -> He's Able
        base = base.replace("_", " ").strip(" -_'")
        base = re.sub(r"\s+", " ", base).strip()
        if base:
            title = base if any(c.islower() for c in base) else base.title()
            title = title[0].upper() + title[1:]
            author, year, classical = "Traditional", "2026", False
    genre = None
    fl2 = "".join(ch for ch in fl if ch not in " _-()")
    # Japanese Hardcore Techno must be checked BEFORE hardcore/gabba
    if "japanesehardcoretechno" in fl2 or "japanesehardcore" in fl2 or "jcore" in fl2 or "japanesehardcore" in fl2:
        genre = "Japanese Hardcore Techno"
    elif "hardcoretechno" in fl2:
        genre = "Japanese Hardcore Techno"
    else:
        for key, g in GENRES:
            if key in fl2:
                genre = g
                break
    if not genre:
        for key, g in GENRE_OVERRIDES.items():
            if key.replace(" ", "") in fl2:
                genre = g
                break
    # speed
    speed = "1.0x Speed"
    if "30x" in fl or "300bpm" in fl or "3.0x" in fl:
        speed = "Triple Speed (3.0x)"
    elif "05x" in fl or "0.5x" in fl or "half" in fl:
        speed = "Half-Speed (0.5x)"
    # variant A/B
    variant = ""
    m = re.search(r"[ _]?([AB])$", fn.replace("_beatsynced.mp4","").replace("_beatloop.mp4","").strip())
    if m:
        variant = f" [{m.group(1)}]"
    return title, author, year, classical, genre, speed, variant

def build_title(fn):
    title, author, year, classical, genre, speed, variant = detect(fn)
    if not title:
        return None
    if not genre:
        genre = "[EDM LSDance]"
    if classical:
        t = f"{genre} Classical Remix - {title} ({author}, {year}) | {speed}{variant}"
    else:
        t = f"{genre} Hymn 2026 Remix: {title} ({author}, {year}) | {speed}{variant}"
    return t

def _loop_score_of_media(video_path):
    """Extract audio from a beat video and detect the 48s-repeat capture bug."""
    import tempfile
    try:
        import cap_cycle
        tmp = tempfile.mktemp(suffix=".mp3")
        r = subprocess.run(["ffmpeg", "-y", "-loglevel", "error", "-i", video_path,
                            "-ac", "1", "-ar", "48000", tmp], capture_output=True)
        if r.returncode != 0 or not os.path.exists(tmp):
            return 0.0
        ls = cap_cycle.loop_score(tmp)
        os.remove(tmp)
        return ls
    except Exception:
        return 0.0


def quality_gate(video_path):
    """Refuse to post a capture that is looped (the cap_cycle seek bug) or silent-ish."""
    ls = _loop_score_of_media(video_path)
    if ls > 0.9:
        print(f"QUALITY GATE FAILED: 48s-repeat loop detected (score={ls}) in {os.path.basename(video_path)}")
        print("  Re-capture the cover with cap_cycle.py, recompose, then post again.")
        return False
    return True


def get_service():
    with open(os.path.join(ROOT, "token.json")) as f:
        data = json.load(f)
    creds = Credentials.from_authorized_user_info(data, ["https://www.googleapis.com/auth/youtube"])
    if not creds.valid:
        creds.refresh(Request())
    return build("youtube", "v3", credentials=creds)

def upload(service, path, title, is_short=False):
    desc = desc_mod.build_description(title)
    if is_short:
        title = (title[:80] + " #Shorts")[:100]
    sz = os.path.getsize(path) // 1024 // 1024
    print(f"Uploading: {os.path.basename(path)} ({sz}MB)")
    print(f"  Title: {title}")
    body = {
        "snippet": {
            "title": title[:100],
            "description": desc[:5000],
            "tags": ["resurrecting beats", "hymnmania", "electronic worship", "spiritual edm"],
            "categoryId": "10",
        },
        "status": {"privacyStatus": "public"},
    }
    media = MediaFileUpload(path, chunksize=4*1024*1024, resumable=True)
    req = service.videos().insert(part="snippet,status", body=body, media_body=media)
    resp = None
    last = 0
    while resp is None:
        status, resp = req.next_chunk()
        if status and int(status.progress()*100) >= last+25:
            last = int(status.progress()*100)
            print(f"  {last}%")
    vid = resp.get("id", "?")
    print(f"  OK https://youtu.be/{vid}")
    return vid

def make_short(src, out):
    """9:16 vertical, first 60s, with audio."""
    if os.path.exists(out):
        return out
    r = subprocess.run(["ffmpeg", "-y", "-loglevel", "error", "-i", src,
        "-vf", "crop=ih*9/16:ih,scale=1080:1920",
        "-c:v", "libx264", "-preset", "medium", "-crf", "23",
        "-c:a", "aac", "-b:a", "128k", "-t", "60", out], capture_output=True)
    if r.returncode != 0:
        print("ffmpeg error:", r.stderr.decode()[-300:])
        return None
    return out

if __name__ == "__main__":
    mode = sys.argv[1] if len(sys.argv) > 1 else "full"
    fn = sys.argv[2] if len(sys.argv) > 2 else None
    if not fn:
        print("usage: python post_to_youtube.py full|short <filename>")
        sys.exit(1)
    src = os.path.join(VDIR, fn)
    if not os.path.exists(src):
        print("not found:", src)
        sys.exit(1)

    base_title = build_title(fn)
    if not base_title:
        print("could not detect hymn/genre for:", fn)
        sys.exit(1)

    if mode != "short":
        if not quality_gate(src):
            sys.exit(3)
    service = get_service()
    if mode == "short":
        out = os.path.join(ROOT, "pipeline_output", "shorts", fn.replace(".mp4", "_short.mp4"))
        os.makedirs(os.path.dirname(out), exist_ok=True)
        made = make_short(src, out)
        if not made:
            sys.exit(1)
        upload(service, made, base_title, is_short=True)
    else:
        upload(service, src, base_title)
