package com.bobsgame.client.engine.map;


import static org.lwjgl.opengl.GL11.*;


//import static org.lwjgl.opengl.GL13.*;
//import static org.lwjgl.opengl.GL15.*;
//import static org.lwjgl.opengl.GL20.*;
//import static org.lwjgl.opengl.GL21.*;
//import static org.lwjgl.opengl.GL30.*;
//import static org.lwjgl.opengl.GL31.*;
//import static org.lwjgl.opengl.GL32.*;
//import static org.lwjgl.opengl.GL33.*;
//import static org.lwjgl.opengl.GL40.*;
//import static org.lwjgl.opengl.GL41.*;
//import static org.lwjgl.opengl.GL42.*;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Enumeration;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import javax.imageio.ImageIO;
//import java.nio.IntBuffer;

//import org.lwjgl.BufferUtils;
//import org.lwjgl.input.Keyboard;
//import com.bobsgame.editor.BobColor;

import org.slf4j.LoggerFactory;

import com.bobsgame.client.Texture;


import ch.qos.logback.classic.Logger;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.Cache;
import com.bobsgame.client.console.Console;
import com.bobsgame.client.console.ConsoleText;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.entity.Character;

import com.bobsgame.client.engine.entity.Entity;
import com.bobsgame.client.engine.entity.Sprite;
import com.bobsgame.client.engine.entity.RandomCharacter;
import com.bobsgame.client.engine.event.Event;
import com.bobsgame.client.engine.game.FriendCharacter;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.client.engine.game.Player;
import com.bobsgame.client.engine.game.gui.statusbar.notification.Notification;
import com.bobsgame.shared.AreaData;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.DoorData;
import com.bobsgame.shared.EntityData;
import com.bobsgame.shared.EventData;
import com.bobsgame.shared.LightData;
import com.bobsgame.shared.MapData;
import com.bobsgame.shared.MapStateData;
import com.bobsgame.shared.SpriteAnimationSequence;
import com.bobsgame.shared.Utils;
import com.bobsgame.shared.MapData.RenderOrder;

import hq2x.HQ2X;
//import com.bobsgame.server.BGSharedNetworkObjects.MapDataMD5sObject;

//=========================================================================================================================
public class Map extends EnginePart
{//=========================================================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(Map.class);


	public MapState currentState = null;
	public boolean randomSpawnEnabled = true;


	public ArrayList<MapState> stateList = new ArrayList<MapState>();
	public ArrayList<Integer> mapEventIDList = new ArrayList<Integer>();





	public float lastKnownScreenX=0;
	public float lastKnownScreenY=0;




	public float alpha = 1.0f;







	//this is a ArrayList of ArrayLists of sorted lights per layer. this is filled in on map first load.
	public ArrayList<ArrayList<Light>> sortedLightsLayers = new ArrayList<ArrayList<Light>>();





	//these are entities that exist in this map
	public ArrayList<Entity> activeEntityList = new ArrayList<Entity>();
	//this gets filled in once per frame with entities from entityList that are on the screen
	public ArrayList<Entity> drawList = new ArrayList<Entity>();
	//that gets sorted into zList which is drawn in sequence.
	public ArrayList<Entity> zList = new ArrayList<Entity>();

	//door/warp list
	public ArrayList<Door> doorList = new ArrayList<Door>();
	public ArrayList<WarpArea> warpAreaList = new ArrayList<WarpArea>();



	public int hitLayer[] = null;
	public int cameraLayer[] = null;
	public int groundShaderLayer[] = null;
	public int lightMaskLayer[] = null;



	Texture chunkTexture[] = null;
	boolean chunkPNGFileExists[] = null;
	boolean hq2xChunkPNGFileExists[] = null;
	boolean usingHQ2XTexture[] = null;

	public int tilesetIntArray[] = null;
	public byte paletteRGBByteArray[] = null;



	public int chunkSizePixelsHQ2X = 512;
	public int chunkSizePixels1X = chunkSizePixelsHQ2X/2;
	public int chunkSizeTiles1X = chunkSizePixels1X/8;


	static public ExecutorService generatePNGExecutorService = null;
	static public ExecutorService generateLightPNGExecutorService = null;
	//public ExecutorService generateHQ2XPNGExecutorService = null;



	public int chunkTexturesLoaded = 0;

	public int maxHq2xChunkPNGThreadsCreated = 0;
	public int hq2xChunkPNGThreadsCreated = 0;

	public int maxChunkPNGThreadsCreated = 0;
	public int chunkPNGThreadsCreated = 0;

	public int maxLightPNGThreadsCreated = 0;
	public int lightPNGThreadsCreated = 0;

	ConsoleText texturesLoadedDebugText = null;
	ConsoleText hq2xChunkPNGThreadsDebugText = null;
	ConsoleText chunkPNGThreadsDebugText = null;
	ConsoleText lightPNGThreadsDebugText = null;


	int chunksWidth = 0;
	int chunksHeight = 0;



	boolean startedMissingChunkPNGThreads = false;
	boolean startedMissingLightPNGThreads = false;
	boolean startedMissingHQ2XChunkPNGThreads = false;

	boolean allChunkPNGsLoadedAsTextures = false;
	boolean allLightsLoadedAsTextures = false;
	boolean allHQ2XChunkPNGsLoadedAsTextures = false;

	public boolean utilityLayersLoaded = false;

	public boolean miniMapGenerated = false;

	long lastTimeMD5sRequested = 0;


	Notification generatingAreaNotification = null;


	public boolean addedEntitiesAndCharactersFromCurrentStateToActiveEntityList=false;

	public boolean eventsAllLoadedFromServer = false;








	private MapData data;



	//=========================================================================================================================
	public Map(Engine g, MapData mapData)
	{//=========================================================================================================================
		super(g);

		this.data = mapData;



		//determine number of chunks horizontal and vertical

		//TODO: make this proper with modulus, if the split is even there will be one extra chunk
		chunksWidth = (mapData.widthTiles1X()/chunkSizeTiles1X)+1;
		chunksHeight = (mapData.heightTiles1X()/chunkSizeTiles1X)+1;

		if(chunkTexture==null)
		{
			chunkTexture = new Texture[chunksWidth*chunksHeight*2];// *2 for over/under layer
			for(int i=0;i<chunksWidth*chunksHeight*2;i++)chunkTexture[i]=null;
		}

		if(chunkPNGFileExists==null)
		{
			chunkPNGFileExists = new boolean[chunksWidth*chunksHeight*2];
			for(int i=0;i<chunksWidth*chunksHeight*2;i++)chunkPNGFileExists[i]=false;
		}

		if(hq2xChunkPNGFileExists==null)
		{
			hq2xChunkPNGFileExists = new boolean[chunksWidth*chunksHeight*2];
			for(int i=0;i<chunksWidth*chunksHeight*2;i++)hq2xChunkPNGFileExists[i]=false;
		}

		if(usingHQ2XTexture==null)
		{
			usingHQ2XTexture = new boolean[chunksWidth*chunksHeight*2];
			for(int i=0;i<chunksWidth*chunksHeight*2;i++)usingHQ2XTexture[i]=false;
		}






		//need to run through mapData structure and create entities, events, lights, areas, doors, states, warpareas




		for(int i=0;i<mapData.eventDataList().size();i++)
		{

			//create event, add to eventList
			EventData eventData = mapData.eventDataList().get(i);


			Event event = null;

			for(int k=0;k<EventManager().eventList.size();k++)
			{
				if(EventManager().eventList.get(k).id()==eventData.id())
				{
					event = EventManager().eventList.get(k);
				}
			}

			if(event==null)event = new Event(Engine(),eventData);

			this.mapEventIDList.add(event.id());

		}


		for(int i=0;i<mapData.doorDataList().size();i++)
		{
			//create door, add to doorList,

			DoorData doorData = mapData.doorDataList().get(i);
			Door door = new Door(Engine(),doorData, this);



			//TODO: in door update, send command to load door connecting map, it will return as a network thread, create the map object, block that thread until it is loaded.
			//also check and make sure it is sending event update

			this.doorList.add(door);

		}



		for(int i=0;i<mapData.stateDataList().size();i++)
		{

			MapStateData mapStateData = mapData.stateDataList().get(i);


			//create state, add to state list.
			MapState mapState = new MapState(mapStateData);

			this.stateList.add(mapState);


			for(int n=0;n<mapStateData.areaDataList().size();n++)
			{
				AreaData areaData = mapStateData.areaDataList().get(n);

				if(areaData.isWarpArea())
				{
					//create warparea, add to warpAreaList
					WarpArea warpArea = new WarpArea(Engine(),areaData);

					//TODO: in door update, send command to load door connecting map, it will return as a network thread, create the map object, block that thread until it is loaded.
					//also check and make sure it is sending event update

					this.warpAreaList.add(warpArea);
					//note that warp areas DON'T get added to the currentMap.areaHashmap.
					//i go through each map and search for the appropriate warparea in that list
				}
				else
				{
					Area area = new Area(Engine(),areaData, this);
					mapState.areaByNameHashtable.put(area.name(),area);
					mapState.areaByTYPEIDHashtable.put(area.getTYPEIDString(),area);
					mapState.areaList.add(area);
				}
			}


			for(int n=0;n<mapStateData.lightDataList().size();n++)
			{
				LightData lightData = mapStateData.lightDataList().get(n);
				Light light = new Light(Engine(),lightData, this);


				mapState.lightList.add(light);
				mapState.lightByNameHashtable.put(light.name(),light);
			}




			for(int n=0;n<mapStateData.entityDataList().size();n++)
			{

				EntityData entityData = mapStateData.entityDataList().get(n);

				if(entityData.isNPC())
				{
					Character character = new Character(Engine(),entityData, this);

					mapState.characterList.add(character);
					mapState.characterByNameHashtable.put(character.name(),character);
				}
				else
				{
					Entity entity = new Entity(Engine(),entityData, this);

					mapState.entityList.add(entity);
					mapState.entityByNameHashtable.put(entity.name(),entity);
				}



			}

		}





		//get load event, run it to determine which state to load. (done in update)





	}










	//=========================================================================================================================
	public Entity getEntityByName(String name)
	{//=========================================================================================================================
		Entity e = currentState.entityByNameHashtable.get(name);

		if(e==null)e = getCharacterByName(name);

		if(e==null)
		{
			for(int i=0;i<activeEntityList.size();i++)
			{
				if(activeEntityList.get(i).name().equals(name))e=activeEntityList.get(i);
			}
		}

		if(e==null)
		{
			for(int i=0;i<SpriteManager().screenSpriteList.size();i++)
			{
				if(SpriteManager().screenSpriteList.get(i).name().equals(name))e=SpriteManager().screenSpriteList.get(i);
			}
		}

		if(e==null)
		{
			e = getLightByName(name);
		}

		return e;

	}
	//=========================================================================================================================
	public Character getCharacterByName(String name)
	{//=========================================================================================================================
		return currentState.characterByNameHashtable.get(name);

	}

	//=========================================================================================================================
	public Light getLightByName(String name)
	{//=========================================================================================================================

		//log.debug("getLightByName: "+name);

		return currentState.lightByNameHashtable.get(name);
	}

	//=========================================================================================================================
	public Area getAreaOrWarpAreaByName(String name)
	{//=========================================================================================================================

		//log.debug("getAreaOrWarpAreaByName: "+name);

		if(name.startsWith("AREA."))name = name.substring(name.indexOf(".")+1);


		Area a = null;
		if(currentState!=null)a = currentState.areaByNameHashtable.get(name);

		if(a==null)
		{
			for(int i=0;i<stateList.size();i++)
			{
				MapState s = stateList.get(i);
				a = s.areaByNameHashtable.get(name);
				if(a!=null)break;
			}
		}

		if(a==null)
		{
			for(int i=0;i<warpAreaList.size();i++)
			{
				if(warpAreaList.get(i).name().equals(name))
				a=warpAreaList.get(i);
			}
		}

		if(a==null)
		{
			log.error("Could not find Area/WarpArea: getAreaOrWarpAreaByName() Name:" + name);

		}


		return a;
	}

	//=========================================================================================================================
	public Area getAreaOrWarpAreaByTYPEID(String typeID)
	{//=========================================================================================================================

		//log.debug("getAreaOrWarpAreaByName: "+name);

		if(typeID.startsWith("AREA.")==false)typeID = "AREA."+typeID;


		Area a = null;
		if(currentState!=null)a = currentState.areaByTYPEIDHashtable.get(typeID);

		if(a==null)
		{
			for(int i=0;i<warpAreaList.size();i++)
			{
				if(warpAreaList.get(i).getTYPEIDString().equals(typeID))
				a=warpAreaList.get(i);
			}
		}

		if(a==null)
		{
			for(int i=0;i<stateList.size();i++)
			{
				MapState s = stateList.get(i);
				a = s.areaByTYPEIDHashtable.get(typeID);
				if(a!=null)break;
			}
		}


		if(a==null)
		{
			log.debug("Could not find Area/WarpArea: getAreaOrWarpAreaByTYPEID() TypeID:" + typeID);
		}


		return a;
	}
	//=========================================================================================================================
	public Door getDoorByTYPEID(String typeID)
	{//=========================================================================================================================

		//log.debug("getDoorByName: "+name);

		if(typeID.startsWith("DOOR.")==false)typeID = "DOOR."+typeID;

		//doors
		//for(int n=0;n<MapAssetIndex.mapList.size();n++)
		{
			//MapAsset m = MapAssetIndex.mapList.get(n);

			for(int i=0;i<doorList.size();i++)
			{
				Door d = doorList.get(i);

				if(typeID.equals(d.getTYPEIDString()))
				{
					return d;

				}
			}
		}

		log.error("Could not find Door: getDoorByTYPEID() TypeID:"+typeID);

		return null;
	}
	//=========================================================================================================================
	public Door getDoorByName(String name)
	{//=========================================================================================================================

		//log.debug("getDoorByName: "+name);

		if(name.startsWith("DOOR."))name = name.substring(name.indexOf(".")+1);

		//doors
		//for(int n=0;n<MapAssetIndex.mapList.size();n++)
		{
			//MapAsset m = MapAssetIndex.mapList.get(n);

			for(int i=0;i<doorList.size();i++)
			{
				Door d = doorList.get(i);

				if(name.equals(d.name()))
				{
					return d;

				}
			}
		}

		log.error("Could not find Door: getDoorByName(): "+name);

		return null;
	}

	//public MapState getStateByName(String name){return getMapStateByName(name);}
	//=========================================================================================================================
	public MapState getMapStateByName(String name)
	{//=========================================================================================================================
		for(int i=0;i<stateList.size();i++)
		{
			MapState mapState = stateList.get(i);

			if(name.equals(mapState.name()))
			{
				return mapState;

			}
		}


		//we didn't find it. make a new one. throw an error.
		log.error("Could not find Map State:"+name+". This should never happen.");

		//MapState s = new MapState(-1,name);
		//stateList.add(s);


		return null;
	}


	//=========================================================================================================================
	public MapState getMapStateByID(int id)
	{//=========================================================================================================================
		//this should look through the current map mapStateList first
		for(int i=0;i<stateList.size();i++)
		{
			MapState s = stateList.get(i);
			if(s.id()==id)return s;
		}


		log.error("Could not find State ID:"+id+" in currentMap stateList. This should never happen.");
		//then it should look through every map mapStateList, since state ID is guaranteed to be unique.

		//MapState s = new MapState(id,"????");
		//stateList.add(s);


		return null;
	}



	//=========================================================================================================================
	public ArrayList<String> getListOfRandomPointsOfInterestTYPEIDs()
	{//=========================================================================================================================

		ArrayList<String> areaTYPEIDList = new ArrayList<String>();


		//areas
		Enumeration<Area> aEnum = currentState.areaByNameHashtable.elements();
		while(aEnum.hasMoreElements())
		{
			Area a = aEnum.nextElement();
			if(a.randomPointOfInterestOrExit())areaTYPEIDList.add(a.getTYPEIDString());
		}


		//warpareas
		for(int i=0;i<warpAreaList.size();i++)
		{
			Area a = warpAreaList.get(i);
			if(a.randomPointOfInterestOrExit())areaTYPEIDList.add(a.getTYPEIDString());
		}


		//doors
		for(int i=0;i<doorList.size();i++)
		{
			Door d = doorList.get(i);
			if(d.randomPointOfInterestOrExit())areaTYPEIDList.add(d.getTYPEIDString());//"DOOR."+d.getTYPEIDString());
		}


		return areaTYPEIDList;

	}


	//public Tile getTileByName(String name)
	//{
		//return tileHashtable.get(name);
	//}


	//=========================================================================================================================
	public void fadeIn()
	{//=========================================================================================================================
		if(alpha<1.0f)alpha+=0.002f*Engine().engineTicksPassed();
		if(alpha>1.0f)alpha=1.0f;
	}

	//=========================================================================================================================
	public void fadeOut()
	{//=========================================================================================================================
		if(alpha>0.0f)alpha-=0.003f*Engine().engineTicksPassed();
		if(alpha<0.0f)alpha=0.0f;
	}



	//===============================================================================================
	public void loadMapState(MapState s)
	{//===============================================================================================
		currentState=s;

	}




	private long lastLoadEventRequestTime = 0;
	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

		long time = System.currentTimeMillis();

		//this should always be true now that we are loading the mapData from the server.
		//the mapData contains the full data for the actual map Events so they are ready at load.

		//area, entity, door events, however, are simply held as eventID in those objects and they will load themselves after map is running.
		if(eventsAllLoadedFromServer==false)
		{
			if(time-lastLoadEventRequestTime>200)
			{
				lastLoadEventRequestTime = time;
				//load all events

				boolean eventsAllLoadedThisTime = false;

				if(mapEventIDList.size()>0)
				{
					eventsAllLoadedThisTime = true;
					for(int i=0;i<mapEventIDList.size();i++)
					{
						int eventID = mapEventIDList.get(i);
						Event event = EventManager().getEventByIDCreateIfNotExist(eventID);
						event.map = this;
						if(event.getInitialized_S() == false)eventsAllLoadedThisTime=false;
					}
				}

				if(eventsAllLoadedThisTime==true)eventsAllLoadedFromServer=true;
			}

			if(eventsAllLoadedFromServer==false)return;
		}




		//run load event to determine which map state to load.
		//DONE: need to choose a MapState here.
		//this is decided by the DEFAULT map Event, which should be loaded and run exactly once before the map loads.
		//so we need to go through currentMap's event list, find event type -1, and run that- before the map actually starts running. how to do that?
		//m.currentState = m.stateList.get(0);


		if(currentState==null)
		{
			if(time-lastLoadEventRequestTime>200)
			{
				lastLoadEventRequestTime = time;
				for(int i=0;i<mapEventIDList.size();i++)
				{
					Event event = EventManager().getEventByIDCreateIfNotExist(mapEventIDList.get(i));
					event.map = this;
					if(event.type()==EventData.TYPE_MAP_RUN_ONCE_BEFORE_LOAD)EventManager().addToEventQueueIfNotThere(event);
				}
			}
			return;
		}










		fadeIn();



		if(utilityLayersLoaded==false)
		{
			utilityLayersLoaded = true;
			loadUtilityLayers();

		}


		if(startedMissingLightPNGThreads==false)
		{
			startedMissingLightPNGThreads=true;
			startThreadsForMissingLightPNGs();
		}
		else
		if(allLightsLoadedAsTextures==false)
		{
			allLightsLoadedAsTextures = loadLightTexturesFromCachePNGs();
		}


		if(sortedLightsLayers.size()==0)
		{
			sortLightLayers();
		}





		//load map entities into entitymanager
		if(addedEntitiesAndCharactersFromCurrentStateToActiveEntityList==false)
		{
			addEntitiesAndCharactersFromCurrentStateToActiveEntityList();
			addedEntitiesAndCharactersFromCurrentStateToActiveEntityList=true;
		}




		//don't hammer eventList
		if(time-lastLoadEventRequestTime>200)
		{
			lastLoadEventRequestTime = time;
			//run all events, **this will also run post-load events for this map, which stop executing after one loop.
			for(int i=0;i<mapEventIDList.size();i++)
			{
				Event event = EventManager().getEventByIDCreateIfNotExist(mapEventIDList.get(i));
				event.map = this;
				if(event.type()!=EventData.TYPE_MAP_DONT_RUN_UNTIL_CALLED&&event.type()!=EventData.TYPE_MAP_RUN_ONCE_BEFORE_LOAD)EventManager().addToEventQueueIfNotThere(event);
			}
		}



		updateEntities();
		updateDoors();

		updateAreas();
		updateWarpAreas();

		//run();

		updateLights();

		zOrderEntities();





		if(startedMissingChunkPNGThreads==false)
		{
			startedMissingChunkPNGThreads=true;
			startThreadsForMissingChunkPNGs();
		}
		else
		if(allChunkPNGsLoadedAsTextures==false || MapManager.loadTexturesOnDemand==true)
		{
			allChunkPNGsLoadedAsTextures = loadChunkTexturesFromCachePNGs();
		}


		//else
		/*
		if(miniMapGenerated==false)
		{
			miniMapGenerated=true;

			drawMiniMapIntoFBO();

		}
		else
		*/

		if(MapManager.loadTexturesOnDemand==true&&startedMissingChunkPNGThreads==true)
		if(MapManager.generateHQ2XChunks==true)
		{
			if(startedMissingHQ2XChunkPNGThreads==false)
			{
				startedMissingHQ2XChunkPNGThreads=true;
				startThreadsForMissingHQ2XChunkPNGs();
			}
		}


		if(allChunkPNGsLoadedAsTextures==true)
		if(MapManager.generateHQ2XChunks==true)
		{

			//check here to see if we already loaded all hq2x textures while loading regular textures, no need to start threads if we have.
			//i don't really have to do this, but why start a thread pool if we don't have to?
			if(allHQ2XChunkPNGsLoadedAsTextures==false)
			{
				boolean tempAllHQ2XChunkPNGsLoaded = true;

				for(int chunkY=0;chunkY<chunksHeight;chunkY++)
				for(int chunkX=0;chunkX<chunksWidth;chunkX++)
				for(int chunkLayer=0;chunkLayer<2;chunkLayer++)
				{
					int chunkIndex = (chunksWidth*chunksHeight*chunkLayer)+((chunkY*chunksWidth)+chunkX);

					if(usingHQ2XTexture[chunkIndex]==false)
					{
						tempAllHQ2XChunkPNGsLoaded = false;
					}
				}
				if(tempAllHQ2XChunkPNGsLoaded==true)allHQ2XChunkPNGsLoadedAsTextures = true;
			}


			//if we still havent loaded them all, they must not exist.
			//start the threads to create them and load them as the threads finish
			if(allHQ2XChunkPNGsLoadedAsTextures==false)
			{

				if(startedMissingHQ2XChunkPNGThreads==false)
				{

					//TODO: manage cpu usage of threads, make sure they don't lower the framerate, even on slow computers.

					startedMissingHQ2XChunkPNGThreads=true;
					startThreadsForMissingHQ2XChunkPNGs();
				}
				else
				{
					allHQ2XChunkPNGsLoadedAsTextures = loadHQ2XTexturesFromCachePNGs();
				}
			}

		}

		//nice percentage progress of chunk/light/hq2x PNG generation and chunk texture loading
		updateLoadingStatus();


		/*if(
				MapManager.useThreads==true&&
				generatePNGExecutorService!=null&&
				startedMissingLightPNGThreads==true&&
				startedMissingChunkPNGThreads==true&&
				startedMissingHQ2XChunkPNGThreads==true
		)
		{
			if(generatePNGExecutorService.isShutdown()==false)
			{
				generatePNGExecutorService.shutdown();
				log.debug("generatePNGExecutorService Shut Down");
			}
		}*/




	}




	//=========================================================================================================================
	public void updateLoadingStatus()
	{//=========================================================================================================================
		if(maxHq2xChunkPNGThreadsCreated>0)
		{
			if(hq2xChunkPNGThreadsDebugText==null)hq2xChunkPNGThreadsDebugText = Console.debug("hq2xChunkPNGThreadsDebugText");



			{
				float percent = ((float)(maxHq2xChunkPNGThreadsCreated-hq2xChunkPNGThreadsCreated)/(float)maxHq2xChunkPNGThreadsCreated)*100.0f;
				hq2xChunkPNGThreadsDebugText.text = "HQ2X Chunk PNG Threads: "+(maxHq2xChunkPNGThreadsCreated-hq2xChunkPNGThreadsCreated)+" / "+maxHq2xChunkPNGThreadsCreated+" ( "+percent+" % )";
			}

			if(hq2xChunkPNGThreadsCreated==0)
			{
				maxHq2xChunkPNGThreadsCreated=0;
				hq2xChunkPNGThreadsDebugText.ticks=1000;
				hq2xChunkPNGThreadsDebugText=null;
			}
		}


		if(maxChunkPNGThreadsCreated>0)
		{
			if(chunkPNGThreadsDebugText==null)chunkPNGThreadsDebugText = Console.debug("chunkPNGThreadsDebugText");


			{
				float percent = ((float)(maxChunkPNGThreadsCreated-chunkPNGThreadsCreated)/(float)maxChunkPNGThreadsCreated)*100.0f;
				chunkPNGThreadsDebugText.text = "1X Chunk PNG Threads: "+(maxChunkPNGThreadsCreated-chunkPNGThreadsCreated)+" / "+maxChunkPNGThreadsCreated+" ( "+percent+" % )";

			}

			if(chunkPNGThreadsCreated==0)
			{
				maxChunkPNGThreadsCreated=0;
				chunkPNGThreadsDebugText.ticks=1000;
				chunkPNGThreadsDebugText=null;
			}
		}


		if(maxLightPNGThreadsCreated>0)
		{
			if(lightPNGThreadsDebugText==null)lightPNGThreadsDebugText = Console.debug("lightPNGThreadsDebugText");


			{
				float percent = ((float)(maxLightPNGThreadsCreated-lightPNGThreadsCreated)/(float)maxLightPNGThreadsCreated)*100.0f;
				lightPNGThreadsDebugText.text = "Light PNG Threads: "+(maxLightPNGThreadsCreated-lightPNGThreadsCreated)+" / "+maxLightPNGThreadsCreated+" ( "+percent+" % )";
			}

			if(lightPNGThreadsCreated==0)
			{
				maxLightPNGThreadsCreated=0;
				lightPNGThreadsDebugText.ticks=1000;
				lightPNGThreadsDebugText=null;
			}
		}


		if(chunkTexturesLoaded>0&&MapManager.loadTexturesOnDemand==false)
		{
			int totalChunkTextures = (chunksWidth*chunksHeight*2);

			if(texturesLoadedDebugText==null)texturesLoadedDebugText = Console.debug("texturesLoadedDebugText");

			if(generatingAreaNotification==null)generatingAreaNotification = new Notification(((ClientGameEngine)Engine()),"Loading Area...");


			{
				float percent = ((float)chunkTexturesLoaded/(float)(totalChunkTextures))*100.0f;
				texturesLoadedDebugText.text = "Textures Loaded: "+(chunkTexturesLoaded)+" / "+(totalChunkTextures)+" ( "+percent+" % )";
				generatingAreaNotification.progress = percent/100.0f;
			}

			if(chunkTexturesLoaded==totalChunkTextures)
			{
				chunkTexturesLoaded=0;
				texturesLoadedDebugText.ticks=1000;
				texturesLoadedDebugText=null;

				if(generatingAreaNotification!=null)generatingAreaNotification = generatingAreaNotification.delete();
			}
		}

		if(MapManager.loadTexturesOnDemand==true)
		if(generatingAreaNotification!=null)generatingAreaNotification = generatingAreaNotification.delete();



	}

	//=========================================================================================================================
	public void updateEntities()
	{//=========================================================================================================================

		//for all entities update
		for(int n=0;n<activeEntityList.size();n++)
		{
			Entity e = activeEntityList.get(n);

			e.update();
		}

	}


	//=========================================================================================================================
	public void updateDoors()
	{//=========================================================================================================================

		for(int n=0;n<doorList.size();n++)
		{
			Door e = doorList.get(n);

			e.update();
		}
	}

	//=========================================================================================================================
	public void updateAreas()
	{//=========================================================================================================================

		if(currentState==null)return;

//		Enumeration<Area> aEnum = currentState.areaHashtable.elements();
//		while(aEnum.hasMoreElements())
//		{
//			Area a = aEnum.nextElement();
//			a.update();
//		}

		for(int i=0;i<currentState.areaList.size();i++)
		{
			Area a = currentState.areaList.get(i);
			a.update();
		}

	}



	//=========================================================================================================================
	public void updateWarpAreas()
	{//=========================================================================================================================
		for(int i=0;i<warpAreaList.size();i++)
		{
			//if(warpAreaList.get(i).mapAsset==currentMap)
			{
				warpAreaList.get(i).update();
			}
		}
	}



	//=========================================================================================================================
	public void updateLights()
	{//=========================================================================================================================

		for(int i=0;i<currentState.lightList.size();i++)currentState.lightList.get(i).update();

	}

	//=========================================================================================================================
	public void zOrderEntities()
	{//=========================================================================================================================



		drawList.clear();


		for(int i=0;i<activeEntityList.size();i++)
		{
			Entity e = activeEntityList.get(i);

			//decide which ones need rendering
			//add to new linked list of on-screen entities to z-order
			if(e.shouldDraw())if(drawList.contains(e)==false)drawList.add(e);

		}

		for(int i=0;i<doorList.size();i++)
		{
			Door e = doorList.get(i);

			//decide which ones need rendering
			//add to new linked list of on-screen entities to z-order
			if(e.shouldDraw())if(drawList.contains(e)==false)drawList.add(e);

		}

		if(CurrentMap()!=null && CurrentMap()==this)
		if(ClientGameEngine()!=null && ClientGameEngine().playerExistsInMap==false)
		if(Player()!=null&&Player().shouldDraw())if(drawList.contains(Player())==false)drawList.add(Player());



		if(Engine() instanceof ClientGameEngine)
		{
			//add friends, they are not added to any entityList
			for(int i=0;i<ClientGameEngine().friendManager.friendCharacters.size();i++)
			{
				FriendCharacter f = FriendManager().friendCharacters.get(i);

				if(f.mapName.equals(this.name()))
				{
					if(f.shouldDraw())if(drawList.contains(f)==false)drawList.add(f);
				}
			}
		}




		//z-order all entities

		//now we want to make a new list of all the on-screen entities, z-ordered starting at the top of the screen and working to the bottom
		//for each entity in the drawList, find the topmost one and add it to the new list, then remove it from the drawList


		zList.clear();

		while(drawList.size()!=0)
		{
			Entity highestOnScreenEntity = null;

			for(int n=0;n<drawList.size();n++)
			{
				Entity e = drawList.get(n);

				//store topmost entity on screen
				//check for non-zordering entities, entities always on top, entities always on bottom here.



				if(e.alwaysOnBottom())
				{
					highestOnScreenEntity=e;
					break;
				}

				if(

					highestOnScreenEntity==null
					||
					(
						e.alwaysOnTop()==false
						&&
						(
							e.middleY()<highestOnScreenEntity.middleY()
							||
							(
								highestOnScreenEntity.aboveWhenEqual()
								&&
								(int)(Math.floor(highestOnScreenEntity.bottom()))==(int)(Math.floor(e.bottom()))
							)
						)
					)
				)
				{
					highestOnScreenEntity=e;
				}
			}

			drawList.remove(highestOnScreenEntity);
			zList.add(highestOnScreenEntity);
		}



//		log.debug("---------------------");
//
//		for(int i=0;i<zList.size();i++)
//		{
//			Entity e = zList.get(i);
//			log.debug(e.spriteName());
//		}


		//TODO: if any part of the feet are under a tile on the above layer, dont draw the shadow


	}


	//public Tile getTileByName(String name)
	//{
		//return tileHashtable.get(name);
	//}


	//=========================================================================================================================
	public void sortLightLayers()
	{//=========================================================================================================================


		//TODO: redo this algorithm so splarka doesn't get pissy
		//even though it was sent without a license written in javascript and i ported, rewrote, and optimised it :P


		//for all lights
			//if light is not drawn

		for(int i=0; i<currentState.lightList.size(); i++)
		{

			Light l = currentState.lightList.get(i);
			//if light is not drawn
			if(l.sortingState != Light.DRAWN)
			{
				ArrayList<Light> thisLayerList = new ArrayList<Light>();

				//light is drawing
				l.sortingState = Light.DRAWING;

				//for all lights from this light to the end
				for(int a=i+1; a<currentState.lightList.size(); a++)
				{
					Light compareLight = currentState.lightList.get(a);

					//if that light isn't already drawn
					if(compareLight.sortingState != Light.DRAWN)
					{

						//for all lights
						for(int b=0;b<currentState.lightList.size();b++)
						{
							Light overlapLight = currentState.lightList.get(b);

							//if this light isn't
							if(a != b && overlapLight.sortingState == Light.DRAWING)
							{

								float left1 = compareLight.left();
								float right1 = compareLight.right();
								float top1 = compareLight.top();
								float bottom1 = compareLight.bottom();

								float left2 = overlapLight.left();
								float right2 = overlapLight.right();
								float top2 = overlapLight.top();
								float bottom2 = overlapLight.bottom();

								if((left1 < right2) && (right1 > left2) && (top1 < bottom2) && (bottom1 > top2))
								{
									compareLight.sortingState = Light.OVERLAPS_SOMETHING;
								}

							}
						}
						if(compareLight.sortingState != Light.OVERLAPS_SOMETHING)
						{
							compareLight.sortingState = Light.DRAWING;
						}
						else
						{
							compareLight.sortingState = Light.NOT_DRAWN;
						}
					}
				}


				for(int d=0; d<currentState.lightList.size(); d++)
				{
					Light drawLight = currentState.lightList.get(d);
					if(drawLight.sortingState == Light.DRAWING)
					{

						thisLayerList.add(drawLight);

						//draw light
						drawLight.sortingState = Light.DRAWN;
					}
				}

				//log.debug("Light layer "+layer);
				//layer++;
				sortedLightsLayers.add(thisLayerList);
			}
		}


	}


	public boolean defaultDisableClip = false;
	public boolean defaultDisableFloorOffset = false;


	//=========================================================================================================================
	public void render(RenderOrder renderOrder)
	{//=========================================================================================================================
		render(renderOrder,defaultDisableClip,defaultDisableFloorOffset);
	}

	//=========================================================================================================================
	public void render(RenderOrder renderOrder, boolean disableClip)
	{//=========================================================================================================================
		render(renderOrder,disableClip,defaultDisableFloorOffset);
	}

	//=========================================================================================================================
	public void render(RenderOrder renderOrder, boolean disableClip, boolean disableFloorOffset)
	{//=========================================================================================================================

		if(renderOrder==RenderOrder.GROUND&&Engine().underLayerEnabled==false)return;
		if(renderOrder==RenderOrder.ABOVE&&Engine().overLayerEnabled==false)return;

		//only allow above or ground
		if(renderOrder!=RenderOrder.GROUND&&renderOrder!=RenderOrder.ABOVE)return;


		int layerIndex = 0;
		if(renderOrder==RenderOrder.GROUND)layerIndex=0;
		if(renderOrder==RenderOrder.ABOVE)layerIndex=1;



		Texture texture = null;

		float sw = Engine().getWidth();
		float sh = Engine().getHeight();

		float zoom = Cameraman().getZoom();

		int filter=GLUtils.FILTER_LINEAR;
		if(zoom==1.0f||zoom>=1.5f||zoom==0.5f)filter=GLUtils.FILTER_NEAREST;



		float tx0 = 0.0f;
		float tx1 = 1.0f;
		float ty0 = 0.0f;
		float ty1 = 1.0f;


		float x0 = 0;
		float x1 = 0;
		float y0 = 0;
		float y1 = 0;


		//for each texture chunk starting at screen-chunksize*zoom
		//if texture isn't null, draw it at the correct place.


		//start at screen - chunksize

		int startChunkX = ((int) Math.floor(((mapCamX()) / (chunkSizePixelsHQ2X))));
		int startChunkY = ((int) Math.floor(((mapCamY()) / (chunkSizePixelsHQ2X))));

		if(startChunkX<0)startChunkX=0;
		if(startChunkY<0)startChunkY=0;

		int screenChunkWidth = ((int)Math.floor(sw/(chunkSizePixelsHQ2X*zoom)))+1;
		int screenChunkHeight = ((int)Math.floor(sh/(chunkSizePixelsHQ2X*zoom)))+1;


		//for drawing the lastMap, we can't clip based on the camera so we have to draw the whole thing.
		if(disableClip==true)
		{
			startChunkX = 0;
			startChunkY = 0;
			screenChunkWidth = chunksWidth;
			screenChunkHeight = chunksHeight;
		}

		for(int chunkY = startChunkY;chunkY<=startChunkY+screenChunkHeight&&chunkY<chunksHeight;chunkY++)
		for(int chunkX = startChunkX;chunkX<=startChunkX+screenChunkWidth&&chunkX<chunksWidth;chunkX++)
		{



			//old way, floor and ceil was good but had small line artifacts when zooming
			//if i make them all floor, the line artifacts are worse, same if i make ceil round
			//if i remove the floor and ceil, the grass is "shimmery" and vertical lines are clippy

			//float chunkMapScreenX = (float) Math.floor(map_screen_x*drawScale+(chunkX * chunkSizePixelsHQ2X*drawScale));
			//float chunkMapScreenY = (float) Math.floor(map_screen_y*drawScale+(chunkY * chunkSizePixelsHQ2X*drawScale));
			//float chunkMapScreenX2 = (float) Math.ceil(chunkMapScreenX+chunkSizePixelsHQ2X*drawScale);
			//float chunkMapScreenY2 = (float) Math.ceil(chunkMapScreenY+chunkSizePixelsHQ2X*drawScale);

			//this seems to work the best:
			//i am only flooring the map screen coords, then using that as an offset for all the other values.
			//this has no lines in between zoom levels
			float chunkMapScreenX = (float) Math.floor(screenX()*zoom)+(chunkX * chunkSizePixelsHQ2X*zoom);
			float chunkMapScreenY = (float) Math.floor(screenY()*zoom)+(chunkY * chunkSizePixelsHQ2X*zoom);

			if(disableFloorOffset)
			{
				chunkMapScreenX = (float)(screenX()*zoom)+(chunkX * chunkSizePixelsHQ2X*zoom);
				chunkMapScreenY = (float)(screenY()*zoom)+(chunkY * chunkSizePixelsHQ2X*zoom);
			}

			float chunkMapScreenX2 = (float) (chunkMapScreenX+chunkSizePixelsHQ2X*zoom);
			float chunkMapScreenY2 = (float) (chunkMapScreenY+chunkSizePixelsHQ2X*zoom);


			if(
					chunkMapScreenX>=sw || //off the right side
					chunkMapScreenX2<0 || //off the left side

					chunkMapScreenY>=sh || //off the bottom
					chunkMapScreenY2<0 //off the top
			)
			continue;

			x0 = (chunkMapScreenX);
			y0 = (chunkMapScreenY);

			x1 = (chunkMapScreenX2);
			y1 = (chunkMapScreenY2);


			int chunkIndex = (chunksWidth*chunksHeight*layerIndex)+((chunksWidth*chunkY)+chunkX);

			texture = getChunkTexture(chunkIndex);

			if(texture!=null&&texture!=GLUtils.blankTexture)GLUtils.drawTexture(texture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,alpha,filter);

		}





		//OLD WAY, SINGLE ROOM GRAPHICS

		//this only renders the clip that needs it


/*
		//if the map is offscreen, don't draw anything

		if((map_screen_x*G.zoom)+(tw*G.zoom)<0)return;
		if((map_screen_y*G.zoom)+(th*G.zoom)<0)return;

		if((map_screen_x*G.zoom)>=sw)return;//this could still be on the screen :\
		if((map_screen_y*G.zoom)>=sh)return;


		if((map_screen_x*G.zoom)<0)
		{
			//tx0 is greater than 0
			tx0 = (float)(0-(map_screen_x*G.zoom))/(float)(tw*G.zoom);
			//x0 is 0
			x0=0;
		}

		if(map_screen_x*G.zoom>=0)
		{
			//tx0 is 0
			tx0=0.0f;
			//x0 is map_cam_x/sw
			x0=(int)(map_screen_x*G.zoom);
		}

		//if map extends off screen to the right
		if((map_screen_x*G.zoom)+(tw*G.zoom)>=sw)
		{
			tx1=(float)(sw-(map_screen_x*G.zoom))/(float)(tw*G.zoom);

			x1=sw;
		}
		else
		{
			tx1 = 1.0f;
			x1 = (int)(map_screen_x*G.zoom)+(int)(tw*G.zoom);
		}




		if((map_screen_y*G.zoom)<0)
		{
			//ty0 is greater than 0
			ty0 = (float)(0-(map_screen_y*G.zoom))/(float)(th*G.zoom);
			//y0 is 0
			y0=0;
		}

		if((map_screen_y*G.zoom)>=0)
		{
			//ty0 is 0
			ty0=0.0f;
			//y0 is map_cam_y
			y0=(int)(map_screen_y*G.zoom);
		}

		//if map extends off screen to the bottom
		if((map_screen_y*G.zoom)+(th*G.zoom)>=sh)
		{
			ty1=(float)(sh-(map_screen_y*G.zoom))/(float)(th*G.zoom);
			y1=sh;
		}
		else
		{
			ty1 = 1.0f;
			y1 = (int)(map_screen_y*G.zoom)+(int)(th*G.zoom);
		}


		*/



		//this renders the whole thing and lets the card clip it
		/*
		float tx0 = 0.0f;// = (float)cam_x/(float)tw;
		float tx1 = 1.0f;//(float)(cam_x+ssx)/(float)tw;

		float ty0 = 0.0f;
		float ty1 = 1.0f;


		int x0 = (int)(map_screen_x*G.zoom);
		int x1 = (int)((map_screen_x*G.zoom)+(tw*G.zoom));
		int y0 = (int)(map_screen_y*G.zoom);
		int y1 = (int)((map_screen_y*G.zoom)+(th*G.zoom));




		GL.drawTexture(texture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,1.0f,0);

		*/

		/*
		texture.bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


		glBegin(GL_QUADS);

			//TL (0,0)
			glTexCoord2f(tx0,ty0);
			glVertex2i(x0,y0);

			//TR (1,0)
			glTexCoord2f(tx1,ty0);
			glVertex2i(x1,y0);

			//BR (1,1)
			glTexCoord2f(tx1,ty1);
			glVertex2i(x1,y1);

			//BL (0,1)
			glTexCoord2f(tx0,ty1);
			glVertex2i(x0,y1);

		glEnd();
		*/

	}

	//=========================================================================================================================
	public void renderEntities(RenderOrder layer)
	{//=========================================================================================================================

		if(layer==RenderOrder.GROUND)renderAreaActionIcons();

		if(Engine().entityLayerEnabled)
		{
			//for all entities, render as needed, in proper order

			for(int n=0;n<zList.size();n++)
			{
				Entity e = zList.get(n);


				if(layer==RenderOrder.SPRITE_DEBUG_OUTLINES)e.renderDebugBoxes();
				else if(layer==RenderOrder.SPRITE_DEBUG_INFO)e.renderDebugInfo();
				else if(e.renderOrder()==layer)e.render(alpha);
			}
		}

	}


	//=========================================================================================================================
	public void renderAllLightsUnsorted()
	{//=========================================================================================================================

		if(Engine().lightsLayerEnabled==false)return;

		if(currentState!=null)
		{
			for(int i=0; i<currentState.lightList.size();i++)
			{
				Light l = currentState.lightList.get(i);
				l.renderLight();
			}
		}

	}

	//=========================================================================================================================
	public void renderAreaActionIcons()
	{//=========================================================================================================================



		//TODO: go through all events currently running. each event will know whether it needs an action icon or not.

		if(currentState==null)return;

		//areas
		Enumeration<Area> aEnum = currentState.areaByNameHashtable.elements();
		while(aEnum.hasMoreElements())
		{
			Area a = aEnum.nextElement();
			//if(a.isAnAction)
			a.renderActionIcon();
		}


		//warpareas
		for(int i=0;i<warpAreaList.size();i++)
		{
			Area a = warpAreaList.get(i);
			//if(a.isAnAction)
			a.renderActionIcon();
		}

	}



	//=========================================================================================================================
	public void renderChunkBoxes()
	{//=========================================================================================================================


		//for each tile on screen
		//go through hit detection


		//glcolor
		//glbegin

		//gl add quads

		//gl end
		glColor4f(1.0f,0.5f,0.0f,0.4f);
		glBegin(GL_LINES);

		float sw = Engine().getWidth();
		float sh = Engine().getHeight();

		float zoom = Cameraman().getZoom();

		int startChunkX = ((int) Math.floor(((mapCamX()) / (chunkSizePixelsHQ2X))));
		int startChunkY = ((int) Math.floor(((mapCamY()) / (chunkSizePixelsHQ2X))));

		if(startChunkX<0)startChunkX=0;
		if(startChunkY<0)startChunkY=0;

		int screenChunkWidth = ((int)Math.floor(sw/(chunkSizePixelsHQ2X*zoom)))+1;
		int screenChunkHeight = ((int)Math.floor(sh/(chunkSizePixelsHQ2X*zoom)))+1;


		for(int chunkY = startChunkY;chunkY<=startChunkY+screenChunkHeight&&chunkY<chunksHeight;chunkY++)
		for(int chunkX = startChunkX;chunkX<=startChunkX+screenChunkWidth&&chunkX<chunksWidth;chunkX++)
		{


			float chunkMapScreenX =  (float)Math.floor(screenX()*zoom+(chunkX * chunkSizePixelsHQ2X*zoom));
			float chunkMapScreenY =  (float)Math.floor(screenY()*zoom+(chunkY * chunkSizePixelsHQ2X*zoom));
			float chunkMapScreenX2 =  (float)Math.ceil(chunkMapScreenX+chunkSizePixelsHQ2X*zoom);
			float chunkMapScreenY2 =  (float)Math.ceil(chunkMapScreenY+chunkSizePixelsHQ2X*zoom);


			//left
			glVertex2f(chunkMapScreenX, chunkMapScreenY);
			glVertex2f(chunkMapScreenX, chunkMapScreenY2);

			//right
			glVertex2f(chunkMapScreenX2, chunkMapScreenY);
			glVertex2f(chunkMapScreenX2, chunkMapScreenY2);

			//top
			glVertex2f(chunkMapScreenX, chunkMapScreenY);
			glVertex2f(chunkMapScreenX2, chunkMapScreenY);

			//bottom
			glVertex2f(chunkMapScreenX, chunkMapScreenY2);
			glVertex2f(chunkMapScreenX2, chunkMapScreenY2);
		}


		glEnd();



	}
	//=========================================================================================================================
	public void renderHitLayer()
	{//=========================================================================================================================
		glColor4f(1.0f,0.0f,0.0f,0.4f);
		glBegin(GL_QUADS);

		float sw = Engine().getWidth();
		float sh = Engine().getHeight();

		float zoom = Cameraman().getZoom();

		int startTileX = ((int) Math.floor(((mapCamX()) / (16))));
		int startTileY = ((int) Math.floor(((mapCamY()) / (16))));

		if(startTileX<0)startTileX=0;
		if(startTileY<0)startTileY=0;

		int screenTileWidth = ((int)Math.floor(sw/(16*zoom)))+1;
		int screenTileHeight = ((int)Math.floor(sh/(16*zoom)))+1;


		for(int tileY = startTileY;tileY<=startTileY+screenTileHeight&&tileY<heightTiles1X();tileY++)
		for(int tileX = startTileX;tileX<=startTileX+screenTileWidth&&tileX<widthTiles1X();tileX++)
		{
			if(getHitLayerValueAtXYPixels((float)tileX*16, (float)tileY*16)==false)continue;

			float tileMapScreenX = (float) Math.floor(screenX()*zoom+(tileX * 16*zoom));
			float tileMapScreenY = (float) Math.floor(screenY()*zoom+(tileY * 16*zoom));
			float tileMapScreenX2 = (float) Math.ceil(tileMapScreenX+16*zoom);
			float tileMapScreenY2 = (float) Math.ceil(tileMapScreenY+16*zoom);



			glVertex2f(tileMapScreenX, tileMapScreenY);
			glVertex2f(tileMapScreenX, tileMapScreenY2);
			glVertex2f(tileMapScreenX2, tileMapScreenY2);
			glVertex2f(tileMapScreenX2, tileMapScreenY);
		}


		glEnd();

	}

	//===============================================================================================
	public void renderLightBoxes()
	{//===============================================================================================
		//light boxes
		for(int i=0; i<sortedLightsLayers.size(); i++)
		{
			ArrayList<Light> thisLayer = sortedLightsLayers.get(i);
			for(int n=0; n<thisLayer.size(); n++)
			{
				thisLayer.get(n).renderDebugBoxes();
			}
		}

	}

	//===============================================================================================
	public void renderAreaDebugBoxes()
	{//===============================================================================================

		if(currentState==null)return;

		Enumeration<Area> aEnum = currentState.areaByNameHashtable.elements();
		//areas
		while(aEnum.hasMoreElements())
		{
			Area a = aEnum.nextElement();

			a.renderDebugBoxes();
			//a.renderDebugInfo();
		}

	}



	//===============================================================================================
	public void renderAreaDebugInfo()
	{//===============================================================================================

		if(currentState==null)return;

		//TODO: make these a manager in mapmanager
		Enumeration<Area> aEnum = currentState.areaByNameHashtable.elements();
		//areas
		while(aEnum.hasMoreElements())
		{
			Area a = aEnum.nextElement();

			//a.renderDebugBoxes();
			a.renderDebugInfo();
		}

	}



	//=========================================================================================================================
	public void renderWarpAreaDebugBoxes()
	{//=========================================================================================================================

		for(int i=0;i<warpAreaList.size();i++)
		{
			//if(warpAreaList.get(i).mapAsset==currentMap)
			{
				warpAreaList.get(i).renderDebugBoxes();
			}
		}

	}



	//=========================================================================================================================
	public void renderWarpAreaDebugInfo()
	{//=========================================================================================================================

		for(int i=0;i<warpAreaList.size();i++)
		{
			//if(warpAreaList.get(i).mapAsset==currentMap)
			{
				warpAreaList.get(i).renderDebugInfo();
			}
		}
	}


//
//	//=========================================================================================================================
//	public void run()
//	{//=========================================================================================================================
//		//for map script use
//
//
//	}
//	//=========================================================================================================================
//	public void load()
//	{//=========================================================================================================================
//		//for map script use
//	}
//
//	//=========================================================================================================================
//	public void unload()
//	{//=========================================================================================================================
//		//for map script use
//	}

	//=========================================================================================================================
	public void loadUtilityLayers()
	{//=========================================================================================================================


		/*public String groundShaderMD5 = null;
		public String cameraBoundsMD5 = null;
		public String hitBoundsMD5 = null;
		public String lightMaskMD5 = null;*/

		//-----------------------------------
		//load hitlayer
		//-----------------------------------
		//hitLayer = BufferUtils.createIntBuffer((mapWidth/8) * (mapHeight/8));

		if(hitLayer==null)
		{
			hitLayer = Cache.loadIntFileFromCacheOrDownloadIfNotExist(""+hitBoundsMD5());
			/*hitLayer = new byte[widthTiles1X * heightTiles1X];

			BufferedInputStream hitBin = new BufferedInputStream(Utils.getResourceAsStream(""+CacheManager.cacheDir+hitBoundsMD5));

			try
			{
				hitBin.read(hitLayer);
				hitBin.close();
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}*/
		}


		//-----------------------------------
		//load fx layer
		//-----------------------------------
		if(cameraLayer==null)
		{
			cameraLayer = Cache.loadIntFileFromCacheOrDownloadIfNotExist(""+cameraBoundsMD5());

//			Cache.downloadSmallFileToCacheIfNotExist(""+cameraBoundsMD5());
//
//
//			cameraLayer = new byte[widthTiles1X() * heightTiles1X()];
//			BufferedInputStream fxBin = new BufferedInputStream(Utils.getResourceAsStream(""+Cache.cacheDir+cameraBoundsMD5()));
//
//			//TODO: in map editor, output this as byte array instead of int array, then i don't have to skip every other byte here
//			try
//			{
//				int data=fxBin.read();
//				int notdata=fxBin.read();
//				int i=0;
//
//				while(data!=-1||notdata!=-1)
//				{
//					cameraLayer[i]=(byte)data;
//					i++;
//					data=fxBin.read();
//					notdata=fxBin.read();
//				}
//
//				fxBin.close();
//			}
//			catch (IOException e)
//			{
//				e.printStackTrace();
//			}
		}


		//-----------------------------------
		//load ground shader layer
		//-----------------------------------

		if(groundShaderLayer==null)
		{
			groundShaderLayer = Cache.loadIntFileFromCacheOrDownloadIfNotExist(""+groundShaderMD5());

			/*groundShaderLayer = new int[widthTiles1X * heightTiles1X];
			BufferedInputStream shaderBin = new BufferedInputStream(Utils.getResourceAsStream(""+CacheManager.cacheDir+groundShaderMD5));

			try
			{
				int sbyte1=shaderBin.read();
				int sbyte2=shaderBin.read();
				int i=0;

				while(sbyte1!=-1||sbyte2!=-1)
				{

					int ubyte1 = sbyte1 & 0xFF;
					int ubyte2 = sbyte2 & 0xFF;

					int result = (ubyte2<<8) + ubyte1;

					groundShaderLayer[i]=result;
					i++;
					sbyte1=shaderBin.read();
					sbyte2=shaderBin.read();
				}

				shaderBin.close();
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}*/
		}




		//-----------------------------------
		//load light mask layer
		//-----------------------------------
		if(groundShaderLayer==null)
		{

			groundShaderLayer = Cache.loadIntFileFromCacheOrDownloadIfNotExist(""+lightMaskMD5());

			/*lightMaskLayer = new int[widthTiles1X * heightTiles1X];
			BufferedInputStream lightMaskBin = new BufferedInputStream(Utils.getResourceAsStream(""+CacheManager.cacheDir+lightMaskMD5));

			try
			{
				int sbyte1=lightMaskBin.read();
				int sbyte2=lightMaskBin.read();
				int i=0;

				while(sbyte1!=-1||sbyte2!=-1)
				{

					int ubyte1 = sbyte1 & 0xFF;
					int ubyte2 = sbyte2 & 0xFF;

					int result = (ubyte2<<8) + ubyte1;

					lightMaskLayer[i]=result;
					i++;
					sbyte1=lightMaskBin.read();
					sbyte2=lightMaskBin.read();
				}

				lightMaskBin.close();
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}*/
		}

	}



	//=========================================================================================================================
	public void saveDataToCache(int[] intArrayAllLayers, int[] tiles, byte[] pal)
	{//=========================================================================================================================

		//I should just save each layer as the MD5 in the cache folder
		//then set the appropriate md5 name in data

		for(int l=0;l<MapData.layers;l++)
		{
			if(MapData.isTileLayer(l))
			{
				int index = (widthTiles1X()*heightTiles1X()*l);
				int[] layer = new int[widthTiles1X()*heightTiles1X()];
				for(int i = 0;i<widthTiles1X()*heightTiles1X();i++)
				{
					layer[i] = intArrayAllLayers[index+i];
				}

				//save to cache folder as md5 name
				byte[] byteArray = Utils.getByteArrayFromIntArray(layer);
				String md5FileName = Utils.getByteArrayMD5Checksum(byteArray);
				Cache.saveByteArrayToCache(byteArray,md5FileName);

				//set layermd5 name to md5
				if(l==MapData.MAP_GROUND_LAYER){setGroundLayerMD5(md5FileName);}
				if(l==MapData.MAP_GROUND_DETAIL_LAYER){setGroundObjectsMD5(md5FileName);}
				if(l==MapData.MAP_GROUND_SHADOW_LAYER){setGroundShadowMD5(md5FileName);}
				if(l==MapData.MAP_OBJECT_LAYER){setObjectsMD5(md5FileName);}
				if(l==MapData.MAP_OBJECT_DETAIL_LAYER){setObjects2MD5(md5FileName);}
				if(l==MapData.MAP_OBJECT_SHADOW_LAYER){setObjectShadowMD5(md5FileName);}
				if(l==MapData.MAP_ABOVE_LAYER){setAboveMD5(md5FileName);}
				if(l==MapData.MAP_ABOVE_DETAIL_LAYER){setAbove2MD5(md5FileName);}
				if(l==MapData.MAP_SPRITE_SHADOW_LAYER){setSpriteShadowMD5(md5FileName);}
				if(l==MapData.MAP_SHADER_LAYER){setGroundShaderMD5(md5FileName);}
				if(l==MapData.MAP_LIGHT_MASK_LAYER){setLightMaskMD5(md5FileName);}
				if(l==MapData.MAP_CAMERA_BOUNDS_LAYER){setCameraBoundsMD5(md5FileName);}
				if(l==MapData.MAP_HIT_LAYER){setHitBoundsMD5(md5FileName);}

			}
		}
		//save tiles
		byte[] byteArray = Utils.getByteArrayFromIntArray(tiles);
		String md5FileName = Utils.getByteArrayMD5Checksum(byteArray);
		Cache.saveByteArrayToCache(byteArray,md5FileName);
		setTilesMD5(md5FileName);

		//save pal
		byteArray = pal;
		md5FileName = Utils.getByteArrayMD5Checksum(byteArray);
		Cache.saveByteArrayToCache(byteArray,md5FileName);
		setPaletteMD5(md5FileName);
	}











	//=========================================================================================================================
	public void unloadArea(String s)
	{//=========================================================================================================================

		//public Hashtable<String, Area> areaHashtable = new Hashtable<String, Area>();

		currentState.areaByNameHashtable.remove(s);
		currentState.areaByTYPEIDHashtable.remove(s);
		currentState.areaList.remove(s);

	}
	//=========================================================================================================================
	public void unloadLight(String s)
	{//=========================================================================================================================
		//public ArrayList<Light> lightList = new ArrayList<Light>();
		//public Hashtable<String,Light> lightHashtable = new Hashtable<String,Light>();


		for(int i=0;i<currentState.lightList.size();i++)
		{
			if(currentState.lightList.get(i).name().equals(s))
			{
				currentState.lightList.remove(i);
				i--;if(i<0)i=0;
			}
		}

		currentState.lightByNameHashtable.remove(s);

		for(int i=0;i<sortedLightsLayers.size();i++)
		{
			for(int j=0;j<sortedLightsLayers.get(i).size();j++)
			{
				if(sortedLightsLayers.get(i).get(j).name().equals(s))
				{
					sortedLightsLayers.get(i).remove(j);
					j--;if(j<0)j=0;
				}

			}
		}


	}
	//=========================================================================================================================
	public void unloadMapEntity(String s)
	{//=========================================================================================================================


		//public ArrayList<MapSprite> entityList = new ArrayList<MapSprite>();
		//public Hashtable<String, MapSprite> entityHashtable = new Hashtable<String, MapSprite>();

		for(int i=0;i<currentState.entityList.size();i++)
		{
			if(currentState.entityList.get(i).name().equals(s))
			{
				currentState.entityList.remove(i);
				i--;if(i<0)i=0;
			}
		}

		currentState.entityByNameHashtable.remove(s);


	}


	//=========================================================================================================================
	public void releaseAllTextures()
	{//=========================================================================================================================
		//go through all chunkTexture[] and release each texture in video memory and set to null
		//then reset all arrays

		//don't reset started threads!!!
		//don't reset these, they will keep going into the next map, which is still useful. they contruct the PNG from raw data which will be loaded later.
		//startedThreads = false;
		//startedHQ2XThreads = false;
		//startedLightThreads=false;


		chunkTexturesLoaded=0;

		//DO reset these, since we unload these textures.
		allChunkPNGsLoadedAsTextures = false;
		allHQ2XChunkPNGsLoadedAsTextures = false;

		//DO reset this, because we haven't necessarily loaded every light texture yet.
		allLightsLoadedAsTextures = false;




		//unload the utility layers
		hitLayer = null;
		cameraLayer = null;
		groundShaderLayer = null;
		lightMaskLayer = null;

		//we need to reload the utility layers
		utilityLayersLoaded = false;



		if(chunkTexture!=null)
		{
			for(int i=0;i<chunksWidth*chunksHeight*2;i++)
			{
				if(chunkTexture[i]!=null)
				{
					//fix for random white tile chunks! don't release the blank texture!
					if(chunkTexture[i]!=GLUtils.blankTexture)chunkTexture[i] = GLUtils.releaseTexture(chunkTexture[i]);

					chunkTexture[i]=null;
				}
			}
		}


		sortedLightsLayers.clear();


		/*if(chunkFileExists!=null)
		{
			for(int i=0;i<chunksWidth*chunksHeight*2;i++)chunkFileExists[i]=false;
		}

		if(HQ2XChunkFileExists!=null)
		{
			for(int i=0;i<chunksWidth*chunksHeight*2;i++)HQ2XChunkFileExists[i]=false;
		}*/

		if(usingHQ2XTexture!=null)
		{
			for(int i=0;i<chunksWidth*chunksHeight*2;i++)usingHQ2XTexture[i]=false;
		}

		tilesetIntArray = null;
		paletteRGBByteArray = null;

		//System.gc();


	}



	//=========================================================================================================================
	/**
	 * Returns the position of the upper left of the screen relative to the map, in HQ2X equivalent pixels.
	 * If the camera is left of the map, it is negative.
	*/
	public float mapCamX()
	{//=========================================================================================================================
		//centers the camera x and y on the screen and sets map cam to the upper left corner
		if(this==CurrentMap())return Cameraman().x()-(Engine().getWidthRelativeToZoom()/2.0f);// divided by 2.0f because it is getting from the center to the upper left
		else return 0-lastKnownScreenX;
	}

	//=========================================================================================================================
	/**
	 * Returns the position of the upper left of the screen relative to the map, in HQ2X equivalent pixels.
	 * If the camera is left of the map, it is negative.
	*/
	public float mapCamY()
	{//=========================================================================================================================
		if(this==CurrentMap())return Cameraman().y()-(Engine().getHeightRelativeToZoom()/2.0f);
		else return 0-lastKnownScreenY;
	}


	//public Tile getTileByName(String name)
	//{
		//return tileHashtable.get(name);
	//}


	//=========================================================================================================================
	public float getScreenX(float mapX, float width)
	{//=========================================================================================================================

		float zoom = Cameraman().getZoom();

		//flooring these fixes all the sprite jitter
		float left 	= (float) Math.floor(mapX);
		float right 	= (float) Math.floor(mapX + width);

		float mapCameraXPixelsHQ = mapCamX();
		float screenleft = mapCameraXPixelsHQ;
		float screenright = mapCameraXPixelsHQ+Engine().getWidthRelativeToZoom();

		float screenXPixelsHQ = left - screenleft;

		//if overlapping left side of screen
		if(right>=screenleft&&left<screenleft)screenXPixelsHQ = 0.0f - (screenleft-left);

		//if onscreen and not overlapping the left side
		if(left>=screenleft&&left<screenright)screenXPixelsHQ = left - screenleft;


		return screenXPixelsHQ * zoom;
	}










	//public Tile getTileByName(String name)
	//{
		//return tileHashtable.get(name);
	//}


	//=========================================================================================================================
	public float getScreenY(float mapY, float height)
	{//=========================================================================================================================

		float zoom = Cameraman().getZoom();

		//flooring these fixes all the sprite jitter
		float top 	= (float) Math.floor(mapY);
		float bottom 	= (float) Math.floor(mapY + height);

		float mapCameraYPixelsHQ = mapCamY();
		float screentop = mapCameraYPixelsHQ;
		float screenbottom = mapCameraYPixelsHQ+Engine().getHeightRelativeToZoom();

		float screenYPixelsHQ = top-screentop;

		//if overlapping top side of screen
		if(bottom>=screentop&&top<screentop)screenYPixelsHQ = 0.0f - (screentop-top);

		//if onscreen and not overlapping the top side
		if(top>=screentop&&top<screenbottom)screenYPixelsHQ = top-screentop;


		return screenYPixelsHQ * zoom;
	}










	public float screenX()
	{
		if(this==CurrentMap())return 0-mapCamX();
		else return lastKnownScreenX;

	}

	public float screenY()
	{
		if(this==CurrentMap())return 0-mapCamY();
		else return lastKnownScreenY;
	}


	//=========================================================================================================================
	public void updateLastKnownScreenXYBasedOnCamera()
	{//=========================================================================================================================

		//set map screen x and y

		//if map_cam_x is -400, map_screen_x should be 400

		lastKnownScreenX = 0-mapCamX();
		lastKnownScreenY = 0-mapCamY();

		//TODO: can't get rid of these with functions because drawing the last map depends on them not being updated, and instead drawn with an offset.
		//figure out a way to fix this

	}



//
//	//=========================================================================================================================
//	/**
//	 *
//	 * checks both hit layer and any mapsprites that aren't characters
//	 *
//	 */
//	public boolean checkHitLayerAndHitSpritesXY(float x, float y)
//	{//=========================================================================================================================
//
//		boolean hit = getHitLayerValueAtXYPixels(x,y);
//
//		if(hit==false)
//		{
//			//go through all mapsprites, check if map characters
//			for(int i=0;i<activeEntityList.size();i++)
//			{
//				Entity m = activeEntityList.get(i);
//				if(m.nonWalkable()==true
//						&&x<m.right()
//						&&x>m.left()
//						&&y<m.bottom()
//						&&y>m.top()
//				)return true;
//
//			}
//		}
//		return hit;
//
//	}

	//=========================================================================================================================
	public boolean getHitLayerValueAtXYTile1X(int xTile1X, int yTile1X)
	{//=========================================================================================================================
		return getHitLayerValueAtXYPixels(xTile1X*8*2,yTile1X*8*2);
	}

	//=========================================================================================================================
	public boolean getHitLayerValueAtXYPixels(float mapXPixelsHQ, float mapYPixelsHQ)
	{//=========================================================================================================================

		if(Engine().hitLayerEnabled==false)return false;

		if(utilityLayersLoaded==false)return true;

		//return "hit wall" if value is outside of the map
		if(mapYPixelsHQ>=heightPixelsHQ()||mapXPixelsHQ>=widthPixelsHQ()||mapYPixelsHQ<0||mapXPixelsHQ<0)
		return true;


		int tilex = (((int)Math.floor(mapXPixelsHQ))/8)/2;
		int tiley = (((int)Math.floor(mapYPixelsHQ))/8)/2; // divided by 2 because map is scale 2x. map_x and map_y are 2x as well, giving "subpixel" precision for maps i guess
		//NOTE: will have to float all the tile xy values for movement and placement if i keep it this way

		int tilew = (widthPixelsHQ()/2)/8;//also divided by 2, see above
		int index = (tiley*tilew)+tilex;


		if(hitLayer[index]==0)return false;
		return true;


	}

	//=========================================================================================================================
	public int getCameraBoundsFXLayerAtXYTile1X(int xTile1X, int yTile1X)
	{//=========================================================================================================================
		return getCameraBoundsFXLayerAtXYPixels(xTile1X*8*2,yTile1X*8*2);
	}

	//=========================================================================================================================
	public int getCameraBoundsFXLayerAtXYPixels(float mapXPixelsHQ, float mapYPixelsHQ)
	{//=========================================================================================================================

		if(utilityLayersLoaded==false)return 0;

		//return 0 if value is outside of the map
		if(mapYPixelsHQ>=heightPixelsHQ()||mapXPixelsHQ>=widthPixelsHQ()||mapYPixelsHQ<0||mapXPixelsHQ<0)
		return 0;


		int tilex = ((((int)Math.floor(mapXPixelsHQ)))/8)/2;
		int tiley = (((int)Math.floor(mapYPixelsHQ))/8)/2;

		int tilew = (widthPixelsHQ()/2)/8;
		int index = (tiley*tilew)+tilex;

		return cameraLayer[index];


	}


	//=========================================================================================================================
	public boolean isXYWithinScreenByAmt(float x,float y, int amt)
	{//=========================================================================================================================

		float displayWidth = Engine().getWidthRelativeToZoom();
		float displayHeight = Engine().getHeightRelativeToZoom();

		if(x==-1)x=(mapCamX())+displayWidth/2;
		if(y==-1)y=(mapCamY())+displayHeight/2;

		if(
				(x+amt>=mapCamX()||x>=mapCamX())
				&&
				(x-amt<=mapCamX()+displayWidth||x<=mapCamX()+displayWidth)
				&&
				(y+amt>=mapCamY()||y>=mapCamY())
				&&
				(y-amt<=mapCamY()+displayHeight||y<=mapCamY()+displayHeight)
		)
		return true;

		return false;

	}


	//=========================================================================================================================
	public boolean isXYXYWithinScreenByAmount(float x,float y, float x2, float y2, float amt)
	{//=========================================================================================================================

		float displayWidth = Engine().getWidthRelativeToZoom();
		float displayHeight = Engine().getHeightRelativeToZoom();

		if(x==-1)x=(mapCamX())+displayWidth/2;
		if(y==-1)y=(mapCamY())+displayHeight/2;
		if(x2==-1)x2=(mapCamX())+displayWidth/2;
		if(y2==-1)y2=(mapCamY())+displayHeight/2;

		if(
			(
				(mapCamX()>=x&&mapCamX()<=x2)||// left side of screen is in range
				(mapCamX()+displayWidth>=x&&mapCamX()+displayWidth<=x2)|| //right side of screen is in range
				(x>=mapCamX()&&x<=mapCamX()+displayWidth)||//left boundary of range is within screen
				(x2>=mapCamX()&&x2<=mapCamX()+displayWidth)//right boundary of range is within screen
			)
			&&
			(
				(mapCamY()>=y&&mapCamY()<=y2)||// top of screen is in range
				(mapCamY()+displayHeight>=y&&mapCamY()+displayHeight<=y2)|| //bottom of screen is within range
				(y>=mapCamY()&&y<=mapCamY()+displayHeight)||//top boundary of range is within screen
				(y2>=mapCamY()&&y2<=mapCamY()+displayHeight)//bottom boundary of range is within screen

			)
		)return true;

		return false;
	}

	//=========================================================================================================================
	public boolean isXYWithinScreen(float x,float y)
	{//=========================================================================================================================

		return isXYWithinScreenByAmt(x, y, 0);

	}




//
//	//=========================================================================================================================
//	public void setTextureMD5Names(String groundLayerMD5,String groundObjectsMD5,String groundShadowMD5,String objectsMD5,String objects2MD5,String objectShadowMD5,String aboveMD5,String above2MD5,String spriteShadowMD5,String groundShaderMD5,String cameraBoundsMD5,String hitBoundsMD5,String lightMaskMD5,String paletteMD5,String tilesMD5)
//	{//=========================================================================================================================
//
//
//		//name = object.name;
//		this.groundLayerMD5 = groundLayerMD5;
//		this.groundObjectsMD5 = groundObjectsMD5;
//		this.groundShadowMD5 = groundShadowMD5;
//		this.objectsMD5 = objectsMD5;
//		this.objects2MD5 = objects2MD5;
//		this.objectShadowMD5 = objectShadowMD5;
//		this.aboveMD5 = aboveMD5;
//		this.above2MD5 = above2MD5;
//		this.spriteShadowMD5 = spriteShadowMD5;
//		this.groundShaderMD5 = groundShaderMD5;
//		this.cameraBoundsMD5 = cameraBoundsMD5;
//		this.hitBoundsMD5 = hitBoundsMD5;
//		this.lightMaskMD5 = lightMaskMD5;
//		this.paletteMD5 = paletteMD5;
//		this.tilesMD5 = tilesMD5;
//
//	}



	//=========================================================================================================================
	public synchronized Texture getChunkTexture(int index)
	{//=========================================================================================================================
		return chunkTexture[index];

	}
	//=========================================================================================================================
	public synchronized void setChunkTexture(int index, Texture t)
	{//=========================================================================================================================
		chunkTexture[index] = t;
	}

	//=========================================================================================================================
	public synchronized void releaseChunkTexture(int index)
	{//=========================================================================================================================
		chunkTexture[index] = GLUtils.releaseTexture(chunkTexture[index]);
	}

	//=========================================================================================================================
	public synchronized boolean getChunkPNGFileExists(int index)
	{//=========================================================================================================================
		return chunkPNGFileExists[index];

	}
	//=========================================================================================================================
	public synchronized void setChunkPNGFileExists_S(int index, boolean done)
	{//=========================================================================================================================
		chunkPNGFileExists[index] = done;
	}

	//=========================================================================================================================
	public synchronized boolean getHQ2XChunkPNGFileExists(int index)
	{//=========================================================================================================================
		return hq2xChunkPNGFileExists[index];

	}
	//=========================================================================================================================
	public synchronized void setHQ2XChunkFileExists_S(int index, boolean done)
	{//=========================================================================================================================
		hq2xChunkPNGFileExists[index] = done;
	}

	//=========================================================================================================================
	public synchronized void incrementChunkTexturesLoaded()
	{//=========================================================================================================================
		chunkTexturesLoaded++;
	}
	//=========================================================================================================================
	public synchronized void decrementChunkTexturesLoaded()
	{//=========================================================================================================================
		chunkTexturesLoaded--;
	}
	//=========================================================================================================================
	public boolean loadChunkTexturesFromCachePNGs()
	{//=========================================================================================================================

		boolean tempAllChunksLoaded = true;

		//for each texture that needs to be on-screen, spiraling clockwise from CAMERA TARGET POSITION

		//get chunkX and Y based on player location

		int startChunkX = (int)Cameraman().x()/chunkSizePixelsHQ2X;
		int startChunkY = (int)Cameraman().y()/chunkSizePixelsHQ2X;
		if(startChunkX<0 || startChunkX >= chunksWidth)startChunkX=0;
		if(startChunkY<0 || startChunkY >= chunksHeight)startChunkY=0;
		int chunkX=startChunkX;
		int chunkY=startChunkY;
		int dir_UP=0;
		int dir_DOWN=1;
		int dir_LEFT=2;
		int dir_RIGHT=3;
		int dir=dir_RIGHT;
		int movementsUntilChangeDirection=1;
		int movementsThisDirection=0;
		int directionChangesUntilIncreaseMovements=0;//when this is equal to 2, increase movementsUntilChangeDirection




		int sw = (int)(Engine().getWidthRelativeToZoom());
		int sh = (int)(Engine().getHeightRelativeToZoom());

		int camX = ((int) Math.floor(((mapCamX()) )));
		int camY = ((int) Math.floor(((mapCamY()) )));

		while(movementsUntilChangeDirection<chunksWidth*2||movementsUntilChangeDirection<chunksHeight*2)
		{


			if(
					MapManager.loadTexturesOnDemand==false
					||
					(
							((chunkX+1)*chunkSizePixelsHQ2X)-1>=camX&&
							chunkX*chunkSizePixelsHQ2X<camX+(sw)&&
							((chunkY+1)*chunkSizePixelsHQ2X)-1>=camY&&
							chunkY*chunkSizePixelsHQ2X<camY+(sh)
					)
			)
			{
				if(chunkX>=0&&chunkX<chunksWidth&&chunkY>=0&&chunkY<chunksHeight)
				{

					for(int chunkLayer=0;chunkLayer<2;chunkLayer++)
					{

						int chunkIndex = (chunksWidth*chunksHeight*chunkLayer)+((chunkY*chunksWidth)+chunkX);

						//check if tile has texture already in gpu
						if(getChunkTexture(chunkIndex)==null)
						{
							tempAllChunksLoaded = false;

							//if it doesnt have a texture, need to load the texture
							//check for existence of texture in groundMD5

							if(getChunkPNGFileExists(chunkIndex)==true || (MapManager.generateHQ2XChunks==true&&getHQ2XChunkPNGFileExists(chunkIndex)==true))
							{

								File textureFile = null;

								if(MapManager.generateHQ2XChunks==true&&getHQ2XChunkPNGFileExists(chunkIndex)==true)
								{
									textureFile = new File(Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+"2x"+Cache.slash+chunkIndex);
									usingHQ2XTexture[chunkIndex]=true;
								}
								else
								{
									textureFile = new File(Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+chunkIndex);
								}

								if(textureFile.exists()==false)
								{
									new Exception().printStackTrace();
									continue;
								}

								//if it exists:

								//if it is 0 bytes, just point texture to blank tile

								if(textureFile.length()<1)
								{
									setChunkTexture(chunkIndex,GLUtils.blankTexture);
								}
								else
								{
									//************
									//there is no reason to do this, single threaded deferred loading one chunk per frame is fast enough
									//************
									//DONTNEEDTODO: create new thread for loading textures
									//however, this isn't possible with lwjgl without some hacks, so what CAN we do?
									//let's see why it gives the error it does...

									setChunkTexture(chunkIndex,GLUtils.loadTexture(textureFile.getAbsolutePath()));
								}

								incrementChunkTexturesLoaded();

							}

						}
					}

					if(tempAllChunksLoaded==false)break;

				}
			}
			else
			{
				//unload texture
				if(chunkX>=0&&chunkX<chunksWidth&&chunkY>=0&&chunkY<chunksHeight)
				{

					for(int chunkLayer=0;chunkLayer<2;chunkLayer++)
					{

						int chunkIndex = (chunksWidth*chunksHeight*chunkLayer)+((chunkY*chunksWidth)+chunkX);

						if(getChunkTexture(chunkIndex)!=null&&getChunkTexture(chunkIndex)!=GLUtils.blankTexture)//fix WHITE TILE bug?
						{


							releaseChunkTexture(chunkIndex);


							decrementChunkTexturesLoaded();
						}

					}
				}
			}

			if(movementsThisDirection<movementsUntilChangeDirection)
			{
				if(dir==dir_RIGHT)chunkX++;
				else if(dir==dir_LEFT)chunkX--;
				else if(dir==dir_DOWN)chunkY++;
				else if(dir==dir_UP)chunkY--;

				movementsThisDirection++;
			}
			else
			{
				movementsThisDirection=0;

				if(dir==dir_RIGHT)dir=dir_DOWN;
				else if(dir==dir_LEFT)dir=dir_UP;
				else if(dir==dir_DOWN)dir=dir_LEFT;
				else if(dir==dir_UP)dir=dir_RIGHT;

				directionChangesUntilIncreaseMovements++;

				if(directionChangesUntilIncreaseMovements>=2)
				{
					directionChangesUntilIncreaseMovements=0;
					movementsUntilChangeDirection++;
				}

				if(dir==dir_RIGHT)chunkX++;
				else if(dir==dir_LEFT)chunkX--;
				else if(dir==dir_DOWN)chunkY++;
				else if(dir==dir_UP)chunkY--;

				movementsThisDirection++;
			}



		}

		return false;
		//return tempAllChunksLoaded;

	}


	//=========================================================================================================================
	public boolean loadLightTexturesFromCachePNGs()
	{//=========================================================================================================================

		boolean tempAllLightTexturesLoaded = true;



		for(int i=0; i<currentState.lightList.size();i++)
		{
			//if(lightList.get(i).mapAsset==this)
			{
				Light l = currentState.lightList.get(i);

					//check if tile has texture already in gpu
					if(l.texture==null)
					{

						//see if it's in the hashmap loaded already from a different map
						l.texture = MapManager().lightTextureHashMap.get(l.getFileName());



						if(l.texture==null)
						{
							tempAllLightTexturesLoaded = false;

							//if it doesnt have a texture, need to load the texture
							//check for existence of texture

							//check our PNG file hashmap which was filled when we started threads for missing textures.
							if(l.getLightTexturePNGFileExists_S()==true)
							{

								//floatcheck it exists, this should never be false.
								File textureFile = new File(Cache.cacheDir+"l"+Cache.slash+l.getFileName());
								if(textureFile.exists()==false)
								{
									new Exception().printStackTrace();
									continue;
								}


								Texture t = GLUtils.loadTexture(Cache.cacheDir+"l"+Cache.slash+l.getFileName());
								MapManager().lightTextureHashMap.put(l.getFileName(), t);

								l.texture = t;
							}
						}

					}
			}

			if(tempAllLightTexturesLoaded==false)break; //only load one per frame



		}

		return tempAllLightTexturesLoaded;

	}

	//=========================================================================================================================
	public boolean loadHQ2XTexturesFromCachePNGs()
	{//=========================================================================================================================

		//run through all chunks
		//this can be linear (not spiral) because this is only called when they are being created by threads (in a spiral) so it will update in a spiral anyway.
		//it's actually probably slightly less efficient to use a spiral since it has to cover a lot of blank space outside the map

		boolean tempAllHQ2XChunksLoaded = true;

		for(int chunkY=0;chunkY<chunksHeight;chunkY++)
		for(int chunkX=0;chunkX<chunksWidth;chunkX++)
		for(int chunkLayer=0;chunkLayer<2;chunkLayer++)
		{
			int chunkIndex = (chunksWidth*chunksHeight*chunkLayer)+((chunkY*chunksWidth)+chunkX);

			if(usingHQ2XTexture[chunkIndex]==false)
			{
				tempAllHQ2XChunksLoaded = false;

				if(getHQ2XChunkPNGFileExists(chunkIndex)==true)
				{



					File textureFile = null;

					if(getHQ2XChunkPNGFileExists(chunkIndex)==true)
					{
						textureFile = new File(Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+"2x"+Cache.slash+chunkIndex);
					}

					if(textureFile.exists()==false)
					{
						new Exception().printStackTrace();
						continue;
					}

					Texture t = getChunkTexture(chunkIndex);

					if(t!=null)
					{
						//remove previous texture from GPU.
						if(t!=GLUtils.blankTexture)t = GLUtils.releaseTexture(t);
						setChunkTexture(chunkIndex, null);
					}

					//set to new texture

					if(textureFile.length()<1)
					{
						setChunkTexture(chunkIndex,GLUtils.blankTexture);
					}
					else
					{
						//DONE: create new thread: load it as a texture, set TileTexture to this texture, delete ByteBuffer
						setChunkTexture(chunkIndex,GLUtils.loadTexture(textureFile.getAbsolutePath()));
					}

					usingHQ2XTexture[chunkIndex]=true;
				}
			}
		}

		return tempAllHQ2XChunksLoaded;



	}




	//=========================================================================================================================
	public synchronized void incrementChunkPNGThreadsCreated()
	{//=========================================================================================================================
		chunkPNGThreadsCreated++;
		if(chunkPNGThreadsCreated>maxChunkPNGThreadsCreated)maxChunkPNGThreadsCreated=chunkPNGThreadsCreated;
	}

	//=========================================================================================================================
	public synchronized void decrementChunkPNGThreadsCreated_S()
	{//=========================================================================================================================
		chunkPNGThreadsCreated--;
	}

	//=========================================================================================================================
	public void startThreadsForMissingChunkPNGs()
	{//=========================================================================================================================



		//does cache/groundMD5/ exist?
		//if not, make it.
		Utils.makeDir(Cache.cacheDir+"_"+groundLayerMD5());
		Utils.makeDir(Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+"1x_padded"+Cache.slash);
		Utils.makeDir(Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+"2x"+Cache.slash);


		if(MapManager.useThreads==true&&generatePNGExecutorService==null)generatePNGExecutorService = Executors.newFixedThreadPool(3);
		//if(MapManager.useThreads==true)generatePNGExecutorService = Executors.newFixedThreadPool(3);


		//for each texture that needs to be on-screen, spiraling clockwise from CAMERA TARGET POSITION

		//get chunkX and Y based on player location

		int startChunkX = (int)Cameraman().x()/chunkSizePixelsHQ2X;
		int startChunkY = (int)Cameraman().y()/chunkSizePixelsHQ2X;

		if(startChunkX<0 || startChunkX >= chunksWidth)startChunkX=0;
		if(startChunkY<0 || startChunkY >= chunksHeight)startChunkY=0;

		int chunkX=startChunkX;
		int chunkY=startChunkY;

		int dir_UP=0;
		int dir_DOWN=1;
		int dir_LEFT=2;
		int dir_RIGHT=3;

		int dir=dir_RIGHT;


		int movementsUntilChangeDirection=1;
		int movementsThisDirection=0;
		int directionChangesUntilIncreaseMovements=0;//when this is equal to 2, increase movementsUntilChangeDirection

		while(movementsUntilChangeDirection<chunksWidth*2||movementsUntilChangeDirection<chunksHeight*2)
		{
			if(chunkX>=0&&chunkX<chunksWidth&&chunkY>=0&&chunkY<chunksHeight)
			{
				for(int chunkLayer=0;chunkLayer<2;chunkLayer++)
				{
					int chunkIndex = (chunksWidth*chunksHeight*chunkLayer)+((chunkY*chunksWidth)+chunkX);


					//check for existence of texture in groundMD5
					File textureFile = new File(Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+chunkIndex);
					File hq2xTextureFile = new File(Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+"2x"+Cache.slash+chunkIndex);


					if(hq2xTextureFile.exists())
					{
						setHQ2XChunkFileExists_S(chunkIndex,true);
					}

					if(textureFile.exists())
					{
						setChunkPNGFileExists_S(chunkIndex,true);
					}
					else
					{
						//if it doesnt exist
						//load tileset and palette into memory if it is not already loaded into mem from another tile

						if(tilesetIntArray==null)
						{
							tilesetIntArray = Cache.loadIntFileFromCacheOrDownloadIfNotExist(""+tilesMD5());
						}

						if(paletteRGBByteArray==null)
						{
							paletteRGBByteArray = Cache.loadByteFileFromCacheOrDownloadIfNotExist(""+paletteMD5());
						}


						//create new thread:
						final int threadChunkLayer = chunkLayer;
						final int threadChunkX = chunkX;
						final int threadChunkY = chunkY;
						final int threadChunkIndex = chunkIndex;
						final int[] threadTilesetIntArray = tilesetIntArray;//we send in a final pointer to this because it is set to null when the map is unloaded, but the threads may still be creating map tile pngs and will release this pointer when they die.
						final byte[] threadPaletteRGBByteArray = paletteRGBByteArray;


						if(MapManager.useThreads==true)
						{

							incrementChunkPNGThreadsCreated();

							generatePNGExecutorService.execute(

							new Runnable()
							{

								public void run()
								{

									try{Thread.currentThread().setName("MapAsset_startThreadsForMissingChunkPNGs");}catch(SecurityException e){e.printStackTrace();}


									createChunkTexturePNG_S(threadChunkLayer, threadChunkX, threadChunkY, threadChunkIndex, threadTilesetIntArray, threadPaletteRGBByteArray);
									setChunkPNGFileExists_S(threadChunkIndex,true);
									decrementChunkPNGThreadsCreated_S();

								}
							}


							);
						}
						else
						{
							//do it linearly, waiting for all chunks to finish before continuing
							createChunkTexturePNG_S(threadChunkLayer, threadChunkX, threadChunkY, threadChunkIndex, threadTilesetIntArray, threadPaletteRGBByteArray);
							setChunkPNGFileExists_S(threadChunkIndex,true);

						}


					}
				}


			}

			if(movementsThisDirection<movementsUntilChangeDirection)
			{
				if(dir==dir_RIGHT)chunkX++;
				else if(dir==dir_LEFT)chunkX--;
				else if(dir==dir_DOWN)chunkY++;
				else if(dir==dir_UP)chunkY--;

				movementsThisDirection++;
			}
			else
			{
				movementsThisDirection=0;

				if(dir==dir_RIGHT)dir=dir_DOWN;
				else if(dir==dir_LEFT)dir=dir_UP;
				else if(dir==dir_DOWN)dir=dir_LEFT;
				else if(dir==dir_UP)dir=dir_RIGHT;

				directionChangesUntilIncreaseMovements++;

				if(directionChangesUntilIncreaseMovements>=2)
				{
					directionChangesUntilIncreaseMovements=0;
					movementsUntilChangeDirection++;
				}

				if(dir==dir_RIGHT)chunkX++;
				else if(dir==dir_LEFT)chunkX--;
				else if(dir==dir_DOWN)chunkY++;
				else if(dir==dir_UP)chunkY--;

				movementsThisDirection++;
			}
		}


		//unload tileset and palette if they were loaded

		tilesetIntArray=null;
		paletteRGBByteArray=null;


		//if(MapManager.useThreads==true)generatePNGExecutorService.shutdown();


	}

	//=========================================================================================================================
	public synchronized void incrementLightPNGThreadsCreated()
	{//=========================================================================================================================
		lightPNGThreadsCreated++;
		if(lightPNGThreadsCreated>maxLightPNGThreadsCreated)maxLightPNGThreadsCreated=lightPNGThreadsCreated;
	}

	//=========================================================================================================================
	public synchronized void decrementLightPNGThreadsCreated_S()
	{//=========================================================================================================================
		lightPNGThreadsCreated--;
	}

	//=========================================================================================================================
	public void startThreadsForMissingLightPNGs()
	{//=========================================================================================================================



		//does cache/groundMD5/ exist?
		//if not, make it.
		Utils.makeDir(Cache.cacheDir+"l"+Cache.slash);



		//if(MapManager.useThreads==true&&generatePNGExecutorService==null)generatePNGExecutorService = Executors.newFixedThreadPool(3);
		if(MapManager.useThreads==true&&generateLightPNGExecutorService==null)generateLightPNGExecutorService = Executors.newFixedThreadPool(3);


		//go through all the lights in lightList
		//for all the lights see if there is a texture generated for it, stored in the light object itself
		//if there isn't, generate the light as a bufferedImage, create a texture for it, and set it in the light object

		for(int i=0; i<currentState.lightList.size();i++)
		{
			//if(lightList.get(i).mapAsset==this)
			{
				Light l = currentState.lightList.get(i);


				//don't create a thread to generate a texture that is already being made.
				//this prevents collisions where a thread is overwriting a png that already exists while it is being loaded as a texture
				boolean c = false;
				for(int j=0;j<i;j++)
				{
					if(currentState.lightList.get(j).getFileName().equals(l.getFileName()))
					{
						c=true;
						break;
					}
				}
				if(c)continue;


				if(l.getLightTexturePNGFileExists_S()==false)
				{

					//check for existence of texture in cache folder
					File textureFile = new File(Cache.cacheDir+"l"+Cache.slash+l.getFileName());
					if(textureFile.exists())
					{
						l.setLightTexturePNGFileExists_S(true);
					}
					else
					{
						if(MapManager.useThreads==true)
						{

							final Light threadLight = currentState.lightList.get(i);
							final String threadLightFilename = threadLight.getFileName();

							incrementLightPNGThreadsCreated();

							generateLightPNGExecutorService.execute(

							new Runnable()
							{

								public void run()
								{

									try{Thread.currentThread().setName("MapAsset_startThreadsForMissingLightPNGs");}catch(SecurityException e){e.printStackTrace();}

									threadLight.createLightTexturePNG(Cache.cacheDir+"l"+Cache.slash+threadLightFilename);
									threadLight.setLightTexturePNGFileExists_S(true);

									decrementLightPNGThreadsCreated_S();

								}
							}


							);
						}
						else
						{
							//do it linearly, waiting for all to finish before continuing
							l.createLightTexturePNG(Cache.cacheDir+"l"+Cache.slash+l.getFileName());

							l.setLightTexturePNGFileExists_S(true);

						}
					}
				}
			}

		}

		//if(MapManager.useThreads==true)generateLightPNGExecutorService.shutdown();


	}


	//=========================================================================================================================
	public synchronized void incrementHQ2XChunkPNGThreadsCreated()
	{//=========================================================================================================================
		hq2xChunkPNGThreadsCreated++;
		if(hq2xChunkPNGThreadsCreated>maxHq2xChunkPNGThreadsCreated)maxHq2xChunkPNGThreadsCreated=hq2xChunkPNGThreadsCreated;
	}

	//=========================================================================================================================
	public synchronized void decrementHQ2XChunkPNGThreadsCreated()
	{//=========================================================================================================================
		hq2xChunkPNGThreadsCreated--;
	}

	//=========================================================================================================================
	public void startThreadsForMissingHQ2XChunkPNGs()
	{//=========================================================================================================================

		//for each chunk, starting at player position

		//does cache/groundMD5/ exist?
		//if not, make it.
		Utils.makeDir(Cache.cacheDir+"_"+groundLayerMD5());
		Utils.makeDir(Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+"1x_padded"+Cache.slash);
		Utils.makeDir(Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+"2x"+Cache.slash);


		if(MapManager.useThreads==true&&generatePNGExecutorService==null)generatePNGExecutorService = Executors.newFixedThreadPool(3);
		//if(MapManager.useThreads==true)generateHQ2XPNGExecutorService = Executors.newFixedThreadPool(3);


		int startChunkX = (int)Cameraman().x()/chunkSizePixelsHQ2X;
		int startChunkY = (int)Cameraman().y()/chunkSizePixelsHQ2X;

		if(startChunkX<0 || startChunkX >= chunksWidth)startChunkX=0;
		if(startChunkY<0 || startChunkY >= chunksHeight)startChunkY=0;

		int chunkX=startChunkX;
		int chunkY=startChunkY;

		int dir_UP=0;
		int dir_DOWN=1;
		int dir_LEFT=2;
		int dir_RIGHT=3;

		int dir=dir_RIGHT;


		int movementsUntilChangeDirection=1;
		int movementsThisDirection=0;
		int directionChangesUntilIncreaseMovements=0;//when this is equal to 2, increase movementsUntilChangeDirection


		while(movementsUntilChangeDirection<chunksWidth*2||movementsUntilChangeDirection<chunksHeight*2)
		{
			if(chunkX>=0&&chunkX<chunksWidth&&chunkY>=0&&chunkY<chunksHeight)
			{

				//check hq2x exists only from bottom layer, since we generate both at the same time.
				int chunkLayer = 0;

				int chunkIndex = (chunksWidth*chunksHeight*chunkLayer)+((chunkY*chunksWidth)+chunkX);
				int chunkIndexOverLayer = (chunksWidth*chunksHeight*1)+((chunkY*chunksWidth)+chunkX);

				//check for existence of texture in groundMD5
				File hq2xTextureFile = new File(Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+"2x"+Cache.slash+chunkIndex);

				if(hq2xTextureFile.exists())
				{
					setHQ2XChunkFileExists_S(chunkIndex,true);
					setHQ2XChunkFileExists_S(chunkIndexOverLayer,true);
				}
				else
				{
					//create new thread:
					final int threadChunkX = chunkX;
					final int threadChunkY = chunkY;
					final int threadChunkIndex = chunkIndex;
					final int threadChunkIndexOverLayer = chunkIndexOverLayer;

					if(MapManager.useThreads==true)
					{
						incrementHQ2XChunkPNGThreadsCreated();

						generatePNGExecutorService.execute(

						new Runnable()
						{

							public void run()
							{

								try{Thread.currentThread().setName("MapAsset_startThreadsForMissingHQ2XChunkPNGs");}catch(SecurityException e){e.printStackTrace();}


								createHQ2XTexturePNG_THREAD(threadChunkX, threadChunkY);
								setHQ2XChunkFileExists_S(threadChunkIndex,true);
								setHQ2XChunkFileExists_S(threadChunkIndexOverLayer,true);

								decrementHQ2XChunkPNGThreadsCreated();

							}
						}

						);
					}
					else
					{
						//do it linearly, waiting for all chunks to finish before continuing
						createHQ2XTexturePNG_THREAD(threadChunkX, threadChunkY);
						setHQ2XChunkFileExists_S(threadChunkIndex,true);
						setHQ2XChunkFileExists_S(threadChunkIndexOverLayer,true);

					}
				}
			}


			if(movementsThisDirection<movementsUntilChangeDirection)
			{
				if(dir==dir_RIGHT)chunkX++;
				else if(dir==dir_LEFT)chunkX--;
				else if(dir==dir_DOWN)chunkY++;
				else if(dir==dir_UP)chunkY--;

				movementsThisDirection++;
			}
			else
			{
				movementsThisDirection=0;

				if(dir==dir_RIGHT)dir=dir_DOWN;
				else if(dir==dir_LEFT)dir=dir_UP;
				else if(dir==dir_DOWN)dir=dir_LEFT;
				else if(dir==dir_UP)dir=dir_RIGHT;


				directionChangesUntilIncreaseMovements++;

				if(directionChangesUntilIncreaseMovements>=2)
				{
					directionChangesUntilIncreaseMovements=0;
					movementsUntilChangeDirection++;
				}


				if(dir==dir_RIGHT)chunkX++;
				else if(dir==dir_LEFT)chunkX--;
				else if(dir==dir_DOWN)chunkY++;
				else if(dir==dir_UP)chunkY--;

				movementsThisDirection++;

			}

		}


		//if(MapManager.useThreads==true)generateHQ2XPNGExecutorService.shutdown();

	}

	//=========================================================================================================================
	public void createChunkTexturePNG_S(int chunkLayer, int chunkX, int chunkY, int chunkIndex, int[] tilesetIntArray, byte[] paletteRGBByteArray)
	{//=========================================================================================================================

		//Thread.yield();

		//create chunkImage
		BufferedImage chunkImage = new BufferedImage(chunkSizeTiles1X*8,chunkSizeTiles1X*8,BufferedImage.TYPE_INT_ARGB);
		BufferedImage chunkImageBorder = new BufferedImage(chunkSizeTiles1X*8+2,chunkSizeTiles1X*8+2,BufferedImage.TYPE_INT_ARGB);


		//***************************************
		//if i don't init the graphics, the buffered image output has a random alpha jitter for a reason i can't figure out...
		//it actually looks nice, but i wanted to figure out what the heck was doing it!
		//NOPE this isn't why!
		//***************************************

		/*Graphics G = chunkImage.getGraphics();
		G.setColor(new Color(0,0,0,0));
		G.fillRect(0, 0, chunkImage.getWidth(), chunkImage.getHeight());
		G.dispose();
		G = chunkImageBorder.getGraphics();
		G.setColor(new Color(0,0,0,0));
		G.fillRect(0, 0, chunkImageBorder.getWidth(), chunkImageBorder.getHeight());
		G.dispose();*/

		int layerChunkBuffer[] = new int[(chunkSizeTiles1X+2)*(chunkSizeTiles1X+2)];

		String layerFileName = "";

		boolean blank = true;

		if(chunkLayer==0)
		{

			blank=false;

			for(int l=0;l<6;l++)
			{
				boolean shadowLayer = false;

				if(l==0){layerFileName = groundLayerMD5();}
				if(l==1){layerFileName = groundObjectsMD5();}
				if(l==2){layerFileName = groundShadowMD5();shadowLayer=true;}
				if(l==3){layerFileName = objectsMD5();}
				if(l==4){layerFileName = objects2MD5();}
				if(l==5){layerFileName = objectShadowMD5();shadowLayer=true;}

				drawTileLayerIntoBufferedImage(layerFileName, chunkImage, chunkImageBorder, chunkX, chunkY, layerChunkBuffer, shadowLayer,tilesetIntArray,paletteRGBByteArray);
			}
		}
		else
		if(chunkLayer==1)
		{


			for(int l=0;l<3;l++)
			{
				boolean shadowLayer = false;

				if(l==0){layerFileName = aboveMD5();}
				if(l==1){layerFileName = above2MD5();}
				if(l==2){layerFileName = spriteShadowMD5();shadowLayer=true;}

				boolean changedImage = drawTileLayerIntoBufferedImage(layerFileName, chunkImage, chunkImageBorder, chunkX, chunkY, layerChunkBuffer, shadowLayer,tilesetIntArray,paletteRGBByteArray);
				if(changedImage==true)blank=false;
			}
		}


		if(blank==true)
		{


			//log.debug("Made blank file: "+chunkLayer+"_"+chunkIndex);

			//save 0 byte placeholder, this will always load blank texture
			File f = new File(""+Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+chunkIndex);
			File f2 = new File(""+Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+"1x_padded"+Cache.slash+chunkIndex);

			try
			{
				f.createNewFile();
				f2.createNewFile();
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}

		}
		else
		{
			//save this as png in folder groundMD5/0_0_0
			Utils.saveImage(""+Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+chunkIndex, chunkImage);
			Utils.saveImage(""+Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+"1x_padded"+Cache.slash+chunkIndex, chunkImageBorder);
		}
	}



	//=========================================================================================================================
	/**
	 * returns false if no image is needed
	 */
	public boolean drawTileLayerIntoBufferedImage(String layerFileName, BufferedImage chunkImage, BufferedImage chunkImageBorder, int chunkX, int chunkY, int layerChunkBuffer[], boolean shadowLayer, int[] tilesetIntArray, byte[] paletteRGBByteArray)
	{//=========================================================================================================================


		boolean isBlank = true;

		//open layer as file, load chunk into memory, with 1 tile border, filling with 0 if it is on the map edge
		RandomAccessFile raf = null;
		try
		{
			raf = new RandomAccessFile(""+Cache.cacheDir+layerFileName,"r");
		}
		catch (FileNotFoundException e)
		{
			e.printStackTrace();
		}

		boolean groundLayer=false;
		if(layerFileName.equals(groundLayerMD5()))groundLayer=true;


		//*********
		//IMPORTANT: need to generate chunk sizes that are exactly the size of a power of two.
		//*********



		//at 512, actual chunks will be 256x256, or 32 x 32 tiles
		//but this has a 2 tile border around all sides, so actual tile chunk is 30 x 30
		//we want to get as close to 512x512 as we can for power of two textures, no wasted space




		//NO: can i hq2x as a shader in gpu memory? probably not, don't need to.

		//DONE: need framebuffer, need shader support



		//so:  here we want to load chunkSize + 2 tiles, so 34 x 34


		//so instead let's take 34x34 chunk to begin with, 272x272
		//then we generate a 258x258 png from this, with 1 pixel around border
		//then we save this as BOTH a 256x256 png and a 258x258 png

		//when loading textures into gpu for texture, use the 256x256 png

		//when loading into memory for hq2x, use the 258x258
		//hq2x this, producing 516x516
		//remove 2 from borders, producing 512x512
		//save this as nice clean 512x512 even DXT




		try
		{

			int startY = (chunkY*(chunkSizeTiles1X));
			int startX = (chunkX*(chunkSizeTiles1X));

			//startY - 1 because of border.
			for(int y = startY-1;y<(startY+chunkSizeTiles1X)+1;y++)
			{

				//if y is actually negative, fill it with 0 because it's off the map
				if(y>=heightTiles1X() || y<0)
				{
					//fill with 0

				}
				else
				{
					if(chunkX==0)
					{
						//seek to 0
						raf.seek((long)(((y*widthTiles1X())+(startX))*4));//*4 for bytes -> int4

						//for -1 to +1
						//if x is -1, fill with 0

						for(int x = startX-1;x<(startX+chunkSizeTiles1X)+1;x++)
						{
							if(x>=widthTiles1X() || x<0)
							{
								layerChunkBuffer[(((y+1)-startY)*(chunkSizeTiles1X+2))+((x+1)-startX)] = 0;
							}
							else
							{
								int result = raf.readInt();

//								int byte1 = raf.read() & 0xFF;
//								int byte2 = raf.read() & 0xFF;
//
//								int result = (byte2<<8) + byte1;

								if(result!=0)isBlank=false;

								layerChunkBuffer[(((y+1)-startY)*(chunkSizeTiles1X+2))+((x+1)-startX)] = result;
							}
						}

					}
					else
					{

						//seek to -1
						raf.seek((long)(((y*widthTiles1X())+(startX-1))*4));

						//for 0 to +2

						for(int x = (startX);x<(startX+chunkSizeTiles1X)+2;x++)
						{
							if(x>=widthTiles1X() || x<0)
							{
								layerChunkBuffer[(((y+1)-startY)*(chunkSizeTiles1X+2))+(x-startX)] = 0;
							}
							else
							{

								int result = raf.readInt();

//								int byte1 = raf.read() & 0xFF;
//								int byte2 = raf.read() & 0xFF;
//
//								int result = (byte2<<8) + byte1;

								if(result!=0)isBlank=false;

								layerChunkBuffer[(((y+1)-startY)*(chunkSizeTiles1X+2))+(x-startX)] = result;
							}
						}
					}
				}
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}

		try
		{
			if(raf!=null)raf.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}


		if(isBlank==true)return false;


		for(int ty=0;ty<(chunkSizeTiles1X+2);ty++)
		{
			for(int tx=0;tx<(chunkSizeTiles1X+2);tx++)
			{

				int tile = layerChunkBuffer[(ty*(chunkSizeTiles1X+2))+tx];

				//skip black tiles on the ground layer
				if(groundLayer==true&&tile==1)continue;

				for(int py=0;py<8;py++)
				for(int px=0;px<8;px++)
				{

					//skip all but one pixel of border
					if(tx==0&&px<7)continue;
					if(tx==chunkSizeTiles1X+1&&px>0)continue;
					if(ty==0&&py<7)continue;
					if(ty==chunkSizeTiles1X+1&&py>0)continue;


					int tilesetIndex = ((tile*64)+(py*8+px));//*2;

					int paletteIndex = tilesetIntArray[tilesetIndex];

//					int byte1 = tileset[tilesetIndex] & 0xFF;
//					int byte2 = tileset[tilesetIndex+1] & 0xFF;
//
//					int paletteIndex = (byte2<<8)+byte1;

					if(paletteIndex!=0)
					{
						int paletteR = paletteRGBByteArray[(paletteIndex*3)+(0)] & 0xFF;
						int paletteG = paletteRGBByteArray[(paletteIndex*3)+(1)] & 0xFF;
						int paletteB = paletteRGBByteArray[(paletteIndex*3)+(2)] & 0xFF;

						BobColor c = new BobColor(paletteR, paletteG, paletteB);

						if(shadowLayer)//shadow layer
						{

							int oldPixel = chunkImageBorder.getRGB(((tx-1)*8+px)+1, ((ty-1)*8+py)+1);
							BobColor oldColor = new BobColor(oldPixel, true);

							int alpha=255;
							if(oldColor.getRGB()==0)alpha=150;

							float shadowAlpha = 150.0f;
							int blendedRed = (int) ((shadowAlpha/255.0f)*paletteR + (1.0f-(shadowAlpha/255.0f))*oldColor.getRed());
							int blendedGreen = (int) ((shadowAlpha/255.0f)*paletteG + (1.0f-(shadowAlpha/255.0f))*oldColor.getGreen());
							int blendedBlue = (int) ((shadowAlpha/255.0f)*paletteB + (1.0f-(shadowAlpha/255.0f))*oldColor.getBlue());

							c = new BobColor(blendedRed,blendedGreen,blendedBlue,alpha);
						}


						chunkImageBorder.setRGB(((tx-1)*8+px)+1, ((ty-1)*8+py)+1, c.getRGB());

						if(tx>0&&tx<chunkSizeTiles1X+1&&ty>0&&ty<chunkSizeTiles1X+1)
						{
							chunkImage.setRGB((tx-1)*8+px, (ty-1)*8+py, c.getRGB());
						}
					}

				}
			}
		}

		return true;
	}



	//=========================================================================================================================
	public void createHQ2XTexturePNG_THREAD(int chunkX, int chunkY)
	{//=========================================================================================================================


		//Thread.currentThread().setPriority(Thread.MIN_PRIORITY);
		//Thread.yield();

		//load 1x png under and over into bitmap arrays


		int clear = new BobColor(0,0,0,0).getRGB();
		int black = new BobColor(0,0,0,255).getRGB();



		int underChunkIndex = (chunksWidth*chunksHeight*0)+((chunkY*chunksWidth)+chunkX);
		int overChunkIndex = (chunksWidth*chunksHeight*1)+((chunkY*chunksWidth)+chunkX);

		File underLayerTextureFile = new File(Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+"1x_padded"+Cache.slash+underChunkIndex);
		File overLayerTextureFile = new File(Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+"1x_padded"+Cache.slash+overChunkIndex);


		//TODO: handle if 1x file doesn't exist, make it again from md5!

		//TODO: check 1, 1x, hq2x file for being over 0 bytes, the correct width and height... if it isn't, delete it and remake it
		//nice fix for broken cache files




		BufferedImage bottom = null;
		BufferedImage top = null;


		//handle 0 byte files!
		if(underLayerTextureFile.length()<1) //it is actually a completely empty image, it was all 0 tiles
		{


			bottom = new BufferedImage(chunkSizePixels1X+2, chunkSizePixels1X+2, BufferedImage.TYPE_INT_ARGB);


			//thought this would fix the hq2x grain glitch, but it was from hq2x being static.
			//dont need to initialize empty graphics
			/*Graphics G = bottom.getGraphics();
			G.setColor(new Color(0,0,0,0));
			G.fillRect(0,0,bottom.getWidth(), bottom.getHeight());
			G.dispose();
			G = null;*/
		}
		else
		{
			try
			{
				bottom = ImageIO.read(underLayerTextureFile);
			}
			catch (IOException e){log.error("Cannot read PNG file: "+underLayerTextureFile.getName()+" "+e.getMessage());}
		}


		if(overLayerTextureFile.length()<1)
		{
			top = new BufferedImage(chunkSizePixels1X+2, chunkSizePixels1X+2, BufferedImage.TYPE_INT_ARGB);
			/*Graphics G = top.getGraphics();
			G.setColor(new Color(0,0,0,0));
			G.fillRect(0,0,top.getWidth(), top.getHeight());
			G.dispose();
			G = null;*/
		}
		else
		{
			try
			{
				top = ImageIO.read(overLayerTextureFile);
			}
			catch (IOException e){log.error("Cannot read PNG file: "+overLayerTextureFile.getName()+" "+e.getMessage());}
		}



		//create bottom + top image

		BufferedImage bottomAndTop = new BufferedImage(chunkSizePixels1X+2, chunkSizePixels1X+2, BufferedImage.TYPE_INT_ARGB);

		//draw bottom, then top into bottomAndTop

		//draw bottom into bottomAndTop
		for(int y = 0; y < bottom.getHeight(); y++)
		{
			for(int x = 0; x < bottom.getWidth(); x++)
			{
				bottomAndTop.setRGB(x, y, bottom.getRGB(x, y));
			}
		}

		//draw top into bottomAndTop
		for(int y = 0; y < top.getHeight(); y++)
		{
			for(int x = 0; x < top.getWidth(); x++)
			{
				if(top.getRGB(x, y)!=clear)
				bottomAndTop.setRGB(x, y, top.getRGB(x, y));
			}
		}

		//----------------------
		//TOP LAYER
		//----------------------

			//hq2x bottom+top
			BufferedImage hq2xBottomAndTop = new HQ2X().hq2x(bottomAndTop);
			//setHQ2XAlphaFromOriginal(hq2xBottomAndTop,bottomAndTop); //(shouldnt be transparent here)

			//dont need bottomandtop
			bottomAndTop.flush();
			bottomAndTop=null;

			BufferedImage hq2xBottomAndTopCopy = new BufferedImage(hq2xBottomAndTop.getWidth(), hq2xBottomAndTop.getHeight(), BufferedImage.TYPE_INT_ARGB);
			for(int y=0;y<hq2xBottomAndTop.getHeight();y++)
			for(int x=0;x<hq2xBottomAndTop.getWidth();x++)
			{
				//copy x,y into x-2,y-2
				hq2xBottomAndTopCopy.setRGB(x,y,hq2xBottomAndTop.getRGB(x, y));
			}


			//Masking 1x top layer from HQ2X bottom+top
			//go through top layer
			//for each transparent pixel set 2x (x+xx y+yy) transparent on hq2x bottom+top
			for(int y = 0; y < top.getHeight(); y++)
			{
				for(int x = 0; x < top.getWidth(); x++)
				{



					//copy alpha pixels from top, including clear and transparent shadows
					//TODO: fix this in editor as well when outputting hq2x
					if(((top.getRGB(x, y) >> 24) & 0xff) < 255)
					{
						for(int xx=0;xx<2;xx++)
						for(int yy=0;yy<2;yy++)
							hq2xBottomAndTop.setRGB((x*2)+xx, ((y*2)+yy), top.getRGB(x, y));
					}


					//could do better antialiasing around edges here. since we're masking out the bottom layer, some of the edges on the top layer have gray pixels.
					//i could go through the top image, find clear pixels surrounded with black, and set the in-between pixel on the hq2x image with black alpha 127

					//this is kind of broken for negligible benefit, not worth working on at the moment

					/*if(top.getRGB(x, y)==clear)
					{
						if(
							(x<top.getWidth()-1&&x>0&&y<top.getHeight()-1&&y>0)
							)
						{
							if(top.getRGB(x+1, y)!=clear&&top.getRGB(x, y-1)!=clear)//right up
							{
								hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+0), new BobColor(0,255,0,127).getRGB());
								hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+0), new BobColor(0,255,0,127).getRGB());
								hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+1), new BobColor(0,255,0,127).getRGB());
							}

							if(top.getRGB(x+1, y)!=clear&&top.getRGB(x, y+1)!=clear)//right down
							{
								hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+1), new BobColor(0,255,0,127).getRGB());
								hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+1), new BobColor(0,255,0,127).getRGB());
								hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+0), new BobColor(0,255,0,127).getRGB());
							}

							if(top.getRGB(x-1, y)!=clear&&top.getRGB(x, y-1)!=clear)//left up
							{
								hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+0), new BobColor(0,255,0,127).getRGB());
								hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+0), new BobColor(0,255,0,127).getRGB());
								hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+1), new BobColor(0,255,0,127).getRGB());
							}

							if(top.getRGB(x-1, y)!=clear&&top.getRGB(x, y+1)!=clear)//left down
							{
								hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+1), new BobColor(0,255,0,127).getRGB());
								hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+0), new BobColor(0,255,0,127).getRGB());
								hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+1), new BobColor(0,255,0,127).getRGB());
							}
						}

					}*/

				}
			}


			//could antialias black edges here. ****this algorithm doesn't really work because all the edges are already interpolated with the background color.
			//antialiasBufferedImage(hq2xBottomAndTop);

			//----------------------
			//output hq2x top layer fully
			//----------------------

				//Outputting full HQ2X top layer

				//make temp image size-4

				BufferedImage temp = new BufferedImage(hq2xBottomAndTop.getWidth()-4,hq2xBottomAndTop.getHeight()-4, BufferedImage.TYPE_INT_ARGB);
				for(int y=2;y<hq2xBottomAndTop.getHeight()-2;y++)
				for(int x=2;x<hq2xBottomAndTop.getWidth()-2;x++)
				{
					//copy x,y into x-2,y-2
					temp.setRGB(x-2,y-2,hq2xBottomAndTop.getRGB(x, y));
				}

				//save temp as hq2x_top
				Utils.saveImage(Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+"2x"+Cache.slash+overChunkIndex,temp);

				//don't need temp
				temp.flush();
				temp = null;


			//dont need hq2xBottomAndTop
			hq2xBottomAndTop.flush();
			hq2xBottomAndTop=null;


		//----------------------
		//BOTTOM LAYER
		//----------------------

		//hq2x bottom+top again

		hq2xBottomAndTop = hq2xBottomAndTopCopy;//new HQ2X().HQ2X(bottomAndTop); //it is probably better to just copy the image above before i modify it


		//put back any transparent pixels from bottom (borders around map)
		setHQ2XAlphaFromOriginal(hq2xBottomAndTop,bottom);

		//hq2x bottom
		BufferedImage hq2xBottom = new HQ2X().hq2x(bottom);


		//dont need bottom
		bottom.flush();
		bottom=null;


		//Masking HQ2X bottom layer into HQ2X bottom+top layer
		//go through top layer
		//for each NON-transparent pixel 2x (x+xx y+yy ) take pixel from hq2x bottom, copy into hq2x bottom_top
		for(int y = 0; y < top.getHeight(); y++)
		{
			for(int x = 0; x < top.getWidth(); x++)
			{
				if(top.getRGB(x, y)!=clear)
				{
					for(int xx=0;xx<2;xx++)
					for(int yy=0;yy<2;yy++)
						hq2xBottomAndTop.setRGB((x*2)+xx, ((y*2)+yy), hq2xBottom.getRGB((x*2)+xx, ((y*2)+yy)));
				}

			}
		}




		//dont need top
		top.flush();
		top=null;

		//dont need hq2xBottom
		hq2xBottom.flush();
		hq2xBottom=null;


		//----------------------
		//output hq2x bottom layer full
		//----------------------

			temp = new BufferedImage(hq2xBottomAndTop.getWidth()-4,hq2xBottomAndTop.getHeight()-4, BufferedImage.TYPE_INT_ARGB);
			for(int y=2;y<hq2xBottomAndTop.getHeight()-2;y++)
			for(int x=2;x<hq2xBottomAndTop.getWidth()-2;x++)
			{
				//copy x,y into x-2,y-2
				temp.setRGB(x-2,y-2,hq2xBottomAndTop.getRGB(x, y));
			}

			//Outputting full HQ2X bottom layer
			//save as hq2x bottom
			Utils.saveImage(Cache.cacheDir+"_"+groundLayerMD5()+Cache.slash+"2x"+Cache.slash+underChunkIndex,temp);

			//don't need temp
			temp.flush();
			temp = null;

		//dont need hq2xBottomAndTop
		hq2xBottomAndTop.flush();
		hq2xBottomAndTop=null;
		hq2xBottomAndTopCopy=null;




		//DONE: set chunkTexture to hq2x chunk

		//need to do this in main thread, can't release textures in a secondary thread.
		//set a thing textureIsHQ2X, allHQ2XLoaded

		//Texture t = getChunkTexture(underChunkIndex);
		//setChunkTexture(underChunkIndex,null);
		//t.release();
		//t=null;


		//t = getChunkTexture(overChunkIndex);
		//setChunkTexture(overChunkIndex,null);
		//t.release();
		//t=null;


		//delete 1x pngs top and bottom

		underLayerTextureFile.delete();
		overLayerTextureFile.delete();


	}



	//===============================================================================================
	public void antialiasBufferedImage(BufferedImage bufferedImage)
	{//===============================================================================================

		//go through hq2x image
		//if pixel is transparent, and the pixel right and down, down and left, left and up, or up and right are black, this one is black

		//have to make a copy otherwise the algorithm becomes recursive
		BufferedImage copy = new BufferedImage(bufferedImage.getWidth(), bufferedImage.getHeight(), BufferedImage.TYPE_INT_ARGB);
		for(int y = 0; y < bufferedImage.getHeight(); y++)
		{
			for(int x = 0; x < bufferedImage.getWidth(); x++)
			{
				copy.setRGB(x, y, bufferedImage.getRGB(x,y));
			}
		}

		int clear = new BobColor(0,0,0,0).getRGB();

		for(int y = 0; y < bufferedImage.getHeight(); y++)
		{
			for(int x = 0; x < bufferedImage.getWidth(); x++)
			{
				if(copy.getRGB(x, y)==clear)
				{
					int black=0;

					//check right and down
					if(x+1<bufferedImage.getWidth()&&y+1<bufferedImage.getHeight())
					{
						if(
							copy.getRGB(x+1, y)!=clear&&
							copy.getRGB(x, y+1)!=clear
						)
						black=1;
					}

					//check right and up
					if(x+1<bufferedImage.getWidth()&&y-1>=0)
					{
						if(
							copy.getRGB(x+1, y)!=clear&&
							copy.getRGB(x, y-1)!=clear
						)
						black=1;
					}


					//check left and down
					if(x-1>=0&&y+1<bufferedImage.getHeight())
					{
						if(
							copy.getRGB(x-1, y)!=clear&&
							copy.getRGB(x, y+1)!=clear
						)
						black=1;
					}

					//check left and up
					if(x-1>=0&&y-1>=0)
					{
						if(
							copy.getRGB(x-1, y)!=clear&&
							copy.getRGB(x, y-1)!=clear
						)
						black=1;
					}

					if(black==1)bufferedImage.setRGB(x, y, new BobColor(0,0,0,127).getRGB());
				}

			}
		}
	}
	//===============================================================================================
	public void setHQ2XAlphaFromOriginal(BufferedImage hq2xBufferedImage, BufferedImage bufferedImage)
	{//===============================================================================================
		//now go through original image again. take each transparent pixel and set the hq2x one with it at 2x
		for(int y = 0; y < bufferedImage.getHeight(); y++)
		{
			for(int x = 0; x < bufferedImage.getWidth(); x++)
			{
				if(bufferedImage.getRGB(x, y)==0)
				{
					for(int xx=0;xx<2;xx++)
					for(int yy=0;yy<2;yy++)
						hq2xBufferedImage.setRGB((x*2)+xx, ((y*2)+yy), new BobColor(0,0,0,0).getRGB());
				}

			}
		}
	}



	//=========================================================================================================================
	public void addEntitiesAndCharactersFromCurrentStateToActiveEntityList()
	{//=========================================================================================================================


		for(int n=0;n<currentState.entityList.size();n++)
		{
			Entity ms = currentState.entityList.get(n);
			activeEntityList.add(ms);
		}

		for(int n=0;n<currentState.characterList.size();n++)
		{
			Character ms = currentState.characterList.get(n);
			activeEntityList.add(ms);
		}

		if(Player()!=null && ClientGameEngine().playerExistsInMap)activeEntityList.add(Player());
	}


	//=========================================================================================================================
	public void clearActiveEntityList()
	{//=========================================================================================================================

		//have to release unique textures on random entities
		for(int i=0;i<activeEntityList.size();i++)
		{
			Entity e = activeEntityList.get(i);
			if(e.getClass().equals(RandomCharacter.class))
			{
				RandomCharacter r = (RandomCharacter)e;
				if(r.uniqueTexture!=null)r.uniqueTexture = GLUtils.releaseTexture(r.uniqueTexture);
			}
		}

		activeEntityList.clear();
		//if(Player()!=null)entityList.add(Player());
		//entityList.add(Cameraman());
	}


	//=========================================================================================================================
	public boolean isAnyoneOverlappingXY(float x, float y)
	{//=========================================================================================================================
		for(int i=0;i<activeEntityList.size();i++)
		{
			//find any characters
			Entity e = activeEntityList.get(i);

			if(
				x>e.left()
				&&x<e.right()
				&&y>e.top()
				&&y<e.bottom()
			)
			{
				return true;
			}
		}

		return false;

	}
	//=========================================================================================================================
	public boolean isAnyoneOverlappingXYXY(float x, float y, float x2, float y2)
	{//=========================================================================================================================
		for(int i=0;i<activeEntityList.size();i++)
		{
			//find any characters
			Entity e = activeEntityList.get(i);

			if(
					x<e.right()
					&&x2>e.left()
					&&y<e.bottom()
					&&y2>e.top()
			)
			{
				return true;
			}
		}

		return false;

	}

	//=========================================================================================================================
	public boolean isAnyRandomCharacterTryingToGoToXY(float x, float y)
	{//=========================================================================================================================
		for(int i=0;i<activeEntityList.size();i++)
		{
			//find any characters
			Entity e = activeEntityList.get(i);

			if(e.getClass().equals(RandomCharacter.class))
			{
				RandomCharacter c = (RandomCharacter)e;

				if(
						x==c.targetX
						&&
						y==c.targetY
				)
				{
					return true;
				}
			}
		}

		return false;

	}


	//=========================================================================================================================
	public int[] findOpenSpaceInArea(Area a, int w, int h)
	{//=========================================================================================================================

		ArrayList<int[]> coords = new ArrayList<int[]>();

		for(int x=1;x<a.w()/8;x++)
		for(int y=1;y<a.h()/8;y++)
		{
			int[] xy = new int[] {x,y};
			coords.add(xy);
		}

		while(coords.size()>0)
		{
			int i = Utils.randLessThan(coords.size());
			int[] xy = coords.get(i);
			int x = xy[0];
			int y = xy[1];

			if(
				isAnyoneOverlappingXYXY(a.x()+(x*8-w/2), a.y()+(y*8-h/2), a.x()+(x*8+w/2), a.y()+(y*8+h/2))==false
				&&
				isAnyRandomCharacterTryingToGoToXY(a.x()+a.w()/2, a.y()+a.h()/2)==false

			)
			{

				//TODO: could also check all the other random characters targetX and targetY to make sure nobody is TRYING to go here


				int[] finalcoords = new int[] {(int)(a.x() + x*8),(int)(a.y() + y*8)};

				return finalcoords;

			}
			else
			coords.remove(i);

		}
		return null;

	}


	//=========================================================================================================================
	public boolean isAnyCharacterTouchingArea(Area a)
	{//=========================================================================================================================

		//go through all entities, if somebody is standing here, don't go there.

		if(a!=null)//DEBUG HERE
		{
			for(int i=0;i<activeEntityList.size();i++)
			{
					Entity e = activeEntityList.get(i);

					if(
						(
							(
								(
									e.getClass().equals(Character.class)
									||
									e.getClass().equals(RandomCharacter.class)

								)
								//&&
								//m.nonWalkable==true
							)
							||
							e.getClass().equals(Player.class)
						)
						&&a.isEntityHitBoxTouchingMyBoundary(e)
					)return true;
			}
		}

		return false;

	}



	//=========================================================================================================================
	public boolean isAnyEntityTouchingArea(Area a)
	{//=========================================================================================================================

		//go through all entities, if somebody is standing here, don't go there.

		if(a!=null)//DEBUG HERE
		{
			for(int i=0;i<activeEntityList.size();i++)
			{
					Entity e = activeEntityList.get(i);

					if(a.isEntityHitBoxTouchingMyBoundary(e))return true;
			}
		}

		return false;

	}

	//=========================================================================================================================
	public ArrayList<Entity> getAllEntitiesTouchingArea(Area a)
	{//=========================================================================================================================

		ArrayList<Entity> entitiesInArea = new ArrayList<Entity>();


		for(int i=0;i<activeEntityList.size();i++)
		{
			Entity e = activeEntityList.get(i);

			if(a.isEntityHitBoxTouchingMyBoundary(e))entitiesInArea.add(e);
		}


		return entitiesInArea;
	}



	//=========================================================================================================================
	public ArrayList<Entity> getAllEntitiesPlayerIsTouching()
	{//=========================================================================================================================

		ArrayList<Entity> entitiesTouching = new ArrayList<Entity>();


		for(int i=0;i<activeEntityList.size();i++)
		{
			Entity e = activeEntityList.get(i);

			if(Player().isEntityHitBoxTouchingMyHitBox(e))entitiesTouching.add(e);
		}


		return entitiesTouching;
	}

	//=========================================================================================================================
	public boolean isAnyoneTryingToGoToArea(Area a)
	{//=========================================================================================================================
		if(a!=null)//DEBUG HERE
		{
			for(int i=0;i<activeEntityList.size();i++)
			{
				if(activeEntityList.get(i).currentAreaTYPEIDTarget.equals(a.name()))
				{
					return true;
				}
			}
		}
		return false;
	}


	//=========================================================================================================================
	public boolean isAnyEntityUsingSpriteAsset(Sprite s)
	{//=========================================================================================================================

		for(int i=0;i<activeEntityList.size();i++)
		{
			if(activeEntityList.get(i).sprite==s)return true;
		}


		return false;
	}

	//=========================================================================================================================
	public ArrayList<Entity> getAllEntitiesUsingSpriteAsset(Sprite s)
	{//=========================================================================================================================

		ArrayList<Entity> entitiesUsingSprite = new ArrayList<Entity>();

		for(int i=0;i<activeEntityList.size();i++)
		{
			Entity e = activeEntityList.get(i);

			if(e.sprite==s)entitiesUsingSprite.add(e);
		}


		return entitiesUsingSprite;
	}

	//=========================================================================================================================
	public Entity createEntity(Map map, String spriteName,Sprite spriteAsset,float mapX,float mapY) // SIZE X AND Y ARE ACTUAL Entity HEIGHT AND WIDTH NOT SPRITE SIZE.. X AND Y ARE UPPER LEFT CORNER NOT FEET
	{//=========================================================================================================================


		EntityData entityData = new EntityData(-1,spriteName,spriteAsset.name(),mapX/2,mapY/2);

		Entity e = new Entity(Engine(), entityData, this);

		CurrentMap().currentState.entityList.add(e);
		CurrentMap().currentState.entityByNameHashtable.put(e.name(),e);

		return e;
	}

	//=========================================================================================================================
	public Entity createEntityFeetAtXY(Map map, String spriteName,Sprite sprite,float mapX,float mapY) // SIZE X AND Y ARE ACTUAL Entity HEIGHT AND WIDTH NOT SPRITE SIZE,X AND Y ARE FEET PLACEMENT
	{//=========================================================================================================================

		// use hitbox center instead of arbitrary offset
		SpriteAnimationSequence a = sprite.getFirstAnimation();
		int hitBoxYCenter = (a.hitBoxFromTopPixels1X*2) + (((sprite.h()-(a.hitBoxFromTopPixels1X*2))-(a.hitBoxFromBottomPixels1X*2))/2);

		return createEntity(map, spriteName,sprite,mapX-(sprite.w()/2),mapY-(hitBoxYCenter));
	}

	//=========================================================================================================================
	public Entity createEntityIfWithinRangeElseDelete_MUST_USE_RETURNVAL(Map map, Entity e, String spriteName,Sprite sprite,float mapX,float mapY,int amt)
	{//=========================================================================================================================

		if(map.isXYWithinScreenByAmt(mapX+sprite.w()/2,mapY+sprite.h()/2,amt)==true)
		{
			if(e==null)return createEntity(map, spriteName,sprite,mapX,mapY);
			else return e;
		}
		else
		{
			if(e!=null)e.delete();
			return null;
		}
	}

	//=========================================================================================================================
	public Entity createEntityAtArea(Map map, String spriteName, Sprite spriteAsset, Area a)
	{//=========================================================================================================================
		float x = a.middleX();
		float y = a.middleY();

		return createEntityFeetAtXY(map,spriteName,spriteAsset,x,y);
	}




	public MapData getData(){return data;}


	public int id(){return data.id();}
	public String name(){return data.name();}
	public String mapNote(){return data.mapNote();}

	public int widthTiles1X(){return data.widthTiles1X();}
	public int heightTiles1X(){return data.heightTiles1X();}

	public int widthPixelsHQ(){return data.widthPixelsHQ();}
	public int heightPixelsHQ(){return data.heightPixelsHQ();}


	public int maxRandoms(){return data.maxRandoms();}
	public boolean isOutside(){return data.isOutside();}

	public String getTYPEIDString(){return data.getTYPEIDString();}

	public String groundLayerMD5(){return getData().groundLayerMD5();}
	public String groundObjectsMD5(){return getData().groundObjectsMD5();}
	public String groundShadowMD5(){return getData().groundShadowMD5();}
	public String objectsMD5(){return getData().objectsMD5();}
	public String objects2MD5(){return getData().objects2MD5();}
	public String objectShadowMD5(){return getData().objectShadowMD5();}
	public String aboveMD5(){return getData().aboveMD5();}
	public String above2MD5(){return getData().above2MD5();}
	public String spriteShadowMD5(){return getData().spriteShadowMD5();}
	public String groundShaderMD5(){return getData().groundShaderMD5();}
	public String cameraBoundsMD5(){return getData().cameraBoundsMD5();}
	public String hitBoundsMD5(){return getData().hitBoundsMD5();}
	public String lightMaskMD5(){return getData().lightMaskMD5();}

	public String paletteMD5(){return getData().paletteMD5();}
	public String tilesMD5(){return getData().tilesMD5();}

//	public Vector<MapStateData> stateDataList(){return getData().stateDataList();}
//	public Vector<EventData> eventDataList(){return getData().eventDataList();}
//	public Vector<DoorData> doorDataList(){return getData().doorDataList();}



	//set


//	public void setWidthTiles(int s){getData().setWidthTiles1X(s);}
//	public void setHeightTiles(int s){getData().setHeightTiles1X(s);}
//
//	public void setID(int s){getData().setID(s);}
//	public void setMapNote(String s){getData().setMapNote(s);}
//
//	public void setMaxRandoms(int s){getData().setMaxRandoms(s);}
//	public void setIsOutside(boolean s){getData().setIsOutside(s);}
//

	public void setGroundLayerMD5(String s){getData().setGroundLayerMD5(s);}
	public void setGroundObjectsMD5(String s){getData().setGroundObjectsMD5(s);}
	public void setGroundShadowMD5(String s){getData().setGroundShadowMD5(s);}
	public void setObjectsMD5(String s){getData().setObjectsMD5(s);}
	public void setObjects2MD5(String s){getData().setObjects2MD5(s);}
	public void setObjectShadowMD5(String s){getData().setObjectShadowMD5(s);}
	public void setAboveMD5(String s){getData().setAboveMD5(s);}
	public void setAbove2MD5(String s){getData().setAbove2MD5(s);}
	public void setSpriteShadowMD5(String s){getData().setSpriteShadowMD5(s);}
	public void setGroundShaderMD5(String s){getData().setGroundShaderMD5(s);}
	public void setCameraBoundsMD5(String s){getData().setCameraBoundsMD5(s);}
	public void setHitBoundsMD5(String s){getData().setHitBoundsMD5(s);}
	public void setLightMaskMD5(String s){getData().setLightMaskMD5(s);}

	public void setPaletteMD5(String s){getData().setPaletteMD5(s);}
	public void setTilesMD5(String s){getData().setTilesMD5(s);}




}
