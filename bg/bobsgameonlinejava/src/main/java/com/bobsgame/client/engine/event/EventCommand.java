package com.bobsgame.client.engine.event;

import java.util.ArrayList;

import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;

//===============================================================================================
public class EventCommand extends EnginePart
{//===============================================================================================


	public String commandString = "";


	int type=-1;
	public static int TYPE_COMMAND=0;
	public static int TYPE_QUALIFIER_TRUE=1;
	public static int TYPE_QUALIFIER_FALSE=2;




	ArrayList<EventParameter> parameterList = new ArrayList<EventParameter>();

	EventCommand parent = null;


	ArrayList<EventCommand> children = new ArrayList<EventCommand>();

	//===============================================================================================
	public EventCommand(Engine g, String command, ArrayList<EventParameter> parameterList, int type)
	{//===============================================================================================

		super(g);

		this.type=type;

		this.parameterList = parameterList;

		this.commandString = command;

	}
	//===============================================================================================
	public int getNumParams()
	{//===============================================================================================
		if(parameterList==null)return 0;
		else return parameterList.size();
	}






	//===============================================================================================
	public static EventCommand parseEventCommandFromCommandString(Engine g, Event event, String commandString)
	{//===============================================================================================


		//possible commandString getting passed in:

		//doThing
		//doThing()
		//doThing(thing)
		//doThing(thing|thing)
		//ifDoThing == TRUE
		//ifDoThing() == TRUE
		//ifDoThing(thing) == TRUE
		//ifDoThing(thing|thing) == TRUE

		int type=-1;

		EventCommand e = null;




		if(commandString.contains(" == TRUE"))
		{
			type=TYPE_QUALIFIER_TRUE;
			commandString = commandString.substring(0,commandString.indexOf(" == TRUE"));
		}
		else
		if(commandString.contains(" == FALSE"))
		{
			type=TYPE_QUALIFIER_FALSE;
			commandString = commandString.substring(0,commandString.indexOf(" == FALSE"));
		}
		else
		{
			type=TYPE_COMMAND;
		}

		//now we're left with one of these:
		//doThing
		//doThing()
		//doThing(thing)
		//doThing(thing|thing)


		if(commandString.contains("("))
		{
			ArrayList<EventParameter> newParameterList = new ArrayList<EventParameter>();

			String command = commandString.substring(0,commandString.indexOf("("));

			commandString = commandString.substring(commandString.indexOf("(")+1);

			//commandString now looks like "thing)" or "thing|thing)" or ")"

			while(commandString.startsWith(")")==false)
			{

				if(commandString.indexOf("|")!=-1) //commandString looks like thing|thing)
				{
					String parameterString = commandString.substring(0,commandString.indexOf("|"));
					commandString = commandString.substring(commandString.indexOf("|")+1);//split off parameter and |
					//commandString now looks like "thing)" or "thing|thing)"

					//all parameters looks like THING.ID
					newParameterList.add(new EventParameter(g,parameterString));

				}
				else //commandString looks like thing)
				{
					String parameterString = commandString.substring(0,commandString.indexOf(")"));
					commandString = commandString.substring(commandString.indexOf(")"));//split off parameter
					//commandString now looks like ")"

					//all parameters looks like THING.ID
					newParameterList.add(new EventParameter(g,parameterString));
				}
			}



			e = new EventCommand(g,command,newParameterList,type);

		}
		else
		{
			//it's just doThing

			e = new EventCommand(g,commandString,null,type);

		}





		return e;
	}

	//=========================================================================================================================
	public EventCommand getParent()
	{//=========================================================================================================================
		return parent;
	}

	//=========================================================================================================================
	public void addChild(EventCommand e)
	{//=========================================================================================================================

		children.add(e);
		e.parent = this;

	}


	public int currentChildIndex = 0;

	//=========================================================================================================================
	public EventCommand getNextChild()
	{//=========================================================================================================================

		//ROOT
		//ifPlayerInArea TRUE
			//doThing
			//doNextThing
		//ifPlayerInArea FALSE

	//if we are [ROOT], we return [ifPlayerInArea TRUE]
	//if we are [ifPlayerInArea], we return [doThing]
	//if we are [doThing], we return [doNextThing]
	//if we are [doNextThing], we return [ifPlayerInArea FALSE]

		if(currentChildIndex<children.size())
		{

			EventCommand e = children.get(currentChildIndex);
			currentChildIndex++;

			return e;

		}
		else
		{

			currentChildIndex=0;
			if(getParent()!=null)return getParent().getNextChild();

			return null;
		}

	}


}
