@echo off
:: RESET_WORKSPACE.bat
:: Forcefully terminates development-related processes to reset the environment.

echo [!] Resetting Workspace Processes...

:: Kill common dev runtimes and tools
taskkill /F /IM node.exe /T 2>nul
taskkill /F /IM pnpm.exe /T 2>nul
taskkill /F /IM bun.exe /T 2>nul
taskkill /F /IM uv.exe /T 2>nul
taskkill /F /IM python.exe /T 2>nul

taskkill /F /IM bash.exe /T 2>nul
taskkill /F /IM nohup.exe /T 2>nul
:: Kill shell hosts and terminals
taskkill /F /IM conhost.exe /T 2>nul
taskkill /F /IM cmdhost.exe /T 2>nul
taskkill /F /IM OpenConsole.exe /T 2>nul
taskkill /F /IM WindowsTerminal.exe /T 2>nul
taskkill /F /IM pwsh.exe /T 2>nul
taskkill /F /IM Tabby.exe /T 2>nul
taskkill /F /IM go.exe /T 2>nul
taskkill /F /IM git.exe /T 2>nul

:: Note: Killing cmd.exe will close this window if it matches.
:: We do this last to allow other commands to complete.
taskkill /F /IM cmd.exe /T 2>nul


echo [OK] Workspace reset attempted.
pause
