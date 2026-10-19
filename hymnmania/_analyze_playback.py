import sys, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
    page = next((p for p in b.contexts[0].pages if 'suno.com' in p.url), None)
    # fresh page load to reset MediaElementSource
    page.goto('https://suno.com/song/e5069135-c529-405c-8663-2f0e480ae55c', wait_until='domcontentloaded', timeout=30000)
    page.wait_for_timeout(8000)
    page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
    page.wait_for_timeout(6000)
    js = """
    async () => {
        const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
        if (!a) return JSON.stringify({err:'no blob'});
        const Ctx = window.AudioContext || window.webkitAudioContext;
        const ac = new Ctx();
        const src = ac.createMediaElementSource(a);
        const analyser = ac.createAnalyser();
        analyser.fftSize = 8192;
        src.connect(analyser);
        await new Promise(r => setTimeout(r, 2000));
        const freqData = new Uint8Array(analyser.frequencyBinCount);
        analyser.getByteFrequencyData(freqData);
        const sr = 22050;
        const bands = [[0,100],[100,300],[300,1000],[1000,3000],[3000,8000],[8000,20000]];
        const out = [];
        for (const bl of bands) {
            let sum = 0;
            const lo = bl[0], hi = bl[1];
            for (let i = Math.floor(lo*sr/analyser.fftSize); i < Math.floor(hi*sr/analyser.fftSize); i++) sum += freqData[i];
            out.push(lo + '-' + hi + 'Hz:' + Math.round(sum));
        }
        const total = out.reduce((s,x)=>s,0);
        return JSON.stringify({bands: out});
    }
    """
    result = page.evaluate(js)
    print('spectrum bands:', result)
    b.close()
