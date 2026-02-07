package com.bobsgame.client.state;


import org.lwjgl.glfw.GLFW;
//import org.lwjgl.input.Keyboard;

import com.bobsgame.ClientMain;
import com.bobsgame.client.GLUtils;
import com.bobsgame.client.LWJGLUtils;
import com.bobsgame.shared.BobColor;

//=========================================================================================================================
public class LoggedOutState extends State
{//=========================================================================================================================





	//=========================================================================================================================
	public LoggedOutState()
	{//=========================================================================================================================



	}


	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

        // Keyboard.KEY_L -> GLFW.GLFW_KEY_L
        // Keyboard.isKeyDown -> GLFW.glfwGetKey
		if(GLFW.glfwGetKey(LWJGLUtils.window, GLFW.GLFW_KEY_L) == GLFW.GLFW_PRESS)
		{

			ClientMain.clientMain.stateManager.setState(ClientMain.clientMain.clientGameEngine);

		}

	}


	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================


		ClientMain.glowTileBackground.render();


		GLUtils.drawFilledRect(0, 0, 0, 0, LWJGLUtils.SCREEN_SIZE_X, 0, LWJGLUtils.SCREEN_SIZE_Y, 0.5f);
		GLUtils.drawOutlinedString("You have been logged out by a different session.", LWJGLUtils.SCREEN_SIZE_X/2-70, LWJGLUtils.SCREEN_SIZE_Y/2-12, BobColor.white);
		GLUtils.drawOutlinedString("Press L to take this session back and log out that one.", LWJGLUtils.SCREEN_SIZE_X/2-90, LWJGLUtils.SCREEN_SIZE_Y/2+12, BobColor.gray);

	}


	//=========================================================================================================================
	public void cleanup()
	{//=========================================================================================================================


	}




}
