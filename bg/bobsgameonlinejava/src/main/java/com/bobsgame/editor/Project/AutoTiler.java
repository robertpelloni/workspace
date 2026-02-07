package com.bobsgame.editor.Project;

import com.bobsgame.editor.Project.Map.Map;

public class AutoTiler {

    // 4-bit Edge Masking (Walls/Pipes)
    // 1 = North
    // 2 = East
    // 4 = South
    // 8 = West

    public static int getAutoTileIndex(Map map, int layer, int x, int y, int baseIndex) {
        if (map == null) return baseIndex;

        // Define "Same Set" as being within the 16-tile block
        int minIndex = baseIndex;
        int maxIndex = baseIndex + 15;

        int mask = 0;

        // North
        if (isSameSet(map, layer, x, y - 1, minIndex, maxIndex)) {
            mask |= 1;
        }

        // East
        if (isSameSet(map, layer, x + 1, y, minIndex, maxIndex)) {
            mask |= 2;
        }

        // South
        if (isSameSet(map, layer, x, y + 1, minIndex, maxIndex)) {
            mask |= 4;
        }

        // West
        if (isSameSet(map, layer, x - 1, y, minIndex, maxIndex)) {
            mask |= 8;
        }

        return baseIndex + mask;
    }

    private static boolean isSameSet(Map map, int layer, int x, int y, int min, int max) {
        if (x < 0 || x >= map.wT() || y < 0 || y >= map.hT()) return false; // Boundary check
        int tile = map.getTileIndex(layer, x, y);
        return tile >= min && tile <= max;
    }
}
