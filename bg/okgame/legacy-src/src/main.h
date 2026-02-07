

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#ifndef bob_main_h
#define bob_main_h



class Logger;
class BGClientTCP;
class Console;
class ControlsManager;
class BobsGame;
class FileUtils;
class BobStateManager;
class LoggedOutState;
class LogoState;
class LoginState;
class ServersHaveShutDownState;
class CreateNewAccountState;
class TitleScreenState;
class YouWillBeNotifiedState;
class GlowTileBackgroundMenuPanel;


#include "bobtypes.h"
#include "src/Utility/System.h"
#include "src/Utility/HashMap.h"
#include "src/Utility/ArrayList.h"

#include "Engine/network/BobNet.h"
#include "Engine/rpg/BGClientEngine.h"
#include "Puzzle/GlobalSettings.h"


#include <lib/GWEN-master/gwen/include/Gwen/Skins/TexturedBase.h>

#ifndef ORBIS
#include <lib/GWEN-master/gwen/include/Gwen/Input/gwen_input_sdl2.h>
#include <lib/GWEN-master/gwen/include/Gwen/Renderers/OpenGL.h>
#else


#include <lib/GWEN-master/gwen/include/Gwen/Input/GwenInputPS4.h>
#include <lib/GWEN-master/gwen/include/Gwen/Renderers/GwenRendererPS4.h>

class PS4InputToSDLEventConverter;



#endif



#ifndef ORBIS
class Main
#else
class Main : sce::SampleUtil::SampleSkeleton, common::Util::StateManager
#endif
{
public:

	static string serverAddressString;
	static string STUNServerAddressString;
	static int serverTCPPort;
	static int STUNServerUDPPort;
	static int clientUDPPortStartRange;


	static string version;
	static string path;
	//-----------------------------
	//variables
	//-----------------------------

	//static bool vbl_done;
	//static bool timer_done;

	//static TTF_Font* ttf_bobsgame_8;
	//static TTF_Font* ttf_bobsgame_16;
	//static bool seeded;
	//static bool vbl_init;
	//static bool GAME_is_running;
	//static bool append_screen;
	//static int MAIN_QUIT;
	static bool GLOBAL_hq2x_is_on;
	//static int HARDWARE_brightness;
	//static int vsync;
	//static int fpsmeter;
	//static int GAMESTATE;
	//static int GLOBAL_debug_level_select;
	//static bool GAME_paused;
	//static bool music_playing;

	//-----------------------------
	//ini variables
	//-----------------------------

	//static int debug;
	//static int fullscreen;
	//static int skiptext;
	//static int easymode;
	//static int cheater;


	BobsGame* bobsGame = nullptr;

	static Gwen::Controls::Canvas* gwenCanvas;
	static Gwen::Skin::TexturedBase* gwenSkin;
#ifndef ORBIS
	static Gwen::Renderer::OpenGL* gwenRenderer;
	static Gwen::Input::GwenSDL2 *gwenInput;

	SDL_Window* SDLWindow = nullptr;
	void printEvent(const SDL_Event* e);
#else

	static Gwen::Renderer::GwenRendererPS4* gwenRenderer;
	static Gwen::Input::GwenInputPS4 *gwenInput;


	//virtual sce::SampleUtil::System::UserIdManager* getUserIdManager();

#endif

	static Logger log;

	
	static bool mainLoopStarted;

	static Main* getMain();
	static void setMain(Main* c);

	Main();
	static ControlsManager* getControlsManager();
	static void openURL(string url);
	static string getPath();

	System* clientInfo = new System();

	//void initSystemInfo();

	float timeZoneGMTOffset = 0.0f;
	float DSTOffset = 0.0f;
	//void initClockAndTimeZone();

	void doLegalScreen();

	void showControlsImage();

	void makeGhostThread();


	void initGWEN();

	static GlobalSettings* globalSettings;
	void loadGlobalSettingsFromXML();
	void saveGlobalSettingsToXML();

	
	//public volatile boolean exit = false;
	static bool quit;// = false;

	//static AudioManager* audioManager;
	static FileUtils* fileUtils;
	static BobStateManager* stateManager;
	static System* systemUtils;
	//static ControlsManager* controlsManager;// = nullptr;

	static BGClientEngine* gameEngine;// = nullptr;
	
	//BGClientEngine* getGameEngine();

	//ArrayDeque<BGClientEngine*> *gameStack = new ArrayDeque<BGClientEngine*>();

	static Console* console;// = nullptr;
	static Console* rightConsole;// = nullptr;

	LogoState* logoScreenState = nullptr;
	LoginState* loginState = nullptr;
	LoggedOutState* loggedOutState = nullptr;
	ServersHaveShutDownState* serversHaveShutDownState = nullptr;
	CreateNewAccountState* createNewAccountState = nullptr;
	TitleScreenState* titleScreenState = nullptr;

	YouWillBeNotifiedState* youWillBeNotifiedState = nullptr;
	static GlowTileBackgroundMenuPanel* glowTileBackgroundMenuPanel;

	bool serversAreShuttingDown = false;

	string slash = "/";// System::getProperties().getProperty("file.separator");

					   //static bool isApplet;

	void processEvents();
	//FileUtils* utils;
	//GLUtils* lwjglUtils = nullptr;
	
	//GLUtils* glUtils = nullptr;
	// static AudioUtils* audioUtils;

	static BobNet* bobNet;



	//ClientUDP clientUDP;



	void mainInit();

	void initClientEngine();

	static bool introMode;
	static bool previewClientInEditor;

	bool debugKeyPressed = false;

	static bool screenShotKeyPressed;// = false;
	static bool resize;// = false;

	static void doResizeCheck();
	static void doScreenShotCheck();

	//static ArrayList<SDL_Event> events;// = new ArrayList<SDL_Event>();


	static void whilefix();
	static void delay(int ticks);
	static void justDelay(int ticks);
	static void StartTextInput();
	static void StopTextInput();

	void oldrender();
	void renderMain();
	virtual void updateMain();

	//static void e(const string &whereErrorOccurredString);
	//static void e();
	static void checkVersion();

	//   static string facebookID;
	//   static string facebookAccessToken;
	//   static bool _gotFacebookResponse;
	//

	//   //The following method was originally marked 'synchronized':
	//   static void setGotFacebookResponse_S(bool b);
	//   //The following method was originally marked 'synchronized':
	//   static bool getGotFacebookResponse_S();
	//
	//
	//   //this is called from the browser javascript after we call the facebook JS SDK
	//   void setFacebookCredentials(const string& facebookID, const string& accessToken);

	static void doSwap();
	void mainLoop();



	void cleanup();

	//int unZip(string file);




#ifdef ORBIS











































	int m_displayWidth;
	int m_displayHeight;

	common::Service::BaseService m_baseService;
	common::SaveDataManager m_saveDataManager;
	common::Service::InputDeviceManager m_inputDeviceManager;
	common::Game::GameLogManager m_gameLogManager;
	common::Util::AvPlayer m_avPlayer;
	SinglePlayerSaveData m_singlePlayerSaveData;

	sss::UserId m_selectedUserId;
	common::Game::PlayStyle::PlayStyle m_selectedPlayerPlayStyle;
	int32_t m_selectedPlayerScore;

	GameMenuScene					m_gameMenuScene;
	LoadingSaveDataScene			m_loadingSaveDataScene;
	SavingSaveDataScene				m_savingSaveDataScene;
	DisplayResultScene				m_displayResultScene;
	DisplayNpScoreRankingScene		m_displayNpScoreRankingScene;
	GameScene						m_gameScene;

	ScePthread			m_thread;
	bool m_isLoaded;
	bool m_isShootingRangeLoaded;









	virtual int initialize(void);
	virtual void render(void);
	virtual int finalize(void);
	virtual int update(void);
	void setErr(int err);

	static wstring getWString(string s);

	static common::Service::BaseService *getBaseService(void);

	static sce::SampleUtil::Graphics::GraphicsContext *getGraphicsContext(void);


	static sce::SampleUtil::Graphics::SpriteRenderer *getSpriteRenderer(void);


	static sce::SampleUtil::Audio::AudioContext *getAudioContext(void);


	static sce::SampleUtil::System::UserIdManager *getUserIdManager(void);


	static sce::SampleUtil::Input::PadContext *getPadContextOfInitialUser(void);

	//DebugMenu	m_debug;


	int getDisplaySize(ssg::GraphicsContext *graphicsContext, float *width, float *height)
	{
		int ret;
		if (graphicsContext && width && height)
		{
			*width = graphicsContext->getNextRenderTarget()->getWidth();
			*height = graphicsContext->getNextRenderTarget()->getHeight();
			ret = SCE_OK;
		}
		else
		{
			ret = -1;
		}
		return ret;
	};



	static PS4InputToSDLEventConverter* ps4ToSDLInputConverter;



	int initializeModules(void);

	int initializeScenes(void);

	static void* loadingThread(void *argc);

	static void* loadingThreadForShootingRange(void *argc);

	int startLoad(void);

	bool isLoaded(void);

	int startLoadRange(void);

	bool isShootingRangeLoaded(void);

	class TitleLogoState : public common::Util::State
	{
	private:
		Main *m_app;
		common::Game::NowLoadingWindow m_nowLoadingWindow;
	public:
		void init(Main *app);

		virtual int onEnter(void);

		virtual int onUpdate(float ellapseSec);

		void render(ssg::GraphicsContext *context);
	};

	class GameMenuState : public common::Util::State
	{
		Main	*m_app;

	public:
		void init(Main *app);

		virtual int onEnter(void);

		virtual int onLeave(void);

		virtual int onUpdate(float ellapseSec);

		void render(ssg::GraphicsContext *context);
	};

	class GameVideoState : public common::Util::State
	{
		enum State
		{
			kStateInitialized,
			kStatePlayingVideo,
			kStateErrorDialog,
			kStateFinished,
		};

		Main *m_app;
		State m_state;
		cu::DialogMonitor m_dialogMonitor;

	public:
		void init(Main *app);

		virtual int onEnter(void);

		virtual int onLeave(void);

		virtual int onUpdate(float ellapseSec);

		void render(ssg::GraphicsContext *context);
	};

	class LoadingSaveDataState : public common::Util::State
	{
		Main	*m_app;

	public:
		void init(Main *app);

		virtual int onEnter(void);

		virtual int onUpdate(float ellapseSec);

		void render(ssg::GraphicsContext *context);
	};

	class SavingSaveDataState : public common::Util::State
	{
		Main	*m_app;

	public:
		void init(Main *app);

		virtual int onEnter(void);

		virtual int onUpdate(float ellapseSec);

		void render(ssg::GraphicsContext *context);
	};

	class DisplayResultState : public common::Util::State
	{
		Main	*m_app;

	public:
		void init(Main *app);

		virtual int onEnter(void);

		virtual int onUpdate(float ellapseSec);

		void render(ssg::GraphicsContext *context);
	};

	class DisplayNpScoreRankingState : public common::Util::State
	{
		Main			*m_app;

	public:
		void init(Main *app);

		virtual int onEnter(void);

		virtual int onUpdate(float ellapseSec);

		void render(ssg::GraphicsContext *context);
	};

	class GameState : public common::Util::State
	{
		Main	*m_app;

	public:
		void init(Main *app);

		virtual int onEnter(void);

		virtual int onLeave(void);

		virtual int onUpdate(float ellapseSec);

		void render(ssg::GraphicsContext *context);
	};



	TitleLogoState					m_titleLogoState;
	GameMenuState					m_gameMenuState;
	GameVideoState					m_gameVideoState;
	LoadingSaveDataState			m_loadingSaveDataState;
	SavingSaveDataState				m_savingSaveDataState;
	DisplayResultState				m_displayResultState;
	DisplayNpScoreRankingState		m_displayNpScoreRankingState;
	GameState						m_gameState;

#endif




};



#endif