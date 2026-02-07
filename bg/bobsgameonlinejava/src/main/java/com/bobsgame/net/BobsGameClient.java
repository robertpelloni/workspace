package com.bobsgame.net;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import io.netty.channel.Channel;



//===============================================================================================
public class BobsGameClient
{//===============================================================================================


	public Channel channel = null;//reference to the netty TCP socket connection, can get IP and port from this.

	public long userID = -1;//filled in when credentials are verified from the DB.
	public String facebookID = "";//also filled in, for easy indexing of facebook friends online
	public String userName = "";//also filled in, for easy indexing of friends online
	public String emailAddress = "";//also filled in, for easy indexing of friends online




	public String encryptionKey = "";

	public long startTime = -1;




}
