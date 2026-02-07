# Editor Roadmap

This roadmap outlines the prioritized implementation of features for the Bob's Game Editor (Legacy Swing Editor), based on research from industry-standard tools like Aseprite, Tiled, and Pyxel Edit.

## Phase 1: Foundations (Immediate Priority)
These features are essential for any usable editor and are currently missing or underdeveloped.

1.  **Layer System** [COMPLETED]
    *   **Description:** Move from a single flat image to a multi-layer stack.
    *   **Status:** Implemented. Includes `List<Layer>` model, Composite Rendering, and `SELayerPanel` UI.
    *   **Note:** Layers are flattened to a single image on export for game engine compatibility.

2.  **Project Persistence** [COMPLETED]
    *   **Description:** Save editor state (layers, visibility, opacity) to a dedicated project file (`.sprproj` / JSON).
    *   **Status:** Implemented. Uses `SpriteProject` class with GZIP+Base64 encoding for pixel data.
    *   **Why:** Enables non-destructive editing and resuming work with layers intact.

3.  **Universal Brush System** [COMPLETED]
    *   **Description:** Abstract the drawing logic so "Pencil", "Eraser", and "Pattern Stamp" share a common interface.
    *   **Status:** Implemented. `Brush` interface created with `PixelBrush`, `EraserBrush`, `FillBrush`. Added `SEToolsPanel`.
    *   **Requirements:** `Brush` interface, `PixelBrush`, `ShapeBrush`, `PatternBrush`. Support for "Custom Brushes" (using a selection as a brush).

4.  **File Format Support (Interoperability)** [COMPLETED]
    *   **Description:** Interoperability with standard tools.
    *   **Status:** Implemented `AsepriteImporter` and `AsepriteParser`. Can import `.ase`/`.aseprite` files (Indexed Mode).
    *   **Goal:** Import `.ase` / `.aseprite` (Aseprite) files. This allows users to create art in Aseprite and bring it into the engine.

## Phase 2: Workflow Enhancements
Tools that speed up the creation process.

5.  **Selection Tools** [COMPLETED]
    *   **Description:** Robust selection capabilities beyond rectangles.
    *   **Status:** Implemented `MagicWandBrush` and mask-based `SelectionArea`.
    *   **Goal:** Magic Wand (Color Select), Polygon Lasso, "Select All of Color".

6.  **Symmetry / Mirror Drawing** [COMPLETED]
    *   **Description:** Real-time mirroring of drawing operations on X and Y axes.
    *   **Status:** Implemented Y-Axis symmetry (Quad symmetry supported). Updated `SECanvas` rendering and `setPixel` logic.
    *   **Why:** Standard feature in Pyxel Edit, Aseprite, Tiled.

7.  **Onion Skinning** [COMPLETED]
    *   **Description:** See previous/next frames faintly while animating.
    *   **Status:** Implemented via `SECanvas.repaintBufferImage` rendering prev/next frames with alpha blending.
    *   **Requirements:** Animation timeline integration.

## Phase 3: Advanced Features
Differentiation features that provide unique value.

8.  **Tile Instancing (Pyxel Edit Style)** [COMPLETED]
    *   **Description:** Editing a tile on the map updates the source tile and all other instances of it instantly.
    *   **Status:** Implemented `tileEditMode` in `MapCanvas`. Allows drawing pixel-level edits directly on the map.
    *   **Why:** Huge time saver for tilemap creation.

9.  **Auto-tiling (Wang/Blob)** [COMPLETED]
    *   **Description:** Automatically selecting the correct tile variation based on neighbors (corners, edges).
    *   **Status:** Implemented 4-bit (16-tile) Edge Auto-tiling logic in `AutoTiler` and integrated into `MapCanvas` as `autoTileMode`.

10. **Reference Layers** [COMPLETED]
    *   **Description:** Layers that hold reference images but are excluded from the final export/game data.
    *   **Status:** Implemented `isReference` boolean in `Sprite.Layer`. Updated export methods (`getAsIntArray`, `outputPNG`, etc.) to skip these layers. Added UI toggle in `SELayerPanel`.

## Execution Plan (Next Steps)

All major features from the roadmap have been implemented.

1.  **Refine & Polish:**
    *   Ensure all new features (Timeline, Animation List, History) work smoothly together.
    *   Verify Undo logic with the new `UndoManager` features.
2.  **Maintenance:**
    *   Keep submodules updated.
    *   Monitor for regressions in legacy game functionality.
