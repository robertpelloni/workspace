#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#include "Room.h"

//=========================================================================================================================
void GameLogic::sendPacketsToOtherPlayers()
{//=========================================================================================================================
	long long currentTime = System::currentHighResTimer();

	//DONE: queue up packets, with id, md5

	//storeNetworkPackets()
	{

		long long ticksPassed = (long long)System::getTicksBetweenTimes(storePacketsTicksCounter, currentTime);
		if (ticksPassed > 200)
		{
			storePacketsTicksCounter = currentTime;

			ArrayList<FrameState> packetToSplit = framesArray;
			framesArray = ArrayList<FrameState>();

			int maxFramesInPacket = 800/16;

			if ((int)packetToSplit.size() > maxFramesInPacket)
			{
				log.debug("Splitting packet");
				//if player 1 has been playing for a while, the network packet will have too many frames in it.
				//so we split it into multiple packets.
				while (packetToSplit.size() > 0)
				{
					ArrayList<FrameState> partialPacket;

					int size = packetToSplit.size();
					for (int i = 0; i < maxFramesInPacket && i < size; i++)
					{
						FrameState frame = packetToSplit.get(0);

						packetToSplit.removeAt(0);
						//Vector<FrameState>::removeAt(packetToSplit.frameStates,0);

						partialPacket.add(frame);
						size--;
					}

					allNetworkPacketsSentUpUntilNow.add(partialPacket);
				}

			}
			else
			if ((int)packetToSplit.size() > 0)
			{
				allNetworkPacketsSentUpUntilNow.add(packetToSplit);
			}
		}
	}

	//queueSendPackets()
	{
		int size = allNetworkPacketsSentUpUntilNow.size();

		for (int j = lastSentPacketID; j < size; j++)
		{

			ArrayList<FrameState> networkPacket = allNetworkPacketsSentUpUntilNow.get(j);

			string b64zip = FrameState::getFrameStatesAsBase64LZ4XML(networkPacket);
			string md5 = FileUtils::getStringMD5(b64zip);

			//log.debug("Packet Size: "+b64zip.length());

			string idAndMD5String = to_string(j) + "," + md5;

			outboundPacketQueueVector.add(idAndMD5String); //just so we have an ordered list we can get(0) from
			outboundPacketQueueHashMap.put(idAndMD5String, b64zip);
		}

		lastSentPacketID = size;
	}


	//send our local players network packets to all peers
	//send_QueuedPacket()
	{
		//send packet 0

		if (outboundPacketQueueVector.size() > 0)
		{
			string idAndMD5String = outboundPacketQueueVector.get(0);
			string b64zip = outboundPacketQueueHashMap.get(idAndMD5String);

			getBobsGame()->sendAllJoinedPeers(BobsGame::netCommand_FRAME + player->getID() + ":" + idAndMD5String + ":" + b64zip);

			//remove id,MD5 from vector queue 	
			//remove id,MD5 from hashmap queue 	
			//if got id, md5, remove packet 0 	
			//if not, send packet 0 again 	
			outboundPacketQueueHashMap.removeAt(idAndMD5String);
			outboundPacketQueueVector.removeAt(0);// idAndMD5String);
		}
	}

	
}



//=========================================================================================================================
void GameLogic::incoming_FramePacket(const string &s)
{ //=========================================================================================================================

	setLastTimeGotIncomingTraffic();

	incomingPacketQueuePush_S(s);

	if(packetProcessThreadStarted == false)
	{
		//log.debug("Creating frame processing thread");
		packetProcessThread = thread(&GameLogic::_packetProcessThreadLoop,this);
		packetProcessThreadStarted = true;
	}

}

//=========================================================================================================================
void GameLogic::_packetProcessThreadLoop(GameLogic *g)
{//=========================================================================================================================

	//log.debug("Started frame processing thread");
	while (g->getStopThread_S()==false)
	{
		this_thread::sleep_for(chrono::milliseconds(100));

		g->_processIncomingPackets();
	}
}

//=========================================================================================================================
void GameLogic::_processIncomingPackets()
{//=========================================================================================================================

	while (incomingPacketQueueSize_S() > 0)
	{
		this_thread::sleep_for(chrono::milliseconds(10));

		string s = incomingPacketQueueFront_S();
		incomingPacketQueuePop_S();

		//packetID,MD5:base64

		//get ID, md5
		if (s.find(":") == -1)
		{
			return;
		}
		string idMD5 = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		string frameData = s.substr(0, s.find(":"));

		long long id = -1;
		try
		{
			id = StringConverterHelper::fromString<long long>(idMD5.substr(0, idMD5.find(",")));
		}
		catch (exception)
		{
			log.error("Failed to parse framePacket ID in incoming frame packet");
			return;
		}
		string md5 = idMD5.substr(idMD5.find(",") + 1);

		string compMD5 = FileUtils::getStringMD5(frameData);
		if (md5 != compMD5)
		{
			log.error("Frame Packet MD5 did not match!");
			return;
		}

		//store id, md5 in "got packets" log so we don't add the same frame packet twice, in case our "OK" doesn't make it back and they keep sending it
		if (_gotPacketsLog.contains(idMD5) == false)
		{

			//if not in log, add to log, add frames to queue, send back id, md5 as confirmation
			ArrayList<FrameState> packet = FrameState::getFramesArrayFromBase64LZ4XML(frameData);

			//queue<FrameState> frames = packet.frameStates;

			if (packet.size() > 0)
			{
				//log.info("Added framePacket ID: "+id);
				if (incomingFramePacketsContainsKey_S(id))
				{
					log.error("Incoming framePacket was already inserted into incomingFramePackets");
				}
				else
				{
					incomingFramePacketsPut_S(id, packet);
				}

				_gotPacketsLog.add(idMD5);

			}
		}
	}
}


//=========================================================================================================================
//void GameLogic::incoming_Forfeit(string s)
//{ //=========================================================================================================================
//
//  //randomSeed:
//
//	if (s.find(":") == -1)
//	{
//		return;
//	}
//	long long theirRandomSeed = -1;
//	try
//	{
//		theirRandomSeed = StringConverterHelper::fromString<long long>(s.substr(0, s.find(":")));
//	}
//	catch (exception)
//	{
//		log.error("Failed to parse randomSeed in incoming frame packet");
//		return;
//	}
//	//s = s.substring(s.indexOf(":")+1);
//
//#ifdef _DEBUG
//		log.error("incoming_Forfeit: Their Seed: " + to_string(theirRandomSeed));
//#endif
//	//Game them = games.get(randomSeed);
//	//if(them==null){log.error("Could not find game with seed:" + randomSeed);return;}
//
//	setTheyForfeit(true);
//
//}
//
//void GameLogic::sendForfeit()
//{ //=========================================================================================================================
//	connection->write(netCommand_FORFEIT + to_string(randomSeed) + ":" + "-1" + BobNet::endline);
//}



long long GameLogic::getLastTimeGotIncomingTraffic()
{
	return lastIncomingTrafficTime;
}

void GameLogic::setLastTimeGotIncomingTraffic()
{
	this->lastIncomingTrafficTime = System::currentHighResTimer();
}

bool GameLogic::getTheyForfeit()
{
	return theyForfeit;
}

void GameLogic::setTheyForfeit(bool b)
{
	this->theyForfeit = b;
}
