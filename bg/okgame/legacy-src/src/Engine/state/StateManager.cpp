#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger BobStateManager::log = Logger("BobStateManager");


BobStateManager::BobStateManager()
{ //=========================================================================================================================
}

shared_ptr<Engine> BobStateManager::getCurrentState()
{ //=========================================================================================================================

	if(states.size()>0)
	return states.get(0);
	else return nullptr;
}

//void BobStateManager::setState(Engine* s)
//{ //=========================================================================================================================
//	currentState = s;
//}

void BobStateManager::pushState(shared_ptr<Engine> s)
{ //=========================================================================================================================
	states.insert(0, s);
}

void BobStateManager::popState()
{ //=========================================================================================================================
	if(states.size()>0)
	states.removeAt(0);
}

void BobStateManager::update()
{
	Engine::updateTimers();
	getCurrentState()->update();
}

void BobStateManager::render()
{
	getCurrentState()->render();
}

