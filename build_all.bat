@echo off
set WORKSPACE=C:\Users\hyper\workspace
cd /d %WORKSPACE%

echo Starting Global Build Process...

:: Maestro
if exist Maestro\build.bat (
    echo Building Maestro...
    cd Maestro
    call build.bat
    cd ..
)

:: Bobmania
if exist bobmani\bobmania\build.bat (
    echo Building Bobmania...
    cd bobmani\bobmania
    call build.bat
    cd ..\..
)

:: hyperharness
if exist hyperharness\build.bat (
    echo Building hyperharness...
    cd hyperharness
    call build.bat
    cd ..
)

echo Build process completed.
