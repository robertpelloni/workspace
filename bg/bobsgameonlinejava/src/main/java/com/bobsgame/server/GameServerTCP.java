package com.bobsgame.server;

import java.util.concurrent.ConcurrentHashMap;


import javax.mail.*;

import java.util.*;


import ch.qos.logback.classic.Level;
import ch.qos.logback.classic.Logger;

import com.bobsgame.ServerMain;
import com.bobsgame.shared.Utils;
import com.bobsgame.net.*;
import com.bobsgame.net.BobsGameLeaderBoardAndHighScoreBoard.LeaderBoardScore;


import com.bobsgame.server.assets.AssetDataIndex;
import com.maxmind.geoip2.DatabaseReader;
import com.maxmind.geoip2.model.CityResponse;
import com.maxmind.geoip2.record.Country;
import com.maxmind.geoip2.record.Subdivision;
import com.mchange.v2.c3p0.ComboPooledDataSource;
import com.restfb.DefaultFacebookClient;
import com.restfb.FacebookClient;
import com.restfb.FacebookClient.AccessToken;
import com.restfb.Version;
import com.restfb.types.User;

import java.beans.PropertyVetoException;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.net.ConnectException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.sql.*;

import org.apache.commons.codec.binary.Base64;
import org.apache.commons.mail.DefaultAuthenticator;
import org.apache.commons.mail.EmailException;
import org.apache.commons.mail.HtmlEmail;
import org.jasypt.util.text.BasicTextEncryptor;

import io.netty.bootstrap.ServerBootstrap;
import io.netty.channel.Channel;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelFutureListener;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.ChannelPipeline;
import io.netty.channel.EventLoopGroup;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.SocketChannel;
import io.netty.channel.socket.nio.NioServerSocketChannel;
import io.netty.handler.codec.DelimiterBasedFrameDecoder;
import io.netty.handler.codec.Delimiters;
import io.netty.handler.codec.string.StringDecoder;
import io.netty.handler.codec.string.StringEncoder;
import io.netty.handler.timeout.IdleState;
import io.netty.handler.timeout.IdleStateEvent;
import io.netty.handler.timeout.IdleStateHandler;
import io.netty.handler.timeout.ReadTimeoutException;
import io.netty.channel.SimpleChannelInboundHandler;
import io.netty.util.concurrent.DefaultEventExecutorGroup;
import io.netty.util.concurrent.EventExecutorGroup;

import org.slf4j.LoggerFactory;



import net.jpountz.lz4.LZ4Compressor;
import net.jpountz.lz4.LZ4Factory;

//===============================================================================================
public class GameServerTCP
{//===============================================================================================


	//TODO: are we sure we want 16 threads??? optimise this.
	static final EventExecutorGroup group = new DefaultEventExecutorGroup(16);




	//Timer timer;


	public Vector<Channel> channels = new Vector<Channel>();
	public ConcurrentHashMap<BobsGameClient,Channel> channelsByClient = new ConcurrentHashMap<BobsGameClient,Channel>();
	public ConcurrentHashMap<Channel,BobsGameClient> clientsByChannel = new ConcurrentHashMap<Channel,BobsGameClient>();

	public ConcurrentHashMap<Long,BobsGameClient> clientsByUserID = new ConcurrentHashMap<Long,BobsGameClient>();//using Integer and supplying ints will work, Java autoboxes/unboxes int natives

	public ConcurrentHashMap<String,BobsGameClient> clientsByFacebookID = new ConcurrentHashMap<String,BobsGameClient>();
	public ConcurrentHashMap<String,BobsGameClient> clientsByEmailAddress = new ConcurrentHashMap<String,BobsGameClient>();
	public ConcurrentHashMap<String,BobsGameClient> clientsByUserName = new ConcurrentHashMap<String,BobsGameClient>();

	public Vector<BobsGameRoom> rooms = new Vector<BobsGameRoom>();
	public ConcurrentHashMap<Long,BobsGameRoom> roomsByUserID = new ConcurrentHashMap<Long,BobsGameRoom>();//using Integer and supplying ints will work, Java autoboxes/unboxes int natives
	public ConcurrentHashMap<String,BobsGameRoom> roomsByRoomUUID = new ConcurrentHashMap<String,BobsGameRoom>();//using Integer and supplying ints will work, Java autoboxes/unboxes int natives



	ServerBootstrap tcpServerBootstrap;
	EventLoopGroup bossGroup;
    EventLoopGroup workerGroup;
	Channel tcpChannel;


	public static Logger log = (Logger)LoggerFactory.getLogger(GameServerTCP.class);




	static ComboPooledDataSource amazonRDSConnectionPool = null;
	static ComboPooledDataSource dreamhostSQLConnectionPool = null;



	//===============================================================================================
	public GameServerTCP()
	{//===============================================================================================

		//timer = new HashedWheelTimer();


        bossGroup = new NioEventLoopGroup(1);
        workerGroup = new NioEventLoopGroup();

		// Configure the channel factory.
		//tcpChannelFactory = new NioServerSocketChannelFactory(Executors.newCachedThreadPool(), Executors.newCachedThreadPool());
		tcpServerBootstrap = new ServerBootstrap();
        tcpServerBootstrap.group(bossGroup, workerGroup)
             .channel(NioServerSocketChannel.class)
             .childHandler(new ChannelInitializer<SocketChannel>() {
                 @Override
                 public void initChannel(SocketChannel ch) throws Exception {
                     ChannelPipeline pipeline = ch.pipeline();

                     pipeline.addLast("idleStateHandler", new IdleStateHandler(30, 30, 30));

                     pipeline.addLast("framer", new DelimiterBasedFrameDecoder(65535, Delimiters.lineDelimiter()));
                     pipeline.addLast("decoder", new StringDecoder());
                     pipeline.addLast("encoder", new StringEncoder());

                     //this should help not stall threads when doing db access
                     pipeline.addLast(group, "handler", new BobsGameServerHandler());
                 }
             });


		// Configure the pipeline factory.
		//tcpServerBootstrap.setPipelineFactory(new TimeOutChannelPipelineFactory(timer));

		//tcpServerBootstrap.setOption("child.tcpNoDelay", true);
		//tcpServerBootstrap.setOption("child.keepAlive", true);

		//tcpServerBootstrap.setOption("tcpNoDelay", true);
		//tcpServerBootstrap.setOption("keepAlive", true);

		//tcpServerBootstrap.setOption("reuseAddress", "true");

		//tcpServerBootstrap.setOption("sendBufferSize", 524288);//524288
		//tcpServerBootstrap.setOption("receiveBufferSize", 524288);
		//tcpServerBootstrap.setOption("receiveBufferSizePredictorFactory", new AdaptiveReceiveBufferSizePredictorFactory());

		//tcpServerBootstrap.setOption("broadcast", "true");


		int serverPort = BobNet.serverTCPPort;
		//if(new File("/localServer").exists())serverPort++;

		// Bind and start to accept incoming connections.
		//tcpChannel = tcpServerBootstrap.bind(new InetSocketAddress(serverPort));
        try {
            ChannelFuture f = tcpServerBootstrap.bind(serverPort).sync();
            tcpChannel = f.channel();
		    log.info("Server TCP ChannelID: "+tcpChannel.id().toString());
        } catch (InterruptedException e) {
            e.printStackTrace();
        }





		System.setProperty("com.mchange.v2.log.MLog","com.mchange.v2.log.slf4j.Slf4jMLog");


		((Logger)LoggerFactory.getLogger(com.mchange.v2.async.ThreadPoolAsynchronousRunner.class)).setLevel(Level.WARN);
		((Logger)LoggerFactory.getLogger(com.mchange.v2.resourcepool.ResourcePool.class)).setLevel(Level.WARN);
		((Logger)LoggerFactory.getLogger("com.mchange.v2.resourcepool.BasicResourcePool")).setLevel(Level.WARN);
		((Logger)LoggerFactory.getLogger(com.mchange.v2.c3p0.impl.C3P0PooledConnectionPool.class)).setLevel(Level.WARN);

		try
		{
			//load the database driver
			Class.forName("com.mysql.jdbc.Driver");
		}
		catch (Exception e)
		{
			e.printStackTrace();
			return;
		}

		try
		{

			amazonRDSConnectionPool = new ComboPooledDataSource();
			amazonRDSConnectionPool.setDriverClass( "com.mysql.jdbc.Driver" ); //loads the jdbc driver
			amazonRDSConnectionPool.setJdbcUrl(PrivateCredentials.AMAZON_RDS_URL);
			amazonRDSConnectionPool.setUser(PrivateCredentials.AMAZON_RDS_USERNAME);
			amazonRDSConnectionPool.setPassword(PrivateCredentials.AMAZON_RDS_PASSWORD);
			amazonRDSConnectionPool.setMinPoolSize(3);
			amazonRDSConnectionPool.setAcquireIncrement(5);
			amazonRDSConnectionPool.setMaxPoolSize(80);
			amazonRDSConnectionPool.setAutoCommitOnClose(true);
			amazonRDSConnectionPool.setTestConnectionOnCheckin(true);
			amazonRDSConnectionPool.setTestConnectionOnCheckout(true);
			amazonRDSConnectionPool.setAutomaticTestTable("c3p0_test_table");
			//amazonRDSConnectionPool.setPreferredTestQuery(preferredTestQuery)
			amazonRDSConnectionPool.setIdleConnectionTestPeriod(30);
//			Properties p = amazonRDSConnectionPool.getProperties();
//			p.setProperty("c3p0.extensions.timezone","UTC");
//			amazonRDSConnectionPool.setProperties(p);

			//amazonRDSConnectionPool.setDebugUnreturnedConnectionStackTraces(true);





			dreamhostSQLConnectionPool = new ComboPooledDataSource();
			dreamhostSQLConnectionPool.setDriverClass( "com.mysql.jdbc.Driver" ); //loads the jdbc driver
			dreamhostSQLConnectionPool.setJdbcUrl(PrivateCredentials.DREAMHOST_SQL_URL);
			dreamhostSQLConnectionPool.setUser(PrivateCredentials.DREAMHOST_SQL_USERNAME);
			dreamhostSQLConnectionPool.setPassword(PrivateCredentials.DREAMHOST_SQL_PASSWORD);
			dreamhostSQLConnectionPool.setMinPoolSize(3);
			dreamhostSQLConnectionPool.setAcquireIncrement(5);
			dreamhostSQLConnectionPool.setMaxPoolSize(20);
			dreamhostSQLConnectionPool.setAutoCommitOnClose(true);
			dreamhostSQLConnectionPool.setTestConnectionOnCheckin(true);
			dreamhostSQLConnectionPool.setTestConnectionOnCheckout(true);
			dreamhostSQLConnectionPool.setAutomaticTestTable("c3p0_test_table");
			dreamhostSQLConnectionPool.setIdleConnectionTestPeriod(30);
//			p = dreamhostSQLConnectionPool.getProperties();
//			p.setProperty("c3p0.extensions.timezone","UTC");
//			dreamhostSQLConnectionPool.setProperties(p);
			//dreamhostSQLConnectionPool.setDebugUnreturnedConnectionStackTraces(true);



/*

			{
				//setup the connection pool
				BoneCPConfig amazonRDSConfig = new BoneCPConfig();

				amazonRDSConfig.setJdbcUrl(ServerMain.AMAZON_RDS_URL); // jdbc url specific to your database, eg jdbc:mysql://127.0f.0f.1/yourdb
				amazonRDSConfig.setUsername(ServerMain.AMAZON_RDS_USERNAME);
				amazonRDSConfig.setPassword(ServerMain.AMAZON_RDS_PASSWORD);

				amazonRDSConfig.setMinConnectionsPerPartition(1);
				amazonRDSConfig.setMaxConnectionsPerPartition(20);
				amazonRDSConfig.setPartitionCount(4); //20 x 4  = 80 per server. //small instance = 150 connections. //medium = 303.
				amazonRDSConfig.setDefaultAutoCommit(true);
				amazonRDSConfig.setDefaultReadOnly(false);
				amazonRDSConfig.setDisableJMX(true);


				amazonRDSConfig.setQueryExecuteTimeLimitInMs(50);

				//amazonRDSConfig.setTransactionRecoveryEnabled(true);//not sure on this one


				if(BobNet.debugMode==true)
				{
					//watch every connection
					amazonRDSConfig.setCloseConnectionWatch(true);

					//log all statements
					amazonRDSConfig.setLogStatementsEnabled(true);
					amazonRDSConfig.setQueryExecuteTimeLimitInMs(0);

					//detect and close any PreparedStatemtents left open
					amazonRDSConfig.setCloseOpenStatements(true);
					amazonRDSConfig.setDetectUnclosedStatements(true);

					//for autoCommit OFF
					//amazonRDSConfig.setResetConnectionOnClose(true);
					//amazonRDSConfig.setDetectUnresolvedTransactions(true);
				}


				amazonRDSConnectionPool = new BoneCP(amazonRDSConfig); // setup the connection pool


			}




			{
				BoneCPConfig dreamhostSQLConfig = new BoneCPConfig();

				dreamhostSQLConfig.setJdbcUrl(ServerMain.DREAMHOST_SQL_URL); // jdbc url specific to your database, eg jdbc:mysql://127.0f.0f.1/yourdb
				dreamhostSQLConfig.setUsername(ServerMain.DREAMHOST_SQL_USERNAME);
				dreamhostSQLConfig.setPassword(ServerMain.DREAMHOST_SQL_PASSWORD);

				dreamhostSQLConfig.setMinConnectionsPerPartition(1);
				dreamhostSQLConfig.setMaxConnectionsPerPartition(5);
				dreamhostSQLConfig.setPartitionCount(4);
				dreamhostSQLConfig.setDefaultAutoCommit(true);
				dreamhostSQLConfig.setDefaultReadOnly(false);
				dreamhostSQLConfig.setDisableJMX(true);


				dreamhostSQLConfig.setQueryExecuteTimeLimitInMs(50);
				//dreamhostSQLConfig.setTransactionRecoveryEnabled(true);//not sure on this one



				if(BobNet.debugMode==true)
				{
					//watch every connection
					dreamhostSQLConfig.setCloseConnectionWatch(true);

					//log all statements
					dreamhostSQLConfig.setLogStatementsEnabled(true);
					dreamhostSQLConfig.setQueryExecuteTimeLimitInMs(0);

					//detect and close any PreparedStatemtents left open
					dreamhostSQLConfig.setCloseOpenStatements(true);
					dreamhostSQLConfig.setDetectUnclosedStatements(true);

					//for autoCommit OFF
					//dreamhostSQLConfig.setResetConnectionOnClose(true);
					//dreamhostSQLConfig.setDetectUnresolvedTransactions(true);
				}


				dreamhostSQLConnectionPool = new BoneCP(dreamhostSQLConfig); // setup the connection pool
			}

*/

		}
		catch(PropertyVetoException e)
		{
			e.printStackTrace();
		}


	}


	//===============================================================================================
	public void cleanup()
	{//===============================================================================================

		amazonRDSConnectionPool.close(); // shutdown connection pool.
		dreamhostSQLConnectionPool.close(); // shutdown connection pool.



		//tcpServerBootstrap.releaseExternalResources();
        workerGroup.shutdownGracefully();
        bossGroup.shutdownGracefully();
		//timer.stop();
	}








	//===============================================================================================
	public class BobsGameServerHandler extends SimpleChannelInboundHandler<String>
	{//===============================================================================================

		Logger log = (Logger)LoggerFactory.getLogger(this.getClass());

		//===============================================================================================
        @Override
		public void userEventTriggered(ChannelHandlerContext ctx, Object evt) throws Exception
		{//===============================================================================================

            if (evt instanceof IdleStateEvent) {
                IdleStateEvent e = (IdleStateEvent) evt;
			    long id = -1;
			    BobsGameClient c = getClientByChannel(ctx.channel());
			    if(c!=null)id=c.userID;


			    if(e.state() == IdleState.READER_IDLE)
			    {
				    log.info("channelIdle: No incoming traffic from client timeout. Closing channel. | ChannelID: "+ctx.channel().id()+" | ClientuserID: "+id);

				    ctx.close();

			    }
			    else if(e.state() == IdleState.WRITER_IDLE)
			    {

				    writePlaintext(ctx.channel(),"ping"+BobNet.endline);

				    //log.debug("channelIdle: ping | ChannelID: "+channel.id()+" | Client userID: "+id);
			    }
            }


		}


		//===============================================================================================
		@Override
		public void channelActive(ChannelHandlerContext ctx) throws Exception
		{//===============================================================================================
			String id = ctx.channel().id().toString();
			String ip = ctx.channel().remoteAddress().toString();


			log.info("channelConnected: ("+id+") "+ip+" "+getCityFromIP(ip));

			channels.add(ctx.channel());

		}





		//===============================================================================================
		@Override
		public void channelInactive(ChannelHandlerContext ctx)
		{//===============================================================================================


			BobsGameClient c = getClientByChannel(ctx.channel());

			String userName = "";
			if(c!=null)userName = c.userName;


			String id = ctx.channel().id().toString();
			String ip = "unknown";
            try{ip = ctx.channel().remoteAddress().toString();}catch(Exception ex){}

			log.info("channelDisconnected: ("+id+") "+userName+" "+ip+" "+getCityFromIP(ip));


			channels.remove(ctx.channel());



			if(c!=null)
			{
				channelsByClient.remove(c);
				clientsByChannel.remove(ctx.channel());
				clientsByUserID.remove(c.userID);
				if(c.facebookID.length()>0)clientsByFacebookID.remove(c.facebookID);
				if(c.userName.length()>0)clientsByUserName.remove(c.userName);
				if(c.emailAddress.length()>0)clientsByEmailAddress.remove(c.emailAddress);

				if(c.startTime!=-1)//we wrote it to the database when the login was verified
				if(c.userID!=-1)
				{




					long end = System.currentTimeMillis();
					long start = c.startTime;
					long len = (end-start)/1000;


					{
						Connection databaseConnection = openDreamhostSQLDB();
						if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

						//Statement databaseStatement = null;
						PreparedStatement ps = null;

						try
						{
							//databaseStatement.executeUpdate("UPDATE connections SET endTime = '"+end+"', lengthSeconds = '"+len+"' WHERE sessionToken = '"+c.sessionToken+"'");
							ps = databaseConnection.prepareStatement(
									"UPDATE connections SET " +
									"endTime = ? , " +
									"lengthSeconds = ? " +
									"WHERE startTime = ?");


							ps.setLong(1, end);
							ps.setLong(2, len);
							ps.setLong(3, c.startTime);
							ps.executeUpdate();

							ps.close();

						}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());}

						closeDBConnection(databaseConnection);
					}


					long totalTimePlayed_DB = -1;

					{
						Connection databaseConnection = openAccountsDBOnAmazonRDS();
						if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

						PreparedStatement ps = null;
						ResultSet resultSet = null;

						try
						{
							ps = databaseConnection.prepareStatement(
									"SELECT " +
									"totalTimePlayed " +
									"FROM accounts WHERE userID = ?");


							ps.setLong(1, c.userID);
							resultSet = ps.executeQuery();

						}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());}

						try
						{

							if(resultSet.next())
							{
								totalTimePlayed_DB = resultSet.getLong("totalTimePlayed");
							}

							resultSet.close();
							ps.close();
							closeDBConnection(databaseConnection);

						}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());}

					}

					totalTimePlayed_DB += len;


					{
						Connection databaseConnection = openAccountsDBOnAmazonRDS();
						if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

						PreparedStatement ps = null;

						try
						{
							ps = databaseConnection.prepareStatement(
									"UPDATE accounts SET " +
									"lastSeenTime = ? , " +
									"isOnline = ? , " +
									"totalTimePlayed = ? " +
									"WHERE userID = ?");


							ps.setLong(1, end);
							ps.setInt(2, 0);
							ps.setLong(3, totalTimePlayed_DB);
							ps.setLong(4, c.userID);
							ps.executeUpdate();

							ps.close();

						}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());}

						closeDBConnection(databaseConnection);
					}


				}
			}



			//log.info("Removed channel clientConnection from hashtable");

			//DONE: set connection end in database, whether client dropped, webpage was closed, client logged out, etc.
			//maybe session should be "connection" instead of "session" which is in theory held between connections
			//or maybe i am tracking sessions which should only be per-computer and not connection dependent
			//maybe i should track both!

		}


		//===============================================================================================
		@Override
		public void channelRead0(ChannelHandlerContext ctx, String message) throws Exception
		{//===============================================================================================

            Channel channel = ctx.channel();

			//if(BobNet.debugMode)
			if(
					message.startsWith("ping")==false && 
					message.startsWith("pong")==false && 
					message.startsWith("Server_Stats")==false && 
					message.startsWith("Online_Friends")==false && 
					message.startsWith("Bobs_Game_RoomList")==false
				)
			{
				long userID = -1;
				String userName = "";
				BobsGameClient c = getClientByChannel(channel);
				if(c!=null){userID=c.userID;userName=c.userName;}

				if(message.indexOf("Login")!=-1 || message.indexOf("Reconnect") != -1 || message.indexOf("Create_Account") != -1)
					log.warn("FROM CLIENT: ("+channel.id()+") "+userName+" | "+message.substring(0, message.indexOf(":")+1)+"(censored)");
				else log.warn("FROM CLIENT: ("+channel.id()+") "+userName+" | "+message);

				//log.debug("ChannelHandlerContext getChannel:"+ctx.channel().getId());
				//log.debug("MessageEvent getChannel:"+channel.id());
				//log.debug("MessageEvent getRemoteAddress:"+channel.remoteAddress().toString());
			}

			if(message.startsWith("ping"))
			{
				//log.debug("INDEX: ping");
				writePlaintext(channel,"pong"+BobNet.endline);
				return;
			}
			if(message.startsWith("pong"))
			{
//				int id = -1;
//				Client c = getClientByChannel(channel);
//				if(c!=null)id=c.userID;

				//log.debug("pong from | ChannelID: "+channel.id()+" | Client userID: "+id);

				return;
			}






			if(message.startsWith(BobNet.Server_IP_Address_Request)){incomingServerIPAddressRequest(channel, message);return;}
			if(message.startsWith(BobNet.Server_Stats_Request)){incomingServerStatsRequest(channel, message);return;}
			if(message.startsWith(BobNet.Client_Location_Request)){incomingClientLocationRequest(channel, message);return;}




			if(message.startsWith(BobNet.Login_Request)){incomingLoginRequest(channel, message);return;}
			if(message.startsWith(BobNet.Facebook_Login_Request)){incomingFacebookLoginOrCreateAccountAndLoginRequest(channel, message);return;}
			if(message.startsWith(BobNet.Reconnect_Request)){incomingReconnectRequest(channel, message);return;}
			if(message.startsWith(BobNet.Password_Recovery_Request)){incomingPasswordRecoveryRequest(channel, message);return;}
			if(message.startsWith(BobNet.Create_Account_Request)){incomingCreateAccountRequest(channel, message);return;}

			if(message.startsWith(BobNet.Initial_GameSave_Request)){incomingInitialGameSaveRequest(channel, message);return;}
			if(message.startsWith(BobNet.Encrypted_GameSave_Update_Request)){incomingGameSaveUpdateRequest(channel, message);return;}
			if(message.startsWith(BobNet.Load_Event_Request)){incomingLoadEventRequest(channel, message);return;}

			//deprecated, client side geolookup using google/yahoo API now.
			if(message.startsWith(BobNet.Postal_Code_Update_Request)){incomingPostalCodeUpdateRequest(channel, message);return;}


			if(message.startsWith(BobNet.Sprite_Request_By_Name)){incomingSpriteDataRequestByName(channel, message);return;}
			if(message.startsWith(BobNet.Sprite_Request_By_ID)){incomingSpriteDataRequestByID(channel, message);return;}
			if(message.startsWith(BobNet.Map_Request_By_Name)){incomingMapDataRequestByName(channel, message);return;}
			if(message.startsWith(BobNet.Map_Request_By_ID)){incomingMapDataRequestByID(channel, message);return;}
			if(message.startsWith(BobNet.Dialogue_Request)){incomingDialogueDataRequest(channel, message);return;}
			if(message.startsWith(BobNet.Flag_Request)){incomingFlagDataRequest(channel, message);return;}
			if(message.startsWith(BobNet.Skill_Request)){incomingSkillDataRequest(channel, message);return;}
			if(message.startsWith(BobNet.Event_Request)){incomingEventDataRequest(channel, message);return;}
			if(message.startsWith(BobNet.GameString_Request)){incomingGameStringDataRequest(channel, message);return;}
			if(message.startsWith(BobNet.Music_Request)){incomingMusicDataRequest(channel, message);return;}
			if(message.startsWith(BobNet.Sound_Request)){incomingSoundDataRequest(channel, message);return;}

			if(message.startsWith(BobNet.Player_Coords)){incomingPlayerCoords(channel, message);return;}


			if(message.startsWith(BobNet.Update_Facebook_Account_In_DB_Request)){incomingUpdateFacebookAccountInDBRequest(channel, message);return;}
			if(message.startsWith(BobNet.Online_Friends_List_Request)){incomingOnlineFriendsListRequest(channel, message);return;}
			if(message.startsWith(BobNet.Add_Friend_By_UserName_Request)){incomingAddFriendByUserNameRequest(channel, message);return;}

			if(message.startsWith(BobNet.Bobs_Game_GameTypesAndSequences_Download_Request)){incomingBobsGameGameTypesDownloadRequest(channel, message);return;}
			if(message.startsWith(BobNet.Bobs_Game_GameTypesAndSequences_Upload_Request)){incomingBobsGameGameTypesUploadRequest(channel, message);return;}
			if(message.startsWith(BobNet.Bobs_Game_GameTypesAndSequences_Vote_Request)){incomingBobsGameGameTypesVoteRequest(channel, message);return;}



			if(message.startsWith(BobNet.Bobs_Game_RoomList_Request)){incomingBobsGameRoomListRequest(channel, message);return;}

			if(message.startsWith(BobNet.Bobs_Game_TellRoomHostToAddMyUserID)){incomingBobsGameTellRoomHostToAddUserID(channel, message);return;}

			if(message.startsWith(BobNet.Bobs_Game_HostingPublicRoomUpdate)){incomingBobsGameHostingPublicRoomUpdate(channel, message);return;}
			if(message.startsWith(BobNet.Bobs_Game_HostingPublicRoomStarted)){incomingBobsGameHostingPublicRoomStarted(channel, message);return;}
			if(message.startsWith(BobNet.Bobs_Game_HostingPublicRoomCanceled)){incomingBobsHostingPublicRoomCanceled(channel, message);return;}
			if(message.startsWith(BobNet.Bobs_Game_HostingPublicRoomEnded)){incomingBobsGameHostingPublicRoomEnded(channel, message);return;}
			if(message.startsWith(BobNet.Bobs_Game_GameStats)){incomingBobsGameGameStats(channel, message);return;}
			if(message.startsWith(BobNet.Bobs_Game_GetHighScoresAndLeaderboardsRequest)){incomingBobsGameGetHighScoresAndLeaderboardsRequest(channel, message);return;}
			if(message.startsWith(BobNet.Bobs_Game_ActivityStream_Request)){incomingBobsGameActivityStreamRequest(channel, message);return;}

			if(message.startsWith(BobNet.Chat_Message)){incomingChatMessage(channel, message,true);return;}


		}

		//===============================================================================================
		@Override
		public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause)
		{//===============================================================================================

			if(cause instanceof ConnectException)
			{
				log.error("Exception caught from Client connection - ConnectException: "+cause.getMessage());
			}
			else
			if(cause instanceof ReadTimeoutException)
			{
				log.error("Exception caught from Client connection - ReadTimeoutException: "+cause.getMessage());
			}
			else
			if(cause instanceof IOException)
			{
				//log.error("Exception caught from Client connection - IOException: "+cause.getMessage());
			}
			else
			{
				//if(BobNet.debugMode)
				{
					log.error("Unexpected Exception caught from Client connection: "+cause.getMessage());
					cause.printStackTrace();
				}
			}

			//ctx.channel().close();
			//channel.close();
		}

	}

	//===============================================================================================
	public ChannelFuture writeFuture(Channel c, String s)
	{//===============================================================================================

		if(s.endsWith(BobNet.endline)==false)
		{
			log.error("Message doesn't end with endline");
			s = s +BobNet.endline;
		}

		//if(BobNet.debugMode)
		{
			long id = -1;
			String userName = "";
			BobsGameClient client = getClientByChannel(c);
			if(client!=null){id=client.userID;userName = client.userName;}
			log.info("SEND: ("+c.id()+") "+userName+" | "+s.substring(0,s.length()-2));
		}


		ChannelFuture cf = c.writeAndFlush(s);

		return cf;
	}


	//===============================================================================================
	public ArrayList<ChannelFuture> writePlaintext(Channel c, String s)
	{//===============================================================================================

		ArrayList<ChannelFuture> futures = new ArrayList<ChannelFuture>();

		if(s.endsWith(BobNet.endline)==false)
		{
			log.error("Message doesn't end with endline");
			s = s +BobNet.endline;
		}

		long id = -1;
		String userName = "";
		if(c!=null)
		{
			BobsGameClient client = getClientByChannel(c);
			if(client!=null){id=client.userID;userName = client.userName;}
		}


		if(s.startsWith("ping")==false && s.startsWith("pong")==false)
		{

			if(s.indexOf("Login")!=-1 || s.indexOf("Reconnect") != -1 || s.indexOf("Create_Account") != -1)
			log.info("SEND CLIENT: ("+c.id()+") "+userName+" | "+s.substring(0, s.indexOf(":")+1)+"(censored)");
			else
			log.info("SEND CLIENT: ("+c.id()+") "+userName+" | "+s.substring(0,Math.min(100,s.length()-2))+"...");

		}



		if(s.length()>1400)
		{
			s = s.substring(0,s.indexOf(BobNet.endline));

			while(s.length()>1300)
			{
				String partial = "PARTIAL:" + s.substring(0,1300) + BobNet.endline;
				s = s.substring(1300);

				//log.info("SEND: chan:"+c.id()+" "+userName+" | "+partial.substring(0,100)+"...");

				futures.add(c.writeAndFlush(partial));

			}

			String finalString = "FINAL:" + s + BobNet.endline;

			//log.info("SEND: chan:"+c.id()+" "+userName+" | "+finalString.substring(0,Math.min(100,finalString.length()-2))+"...");

			futures.add(c.writeAndFlush(finalString));

		}
		else
		{

			//log.info("SEND: chan:"+c.id()+" "+userName+" | "+s.substring(0,s.length()-2));

			futures.add(c.writeAndFlush(s));

		}

		return futures;


	}


	//===============================================================================================
	public ArrayList<ChannelFuture> writeCompressed(Channel c, String s)
	{//===============================================================================================

		ArrayList<ChannelFuture> futures = new ArrayList<ChannelFuture>();

		if(s.endsWith(BobNet.endline)==false)
		{
			log.error("Message doesn't end with endline");
			s = s +BobNet.endline;
		}

		long id = -1;
		String userName = "";
		if(c!=null)
		{
			BobsGameClient client = getClientByChannel(c);
			if(client!=null)
			{
				id=client.userID;
				userName =client.userName;
			}
		}




//
//		log.info("SEND: chan:"+c.id()+" "+userName+" | "+s.substring(0,Math.min(100,s.length()-2))+"...");
//
//		//lzo and base64 string
//
//		String lzoString = null;
//
//		ByteArrayOutputStream out = new ByteArrayOutputStream();
//		LzoAlgorithm algorithm = LzoAlgorithm.LZO1X;
//		LzoCompressor compressor = LzoLibrary.getInstance().newCompressor(algorithm, LzoConstraint.COMPRESSION);
//		LzoOutputStream lzoStream = new LzoOutputStream(out, compressor, 256);
//
//		try
//		{
//			lzoStream.write(s.getBytes());
//			lzoStream.close();
//			lzoString=out.toString("ISO-8859-1");
//		}
//		catch(IOException e)
//		{
//			e.printStackTrace();
//		}
//
//		String base64 = Utils.encodeStringToBase64(lzoString);
//		s = new String(base64+BobNet.endline);
//
//
//
//		log.info("SEND: chan:"+c.id()+" "+userName+" | "+s.substring(0,Math.min(100,s.length()-2))+"...");
//



//		ByteArrayOutputStream out=new ByteArrayOutputStream();
//		DeflaterOutputStream gzip;
//
//		String zip = null;
//
//
//		try
//		{
//			gzip=new DeflaterOutputStream(out);
//			gzip.write(s.getBytes());
//			gzip.close();
//
//			zip=out.toString("ISO-8859-1");
//		}
//		catch(Exception e)
//		{
//			e.printStackTrace();
//		}
//
//
//
//		//String zip = Utils.zipString(s);
//		String base64 = Utils.encodeStringToBase64(zip);
//		s = base64+BobNet.endline;
//

		//String o = new String(s);

		String plainTextCat = s.substring(0,Math.min(100,s.length()-2));
		int origSize = s.length();
		
		try
		{

			LZ4Factory factory = LZ4Factory.safeInstance();

			byte[] data = s.getBytes("UTF-8");


			final int decompressedLength = data.length;

			// compress data
			LZ4Compressor compressor = factory.fastCompressor();
			int maxCompressedLength = compressor.maxCompressedLength(decompressedLength);
			byte[] compressedBuffer = new byte[maxCompressedLength];
			int compressedLength = compressor.compress(data, 0, decompressedLength, compressedBuffer, 0, maxCompressedLength);

			byte[] compressedBytes = new byte[compressedLength];

			for(int i=0;i<compressedLength;i++)
			{
				compressedBytes[i] = compressedBuffer[i];
			}



			String base64 = Base64.encodeBase64String(compressedBytes);
			s = new String(base64);


		}
		catch(UnsupportedEncodingException e)
		{
			e.printStackTrace();
		}



		int compSize = s.length();
		String com = ("Compressed "+origSize+" to "+compSize+" "+(int)(((float)((float)compSize/(float)origSize))*100)+"%");

		if(
				plainTextCat.indexOf("Server_Stats")==-1 && 
				plainTextCat.indexOf("Online_Friends")==-1 && 
				plainTextCat.indexOf("Bobs_Game_RoomList")==-1 &&
				plainTextCat.indexOf("Friend_Is_Online")==-1
			)
		{
			if(plainTextCat.indexOf("Login")!=-1 || plainTextCat.indexOf("Reconnect") != -1 || plainTextCat.indexOf("Create_Account") != -1)
			log.info("SEND CLIENT: ("+c.id()+") "+userName+" | "+plainTextCat.substring(0, plainTextCat.indexOf(":")+1)+"(censored) "+com);
			else
			log.info("SEND CLIENT: ("+c.id()+") "+userName+" | "+plainTextCat+"..."+" "+com);
		}

		if(s.length()>1400)
		{
			//s = s.substring(0,s.indexOf(BobNet.endline));

			while(s.length()>1300)
			{
				String partial = "PARTIAL:" + s.substring(0,1300);
				s = s.substring(1300);

				//log.info("SEND: chan:"+c.id()+" "+userName+" | "+partial.substring(0,100)+"...");

				futures.add(c.writeAndFlush(partial + BobNet.endline));

			}

			String finalString = "FINAL:" + s;

			//log.info("SEND: chan:"+c.id()+" "+userName+" | "+finalString.substring(0,Math.min(100,finalString.length()-2))+"...");

			futures.add(c.writeAndFlush(finalString + BobNet.endline));

		}
		else
		{

			//log.info("SEND: chan:"+c.id()+" "+userName+" | "+s.substring(0,s.length()-2));

			futures.add(c.writeAndFlush(s+BobNet.endline));

		}

		return futures;


	}



	//===============================================================================================
	public static Connection openAccountsDBOnAmazonRDS()
	{//===============================================================================================

		Connection c = null;

		//int tries = 0;

		try
		{

//			while((c == null || !c.isValid(10)) && tries<10)
//			{

				c = amazonRDSConnectionPool.getConnection();

//				if (c != null && !c.isValid(10))
//				{
//					c.prepareStatement("SELECT 1").execute();
//					c.close();
//				}
//
//				tries++;
//
//			}
//
//			if(tries>=10)log.error("accountsDBConnection is null. Could not create DB connection to Amazon RDS.");

			c.setAutoCommit(true);

		}
		catch(Exception e)
		{
			e.printStackTrace();
		}




		return c;

	}



	//===============================================================================================
	public static Connection openDreamhostSQLDB()
	{//===============================================================================================

		Connection c = null;

//		try
//		{
//			connectionLogDBConnection = dreamhostSQLConnectionPool.getConnection();
//			connectionLogDBConnection.setAutoCommit(true);
//		}
//		catch(SQLException e)
//		{
//			e.printStackTrace();
//		}


		//int tries = 0;

		try
		{

//			while((c == null || !c.isValid(10)) && tries<10 )
//			{

				c = dreamhostSQLConnectionPool.getConnection();

//				if (c != null && !c.isValid(10))
//				{
//					c.prepareStatement("SELECT 1").execute();
//					c.close();
//				}
//
//				tries++;
//
//			}
//
//			if(tries>=10)log.error("connectionLogDBConnection is null. Could not create DB connection to Dreamhost SQL.");

			c.setAutoCommit(true);

		}
		catch(Exception e)
		{
			e.printStackTrace();
		}




		return c;

	}

	//===============================================================================================
	public static void closeDBConnection(Connection databaseConnection)
	{//===============================================================================================
		if(databaseConnection != null)
		{
			try
			{
				databaseConnection.close();

			}catch (Exception ex){log.error("DB Error while closing DB: "+ex.getMessage());}
		}
	}


	//===============================================================================================
	public static File getResourceAsFile(String resourcePath)
	{//===============================================================================================
		try {
			InputStream in = ServerMain.class.getClassLoader().getResourceAsStream(resourcePath);
			//InputStream in = ClassLoader.getSystemClassLoader().getResourceAsStream(resourcePath);
			if (in == null) {
				return null;
			}

			File tempFile = File.createTempFile(String.valueOf(in.hashCode()), ".tmp");
			tempFile.deleteOnExit();

			try (FileOutputStream out = new FileOutputStream(tempFile)) {
				//copy stream
				byte[] buffer = new byte[1024];
				int bytesRead;
				while ((bytesRead = in.read(buffer)) != -1) {
					out.write(buffer, 0, bytesRead);
				}
			}
			return tempFile;
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		}
	}

	File geoDB = null;
	//===============================================================================================
	public String getCityFromIP(String ip)
	{//===============================================================================================

		//ServerMain.class.getClassLoader().getResourceAsStream("GeoIP2-City.mmdb");

		// A File object pointing to your GeoIP2 or GeoLite2 database
		if(ip.startsWith("/"))ip = ip.substring(1);
		if(ip.contains(":"))ip = ip.substring(0,ip.indexOf(":"));
		if(ip.equals("127.0.0.1"))return "localhost";

		if(geoDB==null)
		{
			geoDB = getResourceAsFile("GeoLite2-City.mmdb");
		}
		// This creates the DatabaseReader object, which should be reused across
		// lookups.
		DatabaseReader reader;
		InetAddress ipAddress;
		CityResponse response;

		String loc = "";
		try
		{
			reader=new DatabaseReader.Builder(geoDB).build();
			ipAddress=InetAddress.getByName(ip);
			response=reader.city(ipAddress);


			Country country = response.getCountry();
			//System.out.println(country.getIsoCode());            // 'US'
			//System.out.println(country.getName());               // 'United States'
			//System.out.println(country.getNames().get("zh-CN")); // ''



			Subdivision subdivision = response.getMostSpecificSubdivision();
			//System.out.println(subdivision.getName());    // 'Minnesota'
			//System.out.println(subdivision.getIsoCode()); // 'MN'

			loc += subdivision.getName()+", "+country.getName();
			//loc += " ";

			//City city = response.getCity();
			//System.out.println(city.getName()); // 'Minneapolis'

			//Postal postal = response.getPostal();
			//System.out.println(postal.getCode()); // '55455'

			//Location location = response.getLocation();
			//System.out.println(location.getLatitude());  // 44.9733
			//System.out.println(location.getLongitude()); // -93.2323
		}
		catch(Exception e)
		{
			//e.printStackTrace();
		}


		// Replace "city" with the appropriate method for your database, e.g.,
		// "country".


		return loc;



	}


	//===============================================================================================
	private void incomingServerIPAddressRequest(Channel channel, String message)
	{//===============================================================================================

		//ServerIPAddressResponse
		writeCompressed(channel,BobNet.Server_IP_Address_Response+ServerMain.myIPAddressString+BobNet.endline);

	}




	//=========================================================================================================================
	class ServerStats
	{//=========================================================================================================================

		public int serversOnline = 0;
		public int usersOnline = 0;
		public long serverUptime = 0;

		//===============================================================================================
		public String toString()
		{//===============================================================================================

			String s = "";

			s += "serversOnline:`" + (serversOnline) + "`,";
			s += "usersOnline:`" + (usersOnline) + "`,";
			s += "serverUptime:`" + (serverUptime) + "`,";

			return s;
		}

		public String initFromString(String t)
		{

			t = t.substring(t.indexOf("serversOnline:`") + 1);
			t = t.substring(t.indexOf("`") + 1);
			serversOnline = Integer.parseInt(t.substring(0, t.indexOf("`")));
			t = t.substring(t.indexOf("`,") + 2);

			t = t.substring(t.indexOf("usersOnline:`") + 1);
			t = t.substring(t.indexOf("`") + 1);
			usersOnline = Integer.parseInt(t.substring(0, t.indexOf("`")));
			t = t.substring(t.indexOf("`,") + 2);

			t = t.substring(t.indexOf("serverUptime:`") + 1);
			t = t.substring(t.indexOf("`") + 1);
			serverUptime = Long.parseLong(t.substring(0, t.indexOf("`")));
			t = t.substring(t.indexOf("`,") + 2);

			return t;
		}
	};





	//===============================================================================================
	private void incomingServerStatsRequest(Channel channel, String message)
	{//===============================================================================================


		ServerStats s = new ServerStats();
		s.serversOnline = 1;//TODO: have servers queury the index server periodically to get a server count
		s.usersOnline = clientsByChannel.size();//TODO: also have servers queury the index server periodically to get a global user count from all servers
		s.serverUptime = (System.currentTimeMillis() - ServerMain.startTime)/1000;


		writeCompressed(channel,BobNet.Server_Stats_Response+s.toString()+BobNet.endline);

	}

	//===============================================================================================
	private void incomingClientLocationRequest(Channel channel, String message)
	{//===============================================================================================


		String ip = channel.remoteAddress().toString();

		writeCompressed(channel,BobNet.Client_Location_Response+getCityFromIP(ip)+BobNet.endline);

	}




	//===============================================================================================
	public void sendTellClientTheirSessionWasLoggedOnSomewhereElseAndCloseChannel(long userID)
	{//===============================================================================================

		if(BobNet.debugMode==false)
		{
			BobsGameClient check = clientsByUserID.get(userID);
			if(check!=null)
			{
				if(check.channel.isActive())
				{

					clientsByChannel.remove(check.channel);
					clientsByUserID.remove(check.userID);
					if(check.facebookID.length()>0)clientsByFacebookID.remove(check.facebookID);

					ChannelFuture cf = writeFuture(check.channel,BobNet.Tell_Client_Their_Session_Was_Logged_On_Somewhere_Else+BobNet.endline);
					cf.addListener(new ChannelCloseListener());
				}
			}
		}

	}


	//===============================================================================================
	public class ChannelCloseListener implements ChannelFutureListener
	{//===============================================================================================
		@Override
		public void operationComplete(ChannelFuture f) throws Exception
		{
			Channel c = f.channel();
			c.close();
		}
	}











	//===============================================================================================
	private void incomingLoginRequest(Channel channel, String message)
	{//===============================================================================================

		String s = message;
		//s = s.substring(0,s.indexOf(BobNet.endline));
		//log.debug("incomingLoginRequest: "+s);

		String userNameOrEmailAddress = "";
		String password = "";

		//LoginRequest:`emailAddress`,`password`
		//OR
		//LoginRequest:`emailAddress`,`password`,statsBlob



		s = s.substring(s.indexOf(":")+1);//`userNameOrEmailAddress`,`password`,statsBlob
		s = s.substring(s.indexOf("`")+1);//userNameOrEmailAddress`,`password`,statsBlob
		userNameOrEmailAddress = s.substring(0,s.indexOf("`"));//userNameOrEmailAddress


		s = s.substring(s.indexOf("`")+3);//skip `,` //password`,statsBlob
		password = s.substring(0,s.indexOf("`"));//password
		s = s.substring(s.indexOf("`")+1);//,statsBlob OR //
		s = s.substring(s.indexOf(",")+1);
		String clientInfo = "";
		if(s.length()>BobNet.endline.length())clientInfo=s;

		userNameOrEmailAddress = userNameOrEmailAddress.trim();
		if(userNameOrEmailAddress.length() == 0)return;

		password = password.trim();
		if(password.length() == 0)return;

		userNameOrEmailAddress = userNameOrEmailAddress.toLowerCase();

		String queryString = "";

		if(userNameOrEmailAddress.contains("@"))
		{
			queryString = "SELECT " +
					"accountVerified , " +
					"accountCreatedTime , " +
					"passwordHash , " +
					"userID , " +
					"userName , " +
					"emailAddress , " +
					"facebookID , " +
					"firstLoginTime , " +
					"timesLoggedIn , " +
					"firstIP " +
					"FROM accounts WHERE emailAddress = ?";
		}
		else
		{
			queryString = "SELECT " +
					"accountVerified , " +
					"accountCreatedTime , " +
					"passwordHash , " +
					"userID , " +
					"userName , " +
					"emailAddress , " +
					"facebookID , " +
					"firstLoginTime , " +
					"timesLoggedIn , " +
					"firstIP " +
					"FROM accounts WHERE userName = ?";
		}


		String sessionToken = createRandomHash();

		BobsGameClient c = null;
		boolean loggedIn = false;


		Connection databaseConnection = openAccountsDBOnAmazonRDS();
		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}


		ResultSet resultSet = null;
		PreparedStatement ps = null;

		try
		{
			ps = databaseConnection.prepareStatement(
					queryString);

			ps.setString(1, userNameOrEmailAddress);
			resultSet = ps.executeQuery();

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());closeDBConnection(databaseConnection);return;}



		int accountVerified_DB = -1;
		long accountCreatedTime_DB = -1;
		String passwordHash_DB = "";
		long userID_DB = -1;
		String userName_DB = "";
		String emailAddress_DB = "";
		String facebookID_DB = "";
		long firstLoginTime_DB = -1;
		int timesLoggedIn_DB = -1;
		String firstIP_DB = "";


		try
		{

			if(resultSet.next())
			{

				accountVerified_DB = resultSet.getInt("accountVerified");
				accountCreatedTime_DB = resultSet.getLong("accountCreatedTime");
				passwordHash_DB = resultSet.getString("passwordHash");
				userID_DB = resultSet.getLong("userID");
				userName_DB = resultSet.getString("userName");
				emailAddress_DB = resultSet.getString("emailAddress");
				facebookID_DB = resultSet.getString("facebookID");
				firstLoginTime_DB = resultSet.getLong("firstLoginTime");
				timesLoggedIn_DB = resultSet.getInt("timesLoggedIn");
				firstIP_DB = resultSet.getString("firstIP");

				if(passwordHash_DB==null)passwordHash_DB="";
				if(facebookID_DB==null)facebookID_DB="";
				if(firstIP_DB==null)firstIP_DB="";


				resultSet.close();
				ps.close();


			}
			else
			{
				resultSet.close();
				ps.close();

			}

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());closeDBConnection(databaseConnection);return;}

		closeDBConnection(databaseConnection);

//				if(accountVerified_DB==0)
//				{
//					//account wasn't verified.
//					//log.debug("Account not verified for email:"+emailAddress);
//				}
//				else
		{


			String passwordHash = hashPassword(password, accountCreatedTime_DB);
			if(passwordHash_DB.length()>0 && passwordHash.equals(passwordHash_DB))
			{

				loggedIn = true;

				c = clientsByUserID.get(userID_DB);
				if(c==null)
				{
					c = new BobsGameClient();
					c.channel = channel;
					c.startTime = System.currentTimeMillis();
					c.encryptionKey = createRandomHash();
					c.userID = userID_DB;
					c.facebookID = facebookID_DB;
					c.emailAddress = emailAddress_DB;
					c.userName = userName_DB;

					clientsByChannel.put(channel, c);
					clientsByUserID.put(c.userID,c);
					if(c.userName.length()>0)clientsByUserName.put(c.userName,c);
					if(c.emailAddress.length()>0)clientsByEmailAddress.put(c.emailAddress,c);
					if(c.facebookID.length()>0)clientsByFacebookID.put(c.facebookID,c);

				}
				else
				{

					//check to see if the user is already connected to this server
					if(c.channel!=channel)
					{
						//they must have two clients open
						//log the other one off.
						if(c.channel.isActive())
						{
							sendTellClientTheirSessionWasLoggedOnSomewhereElseAndCloseChannel(c.userID);
						}
					}

					clientsByChannel.remove(c.channel);
					channelsByClient.remove(c);

					c.channel = channel;

					clientsByChannel.put(channel, c);
					channelsByClient.put(c,channel);
				}

				long firstLoginTime = firstLoginTime_DB;
				if(firstLoginTime==0)firstLoginTime = c.startTime;

				int timesLoggedIn = timesLoggedIn_DB;
				timesLoggedIn++;

				String firstIP = firstIP_DB;
				if(firstIP.length()==0)firstIP = ""+channel.remoteAddress().toString();





				//then send the sessionToken back to the client, which sends it with each update and request along with userID.
				//ArrayList<ChannelFuture> futures =

				writeCompressed(channel,BobNet.Login_Response+"Success,"+c.userID+",`"+sessionToken+"`"+BobNet.endline);

//						for(int i=0;i<futures.size();i++)
//						{
//							ChannelFuture f = futures.get(i);
//
//							f.awaitUninterruptibly();
//
//						}


				databaseConnection = openAccountsDBOnAmazonRDS();
				if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}
				try
				{
					//store this session token hash in the database, so when the client drops or reconnects later it is validated.
					ps = databaseConnection.prepareStatement(
							"UPDATE accounts SET " +
							"sessionToken = ? , " +
							"encryptionKey = ? , " +
							"firstLoginTime = ? , " +
							"lastLoginTime = ? , " +
							"lastSeenTime = ? , " +
							"timesLoggedIn = ? , " +
							"firstIP = ? , " +
							"lastIP = ? , " +
							"isOnline = ? " +
							"WHERE userID = ?");

					int i=0;
					ps.setString(++i, sessionToken);//sessionToken
					ps.setString(++i, c.encryptionKey);//encryptionKey
					ps.setLong(++i, firstLoginTime);//firstLoginTime
					ps.setLong(++i, c.startTime);//lastLoginTime
					ps.setLong(++i, c.startTime);//lastSeenTime
					ps.setInt(++i, timesLoggedIn);//timesLoggedIn
					ps.setString(++i, firstIP);//firstIP
					ps.setString(++i, ""+channel.remoteAddress().toString());//lastIP
					ps.setInt(++i, 1);//isOnline
					ps.setLong(++i, userID_DB);//emailAddress
					ps.executeUpdate();

					ps.close();
				}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());closeDBConnection(databaseConnection);return;}

				closeDBConnection(databaseConnection);



				//tell all other servers to close connection if they are logged in, go through channels here and close channel if they are logged in
				ServerMain.indexClientTCP.send_INDEX_User_Logged_On_This_Server_Log_Them_Off_Other_Servers(c.userID);



				//DONE: after login, the client should request the game save, the items/games, the flag values, and the dialoguedone values (included in game save now)

				incomingInitialGameSaveRequest(channel, message);


				//sendAllUserStatsGameStatsAndLeaderBoardsToClient(c);


				//tell friends we are online (happens in friend list request)
				//send this client online friends list request
				incomingOnlineFriendsListRequest(channel, message);



				// refresh facebook friends, send online friends list
				if(c.facebookID.length()>0)
				{
					//incomingUpdateFacebookAccountInDBRequest(channel, message);
					//incomingOnlineFriendsListRequest(channel, message);
				}


				//----------------------------------
				//store stats to dreamhost stats DB
				//----------------------------------

//						ClientStats stats = new ClientStats();
//						//client optionally send machine stats with the login request, have option to skip this
//						if(clientInfo.length()>0)stats.decode(clientInfo);//this decodes the parsed off clientInfo string into the clientConnection variables
//						//log.debug(c.encode());
//						stats.sessionToken = sessionToken;
//						{
//							Connection dreamhostSQLConnection = openDreamhostSQLDB();
//							if(dreamhostSQLConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}
//							//it should also create a new entry in the connections DB with the client stats.
//							try
//							{
//								PreparedStatement dreamhostPS = stats.getInsertStatement(dreamhostSQLConnection, emailAddress_DB, c, channel.remoteAddress().toString());
//								dreamhostPS.executeUpdate();
//
//								dreamhostPS.close();
//
//							}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());}
//							closeDBConnection(dreamhostSQLConnection);
//
//						}

			}
			else
			{
				//wrong password
				//log.debug("Wrong password for email:"+emailAddress);
			}
		}






		if(loggedIn==false)
		{
			writeCompressed(channel,BobNet.Login_Response+"Failed"+BobNet.endline);
			return;
		}





	}

	//===============================================================================================
	/**
	 * This should happen when the client has a cookie with a sessionToken set, which should happen when the client either drops the connection or closes the tab and logs in later.
	 */
	private void incomingReconnectRequest(Channel channel, String message)
	{//===============================================================================================

		//this should only ever happen when a client drops from a server (or closes the game and still has a cookie set)
		//the server should connect to the database, get the last known session token for the userID and make sure they match.

		//if they don't, tell the client to log out, say "sorry, your session has expired. please log in again."
		//and log out of the webpage as well, and refresh the webpage. this should go back to the login screen.
		//each new session on any computer would create a new session token and override the existing one on the database,
		//causing this to happen on any other computers they are logged into.

		String s = message;
		//s = s.substring(0,s.indexOf(BobNet.endline));

		long userID = -1;
		String sessionToken = "";
		//ReconnectRequest:`userID`,`sessionToken`
		//OR
		//ReconnectRequest:`userID`,`sessionToken`,statsBlob
		s = s.substring(s.indexOf(":")+1);//`userID`,`sessionToken`,statsBlob
		s = s.substring(s.indexOf("`")+1);//userID`,`sessionToken`,statsBlob
		try{userID = Long.parseLong(s.substring(0,s.indexOf("`")));}catch(Exception ex){log.warn("userID not an long?");return;}//userID
		s = s.substring(s.indexOf("`")+3);//skip `,` //sessionToken`,statsBlob
		sessionToken = s.substring(0,s.indexOf("`"));//sessionToken
		s = s.substring(s.indexOf("`")+1);//,statsBlob OR //
		s = s.substring(s.indexOf(",")+1);
		String clientInfo = "";
		if(s.length()>BobNet.endline.length())clientInfo=s;


		if(userID==-1){log.warn("userID -1");return;}

		sessionToken = sessionToken.trim();
		if(sessionToken.length() == 0){log.warn("No sessionToken for userID:"+userID);return;}




		boolean loggedIn = false;



		Connection databaseConnection = openAccountsDBOnAmazonRDS();
		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}


		ResultSet resultSet = null;
		PreparedStatement ps = null;


		try
		{
			ps = databaseConnection.prepareStatement(
					"SELECT " +
					"sessionToken , " +
					"userName , " +
					"emailAddress , " +
					"encryptionKey , " +
					"facebookID , " +
					"timesLoggedIn " +
					"FROM accounts WHERE userID = ?");


			ps.setLong(1, userID);
			resultSet = ps.executeQuery();

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());closeDBConnection(databaseConnection);return;}


			//TODO: could cut DB reads in half by storing the gameSave for the clientConnection here until the client requests initialGameSave
			//but if the client is reconnecting it will never ask for initialGameSave
			//so could null the gameSave object here after the client requests an update
			//or could have reconnect and loginWithSessionToken different requests

		String sessionToken_DB = "";
		String userName_DB = "";
		String emailAddress_DB = "";
		String encryptionKey_DB = "";
		String facebookID_DB = "";
		int timesLoggedIn_DB = -1;

		try
		{

			if(resultSet.next())
			{

				sessionToken_DB = resultSet.getString("sessionToken");
				userName_DB = resultSet.getString("userName");
				emailAddress_DB = resultSet.getString("emailAddress");
				encryptionKey_DB = resultSet.getString("encryptionKey");
				facebookID_DB = resultSet.getString("facebookID");
				timesLoggedIn_DB = resultSet.getInt("timesLoggedIn");

				if(sessionToken_DB==null)sessionToken_DB="";
				if(userName_DB==null)userName_DB="";
				if(emailAddress_DB==null)emailAddress_DB="";
				if(encryptionKey_DB==null)encryptionKey_DB="";
				if(facebookID_DB==null)facebookID_DB="";

				resultSet.close();
				ps.close();

			}
			else
			{
				resultSet.close();
				ps.close();

			}

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();closeDBConnection(databaseConnection);return;}

		closeDBConnection(databaseConnection);


		if(sessionToken_DB.length()>0 && sessionToken.equals(sessionToken_DB))
		{

			loggedIn = true;


			BobsGameClient c = clientsByUserID.get(userID);
			if(c==null)
			{
				c = new BobsGameClient();
				c.channel = channel;
				c.startTime = System.currentTimeMillis();
				c.encryptionKey = createRandomHash();

				c.userID = userID;
				c.userName = userName_DB;
				c.emailAddress = emailAddress_DB;
				c.facebookID = facebookID_DB;

				clientsByChannel.put(channel, c);
				clientsByUserID.put(c.userID,c);
				if(c.emailAddress.length()>0)clientsByEmailAddress.put(c.emailAddress,c);
				if(c.userName.length()>0)clientsByUserName.put(c.userName,c);
				if(c.facebookID.length()>0)clientsByFacebookID.put(c.facebookID,c);
			}
			else
			{

				//check to see if the user is already connected to this server
				if(c.channel!=channel)
				{
					//they must have two clients open
					//log the other one off.
					if(c.channel.isActive())
					{
						sendTellClientTheirSessionWasLoggedOnSomewhereElseAndCloseChannel(c.userID);
					}
				}

				clientsByChannel.remove(c.channel);
				channelsByClient.remove(c);

				c.channel = channel;

				clientsByChannel.put(channel, c);
				channelsByClient.put(c,channel);


			}

			//if there is no encryption key in the database, use the random one we generated just now (this should never happen but who knows)
			if(encryptionKey_DB==null||encryptionKey_DB.length()==0)
			{
				encryptionKey_DB = c.encryptionKey;
			}

			//set encryption key to the last known one, the user may have dropped and reconnected during gameplay.
			c.encryptionKey = encryptionKey_DB;


			int timesLoggedIn = timesLoggedIn_DB;
			timesLoggedIn++;





			//then send the session token back to the client, which sends it with each update and request along with userID.
			//ArrayList<ChannelFuture> futures =

			writeCompressed(channel,BobNet.Reconnect_Response+"Success,"+c.userID+",`"+sessionToken+"`"+BobNet.endline);

//					for(int i=0;i<futures.size();i++)
//					{
//						ChannelFuture f = futures.get(i);
//
//						f.awaitUninterruptibly();
//
//					}

			databaseConnection = openAccountsDBOnAmazonRDS();
			if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}
			try
			{
				ps = databaseConnection.prepareStatement(
						"UPDATE accounts SET " +
						"encryptionKey = ? , " +
						"lastSeenTime = ? , " +
						"timesLoggedIn = ? , " +
						"lastIP = ? , " +
						"isOnline = ? " +
						"WHERE userID = ?");

				int i=0;
				ps.setString(++i, c.encryptionKey);//encryptionKey
				ps.setLong(++i, c.startTime);//lastSeenTime
				ps.setInt(++i, timesLoggedIn);//timesLoggedIn
				ps.setString(++i, ""+channel.remoteAddress().toString());//lastIP
				ps.setInt(++i, 1);//isOnline
				ps.setLong(++i, userID);//userID
				ps.executeUpdate();

				ps.close();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());closeDBConnection(databaseConnection); return;}

			closeDBConnection(databaseConnection);


			//tell all other servers to close connection if they are logged in, go through channels here and close channel if they are logged in
			ServerMain.indexClientTCP.send_INDEX_User_Logged_On_This_Server_Log_Them_Off_Other_Servers(c.userID);



			incomingInitialGameSaveRequest(channel, message);

			//sendAllUserStatsGameStatsAndLeaderBoardsToClient(c);
			//tell friends we are online (happens in friend list request)
			//send this client online friends list request
			incomingOnlineFriendsListRequest(channel, message);

			// refresh facebook friends, send online friends list
			if(c.facebookID.length()>0)
			{
				//incomingUpdateFacebookAccountInDBRequest(channel, message);
				//incomingOnlineFriendsListRequest(channel, message);
			}



			//----------------------------------
			//store stats to dreamhost stats DB
			//----------------------------------

//					ClientStats stats = new ClientStats();
//
//					//client optionally send machine stats with the login request, have option to skip this
//					if(clientInfo.length()>0)stats.decode(clientInfo);//this decodes the parsed off clientInfo string into the ClientConnection variables
//
//					//log.debug(c.encode());
//					stats.sessionToken = sessionToken;
//
//					//it should also create a new entry in the connections DB with the client stats.
//					{
//						Connection dreamhostSQLConnection = openDreamhostSQLDB();
//						if(dreamhostSQLConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}
//						//it should also create a new entry in the connections DB with the client stats.
//						try
//						{
//							PreparedStatement dreamhostPS = stats.getInsertStatement(dreamhostSQLConnection, emailAddress_DB, c, channel.remoteAddress().toString());
//							dreamhostPS.executeUpdate();
//
//							dreamhostPS.close();
//
//						}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());}
//						closeDBConnection(dreamhostSQLConnection);
//
//					}

		}
		else
		{

			log.debug("Wrong sessionToken for userID:"+userID);
		}






		if(loggedIn==false)
		{
			writeCompressed(channel,BobNet.Reconnect_Response+"Failed"+BobNet.endline);
			return;
		}


	}



	//===============================================================================================
	private int loginWithFacebookIDAndAccessToken(Channel channel, String message, String facebookID, String facebookAccessToken, String clientInfo, String facebookEmail)
	{//===============================================================================================



		int retVal = -1;

		//-1 error
		//0 could not find account
		//1 success



		//-----------------------------
		//FIRST
		//see if their account exists
		//then send them their userID and sessionToken, all done.

		//check for EMAIL ADDRESS too!


		String sessionToken = createRandomHash();


		BobsGameClient c = null;

		Connection databaseConnection = openAccountsDBOnAmazonRDS();
		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return -1;}

		ResultSet resultSet = null;
		PreparedStatement ps = null;

		try
		{
			ps = databaseConnection.prepareStatement(
					"SELECT " +
					"accountVerified , " +
					"accountCreatedTime , " +
					"passwordHash , " +
					"userID , " +
					"userName , " +
					"emailAddress , " +
					"firstLoginTime , " +
					"timesLoggedIn , " +
					"firstIP " +
					"FROM accounts WHERE facebookID = ? OR emailAddress = ?"); // notice I am using OR emailaddress

			ps.setString(1, facebookID);
			ps.setString(2, facebookEmail);
			resultSet = ps.executeQuery();

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

		try
		{

			if(resultSet.next())
			{

				retVal = 1;

				long userID_DB = resultSet.getLong("userID");
				long firstLoginTime_DB = resultSet.getLong("firstLoginTime");
				int timesLoggedIn_DB = resultSet.getInt("timesLoggedIn");
				String firstIP_DB = resultSet.getString("firstIP");
				String userName_DB = resultSet.getString("userName");
				String emailAddress_DB = resultSet.getString("emailAddress");

				if(firstIP_DB==null)firstIP_DB="";
				if(userName_DB==null)userName_DB="";
				if(emailAddress_DB==null)emailAddress_DB="";

				resultSet.close();
				ps.close();
				closeDBConnection(databaseConnection);

				c = clientsByUserID.get(userID_DB);
				if(c==null)
				{
					c = new BobsGameClient();
					c.channel = channel;
					c.startTime = System.currentTimeMillis();
					c.encryptionKey = createRandomHash();
					c.userID = userID_DB;
					c.facebookID = facebookID;
					c.emailAddress = emailAddress_DB;
					c.userName = userName_DB;

					clientsByChannel.put(channel, c);
					clientsByUserID.put(c.userID,c);
					if(c.userName.length()>0)clientsByUserName.put(c.userName,c);
					if(c.emailAddress.length()>0)clientsByEmailAddress.put(c.emailAddress,c);
					if(c.facebookID.length()>0)clientsByFacebookID.put(c.facebookID,c);

				}
				else
				{
					//check to see if the user is already connected to this server
					if(c.channel!=channel)
					{
						//they must have two clients open
						//log the other one off.
						if(c.channel.isActive())
						{
							sendTellClientTheirSessionWasLoggedOnSomewhereElseAndCloseChannel(c.userID);
						}
					}

					clientsByChannel.remove(c.channel);
					channelsByClient.remove(c);

					c.channel = channel;

					clientsByChannel.put(channel, c);
					channelsByClient.put(c,channel);
				}



				long firstLoginTime = firstLoginTime_DB;
				if(firstLoginTime==0)firstLoginTime = c.startTime;

				int timesLoggedIn = timesLoggedIn_DB;
				timesLoggedIn++;

				String firstIP = firstIP_DB;
				if(firstIP.length()==0)firstIP = ""+channel.remoteAddress().toString();





				//tell all other servers to close connection if they are logged in, go through channels here and close channel if they are logged in
				ServerMain.indexClientTCP.send_INDEX_User_Logged_On_This_Server_Log_Them_Off_Other_Servers(c.userID);



				databaseConnection = openAccountsDBOnAmazonRDS();
				if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return -1;}
				try
				{
					//store this session token hash in the database, so when the client drops or reconnects later it is validated.
					ps = databaseConnection.prepareStatement(
							"UPDATE accounts SET " +
							"sessionToken = ? , " +
							"encryptionKey = ? , " +
							"firstLoginTime = ? , " +
							"lastLoginTime = ? , " +
							"lastSeenTime = ? , " +
							"timesLoggedIn = ? , " +
							"firstIP = ? , " +
							"lastIP = ? , " +
							"isOnline = ? , " +
							"facebookID = ? , " +
							"emailAddress = ? , " +
							"userName = ? " +
							"WHERE facebookID = ? OR emailAddress = ?");

					int i=0;
					ps.setString(++i, sessionToken);//sessionToken
					ps.setString(++i, c.encryptionKey);//encryptionKey
					ps.setLong(++i, firstLoginTime);//firstLoginTime
					ps.setLong(++i, c.startTime);//lastLoginTime
					ps.setLong(++i, c.startTime);//lastSeenTime
					ps.setInt(++i, timesLoggedIn);//timesLoggedIn
					ps.setString(++i, firstIP);//firstIP
					ps.setString(++i, ""+channel.remoteAddress().toString());//lastIP
					ps.setInt(++i, 1);//isOnline
					ps.setString(++i, facebookID);//
					ps.setString(++i, emailAddress_DB);//
					ps.setString(++i, userName_DB);//
					ps.setString(++i, facebookID);//facebookID
					ps.setString(++i, facebookEmail);//facebookEmail
					ps.executeUpdate();

					ps.close();
				}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}
				closeDBConnection(databaseConnection);


				//----------------------------------
				//store stats to dreamhost stats DB
				//----------------------------------

				ClientStats stats = new ClientStats();
				//client optionally send machine stats with the login request, have option to skip this
				if(clientInfo.length()>0)stats.decode(clientInfo);//this decodes the parsed off clientInfo string into the clientConnection variables
				//log.debug(c.encode());
				stats.sessionToken = sessionToken;
				{
					Connection dreamhostSQLConnection = openDreamhostSQLDB();
					if(dreamhostSQLConnection==null){log.error("DB ERROR: Could not open DB connection!");return -1;}
					//it should also create a new entry in the connections DB with the client stats.
					try
					{
						PreparedStatement dreamhostPS = stats.getInsertStatement(dreamhostSQLConnection, emailAddress_DB, c, channel.remoteAddress().toString());
						dreamhostPS.executeUpdate();

						dreamhostPS.close();

					}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}
					closeDBConnection(dreamhostSQLConnection);

				}


			}
			else
			{
				retVal=0;

				resultSet.close();
				ps.close();
				closeDBConnection(databaseConnection);
			}


		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}




		if(c!=null)
		{
			//then send the sessionToken back to the client, which sends it with each update and request along with userID.
			writeCompressed(channel,BobNet.Facebook_Login_Response+"Success,"+c.userID+",`"+sessionToken+"`"+BobNet.endline);
			return 1;
		}


		return retVal;

	}

	//===============================================================================================
	private void incomingFacebookLoginOrCreateAccountAndLoginRequest(Channel channel, String message)
	{//===============================================================================================


		String s = message;

		String facebookID = "";
		String facebookAccessToken = "";

		//FacebookLoginRequest:`facebookID`,`accessToken`
		//OR
		//FacebookLoginRequest:`facebookID`,`accessToken`,statsBlob



		s = s.substring(s.indexOf(":")+1);//`facebookID`,`accessToken`,statsBlob
		s = s.substring(s.indexOf("`")+1);//facebookID`,`accessToken`,statsBlob
		facebookID = s.substring(0,s.indexOf("`"));//facebookID
		s = s.substring(s.indexOf("`")+3);//skip `,` //accessToken`,statsBlob
		facebookAccessToken = s.substring(0,s.indexOf("`"));//accessToken
		s = s.substring(s.indexOf("`")+1);//,statsBlob OR //

		String clientInfo = "";
		if(s.length()>0)clientInfo=s.substring(s.indexOf(",")+1);

		facebookID = facebookID.trim();
		if(facebookID.length() == 0)return;
		facebookAccessToken = facebookAccessToken.trim();
		if(facebookAccessToken.length() == 0)return;





		FacebookClient facebookClient = null;
		String facebookEmail = "";
		//------------------------
		//log into facebook
		//------------------------
		try
		{
			facebookClient = new DefaultFacebookClient(facebookAccessToken, Version.VERSION_14_0);

			User user = facebookClient.fetchObject("me", User.class);

			facebookEmail = user.getEmail();

		}
		catch(Exception ex)
		{
			log.error("Error logging into facebook and getting facebook email for facebookID: "+facebookID+" fbAccessToken: "+facebookAccessToken+" "+ex.getMessage());

			writeCompressed(channel,BobNet.Facebook_Login_Response+"Failed"+BobNet.endline);

			ex.printStackTrace();
			return;

		}

		//extend the accessToken
		AccessToken accessToken = new DefaultFacebookClient(Version.VERSION_14_0).obtainExtendedAccessToken(PrivateCredentials.facebookAppID, PrivateCredentials.facebookAppSecret, facebookAccessToken);
		facebookAccessToken = accessToken.getAccessToken();




		//status:
		//-1 error
		//0 no account found
		//1 success

		int status = loginWithFacebookIDAndAccessToken(channel, message, facebookID, facebookAccessToken, clientInfo, facebookEmail);


		if(status==1)
		{
			//we were successful
		}
		else
		if(status==-1)
		{
			//there was an error, send failed.
			log.error("Facebook_Login_Response FacebookID: "+facebookID+" facebookAccessToken:"+facebookAccessToken);

			writeCompressed(channel,BobNet.Facebook_Login_Response+"Failed"+BobNet.endline);

		}
		if(status==0)
		{

			//generate password
			String password = "";
			List<String> myList = null;
			try
			{
				myList=new Sampler().sampler(4);
			}
			catch(FileNotFoundException e1)
			{
				e1.printStackTrace();
			}
			catch(IOException e1)
			{
				e1.printStackTrace();
			}
			for(int index = 0;index<myList.size();index++)
			{
				password = password + myList.get(index).trim()+" ";
			}
			password = password.trim();



			String verificationHash = createRandomHash();
			String sessionToken = createRandomHash();
			String encryptionKey = createRandomHash();

			//create account for them
			//make sure set account verified

			long accountCreatedTime = System.currentTimeMillis();
			String passwordHash = hashPassword(password,accountCreatedTime);


			Connection databaseConnection = openAccountsDBOnAmazonRDS();
			if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}
			PreparedStatement ps = null;
			try
			{
				ps = databaseConnection.prepareStatement(
						"INSERT INTO accounts " +
						"( " +
						"emailAddress , " +
						"passwordHash , " +
						"verificationHash , " +
						"accountVerified , " +
						"accountCreatedTime , " +
						"sessionToken , " +
						"encryptionKey , " +
						"firstLoginTime , " +
						"lastLoginTime , " +
						"lastSeenTime , " +
						"timesLoggedIn , " +
						"firstIP , " +
						"lastIP , " +
						"isOnline " +
						") " +
						"VALUES " +
						"( " +
						"? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ?" +
						") ");



				ps.setString(1, facebookEmail);
				ps.setString(2, passwordHash);
				ps.setString(3, verificationHash);
				ps.setInt(4, 1);
				ps.setLong(5, accountCreatedTime);
				ps.setString(6, sessionToken);
				ps.setString(7, encryptionKey);
				ps.setLong(8, accountCreatedTime);
				ps.setLong(9, accountCreatedTime);
				ps.setLong(10, accountCreatedTime);
				ps.setInt(11, 1);
				ps.setString(12, ""+channel.remoteAddress().toString());
				ps.setString(13, ""+channel.remoteAddress().toString());
				ps.setInt(14, 1);
				ps.executeUpdate();

				ps.close();
			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}
			closeDBConnection(databaseConnection);



			//now we can log in
			loginWithFacebookIDAndAccessToken(channel, message, facebookID, facebookAccessToken, clientInfo, facebookEmail);


			//send account created email with password
			sendFacebookAccountCreationEmail(facebookEmail,password);

			status = 1;

		}


		//update facebook stuff
		if(status==1)
		{
			if(facebookID.length()>0)
			{
				incomingUpdateFacebookAccountInDBRequest(channel, message);
				incomingOnlineFriendsListRequest(channel, message);
			}
		}

	}

	//===============================================================================================
	public class Sampler
	{//===============================================================================================

		public Sampler(){}
		public List<String> sampler (int reservoirSize) throws FileNotFoundException, IOException
		{
			String currentLine=null;
			//reservoirList is where our selected lines stored
			List <String> reservoirList= new ArrayList<String>(reservoirSize);
			// we will use this counter to count the current line number while iterating
			int count=0;

			Random ra = new Random();
			int randomNumber = 0;

			Scanner sc = new Scanner(ServerMain.class.getClassLoader().getResourceAsStream("1000.txt"));
			sc.useDelimiter("\n");

			while (sc.hasNext())
			{
				currentLine = sc.next();
				count ++;
				if (count<=reservoirSize)
				{
					reservoirList.add(currentLine);
				}
				else if ((randomNumber = (int) ra.nextInt(count))<reservoirSize)
				{
					reservoirList.set(randomNumber, currentLine);
				}
			}

			sc.close();


			return reservoirList;
		}
	}



	//===============================================================================================
	private void incomingPasswordRecoveryRequest(Channel channel, String message)
	{//===============================================================================================

		String s = message;
		String userNameOrEmailAddress = "";
		//PasswordRecoveryRequest:`usernameOrEmailAddress`
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(s.indexOf("`")+1);
		userNameOrEmailAddress = s.substring(0,s.indexOf("`"));
		userNameOrEmailAddress = userNameOrEmailAddress.trim();
		if(userNameOrEmailAddress.length() == 0)return;

		userNameOrEmailAddress = userNameOrEmailAddress.toLowerCase();

		String queryString = "";

		if(userNameOrEmailAddress.contains("@"))
		{
			queryString = "" +
					"SELECT " +
					"lastPasswordResetTime , " +
					"verificationHash , " +
					"userName , " +
					"emailAddress " +
					"FROM accounts WHERE emailAddress = ?";
		}
		else
		{
			queryString = "" +
					"SELECT " +
					"lastPasswordResetTime , " +
					"verificationHash , " +
					"userName , " +
					"emailAddress " +
					"FROM accounts WHERE userName = ?";
		}



		Connection databaseConnection = openAccountsDBOnAmazonRDS();
		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

		ResultSet resultSet = null;
		PreparedStatement ps = null;

		try
		{
			ps = databaseConnection.prepareStatement(queryString);

			ps.setString(1, userNameOrEmailAddress);
			resultSet = ps.executeQuery();

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}


		try
		{
			//check to see if email is already registered to account

			if(resultSet.next())
			{

				//if account exists, see if reset email was sent in the past 24 hours
				long lastPasswordResetTime = resultSet.getLong("lastPasswordResetTime");
				String verificationHash = resultSet.getString("verificationHash");
				String userName = resultSet.getString("userName");
				String emailAddress = resultSet.getString("emailAddress");
				//log.debug("lastPasswordResetTime:"+lastPasswordResetTime);

				if(verificationHash==null)verificationHash="";
				if(userName==null)userName="";
				if(emailAddress==null)emailAddress="";

				resultSet.close();
				ps.close();
				closeDBConnection(databaseConnection);



				long currentTime = System.currentTimeMillis();
				//log.debug("currentTime:"+currentTime);
				long oneHour = 1000*60*60;
				long oneDay = 1000*60*60*24;

				if(currentTime-lastPasswordResetTime>oneHour)
				{


					//String verificationHash = createRandomHash();

					databaseConnection = openAccountsDBOnAmazonRDS();
					if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}
					try
					{
						ps = databaseConnection.prepareStatement(
								"UPDATE accounts SET " +
								"verificationHash = ? , " +
								"lastPasswordResetTime = ? " +
								"WHERE emailAddress = ?");


						ps.setString(1, verificationHash);
						ps.setLong(2, currentTime);
						ps.setString(3, emailAddress);
						ps.executeUpdate();

						ps.close();

					}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}
					closeDBConnection(databaseConnection);


					sendPasswordResetEmail(userName, emailAddress,verificationHash);

				}
				else
				{
					//can only send password reset once every 24 hours.
				}

			}
			else
			{
				//account doesn't exist, do nothing. (don't tell the client the result.)

				resultSet.close();
				ps.close();
				closeDBConnection(databaseConnection);

			}


		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}



		writeCompressed(channel,BobNet.Password_Recovery_Response+"Done"+BobNet.endline);

	}


	//===============================================================================================
	private void incomingCreateAccountRequest(Channel channel, String message)
	{//===============================================================================================

		String s = message;
		String userName = "";
		String emailAddress = "";
		String password = "";
		//CreateAccountRequest:`emailAddress`,`password`
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(s.indexOf("`")+1);
		userName = s.substring(0,s.indexOf("`"));
		s = s.substring(s.indexOf("`")+3);//skip `,`
		emailAddress = s.substring(0,s.indexOf("`"));
		s = s.substring(s.indexOf("`")+3);//skip `,`
		password = s.substring(0,s.indexOf("`"));

		userName = userName.trim();
		if(userName.length() == 0){log.warn("No userName");return;}
		emailAddress = emailAddress.trim();
		if(emailAddress.length() == 0){log.warn("No emailAddress");return;}
		password = password.trim();
		if(password.length() == 0){log.warn("No password");return;}

		if(userName.length()>200)userName = userName.substring(0,200);
		if(emailAddress.length()>200)emailAddress = emailAddress.substring(0,200);

		userName = userName.toLowerCase();
		emailAddress = emailAddress.toLowerCase();

		Connection databaseConnection = openAccountsDBOnAmazonRDS();
		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

		ResultSet resultSet = null;
		PreparedStatement ps = null;

		try
		{
			ps = databaseConnection.prepareStatement(
					"SELECT " +
					"emailAddress " +
					"FROM accounts WHERE userName = ?");



			ps.setString(1, userName);
			resultSet = ps.executeQuery();

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

		boolean userNameExists = false;
		try
		{
			//check to see if userName is already registered to account

			if(resultSet.next())
			{
				String emailAddress_DB = resultSet.getString("emailAddress");

				if(emailAddress_DB==null)emailAddress_DB="";

				resultSet.close();
				ps.close();


				if(emailAddress_DB!=emailAddress)
				{
					userNameExists = true;
				}

			}
			else
			{

				resultSet.close();
				ps.close();


			}
		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

		if(userNameExists)
		{
			writeCompressed(channel,BobNet.Create_Account_Response+"UserNameTaken"+BobNet.endline);
			closeDBConnection(databaseConnection);
			return;
		}



		try
		{
			ps = databaseConnection.prepareStatement(
					"SELECT " +
					"accountVerified , " +
					"lastPasswordResetTime , " +
					"userName , " +
					"verificationHash " +
					"FROM accounts WHERE emailAddress = ?");



			ps.setString(1, emailAddress);
			resultSet = ps.executeQuery();

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}


		try
		{
			//check to see if email is already registered to account

			if(resultSet.next())
			{

				int accountVerified = resultSet.getInt("accountVerified");
				long lastPasswordResetTime = resultSet.getLong("lastPasswordResetTime");
				String verificationHash = resultSet.getString("verificationHash");
				String userName_DB = resultSet.getString("userName");

				if(verificationHash==null)verificationHash="";
				if(userName_DB==null)userName_DB="";

				resultSet.close();
				ps.close();


				if(accountVerified==1)
				{
					//if account is verified, send password recovery email
					//see if reset email was sent in the past 24 hours


					//log.debug("lastPasswordResetTime:"+lastPasswordResetTime);
					long currentTime = System.currentTimeMillis();
					//log.debug("currentTime:"+currentTime);
					long oneHour = 1000*60*60;
					long oneDay = 1000*60*60*24;
					if(currentTime-lastPasswordResetTime>oneHour)
					{

						//verificationHash = createRandomHash();
						try
						{
							ps = databaseConnection.prepareStatement(
									"UPDATE accounts SET " +
									"verificationHash = ? , " +
									"lastPasswordResetTime = ? " +
									"WHERE emailAddress = ?");


							ps.setString(1, verificationHash);
							ps.setLong(2, currentTime);
							ps.setString(3, emailAddress);
							ps.executeUpdate();

							ps.close();
						}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

						sendAccountAlreadyExistsEmail(userName_DB,emailAddress,verificationHash);

					}
					else
					{
						//can only send password reset once every 24 hours
					}
				}
				else //if(accountVerified==0)
				{
					//if account isnt verified, send verification link again, maybe they didnt get the email
					//if verification hash isnt set, set it.

					if(verificationHash==null || verificationHash.length()==0)
					{

						verificationHash = createRandomHash();


						resultSet.close();
						ps.close();

						try
						{
							ps = databaseConnection.prepareStatement(
									"UPDATE accounts SET " +
									"verificationHash = ? " +
									"WHERE emailAddress = ?");


							ps.setString(1, verificationHash);
							ps.setString(2, emailAddress);
							ps.executeUpdate();

							ps.close();
						}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}


					}

					sendAccountCreationEmail(userName_DB,emailAddress,verificationHash);
				}
			}
			else
			{

				resultSet.close();
				ps.close();

				long accountCreatedTime = System.currentTimeMillis();

				String passwordHash = hashPassword(password,accountCreatedTime);

				//set verification hash
				String verificationHash = createRandomHash();

				try
				{
					ps = databaseConnection.prepareStatement(
							"INSERT INTO accounts " +
							"( " +
							"userName , " +
							"emailAddress , " +
							"passwordHash , " +
							"verificationHash , " +
							"accountCreatedTime " +
							") " +
							"VALUES " +
							"( " +
							"? , ? , ? , ? , ?" +
							") ");


					int i=0;
					ps.setString(++i, userName);
					ps.setString(++i, emailAddress);
					ps.setString(++i, passwordHash);
					ps.setString(++i, verificationHash);
					ps.setLong(++i, accountCreatedTime);
					ps.executeUpdate();

					ps.close();
				}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

				sendAccountCreationEmail(userName, emailAddress,verificationHash);
			}


		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

		closeDBConnection(databaseConnection);

		writeCompressed(channel,BobNet.Create_Account_Response+"Success"+BobNet.endline);

		int year = Calendar.getInstance().get(Calendar.YEAR);
		int month = Calendar.getInstance().get(Calendar.MONTH)+1;
		int day = Calendar.getInstance().get(Calendar.DAY_OF_MONTH);

		String yearString = ""+year;
		String monthString = ""+month;
		if(monthString.length()==1)monthString = "0"+monthString;
		String dayString = ""+day;
		if(dayString.length()==1)dayString="0"+dayString;

		Connection dreamhostSQLConnection = openDreamhostSQLDB();
		if(dreamhostSQLConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}
		//it should also create a new entry in the email DB
		try
		{
			PreparedStatement dreamhostPS = dreamhostSQLConnection.prepareStatement
					(
					"INSERT INTO `bobsgame_com`.`wp_5394qp_es_emaillist` "+
					"("+
					"`es_email_id`, "+
					"`es_email_name`, "+
					"`es_email_mail`, "+
					"`es_email_status`, "+
					"`es_email_created`, "+
					"`es_email_viewcount`, "+
					"`es_email_group`, "+
					"`es_email_guid` "+
					") VALUES ( "+
					"NULL, '', ? , 'Single Opt In', '"+yearString+"-"+monthString+"-"+dayString+" 00:00:00', '0', 'Public', ? "+
					")"
					);


			int i=0;
			dreamhostPS.setString(++i, emailAddress);
			dreamhostPS.setString(++i, Utils.getStringMD5(emailAddress));
			dreamhostPS.executeUpdate();

			dreamhostPS.close();

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}
		closeDBConnection(dreamhostSQLConnection);
	}








	//===============================================================================================
	public String hashPassword(String password, long accountCreatedTime)
	{//===============================================================================================
		return Utils.getStringMD5(PrivateCredentials.passwordSalt+password+accountCreatedTime);
	}

	//===============================================================================================
	public String createRandomHash()
	{//===============================================================================================

		return Utils.getStringMD5(""+Math.random()+Math.random()+Math.random());
	}

	//===============================================================================================
	public void sendEmail(String emailAddress, String subject, String htmlContent, String textContent)
	{//===============================================================================================


		Properties props = System.getProperties();
		props.put("mail.smtp.starttls.enable", "true"); // added this line
		props.put("mail.smtp.host", PrivateCredentials.emailHost);
		props.put("mail.smtp.user", PrivateCredentials.emailUsername);
		props.put("mail.smtp.password", PrivateCredentials.emailPassword);
		props.put("mail.smtp.port", PrivateCredentials.emailPort);
		props.put("mail.smtp.auth", "true");
		//props.put("mail.smtp.ssl.enable", "true");

		//props.put("mail.mail.host", ServerMain.emailHost);

//		props.put("mail.transport.protocol", "smtps");
//		props.put("mail.smtps.ssl.enable", "true");
//
//		props.put("mail.smtps.auth", "true");
//
//		props.put("mail.smtps.host", ServerMain.emailHost);
//		props.put("mail.smtps.user", ServerMain.emailUsername);
//		props.put("mail.smtps.password", ServerMain.emailPassword);
//		props.put("mail.smtps.port", ServerMain.emailPort);

		//props.put("mail.debug", "true");

		Session session = Session.getInstance(props, new DefaultAuthenticator(PrivateCredentials.emailUsername,PrivateCredentials.emailPassword));

//		String[] to = {emailAddress}; // added this line
//
//
//		MimeMessage message = new MimeMessage(session);
//		try
//		{
//			try
//			{
//				message.setFrom(new InternetAddress("noreply@bobsgame.com","bob's game"));
//			}
//			catch(UnsupportedEncodingException e)
//			{
//				e.printStackTrace();
//			}
//
//			InternetAddress[] toAddress = new InternetAddress[1];
//
//			// To get the array of addresses
//			//for(int i = 0; i < to.length; i++)
//			//{ // changed from a while loop
//				//toAddress[i] = new InternetAddress(to[i]);
//				toAddress[0] = new InternetAddress(to[0]);
//			//}
//			//log.debug(Message.RecipientType.TO);
//
//			//or(int i = 0; i < toAddress.length; i++)
//			//{ // changed from a while loop
//				message.addRecipient(Message.RecipientType.TO, toAddress[0]);
//			//}
//
//			message.setSubject(subject);
//
//
//			// message.setText("Welcome to JavaMail");
//			// alternately, to send HTML mail:
//			message.setContent(htmlContent, "text/html");
//			message.saveChanges();
//
//			Transport transport = session.getTransport("smtp");
//			transport.connect(ServerMain.emailHost, ServerMain.emailUsername, ServerMain.emailPassword);
//			transport.sendMessage(message, message.getAllRecipients());
//			transport.close();
//		}
//		catch(AddressException e)
//		{
//			e.printStackTrace();
//		}
//		catch(MessagingException e)
//		{
//			e.printStackTrace();
//		}


		// Create the email message
		HtmlEmail email = new HtmlEmail();


		// embed the image and get the content id
		//URL url = new URL("http://www.apache.org/images/asf_logo_wide.gif");
		//String cid;

			try
			{
				//email.setDebug(true);
				email.setMailSession(session);
				email.setAuthentication(PrivateCredentials.emailUsername,PrivateCredentials.emailPassword);



//				email.setAuthenticator(new DefaultAuthenticator(ServerMain.emailUsername,ServerMain.emailPassword));
//				email.setHostName(ServerMain.emailHost);
//				email.setStartTLSEnabled(true);
//				//email.setSSL(true);
//				email.setSSLOnConnect(true);
//				email.setSmtpPort(ServerMain.emailPort);
//				email.setSslSmtpPort(""+ServerMain.emailPort);



				email.addTo(emailAddress);
				email.setFrom("noreply@bobsgame.com", "\"bob's game\"");
				email.setSubject(subject);

//				URL url= null;
//				try
//				{
//					url = new URL("https://bobsgame.com/images/welcome_to_bobs_game.gif");
//					email.embed(url, "welcome_to_bobs_game.gif");
//				}
//				catch(MalformedURLException e)
//				{
//					e.printStackTrace();
//				}


				// set the html message
				email.setHtmlMsg(htmlContent);

				// set the alternative message
				email.setTextMsg(textContent);

				// send the email
				email.send();

			}
			catch(EmailException e)
			{
				e.printStackTrace();
			}





	}


	//===============================================================================================
	public void sendAccountCreationEmail(String userName, String emailAddress, String verificationHash)
	{//===============================================================================================

		String subject = "Welcome to \"bob's game!\" Please verify your account.";

		String htmlContent =
						"<html><head></head><body><p>" +
						"Your email address was signed up for an account on <a href=\"http://bobsgame.com\">\"bob's game\"</a>.<br>" +
						"<br>" +
						"Your username is: "+userName +
						"<br>" +
						"Please verify your account by clicking here:<br>" +
						"<br>" +
						"<a href=\"http://bobsgame.com/verify.php?emailAddress="+emailAddress+"&verificationHash="+verificationHash+"\">http://bobsgame.com/verify.php?emailAddress="+emailAddress+"&verificationHash="+verificationHash+"</a><br>" +
						"<br>" +
						"<br>" +
						"If you didn't sign up, it means someone put your email address (perhaps by mistake) and you can safely ignore this email." +
						"</p></body></html>";

		String textContent =
				"Your email address was signed up for an account on http://bobsgame.com " +
						"\n"+
						"Your username is: "+userName+
						"\n"+
				"Please verify your account by clicking here: " +
				"\n" +
				"http://bobsgame.com/verify.php?emailAddress="+emailAddress+"&verificationHash="+verificationHash+
				"\n"+
				"\n"+
				"If you didn't sign up, it means someone put your email address (perhaps by mistake) and you can safely ignore this email.";

		sendEmail(emailAddress,subject,htmlContent,textContent);

		log.info("Verify account email sent to "+emailAddress+" for user "+userName);
	}

	//===============================================================================================
	public void sendFacebookAccountCreationEmail(String emailAddress, String password)
	{//===============================================================================================

		String subject = "Welcome to \"bob's game!\" Here is your (optional) passphrase.";

		String htmlContent =
						"<html><head></head><body><p>" +
						"Your email address was signed up (using Facebook) for an account on <a href=\"http://bobsgame.com\">\"bob's game\"</a>.<br>" +
						"Here is your randomly generated passphrase if you ever want to log in without Facebook. You can change it from inside the game if you want.<br>" +
						"<br>" +
						"Passphrase:\""+password+"\"<br>"+
						"<br>" +
						"<br>" +
						"</p></body></html>";

		String textContent =
				"Your email address was signed up (using Facebook) for an account on http://bobsgame.com " +
				"\n" +
				"Here is your randomly generated passphrase if you ever want to log in without Facebook. You can change it from inside the game if you want. " +
				"\n" +
				"Passphrase:\""+password+"\"<br>"+
				"\n"
				;

		sendEmail(emailAddress,subject,htmlContent,textContent);

		log.info("Verify account email sent to "+emailAddress);
	}

	//===============================================================================================
	public void sendPasswordResetEmail(String userName, String emailAddress, String verificationHash)
	{//===============================================================================================


		String subject = "Reset your password for \"bob's game.\"";

		String htmlContent =
						"<html><head></head><body><p>" +
						"Your password was requested to be changed for your account on <a href=\"http://bobsgame.com\">\"bob's game\"</a>.<br>" +
						"Reset your password by clicking here:<br>" +
						"<br>" +
						"<a href=\"http://bobsgame.com/resetPassword.php?emailAddress="+emailAddress+"&verificationHash="+verificationHash+"\">http://bobsgame.com/resetPassword.php?emailAddress="+emailAddress+"&verificationHash="+verificationHash+"</a><br>" +
						"<br>" +
						"<br>" +
						"Your username is: "+userName +
						"<br>" +
						"<br>" +
						"If you didn't request this, you can safely ignore this email and your password will remain unchanged." +
						"</p></body></html>";

		String textContent =
				"Your password was requested to be changed for your account on http://bobsgame.com " +
				"\n" +
				"Reset your password by clicking here: " +
				"\n" +
				"http://bobsgame.com/resetPassword.php?emailAddress="+emailAddress+"&verificationHash="+verificationHash+
				"\n"+
				"\n"+
				"Your username is: "+userName+
				"\n"+
				"\n"+
				"If you didn't request this, you can safely ignore this email and your password will remain unchanged.";

		sendEmail(emailAddress,subject,htmlContent,textContent);


		log.info("Password reset email sent to "+emailAddress+" for "+userName);
	}

	//===============================================================================================
	public void sendAccountAlreadyExistsEmail(String userName, String emailAddress, String verificationHash)
	{//===============================================================================================


		String subject = "You already have an account on \"bob's game!\".";

		String htmlContent =
						"<html><head></head><body><p>" +
						"Someone tried to create an account with your email address on <a href=\"http://bobsgame.com\">\"bob's game\"</a>, but you already have an account.<br>" +
						"If you forgot your password, click here to reset it:<br>" +
						"<br>" +
						"<a href=\"http://bobsgame.com/resetPassword.php?emailAddress="+emailAddress+"&verificationHash="+verificationHash+"\">http://bobsgame.com/resetPassword.php?emailAddress="+emailAddress+"&verificationHash="+verificationHash+"</a><br>" +
						"<br>" +
						"<br>" +
						"Your username is: "+userName +
						"<br>" +
						"<br>" +
						"If you didn't request this, you can safely ignore this email and your password will remain unchanged." +
						"</p></body></html>";


		String textContent =
				"Someone tried to create an account with your email address on http://bobsgame.com but you already have an account." +
				"\n" +
				"If you forgot your password, click here to reset it: " +
				"\n" +
				"http://bobsgame.com/resetPassword.php?emailAddress="+emailAddress+"&verificationHash="+verificationHash+
				"\n"+
				"\n"+
				"Your username is: "+userName+
				"\n"+
				"\n"+
				"If you didn't request this, you can safely ignore this email and your password will remain unchanged.";

		sendEmail(emailAddress,subject,htmlContent,textContent);

		log.debug("Account already exists email sent to "+emailAddress+" for "+userName);
	}



	//===============================================================================================
	public static GameSave getGameSaveFromDB(long userID)
	{//===============================================================================================

		//connect to sql database
		//look up account by account ID
		//verify session token
		//get all game save data
		//send back to client

		GameSave g = null;

		Connection databaseConnection = openAccountsDBOnAmazonRDS();
		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return null;}

		ResultSet resultSet = null;
		PreparedStatement ps = null;

		try
		{
			ps = databaseConnection.prepareStatement(
					"SELECT " +
					"* " +
					"FROM accounts WHERE userID = ?");



			ps.setLong(1, userID);
			resultSet = ps.executeQuery();

			if(resultSet.next())
			{
				g = new GameSave(resultSet);
			}

			resultSet.close();
			ps.close();
			closeDBConnection(databaseConnection);


		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();return null;}



		return g;
	}

	//===============================================================================================
	public BobsGameClient getClientConnectionByMessageEvent(Channel channel)
	{//===============================================================================================
		return getClientByChannel(channel);
	}

	//===============================================================================================
	public BobsGameClient getClientByChannel(Channel c)
	{//===============================================================================================
		try
		{
			return clientsByChannel.get(c);
		}
		catch(Exception e)
		{
			return null;
		}

	}

	//===============================================================================================
	public Channel getChannelByClient(BobsGameClient c)
	{//===============================================================================================
		try
		{
			return channelsByClient.get(c);
		}
		catch(Exception e)
		{
			return null;
		}

	}

	//===============================================================================================
	public long getUserIDByChannel(Channel channel)
	{//===============================================================================================
		//should be able to just get the userID from the current ClientConnection object in the ClientConnectionHashtable


		long userID = -1;
		BobsGameClient c = getClientByChannel(channel);
		if(c!=null)
		{
			userID = c.userID;
		}
		else
		{
			log.error("ERROR: ClientConnection wasn't found in the ClientConnectionHashtable for this connection in getUserIDByConnection()");
			return -1;
		}

		if(userID==-1)
		{
			log.error("ERROR: UserID wasn't initialized in the ClientConnection for this connection in getUserIDByConnection()");
			return -1;
		}

		return userID;
	}


	//===============================================================================================
	public GameSave getGameSaveByChannel(Channel channel)
	{//===============================================================================================

		long userID = getUserIDByChannel(channel);

		GameSave g = getGameSaveFromDB(userID);

		return g;

	}



	//===============================================================================================
	public GameSave decryptGameSave(BobsGameClient session, String encryptedGameSave)
	{//===============================================================================================

		//create gamesave by decrypting gameSave string by session token

		BasicTextEncryptor textEncryptor = new BasicTextEncryptor();
		textEncryptor.setPassword(session.encryptionKey);

		//log.info(session.encryptionKey);
		//log.info(encryptedGameSave);

		String plainText = textEncryptor.decrypt(encryptedGameSave);

		GameSave g = new GameSave();
		g.decodeGameSave(plainText);

		return g;

	}

	//===============================================================================================
	public String encryptGameSave(BobsGameClient session, GameSave g)
	{//===============================================================================================


		String s = g.encodeGameSave();

		BasicTextEncryptor textEncryptor = new BasicTextEncryptor();
		textEncryptor.setPassword(session.encryptionKey);

		String encryptedText = textEncryptor.encrypt(s);

		return encryptedText;

	}



	//===============================================================================================
	/**
	 * This should only be requested once per login.
	 * */
	private void incomingInitialGameSaveRequest(Channel channel, String message)
	{//===============================================================================================

		//String s = message;

		//InitialGameSaveRequest:`userID`,`sessionToken`
//		s = s.substring(s.indexOf(":")+1);//`userID`,`sessionToken`
//		s = s.substring(s.indexOf("`")+1);//userID`,`sessionToken`
//
//		long userID = Long.parseLong(s.substring(0,s.indexOf('`')));
//		s = s.substring(s.indexOf("`")+1);//,`sessionToken`
//		s = s.substring(s.indexOf("`")+1);//sessionToken`
//		String sessionToken = s.substring(0,s.indexOf('`'));

		//InitialGameSaveRequest:

		BobsGameClient c = getClientByChannel(channel);
		if(c==null)return;
		long userID = c.userID;
		if(userID==-1)return;

		GameSave g = getGameSaveByChannel(channel);


		if(g!=null)
		{
			//send encrypted game save blob based on server secret and session token

			String gameSave = g.encodeGameSave();
			String encryptedGameSave = encryptGameSave(c,g);

			writeCompressed(channel,BobNet.Initial_GameSave_Response+gameSave+BobNet.endline);
			writeCompressed(channel,BobNet.Encrypted_GameSave_Update_Response+"-1,"+encryptedGameSave+BobNet.endline);
		}
	}

	//===============================================================================================
	/**
	 * This should happen constantly, the server receives the encrypted game save blob, decrypts it, updates the value, sends it back, updates the DB.
	 * This is so the client keeps its own game save locally, and disconnecting from the server doesn't matter.
	 *
	 * The only thing the server needs to do at client login is get the gameSave from the database once, set the sessionToken in the DB, and then update the DB as needed during gameplay, passing the game save back and forth.
	 * So it is very write-heavy.
	 *
	 * The server keeps the sessionToken and userID in memory per connection. If the connection drops, the client reconnects to a new server, which then verifies the token from the last known session in the DB.
	 * If it matches, proceed as usual.
	 * */
	private void incomingGameSaveUpdateRequest(Channel channel, String message)
	{//===============================================================================================



		BobsGameClient c = getClientByChannel(channel);
		long userID = c.userID;
		if(userID==-1)return;

		String s = message;
		//GameSaveUpdateRequest:14,flagsSet:`3`,gameSave:encryptedGameSave
		//GameSaveUpdateRequest:requestId,variableName:`value`,gameSave:encryptedGameSave (send back so client knows which update received, they are queued)
		s = s.substring(s.indexOf(":")+1);//14,flagsSet:`3`,gameSave:encryptedGameSave
		int gameSaveID = -1;
		try{gameSaveID = Integer.parseInt(s.substring(0,s.indexOf(',')));}catch(NumberFormatException ex){ex.printStackTrace();ex.printStackTrace();return;}
		s = s.substring(s.indexOf(",")+1);//flagsSet:`3`,gameSave:encryptedGameSave


		class UpdateCommand
		{
			String variableName = "";
			String value = "";
			Object changedValue = null;
		}
		ArrayList<UpdateCommand> commands = new ArrayList<UpdateCommand>();

		//variableName:`value`,variableName:`value`,variableName:`value`,gameSave:encryptedGameSave
		while(s.startsWith("gameSave:")==false)
		{
			UpdateCommand u = new UpdateCommand();

			u.variableName = s.substring(0,s.indexOf(':'));
			s = s.substring(s.indexOf("`")+1);//`value`,
			u.value = s.substring(0,s.indexOf('`'));
			s = s.substring(s.indexOf("`")+2);//gameSave:encryptedGameSave or variableName:`value`,gameSave:encryptedGameSave

			commands.add(u);
		}
		//gameSave:encryptedGameSave
		s = s.substring(s.indexOf(":")+1);//encryptedGameSave
		String encryptedGameSave = s.substring(0,s.indexOf(":"));
		//decrypt game save blob
		GameSave g = decryptGameSave(c,encryptedGameSave);





		for(int i=0;i<commands.size();i++)
		{
			/**
			 * Most variables are simply set to the value sent in the string.
			 * Variables that are comma separated lists like Items, Games, Flags, DialogueDone, etc
			 * will either add or remove to the list, depending on whether the value is preceded with '-'
			 *
			 * so:
			 * realName:`bob` -> realName="bob";
			 * itemsHave:`113` -> itemsHave == "432,543,113,"
			 * itemsHave:`-113` -> itemsHave == "432,543,"
			 *
			 * */

			UpdateCommand u = commands.get(i);
			//update value
			u.changedValue = g.updateGameSaveValue(u.variableName,u.value);//returns the changed value in Object form so we can print it to the DB below.
			if(u.changedValue==null){log.warn("Error updating GameSave:"+u.variableName+","+u.value);}//returns null if variableName wasnt recognized or the value wasnt valid in conversion to the proper form. Integer.parseInt, etc.
			//if variableName isnt found in updating the gameSaveValue, it returns null.

			//TODO: could detect hax, store error in errorList for user. set u.variableName to errorList and value to errorList + "variableName,value"

		}



		//TODO: make sure this action is allowed (get item, etc), how to check this?


		//encrypt new game save
		String updatedEncryptedGameSave = encryptGameSave(c,g);

		//send back to client
		writeCompressed(channel,BobNet.Encrypted_GameSave_Update_Response+gameSaveID+","+updatedEncryptedGameSave+BobNet.endline);


		//now update the DB
		//update sql with previous save



		for(int i=0;i<commands.size();i++)
		{
			UpdateCommand u = commands.get(i);

			if(u.changedValue!=null)
			{

				Connection databaseConnection = openAccountsDBOnAmazonRDS();
				if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}
				try
				{
					PreparedStatement ps = databaseConnection.prepareStatement(
							"UPDATE accounts SET " +
							""+u.variableName+" = ? " +
							"WHERE userID = ?");



					ps.setString(1, u.changedValue.toString());
					ps.setLong(2, c.userID);
					ps.executeUpdate();

					ps.close();
				}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}
				closeDBConnection(databaseConnection);
			}
		}



	}



	//===============================================================================================
	//deprecated, client side geolookup using google/yahoo API now.
	@Deprecated
	private void incomingPostalCodeUpdateRequest(Channel channel, String message)
	{//===============================================================================================

		BobsGameClient c = getClientByChannel(channel);
		long userID = c.userID;
		if(userID==-1)return;
		//look up postal code in database, fill all this info in
		//PostalCodeUpdateRequest:isoCountryCode,`postalCode`,encryptedGameSave
		String s = message;
		s = s.substring(s.indexOf(":")+1);//isoCountryCode,`postalCode`,encryptedGameSave
		String isoCountryCode = s.substring(0,s.indexOf(','));
		s = s.substring(s.indexOf("`")+1);//postalCode`,encryptedGameSave
		String postalCode = s.substring(0,s.indexOf('`'));
		s = s.substring(s.indexOf(",")+1);//encryptedGameSave
		String encryptedGameSave = s;
		String countryName = GameSave.getCountryStringFromCode(isoCountryCode);


		//now we get placeName, stateName, lat, lon from DB
		String placeName = "";
		String stateName = "";
		float lat = 0;
		float lon = 0;

		{
			//update the DB
			Connection databaseConnection = openDreamhostSQLDB();
			if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

			PreparedStatement ps = null;
			ResultSet resultSet = null;

			try
			{
				ps = databaseConnection.prepareStatement(
						"SELECT * FROM geolookup.zipgeoworld WHERE " +
						"isoCountryCode = ? " +
						"AND postalCode = ?");



				ps.setString(1, isoCountryCode);
				ps.setString(2, postalCode);
				resultSet = ps.executeQuery();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

			try
			{

				if(resultSet.next())
				{
					placeName = resultSet.getString("placeName");
					stateName = resultSet.getString("state1");
					lat = resultSet.getFloat("lat");
					lon = resultSet.getFloat("lon");

					if(placeName==null)placeName="";
					if(stateName==null)stateName="";

				}

				resultSet.close();
				ps.close();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

			closeDBConnection(databaseConnection);
		}


		if(lat==0&&lon==0)
		{
			//TODO: if couldnt get results from DB query google API and yahoo API
			//TODO: if still can't get results, send back ERROR
			writeCompressed(channel,BobNet.Postal_Code_Update_Response+"ERROR"+BobNet.endline);
			return;
		}


		//decrypt game save blob
		GameSave g = decryptGameSave(c,encryptedGameSave);

		//now update the encryptedSave
		g.isoCountryCode = isoCountryCode;
		g.countryName = countryName;
		g.postalCode = postalCode;
		g.placeName = placeName;
		g.stateName = stateName;
		g.lat = lat;
		g.lon = lon;

		//send encryptedSave back to client
		String updatedEncryptedGameSave = encryptGameSave(c,g);

		//PostalCodeUpdateResponse:isoCountryCode,`postalCode`,`placeName`,`stateName`,`lat`,`lon`,encryptedGameSave
		writeCompressed(channel,BobNet.Postal_Code_Update_Response+isoCountryCode+",`"+postalCode+"`,`"+placeName+"`,`"+stateName+"`,`"+lat+"`,`"+lon+"`,"+updatedEncryptedGameSave+BobNet.endline);



		{
			//update the DB
			Connection databaseConnection = openAccountsDBOnAmazonRDS();
			if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

			try
			{
				PreparedStatement ps = databaseConnection.prepareStatement(
						"UPDATE accounts SET " +
						"isoCountryCode = ? , " +
						"postalCode = ? , " +
						"countryName = ? , " +
						"placeName = ? , " +
						"stateName = ? , " +
						"lat = ? , " +
						"lon = ? " +
						"WHERE userID = ?");


				ps.setString(1, isoCountryCode);
				ps.setString(2, postalCode);
				ps.setString(3, countryName);
				ps.setString(4, placeName);
				ps.setString(5, stateName);
				ps.setFloat(6, lat);
				ps.setFloat(7, lon);
				ps.setLong(8, c.userID);
				ps.executeUpdate();

				ps.close();


			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

			closeDBConnection(databaseConnection);
		}
	}


	//===============================================================================================
	private void incomingUpdateFacebookAccountInDBRequest(Channel channel, String message)
	{//===============================================================================================


		BobsGameClient c = getClientByChannel(channel);
		long userID = c.userID;
		if(userID==-1)return;



		//public String realName = "";
		//public long birthdayTime = 0;
		//public String facebookID = "";
		//public String googlePlusID = "";
		//setPostalCode(String s);



	//on browser, open this (for the first authorization with user input)

	// Request https://graph.facebook.com/oauth/authorize?client_id=MY_API_KEY& redirect_uri=http://www.facebook.com/connect/login_success.html& scope=publish_stream,create_event
	// Facebook will redirect you to http://www.facebook.com/connect/login_success.html? code=MY_VERIFICATION_CODE


		//in client, open the same thing and get MY_VERIFICATION_CODE

		// Request https://graph.facebook.com/oauth/authorize?client_id=MY_API_KEY& redirect_uri=http://www.facebook.com/connect/login_success.html& scope=publish_stream,create_event
		// Facebook will redirect you to http://www.facebook.com/connect/login_success.html? code=MY_VERIFICATION_CODE


		//in server, open this

	// Request https://graph.facebook.com/oauth/access_token?client_id=MY_API_KEY& redirect_uri=http://www.facebook.com/connect/login_success.html& client_secret=MY_APP_SECRET&code=MY_VERIFICATION_CODE
	// Facebook will respond with access_token=MY_ACCESS_TOKEN



		//we then send a json request using that token, and we should get back a friend list.
		//store them in the DB

		//UpdateFacebookAccountInDB
		//String s = message;
		//s = s.substring(s.indexOf(":")+1);





		String facebookAccessToken = "";

		{
			Connection databaseConnection = openAccountsDBOnAmazonRDS();
			if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

			ResultSet resultSet = null;
			PreparedStatement ps = null;

			try
			{
				ps = databaseConnection.prepareStatement(
						"SELECT " +
						"facebookAccessToken " +
						"FROM accounts WHERE userID = ?");


				ps.setLong(1, userID);
				resultSet = ps.executeQuery();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

			try
			{
				if(resultSet.next())
				{
					facebookAccessToken = resultSet.getString("facebookAccessToken");
					if(facebookAccessToken==null)facebookAccessToken="";
				}

				resultSet.close();
				ps.close();


			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

			closeDBConnection(databaseConnection);
		}

		//send back fail if we don't have a token yet.
		if(facebookAccessToken.length()==0)
		{
			writeCompressed(channel,BobNet.Update_Facebook_Account_In_DB_Response+"Failed"+BobNet.endline);
			return;
		}






		FacebookClient facebookClient = null;
		String facebookID = "";
		String facebookFriendsCSV = "";
		//------------------------
		//log into facebook
		//------------------------
		try
		{
			facebookClient = new DefaultFacebookClient(facebookAccessToken, Version.VERSION_14_0);

			User user = facebookClient.fetchObject("me", User.class);

			facebookID = user.getId();

			com.restfb.Connection<User> myFriends = facebookClient.fetchConnection("me/friends", User.class);
			for(int i = 0; i< myFriends.getData().size(); i++)
			{
				facebookFriendsCSV = facebookFriendsCSV+myFriends.getData().get(i).getId()+",";
			}
		}
		catch(Exception ex)
		{
			log.error("Error logging into facebook and getting facebook friends for userID: "+userID+" fbAccessToken: "+facebookAccessToken+" "+ex.getMessage());

			//access token was bad.
			//send back failure message
			writeCompressed(channel,BobNet.Update_Facebook_Account_In_DB_Response+"Failed"+BobNet.endline);

			//remove bad token from database.
			Connection databaseConnection = openAccountsDBOnAmazonRDS();
			if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

			try
			{
				PreparedStatement ps = databaseConnection.prepareStatement(
						"UPDATE accounts SET " +
						"facebookAccessToken = ? " +
						"WHERE userID = ?");



				ps.setString(1, "");
				ps.setLong(2, c.userID);
				ps.executeUpdate();

				ps.close();

			}catch (Exception dex){log.error("DB ERROR: "+dex.getMessage());return;}

			closeDBConnection(databaseConnection);

			ex.printStackTrace();

			return;
		}



		//extend the accessToken
		AccessToken accessToken = new DefaultFacebookClient(Version.VERSION_14_0).obtainExtendedAccessToken(PrivateCredentials.facebookAppID, PrivateCredentials.facebookAppSecret, facebookAccessToken);
		facebookAccessToken = accessToken.getAccessToken();




		//adding facebook to a normal account, check to make sure facebookID doesn't already exist.

		//so we should search the database for the facebookID
		//if it returns results we should compare to see if the userID matches the one that we have
		//if it doesn't match, we need to send back a custom failure message.
		{
			Connection databaseConnection = openAccountsDBOnAmazonRDS();
			if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

			ResultSet resultSet = null;
			PreparedStatement ps = null;
			try
			{
				ps = databaseConnection.prepareStatement(
						"SELECT " +
						"userID " +
						"FROM accounts WHERE facebookID = ?");

				ps.setString(1, facebookID);
				resultSet = ps.executeQuery();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

			try
			{
				if(resultSet.next())
				{
					long userID_DB = resultSet.getLong("userID");
					if(userID!=userID_DB)
					{
						writeCompressed(channel,BobNet.Update_Facebook_Account_In_DB_Response+"FailedIDAlreadyExists"+BobNet.endline);
						return;
					}
				}

				resultSet.close();
				ps.close();

				closeDBConnection(databaseConnection);
			}
			catch(Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

		}



		String facebookEmail = "";
		//String facebookBirthday = "";
		String facebookFirstName = "";
		String facebookLastName = "";
		String facebookGender = "";
		//String facebookLocale = "";
		//Double facebookTimeZone = 0.0;
		//String facebookUsername = "";
		//String facebookWebsite = "";
		//get as much info as we can
		//now check other extended permissions. these are not required, so failure is OK.
		try
		{
			facebookClient = new DefaultFacebookClient(facebookAccessToken, Version.VERSION_14_0);

			User user = facebookClient.fetchObject("me", User.class);

			facebookEmail = user.getEmail();
			//facebookBirthday = user.getBirthday();
			facebookFirstName = user.getFirstName();
			facebookLastName = user.getLastName();
			facebookGender = user.getGender();
			//facebookLocale = user.getLocale();
			//facebookTimeZone = user.getTimezone();
			//facebookUsername = user.getUsername();
			//facebookWebsite = user.getWebsite();

		}
		catch(Exception ex)
		{
			//we didn't get extended permissions, that's OK though.
			log.error(ex.getMessage());
			ex.printStackTrace();
		}

		//------------------------
		//update DB with friendsList, fbID, sessionToken
		//------------------------
		Connection databaseConnection = openAccountsDBOnAmazonRDS();
		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

		try
		{
			PreparedStatement ps = databaseConnection.prepareStatement(
					"UPDATE accounts SET " +
					"facebookID = ? , " +
					"facebookAccessToken = ? , " +
					"facebookFriends = ? , " +
					"facebookEmail = ? , " +
					//"facebookBirthday = ? , " +
					"facebookFirstName = ? , " +
					"facebookLastName = ? , " +
					"facebookGender = ? " +
					//"facebookLocale = ? , " +
					//"facebookTimeZone = ? , " +
					//"facebookUsername = ? , " +
					//"facebookWebsite = ? " +
					"WHERE userID = ?");

			int i=0;
			ps.setString(++i, facebookID);
			ps.setString(++i, facebookAccessToken);
			ps.setString(++i, facebookFriendsCSV);
			ps.setString(++i, facebookEmail);
			//ps.setString(++i, facebookBirthday);
			ps.setString(++i, facebookFirstName);
			ps.setString(++i, facebookLastName);
			ps.setString(++i, facebookGender);
			//ps.setString(++i, facebookLocale);
			//ps.setFloat(++i, facebookTimeZone.floatValue());
			//ps.setString(++i, facebookUsername);
			//ps.setString(++i, facebookWebsite);
			ps.setLong(++i, c.userID);
			ps.executeUpdate();

			ps.close();

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}


		closeDBConnection(databaseConnection);

		writeCompressed(channel,
								BobNet.Update_Facebook_Account_In_DB_Response+"Success:`"+
								facebookID+"`,`"+
								facebookAccessToken+"`,`"+
								facebookEmail+"`,`"+
								//facebookBirthday+"`,`"+
								facebookFirstName+"`,`"+
								facebookLastName+"`,`"+
								facebookGender+"`"+
								//facebookLocale+"`,`"+
								//facebookTimeZone.floatValue()+"`,`"+
								//facebookUsername+"`,`"+
								//facebookWebsite+"`"+
								BobNet.endline
								);



		//now that we have a facebookID lets update our clientHashtable
		if(facebookID.length()>0)clientsByFacebookID.put(facebookID,c);


	}




	//===============================================================================================
	private void incomingAddFriendByUserNameRequest(Channel channel, String message)
	{//===============================================================================================

		//this should access the DB and get a list of all the friends that are online


		BobsGameClient c = getClientByChannel(channel);
		long userID = c.userID;
		if(userID==-1)return;

		String s = message;

		String friendUserName = "";
		//AddFriendByUserNameRequest:`friendUserName`
		s = s.substring(s.indexOf(":")+1);//`userID`
		s = s.substring(s.indexOf("`")+1);//userID`
		friendUserName = s.substring(0,s.indexOf("`"));

		friendUserName = friendUserName.toLowerCase();
		if(friendUserName.contains(","))return;

		//first get our list of facebook friends, twitter friends, google+ friends, steam friends, etc.

		Connection databaseConnection = openAccountsDBOnAmazonRDS();
		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}


		ResultSet resultSet = null;
		PreparedStatement ps = null;

		try
		{
			ps = databaseConnection.prepareStatement(
					"SELECT " +
							"userName , " +
							"userNameFriends " +
					"FROM accounts WHERE userID = ?");
			ps.setLong(1, userID);
			resultSet = ps.executeQuery();

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

		String userNameFriendsCSV = "";
		String userName = "";
		try
		{
			if(resultSet.next())
			{
				userNameFriendsCSV = resultSet.getString("userNameFriends");
				userName = resultSet.getString("userName");
				if(userNameFriendsCSV==null)userNameFriendsCSV="";
				if(userName==null)userName="";
			}
			resultSet.close();
			ps.close();

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

		if(userNameFriendsCSV.startsWith(friendUserName+",") || userNameFriendsCSV.contains(","+friendUserName+",") || friendUserName.equals(userName))
		{
			writeCompressed(channel,BobNet.Add_Friend_By_UserName_Response+"Success"+BobNet.endline);
			closeDBConnection(databaseConnection);
			return;
		}

		//make sure friend username exists
		try
		{
			ps = databaseConnection.prepareStatement(
					"SELECT " +
							"userID " +
					"FROM accounts WHERE userName = ?");
			ps.setString(1, friendUserName);
			resultSet = ps.executeQuery();

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

		long friendUserID = 0;
		try
		{
			if(resultSet.next())
			{
				friendUserID = resultSet.getLong("userID");
			}

			resultSet.close();
			ps.close();

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

		if(friendUserID==0)
		{
			writeCompressed(channel,BobNet.Add_Friend_By_UserName_Response+"Failed"+BobNet.endline);
			closeDBConnection(databaseConnection);
			return;
		}

		if(friendUserID==userID)
		{
			writeCompressed(channel,BobNet.Add_Friend_By_UserName_Response+"Success"+BobNet.endline);
			closeDBConnection(databaseConnection);
			return;
		}

		//add new friend to csv if doesnt exist
		userNameFriendsCSV = userNameFriendsCSV+friendUserName+",";

		//add to database for you
		try
		{
			ps = databaseConnection.prepareStatement(
					"UPDATE accounts SET " +
					"userNameFriends = ? " +
					"WHERE userID = ?");
			ps.setString(1, userNameFriendsCSV);
			ps.setLong(2, userID);
			ps.executeUpdate();

			ps.close();
		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}


		//add to database for friend
		try
		{
			ps = databaseConnection.prepareStatement(
					"SELECT " +
							"userNameFriends " +
					"FROM accounts WHERE userID = ?");
			ps.setLong(1, friendUserID);
			resultSet = ps.executeQuery();

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

		String friendUserNameFriendsCSV = "";
		try
		{
			if(resultSet.next())
			{
				friendUserNameFriendsCSV = resultSet.getString("userNameFriends");
				if(friendUserNameFriendsCSV==null)friendUserNameFriendsCSV="";
			}
			resultSet.close();
			ps.close();
		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

		if(friendUserNameFriendsCSV.startsWith(userName+",")==false && friendUserNameFriendsCSV.contains(","+userName+",")==false)
		{
			//add new friend to csv if doesnt exist
			friendUserNameFriendsCSV = friendUserNameFriendsCSV+userName+",";

			//add to database for you
			try
			{
				ps = databaseConnection.prepareStatement(
						"UPDATE accounts SET " +
						"userNameFriends = ? " +
						"WHERE userID = ?");
				ps.setString(1, friendUserNameFriendsCSV);
				ps.setLong(2, friendUserID);
				ps.executeUpdate();

				ps.close();
			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}


		}

		writeCompressed(channel,BobNet.Add_Friend_By_UserName_Response+"Success"+BobNet.endline);

		//we should alert them all that we are online.
		ServerMain.indexClientTCP.send_INDEX_Tell_All_Servers_To_Tell_UserNames_That_UserID_Is_Online(userID,userNameFriendsCSV);
		ServerMain.indexClientTCP.send_INDEX_Tell_All_Servers_To_Tell_UserNames_That_UserID_Is_Online(friendUserID,friendUserNameFriendsCSV);

		closeDBConnection(databaseConnection);


		String onlineFriendUserIDsCSV = "";

		while(userNameFriendsCSV.length()>0)
		{
			String friend = userNameFriendsCSV.substring(0,userNameFriendsCSV.indexOf(","));
			userNameFriendsCSV = userNameFriendsCSV.substring(userNameFriendsCSV.indexOf(",")+1);

			BobsGameClient friendClient = clientsByUserName.get(friend);
			if(friendClient!=null)
			{

				//store onlineFriendIDs in a list to send back to our client
				String type = "userName";
				long friendID = friendClient.userID;
				onlineFriendUserIDsCSV = onlineFriendUserIDsCSV+type+":"+friendID+",";


				//notify friend we are online, they start pinging the stun server.
				writeCompressed(friendClient.channel,BobNet.Friend_Is_Online_Notification+type+":"+userID+BobNet.endline);
			}

		}

		//now we have a list of friends userIDs that are online right now.
		//send our list to our client which should start pinging all of the IPs to make connections.
		writeCompressed(channel,BobNet.Online_Friends_List_Response+onlineFriendUserIDsCSV+BobNet.endline);

	}



	//===============================================================================================
	private void incomingBobsGameGameTypesDownloadRequest(Channel channel, String message)
	{//===============================================================================================

		//this should access the DB and get a list of all the gametypes and game sequences
		//they are already zipped as text blob so just send them over

		BobsGameClient c = getClientByChannel(channel);

		long userID = -1;
		if(c!=null)userID = c.userID;
		//if(userID==-1)return;

		String s = message;





		Connection databaseConnection = openAccountsDBOnAmazonRDS();
		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

		ResultSet resultSet = null;
		PreparedStatement ps = null;

		for(int i=0;i<2;i++)
		{

			String type = "";

			if(i==0)type="gameTypes";
			if(i==1)type="gameSequences";

			try
			{
				ps = databaseConnection.prepareStatement(
						"SELECT " +
								"xml , " +
								"name , " +
								"uuid , " +
								"userName , " +
								"userID , " + //bigint 20
								"dateCreated , " +//bigint 30
								"lastModified , " +//bigint 30
								"howManyTimesUpdated , " +//int 11
								"upVotes , " +//bigint 20
								"downVotes , " +//bigint 20
								"usersVoted " +
						"FROM "+type);
				resultSet = ps.executeQuery();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}



			try
			{
				while(resultSet.next())
				{



					String xml = "";
					String name = "";
					String uuid = "";
					String creatorUserName = "";
					long creatorUserID = -1;
					long dateCreated = -1;
					long lastModified = -1;
					long howManyTimesUpdated = -1;
					long upVotes = -1;
					long downVotes = -1;
					String usersVotedCSV = "";

					xml = resultSet.getString("xml");
					name = resultSet.getString("name");
					uuid = resultSet.getString("uuid");
					creatorUserName = resultSet.getString("userName");
					creatorUserID = resultSet.getLong("userID");
					dateCreated = resultSet.getLong("dateCreated");
					lastModified = resultSet.getLong("lastModified");
					howManyTimesUpdated = resultSet.getLong("howManyTimesUpdated");
					upVotes = resultSet.getLong("upVotes");
					downVotes = resultSet.getLong("downVotes");
					usersVotedCSV = resultSet.getString("usersVoted");

					if(xml==null)xml="";
					if(name==null)name="";
					if(uuid==null)uuid="";
					if(creatorUserName==null)creatorUserName="";
					if(usersVotedCSV==null)usersVotedCSV="";


					String parseVotes = new String(usersVotedCSV);
					//ignore database upvote/downvote count because it's not accurate since you can change your vote, should remove it from DB
					//instead parse actual votes here

					upVotes = 0;
					downVotes = 0;

					//userID:up,
					while(parseVotes.contains(":"))
					{
						parseVotes = parseVotes.substring(parseVotes.indexOf(":")+1);
						String vote = parseVotes.substring(0,parseVotes.indexOf(","));
						parseVotes = parseVotes.substring(parseVotes.indexOf(",")+1);

						if(vote.equals("up"))
						{
							upVotes++;
						}

						if(vote.equals("down"))
						{
							downVotes++;
						}

					}


					//get this user's vote
					String userVote = "none";
					if(usersVotedCSV.startsWith(userID+":"))
					{
						usersVotedCSV = usersVotedCSV.substring(usersVotedCSV.indexOf(":")+1);
						userVote = usersVotedCSV.substring(0,usersVotedCSV.indexOf(","));
					}

					if(usersVotedCSV.contains(","+userID+":"))
					{
						usersVotedCSV = usersVotedCSV.substring(usersVotedCSV.indexOf(","+userID+":"));
						usersVotedCSV = usersVotedCSV.substring(usersVotedCSV.indexOf(":")+1);
						userVote = usersVotedCSV.substring(0,usersVotedCSV.indexOf(","));
					}





					//GameType:MD5:XML:userid:username:name:uuid:datecreated:lastmodified:howmanytimesupdated:upvotes:downvotes:haveyouvoted

					String responseMessage = ""+BobNet.Bobs_Game_GameTypesAndSequences_Download_Response;

					if(type.equals("gameTypes"))
					{
						responseMessage+="GameType:";
					}
					else
					if(type.equals("gameSequences"))
					{
						responseMessage+="GameSequence:";
					}
					else
					{
						log.error("Type not found");
						continue;
					}

					responseMessage+=
					Utils.getStringMD5(xml)+":"+
					xml+":"+
					creatorUserID+":"+
					"`"+creatorUserName+"`:"+
					"`"+name+"`:"+
					uuid+":"+
					dateCreated+":"+
					lastModified+":"+
					howManyTimesUpdated+":"+
					upVotes+":"+
					downVotes+":"+
					userVote+":";

					writeCompressed(channel,responseMessage+BobNet.endline);

				}
				resultSet.close();
				ps.close();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}
		}

		closeDBConnection(databaseConnection);







	}

	//===============================================================================================
	private void incomingBobsGameGameTypesUploadRequest(Channel channel, String message)
	{//===============================================================================================


		BobsGameClient c = getClientByChannel(channel);
		long userID = c.userID;
		if(userID==-1)return;
		String userName = c.userName;


		String s = message;
		s = s.substring(s.indexOf(":")+1);

		//GameType:XML:name:uuid

		String type = s.substring(0,s.indexOf(":"));
		s = s.substring(s.indexOf(":")+1);

		String xml = s.substring(0,s.indexOf(":"));
		s = s.substring(s.indexOf(":")+1);


		s = s.substring(s.indexOf("`")+1);
		String name = s.substring(0,s.indexOf("`"));
		s = s.substring(s.indexOf("`")+1);
		s = s.substring(s.indexOf(":")+1);

		String uuid = s.substring(0,s.indexOf(":"));
		s = s.substring(s.indexOf(":")+1);

		String dbName = "";
		if(type.equals("GameType"))
		{
			dbName = "gameTypes";
		}
		else
		if(type.equals("GameSequence"))
		{
			dbName = "gameSequences";
		}
		else
		{
			log.error("Could not parse type on incomingGameUpload: "+type+","+name+","+uuid);
			writeCompressed(channel,BobNet.Bobs_Game_GameTypesAndSequences_Upload_Response+"Failed: Could not parse data, please try again."+BobNet.endline);
			return;
		}


		long howManyTimesUpdated = 0;
		long lastUserID = -1;
		boolean exists = false;
		String oldXML = "";
		String history = "";
		String oldName = "";
		long oldLastModified = -1;


		Connection databaseConnection = openAccountsDBOnAmazonRDS();
		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}
		{
			ResultSet resultSet = null;
			PreparedStatement ps = null;

			//check to see if it exists
			try
			{
				ps = databaseConnection.prepareStatement(
						"SELECT " +
								"userID , " + //bigint 20
								"howManyTimesUpdated , " +//int 11
								"xml , " +//text
								"history , " +//text
								"name , " +//text
								"lastModified " +//long
						"FROM "+dbName+" WHERE uuid = ?");
				int i = 0;
				ps.setString(++i, uuid);
				resultSet = ps.executeQuery();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}


			try
			{
				if(resultSet.next())
				{
					exists = true;
					lastUserID = resultSet.getLong("userID");
					howManyTimesUpdated = resultSet.getLong("howManyTimesUpdated");
					oldXML = resultSet.getString("xml");
					history = resultSet.getString("history");
					oldName = resultSet.getString("name");
					oldLastModified = resultSet.getLong("lastModified");

					if(oldXML==null)oldXML = "";
					if(history==null)history = "";
					if(oldName==null)oldName = "";
				}

				resultSet.close();
				ps.close();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

		}

		if(exists)
		{

			howManyTimesUpdated++;

			if(lastUserID!=userID && userID != 1)//bob can edit anything
			{

				writeCompressed(channel,BobNet.Bobs_Game_GameTypesAndSequences_Upload_Response+"Failed: Already exists on server and you are not the creator."+BobNet.endline);
				closeDBConnection(databaseConnection);
				return;
			}

			long lastModified = System.currentTimeMillis();

			history = "" + oldName + ":" + oldLastModified + ":" + oldXML + ":\n" + history;

			try
			{
				PreparedStatement ps = databaseConnection.prepareStatement(
						"UPDATE "+dbName+" SET " +
						"xml = ? , " +
						"lastModified = ? , " +
						"howManyTimesUpdated = ? , " +
						"name = ? , " +
						"history = ? " +
						"WHERE uuid = ?");

				int i=0;
				ps.setString(++i, xml);
				ps.setLong(++i, lastModified);
				ps.setLong(++i, howManyTimesUpdated);
				ps.setString(++i, name);
				ps.setString(++i, history);
				ps.setString(++i, uuid);
				ps.executeUpdate();

				ps.close();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

			writeCompressed(channel,BobNet.Bobs_Game_GameTypesAndSequences_Upload_Response+"Success: Updated on server."+BobNet.endline);
			closeDBConnection(databaseConnection);
		}
		else
		{


			//rate limit creating new game types

			ResultSet resultSet = null;
			PreparedStatement ps = null;

			//get from accounts userID lastTimeCreatedGame
			try
			{
				ps = databaseConnection.prepareStatement(
						"SELECT " +
								"lastCreatedGameTime " +
						"FROM accounts WHERE userID = ?");
				ps.setLong(1, userID);
				resultSet = ps.executeQuery();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

			long lastCreatedGameTime = -1;
			try
			{
				if(resultSet.next())
				{
					lastCreatedGameTime = resultSet.getLong("lastCreatedGameTime");
				}
				resultSet.close();
				ps.close();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

			if(lastCreatedGameTime==-1)
			{
				writeCompressed(channel,BobNet.Bobs_Game_GameTypesAndSequences_Upload_Response+"Failed: Could not get last created time."+BobNet.endline);
				closeDBConnection(databaseConnection);
				return;
			}

			if(System.currentTimeMillis() < lastCreatedGameTime + 1000 * 60 * 10)//10 minutes
			{
				writeCompressed(channel,BobNet.Bobs_Game_GameTypesAndSequences_Upload_Response+"Failed: Created too soon, only once every 10 minutes."+BobNet.endline);
				closeDBConnection(databaseConnection);
				return;
			}



			long dateCreated = System.currentTimeMillis();

			try
			{
				ps = databaseConnection.prepareStatement(
						"INSERT INTO "+dbName+" " +
						"( " +
						"xml , " +
						"name , " +
						"uuid , " +
						"userName , " +
						"userID , " + //bigint 20
						"dateCreated , " +//bigint 30
						"lastModified , " +//bigint 30
						"history , " +//bigint 30
						"howManyTimesUpdated , " +//int 11
						"upVotes , " +//bigint 20
						"downVotes , " +//bigint 20
						"usersVoted " +
						") " +
						"VALUES " +
						"( " +
						"? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ?" +
						") ");


				int i=0;
				ps.setString(++i, xml);
				ps.setString(++i, name);
				ps.setString(++i, uuid);
				ps.setString(++i, userName);
				ps.setLong(++i, userID);
				ps.setLong(++i, dateCreated);
				ps.setLong(++i, dateCreated);
				ps.setString(++i, history);
				ps.setLong(++i, 0);
				ps.setLong(++i, 1);
				ps.setLong(++i, 0);
				ps.setString(++i, ""+userID+":up,");
				ps.executeUpdate();

				ps.close();
			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

			writeCompressed(channel,BobNet.Bobs_Game_GameTypesAndSequences_Upload_Response+"Success: Created"+BobNet.endline);
			closeDBConnection(databaseConnection);
		}




	}


	//===============================================================================================
	private void incomingBobsGameGameTypesVoteRequest(Channel channel, String message)
	{//===============================================================================================


		BobsGameClient c = getClientByChannel(channel);
		long userID = c.userID;
		if(userID==-1)return;
		//String userName = c.userName;


		String s = message;
		s = s.substring(s.indexOf(":")+1);

		//GameType:uuid:up

		String type = s.substring(0,s.indexOf(":"));
		s = s.substring(s.indexOf(":")+1);



		String uuid = s.substring(0,s.indexOf(":"));
		s = s.substring(s.indexOf(":")+1);

		String upOrDownString = s.substring(0,s.indexOf(":"));
		s = s.substring(s.indexOf(":")+1);

		if(upOrDownString.equals("up")==false && upOrDownString.equals("down")==false)
		{
			writeCompressed(channel,BobNet.Bobs_Game_GameTypesAndSequences_Vote_Response+"Failed: Vote string was not valid."+BobNet.endline);
			return;
		}

		String dbName = "";
		if(type.equals("GameType"))
		{
			dbName = "gameTypes";
		}
		else
		if(type.equals("GameSequence"))
		{
			dbName = "gameSequences";
		}
		else
		{
			log.error("Could not parse incomingGameVote: "+type+","+uuid+","+upOrDownString);
			writeCompressed(channel,BobNet.Bobs_Game_GameTypesAndSequences_Vote_Response+"Failed: Could not parse data, please try again."+BobNet.endline);
			return;
		}


		boolean exists = false;
		long upVotes = -1;
		long downVotes = -1;
		String usersVotedCSV = "";

		Connection databaseConnection = openAccountsDBOnAmazonRDS();
		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}
		{
			ResultSet resultSet = null;
			PreparedStatement ps = null;

			//check to see if it exists
			try
			{
				ps = databaseConnection.prepareStatement(
						"SELECT " +
								"upVotes , " + //bigint 20
								"downVotes , " + //bigint 20
								"usersVoted " +//text
						"FROM "+dbName+" WHERE uuid = ?");
				int i = 0;
				ps.setString(++i, uuid);
				resultSet = ps.executeQuery();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}


			try
			{
				if(resultSet.next())
				{
					exists = true;
					upVotes = resultSet.getLong("upVotes");
					downVotes = resultSet.getLong("downVotes");
					usersVotedCSV = resultSet.getString("usersVoted");

					if(usersVotedCSV==null)usersVotedCSV="";
				}

				resultSet.close();
				ps.close();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

		}

		if(exists)
		{


			boolean upOrDown = false;

			if(upOrDownString.equals("up"))upOrDown=true;
			if(upOrDownString.equals("down"))upOrDown=false;


			if(upOrDown)upVotes++;
			else downVotes++;

			boolean changedVote = false;
			String lastVote = "";
			//see if they already voted, if they did remove it so we can replace it
			if(usersVotedCSV.startsWith(userID+":"))
			{
				usersVotedCSV = usersVotedCSV.substring(usersVotedCSV.indexOf(":")+1);
				lastVote = usersVotedCSV.substring(0,usersVotedCSV.indexOf(","));
				usersVotedCSV = usersVotedCSV.substring(usersVotedCSV.indexOf(",")+1);
			}

			if(usersVotedCSV.contains(","+userID+":"))
			{
				String front = usersVotedCSV.substring(0,usersVotedCSV.indexOf(","+userID+":"));

				usersVotedCSV = usersVotedCSV.substring(usersVotedCSV.indexOf(","+userID+":"));
				usersVotedCSV = usersVotedCSV.substring(usersVotedCSV.indexOf(":")+1);
				lastVote = usersVotedCSV.substring(0,usersVotedCSV.indexOf(","));

				usersVotedCSV = usersVotedCSV.substring(usersVotedCSV.indexOf(","));
				usersVotedCSV = front + usersVotedCSV;

			}

			if(lastVote.length()!=0)
			{
				if((lastVote.equals("up") && upOrDown==true) || (lastVote.equals("down") && upOrDown==false))
				{
					writeCompressed(channel,BobNet.Bobs_Game_GameTypesAndSequences_Vote_Response+"Already voted "+lastVote+"!"+BobNet.endline);
					closeDBConnection(databaseConnection);
					return;
				}
				else
				{
					changedVote = true;
				}
			}

			if(upOrDown)usersVotedCSV = usersVotedCSV+userID+":up,";
			else usersVotedCSV = usersVotedCSV+userID+":down,";


			try
			{
				PreparedStatement ps = databaseConnection.prepareStatement(
						"UPDATE "+dbName+" SET " +
						"upVotes = ? , " +
						"downVotes = ? , " +
						"usersVoted = ? " +
						"WHERE uuid = ?");

				int i=0;
				ps.setLong(++i, upVotes);
				ps.setLong(++i, downVotes);
				ps.setString(++i, usersVotedCSV);
				ps.setString(++i, uuid);
				ps.executeUpdate();

				ps.close();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

			String responseStatus = "Success: Thank you for voting!";
			if(changedVote)responseStatus = "Success: You have updated your vote.";
			writeCompressed(channel,BobNet.Bobs_Game_GameTypesAndSequences_Vote_Response+responseStatus+BobNet.endline);
			closeDBConnection(databaseConnection);
		}
		else
		{

			writeCompressed(channel,BobNet.Bobs_Game_GameTypesAndSequences_Vote_Response+"Failed: Could not find game in database."+BobNet.endline);
			closeDBConnection(databaseConnection);
		}




	}





	//===============================================================================================
	private void incomingBobsGameRoomListRequest(Channel channel, String message)
	{//===============================================================================================

		//send back list of all active rooms in csv format separated by :
		//should probably zip this because it's gonna be large
		//need to test compatibility between server/client zip and base64 or whatever
		//for now let's not bother zipping it because who cares

		//Client c = getClientByChannel(channel);
		//long userID = c.userID;
		//if(userID==-1)return;


		String s = "";
		for(int i=0;i<rooms.size();i++)
		{

			//purge rooms older than 20 seconds
			BobsGameRoom r = rooms.get(i);
			if(System.currentTimeMillis() - r.timeLastGotUpdate > 1000*20)
			{
				roomsByRoomUUID.remove(r.uuid);
				roomsByUserID.remove(r.multiplayer_HostUserID,r);
				rooms.remove(r);
				i--;
			}
			else
			{
				s+=r.encodeRoomData() + ":";
			}
		}


		writeCompressed(channel,BobNet.Bobs_Game_RoomList_Response+s+BobNet.endline);

	}



	//===============================================================================================
	private void incomingBobsGameTellRoomHostToAddUserID(Channel channel, String message)
	{//===============================================================================================

		//look up room with roomUUID and tell the host userID to connect to userID client

		BobsGameClient c = getClientByChannel(channel);
		long userID = c.userID;
		if(userID==-1){log.error("Client UserID was -1");return;}


		String s = message;

		//strip off header
		s = s.substring(s.indexOf(":")+1);

		//roomUUID up to :
		String roomUUID = s.substring(0,s.indexOf(":"));

		BobsGameRoom r = roomsByRoomUUID.get(roomUUID);
		if(r!=null)
		{
			BobsGameClient host = clientsByUserID.get(r.multiplayer_HostUserID);
			if(host!=null)
			{
				//write(host.channel,BobNet.Bobs_Game_TellRoomHostToAddMyUserID+s+BobNet.endline);

				tellUserIDThatUserIDIsOnline(r.multiplayer_HostUserID,userID);
			}
		}


	}



	//===============================================================================================
	private void incomingBobsGameHostingPublicRoomUpdate(Channel channel, String message)
	{//===============================================================================================

		//look for existing room with roomUUID and if it doesn't exist, make one with that UUID and add it to the array
		//set the creation time and updated time


		BobsGameClient c = getClientByChannel(channel);
		long userID = c.userID;
		if(userID==-1){log.error("Client UserID was -1");return;}


		String s = message;

		//strip off header
		s = s.substring(s.indexOf(":")+1);
		

		//log.debug(s);
		BobsGameRoom newRoom = createRoom(s,userID);

		if(newRoom!=null)
		{
			tellAllClientsNewRoomHasBeenCreated(newRoom, userID);
		
		}

		//this also will tell all clients on other servers there is a new room hosted
		ServerMain.indexClientTCP.send_INDEX_Tell_All_Servers_Bobs_Game_Hosting_Room_Update(s, userID);
		
	}
	
	//===============================================================================================
	public void tellAllClientsNewRoomHasBeenCreated(BobsGameRoom room, long exceptUserID)
	{//===============================================================================================
		
		for(int i=0;i<channels.size();i++)
		{
			Channel c = channels.get(i);
			writeCompressed(c,BobNet.Bobs_Game_NewRoomCreatedUpdate+room.encodeRoomData()+BobNet.endline);
		}
		
//		Iterator<BobsGameClient> i = clientsByUserID.values().iterator();
//		while(i.hasNext())
//		{
//			BobsGameClient check = i.next();
//			if(check!=null)
//			{
//				if(check.channel.isActive() && check.userID != exceptUserID)
//				{
//					writeCompressed(check.channel,BobNet.Bobs_Game_NewRoomCreatedUpdate+room.encodeRoomData()+BobNet.endline);
//				}
//			}
//		}
		
	}

	//===============================================================================================
	private void incomingBobsGameHostingPublicRoomStarted(Channel channel, String message)
	{//===============================================================================================

		//set the room status to started and remove it from the list
		//maybe add it to started games list?

		BobsGameClient c = getClientByChannel(channel);
		long userID = c.userID;
		if(userID==-1){log.error("Client UserID was -1");return;}

		incomingBobsHostingPublicRoomCanceled(channel, message);


	}


	//===============================================================================================
	private void incomingBobsHostingPublicRoomCanceled(Channel channel, String message)
	{//===============================================================================================

		//remove the room from the list if it is the userID that created it who sent this
		BobsGameClient c = getClientByChannel(channel);
		long userID = c.userID;
		if(userID==-1){log.error("Client UserID was -1");return;}

		String s = message;

		//strip off header
		s = s.substring(s.indexOf(":")+1);


		removeRoom(s, userID);

		ServerMain.indexClientTCP.send_INDEX_Tell_All_Servers_Bobs_Game_Remove_Room(s, userID);

	}


	//===============================================================================================
	//returns new room if created, null if existing room is updated
	public BobsGameRoom createRoom(String s, long userID)
	{//===============================================================================================

		//hostUserID,roomUUID,`gameSequenceOrTypeName`,isGameSequenceOrType,gameSequenceOrTypeUUID,usersInRoom,maxUsers,private,tournament,multiplayerOptions,
		BobsGameRoom newRoom = new BobsGameRoom(s);

		if(newRoom.multiplayer_HostUserID!=userID){log.error("Room hostUserID did not match Client UserID");return null;}


		BobsGameRoom oldRoom = roomsByRoomUUID.get(newRoom.uuid);
		if(oldRoom!=null)
		{
			if(oldRoom.multiplayer_HostUserID!=userID){log.error("Room hostUserID did not match Client UserID");return null;}

			roomsByRoomUUID.remove(newRoom.uuid);
			roomsByUserID.remove(newRoom.multiplayer_HostUserID);
			rooms.remove(oldRoom);

			newRoom.timeStarted = oldRoom.timeStarted;
			newRoom.timeLastGotUpdate = System.currentTimeMillis();

			roomsByRoomUUID.put(newRoom.uuid, newRoom);
			roomsByUserID.put(newRoom.multiplayer_HostUserID, newRoom);
			rooms.add(newRoom);
			
			return null;
		}
		else
		{

			newRoom.timeStarted = System.currentTimeMillis();
			newRoom.timeLastGotUpdate = System.currentTimeMillis();

			roomsByRoomUUID.put(newRoom.uuid, newRoom);
			roomsByUserID.put(newRoom.multiplayer_HostUserID, newRoom);
			rooms.add(newRoom);
			
			return newRoom;
		}
	}


	//===============================================================================================
	public void removeRoom(String s, long userID)
	{//===============================================================================================


		//roomUUID up to :
		String roomUUID = s.substring(0,s.indexOf(":"));

		BobsGameRoom r = roomsByRoomUUID.get(roomUUID);
		if(r!=null)
		{
			if(r.multiplayer_HostUserID!=userID){log.error("Room hostUserID did not match Client UserID");return;}

			roomsByRoomUUID.remove(r.uuid);
			roomsByUserID.remove(r.multiplayer_HostUserID);
			rooms.remove(r);
		}
	}



	//===============================================================================================
	private void incomingBobsGameHostingPublicRoomEnded(Channel channel, String message)
	{//===============================================================================================

		//the game has ended, if it was a tournament game, set stats, probably do server verification stuff here
		//in fact let's have the server send the replay to the verification server



	}
	
	//===============================================================================================
	private void incomingBobsGameGetHighScoresAndLeaderboardsRequest(Channel channel, String message)
	{//===============================================================================================
		
		sendAllUserStatsGameStatsAndLeaderBoardsToClient(channel, message);
	}
	
	
	//===============================================================================================
	private void incomingBobsGameActivityStreamRequest(Channel channel, String message)
	{//===============================================================================================
		

		//when add stats to database create activity string and add to database
		
		Connection databaseConnection = openAccountsDBOnAmazonRDS();
		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

		ResultSet resultSet = null;
		PreparedStatement ps = null;
		
		int count = 0;
		ArrayList<String> activityStrings = new ArrayList<String>();
		try
		{
			ps = databaseConnection.prepareStatement(
					"SELECT " +
					"* " +
					"FROM "+BobNet.Bobs_Game_ActivityStream_DB_Name+"");
			
			resultSet = ps.executeQuery();
			
			
			while(resultSet.next())
			{
				count++;
				String activityString = resultSet.getString("activityString");
				
				if(activityString==null)activityString = "";
				else activityStrings.add(0,activityString);
			}

			resultSet.close();
			ps.close();

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();closeDBConnection(databaseConnection);return;}
	
		int max = 20;
		//if most recent stats has more than max rows drop the top row
		if(count>max)
		{
			int removeAmount = count-max;
			
			try
			{
				ps = databaseConnection.prepareStatement(
						"DELETE FROM "+BobNet.Bobs_Game_ActivityStream_DB_Name+" LIMIT "+removeAmount+";"
						);
				ps.executeUpdate();
				ps.close();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();closeDBConnection(databaseConnection);return;}
		}
		
		closeDBConnection(databaseConnection);

		
		
		
		if(activityStrings.size()>0)
		{
		
			String responseString = "";//"`Game stats recorded successfully on server.`,";
			for(int i=0;i<activityStrings.size();i++)
			{
				responseString += activityStrings.get(i);
			}
			
			writeCompressed(channel,BobNet.Bobs_Game_ActivityStream_Response+responseString+BobNet.endline);
		}
	}
	
	
	//===============================================================================================
	private void incomingChatMessage(Channel channel, String message, boolean sendToIndex)
	{//===============================================================================================
		
		BobsGameClient c = getClientByChannel(channel);
		
		String name = "Anonymous";
		if(c!=null)name = c.userName;
		//long userID = c.userName;
		//if(userID==-1){log.error("Client UserID was -1");return;}
		//String userName = c.userName;
		
		String s = message;

		//strip off header
		s = s.substring(s.indexOf(":")+1);
		
		s = name+": "+s;

		sendChatMessageToAllClients(s);

		if(sendToIndex)ServerMain.indexClientTCP.send_INDEX_Tell_All_Servers_To_Send_Chat_Message_To_All_Clients(s);
		
		
	}
	//===============================================================================================
	public void sendChatMessageToAllClients(String s)
	{//===============================================================================================
		for(int i=0;i<channels.size();i++)
		{
			Channel c = channels.get(i);
			writeCompressed(c,BobNet.Chat_Message+s+BobNet.endline);
		}
		
	}
	
	
	
	//=========================================================================================================================
	public String getNiceTime(long ms)
	{//=========================================================================================================================
		int sec = (int)(ms / 1000);
		int min = sec / 60;
		int hrs = min / 60;
		sec = sec % 60;
		min = min % 60;

		String niceTime = "";
		
		if(hrs>0)
		{
			if (hrs > 0 && hrs < 10)niceTime += "0"+hrs + ":";
			if (hrs >= 10)niceTime += ""+hrs + ":";
	
			if (min >= 0 && min < 10)niceTime += "0" + min + ":";
			if (min >= 10)niceTime += ""+min + ":";
	
			if (sec >= 0 && sec < 10)niceTime += "0" + sec + "";
			if (sec >= 10)niceTime += ""+sec + "";
		}
		else
		{

			if (min >= 0 && min < 10)niceTime += "0" + min + ":";
			if (min >= 10)niceTime += ""+min + ":";
	
			if (sec >= 0 && sec < 10)niceTime += "0" + sec + "";
			if (sec >= 10)niceTime += ""+sec + "";
			
		}
		return niceTime;
	}
	
	//===============================================================================================
	private void incomingBobsGameGameStats(Channel channel, String message)
	{//===============================================================================================

		BobsGameClient c = getClientByChannel(channel);
		long userID = c.userID;
		if(userID==-1){log.error("Client UserID was -1");return;}
		String userName = c.userName;

		String s = message;

		//strip off header
		s = s.substring(s.indexOf(":")+1);

		BobsGameGameStats game = new BobsGameGameStats(s);

		//make sure userID in stats matches client
		if(userID!=game.userID){log.error("userID did not match in game stats");return;}


		Connection databaseConnection = openAccountsDBOnAmazonRDS();
		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

		//record game stats in database
		{

			PreparedStatement ps = null;
			try
			{
				ps = game.getInsertStatement(databaseConnection,c);
				ps.executeUpdate();
				ps.close();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();closeDBConnection(databaseConnection);return;}
		}

		String responseString = "`Game stats recorded successfully on server.`,";
		String activityString = "";
		
		
		String gameName = "";
		if(game.isGameSequenceOrType.equals("GameType"))gameName = game.gameTypeName;
		if(game.isGameSequenceOrType.equals("GameSequence"))gameName = game.gameSequenceName;
		
		String gameType = "a singleplayer game of";
		
		if(game.isLocalMultiplayer==1)gameType = "a local multiplayer match with "+game.numPlayers+" players in";
		if(game.isNetworkMultiplayer==1)gameType = "an online multiplayer match with "+game.room.multiplayer_NumPlayers+" players in";
		if(game.room.multiplayer_TournamentRoom==1)gameType = "an online tournament with "+game.room.multiplayer_NumPlayers+" players in";

		String action = "";
		String end = "";
		if(game.complete==1) {action = "completed"; end = " in "+getNiceTime(game.timeLasted);}
		if(game.died==1)action = "lasted "+getNiceTime(game.timeLasted)+" in";
		if(game.won==1)action = "won";
		if(game.lost==1)action = "lost";
		
		if((game.timeLasted / 1000)>60)//if score is less than a minute don't log it
		{
			activityString += "`"+game.userName+" "+action+" "+gameType+" \""+gameName+"\" ("+game.difficultyName+")"+end+"`,";
		}
		
		if(game.room.isDefaultSettings()==false)
		{
			responseString+="`Room settings were not default so score cannot apply to leaderboards.`,";
			
			insertActivityInDB(databaseConnection, activityString, game.userName, game.userID, game.statsUUID);
			closeDBConnection(databaseConnection);
			
			writeCompressed(c.channel,BobNet.Bobs_Game_GameStats_Response+responseString+BobNet.endline);
			sendActivityUpdateToAllClients(activityString);
			
			return;
		}

		LeaderBoardScore score = new LeaderBoardScore();

		//update user stats
		
		String objectiveString = "Play To Credits";
		if(game.room.endlessMode==1)objectiveString = "Endless Mode";

		
		
		//get user stats from database
		BobsGameUserStatsForSpecificGameAndDifficulty userStatsForAnyGameAnyDifficulty =
				BobsGameUserStatsForSpecificGameAndDifficulty.getFromDBOrCreateNewIfNotExist(databaseConnection, userID, userName, "OVERALL", "", "", "", "", "OVERALL", objectiveString);
		//update the userStats from the game stats
		userStatsForAnyGameAnyDifficulty.updateFromGameStats(databaseConnection, game, score, responseString, activityString);
		//update stats in db
		userStatsForAnyGameAnyDifficulty.updateDB(databaseConnection,c.userID);


		BobsGameUserStatsForSpecificGameAndDifficulty userStatsForAnyGameThisDifficulty =
				BobsGameUserStatsForSpecificGameAndDifficulty.getFromDBOrCreateNewIfNotExist(databaseConnection, userID, userName, "OVERALL", "", "", "", "", game.difficultyName, objectiveString);
		//update the userStats from the game stats
		userStatsForAnyGameThisDifficulty.updateFromGameStats(databaseConnection, game, score, responseString, activityString);
		//update stats in db
		userStatsForAnyGameThisDifficulty.updateDB(databaseConnection,c.userID);


		BobsGameUserStatsForSpecificGameAndDifficulty userStatsForThisGameAnyDifficulty =
				BobsGameUserStatsForSpecificGameAndDifficulty.getFromDBOrCreateNewIfNotExist(databaseConnection, userID, userName, game.isGameSequenceOrType, game.gameTypeUUID, game.gameTypeName, game.gameSequenceUUID, game.gameSequenceName, "OVERALL", objectiveString);
		//update the userStats from the game stats
		userStatsForThisGameAnyDifficulty.updateFromGameStats(databaseConnection, game, score, responseString, activityString);
		//update stats in db
		userStatsForThisGameAnyDifficulty.updateDB(databaseConnection,c.userID);


		//TODO: could get all userHighScores entries for this user, calculate favorite game and favorite difficulty

		BobsGameUserStatsForSpecificGameAndDifficulty userStatsForThisGameThisDifficulty =
				BobsGameUserStatsForSpecificGameAndDifficulty.getFromDBOrCreateNewIfNotExist(databaseConnection,userID, userName, game.isGameSequenceOrType, game.gameTypeUUID, game.gameTypeName, game.gameSequenceUUID, game.gameSequenceName, game.difficultyName, objectiveString);
		//update the highScore from the game stats
		userStatsForThisGameThisDifficulty.updateFromGameStats(databaseConnection, game, score, responseString, activityString);
		//now update userHighScore in DB
		userStatsForThisGameThisDifficulty.updateDB(databaseConnection,c.userID);


		//now that we have an elo score and planeswalker point score for this game we can check leaderboard and highscoreboard
		//now get leaderBoards by eloScore for this game and difficulty, create it if it doesnt exist

		boolean leaderBoardsModified = BobsGameLeaderBoardAndHighScoreBoard.updateLeaderBoardsAndHighScoreBoards(databaseConnection, game, score, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, responseString, activityString);

		writeCompressed(c.channel,BobNet.Bobs_Game_GameStats_Response+responseString+BobNet.endline);

		insertActivityInDB(databaseConnection, activityString, game.userName, game.userID, game.statsUUID);
		
		closeDBConnection(databaseConnection);

		sendActivityUpdateToAllClients(activityString);
		ServerMain.indexClientTCP.send_INDEX_Tell_All_Servers_To_Send_Activity_Update_To_All_Clients(activityString);

		//send new userStats, modified gameStats or created gameStats, and any modified leaderboards

		String batch = ""+BobNet.Bobs_Game_UserStatsLeaderBoardsAndHighScoresBatched;

		batch+=(BobNet.Bobs_Game_UserStatsForSpecificGameAndDifficulty+userStatsForAnyGameAnyDifficulty.encode()+BobNet.batch);
		batch+=(BobNet.Bobs_Game_UserStatsForSpecificGameAndDifficulty+userStatsForAnyGameThisDifficulty.encode()+BobNet.batch);
		batch+=(BobNet.Bobs_Game_UserStatsForSpecificGameAndDifficulty+userStatsForThisGameAnyDifficulty.encode()+BobNet.batch);
		batch+=(BobNet.Bobs_Game_UserStatsForSpecificGameAndDifficulty+userStatsForThisGameThisDifficulty.encode()+BobNet.batch);

		writeCompressed(c.channel,batch+BobNet.endline);

		if(leaderBoardsModified)
		{
			sendAllLeaderBoardsToClient(channel, message);
		}
	}
	
	//===============================================================================================
	public void insertActivityInDB(Connection databaseConnection, String activityString, String userName, long userID, String statsUUID)
	{//===============================================================================================
		

		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

		PreparedStatement ps = null;

		String query =

		"INSERT INTO "+BobNet.Bobs_Game_ActivityStream_DB_Name+" SET ";

		query += "activityString"+" = ? , ";
		query += "timeCreated"+" = ? , ";
		query += "userName"+" = ? , ";
		query += "userID"+" = ? , ";
		query += "statsUUID"+" = ? ";
	

		try
		{
			ps = databaseConnection.prepareStatement(query);

			int n = 0;
			
			ps.setString(++n, activityString);
			ps.setLong(++n, System.currentTimeMillis());
			ps.setString(++n, userName);
			ps.setLong(++n, userID);
			ps.setString(++n, statsUUID);
			
			ps.executeUpdate();

			ps.close();

		}
		catch (Exception ex){System.err.println("DB ERROR: "+ex.getMessage());}
	}
	
	//===============================================================================================
	public void sendActivityUpdateToAllClients(String activityString)
	{//===============================================================================================
						
		for(int i=0;i<channels.size();i++)
		{
			Channel c = channels.get(i);
			
			writeCompressed(c,BobNet.Bobs_Game_ActivityStream_Update+activityString+BobNet.endline);	
		}
			
	}

	//===============================================================================================
	public void sendAllUserStatsGameStatsAndLeaderBoardsToClient(Channel channel, String message)
	{//===============================================================================================

		BobsGameClient c = getClientByChannel(channel);
		
		if(c!=null)
		{
			Connection databaseConnection = openAccountsDBOnAmazonRDS();
			if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}
	
			ArrayList<BobsGameUserStatsForSpecificGameAndDifficulty> allUserStatsForIndividualGames = BobsGameUserStatsForSpecificGameAndDifficulty.getAllUserStatsForGamesFromDB(databaseConnection, c.userID);
	
			closeDBConnection(databaseConnection);
	
	
			String batch = ""+BobNet.Bobs_Game_UserStatsLeaderBoardsAndHighScoresBatched;
	
			for(int i=0; i<allUserStatsForIndividualGames.size(); i++)
			{
				batch+=(BobNet.Bobs_Game_UserStatsForSpecificGameAndDifficulty+allUserStatsForIndividualGames.get(i).encode()+BobNet.batch);
			}
	
			writeCompressed(c.channel,batch+BobNet.endline);
		}

		sendAllLeaderBoardsToClient(channel, message);


	}

	//===============================================================================================
	public void sendAllLeaderBoardsToClient(Channel channel, String message)
	{//===============================================================================================

		//log.info("Getting leaderboards from DB");
		Connection databaseConnection = openAccountsDBOnAmazonRDS();
		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

		ArrayList<BobsGameLeaderBoardAndHighScoreBoard> bobsGameLeaderBoardsByTotalTimePlayed = BobsGameLeaderBoardAndHighScoreBoard.getAllLeaderBoardsAndHighScoreBoardsFromDB(databaseConnection, "bobsGameLeaderBoardsByTotalTimePlayed");
		//log.info("Got bobsGameLeaderBoardsByTotalTimePlayed");
		String batch = ""+BobNet.Bobs_Game_UserStatsLeaderBoardsAndHighScoresBatched;
		for(int i=0; i<bobsGameLeaderBoardsByTotalTimePlayed.size(); i++)
		{
			batch+=(BobNet.Bobs_Game_LeaderBoardsByTotalTimePlayed+bobsGameLeaderBoardsByTotalTimePlayed.get(i).encode()+BobNet.batch);
		}
		writeCompressed(channel,batch+BobNet.endline);
		
		ArrayList<BobsGameLeaderBoardAndHighScoreBoard> bobsGameLeaderBoardsByTotalBlocksCleared = BobsGameLeaderBoardAndHighScoreBoard.getAllLeaderBoardsAndHighScoreBoardsFromDB(databaseConnection, "bobsGameLeaderBoardsByTotalBlocksCleared");
		//log.info("Got bobsGameLeaderBoardsByTotalBlocksCleared");
		batch = ""+BobNet.Bobs_Game_UserStatsLeaderBoardsAndHighScoresBatched;
		for(int i=0; i<bobsGameLeaderBoardsByTotalBlocksCleared.size(); i++)
		{
			batch+=(BobNet.Bobs_Game_LeaderBoardsByTotalBlocksCleared+bobsGameLeaderBoardsByTotalBlocksCleared.get(i).encode()+BobNet.batch);
		}
		writeCompressed(channel,batch+BobNet.endline);
		
		ArrayList<BobsGameLeaderBoardAndHighScoreBoard> bobsGameLeaderBoardsByPlaneswalkerPoints = BobsGameLeaderBoardAndHighScoreBoard.getAllLeaderBoardsAndHighScoreBoardsFromDB(databaseConnection, "bobsGameLeaderBoardsByPlaneswalkerPoints");
		//log.info("Got bobsGameLeaderBoardsByPlaneswalkerPoints");
		batch = ""+BobNet.Bobs_Game_UserStatsLeaderBoardsAndHighScoresBatched;
		for(int i=0; i<bobsGameLeaderBoardsByPlaneswalkerPoints.size(); i++)
		{
			batch+=(BobNet.Bobs_Game_LeaderBoardsByPlaneswalkerPoints+bobsGameLeaderBoardsByPlaneswalkerPoints.get(i).encode()+BobNet.batch);
		}
		writeCompressed(channel,batch+BobNet.endline);
		
		ArrayList<BobsGameLeaderBoardAndHighScoreBoard> bobsGameLeaderBoardsByEloScore = BobsGameLeaderBoardAndHighScoreBoard.getAllLeaderBoardsAndHighScoreBoardsFromDB(databaseConnection, "bobsGameLeaderBoardsByEloScore");
		//log.info("Got bobsGameLeaderBoardsByEloScore");
		batch = ""+BobNet.Bobs_Game_UserStatsLeaderBoardsAndHighScoresBatched;
		for(int i=0; i<bobsGameLeaderBoardsByEloScore.size(); i++)
		{
			batch+=(BobNet.Bobs_Game_LeaderBoardsByEloScore+bobsGameLeaderBoardsByEloScore.get(i).encode()+BobNet.batch);
		}
		writeCompressed(channel,batch+BobNet.endline);
		
		ArrayList<BobsGameLeaderBoardAndHighScoreBoard> bobsGameHighScoreBoardsByTimeLasted = BobsGameLeaderBoardAndHighScoreBoard.getAllLeaderBoardsAndHighScoreBoardsFromDB(databaseConnection, "bobsGameHighScoreBoardsByTimeLasted");
		//log.info("Got bobsGameHighScoreBoardsByTimeLasted");
		batch = ""+BobNet.Bobs_Game_UserStatsLeaderBoardsAndHighScoresBatched;
		for(int i=0; i<bobsGameHighScoreBoardsByTimeLasted.size(); i++)
		{
			batch+=(BobNet.Bobs_Game_HighScoreBoardsByTimeLasted+bobsGameHighScoreBoardsByTimeLasted.get(i).encode()+BobNet.batch);
		}
		writeCompressed(channel,batch+BobNet.endline);
		
		ArrayList<BobsGameLeaderBoardAndHighScoreBoard> bobsGameHighScoreBoardsByBlocksCleared = BobsGameLeaderBoardAndHighScoreBoard.getAllLeaderBoardsAndHighScoreBoardsFromDB(databaseConnection, "bobsGameHighScoreBoardsByBlocksCleared");
		//log.info("Got bobsGameHighScoreBoardsByBlocksCleared");
		batch = ""+BobNet.Bobs_Game_UserStatsLeaderBoardsAndHighScoresBatched;
		for(int i=0; i<bobsGameHighScoreBoardsByBlocksCleared.size(); i++)
		{
			batch+=(BobNet.Bobs_Game_HighScoreBoardsByBlocksCleared+bobsGameHighScoreBoardsByBlocksCleared.get(i).encode()+BobNet.batch);
		}
		writeCompressed(channel,batch+BobNet.endline);
		
		
		closeDBConnection(databaseConnection);
		
		//log.info("Got leaderboards from DB");

		//		String batch = ""+BobNet.Bobs_Game_UserStatsLeaderBoardsAndHighScoresBatched;
		//		
		//		for(int i=0; i<bobsGameLeaderBoardsByTotalTimePlayed.size(); i++)
		//		{
		//			batch+=(BobNet.Bobs_Game_LeaderBoardsByTotalTimePlayed+bobsGameLeaderBoardsByTotalTimePlayed.get(i).encode()+BobNet.batch);
		//		}
		//
		//		for(int i=0; i<bobsGameLeaderBoardsByTotalBlocksCleared.size(); i++)
		//		{
		//			batch+=(BobNet.Bobs_Game_LeaderBoardsByTotalBlocksCleared+bobsGameLeaderBoardsByTotalBlocksCleared.get(i).encode()+BobNet.batch);
		//		}
		//
		//		for(int i=0; i<bobsGameLeaderBoardsByPlaneswalkerPoints.size(); i++)
		//		{
		//			batch+=(BobNet.Bobs_Game_LeaderBoardsByPlaneswalkerPoints+bobsGameLeaderBoardsByPlaneswalkerPoints.get(i).encode()+BobNet.batch);
		//		}
		//
		//		for(int i=0; i<bobsGameLeaderBoardsByEloScore.size(); i++)
		//		{
		//			batch+=(BobNet.Bobs_Game_LeaderBoardsByEloScore+bobsGameLeaderBoardsByEloScore.get(i).encode()+BobNet.batch);
		//		}
		//
		//		for(int i=0; i<bobsGameHighScoreBoardsByTimeLasted.size(); i++)
		//		{
		//			batch+=(BobNet.Bobs_Game_HighScoreBoardsByTimeLasted+bobsGameHighScoreBoardsByTimeLasted.get(i).encode()+BobNet.batch);
		//		}
		//
		//		for(int i=0; i<bobsGameHighScoreBoardsByBlocksCleared.size(); i++)
		//		{
		//			batch+=(BobNet.Bobs_Game_HighScoreBoardsByBlocksCleared+bobsGameHighScoreBoardsByBlocksCleared.get(i).encode()+BobNet.batch);
		//		}
		//		log.info("Writing leaderboards to client");
		//		writeCompressed(channel,batch+BobNet.endline);
		//		log.info("Wrote leaderboards to client");
	}



	//===============================================================================================
	private void tellUserIDThatUserIDIsOnline(long userIDToTell, long userIDWhichIsOnline)
	{//===============================================================================================

		BobsGameClient c = clientsByUserID.get(userIDToTell);

		if(c!=null)
		{
			//write(c.channel,BobNet.Online_Friends_List_Response+userIDWhichIsOnline+","+BobNet.endline);
			writeCompressed(c.channel,BobNet.Friend_Is_Online_Notification+"anon"+":"+userIDWhichIsOnline+BobNet.endline);
		}
		else
		{
			//userID not on this server

		}

	}


	//===============================================================================================
	private void incomingOnlineFriendsListRequest(Channel channel, String message)
	{//===============================================================================================

		//this should access the DB and get a list of all the friends that are online


		BobsGameClient c = getClientByChannel(channel);
		long userID = -1;
		if(c!=null)
		{
			userID = c.userID;
		}
		else
		{log.error("Could not find client connection, was connection dropped?");return;}


		//first get our list of facebook friends, twitter friends, google+ friends, steam friends, etc.

		Connection databaseConnection = openAccountsDBOnAmazonRDS();
		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}


		ResultSet resultSet = null;
		PreparedStatement ps = null;

		try
		{
			ps = databaseConnection.prepareStatement(
					"SELECT " +
					"userNameFriends , " +
					"facebookFriends " +
					"FROM accounts WHERE userID = ?");


			ps.setLong(1, userID);
			resultSet = ps.executeQuery();

		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}


		String facebookFriendsCSV = "";
		String userNameFriendsCSV = "";
		//String googleFriendsCSV = "";
		//String twitterFriendsCSV = "";

		try
		{

			if(resultSet.next())
			{
				facebookFriendsCSV = resultSet.getString("facebookFriends");
				userNameFriendsCSV = resultSet.getString("userNameFriends");
				//googleFriendsCSV = databaseResultSet.getString("googleFriends");
				//twitterFriendsCSV = databaseResultSet.getString("twitterFriends");

				if(facebookFriendsCSV==null)facebookFriendsCSV="";
				if(userNameFriendsCSV==null)userNameFriendsCSV="";
			}

			resultSet.close();
			ps.close();
			closeDBConnection(databaseConnection);


		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}



		//we should alert them all that we are online.
		ServerMain.indexClientTCP.send_INDEX_Tell_All_Servers_To_Tell_FacebookIDs_That_UserID_Is_Online(userID,facebookFriendsCSV);
		ServerMain.indexClientTCP.send_INDEX_Tell_All_Servers_To_Tell_UserNames_That_UserID_Is_Online(userID,userNameFriendsCSV);


		String onlineFriendUserIDsCSV = "";

		while(facebookFriendsCSV.length()>0)
		{
			String friendFacebookID = facebookFriendsCSV.substring(0,facebookFriendsCSV.indexOf(","));
			facebookFriendsCSV = facebookFriendsCSV.substring(facebookFriendsCSV.indexOf(",")+1);


			//then let's get results from the DB for each facebook friend of ours that is online, their userID, name, IP
			//NO: this will take a very long time
			//MAYBE: should have a server that indexes who is online, which clients are on which server, track by facebook ID, userID, etc.


//			try
//			{
//				ps.close();
//				ps = databaseConnection.prepareStatement("SELECT * FROM accounts WHERE facebookID = ? AND isOnline = 1");
//				ps.setString(1, friendFacebookID);
//				databaseResultSet = ps.executeQuery();
//
//			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}
//
//			try
//			{
//				if(databaseResultSet!=null)
//				if(databaseResultSet.next())
//				{
//					int id = databaseResultSet.getInt("userID");
//					onlineFriendUserIDsCSV = onlineFriendUserIDsCSV+"fb:"+id+",";
//				}
//			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}



			//DONE: could store facebookIDs in clientByFacebookID hashtable and just look up by that instead of accessing the DB (would have to check every server)
			BobsGameClient friendClient = clientsByFacebookID.get(friendFacebookID);
			if(friendClient!=null)
			{

				//store onlineFriendIDs in a list to send back to our client
				String type = "facebook";
				long friendID = friendClient.userID;
				onlineFriendUserIDsCSV = onlineFriendUserIDsCSV+type+":"+friendID+",";


				//notify friend we are online, they start pinging the stun server.
				writeCompressed(friendClient.channel,BobNet.Friend_Is_Online_Notification+type+":"+userID+BobNet.endline);
			}

		}

		while(userNameFriendsCSV.length()>0)
		{
			String friendUserName = userNameFriendsCSV.substring(0,userNameFriendsCSV.indexOf(","));
			userNameFriendsCSV = userNameFriendsCSV.substring(userNameFriendsCSV.indexOf(",")+1);

			BobsGameClient friendClient = clientsByUserName.get(friendUserName);
			if(friendClient!=null)
			{

				//store onlineFriendIDs in a list to send back to our client
				String type = "userName";
				long friendID = friendClient.userID;
				onlineFriendUserIDsCSV = onlineFriendUserIDsCSV+type+":"+friendID+",";


				//notify friend we are online, they start pinging the stun server.
				writeCompressed(friendClient.channel,BobNet.Friend_Is_Online_Notification+type+":"+userID+BobNet.endline);
			}

		}

		//now we have a list of friends userIDs that are online right now.
		//send our list to our client which should start pinging all of the IPs to make connections.
		writeCompressed(channel,BobNet.Online_Friends_List_Response+onlineFriendUserIDsCSV+BobNet.endline);

	}

	//===============================================================================================
	public void notifyAllFriendsWeAreDisconnected()
	{//===============================================================================================
		//TODO:
		//when do we know we're disconnected for sure?
		//need timeout. also need to close channel when timeout.

	}


//
//	// ===============================================================================================
//	public void testJSON()
//	{// ===============================================================================================
//
//		MapData m = MapAssetIndex.mapList.get(MapAssetIndex.mapList.size()-6);
//		Gson gson = new Gson();
//		String json = gson.toJson(m);
//		System.out.println("json------------------------------");
//		System.out.println("length:"+json.length());
//		System.out.println(json);
//
//		String zip = "";
//
//		zip = zipString(json);
//
//
//		System.out.println("zip------------------------------");
//		System.out.println("length:"+zip.length());
//		System.out.println(zip);
//
//
//		String b64 = encodeStringToBase64(zip);
//
//		System.out.println("b64------------------------------");
//		System.out.println("length:"+b64.length());
//		System.out.println(b64);
//
//		String decode64 = decodeBase64String(b64);
//		String unzip = unzipString(decode64);
//		MapData m2 = gson.fromJson(unzip,MapData.class);
//		json = gson.toJson(m2);
//		System.out.println("json------------------------------");
//		System.out.println("length:"+json.length());
//		System.out.println(json);
//
//
//	}



	//===============================================================================================
	private void incomingMapDataRequestByName(Channel channel, String message)
	{//===============================================================================================

		String s = message;




		//MapRequest:name
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(0,s.indexOf(":"));
		String name = s;


		//log.info(""+name);

		int id = AssetDataIndex.mapDataGetIDByNameList.get(name);
		String b64 = AssetDataIndex.mapDataList.get(id).toString();

		if(b64!=null)
		{
			writeCompressed(channel,

				BobNet.Map_Response+
				id+"-"+
				name+":"+
				b64+
				BobNet.endline
			);
		}
	}

	//===============================================================================================
	private void incomingMapDataRequestByID(Channel channel, String message)
	{//===============================================================================================
		String s = message;

		int id = -1;
		//MapRequest:name
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(0,s.indexOf(":"));
		try{id = Integer.parseInt(s);}catch(NumberFormatException ex){ex.printStackTrace();}

		String name = AssetDataIndex.mapDataGetNameByIDList.get(id);
		String b64 = AssetDataIndex.mapDataList.get(id).toString();

		if(b64!=null)
		{
			writeCompressed(channel,
				BobNet.Map_Response+
				id+"-"+
				name+":"+
				b64+
				BobNet.endline
			);
		}
	}

	//===============================================================================================
	private void incomingSpriteDataRequestByName(Channel channel, String message)
	{//===============================================================================================
		String s = message;

		//SpriteRequest:name
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(0,s.indexOf(":"));
		String name = s;

		//if(BobNet.debugMode)log.info(""+name);

		int id = AssetDataIndex.spriteDataGetIDByNameList.get(name);
		String b64 = AssetDataIndex.spriteDataList.get(id).toString();

		if(b64!=null)
		{
			writeCompressed(channel,
				BobNet.Sprite_Response+
				id+"-"+
				name+":"+
				b64+
				BobNet.endline
			);
		}
	}

	//===============================================================================================
	private void incomingSpriteDataRequestByID(Channel channel, String message)
	{//===============================================================================================
		String s = message;

		int id = -1;
		//SpriteRequest:name
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(0,s.indexOf(":"));
		try{id = Integer.parseInt(s);}catch(NumberFormatException ex){ex.printStackTrace();}

		String name = AssetDataIndex.spriteDataGetNameByIDList.get(id);
		String b64 = AssetDataIndex.spriteDataList.get(id).toString();

		if(b64!=null)
		{
			writeCompressed(channel,
				BobNet.Sprite_Response+
				id+"-"+
				name+":"+
				b64+
				BobNet.endline
			);
		}
	}

	//===============================================================================================
	private void incomingDialogueDataRequest(Channel channel, String message)
	{//===============================================================================================
		String s = message;

		int id = -1;
		//DialogueRequest:id
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(0,s.indexOf(":"));
		try{id = Integer.parseInt(s);}catch(NumberFormatException ex){ex.printStackTrace();}

		String name = AssetDataIndex.dialogueDataList.get(id).name();
		String b64 = AssetDataIndex.dialogueDataList.get(id).toString();

		//TODO: make sure the client is allowed to have this dialogue.
		//each dialogue object should have a prerequisite somehow, room, state, previous dialogue values need to be complete

		if(b64!=null)
		{
			writeCompressed(channel,
					BobNet.Dialogue_Response+
					id+"-"+
					name+":"+
					b64+
					BobNet.endline);

			//log.info("Server sent Dialogue Object");
		}
	}

	//===============================================================================================
	private void incomingFlagDataRequest(Channel channel, String message)
	{//===============================================================================================
		String s = message;

		int id = -1;
		//Flag_Request:id
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(0,s.indexOf(":"));
		try{id = Integer.parseInt(s);}catch(NumberFormatException ex){ex.printStackTrace();}

		String b64 = AssetDataIndex.flagDataList.get(id).toString();
		String name = AssetDataIndex.flagDataList.get(id).name();
		if(b64!=null)
		{
			writeCompressed(channel,
					BobNet.Flag_Response+
					id+"-"+
					name+":"+
					b64+
					BobNet.endline);
		}
	}

	//===============================================================================================
	private void incomingSkillDataRequest(Channel channel, String message)
	{//===============================================================================================
		String s = message;

		int id = -1;
		//Skill_Request:id
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(0,s.indexOf(":"));
		try{id = Integer.parseInt(s);}catch(NumberFormatException ex){ex.printStackTrace();}

		String b64 = AssetDataIndex.skillDataList.get(id).toString();
		String name = AssetDataIndex.skillDataList.get(id).name();
		if(b64!=null)
		{
			writeCompressed(channel,
					BobNet.Skill_Response+
					id+"-"+
					name+":"+
					b64+
					BobNet.endline);
		}
	}





	//===============================================================================================
	/**
	 * This should only be requested once per login.
	 * */
	private void incomingLoadEventRequest(Channel channel, String message)
	{//===============================================================================================


		int id = AssetDataIndex.loadEventID;

		if(id!=-1)
		{
			String b64 = AssetDataIndex.eventDataList.get(id).toString();
			String name = AssetDataIndex.eventDataList.get(id).name();

			if(b64!=null)
			{
				writeCompressed(channel,
						BobNet.Load_Event_Response+
						id+"-"+
						name+":"+
						b64+
						BobNet.endline);
			}
			else
			{
				log.error("Could not find event ID: "+id);
			}
		}
		else
		{
			log.error("Load eventID is -1");
		}

	}


	//===============================================================================================
	private void incomingEventDataRequest(Channel channel, String message)
	{//===============================================================================================
		String s = message;

		int id = -1;
		//EventRequest:id
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(0,s.indexOf(":"));
		try{id = Integer.parseInt(s);}catch(NumberFormatException ex){ex.printStackTrace();}

		String b64 = AssetDataIndex.eventDataList.get(id).toString();
		String name = AssetDataIndex.eventDataList.get(id).name();

		if(b64!=null)
		{
			writeCompressed(channel,
					BobNet.Event_Response+
					id+"-"+
					name+":"+
					b64+
					BobNet.endline);
		}
		else
		{
			log.error("Could not find event ID: "+id);
		}

	}


	//===============================================================================================
	private void incomingGameStringDataRequest(Channel channel, String message)
	{//===============================================================================================
		String s = message;

		int id = -1;
		//GameStringRequest:id
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(0,s.indexOf(":"));
		try{id = Integer.parseInt(s);}catch(NumberFormatException ex){ex.printStackTrace();}


		String b64 = AssetDataIndex.gameStringDataList.get(id).toString();
		String name = AssetDataIndex.gameStringDataList.get(id).name();

		if(b64!=null)
		{
			writeCompressed(channel,
					BobNet.GameString_Response+
					id+":"+
					b64+
					BobNet.endline);
		}
	}



	//===============================================================================================
	private void incomingMusicDataRequest(Channel channel, String message)
	{//===============================================================================================

		String s = message;

		int id = -1;
		//MusicRequest:id
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(0,s.indexOf(":"));
		try{id = Integer.parseInt(s);}catch(NumberFormatException ex){ex.printStackTrace();}


		String b64 = AssetDataIndex.musicDataList.get(id).toString();
		String name = AssetDataIndex.musicDataGetNameByIDList.get(id);

		if(b64!=null)
		{
			writeCompressed(channel,
					BobNet.Music_Response+
					id+"-"+
					name+":"+
					b64+
					BobNet.endline);
		}
	}

	//===============================================================================================
	private void incomingSoundDataRequest(Channel channel, String message)
	{//===============================================================================================

		String s = message;

		int id = -1;
		//SoundRequest:id
		s = s.substring(s.indexOf(":")+1);
		s = s.substring(0,s.indexOf(":"));
		try{id = Integer.parseInt(s);}catch(NumberFormatException ex){ex.printStackTrace();}

		String b64 = AssetDataIndex.soundDataList.get(id).toString();
		String name = AssetDataIndex.soundDataGetNameByIDList.get(id);

		if(b64!=null)
		{
			writeCompressed(channel,
					BobNet.Sound_Response+
					id+"-"+
					name+":"+
					b64+
					BobNet.endline);
		}
	}

	//===============================================================================================
	private void incomingPlayerCoords(Channel channel, String message)
	{//===============================================================================================

		String s = message;


		//c.lastKnownX = o.x;
		//c.lastKnownY = o.y;

		//log.info("Server got XY:"+connection.lastKnownX+","+connection.lastKnownY);
	}


}
