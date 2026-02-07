package com.bobsgame.client.engine.game.gui.stuffMenu.subMenus;

import com.bobsgame.client.engine.game.gui.stuffMenu.SubPanel;
import com.bobsgame.client.engine.game.gui.GUIManager;
import de.matthiasmann.twl.Button;

public class EditorsPanel extends SubPanel {

    Button sequenceEditorButton;
    Button customGameEditorButton;
    Button gameSelectorButton;

    public EditorsPanel() {
        super();

        sequenceEditorButton = new Button("Game Sequence Editor");
        sequenceEditorButton.addCallback(new Runnable() {
            public void run() {
                GUIManager().openGameSequenceEditor();
            }
        });

        customGameEditorButton = new Button("Custom Game Editor");
        customGameEditorButton.addCallback(new Runnable() {
            public void run() {
                GUIManager().openCustomGameEditor();
            }
        });

        gameSelectorButton = new Button("Play Custom Games");
        gameSelectorButton.addCallback(new Runnable() {
            public void run() {
                GUIManager().openGameSelector();
            }
        });

        insideLayout.setHorizontalGroup(
            insideLayout.createParallelGroup()
                .addWidget(sequenceEditorButton)
                .addWidget(customGameEditorButton)
                .addWidget(gameSelectorButton)
        );

        insideLayout.setVerticalGroup(
            insideLayout.createSequentialGroup()
                .addWidget(sequenceEditorButton)
                .addWidget(customGameEditorButton)
                .addWidget(gameSelectorButton)
        );
    }
}
