package com.bobsgame.puzzle;

import com.bobsgame.shared.BobColor;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class Grid {
    // public static Logger log;

    public GameLogic game = null;

    public float screenX = 0;
    public float screenY = 0;

    // Using 1D array for grid storage for performance and simplicity
    // Index = y * width + x
    private ArrayList<Block> blocks;

    public static Block nullBlock = null;

    private int wigglePlayingFieldTicksSpeed = 60;
    private int wigglePlayingFieldMaxX = 0;
    private float wigglePlayingFieldX = 0;
    private float wigglePlayingFieldY = 0;
    private long wigglePlayingFieldTicks = 0;
    private boolean wigglePlayingFieldLeftRightToggle = false;

    private int shakePlayingFieldScreenTicksCounter = 0;
    private long shakePlayingFieldStartTime = 0;
    private int shakePlayingFieldTicksDuration = 0;
    private int shakePlayingFieldMaxX = 0;
    private int shakePlayingFieldMaxY = 0;
    private int shakePlayingFieldTicksPerShake = 0;
    private int shakePlayingFieldTicksPerShakeXCounter = 0;
    private boolean shakePlayingFieldLeftRightToggle = false;
    private int shakePlayingFieldTicksPerShakeYCounter = 0;
    private boolean shakePlayingFieldUpDownToggle = false;
    private int shakePlayingFieldX = 0;
    private int shakePlayingFieldY = 0;

    public float scrollPlayingFieldY = 0;
    public float scrollBlockIncrement = 60;

    private int scrollPlayingFieldBackgroundTicksSpeed = 30;
    private int backgroundScrollX = 0;
    private int backgroundScrollY = 0;
    private long scrollPlayingFieldBackgroundTicks = 0;

    private int deadX = 0;
    private int deadY = 0;

    public int lastGarbageHoleX = 0;
    public boolean garbageHoleDirectionToggle = true;
    public ArrayList<Piece> randomBag = new ArrayList<>();

    public Grid(GameLogic gameInstance) {
        this.game = gameInstance;
        this.blocks = new ArrayList<>();
        // Initialize with nulls
        int size = getWidth() * getHeight();
        for (int i = 0; i < size; i++) {
            blocks.add(null);
        }
    }

    public float getXInFBO() {
        return getXInFBONoShake() + wigglePlayingFieldX + shakePlayingFieldX;
    }

    public float getYInFBO() {
        return getYInFBONoShake() + wigglePlayingFieldY + shakePlayingFieldY;
    }

    public float getXInFBONoShake() {
        // TODO: Access playingFieldX vars from GameLogic
        return 0; // Placeholder
    }

    public float getYInFBONoShake() {
        return 5 * cellH();
    }

    public int cellW() { return game.cellW(); }
    public int cellH() { return game.cellH(); }

    // TODO: Dynamic width/height from GameType
    public int getHeight() { return 20 + GameLogic.aboveGridBuffer; }
    public int getWidth() { return 10; }

    public void update() {
        ArrayList<Piece> piecesInGrid = getArrayOfPiecesOnGrid();
        for (Piece p : piecesInGrid) {
            p.update();
        }
        updateShake();
        wigglePlayingField();
    }

    public void add(int x, int y, Block b) {
        if (b == null) return;
        if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight()) return;

        b.xGrid = x;
        b.yGrid = y;
        b.grid = this;

        int index = y * getWidth() + x;
        if (index < blocks.size()) {
            blocks.set(index, b);
        }
        b.setInGrid = true;
    }

    public boolean contains(int x, int y) {
        if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight()) return false;
        int index = y * getWidth() + x;
        return blocks.get(index) != null;
    }

    public Block get(int x, int y) {
        if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight()) return null;
        int index = y * getWidth() + x;
        return blocks.get(index);
    }

    public Block remove(int x, int y, boolean fadeOut, boolean breakConnections) {
        if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight()) return null;

        int index = y * getWidth() + x;
        Block b = blocks.get(index);
        blocks.set(index, null);

        if (b != null) {
            b.setInGrid = false;
            if (fadeOut) {
                b.fadingOut = true;
                if (!game.fadingOutBlocks.contains(b)) {
                    game.fadingOutBlocks.add(b);
                }
            }
            if (breakConnections) {
                b.breakConnectionsInPiece();
            }
        }
        return b;
    }

    public void remove(Block b, boolean fadeOut, boolean breakConnections) {
        if (b.xGrid < 0 || b.yGrid < 0) return;
        remove(b.xGrid, b.yGrid, fadeOut, breakConnections);
    }

    public ArrayList<Piece> getArrayOfPiecesOnGrid() {
        ArrayList<Piece> piecesOnGrid = new ArrayList<>();
        for (int y = 0; y < getHeight(); y++) {
            for (int x = 0; x < getWidth(); x++) {
                Block b = get(x, y);
                if (b != null && b.piece != null && !piecesOnGrid.contains(b.piece)) {
                    piecesOnGrid.add(b.piece);
                }
            }
        }
        return piecesOnGrid;
    }

    public ArrayList<Block> checkLines(ArrayList<BlockType> ignoreTypes, ArrayList<BlockType> mustContainAtLeastOneTypes) {
        ArrayList<Block> blocksOnFullLines = new ArrayList<>();

        for (int y = getHeight() - 1; y >= 0; y--) {
            boolean lineFull = true;
            for (int x = 0; x < getWidth(); x++) {
                Block b = get(x, y);
                if (b == null || (ignoreTypes != null && ignoreTypes.contains(b.blockType))) {
                    lineFull = false;
                    break;
                }
            }

            if (lineFull) {
                for (int x = 0; x < getWidth(); x++) {
                    Block b = get(x, y);
                    if (!blocksOnFullLines.contains(b)) {
                        blocksOnFullLines.add(b);
                    }
                }
            }
        }
        return blocksOnFullLines;
    }

    public void setShakePlayingField(int ticksDuration, int maxX, int maxY, int ticksPerShake) {
        if (shakePlayingFieldScreenTicksCounter == 0) {
            shakePlayingFieldStartTime = System.nanoTime(); // using nanoTime as simple timer
        }
        shakePlayingFieldScreenTicksCounter += ticksDuration;
        shakePlayingFieldTicksDuration = shakePlayingFieldScreenTicksCounter;
        shakePlayingFieldMaxX = maxX;
        shakePlayingFieldMaxY = maxY;
        shakePlayingFieldTicksPerShake = ticksPerShake;
    }

    public void updateShake() {
        if (shakePlayingFieldScreenTicksCounter > 0) {
             shakePlayingFieldScreenTicksCounter -= game.ticks(); // Assuming ticks returns 1 per update for now
             if (shakePlayingFieldScreenTicksCounter < 0) shakePlayingFieldScreenTicksCounter = 0;
             // TODO: Implement Easing logic
        } else {
            shakePlayingFieldX = 0;
            shakePlayingFieldY = 0;
        }
    }

    public void wigglePlayingField() {
        wigglePlayingFieldTicks += 1; // Assuming 1 tick
        if (wigglePlayingFieldTicks > wigglePlayingFieldTicksSpeed) {
            wigglePlayingFieldTicks = 0;
            if (!wigglePlayingFieldLeftRightToggle) {
                wigglePlayingFieldX++;
                if (wigglePlayingFieldX > wigglePlayingFieldMaxX) {
                    wigglePlayingFieldLeftRightToggle = true;
                    wigglePlayingFieldX--;
                }
            } else {
                wigglePlayingFieldX--;
                if (wigglePlayingFieldX < -wigglePlayingFieldMaxX) {
                    wigglePlayingFieldLeftRightToggle = false;
                    wigglePlayingFieldX++;
                }
            }
        }
    }

    // Helper stubs
    public void shakeSmall() { setShakePlayingField(120, 2, 2, 40); }
    public void shakeMedium() { setShakePlayingField(300, 4, 2, 60); }
    public void shakeHard() { setShakePlayingField(600, 10, 10, 60); }

    public void checkRecursiveConnectedRowOrColumn(ArrayList<Block> connectedBlocks, int leastAmountConnected, int startX, int endX, int startY, int endY, ArrayList<BlockType> ignoreTypes, ArrayList<BlockType> mustContainAtLeastOneTypes) {
        for (int y = startY; y < endY; y++) {
            for (int x = startX; x < endX; x++) {
                Block b = get(x, y);
                if (b != null && (ignoreTypes == null || !ignoreTypes.contains(b.blockType))) {
                    ArrayList<Block> connected = new ArrayList<>();
                    addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowAtLeastAmount(b, connected, 2, startX, endX, startY, endY, ignoreTypes, mustContainAtLeastOneTypes);
                    addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInColumnAtLeastAmount(b, connected, 2, startX, endX, startY, endY, ignoreTypes, mustContainAtLeastOneTypes);

                    if (connected.size() > 0) {
                         // Recursive expansion (simplified for now)
                         if (connected.size() >= leastAmountConnected) {
                             for (Block c : connected) {
                                 if (!connectedBlocks.contains(c)) connectedBlocks.add(c);
                             }
                         }
                    }
                }
            }
        }
    }

    public void setColorConnections(ArrayList<BlockType> ignoreTypes) {
        for (int y = 0; y < getHeight(); y++) {
            for (int x = 0; x < getWidth(); x++) {
                Block b = get(x, y);
                if (b != null) b.connectedBlocksByColor.clear();
            }
        }

        for (int y = 0; y < getHeight(); y++) {
            for (int x = 0; x < getWidth(); x++) {
                Block b = get(x, y);
                if (b != null && (ignoreTypes == null || !ignoreTypes.contains(b.blockType))) {
                    ArrayList<Block> connected = new ArrayList<>();
                    recursivelyGetAllMatchingBlocksConnectedToBlockToArrayIfNotInItAlready(b, connected, ignoreTypes);
                    for (Block c : connected) {
                        if (b != c && !b.connectedBlocksByColor.contains(c)) {
                            b.connectedBlocksByColor.add(c);
                        }
                    }
                }
            }
        }
    }

    public boolean doBlocksMatchColor(Block a, Block b, ArrayList<BlockType> ignoreTypes) {
        if (a == null || b == null) return false;
        if ((ignoreTypes != null) && (ignoreTypes.contains(a.blockType) || ignoreTypes.contains(b.blockType))) return false;

        if (a.getColor() != null && b.getColor() != null && a.getColor().equals(b.getColor())) return true;
        if (a.blockType.matchAnyColor || b.blockType.matchAnyColor) return true;

        return false;
    }

    public ArrayList<Block> getConnectedBlocksUpDownLeftRight(Block b) {
        ArrayList<Block> connected = new ArrayList<>();
        if (b.xGrid + 1 < getWidth()) { Block n = get(b.xGrid + 1, b.yGrid); if (n != null) connected.add(n); }
        if (b.xGrid - 1 >= 0) { Block n = get(b.xGrid - 1, b.yGrid); if (n != null) connected.add(n); }
        if (b.yGrid + 1 < getHeight()) { Block n = get(b.xGrid, b.yGrid + 1); if (n != null) connected.add(n); }
        if (b.yGrid - 1 >= 0) { Block n = get(b.xGrid, b.yGrid - 1); if (n != null) connected.add(n); }
        return connected;
    }

    public void recursivelyGetAllMatchingBlocksConnectedToBlockToArrayIfNotInItAlready(Block b, ArrayList<Block> connected, ArrayList<BlockType> ignoreTypes) {
        if (!connected.contains(b)) connected.add(b);
        ArrayList<Block> neighbors = getConnectedBlocksUpDownLeftRight(b);
        for (Block n : neighbors) {
            if (doBlocksMatchColor(b, n, ignoreTypes)) {
                if (!connected.contains(n)) {
                    connected.add(n);
                    recursivelyGetAllMatchingBlocksConnectedToBlockToArrayIfNotInItAlready(n, connected, ignoreTypes);
                }
            }
        }
    }

    public void addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowAtLeastAmount(Block b, ArrayList<Block> connected, int least, int startX, int endX, int startY, int endY, ArrayList<BlockType> ignoreTypes, ArrayList<BlockType> mustContain) {
        ArrayList<Block> row = new ArrayList<>();
        row.add(b);
        // right
        for (int i = 1; b.xGrid + i < endX; i++) {
            Block n = get(b.xGrid + i, b.yGrid);
            if (doBlocksMatchColor(b, n, ignoreTypes)) row.add(n); else break;
        }
        // left
        for (int i = 1; b.xGrid - i >= startX; i++) {
            Block n = get(b.xGrid - i, b.yGrid);
            if (doBlocksMatchColor(b, n, ignoreTypes)) row.add(n); else break;
        }

        if (row.size() >= least) {
             // check mustContain
             for(Block c : row) {
                 if(!connected.contains(c)) connected.add(c);
             }
        }
    }

    public void addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInColumnAtLeastAmount(Block b, ArrayList<Block> connected, int least, int startX, int endX, int startY, int endY, ArrayList<BlockType> ignoreTypes, ArrayList<BlockType> mustContain) {
        ArrayList<Block> col = new ArrayList<>();
        col.add(b);
        // down
        for (int i = 1; b.yGrid + i < endY; i++) {
            Block n = get(b.xGrid, b.yGrid + i);
            if (doBlocksMatchColor(b, n, ignoreTypes)) col.add(n); else break;
        }
        // up
        for (int i = 1; b.yGrid - i >= startY; i++) {
            Block n = get(b.xGrid, b.yGrid - i);
            if (doBlocksMatchColor(b, n, ignoreTypes)) col.add(n); else break;
        }

        if (col.size() >= least) {
             for(Block c : col) {
                 if(!connected.contains(c)) connected.add(c);
             }
        }
    }

    public void addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfDiagonalAtLeastAmount(Block b, ArrayList<Block> connected, int least, int startX, int endX, int startY, int endY, ArrayList<BlockType> ignoreTypes, ArrayList<BlockType> mustContain) {
        ArrayList<Block> diag1 = new ArrayList<>();
        diag1.add(b);
        // down-right
        for (int i = 1; b.xGrid + i < endX && b.yGrid + i < endY; i++) {
            Block n = get(b.xGrid + i, b.yGrid + i);
            if (doBlocksMatchColor(b, n, ignoreTypes)) diag1.add(n); else break;
        }
        // up-left
        for (int i = 1; b.xGrid - i >= startX && b.yGrid - i >= startY; i++) {
            Block n = get(b.xGrid - i, b.yGrid - i);
            if (doBlocksMatchColor(b, n, ignoreTypes)) diag1.add(n); else break;
        }

        if (diag1.size() >= least) {
             for(Block c : diag1) {
                 if(!connected.contains(c)) connected.add(c);
             }
        }

        ArrayList<Block> diag2 = new ArrayList<>();
        diag2.add(b);
        // down-left
        for (int i = 1; b.xGrid - i >= startX && b.yGrid + i < endY; i++) {
            Block n = get(b.xGrid - i, b.yGrid + i);
            if (doBlocksMatchColor(b, n, ignoreTypes)) diag2.add(n); else break;
        }
        // up-right
        for (int i = 1; b.xGrid + i < endX && b.yGrid - i >= startY; i++) {
            Block n = get(b.xGrid + i, b.yGrid - i);
            if (doBlocksMatchColor(b, n, ignoreTypes)) diag2.add(n); else break;
        }

        if (diag2.size() >= least) {
             for(Block c : diag2) {
                 if(!connected.contains(c)) connected.add(c);
             }
        }
    }

    public boolean moveDownAnyBlocksAboveBlankSpacesOneLine(ArrayList<BlockType> ignoreTypes) {
        boolean moved = false;
        for (int y = getHeight() - 2; y >= 0; y--) {
            for (int x = 0; x < getWidth(); x++) {
                Block b = get(x, y);
                if (b != null && (ignoreTypes == null || !ignoreTypes.contains(b.blockType))) {
                    if (get(x, y + 1) == null) {
                        remove(x, y, false, false);
                        add(x, y + 1, b);
                        moved = true;
                    }
                }
            }
        }
        return moved;
    }

    public boolean moveDownDisconnectedBlocksAboveBlankSpacesOneLine(ArrayList<BlockType> ignoreTypes) {
        // Simplified for now
        return moveDownAnyBlocksAboveBlankSpacesOneLine(ignoreTypes);
    }

    public boolean moveDownLinesAboveBlankLinesOneLine() {
        // TODO
        return false;
    }

    public void makeGarbageRowFromFloor() {
        // TODO
    }

    public void makeGarbageRowFromCeiling() {
        // TODO
    }

    public void setPiece(Piece p) {
        setPiece(p, p.xGrid, p.yGrid);
    }

    public void setPiece(Piece p, int x, int y) {
        for(Block b : p.blocks) {
            add(x + b.xInPiece, y + b.yInPiece, b);
            b.setInGrid = true;
        }
        p.setInGrid = true;
    }

    public boolean doesPieceFit(Piece p) {
        return doesPieceFit(p, p.xGrid, p.yGrid);
    }

    public boolean doesPieceFit(Piece p, int x, int y) {
        for(Block b : p.blocks) {
            int tx = x + b.xInPiece;
            int ty = y + b.yInPiece;
            if(tx < 0 || tx >= getWidth()) return false;
            if(ty >= getHeight()) return false; // Floor
            if(ty >= 0 && get(tx, ty) != null) return false;
        }
        return true;
    }
}
