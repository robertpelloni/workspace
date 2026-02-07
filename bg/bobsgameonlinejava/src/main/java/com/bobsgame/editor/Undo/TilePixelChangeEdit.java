package com.bobsgame.editor.Undo;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.TileCanvas.TileCanvas;

public class TilePixelChangeEdit extends AbstractUndoableEdit {
    private TileCanvas tileCanvas;
    private int tileIndex;
    private int[][] oldPixels;
    private int[][] newPixels;

    public TilePixelChangeEdit(TileCanvas tileCanvas, int tileIndex, int[][] oldPixels, int[][] newPixels) {
        this.tileCanvas = tileCanvas;
        this.tileIndex = tileIndex;
        this.oldPixels = oldPixels;
        this.newPixels = newPixels;
    }

    @Override
    public void undo() {
        super.undo();
        restorePixels(oldPixels);
    }

    @Override
    public void redo() {
        super.redo();
        restorePixels(newPixels);
    }

    private void restorePixels(int[][] pixels) {
        for(int y=0; y<8; y++) {
            for(int x=0; x<8; x++) {
                Project.tileset.setPixel(tileIndex, x, y, pixels[x][y]);
            }
        }
        tileCanvas.paint(tileIndex);
        EditorMain.mapCanvas.repaint();
    }

    @Override
    public String getPresentationName() {
        return "Change Tile Pixels";
    }
}
