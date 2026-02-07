package com.bobsgame.shared;



import java.io.IOException;
import java.util.ArrayList;

import javax.swing.tree.DefaultMutableTreeNode;


import com.bobsgame.shared.AssetData;
import com.google.gson.Gson;



//=========================================================================================================================
public class SoundData extends AssetData
{//=========================================================================================================================


	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------
	//
	//
	//
	//	WARNING! EDITING THESE NAMES WILL BREAK JSON DECODING
	//
	//
	//
	//
	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------

	private String fileName = "";
	private String fullFilePath = "";


	private String md5Name = "";//for use in client



	//=========================================================================================================================
	public SoundData()
	{//=========================================================================================================================

	}

	//=========================================================================================================================
	public SoundData(int id, String name, String filename)
	{//=========================================================================================================================

		super(id,name);


		this.fileName = filename;

	}


//
//	//===============================================================================================
//	public static SoundData fromBase64ZippedJSON(String b64)
//	{//===============================================================================================
//
//		String decode64 = Utils.decodeBase64String(b64);
//		String json = Utils.unzipString(decode64);
//
//		//Gson gson = new Gson();
//		//SoundData data = gson.fromJson(json,SoundData.class);
//
//
//		return fromJSON(json);
//	}
//

	//===============================================================================================
	public static SoundData fromJSON(String json)
	{//===============================================================================================



		Gson gson = new Gson();
		SoundData data = gson.fromJson(json,SoundData.class);


//		ObjectMapper mapper = new ObjectMapper();
//		SoundData data = null;
//
//		try
//		{
//			data = mapper.readValue(json, SoundData.class);
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




		s += "fileName:`"+fileName+"`,";
		s += "fullFilePath:`"+fullFilePath+"`,";
		s += "md5Name:`"+md5Name+"`,";



		return s;
	}




	public String initFromString(String t)
	{
		t = super.initFromString(t);


		t = t.substring(t.indexOf("fileName:`")+1);
		t = t.substring(t.indexOf("`")+1);
		fileName = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("fullFilePath:`")+1);
		t = t.substring(t.indexOf("`")+1);
		fullFilePath = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("md5Name:`")+1);
		t = t.substring(t.indexOf("`")+1);
		md5Name = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);





		return t;


	}



	//===============================================================================================
	public String getTYPEIDString()
	{//===============================================================================================
		return "SOUND."+id();
	}

	public String fileName(){return fileName;}
	public String fullFilePath(){return fullFilePath;}
	public String md5Name(){return md5Name;}


	public void setFileName(String s){fileName = s;}
	public void setFullFilePath(String s){fullFilePath = s;}
	public void setMD5Name(String s){md5Name = s;}

}
