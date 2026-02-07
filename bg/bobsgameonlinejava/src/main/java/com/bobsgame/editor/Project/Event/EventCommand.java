package com.bobsgame.editor.Project.Event;

import java.util.ArrayList;

import com.bobsgame.editor.Project.GameObject;

public class EventCommand
{


	public String commandString = "";


	int type=-1;
	public static int TYPE_COMMAND=0;
	public static int TYPE_QUALIFIER_TRUE=1;
	public static int TYPE_QUALIFIER_FALSE=2;


	ArrayList<EventParameter> parameterList = new ArrayList<EventParameter>();

	//===============================================================================================
	public EventCommand(String command, ArrayList<EventParameter> parameterList, int type)
	{//===============================================================================================

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
	/**
	 * This is what gets used when outputting the Tree to a string for saving. Notice it uses getIDString() when printing the parameters.
	 */
	public String toSaveString()
	{//===============================================================================================

		if(parameterList==null)
		{

			String s = ""+commandString;
			if(type==TYPE_QUALIFIER_TRUE)s=s.concat(" == TRUE");
			if(type==TYPE_QUALIFIER_FALSE)s=s.concat(" == FALSE");

			return s;
		}
		else
		{
			String s = ""+commandString+"(";
			for(int i=0;i<parameterList.size();i++)
			{
				s = s.concat(parameterList.get(i).getIDString());
				if(i<parameterList.size()-1)s = s.concat("|");
			}
			s=s.concat(")");

			if(type==TYPE_QUALIFIER_TRUE)s=s.concat(" == TRUE");
			if(type==TYPE_QUALIFIER_FALSE)s=s.concat(" == FALSE");

			return s;
		}

	}

	//===============================================================================================
	/**
	 * This is what the Tree will use to display the cells. Notice it uses getDisplayName() when printing the parameters.
	 */
	public String toString()
	{//===============================================================================================

		if(parameterList==null)
		{
			String s = ""+commandString;
			if(type==TYPE_QUALIFIER_TRUE)s=s.concat(" == TRUE");
			if(type==TYPE_QUALIFIER_FALSE)s=s.concat(" == FALSE");

			return s;
		}
		else
		{
			String s = ""+commandString+"(";
			for(int i=0;i<parameterList.size();i++)
			{

				EventParameter temp = parameterList.get(i);
				if(temp!=null)s = s.concat(temp.getDisplayName());
				if(i<parameterList.size()-1)s = s.concat("|");
			}
			s=s.concat(")");

			if(type==TYPE_QUALIFIER_TRUE)s=s.concat(" == TRUE");
			if(type==TYPE_QUALIFIER_FALSE)s=s.concat(" == FALSE");

			return s;
		}
	}


	//===============================================================================================
	public static EventCommand parseEventCommandFromCommandString(String commandString)
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
					String parameterName = commandString.substring(0,commandString.indexOf("|"));
					commandString = commandString.substring(commandString.indexOf("|")+1);//split off parameter and |
					//commandString now looks like "thing)" or "thing|thing)"

					//all parameters looks like THING.ID
					newParameterList.add(EventParameter.parseParameterFromIDString(parameterName));

				}
				else //commandString looks like thing)
				{
					String parameterName = commandString.substring(0,commandString.indexOf(")"));
					commandString = commandString.substring(commandString.indexOf(")"));//split off parameter
					//commandString now looks like ")"

					//all parameters looks like THING.ID
					newParameterList.add(EventParameter.parseParameterFromIDString(parameterName));
				}
			}



			e = new EventCommand(command,newParameterList,type);

		}
		else
		{
			//it's just doThing

			e = new EventCommand(commandString,null,type);

		}





		return e;
	}


}
