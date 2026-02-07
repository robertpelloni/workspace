cd /d %~dp0

set ORBIS_PSARC="%SCE_ORBIS_SDK_DIR%\host_tools\bin\orbis-psarc.exe"
set DELETE_PATH="%SCE_ORBIS_SDK_DIR%\target\samples\sample_code\system\tutorial_shooting_game\simple_shooting\data\app\game_data"

%ORBIS_PSARC% create --no-compress -y -o game_data.psarc -I filelist.txt

pause