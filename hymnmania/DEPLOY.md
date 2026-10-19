# HymnMania Deployment Guide

## Prerequisites
- **Python 3.12+** with `playwright`, `mido`, `numpy`, `scipy`, `pystray`, `Pillow`
- **Microsoft Edge** with debugging enabled:
  ```powershell
  & "C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe" --remote-debugging-port=9222 --user-data-dir="C:\Users\hyper\EdgeDebug"
  ```
- **Suno Account**: Logged into Suno on the Edge browser.
- **FFmpeg & projectM**: Installed and configured for video generation.
- **Magnific API Key**: In `~/.env` as `MAGNIFIC_API_KEY`
- **YouTube OAuth**: `token.json` + `client_secrets.json` in project root
- **Facebook/Instagram**: Via Edge CDP browser automation

## How to Run
1. Start Microsoft Edge with remote debugging on port 9222:
   ```bash
   python scripts/launch_edge_suno.py
   ```
2. Launch the background system tray app:
   ```powershell
   python systray_app.py
   ```
3. Open your browser to `http://localhost:8083` or click "Open Dashboard" from the tray icon to monitor, generate, and upload.

## Pipeline Commands

```bash
# YouTube descriptions update
python youtube_update_descriptions.py

# Rename YouTube titles to standard format
python rename_youtube_titles.py

# Facebook auto-poster
python daily_scheduler.py

# Quick beat video composer
python quick_composer.py --audio <input.mp3> --video <output.mp4>

# Full cover generation (Suno)
cd scripts
python suno_cover_remix_options_form_style_submitter.py psytrance 05x Thy_Word --instrumental

# Magnific video clip generation
python scripts/magnific_video_pipeline.py --midi hymn_remaker/input/Thy_Word.mid --api-key $MAGNIFIC_API_KEY
```

## Social Media Accounts

| Platform | Account | Notes |
|----------|---------|-------|
| YouTube | Resurrecting Beats (@ResurrectingBeats) | OAuth via token.json |
| Facebook | Page ID 61588784931149 | CDP via Edge |
| Instagram | @ResurrectingBeats | resurrectingbeats@gmail.com |
| TikTok | @resurrecting.beat | Pending integration |
