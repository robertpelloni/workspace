import sys, json, os, time
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

def main():
    abs_path = os.path.abspath(sys.argv[1])
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        page = next((p for p in b.contexts[0].pages if "suno.com" in p.url), None)
        if not page:
            page = b.contexts[0].new_page()
            page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
            page.wait_for_timeout(8000)
        # find the add-audio element broadly (aria or text or browse)
        info = page.evaluate("""
        () => {
            var els = Array.from(document.querySelectorAll('button,[role=button],div,span'));
            for (var i = 0; i < els.length; i++) {
                var e = els[i];
                var aria = (e.getAttribute && (e.getAttribute('aria-label')||'')) || '';
                var t = (e.innerText||'').trim();
                if (aria.includes('Add audio') || t.includes('Browse, upload') || (t.length < 60 && t.includes('Add audio'))) {
                    var r = e.getBoundingClientRect();
                    if (r.width > 20 && r.height > 10) {
                        return JSON.stringify({tag: e.tagName, aria: aria.slice(0,40), t: t.slice(0,50),
                            x: Math.round(r.x+r.width/2), y: Math.round(r.y+r.height/2), w: Math.round(r.width)});
                    }
                }
            }
            return 'none';
        }
        """)
        print("add audio:", info)
        if info == 'none':
            b.close()
            return
        d = json.loads(info)
        page.mouse.click(d["x"], d["y"])
        page.wait_for_timeout(6000)
        # after click, look for file input
        n = page.evaluate("document.querySelectorAll('input[type=file]').length")
        print("file inputs:", n)
        body = page.evaluate("document.body.innerText")
        for kw in ["upload", "browse", "record", "full song"]:
            if kw in body.lower():
                i = body.lower().find(kw)
                print(f"[{kw}]:", body[max(0,i-40):i+200].replace(chr(10), " | "))
                break
        if n > 0:
            for i in range(n):
                try:
                    page.set_input_files("input[type=file] >> nth=" + str(i), abs_path, timeout=20000)
                    print("set nth=" + str(i))
                except Exception as e:
                    print("nth" + str(i) + " err: " + str(e)[:50])
        # watch for modal
        for i in range(20):
            page.wait_for_timeout(5000)
            body = page.evaluate("document.body.innerText")
            low = body.lower()
            if "full song" in low and "uploading" not in low:
                print("FULL SONG MODAL at " + str((i+1)*5) + "s")
                page.evaluate("(()=>{var els=Array.from(document.querySelectorAll('span,div,label,button,li')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim()==='Full Song');if(els.length){els[0].click();return 'ok'}return 'nf'})()")
                page.wait_for_timeout(2000)
                page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&x.innerText.trim().toLowerCase()==='continue');if(b){b.click();return 'ok'}return 'nf'})()")
                print("modal confirmed")
                break
            elif "uploading" in low:
                if i % 3 == 0:
                    print("  uploading... " + str((i+1)*5) + "s")
        b.close()

if __name__ == "__main__":
    main()
