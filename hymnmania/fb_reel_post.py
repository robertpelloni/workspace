"""Facebook Reel poster — WORKING flow (verified 2026-09-03).
Navigate to reels/create (may redirect to /reel/<id> but create tool is present),
click 'Add video' to mount file, set file on the hidden input, wait for
'Checking for copyrighted content' to clear, click Next, type caption,
scroll down, click Post by coordinates.

Usage: python fb_reel_post.py <video_path> <track_title> <genre> <yt_link>
"""
import sys, os, json, time, random, subprocess
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def build_caption(track_title, genre, yt_link):
    hashtags = f"#ResurrectingBeats #Hymnmania #SpiritualEDM #Psytrance #EDM #ElectronicMusic #{genre.replace(' ', '')} #PsychedelicTrance"
    ctas = [
        f"Can this {genre} frequency elevate your spirit? 👇 Drop a like and tell us below!",
        f"Which hymn should we resurrect next? 👇 Comment your pick!",
        f"Does electronic worship hit different for you too? 👇 Like + share if it does!",
        f"Feel that beat sync with your soul? 👇 Let us know in the comments!",
        f"Would you dance to this in a cathedral of light? 👇 Tell us what you think!",
    ]
    cta = random.choice(ctas)
    headline = f"{track_title} — {genre} electronic worship"
    link_line = f"\n\n▶️ Full 4K journey: {yt_link}" if yt_link else ""
    return f"""{headline}\n\n{cta}{link_line}\n\n{hashtags}"""

def click_add_video(fb):
    """Find and click the 'Add video' element inside the create-reel tool."""
    r = fb.evaluate("""
    () => {
        var els = Array.from(document.querySelectorAll('div,span,section,[role=button]'));
        for (var i = 0; i < els.length; i++) {
            var e = els[i];
            var t = (e.innerText || '').trim();
            if (t === 'Add video' && e.offsetParent) {
                var ir = e.getBoundingClientRect();
                return JSON.stringify({x: Math.round(ir.x+ir.width/2), y: Math.round(ir.y+ir.height/2)});
            }
        }
        return JSON.stringify({x: -1, y: -1});
    }
    """)
    d = json.loads(r)
    if d["x"] > 0:
        fb.mouse.click(d["x"], d["y"])
        return True
    return False

def main():
    video = os.path.abspath(sys.argv[1])
    title = sys.argv[2]
    genre = sys.argv[3]
    link = sys.argv[4] if len(sys.argv) > 4 else ""
    caption = build_caption(title, genre, link)

    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        fb = b.contexts[0].new_page()
        fb.goto("https://www.facebook.com/reels/create", wait_until="domcontentloaded", timeout=40000)
        fb.wait_for_timeout(10000)
        print("URL:", fb.url[:70], flush=True)

        # Click 'Create reel' (top nav) to open the composer first
        r0 = fb.evaluate("""() => {
            var els = Array.from(document.querySelectorAll('div,span,[role=button]'));
            for (var i = 0; i < els.length; i++) {
                var e = els[i];
                var t = (e.innerText || '').trim();
                if (t === 'Create reel' && e.offsetParent) {
                    var rr = e.getBoundingClientRect();
                    if (rr.y > 40 && rr.y < 150) {
                        return JSON.stringify({x: Math.round(rr.x+rr.width/2), y: Math.round(rr.y+rr.height/2)});
                    }
                }
            }
            return 'none';
        }""")
        if r0 != 'none':
            d0 = json.loads(r0)
            fb.mouse.click(d0["x"], d0["y"])
            fb.wait_for_timeout(6000)
            print("Create reel clicked", flush=True)

        # Click Add video to mount the correct input
        if not click_add_video(fb):
            print("no Add video btn", flush=True)
            b.close()
            return False
        fb.wait_for_timeout(3000)

        # Set the file on the mounted input
        n = fb.evaluate("document.querySelectorAll('input[type=file]').length")
        print(f"file inputs: {n}", flush=True)
        if n == 0:
            b.close()
            return False
        try:
            fb.set_input_files("input[type=file]", video, timeout=120000)
            print("file set", flush=True)
        except Exception as e:
            print(f"set err: {str(e)[:60]}", flush=True)
            b.close()
            return False

        # Wait for 'Checking for copyrighted content' to clear.
        # BUG (fixed): checking for the word 'next' broke out before the check even started.
        # Correct: give it time, require the indicator to be ABSENT (and Next present).
        print("waiting for copyright check...", flush=True)
        fb.wait_for_timeout(12000)
        for i in range(24):
            fb.wait_for_timeout(5000)
            body = fb.evaluate("document.body.innerText")
            low = body.lower()
            if "checking for copyrighted" in low:
                print(f"  still checking ({12 + i * 5}s)", flush=True)
                continue
            if "next" in low or "replace video" in low:
                print(f"  upload ready ({12 + i * 5}s)", flush=True)
                break

        # Click Next until the caption step is actually reached (the caption editor
        # renders a few seconds after Next; checking too early finds nothing).
        for _ in range(6):
            body = fb.evaluate("document.body.innerText")
            if "describe your reel" in body.lower():
                print("  caption step reached", flush=True)
                break
            r = fb.evaluate("(function(){var els=Array.from(document.querySelectorAll('div[role=button],button'));for(var i=0;i<els.length;i++){var e=els[i];if((e.innerText||'').trim().toLowerCase()==='next'&&e.offsetParent){e.click();return 'next'}}return 'none'})()")
            print(f"  next click: {r}", flush=True)
            fb.wait_for_timeout(7000 if r == 'next' else 4000)

        fb.wait_for_timeout(2000)
        # Type caption
        typed = fb.evaluate("""(function(){
            var e = Array.from(document.querySelectorAll('textarea, [contenteditable=true], [role=textbox], [aria-label*=Describe], [aria-label*=caption], [aria-label*="Describe your"]'))
                .find(x => x.offsetParent);
            if(e){ e.focus(); e.click(); return 'found'; }
            return 'no editor';
        })()""")
        print("caption field:", typed, flush=True)
        fb.wait_for_timeout(1500)
        if typed == 'found':
            fb.keyboard.type(caption, delay=8)
            fb.wait_for_timeout(3000)

        # Scroll down to reveal Post button
        fb.mouse.wheel(0, 3000)
        fb.wait_for_timeout(3000)

        # Click the Post button by coordinates
        rect = fb.evaluate("""(function(){
            var btns = Array.from(document.querySelectorAll('div[role=button], button')).filter(e => e.offsetParent && (e.innerText||e.textContent||'').trim() === 'Post');
            if(btns.length === 0) return 'none';
            var target = btns[btns.length-1];
            target.scrollIntoView({block:'center'});
            var r = target.getBoundingClientRect();
            return JSON.stringify({x: r.x + r.width/2, y: r.y + r.height/2, n: btns.length});
        })()""")
        print("post button:", rect, flush=True)
        if rect != 'none':
            c = json.loads(rect)
            fb.wait_for_timeout(1500)
            fb.mouse.click(c["x"], c["y"])
            fb.wait_for_timeout(10000)
            print(f"FB Reel posted: {title} — {genre}", flush=True)
            b.close()
            return True
        b.close()
        return False

if __name__ == "__main__":
    ok = main()
    print("RESULT:", ok)
