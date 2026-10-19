"""Check playback spectrum of a clip to determine if it's full-quality or degraded.
Usage: python check_clip.py <full_clip_id>
"""
import sys, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def check(page, cid):
    page.goto(f'https://suno.com/song/{cid}', wait_until='domcontentloaded', timeout=25000)
    page.wait_for_timeout(5000)
    page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
    page.wait_for_timeout(6000)
    js = '''
    async () => {
        const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
        if (!a) return JSON.stringify({err:'no blob'});
        const Ctx = window.AudioContext || window.webkitAudioContext;
        const ac = new Ctx();
        const src = ac.createMediaElementSource(a);
        const an = ac.createAnalyser();
        an.fftSize = 8192;
        src.connect(an);
        await new Promise(r => setTimeout(r, 2000));
        const fd = new Uint8Array(an.frequencyBinCount);
        an.getByteFrequencyData(fd);
        const sr = ac.sampleRate;
        let hi = 0; // energy above 1kHz
        for (let i = Math.floor(1000*an.fftSize/sr); i < fd.length; i++) hi += fd[i];
        let lo = 0;
        for (let i = 0; i < Math.floor(1000*an.fftSize/sr); i++) lo += fd[i];
        return JSON.stringify({hiEnergy: Math.round(hi), loEnergy: Math.round(lo)});
    }
    '''
    res = page.evaluate(js)
    return json.loads(res)

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
    page = next((p for p in b.contexts[0].pages if 'suno.com' in p.url), None)
    for cid in sys.argv[1:]:
        try:
            r = check(page, cid)
            verdict = 'FULL-QUALITY' if r.get('hiEnergy', 0) > 100 else 'DEGRADED (lowpassed)'
            print(f'{cid[:12]}: hi={r.get("hiEnergy")} lo={r.get("loEnergy")} => {verdict}', flush=True)
        except Exception as e:
            print(f'{cid[:12]}: ERR {str(e)[:40]}', flush=True)
        # reset between checks
        page.goto('https://suno.com/library', wait_until='domcontentloaded', timeout=20000)
        page.wait_for_timeout(2000)
    b.close()
