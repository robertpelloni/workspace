package com.bobsgame.editor.Undo;

public interface UndoableEdit {
    void undo();
    void redo();
    boolean canUndo();
    boolean canRedo();
    void die();
    boolean addEdit(UndoableEdit anEdit);
    boolean replaceEdit(UndoableEdit anEdit);
    boolean isSignificant();
    String getPresentationName();
    String getUndoPresentationName();
    String getRedoPresentationName();
}
