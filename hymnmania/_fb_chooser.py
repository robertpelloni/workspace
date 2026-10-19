import sys, os, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def main():
    video = os.path.abspath(sys.argv[1])
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        fb = b.contexts[0].new_page()
        fb.goto("https://www.facebook.com/reels/create", wait_until="domcontentloaded", timeout=30000)
        fb.wait_for_timeout(9000)
        print("URL:", fb.url[:60])
        # The create tool shows 'Create reel | Add video | or drag and drop'. 
        # Click the 'Create reel' heading area (should be the real creator studio)
        # Find the container with text starting 'Create reel' that is visible & small
        r = fb.evaluate("""
        () => {
            var els = Array.from(document.querySelectorAll('div,span,section'));
            for (var i = 0; i < els.length; i++) {
                var e = els[i];
                var t = (e.innerText || '').trim();
                if (t.startsWith('Create reel') && t.length < 200 && e.offsetParent) {
                    var rr = e.getBoundingClientRect();
                    if (rr.width > 200) {
                        // find the 'Add video' clickable inside
                        var inner = Array.from(e.querySelectorAll('span,div,[role=button]')).find(x => (x.innerText||'').trim() === 'Add video' && x.offsetParent);
                        if (inner) {
                            var ir = inner.getBoundingClientRect();
                            return JSON.stringify({action: 'click add video', x: Math.round(ir.x+ir.width/2), y: Math.round(ir.y+ir.height/2)});
                        }
                    }
                }
            }
            return JSON.stringify({action: 'nf'});
        }
        """)
        d = json.loads(r)
        print("found:", d)
        if d["action"] == "click add video":
            # use expect_file_chooser while clicking Add video
            try:
                with fb.expect_file_chooser(timeout=15000) as fc:
                    fb.mouse.click(d["x"], d["y"])
                fc.value.set_files(video)
                print("FILE SET via chooser")
            except Exception as e:
                print("chooser err:", str(e)[:80])
                # fallback: click then find input
                fb.mouse.click(d["x"], d["y"])
                fb.wait_for_timeout(3000)
                n = fb.evaluate("document.querySelectorAll('input[type=file]').length")
                print("inputs after click:", n)
        fb.wait_for_timeout(20000)
        body = fb.evaluate("document.body.innerText")
        print("after:", body[:250].replace(chr(10), " | "))
        b.close()

if __name__ == "__main__":
    main()
