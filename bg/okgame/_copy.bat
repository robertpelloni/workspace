@echo off

mkdir "..\..\Desktop\bob's game"
mkdir "..\..\Desktop\bob's game\data"
xcopy /v .\*.dll "..\..\Desktop\bob's game"
xcopy /v .\Release\bobsgame.exe "..\..\Desktop\bob's game"
xcopy /v .\bobsgame.bmp "..\..\Desktop\bob's game"
xcopy /v .\VERSION.md "..\..\Desktop\bob's game\version.txt"
xcopy /v .\LICENSE "..\..\Desktop\bob's game"
xcopy /v /e .\data "..\..\Desktop\bob's game\data"
xcopy /v /e /i .\resources\presets "..\..\Desktop\bob's game\data\presets"

pause