"""Upload all MilkDrop videos to YouTube in batch."""
import os, sys, json, glob, time
sys.stdout.reconfigure(encoding="utf-8", errors="replace")

from google.oauth2.credentials import Credentials
from google.auth.transport.requests import Request
from googleapiclient.discovery import build
from googleapiclient.http import MediaFileUpload

ROOT = os.path.dirname(os.path.abspath(__file__))
GEN = os.path.join(ROOT, "generated")
TOKEN = os.path.join(ROOT, "token.json")

SCOPES = ["https://www.googleapis.com/auth/youtube"]

def get_service():
    with open(TOKEN) as f:
        data = json.load(f)
    creds = Credentials.from_authorized_user_info(data, SCOPES)
    if not creds.valid:
        creds.refresh(Request())
    return build("youtube", "v3", credentials=creds)

def upload_video(service, path, title, desc, tags):
    print(f"\n{'='*60}")
    print(f"Uploading: {os.path.basename(path)}")
    print(f"  Title: {title}")
    print(f"  Size: {os.path.getsize(path)//1024//1024}MB")

    body = {
        "snippet": {
            "title": title[:100],
            "description": desc[:5000],
            "tags": tags[:500],
            "categoryId": "10",
        },
        "status": {"privacyStatus": "public"},
    }

    media = MediaFileUpload(path, chunksize=4*1024*1024, resumable=True)
    request = service.videos().insert(part="snippet,status", body=body, media_body=media)

    response = None
    last_progress = 0
    while response is None:
        status, response = request.next_chunk()
        if status:
            pct = int(status.progress() * 100)
            if pct >= last_progress + 10:
                print(f"  Upload: {pct}%")
                last_progress = pct

    vid = response.get("id", "?")
    print(f"  ✅ https://youtu.be/{vid}")
    return vid

TRACK_FILE = os.path.join(ROOT, ".uploaded_videos.txt")

def load_uploaded():
    if os.path.exists(TRACK_FILE):
        with open(TRACK_FILE) as f:
            return set(line.strip() for line in f if line.strip())
    return set()

def save_uploaded(vid, path):
    with open(TRACK_FILE, "a") as f:
        f.write(f"{vid} | {os.path.basename(path)}\n")

if __name__ == "__main__":
    videos = sorted(glob.glob(os.path.join(GEN, "*_projectm.mp4")))
    if not videos:
        print("No videos found")
        sys.exit(1)

    uploaded = load_uploaded()
    basenames_uploaded = set(line.split(" | ", 1)[-1] for line in uploaded if " | " in line)
    videos = [v for v in videos if os.path.basename(v) not in basenames_uploaded]

    if not videos:
        print("All videos already uploaded!")
        sys.exit(0)

    print(f"Found {len(videos)} videos to upload ({len(basenames_uploaded)} already done)")
    service = get_service()

    GENRE_LABELS = {
        'dnb': 'Drum & Bass', 'drum and bass': 'Drum & Bass',
        'deep_house': 'Deep House', 'deep house': 'Deep House',
        'dubstep': 'Dubstep',
        'psytrance': 'Psytrance',
    }

    # Known hymn metadata (title -> (year, author))
    HYMN_META = {
        'amazing grace': ('1779', 'John Newton'),
    }

    results = []
    for path in videos:
        base = os.path.basename(path).replace("_projectm.mp4", "")
        parts = base.rsplit("_", 1)  # split version A/B
        version = parts[-1] if parts[-1] in ('A', 'B') else ''
        rest = parts[0] if version else base

        # Parse: "Amazing Grace 108 0.5x deep_house"
        rest_clean = rest.replace("_", " ")
        # Extract speed (0.5x, 1.0x, 1.5x, 2.0x, 05x, 10x, 15x, 20x)
        import re
        speed_match = re.search(r'(\\d+[.]?\\d*)x', rest_clean)
        speed = speed_match.group(0) if speed_match else ''
        rest_no_speed = rest_clean.replace(speed, '').strip() if speed else rest_clean

        # Split remaining into hymn name + genre
        genre = ''
        hymn_name = rest_no_speed
        for glabel in ['deep house', 'deep_house', 'dnb', 'dubstep', 'psytrance']:
            if glabel in rest_no_speed:
                genre = GENRE_LABELS.get(glabel, glabel.title())
                hymn_name = rest_no_speed.replace(glabel, '').replace('deep_house', '').strip()
                break

        # Map speed to cleaner format for YouTube title
        if speed:
            speed_val = speed.lower().replace('x', '')
            if speed_val in ('05', '0.5'):
                speed_display = '1/2X'
            elif speed_val in ('10', '1.0', '1'):
                speed_display = '1X'
            elif speed_val in ('15', '1.5'):
                speed_display = '1.5X'
            elif speed_val in ('20', '2.0', '2'):
                speed_display = '2X'
            else:
                speed_display = speed.upper()
        else:
            speed_display = '1X'

        if not genre:
            genre = 'Psytrance'

        # Clean up hymn name — remove trailing catalog numbers like "108" but keep title numbers like "Sabbath 2"
        known_title_numbers = {'sabbath 2', 'hymn 108', 'song 2'}
        hymn_lower = hymn_name.lower().strip()
        # Only strip trailing number if it's a catalog number (3+ digits) and not a known title
        import re
        m = re.search(r'\s+(\d{3,})$', hymn_name)
        if m and hymn_lower.replace(m.group(0).strip(), '').strip() not in known_title_numbers:
            hymn_name = hymn_name[:m.start()].strip()
        elif re.search(r'\s+\d+$', hymn_name):
            stripped = re.sub(r'\s+\d+$', '', hymn_name).strip()
            if stripped.lower() not in known_title_numbers:
                hymn_name = stripped
        if hymn_name.startswith('02'):
            hymn_name = hymn_name[2:].strip()
        # Restore apostrophes lost from underscore naming
        for fix, correct in [(" s ", "'s "), (" t ", "'t "), (" re ", "'re "), (" ve ", "'ve "), (" ll ", "'ll "), (" m ", "'m ")]:
            hymn_name = hymn_name.replace(fix, correct)
        if hymn_name.endswith(" s"):
            hymn_name = hymn_name[:-2] + "'s"

        # Look up hymn metadata
        meta = HYMN_META.get(hymn_name.lower().strip(), (None, None))
        year, author = meta[0], meta[1]
        if author and year:
            meta_str = f" ({author}, {year})"
        elif author:
            meta_str = f" ({author})"
        elif year:
            meta_str = f" ({year})"
        else:
            meta_str = ""

        title = f"{genre} Hymn Remix: {hymn_name}{meta_str}"
        desc = (
            "A traditional hymn reimagined as electronic music using AI generation.\n\n"
            "Generated by HymnMania — transforming hymns into modern electronic music.\n"
            f"Audio: Suno AI | Visualizer: Real MilkDrop via projectM 4.1.0\n"
            f"\nTrack: {hymn_name}\n"
        )
        tags = ["hymn", genre.lower(), "electronic", "ai music", "hymnmania", "milkdrop"]

        print(f"  Title: {title}")
        vid = upload_video(service, path, title, desc, tags)
        if vid:
            save_uploaded(vid, path)
        results.append((hymn_name, vid))
        time.sleep(2)

    print(f"\n{'='*60}")
    print(f"✅ All {len(results)} uploaded!")
    for name, vid in results:
        print(f"  {name}: https://youtu.be/{vid}")
