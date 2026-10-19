import sys, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
    p = b.contexts[0].new_page()
    p.goto("https://www.instagram.com/", wait_until="domcontentloaded", timeout=30000)
    p.wait_for_timeout(7000)
    js = """
    () => {
        var out = [];
        var all = document.querySelectorAll('*');
        for (var i = 0; i < all.length; i++) {
            var e = all[i];
            if (e.getAttribute && e.getAttribute('aria-label') === 'New post') {
                var r = e.getBoundingClientRect();
                out.push({tag: e.tagName, cls: (e.className||'').toString().slice(0,50), x: Math.round(r.x), y: Math.round(r.y)});
            }
        }
        return JSON.stringify(out.slice(0, 10));
    }
    """
    info = p.evaluate(js)
    print("new post elements:", info)
    b.close()
