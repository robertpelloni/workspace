import sys, os, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def main():
    video = os.path.abspath(sys.argv[1])
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        fb = b.contexts[0].new_page()
        fb.goto("https://www.facebook.com/reels/create", wait_until="domcontentloaded", timeout=40000)
        fb.wait_for_timeout(10000)
        # click the Create reel button (use the one around y=80 which is likely top nav)
        r = fb.evaluate("""() => {
            var els = Array.from(document.querySelectorAll('div,span,[role=button]'));
            for (var i = 0; i < els.length; i++) {
                var e = els[i];
                var t = (e.innerText || '').trim();
                if (t === 'Create reel' && e.offsetParent) {
                    var rr = e.getBoundingClientRect();
                    // prefer y between 40-120 (top nav) 
                    if (rr.y > 40 && rr.y < 120) {
                        return JSON.stringify({x: Math.round(rr.x+rr.width/2), y: Math.round(rr.y+rr.height/2)});
                    }
                }
            }
            return 'none';
        }""")
        print("create btn:", r)
        if r != 'none':
            d = json.loads(r)
            fb.mouse.click(d["x"], d["y"])
            fb.wait_for_timeout(6000)
        print("URL now:", fb.url[:70])
        body = fb.evaluate("document.body.innerText")
        print("body:", body[:250].replace(chr(10), " | "))
        # check file input
        n = fb.evaluate("document.querySelectorAll('input[type=file]').length")
        print("file inputs:", n)
        if n > 0:
            try:
                fb.set_input_files("input[type=file]", video, timeout=90000)
                print("FILE SET OK")
            except Exception as e:
                print("set err:", str(e)[:60])
        fb.wait_for_timeout(15000)
        body2 = fb.evaluate("document.body.innerText")
        print("after:", body2[:250].replace(chr(10), " | "))
        b.close()

if __name__ == "__main__":
    main()
