package com.bobsgame.puzzle;

import java.io.Serializable;

public class BlockOffset implements Serializable {
    public int x = 0;
    public int y = 0;

    public BlockOffset() {
    }

    public BlockOffset(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        BlockOffset that = (BlockOffset) obj;
        return x == that.x && y == that.y;
    }
}
