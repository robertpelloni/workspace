"""Debug Instagram reel upload flow step by step."""
import sys, os, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
    p = next((x for x in b.contexts[0].pages if 'instagram' in x.url), None)
    if not p:
        p = b.contexts[0].new_page()
        p.goto('https://www.instagram.com/', wait_until='domcontentloaded', timeout=30000)
        p.wait_for_timeout(5000)

    # Step 1: click New post via svg aria-label
    r = p.evaluate("""(()=>{
        var svg = document.querySelector('svg[aria-label="New post"]');
        if(svg){
            // click the clickable ancestor
            var el = svg.closest('div[role=button],a,span') || svg;
            var clickable = el.closest('[role=button],a') || el.parentElement || el;
            clickable.click();
            return 'clicked svg, parent=' + (clickable.tagName + '.' + (clickable.className||'').slice(0,20));
        }
        var els = Array.from(document.querySelectorAll('[role=button],a')).filter(e=>e.offsetParent);
        for(var e of els){
            if((e.querySelector('[aria-label="New post"]'))){
                e.click(); return 'clicked via role';
            }
        }
        return 'new post not found';
    })()""")
    print('step1 New post:', r)
    p.wait_for_timeout(3000)
    body = p.evaluate('document.body.innerText')
    print('after new post:', body[:250].replace(chr(10),' | '))
    b.close()
