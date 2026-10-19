import sys, json, time
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

upload = "1c59abae-1e8a-4ccd-a20a-7c35600ee47a"
with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
    p = next((x for x in b.contexts[0].pages if "suno.com" in x.url), None)
    p.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
    p.wait_for_timeout(4000)
    p.goto(f"https://suno.com/song/{upload}", wait_until="domcontentloaded", timeout=30000)
    p.wait_for_timeout(8000)
    btn = p.query_selector('button[aria-label="More menu contents"]')
    if btn:
        btn.click()
        p.wait_for_timeout(3000)
    # HOVER over the Remix BUTTON (data-context-menu-trigger) to open submenu
    r = p.evaluate("""
    () => {
        var b = Array.from(document.querySelectorAll('button[data-context-menu-trigger=true]')).find(x=>{
            var it = x.closest('.context-menu-item');
            return it && (it.innerText||'').trim().toLowerCase()==='remix';
        });
        if (!b) {
            // fallback: find any context-menu button whose text is remix
            b = Array.from(document.querySelectorAll('.context-menu-button')).find(x=>(x.innerText||'').trim().toLowerCase().startsWith('remix'));
        }
        if (!b) return 'nf';
        var rr = b.getBoundingClientRect();
        return JSON.stringify({x: Math.round(rr.x+rr.width/2), y: Math.round(rr.y+rr.height/2), txt:(b.innerText||'').trim().slice(0,20)});
    }
    """)
    print("remix btn:", r)
    if r != 'nf':
        d = json.loads(r)
        p.mouse.move(d["x"], d["y"])  # hover to open submenu
        p.wait_for_timeout(3500)
        # now look for Cover submenu item
        cover = p.evaluate("""
        () => {
            var all = document.querySelectorAll('.context-menu-item, [role=menuitem], li, button, div');
            var hits = [];
            for (var e of all) {
                var t = (e.innerText||'').trim();
                var isBtn = e.tagName === 'BUTTON' || e.getAttribute('role') === 'menuitem';
                if (t === 'Cover' && e.offsetParent && (isBtn || t.length < 30)) {
                    var rr = e.getBoundingClientRect();
                    if (rr.width > 5) hits.push({x: Math.round(rr.x+rr.width/2), y: Math.round(rr.y+rr.height/2), tag: e.tagName});
                }
            }
            return JSON.stringify(hits);
        }
        """)
        print("cover positions:", cover)
        cover_list = json.loads(cover)
        if cover_list:
            # click the first Cover
            p.mouse.click(cover_list[0]["x"], cover_list[0]["y"])
            print("clicked cover")
            p.wait_for_timeout(8000)
            print("url after cover:", p.url[:60])
    b.close()
