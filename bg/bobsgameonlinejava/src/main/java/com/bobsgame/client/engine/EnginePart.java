package com.bobsgame.client.engine;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.ClientMain;
import com.bobsgame.client.ControlsManager;
import com.bobsgame.client.engine.cinematics.CinematicsManager;
import com.bobsgame.client.engine.entity.Cameraman;
import com.bobsgame.client.engine.entity.SpriteManager;
import com.bobsgame.client.engine.event.ActionManager;
import com.bobsgame.client.engine.event.EventManager;
import com.bobsgame.client.engine.game.Clock;
import com.bobsgame.client.engine.game.FriendManager;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.client.engine.game.Player;
import com.bobsgame.client.engine.game.Wallet;
import com.bobsgame.client.engine.game.gui.*;
import com.bobsgame.client.engine.game.gui.gameStore.GameStore;
import com.bobsgame.client.engine.game.gui.statusbar.*;
import com.bobsgame.client.engine.game.gui.stuffMenu.StuffMenu;
import com.bobsgame.client.engine.game.nd.*;
import com.bobsgame.client.engine.map.Map;
import com.bobsgame.client.engine.map.MapManager;
import com.bobsgame.client.engine.sound.AudioManager;
import com.bobsgame.client.engine.text.CaptionManager;
import com.bobsgame.client.engine.text.TextManager;
import com.bobsgame.client.network.GameClientTCP;
import com.bobsgame.net.GameSave;
import com.bobsgame.shared.MapData;
//=========================================================================================================================
public class EnginePart
{//=========================================================================================================================

	public static Logger log = (Logger) LoggerFactory.getLogger(EnginePart.class);


	private Engine e = null;

	private static ClientGameEngine clientGameEngine = null;
	private static ControlsManager controlsManager = null;


	private boolean isActivated = false;
	private long lastTimeHere = -1;
	private long timeActivated = -1;


	//=========================================================================================================================
	public EnginePart(Engine e)
	{//=========================================================================================================================
		this.e = e;

		//if(g==null)log.error("e is null");

	}

	public static void setClientGameEngine(ClientGameEngine gameEngine)
	{

		EnginePart.clientGameEngine = gameEngine;
	}

	public static void setControlsManager(ControlsManager controlsManager)
	{

		EnginePart.controlsManager = controlsManager;
	}






	public void toggleActivated()
	{
		isActivated = !isActivated;
		timeActivated = System.currentTimeMillis();


		//TODO: send flag update with this game object TYPEID

		//TODO: maybe instead of flag i should allow any kind of value: int, float, bool, string

		//so, GAMEVALUE
	}
	public void setActivated(boolean b)
	{
		isActivated = b;
		timeActivated = System.currentTimeMillis();

		//TODO: send flag update with this game object TYPEID
	}
	public boolean isActivated()
	{
		return isActivated;
	}
	public boolean wasEverActivated()
	{
		if(timeActivated==-1)return false;
		return true;
	}
	public int secondsSinceActivated()
	{
		if(timeActivated==-1)return 0;

		return (int)((System.currentTimeMillis()-timeActivated)/1000);
	}
	public boolean wasEverHere()
	{
		if(lastTimeHere==-1)return false;
		return true;
	}
	public void resetLastTimeHere()
	{
		lastTimeHere = -1;
	}
	public void setLastTimeHere()
	{
		lastTimeHere = System.currentTimeMillis();

		//TODO: send flag update with this game object TYPEID
	}
	public long getLastTimeHere()
	{
		return lastTimeHere;
	}
	public int secondsSinceLastHere()
	{
		if(lastTimeHere==-1)return -1;
		return (int)((System.currentTimeMillis()-lastTimeHere)/1000);
	}
	public int minutesSinceLastHere()
	{
		if(lastTimeHere==-1)return -1;
		return (int)(((System.currentTimeMillis()-lastTimeHere)/1000)/60);
	}




	public Engine Engine()
	{
		return e;
	}
	public Cameraman Cameraman()
	{
		return e.cameraman;
	}
	public MapManager MapManager()
	{
		return e.mapManager;
	}
	public SpriteManager SpriteManager()
	{
		return e.spriteManager;
	}
	public ActionManager ActionManager()
	{
		return e.actionManager;
	}
	public TextManager TextManager()
	{
		return e.textManager;
	}
	public AudioManager AudioManager()
	{
		return e.audioManager;
	}
	public CaptionManager CaptionManager()
	{
		return e.captionManager;
	}
	public EventManager EventManager()
	{
		return e.eventManager;
	}
	public CinematicsManager CinematicsManager()
	{
		return e.cinematicsManager;
	}

	public Map CurrentMap()
	{
		Map m = e.mapManager.currentMap;
		if(m==null)m = new Map(e,new MapData(-1,"none",0,0));
		return m;
	}


















	public static ControlsManager ControlsManager()
	{
		return controlsManager;
	}
	public static ClientGameEngine ClientGameEngine()
	{
		return clientGameEngine;
	}

	public static GameClientTCP Network()
	{
		if(ClientMain.clientMain==null)return null;
		return ClientMain.clientMain.gameClientTCP;
	}

	public static Clock Clock()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().clock;
	}
	public static GUIManager GUIManager()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().guiManager;
	}
	public static StuffMenu StuffMenu()
	{
		if(ClientGameEngine()==null)return null;
		return GUIManager().stuffMenu;
	}
	public static GameStore GameStore()
	{
		if(ClientGameEngine()==null)return null;
		return GUIManager().gameStore;
	}
	public static PlayerEditMenu PlayerEditMenu()
	{
		if(ClientGameEngine()==null)return null;
		return GUIManager().playerEditMenu;
	}
	public static Player Player()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().player;
	}
	public static ND ND()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().nD;
	}
	public static Wallet Wallet()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().wallet;
	}
	public static FriendManager FriendManager()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().friendManager;
	}
	public static StatusBar StatusBar()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().statusBar;
	}
	public static NotificationManager NotificationManager()
	{
		if(ClientGameEngine()==null)return null;
		return StatusBar().notificationManager;
	}
	synchronized public static GameSave GameSave()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().gameSave_S();
	}



//
//	public String getIDString()
//	{
//
//		return null;
//	}
//
//
//
//	public String getShortTypeName()
//	{
//
//		return null;
//	}




}
