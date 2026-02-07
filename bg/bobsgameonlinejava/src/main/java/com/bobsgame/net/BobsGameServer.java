package com.bobsgame.net;



import io.netty.channel.Channel;

public class BobsGameServer
{
	public Channel channel = null;//reference to the netty TCP socket connection, can get IP and port from this.

	public int serverID = -1;

	public String ipAddressString = "";



	public static int lastServerID = 0;

	public BobsGameServer(Channel c, String ipAddressString)
	{
		this.serverID = lastServerID;

		lastServerID++;

		this.channel = c;

		this.ipAddressString = ipAddressString;

	}


}
