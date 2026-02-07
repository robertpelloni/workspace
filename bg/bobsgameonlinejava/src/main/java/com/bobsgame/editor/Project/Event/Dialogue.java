package com.bobsgame.editor.Project.Event;

import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.shared.DialogueData;





//===============================================================================================
public class Dialogue implements GameObject
{//===============================================================================================




	private DialogueData data;


	//===============================================================================================
	public Dialogue(DialogueData dialogueData)
	{//===============================================================================================


		this.data = dialogueData;

		Project.dialogueList.add(this);
		Project.dialogueHashtable.put(getTYPEIDString(),this);
	}

	//===============================================================================================
	public Dialogue(String name, String caption, String comment, String text)
	{//===============================================================================================

		int id = -1;

		int size=Project.dialogueList.size();

		if(size==0)id=0;
		else
		{
			int biggest=0;
			for(int i=0;i<size;i++)
			{
				int testid = Project.dialogueList.get(i).id();

				if(testid>biggest)biggest=testid;
			}

			id=biggest+1;

		}

		this.data = new DialogueData(id,name,caption,comment,text);

		Project.dialogueList.add(this);
		Project.dialogueHashtable.put(getTYPEIDString(),this);

	}


	public DialogueData getData(){return data;}

	public int id(){return data.id();}
	public String name(){return data.name();}
	public String caption(){return data.caption();}
	public String comment(){return data.comment();}
	public String text(){return data.text();}

	public String getTYPEIDString(){return data.getTYPEIDString();}

	public void setID(int id){data.setID(id);}
	public void setName(String name){data.setName(name);}
	public void setCaption(String caption){data.setCaption(caption);}
	public void setComment(String comment){data.setComment(comment);}
	public void setText(String text){data.setText(text);}







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
