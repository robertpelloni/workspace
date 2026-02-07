package com.bobsgame.puzzle;

import de.matthiasmann.twl.Button;
import de.matthiasmann.twl.ComboBox;
import de.matthiasmann.twl.DialogLayout;
import de.matthiasmann.twl.EditField;
import de.matthiasmann.twl.Label;
import de.matthiasmann.twl.ListBox;
import de.matthiasmann.twl.ScrollPane;
import de.matthiasmann.twl.TabbedPane;
import de.matthiasmann.twl.ToggleButton;
import de.matthiasmann.twl.Widget;
import de.matthiasmann.twl.model.SimpleChangableListModel;
import de.matthiasmann.twl.CallbackWithReason;
import de.matthiasmann.twl.ListBox.CallbackReason;
import java.util.UUID;

public class CustomGameEditor extends Widget {

    private TabbedPane tabbedPane;
    private PuzzleGameType currentGameType;

    // Settings Widgets
    private EditField nameField;
    private EditField rules1Field;
    private ComboBox<ScoreType> scoreTypeBox;
    private ToggleButton nextPieceEnabledBtn;

    // Block Widgets
    private ListBox<String> blockListBox;
    private SimpleChangableListModel<String> blockListModel;
    private EditField blockNameField;
    private EditField blockSpriteField;
    private ToggleButton blockUseInNormalPiecesBtn;
    private ToggleButton blockUseAsGarbageBtn;
    private BlockType currentEditingBlock = null;

    // Piece Widgets
    private ListBox<String> pieceListBox;
    private SimpleChangableListModel<String> pieceListModel;
    private EditField pieceNameField;
    private EditField pieceSpriteField;
    private ToggleButton pieceUseAsNormalBtn;
    private PieceType currentEditingPiece = null;

    // Difficulty Widgets
    private ListBox<String> diffListBox;
    private SimpleChangableListModel<String> diffListModel;
    private EditField diffNameField;
    private EditField initialSpeedField;
    private DifficultyType currentEditingDiff = null;

    public CustomGameEditor(PuzzleGameType gameType) {
        this.currentGameType = gameType != null ? gameType : new PuzzleGameType();

        tabbedPane = new TabbedPane();

        // Settings Tab
        Widget settingsTab = createSettingsTab();
        tabbedPane.addTab("Game Settings", settingsTab);

        // Block Tab
        Widget blockTab = createBlockTab();
        tabbedPane.addTab("Block Designer", blockTab);

        // Piece Tab
        Widget pieceTab = createPieceTab();
        tabbedPane.addTab("Piece Designer", pieceTab);

        // Difficulty Tab
        Widget diffTab = createDifficultyTab();
        tabbedPane.addTab("Difficulty Editor", diffTab);

        add(tabbedPane);
    }

    private Widget createSettingsTab() {
        DialogLayout layout = new DialogLayout();

        // General Rules
        nameField = new EditField();
        nameField.setText(currentGameType.name);

        rules1Field = new EditField();
        rules1Field.setText(currentGameType.rules1);

        SimpleChangableListModel<ScoreType> scoreModel = new SimpleChangableListModel<>(ScoreType.values());
        scoreTypeBox = new ComboBox<>(scoreModel);
        scoreTypeBox.setSelected(0); // TODO: sync with currentGameType

        nextPieceEnabledBtn = new ToggleButton("Next Piece Enabled");
        nextPieceEnabledBtn.setActive(currentGameType.nextPieceEnabled);

        layout.setHorizontalGroup(layout.createParallelGroup()
            .addWidget(new Label("Name"))
            .addWidget(nameField)
            .addWidget(new Label("Rules 1"))
            .addWidget(rules1Field)
            .addWidget(new Label("Score Type"))
            .addWidget(scoreTypeBox)
            .addWidget(nextPieceEnabledBtn)
        );

        layout.setVerticalGroup(layout.createSequentialGroup()
            .addWidget(new Label("Name"))
            .addWidget(nameField)
            .addWidget(new Label("Rules 1"))
            .addWidget(rules1Field)
            .addWidget(new Label("Score Type"))
            .addWidget(scoreTypeBox)
            .addWidget(nextPieceEnabledBtn)
        );

        ScrollPane scroll = new ScrollPane(layout);
        scroll.setFixed(ScrollPane.Fixed.HORIZONTAL);
        return scroll;
    }

    private Widget createBlockTab() {
        DialogLayout layout = new DialogLayout();

        blockListModel = new SimpleChangableListModel<>();
        for (BlockType b : currentGameType.blockTypes) {
            blockListModel.addElement(b.name);
        }

        blockListBox = new ListBox<>(blockListModel);
        blockListBox.addCallback(new CallbackWithReason<CallbackReason>() {
            public void callback(CallbackReason reason) {
                if (reason == CallbackReason.MOUSE_CLICK || reason == CallbackReason.SET_SELECTED) {
                    int selected = blockListBox.getSelected();
                    if (selected >= 0 && selected < currentGameType.blockTypes.size()) {
                        loadBlock(currentGameType.blockTypes.get(selected));
                    }
                }
            }
        });

        Button addBlockBtn = new Button("Add Block");
        addBlockBtn.addCallback(new Runnable() {
            public void run() {
                BlockType newBlock = new BlockType();
                newBlock.name = "New Block";
                newBlock.uuid = UUID.randomUUID().toString();
                currentGameType.blockTypes.add(newBlock);
                blockListModel.addElement(newBlock.name);
                blockListBox.setSelected(blockListModel.getNumEntries() - 1);
            }
        });

        blockNameField = new EditField();
        blockSpriteField = new EditField();
        blockUseInNormalPiecesBtn = new ToggleButton("Use in Normal Pieces");
        blockUseAsGarbageBtn = new ToggleButton("Use as Garbage");

        Button saveBlockBtn = new Button("Save Changes to Block");
        saveBlockBtn.addCallback(new Runnable() {
             public void run() {
                 if (currentEditingBlock != null) {
                     currentEditingBlock.name = blockNameField.getText();
                     currentEditingBlock.spriteName = blockSpriteField.getText();
                     currentEditingBlock.useInNormalPieces = blockUseInNormalPiecesBtn.isActive();
                     currentEditingBlock.useAsGarbage = blockUseAsGarbageBtn.isActive();

                     int idx = currentGameType.blockTypes.indexOf(currentEditingBlock);
                     if (idx != -1) {
                         blockListModel.removeElement(idx);
                         blockListModel.insertElement(idx, currentEditingBlock.name);
                         blockListBox.setSelected(idx);
                     }
                 }
             }
        });

        DialogLayout.Group hGroup = layout.createSequentialGroup()
            .addGroup(layout.createParallelGroup()
                .addWidget(new Label("Blocks"))
                .addWidget(blockListBox)
                .addWidget(addBlockBtn))
            .addGap(20)
            .addGroup(layout.createParallelGroup()
                .addWidget(new Label("Name"))
                .addWidget(blockNameField)
                .addWidget(new Label("Sprite"))
                .addWidget(blockSpriteField)
                .addWidget(blockUseInNormalPiecesBtn)
                .addWidget(blockUseAsGarbageBtn)
                .addWidget(saveBlockBtn));

        DialogLayout.Group vGroup = layout.createParallelGroup()
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup()
                     .addWidget(new Label("Blocks"))
                     .addWidget(new Label("Name")))
                .addGroup(layout.createParallelGroup()
                     .addWidget(blockListBox)
                     .addGroup(layout.createSequentialGroup()
                         .addWidget(blockNameField)
                         .addWidget(new Label("Sprite"))
                         .addWidget(blockSpriteField)
                         .addWidget(blockUseInNormalPiecesBtn)
                         .addWidget(blockUseAsGarbageBtn)
                         .addWidget(saveBlockBtn)))
                .addWidget(addBlockBtn));

        layout.setHorizontalGroup(hGroup);
        layout.setVerticalGroup(vGroup);

        return layout;
    }

    private void loadBlock(BlockType b) {
        currentEditingBlock = b;
        blockNameField.setText(b.name);
        blockSpriteField.setText(b.spriteName);
        blockUseInNormalPiecesBtn.setActive(b.useInNormalPieces);
        blockUseAsGarbageBtn.setActive(b.useAsGarbage);
    }

    private Widget createPieceTab() {
        DialogLayout layout = new DialogLayout();

        pieceListModel = new SimpleChangableListModel<>();
        for (PieceType p : currentGameType.pieceTypes) {
            pieceListModel.addElement(p.name);
        }

        pieceListBox = new ListBox<>(pieceListModel);
        pieceListBox.addCallback(new CallbackWithReason<CallbackReason>() {
            public void callback(CallbackReason reason) {
                if (reason == CallbackReason.MOUSE_CLICK || reason == CallbackReason.SET_SELECTED) {
                    int selected = pieceListBox.getSelected();
                    if (selected >= 0 && selected < currentGameType.pieceTypes.size()) {
                        loadPiece(currentGameType.pieceTypes.get(selected));
                    }
                }
            }
        });

        Button addPieceBtn = new Button("Add Piece");
        addPieceBtn.addCallback(new Runnable() {
            public void run() {
                PieceType newPiece = new PieceType();
                newPiece.name = "New Piece";
                newPiece.uuid = UUID.randomUUID().toString();
                currentGameType.pieceTypes.add(newPiece);
                pieceListModel.addElement(newPiece.name);
                pieceListBox.setSelected(pieceListModel.getNumEntries() - 1);
            }
        });

        pieceNameField = new EditField();
        pieceSpriteField = new EditField();
        pieceUseAsNormalBtn = new ToggleButton("Use as Normal Piece");

        Button savePieceBtn = new Button("Save Changes to Piece");
        savePieceBtn.addCallback(new Runnable() {
             public void run() {
                 if (currentEditingPiece != null) {
                     currentEditingPiece.name = pieceNameField.getText();
                     currentEditingPiece.spriteName = pieceSpriteField.getText();
                     currentEditingPiece.useAsNormalPiece = pieceUseAsNormalBtn.isActive();

                     int idx = currentGameType.pieceTypes.indexOf(currentEditingPiece);
                     if (idx != -1) {
                         pieceListModel.removeElement(idx);
                         pieceListModel.insertElement(idx, currentEditingPiece.name);
                         pieceListBox.setSelected(idx);
                     }
                 }
             }
        });

        DialogLayout.Group hGroup = layout.createSequentialGroup()
            .addGroup(layout.createParallelGroup()
                .addWidget(new Label("Pieces"))
                .addWidget(pieceListBox)
                .addWidget(addPieceBtn))
            .addGap(20)
            .addGroup(layout.createParallelGroup()
                .addWidget(new Label("Name"))
                .addWidget(pieceNameField)
                .addWidget(new Label("Sprite"))
                .addWidget(pieceSpriteField)
                .addWidget(pieceUseAsNormalBtn)
                .addWidget(savePieceBtn));

        DialogLayout.Group vGroup = layout.createParallelGroup()
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup()
                     .addWidget(new Label("Pieces"))
                     .addWidget(new Label("Name")))
                .addGroup(layout.createParallelGroup()
                     .addWidget(pieceListBox)
                     .addGroup(layout.createSequentialGroup()
                         .addWidget(pieceNameField)
                         .addWidget(new Label("Sprite"))
                         .addWidget(pieceSpriteField)
                         .addWidget(pieceUseAsNormalBtn)
                         .addWidget(savePieceBtn)))
                .addWidget(addPieceBtn));

        layout.setHorizontalGroup(hGroup);
        layout.setVerticalGroup(vGroup);

        return layout;
    }

    private void loadPiece(PieceType p) {
        currentEditingPiece = p;
        pieceNameField.setText(p.name);
        pieceSpriteField.setText(p.spriteName);
        pieceUseAsNormalBtn.setActive(p.useAsNormalPiece);
    }

    private Widget createDifficultyTab() {
        DialogLayout layout = new DialogLayout();

        diffListModel = new SimpleChangableListModel<>();
        for (DifficultyType d : currentGameType.difficultyTypes) {
            diffListModel.addElement(d.name);
        }

        diffListBox = new ListBox<>(diffListModel);
        diffListBox.addCallback(new CallbackWithReason<CallbackReason>() {
            public void callback(CallbackReason reason) {
                if (reason == CallbackReason.MOUSE_CLICK || reason == CallbackReason.SET_SELECTED) {
                    int selected = diffListBox.getSelected();
                    if (selected >= 0 && selected < currentGameType.difficultyTypes.size()) {
                        loadDiff(currentGameType.difficultyTypes.get(selected));
                    }
                }
            }
        });

        Button addDiffBtn = new Button("Add Difficulty");
        addDiffBtn.addCallback(new Runnable() {
            public void run() {
                DifficultyType newDiff = new DifficultyType();
                newDiff.name = "New Difficulty";
                currentGameType.difficultyTypes.add(newDiff);
                diffListModel.addElement(newDiff.name);
                diffListBox.setSelected(diffListModel.getNumEntries() - 1);
            }
        });

        diffNameField = new EditField();
        initialSpeedField = new EditField();

        Button saveDiffBtn = new Button("Save Changes to Difficulty");
        saveDiffBtn.addCallback(new Runnable() {
             public void run() {
                 if (currentEditingDiff != null) {
                     currentEditingDiff.name = diffNameField.getText();
                     try {
                         currentEditingDiff.initialLineDropSpeedTicks = Integer.parseInt(initialSpeedField.getText());
                     } catch (NumberFormatException e) {
                         // Ignore invalid input for now
                     }

                     int idx = currentGameType.difficultyTypes.indexOf(currentEditingDiff);
                     if (idx != -1) {
                         diffListModel.removeElement(idx);
                         diffListModel.insertElement(idx, currentEditingDiff.name);
                         diffListBox.setSelected(idx);
                     }
                 }
             }
        });

        DialogLayout.Group hGroup = layout.createSequentialGroup()
            .addGroup(layout.createParallelGroup()
                .addWidget(new Label("Difficulties"))
                .addWidget(diffListBox)
                .addWidget(addDiffBtn))
            .addGap(20)
            .addGroup(layout.createParallelGroup()
                .addWidget(new Label("Name"))
                .addWidget(diffNameField)
                .addWidget(new Label("Initial Speed (Ticks)"))
                .addWidget(initialSpeedField)
                .addWidget(saveDiffBtn));

        DialogLayout.Group vGroup = layout.createParallelGroup()
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup()
                     .addWidget(new Label("Difficulties"))
                     .addWidget(new Label("Name")))
                .addGroup(layout.createParallelGroup()
                     .addWidget(diffListBox)
                     .addGroup(layout.createSequentialGroup()
                         .addWidget(diffNameField)
                         .addWidget(new Label("Initial Speed (Ticks)"))
                         .addWidget(initialSpeedField)
                         .addWidget(saveDiffBtn)))
                .addWidget(addDiffBtn));

        layout.setHorizontalGroup(hGroup);
        layout.setVerticalGroup(vGroup);

        return layout;
    }

    private void loadDiff(DifficultyType d) {
        currentEditingDiff = d;
        diffNameField.setText(d.name);
        initialSpeedField.setText(String.valueOf(d.initialLineDropSpeedTicks));
    }

    @Override
    protected void layout() {
        tabbedPane.setSize(getInnerWidth(), getInnerHeight());
        tabbedPane.setPosition(getInnerX(), getInnerY());
    }

    public void save() {
        // Apply changes to currentGameType
        currentGameType.name = nameField.getText();
        currentGameType.rules1 = rules1Field.getText();
        currentGameType.nextPieceEnabled = nextPieceEnabledBtn.isActive();
        // ... rest
    }
}
