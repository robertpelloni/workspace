import sys, json, time, base64, os, subprocess, tempfile
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
import numpy as np
from playwright.sync_api import sync_playwright

FFM = 'C:/Users/jakeg/AppData/Local/Microsoft/WinGet/Packages/Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe/ffmpeg-9.0.1-full_build/bin/ffmpeg.exe'

def centroid(webm):
    tmp = tempfile.mktemp(suffix='.f32')
    subprocess.run([FFM, '-y', '-loglevel', 'error', '-i', webm, '-ac', '1', '-ar', '44100', '-f', 'f32le', tmp], capture_output=True)
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
    # Play e5069135 (morning-good clip) and record 3 consecutive 10s segments
    # to check if quality changes over time
    page.goto('https://suno.com/song/e5069135-c529-405c-8663-2f0e480ae55c', wait_until='domcontentloaded', timeout=30000)
    page.wait_for_timeout(8000)
    page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
    page.wait_for_timeout(5000)
    # record 3 segments at t=0, t=15, t=30 via seeking
    results = []
    for seg, seek in [(1, 0), (2, 15), (3, 30)]:
        js = """
        async (seekTo) => {
            const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
            if (!a) return JSON.stringify({err:'no blob'});
            a.currentTime = seekTo;
            await a.play();
            const Ctx = window.AudioContext || window.webkitAudioContext;
            const ac = new Ctx();
            await ac.resume();
            const src = ac.createMediaElementSource(a);
            const dest = ac.createMediaStreamDestination();
            src.connect(dest);
            const rec = new MediaRecorder(dest.stream);
            const chunks = [];
            rec.ondataavailable = e => { if (e.data && e.data.size > 0) chunks.push(e.data); };
            rec.start(1000);
            await new Promise(r => setTimeout(r, 10000));
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
        result = page.evaluate(js, seek)
        d = json.loads(result)
        if 'err' in d:
            results.append('ERR: ' + d['err'])
            # reload page (MediaElementSource can only attach once)
            page.reload(wait_until='domcontentloaded')
            page.wait_for_timeout(8000)
            page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
            page.wait_for_timeout(5000)
        else:
            webm = f'/tmp/_seg{seg}.webm'
            with open(webm, 'wb') as f:
                f.write(base64.b64decode(d['b64']))
            results.append(f'seg{seg}@{seek}s centroid=' + str(centroid(webm)))
            # reload for next segment
            page.reload(wait_until='domcontentloaded')
            page.wait_for_timeout(8000)
            page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
            page.wait_for_timeout(5000)
    for r in results:
        print(r)
    b.close()
