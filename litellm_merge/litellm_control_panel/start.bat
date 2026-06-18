@echo off
echo Starting LiteLLM Control Panel...
start "" pythonw main.py
if %errorlevel% neq 0 (
    echo Failed to start the application. Try running setup.bat first.
    pause
    exit /b %errorlevel%
)
echo Application started in the background. Check your system tray.
