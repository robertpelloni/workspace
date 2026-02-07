package com.bobsgame.client.engine.map;

import java.util.Hashtable;
import java.util.ArrayList;
import java.util.Vector;
import java.util.concurrent.ConcurrentHashMap;

import com.bobsgame.client.engine.entity.Character;
import com.bobsgame.client.engine.entity.Entity;
import com.bobsgame.shared.MapStateData;



//=========================================================================================================================
public class MapState
{//=========================================================================================================================


	//these hold the Light objects themselves, created in the constructor for this map.
	//these both hold the same thing for convenience.
	public ArrayList<Light> lightList = new ArrayList<Light>();
	public Hashtable<String,Light> lightByNameHashtable = new Hashtable<String,Light>();





	public ArrayList<Entity> entityList = new ArrayList<Entity>();
	public Hashtable<String, Entity> entityByNameHashtable = new Hashtable<String, Entity>();

	public ArrayList<Character> characterList = new ArrayList<Character>();
	public Hashtable<String, Character> characterByNameHashtable = new Hashtable<String, Character>();


	public ArrayList<Area> areaList = new ArrayList<Area>();
	public Hashtable<String, Area> areaByNameHashtable = new Hashtable<String, Area>();
	public Hashtable<String, Area> areaByTYPEIDHashtable = new Hashtable<String, Area>();




	private MapStateData data;



	//=========================================================================================================================
	public MapState(MapStateData mapStateData)
	{//=========================================================================================================================

		this.data = mapStateData;


	}


	public MapStateData getData(){return data;}

	public int id(){return getData().id();}
	public String name(){return getData().name();}

}
