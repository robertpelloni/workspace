@echo off
setlocal enabledelayedexpansion

:: ═══════════════════════════════════════════════════════════════
:: Omni-Workspace Master Start Script - v5.37.0
:: Builds and launches all Go binary services
:: 7 projects, 10 binaries
:: ═══════════════════════════════════════════════════════════════

cd /d "%~dp0"

:: ─── Parse command ──────────────────────────────────────────
set "ACTION=%1"
if "%ACTION%"=="" set "ACTION=run"
if /i "%ACTION%"=="run"    goto :run_all
if /i "%ACTION%"=="build"  goto :build_all
if /i "%ACTION%"=="stop"   goto :stop_all
if /i "%ACTION%"=="status" goto :status
if /i "%ACTION%"=="help"   goto :help
echo Unknown command: %ACTION%
goto :help

:: ═══════════════════════════════════════════════════════════════
::  RUN ALL - Build + Launch every Go service
:: ═══════════════════════════════════════════════════════════════
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
echo  [1/7] Tabby Go
cd tabby\tabby-go
start /b tabby-backend.exe >nul 2>&1
start /b tabby-native.exe >nul 2>&1
start "" tabby-wails.exe >nul 2>&1
cd ..\..
echo        OK  tabby-backend, tabby-native, tabby-wails

:: 2. Hermes Agent Go
echo  [2/7] Hermes Agent Go
cd hermes-agent
start /b hermes-agent-go.exe >nul 2>&1
cd ..
echo        OK  hermes-agent-go

:: 3. HyperHarness Go
echo  [3/7] HyperHarness Go
cd hyperharness
start /b hyperharness.exe >nul 2>&1
cd ..
echo        OK  hyperharness

:: 4. Pi-Mono Go
echo  [4/7] Pi-Mono Go
cd pi-mono
start /b pi-go.exe >nul 2>&1
cd ..
echo        OK  pi-go

:: 5. NPP Go
echo  [5/7] NPP Go
cd npp\go-port
start /b npp-go.exe >nul 2>&1
cd ..\..
cd npp\bqt
start /b npp_bqt.exe >nul 2>&1
cd ..\..
echo        OK  npp-go, npp_bqt

:: 6. Warp Go
echo  [6/7] Warp Go
cd warp
start /b warp-go.exe >nul 2>&1
cd ..
echo        OK  warp-go

:: 7. Hyper Go
echo  [7/7] Hyper Go
cd hyper
start /b hyper-go.exe >nul 2>&1
cd ..
echo        OK  hyper-go

echo.
echo  ======================================================
echo    All 7 Go services launched successfully
echo  ======================================================
echo.
goto :end

:: ═══════════════════════════════════════════════════════════════
::  BUILD ALL - Compile every Go binary
:: ═══════════════════════════════════════════════════════════════
:build_all
echo  Building all Go binaries...
echo.
set "OK=0"
set "FAIL=0"

:: 1. Tabby Go (3 binaries)
echo  [1/7] tabby-go (backend + native + wails)
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
echo  [2/7] hermes-agent-go
cd hermes-agent
go build -buildvcs=false -ldflags="-s -w" -o hermes-agent-go.exe ./cmd/hermes >nul 2>&1
if errorlevel 1 ( echo        FAIL hermes-agent-go & set /a FAIL+=1 ) else ( echo        OK   hermes-agent-go.exe & set /a OK+=1 )
cd ..

:: 3. HyperHarness Go
echo  [3/7] hyperharness
cd hyperharness
go build -buildvcs=false -o hyperharness.exe . >nul 2>&1
if errorlevel 1 ( echo        FAIL hyperharness & set /a FAIL+=1 ) else ( echo        OK   hyperharness.exe & set /a OK+=1 )
cd ..

:: 4. Pi-Mono Go
echo  [4/7] pi-mono-go
cd pi-mono
go build -buildvcs=false -ldflags="-s -w" -o pi-go.exe ./cmd/pi >nul 2>&1
if errorlevel 1 ( echo        FAIL pi-go & set /a FAIL+=1 ) else ( echo        OK   pi-go.exe & set /a OK+=1 )
cd ..

:: 5. NPP Go (2 binaries)
echo  [5/7] npp-go (ultra + bqt)
cd npp\go-port
go build -buildvcs=false -ldflags="-s -w" -o npp-go.exe ./cmd/ultra >nul 2>&1
if errorlevel 1 ( echo        FAIL npp-go & set /a FAIL+=1 ) else ( echo        OK   npp-go.exe & set /a OK+=1 )
cd ..\..
cd npp\bqt
go build -buildvcs=false -o npp_bqt.exe . >nul 2>&1
if errorlevel 1 ( echo        FAIL npp_bqt & set /a FAIL+=1 ) else ( echo        OK   npp_bqt.exe & set /a OK+=1 )
cd ..\..

:: 6. Warp Go
echo  [6/7] warp-go
cd warp
go build -buildvcs=false -ldflags="-s -w" -o warp-go.exe ./cmd/warp >nul 2>&1
if errorlevel 1 ( echo        FAIL warp-go & set /a FAIL+=1 ) else ( echo        OK   warp-go.exe & set /a OK+=1 )
cd ..

:: 7. Hyper Go
echo  [7/7] hyper-go
cd hyper
go build -buildvcs=false -ldflags="-s -w" -o hyper-go.exe ./cmd/hyper >nul 2>&1
if errorlevel 1 ( echo        FAIL hyper-go & set /a FAIL+=1 ) else ( echo        OK   hyper-go.exe & set /a OK+=1 )
cd ..

echo.
echo  Build complete: %OK% OK, %FAIL% failed
goto :eof

:: ═══════════════════════════════════════════════════════════════
::  STOP ALL - Kill all Go service processes
:: ═══════════════════════════════════════════════════════════════
:stop_all
echo.
echo  Stopping all Go services...
echo.
taskkill /f /im tabby-backend.exe  >nul 2>&1
taskkill /f /im tabby-native.exe   >nul 2>&1
taskkill /f /im tabby-wails.exe    >nul 2>&1
taskkill /f /im hermes-agent-go.exe >nul 2>&1
taskkill /f /im hyperharness.exe   >nul 2>&1
taskkill /f /im pi-go.exe          >nul 2>&1
taskkill /f /im npp-go.exe         >nul 2>&1
taskkill /f /im npp_bqt.exe      >nul 2>&1
taskkill /f /im warp-go.exe        >nul 2>&1
taskkill /f /im hyper-go.exe       >nul 2>&1
echo  All Go services stopped.
echo.
goto :end

:: ═══════════════════════════════════════════════════════════════
::  STATUS - Show running Go processes
:: ═══════════════════════════════════════════════════════════════
:status
echo.
echo  === Omni-Workspace Go Service Status ===
echo.
echo  Binary                  Status
echo  ----------------------- ---------
for %%b in (tabby-backend.exe tabby-native.exe tabby-wails.exe hermes-agent-go.exe hyperharness.exe pi-go.exe npp-go.exe npp_bqt.exe warp-go.exe hyper-go.exe) do (
    tasklist /fi "imagename eq %%b" 2>nul | findstr /i "%%b" >nul
    if !errorlevel! equ 0 (
        echo  %%b  Running
    ) else (
        echo  %%b  Stopped
    )
)
echo.
goto :end

:: ═══════════════════════════════════════════════════════════════
::  HELP
:: ═══════════════════════════════════════════════════════════════
:help
echo.
echo  Omni-Workspace Master Start Script - v5.37.0
echo.
echo  Usage: start.bat [command]
echo.
echo  Commands:
echo    run       Build all + launch all Go services (default)
echo    build     Build all Go binaries (don't launch)
echo    stop      Kill all running Go services
echo    status    Show which Go services are running
echo    help      Show this help
echo.
echo  Go Services (7 projects, 10 binaries):
echo    1. tabby-go          Terminal backend + native + wails GUI
echo    2. hermes-agent-go   Self-improving AI agent (MCP/skills/memory)
echo    3. hyperharness      AI control plane + coding agent
echo    4. pi-mono-go        Agent runtime with scheduler
echo    5. npp-go            Notepad++ Ultra backend (LSP + commands)
echo    6. warp-go           Terminal/IDE (PTY + editor + renderer)
echo    7. hyper-go          Terminal emulator (PTY + plugins + UI)
echo.
echo  Individual start scripts:
echo    tabby\tabby-go\start.bat      [run^|build^|backend^|native^|wails^|test^|clean]
echo    hermes-agent\start.bat        [run^|build^|tui^|gateway^|test^|clean]
echo    hyperharness\start.bat        [tui^|serve^|pipe^|build^|test^|clean]
echo    pi-mono\start.bat             [run^|build^|test^|lint^|clean^|install^|help]
echo    npp\go-port\start.bat         [run^|build^|all^|bqt^|test^|clean^|help]
echo    warp\start.bat                [run^|build^|terminal^|editor^|test^|clean^|help]
echo    hyper\start.bat               [run^|build^|dev^|test^|clean^|help]
echo.
goto :end

:end
endlocal
