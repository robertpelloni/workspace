package com.bobsgame.client.engine.game;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.Vector;


import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.net.BobNet;
//===============================================================================================
public class FriendManager extends EnginePart
{//===============================================================================================


	public int lastUsedUDPPort = BobNet.clientUDPPortStartRange;

	//vector because threads will access it
	public Vector<FriendCharacter> friendCharacters = new Vector<FriendCharacter>();


	public int myStatus = FriendCharacter.status_AVAILABLE;

	//===============================================================================================
	public FriendManager(ClientGameEngine g)
	{//===============================================================================================
		super(g);

	}


	//===============================================================================================
	public void init()
	{//===============================================================================================

		if(BobNet.debugMode)
		{

			int timesRun = 0;


			//get file with times run

			//get times run

			//write back with timesrun+1

			File sessionFile = new File("F:\\source\\games\\bobsgame\\workspace\\simulator.txt");

			if(sessionFile.exists()==false)
			{
				try
				{
					sessionFile.createNewFile();
				}
				catch (IOException e1)
				{
					e1.printStackTrace();
				}
			}


			String line = null;

			try
			{
				BufferedReader input =  new BufferedReader(new FileReader(sessionFile));
				line = input.readLine();
				input.close();
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}

			if(line!=null)
			{
				if(line.length()>0)
				{
					timesRun = Integer.parseInt(line);
					log.debug(""+timesRun);
				}
			}



			Writer output;
			try
			{
				output = new BufferedWriter(new FileWriter(sessionFile));
				output.write(""+(timesRun+1));
				output.close();
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}



			int myPort = 1111;
			int theirPort = 1112;

			if(timesRun%2==0)
			{
				theirPort = 1111;
				myPort = 1112;
			}


			FriendCharacter f = new FriendCharacter(ClientGameEngine(),1,FriendCharacter.FACEBOOK_TYPE,myPort,theirPort, null);


			friendCharacters.add(f);


		}

	}


	//===============================================================================================
	public void cleanup()
	{//===============================================================================================

		for(int i=0;i<friendCharacters.size();i++)
		{
			friendCharacters.get(i).cleanup();
		}
	}


	//this should keep a list of all the friends online
	//each friend is a unique UDP client connection with a unique designated UDP port.
	//go through the list and update those.


	//===============================================================================================
	public void update()
	{//===============================================================================================

		for(int i=0;i<friendCharacters.size();i++)
		{
			friendCharacters.get(i).update();
		}

	}

	//===============================================================================================
	public int getNextUDPPort()
	{//===============================================================================================

		lastUsedUDPPort++;

		return lastUsedUDPPort-1;
	}

	//===============================================================================================
	synchronized public void addNewOnlineFriendIfNotExist(int friendUserID, int friendType)
	{//===============================================================================================
		for(int i=0;i<friendCharacters.size();i++)
		{
			if(friendCharacters.get(i).friendUserID==friendUserID)return;
		}


		friendCharacters.add(new FriendCharacter(ClientGameEngine(),friendUserID,friendType, null));
	}















}
