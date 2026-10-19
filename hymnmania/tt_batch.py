"""Batch post videos to TikTok. Usage: python tt_batch.py video1|capfile1 video2|capfile2 ...
"""
import sys, io, os, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def post_one(page, abs_path, caption):
    page.goto('https://www.tiktok.com/upload', wait_until='domcontentloaded', timeout=30000)
    page.wait_for_timeout(6000)
    try:
        page.click('[data-e2e="select_video_button"]', timeout=8000)
    except Exception:
        page.evaluate("Array.from(document.querySelectorAll('button')).find(x=>/select video/i.test(x.innerText||''))?.click()")
    page.wait_for_timeout(2000)
    page.set_input_files('[data-e2e="upload-input"],input[type=file]', abs_path, timeout=90000)
    for i in range(30):
        page.wait_for_timeout(3000)
        body = page.evaluate('document.body.innerText')
        if 'uploaded' in body.lower() and 'description' in body.lower():
            break
    page.wait_for_timeout(2000)
    page.evaluate("document.querySelector('[contenteditable=true]')?.focus()")
    page.wait_for_timeout(500)
    page.keyboard.press('Control+A')
    page.keyboard.press('Delete')
    page.keyboard.type(caption, delay=4)
    page.wait_for_timeout(2500)
    r = page.evaluate("(()=>{var b=document.querySelector('[data-e2e=post_video_button]');if(b){b.scrollIntoView({block:'center'});b.click();return 'clicked'}return 'nf'})()")
    print(f"  posted: {os.path.basename(abs_path)} click={r}", flush=True)
    page.wait_for_timeout(8000)

def main():
    jobs = sys.argv[1:]
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
        page = next((p for p in b.contexts[0].pages if 'tiktok.com' in p.url), None)
        if not page:
            page = b.contexts[0].new_page()
        for job in jobs:
            video, capfile = job.split('|')
            cap = io.open(capfile, encoding='utf-8').read()
            print(f"posting {os.path.basename(video)}", flush=True)
            try:
                post_one(page, os.path.abspath(video), cap)
            except Exception as e:
                print(f"  err: {str(e)[:80]}", flush=True)
        b.close()
    print('ALL DONE')

if __name__ == '__main__':
    main()
