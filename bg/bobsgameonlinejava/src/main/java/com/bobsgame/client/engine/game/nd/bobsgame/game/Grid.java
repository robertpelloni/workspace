package com.bobsgame.client.engine.game.nd.bobsgame.game;

import java.util.ArrayList;
import java.util.HashMap;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.game.nd.bobsgame.BobsGame;
import com.bobsgame.client.engine.game.nd.bobsgame.game.BlockType.TurnFromBlockTypeToType;
import com.bobsgame.client.engine.game.nd.bobsgame.game.GameLogic.MovementType;
import com.bobsgame.client.engine.game.nd.bobsgame.game.GameType.*;
import com.bobsgame.shared.BobColor;

import easing.Easing;






//=========================================================================================================================
public class Grid
{// =========================================================================================================================

	transient static Logger log = (Logger) LoggerFactory.getLogger(Grid.class);
	transient public GameLogic game = null;


	public float screenX = 0;
	public float screenY = 0;


	public HashMap<Integer,Block> blocks = new HashMap<Integer,Block>();


	int shakeTicksSpeed = 60;
	int shakeMaxX = 3;
	float shakePlayingFieldX=0;
	float shakePlayingFieldY=0;
	long shakePlayingFieldTicks = 0;
	private boolean shakePlayingFieldLeftRightToggle=false;


	int effectShakeDurationTicks = 0;
	int effectShakeTicksCounter = 0;
	int effectShakeMaxX = 0;
	int effectShakeMaxY = 0;


	public int scrollPlayingFieldY = 0;//for panel

	int scrollTicksSpeed = 30;
	private int backgroundScrollX=0;
	private int backgroundScrollY=0;
	long scrollPlayingFieldBackgroundTicks = 0;


	private int deadX=0;
	private int deadY=0;


	public int lastGarbageHoleX = 0;
	public boolean garbageHoleDirectionToggle = true;

	public ArrayList<Piece> randomBag = null;




	//=========================================================================================================================
	public int cellW()
	{//=========================================================================================================================
		return Game().cellW();
	}

	//=========================================================================================================================
	public int cellH()
	{//=========================================================================================================================
		return Game().cellH();
	}

	//=========================================================================================================================
	public GameType GameType()
	{//=========================================================================================================================
		return Game().GameType();
	}

	//=========================================================================================================================
	public GameLogic Game()
	{//=========================================================================================================================
		return game;
	}





	// =========================================================================================================================
	public Grid(GameLogic gameInstance)
	{// =========================================================================================================================
		this.game = gameInstance;

	}





	//=========================================================================================================================
	public float x()
	{//=========================================================================================================================
		return screenX+shakePlayingFieldX;
	}
	//=========================================================================================================================
	public float y()
	{//=========================================================================================================================
		return screenY+shakePlayingFieldY;
	}
	//=========================================================================================================================
	public float bgX()
	{//=========================================================================================================================
		return x()+backgroundScrollX;
	}
	//=========================================================================================================================
	public float bgY()
	{//=========================================================================================================================
		return y()+backgroundScrollY;
	}


	//=========================================================================================================================
	public int h()
	{//=========================================================================================================================
		return GameType().gridHeight;
	}

	//=========================================================================================================================
	public int w()
	{//=========================================================================================================================
		return GameType().gridWidth;
	}

	// =========================================================================================================================
	public void update()
	{// =========================================================================================================================


		//update pieces instead of blocks so we can update all the pieces and blocks inside pieces.update
		ArrayList<Piece> piecesInGrid = getArrayOfPiecesOnGrid();
		for(int i=0;i<piecesInGrid.size();i++)
		{
			Piece p = piecesInGrid.get(i);
			p.update();
		}


		if(effectShakeDurationTicks>0)
		{
			effectShakeTicksCounter+=Game().ticks();

			shakePlayingFieldX = (float)Easing.easeInOutSinusoidal(effectShakeTicksCounter,-effectShakeMaxX/2.0f,effectShakeMaxX/2.0f,50);
			shakePlayingFieldY = (float)Easing.easeInOutSinusoidal(effectShakeTicksCounter,effectShakeMaxY/2.0f,-effectShakeMaxY/2.0f,100);

			if(effectShakeTicksCounter>effectShakeDurationTicks)
			{
				effectShakeTicksCounter=0;
				effectShakeDurationTicks=0;
				shakePlayingFieldX=0;
				shakePlayingFieldY=0;
				effectShakeMaxX = 0;
				effectShakeMaxY = 0;
			}
		}



//		for(int y=0;y<h();y++)
//		{
//			for(int x=0;x<w();x++)
//			{
//				Block b = get(x,y);
//				if(b!=null)b.update(Engine().ticksPassed());
//			}
//		}




	}




	//=========================================================================================================================
	public void reformat(int oldWidth, int oldHeight)
	{//=========================================================================================================================


		ArrayList<Block> blockList = new ArrayList<Block>();

		for(int y=oldHeight-1;y>=0;y--)
		{
			for(int x=0;x<oldWidth;x++)
			{
				if(blocks.containsKey(y*oldWidth+x))
				{
					Block b = blocks.remove(y*oldWidth+x);

					b.xInPiece = 0;
					b.yInPiece = 0;
					b.connectedBlocksByColor.clear();
					b.connectedBlocksByPiece.clear();
					//b.piece = null;

					blockList.add(b);
				}
			}
		}

		//log.warn("Removed "+blockList.size()+" blocks");


		int x=0;
		int y=h()-1;

		while(blockList.size()>0&&y>=0)
		{

			Block b = blockList.remove(0);
			add(x,y,b);

			x++;

			if(x>=w())
			{
				y--;
				x=0;
			}

		}



	}




	//=========================================================================================================================
	public int getNumberOfFilledCells()
	{//=========================================================================================================================

		int amt = 0;

		for(int y=0;y<h();y++)
		{
			for(int x=0;x<w();x++)
			{
				Block b = get(x,y);

				if(b!=null)amt++;
			}
		}

		return amt;

	}


	//=========================================================================================================================
	public void clearField()
	{//=========================================================================================================================

		//blocks = new Hashtable<Integer,Block>();

		for(int y=0;y<h();y++)
		{
			for(int x=0;x<w();x++)
			{
				Block b = get(x,y);

				if(b!=null)remove(x,y);
			}
		}


	}



	//=========================================================================================================================
	public void replaceAllBlocksWithNewGameBlocks()
	{//=========================================================================================================================


		for(int y=h()-1;y>=0;y--)
		{
			for(int x=0;x<w();x++)
			{
				if(get(x,y)!=null)
				{

					Block a = remove(x,y);

					Piece p = getRandomPiece(GameType().getPlayingFieldPieceTypes(), GameType().getPlayingFieldBlockTypes());


					int maxHeight = 0;

					if(GameType().difficulty==Difficulty.HARD)maxHeight = h()/3;
					if(GameType().difficulty==Difficulty.NORMAL)maxHeight = h()/2;
					else maxHeight = (h()/3)*2;


					if(y>maxHeight)
					{

						putPieceInGridCheckingForFillRules(p,x,y);

						Block b = get(x,y);

						if(b!=null)
						{
							b.lastScreenX = a.lastScreenX;
							b.lastScreenY = a.lastScreenY;
							b.ticksSinceLastMovement=0;

//							if(b.blockType.colors!=null&&a.blockType.colors!=null)
//							{
//								for(int i=0;i<b.blockType.colors.length;i++)
//								if(b.blockType.colors[i]==a.color())b.setColor(a.color());
//							}

						}
					}
				}
			}
		}
	}



	//=========================================================================================================================
	public Piece dontPutSameColorDiagonalOrNextToEachOtherReturnNull(int x, int y)
	{//=========================================================================================================================



		ArrayList<BobColor> acceptableColors = new ArrayList<BobColor>();
		for(int b=0;b<GameType().getPlayingFieldBlockTypes().size();b++)
		{
			BlockType blockType = GameType().getPlayingFieldBlockTypes().get(b);

			if(blockType.colors!=null)
			{
				for(int i=0; i<blockType.colors.length; i++)
				if(acceptableColors.contains(blockType.colors[i])==false)acceptableColors.add(blockType.colors[i]);
			}
		}


		//dont use the same color as downleft, or downright
		if(x>0 && y>0 && get(x-1,y-1)!=null && get(x-1,y-1).color()!=null )acceptableColors.remove(get(x-1,y-1).color());//upleft
		if(x>0 && y<h()-1 && get(x-1,y+1)!=null && get(x-1,y+1).color()!=null )acceptableColors.remove(get(x-1,y+1).color());//downleft
		if(x>0 && get(x-1,y)!=null && get(x-1,y).color()!=null )acceptableColors.remove(get(x-1,y).color());//left
		if(y<h()-1 && get(x,y+1)!=null && get(x,y+1).color()!=null )acceptableColors.remove(get(x,y+1).color());//down
		if(y>0 && get(x,y-1)!=null && get(x,y-1).color()!=null )acceptableColors.remove(get(x,y-1).color());//up


		if(acceptableColors.size()>0)
		{

			BobColor color = acceptableColors.get(Game().getRandomIntLessThan(acceptableColors.size()));

			Piece p = getRandomPiece(GameType().getPlayingFieldPieceTypes(), GameType().getPlayingFieldBlockTypes());

			for(int i=0; i<p.blocks.size(); i++)
			{
				Block b = p.blocks.get(i);
				b.setColor(color);
			}

			return p;
		}
		else
		return null;

	}



	//=========================================================================================================================
	public Piece dontPutSameColorNextToEachOtherOrReturnNull(int x, int y)
	{//=========================================================================================================================



		ArrayList<BobColor> acceptableColors = new ArrayList<BobColor>();
		for(int b=0;b<GameType().getPlayingFieldBlockTypes().size();b++)
		{
			BlockType blockType = GameType().getPlayingFieldBlockTypes().get(b);

			if(blockType.colors!=null)
			{
				for(int i=0; i<blockType.colors.length; i++)
				if(acceptableColors.contains(blockType.colors[i])==false)acceptableColors.add(blockType.colors[i]);
			}
		}

		//dont use the same color as left, above, or below
		if(x>0&&get(x-1,y)!=null&&get(x-1,y).color()!=null)acceptableColors.remove(get(x-1,y).color());//left
		if(y<h()-1&&get(x,y+1)!=null&&get(x,y+1).color()!=null)acceptableColors.remove(get(x,y+1).color());//down
		if(y>0&&get(x,y-1)!=null&&get(x,y-1).color()!=null)acceptableColors.remove(get(x,y-1).color());//up

		if(acceptableColors.size()>0)
		{
			BobColor color = acceptableColors.get(Game().getRandomIntLessThan(acceptableColors.size()));

			Piece p = getRandomPiece(GameType().getPlayingFieldPieceTypes(), GameType().getPlayingFieldBlockTypes());

			for(int i=0; i<p.blocks.size(); i++)
			{
				Block b = p.blocks.get(i);
				b.setColor(color);
			}

			return p;
		}
		else
		return null;

	}


	//=========================================================================================================================
	public Piece dontPutSameBlockTypeNextToEachOtherOrReturnNull(int x, int y)
	{//=========================================================================================================================



		ArrayList<BlockType> acceptableBlockTypes = new ArrayList<BlockType>();
		for(int i=0;i<GameType().getPlayingFieldBlockTypes().size();i++)acceptableBlockTypes.add(GameType().getPlayingFieldBlockTypes().get(i));


		//dont use the same color as left, above, or below
		if(x>0&&get(x-1,y)!=null)acceptableBlockTypes.remove(get(x-1,y).blockType);//left
		if(y<h()-1&&get(x,y+1)!=null)acceptableBlockTypes.remove(get(x,y+1).blockType);//down
		if(y>0&&get(x,y-1)!=null)acceptableBlockTypes.remove(get(x,y-1).blockType);//up


		if(acceptableBlockTypes.size()>0)
		{
			PieceType pieceType = getRandomPieceType(GameType().getPlayingFieldPieceTypes());
			Piece p = new Piece(game, this, pieceType, acceptableBlockTypes.get(Game().getRandomIntLessThan(acceptableBlockTypes.size())));

			return p;
		}
		else
		return null;
	}

	//=========================================================================================================================
	public Piece putPieceInGridCheckingForFillRules(Piece p, int x, int y)
	{//=========================================================================================================================



		if(GameType().stackDontPutSameColorNextToEachOther)p = dontPutSameColorNextToEachOtherOrReturnNull(x,y);
		if(GameType().stackDontPutSameBlockTypeNextToEachOther)p = dontPutSameBlockTypeNextToEachOtherOrReturnNull(x,y);
		if(GameType().stackDontPutSameColorDiagonalOrNextToEachOtherReturnNull)p = dontPutSameColorDiagonalOrNextToEachOtherReturnNull(x,y);

		if(p!=null)
		{
			setPiece(p,x,y);

			if(GameType().stackLeaveAtLeastOneGapPerRow)
			{

				boolean isFull = true;
				for(int xx=0;xx<w();xx++)
				{
					if(get(xx,y)==null)isFull=false;
				}

				if(isFull==true)
				{
					remove(Game().getRandomIntLessThan(w()),y);
				}

			}
		}

		return p;

	}

	//=========================================================================================================================
	public void randomlyFillEntireGridWithPlayingFieldPieces(int numberOfPieces, int topY)
	{//=========================================================================================================================



		int fieldSize = w()*(h()-topY);


		//override settings amount of prefilled pieces if there are already pieces on the grid.
		int num = getNumberOfFilledCells();
		if(num>0)numberOfPieces = num;

		if(numberOfPieces>=fieldSize)numberOfPieces=fieldSize-1;




		//get old blocks and remove them
		ArrayList<Block> blockList = new ArrayList<Block>();
		for(int y=0;y<h();y++)
		{
			for(int x=0;x<w();x++)
			{
				Block b = remove(x,y);
				if(b!=null&&blockList.contains(b)==false)blockList.add(b);
			}
		}




		for(int i=0;i<numberOfPieces;i++)
		{
			int r = Game().getRandomIntLessThan(fieldSize);

			int x = r%w();
			int y = r/w() + topY;

			int attempt = 0;
			while(get(x,y)!=null&&attempt<fieldSize)
			{

				r = Game().getRandomIntLessThan(fieldSize);

				x = r%w();
				y = r/w() + topY;

				attempt++;
			}

			if(get(x,y)==null)
			{
				Piece p = getRandomPiece(GameType().getPlayingFieldPieceTypes(), GameType().getPlayingFieldBlockTypes());
				putPieceInGridCheckingForFillRules(p,x,y);
			}
		}


		//set the new blocks to the old blocks lastX lastY so there is a neat animation
		for(int y=0;y<h();y++)
		{
			for(int x=0;x<w();x++)
			{
				Block b = get(x,y);
				if(b!=null&&blockList.size()>0)
				{
					Block a = blockList.remove(0);

					b.lastScreenX = a.lastScreenX;
					b.lastScreenY = a.lastScreenY;
					b.ticksSinceLastMovement=0;
				}
			}
		}




	}


	//=========================================================================================================================
	public void buildRandomStackWithPlayingFieldPieces(int numberOfPieces, int topY)
	{//=========================================================================================================================

		//draw grid one block offscreen to allow for scroll
		//screenY+=cellH();
		scrollPlayingFieldY=0;

		//don't put same colors in row or column of 3
		//don't put spaces


		int fieldSize = w()*((h())-topY);


		//override settings amount of prefilled pieces if there are already pieces on the grid.
		int num = getNumberOfFilledCells();
		if(num>0)numberOfPieces = num;

		if(numberOfPieces>=fieldSize)numberOfPieces=fieldSize-1;


		//clearField();


		int piecesPlaced = 0;

		for(int y=h()-1;y>=topY;y--)
		{
			for(int x=0;x<w();x++)
			{
				if(get(x,y)!=null)
				{
					piecesPlaced++;
					continue;
				}
				else
				{
					Piece p = getRandomPiece(GameType().getPlayingFieldPieceTypes(), GameType().getPlayingFieldBlockTypes());
					putPieceInGridCheckingForFillRules(p,x,y);
					piecesPlaced++;
				}
			}
		}


		while(piecesPlaced>numberOfPieces)
		{
			//pick random column
			int x = Game().getRandomIntLessThan(w());

			//remove first piece
			for(int y=0;y<h();y++)
			{
				if(get(x,y)!=null)
				{
					remove(x,y);
					piecesPlaced--;
					break;
				}
			}


		}
	}




	//=========================================================================================================================
	public boolean scrollUpStack(Piece cursorPiece, int amt)
	{//=========================================================================================================================


		scrollPlayingFieldY -= amt;


		// all pieces set lastY so it isnt blurry
		for(int y=0;y<h();y++)
		{
			for(int x=0;x<w();x++)
			{
				Block b = get(x,y);
				if(b!=null)
				{
					b.lastScreenY = b.getScreenY();
				}
			}
		}


		if(scrollPlayingFieldY<0-cellH())
		{

			//die if there is a piece at the top
			for(int x=0;x<w();x++)
			{
				if(get(x,0)!=null)
				{
					scrollPlayingFieldY=0-cellH();
					return false;
				}
			}

			cursorPiece.yGrid-=1;
			if(cursorPiece.yGrid<1)
			{
				cursorPiece.yGrid+=1;
			}


			scrollPlayingFieldY+=cellH();


			//move all pieces up
			for(int y=0;y<h()-1;y++)
			{
				for(int x=0;x<w();x++)
				{
					Block b = remove(x,y+1);
					if(b!=null)
					{
						add(x,y,b);

						// all pieces set lastY so it isnt blurry
						//b.lastScreenX = b.getScreenX();
						//b.lastScreenY = b.getScreenY();

					}
				}
			}



			//create new row of pieces at bottom
			int y = h()-1;
			for(int x=0;x<w();x++)
			{
				Piece p = getRandomPiece(GameType().getPlayingFieldPieceTypes(), GameType().getPlayingFieldBlockTypes());
				putPieceInGridCheckingForFillRules(p,x,y);
			}

		}

		return true;

	}


	//=========================================================================================================================
	public void putGarbageBlock(int x, int y)
	{//=========================================================================================================================

		Piece p = getRandomPiece(GameType().getGarbagePieceTypes(), GameType().getGarbageBlockTypes());
		putPieceInGridCheckingForFillRules(p,x,y);

	}


	//=========================================================================================================================
	public void makeGarbageRowFromCeiling()
	{//=========================================================================================================================
		int y = 0;
		for(int x=0;x<w();x++)
		{
			putGarbageBlock(x, y);
		}
	}

	//=========================================================================================================================
	public void makeGarbageRowFromFloor()
	{//=========================================================================================================================
		//move all rows up one
		//move all pieces up
		for(int y=0;y<h()-1;y++)
		{
			for(int x=0;x<w();x++)
			{
				add(x,y,remove(x,y+1));
			}
		}


		//make last row filled depending on garbage rule
		if(GameType().garbageType == GarbageType.MATCH_BOTTOM_ROW)
		{

			int y = h()-1;
			for(int x=0;x<w();x++)
			{

				if(get(x,y-1)!=null)
				{
					putGarbageBlock(x, y);
				}

			}
		}


		if(GameType().garbageType == GarbageType.RANDOM)
		{

			int y = h()-1;
			for(int x=0;x<w();x++)
			{
				int r = Game().getRandomIntLessThan(1);

				if(r==0)
				{
					putGarbageBlock(x, y);
				}

			}
		}


		if(GameType().garbageType == GarbageType.SET_PATTERN)
		{

			int y = h()-1;
			for(int x=0;x<w();x++)
			{

				if(x!=lastGarbageHoleX)putGarbageBlock(x, y);

			}

			if(garbageHoleDirectionToggle)
			{
				lastGarbageHoleX++;
				if(lastGarbageHoleX>=w())
				{
					lastGarbageHoleX = w()-1;
					garbageHoleDirectionToggle = !garbageHoleDirectionToggle;
				}
			}
			else
			{
				lastGarbageHoleX--;
				if(lastGarbageHoleX<0)
				{
					lastGarbageHoleX = 0;
					garbageHoleDirectionToggle = !garbageHoleDirectionToggle;
				}
			}
		}
	}


	//=========================================================================================================================
	public void cursorSwapBetweenTwoBlocks(Piece cursor)
	{//=========================================================================================================================

		Block a = get(cursor.xGrid,cursor.yGrid);
		Block b = get(cursor.xGrid+1,cursor.yGrid);

		if(a!=null&&a.swappingWith==0&&a.flashingToBeRemoved==false)
		{
			if(b==null||b.swappingWith==0)
			{
				a.swappingWith = 1;
			}
		}

		if(b!=null&&b.swappingWith==0&&b.flashingToBeRemoved==false)
		{
			if(a==null||a.swappingWith==1)
			{
				b.swappingWith = -1;
			}
		}

//		remove(currentPiece.x,currentPiece.y);
//		remove(currentPiece.x+1,currentPiece.y);

//		add(currentPiece.x,currentPiece.y,b);
//		add(currentPiece.x+1,currentPiece.y,a);


	}
	//=========================================================================================================================
	public void cursorSwapHoldingBlockWithGrid(Piece cursor)
	{//=========================================================================================================================

		Block a = get(cursor.xGrid,cursor.yGrid);
		if(a!=null&&a.flashingToBeRemoved==true)return;


		Block b = cursor.holdingBlock;

		cursor.holdingBlock = remove(cursor.xGrid,cursor.yGrid);
		add(cursor.xGrid,cursor.yGrid,b);


	}

	//=========================================================================================================================
	public void cursorRotateBlocks(Piece cursor, MovementType rotation)
	{//=========================================================================================================================

		Block a = get(cursor.xGrid,cursor.yGrid);
		Block b = get(cursor.xGrid+1,cursor.yGrid);
		Block c = get(cursor.xGrid,cursor.yGrid+1);
		Block d = get(cursor.xGrid+1,cursor.yGrid+1);

		if(a!=null&&a.flashingToBeRemoved==true)return;
		if(b!=null&&b.flashingToBeRemoved==true)return;
		if(c!=null&&c.flashingToBeRemoved==true)return;
		if(d!=null&&d.flashingToBeRemoved==true)return;

		if(rotation==MovementType.ROTATE_CLOCKWISE)
		{
			a = remove(cursor.xGrid,cursor.yGrid);
			b = remove(cursor.xGrid+1,cursor.yGrid);
			c = remove(cursor.xGrid,cursor.yGrid+1);
			d = remove(cursor.xGrid+1,cursor.yGrid+1);

			add(cursor.xGrid+1,cursor.yGrid,a);
			add(cursor.xGrid+1,cursor.yGrid+1,b);
			add(cursor.xGrid,cursor.yGrid,c);
			add(cursor.xGrid,cursor.yGrid+1,d);
		}
		if(rotation==MovementType.ROTATE_COUNTERCLOCKWISE)
		{
			a = remove(cursor.xGrid,cursor.yGrid);
			b = remove(cursor.xGrid+1,cursor.yGrid);
			c = remove(cursor.xGrid,cursor.yGrid+1);
			d = remove(cursor.xGrid+1,cursor.yGrid+1);

			add(cursor.xGrid,cursor.yGrid+1,a);
			add(cursor.xGrid,cursor.yGrid,b);
			add(cursor.xGrid+1,cursor.yGrid+1,c);
			add(cursor.xGrid+1,cursor.yGrid,d);
		}

	}

	//=========================================================================================================================
	public boolean continueSwappingBlocks()
	{//=========================================================================================================================


		boolean swappingAny = false;

		for(int y=0;y<h();y++)
		{
			for(int x=0;x<w();x++)
			{
				Block a = get(x,y);
				if(a!=null)
				{
					if(a.swappingWith!=0)
					{
						Block b = get(x+a.swappingWith,y);

						swappingAny = true;

						if(a.swapTicks<17*6)// 6 frames from start to finish
						{
							a.swapTicks+=Game().ticks();
							if(b!=null)b.swapTicks = a.swapTicks;
						}
						else
						{
							a.swapTicks=0;
							if(b!=null)b.swapTicks=0;

							remove(x,y);
							remove(x+a.swappingWith,y);

							add(x,y,b);
							add(x+a.swappingWith,y,a);

							a.swappingWith = 0;
							if(b!=null)b.swappingWith = 0;
						}
					}
				}

			}
		}

		return swappingAny;


	}





	//=========================================================================================================================
	public void scrollBackground()
	{//=========================================================================================================================

		scrollPlayingFieldBackgroundTicks+=Game().ticks();

		if(scrollPlayingFieldBackgroundTicks>scrollTicksSpeed)
		{
			scrollPlayingFieldBackgroundTicks=0;

			// scroll the playingfield background (annoying scrolling blocks)
			if(backgroundScrollX <= 0)backgroundScrollX = (cellW()-1);
			else backgroundScrollX--;

			if(backgroundScrollY <= 0)backgroundScrollY = (cellH()-1);
			else backgroundScrollY--;
		}
	}

	//=========================================================================================================================
	public void shakeSmall()
	{//=========================================================================================================================
		if(effectShakeDurationTicks==0)effectShakeDurationTicks = 300;
		if(effectShakeMaxX==0)effectShakeMaxX = (int)(3*(game.Engine().getWidth()/320));
		if(effectShakeMaxY==0)effectShakeMaxY = (int)(3*(game.Engine().getWidth()/320));
	}

	//=========================================================================================================================
	public void shakeHard()
	{//=========================================================================================================================
		effectShakeDurationTicks = 600;
		effectShakeMaxX = (int)(20*(game.Engine().getWidth()/320));
		effectShakeMaxY = (int)(20*(game.Engine().getWidth()/320));
	}


	//=========================================================================================================================
	public void shakeForeground()
	{//=========================================================================================================================

		shakePlayingFieldTicks+=Game().ticks();

		if(shakePlayingFieldTicks>shakeTicksSpeed)
		{
			shakePlayingFieldTicks=0;

			if(shakePlayingFieldLeftRightToggle==false)
			{
				shakePlayingFieldX++;
				if(shakePlayingFieldX>shakeMaxX)
				{
					shakePlayingFieldLeftRightToggle=true;
					shakePlayingFieldX--;
				}
			}
			else
			{
				shakePlayingFieldX--;
				if(shakePlayingFieldX<-shakeMaxX)
				{
					shakePlayingFieldLeftRightToggle=false;
					shakePlayingFieldX++;
				}
			}
		}
	}



	//=========================================================================================================================
	public void add(int x, int y,Block b)
	{//=========================================================================================================================
		if(b==null)return;

		b.xGrid = x;
		b.yGrid = y;
		b.grid = this;

		if(x<0 || y<0) return; //don't put negative values in grid, but still set the xGrid yGrid since it's still attached to the piece.

		blocks.put(y*w()+x,b);

	}


	//=========================================================================================================================
	public Block get(int x, int y)
	{//=========================================================================================================================

		if(x<0 || y<0) return null;

		return blocks.get(y*w()+x);
	}


	//=========================================================================================================================
	private Block remove(int x, int y)
	{//=========================================================================================================================

		if(x<0 || y<0) return null;

		Block b = blocks.remove(y*w()+x);


//		if(b.piece!=null)
//		{
//			b.piece.blocks.remove(b);
//
//			for(int i=0;i<b.piece.blocks.size();i++)
//			{
//				Block c = b.piece.blocks.get(i);
//				if(c.connectedBlocksByColor.contains(b))c.connectedBlocksByColor.remove(b);
//				if(c.connectedBlocksByPiece.contains(b))c.connectedBlocksByPiece.remove(b);
//			}
//		}


		if(b!=null)
		{
			if(blocks.containsValue(b))
			{
				log.warn("Grid still contains block after removing it. Figure out why!");
				blocks.remove(b);
			}
		}


		return b;

	}


	//=========================================================================================================================
	private void remove(Block b)
	{//=========================================================================================================================

		if(b.xGrid<0||b.yGrid<0)return;

		Block c = remove(b.xGrid,b.yGrid);

		if(c!=b)
		{

			log.error("Removed block at "+b.xGrid+","+b.yGrid+" does not match requested block, must have been two blocks in the same space");

			log.error("Current game:"+Game().currentGameString);
			log.error("Previous game:"+Game().previousGameString);;

			new Exception().printStackTrace();

		}


	}



	//=========================================================================================================================
	public boolean checkLine(int y)
	{//=========================================================================================================================

		for(int x=0;x<w();x++)if(get(x,y)==null)return false;

		return true;
	}


	//=========================================================================================================================
	public ArrayList<Piece> getArrayOfPiecesOnGrid()
	{//=========================================================================================================================
		ArrayList<Piece> piecesOnGrid = new ArrayList<Piece>();
		for(int y=0;y<h();y++)
		{
			for(int x=0;x<w();x++)
			{
				Block b = get(x,y);
				if(b!=null&&b.piece!=null&&piecesOnGrid.contains(b.piece)==false)piecesOnGrid.add(b.piece);
			}
		}
		return piecesOnGrid;

	}


	//=========================================================================================================================
	public ArrayList<Block> checkLines(ArrayList<BlockType> ignoreTypes, ArrayList<BlockType> mustContainAtLeastOneTypes)
	{//=========================================================================================================================

		ArrayList<Block> blocksOnFullLines = null;


		for(int y=h()-1;y>0;y--)
		{


			boolean lineFull = true;

			for(int x=0;x<w();x++)
			{
				Block b = get(x,y);
				if(b==null||(ignoreTypes!=null&&ignoreTypes.contains(b.blockType)))
				{
					lineFull=false;
					break;
				}
			}


			if(lineFull==true)
			{

				if(blocksOnFullLines==null)blocksOnFullLines = new ArrayList<Block>();
				for(int x=0;x<w();x++)
				{
					Block b = get(x,y);
					if(blocksOnFullLines.contains(b)==false)blocksOnFullLines.add(b);

					//if b is a special flashing piece, also remove any blocks on any lines the flashing block is on.
					if(b.piece!=null&&b.piece.pieceType!=null)
					{
						if(
								b.piece.pieceType.clearEveryRowPieceIsOnIfAnySingleRowCleared
								&&b.piece.overrideAnySpecialBehavior==false
						)
						{
							for(int c=0; c<b.connectedBlocksByPiece.size();c++)
							{
								Block connected = b.connectedBlocksByPiece.get(c);
								for(int cx=0;cx<w();cx++)
								{
									Block otherLineBlock = get(cx,connected.yGrid);
									if(otherLineBlock!=null&&blocksOnFullLines.contains(otherLineBlock)==false)blocksOnFullLines.add(otherLineBlock);
								}
							}

							shakeSmall();

							//TODO: play sound flashing piece cleared
						}
					}
				}


			}
		}

		return blocksOnFullLines;

	}


	//=========================================================================================================================
	public boolean doBlocksMatch(Block a, Block b, ArrayList<BlockType> ignoreTypes)
	{//=========================================================================================================================

		if(a==null||b==null){return false;}
		if(a.swappingWith!=0 || b.swappingWith!=0){return false;}//for puzzle, don't check colors that are being swapped
		if(a.flashingToBeRemoved==true || b.flashingToBeRemoved==true){return false;}//for puzzle, don't check colors that are being swapped
		if(ignoreTypes!=null&&(ignoreTypes.contains(a.blockType)||ignoreTypes.contains(b.blockType))){return false;}//for dama, don't add closed in blocks

		if(a.color()!=null&&b.color()!=null&&a.color()==b.color())return true;

		if(a.specialColor()!=null&&b.specialColor()!=null&&a.specialColor()==b.specialColor())return true;

		if(a.blockType.matchAnyColor==true || b.blockType.matchAnyColor==true) return true;

		return false;

	}

	//=========================================================================================================================
	public ArrayList<Block> getConnectedBlocksUpDownLeftRight(Block b)
	{//=========================================================================================================================

		ArrayList<Block> connectedBlocks = new ArrayList<Block>();


		int xOffset = 1;
		if(b.xGrid+xOffset<w())
		{
			Block n = get(b.xGrid+xOffset,b.yGrid);
			if(n!=null)connectedBlocks.add(n);
		}

		if(b.xGrid-xOffset>=0)
		{
			Block n = get(b.xGrid-xOffset,b.yGrid);
			if(n!=null)connectedBlocks.add(n);
		}



		int yOffset = 1;
		if(b.yGrid+yOffset<h())
		{
			Block n = get(b.xGrid,b.yGrid+yOffset);
			if(n!=null)connectedBlocks.add(n);
		}

		if(b.yGrid-yOffset>=0)
		{
			Block n = get(b.xGrid,b.yGrid-yOffset);
			if(n!=null)connectedBlocks.add(n);
		}



		return connectedBlocks;
	}

	//=========================================================================================================================
	public ArrayList<Block> checkRecursiveConnectedRowOrColumn(ArrayList<Block> connectedBlocks, int leastAmountConnected, int startX, int endX, int startY, int endY, ArrayList<BlockType> ignoreTypes, ArrayList<BlockType> mustContainAtLeastOneTypes)
	{//=========================================================================================================================


		for(int y=startY;y<endY;y++)
		{
			for(int x=startX;x<endX;x++)
			{
				ArrayList<Block> connectedToThisBlock = null;

				Block b = get(x,y);

				if(b!=null&&(ignoreTypes==null||ignoreTypes.contains(b.blockType)==false))
				{
					connectedToThisBlock = addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowOrColumnAtLeastAmount(b,connectedToThisBlock,2,startX,endX,startY,endY,ignoreTypes,mustContainAtLeastOneTypes);

					if(connectedToThisBlock!=null)
					{
						//recursively add all connected blocks to each connectedBlock
						int size = connectedToThisBlock.size();
						for(int i=0;i<size;i++)
						{
							connectedToThisBlock = addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowOrColumnAtLeastAmount(connectedToThisBlock.get(i),connectedToThisBlock,2,startX,endX,startY,endY,ignoreTypes,mustContainAtLeastOneTypes);
							if(connectedToThisBlock.size()>size){size = connectedToThisBlock.size(); i=-1;}
						}

						//if we have at least 4 connected pieces in a blob, add to allConnectedBlocks
						if(connectedToThisBlock.size()>=leastAmountConnected)
						{
							if(connectedBlocks==null)connectedBlocks = new ArrayList<Block>();
							for(int i=0;i<connectedToThisBlock.size();i++)
							{
								Block c = connectedToThisBlock.get(i);
								if(connectedBlocks.contains(c)==false)connectedBlocks.add(c);
							}
						}
					}
				}
			}
		}

		if(connectedBlocks!=null&&connectedBlocks.size()>=leastAmountConnected)return connectedBlocks;

		return null;
	}

	// =========================================================================================================================
	public void setColorConnections(ArrayList<BlockType> ignoreTypes, ArrayList<BlockType> mustContainAtLeastOneTypes)
	{// =========================================================================================================================


		for(int y=0;y<h();y++)
		{
			for(int x=0;x<w();x++)
			{
				ArrayList<Block> connectedBlocks = null;

				Block b = get(x,y);
				if(b!=null&&(ignoreTypes==null||ignoreTypes.contains(b.blockType)==false))
				{
					b.connectedBlocksByColor.clear();

					connectedBlocks = addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowOrColumnAtLeastAmount(b,connectedBlocks,2,0,w(),0,h(),ignoreTypes,mustContainAtLeastOneTypes);

					if(connectedBlocks!=null)
					{
						//recursively add all connected blocks to each connectedBlock
						int size = connectedBlocks.size();
						for(int i=0;i<size;i++)
						{
							connectedBlocks = addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowOrColumnAtLeastAmount(connectedBlocks.get(i),connectedBlocks,2,0,w(),0,h(),ignoreTypes,mustContainAtLeastOneTypes);
							if(connectedBlocks.size()>size){size = connectedBlocks.size(); i=-1;}
						}

						//set connections from all blocks to all connected blocks
						if(connectedBlocks.size()>=2)
						{
							for(int i=0;i<connectedBlocks.size();i++)
							{
								Block c = connectedBlocks.get(i);
								if(b!=c&&b.connectedBlocksByColor.contains(b)==false)b.connectedBlocksByColor.add(c);
							}
						}
					}
				}
			}
		}
	}

	//=========================================================================================================================
	public ArrayList<Block> checkBreakerBlocks(int toRow, ArrayList<BlockType> ignoreUnlessTouchingBreakerBlockTypes, ArrayList<BlockType> breakerBlockTypes)
	{//=========================================================================================================================

		ArrayList<Block> breakBlocks = null;

		//check grid for breaker blocks
		//breaker blocks touching any equal color set off that chain

		for(int y=0;y<toRow;y++)
		{
			for(int x=0;x<w();x++)
			{

				ArrayList<Block> connected = null;

				Block b = get(x,y);

				if(b!=null&&breakerBlockTypes.contains(b.blockType))
				{
					//get recursive list of any blocks of the same color it is touching
					//do breaker blocks set off other breaker blocks? yes, of the same color.

					connected = addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowOrColumnAtLeastAmount(b,connected,2,0,w(),0,h(),ignoreUnlessTouchingBreakerBlockTypes,breakerBlockTypes);

					if(connected!=null)
					{
						//recursively add all connected blocks to each connectedBlock
						int size = connected.size();
						for(int i=0;i<size;i++)
						{
							connected = addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowOrColumnAtLeastAmount(connected.get(i),connected,2,0,w(),0,h(),ignoreUnlessTouchingBreakerBlockTypes,null);
							if(connected.size()>size){size = connected.size(); i=-1;}
						}

						//if we have at least 2 connected pieces, this breaker block will explode.
						if(connected.size()>=2)
						{
							if(breakBlocks==null)breakBlocks = new ArrayList<Block>();

							for(int i=0;i<connected.size();i++)
							{
								Block c = connected.get(i);
								if(breakBlocks.contains(c)==false)breakBlocks.add(c);
							}

							//take out any counter pieces it is touching as well
							ArrayList<Block> surroundingBlocks = new ArrayList<Block>();
							surroundingBlocks = getConnectedBlocksUpDownLeftRight(b);
							for(int i=0;i<surroundingBlocks.size();i++)
							{
								Block d = surroundingBlocks.get(i);
								if(ignoreUnlessTouchingBreakerBlockTypes.contains(d.blockType))
								{
									if(breakBlocks.contains(d)==false)breakBlocks.add(d);
								}
							}

						}
					}

				}
			}
		}

		return breakBlocks;



		//DONE when breaker block explodes, also explode any counter blocks it is touching



		//check grid for diamond
		//if diamond sitting on color remove all colors of that color
		//TODO: check exact behavior of this

	}


	//=========================================================================================================================
	public ArrayList<Block> addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowOrColumnAtLeastAmount(Block b, ArrayList<Block> connectedBlocks, int leastInARow,int startX, int endX, int startY, int endY, ArrayList<BlockType> ignoreTypes, ArrayList<BlockType> mustContainAtLeastOneTypes)
	{//=========================================================================================================================



		{
			ArrayList<Block> row = new ArrayList<Block>();
			row.add(b);

			for(int xOffset = 1; b.xGrid+xOffset<endX; xOffset++)//check all blocks starting from this block to the right
			{
				Block n = get(b.xGrid+xOffset,b.yGrid);
				if(doBlocksMatch(b,n,ignoreTypes)){row.add(n);}else {break;}
			}

			for(int xOffset = 1; b.xGrid-xOffset>=startX; xOffset++)//check all blocks starting from this block to the left
			{
				Block n = get(b.xGrid-xOffset,b.yGrid);
				if(doBlocksMatch(b,n,ignoreTypes)){row.add(n);}else {break;}
			}

			if(row.size()>=leastInARow)
			{
				if(connectedBlocks==null)connectedBlocks = new ArrayList<Block>();

				if(mustContainAtLeastOneTypes!=null&&mustContainAtLeastOneTypes.size()>0)
				{
					boolean containsMandatoryBlocks = false;
					for(int i=0;i<row.size();i++)if(mustContainAtLeastOneTypes.contains(row.get(i).blockType))containsMandatoryBlocks=true;
					if(containsMandatoryBlocks==false)row.clear();
				}

				for(int i=0;i<row.size();i++)
				{
					Block c = row.get(i);
					if(connectedBlocks.contains(c)==false)connectedBlocks.add(c);

				}
			}
		}


		{
			ArrayList<Block> column = new ArrayList<Block>();
			column.add(b);


			for(int yOffset = 1; b.yGrid+yOffset<endY; yOffset++)//check all blocks starting from this block to the right
			{
				Block n = get(b.xGrid,b.yGrid+yOffset);
				if(doBlocksMatch(b,n,ignoreTypes)){column.add(n);}else {break;}

			}

			for(int yOffset = 1; b.yGrid-yOffset>=startY; yOffset++)//check all blocks starting from this block to the left
			{
				Block n = get(b.xGrid,b.yGrid-yOffset);
				if(doBlocksMatch(b,n,ignoreTypes)){column.add(n);}else {break;}
			}

			if(column.size()>=leastInARow)
			{
				if(connectedBlocks==null)connectedBlocks = new ArrayList<Block>();

				if(mustContainAtLeastOneTypes!=null&&mustContainAtLeastOneTypes.size()>0)
				{
					boolean containsMandatoryBlocks = false;
					for(int i=0;i<column.size();i++)if(mustContainAtLeastOneTypes.contains(column.get(i).blockType))containsMandatoryBlocks=true;
					if(containsMandatoryBlocks==false)column.clear();
				}

				for(int i=0;i<column.size();i++)
				{
					Block c = column.get(i);
					if(connectedBlocks.contains(c)==false)connectedBlocks.add(c);
				}
			}
		}

		return connectedBlocks;
	}

	//=========================================================================================================================
	public ArrayList<Block> addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfDiagonalAtLeastAmount(Block b, ArrayList<Block> connectedBlocks, int leastInARow,int startX, int endX, int startY, int endY, ArrayList<BlockType> ignoreTypes, ArrayList<BlockType> mustContainAtLeastOneTypes)
	{//=========================================================================================================================


		{
			ArrayList<Block> upLeftDownRight = new ArrayList<Block>();
			upLeftDownRight.add(b);

			for(int xOffset = 1, yOffset = 1; b.xGrid+xOffset<endX&&b.yGrid+yOffset<endY; xOffset++, yOffset++)//down right
			{
				Block n = get(b.xGrid+xOffset,b.yGrid+yOffset);
				if(doBlocksMatch(b,n,ignoreTypes)){upLeftDownRight.add(n);}else {break;}

			}

			for(int xOffset = 1, yOffset = 1; b.xGrid-xOffset>=startX&&b.yGrid-yOffset>=startY; xOffset++, yOffset++)//up left
			{
				Block n = get(b.xGrid-xOffset,b.yGrid-yOffset);
				if(doBlocksMatch(b,n,ignoreTypes)){upLeftDownRight.add(n);}else {break;}
			}

			if(upLeftDownRight.size()>=leastInARow)
			{

				if(connectedBlocks==null)connectedBlocks = new ArrayList<Block>();

				if(mustContainAtLeastOneTypes!=null&&mustContainAtLeastOneTypes.size()>0)
				{
					boolean containsMandatoryBlocks = false;
					for(int i=0;i<upLeftDownRight.size();i++)if(mustContainAtLeastOneTypes.contains(upLeftDownRight.get(i).blockType))containsMandatoryBlocks=true;
					if(containsMandatoryBlocks==false)upLeftDownRight.clear();
				}

				for(int i=0;i<upLeftDownRight.size();i++)
				{
					Block c = upLeftDownRight.get(i);
					if(connectedBlocks.contains(c)==false)connectedBlocks.add(c);
				}

			}
		}


		{
			ArrayList<Block> downLeftUpRight = new ArrayList<Block>();
			downLeftUpRight.add(b);


			for(int xOffset = 1, yOffset = 1; b.xGrid-xOffset>=startX&&b.yGrid+yOffset<endY; xOffset++, yOffset++)//down left
			{
				Block n = get(b.xGrid-xOffset,b.yGrid+yOffset);
				if(doBlocksMatch(b,n,ignoreTypes)){downLeftUpRight.add(n);}else {break;}

			}

			for(int xOffset = 1, yOffset = 1; b.xGrid+xOffset<endX&&b.yGrid-yOffset>=startY; xOffset++, yOffset++)//up right
			{
				Block n = get(b.xGrid+xOffset,b.yGrid-yOffset);
				if(doBlocksMatch(b,n,ignoreTypes)){downLeftUpRight.add(n);}else {break;}
			}

			if(downLeftUpRight.size()>=leastInARow)
			{
				if(connectedBlocks==null)connectedBlocks = new ArrayList<Block>();

				if(mustContainAtLeastOneTypes!=null&&mustContainAtLeastOneTypes.size()>0)
				{
					boolean containsMandatoryBlocks = false;
					for(int i=0;i<downLeftUpRight.size();i++)if(mustContainAtLeastOneTypes.contains(downLeftUpRight.get(i).blockType))containsMandatoryBlocks=true;
					if(containsMandatoryBlocks==false)downLeftUpRight.clear();
				}

				for(int i=0;i<downLeftUpRight.size();i++)
				{
					Block c = downLeftUpRight.get(i);
					if(connectedBlocks.contains(c)==false)connectedBlocks.add(c);
				}
			}
		}

		return connectedBlocks;
	}





	//=========================================================================================================================
	public void renderBackground()
	{//=========================================================================================================================


		float alpha = 0.85f;

		for(int x=-1;x<w();x++)
		{
			for(int y=-1;y<h();y++)
			{

				BobColor color = GameType().gridCheckeredBackgroundColor1;

				if(y%2==0)
				{
					if(x%2==0)color = GameType().gridCheckeredBackgroundColor1;
					else color = GameType().gridCheckeredBackgroundColor2;
				}
				else
				{
					if(x%2==0)color = GameType().gridCheckeredBackgroundColor2;
					else color = GameType().gridCheckeredBackgroundColor1;
				}

				float bgX = bgX() + (x*cellW());
				float bgY = bgY() + (y*cellH());


				GLUtils.drawFilledRectXYWH(bgX,bgY,cellW(),cellH(),color.r(),color.g(),color.b(),alpha);
			}
		}

		float r = GameType().gridCheckeredBackgroundColor1.rf();
		float g = GameType().gridCheckeredBackgroundColor1.gf();
		float b = GameType().gridCheckeredBackgroundColor1.bf();




		//clip sides of background so scroll doesn't look dumb.
		GLUtils.drawFilledRectXYWH
		(
			x()-cellW(),
			y()-cellH(),
			cellW()*(w()+2),
			cellH(),
			r, g, b, alpha
		);

		GLUtils.drawFilledRectXYWH
		(
			x()-cellW(),
			y()-cellH(),
			cellW(),
			cellH()*(h()+1),
			r, g, b, alpha
		);

		GLUtils.drawFilledRectXYWH
		(
			x()+w()*cellW(),
			y()-cellH(),
			cellW(),
			cellH()*(h()+1),
			r, g, b, alpha
		);

		GLUtils.drawFilledRectXYWH
		(
			x()-cellW(),
			y()+h()*cellH(),
			cellW()*(w()+2),
			cellH(),
			r, g, b, alpha
		);


	}



	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================
		for(int x=0;x<w();x++)
		{
			for(int y=0;y<h();y++)
			{
				Block b = get(x,y);
				if(b!=null)
				{
					b.render(x()+x*cellW(),y()+scrollPlayingFieldY+y*cellH(),1.0f,1.0f,true);
				}
			}
		}
	}

	//=========================================================================================================================
	public void renderBlockOutlines()
	{//=========================================================================================================================
		for(int x=0;x<w();x++)
		{
			for(int y=0;y<h();y++)
			{
				Block b = get(x,y);
				if(b!=null)
				{
					b.renderOutlines(x()+x*cellW(),y()+scrollPlayingFieldY+y*cellH(),1.0f);
				}
			}
		}
	}



	//=========================================================================================================================
	public void renderBorder()
	{//=========================================================================================================================






		for(int i=1;i<cellH();i++)
		{



//			float r = GameType().gridBorderColor.rf() - (float)((float)(i-1)/(float)cellH());
//			float g = GameType().gridBorderColor.gf() - (float)((float)(i-1)/(float)cellH());
//			float b = GameType().gridBorderColor.bf() - (float)((float)(i-1)/(float)cellH());


			float ratio = (float)((float)(i-1)/(float)cellH());

			float amt = ratio+0.5f;
			if(amt>1.0f)amt=1.0f;
			amt-=0.5f;

			if(i<3)amt=1.0f;

			float r = GameType().gridBorderColor.rf() - amt;
			float g = GameType().gridBorderColor.gf() - amt;
			float b = GameType().gridBorderColor.bf() - amt;

			if(r<0)r=0;
			if(g<0)g=0;
			if(b<0)b=0;


			GLUtils.drawFilledRectXYWH
			(
				x()-i,
				y()-i,
				cellW()*(w())+(i*2),
				1,
				r, g, b, 1.0f
			);

			GLUtils.drawFilledRectXYWH
			(
				x()-i,
				y()-i,
				1,
				cellH()*(h())+(i*2),
				r, g, b, 1.0f
			);

			GLUtils.drawFilledRectXYWH
			(
				x()+w()*cellW()+i,
				y()-i,
				1,
				cellH()*(h())+(i*2)+1,
				r, g, b, 1.0f
			);

			GLUtils.drawFilledRectXYWH
			(
				x()-i,
				y()+h()*cellH()+i,
				cellW()*(w())+(i*2)+1,
				1,
				r, g, b, 1.0f
			);


		}





	}

	//=========================================================================================================================
	public void renderTransparentOverLastRow()
	{//=========================================================================================================================

		GLUtils.drawFilledRectXYWH(x(),y()+scrollPlayingFieldY+(h()-1)*cellH(),w()*cellW(),cellH()+1,0,0,0,0.5f);

	}



	//=========================================================================================================================
	public void renderGhostPiece(Piece currentPiece)
	{//=========================================================================================================================
		int ghostY=currentPiece.yGrid;
		for(int y=ghostY;y<h();y++)
		{

			if(doesPieceFit(currentPiece,currentPiece.xGrid,y)==true)
			{
				ghostY=y;
			}
			else
			{
				break;
			}
		}

		if(ghostY!=currentPiece.yGrid)
		{

			float x=x()+currentPiece.xGrid*cellW();
			float y=y()+ghostY*cellH();

			float alpha = ((float)(ghostY - currentPiece.yGrid)) / ((float)h());
			currentPiece.renderGhost(x,y,alpha);
		}
	}


	//=========================================================================================================================
	public boolean isWithinBounds(Piece piece, int x, int y)
	{//=========================================================================================================================

		for(int b=0;b<piece.blocks.size();b++)if(x+piece.blocks.get(b).xInPiece>=w()||x+piece.blocks.get(b).xInPiece<0||y+piece.blocks.get(b).yInPiece>=h())return false;

		return true;

	}


	// =========================================================================================================================
	public boolean isHittingLeft(Piece piece)
	{// =========================================================================================================================
		return isHittingLeft(piece,piece.xGrid,piece.yGrid);
	}


	// =========================================================================================================================
	public boolean isHittingLeft(Piece piece, int x, int y)
	{// =========================================================================================================================

		if(x<0)return true;

		//for(int b=0;b<piece.blocksPerPiece;b++)if(y+piece.block[b].yOffset<0)return false;

		for(int b=0;b<piece.blocks.size();b++)if(x+piece.blocks.get(b).xInPiece<0)return true;


		for(int b=0;b<piece.blocks.size();b++)if(x+piece.blocks.get(b).xInPiece<x&&get(x+piece.blocks.get(b).xInPiece,y+piece.blocks.get(b).yInPiece)!=null)return true;
		return false;
	}


	// =========================================================================================================================
	public boolean isHittingRight(Piece piece)
	{// =========================================================================================================================
		return isHittingRight(piece,piece.xGrid,piece.yGrid);
	}


	// =========================================================================================================================
	public boolean isHittingRight(Piece piece, int x, int y)
	{// =========================================================================================================================

		if(x>=w())return true;

		//for(int b=0;b<piece.blocksPerPiece;b++)if(y+piece.block[b].yOffset<0)return false;

		for(int b=0;b<piece.blocks.size();b++)if(x+piece.blocks.get(b).xInPiece>=w())return true;

		for(int b=0;b<piece.blocks.size();b++)if(x+piece.blocks.get(b).xInPiece>x&&get(x+piece.blocks.get(b).xInPiece,y+piece.blocks.get(b).yInPiece)!=null)return true;
		return false;

	}

	// =========================================================================================================================
	public boolean doesPieceFit(Piece piece)
	{// =========================================================================================================================
		return doesPieceFit(piece,piece.xGrid,piece.yGrid);
	}


	// =========================================================================================================================
	public boolean doesPieceFit(Piece piece, int x, int y)
	{// =========================================================================================================================


		if(isWithinBounds(piece,x,y)==false)return false;
		for(int b=0;b<piece.blocks.size();b++)if(x+piece.blocks.get(b).xInPiece<0||x+piece.blocks.get(b).xInPiece>=w())return false;
		for(int b=0;b<piece.blocks.size();b++)if(y+piece.blocks.get(b).yInPiece>=0&&get(x+piece.blocks.get(b).xInPiece,y+piece.blocks.get(b).yInPiece)!=null)return false;

		return true;

	}
	// =========================================================================================================================
	public void moveToAndDelete(Block b, int x, int y)
	{// =========================================================================================================================
		b.lastScreenX = b.getScreenX();
		b.lastScreenY = b.getScreenY();
		b.ticksSinceLastMovement=0;

		add(x,y,b);
		deleteBlock(b);
	}

	// =========================================================================================================================
	public void deleteBlock(Block b)
	{// =========================================================================================================================

		remove(b);



		b.disappearing=true;
		if(Game().disappearingBlocks.contains(b)==false)Game().disappearingBlocks.add(b);



		for(int i=0;i<b.connectedBlocksByColor.size();i++)
		{
			//remove this block from its connected blocks connectedBlocks list.
			Block c = b.connectedBlocksByColor.get(i);
			c.connectedBlocksByColor.remove(b);
		}
		b.connectedBlocksByColor.clear();



		for(int i=0;i<b.connectedBlocksByPiece.size();i++)
		{
			//remove this block from its connected blocks connectedBlocks list.
			Block c = b.connectedBlocksByPiece.get(i);
			c.connectedBlocksByPiece.remove(b);
		}
		b.connectedBlocksByPiece.clear();


		if(b.piece!=null)
		{
			for(int i=0;i<b.piece.blocks.size();i++)if(b.piece.blocks.get(i)==b)b.piece.blocks.remove(b);
		}


//		b.xInPiece = -1;
//		b.yInPiece = -1;
//		b.xGrid = -1;
//		b.yGrid = -1;


	}


	// =========================================================================================================================
	public void setPiece(Piece piece)
	{// =========================================================================================================================
		setPiece(piece,piece.xGrid,piece.yGrid);

	}

	// =========================================================================================================================
	public void disappearBlock(Block b, int x, int y)
	{// =========================================================================================================================

		b.xGrid = x+b.xInPiece;
		b.yGrid = y+b.yInPiece;

		b.grid = this;

		b.setInGrid = true;
		b.locking = true;
		b.disappearing=true;

		if(Game().disappearingBlocks.contains(b)==false)Game().disappearingBlocks.add(b);
	}

	// =========================================================================================================================
	public void setPiece(Piece piece,int x,int y)
	{// =========================================================================================================================
		if(isWithinBounds(piece,x,y)==false){log.error("Tried to set Piece outside of Grid bounds");return;}



		if(piece.pieceType!=null&&piece.pieceType.disappearOnceSetInGrid==true)
		{
			piece.setInGrid = true;
			for(int i=0;i<piece.blocks.size();i++)
			{
				Block b = piece.blocks.get(i);
				disappearBlock(b,x,y);
			}

			return;
		}







		for(int i=0;i<piece.blocks.size();i++)
		{
			Block b = piece.blocks.get(i);

			add(x+b.xInPiece,y+b.yInPiece,b);

			b.setInGrid = true;
			b.locking = true;

		}

		for(int i=0;i<piece.blocks.size();i++)
		{
			Block b = piece.blocks.get(i);
			if(b.blockType.whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndDisappear.size()>0)
			{
				remove(x+b.xInPiece,y+b.yInPiece);
				piece.blocks.remove(b);
				disappearBlock(b,x,y);
				i=-1;

				ArrayList<Block> surroundingBlocks = getConnectedBlocksUpDownLeftRight(b);
				for(int k=0;k<surroundingBlocks.size();k++)
				{
					Block touchingBlock = surroundingBlocks.get(k);

					if(touchingBlock!=b)
					{
						for(int s=0;s<b.blockType.whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndDisappear.size();s++)
						{
							TurnFromBlockTypeToType turn = b.blockType.whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndDisappear.get(s);

							if(touchingBlock.blockType == turn.fromType)touchingBlock.blockType = turn.toType;
						}
					}
				}

			}
		}


		piece.setInGrid = true;


	}



	// =========================================================================================================================
	public boolean moveDownLinesAboveBlankLinesOneLine()
	{// =========================================================================================================================

		boolean moved = false;

		//TODO: make sure y>=0 is OK, i changed this from >0
		for(int y=h()-1;y>=0;y--)//notice h()-1 because it "grabs" the piece above it
		{

			boolean lineIsBlank = true;
			for(int x=0;x<w();x++)
			{
				if(get(x,y)!=null)lineIsBlank=false;
			}

			if(lineIsBlank==true)
			{
				for(int x=0;x<w();x++)
				{
					Block b = get(x,y-1);
					if(b!=null)
					{
						remove(x,y-1);
						add(x,y,b);

						moved=true;
					}
				}
			}
		}

		return moved;
	}

	//=========================================================================================================================
	public boolean moveDownDisconnectedBlocksAboveBlankSpacesOneLine(ArrayList<BlockType> ignoreTypes)
	{//=========================================================================================================================

		boolean moved = false;

		for(int y=h()-2;y>=0;y--)//notice h()-2 because it "pushes" the piece to the line below it
		{
			for(int x=0;x<w();x++)
			{

				Block b = get(x,y);

				if(b!=null&&(ignoreTypes==null||ignoreTypes.contains(b.blockType)==false))
				{

					if(b.xGrid!=x||b.yGrid!=y)
					{
						log.error("xyGrid does not match! b.xGrid:"+b.xGrid+" b.yGrid:"+b.yGrid+" x:"+x+" y:"+y);
						new Exception().printStackTrace();
					}


					Block c = null;
					for(int i=0;i<b.connectedBlocksByPiece.size();i++)
					{
						Block temp = b.connectedBlocksByPiece.get(i);
						if(blocks.containsValue(temp)==true){c=temp; break;}
					}


					if(c==null)
					{

						if(get(x,y+1)==null)//if there is no connected block, just move the block down one
						{
							remove(b);
							add(x,y+1,b);

							moved=true;
						}

					}
					else
					{

						for(int i=0;i<b.connectedBlocksByPiece.size();i++)
						{

							Block temp = b.connectedBlocksByPiece.get(i);
							if(blocks.containsValue(temp)==true&&c!=b)c=temp;
							else continue;

							//if our connected block is above us and there is nothing below us, move us both down
							if(c.yGrid==b.yGrid-1 && c.xGrid==b.xGrid)
							{

								if(get(x,y+1)==null)
								{
									remove(b);
									add(x,y+1,b);

									remove(c);
									add(x,y,c);

									moved=true;
								}

							}
							else
							//if our connected block is below us and there is nothing below it, that will be handled already when it cycles through

							//if our connected block is to the left or right and there is nothing underneath it, move us down
							if((c.xGrid==b.xGrid-1 || c.xGrid==b.xGrid+1) && c.yGrid == b.yGrid)
							{

								if(get(b.xGrid,y+1)==null && get(c.xGrid,y+1)==null)
								{
									remove(b);
									add(b.xGrid,y+1,b);

									remove(c);
									add(c.xGrid,y+1,c);

									moved=true;
								}

							}

						}
					}
				}
			}
		}

		return moved;
	}


	//=========================================================================================================================
	public boolean moveDownAnyBlocksAboveBlankSpacesOneLine(ArrayList<BlockType> ignoreTypes)
	{//=========================================================================================================================

		boolean moved = false;

		for(int y=h()-2;y>=0;y--)//notice h()-2 because it "pushes" the piece to the line below it
		{
			for(int x=0;x<w();x++)
			{
				Block b = get(x,y);

				if(b!=null&&(ignoreTypes==null||ignoreTypes.contains(b.blockType)==false))
				{
					if(get(x,y+1)==null)
					{
						remove(x,y);
						add(x,y+1,b);

						moved=true;
					}
				}
			}
		}

		return moved;
	}









	// =========================================================================================================================
	public void setRandomBlockColors()
	{// =========================================================================================================================
//		for(int x=0;x<w();x++)
//		{
//			for(int y=0;y<h();y++)
//			{
//				if(get(x,y)!=null)
//				{
//					if(get(x,y).renderColor==get(x,y).color)get(x,y).renderColor = get(x,y).getRandomColor();
//					else get(x,y).renderColor = get(x,y).color;
//				}
//			}
//		}
	}



	// =========================================================================================================================
	public void setRandomMatrixBlockColors()
	{// =========================================================================================================================
//
//		backgroundColor1 = new BobColor(0.0f,BobsGame.randLessThanFloat(1.0f),0.0f);
//		backgroundColor2 = new BobColor(0.0f,BobsGame.randLessThanFloat(1.0f),0.0f);
//
//
//		for(int x=0;x<w();x++)
//		{
//			for(int y=0;y<h();y++)
//			{
//				if(get(x,y)!=null)
//				{
//					get(x,y).renderColor = (Block.getRandomMatrixColor());
//
//				}
//			}
//		}
	}



	// =========================================================================================================================
	public void setRandomWholePieceColors(boolean grayscale, Piece currentPiece, ArrayList<Piece> nextPieces)
	{// =========================================================================================================================

		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
//
//		//make array of previously used colors
//		ArrayList<BobColor> previousColors = new ArrayList<BobColor>();
//
//		for(int x=0;x<w();x++)
//		{
//			for(int y=0;y<h();y++)
//			{
//				if(get(x,y)!=null)
//				{
//					if(previousColors.contains(get(x,y).color)==false)previousColors.add(get(x,y).color);
//				}
//			}
//		}
//
//		if(currentPiece!=null)
//		{
//			for(int b=0;b<currentPiece.blocks.size();b++)
//			{
//				if(previousColors.contains(currentPiece.blocks.get(b).color)==false)previousColors.add(currentPiece.blocks.get(b).color);
//			}
//		}
//		if(nextPieces!=null)
//		{
//			for(int p=0;p<nextPieces.length;p++)
//			{
//				Piece piece = nextPieces[p];
//
//				for(int b=0;b<piece.blocks.size();b++)
//				{
//					if(previousColors.contains(piece.blocks.get(b).color)==false)previousColors.add(piece.blocks.get(b).color);
//				}
//			}
//		}
//
//
//		Piece.setRandomPieceColors(grayscale);
//
//		//set new color based on index of old color
//		for(int x=0;x<w();x++)
//		{
//			for(int y=0;y<h();y++)
//			{
//				if(get(x,y)!=null)
//				{
//					int i = previousColors.indexOf(get(x,y).color);
//					if(i>=0)get(x,y).setColor(Piece.colors[i]);
//				}
//			}
//		}
//
//
//		if(currentPiece!=null)
//		{
//			for(int b=0;b<currentPiece.blocks.size();b++)
//			{
//				int i = previousColors.indexOf(currentPiece.blocks.get(b).color);
//				if(i>=0)currentPiece.blocks.get(b).setColor(Piece.colors[i]);
//			}
//		}
//
//
//		if(nextPieces!=null)
//		{
//			for(int p=0;p<nextPieces.length;p++)
//			{
//				Piece piece = nextPieces[p];
//				for(int b=0;b<piece.blocks.size();b++)
//				{
//					int i = previousColors.indexOf(piece.blocks.get(b).color);
//					if(i>=0)piece.blocks.get(b).setColor(Piece.colors[i]);
//				}
//			}
//		}


	}
	// =========================================================================================================================
	public void setRandomPieceGrayscaleColors(Piece currentPiece, ArrayList<Piece> nextPieces)
	{// =========================================================================================================================
		setRandomWholePieceColors(true,currentPiece,nextPieces);
	}






	// =========================================================================================================================
	public boolean isAnythingAboveThreeQuarters()
	{// =========================================================================================================================
		for(int x=0;x<w();x++)
		{
			for(int y=0;y<h();y++)
			{
				if(get(x,y)!=null)
				{
					if(y<h()/4)
					{
						return true;
					}
				}
			}
		}
		return false;
	}


	// =========================================================================================================================
	public void doDeathSequence()
	{// =========================================================================================================================


		if(deadX<w())
		{


			Piece p = getRandomPiece();
			for(int i=0;i<p.blocks.size();i++)
			{
				Block b = p.blocks.get(i);
				b.lastScreenX = x()+(deadX+b.xInPiece)*cellW();
				b.lastScreenY = y()+(deadY+b.yInPiece)*cellH()+scrollPlayingFieldY;
			}


			Block d = get(deadX,deadY);
			if(d!=null)
			{
				for(int i=0;i<d.piece.blocks.size();i++)
				{
					Block b = d.piece.blocks.get(i);
					deleteBlock(b);
				}
			}

			if(doesPieceFit(p,deadX,deadY)&&deadY+p.getLowestOffsetY()>2)
			{
				//if(isWithinBounds(p,deadX,deadY))
				{
					setPiece(p,deadX,deadY);
					deadX+=p.getWidth();
					deadY-=p.getHeight();
				}
			}
			else
			{
				deadX+=Game().getRandomIntLessThan(3);
				deadY-=Game().getRandomIntLessThan(3);
			}



//			for(int i=0;i<p.blocks.size();i++)
//			{
//				Block b = p.blocks.get(i);
//				deleteBlock(b);
//			}


			//deadX++;

			if(deadY<0)
			{
				deadY=h()-1;
			}

			if(deadX>=w())
			{
				deadX=0;

				//deadY--;
//				if(deadY<0)
//				{
//
//					deadY=h()-1;
//				}
			}
		}
	}




	//=========================================================================================================================
	public PieceType getRandomSpecialPieceTypeFromArrayExcludingNormalPiecesOrNull(ArrayList<PieceType> array)
	{//=========================================================================================================================



		ArrayList<PieceType> randomBag = new ArrayList<PieceType>();

		for(int i=0;i<array.size();i++)
		{
			PieceType p = array.get(i);
			if(p.frequencySpecialPieceTypeOnceEveryNPieces!=0)
			{
				if(Game().createdPiecesCounterForFrequencyPieces>=p.frequencySpecialPieceTypeOnceEveryNPieces-1)
				{
					randomBag.add(p);
				}
			}
		}



		if(randomBag.size()>0)
		{
			Game().createdPiecesCounterForFrequencyPieces=0;

			PieceType p = randomBag.get(Game().getRandomIntLessThan(randomBag.size()));
			return p;
		}





//		int randomTotal = 1;
//		PieceType emptyPieceType = new PieceType();
//		randomBag.add(emptyPieceType);
//		for(int i=0;i<array.size();i++)
//		{
//			PieceType b = array.get(i);
//			//if(b.randomSpecialPieceChanceOneOutOf>0)randomTotal*=b.randomSpecialPieceChanceOneOutOf;
//		}

//		for(int n=0;n<randomTotal;n++)randomBag.add(emptyPieceType);




		for(int i=0;i<array.size();i++)
		{

			PieceType b = array.get(i);

			if(b.randomSpecialPieceChanceOneOutOf>0)
			if(Game().getRandomIntLessThan(b.randomSpecialPieceChanceOneOutOf)==0)randomBag.add(b);
		}


		if(randomBag.size()>0)
		{
			PieceType p = randomBag.get(Game().getRandomIntLessThan(randomBag.size()));
			//if(p!=emptyPieceType)
			return p;
		}

		return null;

	}



	//=========================================================================================================================
	public PieceType getRandomPieceTypeFromArrayExcludingSpecialPieceTypes(ArrayList<PieceType> array)
	{//=========================================================================================================================

		ArrayList<PieceType> randomBag = new ArrayList<PieceType>();

		for(int i=0;i<array.size();i++)
		{
			PieceType b = array.get(i);
			if(b.randomSpecialPieceChanceOneOutOf==0&&b.frequencySpecialPieceTypeOnceEveryNPieces==0)
			{
				randomBag.add(b);
			}
		}

		if(randomBag.size()>0)
		{
			PieceType b = randomBag.get(Game().getRandomIntLessThan(randomBag.size()));
			return b;
		}

		return new PieceType();

	}


	//=========================================================================================================================
	public ArrayList<Piece> getBagOfOneOfEachNonRandomNormalPieces()
	{//=========================================================================================================================

		ArrayList<Piece> tempBag = new ArrayList<Piece>();
		for(int i=0;i<GameType().getNormalPieceTypes().size();i++)
		{
			PieceType type = GameType().getNormalPieceTypes().get(i);

			if(type.randomSpecialPieceChanceOneOutOf==0&&type.frequencySpecialPieceTypeOnceEveryNPieces==0)
			{
				Piece tempPiece = new Piece(Game(), this, type, GameType().getNormalBlockTypes());
				tempBag.add(tempPiece);
			}
		}

		return tempBag;

	}


	//=========================================================================================================================
	public Piece getPieceFromNormalPieceRandomBag()
	{//=========================================================================================================================


		Piece piece = null;

		if(randomBag==null)
		{

			randomBag = new ArrayList<Piece>();
			ArrayList<Piece> tempBag = getBagOfOneOfEachNonRandomNormalPieces();

			while(tempBag.size()>0)
			{

				int i = Game().getRandomIntLessThan(tempBag.size());
				if(randomBag.size()==0)
				{
					while(GameType().isFirstPieceTypeAllowed(tempBag.get(i).pieceType)==false)
					{
						i = Game().getRandomIntLessThan(tempBag.size());
					}
				}

				randomBag.add(tempBag.get(i));
				tempBag.remove(i);
			}

		}


		if(randomBag.size()==0)
		{
			ArrayList<Piece> tempBag = getBagOfOneOfEachNonRandomNormalPieces();
			while(tempBag.size()>0)
			{
				int i = Game().getRandomIntLessThan(tempBag.size());
				randomBag.add(tempBag.get(i));
				tempBag.remove(i);
			}
		}

		piece = randomBag.get(0);
		randomBag.remove(0);

		return piece;

	}

	//=========================================================================================================================
	public Piece getRandomPiece()
	{//=========================================================================================================================

		Piece piece = null;

		//make piece
		{

			PieceType pieceType = getRandomSpecialPieceTypeFromArrayExcludingNormalPiecesOrNull(GameType().getNormalPieceTypes());

			if(GameType().currentPieceRule_getNewPiecesRandomlyOutOfBagWithOneOfEachPieceUntilEmpty)
			{
				if(pieceType!=null)
				{
					piece = new Piece(Game(), this, pieceType, GameType().getNormalBlockTypes());
				}
				else
				{
					piece = getPieceFromNormalPieceRandomBag();
				}
			}
			else
			{
				if(pieceType==null)pieceType = getRandomPieceTypeFromArrayExcludingSpecialPieceTypes(GameType().getNormalPieceTypes());
				piece = new Piece(Game(), this, pieceType, GameType().getNormalBlockTypes());
			}


		}


		return piece;

	}









	//=========================================================================================================================
	public Piece getRandomPiece(ArrayList<PieceType> pieceArray, ArrayList<BlockType> blockArray)
	{//=========================================================================================================================

		Piece piece = new Piece(Game(), this, getRandomPieceType(pieceArray), blockArray);
		return piece;

	}



	//=========================================================================================================================
	public PieceType getRandomPieceType(ArrayList<PieceType> array)
	{//=========================================================================================================================

		PieceType pieceType = getRandomSpecialPieceTypeFromArrayExcludingNormalPiecesOrNull(array);
		if(pieceType==null)pieceType = getRandomPieceTypeFromArrayExcludingSpecialPieceTypes(array);
		return pieceType;

	}


	//=========================================================================================================================
	public BlockType getRandomBlockType(ArrayList<BlockType> array)
	{//=========================================================================================================================

		BlockType blockType = getRandomSpecialBlockTypeFromArrayExcludingNormalBlocksOrNull(array);
		if(blockType==null)blockType = getRandomBlockTypeFromArrayExcludingSpecialBlockTypes(array);
		return blockType;

	}







	//=========================================================================================================================
	public BlockType getRandomSpecialBlockTypeFromArrayExcludingNormalBlocksOrNull(ArrayList<BlockType> array)
	{//=========================================================================================================================


		ArrayList<BlockType> randomBag = new ArrayList<BlockType>();

		for(int i=0;i<array.size();i++)
		{

			BlockType b = array.get(i);
			if(b.frequencySpecialBlockTypeOnceEveryNPieces!=0)
			{
				if(Game().createdPiecesCounterForFrequencyPieces>=b.frequencySpecialBlockTypeOnceEveryNPieces-1)
				{
					randomBag.add(b);
				}
			}

		}


		if(randomBag.size()>0)
		{

			Game().createdPiecesCounterForFrequencyPieces=0;

			BlockType b = randomBag.get(Game().getRandomIntLessThan(randomBag.size()));
			return b;

		}



//		int randomTotal = 1;
//		BlockType emptyBlockType = new BlockType();
//		randomBag.add(emptyBlockType);
//		for(int i=0;i<array.size();i++)
//		{
//			BlockType b = array.get(i);
//			if(b.randomSpecialBlockChanceOneOutOf>0)randomTotal*=b.randomSpecialBlockChanceOneOutOf;
//		}

//		for(int n=0;n<randomTotal;n++)randomBag.add(emptyBlockType);


		for(int i=0;i<array.size();i++)
		{
			BlockType b = array.get(i);
			if(b.randomSpecialBlockChanceOneOutOf>0)
				if(Game().getRandomIntLessThan(b.randomSpecialBlockChanceOneOutOf)==0)randomBag.add(b);

//			for(int n=0;n<randomTotal/b.randomSpecialBlockChanceOneOutOf;n++)randomBag.add(b);


		}

		if(randomBag.size()>0)
		{

			BlockType b = randomBag.get(Game().getRandomIntLessThan(randomBag.size()));

//			if(b!=emptyBlockType)
			return b;

		}

		return null;

	}



	//=========================================================================================================================
	public BlockType getRandomBlockTypeFromArrayExcludingSpecialBlockTypes(ArrayList<BlockType> array)
	{//=========================================================================================================================

		ArrayList<BlockType> randomBag = new ArrayList<BlockType>();

		for(int i=0;i<array.size();i++)
		{
			BlockType b = array.get(i);

			if(b.isSpecialType()==false)
			{
				randomBag.add(b);
			}
		}

		if(randomBag.size()>0)
		{
			BlockType b = randomBag.get(Game().getRandomIntLessThan(randomBag.size()));
			return b;
		}

		return new BlockType(BobsGame.squareName,null,BobColor.gray);

	}



	//=========================================================================================================================
	public boolean areAnyBlocksPopping()
	{//=========================================================================================================================

		for(int y=0;y<h();y++)
		{
			for(int x=0;x<w();x++)
			{
				Block b = get(x,y);

				if(b!=null)
				{
					if(b.popping)return true;
				}
			}
		}
		return false;
	}











}
