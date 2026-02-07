package com.bobsgame.client.engine.game.gui.statusbar.captions;
import com.bobsgame.client.LWJGLUtils;


import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.client.engine.map.Light;
import com.bobsgame.client.engine.text.Caption;
import com.bobsgame.client.engine.text.CaptionManager;
import com.bobsgame.shared.BobColor;
import com.bobsgame.client.engine.text.BobFont;
//=========================================================================================================================
public class DayCaption extends StatusBarCaption
{//=========================================================================================================================

	//=========================================================================================================================
	public DayCaption(ClientGameEngine g)
	{//=========================================================================================================================
		super(g);
	}


	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================

		light = new Light(Engine(), "dayLight",-100,4,10,2,255,255,255,90,16,2.0f,1.0f,0,true,true);

		defaultFGColor = BobColor.WHITE;
		defaultAAColor = BobColor.GRAY;
		defaultBGColor = BobColor.CLEAR;

		currentFGColor = defaultFGColor;
		currentAAColor = defaultAAColor;


	}


	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

		if(caption!=null)
		{
			caption.screenX=LWJGLUtils.SCREEN_SIZE_X-95*2;//50*2;//timeCaption.caption_width*2;
			caption.setAlphaImmediately(1.0f);

			if(light!=null)light.setX(caption.screenX+caption.getWidth()/2-10);
		}
	}



	BobColor pausedFGColor = BobColor.DARKGRAY;
	BobColor pausedAAColor = BobColor.GRAY;
	BobColor pausedBGColor = BobColor.LIGHTGRAY;

	BobColor fastFGColor = BobColor.DARKERBLUE;
	BobColor fastAAColor = BobColor.DARKBLUE;
	BobColor fastBGColor = BobColor.BLUE;

	BobColor unknownFGColor = BobColor.WHITE;
	BobColor unknownAAColor = BobColor.LIGHTGRAY;
	BobColor unknownBGColor = BobColor.BLACK;

	//=========================================================================================================================
	public void setPausedColor()
	{//=========================================================================================================================
		setColors(pausedFGColor,pausedAAColor,pausedBGColor);
	}

	//=========================================================================================================================
	public void setUnknownColor()
	{//=========================================================================================================================
		setColors(unknownFGColor,unknownAAColor,unknownBGColor);
	}


	//=========================================================================================================================
	public void setFastSpeedColor()
	{//=========================================================================================================================
		setColors(fastFGColor,fastAAColor,fastBGColor);
	}



}
