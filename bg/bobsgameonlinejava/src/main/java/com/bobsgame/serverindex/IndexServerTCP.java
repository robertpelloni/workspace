package com.bobsgame.serverindex;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.Executors;
import java.util.*;
import ch.qos.logback.classic.Logger;
import com.bobsgame.net.*;
import java.net.ConnectException;
import java.net.InetSocketAddress;

import io.netty.bootstrap.ServerBootstrap;
import io.netty.channel.Channel;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelFutureListener;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelPipeline;
import io.netty.channel.ChannelInitializer;
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
import io.netty.util.concurrent.DefaultEventExecutorGroup;
import io.netty.util.concurrent.EventExecutorGroup;
import io.netty.channel.SimpleChannelInboundHandler;

import org.slf4j.LoggerFactory;

//===============================================================================================
public class IndexServerTCP
{//===============================================================================================


	static public EventExecutorGroup executionGroup = new DefaultEventExecutorGroup(16);

	//Timer timer;

	//DONE: add any other server channels to this vector
	public Vector<BobsGameServer> serverList = new Vector<BobsGameServer>();
	public ConcurrentHashMap<Channel,BobsGameServer> serversByChannel = new ConcurrentHashMap<Channel,BobsGameServer>();
	public ConcurrentHashMap<Integer,BobsGameServer> serversByServerID = new ConcurrentHashMap<Integer,BobsGameServer>();

    EventLoopGroup bossGroup;
    EventLoopGroup workerGroup;
	Channel tcpChannel;

	public static Logger log = (Logger) LoggerFactory.getLogger(IndexServerTCP.class);


	//===============================================================================================
	public IndexServerTCP()
	{//===============================================================================================

        bossGroup = new NioEventLoopGroup(1);
        workerGroup = new NioEventLoopGroup();

        ServerBootstrap b = new ServerBootstrap();
        b.group(bossGroup, workerGroup)
         .channel(NioServerSocketChannel.class)
         .childHandler(new ChannelInitializer<SocketChannel>() {
             @Override
             public void initChannel(SocketChannel ch) throws Exception {
                 ChannelPipeline p = ch.pipeline();
                 p.addLast("framer", new DelimiterBasedFrameDecoder(65536, Delimiters.lineDelimiter()));
                 p.addLast("decoder", new StringDecoder());
                 p.addLast("encoder", new StringEncoder());
                 p.addLast("idle", new IdleStateHandler(120, 30, 0));
                 p.addLast(executionGroup, "handler", new BobsGameServerHandler());
             }
         });

		int serverPort = BobNet.INDEXServerTCPPort;
		//if(new File("/localServer").exists())serverPort++;

		// Bind and start to accept incoming connections.
        try {
		    tcpChannel = b.bind(serverPort).sync().channel();
		    log.info("INDEX Server TCP ChannelID: "+tcpChannel.id().toString());
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

	}


	//===============================================================================================
	public void cleanup()
	{//===============================================================================================
        bossGroup.shutdownGracefully();
        workerGroup.shutdownGracefully();
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
			    int id = -1;
			    BobsGameServer s = getServerByChannel(ctx.channel());
			    if(s!=null)id=s.serverID;

			    if(e.state() == IdleState.READER_IDLE)
			    {
				    log.warn("channelIdle: No incoming traffic from server timeout. Closing channel. ServerID: "+id);

				    ctx.close();

			    }
			    else if(e.state() == IdleState.WRITER_IDLE)
			    {

				    ctx.writeAndFlush("ping"+BobNet.endline);

				    if(BobNet.debugMode)log.debug("channelIdle: ping ServerID: "+id);
			    }
            }
		}



		//===============================================================================================
		@Override
		public void channelActive(ChannelHandlerContext ctx) throws Exception
		{//===============================================================================================
			log.info("channelConnected: from Server. ChannelID: "+ctx.channel().id());

		}




		//===============================================================================================
		@Override
		public void channelInactive(ChannelHandlerContext ctx) throws Exception
		{//===============================================================================================


			log.warn("channelDisconnected: from Server. ChannelID: "+ctx.channel().id());



			BobsGameServer s = getServerByChannel(ctx.channel());


			if(s!=null)
			{
				serverList.remove(s);
				serversByChannel.remove(ctx.channel());
				serversByServerID.remove(s.serverID);
			}


		}


		//===============================================================================================
		@Override
		public void channelRead0(ChannelHandlerContext ctx, String message) throws Exception
		{//===============================================================================================

			int serverID = -1;
			BobsGameServer s = getServerByChannel(ctx.channel());
			if(s!=null)serverID=s.serverID;






			if(message.startsWith("pong"))
			{
				//log.debug("pong from ServerID: "+id);
				return;

			}
			else
			if(message.startsWith("ping"))
			{

			}

			if(BobNet.debugMode)
			{
				log.warn("FROM SERVER: cID:"+ctx.channel().id()+" sID:"+serverID+" | "+message);
			}

			if(message.startsWith(BobNet.INDEX_Register_Server_With_INDEX_Request)){incoming_INDEX_Register_Server_Request(ctx.channel(), message);return;}


			if(message.startsWith(BobNet.INDEX_Tell_All_Servers_To_Tell_FacebookIDs_That_UserID_Is_Online)){incoming_INDEX_Tell_All_Servers_To_Tell_FacebookIDs_That_UserID_Is_Online(ctx.channel(), message);return;}
			if(message.startsWith(BobNet.INDEX_Tell_All_Servers_To_Tell_UserNames_That_UserID_Is_Online)){incoming_INDEX_Tell_All_Servers_To_Tell_UserNames_That_UserID_Is_Online(ctx.channel(), message);return;}
			if(message.startsWith(BobNet.INDEX_Tell_ServerID_To_Tell_UserID_That_UserIDs_Are_Online)){incoming_INDEX_Tell_ServerID_To_Tell_UserID_That_UserIDs_Are_Online(ctx.channel(), message);return;}
			if(message.startsWith(BobNet.INDEX_UserID_Logged_On_This_Server_Log_Them_Off_Other_Servers)){incoming_INDEX_User_Logged_On_This_Server_Log_Them_Off_Other_Servers(ctx.channel(), message);return;}

			if(message.startsWith(BobNet.INDEX_Tell_All_Servers_Bobs_Game_Hosting_Room_Update)){incoming_INDEX_Tell_All_Servers_Bobs_Game_Hosting_Room_Update(ctx.channel(), message);return;}
			if(message.startsWith(BobNet.INDEX_Tell_All_Servers_Bobs_Game_Remove_Room)){incoming_INDEX_Tell_All_Servers_Bobs_Game_Remove_Room(ctx.channel(), message);return;}
			if(message.startsWith(BobNet.INDEX_Tell_All_Servers_To_Send_Activity_Update_To_All_Clients)){incoming_INDEX_Tell_All_Servers_To_Send_Activity_Update_To_All_Clients(ctx.channel(), message);return;}
			if(message.startsWith(BobNet.INDEX_Tell_All_Servers_To_Send_Chat_Message_To_All_Clients)){incoming_INDEX_Tell_All_Servers_To_Send_Chat_Message_To_All_Clients(ctx.channel(), message);return;}


		}

		//===============================================================================================
		@Override
		public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause)
		{//===============================================================================================
			if(cause instanceof ConnectException)
			{
				log.error("Exception caught from Server connection - ConnectException: "+cause.getMessage());
			}
			else
			if(cause instanceof ReadTimeoutException)
			{
				log.error("Exception caught from Server connection - ReadTimeoutException: "+cause.getMessage());
			}
			else
			{
				log.error("Unexpected Exception caught from Server connection: "+cause.getMessage());
				cause.printStackTrace();
			}

			ctx.close();
		}



	}




	//===============================================================================================
	public BobsGameServer getServerByChannel(Channel c)
	{//===============================================================================================
		return serversByChannel.get(c);
	}

	//===============================================================================================
	public BobsGameServer getServerByServerID(int i)
	{//===============================================================================================
		return serversByServerID.get(i);
	}


	//===============================================================================================
	public void incoming_INDEX_Register_Server_Request(Channel channel, String message)
	{//===============================================================================================

		//INDEX_Register_Server_Request:passCode,serverID,ipAddress
		String s = message;
		s = s.substring(s.indexOf(":")+1);//passCode,serverID,ipAddress
		String passCode = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",")+1);
		int serverID = -1;
		try{serverID = Integer.parseInt(s.substring(0, s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
		s = s.substring(s.indexOf(",")+1);
		String ipAddressString = s.substring(0, s.indexOf(":"));

		if(passCode.equals(PrivateCredentials.passwordSalt)==false)
		{
			channel.writeAndFlush(BobNet.Server_Register_Server_With_INDEX_Response+"Incorrect passcode, cannot register with index.:-1:"+BobNet.endline);
			channel.close();
		}
		

		BobsGameServer server = null;
		if(serverID!=-1)
		{
			//look through our hashtables to find that serverID, set the channel to the new one.
			server = serversByServerID.get(serverID);

			if(server!=null)
			{
				serverList.remove(server);
				serversByChannel.remove(server.channel);
				serversByServerID.remove(serverID);

				serverID = server.serverID;
			}
		}



		if(server==null)
		{
			//make a new serverID, add to hashtables.
			server = new BobsGameServer(channel, ipAddressString);
		}

		serverID = server.serverID;

		serverList.add(server);
		serversByChannel.put(channel,server);
		serversByServerID.put(server.serverID,server);


		channel.writeAndFlush(BobNet.Server_Register_Server_With_INDEX_Response+"Successfully registered with index.:"+serverID+":"+BobNet.endline);

	}




	//===============================================================================================
	public void incoming_INDEX_Tell_All_Servers_To_Tell_FacebookIDs_That_UserID_Is_Online(Channel channel, String message)
	{//===============================================================================================


		BobsGameServer thisServer = getServerByChannel(channel);

		//ServerNotifyFacebookFriendsUserIsOnline:userID,`facebookFriendsCSV,`
		String s = message;
		s = s.substring(s.indexOf(":")+1);//userID,`facebookFriendsCSV,`
		int userID = -1;
		try{userID = Integer.parseInt(s.substring(0,s.indexOf(',')));}catch(NumberFormatException ex){ex.printStackTrace();return;}
		s = s.substring(s.indexOf("`")+1);//facebookFriendsCSV,`
		String facebookIDsCSV = s.substring(0,s.indexOf('`'));

		if(userID==-1)return;
		if(facebookIDsCSV.length()==0)return;



		for(int i=0;i<serverList.size();i++)
		{
			Channel c = serverList.get(i).channel;

			if(c.isActive())
			{
				c.writeAndFlush(BobNet.Server_Tell_All_FacebookIDs_That_UserID_Is_Online+thisServer.serverID+","+userID+",`"+facebookIDsCSV+"`"+BobNet.endline);
			}
			else
			{
				log.warn("channel is not connected in incoming_INDEX_Tell_All_Servers_To_Tell_FacebookIDs_That_UserID_Is_Online. Did server drop connection?");
			}
		}



		//TODO: now each of those servers will look up each facebook friend ID in their hashtable, connect to each client and tell them our userID is online.
		//each server should make a LIST of the clients userID it has in its facebook ID hashtable, and send that list of userIDs back to the index server, which sends it back to the originating server, which sends it to the originating client.

	}

	//===============================================================================================
	public void incoming_INDEX_Tell_All_Servers_To_Tell_UserNames_That_UserID_Is_Online(Channel channel, String message)
	{//===============================================================================================


		BobsGameServer thisServer = getServerByChannel(channel);

		//ServerNotifyUserNameFriendsUserIsOnline:userID,`facebookFriendsCSV,`
		String s = message;
		s = s.substring(s.indexOf(":")+1);//userID,`facebookFriendsCSV,`
		int userID = -1;
		try{userID = Integer.parseInt(s.substring(0,s.indexOf(',')));}catch(NumberFormatException ex){ex.printStackTrace();return;}
		s = s.substring(s.indexOf("`")+1);//facebookFriendsCSV,`
		String userNamesCSV = s.substring(0,s.indexOf('`'));

		if(userID==-1)return;
		if(userNamesCSV.length()==0)return;



		for(int i=0;i<serverList.size();i++)
		{
			Channel c = serverList.get(i).channel;

			if(c.isActive())
			{
				c.writeAndFlush(BobNet.Server_Tell_All_UserNames_That_UserID_Is_Online+thisServer.serverID+","+userID+",`"+userNamesCSV+"`"+BobNet.endline);
			}
			else
			{
				log.warn("channel is not connected in incoming_INDEX_Tell_All_Servers_To_Tell_UserNames_That_UserID_Is_Online. Did server drop connection?");
			}
		}


	}
	//===============================================================================================
	public void incoming_INDEX_Tell_ServerID_To_Tell_UserID_That_UserIDs_Are_Online(Channel channel, String message)
	{//===============================================================================================

		//after a user logs in, we sent a list of all their facebook friends to notify to every server.

		//each server will go through its online users and notify any of them that are in that list.

		//it then compiles a list of the users on that server, and sends it back to us, so we can send it back to the original user, so it knows which friends are online so it can try to connect to them.

		int serverID = -1;
		int userID = -1;

		//INDEXTellServerNotifyUserFriendsAreOnline:serverID,userID,`onlineUserIDCSV,`
		String s = message;
		s = s.substring(s.indexOf(":")+1);//serverID,userID,`onlineUserIDCSV,`
		try{serverID = Integer.parseInt(s.substring(0,s.indexOf(',')));}catch(NumberFormatException ex){ex.printStackTrace();}
		s = s.substring(s.indexOf(",")+1);//userID,`onlineUserIDCSV,`
		try{userID = Integer.parseInt(s.substring(0,s.indexOf(',')));}catch(NumberFormatException ex){ex.printStackTrace();}
		s = s.substring(s.indexOf("`")+1);//onlineUserIDCSV,`
		String onlineUserIDCSV = s.substring(0,s.indexOf('`'));

		if(serverID==-1)return;
		if(userID==-1)return;
		if(onlineUserIDCSV.length()==0)return;



		BobsGameServer originalUserServer = getServerByServerID(serverID);
		if(originalUserServer!=null)
		{
			originalUserServer.channel.writeAndFlush(BobNet.Server_Tell_UserID_That_UserIDs_Are_Online+userID+",`"+onlineUserIDCSV+"`"+BobNet.endline);
		}
		else
		{
			log.warn("serverID could not be found during incoming_INDEX_Tell_ServerID_To_Tell_UserID_That_UserIDs_Are_Online. Did server drop connection?");
		}
	}



	//===============================================================================================
	public void incoming_INDEX_User_Logged_On_This_Server_Log_Them_Off_Other_Servers(Channel channel, String message)
	{//===============================================================================================

		//INDEX_User_Logged_On_This_Server_Log_Them_Off_Other_Servers:serverID,userID
		int serverID = -1;
		int userID = -1;
		String s = message;
		s = s.substring(s.indexOf(":")+1);//serverID,userID
		try{serverID = Integer.parseInt(s.substring(0,s.indexOf(',')));}catch(NumberFormatException ex){ex.printStackTrace();}
		s = s.substring(s.indexOf(",")+1);//userID
		try{userID = Integer.parseInt(s.substring(0,s.indexOf(":")));}catch(NumberFormatException ex){ex.printStackTrace();}

		if(serverID==-1)return;
		if(userID==-1)return;



		for(int i=0;i<serverList.size();i++)
		{

			if(serverList.get(i).serverID!=serverID)
			{

				Channel c = serverList.get(i).channel;

				if(c.isActive())
				{
					c.writeAndFlush(BobNet.Server_UserID_Logged_On_Other_Server_So_Log_Them_Off+userID+BobNet.endline);
				}
				else
				{
					log.warn("channel is not connected in incoming_INDEX_User_Logged_On_This_Server_Log_Them_Off_Other_Servers. Did server drop connection?");
				}
			}
		}


	}




	//===============================================================================================
	public void incoming_INDEX_Tell_All_Servers_Bobs_Game_Hosting_Room_Update(Channel channel, String message)
	{//===============================================================================================

		//INDEX_Tell_All_Servers_Bobs_Game_Hosting_Room_Update,serverID,userID,roomString:
		int serverID = -1;
		int userID = -1;
		String s = message;
		s = s.substring(s.indexOf(":")+1);//serverID,userID
		try{serverID = Integer.parseInt(s.substring(0,s.indexOf(',')));}catch(NumberFormatException ex){ex.printStackTrace();}
		s = s.substring(s.indexOf(",")+1);//userID
		try{userID = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();}
		s = s.substring(s.indexOf(",")+1);
		String roomString = s.substring(0,s.indexOf(":"));

		if(serverID==-1)return;
		if(userID==-1)return;



		for(int i=0;i<serverList.size();i++)
		{

			if(serverList.get(i).serverID!=serverID)
			{

				Channel c = serverList.get(i).channel;

				if(c.isActive())
				{
					c.writeAndFlush(BobNet.Server_Bobs_Game_Hosting_Room_Update+serverID+","+userID+","+roomString+":"+BobNet.endline);
				}
				else
				{
					log.warn("channel is not connected in incoming_INDEX_Tell_All_Servers_Bobs_Game_Hosting_Room_Update. Did server drop connection?");
				}
			}
		}

	}



	
	//===============================================================================================
	public void incoming_INDEX_Tell_All_Servers_Bobs_Game_Remove_Room(Channel channel, String message)
	{//===============================================================================================
		
		//INDEX_Tell_All_Servers_Bobs_Game_Remove_Room,serverID,userID,roomString:
		int serverID = -1;
		int userID = -1;
		String s = message;
		s = s.substring(s.indexOf(":")+1);//serverID,userID
		try{serverID = Integer.parseInt(s.substring(0,s.indexOf(',')));}catch(NumberFormatException ex){ex.printStackTrace();}
		s = s.substring(s.indexOf(",")+1);//userID
		try{userID = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();}
		s = s.substring(s.indexOf(",")+1);
		String roomString = s.substring(0,s.indexOf(":"));
		
		if(serverID==-1)return;
		if(userID==-1)return;
		
		
		
		for(int i=0;i<serverList.size();i++)
		{
			
			if(serverList.get(i).serverID!=serverID)
			{
				
				Channel c = serverList.get(i).channel;
				
				if(c.isActive())
				{
					c.writeAndFlush(BobNet.Server_Bobs_Game_Remove_Room+serverID+","+userID+","+roomString+":"+BobNet.endline);
				}
				else
				{
					log.warn("channel is not connected in incoming_INDEX_Tell_All_Servers_Bobs_Game_Remove_Room. Did server drop connection?");
				}
			}
		}
		
		
	}

	//===============================================================================================
	public void incoming_INDEX_Tell_All_Servers_To_Send_Activity_Update_To_All_Clients(Channel channel, String message)
	{//===============================================================================================
		
		//INDEX_Tell_All_Servers_To_Send_Activity_Update_To_All_Clients,serverID,activityString:END:
		int serverID = -1;
		String s = message;
		s = s.substring(s.indexOf(":")+1);//serverID
		try{serverID = Integer.parseInt(s.substring(0,s.indexOf(',')));}catch(NumberFormatException ex){ex.printStackTrace();}
		s = s.substring(s.indexOf(",")+1);
		
		String activityString = s.substring(0,s.indexOf(":END:"));
		
		if(serverID==-1)return;
		
		
		for(int i=0;i<serverList.size();i++)
		{
			
			if(serverList.get(i).serverID!=serverID)
			{
				
				Channel c = serverList.get(i).channel;
				
				if(c.isActive())
				{
					c.writeAndFlush(BobNet.Server_Send_Activity_Update_To_All_Clients+activityString+":END:"+BobNet.endline);
				}
				else
				{
					log.warn("channel is not connected in incoming_INDEX_Tell_All_Servers_To_Send_Activity_Update_To_All_Clients. Did server drop connection?");
				}
			}
		}
	}
	//===============================================================================================
	public void incoming_INDEX_Tell_All_Servers_To_Send_Chat_Message_To_All_Clients(Channel channel, String message)
	{//===============================================================================================

		//INDEX_Tell_All_Servers_To_Send_Chat_Message_To_All_Clients,serverID,activityString:END:
		int serverID = -1;
		String s = message;
		s = s.substring(s.indexOf(":")+1);//serverID
		try{serverID = Integer.parseInt(s.substring(0,s.indexOf(',')));}catch(NumberFormatException ex){ex.printStackTrace();}
		s = s.substring(s.indexOf(",")+1);
		
		String activityString = s.substring(0,s.indexOf(":END:"));

		if(serverID==-1)return;


		for(int i=0;i<serverList.size();i++)
		{

			if(serverList.get(i).serverID!=serverID)
			{

				Channel c = serverList.get(i).channel;

				if(c.isActive())
				{
					c.writeAndFlush(BobNet.Server_Send_Chat_Message_To_All_Clients+activityString+":END:"+BobNet.endline);
				}
				else
				{
					log.warn("channel is not connected in incoming_INDEX_Tell_All_Servers_To_Send_Chat_Message_To_All_Clients. Did server drop connection?");
				}
			}
		}
	}


	//===============================================================================================
	public void send_Tell_All_Servers_To_Tell_All_Clients_Servers_Are_Shutting_Down()
	{//===============================================================================================
		for(int i=0;i<serverList.size();i++)
		{
			Channel c = serverList.get(i).channel;

			if(c.isActive())
			{
				c.writeAndFlush(BobNet.Server_Tell_All_Users_Servers_Are_Shutting_Down+BobNet.endline);
			}
			else
			{
				log.warn("channel is not connected in send_Tell_All_Servers_To_Tell_All_Clients_Servers_Are_Shutting_Down. Did server drop connection?");
			}
		}
	}



	//===============================================================================================
	public void send_Tell_All_Servers_To_Tell_All_Clients_Servers_Have_Shut_Down()
	{//===============================================================================================
		for(int i=0;i<serverList.size();i++)
		{
			Channel c = serverList.get(i).channel;

			if(c.isActive())
			{
				c.writeAndFlush(BobNet.Server_Tell_All_Users_Servers_Have_Shut_Down+BobNet.endline);
			}
			else
			{
				log.warn("channel is not connected in send_Tell_All_Servers_To_Tell_All_Clients_Servers_Have_Shut_Down. Did server drop connection?");
			}
		}
	}







}
