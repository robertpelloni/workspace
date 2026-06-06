@echo off
echo ============================================
echo Starting Workspace Tools
echo Tabby + Pi + HyperHarness
echo ============================================
echo.

:: --- Tabby Terminal ---
echo [1/3] Starting Tabby...
start "" "C:\Users\hyper\AppData\Local\Programs\Tabby\Tabby.exe"

:: --- Pi Coding Agent ---
echo [2/3] Starting Pi...
start "" cmd /k "pi"

:: --- HyperHarness (Go backend) ---
echo [3/3] Starting HyperHarness...
cd /d "%~dp0hyperharness"
where go >nul 2>nul
if errorlevel 1 (
    echo WARNING: Go not found. Skipping HyperHarness.
) else (
    start "" cmd /k "go run . serve"
)

echo.
echo All tools launched.
timeout /t 3 >nul
