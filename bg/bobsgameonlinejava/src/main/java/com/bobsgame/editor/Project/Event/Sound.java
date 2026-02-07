package com.bobsgame.editor.Project.Event;

import java.io.File;
import java.io.IOException;

import org.apache.commons.io.FileUtils;

import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.shared.SoundData;
import com.bobsgame.shared.Utils;





//===============================================================================================
public class Sound implements GameObject
{//===============================================================================================





	public boolean found = false;


	private SoundData data;


	//===============================================================================================
	public Sound(SoundData data)
	{//===============================================================================================


		this.data = data;

		Project.soundList.add(this);
		Project.soundHashtable.put(getTYPEIDString(),this);
	}

	//===============================================================================================
	public Sound(String name, String filename)
	{//===============================================================================================


		int id = -1;

		int size=Project.soundList.size();

		if(size==0)id=0;
		else
		{
			int biggest=0;
			for(int i=0;i<size;i++)
			{
				int testid = Project.soundList.get(i).id();

				if(testid>biggest)biggest=testid;
			}

			id=biggest+1;

		}


		this.data = new SoundData(id,name,filename);


		Project.soundList.add(this);
		Project.soundHashtable.put(getTYPEIDString(),this);

	}


	public SoundData getData(){return data;}

	public int id(){return data.id();}
	public String name(){return data.name();}
	public String fileName(){return data.fileName();}
	public String fullFilePath(){return data.fullFilePath();}
	public String md5Name(){return data.md5Name();}

	public String getTYPEIDString(){return data.getTYPEIDString();}


	public void setID(int id){data.setID(id);}
	public void setName(String name){data.setName(name);}
	public void setFileName(String fileName){data.setFileName(fileName);}
	public void setFullFilePath(String fullFilePath){data.setFullFilePath(fullFilePath);}
	public void setMD5Name(String s){data.setMD5Name(s);}











	//===============================================================================================
	public String toString()
	{//===============================================================================================
		return getTYPEIDString();

	}




	@Override
	public String getShortTypeName()
	{
		return "SOUND."+name();
	}

	@Override
	public String getLongTypeName()
	{
		return "SOUND."+id()+"."+name();
	}


	//===============================================================================================
	public String getFileBytesAsGZippedBase64String()
	{//===============================================================================================

		byte[] bytes = null;

		try
		{
			bytes = FileUtils.readFileToByteArray(new File(fullFilePath()));
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		return Utils.encodeStringToBase64(Utils.zipByteArrayToString(bytes));
	}





}
