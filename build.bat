@echo off
setlocal enabledelayedexpansion
echo Starting global build sequence (v5.286.11)...
cd /d "%~dp0"
set "OK=0"
set "FAIL=0"
set "SKIP=0"

echo [1/4] Building tormentnexus (Go services + Node.js dashboard)...
if not exist tormentnexus\go (
    echo   SKIP tormentnexus\go not present - submodule not initialized
    set /a SKIP+=1
) else (
    echo   --- Go microservices ---
    cd tormentnexus\go
    for %%b in (tormentnexus deployment_manager health_monitor repo_sync repository_healer) do (
        echo   Building %%b...
        go build -buildvcs=false -o ..\bin\%%b.exe -ldflags "-s -w" .\cmd\%%b\
        if errorlevel 1 ( echo   FAIL %%b & set /a FAIL+=1 ) else ( echo   OK %%b.exe & set /a OK+=1 )
    )
    cd ..\..
    echo   --- Node.js dashboard ---
    cd tormentnexus
    if exist package.json (
        echo   Installing Node.js dependencies...
        if exist pnpm-lock.yaml (
            echo   Using pnpm...
            call pnpm install --no-frozen-lockfile --ignore-scripts 2>&1
        ) else (
            echo   Using npm with --no-audit...
            call npm install --no-audit --no-fund --ignore-scripts 2>&1
        )
        echo   npm run build...
        call npm run build 2>&1
    ) else (
        echo   SKIP No package.json found
        set /a SKIP+=1
    )
    cd ..
)

echo [2/4] Building hyperharness...
if not exist hyperharness\go.mod (
    echo   SKIP hyperharness\go.mod not present
    set /a SKIP+=1
) else (
    cd hyperharness
    go build -buildvcs=false -o hyperharness.exe -ldflags "-s -w" .
    if errorlevel 1 ( echo   FAIL hyperharness & set /a FAIL+=1 ) else ( echo   OK hyperharness.exe & set /a OK+=1 )
    cd ..
)

echo [3/4] Building pi-mono...
if not exist pi-mono\go.mod (
    echo   SKIP pi-mono\go.mod not present
    set /a SKIP+=1
) else (
    cd pi-mono
    go build -buildvcs=false -o pi-mono.exe -ldflags "-s -w" ./cmd/pi/
    if errorlevel 1 ( echo   FAIL pi-mono & set /a FAIL+=1 ) else ( echo   OK pi-mono.exe & set /a OK+=1 )
    cd ..
)

echo [4/4] Building Tabby Go...
if not exist tabby\tabby-go (
    echo   SKIP tabby\tabby-go not present
    set /a SKIP+=1
) else (
    cd tabby\tabby-go
    go build -buildvcs=false -o tabby-backend.exe -ldflags "-s -w" ./cmd/tabby-backend/
    if errorlevel 1 ( echo   FAIL tabby-backend & set /a FAIL+=1 ) else ( echo   OK tabby-backend.exe & set /a OK+=1 )
    go build -buildvcs=false -o tabby-native.exe -ldflags "-s -w" ./cmd/tabby-native/
    if errorlevel 1 ( echo   FAIL tabby-native & set /a FAIL+=1 ) else ( echo   OK tabby-native.exe & set /a OK+=1 )
    cd ..\..
)

echo Build sequence finished: %OK% OK, %FAIL% failed, %SKIP% skipped.
if %FAIL% gtr 0 exit /b 1
