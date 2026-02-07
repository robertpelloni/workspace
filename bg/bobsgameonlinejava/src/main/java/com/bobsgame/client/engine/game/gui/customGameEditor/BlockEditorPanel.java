package com.bobsgame.client.engine.game.gui.customGameEditor;

import com.bobsgame.client.engine.game.nd.bobsgame.game.BlockType;
import com.bobsgame.shared.BobColor;

import de.matthiasmann.twl.Button;
import de.matthiasmann.twl.DialogLayout;
import de.matthiasmann.twl.EditField;
import de.matthiasmann.twl.Label;
import de.matthiasmann.twl.ToggleButton;
import de.matthiasmann.twl.model.SimpleBooleanModel;

public class BlockEditorPanel extends DialogLayout {

    private BlockType blockType;

    private EditField nameField;
    private EditField spriteField;

    private EditField colorR;
    private EditField colorG;
    private EditField colorB;

    private SimpleBooleanModel useNormalModel;
    private SimpleBooleanModel useGarbageModel;
    private SimpleBooleanModel useFillerModel;
    private SimpleBooleanModel flashingModel;
    private SimpleBooleanModel counterModel;
    private SimpleBooleanModel pacmanModel;

    public BlockEditorPanel() {
        //this.setTheme("blockeditorpanel");

        nameField = new EditField();
        nameField.addCallback(new EditField.Callback() {
            public void callback(int key) {
                if(blockType != null) blockType.name = nameField.getText();
            }
        });

        spriteField = new EditField();
        spriteField.addCallback(new EditField.Callback() {
            public void callback(int key) {
                if(blockType != null) blockType.sprite = spriteField.getText();
            }
        });

        EditField.Callback colorCallback = new EditField.Callback() {
            public void callback(int key) {
                updateColor();
            }
        };
        colorR = new EditField(); colorR.addCallback(colorCallback);
        colorG = new EditField(); colorG.addCallback(colorCallback);
        colorB = new EditField(); colorB.addCallback(colorCallback);

        useNormalModel = new SimpleBooleanModel();
        useNormalModel.addCallback(new Runnable() { public void run() { if(blockType!=null) blockType.useInNormalPieces = useNormalModel.getValue(); } });

        useGarbageModel = new SimpleBooleanModel();
        useGarbageModel.addCallback(new Runnable() { public void run() { if(blockType!=null) blockType.useAsGarbage = useGarbageModel.getValue(); } });

        useFillerModel = new SimpleBooleanModel();
        useFillerModel.addCallback(new Runnable() { public void run() { if(blockType!=null) blockType.useAsPlayingFieldFiller = useFillerModel.getValue(); } });

        flashingModel = new SimpleBooleanModel();
        flashingModel.addCallback(new Runnable() { public void run() { if(blockType!=null) blockType.flashingSpecialType = flashingModel.getValue(); } });

        counterModel = new SimpleBooleanModel();
        counterModel.addCallback(new Runnable() { public void run() { if(blockType!=null) blockType.counterType = counterModel.getValue(); } });

        pacmanModel = new SimpleBooleanModel();
        pacmanModel.addCallback(new Runnable() { public void run() { if(blockType!=null) blockType.pacmanType = pacmanModel.getValue(); } });

        ToggleButton useNormalBtn = new ToggleButton(useNormalModel); useNormalBtn.setText("Normal");
        ToggleButton useGarbageBtn = new ToggleButton(useGarbageModel); useGarbageBtn.setText("Garbage");
        ToggleButton useFillerBtn = new ToggleButton(useFillerModel); useFillerBtn.setText("Filler");
        ToggleButton flashingBtn = new ToggleButton(flashingModel); flashingBtn.setText("Flashing");
        ToggleButton counterBtn = new ToggleButton(counterModel); counterBtn.setText("Counter");
        ToggleButton pacmanBtn = new ToggleButton(pacmanModel); pacmanBtn.setText("Pacman");


        Group hGroup = createParallelGroup()
            .addGroup(createSequentialGroup().addWidget(new Label("Name")).addWidget(nameField))
            .addGroup(createSequentialGroup().addWidget(new Label("Sprite")).addWidget(spriteField))
            .addGroup(createSequentialGroup().addWidget(new Label("Color RGB")).addWidget(colorR).addWidget(colorG).addWidget(colorB))
            .addWidget(useNormalBtn)
            .addWidget(useGarbageBtn)
            .addWidget(useFillerBtn)
            .addWidget(flashingBtn)
            .addWidget(counterBtn)
            .addWidget(pacmanBtn);

        Group vGroup = createSequentialGroup()
            .addGroup(createParallelGroup().addWidget(new Label("Name")).addWidget(nameField))
            .addGroup(createParallelGroup().addWidget(new Label("Sprite")).addWidget(spriteField))
            .addGroup(createParallelGroup().addWidget(new Label("Color RGB")).addWidget(colorR).addWidget(colorG).addWidget(colorB))
            .addWidget(useNormalBtn)
            .addWidget(useGarbageBtn)
            .addWidget(useFillerBtn)
            .addWidget(flashingBtn)
            .addWidget(counterBtn)
            .addWidget(pacmanBtn);

        setHorizontalGroup(hGroup);
        setVerticalGroup(vGroup);
    }

    public void setBlockType(BlockType b) {
        this.blockType = b;
        if(b != null) {
            nameField.setText(b.name);
            spriteField.setText(b.sprite);
            if(b.colors != null && b.colors.length > 0) {
                BobColor c = b.colors[0];
                colorR.setText(""+c.getRed());
                colorG.setText(""+c.getGreen());
                colorB.setText(""+c.getBlue());
            } else {
                colorR.setText("255"); colorG.setText("255"); colorB.setText("255");
            }
            useNormalModel.setValue(b.useInNormalPieces);
            useGarbageModel.setValue(b.useAsGarbage);
            useFillerModel.setValue(b.useAsPlayingFieldFiller);
            flashingModel.setValue(b.flashingSpecialType);
            counterModel.setValue(b.counterType);
            pacmanModel.setValue(b.pacmanType);
        }
    }

    private void updateColor() {
        if(blockType == null) return;
        try {
            int r = Integer.parseInt(colorR.getText());
            int g = Integer.parseInt(colorG.getText());
            int b = Integer.parseInt(colorB.getText());
            BobColor c = new BobColor(r,g,b);
            blockType.colors = new BobColor[]{c};
        } catch (NumberFormatException e) {}
    }
}
