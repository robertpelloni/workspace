import sys, os, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def main():
    video = os.path.abspath(sys.argv[1])
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        fb = b.contexts[0].new_page()
        fb.goto("https://www.facebook.com/reels/create", wait_until="domcontentloaded", timeout=40000)
        fb.wait_for_timeout(12000)
        print("URL:", fb.url[:60])
        # Set the file on input[1] (the second input often is the active composer one)
        try:
            fb.set_input_files("input[type=file] >> nth=1", video, timeout=120000)
            print("set on nth=1 OK")
        except Exception as e:
            print("nth1 err:", str(e)[:50])
            try:
                fb.set_input_files("input[type=file] >> nth=0", video, timeout=120000)
                print("set on nth=0 OK")
            except Exception as e2:
                print("nth0 err:", str(e2)[:50])
        # Wait for upload/copyright
        for i in range(25):
            fb.wait_for_timeout(5000)
            body = fb.evaluate("document.body.innerText")
            low = body.lower()
            if "checking for copyrighted" in low:
                print(f"  checking ({i*5}s)")
            elif "replace video" in low or "your video" in low:
                print(f"  uploaded ({i*5}s)")
                break
            elif i == 24:
                print("  timeout waiting")
        # Now what buttons exist?
        dump = fb.evaluate("""() => {
            var btns = Array.from(document.querySelectorAll('div[role=button],button')).filter(e=>e.offsetParent).map(e=>(e.innerText||e.getAttribute('aria-label')||'').trim().slice(0,30)).filter(Boolean);
            var eds = Array.from(document.querySelectorAll('[contenteditable=true],textarea,[role=textbox]')).filter(e=>e.offsetParent).length;
            return JSON.stringify({buttons: [...new Set(btns)].slice(0,20), editors: eds});
        }""")
        print("state:", dump)
        b.close()

if __name__ == "__main__":
    main()
