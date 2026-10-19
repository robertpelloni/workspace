"""Update all YouTube video descriptions to the official Hymnmania template.

Template spec:
  ARTIST: HYMNMANIA
  RECORD LABEL: RESURRECTING BEATS
  Full description with Mission, Science, How We Make Our Music sections.
"""
import json, time, re
from google.oauth2.credentials import Credentials
from google.auth.transport.requests import Request
from googleapiclient.discovery import build

with open("token.json") as f:
    data = json.load(f)
creds = Credentials.from_authorized_user_info(data, ["https://www.googleapis.com/auth/youtube"])
if not creds.valid:
    creds.refresh(Request())
yt = build("youtube", "v3", credentials=creds)

# Hymn metadata
HYMNS = {
    "thy word": ("Thy Word", "Amy Grant & Michael W. Smith", "1984"),
    "winchester": ("Winchester (New)", "Thomas Olivers", "1770"),
    "emmanuel": ("Emmanuel", "Latin, 12th Century", "1710"),
    "praise him": ("Praise Him! Praise Him!", "Fanny J. Crosby", "1869"),
    "oh for a thousand tongues": ("Oh, For a Thousand Tongues to Sing", "Charles Wesley", "1739"),
    "he leadeth me": ("He Leadeth Me", "Joseph H. Gilmore", "1862"),
    "neon valse": ("Neon Valse", "Original Composition", "2026"),
    "garoto": ("Aqui Estou", "Anibal Augusto Sardinha (Garoto)", "1950"),
    "dyens": ("Valse en Skai", "Roland Dyens", "1985"),
    "canon": ("Canon in D", "Johann Pachelbel", "1680"),
    "fur elise": ("Fur Elise", "Ludwig van Beethoven", "1810"),
    "moonlight": ("Moonlight Sonata", "Ludwig van Beethoven", "1801"),
    "toccata": ("Toccata and Fugue in D minor", "Johann Sebastian Bach", "1704"),
    "nocturne": ("Nocturne Op. 9 No. 2", "Frederic Chopin", "1832"),
    "clair": ("Clair de Lune", "Claude Debussy", "1905"),
    "amazing grace": ("Amazing Grace", "John Newton", "1779"),
    "how great": ("How Great Thou Art", "Carl Boberg", "1885"),
    # New hymns (2026 batch)
    "jesus comes with power": ("Jesus Comes With Power", "Traditional", "2026"),
    "just over the mountains": ("Just Over The Mountains", "Traditional", "2026"),
    "o happy day": ("O Happy Day", "Philip Doddridge", "1755"),
    "when love shines in": ("When Love Shines In", "Traditional", "2026"),
    "god is so good": ("God Is So Good", "Traditional", "2026"),
    "oh god our help": ("Oh God Our Help", "Isaac Watts", "1719"),
    "i have decided": ("I Have Decided To Follow Jesus", "Traditional", "2026"),
}

GENRE_KEYWORDS = {
    "psytrance": ("Psytrance", "a hyper-dimensional sacred geometry journey blending neon aesthetics with the high-energy frequency of this classic hymn"),
    "deep house": ("Deep House", "smooth, soulful house grooves that wrap this sacred melody in warm golden-hour energy"),
    "drum and bass": ("Drum and Bass", "high-octane breakbeats that drive through neon-soaked cyberpunk cathedrals"),
    "dubstep": ("Dubstep", "earth-shattering bass drops that merge worship with pure electronic energy"),
    "gabba": ("Gabba / Hardcore", "industrial hardcore worship at its most intense — pounding kicks, warehouse strobes, and divine frequency"),
    "chiptune": ("Chiptune", "retro 8-bit worship through pixel-perfect glitching digital cathedrals"),
    "detroit techno": ("Detroit Techno", "stark industrial beauty meets rhythmic precision in this underground gospel reimagining"),
    "detroit house": ("Detroit House", "deep Motor City grooves breathing soul into sacred melody"),
    "hardstyle": ("Hardstyle Trance", "euphoric hardstyle kicks and soaring melodies transforming this hymn into pure energy"),
    "synthwave": ("Synthwave", "neon-drenched retro-future worship reimagined through vintage synths and pulsing basslines"),
    "japanese": ("J-Core / Japanese Hardcore Techno", "intense Japanese hardcore energy meeting divine frequency"),
}

VISUAL_STYLES = {
    "Psytrance": "A hyper-dimensional visual journey blending sacred geometry with neon aesthetics, matching the high-energy frequency of this classic hymn.",
    "Deep House": "Warm, atmospheric visuals flow like golden-hour light through cathedral architecture, matching the smooth, soulful energy of this track.",
    "Drum and Bass": "Rain-soaked neon streets and cyberpunk cityscapes pulse in sync with the relentless breakbeats.",
    "Dubstep": "Seismic bass visualizations ripple through futuristic cathedral spaces as strobes and particle systems erupt with each drop.",
    "Gabba / Hardcore": "Industrial warehouse visuals with raw strobe effects and pounding kick-drum visualizations match the intensity of this hardcore worship track.",
    "Detroit Techno": "Stark warehouse shadows and light — a monochromatic journey through the birthplace of techno, reimagined for spiritual elevation.",
    "Detroit House": "Warm Motor City textures flow through cathedral architecture, blending soulful house grooves with sacred geometry.",
    "Chiptune": "Pixel-perfect 8-bit cathedrals and glitching digital stained glass create a retro worship arcade experience.",
    "Hardstyle Trance": "Euphoric laser shows and soaring light columns match the euphoric kicks and melodies of this hardstyle transformation.",
    "Synthwave": "Neon-drenched retro grids and palm trees stretch into infinite digital horizons as this synthwave reimagining unfolds.",
}

def get_hymn(title_lower):
    for key, (name, author, year) in HYMNS.items():
        if key in title_lower:
            return name, author, year
    return None, None, None

def get_genre(title_lower):
    for key, (genre_name, blurb) in GENRE_KEYWORDS.items():
        if key in title_lower.lower():
            return genre_name, blurb
    return "Electronic Worship", "a futuristic visual journey blending digital art with sacred melodies"

def get_variant(title_lower):
    if "0.5x" in title_lower or "half" in title_lower:
        return "Half-Speed (0.5x)"
    if "1.5x" in title_lower:
        return "1.5x Speed"
    if "2.0x" in title_lower:
        return "Double Speed (2.0x)"
    if "3.0x" in title_lower or "30x" in title_lower:
        return "Triple Speed (3.0x)"
    return "Original Mix"

# Hashtag bank (draw from these, NEVER exceed 15 combined per post)
CORE_TAGS = ["#EDM", "#ResurrectingBeats", "#Hymnmania", "#SpiritualEDM", "#Art", "#Dance", "#LOVE", "#ElectronicMusic2026"]
PSYTRANCE_TAGS = ["#Psytrance", "#PsychedelicTrance", "#PsytranceFamily"]
SECONDARY_TAGS = ["#WorshipMusic", "#MentalHealthAwareness", "#UNITY"]
HASHTAG_BANK = [
    "#StudyMusic", "#GamingMusic", "#WorkoutMusic", "#TrippyVisuals", "#PsychedelicVisuals",
    "#BassMusic", "#EDMProducer", "#PsytranceProducer", "#MusicProduction", "#FLStudioEDM",
    "#AbletonLive", "#DJSet", "#TrackPreview", "#Ajja", "#PsychedelicMusic",
    "#PsytranceWorld", "#PsytranceCulture", "#PsytranceArt", "#PsytranceCommunity",
    "#Zenonesque", "#HiTechPsytrance", "#MelodicEDM", "#ProgressiveTrance", "#DanceLiveLoveArtLife",
    "#Trance", "#House", "#BPM", "#Creativity", "#SpiritualEnlightenment", "#Spirituality",
]


def build_hashtags(genre_name):
    """Build <=15 hashtags. Always includes Psytrance (1-3) + dedicated genre."""
    tags = list(CORE_TAGS)  # 8 core tags
    tags.extend(PSYTRANCE_TAGS[:2])  # always 2 psytrance tags
    # Dedicated genre tag (if not already psytrance)
    genre_tag = f"#{genre_name.replace(' ', '')}"
    if genre_tag not in tags:
        tags.append(genre_tag)
    tags.extend(SECONDARY_TAGS)  # 3 secondary
    # Fill remaining with bank tags to reach 15
    for bank_tag in HASHTAG_BANK:
        if len(tags) >= 15:
            break
        if bank_tag not in tags:
            tags.append(bank_tag)
    return " ".join(tags[:15])


def build_description(title):
    tl = title.lower()
    hymn_name, author, year = get_hymn(tl)
    if not hymn_name:
        # Extract from title
        hymn_name = title.replace("_", " ").replace("[Artist=Resurrecting Beats/Hymnmania]", "").strip()[:60]
        author = "Traditional"
        year = "2026"
    
    genre_name, genre_blurb = get_genre(tl)
    variant = get_variant(tl)
    visual_style = VISUAL_STYLES.get(genre_name, "A futuristic visual journey blending digital art with sacred melodies.")
    
    # Clean song title for display
    if hymn_name in ["Thy Word", "Emmanuel", "Winchester (New)"]:
        song_title = f'"{hymn_name}"'
    else:
        song_title = hymn_name
    
    desc = f"""Track Details:
🏷️ Artist: Resurrecting Beats ft. {author}
🎼 Track: {song_title}
🎹 Genre: {genre_name} / Electronic Worship
📅 Year: 2026
⚡ Tempo/Variant: {variant}

About this video:
{visual_style}

🙏 Our Mission:
Welcome to Resurrecting Beats, your ultimate destination for electronic worship. Our mission is to bring the world Psytrance and other electronic genres reimagined with the hymns we have all grown to love over the years. We want to honor God by taking every hymn we can and mixing them with futuristic soundscapes. We believe that psytrance is more than just music — it's life, and a powerful vehicle for spiritual and mental elevation.

🧠 The Science of Psytrance & Healing:
We love psytrance because it profoundly engages the brain. Characterized by hypnotic, complex, and repetitive arpeggiated melodies with fast tempos (140-150+ BPM), the highly rhythmic patterns stimulate the motor cortex, while the structural build-ups and unpredictable drops activate the reward pathway, releasing dopamine.

Its driving, repetitive qualities can induce a state of "transient hypofrontality," quieting the brain's overactive analytical centers — similar to deep meditation, prayer, or non-REM sleep stages. Highly immersive music can also modulate the amygdala (the brain's emotional "almond"), helping regulate responses to stress and trauma when paired with positive stimuli or the catharsis of dancing.

While active and mindful listening to music is a scientifically proven tool that helps reduce symptoms of anxiety by lowering cortisol (the primary stress hormone) and boosting neurochemicals like serotonin, it is not a cure for clinical depression. It acts as an incredibly effective adjunctive treatment to counteract feelings of hopelessness.

*If you are experiencing depression, it is highly recommended to seek professional support. You can locate accredited therapists and mental health resources via the SAMHSA National Helpline: https://www.samhsa.gov/find-help/helplines/national-helpline*

⚙️ How We Make Our Music:
The tracks on this channel are generated and meticulously produced using Hymnmania, a custom software automation tool and orchestration platform engineered by creators Bob & Lum to fuse faith, code, and electronic music. Visuals are created using the art skills of our creators and multiple digital media tools to achieve the correct blend of the psychedelic experience.

📅 New Music Videos Uploaded Every Week.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
📧 Business Inquiries:
Contact: ResurrectingBeats@gmail.com

🔗 Follow Our Playlists & Socials:
Facebook: https://www.facebook.com/profile.php?id=61588784931149&sk=directory_links
Instagram: https://www.instagram.com/resurrectingbeats?igsh=MWRxbGM4NHppZ2c2bw== @ResurrectingBeats
TikTok: https://www.tiktok.com/@resurrecting.beat?_r=1&_t=ZP-98NBjRbePx0

🎵 Stream/Download {song_title}: Coming Soon

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
{build_hashtags(genre_name)}"""
    
    return desc

def update_all():
    updated = 0
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
            vid = item["id"]["videoId"]
            title = item["snippet"]["title"]
            old_desc = item["snippet"]["description"]
            
            # Skip if already has the new template
            if "HYMNMANIA" in old_desc.upper() and "RECORD LABEL" in old_desc.upper():
                continue
            
            new_desc = build_description(title)
            
            try:
                yt.videos().update(
                    part="snippet",
                    body={
                        "id": vid,
                        "snippet": {
                            "title": title,
                            "description": new_desc,
                            "categoryId": "10",
                        },
                    },
                ).execute()
                updated += 1
                print(f"[{updated}] Updated: {title[:70]}")
                time.sleep(0.3)
            except Exception as e:
                err = str(e)
                if "quota" in err.lower() or "403" in err:
                    print(f"QUOTA HIT after {updated} updates!")
                    return updated
                print(f"  SKIP: {err[:80]}")
                time.sleep(0.5)
        
        page_token = resp.get("nextPageToken")
        if not page_token or len(items) == 0:
            break
    
    return updated


if __name__ == "__main__":
    print("Updating all YouTube descriptions to official Hymnmania template...\n")
    total = update_all()
    print(f"\n{total} descriptions updated!")
