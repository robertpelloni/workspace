@echo off
setlocal
cd /d "%~dp0"

echo ==============================================================
echo   Omni-Workspace Consolidated Control Center ^& System Tray
echo   Port: http://localhost:2999  ^|  Priority: BelowNormal
echo ==============================================================

:: Start the Node.js Control Center backend on :2999 at BelowNormal priority if not already listening
netstat -ano | findstr ":2999 " | findstr "LISTENING" >nul 2>&1
if errorlevel 1 (
    echo [1/2] Launching Control Center backend on http://localhost:2999 ^(BelowNormal^)...
    pushd "%~dp0research\workspace-orchestrator"
    start "" /b /belownormal node server/index.js >nul 2>&1
    popd
    timeout /t 2 /nobreak >nul
) else (
    echo [1/2] Control Center backend already listening on http://localhost:2999
)

:: Launch the native Windows System Tray icon controller hidden in the background
echo [2/2] Launching Windows System Tray Controller...
start "" /belownormal powershell.exe -NoProfile -ExecutionPolicy Bypass -WindowStyle Hidden -File "%~dp0research\workspace-orchestrator\tray_controller.ps1"

if /i "%1"=="--open" (
    start "" "http://localhost:2999"
)

echo Done. Right-click the Omni-Workspace tray icon near the Windows clock for quick controls.
endlocal
