package com.bobsgame.client.engine.game.gui.stuffMenu.subMenus;

import com.bobsgame.client.engine.game.gui.stuffMenu.SubPanel;
import com.bobsgame.client.engine.game.nd.NDGameEngine;
import com.bobsgame.client.engine.game.nd.bobsgame.BobsGame;
import com.bobsgame.puzzle.CustomGameEditor;
import com.bobsgame.puzzle.PuzzleGameType;

public class GameEditorPanel extends SubPanel {

    public CustomGameEditor customGameEditor;

    public GameEditorPanel() {
        super();

        // Pass null initially, will be updated in setVisible
        customGameEditor = new CustomGameEditor(new PuzzleGameType());

        insideLayout.setHorizontalGroup(insideLayout.createParallelGroup(customGameEditor));
        insideLayout.setVerticalGroup(insideLayout.createParallelGroup(customGameEditor));
    }

    @Override
    public void setVisible(boolean b) {
        super.setVisible(b);
        if (b) {
            // Try to hook up to the current game settings
            try {
                if (ND() != null) {
                    NDGameEngine game = ND().getGame();
                    if (game instanceof BobsGame) {
                        BobsGame bg = (BobsGame) game;
                        if (bg.ME != null && bg.ME.currentGameType != null) {
                            // Re-create the editor with the live settings object
                            // Or add a setGameType method to CustomGameEditor to update references
                            // For now, simpler to re-create to ensure UI sync
                            insideLayout.removeAllChildren();
                            customGameEditor = new CustomGameEditor(bg.ME.currentGameType);
                            insideLayout.setHorizontalGroup(insideLayout.createParallelGroup(customGameEditor));
                            insideLayout.setVerticalGroup(insideLayout.createParallelGroup(customGameEditor));
                        }
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void layout() {
        super.layout();
        // Ensure the editor takes up space
        customGameEditor.setSize(insideLayout.getInnerWidth(), insideLayout.getInnerHeight());
    }
}
