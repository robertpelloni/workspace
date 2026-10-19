"""Generate + capture a real genre cover using an ISOLATED Edge instance.
The shared CDP browser (port 9222) keeps closing pages during Suno Remix->Cover,
so we launch a dedicated Edge (own profile, logs into suno via prompt-free reuse
or re-login) to do the cover generation reliably.

Usage: python gen_cover_isolated.py <genre_key> <upload_clip_id> <hymn_name> [genre_display]
"""
import subprocess, sys, os, json, time, base64, requests
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

SUNO = "https://studio-api-prod.suno.com"
ROOT = os.path.dirname(os.path.abspath(__file__))
GEN_DIR = os.path.join(ROOT, "generated")
EDGE_PATH = r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe"
PROFILE = os.path.join(ROOT, ".suno-iso-profile")
PORT = 9345
FFM = r"C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe"

GENRE_DESC = {
    "deep_house": "deep house, warm analog chords, rolling syncopated bassline, four-on-the-floor kick at 122 BPM, hypnotic groove, soulful late-night warehouse feel",
    "synthwave": "synthwave, warm analog polysynths, pulsing sidechained bassline, 100-110 BPM neon-drenched retro-future groove, 1980s nostalgia",
    "dubstep": "brostep dubstep, massive LFO wobble bass drops, half-time 140 BPM drums, growling midrange basses, festival-ready bass music",
    "psytrance": "full-on psytrance, driving 145 BPM four-on-the-floor kick, rolling offbeat bass, hypnotic acid leads, psychedelic arpeggios, euphoric drops",
    "chiptune": "chiptune, 8-bit square wave leads, arpeggios, triangle bass, noise percussion, retro video game soundtrack energy",
    "drum_and_bass": "drum and bass, fast 174 BPM breakbeats, rolling sub-bass, reese bass swells, chopped breaks, high-energy drum work",
    "gabba": "gabba hardcore, relentlessly distorted kick drums at 190 BPM, saturated low end, aggressive rave atmosphere",
    "hardstyle": "hardstyle trance, pounding distorted kicks at 150 BPM, supersaw leads, euphoric melodies, festival-ready energy",
    "detroit_techno": "detroit techno, analog synth stacks, hypnotic machine grooves, 132 BPM, late-night warehouse minimalism",
    "detroit_house": "detroit house, deep Motor City grooves, soulful chords, rolling bass, 124 BPM, warm underground sound",
}

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

def record(page, ms):
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
    res = page.evaluate(js, ms)
    d = json.loads(res)
    if "err" in d:
        return None
    return base64.b64decode(d["b64"])

def main():
    genre = sys.argv[1]
    upload_cid = sys.argv[2]
    hymn = sys.argv[3]
    os.makedirs(GEN_DIR, exist_ok=True)
    os.makedirs(PROFILE, exist_ok=True)
    proc = subprocess.Popen([EDGE_PATH, f"--remote-debugging-port={PORT}",
        f"--user-data-dir={PROFILE}", "--no-first-run", "--no-default-browser-check",
        "about:blank"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    time.sleep(7)
    try:
        with sync_playwright() as pw:
            b = pw.chromium.connect_over_cdp(f"http://127.0.0.1:{PORT}")
            page = b.contexts[0].new_page()
            page.goto(f"https://suno.com/song/{upload_cid}", wait_until="load", timeout=40000)
            page.wait_for_timeout(8000)
            tok = page.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}")
            if not tok:
                print("isolated browser NOT logged into suno — need login", flush=True)
                b.close()
                return False
            # More menu -> Remix -> Cover
            try:
                page.focus('button[aria-label="More menu contents"]')
                page.keyboard.press("Enter")
            except Exception:
                page.evaluate("document.querySelector('button[aria-label=\\\"More menu contents\\\"]')?.click()")
            page.wait_for_timeout(3000)
            page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],button')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='remix')[0]?.click()")
            page.wait_for_timeout(3000)
            page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],button,div')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='cover')[0]?.click()")
            try:
                page.wait_for_url("**/create**", timeout=20000)
            except Exception:
                pass
            page.wait_for_timeout(8000)
            # fill description
            desc = GENRE_DESC.get(genre, genre)
            desc_i = 2
            tas = json.loads(page.evaluate("JSON.stringify(Array.from(document.querySelectorAll('textarea')).map((t,i)=>({i,ml:t.maxLength})))"))
            d2 = next((t["i"] for t in tas if t["ml"] == 3000), None)
            if d2 is not None:
                desc_i = d2
            page.evaluate("(()=>{var i=" + str(desc_i) + ";var t=document.querySelectorAll('textarea')[i];if(!t)return 'nf';var s=Object.getOwnPropertyDescriptor(HTMLTextAreaElement.prototype,'value').set;s.call(t," + json.dumps(desc) + ");t.dispatchEvent(new Event('input',{bubbles:true}));t.dispatchEvent(new Event('change',{bubbles:true}));return 'ok'})()")
            page.wait_for_timeout(2000)
            val = page.evaluate("(()=>{var t=document.querySelectorAll('textarea')[" + str(desc_i) + "];return t?t.value.slice(0,20):''})()")
            print("desc set: " + str(val), flush=True)
            # instrumental on
            page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button,[role=switch],label')).find(x=>x.offsetParent&&/instrumental/i.test(x.innerText||x.getAttribute('aria-label')||''));if(b&&b.getAttribute('aria-pressed')!=='true'){b.click()}})()")
            page.wait_for_timeout(1000)
            trig = time.strftime("%Y-%m-%dT%H:%M:%S", time.gmtime())
            page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&((x.getAttribute('aria-label')||'').toLowerCase().includes('create'))&&!/create new workspace/i.test(x.innerText||''));if(b){b.click();return 'ok'}return 'nf'})()")
            print("Create at " + trig, flush=True)
            # poll for new clip
            tok2 = page.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}")
            hdr = {"Authorization": "Bearer " + str(tok2)}
            want = desc[:20]
            target = None
            for _ in range(50):
                time.sleep(5)
                r = requests.get(SUNO + "/api/feed/?limit=15", headers=hdr, timeout=20)
                if r.status_code == 200:
                    clips = r.json() if isinstance(r.json(), list) else r.json().get("clips", [])
                    for c in clips:
                        if c.get("model_name") != "chirp-auk":
                            continue
                        md = c.get("metadata", {})
                        if md.get("cover_clip_id") != upload_cid:
                            continue
                        cr = c.get("created_at", "")
                        if md.get("gpt_description_prompt", "")[:20] == want and cr >= trig[:-5] and c.get("status") == "complete":
                            target = c["id"]
                            print("new clip: " + str(target)[:12], flush=True)
                            break
                    if target:
                        break
            if not target:
                print("no clip", flush=True)
                b.close()
                return False
            # get duration
            md_dur = 240
            for pg in range(0, 2):
                r = requests.get(SUNO + "/api/feed/?limit=50&page=" + str(pg), headers=hdr, timeout=20)
                if r.status_code != 200:
                    break
                for c in (r.json() or []):
                    if c.get("id") == target:
                        md_dur = c.get("metadata", {}).get("duration", 240)
            print("duration " + str(md_dur), flush=True)
            # play + capture full
            page.goto(f"https://suno.com/song/{target}", wait_until="load", timeout=30000)
            page.wait_for_timeout(8000)
            page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
            page.wait_for_timeout(6000)
            webm = record(page, int(md_dur * 1000) + 5000)
            if not webm:
                print("record failed", flush=True)
                b.close()
                return False
            out = os.path.join(GEN_DIR, f"{hymn}_10x_{genre}_A_cover.mp3")
            tmpw = out.replace(".mp3", "_t.webm")
            with open(tmpw, "wb") as f:
                f.write(webm)
            subprocess.run([FFM, "-y", "-loglevel", "error", "-i", tmpw, "-c:a", "libmp3lame", "-b:a", "192k", out], check=True)
            os.remove(tmpw)
            c = centroid(out)
            print("RESULT centroid=" + str(c) + (" OK" if c > 2000 else " DEGRADED") + " size=" + str(os.path.getsize(out) // 1024) + "KB", flush=True)
            b.close()
            return c > 2000
    except Exception as e:
        print("err: " + str(e)[:200], flush=True)
        return False
    finally:
        try:
            proc.terminate()
        except Exception:
            pass

if __name__ == "__main__":
    ok = main()
    print("SUCCESS: " + str(ok))
