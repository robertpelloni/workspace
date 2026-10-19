import sys, json, time
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

upload = "1c59abae-1e8a-4ccd-a20a-7c35600ee47a"
with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
    p = next((x for x in b.contexts[0].pages if "suno.com" in x.url), None)
    p.goto(f"https://suno.com/song/{upload}", wait_until="domcontentloaded", timeout=30000)
    p.wait_for_timeout(8000)
    btn = p.query_selector('button[aria-label="More menu contents"]')
    if btn:
        btn.click()
        p.wait_for_timeout(3000)
    # HOVER over Remix (submenu may open on hover)
    r = p.evaluate("""
    () => {
        var e = Array.from(document.querySelectorAll('.context-menu-item')).find(x=>(x.innerText||'').trim().toLowerCase()==='remix');
        if (!e) return 'remix nf';
        var rect = e.getBoundingClientRect();
        return JSON.stringify({x: Math.round(rect.x+rect.width/2), y: Math.round(rect.y+rect.height/2)});
    }
    """)
    print("remix pos:", r)
    if r != 'remix nf':
        d = json.loads(r)
        p.mouse.move(d["x"], d["y"])
        p.wait_for_timeout(3000)
        # after hover, look for Cover anywhere
        items = p.evaluate("""
        () => {
            var out = [];
            var all = document.querySelectorAll('.context-menu-item, [role=menuitem], [role=menu] *, li, button');
            for (var e of all) {
                var t = (e.innerText||'').trim();
                if (t && t.length < 30 && e.offsetParent) out.push(t);
            }
            return JSON.stringify([...new Set(out)]);
        }
        """)
        print("items after hover:", items)
        # click Cover if appears
        c = p.evaluate("""
        () => {
            var all = document.querySelectorAll('.context-menu-item, [role=menuitem], li, button, div, span');
            for (var e of all) {
                var t = (e.innerText||'').trim();
                if ((t === 'Cover') && e.offsetParent) { e.click(); return 'clicked cover'; }
            }
            return 'nf';
        }
        """)
        print("cover:", c)
        p.wait_for_timeout(6000)
        print("url:", p.url[:60])
    b.close()
