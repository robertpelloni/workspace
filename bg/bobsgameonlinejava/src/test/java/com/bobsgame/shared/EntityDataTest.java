package com.bobsgame.shared;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class EntityDataTest {

    @Test
    void testVoicePitch() {
        EntityData data = new EntityData(1, "TestEntity");
        assertEquals(0.0f, data.voicePitch(), "Default voice pitch should be 0.0");

        data.setVoicePitch(1.5f);
        assertEquals(1.5f, data.voicePitch(), "Voice pitch should be updatable");

        // Test serialization
        String serialized = data.toString();
        EntityData newData = new EntityData();
        newData.initFromString(serialized);
        assertEquals(1.5f, newData.voicePitch(), "Voice pitch should be preserved after serialization");
    }
}
