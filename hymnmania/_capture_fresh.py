import sys, json, time, base64, os, subprocess, tempfile
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
import numpy as np
from playwright.sync_api import sync_playwright

FFM = 'C:/Users/jakeg/AppData/Local/Microsoft/WinGet/Packages/Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe/ffmpeg-9.0.1-full_build/bin/ffmpeg.exe'

def analyze(webm):
    tmp = tempfile.mktemp(suffix='.f32')
    subprocess.run([FFM, '-y', '-loglevel', 'error', '-i', webm, '-ac', '1', '-ar', '44100', '-f', 'f32le', tmp], capture_output=True)
    d = np.frombuffer(open(tmp, 'rb').read(), dtype=np.float32)
    os.remove(tmp)
    rms = np.sqrt(np.mean(d**2))
    cents = []
    for i in range(0, len(d) - 2048, 2048):
        spec = np.abs(np.fft.rfft(d[i:i+2048] * np.hanning(2048)))
        fr = np.fft.rfftfreq(2048, 1/44100)
        if spec.sum() > 0:
            cents.append((spec * fr).sum() / spec.sum())
    return {'rms': round(float(rms), 4), 'centroid': round(float(np.mean(cents)), 1) if cents else 0, 'n': len(d)}

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
    page = next((p for p in b.contexts[0].pages if 'suno.com' in p.url), None)
    page.goto('https://suno.com/song/5cc36929-3c64-4a9d-b1df-468ef9552f85', wait_until='domcontentloaded', timeout=30000)
    page.wait_for_timeout(8000)
    page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
    page.wait_for_timeout(6000)
    # capture 20s
    js = """
    async () => {
        const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
        if (!a) return JSON.stringify({err:'no blob'});
        const Ctx = window.AudioContext || window.webkitAudioContext;
        const ac = new Ctx();
        await ac.resume();
        const src = ac.createMediaElementSource(a);
        const dest = ac.createMediaStreamDestination();
        src.connect(dest);
        const rec = new MediaRecorder(dest.stream, {mimeType: 'audio/webm;codecs=opus', audioBitsPerSecond: 256000});
        const chunks = [];
        rec.ondataavailable = e => { if (e.data && e.data.size > 0) chunks.push(e.data); };
        rec.start(1000);
        await new Promise(r => setTimeout(r, 20000));
        rec.stop();
        await new Promise(r => rec.onstop = r);
        const blob = new Blob(chunks, {type: 'audio/webm'});
        const ab = await blob.arrayBuffer();
        const bytes = new Uint8Array(ab);
        let bin = '';
        for (let i = 0; i < bytes.length; i += 0x8000) bin += String.fromCharCode.apply(null, bytes.subarray(i, i + 0x8000));
        return JSON.stringify({size: bytes.length, b64: btoa(bin)});
    }
    """
    result = page.evaluate(js)
    d = json.loads(result)
    webm = '/tmp/_fresh_chiptune_20s.webm'
    with open(webm, 'wb') as f:
        f.write(base64.b64decode(d['b64']))
    print('fresh chiptune 20s capture:', analyze(webm))
    print('(real cover target: rms>0.05, centroid>1000 | sine: rms<0.05 or centroid<500)')
    b.close()
