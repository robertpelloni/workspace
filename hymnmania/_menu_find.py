import sys, json, time
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

upload = "d2246d83-d592-4081-89eb-218a765535a9"  # Jesus (known working)
with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
    p = next((x for x in b.contexts[0].pages if "suno.com" in x.url), None)
    p.goto(f"https://suno.com/song/{upload}", wait_until="domcontentloaded", timeout=30000)
    p.wait_for_timeout(8000)
    # find the More menu contents button and its actual menu
    btn = p.query_selector('button[aria-label="More menu contents"]')
    print("more btn:", "found" if btn else "missing")
    if btn:
        # click via playwright (real click)
        btn.click()
        p.wait_for_timeout(3500)
    # Now find ALL elements that could be the menu popup
    info = p.evaluate("""
    () => {
        var out = [];
        // Look for elements with data-radix-menu or role=menu
        var menus = document.querySelectorAll('[data-radix-menu-content], [role=menu], [data-slot="menu-content"], [class*="menu"]');
        for (var m of menus) {
            var t = (m.innerText||'').trim();
            if (t.length > 5 && t.length < 300) out.push({tag: m.tagName, cls: (m.className||'').toString().slice(0,40), text: t.slice(0,200)});
        }
        return JSON.stringify(out);
    }
    """)
    print("menus found:", info)
    b.close()
