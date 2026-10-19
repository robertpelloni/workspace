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
    # click Remix via context-menu-item class
    r = p.evaluate("(()=>{var e=Array.from(document.querySelectorAll('.context-menu-item')).find(x=>(x.innerText||'').trim().toLowerCase()==='remix');if(e){e.click();return 'ok'}return 'nf'})()")
    print("remix:", r)
    # Remix may open a dropdown — hover over it or wait, then search for Cover broadly
    p.wait_for_timeout(2500)
    # Search for any 'Cover' text in clickable elements
    cov = p.evaluate("""
    () => {
        var all = document.querySelectorAll('.context-menu-item, [role=menuitem], button, div, span');
        for (var e of all) {
            var t = (e.innerText||'').trim();
            var a = (e.getAttribute && (e.getAttribute('aria-label')||'')) || '';
            if ((t === 'Cover' || a === 'Cover' || t.toLowerCase() === 'cover') && e.offsetParent && t.length < 30) {
                var r = e.getBoundingClientRect();
                if (r.width > 5) { e.click(); return 'clicked cover: ' + t; }
            }
        }
        return 'cover nf';
    }
    """)
    print("cover:", cov)
    p.wait_for_timeout(8000)
    print("url:", p.url[:60])
    # if on create page, check textareas
    body = p.evaluate("document.body.innerText")
    print("on create:", "create" in p.url, "| has song desc:", "song description" in body.lower())
    b.close()
