"""Instagram Poster — CO-LOCATED dedicated browser (fixes CDP file-upload blocker).
Launches its OWN local Edge (own profile) logged into IG, so file uploads work
(IG doesn't support remote-CDP file injection). Logs in via .secrets.json if needed.

Usage: python ig_poster_local.py <beat_video.mp4> <TrackTitle> <Genre> [YT Link]
"""
import subprocess, os, sys, json, time, random
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

ROOT = os.path.dirname(os.path.abspath(__file__))
IG_DIR = os.path.join(ROOT, "pipeline_output", "instagram")
os.makedirs(IG_DIR, exist_ok=True)

EDGE_PATH = r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe"
IG_PROFILE = r"C:\Users\jakeg\ig-local-profile"  # dedicated profile for IG local posts
PORT = 9333

def load_creds():
    d = json.load(open(os.path.join(ROOT, ".secrets.json")))
    return d.get("INSTAGRAM_EMAIL") or d.get("INSTAGRAM_USERNAME"), d.get("INSTAGRAM_PASSWORD")

def build_instagram_caption(track_title, genre, yt_link="", bpm=140):
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
    return (
        f"🌀 RESURRECTING BEATS: '{track_title}' [{genre}]\n\n"
        f"🎵 Sound: {genre} electronic worship at {bpm} BPM — driving bass, hypnotic arpeggios, "
        f"and psychedelic textures synced to a spiritual EDM journey.\n\n"
        f"{cta}\n\n"
        f"{hashtag_str}"
    )

def create_beat_reel(beat_path, output_name):
    base = output_name or os.path.splitext(os.path.basename(beat_path))[0]
    out = os.path.join(IG_DIR, f"{base}_reel.mp4")
    if os.path.exists(out) and os.path.getsize(out) > 50000:
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
    except Exception:
        pass
    return None

def post_to_instagram(video_path, caption):
    # Launch dedicated local Edge (headed) with its own profile
    import shutil
    if os.path.exists(IG_PROFILE):
        # reuse existing (keeps login)
        pass
    proc = subprocess.Popen([
        EDGE_PATH, f"--remote-debugging-port={PORT}",
        f"--user-data-dir={IG_PROFILE}",
        "--no-first-run", "--no-default-browser-check",
        "about:blank"
    ], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    time.sleep(6)
    try:
        with sync_playwright() as pw:
            b = pw.chromium.connect_over_cdp(f"http://127.0.0.1:{PORT}")
            ctx = b.contexts[0]
            p = ctx.new_page()
            p.goto("https://www.instagram.com/", wait_until="domcontentloaded", timeout=45000)
            p.wait_for_timeout(10000)
            body = p.evaluate("document.body.innerText")
            # check if logged in
            needs_login = ("log in" in body.lower() and ("password" in body.lower() or "phone number" in body.lower() or "username" in body.lower()))
            if needs_login:
                print("  IG needs login — logging in with secrets...")
                user, pw = load_creds()
                if not user:
                    print("  No IG creds in .secrets.json")
                    b.close()
                    return False
                # Find login form fields
                try:
                    # IG login fields are name="email" and name="pass"
                    p.goto("https://www.instagram.com/accounts/login/", wait_until="domcontentloaded", timeout=30000)
                    p.wait_for_timeout(5000)
                    em = p.query_selector('input[name="email"]')
                    pwf = p.query_selector('input[name="pass"]')
                    if em and pwf:
                        em.fill(user)
                        pwf.fill(pw)
                        p.wait_for_timeout(1000)
                        # click the Log in button (div[role=button] with text 'Log in')
                        clicked = p.evaluate("(()=>{var b=Array.from(document.querySelectorAll('div[role=button],button')).find(x=>x.offsetParent&&(x.innerText||'').trim()==='Log in');if(b){b.click();return 'ok'}return 'nf'})()")
                        print('  login click:', clicked)
                        p.wait_for_timeout(9000)
                        print("  logged in")
                        p.goto("https://www.instagram.com/")
                        p.wait_for_timeout(7000)
                    else:
                        print("  login fields not found")
                        b.close()
                        return False
                except Exception as e:
                    print(f"  login error: {str(e)[:80]}")
                    b.close()
                    return False
            print("  IG ready")
            # New post
            p.evaluate("document.querySelector('svg[aria-label=\\\"New post\\\"]')?.closest('a,div[role=button]')?.click()")
            p.wait_for_timeout(3500)
            p.evaluate("Array.from(document.querySelectorAll('span,div,button,a')).filter(e=>(e.innerText||'').trim()==='Post'&&e.offsetParent)[0]?.click()")
            p.wait_for_timeout(4000)
            # Upload file (co-located so works)
            abs_path = os.path.abspath(video_path)
            fi = p.query_selector("input[type=file]")
            if fi:
                fi.set_input_files(abs_path, timeout=90000)
                print("  file set via input")
            else:
                with p.expect_file_chooser(timeout=20000) as fc:
                    p.evaluate("Array.from(document.querySelectorAll('span,button,div')).filter(e=>(e.innerText||'').trim()==='Select from computer'&&e.offsetParent)[0]?.click()")
                fc.value.set_files(abs_path)
                print("  file set via chooser")
            p.wait_for_timeout(25000)  # upload + process
            # Next x2
            for _ in range(2):
                try:
                    p.evaluate("Array.from(document.querySelectorAll('div[role=button],button')).filter(b=>(b.innerText||'').trim().toLowerCase()==='next'&&b.offsetParent)[0]?.click()")
                except Exception:
                    pass
                p.wait_for_timeout(6000)
            # Type caption
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
            # Share
            try:
                p.evaluate("Array.from(document.querySelectorAll('div[role=button],button')).filter(b=>(b.innerText||'').trim().toLowerCase()==='share'&&b.offsetParent)[0]?.click()")
            except Exception:
                pass
            p.wait_for_timeout(12000)
            print("  IG Reel posted!")
            b.close()
            return True
    except Exception as e:
        print(f"  IG post error: {str(e)[:120]}")
        return False
    finally:
        try:
            proc.terminate()
        except Exception:
            pass

def post_beat_to_instagram(beat_path, track_title, genre, yt_link="", bpm=0):
    base = os.path.splitext(os.path.basename(beat_path))[0]
    reel = create_beat_reel(beat_path, base)
    if not reel:
        print("  Convert failed")
        return False
    if not bpm:
        try:
            import librosa
            import numpy as np
            y, sr = librosa.load(beat_path, sr=22050)
            tempo, _ = librosa.beat.beat_track(y=y, sr=sr)
            bpm = int(float(np.asarray(tempo).ravel()[0]))
        except Exception:
            bpm = 140
    caption = build_instagram_caption(track_title, genre, yt_link, bpm)
    return post_to_instagram(reel, caption)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python ig_poster_local.py <beat.mp4> <Title> [Genre] [YT Link]")
        sys.exit(1)
    beat = sys.argv[1]
    title = sys.argv[2]
    genre = sys.argv[3] if len(sys.argv) > 3 else "Psytrance"
    link = sys.argv[4] if len(sys.argv) > 4 else ""
    ok = post_beat_to_instagram(beat, title, genre, link)
    print("RESULT:", ok)
