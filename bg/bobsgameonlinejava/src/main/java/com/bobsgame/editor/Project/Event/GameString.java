package com.bobsgame.editor.Project.Event;

import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.shared.GameStringData;





//===============================================================================================
public class GameString implements GameObject
{//===============================================================================================




	private GameStringData data;


	//===============================================================================================
	public GameString(GameStringData data)
	{//===============================================================================================

		this.data = data;

		Project.gameStringList.add(this);
		Project.gameStringHashtable.put(getTYPEIDString(),this);
	}

	//===============================================================================================
	public GameString(String name, String text)
	{//===============================================================================================


		int id = -1;

		int size=Project.gameStringList.size();

		if(size==0)id=0;
		else
		{
			int biggest=0;
			for(int i=0;i<size;i++)
			{
				int testid = Project.gameStringList.get(i).id();

				if(testid>biggest)biggest=testid;
			}

			id=biggest+1;

		}

		this.data = new GameStringData(id,name,text);

		Project.gameStringList.add(this);
		Project.gameStringHashtable.put(getTYPEIDString(),this);

	}



	public GameStringData getData(){return data;}

	public int id(){return data.id();}
	public String name(){return data.name();}
	public String text(){return data.text();}

	public String getTYPEIDString(){return data.getTYPEIDString();}

	public void id(int id){data.setID(id);}
	public void setName(String name){data.setName(name);}
	public void text(String text){data.setText(text);}










	//===============================================================================================
	public String toString()
	{//===============================================================================================
		return getTYPEIDString();

	}


	@Override
	public String getShortTypeName()
	{
		return getTYPEIDString();
	}

	@Override
	public String getLongTypeName()
	{
		return getTYPEIDString();
	}





}
