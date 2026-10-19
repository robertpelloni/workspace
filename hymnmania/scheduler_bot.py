"""Resurrecting Beats Weekly Scheduler Bot.
Posts to TikTok + Facebook on a set schedule using CDP browser automation.
No API tokens needed — uses the existing CDP session.

Schedule (EST):
  MON 3-5 PM → Track 1: HOOK_DROP (15s loop)
  TUE 2-6 PM → Track 1: VAULT_STORY (30s background)
  WED 1-6 PM → Track 2: HOOK_DROP (15s loop)
  THU 1-5 PM → Track 2: CONVERSION (30s YT promo)
  FRI 3-5 PM → Track 3: HOOK_DROP (15s loop)
  SAT/SUN    → Rest / Queue Reset
"""
import os, json, time, random, datetime, subprocess
from playwright.sync_api import sync_playwright

ROOT = os.path.dirname(os.path.abspath(__file__))
QUEUE_FILE = os.path.join(ROOT, ".post_queue.json")
POSTED_LOG = os.path.join(ROOT, ".tiktok_posted.json")

OUT_DIR = os.path.join(ROOT, "pipeline_output", "shorts")
os.makedirs(OUT_DIR, exist_ok=True)

# TikTok caption template
def build_tiktok_caption(track_title, subgenre, vibe, bpm, key_name):
    title_upper = track_title.upper()
    caption = f"""🌀 RESURRECTING BEATS: '{track_title}' [{subgenre}] ⚡

Resurrected from the vault! {vibe} energy at {bpm} BPM in {key_name}. Built for festivals, vocalists, and live sets.

🎧 Free Download / License link in bio!
💬 Comment '{title_upper}' for the untagged high-quality link.

#ResurrectingBeats #EDM #Psytrance #SpiritualEDM #ElectronicMusic #Dance #DanceSafe #HymnMania

#producertok #edmmusic #trancefamily #festivalbeats #unreleasedmusic #{subgenre.replace(' ', '')} #{title_upper}"""
    return caption[:2200]

def convert_to_vertical(input_video):
    """Convert 16:9 to 9:16 vertical (1080x1920)."""
    base = os.path.splitext(os.path.basename(input_video))[0]
    out = os.path.join(OUT_DIR, f"{base}_short.mp4")
    if os.path.exists(out): return out
    cmd = [
        "ffmpeg", "-y", "-loglevel", "error",
        "-i", input_video,
        "-vf", "crop=ih*9/16:ih,scale=1080:1920",
        "-c:v", "libx264", "-preset", "medium", "-crf", "23",
        "-c:a", "aac", "-b:a", "128k", "-t", "180", out
    ]
    try:
        subprocess.run(cmd, check=True)
        if os.path.exists(out) and os.path.getsize(out) > 100000: return out
    except: pass
    return None

def post_to_tiktok(video_path, caption):
    """Post to TikTok via CDP browser (tiktok.com/upload)."""
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        tt = b.contexts[0].new_page()
        tt.goto("https://www.tiktok.com/upload")
        tt.wait_for_timeout(8000)
        
        # Upload video
        abs_path = os.path.abspath(video_path).replace("\\", "/")
        try:
            file_input = tt.query_selector('input[type=file]')
            if file_input:
                file_input.set_input_files(abs_path)
            else:
                with tt.expect_file_chooser(timeout=15000) as fc:
                    tt.evaluate('document.querySelector("input[type=file]")?.click()')
                fc.value.set_files(abs_path)
        except:
            print("  TikTok upload failed — check if logged in")
            b.close()
            return False
        
        tt.wait_for_timeout(30000)  # Wait for upload processing
        
        # Type caption
        tt.evaluate(f'''(function(){{
            var editors = document.querySelectorAll('[contenteditable=true], textarea, [role=textbox], .public-DraftEditor-content, .notranslate');
            for(var ed of editors){{
                if(ed.offsetParent){{ed.focus();document.execCommand('insertText',false,{json.dumps(caption)});break;}}
            }}
        }})()''')
        tt.wait_for_timeout(3000)
        
        # Click Post
        tt.evaluate('''(function(){
            var btns = document.querySelectorAll('div[role=button],span,button');
            for(var b of btns){
                var t = (b.innerText||b.value||'').trim().toLowerCase();
                if(t==='post' || t==='publish'){b.click();return;}
            }
        })()''')
        tt.wait_for_timeout(8000)
        print(f"  Posted to TikTok!")
        b.close()
        return True

def post_to_facebook_from_scheduler(video_path, hymn, genre):
    """Reuse the daily_scheduler Facebook poster."""
    from daily_scheduler import build_post, post_to_facebook
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        fb = b.contexts[0].new_page()
        # Extract video ID from filename or use placeholder
        vid = f"FB_{os.path.basename(video_path)[:8]}"
        post, yt_link = build_post(vid, hymn, genre)
        success = post_to_facebook(fb, post, yt_link)
        b.close()
        return success

def get_next_from_queue():
    """Get next track from the queue file."""
    if os.path.exists(QUEUE_FILE):
        with open(QUEUE_FILE) as f:
            queue = json.load(f)
        if queue:
            track = queue.pop(0)
            with open(QUEUE_FILE, "w") as f:
                json.dump(queue, f)
            return track
    return None

def run_scheduled_post(content_type="HOOK_DROP"):
    """Execute a scheduled post for the given content type."""
    now = datetime.datetime.now()
    print(f"\n[{now.strftime('%Y-%m-%d %H:%M EST')}] Running {content_type} post...")
    
    track = get_next_from_queue()
    if not track:
        print("  Queue empty!")
        return
    
    # Find matching beat video
    vdir = os.path.join(ROOT, "pipeline_output", "beat_videos")
    beats = [f for f in os.listdir(vdir) if f.endswith(".mp4") and not f.startswith("_")]
    matching = [b for b in beats if track["title"].lower().replace(" ", "") in b.lower().replace(" ", "").replace("_", "")]
    
    if not matching:
        matching = beats[:1]  # Fallback: use any beat video
    
    video_path = os.path.join(vdir, random.choice(matching))
    
    # Convert to vertical for TikTok
    vertical = convert_to_vertical(video_path)
    
    # Build caption based on content type
    subgenre = track.get("subgenre", "Psytrance")
    vibe = track.get("vibe", "High-energy")
    bpm = track.get("bpm", 140)
    key = track.get("key", "F Major")
    title = track["title"]
    
    if content_type == "HOOK_DROP":
        caption = build_tiktok_caption(title, subgenre, vibe, bpm, key)
    elif content_type == "VAULT_STORY":
        caption = f"🎬 Behind the beat: '{title}' [{subgenre}] — resurrected from the Hymnmania vault!\n\n{title} — {bpm} BPM in {key}. {vibe} energy.\n\n#ResurrectingBeats #Hymnmania #SpiritualEDM #producertok"
    elif content_type == "CONVERSION":
        caption = build_tiktok_caption(title, subgenre, vibe, bpm, key) + "\n\n📺 Full 4K journey on YouTube @ResurrectingBeats"
    else:
        caption = build_tiktok_caption(title, subgenre, vibe, bpm, key)
    
    if vertical:
        post_to_tiktok(vertical, caption)
    
    # Also post to Facebook
    hymn = title
    post_to_facebook_from_scheduler(video_path, hymn, subgenre)
    
    print(f"  Done: {title} [{content_type}]")

# Schedule configuration
SCHEDULE = {
    "monday": [("15:00", "HOOK_DROP")],
    "tuesday": [("15:00", "VAULT_STORY")],
    "wednesday": [("15:00", "HOOK_DROP")],
    "thursday": [("15:00", "CONVERSION")],
    "friday": [("15:00", "HOOK_DROP")],
}

if __name__ == "__main__":
    import sys
    
    if len(sys.argv) > 1:
        # Manual run: python scheduler_bot.py HOOK_DROP
        content_type = sys.argv[1].upper()
        run_scheduled_post(content_type)
    else:
        # Scheduled mode: check current day/time
        now = datetime.datetime.now()
        day = now.strftime("%A").lower()
        
        if day in SCHEDULE:
            for time_str, content_type in SCHEDULE[day]:
                target_hour = int(time_str.split(":")[0])
                if now.hour == target_hour:
                    run_scheduled_post(content_type)
                    break
        else:
            print(f"No posts scheduled for {day.title()}")
