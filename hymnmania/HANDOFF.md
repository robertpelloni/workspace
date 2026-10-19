# HANDOFF — v5.97.9 (2026-09-01)

## CRITICAL LESSONS (read before running pipeline)

### 0. Full pipeline order (VERIFIED 2026-09-01)
```
MIDI → sine MP3 → SUNO COVER → beat video → post
```
**NEVER skip the Suno cover step** — posting raw sine MP3s as final audio is WRONG.
The sine MP3 is the *input* reference; Suno generates the actual genre cover.

### 1. Suno v4.5 Cover Flow (current UI)
- Song page → **More menu (three dots)** → **Remix** (opens dropdown) → **Cover**
- Navigates to suno.com/create with v4.5-all model + track as reference
- Fill **Song Description** textarea (index 2, maxLength 3000) with genre prompt
- Set **Instrumental** toggle ON → click **Create**
- Poll feed for new clips (model `chirp-auk` / v4.5-all)

### 2. Suno DRM download (2026-09-01) — audio_url is FORBIDDEN
- `audio_url` → `https://studio-api.prod.suno.com/api/forbidden` — DO NOT use
- `media_urls` m4a (CloudFront) is an ENCRYPTED blob (no ftyp/mdat); mp3 (cdn1) → 403
- **WORKING METHOD**: click play → audio element src becomes `blob:https://suno.com/...` →
  `AudioContext.createMediaElementSource` + `MediaRecorder` → webm → ffmpeg → mp3
- Reload page between captures (MediaElementSource can only attach once per page)
- Record duration + 5s for full track

### 3. Missing module (FIXED 2026-09-01)
- `scripts/pipeline_config_central_definitions_genres_speeds.py` was deleted (only .pyc remained)
- Cover scripts crashed: `ModuleNotFoundError: No module named 'pipeline_config_central_definitions_genres_speeds'`
- **Restored from git commit `c780ddf`** along with 6 other deleted pipeline scripts
- Verify: `python -c "import sys; sys.path.insert(0,'scripts'); import pipeline_config_central_definitions_genres_speeds"`

### 4. Full-length videos (NOT clips)
- Use **ffprobe** for duration — NOT librosa (misreads Suno VBR MP3s by ~40%)
- `random.choices` (with replacement) to loop clips for long songs
- Each segment looped (`-stream_loop -1`) to exact cut_dur
- Simple concat + `-shortest`. NEVER xfade chains (collapsed videos to 11s)

### 5. Intro/outro text (drawtext)
- MUST include `fontfile=/Windows/Fonts/impact.ttf` or ffmpeg segfaults silently (no text, no error)

### 6. Unique thumbnails
- YouTube auto-thumbnails look identical. Use `youtube_thumbnails.py` (random clip + text overlay)

### 7. Titles — NEVER "cover"
- Only "Original" or "Remix" suffixes. Strip "cover" from filenames.
- Rename script fixes: "Unknown" prefix stripped, #Shorts preserved, genre priority
  (DnB Re**chip** → Drum and Bass, "unknown <genre>" parsed correctly)

### 8. ≤15 hashtags ALL platforms
- YouTube/Facebook/Instagram/TikTok discard ALL hashtags if >15.
- Structure: #EDM #ResurrectingBeats #Hymnmania #SpiritualEDM #Art #Dance #LOVE #ElectronicMusic2026 + #Psytrance #PsychedelicTrance + genre + #WorshipMusic #MentalHealthAwareness #UNITY + bank tag

### 9. Facebook Reels — FIXED
- Flow: reels/create → upload → Next → Next → caption (keyboard.type) → SCROLL DOWN → click "Post" by COORDINATES
- The Post button is BELOW the fold. JS .click() on hidden button does nothing. Must mouse.click(coordinates).

### 10. Facebook link spacing
- YouTube link needs blank line BEFORE and AFTER (else preview card doesn't populate)

### 11. Content originality
- MISSION_VARIATIONS (8) + reel CTAs (5) rotated per post. Never repeat same verbiage.

## Platform Status
- YouTube: Full + Shorts ✅ (Community needs 500 subs)
- Facebook: Feed + Stories + Reels ✅ (all working)
- Instagram: Reels ✅ (Create→Post flow, @resurrectingbeats)
- TikTok: needs @resurrecting.beat login

## New Hymns Added (2026 batch, never posted before)
- Jesus Comes With Power (Traditional, 2026)
- Just Over The Mountains (Traditional, 2026)
- O Happy Day (Philip Doddridge, 1755)
- When Love Shines In (Traditional, 2026)
- God Is So Good (Traditional, 2026)
- Oh God Our Help (Isaac Watts, 1719)
- Added to: `post_to_youtube.py` PIECES + `youtube_update_descriptions.py` HYMNS

## Browser
- Relaunch: `python _try_edge.py` or double-click `_open_edge.bat`
- `--user-data-dir=C:\Users\jakeg\edge-cdp-profile` preserves all logins
- Suno logged in: @resurrectingbeats (Clerk token via `Clerk.session.getToken()`)

## Scripts
| Script | Purpose |
|--------|---------|
| quick_composer.py | Beat videos (intro/outro + waveform visualizer + beat-sync) |
| batch_cover_gen.py | Suno v4.5 cover generation (current, More→Remix→Cover) |
| scripts/pipeline_config_central_definitions_genres_speeds.py | GENRES/SPEEDS config (restore from git c780ddf if missing) |
| scripts/suno_audio_uploader_file_chooser_injector.py | Upload sine MP3 to Suno |
| scripts/suno_cover_remix_options_form_style_submitter.py | Alt cover flow + feed poll |
| post_to_youtube.py | YouTube upload with correct titles/descriptions (no "cover") |
| daily_scheduler.py | Facebook feed posts (varied mission verbiage) |
| fb_stories.py | Facebook Stories + Reels (reel = scroll + coordinate click) |
| instagram_poster.py | Instagram Reels (Magnific clips + SEO captions) |
| youtube_update_descriptions.py | YouTube descriptions (≤15 hashtags) |
| rename_youtube_titles.py | YouTube titles (no "cover", Unknown-prefix fix) |
| youtube_thumbnails.py | Unique custom thumbnails |

## Download helper (DONE 2026-09-01)
`scripts/suno_download_via_mediarecorder.py <clip_id> [output.mp3]`
Plays blob audio → MediaRecorder → webm → mp3. Reloads page per capture automatically.

## VERIFIED PRODUCTION RUN (2026-09-01)
- Jesus Comes With Power → v4.5 psytrance cover (4:19) → beat video → posted FULL + SHORT
- Full: https://youtu.be/lbcCWoDw2fE | Short: https://youtu.be/dfLNlGlksX8
- All fixes active: DRM MediaRecorder download, restored config module, correct titles

## v5.97.10 — FULL GENRE BATCH (2026-09-01 evening)
- Jesus Comes With Power × ALL 11 genres generated (Suno v4.5 covers of upload d2246d83)
- 10 full beat videos composed + posted to YouTube (channel 1,163 → 1,170)
- MULTI-BOT SAFETY: other bot (chirp-v3, psy_darkpsy/hitech clips) is active on the
  SHARED Suno account. ALWAYS filter covers by cover_clip_id == your upload ID.
  Download ONLY chirp-auk (v4.5) clips with your cover_clip_id. Never touch chirp-v3.
- Upload note: sine MP3 uploads to Suno intermittently hang ("Uploading Clip" forever).
  Retry with fresh page + file_chooser. Jesus upload succeeded; others may need retries.
- Scripts: batch_gen_covers.py (generate+filter+download), download_covers.py (full capture),
  suno_upload_sine.py (upload+verify). All in scripts/.

## v5.97.11 — SUNO CAPTURE FIX (CRITICAL, 2026-09-02)
### The bug: batch captures produced SINE audio
- MediaRecorder captures from Suno song pages in batch/automated runs returned
  DEGRADED ~300Hz audio (spectral centroid ~330) instead of the real genre cover.
- User confirmed posted videos "still outputting sine wave sheet music."

### The fix (VERIFIED working):
1. Generate cover fresh with VERIFIED description injection (check textarea value before Create)
2. Capture immediately (within ~30 min of clip creation — clips degrade over time)
3. Get metadata duration from API
4. Play via the SINGLE main-track Play button: aria-label=="Play" AND y<500
   (NEVER click all play buttons — that queues the wrong track = sine!)
5. MediaRecorder for exactly (metadata_duration + 3) seconds
6. ffmpeg webm → mp3
7. VERIFY: spectral centroid >2000 = real cover, ~330 = degraded/sine

### Quality check command
python -c "...spectral centroid analysis..." — real covers are 2000-5000, sine is ~330

### Scripts
- gen_capture_genre.py — generate + capture one genre (verified injection)
- cap_final.py <clip_id> <genre> — capture specific clip correctly
- scan_clips.py — check which clips are still full-quality
- check2.py <clip_id> — playback spectrum check

### Results
- All 11 Jesus genre covers REAL (centroid 2800-5000), 10 reposted to YouTube (channel 1172)
- Extended YouTube quota CONFIRMED: 10+ uploads/day works, no quota errors
- End screens NOT settable via YouTube API (Studio UI only)

## TikTok (for @resurrecting.beat)
- Login: resurrectingbeats@gmail.com / Temppass0!
- Post the 9:16 short vids (like the 60s shorts made for YouTube)
- Can use TikTok in-app effects/remix to make them trendy

## v5.97.14 — AUTO-POST SCHEDULER (2026-09-03)

### scheduler_v2.py — cross-platform auto-poster (VERIFIED)
Usage:
- `python scheduler_v2.py --test`  → list pending (dedups against actual channel titles)
- `python scheduler_v2.py N`       → post N videos across all platforms
- `python scheduler_v2.py`         → post 1 video
Per-video cycle: YouTube full (API) → TikTok (CDP) → FB (reel best-effort + feed fallback) → IG (CDP)

### Verified posting methods (all use compressed <50MB 9:16 shorts)
1. **YouTube full**: post_to_youtube.py build_title + upload (API)
2. **TikTok**: tiktok.com/upload → select_video_button → set_input_files → contenteditable caption → post_video_button
3. **Facebook**: fb_reel_post.py (reels/create → Create reel btn → Add video → set file → Next) BEST-EFFORT
   (FB intermittently redirects reels/create to a reel viewer → falls back to FB FEED POST which is reliable)
4. **Instagram**: ig_cdp_post.py — click New post svg by COORDINATES (x~36,y~554, NOT by DOM),
   Post → set_input_files on mounted input → Next ×2 → Share

### Key scripts
- scheduler_v2.py — main cross-platform auto-poster
- ig_cdp_post.py — Instagram via CDP (coordinate-click New post)
- ig_poster_local.py — co-located IG (separate profile, logs in via .secrets.json)
- fb_reel_post.py — Facebook reel (Create reel → Add video flow)
- tt_batch.py — TikTok batch poster
- cap_final.py / gen_capture_genre.py — Suno DRM-safe cover capture

### CRITICAL: dedup
get_queue() queries actual YouTube channel titles and skips already-posted hymns.
Currently 7 genuinely-pending videos. Run --test first to see what will post.
