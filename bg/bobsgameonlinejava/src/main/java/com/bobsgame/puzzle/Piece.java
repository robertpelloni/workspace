package com.bobsgame.puzzle;

import com.bobsgame.shared.BobColor;
import java.util.ArrayList;

public class Piece {
    public Grid grid = null;
    public GameLogic game = null;

    public int currentRotation = 0;

    public int xGrid = 0;
    public int yGrid = 0;

    public ArrayList<Block> blocks = new ArrayList<>();

    public float cursorAlphaFrom = 0.3f;
    public float cursorAlphaTo = 1.0f;
    public long cursorFadeTicksPerPhase = 200;
    private float cursorAlpha = 0.3f;
    private long cursorFadeTicks = 0;
    private boolean cursorFadeInOutToggle = false;

    public float ghostAlphaFrom = 0.5f;
    public float ghostAlphaTo = 0.8f;
    public long ghostFadeTicksPerPhase = 200;
    private float ghostAlpha = 0.5f;
    private long ghostFadeTicks = 0;
    private boolean ghostFadeInOutToggle = false;

    public Block holdingBlock = null;
    public PieceType pieceType = null;
    public boolean overrideAnySpecialBehavior = false;
    public int piecesSetSinceThisPieceSet = 0;
    public boolean setInGrid = false;

    public Piece(GameLogic gameInstance, Grid grid, PieceType pieceType, ArrayList<BlockType> blockTypes) {
        this.game = gameInstance;
        this.grid = grid;
        this.pieceType = pieceType;

        int maxNumBlocks = 0;
        if (pieceType.rotationSet != null && !pieceType.rotationSet.rotationSet.isEmpty()) {
            for(Rotation r : pieceType.rotationSet.rotationSet) {
                maxNumBlocks = Math.max(maxNumBlocks, r.blockOffsets.size());
            }
        }

        for (int b = 0; b < maxNumBlocks; b++) {
            BlockType bt = blockTypes.isEmpty() ? new BlockType() : blockTypes.get(0);
            blocks.add(new Block(gameInstance, grid, this, bt));
        }

        setRotation(0);
    }

    public Piece(GameLogic gameInstance, Grid grid, PieceType pieceType, BlockType blockType) {
         this.game = gameInstance;
         this.grid = grid;
         this.pieceType = pieceType;

         int maxNumBlocks = 0;
         if (pieceType.rotationSet != null && !pieceType.rotationSet.rotationSet.isEmpty()) {
             for(Rotation r : pieceType.rotationSet.rotationSet) {
                 maxNumBlocks = Math.max(maxNumBlocks, r.blockOffsets.size());
             }
         }

         for (int b = 0; b < maxNumBlocks; b++) {
             blocks.add(new Block(gameInstance, grid, this, blockType));
         }

         setRotation(0);
    }

    public void init() {
        for (Block b : blocks) {
            b.piece = this;
            b.setRandomBlockTypeColor();
        }
    }

    public void update() {
        cursorFadeTicks += game.ticks();
        if (cursorFadeTicks > cursorFadeTicksPerPhase) {
            cursorFadeTicks = 0;
            cursorFadeInOutToggle = !cursorFadeInOutToggle;
        }
        if (cursorFadeInOutToggle) {
            cursorAlpha = cursorAlphaFrom + ((float)cursorFadeTicks / cursorFadeTicksPerPhase) * (cursorAlphaTo - cursorAlphaFrom);
        } else {
            cursorAlpha = cursorAlphaTo - ((float)cursorFadeTicks / cursorFadeTicksPerPhase) * (cursorAlphaTo - cursorAlphaFrom);
        }

        for (Block b : blocks) {
            b.update();
        }
    }

    public void setRotation(int rotation) {
        currentRotation = rotation;
        if (pieceType.rotationSet == null || pieceType.rotationSet.rotationSet.isEmpty()) return;

        if (rotation >= pieceType.rotationSet.size()) {
            rotation -= pieceType.rotationSet.size();
        }

        Rotation r = pieceType.rotationSet.get(rotation);

        for (int i = 0; i < getNumBlocksInCurrentRotation() && i < blocks.size(); i++) {
            BlockOffset b = r.blockOffsets.get(i);
            blocks.get(i).setXYOffsetInPiece(b.x, b.y);
        }
    }

    public void rotateCCW() {
        if (pieceType.rotationSet == null || pieceType.rotationSet.rotationSet.isEmpty()) return;
        if (currentRotation == 0) {
            currentRotation = pieceType.rotationSet.size() - 1;
        } else {
            currentRotation = currentRotation - 1;
        }
        setRotation(currentRotation);
    }

    public void rotateCW() {
        if (pieceType.rotationSet == null || pieceType.rotationSet.rotationSet.isEmpty()) return;
        if (currentRotation == pieceType.rotationSet.size() - 1) {
            currentRotation = 0;
        } else {
            currentRotation = currentRotation + 1;
        }
        setRotation(currentRotation);
    }

    public int getNumBlocksInCurrentRotation() {
        if (pieceType.rotationSet == null || pieceType.rotationSet.rotationSet.isEmpty()) return 0;
        return pieceType.rotationSet.get(currentRotation).blockOffsets.size();
    }

    public int getWidth() {
        int lowestX = 4;
        int highestX = -4;
        for (int i = 0; i < getNumBlocksInCurrentRotation(); i++) {
            Block b = blocks.get(i);
            if (b.xInPiece < lowestX) lowestX = b.xInPiece;
            if (b.xInPiece > highestX) highestX = b.xInPiece;
        }
        return 1 + Math.abs(highestX) + Math.abs(lowestX);
    }

    public int getHeight() {
        int lowestY = 4;
        int highestY = -4;
        for (int i = 0; i < getNumBlocksInCurrentRotation(); i++) {
            Block b = blocks.get(i);
            if (b.yInPiece < lowestY) lowestY = b.yInPiece;
            if (b.yInPiece > highestY) highestY = b.yInPiece;
        }
        return 1 + Math.abs(highestY) + Math.abs(lowestY);
    }

    public void renderAsCurrentPiece() {
        float x = getScreenX();
        float y = getScreenY();
        for (Block b : blocks) {
            b.render(x + b.xInPiece * grid.cellW(), y + b.yInPiece * grid.cellH(), 1.0f, 1.0f, true, false);
        }
    }

    public float getScreenX() {
        return grid.getXInFBO() + xGrid * grid.cellW();
    }

    public float getScreenY() {
        return grid.getYInFBO() + yGrid * grid.cellH() + (grid.scrollPlayingFieldY / grid.scrollBlockIncrement) * grid.cellH();
    }

    public void setBlocksSlamming() {
        for(Block b : blocks) {
            b.slamming = true;
            b.slamX = getScreenX() + b.xInPiece * grid.cellW();
            b.slamY = getScreenY() + b.yInPiece * grid.cellH();
        }
    }

    // Static generators
    public static RotationSet get1BlockCursorRotationSet() {
        RotationSet r = new RotationSet("1 Block Cursor");
        Rotation rot = new Rotation();
        rot.add(new BlockOffset(0,0));
        r.add(rot);
        return r;
    }

    public static RotationSet get4BlockIRotationSet(RotationType type) {
        // Simple 2-state rotation for now
        RotationSet rs = new RotationSet("4 Block I");

        Rotation r1 = new Rotation(); // Horizontal
        r1.add(new BlockOffset(-1, 0));
        r1.add(new BlockOffset(0, 0));
        r1.add(new BlockOffset(1, 0));
        r1.add(new BlockOffset(2, 0));
        rs.add(r1);

        Rotation r2 = new Rotation(); // Vertical
        r2.add(new BlockOffset(0, -1));
        r2.add(new BlockOffset(0, 0));
        r2.add(new BlockOffset(0, 1));
        r2.add(new BlockOffset(0, 2));
        rs.add(r2);

        return rs;
    }

    public static RotationSet get4BlockJRotationSet(RotationType type) {
        RotationSet rs = new RotationSet("4 Block J");
        // 0: J pointing left (standard spawn usually flat)
        // Let's implement standard SRS-like offsets for J
        // J:
        // *
        // ***
        Rotation r0 = new Rotation();
        r0.add(new BlockOffset(-1, -1));
        r0.add(new BlockOffset(-1, 0));
        r0.add(new BlockOffset(0, 0));
        r0.add(new BlockOffset(1, 0));
        rs.add(r0);

        // 90 deg clockwise
        // **
        // *
        // *
        Rotation r1 = new Rotation();
        r1.add(new BlockOffset(0, -1));
        r1.add(new BlockOffset(1, -1));
        r1.add(new BlockOffset(0, 0));
        r1.add(new BlockOffset(0, 1));
        rs.add(r1);

        // 180
        // ***
        //   *
        Rotation r2 = new Rotation();
        r2.add(new BlockOffset(-1, 0));
        r2.add(new BlockOffset(0, 0));
        r2.add(new BlockOffset(1, 0));
        r2.add(new BlockOffset(1, 1));
        rs.add(r2);

        // 270
        // *
        // *
        // **
        Rotation r3 = new Rotation();
        r3.add(new BlockOffset(0, -1));
        r3.add(new BlockOffset(0, 0));
        r3.add(new BlockOffset(0, 1));
        r3.add(new BlockOffset(-1, 1));
        rs.add(r3);

        return rs;
    }

    public static RotationSet get4BlockLRotationSet(RotationType type) {
        RotationSet rs = new RotationSet("4 Block L");
        // L:
        //   *
        // ***
        Rotation r0 = new Rotation();
        r0.add(new BlockOffset(1, -1));
        r0.add(new BlockOffset(-1, 0));
        r0.add(new BlockOffset(0, 0));
        r0.add(new BlockOffset(1, 0));
        rs.add(r0);

        Rotation r1 = new Rotation();
        r1.add(new BlockOffset(0, -1));
        r1.add(new BlockOffset(0, 0));
        r1.add(new BlockOffset(0, 1));
        r1.add(new BlockOffset(1, 1));
        rs.add(r1);

        Rotation r2 = new Rotation();
        r2.add(new BlockOffset(-1, 0));
        r2.add(new BlockOffset(0, 0));
        r2.add(new BlockOffset(1, 0));
        r2.add(new BlockOffset(-1, 1));
        rs.add(r2);

        Rotation r3 = new Rotation();
        r3.add(new BlockOffset(-1, -1));
        r3.add(new BlockOffset(0, -1));
        r3.add(new BlockOffset(0, 0));
        r3.add(new BlockOffset(0, 1));
        rs.add(r3);

        return rs;
    }

    public static RotationSet get4BlockORotationSet(RotationType type) {
        RotationSet rs = new RotationSet("4 Block O");
        Rotation r0 = new Rotation();
        r0.add(new BlockOffset(0, 0));
        r0.add(new BlockOffset(1, 0));
        r0.add(new BlockOffset(0, 1));
        r0.add(new BlockOffset(1, 1));
        rs.add(r0);
        return rs;
    }

    public static RotationSet get4BlockSRotationSet(RotationType type) {
        RotationSet rs = new RotationSet("4 Block S");
        //  **
        // **
        Rotation r0 = new Rotation();
        r0.add(new BlockOffset(0, -1));
        r0.add(new BlockOffset(1, -1));
        r0.add(new BlockOffset(-1, 0));
        r0.add(new BlockOffset(0, 0));
        rs.add(r0);

        Rotation r1 = new Rotation();
        r1.add(new BlockOffset(0, -1));
        r1.add(new BlockOffset(0, 0));
        r1.add(new BlockOffset(1, 0));
        r1.add(new BlockOffset(1, 1));
        rs.add(r1);

        return rs;
    }

    public static RotationSet get4BlockTRotationSet(RotationType type) {
        RotationSet rs = new RotationSet("4 Block T");
        //  *
        // ***
        Rotation r0 = new Rotation();
        r0.add(new BlockOffset(0, -1));
        r0.add(new BlockOffset(-1, 0));
        r0.add(new BlockOffset(0, 0));
        r0.add(new BlockOffset(1, 0));
        rs.add(r0);

        Rotation r1 = new Rotation();
        r1.add(new BlockOffset(0, -1));
        r1.add(new BlockOffset(0, 0));
        r1.add(new BlockOffset(1, 0));
        r1.add(new BlockOffset(0, 1));
        rs.add(r1);

        Rotation r2 = new Rotation();
        r2.add(new BlockOffset(-1, 0));
        r2.add(new BlockOffset(0, 0));
        r2.add(new BlockOffset(1, 0));
        r2.add(new BlockOffset(0, 1));
        rs.add(r2);

        Rotation r3 = new Rotation();
        r3.add(new BlockOffset(0, -1));
        r3.add(new BlockOffset(-1, 0));
        r3.add(new BlockOffset(0, 0));
        r3.add(new BlockOffset(0, 1));
        rs.add(r3);

        return rs;
    }

    public static RotationSet get4BlockZRotationSet(RotationType type) {
        RotationSet rs = new RotationSet("4 Block Z");
        // **
        //  **
        Rotation r0 = new Rotation();
        r0.add(new BlockOffset(-1, -1));
        r0.add(new BlockOffset(0, -1));
        r0.add(new BlockOffset(0, 0));
        r0.add(new BlockOffset(1, 0));
        rs.add(r0);

        Rotation r1 = new Rotation();
        r1.add(new BlockOffset(1, -1));
        r1.add(new BlockOffset(0, 0));
        r1.add(new BlockOffset(1, 0));
        r1.add(new BlockOffset(0, 1));
        rs.add(r1);

        return rs;
    }
}
