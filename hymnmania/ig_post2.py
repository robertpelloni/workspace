"""Instagram Reel post - robust flow. Usage: python ig_post2.py <video_path>
Posts to the logged-in @resurrectingbeats account.
"""
import sys, os, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def main():
    abs_path = os.path.abspath(sys.argv[1])
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
        # fresh page
        p = b.contexts[0].new_page()
        p.goto('https://www.instagram.com/', wait_until='domcontentloaded', timeout=30000)
        p.wait_for_timeout(7000)
        # New post
        p.evaluate("document.querySelector('svg[aria-label=\\\"New post\\\"]')?.closest('a,div[role=button]')?.click()")
        p.wait_for_timeout(3000)
        # Click 'Post' (create new post)
        p.evaluate("Array.from(document.querySelectorAll('span,div,button,a')).filter(e=>(e.innerText||'').trim()==='Post'&&e.offsetParent)[0]?.click()")
        p.wait_for_timeout(4000)
        # The dialog 'Create new post' should be open. Look for file input
        n = p.evaluate("document.querySelectorAll('input[type=file]').length")
        print('file inputs:', n)
        if n == 0:
            # click Select from computer then the input should appear
            p.evaluate("Array.from(document.querySelectorAll('span,button,div')).filter(e=>(e.innerText||'').trim()==='Select from computer'&&e.offsetParent)[0]?.click()")
            p.wait_for_timeout(2000)
            n = p.evaluate("document.querySelectorAll('input[type=file]').length")
            print('after select file inputs:', n)
        # set file on the input (should exist now)
        if n > 0:
            try:
                p.set_input_files('input[type=file]', abs_path, timeout=30000)
                print('FILE SET OK')
            except Exception as e:
                print('set err:', str(e)[:80])
        else:
            # try clicking the visible 'Select from computer' area which mounts input
            print('no input found - trying drag area click')
        p.wait_for_timeout(12000)
        body = p.evaluate('document.body.innerText')
        print('after upload:', body[:250].replace(chr(10),' | '))
        # save page ref for next step
        json.dump({'url': p.url}, open('.ig_state.json','w'))
        b.close()

if __name__ == '__main__':
    main()
