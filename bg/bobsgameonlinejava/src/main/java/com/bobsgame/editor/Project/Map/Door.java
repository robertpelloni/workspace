package com.bobsgame.editor.Project.Map;

import java.awt.image.BufferedImage;
import java.util.ArrayList;

import javax.swing.Timer;

import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Event.Event;
import com.bobsgame.editor.Project.Sprite.Sprite;
import com.bobsgame.shared.AreaData;
import com.bobsgame.shared.DoorData;
import com.bobsgame.shared.EventData;

//===============================================================================================
public class Door implements GameMapObject
{//===============================================================================================



	public static final String DEFAULT_DOOR_EVENT_STRING = "{if(isPlayerWalkingIntoThisDoor() == TRUE){enterThisDoor}}";

	//private String spriteName = "";
	private BufferedImage bufferedImage = null;


	//stuff filled in from sprite on load
	private Sprite sprite = null;


	//TODO: go through all known objects and make a unique id.
	//dialogues, sprites, maps, and events should all extend this.


	//dont export
	private Map map = null; //this isn't really used anywhere except in renaming the door below


	private DoorData data;

	//===============================================================================================
	public Door(Map map)
	{//===============================================================================================

		int id = getBiggestID();

		this.data = new DoorData(id,"Door"+id);

		this.setMap(map);

		if(map.getData().doorDataList().contains(data)==false)map.getData().doorDataList().add(data);

		createDefaultEvent();

		Project.doorIndexList.add(this); //these are only used for ID lookup, doors have to be added to a map.doorList as well.
		Project.doorIndexHashtable.put(getTYPEIDString(),this);

		if(eventData()!=null)new Event(eventData());
	}

	//===============================================================================================
	public Door(Map map, DoorData data)
	{//===============================================================================================

		this.data = data;
		this.setMap(map);


		if(Project.doorIndexHashtable.get(getTYPEIDString())!=null)
		{
			System.err.println("Door ID for Door: "+name()+" already exists. Creating new ID.");
			int id = getBiggestID();
			setID(id);
		}

		Project.doorIndexList.add(this);
		Project.doorIndexHashtable.put(getTYPEIDString(),this);

		if(eventData()!=null)new Event(eventData());

	}



	//===============================================================================================
	public int getBiggestID()
	{//===============================================================================================
		int id = -1;

		int size=Project.doorIndexList.size();
		if(size==0)id=0;
		else
		{
			int biggest=0;
			for(int i=0;i<size;i++)
			{
				int testid = Project.doorIndexList.get(i).id();
				if(testid>biggest)biggest=testid;
			}
			id=biggest+1;
		}
		return id;

	}




	public Map map(){return map;}
	public void setMap(Map map)
	{
		this.map=map;
		//data.setMapID(map.id());
	}


	public DoorData getData(){return data;}

	public String name(){return data.name();}
	public String spriteName(){return data.spriteName();}
	public String comment(){return data.comment();}
	public int id(){return data.id();}


	public int xP(){return (int)data.spawnXPixels1X();}
	public int yP(){return (int)data.spawnYPixels1X();}
	public int xT(){return (int)data.spawnXPixels1X()/8;}
	public int yT(){return (int)data.spawnYPixels1X()/8;}

	public int wP(){return (int)(sprite.wP());}
	public int hP(){return (int)(sprite.hP());}
	public int wT(){return (int)(sprite.wP())/8;}
	public int hT(){return (int)(sprite.hP())/8;}

	public int arrivalXPixels(){return data.arrivalXPixels1X();}
	public int arrivalYPixels(){return data.arrivalYPixels1X();}

	public String destinationTYPEIDString()
	{
		if(data.destinationTYPEIDString()==null||data.destinationTYPEIDString().length()==0)data.setDestinationTYPEIDString(getTYPEIDString());
		return data.destinationTYPEIDString();
	}

	public Door destinationDoor()
	{
		if(data.destinationTYPEIDString()==null||data.destinationTYPEIDString().length()==0||data.destinationTYPEIDString().equals(getTYPEIDString()))return this;
		return (Door)Project.getMapObjectByTYPEIDName(data.destinationTYPEIDString());
	}

	public boolean randomPointOfInterestOrExit(){return data.randomPointOfInterestOrExit();}
	public boolean randomNPCSpawnPoint(){return data.randomNPCSpawnPoint();}
	public float randomSpawnChance(){return data.randomSpawnChance();}
	public int randomSpawnDelay(){return data.randomSpawnDelay();}
	public boolean randomSpawnKids(){return data.randomSpawnKids();}
	public boolean randomSpawnAdults(){return data.randomSpawnAdults();}
	public boolean randomSpawnMales(){return data.randomSpawnMales();}
	public boolean randomSpawnFemales(){return data.randomSpawnFemales();}
	public EventData eventData(){return data.eventData();}
	public ArrayList<String> connectionTYPEIDList(){return data.connectionTYPEIDList();}
	public String getTYPEIDString(){return data.getTYPEIDString();}




	public void setID(int s){data.setID(s);}
	public void setDestinationTYPEIDString(String typeID){data.setDestinationTYPEIDString(typeID);}


	public void setRandomPointOfInterestOrExit(boolean s){data.setRandomPointOfInterestOrExit(s);}
	public void setRandomNPCSpawnPoint(boolean s){data.setRandomNPCSpawnPoint(s);}
	public void setRandomSpawnChance(float s){data.setRandomSpawnChance(s);}
	public void setRandomSpawnDelay(int s){data.setRandomSpawnDelay(s);}
	public void setRandomSpawnKids(boolean s){data.setRandomSpawnKids(s);}
	public void setRandomSpawnAdults(boolean s){data.setRandomSpawnAdults(s);}
	public void setRandomSpawnMales(boolean s){data.setRandomSpawnMales(s);}
	public void setRandomSpawnFemales(boolean s){data.setRandomSpawnFemales(s);}
	public void setEventData(EventData s){data.setEventData(s);}
	public void setComment(String s){data.setComment(s);}

	public void setXPixels(float s){data.setSpawnXPixels1X(s);}
	public void setYPixels(float s){data.setSpawnYPixels1X(s);}
	public void setArrivalXPixels(int s){data.setArrivalXPixels1X(s);}
	public void setArrivalYPixels(int s){data.setArrivalYPixels1X(s);}












	//===============================================================================================
	public void createDefaultEvent()
	{//===============================================================================================
		Event event = new Event(EventData.TYPE_NORMAL_REPEAT_WHILE_MAP_RUNNING,map.name()+"."+name(),"",DEFAULT_DOOR_EVENT_STRING);
		setEventData(event.getData());
	}


	//===============================================================================================
	public void setName(String newName)
	{//===============================================================================================
		//String oldName = name();

		data.setName(newName);



//		//find what map this entity is on
//		for(int i=0;i<Project.getNumMaps();i++)
//		{
//			for(int k=0;k<Project.getMap(i).getNumDoors();k++)
//			{
//				if(Project.getMap(i).getDoor(k)==this)
//				{
//					map = Project.getMap(i);
//
//				}
//			}
//		}
//
//		if(map==null)System.err.println("Couldn't find door in maps in setName()");



		//don't have to do this anymore, everything is tracked by id

		//then rename this door in all events
//		for(int i = 0; i < Project.eventList.size(); i++)
//		{
//			Project.eventList.get(i).renameDoorString(map.name,oldName,newName);
//		}


	}



	//===============================================================================================
	public String toString()
	{//===============================================================================================
		return getTYPEIDString();

	}

	//===============================================================================================
	public Door duplicate(Map mapToCopyTo)
	{//===============================================================================================

		Door doorCopy = new Door(mapToCopyTo);

		doorCopy.setName(new String(""+this.name()));
		//m.spriteName = new String(""+spriteName);
		doorCopy.bufferedImage = null;
		doorCopy.setXPixels(this.xP());
		doorCopy.setYPixels(this.yP());

		doorCopy.setDestinationTYPEIDString(this.destinationTYPEIDString());
		doorCopy.setArrivalXPixels(this.arrivalXPixels());
		doorCopy.setArrivalYPixels(this.arrivalYPixels());

		doorCopy.sprite = sprite;
		doorCopy.setComment(new String(""+this.comment()));


		doorCopy.setRandomNPCSpawnPoint(this.randomNPCSpawnPoint());
		doorCopy.setRandomSpawnChance(this.randomSpawnChance());
		doorCopy.setRandomPointOfInterestOrExit(this.randomPointOfInterestOrExit());
		doorCopy.setRandomSpawnDelay(this.randomSpawnDelay());
		doorCopy.setRandomSpawnKids(this.randomSpawnKids());
		doorCopy.setRandomSpawnAdults(this.randomSpawnAdults());
		doorCopy.setRandomSpawnMales(this.randomSpawnMales());
		doorCopy.setRandomSpawnFemales(this.randomSpawnFemales());



		for(int i=0;i<this.connectionTYPEIDList().size();i++)doorCopy.connectionTYPEIDList().add(this.connectionTYPEIDList().get(i));


		if(this.eventData()==null)doorCopy.setEventData(null);
		else doorCopy.setEventData(Project.getEventByID(this.eventData().id()).duplicate().getData());


		return doorCopy;

	}
	//===============================================================================================
	public Sprite getSprite()
	{//===============================================================================================
		return sprite;

	}
	//===============================================================================================
	public void setSprite(Sprite s)
	{//===============================================================================================
		sprite = s;

		data.setSpriteName(s.name());

		bufferedImage = null;
	}

//
//	//===============================================================================================
//	public Map getMap()
//	{//===============================================================================================
//
//		if(map==null)
//		{
//
//
//			//find what map this entity is on
//			for(int i=0;i<Project.getNumMaps();i++)
//			{
//
//				for(int k=0;k<Project.getMap(i).getNumDoors();k++)
//				{
//					if(Project.getMap(i).getDoor(k)==this)
//					{
//						if(map!=null)System.err.println("SERIOUS ERROR: Door "+name()+" is on multiple maps!");
//
//
//						map = Project.getMap(i);
//
//
//					}
//				}
//
//			}
//		}
//		return map;
//	}


	//===============================================================================================
	public String getShortTypeName()
	{//===============================================================================================

//		Map map = null;
//		State state = null;
//
//		//find what map this entity is on
//		for(int i=0;i<Project.getNumMaps();i++)
//		{
//			for(int s=0;s<Project.getMap(i).getNumStates();s++)
//			{
//				for(int k=0;k<Project.getMap(i).getState(s).getNumDoors();k++)
//				{
//					if(Project.getMap(i).getState(s).getDoor(k)==this)
//					{
//						if(map!=null)System.err.println("SERIOUS ERROR: Door "+doorName+" is on multiple maps!");
//						if(state!=null)System.err.println("SERIOUS ERROR: Door "+doorName+" is on multiple states!");
//
//						map = Project.getMap(i);
//						state = Project.getMap(i).getState(s);
//
//					}
//				}
//			}
//		}


		//return "DOOR."+map.name+"."+state.name+"."+doorName;
		return "DOOR."+name();
	}


	//===============================================================================================
	public String getLongTypeName()
	{//===============================================================================================

		Map map = null;
		MapState state = null;

		//find what map this entity is on
		for(int i=0;i<Project.getNumMaps();i++)
		{
			//for(int s=0;s<Project.getMap(i).getNumStates();s++)
			{
				for(int k=0;k<Project.getMap(i).getNumDoors();k++)
				{
					if(Project.getMap(i).getDoor(k)==this)
					{
						if(map!=null)System.err.println("SERIOUS ERROR: Door "+name()+" is on multiple maps!");
						if(state!=null)System.err.println("SERIOUS ERROR: Door "+name()+" is on multiple states!");

						map = Project.getMap(i);
						//state = Project.getMap(i).getState(s);

					}
				}
			}
		}


		return "DOOR."+map.name()+"."+name();

	}
	//===============================================================================================
	public BufferedImage getImage()
	{//===============================================================================================

		if(bufferedImage==null)bufferedImage = sprite.getFrameImage(0);

		return bufferedImage;
	}











}
