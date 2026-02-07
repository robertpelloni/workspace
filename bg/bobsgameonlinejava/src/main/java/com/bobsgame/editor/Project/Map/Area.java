package com.bobsgame.editor.Project.Map;

import java.util.ArrayList;

import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Event.Event;
import com.bobsgame.shared.AreaData;
import com.bobsgame.shared.EventData;


//===============================================================================================
public class Area implements GameMapObject
{//===============================================================================================


	public static final String DEFAULT_WARP_EVENT_STRING = "{if(isPlayerTouchingThisArea() == TRUE){enterThisWarp}}";
	public static final String DEFAULT_AREA_EVENT_STRING = "{if(isPlayerTouchingThisArea() == TRUE){}}";

	//dont export, these are filled in after load from the objectData strings.
	private Map map = null; //this isn't really used anywhere except in renaming the area below
	private MapState state = null;


	private AreaData data;

	public Event event = null;

	//===============================================================================================
	public Area(Map map, MapState state)
	{//===============================================================================================

		int id = getBiggestID();

		this.data = new AreaData(id,"Area"+id);


		if(isWarpArea())state=map.getDefaultMapStateCreateIfNotExist();

		setMap(map);
		setState(state);

		if(this.state.getData().areaDataList().contains(this.data)==false)this.state.getData().areaDataList().add(this.data);

		Project.areaIndexList.add(this);
		Project.areaIndexHashtable.put(getTYPEIDString(),this);

		if(eventData()!=null)new Event(eventData());


	}

	//===============================================================================================
	public Area(Map map, MapState state, AreaData data)
	{//===============================================================================================

		this.data = data;


		this.setMap(map);
		this.setState(state);


		if(Project.areaIndexHashtable.get(getTYPEIDString())!=null)
		{
			System.err.println("Area ID for Area: "+name()+" already exists. Creating new ID.");
			int id = getBiggestID();
			setID(id);
		}



		Project.areaIndexList.add(this);
		Project.areaIndexHashtable.put(getTYPEIDString(),this);

		if(eventData()!=null)new Event(eventData());

	}





	//===============================================================================================
	public int getBiggestID()
	{//===============================================================================================
		int id = -1;

		int size=Project.areaIndexList.size();
		if(size==0)id=0;
		else
		{
			int biggest=0;
			for(int i=0;i<size;i++)
			{
				int testid = Project.areaIndexList.get(i).id();
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

	public MapState state(){return state;}
	public void setState(MapState state)
	{
		this.state=state;
		//data.setStateID(state.id());
	}



	public AreaData getData(){return data;}

	public String name(){return data.name();}
	public String comment(){return data.comment();}
	public int id(){return data.id();}

	public int wP(){return data.widthPixels1X();}
	public int hP(){return data.heightPixels1X();}
	public int wT(){return data.widthPixels1X()/8;}
	public int hT(){return data.heightPixels1X()/8;}

	public int xP(){return data.mapXPixels1X();}
	public int yP(){return data.mapYPixels1X();}
	public int xT(){return data.mapXPixels1X()/8;}
	public int yT(){return data.mapYPixels1X()/8;}

	public int arrivalXPixels(){return data.arrivalXPixels1X();}
	public int arrivalYPixels(){return data.arrivalYPixels1X();}

	public boolean isWarpArea(){return data.isWarpArea();}
	public boolean randomPointOfInterestOrExit(){return data.randomPointOfInterestOrExit();}
	public boolean randomNPCSpawnPoint(){return data.randomNPCSpawnPoint();}
	public int standSpawnDirection(){return data.standSpawnDirection();}
	public int waitHereTicks(){return data.waitHereTicks();}
	public boolean randomWaitTime(){return data.randomWaitTime();}
	public boolean onlyOneAllowed(){return data.onlyOneAllowed();}
	public boolean randomNPCStayHere(){return data.randomNPCStayHere();}
	public float randomSpawnChance(){return data.randomSpawnChance();}
	public boolean randomSpawnOnlyTryOnce(){return data.randomSpawnOnlyTryOnce();}
	public boolean randomSpawnOnlyOffscreen(){return data.randomSpawnOnlyOffscreen();}
	public int randomSpawnDelay(){return data.randomSpawnDelay();}
	public boolean randomSpawnKids(){return data.randomSpawnKids();}
	public boolean randomSpawnAdults(){return data.randomSpawnAdults();}
	public boolean randomSpawnMales(){return data.randomSpawnMales();}
	public boolean randomSpawnFemales(){return data.randomSpawnFemales();}
	public boolean randomSpawnCars(){return data.randomSpawnCars();}
	public boolean autoPilot(){return data.autoPilot();}
	public boolean playerFaceDirection(){return data.playerFaceDirection();}
	public boolean suckPlayerIntoMiddle(){return data.suckPlayerIntoMiddle();}
	public EventData eventData(){return data.eventData();}
	public ArrayList<String> connectionTYPEIDList(){return data.connectionTYPEIDList();}

	public String getTYPEIDString(){return data.getTYPEIDString();}

	public String destinationTYPEIDString()
	{
		if(data.destinationTYPEIDString()==null||data.destinationTYPEIDString().length()==0)data.setDestinationTYPEIDString(getTYPEIDString());
		return data.destinationTYPEIDString();
	}

	public Area destinationArea()
	{
		if(data.destinationTYPEIDString()==null||data.destinationTYPEIDString().length()==0||data.destinationTYPEIDString().equals(getTYPEIDString()))return this;
		return (Area)Project.getMapObjectByTYPEIDName(data.destinationTYPEIDString());
	}






	//set

	//===============================================================================================
	public void createDefaultWarpAreaEvent()
	{//===============================================================================================
		Event event = new Event(EventData.TYPE_NORMAL_REPEAT_WHILE_MAP_RUNNING,map.name()+"."+name(),"",DEFAULT_WARP_EVENT_STRING);

		this.setEventData(event.getData());
	}




	public void setXPixels(int s){data.setMapXPixels1X(s);}
	public void setYPixels(int s){data.setMapYPixels1X(s);}

	public void setArrivalXPixels(int s){data.setArrivalXPixels1X(s);}
	public void setArrivalYPixels(int s){data.setArrivalYPixels1X(s);}

	public void setWidthPixels(int s){data.setWidthPixels1X(s);}
	public void setHeightPixels(int s){data.setHeightPixels1X(s);}

	public void setID(int s){data.setID(s);}
	public void setDestinationTYPEIDString(String s){data.setDestinationTYPEIDString(s);}
	public void setRandomPointOfInterestOrExit(boolean s){data.setRandomPointOfInterestOrExit(s);}
	public void setRandomNPCSpawnPoint(boolean s){data.setRandomNPCSpawnPoint(s);}
	public void setStandSpawnDirection(int s){data.setStandSpawnDirection(s);}
	public void setWaitHereTicks(int s){data.setWaitHereTicks(s);}
	public void setRandomWaitTime(boolean s){data.setRandomWaitTime(s);}
	public void setOnlyOneAllowed(boolean s){data.setOnlyOneAllowed(s);}
	public void setRandomNPCStayHere(boolean s){data.setRandomNPCStayHere(s);}
	public void setRandomSpawnChance(float s){data.setRandomSpawnChance(s);}
	public void setRandomSpawnOnlyTryOnce(boolean s){data.setRandomSpawnOnlyTryOnce(s);}
	public void setRandomSpawnOnlyOffscreen(boolean s){data.setRandomSpawnOnlyOffscreen(s);}
	public void setRandomSpawnDelay(int s){data.setRandomSpawnDelay(s);}
	public void setRandomSpawnKids(boolean s){data.setRandomSpawnKids(s);}
	public void setRandomSpawnAdults(boolean s){data.setRandomSpawnAdults(s);}
	public void setRandomSpawnMales(boolean s){data.setRandomSpawnMales(s);}
	public void setRandomSpawnFemales(boolean s){data.setRandomSpawnFemales(s);}
	public void setRandomSpawnCars(boolean s){data.setRandomSpawnCars(s);}
	public void setAutoPilot(boolean s){data.setAutoPilot(s);}
	public void setPlayerFaceDirection(boolean s){data.setPlayerFaceDirection(s);}
	public void setSuckPlayerIntoMiddle(boolean s){data.setSuckPlayerIntoMiddle(s);}
	public void setEventData(EventData s){data.setEventData(s);}
	public void setComment(String s){data.setComment(s);}



	public void setIsWarpArea(boolean s)
	{
		data.setIsWarpArea(s);

		if(s==true)
		{
			MapState state = map.getDefaultMapStateCreateIfNotExist();
			if(state()!=state)
			{
				state().removeArea(this);
				state.addArea(this);
			}

			if(eventData()==null)createDefaultWarpAreaEvent();
		}

	}





	//===============================================================================================
	public String toString()
	{//===============================================================================================
		return getTYPEIDString();

	}

	//===============================================================================================
	public String getTreeString()
	{//===============================================================================================
		return getShortTypeName();
	}





	//===============================================================================================
	public Area duplicate(Map mapToCopyTo, MapState stateToCopyTo)
	{//===============================================================================================

		Area areaCopy = new Area(mapToCopyTo,stateToCopyTo);
		areaCopy.data.setName(new String(""+this.name()));

		areaCopy.setXPixels(this.xP());
		areaCopy.setYPixels(this.yP());
		areaCopy.setWidthPixels(this.wP());
		areaCopy.setHeightPixels(this.hP());
		areaCopy.setArrivalXPixels(this.arrivalXPixels());
		areaCopy.setArrivalYPixels(this.arrivalYPixels());

		areaCopy.setComment(new String (""+this.comment()));
		areaCopy.setRandomPointOfInterestOrExit(this.randomPointOfInterestOrExit());
		areaCopy.setRandomNPCSpawnPoint(this.randomNPCSpawnPoint());
		areaCopy.setStandSpawnDirection(this.standSpawnDirection());
		areaCopy.setWaitHereTicks(this.waitHereTicks());
		areaCopy.setRandomWaitTime(this.randomWaitTime());
		areaCopy.setOnlyOneAllowed(this.onlyOneAllowed());
		areaCopy.setRandomNPCStayHere(this.randomNPCStayHere());
		areaCopy.setRandomSpawnChance(this.randomSpawnChance());
		areaCopy.setRandomSpawnOnlyTryOnce(this.randomSpawnOnlyTryOnce());

		areaCopy.setRandomSpawnOnlyOffscreen(this.randomSpawnOnlyOffscreen());
		areaCopy.setRandomSpawnDelay(this.randomSpawnDelay());
		areaCopy.setRandomSpawnKids(this.randomSpawnKids());
		areaCopy.setRandomSpawnAdults(this.randomSpawnAdults());
		areaCopy.setRandomSpawnMales(this.randomSpawnMales());
		areaCopy.setRandomSpawnFemales(this.randomSpawnFemales());
		areaCopy.setRandomSpawnCars(this.randomSpawnCars());

		areaCopy.setAutoPilot(this.autoPilot());
		areaCopy.setPlayerFaceDirection(this.playerFaceDirection());
		areaCopy.setSuckPlayerIntoMiddle(this.suckPlayerIntoMiddle());

		areaCopy.data.setIsWarpArea(this.isWarpArea());
		areaCopy.setDestinationTYPEIDString(this.destinationTYPEIDString());

		if(this.eventData()==null)areaCopy.setEventData(null);
		else areaCopy.setEventData(Project.getEventByID(this.eventData().id()).duplicate().getData());


		for(int i=0;i<this.connectionTYPEIDList().size();i++)areaCopy.connectionTYPEIDList().add(this.connectionTYPEIDList().get(i));


		return areaCopy;


	}


	//===============================================================================================
	public String getShortTypeName()
	{//===============================================================================================

		return "AREA."+name();
	}
	//===============================================================================================
	public String getLongTypeName()
	{//===============================================================================================



		if(map==null||state==null)
		{
			//find what map this area is on
			for(int i=0;i<Project.getNumMaps();i++)
			{
				for(int s=0;s<Project.getMap(i).getNumStates();s++)
				{
					for(int k=0;k<Project.getMap(i).getState(s).getNumAreas();k++)
					{
						if(Project.getMap(i).getState(s).getArea(k)==this)
						{
							if(map!=null&&map!=Project.getMap(i))System.err.println("SERIOUS ERROR: Area "+name()+" is on multiple maps!");
							if(state!=null&&state!=Project.getMap(i).getState(s))System.err.println("SERIOUS ERROR: Area "+name()+" is on multiple states!");

							map = Project.getMap(i);
							state = Project.getMap(i).getState(s);

						}
					}
				}
			}
		}


		return "AREA."+map.name()+"."+state.name()+"."+name();

	}



//	//===============================================================================================
//	public Map getMap()
//	{//===============================================================================================
//
//		if(map==null)
//		{
//			//find what map this area is on
//			for(int i=0;i<Project.getNumMaps();i++)
//			{
//				for(int s=0;s<Project.getMap(i).getNumStates();s++)
//				{
//					for(int k=0;k<Project.getMap(i).getState(s).getNumAreas();k++)
//					{
//						if(Project.getMap(i).getState(s).getArea(k)==this)
//						{
//							if(map!=null&&map!=Project.getMap(i))System.err.println("SERIOUS ERROR: Area "+name()+" is on multiple maps!");
//							if(state!=null&&state!=Project.getMap(i).getState(s))System.err.println("SERIOUS ERROR: Area "+name()+" is on multiple states!");
//
//							map = Project.getMap(i);
//							state = Project.getMap(i).getState(s);
//
//						}
//					}
//				}
//			}
//		}
//		return map;
//	}



	//===============================================================================================
	public void setNameNoRename(String newName)
	{//===============================================================================================
		this.data.setName(newName);

	}
	//===============================================================================================
	public void setName(String newName)
	{//===============================================================================================
		String oldName = this.name();

		this.data.setName(newName);



		if(map==null||state==null)
		{


			//find what map this entity is on
			for(int i=0;i<Project.getNumMaps();i++)
			{
				for(int s=0;s<Project.getMap(i).getNumStates();s++)
				{
					for(int k=0;k<Project.getMap(i).getState(s).getNumAreas();k++)
					{
						if(Project.getMap(i).getState(s).getArea(k)==this)
						{
							map = Project.getMap(i);
							state = Project.getMap(i).getState(s);
						}
					}
				}
			}

			if(map==null)System.err.println("Couldn't find area in maps in setName()");
			if(state==null)System.err.println("Couldn't find area in state in setName()");
		}


		if(map!=null)
		{
			//rename any areas with the same name in any states in THIS MAP
			//have to do all states, keeping area names synchronized between states
			for(int k=0;k<map.getNumStates();k++)
			{
				for(int n=0;n<map.getState(k).getNumAreas();n++)
				{
					Area a = map.getState(k).getArea(n);
					if(a.name().equals(oldName))a.setNameNoRename(newName);
				}
			}
		}


		//don't have to do this anymore, everything is tracked by id

		//then rename this area in all events
//		for(int i = 0; i < Project.eventList.size(); i++)
//		{
//			Project.eventList.get(i).renameAreaString(map.name,oldName,newName);
//		}



	}






}
