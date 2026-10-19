"""Generate ONE genre fresh and capture immediately (verified method).
Combines careful_gen (reliable injection) + cap_final (correct capture).
Usage: python gen_capture_genre.py <genre>
"""
import sys, os, json, time, base64, subprocess, requests
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

FFM = r'C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe'
SUNO = 'https://studio-api-prod.suno.com'
GEN_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'generated')
HYMN = 'Jesus_Comes_With_Power'
UPLOAD = 'd2246d83-d592-4081-89eb-218a765535a9'

GENRE_DESC = {
    'deep_house': 'deep house, warm analog chords, rolling syncopated bassline, four-on-the-floor kick at 122 BPM, hypnotic groove, soulful late-night warehouse feel',
    'drum_and_bass': 'drum and bass, fast 174 BPM breakbeats, rolling sub-bass, reese bass swells, chopped breaks, high-energy syncopated drum work',
    'gabba': 'gabba hardcore, relentlessly distorted kick drums at 190 BPM, saturated low end, aggressive rave atmosphere, industrial hardcore energy',
    'dubstep': 'brostep dubstep, massive LFO wobble bass drops, half-time 140 BPM drums, growling midrange basses, festival-ready bass music',
    'synthwave': 'synthwave, warm analog polysynths, pulsing sidechained bassline, 100-110 BPM neon-drenched retro-future groove, 1980s nostalgia',
    'japanese_hardcore_techno': 'japanese hardcore techno, 180-190 BPM distorted kicks, rave stabs, glitchy accents, intense J-core energy',
    'psytrance': 'full-on psytrance, driving 145 BPM four-on-the-floor kick, rolling offbeat bass, hypnotic acid leads, psychedelic arpeggios, euphoric drops',
    'chiptune': 'chiptune, 8-bit square wave leads, arpeggios, triangle bass, noise percussion, retro video game soundtrack energy',
    'hardstyle': 'hardstyle trance, pounding distorted kicks at 150 BPM, supersaw leads, euphoric melodies, festival-ready energy',
    'detroit_techno': 'detroit techno, analog synth stacks, hypnotic machine grooves, 132 BPM, late-night warehouse minimalism',
    'detroit_house': 'detroit house, deep Motor City grooves, soulful chords, rolling bass, 124 BPM, warm underground sound',
}

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

def main():
    # usage: gen_capture_genre.py <genre> [upload_clip_id] [hymn]
    genre = sys.argv[1]
    upload_id = sys.argv[2] if len(sys.argv) > 2 else UPLOAD
    hymn_name = sys.argv[3] if len(sys.argv) > 3 else HYMN
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp('http://127.0.0.1:9333')
        # reuse existing suno page to avoid CDP churn
        page = next((p for p in b.contexts[0].pages if 'suno.com' in p.url), None)
        if not page:
            page = b.contexts[0].new_page()

        # STEP 1: trigger cover with verified description
        page.goto(f'https://suno.com/song/{upload_id}', wait_until='domcontentloaded', timeout=30000)
        page.wait_for_timeout(7000)
        try:
            page.focus('button[aria-label="More menu contents"]')
            page.keyboard.press('Enter')
        except Exception:
            page.evaluate("document.querySelector('button[aria-label=\"More menu contents\"]')?.click()")
        page.wait_for_timeout(3000)
        # HOVER over the Remix button (data-context-menu-trigger) to open the Cover submenu
        rpos = page.evaluate("""() => {
            var b = Array.from(document.querySelectorAll('button[data-context-menu-trigger=true]')).find(x=>{
                var it = x.closest('.context-menu-item');
                return it && (it.innerText||'').trim().toLowerCase()==='remix';
            });
            if (!b) b = Array.from(document.querySelectorAll('.context-menu-button')).find(x=>(x.innerText||'').trim().toLowerCase().startsWith('remix'));
            if (!b) return 'nf';
            var rr = b.getBoundingClientRect();
            return JSON.stringify({x: Math.round(rr.x+rr.width/2), y: Math.round(rr.y+rr.height/2)});
        }""")
        if rpos != 'nf':
            pd = json.loads(rpos)
            page.mouse.move(pd['x'], pd['y'])
            page.wait_for_timeout(3500)
            # click Cover in the revealed submenu
            cpos = page.evaluate("""() => {
                var all = document.querySelectorAll('.context-menu-item, [role=menuitem], li, button, div');
                for (var e of all) {
                    var t = (e.innerText||'').trim();
                    if (t === 'Cover' && e.offsetParent) {
                        var rr = e.getBoundingClientRect();
                        if (rr.width > 5) return JSON.stringify({x: Math.round(rr.x+rr.width/2), y: Math.round(rr.y+rr.height/2)});
                    }
                }
                return 'nf';
            }""")
            if cpos != 'nf':
                cd = json.loads(cpos)
                page.mouse.click(cd['x'], cd['y'])
        else:
            # fallback: old method click remix then cover
            page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],div[class*=menu] button,button')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='remix')[0]?.click()")
            page.wait_for_timeout(2500)
            page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],button,div[class*=menu] *')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='cover')[0]?.click()")
        try:
            page.wait_for_url('**/create**', timeout=20000)
        except Exception:
            pass
        page.wait_for_timeout(8000)
        # fill textarea maxLength=3000
        desc_i = None
        tas = json.loads(page.evaluate("JSON.stringify(Array.from(document.querySelectorAll('textarea')).map((t,i)=>({i,ml:t.maxLength,ph:(t.placeholder||'').slice(0,30)})))"))
        desc_i = next((t['i'] for t in tas if t['ml'] == 3000), None)
        if desc_i is None:
            desc_i = 2
        page.evaluate("(()=>{var i=" + str(desc_i) + ";var t=document.querySelectorAll('textarea')[i];if(!t)return 'nf';var s=Object.getOwnPropertyDescriptor(HTMLTextAreaElement.prototype,'value').set;s.call(t," + json.dumps(GENRE_DESC[genre]) + ");t.dispatchEvent(new Event('input',{bubbles:true}));t.dispatchEvent(new Event('change',{bubbles:true}));return 'ok'})()")
        page.wait_for_timeout(2000)
        val = page.evaluate("(()=>{var t=document.querySelectorAll('textarea')[" + str(desc_i) + "];return t?t.value.slice(0,20):''})()")
        print(f'[{genre}] desc verified: {val}', flush=True)
        # instrumental on
        page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button,[role=switch],label')).find(x=>x.offsetParent&&/instrumental/i.test(x.innerText||x.getAttribute('aria-label')||''));if(b&&b.getAttribute('aria-pressed')!=='true'){b.click()}})()")
        page.wait_for_timeout(1000)
        trig = time.strftime('%Y-%m-%dT%H:%M:%S', time.gmtime())
        page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&((x.getAttribute('aria-label')||'').toLowerCase().includes('create'))&&!/create new workspace/i.test(x.innerText||''));if(b){b.click();return 'ok'}return 'nf'})()")
        print(f'[{genre}] Create at {trig}', flush=True)

        # STEP 2: poll for new clip with our prompt
        tok = page.evaluate('async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}')
        hdr = {'Authorization': f'Bearer {tok}'}
        want = GENRE_DESC[genre][:20]
        target = None
        deadline = time.time() + 240
        while time.time() < deadline:
            time.sleep(5)
            try:
                r = requests.get(f'{SUNO}/api/feed/?limit=15', headers=hdr, timeout=20)
                if r.status_code != 200:
                    continue
                cs = r.json() if isinstance(r.json(), list) else r.json().get('clips', [])
                for c in cs:
                    mn = c.get('model_name', '')
                    if not (mn.startswith('chirp-') and mn != 'chirp-chirp'):
                        continue
                    md = c.get('metadata', {})
                    if md.get('cover_clip_id') != upload_id:
                        continue
                    pr = md.get('gpt_description_prompt', '')
                    cr = c.get('created_at', '')
                    if pr[:20] == want and cr >= trig[:-5] and c.get('status') == 'complete':
                        target = c['id']
                        print(f'[{genre}] new clip {target[:12]}', flush=True)
                        break
                if target:
                    break
            except Exception:
                pass
        if not target:
            print(f'[{genre}] no clip found in time', flush=True)
            b.close()
            sys.exit(1)

        # STEP 3: capture with correct duration
        md_dur = 240
        r = requests.get(f'{SUNO}/api/feed/?limit=15', headers=hdr, timeout=20)
        if r.status_code == 200:
            for c in (r.json() or []):
                if c.get('id') == target:
                    md_dur = c.get('metadata', {}).get('duration', 240)
        print(f'[{genre}] duration {md_dur}s, capturing...', flush=True)
        page.goto(f'https://suno.com/song/{target}', wait_until='load', timeout=25000)
        page.wait_for_timeout(8000)
        page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
        page.wait_for_timeout(6000)
        rec_s = md_dur + 3
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
        res = page.evaluate(js, rec_s)
        d = json.loads(res)
        if d.get('err'):
            print(f'[{genre}] capture err: {d["err"]}', flush=True)
        else:
            webm = f'/tmp/{genre}_gc.webm'
            with open(webm, 'wb') as f:
                f.write(base64.b64decode(d['b64']))
            out = os.path.join(GEN_DIR, f'{hymn_name}_10x_{genre}_A_cover.mp3')
            subprocess.run([FFM, '-y', '-loglevel', 'error', '-i', webm, '-c:a', 'libmp3lame', '-b:a', '192k', out], check=True)
            os.remove(webm)
            c = centroid(out)
            FFP = FFM.replace('ffmpeg.exe', 'ffprobe.exe')
            r2 = subprocess.run([FFP, '-v', 'quiet', '-show_entries', 'format=duration', '-of', 'csv=p=0', out], capture_output=True, text=True)
            dur = float(r2.stdout.strip()) if r2.stdout.strip() else 0
            ok = 'OK' if c > 2000 else 'DEGRADED'
            print(f'[{genre}] RESULT: dur={dur:.0f}s centroid={c} {ok} size={os.path.getsize(out)//1024}KB', flush=True)
        b.close()

if __name__ == '__main__':
    main()
