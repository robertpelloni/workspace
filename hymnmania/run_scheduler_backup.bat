@echo off
REM ===================================================================
REM HymnMania BACKUP posting runner  (failover for "HymnMania Daily Post")
REM
REM Only posts if NOTHING was published today (checks .scheduler_log.json).
REM Safe to run repeatedly - it is a no-op once the day's post has happened.
REM
REM Registered as Windows Scheduled Tasks:
REM   "HymnMania Backup Post"      -> weekdays 20:00 (catch a missed 3 PM run)
REM   "HymnMania Backup On Logon"  -> at logon (catch a missed day entirely)
REM ===================================================================
cd /d C:\Users\jakeg\robertpelloni\hymnmania
if not exist logs mkdir logs
echo. >> logs\scheduler_backup.log
echo ==================== BACKUP %DATE% %TIME% ==================== >> logs\scheduler_backup.log

REM Make sure the social browser (CDP 9222) is up; the scheduler also self-heals.
python -c "import urllib.request,sys
try:
    urllib.request.urlopen('http://127.0.0.1:9222/json/version',timeout=4)
except Exception:
    import subprocess
    subprocess.Popen([r'C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe',
        '--remote-debugging-port=9222',
        r'--user-data-dir=C:\Users\jakeg\edge-cdp-profile',
        '--no-first-run','--no-default-browser-check',
        '--disable-features=msEdgeDisableStartupBoost'])
" >> logs\scheduler_backup.log 2>&1

"C:\Users\jakeg\AppData\Local\Programs\Python\Python314\python.exe" -u scheduler_v2.py --catchup >> logs\scheduler_backup.log 2>&1
echo ---- exit %ERRORLEVEL% ---- >> logs\scheduler_backup.log
