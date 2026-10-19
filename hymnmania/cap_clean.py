"""Clean ScriptProcessor capture — no double-buffer. Usage: python cap_clean.py <clip_id> <genre> [seconds]
Captures exactly once per audio buffer using onaudioprocess with 1 input channel.
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
    b = pw.chromium.connect_over_cdp('http://127.0.0.1:9333')
    page = next((p for p in b.contexts[0].pages if 'suno.com' in p.url), None)
    cid = sys.argv[1]
    genre = sys.argv[2]
    total_s = int(sys.argv[3]) if len(sys.argv) > 3 else 200
    page.goto(f'https://suno.com/song/{cid}', wait_until='domcontentloaded', timeout=25000)
    page.wait_for_timeout(6000)
    page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
    page.wait_for_timeout(5000)
    # record elapsed via audio element currentTime to stop at correct duration
    js = """async (maxSec) => {
        const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
        if (!a) return JSON.stringify({err:'no blob'});
        const Ctx = window.AudioContext || window.webkitAudioContext;
        const ac = new Ctx(); await ac.resume();
        const src = ac.createMediaElementSource(a);
        const sp = ac.createScriptProcessor(2048, 1, 1);
        src.connect(sp);
        sp.connect(ac.destination);
        const BUF = 2048;
        const all = [];
        await new Promise((resolve) => {
            sp.onaudioprocess = (e) => {
                const d = e.inputBuffer.getChannelData(0);
                all.push(Array.from(d));
                // stop after duration
                if (a.currentTime >= Math.min(maxSec, a.duration - 1) && a.currentTime > 5) {
                    sp.onaudioprocess = null;
                    resolve();
                }
            };
            // safety timeout
            setTimeout(() => { sp.onaudioprocess = null; resolve(); }, (maxSec + 15) * 1000);
        });
        const total = all.length * BUF;
        const flat = new Float32Array(total);
        for (let i = 0; i < all.length; i++) flat.set(all[i], i * BUF);
        const bytes = new Uint8Array(flat.buffer);
        let bin = '';
        for (let i = 0; i < bytes.length; i += 0x8000) bin += String.fromCharCode.apply(null, bytes.subarray(i, i+0x8000));
        return JSON.stringify({n: flat.length, dur: a.duration, ct: a.currentTime, b64: btoa(bin)});
    }"""
    result = page.evaluate(js, total_s)
    d = json.loads(result)
    if 'err' in d:
        print('err:', d['err'], flush=True)
    else:
        import base64 as b64
        sr = 48000
        pcm = b64.b64decode(d['b64'])
        n_floats = d['n']
        actual = n_floats / sr
        print(f'captured {n_floats} floats = {actual:.0f}s | element dur={d["dur"]:.0f}s stopped at ct={d["ct"]:.0f}s', flush=True)
        out_mp3 = os.path.join(GEN_DIR, f'{HYMN}_10x_{genre}_A_cover.mp3')
        # feed raw float32 directly to ffmpeg (no WAV wrapper issues)
        raw = '/tmp/_raw.f32'
        with open(raw, 'wb') as f:
            f.write(pcm)
        subprocess.run([FFM, '-y', '-loglevel', 'error', '-f', 'f32le', '-ar', str(sr), '-ac', '1', '-i', raw,
                        '-c:a', 'libmp3lame', '-b:a', '192k', out_mp3], check=True)
        os.remove(raw)
        print(f'{genre} centroid:', centroid(out_mp3), '| size', os.path.getsize(out_mp3)//1024, 'KB', flush=True)
    b.close()
