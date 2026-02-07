package com.bobsgame.client.engine.game.gui.statusbar.captions;
import com.bobsgame.client.LWJGLUtils;

import java.io.File;


import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.TimeZone;

import com.bobsgame.client.Cache;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.client.engine.map.Light;
import com.bobsgame.client.engine.map.MapManager;
import com.bobsgame.client.engine.text.Caption;
import com.bobsgame.client.engine.text.CaptionManager;
import com.bobsgame.client.engine.text.BobFont;
import com.bobsgame.client.engine.text.TextManager;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.Utils;



//=========================================================================================================================
public class ClockCaption extends StatusBarCaption
{//=========================================================================================================================

	//=========================================================================================================================
	public ClockCaption(ClientGameEngine g)
	{//=========================================================================================================================
		super(g);
	}

	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================

		//TODO: replace these lights with just pre-made pngs, less hackiness.

		light = new Light(Engine(), "timeLight",-100,4,24,2,255,0,0,90,16,2.0f,1.0f,0,true,true);


		defaultFGColor = BobColor.RED;
		defaultAAColor = BobColor.DARKRED;
		defaultBGColor = BobColor.CLEAR;

		currentFGColor = defaultFGColor;
		currentAAColor = defaultAAColor;
		currentBGColor = defaultBGColor;

	}


	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		//if(timecaption!=null)timecaption->scale=2.0f/ZOOM;
		//if(daycaption!=null)daycaption->scale=2.0f/ZOOM;


		if(caption!=null)
		{
			caption.screenX=LWJGLUtils.SCREEN_SIZE_X-50*2;//50*2;//timeCaption.caption_width*2;

			//TODO: need to manually update the caption if they arent in the captionmanager. hmm. maybe have a different list for captions to be updated, or maybe just do captions by layer
			//TODO: make a global list of all captions that get updated, and a smaller managed subset that get rendered in the game

			//if i don't set the alpha they will never increase
			caption.setAlphaImmediately(1.0f);

			if(light!=null)light.setX(caption.screenX+caption.getWidth()/2-20);
		}

	}





	//=========================================================================================================================
	public void setDarkTheme()
	{//=========================================================================================================================


	}
	//=========================================================================================================================
	public void setLightTheme()
	{//=========================================================================================================================

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
	public void setFastColor()
	{//=========================================================================================================================
		setColors(fastFGColor,fastAAColor,fastBGColor);
	}




	//=========================================================================================================================
	public void setColors(BobColor fg, BobColor aa, BobColor bg)
	{//=========================================================================================================================

		super.setColors(fg,aa,bg);

		if(light!=null && (light.r()!=fg.ri() || light.g()!=fg.gi() || light.b()!=fg.bi()))
		{light.delete(); light = new Light(Engine(), "timeLight",-100,4,24,2,fg.ri(),fg.gi(),fg.bi(),90,16,2.0f,1.0f,0,true,true);}
	}





}
