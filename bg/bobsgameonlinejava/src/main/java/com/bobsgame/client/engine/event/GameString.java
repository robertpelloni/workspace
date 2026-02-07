package com.bobsgame.client.engine.event;

import com.bobsgame.client.engine.Engine;
import com.bobsgame.shared.GameStringData;


//=========================================================================================================================
public class GameString extends ServerObject
{//=========================================================================================================================

	private GameStringData data;

	//=========================================================================================================================
	public GameString(Engine g, int id)
	{//=========================================================================================================================
		super(g);

		this.data = new GameStringData(id,"","");

		for(int i=0;i<EventManager().gameStringList.size();i++){if(EventManager().gameStringList.get(i).id()==data.id()){log.error("GameString already exists:"+data.name());return;}}
		EventManager().gameStringList.add(this);
	}


	//=========================================================================================================================
	public GameString(Engine g, GameStringData data)
	{//=========================================================================================================================
		super(g);

		this.data = data;
		setInitialized_S(true);

		for(int i=0;i<EventManager().gameStringList.size();i++){if(EventManager().gameStringList.get(i).id()==data.id()){log.error("GameString already exists:"+data.name());return;}}
		EventManager().gameStringList.add(this);
	}

	//=========================================================================================================================
	public synchronized void setData_S(GameStringData data)
	{//=========================================================================================================================
		this.data = data;
		setInitialized_S(true);
	}


	public GameStringData getData(){return data;}

	public int id(){return getData().id();}
	public String name(){return getData().name();}
	public String text(){return getData().text();}

	public String getTYPEIDString(){return getData().getTYPEIDString();}

	public void id(int id){getData().setID(id);}
	public void setName(String name){getData().setName(name);}
	public void text(String text){getData().setText(text);}

}
