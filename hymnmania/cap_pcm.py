"""Capture raw PCM via getFloatTimeDomainData polling. Bypasses MediaRecorder.
Usage: python cap_pcm.py <clip_id> <genre> <seconds>
"""
import sys, os, json, time, base64, struct, subprocess, tempfile
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

FFM = r'C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe'

def centroid(file):
    import numpy as np
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
    b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
    page = next((p for p in b.contexts[0].pages if 'suno.com' in p.url), None)
    cid = sys.argv[1]
    genre = sys.argv[2]
    dur_s = int(sys.argv[3]) if len(sys.argv) > 3 else 10
    page.goto(f'https://suno.com/song/{cid}', wait_until='domcontentloaded', timeout=25000)
    page.wait_for_timeout(6000)
    page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
    page.wait_for_timeout(5000)
    # capture: use an AnalyserNode (time domain) and poll it; store into an array on window
    js = """async (sec) => {
        const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
        if (!a) return JSON.stringify({err:'no blob'});
        const Ctx = window.AudioContext || window.webkitAudioContext;
        const ac = new Ctx(); await ac.resume();
        const src = ac.createMediaElementSource(a);
        const an = ac.createAnalyser();
        an.fftSize = 2048;
        src.connect(an);
        const td = new Float32Array(an.fftSize);
        const samples = [];
        await new Promise((resolve) => {
            const int = setInterval(() => {
                an.getFloatTimeDomainData(td);
                samples.push(Array.from(td));
            }, Math.floor(1000 * an.fftSize / ac.sampleRate)); // real-time
            setTimeout(() => { clearInterval(int); resolve(); }, sec * 1000);
        });
        // flatten
        const flat = new Float32Array(samples.length * an.fftSize);
        for (let i = 0; i < samples.length; i++) flat.set(samples[i], i * an.fftSize);
        const bytes = new Uint8Array(flat.buffer);
        let bin = '';
        for (let i = 0; i < bytes.length; i += 0x8000) bin += String.fromCharCode.apply(null, bytes.subarray(i, i+0x8000));
        return JSON.stringify({n: flat.length, b64: btoa(bin)});
    }"""
    result = page.evaluate(js, dur_s)
    d = json.loads(result)
    if 'err' in d:
        print('err:', d['err'])
    else:
        import base64 as b64
        pcm = b64.b64decode(d['b64'])
        sr = 48000  # AudioContext default
        out_wav = f'/tmp/{genre}_{dur_s}s.wav'
        with open(out_wav, 'wb') as f:
            f.write(b'RIFF'); f.write(struct.pack('<I', 36 + len(pcm)))
            f.write(b'WAVEfmt '); f.write(struct.pack('<IHHIIHH', 16, 1, 1, sr, sr*2, 2, 16))
            f.write(b'data'); f.write(struct.pack('<I', len(pcm)))
            f.write(pcm)
        print(f'{genre} capture n={d["n"]} centroid:', centroid(out_wav))
    b.close()
