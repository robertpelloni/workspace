package com.bobsgame.client.engine.game.nd.bobsgame.stats;

import com.google.gson.Gson;

public class BobsGameUserStats {
    public long userID = 0;
    public String userName = "";

    public String isGameTypeOrSequence = "";
    public String gameTypeName = "";
    public String gameTypeUUID = "";
    public String gameSequenceName = "";
    public String gameSequenceUUID = "";
    public String difficultyName = "";
    public String objectiveString = "";

    public int totalGamesPlayed = 0;
    public int singlePlayerGamesPlayed = 0;
    public int tournamentGamesPlayed = 0;
    public int localMultiplayerGamesPlayed = 0;

    public int tournamentGamesWon = 0;
    public int tournamentGamesLost = 0;

    public int singlePlayerGamesCompleted = 0;
    public int singlePlayerGamesLost = 0;
    public int singlePlayerHighestLevelReached = 0;

    public long totalTimePlayed = 0;
    public long longestGameLength = 0;
    public long averageGameLength = 0;
    public long fastestClearedLength = 0;

    public double eloScore = 1200.0;

    public long firstTimePlayed = 0;
    public long lastTimePlayed = 0;

    public long planesWalkerPoints = 0;

    public long totalBlocksMade = 0;
    public long totalPiecesMade = 0;
    public long totalBlocksCleared = 0;
    public long totalPiecesPlaced = 0;

    public long totalCombosMade = 0;
    public int biggestCombo = 0;
    public int mostBlocksCleared = 0;

    public String longestTimeStatsUUID = "";
    public String fastestTimeClearedStatsUUID = "";
    public String mostBlocksClearedStatsUUID = "";

    public String toJSON() {
        return new Gson().toJson(this);
    }

    public static BobsGameUserStats fromJSON(String json) {
        return new Gson().fromJson(json, BobsGameUserStats.class);
    }
}
