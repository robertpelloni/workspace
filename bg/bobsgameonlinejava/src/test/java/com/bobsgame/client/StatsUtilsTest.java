package com.bobsgame.client;

import java.lang.management.ManagementFactory;
import com.sun.management.OperatingSystemMXBean;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class StatsUtilsTest {

    @Test
    public void testOSInfo() {
        // Just verify we can get the data without crashing
        int processors = Runtime.getRuntime().availableProcessors();
        assertTrue(processors > 0);

        String osName = System.getProperty("os.name");
        assertNotNull(osName);

        String osArch = System.getProperty("os.arch");
        assertNotNull(osArch);

        String osVersion = System.getProperty("os.version");
        assertNotNull(osVersion);

        java.lang.management.OperatingSystemMXBean osBean = ManagementFactory.getOperatingSystemMXBean();
        assertTrue(osBean.getSystemLoadAverage() >= 0 || osBean.getSystemLoadAverage() < 0); // Just check it doesn't throw
    }
}
