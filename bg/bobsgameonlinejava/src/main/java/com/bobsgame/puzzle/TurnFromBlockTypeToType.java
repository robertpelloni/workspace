package com.bobsgame.puzzle;

import java.io.Serializable;

// Placeholder for GameType until it is implemented
class GameType {
    public BlockType getBlockTypeByUUID(String uuid) {
        return null; // TODO: Implement
    }
}

public class TurnFromBlockTypeToType implements Serializable {
    public String fromType_DEPRECATED = "";
    public String toType_DEPRECATED = "";

    public String fromType_UUID = "";
    public String toType_UUID = "";

    public TurnFromBlockTypeToType() {
    }

    public TurnFromBlockTypeToType(String fromUUID, String toUUID) {
        this.fromType_UUID = fromUUID;
        this.toType_UUID = toUUID;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        TurnFromBlockTypeToType that = (TurnFromBlockTypeToType) obj;
        return fromType_UUID.equals(that.fromType_UUID) && toType_UUID.equals(that.toType_UUID);
    }

    // TODO: Implement proper getName once GameType is available
    // public String getName(GameType g) { return g.getBlockTypeByUUID(fromType_UUID).name + "->" + g.getBlockTypeByUUID(toType_UUID).name; }
}
