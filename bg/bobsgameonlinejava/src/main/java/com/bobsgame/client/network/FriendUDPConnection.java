package com.bobsgame.client.network;

import java.net.InetSocketAddress;

import com.bobsgame.ClientMain;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.game.FriendCharacter;
import com.bobsgame.net.BobNet;


//===============================================================================================
public class FriendUDPConnection extends UDPConnection implements UDPInterface
{//===============================================================================================


	FriendCharacter friend = null;


	public static InetSocketAddress stunServerAddress = new InetSocketAddress(ClientMain.STUNServerAddress,BobNet.STUNServerUDPPort);

	//===============================================================================================
	public FriendUDPConnection(Engine g, int myPort, FriendCharacter friend)
	{//===============================================================================================
		super(g, myPort);
		this.friend = friend;
	}

	//===============================================================================================
	@Override
	public void handleMessage(String s)
	{//===============================================================================================

		if(s.startsWith(BobNet.STUN_Response)){incomingSTUNReply(s);return;}


		//if(e.getRemoteAddress().toString().equals(getPeerSocketAddress_S().toString())==false)
		//{
		//	log.error("Peer IP address didn't match on handleMessage");
		//	return;
		//}



		if(s.startsWith(BobNet.Friend_Connect_Request)){sendPeerConnectResponse();return;}
		if(s.startsWith(BobNet.Friend_Connect_Response)){incomingPeerConnectResponse(s);return;}

		if(friend!=null)friend.handleMessage(s);
	}





	//===============================================================================================
	@Override
	public void sendAddressRequest()
	{//===============================================================================================
		sendSTUNRequest();
	}

	//===============================================================================================
	public void sendSTUNRequest()
	{//===============================================================================================
		write(BobNet.STUN_Request+GameSave().userID+","+friend.friendUserID+BobNet.endline,stunServerAddress);
	}



	//===============================================================================================
	public void incomingSTUNReply(String s)
	{//===============================================================================================


		//make sure it is from the correct IP
		//if(e.getRemoteAddress().toString().equals(stunServerAddress.toString())==false)
		//{
		//	log.error("STUN IP address didn't match stunServerAddress");
		//	return;
		//}


		String friendIP = "";
		int friendPort = -1;

		//STUNResponse:friendUserID,/127.0f.0f.1:port
		s = s.substring(s.indexOf(":")+1);//friendUserID,/127.0f.0f.1:port
		int replyFriendUserID = -1;
		try{replyFriendUserID = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
		if(friend.friendUserID!=replyFriendUserID){log.error("Friend userID did not match in STUN reply! Something is wrong.");return;}
		s = s.substring(s.indexOf(",")+1);///127.0f.0f.1:port

		//socketString looks like /127.0f.0f.1:port
		s = s.substring(s.indexOf("/")+1);
		friendIP = s.substring(0,s.indexOf(":"));
		s = s.substring(s.indexOf(":")+1);//port
		try{friendPort = Integer.parseInt(s);}catch(NumberFormatException ex){ex.printStackTrace();return;}


		if(friendIP.length()==0)return;
		if(friendPort==-1)return;

		setPeerSocketAddress_S(friendIP,friendPort);

	}








	//===============================================================================================
	@Override
	public void sendPeerConnectRequest()
	{//===============================================================================================
		write(BobNet.Friend_Connect_Request+GameSave().userID+BobNet.endline);
	}

	//===============================================================================================
	@Override
	public void sendPeerConnectResponse()
	{//===============================================================================================
		write(BobNet.Friend_Connect_Response+GameSave().userID+BobNet.endline);
	}

	//===============================================================================================
	@Override
	public void incomingPeerConnectResponse(String s)
	{//===============================================================================================

		//FriendConnectResponse:friendUserID
		s = s.substring(s.indexOf(":")+1);
		int replyFriendUserID = -1;
		try{replyFriendUserID = Integer.parseInt(s);}catch(NumberFormatException ex){ex.printStackTrace();return;}


		if(BobNet.debugMode==false)
		{
			if(friend.friendUserID!=replyFriendUserID){log.error("Friend userID did not match in Friend reply! Something is wrong.");return;}
		}

		setGotPeerConnectResponse_S(true);
	}










	//===============================================================================================
	@Override
	public void handleDisconnected()
	{//===============================================================================================
		friend.handleDisconnected();
	}



	//===============================================================================================
	@Override
	public void update()
	{//===============================================================================================


		//ON SERVER
		//get from DB friends online by social ID
		//send list of friendUserIDs to client



		//tell other servers to alert friends we are online (and our userid)
		//go through connections, match friend userID in sessionHashtable, tell them we are online
		//TODO: could store which server they are connected to in ElasticCache so no messing around, could store channel ID in ElasticCache too so no lookups.


		//for each friend, client makes a udp connection
		//makes request to stun server
		//stun server replies with udp with friends IP/port


		//client pings other clients, vice versa, open tunnel
		//connections made


		//TODO: server should send TCP friend offline, remove this from friendManager



		//the stun server should hold onto requests for maybe a minute and then delete them

		//if the stun server replies with their ip/udp port, start sending packets on the same udp connection to that ip/port.

		//if we receive a packet from the friends, the connection is established.

		super.update();


	}







}
