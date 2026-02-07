package com.bobsgame.client.engine.game.stadium;

import com.bobsgame.client.Texture;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.game.MiniGameEngine;
import com.bobsgame.client.engine.game.nd.GameDataLoader;
import com.bobsgame.client.engine.map.Area;
import com.bobsgame.client.engine.text.BobFont;
import com.bobsgame.client.engine.text.Caption;
import com.bobsgame.shared.BobColor;


//=========================================================================================================================
public class StadiumGameEngine extends MiniGameEngine
{//=========================================================================================================================





	public int numTileScreenTextureFrames = 0;
	//public Texture[] titleScreenTextures;
	public Texture titleScreenTexture;
	public Texture cursorTexture = null;

	public long titleScreenFrameTicks=0;
	public int currentTitleScreenTextureFrame=0;
	public boolean showingTitleScreen = false;

	Caption singlePlayerCaption = null;

	public long cursorInOutToggleTicks = 0;
	public boolean cursorInOutToggle = false;



	public String name = "";

	StadiumScreen stadiumScreen;
	Area area;

	//=========================================================================================================================
	public StadiumGameEngine(StadiumScreen stadiumScreen, Area area)
	{//=========================================================================================================================

		super();

		this.stadiumScreen = stadiumScreen;
		this.area = area;
		stadiumScreen.setGame(this,area);

		setupLoadScreens();

		new GameDataLoader(this);
	}

	//=========================================================================================================================
	public void setupLoadScreens()
	{//=========================================================================================================================
		//override
	}

	//=========================================================================================================================
	public void unloadTextures()
	{//=========================================================================================================================
		if(titleScreenTexture!=null)titleScreenTexture = GLUtils.releaseTexture(titleScreenTexture);
		if(cursorTexture!=null)cursorTexture = GLUtils.releaseTexture(cursorTexture);
	}

	//=========================================================================================================================
	public String getGameName()
	{//=========================================================================================================================
		return name;
	}



	//=========================================================================================================================
	public float getWidth()
	{//=========================================================================================================================
		return StadiumScreen.SCREEN_SIZE_X;
	}
	//=========================================================================================================================
	public float getHeight()
	{//=========================================================================================================================
		return StadiumScreen.SCREEN_SIZE_Y;
	}

//	//=========================================================================================================================
//	public void tryToCloseGame()
//	{//=========================================================================================================================
//		// override
//
//	}

	//=========================================================================================================================
	public void shakeSmall()
	{//=========================================================================================================================
		ClientGameEngine().Cameraman().popZOOMto = ClientGameEngine().Cameraman().getZoom()-0.1f;
		ClientGameEngine().Cameraman().setShakeScreen(300,2,2,30);
		ClientGameEngine().CinematicsManager().fadeColorFromTransparentToAlphaBackToTransparent(200,255,255,255,0.5f);

	}

	//=========================================================================================================================
	public void shakeHard()
	{//=========================================================================================================================
		ClientGameEngine().Cameraman().popZOOMto = ClientGameEngine().Cameraman().getZoom()-0.5f;
		ClientGameEngine().Cameraman().setShakeScreen(1000,5,5,30);
		ClientGameEngine().CinematicsManager().fadeColorFromTransparentToAlphaBackToTransparent(200,255,255,255,0.5f);

	}




	boolean throttle30fps = false;
	long ticksPassed = 0;
	long frameThrottleTicks = 0;

	public boolean networkGameStarted_NonThreaded = false;
	protected long nonThreadedTicksCounter = 0;
	//=========================================================================================================================
	public long engineTicksPassed()
	{//=========================================================================================================================
		return ticksPassed;
	}

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		frameThrottleTicks += super.engineTicksPassed();
		if(throttle30fps&&frameThrottleTicks<33)return;
		ticksPassed = frameThrottleTicks;
		frameThrottleTicks = 0;


		super.update();



		titleScreenFrameTicks+= super.engineTicksPassed();
		if(titleScreenFrameTicks>30)
		{
			titleScreenFrameTicks=0;
			currentTitleScreenTextureFrame++;
			if(currentTitleScreenTextureFrame>=numTileScreenTextureFrames)currentTitleScreenTextureFrame=0;

			updateTitleScreenLogoTexture();
		}



		cursorInOutToggleTicks+= super.engineTicksPassed();
		if(cursorInOutToggleTicks>300)
		{
			cursorInOutToggleTicks=0;
			cursorInOutToggle = !cursorInOutToggle;
		}



	}


	//=========================================================================================================================
	public boolean updateLoadScreens()
	{//=========================================================================================================================


		//skip the title screen if we were initialized with a connection, either we are in the simulator or got a friend request



			if(showingTitleScreen)
			{
				updateTitleScreen();
				return true;
			}




		return false;
	}

	//=========================================================================================================================
	public void updateTitleScreenLogoTexture()
	{//=========================================================================================================================
		//override
	}


	//=========================================================================================================================
	private void updateTitleScreen()
	{//=========================================================================================================================

		//if(titleScreenTextures==null)setupLoadScreens();



		if(singlePlayerCaption==null)singlePlayerCaption = CaptionManager().newManagedCaption(Caption.CENTERED_X,(int)(getHeight()/3*2),-1,"TOURNAMENT MODE",BobFont.font_normal_16_outlined_smooth,BobColor.white,BobColor.clear,1.0f);



		if(ControlsManager().BUTTON_ACTION_PRESSED)
		{
			showingTitleScreen=false;


			if(singlePlayerCaption!=null){singlePlayerCaption.deleteImmediately();singlePlayerCaption = null;}

		}

	}




	//=========================================================================================================================
	private void renderTitleScreen()
	{//=========================================================================================================================

		GLUtils.drawFilledRect(0,0,0,0,getWidth(),0,getHeight(),1.0f);

		//if(titleScreenTextures==null)return;

		//Texture t = titleScreenTextures[currentTitleScreenTextureFrame];
		Texture t = titleScreenTexture;

		if(t!=null)
		{

			float tx0 = 0;
			float tx1 = (float)t.getImageWidth() / (float)t.getTextureWidth();
			float ty0 = 0;
			float ty1 = (float)((float)t.getImageHeight()/(float)t.getTextureHeight());

			float ratio = (float)(getWidth()/2)/(float)t.getImageWidth();

			float sx0 = getWidth()/4;
			float sx1 = sx0+getWidth()/2;
			float sy0 = getHeight()/4;
			float sy1 = sy0+(float)(t.getImageHeight()*ratio);

			GLUtils.drawTexture(t, tx0,tx1,ty0,ty1, sx0,sx1,sy0,sy1, 1.0f, GLUtils.FILTER_NEAREST);

		}

		super.render();//captions



		t = cursorTexture;

		if(t!=null && singlePlayerCaption!=null)
		{

			float tx0 = 0;
			float tx1 = 1;
			float ty0 = 0;
			float ty1 = 1;

			float sx0 = singlePlayerCaption.screenX-16;
			if(cursorInOutToggle)sx0+=2;
			float sx1 = sx0+16;

			float sy0 = singlePlayerCaption.screenY+2;
			float sy1 = sy0+16;


			GLUtils.drawTexture(t, tx0,tx1,ty0,ty1, sx0,sx1,sy0,sy1, 1.0f, GLUtils.FILTER_NEAREST);

		}


	}



	//=========================================================================================================================
	public boolean renderLoadScreens()
	{//=========================================================================================================================


		if(showingTitleScreen)
		{
			renderTitleScreen();
			return true;
		}


		return false;

	}




}
