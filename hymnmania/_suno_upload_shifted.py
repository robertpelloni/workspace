import sys, os, json, time
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

def main():
    abs_path = os.path.abspath(sys.argv[1])
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9333")
        for p in list(b.contexts[0].pages):
            if "suno.com" in p.url:
                try:
                    p.close()
                except Exception:
                    pass
        time.sleep(1)
        page = b.contexts[0].new_page()
        page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
        page.wait_for_timeout(9000)
        try:
            page.click('button:has-text("Reject All")', timeout=6000)
        except Exception:
            pass
        page.wait_for_timeout(1500)
        # click Add audio
        page.evaluate("Array.from(document.querySelectorAll('button')).find(x=>x.innerText.includes('Add audio'))?.click()")
        page.wait_for_timeout(4000)
        # set file
        n = page.evaluate("document.querySelectorAll('input[type=file]').length")
        set_ok = False
        for i in range(n):
            try:
                page.set_input_files("input[type=file] >> nth=" + str(i), abs_path, timeout=20000)
                set_ok = True
                print("file set nth=" + str(i), flush=True)
            except Exception:
                pass
        if not set_ok:
            print("file set failed", flush=True)
            b.close()
            return
        # Agree to terms if the dialog appears
        page.wait_for_timeout(4000)
        body = page.evaluate("document.body.innerText")
        if "agree" in body.lower() or "terms" in body.lower():
            r = page.evaluate("(()=>{var els=Array.from(document.querySelectorAll('button,span,div')).filter(e=>e.offsetParent&&/agree|accept|i understand/i.test((e.innerText||''))&&(e.innerText||'').length<60);if(els.length){els[els.length-1].click();return 'clicked '+els.length}return 'nf'})()")
            print("terms click:", r, flush=True)
            page.wait_for_timeout(3000)
        # watch for copyright match or progress
        print("watching upload state...", flush=True)
        for i in range(20):
            page.wait_for_timeout(4000)
            body = page.evaluate("document.body.innerText")
            low = body.lower()
            if "matches an existing recording" in low or "copyright" in low or "already exists" in low:
                print("COPYRIGHT MATCH DETECTED at " + str((i+1)*4) + "s", flush=True)
                break
            elif "full song" in low and "uploading" not in low:
                print("UPLOAD SUCCEEDED — full song modal at " + str((i+1)*4) + "s", flush=True)
                break
            elif "uploading" in low:
                if i % 3 == 0:
                    print("  uploading... " + str((i+1)*4) + "s", flush=True)
        b.close()

if __name__ == "__main__":
    main()
