# HymnMania Roadmap

## Phase 1: MIDI → MP3 Pipeline ✅

- [x] FluidSynth rendering with soundfonts
- [x] Speed variants (0.5x, 1.0x, 1.5x, 2.0x, 3.0x)
- [x] Batch rendering (~33K MIDI files)
- [x] Audio modification (pitch shift, filtering, delay)
- [x] Database: 11,479 hymns with SHA256 dedup, 1,388 with lyrics

## Phase 2: Suno AI Generation ✅

- [x] Audio upload via CDP (Suno API)
- [x] Genre conditioning (11 genres)
- [x] Clip polling + download (A/B versions)
- [x] Extend / continuation generation
- [x] v5.5 model selection
- [x] **Cover pipeline**: Upload hymn as original track → Create Cover
- [x] **Classical pipeline**: 104 classical covers across genres
- [x] **Studio Reversal** (v1.37.0): Validated, Packaged & Web-Integrated
- [x] **Full hymn pipeline**: 15 hymns × 11 genres × 5 speeds with NNT subtitles

## Phase 3: Video Rendering ✅

- [x] MilkDrop visualization via projectM
- [x] FFmpeg video compositing (audio + visualizer)
- [x] Beat-synced video with phrase-boundary clip switching
- [x] Tempo-scaled beat phrases (4/8/12/16 based on BPM)
- [x] Magnific AI video clip generation (MiniMax Hailuo 2.3 Fast 768p)
- [x] Crossfade transitions (0.4s ffmpeg xfade)
- [x] Custom thumbnails with genre + hymn overlay
- [x] INTRO/OUTRO with genre-matched text styles
- [x] 700+ YouTube videos rendered

## Phase 4: Distribution ✅

- [x] YouTube upload automation (OAuth2)
- [x] YouTube title standardization (Hymn + Classical formats)
- [x] YouTube description templates with social links + AI JSON-LD metadata
- [x] YouTube Shorts: 9:16 vertical converter + uploader
- [x] Facebook posting automation (CDP via Edge, 50+ posts)
- [x] Facebook post template with video preview cards
- [x] Instagram posting template + credentials
- [x] TikTok poster: 9:16 convert + CDP upload (`tiktok_poster.py`)
- [x] Weekly scheduler bot: Mon-Fri auto-posting (`scheduler_bot.py`)
- [x] Unified cross-platform posting (`post_all_platforms.py`)
- [x] Single-page Dashboard Console (`dashboard_server.py` at port 8083)
- [x] Background System Tray Server Manager (`systray_app.py`)
- [x] SpiritualEDM hashtag across all platforms
- [ ] YouTube playlist management
- [ ] YouTube Community tab (requires 500 subscribers)

## Phase 5: Future

- [ ] Holiday themed megamixes — mix multiple hymns per genre into one long video
- [ ] All-genre megamix — combine best segments from each genre
- [ ] Multi-voice vocal harmonization (ElevenLabs)
- [ ] Auto-DJ/Live Stream: 24/7 YouTube live stream with real-time MilkDrop
- [ ] Local AI Audio Cover Generation (Stable Audio Open, AudioCraft)
- [ ] Batch YouTube Shorts converter
