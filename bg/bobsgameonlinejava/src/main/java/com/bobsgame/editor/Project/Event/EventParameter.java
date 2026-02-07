package com.bobsgame.editor.Project.Event;


import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Map.Area;
import com.bobsgame.editor.Project.Map.Door;
import com.bobsgame.editor.Project.Map.Entity;
import com.bobsgame.editor.Project.Map.Light;
import com.bobsgame.editor.Project.Map.Map;
import com.bobsgame.editor.Project.Sprite.Sprite;




//===============================================================================================
public class EventParameter
{//===============================================================================================



	public GameObject object = null;

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
	public static int TYPE_DIALOGUE	 	 = 11;
//	public static int TYPE_EVENT		 = 12;
	public static int TYPE_GAMESTRING		 = 13;
//	public static int TYPE_STATE		 = 14;
//	public static int TYPE_SKILL		 = ;

	public static int TYPE_INT			 = 15;
	public static int TYPE_FLOAT		 = 16;
	public static int TYPE_STRING		 = 17;
	public static int TYPE_BOOL		 	= 18;

	public static int TYPE_THIS		 	= 19;
	public static int TYPE_PLAYER		 	= 20;

	public static int TYPE_ERROR = 99;



	int i=-1;
	float f=-1.0f;
	boolean b = false;

	String typeString = "";

	String s = "";
	//===============================================================================================
	public EventParameter(String typeString,GameObject object)
	{//===============================================================================================
		this.typeString = typeString;
		this.object = object;

//		if(object.getClass().equals(Door.class))type=TYPE_DOOR;
//		if(object.getClass().equals(Area.class))type=TYPE_AREA;
//		if(object.getClass().equals(Light.class))type=TYPE_LIGHT;
//		if(object.getClass().equals(Entity.class))type=TYPE_ENTITY;
//		if(object.getClass().equals(Map.class))type=TYPE_MAP;
//		if(object.getClass().equals(Sprite.class))type=TYPE_SPRITE;
//		if(object.getClass().equals(Event.class))type=TYPE_EVENT;



		//could also check typestring for starting with DIALOGUE or GAMESTRING
		if(object.getClass().equals(Dialogue.class))type=TYPE_DIALOGUE;
		if(object.getClass().equals(GameString.class))type=TYPE_GAMESTRING;

	}



	//===============================================================================================
	public EventParameter(String typeString,String s)
	{//===============================================================================================
		this.typeString = typeString;

		this.s=s;

		boolean error=false;

		if(typeString.startsWith("BOOL"))
		{
			type=TYPE_BOOL;
			this.b = Boolean.parseBoolean(s);
		}
		else
		if(typeString.startsWith("INT"))
		{
			type=TYPE_INT;
			try{this.i=Integer.parseInt(s);}catch(NumberFormatException e){error=true;}
		}
		else
		if(typeString.startsWith("FLOAT"))
		{
			type=TYPE_FLOAT;
			try{this.f=Float.parseFloat(s);}catch(NumberFormatException e){error=true;}
		}
		else
		if(typeString.startsWith("STRING") || typeString.startsWith("GAMESTRING"))
		{
			type=TYPE_GAMESTRING;

			GameString g = null;
			for(int i=0;i<Project.gameStringList.size();i++)
			{
				if(Project.gameStringList.get(i).text().equals(s))g = Project.gameStringList.get(i);
			}
			if(g==null)g = new GameString("",s);
			object = g;
		}
		else
		if(s.equals("THIS"))
		{
			type=TYPE_THIS;

		}
		else
		if(s.equals("PLAYER"))
		{
			type=TYPE_PLAYER;

		}
		else
		{
			error=true;
		}


		if(error)
		{
			type=TYPE_ERROR;
		}



	}







	//===============================================================================================
	public String toString()
	{//===============================================================================================


		System.err.println("Should never call toString in EventParameter");


		return "ERROR";
	}




	//===============================================================================================
	public String getIDString()
	{//===============================================================================================
		if(type==TYPE_ERROR)
		{
			System.err.println("Error in Event Parameter: typeName:"+typeString+" String:"+s);
			return "ERROR."+s;
		}


		if(type==TYPE_INT)return "INT."+i;
		if(type==TYPE_FLOAT)return "FLOAT."+f;
		if(type==TYPE_BOOL)return "BOOL."+b;

		if(type==TYPE_THIS)return "THIS";
		if(type==TYPE_PLAYER)return "PLAYER";

		if(object!=null)return object.getTYPEIDString();

		System.err.println("Error in Event Parameter: typeName:"+typeString+" String:"+s);
		return "ERROR"+s;
	}


	//===============================================================================================
	public String getDisplayName()
	{//===============================================================================================
		if(type==TYPE_ERROR)return "ERROR."+typeString+"."+s;
		if(type==TYPE_INT)return "INT."+i;
		if(type==TYPE_FLOAT)return "FLOAT."+f;
		if(type==TYPE_BOOL)return "BOOL."+b;

		if(type==TYPE_GAMESTRING)return "\""+((GameString)object).text().substring(0,Math.min(20,((GameString)object).text().length()))+"\"";
		if(type==TYPE_DIALOGUE)return "\""+((Dialogue)object).text().substring(0,Math.min(20,((Dialogue)object).text().length()))+"\"";

		if(type==TYPE_THIS)return "THIS";
		if(type==TYPE_PLAYER)return "PLAYER";

		if(object!=null)return object.getShortTypeName();


		return "ERROR."+typeString+"."+s;
	}


	//===============================================================================================
	public static EventParameter parseParameterFromIDString(String parameterName)
	{//===============================================================================================

		//parameterName is always OBJECT.id



		if(parameterName.startsWith("BOOL."))
		{
			return new EventParameter("BOOL",parameterName.substring(parameterName.indexOf(".")+1));
		}
		else
		if(parameterName.startsWith("INT."))
		{
			return new EventParameter("INT",parameterName.substring(parameterName.indexOf(".")+1));
		}
		else
		if(parameterName.startsWith("FLOAT."))
		{
			return new EventParameter("FLOAT",parameterName.substring(parameterName.indexOf(".")+1));
		}
		else
		if(parameterName.startsWith("STRING."))
		{
			return new EventParameter("STRING",parameterName.substring(parameterName.indexOf(".")+1));
		}





		if(parameterName.equals("PLAYER"))
		{

			return new EventParameter(parameterName,parameterName);
		}

		if(parameterName.equals("THIS"))
		{

			return new EventParameter(parameterName,parameterName);
		}





		//if we made it here, it's a map object.
		GameObject o = Project.getMapObjectByTYPEIDName(parameterName);

		if(o==null)
		{
			System.err.println("Could not find MapObject: "+parameterName+" when parsing event string.");
			return new EventParameter("ERROR",parameterName);
		}
		else
		{

			String newTypeString = parameterName.substring(parameterName.indexOf("."));

			return new EventParameter(newTypeString,o);
		}



	}



}
