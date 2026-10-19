import sys, os, json, time
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

def main():
    abs_path = os.path.abspath(sys.argv[1])
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
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
        # reject cookies
        try:
            page.click('button:has-text("Reject All")', timeout=6000)
        except Exception:
            pass
        page.wait_for_timeout(1500)
        print("STEP: click Add audio", flush=True)
        page.evaluate("Array.from(document.querySelectorAll('button')).find(x=>x.innerText.includes('Add audio'))?.click()")
        page.wait_for_timeout(5000)
        # Inspect what appears
        body = page.evaluate("document.body.innerText")
        print("after add-audio:", body[:400].replace(chr(10), " | "), flush=True)
        # find all buttons visible
        btns = page.evaluate("""JSON.stringify(Array.from(document.querySelectorAll('button,div[role=button]')).filter(e=>e.offsetParent).map(e=>(e.innerText||'').trim().slice(0,40)).filter(Boolean))""")
        print("buttons:", btns, flush=True)
        # check file inputs and the dialog structure
        dlg = page.evaluate("""JSON.stringify(Array.from(document.querySelectorAll('[role=dialog]')).map(d=>({txt:(d.innerText||'').slice(0,300)})))""")
        print("dialogs:", dlg[:600], flush=True)
        n = page.evaluate("document.querySelectorAll('input[type=file]').length")
        print("file inputs:", n, flush=True)
        if n > 0:
            for i in range(n):
                try:
                    page.set_input_files("input[type=file] >> nth=" + str(i), abs_path, timeout=15000)
                    print("file set nth=" + str(i), flush=True)
                except Exception as e:
                    print("nth" + str(i) + " err: " + str(e)[:50], flush=True)
            # now watch carefully for the terms/agree dialog
            print("watching for dialogs after file set...", flush=True)
            for t in range(10):
                page.wait_for_timeout(3000)
                dlg2 = page.evaluate("""JSON.stringify(Array.from(document.querySelectorAll('[role=dialog]')).map(d=>({txt:(d.innerText||'').slice(0,300)})))""")
                print(f"[{t*3}s] dialogs:", dlg2[:400], flush=True)
        b.close()

if __name__ == "__main__":
    main()
