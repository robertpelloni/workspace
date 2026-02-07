package com.bobsgame.client.engine.game.nd.bobsgame;



import java.util.ArrayList;
import java.util.Vector;
import java.util.concurrent.ConcurrentHashMap;


import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL13.*;
//import static org.lwjgl.opengl.GL30.*;
//import static org.lwjgl.opengl.GL31.*;
//import static org.lwjgl.opengl.GL32.*;
//import static org.lwjgl.opengl.GL33.*;
//import static org.lwjgl.opengl.GL40.*;

import io.netty.channel.ChannelFuture;
//import io.netty.channel.ChannelHandlerContext;
import org.slf4j.LoggerFactory;

import com.bobsgame.client.Texture;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.LWJGLUtils;
import com.bobsgame.client.engine.entity.Sprite;
import com.bobsgame.client.engine.entity.SpriteManager;
import com.bobsgame.client.engine.game.nd.ND;
import com.bobsgame.client.engine.game.nd.NDGameEngine;
import com.bobsgame.puzzle.GameLogic;
import com.bobsgame.puzzle.GameLogic.NetworkPacket;
import com.bobsgame.puzzle.PuzzleGameType;
import com.bobsgame.puzzle.FrameState;
//import com.bobsgame.client.engine.game.nd.bobsgame.game.GameLogic.NetworkPacket;
import com.bobsgame.client.engine.text.BobFont;
import com.bobsgame.client.engine.text.Caption;
import com.bobsgame.net.BobNet;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.Utils;
import com.bobsgame.shared.MapData.RenderOrder;
import com.google.gson.Gson;


//=========================================================================================================================
public class BobsGame extends NDGameEngine
{//=========================================================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(BobsGame.class);





	//public ConcurrentHashMap<Long,Game> games = new ConcurrentHashMap<Long,Game>();

	public GameLogic ME = null;
	GameLogic THEM = null;


	public long randomSeed = -1;

	PuzzleGameType originalSettings = null;


	long timeRenderBegan = System.currentTimeMillis();


	boolean showingStartMenu = false;

	long lastTimeTriedToCloseGame = 0;


	boolean debug = BobNet.debugMode;

	public static boolean doneInitializingSprites = false;

	//=========================================================================================================================
	public BobsGame(ND nD)
	{//=========================================================================================================================


		super(nD);




		newGame();

//		games.put(randomSeed,ME);

//		player2 = new Game(this);
//		player2.controlledByNetwork = true;
//		games.add(player2);


		name = "bob's game";



	}


	//=========================================================================================================================
	public void setupLoadScreens()
	{//=========================================================================================================================


		showingTitleScreen = true;

		numTileScreenTextureFrames = 91;//139;//with quotes

//		titleScreenTextures = new Texture[numTileScreenTextureFrames];
//
//		for(int i=0;i<numTileScreenTextureFrames;i++)
//		{
//			String num = ""+i;
//			int len = num.length();
//			for(int n=0;n<4-len;n++)num = "0"+num;//pad to 4 zeros
//
//			titleScreenTextures[i] = GLUtils.loadTexture("res/guiBackground/bobsGameLogoAnim/"+num+".png");
//		}

		cursorTexture = GLUtils.loadTexture("res/textbox/textCursor.png");

	}


	//=========================================================================================================================
	public void newGame()
	{//=========================================================================================================================

		if(ME!=null)
		{
			resetGame();
		}
		else
		{

			ME = (new GameLogic(this, -1));

			randomSeed = ME.randomSeed;

			originalSettings = ME.currentGameType;
		}

	}


	//=========================================================================================================================
	public void resetGame()
	{//=========================================================================================================================

		if(ME!=null)ME.deleteAllCaptions();
		if(THEM!=null)THEM.deleteAllCaptions();



		//TODO: unload sprites?
		//TODO: stop music



		BobsGame bobsgame = new BobsGame(nD);
		//GameDataLoader gameDataLoader = new GameDataLoader(bobsgame);
		bobsgame.init();


		//for simulator connection
		if(friend==null&&connection!=null)bobsgame.setConnection(connection);


		nD.setGame(bobsgame);
		this.nD = null;

		if(isNetworkGame())
		{
			if(connection!=null)setConnection(null);
			if(friend!=null)
			{
				friend.setGameToForwardPacketsTo(null);
				friend = null;
			}
		}

		unloadTextures();

	}





	//=========================================================================================================================
	public void tryToCloseGame()
	{//=========================================================================================================================


		if(isNetworkGame())
		{

			long currentTime = System.currentTimeMillis();
			if(currentTime - lastTimeTriedToCloseGame < 5000)
			{

				//send "quit" message
				//TODO: add "lose" to records

				sendForfeit();




				nD.setActivated(false);

			}
			else
			{

				//warn that network game will be forfeit

				//if try to close again within 5 seconds, close.

				lastTimeTriedToCloseGame = currentTime;

				CaptionManager().newManagedCaption(Caption.CENTERED_SCREEN,0,5000,"Network game is in progress! Match will be forfeit. Close the nD again within 5 seconds to confirm.",BobFont.font_small_16_outlined_smooth,BobColor.red,BobColor.black,2.0f);

			}



		}
		else
		{
			nD.setActivated(false);
		}


	}



	//=========================================================================================================================
	public boolean isNetworkGame()
	{//=========================================================================================================================
		if(THEM==null)return false;
		return true;
	}


	private static String netCommand_SEED = "SEED:";
	private static String netCommand_SEEDOK = "SEEDOK:";
	private static String netCommand_SETTINGS = "SETTINGS:";
	private static String netCommand_SETTINGSOK = "SETTINGSOK:";
	private static String netCommand_START = "START:";
	private static String netCommand_STARTOK = "STARTOK:";
	private static String netCommand_FRAME = "FRAME:";
	private static String netCommand_FRAMEOK = "FRAMEOK:";
	private static String netCommand_FORFEIT = "FORFEIT:";


	//=========================================================================================================================
	public void handleMessage(String s)
	{//=========================================================================================================================

		//String s = (String) e.getMessage();

		//log.debug(s);


		if(s.indexOf(":")==-1)return;
		String command = s.substring(0,s.indexOf(":")+1);
		s = s.substring(s.indexOf(":")+1);

		if(command.equals(netCommand_SEED)){incoming_Seed(s);return;}
		if(command.equals(netCommand_SEEDOK)){incoming_ReplyToMySeed(s);return;}

		if(command.equals(netCommand_SETTINGS)){incoming_Settings(s);return;}
		if(command.equals(netCommand_SETTINGSOK)){incoming_ReplyToMySettings(s);return;}

		if(command.equals(netCommand_START)){incoming_Start(s);return;}
		if(command.equals(netCommand_STARTOK)){incoming_ReplyToMyStart(s);return;}

		if(command.equals(netCommand_FRAME)){incoming_FramePacket(s);return;}
		if(command.equals(netCommand_FRAMEOK)){incoming_gotFrameOK(s);return;}

		if(command.equals(netCommand_FORFEIT)){incoming_Forfeit(s);return;}

		setLastTimeGotIncomingTraffic_S();

		super.handleMessage(s);

	}



	//=========================================================================================================================
	protected String getFrameStatesAsBase64GZippedGSON(NetworkPacket packet)
	{//=========================================================================================================================

		Gson gson = new Gson();

		String json = gson.toJson(packet);
		String zip = Utils.zipString(json);
		String base64 = Utils.encodeStringToBase64(zip);

		return base64;
	}


	//=========================================================================================================================
	protected NetworkPacket getFrameStatesFromBase64GZippedGSON(String b64GZipJSON)
	{//=========================================================================================================================

		Gson gson = new Gson();

		String zip = Utils.decodeBase64String(b64GZipJSON);
		String json = Utils.unzipString(zip);

		if(json==null||json.length()==0){return null;}

		return gson.fromJson(json,NetworkPacket.class);

	}


	//=========================================================================================================================
	private void incoming_FramePacket(String s)
	{//=========================================================================================================================

		//randomSeed:packetID,MD5:base64
		if(s.indexOf(":")==-1)return;
		long randomSeed = -1;
		try{randomSeed = Long.parseLong(s.substring(0,s.indexOf(":")));}catch(NumberFormatException e){log.error("Failed to parse randomSeed in incoming frame packet");return;}
		s = s.substring(s.indexOf(":")+1);


		//get ID, md5
		if(s.indexOf(":")==-1)return;
		String idMD5 = s.substring(0,s.indexOf(":"));
		s = s.substring(s.indexOf(":")+1);

		long id = -1;
		try{id = Long.parseLong(idMD5.substring(0,idMD5.indexOf(",")));}catch(NumberFormatException e){log.error("Failed to parse framePacket ID in incoming frame packet");return;}
		String md5 = idMD5.substring(idMD5.indexOf(",")+1);

		String compMD5 = Utils.getStringMD5(s);
		if(md5.equals(compMD5)==false){log.error("Frame Packet MD5 did not match!");return;}


		//Game them = games.get(randomSeed);
		//if(them==null){log.error("Could not find game with seed:" + randomSeed);return;}


		//store id, md5 in "got packets" log so we don't add the same frame packet twice, in case our "OK" doesn't make it back and they keep sending it
		if(gotPacketsLog.contains(idMD5)==true)
		{
			//if already in log, just send back id, md5 as confirmation
			connection.write(netCommand_FRAMEOK+randomSeed+":"+idMD5+BobNet.endline);
		}
		else
		{

			//if not in log, add to log, add frames to queue, send back id, md5 as confirmation
			NetworkPacket packet = getFrameStatesFromBase64GZippedGSON(s);
			if(packet!=null)
			{
				Vector<FrameState> frames = packet.frameStates;

				if(frames!=null)
				{
					//log.info("Added framePacket ID: "+id);
					if(
					incomingFramePackets.put(id,frames)
					!=null)log.error("Incoming framePacket was already inserted into incomingFramePackets");

					gotPacketsLog.add(idMD5);

					connection.write(netCommand_FRAMEOK+randomSeed+":"+idMD5+":"+"-1"+BobNet.endline);
				}
			}

		}
	}


	//=========================================================================================================================
	private void incoming_gotFrameOK(String s)
	{//=========================================================================================================================

		//randomSeed:id,MD5:-1
		if(s.indexOf(":")==-1)return;
		long randomSeed = -1;
		try{randomSeed = Long.parseLong(s.substring(0,s.indexOf(":")));}catch(NumberFormatException e){log.error("Failed to parse randomSeed in incoming frame packet");return;}
		s = s.substring(s.indexOf(":")+1);

		if(s.indexOf(",")==-1)return;

		String idMD5 = s.substring(0,s.indexOf(":"));
		s = s.substring(s.indexOf(":")+1);

		//Game them = games.get(randomSeed);
		//if(them==null){log.error("Could not find game with seed:" + randomSeed);return;}

		//remove id,MD5 from vector queue
		//remove id,MD5 from hashmap queue

		//if got id, md5, remove packet 0
		//if not, send packet 0 again

		outboundPacketQueueHashMap.remove(idMD5);
		outboundPacketQueueVector.remove(idMD5);

	}



	ConcurrentHashMap<Long,Long> gotSeedTime = new ConcurrentHashMap<Long,Long>();

	//=========================================================================================================================
	private void incoming_Seed(String s)
	{//=========================================================================================================================

		//randomSeed:-1
		if(s.indexOf(":")==-1)return;
		long theirRandomSeed = -1;
		try{theirRandomSeed = Long.parseLong(s.substring(0,s.indexOf(":")));}catch(NumberFormatException e){log.error("Failed to parse randomSeed in incoming frame packet");return;}
		s = s.substring(s.indexOf(":")+1);


		if(debug)log.error("incoming_Seed: Their Seed: "+theirRandomSeed);


		long currentTime = System.currentTimeMillis();
		Long time = gotSeedTime.get(theirRandomSeed);
		long lastTime=0;
		if(time!=null)lastTime = time;
		if(time!=null&&lastTime+5000<currentTime)return;
		if(time!=null)gotSeedTime.remove(theirRandomSeed);
		gotSeedTime.put(theirRandomSeed,currentTime);


		if(debug)log.debug("gotSeedTime:" +theirRandomSeed+","+currentTime);


		//Game g = games.get(theirRandomSeed);
		if(theirSeed()==-1)
		{
			if(debug)log.debug("Added game: "+theirRandomSeed);

			theirSeed(theirRandomSeed);

		}
		else
		{
			if(debug)log.debug("Got seed twice");
		}

		connection.write(netCommand_SEEDOK+theirRandomSeed+":"+"-1"+BobNet.endline);
		//log.debug("write: netCommand_SEEDOK: Their Seed: " +theirRandomSeed);
	}

	//=========================================================================================================================
	private void incoming_Settings(String s)
	{//=========================================================================================================================



		//randomSeed:MD5:base64
		if(s.indexOf(":")==-1)return;
		long theirRandomSeed = -1;
		try{theirRandomSeed = Long.parseLong(s.substring(0,s.indexOf(":")));}catch(NumberFormatException e){log.error("Failed to parse randomSeed in incoming frame packet");return;}
		s = s.substring(s.indexOf(":")+1);

		if(s.indexOf(":")==-1)return;
		String md5 = s.substring(0,s.indexOf(":"));
		s = s.substring(s.indexOf(":")+1);

		String compMD5 = Utils.getStringMD5(s);
		if(md5.equals(compMD5)==false){log.error("Settings MD5 did not match!");return;}

		if(debug)log.error("incoming_Settings: Their Seed: "+theirRandomSeed);

		//Game g = games.get(theirRandomSeed);
		//if(THEM()!=null)
		{
			Gson gson = new Gson();
			String zip = Utils.decodeBase64String(s);
			String json = Utils.unzipString(zip);

			if(json==null||json.length()==0){log.error("Their settings were invalid!");return;}
			PuzzleGameType settings = gson.fromJson(json,PuzzleGameType.class);
			if(settings==null){log.error("Their settings were null!");return;}

			getTheirSettings(settings);

			//gotTheirSettings(true);

			if(debug)log.debug("Got their Settings");

		}
//		else
//		{
//			log.debug("Got settings but no game found");
//		}

		connection.write(netCommand_SETTINGSOK+theirRandomSeed+":"+"-1"+BobNet.endline);
		//log.debug("write: netCommand_SETTINGSOK " +theirRandomSeed);
	}



	//=========================================================================================================================
	private void incoming_ReplyToMySeed(String s)
	{//=========================================================================================================================

		//randomSeed:
		if(s.indexOf(":")==-1)return;
		long myRandomSeed = -1;
		try{myRandomSeed = Long.parseLong(s.substring(0,s.indexOf(":")));}catch(NumberFormatException e){log.error("Failed to parse randomSeed in incoming seedok");return;}
		//s = s.substring(s.indexOf(":")+1);


		if(debug)log.error("incoming_ReplyToMySeed: My Seed: " +myRandomSeed);
		//Game them = games.get(randomSeed);
		//if(them==null){log.debug("Could not find game with seed:" + randomSeed);}

		gotReplyToMySeed(true);
		//log.debug("gotReplyToMySeed: My Seed: " +myRandomSeed);
	}

	//=========================================================================================================================
	private void incoming_ReplyToMySettings(String s)
	{//=========================================================================================================================

		//randomSeed:
		if(s.indexOf(":")==-1)return;
		long myRandomSeed = -1;
		try{myRandomSeed = Long.parseLong(s.substring(0,s.indexOf(":")));}catch(NumberFormatException e){log.error("Failed to parse randomSeed in incoming settingsok");return;}
		//s = s.substring(s.indexOf(":")+1);



		if(debug)log.error("incoming_ReplyToMySettings: My Seed: " +myRandomSeed);

		//Game them = games.get(myRandomSeed);
		//if(them==null){log.error("Could not find game with seed:" + myRandomSeed);return;}

		gotReplyToMySettings(true);
		//log.debug("gotReplyToMySettings:" +myRandomSeed);
	}


	//=========================================================================================================================
	private void incoming_Start(String s)
	{//=========================================================================================================================

		if(s.indexOf(":")==-1)return;
		long theirRandomSeed = -1;
		try{theirRandomSeed = Long.parseLong(s.substring(0,s.indexOf(":")));}catch(NumberFormatException e){log.error("Failed to parse randomSeed in incoming startok");return;}
		s = s.substring(s.indexOf(":")+1);

		if(debug)log.error("incoming_Start: Their Seed: " +theirRandomSeed);
		//Game them = games.get(randomSeed);
		//if(them==null){log.error("Could not find game with seed:" + randomSeed);return;}

		gotTheirStart(true);

		connection.write(netCommand_STARTOK+randomSeed+":"+BobNet.endline);

	}

	//=========================================================================================================================
	private void incoming_ReplyToMyStart(String s)
	{//=========================================================================================================================

		//randomSeed:

		if(s.indexOf(":")==-1)return;
		long theirRandomSeed = -1;
		try{theirRandomSeed = Long.parseLong(s.substring(0,s.indexOf(":")));}catch(NumberFormatException e){log.error("Failed to parse randomSeed in incoming frame packet");return;}
		//s = s.substring(s.indexOf(":")+1);

		if(debug)log.error("incoming_ReplyToMyStart: Their Seed: " +theirRandomSeed);
		//Game them = games.get(randomSeed);
		//if(them==null){log.error("Could not find game with seed:" + randomSeed);return;}

		gotReplyToMyStart(true);

	}

	//=========================================================================================================================
	private void incoming_Forfeit(String s)
	{//=========================================================================================================================

		//randomSeed:

		if(s.indexOf(":")==-1)return;
		long theirRandomSeed = -1;
		try{theirRandomSeed = Long.parseLong(s.substring(0,s.indexOf(":")));}catch(NumberFormatException e){log.error("Failed to parse randomSeed in incoming frame packet");return;}
		//s = s.substring(s.indexOf(":")+1);

		if(debug)log.error("incoming_Forfeit: Their Seed: " +theirRandomSeed);
		//Game them = games.get(randomSeed);
		//if(them==null){log.error("Could not find game with seed:" + randomSeed);return;}

		setTheyForfeit(true);

	}
	//=========================================================================================================================
	private void sendForfeit()
	{//=========================================================================================================================
		connection.write(netCommand_FORFEIT+randomSeed+":"+"-1"+BobNet.endline);
	}



	long sendSeedTicksCounter = 0;
	long sendSettingsTicksCounter = 0;
	long sendStartTicksCounter = 0;
	long sendFramesTicksCounter = 0;
	long queuePacketsTicksCounter = 0;
	long storePacketsTicksCounter = 0;
	public Vector<NetworkPacket> allNetworkPacketsUpUntilNow = new Vector<NetworkPacket>();

	//=========================================================================================================================
	private void send_Start()
	{//=========================================================================================================================

		long currentTime = System.currentTimeMillis();
		if(currentTime-sendStartTicksCounter>500)
		{
			sendStartTicksCounter=currentTime;

			if(debug)log.debug("send_Start: My Seed: "+randomSeed);
			connection.write(netCommand_START+randomSeed+":"+"-1"+BobNet.endline);
		}

	}

	//=========================================================================================================================
	private void send_Seed()
	{//=========================================================================================================================
		long currentTime = System.currentTimeMillis();
		if(currentTime-sendSeedTicksCounter>2000)
		{
			sendSeedTicksCounter=currentTime;

			if(debug)log.debug("send_Seed: My Seed: "+randomSeed);
			connection.write(netCommand_SEED+randomSeed+":"+"-1"+BobNet.endline);

		}
	}

	//=========================================================================================================================
	private void send_Settings()
	{//=========================================================================================================================
		long currentTime = System.currentTimeMillis();
		if(currentTime-sendSettingsTicksCounter>3000)
		{
			sendSettingsTicksCounter=currentTime;


			String b64zip = originalSettings.toBase64GZippedGSON();
			String md5 = Utils.getStringMD5(b64zip);


			String send = ""+netCommand_SETTINGS+randomSeed+":"+md5+":"+b64zip+BobNet.endline;
			if(debug)log.debug("send_Settings: My Seed: "+randomSeed);

			ChannelFuture c = connection.write(send);

			if(debug)log.debug("send_Settings: Sent in "+(System.currentTimeMillis()-currentTime)+"ms");

		}
	}





	private long winOrLoseTime = 0;

	private long checkLastTrafficTime = 0;
	private long _lastIncomingTrafficTime = 0;
	private boolean _theyForfeit = false;


	private boolean _gotReplyToMySeed = false;
	private boolean _gotReplyToMySettings = false;
	private boolean _gotTheirSettings = false;
	private boolean _gotReplyToMyStart = false;
	private boolean _gotTheirStart = false;


	private long _theirSeed = -1;
	private PuzzleGameType _theirSettings = null;

	boolean setSettings = false;

	public int lastSentPacket = 0;

	public Vector<String> outboundPacketQueueVector = new Vector<String>();
	public ConcurrentHashMap<String,String> outboundPacketQueueHashMap = new ConcurrentHashMap<String,String>();


	public Vector<String> gotPacketsLog = new Vector<String>();
	public long lastIncomingFramePacketID = 0;
	public ConcurrentHashMap<Long,Vector<FrameState>> incomingFramePackets = new ConcurrentHashMap<Long,Vector<FrameState>>();


	public synchronized boolean gotReplyToMySeed(){return _gotReplyToMySeed;}
	public synchronized boolean gotReplyToMySettings(){return _gotReplyToMySettings;}
	//public synchronized boolean gotTheirSettings(){return gotTheirSettings;}
	public synchronized boolean gotReplyToMyStart(){return _gotReplyToMyStart;}
	public synchronized boolean gotTheirStart(){return _gotTheirStart;}

	public synchronized long theirSeed(){return _theirSeed;}

	public synchronized PuzzleGameType theirSettings(){return _theirSettings;}


	public synchronized void gotReplyToMySeed(boolean gotReplyToMySeed){this._gotReplyToMySeed = gotReplyToMySeed;}
	public synchronized void gotReplyToMySettings(boolean gotReplyToMySettings){this._gotReplyToMySettings = gotReplyToMySettings;}
	//public synchronized void gotTheirSettings(boolean gotTheirSettings){this.gotTheirSettings = gotTheirSettings;}
	public synchronized void gotReplyToMyStart(boolean gotReplyToMyStart){this._gotReplyToMyStart = gotReplyToMyStart;}
	public synchronized void gotTheirStart(boolean gotTheirStart){this._gotTheirStart = gotTheirStart;}

	public synchronized void theirSeed(long theirSeed){this._theirSeed = theirSeed;}
	public synchronized void getTheirSettings(PuzzleGameType theirSettings){this._theirSettings = theirSettings;}


	public synchronized long getLastTimeGotIncomingTraffic_S(){return _lastIncomingTrafficTime;}
	public synchronized void setLastTimeGotIncomingTraffic_S(){this._lastIncomingTrafficTime = System.currentTimeMillis();}

	public synchronized boolean getTheyForfeit(){return _theyForfeit;}
	public synchronized void setTheyForfeit(boolean b){this._theyForfeit = b;}
	//=========================================================================================================================
	public void updateTitleScreenLogoTexture()
	{//=========================================================================================================================

		if(titleScreenTexture!=null)
		{
			GLUtils.releaseTexture(titleScreenTexture);
			titleScreenTexture=null;
		}

		String num = ""+currentTitleScreenTextureFrame;
		int len = num.length();
		for(int n=0;n<4-len;n++)num = "0"+num;//pad to 4 zeros

		titleScreenTexture = GLUtils.loadTexture("res/guiBackground/bobsGameLogoAnim/" +num+".png");


	}

	ArrayList<Caption> startMenuCaptions = null;
	int startMenuCursorPosition = 0;
	//=========================================================================================================================
	private void updateStartMenu()
	{//=========================================================================================================================


		if(startMenuCaptions==null)
		{
			startMenuCaptions = new ArrayList<Caption>();
			int y=0;
			Caption c = null;

			y = (int)(getHeight()/2);
			c = CaptionManager().newManagedCaption(Caption.CENTERED_X,y,-1,"Back To Game",BobFont.font_normal_16_outlined_smooth,BobColor.white,BobColor.clear,RenderOrder.OVER_GUI,1.0f,0);
			startMenuCaptions.add(c);

			y+=20;
			c = CaptionManager().newManagedCaption(Caption.CENTERED_X,y,-1,"Reset Game",BobFont.font_normal_16_outlined_smooth,BobColor.white,BobColor.clear,RenderOrder.OVER_GUI,1.0f,0);
			startMenuCaptions.add(c);

			y+=20;
			c = CaptionManager().newManagedCaption(Caption.CENTERED_X,y,-1,"Close nD",BobFont.font_normal_16_outlined_smooth,BobColor.white,BobColor.clear,RenderOrder.OVER_GUI,1.0f,0);
			startMenuCaptions.add(c);

		}


		if(ControlsManager().BUTTON_UP_PRESSED)
		{
			startMenuCursorPosition--;
			if(startMenuCursorPosition<0)startMenuCursorPosition=startMenuCaptions.size()-1;
		}



		if(ControlsManager().BUTTON_DOWN_PRESSED)
		{
			startMenuCursorPosition++;
			if(startMenuCursorPosition>startMenuCaptions.size()-1)startMenuCursorPosition=0;
		}


		if(ControlsManager().BUTTON_ACTION_PRESSED)
		{

			showingStartMenu=false;


			if(startMenuCursorPosition==0)
			{
				//nothing
			}


			if(startMenuCursorPosition==1)
			{
				showingTitleScreen = true;
				newGame();
			}


			if(startMenuCursorPosition==2)
			{
				nD.setActivated(false);
			}


			if(startMenuCaptions!=null)
			{
				for(int i=0;i<startMenuCaptions.size();i++)
				{
					startMenuCaptions.get(i).deleteImmediately();
				}
			}

			startMenuCaptions = null;

		}



	}

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================




		super.update();

		if(doneInitializingSprites==false)initSprites(SpriteManager());


		if(updateLoadScreens()==true)return;


		if(showingStartMenu==true)
		{
			updateStartMenu();
			return;
		}

		if(ControlsManager().BUTTON_RETURN_PRESSED)
		{
			if(isNetworkGame()==false)//no pause in multiplayer
			{
				showingStartMenu = true;
			}
		}


		int side = GameLogic.MIDDLE;
		if(isNetworkGame() || connection!=null)side = GameLogic.LEFT;

		ME.updateNormalGame(side);



		//shaderTicks += super.ticksPassed();
		if(ControlsManager().BUTTON_TAB_PRESSED)//shaderTicks>3000)
		{
			//shaderTicks=0;
			shaderCount++;
			if(shaderCount>=LWJGLUtils.bgShaderCount)shaderCount=0;

			//CaptionManager().newManagedCaption(0,0,2000,""+shaderCount,BobFont.font_normal_16_outlined_smooth,BobColor.white,BobColor.black,2.0f);
		}




		//TODO: make connections ArrayList or somehow allow multiple UDP connections attached to one game.
		//TODO: announce "playing game" to friends, when they join, connect friendUDPconnection to connection pool, each one given a game object
		if(connection!=null)
		{
			if(connection.established())
			{

				long currentTime = System.currentTimeMillis();

				if(networkGameStarted_NonThreaded==false)
				{


					//let's start by establishing who will send the settings first

					//then we'll send the settings reply once we get the server settings

					//that way they aren't randomly pinging each other and we can hopefully avoid the desync issue


					if(currentTime-nonThreadedTicksCounter>200)
					{
						nonThreadedTicksCounter=currentTime;



						if(gotReplyToMySeed()==false){send_Seed();return;}



						if(THEM==null)
						{
							if(theirSeed()!=-1)
							{
								if(debug)log.info("Made game");
								GameLogic g = new GameLogic(this,theirSeed());
								g.controlledByNetwork = true;

								g.grid.screenX = getWidth()*2;
								g.grid.screenY = getHeight()*2;

								THEM = g;
							}
							else
							{
								return;
							}
						}


						//send my settings if my randomseed is greater than theirs
						if(gotReplyToMySettings()==false && THEM.randomSeed<ME.randomSeed){send_Settings();return;}


						if(gotReplyToMySettings()==false){send_Settings();return;}


//						if(setSettings==false)
//						{
//							if(theirSettings()!=null)
//							{
//								log.info("Set settings");
//								THEM.setSettings(theirSettings());
//								setSettings=true;
//							}
//							else
//							{
//								return;
//							}
//						}


						//send my start if my randomseed is greater than theirs
						if(gotReplyToMyStart()==false && THEM.randomSeed<ME.randomSeed){send_Start();return;}


						//wait for start
						if(gotTheirStart()==false){return;}


						if(gotReplyToMyStart()==false){send_Start();return;}



						//if synced settings and started game
						if(THEM.waitingForPlayer==true){THEM.waitingForPlayer=false;}


						networkGameStarted_NonThreaded = true;
					}


				}
				else
				{





					//DONE: queue up packets, with id, md5
					if(ME.sendNetworkFrames)
					{
						//storeNetworkPackets();

						//queueSendPackets();

						//send_QueuedPacket();


						//=========================================================================================================================
						//protected void storeNetworkPackets()
						{//=========================================================================================================================
							if(currentTime-storePacketsTicksCounter>100)
							{
								storePacketsTicksCounter=currentTime;

								NetworkPacket packetToSplit = ME.networkPacket;
								ME.networkPacket = new GameLogic.NetworkPacket();


								int maxFramesInPacket = 20;

								if(packetToSplit.frameStates.size()>maxFramesInPacket)
								{

									//if player 1 has been playing for a while, the network packet will have too many frames in it.
									//so we split it into multiple packets.
									while(packetToSplit.frameStates.size()>0)
									{
										NetworkPacket sendPacket = new GameLogic.NetworkPacket();


										int size = packetToSplit.frameStates.size();
										for(int i=0;i<maxFramesInPacket&&i<size;i++)
										{
											sendPacket.frameStates.add(packetToSplit.frameStates.remove(0));
											size--;
										}

										allNetworkPacketsUpUntilNow.add(sendPacket);
									}

								}
								else
								{
									allNetworkPacketsUpUntilNow.add(packetToSplit);
								}
							}
						}




						//=========================================================================================================================
						//protected void queueSendPackets()
						{//=========================================================================================================================
							if(currentTime-queuePacketsTicksCounter>100)
							{
								queuePacketsTicksCounter=currentTime;


								int size = allNetworkPacketsUpUntilNow.size();

								for(int j=lastSentPacket; j<size; j++)
								{

									NetworkPacket networkPacket = allNetworkPacketsUpUntilNow.get(j);

									String b64zip = getFrameStatesAsBase64GZippedGSON(networkPacket);
									String md5 = Utils.getStringMD5(b64zip);

									//log.debug("Packet Size: "+b64zip.length());

									String idAndMD5String = ""+j+","+md5;

									outboundPacketQueueVector.add(idAndMD5String);//just so we have an ordered list we can get(0) from
									outboundPacketQueueHashMap.put(idAndMD5String,b64zip);
								}


								lastSentPacket=size;

							}
						}

						//=========================================================================================================================
						//private void send_QueuedPacket()
						{//=========================================================================================================================
							//send packet 0

							if(currentTime-sendFramesTicksCounter>50)
							{
								sendFramesTicksCounter=currentTime;

								if(outboundPacketQueueVector.size()>0)
								{
									String idAndMD5String = outboundPacketQueueVector.get(0);
									String b64zip = outboundPacketQueueHashMap.get(idAndMD5String);

									connection.write(netCommand_FRAME+ME.randomSeed+":"+idAndMD5String+":"+b64zip+BobNet.endline);
								}
							}
						}




						//=========================================================================================================================
						//private void updateNetworkGame()
						{//=========================================================================================================================

							if(incomingFramePackets.size()>0)
							{
								Vector<FrameState> frames = incomingFramePackets.remove(lastIncomingFramePacketID);

								if(frames!=null)
								{
									lastIncomingFramePacketID++;

									for(int i=0;i<frames.size();i++)THEM.networkPacket.frameStates.add(frames.get(i));
									THEM.waitingForNetworkFrames=false;
								}
							}

							THEM.updateNetworkGame();

							if(THEM.queuedGarbageAmountToSend>0)
							{
								ME.gotVSGarbageFromOtherPlayer(THEM.queuedGarbageAmountToSend);
								THEM.queuedGarbageAmountToSend=0;
							}

							if(ME.dead || THEM.credits)
							{
								ME.lose=true;
								THEM.win=true;
							}

							if(THEM.dead || ME.credits)
							{
								THEM.lose=true;
								ME.win=true;
							}
						}
					}




					if(currentTime - checkLastTrafficTime > 500)
					{
						checkLastTrafficTime = currentTime;

						if(currentTime-getLastTimeGotIncomingTraffic_S() > 10000)
						{
							//TODO: drop connection, match is forfeit, i am winner

							setTheyForfeit(true);
						}


						if(getTheyForfeit()==true)
						{
							THEM.lose = true;
							ME.win = true;
						}
					}


					if(ME.lose || ME.win)
					{
						if(currentTime-winOrLoseTime>5000)
						{
							if(ControlsManager().BUTTON_SPACE_PRESSED)
							{
								newGame();
							}
						}
					}
					else
					{
						winOrLoseTime = currentTime;
					}



				}
			}
		}
		else
		{
			if(isNetworkGame()==false)
			{

				if(ME.dead)
				{
					if(ControlsManager().BUTTON_SPACE_PRESSED)
					{
						newGame();
					}
				}
			}
		}
	}




	//=========================================================================================================================
	public static void changeBG()
	{//=========================================================================================================================
		//shaderTicks += super.ticksPassed();
		//if(ControlsManager().BUTTON_TAB_PRESSED)//shaderTicks>3000)
		{
			//shaderTicks=0;
			//shaderCount++;
			//if(shaderCount>=LWJGLUtils.bgShaderCount)shaderCount=0;

			shaderCount = Utils.randLessThan(LWJGLUtils.bgShaderCount);

			//CaptionManager().newManagedCaption(0,0,1000,""+shaderCount,BobFont.font_normal_16_outlined_smooth,BobColor.white,BobColor.black,2.0f);
		}

	}

	public static int shaderCount = Utils.randLessThan(LWJGLUtils.bgShaderCount);
	//long shaderTicks = 0;

	boolean fboTextureToggle = false;


	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================



		if(super.renderLoadScreens()==true)return;

		if(showingStartMenu==true)
		{
			renderStartMenu();
			return;

		}

		if(LWJGLUtils.useShader)
		{




			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity();
			glEnable( GL_DEPTH_TEST );


			fboTextureToggle = !fboTextureToggle;

			LWJGLUtils.bindFBO(LWJGLUtils.nDBGFBO);
			if(fboTextureToggle)LWJGLUtils.drawIntoFBOAttachment(0);
			else LWJGLUtils.drawIntoFBOAttachment(1);

			glViewport(0, 0, LWJGLUtils.nDBGFBOWidth, LWJGLUtils.nDBGFBOHeight);
			glLoadIdentity();
			glOrtho(-1, 1, -1, 1, -1, 1);
			float tempDrawScale = GLUtils.globalDrawScale;
			GLUtils.globalDrawScale = 1.0f;









			glActiveTexture(GL_TEXTURE1);
			glEnable(GL_TEXTURE_2D);

			if(fboTextureToggle)glBindTexture(GL_TEXTURE_2D, LWJGLUtils.nDBGFBO_Texture_1);
			else glBindTexture(GL_TEXTURE_2D, LWJGLUtils.nDBGFBO_Texture_0);





			glActiveTexture(GL_TEXTURE0);
			glEnable(GL_TEXTURE_2D);
			if(titleScreenTexture!=null)glBindTexture(GL_TEXTURE_2D, titleScreenTexture.getTextureID());


			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);


			float time = ((System.currentTimeMillis() - timeRenderBegan) / 2000.0f);


			int shaderInt = LWJGLUtils.bgShaders.get(shaderCount).intValue();

			LWJGLUtils.useShader(shaderInt);
			LWJGLUtils.setShaderVar2f(shaderInt, "resolution", LWJGLUtils.nDBGFBOWidth, LWJGLUtils.nDBGFBOHeight);
			LWJGLUtils.setShaderVar2f(shaderInt, "mouse", 0.5f, 0.5f);
			LWJGLUtils.setShaderVar1f(shaderInt, "time", time);
			LWJGLUtils.setShaderVar1i(shaderInt, "tex0", 0);
			LWJGLUtils.setShaderVar1i(shaderInt, "backbuffer", 1);
			LWJGLUtils.setShaderVar1i(shaderInt, "bb", 1);
			//LWJGLUtils.setShaderVar1i(LWJGLUtils.fractalShader, "tex1", 1);

			GLUtils.drawFilledRect(255,255,255,-1.0f,1.0f,-1.0f,1.0f,1.0f);

			LWJGLUtils.useShader(0);



			glDisable(GL_DEPTH_TEST);

			//disable texture2D on texture unit 1
			glActiveTexture(GL_TEXTURE1);
			glDisable(GL_TEXTURE_2D);

			//switch back to texture unit 0
			glActiveTexture(GL_TEXTURE0);
			glDisable(GL_TEXTURE_2D);


			LWJGLUtils.bindFBO(LWJGLUtils.nDFBO);
			LWJGLUtils.drawIntoFBOAttachment(0); //draw to nD FBO screen texture
			ND.setNDViewport();
			GLUtils.globalDrawScale = tempDrawScale;

			if(fboTextureToggle)GLUtils.drawTexture(LWJGLUtils.nDBGFBO_Texture_0, 0.0f, 1.0f, 1.0f, 0.0f, 0, getWidth(), 0, getHeight(), 1.0f, GLUtils.FILTER_FBO_LINEAR_NO_MIPMAPPING);
			else GLUtils.drawTexture(LWJGLUtils.nDBGFBO_Texture_1, 0.0f, 1.0f, 1.0f, 0.0f, 0, getWidth(), 0, getHeight(), 1.0f, GLUtils.FILTER_FBO_LINEAR_NO_MIPMAPPING);

			GLUtils.drawFilledRect(0,0,0,0, getWidth(), 0, getHeight(),0.3f);

		}



		ND.setNDViewport();


		ME.renderBackground();
		if(networkGameStarted_NonThreaded==true)THEM.renderBackground();











		//render the playing field blocks to a FBO

		//draw the FBO to the screen with blur shader and 50% alpha

		//draw the FBO to the screen


		if(LWJGLUtils.useShader)
		{
			LWJGLUtils.drawIntoFBOAttachment(1); // draw to nDFBO auxiliary texture
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}


		ME.renderBlocks();
		if(networkGameStarted_NonThreaded==true)THEM.renderBlocks();



		if(LWJGLUtils.useShader)
		{

			LWJGLUtils.bindFBO(LWJGLUtils.nDBloomFBO);
			ND.setNDBloomViewport();


			glDisable(GL_BLEND);
			glDisable(GL_DEPTH_TEST);
			glDepthMask(false);


			LWJGLUtils.drawIntoFBOAttachment(1);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			LWJGLUtils.drawIntoFBOAttachment(0); //draw to bloom FBO texture 0
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



			LWJGLUtils.useShader(LWJGLUtils.maskShader);

				glBindTexture(GL_TEXTURE_2D, LWJGLUtils.nDFBO_MaskTexture);
				LWJGLUtils.setShaderVar1i(LWJGLUtils.maskShader, "u_texture0", 0);

				float threshold = 0.1f;
				LWJGLUtils.setShaderVar2f(LWJGLUtils.maskShader, "treshold", threshold, 1f / (1 - threshold));

				GLUtils.drawTexture(LWJGLUtils.nDFBO_MaskTexture, 0, 1, 0, 1, -1, 1, -1, 1, 1.0f, GLUtils.FILTER_FBO_LINEAR_NO_MIPMAPPING);

				LWJGLUtils.useShader(0);

			//GLUtils.drawTexture(LWJGLUtils.nDFBO_AuxiliaryTexture, 0, 1, 0, 1, -1, 1, -1, 1, 1, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);





			int blurPasses = ME.Settings().bloomTimes;

			for (int i = 0; i < blurPasses; i++)
			{

				float w = getWidth()*ND.BLOOM_FBO_SCALE;
				float h = getHeight()*ND.BLOOM_FBO_SCALE;

				// horizontal
				LWJGLUtils.drawIntoFBOAttachment(1);
				{
					LWJGLUtils.useShader(LWJGLUtils.gaussianShader);
					{


						LWJGLUtils.setShaderVar2f(LWJGLUtils.gaussianShader, "size", w, h);
						LWJGLUtils.setShaderVar2f(LWJGLUtils.gaussianShader, "dir", 1f, 0f);
						GLUtils.drawTexture(LWJGLUtils.nDBloomFBO_Texture_0,  0, 1, 0, 1, -1, 1, -1, 1, 1.0f, GLUtils.FILTER_FBO_LINEAR_NO_MIPMAPPING);

					}
					LWJGLUtils.useShader(0);
				}



				// vertical
				LWJGLUtils.drawIntoFBOAttachment(0);
				{
					LWJGLUtils.useShader(LWJGLUtils.gaussianShader);
					{
						LWJGLUtils.setShaderVar2f(LWJGLUtils.gaussianShader, "size", w, h);
						LWJGLUtils.setShaderVar2f(LWJGLUtils.gaussianShader, "dir", 0f, 1f);
						GLUtils.drawTexture(LWJGLUtils.nDBloomFBO_Texture_1, 0, 1, 0, 1, -1, 1, -1, 1, 1, GLUtils.FILTER_FBO_LINEAR_NO_MIPMAPPING);

					}
					LWJGLUtils.useShader(0);
				}

			}



			LWJGLUtils.bindFBO(LWJGLUtils.nDFBO);
			LWJGLUtils.drawIntoFBOAttachment(0); //draw to nD FBO screen texture
			ND.setNDViewport();

			//if(blending)
			{
				glEnable(GL_BLEND);
				LWJGLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			}


			//pingPongTex1.bind(1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, LWJGLUtils.nDBloomFBO_Texture_0);


			//original.bind(0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, LWJGLUtils.nDFBO_MaskTexture);



			LWJGLUtils.useShader(LWJGLUtils.bloomShader);
			{
				LWJGLUtils.setShaderVar1f(LWJGLUtils.bloomShader, "OriginalIntensity", 0.8f);
				LWJGLUtils.setShaderVar1f(LWJGLUtils.bloomShader, "BloomIntensity", ME.Settings().bloomIntensity);
				LWJGLUtils.setShaderVar1i(LWJGLUtils.bloomShader, "u_texture0", 0);
				LWJGLUtils.setShaderVar1i(LWJGLUtils.bloomShader, "u_texture1", 1);
				GLUtils.drawTexture(LWJGLUtils.nDFBO_MaskTexture, 0.0f, 1.0f, 1.0f, 0.0f, 0, getWidth(), 0, getHeight(), 1.0f, GLUtils.FILTER_FBO_LINEAR_NO_MIPMAPPING);
			}
			LWJGLUtils.useShader(0);


			//disable texture2D on texture unit 1
			glActiveTexture(GL_TEXTURE1);
			glDisable(GL_TEXTURE_2D);

			//switch back to texture unit 0
			glActiveTexture(GL_TEXTURE0);
			glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D);


			LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		}



		ME.renderForeground();
		if(networkGameStarted_NonThreaded==true)THEM.renderForeground();




		super.render();

	}



	//=========================================================================================================================
	private void renderStartMenu()
	{//=========================================================================================================================

		//super.render();//captions
		CaptionManager().render(RenderOrder.OVER_GUI);

		Texture t = cursorTexture;

		if(t!=null && startMenuCaptions!=null)
		{

			float tx0 = 0;
			float tx1 = 1;

			float ty0 = 0;
			float ty1 = 1;

			float sx0 = startMenuCaptions.get(startMenuCursorPosition).screenX-16;
			if(cursorInOutToggle)sx0+=2;
			float sx1 = sx0+16;

			float sy0 = startMenuCaptions.get(startMenuCursorPosition).screenY+2;
			float sy1 = sy0+16;


			GLUtils.drawTexture(t, tx0,tx1,ty0,ty1, sx0,sx1,sy0,sy1, 1.0f, GLUtils.FILTER_NEAREST);

		}

	}


	//long cellTicks = 0;

//	//=========================================================================================================================
//	void renderCellularEffect(float time)
//	{//=========================================================================================================================
////		// set 2d mode
////		glMatrixMode( GL_PROJECTION );
////		glLoadIdentity();
////		glMatrixMode( GL_MODELVIEW );
////		glLoadIdentity();
////
////		// clear the buffers
////		glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
//
//		glEnable(GL_DEPTH_TEST);
//		glDisable(GL_TEXTURE_2D);
//
//
//		// render the cells
//		int numCells = 100;
//		int sem = 134;
//		for(int j=0; j < numCells; j++ )
//		{
//			// move the cell on the screen
//			float x = (float)Math.cos( (float)(Utils.randLessThan(sem)*3.14f) + ((float)Utils.randLessThan(sem)*time) );
//			float y = (float)Math.cos( (float)(Utils.randLessThan(sem)*3.14f) + ((float)Utils.randLessThan(sem)*time) );
//
//			// render cone (can be optimized of course)
//			glBegin( GL_TRIANGLE_FAN );
//			glColor4f( 0.0f, 0.0f, 0.0f, 1.0f );
//			glVertex3f( x, y, 1.0f );
//			glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
//			for(int i=0; i < 48; i++ )
//			{
//				float an = (6.28318f/47.0f)*(float)i;
//				glVertex3f((float)(x+Math.cos(an)), (float)(y+Math.sin(an)), -1.0f );
//			}
//			glEnd();
//		}
//
//		glDisable(GL_DEPTH_TEST);
//		glEnable(GL_TEXTURE_2D);
////
////		nD.setViewport();
//
//
//	}





	//---------------------------------------------------
	// block graphics
	//----------------------------------------------------

	public static Sprite bobsGameLogoSmall;


	public static Sprite circle;
	public static String circleName = "Circle";

	public static Sprite square;
	public static String squareName = "Square";

	public static Sprite roundedSquareOutline;
	public static String roundedSquareOutlineName = "RoundedSquareOutline";

	public static Sprite squareGem;
	public static String squareGemName = "SquareGem";

	//public static Sprite octagonGem;
	//public static Sprite hexagonGem;

	public static Sprite diamondGem;//puzzle fighter
	public static String diamondGemName = "DiamondGem";

	public static Sprite blob;
	public static String blobName = "Blob";

	public static Sprite virus;// dr mario
	public static String virusName = "Virus";

	public static Sprite circleOutline;
	public static String circleOutlineName = "CircleOutline";

	public static Sprite squareOutline;
	public static String squareOutlineName = "SquareOutline";

	public static Sprite counter;//crash gem, puzzle fighter
	public static String counterName = "Counter";

	public static Sprite sparkBall;//crash gem, puzzle fighter
	public static String sparkBallName = "SparkBall";

	public static Sprite happyBall;
	public static String happyBallName = "HappyBall";

	public static Sprite angryBall;
	public static String angryBallName = "AngryBall";

	public static Sprite pacJar;
	public static String pacjarName = "PacJar";

	public static Sprite pacBall;
	public static String pacBallName = "PacBlob";

	public static Sprite ballJar;
	public static String ballJarName = "BallJar";

	public static Sprite exclamationIconBlock;
	public static String exclamationIconBlockName = "ExclamationIconBlock";

	public static Sprite heartIconBlock;
	public static String heartIconBlockName = "HeartIconBlock";

	public static Sprite circleIconBlock;
	public static String circleIconBlockName = "CircleIconBlock";

	public static Sprite triangleIconBlock;
	public static String triangleIconBlockName = "TriangleIconBlock";

	public static Sprite upsideDownTriangleIconBlock;
	public static String upsideDownTriangleIconBlockName = "UpsideDownTriangleIconBlock";

	public static Sprite diamondIconBlock;
	public static String diamondIconBlockName = "DiamondIconBlock";

	public static Sprite starIconBlock;
	public static String starIconBlockName = "StarIconBlock";

	public static Sprite plusShooterBlock;
	public static String plusShooterBlockName = "PlusBlock";

	public static Sprite minusShooterBlock;
	public static String minusShooterBlockName = "MinusBlock";

	public static Sprite bombBlock;
	public static String bombBlockName = "BombBlock";

	public static Sprite weightBlock;
	public static String weightBlockName = "WeightSpawnBlock";

	public static Sprite linesBlock;
	public static String linesBlockName = "LinesBlock";

	public static Sprite bomb;
	public static String bombName = "Bomb";

	public static Sprite weight;
	public static String weightName = "Weight";



	//=========================================================================================================================
	public static void initSprites(SpriteManager spriteManager)
	{//=========================================================================================================================

		boolean allDone = true;

		//these should be initialized automatically when loading gameData so it is safe to assume they are initialized here
		if(bobsGameLogoSmall==null){bobsGameLogoSmall = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist("bobsGameLogoSmall");allDone=false;}
		if(circle==null){circle = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(circleName);allDone=false;}
		if(square==null){square = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(squareName);allDone=false;}
		if(roundedSquareOutline==null){roundedSquareOutline = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(roundedSquareOutlineName);allDone=false;}
		if(squareGem==null){squareGem = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(squareGemName);allDone=false;}
		if(diamondGem==null){diamondGem = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(diamondGemName);allDone=false;}
		if(blob==null){blob = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(blobName);allDone=false;}
		if(virus==null){virus = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(virusName);allDone=false;}
		if(circleOutline==null){circleOutline = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(circleOutlineName);allDone=false;}
		if(squareOutline==null){squareOutline = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(squareOutlineName);allDone=false;}
		if(sparkBall==null){sparkBall = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(sparkBallName);allDone=false;}
		if(counter==null){counter = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(counterName);allDone=false;}
		if(happyBall==null){happyBall = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(happyBallName);allDone=false;}
		if(angryBall==null){angryBall = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(angryBallName);allDone=false;}
		if(pacJar==null){pacJar = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(pacjarName);allDone=false;}
		if(pacBall==null){pacBall = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(pacBallName);allDone=false;}
		if(ballJar==null){ballJar = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(ballJarName);allDone=false;}
		if(exclamationIconBlock==null){exclamationIconBlock = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(exclamationIconBlockName);allDone=false;}
		if(heartIconBlock==null){heartIconBlock = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(heartIconBlockName);allDone=false;}
		if(circleIconBlock==null){circleIconBlock = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(circleIconBlockName);allDone=false;}
		if(triangleIconBlock==null){triangleIconBlock = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(triangleIconBlockName);allDone=false;}
		if(upsideDownTriangleIconBlock==null){upsideDownTriangleIconBlock = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(upsideDownTriangleIconBlockName);allDone=false;}
		if(diamondIconBlock==null){diamondIconBlock = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(diamondIconBlockName);allDone=false;}
		if(starIconBlock==null){starIconBlock = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(starIconBlockName);allDone=false;}
		if(plusShooterBlock==null){plusShooterBlock = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(plusShooterBlockName);allDone=false;}
		if(minusShooterBlock==null){minusShooterBlock = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(minusShooterBlockName);allDone=false;}
		if(bombBlock==null){bombBlock = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(bombBlockName);allDone=false;}
		if(weightBlock==null){weightBlock = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(weightBlockName);allDone=false;}
		if(linesBlock==null){linesBlock = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(linesBlockName);allDone=false;}
		if(bomb==null){bomb = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(bombName);allDone=false;}
		if(weight==null){weight = spriteManager.getSpriteByNameOrRequestFromServerIfNotExist(weightName);allDone=false;}

		if(allDone==true)doneInitializingSprites = true;
	}

	//=========================================================================================================================
	public static Sprite getSpriteFromName(String name)
	{//=========================================================================================================================

		if(name==null)
		{
			log.error("getSpriteFromName name is null");
			new Exception().printStackTrace();
			System.exit(0);
		}

		if(name.equals(circleName))return circle;
		if(name.equals(squareName))return square;
		if(name.equals(roundedSquareOutlineName))return roundedSquareOutline;
		if(name.equals(squareGemName))return squareGem;
		if(name.equals(diamondGemName))return diamondGem;
		if(name.equals(blobName))return blob;
		if(name.equals(virusName))return virus;
		if(name.equals(circleOutlineName))return circleOutline;
		if(name.equals(squareOutlineName))return squareOutline;
		if(name.equals(counterName))return counter;
		if(name.equals(sparkBallName))return sparkBall;
		if(name.equals(happyBallName))return happyBall;
		if(name.equals(angryBallName))return angryBall;
		if(name.equals(pacjarName))return pacJar;
		if(name.equals(pacBallName))return pacBall;
		if(name.equals(ballJarName))return ballJar;
		if(name.equals(exclamationIconBlockName))return exclamationIconBlock;
		if(name.equals(heartIconBlockName))return heartIconBlock;
		if(name.equals(circleIconBlockName))return circleIconBlock;
		if(name.equals(triangleIconBlockName))return triangleIconBlock;
		if(name.equals(upsideDownTriangleIconBlockName))return upsideDownTriangleIconBlock;
		if(name.equals(diamondIconBlockName))return diamondIconBlock;
		if(name.equals(starIconBlockName))return starIconBlock;
		if(name.equals(plusShooterBlockName))return plusShooterBlock;
		if(name.equals(minusShooterBlockName))return minusShooterBlock;
		if(name.equals(bombBlockName))return bombBlock;
		if(name.equals(weightBlockName))return weightBlock;
		if(name.equals(linesBlockName))return linesBlock;
		if(name.equals(bombName))return bomb;
		if(name.equals(weightName))return weight;

		return null;
	}


}
