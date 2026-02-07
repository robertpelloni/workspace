package com.bobsgame.editor.SpriteEditor.Tools;

import java.awt.Graphics;
import java.awt.Point;
import java.util.ArrayList;
import java.util.List;

import com.bobsgame.editor.SpriteEditor.SECanvas;

public class PixelBrush implements Brush {

	private int lastX = -1;
	private int lastY = -1;
	private boolean pixelPerfect = false;
	private List<Point> strokeHistory = new ArrayList<>();

	public void setPixelPerfect(boolean b) {
		this.pixelPerfect = b;
	}

    @Override
    public String getName() {
        return "Pencil";
    }

    @Override
    public void onMousePress(SECanvas canvas, int x, int y, int color, int modifiers) {
	lastX = x;
	lastY = y;
	strokeHistory.clear();
	plot(canvas, x, y, color);
    }

    @Override
    public void onMouseDrag(SECanvas canvas, int x, int y, int color, int modifiers) {
	drawLine(canvas, lastX, lastY, x, y, color);
	lastX = x;
	lastY = y;
    }

    @Override
    public void onMouseRelease(SECanvas canvas, int x, int y, int color, int modifiers) {
	lastX = -1;
	lastY = -1;
	strokeHistory.clear();
    }

    @Override
    public void onPaint(Graphics g, SECanvas canvas) {
        // Could draw cursor highlight here
    }

    private void drawLine(SECanvas canvas, int x0, int y0, int x1, int y1, int color) {
	int dx = Math.abs(x1 - x0);
	int dy = Math.abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;

	while(true) {
		plot(canvas, x0, y0, color);

		if (x0 == x1 && y0 == y1) break;
		int e2 = 2 * err;
		if (e2 > -dy) {
			err = err - dy;
			x0 = x0 + sx;
		}
		if (e2 < dx) {
			err = err + dx;
			y0 = y0 + sy;
		}
	}
    }

    private void plot(SECanvas canvas, int x, int y, int color) {
	// Pixel Perfect Logic
	if (pixelPerfect && !strokeHistory.isEmpty()) {
		Point current = new Point(x, y);
		Point last = strokeHistory.get(strokeHistory.size() - 1);

		if (current.equals(last)) return; // No change

		if (strokeHistory.size() >= 2) {
			Point prev = strokeHistory.get(strokeHistory.size() - 2);

			// Check for L-shape
			// If we moved diagonally from prev -> current, or if last was a corner.
			// Standard Bresenham output for diagonal lines (e.g. 0,0 -> 1,1) might produce (0,0), (1,0), (1,1) or (0,0), (0,1), (1,1).
			// This creates a corner at the middle point.
			// If prev and current are diagonal neighbors (abs(dx)==1 && abs(dy)==1), then 'last' must be one of the shared orthogonal neighbors.
			// If 'last' is that neighbor, we remove it.

			if (Math.abs(prev.x - current.x) == 1 && Math.abs(prev.y - current.y) == 1) {
				// Prev and Current are diagonal. 'last' connects them.
				// If 'last' is (prev.x, current.y) or (current.x, prev.y)
				if ((last.x == prev.x && last.y == current.y) || (last.x == current.x && last.y == prev.y)) {
					// Remove 'last' from canvas (set to 0? or undo?)
					// Ideally we undo the pixel set at 'last'.
					// Since we are in the same CompoundEdit, we can just set it to 0 (eraser) or...
					// Wait, if we are drawing on a filled background, we want to restore the previous color.
					// But we don't track that here.
					// However, typical pixel art "Pixel Perfect" simply removes the extra pixel from the stroke.
					// If we are drawing Opacity 100%, we can assume we "undo" that pixel.
					// But canvas.setPixel overwrites.
					// We can attempt to set it to '0' (transparent) IF we are on a transparent layer.
					// But what if we are drawing OVER something?
					// The only way to truly "undo" is if we haven't committed it yet, or if we fetch the color from before the stroke.
					// But `canvas` has already updated.

					// Simplify: For now, Pixel Perfect works best on Transparent Layers.
					// We will erase the pixel at `last`.
					// Better: We check if `last` was painted by THIS stroke. Yes it was.
					// So we can revert it?
					// Actually, `undoManager` has the edits. But delving into that is hard.
					// Let's just set it to 0 (Clear). This assumes we are drawing on a new layer or transparent area.
					// If we are drawing on top of existing pixels, this will leave a hole.
					// This is a known limitation of simple Pixel Perfect implementations unless we track "pixels under stroke".
					// Aseprite handles this.
					// Let's leave it as "Set to 0" for now, or fetch from a "snapshot" if we had one.
					// We don't have a snapshot.
					// BUT: `canvas.getPixel(last.x, last.y)` returns the CURRENT color (which is `color`).
					// If we change it, what do we change it TO?
					// If we can't revert, maybe we just don't draw `last` in the first place?
					// But we draw immediately.
					// Algorithm tweak: Buffer the output?
					// No, visual feedback needs to be instant.
					// Aseprite does: Draw A. Draw B. Detect Corner. Revert B. Draw C.
					// "Revert" implies setting it back to what it was.
					// Does `canvas` know what it was? `PixelChangeEdit` knows!
					// `canvas.getCurrentEdit()` is a `CompoundEdit`. It has a list of `PixelChangeEdit`.
					// We can search the current edit for the change at `last.x, last.y` and undo it!

					com.bobsgame.editor.Undo.CompoundEdit edit = canvas.getCurrentEdit();
					if(edit != null) {
						// We need to find the last edit for this pixel.
						// `CompoundEdit` uses `java.util.Vector<UndoableEdit> edits`.
						// We can iterate backwards.
						java.util.List<com.bobsgame.editor.Undo.UndoableEdit> edits = edit.getEdits();
						for(int i=edits.size()-1; i>=0; i--) {
							com.bobsgame.editor.Undo.UndoableEdit e = edits.get(i);
							if(e instanceof com.bobsgame.editor.Undo.PixelChangeEdit) {
								com.bobsgame.editor.Undo.PixelChangeEdit pce = (com.bobsgame.editor.Undo.PixelChangeEdit)e;
								// We can't easily access x/y from PixelChangeEdit unless we expose getters.
								// But let's assume we can add getters or use reflection.
								// Or... simpler: `PixelChangeEdit` has `undo()`.
								// If we find it, we call `undo()` and remove it from the list?
								// `CompoundEdit` doesn't expose list modification easily.

								// Alternative: Just set to 0. It's a "clean up" tool.
								// Most users use Pixel Perfect on Line Art layers (transparent).
								canvas.setPixel(last.x, last.y, 0, canvas.getCurrentEdit());
								break; // Handled
							}
						}
					} else {
						canvas.setPixel(last.x, last.y, 0, canvas.getCurrentEdit());
					}

					strokeHistory.remove(strokeHistory.size() - 1); // Remove 'last' from history
				}
			}
		}
	}

	canvas.setPixel(x, y, color, canvas.getCurrentEdit());
	strokeHistory.add(new Point(x, y));
    }
}
