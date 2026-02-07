package com.bobsgame.shared;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import java.lang.reflect.Field;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;

import org.apache.commons.codec.binary.Base64;
import org.apache.commons.codec.binary.StringUtils;

import com.google.gson.Gson;
import com.google.gson.JsonDeserializationContext;
import com.google.gson.JsonDeserializer;
import com.google.gson.JsonElement;
import com.google.gson.JsonParseException;


//===============================================================================================
public class AssetData
{//===============================================================================================



	protected String name;
	protected int id = -1;





	//===============================================================================================
	public AssetData()
	{//===============================================================================================


	}



	//===============================================================================================
	public AssetData(int id,String name)
	{//===============================================================================================
		this.id=id;
		this.name=name;
	}


	//===============================================================================================
	public String toJSON()
	{//===============================================================================================

		Gson gson = new Gson();
		String json = gson.toJson(this);

//		ObjectMapper mapper = new ObjectMapper();
//		String json = "";
//
//		try
//		{
//			json = mapper.writeValueAsString(this);
//		}
//		catch(JsonGenerationException e)
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


		return json;

	}


	//===============================================================================================
	public String toString()
	{//===============================================================================================

		String s = "";

		while(name.contains("`"))
		{
			String front = name.substring(0,name.indexOf("`"));
			String back = name.substring(name.indexOf("`")+1);
			name = front + back;
		}



		s += "name:`"+name+"`,";
		s += "id:`"+id+"`,";


		return s;
	}




public String initFromString(String t)
{

	t = t.substring(t.indexOf("name:`")+1);
	t = t.substring(t.indexOf("`")+1);
	name = t.substring(0,t.indexOf("`"));
	t = t.substring(t.indexOf("`,")+2);

	t = t.substring(t.indexOf("id:`")+1);
	t = t.substring(t.indexOf("`")+1);
	id = Integer.parseInt(t.substring(0,t.indexOf("`")));
	t = t.substring(t.indexOf("`,")+2);

	return t;
}



//
//
//	//===============================================================================================
//	public String toBase64ZippedJSON()
//	{//===============================================================================================
//
//
//		String json = toJSON();
//		//System.out.println("json------------------------------");
//		//System.out.println("length:"+json.length());
//		//System.out.println(json);
//
//		String zip = "";
//
//		zip = Utils.zipString(json);
//
//
//		//System.out.println("zip------------------------------");
//		//System.out.println("length:"+zip.length());
//		//System.out.println(zip);
//
//
//		String b64 = Utils.encodeStringToBase64(zip);
//
//		//System.out.println("b64------------------------------");
//		//System.out.println("length:"+b64.length());
//		//System.out.println(b64);
//
//		//String decode64 = decodeBase64String(b64);
//		//String unzip = unzipString(decode64);
//		//MapData m2 = gson.fromJson(unzip,MapData.class);
//		//json = gson.toJson(m2);
//		//System.out.println("json------------------------------");
//		//System.out.println("length:"+json.length());
//		//System.out.println(json);
//
//		return b64;
//
//
//	}


	public String name(){return name;}
	public int id(){return id;}


	public void setName(String s){name=s;}
	public void setID(int s){id=s;}


}
