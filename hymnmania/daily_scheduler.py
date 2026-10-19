"""DAILY SOCIAL MEDIA SCHEDULER - Resurrecting Beats
Posts to Facebook using HYMNMANIA_SOCIAL_POST_TEMPLATE.
"""
import os, sys, json, time, random
from playwright.sync_api import sync_playwright

ROOT = os.path.dirname(os.path.abspath(__file__))
POSTED_LOG = os.path.join(ROOT, ".social_posted.json")

FIXED_HASHTAGS = """
#ResurrectingBeats #Hymnmania #SpiritualEDM #Psytrance #ElectronicMusic #WorshipMusic #MusicTherapy #MentalHealthAwareness"""

# Varied phrasings of the Bob & Lum / Hymnmania origin story (rotated per post for originality)
MISSION_VARIATIONS = [
    "Every track is meticulously produced using Hymnmania, a custom software automation tool engineered by Bob & Lum to fuse faith, code, and electronic music.",
    "Born from a vision to honor God through futuristic sound, Bob & Lum built Hymnmania to resurrect the hymns we grew up with as electronic worship.",
    "Hymnmania is Bob & Lum's labor of love — a custom orchestration platform where code meets faith to transform timeless hymns into modern electronic worship.",
    "Engineered by Bob & Lum, Hymnmania fuses faith, code, and electronic music into a powerful tool for spiritual elevation and creative expression.",
    "We're Bob & Lum — two creators who built Hymnmania to take every hymn we love and reimagine it through futuristic electronic soundscapes.",
    "To honor God with every hymn — that's why Bob & Lum created Hymnmania, a custom automation platform fusing faith, code, and music.",
    "A creative fusion of faith and technology: Hymnmania, engineered by Bob & Lum, transforms the hymns of yesterday into the electronic worship of tomorrow.",
    "Hymnmania is more than software — it's Bob & Lum's mission to fuse faith, code, and electronic music, honoring God through every reimagined hymn.",
]

HOOKS = {
    "Psytrance": "Prepare your mind and spirit for a high-frequency journey through sacred geometry and neon cathedrals!",
    "Deep House": "Smooth, soulful, and deeply spiritual — warm golden-hour energy meets classic worship.",
    "Dubstep": "When sacred melody meets earth-shattering bass drops — pure electronic worship energy.",
    "Drum and Bass": "High-energy breakbeats meet timeless hymns — relentless spiritual energy through cyberpunk cathedrals.",
    "Chiptune": "Retro 8-bit worship just dropped — arcade nostalgia meets sacred melody in pixel-perfect praise.",
    "Gabba": "Industrial hardcore meets divine frequency — pure adrenaline for the spirit at 200+ BPM.",
    "Detroit Techno": "Stark industrial beauty meets rhythmic precision — Detroit Techno reimagines this hymn for the underground.",
    "Detroit House": "Deep Motor City grooves meet sacred melody — Detroit House worship for the dance floor.",
    "Hardstyle Trance": "Euphoric hardstyle kicks and soaring melodies transform this hymn into pure energy.",
    "Synthwave": "Neon-drenched retro-future worship reimagined through vintage synths and pulsing basslines.",
    "Japanese Hardcore Techno": "Intense Japanese hardcore energy meets divine frequency — hands up for electronic worship.",
}

VISUALS = {
    "Psytrance": "A hyper-dimensional visual journey blending sacred geometry with neon aesthetics, matching the high-energy frequency of this classic hymn.",
    "Deep House": "Warm, atmospheric visuals flow like golden-hour light through cathedral architecture, matching the smooth, soulful energy.",
    "Dubstep": "Seismic bass visualizations ripple through futuristic cathedral spaces as strobes and particle systems erupt with each drop.",
    "Drum and Bass": "Rain-soaked neon streets and cyberpunk cityscapes pulse in sync with the relentless breakbeats.",
    "Chiptune": "Pixel-perfect 8-bit cathedrals and glitching digital stained glass create a retro worship arcade experience.",
    "Gabba": "Industrial warehouse visuals with raw strobe effects and pounding kick-drum visualizations match the intensity of this hardcore worship track.",
    "Detroit Techno": "Stark warehouse shadows and light — a monochromatic journey through the birthplace of techno, reimagined for spiritual elevation.",
    "Detroit House": "Warm Motor City textures flow through cathedral architecture, blending soulful house grooves with sacred geometry.",
    "Hardstyle Trance": "Euphoric laser shows and soaring light columns match the euphoric kicks and melodies.",
    "Synthwave": "Neon-drenched retro grids stretch into infinite digital horizons as this synthwave reimagining unfolds.",
    "Japanese Hardcore Techno": "Intense Japanese rave visuals with high-speed laser shows and pounding kick-drum energy.",
}

# Video IDs from the channel (format: vid_id: (hymn_name, genre))
VIDEOS = {
    # Hymns
    "JuEpMDgsYsM": ("Thy Word", "Detroit House"),
    "R5-IHTHqSS4": ("Thy Word", "Detroit House"),
    "G9mjkVzUKNs": ("Thy Word", "Deep House"),
    "qlqnJ5ykO4s": ("Thy Word", "Deep House"),
    "dPTIkkFO-EY": ("Thy Word", "Chiptune"),
    "RNamkv63S2c": ("Thy Word", "Chiptune"),
    "FysS5lmxB38": ("Thy Word", "Deep House"),
    "k_jP6_Dj7_Q": ("Thy Word", "Deep House"),
    "JaYsDTrfpS4": ("Thy Word", "Dubstep"),
    "ux3kWy4OyKA": ("Thy Word", "Detroit House"),
    "GtWZgeEb_Fk": ("Thy Word", "Detroit House"),
    "TiAeHbyg9oM": ("Thy Word", "Deep House"),
    "OnRLNvDEf58": ("Thy Word", "Deep House"),
    "znvqbXydaZ4": ("Thy Word", "Chiptune"),
    "C3oPOmWuNbo": ("Thy Word", "Deep House"),
    # Emmanuel
    "4zutG2Npbcs": ("Emmanuel", "Psytrance"),
    "0AolS6uV15o": ("Emmanuel", "Drum and Bass"),
    "_gVaX8RMlEU": ("Emmanuel", "Deep House"),
    "wcFTlVrrK08": ("Emmanuel", "Psytrance"),
    "C_CYWTMaWJ8": ("Emmanuel", "Drum and Bass"),
    "xOhhM2JarfY": ("Emmanuel", "Dubstep"),
    # He Leadeth Me
    "mW_J7XKHcC4": ("He Leadeth Me", "Psytrance"),
    "H_sQan9nqC4": ("He Leadeth Me", "Deep House"),
    "RRu2pLydtDQ": ("He Leadeth Me", "Drum and Bass"),
    "uu3WCkzOsxM": ("He Leadeth Me", "Psytrance"),
    # Oh For A Thousand Tongues
    "8o3ENfNewAs": ("Oh For A Thousand Tongues", "Deep House"),
    "Zf93V2jhbDA": ("Oh For A Thousand Tongues", "Drum and Bass"),
    # Praise Him
    "lcpUL4Gs7lA": ("Praise Him", "Deep House"),
    "y5YoI_swwXc": ("Praise Him", "Psytrance"),
    "8bRkE2kNVuI": ("Praise Him", "Psytrance"),
    # Neon Valse
    "dKJpd7OeElo": ("Neon Valse", "Deep House"),
    "aOPoO1hSpwo": ("Neon Valse", "Deep House"),
    "VRuwzCuwCx8": ("Neon Valse", "Drum and Bass"),
    "0r9EIifbN-4": ("Neon Valse", "Drum and Bass"),
    "Qo2O7xuTbYs": ("Neon Valse", "Gabba"),
    "Kk3Ppc_wuaI": ("Neon Valse", "Gabba"),
    # Canon in D
    "akDePgNmJys": ("Canon in D", "Detroit Techno"),
    "mUZdiQA3o8Y": ("Canon in D", "Dubstep"),
    "dveEJE9S1Zg": ("Canon in D", "Deep House"),
    "kmciMpByYbo": ("Canon in D", "Detroit House"),
    "fdXePu7GBTk": ("Canon in D", "Drum and Bass"),
    "jJj9diBmwUw": ("Canon in D", "Hardstyle Trance"),
    "R0GNSwfcvak": ("Canon in D", "Synthwave"),
    # Toccata
    "sR1AqpmP6Pg": ("Toccata & Fugue", "Psytrance"),
    # Amazing Grace
    "hYvGNTnH1cc": ("Amazing Grace", "Psytrance"),
    # How Great Thou Art
    "a5MK6lE0eDQ": ("How Great Thou Art", "Psytrance"),
}

def load_posted():
    if os.path.exists(POSTED_LOG):
        with open(POSTED_LOG) as f: return set(json.load(f))
    return set()

def save_posted(posted):
    with open(POSTED_LOG, "w") as f: json.dump(list(posted), f)

def pick_videos(posted, count=3):
    available = [(vid, hymn, genre) for vid, (hymn, genre) in VIDEOS.items() if vid not in posted]
    if not available:
        posted.clear()
        available = [(vid, hymn, genre) for vid, (hymn, genre) in VIDEOS.items()]
    random.shuffle(available)
    selected = []
    last_hymn, last_genre = None, None
    for vid, hymn, genre in available:
        if len(selected) >= count: break
        if hymn != last_hymn and genre != last_genre:
            selected.append((vid, hymn, genre))
            last_hymn, last_genre = hymn, genre
    return selected

def build_post(vid, hymn, genre):
    import random
    hook = HOOKS.get(genre, f"New {hymn} electronic remix just dropped!")
    visual = VISUALS.get(genre, "Our visuals are crafted to deliver the ultimate psychedelic experience.")
    mission = random.choice(MISSION_VARIATIONS)
    
    body = f"""{hook} 🚀

🎵 Track: {hymn}
🎹 Vibe: {genre} / Electronic Worship

{visual} Our visuals are crafted by our creators using multiple digital media tools to deliver the ultimate psychedelic experience.

{mission} We believe psytrance is more than music — its fast, repetitive tempos stimulate the brain's reward pathways and induce a state of deep meditation and stress relief. 🙏🧠

Watch the full 4K visual journey on YouTube!"""
    return body, f"https://www.youtube.com/watch?v={vid}"

def post_to_facebook(page, post_text, yt_link):
    """Post with video preview: paste bare URL first, then replace with full text+link."""
    page.goto("https://www.facebook.com/")
    page.wait_for_timeout(5000)
    
    page.evaluate(
        """(function(){var a=document.querySelectorAll('div[role=button],span');for(var e of a){if((e.innerText||'').trim().includes("What")){e.click();return}}})()"""
    )
    page.wait_for_timeout(3000)
    
    # Step 1: Paste bare URL to trigger Facebook's link scraper
    page.evaluate(
        f"""(function(){{var t=document.querySelector('[role=dialog] [role=textbox], [role=dialog] div[contenteditable=true]');if(t){{t.focus();document.execCommand('insertText',false,{json.dumps(yt_link)});}}}})()"""
    )
    
    # Wait for preview
    for _ in range(10):
        time.sleep(2)
        if page.evaluate('!!document.querySelector("[role=dialog] img[src*=ytimg]")'): break
    
    # Step 2: Replace with full text + link (use keyboard Ctrl+A for reliable select-all)
    full = post_text + chr(10) + chr(10) + yt_link + chr(10) + chr(10) + FIXED_HASHTAGS
    
    # Try multiple selection methods to avoid the duplicate-URL bug
    page.keyboard.press("Control+a")
    page.wait_for_timeout(500)
    page.evaluate(
        f"""(function(){{var t=document.querySelector('[role=dialog] [role=textbox], [role=dialog] div[contenteditable=true]');if(t){{t.focus();document.execCommand('selectAll',false,null);document.execCommand('insertText',false,{json.dumps(full)});}}}})()"""
    )
    
    # Wait for preview to regenerate
    for _ in range(15):
        time.sleep(2)
        if page.evaluate('!!document.querySelector("[role=dialog] img[src*=ytimg]")'): break
    
    page.evaluate(
        """(function(){var a=document.querySelectorAll('[role=dialog] div[role=button], [role=dialog] span');for(var e of a){if((e.innerText||'').trim()==='Post'){e.click();return}}})()"""
    )
    page.wait_for_timeout(5000)
    return True

def run(count=3):
    posted = load_posted()
    selected = pick_videos(posted, count)
    if not selected:
        print("No videos to post!")
        return
    print(f"Posting {len(selected)} to Facebook...\n")
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        fb = b.contexts[0].new_page()
        for vid, hymn, genre in selected:
            post, yt_link = build_post(vid, hymn, genre)
            success = post_to_facebook(fb, post, yt_link)
            if success:
                posted.add(vid)
                save_posted(posted)
                print(f"  OK {hymn} - {genre}")
                print(f"     {yt_link}\n")
            time.sleep(3)
        b.close()
    print(f"Done! {len(posted)}/{len(VIDEOS)}")

if __name__ == "__main__":
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 3
    run(n)
