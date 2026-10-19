"""Scan all my cover clips, check full-quality via analyser, output capturable ones.
Usage: python scan_clips.py
"""
import sys, json, time, requests
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def check_quality(page, cid):
    """Return True if clip plays full-quality audio."""
    page.goto(f'https://suno.com/song/{cid}', wait_until='domcontentloaded', timeout=25000)
    page.wait_for_timeout(7000)
    page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
    page.wait_for_timeout(5000)
    js = '''async () => {
        const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
        if (!a) return {err:'no blob'};
        const Ctx = window.AudioContext || window.webkitAudioContext;
        const ac = new Ctx(); await ac.resume();
        const src = ac.createMediaElementSource(a);
        const an = ac.createAnalyser(); an.fftSize = 8192;
        src.connect(an);
        await new Promise(r => setTimeout(r, 2500));
        const fd = new Uint8Array(an.frequencyBinCount);
        an.getByteFrequencyData(fd);
        const sr = ac.sampleRate;
        let hi = 0;
        for (let i = Math.floor(1500*an.fftSize/sr); i < fd.length; i++) hi += fd[i];
        return {hi: Math.round(hi)};
    }'''
    try:
        res = page.evaluate(js)
        if isinstance(res, dict) and 'err' in res:
            return None
        return res.get('hi', 0) > 50
    except Exception:
        return None

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
    for p in list(b.contexts[0].pages):
        if 'suno.com' in p.url:
            try: p.close()
            except: pass
    time.sleep(1)
    page = b.contexts[0].new_page()
    page.goto('https://suno.com/create', wait_until='domcontentloaded', timeout=20000)
    page.wait_for_timeout(5000)
    tok = page.evaluate('async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}')
    hdr = {'Authorization': f'Bearer {tok}'}
    UPLOAD = 'd2246d83-d592-4081-89eb-218a765535a9'
    # collect all unique genre clips (newest per prompt)
    clips = {}
    for pg in range(0, 10):
        r = requests.get(f'https://studio-api-prod.suno.com/api/feed/?limit=50&page={pg}', headers=hdr, timeout=20)
        if r.status_code != 200: break
        cs = r.json() if isinstance(r.json(), list) else r.json().get('clips', [])
        if not cs: break
        for c in cs:
            if c.get('model_name')=='chirp-auk' and c.get('metadata',{}).get('cover_clip_id')==UPLOAD and c.get('status')=='complete':
                pr = c.get('metadata',{}).get('gpt_description_prompt','')
                if pr:
                    g = pr.split(',')[0].strip()[:18]
                    if g not in clips or c.get('created_at','') > clips[g]['created']:
                        clips[g] = {'id': c['id'], 'created': c.get('created_at','')}
        if len(cs) < 50: break
    print(f'found {len(clips)} genre clips to check')
    results = {}
    for g, info in sorted(clips.items()):
        q = check_quality(page, info['id'])
        status = 'FULL' if q else ('DEGRADED' if q is not None else 'ERR')
        results[g] = status
        print(f'{g:20s} {status:10s} {info["id"]}')
        page.goto('https://suno.com/create', wait_until='domcontentloaded', timeout=20000)
        page.wait_for_timeout(3000)
    print()
    print('SUMMARY:')
    for g, s in results.items():
        print(f'  {g}: {s}')
    b.close()
