package com.bobsgame.shared;



import java.io.IOException;
import java.util.ArrayList;

import javax.swing.tree.DefaultMutableTreeNode;


import com.bobsgame.shared.AssetData;
import com.google.gson.Gson;



//=========================================================================================================================
public class SkillData extends AssetData
{//=========================================================================================================================





	//=========================================================================================================================
	public SkillData()
	{//=========================================================================================================================

	}



	//=========================================================================================================================
	public SkillData(int id, String name)
	{//=========================================================================================================================

		super(id,name);

	}

//
//
//	//===============================================================================================
//	public static SkillData fromBase64ZippedJSON(String b64)
//	{//===============================================================================================
//
//		String decode64 = Utils.decodeBase64String(b64);
//		String json = Utils.unzipString(decode64);
//
//		//Gson gson = new Gson();
//		//SkillData data = gson.fromJson(json,SkillData.class);
//
//
//
//		return fromJSON(json);
//	}
//


	//===============================================================================================
	public static SkillData fromJSON(String json)
	{//===============================================================================================


		Gson gson = new Gson();
		SkillData data = gson.fromJson(json,SkillData.class);


//		ObjectMapper mapper = new ObjectMapper();
//		SkillData data = null;
//
//		try
//		{
//			data = mapper.readValue(json, SkillData.class);
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
		return "SKILL."+id();
	}

}
