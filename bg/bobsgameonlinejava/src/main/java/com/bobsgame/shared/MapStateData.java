package com.bobsgame.shared;

import java.io.IOException;
import java.util.Hashtable;
import java.util.ArrayList;

import java.util.Vector;
import java.util.concurrent.ConcurrentHashMap;



import com.bobsgame.shared.AssetData;
import com.google.gson.Gson;



//=========================================================================================================================
public class MapStateData extends AssetData
{//=========================================================================================================================

	private int mapID = -1;

	private ArrayList<LightData> lightDataList = new ArrayList<LightData>();

	private ArrayList<EntityData> entityDataList = new ArrayList<EntityData>();

	//public ArrayList<EntityData> characterDataList = new ArrayList<EntityData>();

	private ArrayList<AreaData> areaDataList = new ArrayList<AreaData>();






	//=========================================================================================================================
	public MapStateData()
	{//=========================================================================================================================

	}


	//===============================================================================================
	public MapStateData(int id, String name)
	{//===============================================================================================
		super(id,name);
	}


//	//===============================================================================================
//	public static MapStateData fromBase64ZippedJSON(String b64)
//	{//===============================================================================================
//
//
//
//		String decode64 = Utils.decodeBase64String(b64);
//		String json = Utils.unzipString(decode64);
//
//		//Gson gson = new Gson();
//		//MapStateData data = gson.fromJson(json,MapStateData.class);
//
//
//		return fromJSON(json);
//	}
//
//

	//===============================================================================================
	public static MapStateData fromJSON(String json)
	{//===============================================================================================



		Gson gson = new Gson();
		MapStateData data = gson.fromJson(json,MapStateData.class);


//		ObjectMapper mapper = new ObjectMapper();
//		MapStateData data = null;
//
//		try
//		{
//			data = mapper.readValue(json, MapStateData.class);
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




		s += "mapID:`"+mapID+"`,";

		s += "lightDataList:{";
		for(int i=0;i<lightDataList.size();i++)
		{
			s += lightDataList.get(i).toString();
		}
		s += "},";

		s += "entityDataList:{";
		for(int i=0;i<entityDataList.size();i++)
		{
			s += entityDataList.get(i).toString();
		}
		s += "},";

		s += "areaDataList:{";
		for(int i=0;i<areaDataList.size();i++)
		{
			s += areaDataList.get(i).toString();
		}
		s += "},";

		return s;
	}



	public String initFromString(String t)
	{
		t = super.initFromString(t);


		t = t.substring(t.indexOf("mapID:`")+1);
		t = t.substring(t.indexOf("`")+1);
		mapID = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);



		t = t.substring(t.indexOf("lightDataList:{")+1);
		t = t.substring(t.indexOf("{")+1);
		while(t.startsWith("}")==false)
		{

			LightData data = new LightData();
			t = data.initFromString(t);
			lightDataList.add(data);
		}
		t = t.substring(t.indexOf("}")+1);
		t = t.substring(t.indexOf(",")+1);


		t = t.substring(t.indexOf("entityDataList:{")+1);
		t = t.substring(t.indexOf("{")+1);
		while(t.startsWith("}")==false)
		{
			EntityData data = new EntityData();
			t = data.initFromString(t);
			entityDataList.add(data);

		}
		t = t.substring(t.indexOf("}")+1);
		t = t.substring(t.indexOf(",")+1);


		t = t.substring(t.indexOf("areaDataList:{")+1);
		t = t.substring(t.indexOf("{")+1);
		while(t.startsWith("}")==false)
		{
			AreaData data = new AreaData();
			t = data.initFromString(t);
			areaDataList.add(data);

		}
		t = t.substring(t.indexOf("}")+1);
		t = t.substring(t.indexOf(",")+1);


		return t;


	}




	//===============================================================================================
	public String getTYPEIDString()
	{//===============================================================================================
		return "STATE."+id();
	}

	public ArrayList<LightData> lightDataList(){return lightDataList;}
	public ArrayList<EntityData> entityDataList(){return entityDataList;}
	public ArrayList<AreaData> areaDataList(){return areaDataList;}


	public int mapID(){return mapID;}

	public void setMapID(int s){mapID=s;}


}
