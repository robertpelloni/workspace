package com.bobsgame.editor.Undo;

import com.bobsgame.editor.MultipleTileEditor.MTECanvas;

public class PixelChangeEdit extends AbstractUndoableEdit {
    private MTECanvas canvas;
    private int x;
    private int y;
    private int oldColor;
    private int newColor;

    public PixelChangeEdit(MTECanvas canvas, int x, int y, int oldColor, int newColor) {
        this.canvas = canvas;
        this.x = x;
        this.y = y;
        this.oldColor = oldColor;
        this.newColor = newColor;
    }

    @Override
    public void undo() {
        super.undo();
        canvas.setPixelRaw(x, y, oldColor);
        canvas.repaintBufferImage();
        canvas.repaint();
    }

    @Override
    public void redo() {
        super.redo();
        canvas.setPixelRaw(x, y, newColor);
        canvas.repaintBufferImage();
        canvas.repaint();
    }
    
    @Override
    public String getPresentationName() {
        return "Pixel Change";
    }
}
