"""Rename ALL YouTube videos to documented standard format.

Hymn format:  [Genre] Hymn 2026 Remix: [Title] ([Author], [Year]) | [Speed] [Variant]
Classical:    [Genre] Classical Remix - [Piece] ([Composer], [Year]) | [Speed]
"""
import json, time, re
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

# Hymn metadata
HYMNS = {
    "thy word": ("Thy Word", "Amy Grant & Michael W. Smith", "1984"),
    "thy": ("Thy Word", "Amy Grant & Michael W. Smith", "1984"),
    "winchester": ("Winchester", "Thomas Olivers", "1770"),
    "emmanuel": ("Emmanuel", "Latin, 12th Century", "1710"),
    "praise him": ("Praise Him! Praise Him!", "Fanny J. Crosby", "1869"),
    "oh for a thousand": ("Oh, For a Thousand Tongues to Sing", "Charles Wesley", "1739"),
    "he leadeth me": ("He Leadeth Me", "Joseph H. Gilmore", "1862"),
    "amazing grace": ("Amazing Grace", "John Newton", "1779"),
    "how great thou art": ("How Great Thou Art", "Carl Boberg", "1885"),
    "how great": ("How Great Thou Art", "Carl Boberg", "1885"),
    "howgreat": ("How Great Thou Art", "Carl Boberg", "1885"),
    "amazinggrace": ("Amazing Grace", "John Newton", "1779"),
    "amazing": ("Amazing Grace", "John Newton", "1779"),
}

CLASSICAL = {
    "canon": ("Canon in D", "Johann Pachelbel", "1680"),
    "fur elise": ("Für Elise", "Ludwig van Beethoven", "1810"),
    "moonlight": ("Moonlight Sonata", "Ludwig van Beethoven", "1801"),
    "toccata": ("Toccata and Fugue in D minor", "Johann Sebastian Bach", "1704"),
    "nocturne": ("Nocturne Op. 9 No. 2", "Frédéric Chopin", "1832"),
    "clair": ("Clair de Lune", "Claude Debussy", "1905"),
    "dyens": ("Valse en Skaï", "Roland Dyens", "1985"),
}

GENRE_MAP = {
    "psytrance": "Psytrance", "gabba": "Gabba", "dubstep": "Dubstep",
    "deep house": "Deep House", "deephouse": "Deep House",
    "detroit house": "Detroit House", "detroithouse": "Detroit House",
    "detroit techno": "Detroit Techno", "detroittechno": "Detroit Techno",
    "drum and bass": "Drum and Bass", "drumandbass": "Drum and Bass",
    "chip": "Chiptune", "hardstyle": "Hardstyle Trance",
    "synthwave": "Synthwave", "detroit": "Detroit Techno",
    "hardcore": "Gabba", "japanese": "Japanese Hardcore Techno",
    "brostep": "Dubstep", "dnb": "Drum and Bass",
    "8bit": "Chiptune", "neon": "Synthwave",
}

def detect_genre(title_lower):
    # "DnB Rechip" must be Drum and Bass — the "chip" inside "Rechip" is a false positive
    if "dnb" in title_lower or "drum and bass" in title_lower or "drumandbass" in title_lower:
        return "Drum and Bass"
    for key, name in sorted(GENRE_MAP.items(), key=lambda x: -len(x[0])):
        if key in title_lower:
            return name
    return None

def detect_speed(title_lower):
    if "05x" in title_lower or "0.5x" in title_lower or "half" in title_lower:
        return "Half-Speed (0.5x)"
    if "15x" in title_lower or "1.5x" in title_lower:
        return "1.5x Speed"
    if "20x" in title_lower or "2.0x" in title_lower:
        return "Double Speed (2.0x)"
    if "30x" in title_lower or "3.0x" in title_lower or "300bpm" in title_lower:
        return "Triple Speed (3.0x)"
    return "1.0x Speed"

def detect_variant(title_lower):
    if title_lower.endswith(" b") or " b_" in title_lower or title_lower.rstrip().endswith("b"):
        return " [B]"
    if title_lower.endswith(" a") or " a_" in title_lower or title_lower.rstrip().endswith("a"):
        return " [A]"
    return ""

def build_correct_title(title, description=""):
    orig = title.lower()
    is_shorts = "#shorts" in orig
    # Process without the #Shorts suffix (re-appended at the end if needed)
    clean = orig.replace("#shorts", "").strip()
    # Fix "Unknown Hymn 2026 Remix: ..." — strip the misleading prefix
    was_unknown = clean.startswith("unknown hymn") or clean.startswith("unknown ")
    if was_unknown:
        if clean.startswith("unknown "):
            clean = clean[len("unknown "):].strip()
        if clean.startswith("hymn 2026 remix: ") or clean.startswith("classical remix "):
            pass  # leave the Remix part intact
    
    # Already correct (skip) — but NOT if it had an Unknown prefix
    already = (("hymn 2026 remix:" in clean or "classical remix" in clean)
               and " | " in clean and not clean.startswith("electronic "))
    if already and not was_unknown:
        return None
    
    genre = detect_genre(clean)
    if not genre and is_shorts:
        genre = detect_genre(orig)
    
    # For "unknown <genre>" filenames, the REAL genre is the keyword after "unknown"
    # (e.g. "Brostep Breaker Mix unknown gabba A" -> Gabba, not Dubstep)
    unknown_genre = None
    import re as _re
    m = _re.search(r"unknown\s+([a-z0-9 _&]+?)\s*([ab]|cover)?\s*$", clean)
    if m and "unknown" in clean:
        cand = m.group(1).strip()
        if cand:
            detected = detect_genre(cand)
            if detected:
                unknown_genre = detected
    if unknown_genre:
        genre = unknown_genre
    
    # If title has no genre, try extracting from description
    if not genre and description:
        desc_lower = description.lower()
        if "genre:" in desc_lower:
            genre_line = desc_lower.split("genre:")[1].split(chr(10))[0].strip()
            # Parse "Psytrance / Electronic Worship" -> "Psytrance"
            extracted = genre_line.split(" / ")[0].strip()
            # Only use if it's a known genre, not "Electronic Worship" or empty
            if extracted and "electronic worship" not in extracted and extracted != "electronic" \
               and "unknown" not in extracted.lower():
                genre = extracted.title()
    
    # Fallback placeholder if genre still unknown
    if not genre:
        genre = "[EDM LSDance]"
    
    speed = detect_speed(clean)
    variant = detect_variant(clean)
    
    # Find which piece
    for key, (name, author, year) in CLASSICAL.items():
        if key in clean:
            if not genre:
                genre = "[EDM LSDance]"
            return f"{genre} Classical Remix - {name} ({author}, {year}) | {speed}{variant}" + (" #Shorts" if is_shorts else "")
    
    for key, (name, author, year) in HYMNS.items():
        if key in clean:
            if not genre:
                genre = "[EDM LSDance]"
            return f"{genre} Hymn 2026 Remix: {name} ({author}, {year}) | {speed}{variant}" + (" #Shorts" if is_shorts else "")
    
    # Neon Valse
    if "neon valse" in clean:
        if not genre:
            genre = "[EDM LSDance]"
        return f"{genre} Electronic Remix - Neon Valse (Original, 2026) | {speed}{variant}" + (" #Shorts" if is_shorts else "")
    
    return None


def rename_all():
    renamed = 0
    page_token = None
    
    while True:
        req = yt.search().list(
            part="snippet", forMine=True, maxResults=50, type="video", order="date",
            pageToken=page_token
        )
        resp = req.execute()
        items = resp.get("items", [])
        
        for item in items:
            if "snippet" not in item:
                continue
            vid = item["id"]["videoId"]
            title = item["snippet"]["title"]
            desc = item["snippet"].get("description", "")
            
            new_title = build_correct_title(title, desc)
            if new_title is None:
                continue
            
            try:
                yt.videos().update(
                    part="snippet",
                    body={"id": vid, "snippet": {"title": new_title, "categoryId": "10"}},
                ).execute()
                renamed += 1
                print(f"[{renamed}] {title[:60]} -> {new_title[:80]}")
                time.sleep(0.3)
            except Exception as e:
                err = str(e)
                if "quota" in err.lower() or "403" in err:
                    print(f"QUOTA after {renamed}")
                    return renamed
                print(f"  SKIP [{vid[:8]}]: {err[:60]}")
                time.sleep(0.5)
        
        page_token = resp.get("nextPageToken")
        if not page_token or len(items) == 0:
            break
    
    return renamed


if __name__ == "__main__":
    print("Renaming ALL YouTube videos to standard format...\n")
    total = rename_all()
    print(f"\n{total} titles renamed!")
