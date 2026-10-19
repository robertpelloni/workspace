"""Careful single-genre flow with step verification. Usage: python careful_gen.py <genre>"""
import sys, os, json, time, base64, subprocess, tempfile, requests
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

SUNO = 'https://studio-api-prod.suno.com'
FFM = r'C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe'
UPLOAD = 'd2246d83-d592-4081-89eb-218a765535a9'
GEN_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'generated')

GENRE_DESC = {
    'chiptune': 'chiptune, 8-bit square wave leads, arpeggios, triangle bass, noise percussion, retro video game soundtrack energy',
    'drum_and_bass': 'drum and bass, fast 174 BPM breakbeats, rolling sub-bass, reese bass swells, chopped breaks, high-energy syncopated drum work',
    'gabba': 'gabba hardcore, relentlessly distorted kick drums at 190 BPM, saturated low end, aggressive rave atmosphere, industrial hardcore energy',
    'dubstep': 'brostep dubstep, massive LFO wobble bass drops, half-time 140 BPM drums, growling midrange basses, festival-ready bass music',
    'synthwave': 'synthwave, warm analog polysynths, pulsing sidechained bassline, 100-110 BPM neon-drenched retro-future groove, 1980s nostalgia',
    'japanese_hardcore_techno': 'japanese hardcore techno, 180-190 BPM distorted kicks, rave stabs, glitchy accents, intense J-core energy',
}

def centroid_of(file):
    tmp = tempfile.mktemp(suffix='.f32')
    subprocess.run([FFM, '-y', '-loglevel', 'error', '-i', file, '-ac', '1', '-ar', '44100', '-f', 'f32le', tmp], capture_output=True)
    d = np.frombuffer(open(tmp, 'rb').read(), dtype=np.float32)
    os.remove(tmp)
    cents = []
    for i in range(0, len(d) - 2048, 2048):
        spec = np.abs(np.fft.rfft(d[i:i+2048] * np.hanning(2048)))
        fr = np.fft.rfftfreq(2048, 1/44100)
        if spec.sum() > 0:
            cents.append((spec * fr).sum() / spec.sum())
    return round(float(np.mean(cents)), 1) if cents else 0

with sync_playwright() as pw:
    import numpy as np
    b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
    # close all suno pages, open ONE clean
    for p in list(b.contexts[0].pages):
        if 'suno.com' in p.url:
            try: p.close()
            except: pass
    time.sleep(2)
    page = b.contexts[0].new_page()
    genre = sys.argv[1]
    print(f'=== {genre} ===', flush=True)

    # 1. Open upload song page, More -> Remix -> Cover
    page.goto(f'https://suno.com/song/{UPLOAD}', wait_until='domcontentloaded', timeout=30000)
    page.wait_for_timeout(8000)
    try:
        page.focus('button[aria-label="More menu contents"]')
        page.keyboard.press('Enter')
    except Exception as e:
        print('more menu focus err', str(e)[:40], flush=True)
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
    print('URL:', page.url[:50], flush=True)

    # 2. Find and fill the song description textarea (maxLength 3000)
    tas = json.loads(page.evaluate("JSON.stringify(Array.from(document.querySelectorAll('textarea')).map((t,i)=>({i,ph:(t.placeholder||'').slice(0,40),ml:t.maxLength})))"))
    print('textareas:', tas, flush=True)
    desc_i = next((t['i'] for t in tas if t['ml'] == 3000), None)
    if desc_i is None:
        desc_i = next((t['i'] for t in tas if 'describe' in t['ph'].lower() or 'song' in t['ph'].lower()), 2 if len(tas) > 2 else None)
    print('filling textarea', desc_i, flush=True)
    # native React setter
    r = page.evaluate("(()=>{var i=" + str(desc_i) + ";var ts=document.querySelectorAll('textarea');var t=ts[i];if(!t)return 'nf';var setter=Object.getOwnPropertyDescriptor(HTMLTextAreaElement.prototype,'value').set;setter.call(t," + json.dumps(GENRE_DESC[genre]) + ");t.dispatchEvent(new Event('input',{bubbles:true}));t.dispatchEvent(new Event('change',{bubbles:true}));return 'set'})()")
    print('set:', r, flush=True)
    page.wait_for_timeout(3000)
    val = page.evaluate("(()=>{var ts=document.querySelectorAll('textarea');var t=ts[" + str(desc_i) + "];return t?t.value.slice(0,40):'none'})()")
    print('VERIFIED value:', val, flush=True)
    # 3. ensure Instrumental
    page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button,[role=switch],label')).find(x=>x.offsetParent&&/instrumental/i.test(x.innerText||x.getAttribute('aria-label')||''));if(b&&b.getAttribute('aria-pressed')!=='true'){b.click()}})()")
    page.wait_for_timeout(2000)
    # 4. Create
    trig = time.strftime('%Y-%m-%dT%H:%M:%S', time.gmtime())
    page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&((x.getAttribute('aria-label')||'').toLowerCase().includes('create'))&&!/create new workspace/i.test(x.innerText||''));if(b){b.click();return 'ok'}return 'nf'})()")
    print('Create at', trig, flush=True)
    b.close()
