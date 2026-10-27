"""DRY-RUN: List all YouTube videos and identify titles that don't match the documented standard.
Does NOT modify anything. Uses the same logic as rename_youtube_titles.py.
"""

import json
import time
from google.oauth2.credentials import Credentials
from google.auth.transport.requests import Request
from googleapiclient.discovery import build

with open("token.json") as f:
    data = json.load(f)
creds = Credentials.from_authorized_user_info(
    data, ["https://www.googleapis.com/auth/youtube"]
)
if not creds.valid:
    creds.refresh(Request())
yt = build("youtube", "v3", credentials=creds)

# Same metadata as rename_youtube_titles.py
HYMNS = {
    "thy word": ("Thy Word", "Amy Grant & Michael W. Smith", "1984"),
    "thy": ("Thy Word", "Amy Grant & Michael W. Smith", "1984"),
    "winchester": ("Winchester", "Thomas Olivers", "1770"),
    "emmanuel": ("Emmanuel", "Latin, 12th Century", "1710"),
    "praise him": ("Praise Him! Praise Him!", "Fanny J. Crosby", "1869"),
    "oh for a thousand": (
        "Oh, For a Thousand Tongues to Sing",
        "Charles Wesley",
        "1739",
    ),
    "he leadeth me": ("He Leadeth Me", "Joseph H. Gilmore", "1862"),
}
CLASSICAL = {
    "canon": ("Canon in D", "Johann Pachelbel", "1680"),
    "fur elise": ("Für Elise", "Ludwig van Beethoven", "1810"),
    "moonlight": ("Moonlight Sonata", "Ludwig van Beethoven", "1801"),
    "toccata": ("Toccata and Fugue in D minor", "Johann Sebastian Bach", "1704"),
    "nocturne": ("Nocturne Op. 9 No. 2", "Frédéric Chopin", "1832"),
    "clair": ("Clair de Lune", "Claude Debussy", "1905"),
    "amazing": ("Amazing Grace", "John Newton", "1779"),
    "how great": ("How Great Thou Art", "Carl Boberg", "1885"),
    "dyens": ("Valse en Skaï", "Roland Dyens", "1985"),
}
GENRE_MAP = {
    "psytrance": "Psytrance",
    "gabba": "Gabba",
    "dubstep": "Dubstep",
    "deep house": "Deep House",
    "detroit house": "Detroit House",
    "detroit techno": "Detroit Techno",
    "drum and bass": "Drum and Bass",
    "chip": "Chiptune",
    "hardstyle": "Hardstyle Trance",
    "synthwave": "Synthwave",
    "detroit": "Detroit Techno",
    "hardcore": "Gabba",
    "japanese": "Japanese Hardcore Techno",
    "brostep": "Dubstep",
    "dnb": "Drum and Bass",
    "8bit": "Chiptune",
    "neon": "Synthwave",
}


def detect_genre(t):
    for key, name in sorted(GENRE_MAP.items(), key=lambda x: -len(x[0])):
        if key in t:
            return name
    return None


def detect_speed(t):
    if "05x" in t or "0.5x" in t or "half" in t:
        return "Half-Speed (0.5x)"
    if "15x" in t or "1.5x" in t:
        return "1.5x Speed"
    if "20x" in t or "2.0x" in t:
        return "Double Speed (2.0x)"
    if "30x" in t or "3.0x" in t or "300bpm" in t:
        return "Triple Speed (3.0x)"
    return "1.0x Speed"


def detect_variant(t):
    if t.endswith(" b") or " b_" in t or t.rstrip().endswith("b"):
        return " [B]"
    if t.endswith(" a") or " a_" in t or t.rstrip().endswith("a"):
        return " [A]"
    return ""


def build_correct_title(title):
    orig = title.lower()
    if "hymn 2026 remix:" in orig and " | " in orig:
        return None
    if "classical remix" in orig and " | " in orig:
        return None
    genre = detect_genre(orig)
    speed = detect_speed(orig)
    variant = detect_variant(orig)
    for key, (name, author, year) in CLASSICAL.items():
        if key in orig:
            if not genre:
                genre = "Electronic"
            return f"{genre} Classical Remix - {name} ({author}, {year}) | {speed}{variant}"
    for key, (name, author, year) in HYMNS.items():
        if key in orig:
            if not genre:
                genre = "Electronic"
            return (
                f"{genre} Hymn 2026 Remix: {name} ({author}, {year}) | {speed}{variant}"
            )
    if "neon valse" in orig:
        if not genre:
            genre = "Electronic"
        return (
            f"{genre} Electronic Remix - Neon Valse (Original, 2026) | {speed}{variant}"
        )
    return None


def list_all():
    videos = []
    page_token = None
    while True:
        req = yt.search().list(
            part="snippet",
            forMine=True,
            maxResults=50,
            type="video",
            order="date",
            pageToken=page_token,
        )
        resp = req.execute()
        items = resp.get("items", [])
        for item in items:
            if "snippet" not in item:
                continue
            videos.append((item["id"]["videoId"], item["snippet"]["title"]))
        page_token = resp.get("nextPageToken")
        if not page_token or len(items) == 0:
            break
        time.sleep(0.2)
    return videos


if __name__ == "__main__":
    print("Fetching video list (read-only)...\n")
    videos = list_all()
    print(f"Total videos: {len(videos)}\n")
    wrong = 0
    ok = 0
    for vid, title in videos:
        new_title = build_correct_title(title)
        if new_title:
            wrong += 1
            print(f"[WRONG] {vid[:12]}: {title[:70]}")
            print(f"         -> {new_title[:80]}")
        else:
            ok += 1
    print(f"\n=== SUMMARY: {ok} correct, {wrong} wrong ===")
