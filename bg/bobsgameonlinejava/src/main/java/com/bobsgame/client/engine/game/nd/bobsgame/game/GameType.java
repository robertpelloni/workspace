package com.bobsgame.client.engine.game.nd.bobsgame.game;

import java.util.ArrayList;

import com.bobsgame.client.engine.game.nd.bobsgame.BobsGame;
import com.bobsgame.client.engine.game.nd.bobsgame.game.BlockType.TurnFromBlockTypeToType;
import com.bobsgame.client.engine.game.nd.bobsgame.game.Piece.RotationType;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.Utils;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonElement;
import com.google.gson.JsonParser;


// =========================================================================================================================
public class GameType
{// =========================================================================================================================

    public String uuid = "";
    public boolean downloaded = false;

    public long creatorUserID = 0;
    public String creatorUserName = "";
    public long dateCreated = 0;
    public long lastModified = 0;
    public long howManyTimesUpdated = 0;
    public long upVotes = 0;
    public long downVotes = 0;
    public String yourVote = "none";

    public ArrayList<DifficultyType> difficultyTypes = new ArrayList<DifficultyType>();

    public enum GameMode
    {
        DROP,
        STACK,
    }
    public GameMode gameMode = GameMode.DROP;

    public void applyDifficulty(String difficultyName) {
        for(DifficultyType d : difficultyTypes) {
            if(d.name.equalsIgnoreCase(difficultyName)) {
                this.initialLineDropSpeedTicks = d.initialLineDropSpeedTicks;
                this.minimumLineDropSpeedTicks = d.minimumLineDropSpeedTicks;
                this.extraStage1Level = d.extraStage1Level;
                this.extraStage2Level = d.extraStage2Level;
                this.extraStage3Level = d.extraStage3Level;
                this.extraStage4Level = d.extraStage4Level;
                this.creditsLevel = d.creditsLevel;
                this.garbageSpawnRuleAmount = d.playingFieldGarbageSpawnRuleAmount;
                this.randomlyFillGrid = d.randomlyFillGrid;
                this.randomlyFillGridStartY = d.randomlyFillGridStartY;
                this.randomlyFillGridAmount = d.randomlyFillGridAmount;

                // TODO: Handle block/piece type restrictions
            }
        }
    }

	//---------------------------------------------------
	//controls
	//---------------------------------------------------
	public int repeatDelayA = 100;
	public int repeatDelayB = 100;
	public int repeatDelayR = 100;
	public int repeatDelayUp = 100;
	public int repeatDelayDown = 30;
	public int repeatDelayLeft = 50;
	public int repeatDelayRight = 50;

	public boolean repeatEnabledA = false;
	public boolean repeatEnabledB = false;
	public boolean repeatEnabledR = false;
	public boolean repeatEnabledUp = false;
	public boolean repeatEnabledDown = true;
	public boolean repeatEnabledLeft = true;
	public boolean repeatEnabledRight = true;

	public int repeatStartDelayA = 150;
	public int repeatStartDelayB = 150;
	public int repeatStartDelayR = 150;
	public int repeatStartDelayUp = 150;
	public int repeatStartDelayDown = repeatDelayDown;
	public int repeatStartDelayLeft = 150;
	public int repeatStartDelayRight = 150;

	//---------------------------------------------------
	// music and sound
	//----------------------------------------------------

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



	//---------------------------------------------------
	//timing
	//---------------------------------------------------

	public int maxLockDelayTicks=17*30;

	public int initialLineDropSpeedTicks=1000;
	public int minimumLineDropSpeedTicks=64;//256;
	public long spawnDelayTicksAmountPerPiece = 30*17;
	public long lineClearDelayTicksAmountPerLine = 100*17;
	public long lineClearDelayTicksAmountPerBlock = 10*17;

	//public int stackRiseSpeed = 0;//used for panel

	public long gravityRule_ticksToMoveDownBlocksOverBlankSpaces = 200;//used for dr.bob style slow fall
	public boolean moveDownAllLinesOverBlankSpacesAtOnce = false; //if we want old tetris style, instant fall

	public int removingBlocksDelayTicksBetweenEachBlock=0;
	public int timesToFlashBlocks = 20;
	public int flashBlockSpeedTicks = 30;

	public long flashScreenSpeedTicks=20;
	public int flashScreenTimesPerLevel=4;
	public int extraStage1Level=3;
	public int extraStage2Level=4;
	public int extraStage3Level=5;
	public int extraStage4Level=6;
	public int creditsLevel=9;



	public float bloomIntensity = 2.0f;
	public int bloomTimes = 1;


	public enum Difficulty
	{
		EASY,
		NORMAL,
		HARD,
		INTRO,
	}
	public Difficulty difficulty = Difficulty.NORMAL;


	public enum ScoreType
	{
		LINES_CLEARED,
		BLOCKS_CLEARED,
		PIECES_MADE,
	}
	public ScoreType scoreType = ScoreType.BLOCKS_CLEARED;

	public int scoreTypeAmountPerLevelGained = 4;



	public enum DropLockType
	{
		HARD_DROP_INSTANT_LOCK,
		SOFT_DROP_INSTANT_LOCK,
		NEITHER_INSTANT_LOCK,
	}
	public DropLockType dropLockType = DropLockType.HARD_DROP_INSTANT_LOCK;



	public enum GarbageType
	{
		MATCH_BOTTOM_ROW,
		RANDOM,
		SET_PATTERN,
	}
	public GarbageType garbageType = GarbageType.SET_PATTERN;


	public enum GarbageSpawnRule
	{
		NONE,
		TICKS,
		LINES_CLEARED,
		BLOCKS_CLEARED,
		PIECES_MADE,
	}
	public GarbageSpawnRule garbageSpawnRule = GarbageSpawnRule.NONE;

	public int garbageSpawnRuleAmount = 0;


	public enum VSGarbageRule
	{
		FALL_FROM_CEILING_IN_EVEN_ROWS,
		RISE_FROM_FLOOR_IN_EVEN_ROWS,
//
//		FALL_IN_1_RANDOM_COLUMN,
//		FALL_IN_2_RANDOM_COLUMNS,
//		FALL_IN_3_RANDOM_COLUMNS,
//
//		FALL_IN_1_COLUMN_FROM_LEFT,
//		FALL_IN_2_COLUMNS_FROM_LEFT,
//		FALL_IN_3_COLUMNS_FROM_LEFT,
//
//		FALL_IN_1_COLUMN_FROM_RIGHT,
//		FALL_IN_2_COLUMNS_FROM_RIGHT,
//		FALL_IN_3_COLUMNS_FROM_RIGHT,
//
//		FALL_IN_1_COLUMN_ON_EACH_SIDE,
//		FALL_IN_2_COLUMNS_ON_EACH_SIDE,
//		FALL_IN_3_COLUMNS_ON_EACH_SIDE,
//
//		FALL_IN_DIAGONAL_STEPS_DECREASING_FROM_SIDES_TO_MIDDLE,// /\
//		FALL_IN_DIAGONAL_STEPS_INCREASING_FROM_SIDES_TO_MIDDLE, // \/

	}
	public VSGarbageRule vsGarbageRule = VSGarbageRule.FALL_FROM_CEILING_IN_EVEN_ROWS;

	//---------------------------------------------------
	//game rules
	//---------------------------------------------------

	public boolean twoSpaceWallKickAllowed = true;//check away from wall, away twice from wall
	public boolean diagonalWallKickAllowed = true;//check away from wall, down, down away from wall
	public boolean pieceClimbingAllowed = true;//check held direction and up as many times as piece height.
	public boolean flip180Allowed = true;
	public boolean floorKickAllowed = true;

	public boolean nextPieceEnabled = true;
	public int numberOfNextPiecesToShow = 3;

	public boolean holdPieceEnabled = true;
	public boolean resetHoldPieceRotation = true;


	public boolean hardDropPunchThroughToLowestValidGridPosition = false;

	public boolean gravityRule_onlyMoveDownDisconnectedBlocks = false;

	public int chainRule_AmountPerChain = 0;
	public boolean chainRule_CheckEntireLine = false;
	public boolean chainRule_CheckRowOrColumn = false;
	public boolean chainRule_CheckDiagonal = false;
	public boolean chainRule_CheckRecursiveConnections = false;
	public boolean chainRule_CheckTouchingBreakerBlocksChain = false;


	public int readyTicksAmount = 2000;


public String name = "My New Game Type";
    @Override public String toString() { return name; }
	public String gameTypeCaptionText = "gameTypeCaptionText";
	public String rulesCaptionText = "rulesCaptionText";


	//---------------------------------------------------
	//grid
	//---------------------------------------------------

	public int gridWidth=10;
	public int gridHeight=20;

	public int gridPixelsBetweenRows = 0;
	public int gridPixelsBetweenColumns = 0;

	public boolean randomlyFillGrid = false;
	public int randomlyFillGridAmount = 0;
	public int randomlyFillGridStartY = 0;



	public boolean stackRiseGame = false;
	public boolean stackDontPutSameColorNextToEachOther = false;
	public boolean stackDontPutSameBlockTypeNextToEachOther = false;
	public boolean stackDontPutSameColorDiagonalOrNextToEachOtherReturnNull = false;
	public boolean stackLeaveAtLeastOneGapPerRow = false;


	public boolean randomlyFillStack = false;
	public int randomlyFillStackAmount = 0;
	public int randomlyFillStackStartY = 0;


	public boolean useCurrentPieceAsCursor=true;
	public boolean makeNewPiece = false;
	public boolean makeCursorPiece = false;
	public int cursorPieceSize = 1;



	public BobColor gridBorderColor = new BobColor(255,255,255);
	public BobColor gridCheckeredBackgroundColor1 = BobColor.black;
	public BobColor gridCheckeredBackgroundColor2 = new BobColor(8,8,8);
	public BobColor screenBackgroundColor = BobColor.black;

	public boolean gridRule_showWarningForFieldThreeQuartersFilled = false;

	//---------------------------------------------------
	//block
	//---------------------------------------------------


	public boolean whenGeneratingBlockDontGetBlockColorThatIsntOnGrid = false;//TODO, also check currentPiece, holdPiece, etc. and maybe replace colors.

	public boolean blockRule_drawDotToSquareOffBlockCorners = false;
	public boolean drawDotOnRotationPiece = false;
	public boolean gridRule_outlineOpenBlockEdges = false;
	public boolean fadeBlocksDarkerWhenLocking = true;
	public boolean blockRule_drawBlocksDarkerWhenLocked = false;
	public boolean blockRule_fillSolidSquareWhenSetInGrid = false;

	public boolean blockRule_drawBlocksConnectedByPieceIgnoringColor = false;
	public boolean blockRule_drawBlocksConnectedByColorIgnoringPiece = false;//can do sticky with this by checking blob color every frame
	public boolean blockRule_drawBlocksConnectedByColorInPiece = false;


	public ArrayList<BlockType> blockTypes = new ArrayList<BlockType>();

    public ArrayList<BlockType> getNormalBlockTypes() {
        ArrayList<BlockType> list = new ArrayList<BlockType>();
        for(BlockType b : blockTypes) if(b.useInNormalPieces) list.add(b);
        return list;
    }
    public ArrayList<BlockType> getGarbageBlockTypes() {
        ArrayList<BlockType> list = new ArrayList<BlockType>();
        for(BlockType b : blockTypes) if(b.useAsGarbage) list.add(b);
        return list;
    }
    public ArrayList<BlockType> getPlayingFieldBlockTypes() {
        ArrayList<BlockType> list = new ArrayList<BlockType>();
        for(BlockType b : blockTypes) if(b.useAsPlayingFieldFiller) list.add(b);
        return list;
    }
    public ArrayList<BlockType> getBlockTypesMustContainWhenCheckingChainConnections() {
        ArrayList<BlockType> list = new ArrayList<BlockType>();
        for(BlockType b : blockTypes) if(b.chainConnectionsMustContainAtLeastOneBlockWithThisTrue) list.add(b);
        return list;
    }
    public ArrayList<BlockType> getBlockTypesToIgnoreWhenCheckingChainConnections() {
        ArrayList<BlockType> list = new ArrayList<BlockType>();
        for(BlockType b : blockTypes) if(b.ignoreWhenCheckingChainConnections) list.add(b);
        return list;
    }
    public ArrayList<BlockType> getBlockTypesToIgnoreWhenMovingDownBlocks() {
        ArrayList<BlockType> list = new ArrayList<BlockType>();
        for(BlockType b : blockTypes) if(b.ignoreWhenMovingDownBlocks) list.add(b);
        return list;
    }



	public long blockMovementInterpolationTicks = 100;
	public int blockAnimationTicksRandomUpToBetweenLoop = 0;

	//---------------------------------------------------
	//piece
	//---------------------------------------------------

	public boolean whenGeneratingPieceDontMatchAllBlockColors = false;// used in columns
	public boolean whenGeneratingPieceDontMatchTwoBlocksOfTheSameSpecialRandomTypeAndColor = false;//used in puzzlefight
	public boolean whenGeneratingPieceDontMatchNormalBlockWithBlockOfDifferentTypeAndSameColor = false;

	public boolean currentPieceRenderAsNormalPiece = true; //set to false for cursors
	public boolean currentPieceOutlineAllPieces = false; //used for cursors
	public boolean currentPieceOutlineFirstBlockRegardlessOfPosition = false; //used in columns
	public boolean currentPieceRule_OutlineBlockAtZeroZero = false;
	public boolean currentPieceRenderHoldingBlock = false;
	public boolean currentPieceMoveUpHalfABlock = false;

	public boolean currentPieceRule_getNewPiecesRandomlyOutOfBagWithOneOfEachPieceUntilEmpty = false;

    public ArrayList<PieceType> pieceTypes = new ArrayList<PieceType>();

    public ArrayList<PieceType> getNormalPieceTypes() {
        ArrayList<PieceType> list = new ArrayList<PieceType>();
        for(PieceType p : pieceTypes) if(p.useAsNormalPiece) list.add(p);
        return list;
    }
    public ArrayList<PieceType> getDisallowedFirstPieceTypes() {
        ArrayList<PieceType> list = new ArrayList<PieceType>();
        for(PieceType p : pieceTypes) if(p.disallowAsFirstPiece) list.add(p);
        return list;
    }
    public ArrayList<PieceType> getGarbagePieceTypes() {
        ArrayList<PieceType> list = new ArrayList<PieceType>();
        for(PieceType p : pieceTypes) if(p.useAsGarbagePiece) list.add(p);
        return list;
    }
    public ArrayList<PieceType> getPlayingFieldPieceTypes() {
        ArrayList<PieceType> list = new ArrayList<PieceType>();
        for(PieceType p : pieceTypes) if(p.useAsPlayingFieldFillerPiece) list.add(p);
        return list;
    }





	//=========================================================================================================================
	public String toGSON()
	{//=========================================================================================================================

		//Gson gson = new Gson();
		//return gson.toJson(this);

		Gson gson = new GsonBuilder().setPrettyPrinting().create();

		String jsonString = gson.toJson(this);

		JsonElement el = JsonParser.parseString(jsonString);
		jsonString = gson.toJson(el); // done

		return jsonString;
	}


	//=========================================================================================================================
	public GameType fromGSON(String gsonString)
	{//=========================================================================================================================
		Gson gson = new Gson();
		return gson.fromJson(gsonString,GameType.class);

	}


	//=========================================================================================================================
	public String toBase64GZippedGSON()
	{//=========================================================================================================================
		Gson gson = new Gson();

		String json = gson.toJson(this);
		String zip = Utils.zipString(json);
		String base64 = Utils.encodeStringToBase64(zip);
		return base64;

	}

	//=========================================================================================================================
	public GameType fromBase64GZippedGSON(String b64GZipJSON)
	{//=========================================================================================================================

		Gson gson = new Gson();

		String zip = Utils.decodeBase64String(b64GZipJSON);
		String json = Utils.unzipString(zip);

		if(json==null||json.length()==0){return null;}

		return gson.fromJson(json,GameType.class);

	}







//	//=========================================================================================================================
//	public void addRandomSpecialPieceType(PieceType pieceType)
//	{//=========================================================================================================================
//
//		randomSpecialPieceTypes.add(pieceType);
//	}
//
//
//
//	//=========================================================================================================================
//	public void addRegularFrequencySpecialPieceType(PieceType pieceType)
//	{//=========================================================================================================================
//
//		regularFrequencySpecialPieceTypes.add(pieceType);
//	}


	//=========================================================================================================================
	public void addNormalPieceType(PieceType pieceType)
	{//=========================================================================================================================
        pieceType.useAsNormalPiece = true;
		if(!pieceTypes.contains(pieceType)) pieceTypes.add(pieceType);
	}

	//=========================================================================================================================
	public void addPlayingFieldPieceType(PieceType pieceType)
	{//=========================================================================================================================
        pieceType.useAsPlayingFieldFillerPiece = true;
		if(!pieceTypes.contains(pieceType)) pieceTypes.add(pieceType);
	}



	//=========================================================================================================================
	public void addDisallowedFirstPieceType(PieceType pieceType)
	{//=========================================================================================================================
        pieceType.disallowAsFirstPiece = true;
		if(!pieceTypes.contains(pieceType)) pieceTypes.add(pieceType);
	}


	//=========================================================================================================================
	public boolean isFirstPieceTypeAllowed(PieceType pieceType)
	{//=========================================================================================================================
		if(pieceType.disallowAsFirstPiece) return false;
		return true;
	}


	//=========================================================================================================================
	public void addNormalBlockType(BlockType blockClass)
	{//=========================================================================================================================
        blockClass.useInNormalPieces = true;
		if(!blockTypes.contains(blockClass)) blockTypes.add(blockClass);
	}

	//=========================================================================================================================
	public void addPlayingFieldBlockType(BlockType blockClass)
	{//=========================================================================================================================
        blockClass.useAsPlayingFieldFiller = true;
		if(!blockTypes.contains(blockClass)) blockTypes.add(blockClass);
	}
	//=========================================================================================================================
	public void addGarbageBlockType(BlockType blockClass)
	{//=========================================================================================================================
        blockClass.useAsGarbage = true;
		if(!blockTypes.contains(blockClass)) blockTypes.add(blockClass);
	}

//	//=========================================================================================================================
//	public void addRandomSpecialBlockType(BlockType blockClass)
//	{//=========================================================================================================================
//
//		randomSpecialBlockTypes.add(blockClass);
//	}
//
//	//=========================================================================================================================
//	public void addRegularFrequencySpecialBlockType(BlockType blockClass)
//	{//=========================================================================================================================
//
//		regularFrequencySpecialBlockTypes.add(blockClass);
//	}









	// =========================================================================================================================
	public void tetrid()
	{// =========================================================================================================================


		bloomIntensity = 3.0f;
		bloomTimes = 4;

		scoreType = ScoreType.LINES_CLEARED;
		scoreTypeAmountPerLevelGained = 5;



		chainRule_CheckEntireLine = true;


		stackLeaveAtLeastOneGapPerRow = true;

		gridRule_showWarningForFieldThreeQuartersFilled = true;
		gridRule_outlineOpenBlockEdges = true;

		blockRule_drawBlocksDarkerWhenLocked = true;
		blockRule_drawDotToSquareOffBlockCorners = true;
		blockRule_fillSolidSquareWhenSetInGrid = false;

		blockRule_drawBlocksConnectedByColorIgnoringPiece = false;
		blockRule_drawBlocksConnectedByPieceIgnoringColor = false;
		blockRule_drawBlocksConnectedByColorInPiece = true;


		currentPieceRule_getNewPiecesRandomlyOutOfBagWithOneOfEachPieceUntilEmpty=true;

		gravityRule_ticksToMoveDownBlocksOverBlankSpaces = 50;



		garbageSpawnRule = GarbageSpawnRule.PIECES_MADE;
		garbageSpawnRuleAmount = 5;



		BobColor[] colors = new BobColor[]{BobColor.cyan,BobColor.magenta,BobColor.green,BobColor.purple,BobColor.blue,BobColor.pink};


		BlockType blockWithNoColor = new BlockType(BobsGame.squareName,null);
		addNormalBlockType(blockWithNoColor);


		//BlockType flashingBlock = new BlockType("flashing",circle,BobColor.white,15,0);
		//addRandomSpecialBlockType(flashingBlock);


		BlockType blockWithColors = new BlockType(BobsGame.squareName,colors);
		addPlayingFieldBlockType(blockWithColors);


		BlockType grayBlock = new BlockType(BobsGame.squareName,null,BobColor.gray);
		addGarbageBlockType(grayBlock);


		PieceType cPiece = new PieceType(colors[0],3,Piece.get3PieceCRotationSet());
		PieceType iPiece = new PieceType(colors[1],3,Piece.get3PieceIRotationSet());
		PieceType jPiece = new PieceType(colors[2],3,Piece.get3PieceJRotationSet());
		PieceType lPiece = new PieceType(colors[3],3,Piece.get3PieceLRotationSet());
		PieceType dPiece = new PieceType(colors[4],3,Piece.get3PieceDRotationSet());
		PieceType tPiece = new PieceType(colors[5],3,Piece.get3PieceTRotationSet());

		addNormalPieceType(tPiece);
		addNormalPieceType(lPiece);
		addNormalPieceType(jPiece);
		addNormalPieceType(iPiece);
		addNormalPieceType(cPiece);
		if(difficulty==Difficulty.HARD)addNormalPieceType(dPiece);

		addDisallowedFirstPieceType(jPiece);
		addDisallowedFirstPieceType(lPiece);
		addDisallowedFirstPieceType(tPiece);
		if(difficulty==Difficulty.HARD)addDisallowedFirstPieceType(dPiece);









		int specialFrequency = 30;

		PieceType flashingCPiece = new PieceType(colors[0],3,Piece.get3PieceCRotationSet(),specialFrequency,0);
		PieceType flashingIPiece = new PieceType(colors[1],3,Piece.get3PieceIRotationSet(),specialFrequency,0);
		PieceType flashingJPiece = new PieceType(colors[2],3,Piece.get3PieceJRotationSet(),specialFrequency,0);
		PieceType flashingLPiece = new PieceType(colors[3],3,Piece.get3PieceLRotationSet(),specialFrequency,0);
		PieceType flashingDPiece = new PieceType(colors[4],3,Piece.get3PieceDRotationSet(),specialFrequency,0);
		PieceType flashingTPiece = new PieceType(colors[5],3,Piece.get3PieceTRotationSet(),specialFrequency,0);


		flashingCPiece.flashingSpecialType=true;
		flashingIPiece.flashingSpecialType=true;
		flashingJPiece.flashingSpecialType=true;
		flashingLPiece.flashingSpecialType=true;
		flashingDPiece.flashingSpecialType=true;
		flashingTPiece.flashingSpecialType=true;


		flashingCPiece.clearEveryRowPieceIsOnIfAnySingleRowCleared=true;
		flashingIPiece.clearEveryRowPieceIsOnIfAnySingleRowCleared=true;
		flashingIPiece.clearEveryRowPieceIsOnIfAnySingleRowCleared=true;
		flashingLPiece.clearEveryRowPieceIsOnIfAnySingleRowCleared=true;
		flashingDPiece.clearEveryRowPieceIsOnIfAnySingleRowCleared=true;
		flashingTPiece.clearEveryRowPieceIsOnIfAnySingleRowCleared=true;


		flashingCPiece.turnBackToNormalPieceAfterNPiecesLock=3;
		flashingIPiece.turnBackToNormalPieceAfterNPiecesLock=3;
		flashingIPiece.turnBackToNormalPieceAfterNPiecesLock=3;
		flashingLPiece.turnBackToNormalPieceAfterNPiecesLock=3;
		flashingDPiece.turnBackToNormalPieceAfterNPiecesLock=3;
		flashingTPiece.turnBackToNormalPieceAfterNPiecesLock=3;


		addNormalPieceType(flashingCPiece);
		addNormalPieceType(flashingIPiece);
		addNormalPieceType(flashingJPiece);
		addNormalPieceType(flashingLPiece);
		addNormalPieceType(flashingDPiece);
		addNormalPieceType(flashingTPiece);



		PieceType pieceShooterPiece = new PieceType(BobsGame.plusShooterBlockName, BobColor.white, 1, Piece.get1PieceCursorRotationSet(), 0, 0);
		pieceShooterPiece.flashingSpecialType = true;
		pieceShooterPiece.pieceShooterPiece = true;
		pieceShooterPiece.disappearOnceSetInGrid = true;
		//addRandomSpecialPieceType(pieceShooterPiece);

		BlockType pieceShooterPieceMakerBlock = new BlockType(BobsGame.squareName,BobsGame.plusShooterBlockName,null,BobColor.gray,specialFrequency,0);
		addNormalBlockType(pieceShooterPieceMakerBlock);
		pieceShooterPieceMakerBlock.flashingSpecialType = true;
		pieceShooterPieceMakerBlock.makePieceTypeWhenCleared = pieceShooterPiece;
		pieceShooterPieceMakerBlock.turnBackToNormalBlockAfterNPiecesLock=3;





		PieceType pieceRemovalShooterPiece = new PieceType(BobsGame.minusShooterBlockName, BobColor.darkGray, 1, Piece.get1PieceCursorRotationSet(), 0, 0);
		pieceRemovalShooterPiece.flashingSpecialType = true;
		pieceRemovalShooterPiece.pieceRemovalShooterPiece = true;
		pieceRemovalShooterPiece.disappearOnceSetInGrid = true;
		//addRandomSpecialPieceType(pieceRemovalShooterPiece);

		BlockType pieceRemovalShooterPieceMakerBlock = new BlockType(BobsGame.squareName,BobsGame.minusShooterBlockName,null,BobColor.gray,specialFrequency,0);
		addNormalBlockType(pieceRemovalShooterPieceMakerBlock);
		pieceRemovalShooterPieceMakerBlock.flashingSpecialType = true;
		pieceRemovalShooterPieceMakerBlock.makePieceTypeWhenCleared = pieceRemovalShooterPiece;
		pieceRemovalShooterPieceMakerBlock.turnBackToNormalBlockAfterNPiecesLock=3;





		PieceType bombPiece = new PieceType(BobsGame.bombName, BobColor.darkBlue, 4, Piece.get4PieceSolidRotationSet(), 0, 0);
		bombPiece.flashingSpecialType = true;
		bombPiece.bombPiece = true;
		bombPiece.disappearOnceSetInGrid = true;
		//addRandomSpecialPieceType(bombPiece);

		BlockType bombPieceMakerBlock = new BlockType(BobsGame.squareName, BobsGame.bombBlockName, null, BobColor.gray, specialFrequency, 0);
		addNormalBlockType(bombPieceMakerBlock);
		bombPieceMakerBlock.flashingSpecialType = true;
		bombPieceMakerBlock.makePieceTypeWhenCleared = bombPiece;
		bombPieceMakerBlock.turnBackToNormalBlockAfterNPiecesLock=3;




		PieceType weightPiece = new PieceType(BobsGame.weightName, BobColor.gray, 9, Piece.get9PieceSolidRotationSet(), 0, 0);
		weightPiece.flashingSpecialType = true;
		weightPiece.weightPiece = true;
		weightPiece.disappearOnceSetInGrid = true;
		//addRandomSpecialPieceType(weightPiece);


		BlockType weightPieceMakerBlock = new BlockType(BobsGame.squareName, BobsGame.weightBlockName, null, BobColor.gray, specialFrequency, 0);
		addNormalBlockType(weightPieceMakerBlock);
		weightPieceMakerBlock.flashingSpecialType = true;
		weightPieceMakerBlock.makePieceTypeWhenCleared = weightPiece;
		weightPieceMakerBlock.turnBackToNormalBlockAfterNPiecesLock=3;



		BlockType clear4LinesBlock = new BlockType(BobsGame.squareName, BobsGame.linesBlockName, null, BobColor.gray, specialFrequency, 0);
		addNormalBlockType(clear4LinesBlock);
		clear4LinesBlock.flashingSpecialType = true;
		clear4LinesBlock.clearEveryOtherLineOnGridWhenCleared = true;
		clear4LinesBlock.turnBackToNormalBlockAfterNPiecesLock=3;




//		normalMusic = "tetrid";
//		fastMusic = "tetrid_floatspeed";
//		deadMusic = "tetrid_death";
//		creditsMusic = "calmbeat";


		gameTypeCaptionText = "Game: Tetrid";
		rulesCaptionText = "Rules: Clear Lines";



		gridWidth = 8;
		gridHeight = 16;

		makeNewPiece = true;



	}







	// =========================================================================================================================
	public void tetsosumi()
	{// =========================================================================================================================


/*

piece animations for various actions/block states

sounds: swoosh
piece smash clank
piece set click
piece touch clink

smash
explosion
laser
buzz no

ready
go
wallkick
floatwallkick
special wallkick
floor kick
level up
speed up
single
float
triple
sosumi
special
flip
180
bonus
combo
tspin
chain

crank
"sosumi"
block flash
block explode
blob smush
blob bounce
bubble pop
flip 180
speed up
bonus
combo
chain
tspin
piece switch


*/



//TENGEN: piece stats, turns gray at bottom, screen wipe left-> right with SINGLE DOUBLE inside line when clear

//NES: line wipe from middle, screen flash for tetris
//NES tetris 2J: 1px movement, 1 in-between spin frame, pieces individually disintegrate on line clear, screen flash for tetris, next piece slides out

//tetris plus: puzzle mode has guy trying to escape, get him to the bottom before spikes kill him

//tetris DX, same as tetris GB, nice colors, start one brick higher i think,  **flash when lock, wall kicks, "ultra mode??" 2 minutes maybe?,  has nice attract mode with fish tank

//tetris world: hold piece, hard drop, infinite spin, wall kick, SRS, but laggy and ugly and 8px drop, no spin animation

//magical tetris challenge: has SRS, wallkick, first game() with hard drop, but uglier than tetris dx
//magical mode: has some 5 block pieces
//tower mode has 2 block piece that shoots 1 blocks

//new tetris (n64) won't work properly

//tetris ds:
//push mode is kind of what i wanted to do with a split field!

//tetris party deluxe is what i played against vivi for awhile
//has bombliss mode, climber mode, master mode, some weird modes
//has nice ghost piece and nice animations, look at this

//also look at cultris animations
//tgm3
//quadra
//nullpomino








//----------------------------------
//DONE: bloxeed items
//----------------------------------

/*
Garbage blocks rise from the floor of the playfield at timed intervals, thus making play more challenging.
The garbage rises a row at a time and follows a fixed looping pattern as depicted below.
Garbage never spawns when a line is cleared.
Sometimes it also fails to spawn immediately after levelling.
Also, collecting a powerup clears the garbage meter, further delaying garbage rows.
The garbage meter starts filling sooner and fills faster as the levels increase, and can fill even during line clear delay or ARE,
though this isn't really noticeable until you reach high levels.


The algorithm for introduction of powerup blocks is complicated. It depends on the current level,
how many times the garbage meter has filled since the last powerup block appeared, how high/messed up the stack is
(the worse off you are, the more powerup blocks appear), and how many pieces have been placed since the last powerup block appeared.

In two-player mode, clearing two or more rows will knock whatever piece is currently
falling in your opponent's well out and send most of the blocks of those two rows back at him.

*/



//----------------------------------
//TODO: tetris battle gaiden: collect balls in some pieces, pressing up does magic event which turns your field into all lines
//----------------------------------
/*
Level 1 - Turns bottom 3 lines to get rid of.
Level 2 - Makes the other person's screen dark for 3 pieces
Level 3 - Steals the other person's crystals in queue
Level 4 - Bombs the other person's side, leaving them with holes all over.

Level 1 - Smashes down the bottom 4 lines.
Level 2 - Turns the other person's controls upside down.
Level 3 - Pushes the other person's side up.
Level 4 -Inverts opponent's side.

Level 1 - Pushes the center to the sides and drops to fill holes, except crystal pieces.
Level 2 - Opponent's down = rotation
Level 3 - Stone come up on opponent's side as they play pieces, more if lines
Level 4 - Random level 4 of other characters. However, you may Medusa yourself.

Level 1 - Pushes the bottom two lines over to opponent.
Level 2 - Protects you from lines being sent to you.
Level 3 - Fax an image of your current layout to opponent.
Level 4 - Controls two pieces of your opponent.

Level 1 - Zaps away a column spanning 3 squares.
Level 2 - Reflects opponent's crystal attack.
Level 3 - Causes opponent to not have rotation for three pieces.
Level 4 - Copies the opponent's layout.

Level 1 - Top couple of lines get cleared away as the little pieces fall in.
Level 2 - Repeats the current piece.
Level 3 - Steals the other person's play area crystal.
Level 4 - Shakes up opponent's side, however may help them complete lines.

Level 1 - Pushes everything to one side.
Level 2 - Cause the opponent to get random pieces.
Level 3 - Puts a web up on opponent's side and holds up pieces, despite them completing lines.
Level 4 - Turns the other side into stone.

Level 1 - Cuts away the top four lines.
Level 2 - Slows down the opponent by nullifying the down button.
Level 3 - Friendship. As opponent sends you lines, your side goes down instead of up.
Level 4 - When one line gets completed, causes all pieces to fall, except where crystals are. Basically Rensa/cascade mode.

Level 1 - Pushes Dragon's stack together by one row (eliminating his two center columns) and down three rows.
Level 2 - For Dragon's next four pieces, he can select any type piece he wants by pressing L and R after the piece enters the field.
Level 3 - For the opponent's next 3 pieces, their controls are randomly scrambled according to an onscreen roulette.
Level 4 - Swap's Dragon's field with his opponent's.

Level 1 - Completely fills the bottom 4 rows of Queen's field.  Upon placing the next piece, this creates a Tetris, clearing 4 of her rows and sending 3 to the opponent.  If there are any Crystal Pieces in those rows, they are lost.
Level 2 - For the opponent's next four pieces, their movement controls are reversed. A completely useless power.  Any gamer worth their salt can deal with reversed controls, and this doesn't even reverse the Fast Drop / Crystal Power controls.
Level 3 - For a while, any rows Queen sends are floatd.  So if she makes a triple, it would send 6 rows.
Level 4 - Completely clears Queen's field.
*/





//----------------------------------
//TODO: TETRINET 2
//----------------------------------

/*
Depending on the game() room's settings, a special will appear onto each player's field after every X amount of line clears by that player.
Specials can be obtained by clearing their row off the field. If a player clears a special, the amount of that special received into the inventory is
multiplied by the amount of lines cleared. For example, clearing a special with a float line clear will yield 2 of those specials into your inventory.

Specials are used in inventory order by pressing the player number you wish to target.
Specials can be shuffled at the cost of 1 special by pressing the shuffle inventory key.
There are 14 possible specials that can appear:

a : Add Line - Adds a line of garbage
c : Clear Line - Clears a line from the bottom of the field.
b : Clear Special Blocks - Transforms all special blocks into regular blocks.
r : Random Blocks Clear - Randomly clears blocks, often making a messier field
o : Block Bomb - Only has an effect if the target's field has a Block Bomb special on it. Causes any blocks within a 3x3 radius of those specials to be scattered around their field.
q : Blockquake - Shifts the blocks on each row, often making a messier field and giving an earthquake effect.
g : Block Gravity - Causes all blocks to pull down to the bottom of the field, and will remove any lines cleared as a result.
s : Switch Fields - Switches your field with the target's field.
n : Nuke Field - Clears the entire field.
i : Immunity - Makes the target immune from being targeted by specials for X amount of seconds. Default = 15 seconds
v : Clear Column - Clears a random column.
m : Mutate Pieces - Makes the target's X next pieces large and odd shaped, often forcing the target to make a messier field. Default = 3 next pieces
d : Darkness - Turns the target's field black, hiding it from their view except for their current piece and a small window around it for X seconds. Default = 10 seconds
f : Confusion - Randomly switches the target's controls for X seconds. Default = 10 seconds
*/




//----------------------------------
//TODO: tgm1/2/3 special items
//----------------------------------

/*


all items are BAG random! won't get two items in a row ever until have gotten them all

DARK BLOCK - field becomes invisible.
MIRROR BLOCK = horizontal reverse playing field repeatedly for 3 pieces
EXCHG FIELD
X-RAY = field is invisible, once a second it "shines" across so you can kinda see
FREE FALL = shake field up and down and slam all holes away (cascade), and gravity is very slow
TRANS FORM  = rotate changes piece, flashing piece
ROLL ROLL = piece automatically rotates, gray piece
LASER = delete random column, mash button will make 2 wide, left or right will move
HARD BLOCK = makes metal block that when cleared each blocks turns normal and gravity on that line does not count, slows gravity
SHOT GUN = One block in each row of field becomes an empty cell.
180 FIELD  = flips field
DEL EVEN  = delete even lines
(L)MOV FIELD = slam all field pieces left
(R)MOV FIELD = slam all field pieces right
(D)DEL FIELD = deletes everything below row got
(U)DEL FIELD = deletes everything above row got
COLOR BLOCK = colors fade in tunnel pattern inward from black, hides playing field kinda
NEGA FIELD - Empty cells on field become blocks.
DEATH BLOCK = giant piece, slows gravity

*/





//----------------------------------
//TODO: heboris unofficial expansion items:
//----------------------------------
/*

Mirror Block
Duration:3 piece placements
Rarity:5
Opponent's active tetromino is destroyed.
Opponent's field is flipped horizontally for each individual placement.


Roll Roll
Duration:4 piece placements
Rarity:8
Opponent's active tetromino is destroyed.
Opponent's pieces are continuously rotated clockwise.


Death Block
Duration:Instant
Rarity:5
Opponent's active tetromino is destroyed.
Opponent's next tetromino is quadrupled in size.
(No effect in BIG mode)


X-Ray
Duration:4 piece placements
Rarity:9
Opponent's active tetromino is destroyed.
Opponent's field becomes invisible with periodic flashes of the silhouette.


Color Block
Duration:3 piece placements
Rarity:6
Opponent's active tetromino is destroyed.
Opponent's field background turns black.
Opponent's field is concealed by downward moving, arrow-shaped, black squares.


Rotate Lock
Duration:10 seconds
Rarity:3
Opponent is unable to rotate active piece.
Opponent is unable to use IRS
Opponent's next piece orientation is randomized.


Hide Next
Duration:15 seconds
Rarity:5
Opponent's preview is disabled.


Magnet Block
Duration:2 piece placements
Rarity:4
Opponent's active tetromino is destroyed.
Opponent's speed is added 0.5G.
Opponent's lock delay is reduced to 0.



Time Stop
Duration:5 seconds
Rarity:6
Opponent's active tetromino is frozen in position.
Opponent is unable to perform any commands.



Hold Lock
Duration:6 piece placements
Rarity:8
Opponent's active tetromino is destroyed.
Opponent is unable to hold active tetromino.
Opponent is unable to use IHS.


Reverse (Left/Right)
Duration:10 seconds
Rarity:4
Opponent's left and right input keys are switched.


Boost Fire
Duration:10 seconds
Rarity:7
Opponent's tetromino fall speed becomes 20g.
If opponent's default speed is 20g,opponent's lock delay becomes half instead.


Fever
Duration:10 seconds
Rarity:5
All of user's preview tetrominoes become I tetrominoes.
Enemy's Item attack is no effect.


Reverse (Up/Down)
Duration:10 seconds
Rarity:6
Opponent's up and down input keys are switched.


Remote Control
Duration:2 piece placements
Rarity:5
Opponent's active tetromino is destroyed.
User assumes control of opponent's inputs while, while maintaining control over his or her field.
Opponent is unable to perform any commands


Dark Block
Duration:8 seconds
Rarity:3
Opponent's active tetromino is destroyed.
Opponent's field becomes invisible.


Delete Field (Top)
Duration:Instant
Rarity:6
Top-most occupied rows will be cleared on the user's field.
Amount of rows cleared increases with the height of the highest occupied row.


Delete Field (Bottom
Duration:Instant
Rarity:6
Bottom-most rows will be cleared on the user's field.
Amount of rows cleared increases with the height of the highest occupied row.


Delete Even
Duration:Instant
Rarity:5
Every even row on the user's field is cleared. Even refers to the even row numbers of the playfield.


Transform
Duration:3 piece placements
Rarity:4
Opponent's active tetromino is destroyed.
Whenever opponent rotates active tetromino, a random tetromino takes its place in the rotated orientation.


Laser
Duration:Instant
Rarity:9
Opponent's active tetromino is destroyed.
A random column on opponent's field is turned into empty cells.
Opponent can move position of laser little, and add number of lasers by tapping rotate botton.


Negative Field
Duration:Instant
Rarity:1
Opponent's active tetromino is destroyed.
Blocks on opponent's field become empty cells.
Empty cells on opponent's field become blocks.


Shot Gun!
Duration:Instant
Rarity:5
Opponent's active tetromino is destroyed.
One block in each row of opponent's field becomes an empty cell.


Exchange Field
Duration:Instant
Rarity:1
Opponent's active tetromino is destroyed.
User and opponent trade fields.(No effect in solo mode)


Hard Block
Duration:Instant
Rarity:7
Opponent's active tetromino is destroyed.
Opponent's next tetromino requires two line clears in order to eliminate.


Shuffle Field
Duration:Instant
Rarity:7
Opponent's rows are shifted randomly left and right.
Opponent's empty columns stay connected only if the rows containing the columns are filled with 9 blocks each.


Random
Duration:Instant
Rarity:8
A random item effect is activated by rulet.


Free Fall
Duration:Instant
Rarity:3
Every block on the user's field is shifted as far down as possible.


Move Field (Left)
Duration:Instant
Rarity:2
Every block on the user's field is shifted as far left as possible.


Move Field (Right)
Duration:Instant
Rarity:5
Every block on the user's field is shifted as far right as possible.


180 Field
Duration:Instant
Rarity:7
Opponent's active tetromino is destroyed.
Opponent's field is flipped vertically with naive gravity still in tact.


16t
Duration:Instant
Rarity:4
3 columns on user's field is turned into empty cells.
User can move position of "16t".


Reflect
Duration:10 seconds
Rarity:3
(VERSUS)Opponent's Item attack is reflected to the opponent.(Others)User is protected from attack type item effect once.


Double
Duration:10 seconds
Rarity:3
Opponent's active tetromino is destroyed.
Garbage sent becomes 2 times higher.
(No effect in solo mode)


All Clear
Duration:Instant
Rarity:1
All of user's field is cleared.


Miss(joke)
Duration:20 piece placements
Rarity:5
(VERSUS)User's level and item guage are not added.
(Others)User's level, score and line count are not added.


Copy Field
Duration:Instant
Rarity:3
Opponent's active tetromino is destroyed.
Opponent's field becomes User's field.
(No effect in solo mode)


Fake Next
Duration:8 seconds
Rarity:2
Opponent's active tetromino is destroyed.
Opponent's shapes of preview and hold tetromino bocomes fake.


Grandmother Block
Duration:20 piece placements
Rarity:7
Opponent's active tetromino is destroyed.
All of opponent's block becomes "[ ]" blocks


*/




//dueltris items, same as bloxeed

//TODO: tetris DS items

//TODO: hotline from tetris worlds: clear horizonal white lines drawn across the playing field, let's integrate this as a special combo get



		bloomIntensity = 3.0f;
		bloomTimes = 4;


		scoreType = ScoreType.LINES_CLEARED;
		scoreTypeAmountPerLevelGained = 10;

		chainRule_CheckEntireLine = true;

		stackLeaveAtLeastOneGapPerRow = true;

		gridRule_showWarningForFieldThreeQuartersFilled = true;
		gridRule_outlineOpenBlockEdges = true;

		blockRule_drawBlocksDarkerWhenLocked = true;
		blockRule_drawDotToSquareOffBlockCorners = true;
		blockRule_fillSolidSquareWhenSetInGrid = false;
		blockRule_drawBlocksConnectedByColorIgnoringPiece = false;
		blockRule_drawBlocksConnectedByPieceIgnoringColor = false;
		blockRule_drawBlocksConnectedByColorInPiece = true;


		currentPieceRule_getNewPiecesRandomlyOutOfBagWithOneOfEachPieceUntilEmpty=true;

		gravityRule_ticksToMoveDownBlocksOverBlankSpaces = 50;


		garbageSpawnRule = GarbageSpawnRule.PIECES_MADE;
		garbageSpawnRuleAmount = 5;

		BobColor[] colors = new BobColor[]{BobColor.green,BobColor.purple};


		RotationType rotationType = RotationType.DTET;

		//SRS official colors
		if(rotationType==RotationType.SRS)
		{
			colors = new BobColor[]
			{
					BobColor.cyan,		//I
					BobColor.blue,		//J
					BobColor.orange,	//L
					BobColor.yellow,	//O
					BobColor.green,	//S
					BobColor.purple,	//T
					BobColor.red		//Z
			};
		}
		//SEGA/TGM/AKIRA colors
		if(rotationType==RotationType.SEGA || rotationType==RotationType.DTET)
		{
			colors = new BobColor[]
			{
					BobColor.red,		//I
					BobColor.blue,		//J
					BobColor.orange,	//L
					BobColor.yellow,	//O
					BobColor.magenta,	//S
					BobColor.cyan,		//T
					BobColor.green		//Z
			};
		}
		//DX (GBC) colors
		if(rotationType==RotationType.GB)
		{
			colors = new BobColor[]
			{
					BobColor.pink,		//I //light gray speckled with medium gray
					BobColor.blue,		//J //medium gray inner outlined white block
					BobColor.red,		//L //medium gray
					BobColor.yellow,	//O //white inner black block
					BobColor.purple,	//S //dark gray inner outlined white block
					BobColor.green,	//T //light gray inner embossed light gray block
					BobColor.orange	//Z //light gray with inner black dot
			};
		}
		//NES colors
		if(rotationType==RotationType.NES)
		{
			colors = new BobColor[]
			{
					BobColor.white,	//I //red outline, white inside
					BobColor.red,		//J
					BobColor.olive,	//L
					BobColor.white,	//O //red outline, white inside
					BobColor.red,		//S
					BobColor.white,	//T //red outline, white inside
					BobColor.olive		//Z
			};
		}



		colors = new BobColor[]
		{
				BobColor.pink,
				BobColor.blue,
				BobColor.aqua,
				BobColor.purple,
				BobColor.magenta,
				BobColor.cyan,
				BobColor.green,
		};











		BlockType blockWithNoColor = new BlockType(BobsGame.squareName,null);
		addNormalBlockType(blockWithNoColor);

		//BlockType flashingBlock = new BlockType("flashing",circle,BobColor.white,15,0);
		//addRandomSpecialBlockType(flashingBlock);


		BlockType blockWithColors = new BlockType(BobsGame.squareName,colors);
		addPlayingFieldBlockType(blockWithColors);


		BlockType grayBlock = new BlockType(BobsGame.squareName,null,BobColor.gray);
		addGarbageBlockType(grayBlock);



		PieceType normalIPiece = new PieceType(colors[0],4,Piece.get4PieceIRotationSet(rotationType));
		PieceType normalJPiece = new PieceType(colors[1],4,Piece.get4PieceJRotationSet(rotationType));
		PieceType normalLPiece = new PieceType(colors[2],4,Piece.get4PieceLRotationSet(rotationType));
		PieceType normalOPiece = new PieceType(colors[3],4,Piece.get4PieceORotationSet());
		PieceType normalSPiece = new PieceType(colors[4],4,Piece.get4PieceSRotationSet(rotationType));
		PieceType normalTPiece = new PieceType(colors[5],4,Piece.get4PieceTRotationSet(rotationType));
		PieceType normalZPiece = new PieceType(colors[6],4,Piece.get4PieceZRotationSet(rotationType));



		addNormalPieceType(normalIPiece);
		addNormalPieceType(normalJPiece);
		addNormalPieceType(normalLPiece);
		addNormalPieceType(normalOPiece);
		addNormalPieceType(normalSPiece);
		addNormalPieceType(normalTPiece);
		addNormalPieceType(normalZPiece);

		addDisallowedFirstPieceType(normalOPiece);
		addDisallowedFirstPieceType(normalSPiece);
		addDisallowedFirstPieceType(normalZPiece);


		int specialFrequency = 40;


		PieceType flashingIPiece = new PieceType(colors[0],4,Piece.get4PieceIRotationSet(rotationType),specialFrequency,0);
		PieceType flashingJPiece = new PieceType(colors[1],4,Piece.get4PieceJRotationSet(rotationType),specialFrequency,0);
		PieceType flashingLPiece = new PieceType(colors[2],4,Piece.get4PieceLRotationSet(rotationType),specialFrequency,0);
		PieceType flashingOPiece = new PieceType(colors[3],4,Piece.get4PieceORotationSet(),specialFrequency,0);
		PieceType flashingSPiece = new PieceType(colors[4],4,Piece.get4PieceSRotationSet(rotationType),specialFrequency,0);
		PieceType flashingTPiece = new PieceType(colors[5],4,Piece.get4PieceTRotationSet(rotationType),specialFrequency,0);
		PieceType flashingZPiece = new PieceType(colors[6],4,Piece.get4PieceZRotationSet(rotationType),specialFrequency,0);

		flashingIPiece.flashingSpecialType=true;
		flashingJPiece.flashingSpecialType=true;
		flashingLPiece.flashingSpecialType=true;
		flashingOPiece.flashingSpecialType=true;
		flashingSPiece.flashingSpecialType=true;
		flashingTPiece.flashingSpecialType=true;
		flashingZPiece.flashingSpecialType=true;

		flashingIPiece.clearEveryRowPieceIsOnIfAnySingleRowCleared=true;
		flashingJPiece.clearEveryRowPieceIsOnIfAnySingleRowCleared=true;
		flashingLPiece.clearEveryRowPieceIsOnIfAnySingleRowCleared=true;
		flashingOPiece.clearEveryRowPieceIsOnIfAnySingleRowCleared=true;
		flashingSPiece.clearEveryRowPieceIsOnIfAnySingleRowCleared=true;
		flashingTPiece.clearEveryRowPieceIsOnIfAnySingleRowCleared=true;
		flashingZPiece.clearEveryRowPieceIsOnIfAnySingleRowCleared=true;

		flashingIPiece.turnBackToNormalPieceAfterNPiecesLock=3;
		flashingJPiece.turnBackToNormalPieceAfterNPiecesLock=3;
		flashingLPiece.turnBackToNormalPieceAfterNPiecesLock=3;
		flashingOPiece.turnBackToNormalPieceAfterNPiecesLock=3;
		flashingSPiece.turnBackToNormalPieceAfterNPiecesLock=3;
		flashingTPiece.turnBackToNormalPieceAfterNPiecesLock=3;
		flashingZPiece.turnBackToNormalPieceAfterNPiecesLock=3;

		addNormalPieceType(flashingIPiece);
		addNormalPieceType(flashingJPiece);
		addNormalPieceType(flashingLPiece);
		addNormalPieceType(flashingOPiece);
		addNormalPieceType(flashingSPiece);
		addNormalPieceType(flashingTPiece);
		addNormalPieceType(flashingZPiece);


		PieceType pieceShooterPiece = new PieceType(BobsGame.plusShooterBlockName,BobColor.white,1,Piece.get1PieceCursorRotationSet(),0,0);
		pieceShooterPiece.flashingSpecialType = true;
		pieceShooterPiece.pieceShooterPiece = true;
		pieceShooterPiece.disappearOnceSetInGrid = true;
		//addRandomSpecialPieceType(pieceShooterPiece);

		BlockType pieceShooterPieceMakerBlock = new BlockType(BobsGame.squareName,BobsGame.plusShooterBlockName,null,BobColor.gray,specialFrequency,0);
		addNormalBlockType(pieceShooterPieceMakerBlock);
		pieceShooterPieceMakerBlock.flashingSpecialType = true;
		pieceShooterPieceMakerBlock.makePieceTypeWhenCleared = pieceShooterPiece;
		pieceShooterPieceMakerBlock.turnBackToNormalBlockAfterNPiecesLock=3;





		PieceType pieceRemovalShooterPiece = new PieceType(BobsGame.minusShooterBlockName,BobColor.darkGray,1,Piece.get1PieceCursorRotationSet(),0,0);
		pieceRemovalShooterPiece.flashingSpecialType = true;
		pieceRemovalShooterPiece.pieceRemovalShooterPiece = true;
		pieceRemovalShooterPiece.disappearOnceSetInGrid = true;
		//addRandomSpecialPieceType(pieceRemovalShooterPiece);

		BlockType pieceRemovalShooterPieceMakerBlock = new BlockType(BobsGame.squareName,BobsGame.minusShooterBlockName,null,BobColor.gray,specialFrequency,0);
		addNormalBlockType(pieceRemovalShooterPieceMakerBlock);
		pieceRemovalShooterPieceMakerBlock.flashingSpecialType = true;
		pieceRemovalShooterPieceMakerBlock.makePieceTypeWhenCleared = pieceRemovalShooterPiece;
		pieceRemovalShooterPieceMakerBlock.turnBackToNormalBlockAfterNPiecesLock=3;





		PieceType bombPiece = new PieceType(BobsGame.bombName,BobColor.darkBlue,4,Piece.get4PieceSolidRotationSet(),0,0);
		bombPiece.flashingSpecialType = true;
		bombPiece.bombPiece = true;
		bombPiece.disappearOnceSetInGrid = true;
		//addRandomSpecialPieceType(bombPiece);

		BlockType bombPieceMakerBlock = new BlockType(BobsGame.squareName,BobsGame.bombBlockName,null,BobColor.gray,specialFrequency,0);
		addNormalBlockType(bombPieceMakerBlock);
		bombPieceMakerBlock.flashingSpecialType = true;
		bombPieceMakerBlock.makePieceTypeWhenCleared = bombPiece;
		bombPieceMakerBlock.turnBackToNormalBlockAfterNPiecesLock=3;




		PieceType weightPiece = new PieceType(BobsGame.weightName,BobColor.gray,9,Piece.get9PieceSolidRotationSet(),0,0);
		weightPiece.flashingSpecialType = true;
		weightPiece.weightPiece = true;
		weightPiece.disappearOnceSetInGrid = true;
		//addRandomSpecialPieceType(weightPiece);

		BlockType weightPieceMakerBlock = new BlockType(BobsGame.squareName,BobsGame.weightBlockName,null,BobColor.gray,specialFrequency,0);
		addNormalBlockType(weightPieceMakerBlock);
		weightPieceMakerBlock.flashingSpecialType = true;
		weightPieceMakerBlock.makePieceTypeWhenCleared = weightPiece;
		weightPieceMakerBlock.turnBackToNormalBlockAfterNPiecesLock=3;



		BlockType clear4LinesBlock = new BlockType(BobsGame.squareName,BobsGame.linesBlockName,null,BobColor.gray,specialFrequency,0);
		addNormalBlockType(clear4LinesBlock);
		clear4LinesBlock.flashingSpecialType = true;
		clear4LinesBlock.clearEveryOtherLineOnGridWhenCleared = true;
		clear4LinesBlock.turnBackToNormalBlockAfterNPiecesLock=3;




		normalMusic = "tetsosumi";
		fastMusic = "";
		//deadMusic = "tetrid_death";
		//creditsMusic = "calmbeat";


		gameTypeCaptionText = "Game: Tetsosumi";
		rulesCaptionText = "Rules: Clear Lines";


		gridWidth = 10;
		gridHeight = 20;

		makeNewPiece = true;

	}



	// =========================================================================================================================
	public void cascademode()
	{// =========================================================================================================================

		//quadra
		//rensa in tetris battle gaiden
		//cascade in tetris worlds


		//cascade: whole pieces stay, break into chunks and are affected by gravity

	}



//	// =========================================================================================================================
//	public void flashpoint(Game game)
//	{// =========================================================================================================================
//		//flashpoint is just "clear the line with the glowing dot" with preset puzzles
//	}


//	// =========================================================================================================================
//	public void jewelmaster(Game game)
//	{// =========================================================================================================================
//
//
//
//	}
//
//	// =========================================================================================================================
//	public void sakuramode(Game game)
//	{// =========================================================================================================================
//
//
//
//	}
//
//
//	// =========================================================================================================================
//	public void magicaliss(Game game)
//	{// =========================================================================================================================
//
//		//super tetris 3:
//		//magicaliss: flashing piece that does ?? maybe creates stone pieces
//		//1,2,3 block stone pieces that don't go away when line clear and have weird gravity for pieces around them
//
//
//	}
//
//
//	// =========================================================================================================================
//	public void stickymode(Game game)
//	{// =========================================================================================================================
//
//		//sticky: blocks of same color stick together as one big block and behave with weird gravity, for some reason this mode has 1px drop
//
//	}
//
//	// =========================================================================================================================
//	public void fusionmode(Game game)
//	{// =========================================================================================================================
//
//		//fusion: connect 1 block "atom" pieces to 1 block "fusion" piece in corner, atom pieces dont go away with lines, but sometimes blow up when hard drop?
//
//
//	}
//
//
//	// =========================================================================================================================
//	public void tetsosumiflash(Game game)
//	{// =========================================================================================================================
//
//		//NES/SNES tetris 2U: tetris flash, tetris pieces, plus some additional pieces, lines dont clear, instead match 3 or more colors, kinda dr mario + tetris hybrid.
//		//have to blow up bombs at the end
//		//some pieces can break off and are maneuverable after
//		//blowing up some bombs blows up other bombs of the same color, not sure why
//		//there is some collapse gravity on some pieces?
//	}
//
//
//	// =========================================================================================================================
//	public void bombliss(Game game)
//	{// =========================================================================================================================
//
//		//TODO://bombliss: line clear does nothing, must have bomb in line.
//		//amount of lines cleared with bombs makes explosion bigger, big explosions blow up bombs within reach, blow up big bomb at bottom finishes level
//		//combine 4 bombs into square bomb with big explosion
//
//		//super tetris 3
//		//sparkliss: exactly like bombliss but horizontal and vertical "bomberman" type explosions, sort of easier than bombliss
//
//	}



	// =========================================================================================================================
	public void mrbob()
	{// =========================================================================================================================







		//TODO: fix color swap extra mode stuff

		//DONE: slower combo fall
		//TODO: play lots of nes/snes/gba/gamecube/dsi/wii and take measurements


		//TODO: rule: don't get color that doesn't exist on screen.


		scoreType = ScoreType.BLOCKS_CLEARED;
		scoreTypeAmountPerLevelGained = 20;


		chainRule_AmountPerChain = 4;
		chainRule_CheckRowOrColumn = true;

		blockRule_drawBlocksConnectedByColorIgnoringPiece = false;
		blockRule_drawBlocksConnectedByPieceIgnoringColor = true;
		blockRule_drawBlocksConnectedByColorInPiece = false;

		gravityRule_ticksToMoveDownBlocksOverBlankSpaces = 150;
		gravityRule_onlyMoveDownDisconnectedBlocks = true;

		blockAnimationTicksRandomUpToBetweenLoop = 5000;


		//no gravity on viruses
		//garbage is randomly spaced out
		//garbage can be same color next to each other
		//garbage does not count towards lines by itself (i.e. 4 red viruses in a row need at least 1 pill)





		int i = 2;
		if(difficulty==Difficulty.EASY)i = 2;
		else
		if(difficulty==Difficulty.NORMAL)i = 3;//0-5
		else
		i = 4;

		//TODO: what are the real colors?
		BobColor[] maxColors = new BobColor[]{BobColor.blue,BobColor.red,BobColor.yellow,BobColor.green};
		maxColors = new BobColor[]{BobColor.cyan,BobColor.magenta,BobColor.green,BobColor.purple,BobColor.pink,BobColor.blue};

		if(i>maxColors.length)i=maxColors.length;

		BobColor[] colors = new BobColor[i];
		for(int c=0;c<i;c++)
		{
			colors[c] = maxColors[c];
		}





		BlockType circleWithColors = new BlockType(BobsGame.circleName,colors);
		addNormalBlockType(circleWithColors);


		BlockType virusBlockWithColors = new BlockType(BobsGame.virusName,colors);
		addPlayingFieldBlockType(virusBlockWithColors);


		BlockType roundedSquareWithColors = new BlockType(BobsGame.roundedSquareOutlineName,colors);
		addGarbageBlockType(roundedSquareWithColors);


		virusBlockWithColors.ignoreWhenMovingDownBlocks = true;
		circleWithColors.chainConnectionsMustContainAtLeastOneBlockWithThisTrue = true;
		roundedSquareWithColors.chainConnectionsMustContainAtLeastOneBlockWithThisTrue = true;



		PieceType drBobPiece = new PieceType(2,Piece.get2PieceBottomLeftAlwaysFilledRotationSet());
		addNormalPieceType(drBobPiece);









		normalMusic = "drbob";
		fastMusic = "";
		deadMusic = "tetrid_death";
		creditsMusic = "calmbeat";


		gameTypeCaptionText = "Game: DrBob";
		rulesCaptionText = "Rules: 4 In A Row Or Column";





		gridWidth = 8;
		gridHeight = 16;


		makeNewPiece = true;
		randomlyFillGrid = true;
		randomlyFillGridAmount=60;
		randomlyFillGridStartY = 4;

	}






	// =========================================================================================================================
	public void boblob()
	{// =========================================================================================================================




		//3 colors = easy
		//4 colors = normal
		//5 colors = hard
		//harder: (start with 2 rows of garbage)

		//180 flip wallkick when in blank column blocked by both sides

		//clear pieces as vs garbage, attach to any 4-connection but only one-deep
		//drop down half a tile at a time

		//glowing 0,0 piece
		//set lock delay
		//points for soft drop
		//garbage to opponent for combo

		//bounce animations
		//field shake on garbage fall

		//blob idle animations
		//blob lose expression
		//blob explode expression
		//explode into goo

		//puyo puyo 2 (tsu)
		//Sousai (Garbage Countering)
		//Zenkeshi (All Clear)
		//If you send a chain after this has happened, it is worth the single chain amount plus 30 garbage
		//two new garbage types also appeared, known as Point Puyos and Hard Puyos.


		//fever:
		//1px scrolling
		//2-4px balls for ghost
		//flashing hint for color match
		//2x2 blob doesn't smash
		//matching colors in piece comes out as one big piece
		//3 blob piece, 2x1 and 1
		//get fever if get ALL CLEAR
		//fever mode gives you some preset combo chains, which you can immediately set off (if you know the right place) or can build on for more

		//look at puyo 7, fever 2 ps2

		scoreType = ScoreType.BLOCKS_CLEARED;
		scoreTypeAmountPerLevelGained = 20;

		chainRule_AmountPerChain = 4;
		chainRule_CheckRecursiveConnections = true;

		gridRule_showWarningForFieldThreeQuartersFilled = true;

		blockRule_drawBlocksConnectedByColorIgnoringPiece = true;
		blockRule_drawBlocksConnectedByPieceIgnoringColor = false;
		blockRule_drawBlocksConnectedByColorInPiece = false;

		currentPieceRule_OutlineBlockAtZeroZero=true;

		gravityRule_ticksToMoveDownBlocksOverBlankSpaces = 50;

		stackDontPutSameColorNextToEachOther = true;

		garbageSpawnRule = GarbageSpawnRule.PIECES_MADE;
		garbageSpawnRuleAmount = 5;

		int i = 3;
		if(difficulty==Difficulty.EASY)i = 3;
		else
		if(difficulty==Difficulty.NORMAL)i = 4;//0-5
		else
		i = 5;

		//TODO: what are the real colors?
		BobColor[] maxColors = new BobColor[]{BobColor.green,BobColor.magenta,BobColor.cyan,BobColor.purple};
		maxColors = new BobColor[]{BobColor.cyan,BobColor.magenta,BobColor.green,BobColor.purple,BobColor.blue,BobColor.pink};

		if(i>maxColors.length)i=maxColors.length;

		BobColor[] colors = new BobColor[i];
		for(int c=0;c<i;c++)
		{
			colors[c] = maxColors[c];
		}




		BlockType blobWithColors = new BlockType(BobsGame.blobName,colors);
		addNormalBlockType(blobWithColors);




		BlockType grayBlob = new BlockType(BobsGame.blobName,null,BobColor.gray);
		grayBlob.addToChainIfConnectedUpDownLeftRightToExplodingChainBlocks=true;
		grayBlob.ignoreWhenCheckingChainConnections = true;

		//Hard Puyos, when they land on the field, are harder to erase than Standard Garbage or Point Puyos, and are often referred to as Steelies
		// Once they're erased a first time, the square shell disappears, leaving a standard ojama left to erase.
		//Because they are in the shape of a square, if you have one or two groups of puyos that touch two or more of the sides of a Hard Puyo, then it will completely disappear, leaving nothing as a result.
		BlockType steelie = new BlockType(BobsGame.squareGemName,null,BobColor.darkerGray,2,0);
		steelie.ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType = grayBlob;
		steelie.ignoreWhenCheckingChainConnections = true;

		addPlayingFieldBlockType(blobWithColors);
		addPlayingFieldBlockType(grayBlob);
		addPlayingFieldBlockType(steelie);

		addGarbageBlockType(grayBlob);
		addGarbageBlockType(steelie);




		//giant blob 2x2 smashes everything underneath
		PieceType weightPiece = new PieceType(BobsGame.blobName,BobColor.gray,4,Piece.get4PieceSolidRotationSet(),15,0);
		weightPiece.flashingSpecialType = true;
		weightPiece.weightPiece = true;
		weightPiece.disappearOnceSetInGrid = true;
		weightPiece.overrideBlockType = new BlockType();
		addNormalPieceType(weightPiece);


		PieceType blobPiece = new PieceType(2,Piece.get2PieceRotateAround00RotationSet());
		addNormalPieceType(blobPiece);




		PieceType threeBlobPiece = new PieceType(null,3,Piece.get3PieceCRotationSet(),15,0);
		PieceType fourBlobPiece = new PieceType(null,4,Piece.get4PieceORotationSet(),15,0);
		addNormalPieceType(threeBlobPiece);
		addNormalPieceType(fourBlobPiece);



		//TODO: //little mouse thing that follows a color randomly and turns all pieces in path to that color
		BlockType pacmanBlock = new BlockType(BobsGame.pacBallName,null,BobColor.yellow);
		pacmanBlock.pacmanType = true;
		PieceType pacmanPiece = new PieceType(null,1,Piece.get1PieceCursorRotationSet(),10,0);//force pacman piece to only be in single block pieces
		pacmanPiece.overrideBlockType = pacmanBlock;
		addNormalPieceType(pacmanPiece);

		//Point Puyos: Like standard ojama's, they are erased once a neighbouring group erases adjacently with them, and add 50 points for each one erased to the chains score.
		//This in theory, can also float the amount of garbage being sent with one chain, though when many are erased, can do more damage.





		normalMusic = "puyo";
		fastMusic = "";
		deadMusic = "tetrid_death";
		creditsMusic = "calmbeat";


		gameTypeCaptionText = "Game: Blob";
		rulesCaptionText = "Rules: 4 Connected";




		gridWidth = 6;
		gridHeight = 12;

		makeNewPiece = true;


	}





	// =========================================================================================================================
	public void jewels()
	{// =========================================================================================================================






		//TODO:
		//need hint for matches
		//need to check 2p for garbage, points, combos, etc.


		//gen version is 6x13 visible, piece starts offscreen above
		//gg version is 6x18, top 3 rows get filled by new piece, but can move left/right




		//TODO: sparkling jewel piece, what does it do?
		//columns 1 has triple flashing piece that removes all colors of what it lands on
		//TODO: find out if single flashing piece here
		//TODO: find out if it only removes the color it lands on or all the colors it touches
		//columns 1 slows down when you get near the top sometimes?
		//also next piece seems to change randomly into a different piece, why?

		//TODO: look at columns 2


		//columns 3 has flashing gem of whatever color that if you use to make a chain turns the opponents playing field all gray
		//also getting a combo or chain breaks the opponents piece, is annoying
		//the floor appears to rise and your piece "breaks" when this happens but i'm not sure what causes it
		//also some triple flashing diamond piece that i couldnt figure out what it does


		//TODO: turn piece sideways!
		//TODO: super columns gg can turn piece sideways and still shuffle colors
		//also has occasional "flame piece" which 3 flame pieces in a row creates flame that destroys horizontal/vertical/diagonal depending on clear



		//in the gba version there is a kind of "drilling" you can do during lock delay and it detects the matches while you rotate, making random "drilling" effective
		//gba version slows down when you get near the top
		//gba version has a weird sun piece, probably the same as the jewel piece
		//TODO: sun piece, what does it do?

		scoreType = ScoreType.BLOCKS_CLEARED;
		scoreTypeAmountPerLevelGained = 20;

		chainRule_AmountPerChain = 3;
		chainRule_CheckRowOrColumn = true;
		chainRule_CheckDiagonal = true;

		gridRule_showWarningForFieldThreeQuartersFilled = true;

		blockRule_drawBlocksConnectedByColorIgnoringPiece = false;
		blockRule_drawBlocksConnectedByPieceIgnoringColor = false;
		blockRule_drawBlocksConnectedByColorInPiece = false;

		currentPieceOutlineFirstBlockRegardlessOfPosition=true;

		gravityRule_ticksToMoveDownBlocksOverBlankSpaces = 50;


		stackDontPutSameColorDiagonalOrNextToEachOtherReturnNull = true;

		whenGeneratingPieceDontMatchAllBlockColors = true;





		blockAnimationTicksRandomUpToBetweenLoop = 5000;



		int i = 4;
		if(difficulty==Difficulty.EASY)i = 4;
		else
		if(difficulty==Difficulty.NORMAL)i = 5;//0-6
		else
		i = 6;

		BobColor[] maxColors = new BobColor[]{BobColor.darkGreen,BobColor.blue,BobColor.yellow,BobColor.purple,BobColor.orange,BobColor.red};
		maxColors = new BobColor[]{BobColor.cyan,BobColor.magenta,BobColor.green,BobColor.purple,BobColor.orange,BobColor.blue};

		if(i>maxColors.length)i=maxColors.length;

		BobColor[] colors = new BobColor[i];
		for(int c=0;c<i;c++)
		{
			colors[c] = maxColors[c];
		}



		BlockType gemWithColors = new BlockType(BobsGame.squareGemName,colors);
		addNormalBlockType(gemWithColors);


		BlockType flashingBlock = new BlockType(BobsGame.diamondGemName,null,BobColor.gray,30,0);
		flashingBlock.flashingSpecialType = true;
		flashingBlock.matchAnyColor = true;
		addNormalBlockType(flashingBlock);//sometimes we have single flashing gems

		addPlayingFieldBlockType(gemWithColors);
		addGarbageBlockType(gemWithColors);




		PieceType columnsPiece = new PieceType(3,Piece.get3PieceVerticalRotationSet());
		addNormalPieceType(columnsPiece);



		//sometimes we have entire flashing pieces
		PieceType flashingPiece = new PieceType(null,3,Piece.get3PieceVerticalRotationSet(),50,0);
		flashingPiece.overrideBlockType = flashingBlock;
		addNormalPieceType(flashingPiece);







		normalMusic = "columns";
		fastMusic = "";
		deadMusic = "tetrid_death";
		creditsMusic = "calmbeat";



		gameTypeCaptionText = "Game: Jewel";
		rulesCaptionText = "Rules: 3 In A Row, Column, Or Diagonal";


		gridWidth = 6;
		gridHeight = 15;
		gridPixelsBetweenRows = 1;
		gridPixelsBetweenColumns = 1;


		makeNewPiece = true;



	}





	// =========================================================================================================================
	public void pop()
	{// =========================================================================================================================






		//vs garbage types:
		//SNES



		//normal: 2 6 wide rows of blue fall straight down
		//one 5 tall column of yellow with one green in the center falls in second slot from left, one 5 tall column of blue with one yellow in center falls from left to middle
		//one 6 wide row of blue and one 6 wide row of red fall straight down
		//2 6 wide rows of 4 colors cycling per column fall straight down
		//one 5 tall column of blue on left, one column of yellow on right, fall inward?
		//one 5 tall column of yellow fall on left to middle, one column of red fall in middle to right
		//4 rows of alternating colors fall on right side of field
		//one blue block falls from left to middle, one yellow falls from right to middle, two rows of alternating colors per column push from below
		//one green column on right, one green column from middle to left
		//two yellow blocks fall from upper left to right, two rows of yellow push from below

		//difficulty appears to increase amount of colors in some modes
		//4 normal - blue green red yellow
		//5 hard - magenta
		//6 very hard - gray, selectable in options

		//***Note, this doesn't appear to be an option anymore in the n64 one
		//n64 does have "hard mode" with magenta blobs but ONLY for dama-swap, not for normal dama, weird.




		//N64

		//evil-type black blob which makes 3x3 square around it into boxes
		//happy white blob which unboxes 3x3 grid around it
		//pink pacman-type box which eats everything in a direction when unboxed, only if there are blobs in front of it

		//n64 also has a completely different mode like tetris attack, snes version doesn't have this
		//**also has bowling for some reason

		//n64 attacks:
		//drop a stack that grows blue and red from lower left to upper right
		//drop a stack that grows all 4 colors from lower left to upper right
		//drop a stack that grows 3 colors from lower right to upper left
		//drop a stack 1 color per row, 3 tall in the corners and 1 in the middle
		//drop column of all colors on the right, and a column from middle to left
		//drop a stack, 1 tall in corners, 3 tall in middle, cycle colors per column
		//raise a stack of all colors first row, all red next row
		//drop 1 row of all colors, raise 1 row of all red
		//drop row of all colors, raise 2 rows of all colors
		//drop 3 rows cycle colors per column, first 3 rows 3 tall, rest 1 tall all red





		//TODO: check dama arcade versions, tokimeki memorial, popn dama
		//TODO: get timing and score right


		//n64 version appears to be identical to susume arcade version, no swap game()
		//ps1 tokimeki is like a slightly worse version of n64, no swap game(), uglier pieces

		scoreType = ScoreType.BLOCKS_CLEARED;
		scoreTypeAmountPerLevelGained = 20;

		chainRule_AmountPerChain = 3;
		chainRule_CheckRecursiveConnections = true;



		gridRule_showWarningForFieldThreeQuartersFilled = true;


		blockRule_drawBlocksConnectedByColorIgnoringPiece = false;
		blockRule_drawBlocksConnectedByPieceIgnoringColor = false;
		blockRule_drawBlocksConnectedByColorInPiece = false;

		currentPieceRule_OutlineBlockAtZeroZero = true;

		gravityRule_ticksToMoveDownBlocksOverBlankSpaces = 50;

		stackDontPutSameColorNextToEachOther = true;


		int i = 3;
		if(difficulty==Difficulty.EASY)i = 3;
		else
		if(difficulty==Difficulty.NORMAL)i = 4;//0-6
		else
		i = 5;

		BobColor[] maxColors = new BobColor[]{BobColor.green,BobColor.blue,BobColor.red,BobColor.yellow,BobColor.purple,BobColor.gray};
		maxColors = new BobColor[]{BobColor.cyan,BobColor.magenta,BobColor.green,BobColor.purple,BobColor.blue,BobColor.orange};

		if(i>maxColors.length)i=maxColors.length;

		BobColor[] colors = new BobColor[i];
		for(int c=0;c<i;c++)
		{
			colors[c] = maxColors[c];
		}




		BlockType normalBlock = new BlockType(BobsGame.circleName,colors);
		addNormalBlockType(normalBlock);

		BlockType boxBlock = new BlockType(BobsGame.ballJarName,colors,2,0);
		boxBlock.ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType = normalBlock;
		boxBlock.ignoreWhenCheckingChainConnections = true;
		addNormalBlockType(boxBlock);



		BlockType pacmanJarBlock = new BlockType(BobsGame.pacjarName,null,BobColor.pink,20,0);
		BlockType pacmanBlock = new BlockType(BobsGame.pacBallName,null,BobColor.pink);
		pacmanBlock.pacmanType = true;
		pacmanJarBlock.ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType = pacmanBlock;
		pacmanJarBlock.ignoreWhenCheckingChainConnections = true;
		pacmanJarBlock.flashingSpecialType = true;
		addNormalBlockType(pacmanJarBlock);


		BlockType whiteBlock = new BlockType(BobsGame.happyBallName,null,BobColor.gray,20,0);
		whiteBlock.whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndDisappear.add(new TurnFromBlockTypeToType(boxBlock,normalBlock));
		whiteBlock.whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndDisappear.add(new TurnFromBlockTypeToType(pacmanJarBlock,pacmanBlock));
		whiteBlock.flashingSpecialType = true;
		addNormalBlockType(whiteBlock);


		BlockType blackBlock = new BlockType(BobsGame.angryBallName,null,BobColor.black,20,0);
		blackBlock.whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndDisappear.add(new TurnFromBlockTypeToType(normalBlock,boxBlock));

		blackBlock.flashingSpecialType = true;
		addNormalBlockType(blackBlock);





		//TODO: figure out exact ratio of normal to box pieces
		//TODO: also handle white, black, pacman pieces, but NOT for dama swap




		addPlayingFieldBlockType(normalBlock);
		addPlayingFieldBlockType(boxBlock);


		addGarbageBlockType(boxBlock);












		PieceType damaPiece = new PieceType(2,Piece.get2PieceRotateAround00RotationSet());
		addNormalPieceType(damaPiece);







		normalMusic = "dama";
		fastMusic = "";
		deadMusic = "tetrid_death";
		creditsMusic = "calmbeat";


		gameTypeCaptionText = "Game: Dama";
		rulesCaptionText = "Rules: 3 Connected";


		//SNES: 6x12
		gridWidth = 6;
		gridHeight = 13;
		//**6x13 tall in n64


		makeNewPiece = true;
	}





	// =========================================================================================================================
	public void popswap()
	{// =========================================================================================================================



		bloomIntensity = 1.5f;
		bloomTimes = 10;


		//TODO: "stop" behavior is a bit different from panel, there is always gravity

		//this only exists in n64 version, check arcade and ps1/2 versions


		scoreType = ScoreType.BLOCKS_CLEARED;
		scoreTypeAmountPerLevelGained = 20;


		chainRule_AmountPerChain = 3;
		chainRule_CheckRecursiveConnections = true;

		removingBlocksDelayTicksBetweenEachBlock = 300;


		blockRule_drawBlocksConnectedByColorIgnoringPiece = false;
		blockRule_drawBlocksConnectedByPieceIgnoringColor = false;
		blockRule_drawBlocksConnectedByColorInPiece = false;

		currentPieceRenderAsNormalPiece = false;
		currentPieceRenderHoldingBlock = true;
		currentPieceOutlineAllPieces = true;
		currentPieceMoveUpHalfABlock=true;


		gravityRule_ticksToMoveDownBlocksOverBlankSpaces = 50;

		blockMovementInterpolationTicks = 200;

		stackDontPutSameColorNextToEachOther = true;


		//difficulty increases amount of colors only in swap for n64, not in normal dama
		//4 normal - blue green red yellow
		//5 hard - magenta

		int i = 3;
		if(difficulty==Difficulty.EASY)i = 3;
		else
		if(difficulty==Difficulty.NORMAL)i = 4;//0-5
		else
		i = 5;

		BobColor[] maxColors = new BobColor[]{BobColor.green,BobColor.blue,BobColor.red,BobColor.yellow,BobColor.magenta};
		maxColors = new BobColor[]{BobColor.cyan,BobColor.magenta,BobColor.green,BobColor.purple,BobColor.blue,BobColor.orange};

		if(i>maxColors.length)i=maxColors.length;

		BobColor[] colors = new BobColor[i];
		for(int c=0;c<i;c++)
		{
			colors[c] = maxColors[c];
		}






		BlockType normalBlock = new BlockType(BobsGame.circleName,colors);
		BlockType boxBlock = new BlockType(BobsGame.ballJarName,colors,2,0);

		addPlayingFieldBlockType(normalBlock);
		addPlayingFieldBlockType(boxBlock);



		addGarbageBlockType(boxBlock);


		boxBlock.ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType = normalBlock;
		boxBlock.ignoreWhenCheckingChainConnections = true;


		//PieceType damaPiece = new PieceType("DAMA",1,0);
		//addNormalPieceType(damaPiece);


		//PieceType normalPlayingFieldPiece = new PieceType();//will take blocks from presetFieldBlocks
		//addPlayingFieldPieceType(normalPlayingFieldPiece);







		repeatDelayA = 100;
		repeatDelayB = 100;
		repeatDelayR = 100;
		repeatDelayUp = 50;
		repeatDelayDown = 50;
		repeatDelayLeft = 50;
		repeatDelayRight = 50;


		repeatEnabledA = false;
		repeatEnabledB = false;
		repeatEnabledR = false;
		repeatEnabledUp = true;
		repeatEnabledDown = true;
		repeatEnabledLeft = true;
		repeatEnabledRight = true;


		repeatStartDelayA = 150;
		repeatStartDelayB = 150;
		repeatStartDelayR = 150;
		repeatStartDelayUp = 150;
		repeatStartDelayDown = 150;
		repeatStartDelayLeft = 150;
		repeatStartDelayRight = 150;






		flashBlockSpeedTicks = 17;
		timesToFlashBlocks = 28;




		normalMusic = "damaswap";
		fastMusic = "";
		deadMusic = "tetrid_death";
		creditsMusic = "calmbeat";


		gameTypeCaptionText = "Game: DamaSwap";
		rulesCaptionText = "Rules: 3 Connected";



		gridWidth = 6;
		gridHeight = 13+2;
		//**6x13 tall in n64, 2 for overlap and hidden
		gridPixelsBetweenRows = 1;
		gridPixelsBetweenColumns = 1;


		//level 1 easy = 1 pixel every 60 frames
		//level 99 easy = 3,3,3,2
		//stop 1 frame when new row becomes opaque
		//stackRiseSpeed=300;
		stackRiseGame = true;
		useCurrentPieceAsCursor=true;
		randomlyFillStack = true;
		randomlyFillStackAmount = 30;
		randomlyFillStackStartY = 7;


		makeCursorPiece = true;
		cursorPieceSize = 1;

	}





	// =========================================================================================================================
	public void panelswap()
	{// =========================================================================================================================


		bloomIntensity = 1.1f;
		bloomTimes = 10;


		//TODO: check n64, gba, gamecube, DS versions

		//TODO: check gravity behavior when stopped. not sure if swapped blocks fall or not, i think they do

		//6x12, scrolls up 1px, 13 can be visible
		//start with 30 pieces, 6 tall
		//cursor starts at 2,6
		//5 colors easy - cyan triangle, yellow star, red heart, green circle, purple diamond
		//6 colors hard - blue upside down triangle





		//DONE:stack doesn't rise during swap

		//TODO:
		//blocks do continue animating

		//from A pressed:
		//normal
		//in between
		//middle
		//in between
		//swapped
		//immediately flash white
		//14 flash on/off cycles
		//then surprise face for 15 frames
		//top block pops
		//shell animation 8 frames
		//on 8th frame next block pops, any blocks above fall 1 block per frame
		//as soon as last block pops stack continues rising
		//shell animation continues, 26 frames total


		//drop 4:
		//drop down 1 pixel
		//drop down entire block
		//one frame squish animation
		//white, speed becomes stop immediately
		//second frame of flash (normal color) puts [4] on top block
		//[4] moves up 1 pixel for 4 frames
		//eggs start circling in
		//[4] moves up 1 pixel every 2 frames
		//[4] disappears frame before pop, so all flash frames + 15 surprise face frames
		//from last block pop

		//combo puts [2x] on upper left block, same as [4], STOP now says 2 STOP
		//egg animation has one big egg going from corner to corner for each block exploding
		//each STOP is one second


		//DONE: can't swap blocks that are swapping
		//TODO: can't grab blocks in mid-fall (check this on emu)

		//TODO: can't swap blocks that are flashing!

		//TODO: figure out combo system and point system.
		//TODO: figure out garbage system.


		scoreType = ScoreType.BLOCKS_CLEARED;
		scoreTypeAmountPerLevelGained = 20;


		chainRule_AmountPerChain = 3;
		chainRule_CheckRowOrColumn = true;

		removingBlocksDelayTicksBetweenEachBlock = 300;


		blockRule_drawBlocksConnectedByColorIgnoringPiece = false;
		blockRule_drawBlocksConnectedByPieceIgnoringColor = false;
		blockRule_drawBlocksConnectedByColorInPiece = false;

		currentPieceRenderAsNormalPiece = false;
		currentPieceOutlineAllPieces = true;

		gravityRule_ticksToMoveDownBlocksOverBlankSpaces = 50;

		blockMovementInterpolationTicks = 200;

		stackDontPutSameBlockTypeNextToEachOther = true;




		int i = 5;
		if(difficulty==Difficulty.EASY)i = 5;
		else
		if(difficulty==Difficulty.NORMAL)i = 6;//0-7
		else
		i = 7;

		//TODO: 7 colors orange, is this in a real game() or did i make it up?

		BobColor[] maxColors = new BobColor[]{BobColor.green,BobColor.purple, BobColor.red, BobColor.cyan, BobColor.yellow, BobColor.blue, BobColor.orange};
		maxColors = new BobColor[]{BobColor.cyan,BobColor.magenta,BobColor.green,BobColor.purple,BobColor.blue,BobColor.orange, BobColor.yellow};

		if(i>maxColors.length)i=maxColors.length;

		BobColor[] colors = new BobColor[i];
		for(int c=0;c<i;c++)
		{
			colors[c] = maxColors[c];
		}



		//TODO: handle GRAY EXCLAMATION POINT pieces, figure out exact ratio of this
		//breaking them with a combo will add a garbage row to other player

		//Piece.addRandomSpecialBlockType(blockType,randomSpecialBlockChanceOneOutOf)

		//Piece.normalBlockType = BlockType.PANELPUZZLEATTACK;
		//Piece.presetFieldGarbageBlockType = BlockType.PANELPUZZLEATTACK;

		//gravity on preset garbage
		//do not put same colors next to each other more than twice
		//no spaces between rows, but spaces between columns is ok above a certain line to give some room for movement

		//addNormalPieceType(PieceTypes.PANELPUZZLE,1,0);






		BlockType circleIcon 				= new BlockType(BobsGame.circleIconBlockName,null,				colors[0]);
		BlockType diamondIcon 				= new BlockType(BobsGame.diamondIconBlockName,null,				colors[1]);
		BlockType heartIcon 				= new BlockType(BobsGame.heartIconBlockName,null,				colors[2]);
		BlockType triangleIcon 			= new BlockType(BobsGame.triangleIconBlockName,null,				colors[3]);
		BlockType starIcon 				= new BlockType(BobsGame.starIconBlockName,null,					colors[4]);
		BlockType upsideDownTriangleIcon 	= new BlockType(BobsGame.upsideDownTriangleIconBlockName,null,	colors[5]);


		addNormalBlockType(circleIcon);
		addNormalBlockType(diamondIcon);
		addNormalBlockType(heartIcon);
		addNormalBlockType(triangleIcon);
		addNormalBlockType(starIcon);

		//if(hardMode)
		addNormalBlockType(upsideDownTriangleIcon);





		addPlayingFieldBlockType(circleIcon);
		addPlayingFieldBlockType(diamondIcon);
		addPlayingFieldBlockType(heartIcon);
		addPlayingFieldBlockType(triangleIcon);
		addPlayingFieldBlockType(starIcon);


		//if(hardMode)
		addPlayingFieldBlockType(upsideDownTriangleIcon);




		//addGarbageBlockType(boxBlock);//TODO: giant gray blob


		//BlockClass exclamationBlock = new BlockClass("normal",exclamationIconBlock,BobColor.gray);//TODO figure out when this happens
		//addRandomSpecialBlockType(exclamationBlock);



		//PieceType normalPlayingFieldPiece = new PieceType();//will take blocks from presetFieldBlocks
		//addPlayingFieldPieceType(normalPlayingFieldPiece);










		repeatDelayA = 100;
		repeatDelayB = 100;
		repeatDelayR = 100;
		repeatDelayUp = 50;
		repeatDelayDown = 50;
		repeatDelayLeft = 50;
		repeatDelayRight = 50;


		repeatEnabledA = false;
		repeatEnabledB = false;
		repeatEnabledR = false;
		repeatEnabledUp = true;
		repeatEnabledDown = true;
		repeatEnabledLeft = true;
		repeatEnabledRight = true;


		repeatStartDelayA = 150;
		repeatStartDelayB = 150;
		repeatStartDelayR = 150;
		repeatStartDelayUp = 150;
		repeatStartDelayDown = 150;
		repeatStartDelayLeft = 150;
		repeatStartDelayRight = 150;


		flashBlockSpeedTicks = 17;
		timesToFlashBlocks = 28;




		normalMusic = "panel";
		fastMusic = "";
		deadMusic = "tetrid_death";
		creditsMusic = "calmbeat";


		gameTypeCaptionText = "Game: Panel";
		rulesCaptionText = "Rules: 3 In A Row Or Column";



		gridWidth = 6;
		gridHeight = 12+2;
		//6x12 + 2 for overlap and hidden
		gridPixelsBetweenRows = 1;
		gridPixelsBetweenColumns = 1;



		//level 1 easy = 1 pixel every 60 frames
		//level 99 easy = 3,3,3,2
		//stop 1 frame when new row becomes opaque
		//stackRiseSpeed=300;
		stackRiseGame = true;
		useCurrentPieceAsCursor=true;
		randomlyFillStack = true;
		randomlyFillStackAmount = 30;
		randomlyFillStackStartY = 5;
		makeCursorPiece = true;
		cursorPieceSize = 2;
	}





	// =========================================================================================================================
	public void gemfight()
	{// =========================================================================================================================






		//in dreamcast and PSP version:
		//psp version works a little bit better





		scoreType = ScoreType.BLOCKS_CLEARED;
		scoreTypeAmountPerLevelGained = 20;


		chainRule_CheckTouchingBreakerBlocksChain = true;



		gridRule_showWarningForFieldThreeQuartersFilled = true;


		blockRule_drawBlocksConnectedByColorIgnoringPiece = false;
		blockRule_drawBlocksConnectedByPieceIgnoringColor = false;
		blockRule_drawBlocksConnectedByColorInPiece = false;

		currentPieceRule_OutlineBlockAtZeroZero=true;

		gravityRule_ticksToMoveDownBlocksOverBlankSpaces = 50;

		stackDontPutSameColorNextToEachOther = true;


		whenGeneratingPieceDontMatchNormalBlockWithBlockOfDifferentTypeAndSameColor = true;
		whenGeneratingPieceDontMatchTwoBlocksOfTheSameSpecialRandomTypeAndColor = true;







		int i = 4;
		if(difficulty==Difficulty.EASY)i = 4;
		else
		if(difficulty==Difficulty.NORMAL)i = 5;//0-6
		else
		i = 6;

		BobColor[] maxColors = new BobColor[]{BobColor.green,BobColor.blue,BobColor.red,BobColor.yellow};
		maxColors = new BobColor[]{BobColor.cyan,BobColor.magenta,BobColor.green,BobColor.purple,BobColor.blue,BobColor.orange, BobColor.yellow};

		if(i>maxColors.length)i=maxColors.length;

		BobColor[] colors = new BobColor[i];
		for(int c=0;c<i;c++)
		{
			colors[c] = maxColors[c];
		}




		BlockType normalBlock = new BlockType(BobsGame.squareGemName,colors);
		addNormalBlockType(normalBlock);

		BlockType crashGemBlock = new BlockType(BobsGame.sparkBallName,colors,3,0);
		addNormalBlockType(crashGemBlock);

		//diamond clears all blocks of the color it touches
		BlockType diamondGemBlock = new BlockType(BobsGame.diamondGemName,null,BobColor.gray,0,25);
		diamondGemBlock.removeAllBlocksOfColorOnFieldBlockIsSetOn = true;
		diamondGemBlock.flashingSpecialType = true;
		addNormalBlockType(diamondGemBlock);

		// if meter is full, get colored diamond that changes everything it touches to color
		BlockType coloredDiamondGemBlock = new BlockType(BobsGame.diamondGemName,colors,0,25);
		coloredDiamondGemBlock.changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor = true;
		coloredDiamondGemBlock.flashingSpecialType = true;
		addNormalBlockType(coloredDiamondGemBlock);

		BlockType counterGemBlock = new BlockType(BobsGame.counterName,colors);
		counterGemBlock.counterType=true;

		addPlayingFieldBlockType(counterGemBlock);
		addGarbageBlockType(counterGemBlock);






		crashGemBlock.chainConnectionsMustContainAtLeastOneBlockWithThisTrue = true;
		counterGemBlock.ignoreWhenCheckingChainConnections = true;




		PieceType fighterPiece = new PieceType(2,Piece.get2PieceRotateAround00RotationSet());
		addNormalPieceType(fighterPiece);





		normalMusic = "puzzlefight";
		fastMusic = "";
		deadMusic = "tetrid_death";
		creditsMusic = "calmbeat";


		gameTypeCaptionText = "Game: Puzzle Fight";
		rulesCaptionText = "Rules: Breaker Block";


		//6x13
		gridWidth = 6;
		gridHeight = 13;




		makeNewPiece = true;
	}





	// =========================================================================================================================
	public void gemfight_columns()
	{// =========================================================================================================================






		//DONE: type y is like columns, except with 2 blocks as normal puzzle fighter, 3 in a row or diagonal, no breaker blocks needed
		//DONE: no diamonds

		//DONE: fill grid with counter pieces garbage in a pattern


		scoreType = ScoreType.BLOCKS_CLEARED;
		scoreTypeAmountPerLevelGained = 20;


		chainRule_AmountPerChain = 3;
		chainRule_CheckRowOrColumn = true;
		chainRule_CheckDiagonal = true;



		gridRule_showWarningForFieldThreeQuartersFilled = true;


		blockRule_drawBlocksConnectedByColorIgnoringPiece = false;
		blockRule_drawBlocksConnectedByPieceIgnoringColor = false;
		blockRule_drawBlocksConnectedByColorInPiece = false;

		currentPieceRule_OutlineBlockAtZeroZero=true;

		gravityRule_ticksToMoveDownBlocksOverBlankSpaces = 50;

		stackDontPutSameColorNextToEachOther = false;





		int i = 4;
		if(difficulty==Difficulty.EASY)i = 4;
		else
		if(difficulty==Difficulty.NORMAL)i = 5;//0-6
		else
		i = 6;

		BobColor[] maxColors = new BobColor[]{BobColor.green,BobColor.blue,BobColor.red,BobColor.yellow};
		maxColors = new BobColor[]{BobColor.cyan,BobColor.magenta,BobColor.green,BobColor.purple,BobColor.blue,BobColor.orange, BobColor.yellow};

		if(i>maxColors.length)i=maxColors.length;

		BobColor[] colors = new BobColor[i];
		for(int c=0;c<i;c++)
		{
			colors[c] = maxColors[c];
		}


		BlockType normalBlock = new BlockType(BobsGame.squareGemName,colors);
		addNormalBlockType(normalBlock);



		BlockType counterGemBlock = new BlockType(BobsGame.counterName,colors);
		counterGemBlock.counterType=true;

		addPlayingFieldBlockType(counterGemBlock);
		addGarbageBlockType(counterGemBlock);

		counterGemBlock.ignoreWhenCheckingChainConnections = true;


		PieceType fighterPiece = new PieceType(2,Piece.get2PieceRotateAround00RotationSet());
		addNormalPieceType(fighterPiece);





		normalMusic = "puzzlefight";
		fastMusic = "";
		deadMusic = "tetrid_death";
		creditsMusic = "calmbeat";


		gameTypeCaptionText = "Game: Puzzle Fight Type Y (Columnsish)";
		rulesCaptionText = "Rules: 3 In A Row Or Diagonal";


		//6x13
		gridWidth = 6;
		gridHeight = 13;

		makeNewPiece = true;


	}





	// =========================================================================================================================
	public void gemfight_swap()
	{// =========================================================================================================================




		bloomIntensity = 1.5f;
		bloomTimes = 10;

		//this only exists in dreamcast and psp versions
		// type z is like tetris attack except you rotate a quad cursor and you have to break chains with a breaker block


		scoreType = ScoreType.BLOCKS_CLEARED;
		scoreTypeAmountPerLevelGained = 20;


		chainRule_CheckTouchingBreakerBlocksChain = true;


		removingBlocksDelayTicksBetweenEachBlock = 300;


		blockRule_drawBlocksConnectedByColorIgnoringPiece = false;
		blockRule_drawBlocksConnectedByPieceIgnoringColor = false;
		blockRule_drawBlocksConnectedByColorInPiece = false;

		currentPieceRenderAsNormalPiece = false;
		currentPieceOutlineAllPieces = true;

		gravityRule_ticksToMoveDownBlocksOverBlankSpaces = 50;


		stackDontPutSameColorNextToEachOther = true;

		blockMovementInterpolationTicks = 200;


		int i = 4;
		if(difficulty==Difficulty.EASY)i = 4;
		else
		if(difficulty==Difficulty.NORMAL)i = 5;//0-6
		else
		i = 6;

		BobColor[] maxColors = new BobColor[]{BobColor.green,BobColor.blue,BobColor.red,BobColor.yellow};
		maxColors = new BobColor[]{BobColor.cyan,BobColor.magenta,BobColor.green,BobColor.purple,BobColor.blue,BobColor.orange, BobColor.yellow};

		if(i>maxColors.length)i=maxColors.length;

		BobColor[] colors = new BobColor[i];
		for(int c=0;c<i;c++)
		{
			colors[c] = maxColors[c];
		}



		BlockType normalBlock = new BlockType(BobsGame.squareGemName,colors);
		addNormalBlockType(normalBlock);
		addPlayingFieldBlockType(normalBlock);


		BlockType crashGemBlock = new BlockType(BobsGame.sparkBallName,colors,4,0);
		addNormalBlockType(crashGemBlock);
		addPlayingFieldBlockType(crashGemBlock);


		BlockType counterGemBlock = new BlockType(BobsGame.counterName,colors);
		counterGemBlock.counterType=true;

		addGarbageBlockType(counterGemBlock);


		crashGemBlock.chainConnectionsMustContainAtLeastOneBlockWithThisTrue = true;
		counterGemBlock.ignoreWhenCheckingChainConnections = true;





		repeatDelayA = 200;
		repeatDelayB = 200;
		repeatDelayR = 200;
		repeatDelayUp = 50;
		repeatDelayDown = 50;
		repeatDelayLeft = 50;
		repeatDelayRight = 50;


		repeatEnabledA = false;
		repeatEnabledB = false;
		repeatEnabledR = false;
		repeatEnabledUp = true;
		repeatEnabledDown = true;
		repeatEnabledLeft = true;
		repeatEnabledRight = true;


		repeatStartDelayA = 200;
		repeatStartDelayB = 200;
		repeatStartDelayR = 200;
		repeatStartDelayUp = 200;
		repeatStartDelayDown = 200;
		repeatStartDelayLeft = 200;
		repeatStartDelayRight = 200;




		flashBlockSpeedTicks = 17;
		timesToFlashBlocks = 28;





		normalMusic = "puzzlefight";
		fastMusic = "";
		deadMusic = "tetrid_death";
		creditsMusic = "calmbeat";


		gameTypeCaptionText = "Game: Puzzle Fight Type Z (Quad Swap)";
		rulesCaptionText = "Rules: Breaker Block";




		gridWidth = 6;
		gridHeight = 13+2;
		//**6x13, 2 for overlap and hidden
		gridPixelsBetweenRows = 1;
		gridPixelsBetweenColumns = 1;




		//level 1 easy = 1 pixel every 60 frames
		//level 99 easy = 3,3,3,2
		//stop 1 frame when new row becomes opaque
		//stackRiseSpeed=300;
		stackRiseGame = true;
		useCurrentPieceAsCursor=true;
		randomlyFillStack = true;
		randomlyFillStackAmount = 30;
		randomlyFillStackStartY = 7;

		makeCursorPiece = true;
		cursorPieceSize = 4;
	}






}
