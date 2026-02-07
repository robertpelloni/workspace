package com.bobsgame.client.engine.game;

//import static org.jboss.netty.channel.Channels.pipeline;

//import org.jboss.netty.channel.ChannelHandlerContext;
//import org.jboss.netty.channel.MessageEvent;
import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.console.Console;
import com.bobsgame.client.engine.entity.Character;
import com.bobsgame.client.engine.game.gui.GameChallengeNotificationPanel;
import com.bobsgame.client.engine.game.nd.NDGameEngine;
import com.bobsgame.client.engine.map.Map;
import com.bobsgame.client.network.FriendUDPConnection;

import com.bobsgame.net.BobNet;
import com.bobsgame.net.GameSave;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.EntityData;



//===============================================================================================
public class FriendCharacter extends Character
{//===============================================================================================

	public static Logger log = (Logger) LoggerFactory.getLogger(FriendCharacter.class);




	public int friendUserID = -1;



	public static final int FACEBOOK_TYPE = 0;
	public static final int GOOGLE_TYPE = 1;
	public static final int TWITTER_TYPE = 2;
	public static final int ZIP_TYPE = 3;
	public int friendType = -1;
	//0 facebook
	//1 google
	//2 twitter
	//3 zip





	public FriendUDPConnection connection = null;

	FriendManager friendManager;


	public String mapName = "";

	public static int status_AVAILABLE = 0;
	public static int status_PLAYING_GAME = 1;
	public static int status_AWAY = 2;
	public static int status_DO_NOT_DISTURB = 3;
	private int _status = status_AVAILABLE;


	NDGameEngine game = null;


	float targetX = 0;
	float targetY = 0;

	//===============================================================================================
	public FriendCharacter(ClientGameEngine g, Map m)
	{//===============================================================================================
		super
		(
			g,
			new EntityData(-1,"Camera","Camera",0,0,0,false,true,255,1.25f,8,false,false,false,false,false,0,0,false,false,false,null,""),
			m
		);

		setScale(1.25f);

		rotationAnimationSpeedTicks = 100;//80;
	}

	//===============================================================================================
	public FriendCharacter(ClientGameEngine g, int friendUserID, int friendType, Map m)
	{//===============================================================================================


		this(g,m);//does NOT add to entityList
		friendManager = g.friendManager;

		this.friendUserID = friendUserID;
		this.friendType = friendType;


		connection = new FriendUDPConnection(g, friendManager.getNextUDPPort(),this);

	}

	//===============================================================================================
	/** FOR DEBUG */
	public FriendCharacter(ClientGameEngine g, int friendUserID, int friendType, int myUDPPort, int theirUDPPort, Map m)
	{//===============================================================================================


		//FOR DEBUG
		//FOR DEBUG
		//FOR DEBUG

		this(g,m);//does NOT add to entityList
		friendManager = g.friendManager;

		this.friendUserID = friendUserID;
		this.friendType = friendType;

		connection = new FriendUDPConnection(g, myUDPPort, this);
		connection.setPeerSocketAddress_S("127.0.0.1",theirUDPPort);

	}


	//===============================================================================================
	public void setGameToForwardPacketsTo(NDGameEngine game)
	{//===============================================================================================

		this.game = game;
	}

	//===============================================================================================
	public void handleMessage(String s)
	{//===============================================================================================

		if(s.startsWith(BobNet.Friend_LocationStatus_Update)){incomingFriendLocationStatusUpdate(s);return;}
		if(s.startsWith(BobNet.Friend_Data_Request)){incomingFriendDataRequest(s);return;}
		if(s.startsWith(BobNet.Friend_Data_Response)){incomingFriendDataResponse(s);return;}
		if(s.startsWith(BobNet.Game_Challenge_Request)){incomingGameChallengeRequest(s);return;}

		if(game!=null)game.handleMessage(s);
	}





	long lastSentFriendDataRequestTime = System.currentTimeMillis();
	long lastSentLocationTime = System.currentTimeMillis();

	boolean gotFriendData_NonThreaded = false;

	//===============================================================================================
	public void update()
	{//===============================================================================================


		super.update();//Character.update() -> Entity.update()



		connection.update();

		long currentTime = System.currentTimeMillis();


		//see if we have a udp connection to them established
		if(connection.established())
		{



			if(gotFriendData_NonThreaded==false)
			{
				//trade info, name, etc
				if(currentTime-lastSentFriendDataRequestTime>3000)
				{
					lastSentFriendDataRequestTime = currentTime;

					if(getGotFriendData_S()==false)
					{
						connection.write(BobNet.Friend_Data_Request+BobNet.endline);
					}
					else
					{
						gotFriendData_NonThreaded = true;
					}
				}
			}


			//generate avatar from charAppearance
			if(uniqueTexture==null)
			{
				if(getGotFriendData_S()==true)
				{

					String characterName = getFriendData_S().characterName;
					String characterAppearance = getFriendData_S().characterAppearance;
					int accountRank = getFriendData_S().accountRank;


					setAppearanceFromCharacterAppearanceString(characterAppearance);

					setCharacterNameAndCaption
					(
						ClientGameEngine().getNameColor(accountRank),
						characterName,
						ClientGameEngine().getAccountRankColor(accountRank),
						ClientGameEngine().getAccountRankString(accountRank)
					);
				}
			}


			//send room,x,y
			//xy data, messages, minigame reqs, etc.
			if(currentTime-lastSentLocationTime>100)
			{
				lastSentLocationTime = currentTime;

				sendFriendLocationStatusUpdate();

			}

		}

		//TODO: need function to get screen pixels based on camera zoom
		if(Math.abs(roundedMiddleX() - targetX)>Engine().getWidth())setX(targetX - middleOffsetX());
		if(Math.abs(roundedMiddleY() - targetY)>Engine().getWidth())setY(targetY - middleOffsetY());

		walkToXYNoCheckHit(targetX,targetY);

		checkIfMoved();

		doCharacterAnimation();


	}



	//===============================================================================================
	public boolean connected()
	{//===============================================================================================
		return connection.established();
	}


	//===============================================================================================
	public void handleDisconnected()
	{//===============================================================================================

		if(getFriendData_S()!=null)Console.add(""+getFriendData_S().characterName+" escaped from reality and has descended into the inferior meat world. What a traitor.",BobColor.red,5000);

		//TODO: need to remove from FriendManager

	}




	//TODO: no idea if synchronized functions that access non-synchronized variables works the way I want.
	//===============================================================================================
	public synchronized void setMapName_S(String mapName)
	{//===============================================================================================
		this.mapName = mapName;
	}

	//===============================================================================================
	public synchronized void setX_S(float x)
	{//===============================================================================================
		this.setX(x);
	}

	//===============================================================================================
	public synchronized void setY_S(float y)
	{//===============================================================================================
		this.setY(y);
	}



	//===============================================================================================
	public synchronized void setStatus_S(int i)
	{//===============================================================================================
		_status = i;
	}



	//===============================================================================================
	public synchronized int getStatus_S()
	{//===============================================================================================

		return _status; // TODO need to send current status, away, busy, private, do not disturb, playing nD game, etc.

	}



	//===============================================================================================
	public void cleanup()
	{//===============================================================================================

		connection.cleanup();

	}





	private FriendData _friendData = null;
	private boolean _gotFriendData = false;

	//===============================================================================================
	synchronized public void setGotFriendData_S(boolean b)
	{//===============================================================================================
		_gotFriendData = b;
	}
	//===============================================================================================
	synchronized public boolean getGotFriendData_S()
	{//===============================================================================================
		return _gotFriendData;
	}
	//===============================================================================================
	synchronized public void setFriendData_S(FriendData f)
	{//===============================================================================================
		_friendData = f;
	}
	//===============================================================================================
	synchronized public FriendData getFriendData_S()
	{//===============================================================================================
		return _friendData;
	}




	//===============================================================================================
	public void incomingFriendDataRequest(String s)
	{//===============================================================================================

		//allowed info depends on type of friend, zip code friends should not get full name, etc.
		// send name,charAppearance, etc


		if(ClientGameEngine().getGameSaveInitialized_S()==false)return;

		FriendData myFriendData = new FriendData();
		myFriendData.initWithGameSave(GameSave());

		String responseData = myFriendData.encode(friendType);

		connection.write(BobNet.Friend_Data_Response+responseData+BobNet.endline);
	}


	//===============================================================================================
	public void incomingFriendDataResponse(String s)
	{//===============================================================================================

		s = s.substring(s.indexOf(":")+1);

		FriendData f = new FriendData();
		f.decode(s);

		setFriendData_S(f);
		setGotFriendData_S(true);
	}


	//===============================================================================================
	private void sendFriendLocationStatusUpdate()
	{//===============================================================================================

		connection.write
		(
				BobNet.Friend_LocationStatus_Update+
				getMap().name()+
				","+
				Player().roundedMiddleX()+
				","+
				Player().roundedMiddleY()+
				","+
				FriendManager().myStatus+
				BobNet.endline
		);
	}

	//===============================================================================================
	public void incomingFriendLocationStatusUpdate(String s)
	{//===============================================================================================

		//FriendLocationUpdate:mapName,x,y,status
		s = s.substring(s.indexOf(":")+1);

		String mapName = s.substring(0,s.indexOf(","));
		s = s.substring(s.indexOf(",")+1);

		float mapX = -1;
		try{mapX = Float.parseFloat(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){return;}
		s = s.substring(s.indexOf(",")+1);

		float mapY = -1;
		try{mapY = Float.parseFloat(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){return;}
		s = s.substring(s.indexOf(",")+1);

		int status = -1;
		try{status = Integer.parseInt(s);}catch(NumberFormatException ex){return;}


		targetX = mapX;
		targetY = mapY;

		setMapName_S(mapName);
		setStatus_S(status);

	}




	private int outgoingGameChallengeResponse = NDGameEngine.gameChallengeResponse_NONE;
	private long timeOutgoingGameChallengeResponseSet = 0;
	public GameChallengeNotificationPanel gameChallengeNotification = null;

	//===============================================================================================
	public synchronized void setOutgoingGameChallengeResponse(int i)
	{//===============================================================================================

		timeOutgoingGameChallengeResponseSet = System.currentTimeMillis();

		outgoingGameChallengeResponse = i;

		if(i==NDGameEngine.gameChallengeResponse_ACCEPT)sendGameChallengeResponse(true);
		else
		if(i==NDGameEngine.gameChallengeResponse_DECLINE)sendGameChallengeResponse(false);
	}

	//===============================================================================================
	public synchronized int getOutgoingGameChallengeResponse()
	{//===============================================================================================


		//store last challenge time for this user
		//if challenge less than 10 seconds ago, just send last decision.


		long currentTime = System.currentTimeMillis();
		if(currentTime - timeOutgoingGameChallengeResponseSet > 10000)
		{
			outgoingGameChallengeResponse=NDGameEngine.gameChallengeResponse_NONE;
		}

		return outgoingGameChallengeResponse;

	}


	//===============================================================================================
	public void sendGameChallengeResponse(boolean b)
	{//===============================================================================================

		if(b==true)
		{
			connection.write(BobNet.Game_Challenge_Response+"Accept"+BobNet.endline);
		}
		else
		{
			connection.write(BobNet.Game_Challenge_Response+"Decline"+BobNet.endline);
		}

	}



	//===============================================================================================
	public void incomingGameChallengeRequest(String s)
	{//===============================================================================================



		s = s.substring(s.indexOf(":")+1);
		String gameName = s;


		//if player is already in game, they should not show up in the minigame challenge list, should broadcast current status constantly.
		//however, if they got populated before the broadcast was received, automatically deny the request

		if(FriendManager().myStatus!=FriendCharacter.status_AVAILABLE)
		{
			sendGameChallengeResponse(false);
			return;
		}

		if(getOutgoingGameChallengeResponse()==NDGameEngine.gameChallengeResponse_NONE)
		{

			//if notification is already open, don't open a new one, wait for the old one to time out.
			if(this.gameChallengeNotification!=null)return;

			//&&this.gameChallengeNotification.isActivated()==true)return; //this doesn't work because we destroy the GUI on unload.


			//open dialog window with friendname, game name
			this.gameChallengeNotification = GUIManager().makeGameChallengeNotification(this,gameName);
		}
		else
		{

			//resend last response
			if(getOutgoingGameChallengeResponse()==NDGameEngine.gameChallengeResponse_ACCEPT)sendGameChallengeResponse(true);
			else
			if(getOutgoingGameChallengeResponse()==NDGameEngine.gameChallengeResponse_DECLINE)sendGameChallengeResponse(false);

		}

	}



	//===============================================================================================
	static public class FriendData
	{//===============================================================================================

		public int friendType;

		public String characterName = "???";
		public String characterAppearance = "";
		public int accountRank = 0;

		public long accountCreatedTime = 0;
		public int timesLoggedIn = 0;
		public long totalTimePlayed = 0;
		public String postalCode = "";
		public String countryName = "";
		public String isoCountryCode = "";
		public String placeName = "";
		public String stateName = "";
		public float lat = 0;
		public float lon = 0;

		public int miniGamesTimesPlayed = 0;
		public int miniGamesTimesBattled = 0;
		public int miniGamesTimesChallenged = 0;
		public int miniGamesTimesChallenger = 0;
		public int miniGamesTimesWon = 0;
		public int miniGamesTimesLost = 0;
		public int miniGamesTimesTied = 0;



		public String facebookID = "";
		public String facebookEmail = "";
		//public String facebookBirthday = "";
		public String facebookFirstName = "";
		public String facebookLastName = "";
		public String facebookGender = "";
		//public String facebookLocale = "";
		//public Float facebookTimeZone = 0.0f;
		//public String facebookUsername = "";
		//public String facebookWebsite = "";
		//public String googlePlusID = "";





		//===============================================================================================
		public void initWithGameSave(GameSave g)
		{//===============================================================================================

			characterName             =g.characterName             ;
			characterAppearance       =g.characterAppearance       ;
			accountRank               =g.accountRank               ;
			accountCreatedTime        =g.accountCreatedTime        ;
			timesLoggedIn             =g.timesLoggedIn             ;
			totalTimePlayed           =g.totalTimePlayed           ;
			postalCode                =g.postalCode                ;
			countryName               =g.countryName               ;
			isoCountryCode            =g.isoCountryCode            ;
			placeName                 =g.placeName                 ;
			stateName                 =g.stateName                 ;
			lat                       =g.lat                       ;
			lon                       =g.lon                       ;

			miniGamesTimesPlayed      =g.miniGamesTimesPlayed      ;
			miniGamesTimesBattled     =g.miniGamesTimesBattled     ;
			miniGamesTimesChallenged  =g.miniGamesTimesChallenged  ;
			miniGamesTimesChallenger  =g.miniGamesTimesChallenger  ;
			miniGamesTimesWon         =g.miniGamesTimesWon         ;
			miniGamesTimesLost        =g.miniGamesTimesLost        ;
			miniGamesTimesTied        =g.miniGamesTimesTied        ;

			facebookID                =g.facebookID                ;
			facebookEmail             =g.facebookEmail             ;
			//facebookBirthday          =g.facebookBirthday          ;
			facebookFirstName         =g.facebookFirstName         ;
			facebookLastName          =g.facebookLastName          ;
			facebookGender            =g.facebookGender            ;
			//facebookLocale            =g.facebookLocale            ;
			//facebookTimeZone          =g.facebookTimeZone          ;
			//facebookUsername          =g.facebookUsername          ;
			//facebookWebsite           =g.facebookWebsite           ;
			//googlePlusID              =g.googlePlusID              ;

		}


		//===============================================================================================
		public String encode(int friendType)
		{//===============================================================================================

			this.friendType = friendType;

			String s = ""+
			friendType+","+
			"`"+characterName           +"`"+","+
			"`"+characterAppearance     +"`"+","+
			"`"+accountRank             +"`"+","+
			"`"+accountCreatedTime      +"`"+","+
			"`"+timesLoggedIn           +"`"+","+
			"`"+totalTimePlayed         +"`"+","+
			"`"+postalCode              +"`"+","+
			"`"+countryName             +"`"+","+
			"`"+isoCountryCode          +"`"+","+
			"`"+placeName               +"`"+","+
			"`"+stateName               +"`"+","+
			"`"+lat                     +"`"+","+
			"`"+lon                     +"`"+","+
			"`"+miniGamesTimesPlayed    +"`"+","+
			"`"+miniGamesTimesBattled   +"`"+","+
			"`"+miniGamesTimesChallenged+"`"+","+
			"`"+miniGamesTimesChallenger+"`"+","+
			"`"+miniGamesTimesWon       +"`"+","+
			"`"+miniGamesTimesLost      +"`"+","+
			"`"+miniGamesTimesTied      +"`";

			if(friendType==ZIP_TYPE)return s;

			s = s+","+
			"`"+facebookID              +"`"+","+
			"`"+facebookEmail           +"`"+","+
			//"`"+facebookBirthday        +"`"+","+
			"`"+facebookFirstName       +"`"+","+
			"`"+facebookLastName        +"`"+","+
			"`"+facebookGender          +"`"
			//"`"+facebookLocale          +"`"+","+
			//"`"+facebookTimeZone        +"`"+","+
			//"`"+facebookUsername        +"`"+","+
			//"`"+facebookWebsite         +"`"+","+
			//"`"+googlePlusID            +"`"
			;

			return s;
		}



		//===============================================================================================
		public void decode(String s)
		{//===============================================================================================

			try{friendType = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(",")+1);


			//",characterName:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)characterName = t;
				s = s.substring(s.indexOf('`')+1);
			}

			//",characterAppearance:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)characterAppearance = t;
				s = s.substring(s.indexOf('`')+1);
			}

			//",accountRank:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)try{accountRank = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf('`')+1);
			}

			//",accountCreatedTime:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)try{accountCreatedTime = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf('`')+1);
			}

			//",timesLoggedIn:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)try{timesLoggedIn = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf('`')+1);
			}

			//",totalTimePlayed:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)try{totalTimePlayed = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf('`')+1);
			}

			//",postalCode:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)postalCode = t;
				s = s.substring(s.indexOf('`')+1);
			}

			//",countryName:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)countryName = t;
				s = s.substring(s.indexOf('`')+1);
			}

			//",isoCountryCode:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)isoCountryCode = t;
				s = s.substring(s.indexOf('`')+1);
			}

			//",placeName:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)placeName = t;
				s = s.substring(s.indexOf('`')+1);
			}

			//",stateName:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)stateName = t;
				s = s.substring(s.indexOf('`')+1);
			}

			//",lat:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)try{lat = Float.parseFloat(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf('`')+1);
			}

			//",lon:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)try{lon = Float.parseFloat(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf('`')+1);
			}


			//",miniGamesTimesPlayed:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)try{miniGamesTimesPlayed = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf('`')+1);
			}

			//",miniGamesTimesBattled:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)try{miniGamesTimesBattled = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf('`')+1);
			}

			//",miniGamesTimesChallenged:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)try{miniGamesTimesChallenged = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf('`')+1);
			}

			//",miniGamesTimesChallenger:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)try{miniGamesTimesChallenger = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf('`')+1);
			}

			//",miniGamesTimesWon:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)try{miniGamesTimesWon = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf('`')+1);
			}

			//",miniGamesTimesLost:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)try{miniGamesTimesLost = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf('`')+1);
			}

			//",miniGamesTimesTied:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)try{miniGamesTimesTied = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf('`')+1);
			}


			if(friendType==ZIP_TYPE)return;



			//",facebookID:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)facebookID = t;
				s = s.substring(s.indexOf('`')+1);
			}

			//",facebookEmail:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)facebookEmail = t;
				s = s.substring(s.indexOf('`')+1);
			}

//			//",facebookBirthday:"+
//			{
//				s = s.substring(s.indexOf('`')+1);
//				String t = s.substring(0, s.indexOf('`'));
//				if(t.length()>0)facebookBirthday = t;
//				s = s.substring(s.indexOf('`')+1);
//			}

			//",facebookFirstName:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)facebookFirstName = t;
				s = s.substring(s.indexOf('`')+1);
			}

			//",facebookLastName:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)facebookLastName = t;
				s = s.substring(s.indexOf('`')+1);
			}

			//",facebookGender:"+
			{
				s = s.substring(s.indexOf('`')+1);
				String t = s.substring(0, s.indexOf('`'));
				if(t.length()>0)facebookGender = t;
				s = s.substring(s.indexOf('`')+1);
			}

//			//",facebookLocale:"+
//			{
//				s = s.substring(s.indexOf('`')+1);
//				String t = s.substring(0, s.indexOf('`'));
//				if(t.length()>0)facebookLocale = t;
//				s = s.substring(s.indexOf('`')+1);
//			}
//
//			//",facebookTimeZone:"+
//			{
//				s = s.substring(s.indexOf('`')+1);
//				String t = s.substring(0, s.indexOf('`'));
//				if(t.length()>0)try{facebookTimeZone = Float.parseFloat(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
//				s = s.substring(s.indexOf('`')+1);
//			}
//
//			//",facebookUsername:"+
//			{
//				s = s.substring(s.indexOf('`')+1);
//				String t = s.substring(0, s.indexOf('`'));
//				if(t.length()>0)facebookUsername = t;
//				s = s.substring(s.indexOf('`')+1);
//			}
//
//			//",facebookWebsite:"+
//			{
//				s = s.substring(s.indexOf('`')+1);
//				String t = s.substring(0, s.indexOf('`'));
//				if(t.length()>0)facebookWebsite = t;
//				s = s.substring(s.indexOf('`')+1);
//			}
//
//			//",googlePlusID:"+
//			{
//				s = s.substring(s.indexOf('`')+1);
//				String t = s.substring(0, s.indexOf('`'));
//				if(t.length()>0)googlePlusID = t;
//				s = s.substring(s.indexOf('`')+1);
//			}


		}



	}



















}
