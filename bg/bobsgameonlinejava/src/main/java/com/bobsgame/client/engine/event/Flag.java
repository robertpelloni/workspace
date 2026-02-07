package com.bobsgame.client.engine.event;

import com.bobsgame.client.engine.Engine;
import com.bobsgame.shared.FlagData;

//=========================================================================================================================
public class Flag extends ServerObject
{//=========================================================================================================================

	private boolean value = false;
	private long timeSet = -1;

	private FlagData data;

	//=========================================================================================================================
	public Flag(Engine g, int id)
	{//=========================================================================================================================
		super(g);

		this.data = new FlagData(id,"");

		for(int i=0;i<EventManager().flagList.size();i++){if(EventManager().flagList.get(i).id()==data.id()){log.error("Flag already exists:"+data.name());return;}}
		EventManager().flagList.add(this);

		//we don't particularly need to know what the actual flag name is... ID is fine.
		//so, don't really care about getting the flag name from the server.
		//it's a good idea for debugging.
	}

	//=========================================================================================================================
	public Flag(Engine g, FlagData data)
	{//=========================================================================================================================
		super(g);

		this.data = data;
		setInitialized_S(true);

		for(int i=0;i<EventManager().flagList.size();i++){if(EventManager().flagList.get(i).id()==data.id()){log.error("Flag already exists:"+data.name());return;}}
		EventManager().flagList.add(this);
	}

	//=========================================================================================================================
	public synchronized void setData_S(FlagData data)
	{//=========================================================================================================================
		this.data = data;
		setInitialized_S(true);
	}



	public FlagData getData(){return data;}


	public int id(){return getData().id();}
	public String name(){return getData().name();}
	public String getTYPEIDString(){return getData().getTYPEIDString();}


	public void setID(int id){getData().setID(id);}
	public void setName(String name){getData().setName(name);}





	//=========================================================================================================================
	public synchronized void setValue_S(boolean b)//sendServerValueUpdate(boolean b)
	{//=========================================================================================================================

		//send a request to the server

		timeSet = System.currentTimeMillis();
		value = b;

		if(b==true)Network().addQueuedGameSaveUpdateRequest_S("flagsSet:`"+id()+":true:"+timeSet+"`");
		if(b==false)Network().addQueuedGameSaveUpdateRequest_S("flagsSet:`"+id()+":false:"+timeSet+"`");

	}

	//=========================================================================================================================
	public synchronized void initValueFromGameSave_S(boolean b, long timeSet)//sendServerValueUpdate(boolean b)
	{//=========================================================================================================================

		this.value = b;
		this.timeSet = timeSet;

	}

	//=========================================================================================================================
	public synchronized boolean getValue_S()
	{//=========================================================================================================================
		return value;
	}

	//=========================================================================================================================
	public long getTimeSet()
	{//=========================================================================================================================
		return timeSet;
	}



}
