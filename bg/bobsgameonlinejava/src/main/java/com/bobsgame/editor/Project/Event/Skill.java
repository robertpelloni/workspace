package com.bobsgame.editor.Project.Event;

import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.shared.SkillData;





//===============================================================================================
public class Skill implements GameObject
{//===============================================================================================




	private SkillData data;

	//===============================================================================================
	public Skill(SkillData data)
	{//===============================================================================================


		this.data = data;


		Project.skillList.add(this);
		Project.skillHashtable.put(getTYPEIDString(),this);
	}

	//===============================================================================================
	public Skill(String name)
	{//===============================================================================================



		int id = -1;

		int size=Project.skillList.size();

		if(size==0)id=0;
		else
		{
			int biggest=0;
			for(int i=0;i<size;i++)
			{
				int testid = Project.skillList.get(i).id();

				if(testid>biggest)biggest=testid;
			}

			id=biggest+1;

		}

		this.data = new SkillData(id,name);

		Project.skillList.add(this);
		Project.skillHashtable.put(getTYPEIDString(),this);

	}



	public SkillData getData(){return data;}


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
		return "SKILL."+name();
	}

	@Override
	public String getLongTypeName()
	{
		return "SKILL."+id()+"."+name();
	}





}
