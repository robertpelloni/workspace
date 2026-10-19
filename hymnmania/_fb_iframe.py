import sys, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright
with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
    fb = b.contexts[0].new_page()
    fb.goto("https://www.facebook.com/reels/create", wait_until="domcontentloaded", timeout=40000)
    fb.wait_for_timeout(10000)
    # list iframes
    frames = fb.frames
    print("frames:", len(frames))
    for fr in frames:
        print("  frame:", fr.url[:80])
    # click create reel
    r0 = fb.evaluate("""() => { var els=Array.from(document.querySelectorAll('div,span,[role=button]')); for(var i=0;i<els.length;i++){ var e=els[i]; var t=(e.innerText||'').trim(); if(t==='Create reel'&&e.offsetParent){ var rr=e.getBoundingClientRect(); if(rr.y>40&&rr.y<150) return JSON.stringify({x:Math.round(rr.x+rr.width/2),y:Math.round(rr.y+rr.height/2)}); } } return 'none'; }""")
    if r0 != 'none':
        d0 = json.loads(r0); fb.mouse.click(d0["x"], d0["y"]); fb.wait_for_timeout(6000)
    # new frame check
    print("frames after click:", len(fb.frames))
    for fr in fb.frames:
        u = fr.url
        if 'video' in u or 'reel' in u or 'create' in u:
            print("  relevant frame:", u[:80])
    b.close()
