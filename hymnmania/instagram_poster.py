"""Instagram Poster — posts Magnific clips / beat videos as Reels with SEO captions.

Flow (Instagram desktop web):
  1. instagram.com → Create ("New post") → "Post"
  2. Upload 9:16 vertical video (Magnific clip converted)
  3. Next (crop) → Next (filter) → caption → Share

SEO: caption has keywords + hashtags, bio has YouTube link.
Funnel: caption CTA "Full 4K on YouTube — link in bio".
"""
import subprocess, os, json, time, random
from playwright.sync_api import sync_playwright

ROOT = os.path.dirname(os.path.abspath(__file__))
MAG_DIR = os.path.join(ROOT, "pipeline_output", "magnific_videos")
IG_DIR = os.path.join(ROOT, "pipeline_output", "instagram")
os.makedirs(IG_DIR, exist_ok=True)

def convert_to_reel(input_path, output_name):
    """Convert a Magnific clip (16:9) to 9:16 vertical Reel."""
    base = output_name or os.path.splitext(os.path.basename(input_path))[0]
    out = os.path.join(IG_DIR, f"{base}_reel.mp4")
    if os.path.exists(out):
        return out
    cmd = [
        "ffmpeg", "-y", "-loglevel", "error", "-i", input_path,
        "-vf", "crop=ih*9/16:ih,scale=1080:1920",
        "-c:v", "libx264", "-preset", "fast", "-crf", "26",
        "-c:a", "aac", "-b:a", "128k", out
    ]
    try:
        subprocess.run(cmd, check=True, capture_output=True)
        if os.path.exists(out) and os.path.getsize(out) > 50000:
            return out
    except: pass
    return None

def build_instagram_caption(track_title, genre, yt_link="", bpm=140):
    """SEO caption with sound description + like/subscribe CTA + YouTube funnel + <=15 hashtags."""
    import random
    ctas = [
        "👍 Like this if it moves you! SUBSCRIBE for more electronic worship — full 4K journey on YouTube (link in bio).",
        "👊 Like + Subscribe for daily spiritual EDM! Watch the full journey on YouTube — link in bio.",
        "🙏 Like if your soul needed this. Subscribe to Resurrecting Beats on YouTube for more — link in bio!",
        "✨ Like, share, and subscribe! The full 4K visual journey is on YouTube — link in bio.",
    ]
    cta = random.choice(ctas)
    
    genre_tag = genre.replace(' ', '')
    hashtags = ["#ResurrectingBeats", "#Hymnmania", "#SpiritualEDM", "#Psytrance", "#EDM", "#ElectronicMusic"]
    if genre_tag not in ["Psytrance"]:
        hashtags.append(f"#{genre_tag}")
    hashtags += ["#PsychedelicTrance", "#PsytranceFamily", "#MusicVideo", "#ElectronicWorship", "#EDMMusic", "#DanceMusic", "#TrippyVisuals"]
    hashtag_str = " ".join(hashtags[:15])
    
    caption = (
        f"🌀 RESURRECTING BEATS: '{track_title}' [{genre}]\n\n"
        f"🎵 Sound: {genre} electronic worship at {bpm} BPM — driving bass, hypnotic arpeggios, "
        f"and psychedelic textures synced to a spiritual EDM journey.\n\n"
        f"{cta}\n\n"
        f"{hashtag_str}"
    )
    return caption

def create_beat_reel(beat_path, output_name):
    """Convert a beat video (has audio + RESURRECTING BEATS intro) to 9:16 Reel, keeping audio."""
    base = output_name or os.path.splitext(os.path.basename(beat_path))[0]
    out = os.path.join(IG_DIR, f"{base}_beat_reel.mp4")
    if os.path.exists(out):
        return out
    cmd = [
        "ffmpeg", "-y", "-loglevel", "error", "-i", beat_path,
        "-vf", "crop=ih*9/16:ih,scale=1080:1920",
        "-c:v", "libx264", "-preset", "fast", "-crf", "26",
        "-c:a", "aac", "-b:a", "128k", "-t", "30", out
    ]
    try:
        subprocess.run(cmd, check=True, capture_output=True)
        if os.path.exists(out) and os.path.getsize(out) > 50000:
            return out
    except: pass
    return None

def post_beat_to_instagram(beat_path, track_title, genre, yt_link="", bpm=0):
    """Convert beat video (has audio + intro) to 9:16 and post with SEO caption."""
    base = os.path.splitext(os.path.basename(beat_path))[0]
    reel = create_beat_reel(beat_path, base)
    if not reel:
        print("  Convert failed")
        return False
    # Detect BPM if not provided
    if not bpm:
        try:
            import librosa
            import numpy as np
            y, sr = librosa.load(beat_path, sr=22050)
            tempo, _ = librosa.beat.beat_track(y=y, sr=sr)
            bpm = int(float(np.asarray(tempo).ravel()[0]))
        except:
            bpm = 140
    caption = build_instagram_caption(track_title, genre, yt_link, bpm)
    return post_to_instagram(reel, caption)

def post_to_instagram(video_path, caption):
    """Post a Reel using the correct Create → Post flow."""
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        p = b.contexts[0].new_page()
        p.goto("https://www.instagram.com/")
        p.wait_for_timeout(5000)
        
        # 1. Click "New post" (Create button)
        p.evaluate("""(function(){
            var els = document.querySelectorAll('svg[aria-label], a[href], div[role=button]');
            for(var e of els){
                if((e.getAttribute('aria-label')||'').toLowerCase() === 'new post'){
                    (e.closest('[role=button],a') || e.parentElement || e).click();
                    return;
                }
            }
        })()""")
        p.wait_for_timeout(3000)
        
        # 2. Click "Post" option
        p.evaluate("""(function(){
            var els = document.querySelectorAll('div[role=button], [role=menuitem], span, a');
            for(var e of els){
                if((e.innerText||e.textContent||'').trim() === 'Post' && e.offsetParent){
                    e.click(); return;
                }
            }
        })()""")
        p.wait_for_timeout(3000)
        
        # 3. Upload video via file input
        abs_path = os.path.abspath(video_path)
        file_input = p.query_selector("input[type=file]")
        if not file_input:
            # try file chooser
            try:
                with p.expect_file_chooser(timeout=15000) as fc:
                    p.evaluate("document.querySelector('input[type=file]')?.click()")
                fc.value.set_files(abs_path)
                file_uploaded = True
            except:
                file_uploaded = False
        else:
            try:
                file_input.set_input_files(abs_path)
                file_uploaded = True
            except:
                file_uploaded = False
        
        if not file_uploaded:
            print("  Instagram: upload failed")
            b.close()
            return False
        
        print("  Instagram: video uploaded, processing...")
        p.wait_for_timeout(15000)
        
        # 4. Click Next (crop) then Next (filter)
        for _ in range(2):
            p.evaluate("""(function(){
                var btns = document.querySelectorAll('div[role=button], button');
                for(var b of btns){
                    if((b.innerText||'').trim().toLowerCase() === 'next'){
                        b.click(); return;
                    }
                }
            })()""")
            p.wait_for_timeout(4000)
        
        # 5. Type caption
        p.evaluate(f"""(function(){{
            var editors = document.querySelectorAll('[contenteditable=true], textarea, [role=textbox]');
            for(var e of editors){{
                if(e.offsetParent && e.tagName !== 'BODY'){{
                    e.focus();
                    document.execCommand('insertText', false, {json.dumps(caption)});
                    break;
                }}
            }}
        }})()""")
        p.wait_for_timeout(3000)
        
        # 6. Click Share
        p.evaluate("""(function(){
            var btns = document.querySelectorAll('div[role=button], button');
            for(var b of btns){
                var t = (b.innerText||'').trim().toLowerCase();
                if(t === 'share'){
                    b.click(); return;
                }
            }
        })()""")
        p.wait_for_timeout(10000)
        print("  Instagram: Reel posted!")
        b.close()
        return True

def post_magnific_clip(clip_name, track_title, genre, yt_link=""):
    """Convert + post a Magnific clip as an Instagram Reel."""
    src = os.path.join(MAG_DIR, clip_name)
    if not os.path.exists(src):
        print(f"  Clip not found: {clip_name}")
        return False
    reel = convert_to_reel(src, clip_name.replace(".mp4", ""))
    if not reel:
        print("  Convert failed")
        return False
    caption = build_instagram_caption(track_title, genre, yt_link)
    return post_to_instagram(reel, caption)

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python instagram_poster.py <clip.mp4> <TrackTitle> [Genre] [YT Link]")
        sys.exit(1)
    clip = sys.argv[1]
    title = sys.argv[2] if len(sys.argv) > 2 else "Psychedelic Visual"
    genre = sys.argv[3] if len(sys.argv) > 3 else "Psytrance"
    link = sys.argv[4] if len(sys.argv) > 4 else ""
    post_magnific_clip(clip, title, genre, link)
