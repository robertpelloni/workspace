package com.bobsgame.client.engine;


import java.util.ArrayDeque;

import com.bobsgame.client.LWJGLUtils;
import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.ControlsManager;
import com.bobsgame.client.console.Console;
import com.bobsgame.client.console.ConsoleText;
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
import com.bobsgame.client.engine.game.gui.GUIManager;
import com.bobsgame.client.engine.game.gui.PlayerEditMenu;
import com.bobsgame.client.engine.game.gui.gameStore.GameStore;
import com.bobsgame.client.engine.game.gui.statusbar.NotificationManager;
import com.bobsgame.client.engine.game.gui.statusbar.StatusBar;
import com.bobsgame.client.engine.game.gui.stuffMenu.StuffMenu;
import com.bobsgame.client.engine.game.nd.ND;
import com.bobsgame.client.engine.map.Map;
import com.bobsgame.client.engine.map.MapManager;
import com.bobsgame.client.engine.sound.AudioManager;
import com.bobsgame.client.engine.text.CaptionManager;
import com.bobsgame.client.engine.text.TextManager;





import com.bobsgame.client.state.State;
import com.bobsgame.net.GameSave;
import com.bobsgame.shared.MapData;
import com.bobsgame.shared.MapData.RenderOrder;


//=========================================================================================================================
public class Engine extends State
{//=========================================================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(Engine.class);








	//i could make these all static singletons, init them with new ThingManager(this) and just access them with ThingManager.update()

	//public LuaAPI luaAPI = new LuaAPI(this);

	public AudioManager audioManager = null;



	public Cameraman cameraman = null;


	public SpriteManager spriteManager = null;
	public ActionManager actionManager = null;
	public MapManager mapManager = null;
	public CinematicsManager cinematicsManager = null;
	public CaptionManager captionManager = null;
	public TextManager textManager = null;
	public EventManager eventManager = null;



	public ArrayDeque<Cameraman> cameramanStack = new ArrayDeque<Cameraman>();



























	public boolean hitLayerEnabled = true;
	public boolean underLayerEnabled = true;
	public boolean overLayerEnabled = true;
	public boolean entityLayerEnabled = true;
	public boolean lightsLayerEnabled = true;

	public boolean debugLayerEnabled = false;




	//DebugText cameraSpeedText = DebugConsole.add("cameraSpeedText");
	public ConsoleText zoomText = Console.debug("zoomText");

	public ConsoleText mapCamText = Console.debug("mapCamText");
	public ConsoleText mapScreenText = Console.debug("mapScreenText");

	public ConsoleText mapSizeText = Console.debug("mapSizeText");
	public ConsoleText resolutionText = Console.debug("resolutionText");

	public ConsoleText textText = Console.debug("textText");
	public ConsoleText textOptionText = Console.debug("textOptionText");

	public ConsoleText texturesLoadedText = Console.debug("texturesLoadedText");
	public ConsoleText textureBytesLoadedText = Console.debug("textureBytesLoadedText");


















	//=========================================================================================================================
	public Engine()
	{//=========================================================================================================================

		audioManager = new AudioManager(this);

		spriteManager = new SpriteManager(this);

		mapManager = new MapManager(this);
		cinematicsManager = new CinematicsManager(this);
		captionManager = new CaptionManager(this);
		textManager = new TextManager(this);

		eventManager = new EventManager(this);




		cameraman = new Cameraman(this);
		actionManager = new ActionManager(this);

	}



	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================




		actionManager.init();
		textManager.init();

		audioManager.init();

		spriteManager.init();

		mapManager.init();
		cinematicsManager.init();
		captionManager.init();

		eventManager.init();


	}




	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================




		/*
		try
		{
			InputStream luaScript = Utils.getResourceAsStream("lua/script.lua");
			LuaClosure closure = LuaCompiler.loadis(luaScript, "", env);
			caller.protectedCall(thread, closure);
		}
		catch(IOException ioe)
		{

		}
		*/





		audioManager.update();

		textManager.update();

		captionManager.update();

		spriteManager.update();

		cameraman.update();

		mapManager.update();//map adjusts itself based on cameraman xy so it must update after entities do



		actionManager.update();
		eventManager.update();
		cinematicsManager.update();


		updateDebugText();

	}


	//=========================================================================================================================
	public void cleanup()
	{//=========================================================================================================================

		mapManager.cleanup();
	}




	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================

		super.render();

		MapManager().render();//does entities as well, multi-layered rendering here.

		SpriteManager().renderScreenSprites(RenderOrder.ABOVE);

		CaptionManager().render(RenderOrder.ABOVE);

		SpriteManager().renderScreenSprites(RenderOrder.ABOVE_TOP);

		CaptionManager().render(RenderOrder.ABOVE_TOP);

		//if(!Keyboard.isKeyDown(Keyboard.KEY_LBRACKET))LWJGLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		CinematicsManager().render(RenderOrder.ABOVE_TOP);
		//if(!Keyboard.isKeyDown(Keyboard.KEY_RBRACKET))LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		TextManager().render();

		MapManager().renderEntities(RenderOrder.OVER_TEXT);

		SpriteManager().renderScreenSprites(RenderOrder.OVER_TEXT);//screensprites

		CaptionManager().render(RenderOrder.OVER_TEXT);

		MapManager().renderDebug();

		SpriteManager().renderScreenSprites(RenderOrder.OVER_GUI);

		CaptionManager().render(RenderOrder.OVER_GUI);

	}



	//=========================================================================================================================
	public void updateDebugText()
	{//=========================================================================================================================

		//playerSpeedText.text = "Player speed: " + player.pixelsToMoveThisFrame;
		//cameraSpeedText.text = "Camera speed: " + cameraman.pixelsToMoveThisFrame;
		zoomText.text = "Zoom level: " + cameraman.getZoom() + " ZoomTO: " + cameraman.ZOOMto;

		mapCamText.text = "Map cam xy: " + CurrentMap().mapCamX() + "," + CurrentMap().mapCamY();
		mapScreenText.text = "Map screen xy: " + CurrentMap().screenX() + "," + CurrentMap().screenY();

		mapSizeText.text = "Map: " +CurrentMap().name() + " | Size : " + CurrentMap().widthPixelsHQ() + " x " + CurrentMap().heightPixelsHQ() + " PixelsHQ | " + CurrentMap().widthTiles1X() + " x " + CurrentMap().heightTiles1X() + " Tiles 1X ";

		resolutionText.text = "Window res: "+LWJGLUtils.SCREEN_SIZE_X+" x "+LWJGLUtils.SCREEN_SIZE_Y+" ("+(int)LWJGLUtils.SCREEN_SIZE_X/2/cameraman.getZoom()+" x "+(int)LWJGLUtils.SCREEN_SIZE_Y/2/cameraman.getZoom()+")";

		textText.text = "Text: "+textManager.currentText;
		textOptionText.text = "Text option: "+textManager.optionBuffer;

		texturesLoadedText.text = "Textures Loaded: "+GLUtils.texturesLoaded;
		textureBytesLoadedText.text = "Texture MBs Loaded: "+GLUtils.textureBytesLoaded/1024/1024;
	}


	//=========================================================================================================================
	public Object getGameObjectByTYPEIDName(String typeIDName)
	{//=========================================================================================================================




		//typeIDName always looks like TYPE.id
		//MUSIC.1
		//DIALOGUE.0f
		//STATE.4
		//AREA.15

		//areas, entities, and lights are map-specific and are created when the map loads, and destroyed when the map changes.
		//they always have the same ID when they are created, but they may not exist if the map is not loaded.

		//this function is intended to be called when event parameters are parsed,
		//upon loading new events inside of objects (inside of maps), because objects are referenced by id name inside event strings send from the server,
		//based on the exported IDs from the tools, which indexes everything uniquely.
		//therefore all of the objects that a script references will exist inside the map the event is being called from.
		//these references will break every time the map is loaded and unloaded and the objects are destroyed, so an event must re-parse all the parameters each time the map is loaded.

		int id = -1;
		try{id = Integer.parseInt(typeIDName.substring(typeIDName.indexOf(".")+1));}catch(NumberFormatException ex){ex.printStackTrace();return null;}

		//global objects
		if(typeIDName.startsWith("MAP.")){return MapManager().getMapByIDBlockUntilLoaded(id);}
		if(typeIDName.startsWith("SPRITE.")){return SpriteManager().getSpriteAssetByIDOrRequestFromServerIfNotExist(id);}
		if(typeIDName.startsWith("DIALOGUE.")){return EventManager().getDialogueByIDCreateIfNotExist(id);}
		if(typeIDName.startsWith("EVENT.")){return EventManager().getEventByIDCreateIfNotExist(id);}
		if(typeIDName.startsWith("FLAG.")){return EventManager().getFlagByIDCreateIfNotExist(id);}
		if(typeIDName.startsWith("SKILL.")){return EventManager().getSkillByIDCreateIfNotExist(id);}
		if(typeIDName.startsWith("GAMESTRING.")){return EventManager().getGameStringByIDCreateIfNotExist(id);}
		if(typeIDName.startsWith("MUSIC.")){return AudioManager().getMusicByIDCreateIfNotExist(id);}
		if(typeIDName.startsWith("SOUND.")){return AudioManager().getSoundByIDCreateIfNotExist(id);}


		//map objects (will only exist within the current map)
		if(typeIDName.startsWith("STATE.")){return MapManager().getMapStateByID(id);}
		if(typeIDName.startsWith("ENTITY.")){return MapManager().getEntityByID(id);}
		if(typeIDName.startsWith("AREA.")){return MapManager().getAreaByID(id);}
		if(typeIDName.startsWith("LIGHT.")){return MapManager().getLightByID(id);}
		if(typeIDName.startsWith("DOOR.")){return MapManager().getDoorByID(id);}


		return null;
	}






	public Cameraman Cameraman()
	{
		return cameraman;
	}
	public MapManager MapManager()
	{
		return mapManager;
	}
	public SpriteManager SpriteManager()
	{
		return spriteManager;
	}
	public ActionManager ActionManager()
	{
		return actionManager;
	}
	public TextManager TextManager()
	{
		return textManager;
	}
	public AudioManager AudioManager()
	{
		return audioManager;
	}
	public CaptionManager CaptionManager()
	{
		return captionManager;
	}
	public EventManager EventManager()
	{
		return eventManager;
	}

	public CinematicsManager CinematicsManager()
	{
		return cinematicsManager;
	}
	public Map CurrentMap()
	{
		Map m = mapManager.currentMap;
		if(m==null)m = new Map(this,new MapData(-1,"none",0,0));
		return m;
	}










	private static ControlsManager controlsManager;
	private static ClientGameEngine clientGameEngine;

	public static void setClientGameEngine(ClientGameEngine clientGameEngine)
	{
		Engine.clientGameEngine = clientGameEngine;
		EnginePart.setClientGameEngine(clientGameEngine);
	}

	public static void setControlsManager(ControlsManager controlsManager)
	{
		Engine.controlsManager = controlsManager;
		EnginePart.setControlsManager(controlsManager);
	}



	public static ControlsManager ControlsManager()
	{
		return controlsManager;
	}
	public static ClientGameEngine ClientGameEngine()
	{
		return clientGameEngine;
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



	public float getWidth()
	{
		return LWJGLUtils.SCREEN_SIZE_X; //LWJGLUtils.SCREEN_SIZE_X;
	}

	public float getHeight()
	{
		return LWJGLUtils.SCREEN_SIZE_Y; //LWJGLUtils.SCREEN_SIZE_Y;
	}

	public float getWidthRelativeToZoom()
	{
		return getWidth()/Cameraman().getZoom();
	}

	public float getHeightRelativeToZoom()
	{
		return getHeight()/Cameraman().getZoom();
	}


}
