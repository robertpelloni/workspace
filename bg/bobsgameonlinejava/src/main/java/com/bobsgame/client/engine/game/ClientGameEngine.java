package com.bobsgame.client.engine.game;




import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.List;

//import static org.lwjgl.opengl.GL30.*;
//import static org.lwjgl.opengl.GL31.*;
//import static org.lwjgl.opengl.GL32.*;
//import static org.lwjgl.opengl.GL33.*;
//import static org.lwjgl.opengl.GL40.*;
//import static org.lwjgl.opengl.GL41.*;




import org.apache.commons.io.IOUtils;

import com.bobsgame.ClientMain;
import com.bobsgame.client.LWJGLUtils;
import com.bobsgame.client.console.*;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.entity.Sprite;
import com.bobsgame.client.engine.event.Dialogue;
import com.bobsgame.client.engine.event.Event;
import com.bobsgame.client.engine.event.Flag;
import com.bobsgame.client.engine.event.GameString;
import com.bobsgame.client.engine.event.Skill;
import com.bobsgame.client.engine.game.gui.GUIManager;
import com.bobsgame.client.engine.game.gui.statusbar.StatusBar;
import com.bobsgame.client.engine.game.nd.ND;
import com.bobsgame.client.engine.game.nd.bobsgame.BobsGame;
import com.bobsgame.client.engine.game.stadium.StadiumScreen;
import com.bobsgame.client.engine.map.Map;
import com.bobsgame.client.engine.sound.Music;
import com.bobsgame.client.engine.sound.Sound;


import com.bobsgame.client.network.GameClientTCP;
import com.bobsgame.net.BobNet;
import com.bobsgame.net.GameSave;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.DialogueData;
import com.bobsgame.shared.EventData;
import com.bobsgame.shared.FlagData;
import com.bobsgame.shared.GameStringData;
import com.bobsgame.shared.MapData;
import com.bobsgame.shared.MusicData;
import com.bobsgame.shared.SkillData;
import com.bobsgame.shared.SoundData;
import com.bobsgame.shared.SpriteData;
import com.bobsgame.shared.Utils;



//=========================================================================================================================
public class ClientGameEngine extends Engine
{//=========================================================================================================================


	//DebugText playerSpeedText = DebugConsole.add("playerSpeedText");

	public ConsoleText playerMapText = Console.debug("playerMapText");
	public ConsoleText playerScreenText = Console.debug("playerScreenText");


	public GUIManager guiManager = null;
	public StatusBar statusBar = null;
	public Wallet wallet = null;

	public Clock clock = null;


	public Player normalPlayer = null;
	public Player player = null;

	public FriendManager friendManager = null;

	public ND nD = null;
	public StadiumScreen stadiumScreen = null;

	public com.bobsgame.puzzle.GameLogic gameLogic;



	public boolean controlsEnabled = true;
	public boolean playerExistsInMap = true;



	//=========================================================================================================================
	public ClientGameEngine()
	{//=========================================================================================================================

		super();

	}

	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================

		clock = new Clock(this);

		player = new Player(this);
		normalPlayer = player;

		guiManager = new GUIManager(this);

		statusBar = new StatusBar(this);
		wallet = new Wallet(this);

		friendManager = new FriendManager(this);

		nD = new ND();
		stadiumScreen = new StadiumScreen(this);


		if(ClientMain.previewClientInEditor==false)loadPreCachedObjectData();

		super.init();

		guiManager.init();

		statusBar.init();

		wallet.init();




		nD.init();
		//nD.setActivated(true);



		BobsGame bobsgame = new BobsGame(nD);
		//bobsgame.setConnection(null);
		bobsgame.init();
//		nDMenu.addGame(ping,"Ping",BobColor.BLUE);
//		nDMenu.addGame(ramio,"Ramio",BobColor.RED);
//		nDMenu.addGame(bobsgame,"\"bob's game\"",BobColor.GREEN);
		nD.setGame(bobsgame);








		friendManager.init();

		//mapManager.changeMap("TOWNYUUDownstairs",30,18);
		//mapManager.changeMap("TOWNVideoRentAdultRoom",10,10);
		//mapManager.changeMap("CITYTheCafe",10,10);
		//mapManager.changeMap("TOWNTacoBurger",53,110);
		//mapManager.changeMap("BLANK",16,16);
		//mapManager.changeMap("TOWNCoffeeShop",53,110);//start nowhere
		//mapManager.changeMap("CITYCityHallEntrance",53,110);
		//mapManager.changeMap("CITYStadiumBackstage",80,140);
		//mapManager.changeMap("TOWNPets4Less",53,110);
		//mapManager.changeMap("TOWNMovieTheatreMensBathroom",53,110);

		cameraman.setTarget(player);


		//can't remember why i did this, to fix gui stuff???
		cameraman.update();//TODO: fix this so it only updates ONE TICK


		cameraman.setXYToTarget();//TODO: fix this so it goes to xtarget (camstop tiles) instead of just npc target (player)



		//itemManager.ITEM_get_no_caption(new Item("nD","The indie handheld Game() console. A juggernaut of disposable technology, devised as a vengeful scheme to destroy the traditional Game() industry. Invented by a secretive, notoriously stubborn developer whose first Game() was held back by corrupt, obsolete corporate policy. So cheap and ubiquitous that every kid has two or three- making it a modern societal requirement."));
		//itemManager.ITEM_get_no_caption(new Item("Wallet","This holds your old receipts, slowly rubbing the ink off so the paper can be reused to write down phone numbers- if only you had a pen!"));
		//itemManager.ITEM_get_no_caption(new Item("Keys","These relics of long-antiquated technology give an illusion of security. Easily lost, they weigh down your pants, scratch everything in your pockets, and are generally uncomfortable, noisy metal daggers. Don't ever leave home without them!"));
		//itemManager.ITEM_get_no_caption(new Item("Smartphone","This infinitely helpful device keeps you constantly distracted and tracks your every move for a huge monthly fee. Sometimes you begin to wonder if it is making you more impulsive and helpless, and are fortunately comforted by its glow just as panic sets in. Scientists are pretty sure it doesn't cause brain cancer!"));



		//new EasingTest();

		//cinematicsManager.toggleLetterbox(true);
		//textManager.text("Yuu normal font <TINY>tiny font <SMALL><GREEN>small font <WHITE><HUGE>huge font <.><SMALL><NORMAL><NEXTLINE>next line <1>top text box<0>bottom text box");

		//captionManager.CAPTION_make_caption(Caption.CAPTION_CENTERED_SCREEN,0,Caption.CAPTION_DELETE_WHEN_MAIN_SPRITE_MOVES,"CAPTION_CENTERED_SCREEN",0,BobColor.white,BobColor.black,4,1.0f,0);
		//captionManager.CAPTION_make_caption(Caption.CAPTION_CENTERED_OVER_SPRITE,0,-1,"CAPTION_CENTERED_OVER_SPRITE",0,BobColor.white,BobColor.black,4,1.0f,0);
		//captionManager.CAPTION_make_caption(Caption.CAPTION_CENTERED_X,0,Caption.CAPTION_DELETE_WHEN_MAIN_SPRITE_MOVES,"CAPTION_CENTERED_X",0,BobColor.white,BobColor.black,4,1.0f,0);


		//new Notification("This is the notification area.");
		//new Notification("This is the notification area. Important messages will show up here periodically to let you know about events or whatever.");



	}






	long networkDelayTime = 0;
	long reloginTicks = 3001;
	long reconnectTicks = 3001;



	long checkInitialGameSaveReceivedDelayTime = 0;
	boolean initialGameSaveReceived_nonThreaded = false;
	private boolean _initialGameSaveRecieved = false;//synchronized
	synchronized public boolean getInitialGameSaveReceived_S(){return _initialGameSaveRecieved;}
	synchronized public void setInitialGameSaveReceived_S(boolean b){_initialGameSaveRecieved = b;}


	private boolean isGameSaveInitialized_nonThreaded = false;
	private boolean _isGameSaveInitialized = false;//synchronized
	synchronized public void setGameSaveInitialized_S(boolean b){_isGameSaveInitialized = b;}
	synchronized public boolean getGameSaveInitialized_S(){return _isGameSaveInitialized;}

	private GameSave _gameSave = new GameSave();
	synchronized public GameSave gameSave_S(){return _gameSave;}
	synchronized public void setGameSave_S(GameSave g){_gameSave = g;}

	boolean gameSaveCompleted_nonThreaded = false;



	private long lastSentLoadEventRequestTime = 0;
	private boolean isLoadEventInitialized_nonThreaded = false;
	private int _projectLoadEventID = -1;
	//=========================================================================================================================
	synchronized public void setProjectLoadEventID_S(int id)
	{//=========================================================================================================================
		_projectLoadEventID = id;
	}
	//=========================================================================================================================
	synchronized public int getProjectLoadEventID_S()
	{//=========================================================================================================================
		return _projectLoadEventID;
	}


	public boolean finishedLoadEvent(){return finishedLoadEvent;}
	Event loadEvent = null;
	boolean finishedLoadEvent = false;
	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

		long time = System.currentTimeMillis();

		if(ClientMain.introMode==true)
		{
			setGameSave_S(new GameSave());
			setInitialGameSaveReceived_S(true);
			setGameSaveInitialized_S(true);

			guiManager.update();
		}
		else
		{
			if(initialGameSaveReceived_nonThreaded==false)
			{
				//hammering the synchronized methods was causing lock issues, put a small delay on network checks
				if(time-checkInitialGameSaveReceivedDelayTime>200)
				{
					checkInitialGameSaveReceivedDelayTime=time;

					if(getInitialGameSaveReceived_S()==false)
					{
						//don't send initial request until we have authorized.
						//otherwise we will create an authorization thread that is sitting there waiting for us to have a userID anyway.
						if(Network().getAuthorizedOnServer()==true)
						Network().sendInitialGameSaveRequest();
					}
					else
					{
						initialGameSaveReceived_nonThreaded = true;//non threaded, a bit faster.
					}

				}

				return;
			}


			if(isGameSaveInitialized_nonThreaded==false)
			{
				if(getGameSaveInitialized_S()==true)
				{
					isGameSaveInitialized_nonThreaded=true;

					setPlayerAppearanceFromGameSave_S();
				}

				return;
			}


			//hammering the synchronized methods was causing lock issues, put a small delay on network checks
			if(time-networkDelayTime>200)
			{
				networkDelayTime=time;
				Network().sendQueuedGameSaveUpdates();
			}


			guiManager.update();


			if(gameSaveCompleted_nonThreaded==false)
			{
				if(gameSave_S().wasPlayerCreatedYet()==false)
				{
					if(guiManager.playerEditMenu.isActivated()==false)guiManager.playerEditMenu.setActivated(true);
				}
				else
				{
					gameSaveCompleted_nonThreaded = true;
				}

				return;
			}



			if(isLoadEventInitialized_nonThreaded==false)
			{
				if(time - lastSentLoadEventRequestTime>200)
				{
					lastSentLoadEventRequestTime = time;

					if(getProjectLoadEventID_S()==-1)
					{
						Network().sendLoadEventRequest();

					}
					else
					{
						isLoadEventInitialized_nonThreaded = true;

						loadEvent = EventManager().getEventByIDCreateIfNotExist(getProjectLoadEventID_S());
						EventManager().addToEventQueueIfNotThere(loadEvent);//events update their own network data inside their run function
					}
				}

				return;
			}


			if(finishedLoadEvent==false)
			{
				//wait for load event to finish
				if(EventManager().isEventInQueue(loadEvent)==false)
				{
					finishedLoadEvent=true;

					GameSave g = gameSave_S();


					boolean updateGameSave = false;

					//if(g.startingRoom.equals("BLANK"))g.startingRoom = "GENERIC1UpstairsBedroom1";
					if(g.lastKnownRoom.equals("BLANK")){g.lastKnownRoom = "GENERIC1UpstairsBedroom1";g.lastKnownX = 17*8*2; g.lastKnownY = 12*8*2; updateGameSave = true;}

					MapManager().changeMap(g.lastKnownRoom, g.lastKnownX, g.lastKnownY, updateGameSave);// *** don't changemap in network thread! it blocks
				}
			}
		}



		handleGameEngineOptionKeys();


		super.update();





		clock.update();

		friendManager.update();


		//EasingTest.update();

		statusBar.update();

		wallet.update();

		nD.update();
		stadiumScreen.update();

	}



	//=========================================================================================================================
	public void cleanup()
	{//=========================================================================================================================

		super.cleanup();

		guiManager.cleanup();

		friendManager.cleanup();
	}




	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================


		if(nD.isScrolledUp()==false)super.render();


		//LWJGLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		nD.render();
		//stadiumScreen.render();

		//LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		statusBar.render();

		guiManager.render();

		//LWJGLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	}


	//=========================================================================================================================
	public boolean areAnyMenusOpen()
	{//=========================================================================================================================


		if
		(
			ND().isActivated() ||
			StuffMenu().isActivated() ||
			PlayerEditMenu().isActivated() ||
			GameStore().isActivated()
		)
		return true;

		return false;

	}



	//=========================================================================================================================
	public void handleGameEngineOptionKeys()
	{//=========================================================================================================================


		if(ControlsManager().BUTTON_F1_PRESSED==true)
		{
			guiManager.keyboardScreen.toggleActivated();
		}


		if(ControlsManager().BUTTON_RETURN_PRESSED==true && nD.isActivated()==false)
		{
			nD.toggleActivated();
		}


		if(ControlsManager().BUTTON_TAB_PRESSED==true)
		{
			guiManager.stuffMenu.toggleActivated();
		}


		if(areAnyMenusOpen())
		{
			return;
		}



		//-----------------------------
		// zoom controls
		//------------------------------

		if(Cameraman().zoomManuallyEnabled)
		{
			if(ControlsManager().BUTTON_MINUS_PRESSED==true)
			{
				cameraman.zoomOut();
			}

			if(ControlsManager().BUTTON_PLUS_PRESSED==true)
			{
				cameraman.zoomIn();
			}

			if(ControlsManager().BUTTON_BACKSPACE_PRESSED==true)
			{
				cameraman.resetZoom();
			}

			if(ControlsManager().BUTTON_RCTRL_HELD==true)
			{
				cameraman.quickZoomOut();
			}
			else
			if(ControlsManager().BUTTON_RSHIFT_HELD==true)
			{
				cameraman.quickZoomIn();
			}
			else
			{
				cameraman.resetQuickZoom();
			}
		}




		if(BobNet.debugMode==true)
		{

			if(ControlsManager().BUTTON_H_PRESSED==true)
			{
				hitLayerEnabled=!hitLayerEnabled;
				Console.debug("Hit Layer Toggled: "+hitLayerEnabled,1000);
			}

			if(ControlsManager().BUTTON_TILDE_PRESSED==true)
			{
				underLayerEnabled=!underLayerEnabled;
				Console.debug("Under Layer Toggled: "+underLayerEnabled,1000);
			}

			if(ControlsManager().BUTTON_1_PRESSED==true)
			{
				entityLayerEnabled=!entityLayerEnabled;
				Console.debug("Entity Layer Toggled: "+entityLayerEnabled,1000);
			}

			if(ControlsManager().BUTTON_2_PRESSED==true)
			{
				overLayerEnabled=!overLayerEnabled;
				Console.debug("Over Layer Toggled: "+overLayerEnabled,1000);
			}

			if(ControlsManager().BUTTON_3_PRESSED==true)
			{
				lightsLayerEnabled=!lightsLayerEnabled;
				Console.debug("Lights Layer Toggled: "+lightsLayerEnabled,1000);
			}

			if(ControlsManager().BUTTON_4_PRESSED==true)
			{
				LWJGLUtils.useShader=!LWJGLUtils.useShader;
				Console.debug("Shader Toggled: "+LWJGLUtils.useShader,1000);
			}

			if(ControlsManager().BUTTON_5_PRESSED==true)
			{
				LWJGLUtils.useFBO=!LWJGLUtils.useFBO;
				Console.debug("FBO Toggled: "+LWJGLUtils.useFBO,1000);
			}

			if(ControlsManager().BUTTON_6_PRESSED==true)
			{
				debugLayerEnabled=!debugLayerEnabled;
				Console.debug("Debug Layer Toggled: "+debugLayerEnabled,1000);
			}

			if(ControlsManager().BUTTON_NUM2_PRESSED==true)
			{
				MapManager().contrast-=0.1f;
				Console.debug("Contrast: "+MapManager().contrast,1000);
			}

			if(ControlsManager().BUTTON_NUM3_PRESSED==true)
			{
				MapManager().contrast+=0.1f;
				Console.debug("Contrast: "+MapManager().contrast,1000);
			}

			if(ControlsManager().BUTTON_NUM5_PRESSED==true)
			{
				MapManager().brightness-=0.1f;
				Console.debug("Brightness: "+MapManager().brightness,1000);
			}

			if(ControlsManager().BUTTON_NUM6_PRESSED==true)
			{
				MapManager().brightness+=0.1f;
				Console.debug("Brightness: "+MapManager().brightness,1000);
			}

			if(ControlsManager().BUTTON_NUM8_PRESSED==true)
			{
				MapManager().saturation-=0.1f;
				Console.debug("Saturation: "+MapManager().saturation,1000);
			}

			if(ControlsManager().BUTTON_NUM9_PRESSED==true)
			{
				MapManager().saturation+=0.1f;
				Console.debug("Saturation: "+MapManager().saturation,1000);
			}

			if(ControlsManager().BUTTON_NUM1_PRESSED==true)
			{
				MapManager().gamma-=0.1f;
				Console.debug("Gamma: "+MapManager().gamma,1000);
			}

			if(ControlsManager().BUTTON_NUM4_PRESSED==true)
			{
				MapManager().gamma+=0.1f;
				Console.debug("Gamma: "+MapManager().gamma,1000);
			}

			if(ControlsManager().BUTTON_NUM0_PRESSED==true)
			{
				MapManager().saturation=1.0f;
				MapManager().brightness=1.0f;
				MapManager().contrast=1.0f;
				MapManager().gamma=1.0f;
				Console.debug("Saturation: "+MapManager().saturation+" | Brightness: "+MapManager().brightness+" | Contrast: "+MapManager().contrast+" | Gamma: "+MapManager().gamma,1000);
			}
		}
	}




	//=========================================================================================================================
	public void updateDebugText()
	{//=========================================================================================================================
		super.updateDebugText();

		playerMapText.text =  "Player map xy: " + player.x() + "," + player.y() + " | Tiles: "+ player.x()/8 + "," + player.y()/8 ;
		playerScreenText.text =  "Player screen xy: " + player.screenLeft() + "," + player.screenTop() + " Player layer: " + player.renderOrder();
	}



	//===============================================================================================
	public void loadPreCachedObjectData()
	{//===============================================================================================


		boolean debug = false;



		List<String> b64List=null;


		try{b64List = IOUtils.readLines(Utils.getResourceAsStream("res/PreloadSkillData"), StandardCharsets.UTF_8);}catch(IOException e){e.printStackTrace();}
		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);
				if(s.length()>0)
				{
					SkillData data = new SkillData();
					data.initFromString(s);
					Skill skill = new Skill(this,data);
					//EventManager().skillList.add(skill);
					if(debug)log.debug("Preload Skill id:"+data.id()+" name:"+data.name());
				}
			}
		}

		try{b64List = IOUtils.readLines(Utils.getResourceAsStream("res/PreloadDialogueData"), StandardCharsets.UTF_8);}catch(IOException e){e.printStackTrace();}
		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);
				if(s.length()>0)
				{
					DialogueData data = new DialogueData();
					data.initFromString(s);
					Dialogue m = new Dialogue(this,data);
					//EventManager().dialogueList.add(m);
					if(debug)log.debug("Preload Dialogue id:"+data.id()+" name:"+data.name());
				}
			}
		}

		try{b64List = IOUtils.readLines(Utils.getResourceAsStream("res/PreloadFlagData"), StandardCharsets.UTF_8);}catch(IOException e){e.printStackTrace();}
		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);
				if(s.length()>0)
				{
					FlagData data = new FlagData();
					data.initFromString(s);
					Flag m = new Flag(this,data);
					//EventManager().flagList.add(m);
					if(debug)log.debug("Preload Flag id:"+data.id()+" name:"+data.name());
				}
			}
		}

		try{b64List = IOUtils.readLines(Utils.getResourceAsStream("res/PreloadGameStringData"), StandardCharsets.UTF_8);}catch(IOException e){e.printStackTrace();}
		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);
				if(s.length()>0)
				{
					GameStringData data = new GameStringData();
					data.initFromString(s);
					GameString m = new GameString(this,data);
					//EventManager().gameStringList.add(m);
					if(debug)log.debug("Preload GameString id:"+data.id()+" name:"+data.name());
				}
			}
		}

		try{b64List = IOUtils.readLines(Utils.getResourceAsStream("res/PreloadEventData"), StandardCharsets.UTF_8);}catch(IOException e){e.printStackTrace();}
		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);
				if(s.length()>0)
				{
					EventData data = new EventData();
					data.initFromString(s);
					Event m = new Event(this,data);
					//EventManager().eventList.add(m);
					if(debug)log.debug("Preload Event id:"+data.id()+" name:"+data.name());
				}
			}
		}

		try{b64List = IOUtils.readLines(Utils.getResourceAsStream("res/PreloadSpriteData"), StandardCharsets.UTF_8);}catch(IOException e){e.printStackTrace();}
		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);

				if(s.length()>0)
				{
					SpriteData data = new SpriteData();
					data.initFromString(s);

					if(SpriteManager().spriteByIDHashMap.get(data.id())==null)
					{
						Sprite sprite = new Sprite(this);
						sprite.initalizeWithSpriteData(data);

						SpriteManager().spriteByNameHashMap.put(data.name(),sprite);
						SpriteManager().spriteByIDHashMap.put(data.id(),sprite);
					}
					else
					{
						log.error("Sprite already exists:"+data.name());
					}

					//System.out.println(spriteData.name);

					if(debug)log.debug("Preload Sprite id:"+data.id()+" name:"+data.name());
				}
			}
		}


		try{b64List = IOUtils.readLines(Utils.getResourceAsStream("res/PreloadSoundData"), StandardCharsets.UTF_8);}catch(IOException e){e.printStackTrace();}
		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);

				if(s.length()>0)
				{
					SoundData data = new SoundData();
					data.initFromString(s);

					Sound m = new Sound(this,data);

					//just adding the md5 names for the sounds in sounds.zip to the soundList so they can be immediately accessed without server calls
					//AudioManager().soundList.add(m);

					//music will first ask the server

					//System.out.println(data.name);

					if(debug)log.debug("Preload Sound id:"+data.id()+" name:"+data.name());
				}
			}
		}


		try{b64List = IOUtils.readLines(Utils.getResourceAsStream("res/PreloadMusicData"), StandardCharsets.UTF_8);}catch(IOException e){e.printStackTrace();}
		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);

				if(s.length()>0)
				{
					MusicData data = new MusicData();
					data.initFromString(s);

					Music m = new Music(this,data);

					//just adding the md5 names for PRELOADED music in music.zip to the musicList so they can be immediately accessed without server calls
					//AudioManager().musicList.add(m);

					if(debug)log.debug("Preload Music id:"+data.id()+" name:"+data.name());
				}
			}
		}

		try{b64List = IOUtils.readLines(Utils.getResourceAsStream("res/PreloadMapData"), StandardCharsets.UTF_8);}catch(IOException e){e.printStackTrace();}
		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);

				if(s.length()>0)
				{
					MapData data = new MapData();
					data.initFromString(s);

					if(MapManager().mapByIDHashMap.get(data.id())==null)
					{
						Map m = new Map(this,data);

						MapManager().mapList.add(m);
						MapManager().mapByNameHashMap.put(data.name(),m);
						MapManager().mapByIDHashMap.put(data.id(),m);
					}
					else
					{
						log.error("Map already exists:"+data.name());
					}

					if(debug)log.debug("Preload Map id:"+data.id()+" name:"+data.name());
				}
			}
		}



	}





	//=========================================================================================================================
	synchronized public void initializeGameFromSave_S()
	{//=========================================================================================================================


		//set flags, set dialogueDone values, stats values
		{
			String itemsHeld = gameSave_S().itemsHeld;//items are just comma separated values
			while(itemsHeld.contains(","))
			{

				String dataString = itemsHeld.substring(0,itemsHeld.indexOf(","));

				int itemID = -1;
				try{itemID = Integer.parseInt(dataString.substring(0,dataString.indexOf(":")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
				dataString = dataString.substring(dataString.indexOf(":")+1);
				boolean value = Boolean.parseBoolean(dataString.substring(0,dataString.indexOf(":")));
				dataString = dataString.substring(dataString.indexOf(":")+1);
				long timeSet = -1;
				try{timeSet = Long.parseLong(dataString);}catch(NumberFormatException ex){ex.printStackTrace();return;}


				itemsHeld = itemsHeld.substring(itemsHeld.indexOf(",")+1);


				Item f = EventManager().getItemByID(itemID);
				f.initHaveItemValue_S(value,timeSet);
			}
		}



		{
			String flagsSet = gameSave_S().flagsSet;//flags are just comma separated values
			while(flagsSet.contains(","))
			{

				//flag looks like id:true:timeSet,id:false:timeSet,
				String dataString = flagsSet.substring(0,flagsSet.indexOf(","));

				int flagID = -1;
				try{flagID = Integer.parseInt(dataString.substring(0,dataString.indexOf(":")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
				dataString = dataString.substring(dataString.indexOf(":")+1);
				boolean value = Boolean.parseBoolean(dataString.substring(0,dataString.indexOf(":")));
				dataString = dataString.substring(dataString.indexOf(":")+1);
				long timeSet = -1;
				try{timeSet = Long.parseLong(dataString);}catch(NumberFormatException ex){ex.printStackTrace();return;}


				flagsSet = flagsSet.substring(flagsSet.indexOf(",")+1);

				Flag f = EventManager().getFlagByIDCreateIfNotExist(flagID);
				f.initValueFromGameSave_S(value,timeSet);
			}
		}



		{
			String dialoguesDone = gameSave_S().dialoguesDone;//dialogues are just comma separated values
			while(dialoguesDone.contains(","))
			{
				String dataString = dialoguesDone.substring(0,dialoguesDone.indexOf(","));

				int dialogueID = -1;
				try{dialogueID = Integer.parseInt(dataString.substring(0,dataString.indexOf(":")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
				dataString = dataString.substring(dataString.indexOf(":")+1);
				boolean value = Boolean.parseBoolean(dataString.substring(0,dataString.indexOf(":")));
				dataString = dataString.substring(dataString.indexOf(":")+1);
				long timeSet = -1;
				try{timeSet = Long.parseLong(dataString);}catch(NumberFormatException ex){ex.printStackTrace();return;}

				dialoguesDone = dialoguesDone.substring(dialoguesDone.indexOf(",")+1);

				Dialogue d = EventManager().getDialogueByIDCreateIfNotExist(dialogueID);
				d.initDialogueDoneValueFromGameSave_S(value,timeSet);
			}
		}



		{
			String skillValues = gameSave_S().skillValues;//skills look like skillID:float:time, so 199:-1.4:time,
			while(skillValues.contains(","))
			{
				String dataString = skillValues.substring(0,skillValues.indexOf(","));

				int skillID = -1;
				try{skillID = Integer.parseInt(dataString.substring(0,dataString.indexOf(":")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
				dataString = dataString.substring(dataString.indexOf(":")+1);
				float value = -1;
				try{value = Float.parseFloat(dataString.substring(0,dataString.indexOf(":")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
				dataString = dataString.substring(dataString.indexOf(":")+1);
				long timeSet = -1;
				try{timeSet = Long.parseLong(dataString);}catch(NumberFormatException ex){ex.printStackTrace();return;}

				skillValues = skillValues.substring(skillValues.indexOf(",")+1);

				Skill skill = EventManager().getSkillByIDCreateIfNotExist(skillID);
				skill.initValueFromGameSave_S(value,timeSet);
			}
		}

		//mapManager.changeMap("ALPHABobsApartment",18,15);//g.lastKnownRoom, g.lastKnownX/8, g.lastKnownY/8);
		//mapManager.changeMap(g.lastKnownRoom, g.lastKnownX/8, g.lastKnownY/8);


		setGameSaveInitialized_S(true);
	}






	//=========================================================================================================================
	synchronized public void setPlayerAppearanceFromGameSave_S()
	{//=========================================================================================================================

		GameSave g = gameSave_S();

		String s = g.characterAppearance;

		player.setAppearanceFromCharacterAppearanceString(s);

		player.setCharacterNameAndCaption
		(
				getNameColor(g.accountRank),
				g.characterName,
				getAccountRankColor(g.accountRank),
				getAccountRankString(g.accountRank)
		);
	}


	//=========================================================================================================================
	public BobColor getNameColor(int accountType)
	{//=========================================================================================================================
		return getAccountRankColor(accountType);
	}

	//=========================================================================================================================
	public String getAccountRankString(int accountType)
	{//=========================================================================================================================
		String accountRankString = "Free";
		if(accountType==0)accountRankString = "Free";
		if(accountType==1)accountRankString = "Premium";
		if(accountType==2)accountRankString = "nD Dev";
		if(accountType==3)accountRankString = "Mod";
		if(accountType==4)accountRankString = "Admin";
		if(accountType==5)accountRankString = "Champion";
		if(accountType==6)accountRankString = "Legend";
		if(accountType==7)accountRankString = "Saint";
		if(accountType==8)accountRankString = "Prophet";
		if(accountType==9)accountRankString = "Genius";
		if(accountType==10)accountRankString = "Uberman";
		if(accountType==11)accountRankString = "Angel";
		if(accountType==12)accountRankString = "Christ";
		if(accountType==13)accountRankString = "God";
		if(accountType==14)accountRankString = "\"bob\"";

		return accountRankString;

	}

	//=========================================================================================================================
	public BobColor getAccountRankColor(int accountType)
	{//=========================================================================================================================
		BobColor accountRankColor = BobColor.WHITE;
		if(accountType==0)accountRankColor = BobColor.WHITE;//"Free";
		if(accountType==1)accountRankColor = BobColor.PURPLE;//"Premium";
		if(accountType==2)accountRankColor = BobColor.BLUE;//"nD Dev";
		if(accountType==3)accountRankColor = BobColor.RED;//"Mod";
		if(accountType==4)accountRankColor = BobColor.RED;//"Admin";
		if(accountType==5)accountRankColor = BobColor.RED;//"Champion";
		if(accountType==6)accountRankColor = BobColor.RED;//"Legend";
		if(accountType==7)accountRankColor = BobColor.RED;//"Saint";
		if(accountType==8)accountRankColor = BobColor.RED;//"Prophet";
		if(accountType==9)accountRankColor = BobColor.RED;//"Genius";
		if(accountType==10)accountRankColor = BobColor.RED;//"Uberman";
		if(accountType==11)accountRankColor = BobColor.RED;//"Angel";
		if(accountType==12)accountRankColor = BobColor.RED;//"Christ";
		if(accountType==13)accountRankColor = BobColor.RED;//"God";
		if(accountType==14)accountRankColor = BobColor.GREEN;//"\"bob\"";

		return accountRankColor;

	}


	//=========================================================================================================================
	public static GameClientTCP Network()
	{//=========================================================================================================================
		if(ClientMain.clientMain==null)return null;
		return ClientMain.clientMain.gameClientTCP;
	}


	//=========================================================================================================================
	public void setPlayerToTempPlayerWithSprite(Sprite s)
	{//=========================================================================================================================


		Player p = new Player(ClientGameEngine(),s.name());

		p.update();

		p.setX(player.x());
		p.setY(player.y());
		p.setSpawnXPixelsHQ(player.x());
		p.setSpawnYPixelsHQ(player.y());


		if(CurrentMap()!=null)
		{
			if(CurrentMap().activeEntityList.contains(player))
			{
				CurrentMap().activeEntityList.remove(player);
				CurrentMap().activeEntityList.add(p);
			}
		}

		if(Cameraman()!=null&&Cameraman().targetEntity == player)Cameraman().setTarget(p);

		player = p;
	}

	//=========================================================================================================================
	public void setPlayerToNormalPlayer()
	{//=========================================================================================================================


		if(CurrentMap()!=null)
		{
			if(CurrentMap().activeEntityList.contains(player))
			{
				CurrentMap().activeEntityList.remove(player);
				CurrentMap().activeEntityList.add(normalPlayer);
			}
		}

		if(Cameraman()!=null&&Cameraman().targetEntity == player)Cameraman().setTarget(normalPlayer);

		player = normalPlayer;

	}






}
