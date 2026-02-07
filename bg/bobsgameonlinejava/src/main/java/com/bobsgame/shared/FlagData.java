package com.bobsgame.shared;



import java.io.IOException;
import java.util.ArrayList;

import javax.swing.tree.DefaultMutableTreeNode;


import com.bobsgame.shared.AssetData;
import com.google.gson.Gson;



//=========================================================================================================================
public class FlagData extends AssetData
{//=========================================================================================================================


	//=========================================================================================================================
	public FlagData()
	{//=========================================================================================================================

	}


	//=========================================================================================================================
	public FlagData(int id, String name)
	{//=========================================================================================================================

		super(id,name);

	}


//
//	//===============================================================================================
//	public static FlagData fromBase64ZippedJSON(String b64)
//	{//===============================================================================================
//
//
//
//		String decode64 = Utils.decodeBase64String(b64);
//		String json = Utils.unzipString(decode64);
//
//		//Gson gson = new Gson();
//		//FlagData data = gson.fromJson(json,FlagData.class);
//
//		return fromJSON(json);
//	}
//
//
	//===============================================================================================
	public static FlagData fromJSON(String json)
	{//===============================================================================================


		Gson gson = new Gson();
		FlagData data = gson.fromJson(json,FlagData.class);


//		ObjectMapper mapper = new ObjectMapper();
//		FlagData data = null;
//
//		try
//		{
//			data = mapper.readValue(json, FlagData.class);
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



		return s;
	}




	public String initFromString(String t)
	{
		t = super.initFromString(t);




		return t;
	}




	//===============================================================================================
	public String getTYPEIDString()
	{//===============================================================================================
		return "FLAG."+id();
	}


}
