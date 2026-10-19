"""Batch cover generation for a specific upload clip — SAFE from other-bot confusion.
Generates v4.5 covers (More->Remix->Cover) for each genre, then downloads ONLY clips
whose cover_clip_id == our upload_clip_id.

Usage: python scripts/batch_gen_covers.py <upload_clip_id> <hymn_name> <genres_csv>
  genres_csv: psytrance,deep_house,drum_and_bass,gabba,dubstep,chiptune,synthwave,hardstyle,detroit_techno,detroit_house,japanese_hardcore_techno
"""
import sys, os, json, time, requests, subprocess, argparse
from playwright.sync_api import sync_playwright

SUNO_BASE = "https://studio-api-prod.suno.com"
GEN_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "generated")

GENRE_DESC = {
    "psytrance": "full-on psytrance, driving 145 BPM four-on-the-floor kick, rolling offbeat bass, hypnotic acid leads, psychedelic arpeggios, euphoric drops, festival-ready trance journey",
    "deep_house": "deep house, warm analog chords, rolling syncopated bassline, four-on-the-floor kick at 122 BPM, hypnotic groove, soulful late-night warehouse feel",
    "drum_and_bass": "drum and bass, fast 174 BPM breakbeats, rolling sub-bass, reese bass swells, chopped breaks, high-energy syncopated drum work",
    "gabba": "gabba hardcore, relentlessly distorted kick drums at 190 BPM, saturated low end, aggressive rave atmosphere, industrial hardcore energy",
    "dubstep": "brostep dubstep, massive LFO wobble bass drops, half-time 140 BPM drums, growling midrange basses, festival-ready bass music",
    "chiptune": "chiptune, 8-bit square wave leads, arpeggios, triangle bass, noise percussion, retro video game soundtrack energy",
    "synthwave": "synthwave, warm analog polysynths, pulsing sidechained bassline, 100-110 BPM neon-drenched retro-future groove, 1980s nostalgia",
    "hardstyle": "hardstyle trance, pounding distorted kicks at 150 BPM, supersaw leads, euphoric melodies, festival-ready raw energy",
    "detroit_techno": "detroit techno, analog synth stacks, hypnotic machine grooves, 132 BPM, late-night warehouse minimalism, deep soulful tension",
    "detroit_house": "detroit house, deep Motor City grooves, soulful chords, rolling bass, 124 BPM, warm underground warehouse sound",
    "japanese_hardcore_techno": "japanese hardcore techno, 180-190 BPM distorted kicks, rave stabs, glitchy accents, intense J-core energy",
}

def find_upload_feed(hdr, upload_clip_id):
    """Get the upload clip's title/model from feed (search deeper pages)."""
    for pg in range(0, 15):
        r = requests.get(f"{SUNO_BASE}/api/feed/?limit=50&page={pg}", headers=hdr, timeout=30)
        if r.status_code != 200:
            break
        clips = r.json() if isinstance(r.json(), list) else r.json().get('clips', [])
        if not clips:
            break
        for c in clips:
            if c.get('id') == upload_clip_id:
                return c
        if len(clips) < 50:
            break
    return None

def trigger_cover(page, hdr, upload_cid, genre):
    """v4.5 More->Remix->Cover flow for one genre. Returns list of new clip ids."""
    # Navigate to song page
    page.goto(f"https://suno.com/song/{upload_cid}", wait_until="domcontentloaded", timeout=30000)
    page.wait_for_timeout(8000)
    # dismiss cookie banner if present
    page.evaluate('Array.from(document.querySelectorAll("button")).find(b=>b.innerText.trim()==="Reject All")?.click()')
    page.wait_for_timeout(1000)
    # More menu (focus + Enter is reliable)
    try:
        page.focus('button[aria-label="More menu contents"]')
        page.keyboard.press('Enter')
    except Exception:
        page.evaluate('document.querySelector(\'button[aria-label="More menu contents"]\')?.click()')
    page.wait_for_timeout(2500)
    # Click Remix
    page.evaluate('''(()=>{var els=Array.from(document.querySelectorAll('[role=menuitem],div[class*=menu] button,button')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='remix');if(els.length){els[0].click();return 'ok'}return 'nf'})()''')
    page.wait_for_timeout(2500)
    # Click Cover
    page.evaluate('''(()=>{var els=Array.from(document.querySelectorAll('[role=menuitem],button,div[class*=menu] *')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='cover');if(els.length){els[0].click();return 'ok'}return 'nf'})()''')
    try:
        page.wait_for_url("**/create**", timeout=20000)
    except Exception:
        pass
    page.wait_for_timeout(6000)

    # Fill Song Description textarea (index 2)
    genre_desc = GENRE_DESC.get(genre, genre)
    page.evaluate(f'''(() => {{
        var ns = Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype, 'value').set;
        var t = document.querySelectorAll('textarea')[2];
        if (!t) return 'no textarea';
        ns.call(t, {json.dumps(genre_desc)});
        var fiberKey = Object.keys(t).find(k => k.startsWith('__reactFiber'));
        var fiber = t[fiberKey];
        var current = fiber;
        for (var i = 0; i < 10 && current; i++) {{
            if (i >= 2 && current.memoizedProps && typeof current.memoizedProps.onChange === 'function') {{
                current.memoizedProps.onChange({{ target: t }});
                return 'ok';
            }}
            current = current.return;
        }}
        t.dispatchEvent(new Event('input', {{bubbles: true}}));
    }})()''')
    page.wait_for_timeout(2000)
    # Ensure Instrumental ON
    page.evaluate('''(()=>{var b=Array.from(document.querySelectorAll('button,[role=switch],label')).find(x=>x.offsetParent&&/instrumental/i.test(x.innerText||x.getAttribute('aria-label')||''));if(b){var p=b.getAttribute('aria-pressed');if(p==='true'||b.className.includes('checked')){return} b.click()}})()''')
    page.wait_for_timeout(1500)

    # Snapshot existing cover clip ids (only chirp-auk v4.5)
    existing = set()
    for pg in range(0, 3):
        r = requests.get(f"{SUNO_BASE}/api/feed/?limit=50&page={pg}", headers=hdr, timeout=30)
        if r.status_code != 200: break
        clips = r.json() if isinstance(r.json(), list) else r.json().get('clips', [])
        if not clips: break
        for c in clips:
            if c.get('model_name') == 'chirp-auk':
                existing.add(c['id'])
        if len(clips) < 50: break

    # Click Create
    page.evaluate('''(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&((x.getAttribute('aria-label')||'').toLowerCase().includes('create'))&&!/create new workspace/i.test(x.innerText||''));if(b){b.click();return 'ok'}return 'nf'})()''')
    time.sleep(5)

    # Poll for new chirp-auk clips with our cover_clip_id
    found = []
    for wait_loop in range(60):
        time.sleep(5)
        for pg in range(0, 3):
            r = requests.get(f"{SUNO_BASE}/api/feed/?limit=50&page={pg}", headers=hdr, timeout=30)
            if r.status_code != 200: continue
            clips = r.json() if isinstance(r.json(), list) else r.json().get('clips', [])
            for c in clips:
                cid = c.get('id')
                if cid in existing: continue
                if cid in [f['id'] for f in found]: continue
                if c.get('model_name') != 'chirp-auk': continue
                md = c.get('metadata', {})
                # STRICT: cover_clip_id must match our upload
                if md.get('cover_clip_id') == upload_cid:
                    found.append(c)
                    print(f"  FOUND {genre}: {c.get('title','')[:30]} {cid[:12]} cover={md.get('cover_clip_id','')[:12]}")
        if len(found) >= 2:
            break
        if wait_loop % 6 == 5:
            print(f"  waiting... {wait_loop+1}/60")
    return found

def download_via_mediarecorder(page, clip_id, out_mp3, record_ms=9000):
    """Reuse the DRM-safe capture method. record_ms=full duration by default."""
    # navigate, play, record
    page.goto(f"https://suno.com/song/{clip_id}", wait_until="domcontentloaded", timeout=30000)
    page.wait_for_timeout(8000)
    # get duration from API first
    tok = page.evaluate('async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}')
    hdr = {"Authorization": f"Bearer {tok}"}
    try:
        r = requests.get(f"{SUNO_BASE}/api/clip/{clip_id}/", headers=hdr, timeout=30)
        if r.status_code == 200:
            dur = float(r.json().get('metadata', {}).get('duration', 240))
            record_ms = int((dur + 5) * 1000)
    except Exception:
        pass
    print(f"    recording {record_ms/1000:.0f}s...")
    # click ONLY the main track play button (aria 'Play' in track area y<500)
    for _ in range(3):
        page.evaluate('''(()=>{var btns=Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent);var t=btns.find(b=>(b.getAttribute('aria-label')||'').trim()==='Play'&&b.getBoundingClientRect().y<500);if(t){t.click();return 'ok'}return 'nf'})()''')
        page.wait_for_timeout(5000)
        has_blob = page.evaluate("!!Array.from(document.querySelectorAll('audio')).find(e=>(e.currentSrc||'').startsWith('blob:'))")
        if has_blob: break
    result = page.evaluate('''async (ms) => {
        const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
        if (!a) return JSON.stringify({err:'no blob'});
        a.currentTime = 0; await a.play();
        const Ctx = window.AudioContext || window.webkitAudioContext;
        const ac = new Ctx();
        const src = ac.createMediaElementSource(a);
        const dest = ac.createMediaStreamDestination();
        src.connect(dest);
        const rec = new MediaRecorder(dest.stream);
        const chunks = [];
        rec.ondataavailable = e => { if (e.data && e.data.size > 0) chunks.push(e.data); };
        rec.start(5000);
        await new Promise(r => setTimeout(r, ms));
        rec.stop();
        await new Promise(r => rec.onstop = r);
        const blob = new Blob(chunks, {type:'audio/webm'});
        const buf = await blob.arrayBuffer();
        const bytes = new Uint8Array(buf);
        let bin = '';
        for (let i = 0; i < bytes.length; i += 0x8000) bin += String.fromCharCode.apply(null, bytes.subarray(i, i+0x8000));
        return JSON.stringify({size:bytes.length, b64: btoa(bin)});
    }''', record_ms)  # full song capture
    d = json.loads(result)
    if 'err' in d:
        return False
    # Convert to mp3 via ffmpeg
    import base64
    data = base64.b64decode(d['b64'])
    webm_tmp = out_mp3.replace('.mp3', '.webm')
    with open(webm_tmp, 'wb') as f:
        f.write(data)
    subprocess.run(["ffmpeg", "-y", "-loglevel", "error", "-i", webm_tmp, "-c:a", "libmp3lame", "-b:a", "192k", out_mp3], check=True)
    os.remove(webm_tmp) if os.path.exists(webm_tmp) else None
    return True

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("upload_clip_id")
    ap.add_argument("hymn_name")
    ap.add_argument("genres_csv")
    args = ap.parse_args()
    genres = [g.strip() for g in args.genres_csv.split(",") if g.strip()]

    os.makedirs(GEN_DIR, exist_ok=True)
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        page = next((p for p in b.contexts[0].pages if "suno.com" in p.url), None)
        if not page:
            page = b.contexts[0].new_page()
            page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
            page.wait_for_timeout(8000)
        tok = page.evaluate('async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}')
        if not tok:
            print("No auth token")
            sys.exit(1)
        hdr = {"Authorization": f"Bearer {tok}"}
        # confirm upload exists (warn only — may be deep in feed)
        up = find_upload_feed(hdr, args.upload_clip_id)
        if not up:
            print(f"WARNING: upload {args.upload_clip_id} not in recent feed (may be deep-paged). Proceeding anyway — covers are filtered by cover_clip_id.")
        if up:
            print(f"Upload confirmed: {up.get('title')} ({up.get('model_name')})")

        for genre in genres:
            out_a = os.path.join(GEN_DIR, f"{args.hymn_name}_10x_{genre}_A_cover.mp3")
            if os.path.exists(out_a) and os.path.getsize(out_a) > 1000000:
                print(f"[skip] {genre} already done")
                continue
            print(f"\n=== {genre} ===")
            clips = trigger_cover(page, hdr, args.upload_clip_id, genre)
            if not clips:
                print(f"  {genre}: no clips generated")
                continue
            # download variant A via mediarecorder
            ok = download_via_mediarecorder(page, clips[0]['id'], out_a)
            if ok:
                print(f"  {genre}: A saved -> {os.path.basename(out_a)} ({os.path.getsize(out_a)//1024}KB)")
            else:
                print(f"  {genre}: download failed")
        b.close()
    print("\nDONE")

if __name__ == "__main__":
    main()
