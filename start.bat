@echo off
setlocal enabledelayedexpansion

:: ================================================================
:: Omni-Workspace Master Start Script - v5.336.0
:: Builds and launches all Go binary services + Control Center (:2999)
:: 9 projects, 12 Go binaries + Consolidated Control Center & Tray
:: ================================================================

cd /d "%~dp0"

:: --- Parse command ----------------------------------------------
set "ACTION=%1"
if "%ACTION%"=="" set "ACTION=run"
if /i "%ACTION%"=="run"       goto :run_all
if /i "%ACTION%"=="build"     goto :build_all
if /i "%ACTION%"=="stop"      goto :stop_all
if /i "%ACTION%"=="status"    goto :status
if /i "%ACTION%"=="dashboard" goto :dashboard
if /i "%ACTION%"=="tray"      goto :tray
if /i "%ACTION%"=="help"      goto :help
echo Unknown command: %ACTION%
goto :help

:: ================================================================
::  RUN ALL - Build + Launch every Go service
:: ================================================================
:run_all
echo.
echo  +======================================================+
echo  ^|  Omni-Workspace - Starting All Go Services            ^|
echo  +======================================================+
echo.
call :build_all
echo.
echo  Launching services...
echo.

:: 1. Tabby Go
echo  [1/9] Tabby Go
cd tabby\tabby-go
start /b /belownormal tabby-backend.exe >nul 2>&1
start /b /belownormal tabby-native.exe >nul 2>&1
start "" /belownormal tabby-wails.exe >nul 2>&1
cd ..\..
echo        OK  tabby-backend, tabby-native, tabby-wails

:: 2. Hermes Agent Go
echo  [2/9] Hermes Agent Go
cd hermes-agent
start /b /belownormal hermes-agent-go.exe >nul 2>&1
cd ..
echo        OK  hermes-agent-go

:: 3. HyperHarness Go
echo  [3/9] HyperHarness Go
cd hyperharness
start /b /belownormal hyperharness.exe >nul 2>&1
cd ..
echo        OK  hyperharness

:: 4. Pi-Mono Go
echo  [4/9] Pi-Mono Go
cd pi-mono
start /b /belownormal pi-go.exe >nul 2>&1
cd ..
echo        OK  pi-go

:: 5. NPP Go
echo  [5/9] NPP Go
cd npp\go-port
start /b /belownormal npp-go.exe >nul 2>&1
cd ..\..
cd npp\bqt
start /b /belownormal npp_bqt.exe >nul 2>&1
cd ..\..
echo        OK  npp-go, npp_bqt

:: 6. Warp Go
echo  [6/9] Warp Go
cd warp
start /b /belownormal warp-go.exe >nul 2>&1
cd ..
echo        OK  warp-go

:: 7. Hyper Go
echo  [7/9] Hyper Go
cd hyper
start /b /belownormal hyper-go.exe >nul 2>&1
cd ..
echo        OK  hyper-go

:: 8. FreeLLM Proxy & Tray Go
echo  [8/9] FreeLLM Go
cd freellm
start "" /belownormal freellm.exe >nul 2>&1
cd ..
echo        OK  freellm

:: 9. BGTK 6-Pillar Framework & Dashboard Go
echo  [9/9] BGTK Go
cd bgtk\go
start /b /belownormal bobtk.exe -serve >nul 2>&1
cd ..\..
echo        OK  bobtk (-serve)

echo.
echo  ======================================================
echo    All 9 Go services (12 binaries) launched successfully
echo  ======================================================
echo.
goto :end

:: ================================================================
::  BUILD ALL - Compile every Go binary
:: ================================================================
:build_all
if "%GOCACHE%"=="" if exist "D:\agent-cache" set "GOCACHE=D:\agent-cache\go-build"
if "%GOTMPDIR%"=="" if exist "D:\agent-cache" set "GOTMPDIR=D:\agent-cache\go-tmp"
echo  Building all Go binaries...
echo.
set "OK=0"
set "FAIL=0"

:: 1. Tabby Go (3 binaries)
echo  [1/9] tabby-go (backend + native + wails)
cd tabby\tabby-go
go build -buildvcs=false -o tabby-backend.exe ./cmd/tabby-backend >nul 2>&1
if errorlevel 1 ( echo        FAIL tabby-backend & set /a FAIL+=1 ) else ( echo        OK   tabby-backend.exe & set /a OK+=1 )
go build -buildvcs=false -o tabby-native.exe ./cmd/tabby-native >nul 2>&1
if errorlevel 1 ( echo        FAIL tabby-native & set /a FAIL+=1 ) else ( echo        OK   tabby-native.exe & set /a OK+=1 )
cd wails-app
go build -buildvcs=false -o ..\tabby-wails.exe . >nul 2>&1
if errorlevel 1 ( echo        FAIL tabby-wails & set /a FAIL+=1 ) else ( echo        OK   tabby-wails.exe & set /a OK+=1 )
cd ..\..\..

:: 2. Hermes Agent Go
echo  [2/9] hermes-agent-go
cd hermes-agent
go build -buildvcs=false -ldflags="-s -w" -o hermes-agent-go.exe ./cmd/hermes >nul 2>&1
if errorlevel 1 ( echo        FAIL hermes-agent-go & set /a FAIL+=1 ) else ( echo        OK   hermes-agent-go.exe & set /a OK+=1 )
cd ..

:: 3. HyperHarness Go
echo  [3/9] hyperharness
cd hyperharness
go build -buildvcs=false -o hyperharness.exe . >nul 2>&1
if errorlevel 1 ( echo        FAIL hyperharness & set /a FAIL+=1 ) else ( echo        OK   hyperharness.exe & set /a OK+=1 )
cd ..

:: 4. Pi-Mono Go
echo  [4/9] pi-mono-go
cd pi-mono
go build -buildvcs=false -ldflags="-s -w" -o pi-go.exe ./cmd/pi >nul 2>&1
if errorlevel 1 ( echo        FAIL pi-go & set /a FAIL+=1 ) else ( echo        OK   pi-go.exe & set /a OK+=1 )
cd ..

:: 5. NPP Go (2 binaries)
echo  [5/9] npp-go (ultra + bqt)
cd npp\go-port
go build -buildvcs=false -ldflags="-s -w" -o npp-go.exe ./cmd/ultra >nul 2>&1
if errorlevel 1 ( echo        FAIL npp-go & set /a FAIL+=1 ) else ( echo        OK   npp-go.exe & set /a OK+=1 )
cd ..\..
cd npp\bqt
go build -buildvcs=false -o npp_bqt.exe . >nul 2>&1
if errorlevel 1 ( echo        FAIL npp_bqt & set /a FAIL+=1 ) else ( echo        OK   npp_bqt.exe & set /a OK+=1 )
cd ..\..

:: 6. Warp Go
echo  [6/9] warp-go
cd warp
go build -buildvcs=false -ldflags="-s -w" -o warp-go.exe ./cmd/warp >nul 2>&1
if errorlevel 1 ( echo        FAIL warp-go & set /a FAIL+=1 ) else ( echo        OK   warp-go.exe & set /a OK+=1 )
cd ..

:: 7. Hyper Go
echo  [7/9] hyper-go
cd hyper
go build -buildvcs=false -ldflags="-s -w" -o hyper-go.exe . >nul 2>&1
if errorlevel 1 ( echo        FAIL hyper-go & set /a FAIL+=1 ) else ( echo        OK   hyper-go.exe & set /a OK+=1 )
cd ..

:: 8. FreeLLM Go
echo  [8/9] freellm
cd freellm
go build -buildvcs=false -ldflags="-s -w" -o freellm.exe ./cmd/app >nul 2>&1
if errorlevel 1 ( echo        FAIL freellm & set /a FAIL+=1 ) else ( echo        OK   freellm.exe & set /a OK+=1 )
cd ..

:: 9. BGTK Go
echo  [9/9] bgtk-go (bobtk v1.8.0)
cd bgtk\go
go build -buildvcs=false -ldflags="-s -w" -o bobtk.exe . >nul 2>&1
if errorlevel 1 ( echo        FAIL bobtk & set /a FAIL+=1 ) else ( echo        OK   bobtk.exe & set /a OK+=1 )
cd ..\..

echo.
echo  Build complete: %OK% OK, %FAIL% failed
goto :eof

:: ================================================================
::  STOP ALL - Kill all Go service processes
:: ================================================================
:stop_all
echo.
echo  Stopping all Go services...
echo.
taskkill /f /im tabby-backend.exe   >nul 2>&1
taskkill /f /im tabby-native.exe    >nul 2>&1
taskkill /f /im tabby-wails.exe     >nul 2>&1
taskkill /f /im hermes-agent-go.exe >nul 2>&1
taskkill /f /im hyperharness.exe    >nul 2>&1
taskkill /f /im pi-go.exe           >nul 2>&1
taskkill /f /im npp-go.exe          >nul 2>&1
taskkill /f /im npp_bqt.exe         >nul 2>&1
taskkill /f /im warp-go.exe         >nul 2>&1
taskkill /f /im hyper-go.exe        >nul 2>&1
taskkill /f /im freellm.exe         >nul 2>&1
taskkill /f /im bobtk.exe           >nul 2>&1
echo  All Go services stopped.
echo.
goto :end

:: ================================================================
::  STATUS - Show running Go processes
:: ================================================================
:status
echo.
echo  === Omni-Workspace Go Service Status ===
echo.
echo  Binary                  Status
echo  ----------------------- ---------
for %%b in (tabby-backend.exe tabby-native.exe tabby-wails.exe hermes-agent-go.exe hyperharness.exe pi-go.exe npp-go.exe npp_bqt.exe warp-go.exe hyper-go.exe freellm.exe bobtk.exe) do (
    tasklist /fi "imagename eq %%b" 2>nul | findstr /i "%%b" >nul
    if !errorlevel! equ 0 (
        echo  %%b  Running
    ) else (
        echo  %%b  Stopped
    )
)
echo.
goto :end

:: ================================================================
::  HELP
:: ================================================================
:dashboard
echo.
echo  Launching Consolidated Control Center on http://localhost:2999 (BelowNormal)...
pushd "%~dp0research\workspace-orchestrator"
start "" /b /belownormal node server/index.js >nul 2>&1
popd
timeout /t 2 /nobreak >nul
start "" "http://localhost:2999"
goto :end

:tray
call "%~dp0start_dashboard_tray.bat"
goto :end

:help
echo.
echo  Omni-Workspace Master Start Script - v5.336.0
echo.
echo  Usage: start.bat [command]
echo.
echo  Commands:
echo    run         Build all + launch all Go services at BelowNormal priority (default)
echo    build       Build all Go binaries (don't launch)
echo    stop        Kill all running Go services
echo    status      Show which Go services are running
echo    dashboard   Launch Consolidated Control Center (:2999) and open browser
echo    tray        Launch Control Center (:2999) + Windows System Tray Controller
echo    help        Show this help
echo.
echo  Go Services (9 projects, 12 binaries):
echo    1. tabby-go          Terminal backend + native + wails GUI
echo    2. hermes-agent-go   Self-improving AI agent (MCP/skills/memory)
echo    3. hyperharness      AI control plane + coding agent
echo    4. pi-mono-go        Agent runtime with scheduler
echo    5. npp-go            Notepad++ Ultra backend + BQT editor
echo    6. warp-go           Terminal/IDE (PTY + editor + renderer)
echo    7. hyper-go          Terminal emulator (PTY + Mission Control + MCP)
echo    8. freellm           Survival-of-the-fittest LLM router + Windows Tray
echo    9. bgtk-go           BobTK v1.8.0 6-pillar runtime + Web Dashboard
echo.
goto :end

:end
endlocal
