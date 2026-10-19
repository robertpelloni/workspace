"""DEFINITIVE BATCH COVER GENERATOR
Uses the proven More -> Remix -> Cover flow (documented in AGENTS.md)
Connects to Edge CDP on port 9222.

Flow:
1. Find upload clips in Suno feed (model_name: chirp-fenix or chirp-chirp)
2. Navigate to suno.com/song/{id}
3. More menu -> Remix -> Cover
4. Fill genre in textareas (indices 2 and 3)
5. Click Create
6. Poll feed for new clips
7. Download completed covers

Usage: python batch_cover_gen.py [hymn_name] [genres_comma_separated]
"""
import os, sys, time, json, requests as req
from playwright.sync_api import sync_playwright

SUNO_BASE = "https://studio-api.prod.suno.com"
ROOT = os.path.dirname(os.path.abspath(__file__))
GEN_DIR = os.path.join(ROOT, "generated")
os.makedirs(GEN_DIR, exist_ok=True)

ALL_GENRES = ["psytrance", "deep_house", "drum_and_bass", "gabba", "dubstep",
              "chiptune", "synthwave", "hardstyle", "detroit_techno", "detroit_house"]


def find_upload_clips(hdr):
    """Find all upload clips in the feed (sine variants)."""
    uploads = {}
    for page_n in range(1, 5):
        r = req.get(f"{SUNO_BASE}/api/feed/?page={page_n}", headers=hdr)
        if r.status_code != 200:
            continue
        clips = r.json() if isinstance(r.json(), list) else r.json().get("clips", [])
        for c in clips:
            title = c.get("title", "")
            model = c.get("model_name", "")
            cid = c.get("id", "")
            # Any sine upload clip
            is_sine = "sine" in title.lower()
            if not is_sine:
                continue
            if not model:
                continue  # Require model info
            # Parse hymn and speed
            if "_sine_" in title:
                parts = title.split("_sine_")
                hymn = parts[0].replace("_", " ")
                speed = parts[1][:3]
            else:
                hymn = title.split("_")[0]
                speed = "unknown"
                key = f"{hymn}_{speed}"
                if key not in uploads:
                    uploads[key] = {"id": cid, "title": title, "hymn": hymn, "speed": speed}
    return uploads


def generate_cover(page, hdr, upload_cid, hymn_name, speed, genre):
    """Generate one cover using More->Remix->Cover flow."""
    out_a = os.path.join(GEN_DIR, f"{hymn_name.replace(' ','_')}_{speed}_{genre}_A_cover.mp3")
    out_b = os.path.join(GEN_DIR, f"{hymn_name.replace(' ','_')}_{speed}_{genre}_B_cover.mp3")
    
    if os.path.exists(out_a) and os.path.getsize(out_a) > 1000000:
        return True  # Already done
    
    print(f"  {genre}...")
    
    # Navigate to song page
    page.goto(f"https://suno.com/song/{upload_cid}")
    page.wait_for_timeout(6000)
    
    # More menu (three dots)
    page.evaluate(
        'Array.from(document.querySelectorAll("button,[role=button],[aria-label]")).find(x=>(x.getAttribute("aria-label")||x.innerText||"").toLowerCase().includes("more")&&x.offsetParent)?.click()'
    )
    page.wait_for_timeout(2500)
    
    # Remix (opens dropdown with Cover option)
    page.evaluate(
        'Array.from(document.querySelectorAll("[role=menuitem],li,button,[role=button]")).find(x=>x.offsetParent&&(x.innerText||x.textContent||"").trim().toLowerCase()==="remix")?.click()'
    )
    page.wait_for_timeout(2500)
    
    # Cover (in Remix dropdown)
    page.evaluate(
        'Array.from(document.querySelectorAll("[role=menuitem],li,button,[role=button],span,div")).find(x=>x.offsetParent&&(x.innerText||x.textContent||"").trim().toLowerCase()==="cover")?.click()'
    )
    page.wait_for_timeout(4000)
    
    # Map textareas (indices 2 and 3 in current Suno UI)
    tas = page.evaluate(
        "JSON.stringify(Array.from(document.querySelectorAll('textarea')).map(function(t,i){return{idx:i,ph:(t.placeholder||'').substring(0,40)}}))"
    )
    ta = json.loads(tas)
    desc_i = next((t["idx"] for t in ta if "create" in t["ph"].lower() or "song" in t["ph"].lower() or t["idx"] == 2), 2)
    style_i = desc_i + 1 if len(ta) > desc_i + 1 else desc_i
    
    # Fill BOTH textareas with genre
    for idx in [desc_i, style_i]:
        if idx < len(ta):
            page.evaluate(
                f'(function(){{var t=document.querySelectorAll("textarea");var n=Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype,"value").set;n.call(t[{idx}],"{genre}");t[{idx}].dispatchEvent(new Event("input",{{bubbles:true}}))}})()'
            )
    page.wait_for_timeout(1500)
    
    # Snapshot existing clips
    existing = set()
    r = req.get(f"{SUNO_BASE}/api/feed/?limit=10", headers=hdr)
    if r.status_code == 200:
        clips = r.json() if isinstance(r.json(), list) else r.json().get("clips", [])
        existing = {c["id"] for c in clips}
    
    # Click Create
    page.evaluate(
        """(()=>{var b=Array.from(document.querySelectorAll("button")).find(x=>x.offsetParent&&((x.getAttribute("aria-label")||"").toLowerCase().includes("create")||(x.textContent||"").toLowerCase().trim()==="create"));if(b)b.click()})()"""
    )
    page.wait_for_timeout(15000)
    
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
        return False
    
    # Download
    for vi, clip in enumerate(found[:2]):
        vid = clip["id"]
        label = ["A", "B"][vi]
        out_path = os.path.join(GEN_DIR, f"{hymn_name.replace(' ','_')}_{speed}_{genre}_{label}_cover.mp3")
        
        for i in range(60):
            time.sleep(2)
            r2 = req.get(f"{SUNO_BASE}/api/clip/{vid}/", headers=hdr)
            if r2.status_code == 200:
                d = r2.json()
                if d.get("status") == "complete" and d.get("audio_url"):
                    dl = req.get(d["audio_url"], timeout=120, stream=True)
                    if dl.status_code == 200:
                        with open(out_path, "wb") as f:
                            for c in dl.iter_content(65536):
                                f.write(c)
                        dur = d.get("metadata", {}).get("duration", "?")
                        tags = d.get("metadata", {}).get("tags", "")[:50]
                        print(f"    {label}: {os.path.getsize(out_path)//1024}KB {dur}s | {tags}")
                    break
                elif d.get("status") in ("error", "failed"):
                    break
    return True


def run(hymn_filter=None, genres=None):
    if genres is None:
        genres = ALL_GENRES
    
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        pg = [p for p in b.contexts[0].pages if "suno.com" in p.url and "handshake" not in p.url][0]
        token = pg.evaluate(
            "(async function(){try{return await Clerk.session.getToken()}catch(e){return null}})()"
        )
        hdr = {"Authorization": f"Bearer {token}"}
        
        # Find available uploads
        uploads = find_upload_clips(hdr)
        if hymn_filter:
            uploads = {k: v for k, v in uploads.items() if hymn_filter.lower() in k.lower()}
        
        print(f"Found {len(uploads)} upload clips:")
        for key, info in sorted(uploads.items()):
            print(f"  {info['hymn']} ({info['speed']}): {info['id'][:24]}...")
        
        for key, info in sorted(uploads.items()):
            hymn = info["hymn"]
            speed = info["speed"]
            uid = info["id"]
            
            print(f"\n=== {hymn} ({speed}) ===")
            
            for genre in genres:
                generate_cover(pg, hdr, uid, hymn, speed, genre)
        
        b.close()
    print("\nDONE")


if __name__ == "__main__":
    hymn = sys.argv[1] if len(sys.argv) > 1 else None
    genres = sys.argv[2].split(",") if len(sys.argv) > 2 else ALL_GENRES
    run(hymn, genres)
