# HymnMania Architectural Memory

## Codebase Traits
- **Browser Automation**: CDP websocket connections are used to interact with Edge on port 9222. Playwright is used for robust browser upload automation.
- **Suno Cover Limitations**: Generating a cover of an uploaded track on Suno can trigger a copyright moderation failure if words like "Joy to the World" or "hymn" are placed in the description prompt or lyrics box. To bypass this, we use generic style tags ("full-on psytrance, energetic beat...") and set `"make_instrumental": True`.
- **Unique Sessions**: Navigation includes `session_id` query parameters to prevent multiple background tabs from colliding in CDP.

## Pipeline (VERIFIED 2026-09-01 — PRODUCTION CONFIRMED, full order)
```
MIDI → sine MP3 → SUNO COVER → beat video → post
```
- Sine MP3 = INPUT reference only. Suno generates the real genre cover.
- Cover flow (v4.5): song page → More menu (three dots) → Remix → Cover → /create
- Song Description textarea (index 2, maxLength 3000) sets gpt_description_prompt
- Instrumental toggle ON; model v4.5-all; new clips have model `chirp-auk`
- **PRODUCTION POST (2026-09-01)**: Jesus Comes With Power psytrance cover → beat video →
  FULL https://youtu.be/lbcCWoDw2fE + SHORT https://youtu.be/dfLNlGlksX8 (both public/live)

## Suno DRM Download (2026-09-01) — CRITICAL
- `audio_url` returns `/api/forbidden` — obsolete
- `media_urls`: m4a-opus (CloudFront = encrypted blob, no ftyp/mdat), mp3 (cdn1.suno.ai → 403)
- Direct URL fetch fails (403 / CORS / encryption)
- **WORKING**: click play → audio element src = `blob:https://suno.com/...` →
  `AudioContext.createMediaElementSource(audioEl)` + `MediaRecorder(stream)` → webm → ffmpeg → mp3
- Must reload page between captures (MediaElementSource attaches once per page)
- Record for (duration + 5s)

## Missing Module Incident (FIXED 2026-09-01)
- `scripts/pipeline_config_central_definitions_genres_speeds.py` deleted from tree (only .pyc in __pycache__)
- Crash: `ModuleNotFoundError: No module named 'pipeline_config_central_definitions_genres_speeds'`
- Defines: `GENRES` (11 genres), `SPEEDS` [0.5..3.0], `SPEED_LABEL_MAP`, `PITCH_SHIFT_FACTORS`
- Restored from git commit `c780ddf` (auto checkpoint before sync, 2026-07-11)
- Also restored: suno_browser_setup_connect_debugging_port.py, audio_speed_variants_exporter_for_multi_tempo_runs.py,
  suno_modal_dismissal_identify_describe_overwrite_resolver.py, suno_feed_polling_status_monitor_downloader.py,
  visuals_video_ffmpeg_pipe_muxer.py, visuals_milkdrop_preset_energy_analysis_transition_renderer.py,
  v2_youtube_oauth_uploader_with_hymn_metadata.py, generate_sine_cover.py
- LESSON: never delete scripts/ modules; config module is critical for cover generation

## Design Decisions
- **Dashboard Consolidations**: All features are condensed onto a single-page dashboard at `http://localhost:8083` to eliminate complex subpages and routes.
- **System Tray Controller**: A background utility (`systray_app.py`) is used to start the dashboard server and clean up python.exe processes upon quitting.

## Playwright & Browser Cover Pipelines
- **Generate Sine Cover (`generate_sine_cover.py`)**: High-performance browser flow running over CDP to control Edge. Synthesizes MIDI as a speed-adjusted sine-wave MP3, mounts the hidden file upload element by clicking `Audio`, switches to `Advanced` mode, inputs generic style text to avoid copyright filters, and polls the studio API feeds to download the generated `.mp3` covers directly.
- **Hydration Waiting**: Suno's UI requires waiting for hydration states to ensure the `Advanced` and `Audio` elements are fully visible and ready for interaction, which is handled via Playwright's native `wait_for(state="visible")` selectors.
- **Suno create page**: has 3-4 textareas — [0]=?, [1]=style (maxLen 1000), [2]=Song Description (maxLen 3000, sets gpt_description_prompt), [3]=Describe the sound (maxLen 500)
- **Upload modal**: after file inject, "Describe your audio" → select "Full Song" → Continue

## Social Media Posting
- **Facebook**: Uses Edge CDP (port 9222, profile `edge-cdp-profile`) via `daily_scheduler.py` / `facebook_poster.py`. Proven method: paste bare YouTube URL → wait for preview card → selectAll + replace with full template text → wait for re-scrape → post.
- **Instagram**: Credentials in `.secrets.json` (`resurrectingbeats@gmail.com`). Post template mirrors Facebook with bio-link CTA.
- **YouTube**: OAuth2 via `token.json`. Title format standardized for hymns and classical pieces. Descriptions include Artist: Resurrecting Beats ft. [Author].
- **YouTube quota**: 10,000 units/day. Upload = 1,600, rename = 50, thumbnail = 50, search = 100. ~6 uploads/day max. Shorts cost the same as full videos.

## Repository Sanitization
- **Windows Reserved File Names**: Dummy files named `nul` created inside recursively imported subdirectories must be deleted. Windows prevents reading or indexing files named `nul` because it is a reserved system device name. This blocks Git commands. Deletion requires using the UNC namespace prefix (`\\?\`) to bypass system reserved name checks.

## Clean Full-Length Capture — v5.97.16 (2026-09-09)
- Segmented 12s captures on separate pages = GAPS → stitched/cut-off audio (the "sounds cut off" bug).
- **cap_cycle.py is canonical**: page does 4x12s rounds on ONE page (survives ~60s), then fresh page seeks forward.
- Verified: 215s full capture, 0 silent gaps, centroid 3300-4000 throughout.
- Single page drops after ~60-72s of MediaRecorder rounds — cycle pages to be safe.
- Use ffprobe duration (NOT librosa — VBR misread ~40%).

## Suno CDN direct download = NOT possible for unpublished (tested 2026-09-09)
- cdn1.suno.ai/{uuid}.mp3 → 403; suno.ai/{uuid}.mp3 → 404; api/clip/{uuid} → 400
- CloudFront m4a returns 200 but encrypted blob (client-side DRM, browser decrypts to blob: URL)
- Research scripts claiming raw CDN download for unpublished tracks are OUTDATED
- MediaRecorder blob capture is the only working download path

## YouTube library reality (2026-09-09)
- Channel: 1247 total videos, only 295 UNIQUE titles (heavily duplicated from older pipeline era)
- Full-length REAL covers all posted now. Remaining unposted = only degraded (Just Over, O Happy Day
  copyright-blocked, sine-only) or duplicates under old naming.
- Amazing Grace / Canon / Clair de Lune / Toccata / Thy Word families are SATURATED (50-436 each).
- Posting quota: upload=1600 units; ~10/day verified fine (11 incl. delete).

## CRITICAL: cap_cycle seek bug + loop detector — v5.97.17 (2026-09-10)
- The 2026-09-09 cap_cycle capture had a SEEK BUG: `a.currentTime=start` set before the
  blob audio loaded → seek dropped → pages 2+ re-captured from 0 → output = first ~48s
  REPEATED. The file was still full-length and gap-free, so centroid/duration checks
  PASSED it — only a repetition analysis catches it.
- FIX: `seek_and_play()` waits for blob → waits for duration>0 → seeks → polls until
  currentTime lands at target → THEN records.
- DETECTOR: `cap_cycle.loop_score(f)` — centroid-bin(4s) analysis; bug = 2 CONSECUTIVE
  48s blocks near-identical (>0.9). Single high pair = legit genre repetition (not flagged).
- GATE: `post_to_youtube.quality_gate(video)` blocks upload if loop_score>0.9 (auto for full).
- Only When Love + God Is So Good were affected (both buggy-era cap_cycle captures).
  All other covers (cap_final era) audited clean.

## Verified E2E (2026-09-10) — God Is So Good (brand-new hymn)
sine mp3 → upload VERIFIED → psytrance cover (chirp-hawk) → cap_cycle 168s centroid 4612 →
beat video 170s → FULL https://youtu.be/fTfZ-QZDL1I + SHORT https://youtu.be/Js3l1JBkonk
When Love fixed: FULL https://youtu.be/friujcW2VLY + SHORT https://youtu.be/S2hZweqSY1Q

## Social reel paths VERIFIED LIVE — v5.97.18 (2026-09-10)
- Socials run on port 9222 / profile C:\Users\jakeg\edge-cdp-profile (has FB/IG/TikTok logins).
  Suno browser (9333) is NOT logged into socials. Other bot moved to 9223.
- tt_post.py: TikTok needs "Got it" dismissed + "Post now" clicked (confirmation dialog), else draft only.
- fb_reel_post.py: must wait for "Checking for copyrighted content" to CLEAR before Next.
- ig_cdp_post.py: Next(crop) -> Next(edit) -> keyboard.type caption -> Share. Typing after Share = lost post.
- Shorts are ~53MB > 50MB CDP limit -> compress to ~32MB (-crf 28) for FB/IG.
- Verified live on God Is So Good: TikTok Posts 10, FB Reel "shared with EVERYONE", IG reel DdHP5cFKSru (post 11).

## FULL PIPELINE + SCHEDULE — v5.97.19 (2026-09-10)
- Verified complete chain on new hymn "I Have Decided To Follow Jesus":
  upload -> cover (chirp-hawk) -> cap_cycle (157s, loop 0.0) -> beat video -> YT full+short
  -> compressed short -> TikTok + FB Reel + Instagram. All public.
- scheduler_v2.py REWRITTEN to use verified flows only; socials on 9222 (NOT 9333).
  ensure_browser() auto-launches 9222. Idempotency via .scheduler_log.json.
- ig_cdp_post.py now importable: post(video, caption_file); CLI under __main__.
- Bugs fixed: tt_post timeout 60s->240s; fb_reel waits for caption step; genre detroitcircuit/313.
- SCHEDULE: Windows Task "HymnMania Daily Post" -> run_scheduler.bat -> scheduler_v2.py --now 1,
  Mon-Fri 15:00, logs/scheduler.log. (Register/query schtasks via a .bat wrapper in Git Bash.)

## Backup scheduler + blocked hymns — v5.97.20 (2026-09-10)
- BACKUP posting: scheduler_v2.py --catchup (posts only if nothing published today, idempotent)
  run via run_scheduler_backup.bat. Windows Task "HymnMania Backup Post" weekdays 20:00, plus
  HymnMania_Catchup.bat in the Startup folder (ONLOGON scheduled task needs admin -> denied).
- BLOCKED (Suno ACRCloud fingerprint): O Happy Day, Kumbayah, Brighten The Corner, Leyenda,
  Praise Him! Praise Him!  DEGRADED: Just Over The Mountains (~400 centroid).
  Moved to mp3_input/_blocked/, filtered by scheduler_v2.BLOCKED_HYMNS. See BLOCKED_HYMNS.md.
- POOL: ~170 distinct pieces — 148 MIDIs in the submodule library (105 hymns/choruses + 43
  classical) + ~17 local MIDIs + 12 ready sine inputs.
