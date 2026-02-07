package com.bobsgame.shared;



import java.io.IOException;
import java.util.ArrayList;

import javax.swing.tree.DefaultMutableTreeNode;


import com.bobsgame.shared.AssetData;
import com.google.gson.Gson;



//=========================================================================================================================
public class GameStringData extends AssetData
{//=========================================================================================================================



	private String text = "";


	//=========================================================================================================================
	public GameStringData()
	{//=========================================================================================================================

	}


	//=========================================================================================================================
	public GameStringData(int id, String name, String text)
	{//=========================================================================================================================

		super(id,name);

		this.text = text;

	}



//	//===============================================================================================
//	public static GameStringData fromBase64ZippedJSON(String b64)
//	{//===============================================================================================
//
//
//
//
//		String decode64 = Utils.decodeBase64String(b64);
//		String json = Utils.unzipString(decode64);
//
//		//Gson gson = new Gson();
//		//GameStringData data = gson.fromJson(json,GameStringData.class);
//
//		return fromJSON(json);
//	}
//
//

	//===============================================================================================
	public static GameStringData fromJSON(String json)
	{//===============================================================================================

		Gson gson = new Gson();
		GameStringData data = gson.fromJson(json,GameStringData.class);


//		ObjectMapper mapper = new ObjectMapper();
//		GameStringData data = null;
//
//		try
//		{
//			data = mapper.readValue(json, GameStringData.class);
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

		while(text.contains("`"))
		{
			String front = text.substring(0,text.indexOf("`"));
			String back = text.substring(text.indexOf("`")+1);
			text = front + back;
		}


		s += "text:`"+text+"`,";

		return s;
	}




	public String initFromString(String t)
	{
		t = super.initFromString(t);


		t = t.substring(t.indexOf("text:`")+1);
		t = t.substring(t.indexOf("`")+1);
		text = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		return t;
	}


	//===============================================================================================
	public String getTYPEIDString()
	{//===============================================================================================
		return "GAMESTRING."+id();
	}


	public String text(){return text;}

	public void setText(String s){text=s;}


}
