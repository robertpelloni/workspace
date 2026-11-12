# ROADMAP.md â€” HymnMania & Workspace

## Current Status (v5.292.0)

**Protocol #283 (2026-11-07):** 42 forward merges pushed (23 plain + 11 deferred-after-dirty-commit + 8 -X theirs), 28 fast-forwards, 65 submodule pointers staged; 5 conflict branches retained; system Git broken (GitHub Desktop git used).
**Protocol #282 (2026-11-07):** 22 fast-forwards + 10 forward merges pushed (bobmani x6 incl. beatoraja master close, jvm-cpp-runtime +17, gods-eye-view, ww3_game); fetch 133/133; 3 conflict branches retained (freellm x2, itgmania jules-1251).

**Protocol #281 (2026-11-07, leader run):** 77 fast-forwards + 7 merges pushed; resolved slsk/veilid/sales_bot retained branches; stacked on origin #280 (no divergence).

**Protocol #278 (2026-11-05):** 36 forward merges pushed; bobmani/beatoraja master closed (+125); _fix repos published; 5 conflict branches retained for Robert's disposition decision.

**Protocol #277 (2026-11-05):** 91 forward merges pushed (~45 repos incl. bcs x5, pi-mono, succubus.red, educational_video_pipeline, mparty, make_elon_laugh, webapp_factory); 132/133 submodules initialized; 5 conflict-final branches retained for dedicated sessions (freellm temp-main, slsk, veilid scaffold, itgmania jules-1251, sales_bot sirens).

### HymnMania Pipeline

| Component | Status | Notes |
|-----------|--------|-------|
| MIDI Database | âœ… Complete | 11,470+ hymns |
| Audio Synthesis | âœ… Complete | FluidSynth rendering |
| Suno Cover Generation | âœ… Complete | v5.5 model via browser automation |
| Video Generation | âœ… Complete | projectM + ffmpeg |
| YouTube Uploads | âœ… 197 videos | OAuth working |
| TikTok Vertical Crop | âœ… 81 videos | 9:16 format (1080x1920) |
| TikTok Uploads | â³ Pending | Requires Zernio API setup |
| Facebook Posting | âœ… Working | daily_scheduler.py |

### Workspace Merges (v5.282.0)

| Repository | Branch Merged | Description |
|------------|---------------|-------------|
| root | dependabot npm+uv | 5 dependency updates |
| projectM-upstream | origin/master | HLSL/PCM fixes |
| HyperNexus2old | origin/main | VectorStore, MCP catalog, Ollama embeddings (133 conflicts resolved) |
| skillzhub | dependabot-3d78e36c6 | 4 dependency updates |
| bobcoin | dependabot-dcc3f92f05 | 1 dependency update |
| apophysis-j | jules-032566ef | v2.10.20 milestone |
| OpenMBU | party-framework | Party framework enhancements |
| MilkDrop3_fix | remote/main | Added aios submodule |

## Next Steps

### Immediate (This Week)

1. **Zernio Setup**: Sign up at zernio.com, get API key, connect TikTok
2. **TikTok Batch Upload**: Upload 81 vertical videos
3. **YouTube Uploads**: Continue when quota resets (50 hymn videos remaining)

### Short Term (This Month)

1. **Magnific Clips**: Download remaining clips for new hymns
2. **Video Generation**: Generate videos for all hymn variations
3. **Social Media Automation**: Schedule posts across platforms

### Long Term (Q3 2026)

1. **Full Automation**: End-to-end pipeline with no manual intervention
2. **Multi-Platform**: TikTok, YouTube, Instagram, Facebook
3. **Analytics**: Track engagement and optimize content

## Technical Debt

- ArrowVortex nested submodule issue (ffr-difficulty-model)
- bobmani submodule dirty state (local changes)
- Upstream branches in hermes-agent, fwber, bgtk (not merged)

## Version History

- v5.282.0: Repository sync, dependabot merges, projectM-upstream/HyperNexus2old feature branch reconciliation
- v5.281.0: Repository sync, dependabot merges, hymnmania/projectM/freellm feature branch reconciliation
- v5.268.0: Repository sync, feature branch merges, HymnMania TikTok pipeline
- v5.267.0: Feature branch merge round 2
- v5.266.0: Repository sync, hyperharness merge
- v5.265.0: Dependabot branch sweep
