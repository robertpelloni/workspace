package com.bobsgame.client.engine.event;

import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;


//=========================================================================================================================
public class ServerObject extends EnginePart
{//=========================================================================================================================
	//=========================================================================================================================
	public ServerObject(Engine g)
	{//=========================================================================================================================
		super(g);
	}


	protected boolean _initialized = false;
	protected long lastTimeRequestedFromServer=0;
	//=========================================================================================================================
	public synchronized boolean getInitialized_S()
	{//=========================================================================================================================
		return _initialized;
	}
	//=========================================================================================================================
	protected synchronized void setInitialized_S(boolean i)
	{//=========================================================================================================================
		_initialized=i;
	}
	//=========================================================================================================================
	private void sendServerRequest()
	{//=========================================================================================================================
		if(getInitialized_S() == false)
		{
			//send a request to the server
			long time = System.currentTimeMillis();
			if(time-lastTimeRequestedFromServer>1000)
			{
				Network().sendServerObjectRequest(this);
				lastTimeRequestedFromServer=time;
			}
		}
	}


	protected boolean loadedInfoDataFromServer = false;//non-threaded check
	protected long lastCheckedInitializedTime = 0;
	//=========================================================================================================================
	protected boolean getLoadedFromServerSendRequestIfFalse()
	{//=========================================================================================================================

		if(loadedInfoDataFromServer==false)
		{
			//small delay to prevent thread locking on synchronized functions.
			long time = System.currentTimeMillis();
			if(time-lastCheckedInitializedTime>200)
			{
				lastCheckedInitializedTime = time;

				if(getInitialized_S() == false)
				{
					//this has its own timer delay for network requests
					sendServerRequest();
				}
				else
				{
					loadedInfoDataFromServer = true;
				}
			}
		}
		return loadedInfoDataFromServer;
	}
	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================
		if(getLoadedFromServerSendRequestIfFalse())
		{

		}
	}












}
