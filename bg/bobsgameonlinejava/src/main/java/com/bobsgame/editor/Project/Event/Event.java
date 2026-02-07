package com.bobsgame.editor.Project.Event;

import java.awt.Color;

import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Map.Area;
import com.bobsgame.editor.Project.Map.Door;
import com.bobsgame.editor.Project.Map.Entity;
import com.bobsgame.editor.Project.Map.Light;
import com.bobsgame.editor.Project.Map.Map;
import com.bobsgame.shared.DialogueData;
import com.bobsgame.shared.EventData;



//===============================================================================================
public class Event implements GameObject
{//===============================================================================================


	private EventData data;

	public boolean connectedToSomething = false;

	//===============================================================================================
	public Event(int type, String name, String comment, String text)
	{//===============================================================================================

		int id = getBiggestID();


		this.data = new EventData(id,name,type,comment,text);

		Project.eventList.add(this);
		Project.eventHashtable.put(getTYPEIDString(),this);
	}



	//===============================================================================================
	public Event(EventData eventData)
	{//===============================================================================================

		this.data = eventData;

		if(Project.eventHashtable.get(getTYPEIDString())!=null)
		{
			System.err.println("Event ID for Event: "+name()+" already exists. Creating new ID.");
			int id = getBiggestID();
			setID(id);
		}


		Project.eventList.add(this);
		Project.eventHashtable.put(getTYPEIDString(),this);
	}





	//===============================================================================================
	public int getBiggestID()
	{//===============================================================================================
		int id = -1;

		int size=Project.eventList.size();

		if(size==0)id=0;
		else
		{
			int biggest=0;
			for(int i=0;i<size;i++)
			{
				int testid = Project.eventList.get(i).id();

				if(testid>biggest)biggest=testid;
			}

			id=biggest+1;

		}
		return id;

	}





	public EventData getData(){return data;}

	public int id(){return data.id();}
	public String name(){return data.name();}
	public int type(){return data.type();}
	public String comment(){return data.comment();}
	public String text(){return data.text();}

	public String getTYPEIDString(){return data.getTYPEIDString();}

	public void setID(int id){data.setID(id);}
	public void setName(String name){data.setName(name);}
	public void setType(int type){data.setType(type);}
	public void setComment(String comment){data.setComment(comment);}
	public void setText(String text){data.setText(text);}










	//===============================================================================================
	public String toString()
	{//===============================================================================================
		return getTYPEIDString();

	}


	//===============================================================================================
	public Event duplicate()
	{//===============================================================================================
		Event e = new Event(type(),name(),comment(),text());

		return e;

	}




	//===============================================================================================
	public String getPreviewString()
	{//===============================================================================================

		if(text().length()==0)return text();


		String s = text().substring(0);

		s = s.replace(',','\n');
		s = s.replace("{","\n{\n");
		s = s.replace("}","\n}\n");



		//go to next newline
		//add and subtract tabs

		String yay = "";

		int tabs = 0;
		while(s.contains("\n"))
		{
			for(int i=0;i<tabs;i++)yay = yay.concat("\t");

			String temp = s.substring(0,s.indexOf('\n'));

			yay = yay.concat(temp);
			yay = yay.concat("\n");

			if(temp.indexOf('{')!=-1)tabs++;
			if(temp.indexOf('}')!=-1)tabs--;

			s = s.substring(s.indexOf('\n'));

			if(s.length()>1)s=s.substring(1, s.length());
			else s = "";
		}
		yay = yay.replace("\t}","}");
		yay = yay.replace("\t","        ");


		return yay;


	}



	//===============================================================================================
	public String getFirstDialogueCaption()
	{//===============================================================================================
		if(text().contains("DIALOGUE."))
		{
			String s = text().substring(text().indexOf("DIALOGUE."),text().length());
			s = s.substring(s.indexOf(".")+1,s.indexOf(")"));
			return Project.getDialogueByID(Integer.parseInt(s)).caption();

		}
		return "";
	}


	@Override
	public String getShortTypeName()
	{

		//for event objects this is used to populate lists in the event editor.
		return "EVENT."+name();
	}
	@Override
	public String getLongTypeName()
	{
		return "EVENT."+id()+"."+name();
	}




	public String getFirst20Chars()
	{
		return text().substring(0,Math.min(20, text().length()));
	}





}






