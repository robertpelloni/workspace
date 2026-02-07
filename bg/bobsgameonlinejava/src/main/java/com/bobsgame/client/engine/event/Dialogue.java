package com.bobsgame.client.engine.event;

import com.bobsgame.client.engine.Engine;
import com.bobsgame.shared.DialogueData;

//=========================================================================================================================
public class Dialogue extends ServerObject
{//=========================================================================================================================


	private boolean doneValue_S = false;
	private long timeSet = -1;

	private DialogueData data;

	//=========================================================================================================================
	public Dialogue(Engine g, int id)
	{//=========================================================================================================================
		super(g);

		this.data = new DialogueData(id,"","","","");

		for(int i=0;i<EventManager().dialogueList.size();i++){if(EventManager().dialogueList.get(i).id()==data.id()){log.error("Dialogue already exists:"+data.name());return;}}
		EventManager().dialogueList.add(this);
	}

	//=========================================================================================================================
	public Dialogue(Engine g, DialogueData data)
	{//=========================================================================================================================
		super(g);

		this.data = data;
		setInitialized_S(true);

		for(int i=0;i<EventManager().dialogueList.size();i++){if(EventManager().dialogueList.get(i).id()==data.id()){log.error("Dialogue already exists:"+data.name());return;}}
		EventManager().dialogueList.add(this);
	}


	//=========================================================================================================================
	public synchronized void setData_S(DialogueData data)
	{//=========================================================================================================================

		this.data = data;
		setInitialized_S(true);
	}


	public DialogueData getData(){return data;}

	public int id(){return getData().id();}
	public String name(){return getData().name();}
	public String caption(){return getData().caption();}
	public String comment(){return getData().comment();}
	public String text(){return getData().text();}

	public String getTYPEIDString(){return getData().getTYPEIDString();}

	public void setID(int id){getData().setID(id);}
	public void setName(String name){getData().setName(name);}
	public void setCaption(String caption){getData().setCaption(caption);}
	public void setComment(String comment){getData().setComment(comment);}
	public void setText(String text){getData().setText(text);}






	//=========================================================================================================================
	public synchronized void setDialogueDoneValue_S(boolean b)//sendServerDialogueDoneValueUpdate(boolean b)
	{//=========================================================================================================================

		//send a request to the server

		//ClientMain.clientObject.sendDialogueDoneValueUpdate(id, b);

		timeSet = System.currentTimeMillis();

		if(b==true)Network().addQueuedGameSaveUpdateRequest_S("dialoguesDone:`"+id()+":true:"+timeSet+"`");
		if(b==false)Network().addQueuedGameSaveUpdateRequest_S("dialoguesDone:`"+id()+":false:"+timeSet+"`");


		doneValue_S = b;
	}

	//=========================================================================================================================
	public synchronized void initDialogueDoneValueFromGameSave_S(boolean b,long timeSet)
	{//=========================================================================================================================

		doneValue_S = b;
		this.timeSet = timeSet;
	}

	//=========================================================================================================================
	public synchronized boolean getDialogueDoneValue_S()
	{//=========================================================================================================================
		return doneValue_S;
	}


	//=========================================================================================================================
	public long getTimeSet()
	{//=========================================================================================================================
		return timeSet;
	}



}
