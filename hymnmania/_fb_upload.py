import sys, os, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def main():
    video = os.path.abspath(sys.argv[1])
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        fb = b.contexts[0].new_page()
        fb.goto("https://www.facebook.com/reels/create", wait_until="domcontentloaded", timeout=30000)
        fb.wait_for_timeout(9000)
        print("URL:", fb.url[:70])
        # Look for the create-reel container with Add video
        # Find clickable 'Add video' area
        n = fb.evaluate("document.querySelectorAll('input[type=file]').length")
        print("file inputs:", n)
        if n > 0:
            try:
                fb.set_input_files("input[type=file]", video, timeout=90000)
                print("SET OK on input")
            except Exception as e:
                print("set err:", str(e)[:100])
        else:
            # click 'Add video'
            r = fb.evaluate("(function(){var els=Array.from(document.querySelectorAll('span,div,button'));for(var i=0;i<els.length;i++){var e=els[i];if((e.innerText||'').trim()==='Add video'&&e.offsetParent){e.click();return 'clicked'}}return 'nf'})()")
            print("add video click:", r)
            fb.wait_for_timeout(4000)
            n = fb.evaluate("document.querySelectorAll('input[type=file]').length")
            print("file inputs after:", n)
            if n > 0:
                try:
                    fb.set_input_files("input[type=file]", video, timeout=90000)
                    print("SET OK after click")
                except Exception as e:
                    print("set err:", str(e)[:100])
        fb.wait_for_timeout(15000)
        body = fb.evaluate("document.body.innerText")
        print("after:", body[:200].replace(chr(10), " | "))
        b.close()

if __name__ == "__main__":
    main()
