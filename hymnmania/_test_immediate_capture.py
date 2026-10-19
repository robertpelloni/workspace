"""Generate a cover and capture it IMMEDIATELY (within seconds of completion).
Tests whether fresh clips stream full quality before Suno's DRM degrades them.
"""
import sys, json, time, base64, os, subprocess, tempfile
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
import numpy as np, requests
from playwright.sync_api import sync_playwright

FFM = 'C:/Users/jakeg/AppData/Local/Microsoft/WinGet/Packages/Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe/ffmpeg-9.0.1-full_build/bin/ffmpeg.exe'
SUNO = 'https://studio-api-prod.suno.com'
UPLOAD = 'd2246d83-d592-4081-89eb-218a765535a9'

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
    tok = page.evaluate('async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}')
    hdr = {'Authorization': f'Bearer {tok}'}

    # 1. Trigger cover (dubstep)
    page.goto(f'https://suno.com/song/{UPLOAD}', wait_until='domcontentloaded', timeout=30000)
    page.wait_for_timeout(8000)
    page.focus('button[aria-label="More menu contents"]')
    page.keyboard.press('Enter')
    page.wait_for_timeout(2500)
    page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],button,div[class*=menu] *')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='remix')[0]?.click()")
    page.wait_for_timeout(2500)
    page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],button,div[class*=menu] *')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='cover')[0]?.click()")
    try:
        page.wait_for_url('**/create**', timeout=20000)
    except Exception:
        pass
    page.wait_for_timeout(6000)
    desc = 'dubstep, massive LFO wobble bass drops, half-time 140 BPM drums, growling midrange basses, festival bass'
    page.evaluate("(()=>{var t=document.querySelectorAll('textarea')[2];if(!t)return;var ns=Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype,'value').set;ns.call(t," + json.dumps(desc) + ");var fk=Object.keys(t).find(k=>k.startsWith('__reactFiber'));var f=t[fk];var c=f;for(var i=0;i<10&&c;i++){if(i>=2&&c.memoizedProps&&typeof c.memoizedProps.onChange==='function'){c.memoizedProps.onChange({target:t});return}c=c.return}})()")
    page.wait_for_timeout(1500)
    page.evaluate("Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&((x.getAttribute('aria-label')||'').toLowerCase().includes('create'))&&!/create new workspace/i.test(x.innerText||''))?.click()")
    print('Create clicked', flush=True)

    # 2. Poll every 3s for new clip; as soon as status=complete, jump to song page and capture FAST
    seen = set()
    for i in range(120):
        time.sleep(3)
        try:
            r = requests.get(f'{SUNO}/api/feed/?limit=10', headers=hdr, timeout=20)
            if r.status_code != 200:
                continue
            clips = r.json() if isinstance(r.json(), list) else r.json().get('clips', [])
            for c in clips:
                cid = c.get('id')
                if cid in seen or c.get('model_name') != 'chirp-auk':
                    continue
                if c.get('metadata', {}).get('cover_clip_id') != UPLOAD:
                    continue
                seen.add(cid)
                # only care about brand new ones (created just now)
                created = c.get('created_at', '')
                print(f'[{i*3}s] clip {cid[:12]} status={c.get("status")} created={created}', flush=True)
                if c.get('status') == 'complete':
                    # CAPTURE IMMEDIATELY
                    page.goto(f'https://suno.com/song/{cid}', wait_until='domcontentloaded', timeout=20000)
                    page.wait_for_timeout(4000)
                    page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
                    page.wait_for_timeout(4000)
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
                        const rec = new MediaRecorder(dest.stream);
                        const chunks = [];
                        rec.ondataavailable = e => { if (e.data && e.data.size > 0) chunks.push(e.data); };
                        rec.start(1000);
                        await new Promise(r => setTimeout(r, 12000));
                        rec.stop();
                        await new Promise(r => rec.onstop = r);
                        const blob = new Blob(chunks, {type:'audio/webm'});
                        const ab = await blob.arrayBuffer();
                        const bytes = new Uint8Array(ab);
                        let bin='';
                        for (let i=0;i<bytes.length;i+=0x8000) bin+=String.fromCharCode.apply(null,bytes.subarray(i,i+0x8000));
                        return JSON.stringify({size:bytes.length,b64:btoa(bin)});
                    }
                    """
                    res = page.evaluate(js)
                    dd = json.loads(res)
                    if 'err' not in dd:
                        webm = '/tmp/_immediate_capture.webm'
                        with open(webm, 'wb') as f:
                            f.write(base64.b64decode(dd['b64']))
                        print('IMMEDIATE capture centroid:', centroid(webm), flush=True)
                        print('(real cover ~2000+, degraded ~300)', flush=True)
                    else:
                        print('capture err:', dd['err'], flush=True)
                    b.close()
                    sys.exit(0)
        except Exception as e:
            print('poll err:', str(e)[:50], flush=True)
    b.close()
