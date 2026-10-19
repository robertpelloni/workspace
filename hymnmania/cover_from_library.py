"""BATCH COVER GENERATOR - Uses existing uploads in Suno library.
No file upload needed - clicks Remix/Cover on existing clips.
"""
import os, sys, time, json, requests as req, random
from playwright.sync_api import sync_playwright

SUNO_BASE = "https://studio-api.prod.suno.com"
GEN_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "generated")
os.makedirs(GEN_DIR, exist_ok=True)

GENRES = ["psytrance", "deep_house", "drum_and_bass", "gabba", "dubstep",
          "chiptune", "synthwave", "hardstyle", "detroit_techno", "detroit_house"]

def generate_from_existing(hymn_title="Thy_Word", n_genres=None):
    """Generate covers from existing upload clips in the Suno uploads panel."""
    if n_genres is None:
        genres_to_run = GENRES
    else:
        genres_to_run = random.sample(GENRES, min(n_genres, len(GENRES)))
    
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        pg = [p for p in b.contexts[0].pages if "suno.com" in p.url and "handshake" not in p.url][0]
        token = pg.evaluate(
            "(async function(){try{return await Clerk.session.getToken()}catch(e){return null}})()"
        )
        hdr = {"Authorization": f"Bearer {token}"}
        
        for genre in genres_to_run:
            out_path = os.path.join(GEN_DIR, f"{hymn_title}_05x_{genre}_A_cover.mp3")
            if os.path.exists(out_path) and os.path.getsize(out_path) > 1000000:
                print(f"  {genre}: already done")
                continue
            
            print(f"\n=== {genre} ===")
            
            # Go to create page and open uploads panel
            pg.goto("https://suno.com/create")
            pg.wait_for_timeout(8000)
            
            # Click Add audio to open uploads panel
            pg.evaluate(
                'Array.from(document.querySelectorAll("button")).find(x=>(x.getAttribute("aria-label")||"").includes("Add audio"))?.click()'
            )
            pg.wait_for_timeout(3000)
            
            # Click on a Thy_Word upload clip
            pg.evaluate(
                """(()=>{var clips=Array.from(document.querySelectorAll('[aria-label=\"Select clip\"]'));for(var c of clips){var p=c.closest('[role=\"listitem\"],div');if(p&&(p.innerText||'').includes('Thy_Word')&&(p.innerText||'').includes('sine')){c.click();return'ok'}}return'nf'})()"""
            )
            pg.wait_for_timeout(2000)
            
            # Click Remix button
            pg.evaluate(
                'Array.from(document.querySelectorAll("button")).find(x=>x.offsetParent&&(x.getAttribute("aria-label")||"").includes("Remix"))?.click()'
            )
            pg.wait_for_timeout(2000)
            
            # In Remix menu, click Cover
            pg.evaluate(
                'Array.from(document.querySelectorAll("[role=\"menuitem\"],li,button")).find(x=>x.offsetParent&&(x.innerText||"").toLowerCase().includes("cover"))?.click()'
            )
            pg.wait_for_timeout(4000)
            
            # Fill genre in textareas
            tas = pg.evaluate(
                "JSON.stringify(Array.from(document.querySelectorAll('textarea')).map(function(t,i){return{idx:i,ph:(t.placeholder||'').substring(0,40)}}))"
            )
            ta = json.loads(tas)
            desc_i = next((t["idx"] for t in ta if "create" in t["ph"].lower() or "song" in t["ph"].lower()), 0)
            style_i = desc_i + 1 if len(ta) > 1 else 0
            
            pg.evaluate(
                f'(function(){{var t=document.querySelectorAll("textarea");var n=Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype,"value").set;n.call(t[{desc_i}],"{genre}");t[{desc_i}].dispatchEvent(new Event("input",{{bubbles:true}}))}})()'
            )
            pg.evaluate(
                f'(function(){{var t=document.querySelectorAll("textarea");var n=Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype,"value").set;n.call(t[{style_i}],"{genre}");t[{style_i}].dispatchEvent(new Event("input",{{bubbles:true}}))}})()'
            )
            pg.wait_for_timeout(1500)
            
            # Snapshot feed
            existing = set()
            r = req.get(f"{SUNO_BASE}/api/feed/?limit=10", headers=hdr)
            if r.status_code == 200:
                clips = r.json() if isinstance(r.json(), list) else r.json().get("clips", [])
                existing = {c["id"] for c in clips}
            
            # Click Create
            pg.evaluate(
                """(()=>{var b=Array.from(document.querySelectorAll("button")).find(x=>x.offsetParent&&((x.getAttribute("aria-label")||"").toLowerCase().includes("create")||(x.textContent||"").toLowerCase().trim()==="create"));if(b)b.click()})()"""
            )
            print("  Create clicked")
            pg.wait_for_timeout(15000)
            
            # Poll for new clips
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
                print("  No clips found")
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
                                out = os.path.join(GEN_DIR, f"{hymn_title}_05x_{genre}_{label}_cover.mp3")
                                with open(out, "wb") as f:
                                    for c in dl.iter_content(65536):
                                        f.write(c)
                                dur = d.get("metadata", {}).get("duration", "?")
                                tags = d.get("metadata", {}).get("tags", "")[:60]
                                gpt = d.get("metadata", {}).get("gpt_description_prompt", "")[:40]
                                model = d.get("metadata", {}).get("model_version", "?")
                                print(f"  {label}: {os.path.getsize(out)//1024}KB {dur}s | {model} | {tags} | gpt={gpt}")
                            break
                        elif d.get("status") in ("error", "failed"):
                            print(f"  {label}: failed")
                            break
        
        b.close()
        return True

if __name__ == "__main__":
    generate_from_existing("Thy_Word")
