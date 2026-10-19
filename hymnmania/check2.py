"""Robust play + spectrum check for a clip. Usage: python check2.py <clip_id>"""
import sys, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp('http://127.0.0.1:9333')
    page = next((p for p in b.contexts[0].pages if 'suno.com' in p.url), None)
    cid = sys.argv[1]
    page.goto(f'https://suno.com/song/{cid}', wait_until='domcontentloaded', timeout=25000)
    page.wait_for_timeout(7000)
    # try multiple play strategies
    plays = [
        "Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()",
        "Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play')[0]?.click()",
        "Array.from(document.querySelectorAll('[aria-label*=play i],[role=button]')).filter(b=>b.offsetParent).slice(-5).forEach(b=>b.click())",
    ]
    for i, p in enumerate(plays):
        try:
            page.evaluate(p)
        except Exception:
            pass
        page.wait_for_timeout(3000)
        has = page.evaluate("!!Array.from(document.querySelectorAll('audio')).find(e=>!e.paused && (e.currentSrc||'').startsWith('blob:'))")
        if has:
            print(f'play strategy {i} worked', flush=True)
            break
    page.wait_for_timeout(3000)
    aus = page.evaluate("JSON.stringify(Array.from(document.querySelectorAll('audio')).map((a,i)=>({i,src:(a.currentSrc||'').slice(0,45),paused:a.paused,ct:Math.round(a.currentTime)})))")
    print('audio:', aus, flush=True)
    # spectrum via analyser
    js = '''
    async () => {
        const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
        if (!a) return JSON.stringify({err:'no blob'});
        const Ctx = window.AudioContext || window.webkitAudioContext;
        const ac = new Ctx(); await ac.resume();
        const src = ac.createMediaElementSource(a);
        const an = ac.createAnalyser(); an.fftSize = 8192;
        src.connect(an);
        await new Promise(r => setTimeout(r, 1500));
        const fd = new Uint8Array(an.frequencyBinCount);
        an.getByteFrequencyData(fd);
        const sr = ac.sampleRate;
        let hi = 0;
        for (let i = Math.floor(1000*an.fftSize/sr); i < fd.length; i++) hi += fd[i];
        let lo = 0;
        for (let i = 0; i < Math.floor(1000*an.fftSize/sr); i++) lo += fd[i];
        return JSON.stringify({hi: Math.round(hi), lo: Math.round(lo), sr});
    }
    '''
    res = page.evaluate(js)
    print('spectrum:', res, flush=True)
    b.close()
