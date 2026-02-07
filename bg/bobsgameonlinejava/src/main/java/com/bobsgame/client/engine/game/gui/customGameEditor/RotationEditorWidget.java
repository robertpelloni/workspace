package com.bobsgame.client.engine.game.gui.customGameEditor;

import com.bobsgame.client.engine.game.nd.bobsgame.game.Piece;
import com.bobsgame.client.engine.game.nd.bobsgame.game.Piece.BlockOffset;
import com.bobsgame.client.engine.game.nd.bobsgame.game.Piece.Rotation;

import de.matthiasmann.twl.DialogLayout;
import de.matthiasmann.twl.ToggleButton;

public class RotationEditorWidget extends DialogLayout {
    private ToggleButton[][] gridButtons;
    private Rotation rotation;
    private int size = 5;
    private int offset = 2; // center

    public RotationEditorWidget() {
        gridButtons = new ToggleButton[size][size];

        Group vGroup = createSequentialGroup();
        Group hMain = createParallelGroup();

        for(int y=0; y<size; y++) {
            Group rowGroupV = createSequentialGroup(); // For VGroup (contains widgets)
            Group rowGroupH = createSequentialGroup(); // For HGroup (contains widgets)

            for(int x=0; x<size; x++) {
                final int gx = x - offset;
                final int gy = y - offset;
                ToggleButton b = new ToggleButton();
                b.setMinSize(20, 20);
                b.setMaxSize(20, 20);
                if(gx==0 && gy==0) b.setText("C"); // Center mark

                final ToggleButton btnRef = b;
                b.addCallback(new Runnable() {
                    public void run() {
                        updateRotation(gx, gy, btnRef.isActive());
                    }
                });
                gridButtons[x][y] = b;
                rowGroupH.addWidget(b);
            }
            // For VGroup, we add a Group that contains the row widgets?
            // Actually, in DialogLayout:
            // VGroup: Sequential( Row1, Row2 )
            // HGroup: Parallel( Row1, Row2 )
            // But Row1 in VGroup needs to be Parallel(Widget, Widget)? No, widgets in a row are side-by-side (Horizontal).
            // Wait.
            // HGroup defines Horizontal relationship. Sequential(A, B) means A is left of B.
            // VGroup defines Vertical relationship. Parallel(A, B) means A and B are same height/y.

            // To make a grid:
            // HGroup: Parallel( RowH1, RowH2... ) where RowHi is Sequential(Cells).
            // VGroup: Sequential( RowV1, RowV2... ) where RowVi is Parallel(Cells).

            Group rowH = createSequentialGroup();
            Group rowV = createParallelGroup(); // Cells in a row share the same vertical space (Parallel in VGroup)

            for(int x=0; x<size; x++) {
                rowH.addWidget(gridButtons[x][y]);
                rowV.addWidget(gridButtons[x][y]);
            }

            hMain.addGroup(rowH);
            vGroup.addGroup(rowV);
        }

        setHorizontalGroup(hMain);
        setVerticalGroup(vGroup);
    }

    public void setRotation(Rotation r) {
        this.rotation = r;
        // Clear buttons
        for(int x=0;x<size;x++) for(int y=0;y<size;y++) gridButtons[x][y].setActive(false);

        if(r != null) {
            for(BlockOffset bo : r.blockOffsets) {
                int bx = bo.x + offset;
                int by = bo.y + offset;
                if(bx >= 0 && bx < size && by >= 0 && by < size) {
                    gridButtons[bx][by].setActive(true);
                }
            }
        }
    }

    private void updateRotation(int x, int y, boolean active) {
        if(rotation == null) return;

        // Remove existing
        for(int i=0; i<rotation.blockOffsets.size(); i++) {
            BlockOffset bo = rotation.blockOffsets.get(i);
            if(bo.x == x && bo.y == y) {
                rotation.blockOffsets.remove(i);
                break;
            }
        }

        if(active) {
            rotation.blockOffsets.add(new BlockOffset(x, y));
        }
    }
}
