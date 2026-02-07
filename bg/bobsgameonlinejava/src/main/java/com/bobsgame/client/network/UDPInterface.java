package com.bobsgame.client.network;

//import org.jboss.netty.channel.ChannelHandlerContext;
//import org.jboss.netty.channel.MessageEvent;

public interface UDPInterface {
	void sendAddressRequest();
	void sendPeerConnectRequest();
	void handleDisconnected();
	void incomingPeerConnectResponse(String s);
	void update();
	void handleMessage(String s);
}