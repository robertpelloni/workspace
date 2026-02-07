package com.bobsgame.puzzle;

import java.io.Serializable;
import java.util.ArrayList;

public class RotationSet implements Serializable {
    public String name = "";
    public ArrayList<Rotation> rotationSet = new ArrayList<>();

    public RotationSet() {
    }

    public RotationSet(String name) {
        this.name = name;
    }

    public void add(Rotation r) {
        rotationSet.add(r);
    }

    public int size() {
        return rotationSet.size();
    }

    public Rotation get(int i) {
        return rotationSet.get(i);
    }

    public void clear() {
        rotationSet.clear();
    }

    public void removeAt(int i) {
        rotationSet.remove(i);
    }
}
