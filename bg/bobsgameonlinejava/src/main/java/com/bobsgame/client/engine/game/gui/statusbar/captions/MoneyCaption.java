package com.bobsgame.client.engine.game.gui.statusbar.captions;
import com.bobsgame.client.LWJGLUtils;


import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.client.engine.game.gui.statusbar.StatusBar;
import com.bobsgame.client.engine.map.Light;
import com.bobsgame.shared.BobColor;


//=========================================================================================================================
public class MoneyCaption extends StatusBarCaption
{//=========================================================================================================================



	public int dividerX = 0;


	//=========================================================================================================================
	public MoneyCaption(ClientGameEngine g)
	{//=========================================================================================================================
		super(g);
	}



	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================

		light = new Light(Engine(), "moneyLight",-100,4,18,6,0,255,0,70,10,2.0f,1.0f,0,true,true);// divided by 2 because lights take 1x pixels from tools

		defaultFGColor = BobColor.GREEN;
		defaultAAColor = BobColor.DARKERGREEN;
		defaultBGColor = BobColor.CLEAR;

		currentFGColor = defaultFGColor;
		currentAAColor = defaultAAColor;


	}



	//=========================================================================================================================
	public void render(int layer)
	{//=========================================================================================================================

		if(enabled==false)return;

		super.render(layer);

		if(layer==1)
		{
			GLUtils.drawTexture(StatusBar.dividerTexture, dividerX, dividerX+3, 0, com.bobsgame.client.engine.game.gui.statusbar.StatusBar.sizeY-1, 1.0f, GLUtils.FILTER_LINEAR);
		}
	}


	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		if(caption!=null)
		{

			caption.screenX=LWJGLUtils.SCREEN_SIZE_X-(100*2)-caption.texture.getImageWidth();//100*2;//timeCaption.caption_width*2+dayCaption.caption_width*2;
			caption.setAlphaImmediately(1.0f);

			if(light!=null)light.setX(caption.screenX+caption.getWidth()/2-15);

			dividerX = (int)caption.screenX-20;
		}

	}









}
