package com.bobsgame.client.engine.game.nd.bobsgame.game;

import java.util.ArrayList;
import com.google.gson.Gson;
import com.bobsgame.shared.Utils;

public class GameSequence {
    public String uuid = "";
    public String name = "My New Game Sequence";
    @Override public String toString() { return name; }
    public String description = "This is an empty game sequence.";

    public ArrayList<String> importExport_gameUUIDs = new ArrayList<String>();
    public ArrayList<GameType> gameTypes = new ArrayList<GameType>();

    public boolean randomizeSequence = true;
    public String currentDifficultyName = "Beginner";

    public boolean downloaded = false;

    public long creatorUserID = 0;
    public String creatorUserName = "";
    public long dateCreated = 0;
    public long lastModified = 0;
    public long howManyTimesUpdated = 0;
    public long upVotes = 0;
    public long downVotes = 0;
    public String yourVote = "none";

    public GameSequence() {
        uuid = java.util.UUID.randomUUID().toString();
    }

    public String toBase64GZippedGSON() {
        Gson gson = new Gson();
        String json = gson.toJson(this);
        String zip = Utils.zipString(json);
        String base64 = Utils.encodeStringToBase64(zip);
        return base64;
    }

    public static GameSequence fromBase64GZippedGSON(String b64GZipJSON) {
        Gson gson = new Gson();
        String zip = Utils.decodeBase64String(b64GZipJSON);
        String json = Utils.unzipString(zip);
        if(json==null||json.length()==0){return null;}
        return gson.fromJson(json, GameSequence.class);
    }
}
