package com.bobsgame.client.engine.event;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.entity.Entity;



//===============================================================================================
public class EventParameter extends EnginePart
{//===============================================================================================

	public static Logger log = (Logger) LoggerFactory.getLogger(EventParameter.class);

	public Object object = null;

	public int type = -1;

//	public static int TYPE_MAP			 = 0;
//	public static int TYPE_SPRITE		 = 1;
//	public static int TYPE_ENTITY		 = 2;
//	public static int TYPE_LIGHT		 = 3;
//	public static int TYPE_DOOR			 = 4;
//	public static int TYPE_AREA			 = 5;
//	public static int TYPE_ITEM			 = 6;
//	public static int TYPE_GAME			 = 7;
//	public static int TYPE_FLAG			 = 8;
//	public static int TYPE_SOUND	 	 = 9;
//	public static int TYPE_MUSIC		 = 10;
	//public static int TYPE_DIALOGUE	 	 = 11;
//	public static int TYPE_EVENT		 = 12;
	//public static int TYPE_GAMESTRING		 = 13;
//	public static int TYPE_STATE		 = 14;
//	public static int TYPE_SKILL		 = ;

//	public static int TYPE_INT			 = 15;
//	public static int TYPE_FLOAT		 = 16;
//	public static int TYPE_STRING		 = 17;
//	public static int TYPE_BOOL		 	= 18;
//	public static int TYPE_THIS		 	= 19;
//	public static int TYPE_PLAYER		 	= 20;
//
//	public static int TYPE_ERROR = 99;



	int i=-1;
	float f=-1.0f;
	boolean b = false;

	String parameterString = "";

	//===============================================================================================
	public EventParameter(Engine g, String parameterString)
	{//===============================================================================================

		super(g);
		this.parameterString = parameterString;

	}



	//===============================================================================================
	public void parsePrimitive(String typeString,String primitiveValueString)
	{//===============================================================================================

		if(typeString.startsWith("BOOL"))
		{
			//type=TYPE_BOOL;
			this.b = Boolean.parseBoolean(primitiveValueString);
		}
		else
		if(typeString.startsWith("INT"))
		{
			//type=TYPE_INT;
			try{this.i=Integer.parseInt(primitiveValueString);}catch(NumberFormatException e){e.printStackTrace();}
		}
		else
		if(typeString.startsWith("FLOAT"))
		{
			//type=TYPE_FLOAT;
			try{this.f=Float.parseFloat(primitiveValueString);}catch(NumberFormatException e){e.printStackTrace();}
		}

	}


	//===============================================================================================
	public void updateParameterVariablesFromString(Event event)
	{//===============================================================================================

		//parameterName is always OBJECT.id



		if(parameterString.startsWith("BOOL."))
		{
			parsePrimitive("BOOL",parameterString.substring(parameterString.indexOf(".")+1));
		}
		else
		if(parameterString.startsWith("INT."))
		{
			parsePrimitive("INT",parameterString.substring(parameterString.indexOf(".")+1));
		}
		else
		if(parameterString.startsWith("FLOAT."))
		{
			parsePrimitive("FLOAT",parameterString.substring(parameterString.indexOf(".")+1));
		}
		else
		if(parameterString.startsWith("STRING."))
		{
			parsePrimitive("STRING",parameterString.substring(parameterString.indexOf(".")+1));
		}
		else
		if(parameterString.equals("PLAYER"))
		{
			this.object = Player();
		}
		else
		if(parameterString.equals("THIS"))
		{
			Object o = null;

			if(event.door!=null)o = event.door;
			if(event.entity!=null)o = event.entity;

			this.object = o;

		}
		else
		{
			//if we made it here, it's a map object.
			Object o = Engine().getGameObjectByTYPEIDName(parameterString);

			if(o==null)
			{
				log.error("Could not find GameObject: "+parameterString+" when parsing Event Parameter.");
			}
			else
			{
				//String newTypeString = parameterString.substring(parameterString.indexOf("."));

				this.object = o;
			}
		}

	}






	//===============================================================================================
	public String toString()
	{//===============================================================================================


		log.error("Should never call toString in EventParameter");


		return null;
	}




//	//===============================================================================================
//	public String getIDString()
//	{//===============================================================================================
//		if(type==TYPE_ERROR)
//		{
//			log.error("Error in Event Parameter: typeName:"+typeString+" String:"+s);
//			return "ERROR."+s;
//		}
//
//
//		if(type==TYPE_INT)return "INT."+i;
//		if(type==TYPE_FLOAT)return "FLOAT."+f;
//		if(type==TYPE_BOOL)return "BOOL."+b;
//
//		if(object!=null)return object.getIDString();
//
//		log.error("Error in Event Parameter: typeName:"+typeString+" String:"+s);
//		return "ERROR"+s;
//	}


//	//===============================================================================================
//	public String getDisplayName()
//	{//===============================================================================================
//		if(type==TYPE_ERROR)return "ERROR."+typeString+"."+s;
//		if(type==TYPE_INT)return "INT."+i;
//		if(type==TYPE_FLOAT)return "FLOAT."+f;
//		if(type==TYPE_BOOL)return "BOOL."+b;
//
//		if(type==TYPE_CAPTION)return "\""+((GameString)object).text.substring(0,Math.min(20,((GameString)object).text.length()))+"\"";
//		if(type==TYPE_DIALOGUE)return "\""+((Dialogue)object).text.substring(0,Math.min(20,((Dialogue)object).text.length()))+"\"";
//
//		if(object!=null)return object.getShortTypeName();
//
//
//		return "ERROR."+typeString+"."+s;
//	}





}
