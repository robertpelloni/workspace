import subprocess, time, socket, os

subprocess.Popen([
    r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe",
    "--remote-debugging-port=9222",
    r"--user-data-dir=C:\Users\jakeg\edge-cdp-profile",
    "--no-first-run",
    "--no-default-browser-check",
    "https://suno.com/create"
])
time.sleep(12)

s = socket.socket()
s.settimeout(5)
try:
    s.connect(("127.0.0.1", 9222))
    print("PORT 9222 OPEN with fresh Edge profile!")
    import urllib.request, json
    pages = json.load(urllib.request.urlopen("http://127.0.0.1:9222/json"))
    for p in pages:
        print(" ", p.get("url","")[:100])
    s.close()
except Exception as e:
    print("Failed:", e)
    r = subprocess.run("tasklist", shell=True, capture_output=True, text=True)
    print(f"msedge: {r.stdout.count('msedge.exe')}, webview2: {r.stdout.count('msedgewebview2.exe')}")
