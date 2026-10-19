"""Resilient cover generator that reconnects to the suno page if the CDP handle dies.
Usage: python gen_cover_resilient.py <genre_key> <upload_clip_id> <hymn_name>
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
}

def get_page(b):
    for p in b.contexts[0].pages:
        if "suno.com" in p.url:
            return p
    p = b.contexts[0].new_page()
    return p

def safe_eval(page, expr):
    """Evaluate with reconnect if page died."""
    try:
        return page.evaluate(expr)
    except Exception:
        time.sleep(2)
        return None

def main():
    genre = sys.argv[1]
    upload_cid = sys.argv[2]
    hymn = sys.argv[3]
    desc = GENRE_DESC[genre]
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9333")
        page = get_page(b)
        # goto song page (fresh load)
        page.goto(f"https://suno.com/song/{upload_cid}", wait_until="load", timeout=40000)
        page.wait_for_timeout(8000)
        # open More menu via focus+enter
        try:
            page.focus('button[aria-label="More menu contents"]')
            page.keyboard.press("Enter")
        except Exception:
            pass
        page.wait_for_timeout(3000)
        # click Remix (re-acquire page if needed)
        try:
            page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],button')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='remix')[0]?.click()")
        except Exception:
            page = get_page(b)
        page.wait_for_timeout(3000)
        # click Cover
        try:
            page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],button,div')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='cover')[0]?.click()")
        except Exception:
            page = get_page(b)
        # wait for /create
        try:
            page.wait_for_url("**/create**", timeout=20000)
        except Exception:
            page = get_page(b)
            page.wait_for_timeout(3000)
        page.wait_for_timeout(8000)
        # fill textarea
        try:
            tas = json.loads(page.evaluate("JSON.stringify(Array.from(document.querySelectorAll('textarea')).map((t,i)=>({i,ml:t.maxLength})))"))
        except Exception:
            page = get_page(b)
            tas = json.loads(page.evaluate("JSON.stringify(Array.from(document.querySelectorAll('textarea')).map((t,i)=>({i,ml:t.maxLength})))"))
        desc_i = next((t["i"] for t in tas if t["ml"] == 3000), 2)
        try:
            page.evaluate("(()=>{var i=" + str(desc_i) + ";var t=document.querySelectorAll('textarea')[i];var s=Object.getOwnPropertyDescriptor(HTMLTextAreaElement.prototype,'value').set;s.call(t," + json.dumps(desc) + ");t.dispatchEvent(new Event('input',{bubbles:true}));t.dispatchEvent(new Event('change',{bubbles:true}));return 'ok'})()")
        except Exception:
            page = get_page(b)
        page.wait_for_timeout(2000)
        # instrumental + create
        try:
            page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button,[role=switch],label')).find(x=>x.offsetParent&&/instrumental/i.test(x.innerText||x.getAttribute('aria-label')||''));if(b&&b.getAttribute('aria-pressed')!=='true'){b.click()}})()")
        except Exception:
            pass
        page.wait_for_timeout(1000)
        trig = time.strftime("%Y-%m-%dT%H:%M:%S", time.gmtime())
        try:
            page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&((x.getAttribute('aria-label')||'').toLowerCase().includes('create'))&&!/create new workspace/i.test(x.innerText||''));if(b){b.click();return 'ok'}return 'nf'})()")
            print("Create at " + trig, flush=True)
        except Exception:
            page = get_page(b)
        # poll for new clip
        tok = page.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}")
        hdr = {"Authorization": "Bearer " + str(tok)}
        want = desc[:20]
        target = None
        for _ in range(50):
            time.sleep(5)
            r = requests.get(SUNO + "/api/feed/?limit=15", headers=hdr, timeout=20)
            if r.status_code == 200:
                for c in (r.json() or []):
                    if c.get("model_name") != "chirp-auk":
                        continue
                    md = c.get("metadata", {})
                    if md.get("cover_clip_id") != upload_cid:
                        continue
                    cr = c.get("created_at", "")
                    if md.get("gpt_description_prompt", "")[:20] == want and cr >= trig[:-5] and c.get("status") == "complete":
                        target = c["id"]
                        print("new clip " + str(target)[:12], flush=True)
                        break
                if target:
                    break
        if not target:
            print("no clip found", flush=True)
            b.close()
            return
        # get duration + capture
        md_dur = 240
        for pg in range(0, 2):
            r = requests.get(SUNO + "/api/feed/?limit=50&page=" + str(pg), headers=hdr, timeout=20)
            if r.status_code != 200:
                break
            for c in (r.json() or []):
                if c.get("id") == target:
                    md_dur = c.get("metadata", {}).get("duration", 240)
        print("dur " + str(md_dur), flush=True)
        # play + record
        page.goto(f"https://suno.com/song/{target}", wait_until="load", timeout=30000)
        page.wait_for_timeout(8000)
        try:
            page.evaluate("Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent && (b.getAttribute('aria-label')||'').trim()==='Play' && b.getBoundingClientRect().y<500)[0]?.click()")
        except Exception:
            page = get_page(b)
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
            print("record err: " + d["err"], flush=True)
            b.close()
            return
        out = os.path.join(GEN_DIR, f"{hymn}_10x_{genre}_A_cover.mp3")
        tmpw = out.replace(".mp3", "_t.webm")
        with open(tmpw, "wb") as f:
            f.write(base64.b64decode(d["b64"]))
        subprocess.run([FFM, "-y", "-loglevel", "error", "-i", tmpw, "-c:a", "libmp3lame", "-b:a", "192k", out], check=True)
        os.remove(tmpw)
        # centroid check
        import numpy as np, tempfile as _tf
        tf = _tf.mktemp(suffix=".f32")
        subprocess.run([FFM, "-y", "-loglevel", "error", "-i", out, "-ac", "1", "-ar", "48000", "-f", "f32le", tf], capture_output=True)
        dd = np.frombuffer(open(tf, "rb").read(), dtype=np.float32)
        os.remove(tf)
        cents = []
        for i in range(0, len(dd) - 2048, 2048):
            sp = np.abs(np.fft.rfft(dd[i:i+2048] * np.hanning(2048)))
            fr = np.fft.rfftfreq(2048, 1/48000)
            if sp.sum() > 0:
                cents.append((sp * fr).sum() / sp.sum())
        c = round(float(np.mean(cents)), 1) if cents else 0
        print("RESULT centroid=" + str(c) + (" OK" if c > 2000 else " DEGRADED"), flush=True)
        b.close()

if __name__ == "__main__":
    main()
