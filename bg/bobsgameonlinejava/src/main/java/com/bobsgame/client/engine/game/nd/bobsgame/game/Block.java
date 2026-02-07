package com.bobsgame.client.engine.game.nd.bobsgame.game;

import java.util.ArrayList;

import org.slf4j.LoggerFactory;

import com.bobsgame.client.Texture;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.entity.Sprite;
import com.bobsgame.client.engine.game.nd.bobsgame.BobsGame;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.SpriteAnimationSequence;


//=========================================================================================================================
public class Block
{// =========================================================================================================================


	transient static Logger log = (Logger) LoggerFactory.getLogger(Block.class);

	transient public GameLogic game = null;
	transient public Grid grid = null;
	transient public Piece piece = null;
	transient public ArrayList<Block> connectedBlocksByPiece = new ArrayList<Block>();
	transient public ArrayList<Block> connectedBlocksByColor = new ArrayList<Block>();


	public int xInPiece = 0;//offset in Piece() block is in
	public int yInPiece = 0;

	public int xGrid = -1;
	public int yGrid = -1;



	public BlockType blockType = null;

	private BobColor color = null;



	public float effectAlphaFrom = 0.5f;
	public float effectAlphaTo = 0.8f;
	public long effectFadeTicksPerPhase = 1000;
	float effectAlpha = effectAlphaFrom;
	long effectFadeTicks = 0;
	boolean effectFadeInOutToggle = false;



	public float colorFlashFrom = 0.0f;
	public float colorFlashTo = 1.0f;
	public long colorFlashTicksPerPhase = 100;
	float colorFlash = colorFlashFrom;
	long colorFlashTicks = 0;
	boolean colorFlashInOutToggle = false;




	public boolean overrideAnySpecialBehavior = false;

	public int swappingWith = 0; //-1 left  0 none  1 right
	public int swapTicks = 0;
	public boolean flashingToBeRemoved = false;
	public boolean flashingToBeRemovedLightDarkToggle = false;


	public boolean setInGrid = false;
	public boolean locking = false;
	public int lockingAnimationFrame = 0;
	public int lockAnimationFrameTicks = 0;


	public boolean disappearing = false;
	public float disappearingAlpha = 1.0f;

	public float lastScreenX = -1;
	public float lastScreenY = -1;

	public long ticksSinceLastMovement = 0;

	boolean slamming = false;
	long ticksSinceSlam = 0;
	float slamX = 0;
	float slamY = 0;


	public static enum AnimationState
	{
		NORMAL,
		DROPPING,
		TOUCHING_BOTTOM,
		SET_AT_BOTTOM,
		FLASHING,
		REMOVING,
		PRESSURE,
	}

	public AnimationState animationState = AnimationState.NORMAL;
	public int animationFrame = 0;
	public int animationFrameTicks = 0;
	public int animationFrameSpeed = 100;



	public int counterCount=-2;

	public boolean didFlashingColoredDiamond = false;
	public boolean ateBlocks = false;//for pacman type
	public int direction = -1;//for pacman type
	public int directionChangeTicks = 0;//for pacman type

	public int UP=0;
	public int LEFT=1;
	public int DOWN=2;
	public int RIGHT=3;

	int customInterpolationTicks = -1;//used for pacman

	public boolean popping = false;

	public boolean panic = false;

	//=========================================================================================================================
	public Block(GameLogic game, Grid grid, Piece piece, BlockType blockType)
	{//=========================================================================================================================

		this.game = game;
		this.grid = grid;
		this.piece = piece;
		this.blockType = blockType;

	}



	public int cellW()
	{
		return Game().cellW();
	}

	public int cellH()
	{
		return Game().cellH();
	}

	public int blockW()
	{
		return Game().blockWidth;
	}

	public int blockH()
	{
		return Game().blockHeight;
	}

	public GameType GameType()
	{
		return Game().GameType();
	}

	public GameLogic Game()
	{
		return game;
	}
	public BobColor color()
	{
		return color;
	}
	public BobColor specialColor()
	{
		if(blockType==null)return null;

		return blockType.specialColor;
	}


	// =========================================================================================================================
	public void update()
	{// =========================================================================================================================



		effectFadeTicks+=Game().ticks();

		ticksSinceLastMovement+=Game().ticks();


		if(slamming)ticksSinceSlam+=Game().ticks();


		if(locking)
		{
			lockAnimationFrameTicks+=Game().ticks();
			if(lockAnimationFrameTicks>20)
			{
				lockAnimationFrameTicks=0;
				if(lockingAnimationFrame<8)
				{
					lockingAnimationFrame++;
				}
				else
				{
					lockingAnimationFrame=0;
					locking=false;
				}
			}
		}

		if(disappearing)
		{
			if(disappearingAlpha>0.0f)
			{
				disappearingAlpha-=(float)Game().ticks()*0.005f;

			}

			if(disappearingAlpha<0.0f)disappearingAlpha=0.0f;

			if(disappearingAlpha==0.0f)
			{
				disappearing=false;
				Game().disappearingBlocks.remove(this);
			}
		}

		if(popping)
		{
			if(animationFrame==-1)
			{
				popping=false;
				blockType = blockType.ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType;
			}
		}

		animationFrameTicks-=Game().ticks();
		if(animationFrameTicks<=0)
		{
			if(animationFrame>=0)
			{
				animationFrameTicks=animationFrameSpeed;
				animationFrame++;
			}
			else
			if(animationFrame==-1)
			{
				animationFrame++;
				animationFrameTicks = animationFrameSpeed;
				if(GameType().blockAnimationTicksRandomUpToBetweenLoop>0)animationFrameTicks+=Game().getRandomIntLessThan(GameType().blockAnimationTicksRandomUpToBetweenLoop);
			}
		}


		if(blockType.pacmanType&&ateBlocks==false)
		{
			if(setInGrid)
			{
				ateBlocks = true;
				customInterpolationTicks = 1000;

				int x = xGrid;
				int y = yGrid;

				if(direction==UP)
				{

					for(int yy=y;yy>=0;yy--)if(grid.get(x,yy)!=null){grid.deleteBlock(grid.get(x,yy));}
					grid.moveToAndDelete(this,x,0);
				}
				else
				if(direction==DOWN)
				{

					for(int yy=y;yy<grid.h();yy++)if(grid.get(x,yy)!=null){grid.deleteBlock(grid.get(x,yy));}
					grid.moveToAndDelete(this,x,grid.h()-1);
				}
				else
				if(direction==LEFT)
				{

					for(int xx=x;xx>=0;xx--)if(grid.get(xx,y)!=null){grid.deleteBlock(grid.get(xx,y));}
					grid.moveToAndDelete(this,0,y);
				}
				else
				if(direction==RIGHT)
				{

					for(int xx=x;xx<grid.w();xx++)if(grid.get(xx,y)!=null){grid.deleteBlock(grid.get(xx,y));}
					grid.moveToAndDelete(this,grid.w()-1,y);
				}
				else
				{
					grid.deleteBlock(this);
				}

				Game().forceGravity=true;
			}
			else
			{
				directionChangeTicks+=Game().ticks();
				if(directionChangeTicks>1000)
				{
					directionChangeTicks=0;

					direction++;
					if(direction>3)direction=0;
				}
			}

		}

		if(blockType.removeAllBlocksOfColorOnFieldBlockIsSetOn&&ateBlocks==false)
		{
			if(setInGrid)
			{
				if(yGrid<grid.h()-1)
				{
					Block a = grid.get(xGrid,yGrid+1);
					if(a!=null&&a.color()!=null)
					{
						for(int y=0;y<grid.h();y++)
						{
							for(int x=0;x<grid.w();x++)
							{
								Block b = grid.get(x,y);
								if(b!=null)
								{
									if(b.color()==a.color())
									{
										grid.deleteBlock(b);
									}
								}
							}
						}
					}
				}
				grid.deleteBlock(this);
				Game().manuallyApplyGravityWithoutChainChecking();
				Game().forceGravity=true;
				ateBlocks=true;
			}
		}

		if(blockType.changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor&&didFlashingColoredDiamond==false)
		{
			if(setInGrid)
			{
				if(yGrid<grid.h()-1)
				{
					Block a = grid.get(xGrid,yGrid+1);
					if(a!=null&&a.color()!=null&&a.color()!=this.color())
					{
						BobColor colorToReplace = a.color();

						for(int y=0;y<grid.h();y++)
						{
							for(int x=0;x<grid.w();x++)
							{
								Block b = grid.get(x,y);
								if(b!=null)
								{
									if(b.color()==colorToReplace)
									{
										b.setColor(this.color());
									}
								}
							}
						}
					}
				}
				grid.deleteBlock(this);
				Game().manuallyApplyGravityWithoutChainChecking();
				Game().forceGravity=true;
				didFlashingColoredDiamond=true;
			}
		}



		colorFlashTicks+=Game().ticks();

		if(colorFlashTicks>colorFlashTicksPerPhase)
		{
			colorFlashTicks=0;
			colorFlashInOutToggle=!colorFlashInOutToggle;
		}
		if(colorFlashInOutToggle==true)
		{
			colorFlash = colorFlashFrom + ((float)colorFlashTicks/(float)colorFlashTicksPerPhase)*(colorFlashTo-colorFlashFrom);
		}
		else
		{
			colorFlash = colorFlashTo - ((float)colorFlashTicks/(float)colorFlashTicksPerPhase)*(colorFlashTo-colorFlashFrom);
		}






		if(effectFadeTicks>effectFadeTicksPerPhase)
		{
			effectFadeTicks=0;
			effectFadeInOutToggle=!effectFadeInOutToggle;
		}


		if(effectFadeInOutToggle==true)
		{
			effectAlpha = effectAlphaFrom + ((float)effectFadeTicks/(float)effectFadeTicksPerPhase)*(effectAlphaTo-effectAlphaFrom);
		}
		else
		{
			effectAlpha = effectAlphaTo - ((float)effectFadeTicks/(float)effectFadeTicksPerPhase)*(effectAlphaTo-effectAlphaFrom);
		}

	}


	// =========================================================================================================================
	public void setXYOffsetInPiece(int x, int y)
	{// =========================================================================================================================
		this.xInPiece = x;
		this.yInPiece = y;
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
	public float[] getInterpolatedScreenXY(float screenX, float screenY)
	{//=========================================================================================================================
		if(screenX!=lastScreenX||screenY!=lastScreenY)
		{

			float fromX = 0;
			float fromY = 0;

			//sweep in from closest screen edge if coming from offscreen
			if(lastScreenX==-1){if(screenX<Game().getWidth()/2)fromX = screenX;else fromX = Game().getWidth()-screenX;}
			if(lastScreenY==-1){if(screenY<Game().getHeight()/2)fromY = screenY;else fromY = Game().getHeight()-screenY;}
			if(lastScreenX==-1&&lastScreenY==-1)
			{
				if(fromX<fromY)
				{
					if(screenX<Game().getWidth()/2)lastScreenX = 0;
					else lastScreenX = Game().getWidth();
					lastScreenY = screenY;
				}
				else
				{
					if(screenY<Game().getHeight()/2)lastScreenY = 0;
					else lastScreenY = Game().getHeight();
					lastScreenX = screenX;
				}
			}

			int ticks = (int)GameType().blockMovementInterpolationTicks;
			if(customInterpolationTicks!=-1) ticks = customInterpolationTicks;

			if(ticksSinceLastMovement<ticks)
			{


				// draw in between animation
				float xDiff=screenX-lastScreenX;
				float yDiff=screenY-lastScreenY;

				float betweenX=((float)ticksSinceLastMovement/(float)ticks)*xDiff;
				float betweenY=((float)ticksSinceLastMovement/(float)ticks)*yDiff;

				//added this to try and fix skipping
				if(Math.abs(betweenX)>Math.abs(xDiff))betweenX = xDiff;
				if(Math.abs(betweenY)>Math.abs(yDiff))betweenY = yDiff;


				screenX = lastScreenX+betweenX;
				screenY = lastScreenY+betweenY;


			}
			else
			{
				lastScreenX=screenX;
				lastScreenY=screenY;

				//added this to try and fix skipping, but i think it is "too" smooth? this is probably the issue.
				//ticksSinceLastMovement=0;
			}
		}
		else
		{
			lastScreenX=screenX;
			lastScreenY=screenY;
			ticksSinceLastMovement=0;
		}

		float[] xy = new float[]{screenX,screenY};
		return xy;
	}


	// =========================================================================================================================
	public void renderDisappearing()
	{// =========================================================================================================================

		render(getScreenX(),getScreenY(),disappearingAlpha,1.0f+(2.0f-(disappearingAlpha*2.0f)),true);

	}

	// =========================================================================================================================
	public void render(float screenX,float screenY,float a, float s,boolean interpolate)
	{// =========================================================================================================================


		BobColor renderColor = color;

		if(overrideAnySpecialBehavior==false&&blockType.specialColor!=null)renderColor = blockType.specialColor;

		if(
				(
					overrideAnySpecialBehavior==false
					&&blockType.flashingSpecialType
				)
				||
				(
					piece!=null
					&&piece.overrideAnySpecialBehavior==false
					&&piece.pieceType!=null
					&&piece.pieceType.flashingSpecialType
				)
		)
		{
			BobColor c = color;

			if(blockType.specialColor!=null)c = blockType.specialColor;
			renderColor = new BobColor(c.r()+colorFlash,c.g()+colorFlash,c.b()+colorFlash,c.a());
		}

		if(renderColor==null)
		{
			renderColor = BobColor.black;
		}




		float w = blockW()*s;
		float h = blockH()*s;

		if(swappingWith!=0)
		{
			if(swappingWith==-1)screenX-=(w/(17*6))*swapTicks;
			else
			screenX+=(w/(17*6))*swapTicks;

			interpolate=false;

			lastScreenX=screenX;
			lastScreenY=screenY;
			ticksSinceLastMovement=0;
		}


		if(interpolate)
		{
			float[] xy = getInterpolatedScreenXY(screenX,screenY);

			screenX = xy[0];
			screenY = xy[1];
		}





		//-------------------------------------------------
		//do locking animation, draw darker if locked into Grid()
		//-------------------------------------------------
		BobColor drawColor = renderColor;
		if(GameType().fadeBlocksDarkerWhenLocking&&locking)
		{

			for(int i=0;i<lockingAnimationFrame;i++)drawColor = drawColor.darker(0.1f);

			if(lockingAnimationFrame>5)drawColor = BobColor.white;
		}
		else
		if(GameType().blockRule_drawBlocksDarkerWhenLocked&&setInGrid&&flashingToBeRemoved==false)drawColor = drawColor.darker(0.5f);//.darker();//a=0.6f;//



		if(flashingToBeRemoved)
		{
			if(flashingToBeRemovedLightDarkToggle==true)
			{
				drawColor = drawColor.lighter().lighter().lighter();
			}
			else
			{
				drawColor = drawColor.darker().darker().darker();
			}
		}




		float r = drawColor.r();
		float g = drawColor.g();
		float b = drawColor.b();




		if(slamming)
		{
			if(ticksSinceSlam<100)
			{
				float xDiff = screenX-slamX;
				float yDiff = screenY-slamY;

				screenX = slamX;
				screenY = slamY;

				w += xDiff;
				h += yDiff;
			}
			else
			{
				slamming=false;
			}
		}


		screenX = (float)Math.floor(screenX);
		screenY = (float)Math.floor(screenY);

		//-------------------------------------------------
		//if Piece() has color, draw color to background before draw Piece()
		//so that special blocks like spark balls inside of square pieces don't look so disconnected.
		//-------------------------------------------------
//		if(Piece()!=null)
//		{
//			if(Piece().pieceType.color!=null)
//			{
//				BobColor c = Piece().pieceType.color;
//				GLUtils.drawFilledRectXYWH(x,y,w,h,0,0,0,a);
//				GLUtils.drawFilledRectXYWH(x+1*s,y+1*s,w-2*s,h-2*s,c.r(),c.g(),c.b(),a);
//			}
//		}



		if(
				overrideAnySpecialBehavior==false
				&&piece!=null
				&&piece.pieceType!=null
				&&piece.pieceType.spriteName!=null
				&&piece.overrideAnySpecialBehavior==false
		)
		{

			//figure out what block we are in the Piece()

			//draw that part of the sprite

			float blocksWidth = piece.getWidth();
			float blocksHeight = piece.getHeight();

			float lowestX = piece.getLowestOffsetX();
			float thisX = xInPiece - lowestX;

			float lowestY = piece.getLowestOffsetY();
			float thisY = yInPiece - lowestY;


			Sprite sprite = BobsGame.getSpriteFromName(piece.pieceType.spriteName);

			Texture texture = sprite.texture;
			//float imageWidth = texture.getImageWidth();
			//float imageHeight = texture.getImageHeight();

			float x0InImage = (thisX / blocksWidth);
			float x1InImage = ((thisX+1) / blocksWidth);

			float y0InImage = (thisY / blocksHeight);
			float y1InImage = ((thisY+1) / blocksHeight);

			float imageToTextureRatioX =  ((float)texture.getImageWidth() / (float)texture.getTextureWidth());
			float tx0 = x0InImage * imageToTextureRatioX;
			float tx1 = x1InImage * imageToTextureRatioX;

			float imageToTextureRatioY =  ((float)sprite.h() / (float)texture.getTextureHeight());
			float ty0 = y0InImage * imageToTextureRatioY;
			float ty1 = y1InImage * imageToTextureRatioY;


			//log.info(""+tx0+" "+tx1+" "+ty0+" "+ty1);

			GLUtils.drawTexture(texture,tx0,tx1,ty0,ty1,screenX,screenX+w,screenY,screenY+h,r,g,b,a,GLUtils.FILTER_LINEAR);


			//sprite.drawFrame(0,x,x+w,y,y+h,r,g,b,a,GLUtils.FILTER_LINEAR);

			return;
		}



		boolean connectedUp = false;
		boolean connectedDown = false;
		boolean connectedLeft = false;
		boolean connectedRight = false;

		boolean connectedUpRight = false;
		boolean connectedDownRight = false;
		boolean connectedUpLeft = false;
		boolean connectedDownLeft = false;

		if(GameType().blockRule_drawBlocksConnectedByColorIgnoringPiece)
		{
			if(connectedBlocksByColor!=null)
			for(int i=0;i<connectedBlocksByColor.size();i++)
			{

				Block c = connectedBlocksByColor.get(i);
				if(c.xGrid==xGrid		&&	c.yGrid==yGrid-1)connectedUp=true;
				if(c.xGrid==xGrid		&&	c.yGrid==yGrid+1)connectedDown=true;
				if(c.xGrid==xGrid-1		&&	c.yGrid==yGrid)connectedLeft=true;
				if(c.xGrid==xGrid+1		&&	c.yGrid==yGrid)connectedRight=true;

				if(c.xGrid==xGrid-1		&&	c.yGrid==yGrid-1)connectedUpLeft=true;
				if(c.xGrid==xGrid+1		&&	c.yGrid==yGrid-1)connectedUpRight=true;
				if(c.xGrid==xGrid-1		&&	c.yGrid==yGrid+1)connectedDownLeft=true;
				if(c.xGrid==xGrid+1		&&	c.yGrid==yGrid+1)connectedDownRight=true;

			}
		}

		if(GameType().blockRule_drawBlocksConnectedByPieceIgnoringColor)
		{
			if(connectedBlocksByPiece!=null)
			for(int i=0;i<connectedBlocksByPiece.size();i++)
			{
				Block c = connectedBlocksByPiece.get(i);

				if(c.xInPiece==xInPiece		&&	c.yInPiece==yInPiece-1)connectedUp=true;
				if(c.xInPiece==xInPiece		&&	c.yInPiece==yInPiece+1)connectedDown=true;
				if(c.xInPiece==xInPiece-1	&&	c.yInPiece==yInPiece)connectedLeft=true;
				if(c.xInPiece==xInPiece+1	&&	c.yInPiece==yInPiece)connectedRight=true;

				if(c.xInPiece==xInPiece-1		&&	c.yInPiece==yInPiece-1)connectedUpLeft=true;
				if(c.xInPiece==xInPiece+1		&&	c.yInPiece==yInPiece-1)connectedUpRight=true;
				if(c.xInPiece==xInPiece-1		&&	c.yInPiece==yInPiece+1)connectedDownLeft=true;
				if(c.xInPiece==xInPiece+1		&&	c.yInPiece==yInPiece+1)connectedDownRight=true;


				if(c.xGrid==xGrid		&&	c.yGrid==yGrid-1)connectedUp=true;
				if(c.xGrid==xGrid		&&	c.yGrid==yGrid+1)connectedDown=true;
				if(c.xGrid==xGrid-1		&&	c.yGrid==yGrid)connectedLeft=true;
				if(c.xGrid==xGrid+1		&&	c.yGrid==yGrid)connectedRight=true;

				if(c.xGrid==xGrid-1		&&	c.yGrid==yGrid-1)connectedUpLeft=true;
				if(c.xGrid==xGrid+1		&&	c.yGrid==yGrid-1)connectedUpRight=true;
				if(c.xGrid==xGrid-1		&&	c.yGrid==yGrid+1)connectedDownLeft=true;
				if(c.xGrid==xGrid+1		&&	c.yGrid==yGrid+1)connectedDownRight=true;
			}
		}


		if(GameType().blockRule_drawBlocksConnectedByColorInPiece)
		{
			if(connectedBlocksByPiece!=null)
			for(int i=0;i<connectedBlocksByPiece.size();i++)
			{
				Block c = connectedBlocksByPiece.get(i);

				if(c.xInPiece==xInPiece		&&	c.yInPiece==yInPiece-1 && c.color == color && color!=null)connectedUp=true;
				if(c.xInPiece==xInPiece		&&	c.yInPiece==yInPiece+1 && c.color == color && color!=null)connectedDown=true;
				if(c.xInPiece==xInPiece-1	&&	c.yInPiece==yInPiece && c.color == color && color!=null)connectedLeft=true;
				if(c.xInPiece==xInPiece+1	&&	c.yInPiece==yInPiece && c.color == color && color!=null)connectedRight=true;

				if(c.xInPiece==xInPiece-1		&&	c.yInPiece==yInPiece-1 && c.color == color && color!=null)connectedUpLeft=true;
				if(c.xInPiece==xInPiece+1		&&	c.yInPiece==yInPiece-1 && c.color == color && color!=null)connectedUpRight=true;
				if(c.xInPiece==xInPiece-1		&&	c.yInPiece==yInPiece+1 && c.color == color && color!=null)connectedDownLeft=true;
				if(c.xInPiece==xInPiece+1		&&	c.yInPiece==yInPiece+1 && c.color == color && color!=null)connectedDownRight=true;

				if(c.xGrid==xGrid		&&	c.yGrid==yGrid-1 && c.color == color && color!=null)connectedUp=true;
				if(c.xGrid==xGrid		&&	c.yGrid==yGrid+1 && c.color == color && color!=null)connectedDown=true;
				if(c.xGrid==xGrid-1		&&	c.yGrid==yGrid && c.color == color && color!=null)connectedLeft=true;
				if(c.xGrid==xGrid+1		&&	c.yGrid==yGrid && c.color == color && color!=null)connectedRight=true;

				if(c.xGrid==xGrid-1		&&	c.yGrid==yGrid-1 && c.color == color && color!=null)connectedUpLeft=true;
				if(c.xGrid==xGrid+1		&&	c.yGrid==yGrid-1 && c.color == color && color!=null)connectedUpRight=true;
				if(c.xGrid==xGrid-1		&&	c.yGrid==yGrid+1 && c.color == color && color!=null)connectedDownLeft=true;
				if(c.xGrid==xGrid+1		&&	c.yGrid==yGrid+1 && c.color == color && color!=null)connectedDownRight=true;

			}
		}







		Sprite sprite = BobsGame.getSpriteFromName(blockType.sprite);

		if(
				blockType.specialSprite!=null
				&&overrideAnySpecialBehavior==false
		)
		{
			sprite = BobsGame.getSpriteFromName(blockType.specialSprite);
			sprite.drawFrame(0,screenX,screenX+w,screenY,screenY+h,r,g,b,a,GLUtils.FILTER_LINEAR);
		}
		else
		if(sprite!=null)
		{
			String animationName = "";


			if(connectedUp&&connectedDown&&connectedLeft&&connectedRight)animationName=("ConnectedAll");
			else if(connectedUp&&connectedLeft&&connectedRight)animationName=("ConnectedAllBottom");
			else if(connectedDown&&connectedLeft&&connectedRight)animationName=("ConnectedAllTop");
			else if(connectedRight&&connectedUp&&connectedDown)animationName=("ConnectedAllLeft");
			else if(connectedLeft&&connectedUp&&connectedDown)animationName=("ConnectedAllRight");

			else if(connectedLeft&&connectedUp)animationName=("ConnectedUpLeft");
			else if(connectedLeft&&connectedDown)animationName=("ConnectedDownLeft");
			else if(connectedRight&&connectedUp)animationName=("ConnectedUpRight");
			else if(connectedRight&&connectedDown)animationName=("ConnectedDownRight");

			else if(connectedUp&&connectedDown)animationName=("ConnectedUpDown");
			else if(connectedRight&&connectedLeft)animationName=("ConnectedLeftRight");

			else if(connectedRight)animationName=("ConnectedRight");
			else if(connectedLeft)animationName=("ConnectedLeft");
			else if(connectedUp)animationName=("ConnectedUp");
			else if(connectedDown)animationName=("ConnectedDown");


			if(direction!=-1)
			{
				if(direction==UP)animationName="Up";
				if(direction==DOWN)animationName="Down";
				if(direction==LEFT)animationName="Left";
				if(direction==RIGHT)animationName="Right";
			}

			if(counterCount>-1)
			{
				if(sprite.getAnimationByName(""+counterCount)!=null)animationName = ""+counterCount;
			}


			if(panic)
			{
				if(sprite.getAnimationByName("Panic")!=null)animationName = "Panic";
			}

			if(popping)
			{
				if(sprite.getAnimationByName("Popping")!=null)animationName = "Popping";
			}

			if(flashingToBeRemoved)
			{
				if(sprite.getAnimationByName("Flashing")!=null)animationName = "Flashing";
			}

			SpriteAnimationSequence anim = sprite.getFirstAnimation();

			if(animationName.length()>0)
			{
				SpriteAnimationSequence namedAnimation = sprite.getAnimationByName(animationName);
				if(namedAnimation!=null)anim = namedAnimation;
			}

			int animLength = sprite.getAnimationNumFramesByAnimation(anim);

			if(animationFrame>=animLength)animationFrame=-1;
			int frame = animationFrame;
			if(frame==-1)frame=0;

			sprite.drawFrame(anim.frameStart+frame,screenX,screenX+w,screenY,screenY+h,r,g,b,a,GLUtils.FILTER_LINEAR);

		}







		if(GameType().blockRule_drawDotToSquareOffBlockCorners)
		{
			if(connectedDown&&connectedRight&&!connectedDownRight)GLUtils.drawFilledRectXYWH(screenX+w-1,screenY+h-1,1*s,1*s,r,g,b,a);
			if(connectedDown&&connectedLeft&&!connectedDownLeft)GLUtils.drawFilledRectXYWH(screenX,screenY+h-1,1*s,1*s,r,g,b,a);
			if(connectedUp&&connectedLeft&&!connectedUpLeft)GLUtils.drawFilledRectXYWH(screenX,screenY,1*s,1*s,r,g,b,a);
			if(connectedUp&&connectedRight&&!connectedUpRight)GLUtils.drawFilledRectXYWH(screenX+w-1,screenY,1*s,1*s,r,g,b,a);
		}



		if(GameType().blockRule_fillSolidSquareWhenSetInGrid&&setInGrid&&flashingToBeRemoved==false)
		{
			BobColor c = new BobColor(renderColor,0.1f);
			GLUtils.drawFilledRectXYWH(screenX,screenY,w,h,c.r(),c.g(),c.b(),c.a());
		}


		if(GameType().drawDotOnRotationPiece)
		{
			BobColor dotColor = renderColor.lighter().lighter();

			if(this.xInPiece==0&&this.yInPiece==0)GLUtils.drawFilledRectXYWH(screenX+3*s,screenY+3*s,w-6*s,h-6*s,dotColor.r(),dotColor.g(),dotColor.b(),a);
		}


	}

	// =========================================================================================================================
	public void renderOutlines(float screenX,float screenY,float s)
	{// =========================================================================================================================

		float w = blockW()*s;
		float h = blockH()*s;

		if(GameType().gridRule_outlineOpenBlockEdges&&setInGrid==true&&disappearing==false)
		{
			if(grid!=null)
			{

				float gridAlpha = 1.0f;

				int gridOutlineWidth = 4;//TODO: scale with screen res

				for(int i=0;i<gridOutlineWidth;i++)
				{
					//left
					if(xGrid-1>=0&&grid.get(xGrid-1,yGrid)==null)GLUtils.drawFilledRectXYWH(screenX-i,screenY,i,h,1.0f,1.0f,1.0f,gridAlpha);
					//right
					if(xGrid+1<=grid.w()-1&&grid.get(xGrid+1,yGrid)==null)GLUtils.drawFilledRectXYWH(screenX+w,screenY,i,h,1.0f,1.0f,1.0f,gridAlpha);

					//up
					if(yGrid-1>=0&&grid.get(xGrid,yGrid-1)==null)GLUtils.drawFilledRectXYWH(screenX,screenY-i,w,i,1.0f,1.0f,1.0f,gridAlpha);
					//down
					if(yGrid+1<=grid.h()-1&&grid.get(xGrid,yGrid+1)==null)GLUtils.drawFilledRectXYWH(screenX,screenY+h,w,i,1.0f,1.0f,1.0f,gridAlpha);


					//if left and up is clear, draw pixel there
					if(xGrid-1>=0)
						if(yGrid-1>=0&&grid.get(xGrid-1,yGrid-1)==null)
							GLUtils.drawFilledRectXYWH(screenX-i,screenY-i,i,i,1.0f,1.0f,1.0f,gridAlpha);

					//if right and up is clear, draw pixel there
					if(xGrid+1<=grid.w()-1)
						if(yGrid-1>=0&&grid.get(xGrid+1,yGrid-1)==null)
							GLUtils.drawFilledRectXYWH(screenX+w,screenY-i,i,i,1.0f,1.0f,1.0f,gridAlpha);

					//if left and down is clear, draw pixel there
					if(xGrid-1>=0)
						if(yGrid+1<=grid.h()-1&&grid.get(xGrid-1,yGrid+1)==null)
							GLUtils.drawFilledRectXYWH(screenX-i,screenY+h,i,i,1.0f,1.0f,1.0f,gridAlpha);

					//if right and down is clear, draw pixel there
					if(xGrid+1<=grid.w()-1)
						if(yGrid+1<=grid.h()-1&&grid.get(xGrid+1,yGrid+1)==null)
							GLUtils.drawFilledRectXYWH(screenX+w,screenY+h,i,i,1.0f,1.0f,1.0f,gridAlpha);
				}

			}
		}

//		if(Piece()!=null)
//		{
//			int blockNum = 0;
//			for(int i=0;i<Piece().pieceType.numBlocks;i++)
//			{
//				if(Piece().blocks[i]==this){blockNum=i;break;}
//			}
//
//			GLUtils.drawOutlinedString(""+blockNum,(int)x,(int)y,BobColor.white);
//			GLUtils.drawOutlinedString(""+xInPiece+","+yInPiece,(int)x,(int)y+4,BobColor.white);
//		}


	}




	// =========================================================================================================================
	public void setColor(BobColor color)
	{// =========================================================================================================================
		this.color = color;
	}

	// =========================================================================================================================
	public void setRandomBlockTypeColor()
	{// =========================================================================================================================
		this.color = blockType.colors[Game().getRandomIntLessThan(blockType.colors.length)];
	}



	// =========================================================================================================================
	public BobColor getRandomMatrixColor()
	{// =========================================================================================================================
		int i=Game().getRandomIntLessThan(5);

		if(i==0) return BobColor.green;
		if(i==1) return BobColor.darkGreen;
		if(i==2) return BobColor.lightGreen;
		if(i==3) return BobColor.darkerGreen;
		if(i==4) return BobColor.lighterGreen;

		return BobColor.green;
	}



	// =========================================================================================================================
	public BobColor getRandomRainbowColor()
	{// =========================================================================================================================
		int i=Game().getRandomIntLessThan(22);

		if(i==0) return BobColor.lightGreen.lighter();
		if(i==1) return BobColor.green;
		if(i==2) return BobColor.darkGreen.darker();
		if(i==3) return BobColor.lightRed.lighter();
		if(i==4) return BobColor.red;
		if(i==5) return BobColor.darkRed.darker();
		if(i==6) return BobColor.lightYellow.lighter();
		if(i==7) return BobColor.yellow;
		if(i==8) return BobColor.darkYellow.darker();
		if(i==9) return BobColor.lightPink.lighter();
		if(i==10) return BobColor.pink;
		if(i==11) return BobColor.darkPink.darker();
		if(i==12) return BobColor.lightPurple.lighter();
		if(i==13) return BobColor.purple;
		if(i==14) return BobColor.darkPurple.darker();
		if(i==15) return BobColor.lightOrange.lighter();
		if(i==16) return BobColor.orange;
		if(i==17) return BobColor.darkOrange.darker();
		if(i==18) return BobColor.lightBlue.lighter();
		if(i==19) return BobColor.blue;
		if(i==20) return BobColor.darkBlue.darker();
		if(i==21) return BobColor.lightMagenta.lighter();
		if(i==21) return BobColor.magenta;
		if(i==21) return BobColor.darkMagenta.darker();

		return BobColor.green;
	}


	// =========================================================================================================================
	public BobColor getRandomGrayscaleColor()
	{// =========================================================================================================================
		int i=Game().getRandomIntLessThan(7);

		if(i==0) return new BobColor(0.2f,0.2f,0.2f);
		if(i==1) return new BobColor(0.3f,0.3f,0.3f);
		if(i==2) return new BobColor(0.4f,0.4f,0.4f);
		if(i==3) return new BobColor(0.5f,0.5f,0.5f);
		if(i==4) return new BobColor(0.6f,0.6f,0.6f);
		if(i==5) return new BobColor(0.7f,0.7f,0.7f);
		if(i==6) return new BobColor(0.8f,0.8f,0.8f);

		return BobColor.black;
	}









}
