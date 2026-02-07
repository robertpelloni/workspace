# Submodule Dashboard

> Last updated: January 11, 2025

This project uses **89 git submodules** for external dependencies and preset collections.

## Quick Stats

| Category | Count |
|----------|-------|
| Code Libraries (lib/) | 77 |
| Visualizer Presets (resources/presets/) | 12 |
| **Total** | **89** |

## Commands

```bash
# Initialize all submodules
git submodule update --init --recursive

# Update all submodules to latest
git submodule update --remote --merge

# Check submodule status
git submodule status
```

---

## Code Libraries (lib/)

### SDL Ecosystem

| Path | Version/Tag | Description |
|------|-------------|-------------|
| lib/SDL | release-2.32.0-145 | Simple DirectMedia Layer |
| lib/SDL2_gfx | release-1.0.4-5 | SDL2 graphics primitives |
| lib/SDL_gesture | heads/main | SDL gesture recognition |
| lib/SDL_image | release-2.8.0-157 | Image loading |
| lib/SDL_mixer | release-2.8.0-126 | Audio mixing |
| lib/SDL_native_midi | heads/main | Native MIDI support |
| lib/SDL_net | release-2.2.0-76 | Networking |
| lib/SDL_rtf | heads/main | Rich text format |
| lib/SDL_ttf | release-2.24.0-23 | TrueType font rendering |
| lib/sdl2-compat | release-2.32.60-8 | SDL2 compatibility layer |

### Visualizers (MilkDrop/projectM)

| Path | Version/Tag | Description |
|------|-------------|-------------|
| lib/projectm | v3.1.8-693 | **Primary visualizer engine** (Robert Pelloni fork) |
| lib/projectm-eval | v1.0.0-26 | projectM expression evaluator |
| lib/MilkDrop3 | MilkDrop3-74 | MilkDrop3 implementation |
| lib/milkdrop2 | heads/master | MilkDrop2 |
| lib/milkdrop2077 | heads/main | MilkDrop 2077 |
| lib/butterchurn | heads/master | WebGL MilkDrop |
| lib/geiss | 4.30-82 | Geiss visualizer |
| lib/Milkwave | v3.4-4 | Milkwave visualizer |
| lib/BeatDrop | v1.0.0.0-1 | BeatDrop visualizer (Robert Pelloni fork) |
| lib/MilkDrop-MusicVisualizer | heads/master | MilkDrop music visualizer |
| lib/milkdrop-preset-utils | heads/master | Preset utilities |
| lib/milkdrop-preset-converter-node | heads/master | Preset converter |
| lib/frontend-sdl-cpp | heads/master | SDL frontend for projectM |

### Emulators (Libretro)

| Path | Version/Tag | Description |
|------|-------------|-------------|
| lib/RetroArch | v1.2-44970 | RetroArch frontend |
| lib/libretro-common | heads/master | Common libretro code |
| lib/libretro-database | v1.22.1-9 | Libretro database |
| lib/libretro-fceumm | heads/master | FCEUmm NES emulator |
| lib/libretro-lutro | heads/master | Lua game framework |
| lib/libretro-samples | heads/master | Sample cores |
| lib/libretro-super | Latest-966 | Build system |
| lib/retroarch-assets | v1.22.0-4 | RetroArch assets |
| lib/retroarch-joypad-autoconfig | v1.22.0 | Controller configs |
| lib/snes9x | 1.53-2502 | SNES emulator |
| lib/snes9x2010 | heads/master | SNES emulator (2010) |
| lib/nestopia | heads/master | NES emulator |
| lib/Genesis-Plus-GX | heads/master | Genesis/Mega Drive |
| lib/desmume | release_0_9_13-404 | Nintendo DS |
| lib/gambatte-libretro | heads/master | Game Boy |
| lib/vba-next | heads/master | GBA emulator |
| lib/vbam-libretro | heads/master | VBA-M |
| lib/gpsp | heads/master | GBA emulator |
| lib/FBNeo | v1.0.0.02-7471 | Final Burn Neo |
| lib/picodrive | heads/master | Genesis/32X |
| lib/mgba | heads/master | GBA/GB emulator |
| lib/melonDS | 0.8.1-1741 | Nintendo DS |

### Audio Codecs & Libraries

| Path | Version/Tag | Description |
|------|-------------|-------------|
| lib/vorbis | v1.3.7-22 | Ogg Vorbis |
| lib/ogg | v1.3.6-6 | Ogg container |
| lib/opus | v1.6-13 | Opus codec |
| lib/opusfile | v0.12-56 | Opus file I/O |
| lib/flac | 1.3.1-1098 | FLAC codec |
| lib/mpg123 | v1.30.0-24 | MP3 decoder |
| lib/game-music-emu | 0.6.3-222 | Game music emulation |
| lib/MODPlay | heads/master | MOD player |
| lib/libmodplug | heads/master | MOD plugin |
| lib/libmidi | v1.0.1-75 | MIDI library |
| lib/libtimidity | libtimidity-0.2.6-47 | TiMidity |
| lib/timidity | heads/cvs | TiMidity++ |
| lib/tremor | heads/sezero | Fixed-point Vorbis |
| lib/soundtouch | 2.3.3-14 | Audio processing |
| lib/libxmp | libxmp-4.6.3-87 | XM/MOD player |
| lib/WavPack | 5.1.0-427 | WavPack codec |
| lib/paulxstretch | 1.2.2-192 | Audio stretching |

### Graphics & Fonts

| Path | Version/Tag | Description |
|------|-------------|-------------|
| lib/freetype | VER-2-14-1-31 | Font rendering |
| lib/harfbuzz | 12.2.0-87 | Text shaping |
| lib/imgui | v1.62-5120 | Immediate mode GUI |
| lib/glew | glew-1.10.0-478 | OpenGL extension wrangler |
| lib/glad | v0.1.11a-307 | GL loader |
| lib/glfw | 3.4-61 | Window/context |
| lib/nanovg | heads/master | Vector graphics |
| lib/nanogui | heads/master | GUI library |
| lib/nanogui-sdl | heads/master | NanoGUI SDL backend |
| lib/nngui | heads/master | NN GUI |
| lib/Nuklear | 4.12.8-22 | Immediate mode GUI |
| lib/lvgl | v9.3.0-805 | Light/versatile graphics |
| lib/GWEN | heads/main | GUI library |
| lib/raylib | 5.5-1494 | Game library |
| lib/plutosvg | v0.0.7-12 | SVG rendering |
| lib/plutovg | v1.3.2 | Vector graphics |
| lib/stb | heads/master | Single-file libraries |

### Image Formats

| Path | Version/Tag | Description |
|------|-------------|-------------|
| lib/libpng | v1.6.53-3 | PNG library |
| lib/jpeg | heads/main | JPEG library |
| lib/libtiff | v4.7.1-80 | TIFF library |
| lib/libwebp | v1.6.0-146 | WebP codec |
| lib/libavif | v1.3.0-106 | AVIF codec |
| lib/libjxl | v0.11-snapshot-462 | JPEG XL |
| lib/aom | v3.13.1-172 | AV1 codec |
| lib/dav1d | 1.5.2-18 | AV1 decoder |
| lib/highway | 1.3.0-188 | SIMD library |

### Compression

| Path | Version/Tag | Description |
|------|-------------|-------------|
| lib/zlib | v1.3.1 | Compression |
| lib/brotli | v1.1.1-rc0-139 | Brotli compression |
| lib/miniz | 3.1.0 | Mini zlib |
| lib/lz4-java | 1.8.0-13 | LZ4 compression |

### Networking & System

| Path | Version/Tag | Description |
|------|-------------|-------------|
| lib/poco | poco-1.14.2-release-202 | C++ class libraries |
| lib/boost | boost-1.71.0.beta1-4503 | Boost libraries |
| lib/libusb | v1.0.23-rc1-626 | USB access |
| lib/sigar | sigar-1.6.4-475 | System information |
| lib/mpv | v0.41.0-39 | Media player |

### Utilities

| Path | Version/Tag | Description |
|------|-------------|-------------|
| lib/CTPL | ctpl_v.0.0.2 | Thread pool |
| lib/MicroPather | heads/master | A* pathfinding |
| lib/defold-astar | v1.2.1-3 | A* implementation |
| lib/cppcodec | v0.2-11 | Base64/Base32 |
| lib/md5-c | heads/main | MD5 hashing |
| lib/Snippets | heads/master | Code snippets |
| lib/sumatrapdf | 3.1.2rel-6544 | PDF library |

### Games & Examples

| Path | Version/Tag | Description |
|------|-------------|-------------|
| lib/Craft | v1.0-17 | Minecraft clone |
| lib/Maelstrom | release-3.0.7-6 | Classic Mac game |
| lib/CLove | heads/master | LOVE2D in C |
| lib/UACME | v3.6.9-1 | Windows UAC |
| lib/BufferedImage | heads/main | Image buffer |

---

## Visualizer Presets (resources/presets/)

| Path | Version/Tag | Description |
|------|-------------|-------------|
| resources/presets/presets-milkdrop-texture-pack | heads/master | Texture pack |
| resources/presets/presets-cream-of-the-crop | heads/master | Curated presets |
| resources/presets/presets-projectm-classic | heads/master | Classic projectM |
| resources/presets/presets-milkdrop-original | heads/master | Original MilkDrop |
| resources/presets/presets-en-d | heads/master | en-D presets |
| resources/presets/butterchurn-presets | heads/master | Butterchurn collection |
| resources/presets/poweramp-visualizer-presets | 1.2 | Poweramp presets |
| resources/presets/milkdrop-preset-collection | heads/master | Large collection |
| resources/presets/Milkdrop3-Portal-Presets | v1.0.0-2 | MilkDrop3 Portal |
| resources/presets/tens-of-thousands-milkdrop-presets-for-butterchurn | heads/master | Massive collection |
| resources/presets/Rhythmbeam-Milkdrop | 1.0.0-alpha.1 | Rhythmbeam |
| resources/presets/milkdrop-presets | heads/master | General presets |

---

## Robert Pelloni Forks

These submodules are maintained as forks by robertpelloni:

| Path | Original | Notes |
|------|----------|-------|
| lib/projectm | projectm-visualizer/projectm | Custom modifications |
| lib/BeatDrop | - | Visualizer integration |
| lib/GWEN | - | GUI library |
| lib/frontend-sdl-cpp | - | SDL frontend |

---

## Maintenance Notes

### Submodules Showing "Modified Content"
This typically means the submodule's working directory has local changes. To reset:
```bash
git submodule foreach --recursive git checkout .
git submodule foreach --recursive git clean -fd
```

### Updating a Single Submodule
```bash
cd lib/projectm
git fetch origin
git checkout <tag-or-branch>
cd ../..
git add lib/projectm
git commit -m "Update lib/projectm to <version>"
```

### Adding a New Submodule
```bash
git submodule add <url> lib/<name>
git commit -m "Add lib/<name> submodule"
```

---

## Related Documentation

- [AGENTS.md](AGENTS.md) - Project overview
- [LLM_INSTRUCTIONS.md](LLM_INSTRUCTIONS.md) - AI instructions
