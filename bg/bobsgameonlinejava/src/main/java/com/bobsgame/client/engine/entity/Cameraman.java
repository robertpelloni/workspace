package com.bobsgame.client.engine.entity;


import com.bobsgame.client.console.Console;
import com.bobsgame.client.console.ConsoleText;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.client.engine.game.gui.statusbar.StatusBar;
import com.bobsgame.client.engine.map.Area;
import com.bobsgame.client.engine.map.Map;
import com.bobsgame.shared.EntityData;

import easing.Easing;



//=========================================================================================================================
public class Cameraman extends Entity
{//=========================================================================================================================

	public Entity targetEntity = null;

	float lastXTarget=-1;
	float lastYTarget=-1;

	public boolean ignoreCameraFXBoundaries = false;

	int camstop_tile=4;
	int tileSize = 16;





	static ConsoleText currentSpeedXText = Console.debug("currentSpeedXText");
	static ConsoleText currentSpeedYText = Console.debug("currentSpeedYText");


	static ConsoleText targetSpeedXText = Console.debug("targetSpeedXText");
	static ConsoleText targetSpeedYText = Console.debug("targetSpeedYText");


	int ticksSinceSnapToPlayer = 0;
	int ticksSinceZoomOut = 0;

	float snapSpeedX = 0;
	float snapSpeedY = 0;


	//public float easingDistance = 0;
	//public int easingTicks = 0;
	//public int easingDuration = 2000;
	//public float easingStartX = x();
	//public float easingStartY = y();

	int runningZoomTicks=0;
	int walkingZoomTicks=0;
	int standingTicks=0;
	int zoomBackInTicks=0;

	float walkingTempZoom=0;
	float runningTempZoom=0;
	float standingTempZoom=0;


	int ticksToZoomBackInFromRunningOrWalking = 1000;
	int ticksToWaitBeforeZoomingBackIn = 200;

	int ticksToWaitBeforeZoomingOut = 1000;
	int ticksToZoomOutWhileRunningOrWalking = 1000;

	int ticksToWaitBeforeCenteringOnPlayer = 1000;
	int ticksToCenterOnPlayer = 2000;

	float runningZoom = 1.0f;
	float walkingZoom = 1.5f;

	//TODO: if running outside, zoom out to 1.0f
	//TODO: if walking outside, zoom out to 1.5



	boolean autoZoomByPlayerMovementEnabled = true;
	public boolean zoomManuallyEnabled = true;




	public float screenShakeX = 0.0f;
	public float screenShakeY = 0.0f;
	public int screenShakeTicksPerShake = 0;
	public int screenShakeTicksPerShakeXCounter = 0;
	public int screenShakeTicksPerShakeYCounter = 0;

	public long shakeScreenStartTime = 0;
	public boolean shakeScreenLeftRightToggle = false;
	public boolean shakeScreenUpDownToggle = false;

	public int shakeScreenTicksCounter = 0;
	public int shakeScreenTicksDuration = 0;
	public float screenShakeMaxX = 0.0f;
	public float screenShakeMaxY = 0.0f;
	//=========================================================================================================================
	public Cameraman(Engine g)
	{//=========================================================================================================================
		super(g, new EntityData(-1,"Camera","Camera",0,0), null);


		//set target

		//set map x and map y to target x y

		targetEntity = this;

		getData().setDisableShadow(true);

	}



	//=========================================================================================================================
	public void initCurrentAnimationFromSprite()
	{//=========================================================================================================================

		//super.initCurrentAnimationFromSprite();

		setXYToTarget();
	}



	//=========================================================================================================================
	public Map getMap()
	{//=========================================================================================================================

		return MapManager().CurrentMap();
	}

	//=========================================================================================================================
	public Map CurrentMap()
	{//=========================================================================================================================

		return MapManager().CurrentMap();
	}

	//=========================================================================================================================
	@Override
	public void render(float alpha)
	{//=========================================================================================================================

		//don't render cameraman
		//super.render();
	}


	//=========================================================================================================================
	public float x()
	{//=========================================================================================================================

		return (float)(super.x()+(screenShakeX/zoom));
	}
	//=========================================================================================================================
	public float y()
	{//=========================================================================================================================

		return (float)(super.y()+(screenShakeY/zoom));
	}


	//=========================================================================================================================
	public void setShakeScreen(int ticksDuration, int maxX, int maxY, int ticksPerShake)
	{//=========================================================================================================================

		if(shakeScreenTicksCounter==0)shakeScreenStartTime = System.currentTimeMillis();

		shakeScreenTicksCounter+=ticksDuration;

		shakeScreenTicksDuration=shakeScreenTicksCounter;

		screenShakeMaxX = maxX;
		screenShakeMaxY = maxY;

		screenShakeTicksPerShake = ticksPerShake;

	}


	//=========================================================================================================================
	public void updateScreenShake()
	{//=========================================================================================================================
		if(shakeScreenTicksCounter>0)
		{
			shakeScreenTicksCounter-=Engine().engineTicksPassed();
			if(shakeScreenTicksCounter<0)shakeScreenTicksCounter=0;


			int ticksPassed = (int)(System.currentTimeMillis() - shakeScreenStartTime);


			float xOverShakeTime = (float)Easing.easeInOutCircular(ticksPassed,0,screenShakeMaxX,shakeScreenTicksDuration);
			float yOverShakeTime = (float)Easing.easeInOutCircular(ticksPassed,0,screenShakeMaxY,shakeScreenTicksDuration);

			screenShakeTicksPerShakeXCounter+=Engine().engineTicksPassed();
			if(screenShakeTicksPerShakeXCounter>screenShakeTicksPerShake)
			{
				screenShakeTicksPerShakeXCounter=0;
				shakeScreenLeftRightToggle=!shakeScreenLeftRightToggle;


			}

			screenShakeTicksPerShakeYCounter+=Engine().engineTicksPassed();//y shakes at half speed
			if(screenShakeTicksPerShakeYCounter>screenShakeTicksPerShake*2)
			{
				screenShakeTicksPerShakeYCounter=0;

				shakeScreenUpDownToggle=!shakeScreenUpDownToggle;
			}


			float xThisTime = (float)Easing.easeInOutCircular(screenShakeTicksPerShakeXCounter,0,xOverShakeTime,screenShakeTicksPerShake);
			float yThisTime = (float)Easing.easeInOutCircular(screenShakeTicksPerShakeYCounter,0,yOverShakeTime,screenShakeTicksPerShake*2);

			if(shakeScreenLeftRightToggle)screenShakeX = xThisTime;else screenShakeX = 0-xThisTime;
			if(shakeScreenUpDownToggle)screenShakeY = yThisTime;else screenShakeY = 0-yThisTime;

		}
		else
		{
			screenShakeX = 0;
			screenShakeY = 0;
		}

	}


	//=========================================================================================================================
	@Override
	public void update()
	{//=========================================================================================================================

		super.update();


		float xtarget = getXTarget();
		float ytarget = getYTarget();


		float distX = Math.abs(x()-xtarget);
		float distY = Math.abs(y()-ytarget);


		float maxDistX = Engine().getWidth();
		float maxDistY = Engine().getHeight();







		if(Engine() instanceof ClientGameEngine)
		{

			float playerSpeedX=((Math.abs(Player().forceX*(Player().pixelsToMoveThisFrame+1)))/Engine().engineTicksPassed())/0.01f;
			float playerSpeedY=((Math.abs(Player().forceY*(Player().pixelsToMoveThisFrame+1)))/Engine().engineTicksPassed())/0.01f;


			if(Player().noInput==true)
			{
				snapSpeedX=0.0f;
				snapSpeedY=0.0f;
				ticksSinceSnapToPlayer=0;
				ticksSinceZoomOut=0;


				standingTicks+=Engine().engineTicksPassed();
				if(standingTicks>ticksToWaitBeforeZoomingBackIn)
				{
					zoomBackInTicks+=Engine().engineTicksPassed();

					//zoom back into normal zoom if running zoom is further away
					if(zoomBackInTicks<ticksToZoomBackInFromRunningOrWalking)
					{
						runZOOMto = (float) (Math.ceil((standingTempZoom - (float)Easing.easeInOutSinusoidal(zoomBackInTicks, 0, standingTempZoom-ZOOMto, ticksToZoomBackInFromRunningOrWalking))*1000.0f)/1000.0f);
					}
					else runZOOMto=ZOOMto;
				}


				runningZoomTicks=0;
				walkingZoomTicks=0;

			}
			else
			{

				ticksSinceSnapToPlayer+=Engine().engineTicksPassed();
				ticksSinceZoomOut+=Engine().engineTicksPassed();
				standingTicks=0;

				zoomBackInTicks=0;
				standingTempZoom = runZOOMto;

				if(ticksSinceSnapToPlayer>ticksToWaitBeforeCenteringOnPlayer)
				{
					if(snapSpeedX<playerSpeedX)
					snapSpeedX = (float)Easing.easeInSinusoidal(ticksSinceSnapToPlayer-ticksToWaitBeforeCenteringOnPlayer, 0, playerSpeedX, ticksToWaitBeforeCenteringOnPlayer+ticksToCenterOnPlayer);

					if(snapSpeedY<playerSpeedY)
					snapSpeedY = (float)Easing.easeInSinusoidal(ticksSinceSnapToPlayer-ticksToWaitBeforeCenteringOnPlayer, 0, playerSpeedY, ticksToWaitBeforeCenteringOnPlayer+ticksToCenterOnPlayer);
				}

				if(ticksSinceZoomOut>ticksToWaitBeforeZoomingOut)
				{

					if(Player().running==true)
					{
						runningZoomTicks+=Engine().engineTicksPassed();
						walkingZoomTicks=0;

						//zoom out to 1.0f if we are closer in
						if(ZOOMto>runningZoom)
						{

							if(runningZoomTicks<=ticksToZoomOutWhileRunningOrWalking)
							runZOOMto = (float) (Math.floor((runningTempZoom - (float)Easing.easeInOutSinusoidal(runningZoomTicks, 0, runningTempZoom - runningZoom, ticksToZoomOutWhileRunningOrWalking))*1000.0f)/1000.0f);
							else
							runZOOMto=runningZoom;

							walkingTempZoom = runZOOMto;
						}
					}
					else
					if(Player().running==false)
					{
						walkingZoomTicks+=Engine().engineTicksPassed();
						runningZoomTicks=0;

						if(ZOOMto>walkingZoom)
						{
							if(walkingZoomTicks<=ticksToZoomOutWhileRunningOrWalking)
							runZOOMto = (float) (Math.floor((walkingTempZoom - (float)Easing.easeInOutSinusoidal(walkingZoomTicks, 0, walkingTempZoom - walkingZoom, ticksToZoomOutWhileRunningOrWalking))*1000.0f)/1000.0f);
							else
							runZOOMto=walkingZoom;

							runningTempZoom = runZOOMto;
						}
					}
				}
				else
				{
					walkingTempZoom = runZOOMto;
					runningTempZoom = runZOOMto;
				}
			}
		}
		else
		{
			runZOOMto = ZOOMto;


			float playerSpeedX=((Math.abs(targetEntity.ticksPerPixelMoved()*(targetEntity.pixelsToMoveThisFrame+1)))/Engine().engineTicksPassed())/0.01f;
			float playerSpeedY=((Math.abs(targetEntity.ticksPerPixelMoved()*(targetEntity.pixelsToMoveThisFrame+1)))/Engine().engineTicksPassed())/0.01f;

			if(targetEntity.ticksSinceLastMovement>0)
			{

				snapSpeedX=0.0f;
				snapSpeedY=0.0f;
				ticksSinceSnapToPlayer=0;

			}
			else
			{

				ticksSinceSnapToPlayer+=Engine().engineTicksPassed();
				ticksSinceZoomOut+=Engine().engineTicksPassed();
				standingTicks=0;

				zoomBackInTicks=0;
				standingTempZoom = runZOOMto;

				if(ticksSinceSnapToPlayer>ticksToWaitBeforeCenteringOnPlayer)
				{
					if(snapSpeedX<playerSpeedX)
					snapSpeedX = (float)Easing.easeInSinusoidal(ticksSinceSnapToPlayer-ticksToWaitBeforeCenteringOnPlayer, 0, playerSpeedX, ticksToWaitBeforeCenteringOnPlayer+ticksToCenterOnPlayer);

					if(snapSpeedY<playerSpeedY)
					snapSpeedY = (float)Easing.easeInSinusoidal(ticksSinceSnapToPlayer-ticksToWaitBeforeCenteringOnPlayer, 0, playerSpeedY, ticksToWaitBeforeCenteringOnPlayer+ticksToCenterOnPlayer);
				}
			}
		}



		float maxSpeed = 100.0f;
		float currentSpeedX = (float)Easing.easeOutQuintic(distX, snapSpeedX, maxSpeed, maxDistX);
		float currentSpeedY = (float)Easing.easeOutQuintic(distY, snapSpeedY, maxSpeed, maxDistY);



		currentSpeedXText.text = "Cam Speed X: "+Math.floor(currentSpeedX*Engine().engineTicksPassed()*0.01f*1000)/1000;
		currentSpeedYText.text = "Cam Speed Y: "+Math.floor(currentSpeedY*Engine().engineTicksPassed()*0.01f*1000)/1000;

		targetSpeedXText.text = "Player Snap Speed X: "+Math.floor(snapSpeedX*Engine().engineTicksPassed()*0.01f*1000)/1000;
		targetSpeedYText.text = "Player Snap Speed Y: "+Math.floor(snapSpeedY*Engine().engineTicksPassed()*0.01f*1000)/1000;


		float pixelsToMoveX = currentSpeedX*Engine().engineTicksPassed()*0.01f;//currentSpeed*pixelsToMoveThisFrame;//Game().ticksPassed()*0.2f*((float)Math.pow(2.0f, dist));
		float pixelsToMoveY = currentSpeedY*Engine().engineTicksPassed()*0.01f;//currentSpeed*pixelsToMoveThisFrame;//Game().ticksPassed()*0.2f*((float)Math.pow(2.0f, dist));



		if(CurrentMap().alpha==1.0f)//TODO: if current map is done fading in , make this a function
		{
			if(x()>xtarget)
			{
				setX(x()-pixelsToMoveX);
				if(x()<xtarget)setX(xtarget);
			}
			if(x()<xtarget)
			{
				setX(x()+pixelsToMoveX);
				if(x()>xtarget)setX(xtarget);
			}
			if(y()>ytarget)
			{
				setY(y()-pixelsToMoveY);
				if(y()<ytarget)setY(ytarget);
			}
			if(y()<ytarget)
			{
				setY(y()+pixelsToMoveY);
				if(y()>ytarget)setY(ytarget);
			}
		}

		//setX(xtarget);
		//setY(ytarget);

		updateZoom();

		updateScreenShake();
	}




	static public float ZOOMINCREMENT = 0.25f;

	static public float MINZOOM = 0.25f;//1.0f;

	static public float MAXZOOM = 3.0f;


	public float ZOOMto=2.0f;//0.25f;//2.0f;

	public float quickZOOMto=0.0f;//0.25f;//2.0f;
	public float runZOOMto=ZOOMto;//0.25f;//2.0f;


	public int ZOOMlock=0;

	private float zoom = 2.0f;//0.25f;//2.0f;


	public float speedMultiplier;//TODO

	public float popZOOMto = 0.0f;


	public float getZoom()
	{
		if(screenShakeMaxY!=0)
		{
			return zoom + ((float)(((float)screenShakeY / (float)screenShakeMaxY) * (screenShakeMaxY / (Engine().getWidth()*zoom))))*2;
		}
		return zoom;
	}
	public void setZoomTO(float ZOOMto)
	{
		this.ZOOMto = ZOOMto;
	}


	public void setZoomToFitArea(Area a)
	{
		float screenWidth = Engine().getWidth();
		float areaWidth = a.w();

		float screenHeight = Engine().getHeight();
		float areaHeight = a.h();

		//TODO:

	}

	//=========================================================================================================================
	public void updateZoom()
	{//=========================================================================================================================

		//float oldZoom = zoom;


		if(quickZOOMto!=0.0f && zoomManuallyEnabled)
		{
			if(zoom!=quickZOOMto)
			{
				if(zoom>quickZOOMto)
				{
					zoom-=0.01f*Engine().engineTicksPassed();
					if(zoom<quickZOOMto)zoom=quickZOOMto;
				}

				if(zoom<quickZOOMto)
				{
					zoom+=0.01f*Engine().engineTicksPassed();
					if(zoom>quickZOOMto)zoom=quickZOOMto;
				}
			}
		}
		else
		if(runZOOMto!=ZOOMto && autoZoomByPlayerMovementEnabled)
		{
			if(zoom!=runZOOMto)
			{
				if(zoom>runZOOMto)
				{
					zoom-=0.01f*Engine().engineTicksPassed();
					if(zoom<runZOOMto)zoom=runZOOMto;
				}

				if(zoom<runZOOMto)
				{
					zoom+=0.01f*Engine().engineTicksPassed();
					if(zoom>runZOOMto)zoom=runZOOMto;
				}
			}
		}
		else
		if(popZOOMto!=0)
		{
			if(zoom!=popZOOMto)
			{
				if(zoom>popZOOMto)
				{
					zoom-=0.00005f*Engine().engineTicksPassed();
					if(zoom<popZOOMto)zoom=popZOOMto;
				}

				if(zoom<ZOOMto)
				{
					zoom+=0.00005f*Engine().engineTicksPassed();
					if(zoom>popZOOMto)zoom=popZOOMto;
				}
			}

			if(zoom==popZOOMto){popZOOMto=0.0f;}

		}
		else
		{
			if(zoom!=ZOOMto)
			{
				if(zoom>ZOOMto)
				{
					zoom-=0.002f*Engine().engineTicksPassed();
					if(zoom<ZOOMto)zoom=ZOOMto;
				}

				if(zoom<ZOOMto)
				{
					zoom+=0.002f*Engine().engineTicksPassed();
					if(zoom>ZOOMto)zoom=ZOOMto;
				}
			}
		}




		//TODO: figure out how to smoothly zoom in without update(1000) hack


		//TODO: shift should lock camera? maybe caps lock


		//TODO: update camera coordinates to smoothly zoom in
		//if(zoom!=oldZoom)
		//{
			//cameraman.mapXPixelsHQ=cameraman.mapXPixelsHQ/(zoom-oldZoom);
			//cameraman.mapYPixelsHQ=cameraman.mapYPixelsHQ/(zoom-oldZoom);
			//cameraman.update(10000);
		//}

		//TODO: update min zoom to room size? only for big areas, dont want closets zoomed in all the way


		/*if(map().alpha==1.0f)//is finished fading in, make this a function or something
		{


			//TODO: if we are outside, prefer 640x480?
			//keep users zoom level, but if camstop layer to edge is smaller than zoom, zoom into that temporarily.

			//zoom in closer near stores. maybe need fx layer markings for "zoom in"

			//remember each room's zoom level set by user

			//if we are inside, prefer 320 x 240, dont allow zooming out further than the room size.


			int maxCamWidth = cameraman.getMaxCameraBoundaryWidth();
			int maxCamHeight = cameraman.getMaxCameraBoundaryHeight();

			if(maxCamWidth<maxCamHeight)
			//if((float)LWJGLUtils.SCREEN_SIZE_X>maxCamWidth*ZOOMto)
			{
				ZOOMto=(float)LWJGLUtils.SCREEN_SIZE_X/(float)maxCamWidth;

				//round to nearest 0.25 (higher)
				//1.77-> 2.0f
				//1.74-> 1.75
				ZOOMto=((float)(((((int)(ZOOMto*100))/25)+1)*25))/100.0f;
				//Math.floor(ZOOMto);

				if(ZOOMto<MINZOOM)ZOOMto=MINZOOM;
				if(ZOOMto>MAXZOOM)ZOOMto=MAXZOOM;

			}

			if(maxCamHeight<maxCamWidth)
			//if((float)LWJGLUtils.SCREEN_SIZE_Y>(float)maxCamHeight*ZOOMto)
			{
				ZOOMto=(float)LWJGLUtils.SCREEN_SIZE_Y/(float)maxCamHeight;
				ZOOMto=((float)(((((int)(ZOOMto*100))/25)+1)*25))/100.0f;

				if(ZOOMto<MINZOOM)ZOOMto=MINZOOM;
				if(ZOOMto>MAXZOOM)ZOOMto=MAXZOOM;
			}
		}*/

	}

	//=========================================================================================================================
	public void zoomOut()
	{//=========================================================================================================================
		if(ZOOMlock==0)
		{
			if(ZOOMto>MINZOOM)ZOOMto-=ZOOMINCREMENT;
			if(ZOOMto<MINZOOM)ZOOMto=MINZOOM;

			runZOOMto = ZOOMto;
		}

	}
	//=========================================================================================================================
	public void zoomIn()
	{//=========================================================================================================================
		if(ZOOMlock==0)
		{
			if(ZOOMto<MAXZOOM)ZOOMto+=ZOOMINCREMENT;
			if(ZOOMto>MAXZOOM)ZOOMto=MAXZOOM;

			runZOOMto = ZOOMto;
		}

	}
	//=========================================================================================================================
	public void resetZoom()
	{//=========================================================================================================================
		ZOOMto = 2.0f;
		runZOOMto = ZOOMto;

	}
	//=========================================================================================================================
	public void quickZoomOut()
	{//=========================================================================================================================
		//zoom out
		quickZOOMto=1.0f;

		//TODO: if outside this should be 0.5

	}
	//=========================================================================================================================
	public void quickZoomIn()
	{//=========================================================================================================================
		//zoom in
		quickZOOMto=3.0f;

		//TODO: do this for conversations

	}
	//=========================================================================================================================
	public void resetQuickZoom()
	{//=========================================================================================================================
		if(quickZOOMto!=0.0f)
		{
			if(quickZOOMto>ZOOMto)
			{
				quickZOOMto-=0.01f*Engine().engineTicksPassed();
				if(quickZOOMto<ZOOMto)quickZOOMto=0.0f;
			}

			if(zoom<ZOOMto)
			{
				quickZOOMto+=0.01f*Engine().engineTicksPassed();
				if(quickZOOMto>ZOOMto)quickZOOMto=0.0f;
			}
		}
	}



	//=========================================================================================================================
	public float getXTarget()
	{//=========================================================================================================================
		//=============FIND BOUNDARY TARGETS,CENTER OF THE ROOM IF THE ROOM WILL FIT ONSCREEN,ELSE HALF A SCREEN AWAY FROM THE NEAREST BOUNDARY

		int leftbounds=-1;
		int rightbounds=-1;

		float xtarget=-1;

		int SCREEN_WIDTH_TILES = (int)(((Engine().getWidth())/zoom)/tileSize);//width in tiles at current zoom

		int GAME_VIEWPORT_WIDTH_PIXELS = (int)(Engine().getWidth()/zoom);

		int mapWidthTiles = CurrentMap().widthPixelsHQ()/tileSize;


		//TODO: check the fx layer for BOTH left and right/top and bottom of the player (not just the middle), to prevent single tile width camera boundaries from making the camera move for a few frames.
		//prefer the one that is further away

		float playerx = targetEntity.x()+(targetEntity.w()/2.0f);
		float playery = targetEntity.y()+(targetEntity.h()/2.0f);


		for(xtarget=(int)playerx/tileSize;xtarget>=0&&xtarget>=(playerx/tileSize)-(SCREEN_WIDTH_TILES);xtarget--)
		{
			if(
				CurrentMap().getCameraBoundsFXLayerAtXYPixels(xtarget*tileSize, playery)==camstop_tile||
				xtarget==0
			)
			{
				leftbounds=(int)((xtarget+1)*tileSize);//+1 because it's measured by the left edge of the tile: on the right of the tile, the "active" edge is offset by the width of the tile itself
				break;
			}
		}


		for(xtarget=(int)playerx/tileSize;xtarget<mapWidthTiles&&xtarget<=(playerx/tileSize)+(SCREEN_WIDTH_TILES);xtarget++)
		{
			if(
				CurrentMap().getCameraBoundsFXLayerAtXYPixels(xtarget*tileSize, playery)==camstop_tile||
				xtarget==mapWidthTiles-1
			)
			{
				rightbounds=(int)(xtarget*tileSize);
				break;
			}
		}

		xtarget=-1;

		if(leftbounds!=-1||rightbounds!=-1)
		{
			if(leftbounds!=-1&&rightbounds!=-1&&rightbounds-leftbounds<=GAME_VIEWPORT_WIDTH_PIXELS)
			{
				xtarget=(leftbounds+((rightbounds-leftbounds)/2));
			}
			else
			if(leftbounds!=-1&&playerx<=leftbounds+GAME_VIEWPORT_WIDTH_PIXELS/2)
			{
				xtarget=(leftbounds+GAME_VIEWPORT_WIDTH_PIXELS/2);
			}
			else
			if(rightbounds!=-1&&playerx>=rightbounds-GAME_VIEWPORT_WIDTH_PIXELS/2)
			{
				xtarget=(rightbounds-GAME_VIEWPORT_WIDTH_PIXELS/2);
			}

		}


		lastXTarget=xtarget;
		if(xtarget==-1||ignoreCameraFXBoundaries==true)xtarget=playerx;

		return xtarget;

	}

	//=========================================================================================================================
	public float getYTarget()
	{//=========================================================================================================================

		//=============FIND BOUNDARY TARGETS,CENTER OF THE ROOM IF THE ROOM WILL FIT ONSCREEN,ELSE HALF A SCREEN AWAY FROM THE NEAREST BOUNDARY
		int topbounds=-1;
		int bottombounds=-1;

		float ytarget=-1;

		float statusBarSize = 0;
		if(Engine().getClass().equals(ClientGameEngine.class))statusBarSize = StatusBar.sizeY;


		int SCREEN_HEIGHT_TILES = (int)(((Engine().getHeight())/zoom)/tileSize);

		int GAME_VIEWPORT_HEIGHT_PIXELS = (int)((int)(Engine().getHeight()/zoom)-statusBarSize);

		int mapHeightTiles = CurrentMap().heightPixelsHQ()/tileSize;



		//TODO: check the fx layer for BOTH left and right/top and bottom of the player (not just the middle), to prevent single tile width camera boundaries from making the camera move for a few frames.
		//prefer the one that is further away

		float playerx = targetEntity.x()+(targetEntity.w()/2.0f);
		float playery = targetEntity.y()+(targetEntity.h()/2.0f);


		for(ytarget=(int)playery/tileSize;ytarget>=0&&ytarget>=(playery/tileSize)-(SCREEN_HEIGHT_TILES);ytarget--)
		{
			if(
				CurrentMap().getCameraBoundsFXLayerAtXYPixels(playerx, ytarget*tileSize)==camstop_tile|
				ytarget==0
			)
			{
				topbounds=(int)((ytarget+1)*tileSize);
				break;
			}

		}

		for(ytarget=(int)playery/tileSize;ytarget<mapHeightTiles&&ytarget<=(playery/tileSize)+(SCREEN_HEIGHT_TILES);ytarget++)
		{
			if(
				CurrentMap().getCameraBoundsFXLayerAtXYPixels(playerx, ytarget*tileSize)==camstop_tile||
				ytarget==mapHeightTiles-1
			)
			{
				bottombounds=(int)(ytarget*tileSize);
				break;
			}
		}

		ytarget=-1;

		if(topbounds!=-1||bottombounds!=-1)
		{
			if(topbounds!=-1&&bottombounds!=-1&&bottombounds-topbounds<=GAME_VIEWPORT_HEIGHT_PIXELS)
			{
				ytarget=(topbounds+((bottombounds-topbounds)/2));
			}
			else
			if(topbounds!=-1&&playery<=topbounds+GAME_VIEWPORT_HEIGHT_PIXELS/2)
			{
				ytarget=(topbounds+GAME_VIEWPORT_HEIGHT_PIXELS/2);
			}
			else
			if(bottombounds!=-1&&playery>=bottombounds-GAME_VIEWPORT_HEIGHT_PIXELS/2)
			{
				ytarget=(bottombounds-GAME_VIEWPORT_HEIGHT_PIXELS/2);
			}

		}

		lastYTarget=ytarget;

		if(ytarget==-1||ignoreCameraFXBoundaries==true)ytarget=playery;

		//TODO: adjust this based on status bar position
		ytarget-=statusBarSize/2;

		return ytarget;

	}



	//=========================================================================================================================
	public int getMaxCameraBoundaryWidth()
	{//=========================================================================================================================

		//we want to go from player x to 0, checking for camstop tiles. leftBounds = camstop tile OR 0.
		//this is different from below because it doesn't stop at the edge of the visible screen.

		int leftbounds=-1;
		int rightbounds=-1;

		int xtarget=-1;


		float playerx = targetEntity.x()+(targetEntity.w()/2);
		float playery = targetEntity.y()+(targetEntity.h()/2);

		int mapWidthTiles = CurrentMap().widthPixelsHQ()/tileSize;
		//int mapHeightTiles = map().heightPixelsHQ2X/tileSize;


		for(xtarget=(int)(playerx/tileSize);xtarget>=0;xtarget--)
		{
			//TODO: this could actually go by increments of two tiles (or 16 pixels), since every other tile is redundant (get_fx_layer rounds down), since map is hq2x

			if(CurrentMap().getCameraBoundsFXLayerAtXYPixels(xtarget*tileSize, (int)playery)==camstop_tile)
			{
				leftbounds=(xtarget+1)*tileSize;
				break;
			}
		}


		for(xtarget=(int)(playerx/tileSize);xtarget<mapWidthTiles;xtarget++)
		{
			int fxtile = CurrentMap().getCameraBoundsFXLayerAtXYPixels(xtarget*tileSize, (int)playery);
			if(fxtile==camstop_tile)
			{
				rightbounds=xtarget*tileSize;
				break;
			}
		}

		return rightbounds-leftbounds;

	}

	//=========================================================================================================================
	public int getMaxCameraBoundaryHeight()
	{//=========================================================================================================================

		//we want to go from player x to 0, checking for camstop tiles. leftBounds = camstop tile OR 0.
		//this is different from below because it doesn't stop at the edge of the visible screen.

		int topbounds=-1;
		int bottombounds=-1;

		float ytarget=-1;


		float playerx = targetEntity.x()+(targetEntity.w()/2);
		float playery = targetEntity.y()+(targetEntity.h()/2);

		//int mapWidthTiles = map().widthPixelsHQ2X/tileSize;
		int mapHeightTiles = CurrentMap().heightPixelsHQ()/tileSize;


		for(ytarget=(int)(playery/tileSize);ytarget>=0;ytarget--)
		{
			if(CurrentMap().getCameraBoundsFXLayerAtXYPixels((int)playerx, ytarget*tileSize)==camstop_tile)
			{
				topbounds=(int)((ytarget+1)*tileSize);
				break;
			}
		}


		for(ytarget=(int)(playery/tileSize);ytarget<mapHeightTiles;ytarget++)
		{
			if(CurrentMap().getCameraBoundsFXLayerAtXYPixels((int)playerx, ytarget*tileSize)==camstop_tile)
			{
				bottombounds=(int)(ytarget*tileSize);
				break;
			}
		}

		return bottombounds-topbounds;

	}

	//=========================================================================================================================
	public int getMapWidthBasedOnCameraBoundsFromEdge()
	{//=========================================================================================================================


		return 0;
	}
	//=========================================================================================================================
	public int getMapHeightBasedOnCameraBoundsFromEdge()
	{//=========================================================================================================================


		return 0;
	}



	//=========================================================================================================================
	public void setXYToTarget()
	{//=========================================================================================================================
		setX(targetEntity.x()+(targetEntity.w()/2));
		setY(targetEntity.y()+(targetEntity.h()/2));
	}

	//=========================================================================================================================
	public void setTarget(Entity t)
	{//=========================================================================================================================
		if(t==null)t=Player();

		if(t==null)setDummyTarget();
		else
		targetEntity = t;

	}

	//=========================================================================================================================
	public void setTarget(int mapXPixelsHQ, int mapYPixelsHQ)
	{//=========================================================================================================================
		targetEntity = new Entity(Engine(),new EntityData(-1,"Null Target","",mapXPixelsHQ/2,mapYPixelsHQ/2), null);

	}

	//=========================================================================================================================
	public void setTarget(Area area)
	{//=========================================================================================================================
		targetEntity = new Entity(Engine(),new EntityData(-1,"Null Target","",area.middleX()/2,area.middleY()/2), null);

	}

	//=========================================================================================================================
	public void setDummyTarget()
	{//=========================================================================================================================
		targetEntity = this;//new Entity(Engine(),new EntityData(-1,"Null Target","",x(),y()));


	}



	//=========================================================================================================================
	public void setAutoZoomByPlayerMovement(boolean b)
	{//=========================================================================================================================
		autoZoomByPlayerMovementEnabled = b;

	}

	//=========================================================================================================================
	public void setPlayerCanZoomManuallyWithKeyboard(boolean b)
	{//=========================================================================================================================
		zoomManuallyEnabled = b;

	}



}
