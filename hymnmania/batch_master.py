"""ULTIMATE BATCH PIPELINE - MIDI → Cover → Beat Video → YouTube
Processes multiple hymns across all genres at all accepted speeds.
Fully automated with Edge CDP (port 9222 required).

Usage: python batch_master.py
"""
import os, sys, time, json, mido, numpy as np, requests as req, random, glob, subprocess as sp
from scipy.io import wavfile
from playwright.sync_api import sync_playwright

ROOT = os.path.dirname(os.path.abspath(__file__))
INPUT_DIR = os.path.join(ROOT, "hymn_remaker", "input")
FFMPEG = "ffmpeg"
SUNO_BASE = "https://studio-api.prod.suno.com"
GEN_DIR = os.path.join(ROOT, "generated")
MP3_DIR = os.path.join(ROOT, "mp3_input")
CF = sp.CREATE_NO_WINDOW if hasattr(sp, "CREATE_NO_WINDOW") else 0

os.makedirs(GEN_DIR, exist_ok=True)
os.makedirs(MP3_DIR, exist_ok=True)

GENRES = ["psytrance", "deep_house", "drum_and_bass", "gabba", "dubstep",
          "chiptune", "synthwave", "hardstyle", "detroit_techno", "detroit_house"]

# Top 5 hymns to process
HYMNS = [
    ("117 - Oh God Our Help In Ages Past.mid", "Oh God Our Help"),
    ("Just Over The Mountains 642(Sa Kabila ng mga Kabundukan 232).mid", "Just Over The Mountains"),
    ("Jesus Comes With Power to Gladden(Pag Sumilang na ang Pag-ibig 34).mid", "Jesus Comes With Power"),
    ("O Happy Day! That Fixed My Choice (O Masayang Araw Ngayon).mid", "O Happy Day"),
    ("When Love Shines In (Pag Sumilang Na Ang Pag-i-big 33).mid", "When Love Shines In"),
]

SPEEDS = [(0.5, "05x"), (1.0, "10x")]  # Start with these, add more if accepted

PITCH_FACTORS = {
    0.5: {"r": 0.8909, "t": 1.1225}, 1.0: {"r": 1.0595, "t": 0.9439},
    1.5: {"r": 0.9439, "t": 1.0595}, 2.0: {"r": 1.1225, "t": 0.8909},
    3.0: {"r": 1.1892, "t": 0.8409},
}


def render_midi(midi_name, hymn_title):
    """Render MIDI to WAV - uses proven algorithm from generate_sine_cover.py."""
    wav_path = os.path.join(MP3_DIR, hymn_title.replace(" ", "_") + ".wav")
    if os.path.exists(wav_path) and os.path.getsize(wav_path) > 1000:
        # Check duration
        r = sp.run(["ffprobe", "-v", "error", "-show_entries", "format=duration",
                     "-of", "default=noprint_wrappers=1:nokey=1", wav_path],
                    capture_output=True, text=True)
        try:
            if float(r.stdout.strip()) > 10:
                return wav_path
        except:
            pass
    
    midi_path = None
    for root, dirs, files in os.walk(INPUT_DIR):
        for f in files:
            if f == midi_name:
                midi_path = os.path.join(root, f)
                break
        if midi_path:
            break
    if not midi_path:
        print(f"  MIDI not found: {midi_name}")
        return None
    
    print(f"  Rendering: {midi_name}...")
    mid = mido.MidiFile(midi_path)
    events = []
    current_time = 0.0
    for msg in mid:
        current_time += msg.time
        if msg.type == "note_on" and msg.velocity > 0:
            events.append({"type": "note_on", "note": msg.note, "velocity": msg.velocity, "time": current_time})
        elif msg.type == "note_off" or (msg.type == "note_on" and msg.velocity == 0):
            events.append({"type": "note_off", "note": msg.note, "time": current_time})
    
    notes = []
    active_notes = {}
    for ev in events:
        note = ev["note"]
        if ev["type"] == "note_on":
            if note in active_notes:
                s = active_notes[note]
                notes.append({"note": note, "start": s["time"], "end": ev["time"], "velocity": s["velocity"]})
            active_notes[note] = ev
        elif ev["type"] == "note_off" and note in active_notes:
            s = active_notes.pop(note)
            notes.append({"note": note, "start": s["time"], "end": ev["time"], "velocity": s["velocity"]})
    for note, s in active_notes.items():
        notes.append({"note": note, "start": s["time"], "end": current_time, "velocity": s["velocity"]})
    
    if not notes:
        print("  No notes!")
        return None
    
    max_time = max(n["end"] for n in notes) + 0.5
    sr = 44100
    audio = np.zeros(int(max_time * sr), dtype=np.float32)
    for n in notes:
        freq = 440.0 * (2.0 ** ((n["note"] - 69) / 12.0))
        s0 = int(n["start"] * sr)
        s1 = int(n["end"] * sr)
        dur = s1 - s0
        if dur <= 0:
            continue
        t_arr = np.arange(dur) / sr
        amp = (n["velocity"] / 127.0) * 0.15
        env = np.ones(dur, dtype=np.float32)
        fl = min(int(0.01 * sr), dur // 2)
        if fl > 0:
            env[:fl] = np.linspace(0, 1, fl)
            env[-fl:] = np.linspace(1, 0, fl)
        audio[s0:s1] += amp * np.sin(2.0 * np.pi * freq * t_arr) * env
    
    peak = np.max(np.abs(audio))
    if peak > 0:
        audio = audio / peak * 0.9
    wavfile.write(wav_path, sr, (audio * 32767).astype(np.int16))
    print(f"  WAV: {os.path.getsize(wav_path)//1024}KB, {max_time:.0f}s")
    return wav_path


def prepare_mp3(wav_path, speed):
    """Pitch-shift + MP3 for copyright bypass."""
    mp3_path = wav_path.replace(".wav", f"_{speed}x.mp3")
    if os.path.exists(mp3_path):
        return mp3_path
    
    pf = PITCH_FACTORS.get(speed, {"r": 1.0595, "t": 0.9439})
    sp.run([
        FFMPEG, "-y", "-i", wav_path,
        "-af", f"asetrate=44100*{pf['r']},atempo={pf['t']},aresample=44100,lowpass=f=3500,highpass=f=120,adelay=400|400",
        "-codec:a", "libmp3lame", "-b:a", "128k", mp3_path
    ], capture_output=True, text=True, timeout=60, creationflags=CF)
    return mp3_path if os.path.exists(mp3_path) else wav_path


def run_batch():
    print("=" * 60)
    print("ULTIMATE BATCH PIPELINE")
    print("=" * 60)
    
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        suno = [p for p in b.contexts[0].pages if "suno.com" in p.url and "handshake" not in p.url][0]
        token = suno.evaluate(
            "(async function(){try{return await Clerk.session.getToken()}catch(e){return null}})()"
        )
        hdr = {"Authorization": f"Bearer {token}"}
        
        for midi_name, hymn_title in HYMNS:
            print(f"\n{'='*60}")
            print(f"HYMN: {hymn_title}")
            print(f"{'='*60}")
            
            wav = render_midi(midi_name, hymn_title)
            if not wav:
                continue
            
            for speed_val, speed_lbl in SPEEDS:
                mp3 = prepare_mp3(wav, speed_val)
                if not mp3:
                    continue
                
                print(f"\n  Speed {speed_val}x:")
                
                # Upload
                suno.goto("https://suno.com/create")
                suno.wait_for_timeout(8000)
                suno.evaluate(
                    'Array.from(document.querySelectorAll("button")).find(x=>(x.getAttribute("aria-label")||"").includes("Add audio"))?.click()'
                )
                suno.wait_for_timeout(3000)
                suno.evaluate(
                    'Array.from(document.querySelectorAll("*")).find(e=>e.offsetParent&&e.textContent.trim()==="Browse, upload, or record audio")?.click()'
                )
                suno.wait_for_timeout(2000)
                
                with suno.expect_file_chooser(timeout=15000) as fc:
                    suno.evaluate("document.querySelector('input[type=file]')?.click()")
                fc.value.set_files(os.path.abspath(mp3))
                suno.wait_for_timeout(5000)
                
                # Modals
                upload_ok = False
                for i in range(45):
                    suno.wait_for_timeout(2000)
                    body = suno.evaluate("document.body.innerText.toLowerCase().substring(0,1000)")
                    if "identify" in body:
                        suno.evaluate(
                            """(()=>{var o=Array.from(document.querySelectorAll('span,p,div,label,button')).filter(e=>e.offsetParent&&/full song|instrumental/i.test(e.textContent||''));o.forEach(e=>e.click());setTimeout(()=>{var c=Array.from(document.querySelectorAll('button')).find(b=>b.offsetParent&&b.textContent.trim()==='Continue');if(c)c.click()},500)})()"""
                        )
                    elif "describe" in body and "identify" not in body:
                        suno.evaluate(
                            """(()=>{var t=Array.from(document.querySelectorAll('textarea'));var n=Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype,'value').set;var a=t.find(x=>x.offsetParent);if(a){n.call(a,'hymn');a.dispatchEvent(new Event('input',{bubbles:true}))}setTimeout(()=>{var c=Array.from(document.querySelectorAll('button')).find(b=>b.offsetParent&&b.textContent.trim()==='Continue');if(c)c.click()},500)})()"""
                        )
                    elif "copyright" in body or "matches an existing" in body:
                        break
                    else:
                        is_m = suno.evaluate(
                            "!!Array.from(document.querySelectorAll('span,p,div,label,button,h2')).find(x=>(/identify|describe/i.test(x.textContent||'')))"
                        )
                        if not is_m:
                            upload_ok = True
                            break
                
                if not upload_ok:
                    print("    Upload failed, trying next speed...")
                    continue
                
                # Find upload clip
                upload_cid = None
                for _ in range(15):
                    time.sleep(3)
                    r = req.get(f"{SUNO_BASE}/api/feed/?limit=10", headers=hdr)
                    if r.status_code == 200:
                        clips = r.json() if isinstance(r.json(), list) else r.json().get("clips", [])
                        for c in clips:
                            if f"sine_{speed_lbl}" in c.get("title", "").lower() or c.get("title") == "hymn":
                                upload_cid = c.get("id")
                                break
                        if upload_cid:
                            break
                
                if not upload_cid:
                    print("    No clip ID")
                    continue
                
                print(f"    Uploaded: {upload_cid[:24]}...")
                
                # Generate covers
                for genre in GENRES:
                    label_a = os.path.join(GEN_DIR, f"{hymn_title.replace(' ','_')}_{speed_lbl}_{genre}_A_cover.mp3")
                    if os.path.exists(label_a) and os.path.getsize(label_a) > 1000000:
                        continue  # Already done
                    
                    print(f"      {genre}...")
                    suno.goto(f"https://suno.com/song/{upload_cid}")
                    suno.wait_for_timeout(6000)
                    
                    # Click Create Cover
                    for a in range(10):
                        suno.wait_for_timeout(1500)
                        r = suno.evaluate(
                            """(()=>{var b=Array.from(document.querySelectorAll("button")).filter(x=>x.offsetParent);var c=b.find(x=>(x.innerText||"").toLowerCase().includes("create cover")||(x.innerText||"").toLowerCase().includes("cover this"));if(c){c.click();return"ok"}var m=b.find(x=>(x.getAttribute("aria-label")||"").toLowerCase().includes("more"));if(m){m.click();return"menu"}return"nf"})()"""
                        )
                        if r == "ok":
                            suno.wait_for_timeout(4000)
                            break
                        elif r == "menu":
                            time.sleep(1)
                            r2 = suno.evaluate(
                                """(()=>{var i=Array.from(document.querySelectorAll("[role=menuitem],li")).filter(x=>x.offsetParent);var c=i.find(x=>/cover/i.test(x.textContent||""));if(c){c.click();return"ok"}return"no"})()"""
                            )
                            if r2 == "ok":
                                suno.wait_for_timeout(4000)
                                break
                    
                    # Map and fill textareas
                    tas = suno.evaluate(
                        "JSON.stringify(Array.from(document.querySelectorAll('textarea')).map(function(t,i){return{idx:i,ph:(t.placeholder||'').substring(0,40)}}))"
                    )
                    ta = json.loads(tas)
                    desc_i = next((t["idx"] for t in ta if "create" in t["ph"].lower() or "song" in t["ph"].lower()), 0)
                    style_i = desc_i + 1 if len(ta) > 1 else 0
                    
                    suno.evaluate(
                        f'(function(){{var t=document.querySelectorAll("textarea");var n=Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype,"value").set;n.call(t[{desc_i}],"{genre}");t[{desc_i}].dispatchEvent(new Event("input",{{bubbles:true}}));t[{desc_i}].dispatchEvent(new Event("change",{{bubbles:true}}))}})()'
                    )
                    suno.evaluate(
                        f'(function(){{var t=document.querySelectorAll("textarea");var n=Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype,"value").set;n.call(t[{style_i}],"{genre}");t[{style_i}].dispatchEvent(new Event("input",{{bubbles:true}}));t[{style_i}].dispatchEvent(new Event("change",{{bubbles:true}}))}})()'
                    )
                    suno.wait_for_timeout(1500)
                    
                    # Snapshot
                    existing = set()
                    r = req.get(f"{SUNO_BASE}/api/feed/?limit=10", headers=hdr)
                    if r.status_code == 200:
                        clips = r.json() if isinstance(r.json(), list) else r.json().get("clips", [])
                        existing = {c["id"] for c in clips}
                    
                    # Create
                    suno.evaluate(
                        """(()=>{var b=Array.from(document.querySelectorAll("button")).find(x=>x.offsetParent&&((x.getAttribute("aria-label")||"").toLowerCase().includes("create")||(x.textContent||"").toLowerCase().trim()==="create"));if(b)b.click()})()"""
                    )
                    suno.wait_for_timeout(15000)
                    
                    # Poll
                    found = []
                    for _ in range(40):
                        time.sleep(3)
                        r = req.get(f"{SUNO_BASE}/api/feed/?limit=10", headers=hdr)
                        if r.status_code == 200:
                            clips = r.json() if isinstance(r.json(), list) else r.json().get("clips", [])
                            for c in clips:
                                cid = c.get("id")
                                if cid and cid not in existing and cid not in [f["id"] for f in found]:
                                    found.append(c)
                            if len(found) >= 2:
                                break
                    
                    if not found:
                        continue
                    
                    # Download
                    for vi, clip in enumerate(found[:2]):
                        vid = clip["id"]
                        label = ["A", "B"][vi]
                        for i in range(60):
                            time.sleep(2)
                            r2 = req.get(f"{SUNO_BASE}/api/clip/{vid}/", headers=hdr)
                            if r2.status_code == 200:
                                d = r2.json()
                                if d.get("status") == "complete" and d.get("audio_url"):
                                    dl = req.get(d["audio_url"], timeout=120, stream=True)
                                    if dl.status_code == 200:
                                        out = os.path.join(GEN_DIR, f"{hymn_title.replace(' ','_')}_{speed_lbl}_{genre}_{label}_cover.mp3")
                                        with open(out, "wb") as f:
                                            for c in dl.iter_content(65536):
                                                f.write(c)
                                        dur = d.get("metadata", {}).get("duration", "?")
                                        tags = d.get("metadata", {}).get("tags", "")[:50]
                                        print(f"        {label}: {os.path.getsize(out)//1024}KB {dur}s | {tags}")
                                    break
                                elif d.get("status") in ("error", "failed"):
                                    break
        
        b.close()
    print(f"\n{'='*60}")
    print("BATCH PIPELINE COMPLETE!")
    print(f"{'='*60}")


if __name__ == "__main__":
    run_batch()
