import sys, json, time
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

upload = "1c59abae-1e8a-4ccd-a20a-7c35600ee47a"
with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
    # find a stable suno page or make one
    p = next((x for x in b.contexts[0].pages if "suno.com" in x.url), None)
    if not p:
        p = b.contexts[0].new_page()
    # NAVIGATE to create first (loads app), then to song
    p.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
    p.wait_for_timeout(5000)
    p.goto(f"https://suno.com/song/{upload}", wait_until="domcontentloaded", timeout=30000)
    p.wait_for_timeout(8000)
    btn = p.query_selector('button[aria-label="More menu contents"]')
    if btn:
        btn.click()
        p.wait_for_timeout(3000)
    # find remix item position
    r = p.evaluate("(()=>{var e=Array.from(document.querySelectorAll('.context-menu-item')).find(x=>(x.innerText||'').trim().toLowerCase()==='remix');if(!e)return 'nf';var rr=e.getBoundingClientRect();return JSON.stringify({x:Math.round(rr.x+rr.width/2),y:Math.round(rr.y+rr.height/2)})})()")
    print("remix:", r)
    if r != 'nf':
        d = json.loads(r)
        p.mouse.click(d["x"], d["y"])
        print("clicked remix at", d)
        # Now WATCH for what appears over next 8s — dump context-menu items each 2s
        for i in range(4):
            p.wait_for_timeout(2000)
            its = p.evaluate("(()=>{var o=[];var all=document.querySelectorAll('.context-menu-item,[role=menuitem],[role=menu] *,li');for(var e of all){var t=(e.innerText||'').trim();if(t&&t.length<30&&e.offsetParent)o.push(t)}return JSON.stringify([...new Set(o)])})()")
            print(f"[{i*2}s] items:", its)
        # Also check if URL changed
        print("url:", p.url[:60])
        # click Cover if present now
        c = p.evaluate("(()=>{var all=document.querySelectorAll('.context-menu-item,[role=menuitem],li,button,div,span');for(var e of all){var t=(e.innerText||'').trim();if(t==='Cover'&&e.offsetParent){e.click();return 'ok'}}return 'nf'})()")
        print("cover:", c)
        p.wait_for_timeout(6000)
        print("url after cover:", p.url[:60])
    b.close()
