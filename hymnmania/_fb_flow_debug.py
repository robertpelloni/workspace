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
        print("URL:", fb.url[:70])
        # click Add video
        r = fb.evaluate("""() => {
            var els = Array.from(document.querySelectorAll('div,span,[role=button]'));
            for (var i = 0; i < els.length; i++) {
                var e = els[i];
                if ((e.innerText||'').trim() === 'Add video' && e.offsetParent) {
                    var ir = e.getBoundingClientRect();
                    return JSON.stringify({x: Math.round(ir.x+ir.width/2), y: Math.round(ir.y+ir.height/2)});
                }
            }
            return 'none';
        }""")
        print("add video:", r)
        if r != 'none':
            d = json.loads(r)
            fb.mouse.click(d["x"], d["y"])
        fb.wait_for_timeout(3000)
        # set file
        try:
            fb.set_input_files("input[type=file]", video, timeout=120000)
            print("file set")
        except Exception as e:
            print("set err:", str(e)[:60])
        # wait and click Next carefully
        for step in range(4):
            fb.wait_for_timeout(6000)
            r2 = fb.evaluate("(function(){var els=Array.from(document.querySelectorAll('div[role=button],button'));for(var i=0;i<els.length;i++){var e=els[i];if((e.innerText||'').trim().toLowerCase()==='next'&&e.offsetParent){e.click();return 'clicked next '+(i)} }return 'none'})()")
            print(f"step {step} next:", r2)
            if r2 == 'none':
                break
        fb.wait_for_timeout(5000)
        # Now inspect all editable/textarea/editor and buttons
        info = fb.evaluate("""() => {
            var eds = Array.from(document.querySelectorAll('textarea,[contenteditable=true],[role=textbox],[data-editor]'));
            var out = eds.map((e,i) => ({i:i, tag:e.tagName, ce:e.getAttribute('contenteditable'), ar:e.getAttribute('aria-label')||'', ph:e.getAttribute('placeholder')||'', vis:!!e.offsetParent}));
            var btns = Array.from(document.querySelectorAll('div[role=button],button')).filter(e=>e.offsetParent).map(e=>(e.innerText||e.getAttribute('aria-label')||'').trim().slice(0,25)).filter(Boolean);
            return JSON.stringify({editors: out, buttons: btns.slice(0,20)});
        }""")
        print("after nexts:", info[:800])
        b.close()

if __name__ == "__main__":
    main()
