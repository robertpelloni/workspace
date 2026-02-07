package com.bobsgame.editor.Undo;

public abstract class AbstractUndoableEdit implements UndoableEdit {
    protected boolean hasBeenDone;
    protected boolean alive;

    public AbstractUndoableEdit() {
        hasBeenDone = true;
        alive = true;
    }

    public void die() {
        alive = false;
    }

    public void undo() {
        if (!canUndo()) {
            throw new RuntimeException("Cannot undo");
        }
        hasBeenDone = false;
    }

    public boolean canUndo() {
        return alive && hasBeenDone;
    }

    public void redo() {
        if (!canRedo()) {
            throw new RuntimeException("Cannot redo");
        }
        hasBeenDone = true;
    }

    public boolean canRedo() {
        return alive && !hasBeenDone;
    }

    public boolean addEdit(UndoableEdit anEdit) {
        return false;
    }

    public boolean replaceEdit(UndoableEdit anEdit) {
        return false;
    }

    public boolean isSignificant() {
        return true;
    }

    public String getPresentationName() {
        return "";
    }

    public String getUndoPresentationName() {
        String name = getPresentationName();
        if (!"".equals(name)) {
            name = " " + name;
        }
        return "Undo" + name;
    }

    public String getRedoPresentationName() {
        String name = getPresentationName();
        if (!"".equals(name)) {
            name = " " + name;
        }
        return "Redo" + name;
    }
}
