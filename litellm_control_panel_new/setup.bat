@echo off
echo Installing dependencies for FreeLLM...
go build -buildvcs=false -o freellm.exe ./cmd/app/
if %errorlevel% neq 0 (
    echo Failed to build FreeLLM. Please ensure Go is in your PATH.
    pause
    exit /b %errorlevel%
)
echo Setup complete. You can now run start.bat.
pause
