@echo off
echo Starting global build sequence (v5.73.0)...
echo [1/4] Building tormentnexus (Go services + Node.js dashboard)...
echo   --- Go microservices ---
cd tormentnexus\go
for %%b in (tormentnexus deployment_manager health_monitor repo_sync repository_healer) do (
    echo   Building %%b...
    go build -buildvcs=false -o ..\bin\%%b.exe -ldflags "-s -w" .\cmd\%%b\
)
cd ..\..
echo   --- Node.js dashboard ---
cd tormentnexus
if exist package.json (
    echo   npm install --production...
    call npm install --production --ignore-scripts 2>nul
    echo   npm run build...
    call npm run build 2>nul
) else (
    echo   No package.json found
)
cd ..
echo [2/4] Building hyperharness...
cd hyperharness
go build -buildvcs=false -o hyperharness.exe -ldflags "-s -w" .
cd ..
echo [3/4] Building pi-mono...
cd pi-mono
go build -buildvcs=false -o pi-mono.exe -ldflags "-s -w" ./cmd/pi/
cd ..
echo [4/4] Building Tabby Go...
cd tabby/tabby-go
go build -buildvcs=false -o tabby-backend.exe -ldflags "-s -w" ./cmd/tabby-backend/
go build -buildvcs=false -o tabby-native.exe -ldflags "-s -w" ./cmd/tabby-native/
cd ../..
echo Build sequence finished.
echo ✅ Built: tormentnexus Go services, hyperharness, pi-mono, tabby-backend, tabby-native
echo ℹ️  tormentnexus dashboard build result shown above
