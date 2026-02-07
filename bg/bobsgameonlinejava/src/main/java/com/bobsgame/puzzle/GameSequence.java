package com.bobsgame.puzzle;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.UUID;

public class GameSequence implements Serializable {
    public String uuid = "";
    public String currentDifficultyName = "Normal";
    public boolean randomizeSequence = false;
    public ArrayList<GameType> gameTypes = new ArrayList<>();

    public GameSequence() {
        this.uuid = UUID.randomUUID().toString();
    }
}
