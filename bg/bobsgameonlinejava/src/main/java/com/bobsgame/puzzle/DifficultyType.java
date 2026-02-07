package com.bobsgame.puzzle;

import java.io.Serializable;
import java.util.ArrayList;

public class DifficultyType implements Serializable {
    public String name = "";

    public int initialLineDropSpeedTicks = 1000;
    public int minimumLineDropSpeedTicks = 64;
    public int maxStackRise = 400;
    public int minStackRise = 30;

    public int extraStage1Level = 10;
    public int extraStage2Level = 15;
    public int extraStage3Level = 20;
    public int extraStage4Level = 25;
    public int creditsLevel = 30;

    public int playingFieldGarbageSpawnRuleAmount = 5;
    public int maximumBlockTypeColors = 8;

    public boolean randomlyFillGrid = true;
    public int randomlyFillGridStartY = 10;
    public int randomlyFillGridAmount = 30;

    public ArrayList<String> pieceTypesToDisallow_UUID = new ArrayList<>();
    public ArrayList<String> blockTypesToDisallow_UUID = new ArrayList<>();
}
