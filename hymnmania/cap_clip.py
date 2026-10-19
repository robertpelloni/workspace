"""Robustly capture ONE clip's full audio. Usage: python cap_clip.py <full_clip_id> <genre>
Handles navigation races by using a dedicated page and retrying.
"""
import sys, os, json, time, base64, subprocess, tempfile, requests
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
import numpy as np
from playwright.sync_api import sync_playwright

SUNO = 'https://studio-api-prod.suno.com'
FFM = r'C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe'
GEN_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'generated')
HYMN = 'Jesus_Comes_With_Power'

def centroid_of(file):
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

def open_fresh_page(b):
    """Create a brand-new page in a way that avoids SPA navigation races."""
    page = b.contexts[0].new_page()
    page.goto('https://suno.com/song', wait_until='domcontentloaded', timeout=30000)
    return page

def play_and_record(page, cid, ms):
    """Navigate, play, record. Returns webm bytes or None."""
    page.goto(f'https://suno.com/song/{cid}', wait_until='load', timeout=30000)
    page.wait_for_timeout(6000)
    # dismiss cookies if present
    try:
        page.evaluate("Array.from(document.querySelectorAll('button')).find(b=>b.innerText.trim()==='Reject All')?.click()")
        page.wait_for_timeout(500)
    except Exception:
        pass
    # click the main track Play
    page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
    page.wait_for_timeout(6000)
    # verify blob is playing
    has = page.evaluate("!!Array.from(document.querySelectorAll('audio')).find(e=>!e.paused && (e.currentSrc||'').startsWith('blob:'))")
    if not has:
        print('  no playing blob', flush=True)
        return None
    js = """async (ms) => {
        const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
        const Ctx = window.AudioContext || window.webkitAudioContext;
        const ac = new Ctx(); await ac.resume();
        const src = ac.createMediaElementSource(a);
        const dest = ac.createMediaStreamDestination();
        src.connect(dest);
        const rec = new MediaRecorder(dest.stream);
        const chunks=[]; rec.ondataavailable = e => { if(e.data&&e.data.size>0) chunks.push(e.data); };
        rec.start(5000);
        await new Promise(r => setTimeout(r, ms));
        rec.stop(); await new Promise(r => rec.onstop = r);
        const blob = new Blob(chunks,{type:'audio/webm'});
        const ab = await blob.arrayBuffer(); const bytes = new Uint8Array(ab);
        let bin=''; for(let i=0;i<bytes.length;i+=0x8000) bin+=String.fromCharCode.apply(null,bytes.subarray(i,i+0x8000));
        return JSON.stringify({size:bytes.length,b64:btoa(bin)});
    }"""
    res = page.evaluate(js, ms)
    d = json.loads(res)
    if 'err' in d:
        print(f'  record err: {d["err"]}', flush=True)
        return None
    return base64.b64decode(d['b64'])

def main():
    cid = sys.argv[1]
    genre = sys.argv[2]
    out = os.path.join(GEN_DIR, f'{HYMN}_10x_{genre}_A_cover.mp3')
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
        # quick 8s sample first
        p1 = open_fresh_page(b)
        webm = play_and_record(p1, cid, 8000)
        if webm:
            tmp = '/tmp/_s.webm'
            with open(tmp, 'wb') as f:
                f.write(webm)
            c0 = centroid_of(tmp)
            os.remove(tmp)
            print(f'[{genre}] sample centroid={c0}', flush=True)
        try:
            p1.close()
        except Exception:
            pass
        # full record on fresh page
        p2 = open_fresh_page(b)
        webm_full = play_and_record(p2, cid, 265000)
        if webm_full:
            tmpw = out.replace('.mp3', '_t.webm')
            with open(tmpw, 'wb') as f:
                f.write(webm_full)
            subprocess.run([FFM, '-y', '-loglevel', 'error', '-i', tmpw, '-c:a', 'libmp3lame', '-b:a', '192k', out], check=True)
            os.remove(tmpw)
            c = centroid_of(out)
            print(f'[{genre}] SAVED centroid={c} {"OK" if c>1500 else "DEGRADED"} size={os.path.getsize(out)//1024}KB', flush=True)
        try:
            p2.close()
        except Exception:
            pass
        b.close()

if __name__ == '__main__':
    main()
