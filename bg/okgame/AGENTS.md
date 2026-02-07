# Visualizer Integration Status

Please refer to [LLM_INSTRUCTIONS.md](LLM_INSTRUCTIONS.md) for the master instruction set.

## Submodules
The following submodules have been added for visualizer integration:

### Code Repositories (in `lib/`)
- `lib/projectm`: Core visualizer engine (Robert Pelloni's fork).
- `lib/MilkDrop3`: MilkDrop3 implementation.
- `lib/geiss`, `lib/butterchurn`, `lib/milkdrop2077`, `lib/frontend-sdl-cpp`, `lib/BeatDrop`, `lib/milkdrop2`, `lib/milkdrop-preset-utils`, `lib/milkdrop-preset-converter-node`, `lib/MilkDrop-MusicVisualizer`, `lib/Milkwave`, `lib/projectm-eval`.

### Presets (in `resources/presets/`)
- `presets-milkdrop-texture-pack`
- `presets-cream-of-the-crop`
- `presets-projectm-classic`
- `presets-milkdrop-original`
- `presets-en-d`
- `butterchurn-presets`
- `poweramp-visualizer-presets`
- `milkdrop-preset-collection`
- `Milkdrop3-Portal-Presets`
- `tens-of-thousands-milkdrop-presets-for-butterchurn`
- `Rhythmbeam-Milkdrop`
- `milkdrop-presets`

## Integration Plan
To fully integrate `projectM` as a background:
1.  **Build System**: [COMPLETED] Update `CMakeLists.txt` to build `lib/projectm`. Note that `projectm` has its own dependencies (glm, etc.).
2.  **Render Loop**: [COMPLETED] In `BobsGame::render()` or `BGClientEngine::render()`, integrate the visualizer rendering call. `frontend-sdl-cpp` contains examples of SDL/OpenGL integration.
3.  **Input**: [COMPLETED] Feed audio data from `AudioManager` (e.g., FMOD or SDL_mixer output) to `projectM::pcm_add`.
4.  **Preset Loading**: [COMPLETED] Implemented preset loading in `BobsGame::init()`.
5.  **Texture Paths**: [COMPLETED] Configured `projectM` to look for textures in `resources/presets/presets-milkdrop-texture-pack/textures` (dev) and `data/presets/...` (prod).
6.  **Deployment**: [COMPLETED] Updated `_copy.bat` to copy `resources/presets` to `data/presets` for distribution.

## Refactoring Status
The engine (BobsGame, NDMenu, RPG) has been refactored to use `std::shared_ptr` for better memory management, which facilitates adding complex subsystems like visualizers without leak risks.
