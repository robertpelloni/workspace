# Features Research

This document compiles research on features from various sprite and tile editing tools to inform the development of the internal tools.

## Feature Analysis

### 1. Layers & Project Management
*   **Standard Layers:** Visibility, Opacity, Locking, Blending Modes. (Aseprite, Photoshop, GIMP)
*   **Reference Layers:** Layers that are visible during editing but excluded from final export. (Aseprite)
*   **Tilemap Layers:** Layers dedicated to tile indices rather than pixels. (Tiled, Pyxel Edit)
*   **Parallax Layers:** Defining scroll speeds for layers for preview. (Tiled)

### 2. Drawing Tools
*   **Universal Brush:** Common interface for Pencil, Eraser, Fill, Shape, Custom Brushes.
*   **Pixel-Perfect:** Algorithm to remove "doubled" pixels on corners for cleaner lines. (Aseprite)
*   **Symmetry:** Real-time mirroring (X, Y, Radial). (Pyxel Edit, Aseprite)
*   **Tile Instancing:** Drawing on a tile on the canvas updates the tileset and all other instances. (Pyxel Edit)
*   **Shading Mode:** Locking palette to gradients, so painting "light" or "dark" shifts the pixel color index up/down the ramp. (Pro Motion NG, Aseprite)
*   **Contour Fill:** Filling connected pixels of the same color, but also filling diagonal connections or stopping at boundaries.

### 3. Selection & Transformation
*   **Magic Wand:** Select connected pixels of color.
*   **Color Select:** Select all pixels of color X in layer/frame/cel.
*   **Rotated Sprite:** Support for rotating sprites (lossy or non-lossy via rotation layers).
*   **Grid Snapping:** Snapping selections or brushes to grid.

### 4. Animation
*   **Onion Skinning:** Viewing previous/next frames with tint/alpha.
*   **Tags/Loops:** Defining animation segments (Idle, Walk, Run) with tags. (Aseprite)
*   **Cel Linking:** Reusing the same image data across multiple frames.

### 5. Color & Palette
*   **Palette Management:** Loading/Saving .pal, .gpl. Rearranging colors.
*   **Color Replacement:** Global swap of Color A to Color B.
*   **Gradients:** Generating ramps between two colors.

### 6. Tile Mapping
*   **Auto-Tiling:** Blob/Wang sets to automatically place corners/edges. (Tiled, Godot)
*   **Stamp Brush:** Selecting an area of tiles and painting with it.
*   **Collision Editor:** Defining collision polygons per tile.

### 7. Generative / AI
*   **Sprite Generation:** Text-to-Image for sprites.
*   **Upscaling:** Pixel-art specific upscaling (HQ2x, xBRZ, or AI-based).
*   **Variation Generation:** Creating color variants or slight shape variants.

## Priority Implementation List (Derived for Internal Tools)

1.  **Layers (Ref & Normal)** - Essential for complex art. (Done)
2.  **Symmetry** - High value for character/item art. (Done)
3.  **Tile Instancing** - Crucial for tileset workflow. (Done)
4.  **Auto-Tiling** - Speed up map creation. (Done)
5.  **Aseprite Import** - Bridge to external tools. (Done)
6.  **Magic Wand** - Basic selection necessity. (Done)
7.  **Onion Skinning** - Essential for animation. (Done)

## Remaining High Value Candidates

*   **Undo System Improvements**: The current system wraps and is basic. A robust `Command` pattern undo system is "universally useful".
*   **Pixel Perfect Drawing**: A very common request for pixel art tools to avoid "jaggies".
*   **Shading/Palette Mode**: Very useful for limited palette pixel art.
*   **Animation Tags**: Defining "Walk", "Run", etc. metadata.
*   **Generative/AI integration**: As requested in the prompt.
