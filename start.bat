@echo off
echo Starting workspace (v4.57.0)...

echo [1/3] Starting BORG (HyperNexus Core)...
cd borg
:: start /b call start.bat
echo Use .\borg\start.bat to launch manually.
cd ..

echo [2/3] Starting REAL ESTATE CRM...
cd realestatecrm
:: start /b npm run dev
echo Use 'npm run dev' in .\realestatecrm to launch manually.
cd ..

echo [3/3] Starting JULES AUTOPILOT...
cd jules-autopilot
echo Use python/npm commands in .\jules-autopilot to launch.
cd ..

echo Start sequence finished.
