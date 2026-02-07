package com.bobsgame.client.engine.event;

import java.util.ArrayList;
import java.util.Vector;

import com.bobsgame.client.console.Console;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.game.Item;
import com.bobsgame.client.engine.map.WarpArea;
import com.bobsgame.shared.EventData;
//=========================================================================================================================
public class EventManager extends EnginePart
{//=========================================================================================================================

	public Vector<Event> eventList = new Vector<Event>();
	public Vector<Dialogue> dialogueList = new Vector<Dialogue>();
	public Vector<GameString> gameStringList = new Vector<GameString>();
	public Vector<Flag> flagList = new Vector<Flag>();
	public Vector<Skill> skillList = new Vector<Skill>();
	public Vector<Item> itemList = new Vector<Item>();


	public ArrayList<Event> runningEventQueue = new ArrayList<Event>();

	//=========================================================================================================================
	public EventManager(Engine g)
	{//=========================================================================================================================
		super(g);


	}


	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================


	}





	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

		//for(int i=0;i<eventList.size();i++)eventList.get(i).update();//only update running events, otherwise we update events that we might not have access to yet.

		for(int i=0;i<itemList.size();i++)itemList.get(i).update();
		for(int i=0;i<gameStringList.size();i++)gameStringList.get(i).update();
		for(int i=0;i<dialogueList.size();i++)dialogueList.get(i).update();
		for(int i=0;i<flagList.size();i++)flagList.get(i).update();
		for(int i=0;i<skillList.size();i++)skillList.get(i).update();
		for(int i=0;i<itemList.size();i++)itemList.get(i).update();


		for(int i=0;i<runningEventQueue.size();i++)
		{
			Event s = runningEventQueue.get(i);
			s.run();
		}
	}






	//=========================================================================================================================
	public void addToEventQueueIfNotThere(Event event)
	{//=========================================================================================================================




			if(event.getWasAddedToQueue()==false)
			{

				runningEventQueue.add(event);
				event.setAddedToQueue();

			}

			//if it isn't in the event queue, add a fresh stack to the event queue.


			//if it is in the event queue, run the next instruction.


	}


	//=========================================================================================================================
	public boolean isEventInQueue(Event event)
	{//=========================================================================================================================

		for(int i=0;i<runningEventQueue.size();i++)
		{

			Event s = runningEventQueue.get(i);

			if(s == event)return true;

		}
		return false;


	}



	//=========================================================================================================================
	public void unloadCurrentMapEvents()
	{//=========================================================================================================================

		for(int i=0;i<CurrentMap().mapEventIDList.size();i++)
		{
			Event s = EventManager().getEventByIDCreateIfNotExist(CurrentMap().mapEventIDList.get(i));
			s.reset();
		}

		for(int i=0;i<runningEventQueue.size();i++)
		{
			Event s = runningEventQueue.get(i);

			if(s.type()!=EventData.TYPE_PROJECT_INITIAL_LOADER && s.type()!=EventData.TYPE_PROJECT_CUTSCENE_DONT_RUN_UNTIL_CALLED)
			{
				s.reset();
				runningEventQueue.remove(i);
				i=-1;
			}
		}


	}








	//=========================================================================================================================
	public Item getItemByID(int id)
	{//=========================================================================================================================
		for(int i=0;i<itemList.size();i++)
		{
			Item s = itemList.get(i);
			if(s.id()==id)return s;
		}



		String e = "Item not found! getItemByID():"+id;
		Console.error(e);
		log.error(e);

		return null;
	}




	//=========================================================================================================================
	public Dialogue getDialogueByIDCreateIfNotExist(int id)
	{//=========================================================================================================================
		for(int i=0; i<dialogueList.size(); i++)
		{
			Dialogue d = dialogueList.get(i);
			if(d.id()==id)return d;
		}
		return new Dialogue(Engine(), id);
	}

	//=========================================================================================================================
	public Event getEventByIDCreateIfNotExist(int id)
	{//=========================================================================================================================
		//go through list
		//if event doesn't exist, make new one
		for(int i=0; i<eventList.size(); i++)
		{
			Event d = eventList.get(i);
			if(d.id()==id)return d;
		}


		Event d = new Event(Engine(),id);

		return d;
	}


	//=========================================================================================================================
	public Skill getSkillByIDCreateIfNotExist(int id)
	{//=========================================================================================================================
		for(int i=0;i<skillList.size();i++)
		{
			Skill s = skillList.get(i);
			if(s.id()==id)return s;
		}

		//All skills defined in editor should be loaded from /res/SkillData at load, so it should always exist.

		String e = "Skill not found! getSkillByID():"+id;
		Console.error(e);
		log.error(e);


		return new Skill(Engine(),id);


	}

	//=========================================================================================================================
	public GameString getGameStringByIDCreateIfNotExist(int id)
	{//=========================================================================================================================

		for(int i=0;i<gameStringList.size();i++)
		{
			GameString s = gameStringList.get(i);
			if(s.id()==id)return s;
		}

		return new GameString(Engine(),id);
	}


	//=========================================================================================================================
	public Flag getFlagByIDCreateIfNotExist(int id)
	{//=========================================================================================================================
		for(int i=0;i<flagList.size();i++)
		{
			Flag s = flagList.get(i);
			if(s.id()==id)return s;
		}

		return new Flag(Engine(),id);
	}








}
