package com.bobsgame.editor.SpriteEditor.Tools;

import java.awt.Graphics;
import com.bobsgame.editor.SpriteEditor.SECanvas;

public interface Brush {
    String getName();
    void onMousePress(SECanvas canvas, int x, int y, int color, int modifiers);
    void onMouseDrag(SECanvas canvas, int x, int y, int color, int modifiers);
    void onMouseRelease(SECanvas canvas, int x, int y, int color, int modifiers);
    void onPaint(Graphics g, SECanvas canvas);
}
