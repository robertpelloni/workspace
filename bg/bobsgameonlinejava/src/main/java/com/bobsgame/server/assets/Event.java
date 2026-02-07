package com.bobsgame.server.assets;



import java.util.ArrayList;

import javax.swing.tree.DefaultMutableTreeNode;


import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;




//=========================================================================================================================
public class Event
{//=========================================================================================================================


	public int id = -1;
	public int type = 0;
	public String name = ""; //for MAP events that don't run right away and are called by other events inside the map or map objects.
	public String comment = "";

	public String text = "";



	public static int TYPE_MAP_RUN_ONCE_BEFORE_LOAD = -1;//maps will use this for setting the map State, it is run exactly once upon map load, before any objects are created.
	public static int TYPE_NORMAL_REPEAT_WHILE_MAP_RUNNING = 0;//all object will use this
	public static int TYPE_MAP_DONT_RUN_UNTIL_CALLED = 1;//maps can set this type, which is populated in the EventEditor Events tab. it is an event that any of the objects on this map can call.
	public static int TYPE_MAP_RUN_ONCE_AFTER_LOAD = 2;//maps can set this type, it is used for cutscenes




	//=========================================================================================================================
	public Event(int id)
	{//=========================================================================================================================

		this.id=id;

		//g.eventList.add(this);//this tracks events created for areas and entities that don't exist after the map is unloaded, so they don't have to be loaded from the server and parsed again.

	}




	public Event(int id,int type,String name,String comment,String text)
	{

		this.id = id;
		this.type = type;
		this.name = name;
		this.comment = comment;
		this.text = text;

	}











}
