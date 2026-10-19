"""Test: IG file upload via main CDP browser (port 9222, logged in).
Sets file directly on input[type=file] that IG keeps mounted in the create dialog.
"""
import sys, os, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def main():
    video = os.path.abspath(sys.argv[1])
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        p = b.contexts[0].new_page()
        p.goto("https://www.instagram.com/", wait_until="domcontentloaded", timeout=30000)
        p.wait_for_timeout(7000)
        # Click New post svg
        p.evaluate("(function(){var s=document.querySelector('svg[aria-label=\\\"New post\\\"]');if(!s)return 'no';var el=s.closest('a,[role=button],div');(el||s).click();return 'ok'})()")
        p.wait_for_timeout(3000)
        # Click Post
        p.evaluate("(function(){var els=Array.from(document.querySelectorAll('span,div,button'));for(var e of els){if((e.innerText||'').trim()==='Post'&&e.offsetParent){e.click();return 'ok'}}return 'nf'})()")
        p.wait_for_timeout(4000)
        # The dialog should have the file input already (IG mounts hidden input)
        n = p.evaluate("document.querySelectorAll('input[type=file]').length")
        print("file inputs:", n)
        if n > 0:
            # Try set_input_files on the FIRST input
            try:
                p.set_input_files("input[type=file]", video, timeout=60000)
                print("SET OK via set_input_files")
            except Exception as e:
                print("set err:", str(e)[:120])
        else:
            print("no input - checking dialog text")
            body = p.evaluate("document.body.innerText")
            print("body:", body[:200].replace(chr(10), " | "))
        p.wait_for_timeout(8000)
        body = p.evaluate("document.body.innerText")
        print("after:", body[:200].replace(chr(10), " | "))
        b.close()

if __name__ == "__main__":
    main()
