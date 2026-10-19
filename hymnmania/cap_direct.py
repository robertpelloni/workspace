import sys, os, json, time, base64, subprocess, requests
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright
FFM = r"C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe"

def get_page(b):
    for p in b.contexts[0].pages:
        if "suno.com" in p.url:
            return p
    return b.contexts[0].new_page()

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
    cid = sys.argv[1]
    out = sys.argv[2]  # output mp3 path
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9333")
        page = get_page(b)
        page.goto(f"https://suno.com/song/{cid}", wait_until="domcontentloaded", timeout=30000)
        page.wait_for_timeout(8000)
        # get duration from API
        tok = page.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}")
        hdr = {"Authorization": "Bearer " + str(tok)}
        md_dur = 240
        try:
            r = requests.get("https://studio-api-prod.suno.com/api/clip/" + cid + "/", headers=hdr, timeout=20)
            if r.status_code == 200:
                md_dur = r.json().get("metadata", {}).get("duration", 240)
        except Exception:
            pass
        print("dur", md_dur, flush=True)
        # play
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
        res = page.evaluate(js, int(md_dur * 1000) + 6000)
        d = json.loads(res)
        if "err" in d:
            print("record err:", d["err"], flush=True)
            b.close()
            return False
        tmpw = out.replace(".mp3", "_t.webm")
        with open(tmpw, "wb") as f:
            f.write(base64.b64decode(d["b64"]))
        subprocess.run([FFM, "-y", "-loglevel", "error", "-i", tmpw, "-c:a", "libmp3lame", "-b:a", "192k", out], check=True)
        os.remove(tmpw)
        c = centroid(out)
        print("RESULT centroid=" + str(c) + (" OK" if c > 2000 else " DEGRADED") + " size=" + str(os.path.getsize(out)//1024) + "KB", flush=True)
        b.close()
        return c > 2000

if __name__ == "__main__":
    ok = main()
    print("SUCCESS: " + str(ok))
