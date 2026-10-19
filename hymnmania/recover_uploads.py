"""Recover lost Suno upload IDs and backfill them into the throttle queue.

WHY: the 2026-09-21 queue rebuild dropped the upload_id field (the old queue stored the
generated cover clip, not the reference upload). So the throttle shows "uploaded: 0" even
though the hymns' reference uploads still exist in Suno. Re-uploading risks self-match, so
we recover the existing upload IDs from the feed instead.

The old upload naming was  `_thr_{hymn}_{genre}.wav`  (e.g. _thr_Adventist_Youth_psytrance_fullon),
so we match each hymn's FULL-ON upload (the one that actually succeeded) by title.

    python recover_uploads.py --check    # report only
    python recover_uploads.py            # backfill upload_id into .upload_queue.json
"""
import json, os, sys, re, time

sys.stdout.reconfigure(encoding="utf-8", errors="replace")
ROOT = os.path.dirname(os.path.abspath(__file__))
QUEUE = os.path.join(ROOT, ".upload_queue.json")
FEED = "https://studio-api-prod.suno.com/api/feed/v3"


def safe(h):
    return re.sub(r"[^A-Za-z0-9]+", "_", h).strip("_")


def get_uploads():
    """Return {title: id} for every '_thr_' reference upload in the feed."""
    import requests
    from playwright.sync_api import sync_playwright
    out = {}
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9333")
        cookies = {c["name"]: c["value"] for c in b.contexts[0].cookies()}
        sess = cookies.get("__session") or cookies.get("__session_Jnxw-muT")
        hdr = {"Authorization": "Bearer " + sess}
        for page in range(0, 40):
            try:
                r = requests.post(FEED, headers=hdr, json={"page": page}, timeout=20)
            except Exception:
                break
            if r.status_code != 200:
                break
            clips = r.json().get("clips", [])
            if not clips:
                break
            for c in clips:
                t = c.get("title", "")
                if t.startswith("_thr_") and c.get("entity_type") == "song_schema":
                    out[t] = c.get("id")
            if len(clips) < 20:
                break
            time.sleep(0.3)
        b.close()
    return out


def main():
    uploads = get_uploads()
    print(f"recovered {len(uploads)} _thr_ reference uploads from the feed")
    q = json.load(open(QUEUE, encoding="utf-8"))
    filled = 0
    for j in q:
        if j.get("upload_id"):
            continue
        h = j["hymn"]
        # try the full-on naming, then any other genre naming for this hymn
        for t, i in uploads.items():
            if t == f"_thr_{safe(h)}_psytrance_fullon" or t == f"_thr_{safe(h)}":
                j["upload_id"] = i
                filled += 1
                break
    if "--check" in sys.argv:
        todo = [j for j in q if not j.get("upload_id") and j.get("status") != "blocked"]
        print(f"  would backfill: {filled} upload ids")
        print(f"  still missing (fresh hymns to upload): {len(todo)}")
        return
    json.dump(q, open(QUEUE, "w", encoding="utf-8"), indent=1)
    uploaded = sum(1 for j in q if j.get("upload_id"))
    print(f"backfilled {filled} upload ids -> {uploaded}/{len(q)} hymns now have an upload reference")


if __name__ == "__main__":
    main()
