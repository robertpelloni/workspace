package com.bobsgame.client.engine.game.gui;

import com.bobsgame.client.engine.game.nd.bobsgame.game.GameSequence;
import com.bobsgame.client.engine.game.nd.bobsgame.game.GameFileUtils;
import com.bobsgame.client.engine.game.nd.bobsgame.game.GameLogic;
import com.bobsgame.client.engine.game.nd.bobsgame.BobsGame;
import de.matthiasmann.twl.Button;
import de.matthiasmann.twl.ListBox;
import de.matthiasmann.twl.model.SimpleChangableListModel;

public class GameSelector extends MenuPanel {
    private ListBox<GameSequence> sequenceList;
    private SimpleChangableListModel<GameSequence> sequenceListModel;
    private Button playButton;

    public GameSelector() {
        super();

        sequenceListModel = new SimpleChangableListModel<GameSequence>();
        sequenceList = new ListBox<GameSequence>(sequenceListModel);

        playButton = new Button("Play Sequence");

        // Layout
        insideScrollPaneLayout.setHorizontalGroup(
            insideScrollPaneLayout.createParallelGroup()
                .addWidget(sequenceList)
                .addWidget(playButton)
        );

        insideScrollPaneLayout.setVerticalGroup(
            insideScrollPaneLayout.createSequentialGroup()
                .addWidget(sequenceList)
                .addWidget(playButton)
        );

        playButton.addCallback(new Runnable() {
            @Override
            public void run() {
                int sel = sequenceList.getSelected();
                if(sel >= 0) {
                    GameSequence seq = sequenceListModel.getEntry(sel);

                    if(GUIManager() != null && GUIManager().ND() != null && GUIManager().ND().getGame() instanceof BobsGame) {
                         BobsGame bg = (BobsGame)GUIManager().ND().getGame();
                         bg.ME.setGameSequence(seq);
                         GUIManager().closeAllMenusAndND();
                         GUIManager().ND().setActivated(true);
                    }
                }
            }
        });
    }

    @Override
    public void setActivated(boolean active) {
        super.setActivated(active);
        if(active) {
            refreshList();
        }
    }

    public void refreshList() {
        sequenceListModel.clear();
        for(GameSequence gs : GameFileUtils.getGameSequenceList()) {
            sequenceListModel.addElement(gs);
        }
        // Add a default sequence
        GameSequence defaultSeq = new GameSequence();
        defaultSeq.name = "Built-in Games";
        defaultSeq.gameTypes.addAll(GameLogic.getBuiltInGameTypes());
        sequenceListModel.addElement(defaultSeq);
    }
}
