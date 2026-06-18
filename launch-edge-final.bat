@echo off
REM Launch Edge with CDP on 0.0.0.0:9222
cd /d "C:\Program Files (x86)\Microsoft\Edge\Application"
start "" msedge.exe --remote-debugging-port=9222 --remote-debugging-address=0.0.0.0 --user-data-dir="C:\Users\hyper\workspace\cdp-edge-final" --no-first-run --no-default-browser-check --remote-allow-origins=*
timeout /t 3 /nobreak >nul
netstat -an | findstr :9222
