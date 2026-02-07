package com.bobsgame.client.network;

import java.net.InetSocketAddress;
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

import org.slf4j.LoggerFactory;
import ch.qos.logback.classic.Logger;

import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.net.BobNet;

//===============================================================================================
public class UDPConnection extends EnginePart
{//===============================================================================================

	public static Logger log = (Logger) LoggerFactory.getLogger(UDPConnection.class);

	String peerIP_S = "";//synchronized
	int peerUDPPort_S = -1;//synchronized
	int myUDPPort = -1;

	Bootstrap connectionlessBootstrap;
	private Channel channel;
    EventLoopGroup workerGroup;

	private int port;

	long lastReceivedDataTime = System.currentTimeMillis();
	long lastSentPingTime = System.currentTimeMillis();

	//===============================================================================================
	public UDPConnection(Engine g, int myPort)
	{//===============================================================================================

		super(g);

		this.myUDPPort = myPort;

        workerGroup = new NioEventLoopGroup();
		connectionlessBootstrap = new Bootstrap();
        connectionlessBootstrap.group(workerGroup)
            .channel(NioDatagramChannel.class)
            .handler(new ChannelInitializer<NioDatagramChannel>() {
                @Override
                public void initChannel(NioDatagramChannel ch) throws Exception {
                    ChannelPipeline pipeline = ch.pipeline();
                    pipeline.addLast("handler", new UDPHandler());
                }
            });

		//connectionlessBootstrap.setOption("receiveBufferSizePredictorFactory", new AdaptiveReceiveBufferSizePredictorFactory(16000,16000,65536));
		//connectionlessBootstrap.setOption("broadcast", "false");
		//connectionlessBootstrap.setOption("reuseAddress", "true");

		this.port = myUDPPort;

        try {
		    channel = connectionlessBootstrap.bind(port).sync().channel();
		    log.info("UDP Channel: "+channel.id().toString());
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
	}

	//===============================================================================================
	public class UDPHandler extends SimpleChannelInboundHandler<DatagramPacket>
	{//===============================================================================================

		//===============================================================================================
		public UDPHandler()
		{//===============================================================================================
			super();
		}

		//===============================================================================================
		@Override
		public void channelActive(ChannelHandlerContext ctx) throws Exception
		{//===============================================================================================
			log.debug("UDP channelActive: "+ctx.channel().id());
		}
		//===============================================================================================
		@Override
		public void channelInactive(ChannelHandlerContext ctx) throws Exception
		{//===============================================================================================
			log.debug("UDP channelInactive: "+ctx.channel().id());
		}

		//===============================================================================================
		@Override
		protected void channelRead0(ChannelHandlerContext ctx, DatagramPacket packet) throws Exception
		{//===============================================================================================

			try{Thread.currentThread().setName("UDPConnection_UDPHandler");}catch(SecurityException ex){ex.printStackTrace();}

			String s = packet.content().toString(CharsetUtil.UTF_8);

			if(BobNet.debugMode)
			{
				if(s.startsWith("Friend_Location_Update")==false)
				log.warn("FROM CLIENT: cID:"+channel.id()+" | "+s);
			}

			lastReceivedDataTime = System.currentTimeMillis();

			if(s.startsWith("ping"))
			{
				InetSocketAddress peerAddress = getPeerSocketAddress_S();
				if(peerAddress!=null)
				{
					write("pong"+BobNet.endline);
				}
				else
				{
					log.warn("peerAddress was null, but got ping.");
				}
				return;
			}

			if(s.startsWith("pong")){}

			handleMessage(ctx,s, packet.sender());
		}

        @Override
        public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {
             cause.printStackTrace();
             //ctx.close();
        }

	}

	//===============================================================================================
	public void cleanup()
	{//===============================================================================================

		if(channel!=null)channel.close().awaitUninterruptibly();
		workerGroup.shutdownGracefully();
	}

	//===============================================================================================
	public ChannelFuture write(String s)
	{//===============================================================================================

		if(s.endsWith(BobNet.endline)==false)
		{
			log.error("Packet doesn't end with endline");
			s = s +BobNet.endline;
		}

		if(BobNet.debugMode)
		{
			if(s.startsWith("Friend_Location_Update")==false&&s.startsWith("Friend_Connect_Request")==false)
			log.debug("SEND CLIENT: cID:"+channel.id()+" | "+s.substring(0,s.length()-2));
		}

		InetSocketAddress peerAddress = getPeerSocketAddress_S();
		if(peerAddress!=null)
		{
			return write(s,getPeerSocketAddress_S());
		}
		else log.warn("peerAddress was null.");

		return null;

	}
	//===============================================================================================
	public synchronized ChannelFuture write(String s,InetSocketAddress address)
	{//===============================================================================================
		ChannelFuture c = channel.writeAndFlush(new DatagramPacket(
                Unpooled.copiedBuffer(s, CharsetUtil.UTF_8),
                address));
		return c;
	}





	private InetSocketAddress _peerAddress = null;

	//===============================================================================================
	protected synchronized InetSocketAddress getPeerSocketAddress_S()
	{//===============================================================================================
		return _peerAddress;
	}
	//===============================================================================================
	public synchronized void setPeerSocketAddress_S(String ipAddress, int port)
	{//===============================================================================================

		if(ipAddress==null)_peerAddress=null;
		else
		_peerAddress = new InetSocketAddress(ipAddress,port);
	}



	boolean established_NonThreaded = false;
	//===============================================================================================
	public boolean established()
	{//===============================================================================================
		return established_NonThreaded;
	}
	//===============================================================================================
	public void setEstablished(boolean b)
	{//===============================================================================================
		established_NonThreaded = b;
	}





	boolean gotPeerConnectResponse_S = false;
	//===============================================================================================
	synchronized boolean gotConnectResponse_S()
	{//===============================================================================================
		return gotPeerConnectResponse_S;
	}
	//===============================================================================================
	protected synchronized void setGotPeerConnectResponse_S(boolean b)
	{//===============================================================================================
		gotPeerConnectResponse_S = b;
	}




	long lastConnectAttemptTime = System.currentTimeMillis();
	//===============================================================================================
	public void update()
	{//===============================================================================================

		//see if we have a udp connection to them established
		if(established()==false)
		{
			long currentTime = System.currentTimeMillis();

			//if we don't, keep pinging the stun server with our request. they should be doing the same thing.
			if(currentTime-lastConnectAttemptTime>500)
			{
				lastConnectAttemptTime=currentTime;

				if(getPeerSocketAddress_S()==null)
				{
					sendAddressRequest();
				}
				else
				{

					if(gotConnectResponse_S()==false)
					{
						sendPeerConnectRequest();
					}
					else
					{
						setEstablished(true);
					}
				}
			}
		}

		if(established()==true)
		{
			long currentTime = System.currentTimeMillis();

			//-----------------------------
			//connection is established!
			//-----------------------------

			//send keepalive
			//keep last got friend keepalive ping/pong
			if(currentTime-lastReceivedDataTime>10000)//10 seconds
			{
				//send ping
				if(currentTime-lastSentPingTime>10000)
				{
					lastSentPingTime = currentTime;
					write("ping"+BobNet.endline);
				}
			}

			if(currentTime-lastReceivedDataTime>60000)//60 seconds
			{
				//assume peer has gone offline
				//close if no keepalive
				established_NonThreaded = false;
				setPeerSocketAddress_S(null,-1);

				handleDisconnected();
			}
		}
	}



	//===============================================================================================
	public void handleMessage(ChannelHandlerContext ctx, String s, InetSocketAddress sender)
	{//===============================================================================================
		//override this
		log.error("This function should always be overridden");
	}
	//===============================================================================================
	public void incomingPeerConnectResponse(String s)
	{//===============================================================================================
		//override this
		log.error("This function should always be overridden");
	}
	//===============================================================================================
	public void sendAddressRequest()
	{//===============================================================================================
		//override this
		log.error("This function should always be overridden");
	}
	//===============================================================================================
	public void sendPeerConnectRequest()
	{//===============================================================================================
		//override this
		log.error("This function should always be overridden");
	}
	//===============================================================================================
	public void sendPeerConnectResponse()
	{//===============================================================================================
		//override this
		log.error("This function should always be overridden");
	}
	//===============================================================================================
	public void handleDisconnected()
	{//===============================================================================================

		//override this

		log.error("Disconnected from "+getPeerSocketAddress_S());
	}

}
