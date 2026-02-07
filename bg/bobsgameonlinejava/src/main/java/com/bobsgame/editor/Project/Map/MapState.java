package com.bobsgame.editor.Project.Map;

import java.util.ArrayList;

import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Event.Event;
import com.bobsgame.shared.AreaData;
import com.bobsgame.shared.EntityData;
import com.bobsgame.shared.LightData;
import com.bobsgame.shared.MapStateData;



public class MapState implements GameObject
{



	private Map map = null;


	//public int num_Entities = 0;
	private int selectedEntityIndex=-1;
	//private ArrayList<Entity> entityList = new ArrayList<Entity>();

	//public int num_Lights = 0;
	private int selectedLightIndex=-1;
	//private ArrayList<Light> lightList = new ArrayList<Light>();

	//public int num_Areas = 0;
	private int selectedAreaIndex=-1;
	//private ArrayList<Area> areaList = new ArrayList<Area>();




	private MapStateData data;


	//===============================================================================================
	public MapState(Map map, String name)
	{//===============================================================================================

		int id = getBiggestID();


		this.data = new MapStateData(id,name);
		this.setMap(map);


		Project.stateIndexList.add(this);
		Project.stateIndexHashtable.put(getTYPEIDString(),this);

	}



	//===============================================================================================
	public MapState(Map map, MapStateData data)
	{//===============================================================================================


		this.data = data;
		this.setMap(map);

		//if(name().startsWith("DEFAULT"))name("DEFAULT");


		if(Project.stateIndexHashtable.get(getTYPEIDString())!=null)
		{
			System.err.println("MapState ID for MapState: "+name()+" already exists. Creating new ID.");
			int id = getBiggestID();
			setID(id);
		}


		Project.stateIndexList.add(this);
		Project.stateIndexHashtable.put(getTYPEIDString(),this);

	}


	//===============================================================================================
	public int getBiggestID()
	{//===============================================================================================
		int id = -1;
		int size=Project.stateIndexList.size();

		if(size==0)id=0;
		else
		{
			int biggest=0;
			for(int i=0;i<size;i++)
			{
				int testid = Project.stateIndexList.get(i).id();

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
		data.setMapID(map.id());

	}


	public MapStateData getData(){return data;}


	public int id(){return data.id();}
	public String name(){return data.name();}
	public String getTYPEIDString(){return data.getTYPEIDString();}


	public void setID(int s){data.setID(s);}
	public void setName(String s){data.setName(s);}






	//===============================================================================================
	public String toString()
	{//===============================================================================================
		return getTYPEIDString();

	}



	public Area getArea(int i)
	{
		return Project.areaIndexHashtable.get(data.areaDataList().get(i).getTYPEIDString());
	}

	public Light getLight(int i)
	{
		return Project.lightIndexHashtable.get(data.lightDataList().get(i).getTYPEIDString());
	}

	public Entity getEntity(int i)
	{
		return Project.entityIndexHashtable.get(data.entityDataList().get(i).getTYPEIDString());
	}




	public Area getAreaByName(String s)
	{
		for(int i=0;i<data.areaDataList().size();i++)
		{
			if(data.areaDataList().get(i).name().equals(s))return getArea(i);
		}
		return null;
	}

	public Light getLightByName(String s)
	{
		for(int i=0;i<data.lightDataList().size();i++)
		{
			if(data.lightDataList().get(i).name().equals(s))return getLight(i);
		}
		return null;
	}

	public Entity getEntityByName(String s)
	{
		for(int i=0;i<data.entityDataList().size();i++)
		{
			if(data.entityDataList().get(i).name().equals(s))return getEntity(i);
		}
		return null;
	}





	public int getNumAreas()
	{
		return data.areaDataList().size();
	}

	public int getNumLights()
	{
		return data.lightDataList().size();
	}

	public int getNumEntities()
	{
		return data.entityDataList().size();
	}


	public int getSelectedAreaIndex()
	{
		return selectedAreaIndex;
	}

	public int getSelectedLightIndex()
	{
		return selectedLightIndex;
	}

	public int getSelectedEntityIndex()
	{
		return selectedEntityIndex;
	}




	public void setSelectedAreaIndex(int i)
	{
		selectedAreaIndex=i;
	}

	public void setSelectedLightIndex(int i)
	{
		selectedLightIndex=i;
	}

	public void setSelectedEntityIndex(int i)
	{
		selectedEntityIndex=i;
	}





	public Area getSelectedArea()
	{
		return getArea(getSelectedAreaIndex());
	}

	public Light getSelectedLight()
	{
		return getLight(getSelectedLightIndex());
	}

	public Entity getSelectedEntity()
	{
		return getEntity(getSelectedEntityIndex());
	}


	public void addLight(Light l)
	{
		if(l.state()!=this)l.state().removeLight(l);

		l.setMap(map);
		l.setState(this);

		//lightList.add(l);
		if(data.lightDataList().contains(l.getData())==false)data.lightDataList().add(l.getData());
	}

	public void addArea(Area a)
	{

		if(a.state()!=this)a.state().removeArea(a);

		a.setMap(map);
		a.setState(this);

		//areaList.add(a);
		if(data.areaDataList().contains(a.getData())==false)data.areaDataList().add(a.getData());
	}

	public void addEntity(Entity e)
	{

		if(e.state()!=this)e.state().removeEntity(e);

		e.setMap(map);
		e.setState(this);

		//entityList.add(e);

		//if(e.getSprite().isNPC())
		//data.characterDataList.add(e.getData());
		//else
		if(data.entityDataList().contains(e.getData())==false)data.entityDataList().add(e.getData());
	}



	public void removeLight(int index)
	{
		//just to be safe, let's not delete any connections, and leave that up to the user. instead, we'll highlight any connections in the connection list that are broken.

//		//delete it from all map events
//		for(int i=0;i<Project.getNumMaps();i++)
//		{
//			Event event = Project.getEventByID(Project.getMap(i).eventID);
//			if(event!=null)event.deleteLight(getLight(deleteIndex));
//		}
//		//delete it from all  entity, and area events
//
//		for(int i=0;i<getNumAreas();i++)
//		{
//			Event event = Project.getEventByID(getArea(i).eventID);
//			if(event!=null)event.deleteLight(getLight(deleteIndex));
//		}
//		for(int i=0;i<getNumEntities();i++)
//		{
//			Event event = Project.getEventByID(getEntity(i).eventID);
//			if(event!=null)event.deleteLight(getLight(deleteIndex));
//		}

		data.lightDataList().remove(index);
	}

	public void removeArea(int index)
	{
		//just to be safe, let's not delete any connections, and leave that up to the user. instead, we'll highlight any connections in the connection list that are broken.

		//go through sprites, areas, doors, remove connections

//		for(int i=0;i<getNumAreas();i++)
//		{
//			getArea(i).connectionList.remove(getArea(deleteIndex));
//
//		}
//		for(int i=0;i<getNumEntities();i++)
//		{
//			getEntity(i).connectionList.remove(getArea(deleteIndex));
//		}
//
//		for(int i=0;i<Project.getNumMaps();i++)
//		for(int s=0;s<Project.getMap(i).getNumStates();s++)
//		for(int a=0;a<Project.getMap(i).getState(s).getNumAreas();a++)
//		if(Project.getMap(i).getState(s).getArea(a).destination==getArea(deleteIndex))Project.getMap(i).getState(s).getArea(a).destination=Project.getMap(i).getState(s).getArea(a);

//
//		//delete it from all map events
//		for(int i=0;i<Project.getNumMaps();i++)
//		{
//			Event event = Project.getEventByID(Project.getMap(i).eventID);
//			if(event!=null)event.deleteArea(getArea(deleteIndex));
//		}
//		//delete it from all , entity, and area events
//
//		for(int i=0;i<getNumAreas();i++)
//		{
//			Event event = Project.getEventByID(getArea(i).eventID);
//			if(event!=null)event.deleteArea(getArea(deleteIndex));
//		}
//		for(int i=0;i<getNumEntities();i++)
//		{
//			Event event = Project.getEventByID(getEntity(i).eventID);
//			if(event!=null)event.deleteArea(getArea(deleteIndex));
//		}

		data.areaDataList().remove(index);
	}

	public void removeEntity(int index)
	{

//		//delete it from all map events
//		for(int i=0;i<Project.getNumMaps();i++)
//		{
//			Event event = Project.getEventByID(Project.getMap(i).eventID);
//			if(event!=null)event.deleteEntity(getEntity(deleteIndex));
//		}
//
//		//delete it from all  entity, and area events
//
//		for(int i=0;i<getNumAreas();i++)
//		{
//			Event event = Project.getEventByID(getArea(i).eventID);
//			if(event!=null)event.deleteEntity(getEntity(deleteIndex));
//		}
//		for(int i=0;i<getNumEntities();i++)
//		{
//			Event event = Project.getEventByID(getEntity(i).eventID);
//			if(event!=null)event.deleteEntity(getEntity(deleteIndex));
//		}

		data.entityDataList().remove(index);
	}


	public void removeLight(Light l)
	{
		data.lightDataList().remove(l.getData());
	}

	public void removeArea(Area a)
	{
		data.areaDataList().remove(a.getData());
	}

	public void removeEntity(Entity e)
	{
		data.entityDataList().remove(e.getData());
	}

	public MapState duplicate(Map m)
	{


		MapState stateCopy = new MapState(m,""+name()+"Copy"+id());


		for(int i=0;i<getNumEntities();i++)
		{
			Entity e = getEntity(i).duplicate(m,this);
			e.connectionTYPEIDList().clear();
			stateCopy.addEntity(e);

			//TODO: fill the connectionList with the duplicates!

		}

		for(int i=0;i<getNumLights();i++)
		{
			Light l = getLight(i).duplicate(m,this);
			stateCopy.addLight(l);
		}

		for(int i=0;i<getNumAreas();i++)
		{

			Area a = getArea(i).duplicate(m,this);
			a.setDestinationTYPEIDString(a.getTYPEIDString());
			a.connectionTYPEIDList().clear();
			stateCopy.addArea(a);

			//TODO: fill the connectionList with the duplicates!

		}

		return stateCopy;

	}


	@Override
	public String getShortTypeName()
	{
		return "STATE."+name();
	}

	@Override
	public String getLongTypeName()
	{
		return "STATE."+map.name()+"."+name();
	}




	public Map getMap()
	{
		if(map==null)
		{


			//find what map this object is on
			for(int i=0;i<Project.getNumMaps();i++)
			{
				for(int s=0;s<Project.getMap(i).getNumStates();s++)
				{

					if(Project.getMap(i).getState(s)==this)
					{
						map = Project.getMap(i);
					}

				}
			}

		}

		return map;
	}


}
