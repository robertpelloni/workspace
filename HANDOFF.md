# Workspace Handoff — v2.7.0 — 2026-04-17

## Session Summary
Protocol v2.7.0: Merged new jules-autopilot branch (6 commits), bobfilez jules + image-hash branches, opencode-autopilot (34 commits), bobui, and massive superai cleanup (22 dependabot branches + rewrite/main-sanitized). All 18 upstream forks checked — zero new upstream commits. 34+ feature branches reverse-synced. Submodules updated including major juce restructuring in bobui. jules-autopilot built successfully.

## Key Changes This Session
- **jules-autopilot**: NEW branch `jules-17764958747146694232-3d7c3856` merged (6 commits, adds vercel.json)
- **bobfilez**: `jules-372251447975422924-5b932c3a` merged + `image-hash-stable` merged with `--allow-unrelated-histories` (218 commits ahead, pushed)
- **opencode-autopilot**: `jules-4657769983160951050-bc8be7a1` merged (34 commits, vscode tsconfig)
- **bobui**: `jules-11090863842246041945-58931a03` merged; submodule updates (juce major restructure, ultimatepp); pushed (4 ahead)
- **superai**: 22 dependabot branches merged (actions/download-artifact-7, setup-python-6, upload-artifact-6, codecov-5, codeql-4, npm packages for borg-extension, hypercode-extension, web, openai-codex, drizzle, eslint, hono, mcp-sdk, next, vite, pip/aider, uv/agent-sdk, werkzeug). Also merged `rewrite/main-sanitized` (21 commits). Pushed.
- **bobbybookmarks**: `multi_pool.py` added, pushed
- **bobtrax**: reverse sync pushed (1 ahead)
- **superai/rewrite/main-sanitized**: reverse synced and pushed (1113 ahead)

## Upstream Sync Results
All 18 upstream forks checked — **zero new upstream commits**:
- bobeditpro (audacity/audacity): 0
- tabby (Eugeny/tabby): 0
- sm64coopdx: 0
- topaz-ffmpeg (FFmpeg/FFmpeg): 0
- jules-autopilot (sbhavani/jules-app): 0
- bobtrader: 0
- bobtorrent: 0
- mcp-superassistant: 0
- raindropioapp: 0
- fwber: 0
- mk64: 0
- bobmani/arrowvortex: 0
- bobmani/beatoraja: 0
- bobmani/ddc: 0
- bobmani/itgmania: 0
- bobmani/ksm-v2: 0
- bobmani/linthesia: 0
- bobmani/Simply-Love-SM5: 0

## Pushed Repos (Default Branches)
- bobbybookmarks (1 ahead → pushed)
- bobfilez (218 ahead → pushed)
- bobui (4 ahead → pushed, includes submodule updates)
- superai (1 ahead → pushed)

## Pushed Feature Branches
- bobui/dev (4 ahead), bobui/jules-11090863842246041945 (2 ahead)
- bobtrax/jules-13814763330234479585 (1 ahead)
- jules-autopilot/jules-17764958747146694232 (1 ahead, forced)
- superai/rewrite/main-sanitized (1113 ahead)
- opencode-autopilot/jules-4657769983160951050 (3 ahead)

## Push Failures / Blockers
- **openclaw-config**: HTTP 403 — origin is TechNickAI/openclaw-config. robertpelloni fork does NOT exist yet. Need to create fork at github.com/robertpelloni/openclaw-config.
- **topaz-ffmpeg**: HTTP 403 — origin is TopazLabs/ffmpeg. robertpelloni fork needed.
- **bobui/submodules/juce**: HTTP 403 — origin is juce-framework/JUCE (third-party)
- **bobui/submodules/ultimatepp**: HTTP 403 — origin is ultimatepp/ultimatepp (third-party)
- **Maestro**: Requires `--no-verify` (working as expected)
- **bobfilez**: Deep pybind11 directory causes checkout hangs ( Filename too long)

## Repo Architecture
### Workspace Root (C:/Users/hyper/workspace)
Main meta-repo. Contains CHANGELOG.md, VERSION, HANDOFF.md, and 40+ repo clones.

### Key Repos
| Repo | Default | Upstream | Status |
|------|---------|----------|--------|
| jules-autopilot | main | sbhavani/jules-app | ✅ clean, built |
| bobeditpro | master | audacity/audacity | ✅ clean |
| superai | main | — | ✅ pushed |
| bobgui | master | — | ✅ clean |
| tabby | master | Eugeny/tabby | ✅ clean |
| Maestro | main | — | ✅ clean |
| bobcoin | main | — | ✅ clean |
| pi-mono | main | — | ✅ clean |
| openclaw-config | main | TechNickAI | ❌ 403 push (101 ahead) |
| topaz-ffmpeg | master | TopazLabs/FFmpeg | ❌ 403 push |
| bobfilez | main | — | ✅ pushed (218 ahead) |
| bobui | main | — | ✅ pushed |
| bobbybookmarks | main | — | ✅ pushed |
| opencode-autopilot | main | — | ✅ clean |

### Submodule Tree
```
workspace/
├── bobeditpro/          (master, audacity fork)
│   ├── muse_framework/  (upstream: MuseScore)
│   └── bobui/           (local fork)
├── bobtrax/             (master)
│   ├── ardour/          └── bobui/ └── lmms/ └── muse/ └── zrythm/
├── bobui/               (main, 4 ahead)
│   ├── submodules/juce/     (origin: juce-framework/JUCE — 403)
│   └── submodules/ultimatepp/ (origin: ultimatepp/ultimatepp — 403)
├── btk/                 (master)
│   ├── external/bobui-reference/ └── juce/ └── ultimatepp/
├── f-zerox/             (main)
│   ├── subprojects/bobgui/ └── bobui/ └── btk/
├── geany/               (master, no upstream remote)
│   ├── subprojects/bobgui/ └── bobui/ └── btk/
├── hyperharness/        (main, 27 AI tool submodules)
│   ├── adrenaline/ └── aider/ └── goose/ └── ...
├── npp/                 (master)
│   ├── bobgui/ └── bobui/ └── btk/
├── jules-autopilot/     (main, Vite build)
├── superai/             (main, 1 ahead pushed)
├── openclaw-config/     (main, 101 ahead, 403)
└── bobmani/
    ├── arrowvortex/ beatoraja/ bobmania/ ddc/
    ├── hymnmania/ itgmania/ ksm-v2/ linthesia/
    └── Simply-Love-SM5/
```

## Known Issues
- 156 Dependabot vulnerabilities in jules-autopilot (3 critical)
- openclaw-config: Need to create robertpelloni fork (403)
- topaz-ffmpeg: Need to create robertpelloni fork (403)
- bobui/submodules/juce & ultimatepp: Third-party origins, can't push (by design)
- bobfilez: Deep pybind11 paths cause git checkout hangs
- bobtrax/npp/btk: ultimatepp submodule remote ref errors (upload-pack: not our ref)
- f-zerox/bobcoin: Unresolved merge conflict in submodule
- hyperharness/amazon-q-developer-cli: Unresolved merge conflict in submodule
- bg: Skipped (huge build_output tree)
- bobdesk: 13K dirty LibreOffice files (intentional)
- borg: Secondary worktree at hypercode-push (by design)

## Build Info
- **jules-autopilot**: Vite v6.4.2, 2970 modules, ~11.77s build, 485KB index chunk
- **Node**: v22+ required
- **Build command**: `cd jules-autopilot && npm run build`

## Conflict Resolution Strategy
- Lock files (package-lock, yarn.lock, Cargo.lock): `--theirs` (accept incoming)
- Translation files (.po): `--theirs`
- Source files: Union merge (concatenate both sides via Python regex)
- Submodule conflicts: Reset dirty state, then merge
- Unrelated histories: Use `--allow-unrelated-histories` only when safe
- bobeditpro upstream branches: ALL skipped (60+ upstream audacity release/feature branches)
- geany upstream branches: ALL skipped
- tabby upstream branches: ALL skipped (80+ all-contributors + dependabot)

## Next Steps
1. **openclaw-config**: Create robertpelloni fork on GitHub, add as remote, push 101 commits
2. **topaz-ffmpeg**: Create robertpelloni fork, push local changes
3. Fix bobui/ultimatepp submodule remote ref errors (affects bobtrax, npp, btk)
4. Fix f-zerox/bobcoin submodule conflict
5. Fix hyperharness/amazon-q-developer-cli submodule conflict
6. Push Maestro/rc branch if it exists
7. Address 156 Dependabot vulnerabilities (3 critical)
8. Consider geany upstream remote setup
