"""Capture ONE genre cover fresh (generate -> verify -> full record).
Usage: python capture_one.py <genre>
"""
import sys, os, json, time, base64, subprocess, tempfile, requests
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
import numpy as np
from playwright.sync_api import sync_playwright

SUNO = 'https://studio-api-prod.suno.com'
FFM = r'C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe'
GEN_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'generated')
UPLOAD = 'd2246d83-d592-4081-89eb-218a765535a9'
HYMN = 'Jesus_Comes_With_Power'

GENRE_DESC = {
    'psytrance': 'full-on psytrance, driving 145 BPM four-on-the-floor kick, rolling offbeat bass, hypnotic acid leads, psychedelic arpeggios, euphoric drops, festival-ready trance journey',
    'deep_house': 'deep house, warm analog chords, rolling syncopated bassline, four-on-the-floor kick at 122 BPM, hypnotic groove, soulful late-night warehouse feel',
    'drum_and_bass': 'drum and bass, fast 174 BPM breakbeats, rolling sub-bass, reese bass swells, chopped breaks, high-energy syncopated drum work',
    'gabba': 'gabba hardcore, relentlessly distorted kick drums at 190 BPM, saturated low end, aggressive rave atmosphere, industrial hardcore energy',
    'dubstep': 'brostep dubstep, massive LFO wobble bass drops, half-time 140 BPM drums, growling midrange basses, festival-ready bass music',
    'chiptune': 'chiptune, 8-bit square wave leads, arpeggios, triangle bass, noise percussion, retro video game soundtrack energy',
    'synthwave': 'synthwave, warm analog polysynths, pulsing sidechained bassline, 100-110 BPM neon-drenched retro-future groove, 1980s nostalgia',
    'hardstyle': 'hardstyle trance, pounding distorted kicks at 150 BPM, supersaw leads, euphoric melodies, festival-ready raw energy',
    'detroit_techno': 'detroit techno, analog synth stacks, hypnotic machine grooves, 132 BPM, late-night warehouse minimalism, deep soulful tension',
    'detroit_house': 'detroit house, deep Motor City grooves, soulful chords, rolling bass, 124 BPM, warm underground warehouse sound',
    'japanese_hardcore_techno': 'japanese hardcore techno, 180-190 BPM distorted kicks, rave stabs, glitchy accents, intense J-core energy',
}

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

def get_page(b):
    page = next((p for p in b.contexts[0].pages if 'suno.com' in p.url), None)
    if not page:
        page = b.contexts[0].new_page()
        page.goto('https://suno.com/create', wait_until='domcontentloaded', timeout=30000)
        page.wait_for_timeout(8000)
    return page

def record(page, ms):
    """Record from playing audio element. Returns webm bytes."""
    js = """async (ms) => {
        const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
        if (!a) return JSON.stringify({err:'no blob'});
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
        print('  record err:', d['err'], flush=True)
        return None
    return base64.b64decode(d['b64'])

def play_clip(page, cid, hard=False):
    if hard:
        # hard reload to fully reset audio pipeline
        try:
            page.goto('about:blank', wait_until='domcontentloaded', timeout=10000)
        except Exception:
            pass
        time.sleep(1)
    page.goto(f'https://suno.com/song/{cid}', wait_until='domcontentloaded', timeout=25000)
    page.wait_for_timeout(5000)
    page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
    page.wait_for_timeout(5000)

def main():
    genre = sys.argv[1]
    want = GENRE_DESC[genre][:30]
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
        page = get_page(b)
        tok = page.evaluate('async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}')
        hdr = {'Authorization': f'Bearer {tok}'}

        # 1. Trigger cover
        page.goto(f'https://suno.com/song/{UPLOAD}', wait_until='domcontentloaded', timeout=30000)
        page.wait_for_timeout(7000)
        try:
            page.focus('button[aria-label="More menu contents"]')
            page.keyboard.press('Enter')
        except Exception:
            page.evaluate("document.querySelector('button[aria-label=\"More menu contents\"]')?.click()")
        page.wait_for_timeout(2500)
        page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],div[class*=menu] button,button')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='remix')[0]?.click()")
        page.wait_for_timeout(2500)
        page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],button,div[class*=menu] *')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='cover')[0]?.click()")
        try:
            page.wait_for_url('**/create**', timeout=20000)
        except Exception:
            pass
        page.wait_for_timeout(6000)
        page.evaluate("(()=>{var t=document.querySelectorAll('textarea')[2];if(!t)return;var ns=Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype,'value').set;ns.call(t," + json.dumps(GENRE_DESC[genre]) + ");var fk=Object.keys(t).find(k=>k.startsWith('__reactFiber'));var f=t[fk];var c=f;for(var i=0;i<10&&c;i++){if(i>=2&&c.memoizedProps&&typeof c.memoizedProps.onChange==='function'){c.memoizedProps.onChange({target:t});return}c=c.return}})()")
        page.wait_for_timeout(1500)
        trig = time.strftime('%Y-%m-%dT%H:%M:%S', time.gmtime())
        page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&((x.getAttribute('aria-label')||'').toLowerCase().includes('create'))&&!/create new workspace/i.test(x.innerText||''));if(b){b.click();return 'ok'}return 'nf'})()")
        print(f'[{genre}] triggered at {trig}', flush=True)

        # 2. Poll for NEW clip with matching prompt
        deadline = time.time() + 240
        target = None
        while time.time() < deadline:
            time.sleep(4)
            try:
                r = requests.get(f'{SUNO}/api/feed/?limit=15', headers=hdr, timeout=20)
                if r.status_code != 200:
                    continue
                clips = r.json() if isinstance(r.json(), list) else r.json().get('clips', [])
                for c in clips:
                    if c.get('model_name') != 'chirp-auk':
                        continue
                    md = c.get('metadata', {})
                    if md.get('cover_clip_id') != UPLOAD:
                        continue
                    pr = md.get('gpt_description_prompt', '')
                    if pr[:30] != want:
                        continue
                    created = c.get('created_at', '')
                    if created < trig[:-5]:
                        continue
                    if c.get('status') in ('complete', 'streaming'):
                        target = c['id']
                        print(f'[{genre}] found clip {target[:12]} status={c.get("status")} created={created}', flush=True)
                        break
                if target:
                    break
            except Exception as e:
                print('poll err', str(e)[:40], flush=True)
        if not target:
            print(f'[{genre}] NO new clip found', flush=True)
            b.close()
            sys.exit(1)

        # 3. Play + quick verify
        play_clip(page, target)
        webm = record(page, 10000)
        if not webm:
            play_clip(page, target, hard=True)
            webm = record(page, 10000)
        tmp = '/tmp/_v.webm'
        with open(tmp, 'wb') as f:
            f.write(webm)
        c0 = centroid_of(tmp)
        os.remove(tmp)
        print(f'[{genre}] sample centroid={c0}', flush=True)
        if c0 < 1500:
            print(f'[{genre}] DEGRADED sample — will still record (may be brief lock)', flush=True)

        # 4. Fresh page + record FULL (MediaElementSource needs clean page)
        play_clip(page, target, hard=True)  # about:blank then song page = clean audio pipeline
        webm_full = record(page, 265000)
        if not webm_full:
            print(f'[{genre}] full record failed, retrying fresh...', flush=True)
            time.sleep(3)
            play_clip(page, target, hard=True)
            webm_full = record(page, 265000)
        if not webm_full:
            print(f'[{genre}] full record failed', flush=True)
            b.close()
            sys.exit(1)
        out = os.path.join(GEN_DIR, f'{HYMN}_10x_{genre}_A_cover.mp3')
        tmpw = out.replace('.mp3', '_t.webm')
        with open(tmpw, 'wb') as f:
            f.write(webm_full)
        subprocess.run([FFM, '-y', '-loglevel', 'error', '-i', tmpw, '-c:a', 'libmp3lame', '-b:a', '192k', out], check=True)
        os.remove(tmpw)
        c = centroid_of(out)
        print(f'[{genre}] SAVED centroid={c} {"OK" if c>1500 else "STILL DEGRADED"} size={os.path.getsize(out)//1024}KB', flush=True)
        b.close()

if __name__ == '__main__':
    main()
