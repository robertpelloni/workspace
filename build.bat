@echo off
echo Starting global build sequence (v5.13.3)...
echo [1/4] Building tormentnexus...
cd tormentnexus
go build -buildvcs=false -o tormentnexus.exe -ldflags "-s -w" .
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
cd tabby\tabby-go
go build -buildvcs=false -o tabby-backend.exe -ldflags "-s -w" ./cmd/tabby-backend/
go build -buildvcs=false -o tabby-native.exe -ldflags "-s -w" ./cmd/tabby-native/
cd ..\..
echo Build sequence finished.
