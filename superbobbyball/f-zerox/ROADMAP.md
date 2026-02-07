# F-Zero X to GX/AX: Decompilation & Porting Roadmap

This document outlines the strategic roadmap to evolve the F-Zero X decompilation project into a fully-featured, native PC port with feature parity to F-Zero GX/AX and modern enhancements.

## Phase 1: Foundation (Decompilation & Shiftability)
**Goal:** A fully decompiled, C-based codebase that is "shiftable" (relocatable), allowing for code modification and expansion without breaking the ROM.

1.  **Complete Decompilation**
    -   **Current Status:** ~10% decompiled. **Documentation Phase Active** (due to missing ROM).
    -   **Action:** Systematically replace `GLOBAL_ASM` blocks with matching C code.
    -   **Priority:** High. This is the prerequisite for any meaningful porting work.
    -   **Milestone:** 100% C codebase matching the original US ROM.

2.  **Achieve Shiftability**
    -   **Current Status:** Not shiftable. Pointers and assets are hardcoded to specific ROM addresses.
    -   **Action:**
        -   Identify and label all hardcoded pointers.
        -   Implement a dynamic asset loading system or proper linker script segmentation.
        -   Ensure the build system (`splat`, `make`) supports position-independent code or automatic relocation.
    -   **Milestone:** Ability to add a new function or asset and successfully compile a working ROM (even if checksum differs).

3.  **Documentation & Naming**
    -   **Current Status:** **Partial**. Identified linked list nodes, debug functions, and math utilities.
    -   **Action:** rename variables (e.g., `func_80076498` -> `Physics_UpdateMomentum`) and document structs (e.g., `PlayerState`, `VehiclePhysics`).
    -   **Milestone:** A codebase readable by human contributors.

## Phase 2: PC Porting (Native Execution)
**Goal:** Break free from N64 hardware limitations by creating a platform abstraction layer (HAL) that runs natively on Windows/Linux/macOS.

1.  **Platform Abstraction Layer (PAL)**
    -   **Action:** Replace N64 hardware calls with generic interfaces.
        -   **Video:** Map N64 GBI (Graphics Binary Interface) commands to a modern backend (OpenGL/Vulkan/DirectX).
            -   *Reference:* Fast3D (libultragfx) or similar N64-to-PC graphics translation layers.
            -   *Status:* HAL defined (`hal.h`). SDL2 Backend initialized.
        -   **Audio:** Map N64 ABI (Audio Binary Interface) to SDL2/OpenAL.
            -   *Status:* HAL defined. SDL2 Audio Stub implemented.
        -   **Input:** Map N64 controller inputs to SDL2 input (supporting Keyboard, Gamepad, Wheels).
            -   *Status:* HAL defined. SDL2 Input Poll implemented.
    -   **Milestone:** "F-Zero X PC" executable that boots and plays original content. (Partially Achieved: Shell boots).

2.  **High-FPS & Widescreen Support**
    -   **Action:**
        -   Uncouple game logic (tick rate) from framerate to support 120Hz+ (Interpolation).
        -   Patch rendering logic to support arbitrary resolutions and aspect ratios (Ultrawide support).
    -   **Milestone:** Game runs at 1440p/4K @ 144Hz without logic speedups.

## Phase 3: Modernization (Visuals & Audio)
**Goal:** "GX Quality" presentation.

1.  **Render Pipeline Enhancements**
    -   **Action:**
        -   Implement programmable shaders to replace fixed-function N64 combiner logic.
        -   Add support for dynamic lighting, shadows, and bloom (mimicking GX's visual style).
        -   Implement Model Replacement: Allow loading .obj/.fbx/.gltf models to replace low-poly N64 assets.
    -   **Milestone:** Ability to load a "High-Res Texture/Model Pack".

2.  **Audio Engine Overhaul**
    -   **Action:**
        -   Support high-quality streaming audio (WAV/FLAC/OGG) to replace compressed MIDI sequences.
        -   Implement 3D spatial audio.

## Phase 4: Feature Parity (GX/AX Mechanics & Content)
**Goal:** Implement specific gameplay features and content from F-Zero GX and AX.

1.  **Physics Engine Variations**
    -   **Action:**
        -   Reverse engineer GX physics (Momentum Turbo Slide, different gravity/grip values).
        -   Implement a "Physics Toggle" in options: `Classic (X)`, `Modern (GX)`, `Arcade (AX)`.
    -   **Milestone:** "Snaking" works exactly as it does in GX when the option is enabled.

2.  **Content Import (Tracks & Machines)**
    -   **Action:**
        -   Create importers for GX/AX track data (.gma, .tpl).
        -   Implement GX-specific track elements: Cylinders, Half-pipes (if not fully present in X), and complex moving geometry.
        -   Port the 30+ GX machines and AX arcade exclusives.
    -   **Milestone:** Play "Mute City: Twist Road" (GX) in the F-Zero X engine.

3.  **Story Mode & Customization**
    -   **Action:**
        -   Implement a mission scripting engine (Lua or Python bindings) to recreate GX Story Mode chapters.
        -   Build a "Garage" UI for machine customization (color edit, decal editor).

## Phase 5: Expansion ("And Beyond")
**Goal:** Features never seen in the original games.

1.  **Online Multiplayer**
    -   **Action:**
        -   Implement rollback netcode (GGPO-style) or deterministic lockstep for 30-player races.
        -   Server browser and matchmaking.
    -   **Milestone:** 30-player "Death Race" online.

2.  **Modding API**
    -   **Action:** Expose game logic to scripts (Lua).
    -   **Milestone:** Community-created tracks and game modes (e.g., "Battle Royale").

3.  **VR Support**
    -   **Action:** Stereoscopic rendering and head tracking support (OpenXR).
    -   **Milestone:** F-Zero in First-Person VR.
