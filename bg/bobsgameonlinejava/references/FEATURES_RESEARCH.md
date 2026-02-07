# Editor Features Research

This document compiles a list of features found in various sprite and tile editors.

## 1. Feature Categories

### 1.1 Universal Features
These are features present in almost all robust sprite editors.
*   **Canvas & Viewport:** Zoom, Pan, Grid toggle, Pixel Grid.
*   **Basic Tools:** Pencil, Eraser, Fill Bucket, Line Tool, Rectangle/Ellipse Shape Tools.
*   **Color Management:** Palette management, Color Picker (Eyedropper), HSV/RGB sliders.
*   **Selection:** Rectangular selection, Move selection, Cut/Copy/Paste.
*   **File Operations:** Open, Save, Export (PNG, GIF).
*   **Undo/Redo:** History stack.

### 1.2 Advanced/Modern Features (High Priority)
Features that distinguish modern editors from basic paint tools.
*   **Layers:**
    *   Create, Delete, Reorder, Rename.
    *   Visibility toggle, Opacity control.
    *   Blend Modes (Normal, Multiply, Screen, Overlay, etc.).
    *   Lock layer.
*   **Animation:**
    *   Timeline view.
    *   Frames (Add, Delete, Duplicate, Move).
    *   Onion Skinning (Previous/Next frame visibility).
    *   Playback controls (Play, Pause, Loop, FPS setting).
    *   Tagging/Labeling frames (e.g., "Walk", "Jump").
*   **Tile/Grid Features:**
    *   Tilemap editing mode.
    *   Tile palette / Tileset management.
    *   Auto-tiling (Wang tiles / Blob tiles).
    *   Symmetry / Mirror drawing (X/Y axis).
*   **Brushes:**
    *   Custom brushes (draw with a selection/image).
    *   Dithering brushes.
    *   Pixel-perfect drawing mode (removes "L" shapes).

### 1.3 Unique / Standout Features
Specific features found in certain tools that offer unique value.
*   **Aseprite:**
    *   **Reference Layers:** Layers specifically for reference images that don't get exported.
    *   **Sprite Sheet Export:** Powerful packing and metadata generation.
    *   **Command Line Interface:** For batch processing.
    *   **Pixel Perfect Mode:** Algorithm to clean up lines automatically.
*   **Pyxel Edit:**
    *   **Tile Instancing:** Drawing on one tile updates all instances of that tile in the map. This is crucial for seamless pattern creation.
*   **Tiled:**
    *   **Object Layers:** Placing arbitrary objects (rectangles, points) with properties, not just tiles.
    *   **Automapping:** Rules to automatically place tiles based on neighbors.
*   **Spine / Spriter (General Concept):**
    *   **Skeletal Animation:** animating bones rather than pixels (may be out of scope for pure pixel editor but worth noting).
*   **Blockbench:**
    *   **3D Painting:** Painting directly onto low-poly 3D models.
*   **Grafx2:**
    *   **Color Cycling:** Animating the palette itself (old school effect).
    *   **Spare Page:** A scratchpad area.

## 2. Research Findings from Submodules

### Aseprite (Industry Standard)
*   **Key Strength:** Workflow speed, keyboard shortcuts, robust animation timeline.
*   **File Format:** `.ase` / `.aseprite` (Open spec). Highly recommended to support importing this.

### Tiled (Map Editor Standard)
*   **Key Strength:** Managing large maps, layers of tiles, object layers.
*   **File Format:** `.tmx` (XML based), `.json`. Support for exporting to these is valuable.

### Libresprite
*   (Fork of old Aseprite) Similar feature set to Aseprite.

### Pixelorama (Godot based)
*   Free and open source. Good reference for UI layout in a modern engine context.

### Piskel (Web based)
*   Simple, accessible. Good reference for "minimum viable" animation features.

### Pyxel Edit (Website)
*   **Tile References:** The killer feature is the ability to edit a tile and see it update everywhere in the map instantly.

## 3. Recommended Roadmap

### Phase 1: Foundations (The "Must Haves")
1.  **Layer System:** Implement a basic layer stack (Name, Visibility, Opacity).
2.  **Universal Brush System:** Abstract the "tool" concept to allow for different brush shapes and custom patterns.
3.  **File Format Support:**
    *   Implement `.ase` / `.aseprite` Import (Read-only initially).
    *   Implement `.tmx` / `.json` (Tiled) Export.

### Phase 2: Animation & Workflow
1.  **Animation Timeline:** Basic frame management and playback.
2.  **Onion Skinning:** Visualizing previous/next frames with reduced opacity.
3.  **Symmetry Tools:** Mirror X/Y drawing.
4.  **Selection Tools:** Magic Wand (Color selection), Polygon selection.

### Phase 3: Advanced Tiling (The "Game Changer")
1.  **Tile Instancing:** Like Pyxel Edit. This is hugely beneficial for game art.
2.  **Auto-tiling Rules:** Basic blob-tiles support.

### Phase 4: Modern Polish
1.  **Pixel Perfect Line Algorithm.**
2.  **Gradient Tools.**
3.  **Palette Management:** Load/Save `.pal` or `.gpl` files.
