"""TikTok video converter + uploader for Resurrecting Beats.
Converts beat videos to 9:16 vertical (1080x1920) and uploads via TikTok web uploader.
"""
import subprocess, os, json, time, random, sys
from playwright.sync_api import sync_playwright

OUT_DIR = os.path.abspath("pipeline_output/shorts")

def convert_to_vertical(input_video, output_name=None):
    """Convert 16:9 beat video to 9:16 vertical with center crop + zoom."""
    os.makedirs(OUT_DIR, exist_ok=True)
    base = output_name or os.path.splitext(os.path.basename(input_video))[0]
    out = os.path.join(OUT_DIR, f"{base}_short.mp4")
    if os.path.exists(out): return out
    
    # Crop center 9:16 from 16:9, add slight zoom effect
    cmd = [
        "ffmpeg", "-y", "-loglevel", "error",
        "-i", input_video,
        "-vf", "crop=ih*9/16:ih,scale=1080:1920",
        "-c:v", "libx264", "-preset", "medium", "-crf", "23",
        "-c:a", "aac", "-b:a", "128k",
        "-t", "180",  # Max 3 min for TikTok
        out
    ]
    try:
        subprocess.run(cmd, check=True)
        if os.path.exists(out) and os.path.getsize(out) > 100000:
            return out
    except: pass
    return None

def build_tiktok_caption(track_title, subgenre, vibe, bpm, key_name):
    """Build TikTok SEO-optimized caption using the Resurrecting Beats template."""
    title_upper = track_title.upper()
    
    caption = f"""🌀 RESURRECTING BEATS: '{track_title}' [{subgenre}] ⚡

Resurrected from the vault! {vibe} energy at {bpm} BPM in {key_name}. Built for festivals, vocalists, and live sets.

🎧 Free Download / License link in bio!
💬 Comment '{title_upper}' for the untagged high-quality link.

#ResurrectingBeats #EDM #Psytrance #SpiritualEDM #ElectronicMusic #Dance #DanceSafe #HymnMania

#producertok #edmmusic #trancefamily #festivalbeats #unreleasedmusic #{subgenre.replace(' ', '')} #{title_upper}"""
    
    return caption[:2200]  # TikTok max

def upload_to_tiktok(video_path, caption):
    """Upload video to TikTok via CDP browser web uploader."""
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        tt = b.contexts[0].new_page()
        tt.goto("https://www.tiktok.com/upload")
        tt.wait_for_timeout(5000)
        
        # Check logged in
        is_logged = tt.evaluate('!!document.querySelector("input[type=file]") || document.body.innerText.includes("Upload")')
        if not is_logged:
            print("TikTok not logged in! Please log in first.")
            b.close()
            return False
        
        # Upload video via file input
        abs_path = os.path.abspath(video_path).replace("\\", "/")
        file_input = tt.query_selector('input[type=file]')
        if file_input:
            file_input.set_input_files(abs_path)
        else:
            # Try iframe
            tt.evaluate('''(function(){
                var iframe = document.querySelector('iframe');
                if(iframe) {
                    var doc = iframe.contentDocument || iframe.contentWindow.document;
                    var input = doc.querySelector('input[type=file]');
                    if(input) input.click();
                }
            })()''')
            # Use file chooser
            with tt.expect_file_chooser(timeout=15000) as fc:
                tt.evaluate('document.querySelector("input[type=file]")?.click()')
            fc.value.set_files(abs_path)
        
        # Wait for upload processing
        print("Uploading video...")
        tt.wait_for_timeout(30000)
        
        # Type caption
        tt.evaluate(f'''(function(){{
            var ta = document.querySelector('[contenteditable=true], textarea, [role=textbox], .public-DraftEditor-content');
            if(ta){{ta.focus();document.execCommand('insertText',false,{json.dumps(caption)});}}
        }})()''')
        tt.wait_for_timeout(3000)
        
        # Click Post
        tt.evaluate('''(function(){
            var btns = document.querySelectorAll('div[role=button],span,button');
            for(var b of btns){
                var t = (b.innerText||'').trim().toLowerCase();
                if(t==='post' || t==='publish'){
                    b.click(); return;
                }
            }
        })()''')
        tt.wait_for_timeout(8000)
        print(f"Posted to TikTok!")
        b.close()
        return True

def post_beat_to_tiktok(beat_video_path, track_title, subgenre, vibe="High-energy", bpm=140, key_name="F Major"):
    """Full pipeline: convert 16:9 video to vertical, then upload to TikTok."""
    vertical = convert_to_vertical(beat_video_path)
    if not vertical:
        print("Conversion failed")
        return False
    
    caption = build_tiktok_caption(track_title, subgenre, vibe, bpm, key_name)
    print(f"Caption: {caption[:100]}...")
    
    return upload_to_tiktok(vertical, caption)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python tiktok_poster.py <video.mp4> <TrackTitle> [Subgenre] [BPM] [Key]")
        sys.exit(1)
    
    video = sys.argv[1]
    title = sys.argv[2]
    subgenre = sys.argv[3] if len(sys.argv) > 3 else "Psytrance"
    bpm = int(sys.argv[4]) if len(sys.argv) > 4 else 140
    key = sys.argv[5] if len(sys.argv) > 5 else "F Major"
    
    post_beat_to_tiktok(video, title, subgenre, "High-energy", bpm, key)
