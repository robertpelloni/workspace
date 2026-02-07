package com.bobsgame.client.engine.game.gui.gameSequenceEditor;

import com.bobsgame.client.engine.game.gui.MenuPanel;
import com.bobsgame.client.engine.game.nd.bobsgame.game.GameSequence;
import com.bobsgame.client.engine.game.nd.bobsgame.game.GameType;
import com.bobsgame.client.engine.game.nd.bobsgame.game.GameLogic;
import com.bobsgame.client.engine.game.nd.bobsgame.game.GameFileUtils;

import de.matthiasmann.twl.Button;
import de.matthiasmann.twl.EditField;
import de.matthiasmann.twl.Label;
import de.matthiasmann.twl.ListBox;
import de.matthiasmann.twl.model.SimpleChangableListModel;
import java.util.ArrayList;

public class GameSequenceEditor extends MenuPanel {

    public GameSequence currentGameSequence;

    // Left Side: Available Types
    private ListBox<GameType> availableGameTypeList;
    private SimpleChangableListModel<GameType> availableGameTypeListModel;

    // Right Side: Current Sequence
    private EditField nameField;
    private EditField descriptionField;
    private ListBox<GameType> sequenceGameTypeList;
    private SimpleChangableListModel<GameType> sequenceGameTypeListModel;

    private Button addButton;
    private Button removeButton;
    private Button upButton;
    private Button downButton;

    private Button saveButton;
    private Button loadButton;
    private Button newButton;

    public GameSequenceEditor() {
        super();

        // --- Models ---
        availableGameTypeListModel = new SimpleChangableListModel<GameType>();
        for(GameType gt : GameLogic.getBuiltInGameTypes()) {
            availableGameTypeListModel.addElement(gt);
        }
        for(GameType gt : GameFileUtils.getGameTypeList()) {
            availableGameTypeListModel.addElement(gt);
        }

        sequenceGameTypeListModel = new SimpleChangableListModel<GameType>();

        // --- Widgets ---
        availableGameTypeList = new ListBox<GameType>(availableGameTypeListModel);

        sequenceGameTypeList = new ListBox<GameType>(sequenceGameTypeListModel);

        nameField = new EditField();
        nameField.setText("New Sequence");
        nameField.addCallback(new de.matthiasmann.twl.EditField.Callback() {
            public void callback(int key) {
                if(currentGameSequence != null) currentGameSequence.name = nameField.getText();
            }
        });

        descriptionField = new EditField();
        descriptionField.setText("Description");
        descriptionField.addCallback(new de.matthiasmann.twl.EditField.Callback() {
            public void callback(int key) {
                if(currentGameSequence != null) currentGameSequence.description = descriptionField.getText();
            }
        });

        addButton = new Button("Add >");
        addButton.addCallback(new Runnable() {
            public void run() {
                int sel = availableGameTypeList.getSelected();
                if(sel >= 0) {
                    GameType type = availableGameTypeListModel.getEntry(sel);
                    if(currentGameSequence != null) {
                        currentGameSequence.gameTypes.add(type);
                        refreshSequenceList();
                    }
                }
            }
        });

        removeButton = new Button("Remove");
        removeButton.addCallback(new Runnable() {
            public void run() {
                int sel = sequenceGameTypeList.getSelected();
                if(sel >= 0 && currentGameSequence != null) {
                    currentGameSequence.gameTypes.remove(sel);
                    refreshSequenceList();
                }
            }
        });

        upButton = new Button("Up");
        upButton.addCallback(new Runnable() {
            public void run() {
                int sel = sequenceGameTypeList.getSelected();
                if(sel > 0 && currentGameSequence != null) {
                    GameType t = currentGameSequence.gameTypes.remove(sel);
                    currentGameSequence.gameTypes.add(sel-1, t);
                    refreshSequenceList();
                    sequenceGameTypeList.setSelected(sel-1);
                }
            }
        });

        downButton = new Button("Down");
        downButton.addCallback(new Runnable() {
            public void run() {
                int sel = sequenceGameTypeList.getSelected();
                if(sel >= 0 && sel < sequenceGameTypeListModel.getNumEntries()-1 && currentGameSequence != null) {
                    GameType t = currentGameSequence.gameTypes.remove(sel);
                    currentGameSequence.gameTypes.add(sel+1, t);
                    refreshSequenceList();
                    sequenceGameTypeList.setSelected(sel+1);
                }
            }
        });

        newButton = new Button("New");
        newButton.addCallback(new Runnable() {
            public void run() {
                setGameSequence(new GameSequence());
            }
        });

        saveButton = new Button("Save");
        saveButton.addCallback(new Runnable() {
            public void run() {
                if(currentGameSequence != null) {
                    GameFileUtils.saveGameSequence(currentGameSequence);
                }
            }
        });

        loadButton = new Button("Load");
        loadButton.addCallback(new Runnable() {
            public void run() {
                // TODO: Implement load dialog
            }
        });

        // --- Layout ---

        Label availLabel = new Label("Available Types");
        Label seqLabel = new Label("Current Sequence");
        Label nameLabel = new Label("Name:");
        Label descLabel = new Label("Desc:");

        insideScrollPaneLayout.setHorizontalGroup(
            insideScrollPaneLayout.createSequentialGroup()
                .addGroup(insideScrollPaneLayout.createParallelGroup()
                    .addWidget(availLabel)
                    .addWidget(availableGameTypeList)
                )
                .addGroup(insideScrollPaneLayout.createParallelGroup()
                    .addWidget(addButton)
                )
                .addGroup(insideScrollPaneLayout.createParallelGroup()
                    .addGroup(insideScrollPaneLayout.createSequentialGroup()
                        .addGroup(insideScrollPaneLayout.createParallelGroup()
                            .addWidget(nameLabel)
                            .addWidget(descLabel)
                        )
                        .addGroup(insideScrollPaneLayout.createParallelGroup()
                            .addWidget(nameField)
                            .addWidget(descriptionField)
                        )
                    )
                    .addWidget(seqLabel)
                    .addWidget(sequenceGameTypeList)
                    .addGroup(insideScrollPaneLayout.createSequentialGroup()
                        .addWidget(removeButton)
                        .addWidget(upButton)
                        .addWidget(downButton)
                    )
                    .addGroup(insideScrollPaneLayout.createSequentialGroup()
                        .addWidget(newButton)
                        .addWidget(saveButton)
                        .addWidget(loadButton)
                    )
                )
        );

        insideScrollPaneLayout.setVerticalGroup(
            insideScrollPaneLayout.createParallelGroup()
                .addGroup(insideScrollPaneLayout.createSequentialGroup()
                    .addWidget(availLabel)
                    .addWidget(availableGameTypeList)
                )
                .addGroup(insideScrollPaneLayout.createSequentialGroup()
                    .addGap() // Push Add button to middle
                    .addWidget(addButton)
                    .addGap()
                )
                .addGroup(insideScrollPaneLayout.createSequentialGroup()
                    .addGroup(insideScrollPaneLayout.createParallelGroup()
                        .addWidget(nameLabel)
                        .addWidget(nameField)
                    )
                    .addGroup(insideScrollPaneLayout.createParallelGroup()
                        .addWidget(descLabel)
                        .addWidget(descriptionField)
                    )
                    .addWidget(seqLabel)
                    .addWidget(sequenceGameTypeList)
                    .addGroup(insideScrollPaneLayout.createParallelGroup()
                        .addWidget(removeButton)
                        .addWidget(upButton)
                        .addWidget(downButton)
                    )
                    .addGroup(insideScrollPaneLayout.createParallelGroup()
                        .addWidget(newButton)
                        .addWidget(saveButton)
                        .addWidget(loadButton)
                    )
                )
        );

        setGameSequence(new GameSequence());
    }

    public void setGameSequence(GameSequence seq) {
        this.currentGameSequence = seq;
        nameField.setText(seq.name);
        descriptionField.setText(seq.description);
        refreshSequenceList();
    }

    public void refreshSequenceList() {
        sequenceGameTypeListModel.clear();
        if(currentGameSequence != null) {
            for(GameType gt : currentGameSequence.gameTypes) {
                sequenceGameTypeListModel.addElement(gt);
            }
        }
    }
}
