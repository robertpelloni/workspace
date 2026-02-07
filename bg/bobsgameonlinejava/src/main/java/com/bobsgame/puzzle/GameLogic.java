package com.bobsgame.puzzle;

import com.bobsgame.ClientMain;
import com.bobsgame.net.BobNet;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.shared.Utils;
import com.google.gson.Gson;
import java.util.ArrayList;
import java.util.Random;
import java.util.Vector;

// Stubs
class Room {
    public float gameSpeedStart = 0.0f;
    public long lockDelayMinimum = -1;
    public long spawnDelayLimit = -1;
    public long spawnDelayMinimum = -1;
    public long totalYLockDelayLimit = -1;
    public long floorSpinLimit = -1;

    public float gameSpeedChangeRate = 0.001f;
    public float gameSpeedMaximum = 1.0f;
    public long dropDelayMinimum = -1;

    public int levelUpMultiplier = 1;
    public int levelUpCompoundMultiplier = 1;

    public float lockDelayDecreaseRate = 0;
    public float spawnDelayDecreaseRate = 0;

    public boolean endlessMode = false;

    public boolean multiplayer_DisableVSGarbage = false;
    public int multiplayer_GarbageMultiplier = 1;
    public boolean multiplayer_GarbageScaleByDifficulty = false;
    public int multiplayer_GarbageLimit = 0;
}

public class GameLogic {
    // public static Logger log;

    public static final int LEFT = 0;
    public static final int RIGHT = 1;
    public static final int MIDDLE = 2;

    public Engine engine;
    public GameSequence currentGameSequence = new GameSequence();
    public PuzzlePlayer player;

    public ArrayList<PuzzleGameType> gameTypeRandomBag = new ArrayList<>();
    public PuzzleGameType currentGameType;

    public Grid grid = null;

    public int blockWidth = 1;
    public int blockHeight = 1;

    public static int aboveGridBuffer = 4;

    private long lockInputCountdownTicks = 0;

    public boolean won = false;
    public boolean lost = false;
    public boolean died = false;
    public boolean complete = false;
    public boolean didInit = false;

    private boolean firstInit = true;

    public ArrayList<Block> fadingOutBlocks = new ArrayList<>();
    public Piece currentPiece = null;
    public Piece lastPiece = null;
    public Piece holdPiece = null;
    public ArrayList<Piece> nextPieces = new ArrayList<>();
    public ArrayList<Piece> nextPieceSpecialBuffer = new ArrayList<>();

    public int lastKnownLevel = 0;
    public int currentLevel = 0;

    public long timeStarted = 0;
    public long timeEnded = 0;
    public long lastTicksPassed = 0;
    public long totalTicksPassed = 0;

    public int createdPiecesCounterForFrequencyPieces = 0;

    public boolean forceGravityThisFrame = false;
    public String previousGameString = "";

    public int totalCombosMade = 0;
    public int biggestComboChain = 0;

    public int lastSentGarbageToPlayerIndex = 0;
    public int queuedVSGarbageAmountToSend = 0;
    public int queuedVSGarbageAmountFromOtherPlayer = 0;
    public int garbageWaitForPiecesSetCount = 0;

    // Legacy support fields
    public int queuedGarbageAmountToSend = 0; // Alias for VS garbage? Or just keep both sync
    public boolean dead = false; // Alias for died
    public boolean win = false; // Alias for won
    public boolean lose = false; // Alias for lost

    public boolean isNetworkPlayer = false;
    public ArrayList<FrameState> framesArray = new ArrayList<>();
    public FrameState frameState = new FrameState();

    public long randomSeed = -1;
    public String uuid = "";
    public Random randomGenerator;

    // Logic vars
    public float gameSpeed = 0.0f;
    public long currentLineDropSpeedTicks = 0;
    public long currentStackRiseSpeedTicks = 0;
    public long lockDelayTicksCounter = 0;
    public long lineDropTicksCounter = 0;
    public long spawnDelayTicksCounter = 0;
    public long lineClearDelayTicksCounter = 0;
    public long moveDownLineTicksCounter = 0;

    public long currentTotalYLockDelay = 0;
    public long adjustedMaxLockDelayTicks = 0;
    public long adjustedSpawnDelayTicksAmount = 0;
    public long currentFloorMovements = 0;

    public int piecesMadeThisGame = 0;
    public int lastPiecesMadeThisGame = 0;
    public int blocksClearedThisGame = 0;
    public int linesClearedThisGame = 0;
    public int piecesMadeThisLevel = 0;
    public int blocksClearedThisLevel = 0;
    public int linesClearedThisLevel = 0;
    public int blocksMadeTotal = 0;
    public int piecesMadeTotal = 0;
    public int piecesPlacedTotal = 0;
    public int blocksClearedTotal = 0;
    public int linesClearedTotal = 0;

    public boolean pieceSetAtBottom = false;
    public boolean switchedHoldPieceAlready = false;
    public boolean gravityThisFrame = false;
    public boolean checkForChainAgainIfNoBlocksPopping = false;

    public int currentChain = 0;
    public int currentCombo = 0;
    public int comboChainTotal = 0;

    // Networking Helpers
    public boolean sendNetworkFrames = false;
    public boolean waitingForNetworkFrames = false;
    public boolean waitingForPlayer = false;
    public boolean controlledByNetwork = false;
    public boolean credits = false;

    public static class NetworkPacket {
        public Vector<FrameState> frameStates = new Vector<>();
    }
    public NetworkPacket networkPacket = new NetworkPacket();

    // Input helpers
    private boolean canPressRotateCW = false;
    private boolean canPressRotateCCW = false;
    private boolean canPressRight = false;
    private boolean canPressLeft = false;
    private boolean canPressDown = false;
    private boolean canPressUp = false;
    private boolean canPressHoldRaise = false;
    private boolean canPressSlam = false;

    private long ticksHoldingRotateCW = 0;
    private long ticksHoldingRotateCCW = 0;
    private long ticksHoldingRight = 0;
    private long ticksHoldingLeft = 0;
    private long ticksHoldingDown = 0;
    private long ticksHoldingUp = 0;
    private long ticksHoldingHoldRaise = 0;
    private long ticksHoldingSlam = 0;

    private boolean repeatStartedRotateCW = false;
    private boolean repeatStartedRotateCCW = false;
    private boolean repeatStartedHoldRaise = false;
    private boolean repeatStartedUp = false;
    private boolean repeatStartedDown = false;
    private boolean repeatStartedLeft = false;
    private boolean repeatStartedRight = false;
    private boolean repeatStartedSlam = false;

    public GameLogic(Engine g, long seed) {
        this.engine = g;
        this.randomSeed = seed;
        initializeRandomGenerator();
        this.grid = new Grid(this);
        this.player = new PuzzlePlayer(this);
        this.currentGameType = new PuzzleGameType();
    }

    public void initializeRandomGenerator() {
         if (this.randomSeed == -1) this.randomSeed = new Random().nextLong();
         this.randomGenerator = new Random(this.randomSeed);
    }

    public Engine getEngine() { return engine; }
    public Room getRoom() { return new Room(); } // Stub
    public DifficultyType getCurrentDifficulty() { return currentGameType.getDifficultyByName(currentGameSequence.currentDifficultyName); }

    public PuzzleGameType Settings() { return currentGameType; }
    public void setSettings(PuzzleGameType s) { this.currentGameType = s; }

    public void update(int gameIndex, int numGames, float forceWidth, float forceHeight) {
        if (!didInit) initGame();

        frameState = new FrameState();
        frameState.ticksPassed = engine.engineTicksPassed();

        // TODO: Handle pause

        setControlsState();
        processFrame();

        // Sync aliases
        this.dead = this.died;
        this.win = this.won;
        this.lose = this.lost;
        this.queuedGarbageAmountToSend = this.queuedVSGarbageAmountToSend;
    }

    public void updateNormalGame(int side) {
        // Wrapper for legacy calls
        update(side, 1, 0, 0); // Assuming standard update
    }

    public void updateNetworkGame() {
        // Called by network handler to process frames
        // TODO: process incoming frames from networkPacket
    }

    public void initGame() {
        if(firstInit) {
            firstInit = false;
            timeStarted = System.currentTimeMillis();
            gameSpeed = getRoom().gameSpeedStart;
            adjustedMaxLockDelayTicks = currentGameType.maxLockDelayTicks;
        }
        didInit = true;

        // TODO: Reset pieces, reformat grid, fill grid

        currentLineDropSpeedTicks = getCurrentDifficulty().initialLineDropSpeedTicks;
        currentStackRiseSpeedTicks = getCurrentDifficulty().maxStackRise;

        newRandomPiece();
    }

    public void setControlsState() {
        frameState.ROTATECW_HELD = player.ROTATECW_HELD;
        frameState.HOLDRAISE_HELD = player.HOLDRAISE_HELD;
        frameState.ROTATECCW_HELD = player.ROTATECCW_HELD;
        frameState.UP_HELD = player.UP_HELD;
        frameState.LEFT_HELD = player.LEFT_HELD;
        frameState.DOWN_HELD = player.DOWN_HELD;
        frameState.RIGHT_HELD = player.RIGHT_HELD;
        frameState.SLAM_HELD = player.SLAM_HELD;

        frameState.slamLock = player.slamLock;
        frameState.singleDownLock = player.singleDownLock;
        frameState.doubleDownLock = player.doubleDownLock;
    }

    public void processFrame() {
        totalTicksPassed += ticks();

        if (currentPiece != null) currentPiece.update();
        grid.update();

        // Timers
        if (lockDelayTicksCounter > 0) lockDelayTicksCounter -= ticks();
        if (lineDropTicksCounter > 0) lineDropTicksCounter -= ticks();
        if (spawnDelayTicksCounter > 0) spawnDelayTicksCounter -= ticks();
        if (lineClearDelayTicksCounter > 0) lineClearDelayTicksCounter -= ticks();

        if (currentGameType.gameMode == GameMode.DROP) {
            doFallingBlockGame();
        }

        // TODO: Chain checking and gravity
    }

    public void doFallingBlockGame() {
        if (!pieceSetAtBottom) {
            currentTotalYLockDelay += lockDelayTicksCounter;

            if (lineDropTicksCounter <= 0 && spawnDelayTicksCounter <= 0 && lineClearDelayTicksCounter <= 0) {
                boolean moved = movePiece(MovementType.DOWN);
                if (moved) {
                    lineDropTicksCounter = currentLineDropSpeedTicks;
                }
            }
            updateKeyInput();
        }
    }

    public boolean movePiece(MovementType move) {
        if (currentPiece == null) return false;

        if (move == MovementType.DOWN || move == MovementType.HARD_DROP) {
            currentPiece.yGrid++;
        } else if (move == MovementType.LEFT) {
            currentPiece.xGrid--;
        } else if (move == MovementType.RIGHT) {
            currentPiece.xGrid++;
        } else if (move == MovementType.ROTATE_CLOCKWISE) {
            currentPiece.rotateCW();
        }
        // TODO: Implement other moves and collision checks

        if (grid.doesPieceFit(currentPiece)) {
            // Valid move
            return true;
        } else {
            // Revert
            if (move == MovementType.DOWN || move == MovementType.HARD_DROP) currentPiece.yGrid--;
            else if (move == MovementType.LEFT) currentPiece.xGrid++;
            else if (move == MovementType.RIGHT) currentPiece.xGrid--;
            // else if rotate...

            if (move == MovementType.DOWN && lockDelayTicksCounter <= 0) {
                setPiece();
            }
            return false;
        }
    }

    public void setPiece() {
        grid.setPiece(currentPiece);
        pieceSetAtBottom = true;
        currentPiece = null;
        // Play sound
    }

    public void newRandomPiece() {
        pieceSetAtBottom = false;
        // TODO: Implement bag logic
        // For now just create a dummy piece
        currentPiece = new Piece(this, grid, new PieceType(), new BlockType());
        currentPiece.init();
        currentPiece.xGrid = grid.getWidth() / 2;
        currentPiece.yGrid = 0;
    }

    public void updateKeyInput() {
        // TODO: Implement full key repeat logic from C++
        if (frameState.LEFT_HELD && canPressLeft) {
            movePiece(MovementType.LEFT);
            // canPressLeft = false; // logic for repeat
        }
        if (frameState.RIGHT_HELD && canPressRight) {
            movePiece(MovementType.RIGHT);
        }
        // etc
    }

    public int getRandomIntLessThan(int i, String whereCalledFrom) {
        if (i <= 0) return 0;
        return randomGenerator.nextInt(i);
    }

    public int cellW() {
        return blockWidth + currentGameType.gridPixelsBetweenColumns;
    }

    public int cellH() {
        return blockHeight + currentGameType.gridPixelsBetweenRows;
    }

    public int gridW() {
        return currentGameType.gridWidth;
    }

    public int gridH() {
        return currentGameType.gridHeight + GameLogic.aboveGridBuffer;
    }

    public long ticks() {
        return frameState.ticksPassed;
    }

    public FrameState getFrameState() {
        return frameState;
    }

    // Networking
    public void sendPacketsToOtherPlayers() {
        if (ClientMain.clientMain != null && ClientMain.clientMain.gameClientTCP != null) {
            Gson gson = new Gson();
            String json = gson.toJson(networkPacket);
            String zip = Utils.zipString(json);
            String payload = Utils.encodeStringToBase64(zip);

            ClientMain.clientMain.gameClientTCP.send(BobNet.Bobs_Game_Frame_Packet + payload);
        }
    }

    public void incoming_FramePacket(String s) {
        Gson gson = new Gson();
        String zip = Utils.decodeBase64String(s);
        String json = Utils.unzipString(zip);

        if(json != null && !json.isEmpty()) {
            NetworkPacket packet = gson.fromJson(json, NetworkPacket.class);
            if(packet != null && packet.frameStates != null) {
                // In a real implementation, you would queue these or process them
                // For this port, we will just log or acknowledge receipt
                // incomingFramePackets.add(packet);
            }
        }
    }

    public void gotVSGarbageFromOtherPlayer(int amount) {
        queuedVSGarbageAmountFromOtherPlayer += amount;
    }

    public void renderBackground() {
        // Render simple background border for the grid
        if (grid == null) return;

        float x = grid.getXInFBO();
        float y = grid.getYInFBO();
        float w = grid.getWidth() * grid.cellW();
        float h = grid.getHeight() * grid.cellH();

        // Background
        com.bobsgame.client.GLUtils.drawFilledRectXYWH(x, y, w, h, 0.1f, 0.1f, 0.1f, 0.8f);

        // Border
        com.bobsgame.client.GLUtils.drawBox(x, x+w, y, y+h, 255, 255, 255);
    }

    public void renderBlocks() {
        if (grid == null) return;

        // Render blocks in grid
        for (int gy = 0; gy < grid.getHeight(); gy++) {
            for (int gx = 0; gx < grid.getWidth(); gx++) {
                Block b = grid.get(gx, gy);
                if (b != null) {
                    b.render(b.getScreenX(), b.getScreenY(), 1.0f, 1.0f, true, false);
                }
            }
        }

        // Render fading out blocks
        for (Block b : fadingOutBlocks) {
            b.renderDisappearing();
        }

        // Render current piece
        if (currentPiece != null) {
            // Render Ghost first (if enabled)
            // currentPiece.renderGhost(); // TODO: implement ghost render in Piece

            // Render actual piece
            currentPiece.renderAsCurrentPiece();
        }
    }

    public void renderForeground() {
        // Render HUD, Score, Next/Hold pieces
        // For now, minimal placeholder
        if (player != null) {
            // Render Next Pieces
            // Render Hold Piece
        }
    }

    public void resetNextPieces() {
        // TODO
    }

    public void deleteAllCaptions() {
        // TODO
    }
}
