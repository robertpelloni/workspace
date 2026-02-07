//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
class Logger;

#include "src/Engine/Engine.h"

#include "src/Utility/BobConsole.h"
#include "src/Utility/ConsoleText.h"

class Wallet;
class Clock;
class Player;
class GameSave;
class GUIManager;
class BobStatusBar;
class FriendManager;
class ND;
class Sprite;
class StadiumScreen;

class BGClientEngine : public Engine
{
	//DebugText playerSpeedText = DebugConsole.add("playerSpeedText");
private:
	typedef Engine super;

public:
	
	static Logger log;

	static bool debugMode;

	ConsoleText* playerMapText = nullptr;// = Console::debug("playerMapText");
	ConsoleText* playerScreenText = nullptr;// = Console::debug("playerScreenText");

	shared_ptr<GUIManager> guiManager = nullptr;
	shared_ptr<BobStatusBar> statusBar = nullptr;
	shared_ptr<Wallet> wallet = nullptr;

	shared_ptr<Clock> clock = nullptr;

	shared_ptr<Player> normalPlayer = nullptr;
	shared_ptr<Player> player = nullptr;

	shared_ptr<FriendManager> friendManager = nullptr;

	shared_ptr<ND> nD = nullptr;
	shared_ptr<StadiumScreen> stadiumScreen = nullptr;

	bool controlsEnabled = true;
	bool playerExistsInMap = true;

	BGClientEngine();
	virtual ~BGClientEngine() override;
	virtual void init() override;

	virtual void update() override;

	virtual void cleanup() override;

	virtual void render() override;

	bool areAnyMenusOpen();

	void handleGameEngineOptionKeys();

	virtual void updateDebugText() override;

	void loadPreCachedObjectData();

	void initializeGameFromSave_S();
	void setPlayerAppearanceFromGameSave_S();

	BobColor* getNameColor(int accountType);

	string getAccountRankString(int accountRank);
	BobColor* getAccountRankColor(int accountRank);

	void setPlayerToTempPlayerWithSprite(Sprite* s);
	void setPlayerToNormalPlayer();

	Clock* getClock();
	GUIManager* getGUIManager();
	StuffMenu* getStuffMenu();
	GameStore* getGameStore();
	PlayerEditMenu* getPlayerEditMenu();
	Player* getPlayer();
	ND* getND();
	Wallet* getWallet();
	FriendManager* getFriendManager();
	BobStatusBar* getBobStatusBar();
	NotificationManager* getNotificationManager();
	//The following method was originally marked 'synchronized':

	//====================================================
	//NETWORKING
	//====================================================

	bool gameSaveCompleted_nonThreaded = false;

	//GameSave* getGameSave_S();

	private:
		bool isGameInitializedFromSave_nonThreaded = false;
		bool _isGameInitializedFromSave = false; //synchronized
public:
	//The following method was originally marked 'synchronized':
	void setGameInitializedFromSave_S(bool b);
	//The following method was originally marked 'synchronized':
	bool getGameInitializedFromSave_S();

	virtual bool serverMessageReceived(string e) override;

private:
	//long long lastSentProjectLoadEventRequestTime = 0;
	//bool isProjectLoadEventInitialized_nonThreaded = false;
	int _projectLoadEventID = -1;

public:
	//The following method was originally marked 'synchronized':
	void setProjectLoadEventID_S(int id);

	//The following method was originally marked 'synchronized':
	int getProjectLoadEventID_S();

	bool getFinishedLoadEvent();
	BobEvent* projectLoadEvent = nullptr;

	bool finishedProjectLoadEvent = false;

	public:
		void sendProjectLoadEventRequest();

private:
	void incomingLoadEventResponse(string s);

};

