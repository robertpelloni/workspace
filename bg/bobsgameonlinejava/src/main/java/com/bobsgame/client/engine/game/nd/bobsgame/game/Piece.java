package com.bobsgame.client.engine.game.nd.bobsgame.game;

import java.util.ArrayList;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.GLUtils;
import com.bobsgame.shared.BobColor;


//=========================================================================================================================
public class Piece
{//=========================================================================================================================

	transient static Logger log = (Logger) LoggerFactory.getLogger(Piece.class);
	transient public Grid grid = null;
	transient public GameLogic game = null;

	public int currentRotation = 0;

	public int xGrid;
	public int yGrid;

	public ArrayList<Block> blocks = new ArrayList<Block>();


	public float cursorAlphaFrom = 0.3f;
	public float cursorAlphaTo = 1.0f;
	public long cursorFadeTicksPerPhase = 200;
	float cursorAlpha = cursorAlphaFrom;
	long cursorFadeTicks = 0;
	boolean cursorFadeInOutToggle = false;


	public float ghostAlphaFrom = 0.3f;
	public float ghostAlphaTo = 0.7f;
	public long ghostFadeTicksPerPhase = 100;
	float ghostAlpha = ghostAlphaFrom;
	long ghostFadeTicks = 0;
	boolean ghostFadeInOutToggle = false;


	public Block holdingBlock = null;
	public PieceType pieceType = null;


	public boolean overrideAnySpecialBehavior = false;

	public int piecesSetSinceThisPieceSet = 0;
	public boolean setInGrid = false;



	//=========================================================================================================================
	public Piece(GameLogic gameInstance, Grid grid, PieceType pieceType, ArrayList<BlockType> blockTypes)
	{//=========================================================================================================================

		this.game = gameInstance;

		this.grid = grid;
		this.pieceType = pieceType;

		if(pieceType.overrideBlockType!=null)
		{
			for(int b=0;b<pieceType.numBlocks;b++)
			{
				blocks.add(new Block(gameInstance,grid,this,pieceType.overrideBlockType));
			}
		}
		else
		{
			for(int b=0;b<pieceType.numBlocks;b++)
			{
				blocks.add(new Block(gameInstance,grid,this,grid.getRandomBlockType(blockTypes)));
			}
		}

		setRotation(0);


		initBlocks();
	}

	//=========================================================================================================================
	public Piece(GameLogic gameInstance, Grid grid, PieceType pieceType, BlockType blockType)
	{//=========================================================================================================================


		this.game = gameInstance;

		//only used for cursors for now
		this.grid = grid;
		this.pieceType = pieceType;

		if(pieceType.overrideBlockType!=null){blockType = pieceType.overrideBlockType;}

		for(int b=0;b<pieceType.numBlocks;b++)
		{
			blocks.add(new Block(gameInstance,grid,this,blockType));
		}


		setRotation(0);


		initBlocks();
	}


	public int cellW()
	{
		return Game().cellW();
	}

	public int cellH()
	{
		return Game().cellH();
	}


	public GameType GameType()
	{
		return Game().GameType();
	}

	public GameLogic Game()
	{
		return game;
	}






	// =========================================================================================================================
	public static enum RotationType
	{// =========================================================================================================================

		SRS,
		//Tetris Worlds
		//Tetris Deluxe
		//used in TGM3TI, called "World"

		//flipped side up spawn for T,L,J and new wall kicks

		//4 orientations for I,S,Z
		//originated in Tetris 2+bombliss

		SEGA,
		//used in TGM1/2, earlier games

		NES,
		GB,
		//TENGEN,
		//RUSSIAN,
		DTET,

	}





	// =========================================================================================================================
	static public class BlockOffset
	{// =========================================================================================================================
		public int x;
		public int y;

		public BlockOffset(int x, int y)
		{
			this.x = x;
			this.y = y;
		}
	}


	// =========================================================================================================================
	static public class Rotation
	{// =========================================================================================================================
		public ArrayList<BlockOffset> blockOffsets = new ArrayList<BlockOffset>();

		public void add(BlockOffset b)
		{
			blockOffsets.add(b);
		}
	}




	// =========================================================================================================================
	public void initBlocks()
	{// =========================================================================================================================
		initColors();
		setPieceBlockConnections();
		setBlockColorConnectionsInPiece();
	}


	// =========================================================================================================================
	public void initColors()
	{// =========================================================================================================================
		//set piece color

		for(int i=0;i<blocks.size();i++)
		{
			Block b = blocks.get(i);

			if(b.blockType.colors!=null)b.setRandomBlockTypeColor();
			else
			if(pieceType.color!=null){b.setColor(pieceType.color);}
		}


		if(GameType().whenGeneratingPieceDontMatchTwoBlocksOfTheSameSpecialRandomTypeAndColor)
		{

			//don't match a green crash piece with a green crash piece
			for(int a=0;a<blocks.size();a++)
			{

				Block blockA = blocks.get(a);

				for(int b=0;b<blocks.size();b++)
				{

					Block blockB = blocks.get(b);

					if(blockB==blockA)continue;

					if
					(
						blockA.blockType==blockB.blockType
						&&
						blockA.blockType.isSpecialType()
						&&
						blockB.blockType.isSpecialType()

					)
					{
						while(blockA.color()==blockB.color())blockA.setRandomBlockTypeColor();
					}
				}
			}

		}

		if(GameType().whenGeneratingPieceDontMatchNormalBlockWithBlockOfDifferentTypeAndSameColor)
		{

			//don't match a green crash piece with a green gem
			for(int a=0;a<blocks.size();a++)
			{

				Block blockA = blocks.get(a);

				for(int b=0;b<blocks.size();b++)
				{

					Block blockB = blocks.get(b);

					if(blockB==blockA)continue;

					if
					(
						blockA.blockType!=blockB.blockType
						&&
						blockA.blockType.isSpecialType()!=blockB.blockType.isSpecialType()

					)
					{
						if(blockA.blockType.isSpecialType()==false)
						{
							while(blockA.color()==blockB.color())blockA.setRandomBlockTypeColor();
						}
						else
						if(blockB.blockType.isSpecialType()==false)
						{
							while(blockA.color()==blockB.color())blockB.setRandomBlockTypeColor();
						}
					}
				}
			}

		}

		if(GameType().whenGeneratingPieceDontMatchAllBlockColors)
		{

			//don't make 3 jewels of the same color

			BobColor c = blocks.get(0).color();

			if(c!=null)
			{

				boolean allTheSame = true;

				for(int i=0;i<blocks.size();i++)
				{
					if(c!=blocks.get(i).color())
					{
						allTheSame = false;
					}
				}

				if(allTheSame)
				{

					Block blockA = blocks.get(0);

					for(int b=0;b<blocks.size();b++)
					{
						Block blockB = blocks.get(b);

						if(blockB==blockA)continue;

						while(blockA.color()==blockB.color())blockB.setRandomBlockTypeColor();

					}

				}
			}

		}

	}

	//=========================================================================================================================
	public void setPieceBlockConnections()
	{//=========================================================================================================================

		for(int b=0;b<blocks.size();b++)blocks.get(b).connectedBlocksByPiece.clear();

		for(int b=0;b<blocks.size();b++)
		{
			for(int c=0;c<blocks.size();c++)
			{
				if(blocks.get(c)!=blocks.get(b))
				{
					if(blocks.get(b).connectedBlocksByPiece.contains(blocks.get(c))==false)blocks.get(b).connectedBlocksByPiece.add(blocks.get(c));
				}
			}
		}
	}


	//=========================================================================================================================
	public void setBlockColorConnectionsInPiece()
	{//=========================================================================================================================

		for(int b=0;b<blocks.size();b++)blocks.get(b).connectedBlocksByColor.clear();

		for(int b=0;b<blocks.size();b++)
		{
			for(int c=0;c<blocks.size();c++)
			{
				if(blocks.get(c)!=blocks.get(b))
				{
					if(blocks.get(b).color()==blocks.get(c).color())
					if(blocks.get(b).connectedBlocksByColor.contains(blocks.get(c))==false)blocks.get(b).connectedBlocksByColor.add(blocks.get(c));
				}
			}
		}
	}





	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

		cursorFadeTicks+=Game().ticks();

		if(cursorFadeTicks>cursorFadeTicksPerPhase)
		{
			cursorFadeTicks=0;
			cursorFadeInOutToggle=!cursorFadeInOutToggle;
		}
		if(cursorFadeInOutToggle==true)
		{
			cursorAlpha = cursorAlphaFrom + ((float)cursorFadeTicks/(float)cursorFadeTicksPerPhase)*(cursorAlphaTo-cursorAlphaFrom);
		}
		else
		{
			cursorAlpha = cursorAlphaTo - ((float)cursorFadeTicks/(float)cursorFadeTicksPerPhase)*(cursorAlphaTo-cursorAlphaFrom);
		}




		ghostFadeTicks+=Game().ticks();

		if(ghostFadeTicks>ghostFadeTicksPerPhase)
		{
			ghostFadeTicks=0;
			ghostFadeInOutToggle=!ghostFadeInOutToggle;
		}
		if(ghostFadeInOutToggle==true)
		{
			ghostAlpha = ghostAlphaFrom + ((float)ghostFadeTicks/(float)ghostFadeTicksPerPhase)*(ghostAlphaTo-ghostAlphaFrom);
		}
		else
		{
			ghostAlpha = ghostAlphaTo - ((float)ghostFadeTicks/(float)ghostFadeTicksPerPhase)*(ghostAlphaTo-ghostAlphaFrom);
		}


		for(int i=0;i<blocks.size();i++)
		{
			Block b = blocks.get(i);
			if(b.blockType.counterType)
			{
				if(b.counterCount==-2)
				{
					b.counterCount = Game().getRandomIntLessThan(11);
				}
			}
		}


		if(setInGrid)
		{
			if(pieceType.turnBackToNormalPieceAfterNPiecesLock!=-1)
			{
				if(piecesSetSinceThisPieceSet >= pieceType.turnBackToNormalPieceAfterNPiecesLock)
				{
					overrideAnySpecialBehavior = true;
				}
			}


			for(int i=0;i<blocks.size();i++)
			{

				Block b = blocks.get(i);

				if(b.blockType.turnBackToNormalBlockAfterNPiecesLock!=-1)
				{
					if(piecesSetSinceThisPieceSet >= b.blockType.turnBackToNormalBlockAfterNPiecesLock)
					{
						b.overrideAnySpecialBehavior = true;
					}
				}

				if(b.blockType.counterType)
				{
					if(b.counterCount==-1)
					{
						b.counterCount=-2;
						BobColor color = b.color();
						b.blockType = grid.getRandomBlockTypeFromArrayExcludingSpecialBlockTypes(GameType().getNormalBlockTypes());
						b.setColor(color);
					}
				}

			}

		}



		for(int i=0;i<blocks.size();i++)blocks.get(i).update();
		if(holdingBlock!=null)holdingBlock.update();
	}





	//=========================================================================================================================
	public float getScreenX()
	{//=========================================================================================================================
		return grid.x()+xGrid*cellW();

	}

	//=========================================================================================================================
	public float getScreenY()
	{//=========================================================================================================================
		return grid.y()+yGrid*cellH() + grid.scrollPlayingFieldY;
	}





	//=========================================================================================================================
	public void renderOutlineFirstBlock(float x, float y, float alpha, boolean asGhost)
	{//=========================================================================================================================

		int w = cellW();
		int h = cellH();

		Block b = blocks.get(0);


		float bx = x+b.xInPiece*w;
		float by = y+b.yInPiece*h;

		if(asGhost==false)
		{
			float[] xy = b.getInterpolatedScreenXY(bx,by);

			bx = xy[0];
			by = xy[1];
		}



		for(int p=0;p<5;p++)//TODO: scale with screen res
		{
			float a = alpha;

			//if(p==1)a = 1.0f / alpha;//TODO: shift alpha through cycle?

			//top
			GLUtils.drawFilledRectXYWH(bx,by-p,w,1,1.0f,1.0f,1.0f,a);
			//bottom
			GLUtils.drawFilledRectXYWH(bx,by+h+(p-1),w,1,1.0f,1.0f,1.0f,a);
			//left
			GLUtils.drawFilledRectXYWH(bx-p,by,1,h,1.0f,1.0f,1.0f,a);
			//right
			GLUtils.drawFilledRectXYWH(bx+w+(p-1),by,1,h,1.0f,1.0f,1.0f,a);
		}


	}


	//=========================================================================================================================
	public void renderOutlineBlockZeroZero(float x, float y, float alpha, boolean asGhost)
	{//=========================================================================================================================

		int w = cellW();
		int h = cellH();


		for(int i=0;i<blocks.size();i++)
		{
			Block b = blocks.get(i);


			//outline main piece
			if(b.xInPiece==0&&b.yInPiece==0)
			{

				float bx = x+b.xInPiece*w;
				float by = y+b.yInPiece*h;

				if(asGhost==false)
				{
					float[] xy = b.getInterpolatedScreenXY(bx,by);

					bx = xy[0];
					by = xy[1];
				}

				for(int p=0;p<5;p++)//TODO: scale with screen res
				{
					float a = alpha;

					//if(p==1)a = 1.0f / alpha;

					//top
					GLUtils.drawFilledRectXYWH(bx,by-p,w,1,1.0f,1.0f,1.0f,a);
					//bottom
					GLUtils.drawFilledRectXYWH(bx,by+h+(p-1),w,1,1.0f,1.0f,1.0f,a);
					//left
					GLUtils.drawFilledRectXYWH(bx-p,by,1,h,1.0f,1.0f,1.0f,a);
					//right
					GLUtils.drawFilledRectXYWH(bx+w+(p-1),by,1,h,1.0f,1.0f,1.0f,a);
				}
			}
		}

	}



	//=========================================================================================================================
	public void renderAsCurrentPiece()
	{//=========================================================================================================================
		renderAsCurrentPiece(getScreenX(),getScreenY());
	}
	//=========================================================================================================================
	public void renderAsCurrentPiece(float x, float y)
	{//=========================================================================================================================


		int w = cellW();
		int h = cellH();


		if(GameType().currentPieceMoveUpHalfABlock)y-=cellH()/3;

		if(GameType().currentPieceRenderAsNormalPiece)
		{
			render(x,y);
		}

		if(GameType().currentPieceRule_OutlineBlockAtZeroZero)renderOutlineBlockZeroZero(x,y,cursorAlpha,false);

		if(GameType().currentPieceOutlineFirstBlockRegardlessOfPosition)renderOutlineFirstBlock(x, y, cursorAlpha,false);



		if(GameType().currentPieceRenderHoldingBlock)
		{
			if(holdingBlock!=null)
			{
				holdingBlock.render(x,y,1.0f,1.0f,true);
			}
		}

		if(GameType().currentPieceOutlineAllPieces)
		{
			for(int i=0;i<blocks.size();i++)
			{
				int ox = GameType().gridPixelsBetweenColumns;
				int oy = GameType().gridPixelsBetweenRows;


				Block b = blocks.get(i);


				float bx = x+b.xInPiece*w+b.xInPiece*ox;
				float by = y+b.yInPiece*h+b.yInPiece*oy;


//				float[] xy = b.getInterpolatedScreenXY(bx,by);
//
//				bx = xy[0];
//				by = xy[1];

				for(int p=0;p<5;p++)
				{
					float a = cursorAlpha;

					if(p==1)a = 1.0f / cursorAlpha;

					//top
					GLUtils.drawFilledRectXYWH(bx,by-p,w,1,1.0f,1.0f,1.0f,a);
					//bottom
					GLUtils.drawFilledRectXYWH(bx,by+h+(p-1),w,1,1.0f,1.0f,1.0f,a);
					//left
					GLUtils.drawFilledRectXYWH(bx-p,by,1,h,1.0f,1.0f,1.0f,a);
					//right
					GLUtils.drawFilledRectXYWH(bx+w+(p-1),by,1,h,1.0f,1.0f,1.0f,a);
				}
			}
		}




	}

	//=========================================================================================================================
	public void render(float x, float y)
	{//=========================================================================================================================
		for(int i=0;i<blocks.size();i++)
		{
			Block b = blocks.get(i);
			b.render(x+b.xInPiece*cellW(),y+b.yInPiece*cellH(),1.0f,1.0f,true);
		}
	}



	//=========================================================================================================================
	public void renderGhost(float x, float y, float alpha)
	{//=========================================================================================================================

		for(int i=0;i<blocks.size();i++)
		{
			Block b = blocks.get(i);

			BobColor c = GameType().gridCheckeredBackgroundColor1;
			// fill in black square so background doesnt show through alpha
			GLUtils.drawFilledRectXYWH(x+b.xInPiece*cellW(),y+b.yInPiece*cellH(),cellW(),cellH(),c.r(),c.g(),c.b(),1.0f);

			b.render(x+b.xInPiece*cellW(),y+b.yInPiece*cellH(),ghostAlpha*alpha,1.0f,false);

		}

		if(GameType().currentPieceRule_OutlineBlockAtZeroZero)renderOutlineBlockZeroZero(x,y,ghostAlpha/2*alpha,true);

		if(GameType().currentPieceOutlineFirstBlockRegardlessOfPosition)renderOutlineFirstBlock(x, y, ghostAlpha/2*alpha,true);



	}


	// =========================================================================================================================
	public void setBlocksSlamming()
	{// =========================================================================================================================
		for(int i=0;i<blocks.size();i++)
		{
			Block b = blocks.get(i);
			b.slamming=true;
			b.slamX=getScreenX()+(b.xInPiece)*cellW();
			b.slamY=getScreenY()+(b.yInPiece)*cellH();
		}
	}


	// =========================================================================================================================
	public int getWidth()
	{// =========================================================================================================================


		int lowestXOffset = 4;
		int highestXOffset = -4;
		for(int b=0;b<blocks.size();b++)if(blocks.get(b).xInPiece<lowestXOffset)lowestXOffset = blocks.get(b).xInPiece;
		for(int b=0;b<blocks.size();b++)if(blocks.get(b).xInPiece>highestXOffset)highestXOffset = blocks.get(b).xInPiece;

		//1+ for 0,0 piece
		return 1 + Math.abs(highestXOffset)+Math.abs(lowestXOffset);
	}

	// =========================================================================================================================
	public int getHeight()
	{// =========================================================================================================================

		int lowestYOffset = 4;
		int highestYOffset = -4;
		for(int b=0;b<blocks.size();b++)if(blocks.get(b).yInPiece<lowestYOffset)lowestYOffset = blocks.get(b).yInPiece;
		for(int b=0;b<blocks.size();b++)if(blocks.get(b).yInPiece>highestYOffset)highestYOffset = blocks.get(b).yInPiece;

		return 1 + Math.abs(highestYOffset)+Math.abs(lowestYOffset);
	}

	// =========================================================================================================================
	public int getLowestOffsetX()
	{// =========================================================================================================================
		int lowestXOffset = 0;
		for(int b=0;b<blocks.size();b++)if(blocks.get(b).xInPiece<lowestXOffset)lowestXOffset = blocks.get(b).xInPiece;

		return lowestXOffset;
	}

	// =========================================================================================================================
	public int getLowestOffsetY()
	{// =========================================================================================================================
		int lowestYOffset = 0;
		for(int b=0;b<blocks.size();b++)if(blocks.get(b).yInPiece<lowestYOffset)lowestYOffset = blocks.get(b).yInPiece;

		return lowestYOffset;
	}


	// =========================================================================================================================
	public int getHighestOffsetX()
	{// =========================================================================================================================
		int highestXOffset = 0;
		for(int b=0;b<blocks.size();b++)if(blocks.get(b).xInPiece>highestXOffset)highestXOffset = blocks.get(b).xInPiece;

		return highestXOffset;
	}


	// =========================================================================================================================
	public int getHighestOffsetY()
	{// =========================================================================================================================
		int highestYOffset = 0;
		for(int b=0;b<blocks.size();b++)if(blocks.get(b).yInPiece>highestYOffset)highestYOffset = blocks.get(b).yInPiece;

		return highestYOffset;
	}



	// =========================================================================================================================
	public void rotateCCW()
	{// =========================================================================================================================
		if(currentRotation==0)currentRotation=(pieceType.rotationSet.size() - 1);
		else currentRotation=currentRotation-1;
		setRotation(currentRotation);
	}


	// =========================================================================================================================
	public void rotateCW()
	{// =========================================================================================================================
		if(currentRotation==(pieceType.rotationSet.size() - 1))currentRotation=0;
		else currentRotation=currentRotation+1;
		setRotation(currentRotation);
	}


	// =========================================================================================================================
	public void setRandomPieceColors(boolean grayscale)
	{// =========================================================================================================================


		//TODO:
		//TODO:
		//TODO:
		//TODO:
		//TODO:
		//TODO:
//		for(int i=0;i<colors.length;i++)
//		{
//			colors[i] = BobColor.black;
//		}
//
//		for(int i=0;i<colors.length;i++)
//		{
//			BobColor temp = BobColor.black;
//			boolean taken = true;
//			while(taken==true)
//			{
//				taken=false;
//
//				if(grayscale)temp = Block.getRandomGrayscaleColor();
//				else temp = Block.getRandomColor();
//
//				for(int n=0;n<colors.length;n++)if(colors[n]==temp)taken=true;
//			}
//
//			colors[i]=temp;
//		}
	}





	//=========================================================================================================================
	public void setRotation(int rotation)
	{//=========================================================================================================================

		currentRotation = rotation;

		if(rotation>=pieceType.rotationSet.size())rotation-=pieceType.rotationSet.size();

		Rotation r = pieceType.rotationSet.get(rotation);

		for(int i=0;i<blocks.size();i++)
		{
			BlockOffset b = r.blockOffsets.get(i);
			blocks.get(i).setXYOffsetInPiece(b.x,b.y);
		}

	}

	// =========================================================================================================================
	static public ArrayList<Rotation> get2PieceRotateAround00RotationSet()
	{// =========================================================================================================================



		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		//if(pieceType.name.equals("BLOB") || pieceType.name.equals("DAMA") || pieceType.name.equals("PUZZLEFIGHTER"))

		//this is rotation around 0,0
		//if(rotation==0)
		{
			Rotation r = new Rotation();
			rotations.add(r);
			r.add(new BlockOffset(0,0));
			r.add(new BlockOffset(1,0));
		}

		//if(rotation==1)
		{
			Rotation r = new Rotation();
			rotations.add(r);
			r.add(new BlockOffset(0,0));
			r.add(new BlockOffset(0,1));
		}

		//if(rotation==2)
		{
			Rotation r = new Rotation();
			rotations.add(r);
			r.add(new BlockOffset(0,0));
			r.add(new BlockOffset(-1,0));
		}

		//if(rotation==3)
		{
			Rotation r = new Rotation();
			rotations.add(r);
			r.add(new BlockOffset(0,0));
			r.add(new BlockOffset(0,-1));
		}

		return rotations;
	}


	// =========================================================================================================================
	static public ArrayList<Rotation> get2PieceBottomLeftAlwaysFilledRotationSet()
	{// =========================================================================================================================



		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		//if(pieceType.name.equals("DRBOB"))

		//this is rotation in a 2x2 bounding box with bottom left always filled
		//if(rotation==0)
		{
			Rotation r = new Rotation();
			rotations.add(r);
			r.add(new BlockOffset(0,0));
			r.add(new BlockOffset(1,0));
		}

		//if(rotation==1)
		{
			Rotation r = new Rotation();
			rotations.add(r);
			r.add(new BlockOffset(0,-1));
			r.add(new BlockOffset(0,0));
		}

		//if(rotation==2)
		{
			Rotation r = new Rotation();
			rotations.add(r);
			r.add(new BlockOffset(1,0));
			r.add(new BlockOffset(0,0));
		}

		//if(rotation==3)
		{
			Rotation r = new Rotation();
			rotations.add(r);
			r.add(new BlockOffset(0,0));
			r.add(new BlockOffset(0,-1));
		}

		return rotations;
	}


	// =========================================================================================================================
	static public ArrayList<Rotation> get2PieceCursorRotationSet()
	{// =========================================================================================================================

		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		//if(pieceType.name.equals("PANELPUZZLE_CURSOR"))
		{
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));
			}
		}

		return rotations;
	}

	// =========================================================================================================================
	static public ArrayList<Rotation> get1PieceCursorRotationSet()
	{// =========================================================================================================================

		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		//if(pieceType.name.equals("PANELPUZZLE")) if(pieceType.name.equals("DAMASWAP_CURSOR"))
		{
			//this is rotation in a 2x2 bounding box with bottom left always filled
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
			}
		}

		return rotations;
	}

	// =========================================================================================================================
	static public ArrayList<Rotation> get4PieceCursorRotationSet()
	{// =========================================================================================================================

		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		//if(pieceType.name.equals("PUZZLEFIGHTER_CURSOR"))
		{
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(1,1));
			}
		}

		return rotations;
	}



	// =========================================================================================================================
	static public ArrayList<Rotation> get3PieceVerticalRotationSet()
	{// =========================================================================================================================

		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		//if(pieceType.name.equals("COLUMNS"))
		{

			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,-2));
			}

			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,-2));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,-1));
			}

			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,-2));
				r.add(new BlockOffset(0,0));
			}

		}
		return rotations;
	}


	// =========================================================================================================================
	static public ArrayList<Rotation> get3PieceTRotationSet()
	{// =========================================================================================================================

		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		//if(pieceType.name.equals("TETRID_T"))
		{
			/*
			.....[0]
			..[1]...[2]
			*/
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,1));
				r.add(new BlockOffset(1,1));
			}

			/*
			..[1]
			.....[0]
			..[2]
			*/
			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,-1));
				r.add(new BlockOffset(-1,1));
			}

			/*
			..[2]...[1]
			.....[0]
			*/
			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,-1));
				r.add(new BlockOffset(-1,-1));
			}

			/*
			........[2]
			.....[0]
			........[1]
			*/
			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,1));
				r.add(new BlockOffset(1,-1));
			}

		}
		return rotations;
	}

	// =========================================================================================================================
	static public ArrayList<Rotation> get3PieceLRotationSet()
	{// =========================================================================================================================

		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		//if(pieceType.name.equals("TETRID_L"))
		{
			/*
			...[1]
			......[0]
			......[2]
			*/
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,-1));
				r.add(new BlockOffset(0,1));
			}

			/*
			.........[1]
			...[2][0]
			*/
			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,-1));
				r.add(new BlockOffset(-1,0));
			}

			/*
			......[2]
			......[0]
			.........[1]
			*/
			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,1));
				r.add(new BlockOffset(0,-1));
			}

			/*
			......[0][2]
			...[1]
			*/
			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,1));
				r.add(new BlockOffset(1,0));
			}
		}


		return rotations;
	}

	// =========================================================================================================================
	public static ArrayList<Rotation> get3PieceJRotationSet()
	{// =========================================================================================================================

		ArrayList<Rotation> rotations = new ArrayList<Rotation>();


		//if(pieceType.name.equals("TETRID_J"))
		{
			/*
			.........[1]
			......[0]
			......[2]
			*/
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,-1));
				r.add(new BlockOffset(0,1));
			}

			/*
			...[2][0]
			.........[1]
			*/
			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,1));
				r.add(new BlockOffset(-1,0));
			}

			/*
			......[2]
			......[0]
			...[1]
			*/
			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,1));
				r.add(new BlockOffset(0,-1));
			}

			/*
			...[1]
			......[0][2]
			*/
			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,-1));
				r.add(new BlockOffset(1,0));
			}

		}


		return rotations;
	}


	// =========================================================================================================================
	static public ArrayList<Rotation> get3PieceIRotationSet()
	{// =========================================================================================================================

		ArrayList<Rotation> rotations = new ArrayList<Rotation>();


		//if(pieceType.name.equals("TETRID_I"))
		{

			/*
			....[1]
			....[0]
			....[2]
			*/
			//if(rotation==0 || rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,1));
			}

			/*
			..[2][0][1]
			*/
			//if(rotation==1 || rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(-1,0));
			}

			/*
			....[2]
			....[0]
			....[1]
			*/
			//if(rotation==0 || rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(0,-1));

			}

			/*
			..[1][0][2]
			*/
			//if(rotation==1 || rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(1,0));

			}
		}


		return rotations;
	}


	// =========================================================================================================================
	static public ArrayList<Rotation> get3PieceCRotationSet()
	{// =========================================================================================================================

		ArrayList<Rotation> rotations = new ArrayList<Rotation>();


		//if(pieceType.name.equals("TETRID_C"))
		{
			/*
			..[2][0]
			.....[1]
			*/
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(-1,0));
			}

			/*
			.....[2]
			..[1][0]
			*/
			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(0,-1));
			}

			/*
			..[1]
			..[0][2]
			*/
			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(1,0));
			}

			/*
			..[0][1]
			..[2]
			*/
			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(0,1));
			}

		}


		return rotations;
	}


	// =========================================================================================================================
	static public ArrayList<Rotation> get3PieceDRotationSet()
	{// =========================================================================================================================

		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		//if(pieceType.name.equals("TETRID_D"))
		{
			/*
			..[1]
			.....[0]
			........[2]
			*/
			//if(rotation==0 || rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,-1));
				r.add(new BlockOffset(1,1));
			}

			/*
			........[1]
			.....[0]
			..[2]
			*/
			//if(rotation==1 || rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,-1));
				r.add(new BlockOffset(-1,1));
			}
			/*
			..[2]
			.....[0]
			........[1]
			*/
			//if(rotation==0 || rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,1));
				r.add(new BlockOffset(-1,-1));

			}

			/*
			........[2]
			.....[0]
			..[1]
			*/
			//if(rotation==1 || rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,1));
				r.add(new BlockOffset(1,-1));

			}
		}

		return rotations;
	}

	// =========================================================================================================================
	static public ArrayList<Rotation> get4PieceORotationSet()
	{// =========================================================================================================================

		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		//same everywhere
		{
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(1,-1));
			}
			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);

				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,-1));
				r.add(new BlockOffset(1,0));

			}
			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(1,-1));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(0,0));
			}
			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(1,-1));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,-1));
			}
		}

		return rotations;
	}

	// =========================================================================================================================
	static public ArrayList<Rotation> get4PieceSolidRotationSet()
	{// =========================================================================================================================

		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		//same everywhere
		{
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(1,-1));
			}
		}

		return rotations;
	}

	// =========================================================================================================================
	static public ArrayList<Rotation> get9PieceSolidRotationSet()
	{// =========================================================================================================================

		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		//same everywhere
		{
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(2,0));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(1,-1));
				r.add(new BlockOffset(2,-1));
				r.add(new BlockOffset(0,-2));
				r.add(new BlockOffset(1,-2));
				r.add(new BlockOffset(2,-2));
			}
		}

		return rotations;
	}

	// =========================================================================================================================
	static public ArrayList<Rotation> get4PieceIRotationSet(RotationType type)
	{// =========================================================================================================================


		ArrayList<Rotation> rotations = new ArrayList<Rotation>();


		if(type==RotationType.SRS || type==RotationType.DTET || type==RotationType.SEGA)//unique for SRS: 4 position ISZ rotation
		{

			if(type==RotationType.SRS || type==RotationType.SEGA)
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);

				r.add(new BlockOffset(-2,0));
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));

			}

			if(type==RotationType.DTET)
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(-2,1));
				r.add(new BlockOffset(-1,1));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(1,1));
			}


			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(0,2));

			}

			if(type==RotationType.SRS || type==RotationType.DTET)
			{
				//if(rotation==2)
				{
					Rotation r = new Rotation();
					rotations.add(r);
					r.add(new BlockOffset(1,1));

					r.add(new BlockOffset(0,1));
					r.add(new BlockOffset(-1,1));
					r.add(new BlockOffset(-2,1));
				}
				//if(rotation==3)
				{
					Rotation r = new Rotation();
					rotations.add(r);
					r.add(new BlockOffset(-1,2));

					r.add(new BlockOffset(-1,1));
					r.add(new BlockOffset(-1,0));
					r.add(new BlockOffset(-1,-1));
				}
			}
			if(type==RotationType.SEGA)
			{
				//if(rotation==2)
				{
					Rotation r = new Rotation();
					rotations.add(r);
					r.add(new BlockOffset(1,0));
					r.add(new BlockOffset(0,0));
					r.add(new BlockOffset(-1,0));
					r.add(new BlockOffset(-2,0));


				}
				//if(rotation==3)
				{
					Rotation r = new Rotation();
					rotations.add(r);

					r.add(new BlockOffset(0,2));
					r.add(new BlockOffset(0,1));
					r.add(new BlockOffset(0,0));

					r.add(new BlockOffset(0,-1));
				}
			}
		}



		if(type==RotationType.GB)
		{
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(2,0));
			}

			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,-2));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));
			}
			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(2,0));

				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,0));
			}

			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,1));

				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,-2));
			}
		}


		if(type==RotationType.NES)
		{
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(-2,0));
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));

			}
			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,-2));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));
			}
			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(1,0));

				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(-2,0));

			}
			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,1));

				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,-2));
			}
		}



		return rotations;

	}

	// =========================================================================================================================
	static public ArrayList<Rotation> get4PieceJRotationSet(RotationType type)
	{// =========================================================================================================================


		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		if(type==RotationType.SRS)//unique for SRS: flat side down
		{
			//if(rotation==0)//this is rotation 2 for every other game()
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,-1));
				r.add(new BlockOffset(-1,0));

				r.add(new BlockOffset(1,0));

			}
			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));

				r.add(new BlockOffset(1,-1));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,1));

			}
			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,1));


				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(-1,0));

			}
			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));


				r.add(new BlockOffset(-1,1));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(0,-1));
			}
		}

		if(type==RotationType.SEGA || type==RotationType.GB || type==RotationType.NES || type==RotationType.DTET)
		{
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,0));

				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(1,1));

			}
			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(-1,1));

			}

			if(type==RotationType.SEGA || type==RotationType.DTET)
			//if(rotation==2)//SRS rotation 0 but down 1 //down one from other games, on floor
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(1,1));
				r.add(new BlockOffset(-1,1));
				r.add(new BlockOffset(-1,0));

			}

			if(type==RotationType.GB || type==RotationType.NES)
			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(-1,0));


				r.add(new BlockOffset(-1,-1));
			}



			//if(rotation==3)//SRS rotation 1
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(1,-1));



			}

		}



		return rotations;

	}
	// =========================================================================================================================
	static public ArrayList<Rotation> get4PieceLRotationSet(RotationType type)
	{// =========================================================================================================================


		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		if(type==RotationType.SRS)//unique for SRS: flat side down
		{
			//if(rotation==0)//this is rotation 2 for every other game()
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));

				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(1,-1));

			}
			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(1,1));

			}
			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));

				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(-1,1));

			}
			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(0,-1));

				r.add(new BlockOffset(-1,-1));
			}
		}


		if(type==RotationType.SEGA || type==RotationType.GB || type==RotationType.NES || type==RotationType.DTET)
		{
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));

				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(-1,1));

			}

			if(type==RotationType.SEGA || type==RotationType.DTET)
			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));

				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(-1,-1));

			}

			if(type==RotationType.GB || type==RotationType.NES)
			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(-1,-1));
			}


			//if(rotation==2)//down one from other games, on floor
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,1));


				r.add(new BlockOffset(-1,1));
				r.add(new BlockOffset(1,1));
				r.add(new BlockOffset(1,0));
			}

			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));

				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(1,1));
			}
		}



		return rotations;

	}


	// =========================================================================================================================
	static public ArrayList<Rotation> get4PieceSRotationSet(RotationType type)
	{// =========================================================================================================================

		//type=RotationType.SRS;
		//type=RotationType.DTET;
		//type=RotationType.SEGA;
		//type=RotationType.NES;
		//type=RotationType.GB;

		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		if(type==RotationType.SRS || type==RotationType.DTET)//unique for SRS: 4 position ISZ rotation
		{

			if(type==RotationType.SRS)
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(1,-1));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,0));


			}

			if(type==RotationType.DTET)
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);

				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(-1,1));

			}

			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(1,1));

				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,-1));

			}
			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);


				r.add(new BlockOffset(-1,1));
				r.add(new BlockOffset(0,1));

				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));

			}
			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);


				r.add(new BlockOffset(-1,-1));
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));
			}
		}


		if(type==RotationType.SEGA || type==RotationType.GB || type==RotationType.NES )
		{
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);

				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(0,0));

				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(-1,1));

			}

			if(type==RotationType.SEGA || type==RotationType.GB)
			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(-1,-1));
			}

			if(type==RotationType.NES )
			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(1,1));

				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,-1));
			}

			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(-1,1));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));


			}

			if(type==RotationType.SEGA || type==RotationType.GB)
			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(-1,-1));
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));
			}

			if(type==RotationType.NES )
			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(1,1));
			}
		}




		return rotations;

	}

	// =========================================================================================================================
	static public ArrayList<Rotation> get4PieceTRotationSet(RotationType type)
	{// =========================================================================================================================



		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		if(type==RotationType.SRS)//unique for SRS: flat side down
		{
			//if(rotation==0)//this is rotation 2 for every other game()
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));

				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(1,0));

			}
			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,-1));

				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(0,1));

			}
			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(-1,0));



			}
			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));

				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(0,-1));

			}
		}



		if(type==RotationType.SEGA || type==RotationType.GB || type==RotationType.NES  || type==RotationType.DTET)
		{
			//if(rotation==0)//SRS rotation 2, same as NES,GB
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,0));

				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(1,0));
			}

			//if(rotation==1)//SRS rotation 3, same as NES,GB
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(0,1));

			}

			if(type==RotationType.SEGA || type==RotationType.DTET)
			//if(rotation==2)//down one from other games, on floor
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(1,1));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,1));

			}

			if(type==RotationType.GB || type==RotationType.NES )
			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));

				r.add(new BlockOffset(1,0));

				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(-1,0));

			}


			//if(rotation==3)//STS rotation 1, same as NES,GB
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(0,-1));

			}
		}






		return rotations;

	}

	// =========================================================================================================================
	static public ArrayList<Rotation> get4PieceZRotationSet(RotationType type)
	{// =========================================================================================================================

		ArrayList<Rotation> rotations = new ArrayList<Rotation>();

		if(type==RotationType.SRS || type==RotationType.DTET)//unique for SRS: 4 position ISZ rotation
		{

			if(type==RotationType.SRS)
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(-1,-1));
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));

			}
			else
			if(type==RotationType.DTET)
			//if(rotation==0)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(1,1));

			}

			//if(rotation==1)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(1,-1));

				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));

			}

			//if(rotation==2)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(1,1));

				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,0));

			}

			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(-1,1));
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(0,0));

				r.add(new BlockOffset(0,-1));
			}
		}


		if(type==RotationType.SEGA || type==RotationType.GB || type==RotationType.NES )
		{
			//if(rotation==0)//same as STS rotation 2, same as NES,GB
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(1,1));
			}


			if(type==RotationType.SEGA || type==RotationType.NES)
			//if(rotation==1 || rotation==3)//same as STS rotation 1, same as NES
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(1,-1));
				r.add(new BlockOffset(1,0));


				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,1));

			}

			if(type==RotationType.GB)
			//if(rotation==1 || rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,-1));
				r.add(new BlockOffset(0,0));

				r.add(new BlockOffset(-1,0));

				r.add(new BlockOffset(-1,1));
			}
			//if(rotation==2)//same as STS rotation 2, same as NES,GB
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(1,1));

				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(-1,0));

			}

			if(type==RotationType.SEGA || type==RotationType.NES )
			//if(rotation==3)//same as STS rotation 1, same as NES
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(0,1));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(1,0));
				r.add(new BlockOffset(1,-1));

			}

			if(type==RotationType.GB)
			//if(rotation==3)
			{
				Rotation r = new Rotation();
				rotations.add(r);
				r.add(new BlockOffset(-1,1));
				r.add(new BlockOffset(-1,0));
				r.add(new BlockOffset(0,0));
				r.add(new BlockOffset(0,-1));

			}
		}




		return rotations;

	}








}
