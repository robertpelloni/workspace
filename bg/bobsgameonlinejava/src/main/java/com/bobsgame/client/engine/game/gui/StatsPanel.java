package com.bobsgame.client.engine.game.gui;

import com.bobsgame.client.engine.game.nd.bobsgame.game.GameFileUtils;
import com.bobsgame.client.engine.game.nd.bobsgame.stats.BobsGameUserStats;
import de.matthiasmann.twl.Label;
import de.matthiasmann.twl.Button;

public class StatsPanel extends MenuPanel {

    private BobsGameUserStats stats;

    private Label totalGames;
    private Label totalBlocks;
    private Label totalPieces;
    private Label biggestCombo;
    private Label timePlayed;

    public StatsPanel() {
        super();

        Label title = new Label("User Statistics");
        //title.setTheme("titleLabel");

        totalGames = new Label("Total Games Played: 0");
        totalBlocks = new Label("Total Blocks Cleared: 0");
        totalPieces = new Label("Total Pieces Made: 0");
        biggestCombo = new Label("Biggest Combo: 0");
        timePlayed = new Label("Total Time Played: 0s");

        Button refreshButton = new Button("Refresh");
        refreshButton.addCallback(new Runnable() {
            public void run() {
                refreshStats();
            }
        });

        Button closeButton = new Button("Close");
        closeButton.addCallback(new Runnable() {
            public void run() {
                setActivated(false);
            }
        });

        insideScrollPaneLayout.setHorizontalGroup(
            insideScrollPaneLayout.createParallelGroup()
                .addWidget(title)
                .addWidget(totalGames)
                .addWidget(totalBlocks)
                .addWidget(totalPieces)
                .addWidget(biggestCombo)
                .addWidget(timePlayed)
                .addGroup(insideScrollPaneLayout.createSequentialGroup().addWidget(refreshButton).addWidget(closeButton))
        );

        insideScrollPaneLayout.setVerticalGroup(
            insideScrollPaneLayout.createSequentialGroup()
                .addWidget(title)
                .addWidget(totalGames)
                .addWidget(totalBlocks)
                .addWidget(totalPieces)
                .addWidget(biggestCombo)
                .addWidget(timePlayed)
                .addGroup(insideScrollPaneLayout.createParallelGroup().addWidget(refreshButton).addWidget(closeButton))
        );

        refreshStats();
    }

    private void refreshStats() {
        stats = GameFileUtils.loadUserStats();
        if(stats != null) {
            totalGames.setText("Total Games Played: " + stats.totalGamesPlayed);
            totalBlocks.setText("Total Blocks Cleared: " + stats.totalBlocksCleared);
            totalPieces.setText("Total Pieces Made: " + stats.totalPiecesMade);
            biggestCombo.setText("Biggest Combo: " + stats.biggestCombo);
            timePlayed.setText("Total Time Played: " + (stats.totalTimePlayed / 1000) + "s");
        }
    }

    @Override
    public void setActivated(boolean active) {
        super.setActivated(active);
        if(active) {
            refreshStats();
        }
    }

    @Override
    public void layout() {
        super.layout();
    }
}
