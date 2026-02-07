package com.bobsgame.client.engine.game.nd;



import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL13.*;
//import static org.lwjgl.opengl.GL30.*;
//import static org.lwjgl.opengl.GL31.*;
//import static org.lwjgl.opengl.GL32.*;
//import static org.lwjgl.opengl.GL33.*;
//import static org.lwjgl.opengl.GL40.*;



import com.bobsgame.client.Texture;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.LWJGLUtils;

import com.bobsgame.client.console.Console;
import com.bobsgame.client.console.ConsoleText;
import com.bobsgame.client.engine.game.FriendCharacter;
import com.bobsgame.client.engine.game.gui.MenuPanel;
import com.bobsgame.client.engine.map.Light;


import com.bobsgame.client.state.State;
import com.bobsgame.client.state.StateManager;

import easing.Easing;



//=========================================================================================================================
public class ND extends MenuPanel
{//=========================================================================================================================

	Texture texture = null;

	float nDDrawAlpha = 1.0f;
	float nDZoom = 0.01f;


	float widthTextureAspectRatio=0;
	float heightTextureAspectRatio=0;
	float widthToHeightRatio=0;


	float widthThisFrame = 0;
	float targetWidth = 0;



	public static final int SCREEN_SIZE_X = 640*2;
	public static final int SCREEN_SIZE_Y = 480*2;
	public static final int FBO_SCALE_MULTIPLIER = 1;




	public StateManager nDGameStateManager;


	public Light light = null;
	float lightAlpha = 1.0f;
	boolean lightFadeInOutToggle = false;

	float lightFadeSpeedMult = 0.0005f;
	float lightMaxAlpha = 0.75f;
	float lightMinAlpha = 0.70f;


	public ConsoleText ndZoomText = Console.debug("ndZoomText");


	long fadeOutMeshTicks = 0;
	int fadeOutMeshTicksSpeed = 2000;
	boolean fadeMesh = true;
	float drawMeshAlpha = 0.5f;

	//=========================================================================================================================
	public ND()
	{//=========================================================================================================================
		super();

		texture = GLUtils.loadTexture("res/nD/nD.png");

		widthTextureAspectRatio = ((float)texture.getTextureWidth()/(float)texture.getImageWidth());
		heightTextureAspectRatio = ((float)texture.getTextureHeight()/(float)texture.getImageHeight());
		widthToHeightRatio = ((float)texture.getTextureWidth()/(float)texture.getTextureHeight());



		nDGameStateManager = new StateManager();

	}

	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================

		fadeInTime = 1500.0f;//override MenuPanel defaults, since we are zooming in, not scrolling in.
		fadeOutTime = 500.0f;
	}



	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================



		targetWidth = LWJGLUtils.SCREEN_SIZE_X*2.00f;



		super.update();


		State s = nDGameStateManager.getState();

		if(isActivated==true)
		{
			GLUtils.globalDrawScale=FBO_SCALE_MULTIPLIER;
			if(s!=null)nDGameStateManager.update();
			GLUtils.globalDrawScale=1.0f;
		}

		if(s!=null)
		{
			if(lightFadeInOutToggle==true)
			{
				if(lightAlpha<lightMaxAlpha)
				{
					lightAlpha += s.engineTicksPassed()*(lightFadeSpeedMult);

					if(lightAlpha>=lightMaxAlpha)
					{
						lightAlpha = lightMaxAlpha;
						lightFadeInOutToggle = false;
					}
				}

			}
			else
			{
				if(lightAlpha>=lightMinAlpha)
				{
					lightAlpha -= s.engineTicksPassed()*(lightFadeSpeedMult);

					if(lightAlpha<lightMinAlpha)
					{
						lightAlpha = lightMinAlpha;
						lightFadeInOutToggle = true;
					}

				}

			}




			if(isScrolledUp==true)
			{
				fadeOutMeshTicks+=s.engineTicksPassed();

				if(fadeOutMeshTicks>fadeOutMeshTicksSpeed)
				{
					fadeOutMeshTicks=0;
					fadeMesh = false;
				}

				if(fadeMesh)
				{
					drawMeshAlpha = 0.1f +  (0.5f - (0.5f*((float)fadeOutMeshTicks/(float)fadeOutMeshTicksSpeed)));
				}
				else drawMeshAlpha = 0.1f;

			}

		}



		ndZoomText.text = "nD zoom: "+nDZoom;


	}


	//=========================================================================================================================
	public void setGame(NDGameEngine game)
	{//=========================================================================================================================

		light = new Light(game, "nDScreenLight",0,0,SCREEN_SIZE_X,SCREEN_SIZE_Y,240,240,255,60,32,2.0f,1.0f,0,true,true);


		nDGameStateManager.setState(game);

	}
	//=========================================================================================================================
	public NDGameEngine getGame()
	{//=========================================================================================================================
		return (NDGameEngine)nDGameStateManager.getState();

	}



	//=========================================================================================================================
	public void toggleActivated()
	{//=========================================================================================================================

		if(isActivated==false)
		{
			setActivated(true);
		}
		else
		if(isActivated==true)
		{

			if(isScrollingDown==true)
			{
				isScrollingDown=false;
			}
			else
			{

				//ask the game to close instead of directly closing!

				if(getGame()!=null)
				{
					getGame().tryToCloseGame();

				}
				else
				setActivated(false);

			}
		}

	}

	//=========================================================================================================================
	public void setActivated(boolean b)
	{//=========================================================================================================================

		if(b==true&&enabled()==false)return;


		if(ClientGameEngine()!=null)
		{
			if(b==true)
			{
				FriendManager().myStatus = FriendCharacter.status_PLAYING_GAME;
			}
			else
			{
				FriendManager().myStatus = FriendCharacter.status_AVAILABLE;
			}
		}



		super.setActivated(b);

	}



	//=========================================================================================================================
	public void onScrolledUp()
	{//=========================================================================================================================

	}



	//=========================================================================================================================
	public void scrollUp()//zoomIn()
	{//=========================================================================================================================

		if(widthThisFrame!=targetWidth)
		{

			if(ticksSinceTurnedOn<=fadeInTime)widthThisFrame = (float) Easing.easeOutParabolicBounce(ticksSinceTurnedOn, 0.0f, targetWidth, fadeInTime);
			else widthThisFrame = targetWidth;

			float zWidth = widthTextureAspectRatio * widthThisFrame;
			float zHeight = (widthTextureAspectRatio / widthToHeightRatio) * widthThisFrame;

			nDDrawAlpha = (widthThisFrame*2.0f)/targetWidth;
			if(nDDrawAlpha>1.0f)nDDrawAlpha=1.0f;

			nDZoom = zWidth/texture.getTextureWidth();
		}
		else
		if(isScrolledUp==false)
		{
			onScrolledUp();
			isScrolledUp=true;
		}

	}


	//=========================================================================================================================
	public void scrollDown()//zoomOut()
	{//=========================================================================================================================

		if(widthThisFrame>0)
		{

			fadeMesh = true;
			fadeOutMeshTicks = 0;
			drawMeshAlpha = 1.0f;

			widthThisFrame = targetWidth-(float) Easing.easeInBackSlingshot(ticksSinceTurnedOff, 0.0f, targetWidth, fadeOutTime);

			float zWidth = widthTextureAspectRatio * (widthThisFrame);
			float zHeight = (widthTextureAspectRatio / widthToHeightRatio) * (widthThisFrame);

			nDDrawAlpha = (widthThisFrame*2.0f)/targetWidth;
			if(nDDrawAlpha>1.0f)nDDrawAlpha=1.0f;

			nDZoom = zWidth/texture.getTextureWidth();
		}
		else
		{
			isActivated=false;
			isScrollingDown=false;
		}

	}

	//=========================================================================================================================
	public static void setNDViewport()
	{//=========================================================================================================================
		glViewport(0, 0, SCREEN_SIZE_X*FBO_SCALE_MULTIPLIER, SCREEN_SIZE_Y*FBO_SCALE_MULTIPLIER);
		glLoadIdentity();
		glOrtho(0, SCREEN_SIZE_X*FBO_SCALE_MULTIPLIER, SCREEN_SIZE_Y*FBO_SCALE_MULTIPLIER, 0, -1, 1);
	}

	public static float BLOOM_FBO_SCALE = 0.25f;
	//=========================================================================================================================
	public static void setNDBloomViewport()
	{//=========================================================================================================================
		glViewport(0, 0, (int)(SCREEN_SIZE_X*FBO_SCALE_MULTIPLIER*BLOOM_FBO_SCALE), (int)(SCREEN_SIZE_Y*FBO_SCALE_MULTIPLIER*BLOOM_FBO_SCALE));
		glLoadIdentity();
		glOrtho(-1, 1, -1, 1, -1, 1);
	}


	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================

		if(isActivated==false)return;



		if(texture==null)return;



		float tx0 = 0.0f;
		float tx1 = 1.0f;
		float ty0 = 0.0f;
		float ty1 = 1.0f;

		float x0 = 0;
		float x1 = 0;
		float y0 = 0;
		float y1 = 0;



		//calculate width and height based on zoom

		float zWidth = (float)texture.getImageWidth()*widthTextureAspectRatio*nDZoom;
		float zHeight = (float)texture.getImageHeight()*heightTextureAspectRatio*nDZoom;

		//calculate screen x and y by centering based on width and height
		float screenX = (LWJGLUtils.SCREEN_SIZE_X-(zWidth/widthTextureAspectRatio))/2.0f;
		float screenY = (LWJGLUtils.SCREEN_SIZE_Y-(zHeight/heightTextureAspectRatio))/2.0f;


		x0 = screenX;
		x1 = screenX+(zWidth);
		y0 = screenY;
		y1 = screenY+(zHeight);





		//--------------------------
		//set the framebuffer to the nD FBO
		//--------------------------
		LWJGLUtils.bindFBO(LWJGLUtils.nDFBO);
		//glDrawBuffer(GL_COLOR_ATTACHMENT0);

		setNDViewport();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//--------------------------
		//render the game, which should render the map and entities, etc first.
		//--------------------------
		GLUtils.globalDrawScale=FBO_SCALE_MULTIPLIER;
		nDGameStateManager.render();
		GLUtils.globalDrawScale=1.0f;




		//--------------------------
		//set main FBO
		//--------------------------

		LWJGLUtils.bindFBO(LWJGLUtils.mainFBO);//set the framebuffer object to the MAIN FBO
		LWJGLUtils.drawIntoFBOAttachment(0);//set which framebuffer object to draw into (whatever buffer is set with glBindFramebuffer)

		//--------------------------
		//set main viewport
		//--------------------------
		LWJGLUtils.setViewport();

		//--------------------------
		//clear the main FBO
		//--------------------------
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//--------------------------
		//draw nD console background to main FBO
		//--------------------------
		GLUtils.drawTexture(texture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,nDDrawAlpha,GLUtils.FILTER_LINEAR);


		//--------------------------
		//draw nD FBO texture to main FBO
		//--------------------------

		float screenScale = (640.0f/(float)SCREEN_SIZE_X) * (float)FBO_SCALE_MULTIPLIER;
		//302x258
		float inScreenX = (((float)texture.getImageWidth()-SCREEN_SIZE_X*screenScale)/2)*nDZoom;
		float inScreenY = (((float)texture.getImageHeight()-SCREEN_SIZE_Y*screenScale)/2)*nDZoom;
		float inScreenWidth = SCREEN_SIZE_X*screenScale*nDZoom;
		float inScreenHeight = SCREEN_SIZE_Y*screenScale*nDZoom;


		float nDScreenOnScreenX0 = screenX+inScreenX;
		float nDScreenOnScreenX1 = screenX+inScreenX+inScreenWidth;

		float nDScreenOnScreenY0 = screenY+inScreenY;
		float nDScreenOnScreenY1 = screenY+inScreenY+inScreenHeight;


		//draw black background
		GLUtils.drawFilledRect(8,8,8,nDScreenOnScreenX0,nDScreenOnScreenX1,nDScreenOnScreenY0,nDScreenOnScreenY1,1.0f);

		//draw nD screen  (upside down because FBO is flipped)
		GLUtils.drawTexture(LWJGLUtils.nDFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, nDScreenOnScreenX0, nDScreenOnScreenX1, nDScreenOnScreenY0, nDScreenOnScreenY1, 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);



		//--------------------------
		// draw pixel mesh to main FBO
		//--------------------------

		//TODO: make glowing power lights, maybe slight glow on screen, maybe slight pixel filter on screen


		//if(fadeMesh)
		{

			//draw pixel mesh
			int meshDiv = SCREEN_SIZE_X/320;

			for(int x=0;x<SCREEN_SIZE_X/meshDiv;x++)
			{
				GLUtils.drawLine(nDScreenOnScreenX0+(x*meshDiv*screenScale*nDZoom),nDScreenOnScreenY0,nDScreenOnScreenX0+(x*meshDiv*screenScale*nDZoom),nDScreenOnScreenY1,0.1f,0.1f,0.1f,drawMeshAlpha);
			}
			for(int y=0;y<SCREEN_SIZE_Y/meshDiv;y++)
			{
				GLUtils.drawLine(nDScreenOnScreenX0,nDScreenOnScreenY0+(y*meshDiv*screenScale*nDZoom),nDScreenOnScreenX1,nDScreenOnScreenY0+(y*meshDiv*screenScale*nDZoom),0.1f,0.1f,0.1f,drawMeshAlpha);
			}
		}



		boolean drawScreenLight = true;

		if(LWJGLUtils.useShader)
		{
			if(drawScreenLight)
			{

				//--------------------------
				// set LIGHTS buffer in MAIN FBO
				//--------------------------
				//switch to LIGHTS buffer attachment
				LWJGLUtils.drawIntoFBOAttachment(1);//draws into lightFBOTextureID
				glClear(GL_COLOR_BUFFER_BIT);

				//--------------------------
				//draw the main FBO texture into the LIGHTS buffer attachment (upside down because FBO is flipped)
				//--------------------------
				GLUtils.drawTexture(LWJGLUtils.mainFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, (int)(LWJGLUtils.SCREEN_SIZE_X), 0.0f, (int)(LWJGLUtils.SCREEN_SIZE_Y), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);

				//--------------------------
				//switch to MAIN buffer attachment in MAIN FBO
				//--------------------------
				LWJGLUtils.drawIntoFBOAttachment(0);//draws into mainFBOTextureID


				//--------------------------
				// draw light into MAIN FBO mixing with LIGHT BUFFER TEXTURE (copy of MAIN FBO) to blend nicely
				//--------------------------
				LWJGLUtils.useShader(LWJGLUtils.lightShader);

				//set the LIGHTS FBO texture to texture 0, we drew the main FBO (maps and sprites) into it and we are going to use it to blend
				glActiveTexture(GL_TEXTURE0);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, LWJGLUtils.mainFBO_lightTexture);


				glActiveTexture(GL_TEXTURE1);//switch to texture 1, we are going to bind the light textures to this when we draw them.
				glEnable(GL_TEXTURE_2D);


				LWJGLUtils.setShaderVar1i(LWJGLUtils.lightShader, "Tex0", 0);
				LWJGLUtils.setShaderVar1i(LWJGLUtils.lightShader, "Tex1", 1);
				LWJGLUtils.setShaderVar1f(LWJGLUtils.lightShader, "width", LWJGLUtils.SCREEN_SIZE_X);
				LWJGLUtils.setShaderVar1f(LWJGLUtils.lightShader, "height", LWJGLUtils.SCREEN_SIZE_Y);


				float lightOffset = 48*nDZoom;
				//draw screen light
				if(light!=null)light.renderLight(nDScreenOnScreenX0-lightOffset,nDScreenOnScreenX1+lightOffset,nDScreenOnScreenY0-lightOffset,nDScreenOnScreenY1+lightOffset,lightAlpha);


				//disable texture2D on texture unit 1
				glActiveTexture(GL_TEXTURE1);
				glDisable(GL_TEXTURE_2D);

				//switch back to texture unit 0
				glActiveTexture(GL_TEXTURE0);
				glDisable(GL_TEXTURE_2D);

				LWJGLUtils.useShader(0);
			}
		}


		//--------------------------
		// switch back to SCREEN BUFFER (has game drawn in it)
		//--------------------------

		LWJGLUtils.bindFBO(0);//set the framebuffer back to the screen buffer
		glEnable(GL_TEXTURE_2D);

		//--------------------------
		// draw MAIN FBO texture into SCREEN BUFFER
		//--------------------------

		if(LWJGLUtils.useShader)
		{
			LWJGLUtils.useShader(LWJGLUtils.colorShader);

			LWJGLUtils.setShaderVar1f(LWJGLUtils.colorShader, "gameHue", 1.0f);
			LWJGLUtils.setShaderVar1f(LWJGLUtils.colorShader, "gameSaturation", 1.2f);
			LWJGLUtils.setShaderVar1f(LWJGLUtils.colorShader, "gameBrightness", 1.0f);
			LWJGLUtils.setShaderVar1f(LWJGLUtils.colorShader, "gameContrast", 1.2f);
			LWJGLUtils.setShaderVar1f(LWJGLUtils.colorShader, "gameGamma", 1.0f);
			LWJGLUtils.setShaderVar1i(LWJGLUtils.colorShader, "Tex0", 0);
		}

		//draw the framebuffer with the lights drawn into it into the screen buffer  (upside down because FBO is flipped)
		LWJGLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);//this fixes the small shadow problems, and also makes the doorknob glow brighter.
		GLUtils.drawTexture(LWJGLUtils.mainFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, (int)(LWJGLUtils.SCREEN_SIZE_X), 0.0f, (int)(LWJGLUtils.SCREEN_SIZE_Y), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);
		LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		if(LWJGLUtils.useShader)
		{
			LWJGLUtils.useShader(0);
		}

		//--------------------------
		// draw shine overlay over screen
		//--------------------------


		//DONE: make shiny screen overlay that moves when scrolling up
		//draw shine over screen
		float endShineRemovedSize = 1.0f;
		float shineSize = ((widthThisFrame/targetWidth) * ((inScreenHeight)*endShineRemovedSize));

		float shineOffset = 2*nDZoom;//2 (adjusted) pixels closer to bezel
		GLUtils.drawFilledRect(255,255,255,nDScreenOnScreenX0-shineOffset,nDScreenOnScreenX1+shineOffset,nDScreenOnScreenY0-shineOffset,(nDScreenOnScreenY0-shineOffset)+(inScreenHeight-shineSize),0.3f);




	}




	//=========================================================================================================================
	public void layout()
	{//=========================================================================================================================

		//we are overriding MenuPanel but it isnt really a widget, we're just using the same convenience functions.
		//so do nothing here.
	}








}
