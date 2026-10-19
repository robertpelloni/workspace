"""Trigger ONE genre cover with VERIFIED description injection.
Confirms the textarea value is set before clicking Create.
Usage: python trigger_verified.py <genre>
"""
import sys, os, json, time, requests
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

SUNO = 'https://studio-api-prod.suno.com'
UPLOAD = 'd2246d83-d592-4081-89eb-218a765535a9'

GENRE_DESC = {
    'chiptune': 'chiptune, 8-bit square wave leads, arpeggios, triangle bass, noise percussion, retro video game soundtrack energy',
    'drum_and_bass': 'drum and bass, fast 174 BPM breakbeats, rolling sub-bass, reese bass swells, chopped breaks, high-energy syncopated drum work',
    'gabba': 'gabba hardcore, relentlessly distorted kick drums at 190 BPM, saturated low end, aggressive rave atmosphere, industrial hardcore energy',
    'dubstep': 'brostep dubstep, massive LFO wobble bass drops, half-time 140 BPM drums, growling midrange basses, festival-ready bass music',
    'synthwave': 'synthwave, warm analog polysynths, pulsing sidechained bassline, 100-110 BPM neon-drenched retro-future groove, 1980s nostalgia',
    'japanese_hardcore_techno': 'japanese hardcore techno, 180-190 BPM distorted kicks, rave stabs, glitchy accents, intense J-core energy',
}

def main():
    genre = sys.argv[1]
    desc = GENRE_DESC[genre]
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
        page = next((p for p in b.contexts[0].pages if 'suno.com' in p.url), None)
        # song page -> more menu -> remix -> cover
        page.goto(f'https://suno.com/song/{UPLOAD}', wait_until='domcontentloaded', timeout=30000)
        page.wait_for_timeout(7000)
        try:
            page.focus('button[aria-label="More menu contents"]')
            page.keyboard.press('Enter')
        except Exception:
            page.evaluate("document.querySelector('button[aria-label=\"More menu contents\"]')?.click()")
        page.wait_for_timeout(3000)
        page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],div[class*=menu] button,button')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='remix')[0]?.click()")
        page.wait_for_timeout(3000)
        page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],button,div[class*=menu] *')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='cover')[0]?.click()")
        try:
            page.wait_for_url('**/create**', timeout=20000)
        except Exception:
            pass
        page.wait_for_timeout(8000)
        # check textareas
        tas = page.evaluate("JSON.stringify(Array.from(document.querySelectorAll('textarea')).map((t,i)=>({i,ph:(t.placeholder||'').slice(0,30),ml:t.maxLength})))")
        print('textareas:', tas, flush=True)
        # inject into the maxLen=3000 textarea (song description)
        r = page.evaluate("(()=>{var ts=Array.from(document.querySelectorAll('textarea'));var t=ts.find(x=>x.maxLength===3000)||ts[2];if(!t)return 'no textarea';var ns=Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype,'value').set;ns.call(t," + json.dumps(desc) + ");var fk=Object.keys(t).find(k=>k.startsWith('__reactFiber'));var f=t[fk];var c=f;for(var i=0;i<12&&c;i++){if(i>=2&&c.memoizedProps&&typeof c.memoizedProps.onChange==='function'){c.memoizedProps.onChange({target:t});return 'fiber'+i}c=c.return}t.dispatchEvent(new Event('input',{bubbles:true}));return 'events'})()")
        print('inject:', r, flush=True)
        page.wait_for_timeout(2500)
        # VERIFY value stuck
        val = page.evaluate("(()=>{var ts=Array.from(document.querySelectorAll('textarea'));var t=ts.find(x=>x.maxLength===3000)||ts[2];return t?t.value.slice(0,50):'none'})()")
        print('VERIFIED value:', val, flush=True)
        if not val or len(val) < 10:
            print('INJECTION FAILED — retrying with native setter', flush=True)
            r2 = page.evaluate("(()=>{var ts=Array.from(document.querySelectorAll('textarea'));var t=ts.find(x=>x.maxLength===3000)||ts[2];var setter=Object.getOwnPropertyDescriptor(HTMLTextAreaElement.prototype,'value').set;setter.call(t," + json.dumps(desc) + ");t.dispatchEvent(new Event('input',{bubbles:true}));t.dispatchEvent(new Event('change',{bubbles:true}));return 'native'})()")
            page.wait_for_timeout(2000)
            val2 = page.evaluate("(()=>{var ts=Array.from(document.querySelectorAll('textarea'));var t=ts.find(x=>x.maxLength===3000)||ts[2];return t?t.value.slice(0,50):'none'})()")
            print('VERIFIED 2nd:', val2, flush=True)
        # click Create
        trig = time.strftime('%Y-%m-%dT%H:%M:%S', time.gmtime())
        page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&((x.getAttribute('aria-label')||'').toLowerCase().includes('create'))&&!/create new workspace/i.test(x.innerText||''));if(b){b.click();return 'ok'}return 'nf'})()")
        print(f'Create clicked at {trig}', flush=True)
        b.close()

if __name__ == '__main__':
    main()
