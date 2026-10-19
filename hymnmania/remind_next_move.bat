@echo off
REM Fires once, 2026-09-14 09:00 — reminds about the Suno promo / next pipeline move.
cd /d C:\Users\jakeg\robertpelloni\hymnmania
if not exist logs mkdir logs
echo ==== REMINDER %DATE% %TIME% ==== >> logs\reminder.log
type NEXT_MOVE.md >> logs\reminder.log 2>nul
powershell -NoProfile -Command "Add-Type -AssemblyName System.Windows.Forms; [System.Windows.Forms.MessageBox]::Show('HymnMania REMINDER^r^rThe Suno FREE-credit window closes ~11:00 today.^r^r1) Check if promo_sprint.py finished (see NEXT_MOVE.md)^r^r2) If unfinished, restart it NOW: python promo_sprint.py^r^r3) Banked clips then get captured/composed/posted for free.^r^rFull plan: C:\Users\jakeg\robertpelloni\hymnmania\NEXT_MOVE.md','HymnMania - next move',0,64)"
