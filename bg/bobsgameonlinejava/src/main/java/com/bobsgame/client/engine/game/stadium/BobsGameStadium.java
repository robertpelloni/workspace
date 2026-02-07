package com.bobsgame.client.engine.game.stadium;


import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL13.*;
//import static org.lwjgl.opengl.GL30.*;
//import static org.lwjgl.opengl.GL31.*;
//import static org.lwjgl.opengl.GL32.*;
//import static org.lwjgl.opengl.GL33.*;
//import static org.lwjgl.opengl.GL40.*;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.LWJGLUtils;
import com.bobsgame.client.engine.game.nd.ND;
import com.bobsgame.client.engine.game.nd.bobsgame.BobsGame;
import com.bobsgame.client.engine.game.nd.bobsgame.game.GameLogic;
import com.bobsgame.client.engine.game.nd.bobsgame.game.GameType;
import com.bobsgame.client.engine.map.Area;
import com.bobsgame.net.BobNet;


//=========================================================================================================================
public class BobsGameStadium extends StadiumGameEngine
{//=========================================================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(BobsGameStadium.class);





	//public ConcurrentHashMap<Long,Game> games = new ConcurrentHashMap<Long,Game>();

	public GameLogic ME = null;


	public long randomSeed = -1;

	GameType originalSettings = null;


	long timeRenderBegan = System.currentTimeMillis();


	boolean showingStartMenu = false;

	long lastTimeTriedToCloseGame = 0;


	boolean debug = BobNet.debugMode;



	//=========================================================================================================================
	public BobsGameStadium(StadiumScreen stadiumScreen, Area area)
	{//=========================================================================================================================

		super(stadiumScreen,area);




		newGame();

//		games.put(randomSeed,ME);

//		player2 = new Game(this);
//		player2.controlledByNetwork = true;
//		games.add(player2);


		name = "bob's game";



	}


	//=========================================================================================================================
	public void setupLoadScreens()
	{//=========================================================================================================================


		showingTitleScreen = true;

		numTileScreenTextureFrames = 91;//139;//with quotes

//		titleScreenTextures = new Texture[numTileScreenTextureFrames];
//
//		for(int i=0;i<numTileScreenTextureFrames;i++)
//		{
//			String num = ""+i;
//			int len = num.length();
//			for(int n=0;n<4-len;n++)num = "0"+num;//pad to 4 zeros
//
//			titleScreenTextures[i] = GLUtils.loadTexture("res/guiBackground/bobsGameLogoAnim/"+num+".png");
//		}

		cursorTexture = GLUtils.loadTexture("res/textbox/textCursor.png");

	}


	//=========================================================================================================================
	public void newGame()
	{//=========================================================================================================================

		if(ME!=null)
		{
			resetGame();
		}
		else
		{

			ME = (new GameLogic(this, -1));

			randomSeed = ME.randomSeed;

			originalSettings = ME.GameType();
		}

	}


	//=========================================================================================================================
	public void resetGame()
	{//=========================================================================================================================

		if(ME!=null)ME.deleteAllCaptions();


		//TODO: unload sprites?
		//TODO: stop music



		BobsGameStadium bobsgame = new BobsGameStadium(stadiumScreen, area);
		bobsgame.init();




		unloadTextures();

	}


	//=========================================================================================================================
	public void tryToCloseGame()
	{//=========================================================================================================================
		//TODO: upload score to leaderboard

	}




	//=========================================================================================================================
	public boolean isNetworkGame()
	{//=========================================================================================================================
		return false;

	}







	//=========================================================================================================================
	public void updateTitleScreenLogoTexture()
	{//=========================================================================================================================

		if(titleScreenTexture!=null)
		{
			GLUtils.releaseTexture(titleScreenTexture);
			titleScreenTexture=null;
		}

		String num = ""+currentTitleScreenTextureFrame;
		int len = num.length();
		for(int n=0;n<4-len;n++)num = "0"+num;//pad to 4 zeros

		titleScreenTexture = GLUtils.loadTexture("res/guiBackground/bobsGameLogoAnim/" +num+".png");


	}


	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================




		super.update();

		if(BobsGame.doneInitializingSprites==false)BobsGame.initSprites(SpriteManager());


		if(updateLoadScreens()==true)return;





		ME.updateNormalGame(GameLogic.MIDDLE);

		if(ME.dead)
		{
			if(ControlsManager().BUTTON_SPACE_PRESSED)
			{
				newGame();
			}
		}

	}




	boolean fboTextureToggle = false;


	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================



		if(super.renderLoadScreens()==true)return;



		if(LWJGLUtils.useShader)
		{




			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity();
			glEnable( GL_DEPTH_TEST );


			fboTextureToggle = !fboTextureToggle;

			LWJGLUtils.bindFBO(LWJGLUtils.nDBGFBO);
			if(fboTextureToggle)LWJGLUtils.drawIntoFBOAttachment(0);
			else LWJGLUtils.drawIntoFBOAttachment(1);

			glViewport(0, 0, LWJGLUtils.nDBGFBOWidth, LWJGLUtils.nDBGFBOHeight);
			glLoadIdentity();
			glOrtho(-1, 1, -1, 1, -1, 1);
			float tempDrawScale = GLUtils.globalDrawScale;
			GLUtils.globalDrawScale = 1.0f;









			glActiveTexture(GL_TEXTURE1);
			glEnable(GL_TEXTURE_2D);

			if(fboTextureToggle)glBindTexture(GL_TEXTURE_2D, LWJGLUtils.nDBGFBO_Texture_1);
			else glBindTexture(GL_TEXTURE_2D, LWJGLUtils.nDBGFBO_Texture_0);





			glActiveTexture(GL_TEXTURE0);
			glEnable(GL_TEXTURE_2D);
			if(titleScreenTexture!=null)glBindTexture(GL_TEXTURE_2D, titleScreenTexture.getTextureID());


			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);


			float time = ((System.currentTimeMillis() - timeRenderBegan) / 2000.0f);


			int shaderInt = LWJGLUtils.bgShaders.get(BobsGame.shaderCount).intValue();

			LWJGLUtils.useShader(shaderInt);
			LWJGLUtils.setShaderVar2f(shaderInt, "resolution", LWJGLUtils.nDBGFBOWidth, LWJGLUtils.nDBGFBOHeight);
			LWJGLUtils.setShaderVar2f(shaderInt, "mouse", 0.5f, 0.5f);
			LWJGLUtils.setShaderVar1f(shaderInt, "time", time);
			LWJGLUtils.setShaderVar1i(shaderInt, "tex0", 0);
			LWJGLUtils.setShaderVar1i(shaderInt, "backbuffer", 1);
			LWJGLUtils.setShaderVar1i(shaderInt, "bb", 1);
			//LWJGLUtils.setShaderVar1i(LWJGLUtils.fractalShader, "tex1"), 1);

			GLUtils.drawFilledRect(255,255,255,-1.0f,1.0f,-1.0f,1.0f,1.0f);

			LWJGLUtils.useShader(0);



			glDisable(GL_DEPTH_TEST);

			//disable texture2D on texture unit 1
			glActiveTexture(GL_TEXTURE1);
			glDisable(GL_TEXTURE_2D);

			//switch back to texture unit 0
			glActiveTexture(GL_TEXTURE0);
			glDisable(GL_TEXTURE_2D);


			LWJGLUtils.bindFBO(LWJGLUtils.nDFBO);
			LWJGLUtils.drawIntoFBOAttachment(0); //draw to nD FBO screen texture
			ND.setNDViewport();
			GLUtils.globalDrawScale = tempDrawScale;

			if(fboTextureToggle)GLUtils.drawTexture(LWJGLUtils.nDBGFBO_Texture_0, 0.0f, 1.0f, 1.0f, 0.0f, 0, getWidth(), 0, getHeight(), 1.0f, GLUtils.FILTER_FBO_LINEAR_NO_MIPMAPPING);
			else GLUtils.drawTexture(LWJGLUtils.nDBGFBO_Texture_1, 0.0f, 1.0f, 1.0f, 0.0f, 0, getWidth(), 0, getHeight(), 1.0f, GLUtils.FILTER_FBO_LINEAR_NO_MIPMAPPING);

			GLUtils.drawFilledRect(0,0,0,0, getWidth(), 0, getHeight(),0.3f);

		}



		ND.setNDViewport();


		ME.renderBackground();





		//render the playing field blocks to a FBO

		//draw the FBO to the screen with blur shader and 50% alpha

		//draw the FBO to the screen


		if(LWJGLUtils.useShader)
		{
			LWJGLUtils.drawIntoFBOAttachment(1); // draw to nDFBO auxiliary texture
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}


		ME.renderBlocks();



		if(LWJGLUtils.useShader)
		{

			LWJGLUtils.bindFBO(LWJGLUtils.nDBloomFBO);
			ND.setNDBloomViewport();


			glDisable(GL_BLEND);
			glDisable(GL_DEPTH_TEST);
			glDepthMask(false);


			LWJGLUtils.drawIntoFBOAttachment(1);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			LWJGLUtils.drawIntoFBOAttachment(0); //draw to bloom FBO texture 0
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



			LWJGLUtils.useShader(LWJGLUtils.maskShader);

				glBindTexture(GL_TEXTURE_2D, LWJGLUtils.nDFBO_MaskTexture);
				LWJGLUtils.setShaderVar1i(LWJGLUtils.maskShader, "u_texture0", 0);

				float threshold = 0.1f;
				LWJGLUtils.setShaderVar2f(LWJGLUtils.maskShader, "treshold", threshold, 1f / (1 - threshold));

				GLUtils.drawTexture(LWJGLUtils.nDFBO_MaskTexture, 0, 1, 0, 1, -1, 1, -1, 1, 1.0f, GLUtils.FILTER_FBO_LINEAR_NO_MIPMAPPING);

				LWJGLUtils.useShader(0);

			//GLUtils.drawTexture(LWJGLUtils.nDFBO_AuxiliaryTexture, 0, 1, 0, 1, -1, 1, -1, 1, 1, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);





			int blurPasses = ME.GameType().bloomTimes;

			for (int i = 0; i < blurPasses; i++)
			{

				float w = getWidth()*ND.BLOOM_FBO_SCALE;
				float h = getHeight()*ND.BLOOM_FBO_SCALE;

				// horizontal
				LWJGLUtils.drawIntoFBOAttachment(1);
				{
					LWJGLUtils.useShader(LWJGLUtils.gaussianShader);
					{


						LWJGLUtils.setShaderVar2f(LWJGLUtils.gaussianShader, "size", w, h);
						LWJGLUtils.setShaderVar2f(LWJGLUtils.gaussianShader, "dir", 1f, 0f);
						GLUtils.drawTexture(LWJGLUtils.nDBloomFBO_Texture_0,  0, 1, 0, 1, -1, 1, -1, 1, 1.0f, GLUtils.FILTER_FBO_LINEAR_NO_MIPMAPPING);

					}
					LWJGLUtils.useShader(0);
				}



				// vertical
				LWJGLUtils.drawIntoFBOAttachment(0);
				{
					LWJGLUtils.useShader(LWJGLUtils.gaussianShader);
					{
						LWJGLUtils.setShaderVar2f(LWJGLUtils.gaussianShader, "size", w, h);
						LWJGLUtils.setShaderVar2f(LWJGLUtils.gaussianShader, "dir", 0f, 1f);
						GLUtils.drawTexture(LWJGLUtils.nDBloomFBO_Texture_1, 0, 1, 0, 1, -1, 1, -1, 1, 1, GLUtils.FILTER_FBO_LINEAR_NO_MIPMAPPING);

					}
					LWJGLUtils.useShader(0);
				}

			}



			LWJGLUtils.bindFBO(LWJGLUtils.nDFBO);
			LWJGLUtils.drawIntoFBOAttachment(0); //draw to nD FBO screen texture
			ND.setNDViewport();

			//if(blending)
			{
				glEnable(GL_BLEND);
				LWJGLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			}


			//pingPongTex1.bind(1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, LWJGLUtils.nDBloomFBO_Texture_0);


			//original.bind(0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, LWJGLUtils.nDFBO_MaskTexture);



			LWJGLUtils.useShader(LWJGLUtils.bloomShader);
			{
				LWJGLUtils.setShaderVar1f(LWJGLUtils.bloomShader, "OriginalIntensity", 0.8f);
				LWJGLUtils.setShaderVar1f(LWJGLUtils.bloomShader, "BloomIntensity", ME.GameType().bloomIntensity);
				LWJGLUtils.setShaderVar1i(LWJGLUtils.bloomShader, "u_texture0", 0);
				LWJGLUtils.setShaderVar1i(LWJGLUtils.bloomShader, "u_texture1", 1);
				GLUtils.drawTexture(LWJGLUtils.nDFBO_MaskTexture, 0.0f, 1.0f, 1.0f, 0.0f, 0, getWidth(), 0, getHeight(), 1.0f, GLUtils.FILTER_FBO_LINEAR_NO_MIPMAPPING);
			}
			LWJGLUtils.useShader(0);


			//disable texture2D on texture unit 1
			glActiveTexture(GL_TEXTURE1);
			glDisable(GL_TEXTURE_2D);

			//switch back to texture unit 0
			glActiveTexture(GL_TEXTURE0);
			glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D);


			LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		}



		ME.renderForeground();



		super.render();

	}







}
