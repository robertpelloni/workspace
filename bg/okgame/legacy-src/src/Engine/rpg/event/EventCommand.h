//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include <memory>




class EventParameter;


class EventCommand : public EnginePart, public std::enable_shared_from_this<EventCommand>
{
public:

	static Logger log;


	string commandString = "";


	int type = -1;
	static int TYPE_COMMAND;
	static int TYPE_QUALIFIER_TRUE;
	static int TYPE_QUALIFIER_FALSE;


	ArrayList<shared_ptr<EventParameter>>* parameterList = new ArrayList<shared_ptr<EventParameter>>();

	weak_ptr<EventCommand> parent;


	ArrayList<shared_ptr<EventCommand>>* children = new ArrayList<shared_ptr<EventCommand>>();


	EventCommand(Engine* g, const string& command, ArrayList<shared_ptr<EventParameter>>* parameterList, int type);

	int getNumParams();


	static shared_ptr<EventCommand> parseEventCommandFromCommandString(Engine* g, BobEvent* event, string commandString);


	shared_ptr<EventCommand> getParent();


	void addChild(shared_ptr<EventCommand> e);


	int currentChildIndex = 0;


	shared_ptr<EventCommand> getNextChild();
};

