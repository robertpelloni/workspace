package com.bobsgame.client.engine.game.nd.bobsgame.game;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import com.bobsgame.client.engine.game.nd.bobsgame.stats.BobsGameUserStats;

public class GameFileUtils {

    public static final String GAMES_DIR = "games";
    public static final String TYPES_DIR = GAMES_DIR + File.separator + "types";
    public static final String SEQUENCES_DIR = GAMES_DIR + File.separator + "sequences";
    public static final String STATS_FILE = GAMES_DIR + File.separator + "stats.json";

    private static Gson gson = new GsonBuilder().setPrettyPrinting().create();

    public static void initDirs() {
        new File(TYPES_DIR).mkdirs();
        new File(SEQUENCES_DIR).mkdirs();
    }

    public static void saveGameType(GameType gt) {
        initDirs();
        // Sanitize filename
        String safeName = gt.name.replaceAll("[^a-zA-Z0-9.-]", "_");
        String filename = TYPES_DIR + File.separator + safeName + ".json";
        try (FileWriter writer = new FileWriter(filename)) {
            gson.toJson(gt, writer);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void saveGameSequence(GameSequence gs) {
        initDirs();
        String safeName = gs.name.replaceAll("[^a-zA-Z0-9.-]", "_");
        String filename = SEQUENCES_DIR + File.separator + safeName + ".json";
        try (FileWriter writer = new FileWriter(filename)) {
            gson.toJson(gs, writer);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static ArrayList<GameType> getGameTypeList() {
        initDirs();
        ArrayList<GameType> list = new ArrayList<GameType>();
        File dir = new File(TYPES_DIR);
        File[] files = dir.listFiles((d, name) -> name.endsWith(".json"));
        if (files != null) {
            for (File f : files) {
                try {
                    String content = new String(Files.readAllBytes(f.toPath()));
                    GameType gt = gson.fromJson(content, GameType.class);
                    if(gt != null) list.add(gt);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
        return list;
    }

    public static ArrayList<GameSequence> getGameSequenceList() {
        initDirs();
        ArrayList<GameSequence> list = new ArrayList<GameSequence>();
        File dir = new File(SEQUENCES_DIR);
        File[] files = dir.listFiles((d, name) -> name.endsWith(".json"));
        if (files != null) {
            for (File f : files) {
                try {
                    String content = new String(Files.readAllBytes(f.toPath()));
                    GameSequence gs = gson.fromJson(content, GameSequence.class);
                    if(gs != null) list.add(gs);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
        return list;
    }

    public static void saveUserStats(BobsGameUserStats stats) {
        initDirs();
        try (FileWriter writer = new FileWriter(STATS_FILE)) {
            gson.toJson(stats, writer);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static BobsGameUserStats loadUserStats() {
        initDirs();
        File f = new File(STATS_FILE);
        if(f.exists()) {
             try {
                String content = new String(Files.readAllBytes(f.toPath()));
                return gson.fromJson(content, BobsGameUserStats.class);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return new BobsGameUserStats();
    }
}
