package com.bobsgame.puzzle;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.UUID;

public class PuzzleGameType implements Serializable {
    public boolean downloaded = false;
    public String uuid = "";

    public long creatorUserID = 0;
    public String creatorUserName = "";
    public long dateCreated = 0;
    public long lastModified = 0;
    public long howManyTimesUpdated = 0;
    public long upVotes = 0;
    public long downVotes = 0;
    public String yourVote = "none";

    // Sounds
    public String normalMusic = "";
    public String fastMusic = "";
    public String winMusic = "";
    public String loseMusic = "";
    public String deadMusic = "";
    public String creditsMusic = "";

    public String blocksFlashingSound = "slam";
    public String singleLineFlashingSound = "single";
    public String doubleLineFlashingSound = "double";
    public String tripleLineFlashingSound = "triple";
    public String quadLineFlashingSound = "sosumi";

    public String hardDropSwishSound = "";
    public String hardDropClankSound = "slam2";
    public String switchHoldPieceSound = "hold";
    public String cantHoldPieceSound = "buzz";

    public String moveUpSound = "tick";
    public String moveDownSound = "tick";
    public String moveLeftSound = "tick";
    public String moveRightSound = "tick";

    public String pieceSetSound = "lock";
    public String touchBottomSound = "touchblock";
    public String wallKickSound = "wallkick";
    public String doubleWallKickSound = "doublewallkick";
    public String diagonalWallKickSound = "specialwallkick";
    public String floorKickSound = "floorkick";
    public String pieceFlip180Sound = "flip";

    public String rotateSound = "rotate";
    public String levelUpSound = "levelup";

    public String extraStage1Sound = "gtbling";
    public String extraStage2Sound = "gtbling";
    public String extraStage3Sound = "gtbling";
    public String extraStage4Sound = "gtbling";
    public String creditsSound = "gtbling";
    public String deadSound = "gtbling";
    public String winSound = "gtbling";
    public String loseSound = "gtbling";

    public String stackRiseSound = "tick";

    public String readySound = "ready";
    public String goSound = "go";

    public String gotBombSound = "gotBomb";
    public String gotWeightSound = "gotWeight";
    public String gotSubtractorSound = "gotSubtractor";
    public String gotAdderSound = "gotAdder";
    public String flashingClearSound = "flashingClear";
    public String scanlineClearSound = "scanlineClear";

    public boolean useRandomSoundModulation = false;

    // Game Rules
    public String name = "My New Game Type";
    public String rules1 = "Make a line of 3 or more matching colors to score!";
    public String rules2 = "The spark ball turns the blocks into circles.";
    public String rules3 = "The flashing ball matches any color.";

    public ScoreType scoreType = ScoreType.BLOCKS_CLEARED;
    public int scoreTypeAmountPerLevelGained = 4;

    public boolean nextPieceEnabled = true;
    public int numberOfNextPiecesToShow = 3;

    public boolean holdPieceEnabled = true;
    public boolean resetHoldPieceRotation = true;

    public boolean chainRule_CheckEntireLine = false;
    public int chainRule_AmountPerChain = 0;

    public boolean chainRule_CheckRow = false;
    public boolean chainRule_CheckColumn = false;
    public boolean chainRule_CheckDiagonal = false;
    public boolean chainRule_CheckRecursiveConnections = false;
    public boolean chainRule_CheckTouchingBreakerBlocksChain = false;

    public boolean gravityRule_onlyMoveDownDisconnectedBlocks = false;

    public GarbageType playingFieldGarbageType = GarbageType.ZIGZAG_PATTERN;
    public GarbageSpawnRule playingFieldGarbageSpawnRule = GarbageSpawnRule.NONE;

    public boolean hardDropPunchThroughToLowestValidGridPosition = false;

    public boolean twoSpaceWallKickAllowed = true;
    public boolean diagonalWallKickAllowed = true;
    public boolean pieceClimbingAllowed = true;
    public boolean flip180Allowed = true;
    public boolean floorKickAllowed = true;

    public int readyTicksAmount = 2000;

    // VS Rules
    public VSGarbageDropRule vsGarbageRule = VSGarbageDropRule.FALL_FROM_CEILING_IN_EVEN_ROWS;

    // Grid
    public int gridWidth = 10;
    public int gridHeight = 20;

    public int gridPixelsBetweenRows = 0;
    public int gridPixelsBetweenColumns = 0;

    public GameMode gameMode = GameMode.DROP;

    public boolean stackDontPutSameColorNextToEachOther = false;
    public boolean stackDontPutSameBlockTypeNextToEachOther = false;
    public boolean stackDontPutSameColorDiagonalOrNextToEachOtherReturnNull = false;
    public boolean stackLeaveAtLeastOneGapPerRow = false;

    public CursorType stackCursorType = CursorType.ONE_BLOCK_PICK_UP;

    public boolean blockRule_drawDotToSquareOffBlockCorners = false;
    public boolean drawDotOnCenterOfRotation = false;

    // Block
    public boolean gridRule_outlineOpenBlockEdges = false;
    public boolean fadeBlocksDarkerWhenLocking = true;
    public boolean blockRule_drawBlocksDarkerWhenLocked = false;
    public boolean blockRule_fillSolidSquareWhenSetInGrid = false;

    public boolean blockRule_drawBlocksConnectedByPieceIgnoringColor = false;
    public boolean blockRule_drawBlocksConnectedByColorIgnoringPiece = false;
    public boolean blockRule_drawBlocksConnectedByColorInPiece = false;

    public long blockMovementInterpolationTicks = 100;
    public int blockAnimationTicksRandomUpToBetweenLoop = 0;

    public ArrayList<BlockType> blockTypes = new ArrayList<>();

    // Piece
    public boolean whenGeneratingPieceDontMatchAllBlockColors = false;
    public boolean whenGeneratingPieceDontMatchTwoBlocksOfTheSameSpecialRandomTypeAndColor = false;
    public boolean whenGeneratingPieceDontMatchNormalBlockWithBlockOfDifferentTypeAndSameColor = false;

    public boolean currentPieceOutlineFirstBlockRegardlessOfPosition = false;
    public boolean currentPieceRule_OutlineBlockAtZeroZero = false;

    public boolean currentPieceRule_getNewPiecesRandomlyOutOfBagWithOneOfEachPieceUntilEmpty = false;

    public ArrayList<PieceType> pieceTypes = new ArrayList<>();
    public ArrayList<DifficultyType> difficultyTypes = new ArrayList<>();

    // Timing
    public float bloomIntensity = 1.5f;
    public int bloomTimes = 4;

    public long maxLockDelayTicks = 17 * 30;
    public long spawnDelayTicksAmountPerPiece = 30 * 17;
    public long lineClearDelayTicksAmountPerLine = 100 * 17;
    public long lineClearDelayTicksAmountPerBlock = 10 * 17;

    public long gravityRule_ticksToMoveDownBlocksOverBlankSpaces = 200;
    public boolean moveDownAllLinesOverBlankSpacesAtOnce = false;
    public int removingBlocksDelayTicksBetweenEachBlock = 0;

    public PuzzleGameType() {
        this.uuid = UUID.randomUUID().toString();
        // Add default difficulty
        DifficultyType normal = new DifficultyType();
        normal.name = "Normal";
        difficultyTypes.add(normal);
    }

    public DifficultyType getDifficultyByName(String name) {
        for (DifficultyType d : difficultyTypes) {
            if (d.name.equals(name)) return d;
        }
        if (!difficultyTypes.isEmpty()) return difficultyTypes.get(0);
        return new DifficultyType(); // Fallback
    }

    // Stub methods for getting filtered types based on difficulty
    public ArrayList<BlockType> getNormalBlockTypes(DifficultyType d) { return blockTypes; } // TODO: filter
    public ArrayList<BlockType> getGarbageBlockTypes(DifficultyType d) { return blockTypes; } // TODO: filter
    public ArrayList<BlockType> getPlayingFieldBlockTypes(DifficultyType d) { return blockTypes; } // TODO: filter
    public ArrayList<BlockType> getBlockTypesToIgnoreWhenCheckingChain(DifficultyType d) { return new ArrayList<>(); } // TODO
    public ArrayList<BlockType> getBlockTypesToIgnoreWhenMovingDown(DifficultyType d) { return new ArrayList<>(); } // TODO
    public ArrayList<BlockType> getBlockTypesChainMustContain(DifficultyType d) { return new ArrayList<>(); } // TODO
    public ArrayList<PieceType> getNormalPieceTypes(DifficultyType d) { return pieceTypes; } // TODO: filter
    public ArrayList<PieceType> getGarbagePieceTypes(DifficultyType d) { return pieceTypes; } // TODO: filter
    public ArrayList<PieceType> getPlayingFieldPieceTypes(DifficultyType d) { return pieceTypes; } // TODO: filter

    public BlockType getBlockTypeByUUID(String uuid) {
        for(BlockType b : blockTypes) {
            if(b.uuid.equals(uuid)) return b;
        }
        return null;
    }

    public PieceType getPieceTypeByUUID(String uuid) {
        for(PieceType p : pieceTypes) {
            if(p.uuid.equals(uuid)) return p;
        }
        return null;
    }

    public String toBase64GZippedGSON() {
        // TODO: Implement actual serialization
        return "";
    }
}
