"""Full-song capture via AnalyserNode PCM (bypasses MediaRecorder degradation).
Captures in 25-second chunks, appends to one big float32 buffer on the page,
returns all at the end. Usage: python cap_pcm_full.py <clip_id> <genre> [seconds]
"""
import sys, os, json, time, base64, struct, subprocess, tempfile
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

FFM = r'C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe'
GEN_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'generated')
HYMN = 'Jesus_Comes_With_Power'

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

def capture_chunk(page, an_fft, ms):
    """Capture one time segment. Returns list of sample arrays (as page-side flat list)."""
    pass

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
    page = next((p for p in b.contexts[0].pages if 'suno.com' in p.url), None)
    cid = sys.argv[1]
    genre = sys.argv[2]
    total_s = int(sys.argv[3]) if len(sys.argv) > 3 else 250
    page.goto(f'https://suno.com/song/{cid}', wait_until='domcontentloaded', timeout=25000)
    page.wait_for_timeout(6000)
    page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
    page.wait_for_timeout(5000)
    # Capture the full duration in one page-side run, buffering chunks and encoding progressively.
    # Return in multiple result pages would lose data; instead encode every 10s chunk to b64 list.
    js = """async (totalSec) => {
        const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
        if (!a) return JSON.stringify({err:'no blob'});
        const Ctx = window.AudioContext || window.webkitAudioContext;
        const ac = new Ctx(); await ac.resume();
        const src = ac.createMediaElementSource(a);
        const an = ac.createAnalyser();
        an.fftSize = 2048;
        src.connect(an);
        const td = new Float32Array(an.fftSize);
        const CHUNK_SEC = 10;
        const results = [];
        for (let seg = 0; seg < totalSec; seg += CHUNK_SEC) {
            const samples = [];
            const segMs = Math.min(CHUNK_SEC, totalSec - seg) * 1000;
            await new Promise((resolve) => {
                const int = setInterval(() => {
                    an.getFloatTimeDomainData(td);
                    samples.push(Array.from(td));
                }, 25); // ~40fps * 2048 = ~80k samples/sec... too much, throttle
                setTimeout(() => { clearInterval(int); resolve(); }, segMs);
            });
            const flat = new Float32Array(samples.length * an.fftSize);
            for (let i = 0; i < samples.length; i++) flat.set(samples[i], i * an.fftSize);
            const bytes = new Uint8Array(flat.buffer);
            let bin = '';
            for (let i = 0; i < bytes.length; i += 0x8000) bin += String.fromCharCode.apply(null, bytes.subarray(i, i+0x8000));
            results.push(btoa(bin));
            if (seg + CHUNK_SEC >= totalSec) break;
        }
        return JSON.stringify({chunks: results, perChunk: an.fftSize});
    }"""
    result = page.evaluate(js, total_s)
    d = json.loads(result)
    if 'err' in d:
        print('err:', d['err'], flush=True)
    else:
        import base64 as b64
        sr = 48000
        all_bytes = b''.join(b64.b64decode(c) for c in d['chunks'])
        # count samples
        n_floats = len(all_bytes) // 4
        print(f'captured {n_floats} floats (~{n_floats/sr:.0f}s at {sr}Hz)', flush=True)
        out_wav = f'/tmp/{genre}_full.wav'
        with open(out_wav, 'wb') as f:
            f.write(b'RIFF'); f.write(struct.pack('<I', 36 + len(all_bytes)))
            f.write(b'WAVEfmt '); f.write(struct.pack('<IHHIIHH', 16, 1, 1, sr, sr*2, 2, 16))
            f.write(b'data'); f.write(struct.pack('<I', len(all_bytes)))
            f.write(all_bytes)
        print(f'{genre} full capture centroid:', centroid(out_wav), flush=True)
        # convert to mp3
        out_mp3 = os.path.join(GEN_DIR, f'{HYMN}_10x_{genre}_A_cover.mp3')
        subprocess.run([FFM, '-y', '-loglevel', 'error', '-i', out_wav, '-c:a', 'libmp3lame', '-b:a', '192k', out_mp3], check=True)
        print(f'saved {out_mp3} ({os.path.getsize(out_mp3)//1024}KB)', flush=True)
    b.close()
