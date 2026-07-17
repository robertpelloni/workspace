@echo off
REM Cleanup script for post-reboot: remove locked tormentnexus directory
REM Run this after rebooting to clean up the old directory
echo Removing locked tormentnexus directory...
rmdir /s /q C:\Users\hyper\workspace\tormentnexus
if %errorlevel%==0 (
    echo SUCCESS: tormentnexus removed
) else (
    echo FAILED: Directory still locked. Try running as administrator.
)
pause
