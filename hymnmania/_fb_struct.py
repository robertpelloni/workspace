import sys, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
    fb = b.contexts[0].new_page()
    fb.goto("https://www.facebook.com/reels/create", wait_until="domcontentloaded", timeout=30000)
    fb.wait_for_timeout(9000)
    print("URL:", fb.url[:70])
    # Inspect all file inputs: accept, position, visibility
    js = """
    () => {
        var ins = document.querySelectorAll('input[type=file]');
        var out = [];
        for (var i = 0; i < ins.length; i++) {
            var f = ins[i];
            var r = f.getBoundingClientRect();
            var st = getComputedStyle(f);
            out.push({i: i, accept: f.accept || '', x: Math.round(r.x), y: Math.round(r.y),
                      w: Math.round(r.width), h: Math.round(r.height),
                      display: st.display, visible: !!(f.offsetWidth || f.offsetHeight)});
        }
        return JSON.stringify(out);
    }
    """
    info = fb.evaluate(js)
    print("file inputs detail:", info)
    # Also find the create-reel container text and any element with 'or drag and drop'
    js2 = """
    () => {
        var els = Array.from(document.querySelectorAll('span,div'));
        var out = [];
        for (var i = 0; i < els.length; i++) {
            var e = els[i];
            var t = (e.innerText || '').trim();
            if ((t === 'Add video' || t.includes('drag and drop') || t === 'Create reel') && e.offsetParent) {
                var r = e.getBoundingClientRect();
                out.push({t: t.slice(0,40), x: Math.round(r.x), y: Math.round(r.y), tag: e.tagName});
            }
        }
        return JSON.stringify(out.slice(0,10));
    }
    """
    info2 = fb.evaluate(js2)
    print("create elements:", info2)
    b.close()
