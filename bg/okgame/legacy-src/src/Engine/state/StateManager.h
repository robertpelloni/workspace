//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class BobStateManager
{
public:

	static Logger log;


	ArrayList<Engine*> states;

	//Engine* currentState = nullptr;


	BobStateManager();


	Engine* getCurrentState();


	void pushState(Engine* s);
	void popState();


	void update();

	void render();


};

