import sys, json, time
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

upload = "1c59abae-1e8a-4ccd-a20a-7c35600ee47a"  # Just Over
with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
    p = next((x for x in b.contexts[0].pages if "suno.com" in x.url), None)
    p.goto(f"https://suno.com/song/{upload}", wait_until="domcontentloaded", timeout=30000)
    p.wait_for_timeout(8000)
    btn = p.query_selector('button[aria-label="More menu contents"]')
    if btn:
        btn.click()
        p.wait_for_timeout(3500)
    # find ALL context-menu-item divs with their text (full menu incl top items)
    items = p.evaluate("""
    () => {
        var els = document.querySelectorAll('.context-menu-item');
        var out = [];
        for (var e of els) {
            var t = (e.innerText||'').trim();
            if (t && t.length < 40) out.push(t);
        }
        return JSON.stringify(out);
    }
    """)
    print("context menu items:", items)
    # click Remix if present
    r = p.evaluate("""
    () => {
        var els = Array.from(document.querySelectorAll('.context-menu-item'));
        for (var e of els) {
            if ((e.innerText||'').trim().toLowerCase() === 'remix') { e.click(); return 'clicked remix'; }
        }
        return 'remix not found';
    }
    """)
    print("remix:", r)
    p.wait_for_timeout(3500)
    # after remix, look for Cover submenu
    cover = p.evaluate("""
    () => {
        var els = Array.from(document.querySelectorAll('.context-menu-item'));
        var found = [];
        for (var e of els) {
            var t = (e.innerText||'').trim();
            if (t && t.length < 40) found.push(t);
        }
        var c = els.find(e => (e.innerText||'').trim().toLowerCase() === 'cover');
        if (c) { c.click(); return 'clicked cover: ' + JSON.stringify(found); }
        return 'cover not found. items: ' + JSON.stringify(found);
    }
    """)
    print("cover:", cover)
    p.wait_for_timeout(6000)
    print("url now:", p.url[:60])
    b.close()
