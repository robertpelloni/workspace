package com.bobsgame.shared;

import java.io.IOException;

import com.bobsgame.shared.MapData.RenderOrder;
import com.google.gson.Gson;


//=========================================================================================================================
public class LightData extends EntityData
{//=========================================================================================================================


	private int widthPixels1X = 2;
	private int heightPixels1X = 2;
	private int redColorByte=0;
	private int greenColorByte=0;
	private int blueColorByte=0;
	private int alphaColorByte=0;
	private int radiusPixels1X = 2;
	private float blendFalloff = 2.0f;
	private float decayExponent = 1.0f;
	private int focusRadius1X = 0;
	private boolean isDayLight = true;
	private boolean isNightLight = false;
	private boolean flickers = false;
	private boolean changesColor = false;
	private boolean toggleable = false;
	private int toggleXPixels1X = -1;
	private int toggleYPixels1X = -1;
	private int flickerOnTicks = 0;
	private int flickerOffTicks = 0;
	private boolean flickerRandomUpToOnTicks = false;
	private boolean flickerRandomUpToOffTicks = false;


	//=========================================================================================================================
	public LightData()
	{//=========================================================================================================================

	}

	//=========================================================================================================================
	public LightData(int id, String mapName, String stateName, String name, int spawnXPixels1X, int spawnYPixels1X, int widthPixels1X, int heightPixels1X, int redColorByte, int greenColorByte, int blueColorByte, int alphaColorByte, int radiusPixels1X, float blendFalloff, float decayExponent, int focusRadius1X, boolean isDayLight, boolean isNightLight, boolean flickers,	boolean changesColor,	boolean toggleable,	int toggleXPixels1X,	int toggleYPixels1X,	int flickerOnTicks,	int flickerOffTicks,	boolean flickerRandomUpToOnTicks,	boolean flickerRandomUpToOffTicks)
	{//=========================================================================================================================



		super(
				id,
				name,
				"", //spriteAssetName
				spawnXPixels1X,
				spawnYPixels1X,
				0,
				false,
				false,
				255,
				1.0f,
				12,
				false,
				false,
				false,
				false,
				false,
				0,
				0,
				false,
				false,
				true,
				null,
				""
			);



		this.widthPixels1X = widthPixels1X;
		this.heightPixels1X = heightPixels1X;

		this.redColorByte = redColorByte;
		this.greenColorByte = greenColorByte;
		this.blueColorByte = blueColorByte;
		this.alphaColorByte = alphaColorByte;

		this.radiusPixels1X = radiusPixels1X;
		this.blendFalloff = blendFalloff;
		this.decayExponent = decayExponent;
		this.focusRadius1X = focusRadius1X;
		this.isDayLight = isDayLight;
		this.isNightLight = isNightLight;


		this.flickers = flickers;
		this.changesColor = changesColor;
		this.toggleable = toggleable;
		this.toggleXPixels1X = toggleXPixels1X;
		this.toggleYPixels1X = toggleYPixels1X;
		this.flickerOnTicks = flickerOnTicks;
		this.flickerOffTicks = flickerOffTicks;
		this.flickerRandomUpToOnTicks = flickerRandomUpToOnTicks;
		this.flickerRandomUpToOffTicks = flickerRandomUpToOffTicks;





	}

	//=========================================================================================================================
	public LightData(int id,String name)
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

//	//===============================================================================================
//	public static LightData fromBase64ZippedJSON(String b64)
//	{//===============================================================================================
//
//
//
//		String decode64 = Utils.decodeBase64String(b64);
//		String json = Utils.unzipString(decode64);
//
//		//Gson gson = new Gson();
//		//LightData data = gson.fromJson(json,LightData.class);
//
//
//		return fromJSON(json);
//
//
//	}

	//===============================================================================================
	public static LightData fromJSON(String json)
	{//===============================================================================================


		Gson gson = new Gson();
		LightData data = gson.fromJson(json,LightData.class);


//		ObjectMapper mapper = new ObjectMapper();
//		LightData data = null;
//
//		try
//		{
//			data = mapper.readValue(json, LightData.class);
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


		s += "widthPixels1X:`"+widthPixels1X+"`,";
		s += "heightPixels1X:`"+heightPixels1X+"`,";
		s += "redColorByte:`"+redColorByte+"`,";
		s += "greenColorByte:`"+greenColorByte+"`,";
		s += "blueColorByte:`"+blueColorByte+"`,";
		s += "alphaColorByte:`"+alphaColorByte+"`,";
		s += "radiusPixels1X:`"+radiusPixels1X+"`,";
		s += "blendFalloff:`"+blendFalloff+"`,";
		s += "decayExponent:`"+decayExponent+"`,";
		s += "focusRadius1X:`"+focusRadius1X+"`,";
		s += "isDayLight:`"+isDayLight+"`,";
		s += "isNightLight:`"+isNightLight+"`,";
		s += "flickers:`"+flickers+"`,";
		s += "changesColor:`"+changesColor+"`,";
		s += "toggleable:`"+toggleable+"`,";
		s += "toggleXPixels1X:`"+toggleXPixels1X+"`,";
		s += "toggleYPixels1X:`"+toggleYPixels1X+"`,";
		s += "flickerOnTicks:`"+flickerOnTicks+"`,";
		s += "flickerOffTicks:`"+flickerOffTicks+"`,";
		s += "flickerRandomUpToOnTicks:`"+flickerRandomUpToOnTicks+"`,";
		s += "flickerRandomUpToOffTicks:`"+flickerRandomUpToOffTicks+"`,";


		return s;
	}




	public String initFromString(String t)
	{
		t = super.initFromString(t);



		t = t.substring(t.indexOf("widthPixels1X:`")+1);
		t = t.substring(t.indexOf("`")+1);
		widthPixels1X = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("heightPixels1X:`")+1);
		t = t.substring(t.indexOf("`")+1);
		heightPixels1X = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("redColorByte:`")+1);
		t = t.substring(t.indexOf("`")+1);
		redColorByte = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("greenColorByte:`")+1);
		t = t.substring(t.indexOf("`")+1);
		greenColorByte = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("blueColorByte:`")+1);
		t = t.substring(t.indexOf("`")+1);
		blueColorByte = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("alphaColorByte:`")+1);
		t = t.substring(t.indexOf("`")+1);
		alphaColorByte = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("radiusPixels1X:`")+1);
		t = t.substring(t.indexOf("`")+1);
		radiusPixels1X = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("blendFalloff:`")+1);
		t = t.substring(t.indexOf("`")+1);
		blendFalloff = Float.parseFloat(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("decayExponent:`")+1);
		t = t.substring(t.indexOf("`")+1);
		decayExponent = Float.parseFloat(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("focusRadius1X:`")+1);
		t = t.substring(t.indexOf("`")+1);
		focusRadius1X = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("isDayLight:`")+1);
		t = t.substring(t.indexOf("`")+1);
		isDayLight = Boolean.parseBoolean(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("isNightLight:`")+1);
		t = t.substring(t.indexOf("`")+1);
		isNightLight = Boolean.parseBoolean(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("flickers:`")+1);
		t = t.substring(t.indexOf("`")+1);
		flickers = Boolean.parseBoolean(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("changesColor:`")+1);
		t = t.substring(t.indexOf("`")+1);
		changesColor = Boolean.parseBoolean(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("toggleable:`")+1);
		t = t.substring(t.indexOf("`")+1);
		toggleable = Boolean.parseBoolean(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("toggleXPixels1X:`")+1);
		t = t.substring(t.indexOf("`")+1);
		toggleXPixels1X = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("toggleYPixels1X:`")+1);
		t = t.substring(t.indexOf("`")+1);
		toggleYPixels1X = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("flickerOnTicks:`")+1);
		t = t.substring(t.indexOf("`")+1);
		flickerOnTicks = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("flickerOffTicks:`")+1);
		t = t.substring(t.indexOf("`")+1);
		flickerOffTicks = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("flickerRandomUpToOnTicks:`")+1);
		t = t.substring(t.indexOf("`")+1);
		flickerRandomUpToOnTicks = Boolean.parseBoolean(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("flickerRandomUpToOffTicks:`")+1);
		t = t.substring(t.indexOf("`")+1);
		flickerRandomUpToOffTicks = Boolean.parseBoolean(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);



		return t;


	}






	//===============================================================================================
	public String getTYPEIDString()
	{//===============================================================================================
		return "LIGHT."+id();
	}


	public int widthPixels1X(){return widthPixels1X;}
	public int heightPixels1X(){return heightPixels1X;}
	public int widthPixelsHQ(){return widthPixels1X*2;}
	public int heightPixelsHQ(){return heightPixels1X*2;}

	public int radiusPixels1X(){return radiusPixels1X;}
	public int radiusPixelsHQ(){return radiusPixels1X*2;}

	public int focusRadiusPixels1X(){return focusRadius1X;}
	public int focusRadiusPixelsHQ(){return focusRadius1X*2;}


	public int toggleXPixels1X(){return toggleXPixels1X;}
	public int toggleYPixels1X(){return toggleYPixels1X;}
	public int toggleXPixelsHQ(){return toggleXPixels1X*2;}
	public int toggleYPixelsHQ(){return toggleYPixels1X*2;}

	public int redColorByte(){return redColorByte;}
	public int greenColorByte(){return greenColorByte;}
	public int blueColorByte(){return blueColorByte;}
	public int alphaColorByte(){return alphaColorByte;}

	public int r(){return redColorByte;}
	public int g(){return greenColorByte;}
	public int b(){return blueColorByte;}
	public int a(){return alphaColorByte;}



	public float blendFalloff(){return blendFalloff;}
	public float decayExponent(){return decayExponent;}
	public boolean isDayLight(){return isDayLight;}
	public boolean isNightLight(){return isNightLight;}
	public boolean flickers(){return flickers;}
	public boolean changesColor(){return changesColor;}
	public boolean toggleable(){return toggleable;}
	public int flickerOnTicks(){return flickerOnTicks;}
	public int flickerOffTicks(){return flickerOffTicks;}
	public boolean flickerRandomUpToOnTicks(){return flickerRandomUpToOnTicks;}
	public boolean flickerRandomUpToOffTicks(){return flickerRandomUpToOffTicks;}









	//set

	public void setWidthPixels1X(int s){widthPixels1X = s;}
	public void setHeightPixels1X(int s){heightPixels1X = s;}

	public void setRadiusPixels1X(int s){radiusPixels1X = s;}

	public void setFocusRadiusPixels1X(int s){focusRadius1X = s;}

	public void setToggleXPixels1X(int s){toggleXPixels1X = s;}
	public void setToggleYPixels1X(int s){toggleYPixels1X = s;}

	public void setRedColorByte(int s){redColorByte = s;}
	public void setGreenColorByte(int s){greenColorByte = s;}
	public void setBlueColorByte(int s){blueColorByte = s;}
	public void setAlphaColorByte(int s){alphaColorByte = s;}

	public void setBlendFalloff(float s){blendFalloff = s;}
	public void setDecayExponent(float s){decayExponent = s;}
	public void setIsDayLight(boolean s){isDayLight = s;}
	public void setIsNightLight(boolean s){isNightLight = s;}
	public void setFlickers(boolean s){flickers = s;}
	public void setChangesColor(boolean s){changesColor = s;}
	public void setToggleable(boolean s){toggleable = s;}
	public void setFlickerOnTicks(int s){flickerOnTicks = s;}
	public void setFlickerOffTicks(int s){flickerOffTicks = s;}
	public void setFlickerRandomUpToOnTicks(boolean s){flickerRandomUpToOnTicks = s;}
	public void setFlickerRandomUpToOffTicks(boolean s){flickerRandomUpToOffTicks = s;}








}
