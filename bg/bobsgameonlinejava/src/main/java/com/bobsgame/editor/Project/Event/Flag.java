package com.bobsgame.editor.Project.Event;

import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.shared.FlagData;





//===============================================================================================
public class Flag implements GameObject
{//===============================================================================================


	private FlagData data;


	//===============================================================================================
	public Flag(FlagData data)
	{//===============================================================================================

		this.data = data;

		Project.flagList.add(this);
		Project.flagHashtable.put(getTYPEIDString(),this);
	}

	//===============================================================================================
	public Flag(String name)
	{//===============================================================================================


		int id = -1;

		int size=Project.flagList.size();

		if(size==0)id=0;
		else
		{
			int biggest=0;
			for(int i=0;i<size;i++)
			{
				int testid = Project.flagList.get(i).id();

				if(testid>biggest)biggest=testid;
			}

			id=biggest+1;

		}

		this.data = new FlagData(id,name);

		Project.flagList.add(this);
		Project.flagHashtable.put(getTYPEIDString(),this);

	}




	public FlagData getData(){return data;}


	public int id(){return data.id();}
	public String name(){return data.name();}
	public String getTYPEIDString(){return data.getTYPEIDString();}


	public void setID(int id){data.setID(id);}
	public void setName(String name){data.setName(name);}








	//===============================================================================================
	public String toString()
	{//===============================================================================================
		return getTYPEIDString();

	}



	@Override
	public String getShortTypeName()
	{
		return "FLAG."+name();
	}

	@Override
	public String getLongTypeName()
	{
		return "FLAG."+id()+"."+name();
	}





}
