"""Correct ScriptProcessor capture (no double-buffer). 
Key: do NOT connect sp to destination. Only src -> sp. Capture input buffer once.
Usage: python cap_v2.py <clip_id> <genre>
"""
import sys, os, json, time, base64, subprocess
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

FFM = r'C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe'
GEN_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'generated')
HYMN = 'Jesus_Comes_With_Power'

def centroid(file):
    import numpy as np, tempfile as _tf
    tmp = _tf.mktemp(suffix='.f32')
    subprocess.run([FFM, '-y', '-loglevel', 'error', '-i', file, '-ac', '1', '-ar', '48000', '-f', 'f32le', tmp], capture_output=True)
    d = np.frombuffer(open(tmp, 'rb').read(), dtype=np.float32)
    os.remove(tmp)
    cents = []
    for i in range(0, len(d) - 2048, 2048):
        spec = np.abs(np.fft.rfft(d[i:i+2048] * np.hanning(2048)))
        fr = np.fft.rfftfreq(2048, 1/48000)
        if spec.sum() > 0:
            cents.append((spec * fr).sum() / spec.sum())
    return round(float(np.mean(cents)), 1) if cents else 0

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
    page = next((p for p in b.contexts[0].pages if 'suno.com' in p.url), None)
    if not page:
        page = b.contexts[0].new_page()
        page.goto('https://suno.com/create', wait_until='domcontentloaded', timeout=30000)
        page.wait_for_timeout(5000)
    cid = sys.argv[1]
    genre = sys.argv[2]
    page.goto(f'https://suno.com/song/{cid}', wait_until='load', timeout=25000)
    page.wait_for_timeout(8000)
    page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
    page.wait_for_timeout(6000)
    js = """async () => {
        const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
        if (!a) return JSON.stringify({err:'no blob'});
        const Ctx = window.AudioContext || window.webkitAudioContext;
        const ac = new Ctx(); await ac.resume();
        const src = ac.createMediaElementSource(a);
        const sp = ac.createScriptProcessor(4096, 1, 1);
        // ONLY src -> sp. NO sp -> destination (prevents double routing)
        src.connect(sp);
        const all = [];
        const dur = a.duration || 240;
        await new Promise((resolve) => {
            sp.onaudioprocess = (e) => {
                const d = e.inputBuffer.getChannelData(0);
                all.push(Array.from(d));
                if (a.currentTime >= dur - 1) { sp.onaudioprocess = null; resolve(); }
            };
            setTimeout(() => { sp.onaudioprocess = null; resolve(); }, (dur + 20) * 1000);
        });
        const flat = new Float32Array(all.length * 4096);
        for (let i = 0; i < all.length; i++) flat.set(all[i], i * 4096);
        const bytes = new Uint8Array(flat.buffer);
        let bin = '';
        for (let i = 0; i < bytes.length; i += 0x8000) bin += String.fromCharCode.apply(null, bytes.subarray(i, i+0x8000));
        return JSON.stringify({n: flat.length, sr: ac.sampleRate, dur: a.duration, b64: btoa(bin)});
    }"""
    result = page.evaluate(js)
    d = json.loads(result)
    if d.get('err'):
        print('err:', d['err'])
    else:
        import base64 as b64
        pcm = b64.b64decode(d['b64'])
        sr = d['sr']
        n = d['n']
        actual = n / sr
        print(f'captured {n} floats = {actual:.0f}s (element dur {d["dur"]:.0f}s)', flush=True)
        raw = f'/tmp/{genre}_v2.f32'
        with open(raw, 'wb') as f:
            f.write(pcm)
        out = os.path.join(GEN_DIR, f'{HYMN}_10x_{genre}_A_cover.mp3')
        subprocess.run([FFM, '-y', '-loglevel', 'error', '-f', 'f32le', '-ar', str(sr), '-ac', '1', '-i', raw,
                        '-c:a', 'libmp3lame', '-b:a', '192k', out], check=True)
        os.remove(raw)
        c = centroid(out)
        print(f'{genre}: SAVED centroid={c} size={os.path.getsize(out)//1024}KB', flush=True)
    b.close()
