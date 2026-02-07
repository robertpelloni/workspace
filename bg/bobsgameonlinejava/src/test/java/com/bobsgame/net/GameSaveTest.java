package com.bobsgame.net;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class GameSaveTest {

    @Test
    void testGetCountryCodeFromCountryString() {
        assertEquals("US", GameSave.getCountryCodeFromCountryString("United States"));
        assertEquals("CA", GameSave.getCountryCodeFromCountryString("Canada"));
        assertEquals("GB", GameSave.getCountryCodeFromCountryString("United Kingdom"));
        assertEquals("JP", GameSave.getCountryCodeFromCountryString("Japan"));
        // Test a default case
        assertEquals("US", GameSave.getCountryCodeFromCountryString("Non Existent Country"));
    }

    @Test
    void testGetCountryStringFromCode() {
        assertEquals("United States", GameSave.getCountryStringFromCode("US"));
        assertEquals("Canada", GameSave.getCountryStringFromCode("CA"));
        assertEquals("United Kingdom", GameSave.getCountryStringFromCode("GB"));
        assertEquals("Japan", GameSave.getCountryStringFromCode("JP"));
        // Test a default case
        assertEquals("United States", GameSave.getCountryStringFromCode("XX"));
    }

    @Test
    void testEncodeDecode() {
        GameSave original = new GameSave();
        original.userID = 12345;
        original.userName = "TestUser";
        original.emailAddress = "test@example.com";
        original.money = 100.50f;
        original.itemsHeld = "1:1:0,2:5:0,";
        original.lastLoginTime = System.currentTimeMillis();

        String encoded = original.encodeGameSave();
        assertNotNull(encoded);
        assertTrue(encoded.length() > 0);

        GameSave decoded = new GameSave();
        decoded.decodeGameSave(encoded);

        assertEquals(original.userID, decoded.userID);
        assertEquals(original.userName, decoded.userName);
        assertEquals(original.emailAddress, decoded.emailAddress);
        assertEquals(original.money, decoded.money, 0.001f);
        assertEquals(original.itemsHeld, decoded.itemsHeld);
        assertEquals(original.lastLoginTime, decoded.lastLoginTime);
    }
}
