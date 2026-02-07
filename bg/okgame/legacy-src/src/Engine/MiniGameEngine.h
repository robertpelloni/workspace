//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
#include "Engine.h"
#include "../Utility/CaptionManager.h"
#include "../Utility/gl/BobTexture.h"
#include "../Utility/BobMenu.h"
#include <memory>

class Logger;
class GameDataLoader;
class UDPPeerConnection;
class FriendCharacter;

//=========================================================================================================================
class MiniGameEngine : public Engine
{//=========================================================================================================================
private:
	typedef Engine super;
public:
	static Logger log;

	shared_ptr<GameDataLoader> gameDataLoader = nullptr;

	string name = "";

	MiniGameEngine();
	virtual ~MiniGameEngine();
	virtual void init();

	string& getGameName();

	virtual void shakeSmall();
	virtual void shakeHard();

	//void update();



	int numTitleMenuTextureFrames = 0;
	shared_ptr<ArrayList<shared_ptr<BobTexture>>> titleMenuTextures = make_shared<ArrayList<shared_ptr<BobTexture>>>();
	shared_ptr<BobTexture> titleMenuTexture = nullptr;
	long long titleMenuFrameTicks = 0;
	int currentTitleMenuTextureFrame = 0;
	bool currentTitleMenuTextureFrameIncrementDecrementToggle = false;
	bool titleMenuShowing = false;

	bool pauseMenuShowing = false;
	shared_ptr<BobMenu> pauseMenu = nullptr;
	//Caption* volumeCaption = nullptr;
	int pauseMenuCursorPosition = 0;

	shared_ptr<BobMenu> titleMenu = nullptr;
	int titleMenuCursorPosition = 0;

	virtual void setupMenus();
	virtual bool updateMenus();
	virtual bool renderMenus();

	virtual void titleMenuUpdate();
	virtual void titleMenuRender();
	
	virtual void updateTitleScreenLogo();
	virtual void updateTitleMenuLogoTexture();
	virtual void unloadTitleMenuTextures();

	virtual void pauseMenuUpdate();
	virtual void pauseMenuRender();
	

	virtual void tryToCloseGame();
	virtual bool isNetworkGame();

protected:

	bool waitingForFriendScreenShowing = false;
	long long updateStatsTime = 0;
	long long rotateLeaderBoardsTime = 0;
	long long whichLeaderBoardToShow = 0;
	long long whichDifficultyToShow = 0;
	long long updateFriendsTime = 0;
	long long updatePublicGamesTime = 0;
	shared_ptr<ArrayList<shared_ptr<Caption>>> onlineFriendCaptions = make_shared<ArrayList<shared_ptr<Caption>>>();
	shared_ptr<ArrayList<shared_ptr<Caption>>> waitingForFriendCaptions = make_shared<ArrayList<shared_ptr<Caption>>>();
	void waitingForFriendScreenUpdate();
	void waitingForFriendScreenRender();

	//bool singlePlayerMultiPlayerSwitchToggle = false; //false = singleplayer
	bool multiplayerScreenShowing = false;
	//Caption* singlePlayerCaption = nullptr;
	//Caption* onlineMultiplayerCaption = nullptr;
	//Caption* multiPlayerCaption = nullptr;
	int multiplayerScreenCursorPosition = 0;
	void multiplayerScreenRender();
	void multiplayerScreenUpdate();


public:
	//	bool throttle30fps = false;
	//	long long ticksPassed = 0;
	//	long long frameThrottleTicks = 0;

	bool networkGameStarted_NonThreaded = false;
protected:
	long long nonThreadedTicksCounter = 0;

public:
	shared_ptr<UDPPeerConnection> connection = nullptr;

	//public boolean multiplayer = false;

protected:
	//UDPPeerConnection* friendCharacter = nullptr;

public:
	static int gameChallengeResponse_NONE;
	static int gameChallengeResponse_ACCEPT;
	static int gameChallengeResponse_DECLINE;

private:
	int _incomingGameChallengeResponse = gameChallengeResponse_NONE;
public:

	long long nonThreaded_SendGameChallengeRequestSentTime = 0;
	long long nonThreaded_CheckForGameChallengeResponseCounter = 0;

	long long gameChallengeRequestSentTime = -1;

	//The following method was originally marked 'synchronized':
	int getIncomingGameChallengeResponse();
	//The following method was originally marked 'synchronized':
	void setIncomingGameChallengeResponse(int s);

	//void setConnection(UDPPeerConnection* connection);
	virtual bool udpPeerMessageReceived(shared_ptr<UDPPeerConnection> c, string e);

private:
	void incoming_GameChallengeResponse(const string& s);

};
