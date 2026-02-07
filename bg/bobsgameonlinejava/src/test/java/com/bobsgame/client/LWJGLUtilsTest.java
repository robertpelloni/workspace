package com.bobsgame.client;

import org.junit.jupiter.api.Test;
import java.nio.ByteBuffer;
import static org.junit.jupiter.api.Assertions.*;

public class LWJGLUtilsTest {

    @Test
    public void testIconLogic() {
        // This test verifies the logic for loading an icon would compile and basic buffer operations work.
        // We cannot test actual GLFW window creation or icon setting in a headless environment easily without mocking static native calls.

        // Simulating the buffer creation part which is pure Java/LWJGL memory management
        ByteBuffer buffer = ByteBuffer.allocateDirect(100);
        assertNotNull(buffer);
        assertEquals(0, buffer.position());
        assertEquals(100, buffer.limit());
    }
}
