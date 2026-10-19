🛠️ ALPHA SOFTWARE UNDER CONSTRUCTION — Use at your own risk. Backwards compatibility not guaranteed.

```text
╔══════════════════════════════════════════════════════════════════════════════╗
║                                                                              ║
║                     ██╗   ██╗███╗   ██╗██████╗ ███████╗██████╗              ║
║                     ██║   ██║████╗  ██║██╔══██╗██╔════╝██╔══██╗             ║
║                     ██║   ██║██╔██╗ ██║██║  ██║█████╗  ██████╔╝             ║
║                     ██║   ██║██║╚██╗██║██║  ██║██╔══╝  ██╔══██╗             ║
║                     ╚██████╔╝██║ ╚████║██████╔╝███████╗██║  ██║             ║
║                      ╚═════╝ ╚═╝  ╚═══╝╚═════╝ ╚══════╝╚═╝  ╚═╝             ║
║                                                                              ║
║                     ██████╗ ██████╗ ███╗   ██╗███████╗████████╗██████╗      ║
║                    ██╔════╝██╔═══██╗████╗  ██║██╔════╝╚══██╔══╝██╔══██╗     ║
║                    ██║     ██║   ██║██╔██╗ ██║███████╗   ██║   ██████╔╝     ║
║                    ██║     ██║   ██║██║╚██╗██║╚════██║   ██║   ██╔══██╗     ║
║                    ╚██████╗╚██████╔╝██║ ╚████║███████║   ██║   ██║  ██║     ║
║                     ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝   ╚═╝   ╚═╝  ╚═╝     ║
║                                                                              ║
║                     █████╗ ██╗     ██████╗ ██╗  ██╗ █████╗                  ║
║                    ██╔══██╗██║     ██╔══██╗██║  ██║██╔══██╗                 ║
║                    ███████║██║     ██████╔╝███████║███████║                 ║
║                    ██╔══██║██║     ██╔═══╝ ██╔══██║██╔══██║                 ║
║                    ██║  ██║███████╗██║     ██║  ██║██║  ██║                 ║
║                    ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝                 ║
║                                                                              ║
║                    ╔══════════════════════════════════════╗                  ║
║                    ║     ⚠️  ALPHA SOFTWARE  ⚠️           ║                  ║
║                    ║  EXPECT BREAKING CHANGES & BUGS     ║                  ║
║                    ║  NOT READY FOR PRODUCTION USE       ║                  ║
║                    ╚══════════════════════════════════════╝                  ║
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝
```

---
[hymnmania](https://github.com/robertpelloni/hymnmania) — **v5.97.5**

## 🎵 Automated Hymn → Electronic Cover → Beat-Synced Video → YouTube + Social Pipeline

HymnMania is an end-to-end automation platform that takes classical hymns and classical pieces (MIDI files), renders them as speed-adjusted audio, generates modern electronic music covers via Suno AI across 11 genres, creates beat-synced music videos with AI-generated visuals, and publishes to YouTube, Facebook, and Instagram.

### 🚀 Quick Start

```bash
# 1. Launch Edge with remote debugging
python scripts/launch_edge_suno.py

# 2. Generate a cover (Suno AI)
cd scripts
python suno_cover_remix_options_form_style_submitter.py psytrance 05x Thy_Word --instrumental

# 3. Compose beat-synced video
python quick_composer.py --audio input.mp3 --video output.mp4

# 4. Update YouTube descriptions
python youtube_update_descriptions.py

# 5. Post to Facebook
python daily_scheduler.py
```

### 📂 Project Structure

```
hymnmania/
├── scripts/                          # Active pipeline components
├── src/                              # TypeScript pipeline core
├── services/                         # Renderer workers
├── pipeline/                         # Pipeline orchestration
├── hymn_remaker/                     # MIDI rendering (FluidSynth + FFmpeg)
├── submodules/                       # Git submodules
├── data/                             # MIDI databases (~33K files)
├── docs/                             # Documentation
├── AGENTS.md                         # Agent instructions
├── CHANGELOG.md                      # Version history
├── HANDOFF.md                        # Session handoff notes
├── ROADMAP.md                        # Development roadmap
└── VERSION                           # Current version
```

### 🔗 Social Channels

| Platform | Link |
|----------|------|
| YouTube | [Resurrecting Beats](https://youtube.com/@ResurrectingBeats) |
| Facebook | [Resurrecting Beats](https://www.facebook.com/profile.php?id=61588784931149) |
| Instagram | [@ResurrectingBeats](https://www.instagram.com/resurrectingbeats) |
| TikTok | [@resurrecting.beat](https://www.tiktok.com/@resurrecting.beat) |
