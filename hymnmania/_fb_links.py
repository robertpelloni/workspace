import sys, os, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def main():
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        fb = b.contexts[0].new_page()
        fb.goto("https://www.facebook.com/reels/create", wait_until="domcontentloaded", timeout=40000)
        fb.wait_for_timeout(12000)
        print("URL:", fb.url[:70])
        # Look for a 'Create reel' button/link to click that opens the composer
        js = """
        () => {
            var els = Array.from(document.querySelectorAll('a,div,span,[role=button],button'));
            var out = [];
            for (var i = 0; i < els.length; i++) {
                var e = els[i];
                var t = (e.innerText || '').trim();
                var href = e.getAttribute('href') || '';
                if ((t === 'Create reel' || href.includes('reels/create') || href.includes('reel_composer') || href.includes('create')) && t.length < 30 && e.offsetParent) {
                    var r = e.getBoundingClientRect();
                    out.push({t: t, href: href.slice(0,60), x: Math.round(r.x), y: Math.round(r.y), tag: e.tagName});
                }
            }
            return JSON.stringify(out.slice(0,15));
        }
        """
        print("create links:", fb.evaluate(js))
        # Also list ALL visible links with 'reel' or 'create' in href
        js2 = """
        () => {
            var links = Array.from(document.querySelectorAll('a[href]'));
            var out = [];
            for (var i = 0; i < links.length; i++) {
                var h = links[i].getAttribute('href');
                if ((h.includes('reel') || h.includes('composer') || h.includes('video')) && h.length < 100 && links[i].offsetParent) {
                    out.push({h: h.slice(0,90), t: (links[i].innerText||'').trim().slice(0,20)});
                }
            }
            return JSON.stringify([...new Map(out.map(o=>[o.h,o])).values()].slice(0,15));
        }
        """
        print("reel links:", fb.evaluate(js2))
        b.close()

if __name__ == "__main__":
    main()
