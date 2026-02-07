package com.bobsgame.shared;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Vector;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;

import org.apache.commons.codec.binary.Base64;
import org.apache.commons.codec.binary.StringUtils;

import com.bobsgame.shared.EventData;
import com.bobsgame.shared.DoorData;
import com.bobsgame.shared.MapStateData;
import com.bobsgame.shared.MapData.RenderOrder;
import com.bobsgame.shared.AssetData;
import com.google.gson.Gson;


//=========================================================================================================================
public class MapData extends AssetData
{//=========================================================================================================================


	public static int MAP_GROUND_LAYER = 0;
	public static int MAP_GROUND_DETAIL_LAYER = 1;
	public static int MAP_SHADER_LAYER=2;
	public static int MAP_GROUND_SHADOW_LAYER=3;

	public static int MAP_OBJECT_LAYER=4;
	public static int MAP_OBJECT_DETAIL_LAYER=5;
	public static int MAP_OBJECT_SHADOW_LAYER=6;

	public static int MAP_ENTITY_LAYER = 12;
	public static int MAP_DOOR_LAYER=16;

	//TODO: need a shadow layer here that affects sprite but not overlayer

	public static int MAP_ABOVE_LAYER = 7;
	public static int MAP_ABOVE_DETAIL_LAYER = 8;
	public static int MAP_SPRITE_SHADOW_LAYER=9;

	public static int MAP_CAMERA_BOUNDS_LAYER=10;
	public static int MAP_HIT_LAYER=11;


	public static int MAP_LIGHT_LAYER=13;
	public static int MAP_AREA_LAYER=14;
	public static int MAP_LIGHT_MASK_LAYER=15;


	public static int MAP_ENTITY_LAYER_ABOVE=100;//not a real layer, just used to draw entity layer with priority

	public static int layers = 17;

	//===============================================================================================
	public static boolean isTileLayer(int l)
	{//===============================================================================================
		if(l==MAP_DOOR_LAYER)return false;
		if(l==MAP_ENTITY_LAYER)return false;
		if(l==MAP_ENTITY_LAYER_ABOVE)return false;
		if(l==MAP_AREA_LAYER)return false;
		if(l==MAP_LIGHT_LAYER)return false;

		return true;
	}

	//===============================================================================================
	public static boolean isTransparentLayer(int l)
	{//===============================================================================================
		if(l==MAP_AREA_LAYER)return true;
		if(l==MAP_LIGHT_LAYER)return true;
		if(l==MAP_HIT_LAYER)return true;
		if(l==MAP_SPRITE_SHADOW_LAYER)return true;
		if(l==MAP_GROUND_SHADOW_LAYER)return true;
		if(l==MAP_SHADER_LAYER)return true;
		if(l==MAP_OBJECT_SHADOW_LAYER)return true;
		if(l==MAP_CAMERA_BOUNDS_LAYER)return true;
		if(l==MAP_LIGHT_MASK_LAYER)return true;
		return false;
	}











	//DONE clean up layers in mapAsset and Entity to make more sense in game.render()

	public static enum RenderOrder
	{
		GROUND,
		ABOVE,

		ABOVE_TOP,//over overlayer, underneath lights

		//sprites over top
		//captions
		//overlay under lights
		//stadium screen


		//lights

		//should have birds here?

		SPRITE_DEBUG_OUTLINES,
		SPRITE_DEBUG_INFO,
		OVER_TEXT,
		OVER_GUI,
		CONSOLE
	}

/*
	----------------------MAP
	currentMap.render(RenderOrder.GROUND);//layer 0 1 3s 4 5 6s

	currentMap.renderEntities(RenderOrder.GROUND);
	CaptionManager().render(RenderOrder.GROUND);

	currentMap.render(RenderOrder.ABOVE); //includes above shadows, layer 9 - layers 7,8,9
	currentMap.renderEntities(RenderOrder.ABOVE);
	currentMap.renderEntities(RenderOrder.ABOVE_TOP);//birds? //TODO should have something OVER lights as well!
	CinematicsManager().render(RenderOrder.ABOVE);//screen overlay under lights

	ClientGameEngine().stadiumScreen.render();

	//LIGHTS HERE

	---------------------------ENGINE
	SpriteManager().renderScreenSprites(RenderOrder.ABOVE);

	CaptionManager().render(RenderOrder.ABOVE);

	SpriteManager().renderScreenSprites(RenderOrder.ABOVE_TOP);

	CaptionManager().render(RenderOrder.ABOVE_TOP);

	CinematicsManager().render(RenderOrder.ABOVE_TOP);

	TextManager().render();

	MapManager().renderEntities(RenderOrder.OVER_TEXT);

	SpriteManager().renderScreenSprites(RenderOrder.OVER_TEXT);//screensprites

	CaptionManager().render(RenderOrder.OVER_TEXT);

	MapManager().renderDebug();

	SpriteManager().renderScreenSprites(RenderOrder.OVER_GUI);

	CaptionManager().render(RenderOrder.OVER_GUI);


	---------------GAME ENGINE
	nD
	StatusBar
	GUI


*/

//	public static final int SPRITE_LAYER_DEBUG_INFO = -2;
//	public static final int SPRITE_LAYER_DEBUG_BOXES = -1;
//
//
//	public static final int SPRITE_LAYER_UNDERNEATH_MAP = 0;
//	public static final int MAP_LAYER_GROUND = 0;
//	public static final int SPRITE_LAYER_GROUND = 1;
//	public static final int MAP_LAYER_ABOVE = 1;
//	public static final int SPRITE_LAYER_ABOVE_OVERLAYER = 2;
//	public static final int SPRITE_LAYER_ABOVE_TEXT = 3;





	private String mapNote = "";




	private int widthTiles1X = 40; //1x tile width
	private int heightTiles1X = 30; //1x tile width
//	public int widthPixels1X = 240; //1x pixel width
//	public int heightPixels1X = 160; //1x pixel width
//	public int widthTilesHQ2X = 60; //hq2x tile width
//	public int heightTilesHQ2X = 40; //hq2x tile width
//	public int widthPixelsHQ2X = 480; //hq2x pixel width
//	public int heightPixelsHQ2X = 320; //hq2x pixel width

	private int maxRandoms = 10;
	private boolean isOutside = false;
	private boolean preload = false;

	private String groundLayerMD5 = null;
	private String groundObjectsMD5 = null;
	private String groundShadowMD5 = null;
	private String objectsMD5 = null;
	private String objects2MD5 = null;
	private String objectShadowMD5 = null;
	private String aboveMD5 = null;
	private String above2MD5 = null;
	private String spriteShadowMD5 = null;
	private String groundShaderMD5 = null;
	private String cameraBoundsMD5 = null;
	private String hitBoundsMD5 = null;
	private String lightMaskMD5 = null;
	private String paletteMD5 = null;
	private String tilesMD5 = null;




	//these are ASSET lists only populated with objectDatas to convert into JSON and fill the regular Map lists at runtime with.
	private ArrayList<MapStateData> stateDataList = new ArrayList<MapStateData>();
	//private ArrayList<Integer> eventIDList = new ArrayList<Integer>();
	private ArrayList<EventData> eventDataList = new ArrayList<EventData>();
	private ArrayList<DoorData> doorDataList = new ArrayList<DoorData>();





	//=========================================================================================================================
	public MapData()
	{//=========================================================================================================================

	}

	//=========================================================================================================================
	public MapData(int id, String name, int widthTiles1X, int heightTiles1X)
	{//=========================================================================================================================


		super(id,name);



		this.widthTiles1X = widthTiles1X;
		this.heightTiles1X = heightTiles1X;

//		this.widthPixels1X = widthTiles1X*8; //1x pixel width
//		this.heightPixels1X = heightTiles1X*8; //1x pixel width
//		this.widthTilesHQ2X = widthTiles1X*2; //hq2x tile width
//		this.heightTilesHQ2X = heightTiles1X*2; //hq2x tile width
//		this.widthPixelsHQ2X = widthTiles1X*2*8; //hq2x pixel width
//		this.heightPixelsHQ2X = heightTiles1X*2*8; //hq2x pixel width


	}



//
//	//===============================================================================================
//	public static MapData fromBase64ZippedJSON(String b64)
//	{//===============================================================================================
//
//
//
//
//		String decode64 = Utils.decodeBase64String(b64);
//		String json = Utils.unzipString(decode64);
//
//
//		//Gson gson = new Gson();
//		//MapData data = gson.fromJson(json,MapData.class);
//
//		return fromJSON(json);
//	}
//
//
	//===============================================================================================
	public static MapData fromJSON(String json)
	{//===============================================================================================



		Gson gson = new Gson();
		MapData data = gson.fromJson(json,MapData.class);



//		ObjectMapper mapper = new ObjectMapper();
//		MapData data = null;
//
//		try
//		{
//			data = mapper.readValue(json, MapData.class);
//		}
//		catch(JsonParseException e)
//		{
//			e.printStackTrace();
//		}
//		catch(JsonMappingException e)
//		{
//			e.printStackTrace();
//		}
//		catch(IOException e)
//		{
//			e.printStackTrace();
//		}

		return data;



	}



	//===============================================================================================
	public String toString()
	{//===============================================================================================

		String s = "";

		s = super.toString();



		while(mapNote.contains("`"))
		{
			String front = mapNote.substring(0,mapNote.indexOf("`"));
			String back = mapNote.substring(mapNote.indexOf("`")+1);
			mapNote = front + back;
		}



		s += "mapNote:`"+mapNote+"`,";
		s += "widthTiles1X:`"+widthTiles1X+"`,";
		s += "heightTiles1X:`"+heightTiles1X+"`,";
		s += "maxRandoms:`"+maxRandoms+"`,";
		s += "isOutside:`"+isOutside+"`,";
		s += "preload:`"+preload+"`,";
		s += "groundLayerMD5:`"+groundLayerMD5+"`,";
		s += "groundObjectsMD5:`"+groundObjectsMD5+"`,";
		s += "groundShadowMD5:`"+groundShadowMD5+"`,";
		s += "objectsMD5:`"+objectsMD5+"`,";
		s += "objects2MD5:`"+objects2MD5+"`,";
		s += "objectShadowMD5:`"+objectShadowMD5+"`,";
		s += "aboveMD5:`"+aboveMD5+"`,";
		s += "above2MD5:`"+above2MD5+"`,";
		s += "spriteShadowMD5:`"+spriteShadowMD5+"`,";
		s += "groundShaderMD5:`"+groundShaderMD5+"`,";
		s += "cameraBoundsMD5:`"+cameraBoundsMD5+"`,";
		s += "hitBoundsMD5:`"+hitBoundsMD5+"`,";
		s += "lightMaskMD5:`"+lightMaskMD5+"`,";
		s += "paletteMD5:`"+paletteMD5+"`,";
		s += "tilesMD5:`"+tilesMD5+"`,";


		s += "stateDataList:{";
		for(int i=0;i<stateDataList.size();i++)
		{
			s += stateDataList.get(i).toString();
		}
		s += "},";


//		s += "eventIDList:{";
//		for(int i=0;i<eventIDList.size();i++)
//		{
//			s += ""+eventIDList.get(i)+",";
//		}
//		s += "},";

		//this exports the event data for convenient loading by the client, so it doesnt have to do server lookups for everything
		s += "eventDataList:{";
		for(int i=0;i<eventDataList.size();i++)
		{
			s += eventDataList.get(i).toString();
		}
		s += "},";

		s += "doorDataList:{";
		for(int i=0;i<doorDataList.size();i++)
		{
			s += doorDataList.get(i).toString();
		}
		s += "},";


		return s;
	}




	public String initFromString(String t)
	{
		t = super.initFromString(t);


		t = t.substring(t.indexOf("mapNote:`")+1);
		t = t.substring(t.indexOf("`")+1);
		mapNote = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("widthTiles1X:`")+1);
		t = t.substring(t.indexOf("`")+1);
		widthTiles1X = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("heightTiles1X:`")+1);
		t = t.substring(t.indexOf("`")+1);
		heightTiles1X = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("maxRandoms:`")+1);
		t = t.substring(t.indexOf("`")+1);
		maxRandoms = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("isOutside:`")+1);
		t = t.substring(t.indexOf("`")+1);
		isOutside = Boolean.parseBoolean(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("preload:`")+1);
		t = t.substring(t.indexOf("`")+1);
		preload = Boolean.parseBoolean(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("groundLayerMD5:`")+1);
		t = t.substring(t.indexOf("`")+1);
		groundLayerMD5 = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("groundObjectsMD5:`")+1);
		t = t.substring(t.indexOf("`")+1);
		groundObjectsMD5 = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("groundShadowMD5:`")+1);
		t = t.substring(t.indexOf("`")+1);
		groundShadowMD5 = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("objectsMD5:`")+1);
		t = t.substring(t.indexOf("`")+1);
		objectsMD5 = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("objects2MD5:`")+1);
		t = t.substring(t.indexOf("`")+1);
		objects2MD5 = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("objectShadowMD5:`")+1);
		t = t.substring(t.indexOf("`")+1);
		objectShadowMD5 = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("aboveMD5:`")+1);
		t = t.substring(t.indexOf("`")+1);
		aboveMD5 = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("above2MD5:`")+1);
		t = t.substring(t.indexOf("`")+1);
		above2MD5 = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("spriteShadowMD5:`")+1);
		t = t.substring(t.indexOf("`")+1);
		spriteShadowMD5 = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("groundShaderMD5:`")+1);
		t = t.substring(t.indexOf("`")+1);
		groundShaderMD5 = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("cameraBoundsMD5:`")+1);
		t = t.substring(t.indexOf("`")+1);
		cameraBoundsMD5 = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("hitBoundsMD5:`")+1);
		t = t.substring(t.indexOf("`")+1);
		hitBoundsMD5 = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("lightMaskMD5:`")+1);
		t = t.substring(t.indexOf("`")+1);
		lightMaskMD5 = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("paletteMD5:`")+1);
		t = t.substring(t.indexOf("`")+1);
		paletteMD5 = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("tilesMD5:`")+1);
		t = t.substring(t.indexOf("`")+1);
		tilesMD5 = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("stateDataList:{")+1);
		t = t.substring(t.indexOf("{")+1);
		while(t.startsWith("}")==false)
		{
			MapStateData data = new MapStateData();
			t = data.initFromString(t);
			stateDataList.add(data);
		}
		t = t.substring(t.indexOf("}")+1);
		t = t.substring(t.indexOf(",")+1);

//		if(t.startsWith("eventIDList:"))
//		{
//			t = t.substring(t.indexOf("eventIDList:{")+1);
//			t = t.substring(t.indexOf("{")+1);
//			while(t.startsWith("}")==false)
//			{
//				int id = Integer.parseInt(t.substring(0,t.indexOf(",")));
//				t = t.substring(t.indexOf(",")+1);
//				eventIDList.add(id);
//			}
//			t = t.substring(t.indexOf("}")+1);
//			t = t.substring(t.indexOf(",")+1);
//		}


		t = t.substring(t.indexOf("eventDataList:{")+1);
		t = t.substring(t.indexOf("{")+1);
		while(t.startsWith("}")==false)
		{
			EventData data = new EventData();
			t = data.initFromString(t);
			eventDataList.add(data);
		}
		t = t.substring(t.indexOf("}")+1);
		t = t.substring(t.indexOf(",")+1);


		t = t.substring(t.indexOf("doorDataList:{")+1);
		t = t.substring(t.indexOf("{")+1);
		while(t.startsWith("}")==false)
		{
			DoorData data = new DoorData();
			t = data.initFromString(t);
			doorDataList.add(data);
		}
		t = t.substring(t.indexOf("}")+1);
		t = t.substring(t.indexOf(",")+1);


		return t;


	}



	//===============================================================================================
	public String getTYPEIDString()
	{//===============================================================================================
		return "MAP."+id();
	}



	public int widthTiles1X(){return widthTiles1X;}
	public int heightTiles1X(){return heightTiles1X;}


	public int maxRandoms(){return maxRandoms;}
	public boolean isOutside(){return isOutside;}
	public boolean preload(){return preload;}

	public String mapNote(){return mapNote;}

	public String groundLayerMD5(){return groundLayerMD5;}
	public String groundObjectsMD5(){return groundObjectsMD5;}
	public String groundShadowMD5(){return groundShadowMD5;}
	public String objectsMD5(){return objectsMD5;}
	public String objects2MD5(){return objects2MD5;}
	public String objectShadowMD5(){return objectShadowMD5;}
	public String aboveMD5(){return aboveMD5;}
	public String above2MD5(){return above2MD5;}
	public String spriteShadowMD5(){return spriteShadowMD5;}
	public String groundShaderMD5(){return groundShaderMD5;}
	public String cameraBoundsMD5(){return cameraBoundsMD5;}
	public String hitBoundsMD5(){return hitBoundsMD5;}
	public String lightMaskMD5(){return lightMaskMD5;}
	public String paletteMD5(){return paletteMD5;}
	public String tilesMD5(){return tilesMD5;}


	public int widthPixelsHQ(){return widthTiles1X()*8*2;}
	public int heightPixelsHQ(){return heightTiles1X()*8*2;}





	public ArrayList<MapStateData> stateDataList(){return stateDataList;}
	//public ArrayList<Integer> eventIDList(){return eventIDList;}
	public ArrayList<EventData> eventDataList(){return eventDataList;}
	public ArrayList<DoorData> doorDataList(){return doorDataList;}








	public void setGroundLayerMD5(String s){groundLayerMD5=s;}
	public void setGroundObjectsMD5(String s){groundObjectsMD5=s;}
	public void setGroundShadowMD5(String s){groundShadowMD5=s;}
	public void setObjectsMD5(String s){objectsMD5=s;}
	public void setObjects2MD5(String s){objects2MD5=s;}
	public void setObjectShadowMD5(String s){objectShadowMD5=s;}
	public void setAboveMD5(String s){aboveMD5=s;}
	public void setAbove2MD5(String s){above2MD5=s;}
	public void setSpriteShadowMD5(String s){spriteShadowMD5=s;}
	public void setGroundShaderMD5(String s){groundShaderMD5=s;}
	public void setCameraBoundsMD5(String s){cameraBoundsMD5=s;}
	public void setHitBoundsMD5(String s){hitBoundsMD5=s;}
	public void setLightMaskMD5(String s){lightMaskMD5=s;}
	public void setPaletteMD5(String s){paletteMD5=s;}
	public void setTilesMD5(String s){tilesMD5=s;}



	public void setMapNote(String s){mapNote=s;}

	public void setWidthTiles1X(int s){widthTiles1X=s;}
	public void setHeightTiles1X(int s){heightTiles1X=s;}



	public void setMaxRandoms(int s){maxRandoms=s;}
	public void setIsOutside(boolean s){isOutside=s;}
	public void setPreload(boolean s){preload=s;}


}
