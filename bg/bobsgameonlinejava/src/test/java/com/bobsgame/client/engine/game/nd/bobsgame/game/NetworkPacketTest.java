package com.bobsgame.client.engine.game.nd.bobsgame.game;

import org.junit.jupiter.api.Test;
import com.google.gson.Gson;
import static org.junit.jupiter.api.Assertions.*;

public class NetworkPacketTest {

    @Test
    public void testSerialization() {
        GameLogic.NetworkPacket packet = new GameLogic.NetworkPacket();
        GameLogic.FrameState frame = new GameLogic.FrameState();
        frame.ticksPassed = 12345;
        frame.controlsState.BUTTON_SPACE_HELD = true;
        frame.receivedGarbageAmount = 5;
        packet.frameStates.add(frame);

        Gson gson = new Gson();
        String json = gson.toJson(packet);

        // System.out.println("JSON: " + json);

        GameLogic.NetworkPacket deserialized = gson.fromJson(json, GameLogic.NetworkPacket.class);

        assertEquals(1, deserialized.frameStates.size());
        GameLogic.FrameState df = deserialized.frameStates.get(0);
        assertEquals(12345, df.ticksPassed);
        assertTrue(df.controlsState.BUTTON_SPACE_HELD);
        assertEquals(5, df.receivedGarbageAmount);
    }
}
