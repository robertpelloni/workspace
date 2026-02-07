package com.bobsgame.editor.Project.Map;

import java.awt.image.BufferedImage;
import java.util.ArrayList;

import javax.swing.Timer;

import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Event.Event;
import com.bobsgame.editor.Project.Sprite.Sprite;
import com.bobsgame.shared.DoorData;
import com.bobsgame.shared.EntityData;
import com.bobsgame.shared.EventData;
import com.bobsgame.shared.MapData.RenderOrder;
//===============================================================================================
public class Entity implements GameMapObject
{//===============================================================================================



	//stuff filled in from sprite on load
	private Sprite sprite = null;
	private BufferedImage bufferedImage = null;


	public Timer frameTimer;
	public Timer startAnimationTimer;
	public int currentAnimationFrame=0;



	//dont export
	private Map map = null; //this isn't really used anywhere except in renaming the entity below, it needs to know what map it is on so it knows what other areas/entities/etc to compare to.
	private MapState state = null;



	private EntityData data;




	//===============================================================================================
	public Entity(Map map, MapState state)
	{//===============================================================================================



		int id = getBiggestID();

		this.data = new EntityData(id,"Entity"+id);
		this.setMap(map);
		this.setState(state);


		if(this.state.getData().entityDataList().contains(this.data)==false)this.state.getData().entityDataList().add(this.data);



		Project.entityIndexList.add(this);
		Project.entityIndexHashtable.put(getTYPEIDString(),this);

		if(eventData()!=null)new Event(eventData());
	}

	//===============================================================================================
	public Entity(Map map, MapState state, EntityData data)
	{//===============================================================================================

		this.data = data;
		this.setMap(map);
		this.setState(state);


		if(data.layerrr()==1)data.setRenderOrder(RenderOrder.GROUND);//TODO: hack to replace layer with RenderOrder, saved assets are still using layer.
		if(data.layerrr()==2)data.setRenderOrder(RenderOrder.ABOVE);
		if(data.aboveTopLayer())data.setRenderOrder(RenderOrder.ABOVE_TOP);

		if(data.walkSpeed==0)data.setTicksPerPixelMoved(12);
		if(data.walkSpeed==1)data.setTicksPerPixelMoved(8);
		if(data.walkSpeed==2)data.setTicksPerPixelMoved(4);

//				//this.walkSpeed = walkSpeed;
//				// make speed stuff better
//				ticksPerPixelMoved=10;
//				if(walkSpeed==0) ticksPerPixelMoved=12;
//				if(walkSpeed==1) ticksPerPixelMoved=8;
//				if(walkSpeed==2) ticksPerPixelMoved=4;
			//
//				//TODO: this should be pixelsPerSecond:
//				//10 ticksPerPixelsMoved = 100 pps
//				//12 = 85 pps
//				//4 = 250 pps
//				//in editor i should show the movement speed and give pps calculation, base everything on ticksPerPixel

		if(Project.entityIndexHashtable.get(getTYPEIDString())!=null)
		{
			System.err.println("Entity ID for Entity: "+name()+" already exists. Creating new ID.");
			int id = getBiggestID();
			setID(id);
		}

		Project.entityIndexList.add(this);
		Project.entityIndexHashtable.put(getTYPEIDString(),this);

		if(eventData()!=null)new Event(eventData());

	}


	//===============================================================================================
	public int getBiggestID()
	{//===============================================================================================
		int id = -1;

		int size=Project.entityIndexList.size();
		if(size==0)id=0;
		else
		{
			int biggest=0;
			for(int i=0;i<size;i++)
			{
				int testid = Project.entityIndexList.get(i).id();
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







	public EntityData getData(){return data;}



	public String name(){return data.name();}
	public String comment(){return data.comment();}
	public int id(){return data.id();}
	//public int mapID(){return data.mapID();}
	public String spriteName(){return data.spriteName();}


	public int xP(){return (int)data.spawnXPixels1X();}
	public int yP(){return (int)data.spawnYPixels1X();}
	public int xT(){return (int)data.spawnXPixels1X()/8;}
	public int yT(){return (int)data.spawnYPixels1X()/8;}

	public int wP(){return (int)(sprite.wP()*scale());}
	public int hP(){return (int)(sprite.hP()*scale());}
	public int wT(){return (int)(sprite.wP()*scale())/8;}
	public int hT(){return (int)(sprite.hP()*scale())/8;}

	public boolean pushable(){return data.pushable();}
	public boolean nonWalkable(){return data.nonWalkable();}
	public float toAlpha(){return data.toAlpha();}
	public float scale(){return data.scale();}
	public boolean disableShadow(){return data.disableShadow();}
	public boolean aboveWhenEqual(){return data.aboveWhenEqual();}
	public boolean alwaysOnTop(){return data.alwaysOnTop();}
	public boolean alwaysOnBottom(){return data.alwaysOnBottom();}
	public RenderOrder renderOrder(){return data.renderOrder();}
	//public boolean aboveTopLayer(){return data.aboveTopLayer();}
	public int initialFrame(){return data.initialFrame();}
	public boolean animatingThroughAllFrames(){return data.animatingThroughAllFrames();}
	public boolean randomFrames(){return data.randomFrames();}
	public boolean randomUpToTicksBetweenFrames(){return data.randomUpToTicksBetweenFrames();}
	public boolean randomUpToTicksBetweenAnimationLoop(){return data.randomUpToTicksBetweenAnimationLoop();}
	public int ticksBetweenFrames(){return data.ticksBetweenFrames();}
	public int ticksBetweenAnimationLoop(){return data.ticksBetweenAnimationLoop();}


	public float ticksPerPixelMoved(){return data.ticksPerPixelMoved();}

	public EventData eventData(){return data.eventData();}
	public boolean onlyHereDuringEvent(){return data.onlyHereDuringEvent();}
	public float voicePitch(){return data.voicePitch();}
	public boolean movementAnimationDisabled(){return data.movementAnimationDisabled();}
	public boolean hitLayerDisabled(){return data.hitLayerDisabled();}
	public boolean ignoreHitPlayer(){return data.ignoreHitPlayer();}
	public boolean pullPlayer(){return data.pullPlayer();}
	public boolean pushPlayer(){return data.pushPlayer();}

	public ArrayList<String> connectionTYPEIDList(){return data.connectionTYPEIDList();}
	public ArrayList<String> behaviorList(){return data.behaviorList();}

	public String getTYPEIDString(){return data.getTYPEIDString();}





	//set
	public void setID(int s){data.setID(s);}
	public void setComment(String s){data.setComment(s);}

	public void setXPixels(float s){data.setSpawnXPixels1X(s);}
	public void setYPixels(float s){data.setSpawnYPixels1X(s);}
	public void setPushable(boolean s){data.setPushable(s);}
	public void setNonWalkable(boolean s){data.setNonWalkable(s);}
	public void setToAlpha(float alpha){data.setToAlpha(alpha);bufferedImage = null;}
	public void setScale(float s){data.setScale(s);}
	public void setDisableShadow(boolean s){data.setDisableShadow(s);}
	public void setInitialFrame(int f){data.setInitialFrame(f);bufferedImage = null;}
	public void setAnimateThroughAllFrames(boolean s){data.setAnimateThroughAllFrames(s);}
	public void setRandomFrames(boolean s){data.setRandomFrames(s);}
	public void setRandomUpToTicksBetweenFrames(boolean s){data.setRandomUpToTicksBetweenFrames(s);}
	public void setRandomUpToTicksBetweenAnimationLoop(boolean s){data.setRandomUpToTicksBetweenAnimationLoop(s);}
	public void setTicksBetweenFrames(int s){data.setTicksBetweenFrames(s);}
	public void setTicksBetweenAnimationLoop(int s){data.setTicksBetweenAnimationLoop(s);}

	public void setTicksPerPixelMoved(float s){data.setTicksPerPixelMoved(s);}
	public void setRenderOrder(RenderOrder s){data.setRenderOrder(s);}
	//public void setAboveTopLayer(boolean s){data.setAboveTopLayer(s);}
	public void setAboveWhenEqual(boolean s){data.setAboveWhenEqual(s);}
	public void setAlwaysOnBottom(boolean s){data.setAlwaysOnBottom(s);}
	public void setAlwaysOnTop(boolean s){data.setAlwaysOnTop(s);}
	public void setOnlyHereDuringEvent(boolean s){data.setOnlyHereDuringEvent(s);}
	public void setVoicePitch(float s){data.setVoicePitch(s);}
	public void setAnimationDisabled(boolean s){data.setAnimationDisabled(s);}
	public void setHitLayerDisabled(boolean s){data.setHitLayerDisabled(s);}
	public void setIgnoreHitPlayer(boolean s){data.setIgnoreHitPlayer(s);}
	public void setEventData(EventData s){data.setEventData(s);}


	//===============================================================================================
	public String toString()
	{//===============================================================================================
		return getTYPEIDString();

	}


	//===============================================================================================
	public void setSprite(Sprite s)
	{//===============================================================================================
		sprite = s;

		if(sprite.isNPC()==true)data.setIsNPC(true);

		data.setSpriteName(s.name());

		bufferedImage = null;
	}



	//===============================================================================================
	public Sprite getSprite()
	{//===============================================================================================
		return sprite;

	}
	//===============================================================================================
	public BufferedImage getImage()
	{//===============================================================================================

		if(bufferedImage==null)
		{
			if(toAlpha()<1.0f)bufferedImage = sprite.getFrameImageTransparent(initialFrame());
			else bufferedImage = sprite.getFrameImage(initialFrame());
		}


		return bufferedImage;
	}



	//===============================================================================================
	public Entity duplicate(Map mapToCopyTo, MapState stateToCopyTo)
	{//===============================================================================================
		Entity entityCopy = new Entity(mapToCopyTo, stateToCopyTo);

		entityCopy.data.setName(new String(""+this.name()));

		entityCopy.setXPixels(this.xP());
		entityCopy.setYPixels(this.yP());
		entityCopy.setInitialFrame(this.initialFrame());
		entityCopy.setComment(new String(""+this.comment()));
		entityCopy.setAnimateThroughAllFrames(this.animatingThroughAllFrames());
		entityCopy.setTicksBetweenFrames(this.ticksBetweenFrames());
		entityCopy.setTicksBetweenAnimationLoop(this.ticksBetweenAnimationLoop());
		entityCopy.setRandomUpToTicksBetweenAnimationLoop(this.randomUpToTicksBetweenAnimationLoop());
		entityCopy.setPushable(this.pushable());
		entityCopy.setNonWalkable(this.nonWalkable());
		entityCopy.setToAlpha(this.toAlpha());
		entityCopy.setScale(this.scale());

		entityCopy.setRenderOrder(this.renderOrder());
		//entityCopy.setAboveTopLayer(this.aboveTopLayer());
		entityCopy.setAboveWhenEqual(this.aboveWhenEqual());
		entityCopy.setAlwaysOnBottom(this.alwaysOnBottom());


		entityCopy.setTicksPerPixelMoved(this.ticksPerPixelMoved());
		entityCopy.setOnlyHereDuringEvent(this.onlyHereDuringEvent());

		entityCopy.setRandomFrames(this.randomFrames());
		entityCopy.setDisableShadow(this.disableShadow());

		entityCopy.data.setSpriteName(this.spriteName());


		for(int i=0;i<this.behaviorList().size();i++)entityCopy.behaviorList().add(new String(""+this.behaviorList().get(i)));
		for(int i=0;i<this.connectionTYPEIDList().size();i++)entityCopy.connectionTYPEIDList().add(this.connectionTYPEIDList().get(i));

		if(this.eventData()==null)entityCopy.setEventData(null);
		else entityCopy.setEventData(Project.getEventByID(this.eventData().id()).duplicate().getData());





		entityCopy.frameTimer = new Timer(100,frameTimer.getActionListeners()[0]);
		entityCopy.startAnimationTimer = new Timer(100,startAnimationTimer.getActionListeners()[0]);
		entityCopy.currentAnimationFrame = currentAnimationFrame;

		entityCopy.bufferedImage = null;
		entityCopy.sprite = sprite;


		return entityCopy;

	}


//
//	//===============================================================================================
//	public Map getMap()
//	{//===============================================================================================
//
//		if(map==null)
//		{
//
//			//find what map this entity is on
//			for(int i=0;i<Project.getNumMaps();i++)
//			{
//				for(int s=0;s<Project.getMap(i).getNumStates();s++)
//				{
//					for(int k=0;k<Project.getMap(i).getState(s).getNumEntities();k++)
//					{
//						if(Project.getMap(i).getState(s).getEntity(k)==this)
//						{
//							map = Project.getMap(i);
//							state = Project.getMap(i).getState(s);
//						}
//					}
//				}
//			}
//		}
//
//		return map;
//	}


	//===============================================================================================
	public String getLongTypeName()
	{//===============================================================================================


		if(map==null||state==null)
		{


			//find what map this entity is on
			for(int i=0;i<Project.getNumMaps();i++)
			{
				for(int s=0;s<Project.getMap(i).getNumStates();s++)
				{
					for(int k=0;k<Project.getMap(i).getState(s).getNumEntities();k++)
					{
						if(Project.getMap(i).getState(s).getEntity(k)==this)
						{
							map = Project.getMap(i);
							state = Project.getMap(i).getState(s);
						}
					}
				}
			}
		}


		return "ENTITY."+map.name()+"."+state.name()+"."+name();

	}
	//===============================================================================================
	public String getShortTypeName()
	{//===============================================================================================
		return "ENTITY."+name();
	}

	//===============================================================================================
	public void setNameNoRename(String newName)
	{//===============================================================================================
		this.data.setName(newName);

	}
	//===============================================================================================
	public void setName(String newName)
	{//===============================================================================================

		String oldName = name();

		this.data.setName(newName);


		if(map==null||state==null)
		{


			//find what map this entity is on
			for(int i=0;i<Project.getNumMaps();i++)
			{
				for(int s=0;s<Project.getMap(i).getNumStates();s++)
				{
					for(int k=0;k<Project.getMap(i).getState(s).getNumEntities();k++)
					{
						if(Project.getMap(i).getState(s).getEntity(k)==this)
						{
							map = Project.getMap(i);
							state = Project.getMap(i).getState(s);
						}
					}
				}
			}
		}

		if(map==null)System.err.println("Couldn't find entity in maps in setName()");
		if(state==null)System.err.println("Couldn't find entity in state in setName()");



		if(map!=null)
		{
			//rename any entity with the same name in any states in THIS MAP
			//have to do all states, keeping entity names synchronized between states
			for(int k=0;k<map.getNumStates();k++)
			{
				for(int n=0;n<map.getState(k).getNumEntities();n++)
				{
					Entity e = map.getState(k).getEntity(n);
					if(e.name().equals(oldName))e.setNameNoRename(newName);
				}
			}
		}



		//don't have to do this anymore, everything is tracked by id

		//then rename this door in all events
//		for(int i = 0; i < Project.eventList.size(); i++)
//		{
//			Project.eventList.get(i).renameEntityString(map.name,oldName,newName);
//		}








	}




}
