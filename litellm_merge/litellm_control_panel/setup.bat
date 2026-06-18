@echo off
echo Installing dependencies for LiteLLM Control Panel...
python -m pip install pystray httpx ruamel.yaml pyinstaller Pillow
if %errorlevel% neq 0 (
    echo Failed to install dependencies. Please ensure Python is in your PATH.
    pause
    exit /b %errorlevel%
)
echo Setup complete. You can now run start.bat.
pause
