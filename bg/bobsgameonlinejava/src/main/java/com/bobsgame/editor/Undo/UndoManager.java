package com.bobsgame.editor.Undo;

import java.util.Stack;

public class UndoManager extends AbstractUndoableEdit {
    protected Stack<UndoableEdit> edits = new Stack<>();
    protected UndoableEdit nextEdit = null;
    protected int limit = 100;

    // For Listener support
    private java.util.List<javax.swing.event.ChangeListener> listeners = new java.util.ArrayList<>();

    public UndoManager() {
        super();
    }

    public void addChangeListener(javax.swing.event.ChangeListener l) {
	listeners.add(l);
    }

    public void removeChangeListener(javax.swing.event.ChangeListener l) {
	listeners.remove(l);
    }

    protected void fireStateChanged() {
	javax.swing.event.ChangeEvent e = new javax.swing.event.ChangeEvent(this);
	for(javax.swing.event.ChangeListener l : listeners) {
		l.stateChanged(e);
	}
    }

    public java.util.List<UndoableEdit> getEdits() {
	return java.util.Collections.unmodifiableList(edits);
    }

    public int getNextEditIndex() {
	if (nextEdit == null) return edits.size();
	return edits.indexOf(nextEdit);
    }

    public void setLimit(int l) {
        limit = l;
        trimEdits();
    }

    public int getLimit() {
        return limit;
    }

    protected void trimEdits() {
        while (edits.size() > limit) {
            UndoableEdit edit = edits.remove(0);
            edit.die();
        }
    }

    public synchronized void discardAllEdits() {
        for (UndoableEdit e : edits) {
            e.die();
        }
        edits.clear();
        nextEdit = null;
        fireStateChanged();
    }

    protected void trimForAdd() {
        if (nextEdit != null) {
            // We are adding a new edit, so any redoable edits (from nextEdit onwards) must be discarded
            int index = edits.indexOf(nextEdit);
            if (index != -1) {
                while (edits.size() > index) {
                    UndoableEdit e = edits.pop();
                    e.die();
                }
            }
            nextEdit = null;
        }
        trimEdits();
    }

    @Override
    public synchronized boolean addEdit(UndoableEdit anEdit) {
        trimForAdd();
        edits.push(anEdit);
        trimEdits();
        fireStateChanged();
        return true;
    }

    @Override
    public synchronized boolean canUndo() {
        if (nextEdit != null) {
            // If nextEdit is set, we can undo if there are edits before it
            return edits.indexOf(nextEdit) > 0;
        }
        // If nextEdit is null, we are at the top of the stack, so we can undo if stack is not empty
        return !edits.isEmpty();
    }

    @Override
    public synchronized boolean canRedo() {
        if (nextEdit != null) {
            return true;
        }
        return false;
    }

    @Override
    public synchronized void undo() {
        if (!canUndo()) {
            throw new RuntimeException("Cannot undo");
        }

        UndoableEdit edit;
        if (nextEdit != null) {
            int index = edits.indexOf(nextEdit);
            edit = edits.get(index - 1);
        } else {
            edit = edits.peek();
        }

        edit.undo();
        nextEdit = edit;
        fireStateChanged();
    }

    @Override
    public synchronized void redo() {
        if (!canRedo()) {
            throw new RuntimeException("Cannot redo");
        }

        UndoableEdit edit = nextEdit;
        edit.redo();
        
        int index = edits.indexOf(nextEdit);
        if (index + 1 < edits.size()) {
            nextEdit = edits.get(index + 1);
        } else {
            nextEdit = null;
        }
        fireStateChanged();
    }

    public synchronized void undoTo(UndoableEdit edit) {
	int index = edits.indexOf(edit);
	if (index == -1) return;

	while(canUndo()) {
		// Check if we are already at the state BEFORE this edit?
		// If we want to undo TO 'edit', does that mean 'edit' is the last done thing?
		// Or we undo UNTIL 'edit' is undone?
		// Usually clicking history means "Go back to this state".
		// If list is: [Draw A, Draw B, Draw C]. Current is end.
		// Click "Draw A". We want to undo C, then undo B. State is "After Draw A".

		// Current index (nextEditIndex) is size (3).
		// Draw A is index 0.
		// We want nextEditIndex to be 1 (pointing to Draw B).

		int current = getNextEditIndex();
		if (current <= index + 1) break;
		undo();
	}
    }

    public synchronized void redoTo(UndoableEdit edit) {
	int index = edits.indexOf(edit);
	if (index == -1) return;

	while(canRedo()) {
		int current = getNextEditIndex(); // points to next edit to REDO
		if (current > index) break; // We have redone it
		redo();
	}
    }
    
    public synchronized String getUndoPresentationName() {
        if (canUndo()) {
            UndoableEdit edit;
            if (nextEdit != null) {
                int index = edits.indexOf(nextEdit);
                edit = edits.get(index - 1);
            } else {
                edit = edits.peek();
            }
            return edit.getUndoPresentationName();
        }
        return "Undo";
    }

    public synchronized String getRedoPresentationName() {
        if (canRedo()) {
            return nextEdit.getRedoPresentationName();
        }
        return "Redo";
    }
}
