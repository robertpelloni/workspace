"""Post a short video to TikTok with caption. Usage: python tt_post.py <video_path> <caption_file_or_text>
Posts via tiktok.com/upload with the logged-in @resurrecting.beat session.
"""
import sys, os, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def post_video(page, abs_path, caption):
    # Go to upload
    page.goto('https://www.tiktok.com/upload', wait_until='domcontentloaded', timeout=30000)
    page.wait_for_timeout(6000)
    # Click select video
    try:
        page.click('[data-e2e="select_video_button"]', timeout=8000)
    except Exception:
        page.evaluate("Array.from(document.querySelectorAll('button')).find(x=>/select video/i.test(x.innerText||''))?.click()")
    page.wait_for_timeout(2000)
    # Set file
    page.set_input_files('[data-e2e="upload-input"],input[type=file]', abs_path, timeout=240000)
    print('file set, waiting for upload...')
    # Wait for upload to finish (filename disappears / Uploaded shows)
    for i in range(30):
        page.wait_for_timeout(3000)
        body = page.evaluate('document.body.innerText')
        if 'uploaded' in body.lower() and 'description' in body.lower():
            print(f'uploaded after ~{i*3+6}s')
            break
        if i == 29:
            print('upload wait timeout')
    page.wait_for_timeout(3000)
    # Focus caption editor, select all, type
    r = page.evaluate("document.querySelector('[contenteditable=\"true\"]')?.focus() ? 'ok' : 'nf'")
    page.wait_for_timeout(500)
    page.keyboard.press('Control+A')
    page.wait_for_timeout(300)
    page.keyboard.press('Delete')
    page.wait_for_timeout(300)
    page.keyboard.type(caption, delay=6)
    page.wait_for_timeout(3000)
    # Verify caption
    txt = page.evaluate("document.querySelector('[contenteditable=true]')?.innerText || ''")
    print('caption len:', len(txt))
    # Click Post
    r2 = page.evaluate("(()=>{var b=document.querySelector('[data-e2e=\"post_video_button\"]');if(b){b.scrollIntoView({block:'center'});b.click();return 'clicked'}return 'nf'})()")
    print('post click:', r2)
    page.wait_for_timeout(4000)
    # TikTok shows a confirmation dialog after Post ("Got it" info + "Post now"/"Cancel")
    page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).filter(x=>x.offsetParent).find(x=>/^got it$/i.test((x.innerText||'').trim()));if(b)b.click()})()")
    page.wait_for_timeout(1500)
    r3 = page.evaluate("(()=>{var btns=Array.from(document.querySelectorAll('button')).filter(x=>x.offsetParent);var pn=btns.find(x=>/^post now$/i.test((x.innerText||'').trim()));if(pn){pn.click();return 'post now'}var po=btns.find(x=>/^post$/i.test((x.innerText||'').trim()));if(po){po.click();return 'post'}return 'nf'})()")
    print('confirm click:', r3)
    page.wait_for_timeout(14000)
    # success = TikTok redirects the composer to the content manager
    return ('tiktokstudio/content' in page.url) or ('upload' not in page.url)
    return True

def main():
    abs_path = os.path.abspath(sys.argv[1])
    caption = sys.argv[2]
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
        page = next((p for p in b.contexts[0].pages if 'tiktok.com' in p.url), None)
        if not page:
            page = b.contexts[0].new_page()
        ok = post_video(page, abs_path, caption)
        b.close()
        print('DONE, posted:', ok)

if __name__ == '__main__':
    main()
