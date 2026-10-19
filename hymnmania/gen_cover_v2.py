"""Robust cover flow that re-acquires the page handle after SPA navigation.
The Suno More->Remix->Cover navigation to /create invalidates the CDP page handle,
so we must re-fetch the page after navigating.

Usage: python gen_cover_v2.py <genre_key> <upload_clip_id> <hymn_name>
"""
import sys, os, json, time, base64, requests, subprocess
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

SUNO = "https://studio-api-prod.suno.com"
ROOT = os.path.dirname(os.path.abspath(__file__))
GEN_DIR = os.path.join(ROOT, "generated")
FFM = r"C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe"

GENRE_DESC = {
    "deep_house": "deep house, warm analog chords, rolling syncopated bassline, four-on-the-floor kick at 122 BPM, hypnotic groove, soulful late-night warehouse feel",
    "synthwave": "synthwave, warm analog polysynths, pulsing sidechained bassline, 100-110 BPM neon-drenched retro-future groove, 1980s nostalgia",
    "dubstep": "brostep dubstep, massive LFO wobble bass drops, half-time 140 BPM drums, growling midrange basses, festival-ready bass music",
    "drum_and_bass": "drum and bass, fast 174 BPM breakbeats, rolling sub-bass, reese bass swells, chopped breaks, high-energy drum work",
    "gabba": "gabba hardcore, relentlessly distorted kick drums at 190 BPM, saturated low end, aggressive rave atmosphere",
    "chiptune": "chiptune, 8-bit square wave leads, arpeggios, triangle bass, noise percussion, retro video game soundtrack energy",
    "psytrance": "full-on psytrance, driving 145 BPM four-on-the-floor kick, rolling offbeat bass, hypnotic acid leads, psychedelic arpeggios, euphoric drops",
    "hardstyle": "hardstyle trance, pounding distorted kicks at 150 BPM, supersaw leads, euphoric melodies, festival-ready energy",
    "detroit_techno": "detroit techno, analog synth stacks, hypnotic machine grooves, 132 BPM, late-night warehouse minimalism",
    "detroit_house": "detroit house, deep Motor City grooves, soulful chords, rolling bass, 124 BPM, warm underground sound",
}

def get_suno_page(b):
    for p in b.contexts[0].pages:
        if "suno.com" in p.url and "handshake" not in p.url:
            return p
    p = b.contexts[0].new_page()
    p.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
    return p

def centroid(file):
    import numpy as np, tempfile as _tf
    tmp = _tf.mktemp(suffix=".f32")
    subprocess.run([FFM, "-y", "-loglevel", "error", "-i", file, "-ac", "1", "-ar", "48000", "-f", "f32le", tmp], capture_output=True)
    d = np.frombuffer(open(tmp, "rb").read(), dtype=np.float32)
    os.remove(tmp)
    cents = []
    for i in range(0, len(d) - 2048, 2048):
        spec = np.abs(np.fft.rfft(d[i:i+2048] * np.hanning(2048)))
        fr = np.fft.rfftfreq(2048, 1/48000)
        if spec.sum() > 0:
            cents.append((spec * fr).sum() / spec.sum())
    return round(float(np.mean(cents)), 1) if cents else 0

def main():
    genre = sys.argv[1]
    upload_id = sys.argv[2]
    hymn = sys.argv[3]
    desc = GENRE_DESC[genre]
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9333")
        page = get_suno_page(b)
        # 1. go to song page
        page.goto(f"https://suno.com/song/{upload_id}", wait_until="domcontentloaded", timeout=40000)
        page.wait_for_timeout(8000)
        print("on song page:", page.url[:50], flush=True)
        # 2. More menu (keyboard)
        try:
            page.focus('button[aria-label="More menu contents"]')
            page.keyboard.press("Enter")
        except Exception:
            page.evaluate("document.querySelector('button[aria-label=\\\"More menu contents\\\"]')?.click()")
        page.wait_for_timeout(3500)
        # 3. Remix
        try:
            page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],div[class*=menu] button,button')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='remix')[0]?.click()")
            print("remix clicked", flush=True)
        except Exception as e:
            print("remix err:", str(e)[:60], flush=True)
        page.wait_for_timeout(3500)
        # 4. Cover (this navigates to /create and may invalidate handle)
        try:
            page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],button,div[class*=menu] *')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='cover')[0]?.click()")
            print("cover clicked", flush=True)
        except Exception as e:
            print("cover click err:", str(e)[:60], flush=True)
        # 5. WAIT for /create navigation to settle
        time.sleep(8)
        # 6. RE-ACQUIRE the page handle (old one may be stale after navigation)
        page = get_suno_page(b)
        page.wait_for_timeout(5000)
        print("re-acquired page:", page.url[:50], flush=True)
        # verify cover form is ready
        body = page.evaluate("document.body.innerText")
        if "create" not in page.url:
            print("not on create page — retrying nav", flush=True)
        # 7. fill description textarea (maxLength 3000)
        tas = json.loads(page.evaluate("JSON.stringify(Array.from(document.querySelectorAll('textarea')).map((t,i)=>({i,ml:t.maxLength,ph:(t.placeholder||'').slice(0,30)})))"))
        desc_i = next((t["i"] for t in tas if t["ml"] == 3000), None)
        if desc_i is None:
            desc_i = 2
        page.evaluate("(()=>{var i=" + str(desc_i) + ";var t=document.querySelectorAll('textarea')[i];if(!t)return 'nf';var s=Object.getOwnPropertyDescriptor(HTMLTextAreaElement.prototype,'value').set;s.call(t," + json.dumps(desc) + ");t.dispatchEvent(new Event('input',{bubbles:true}));t.dispatchEvent(new Event('change',{bubbles:true}));return 'ok'})()")
        page.wait_for_timeout(2500)
        val = page.evaluate("(()=>{var t=document.querySelectorAll('textarea')[" + str(desc_i) + "];return t?t.value.slice(0,25):''})()")
        print("desc set:", val, flush=True)
        # 8. instrumental on
        page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button,[role=switch],label')).find(x=>x.offsetParent&&/instrumental/i.test(x.innerText||x.getAttribute('aria-label')||''));if(b&&b.getAttribute('aria-pressed')!=='true'){b.click()}})()")
        page.wait_for_timeout(1000)
        # 9. Create
        trig = time.strftime("%Y-%m-%dT%H:%M:%S", time.gmtime())
        page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&((x.getAttribute('aria-label')||'').toLowerCase().includes('create'))&&!/create new workspace/i.test(x.innerText||''));if(b){b.click();return 'ok'}return 'nf'})()")
        print("Create at", trig, flush=True)
        # 10. poll for new clip
        tok = page.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}")
        hdr = {"Authorization": "Bearer " + str(tok)}
        want = desc[:20]
        target = None
        for _ in range(55):
            time.sleep(5)
            try:
                r = requests.get(SUNO + "/api/feed/?limit=15", headers=hdr, timeout=20)
                if r.status_code == 200:
                    for c in (r.json() or []):
                        if c.get("model_name") != "chirp-auk":
                            continue
                        md = c.get("metadata", {})
                        if md.get("cover_clip_id") != upload_id:
                            continue
                        cr = c.get("created_at", "")
                        if md.get("gpt_description_prompt", "")[:20] == want and cr >= trig[:-5] and c.get("status") == "complete":
                            target = c["id"]
                            print("new clip:", str(target)[:12], flush=True)
                            break
                    if target:
                        break
            except Exception:
                pass
        if not target:
            print("no clip found", flush=True)
            b.close()
            return
        # 11. get duration + capture
        md_dur = 240
        for pg in range(0, 2):
            r = requests.get(SUNO + "/api/feed/?limit=50&page=" + str(pg), headers=hdr, timeout=20)
            if r.status_code != 200:
                break
            for c in (r.json() or []):
                if c.get("id") == target:
                    md_dur = c.get("metadata", {}).get("duration", 240)
        print("dur", md_dur, flush=True)
        # re-acquire + navigate to clip
        page = get_suno_page(b)
        page.goto(f"https://suno.com/song/{target}", wait_until="domcontentloaded", timeout=30000)
        page.wait_for_timeout(9000)
        try:
            page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
        except Exception:
            pass
        page.wait_for_timeout(6000)
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
            rec.start(2000);
            await new Promise(r => setTimeout(r, ms));
            rec.stop(); await new Promise(r => rec.onstop = r);
            const blob = new Blob(chunks,{type:'audio/webm'});
            const ab = await blob.arrayBuffer(); const bytes = new Uint8Array(ab);
            let bin=''; for(let i=0;i<bytes.length;i+=0x8000) bin+=String.fromCharCode.apply(null,bytes.subarray(i,i+0x8000));
            return JSON.stringify({size:bytes.length,b64:btoa(bin)});
        }"""
        res = page.evaluate(js, int(md_dur * 1000) + 5000)
        d = json.loads(res)
        if "err" in d:
            print("record err:", d["err"], flush=True)
            b.close()
            return
        out = os.path.join(GEN_DIR, f"{hymn}_10x_{genre}_A_cover.mp3")
        tmpw = out.replace(".mp3", "_t.webm")
        with open(tmpw, "wb") as f:
            f.write(base64.b64decode(d["b64"]))
        subprocess.run([FFM, "-y", "-loglevel", "error", "-i", tmpw, "-c:a", "libmp3lame", "-b:a", "192k", out], check=True)
        os.remove(tmpw)
        c = centroid(out)
        print("RESULT centroid=" + str(c) + (" OK" if c > 2000 else " DEGRADED") + " size=" + str(os.path.getsize(out) // 1024) + "KB", flush=True)
        b.close()

if __name__ == "__main__":
    main()
