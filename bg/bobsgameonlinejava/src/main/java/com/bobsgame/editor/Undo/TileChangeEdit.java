package com.bobsgame.editor.Undo;

import com.bobsgame.editor.MapCanvas.MapCanvas;
import com.bobsgame.shared.MapData;

public class TileChangeEdit extends AbstractUndoableEdit {
    private MapCanvas mapCanvas;
    private int layer;
    private int x;
    private int y;
    private int oldTile;
    private int newTile;

    public TileChangeEdit(MapCanvas mapCanvas, int layer, int x, int y, int oldTile, int newTile) {
        this.mapCanvas = mapCanvas;
        this.layer = layer;
        this.x = x;
        this.y = y;
        this.oldTile = oldTile;
        this.newTile = newTile;
    }

    @Override
    public void undo() {
        super.undo();
        mapCanvas.getMap().setTileIndex(layer, x, y, oldTile);
        mapCanvas.paintTileXY(layer, x, y);
    }

    @Override
    public void redo() {
        super.redo();
        mapCanvas.getMap().setTileIndex(layer, x, y, newTile);
        mapCanvas.paintTileXY(layer, x, y);
    }

    @Override
    public String getPresentationName() {
        return "Tile Change";
    }
    
    // Optimization: If we change the same tile multiple times in a row (e.g. dragging over it back and forth),
    // we could potentially merge edits, but CompoundEdit handles the grouping of a stroke.
    // However, inside a CompoundEdit, we might want to avoid storing multiple changes to the same tile.
    // But for now, simple is better.
}
