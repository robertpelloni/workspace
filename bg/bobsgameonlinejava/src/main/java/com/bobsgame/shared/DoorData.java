package com.bobsgame.shared;

import java.io.IOException;
import java.util.ArrayList;

import com.google.gson.Gson;


//=========================================================================================================================
public class DoorData extends EntityData
{//=========================================================================================================================



	private String destinationTYPEID = "";



	private int arrivalXPixels1X=-1;
	private int arrivalYPixels1X=-1;

	private boolean randomNPCSpawnPoint = false;
	private float randomSpawnChance = 1.0f; //will distribute max randoms across spawn points based on chance.
	private boolean randomPointOfInterestOrExit = false;
	private int randomSpawnDelay = 1000;
	private boolean randomSpawnKids = true;
	private boolean randomSpawnAdults = true;
	private boolean randomSpawnMales = true;
	private boolean randomSpawnFemales = true;



	//ONLY USED FOR EXPORT
	private String destinationMapName = "";
	private String destinationDoorName = "";


	//=========================================================================================================================
	public DoorData()
	{//=========================================================================================================================

	}


	//=========================================================================================================================
	public DoorData(int id, String name, String spriteAssetName, int spawnXPixels1X, int spawnYPixels1X, String destinationTYPEID, int arrivalXPixels, int arrivalYPixels, boolean randomNPCSpawnPoint, float randomSpawnChance, boolean randomExitPoint, int randomSpawnDelay, boolean randomSpawnKids, boolean randomSpawnAdults, boolean randomSpawnMales, boolean randomSpawnFemales, EventData eventData, String comment)
	{//=========================================================================================================================



		super(
				id,               //int id,
				name,             //String name,
				spriteAssetName,  //String spriteAssetName,
				spawnXPixels1X,   //int spawnXPixels1X,
				spawnYPixels1X,   //int spawnYPixels1X,
				0,                //int initialFrame,
				false,            //boolean pushable,
				true,             //boolean nonWalkable,
				255,              //int alphaByte,
				1.0f,              //float scale,
				12,
				false,            //boolean aboveTopLayer,
				false,            //boolean aboveWhenEqual,
				false,            //boolean alwaysOnBottom,
				false,            //boolean animateThroughFrames,
				false,            //boolean randomTimeBetweenAnimation,
				0,                //int ticksBetweenFrames,
				0,                //int ticksBetweenAnimation,
				false,            //boolean onlyHereDuringEvent,
				false,            //boolean randomFrames,
				true,            //boolean disableShadow,
				eventData,        //int eventID,
				comment
		);





		this.arrivalXPixels1X = arrivalXPixels;
		this.arrivalYPixels1X = arrivalYPixels;


		this.randomNPCSpawnPoint= randomNPCSpawnPoint;
		this.randomSpawnChance= randomSpawnChance;
		this.randomPointOfInterestOrExit= randomExitPoint; //point of interest
		this.randomSpawnDelay= randomSpawnDelay;
		this.randomSpawnKids= randomSpawnKids;
		this.randomSpawnAdults= randomSpawnAdults;
		this.randomSpawnMales= randomSpawnMales;
		this.randomSpawnFemales= randomSpawnFemales;

		this.destinationTYPEID = destinationTYPEID;




	}


	//=========================================================================================================================
	public DoorData(int id,String name)
	{//=========================================================================================================================
		super(
				id,               //int id,
				name,             //String name,
				"",  //String spriteAssetName,
				0,   //int spawnXPixels1X,
				0,   //int spawnYPixels1X,
				0,                //int initialFrame,
				false,            //boolean pushable,
				true,             //boolean nonWalkable,
				255,              //int alphaByte,
				1.0f,              //float scale,
				12,
				false,            //boolean aboveTopLayer,
				false,            //boolean aboveWhenEqual,
				false,            //boolean alwaysOnBottom,
				false,            //boolean animateThroughFrames,
				false,            //boolean randomTimeBetweenAnimation,
				0,                //int ticksBetweenFrames,
				0,                //int ticksBetweenAnimation,
				false,            //boolean onlyHereDuringEvent,
				false,            //boolean randomFrames,
				true,            //boolean disableShadow,
				null,        //int eventID,
				""
		);
	}





//
//
//	//===============================================================================================
//	public static DoorData fromBase64ZippedJSON(String b64)
//	{//===============================================================================================
//
//
//
//		String decode64 = Utils.decodeBase64String(b64);
//		String json = Utils.unzipString(decode64);
//
//		//Gson gson = new Gson();
//		//DoorData data = gson.fromJson(json,DoorData.class);
//
//
//		return fromJSON(json);
//
//	}
//
//
//
	//===============================================================================================
	public static DoorData fromJSON(String json)
	{//===============================================================================================


		Gson gson = new Gson();
		DoorData data = gson.fromJson(json,DoorData.class);


//		ObjectMapper mapper = new ObjectMapper();
//		DoorData data = null;
//
//		try
//		{
//			data = mapper.readValue(json, DoorData.class);
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
//
//


	//===============================================================================================
	public String toString()
	{//===============================================================================================

		String s = "";

		s = super.toString();




		while(destinationTYPEID.contains("`"))
		{
			String front = destinationTYPEID.substring(0,destinationTYPEID.indexOf("`"));
			String back = destinationTYPEID.substring(destinationTYPEID.indexOf("`")+1);
			destinationTYPEID = front + back;
		}

		while(destinationMapName.contains("`"))
		{
			String front = destinationMapName.substring(0,destinationMapName.indexOf("`"));
			String back = destinationMapName.substring(destinationMapName.indexOf("`")+1);
			destinationMapName = front + back;
		}

		while(destinationDoorName.contains("`"))
		{
			String front = destinationDoorName.substring(0,destinationDoorName.indexOf("`"));
			String back = destinationDoorName.substring(destinationDoorName.indexOf("`")+1);
			destinationDoorName = front + back;
		}

		s += "destinationTYPEID:`"+destinationTYPEID+"`,";
		s += "arrivalXPixels1X:`"+arrivalXPixels1X+"`,";
		s += "arrivalYPixels1X:`"+arrivalYPixels1X+"`,";
		s += "randomNPCSpawnPoint:`"+randomNPCSpawnPoint+"`,";
		s += "randomSpawnChance:`"+randomSpawnChance+"`,";
		s += "randomPointOfInterestOrExit:`"+randomPointOfInterestOrExit+"`,";
		s += "randomSpawnDelay:`"+randomSpawnDelay+"`,";
		s += "randomSpawnKids:`"+randomSpawnKids+"`,";
		s += "randomSpawnAdults:`"+randomSpawnAdults+"`,";
		s += "randomSpawnMales:`"+randomSpawnMales+"`,";
		s += "randomSpawnFemales:`"+randomSpawnFemales+"`,";
		s += "destinationMapName:`"+destinationMapName+"`,";
		s += "destinationDoorName:`"+destinationDoorName+"`,";


		return s;
	}



	public String initFromString(String t)
	{
		t = super.initFromString(t);


		t = t.substring(t.indexOf("destinationTYPEID:`")+1);
		t = t.substring(t.indexOf("`")+1);
		destinationTYPEID = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("arrivalXPixels1X:`")+1);
		t = t.substring(t.indexOf("`")+1);
		arrivalXPixels1X = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("arrivalYPixels1X:`")+1);
		t = t.substring(t.indexOf("`")+1);
		arrivalYPixels1X = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("randomNPCSpawnPoint:`")+1);
		t = t.substring(t.indexOf("`")+1);
		randomNPCSpawnPoint = Boolean.parseBoolean(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("randomSpawnChance:`")+1);
		t = t.substring(t.indexOf("`")+1);
		randomSpawnChance = Float.parseFloat(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("randomPointOfInterestOrExit:`")+1);
		t = t.substring(t.indexOf("`")+1);
		randomPointOfInterestOrExit = Boolean.parseBoolean(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("randomSpawnDelay:`")+1);
		t = t.substring(t.indexOf("`")+1);
		randomSpawnDelay = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("randomSpawnKids:`")+1);
		t = t.substring(t.indexOf("`")+1);
		randomSpawnKids = Boolean.parseBoolean(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("randomSpawnAdults:`")+1);
		t = t.substring(t.indexOf("`")+1);
		randomSpawnAdults = Boolean.parseBoolean(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("randomSpawnMales:`")+1);
		t = t.substring(t.indexOf("`")+1);
		randomSpawnMales = Boolean.parseBoolean(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("randomSpawnFemales:`")+1);
		t = t.substring(t.indexOf("`")+1);
		randomSpawnFemales = Boolean.parseBoolean(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("destinationMapName:`")+1);
		t = t.substring(t.indexOf("`")+1);
		destinationMapName = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("destinationDoorName:`")+1);
		t = t.substring(t.indexOf("`")+1);
		destinationDoorName = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);


		return t;


	}




	//===============================================================================================
	public String getTYPEIDString()
	{//===============================================================================================
		return "DOOR."+id();
	}





	public String destinationTYPEIDString(){return destinationTYPEID;}
	public String destinationMapName(){return destinationMapName;}
	public String destinationDoorName(){return destinationDoorName;}

	public int arrivalXPixels1X(){return arrivalXPixels1X;}
	public int arrivalYPixels1X(){return arrivalYPixels1X;}
	public int arrivalXPixelsHQ(){return arrivalXPixels1X*2;}
	public int arrivalYPixelsHQ(){return arrivalYPixels1X*2;}

	public boolean randomNPCSpawnPoint(){return randomNPCSpawnPoint;}
	public float randomSpawnChance(){return randomSpawnChance;}
	public boolean randomPointOfInterestOrExit(){return randomPointOfInterestOrExit;}
	public int randomSpawnDelay(){return randomSpawnDelay;}
	public boolean randomSpawnKids(){return randomSpawnKids;}
	public boolean randomSpawnAdults(){return randomSpawnAdults;}
	public boolean randomSpawnMales(){return randomSpawnMales;}
	public boolean randomSpawnFemales(){return randomSpawnFemales;}









	public void setDestinationTYPEIDString(String s){destinationTYPEID=s;}
	public void setDestinationMapName(String s){destinationMapName=s;}
	public void setDestinationDoorName(String s){destinationDoorName=s;}

	public void setRandomPointOfInterestOrExit(boolean s){randomPointOfInterestOrExit = s;}
	public void setRandomNPCSpawnPoint(boolean s){randomNPCSpawnPoint = s;}
	public void setRandomSpawnChance(float s){randomSpawnChance = s;}
	public void setRandomSpawnDelay(int s){randomSpawnDelay = s;}
	public void setRandomSpawnKids(boolean s){randomSpawnKids = s;}
	public void setRandomSpawnAdults(boolean s){randomSpawnAdults = s;}
	public void setRandomSpawnMales(boolean s){randomSpawnMales = s;}
	public void setRandomSpawnFemales(boolean s){randomSpawnFemales = s;}


	public void setArrivalXPixels1X(int s){arrivalXPixels1X=s;}
	public void setArrivalYPixels1X(int s){arrivalYPixels1X=s;}



}
