@echo off
echo Starting global build sequence (v5.71.0)...
echo [1/4] Building tormentnexus (Node.js)...
cd tormentnexus
if exist package.json (
    echo   TormentNexus is a Node.js project - run npm install && npm run build manually
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
echo ✅ Built: hyperharness, pi-mono, tabby-backend, tabby-native
echo ℹ️  Skipped: tormentnexus (Node.js - manual build required)
