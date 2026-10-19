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
    # Inspect the Remix item's DOM structure (does it have a chevron/submenu?)
    info = p.evaluate("""
    () => {
        var e = Array.from(document.querySelectorAll('.context-menu-item')).find(x=>(x.innerText||'').trim().toLowerCase()==='remix');
        if (!e) return 'remix not in .context-menu-item';
        var out = {tag: e.tagName, cls: (e.className||'').toString().slice(0,60), html: e.outerHTML.slice(0,400)};
        // find its parent menu and siblings
        var par = e.parentElement;
        if (par) { out.parent_cls = (par.className||'').toString().slice(0,60); out.siblings = Array.from(par.children).map(c=>(c.innerText||'').trim().slice(0,20)); }
        return JSON.stringify(out);
    }
    """)
    print("remix dom:", info)
    # Get the remix element's position properly
    pos = p.evaluate("""
    () => {
        var e = Array.from(document.querySelectorAll('.context-menu-item')).find(x=>(x.innerText||'').trim().toLowerCase()==='remix');
        if (!e) return 'nf';
        var r = e.getBoundingClientRect();
        return JSON.stringify({x: Math.round(r.x), y: Math.round(r.y), w: Math.round(r.width), h: Math.round(r.height), vis: r.width>0 && r.height>0});
    }
    """)
    print("remix rect:", pos)
    b.close()
