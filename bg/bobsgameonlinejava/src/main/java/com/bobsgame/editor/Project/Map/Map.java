package com.bobsgame.editor.Project.Map;

import java.io.*;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.util.ArrayList;

import java.awt.*;

import java.awt.image.*;

import javax.swing.Timer;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.HQ2X;
import com.bobsgame.editor.MapCanvas.MapCanvas;
import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Tileset;
import com.bobsgame.editor.Project.TilesetPalette;
import com.bobsgame.editor.Project.Event.Event;
import com.bobsgame.editor.Project.Sprite.Sprite;
import com.bobsgame.shared.AreaData;
import com.bobsgame.shared.EntityData;
import com.bobsgame.shared.EventData;
import com.bobsgame.shared.LightData;
import com.bobsgame.shared.MapData;
import com.bobsgame.shared.MapStateData;
import com.bobsgame.shared.Utils;
import com.bobsgame.shared.MapData.RenderOrder;
//===============================================================================================
public class Map implements ImageObserver, GameObject
{//===============================================================================================

	public int layerTileIndex[][][];

	public BufferedImage layerImage[];
	public boolean layerImagesAllocated = false;


	private int selectedDoorIndex=-1;
	//private ArrayList<Door> doorList = new ArrayList<Door>();

	private int selectedState=0;
	//private ArrayList<MapState> stateList = new ArrayList<MapState>();





	//public ArrayList<Integer> ONLOADeventIDList = new ArrayList<Integer>();//hack to store the event IDs on load, which i then use to fill the eventList after the events are parsed.
	//don't need to do this, save the event objects before the maps so they exist when the maps load and can reference them by ID.

	//private ArrayList<Event> mapEventList = new ArrayList<Event>();




	public static final String DEFAULT_STATE_NAME = "DEFAULT";
	public static final String DEFAULT_LOAD_EVENT_NAME = "Load";
	public static final String DEFAULT_LOAD_EVENT_COMMAND = "loadMapState";



	




	public Color CLEAR = new Color(0,0,0,0);



	private MapData data;




	//===============================================================================================
	public Map(String name, int widthTiles, int heightTiles)
	{//===============================================================================================

		int id = getBiggestID();

		this.data = new MapData(id,name,widthTiles,heightTiles);

		layerTileIndex = new int[MapData.layers][wT()][hT()];

		Project.mapList.add(this);
		Project.mapHashtable.put(getTYPEIDString(),this);

		init();

	}

	//===============================================================================================
	public Map(MapData data)
	{//===============================================================================================
		this.data = data;

		layerTileIndex = new int[MapData.layers][wT()][hT()];

		if(Project.mapHashtable.get(getTYPEIDString())!=null)
		{
			System.err.println("Map ID for Map: "+name()+" already exists. Creating new ID.");
			int id = getBiggestID();
			setID(id);
		}

		Project.mapList.add(this);
		Project.mapHashtable.put(getTYPEIDString(),this);

		init();
	}

	//===============================================================================================
	public void init()
	{//===============================================================================================


		for(int i=0;i<getData().eventDataList().size();i++)
		{
			new Event(getData().eventDataList().get(i));
		}

		for(int i=0;i<getData().doorDataList().size();i++)
		{
			Door door = new Door(this,getData().doorDataList().get(i));


		}

		for(int i=0;i<getData().stateDataList().size();i++)
		{
			new MapState(this,getData().stateDataList().get(i));
		}

		for(int s=0;s<getNumStates();s++)
		{

			MapState state = getState(s);

			MapStateData data = state.getData();

			for(int i=0;i<data.areaDataList().size();i++)
			{
				AreaData areaData = data.areaDataList().get(i);

				Area area = new Area(this,state,areaData);

			}

			for(int i=0;i<data.entityDataList().size();i++)
			{
				EntityData entityData = data.entityDataList().get(i);


				Entity entity = new Entity(this,state,entityData);

			}

			for(int i=0;i<data.lightDataList().size();i++)
			{
				LightData lightData = data.lightDataList().get(i);


				new Light(this,state,lightData);

			}

		}

	}

	//===============================================================================================
	public int getBiggestID()
	{//===============================================================================================
		int id = -1;

		int size=Project.mapList.size();
		if(size==0)id=0;
		else
		{
			int biggest=0;
			for(int i=0;i<size;i++)
			{
				int testid = Project.mapList.get(i).id();
				if(testid>biggest)biggest=testid;
			}
			id=biggest+1;
		}
		return id;

	}


	//===============================================================================================
	public MapState addDefaultMapState()
	{//===============================================================================================
		MapState mapState = new MapState(this,DEFAULT_STATE_NAME);

		addState(mapState);

		return mapState;

	}

	//===============================================================================================
	public MapState getDefaultMapStateCreateIfNotExist()
	{//===============================================================================================
		MapState defaultMapState = null;
		for(int i=0;i<getNumStates();i++)
		{
			MapState mapState = getState(i);
			if(mapState.name().equals(DEFAULT_STATE_NAME))
			{
				defaultMapState = mapState;
				break;
			}
		}

		if(defaultMapState==null)defaultMapState = addDefaultMapState();

		return defaultMapState;

	}

	//===============================================================================================
	public void addDefaultLoadMapStateEvent()
	{//===============================================================================================

		MapState defaultMapState = getDefaultMapStateCreateIfNotExist();

		addEvent(new Event(EventData.TYPE_MAP_RUN_ONCE_BEFORE_LOAD, name()+"."+DEFAULT_LOAD_EVENT_NAME, "", "{"+DEFAULT_LOAD_EVENT_COMMAND+"(STATE."+defaultMapState.id()+")}"));
	}
	//===============================================================================================
	public void renameAllEventsToName()
	{//===============================================================================================

		//all event names look like MapName.EventName

		for(int i=0;i<getNumEvents();i++)
		{
			Event event = getEvent(i);

			String newName = this.name()+event.name().substring(event.name().indexOf("."));
			event.setName(newName);
		}

	}




	//===============================================================================================
	public void setName(String s)
	{//===============================================================================================


		//don't have to do this anymore, everything is tracked by id


		//go through all maps, find area.destination that starts with oldmapname.? and change it to newmapname.?
//		for(int m=0;m<Project.getNumMaps();m++)
//		{
//
//			for(int n=0;n<Project.getMap(m).getNumDoors();n++)
//			{
//				Event event = Project.getEventByID(Project.getMap(m).getDoor(n).eventID);
//				if(event!=null)event.renameMapString(name, newName);
//			}
//
//
//			for(int s=0;s<Project.getMap(m).getNumStates();s++)
//			{
//
//				for(int n=0;n<Project.getMap(m).getState(s).getNumAreas();n++)
//				{
//
//					Event event = Project.getEventByID(Project.getMap(m).getState(s).getArea(n).eventID);
//					if(event!=null)event.renameMapString(name, newName);
//
//				}
//
//				for(int n=0;n<Project.getMap(m).getState(s).getNumEntities();n++)
//				{
//					Event event = Project.getEventByID(Project.getMap(m).getState(s).getEntity(n).eventID);
//					if(event!=null)event.renameMapString(name, newName);
//				}
//			}
//		}

		data.setName(s);

		renameAllEventsToName();

	}


	//===============================================================================================
	public int[] getLayerAsIntArray(int l)
	{//===============================================================================================

		int[] intArray = new int[wT()*hT()];


		for(int y = 0; y < hT(); y++)
		{

			for(int x = 0; x < wT(); x++)
			{

				int i = layerTileIndex[l][x][y];

				int index = (y*wT())+(x);

				intArray[index]=i;
			}
		}

		return intArray;

	}

	//===============================================================================================
	public byte[] getLayerAsByteArray(int l)
	{//===============================================================================================

		return Utils.getByteArrayFromIntArray(getLayerAsIntArray(l));
	}


	//===============================================================================================
	public void initializeLayerFromIntArray(int l, int[] intArray)
	{//===============================================================================================
		for(int y = 0; y < hT(); y++)
		{

			for(int x = 0; x < wT(); x++)
			{

				int index = (y*wT())+(x);

				int i = intArray[index];



				layerTileIndex[l][x][y] = i;

			}
		}

	}


	//===============================================================================================
	public class MapBinWithUniqueTilesetAndPalette
	{//===============================================================================================

		public int[] mapLayerDataIntArray;
		public int[] tileDataIntArray;
		public byte[] paletteRGBByteArray;


		public byte[] getIndividualMapLayerIntArrayAsByteArray(int l)
		{
			ByteBuffer byteBuffer = ByteBuffer.allocate(wT()*hT() * 4);
			IntBuffer intBuffer = byteBuffer.asIntBuffer();

			for(int i=0;i<wT()*hT();i++)
			intBuffer.put(mapLayerDataIntArray[(l*wT()*hT())+i]);

			return byteBuffer.array();
		}



		public String getMapDataIntArrayAsGZippedBase64String()
		{
			return Utils.encodeStringToBase64(Utils.zipByteArrayToString(Utils.getByteArrayFromIntArray(mapLayerDataIntArray)));
		}

		public String getTileDataIntArrayAsGZippedBase64String()
		{
			return Utils.encodeStringToBase64(Utils.zipByteArrayToString(Utils.getByteArrayFromIntArray(tileDataIntArray)));
		}
		public String getPaletteRGBByteArrayAsGZippedBase64String()
		{
			return Utils.encodeStringToBase64(Utils.zipByteArrayToString(paletteRGBByteArray));
		}
	}


	//===============================================================================================
	public MapBinWithUniqueTilesetAndPalette makeMapBinWithUniqueTilesetAndPalette()
	{//===============================================================================================
		MapBinWithUniqueTilesetAndPalette m = new MapBinWithUniqueTilesetAndPalette();


		//counting tiles, making virtual tileset based on used tiles only, only for layers 0,1,2,3
		int uniqueTileset[][][] = new int[Tileset.num_Tiles][Tileset.tileWidth][Tileset.tileHeight];
		int uniqueTileIndex[] = new int[Tileset.num_Tiles];
		int uniqueTileCount = 0;
		int uniqueMap[][][] = new int[MapData.layers][wT()][hT()];


		//fill vmap with 0
		for(int l = 0; l < MapData.layers; l++)
		{
			for(int y = 0; y < hT(); y++)
			{
				for(int x = 0; x < wT(); x++)
				{
					uniqueMap[l][x][y] = 0;
				}
			}
		}

		//set vtile 0 to blank tile
		for(int ty = 0; ty < 8; ty++)
		{
			for(int tx = 0; tx < 8; tx++)
			{
				uniqueTileset[uniqueTileCount][tx][ty] = 0;
			}
		}

		uniqueTileIndex[uniqueTileCount] = 0;
		uniqueTileCount++;


		for(int l = 0; l < MapData.layers; l++)
		{
			for(int x = 0; x < wT(); x++)
			{
				for(int y = 0; y < hT(); y++)
				{

					//just set direct values for non-graphical tile layers
					if(
							l == MapData.MAP_SHADER_LAYER
							||l == MapData.MAP_LIGHT_MASK_LAYER
							||l == MapData.MAP_CAMERA_BOUNDS_LAYER
							||l == MapData.MAP_HIT_LAYER
					)
					{
						uniqueMap[l][x][y] = layerTileIndex[l][x][y];
					}
					else
					if(MapData.isTileLayer(l)==true)
					{
						boolean foundtile = false;
						for(int i = 0; i < uniqueTileCount; i++)
						{
							if(layerTileIndex[l][x][y] == uniqueTileIndex[i])
							{
								uniqueMap[l][x][y] = i;
								foundtile = true;

								i=uniqueTileCount;
								break;
							}
						}

						if(foundtile == false)
						{
							boolean compareForDupes = false;//slow down exporting a lot.
							if(compareForDupes)
							{

								for(int i=0;i<uniqueTileCount;i++)
								{
									boolean isTheSame=true;
									for(int ty = 0; ty < 8; ty++)
									{
										for(int tx = 0; tx < 8; tx++)
										{
											int tileIndex = layerTileIndex[l][x][y];
											if(uniqueTileset[i][tx][ty]!=Project.tileset.tilePaletteIndex[tileIndex][tx][ty])
											{
												isTheSame=false;

												tx=8;
												ty=8;
												break;
											}
										}
									}
									if(isTheSame==true)
									{
										uniqueMap[l][x][y] = i;
										foundtile=true;
										break;
									}
								}
								if(foundtile==true)continue;
							}

							for(int ty = 0; ty < 8; ty++)
							{
								for(int tx = 0; tx < 8; tx++)
								{
									int tileIndex = layerTileIndex[l][x][y];
									uniqueTileset[uniqueTileCount][tx][ty] = Project.tileset.tilePaletteIndex[tileIndex][tx][ty];
								}
							}
							uniqueMap[l][x][y] = uniqueTileCount;
							uniqueTileIndex[uniqueTileCount] = layerTileIndex[l][x][y];
							uniqueTileCount++;
						}
					}
				}
			}
		}


		System.out.println("Map " + name() + " has " + (uniqueTileCount - 1) + " tiles");



		//create new unique palette, reindex the uniqueTileset values by the new palette colors, add into m.tileDataIntArray

		ArrayList<Color> newPal = new ArrayList<Color>();
		newPal.add(Project.getSelectedPalette().getColor(0));
		newPal.add(Project.getSelectedPalette().getColor(1));
		newPal.add(Project.getSelectedPalette().getColor(2));


		m.tileDataIntArray = new int[uniqueTileCount*Tileset.tileWidth*Tileset.tileHeight];
		for(int t=0;t<uniqueTileCount;t++)
		{
			for(int y=0;y<Tileset.tileHeight;y++)
			{
				for(int x=0;x<Tileset.tileWidth;x++)
				{

					int oldPalIndex = uniqueTileset[t][x][y];

					Color c = Project.getSelectedPalette().getColor(oldPalIndex);

					//run through palette and see if color exists
					//if it doesn't, add it.
					int newPalIndex=-1;
					for(int i=0;i<newPal.size();i++)
					{
						if(newPal.get(i)==c){newPalIndex=i;break;}
					}
					if(newPalIndex==-1)//we didn't find the color
					{
						newPal.add(c);//add the new color to newpal
						newPalIndex = newPal.size()-1;
					}

					int index = (t*Tileset.tileWidth*Tileset.tileHeight) + (y*Tileset.tileWidth) + x;
					m.tileDataIntArray[index] = newPalIndex;
				}
			}
		}

		//fill the RGB byte palette with the unique palette color values
		m.paletteRGBByteArray = new byte[newPal.size()*3];
		for(int i=0;i<newPal.size();i++)
		{
			m.paletteRGBByteArray[i*3+0] = (byte)newPal.get(i).getRed();
			m.paletteRGBByteArray[i*3+1] = (byte)newPal.get(i).getGreen();
			m.paletteRGBByteArray[i*3+2] = (byte)newPal.get(i).getBlue();
		}


		//now for each layer, fill the intArray
		m.mapLayerDataIntArray = new int[MapData.layers*wT()*hT()];

		for(int l = 0; l < MapData.layers; l++)
		{
			for(int y = 0; y < hT(); y++)
			{
				for(int x = 0; x < wT(); x++)
				{
					int value = uniqueMap[l][x][y];

					int index = (l*wT()*hT()) + (y*wT()) + x;

					m.mapLayerDataIntArray[index] = value;
				}
			}
		}


		return m;
	}



	//===============================================================================================
	public void outputUniqueTilesetForSingleMapSeparatedBINs()
	{//===============================================================================================


		String dirpath = EditorMain.getDesktopTempDirPath() + "htdocs\\bin\\tilemap\\";

		Utils.makeDir(dirpath);
		Utils.makeDir(dirpath + name() + "\\");

		MapBinWithUniqueTilesetAndPalette m = makeMapBinWithUniqueTilesetAndPalette();


		try
		{
			BufferedOutputStream fouts = null;

			for(int l = 0; l < MapData.layers; l++)
			{
				if(MapData.isTileLayer(l))
				{
					fouts = new BufferedOutputStream(new FileOutputStream(new File(dirpath + name() + "\\"+l)));
					fouts.write(m.getIndividualMapLayerIntArrayAsByteArray(l));
					fouts.close();
				}
			}

			//output unique tileset to bin
			fouts = new BufferedOutputStream(new FileOutputStream(new File(dirpath + name() + "\\t")));
			fouts.write(Utils.getByteArrayFromIntArray(m.tileDataIntArray));
			fouts.close();

			//output unique palette to bin
			fouts = new BufferedOutputStream(new FileOutputStream(new File(dirpath + name() + "\\p")));
			fouts.write(m.paletteRGBByteArray);
			fouts.close();

		}
		catch(FileNotFoundException fnfe){System.out.println("Could not create file.");}
		catch(IOException e){}


//
//		//now lets zip all those files, including the palette too
//		try
//		{
//
//			ZipOutputStream zos = new ZipOutputStream(new FileOutputStream(dirpath + "bin\\tilemap\\" + name() + "\\map.zip"));
//			for(int l=0;l<MapData.num_Layers;l++)
//			{
//				if(isTileLayer(l))
//				{
//					Utils.putFileInZipAsMD5(zos,dirpath + "bin\\tilemap\\" + name() + "\\"+l);
//				}
//			}
//			Utils.putFileInZipAsMD5(zos,dirpath + "bin\\tilemap\\" + name() + "\\t");
//			Utils.putFileInZipAsMD5(zos,dirpath + "bin\\tilemap\\" + name() + "\\p");
//
//			//close the stream
//			zos.close();
//		}
//		catch(Exception e)
//		{
//			e.printStackTrace();
//		}



		for(int l=0;l<MapData.layers;l++)
		{
			if(MapData.isTileLayer(l))
			{

				String filename = dirpath + name() + "\\"+l;
				String md5FileName = Utils.getFileMD5Checksum(filename);

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

		setTilesMD5(Utils.getFileMD5Checksum(dirpath + name() + "\\t"));
		setPaletteMD5(Utils.getFileMD5Checksum(dirpath + name() + "\\p"));



	}




	//===============================================================================================
	public Map duplicate()
	{//===============================================================================================
		Map m = new Map(name() + "Copy", this.wT(), this.hT());

		for(int l = 0; l < MapData.layers; l++)
		{
			if(MapData.isTileLayer(l))
			for(int y = 0; y < this.hT(); y++)
			{
				for(int x = 0; x < this.wT(); x++)
				{
					m.setTileIndex(l, x, y, layerTileIndex[l][x][y]);
				}
			}
		}

		for(int n=0;n<getNumStates();n++)
		{
			MapState copy = getState(n).duplicate(m);
			//set it to the original name, not "stateCopy0"
			copy.setName(getState(n).name());
			m.addState(copy);
		}


		//this will add the "MapName.LoadDefaultState: loadMapState(STATE.id)" but with the duplicated default state ID that we just added
		m.addDefaultLoadMapStateEvent();

		for(int n=0;n<getNumEvents();n++)
		{
			Event e = getEvent(n);

			//dont copy default name.LoadDefaultState: loadMapState(STATE.id) event
			//a new one gets made when we create a map object.
			if(e.name().contains(DEFAULT_LOAD_EVENT_NAME)==false)
			{
				Event copy = e.duplicate();
				copy.setName(e.name());

				m.addEvent(copy);
			}
		}



		for(int n=0;n<getNumDoors();n++)
		{
			Door copy = getDoor(n).duplicate(m);
			copy.setDestinationTYPEIDString(copy.getTYPEIDString());
			copy.connectionTYPEIDList().clear();
			m.addDoor(copy);
			//TODO: fill the connectionList with the duplicates!
		}


		//fix all the event names, the name is "MapName.Event.whatever" and should be "MapNameCOPY.Event.whatever" now.
		m.renameAllEventsToName();


		m.setMapNote(new String(""+this.mapNote()));
		m.setIsOutside(this.isOutside());
		m.setMaxRandoms(this.maxRandoms());





		return m;
	}


	//===============================================================================================
	public boolean isTileUsed(int t)
	{//===============================================================================================
		for(int l = 0; l < MapData.layers; l++)
		{
			if(MapData.isTileLayer(l))
			if(l != MapData.MAP_HIT_LAYER)
			{
				for(int y = 0; y < this.hT(); y++)
				{
					for(int x = 0; x < this.wT(); x++)
					{
						if(layerTileIndex[l][x][y] == t)
						{
							return true;
						}
					}
				}
			}
		}

		return false;
	}


	//===============================================================================================
	public void setTileIndex(int layer, int x, int y, int tileIndex)
	{//===============================================================================================
		if(MapData.isTileLayer(layer)==false)return;
		layerTileIndex[layer][x][y] = tileIndex;
	}

	//===============================================================================================
	public int getTileIndex(int layer, int x, int y)
	{//===============================================================================================
		if(MapData.isTileLayer(layer)==false)return 0;
		return layerTileIndex[layer][x][y];
	}

	//===============================================================================================
	public void destroyLayerImages()			// Must be called when map is not visible anymore
	{//===============================================================================================

		if(layerImagesAllocated)
		{

			for(int l=0;l<MapData.layers;l++)
			{
				if(layerImage[l]!=null)layerImage[l].flush();
				layerImage[l] = null;
			}

			layerImage = null;		// Get Images garbage collected to save memory

			layerImagesAllocated = false;

			//try{wait(1000);}catch(InterruptedException ie){}
			System.gc();
		}

	}

	//===============================================================================================
	public void updateAllLayerBufferImages()	// This function will draw the whole map.  It will take a while and should only be used loading a map.
	{//===============================================================================================
		if(EditorMain.mapCanvas.useLayerImageBuffer)
		{
			if(!layerImagesAllocated)
			{
				layerImage = new BufferedImage[MapData.layers];
				layerImagesAllocated = true;
			}

			for(int l=0;l<MapData.layers;l++)
			{
				updateLayerBufferImage(l);
			}


		}
		else
		{
			destroyLayerImages();
		}
	}

	//===============================================================================================
	public void updateLayerBufferImage(int l)
	{//===============================================================================================

		if(layerImage[l]!=null)
		{
			layerImage[l].flush();
			layerImage[l] = null;
			System.gc();
		}

		layerImage[l]=createTempLayerImage(l);
	}


	//===============================================================================================
	public void drawTileIntoImage(BufferedImage image, int l, int tx, int ty)
	{//===============================================================================================

		Graphics G = image.getGraphics();

		int xx = tx * 8;
		int yy = ty * 8;

		if(getTileIndex(l, tx, ty)==0)return;

		if(l == MapData.MAP_HIT_LAYER)
		{
			G.drawImage((Image) Project.tileset.hitTile, xx, yy, this);
		}
		else
		if(l == MapData.MAP_LIGHT_MASK_LAYER)
		{
			G.drawImage((Image) Project.tileset.getTileImageLightMask(getTileIndex(l, tx, ty)), xx, yy, this);
		}
		else
		/*if(E.mapCanvas.isShadowLayer(l))
		{
			G.drawImage((Image) E.project.tileset.getTileImageTranslucent(getTileIndex(l, tx, ty)), xx, yy, this);
		}
		else*/
		if(MapData.isTransparentLayer(l))
		{
			G.drawImage((Image) Project.tileset.getTileImageTranslucent(getTileIndex(l, tx, ty)), xx, yy, this);
		}
		else
		{
			G.drawImage((Image) Project.tileset.getTileImage(getTileIndex(l, tx, ty)), xx, yy, this);
		}

		G.dispose();

	}
	//===============================================================================================
	public int[][] getCombinedTileDataForAllNonShadowTileLayers(int tx, int ty)
	{//===============================================================================================
		//build a tile from all the non-shadow tile layers
		int tile[][] = new int[8][8];

		//TODO: could fill the tile with black here if i want lights to not ever get blended with bg color (blue)



		for(int tl=0;tl<MapData.layers;tl++)
		{
			if(!MapData.isTileLayer(tl))continue;
			if(!EditorMain.mapCanvas.lightBlendWithShadow&&tl==MapData.MAP_GROUND_SHADOW_LAYER)continue;
			if(tl==MapData.MAP_HIT_LAYER)continue;
			if(tl==MapData.MAP_CAMERA_BOUNDS_LAYER)continue;
			if(tl==MapData.MAP_AREA_LAYER)continue;
			if(tl==MapData.MAP_LIGHT_LAYER)continue;
			if(tl==MapData.MAP_LIGHT_MASK_LAYER)continue;
			if(!EditorMain.mapCanvas.lightBlendWithShadow&&tl==MapData.MAP_OBJECT_SHADOW_LAYER)continue;
			if(tl==MapData.MAP_SHADER_LAYER)continue;
			if(!EditorMain.mapCanvas.lightBlendWithShadow&&tl==MapData.MAP_SPRITE_SHADOW_LAYER)continue;
			if(tl==MapData.MAP_ENTITY_LAYER)continue;
			if(tl==MapData.MAP_DOOR_LAYER)continue;




			if(tl==MapData.MAP_SPRITE_SHADOW_LAYER||tl==MapData.MAP_OBJECT_SHADOW_LAYER||tl==MapData.MAP_GROUND_SHADOW_LAYER)
			{
				int tileIndex = getTileIndex(tl,tx,ty);

				if(tileIndex!=0)
				for(int xx=0;xx<8;xx++)
				for(int yy=0;yy<8;yy++)
				{
					int p = Project.tileset.tilePaletteIndex[tileIndex][xx][yy];
					if(p!=0)
					{
						Color c = Project.getSelectedPalette().getColor(tile[xx][yy]);


						float hsb[] = new float[3];
						hsb = Color.RGBtoHSB(c.getRed(), c.getGreen(), c.getBlue(), hsb);

						Color newColor = new Color(Color.HSBtoRGB(hsb[0],hsb[1],hsb[2]*0.5f));

						int newPalIndex = Project.getSelectedPalette().getColorIfExistsOrAddColor(newColor.getRed(), newColor.getGreen(), newColor.getBlue(), 0);
						tile[xx][yy]=newPalIndex;
					}
				}
			}
			else
			{
				int tileIndex = getTileIndex(tl,tx,ty);

				if(tileIndex!=0)
				for(int xx=0;xx<8;xx++)
				for(int yy=0;yy<8;yy++)
				{
					int p = Project.tileset.tilePaletteIndex[tileIndex][xx][yy];
					if(p!=0)tile[xx][yy]=p;
				}
			}


			//TODO: could mask out all the colors here if i wanted to produce a light mask overlay for the client

		}

		return tile;
	}

	//===============================================================================================
	public BufferedImage createTempLayerImage(int l)
	{//===============================================================================================

		BufferedImage layer = new BufferedImage(wT() * 8, hT() * 8, BufferedImage.TYPE_INT_ARGB);

		/*if(E.mapCanvas.isTransparentLayer(l))
		{
			layer = new BufferedImage(width * 8, height * 8, BufferedImage.TYPE_INT_ARGB);
		}
		else
		{
			layer = new BufferedImage(width * 8, height * 8, BufferedImage.TYPE_INT_ARGB);
		}*/

		Graphics G = layer.getGraphics();


		if(MapData.isTileLayer(l))
		{
			for(int my = 0; my < hT(); my++)
			{
				for(int mx = 0; mx < wT(); mx++)
				{
					drawTileIntoImage(layer,l,mx,my);
				}
			}
		}
		else
		{

			if(l==MapData.MAP_DOOR_LAYER)
			{
				drawDoorLayer(G);
			}

			if(l==MapData.MAP_ENTITY_LAYER)
			{
				drawSpriteLayer(G, false);
			}

			if(l==MapData.MAP_ENTITY_LAYER_ABOVE)
			{
				drawSpriteLayer(G, true);
			}

			if(l==MapData.MAP_LIGHT_LAYER)
			{
				drawLightsLayer(layer);
			}
		}

		G.dispose();
		return layer;
	}

	//===============================================================================================
	public void repaintTileXYInLayerImage(int l, int mx, int my)
	{//===============================================================================================
		if(EditorMain.mapCanvas.useLayerImageBuffer)
		if(layerImagesAllocated)
		{
			if(MapData.isTileLayer(l)==false)return;

			//clear tile in layer image before drawing it, otherwise drawing transparent on transparent just makes it darker
			for(int yy = 0; yy < 8; yy++)
			{
				for(int xx = 0; xx < 8; xx++)
				{
					layerImage[l].setRGB(mx * 8 + xx, my * 8 + yy, CLEAR.getRGB());
				}
			}


			drawTileIntoImage(layerImage[l],l,mx,my);
		}
	}


	//===============================================================================================
	public Sprite getSpriteByName(String name)
	{//===============================================================================================
		return Project.getSpriteByName(name);
	}

	//===============================================================================================
	public int getSpriteIndexByName(String name)
	{//===============================================================================================
		for(int q = 0; q < Project.getNumSprites(); q++)
		{
			if(name.equals(Project.getSprite(q).name()))
			{
				return q;
			}
		}
		return -1;
	}

	//===============================================================================================
	public Sprite getSpriteByEntityIndex(int n)
	{//===============================================================================================

		Sprite s = getEntity(n).getSprite();//getSpriteByName(getEntity(n).spriteName);

		if(s==null)
		{
			System.err.println("ERROR: Entity Index "+n+" has a null sprite attached!");

			//getEntity(n).spriteName = Project.getSprite(0).name;
			//s = getSpriteByName(getEntity(n).spriteName);
		}


		return s;
	}

	//===============================================================================================
	public void createEntity(String name, int x, int y)
	{//===============================================================================================
		int n = getSpriteIndexByName(name);

		createEntity(n,x,y);
	}

	//===============================================================================================
	public void createEntity(int n, int x, int y)
	{//===============================================================================================

		//go through all other mapsprites in this map. if mapspritename exists, append number.

		Entity e = new Entity(this,getSelectedState());

		e.setNameNoRename(createUniqueEntityName(Project.getSprite(n).name(), -1));

		e.setXPixels(x);
		e.setYPixels(y);

		e.setSprite(Project.getSprite(n));

		if(e.getSprite().isNPC()==true)e.setScale(1.25f);


		e.frameTimer = new Timer(100,EditorMain.mapCanvas);
		e.startAnimationTimer = new Timer(100,EditorMain.mapCanvas);

		addEntity(e);

		setSelectedEntityIndex(getNumEntities()-1);

	}


	//===============================================================================================
	public void drawSpriteLayer(Graphics G, boolean aboveTopLayer)
	{//===============================================================================================

		ArrayList<Entity> spritesThisLayer = new ArrayList<Entity>();
		ArrayList<Entity> zList = new ArrayList<Entity>();

		for(int i = 0; i<getNumEntities();i++)
		{
			Entity e = getEntity(i);

			if(aboveTopLayer==true && e.renderOrder()==RenderOrder.GROUND)continue;

			spritesThisLayer.add(getEntity(i));

		}

		//now sort them into zList by top Y (from the bottom of the hitbox)
		while(spritesThisLayer.size()>0)
		{
			int topIndex = 0;
			int topY = hT()*8;
			for(int i=0;i<spritesThisLayer.size();i++)
			{

				Entity s = spritesThisLayer.get(i);
				int thisY = (int) (s.yP()+((s.hP())-(s.getSprite().getAnimationStartFrameForFrame(s.initialFrame()).hitBoxFromBottomPixels1X)));

				if(thisY<=topY)
				{
					topY = thisY;
					topIndex = i;
				}
			}

			zList.add(spritesThisLayer.get(topIndex));
			spritesThisLayer.remove(topIndex);
		}

		//now draw zList
		for(int i=0;i<zList.size();i++)
		{
			G.drawImage(zList.get(i).getImage(), zList.get(i).xP(), zList.get(i).yP(), (int) (zList.get(i).wP()), (int) (zList.get(i).hP()), this);
		}

	}

	//===============================================================================================
	public void drawSpriteLayerAtTileXY(Graphics G, int mapX, int mapY, boolean aboveTopLayer)
	{//===============================================================================================


		ArrayList<Entity> spritesThisLayer = new ArrayList<Entity>();
		ArrayList<Entity> zList = new ArrayList<Entity>();


		for(int i = 0; i<getNumEntities();i++)
		{
			Entity e = getEntity(i);

			if(aboveTopLayer==true && e.renderOrder()==RenderOrder.GROUND)continue;

			int x=e.xP();
			int y=e.yP();
			int w=(int)(e.wP());
			int h=(int)(e.hP());

			if(x>(mapX)+8||y>(mapY)+8||x+w<(mapX)||y+h<(mapY))continue;



			spritesThisLayer.add(getEntity(i));

		}

		//now sort them into zList by top Y (from the bottom of the hitbox)
		while(spritesThisLayer.size()>0)
		{
			int topIndex = 0;
			int topY = hT()*8;
			for(int i=0;i<spritesThisLayer.size();i++)
			{
				Entity s = spritesThisLayer.get(i);
				int thisY = (int) (s.yP()+((s.hP())-(s.getSprite().getAnimationStartFrameForFrame(s.initialFrame()).hitBoxFromBottomPixels1X)));

				if(thisY<=topY)
				{
					topY = thisY;
					topIndex = i;
				}
			}

			zList.add(spritesThisLayer.get(topIndex));
			spritesThisLayer.remove(topIndex);
		}

		//now draw zList
		for(int i=0;i<zList.size();i++)
		{
			Entity s = zList.get(i);

			int x=s.xP();
			int y=s.yP();

			//find clip of sprite image we need to draw
			int clipX = (int)((mapX-x)/s.scale());
			int clipY = (int)((mapY-y)/s.scale());

			G.drawImage(s.getImage(),mapX, mapY, mapX+8, mapY+8, clipX, clipY, (int)(clipX+(8.0f/s.scale())), (int)(clipY+(8.0f/s.scale())), this);

		}
	}


	//===============================================================================================
	public void drawSpriteConnections(Graphics G, Entity s)
	{	//===============================================================================================


		float zoom =  ((float)MapCanvas.zoom/8.0f);



		int ax = (int)(((float)(s.xP() + s.wP()/2))*zoom);
		int ay = (int)(((float)(s.yP() + s.hP()))*zoom);

		//draw lines to connections


		//for all connections from this sprite
		for(int c=0; c<s.connectionTYPEIDList().size(); c++)
		{

			//if starts with Door. find door with name
			if(s.connectionTYPEIDList().get(c).startsWith("DOOR"))
			{
				for(int i=0;i<getNumDoors();i++)
				{
					Door toDoor = getDoor(i);
					if(s.connectionTYPEIDList().get(c).equals(toDoor.getTYPEIDString()))
					{
						G.setColor(Color.GREEN);

						int bottomOffset = toDoor.getSprite().getAnimationStartFrameForFrame(s.initialFrame()).hitBoxFromBottomPixels1X;

						int endDoorX = (int)((toDoor.xP() + (toDoor.wP()/2))*zoom);
						int endDoorY = (int)((toDoor.yP() + (toDoor.hP()-bottomOffset))*zoom);

						drawArrowLine(G,ax, ay, endDoorX, endDoorY);
					}
				}
			}
			else
			if(s.connectionTYPEIDList().get(c).startsWith("AREA"))
			{
				//if doesnt start with door, it's an action
				//go through actions and find name

				for(int i=0;i<getNumAreas();i++)
				{
					Area toArea = getArea(i);
					if(s.connectionTYPEIDList().get(c).equals(toArea.getTYPEIDString()))
					{
						G.setColor(Color.GREEN);

						int actionx = (int)((toArea.xP() + (toArea.wP()/2))*zoom);
						int actiony = (int)((toArea.yP() + (toArea.hP()/2))*zoom);

						drawArrowLine(G,ax, ay, actionx, actiony);

					}
				}
			}
		}


	}


	//===============================================================================================
	public void drawSpriteHitBox(Graphics G, Entity s)
	{//===============================================================================================

		float zoom =  ((float)MapCanvas.zoom/8.0f);

		int x = (int)(((float)s.xP())*zoom);
		int y = (int)(((float)s.yP())*zoom);
		int w = (int)((float)(s.wP()*zoom)-1);
		int h = (int)((float)(s.hP()*zoom)-1);


		int leftOffset = (int)(((float)s.getSprite().getAnimationStartFrameForFrame(s.initialFrame()).hitBoxFromLeftPixels1X * zoom));
		int rightOffset = (int)(((float)s.getSprite().getAnimationStartFrameForFrame(s.initialFrame()).hitBoxFromRightPixels1X * zoom));
		int topOffset = (int)(((float)s.getSprite().getAnimationStartFrameForFrame(s.initialFrame()).hitBoxFromTopPixels1X * zoom));
		int bottomOffset =(int)(((float) s.getSprite().getAnimationStartFrameForFrame(s.initialFrame()).hitBoxFromBottomPixels1X * zoom));

		//draw hitbox
		G.setColor(Color.RED);
		G.drawRect(x+leftOffset,y+topOffset,(w-(leftOffset))-rightOffset,h-(topOffset+bottomOffset));
		G.drawLine(x+leftOffset,y+topOffset,(x+leftOffset)+((w-(leftOffset))-rightOffset)-1,(y+topOffset)+(h-(topOffset+bottomOffset))-1);

		G.setColor(new Color(255,0,0,150));
		G.fillRect((x+leftOffset)+1,(y+topOffset)+1,((w-(leftOffset))-rightOffset)-1,(h-(topOffset+bottomOffset))-1);

	}


	//===============================================================================================
	public void drawSpriteInfo(Graphics G, Entity s)
	{//===============================================================================================

		float zoom =  ((float)MapCanvas.zoom/8.0f);

		int x = (int)(((float)s.xP())*zoom);
		int y = (int)(((float)s.yP())*zoom);

		G.setFont(new Font("Arial", Font.PLAIN, 10));

		drawOutlinedString(G,s.name(), x, y-18,Color.YELLOW);
		drawOutlinedString(G,"Sprite: "+s.getSprite().name(), x, y-9,Color.YELLOW);


		int strings = -1;


		if(s.renderOrder()!=RenderOrder.GROUND)drawOutlinedString(G,"RenderOrder:"+s.renderOrder(), x, y+(++strings*9),Color.WHITE);
		if(s.ticksPerPixelMoved()!=12)drawOutlinedString(G,"TicksPerPixelMoved:"+s.ticksPerPixelMoved(), x, y+(++strings*9),Color.WHITE);
		if(s.aboveWhenEqual())drawOutlinedString(G,"Above When Equal", x, y+(++strings*9),Color.WHITE);
		if(s.alwaysOnBottom())drawOutlinedString(G,"Always On Bottom", x, y+(++strings*9),Color.WHITE);
		if(s.disableShadow())drawOutlinedString(G,"Disable Shadow", x, y+(++strings*9),Color.WHITE);
		if(s.nonWalkable())drawOutlinedString(G,"NonWalkable", x, y+(++strings*9),Color.WHITE);
		if(s.pushable())drawOutlinedString(G,"Pushable", x, y+(++strings*9),Color.WHITE);
		if(s.randomFrames())drawOutlinedString(G,"Animate Randomly Through Frames", x, y+(++strings*9),Color.WHITE);
		if(s.toAlpha()<1.0f)drawOutlinedString(G,"Alpha: "+s.toAlpha(), x, y+(++strings*9),Color.WHITE);


		if(s.eventData()!=null)
		{
			if(Project.getEventByID(s.eventData().id()).getFirstDialogueCaption().length()>0)
			drawOutlinedString(G,"Has Event: "+Project.getEventByID(s.eventData().id()).getFirstDialogueCaption(), x, y+(++strings*9),Color.RED);
			else
			drawOutlinedString(G,"Has Event: "+Project.getEventByID(s.eventData().id()).getFirst20Chars(), x, y+(++strings*9),Color.RED);
		}




	}

	//===============================================================================================
	public void drawSpriteLayerSelection(Graphics G)
	{//===============================================================================================

		float zoom =  ((float)MapCanvas.zoom/8.0f);


		//draw rectangle around all sprites

		for(int n=0;n<getNumEntities();n++)
		{
			Entity e = getEntity(n);

			int x = (int)(((float)e.xP())*zoom);
			int y = (int)(((float)e.yP())*zoom);
			int w = (int)((float)(e.wP()*zoom)-1);
			int h = (int)((float)(e.hP()*zoom)-1);

			G.setColor(Color.BLACK);
			G.drawRect(x+1,y+1,w-2,h-2);
			G.drawRect(x-1,y-1,w+2,h+2);
			G.setColor(Color.YELLOW);
			G.drawRect(x,y,w,h);


			drawSpriteConnections(G,e);

			if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_HIT_LAYER].isSelected())
			drawSpriteHitBox(G,e);

			if(MapCanvas.alwaysShowAreaAndSpriteInfo==true)// || MapCanvas.selectedAllLayers)
			drawSpriteInfo(G,e);
		}



		//draw bounds box over selected mapsprite
		if(getSelectedEntityIndex()<getNumEntities()&&getSelectedEntityIndex()!=-1)
		{
			Entity e = getSelectedEntity();

			int x = (int)(((float)e.xP())*zoom);
			int y = (int)(((float)e.yP())*zoom);
			int w = (int)(((float)(e.wP()))*zoom)-1;
			int h = (int)(((float)(e.hP()))*zoom)-1;

			G.setColor(Color.BLACK);
			G.drawRect(x+2,y+2,w-4,h-4);
			G.drawRect(x-1,y-1,w+2,h+2);
			G.setColor(Color.GREEN);
			G.drawRect(x,y,w,h);
			G.drawRect(x+1,y+1,w-2,h-2);

			drawSpriteConnections(G,e);
			drawSpriteHitBox(G,e);
			drawSpriteInfo(G,e);

		}

	}


	//===============================================================================================
	public String createUniqueLightName(String name, int ignoreThisLight)
	{//===============================================================================================

		String uniqueName = ""+name;

		String ignoreName = "";
		if(ignoreThisLight!=-1)ignoreName = ""+getSelectedState().getLight(ignoreThisLight).name();

		boolean unique = false;
		int number = 0;
		while(unique==false)
		{
			boolean uniqueThisTime = true;

			for(int k=0;k<getNumStates();k++)
			for(int i=0;i<getState(k).getNumLights();i++)
			{
				if(uniqueName.equals(ignoreName)==false&&uniqueName.equals(getState(k).getLight(i).name()))
				{
					uniqueThisTime = false;

					String tempName = ""+getState(k).getLight(i).name();
					tempName = tempName.split("[0-9]")[0];

					uniqueName = tempName.concat(""+number);
					number++;
				}
			}
			if(uniqueThisTime==true)unique=true;
		}

		return uniqueName;
	}



	//===============================================================================================
	public String createUniqueEntityName(String name, int ignoreThisSprite)
	{//===============================================================================================

		String uniqueName = ""+name;

		String ignoreName = "";
		if(ignoreThisSprite!=-1)ignoreName = ""+getSelectedState().getEntity(ignoreThisSprite).name();


		boolean unique = false;
		int number = 0;
		while(unique==false)
		{
			boolean uniqueThisTime = true;

			for(int k=0;k<getNumStates();k++)
			for(int i=0;i<getState(k).getNumEntities();i++)
			{
				if(uniqueName.equals(ignoreName)==false&&uniqueName.equals(getState(k).getEntity(i).name()))
				{
					uniqueThisTime = false;

					String tempName = ""+getState(k).getEntity(i).name();
					tempName = tempName.split("[0-9]")[0];

					uniqueName = tempName.concat(""+number);
					number++;
				}
			}
			if(uniqueThisTime==true)unique=true;
		}

		return uniqueName;
	}


	//===============================================================================================
	public String createUniqueDoorName(String name, int ignoreThisDoor)
	{//===============================================================================================

		String uniqueName = ""+name;

		String ignoreName = "";
		if(ignoreThisDoor!=-1)ignoreName = ""+getDoor(ignoreThisDoor).name();


		boolean unique = false;
		int number = 0;
		while(unique==false)
		{
			boolean uniqueThisTime = true;


			for(int i=0;i<getNumDoors();i++)
			{
				if(uniqueName.equals(ignoreName)==false&&uniqueName.equals(getDoor(i).name()))
				{
					uniqueThisTime = false;

					String tempName = ""+getDoor(i).name();
					tempName = tempName.split("[0-9]")[0];

					uniqueName = tempName.concat(""+number);
					number++;
				}
			}
			if(uniqueThisTime==true)unique=true;
		}

		return uniqueName;
	}

	//===============================================================================================
	public String createUniqueAreaName(String name, int ignoreThisAction)
	{//===============================================================================================

		String uniqueName = ""+name;

		String ignoreName = "";
		if(ignoreThisAction!=-1)ignoreName = ""+getSelectedState().getArea(ignoreThisAction).name();

		boolean unique = false;
		int number = 0;
		while(unique==false)
		{
			boolean uniqueThisTime = true;

			for(int k=0;k<getNumStates();k++)
			for(int i=0;i<getState(k).getNumAreas();i++)
			{
				if(uniqueName.equals(ignoreName)==false&&uniqueName.equals(getState(k).getArea(i).name()))
				{
					uniqueThisTime = false;

					String tempName = ""+getState(k).getArea(i).name();
					tempName = tempName.split("[0-9]")[0];

					uniqueName = tempName.concat(""+number);
					number++;
				}
			}
			if(uniqueThisTime==true)unique=true;
		}

		return uniqueName;
	}



	//===============================================================================================
	public void drawLightsLayerWithNoBlending(BufferedImage layer)
	{//===============================================================================================

		//this should be much faster than processing each tile, but it doesn't allow for blending the lights together.
		//i can process each tile afterwards but then i can't have a unique blendfalloff for each light

		Graphics G = layer.getGraphics();

		for(int i = 0; i<getNumLights();i++)
		{

			if(getLight(i).bufferedImage==null)//draw new image
			{
				getLight(i).createLightImage();
			}

			G.drawImage(getLight(i).bufferedImage,getLight(i).xP()-(getLight(i).radiusPixels1X()),getLight(i).yP()-(getLight(i).radiusPixels1X()),this);
		}
		/*
		//now go through image tile by tile and remove all areas masked by light_mask_layer
		for(int tx=0;tx<width();tx++)
		{
			for(int ty=0;ty<height();ty++)
			{
				//if there is a tile on the light mask layer, set this whole tile to clear
				if(getTileIndex(MapData.LIGHTS_MASK_LAYER, tx, ty)!=0)
				{
					for(int xx=0;xx<8;xx++)
					for(int yy=0;yy<8;yy++)
					layer.setRGB((tx*8)+xx,(ty*8)+yy,CLEAR.getRGB());
				}
				else
				{

					//create a new tiledata with all non-shadow layers combined
					int[][] tile=null;
					if(E.mapCanvas.lightBlackMasking||E.mapCanvas.lightScreenBlending)tile = getCombinedTileDataForAllNonShadowTileLayers(tx,ty);

					if(E.mapCanvas.lightBlackMasking)
					{
						//mask out any black pixels in our combined tile in our light image
						for(int xx=0;xx<8;xx++)
						for(int yy=0;yy<8;yy++)
						{
							if(tile[xx][yy]==1)
							layer.setRGB((tx*8)+xx,(ty*8)+yy,CLEAR.getRGB());
						}
					}

					if(E.mapCanvas.lightScreenBlending)
					{
						//make an image of the tile
						BufferedImage tileImage = new BufferedImage(8,8,BufferedImage.TYPE_INT_ARGB);
						BufferedImage tileImageWithLightApplied = new BufferedImage(8,8,BufferedImage.TYPE_INT_ARGB);
						for(int xx=0;xx<8;xx++)
						for(int yy=0;yy<8;yy++)
						{
							int tiler = E.project.getSelectedPalette().data[tile[xx][yy]][0];
							int tileg = E.project.getSelectedPalette().data[tile[xx][yy]][1];
							int tileb = E.project.getSelectedPalette().data[tile[xx][yy]][2];

							tileImage.setRGB(xx, yy, new Color(tiler,tileg,tileb).getRGB());
							tileImageWithLightApplied.setRGB(xx, yy, new Color(tiler,tileg,tileb).getRGB());
						}

						//draw the light image onto the tile
						Graphics tileImageWithLightAppliedGraphics = tileImageWithLightApplied.getGraphics();
						tileImageWithLightAppliedGraphics.drawImage(layer, 0, 0, 8, 8, tx*8, ty*8, tx*8+8, ty*8+8, this);

						//blend the resulting tile with the original tile
						for(int xx=0;xx<8;xx++)
						for(int yy=0;yy<8;yy++)
						{

								Color tileColor = new Color(tileImage.getRGB(xx, yy));
								int tiler = tileColor.getRed();
								int tileg = tileColor.getGreen();
								int tileb = tileColor.getBlue();

								Color lightTileColor = new Color(tileImageWithLightApplied.getRGB(xx, yy));
								int lightr = lightTileColor.getRed();
								int lightg = lightTileColor.getGreen();
								int lightb = lightTileColor.getBlue();

								//screen blend
								int newr = (lightr+tiler)-((lightr*tiler)/255);
								int newg = (lightg+tileg)-((lightg*tileg)/255);
								int newb = (lightb+tileb)-((lightb*tileb)/255);


								tileImage.setRGB(xx,yy,new Color(newr,newg,newb).getRGB());
						}

						//draw this result on the light layer at alpha (alpha * 2 works better, gives a fade effect)
						for(int xx=0;xx<8;xx++)
						for(int yy=0;yy<8;yy++)
						{
							if(layer.getRGB((tx*8)+xx,(ty*8)+yy)!=0)
							{
								int a = new Color(layer.getRGB((tx*8)+xx,(ty*8)+yy),true).getAlpha();
								a*=2;
								if(a>255)a=255;
								Color tileColor = new Color(tileImage.getRGB(xx, yy));
								Color tileColorWithAlpha = new Color(tileColor.getRed(),tileColor.getGreen(),tileColor.getBlue(),a);
								layer.setRGB((tx*8)+xx,(ty*8)+yy,tileColorWithAlpha.getRGB());
							}
						}
					}

				}
			}
		}*/


	}
	//===============================================================================================
	public void drawLightsLayer(BufferedImage layer)
	{//===============================================================================================

		Graphics G = layer.getGraphics();

		Light lights[] = new Light[getNumLights()];
		for(int i = 0; i<getNumLights();i++)lights[i] = getLight(i);

		Entity entities[] = new Entity[getNumEntities()];
		for(int i = 0; i<getNumEntities();i++)entities[i] = getEntity(i);

		for(int tx=0;tx<wT();tx++)
		{
			for(int ty=0;ty<hT();ty++)
			{
				drawLightsLayerAtTileXY(G,tx,ty, lights, entities);
			}
		}
	}

	//===============================================================================================
	public void drawLightsLayerAtTileXY(Graphics G, int tileX, int tileY, Light[] lights, Entity[] entities)
	{//===============================================================================================

		int mapX = tileX*8;
		int mapY = tileY*8;

		boolean tileUsed=false;

		if(lights==null)
		{
			lights = new Light[getNumLights()];
			for(int i = 0; i<getNumLights();i++)lights[i] = getLight(i);
		}

		if(entities==null)
		{
			entities = new Entity[getNumEntities()];
			for(int i = 0; i<getNumEntities();i++)entities[i] = getEntity(i);
		}

		int numLights = getNumLights();

		for(int i = 0; i<numLights;i++)
		{


			int lightX=lights[i].xP()-lights[i].radiusPixels1X();
			int lightY=lights[i].yP()-lights[i].radiusPixels1X();
			int lightW=lights[i].wP()+lights[i].radiusPixels1X()*2;
			int lightH=lights[i].hP()+lights[i].radiusPixels1X()*2;

			//if the light isn't in this tile, go to the next light.
			if(lightX>(mapX)+8||lightY>(mapY)+8||lightX+lightW<(mapX)||lightY+lightH<(mapY))continue;


			//skip lights that aren't on at night if its night time
			if(lights[i].isNightLight()==false&&MapCanvas.nightTimePreview==true)continue;

			//if any lights use this tile, we want to change it
			tileUsed=true;
		}




		if(tileUsed==true)
		{

			//create a new tiledata with all non-shadow layers combined
			int[][] combinedTileData=null;
			if(EditorMain.mapCanvas.lightBlackMasking||EditorMain.mapCanvas.lightScreenBlending)
			{
				combinedTileData = getCombinedTileDataForAllNonShadowTileLayers(tileX,tileY);
			}


			//we want to draw each light into one tile and then draw that to the screen with blending

			//make new tile image
			BufferedImage lightTileImage = new BufferedImage(8,8,BufferedImage.TYPE_INT_ARGB);
			Graphics LTG = lightTileImage.getGraphics();

			float maxBlendFalloff=0;

			for(int i = 0; i<numLights;i++)
			{

				int lightX=lights[i].xP()-lights[i].radiusPixels1X();
				int lightY=lights[i].yP()-lights[i].radiusPixels1X();
				int lightW=lights[i].wP()+lights[i].radiusPixels1X()*2;
				int lightH=lights[i].hP()+lights[i].radiusPixels1X()*2;

				//if the light isn't in this tile, go to the next light.
				if(lightX>(mapX)+8||lightY>(mapY)+8||lightX+lightW<(mapX)||lightY+lightH<(mapY))continue;

				//skip lights that aren't on at night if its night time
				if(lights[i].isNightLight()==false&&MapCanvas.nightTimePreview==true)continue;


				if(lights[i].bufferedImage==null)
				{
					lights[i].createLightImage();
				}

				//find 8x8 clip of the light image we need to draw
				int clipX = mapX-lightX;
				int clipY = mapY-lightY;

				//draw the light image into the new tile image
				LTG.drawImage(lights[i].bufferedImage,0,0,8,8, clipX, clipY, clipX+8, clipY+8, this);

				if(lights[i].blendFalloff()>maxBlendFalloff)maxBlendFalloff=lights[i].blendFalloff();

			}

			//now lightTileImage contains each light blended onto it
			if(EditorMain.mapCanvas.lightScreenBlending)
			{

				TilesetPalette p = Project.getSelectedPalette();
				//make an image of the tile
				BufferedImage tileImage = new BufferedImage(8,8,BufferedImage.TYPE_INT_ARGB);
				BufferedImage tileImageWithLightApplied = new BufferedImage(8,8,BufferedImage.TYPE_INT_ARGB);
				for(int xx=0;xx<8;xx++)
				for(int yy=0;yy<8;yy++)
				{
					int tiler = p.data[combinedTileData[xx][yy]][0];
					int tileg = p.data[combinedTileData[xx][yy]][1];
					int tileb = p.data[combinedTileData[xx][yy]][2];

					tileImage.setRGB(xx, yy, new Color(tiler,tileg,tileb).getRGB());
					tileImageWithLightApplied.setRGB(xx, yy, new Color(tiler,tileg,tileb).getRGB());
				}

				Graphics TIG = tileImage.getGraphics();
				Graphics TIWLAG = tileImageWithLightApplied.getGraphics();
				//now draw sprites and doors into tileImage and tileImageWithLightApplied

				//TODO: this doesn't take into account sprite layer order
				//also, z-ordering should go here.

					int numEntities = getNumEntities();
					for(int i = 0; i<numEntities;i++)
					{

						Entity e = entities[i];

						int x=e.xP();
						int y=e.yP();
						int w=e.wP();
						int h=e.hP();


						if(x>(mapX)+8||y>(mapY)+8||x+w<(mapX)||y+h<(mapY))continue;



						//find clip of sprite image we need to draw
						int clipX = (int)((mapX-x)/e.scale());
						int clipY = (int)((mapY-y)/e.scale());

						TIG.drawImage(e.getImage(),0, 0, 0+8, 0+8, clipX, clipY, (int)(clipX+(8/e.scale())), (int)(clipY+(8/e.scale())), this);
						TIWLAG.drawImage(e.getImage(),0, 0, 0+8, 0+8, clipX, clipY, (int)(clipX+(8/e.scale())), (int)(clipY+(8/e.scale())), this);

					}

					//go through all doors and see if any are on this tile
					//if they are, take the pixels from the bufferedImage that are over this tile and draw them over

					int numDoors = getNumDoors();
					for(int i = 0; i<numDoors;i++)
					{
						Door d = getDoor(i);

						int x=d.xP();
						int y=d.yP();
						int w=d.wP();
						int h=d.hP();

						if(x>(mapX)+8||y>(mapY)+8||x+w<(mapX)||y+h<(mapY))continue;


						//find clip of sprite image we need to draw
						int clipX = mapX-x;
						int clipY = mapY-y;

						TIG.drawImage(d.getImage(),0, 0, 0+8, 0+8, clipX, clipY, clipX+8, clipY+8, this);
						TIWLAG.drawImage(d.getImage(),0, 0, 0+8, 0+8, clipX, clipY, clipX+8, clipY+8, this);

					}


				//draw the light image onto the tile
				TIWLAG.drawImage(lightTileImage, 0, 0, 8, 8, 0, 0, 8, 8, this);

				//blend the resulting tile with the original tile
				for(int xx=0;xx<8;xx++)
				for(int yy=0;yy<8;yy++)
				{

					Color tileColor = new Color(tileImage.getRGB(xx, yy));
					int tiler = tileColor.getRed();
					int tileg = tileColor.getGreen();
					int tileb = tileColor.getBlue();

					Color lightTileColor = new Color(tileImageWithLightApplied.getRGB(xx, yy));
					int lightr = lightTileColor.getRed();
					int lightg = lightTileColor.getGreen();
					int lightb = lightTileColor.getBlue();

					//screen blend
					int newr = (lightr+tiler)-((lightr*tiler)/255);
					int newg = (lightg+tileg)-((lightg*tileg)/255);
					int newb = (lightb+tileb)-((lightb*tileb)/255);

					tileImage.setRGB(xx,yy,new Color(newr,newg,newb).getRGB());
				}

				//draw this result on the light layer at alpha (alpha * 2 works better, gives a fade effect)
				for(int xx=0;xx<8;xx++)
				for(int yy=0;yy<8;yy++)
				{
					if(lightTileImage.getRGB(xx,yy)!=0)
					{
						int a = new Color(lightTileImage.getRGB(xx,yy),true).getAlpha();
						a=(int)((float)a*maxBlendFalloff);
						if(a>255)a=255;
						Color tileColor = new Color(tileImage.getRGB(xx, yy));
						Color tileColorWithAlpha = new Color(tileColor.getRed(),tileColor.getGreen(),tileColor.getBlue(),a);
						lightTileImage.setRGB(xx,yy,tileColorWithAlpha.getRGB());
					}
				}
			}

			if(EditorMain.mapCanvas.lightBlackMasking)
			{
				//mask out black pixels from our combined tile in our new tile image
				for(int xx=0;xx<8;xx++)
				for(int yy=0;yy<8;yy++)
				{
					if(combinedTileData[xx][yy]==1)
						lightTileImage.setRGB(xx,yy,CLEAR.getRGB());
				}
			}


			//check the light mask layer, only draw the light in this tile if there is nothing there
			//mask out lights mask layer as bitmap
			int lightMaskIndex = getTileIndex(MapData.MAP_LIGHT_MASK_LAYER, tileX, tileY);
			if(lightMaskIndex!=0)
			{
				for(int xx=0;xx<8;xx++)
				for(int yy=0;yy<8;yy++)
				{
					if(Project.tileset.tilePaletteIndex[lightMaskIndex][xx][yy]!=0)
						lightTileImage.setRGB(xx,yy,CLEAR.getRGB());
				}

			}

			//draw our new tile image into the map canvas
			G.drawImage(lightTileImage,mapX, mapY, mapX+8, mapY+8, 0, 0, 8, 8, this);
		}
	}

	//===============================================================================================
	public void drawOutlinedString(Graphics G, String s, int x, int y, Color color)
	{//===============================================================================================

		G.setColor(Color.BLACK);
		G.drawString(s, (x-1), y);
		G.drawString(s, (x+1), y);
		G.drawString(s, x, (y-1));
		G.drawString(s, x, (y+1));
		G.setColor(color);
		G.drawString(s, x, y);

	}



	//===============================================================================================
	public void drawAllLightRadiusBoxes(Graphics G)
	{//===============================================================================================

		float zoom =  ((float)MapCanvas.zoom/8.0f);

		//draw rectangle around all lights
		for(int n=0;n<getNumLights();n++)
		{
			int x = (int)(((float)getLight(n).xP())*zoom);
			int y = (int)(((float)getLight(n).yP())*zoom);
			int w = (int)(((float)(getLight(n).wP()))*zoom)-1;
			int h = (int)(((float)(getLight(n).hP()))*zoom)-1;

				if(getLight(n).flickers()==true)
				G.setColor(Color.PINK);
				else
				G.setColor(Color.GREEN);

				G.drawRect(x-(int)(getLight(n).radiusPixels1X()*zoom), y-(int)(getLight(n).radiusPixels1X()*zoom), w+(int)(getLight(n).radiusPixels1X()*2*zoom), h+(int)(getLight(n).radiusPixels1X()*2*zoom));
		}

	}

	//===============================================================================================
	public void drawLightsLayerSelection(Graphics G)
	{//===============================================================================================

		float zoom =  ((float)MapCanvas.zoom/8.0f);


		//draw rectangle around all lights
		for(int n=0;n<getNumLights();n++)
		{
			int x = (int)(((float)getLight(n).xP())*zoom);
			int y = (int)(((float)getLight(n).yP())*zoom);
			int w = (int)(((float)(getLight(n).wP()))*zoom)-1;
			int h = (int)(((float)(getLight(n).hP()))*zoom)-1;

				G.setColor(Color.BLACK);
				G.drawRect(x+1,y+1,w-2,h-2);
				G.drawRect(x-1,y-1,w+2,h+2);
				G.setColor(Color.YELLOW);
				G.drawRect(x,y,w,h);



				G.setFont(new Font("Arial", Font.PLAIN, 10));
				drawOutlinedString(G,getLight(n).name(), x, y-5,Color.YELLOW);


				if(getLight(n).toggleable()==true)
				{

					int ax = (int)(((float)getLight(n).toggleXPixels1X()) * zoom);
					int ay = (int)(((float)getLight(n).toggleYPixels1X()) * zoom);
					int aw = (int)(8.0f*zoom)-1;
					int ah = (int)(8.0f*zoom)-1;

					//draw purple arrival point marker
					G.setColor(new Color(200,0,255,91));
					G.fillRect(ax, ay, aw, ah);

					G.setColor(new Color(200,0,255,255));
					G.drawRect(ax, ay, aw, ah);

					//draw connecting line
					G.setColor(Color.WHITE);
					G.drawLine(x+(w/2), y+(h/2), ax+(aw/2), ay+(ah/2));
				}

		}


		//draw bounds box over selected light
		if(getSelectedLightIndex()<getNumLights()&&getSelectedLightIndex()>=0)
		{
			int x = (int)(((float)getSelectedLight().xP())*zoom);
			int y = (int)(((float)getSelectedLight().yP())*zoom);
			int w = (int)(((float)(getSelectedLight().wP()))*zoom)-1;
			int h = (int)(((float)(getSelectedLight().hP()))*zoom)-1;

				G.setColor(Color.BLACK);
				G.drawRect(x+2,y+2,w-4,h-4);
				G.drawRect(x-1,y-1,w+2,h+2);

				G.setColor(Color.GREEN);
				G.drawRect(x,y,w,h);
				G.drawRect(x+1,y+1,w-2,h-2);

				G.drawRect(x-(int)(getSelectedLight().radiusPixels1X()*zoom), y-(int)(getSelectedLight().radiusPixels1X()*zoom), w+(int)(getSelectedLight().radiusPixels1X()*2*zoom), h+(int)(getSelectedLight().radiusPixels1X()*2*zoom));


				G.setFont(new Font("Arial", Font.PLAIN, 10));
				drawOutlinedString(G,getSelectedLight().name(), x, y-5,Color.YELLOW);

		}

	}



	//===============================================================================================
	//public void deleteArea(int n)
	//{//===============================================================================================

		//go through sprites, areas, doors, remove connections
		//for(int i=0;i<getNumDoors();i++){getDoor(i).connectionList.remove(getArea(n).getName());}
		//for(int i=0;i<getNumAreas();i++){getArea(i).connectionList.remove(getArea(n).getName());}
		//for(int i=0;i<getNumEntities();i++){getEntity(i).connectionList.remove(getArea(n).getName());}

//		for(int i = n; i < getNumAreas(); i++)
//		{
//			getArea(i)=area[i+1];
//
//		}
//		area[getNumAreas()] = new Area();
//		if(getNumAreas() > 0)
//		{
//			getNumAreas()--;
//		}

		//getSelectedState().area.remove(n);

	//}

	//===============================================================================================
	public void drawAreaConnections(Graphics G, Area area)
	{//===============================================================================================



		float zoom =  ((float)MapCanvas.zoom/8.0f);

		int x = (int)(((float)area.xP())*zoom);
		int y = (int)(((float)area.yP())*zoom);
		int w = (int)(((float)(area.wP()))*zoom)-1;
		int h = (int)(((float)(area.hP()))*zoom)-1;



		int ax = x+w/2;
		int ay = y+h/2;

		//draw line from spawn point if it warp area
		//if(a.isWarpArea)ax = (int)(((float)a.arrivalX+4)*zoom);
		//if(a.isWarpArea)ay = (int)(((float)a.arrivalY+4)*zoom);


		//if this is a random spawn point
		//draw lines from here to doors and areas that are random points of interests
		if(area.connectionTYPEIDList().size()==0&&((area.randomNPCSpawnPoint()&&area.randomNPCStayHere()==false) || (area.randomPointOfInterestOrExit()&&area.waitHereTicks()!=-1)))
		{
			//for all actions
			for(int i=0;i<getNumAreas();i++)
			{
				//only draw arrows to areas for all areas if nothing is selected
				//if an area is selected, only draw arrows for that one.
				//or if this area is drawing an arrow to the selected area, draw that.
				if((MapCanvas.drawRandomPointOfInterestLines==true && getSelectedAreaIndex()==-1) || (getSelectedAreaIndex()!=-1 && getSelectedArea() == area) || i == getSelectedAreaIndex() || MapCanvas.selectedAllLayers)
				if(getArea(i)!=area && ((getArea(i).randomPointOfInterestOrExit()&&getArea(i).waitHereTicks()!=-1) || (getArea(i).randomNPCSpawnPoint()&&getArea(i).randomNPCStayHere()==false)))
				{

					if(area.randomNPCSpawnPoint() || getArea(i).randomNPCSpawnPoint())G.setColor(Color.MAGENTA);
					else G.setColor(Color.WHITE);

					int actionx = (int)((getArea(i).xP() + (getArea(i).wP()/2))*zoom);
					int actiony = (int)((getArea(i).yP() + (getArea(i).hP()/2))*zoom);

					drawArrowLine(G,ax, ay, actionx, actiony);

				}
			}

			//for all doors
			for(int i=0;i<getNumDoors();i++)
			{
				//only draw arrows to doors for all areas if nothing is selected
				//if an area is selected, draw arrows for this one
				//if this area is drawing an arrow to the selected door, draw that.
				if((MapCanvas.drawRandomPointOfInterestLines==true && getSelectedAreaIndex()==-1) || (getSelectedAreaIndex()!=-1 && getSelectedArea() == area) || MapCanvas.selectedAllLayers)
				if(getDoor(i).randomPointOfInterestOrExit()==true || (getDoor(i).randomNPCSpawnPoint()&&getDoor(i).connectionTYPEIDList().size()==0))
				{
					if(area.randomNPCSpawnPoint() || (getDoor(i).randomNPCSpawnPoint()&&getDoor(i).connectionTYPEIDList().size()==0))G.setColor(Color.MAGENTA);
					else G.setColor(Color.WHITE);

					int bottomOffset = getDoor(i).getSprite().getAnimationStartFrameForFrame(0).hitBoxFromBottomPixels1X;

					int endDoorX = (int)((getDoor(i).xP() + (getDoor(i).wP()/2))*zoom);
					int endDoorY = (int)((getDoor(i).yP() + (getDoor(i).hP()-bottomOffset))*zoom);

					if(getDoor(i).randomNPCSpawnPoint())
					{
						//draw arrow from door to area
						drawArrowLine(G,endDoorX, endDoorY,ax, ay);
						//if this area doesn't go anywhere, draw arrow back to door.
						if(area.connectionTYPEIDList().size()==0)drawArrowLine(G,ax, ay, endDoorX, endDoorY);
					}
					else drawArrowLine(G,ax, ay, endDoorX, endDoorY);

				}
			}
		}

		//if this is selected action
		//go through all doors, all connections, if connection is this action, draw line from door to action
		if(getSelectedAreaIndex()!=-1 && getSelectedArea() == area)
		{
			for(int i=0;i<getNumDoors();i++)
			{
				for(int c=0; c<getDoor(i).connectionTYPEIDList().size(); c++)
				{
					if(getDoor(i).connectionTYPEIDList().get(c).equals(getSelectedArea().getTYPEIDString()))
					{
						G.setColor(Color.GREEN);

						int doorX = (int)((getDoor(i).xP() + (getDoor(i).wP()/2))*zoom);
						int doorY = (int)((getDoor(i).yP() + (getDoor(i).hP()/2))*zoom);

						drawArrowLine(G,doorX, doorY, ax,ay);
					}
				}
			}

		}

		//for all connections from this area
		for(int c=0; c<area.connectionTYPEIDList().size(); c++)
		{
			//if starts with Door. find door with name
			if(area.connectionTYPEIDList().get(c).startsWith("DOOR"))
			{
				for(int i=0;i<getNumDoors();i++)
				{
					if((MapCanvas.drawRandomPointOfInterestLines==true && getSelectedAreaIndex()==-1) || (getSelectedAreaIndex()!=-1 && getSelectedArea() == area) || MapCanvas.selectedAllLayers)
					if(area.connectionTYPEIDList().get(c).equals(getDoor(i).getTYPEIDString()))
					{
						G.setColor(Color.GREEN);

						int bottomOffset = getDoor(i).getSprite().getAnimationStartFrameForFrame(0).hitBoxFromBottomPixels1X;

						int endDoorX = (int)((getDoor(i).xP() + (getDoor(i).wP()/2))*zoom);
						int endDoorY = (int)((getDoor(i).yP() + (getDoor(i).hP()-bottomOffset))*zoom);

						drawArrowLine(G,ax, ay, endDoorX, endDoorY);
					}
				}
			}
			else
			{
				//if doesnt start with door, it's an action
				//go through actions and find name

				for(int i=0;i<getNumAreas();i++)
				{
					if((MapCanvas.drawRandomPointOfInterestLines==true && getSelectedAreaIndex()==-1) || (getSelectedAreaIndex()!=-1 && getSelectedArea() == area) || i == getSelectedAreaIndex() || MapCanvas.selectedAllLayers)
					if(area.connectionTYPEIDList().get(c).equals(getArea(i).getTYPEIDString()))
					{
						G.setColor(Color.GREEN);

						int actionx = (int)((getArea(i).xP() + (getArea(i).wP()/2))*zoom);
						int actiony = (int)((getArea(i).yP() + (getArea(i).hP()/2))*zoom);

						drawArrowLine(G,ax, ay, actionx, actiony);
					}
				}
			}
		}




	}



	//===============================================================================================
	public void drawAreaInfo(Graphics G, Area area)
	{//===============================================================================================





		float zoom =  ((float)MapCanvas.zoom/8.0f);

		int x = (int)(((float)area.xP())*zoom);
		int y = (int)(((float)area.yP())*zoom);
		int w = (int)(((float)(area.wP()))*zoom)-1;
		int h = (int)(((float)(area.hP()))*zoom)-1;

			G.setFont(new Font("Tahoma", Font.PLAIN, 9));
			int strings = -1;

			if(area.isWarpArea()==true)
			{
				drawOutlinedString(G,area.name(), x, y-18,Color.WHITE);

				if(area.destinationTYPEIDString().equals(area.getTYPEIDString())==false)
				{
					drawOutlinedString(G,"WarpArea: Goes to: "+area.destinationArea().getLongTypeName(), x, y-9,new Color(200,0,255,255));
				}
				else
				{
					//if it doesn't have a destination set, mark it as problematic
					drawOutlinedString(G,"WarpArea: Has no destination!", x, y-9,Color.RED);
				}
			}
			else
			drawOutlinedString(G,area.name(), x, y-9,Color.WHITE);

			//if(a.isAnAction)drawOutlinedString(G,"Is An Action", x, y+(++strings*9),Color.RED);
			//if(a.eventID!=-1)drawOutlinedString(G,"Has Event", x, y+(++strings*9),Color.RED);

			if(area.eventData()!=null)
			{
				if(Project.getEventByID(area.eventData().id()).getFirstDialogueCaption().length()>0)
				drawOutlinedString(G,"Has Event: "+Project.getEventByID(area.eventData().id()).getFirstDialogueCaption(), x, y+(++strings*9),Color.RED);
				else
				drawOutlinedString(G,"Has Event: "+Project.getEventByID(area.eventData().id()).getFirst20Chars(), x, y+(++strings*9),Color.RED);
			}




			if(area.waitHereTicks()==-1)drawOutlinedString(G,"Stop Here", x, y+(++strings*9),Color.YELLOW);
			if(area.waitHereTicks()>0&&area.randomWaitTime()==false)drawOutlinedString(G,"Wait "+area.waitHereTicks(), x, y+(++strings*9),Color.YELLOW);
			if(area.waitHereTicks()>0&&area.randomWaitTime()==true)drawOutlinedString(G,"Wait Random < "+area.waitHereTicks(), x, y+(++strings*9),Color.YELLOW);
			if(area.onlyOneAllowed())drawOutlinedString(G,"Only 1", x, y+(++strings*9),Color.GREEN);

			if(area.suckPlayerIntoMiddle())drawOutlinedString(G,"Suck Player Into Middle", x, y+(++strings*9),Color.GREEN);
			if(area.autoPilot())drawOutlinedString(G,"Is AutoPilot Action!", x, y+(++strings*9),Color.RED);

			if(area.standSpawnDirection()!=-1)
			{
				if(area.playerFaceDirection())
				{
					if(area.standSpawnDirection()==0)drawOutlinedString(G,"Player Face Dir: Up", x, y+(++strings*9),Color.ORANGE);
					if(area.standSpawnDirection()==1)drawOutlinedString(G,"Player Face Dir: Down", x, y+(++strings*9),Color.ORANGE);
					if(area.standSpawnDirection()==2)drawOutlinedString(G,"Player Face Dir: Left", x, y+(++strings*9),Color.ORANGE);
					if(area.standSpawnDirection()==3)drawOutlinedString(G,"Player Face Dir: Right", x, y+(++strings*9),Color.ORANGE);
				}
				else
				{
					if(area.standSpawnDirection()==0)drawOutlinedString(G,"Dir: Up", x, y+(++strings*9),Color.YELLOW);
					if(area.standSpawnDirection()==1)drawOutlinedString(G,"Dir: Down", x, y+(++strings*9),Color.YELLOW);
					if(area.standSpawnDirection()==2)drawOutlinedString(G,"Dir: Left", x, y+(++strings*9),Color.YELLOW);
					if(area.standSpawnDirection()==3)drawOutlinedString(G,"Dir: Right", x, y+(++strings*9),Color.YELLOW);
				}
			}



			if(area.randomPointOfInterestOrExit())drawOutlinedString(G,"Random Point Of Interest", x, y+(++strings*9),Color.WHITE);
			if(area.randomNPCSpawnPoint())drawOutlinedString(G,"Random Spawn Point", x, y+(++strings*9),Color.MAGENTA);
			if(area.randomNPCSpawnPoint())
			{
				String allowedTypes = "";
				if(area.randomSpawnKids())allowedTypes = allowedTypes+" Kids";
				if(area.randomSpawnAdults())allowedTypes = allowedTypes+" Adults";
				if(area.randomSpawnMales())allowedTypes = allowedTypes+" Males";
				if(area.randomSpawnFemales())allowedTypes = allowedTypes+" Females";
				if(area.randomSpawnCars())allowedTypes = allowedTypes+" Cars";
				drawOutlinedString(G,"Spawn Types: "+allowedTypes, x, y+(++strings*9),Color.MAGENTA);
			}
			if(area.randomNPCStayHere())drawOutlinedString(G,"Random Stay Here", x, y+(++strings*9),Color.WHITE);
			if(area.randomSpawnOnlyTryOnce())drawOutlinedString(G,"Random Only Try Once: "+area.randomSpawnChance(), x, y+(++strings*9),Color.WHITE);
			if(area.randomSpawnOnlyOffscreen())drawOutlinedString(G,"Random Only Offscreen", x, y+(++strings*9),Color.WHITE);



	}


	//===============================================================================================
	public void drawAreaOutline(Graphics G, Area a)
	{//===============================================================================================


		float zoom =  ((float)MapCanvas.zoom/8.0f);


		int x = (int)(((float)a.xP())*zoom);
		int y = (int)(((float)a.yP())*zoom);
		int w = (int)(((float)(a.wP()))*zoom)-1;
		int h = (int)(((float)(a.hP()))*zoom)-1;

		int ax = (int)(((float)a.arrivalXPixels()) * zoom);
		int ay = (int)(((float)a.arrivalYPixels()) * zoom);
		int aw = (int)(8.0f*zoom)-1;
		int ah = (int)(8.0f*zoom)-1;


		//G.setColor(new Color(255,155,0,127));
		//G.fillRect(x, y, w, h);

		G.setColor(Color.BLACK);
		G.drawRect(x+1,y+1,w-2,h-2);
		G.drawRect(x-1,y-1,w+2,h+2);
		if(a.isWarpArea()==true)G.setColor(new Color(200,0,255,255));
		else if(a.randomNPCSpawnPoint())G.setColor(Color.MAGENTA);
		else if(a.randomPointOfInterestOrExit())G.setColor(Color.WHITE);
		else G.setColor(Color.ORANGE);
		G.drawRect(x,y,w,h);



		//draw arrival point if it has one
		if(a.isWarpArea()==true)
		{
			G.setColor(new Color(200,0,255,91));
			G.fillRect(ax, ay, aw, ah);

			G.setColor(new Color(200,0,255,255));
			G.drawRect(ax, ay, aw, ah);

			G.setColor(Color.WHITE);
			G.drawLine(x+(w/2), y+(h/2), ax+(aw/2), ay+(ah/2));


			if(a.destinationTYPEIDString().equals(a.getTYPEIDString()))
			{
				//if it doesn't have a destination set, mark it as problematic
				G.setFont(new Font("Tahoma", Font.PLAIN, 9));
				drawOutlinedString(G,"WarpArea: Has no destination!", x, y-9,Color.RED);
			}
		}
	}

	//===============================================================================================
	public void drawAllAreaOutlines(Graphics G)
	{//===============================================================================================
		for(int i = 0; i<getNumAreas();i++)
		{
			Area a = getArea(i);

			drawAreaOutline(G,a);
		}

	}

	//===============================================================================================
	public void drawAllAreaConnections(Graphics G)
	{//===============================================================================================
		for(int i = 0; i<getNumAreas();i++)
		{
			Area a = getArea(i);

			drawAreaConnections(G,a);
		}

	}

	//===============================================================================================
	public void drawAreaLayerSelection(Graphics G)
	{//===============================================================================================

		float zoom =  ((float)MapCanvas.zoom/8.0f);


		for(int i = 0; i<getNumAreas();i++)
		{
			Area a = getArea(i);

			drawAreaOutline(G,a);

			if(MapCanvas.alwaysShowAreaAndSpriteInfo==true)
			drawAreaConnections(G,a);

			if(MapCanvas.alwaysShowAreaAndSpriteInfo==true)
			drawAreaInfo(G,a);

		}


		//draw bounds box over selected action
		if(getSelectedAreaIndex()<getNumAreas()&&getSelectedAreaIndex()>=0)
		{

			Area a = getSelectedArea();

			int x = (int)(((float)a.xP())*zoom);
			int y = (int)(((float)a.yP())*zoom);
			int w = (int)(((float)(a.wP()))*zoom)-1;
			int h = (int)(((float)(a.hP()))*zoom)-1;


			G.setColor(new Color(0,255,0,91));
			G.fillRect(x, y, w, h);

			G.setColor(Color.BLACK);
			G.drawRect(x+2,y+2,w-4,h-4);
			G.drawRect(x-1,y-1,w+2,h+2);
			G.setColor(Color.GREEN);
			G.drawRect(x, y, w, h);
			G.drawRect(x+1, y+1, w-2, h-2);


			drawAreaConnections(G,a);
			drawAreaInfo(G,a);


			//Font[] fonts = GraphicsEnvironment.getLocalGraphicsEnvironment().getAllFonts();

			//for(int f=0;f<fonts.length;f++)
				//System.out.println(fonts[f].getFontName());
		}
	}





	//===============================================================================================
	public void createDoor(String spriteName, int x, int y)
	{//===============================================================================================

		Sprite sprite = getSpriteByName(spriteName);
		//go through all other doors in this map. if doorsName exists, append number.


		Door d = new Door(this);

		d.setName(sprite.name());

		boolean unique = false;
		int number = 0;

		while(unique==false)
		{
			boolean uniqueThisTime = true;
			for(int i=0;i<getNumDoors();i++)
			{
				if(d!=getDoor(i) && d.name().equals(getDoor(i).name()))
				{
					uniqueThisTime = false;
					d.setName(sprite.name().concat(""+number));
					number++;
				}
			}
			if(uniqueThisTime==true)unique=true;
		}


		//d.spriteName = sprite.name;
		d.setXPixels(x);
		d.setYPixels(y);
		d.setSprite(sprite);

		d.setArrivalXPixels(x+d.wP());
		d.setArrivalYPixels(y+d.hP());


		addDoor(d);

		setSelectedDoorIndex(getNumDoors()-1);


	}

	//===============================================================================================
	//public void deleteDoor(int n)
	//{//===============================================================================================

		//go through sprites, areas, doors, remove connections
		//for(int i=0;i<getNumDoors();i++){getDoor(i).connectionList.remove("Door."+getDoor(n).getName());}
		//for(int i=0;i<getNumAreas();i++){getArea(i).connectionList.remove("Door."+getDoor(n).getName());}
		//for(int i=0;i<getNumEntities();i++){getEntity(i).connectionList.remove("Door."+getDoor(n).getName());}

//		for(int i = n; i < getNumDoors(); i++)
//		{
//			getDoor(i) = door[i + 1];
//
//		}
//		door[getNumDoors()] = new Door();
//		if(getNumDoors() > 0)
//		{
//			getNumDoors()--;
//		}

		//getSelectedState().door.remove(n);


	//}
	//===============================================================================================
	public void drawDoorLayer(Graphics G)
	{//===============================================================================================

		for(int i = 0; i<getNumDoors();i++)
		{
			Door d = getDoor(i);

			G.drawImage(d.getImage(), d.xP(), d.yP(), this);
		}
	}

	//===============================================================================================
	public void drawDoorLayerAtTileXY(Graphics G, int mapX, int mapY)
	{//===============================================================================================

		for(int i = 0; i<getNumDoors();i++)
		{

			Door d = getDoor(i);

			int x=d.xP();
			int y=d.yP();
			int w=d.wP();
			int h=d.hP();

			if(x>(mapX)+8||y>(mapY)+8||x+w<(mapX)||y+h<(mapY))continue;



			//find clip of sprite image we need to draw
			int clipX = mapX-x;
			int clipY = mapY-y;

			G.drawImage(d.getImage(),mapX, mapY, mapX+8, mapY+8, clipX, clipY, clipX+8, clipY+8, this);

		}
	}


	//===============================================================================================
	public void drawArrowLine(Graphics G, int x1, int y1, int x2, int y2)
	{//===============================================================================================

		G.drawLine(x1, y1, x2, y2);

		//get distance
		float dx = (x2-x1);
		float dy = (y2-y1);

		//get midpoint from distance
		float midX = (x1+dx/2);
		float midY = (y1+dy/2);

		//make distance half since we are using midpoint
		dx/=2;
		dy/=2;

		//get actual distance to midpoint
		float dist = (float) Math.sqrt(dx*dx + dy*dy);

		//get distance ratio
		float distXRatio=dx/dist;
		float distYRatio=dy/dist;

		int arrowWidth = 12;

		//get perpendicular points to midpoint
		float midXPerpX1 =  (midX + (arrowWidth/2)*distYRatio);
		float midYPerpY1 =  (midY - (arrowWidth/2)*distXRatio);
		float midXPerpX2 =  (midX - ((arrowWidth)/2)*distYRatio);
		float midYPerpY2 =  (midY + ((arrowWidth)/2)*distXRatio);



		//get point 10 pixels past midpoint
		float pastMidX = (x1 + (dist+16)*distXRatio);
		float pastMidY = (y1 + (dist+16)*distYRatio);

		G.drawLine((int)midXPerpX1, (int)midYPerpY1, (int)midXPerpX2, (int)midYPerpY2);
		G.drawLine((int)midXPerpX1, (int)midYPerpY1, (int)pastMidX, (int)pastMidY);
		G.drawLine((int)midXPerpX2, (int)midYPerpY2, (int)pastMidX, (int)pastMidY);



	}

	//===============================================================================================
	public void drawDoorInfo(Graphics G, Door d)
	{//===============================================================================================

		float zoom =  ((float)MapCanvas.zoom/8.0f);

		int x = (int)(((float)d.xP())*zoom);
		int y = (int)(((float)d.yP())*zoom);


		G.setFont(new Font("Tahoma", Font.PLAIN, 9));

		int strings = -1;


		drawOutlinedString(G,d.name(), x, y-18,Color.YELLOW);


		if(d.destinationTYPEIDString().equals(d.getTYPEIDString())==false)
		{
			drawOutlinedString(G,"Goes to: "+d.destinationDoor().getLongTypeName(), x, y-9,new Color(200,0,255,255));
		}
		else
		{
			//if it doesn't have a destination set, mark it as problematic
			drawOutlinedString(G,"Has no destination!", x, y-9,Color.RED);
		}



		if(d.eventData()!=null)
		drawOutlinedString(G,"Event: "+Project.getEventByID(d.eventData().id()).getFirst20Chars(), x, y+(++strings*9),Color.WHITE);

		drawOutlinedString(G,"Sprite: "+d.getSprite().name(), x, y+(++strings*9),Color.WHITE);

		if(d.randomNPCSpawnPoint())drawOutlinedString(G,"Random Spawn Point | Chance: "+d.randomSpawnChance(), x, y+(++strings*9),Color.MAGENTA);

		if(d.randomNPCSpawnPoint())drawOutlinedString(G,"Spawn Delay: "+d.randomSpawnDelay(), x, y+(++strings*9),Color.WHITE);

		if(d.randomNPCSpawnPoint())
		{
			String allowedTypes = "";
			if(d.randomSpawnKids())allowedTypes = allowedTypes+" Kids";
			if(d.randomSpawnAdults())allowedTypes = allowedTypes+" Adults";
			if(d.randomSpawnMales())allowedTypes = allowedTypes+" Males";
			if(d.randomSpawnFemales())allowedTypes = allowedTypes+" Females";
			drawOutlinedString(G,"Spawn Types: "+allowedTypes, x, y+(++strings*9),Color.MAGENTA);
		}

		if(d.randomPointOfInterestOrExit())drawOutlinedString(G,"Random Exit (Point Of Interest)", x, y+(++strings*9),Color.RED);



	}
	//===============================================================================================
	public void drawDoorConnections(Graphics G, Door d)
	{//===============================================================================================


		float zoom =  ((float)MapCanvas.zoom/8.0f);



		//from arrival point
		//int ax = (int)(((float)d.arrivalX+4)*zoom);
		//int ay = (int)(((float)d.arrivalY+4)*zoom);

		//from bottom of door
		int ax = (int)((d.xP() + (d.wP()/2))*zoom);
		int ay = (int)((d.yP() + (d.hP()-d.getSprite().getAnimationStartFrameForFrame(0).hitBoxFromBottomPixels1X*zoom)));

		//if this is a random spawn point
		//draw a connection to all random points of interest
		if(d.connectionTYPEIDList().size()==0&&(d.randomNPCSpawnPoint() || d.randomPointOfInterestOrExit()))
		{

			//for all actions
			for(int i=0;i<getNumAreas();i++)
			{
				//only draw arrows to areas for all doors if nothing is selected
				//if a door is selected, only draw arrows for the selected one
				//or if this door is drawing an arrow TO the selected area, draw that.
				if((MapCanvas.drawRandomPointOfInterestLines==true && getSelectedDoorIndex()==-1) || (getSelectedDoorIndex()!=-1 && getSelectedDoor() == d) || MapCanvas.selectedAllLayers)
				if(getArea(i).randomPointOfInterestOrExit() || getArea(i).randomNPCSpawnPoint())
				{
					if(d.randomNPCSpawnPoint() || getArea(i).randomNPCSpawnPoint())G.setColor(Color.MAGENTA);
					else G.setColor(Color.WHITE);

					int actionx = (int)((getArea(i).xP() + (getArea(i).wP()/2))*zoom);
					int actiony = (int)((getArea(i).yP() + (getArea(i).hP()/2))*zoom);

					if(getArea(i).randomNPCSpawnPoint())
					{
						//draw arrow from area to door
						drawArrowLine(G,actionx, actiony,ax, ay);
						//if this area doesn't go anywhere, draw arrow back to area.
						if(d.connectionTYPEIDList().size()==0)drawArrowLine(G,ax, ay, actionx, actiony);
					}
					else drawArrowLine(G,ax, ay, actionx, actiony);
				}
			}

			//for all doors
			for(int i=0;i<getNumDoors();i++)
			{
				//only draw arrows to doors for all doors if nothing is selected
				//if a door is selected, draw arrows for the selected one only
				//if this door is drawing an arrow TO the selected door, draw that.
				if((MapCanvas.drawRandomPointOfInterestLines==true && getSelectedDoorIndex()==-1) || (getSelectedDoorIndex()!=-1 && getSelectedDoor() == d) || i == getSelectedDoorIndex() || MapCanvas.selectedAllLayers)
				if(getDoor(i) != d && (getDoor(i).randomPointOfInterestOrExit()==true || getDoor(i).randomNPCSpawnPoint()))
				{
					if(d.randomNPCSpawnPoint() || getDoor(i).randomNPCSpawnPoint())G.setColor(Color.MAGENTA);
					else G.setColor(Color.WHITE);

					int bottomOffset =(int)(((float) getDoor(i).getSprite().getAnimationStartFrameForFrame(0).hitBoxFromBottomPixels1X));

					int endDoorX = (int)((getDoor(i).xP() + (getDoor(i).wP()/2))*zoom);
					int endDoorY = (int)((getDoor(i).yP() + (getDoor(i).hP()-bottomOffset))*zoom);

					drawArrowLine(G,ax, ay, endDoorX, endDoorY);
				}
			}
		}

		//if this is selected door
		//go through all actions, all connections, if connection is this door, draw line from connection to door
		if(getSelectedDoorIndex()!=-1 && getSelectedDoor() == d)
		{
			for(int i=0;i<getNumAreas();i++)
			{
				for(int c=0; c<getArea(i).connectionTYPEIDList().size(); c++)
				{
					if(getArea(i).connectionTYPEIDList().get(c).equals(getSelectedDoor().getTYPEIDString()))
					{
						G.setColor(Color.GREEN);

						int actionx = (int)((getArea(i).xP() + (getArea(i).wP()/2))*zoom);
						int actiony = (int)((getArea(i).yP() + (getArea(i).hP()/2))*zoom);

						drawArrowLine(G,actionx, actiony, ax,ay);
					}
				}
			}

		}



		//for all connections from this door
		for(int c=0; c<d.connectionTYPEIDList().size(); c++)
		{

			//if starts with Door. find door with name
			if(d.connectionTYPEIDList().get(c).startsWith("DOOR"))
			{
				for(int i=0;i<getNumDoors();i++)
				{
					if((MapCanvas.drawRandomPointOfInterestLines==true && getSelectedDoorIndex()==-1) || (getSelectedDoorIndex()!=-1 && getSelectedDoor() == d) || i == getSelectedDoorIndex() || MapCanvas.selectedAllLayers)
					if(d.connectionTYPEIDList().get(c).equals(getDoor(i).getTYPEIDString()))
					{
						G.setColor(Color.GREEN);

						int bottomOffset = (int)(((float) getDoor(i).getSprite().getAnimationStartFrameForFrame(0).hitBoxFromBottomPixels1X));

						int endDoorX = (int)((getDoor(i).xP() + (getDoor(i).wP()/2))*zoom);
						int endDoorY = (int)((getDoor(i).yP() + (getDoor(i).hP()-bottomOffset))*zoom);

						drawArrowLine(G,ax, ay, endDoorX, endDoorY);
					}
				}
			}
			else
			{
				//if doesnt start with door, it's an action
				//go through actions and find name

				for(int i=0;i<getNumAreas();i++)
				{
					if((MapCanvas.drawRandomPointOfInterestLines==true && getSelectedDoorIndex()==-1) || (getSelectedDoorIndex()!=-1 && getSelectedDoor() == d) || MapCanvas.selectedAllLayers)
					if(d.connectionTYPEIDList().get(c).equals(getArea(i).getTYPEIDString()))
					{
						G.setColor(Color.GREEN);

						int actionx = (int)((getArea(i).xP() + (getArea(i).wP()/2))*zoom);
						int actiony = (int)((getArea(i).yP() + (getArea(i).hP()/2))*zoom);

						drawArrowLine(G,ax, ay, actionx, actiony);

					}
				}
			}
		}



	}

	//===============================================================================================
	public void drawDoorOutline(Graphics G, Door d)
	{//===============================================================================================
		float zoom =  ((float)MapCanvas.zoom/8.0f);

		int x = (int)(((float)d.xP())*zoom);
		int y = (int)(((float)d.yP())*zoom);
		int w = (int)(((float)(d.wP()))*zoom)-1;
		int h = (int)(((float)(d.hP()))*zoom)-1;

		//draw purple rectangle with black outlines
		G.setColor(Color.BLACK);
		G.drawRect(x+1,y+1,w-2,h-2);
		G.drawRect(x-1,y-1,w+2,h+2);
		G.setColor(new Color(200,0,255,255));
		G.drawRect(x,y,w,h);
	}

	//===============================================================================================
	public void drawDoorArrivalPoint(Graphics G, Door d)
	{//===============================================================================================

		float zoom =  ((float)MapCanvas.zoom/8.0f);

		int x = (int)(((float)d.xP())*zoom);
		int y = (int)(((float)d.yP())*zoom);
		int w = (int)(((float)(d.wP()))*zoom)-1;
		int h = (int)(((float)(d.hP()))*zoom)-1;

		int ax = (int)(((float)d.arrivalXPixels()) * zoom);
		int ay = (int)(((float)d.arrivalYPixels()) * zoom);
		int aw = (int)(8.0f*zoom)-1;
		int ah = (int)(8.0f*zoom)-1;

		//draw purple arrival point marker
		G.setColor(new Color(200,0,255,91));
		G.fillRect(ax, ay, aw, ah);

		G.setColor(new Color(200,0,255,255));
		G.drawRect(ax, ay, aw, ah);

		//draw connecting line
		G.setColor(Color.WHITE);
		G.drawLine(x+(w/2), y+(h/2), ax+(aw/2), ay+(ah/2));
	}

	//===============================================================================================
	public void drawDoorActivationBox(Graphics G, Door d)
	{//===============================================================================================

		float zoom =  ((float)MapCanvas.zoom/8.0f);

		int x = (int)(((float)d.xP())*zoom);
		int y = (int)(((float)d.yP())*zoom);
		int w = (int)(((float)(d.wP()))*zoom)-1;
		int h = (int)(((float)(d.hP()))*zoom)-1;

		int leftOffset = (int)(((float)d.getSprite().getAnimationStartFrameForFrame(0).hitBoxFromLeftPixels1X) * zoom);
		int rightOffset = (int)(((float)d.getSprite().getAnimationStartFrameForFrame(0).hitBoxFromRightPixels1X) * zoom);
		int topOffset = (int)(((float)d.getSprite().getAnimationStartFrameForFrame(0).hitBoxFromTopPixels1X) * zoom);
		int bottomOffset =(int)(((float) d.getSprite().getAnimationStartFrameForFrame(0).hitBoxFromBottomPixels1X) * zoom);

		//draw yellow activation area (hitbox)
		G.setColor(new Color(255,255,0,127));
		G.fillRect(x+leftOffset,y+topOffset,((w-leftOffset)-rightOffset),h-(topOffset+bottomOffset));
		G.setColor(Color.YELLOW);
		G.drawRect(x+leftOffset,y+topOffset,((w-leftOffset)-rightOffset),h-(topOffset+bottomOffset));
	}

	//===============================================================================================
	public void drawDoorLayerSelection(Graphics G)
	{//===============================================================================================

		float zoom =  ((float)MapCanvas.zoom/8.0f);


		//draw rectangle around all Doors
		for(int n=0;n<getNumDoors();n++)
		{

			Door d = getDoor(n);

			drawDoorOutline(G,d);
			drawDoorActivationBox(G,d);
			drawDoorArrivalPoint(G,d);
			drawDoorConnections(G,d);
			drawDoorInfo(G,d);


		}


		//draw bounds box over selected mapsprite
		if(getSelectedDoorIndex()<getNumDoors()&&getSelectedDoorIndex()>=0)
		{

			Door d = getSelectedDoor();

			int x = (int)(((float)d.xP())*zoom);
			int y = (int)(((float)d.yP())*zoom);
			int w = (int)(((float)(d.wP()))*zoom)-1;
			int h = (int)(((float)(d.hP()))*zoom)-1;

			G.setColor(Color.BLACK);
			G.drawRect(x+2,y+2,w-4,h-4);
			G.drawRect(x-1,y-1,w+2,h+2);
			G.setColor(Color.GREEN);
			G.drawRect(x,y,w,h);
			G.drawRect(x+1,y+1,w-2,h-2);


			//redraw the connections and info since we drew over them
			drawDoorConnections(G,d);
			drawDoorInfo(G,d);


		}

	}


	//===============================================================================================
	public void replaceTileWithNewTileOnEveryLayer(int tile, int newtile)
	{//===============================================================================================
		for(int l = 0; l < MapData.layers; l++)
		{
			if(MapData.isTileLayer(l))
			if(l != MapData.MAP_HIT_LAYER)
			{
				for(int y = 0; y < hT(); y++)
				{
					for(int x = 0; x < wT(); x++)
					{
						if(layerTileIndex[l][x][y] == tile)
						{
							layerTileIndex[l][x][y] = newtile;
						}

					}
				}
			}
		}
	}


	//===============================================================================================
	public void swapTilesOnMapOnLayer(int l, int tile, int newtile)
	{//===============================================================================================
		if(MapData.isTileLayer(l))
		for(int y = 0; y < hT(); y++)
		{
			for(int x = 0; x < wT(); x++)
			{
				if(layerTileIndex[l][x][y] == tile)
				{
					layerTileIndex[l][x][y] = newtile;
				}
				else if(layerTileIndex[l][x][y] == newtile)
				{
					layerTileIndex[l][x][y] = tile;
				}
			}
		}
	}

	//===============================================================================================
	public void swapTilesOnMapEveryLayer(int tile, int newtile) //ACTUALLY SWAP ALL
	{//===============================================================================================
		for(int l = 0; l < MapData.layers; l++)
		{
			if(MapData.isTileLayer(l))
			swapTilesOnMapOnLayer(l, tile, newtile);
		}
	}

	//===============================================================================================
	public void shiftTileIndices(int offset)
	{//===============================================================================================
		for(int l = 0; l < MapData.layers; l++)
		{
			if(MapData.isTileLayer(l))
			{
				for(int y = 0; y < hT(); y++)
				{
					for(int x = 0; x < wT(); x++)
					{
						int tile = layerTileIndex[l][x][y];
						if(tile > 0)
						{
							layerTileIndex[l][x][y] = tile + offset;
						}
					}
				}
			}
		}
	}






	//===============================================================================================
	public boolean imageUpdate(Image i, int i1, int i2, int i3, int i4, int i5)
	{//===============================================================================================

		return false;
	}






	//===============================================================================================
	public void runGC()
	{//===============================================================================================

		for(int i=0;i<1;i++)
		{
			System.gc();
		}
	}




	//===============================================================================================
	public void saveMapPNGForEachLayer(String dirpath)
	{//===============================================================================================

		EditorMain.infoLabel.setText("Outputting " + name() + " to PNG Hold On...");

		if(dirpath==null)dirpath = EditorMain.getDesktopTempDirPath();
		Utils.makeDir(dirpath + "png\\" + name() + "(0,1,2,3,4,5,6,7,8,9,10,11)\\");


		EditorMain.mapCanvas.mapCanvasImage.flush();
		EditorMain.mapCanvas.mapCanvasImage = null;
		runGC();

		EditorMain.mapCanvas.mapCanvasImage = new BufferedImage(wT() * 8, hT() * 8, BufferedImage.TYPE_INT_ARGB);

		runGC();

		Graphics g = EditorMain.mapCanvas.mapCanvasImage.getGraphics();
		g.setColor(new Color(0, 0, 0, 0));
		g.fillRect(0, 0, wT() * 8, hT() * 8);

		int l = 0;
		for(l = 0; l < MapData.layers; l++)
		{

			EditorMain.infoLabel.setText("Outputting " + name() + " Layer " + l + " to PNG...");


			EditorMain.mapCanvas.mapCanvasImage.flush();
			EditorMain.mapCanvas.mapCanvasImage = null;
			runGC();

			EditorMain.mapCanvas.mapCanvasImage = new BufferedImage(wT() * 8, hT() * 8, BufferedImage.TYPE_INT_ARGB);

			runGC();

			g = EditorMain.mapCanvas.mapCanvasImage.getGraphics();
			//g.setColor(E.project.getSelectedPalette().getColor(0));

			g.setColor(new Color(0, 0, 0, 0));
			g.fillRect(0, 0, wT() * 8, hT() * 8);
			g.drawImage(createTempLayerImage(l), 0, 0, this);

			runGC();


			Utils.saveImage(dirpath + "png\\" + name() + "(0,1,2,3,4,5,6,7,8,9,10,11)\\" + name() + "_Map_Layer_" + l + ".png",EditorMain.mapCanvas.mapCanvasImage);

		}


		g.dispose();
		EditorMain.mapCanvas.mapCanvasImage.flush();
		EditorMain.mapCanvas.mapCanvasImage = null;
		runGC();
		//destroyImages();

	}

	//===============================================================================================
	public void saveMapCombinedLayersToPNG(String dirpath)
	{//===============================================================================================

		if(dirpath==null)dirpath = EditorMain.getDesktopTempDirPath();

		EditorMain.infoLabel.setText("Outputting " + name() + " to PNG Hold On...");

		Utils.makeDir(dirpath + "png\\" + name() + "(01345,789)\\");


		EditorMain.mapCanvas.mapCanvasImage.flush();
		EditorMain.mapCanvas.mapCanvasImage = null;
		runGC();

		EditorMain.mapCanvas.mapCanvasImage = new BufferedImage(wT() * 8, hT() * 8, BufferedImage.TYPE_INT_ARGB);

		runGC();

		Graphics g = EditorMain.mapCanvas.mapCanvasImage.getGraphics();
		g.setColor(new Color(0, 0, 0, 0));
		g.fillRect(0, 0, wT() * 8, hT() * 8);

		EditorMain.infoLabel.setText("Outputting " + name() + " 013456 to PNG...");

		g.drawImage(createTempLayerImage(0), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(1), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(3), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(4), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(5), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(6), 0, 0, this);
		runGC();


		Utils.saveImage(dirpath + "png\\" + name() + "(013456,789)\\" + name() + "_Map_01345.png",EditorMain.mapCanvas.mapCanvasImage);



		EditorMain.mapCanvas.mapCanvasImage.flush();
		EditorMain.mapCanvas.mapCanvasImage = null;
		runGC();

		EditorMain.mapCanvas.mapCanvasImage = new BufferedImage(wT() * 8, hT() * 8, BufferedImage.TYPE_INT_ARGB);

		runGC();

		g = EditorMain.mapCanvas.mapCanvasImage.getGraphics();

		g.setColor(new Color(0, 0, 0, 0));
		g.fillRect(0, 0, wT() * 8, hT() * 8);

		runGC();

		EditorMain.infoLabel.setText("Outputting " + name() + " 789 to PNG...");

		g.drawImage(createTempLayerImage(7), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(8), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(9), 0, 0, this);
		runGC();


		Utils.saveImage(dirpath + "png\\" + name() + "(01345,789)\\" + name() + "_Map_789.png", EditorMain.mapCanvas.mapCanvasImage);


		g.dispose();
		EditorMain.mapCanvas.mapCanvasImage.flush();
		EditorMain.mapCanvas.mapCanvasImage = null;
		runGC();

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

		int clear = new Color(0,0,0,0).getRGB();

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

					if(black==1)bufferedImage.setRGB(x, y, new Color(0,0,0,127).getRGB());
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
						hq2xBufferedImage.setRGB((x*2)+xx, ((y*2)+yy), new Color(0,0,0,0).getRGB());
				}

			}
		}
	}




	//===============================================================================================
	public void saveMapCombinedLayersToHQ2XPNG(String dirpath)
	{//===============================================================================================



		if(dirpath==null)dirpath = EditorMain.getDesktopTempDirPath();

		EditorMain.infoLabel.setText("Outputting " + name() + " to HQ2X PNG Hold On...");

		Utils.makeDir(dirpath + "png\\hq2xmap\\"+name()+"\\");
		//----------------------
		//flush mapbuffer if exists
		//----------------------
			if(EditorMain.mapCanvas.mapCanvasImage!=null)
			{
				EditorMain.mapCanvas.mapCanvasImage.flush();
				EditorMain.mapCanvas.mapCanvasImage = null;
			}
			runGC();

			Graphics g;


		//----------------------
		//draw top layer 1x
		//----------------------

		EditorMain.infoLabel.setText(name() + " | Drawing 1x top layer");

		//BufferedImage top = E.getGraphicsConfiguration().createCompatibleImage(getWidth() * 8, getHeight() * 8, Transparency.TRANSLUCENT);
		BufferedImage top = new BufferedImage(wT() * 8, hT() * 8, BufferedImage.TYPE_INT_ARGB);

		runGC();

		g = top.getGraphics();

		g.setColor(new Color(0, 0, 0, 0));
		g.fillRect(0, 0, wT()*8, hT()*8);

		runGC();

		g.drawImage(createTempLayerImage(7), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(8), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(9), 0, 0, this);
		runGC();

		g.dispose();
		g=null;
		runGC();

		//----------------------
		//draw bottom+top layer 1x
		//----------------------

		EditorMain.infoLabel.setText(name() + " | Drawing 1x bottom+top layer");

		//BufferedImage bottomAndTop = E.getGraphicsConfiguration().createCompatibleImage(getWidth() * 8, getHeight() * 8, Transparency.TRANSLUCENT);
		BufferedImage bottomAndTop = new BufferedImage(wT() * 8, hT() * 8, BufferedImage.TYPE_INT_RGB);

		runGC();

		g = bottomAndTop.getGraphics();

		g.setColor(new Color(0, 0, 0, 0));
		g.fillRect(0, 0, wT()*8, hT()*8);

		runGC();



		g.drawImage(createTempLayerImage(0), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(1), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(3), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(4), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(5), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(6), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(7), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(8), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(9), 0, 0, this);
		runGC();

		g.dispose();
		g=null;
		runGC();
		//----------------------
		//TOP LAYER
		//----------------------

			int clear = new Color(0,0,0,0).getRGB();

			//hq2x bottom+top

			EditorMain.infoLabel.setText(name() + " | HQ2Xing bottom+top layer");

			BufferedImage hq2xBottomAndTop = new HQ2X().HQ2X(bottomAndTop);
			//setHQ2XAlphaFromOriginal(hq2xBottomAndTop,bottomAndTop); //(shouldnt be transparent here)


			EditorMain.infoLabel.setText(name() + " | Masking 1x top layer from HQ2X bottom+top");

			//go through top layer
			//for each transparent pixel set 2x (x+xx y+yy) transparent on hq2x bottom+top
			for(int y = 0; y < top.getHeight(); y++)
			{
				for(int x = 0; x < top.getWidth(); x++)
				{
					if(top.getRGB(x, y)==clear)
					{
						for(int xx=0;xx<2;xx++)
						for(int yy=0;yy<2;yy++)
							hq2xBottomAndTop.setRGB((x*2)+xx, ((y*2)+yy), clear);
					}
				}
			}


			//could antialias black edges here
			antialiasBufferedImage(hq2xBottomAndTop);


			//----------------------
			//output hq2x top layer to chunks
			//----------------------

				EditorMain.infoLabel.setText(name() + " | Outputting HQ2X top layer to chunks");

				//starting at 0 and going to hq2xBottomAndTop.width
				for(int ty=0;ty<hq2xBottomAndTop.getHeight();ty+=128)
				for(int tx=0;tx<hq2xBottomAndTop.getWidth();tx+=128)
				{
					//make 128x128 graphic
					BufferedImage chunk = new BufferedImage(128, 128, BufferedImage.TYPE_INT_ARGB);
					for(int y=0;y<128;y++)
					for(int x=0;x<128;x++)
					{
						if((tx)+x<hq2xBottomAndTop.getWidth()&&(ty)+y<hq2xBottomAndTop.getHeight())
						chunk.setRGB(x, y, hq2xBottomAndTop.getRGB((tx)+x, (ty)+y));
					}


					//fill with pixels from hq2xBottomAndTop
					//save in \\hq2xmap\\mapname as over_x_y.png

					Utils.saveImage(dirpath + "png\\hq2xmap\\" + name() + "\\"+name()+"_OverLayer_"+tx/128+"_"+ty/128+".png",chunk);

					chunk.flush();
					chunk=null;
					runGC();

				}


			//----------------------
			//output hq2x top layer fully
			//----------------------

				EditorMain.infoLabel.setText(name() + " | Outputting full HQ2X top layer");

				//save as hq2x_top
				Utils.saveImage(dirpath + "png\\hq2xmap\\" + name() + "\\"+name()+"_Map_OverLayer.png",hq2xBottomAndTop);


			//dont need hq2xBottomAndTop
			hq2xBottomAndTop.flush();
			hq2xBottomAndTop=null;
			runGC();



		//----------------------
		//BOTTOM LAYER
		//----------------------

		EditorMain.infoLabel.setText(name() + " | Drawing 1x bottom layer");

		//BufferedImage bottom = E.getGraphicsConfiguration().createCompatibleImage((getWidth()*8), (getHeight()*8), Transparency.TRANSLUCENT);
		BufferedImage bottom = new BufferedImage(wT() * 8, hT() * 8, BufferedImage.TYPE_INT_RGB);

		runGC();

		g = bottom.getGraphics();
		g.setColor(new Color(0, 0, 0, 0));
		g.fillRect(0, 0, wT()*8, hT()*8);

		g.drawImage(createTempLayerImage(0), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(1), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(3), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(4), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(5), 0, 0, this);
		runGC();
		g.drawImage(createTempLayerImage(6), 0, 0, this);
		runGC();


		g.dispose();
		g=null;
		runGC();

		EditorMain.infoLabel.setText(name() + " | HQ2Xing bottom+top layer");

		//hq2x bottom+top
		hq2xBottomAndTop = new HQ2X().HQ2X(bottomAndTop);

		//dont need bottomandtop
		bottomAndTop.flush();
		bottomAndTop=null;
		runGC();

		EditorMain.infoLabel.setText(name() + " | HQ2Xing bottom layer");

		//hq2x bottom
		BufferedImage hq2xBottom = new HQ2X().HQ2X(bottom);

		//dont need bottom
		bottom.flush();
		bottom=null;
		runGC();

		EditorMain.infoLabel.setText(name() + " | Masking HQ2X bottom layer into HQ2X bottom+top layer");

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
		runGC();

		//dont need hq2xBottom
		hq2xBottom.flush();
		hq2xBottom=null;
		runGC();

		//----------------------
		//output hq2x bottom layer to chunks
		//----------------------
			EditorMain.infoLabel.setText(name() + " | Outputting HQ2X bottom layer to chunks");

			//starting at 0 and going to hq2xBottomAndTop.width
			for(int ty=0;ty<hq2xBottomAndTop.getHeight();ty+=128)
			for(int tx=0;tx<hq2xBottomAndTop.getWidth();tx+=128)
			{
				//make 128x128 graphic
				BufferedImage chunk = new BufferedImage(128, 128, BufferedImage.TYPE_INT_ARGB);
				for(int y=0;y<128;y++)
				for(int x=0;x<128;x++)
				{
					if((tx)+x<hq2xBottomAndTop.getWidth()&&(ty)+y<hq2xBottomAndTop.getHeight())
					chunk.setRGB(x, y, hq2xBottomAndTop.getRGB((tx)+x, (ty)+y));
				}


				//fill with pixels from hq2xBottomAndTop
				//save in \\hq2xmap\\mapname as over_x_y.png

				Utils.saveImage(dirpath + "png\\hq2xmap\\" + name() + "\\"+name()+"_UnderLayer_"+tx/128+"_"+ty/128+".png",chunk);

				chunk.flush();
				chunk=null;
				runGC();

			}

		//----------------------
		//output hq2x bottom layer full
		//----------------------

			EditorMain.infoLabel.setText(name() + " | Outputting full HQ2X bottom layer");

			//save as hq2x bottom
			Utils.saveImage(dirpath + "png\\hq2xmap\\" + name() + "\\"+name()+"_Map_UnderLayer.png",hq2xBottomAndTop);

		//dont need hq2xBottomAndTop
		hq2xBottomAndTop.flush();
		hq2xBottomAndTop=null;
		runGC();

	}


	public MapState getSelectedState()
	{
		return getState(selectedState);
	}
	public int getSelectedStateIndex()
	{
		return selectedState;
	}
	public void setSelectedState(int i)
	{
		if(i<getNumStates())
		selectedState = i;
	}
	public int getNumStates()
	{
		return data.stateDataList().size();
	}
	public void duplicateState()
	{
		addState(getSelectedState().duplicate(this));
	}
	public void deleteState(MapState s)
	{
		data.stateDataList().remove(s.getData());
	}
	public MapState getState(int i)
	{
		return Project.stateIndexHashtable.get(data.stateDataList().get(i).getTYPEIDString());
	}
	public MapState getStateByName(String s)
	{
		for(int i=0;i<getNumStates();i++)
		{
			if(data.stateDataList().get(i).name().equals(s))return getState(i);
		}
		return null;
	}
	public void selectStateByName(String s)
	{
		for(int i=0;i<getNumStates();i++)
		{
			if(data.stateDataList().get(i).name().equals(s)){selectedState = i; return;}
		}
	}
	public void addState(String s)
	{
		data.stateDataList().add(new MapState(this,s).getData());
	}
	public void addState(int i, MapState s)
	{
		if(s.map()!=this)s.map().deleteState(s);
		data.stateDataList().add(i,s.getData());
	}
	public void addState(MapState s)
	{
		if(s.map()!=this)s.map().deleteState(s);
		data.stateDataList().add(s.getData());
	}

	public Door getDoor(int i)
	{
		return Project.doorIndexHashtable.get(data.doorDataList().get(i).getTYPEIDString());
	}


	public Door getDoorByName(String s)
	{
		for(int i=0;i<getNumDoors();i++)
		{
			if(data.doorDataList().get(i).name().equals(s))return getDoor(i);
		}
		return null;
	}

	public Area getArea(int i)
	{
		return getSelectedState().getArea(i);
	}

	public Area getAreaByName(String s)
	{
		return getSelectedState().getAreaByName(s);
	}

	public Light getLight(int i)
	{
		return getSelectedState().getLight(i);
	}

	public Light getLightByName(String s)
	{
		return getSelectedState().getLightByName(s);
	}

	public Entity getEntity(int i)
	{
		return getSelectedState().getEntity(i);
	}

	public Entity getEntityByName(String s)
	{
		return getSelectedState().getEntityByName(s);
	}

	public Event getEvent(int i)
	{
		return Project.eventHashtable.get("EVENT."+data.eventDataList().get(i).id());
	}




	public int getNumDoors()
	{
		return data.doorDataList().size();
	}

	public int getNumAreas()
	{
		return getSelectedState().getNumAreas();
	}

	public int getNumLights()
	{
		return getSelectedState().getNumLights();
	}

	public int getNumEntities()
	{
		return getSelectedState().getNumEntities();
	}

	public int getNumEvents()
	{
		return data.eventDataList().size();
	}
	public int getSelectedDoorIndex()
	{
		return selectedDoorIndex;
	}


	public int getSelectedAreaIndex()
	{
		return getSelectedState().getSelectedAreaIndex();
	}

	public int getSelectedLightIndex()
	{
		return getSelectedState().getSelectedLightIndex();
	}

	public int getSelectedEntityIndex()
	{
		return getSelectedState().getSelectedEntityIndex();
	}


	public void setSelectedDoorIndex(int i)
	{
		selectedDoorIndex=i;
	}




	public void setSelectedAreaIndex(int i)
	{
		getSelectedState().setSelectedAreaIndex(i);
	}

	public void setSelectedLightIndex(int i)
	{
		getSelectedState().setSelectedLightIndex(i);
	}

	public void setSelectedEntityIndex(int i)
	{
		getSelectedState().setSelectedEntityIndex(i);
	}



	public Door getSelectedDoor()
	{
		if(getSelectedDoorIndex()==-1)return null;
		return getDoor(getSelectedDoorIndex());
	}

	public Area getSelectedArea()
	{
		if(getSelectedAreaIndex()==-1)return null;
		return getArea(getSelectedAreaIndex());
	}

	public Light getSelectedLight()
	{
		if(getSelectedLightIndex()==-1)return null;
		return getLight(getSelectedLightIndex());
	}

	public Entity getSelectedEntity()
	{
		if(getSelectedEntityIndex()==-1)return null;
		return getEntity(getSelectedEntityIndex());
	}


	public void addLight(Light l)
	{
		getSelectedState().addLight(l);
	}

	public void addArea(Area a)
	{
		getSelectedState().addArea(a);
	}
	public void addEntity(Entity e)
	{
		getSelectedState().addEntity(e);
	}
	public void addDoor(Door d)
	{
		if(d.map()!=this)d.map().removeDoor(d);
		if(data.doorDataList().contains(d.getData())==false)data.doorDataList().add(d.getData());
	}

	public void addEvent(Event e)
	{
		data.eventDataList().add(e.getData());
	}


	public void removeDoor(Door d)
	{
		data.doorDataList().remove(d.getData());
	}
	public void removeDoor(int index)
	{
		//just to be safe, let's not delete any connections, and leave that up to the user. instead, we'll highlight any connections in the connection list that are broken.

//		for(int i=0;i<Project.getNumMaps();i++)
//		for(int a=0;a<Project.getMap(i).getNumDoors();a++)
//		if(Project.getMap(i).getDoor(a).destination==getDoor(deleteIndex))Project.getMap(i).getDoor(a).destination=Project.getMap(i).getDoor(a);
//
//		//go through sprites, areas, doors, remove connections
//		for(int i=0;i<getNumDoors();i++)
//		{
//			getDoor(i).connectionList.remove(getDoor(deleteIndex));
//		}

//		//delete it from all map events
//		for(int i=0;i<Project.getNumMaps();i++)
//		{
//			Event event = Project.getEventByID(Project.getMap(i).eventID);
//			if(event!=null)event.deleteDoor(getDoor(deleteIndex));
//		}
//
//
//		//delete it from all door, entity, and area events
//		for(int i=0;i<getNumDoors();i++)
//		{
//			Event event = Project.getEventByID(getDoor(i).eventID);
//			if(event!=null)event.deleteDoor(getDoor(deleteIndex));
//		}


//		for(int k=0;k<getNumStates();k++)
//		{
////				for(int i=0;i<getState(k).getNumAreas();i++){getState(k).getArea(i).connectionList.remove(getDoor(deleteIndex));}
////				for(int i=0;i<getState(k).getNumEntities();i++){getState(k).getEntity(i).connectionList.remove(getDoor(deleteIndex));}
////
////				for(int i=0;i<getState(k).getNumAreas();i++)
////				{
////					Event event = Project.getEventByID(getState(k).getArea(i).eventID);
////					if(event!=null)event.deleteDoor(getDoor(deleteIndex));
////				}
////
////				for(int i=0;i<getState(k).getNumEntities();i++)
////				{
////					Event event = Project.getEventByID(getState(k).getEntity(i).eventID);
////					if(event!=null)event.deleteDoor(getDoor(deleteIndex));
////				}
//
//		}

		data.doorDataList().remove(index);

	}

	public void removeLight(int i)
	{
		getSelectedState().removeLight(i);
	}

	public void removeArea(int n)
	{

		for(int i=0;i<getNumDoors();i++)
		{
			getDoor(i).connectionTYPEIDList().remove(getArea(n).getTYPEIDString());
		}

		getSelectedState().removeArea(n);
	}

	public void removeEntity(int i)
	{
		getSelectedState().removeEntity(i);
	}

	public void removeSelectedState()
	{
		MapState s = getSelectedState();
		data.stateDataList().remove(s.getData());
		setSelectedState(0);
	}

	public void moveLightToState(int lightIndex, int stateIndex)
	{
		Light light = getSelectedState().getLight(lightIndex);

		getSelectedState().removeLight(light);
		getState(stateIndex).addLight(light);
		light.setState(getState(stateIndex));
		light.setNameNoRename(createUniqueLightName(light.name(),-1));
	}

	public void moveAreaToState(int areaIndex, int stateIndex)
	{
		Area area = getSelectedState().getArea(areaIndex);

		if(area.isWarpArea())return;

		getSelectedState().removeArea(area);
		getState(stateIndex).addArea(area);
		area.setState(getState(stateIndex));
		area.setNameNoRename(createUniqueAreaName(area.name(),-1));
		area.connectionTYPEIDList().clear();
	}


	public void moveEntityToState(int entityIndex, int stateIndex)
	{
		Entity entity = getSelectedState().getEntity(entityIndex);

		getSelectedState().removeEntity(entity);
		getState(stateIndex).addEntity(entity);
		entity.setState(getState(stateIndex));
		entity.setNameNoRename(createUniqueEntityName(entity.name(),-1));
		entity.connectionTYPEIDList().clear();
	}



	public void copyLightToState(int lightIndex, int stateIndex)
	{
		Light lightCopy = getSelectedState().getLight(lightIndex).duplicate(this,getState(stateIndex));
		lightCopy.setNameNoRename(createUniqueLightName(lightCopy.name(),-1));
	}

	public void copyAreaToState(int areaIndex, int stateIndex)
	{
		if(getSelectedState().getArea(areaIndex).isWarpArea())return;
		Area areaCopy = getSelectedState().getArea(areaIndex).duplicate(this,getState(stateIndex));
		areaCopy.setNameNoRename(createUniqueAreaName(areaCopy.name(),-1));
		areaCopy.connectionTYPEIDList().clear();
	}


	public void copyEntityToState(int entityIndex, int stateIndex)
	{
		Entity copy = getSelectedState().getEntity(entityIndex).duplicate(this,getState(stateIndex));
		copy.setNameNoRename(createUniqueEntityName(copy.name(),-1));
		copy.connectionTYPEIDList().clear();
	}

	@Override
	public String getShortTypeName()
	{

		return "MAP."+name();
	}

	@Override
	public String getLongTypeName()
	{
		// TODO Auto-generated method stub
		return "MAP."+name();
	}





	public MapData getData(){return data;}


	public int id(){return data.id();}
	public String name(){return data.name();}
	public String mapNote(){return data.mapNote();}

	public int wT(){return data.widthTiles1X();}
	public int hT(){return data.heightTiles1X();}

	public int wP(){return data.widthTiles1X()*8;}
	public int hP(){return data.heightTiles1X()*8;}

	public int maxRandoms(){return data.maxRandoms();}
	public boolean isOutside(){return data.isOutside();}
	public boolean preload(){return data.preload();}

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

	//set


	public void setWidthTiles(int s){data.setWidthTiles1X(s);}
	public void setHeightTiles(int s){data.setHeightTiles1X(s);}

	public void setID(int s){data.setID(s);}
	public void setMapNote(String s){data.setMapNote(s);}

	public void setMaxRandoms(int s){data.setMaxRandoms(s);}
	public void setIsOutside(boolean s){data.setIsOutside(s);}
	public void setPreload(boolean s){data.setPreload(s);}


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

	//===============================================================================================
	public void shiftMap(int dx, int dy)
	{//===============================================================================================
		// Shift tiles
		int w = wT();
		int h = hT();
		
		for(int l = 0; l < MapData.layers; l++) {
			//if(!MapData.isTileLayer(l)) continue; // Shift all layers including collision/etc
			
			int[][] newLayer = new int[w][h];
			
			for(int y = 0; y < h; y++) {
				for(int x = 0; x < w; x++) {
					int newX = x + dx;
					int newY = y + dy;
					
					if(newX >= 0 && newX < w && newY >= 0 && newY < h) {
						newLayer[newX][newY] = layerTileIndex[l][x][y];
					}
				}
			}
			layerTileIndex[l] = newLayer;
		}
		
		// Shift Objects (Doors, Entities, Lights, Areas)
		
		for(int i = 0; i < getNumDoors(); i++) {
			Door d = getDoor(i);
			d.setXPixels(d.xP() + (dx * 8));
			d.setYPixels(d.yP() + (dy * 8));
		}
		
		for(int s = 0; s < getNumStates(); s++) {
			MapState state = getState(s);
			
			for(int i = 0; i < state.getNumEntities(); i++) {
				Entity e = state.getEntity(i);
				e.setXPixels(e.xP() + (dx * 8));
				e.setYPixels(e.yP() + (dy * 8));
			}
			
			for(int i = 0; i < state.getNumLights(); i++) {
				Light l = state.getLight(i);
				l.setXPixels(l.xP() + (dx * 8));
				l.setYPixels(l.yP() + (dy * 8));
			}
			
			for(int i = 0; i < state.getNumAreas(); i++) {
				Area a = state.getArea(i);
				a.setXPixels(a.xP() + (dx * 8));
				a.setYPixels(a.yP() + (dy * 8));
			}
		}
	}


}
