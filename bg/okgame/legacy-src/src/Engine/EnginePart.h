//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
class UDPPeerConnection;
class TCPServerConnection;
class Logger;



class ControlsManager;
class Cameraman;
class Engine;
class MapManager;
class SpriteManager;
class ActionManager;
class AudioManager;
class TextManager;
class EventManager;
class CinematicsManager;
class Map;
class BGClientEngine;
class Player;
class Wallet;
class GameSave;
class CaptionManager;
class Clock;
class BGClientTCP;
class GUIManager;
class StuffMenu;
class GameStore;
class PlayerEditMenu;
class ND;
class FriendManager;
class BobStatusBar;
class NotificationManager;

class EnginePart
{
public:
	virtual ~EnginePart()
	{
	}

	static Logger log;

protected:
	Engine* e = nullptr;

private:
	//static BGClientEngine* clientGameEngine;
	//ControlsManager* controlsManager = nullptr;

	
	bool isActivated = false;
	long long lastTimeHere = -1;
	long long timeActivated = -1;

public:
	EnginePart();
	EnginePart(Engine* e);

	//void setControlsManager(ControlsManager* controlsManager);

	virtual void toggleActivated();
	virtual void setActivated(bool b);
	virtual bool getIsActivated();
	bool getWasEverActivated();
	int getSecondsSinceActivated();
	bool getWasEverHere();
	void resetLastTimeHere();
	void setLastTimeHere();
	long long getLastTimeHere();
	int getSecondsSinceLastHere();
	int getMinutesSinceLastHere();

	Engine* getEngine();
	shared_ptr<Cameraman> getCameraman();
	shared_ptr<MapManager> getMapManager();
	shared_ptr<SpriteManager> getSpriteManager();
	shared_ptr<ActionManager> getActionManager();
	shared_ptr<TextManager> getTextManager();
	shared_ptr<AudioManager> getAudioManager();
	virtual shared_ptr<CaptionManager> getCaptionManager();
	shared_ptr<EventManager> getEventManager();
	shared_ptr<CinematicsManager> getCinematicsManager();

	virtual shared_ptr<Map> getCurrentMap();

	shared_ptr<ControlsManager> getControlsManager();

	//static void setClientGameEngine(BGClientEngine* gameEngine);

	static BGClientEngine* getClientGameEngine();

	static TCPServerConnection* getServerConnection();

	static Clock* getClock();
	static GUIManager* getGUIManager();
	static StuffMenu* getStuffMenu();
	static GameStore* getGameStore();
	static PlayerEditMenu* getPlayerEditMenu();
	static Player* getPlayer();
	static ND* getND();
	static Wallet* getWallet();
	static FriendManager* getFriendManager();
	static BobStatusBar* getBobStatusBar();
	static NotificationManager* getNotificationManager();
	//The following method was originally marked 'synchronized':
	static GameSave getGameSave();

	virtual bool udpPeerMessageReceived(shared_ptr<UDPPeerConnection> c, string e);
	//
	//	public String getIDString()
	//	{
	//
	//		return null;
	//	}
	//
	//
	//
	//	public String getShortTypeName()
	//	{
	//
	//		return null;
	//	}
};

