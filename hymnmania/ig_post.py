"""Post reel to Instagram - retry with correct flow. Usage: python ig_post.py <video_path> <caption>"""
import sys, os, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def main():
    abs_path = os.path.abspath(sys.argv[1])
    caption = sys.argv[2] if len(sys.argv) > 2 else ''
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
        p = next((x for x in b.contexts[0].pages if 'instagram' in x.url), None)
        if not p:
            p = b.contexts[0].new_page()
            p.goto('https://www.instagram.com/', wait_until='domcontentloaded', timeout=30000)
            p.wait_for_timeout(5000)
        # Fresh: reload home
        p.goto('https://www.instagram.com/', wait_until='domcontentloaded', timeout=30000)
        p.wait_for_timeout(6000)
        # Click New post
        p.evaluate("""(()=>{var svg=document.querySelector('svg[aria-label="New post"]');if(svg){var el=svg.closest('[role=button],a')||svg.parentElement||svg;el.click();return 'ok'}return 'nf'})()""")
        p.wait_for_timeout(3000)
        # Click Post in create menu
        p.evaluate("""(()=>{var els=Array.from(document.querySelectorAll('span,div,button,a'));for(var e of els){if((e.innerText||'').trim()==='Post'&&e.offsetParent){e.click();return 'ok'}}return 'nf'})()""")
        p.wait_for_timeout(3000)
        # Now the file picker dialog should be open with input
        fi = p.query_selector('input[type=file]')
        if fi:
            try:
                fi.set_input_files(abs_path, timeout=20000)
                print('file set via input')
            except Exception as e:
                print('input set err:', str(e)[:60])
                # fallback: click and use chooser
                try:
                    with p.expect_file_chooser(timeout=15000) as fc:
                        fi.click()
                    fc.value.set_files(abs_path)
                    print('file set via chooser')
                except Exception as e2:
                    print('chooser err:', str(e2)[:60])
        else:
            print('no file input after clicking Post')
        p.wait_for_timeout(10000)
        body = p.evaluate('document.body.innerText')
        print('post-upload state:', body[:250].replace(chr(10),' | '))
        b.close()

if __name__ == '__main__':
    main()
