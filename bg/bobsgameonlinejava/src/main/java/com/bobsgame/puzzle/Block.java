package com.bobsgame.puzzle;

import com.bobsgame.shared.BobColor;
import com.bobsgame.client.GLUtils;
import java.util.ArrayList;

public class Block {
    public GameLogic game = null;
    public Grid grid = null;

    public Piece piece = null;
    public ArrayList<Block> connectedBlocksByPiece = new ArrayList<>();
    public ArrayList<Block> connectedBlocksByColor = new ArrayList<>();

    public int xInPiece = 0;
    public int yInPiece = 0;

    public int xGrid = -1;
    public int yGrid = -1;

    public BlockType blockType = null;

    private BobColor color = null;

    public float effectAlphaFrom = 0.5f;
    public float effectAlphaTo = 0.8f;
    public long effectFadeTicksPerPhase = 1000;
    private float effectAlpha = 0.5f;
    private long effectFadeTicks = 0;
    private boolean effectFadeInOutToggle = false;

    public float colorFlashFrom = 0.0f;
    public float colorFlashTo = 1.0f;
    public long colorFlashTicksPerPhase = 100;
    private float colorFlash = 0.0f;
    private long colorFlashTicks = 0;
    private boolean colorFlashInOutToggle = false;

    public boolean overrideAnySpecialBehavior = false;

    public int interpolateSwappingWithX = 0;
    public int interpolateSwappingWithY = 0;
    public long swapTicks = 0;
    public boolean flashingToBeRemoved = false;
    public boolean flashingToBeRemovedLightDarkToggle = false;

    public boolean setInGrid = false;
    public boolean locking = false;
    public int lockingAnimationFrame = 0;
    public long lockAnimationFrameTicks = 0;

    public boolean fadingOut = false;
    public float disappearingAlpha = 1.0f;

    public float lastScreenX = -1;
    public float lastScreenY = -1;

    public long ticksSinceLastMovement = 0;

    public boolean slamming = false;
    private long ticksSinceSlam = 0;
    public float slamX = 0;
    public float slamY = 0;

    public AnimationState animationState = AnimationState.NORMAL;
    public int animationFrame = 0;
    public long animationFrameTicks = 0;
    public int animationFrameSpeed = 100;

    public int counterCount = -2;

    public boolean didFlashingColoredDiamond = false;
    public boolean ateBlocks = false;
    public int direction = -1;
    public long directionChangeTicksCounter = 0;

    public static final int UP = 0;
    public static final int LEFT = 1;
    public static final int DOWN = 2;
    public static final int RIGHT = 3;

    private int customInterpolationTicks = -1;

    public boolean popping = false;
    public boolean panic = false;

    public boolean connectedUp = false;
    public boolean connectedDown = false;
    public boolean connectedLeft = false;
    public boolean connectedRight = false;

    public boolean connectedUpRight = false;
    public boolean connectedDownRight = false;
    public boolean connectedUpLeft = false;
    public boolean connectedDownLeft = false;

    public Block() {}

    public Block(GameLogic game, Grid grid, Piece piece, BlockType blockType) {
        this.game = game;
        this.grid = grid;
        this.piece = piece;
        this.blockType = blockType;
    }

    public void update() {
        effectFadeTicks += game.ticks();
        ticksSinceLastMovement += game.ticks();

        if (slamming) {
            ticksSinceSlam += game.ticks();
            if (ticksSinceSlam >= 100) {
                slamming = false;
            }
        }

        if (locking) {
            lockAnimationFrameTicks += game.ticks();
            if (lockAnimationFrameTicks > 20) {
                lockAnimationFrameTicks = 0;
                if (lockingAnimationFrame < 8) {
                    lockingAnimationFrame++;
                } else {
                    lockingAnimationFrame = 0;
                    locking = false;
                }
            }
        }

        if (fadingOut) {
            if (disappearingAlpha > 0.0f) {
                disappearingAlpha -= (float)game.ticks() * 0.005f;
            }
            if (disappearingAlpha < 0.0f) disappearingAlpha = 0.0f;

            if (disappearingAlpha == 0.0f) {
                fadingOut = false;
                if(game.fadingOutBlocks.contains(this)) game.fadingOutBlocks.remove(this);
            }
        }
    }

    public void setXYOffsetInPiece(int x, int y) {
        this.xInPiece = x;
        this.yInPiece = y;
    }

    public void breakConnectionsInPiece() {
        if(connectedBlocksByPiece != null) connectedBlocksByPiece.clear();
        if(connectedBlocksByColor != null) connectedBlocksByColor.clear();
    }

    public float getScreenX() {
        if (grid == null) return 0;
        return grid.getXInFBO() + xGrid * grid.cellW();
    }

    public float getScreenY() {
        if (grid == null) return 0;
        return grid.getYInFBO() + yGrid * grid.cellH() + (grid.scrollPlayingFieldY / grid.scrollBlockIncrement) * grid.cellH();
    }

    public BobColor getColor() {
        return color;
    }

    public void setColor(BobColor color) {
        this.color = color;
    }

    public void setRandomBlockTypeColor() {
        if (blockType != null && !blockType.colors.isEmpty()) {
            int index = game.getRandomIntLessThan(blockType.colors.size(), "Block.setRandomColor");
            this.color = blockType.colors.get(index);
        }
    }

    public void render(float screenX, float screenY, float a, float scale, boolean interpolate, boolean ghost) {
        float w = grid.cellW() * scale;
        float h = grid.cellH() * scale;

        BobColor renderColor = color;
        if (renderColor == null) renderColor = BobColor.gray;

        if (slamming && ticksSinceSlam < 100) {
             float xDiff = screenX - slamX;
             float yDiff = screenY - slamY;
             screenX = slamX;
             screenY = slamY;
             // Stretch
             w += xDiff;
             h += yDiff;
        }

        if (interpolate && ticksSinceLastMovement < 100 && lastScreenX != -1) {
             // Simple lerp
             float t = (float)ticksSinceLastMovement / 100.0f;
             if (t > 1.0f) t = 1.0f;
             screenX = lastScreenX + (screenX - lastScreenX) * t;
             screenY = lastScreenY + (screenY - lastScreenY) * t;
        } else {
             lastScreenX = screenX;
             lastScreenY = screenY;
        }

        // Draw colored rectangle for now
        GLUtils.drawFilledRectXYWH(screenX, screenY, w, h, renderColor.rf(), renderColor.gf(), renderColor.bf(), a);

        // Outline
        GLUtils.drawBox(screenX, screenX+w, screenY, screenY+h, 255, 255, 255);
    }

    public void renderDisappearing() {
        render(getScreenX(), getScreenY(), disappearingAlpha, 1.0f + (2.0f - (disappearingAlpha * 2.0f)), true, false);
    }

    public void renderOutlines(float screenX, float screenY, float s) {
        // TODO
    }
}
