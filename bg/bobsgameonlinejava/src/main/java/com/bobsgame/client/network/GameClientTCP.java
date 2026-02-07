package com.bobsgame.client.network;

import java.net.ConnectException;
import java.net.InetSocketAddress;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import io.netty.bootstrap.Bootstrap;
import io.netty.channel.Channel;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelPipeline;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.EventLoopGroup;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.SocketChannel;
import io.netty.channel.socket.nio.NioSocketChannel;
import io.netty.handler.codec.DelimiterBasedFrameDecoder;
import io.netty.handler.codec.Delimiters;
import io.netty.handler.codec.string.StringDecoder;
import io.netty.handler.codec.string.StringEncoder;
import io.netty.handler.timeout.ReadTimeoutException;
import io.netty.channel.SimpleChannelInboundHandler;

import org.slf4j.LoggerFactory;
import ch.qos.logback.classic.Logger;

import com.bobsgame.ClientMain;
import com.bobsgame.client.console.Console;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.entity.Sprite;
import com.bobsgame.client.engine.event.Dialogue;
import com.bobsgame.client.engine.event.Event;
import com.bobsgame.client.engine.event.Flag;
import com.bobsgame.client.engine.event.GameString;
import com.bobsgame.client.engine.event.ServerObject;
import com.bobsgame.client.engine.event.Skill;
import com.bobsgame.client.engine.game.FriendCharacter;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.client.engine.map.Map;
import com.bobsgame.client.engine.sound.Music;
import com.bobsgame.client.engine.sound.Sound;
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

//=========================================================================================================================
public class GameClientTCP extends EnginePart
{//=========================================================================================================================

	private static Bootstrap clientBootstrap;
	private static ChannelFuture channelFuture;
    private static EventLoopGroup workerGroup;

	//Timer timer;

	public static Logger log = (Logger)LoggerFactory.getLogger(GameClientTCP.class);


	//=========================================================================================================================
	public GameClientTCP(ClientGameEngine g)
	{//=========================================================================================================================

		super(g);

	}


	public void send(String msg) {
		if (channelFuture != null && channelFuture.channel() != null && channelFuture.channel().isActive()) {
			write(channelFuture.channel(), msg);
		}
	}

	//===============================================================================================
	public void initBootstrap()
	{//===============================================================================================


		//Initialize the timer that schedules subsequent reconnection attempts.
		//timer = new HashedWheelTimer();

		//Configure the client.
        workerGroup = new NioEventLoopGroup();
		clientBootstrap = new Bootstrap();
        clientBootstrap.group(workerGroup);
        clientBootstrap.channel(NioSocketChannel.class);
        clientBootstrap.handler(new ChannelInitializer<SocketChannel>() {
            @Override
            public void initChannel(SocketChannel ch) throws Exception {
                ChannelPipeline pipeline = ch.pipeline();
                pipeline.addLast("framer", new DelimiterBasedFrameDecoder(65536, Delimiters.lineDelimiter()));
                pipeline.addLast("decoder", new StringDecoder());
                pipeline.addLast("encoder", new StringEncoder());
                pipeline.addLast("handler", new BobsGameClientHandler());
            }
        });

		//clientBootstrap.setOption("sendBufferSize", 65536);
		//clientBootstrap.setOption("receiveBufferSize", 65536);
		//clientBootstrap.setOption("receiveBufferSizePredictorFactory", new AdaptiveReceiveBufferSizePredictorFactory());

		//clientBootstrap.setOption("tcpNoDelay", true);
		//clientBootstrap.setOption("keepAlive", true);

		//clientBootstrap.setOption("remoteAddress", new InetSocketAddress(ClientMain.serverAddress, BobNet.serverTCPPort));

	}




	//===============================================================================================
	public class BobsGameClientHandler extends SimpleChannelInboundHandler<String>
	{//===============================================================================================

		//===============================================================================================
		public BobsGameClientHandler()
		{//===============================================================================================
			super();

		}

		//===============================================================================================
		@Override
		public void channelInactive(ChannelHandlerContext ctx) throws Exception
		{//===============================================================================================

			log.warn("channelDisconnected from Server: ChannelID: "+ctx.channel().id());

			Console.add("Disconnected from Server.", BobColor.red, 5000);

			setConnectedToServer_S(false);
			setNotAuthorizedOnServer();
			setServerIPAddress_S(null);
		}

		//===============================================================================================
		@Override
		public void channelActive(ChannelHandlerContext ctx) throws Exception
		{//===============================================================================================

			log.info("channelConnected to Server: ChannelID: "+ctx.channel().id());
			Console.add("Connected to Server!", BobColor.green, 5000);

		}


		//===============================================================================================
		@Override
		public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause)
		{//===============================================================================================
			if(cause instanceof ConnectException)
			{
				log.error("Exception caught connecting to Server - ConnectException: "+cause.getMessage());
			}
			else
			if(cause instanceof ReadTimeoutException)
			{
				log.error("Exception caught connecting to Server - ReadTimeoutException: "+cause.getMessage());
			}
			else
			{
				log.error("Unexpected Exception caught connecting to Server: "+cause.getMessage());
				cause.printStackTrace();
			}

			ctx.close();
		}


		//===============================================================================================
		@Override
		public void channelRead0(ChannelHandlerContext ctx, String s) throws Exception
		{//===============================================================================================
			//Print out the line received from the server.

			try{Thread.currentThread().setName("ClientTCP_BobsGameClientHandler");}catch(SecurityException ex){ex.printStackTrace();}

			if(BobNet.debugMode)
			{
				log.warn("FROM SERVER: cID:"+ctx.channel().id()+" | "+s);
			}


			if(s.startsWith("ping"))
			{
				//log.debug("SERVER: ping");
				write(ctx.channel(),"pong"+BobNet.endline);
				return;
			}


			if(s.startsWith(BobNet.Server_IP_Address_Response)){incomingServerIPAddressResponse(s);return;}

			if(s.startsWith(BobNet.Login_Response)){incomingLoginResponse(s);return;}
			if(s.startsWith(BobNet.Facebook_Login_Response)){incomingFacebookCreateAccountOrLoginResponse(s);return;}
			if(s.startsWith(BobNet.Reconnect_Response)){incomingReconnectResponse(s);return;}
			if(s.startsWith(BobNet.Tell_Client_Their_Session_Was_Logged_On_Somewhere_Else)){incomingSessionWasLoggedOnSomewhereElse(s);return;}
			if(s.startsWith(BobNet.Tell_Client_Servers_Are_Shutting_Down)){incomingServersAreShuttingDown(s);return;}
			if(s.startsWith(BobNet.Tell_Client_Servers_Have_Shut_Down)){incomingServersHaveShutDown(s);return;}

			if(s.startsWith(BobNet.Password_Recovery_Response)){incomingPasswordRecoveryResponse(s);return;}
			if(s.startsWith(BobNet.Create_Account_Response)){incomingCreateAccountResponse(s);return;}


			if(s.startsWith(BobNet.Sprite_Response)){incomingSpriteData(s);return;}
			if(s.startsWith(BobNet.Map_Response)){incomingMapData(s);return;}

			if(s.startsWith(BobNet.Initial_GameSave_Response)){incomingInitialGameSaveResponse(s);return;}
			if(s.startsWith(BobNet.Encrypted_GameSave_Update_Response)){incomingGameSaveUpdateResponse(s);return;}

			if(s.startsWith(BobNet.Load_Event_Response)){incomingLoadEventResponse(s);return;}


			if(s.startsWith(BobNet.Dialogue_Response)){incomingDialogue(s);return;}
			if(s.startsWith(BobNet.Flag_Response)){incomingFlag(s);return;}
			if(s.startsWith(BobNet.Skill_Response)){incomingSkill(s);return;}
			if(s.startsWith(BobNet.Event_Response)){incomingEvent(s);return;}
			if(s.startsWith(BobNet.GameString_Response)){incomingGameString(s);return;}
			if(s.startsWith(BobNet.Music_Response)){incomingMusic(s);return;}
			if(s.startsWith(BobNet.Sound_Response)){incomingSound(s);return;}



			if(s.startsWith(BobNet.Update_Facebook_Account_In_DB_Response)){incomingUpdateFacebookAccountInDBResponse(s);return;}
			if(s.startsWith(BobNet.Online_Friends_List_Response)){incomingOnlineFriendsListResponse(s);return;}
			if(s.startsWith(BobNet.Chat_Message)){incomingChatMessage(s);return;}
			if(s.startsWith(BobNet.Friend_Is_Online_Notification)){incomingFriendOnlineNotification(s);return;}

            if(s.startsWith(BobNet.Bobs_Game_RoomList_Response)){incomingOKGameRoomListResponse(s);return;}

			if(s.startsWith(BobNet.Bobs_Game_Frame_Packet)){incomingFramePacket(s);return;}

		}

	}







	//===============================================================================================
	public ChannelFuture write(Channel c, String s)
	{//===============================================================================================

		if(s.endsWith(BobNet.endline)==false)
		{
			log.error("Message doesn't end with endline");
			s = s +BobNet.endline;
		}


		if(BobNet.debugMode)
		{
			log.debug("SEND SERVER: cID:"+c.id()+" | "+s.substring(0,s.length()-2));
		}


		ChannelFuture cf = c.writeAndFlush(s);

		return cf;
	}





















	//=========================================================================================================================
	public void cleanup()
	{//=========================================================================================================================


		serverCommandExecutorService.shutdownNow();


		// Close the connection. Make sure the close operation ends because
		// all I/O operations are asynchronous in Netty.
		if(getChannel_S()!=null)
		{

			Channel c = getChannel_S();

			if(c.isActive()||c.isOpen())
			{
				try
				{
					c.close().sync();
				}
				catch(InterruptedException e)
				{
					e.printStackTrace();
				}
			}

		}


		if(workerGroup!=null)workerGroup.shutdownGracefully();

		//timer.stop();



	}











































	private void setNotAuthorizedOnServer()
	{
		setLoginResponse_S(false,false);//may have to reinitialize if we connect to a different server
		setReconnectResponse_S(false,false);

	}

	public boolean getAuthorizedOnServer()
	{
		if(getWasLoginResponseValid_S()==true || getWasReconnectResponseValid_S()==true)return true;
		return false;
	}




	private Channel _channel;
	synchronized private void setChannel_S(Channel c)
	{
		_channel = c;
	}
	synchronized private Channel getChannel_S()
	{
		return _channel;
	}
	synchronized public ChannelFuture writeToChannel_S(String s)
	{
		return write(getChannel_S(),s);
	}


	private boolean _connectedToServer = false;//synchronized
	synchronized private void setConnectedToServer_S(boolean b)
	{
		_connectedToServer = b;
	}
	synchronized public boolean getConnectedToServer_S()
	{
		return _connectedToServer;
	}




	private InetSocketAddress _serverAddress = null;
	private synchronized InetSocketAddress getServerIPAddress_S()
	{
		return _serverAddress;
	}
	private synchronized void setServerIPAddress_S(String ipAddressString)
	{
		if(ipAddressString==null || ipAddressString.length()==0)_serverAddress=null;
		else _serverAddress = new InetSocketAddress(ipAddressString, BobNet.serverTCPPort);
	}






	//TODO: maybe should have BobNet.getServerAddress or something that returns release or debug depending on flags. could also detect local?

	private InetSocketAddress loadBalancerAddress = new InetSocketAddress(ClientMain.serverAddress, BobNet.serverTCPPort);

	ExecutorService serverCommandExecutorService = Executors.newFixedThreadPool(1);



	//=========================================================================================================================
	private void ensureConnectedToServerThreadBlock()
	{//=========================================================================================================================

		while(getConnectedToServer_S()==false && ClientMain.clientMain.exit==false)
		{

			log.debug("ensureConnectedToServerThreadBlock() Not connected to server. Trying...");

			//if we dont have a server ip address, connect to the load balancer
			while(getServerIPAddress_S()==null)
			{
				log.debug("ensureConnectedToServerThreadBlock() Don't have server IP. Connecting through LB...");


				try
				{
					Channel c = getChannel_S();
					if(c!=null)c.close().sync();
				}
				catch(InterruptedException e1)
				{
					e1.printStackTrace();
					return;
				}

				if(workerGroup!=null)workerGroup.shutdownGracefully();

				initBootstrap();

				channelFuture = clientBootstrap.connect(loadBalancerAddress);


				//wait for load balancer to respond (we are connected to a server)
				boolean connected=false;
				while(connected==false)
				{
					try
					{
						channelFuture.sync();
						connected=true;
					}
					catch(InterruptedException e){log.error("InterruptedException while connecting to Load Balancer. "+e.getMessage());return;}
				}

				setChannel_S(channelFuture.channel());


				//when connected to load balancer, send getServerIPCommand to get the servers real IP behind the load balancer
				ChannelFuture c = writeToChannel_S(BobNet.Server_IP_Address_Request+BobNet.endline);

				connected=false;
				while(connected==false)
				{
					try
					{
						c.sync();
						connected=true;
					}
					catch(InterruptedException e){log.error("InterruptedException while sending GetIP to Server behind LB. "+e.getMessage());return;}
				}

				//wait for server to return IP in message response (handled elsewhere)
				//message response will set server IP which will break out of the loop or try again with a new server

				for(int i=0;i<5;i++)
				{
					try
					{
						Thread.sleep(1000);
					}
					catch(InterruptedException e)
					{
						e.printStackTrace();
						return;
					}
					if(getServerIPAddress_S()!=null)break;
				}

				//if we have server IP here we will break out of the while loop and continue.
				//otherwise we try again by connecting to the LB again and get a new server.
			}



			//disconnecting from the LB will set the address to null again, so we store it.
			InetSocketAddress serverIP = getServerIPAddress_S();


			//close the connection to the load balancer
			try
			{
				Channel c = getChannel_S();
				if(c!=null)c.close().sync();
			}
			catch(InterruptedException e1)
			{
				e1.printStackTrace();
				return;
			}

			if(workerGroup!=null)workerGroup.shutdownGracefully();

			initBootstrap();

			//connect to the server
			channelFuture = clientBootstrap.connect(serverIP);

			//wait for the server to open the channel
			boolean connected=false;
			while(connected==false)
			{
				try
				{
					channelFuture.sync();
					connected=true;
				}
				catch(InterruptedException e){log.error("InterruptedException while connecting to Server. "+e.getMessage());return;}
			}
			setChannel_S(channelFuture.channel());



			setConnectedToServer_S(true);

		}
	}

	//=========================================================================================================================
	private void ensureAuthorizedOnServerThreadBlock()
	{//=========================================================================================================================

		while(getAuthorizedOnServer()==false && ClientMain.clientMain.exit==false)
		{

			if(getUserID_S()!=-1)//we have a userID set, we must have dropped the connection. reconnect.
			{

				//send reconnect request

				//wait for server to authorize our credentials

				//set got reconnect response

				//set session authorized

				//write immediately in this thread, don't create another thread, because the queue is already blocking on this one!
				writeToChannel_S(BobNet.Reconnect_Request+"`"+getUserID_S()+"`,`"+getSessionToken_S()+"`"+BobNet.endline);


			}
			else
			{
				//we haven't successfully logged in yet.
				log.warn("Thread is waiting to authorize on Server before we have logged in.");
			}

			try
			{
				Thread.sleep(1000);
			}
			catch(InterruptedException e)
			{
				e.printStackTrace();
				return;
			}

			log.warn("Thread is waiting to authorize on Server.");

		}

	}


	//=========================================================================================================================
	private void incomingServerIPAddressResponse(String s)
	{//=========================================================================================================================

		//ServerIP:ip
		s = s.substring(s.indexOf(":")+1);//ip
		setServerIPAddress_S(s);
	}


	//when this goes bad, cant reconnect, get a new one from the load balancer.

	//when i connect to a server, it checks its hashtable and determines whether i am registered there right now.

	//if not, it grabs my last encryption key from the database and proceeds as usual.

	//as a client, if i have a sessionToken set, i am good to go.
	//otherwise, do login to get a sessionToken.

	//just send the sessionToken to the new server i connect to.
	//if i need an initialGameState, get it.

	//if i already have a gameState, just proceed normally, auth with the sessionToken to register with the server




	//yeah, should pause the game on every channel.write, put transparency over screen and say waiting to reconnect to server
	//this should be very infrequent and it will allow for reconnecting to a different server.

	//nD should be on a different thread, so minigames can keep going




	//=========================================================================================================================
	public void connectToServer()
	{//=========================================================================================================================

		serverCommandExecutorService.execute
		(
			new Runnable()
			{
				public void run()
				{
					try{Thread.currentThread().setName("ClientTCP_connectToServer");}catch(SecurityException e){e.printStackTrace();}
					//log.debug("connectToServer() Start");
					ensureConnectedToServerThreadBlock();
					//log.debug("connectToServer() Success");
				}
			}
		);

	}



	//=========================================================================================================================
	public void connectAndWriteToChannelBeforeAuthorization(final String s)
	{//=========================================================================================================================

		serverCommandExecutorService.execute
		(
			new Runnable()
			{
				public void run()
				{

					try{Thread.currentThread().setName("ClientTCP_connectAndWriteToChannelBeforeAuthorization");}catch(SecurityException e){e.printStackTrace();}
					//log.debug("connectAndWriteToChannelBeforeAuthorization() Start");
					ensureConnectedToServerThreadBlock();
					//log.debug("connectAndWriteToChannelBeforeAuthorization() Success");
					writeToChannel_S(s);

				}
			}
		);

	}


	//=========================================================================================================================
	public void connectAndAuthorizeAndWriteToChannel(final String s)
	{//=========================================================================================================================


		if(ClientMain.previewClientInEditor || ClientMain.introMode)
		{
			log.debug("Blocked writing to network: "+s);
			return;
		}

		//new Exception().printStackTrace();

		serverCommandExecutorService.execute
		(
			new Runnable()
			{
				public void run()
				{
					try{Thread.currentThread().setName("ClientTCP_connectAndAuthorizeAndWriteToChannel");}catch(SecurityException e){e.printStackTrace();}
					//log.debug("connectAndAuthorizeAndWriteToChannel() Start : "+s);
					ensureConnectedToServerThreadBlock();
					ensureAuthorizedOnServerThreadBlock();
					//log.debug("connectAndAuthorizeAndWriteToChannel() Success : "+s);

					writeToChannel_S(s);

				}
			}
		);

	}












	//=========================================================================================================================
	//LOGIN
	//=========================================================================================================================

	private boolean gotLoginResponse_S = false;//synchronized
	private boolean loginWasValid_S = false;//synchronized

	private boolean gotReconnectResponse_S = false;//synchronized
	private boolean reconnectWasValid_S = false;//synchronized

	private int _userID = -1;//synchronized
	private String _sessionToken = "";//synchronized

	private boolean statsAllowed = false;

	//=========================================================================================================================
	synchronized public void setLoginResponse_S(boolean gotReponse, boolean wasValid)
	{//=========================================================================================================================
		gotLoginResponse_S = gotReponse;
		loginWasValid_S = wasValid;

	}

	//=========================================================================================================================
	synchronized public void setGotLoginResponse_S(boolean b)
	{//=========================================================================================================================
		gotLoginResponse_S = b;
	}

	//=========================================================================================================================
	synchronized public boolean getGotLoginResponse_S()
	{//=========================================================================================================================
		return gotLoginResponse_S;
	}

	//=========================================================================================================================
	synchronized public boolean getWasLoginResponseValid_S()
	{//=========================================================================================================================
		return loginWasValid_S;
	}

	//=========================================================================================================================
	synchronized public void setReconnectResponse_S(boolean gotReponse, boolean wasValid)
	{//=========================================================================================================================
		gotReconnectResponse_S = gotReponse;
		reconnectWasValid_S = wasValid;

	}
	//=========================================================================================================================
	synchronized public void setGotReconnectResponse_S(boolean b)
	{//=========================================================================================================================
		gotReconnectResponse_S = b;
	}
	//=========================================================================================================================
	synchronized public boolean getGotReconnectResponse_S()
	{//=========================================================================================================================
		return gotReconnectResponse_S;
	}

	//=========================================================================================================================
	synchronized public boolean getWasReconnectResponseValid_S()
	{//=========================================================================================================================
		return reconnectWasValid_S;
	}
	//=========================================================================================================================
	public void sendLoginRequest(String email, String password, boolean stats)
	{//=========================================================================================================================

		statsAllowed = stats;

		String message = "";

		if(stats==false)
		{
			message = BobNet.Login_Request+"`"+email+"`,`"+password+"`"+BobNet.endline;
		}
		else
		{
			//send session info
			String clientInfoString = ClientMain.clientMain.clientInfo.encode();
			message = BobNet.Login_Request+"`"+email+"`,`"+password+"`,"+clientInfoString+BobNet.endline;
		}

		connectAndWriteToChannelBeforeAuthorization(message);
	}

	//=========================================================================================================================
	public void sendReconnectRequest(int userID, String sessionToken, boolean stats)
	{//=========================================================================================================================

		statsAllowed = stats;//just used if we need to reconnect

		String message = "";

		if(stats==false)
		{
			message = BobNet.Reconnect_Request+"`"+userID+"`,`"+sessionToken+"`"+BobNet.endline;
		}
		else
		{
			//send session info
			String clientInfoString = ClientMain.clientMain.clientInfo.encode();

			message = BobNet.Reconnect_Request+"`"+userID+"`,`"+sessionToken+"`,"+clientInfoString+BobNet.endline;
		}

		connectAndWriteToChannelBeforeAuthorization(message);

	}

	//=========================================================================================================================
	private void incomingLoginResponse(String s)
	{//=========================================================================================================================

		//LoginResponse:Failed
		//LoginResponse:Success,userID,`sessionToken`
		s = s.substring(s.indexOf(":")+1);//Success,userID,`sessionToken`

		if(s.startsWith("Success")==false)
		{
			setLoginResponse_S(true, false);
		}
		else
		{
			setLoginResponse_S(true, true);

			//server sends back userID and sessionToken, need to store these
			s = s.substring(s.indexOf(",")+1);//userID,`sessionToken`
			int userID = -1;
			try{userID = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf("`")+1);//sessionToken`
			String sessionToken = s.substring(0,s.indexOf("`"));

			setUserID_S(userID);
			setSessionToken_S(sessionToken);
		}
	}

	//=========================================================================================================================
	private void incomingReconnectResponse(String s)
	{//=========================================================================================================================

		//ReconnectResponse:Failed
		//ReconnectResponse:Success,userID,`sessionToken`
		s = s.substring(s.indexOf(":")+1);//Success,userID,`sessionToken`

		if(s.startsWith("Success")==false)
		{
			setReconnectResponse_S(true, false);

		}
		else
		{
			setReconnectResponse_S(true, true);

			//server sends back userID and sessionToken, need to store these
			s = s.substring(s.indexOf(",")+1);//userID,`sessionToken`
			int userID = -1;
			try{userID = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf("`")+1);//sessionToken`
			String sessionToken = s.substring(0,s.indexOf("`"));

			setUserID_S(userID);
			setSessionToken_S(sessionToken);
		}
	}

	//=========================================================================================================================
	synchronized public void setUserID_S(int i)
	{//=========================================================================================================================
		_userID = i;
	}

	//=========================================================================================================================
	synchronized public void setSessionToken_S(String s)
	{//=========================================================================================================================
		_sessionToken = s;
	}

	//=========================================================================================================================
	synchronized public int getUserID_S()
	{//=========================================================================================================================
		return _userID;
	}
	//=========================================================================================================================
	synchronized public String getSessionToken_S()
	{//=========================================================================================================================
		return _sessionToken;
	}

	//=========================================================================================================================
	private void incomingSessionWasLoggedOnSomewhereElse(String s)
	{//=========================================================================================================================

		//TellClientTheirSessionWasLoggedOnSomewhereElse

		//setUserID_S(-1);
		//setSessionToken_S("");

		ClientMain.clientMain.stateManager.setState(ClientMain.clientMain.loggedOutState);

	}

	//=========================================================================================================================
	private void incomingServersAreShuttingDown(String s)
	{//=========================================================================================================================

		ClientMain.clientMain.serversAreShuttingDown=true;

	}

	//=========================================================================================================================
	private void incomingServersHaveShutDown(String s)
	{//=========================================================================================================================

		ClientMain.clientMain.stateManager.setState(ClientMain.clientMain.serversHaveShutDownState);

	}


















	private boolean gotFacebookLoginResponse_S = false;//synchronized
	private boolean facebookLoginWasValid_S = false;//synchronized

	//=========================================================================================================================
	synchronized public void setFacebookLoginResponse_S(boolean gotReponse, boolean wasValid)
	{//=========================================================================================================================
		gotFacebookLoginResponse_S = gotReponse;
		facebookLoginWasValid_S = wasValid;

	}

	//=========================================================================================================================
	synchronized public void setGotFacebookLoginResponse_S(boolean b)
	{//=========================================================================================================================
		gotFacebookLoginResponse_S = b;
	}

	//=========================================================================================================================
	synchronized public boolean getGotFacebookLoginResponse_S()
	{//=========================================================================================================================
		return gotFacebookLoginResponse_S;
	}

	//=========================================================================================================================
	synchronized public boolean getWasFacebookLoginResponseValid_S()
	{//=========================================================================================================================
		return facebookLoginWasValid_S;
	}
	//=========================================================================================================================
	public void sendFacebookLoginCreateAccountIfNotExist(String facebookID, String accessToken, boolean stats)
	{//=========================================================================================================================
		statsAllowed = stats;

		String message = "";

		if(stats==false)
		{
			message = BobNet.Facebook_Login_Request+"`"+facebookID+"`,`"+accessToken+"`"+BobNet.endline;
		}
		else
		{
			//send session info
			String clientInfoString = ClientMain.clientMain.clientInfo.encode();
			message = BobNet.Facebook_Login_Request+"`"+facebookID+"`,`"+accessToken+"`,"+clientInfoString+BobNet.endline;
		}

		connectAndWriteToChannelBeforeAuthorization(message);

	}
	//=========================================================================================================================
	private void incomingFacebookCreateAccountOrLoginResponse(String s)
	{//=========================================================================================================================

		//FacebookLoginResponse:Failed
		//FacebookLoginResponse:Success,userID,`sessionToken`
		s = s.substring(s.indexOf(":")+1);//Success,userID,`sessionToken`

		if(s.startsWith("Success")==false)
		{
			setFacebookLoginResponse_S(true, false);
		}
		else
		{
			setFacebookLoginResponse_S(true, true);

			//server sends back userID and sessionToken, need to store these
			s = s.substring(s.indexOf(",")+1);//userID,`sessionToken`
			int userID = -1;
			try{userID = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf("`")+1);//sessionToken`
			String sessionToken = s.substring(0,s.indexOf("`"));

			setUserID_S(userID);
			setSessionToken_S(sessionToken);
		}
	}









	//=========================================================================================================================
	//CREATE ACCOUNT
	//=========================================================================================================================

	public boolean _gotCreateAccountResponse = false;//synchronized

	synchronized public void setGotCreateAccountResponse_S(boolean b)
	{
		_gotCreateAccountResponse = b;
	}
	synchronized public boolean getGotCreateAccountResponse_S()
	{
		return _gotCreateAccountResponse;
	}

	//=========================================================================================================================
	public void sendCreateAccountRequest(String email, String password)
	{//=========================================================================================================================

		connectAndWriteToChannelBeforeAuthorization(BobNet.Create_Account_Request+"`"+email+"`,`"+password+"`"+BobNet.endline);
	}


	//=========================================================================================================================
	private void incomingCreateAccountResponse(String s)
	{//=========================================================================================================================

		//s = s.substring(s.indexOf(":")+1);

		//it doesn't matter what the response was, we should not provide any information otherwise they can determine whether the email is signed up.
		//so we just say "ok we tried to make an account, check your email"

		setGotCreateAccountResponse_S(true);

	}















	//=========================================================================================================================
	//PASSWORD RECOVERY
	//=========================================================================================================================

	public boolean _gotPasswordRecoveryResponse = false;//synchronized

	synchronized public void setGotPasswordRecoveryResponse_S(boolean b)
	{
		_gotPasswordRecoveryResponse = b;
	}
	synchronized public boolean getGotPasswordRecoveryResponse_S()
	{
		return _gotPasswordRecoveryResponse;
	}


	//=========================================================================================================================
	public void sendPasswordRecoveryRequest(String email)
	{//=========================================================================================================================

		connectAndWriteToChannelBeforeAuthorization(BobNet.Password_Recovery_Request+"`"+email+"`"+BobNet.endline);
	}


	//=========================================================================================================================
	private void incomingPasswordRecoveryResponse(String s)
	{//=========================================================================================================================


		//s = s.substring(s.indexOf(":")+1);

		setGotPasswordRecoveryResponse_S(true);

	}




























	//=========================================================================================================================
	//GAME SAVE UPDATES
	//=========================================================================================================================

	//=========================================================================================================================
	//INITIAL GAME SAVE
	//=========================================================================================================================


	long lastInitialGameSaveRequestTime = 0;

	//=========================================================================================================================
	public void sendInitialGameSaveRequest()
	{//=========================================================================================================================
		//the game should wait until this is received.
		//it should also get an encrypted game save.

		//needs to resend this request every 3 seconds

		long time = System.currentTimeMillis();
		if(time-lastInitialGameSaveRequestTime>3000)
		{
			lastInitialGameSaveRequestTime=time;
			connectAndAuthorizeAndWriteToChannel(BobNet.Initial_GameSave_Request+BobNet.endline);
		}

	}

	//=========================================================================================================================
	private void incomingInitialGameSaveResponse(String s)
	{//=========================================================================================================================
		//parse off all values, initialize engine
		//parse off flagsSet,dialoguesDone,skillValues

		//parse gamesave



		//InitialGameSave:userID:`1`,thing:`thing`,,etc.
		String gameSaveString = s.substring(s.indexOf(":")+1);

		GameSave g = new GameSave();
		g.decodeGameSave(gameSaveString);

		ClientGameEngine().setGameSave_S(g);

		ClientGameEngine().initializeGameFromSave_S();

		ClientGameEngine().setInitialGameSaveReceived_S(true);

	}


	//each game save needs to have an ID so we know for sure which one is being replied to.
	//=========================================================================================================================
	public class GameSaveUpdateRequest
	{//=========================================================================================================================

		public String requestString = "";
		public int id = -1;
		public long timeLastSent=0;
		public boolean sent = false;

		//=========================================================================================================================
		public GameSaveUpdateRequest(String request, int id)
		{//=========================================================================================================================
			this.requestString = request;
			this.id = id;
		}
	}

	private int _requestCounter = 0;//synchronized
	private String _encryptedGameSave = "";//synchronized
	private ArrayList<GameSaveUpdateRequest> _gameSaveUpdateRequestQueue = new ArrayList<GameSaveUpdateRequest>(); //synchronized

	//================================================================
	synchronized public GameSaveUpdateRequest getQueuedGameSaveUpdateRequest_S(int i)
	{//================================================================

		int size = _gameSaveUpdateRequestQueue.size();

		if(i>=size)return null;


		return _gameSaveUpdateRequestQueue.get(i);

	}

	//================================================================
	synchronized public void addQueuedGameSaveUpdateRequest_S(String value)
	{//================================================================

		//all game save updates should be instantly queued
		//any changes to the game save should happen instantly on the client

		GameSaveUpdateRequest g = new GameSaveUpdateRequest(value,_requestCounter);

		_gameSaveUpdateRequestQueue.add(g);

		_requestCounter++;


	}

	//================================================================
	synchronized public void removeQueuedGameSaveUpdateRequestByID_S(int id)
	{//================================================================

		int size = _gameSaveUpdateRequestQueue.size();

		for(int i=0;i<size;i++)
		{
			if(_gameSaveUpdateRequestQueue.get(i).id==id)
			{
				_gameSaveUpdateRequestQueue.remove(i);
				i=size;
				break;
			}
		}
	}

	synchronized public String getEncryptedGameSave_S()
	{
		return _encryptedGameSave;
	}
	synchronized public void setEncryptedGameSave_S(String s)
	{
		_encryptedGameSave = s;
	}

	//=========================================================================================================================
	public void sendQueuedGameSaveUpdates()
	{//=========================================================================================================================

		//keep resending the same game update request every few seconds until we have a definite reply.
		GameSaveUpdateRequest g = getQueuedGameSaveUpdateRequest_S(0);

		if(g!=null)
		{
			if(g.sent==true)
			{
				long time = System.currentTimeMillis();
				if(time-g.timeLastSent>3000)
				{
					g.timeLastSent=time;
					connectAndAuthorizeAndWriteToChannel(BobNet.Encrypted_GameSave_Update_Request+g.id+","+g.requestString+",gameSave:"+getEncryptedGameSave_S()+BobNet.endline);

					log.info("Sent Game Save Update Request:"+g.id);
				}
			}
			else
			{
				//GameSaveUpdateRequest:14,flagsSet:`3`,gameSave
				connectAndAuthorizeAndWriteToChannel(BobNet.Encrypted_GameSave_Update_Request+g.id+","+g.requestString+",gameSave:"+getEncryptedGameSave_S()+BobNet.endline);
				g.sent=true;

				log.info("Sent Game Save Update Request:"+g.id);
			}
		}
	}





	//=========================================================================================================================
	private void incomingGameSaveUpdateResponse(String s)
	{//=========================================================================================================================



		//EncryptedGameSave:id,blob
		s = s.substring(s.indexOf(":")+1);//id,blob
		int gameSaveID = -1;
		try{gameSaveID = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
		s = s.substring(s.indexOf(",")+1);//blob
		String encryptedGameSave = s;

		log.info("Received Encrypted Game Save:"+gameSaveID);

		//store encrypted gameSave
		setEncryptedGameSave_S(encryptedGameSave);

		//parse off ID, remove from queue
		removeQueuedGameSaveUpdateRequestByID_S(gameSaveID);

	}







	//=========================================================================================================================
	//FACEBOOK TRASH
	//=========================================================================================================================




	boolean _gotFacebookAccountUpdateResponse = false;//synchronized
	boolean _facebookAccountUpdateResponseWasValid = false;//synchronized

	synchronized public void setGotFacebookAccountUpdateResponse_S(boolean b)
	{
		_gotFacebookAccountUpdateResponse = b;
	}
	synchronized public boolean getFacebookAccountUpdateResponseReceived_S()
	{
		return _gotFacebookAccountUpdateResponse;
	}
	synchronized public void setFacebookAccountUpdateResponseWasValid_S(boolean b)
	{
		_facebookAccountUpdateResponseWasValid = b;
	}
	synchronized public boolean getFacebookAccountUpdateResponseWasValid_S()
	{
		return _facebookAccountUpdateResponseWasValid;
	}
	synchronized public void setFacebookAccountUpdateResponseState_S(boolean gotResponse, boolean wasValid)
	{
		_gotFacebookAccountUpdateResponse = gotResponse;
		_facebookAccountUpdateResponseWasValid = wasValid;
	}

	//=========================================================================================================================
	public void sendUpdateFacebookAccountInDBRequest()
	{//=========================================================================================================================
		connectAndAuthorizeAndWriteToChannel(BobNet.Update_Facebook_Account_In_DB_Request+BobNet.endline);

	}

	//=========================================================================================================================
	private void incomingUpdateFacebookAccountInDBResponse(String s)
	{//=========================================================================================================================
		//UpdateFacebookAccountInDBResponse:Failed
		//UpdateFacebookAccountInDBResponse:Success

		s = s.substring(s.indexOf(":")+1);//Success


		if(s.startsWith("Success")==false)
		{
			setFacebookAccountUpdateResponseState_S(true, false);


//			BobNet.UpdateFacebookAccountInDBResponse+"Success:`"+
//			facebookID+"`,`"+
//			facebookAccessToken+"`,`"+
//			facebookEmail+"`,`"+
//			facebookBirthday+"`,`"+
//			facebookFirstName+"`,`"+
//			facebookLastName+"`,`"+
//			facebookGender+"`,`"+
//			facebookLocale+"`,`"+
//			facebookTimeZone+"`,`"+
//			facebookUsername+"`,`"+
//			facebookWebsite+"`"+

			s = s.substring(s.indexOf("`")+1);
			GameSave().facebookID = s.substring(0,s.indexOf("`"));
			s = s.substring(s.indexOf("`")+3);
			GameSave().facebookAccessToken = s.substring(0,s.indexOf("`"));
			s = s.substring(s.indexOf("`")+3);
			GameSave().facebookEmail = s.substring(0,s.indexOf("`"));
			//s = s.substring(s.indexOf("`")+3);
			//GameSave().facebookBirthday = s.substring(0,s.indexOf("`"));
			s = s.substring(s.indexOf("`")+3);
			GameSave().facebookFirstName = s.substring(0,s.indexOf("`"));
			s = s.substring(s.indexOf("`")+3);
			GameSave().facebookLastName = s.substring(0,s.indexOf("`"));
			s = s.substring(s.indexOf("`")+3);
			GameSave().facebookGender = s.substring(0,s.indexOf("`"));
			//s = s.substring(s.indexOf("`")+3);
			//GameSave().facebookLocale = s.substring(0,s.indexOf("`"));
			//s = s.substring(s.indexOf("`")+3);
			//try{GameSave().facebookTimeZone = Float.parseFloat(s.substring(0,s.indexOf("`")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
			//s = s.substring(s.indexOf("`")+3);
			//GameSave().facebookUsername = s.substring(0,s.indexOf("`"));
			//s = s.substring(s.indexOf("`")+3);
			//GameSave().facebookWebsite = s.substring(0,s.indexOf("`"));


		}
		else
		{
			setFacebookAccountUpdateResponseState_S(true, true);
		}

	}





	//=========================================================================================================================
	public void sendOnlineFriendListRequest()
	{//=========================================================================================================================
		connectAndAuthorizeAndWriteToChannel(BobNet.Online_Friends_List_Request+BobNet.endline);

	}
	//=========================================================================================================================
	private void incomingOnlineFriendsListResponse(String s)
	{//=========================================================================================================================
		//OnlineFriendsListResponse:type:id,type:id
		//type can be fb, g+, t, zip
		s = s.substring(s.indexOf(":")+1);


		//parse each friend, do incomingFriendOnlineNotification for each
		while(s.length()>0)
		{
			int type = 0;
			String typeString = s.substring(0,s.indexOf(":"));
			s = s.substring(s.indexOf(":")+1);
			if(typeString.equals("facebook"))type = FriendCharacter.FACEBOOK_TYPE;

			int friendUserID = -1;
			try{friendUserID = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(",")+1);

			FriendManager().addNewOnlineFriendIfNotExist(friendUserID,type);
		}
	}



	//=========================================================================================================================
	private void incomingChatMessage(String s)
	{
		s = s.substring(s.indexOf(":")+1);
		if(GUIManager()!=null) GUIManager().addChatMessage(s);
	}

	private void incomingFriendOnlineNotification(String s)
	{//=========================================================================================================================

		//FriendOnlineNotification:type:id


		//make a new friendConnection and add it to the friend manager
		//check existing friends to see if userID already exists

		s = s.substring(s.indexOf(":")+1);
		int type = 0;
		String typeString = s.substring(0,s.indexOf(":"));
		s = s.substring(s.indexOf(":")+1);
		if(typeString.equals("facebook"))type = FriendCharacter.FACEBOOK_TYPE;
		int friendUserID = -1;
		try{friendUserID = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}

		FriendManager().addNewOnlineFriendIfNotExist(friendUserID,type);
	}

	private void incomingFramePacket(String s) {
		if (ClientGameEngine() != null && ClientGameEngine().gameLogic != null) {
			ClientGameEngine().gameLogic.incoming_FramePacket(s);
		}
	}

    //=========================================================================================================================
    // ROOM LIST
    //=========================================================================================================================

    private String _okGameRoomListResponse = "";

    public void sendOKGameRoomListRequest_S() {
        connectAndAuthorizeAndWriteToChannel(BobNet.Bobs_Game_RoomList_Request + BobNet.endline);
    }

    private void incomingOKGameRoomListResponse(String s) {
        // Bobs_Game_RoomList_Response:room1:room2...
        s = s.substring(s.indexOf(":")+1);
        synchronized(this) {
            _okGameRoomListResponse = s;
        }
    }

    public synchronized String getAndResetOKGameRoomListResponse_S() {
        String r = _okGameRoomListResponse;
        _okGameRoomListResponse = "";
        return r;
    }








	//====================================================
	//SPRITE
	//====================================================
	//=========================================================================================================================
	public void sendSpriteDataRequestByName(String spriteAssetName)
	{//=========================================================================================================================
		connectAndAuthorizeAndWriteToChannel(BobNet.Sprite_Request_By_Name+spriteAssetName+BobNet.endline);

	}
	//=========================================================================================================================
	public void sendSpriteDataRequestByID(int id)
	{//=========================================================================================================================
		connectAndAuthorizeAndWriteToChannel(BobNet.Sprite_Request_By_ID+id+BobNet.endline);

	}

	//=========================================================================================================================
	private void incomingSpriteData(String s)
	{//=========================================================================================================================

		//Sprite:id-spriteName:spriteData
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(s.indexOf(":")+1);//intentional ::

		SpriteData data = new SpriteData();
		data.initFromString(s);


		if(data==null)
		{
			log.error("Sprite could not be decompressed.");
		}
		else
		{
			Sprite sprite = SpriteManager().spriteByNameHashMap.get(data.name());

			if(sprite==null)
			{
				sprite = new Sprite(Engine());
			}

			sprite.initalizeWithSpriteData(data);

			SpriteManager().spriteByNameHashMap.put(sprite.name(),sprite);
			SpriteManager().spriteByIDHashMap.put(sprite.id(),sprite);

		}

	}

	//====================================================
	//MAP
	//====================================================
	//=========================================================================================================================
	public void sendMapDataRequestByName(String mapName)
	{//=========================================================================================================================
		connectAndAuthorizeAndWriteToChannel(BobNet.Map_Request_By_Name+mapName+BobNet.endline);
	}

	//=========================================================================================================================
	public void sendMapDataRequestByID(int id)
	{//=========================================================================================================================
		connectAndAuthorizeAndWriteToChannel(BobNet.Map_Request_By_ID+id+BobNet.endline);
	}

	//=========================================================================================================================
	private void incomingMapData(String s)
	{//=========================================================================================================================

		//Map:id-name:Base64->GZip->GSON/JSON->MapData[Lights,Entities,Events,States,Areas,Doors,Characters]
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(s.indexOf(":")+1);//intentional ::

		MapData data = new MapData();
		data.initFromString(s);

		if(data==null)
		{
			log.error("Map could not be decompressed.");
		}
		else
		{

			if(MapManager().mapByNameHashMap.get(data.name())==null)
			{

				Map m = new Map(Engine(),data);
				MapManager().mapList.add(m);
				MapManager().mapByNameHashMap.put(data.name(),m);
				MapManager().mapByIDHashMap.put(data.id(),m);

			}
		}
	}



	//====================================================
	public void sendServerObjectRequest(ServerObject serverObject)
	{//====================================================
		if(serverObject.getClass()==Dialogue.class)sendDialogueRequest(((Dialogue)serverObject).id());
		if(serverObject.getClass()==Flag.class)sendFlagRequest(((Flag)serverObject).id());
		if(serverObject.getClass()==GameString.class)sendGameStringRequest(((GameString)serverObject).id());
		if(serverObject.getClass()==Skill.class)sendSkillRequest(((Skill)serverObject).id());
		if(serverObject.getClass()==Event.class)sendEventRequest(((Event)serverObject).id());
		if(serverObject.getClass()==Sound.class)sendSoundRequest(((Sound)serverObject).id());
		if(serverObject.getClass()==Music.class)sendMusicRequest(((Music)serverObject).id());
	}


	//====================================================
	//DIALOGUE
	//====================================================

	//=========================================================================================================================
	public void sendDialogueRequest(int id)
	{//=========================================================================================================================
		connectAndAuthorizeAndWriteToChannel(BobNet.Dialogue_Request+id+BobNet.endline);
	}

	//=========================================================================================================================
	private void incomingDialogue(String s)
	{//=========================================================================================================================

		s = s.substring(s.indexOf(":")+1);
		s = s.substring(s.indexOf(":")+1);//intentional ::

		//Dialogue:id-name:base64Blob

		DialogueData data = new DialogueData();
		data.initFromString(s);

		if(data==null)
		{
			log.error("Dialogue could not be decompressed.");
		}
		else
		{
			Dialogue d = EventManager().getDialogueByIDCreateIfNotExist(data.id());
			d.setData_S(data);
		}


	}

	//====================================================
	//EVENT
	//====================================================

	//=========================================================================================================================
	public void sendLoadEventRequest()
	{//=========================================================================================================================
		connectAndAuthorizeAndWriteToChannel(BobNet.Load_Event_Request+BobNet.endline);
	}

	//=========================================================================================================================
	private void incomingLoadEventResponse(String s)
	{//=========================================================================================================================

		//Event:id-name:eventData
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(s.indexOf(":")+1);//intentional ::


		EventData data = new EventData();
		data.initFromString(s);

		if(data==null)
		{
			log.error("Load Event could not be decompressed.");
		}
		else
		{
			Event d = EventManager().getEventByIDCreateIfNotExist(data.id());
			d.setData_S(data);

			ClientGameEngine().setProjectLoadEventID_S(data.id());

			if(data.id()==-1)
			{
				log.error("Load eventID is -1");
			}
		}


	}


	//=========================================================================================================================
	public void sendEventRequest(int id)
	{//=========================================================================================================================
		connectAndAuthorizeAndWriteToChannel(BobNet.Event_Request+id+BobNet.endline);
	}

	//=========================================================================================================================
	private void incomingEvent(String s)
	{//=========================================================================================================================

		//Event:id-name:eventData
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(s.indexOf(":")+1);//intentional ::


		EventData data = new EventData();
		data.initFromString(s);

		if(data==null)
		{
			log.error("Event could not be decompressed.");
		}
		else
		{
			Event d = EventManager().getEventByIDCreateIfNotExist(data.id());
			d.setData_S(data);
		}


	}

	//====================================================
	//GAMESTRING
	//====================================================

	//=========================================================================================================================
	public void sendGameStringRequest(int id)
	{//=========================================================================================================================
		connectAndAuthorizeAndWriteToChannel(BobNet.GameString_Request+id+BobNet.endline);
	}

	//=========================================================================================================================
	private void incomingGameString(String s)
	{//=========================================================================================================================


		//GameString:id:data
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(s.indexOf(":")+1);//intentional ::

		GameStringData data = new GameStringData();
		data.initFromString(s);

		if(data==null)
		{
			log.error("GameString could not be decompressed.");
		}
		else
		{
			GameString gameString = EventManager().getGameStringByIDCreateIfNotExist(data.id());
			gameString.setData_S(data);
		}

	}

	//====================================================
	//FLAG
	//====================================================

	//=========================================================================================================================
	public void sendFlagRequest(int id)
	{//=========================================================================================================================
		connectAndAuthorizeAndWriteToChannel(BobNet.Flag_Request+id+BobNet.endline);
	}

	//=========================================================================================================================
	private void incomingFlag(String s)
	{//=========================================================================================================================


		//Flag:id:data
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(s.indexOf(":")+1);//intentional ::

		FlagData data = new FlagData();
		data.initFromString(s);

		if(data==null)
		{
			log.error("Flag could not be decompressed.");
		}
		else
		{
			Flag flag = EventManager().getFlagByIDCreateIfNotExist(data.id());
			flag.setData_S(data);
		}

	}

	//====================================================
	//SKILL
	//====================================================

	//=========================================================================================================================
	public void sendSkillRequest(int id)
	{//=========================================================================================================================
		connectAndAuthorizeAndWriteToChannel(BobNet.Skill_Request+id+BobNet.endline);
	}

	//=========================================================================================================================
	private void incomingSkill(String s)
	{//=========================================================================================================================


		//Skill:id:data
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(s.indexOf(":")+1);//intentional ::

		SkillData data = new SkillData();
		data.initFromString(s);

		if(data==null)
		{
			log.error("Skill could not be decompressed.");
		}
		else
		{
			Skill skill = EventManager().getSkillByIDCreateIfNotExist(data.id());
			skill.setData_S(data);
		}

	}

	//====================================================
	//MUSIC
	//====================================================

	//=========================================================================================================================
	public void sendMusicRequest(int id)
	{//=========================================================================================================================
		connectAndAuthorizeAndWriteToChannel(BobNet.Music_Request+id+BobNet.endline);
	}

	//=========================================================================================================================
	private void incomingMusic(String s)
	{//=========================================================================================================================

		//Music:id:data
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(s.indexOf(":")+1);//intentional ::

		MusicData data = new MusicData();
		data.initFromString(s);

		if(data==null)
		{
			log.error("Music could not be decompressed.");
		}
		else
		{
			Music music = AudioManager().getMusicByIDCreateIfNotExist(data.id());
			music.setData_S(data);
		}


	}

	//====================================================
	//SOUND
	//====================================================

	//=========================================================================================================================
	public void sendSoundRequest(int id)
	{//=========================================================================================================================
		connectAndAuthorizeAndWriteToChannel(BobNet.Sound_Request+id+BobNet.endline);
	}

	//=========================================================================================================================
	private void incomingSound(String s)
	{//=========================================================================================================================


		//Sound:id:data
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(s.indexOf(":")+1);//intentional ::

		SoundData data = new SoundData();
		data.initFromString(s);

		if(data==null)
		{
			log.error("Sound could not be decompressed.");
		}
		else
		{
			Sound sound = AudioManager().getSoundByIDCreateIfNotExist(data.id());
			sound.setData_S(data);
		}

	}












}
