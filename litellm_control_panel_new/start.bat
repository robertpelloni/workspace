@echo off
echo Starting FreeLLM...
start "" freellm.exe
if %errorlevel% neq 0 (
    echo Failed to start FreeLLM. Try running setup.bat first.
    pause
    exit /b %errorlevel%
)
echo FreeLLM started in the background. Check your system tray.
