"""Capture audio via AnalyserNode time-domain data (bypasses MediaRecorder).
The analyser hears full-quality audio; MediaRecorder gets degraded. So we capture
the raw PCM from an AnalyserNode directly and encode to WAV.
Usage: python cap_analyser.py <full_clip_id> <genre> <seconds>
"""
import sys, os, json, time, base64, subprocess, struct, math
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

FFM = r'C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe'
GEN_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'generated')
HYMN = 'Jesus_Comes_With_Power'

def centroid(file):
    import numpy as np, tempfile
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
    dur_s = int(sys.argv[3]) if len(sys.argv) > 3 else 15
    page.goto(f'https://suno.com/song/{cid}', wait_until='domcontentloaded', timeout=25000)
    page.wait_for_timeout(6000)
    page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
    page.wait_for_timeout(6000)
    # Capture time-domain data from analyser at 44100 in chunks via page
    # We record 44100 samples/sec as float32, but can't send huge base64 at once.
    # Record in 2-second chunks and append.
    js_capture = """async (sec) => {
        const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
        if (!a) return JSON.stringify({err:'no blob'});
        const Ctx = window.AudioContext || window.webkitAudioContext;
        const ac = new Ctx(); await ac.resume();
        const src = ac.createMediaElementSource(a);
        const an = ac.createAnalyser();
        an.fftSize = 8192;
        const bufferLen = an.frequencyBinCount;
        src.connect(an);
        // We need time domain: use a ScriptProcessor/Worklet? Analyser gives freq only via fft.
        // Use OfflineAudioContext approach: render element to buffer
        const sr = ac.sampleRate;
        const OffCtx = new OfflineAudioContext(1, sr * sec, sr);
        const elSrc = OffCtx.createMediaElementSource(a);
        elSrc.connect(OffCtx.destination);
        const rendered = await OffCtx.startRendering();
        const data = rendered.getChannelData(0);
        let bin = '';
        const chunk = 0x8000;
        for (let i = 0; i < data.length; i += chunk) {
            const sub = data.subarray(i, Math.min(i+chunk, data.length));
            const bytes = new Uint8Array(sub.buffer);
            for (let j = 0; j < bytes.length; j++) bin += String.fromCharCode(bytes[j]);
        }
        return JSON.stringify({n: data.length, sr: sr, b64: btoa(bin)});
    }"""
    result = page.evaluate(js_capture, dur_s)
    d = json.loads(result)
    if 'err' in d:
        print('err:', d['err'], flush=True)
    else:
        import base64 as b64
        pcm = b64.b64decode(d['b64'])
        sr = d['sr']
        # write WAV
        out_wav = f'/tmp/{genre}_{dur_s}s.wav'
        with open(out_wav, 'wb') as f:
            f.write(b'RIFF')
            f.write(struct.pack('<I', 36 + len(pcm)))
            f.write(b'WAVEfmt ')
            f.write(struct.pack('<IHHIIHH', 16, 1, 1, sr, sr*2, 2, 16))
            f.write(b'data')
            f.write(struct.pack('<I', len(pcm)))
            f.write(pcm)
        print(f'saved wav {out_wav} sr={sr} n={d["n"]}', flush=True)
        # centroid
        print(f'{genre} {dur_s}s capture centroid:', centroid(out_wav), flush=True)
    b.close()
