package com.bobsgame.editor.Project.Sprite;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.zip.Inflater;

import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Sprite.AsepriteParser.Frame;
import com.bobsgame.editor.Project.Sprite.AsepriteParser.Frame.Chunk;
import com.bobsgame.editor.Project.Sprite.AsepriteParser.Frame.Chunk.CelChunk;
import com.bobsgame.editor.Project.Sprite.AsepriteParser.Frame.Chunk.LayerChunk;
import com.bobsgame.editor.Project.Sprite.AsepriteParser.Frame.Chunk.PaletteChunk;
import com.bobsgame.editor.Project.Sprite.AsepriteParser.Frame.Chunk.PaletteChunk.PaletteEntry;
import com.bobsgame.shared.Utils;

public class AsepriteImporter {

    public static Sprite importSprite(File file) throws IOException {
        byte[] bytes = Utils.loadByteFile(file.getAbsolutePath());
        if (bytes == null) throw new IOException("Could not read file: " + file.getAbsolutePath());

        AsepriteParser parser = new AsepriteParser(bytes);
        AsepriteParser.Header header = parser.header();

        if (header.colorDepth() != 8) {
            throw new IOException("Only Indexed (8 bpp) Aseprite files are supported. This file is " + header.colorDepth() + " bpp.");
        }

        int width = header.width();
        int height = header.height();
        int frameCount = header.frames();
        int transparentIndex = header.transparentColorPaletteEntryIndex();

        // 1. Create Sprite
        String name = file.getName();
        if (name.contains(".")) name = name.substring(0, name.lastIndexOf('.'));
        Sprite sprite = new Sprite(name, frameCount, width, height);

        // Clear default layer
        sprite.getLayers().clear();

        // 2. Parse Frames
        List<Frame> frames = parser.parseFrames();

        // 3. Find Layers (usually in first frame)
        List<LayerChunk> aseLayers = new ArrayList<>();
        // Also find Palette
        SpritePalette spritePalette = null;

        for (Frame frame : frames) {
            for (Chunk chunk : frame.chunks()) {
                if (chunk.isLayer()) {
                    aseLayers.add(chunk.layer());
                } else if (chunk.isPalette() && spritePalette == null) {
                    // Create Palette
                    PaletteChunk pc = chunk.palette();
                    spritePalette = new SpritePalette(name + "_Pal");
                    Project.addSpritePalette(spritePalette); // Add to project

                    int pIndex = (int) pc.firstColorIndexToChange();
                    for (PaletteEntry entry : pc.entries()) {
                        if (pIndex < 256) {
                            spritePalette.setColorDataFromRGB(pIndex, entry.red(), entry.green(), entry.blue());
                            // Handle alpha? Aseprite palette has alpha.
                            // SpritePalette seems to support RGB.
                            // If alpha < 255, we might need to handle transparency?
                            // SpritePalette usually assumes index 0 is transparent.
                        }
                        pIndex++;
                    }
                }
            }
            // If we found layers in first frame, break?
            // Aseprite spec says layers are in first frame.
            // But palette might be later? Usually first.
            if (!aseLayers.isEmpty() && spritePalette != null) break;
        }

        if (spritePalette == null) {
            // Fallback: use current palette or create default?
            System.err.println("Warning: No palette found in Aseprite file.");
        } else {
            // Set selected palette?
            Project.setSelectedSpritePaletteIndex(Project.getNumSpritePalettes() - 1);
        }

        // 4. Create Sprite Layers
        // aseLayers contains all layers in order (index 0 to N).
        // We filter for Image layers.
        List<Integer> layerMapping = new ArrayList<>(); // Maps Aseprite Layer Index to Sprite Layer Index (or -1 if ignored)

        for (int i = 0; i < aseLayers.size(); i++) {
            LayerChunk lc = aseLayers.get(i);
            if (lc.imageLayer()) {
                Sprite.Layer sl = sprite.new Layer(lc.name(), frameCount, width, height);
                sl.visible = lc.visible();
                sl.opacity = lc.opacity() / 255.0f;
                sprite.getLayers().add(sl);
                layerMapping.add(sprite.getLayers().size() - 1);
            } else {
                layerMapping.add(-1); // Group layer or otherwise ignored
            }
        }

        if (sprite.getLayers().isEmpty()) {
            sprite.addLayer(); // Ensure at least one
        }

        // 5. Read Cels
        for (int f = 0; f < frames.size(); f++) {
            Frame frame = frames.get(f);

            // Set duration? Sprite doesn't support per-frame duration easily (it has animations).
            // Ignored for now.

            for (Chunk chunk : frame.chunks()) {
                if (chunk.isCel()) {
                    CelChunk cel = chunk.cel();
                    int layerIndex = cel.layerIndex();

                    if (layerIndex < layerMapping.size()) {
                        int spriteLayerIdx = layerMapping.get(layerIndex);
                        if (spriteLayerIdx != -1) {
                            Sprite.Layer sl = sprite.getLayers().get(spriteLayerIdx);

                            // Get Pixels
                            byte[] pixels = null;
                            int w = cel.width();
                            int h = cel.height();

                            if (cel.celType() == 0) { // Raw
                                pixels = cel.getData();
                            } else if (cel.celType() == 2) { // Compressed
                                byte[] compressed = cel.getData();
                                if (compressed != null) {
                                    try {
                                        Inflater inflater = new Inflater();
                                        inflater.setInput(compressed);
                                        pixels = new byte[w * h]; // 8 bpp = 1 byte per pixel
                                        inflater.inflate(pixels);
                                        inflater.end();
                                    } catch (Exception e) {
                                        e.printStackTrace();
                                    }
                                }
                            }

                            // Paint pixels to layer
                            if (pixels != null) {
                                int cx = cel.x();
                                int cy = cel.y();

                                for (int y = 0; y < h; y++) {
                                    for (int x = 0; x < w; x++) {
                                        int px = cx + x;
                                        int py = cy + y;
                                        if (px >= 0 && px < width && py >= 0 && py < height) {
                                            int colorIndex = Byte.toUnsignedInt(pixels[y * w + x]);

                                            // Handle transparency
                                            if (colorIndex == transparentIndex) {
                                                sl.pixels[f][px][py] = 0;
                                            } else {
                                                // If transparentIndex != 0, we might need to map.
                                                // If our palette has transparent at 0, and Aseprite has it at 0, fine.
                                                // If Aseprite has transparent at index 5, then pixel 5 is transparent.
                                                // We set it to 0.
                                                // But what if pixel is 0 (and 0 is valid color in Aseprite)?
                                                // Then we map 0 to... ?
                                                // SpritePalette usually reserves 0 for transparent.
                                                // So we assume target 0 is transparent.
                                                // If colorIndex == transparentIndex -> 0.
                                                // Else -> colorIndex.
                                                // Ideally we should swap colors in palette too?
                                                // For now, assuming index 0 is transparent in Aseprite is standard.
                                                sl.pixels[f][px][py] = colorIndex;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        sprite.activeLayerIndex = sprite.getLayers().size() - 1;

        return sprite;
    }
}
