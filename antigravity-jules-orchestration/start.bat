@echo off
setlocal
title Antigravity Jules Orchestration
cd /d "%~dp0"

echo [Antigravity Jules Orchestration] Starting...
where npm >nul 2>nul
if errorlevel 1 (
    echo [Antigravity Jules Orchestration] npm not found. Please install it.
    pause
    exit /b 1
)

npm start

if errorlevel 1 (
    echo [Antigravity Jules Orchestration] Exited with error code %errorlevel%.
    pause
)
endlocal
