package com.bobsgame.editor.Undo;

import com.bobsgame.editor.Project.Map.Area;
import com.bobsgame.editor.Project.Map.Door;
import com.bobsgame.editor.Project.Map.Entity;
import com.bobsgame.editor.Project.Map.Light;
import com.bobsgame.editor.Project.Map.Map;

public class MapObjectRemoveEdit extends AbstractUndoableEdit {
    private Map map;
    private Object object;
    
    public MapObjectRemoveEdit(Map map, Object object) {
        this.map = map;
        this.object = object;
    }
    
    @Override
    public void undo() {
        super.undo();
        if (object instanceof Entity) map.addEntity((Entity)object);
        else if (object instanceof Door) map.addDoor((Door)object);
        else if (object instanceof Light) map.addLight((Light)object);
        else if (object instanceof Area) map.addArea((Area)object);
    }
    
    @Override
    public void redo() {
        super.redo();
        if (object instanceof Entity) map.getSelectedState().removeEntity((Entity)object);
        else if (object instanceof Door) map.removeDoor((Door)object);
        else if (object instanceof Light) map.getSelectedState().removeLight((Light)object);
        else if (object instanceof Area) map.getSelectedState().removeArea((Area)object);
    }
}
