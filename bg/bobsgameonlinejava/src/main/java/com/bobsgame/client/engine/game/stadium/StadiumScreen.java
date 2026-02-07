package com.bobsgame.client.engine.game.stadium;



import static org.lwjgl.opengl.GL11.*;
//import static org.lwjgl.opengl.GL30.*;
//import static org.lwjgl.opengl.GL31.*;
//import static org.lwjgl.opengl.GL32.*;
//import static org.lwjgl.opengl.GL33.*;
//import static org.lwjgl.opengl.GL40.*;


import com.bobsgame.client.GLUtils;
import com.bobsgame.client.LWJGLUtils;

import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.game.nd.ND;
import com.bobsgame.client.engine.map.Area;


import com.bobsgame.client.state.State;
import com.bobsgame.client.state.StateManager;


//=========================================================================================================================
public class StadiumScreen extends EnginePart
{//=========================================================================================================================




	public static final int SCREEN_SIZE_X = 640*2;
	public static final int SCREEN_SIZE_Y = 480*2;
	public static final int FBO_SCALE_MULTIPLIER = 1;




	public StateManager stadiumGameStateManager;





	Area area;

	//=========================================================================================================================
	public StadiumScreen(Engine g)
	{//=========================================================================================================================
		super(g);

		stadiumGameStateManager = new StateManager();

	}



	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================






		if(isActivated()==false)return;

		State s = stadiumGameStateManager.getState();
		if(s==null)return;


		GLUtils.globalDrawScale=FBO_SCALE_MULTIPLIER;
		if(s!=null)stadiumGameStateManager.update();
		GLUtils.globalDrawScale=1.0f;




	}


	//=========================================================================================================================
	public void setGame(StadiumGameEngine game, Area area)
	{//=========================================================================================================================

		this.area = area;


		stadiumGameStateManager.setState(game);

		this.setActivated(true);

	}


	//=========================================================================================================================
	public StadiumGameEngine getGame()
	{//=========================================================================================================================
		return (StadiumGameEngine)stadiumGameStateManager.getState();

	}







	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================

		if(isActivated()==false)return;

		if(area==null)return;

		if(stadiumGameStateManager.getState()==null)return;

		float x0 = area.screenLeft();
		float x1 = area.screenRight();
		float y0 = area.screenTop();
		float y1 = area.screenBottom();




		//--------------------------
		//set the framebuffer to the nD FBO
		//--------------------------
		LWJGLUtils.bindFBO(LWJGLUtils.nDFBO);
		//glDrawBuffer(GL_COLOR_ATTACHMENT0);

		ND.setNDViewport();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//--------------------------
		//render the game, which should render the map and entities, etc first.
		//--------------------------
		GLUtils.globalDrawScale=FBO_SCALE_MULTIPLIER;
		stadiumGameStateManager.render();
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
		//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//glClear(GL_COLOR_BUFFER_BIT);


		//--------------------------
		//draw nD FBO texture to main FBO
		//--------------------------



		//draw black background
		//GLUtils.drawFilledRect(8,8,8,x0,x1,y0,y1,1.0f);

		//draw nD screen  (upside down because FBO is flipped)
		//GLUtils.drawTexture(LWJGLUtils.nDFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, x0, x1, y0, y1, 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);


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
		//if(!Keyboard.isKeyDown(Keyboard.KEY_SEMICOLON))
		LWJGLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);//this fixes the small shadow problems, and also makes the doorknob glow brighter.
		//GLUtils.drawTexture(LWJGLUtils.mainFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, (int)(LWJGLUtils.SCREEN_SIZE_X), 0.0f, (int)(LWJGLUtils.SCREEN_SIZE_Y), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);

		GLUtils.drawTexture(LWJGLUtils.nDFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, x0, x1, y0, y1, 1.0f, GLUtils.FILTER_FBO_LINEAR_NO_MIPMAPPING);

		//GLUtils.drawTexture(LWJGLUtils.mainFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, (int)(LWJGLUtils.SCREEN_SIZE_X), 0.0f, (int)(LWJGLUtils.SCREEN_SIZE_Y), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);
		//if(!Keyboard.isKeyDown(Keyboard.KEY_APOSTROPHE))
		LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		if(LWJGLUtils.useShader)
		{
			LWJGLUtils.useShader(0);
		}





//
//		boolean drawScreenLight = true;
//
//		if(LWJGLUtils.useShader)
//		{
//			if(drawScreenLight)
//			{
//
//				//--------------------------
//				// set LIGHTS buffer in MAIN FBO
//				//--------------------------
//				//switch to LIGHTS buffer attachment
//				glDrawBuffer(GL_COLOR_ATTACHMENT1);//draws into lightFBOTextureID
//				glClear(GL_COLOR_BUFFER_BIT);
//
//				//--------------------------
//				//draw the main FBO texture into the LIGHTS buffer attachment (upside down because FBO is flipped)
//				//--------------------------
//				GLUtils.drawTexture(LWJGLUtils.mainFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, (int)(LWJGLUtils.SCREEN_SIZE_X), 0.0f, (int)(LWJGLUtils.SCREEN_SIZE_Y), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);
//
//				//--------------------------
//				//switch to MAIN buffer attachment in MAIN FBO
//				//--------------------------
//				glDrawBuffer(GL_COLOR_ATTACHMENT0);//draws into mainFBOTextureID
//
//
//				//--------------------------
//				// draw light into MAIN FBO mixing with LIGHT BUFFER TEXTURE (copy of MAIN FBO) to blend nicely
//				//--------------------------
//				glUseProgram(LWJGLUtils.lightShader);
//
//				//set the LIGHTS FBO texture to texture 0, we drew the main FBO (maps and sprites) into it and we are going to use it to blend
//				glActiveTexture(GL_TEXTURE0);
//				glEnable(GL_TEXTURE_2D);
//				glBindTexture(GL_TEXTURE_2D, LWJGLUtils.mainFBO_lightTexture);
//
//
//				glActiveTexture(GL_TEXTURE1);//switch to texture 1, we are going to bind the light textures to this when we draw them.
//				glEnable(GL_TEXTURE_2D);
//
//
//				glUniform1i(glGetUniformLocation(LWJGLUtils.lightShader, new StringBuffer("Tex0")), 0);
//				glUniform1i(glGetUniformLocation(LWJGLUtils.lightShader, new StringBuffer("Tex1")), 1);
//				glUniform1f(glGetUniformLocation(LWJGLUtils.lightShader, new StringBuffer("width")), LWJGLUtils.SCREEN_SIZE_X);
//				glUniform1f(glGetUniformLocation(LWJGLUtils.lightShader, new StringBuffer("height")), LWJGLUtils.SCREEN_SIZE_Y);
//
//
//				float lightOffset = 48*Cameraman().zoom;
//				//draw screen light
//				if(light!=null)light.renderLight(x0-lightOffset,x1+lightOffset,y0-lightOffset,y1+lightOffset,lightAlpha);
//
//
//				//disable texture2D on texture unit 1
//				glActiveTexture(GL_TEXTURE1);
//				glDisable(GL_TEXTURE_2D);
//
//				//switch back to texture unit 0
//				glActiveTexture(GL_TEXTURE0);
//				glDisable(GL_TEXTURE_2D);
//
//				glUseProgram(0);
//			}
//		}

//
//		//--------------------------
//		// switch back to SCREEN BUFFER (has game drawn in it)
//		//--------------------------
//
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);//set the framebuffer back to the screen buffer
//		glEnable(GL_TEXTURE_2D);
//
//		LWJGLUtils.setViewport();
//
//		//--------------------------
//		// draw MAIN FBO texture into SCREEN BUFFER
//		//--------------------------
//
//		if(LWJGLUtils.useShader)
//		{
//			glUseProgram(LWJGLUtils.colorShader);
//
//			glUniform1f(glGetUniformLocation(LWJGLUtils.colorShader, new StringBuffer("gameHue")), 1.0f);
//			glUniform1f(glGetUniformLocation(LWJGLUtils.colorShader, new StringBuffer("gameSaturation")), 1.2f);
//			glUniform1f(glGetUniformLocation(LWJGLUtils.colorShader, new StringBuffer("gameBrightness")), 1.0f);
//			glUniform1f(glGetUniformLocation(LWJGLUtils.colorShader, new StringBuffer("gameContrast")), 1.2f);
//			glUniform1f(glGetUniformLocation(LWJGLUtils.colorShader, new StringBuffer("gameGamma")), 1.0f);
//			glUniform1i(glGetUniformLocation(LWJGLUtils.colorShader, new StringBuffer("Tex0")), 0);
//		}
//
//		//draw the framebuffer with the lights drawn into it into the screen buffer  (upside down because FBO is flipped)
//		LWJGLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);//this fixes the small shadow problems, and also makes the doorknob glow brighter.
//		//GLUtils.drawTexture(LWJGLUtils.mainFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, (int)(LWJGLUtils.SCREEN_SIZE_X), 0.0f, (int)(LWJGLUtils.SCREEN_SIZE_Y), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);
//		GLUtils.drawTexture(LWJGLUtils.mainFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, (int)(LWJGLUtils.SCREEN_SIZE_X), 0.0f, (int)(LWJGLUtils.SCREEN_SIZE_Y), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);
//		LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//
//		if(LWJGLUtils.useShader)
//		{
//			glUseProgram(0);
//		}
//



	}







}
