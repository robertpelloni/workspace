package com.bobsgame.editor.Undo;

import com.bobsgame.editor.TileCanvas.TileCanvas;

public class TileMoveEdit extends AbstractUndoableEdit {
    private TileCanvas tileCanvas;
    private int tile1;
    private int tile2;

    public TileMoveEdit(TileCanvas tileCanvas, int tile1, int tile2) {
        this.tileCanvas = tileCanvas;
        this.tile1 = tile1;
        this.tile2 = tile2;
    }

    @Override
    public void undo() {
        super.undo();
        tileCanvas.moveTile(tile1, tile2, false);
    }

    @Override
    public void redo() {
        super.redo();
        tileCanvas.moveTile(tile1, tile2, false);
    }

    @Override
    public String getPresentationName() {
        return "Move Tile";
    }
}
