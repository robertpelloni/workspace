"""Generate a cover and capture the FULL audio IMMEDIATELY when it completes.
Suno degrades playback of clips within minutes of creation. Must capture fast.
Strategy: trigger cover -> poll every 3s -> on status=complete -> capture 10s
sample FIRST to verify full quality -> then record full song immediately.

Usage: python scripts/gen_and_capture.py <upload_clip_id> <hymn_name> <genre> [genre2...]
"""
import sys, os, json, time, base64, subprocess, tempfile, requests
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
import numpy as np
from playwright.sync_api import sync_playwright

SUNO = 'https://studio-api-prod.suno.com'
FFM = r'C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe'
GEN_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'generated')

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

def trigger_cover(page, upload_cid, genre):
    page.goto(f'https://suno.com/song/{upload_cid}', wait_until='domcontentloaded', timeout=30000)
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
    desc = GENRE_DESC.get(genre, genre)
    page.evaluate("(()=>{var t=document.querySelectorAll('textarea')[2];if(!t)return;var ns=Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype,'value').set;ns.call(t," + json.dumps(desc) + ");var fk=Object.keys(t).find(k=>k.startsWith('__reactFiber'));var f=t[fk];var c=f;for(var i=0;i<10&&c;i++){if(i>=2&&c.memoizedProps&&typeof c.memoizedProps.onChange==='function'){c.memoizedProps.onChange({target:t});return}c=c.return}})()")
    page.wait_for_timeout(1500)
    # get trigger time (before Create)
    trig = time.strftime('%Y-%m-%dT%H:%M:%S', time.gmtime())
    page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&((x.getAttribute('aria-label')||'').toLowerCase().includes('create'))&&!/create new workspace/i.test(x.innerText||''));if(b){b.click();return 'ok'}return 'nf'})()")
    print(f'  [{genre}] Create clicked at {trig}', flush=True)
    return trig

def sample_capture(page, ms=12000):
    """Record a sample and return webm bytes."""
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
        rec.start(1000);
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
        return None
    return base64.b64decode(d['b64'])

def capture_from_page(page, cid, genre, hymn, speed, want_full=True):
    """Navigate to clip, play, verify quality with 12s sample, then record full."""
    page.goto(f'https://suno.com/song/{cid}', wait_until='domcontentloaded', timeout=20000)
    page.wait_for_timeout(4000)
    page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
    page.wait_for_timeout(4000)
    # quick 12s sample to verify
    webm = sample_capture(page, 12000)
    if not webm:
        print(f'  [{genre}] no blob on {cid[:12]}', flush=True)
        return None
    tmp = '/tmp/_qc_sample.webm'
    with open(tmp, 'wb') as f:
        f.write(webm)
    c = centroid_of(tmp)
    os.remove(tmp)
    print(f'  [{genre}] {cid[:12]} sample centroid={c}', flush=True)
    if c < 1500:
        print(f'  [{genre}] DEGRADED — skip (need fresh clip)', flush=True)
        return None
    if not want_full:
        return c
    # reload (MediaElementSource used once) and record full
    page.reload(wait_until='domcontentloaded')
    page.wait_for_timeout(5000)
    page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
    page.wait_for_timeout(4000)
    webm_full = sample_capture(page, 260000)  # ~4min20
    if not webm_full:
        return None
    out = os.path.join(GEN_DIR, f'{hymn}_{speed}_{genre}_A_cover.mp3')
    tmpw = out.replace('.mp3', '_tmp.webm')
    with open(tmpw, 'wb') as f:
        f.write(webm_full)
    subprocess.run([FFM, '-y', '-loglevel', 'error', '-i', tmpw, '-c:a', 'libmp3lame', '-b:a', '192k', out], check=True)
    os.remove(tmpw)
    cc = centroid_of(out)
    print(f'  [{genre}] SAVED full centroid={cc} {"OK" if cc>1500 else "DEGRADED!"}', flush=True)
    return out if cc > 1500 else None

def wait_and_capture(page, hdr, upload_cid, genre, hymn, trig, speed='10x', timeout_s=280):
    """Poll for clip created after trig-30s, complete, then capture."""
    start = time.time()
    while time.time() - start < timeout_s:
        time.sleep(3)
        try:
            r = requests.get(f'{SUNO}/api/feed/?limit=15', headers=hdr, timeout=20)
            if r.status_code != 200:
                continue
            clips = r.json() if isinstance(r.json(), list) else r.json().get('clips', [])
            for c in clips:
                if c.get('model_name') != 'chirp-auk':
                    continue
                md = c.get('metadata', {})
                if md.get('cover_clip_id') != upload_cid:
                    continue
                created = c.get('created_at', '')
                if created < trig[:-5]:  # allow 30s clock tolerance
                    continue  # old clip, skip
                if c.get('status') == 'complete':
                    print(f'  [{genre}] NEW complete {c["id"][:12]} at {created}', flush=True)
                    out = capture_from_page(page, c['id'], genre, hymn, speed)
                    if out:
                        return out
                    # if degraded or failed, keep polling for the other variant
        except Exception as e:
            pass
    return None

def main():
    upload_cid = sys.argv[1]
    hymn = sys.argv[2]
    genres = sys.argv[3:]
    os.makedirs(GEN_DIR, exist_ok=True)
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
        page = next((p for p in b.contexts[0].pages if 'suno.com' in p.url), None)
        if not page:
            page = b.contexts[0].new_page()
            page.goto('https://suno.com/create', wait_until='domcontentloaded', timeout=30000)
            page.wait_for_timeout(8000)
        tok = page.evaluate('async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}')
        hdr = {'Authorization': f'Bearer {tok}'}
        for genre in genres:
            # skip if already OK
            out_check = os.path.join(GEN_DIR, f'{hymn}_10x_{genre}_A_cover.mp3')
            if os.path.exists(out_check) and os.path.getsize(out_check) > 1000000:
                c = centroid_of(out_check)
                if c > 1500:
                    print(f'[skip] {genre} already OK ({c})', flush=True)
                    continue
            print(f'=== {genre} ===', flush=True)
            trig = trigger_cover(page, upload_cid, genre)
            ok = wait_and_capture(page, hdr, upload_cid, genre, hymn, trig)
            if not ok:
                print(f'  {genre}: FAILED', flush=True)
        b.close()
    print('DONE')

if __name__ == '__main__':
    main()
