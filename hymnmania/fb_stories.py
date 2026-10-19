"""Facebook Stories & Reels poster for Resurrecting Beats.
Creates compressed 9:16 vertical clips and uploads to Facebook Stories and Reels.
"""
import subprocess, os, json, time, random
from playwright.sync_api import sync_playwright

OUT_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "pipeline_output", "stories")
os.makedirs(OUT_DIR, exist_ok=True)

def create_story_clip(beat_video_path, duration=20, start_offset=5, track_title="", genre=""):
    """Extract a compressed 9:16 clip with text overlay."""
    base = os.path.splitext(os.path.basename(beat_video_path))[0]
    tag = f"{track_title}_{genre}" if track_title else base
    out = os.path.join(OUT_DIR, f"{tag[:60]}_story.mp4")
    if os.path.exists(out): return out
    
    # Build text overlay filter
    vf_parts = ["crop=ih*9/16:ih,scale=720:1280"]
    
    if track_title:
        # Use ffmpeg drawtext with fontfile to avoid crashes
        vf_parts.append(
            "drawtext=text='" + track_title.replace("'","") + "':fontcolor=white:fontsize=32:"
            "x=(w-text_w)/2:y=h-text_h-80:borderw=3:bordercolor=black@0.6:fontfile=/Windows/Fonts/impact.ttf"
        )
        vf_parts.append(
            "drawtext=text='resurrectingbeats':fontcolor=magenta:fontsize=20:"
            "x=(w-text_w)/2:y=h-text_h-45:borderw=2:bordercolor=black@0.5:fontfile=/Windows/Fonts/tahoma.ttf"
        )
        if genre:
            vf_parts.append(
                "drawtext=text='" + genre.replace("'","") + " Electronic Worship':fontcolor=white@0.8:fontsize=16:"
                "x=(w-text_w)/2:y=h-text_h-20:borderw=1:bordercolor=black@0.4:fontfile=/Windows/Fonts/tahoma.ttf"
            )
    
    vf = ",".join(vf_parts)
    
    cmd = [
        "ffmpeg", "-y", "-loglevel", "error",
        "-ss", str(start_offset), "-i", beat_video_path, "-t", str(duration),
        "-vf", vf,
        "-c:v", "libx264", "-preset", "fast", "-crf", "30",
        "-c:a", "aac", "-b:a", "64k", out
    ]
    try:
        subprocess.run(cmd, check=True)
        if os.path.exists(out) and os.path.getsize(out) > 10000:
            return out
    except: pass
    return None

def post_to_facebook_story(video_path, headline="", youtube_link=""):
    """Upload a video to Facebook Stories with headline and YT link."""
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        fb = b.contexts[0].new_page()
        fb.goto("https://www.facebook.com/stories/create")
        fb.wait_for_timeout(6000)
        
        # Click "Create a photo or video story"
        fb.evaluate("""(function(){
            var els = document.querySelectorAll('div[role=button],span');
            for(var e of els){
                if((e.innerText||'').toLowerCase().includes('photo') || (e.innerText||'').toLowerCase().includes('video')){
                    e.click(); return;
                }
            }
        })()""")
        fb.wait_for_timeout(4000)
        
        # Upload video
        abs_path = os.path.abspath(video_path)
        try:
            file_input = fb.query_selector("input[type=file]")
            if file_input:
                file_input.set_input_files(abs_path)
            else:
                with fb.expect_file_chooser(timeout=15000) as fc:
                    fb.evaluate("document.querySelector('input[type=file]')?.click()")
                fc.value.set_files(abs_path)
        except Exception as e:
            print(f"  Story upload error: {str(e)[:50]}")
            b.close()
            return False
        
        fb.wait_for_timeout(12000)
        
        # If headline provided, try to add text overlay
        if headline:
            try:
                fb.evaluate(f"""(function(){{
                    var els = document.querySelectorAll('[contenteditable=true], textarea, [role=textbox]');
                    for(var e of els){{
                        if(e.offsetParent){{
                            e.focus();
                            document.execCommand('insertText', false, {json.dumps(headline)});
                            break;
                        }}
                    }}
                }})()""")
            except: pass
        
        # Click Share to Story
        fb.evaluate("""(function(){
            var btns = document.querySelectorAll('div[role=button],span,button');
            for(var b of btns){
                var t = (b.innerText||'').trim().toLowerCase();
                if(t==='share to story' || t==='share now' || t==='share'){
                    b.click(); return;
                }
            }
        })()""")
        fb.wait_for_timeout(8000)
        print(f"  Story posted: {headline[:50]}...")
        b.close()
        return True

def post_beat_to_story(beat_path, track_title, genre, yt_link):
    """Full story pipeline: clip + upload."""
    clip = create_story_clip(beat_path, track_title=track_title, genre=genre)
    if not clip:
        print("  Clip creation failed")
        return False
    
    headline = f"{track_title} - {genre} / Electronic Worship - Full 4K on YouTube: {yt_link}"
    return post_to_facebook_story(clip, headline, yt_link)

def post_to_facebook_reel(video_path, track_title, genre, yt_link, headline=""):
    """Upload a video to Facebook Reels with short inquisitive CTA + YouTube link."""
    import random
    # <=15 hashtags
    hashtags = f"#ResurrectingBeats #Hymnmania #SpiritualEDM #Psytrance #EDM #ElectronicMusic #{genre.replace(' ', '')} #PsychedelicTrance"
    
    # Short inquisitive CTA (rotated for originality)
    ctas = [
        f"Can this {genre} frequency elevate your spirit? 👇 Drop a like and tell us below!",
        f"Which hymn should we resurrect next? 👇 Comment your pick!",
        f"Does electronic worship hit different for you too? 👇 Like + share if it does!",
        f"Feel that beat sync with your soul? 👇 Let us know in the comments!",
        f"Would you dance to this in a cathedral of light? 👇 Tell us what you think!",
    ]
    cta = random.choice(ctas)
    
    if not headline:
        headline = f"{track_title} — {genre} electronic worship"
    
    link_line = f"\n\n▶️ Full 4K journey: {yt_link}" if yt_link else ""
    
    caption = f"""{headline}

{cta}{link_line}

{hashtags}"""
    
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        fb = b.contexts[0].new_page()
        
        # Direct Reels create flow (works now)
        fb.goto("https://www.facebook.com/reels/create")
        fb.wait_for_timeout(8000)
        
        # Upload video
        abs_path = os.path.abspath(video_path)
        try:
            file_input = fb.query_selector("input[type=file]")
            if file_input:
                file_input.set_input_files(abs_path)
            else:
                with fb.expect_file_chooser(timeout=15000) as fc:
                    fb.evaluate("document.querySelector('input[type=file]')?.click()")
                fc.value.set_files(abs_path)
        except Exception as e:
            print(f"  Reel upload error: {str(e)[:50]}")
            b.close()
            return False
        
        fb.wait_for_timeout(20000)  # wait for copyright check
        
        # Click Next (after copyright check completes)
        for _ in range(3):
            fb.evaluate("""(function(){
                var btns = document.querySelectorAll('div[role=button], button');
                for(var b of btns){
                    var t = (b.innerText||b.textContent||'').trim().toLowerCase();
                    if(t === 'next' && b.offsetParent){ b.click(); return; }
                }
            })()""")
            fb.wait_for_timeout(5000)
        
        # Type caption (keyboard.type for the React caption field)
        try:
            fb.evaluate("""(function(){
                var e = Array.from(document.querySelectorAll('textarea, [contenteditable=true], [role=textbox], [aria-label*=Describe], [aria-label*=caption]'))
                    .find(x => x.offsetParent);
                if(e){ e.focus(); e.click(); }
            })()""")
            fb.wait_for_timeout(1500)
            fb.keyboard.type(caption, delay=10)
            fb.wait_for_timeout(3000)
        except: pass
        
        # Scroll down to reveal the Post button (it's below the fold)
        fb.mouse.wheel(0, 3000)
        fb.wait_for_timeout(3000)
        
        # Click the SECOND Post button by exact coordinates (scroll into view + mouse click)
        posted = fb.evaluate("""(function(){
            var btns = Array.from(document.querySelectorAll('div[role=button], button')).filter(e => e.offsetParent && (e.innerText||e.textContent||'').trim() === 'Post');
            if(btns.length >= 2){ btns[1].scrollIntoView({block:'center'}); return 'found '+btns.length; }
            if(btns.length === 1){ btns[0].scrollIntoView({block:'center'}); return 'found 1'; }
            return 'none';
        })()""")
        fb.wait_for_timeout(2000)
        
        # Get the Post button coordinates and click it
        rect = fb.evaluate("""(function(){
            var btns = Array.from(document.querySelectorAll('div[role=button], button')).filter(e => e.offsetParent && (e.innerText||e.textContent||'').trim() === 'Post');
            var target = btns[btns.length-1];
            target.scrollIntoView({block:'center'});
            var r = target.getBoundingClientRect();
            return JSON.stringify({x: r.x + r.width/2, y: r.y + r.height/2});
        })()""")
        import json as _json
        coords = _json.loads(rect)
        fb.wait_for_timeout(1000)
        fb.mouse.click(coords['x'], coords['y'])
        fb.wait_for_timeout(10000)
        print(f"  Reel posted: {headline[:50]}...")
        b.close()
        return True

def post_beat_to_reel(beat_path, track_title, genre, yt_link):
    """Full reel pipeline: clip + upload with hashtags."""
    clip = create_story_clip(beat_path, track_title=track_title, genre=genre)
    if not clip:
        print("  Clip creation failed")
        return False
    
    return post_to_facebook_reel(clip, track_title, genre, yt_link)

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python fb_stories.py <beat_video.mp4> [Track Title] [Genre] [YT Link]")
        sys.exit(1)
    
    video = sys.argv[1]
    title = sys.argv[2] if len(sys.argv) > 2 else "Hymn Remix"
    genre = sys.argv[3] if len(sys.argv) > 3 else "Electronic Worship"
    link = sys.argv[4] if len(sys.argv) > 4 else ""
    
    post_beat_to_story(video, title, genre, link)
