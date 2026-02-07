package com.bobsgame.editor.SpriteEditor.Tools;

import java.awt.Graphics;
import com.bobsgame.editor.SpriteEditor.SECanvas;

public class FillBrush implements Brush {

    @Override
    public String getName() {
        return "Fill";
    }

    @Override
    public void onMousePress(SECanvas canvas, int x, int y, int color, int modifiers) {
        int oldColor = canvas.getPixel(x, y);
        if (oldColor != color) {
            canvas.fill(x, y, color, oldColor, canvas.getCurrentEdit());
        }
    }

    @Override
    public void onMouseDrag(SECanvas canvas, int x, int y, int color, int modifiers) {
        // Fill usually doesn't work on drag
    }

    @Override
    public void onMouseRelease(SECanvas canvas, int x, int y, int color, int modifiers) {
    }

    @Override
    public void onPaint(Graphics g, SECanvas canvas) {
    }
}
