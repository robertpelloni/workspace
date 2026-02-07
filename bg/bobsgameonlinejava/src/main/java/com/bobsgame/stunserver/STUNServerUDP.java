package com.bobsgame.stunserver;

import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.util.Vector;
import java.util.concurrent.Executors;

import com.bobsgame.STUNServerMain;
import io.netty.bootstrap.Bootstrap;
import io.netty.channel.Channel;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.ChannelPipeline;
import io.netty.channel.EventLoopGroup;
import io.netty.channel.SimpleChannelInboundHandler;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.DatagramPacket;
import io.netty.channel.socket.nio.NioDatagramChannel;
import io.netty.util.CharsetUtil;
import io.netty.buffer.Unpooled;
import io.netty.util.concurrent.DefaultEventExecutorGroup;
import io.netty.util.concurrent.EventExecutorGroup;

import org.slf4j.LoggerFactory;
import ch.qos.logback.classic.Logger;

import com.bobsgame.net.BobNet;


//===============================================================================================
public class STUNServerUDP
{//===============================================================================================


	//TODO: are we sure we want 16 threads??? optimise this.
	static final EventExecutorGroup group = new DefaultEventExecutorGroup(16);


	Bootstrap connectionlessBootstrap;
	Channel channel;
    EventLoopGroup workerGroup;

	public static Logger log = (Logger)LoggerFactory.getLogger(STUNServerUDP.class);


	//===============================================================================================
	public STUNServerUDP()
	{//===============================================================================================


        workerGroup = new NioEventLoopGroup();
		connectionlessBootstrap = new Bootstrap();
        connectionlessBootstrap.group(workerGroup)
            .channel(NioDatagramChannel.class)
            .handler(new ChannelInitializer<NioDatagramChannel>() {
                @Override
                public void initChannel(NioDatagramChannel ch) throws Exception {
                    ChannelPipeline pipeline = ch.pipeline();
                    pipeline.addLast(group, "handler", new UDPHandler());
                }
            });

		//connectionlessBootstrap.setOption("sendBufferSize", 524288);
		//connectionlessBootstrap.setOption("receiveBufferSize", 524288);
		//connectionlessBootstrap.setOption("broadcast", "false");

		int serverPort = BobNet.STUNServerUDPPort;

        try {
		    channel = connectionlessBootstrap.bind(serverPort).sync().channel();
		    log.info("udp Channel: "+channel.id().toString());
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

	}




	//===============================================================================================
	public void cleanup()
	{//===============================================================================================
		workerGroup.shutdownGracefully();
	}


	//===============================================================================================
	public class UDPHandler extends SimpleChannelInboundHandler<DatagramPacket>
	{//===============================================================================================

		//===============================================================================================
		@Override
		public void channelActive(ChannelHandlerContext ctx) throws Exception
		{//===============================================================================================
			log.debug("UDP channelConnected:"+ctx.channel().id());
		}
		//===============================================================================================
		@Override
		public void channelInactive(ChannelHandlerContext ctx) throws Exception
		{//===============================================================================================
			log.debug("UDP channelDisconnected:"+ctx.channel().id());
		}

		//===============================================================================================
		@Override
		protected void channelRead0(ChannelHandlerContext ctx, DatagramPacket packet) throws Exception
		{//===============================================================================================

			String s = packet.content().toString(CharsetUtil.UTF_8);

			//if(BobNet.debugMode)
			{
				log.debug("UDP messageReceived:"+s);
			}

			STUNServerMain.totalConnections++;

			if(s.startsWith(BobNet.STUN_Request)){incomingSTUNRequest(packet, s);return;}


		}
	}




	//===============================================================================================
	public class STUNRequest
	{//===============================================================================================
		public long userID1 = -1;
		public long userID2 = -1;
		public long lastHeardFromTime = 0;
		public int user1Port = -1;
		public int user2Port = -1;

		public InetSocketAddress userIP1 = null;
		public InetSocketAddress userIP2 = null;


		public STUNRequest(long userID1, long userID2, InetSocketAddress userIP1, int user1Port)
		{
			lastHeardFromTime = System.currentTimeMillis();
			this.userID1 = userID1;
			this.userID2 = userID2;
			this.userIP1 = userIP1;
			this.user1Port = user1Port;

		}

	}



	Vector<STUNRequest> STUNRequestList = new Vector<STUNRequest>();


	//===============================================================================================
	public synchronized int getSTUNRequestListSize()
	{//===============================================================================================
		return STUNRequestList.size();
	}

	//===============================================================================================
	synchronized void addToSTUNRequestList(STUNRequest s)
	{//===============================================================================================
		STUNRequestList.add(s);
	}

	//===============================================================================================
	synchronized void removeFromSTUNRequestList(STUNRequest s)
	{//===============================================================================================
		STUNRequestList.remove(s);
	}

	//===============================================================================================
	synchronized void removeFromSTUNRequestList(int i)
	{//===============================================================================================
		STUNRequestList.remove(i);
	}

	//===============================================================================================
	synchronized STUNRequest getFromSTUNRequestList(int i)
	{//===============================================================================================
		return STUNRequestList.get(i);
	}

	//===============================================================================================
	public void update()
	{//===============================================================================================
		for(int i=0;i<getSTUNRequestListSize();i++)
		{

			STUNRequest r = getFromSTUNRequestList(i);

			if(System.currentTimeMillis()-r.lastHeardFromTime>10000)//10 seconds
			{

				if(r.userIP1!=null&&r.userIP2!=null)STUNServerMain.totalSTUNsCompleted++;
				else STUNServerMain.totalSTUNsTimedOut++;

				removeFromSTUNRequestList(i);
				i--;
			}
		}


	}

	//===============================================================================================
	public STUNRequest getSTUNRequestFor(long userID, long friendID)
	{//===============================================================================================

		for(int i=0;i<getSTUNRequestListSize();i++)
		{
			STUNRequest s = getFromSTUNRequestList(i);

			if(
				(s.userID1==userID && s.userID2==friendID)
				||
				(s.userID1==friendID && s.userID2==userID)
			)return s;
		}

		return null;
	}

	//===============================================================================================
	private void incomingSTUNRequest(DatagramPacket packet, String s)
	{//===============================================================================================

		//String s = (String) e.getMessage();

		//STUNRequest:userID,friendID
		s = s.substring(s.indexOf(":")+1);
		long userID = -1;
		try{userID = Long.parseLong(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}

		s = s.substring(s.indexOf(",")+1);
		long friendID = -1;
		try{friendID = Long.parseLong(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}


		s = s.substring(s.indexOf(",")+1);
		int port = -1;
		try{port = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}

		//look up userID in RequestList

		STUNRequest r = getSTUNRequestFor(userID, friendID);

		if(r==null)
		{
			log.debug("Created request, waiting: userID: "+userID+" friendID:"+friendID);
			addToSTUNRequestList(new STUNRequest(userID,friendID,packet.sender(),port));
		}
		else
		{
			r.lastHeardFromTime = System.currentTimeMillis();

			if(r.userID2==userID)//i didn't create the request first, my friend did.
			{
				log.debug("Found pair: userID2: "+r.userID2+" userID1:"+r.userID1);
				//we have a completed pair
				r.userIP2 = packet.sender();
				r.user2Port = port;

                channel.writeAndFlush(new DatagramPacket(
                    Unpooled.copiedBuffer(BobNet.STUN_Response+r.userID2+","+r.userIP2.toString()+","+r.user2Port+","+BobNet.endline, CharsetUtil.UTF_8),
                    r.userIP1));

                channel.writeAndFlush(new DatagramPacket(
                    Unpooled.copiedBuffer(BobNet.STUN_Response+r.userID1+","+r.userIP1.toString()+","+r.user1Port+","+BobNet.endline, CharsetUtil.UTF_8),
                    r.userIP2));

				//removeFromSTUNRequestList(r);
			}
			else //i created the request, but i didn't get the ping for some reason when they completed the request.
			{
				if(r.userIP1!=null&&r.userIP2!=null)
				{
					log.debug("Found late pair: userID1: "+r.userID1+" userID2:"+r.userID2);

                    channel.writeAndFlush(new DatagramPacket(
                        Unpooled.copiedBuffer(BobNet.STUN_Response+r.userID2+","+r.userIP2.toString()+","+r.user2Port+","+BobNet.endline, CharsetUtil.UTF_8),
                        r.userIP1));

                    channel.writeAndFlush(new DatagramPacket(
                        Unpooled.copiedBuffer(BobNet.STUN_Response+r.userID1+","+r.userIP1.toString()+","+r.user1Port+","+BobNet.endline, CharsetUtil.UTF_8),
                        r.userIP2));
				}
				else
				{
					//still waiting
				}
			}
		}
	}






}
