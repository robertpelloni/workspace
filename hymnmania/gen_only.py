"""Clean cover-generation (no capture) on the dedicated browser.
Usage: python gen_only.py <genre_key> <upload_clip_id> <hymn_name>
Prints the new clip IDs when generation completes.

2026-09-23 rewrite: Suno changed the cover flow. The song menu now has "Create"
(an <a>, not a button) which navigates to /create with the clip as reference, and the
submit button is aria-label="Generate" (not "Create").
"""
import sys, os, json, time, requests
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

SUNO = "https://studio-api-prod.suno.com"

GENRE_DESC = {
    "deep_house": "deep house, warm analog chords, rolling syncopated bassline, four-on-the-floor kick at 122 BPM, hypnotic groove, soulful late-night warehouse feel",
    "synthwave": "synthwave, warm analog polysynths, pulsing sidechained bassline, 100-110 BPM neon-drenched retro-future groove, 1980s nostalgia",
    "psytrance": "full-on psytrance, driving 142 BPM, bright euphoric melodies, punchy rolling bassline, cinematic sci-fi leads, energetic morning dancefloor",
    "psytrance_fullon": "full-on psytrance, 142 BPM, deep heavy sub-bass, punchy kick drum on every beat, rolling 16th-note bassline filling the gaps between kicks, hypnotic acid lead line, driving dancefloor groove, bass-heavy mix, festival main stage",
    "goa_trance": "goa trance, 135 BPM, complex melodic acid lines, warm organic analog synthesizers, layered hypnotic arpeggios, eastern-influenced psychedelic melodies, classic 1990s Goa energy",
    "psytrance_progressive": "progressive psytrance, 132 BPM, slower cleaner hypnotic groove, steady rolling bassline, deep spacious pads, gradual build-ups, daytime festival set",
    "psytrance_dark": "darkpsy, 150 BPM, fast aggressive nocturnal rolling bass, eerie chaotic sci-fi soundscapes, dissonant acid leads, menacing deep atmosphere, night-time dancing",
    "psytrance_forest": "forest psytrance, 143 BPM, organic earthy percussion, natural woodland sound effects, mysterious nocturnal atmosphere, twisted organic basslines, deep forest energy",
    "psytrance_hitech": "hi-tech psytrance, 165 BPM, extremely fast hyper-detailed rolling bass, rapid-fire glitch percussion, intense futuristic digital sound design, frantic psychedelic chaos",
    "psytrance_psychill": "psychill psybient, 105 BPM, ambient psychedelic chill-out, dub-influenced bass, lush atmospheric pads, downtempo meditative soundscapes, relaxing cosmic journey",
    "psytrance_zenonesque": "zenonesque, 130 BPM, dark funky minimalist psychedelic techno, deep off-beat basslines, groovy unconventional rhythms, hypnotic subtle evolution, Zenon Records style",
    "dubstep": "brostep dubstep, massive LFO wobble bass drops, half-time 140 BPM drums, growling midrange basses, festival-ready bass music",
    "chiptune": "chiptune, 8-bit square wave leads, arpeggios, triangle bass, noise percussion, retro video game soundtrack energy",
    "drum_and_bass": "drum and bass, fast 174 BPM breakbeats, rolling sub-bass, reese bass swells, chopped breaks, high-energy drum work",
    "gabba": "gabba hardcore, relentlessly distorted kick drums at 190 BPM, saturated low end, aggressive rave atmosphere",
    "hardstyle": "hardstyle trance, pounding distorted kicks at 150 BPM, supersaw leads, euphoric melodies, festival-ready energy",
    "japanese_hardcore_techno": "japanese hardcore techno, hyperactive 180 BPM distorted kick, kawaii rave supersaw leads, rapid-fire stabs, relentless Tokyo night energy",
    "detroit_techno": "detroit techno, minimal mechanical 130 BPM groove, analog synth stabs, industrial percussion, cold futuristic atmosphere, Motor City machine funk",
    "detroit_house": "detroit house, warm analog chords, soulful 122 BPM four-on-the-floor, lush strings, classic deep groove, vintage vinyl warmth",
}


def main():
    genre = sys.argv[1]
    upload_id = sys.argv[2]
    desc = GENRE_DESC[genre]
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9333")
        # use a clean NEW page (close stale suno pages first)
        for p in list(b.contexts[0].pages):
            if 'suno.com' in p.url:
                try:
                    p.close()
                except Exception:
                    pass
        time.sleep(1)
        page = b.contexts[0].new_page()
        page.goto("https://suno.com/song/" + upload_id, wait_until="domcontentloaded", timeout=40000)
        page.wait_for_timeout(8000)
        # 1) open the More options menu, click "Create" (an <a>, not a button)
        page.evaluate("Array.from(document.querySelectorAll('button')).find(x=>x.getAttribute('aria-label')==='More options')?.click()")
        page.wait_for_timeout(2500)
        r = page.evaluate("(()=>{var a=Array.from(document.querySelectorAll('a')).find(x=>(x.innerText||'').trim()==='Create');if(a){a.click();return 'ok'}return 'nf'})()")
        print("create link:", r, flush=True)
        # 2) wait for /create (the clip is passed as reference)
        try:
            page.wait_for_url("**/create**", timeout=25000)
        except Exception:
            pass
        page.wait_for_timeout(9000)
        print("on create:", page.url[:50], flush=True)
        # 3) fill the style description (prefer 'Describe the sound you want', ml 500)
        idx = page.evaluate("(()=>{var tas=Array.from(document.querySelectorAll('textarea'));var i=tas.findIndex(t=>(t.placeholder||'').toLowerCase().includes('describe'));if(i<0){i=tas.findIndex(t=>t.maxLength===500)}if(i<0){i=2}return i})()")
        page.evaluate("(()=>{var i=" + str(idx) + ";var t=document.querySelectorAll('textarea')[i];if(!t){return 'nf'}var s=Object.getOwnPropertyDescriptor(HTMLTextAreaElement.prototype,'value').set;s.call(t," + json.dumps(desc) + ");t.dispatchEvent(new Event('input',{bubbles:true}));t.dispatchEvent(new Event('change',{bubbles:true}));return 'ok'})()")
        page.wait_for_timeout(1500)
        print("desc:", desc[:40], flush=True)
        # 4) click Generate (aria-label="Generate")
        trig = time.strftime("%Y-%m-%dT%H:%M:%S", time.gmtime())
        r = page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>(x.getAttribute('aria-label')||'')==='Generate');if(b){b.click();return 'ok'}return 'nf'})()")
        print("Generate:", r, "at", trig, flush=True)
        # 5) poll for NEW cover clips (chirp-*) via the page's own JWT
        from suno_auth import get_jwt
        tok = get_jwt(page, navigate=False)
        hdr = {"Authorization": "Bearer " + str(tok)}
        found_ids = []
        if tok:
            for _ in range(50):
                time.sleep(5)
                try:
                    rq = requests.post(SUNO + "/api/feed/v3", headers=hdr, json={"page": 0}, timeout=20)
                except Exception:
                    continue
                if rq.status_code == 200:
                    clips = rq.json() if isinstance(rq.json(), list) else rq.json().get("clips", [])
                    for c in clips:
                        mn = c.get("model_name", "")
                        if not (mn.startswith("chirp-") and mn != "chirp-chirp"):
                            continue
                        cr = c.get("created_at", "")
                        if cr >= trig and c.get("status") == "complete":
                            cid = c["id"]
                            if cid not in found_ids:
                                found_ids.append(cid)
                                print("NEW CLIP:", cid, mn, cr, flush=True)
                    if len(found_ids) >= 2:
                        break
        print("CLIPS:" + ",".join(found_ids), flush=True)
        b.close()


if __name__ == "__main__":
    main()
