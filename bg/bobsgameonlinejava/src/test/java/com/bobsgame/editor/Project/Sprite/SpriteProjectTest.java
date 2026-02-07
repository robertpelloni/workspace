package com.bobsgame.editor.Project.Sprite;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.File;
import java.io.IOException;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Sprite.Sprite.Layer;

public class SpriteProjectTest {

    @TempDir
    File tempDir;

    @BeforeEach
    public void setup() {
        // Reset Project statics
        Project.spriteList.clear();
        Project.spriteHashtable.clear();
    }

    @Test
    public void testSaveAndLoadSpriteProject() throws IOException {
        // 1. Create a Sprite with Layers
        Sprite sprite = new Sprite("TestSprite", 1, 16, 16);

        // It starts with 1 layer (Layer 1)
        Layer layer1 = sprite.getActiveLayer();
        layer1.pixels[0][0][0] = 1; // Set a pixel

        // Add a second layer
        sprite.addLayer();
        Layer layer2 = sprite.getActiveLayer();
        layer2.name = "Layer 2";
        layer2.opacity = 0.5f;
        layer2.pixels[0][5][5] = 2; // Set another pixel
        layer2.visible = false;

        // 2. Save Project
        File projectFile = new File(tempDir, "test.sprproj");
        SpriteProject.save(sprite, projectFile);

        // 3. Clear Project state to ensure clean load
        Project.spriteList.clear();
        Project.spriteHashtable.clear();

        // 4. Load Project
        Sprite loadedSprite = SpriteProject.load(projectFile);

        // 5. Verify
        assertEquals("TestSprite", loadedSprite.name());
        assertEquals(2, loadedSprite.getLayers().size());

        // Verify Layer 1
        Layer l1 = loadedSprite.getLayers().get(0);
        assertEquals("Layer 1", l1.name);
        assertEquals(1.0f, l1.opacity);
        assertTrue(l1.visible);
        assertEquals(1, l1.pixels[0][0][0]);
        assertEquals(0, l1.pixels[0][5][5]);

        // Verify Layer 2
        Layer l2 = loadedSprite.getLayers().get(1);
        assertEquals("Layer 2", l2.name);
        assertEquals(0.5f, l2.opacity);
        assertTrue(!l2.visible);
        assertEquals(0, l2.pixels[0][0][0]);
        assertEquals(2, l2.pixels[0][5][5]);

        // Verify Frames/Size
        assertEquals(16, loadedSprite.wP());
        assertEquals(16, loadedSprite.hP());
        assertEquals(1, loadedSprite.frames());
    }
}
