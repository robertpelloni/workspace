import os
import sys
import json
import urllib.request
import requests
import websocket

def check_edge_debugging():
    import socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(2)
    result = sock.connect_ex(("127.0.0.1", 9222))
    sock.close()
    return result == 0

def check_suno_tab():
    try:
        res = requests.get("http://127.0.0.1:9222/json", timeout=3)
        targets = res.json()
        for t in targets:
            if t.get("type") == "page" and "suno.com" in t.get("url", "").lower():
                return True, t.get("url")
        return False, None
    except Exception as e:
        print(f"Error checking targets: {e}")
        return False, None

def navigate_to_suno():
    try:
        res = requests.get("http://127.0.0.1:9222/json", timeout=3)
        targets = res.json()
        for t in targets:
            if t.get("type") == "page" and t.get("webSocketDebuggerUrl"):
                ws = websocket.create_connection(
                    t["webSocketDebuggerUrl"].replace("localhost", "127.0.0.1"),
                    suppress_origin=True, timeout=10
                )
                ws.send(json.dumps({
                    "id": 1, "method": "Page.navigate",
                    "params": {"url": "https://suno.com/create"}
                }))
                ws.recv()
                ws.close()
                print("Navigated browser page target to suno.com/create")
                return True
    except Exception as e:
        print(f"Error navigating: {e}")
    return False

def main():
    if not check_edge_debugging():
        print("Edge CDP port 9222 is closed.")
        sys.exit(1)
    print("Edge CDP port 9222 is open.")
    has_tab, url = check_suno_tab()
    if has_tab:
        print(f"Suno tab verified at: {url}")
        sys.exit(0)
    print("No active Suno tab found. Navigating to suno.com/create...")
    if navigate_to_suno():
        sys.exit(0)
    sys.exit(2)

if __name__ == "__main__":
    main()
