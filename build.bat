@echo off
echo Starting global build sequence (v4.57.0)...

echo [1/3] Building BORG...
cd borg
call build.bat
cd ..

echo [2/3] Building REAL ESTATE CRM...
cd realestatecrm
call npm run build
cd ..

echo [3/3] Building BROKER AGENT WORKFLOW...
cd brokeragentworkflow
:: No specific build script seen, but let's assume standard python/npm if applicable
:: For now, we verified requirements.txt earlier.
cd ..

echo Build sequence finished.
