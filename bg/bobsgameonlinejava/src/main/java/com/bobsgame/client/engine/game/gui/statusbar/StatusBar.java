package com.bobsgame.client.engine.game.gui.statusbar;


import com.bobsgame.client.LWJGLUtils;
import com.bobsgame.client.Texture;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.client.engine.game.gui.statusbar.buttons.GameStoreButton;
import com.bobsgame.client.engine.game.gui.statusbar.buttons.NDButton;
import com.bobsgame.client.engine.game.gui.statusbar.buttons.StuffButton;
import com.bobsgame.client.engine.game.gui.statusbar.captions.ClockCaption;
import com.bobsgame.client.engine.game.gui.statusbar.captions.DayCaption;
import com.bobsgame.client.engine.game.gui.statusbar.captions.MoneyCaption;
import com.bobsgame.shared.BobColor;


//=========================================================================================================================
public class StatusBar extends EnginePart
{//=========================================================================================================================



	static public Texture blackBackgroundTexture = null;
	static public Texture blackForegroundTexture = null;

	static public Texture whiteBackgroundTexture = null;
	static public Texture whiteForegroundTexture = null;

	static public Texture backgroundTexture = null;
	static public Texture foregroundTexture = null;


	static public Texture glowTexture = null;
	static public Texture dividerTexture = null;


	public static int sizeY = 26;

	static public float glossAlpha=1.0f;

	static public boolean useLightTheme = false;

	public ClockCaption clockCaption;
	public DayCaption dayCaption;
	public MoneyCaption moneyCaption;
	public NDButton ndButton;
	public GameStoreButton gameStoreButton;
	public StuffButton stuffButton;

	public NotificationManager notificationManager;




	public boolean enabled = true;


	//=========================================================================================================================
	public StatusBar(ClientGameEngine g)
	{//=========================================================================================================================

		super(g);

		clockCaption = new ClockCaption(g);
		dayCaption = new DayCaption(g);
		moneyCaption = new MoneyCaption(g);
		ndButton = new NDButton(g);
		gameStoreButton = new GameStoreButton(g);
		stuffButton = new StuffButton(g);

		notificationManager = new NotificationManager(g);



		blackBackgroundTexture = GLUtils.loadTexture("res/statusbar/blackbarbackground.png");
		blackForegroundTexture = GLUtils.loadTexture("res/statusbar/blackbarforeground.png");

		whiteBackgroundTexture = GLUtils.loadTexture("res/statusbar/whitebarbackground.png");
		whiteForegroundTexture = GLUtils.loadTexture("res/statusbar/whitebarforeground.png");

		backgroundTexture = blackBackgroundTexture;
		foregroundTexture = blackForegroundTexture;




		glowTexture = GLUtils.loadTexture("res/statusbar/greenDot.png");
		dividerTexture = GLUtils.loadTexture("res/statusbar/dividerLine.png");
	}


	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================

		clockCaption.init();
		dayCaption.init();
		moneyCaption.init();
		ndButton.init();
		gameStoreButton.init();
		stuffButton.init();

		notificationManager.init();



	}



	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================
		clockCaption.update();
		dayCaption.update();
		moneyCaption.update();

		ndButton.update();
		gameStoreButton.update();
		stuffButton.update();

		notificationManager.update();
	}



	//=========================================================================================================================
	public void setLightTheme()
	{//=========================================================================================================================

		if(useLightTheme==false)
		{

			useLightTheme=true;
			backgroundTexture = whiteBackgroundTexture;
			foregroundTexture = whiteForegroundTexture;


			clockCaption.setColors(new BobColor(200,0,0),BobColor.LIGHTRED,null);
			dayCaption.setColors(BobColor.BLACK, BobColor.LIGHTERGRAY,null);
			moneyCaption.setColors(BobColor.GREEN,BobColor.DARKERGREEN,null);

		}
	}
	//=========================================================================================================================
	public void setDarkTheme()
	{//=========================================================================================================================
		if(useLightTheme==true)
		{

			useLightTheme=false;
			backgroundTexture = blackBackgroundTexture;
			foregroundTexture = blackForegroundTexture;


			clockCaption.setColors(BobColor.RED,BobColor.DARKERRED,null);
			dayCaption.setColors(BobColor.WHITE,BobColor.DARKERGRAY,null);
			moneyCaption.setColors(BobColor.GREEN,BobColor.DARKERGREEN,null);

		}
	}

	//=========================================================================================================================
	public void setEnabled(boolean b)
	{//=========================================================================================================================
		enabled = b;
	}

	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================


		if(enabled==false)return;



		render(0);

		clockCaption.render(0);//text, lights
		dayCaption.render(0);
		moneyCaption.render(0);


		ndButton.render(0);//button graphics
		gameStoreButton.render(0);
		stuffButton.render(0);

		notificationManager.render(0);//notification string

		render(1);//status bar gloss


		clockCaption.render(1);//nothing
		dayCaption.render(1);//nothing
		moneyCaption.render(1);//divider



		ndButton.render(1);//dividers
		gameStoreButton.render(1);
		stuffButton.render(1);


		notificationManager.render(1);//nothing yet


	}

	//=========================================================================================================================
	public void render(int layer)
	{//=========================================================================================================================

		if(enabled==false)return;

		Texture texture = null;
		if(layer==0)texture = backgroundTexture;
		if(layer==1)texture = foregroundTexture;

		float alpha = 1.0f;
		if(layer==1)alpha = glossAlpha;



		GLUtils.drawTexture(texture, 0, LWJGLUtils.SCREEN_SIZE_X, -6, sizeY+6, alpha, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);

	}



}
