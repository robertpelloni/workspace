# HymnMania — Agent Instructions

> **Version: 5.97.25**
> **Last updated: 2026-09-10**
> **Purpose: Automated hymn/classical → electronic cover music → beat-synced video → YouTube + Facebook pipeline**
> **Status: WORKING END-TO-END — full pipe verified on a new hymn; auto-posting SCHEDULED (Mon–Fri 3 PM). Suno copyright-fingerprinting still blocks some familiar melodies.**

---

## SCHEDULE LIVE — "HymnMania Daily Post" (2026-09-10)

Windows Scheduled Task **"HymnMania Daily Post"** runs `run_scheduler.bat` →
`scheduler_v2.py --now 1` every **weekday at 3:00 PM**. Logs to `logs/scheduler.log`.

### BACKUP / FAILOVER (in case the primary run doesn't happen)
| Mechanism | Trigger | What it does |
|---|---|---|
| **HymnMania Backup Post** (scheduled task) | weekdays **8:00 PM** | `run_scheduler_backup.bat` → `scheduler_v2.py --catchup` — posts **only if nothing** was published today |
| **HymnMania_Catchup.bat** (Startup folder) | **at logon** | same catch-up (handles a day the machine was off) |

- `--catchup` is idempotent: it reads `.scheduler_log.json`, and if a post already happened
today it prints "already posted today" and exits. Safe to run any number of times.
- `run_scheduler_backup.bat` also ensures the social browser (CDP 9222) is running.
- The Startup-folder shortcut is user-level; an ONLOGON *scheduled task* needs admin
  ("Access is denied"), so the Startup folder is used instead.
- Manage: `schtasks /Query /TN "HymnMania Daily Post"` — **use a .bat wrapper from Git Bash**
  (Git Bash rewrites the `/Create` and `/Query` switches into paths).

- The scheduler auto-launches the social browser (9222) if CDP is down.
- Queue = full-length, real-audio (centroid>1000), non-looped (loop_score<=0.9), no mid-song
  silence (<3s), not already on the channel, not in `BLOCKED_HYMNS`, and **not classical**
  (`EXCLUDE_CLASSICAL` — classical belongs to a different channel). Per-track/platform
  idempotency via `.scheduler_log.json`.
- Manual: `python scheduler_v2.py --test | --now [N] | --catchup | --daemon`.

## Hymn Pool — what we can still use (see `BLOCKED_HYMNS.md`)

- **REMOVED** (Suno fingerprint rejects): O Happy Day, Kumbayah, Brighten The Corner,
  Leyenda, Praise Him! Praise Him! — and **Just Over The Mountains** (covers come out
  degraded ~400 centroid). Moved to `mp3_input/_blocked/`, filtered by `scheduler_v2.BLOCKED_HYMNS`.
- **AVAILABLE: ~163 distinct pieces** — 148 MIDIs in
  `submodules/ableton_psytrance_hymn_creator/hymnmania_src/hymn_remaker/input/`
  (**100 hymns/choruses + 46 classical**, 2 test files excluded) plus ~17 local MIDIs and
  12 ready sine inputs.
  - Hymn list: **`HYMNS_POOL.md`** (100)
  - **Classical list: `CLASSICAL_PIECES.md`** (46 files ≈ 20 distinct works) — ⚠️ **belongs to a
    DIFFERENT channel**; the HymnMania scheduler excludes it (`EXCLUDE_CLASSICAL`).
- Before generating, upload the sine render and confirm the uploader prints `VERIFIED`;
  a copyright match means the melody is fingerprinted — quarantine and pick another.

## Full Pipeline (VERIFIED end-to-end 2026-09-10)
```
MIDI/sine MP3 → Suno upload (VERIFIED) → cover gen (chirp-hawk) → cap_cycle.py (full, loop-checked)
              → quick_composer.py (beat video) → post_to_youtube full + short
              → compress 9:16 short (<50MB) → TikTok + FB Reel + Instagram
```
Reference run "I Have Decided To Follow Jesus": YT full youtu.be/TTsIGQDDAV0 ·
Short youtu.be/k8W_oqD9LwI · TikTok Posts 11 · FB Reel live · IG Posts 12.

---

## CRITICAL: Dedicated Browser on Port 9333 (2026-09-09)

All HymnMania automation uses its **own** Edge CDP browser on port **9333** (NOT 9222, which is shared with another bot).
- Profile: `.dedicated-edge-profile` (Suno logged in)
- Launch: `python launch_dedicated_browser.py` OR
  `msedge.exe --remote-debugging-port=9333 --user-data-dir="C:\Users\jakeg\robertpelloni\hymnmania\.dedicated-edge-profile" --disable-features=msEdgeDisableStartupBoost --disable-extensions`
- All core scripts (gen_only, cap_cycle, cap_final, scheduler_v2, upload_robust2) point to 9333.
- Do NOT kill Edge processes globally — it also takes down 9222's owner. Relaunch the profile after any kill.

## CRITICAL: Clean Full-Length Capture — `cap_cycle.py` (2026-09-09)

The stitched / cut-off-audio bug is SOLVED. Root cause: 12s MediaRecorder rounds on SEPARATE
pages left silent GAPS when a round failed. A single page survives only ~60-72s of consecutive
MediaRecorder rounds before it drops.

**`cap_cycle.py` is the canonical full-length capture script.**
- Each page does **4 consecutive 12s rounds on ONE page** (survives), then a FRESH page seeks forward.
- Concat + re-encode to mp3.
- Verified E2E: God Is So Good = 168s, centroid 4612, loop_check 0.000 (2026-09-10).
- Use **ffprobe** for duration (librosa misreads VBR/Suno MP3s by ~40%).

### CRITICAL BUG (fixed 2026-09-10): the seek must be CONFIRMED
Earlier versions set `audio.currentTime = start` before the blob element had loaded, so the
seek was silently DROPPED and every page re-recorded from 0 → the output was the first ~48s
**REPEATED**. The file was still full-length and gap-free, so duration/centroid checks PASSED it.
- FIX: `seek_and_play()` waits for the blob element → waits for `duration>0` → seeks →
  **polls until `currentTime` actually lands at the target** → only then records.
- Also: rounds are capped by remaining duration (never record past the song end — it wraps to 0),
  and the output is trimmed to the true song duration.

### MANDATORY validation of any capture (3 checks)
1. **loop_score** (`cap_cycle.loop_score`) must be ~0 — detects the 48s-repeat bug. Signature =
   **two CONSECUTIVE 48s blocks near-identical** (>0.9). A single high pair is legitimate genre
   repetition (techno/deep house) and is NOT flagged.
2. Full-file silence scan — longest mid-song silence <3s (only intro/outro fades allowed).
3. Multi-point spectral centroid >1200 (real cover); ~330 = sine/sheet-music.

`post_to_youtube.quality_gate()` runs check #1 automatically before every `full` upload and
refuses to post a looped video (verified: good=True, broken fixture=0.998 → blocked).

## CRITICAL: Suno CDN direct download does NOT work (tested 2026-09-09)

User research claiming unpublished tracks are downloadable from the raw CDN is **OUTDATED**.
- `https://cdn1.suno.ai/{uuid}.mp3` → **403** (XML error, Content-Length 146) for unpublished
- `https://suno.ai/{uuid}.mp3` → 404; `studio-api.prod.suno.com/api/clip/{uuid}` → 400
- CloudFront m4a (`d2lwuy8qc234o3.cloudfront.net/1/clip/{uuid}.m4a`) → 200 but **encrypted**
  (no ftyp/moov/mdat; browser decrypts client-side into a `blob:` URL)
- **Verdict**: MediaRecorder blob capture (`cap_cycle.py`) is the ONLY reliable download path.

## Posting Quota & Quality Gate (2026-09-12 — MEASURED)

### ✅ ANSWER: ~100 uploads/day, and FULL + SHORT share that one limit
Measured on 2026-09-12 by running `quota_probe.py` until it failed:
**99 uploads succeeded, then the API returned**
```
400 uploadLimitExceeded — "The user has exceeded the number of videos they may upload."
```
That is **YouTube's own per-channel daily upload limit**, NOT the API quota.
- **Full videos and Shorts count against the SAME limit** — it is one pool, not one each.
- Practical max ≈ **100 uploads/day** → at 2 uploads per track (full + Short) that is
  **~50 tracks/day**.
- The counter is a rolling ~24 h window (resets at midnight Pacific).

### API quota was NOT the binding limit
- `videos.insert` = **1,600 units EACH**. Default Google quota = 10,000 units/day → 6 uploads.
- This project's API quota is **raised**: 99 uploads consumed **~158,400 units** with **no**
  `quotaExceeded`. So the API quota is **at least ~158,400 units/day** — meaning
  **100 full videos/day (160,000 units) FITS on the API side.**
- Historic best day: **118 uploads** (2026-07-23).
- Conclusion: **the API is not the blocker — YouTube's ~100/day platform limit is.**
- Measuring the exact API ceiling is impractical: `search.list` (100 units) is rate-limited
  to ~100-125 calls before returning HTTP 429, so `api_quota_probe.py` cannot force
  `quotaExceeded`. Kept for reference only.

### Our settings
- `scheduler_v2.MAX_UPLOADS_PER_DAY = 96` (full + short combined) — a small safety margin
  under the observed ~99-100 platform limit. Check with `python scheduler_v2.py --status`;
  counter in `.yt_uploads.json`.
- `python quota_probe.py [max]` re-measures by uploading tiny **private** test videos until it
  fails, then deleting them all. Run it when you don't need that day's budget.

### Running the maximum
- Each track = up to **2 YouTube uploads** (full + Short) + 4 social posts.
- `python scheduler_v2.py --now 48` → 48 tracks ≈ 96 uploads (at the cap).
- Other API costs: title rename = 50, thumbnail = 50, search = 100, delete = 50, list = 1.
  Budget these AFTER uploads; never spend the pool on renames first.

### Quality gate (runs before ANY upload)
1. Full-file silence scan — no mid-song gap >3s
2. Multi-point spectral centroid >1200 (rejects sine/sheet-music ~330)
3. Loop check — no 48s-repeat capture bug
4. Not already on the channel (exact title dedupe)
5. Not in `BLOCKED_HYMNS`, and not classical (`EXCLUDE_CLASSICAL`)

## Social Reels — ALL 3 VERIFIED LIVE (2026-09-10)

Social scripts run on **port 9222** with profile `C:/Users/jakeg/edge-cdp-profile`
(the shared profile that holds the FB/IG/TikTok logins). Do NOT point them at the Suno
browser (9333) — that profile is not logged into the socials. Port 9222 is free (the other
bot now uses 9223).

Logins (verified): FB Page "Resurrecting Beats" (61588784931149) · IG @resurrectingbeats · TikTok @resurrecting.beat

| Platform | Script | Critical detail |
|---|---|---|
| TikTok | `tt_post.py <video> <caption>` | After Post, a dialog appears — dismiss **"Got it"** then click **"Post now"**. Success = redirect to `tiktokstudio/content`. Without this the reel stays an unposted draft. |
| Facebook Reel | `fb_reel_post.py <video> <title> <genre> <ytlink>` | Wait for **"Checking for copyrighted content" to CLEAR** before clicking Next. Do NOT break on the word "next" (it renders before the check). |
| Instagram | `ig_cdp_post.py <video> <caption_file>` | Order: Next (crop) → Next (edit) → **type caption with `keyboard.type`** (execCommand is ignored by React) → Share. Type the caption BEFORE clicking Share or the composer closes without publishing. |
| Facebook Stories | `fb_stories.py` | Compresses to ~5MB; story flow |

**Size**: the 60s short is ~53MB, which exceeds the ~50MB CDP upload limit → compress first
(`-crf 28` → 32MB worked). Verified live 2026-09-10 on "God Is So Good": TikTok (Posts 10),
FB Reel ("shared with EVERYONE"), IG (post 11, reel `DdHP5cFKSru`).

## 60-Second Reels / Shorts — VERIFIED (2026-09-09)

- `post_to_youtube.py short <beatfile>` → `make_short()` → 9:16 (1080x1920), first 60s, with audio,
  `#Shorts` appended. Verified live: 60.0s / 1080x1920, ~53MB.
- NOTE: ~53MB exceeds the 50MB CDP limit for TikTok/Facebook uploads — `fb_stories.py` compresses
  to ~5MB for Stories; TikTok uploader needs a compressed variant.
- Facebook Reels (`fb_stories.py post_to_facebook_reel`), Stories, Instagram Reels, TikTok all use
  the 9:16 short clips.

---

## Suno Limitations (KNOWN, 2026-09-09)

- **ACRCloud copyright fingerprinting** matches most familiar hymn melodies regardless of pitch shift
  (O Happy Day, Praise Him, Kumbayah, Brighten, Leyenda all matched). Only lesser-known melodies pass
  (Jesus Comes With Power, When Love Shines In, Amazing Grace).
- **Just Over The Mountains**: passes upload but Suno covers come out **degraded** (~400-700 centroid)
  from every input.
- Workaround: pick melodies that pass, or generate from existing Suno library uploads.

---

## CRITICAL: 15-Hashtag Limit (ALL PLATFORMS)

YouTube, Facebook, Instagram, and TikTok all DISREGARD every hashtag if a single post exceeds 15. NEVER exceed 15 combined hashtags on ANY platform.

## CRITICAL: Spacing Rules

**Always** use proper spacing between categories in YouTube descriptions and Facebook posts:

| Category | YouTube | Facebook |
|----------|---------|----------|
| Artist | `Artist: Resurrecting Beats ft. [Author]` | — (see template) |
| Genre | `Genre: {genre_name} / Electronic Worship` | `🎹 Vibe: {genre}` |
| Year | `Year: 2026` | — |

- Use spaces around slashes: `" / "` NOT `"/"`
- Facebook uses the full `HYMNMANIA_SOCIAL_POST_TEMPLATE` structure
- YouTube uses single newlines with emoji bullets

---

## YouTube Title Format

**Hymns:** `[Genre] Hymn 2026 Remix: [Title] ([Author], [Year]) | [Speed] [Variant]`
**Classical:** `[Genre] Classical Remix - [Piece] ([Composer], [Year]) | [Speed]`

Examples:
- `Psytrance Hymn 2026 Remix: Thy Word (Amy Grant & Michael W. Smith, 1984) | 1.0x Speed [A]`
- `Dubstep Classical Remix - Canon in D (Johann Pachelbel, 1680) | Triple Speed (3.0x)`

**CRITICAL**: NEVER put "cover" in the title. Only acceptable suffixes are "Original" or "Remix". Strip "cover" from filenames when generating titles.

**Genre Detection**: When the title doesn't contain the genre keyword, the rename script extracts it from the YouTube description (`Genre: {genre} / Electronic Worship`). If still unknown, use the placeholder `[EDM LSDance]` (case-sensitive, exact format). Never use "Electronic" alone as a genre in titles.

---

## YouTube Description Template

```
Track Details:
🏷️ Artist: Resurrecting Beats ft. [Original Hymn/Author]
🎼 Track: [Song Title]
🎹 Genre: [Genre] / Electronic Worship
📅 Year: 2026
⚡ Tempo/Variant: [Speed]

About this video:
[2-3 sentences about the visual style]

🙏 Our Mission:
Welcome to Resurrecting Beats, your ultimate destination for electronic worship. Our mission is to bring the world Psytrance and other electronic genres reimagined with the hymns we have all grown to love over the years. We want to honor God by taking every hymn we can and mixing them with futuristic soundscapes. We believe that psytrance is more than just music — it's life, and a powerful vehicle for spiritual and mental elevation.

🧠 The Science of Psytrance & Healing:
We love psytrance because it profoundly engages the brain. Characterized by hypnotic, complex, and repetitive arpeggiated melodies with fast tempos (140-150+ BPM), the highly rhythmic patterns stimulate the motor cortex, while the structural build-ups and unpredictable drops activate the reward pathway, releasing dopamine.

Its driving, repetitive qualities can induce a state of "transient hypofrontality," quieting the brain's overactive analytical centers — similar to deep meditation, prayer, or non-REM sleep stages. Highly immersive music can also modulate the amygdala (the brain's emotional "almond"), helping regulate responses to stress and trauma when paired with positive stimuli or the catharsis of dancing.

While active and mindful listening to music is a scientifically proven tool that helps reduce symptoms of anxiety by lowering cortisol (the primary stress hormone) and boosting neurochemicals like serotonin, it is not a cure for clinical depression. It acts as an incredibly effective adjunctive treatment to counteract feelings of hopelessness.

*If you are experiencing depression, it is highly recommended to seek professional support. You can locate accredited therapists and mental health resources via the SAMHSA National Helpline: https://www.samhsa.gov/find-help/helplines/national-helpline*

⚙️ How We Make Our Music:
The tracks on this channel are generated and meticulously produced using Hymnmania, a custom software automation tool and orchestration platform engineered by creators Bob & Lum to fuse faith, code, and electronic music. Visuals are created using the art skills of our creators and multiple digital media tools to achieve the correct blend of the psychedelic experience.

📅 New Music Videos Uploaded Every Week.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
📧 Business Inquiries:
Contact: ResurrectingBeats@gmail.com

🔗 Follow Our Playlists & Socials:
Facebook: https://www.facebook.com/profile.php?id=61588784931149&sk=directory_links
Instagram: https://www.instagram.com/resurrectingbeats?igsh=MWRxbGM4NHppZ2c2bw== @ResurrectingBeats
TikTok: https://www.tiktok.com/@resurrecting.beat?_r=1&_t=ZP-98NBjRbePx0

🎵 Stream/Download [Song Title]: Coming Soon

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#EDM #ResurrectingBeats #Hymnmania #SpiritualEDM #Art #Dance #LOVE #ElectronicMusic2026 #Psytrance #PsychedelicTrance #[Genre] #WorshipMusic #MentalHealthAwareness #UNITY + 1-2 bank tags (MAX 15 TOTAL)
```

---

## Facebook Post Template

The `daily_scheduler.py` script posts using this proven 3-step method.

### Posting Method (CRITICAL)

1. **Paste bare YouTube URL** into the composer — this triggers Facebook's link scraper to generate the video preview card
2. **Wait for preview** — poll for `img[src*=ytimg]` in the dialog, up to 20 seconds
3. **Select all + replace** — `document.execCommand('selectAll')` then `insertText` with full template text followed by the YouTube link at the bottom
4. **Wait for preview to regenerate** — Facebook re-scrapes the link after replacement
5. **Click Post** — post renders with full text structure AND video thumbnail preview card

### Post Body Template

```
{{HOOK_TEXT}} 🚀

🎵 Track: {{SONG_TITLE}}
🎹 Vibe: {{GENRE_OR_VIBE}} / Electronic Worship

{{VISUAL_EXPERIENCE_SUMMARY}} Our visuals are crafted by our creators using multiple digital media tools to deliver the ultimate psychedelic experience.

Every track is meticulously produced using Hymnmania, a custom software automation tool engineered by Bob & Lum to fuse faith, code, and electronic music. We believe psytrance is more than music — its fast, repetitive tempos stimulate the brain's reward pathways and induce a state of deep meditation and stress relief. 🙏🧠

Watch the full 4K visual journey on YouTube!

{{YOUTUBE_LINK}}

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#ResurrectingBeats #Hymnmania #SpiritualEDM #Psytrance #ElectronicMusic #WorshipMusic #MusicTherapy #MentalHealthAwareness
```

### Spacing Rules
- Double newlines (`\n\n`) between EVERY section
- Space after links and hashtags
- YouTube link MUST be on its own line at the bottom for preview regeneration
- Fixed hashtag block on EVERY post — no dynamic hashtags

## Instagram Post Template

Same template as Facebook, but:
- Set `{{LINK_CTA_TEXT}}` to: `(Full 4K visual journey link in our bio! 🔗)`
- Update Instagram bio link to the YouTube video URL
- Upload MP4 video to Instagram Reels/Feed

## Instagram Credentials

- **Login**: resurrectingbeats@gmail.com
- **Password**: Temppass0!
- **Profile**: @ResurrectingBeats

---

## Pipeline Scripts

| Step | Script | Notes |
|------|--------|-------|
| YouTube Descriptions | `youtube_update_descriptions.py` | Artist: Resurrecting Beats ft. author |
| YouTube Title Rename | `rename_youtube_titles.py` | Standard format |
| Facebook Poster | `daily_scheduler.py` | Bare URL → preview → selectAll → full text |
| Facebook Stories | `fb_stories.py` | Compressed 9:16 clip → Stories upload with YT link |
| Beat Video Composer | `quick_composer.py` | ffmpeg concat + Magnific clips + intro/outro + thumbnails (full-length) |
| Cover Generator | `batch_cover_gen.py` | Suno v4.5 More→Remix→Cover flow (current) |
| Cover Generator (alt) | `scripts/suno_cover_remix_options_form_style_submitter.py` | More→Remix→Cover + feed poll (needs restored config module) |
| MIDI→Sine MP3 | `scripts/audio_speed_variants_exporter_for_multi_tempo_runs.py` | Renders MIDI as speed-adjusted sine MP3 (input for Suno) |
| Suno Upload | `scripts/suno_audio_uploader_file_chooser_injector.py` | Injects MP3 via file chooser on suno.com/create |
| Config (CRITICAL) | `scripts/pipeline_config_central_definitions_genres_speeds.py` | GENRES/SPEEDS/PITCH_SHIFT_FACTORS — restore from git c780ddf if missing |
| Suno Download (DRM) | `cap_cycle.py` (CANONICAL) | Page-cycle 4x12s MediaRecorder rounds → concat → mp3. audio_url=forbidden |
| Suno Download (alt, short) | `cap_final.py`, `cap_single_full.py` | ≤12s single captures / older helpers |
| YouTube Shorts | `post_to_youtube.py short <file>` | 9:16 1080x1920, first 60s, `#Shorts` (verified 2026-09-09) |
| YouTube Full Post | `post_to_youtube.py full <file>` | Data API videos().insert(), 1600 units |
| Scheduler v2 | `scheduler_v2.py` | Quality-gated queue (centroid>1000) + multi-platform |
| YouTube Community | CDP browser | Static SEO posts on Community tab (requires 500+ subscribers) |
| TikTok Poster | `tiktok_poster.py` | Convert to vertical + upload via CDP browser |
| Scheduler Bot | `scheduler_bot.py` | Weekly auto-posting Mon-Fri to TikTok + Facebook |
| AI Metadata | Embedded JSON-LD | Schema.org MusicRecording for AI crawler indexing |

## Beat Video Branding

### Beat Synchronization
Every video is beat-synced to the music with tempo-scaled phrase lengths:
1. **librosa** detects BPM from the audio track (range 60-200 BPM)
2. Clip duration scales with tempo to keep cuts in the 3-6 second sweet spot:

| Tempo Range | Beats/Phrase | Clip Duration | Genres |
|------------|-------------|---------------|--------|
| >160 BPM | 16 beats | ~5-6s | Gabba, fast DnB |
| 130-160 BPM | 12 beats | ~4.5-5.5s | Psytrance, Hardstyle |
| 100-130 BPM | 8 beats | ~3.7-4.8s | Deep House, Detroit, Dubstep |
| <100 BPM | 4 beats | ~2.4-4s | Half-speed, ambient |

### Intro/Outro (Text on Video — REQUIRES fontfile)
- **Intro (2.5s)**: "RESURRECTING BEATS" + genre name over random Magnific clip with genre-matched colors
- **Outro (3s)**: "RESURRECTING BEATS" + "Subscribe for more!" with fade-out
- **CRITICAL**: drawtext MUST include `fontfile=/Windows/Fonts/impact.ttf` — without it, ffmpeg segfaults and the text silently fails to render

### Genre Style Map
| Genre | Text Color | Effect |
|-------|-----------|--------|
| Psytrance | Purple neon | Neon glow |
| Dubstep | Red | Bass shake |
| Deep House | Gold | Warm fade |
| Drum and Bass | Cyan | Fast pulse |
| Chiptune | Lime green | Pixel glitch |
| Gabba | Orange | Hardcore flash |
| Detroit Techno | Silver | Industrial |
| Detroit House | Gold | Smooth |
| Hardstyle Trance | Yellow | Laser blast |
| Synthwave | Magenta | Neon grid |
| Japanese Hardcore | Cyan | Kawaii rave |

### Unique Previews
- Clips are randomly sampled from 152 Magnific videos
- Each clip uses a random start timestamp — no two videos start the same way
- YouTube thumbnail frames are always different

## TikTok Posting

### Channel
- **Handle**: @resurrecting.beat
- **URL**: https://www.tiktok.com/@resurrecting.beat?_r=1&_t=ZP-98NBjRbePx0

### Post Template
```
🌀 RESURRECTING BEATS: '{TRACK_TITLE}' [{SUB_GENRE}] ⚡

Resurrected from the vault! {VIBE} energy at {BPM} BPM in {KEY}. Built for festivals, vocalists, and live sets.

🎧 Free Download / License link in bio!
💬 Comment '{TRACK_TITLE_UPPER}' for the untagged high-quality link.

#ResurrectingBeats #EDM #Psytrance #SpiritualEDM #ElectronicMusic #Dance #DanceSafe #HymnMania

#producertok #edmmusic #trancefamily #festivalbeats #unreleasedmusic #[Genre] #[Hook/TrackTitle]
```

### Example
```
🌀 RESURRECTING BEATS: 'Samsara' [Psytrance / Spiritual EDM] ⚡

Resurrected from the vault! High-energy 138 BPM Psytrance beat packed with spiritual vocals & driving bass. Perfect for festivals, vocalists, and content creators.

🎧 Free Download / License link in bio!
💬 Comment 'SAMSARA' to get the untagged high-quality link sent to your inbox.

#ResurrectingBeats #EDM #Psytrance #SpiritualEDM #ElectronicMusic #Dance #DanceSafe #HymnMania #producertok #trancefamily #festivalmusic #unreleasedmusic #producertok #edmbeats
```

### Posting Method
- **Upload**: TikTok web uploader at `tiktok.com/upload` via CDP browser
- **Format**: 9:16 vertical (1080x1920) MP4 — converted from existing beat videos
- **Privacy**: PUBLIC_TO_EVERYONE
- **AI flag**: Set `is_aigc=true` for Suno-generated audio

### What's Needed to Post
1. CDP browser session with TikTok logged in (@resurrecting.beat)
2. 9:16 vertical video files (converted via ffmpeg crop/scale from beat videos)
3. BPM + Key metadata (extracted via librosa)
4. TikTok web uploader automation script (same pattern as Facebook poster)

## Credentials

- **YouTube**: `token.json` (OAuth refreshable)
- **Facebook**: via Edge CDP browser (port 9222, profile `edge-cdp-profile`)
- **Instagram**: `resurrectingbeats@gmail.com` / `Temppass0!` (in `.secrets.json`)
- **Magnific**: `~/.env` (needs credits)
- **Channel**: Resurrecting Beats (@ResurrectingBeats)
- **Facebook Page**: lumkourlos@gmail.com / Page ID 61588784931149

## Growth Recommendations

### Immediate (can implement now)
| Priority | Feature | Impact | Effort |
|----------|---------|--------|--------|
| **P0** | Crossfade transitions between clips (0.3-0.5s xfade) | High | Low |
| **P0** | YouTube Shorts - 60s vertical highlights from beat videos | High | Medium |
| **P0** | End screens - Subscribe + next video card on last 20s | High | Low |
| **P1** | Custom thumbnails - genre + hymn title overlay | Medium | Medium |
| **P1** | Audio-reactive waveform/spectrum overlay synced to beat | Medium | Medium |
| **P1** | Playlist auto-organization by hymn, genre, speed | Medium | Low |
| **P1** | TikTok/Reels cross-post - 9:16 vertical cuts | High | Medium |
| **P2** | Comment auto-engagement - reply with YT link | Low | Low |
| **P2** | Ken Burns zoom/pan on static clips | Medium | Low |
| **P2** | Pinned comment: "Which hymn should we remix next?" | Low | Low |

### Weekly Cadence
| Day | Time (EST) | Content Type | Platform |
|-----|-----------|-------------|----------|
| MON | 3-5 PM | HOOK_DROP (15s loop) | TikTok + FB |
| TUE | 2-6 PM | VAULT_STORY (30s background) | TikTok + FB |
| WED | 1-6 PM | HOOK_DROP (15s loop) | TikTok + FB |
| THU | 1-5 PM | CONVERSION (30s YT promo) | TikTok + FB |
| FRI | 3-5 PM | HOOK_DROP (15s loop) | TikTok + FB |
| SAT/SUN | — | Rest / Queue Reset | — |

Run manually: `python scheduler_bot.py HOOK_DROP`
Auto-run: leave running and it posts on schedule hourly check

### Subscriber Hooks
- **First 3s**: RESURRECTING BEATS intro flash
- **Last 20s**: End screen with subscribe CTA
- **Description**: Clear call-to-action to subscribe
- **Cross-promote**: Link Facebook + TikTok in every description

### YouTube Post Types (All 3)
| Type | Format | Method | Min Subs |
|------|--------|--------|----------|
| Full Video | 16:9 MP4 | API videos().insert() | 0 |
| Shorts | 9:16 vertical <60s | API + #Shorts tag | 0 |
| Community (Static) | Text + link | CDP browser Community tab | 500 |

Community tab blocked until 500 subscribers. Script ready.

### Facebook Stories & Reels
- **Script**: `fb_stories.py` — creates 20s compressed 9:16 clips from beat videos
- **Upload**: CDP browser → `facebook.com/stories/create`
- **Format**: 9:16 vertical (720x1280), under 50MB, 15-30 second clips
- **Headline**: Track title + genre + YouTube link
- **Link**: Full YouTube URL included in the story text

## Facebook — All Post Types

### 1. Feed Posts (`daily_scheduler.py`)
- Text + YouTube link in body (generates video preview card)
- Full template: hook, track, vibe, visual summary, Hymnmania production, YT link
- Method: bare URL → preview → selectAll + replace → Post
- Hashtags: #ResurrectingBeats #Hymnmania #SpiritualEDM #Psytrance #ElectronicMusic #WorshipMusic #MusicTherapy #MentalHealthAwareness

### 2. Stories (`fb_stories.py`)
- 20-second 9:16 vertical clip from beat video
- Compressed to ~5MB (under CDP 50MB limit)
- Text overlay: track name + resurrectingbeats + genre (via ffmpeg drawtext with fontfile)
- Upload via CDB `facebook.com/stories/create`
- Stays live 24 hours

### 3. Reels (`fb_stories.py` — `post_to_facebook_reel`)
- Flow DISCOVERED: facebook.com/reels/create → upload → Next → Next → caption → Post
- Caption field: placeholder "Describe your reel..." (use keyboard.type, NOT execCommand)
- Final button: "Post" (not Publish/Share)
- **STATUS**: Draft created but final publish not confirmed (reel shows "No reels yet")
- Instagram Reels WORK (verified 4 posts). Facebook Reels still need the final publish step resolved.

### Hashtag Block (ALL Facebook Posts)
```
#ResurrectingBeats #Hymnmania #SpiritualEDM #Psytrance #ElectronicMusic #WorshipMusic #MusicTherapy #MentalHealthAwareness
```
Plus genre-specific: #Dubstep #DeepHouse #DrumAndBass #Chiptune #Gabba #DetroitTechno #DetroitHouse #Hardstyle #Synthwave #JapaneseHardcore

## Instagram Posting (UPDATED 2026-08-24)
- **Script**: `instagram_poster.py` — use `post_beat_to_instagram()` (NOT `post_magnific_clip`)
- **Video**: Beat videos (have AUDIO + RESURRECTING BEATS intro), converted to 9:16 30s Reel
- **Flow**: instagram.com → Create ("New post") → "Post" → upload → Next → Next → caption → Share
- **Caption**: Sound description (genre + BPM) + like/subscribe CTA + YouTube link + <=15 hashtags
- **Cross-post to Facebook**: At final Share step, the "Share to" section shows the Instagram account + a "Facebook" toggle. Click the Facebook toggle to ALSO post to Facebook. This appears AT the moment of posting (not before).
- **Credentials**: resurrectingbeats@gmail.com / Temppass0! (in .secrets.json)
- **CRITICAL**: Use beat videos (have audio+intro), NOT raw Magnific clips (silent, no intro)

## Suno v4.5 Cover Flow (Updated 2026-09-01 — VERIFIED WORKING END-TO-END)

Suno UI changed from v5.5 → v4.5. The Cover flow is now:
- **Old**: More menu → Remix → Cover (nested)
- **New**: More menu (three dots) → Remix (opens dropdown) → **Cover**

Cover still opens at `suno.com/create` with the song as reference and v4.5-all model. Same genre/style injection as before.

### FULL PIPELINE (documented, verified 2026-09-01)
```
1. MIDI → sine MP3        scripts/audio_speed_variants_exporter_for_multi_tempo_runs.py (or batch_master.py)
2. sine MP3 → Suno upload  scripts/suno_audio_uploader_file_chooser_injector.py (Add audio → file chooser)
3. Upload modal: select "Full Song" → Continue
4. Cover flow: song page → More menu (three dots) → Remix → Cover
5. Fill Song Description textarea (index 2, maxLength 3000) with genre → Instrumental ON → Create
6. Poll feed → new clips (model chirp-auk / v4.5-all)
7. DOWNLOAD: capture via MediaRecorder (see DRM section below)
8. cover MP3 → beat video  quick_composer.py
9. post                   post_to_youtube.py (+ rename/descriptions)
```


### CRITICAL: Capture degradation fix (2026-09-02)
- MediaRecorder batch captures from Suno song pages can return DEGRADED ~300Hz audio
  (spectral centroid ~330) instead of the real genre cover (~2800-5000).
- Correct method: generate cover fresh, capture within ~30 min of clip creation,
  get metadata duration first, play via the SINGLE main-track Play button
  (aria-label=="Play", y<500 — NEVER click all play buttons), MediaRecorder for
  exactly metadata_duration+3s, ffmpeg webm->mp3. Verify centroid >2000.
- Helpers: gen_capture_genre.py, cap_final.py, scan_clips.py
### CRITICAL: Suno DRM download (2026-09-01)
- `audio_url` now returns `https://studio-api.prod.suno.com/api/forbidden` — DO NOT use it
- `media_urls` has m4a-opus (CloudFront, ENCRYPTED blob — no ftyp/mdat) and mp3 (cdn1.suno.ai → 403)
- Direct URL fetch of either fails (403 / CORS / encrypted)
- **WORKING METHOD**: play the song in the browser → audio element gets `blob:https://suno.com/...` src →
  capture with `AudioContext.createMediaElementSource` + `MediaRecorder` → save webm → ffmpeg to mp3
- MediaRecorder details:
  - Must click the track's play button to start blob streaming (song page does NOT autoplay)
  - `createMediaElementSource` can only attach once per page — reload page between captures
  - Record full duration (~duration+5s) to capture complete track
- Download helper: see capture logic in session notes / `scripts/` (needs a `suno_download_via_mediarecorder.py`)

### CRITICAL: missing module (FIXED 2026-09-01)
- `scripts/pipeline_config_central_definitions_genres_speeds.py` defines GENRES, SPEEDS, SPEED_LABEL_MAP, PITCH_SHIFT_FACTORS
- It was DELETED from the working tree (only .pyc cache remained) → cover script crashed with ModuleNotFoundError
- Restored from git commit `c780ddf` (also restored: suno_browser_setup, audio_speed_variants_exporter,
  suno_modal_dismissal, suno_feed_polling, visuals_video_ffmpeg_pipe_muxer, visuals_milkdrop_renderer,
  v2_youtube_oauth_uploader, generate_sine_cover.py)
- NEVER delete scripts/ modules — verify with `python -c "import pipeline_config_central_definitions_genres_speeds"`

### VERIFIED COMPLETE RUN (2026-09-01 — with all fixes)
- Uploaded sine MP3 → v4.5 Cover (More→Remix→Cover) → genre desc → Instrumental → Create
- Downloaded full cover via MediaRecorder capture (scripts/suno_download_via_mediarecorder.py)
- Composed beat video + posted FULL + SHORT to YouTube:
  - Full: https://youtu.be/lbcCWoDw2fE (Psytrance Hymn 2026 Remix: Jesus Comes With Power)
  - Short: https://youtu.be/dfLNlGlksX8 (#Shorts)

### Full-Length Video Guarantee (CRITICAL)
The beat composer uses **ffprobe** duration (NOT librosa — librosa misreads Suno VBR MP3s by ~40%):
1. ffprobe reads true audio duration
2. `random.choices` loops Magnific clips for long songs
3. Each clip looped (`-stream_loop`) to exact cut_dur
4. Simple concat + `-shortest` cuts at full song end

Verification: 135 beat videos, 0 truncated, 0 empty, all match source audio.

## How To Relaunch The Edge CDP Browser

When the browser closes, run one of these methods:

### Method 1: Script (easiest)
```bash
python _try_edge.py
```

### Method 2: Command line (manual)
```cmd
"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe" --remote-debugging-port=9222 --user-data-dir=C:\Users\jakeg\edge-cdp-profile --no-first-run --no-default-browser-check
```

### Method 3: Batch file
Create `_open_edge.bat` with:
```bat
start "" "C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe" --remote-debugging-port=9222 --user-data-dir=C:\Users\jakeg\edge-cdp-profile --no-first-run --no-default-browser-check
```

**IMPORTANT**: The `--user-data-dir=C:\Users\jakeg\edge-cdp-profile` is what preserves all your logins (Facebook, Instagram, Suno, Magnific). ALWAYS include it or you'll lose sessions.

## CRITICAL: Beat Video & Thumbnail Rules (Learned 2026-08-24)

### 1. Full-Length Videos (NOT clips)
- Use **ffprobe** for duration — NOT librosa (librosa misreads Suno VBR MP3s by ~40%)
- `random.choices` (with replacement) to loop Magnific clips for long songs
- Each segment looped (`-stream_loop -1`) to exact `cut_dur`
- Simple concat + `-shortest` cuts at full song end
- NEVER use xfade chains — the offset math collapsed videos to 11s

### 2. Intro/Outro Text (drawtext)
- drawtext MUST include `fontfile=/Windows/Fonts/impact.ttf` 
- WITHOUT fontfile, ffmpeg segfaults and text silently fails (no error, no text)
- Intro (2.5s): "RESURRECTING BEATS" + genre name
- Outro (3s): "RESURRECTING BEATS" + "Subscribe for more!"

### 3. Unique Thumbnails (NO duplicates)
- YouTube auto-thumbnails from first frame = all look identical (similar Magnific clips)
- Fix: `youtube_thumbnails.py` generates custom thumbnails
- Each thumbnail = UNIQUE random Magnific clip + genre + hymn text overlay
- Run daily: `python youtube_thumbnails.py 100` (quota ~200/day)

### 4. Quota Management
- YouTube Data API = 10,000 units/day (SHARED pool)
- Title rename = 50 units, Upload = 1,600 units, Thumbnail = 50 units, Search = 100 units
- Plan order: uploads first → titles → thumbnails last
- Never exceed ~200 renames/day (10,000 units / 50)

### 5. Beat Sync (librosa for BPM only)
- librosa is GOOD for BPM detection (tempo)
- librosa is BAD for duration (VBR misread)
- tempo-scaled beats: >160 BPM=16 beats, 130-160=12, 100-130=8, <100=4

## Hashtag Rules (CRITICAL — YouTube ignores ALL hashtags if >15)

### Max 15 Combined Hashtags Per Post
YouTube discards ALL hashtags if a description contains more than 15. NEVER exceed 15.

### Structure (always in this order)
1. **Core (8)**: #EDM #ResurrectingBeats #Hymnmania #SpiritualEDM #Art #Dance #LOVE #ElectronicMusic2026
2. **Psytrance (2, always)**: #Psytrance #PsychedelicTrance (channel identity)
3. **Dedicated genre (1)**: #[Genre] (e.g. #Dubstep, #DeepHouse, #Synthwave)
4. **Secondary (3)**: #WorshipMusic #MentalHealthAwareness #UNITY
5. **Bank (1-2, rotate for SEO)**: draw from the bank below

### Hashtag Bank (rotate these for keyword/SEO coverage)
```
#StudyMusic #GamingMusic #WorkoutMusic #TrippyVisuals #PsychedelicVisuals
#BassMusic #EDMProducer #PsytranceProducer #MusicProduction #FLStudioEDM
#AbletonLive #DJSet #TrackPreview #Ajja #PsychedelicMusic
#PsytranceWorld #PsytranceCulture #PsytranceArt #PsytranceCommunity
#Zenonesque #HiTechPsytrance #MelodicEDM #ProgressiveTrance #DanceLiveLoveArtLife
#Trance #House #BPM #Creativity #SpiritualEnlightenment #Spirituality
#PsytranceFamily #FullOnPsytrance #ProgressivePsytrance #GoaTrance #DarkPsy
#PsytranceMix #DJMix #NewEDM #HyperNexus
```

### Rules
- Always include #Psytrance in 1-3 hashtags per post
- Always include the dedicated genre hashtag
- All content is EDM with a specific genre style — hashtag both
- `build_hashtags()` in `youtube_update_descriptions.py` auto-generates this

## Content Originality System (2026-08-24)

### Varied Mission Verbiage (NEVER repeat the same text)
`daily_scheduler.py` has `MISSION_VARIATIONS` — 8 different phrasings of the Bob & Lum / Hymnmania story. `build_post()` randomly picks one per post.

### Inquisitive Reel CTAs (5 rotations)
`fb_stories.py` `post_to_facebook_reel()` rotates 5 short question CTAs:
- "Can this [genre] frequency elevate your spirit? 👇"
- "Which hymn should we resurrect next? 👇"
- "Does electronic worship hit different for you too? 👇"
- "Feel that beat sync with your soul? 👇"
- "Would you dance to this in a cathedral of light? 👇"

### Link Spacing (CRITICAL)
YouTube links MUST have a blank line BEFORE and AFTER (else preview card doesn't populate):
```
Watch the full 4K visual journey on YouTube!

https://youtube.com/watch?v=XXX

#hashtags
```

### Facebook Reels Caption Field
Use `keyboard.type()` (NOT `execCommand`) — the field placeholder is "Describe your reel...". React ignores execCommand.

### Facebook Reels — WORKING (FIXED 2026-08-24)
Complete working flow:
1. facebook.com/reels/create
2. Upload 9:16 video (input[type=file])
3. Wait for "Your reel is safe to publish!" (copyright check)
4. Click "Next" (edit options)
5. Click "Next" (caption step)
6. Type caption via keyboard.type (NOT execCommand — React ignores it). Field placeholder = "Describe your reel..."
7. SCROLL DOWN (mouse.wheel 3000) to reveal the Post button
8. Click "Post" by mouse COORDINATES (not JS .click() — the button is below the fold and JS click hits wrong element)
   - Get rect: Array.from(buttons).filter(text==='Post'), scrollIntoView, getBoundingClientRect, mouse.click(cx, cy)

CRITICAL: The Post button is BELOW the fold. MUST scroll + click by coordinates. JS .click() on the hidden button does nothing.

### Facebook Stories — WORKING
`stories/create` → upload 20s 9:16 clip → "Share to story". Confirmed live.

### YouTube Shorts — WORKING
9:16 vertical <60s, `#Shorts` in title, full description with ≤15 hashtags SEO + #EDM + #Psytrance + genre.
