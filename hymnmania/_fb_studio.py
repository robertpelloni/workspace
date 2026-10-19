import sys, os, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def main():
    video = os.path.abspath(sys.argv[1])
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        fb = b.contexts[0].new_page()
        fb.goto("https://business.facebook.com/latest/reels_composer", wait_until="domcontentloaded", timeout=40000)
        fb.wait_for_timeout(10000)
        print("URL:", fb.url[:70])
        body = fb.evaluate("document.body.innerText")
        print("body:", body[:300].replace(chr(10), " | "))
        # find file input
        n = fb.evaluate("document.querySelectorAll('input[type=file]').length")
        print("file inputs:", n)
        # find upload button text
        js = """
        () => {
            var els = Array.from(document.querySelectorAll('div,span,button,[role=button]'));
            var out = [];
            for (var i = 0; i < els.length; i++) {
                var e = els[i];
                var t = (e.innerText || '').trim();
                if ((t.includes('upload') || t.includes('Add video') || t === 'Select video' || t.includes('drag')) && t.length < 60 && e.offsetParent) {
                    out.push(t.slice(0,50));
                }
            }
            return JSON.stringify([...new Set(out)].slice(0,10));
        }
        """
        print("upload texts:", fb.evaluate(js))
        b.close()

if __name__ == "__main__":
    main()
