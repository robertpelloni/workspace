"""DEFINITIVE capture: MediaRecorder for exact metadata duration. 
Proven: 221s capture of 219s clip, centroid 2899 (full quality).
Usage: python cap_final.py <clip_id> <genre>
"""
import sys, os, json, time, base64, subprocess, requests
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

FFM = r'C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe'
SUNO = 'https://studio-api-prod.suno.com'
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

def get_duration(page, hdr, cid):
    for pg in range(0, 3):
        r = requests.get(f'{SUNO}/api/feed/?limit=50&page={pg}', headers=hdr, timeout=20)
        if r.status_code != 200:
            break
        clips = r.json() if isinstance(r.json(), list) else r.json().get('clips', [])
        for c in clips:
            if c.get('id') == cid:
                return c.get('metadata', {}).get('duration') or 240
        if len(clips) < 50:
            break
    return 240

def main():
    cid = sys.argv[1]
    genre = sys.argv[2]
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp('http://127.0.0.1:9333')
        # reuse existing suno page (closing pages destabilizes the session)
        page = next((p for p in b.contexts[0].pages if 'suno.com' in p.url), None)
        if not page:
            page = b.contexts[0].new_page()
        page.goto('https://suno.com/create', wait_until='domcontentloaded', timeout=25000)
        page.wait_for_timeout(5000)
        tok = page.evaluate('async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}')
        hdr = {'Authorization': f'Bearer {tok}'}
        md_dur = get_duration(page, hdr, cid)
        print(f'[{genre}] metadata duration: {md_dur}s', flush=True)
        page.goto(f'https://suno.com/song/{cid}', wait_until='load', timeout=25000)
        page.wait_for_timeout(8000)
        page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
        page.wait_for_timeout(6000)
        record_s = md_dur + 3
        js = """async (sec) => {
            const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
            if (!a) return JSON.stringify({err:'no blob'});
            const Ctx = window.AudioContext || window.webkitAudioContext;
            const ac = new Ctx(); await ac.resume();
            const src = ac.createMediaElementSource(a);
            const dest = ac.createMediaStreamDestination();
            src.connect(dest);
            const rec = new MediaRecorder(dest.stream);
            const chunks=[]; rec.ondataavailable = e => { if(e.data&&e.data.size>0) chunks.push(e.data); };
            rec.start(2000);
            await new Promise(r => setTimeout(r, sec*1000 + 2000));
            rec.stop(); await new Promise(r => rec.onstop = r);
            const blob = new Blob(chunks,{type:'audio/webm'});
            const ab = await blob.arrayBuffer(); const bytes = new Uint8Array(ab);
            let bin=''; for(let i=0;i<bytes.length;i+=0x8000) bin+=String.fromCharCode.apply(null,bytes.subarray(i,i+0x8000));
            return JSON.stringify({size:bytes.length,b64:btoa(bin)});
        }"""
        res = page.evaluate(js, record_s)
        d = json.loads(res)
        if d.get('err'):
            print(f'[{genre}] ERR: {d["err"]}', flush=True)
        else:
            webm = f'/tmp/{genre}_final.webm'
            with open(webm, 'wb') as f:
                f.write(base64.b64decode(d['b64']))
            out = os.path.join(GEN_DIR, f'{HYMN}_10x_{genre}_A_cover.mp3')
            subprocess.run([FFM, '-y', '-loglevel', 'error', '-i', webm, '-c:a', 'libmp3lame', '-b:a', '192k', out], check=True)
            # check duration
            FFP = FFM.replace('ffmpeg.exe', 'ffprobe.exe')
            r2 = subprocess.run([FFP, '-v', 'quiet', '-show_entries', 'format=duration', '-of', 'csv=p=0', out], capture_output=True, text=True)
            try:
                dur = float(r2.stdout.strip())
            except Exception:
                dur = 0
            c = centroid(out)
            status = 'OK' if c > 2000 and abs(dur - md_dur) < 20 else ('BAD-DUR' if abs(dur - md_dur) >= 20 else 'DEGRADED')
            print(f'[{genre}] dur={dur:.0f}s centroid={c} => {status} size={os.path.getsize(out)//1024}KB', flush=True)
            os.remove(webm)
        b.close()

if __name__ == '__main__':
    main()
