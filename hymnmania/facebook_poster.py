"""FACEBOOK AUTO-POSTER — Posts to Resurrecting Beats page via CDP browser.
Uses the exact brand template provided. Tracks posted videos to avoid duplicates.

Template structure per post:
  [Hook: 1-2 lines with emojis]
  [Track Info: title, vibe, link]
  [Visual Experience: 2 sentences]
  [Tech & Mission: Hymnmania, science]
  [CTA: YouTube link]
  [Hashtags: 7-10 from pillars]

Artist: RESURRECTING BEATS/HYMNMANIA on every post
"""
import os, sys, json, time, random
from playwright.sync_api import sync_playwright

ROOT = os.path.dirname(os.path.abspath(__file__))
POSTED_LOG = os.path.join(ROOT, ".facebook_posted.json")

GENRE_VISUALS = {
    "psytrance": "hyper-dimensional sacred geometry, neon fractal spirals, and morphing alien temple landscapes",
    "deep house": "warm sunset gradients, smooth ocean waves, and golden-hour light dancing through atmospheric spaces",
    "drum and bass": "rain-soaked neon streets, liquid motion graphics, and breakbeat energy pulsing through a dark cyberpunk cityscape",
    "dubstep": "mechanical bass-drop shockwaves, glitch-art distortions, and wobble visualizations tearing through a digital wasteland",
    "gabba": "industrial warehouse strobes, pounding distortion fields, and aggressive hardcore energy blasting through darkness",
    "chiptune": "retro 8-bit pixel worlds, glitching digital arcade landscapes, and neon explosions of vintage gaming nostalgia",
    "synthwave": "neon grid lines stretching to infinity beneath a chrome sunset, retro-futuristic aesthetics in perfect motion",
    "hardstyle": "massive festival lasers, pyrotechnic eruptions, and euphoric mainstage energy lifting spirits sky-high",
    "detroit techno": "stark industrial cathedral of shadow and light, rhythmic precision meeting warehouse soul",
    "detroit house": "deep warm textures, smooth urban landscapes, and jackin grooves flowing through the Motor City underground",
}

GENRE_EMOJIS = {
    "psytrance": "🌀👽🌀", "deep house": "🌊🏠🎹", "drum and bass": "💥⚡🔊",
    "dubstep": "🤖🔊💀", "gabba": "⛓️💀🔥", "chiptune": "👾🎮✨",
    "synthwave": "🌆🚗💜", "hardstyle": "🎆🔥🙌", "detroit techno": "🏭🎛️🌃",
    "detroit house": "🏙️🎹💫",
}

HASHTAGS = [
    "#ResurrectingBeats", "#Hymnmania", "#ChristianPsytrance", "#Psytrance",
    "#WorshipMusic", "#MusicTherapy", "#PsychedelicArt", "#TrippyVisuals",
    "#ElectronicWorship", "#ModernHymns", "#AI", "#AIMusic",
]

HOOKS = [
    "Prepare to elevate your spirit and your mind! 🚀",
    "When a classic hymn meets the future of electronic music... ⚡",
    "The spirit of the old made new again through sacred frequencies. 🎵",
    "Hymns you grew up with, reimagined for the next dimension. 🌌",
    "Ancient words, futuristic sound. This one hits different. 🔥",
    "Your favorite hymn just got a massive electronic upgrade. 💫",
]


def load_posted():
    """Load set of already-posted video IDs."""
    if os.path.exists(POSTED_LOG):
        with open(POSTED_LOG) as f:
            return set(json.load(f))
    return set()


def save_posted(posted):
    """Save posted video IDs."""
    with open(POSTED_LOG, "w") as f:
        json.dump(list(posted), f)


def get_unposted_videos():
    """Get list of beat videos not yet posted to Facebook."""
    posted = load_posted()
    vdir = os.path.join(ROOT, "pipeline_output", "beat_videos")
    if not os.path.exists(vdir):
        return []
    videos = [f for f in os.listdir(vdir) if f.endswith(".mp4") and os.path.getsize(os.path.join(vdir, f)) > 5000000]
    unposted = [v for v in videos if v not in posted]
    random.shuffle(unposted)
    return unposted


def parse_video_info(filename):
    """Extract hymn, genre, speed, variant from filename."""
    name = filename.replace("_beatsynced.mp4", "")
    parts = name.split("_")
    hymn = parts[0] if parts else "Unknown"
    # Find genre
    genre = "psytrance"
    for g in GENRE_VISUALS:
        if g in name.lower():
            genre = g
            break
    # Speed
    speed = ""
    for s in ["05x", "10x", "15x", "20x", "30x"]:
        if s in name:
            speed_map = {"05x": "Half-Speed", "10x": "1.0x", "15x": "1.5x", "20x": "Double", "30x": "Triple"}
            speed = speed_map.get(s, "")
            break
    return hymn, genre, speed


AUTHORS = {
    "thy": ("Amy Grant & Michael W. Smith", "1984"),
    "emmanuel": ("Latin, 12th Century", "1710"),
    "praise": ("Fanny J. Crosby", "1869"),
    "oh_for": ("Charles Wesley", "1739"),
    "he_leadeth": ("Joseph H. Gilmore", "1862"),
    "winchester": ("Thomas Olivers", "1770"),
}


def build_post_text(filename):
    """Build the full post text using the brand template."""
    hymn, genre, speed = parse_video_info(filename)
    visual = GENRE_VISUALS.get(genre, "transcendent AI-generated psychedelic imagery")
    emoji = GENRE_EMOJIS.get(genre, "🎵")
    hook = random.choice(HOOKS)

    # Find author
    author, year = "", ""
    for key, (a, y) in AUTHORS.items():
        if key in hymn.lower():
            author, year = a, y
            break
    
    credit = f" ({author}, {year})" if author else ""
    speed_str = f" | {speed}" if speed else ""

    # Random hashtags
    tags = random.sample(HASHTAGS, min(9, len(HASHTAGS)))

    post = f"""{hook}

🎵 ARTIST: RESURRECTING BEATS/HYMNMANIA
🎵 Track: {hymn}{credit} — {genre.title()} Remix{speed_str}
🎹 Vibe: {genre.title()} Electronic Worship
📺 Watch the full visual journey on YouTube! Link in bio

{emoji} Lose yourself in {visual}. Our visuals are crafted by our creators using multiple digital media tools to deliver the perfect blend of the psychedelic experience.

Every track is meticulously produced using Hymnmania, a custom software automation tool engineered by Bob & Lum to fuse faith, code, and electronic music. We believe psytrance is more than music—its fast, repetitive tempos stimulate the brain's reward pathways, release dopamine, and act as a powerful tool for stress relief and deep meditation. 🙏🧠

Head over to Resurrecting Beats on YouTube to stream it now and subscribe! Let us know how this frequency makes you feel. 👇

{' '.join(tags)}"""
    return post


def post_to_facebook(page, video_path, post_text):
    """Post a video to the Resurrecting Beats Facebook page via CDP browser."""
    print(f"  Posting: {os.path.basename(video_path)}...")
    
    # Navigate to page
    page.goto("https://www.facebook.com/ResurrectingBeats")
    page.wait_for_timeout(5000)
    
    # Check login
    has_composer = page.evaluate('!!document.querySelector("[role=textbox]")')
    if not has_composer:
        print("  Not logged in! Open Facebook in Edge and log in first.")
        return False
    
    # Click the composer
    page.evaluate('''
        (function(){
            var textbox = document.querySelector('[role=textbox]');
            if(textbox) { textbox.click(); return; }
            // Alternative: click what's on your mind
            var spans = document.querySelectorAll('span');
            for(var s of spans) {
                if((s.innerText||'').includes("What's on your mind") || (s.innerText||'').includes("Create post")) {
                    s.click(); return;
                }
            }
        })()
    ''')
    page.wait_for_timeout(3000)
    
    # Type the post text into the composer
    page.evaluate(f'''
        (function(){{
            var textbox = document.querySelector('[role=textbox], div[contenteditable=true]');
            if(!textbox) return 'no composer';
            textbox.focus();
            var text = {json.dumps(post_text)};
            document.execCommand('insertText', false, text);
            return 'typed';
        }})()
    ''')
    page.wait_for_timeout(2000)
    
    # Attach video
    abs_path = os.path.abspath(video_path)
    with page.expect_file_chooser(timeout=10000) as fc:
        page.evaluate('''
            (function(){
                var btns = document.querySelectorAll('div[role=button], span');
                for(var b of btns) {
                    if((b.innerText||'').includes('Photo/video') || (b.getAttribute('aria-label')||'').includes('Photo')) {
                        b.click(); return;
                    }
                }
            })()
        ''')
    fc.value.set_files(abs_path)
    page.wait_for_timeout(10000)  # Wait for video upload
    
    # Click Post
    page.evaluate('''
        (function(){
            var btns = document.querySelectorAll('div[role=button], span, button');
            for(var b of btns) {
                if((b.innerText||'').trim() === 'Post' && b.offsetParent) {
                    b.click(); return;
                }
            }
        })()
    ''')
    page.wait_for_timeout(5000)
    
    print(f"  Posted!")
    return True


def run(limit=3):
    """Post N unposted videos to Facebook."""
    videos = get_unposted_videos()
    if not videos:
        print("No unposted videos found!")
        return
    
    posted = load_posted()
    print(f"Found {len(videos)} unposted videos. Posting {min(limit, len(videos))}...\n")
    
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        fb = None
        for p in b.contexts[0].pages:
            if "facebook.com" in p.url and "login" not in p.url.lower():
                fb = p
                break
        if not fb:
            fb = b.contexts[0].new_page()
        
        count = 0
        for video in videos[:limit]:
            video_path = os.path.join(ROOT, "pipeline_output", "beat_videos", video)
            post_text = build_post_text(video)
            
            success = post_to_facebook(fb, video_path, post_text)
            if success:
                posted.add(video)
                save_posted(posted)
                count += 1
            
            time.sleep(3)
        
        b.close()
    
    print(f"\nPosted {count} videos to Facebook!")
    print(f"Total posted: {len(posted)}")


if __name__ == "__main__":
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 3
    run(n)
