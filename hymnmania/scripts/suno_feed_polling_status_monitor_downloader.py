import os
import sys
import time
import json
import urllib.request
import requests
import websocket

SUNO_BASE = "https://studio-api-prod.suno.com"

def get_ws_url():
    pages = json.load(urllib.request.urlopen("http://127.0.0.1:9222/json"))
    for p in pages:
        if "suno.com" in p.get("url", "") and "stripe" not in p.get("url", ""):
            return p["webSocketDebuggerUrl"].replace("localhost", "127.0.0.1")
    return pages[0]["webSocketDebuggerUrl"].replace("localhost", "127.0.0.1")

def js(ws_url, expr):
    try:
        ws = websocket.create_connection(ws_url, suppress_origin=True, timeout=5)
        ws.send(json.dumps({
            "id": 2,
            "method": "Runtime.evaluate",
            "params": {
                "expression": expr,
                "returnByValue": True,
                "awaitPromise": True
            }
        }))
        for _ in range(15):
            r = ws.recv()
            d = json.loads(r)
            if d.get("id") == 2:
                val = d.get("result", {}).get("result", {}).get("value")
                ws.close()
                return val
        ws.close()
    except Exception as e:
        pass
    return None

def poll_and_download(clip_ids, output_dir, hymn_name, speed_lbl, genre_name, suffix="instrumental"):
    ws_url = get_ws_url()
    token = js(ws_url, "async function t(){try{return await Clerk.session.getToken()}catch(e){return null}};t()")
    if not token:
        print("Error: Could not retrieve token.")
        return False

    hdr = {"Authorization": f"Bearer {token}", "User-Agent": "Mozilla/5.0"}
    os.makedirs(output_dir, exist_ok=True)
    
    downloaded_all = True
    for vi, vid in enumerate(clip_ids):
        vlabel = ["A", "B"][vi % 2]
        print(f"Polling status of clip: {vid} (Version {vlabel})...")
        success = False
        for attempt in range(100):
            time.sleep(4)
            r2 = requests.get(f"{SUNO_BASE}/api/clip/{vid}/", headers=hdr)
            if r2.status_code == 200:
                d = r2.json()
                status = d.get("status", "")
                audio_url = d.get("audio_url", "")
                if status == "complete" and audio_url:
                    # Tag validation
                    model_name = d.get("model_name", "")
                    is_cover = d.get("parent_id") is not None or d.get("is_cover") == True or "cover" in str(d).lower()
                    print(f"  [VERIFICATION] Clip {vid} complete. Model: {model_name}, Is Cover: {is_cover}")
                    
                    if "v5.5" not in str(model_name) and not is_cover:
                        print("  [WARNING] Track does not match v5.5 or cover tags. Continuing download anyway.")

                    print(f"Downloading audio...")
                    dl = requests.get(audio_url, timeout=120, stream=True)
                    if dl.status_code == 200:
                        out_path = os.path.join(output_dir, f"{hymn_name}_{speed_lbl}_{genre_name}_{suffix}_{vlabel}_cover.mp3")
                        with open(out_path, "wb") as f:
                            for chunk in dl.iter_content(chunk_size=65536):
                                f.write(chunk)
                        print(f"Downloaded cover: {out_path}")
                        success = True
                        break
                elif status in ("error", "failed"):
                    print(f"Clip {vid} failed in generation.")
                    break
        if not success:
            downloaded_all = False
            
    return downloaded_all

if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("clip_ids")
    parser.add_argument("output_dir")
    parser.add_argument("hymn_name")
    parser.add_argument("speed_lbl")
    parser.add_argument("genre")
    parser.add_argument("--suffix", default="instrumental")
    args = parser.parse_args()

    clip_list = args.clip_ids.split(",")
    success = poll_and_download(clip_list, args.output_dir, args.hymn_name, args.speed_lbl, args.genre, suffix=args.suffix)
    sys.exit(0 if success else 1)
