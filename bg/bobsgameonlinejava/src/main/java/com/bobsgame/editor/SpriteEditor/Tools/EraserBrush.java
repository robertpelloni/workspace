package com.bobsgame.editor.SpriteEditor.Tools;

import java.awt.Graphics;
import com.bobsgame.editor.SpriteEditor.SECanvas;

public class EraserBrush implements Brush {

    @Override
    public String getName() {
        return "Eraser";
    }

    @Override
    public void onMousePress(SECanvas canvas, int x, int y, int color, int modifiers) {
        // Erase sets color to 0 (transparent)
        canvas.setPixel(x, y, 0, canvas.getCurrentEdit());
    }

    @Override
    public void onMouseDrag(SECanvas canvas, int x, int y, int color, int modifiers) {
        canvas.setPixel(x, y, 0, canvas.getCurrentEdit());
    }

    @Override
    public void onMouseRelease(SECanvas canvas, int x, int y, int color, int modifiers) {
    }

    @Override
    public void onPaint(Graphics g, SECanvas canvas) {
    }
}
