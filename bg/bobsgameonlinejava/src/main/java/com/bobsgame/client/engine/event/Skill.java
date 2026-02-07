package com.bobsgame.client.engine.event;

import com.bobsgame.client.engine.Engine;
import com.bobsgame.shared.SkillData;

//=========================================================================================================================
public class Skill extends ServerObject
{//=========================================================================================================================

	private long timeSet = -1;
	private float value = 0.0f;

	private SkillData data;


	//=========================================================================================================================
	public Skill(Engine g, int id)
	{//=========================================================================================================================
		super(g);

		this.data = new SkillData(id,"");

		for(int i=0;i<EventManager().skillList.size();i++){if(EventManager().skillList.get(i).id()==data.id()){log.error("Skill already exists:"+data.name());return;}}
		EventManager().skillList.add(this);
	}


	//=========================================================================================================================
	public Skill(Engine g, SkillData data)
	{//=========================================================================================================================
		super(g);

		this.data = data;
		setInitialized_S(true);

		for(int i=0;i<EventManager().skillList.size();i++){if(EventManager().skillList.get(i).id()==data.id()){log.error("Skill already exists:"+data.name());return;}}
		EventManager().skillList.add(this);
	}




	public SkillData getData(){return data;}


	public int id(){return getData().id();}
	public String name(){return getData().name();}

	public String getTYPEIDString(){return getData().getTYPEIDString();}


	public void setID(int id){getData().setID(id);}
	public void setName(String name){getData().setName(name);}






	//=========================================================================================================================
	public synchronized void setData_S(SkillData data)
	{//=========================================================================================================================
		this.data = data;
		setInitialized_S(true);
	}


	//=========================================================================================================================
	public synchronized void setValue_S(float f)
	{//=========================================================================================================================
		timeSet = System.currentTimeMillis();
		value = f;
		Network().addQueuedGameSaveUpdateRequest_S("skillValues:`"+data.id()+":"+f+":"+timeSet+"`");
	}
	//=========================================================================================================================
	public synchronized void initValueFromGameSave_S(float f, long timeSet)
	{//=========================================================================================================================
		value = f;
		this.timeSet = timeSet;
	}
	//=========================================================================================================================
	public synchronized float getValue_S()
	{//=========================================================================================================================
		return value;
	}
	//=========================================================================================================================
	public long getTimeSet()
	{//=========================================================================================================================
		return timeSet;
	}


//	//=========================================================================================================================
//	public void sendServerSkillValueRequest()
//	{//=========================================================================================================================
//
//		//send a request to the server
//
//		long time = System.currentTimeMillis();
//		if(time-lastTimeRequestedServerValue>1000)
//		{
//
//			if(ClientMain.clientObject.sendSkillValueRequest(id)==true)
//			{
//				lastTimeRequestedServerValue=time;
//			}
//		}
//
//	}
//
//	//=========================================================================================================================
//	public void sendServerValueUpdate(float f)
//	{//=========================================================================================================================
//
//		//send a request to the server
//
//		long time = System.currentTimeMillis();
//		if(time-lastTimeSentServerValueUpdate>1000)
//		{
//
//			if(ClientMain.clientObject.sendSkillValueUpdate(id, f)==true)
//			{
//				lastTimeSentServerValueUpdate=time;
//			}
//		}
//
//	}
//
//	//=========================================================================================================================
//	public synchronized void setServerValue(float f)
//	{//=========================================================================================================================
//		serverValue = new Float(f);
//	}
//	//=========================================================================================================================
//	public synchronized Float getServerValue()
//	{//=========================================================================================================================
//		return serverValue;
//
//	}
//	//=========================================================================================================================
//	public synchronized void resetServerValue()
//	{//=========================================================================================================================
//		serverValue = null;
//	}
//
//
//
//	//=========================================================================================================================
//	/**
//	 * This gets called repeatedly in events, until it returns a non-null value, at which point the event continues and does not ask again.
//	 * This function will continue asking the server for the value, returning null until the server has set the response value.
//	 * Upon finding a non-null response value set by the networking thread by a server response, we reset it to null and return that value, ensuring that it is always a fresh copy from the server.
//	 */
//	public Float checkServerValueAndResetAfterSuccessfulReturn()
//	{//=========================================================================================================================
//
//		Float tempValue = getServerValue();
//
//		if(tempValue==null)
//		{
//			sendServerSkillValueRequest();
//		}
//		else
//		{
//			resetServerValue();
//		}
//
//		return tempValue;
//	}
//
//	//=========================================================================================================================
//	/**
//	 * This will keep sending a flag value to the server and then checking it to make sure it was set. Returns true after it confirms.
//	 * Event commands should repeatedly call this until it returns true.
//	 */
//	public boolean setServerValueAndReturnTrueWhenConfirmed(float f)
//	{//=========================================================================================================================
//
//
//		sendServerValueUpdate(f);
//
//
//		Float tempValue = checkServerValueAndResetAfterSuccessfulReturn();
//
//		if(tempValue!=null)
//		{
//			if(tempValue.intValue()==f)return true;
//		}
//
//		return false;
//
//
//	}


}
