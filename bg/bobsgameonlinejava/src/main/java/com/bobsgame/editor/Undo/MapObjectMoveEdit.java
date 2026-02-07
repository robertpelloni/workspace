package com.bobsgame.editor.Undo;

import com.bobsgame.editor.Project.Map.Area;
import com.bobsgame.editor.Project.Map.Door;
import com.bobsgame.editor.Project.Map.Entity;
import com.bobsgame.editor.Project.Map.Light;

public class MapObjectMoveEdit extends AbstractUndoableEdit {
    private Object target;
    private int oldX, oldY;
    private int newX, newY;
    
    public MapObjectMoveEdit(Object target, int oldX, int oldY, int newX, int newY) {
        this.target = target;
        this.oldX = oldX;
        this.oldY = oldY;
        this.newX = newX;
        this.newY = newY;
    }
    
    @Override
    public void undo() {
        super.undo();
        setPos(oldX, oldY);
    }
    
    @Override
    public void redo() {
        super.redo();
        setPos(newX, newY);
    }
    
    private void setPos(int x, int y) {
        if (target instanceof Entity) {
            ((Entity)target).setXPixels(x);
            ((Entity)target).setYPixels(y);
        } else if (target instanceof Door) {
            ((Door)target).setXPixels(x);
            ((Door)target).setYPixels(y);
        } else if (target instanceof Light) {
            ((Light)target).setXPixels(x);
            ((Light)target).setYPixels(y);
        } else if (target instanceof Area) {
            ((Area)target).setXPixels(x);
            ((Area)target).setYPixels(y);
        }
    }
}
