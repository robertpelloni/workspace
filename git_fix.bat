@echo off
del /f /q C:\Users\hyper\workspace\tormentnexus\.git\index.lock 2>nul
cd /d C:\Users\hyper\workspace\tormentnexus
git status --short
if %errorlevel% neq 0 ( echo "Lock cleared" && git status --short )
