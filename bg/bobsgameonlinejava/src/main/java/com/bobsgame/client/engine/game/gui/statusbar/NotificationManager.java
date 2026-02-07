package com.bobsgame.client.engine.game.gui.statusbar;

import java.util.ArrayList;

import com.bobsgame.client.Texture;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.client.engine.game.gui.statusbar.notification.Notification;


//=========================================================================================================================
public class NotificationManager extends EnginePart
{//=========================================================================================================================



	public ArrayList<Notification> notificationList = new ArrayList<Notification>();

	public static Texture loadingBarTexture = null;
	public static Texture loadingBarBackgroundTexture = null;




	//=========================================================================================================================
	public NotificationManager(ClientGameEngine g)
	{//=========================================================================================================================


		super(g);

		loadingBarTexture = GLUtils.loadTexture("res/statusbar/loadingBar.png");
		loadingBarBackgroundTexture = GLUtils.loadTexture("res/statusbar/loadingBarBackground.png");



		//TODO: manage multiple notifications, cycle through them, keep them in a dropdown log

		//TODO: have status bar movable to bottom


	}



	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================






	}



	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		for(int i=0;i<notificationList.size();i++)
		{
			notificationList.get(i).update();


		}

	}

	//=========================================================================================================================
	public void render(int layer)
	{//=========================================================================================================================
		for(int i=0;i<notificationList.size();i++)
		{
			notificationList.get(i).render(layer);


		}
	}



	//=========================================================================================================================
	public void add(Notification n)
	{//=========================================================================================================================


		notificationList.add(n);

	}


	//=========================================================================================================================
	public void remove(Notification n)
	{//=========================================================================================================================

		notificationList.remove(n);

	}












}
