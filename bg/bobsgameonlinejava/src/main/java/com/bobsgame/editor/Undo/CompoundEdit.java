package com.bobsgame.editor.Undo;

import java.util.ArrayList;
import java.util.List;

public class CompoundEdit extends AbstractUndoableEdit {
    protected List<UndoableEdit> edits;
    protected boolean inProgress;

    public CompoundEdit() {
        super();
        inProgress = true;
        edits = new ArrayList<>();
    }

    public List<UndoableEdit> getEdits() {
	return edits;
    }

    public void end() {
        inProgress = false;
    }

    @Override
    public void undo() {
        super.undo();
        int i = edits.size();
        while (i-- > 0) {
            UndoableEdit e = edits.get(i);
            e.undo();
        }
    }

    @Override
    public void redo() {
        super.redo();
        for (UndoableEdit e : edits) {
            e.redo();
        }
    }

    @Override
    public void die() {
        int i = edits.size();
        while (i-- > 0) {
            UndoableEdit e = edits.get(i);
            e.die();
        }
        super.die();
    }

    @Override
    public boolean addEdit(UndoableEdit anEdit) {
        if (!inProgress) {
            return false;
        }
        UndoableEdit last = lastEdit();

        if (last == null) {
            edits.add(anEdit);
        } else if (!last.addEdit(anEdit)) {
            if (anEdit.replaceEdit(last)) {
                edits.remove(edits.size() - 1);
            }
            edits.add(anEdit);
        }
        return true;
    }

    protected UndoableEdit lastEdit() {
        int count = edits.size();
        if (count > 0) {
            return edits.get(count - 1);
        }
        return null;
    }

    @Override
    public boolean isSignificant() {
        for (UndoableEdit e : edits) {
            if (e.isSignificant()) {
                return true;
            }
        }
        return false;
    }

    @Override
    public String getPresentationName() {
        UndoableEdit last = lastEdit();
        if (last != null) {
            return last.getPresentationName();
        }
        return super.getPresentationName();
    }
}
