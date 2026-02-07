package com.bobsgame.puzzle;

import java.io.Serializable;
import java.util.ArrayList;

public class Rotation implements Serializable {
    public ArrayList<BlockOffset> blockOffsets = new ArrayList<>();

    public Rotation() {
    }

    public void add(BlockOffset b) {
        blockOffsets.add(b);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Rotation rotation = (Rotation) obj;
        return blockOffsets.equals(rotation.blockOffsets);
    }
}
