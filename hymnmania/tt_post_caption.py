"""Post caption + publish to TikTok. Usage: python tt_post_caption.py"""
import sys, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

caption = """🌀 RESURRECTING BEATS: 'Jesus Comes With Power' [Japanese Hardcore Techno] ⚡

Resurrected from the vault! High-energy 185 BPM J-Core beat packed with spiritual energy & driving bass. Built for festivals, vocalists, and live sets.

🎧 Full video on YouTube (link in bio)!
💬 Comment 'JCWP' for the untagged high-quality link.

#ResurrectingBeats #EDM #Psytrance #SpiritualEDM #ElectronicMusic #Dance #DanceSafe #HymnMania

#producertok #edmmusic #trancefamily #festivalbeats #hardcoretechno #JapaneseHardcore #resurrectingbeats"""

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
    page = next((p for p in b.contexts[0].pages if 'tiktok.com' in p.url), None)
    # clear existing filename caption and type new one
    try:
        box = page.query_selector('[data-e2e="caption_container"] textarea, [data-e2e="caption_container"] [contenteditable=true], [data-e2e="caption-input"]')
        if not box:
            # the caption box may be the Description area; find editable
            box = page.query_selector('[data-e2e="caption_container"] [contenteditable="true"], [data-e2e="caption_container"] textarea')
        if box:
            box.click()
            page.wait_for_timeout(500)
            # select all + delete
            box.press('Control+A')
            box.press('Delete')
            box.type(caption, delay=15)
            print('caption typed')
        else:
            # try JS approach
            r = page.evaluate('''(()=>{var el=document.querySelector('[data-e2e="caption_container"] [contenteditable="true"]')||document.querySelector('[data-e2e="caption_container"] textarea')||document.querySelector('[contenteditable="true"]');if(!el)return 'no box';el.focus();return el.tagName})()''')
            print('js focus:', r)
            if r != 'no box':
                page.keyboard.press('Control+A')
                page.keyboard.type(caption, delay=15)
                print('typed via keyboard')
    except Exception as e:
        print('caption err:', str(e)[:80])
    page.wait_for_timeout(3000)
    # verify caption length
    txt = page.evaluate('''(()=>{var el=document.querySelector('[data-e2e="caption_container"] [contenteditable="true"]')||document.querySelector('[data-e2e="caption_container"] textarea');return el?el.innerText.slice(0,60):''})()''')
    print('caption now:', txt)
    b.close()
