package com.bobsgame.editor.Project;


import java.awt.Frame;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.Hashtable;
import java.util.ArrayList;
import java.util.List;
import java.util.zip.ZipEntry;
import java.util.zip.ZipException;
import java.util.zip.ZipOutputStream;
//import java.util.zip.*;

import javax.swing.Timer;

import org.apache.commons.compress.archivers.zip.ZipArchiveEntry;
import org.apache.commons.compress.archivers.zip.ZipFile;
import org.apache.commons.io.FileUtils;
import org.apache.commons.io.IOUtils;


//import com.bobsgame.ClientMain;
import com.bobsgame.EditorMain;
import com.bobsgame.editor.Dialogs.NumberDialog;
import com.bobsgame.editor.Dialogs.YesNoWindow;
import com.bobsgame.editor.Project.Event.GameString;
import com.bobsgame.editor.Project.Event.Dialogue;
import com.bobsgame.editor.Project.Event.Event;
import com.bobsgame.editor.Project.Event.Flag;
import com.bobsgame.editor.Project.Event.Skill;
import com.bobsgame.editor.Project.Event.Music;
import com.bobsgame.editor.Project.Event.Sound;
import com.bobsgame.editor.Project.Map.Area;
import com.bobsgame.editor.Project.Map.Door;
import com.bobsgame.editor.Project.Map.Entity;
import com.bobsgame.editor.Project.Map.Light;
import com.bobsgame.editor.Project.Map.Map;

import com.bobsgame.editor.Project.Map.Map.MapBinWithUniqueTilesetAndPalette;
import com.bobsgame.editor.Project.Map.MapState;
import com.bobsgame.editor.Project.Sprite.Sprite;
import com.bobsgame.editor.Project.Sprite.Sprite.SpriteBinWithUniquePalette;
import com.bobsgame.editor.Project.Sprite.SpritePalette;
import com.bobsgame.shared.AreaData;
import com.bobsgame.shared.DialogueData;
import com.bobsgame.shared.DoorData;
import com.bobsgame.shared.EntityData;
import com.bobsgame.shared.EventData;
import com.bobsgame.shared.FlagData;
import com.bobsgame.shared.GameStringData;
import com.bobsgame.shared.LightData;
import com.bobsgame.shared.MapData;
import com.bobsgame.shared.MapStateData;
import com.bobsgame.shared.MusicData;
import com.bobsgame.shared.SkillData;
import com.bobsgame.shared.SoundData;
import com.bobsgame.shared.SpriteData;
import com.bobsgame.shared.Utils;

//===============================================================================================
public class Project
{//===============================================================================================

	public EditorMain E;

	public String name, directory;
	public static Tileset tileset;



	public static ArrayList<Event> cutsceneEventList = new ArrayList<Event>();


	private static int selected_Map = -1;


	private static int selected_Palette = -1;

	public static ArrayList<TilesetPalette> palette = new ArrayList<TilesetPalette>();
	public static ArrayList<SpritePalette> spritepalette = new ArrayList<SpritePalette>();



	private static int selected_Sprite = 0;//-1;
	private static int selected_SpritePalette = 0;


	//public int maxRGBValue=255;





	//these are just handy lists used for quick lookup and generating IDs.
	//they are loaded in the order of the Maps they are attached to, not ordered by their unique ID.
	//the hashTables are there for fast lookup by "TYPE.id" String which is output by any MapObject getIDString() function when exporting.

	public static ArrayList<Area> areaIndexList = new ArrayList<Area>();
	public static Hashtable<String,Area> areaIndexHashtable = new Hashtable<String,Area>();

	public static ArrayList<Entity> entityIndexList = new ArrayList<Entity>();
	public static Hashtable<String,Entity> entityIndexHashtable = new Hashtable<String,Entity>();

	public static ArrayList<Light> lightIndexList = new ArrayList<Light>();
	public static Hashtable<String,Light> lightIndexHashtable = new Hashtable<String,Light>();

	public static ArrayList<Door> doorIndexList = new ArrayList<Door>();
	public static Hashtable<String,Door> doorIndexHashtable = new Hashtable<String,Door>();

	public static ArrayList<MapState> stateIndexList = new ArrayList<MapState>();
	public static Hashtable<String,MapState> stateIndexHashtable = new Hashtable<String,MapState>();

	public static ArrayList<Event> eventList = new ArrayList<Event>();//events are also stored in Maps.eventList by reference and MapObjects by eventID
	public static Hashtable<String,Event> eventHashtable = new Hashtable<String,Event>();


	//these lists are the only place these objects are located.

	public static ArrayList<Map> mapList = new ArrayList<Map>(); //this stores the maps loaded in the normal load order.
	public static Hashtable<String,Map> mapHashtable = new Hashtable<String,Map>();//this indexes the maps by String "MAP.id"

	public static ArrayList<Sprite> spriteList = new ArrayList<Sprite>(); //this stores the sprites loaded in the normal load order.
	public static Hashtable<String,Sprite> spriteHashtable = new Hashtable<String,Sprite>();//this indexes the sprites by String "SPRITE.id"



	public static ArrayList<Dialogue> dialogueList = new ArrayList<Dialogue>();
	public static Hashtable<String,Dialogue> dialogueHashtable = new Hashtable<String,Dialogue>();




	public static ArrayList<Flag> flagList = new ArrayList<Flag>();
	public static Hashtable<String,Flag> flagHashtable = new Hashtable<String,Flag>();

	public static ArrayList<GameString> gameStringList = new ArrayList<GameString>();
	public static Hashtable<String,GameString> gameStringHashtable = new Hashtable<String,GameString>();

	public static ArrayList<Sound> soundList = new ArrayList<Sound>();
	public static Hashtable<String,Sound> soundHashtable = new Hashtable<String,Sound>();

	public static ArrayList<Music> musicList = new ArrayList<Music>();
	public static Hashtable<String,Music> musicHashtable = new Hashtable<String,Music>();

	public static ArrayList<Skill> skillList = new ArrayList<Skill>();
	public static Hashtable<String,Skill> skillHashtable = new Hashtable<String,Skill>();









	//===============================================================================================
	public Project(EditorMain e)		// Set up a new project
	{//===============================================================================================
		E=e;

		name = "blank";
		tileset = new Tileset();

		mapList = new ArrayList<Map>();
		mapHashtable = new Hashtable<String,Map>();
		spriteList = new ArrayList<Sprite>();
		spriteHashtable = new Hashtable<String,Sprite>();

		palette = new ArrayList<TilesetPalette>();

		spritepalette = new ArrayList<SpritePalette>();



		areaIndexList = new ArrayList<Area>();
		entityIndexList = new ArrayList<Entity>();
		lightIndexList = new ArrayList<Light>();
		doorIndexList = new ArrayList<Door>();
		areaIndexHashtable = new Hashtable<String,Area>();
		entityIndexHashtable = new Hashtable<String,Entity>();
		lightIndexHashtable = new Hashtable<String,Light>();
		doorIndexHashtable = new Hashtable<String,Door>();
		stateIndexList = new ArrayList<MapState>();
		stateIndexHashtable = new Hashtable<String,MapState>();




		dialogueList = new ArrayList<Dialogue>();
		dialogueHashtable = new Hashtable<String,Dialogue>();

		eventList = new ArrayList<Event>();
		eventHashtable = new Hashtable<String,Event>();

		flagList = new ArrayList<Flag>();
		flagHashtable = new Hashtable<String,Flag>();

		gameStringList = new ArrayList<GameString>();
		gameStringHashtable = new Hashtable<String,GameString>();

		soundList = new ArrayList<Sound>();
		soundHashtable = new Hashtable<String,Sound>();

		musicList = new ArrayList<Music>();
		musicHashtable = new Hashtable<String,Music>();

		skillList = new ArrayList<Skill>();
		skillHashtable = new Hashtable<String,Skill>();



		selected_Map = 0;
		//getNumMaps() = 0;

		//getNumPalettes() = 0;
		selected_Palette = -1;

		//getNumSprites() = 0;
		selected_Sprite = 0;//-1;

		//getNumSpritePalettes() = 0;
		selected_SpritePalette = 0;


		createNewPalette();
		appendNewMap();


		createNewSpritePalette();
		new Sprite("Sprite0",1,16,32);
		new Sprite("DoorTestSprite",1,32,64).setIsDoor(true);

	}

	//===============================================================================================
	public Project(EditorMain e, String name)		// Set up a new project
	{//===============================================================================================
		this(e);

		this.name = name;


		//16 across
		//1024 total

		//64 rows down

		//let's do 8x8 groups

		//color 0 = clear
		//color 1 = black
		//32 shades of gray

		for(int i=0;i<32;i++)
		{
			if(i==0)
			{
				getPalette(0).setColorDataFromRGB(i,0,0,152);
				getSpritePalette(0).setColorDataFromRGB(i,0,0,152);

			}
			else if(i==1)
			{
				getPalette(0).setColorDataFromRGB(i,8,8,8);
				getSpritePalette(0).setColorDataFromRGB(i,8,8,8);
			}
			else
			{

				int v = ((i)*8);//(int)(((float)(i-2)/30.0f) * 256.0f);
				getPalette(0).setColorDataFromRGB(i,v,v,v);
				getSpritePalette(0).setColorDataFromRGB(i,v,v,v);
			}
		}



		//we are on color 32
		//third row

		//so hue in groups of
		//(total colors  - 32) / (8*8)

		int totalColors = getPalette(0).numColors;

		int rowWidth = 16;

		int satSize = 5;//8x8 groups, brightness + ->
		int briSize = 8;//               \|/ sat +



		int rowsRemaining = (totalColors-32)/rowWidth;
		int totalHues = ((rowsRemaining/satSize)* (rowWidth/briSize));



						//(totalColors-32)//we are on color 32 because of grays
						///
						//(satSize*briSize);

		for(int hueGroup = 0; hueGroup < totalHues;hueGroup++)
		{

			int hue = (int)(((float)hueGroup/(float)(totalHues-1))*255.0f);//256 because hueGroup is always less //255 because totalHues -1 so we skew closer to 255

			int satGroup = 0;
			int briGroup = 0;

			for(satGroup=0;satGroup<satSize;satGroup++)
			{

				//we want to clamp sat between 16 and 256
				int sat = (int)((((((float)satGroup/(float)satSize)*216.0f)+40.0f)/232.0f)*255.0f); //(256-offset) + offset to start at a reasonably light color. / 232 should be /255, but i want to skew closer to 255


				for(briGroup=0;briGroup<briSize;briGroup++)
				{

					//we want to clamp bri between 16 and 256

					int bri = (int)((((((float)briGroup/(float)briSize)*216.0f)+40.0f)/232.0f)*255.0f);


					int startRow = 2 + ((hueGroup/(rowWidth/briSize))*satSize);//start at 2 because color 32
					int startCol = briSize * (hueGroup%(rowWidth/briSize));

					int currentRow = startRow + satGroup;
					int currentCol = startCol + briGroup;

					int colorIndex = (currentRow * rowWidth) + currentCol;


					//int h = (int)(hue * 255.0f);
					//int s = (int)(sat * 255.0f);
					//int b = (int)(bri * 255.0f);


					getPalette(0).setColorDataFromHSBData(colorIndex,hue,sat,bri);
					getSpritePalette(0).setColorDataFromHSBData(colorIndex,hue,sat,bri);

				}
			}
		}
	}


	//===============================================================================================
	public Project(String filename, String directory, EditorMain e)
	{//===============================================================================================


		E=e;
		tileset = new Tileset();

		mapList = new ArrayList<Map>();
		mapHashtable = new Hashtable<String,Map>();
		spriteList = new ArrayList<Sprite>();
		spriteHashtable = new Hashtable<String,Sprite>();

		spritepalette = new ArrayList<SpritePalette>();
		palette = new ArrayList<TilesetPalette>();



		areaIndexList = new ArrayList<Area>();
		entityIndexList = new ArrayList<Entity>();
		lightIndexList = new ArrayList<Light>();
		doorIndexList = new ArrayList<Door>();
		areaIndexHashtable = new Hashtable<String,Area>();
		entityIndexHashtable = new Hashtable<String,Entity>();
		lightIndexHashtable = new Hashtable<String,Light>();
		doorIndexHashtable = new Hashtable<String,Door>();
		stateIndexList = new ArrayList<MapState>();
		stateIndexHashtable = new Hashtable<String,MapState>();

		dialogueList = new ArrayList<Dialogue>();
		dialogueHashtable = new Hashtable<String,Dialogue>();

		eventList = new ArrayList<Event>();
		eventHashtable = new Hashtable<String,Event>();

		flagList = new ArrayList<Flag>();
		flagHashtable = new Hashtable<String,Flag>();

		gameStringList = new ArrayList<GameString>();
		gameStringHashtable = new Hashtable<String,GameString>();

		soundList = new ArrayList<Sound>();
		soundHashtable = new Hashtable<String,Sound>();

		musicList = new ArrayList<Music>();
		musicHashtable = new Hashtable<String,Music>();

		skillList = new ArrayList<Skill>();
		skillHashtable = new Hashtable<String,Skill>();



		selected_Map = 0;
		//getNumMaps() = 0;

		//getNumPalettes() = 0;
		selected_Palette = -1;

		//getNumSprites() = 0;
		selected_Sprite = 0;//-1;

		//getNumSpritePalettes() = 0;
		selected_SpritePalette = 0;


		open(filename, directory);

	}

	//===============================================================================================
	public void open(String fn, String directory)
	{//===============================================================================================


		ZipFile zip = null;

		try
		{
			zip=new ZipFile(new File(directory + fn));
		}
		catch(IOException e1)
		{
			e1.printStackTrace();
			return;
		}

		InputStream zin = null;


		List<String> stringList = null;

		try
		{
			ZipArchiveEntry z = zip.getEntry("Project.ini");
			if(z==null)z = zip.getEntry("_Project.txt");


			zin=zip.getInputStream(z);
			stringList = IOUtils.readLines(zin, StandardCharsets.UTF_8);
		}
		catch(ZipException e1)
		{
			e1.printStackTrace();
			return;
		}
		catch(IOException e1)
		{
			e1.printStackTrace();
			return;
		}

		try
		{
			zin.close();
		}
		catch(IOException e)
		{
			e.printStackTrace();
			return;
		}



		for(int i=0;i<stringList.size();i++)
		{
			String s = stringList.get(i);





			if(s.equals("Tileset"))
			{
				s = stringList.get(++i);
				int tiles = Integer.parseInt(s);
				tileset = new Tileset(tiles);
				String zipfilename = "Tiles.bin";
				int[] bytes = Utils.getIntArrayFromFileInZip(zip,zipfilename);
				tileset.initializeFromIntArray(bytes);
			}

			if(s.equals("TilesetPalettes"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					String zipfilename = s;
					byte[] bytes = Utils.getByteArrayFromFileInZip(zip,"TilesetPalette_"+zipfilename+".bin");
					addPalette(new TilesetPalette(zipfilename,bytes));
					s = stringList.get(++i);
				}
			}

			if(s.equals("SpritePalettes"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					String zipfilename = s;
					byte[] bytes = Utils.getByteArrayFromFileInZip(zip,"SpritePalette_"+zipfilename+".bin");
					addSpritePalette(new SpritePalette(zipfilename,bytes));
					s = stringList.get(++i);
				}
			}

			if(s.equals("Sprites"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("SPRITE:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					SpriteData data = new SpriteData();
					data.initFromString(s);


					ZipArchiveEntry z = zip.getEntry("Sprite_"+data.name()+".bin");
					if(z==null){s = stringList.get(++i);continue;}


					int[] intArray = Utils.getIntArrayFromFileInZip(zip,"Sprite_"+data.name()+".bin");
					Sprite sprite = new Sprite(data);
					sprite.initializeFromIntArray(intArray);
					s = stringList.get(++i);

				}
			}

			if(s.equals("Dialogues"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("DIALOGUE:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					DialogueData data = new DialogueData();
					data.initFromString(s);
					new Dialogue(data);
					s = stringList.get(++i);
				}
			}

//			if(s.equals("Events"))
//			{
//				s = stringList.get(++i);
//				while(s.length()>1)
//				{
//					s = s.substring(s.indexOf("EVENT:"));
//					s = s.substring(s.indexOf(":"));//ID
//					s = s.substring(s.indexOf(":"));//name
//					EventData data = new EventData();
//					data.initFromString(s);
//					new Event(data);
//					s = stringList.get(++i);
//				}
//			}


			if(s.equals("Flags"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("FLAG:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					FlagData data = new FlagData();
					data.initFromString(s);
					new Flag(data);
					s = stringList.get(++i);
				}
			}

			if(s.equals("Skills"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("SKILL:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					SkillData data = new SkillData();
					data.initFromString(s);
					new Skill(data);
					s = stringList.get(++i);
				}
			}

			if(s.equals("GameStrings"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("GAMESTRING:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					GameStringData data = new GameStringData();
					data.initFromString(s);
					new GameString(data);
					s = stringList.get(++i);
				}
			}

			if(s.equals("Sounds"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("SOUND:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					SoundData data = new SoundData();
					data.initFromString(s);
					new Sound(data);
					s = stringList.get(++i);
				}
			}

			if(s.equals("Music"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("MUSIC:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					MusicData data = new MusicData();
					data.initFromString(s);
					new Music(data);
					s = stringList.get(++i);
				}
			}

			if(s.equals("Maps"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("MAP:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name

					MapData data = new MapData();
					data.initFromString(s);



					ZipArchiveEntry z = zip.getEntry("Map_"+data.name()+"_"+"0"+".bin");
					if(z==null){s = stringList.get(++i);continue;}


					Map m = new Map(data);
					//System.out.println(data.name);
					for(int l=0;l<MapData.layers;l++)
					{
						if(MapData.isTileLayer(l))
						{
							int[] intArray = Utils.getIntArrayFromFileInZip(zip,"Map_"+data.name()+"_"+l+".bin");
							m.initializeLayerFromIntArray(l,intArray);
						}
					}

					s = stringList.get(++i);

				}
			}

			if(s.equals("Cutscenes"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("CUTSCENEEVENT:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					EventData data = new EventData();
					data.initFromString(s);
					cutsceneEventList.add(new Event(data));
					s = stringList.get(++i);
				}
			}
		}


		try
		{
			zip.close();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

		selected_Map=0;
		selected_Palette=0;
		selected_Sprite=0;
		selected_SpritePalette=0;





		boolean cErr=false;

		//cache all loaded entity sprite images
		for(int m=0;m<Project.getNumMaps();m++)
		{

			Map map = Project.getMap(m);

			{



				//make doors, areas, lights, entities, etc.
				MapData data = map.getData();

				for(int i=0;i<data.doorDataList().size();i++)
				{
					DoorData doorData = data.doorDataList().get(i);

					Door door = Project.doorIndexHashtable.get(doorData.getTYPEIDString());
					if(door==null)new Door(map,doorData);
					else
					{
						if(door.map()!=map)
						{
							System.err.println("Door: "+door.name()+" with ID: "+door.id()+" found on two maps. Creating a unique Door for this map.");
							new Door(map,doorData);
						}
					}

				}




				for(int i=0;i<data.stateDataList().size();i++)
				{
					MapStateData mapStateData = data.stateDataList().get(i);

					MapState state = Project.stateIndexHashtable.get(mapStateData.getTYPEIDString());
					if(state==null)new MapState(map,mapStateData);
					else
					{
						if(state.map()!=map)
						{
							System.err.println("MapState: "+state.name()+" with ID: "+state.id()+" found on two maps. Creating a unique MapState for this map.");
							new MapState(map,mapStateData);
						}
					}
				}
			}





			for(int s=0;s<map.getNumStates();s++)
			{

				MapState state = map.getState(s);

				MapStateData data = state.getData();

				for(int i=0;i<data.areaDataList().size();i++)
				{
					AreaData areaData = data.areaDataList().get(i);

					Area area = Project.areaIndexHashtable.get(areaData.getTYPEIDString());
					if(area==null)new Area(map,state,areaData);
					else
					{
						if(area.map()!=map||area.state()!=state)
						{
							System.err.println("Area: "+area.name()+" with ID: "+area.id()+" found on two maps or states. Creating a unique Area for this state.");
							new Area(map,state,areaData);
						}
					}
				}

				for(int i=0;i<data.entityDataList().size();i++)
				{
					EntityData entityData = data.entityDataList().get(i);

					Entity entity = Project.entityIndexHashtable.get(entityData.getTYPEIDString());
					if(entity==null)new Entity(map,state,entityData);
					else
					{
						if(entity.map()!=map||entity.state()!=state)
						{
							System.err.println("Entity: "+entity.name()+" with ID: "+entity.id()+" found on two maps or states. Creating a unique Entity for this state.");
							new Entity(map,state,entityData);
						}
					}
				}

				for(int i=0;i<data.lightDataList().size();i++)
				{
					LightData lightData = data.lightDataList().get(i);

					Light light = Project.lightIndexHashtable.get(lightData.getTYPEIDString());
					if(light==null)new Light(map,state,lightData);
					else
					{
						if(light.map()!=map||light.state()!=state)
						{
							System.err.println("Light: "+light.name()+" with ID: "+light.id()+" found on two maps or states. Creating a unique Light for this state.");
							new Light(map,state,lightData);
						}
					}
				}














				//set sprite
				for(int e=0;e<map.getState(s).getNumEntities();e++)
				{
					Entity entity = map.getState(s).getEntity(e);
					if(entity.getSprite()==null && Project.getSpriteByName(entity.spriteName())!=null)
					{
							entity.setSprite(Project.getSpriteByName(entity.spriteName()));

							entity.frameTimer = new Timer(100,EditorMain.mapCanvas);
							entity.startAnimationTimer = new Timer(100,EditorMain.mapCanvas);

							entity.getImage();
					}
					else
					{
						System.err.println("Could not find sprite:"+entity.spriteName() + " for entity:"+entity.name());
					}

					if(entity.eventData()!=null)Project.getEventByID(entity.eventData().id()).setName(entity.map().name()+"."+entity.name());
				}




				//set all warp areas to the default state, since they are visible in all states.

				for(int e=0;e<map.getState(s).getNumAreas();e++)
				{
					Area area = map.getState(s).getArea(e);
					//if(area.isWarpArea())area.state(area.map().getDefaultMapStateCreateIfNotExist());
					if(area.eventData()!=null)
					{

						Event event = Project.getEventByID(area.eventData().id());
						event.setName(area.map().name()+"."+area.name());
						if(area.isWarpArea())
						{
							if(event.text().equals("{}"))event.setText(Area.DEFAULT_WARP_EVENT_STRING);

							if(event.text().equals(Area.DEFAULT_AREA_EVENT_STRING))event.setText(Area.DEFAULT_WARP_EVENT_STRING);

							if(event.text().contains("enterThisWarp")==false)System.err.println("WarpArea: "+area.name()+" on Map: "+map.name()+" does not have enterThisWarp in the event.");
						}
					}
					else
					{
						if(area.isWarpArea())area.createDefaultWarpAreaEvent();
					}

				}


			}





			//set door sprite
			for(int d=0;d<map.getNumDoors();d++)
			{
				Door door = map.getDoor(d);
				if(door.getSprite()==null && Project.getSpriteByName(door.spriteName())!=null)
				{
					door.setSprite(Project.getSpriteByName(door.spriteName()));

				}
				else
				{
					System.err.println("Could not find sprite:"+door.spriteName() + " for door:"+door.name());
				}

				if(door.eventData()!=null)
				{
					Event e = Project.getEventByID(door.eventData().id());
					e.setName(door.map().name()+"."+door.name());
					if(e.text().equals("{}"))e.setText(Door.DEFAULT_DOOR_EVENT_STRING);

					if(e.text().contains("enterThisDoor")==false)System.err.println("Door: "+door.name()+" on Map: "+map.name()+" does not have enterThisDoor in the event.");

				}
				else door.createDefaultEvent();
			}

			//set door connections
//			for(int d=0;d<map.getNumDoors();d++)
//			{
//				Door door = map.getDoor(d);
//
//				for(int i=0;i<door.tempLoadingConnectionStringList.size();i++)
//				{
//					String connection = door.tempLoadingConnectionStringList.get(i);
//
//					GameObject mo = Project.getMapObjectByTYPEIDName(connection);
//					if(mo==null){System.err.println("Could not create connection:"+connection+" in Door:"+door.getLongTypeName());cErr=true;}
//					else door.connectionList.add(mo);
//
//				}
//
//				GameObject mo = Project.getMapObjectByTYPEIDName(door.tempLoadingDestString);
//				if(mo==null){System.err.println("Could not find destination:"+door.tempLoadingDestString+" in Door:"+door.getLongTypeName());cErr=true;}
//				else door.destination = (Door) mo;
//			}




			//fix event names that got mangled when we renamed or duplicated maps.
//			map.renameAllEventsToName();
//
//
//
//
//			//remove any map load events that refer to a state that doesnt exist, this shouldnt happen anymore but it happened for maps that i duplicated.
//			for(int i=0;i<map.mapEventList.size();i++)
//			{
//				Event e = map.mapEventList.get(i);
//				if(e.text.contains("loadMapState("))
//				{
//					String t = e.text.substring(e.text.indexOf("loadMapState(STATE."));
//					t = t.substring(t.indexOf(".")+1);
//
//					int stateID = Integer.parseInt(t.substring(0, t.indexOf(")")));
//
//					boolean found = false;
//					for(int s = 0; s<map.getNumStates();s++)
//					{
//						if(map.getState(s).id==stateID)found=true;
//					}
//
//					if(found==false)
//					{
//						map.mapEventList.remove(i);
//						i=-1;
//						System.err.println("Removed loadMapState Event for State that doesn't exist in map:"+map.getName());
//					}
//				}
//
//			}


			//look for a LoadDefaultState event in map, if doesnt exist, add it.

			boolean loadEventExists = false;
			for(int i=0;i<map.getNumEvents();i++)
			{
				Event e = map.getEvent(i);

				if(
					e.name().contains("LoadDefaultState")==true
					||e.name().contains("loadDefaultState")==true
					||e.name().contains("LoadDefaultMapState")==true
					||e.name().contains("loadDefaultMapState")==true
					||e.name().contains("Load")==true
				)
				{
					loadEventExists=true;
					e.setName(map.name()+"."+Map.DEFAULT_LOAD_EVENT_NAME);//uniform names
				}



			}

			if(loadEventExists==false)
			{
				map.addDefaultLoadMapStateEvent();
				System.err.println("Added default loadMapState Event for map:"+map.name());
			}



			//TODO: should add default events to doors, warps if they don't exist!
			//where else do I do this???

		}







	//remove any map load events that refer to a state that doesnt exist, this shouldnt happen anymore but it happened for maps that i duplicated.
	for(int i=0;i<Project.eventList.size();i++)
	{
		Event event = Project.eventList.get(i);

		if(event.text().contains("STATE."))
		{
			String t = event.text().substring(event.text().indexOf("STATE."));
			t = t.substring(t.indexOf(".")+1);

			int stateID = Integer.parseInt(t.substring(0, t.indexOf(")")));

			boolean found = false;

			for(int m=0;m<Project.getNumMaps();m++)
			{
				Map map = Project.getMap(m);

				for(int s = 0; s<map.getNumStates();s++)
				{
					if(map.getState(s).id()==stateID)found=true;
				}
			}

			if(found==false)
			{
				System.err.println("Event ID "+event.id()+" references a STATE that doesn't exist!");
			}
		}

	}





		//we have to fill the map event list with the event objects from the stored ID list we made on load.
		//we can't load them when we load the map because they aren't loaded yet.
		//DONE: i could potentially output all the objects FIRST and prevent this!
//		for(int m=0;m<Project.getNumMaps();m++)
//		{
//			Map map = Project.getMap(m);
//
//			for(int i=0;i<map.ONLOADeventIDList.size();i++)
//			{
//				Event e = Project.getEventByID(map.ONLOADeventIDList.get(i).intValue());
//				if(e!=null)map.eventList.add(e);
//				else System.err.println("null event id");
//			}
//
//		}




		//one time hack for adding default nodes to existing events.

//		for(int i=0;i<Project.areaIndexList.size();i++)
//		{
//			Area a = Project.areaIndexList.get(i);
//
//			if(a.eventID!=-1)
//			{
//				Event e = Project.getEventByID(a.eventID);
//
//				e.text = "{if(isPlayerTouchingThisArea() == TRUE)"+e.text+"}";
//
//			}
//		}
//
//
		for(int i=0;i<Project.entityIndexList.size();i++)
		{
			Entity a = Project.entityIndexList.get(i);
			if(a.name().startsWith("No Name")){System.out.println("Set Entity name from "+a.name()+" to nothing.");a.setName("");}

//			if(a.eventID!=-1)
//			{
//				Event e = Project.getEventByID(a.eventID);
//
//				e.text = "{if(isPlayerTouchingThisEntity() == TRUE)"+e.text+"}";
//
//			}
		}
//
//		for(int i=0;i<Project.doorIndexList.size();i++)
//		{
//			Door a = Project.doorIndexList.get(i);
//
//			if(a.eventID!=-1)
//			{
//				Event e = Project.getEventByID(a.eventID);
//
//				e.text = "{if(isPlayerWalkingIntoThisDoor() == TRUE)"+e.text+"}";
//
//			}
//		}
//
		for(int i=0;i<Project.getNumSprites();i++)
		{
			Sprite a = Project.getSprite(i);

			if(a.displayName().contains("No Name")){System.out.println("Set Sprite displayName from "+a.displayName()+" to nothing.");a.setDisplayName("");}

//			if(a.eventID!=-1)
//			{
//				Event e = Project.getEventByID(s.eventID);
//
//				e.text = "{if(isPlayerTouchingAnyEntityUsingThisSprite() == TRUE)"+e.text+"}";
//
//			}
		}


		System.out.println(""+Tileset.num_Tiles+" Tiles");
		System.out.println(""+Project.getNumMaps()+" Maps");
		System.out.println(""+Project.stateIndexList.size()+" States");
		System.out.println(""+Project.getNumSprites()+" Sprites");
		System.out.println(""+Project.lightIndexList.size()+" Lights");
		System.out.println(""+Project.areaIndexList.size()+" Areas");
		System.out.println(""+Project.entityIndexList.size()+" Entities");
		System.out.println(""+Project.doorIndexList.size()+" Doors");
		System.out.println(""+Project.dialogueList.size()+" Dialogues");
		System.out.println(""+Project.eventList.size()+" Events");
		System.out.println(""+Project.flagList.size()+" Flags");
		System.out.println(""+Project.skillList.size()+" Skills");
		System.out.println(""+Project.gameStringList.size()+" GameStrings");
		System.out.println(""+Project.soundList.size()+" Sound");
		System.out.println(""+Project.musicList.size()+" Music");


		if(cErr==true)
		{
			String s = "There was an error creating connections or destinations. Review the console history to fix them or they will be lost when you save.";
			EditorMain.infoLabel.setTextError(s);
			System.err.println(s);
		}


	}

	//===============================================================================================
	public void merge(String fn, String directory)
	{//===============================================================================================
		ZipFile zip = null;
		try
		{
			zip=new ZipFile(new File(directory + fn));
		}
		catch(IOException e1)
		{
			e1.printStackTrace();
			return;
		}

		InputStream zin = null;
		List<String> stringList = null;

		try
		{
			ZipArchiveEntry z = zip.getEntry("Project.ini");
			if(z==null)z = zip.getEntry("_Project.txt");
			zin=zip.getInputStream(z);
			stringList = IOUtils.readLines(zin, StandardCharsets.UTF_8);
		}
		catch(Exception e1)
		{
			e1.printStackTrace();
			return;
		}

		try{zin.close();}catch(IOException e){e.printStackTrace();}

		Tileset incomingTileset = null;
		TilesetPalette incomingPalette = null;
		int tileOffset = tileset.num_Tiles;

		for(int i=0;i<stringList.size();i++)
		{
			String s = stringList.get(i);

			if(s.equals("Tileset"))
			{
				s = stringList.get(++i);
				int tiles = Integer.parseInt(s);
				incomingTileset = new Tileset(tiles);
				String zipfilename = "Tiles.bin";
				int[] bytes = Utils.getIntArrayFromFileInZip(zip,zipfilename);
				incomingTileset.initializeFromIntArray(bytes);
			}

			if(s.equals("TilesetPalettes"))
			{
				s = stringList.get(++i);
				boolean firstPalette = true;
				while(s.length()>1)
				{
					String zipfilename = s;
					byte[] bytes = Utils.getByteArrayFromFileInZip(zip,"TilesetPalette_"+zipfilename+".bin");
					TilesetPalette p = new TilesetPalette(zipfilename,bytes);
					
					if(firstPalette) {
						incomingPalette = p;
						firstPalette = false;
					}
					
					addPalette(p);
					s = stringList.get(++i);
				}
				
				if(incomingTileset != null && incomingPalette != null) {
					mergeTileset(incomingTileset, incomingPalette);
				}
			}

			if(s.equals("SpritePalettes"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					String zipfilename = s;
					byte[] bytes = Utils.getByteArrayFromFileInZip(zip,"SpritePalette_"+zipfilename+".bin");
					addSpritePalette(new SpritePalette(zipfilename,bytes));
					s = stringList.get(++i);
				}
			}

			if(s.equals("Sprites"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("SPRITE:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					SpriteData data = new SpriteData();
					data.initFromString(s);

					ZipArchiveEntry z = zip.getEntry("Sprite_"+data.name()+".bin");
					if(z==null){s = stringList.get(++i);continue;}

					int[] intArray = Utils.getIntArrayFromFileInZip(zip,"Sprite_"+data.name()+".bin");
					Sprite sprite = new Sprite(data);
					sprite.initializeFromIntArray(intArray);
					s = stringList.get(++i);
				}
			}

			if(s.equals("Dialogues"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("DIALOGUE:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					DialogueData data = new DialogueData();
					data.initFromString(s);
					new Dialogue(data);
					s = stringList.get(++i);
				}
			}

			if(s.equals("Flags"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("FLAG:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					FlagData data = new FlagData();
					data.initFromString(s);
					new Flag(data);
					s = stringList.get(++i);
				}
			}

			if(s.equals("Skills"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("SKILL:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					SkillData data = new SkillData();
					data.initFromString(s);
					new Skill(data);
					s = stringList.get(++i);
				}
			}

			if(s.equals("GameStrings"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("GAMESTRING:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					GameStringData data = new GameStringData();
					data.initFromString(s);
					new GameString(data);
					s = stringList.get(++i);
				}
			}

			if(s.equals("Sounds"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("SOUND:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					SoundData data = new SoundData();
					data.initFromString(s);
					new Sound(data);
					s = stringList.get(++i);
				}
			}

			if(s.equals("Music"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("MUSIC:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					MusicData data = new MusicData();
					data.initFromString(s);
					new Music(data);
					s = stringList.get(++i);
				}
			}

			if(s.equals("Maps"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("MAP:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name

					MapData data = new MapData();
					data.initFromString(s);

					ZipArchiveEntry z = zip.getEntry("Map_"+data.name()+"_"+"0"+".bin");
					if(z==null){s = stringList.get(++i);continue;}

					Map m = new Map(data);
					for(int l=0;l<MapData.layers;l++)
					{
						if(MapData.isTileLayer(l))
						{
							int[] intArray = Utils.getIntArrayFromFileInZip(zip,"Map_"+data.name()+"_"+l+".bin");
							m.initializeLayerFromIntArray(l,intArray);
						}
					}
					
					m.shiftTileIndices(tileOffset);

					s = stringList.get(++i);
				}
			}

			if(s.equals("Cutscenes"))
			{
				s = stringList.get(++i);
				while(s.length()>1)
				{
					s = s.substring(s.indexOf("CUTSCENEEVENT:"));
					s = s.substring(s.indexOf(":"));//ID
					s = s.substring(s.indexOf(":"));//name
					EventData data = new EventData();
					data.initFromString(s);
					cutsceneEventList.add(new Event(data));
					s = stringList.get(++i);
				}
			}
		}

		try
		{
			zip.close();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		
		// Re-cache entities
		for(int m=0;m<Project.getNumMaps();m++)
		{
			Map map = Project.getMap(m);
			for(int s=0;s<map.getNumStates();s++)
			{
				for(int e=0;e<map.getState(s).getNumEntities();e++)
				{
					com.bobsgame.editor.Project.Map.Entity entity = map.getState(s).getEntity(e);
					if(entity.getSprite()==null && Project.getSpriteByName(entity.spriteName())!=null)
					{
							entity.setSprite(Project.getSpriteByName(entity.spriteName()));
							entity.frameTimer = new Timer(100,EditorMain.mapCanvas);
							entity.startAnimationTimer = new Timer(100,EditorMain.mapCanvas);
							entity.getImage();
					}
				}
				for(int d=0;d<map.getNumDoors();d++)
				{
					com.bobsgame.editor.Project.Map.Door door = map.getDoor(d);
					if(door.getSprite()==null && Project.getSpriteByName(door.spriteName())!=null)
					{
						door.setSprite(Project.getSpriteByName(door.spriteName()));
					}
				}
			}
		}
	}

	public void mergeTileset(Tileset incoming, TilesetPalette incomingPalette) {
		TilesetPalette currentPalette = getPalette(0);
		int startTile = tileset.num_Tiles;
		tileset.setNumTiles(tileset.num_Tiles + incoming.num_Tiles);
		
		for(int t = 0; t < incoming.num_Tiles; t++) {
			if(incoming.isTileBlank(t)) continue;
			
			int newTileIndex = startTile + t;
			
			for(int y=0; y<8; y++) {
				for(int x=0; x<8; x++) {
					int oldColorIndex = incoming.getPixel(t, x, y);
					if(oldColorIndex == 0) { // Transparent
						tileset.setPixel(newTileIndex, x, y, 0);
						continue;
					}
					
					java.awt.Color c = incomingPalette.getColor(oldColorIndex);
					int newColorIndex = currentPalette.getColorIfExistsOrAddColor(c.getRed(), c.getGreen(), c.getBlue(), 0);
					
					if(newColorIndex == -1) {
						newColorIndex = currentPalette.addColor(c.getRed(), c.getGreen(), c.getBlue());
					}
					
					tileset.setPixel(newTileIndex, x, y, newColorIndex);
				}
			}
		}
		tileset.buildTileImages();
	}



	//===============================================================================================
	public void save(String filepath, String fn)
	{//===============================================================================================


		clearEventsListsForProjectSave();

		try
		{
			//create a ZipOutputStream to zip the data to
			ZipOutputStream zos = new ZipOutputStream(new FileOutputStream(filepath+".zip"));
			//assuming that there is a directory named inFolder



			//--------------------------------------
			//output tileset byte file as entry in zip
			//--------------------------------------
			try
			{
				zos.putNextEntry(new ZipEntry("Tiles.bin"));
			}
			catch(Exception e)
			{
				System.err.println("Error putting Tiles.bin into zip.");
			}

			zos.write(tileset.getAsByteArray());



			//output each palette as entry in zip
			//just as "palettex.bin"
			//record each name and size
			for(int i=0;i<getNumPalettes();i++)
			{
				TilesetPalette pal = getPalette(i);
				try
				{
					zos.putNextEntry(new ZipEntry("TilesetPalette_"+pal.name+".bin"));
				}
				catch(Exception e)
				{
					System.err.println("Error putting TilesetPalette: "+pal.name+" into zip.");
				}

				zos.write(pal.getAsByteArray());
			}

			//output each map layer as entry in zip
			//"mapname_layer.bin"

			for(int m = 0; m < getNumMaps(); m++)
			{
				Map map = getMap(m);

				for(int l = 0; l < MapData.layers; l++)
				{
					if(MapData.isTileLayer(l))
					{
						try
						{
							zos.putNextEntry(new ZipEntry("Map_"+map.name()+"_"+l+".bin"));
						}
						catch(Exception e)
						{
							System.err.println("Error putting Map Layer: "+map.name()+"_"+l+" into zip.");

						}

						zos.write(map.getLayerAsByteArray(l));
					}
				}
			}

			//output each sprite as entry in zip
			//"spritename.bin"
			for(int i=0;i<getNumSprites();i++)
			{
				Sprite sprite = getSprite(i);
				try
				{
					zos.putNextEntry(new ZipEntry("Sprite_"+sprite.name()+".bin"));
				}
				catch(Exception e)
				{
					System.err.println("Error putting sprite: "+sprite.name()+" into zip.");
				}

				zos.write(sprite.getAsByteArray());
			}


			//output each spritepalette as entry in zip
			//"spritepal.bin"
			for(int i=0;i<getNumSpritePalettes();i++)
			{
				SpritePalette spal = getSpritePalette(i);
				try
				{
					zos.putNextEntry(new ZipEntry("SpritePalette_"+spal.name+".bin"));
				}
				catch(Exception e)
				{
					System.err.println("Error putting sprite palette: "+spal.name+" into zip.");
				}

				zos.write(spal.getAsByteArray());
			}



			try
			{
				zos.putNextEntry(new ZipEntry("_Project.txt"));
			}
			catch(Exception e)
			{
				System.err.println("Error putting _Project.txt into zip.");
			}




			PrintWriter pw;
			pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(zos)));

			pw.println("bgEdit v0.1.2");
			pw.println();
			pw.println("Tileset");
			pw.println(Tileset.num_Tiles);
			pw.println();

			pw.println("TilesetPalettes");
			for(int p = 0; p < getNumPalettes(); p++)
			{
				TilesetPalette pal = getPalette(p);
				pw.println(pal.name);
			}
			pw.println();

			pw.println("SpritePalettes");
			for(int p = 0; p < getNumSpritePalettes(); p++)
			{
				SpritePalette pal = getSpritePalette(p);
				pw.println(pal.name);
			}
			pw.println();


			pw.println("Sprites");
			for(int p = 0; p < getNumSprites(); p++)
			{
				Sprite o = getSprite(p);
				pw.println("SPRITE:"+o.id()+":"+o.name()+":"+o.getData().toString());
			}
			pw.println();


			pw.println("Dialogues");
			for(int i=0;i<dialogueList.size();i++)
			{
				Dialogue o = dialogueList.get(i);
				pw.println("DIALOGUE:"+o.id()+":"+o.name()+":"+o.getData().toString());
			}
			pw.println();


//			pw.println("Events");
//			for(int i=0;i<eventList.size();i++)
//			{
//				Event o = eventList.get(i);
//				pw.println("EVENT:"+o.id()+":"+o.name()+":"+o.getData().toString());
//			}
//			pw.println();



			pw.println("Flags");
			for(int i=0;i<flagList.size();i++)
			{
				Flag o = flagList.get(i);
				pw.println("FLAG:"+o.id()+":"+o.name()+":"+o.getData().toString());
			}
			pw.println();

			pw.println("Skills");
			for(int i=0;i<skillList.size();i++)
			{
				Skill o = skillList.get(i);
				pw.println("SKILL:"+o.id()+":"+o.name()+":"+o.getData().toString());
			}
			pw.println();


			pw.println("GameStrings");
			for(int i=0;i<gameStringList.size();i++)
			{
				GameString o = gameStringList.get(i);
				pw.println("GAMESTRING:"+o.id()+":"+o.name()+":"+o.getData().toString());
			}
			pw.println();

			pw.println("Sounds");
			for(int i=0;i<soundList.size();i++)
			{
				Sound o = soundList.get(i);
				pw.println("SOUND:"+o.id()+":"+o.name()+":"+o.getData().toString());
			}
			pw.println();

			pw.println("Music");
			for(int i=0;i<musicList.size();i++)
			{
				Music o = musicList.get(i);
				pw.println("MUSIC:"+o.id()+":"+o.name()+":"+o.getData().toString());
			}
			pw.println();

			pw.println("Maps");
			for(int m = 0; m < getNumMaps(); m++)
			{
				Map o = getMap(m);
				pw.println("MAP:"+o.id()+":"+o.name()+":"+o.getData().toString());
			}
			pw.println();







			pw.println("Cutscenes");
			for(int i = 0; i < cutsceneEventList.size(); i++)
			{
				Event o = cutsceneEventList.get(i);
				pw.println("CUTSCENEEVENT:"+o.id()+":"+o.name()+":"+o.getData().toString());
			}
			pw.println();


			pw.println(""+Tileset.num_Tiles+" Tiles");
			pw.println(""+getNumMaps()+" Maps");
			pw.println(""+stateIndexList.size()+" States");
			pw.println(""+getNumSprites()+" Sprites");
			pw.println(""+lightIndexList.size()+" Lights");
			pw.println(""+areaIndexList.size()+" Areas");
			pw.println(""+entityIndexList.size()+" Entities");
			pw.println(""+doorIndexList.size()+" Doors");
			pw.println(""+dialogueList.size()+" Dialogues");
			pw.println(""+eventList.size()+" Events");
			pw.println(""+flagList.size()+" Flags");
			pw.println(""+skillList.size()+" Skills");
			pw.println(""+gameStringList.size()+" GameStrings");
			pw.println(""+soundList.size()+" Sound");
			pw.println(""+musicList.size()+" Music");

			System.out.println(""+Tileset.num_Tiles+" Tiles");
			System.out.println(""+getNumMaps()+" Maps");
			System.out.println(""+stateIndexList.size()+" States");
			System.out.println(""+getNumSprites()+" Sprites");
			System.out.println(""+lightIndexList.size()+" Lights");
			System.out.println(""+areaIndexList.size()+" Areas");
			System.out.println(""+entityIndexList.size()+" Entities");
			System.out.println(""+doorIndexList.size()+" Doors");
			System.out.println(""+dialogueList.size()+" Dialogues");
			System.out.println(""+eventList.size()+" Events");
			System.out.println(""+flagList.size()+" Flags");
			System.out.println(""+skillList.size()+" Skills");
			System.out.println(""+gameStringList.size()+" GameStrings");
			System.out.println(""+soundList.size()+" Sound");
			System.out.println(""+musicList.size()+" Music");

			pw.close();


			//close the stream
			zos.close();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		//handle exception
		}



	}



	//===============================================================================================
	public void saveAllMapsPNGForEachLayer()
	{//===============================================================================================

		String dirpath = EditorMain.getDesktopTempDirPath();

		for(int m = 0; m < getNumMaps(); m++)
		{
			getMap(m).saveMapPNGForEachLayer(dirpath);
		}
		EditorMain.mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();

		EditorMain.infoLabel.setTextSuccess("Saved All Maps to PNGs 0,1,2,3,4,5,6,7,8,9,10: " + dirpath);
	}
	//===============================================================================================
	public void saveCurrentMapPNGForEachLayer()
	{//===============================================================================================
		String dirpath = EditorMain.getDesktopTempDirPath();

		getSelectedMap().saveMapPNGForEachLayer(dirpath);
		EditorMain.mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();

		EditorMain.infoLabel.setTextSuccess("Saved Current Map to PNGs 0,1,2,3,4,5,6,7,8,9,10: " + dirpath);
	}

	//===============================================================================================
	public void saveAllMapsCombinedLayersToPNG()
	{//===============================================================================================
		String dirpath = EditorMain.getDesktopTempDirPath();


		for(int m = 0; m < getNumMaps(); m++)
		{
			getMap(m).saveMapCombinedLayersToPNG(dirpath);
		}
		EditorMain.mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();

		EditorMain.infoLabel.setTextSuccess("Saved All Maps to PNGs 01345,678: " + dirpath);
	}
	//===============================================================================================
	public void saveCurrentMapCombinedLayersToPNG()
	{//===============================================================================================
		String dirpath = EditorMain.getDesktopTempDirPath();

		getSelectedMap().saveMapCombinedLayersToPNG(dirpath);
		EditorMain.mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();

		EditorMain.infoLabel.setTextSuccess("Saved Current Map to PNGs 01345,678: " + dirpath);
	}

	//===============================================================================================
	public void saveAllMapsCombinedLayersToHQ2XPNG()
	{//===============================================================================================
		String dirpath = EditorMain.getDesktopTempDirPath();

		for(int m = 0; m < getNumMaps(); m++)
		{
			getMap(m).saveMapCombinedLayersToHQ2XPNG(dirpath);
		}
		EditorMain.mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();

		EditorMain.infoLabel.setTextSuccess("Saved All Maps to HQ2X PNGs 01345,678: " + dirpath);
	}
	//===============================================================================================
	public void saveCurrentMapCombinedLayersToHQ2XPNG()
	{//===============================================================================================
		String dirpath = EditorMain.getDesktopTempDirPath();

		getSelectedMap().saveMapCombinedLayersToHQ2XPNG(dirpath);
		EditorMain.mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();

		EditorMain.infoLabel.setTextSuccess("Saved Current Map to HQ2X PNGs 01345,678: " + dirpath);
	}




	//===============================================================================================
	public void moveMapDown()
	{//===============================================================================================

		//if we're not the last map
		if(selected_Map>=getNumMaps()-1||selected_Map<0)return;

		getMap(selected_Map).destroyLayerImages();

		//swap this map and the next one
		Map temp = getMap(selected_Map);
		mapList.remove(selected_Map);
		mapList.add(selected_Map+1, temp);


		//set current map the next one
		selected_Map = selected_Map+1;




	}

	//===============================================================================================
	public void moveMapUp()
	{//===============================================================================================
		//if we're not the first map
		if(selected_Map<=0)return;

		getMap(selected_Map).destroyLayerImages();

		//swap this map and the next one
		Map temp = getMap(selected_Map-1);
		mapList.remove(selected_Map-1);
		mapList.add(selected_Map, temp);

		//set current map the next one
		selected_Map = selected_Map-1;


	}

	//===============================================================================================
	public static void insertNewMap()
	{//===============================================================================================

		Map m = new Map("Map" + Project.getNumMaps(), 40, 30);//this adds it to the map linked list automatically.

		m.addDefaultMapState();
		m.addDefaultLoadMapStateEvent();

		mapList.remove(m); //remove it so we can add it in the right place.

		mapList.add(selected_Map+1,m);//add new map after current map

		if(selected_Map != -1)
		{
			getSelectedMap().destroyLayerImages();
		}
		selected_Map = selected_Map+1;


	}

	//===============================================================================================
	public static void appendNewMap()
	{//===============================================================================================


		Map map = new Map("Map" + Project.getNumMaps(), 40, 30); //adds to map linked list automatically, at the end.

		map.addDefaultMapState();
		map.addDefaultLoadMapStateEvent();

		if(selected_Map != -1)
		{
			getSelectedMap().destroyLayerImages();
		}
		selected_Map = mapList.size()-1;
	}



	//===============================================================================================
	public void duplicateMap()
	{//===============================================================================================


		Map m = getSelectedMap().duplicate();//this adds it to the map linked list automatically.

		mapList.remove(m); //remove it so we can add it in the right place.

		mapList.add(selected_Map+1,m);//add new map after current map


		getMap(selected_Map).destroyLayerImages();
		selected_Map = selected_Map+1;



	}



	//===============================================================================================
	public void deleteMap()
	{//===============================================================================================

		if(getNumMaps() <= 1)
		{
			return;
		}

		if(selected_Map > -1)
		{
			getMap(selected_Map).destroyLayerImages();
		}


		mapList.remove(selected_Map);


		if(selected_Map>=getNumMaps())selected_Map=getNumMaps()-1;

	}

	//===============================================================================================
	public void setMapSize(int w, int h)
	{//===============================================================================================


		Map map = getSelectedMap();


//		//move the original
//		mapList.remove(oldMap);
//		mapHashtable.remove(oldMap.getIDString());
//
//
//		//make a new one with the same ID (adds to maplist)
//		Map m = new Map(oldMap.id,oldMap.getName(), w, h);
//
//		//remove and readd it in the right place in mapList
//		mapList.remove(m);
//		mapList.add(selected_Map,m);




		//rebuild the tile location data
		{
			int[][][] location = new int[MapData.layers][w][h];

			for(int l = 0; l < MapData.layers; l++)
			{
				if(MapData.isTileLayer(l))
				{
					for(int y = 0; y < map.hT() && y < h; y++)
					{
						for(int x = 0; x < map.wT() && x < w; x++)
						{
							location[l][x][y] = map.getTileIndex(l, x, y);
							//m.setTileIndex(l, x, y, oldMap.getTileIndex(l, x, y));
						}
					}
				}
			}

			map.layerTileIndex = location;
		}


		//remove any doors that are outside of our new size.

		for(int i=0;i<map.getNumDoors();i++)
		{
			Door door = map.getDoor(i);

			if(door.xP()>=w*8||door.yP()>=h*8){map.removeDoor(i);i=-1;}
		}

		//remove any areas, lights, entities that are outside our new size

		for(int i=0;i<map.getNumStates();i++)
		{
			MapState state = map.getState(i);

			for(int n=0;n<state.getNumAreas();n++)
			{
				Area area = state.getArea(n);
				if(area.xP()>=w*8||area.yP()>=h*8){state.removeArea(n);n=-1;}
			}

			for(int n=0;n<state.getNumLights();n++)
			{
				Light light = state.getLight(n);
				if(light.xP()>=w*8||light.yP()>=h*8){state.removeLight(n);n=-1;}
			}

			for(int n=0;n<state.getNumEntities();n++)
			{
				Entity entity = state.getEntity(n);
				if(entity.xP()>=w*8||entity.yP()>=h*8){state.removeEntity(n);n=-1;}
			}

		}

		map.setWidthTiles(w);
		map.setHeightTiles(h);


//		m.doorList = oldMap.doorList;
//		m.stateList = oldMap.stateList;
//		m.mapEventList = oldMap.mapEventList;
//		m.mapNote = oldMap.mapNote;
//		m.isOutside = oldMap.isOutside;
//		m.maxRandoms = oldMap.maxRandoms;




		map.destroyLayerImages();	// rebuild the mapImage





		EditorMain.mapCanvas.setSizedoLayout();

		EditorMain.mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();

	}




	//===============================================================================================
	static public int getNumMaps()
	{//===============================================================================================
		return mapList.size();
	}

	//===============================================================================================
	static public Map getMap(int i)
	{//===============================================================================================

		return mapList.get(i);

	}

	//===============================================================================================
	public static Map getMapByName(String mapName)
	{//===============================================================================================

		for(int i=0;i<mapList.size();i++)
		{
			if(mapList.get(i).name().equals(mapName))return mapList.get(i);
		}
		return null;
	}

	//===============================================================================================
	public String getSelectedMapName()
	{//===============================================================================================
		return getMap(selected_Map).name();
	}

	//===============================================================================================
	public static Map getSelectedMap()
	{//===============================================================================================
		if(getNumMaps() > 0)
		{
			return getMap(selected_Map);
		}
		else
		{
			return null;
		}
	}

	//===============================================================================================
	public static void setSelectedMapIndex(int i)
	{//===============================================================================================
		if(i >= getNumMaps())
		{
			System.err.println("Tried to set selected map over limit");
			return;
		}

		if(selected_Map == i)
		{
			//System.err.println("Tried to set selected map to already selected value.");
			return;
		}

		if(selected_Map > -1)
		{
			getMap(selected_Map).destroyLayerImages();			// Free up memory
		}
		selected_Map = i;
	}

	//===============================================================================================
	public static int getSelectedMapIndex()
	{//===============================================================================================
		return selected_Map;
	}


	//===============================================================================================
	public static void swapTilesEveryMap(int tile, int newtile)
	{//===============================================================================================
		if(newtile>=Tileset.num_Tiles)
		{
			tileset.setNumTiles(newtile + 1);	// Increase the tileset size if the pixel to be set is outside current size
		}

		for(int m = 0; m < getNumMaps(); m++)
		{
			getMap(m).swapTilesOnMapEveryLayer(tile, newtile);
		}
	}


	//===============================================================================================
	public void countUsedTilesSelectedMap()
	{//===============================================================================================
		int vtilelist[] = new int[Tileset.num_Tiles];
		int vtilecount = 0;

		for(int l = 0; l < MapData.layers; l++)
		{
			if(MapData.isTileLayer(l))
			for(int x = 0; x < getSelectedMap().wT(); x++)
			{
				for(int y = 0; y < getSelectedMap().hT(); y++)
				{

					int v = 0;
					int foundtile = 0;
					for(v = 0; v < vtilecount; v++)
					{
						if(getSelectedMap().layerTileIndex[l][x][y] == vtilelist[v])
						{
							v = vtilecount + 1;
							foundtile = 1;
						}
					}
					if(foundtile != 1)
					{
						vtilelist[vtilecount] = getSelectedMap().layerTileIndex[l][x][y];
						vtilecount++;

					}
				}
			}

		}

		System.out.println("map " + getSelectedMap().name() + " has " + (vtilecount - 1) + " tiles");

	}

	//===============================================================================================
	public void countUsedTilesAllMaps()
	{//===============================================================================================
		int vtilelist[] = new int[Tileset.num_Tiles];
		int vtilecount = 0;
		for(int m = 0; m < getNumMaps(); m++)
		{
			for(int l = 0; l < MapData.layers; l++)
			{
				if(MapData.isTileLayer(l))
				for(int x = 0; x < getMap(m).wT(); x++)
				{
					for(int y = 0; y < getMap(m).hT(); y++)
					{

						int v = 0;
						int foundtile = 0;
						for(v = 0; v < vtilecount; v++)
						{
							if(getMap(m).layerTileIndex[l][x][y] == vtilelist[v])
							{
								v = vtilecount + 1;
								foundtile = 1;
							}
						}
						if(foundtile != 1)
						{
							vtilelist[vtilecount] = getMap(m).layerTileIndex[l][x][y];
							vtilecount++;

						}
					}
				}

			}
		}

		EditorMain.infoLabel.setTextSuccess("All maps have" + (vtilecount - 1) + " used tiles");

	}

	//===============================================================================================
	public void findLeastUsedTileOnSelectedMap(EditorMain E)
	{//===============================================================================================

		NumberDialog nd = new NumberDialog(E, "Times used (or less) to list/sort?");
		nd.text.setText("2");
		nd.show();

		int timeslimit = Integer.parseInt(nd.text.getText());

		YesNoWindow ynw = new YesNoWindow(new Frame(), "Move tiles used " + timeslimit + " or less to bottom?");
		ynw.setVisible(true);
		boolean movetobottom = ynw.result;

		int tilearray[] = new int[Tileset.num_Tiles];
		int tilearraycount = 0;

		int mintile = 0;
		int mintimes = 1000;

		int mx = 0;
		int my = 0;

		for(int t = Tileset.num_Tiles - 1; t > 0; t--)
		{
			//boolean used = false;
			boolean blank = tileset.isTileBlank(t);

			int times = 0;
			int tx = 0;
			int ty = 0;

			if(!blank)
			{
				for(int l = 0; l < MapData.layers; l++)
				{
					if(
							MapData.isTileLayer(l)
							&& l!=MapData.MAP_HIT_LAYER
							&& l!=MapData.MAP_CAMERA_BOUNDS_LAYER
							&& l!=MapData.MAP_SHADER_LAYER
					)
					{
						for(int y = 0; y < getMap(selected_Map).hT(); y++)
						{
							for(int x = 0; x < getMap(selected_Map).wT(); x++)
							{
								if(getMap(selected_Map).layerTileIndex[l][x][y] == t)
								{
									times++;
									tx = x;
									ty = y;
								}
							}
						}
					}
				}
			}

			if(times > 0 && times < mintimes)
			{
				mintile = t;
				mintimes = times;
				mx = tx;
				my = ty;
			}
			if(times > 0 && times <= timeslimit)
			{
				System.out.println("Tile " + t + " used " + times + " times at " + tx + "," + ty);
				tilearray[tilearraycount] = t;
				tilearraycount++;
			}
		}

		EditorMain.infoLabel.setTextSuccess("Tile " + mintile + " used " + mintimes + " times at " + mx + "," + my);

		EditorMain.tileCanvas.tileSelected = mintile;

		EditorMain.tileCanvas.scrollToSelectedTile();


		if(movetobottom)
		{

			EditorMain.tileCanvas.tileSelected = Tileset.num_Tiles;
			tileset.setNumTiles(Tileset.num_Tiles + 1 + tilearraycount);

			EditorMain.tileScrollPane.getHorizontalScrollBar().setValue(EditorMain.tileCanvas.getTileX(EditorMain.tileCanvas.tileSelected));
			EditorMain.tileScrollPane.getVerticalScrollBar().setValue(EditorMain.tileCanvas.getTileY(EditorMain.tileCanvas.tileSelected));
			//E.tileScrollPane.setScrollPosition(EditorMain.tileCanvas.getTileX(EditorMain.tileCanvas.tileSelected), EditorMain.tileCanvas.getTileY(EditorMain.tileCanvas.tileSelected));

			for(int x = 0; x < tilearraycount; x++)
			{

				//move tilearray[x] to tileSelected+x
				EditorMain.tileCanvas.moveTile(EditorMain.tileCanvas.tileSelected + x, tilearray[x]);

			}

		}

		EditorMain.mapCanvas.mapSelectionArea.setLocation(mx, my);
		EditorMain.mapCanvas.mapSelectionArea.setLocation2(mx + 1, my + 1);
		EditorMain.mapCanvas.repaint();

		EditorMain.tileCanvas.setSizedoLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.paintBuffer();
		EditorMain.tileCanvas.repaint();

	}

	//===============================================================================================
	public void findFirstMapWithSelectedTile(EditorMain E)
	{//===============================================================================================

		int m = 0;

		boolean done = false;

		for(m = 0; m < getNumMaps() && !done; m++)
		{

			for(int l = 0; l < MapData.layers && !done; l++)
			{
				if(
						MapData.isTileLayer(l)
						&&l!=MapData.MAP_HIT_LAYER
						&&l!=MapData.MAP_SHADER_LAYER
						&&l!=MapData.MAP_CAMERA_BOUNDS_LAYER
				)
				{
					for(int y = 0; y < getMap(m).hT() && !done; y++)
					{
						for(int x = 0; x < getMap(m).wT() && !done; x++)
						{
							if(getMap(m).layerTileIndex[l][x][y] == EditorMain.tileCanvas.tileSelected)
							{
								EditorMain.infoLabel.setTextSuccess("Tile first used on " + getMap(m).name() + " at " + x + "," + y + " Layer " + l);
								done = true;

								E.mapChoice.setSelectedIndex(m);
								//E.itemStateChanged(new ItemEvent(E.mapChoice,701,"",1));

								EditorMain.mapCanvas.mapSelectionArea.setLocation(x, y);
								EditorMain.mapCanvas.mapSelectionArea.setLocation2(x + 1, y + 1);
								EditorMain.mapCanvas.repaint();
							}
						}
					}
				}
			}
		}

		if(!done)
		{
			EditorMain.infoLabel.setTextSuccess("Tile not Used");
		}

	}

	//===============================================================================================
	public void createNewPalette(String n)
	{//===============================================================================================


		palette.add(new TilesetPalette(n));
		selected_Palette = getNumPalettes()-1;
		//getNumPalettes()++;
	}

	//===============================================================================================
	public void createNewPalette()
	{//===============================================================================================
		palette.add(new TilesetPalette("Palette" + getNumPalettes()));
		selected_Palette = getNumPalettes()-1;
		//getNumPalettes()++;
	}

	//===============================================================================================
	public void duplicatePalette()
	{//===============================================================================================
		palette.add(getPalette(selected_Palette).duplicate());
		selected_Palette = getNumPalettes()-1;
		//getNumPalettes()++;
	}

	//===============================================================================================
	public void addPalette(TilesetPalette p)
	{//===============================================================================================
		palette.add(p);
		selected_Palette = getNumPalettes()-1;
		//getNumPalettes()++;
		tileset.buildTileImages();
	}


	//===============================================================================================
	public void deletePalette()
	{//===============================================================================================

		if(getNumPalettes() <= 1)
		{
			return;
		}


		palette.remove(selected_Palette);

		tileset.buildTileImages();
	}

	//===============================================================================================
	static public int getNumPalettes()
	{//===============================================================================================
		return palette.size();
	}
	//===============================================================================================
	static public TilesetPalette getPalette(int i)
	{//===============================================================================================
		if(getNumPalettes() > 0)
		return palette.get(i);
		else return null;

	}
	//===============================================================================================
	public void renamePalette(String n)
	{//===============================================================================================
		if(getNumPalettes() > 0)
		getPalette(selected_Palette).rename(n);
		else System.err.println("No palettes to rename");
	}

	//===============================================================================================
	public String getSelectedPaletteName()
	{//===============================================================================================
		if(getNumPalettes() > 0)
		return getPalette(selected_Palette).name;
		else return null;
	}

	//===============================================================================================
	public static TilesetPalette getSelectedPalette()
	{//===============================================================================================
		if(getNumPalettes() > 0)
		return getPalette(selected_Palette);
		else return null;
	}

	//===============================================================================================
	public static int getSelectedPaletteIndex()
	{//===============================================================================================
		return selected_Palette;
	}

	//===============================================================================================
	public void setSelectedPaletteIndex(int i)
	{//===============================================================================================

		if(i >= getNumPalettes())
		{
			System.err.println("Tried to set selected palette over limit");
			return;
		}

		if(i >= selected_Palette)
		{
			System.err.println("Tried to set selected palette to already selected value");
			return;
		}


		selected_Palette = i;
		EditorMain.controlPanel.paletteCanvas.setColorsPerColumn();
		EditorMain.multipleTileEditor.controlPanel.paletteCanvas.setColorsPerColumn();
		tileset.buildTileImages();
	}




	//===============================================================================================
	public static void moveSpriteDown()
	{//===============================================================================================

		//if we're not the last sprite
		if(selected_Sprite>=getNumSprites()-1||selected_Sprite<0)return;


		//swap this sprite and the next one
		Sprite temp = getSprite(selected_Sprite);

		spriteList.remove(selected_Sprite);
		spriteList.add(selected_Sprite+1,temp);

		//set current sprite the next one
		selected_Sprite = selected_Sprite+1;

	}

	//===============================================================================================
	public static void moveSpriteUp()
	{//===============================================================================================
		//if we're not the first sprite
		if(selected_Sprite<=0)return;


		//swap this sprite and the next one
		Sprite temp = getSprite(selected_Sprite-1);

		spriteList.remove(selected_Sprite-1);
		spriteList.add(selected_Sprite,temp);

		//set current sprite the next one
		selected_Sprite = selected_Sprite-1;

	}



	//===============================================================================================
	public static void deleteSprite()
	{//===============================================================================================
		if(getNumSprites() <= 1)
		{
			return;
		}

		spriteList.remove(selected_Sprite);

		if(selected_Sprite>=getNumSprites())selected_Sprite=getNumSprites()-1;

	}



	//===============================================================================================
	static public int getNumSprites()
	{//===============================================================================================
		return spriteList.size();
	}


	//===============================================================================================
	static public Sprite getSprite(int i)
	{//===============================================================================================
		if(getNumSprites() > 0)
		return spriteList.get(i);
		else return null;
	}

	//===============================================================================================
	public static Sprite getSpriteByName(String nameString)
	{//===============================================================================================
		for(int i=0;i<spriteList.size();i++)
		{
			if(spriteList.get(i).name().equals(nameString))return spriteList.get(i);
		}
		return null;
	}

	//===============================================================================================
	public static String getSelectedSpriteName()
	{//===============================================================================================
		if(getNumSprites() > 0)
		{
			return getSprite(selected_Sprite).name();
		}
		else
		{
			return null;
		}
	}

	//===============================================================================================
	public static Sprite getSelectedSprite()
	{//===============================================================================================
		if(getNumSprites() > 0)
		{
			return getSprite(selected_Sprite);
		}
		else
		{
			return null;
		}
	}

	//===============================================================================================
	public static int getSpriteIndex(Sprite s)
	{//===============================================================================================
		for(int i=0;i<spriteList.size();i++)
		{
			if(spriteList.get(i)==s)return i;
		}
		return -1;

	}
	//===============================================================================================
	public static void setSelectedSpriteIndex(int i)
	{//===============================================================================================
		if(getNumSprites() < i)
		{
			System.err.println("Tried to select sprite over limit");
			return;
		}
		selected_Sprite = i;
	}

	//===============================================================================================
	public static void setSelectedSprite(Sprite s)
	{//===============================================================================================
		for(int i=0;i<spriteList.size();i++)
		{
			if(spriteList.get(i)==s)selected_Sprite=i;
		}

	}

	//===============================================================================================
	public static int getSelectedSpriteIndex()
	{//===============================================================================================
		return selected_Sprite;
	}
	//===============================================================================================
	public static void addSpritePalette(SpritePalette p)
	{//===============================================================================================
		spritepalette.add(p);
		setSelectedSpritePaletteIndex(getNumSpritePalettes()-1);
	}

	//===============================================================================================
	public static void createNewSpritePalette(String n)
	{//===============================================================================================


		spritepalette.add(new SpritePalette(n));
		setSelectedSpritePaletteIndex(getNumSpritePalettes()-1);

		//getNumSpritePalettes()++;
	}

	//===============================================================================================
	public static void createNewSpritePalette()
	{//===============================================================================================
		createNewSpritePalette("SpritePalette" + getNumSpritePalettes());
	}

	//===============================================================================================
	public static void duplicateSpritePalette()
	{//===============================================================================================
		spritepalette.add((SpritePalette) getSpritePalette(selected_SpritePalette).duplicate());
		setSelectedSpritePaletteIndex(getNumSpritePalettes()-1);
		//getNumSpritePalettes()++;
	}



	//===============================================================================================
	public static void deleteSpritePalette()
	{//===============================================================================================
		if(getNumSpritePalettes() <= 1)
		{
			return;
		}


		spritepalette.remove(selected_SpritePalette);
		setSelectedSpritePaletteIndex(0);
	}

	//===============================================================================================
	static public int getNumSpritePalettes()
	{//===============================================================================================
		return spritepalette.size();
	}

	//===============================================================================================
	static public SpritePalette getSpritePalette(int i)
	{//===============================================================================================

		return spritepalette.get(i);

	}

	//===============================================================================================
	public static void renameSpritePalette(String n)
	{//===============================================================================================
		if(getNumSpritePalettes() > 0)
		{
			getSpritePalette(selected_SpritePalette).rename(n);
		}
	}

	//===============================================================================================
	public static String getSelectedSpritePaletteName()
	{//===============================================================================================
		if(getNumSpritePalettes() > 0)
		{
			return getSpritePalette(selected_SpritePalette).name;
		}
		else
		{
			return null;
		}
	}

	//===============================================================================================
	public static SpritePalette getSelectedSpritePalette()
	{//===============================================================================================
		if(getNumSpritePalettes() > 0)
		{
			return getSpritePalette(selected_SpritePalette);
		}
		else
		{
			return null;
		}
	}

	//===============================================================================================
	public static int getSelectedSpritePaletteIndex()
	{//===============================================================================================

		return selected_SpritePalette;

	}

	//===============================================================================================
	public static void setSelectedSpritePaletteIndex(int i)
	{//===============================================================================================
		if(getNumSpritePalettes() <= i)
		{
			System.err.println("Tried to select spritePalette over limit");
			return;
		}
		selected_SpritePalette = i;
	}

	//===============================================================================================
	public void listDoorsThatAreBroken()
	{//===============================================================================================


		//go through each map
		//go through each door
		for(int m=0;m<getNumMaps();m++)
		{
			Map compareMap = getMap(m);

			for(int j=0;j<compareMap.getNumDoors();j++)
			{
				Door d = compareMap.getDoor(j);

				//if door does not have destination, list it here with the map name
				if(d.destinationTYPEIDString().equals(d.getTYPEIDString())==false)
				{
					//if the door has a destination, parse the destination string, find the map it goes to, find the door it goes to, make sure that door's destination is this one

					Door destDoor = d.destinationDoor();
					Map destMap = destDoor.map();

					boolean found=false;

					for(int k=0;k<getNumMaps()&&found==false;k++)
					{
						if(getMap(k)==destMap)
						{
							for(int l=0;l<getMap(k).getNumDoors();l++)
							{
								if(getMap(k).getDoor(l)==destDoor)
								{
									if(getMap(k).getDoor(l).destinationDoor()==getMap(k).getDoor(l))continue;

									Door otherDoor = getMap(k).getDoor(l).destinationDoor();
									Map otherMap = otherDoor.map();

									if(otherMap==compareMap&&otherDoor==d)
									{
										found=true;
									}
								}
							}
						}
					}

					if(found==false)
					{
						System.err.println(""+compareMap.name()+" "+d.name()+" is not connected properly.");
					}
				}
				else
				{
					System.out.println(""+compareMap.name()+" "+d.name()+" has no destination.");
				}
			}
		}
	}



	//===============================================================================================
	public static GameObject getMapObjectByTYPEIDName(String exportName)
	{//===============================================================================================

		if(exportName.startsWith("DOOR."))
		{
			return doorIndexHashtable.get(exportName);
		}

		if(exportName.startsWith("AREA."))
		{
			return areaIndexHashtable.get(exportName);

		}

		if(exportName.startsWith("LIGHT."))
		{
			return lightIndexHashtable.get(exportName);

		}

		if(exportName.startsWith("ENTITY."))
		{
			return entityIndexHashtable.get(exportName);
		}

		if(exportName.startsWith("MAP."))return mapHashtable.get(exportName);
		if(exportName.startsWith("SPRITE."))return spriteHashtable.get(exportName);
		if(exportName.startsWith("SOUND."))return soundHashtable.get(exportName);
		if(exportName.startsWith("MUSIC."))return musicHashtable.get(exportName);
		if(exportName.startsWith("GAMESTRING."))return gameStringHashtable.get(exportName);
		if(exportName.startsWith("DIALOGUE."))return dialogueHashtable.get(exportName);
		if(exportName.startsWith("FLAG."))return flagHashtable.get(exportName);
		if(exportName.startsWith("SKILL."))return skillHashtable.get(exportName);
		if(exportName.startsWith("EVENT."))return eventHashtable.get(exportName);
		if(exportName.startsWith("STATE."))return stateIndexHashtable.get(exportName);


		System.err.println("ERROR! Could not find Object By TypeID:"+exportName);
		return null;
	}


	//===============================================================================================
	public static Map getMapByID(int id)
	{//===============================================================================================
		if(id==-1)return null;
		return mapHashtable.get("MAP."+id);
	}
	//===============================================================================================
	public static Sprite getSpriteByID(int id)
	{//===============================================================================================
		if(id==-1)return null;
		return spriteHashtable.get("SPRITE."+id);
	}
	//===============================================================================================
	public static Sound getSoundByID(int id)
	{//===============================================================================================
		if(id==-1)return null;
		return soundHashtable.get("SOUND."+id);
	}
	//===============================================================================================
	public static Music getMusicByID(int id)
	{//===============================================================================================
		if(id==-1)return null;
		return musicHashtable.get("MUSIC."+id);
	}
	//===============================================================================================
	public static GameString getGameStringByID(int id)
	{//===============================================================================================
		if(id==-1)return null;
		return gameStringHashtable.get("GAMESTRING."+id);
	}

	//===============================================================================================
	public static Dialogue getDialogueByID(int id)
	{//===============================================================================================
		if(id==-1)return null;
		return dialogueHashtable.get("DIALOGUE."+id);
	}
	//===============================================================================================
	public static Flag getFlagByID(int id)
	{//===============================================================================================
		if(id==-1)return null;
		return flagHashtable.get("FLAG."+id);
	}

	//===============================================================================================
	public static Skill getSkillByID(int id)
	{//===============================================================================================
		if(id==-1)return null;
		return skillHashtable.get("FLAG."+id);
	}
	//===============================================================================================
	public static Event getEventByID(int id)
	{//===============================================================================================
		if(id==-1)return null;
		return eventHashtable.get("EVENT."+id);
	}
	//===============================================================================================
	public static MapState getStateByID(int id)
	{//===============================================================================================
		if(id==-1)return null;
		return stateIndexHashtable.get("STATE."+id);
	}

	//===============================================================================================
	public static Flag getFlagByName(String nameString)
	{//===============================================================================================
		for(int i=0;i<flagList.size();i++)if(flagList.get(i).name().equals(nameString))return flagList.get(i);
		return null;
	}

	//===============================================================================================
	public static Skill getSkillByName(String nameString)
	{//===============================================================================================
		for(int i=0;i<skillList.size();i++)if(skillList.get(i).name().equals(nameString))return skillList.get(i);
		return null;
	}
	//===============================================================================================
	public static Music getMusicByName(String nameString)
	{//===============================================================================================
		for(int i=0;i<musicList.size();i++)if(musicList.get(i).name().equals(nameString))return musicList.get(i);
		return null;
	}
	//===============================================================================================
	public static Sound getSoundByName(String nameString)
	{//===============================================================================================
		for(int i=0;i<soundList.size();i++)if(soundList.get(i).name().equals(nameString))return soundList.get(i);
		return null;
	}


	//===============================================================================================
	public void exportProjectToWorkspaceLibGDXAssetsFolderForHTML5()
	{//===============================================================================================


		//String oggTemp = EditorMain.exportDirectory;

		//String dirpath = System.getProperties().getProperty("user.home")+"\\Desktop\\";

//		String dirpath = EditorMain.androidProjectAssetsDir+"sprites\\";//EditorMain.htdocsZippedAssetsDir;
//		Utils.makeDir(dirpath);
//
//
//
//			//pw.println("Sprites");
//			for(int p = 0; p < getNumSprites(); p++)
//			{
//				Sprite sprite = getSprite(p);
////				pw.println(sprite.name()+":"+sprite.getData().toBase64ZippedJSON());
////
////				SpriteBinWithUniquePalette sbin = sprite.makeSpriteBinWithUniquePalette();
////				pw.println(sbin.getDataIntArrayAsGZippedBase64String());
////				pw.println(sbin.getPaletteRGBByteArrayAsGZippedBase64String());
//
//				sprite.outputHorizontalVerticalSpriteSheetPNGAndDescriptorTextFile(dirpath,E,512);
//				//save png frames in 512x512
//				//save data json or txt
//
//
//			}




			{
				String p = EditorMain.androidProjectAssetsDir+"sprites\\";
				Utils.makeDir(p);


					File indexFile = new File(p + "index" + ".txt");

					if(indexFile.exists()==false)
					{
						try
						{
							indexFile.createNewFile();
						}
						catch (IOException e1){e1.printStackTrace();}
					}

					PrintWriter indexFileWriter;
					try
					{
						indexFileWriter = new PrintWriter(new BufferedWriter(new FileWriter(indexFile)));

						for(int n = 0; n < getNumSprites(); n++)
						{
							Sprite sprite = getSprite(n);

							System.out.println(""+sprite.name());

							//save png frames in 512x512
							//save data json or txt
							sprite.outputHorizontalVerticalSpriteSheetPNGAndDescriptorTextFile(p,E,512);


							indexFileWriter.println(""+sprite.name());


						}

						indexFileWriter.close();
					}
					catch (IOException e)
					{
						e.printStackTrace();
					}

			}


//			pw.println("Maps");
//			for(int m = 0; m < getNumMaps(); m++)
//			{
//				Map map = getMap(m);
//				pw.println(map.name()+":"+map.getData().toBase64ZippedJSON());
//
//				MapBinWithUniqueTilesetAndPalette mbin = map.makeMapBinWithUniqueTilesetAndPalette();
//
//				pw.println(mbin.getTileDataIntArrayAsGZippedBase64String());
//				pw.println(mbin.getPaletteRGBByteArrayAsGZippedBase64String());
//				pw.println(mbin.getMapDataIntArrayAsGZippedBase64String());
//
//
//			}
//			pw.println();








			//TODO: OR output Java file descriptor of all assets that initializes all the data
			//then the sprite/music/whatever update can try to load the texture


			{
				String p = EditorMain.androidProjectAssetsDir+"sounds\\";
				Utils.makeDir(p);
				//pw.println("Sounds");


				//---------------------------
				//save text file
				//---------------------------

					//id,name,w,h,frames

					File indexFile = new File(p + "index" + ".txt");

					if(indexFile.exists()==false)
					{
						try
						{
							indexFile.createNewFile();
						}
						catch (IOException e1){e1.printStackTrace();}
					}

					PrintWriter indexFileWriter;
					try
					{
						indexFileWriter = new PrintWriter(new BufferedWriter(new FileWriter(indexFile)));

						for(int m = 0; m < soundList.size(); m++)
						{

							Sound s = soundList.get(m);

							System.out.println(""+s.name());

							//make COPY of data

							SoundData data = new SoundData();
							data.initFromString(s.getData().toString());

							String fullFilePath = data.fullFilePath();

							byte[] bytes = null;

							if(fullFilePath.toLowerCase().endsWith(".wav"))// && FileUtils.sizeOf(new File(fullFilePath))>1024*50)
							{
								String originalFilePath = ""+fullFilePath;

								String fileName = data.fileName().substring(0,data.fileName().length()-4)+".mp3";
								data.setFileName(fileName);

								String oggDir = fullFilePath.substring(0,fullFilePath.lastIndexOf("\\"));
								Utils.makeDir(oggDir+"\\mp3\\");
								fullFilePath = oggDir+"\\mp3\\"+fileName;

								File f = new File(fullFilePath);
								if(f.exists()==false)
								{
									String[] commands = {EditorMain.lameEncoderPath, "-b 192", "\""+originalFilePath+"\"", "\""+fullFilePath+"\""};
									try{Runtime.getRuntime().exec(commands).waitFor();}catch(InterruptedException e){e.printStackTrace();}

									//String[] commands = {EditorMain.oggEncPath, "-q 5", "--output=\""+fullFilePath+"\"", "\""+originalFilePath+"\""};
									//try{Runtime.getRuntime().exec(commands).waitFor();}catch(InterruptedException e){e.printStackTrace();}
								}


								FileUtils.copyFile(f,new File(""+p+fileName));

								indexFileWriter.println(""+fileName);
							}

							//remove filepath from COPY of data sent to server
							data.setFullFilePath("");


						}

						indexFileWriter.close();
					}
					catch (IOException e)
					{
						e.printStackTrace();
					}

			}



			{
				String p = EditorMain.androidProjectAssetsDir+"music\\";
				Utils.makeDir(p);

				File indexFile = new File(p + "index" + ".txt");

				if(indexFile.exists()==false)
				{
					try
					{
						indexFile.createNewFile();
					}
					catch (IOException e1){e1.printStackTrace();}
				}

				PrintWriter indexFileWriter;
				try
				{
					indexFileWriter = new PrintWriter(new BufferedWriter(new FileWriter(indexFile)));


					for(int i = 0; i < musicList.size(); i++)
					{
						Music m = musicList.get(i);

						System.out.println(""+m.name());

						//make COPY of data

						MusicData data = new MusicData();
						data.initFromString(m.getData().toString());

						String fullFilePath = data.fullFilePath();

						byte[] bytes = null;

						if(fullFilePath.toLowerCase().endsWith(".wav"))// && FileUtils.sizeOf(new File(fullFilePath))>1024*50)
						{
							String originalFilePath = ""+fullFilePath;

							String fileName = data.fileName().substring(0,data.fileName().length()-4)+".mp3";
							data.setFileName(fileName);


							String oggDir = fullFilePath.substring(0,fullFilePath.lastIndexOf("\\"));
							Utils.makeDir(oggDir+"\\mp3\\");
							fullFilePath = oggDir+"\\mp3\\"+fileName;

							File f = new File(fullFilePath);
							if(f.exists()==false)
							{

								String[] commands = {EditorMain.lameEncoderPath, "-b 192", "\""+originalFilePath+"\"", "\""+fullFilePath+"\""};
								try{Runtime.getRuntime().exec(commands).waitFor();}catch(InterruptedException e){e.printStackTrace();}


								//String[] commands = {EditorMain.oggEncPath, "-q 5", "--output=\""+fullFilePath+"\"", "\""+originalFilePath+"\""};
								//try{Runtime.getRuntime().exec(commands).waitFor();}catch(InterruptedException e){e.printStackTrace();}
							}


							FileUtils.copyFile(f,new File(""+p+fileName));

							indexFileWriter.println(""+fileName);
						}

						//remove filepath from COPY of data sent to server
						data.setFullFilePath("");


					}

					indexFileWriter.close();
				}
				catch (IOException e)
				{
					e.printStackTrace();
				}

			}




		EditorMain.infoLabel.setTextSuccess("Exported Sprites to LibGDX Android asset folder");
	}


	//===============================================================================================
	public void exportProjectAsGameDataFile()
	{//===============================================================================================

		//String oggTemp = EditorMain.exportDirectory;

		String dirpath = EditorMain.htdocsZippedAssetsDir;

		try
		{
			PrintWriter pw  = new PrintWriter(new BufferedWriter(new FileWriter(new File(dirpath+"gameData"))));//TODO
			//TODO
			//TODO custom name per game, game loads its own gameData from server
			//TODO
			//TODO
			//TODO
			//TODO

			pw.println("Sprites");
			for(int p = 0; p < getNumSprites(); p++)
			{
				Sprite sprite = getSprite(p);
				pw.println(sprite.name()+":"+sprite.getData().toString());

				SpriteBinWithUniquePalette sbin = sprite.makeSpriteBinWithUniquePalette();
				pw.println(sbin.getDataIntArrayAsGZippedBase64String());
				pw.println(sbin.getPaletteRGBByteArrayAsGZippedBase64String());

			}
			pw.println();


			pw.println("Maps");
			for(int m = 0; m < getNumMaps(); m++)
			{
				Map map = getMap(m);
				pw.println(map.name()+":"+map.getData().toString());

				MapBinWithUniqueTilesetAndPalette mbin = map.makeMapBinWithUniqueTilesetAndPalette();

				pw.println(mbin.getTileDataIntArrayAsGZippedBase64String());
				pw.println(mbin.getPaletteRGBByteArrayAsGZippedBase64String());
				pw.println(mbin.getMapDataIntArrayAsGZippedBase64String());


			}
			pw.println();


			pw.println("Sounds");
			for(int m = 0; m < soundList.size(); m++)
			{

				Sound s = soundList.get(m);

				//make COPY of data
				SoundData data = new SoundData();
				data.initFromString(s.getData().toString());

				String fullFilePath = data.fullFilePath();

				byte[] bytes = null;

				if(fullFilePath.toLowerCase().endsWith(".wav") && FileUtils.sizeOf(new File(fullFilePath))>1024*50)
				{
					String originalFilePath = ""+fullFilePath;

					String fileName = data.fileName().substring(0,data.fileName().length()-4)+".ogg";
					data.setFileName(fileName);

					String oggDir = fullFilePath.substring(0,fullFilePath.lastIndexOf("\\"));
					Utils.makeDir(oggDir+"\\ogg\\");
					fullFilePath = oggDir+"\\ogg\\"+fileName;

					File f = new File(fullFilePath);
					if(f.exists()==false)
					{

						String[] commands = {EditorMain.oggEncPath, "-q 5", "--output=\""+fullFilePath+"\"", "\""+originalFilePath+"\""};
						try{Runtime.getRuntime().exec(commands).waitFor();}catch(InterruptedException e){e.printStackTrace();}
					}
				}

				if(bytes==null)
				{
					try
					{
						bytes = FileUtils.readFileToByteArray(new File(fullFilePath));
					}
					catch(IOException e)
					{
						e.printStackTrace();
					}
				}

				//remove filepath from COPY of data sent to server
				data.setFullFilePath("");

				String md5FileName = Utils.getByteArrayMD5Checksum(bytes);
				data.setMD5Name(md5FileName);

				pw.println(data.name()+":"+data.toString());
				pw.println(Utils.encodeStringToBase64(Utils.zipByteArrayToString(bytes)));

			}
			pw.println();



			pw.println("Music");
			for(int i = 0; i < musicList.size(); i++)
			{
				Music m = musicList.get(i);
				//pw.println(sound.name()+":"+sound.getData().toBase64ZippedJSON());
				//pw.println(sound.getFileBytesAsGZippedBase64String());

				//make COPY of data
				MusicData data = new MusicData();
				data.initFromString(m.getData().toString());

				String fullFilePath = data.fullFilePath();

				byte[] bytes = null;

				if(fullFilePath.toLowerCase().endsWith(".wav") && FileUtils.sizeOf(new File(fullFilePath))>1024*50)
				{
					String originalFilePath = ""+fullFilePath;

					String fileName = data.fileName().substring(0,data.fileName().length()-4)+".ogg";
					data.setFileName(fileName);


					String oggDir = fullFilePath.substring(0,fullFilePath.lastIndexOf("\\"));
					Utils.makeDir(oggDir+"\\ogg\\");
					fullFilePath = oggDir+"\\ogg\\"+fileName;

					File f = new File(fullFilePath);
					if(f.exists()==false)
					{

						String[] commands = {EditorMain.oggEncPath, "-q 5", "--output=\""+fullFilePath+"\"", "\""+originalFilePath+"\""};
						try{Runtime.getRuntime().exec(commands).waitFor();}catch(InterruptedException e){e.printStackTrace();}
					}

				}

				if(bytes==null)
				{
					try
					{
						bytes = FileUtils.readFileToByteArray(new File(fullFilePath));
					}
					catch(IOException e)
					{
						e.printStackTrace();
					}
				}

				//remove filepath from COPY of data sent to server
				data.setFullFilePath("");

				String md5FileName = Utils.getByteArrayMD5Checksum(bytes);
				data.setMD5Name(md5FileName);

				pw.println(data.name()+":"+data.toString());
				pw.println(Utils.encodeStringToBase64(Utils.zipByteArrayToString(bytes)));
			}
			pw.println();



			pw.close();

		}
		catch(IOException e1)
		{
			e1.printStackTrace();
		}

		EditorMain.infoLabel.setTextSuccess("Exported Maps and Sprites to htdocs/z/gameData");

	}



	//===============================================================================================
	public void makeDirs()
	{//===============================================================================================

		String dirpath = EditorMain.exportDirectory;
		Utils.makeDir(dirpath + "\\htdocs\\");
		Utils.makeDir(dirpath + "\\htdocs\\z\\");
		Utils.makeDir(dirpath + "\\htdocs\\bin\\");
		Utils.makeDir(dirpath + "\\htdocs\\png\\");
		Utils.makeDir(dirpath + "\\BobsGameOnline\\");
		Utils.makeDir(dirpath + "\\BobsGameServer\\");
		Utils.makeDir(dirpath + "\\BobsGameOnline\\src\\");
		Utils.makeDir(dirpath + "\\BobsGameServer\\src\\");

	}


	//===============================================================================================
	public void exportPalettes()
	{//===============================================================================================
		//output tileset, palette, maps
		for(int p = 0; p < getNumPalettes(); p++)
		{
			//outputs both BGR and RGB palettes
			getPalette(p).outputBIN();
		}

	}



	//===============================================================================================
	public void exportMapTilesets()
	{//===============================================================================================

		for(int m = 0; m < getNumMaps(); m++) //counting tiles, making virtual tileset based on used tiles only, only for layers 0,1,2,3
		{
			getMap(m).outputUniqueTilesetForSingleMapSeparatedBINs();
		}

	}


	//===============================================================================================
	public void exportSpriteData()
	{//===============================================================================================
		for(int q = 0; q < Project.getNumSprites(); q++)
		{
			Project.getSprite(q).outputBINWithCustomPalette();
		}

	}

	//===============================================================================================
	public void exportClientPreloadedAssets()
	{//===============================================================================================


		String baseDir = EditorMain.clientPreloadedAssetsDir;
		//String baseDir = "C:\\Users\\Administrator\\workspace\\BobsGameOnline\\res\\";
		Utils.makeDir(baseDir);




		prepareEventsForExport();


		//preload ALL skills

		//===============================================================================================
		//public void exportClientPreloadedPlayerSkillIndex()
		{//===============================================================================================

			//Utils.makeDir("C:\\Users\\Administrator\\workspace\\BobsGameOnline\\res\\");

			try
			{
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(baseDir+"PreloadSkillData"))));

				for(int i = 0; i < skillList.size(); i++)
				{
					pw.println(skillList.get(i).getData().toString());
				}

				pw.close();

			}
			catch(IOException e){System.out.println("Could not create file.");return;}

		}



		//add preload music and sprite to arraylist

		ArrayList<Sprite> preloadSpriteList = new ArrayList<Sprite>();
		ArrayList<Music> preloadMusicList = new ArrayList<Music>();
		ArrayList<Event> eventCheckList = new ArrayList<Event>();

		for(int i=0;i<musicList.size();i++)
		{
			Music s = musicList.get(i);
			if(s.preload()==true)
			{
				preloadMusicList.add(s);
			}
		}

		for(int i=0;i<spriteList.size();i++)
		{
			Sprite s = spriteList.get(i);

			if(s.isRandom()==true || s.forceMD5Export()==true)
			{
				preloadSpriteList.add(s);
			}

		}

		//===============================================================================================
		//public void exportClientPreloadedMapAssetIndex()
		{//===============================================================================================

			//Utils.makeDir("C:\\Users\\Administrator\\workspace\\BobsGameOnline\\res\\");

			try
			{
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(baseDir+"PreloadMapData"))));

				for(int n = 0; n < mapList.size(); n++)
				{
					Map m = mapList.get(n);

					if(m.preload())
					{
						pw.println(m.getData().toString());




						// need to export every sprite, sound, music referenced in map and all map events

						// the problem with having preloaded data for map/sprite etc is that if i modify the graphics or event or whatever, the client is forever stuck with the old version since it never contacts the server.
						//so i need to only use this for intro and not touch anything that it uses


						//all sounds should be exported by default (I can add sounds in the assets without a complete client refresh)

						//should check to see if sprites and music are exported by default, if not, export them here.
						// probably need to combine all these export functions into one in order to do this



						//get every sprite, music referenced in every event

////already exported in events now
//						for(int i=0;i<cutsceneEventList.size();i++)
//						{
//
//							Event e = cutsceneEventList.get(i);
//							if(eventCheckList.contains(e)==false)eventCheckList.add(e);
//						}
//
//
//						for(int i=0;i<m.getNumEvents();i++)
//						{
//
//							Event e = m.getEvent(i);
//							if(eventCheckList.contains(e)==false)eventCheckList.add(e);
//						}



						//get every sprite, music referenced in every entity in every state, and every event in every entity and area
						for(int i=0;i<m.getNumStates();i++)
						{
							MapState s = m.getState(i);
							for(int k=0;k<s.getNumEntities();k++)
							{
								Entity o = s.getEntity(k);
								if(preloadSpriteList.contains(o.getSprite())==false)preloadSpriteList.add(o.getSprite());

								//if(o.eventData()!=null){Event e = getEventByID(o.eventData().id()); if(eventCheckList.contains(e)==false)eventCheckList.add(e);}
							}

							for(int k=0;k<s.getNumAreas();k++)
							{
								Area o = s.getArea(k);

								//if(o.eventData()!=null){Event e = getEventByID(o.eventData().id()); if(eventCheckList.contains(e)==false)eventCheckList.add(e);}
							}
						}

						//get every sprite, music referenced in every door
						for(int i=0;i<m.getNumDoors();i++)
						{
							Door o = m.getDoor(i);
							if(preloadSpriteList.contains(o.getSprite())==false)preloadSpriteList.add(o.getSprite());

							//if(o.eventData()!=null){Event e = getEventByID(o.eventData().id()); if(eventCheckList.contains(e)==false)eventCheckList.add(e);}
						}


					}


				}

				pw.close();

			}
			catch(IOException e){System.out.println("Could not create file.");return;}


		}




		//already exported in events now
//
//		for(int i=0;i<eventCheckList.size();i++)
//		{
//			Event e = eventCheckList.get(i);
//			String s = ""+e.text();
//			while(s.contains("SPRITE."))
//			{
//				s = s.substring(s.indexOf("SPRITE."));
//				if(s.indexOf("|")!=-1&&s.indexOf("|")<s.indexOf(")"))
//				{
//					String typeIDString = s.substring(0,s.indexOf("|"));
//					Sprite o = (Sprite)getMapObjectByTYPEIDName(typeIDString);
//					if(o == null)System.out.println("Could not find "+typeIDString);
//					else if(preloadSpriteList.contains(o)==false)preloadSpriteList.add(o);
//					s = s.substring(s.indexOf("|")+1);
//				}
//				else
//				{
//					String typeIDString = s.substring(0,s.indexOf(")"));
//					Sprite o = (Sprite)getMapObjectByTYPEIDName(typeIDString);
//					if(o == null)System.out.println("Could not find "+typeIDString);
//					else if(preloadSpriteList.contains(o)==false)preloadSpriteList.add(o);
//					s = s.substring(s.indexOf(")")+1);
//				}
//			}
//
//
//			//already exported in events now
////			s = ""+e.text();
////			while(s.contains("MUSIC."))
////			{
////				s = s.substring(s.indexOf("MUSIC."));
////				if(s.indexOf("|")!=-1&&s.indexOf("|")<s.indexOf(")"))
////				{
////					String typeIDString = s.substring(0,s.indexOf("|"));
////					Music o = (Music)getMapObjectByTYPEIDName(typeIDString);
////					if(o == null)System.out.println("Could not find "+typeIDString);
////					else if(preloadMusicList.contains(o)==false)preloadMusicList.add(o);
////					s = s.substring(s.indexOf("|")+1);
////				}
////				else
////				{
////					String typeIDString = s.substring(0,s.indexOf(")"));
////					Music o = (Music)getMapObjectByTYPEIDName(typeIDString);
////					if(o == null)System.out.println("Could not find "+typeIDString);
////					else if(preloadMusicList.contains(o)==false)preloadMusicList.add(o);
////					s = s.substring(s.indexOf(")")+1);
////				}
////			}
//
//		}



		//export all the sprites we have needed thus far, collect their events too


		//===============================================================================================
		//public void exportClientPreloadedSpriteAssetIndex()
		{//===============================================================================================

			//Utils.makeDir("C:\\Users\\Administrator\\workspace\\BobsGameOnline\\res\\");

			try
			{
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(baseDir+"PreloadSpriteData"))));

				for(int i = 0; i < preloadSpriteList.size(); i++)
				{
					Sprite o = preloadSpriteList.get(i);
					SpriteData spriteData = o.getData();//new SpriteData(s.id,s.name(),s.displayName,s.width(),s.height(),s.frames(),s.isNPC,s.isKid,s.isAdult,s.isMale,s.isFemale,s.isCar,s.isAnimal,s.hasShadow,s.isRandom,s.isDoor,s.isGame,s.isItem,s.clientForceHQ2X,s.eventID,s.itemGameDescription,gamePriceFloat,s.utilityPointOffsetX,s.utilityPointOffsetY,"","");

					//if(o.eventData()!=null){Event e = getEventByID(o.eventData().id()); if(eventCheckList.contains(e)==false)eventCheckList.add(e);}

					//if(getSprite(i).isRandom()==true || getSprite(i).forceMD5Export()==true)
					{
						pw.println(spriteData.toString());
					}
				}

				pw.close();

			}
			catch(IOException e){System.out.println("Could not create file.");return;}

		}


		//export ALL sounds for now

		//===============================================================================================
		//public void exportClientPreloadedSoundAssetIndex()
		{//===============================================================================================

			//Utils.makeDir("C:\\Users\\Administrator\\workspace\\BobsGameOnline\\res\\");

			try
			{
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(baseDir+"PreloadSoundData"))));

				for(int i = 0; i < soundList.size(); i++)
				{
					Sound o = soundList.get(i);



					//make COPY of data

					SoundData data = new SoundData();
					data.initFromString(o.getData().toString());

					String fullFilePath = data.fullFilePath();
					String fileName = data.fileName();

					if(fileName.toLowerCase().endsWith(".wav") && FileUtils.sizeOf(new File(fullFilePath))>1024*50)
						data.setFileName(fileName.substring(0,fileName.length()-4)+".ogg");

					//remove filepath from COPY of data sent to client
					data.setFullFilePath("");

					pw.println(data.toString());

				}

				pw.close();

			}
			catch(IOException e){System.out.println("Could not create file.");return;}

		}



		//export only the music we have marked preload and associated with events

		//===============================================================================================
		//public void exportClientPreloadedMusicAssetIndex()
		{//===============================================================================================

			//Utils.makeDir("C:\\Users\\Administrator\\workspace\\BobsGameOnline\\res\\");

			try
			{
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(baseDir+"PreloadMusicData"))));

				for(int i = 0; i < preloadMusicList.size(); i++)
				{
					Music o = preloadMusicList.get(i);

					//if(s.preload()==true)
					{

						//make COPY of data

						MusicData data = new MusicData();
						data.initFromString(o.getData().toString());

						String fullFilePath = data.fullFilePath();
						String fileName = data.fileName();

						if(fileName.toLowerCase().endsWith(".wav") && FileUtils.sizeOf(new File(fullFilePath))>1024*50)
							data.setFileName(fileName.substring(0,fileName.length()-4)+".ogg");

						//remove filepath from COPY of data sent to client
						data.setFullFilePath("");

						pw.println(data.toString());
					}

				}

				pw.close();

			}
			catch(IOException e){System.out.println("Could not create file.");return;}

		}











		//now export all the cutscene events

		//===============================================================================================
		//public void exportClientPreloadedEventIndex()
		{//===============================================================================================

			//Utils.makeDir("C:\\Users\\Administrator\\workspace\\BobsGameOnline\\res\\");

			try
			{
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(baseDir+"PreloadEventData"))));

				for(int i = 0; i < cutsceneEventList.size(); i++)
				{
					pw.println(cutsceneEventList.get(i).getData().toString());
				}

				pw.close();

			}
			catch(IOException e){System.out.println("Could not create file.");return;}

		}













		//already exported in events now

		//now output the dialogues those events need



		//===============================================================================================
		//public void exportClientPreloadedDialogueIndex()
		{//===============================================================================================

			//Utils.makeDir("C:\\Users\\Administrator\\workspace\\BobsGameOnline\\res\\");

			ArrayList<Dialogue> preloadDialogueList = new ArrayList<Dialogue>();

			for(int i=0;i<eventCheckList.size();i++)
			{
				Event e = eventCheckList.get(i);
				String s = ""+e.text();
				while(s.contains("DIALOGUE."))
				{
					s = s.substring(s.indexOf("DIALOGUE."));
					if(s.indexOf("|")!=-1&&s.indexOf("|")<s.indexOf(")"))
					{
						String typeIDString = s.substring(0,s.indexOf("|"));
						Dialogue o = (Dialogue)getMapObjectByTYPEIDName(typeIDString);
						if(preloadDialogueList.contains(o)==false)preloadDialogueList.add(o);
						s = s.substring(s.indexOf("|")+1);
					}
					else
					{
						String typeIDString = s.substring(0,s.indexOf(")"));
						Dialogue o = (Dialogue)getMapObjectByTYPEIDName(typeIDString);
						if(preloadDialogueList.contains(o)==false)preloadDialogueList.add(o);
						s = s.substring(s.indexOf(")")+1);
					}
				}
			}

			try
			{
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(baseDir+"PreloadDialogueData"))));

				for(int i = 0; i < preloadDialogueList.size(); i++)
				{
					pw.println(preloadDialogueList.get(i).getData().toString());
				}

				pw.close();

			}
			catch(IOException e){System.out.println("Could not create file.");return;}

		}















		//===============================================================================================
		//public void exportClientPreloadedGameStringIndex()
		{//===============================================================================================

			//Utils.makeDir("C:\\Users\\Administrator\\workspace\\BobsGameOnline\\res\\");

			ArrayList<GameString> preloadGameStringList = new ArrayList<GameString>();

			for(int i=0;i<eventCheckList.size();i++)
			{
				Event e = eventCheckList.get(i);
				String s = ""+e.text();
				while(s.contains("GAMESTRING."))
				{
					s = s.substring(s.indexOf("GAMESTRING."));
					if(s.indexOf("|")!=-1&&s.indexOf("|")<s.indexOf(")"))
					{
						String typeIDString = s.substring(0,s.indexOf("|"));
						GameString o = (GameString)getMapObjectByTYPEIDName(typeIDString);
						if(preloadGameStringList.contains(o)==false)preloadGameStringList.add(o);
						s = s.substring(s.indexOf("|")+1);
					}
					else
					{
						String typeIDString = s.substring(0,s.indexOf(")"));
						GameString o = (GameString)getMapObjectByTYPEIDName(typeIDString);
						if(preloadGameStringList.contains(o)==false)preloadGameStringList.add(o);
						s = s.substring(s.indexOf(")")+1);
					}
				}
			}

			try
			{
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(baseDir+"PreloadGameStringData"))));

				for(int i = 0; i < preloadGameStringList.size(); i++)
				{
					pw.println(preloadGameStringList.get(i).getData().toString());
				}

				pw.close();

			}
			catch(IOException e){System.out.println("Could not create file.");return;}

		}


		//===============================================================================================
		//public void exportClientPreloadedFlagIndex()
		{//===============================================================================================

			//Utils.makeDir("C:\\Users\\Administrator\\workspace\\BobsGameOnline\\res\\");

			ArrayList<Flag> preloadFlagList = new ArrayList<Flag>();

			for(int i=0;i<eventCheckList.size();i++)
			{
				Event e = eventCheckList.get(i);
				String s = ""+e.text();
				while(s.contains("FLAG."))
				{
					s = s.substring(s.indexOf("FLAG."));
					if(s.indexOf("|")!=-1&&s.indexOf("|")<s.indexOf(")"))
					{
						String typeIDString = s.substring(0,s.indexOf("|"));
						Flag o = (Flag)getMapObjectByTYPEIDName(typeIDString);
						if(preloadFlagList.contains(o)==false)preloadFlagList.add(o);
						s = s.substring(s.indexOf("|")+1);
					}
					else
					{
						String typeIDString = s.substring(0,s.indexOf(")"));
						Flag o = (Flag)getMapObjectByTYPEIDName(typeIDString);
						if(preloadFlagList.contains(o)==false)preloadFlagList.add(o);
						s = s.substring(s.indexOf(")")+1);
					}
				}
			}

			try
			{
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(baseDir+"PreloadFlagData"))));

				for(int i = 0; i < preloadFlagList.size(); i++)
				{
					pw.println(preloadFlagList.get(i).getData().toString());
				}

				pw.close();

			}
			catch(IOException e){System.out.println("Could not create file.");return;}

		}


	}

	//===============================================================================================
	public void exportServerMapAssetIndex()
	{//===============================================================================================



			//take each bin file, rename to 0-12,t,p, zip as temp.zip
			//rename temp.zip to md5
			//store in htdocs/z
			//store md5 filename in this output structure



			//in client--------

			//when load map
			//ask server for permission, md5
				//if not permission, server logs cheater, game restarts player to door.

			//check cache/md5
			//if not exist
				//download bobsgame.com/z/md5
				//unzip to cache/md5/0-12,t,p
				//open t,p
				//for each chunk + 1 tile border
					//open 0-6
					//combine into oversized chunk png with 1 pixel border
					//if blank, don't create png.
					//save as md5/b/0x0

					//open 7-9
					//combine into oversized chunk png with 1 pixel border
					//if blank, don't create png.
					//save as md5/a/0x0

				//hq2x both chunks
				//crop borders
				//save as md5/a/2/0x0
				//save as md5/b/2/0x0

			//determine how many chunks needed on screen
			//load each chunk md5/a/2/0x0 into graphics card as texture, not keeping in local memory.

			//tell server "i am in room"


			//-------

			//save sprite as md5
			//zip as s

			//in client---------
			//download s
			//unzip to cache/
			//download md5list each login
			//if missing md5, download individual md5
			//load md5list sprites into graphics card as texture, not keeping in local memory.

			//it is best to have all sprites local, so there is no lag when new sprites pop in.

			//there will be some lag when custom sprites are created or user avatars enter the room...
			//todo: could have a black generic silhouette outline for this until data loads

			//DONE: need random sprites, custom sprites. how to do this?
			//probably best to generate these on the server side. maybe 50 variations per sprite.
			//DONE: should have a "random" checkbox and a colorset window...

			//making custom sprite: not sure yet.
			//choose face, head, colors?


			//need: java md5 tool
			//need: java zip manipulation
			//need: java applet
			//need: applet get GPU memory, capabilities, GL version
			//need: applet info, browser info, signed applet capabilities, applet permissions, read/write folders, maybe use sigar?
			//need: java graphics card texture manipulation, no local memory
			//need: graphics card texture LOSSLESS compression.
			//need: hq2x as utility jar
			//need: applet cache store
			//need: applet write permissions



			String dirpath = EditorMain.getDesktopTempDirPath() + "htdocs\\bin\\tilemap\\";

			Utils.makeDir(dirpath);
			//Utils.makeDir(dirpath + name() + "\\");

			Utils.makeDir(EditorMain.serverDataDir);



			//create a new zip file
			try
			{

				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(EditorMain.serverDataDir+"MapData"))));

				ZipOutputStream zos = new ZipOutputStream(new FileOutputStream(EditorMain.htdocsZippedAssetsDir+"maps.zip"));


				for(int m = 0; m < getNumMaps(); m++)
				{

					MapData mapData = getMap(m).getData();//new MapData(getMap(m).id(),getMap(m).name(),getMap(m).wT(),getMap(m).hT());

					//mapData.setMaxRandoms(getMap(m).maxRandoms());
					//mapData.setIsOutside(getMap(m).isOutside());

					for(int l=0;l<MapData.layers;l++)
					{
						if(MapData.isTileLayer(l))
						{

							String filename = dirpath + getMap(m).name() + "\\"+l;
							String md5FileName = Utils.putFileInZipAsMD5(zos,filename);

							if(l==MapData.MAP_GROUND_LAYER){mapData.setGroundLayerMD5(md5FileName);}
							if(l==MapData.MAP_GROUND_DETAIL_LAYER){mapData.setGroundObjectsMD5(md5FileName);}
							if(l==MapData.MAP_GROUND_SHADOW_LAYER){mapData.setGroundShadowMD5(md5FileName);}
							if(l==MapData.MAP_OBJECT_LAYER){mapData.setObjectsMD5(md5FileName);}
							if(l==MapData.MAP_OBJECT_DETAIL_LAYER){mapData.setObjects2MD5(md5FileName);}
							if(l==MapData.MAP_OBJECT_SHADOW_LAYER){mapData.setObjectShadowMD5(md5FileName);}
							if(l==MapData.MAP_ABOVE_LAYER){mapData.setAboveMD5(md5FileName);}
							if(l==MapData.MAP_ABOVE_DETAIL_LAYER){mapData.setAbove2MD5(md5FileName);}
							if(l==MapData.MAP_SPRITE_SHADOW_LAYER){mapData.setSpriteShadowMD5(md5FileName);}
							if(l==MapData.MAP_SHADER_LAYER){mapData.setGroundShaderMD5(md5FileName);}
							if(l==MapData.MAP_LIGHT_MASK_LAYER){mapData.setLightMaskMD5(md5FileName);}
							if(l==MapData.MAP_CAMERA_BOUNDS_LAYER){mapData.setCameraBoundsMD5(md5FileName);}
							if(l==MapData.MAP_HIT_LAYER){mapData.setHitBoundsMD5(md5FileName);}

						}
					}

					mapData.setTilesMD5(Utils.putFileInZipAsMD5(zos,dirpath + getMap(m).name() + "\\t"));
					mapData.setPaletteMD5(Utils.putFileInZipAsMD5(zos,dirpath + getMap(m).name() + "\\p"));



//					for(int n=0;n<getMap(m).getNumEvents();n++)
//					{
//						Event e = getMap(m).getEvent(n);
//						EventData eventData = new EventData(e.id(),e.name(),e.type(),e.comment(),e.text());
//						mapData.eventDataList().add(eventData);
//					}

//					for(int n=0;n<getMap(m).getNumStates();n++)
//					{
//						MapState s = getMap(m).getState(n);
//						MapStateData data = new MapStateData(s.id(),s.name());
//						mapData.stateDataList().add(data);
//					}

					for(int n=0;n<getMap(m).getNumDoors();n++)
					{
						Door d = getMap(m).getDoor(n);

						//TODO: this is a hack
						d.getData().setDestinationMapName(((Door)Project.getMapObjectByTYPEIDName(d.destinationTYPEIDString())).map().name());
						d.getData().setDestinationDoorName(((Door)Project.getMapObjectByTYPEIDName(d.destinationTYPEIDString())).name());
						//mapData.doorDataList().add(d.getData());
					}


					for(int s=0;s<getMap(m).getNumStates();s++)
					{
						MapState state = getMap(m).getState(s);

//						MapStateData mapStateData = null;
//						for(int i=0;i<mapData.stateDataList().size();i++){if(mapData.stateDataList().get(i).id()==state.id()){mapStateData = mapData.stateDataList().get(i);break;}}
//
//						if(mapStateData==null)System.err.println("Could not find state ID: "+state.id());

						for(int n=0;n<state.getNumAreas();n++)
						{
							Area a = state.getArea(n);
							if(a.isWarpArea()==true)//it is a WarpArea
							{
								//TODO: this is a hack
								a.getData().setDestinationMapName(((Area)Project.getMapObjectByTYPEIDName(a.destinationTYPEIDString())).map().name());
								a.getData().setDestinationWarpAreaName(((Area)Project.getMapObjectByTYPEIDName(a.destinationTYPEIDString())).name());
							}

							//mapStateData.areaDataList().add(a.getData());
						}

//						for(int n=0;n<getMap(m).getState(s).getNumLights();n++)
//						{
//							Light l = getMap(m).getState(s).getLight(n);
//							mapStateData.lightDataList().add(l.getData());
//						}
//
//						for(int n=0;n<getMap(m).getState(s).getNumEntities();n++)
//						{
//							Entity e = getMap(m).getState(s).getEntity(n);
//							mapStateData.entityDataList().add(e.getData());
//						}
					}


					pw.println(mapData.toJSON());

				}

				pw.close();


				//close the stream
				zos.close();
			}
			catch(Exception e)
			{
				e.printStackTrace();
			//handle exception
			}


		}


	//===============================================================================================
	public void exportServerSpriteAssetIndex()
	{//===============================================================================================


		String dirpath = EditorMain.getDesktopTempDirPath() + "htdocs\\bin\\sprite\\";


		Utils.makeDir(EditorMain.serverDataDir);
			Utils.makeDir(EditorMain.htdocsZippedAssetsDir);

			try
			{
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(EditorMain.serverDataDir+"SpriteData"))));

				ZipOutputStream zos = new ZipOutputStream(new FileOutputStream(EditorMain.htdocsZippedAssetsDir+"sprites.zip"));

				for(int i = 0; i < getNumSprites(); i++)
				{
					Sprite s = getSprite(i);
					SpriteData spriteData = s.getData();

					spriteData.setDataMD5(Utils.putFileInZipAsMD5(zos,dirpath + s.name() + "_SpriteDataUnique.bin"));
					spriteData.setPaletteMD5(Utils.putFileInZipAsMD5(zos,dirpath + s.name() + "_SpritePaletteUnique.bin"));

					pw.println(spriteData.toJSON());
				}

				pw.close();

				zos.close();
			}
			catch (FileNotFoundException e1){}
			catch (IOException e){}


	}



	//===============================================================================================
	public void exportServerDialogueAssetIndex()
	{//===============================================================================================

		Utils.makeDir(EditorMain.serverDataDir);

		try
		{
			PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(EditorMain.serverDataDir+"DialogueData"))));

			for(int s = 0; s < dialogueList.size(); s++)
			{
				Dialogue d = dialogueList.get(s);
				pw.println(d.getData().toJSON());
			}

			pw.close();

		}
		catch(IOException e){System.out.println("Could not create file.");return;}

	}



	//===============================================================================================
	public void exportServerCutsceneEventAssetIndex()
	{//===============================================================================================

		Utils.makeDir(EditorMain.serverDataDir);

		try
		{
			PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(EditorMain.serverDataDir+"CutsceneEventData"))));


			for(int s = 0; s < eventList.size(); s++)
			{
				Event d = eventList.get(s);
				pw.println(d.getData().toJSON());
			}

			pw.close();
		}
		catch(IOException e){System.out.println("Could not create file.");return;}

	}

	//===============================================================================================
	public void exportServerGameStringAssetIndex()
	{//===============================================================================================

		Utils.makeDir(EditorMain.serverDataDir);

		try
		{
			PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(EditorMain.serverDataDir+"GameStringData"))));

			for(int s = 0; s < gameStringList.size(); s++)
			{
				GameString d = gameStringList.get(s);
				pw.println(d.getData().toJSON());
			}

			pw.close();
		}
		catch(IOException e){System.out.println("Could not create file.");return;}

	}

	//===============================================================================================
	public void exportServerFlagAssetIndex()
	{//===============================================================================================

		Utils.makeDir(EditorMain.serverDataDir);

		try
		{
			PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(EditorMain.serverDataDir+"FlagData"))));

			for(int s = 0; s < flagList.size(); s++)
			{
				Flag d = flagList.get(s);
				pw.println(d.getData().toJSON());
			}

			pw.close();
		}
		catch(IOException e){System.out.println("Could not create file.");return;}

	}

	//===============================================================================================
	public void exportServerPlayerSkillAssetIndex()
	{//===============================================================================================

		Utils.makeDir(EditorMain.serverDataDir);


		try
		{
			PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(EditorMain.serverDataDir+"SkillData"))));

			for(int s = 0; s < skillList.size(); s++)
			{
				Skill d = skillList.get(s);
				pw.println(d.getData().toJSON());
			}

			pw.close();
		}
		catch(IOException e){System.out.println("Could not create file.");return;}

	}

	//===============================================================================================
	public void exportServerMusicAssetIndex()
	{//===============================================================================================
			Utils.makeDir(EditorMain.serverDataDir);
			//String oggTemp = EditorMain.exportDirectory;

			try
			{
				System.out.println("Writing music.zip!");
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(EditorMain.serverDataDir+"MusicData"))));

				ZipOutputStream zos = new ZipOutputStream(new FileOutputStream(EditorMain.htdocsZippedAssetsDir+"music.zip"));

				for (int i = 0; i < musicList.size(); i++) {
					try {
						Music s = musicList.get(i);

						//make COPY of data
						MusicData data = new MusicData();
						data.initFromString(s.getData().toString());
						System.out.println("Got Music " + s.getLongTypeName());

						String fullFilePath = data.fullFilePath();
						System.out.println("Path for music is " + data.fullFilePath());

						if(fullFilePath.toLowerCase().endsWith(".wav") && FileUtils.sizeOf(new File(data.fullFilePath()))>1024*50)
						{

							String originalFilePath = ""+fullFilePath;

							String fileName = data.fileName().substring(0,data.fileName().length()-4)+".ogg";
							data.setFileName(fileName);

							String oggDir = fullFilePath.substring(0,fullFilePath.lastIndexOf("\\"));
							Utils.makeDir(oggDir+"\\ogg\\");
							fullFilePath = oggDir+"\\ogg\\"+fileName;

							File f = new File(fullFilePath);
							if(f.exists()==false)
							{
								System.out.println("Encoding "+originalFilePath+"...");
								String[] commands = {EditorMain.oggEncPath, "-q 5", "--output=\""+fullFilePath+"\"", "\""+originalFilePath+"\""};
								try{Runtime.getRuntime().exec(commands).waitFor();}catch(InterruptedException e){e.printStackTrace();}
								System.out.println("Finished encoding");
							}

						}

						//remove filepath from COPY of data sent to server
						data.setFullFilePath("");

						File theFile = new File(fullFilePath);
						if (theFile.exists()) {
							if (s.preload()) {
								Utils.putFileInZipAsMD5(zos, fullFilePath);
							}


							String md5FileName = Utils.getFileMD5Checksum(fullFilePath);

							data.setMD5Name(md5FileName);
							s.setMD5Name(md5FileName);

							pw.println(data.toJSON());

							FileUtils.copyFile(new File(fullFilePath), new File(EditorMain.htdocsZippedAssetsDir + md5FileName));

							System.out.println("Copied to zip fullFilePath: " + fullFilePath + " other path: " + EditorMain.htdocsZippedAssetsDir + md5FileName);
						} else {
							System.out.println("It appears that the file at " + fullFilePath + " does not exist.");
						}
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
				pw.close();

				zos.close();
			} catch (IOException e1) {
				e1.printStackTrace();
			}
	}


	//===============================================================================================
	public void exportServerSoundAssetIndex()
	{//===============================================================================================

			//String oggTemp = EditorMain.exportDirectory;

			Utils.makeDir(EditorMain.serverDataDir);

			try
			{
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(new File(EditorMain.serverDataDir+"SoundData"))));

				ZipOutputStream zos = new ZipOutputStream(new FileOutputStream(EditorMain.htdocsZippedAssetsDir+"sounds.zip"));

				for(int i = 0; i < soundList.size(); i++)
				{
					Sound s = soundList.get(i);

					//make COPY of data
					SoundData data = new SoundData();
					data.initFromString(s.getData().toString());

					String fullFilePath = data.fullFilePath();

					File fileThing = new File(fullFilePath);
					if (fileThing.exists()) {
						if(fullFilePath.toLowerCase().endsWith(".wav") && FileUtils.sizeOf(new File(data.fullFilePath()))>1024*50)
						{

							String originalFilePath = ""+fullFilePath;

							String fileName = data.fileName().substring(0,data.fileName().length()-4)+".ogg";
							data.setFileName(fileName);

							String oggDir = fullFilePath.substring(0,fullFilePath.lastIndexOf("\\"));
							Utils.makeDir(oggDir+"\\ogg\\");
							fullFilePath = oggDir+"\\ogg\\"+fileName;

							File f = new File(fullFilePath);
							if(f.exists()==false)
							{

								String[] commands = {EditorMain.oggEncPath, "-q 5", "--output=\""+fullFilePath+"\"", "\""+originalFilePath+"\""};
								try{Runtime.getRuntime().exec(commands).waitFor();}catch(InterruptedException e){e.printStackTrace();}
							}

						}

						//remove filepath from COPY of data sent to server
						data.setFullFilePath("");

						String md5FileName = Utils.putFileInZipAsMD5(zos,fullFilePath);

						data.setMD5Name(md5FileName);
						s.setMD5Name(md5FileName);

						pw.println(data.toJSON());
					} else {
						System.out.println(fullFilePath + " does not exist.");
					}
				}
				pw.close();

				zos.close();
			}
			catch (FileNotFoundException e1){}
			catch (IOException e){}
	}




	//String dirpath = "";

	//===============================================================================================
	public void clearEventsListsForProjectSave()
	{//===============================================================================================

		for(int i=0;i<eventList.size();i++)
		{
			Event e = eventList.get(i);
			EventData d = e.getData();

			d.dialogueDataList = new ArrayList<DialogueData>();
			d.flagDataList = new ArrayList<FlagData>();
			d.skillDataList = new ArrayList<SkillData>();
			d.gameStringDataList = new ArrayList<GameStringData>();
			d.musicDataList = new ArrayList<MusicData>();
			d.soundDataList = new ArrayList<SoundData>();

		}

	}

	//===============================================================================================
	public void prepareEventsForExport()
	{//===============================================================================================

		for(int i=0;i<eventList.size();i++)
		{
			Event e = eventList.get(i);
			EventData d = e.getData();

			d.dialogueDataList = new ArrayList<DialogueData>();
			d.flagDataList = new ArrayList<FlagData>();
			d.skillDataList = new ArrayList<SkillData>();
			d.gameStringDataList = new ArrayList<GameStringData>();
			d.musicDataList = new ArrayList<MusicData>();
			d.soundDataList = new ArrayList<SoundData>();


			String t = "";
			String type = "";



			t = new String(d.text());
			type = "DIALOGUE.";
			while(t.contains(type))
			{
				t = t.substring(t.indexOf(type));
				t = t.substring(t.indexOf(".")+1);

				String id = "";
				while(t.startsWith(")")==false && t.startsWith("|")==false)
				{
					id += t.substring(0,1);
					t = t.substring(1);
				}
				d.dialogueDataList.add(((Dialogue)getMapObjectByTYPEIDName(type+id)).getData());
			}

			t = new String(d.text());
			type = "FLAG.";
			while(t.contains(type))
			{
				t = t.substring(t.indexOf(type));
				t = t.substring(t.indexOf(".")+1);

				String id = "";
				while(t.startsWith(")")==false && t.startsWith("|")==false)
				{
					id += t.substring(0,1);
					t = t.substring(1);
				}
				d.flagDataList.add(((Flag)getMapObjectByTYPEIDName(type+id)).getData());
			}

			t = new String(d.text());
			type = "SKILL.";
			while(t.contains(type))
			{
				t = t.substring(t.indexOf(type));
				t = t.substring(t.indexOf(".")+1);

				String id = "";
				while(t.startsWith(")")==false && t.startsWith("|")==false)
				{
					id += t.substring(0,1);
					t = t.substring(1);
				}
				d.skillDataList.add(((Skill)getMapObjectByTYPEIDName(type+id)).getData());
			}

			t = new String(d.text());
			type = "GAMESTRING.";
			while(t.contains(type))
			{
				t = t.substring(t.indexOf(type));
				t = t.substring(t.indexOf(".")+1);

				String id = "";
				while(t.startsWith(")")==false && t.startsWith("|")==false)
				{
					id += t.substring(0,1);
					t = t.substring(1);
				}
				d.gameStringDataList.add(((GameString)getMapObjectByTYPEIDName(type+id)).getData());
			}

			t = new String(d.text());
			type = "MUSIC.";
			while(t.contains(type))
			{
				t = t.substring(t.indexOf(type));
				t = t.substring(t.indexOf(".")+1);

				String id = "";
				while(t.startsWith(")")==false && t.startsWith("|")==false)
				{
					id += t.substring(0,1);
					t = t.substring(1);
				}
				d.musicDataList.add(((Music)getMapObjectByTYPEIDName(type+id)).getData());
			}

			t = new String(d.text());
			type = "SOUND.";
			while(t.contains(type))
			{
				t = t.substring(t.indexOf(type));
				t = t.substring(t.indexOf(".")+1);

				String id = "";
				while(t.startsWith(")")==false && t.startsWith("|")==false)
				{
					id += t.substring(0,1);
					t = t.substring(1);
				}
				d.soundDataList.add(((Sound)getMapObjectByTYPEIDName(type+id)).getData());
			}

		}

	}

	//===============================================================================================
	public void exportProject()
	{//===============================================================================================


		prepareEventsForExport();



		makeDirs();

		exportPalettes();
		exportMapTilesets();
		exportSpriteData();






		exportServerMapAssetIndex();
		exportServerSpriteAssetIndex();

		exportServerDialogueAssetIndex();
		exportServerCutsceneEventAssetIndex();
		exportServerGameStringAssetIndex();
		exportServerFlagAssetIndex();
		exportServerPlayerSkillAssetIndex();

		exportServerMusicAssetIndex();
		exportServerSoundAssetIndex();

		exportClientPreloadedAssets();
//		exportClientPreloadedSoundAssetIndex();
//		exportClientPreloadedMusicAssetIndex();
//		exportClientPreloadedPlayerSkillIndex();
//		exportClientPreloadedSpriteAssetIndex();
//		exportClientPreloadedMapAssetIndex();


		//delete directory c:\Users\Administrator\bobsgamecache
		//copy desktop\bobsgametemp\htdocs\z\maps.zip, sprites.zip to c:\xampp\htdocs\z\

		//File cache = new File("C:\\Users\\Administrator\\bobsGameCache");
		//cache.delete();


		//File tempDir = new File(dirpath);
		//tempDir.delete();



		//run C:\Java\jdk1.7.0f_02-64bit\bin\java.exe -jar c:\eclipse\plugins\eclipse-core.jar -cp C:\Java\libs\ c:\Users\Administrator\workspace\BobsGameServer\ ServerMain
		//run C:\Java\jdk1.7.0f_02-64bit\bin\java.exe -cp C:\Java\libs\ c:\Users\Administrator\workspace\BobsGameServer\ ServerMain.class


		//try
		//{
			//Runtime.getRuntime().exec("C:\\Users\\Administrator\\workspace\\deleteCacheAndTemp.cmd");
		//}
		//catch (IOException e)
		//{

			//e.printStackTrace();
		//}



		EditorMain.infoLabel.setTextSuccess("Exported project to htdocs/z/asset.zips and workspace/project/res/objectData");



	}

/*

	//===============================================================================================
	public com.bobsgame.client.engine.map.Map addMapToClient(Map editorMap)
	{//===============================================================================================


		String dirpath = EditorMain.getDesktopTempDirPath() + "htdocs\\bin\\tilemap\\";

		//Utils.makeDir(dirpath);
		//Utils.makeDir(dirpath + name() + "\\");

		String cachePath = "C:\\Users\\Administrator\\.bobsGame\\";


		MapData mapData = new MapData();
		data.initFromString(editorMap.getData().toString());

		if(mapData.groundLayerMD5()==null||mapData.groundLayerMD5().length()<1)
		{
			editorMap.outputUniqueTilesetForSingleMapSeparatedBINs();

			//set currentmap loaded md5s
			for(int l=0;l<MapData.layers;l++)
			{
				if(MapData.isTileLayer(l))
				{

					String filename = dirpath + editorMap.name() + "\\"+l;
					String md5FileName = Utils.getFileMD5Checksum(filename);

					if(l==MapData.MAP_GROUND_LAYER){mapData.setGroundLayerMD5(md5FileName);}
					if(l==MapData.MAP_GROUND_DETAIL_LAYER){mapData.setGroundObjectsMD5(md5FileName);}
					if(l==MapData.MAP_GROUND_SHADOW_LAYER){mapData.setGroundShadowMD5(md5FileName);}
					if(l==MapData.MAP_OBJECT_LAYER){mapData.setObjectsMD5(md5FileName);}
					if(l==MapData.MAP_OBJECT_DETAIL_LAYER){mapData.setObjects2MD5(md5FileName);}
					if(l==MapData.MAP_OBJECT_SHADOW_LAYER){mapData.setObjectShadowMD5(md5FileName);}
					if(l==MapData.MAP_ABOVE_LAYER){mapData.setAboveMD5(md5FileName);}
					if(l==MapData.MAP_ABOVE_DETAIL_LAYER){mapData.setAbove2MD5(md5FileName);}
					if(l==MapData.MAP_SPRITE_SHADOW_LAYER){mapData.setSpriteShadowMD5(md5FileName);}
					if(l==MapData.MAP_SHADER_LAYER){mapData.setGroundShaderMD5(md5FileName);}
					if(l==MapData.MAP_LIGHT_MASK_LAYER){mapData.setLightMaskMD5(md5FileName);}
					if(l==MapData.MAP_CAMERA_BOUNDS_LAYER){mapData.setCameraBoundsMD5(md5FileName);}
					if(l==MapData.MAP_HIT_LAYER){mapData.setHitBoundsMD5(md5FileName);}

					//copy to cache folder with md5 name
					try{FileUtils.copyFile(new File(filename),new File(cachePath+md5FileName));}catch(IOException e){e.printStackTrace();}
				}
			}


			{
				String filename;
				String md5FileName;

				filename = dirpath + editorMap.name() + "\\t";
				md5FileName = Utils.getFileMD5Checksum(filename);
				mapData.setTilesMD5(md5FileName);
				try{FileUtils.copyFile(new File(filename),new File(cachePath+md5FileName));}catch(IOException e){e.printStackTrace();}


				filename = dirpath + editorMap.name() + "\\p";
				md5FileName = Utils.getFileMD5Checksum(filename);
				mapData.setPaletteMD5(md5FileName);
				try{FileUtils.copyFile(new File(filename),new File(cachePath+md5FileName));}catch(IOException e){e.printStackTrace();}
			}
		}


		//fill in currentmap
		com.bobsgame.client.engine.map.Map clientMap = new com.bobsgame.client.engine.map.Map(ClientMain.clientMain.clientGameEngine,mapData);
		ClientMain.clientMain.clientGameEngine.MapManager().mapList.add(clientMap);
		ClientMain.clientMain.clientGameEngine.MapManager().mapByNameHashMap.put(mapData.name(),clientMap);
		ClientMain.clientMain.clientGameEngine.MapManager().mapByIDHashMap.put(mapData.id(),clientMap);

		for(int i=0;i<clientMap.doorList.size();i++)
		{
			//TODO: this is a hack
			clientMap.doorList.get(i).getData().setDestinationMapName(((Door)Project.getMapObjectByTYPEIDName(clientMap.doorList.get(i).destinationTYPEIDString())).map().name());
			clientMap.doorList.get(i).getData().setDestinationDoorName(((Door)Project.getMapObjectByTYPEIDName(clientMap.doorList.get(i).destinationTYPEIDString())).name());
		}

		return clientMap;

	}*/

	//===============================================================================================
	public void previewMapInClient()
	{//===============================================================================================

/*
		ClientMain.clientMain = new ClientMain();
		ClientMain.previewClientInEditor = true;

		ClientMain.clientMain.mainInit();

		ClientMain.clientMain.stateManager.setState(ClientMain.clientMain.clientGameEngine);

		ClientMain.clientMain.clientGameEngine.setInitialGameSaveReceived_S(true);




		for(int i=0;i<cutsceneEventIDList.size();i++)
		{
			Event e = getEventByID(cutsceneEventIDList.get(i));
			if(e.type()==EventData.TYPE_PROJECT_INITIAL_LOADER)
			{
				ClientMain.clientMain.clientGameEngine.setProjectLoadEventID_S(e.id());
			}
		}

		//fill in gamesave
		GameSave g = new GameSave();
		g.lastKnownRoom = getSelectedMap().name();

		// fill in char appearance, name
		g.characterAppearance = "1,1,1,1,1,1,1,1";
		g.characterName = "bob";
		g.postalCode = "95817";



		//fill in player start location, pick a door?
		if(getSelectedMap().getSelectedArea()!=null)
		{
			g.lastKnownX = getSelectedMap().getSelectedArea().xP()*2;
			g.lastKnownY = getSelectedMap().getSelectedArea().yP()*2;
		}
		else
		if(getSelectedMap().getNumDoors()>0)
		{
			g.lastKnownX = getSelectedMap().getDoor(0).arrivalXPixels()*2;
			g.lastKnownY = getSelectedMap().getDoor(0).arrivalYPixels()*2;
		}
		else
		{
			g.lastKnownX = getSelectedMap().wP()/2*2;
			g.lastKnownY = getSelectedMap().hP()/2*2;
		}


		//set gamesave loaded
		ClientMain.clientMain.clientGameEngine.setGameSave_S(g);
		ClientMain.clientMain.clientGameEngine.setGameSaveInitialized_S(true);



		//fill in events
		for(int i=0;i<eventList.size();i++)
		{
			Event e = eventList.get(i);
			EventData data = gson.fromJson(gson.toJson(e.getData()),EventData.class);
			new com.bobsgame.client.engine.event.Event(ClientMain.clientMain.clientGameEngine,data);
		}

		//fill in dialogues
		for(int i=0;i<dialogueList.size();i++)
		{
			Dialogue e = dialogueList.get(i);
			DialogueData data = gson.fromJson(gson.toJson(e.getData()),DialogueData.class);
			new com.bobsgame.client.engine.event.Dialogue(ClientMain.clientMain.clientGameEngine,data);
		}

		//fill in gamestrings
		for(int i=0;i<gameStringList.size();i++)
		{
			GameString e = gameStringList.get(i);
			GameStringData data = gson.fromJson(gson.toJson(e.getData()),GameStringData.class);
			new com.bobsgame.client.engine.event.GameString(ClientMain.clientMain.clientGameEngine,data);
		}

		//fill in flags
		for(int i=0;i<flagList.size();i++)
		{
			Flag e = flagList.get(i);
			FlagData data = gson.fromJson(gson.toJson(e.getData()),FlagData.class);
			new com.bobsgame.client.engine.event.Flag(ClientMain.clientMain.clientGameEngine,data);
		}
		//fill in skills
		for(int i=0;i<skillList.size();i++)
		{
			Skill e = skillList.get(i);
			SkillData data = gson.fromJson(gson.toJson(e.getData()),SkillData.class);
			new com.bobsgame.client.engine.event.Skill(ClientMain.clientMain.clientGameEngine,data);
		}

		//fill in sounds
		for(int i=0;i<soundList.size();i++)
		{
			Sound e = soundList.get(i);
			SoundData data = gson.fromJson(gson.toJson(e.getData()),SoundData.class);

			if(data.fileName().toLowerCase().endsWith(".wav") && FileUtils.sizeOf(new File(data.fullFilePath()))>1024*50)
			data.setFileName(data.fileName().substring(0,data.fileName().length()-4)+".ogg");


			new com.bobsgame.client.engine.sound.Sound(ClientMain.clientMain.clientGameEngine,data);
		}

		//fill in music
		for(int i=0;i<musicList.size();i++)
		{
			Music e = musicList.get(i);

			//if(e.preload()==false)continue;

			MusicData data = gson.fromJson(gson.toJson(e.getData()),MusicData.class);

			if(data.fileName().toLowerCase().endsWith(".wav") && FileUtils.sizeOf(new File(data.fullFilePath()))>1024*50)
			data.setFileName(data.fileName().substring(0,data.fileName().length()-4)+".ogg");

			//this is why i'm getting errors, not all the music files exist in music.zip but they all exist here
			// check md5name exists in the cache, if not, copy it there, it is actually copying from htdocs during gameplay! neat.
			if(new File("C:\\Users\\Administrator\\.bobsGame\\"+data.md5Name()).exists()==false)
			{
				try
				{
					FileUtils.copyFile(new File(EditorMain.htdocsZippedAssetsDir+data.md5Name()),new File("C:\\Users\\Administrator\\.bobsGame\\"+data.md5Name()));
				}
				catch(IOException e1)
				{
					e1.printStackTrace();
				}
			}

			new com.bobsgame.client.engine.sound.Music(ClientMain.clientMain.clientGameEngine,data);
		}



		makeDirs();


		//save current map data to cache folder with md5 names, store md5 names
		//set all currentmap state, entitydata, areadata, lightdata, etc

		//com.bobsgame.client.engine.map.Map clientMap = addMapToClient(getSelectedMap());

		//ClientMain.clientMain.clientGameEngine.MapManager().currentMap =
//		addMapToClient(getSelectedMap());
//
//
//
//		for(int i=0;i<getSelectedMap().getNumDoors();i++)
//		{
//			Map map = getSelectedMap().getDoor(i).destinationDoor().map();
//			if(map!=null&&map!=getSelectedMap())
//			{
//				addMapToClient(map);
//			}
//		}

		for(int i=0;i<Project.mapList.size();i++)
		{
			addMapToClient(Project.mapList.get(i));
		}


		//fill in sprites
		String dirpath = EditorMain.getDesktopTempDirPath() + "htdocs\\bin\\sprite\\";

		//Utils.makeDir(dirpath);
		//Utils.makeDir(dirpath + name() + "\\");

		String cachePath = "C:\\Users\\Administrator\\.bobsGame\\";


		ArrayList<Sprite> usedSprites = new ArrayList<Sprite>();


		//this is done by clientData
//		for(int i=0;i<spriteList.size();i++)
//		{
//			Sprite sp = spriteList.get(i);
//			if(sp.forceMD5Export()&&usedSprites.contains(sp)==false)usedSprites.add(sp);
//		}



//		usedSprites.add(Project.getSpriteByName("actionIcon"));
//		usedSprites.add(Project.getSpriteByName("bob"));
//
//		for(int i=0;i<getSelectedMap().getNumDoors();i++)
//		{
//			Door e = getSelectedMap().getDoor(i);
//			Sprite sp = e.getSprite();
//			if(sp!=null&&usedSprites.contains(sp)==false)usedSprites.add(sp);
//		}
//		for(int s=0;s<getSelectedMap().getNumStates();s++)
//		{
//			for(int i=0;i<getSelectedMap().getState(s).getNumEntities();i++)
//			{
//				Entity e = getSelectedMap().getState(s).getEntity(i);
//				Sprite sp = e.getSprite();
//				if(sp!=null&&usedSprites.contains(sp)==false)usedSprites.add(sp);
//			}
//		}



		usedSprites = Project.spriteList;


		for(int i=0;i<usedSprites.size();i++)
		{

			Sprite editorSprite = usedSprites.get(i);

			SpriteData spriteData = editorSprite.getData();//new SpriteData(s.id,s.name(),s.displayName,s.width(),s.height(),s.frames(),s.isNPC,s.isKid,s.isAdult,s.isMale,s.isFemale,s.isCar,s.isAnimal,s.hasShadow,s.isRandom,s.isDoor,s.isGame,s.isItem,s.clientForceHQ2X,s.eventID,s.itemGameDescription,gamePriceFloat,s.utilityPointOffsetX,s.utilityPointOffsetY,"","");
			spriteData = gson.fromJson(gson.toJson(spriteData),SpriteData.class);

			if(spriteData.dataMD5()==null || spriteData.dataMD5().length()<1)
			{
				editorSprite.outputBINWithCustomPalette();

				String filename = dirpath + editorSprite.name() + "_SpriteDataUnique" + ".bin";
				String filenamePalette = dirpath + editorSprite.name() + "_SpritePaletteUnique" + ".bin";

				String md5FileName = Utils.getFileMD5Checksum(filename);
				String md5FileNamePalette = Utils.getFileMD5Checksum(filenamePalette);

				spriteData.setDataMD5(md5FileName);
				try{FileUtils.copyFile(new File(filename),new File(cachePath+md5FileName));}catch(IOException e){e.printStackTrace();}

				spriteData.setPaletteMD5(md5FileNamePalette);
				try{FileUtils.copyFile(new File(filename),new File(cachePath+md5FileName));}catch(IOException e){e.printStackTrace();}
			}

			com.bobsgame.client.engine.entity.Sprite clientSprite = new com.bobsgame.client.engine.entity.Sprite(ClientMain.clientMain.clientGameEngine);

			//SpriteData d = editorSprite.getData();

			clientSprite.initalizeWithSpriteData(spriteData);
			ClientMain.clientMain.clientGameEngine.SpriteManager().spriteByNameHashMap.put(clientSprite.name(),clientSprite);
			ClientMain.clientMain.clientGameEngine.SpriteManager().spriteByIDHashMap.put(clientSprite.id(),clientSprite);

		}

		try
		{
			ClientMain.clientMain.mainLoop();
		}
		catch(Exception e){e.printStackTrace();}

		try
		{
			ClientMain.clientMain.cleanup();
		}
		catch(Exception e){e.printStackTrace();}
*/
	}







}
