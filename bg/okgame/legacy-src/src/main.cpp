#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

//#undef INADDR_ANY
//#undef INADDR_LOOPBACK
//#undef INADDR_BROADCAST
//#undef INADDR_NONE
//#include "enet/enet.h"

//#include <lib/authenticate-GWEN-master/include/Gwen/renderer/gwen_renderer_sdl2.h>
//#include <lib/authenticate-GWEN-master/include/Gwen/input/gwen_input_sdl2.h>
//#include <lib/authenticate-GWEN-master/include/Gwen/skin/gwen_skin_texture.h>

//#include <imgui.h>
//#include "imgui_impl_sdl.h"

//#include "minilzo-2.10/minilzo.h"

#include "Gwen/Gwen.h"
#include "Gwen/Skins/Simple.h"
#include "Gwen/Skins/TexturedBase.h"
#include "Gwen/UnitTest/UnitTest.h"


#ifndef ORBIS
#include "Gwen/Input/Windows.h"
#include "Gwen/Renderers/OpenGL_TruetypeFont.h"
#include <lib/GWEN-master/gwen/include/Gwen/Input/gwen_input_sdl2.h>
Gwen::Input::GwenSDL2 *Main::gwenInput = nullptr;
Gwen::Renderer::OpenGL* Main::gwenRenderer = nullptr;
#else


#include "Gwen/Renderers/GwenRendererPS4.h"
#include <lib/GWEN-master/gwen/include/Gwen/Input/GwenInputPS4.h>
Gwen::Input::GwenInputPS4 *Main::gwenInput = nullptr;
Gwen::Renderer::GwenRendererPS4* Main::gwenRenderer = nullptr;

PS4InputToSDLEventConverter* Main::ps4ToSDLInputConverter = nullptr;




//size_t sceLibcHeapSize = (0xffffffffffffffffUL);// SCE_LIBC_HEAP_SIZE_EXTENDED_ALLOC_NO_LIMIT;
//unsigned int sceLibcHeapExtendedAlloc = 1;

size_t sceLibcHeapSize = 256 * 1024 * 1024;


#include <piglet\piglet.h>
#include <EGL\egl.h>
#include <GLES2\gl2.h>
#include <piglet\piglet.h>


/*E The FIOS2 default maximum path is 1024, games can normally use a much smaller value. */
#define MAX_PATH_LENGTH 1024

/*E Buffers for FIOS2 initialization.
* These are typical values that a game might use, but adjust them as needed. They are
* of type int64_t to avoid alignment issues. */

/* 64 ops: */
int64_t g_OpStorage[SCE_FIOS_DIVIDE_ROUNDING_UP(SCE_FIOS_OP_STORAGE_SIZE(64, MAX_PATH_LENGTH), sizeof(int64_t))];
/* 1024 chunks, 64KiB: */
int64_t g_ChunkStorage[SCE_FIOS_DIVIDE_ROUNDING_UP(SCE_FIOS_CHUNK_STORAGE_SIZE(1024), sizeof(int64_t))];
/* 16 file handles: */
int64_t g_FHStorage[SCE_FIOS_DIVIDE_ROUNDING_UP(SCE_FIOS_FH_STORAGE_SIZE(16, MAX_PATH_LENGTH), sizeof(int64_t))];
/* 1 directory handle: */
int64_t g_DHStorage[SCE_FIOS_DIVIDE_ROUNDING_UP(SCE_FIOS_DH_STORAGE_SIZE(1, MAX_PATH_LENGTH), sizeof(int64_t))];




uint64_t	m_previousTime;

namespace NpToolkit2 = sce::Toolkit::NP::V2;

void sceNpToolkitCallback(NpToolkit2::Core::CallbackEvent* event)
{
	NpToolkit2::Core::StringifyResult serviceAsString;
	NpToolkit2::Core::StringifyResult functionAsString;
	NpToolkit2::Core::getServiceTypeAsString(event->service, serviceAsString);
	NpToolkit2::Core::getFunctionTypeAsString(event->apiCalled, functionAsString);
}


using namespace sce;
using namespace sce::Gnmx;

#endif



Main* mainObject = nullptr;

//==========================================================================================================================
void cleanup()
{//==========================================================================================================================
	if (mainObject != nullptr)
	{
		mainObject->cleanup();
		delete mainObject;
		mainObject = nullptr;
	}


	try
	{
		std::terminate();
	}
	catch (exception e)
	{
		cerr << e.what();
	}
}




//==========================================================================================================================
int main(int argc, char* argv[])//int argc, char **argv)
{//==========================================================================================================================



//#ifdef WIN32
//	SetDllDirectory(LPCWSTR("./libs/"));
//#endif

	//cout << "Starting..." << endl;

	if(argc>0)
	{

		//TODO: run in headless mode, run bobsgame at maximum speed, load framestate binary from disk, encode youtube video?

	}


	

	mainObject = new Main();

	
	
	Main::setMain(mainObject);

	

	//atexit(cleanup);

	

	mainObject->mainInit();
	
	
	mainObject->mainLoop();

	cleanup();

//	Main::setMain(new Main());
//	Main::getMain()->mainInit();
//	Main::getMain()->mainLoop();
//	Main::getMain()->cleanup();


	return 0;
}

Logger Main::log = Logger("Main");


bool Main::mainLoopStarted = false;



bool Main::quit = false;

//bool Main::GAME_is_running = false;
bool Main::GLOBAL_hq2x_is_on = false;
//int Main::fpsmeter = true;

//==========================================================================================================================
Main::Main()
{//=========================================================================================================================

}



#ifdef __WINDOWS__
#include <shellapi.h>
wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}
#endif
//==========================================================================================================================
void Main::openURL(string url)
{//==========================================================================================================================

#ifdef __WINDOWS__

	LPCWSTR o = L"open";
	LPCWSTR u = convertCharArrayToLPCWSTR(url.c_str());

	ShellExecute(NULL, o, u, NULL, NULL, SW_SHOWNORMAL);

#endif
#ifdef __LINUX__
	string bin = "/usr/bin/firefox";
	char *args[2];
	args[0] = (char*)url.c_str();
	args[1] = 0;
	//					pid_t pid;
	//					pid = fork();
	//					if (!pid)execvp((char*)bin.c_str(), args);

	int result = system(string(bin + " " + url).c_str());
	if (result == -1)
	{
		bin = "/usr/bin/xdg-open";
		result = system(string(bin + " " + url).c_str());
	}
#endif
#ifdef __MACOSX__
	string command = "open " + url;
	system(command.c_str());
#endif
}






//FileUtils *Main::cacheManager = new FileUtils();
//bool Main::isApplet = false;

string Main::serverAddressString = BobNet::releaseServerAddress;
string Main::STUNServerAddressString = BobNet::releaseSTUNServerAddress;
int Main::serverTCPPort = BobNet::serverTCPPort;
int Main::STUNServerUDPPort = BobNet::STUNServerUDPPort;
int Main::clientUDPPortStartRange = BobNet::clientUDPPortStartRange;

string Main::version = "";

BobNet* Main::bobNet = nullptr;
Console* Main::console = nullptr;
Console* Main::rightConsole = nullptr;
//AudioManager* Main::audioManager = nullptr;
FileUtils* Main::fileUtils = nullptr;
BobStateManager* Main::stateManager = nullptr;
System* Main::systemUtils = nullptr;
GlobalSettings* Main::globalSettings = nullptr;
//ControlsManager* Main::controlsManager = nullptr;
BGClientEngine* Main::gameEngine = nullptr;

GlowTileBackgroundMenuPanel* Main::glowTileBackgroundMenuPanel = nullptr;


Gwen::Controls::Canvas* Main::gwenCanvas = nullptr;

Gwen::Skin::TexturedBase* Main::gwenSkin = nullptr;



//==========================================================================================================================
void Main::mainInit()
{//=========================================================================================================================



	//easy mode
	//debug/skiptext
	//bpp
	//fullscreen
	/*
	dictionary*	ini ;
	ini = iniparser_load("config.ini");
	if (ini==nullptr){fprintf(stderr,"config.ini not found\n");}
	else
	{
		fullscreen = iniparser_getboolean(ini, "bobsgame:fullscreen", 0);
		easymode = iniparser_getboolean(ini, "bobsgame:easymode", 0);
		debug = iniparser_getboolean(ini, "bobsgame:debug", 0);
		///if(debug)skiptext=1;
		//s = iniparser_getstring(ini, "bobsgame:easymode", nullptr);
		//i = iniparser_getint(ini, "skiptext:year", -1);
		//s = iniparser_getstring(ini, "wine:country", nullptr);
		//d = iniparser_getdouble(ini, "wine:alcohol", -1.0);
		iniparser_freedict(ini);
	}
	*/



#ifdef ORBIS
	int ret;

	ret = initialize();
#endif

	new Logger();
	Logger::initLogger();

	BobColor::initPresetColors();

	log.debug("Start");
	

	fileUtils = new FileUtils();
	fileUtils->initCache();

	loadGlobalSettingsFromXML();

	

#ifndef ORBIS
	if (globalSettings->useXInput == false)SDL_SetHint(SDL_HINT_XINPUT_ENABLED, "0");
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");

	log.debug("Init SDL");

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		log.error("SDL_Init error: "+string(SDL_GetError()));
		exit(2);
	}

	if (SDLNet_Init() < 0)
	{
		log.error("SDLNet_Init error: "+string(SDLNet_GetError()));
	}

#else
	
	



	//assert(ret == SCE_OK);

	

//	/*E Register libnetctl callback */
//	ret = sceNetCtlRegisterCallback(libnetctlCallback, NULL, &libnetctlCid);
//	if (ret < 0)
//	{
//		//printf("[SAMPLE] %s,%d ret=%x\n", __FUNCTION__, __LINE__, ret);
//		
//	}
//
//	/*E Create libnetctl check callback thread. */
//	ret = scePthreadCreate(&libnetctlTid, NULL, checkCallbackThread, NULL, "CheckCallbackThread");
//	if (ret < 0)
//	{
//		//printf("[SAMPLE] %s,%d ret=%x\n", __FUNCTION__, __LINE__, ret);
//	
//	}

#endif


	//	if (lzo_init() != LZO_E_OK)
	//	{
	//		printf("internal error - lzo_init() failed !!!\n");
	//		printf("(this usually indicates a compiler bug - try recompiling\nwithout optimizations, and enable '-DLZO_DEBUG' for diagnostics)\n");
	//	}
	//
	//
	//	//string s = "a really long test string with repeating words to test. a really long test string with repeating words to test. a really long test string with repeating words to test.";
	//	//string javaunzipped = FileUtils::unlz4Base64StringToString(javazipped);
	//	//log.error(javaunzipped);
	//
	//
	//	//atexit(SDL_Quit);
	//
	//
	//	string b64lzoFromServer = "AFM8P3htbCB2ZXJzaW9uPSIxLjAiIGVuY29kaW5nPSJVVEYtOCIgc3RhbmRhbG9uZT0ieWVzIiA/Pgo8IURPQ1RZUEUgYm9vc3Rfc2VyaWFsaXphdGlvbj4KPGJvb3N0X3NlcmlhbNQCCSBzaWduYXR1cmU9Iiu4AAc6OmFyY2hpdmUiKSQCABA0Ij4KPGcgY2xhc3NfaWQ9IjAiIHRyYWNraW5nX2xldmVsiAIn6AIAIDUiPgoJPHV1aWQ+OGQzYjMzMTUtMjMxNC00MDdhLWFmZmEtOWJlNTE1ZjhmYWMzPC91aAUPCgk8YnVpbHRJblR5cGU+MDwvKjgAAAMKCTxuYW1lPkZpbGxldCBHYW1lPC+EAgAWCgk8cnVsZXM+TWFrZSBhIGxpbmUgb2YgbWF0Y2hpbmcgY29sbyAgICoEAAtycyB0byBzY29yZSE8L7sHCgk8gAKXDzI8LygwACpkAAdBbW91bnRQZXJMfB4FR2FpbmVkPjMptAAzgAB0FwACZXh0UGllY2VFbmFibGVkPjE8L24uTAB8BAV1bWJlck9mTuwDBHNUb1Nob3dxDG42bAAECgk8aG9sZC58AS9MAGwlAmVzZXRI8AUBUm90YZhEATE8L3I0ZAAKCgk8Y2hhaW5SdWxlXyd1A0NoAmwSN2wAK9wAC0NoZWNrRW50aXJlTGlulDso4AAucAAw5wBSb3d8JS3IAHQCMKwAA0NvbHVtbjG4AMADMMQAAlJvd09y1wMwPC8wlAEndAAw7AAFRGlhZ29uYWx8VS3gACdoADDUAAxSZWN1cnNpdmVDb25uZWNlMHMxBAEzmAAwNwFUb3WEXQpCcmVha2VyQmxvY2tzoDQwOAM5sAAHCgk8Z3Jhdml0eYw9DW9ubHlNb3ZlRG93bkRpc2OqFWVkvAt4FSAKtAAABAoJPHBsYXlpbmdGaWVsZEdhcmJhZ2XsbTZoADTUAAFTcGF3mFFsEDHoACh8AHxiABZhcmREcm9wUHVuY2hUaHJvdWdoVG9Mb3dlc3RWYWxpZEdyaWRQb3NpcDBhCmggDMAAAAYKCTx0d29TcGFjZVdhbGxLaWNrQWxsb3egfDZoAAEKCTxkwEcx1AA2aAB0IWSIBUNsaW1iaW5nKaEBcDJcAAcKCTxmbGlwMTgwKaQALUQAjwRvb3It4gJmbC1MAISHBWFkeVRpY2tz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";
	//
	//
	//
	//
	//
	//
	//
	//	string xml = FileUtils::unlzoBase64StringToString(b64lzoFromServer);
	//
	//	string b64zip = FileUtils::zipStringToBase64String(xml);
	//	string b64lz4 = FileUtils::lz4StringToBase64String(xml);
	//
	//
	//	log.info("lzo length:"+to_string(b64lzoFromServer.length()));
	//	log.info("zip length:"+to_string(b64zip.length()));
	//	log.info("lz4 length:"+to_string(b64lz4.length()));
	//
	//	cleanup();
	//
	//	return;


	

	new GLUtils();
	
	


	new AudioManager();
	
	
	AudioManager::initAudioLibrary();
	
	

	GLUtils::checkSDLError("");

	
	
	
	
	



	//this is done before init game so we can put debug stuff
	console = new Console();
	console->fontSize = 16;
	rightConsole = new Console();
	rightConsole->justifyRight = true;
	rightConsole->fontSize = 16;


	

	GLUtils::initGL((char*)"\"bob's game\"");
	//GLUtils::initTWL();
	GLUtils::e();

	

	new ControlsManager();
	ControlsManager::initControllers();
	GLUtils::e();



	exit(0);




	BobFont::initFonts();
	GLUtils::e();

#ifndef ORBIS
	Main::StopTextInput();
#endif
	
	

	stateManager = new BobStateManager();
	GLUtils::e();

	//-------------------
	//init login GUI
	//-------------------

	log.debug("Init GUIs");


	

	glowTileBackgroundMenuPanel = new GlowTileBackgroundMenuPanel();
	glowTileBackgroundMenuPanel->init();


	

	logoScreenState = new LogoState();
	logoScreenState->init();
	loginState = new LoginState();
	loginState->init();
	loggedOutState = new LoggedOutState();
	loggedOutState->init();
	serversHaveShutDownState = new ServersHaveShutDownState();
	serversHaveShutDownState->init();
	createNewAccountState = new CreateNewAccountState();
	createNewAccountState->init();
	titleScreenState = new TitleScreenState();
	titleScreenState->init();
	youWillBeNotifiedState = new YouWillBeNotifiedState();
	youWillBeNotifiedState->init();
	GLUtils::e();

	//-------------------
	//init game
	//-------------------
	//log.debug("Init System");

	


	systemUtils = new System();
	GLUtils::e();
	
	System::initStats();
	GLUtils::e();
	System::initClockAndTimeZone();
	GLUtils::e();
	//-------------------
	//fill in the client session info to send to the server for debug/stats
	//this must be done after everything is initialized.
	//-------------------
	
	System::initSystemInfo();
	GLUtils::e();
	//makeGhostThread();
	//GLUtils::e();
	
	srand((int)(time(nullptr)));

	
	

	initGWEN();

	
	

	


	log.debug("Check for testing environment");

	//	bool debugOnLiveServer = true;
	//	if (debugOnLiveServer == false)
	//	{
	//		serverAddressString = BobNet::debugServerAddress;
	//		STUNServerAddressString = BobNet::debugSTUNServerAddress;
	//	}
	//	else
	{
		serverAddressString = BobNet::releaseServerAddress;
		STUNServerAddressString = BobNet::releaseSTUNServerAddress;
	}

	//for testing on second PC locally
	{
		BobFile f("/oldbob");
		if (f.exists())
		{
			clientUDPPortStartRange = 6499;
		}
	}

	{
		BobFile f("/localServer");
		if (f.exists())
		{
			serverAddressString = "192.168.1.3";// BobNet::debugServerAddress;
			STUNServerAddressString = "192.168.1.3";//BobNet::debugSTUNServerAddress;

			//stun server port is incremented by 1 to prevent bind conflict when running local server

			STUNServerUDPPort++;
		}
	}

	

	log.debug("Init BobNet");
	bobNet = new BobNet();

	

	bool rpg = false;

	BobFile f(getPath()+"rpg");
	if (f.exists() || rpg)
	{
		rpg = true;

		if (gameEngine != nullptr)
		{
			gameEngine->cleanup();
		}

		gameEngine = new BGClientEngine();
		stateManager->pushState(gameEngine);
		//Engine::setClientGameEngine(gameEngine);
		gameEngine->init();

		//bobNet->addEngineToForwardMessagesTo(gameEngine);

		if (previewClientInEditor == false)
		{
			bool didIntro = true; //FileUtils.doesDidIntroFileExist();

			if (didIntro == false)
			{
				introMode = true;

				log.debug("Setup Intro");

				gameEngine->statusBar->gameStoreButton->setEnabled(false);
				gameEngine->statusBar->ndButton->setEnabled(false);
				gameEngine->statusBar->stuffButton->setEnabled(false);
				gameEngine->statusBar->moneyCaption->setEnabled(false);
				gameEngine->statusBar->dayCaption->setEnabled(false);

				gameEngine->cinematicsManager->fadeFromBlack(10000);

				//gameEngine->mapManager->changeMap("ALPHABobElevator", "center");
				gameEngine->mapManager->changeMap("ALPHABobsApartment", "atDesk");
				//gameEngine.mapManager.changeMap("GENERIC1UpstairsBedroom1",12*8*2,17*8*2);

				//gameEngine->textManager->text("yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay <PLAYER>Yep  \"Yuu\" yay. Yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay yay. a aa aaa aaaa aaaaa aaaaaa aaaaaaa aaaaaaaa aaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa <.><1><PLAYER>bob! yay, \"bob\" yay! <.><0><PLAYER>\"Yuu\" yay, nD. yay yay \"bob's game\" yay- bob's? yay \"bob's\" yay bob's game<1>yep");

			}
			else
			{
				stateManager->pushState(loginState);
			}

			//gameEngine->mapManager->changeMap("ALPHABobElevator", "center");
			//gameEngine->mapManager->changeMap("TOWNYUUDownstairs", 30, 18);


		}
	}
	else
	{
		

		log.debug("Create BobsGame");
		bobsGame = new BobsGame();
		
		stateManager->pushState(bobsGame);
		bobsGame->init();

	}


	

	System::initTimers();


	checkVersion();


	System::initTimers();
	GLUtils::e();

	

	if (rpg)
	{
		if (previewClientInEditor == false)
		{
			//stateManager->pushState(controlsScreenState);
			//showControlsImage();

			//stateManager->pushState(legalScreenState);
			//doLegalScreen();

			stateManager->pushState(logoScreenState);
		}
	}
	else
	{
		stateManager->pushState(logoScreenState);
	}

	//GLUtils::e();
	//tcpServerConnection = new BGClientTCP(gameEngine);
	//GLUtils::e();

//#ifdef _DEBUG
//	string s = "hello this is a test asdu fasigdf aiohsdf aoisbd gab srihagb isrhbagiusrhb gkjbazarhgbszjkhvgaoishb ashgb uaysb gjabs ougyab eriabslkbgvaoisugh kasbgvjahsidf aslkbasdhga isbga isbr gasbd sg jkseba lkgsdboiags ekjaslgbaisueabhs lgkjahsr jagbrsouigbaisbrgabfoiguas rabg riahbg sirhbgalisrbga isrhbgalisrbg iasrbga lisrhb galisrbg lahsbrgiaubse lagijbse rlkaghbsr iugab srlijabg lsrbga lisrubg ailusrbg alisurbg laiusrbilguabisurgliaubsrlgba bg liseba glsgb asiugejhgdrigshrd";
//	string z = FileUtils::zipStringToBase64String(s);
//	log.debug(z);
//	string u = FileUtils::unzipBase64StringToString(z);
//	log.debug(u);
//#endif

//	GameType *s = new GameType();
//	s->tetsosumi();
//	string zip = s->toBase64GZippedXML();
//	string xml = FileUtils::unzipBase64StringToString(zip);
//		log.info(xml);

#ifndef _DEBUG
	//GLUtils::toggleFullscreen();
#endif


	//ImGui_ImplSdl_Init(GLUtils::window);

	

}


//=========================================================================================================================
void Main::initGWEN()
{//=========================================================================================================================

	log.debug("Init GWEN");

	uint64_t start=0, now=0;
	start = System::getPerformanceCounter();

#ifndef ORBIS
	gwenRenderer = new Gwen::Renderer::OpenGL_TruetypeFont();
	gwenRenderer->Init();
	gwenRenderer->SetDrawColor(Gwen::Color(255, 0, 0, 255));
	gwenSkin = new Gwen::Skin::TexturedBase(gwenRenderer);
	string path = Main::getPath();
	gwenSkin->Init(path + "data/DefaultSkin.png");
	gwenSkin->SetDefaultFont(Gwen::Utility::StringToUnicode(path + "data/fonts/Lato-Medium.ttf"), 16);
	gwenCanvas = new Gwen::Controls::Canvas(gwenSkin);
	gwenCanvas->SetSize(GLUtils::getViewportWidth(), GLUtils::getViewportHeight());
	gwenCanvas->SetDrawBackground(false);
#else
	gwenRenderer = new Gwen::Renderer::GwenRendererPS4();
#endif


#ifndef ORBIS
	gwenInput = new Gwen::Input::GwenSDL2();
	gwenInput->Initialize(gwenCanvas);
#else
	gwenInput = new Gwen::Input::GwenInputPS4();
	//gwenInput->Initialize(gwenCanvas);
#endif

	now = System::getPerformanceCounter();
	log.debug("Init GWEN took " + to_string((double)((now - start) * 1000) / System::GetPerformanceFrequency()) + "ms");
}



//=========================================================================================================================
void Main::loadGlobalSettingsFromXML()
{//=========================================================================================================================

	log.debug("Load global settings");

	string userDataPathString = FileUtils::appDataPath + "";
	//Path userDataPath(userDataPathString);
	BobFile userDataPathDir(userDataPathString);
	if (userDataPathDir.exists() == false)userDataPathDir.createDirectories();

	string filename = "globalSettings.xml";
	BobFile f(userDataPathString + filename);
	if (f.exists())
	{
		ifstream t(userDataPathString + filename);
		string str;

		t.seekg(0, ios::end);
		str.reserve((size_t)t.tellg());
		t.seekg(0, ios::beg);

		str.assign((istreambuf_iterator<char>(t)),
			istreambuf_iterator<char>());

		stringstream ss;
		ss << str;

		boost::archive::xml_iarchive ia(ss);
		GlobalSettings gs;
		try
		{
			ia >> BOOST_SERIALIZATION_NVP(gs);

			log.info("Global settings loaded.");
		}
		catch (exception)
		{
			gs = GlobalSettings();
			log.error("Could not unserialize GlobalSettings");
		}

		GlobalSettings *s = new GlobalSettings();
		*s = gs;
		globalSettings = s;

	}
	else
	{
		globalSettings = new GlobalSettings();

		log.warn("Global settings not found.");
	}



}

//=========================================================================================================================
void Main::saveGlobalSettingsToXML()
{//=========================================================================================================================

	string userDataPathString = FileUtils::appDataPath + "";
	//Path userDataPath(userDataPathString);
	BobFile userDataPathDir(userDataPathString);
	if (userDataPathDir.exists() == false)userDataPathDir.createDirectories();

	string filename = "globalSettings.xml";

	//Path filePath(userDataPathString + filename);
	BobFile file(userDataPathString + filename);

	if (file.exists())
	{
		file.deleteFile();
	}

	{
		std::stringstream ss;
		boost::archive::xml_oarchive oarchive(ss);

		GlobalSettings s;
		s = *globalSettings;
		oarchive << BOOST_SERIALIZATION_NVP(s);

		ofstream outputFile;
		outputFile.open(userDataPathString + filename, ofstream::out);
		outputFile << ss.str() << endl;
		outputFile.close();
	}

}

////===========================================================================================================================
//void Main::e(const string& &whereErrorOccurredString)
//{//===========================================================================================================================
//
//	GLUtils::e(whereErrorOccurredString);
//
//}
//
//===========================================================================================================================
//void Main::e()
//{//===========================================================================================================================
//
//	GLUtils::checkSDLError("");
//	GLUtils::checkGLError("");
//
//}

bool Main::introMode = false;
bool Main::previewClientInEditor = false;

//==========================================================================================================================
void Main::initClientEngine()
{//=========================================================================================================================

}


//      string Main::facebookID = "";
//      string Main::facebookAccessToken = "";
//      bool Main::_gotFacebookResponse = false;
//
//      //The following method was originally marked 'synchronized':
//      void Main::setGotFacebookResponse_S(bool b)
//      {
//         _gotFacebookResponse = b;
//      }
//
//      //The following method was originally marked 'synchronized':
//      bool Main::getGotFacebookResponse_S()
//      {
//         return _gotFacebookResponse;
//      }
//
//      void Main::setFacebookCredentials(const string &facebookID, const string &accessToken)
//      { //=========================================================================================================================
//         Main::facebookID = facebookID;
//         Main::facebookAccessToken = accessToken;
//
//         setGotFacebookResponse_S(true);
//      }

//==========================================================================================================================
void Main::whilefix()
{//==========================================================================================================================
	mainObject->processEvents();
	mainObject->stateManager->getCurrentState()->resetPressedButtons();

	bool frame = false;

	while (frame == false)
	{
		System::updateRenderTimers();
		System::updateStats();

		if (System::getTotalRenderTicksPassed() >= 16)
		{
			System::resetTotalRenderTicksPassed();
			System::updateUpdateTimers();

			console->update();
			rightConsole->update();
			bobNet->tcpServerConnection.update();

			if (dynamic_cast<Engine*>(mainObject->stateManager->getCurrentState()) != NULL)
			{
				((Engine*)mainObject->stateManager->getCurrentState())->getCaptionManager()->update();
			}


			frame = true;

			mainObject->render();
			doSwap();
		}
		justDelay(10);
	}

	mainObject->stateManager->getCurrentState()->setButtonStates();
}

//==========================================================================================================================
void Main::delay(int ticks)
{//==========================================================================================================================

 	long long startTime = System::currentHighResTimer();
 	int ticksPassed = 0;

	while (ticksPassed < ticks)
	{
		long long currentTime = System::currentHighResTimer();
		ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		whilefix();
	}
}
//=========================================================================================================================
void Main::justDelay(int ticks)
{//=========================================================================================================================

#ifndef ORBIS
	SDL_Delay(2);
#else
	sceKernelUsleep(ticks);
#endif
}


void Main::StartTextInput()
{
#ifndef ORBIS
	SDLStartTextInput();
#else
	
#endif	
}

void Main::StopTextInput()
{
#ifndef ORBIS
	SDLStopTextInput();
#else
	
#endif

}

//=========================================================================================================================
void Main::oldrender()
{//=========================================================================================================================
	GLUtils::old_clear();
	GLUtils::old_render();
}

//bool show_test_window = true;
//bool show_another_window = false;
//ImVec4 clear_color = ImColor(0, 0, 0);
//=========================================================================================================================
void Main::updateMain()
{//=========================================================================================================================

//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//	{
//		// .. give it to the input handler to process
//		GwenInput.ProcessMessage(msg);
//	}
	

	

#ifdef ORBIS
	update();
#endif

	
	
	processEvents();
	//GLUtils::e();
	stateManager->getCurrentState()->updateControls();
	//GLUtils::e();
	
	doScreenShotCheck();
	doResizeCheck();


	
	stateManager->update();
	//GLUtils::e();

	
	
	console->update();
	

	rightConsole->update();

	
	//GLUtils::e();
	//bobNet->update();

	
	
//	ImGui_ImplSdl_NewFrame(GLUtils::window);
//
//	// 1. Show a simple window
//	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
//	{
//		static float f = 0.0f;
//		ImGui::Text("Hello, world!");
//		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
//		ImGui::ColorEdit3("clear color", (float*)&clear_color);
//		if (ImGui::Button("Test Window")) show_test_window ^= 1;
//		if (ImGui::Button("Another Window")) show_another_window ^= 1;
//		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//	}
//
//	// 2. Show another simple window, this time using an explicit Begin/End pair
//	if (show_another_window)
//	{
//		ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
//		ImGui::Begin("Another Window", &show_another_window);
//		ImGui::Text("Hello");
//		ImGui::End();
//	}
//
//	// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
//	if (show_test_window)
//	{
//		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
//		ImGui::ShowTestWindow(&show_test_window);
//	}
	

}

//=========================================================================================================================
void Main::renderMain()
{//=========================================================================================================================

	glClear(GL_COLOR_BUFFER_BIT);

	//stateManager->render();

	//GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//console->render();
	//rightConsole->render();

	GLUtils::drawFilledRect(255, 255, 255, 0, 1, 0, 1, 1);


#ifndef ORBIS
	if (error_console_on)ERROR_draw_error_console();
	DEBUG_draw_overlays();

	//ImGui::Render();

#endif


}

//=========================================================================================================================
void Main::doSwap()
{//=========================================================================================================================
#ifndef ORBIS
	SDL_GL_SwapWindow(GLUtils::window);
#else

	eglSwapBuffers(GLUtils::display, GLUtils::surface);

	//log.debug("flip");

	//mainObject->m_baseService.m_debugWindow.notifyPhase(common::Service::DebugWindow::kBeginFlip);
	//getGraphicsContext()->flip(0);
	//mainObject->m_baseService.m_debugWindow.notifyPhase(common::Service::DebugWindow::kEndFlip);

	//log.debug("flip done");

//	for(int i=0;i<BobTexture::texturesToDeleteAfterRender.size();i++)
//	{
//		delete BobTexture::texturesToDeleteAfterRender.get(i);
//	}
//	BobTexture::texturesToDeleteAfterRender.clear();

#endif
}

//=========================================================================================================================
void Main::mainLoop()
{ //=========================================================================================================================

	
	log.debug("Begin Main Loop");

	mainLoopStarted = true;

	while (quit == false)
	{
		//------------------------------
		//END OLD MAIN LOOP
		//------------------------------
		System::updateRenderTimers();
		System::updateStats();
		
		//GLUtils::e();

		//        if (serversAreShuttingDown)
		//        {
		//            GLUtils::drawFilledRect(0, 0, 0, 0, GLUtils::getViewportWidth(), 0, GLUtils::getViewportHeight(), 0.2f);
		//            GLUtils::drawOutlinedString("The servers are shutting down soon for updating.", GLUtils::getViewportWidth() / 2 - 60, GLUtils::getViewportHeight() / 2 - 12, Color::white);
		//        }

		//		if (GLUtils::isActive() == false && debugMode == false)
		//		{
		//			GLUtils::drawFilledRect(0, 0, 0, 0, (float)GLUtils::getViewportWidth(), 0, (float)GLUtils::getViewportHeight(), 0.5f);
		//			GLUtils::drawOutlinedString("Low power mode. Click to resume.", (float)GLUtils::getViewportWidth() / 2 - 70, (float)GLUtils::getViewportHeight() / 2 - 12, Color::white);
		//
		//			Sleep(16 * 3);//skip 3 frames
		//
		//			if (GLUtils::isVisible())
		//			{
		//				update();
		//				render();
		//				SDL_GL_SwapWindow(GLUtils::window);
		//			}
		//			else
		//			{
		//				GLUtils::processMessages();
		//			}
		//		}
		//		else
		{
			if (GLUtils::usingVSync == true)
			{
				System::updateUpdateTimers();
				//this just lowers cpu usage
				//Sleep(2); //TODO: vary this based on system speed
				updateMain();
				renderMain();
				doSwap();
				//System::framesrendered++;
			}
			else
			{

				if (GLUtils::noVSync_UpdateAndRenderEveryFrame || System::getTotalRenderTicksPassed() >= 16)
				{
					System::resetTotalRenderTicksPassed();
					System::updateUpdateTimers();
					updateMain();
					renderMain();
					doSwap();
					//System::framesrendered++;
				}
				else
				{
					renderMain();
					doSwap();
					//System::framesrendered++;
				}

				//TODO: vary this based on system speed
				if (GLUtils::noVSync_DelayOff == false)justDelay(2);

				/*
				try
				{
					//this actually regulates framerate
					Thread.sleep(6);//16);//TODO: vary this based on system speed

					//no ghost thread
					//30 = 30 fps solid, jitter but no stutter, very smooth though **(same for with ghost thread)

					//ghost thread
					//8 = ~ 120-125 fps, starting to get a little bit of stutter
					//7 = ~ 130-140 fps, no stutter, tiny bit choppy for some reason
					//6 = ~ 150 fps, no stutter
					//5 = ~ 200 fps, no stutter
					//4 = ~ 250 fps, no stutter

					//1 = 950 fps, very smooth

					Thread.yield();

				}
				catch(Exception e){e.printStackTrace();}
				*/
			}

			//System::calculate_fps();

			GLUtils::e("End main loop");
		}

		GLUtils::e();
	}
}

bool Main::screenShotKeyPressed = false;
bool Main::resize = false;

//=========================================================================================================================
void Main::doResizeCheck()
{ //=========================================================================================================================

	if ((getControlsManager()->KEY_RALT_HELD && getControlsManager()->key_RETURN_Pressed()) || getControlsManager()->key_F11_Pressed())
	{

		log.debug("Toggled fullscreen");

		GLUtils::toggleFullscreen();
	}

	if (resize == true)
	{
		resize = false;

		//reset GL model matrix, etc.

		log.debug("Resized window");

		GLUtils::doResize();
	}
}

//=========================================================================================================================
void Main::doScreenShotCheck()
{ //=========================================================================================================================

	bool takeScreenShot = false;


#ifdef _DEBUG
	if (getControlsManager()->key_PRINTSCREEN_Pressed() || getControlsManager()->key_F10_Pressed())
	{
		if (screenShotKeyPressed == false)
		{
			screenShotKeyPressed = true;
			takeScreenShot = true;
		}
	}
	else
	{
		screenShotKeyPressed = false;
	}
#else
	if (getControlsManager()->key_PRINTSCREEN_Pressed() || getControlsManager()->key_F12_Pressed())
	{
		if (screenShotKeyPressed == false)
		{
			screenShotKeyPressed = true;
			takeScreenShot = true;
		}
	}
	else
	{
		screenShotKeyPressed = false;
	}
#endif



	if (takeScreenShot)
	{

		if (mainObject->gameEngine != nullptr)mainObject->gameEngine->audioManager->playSound("screenShot", 1.0f, 1.0f, 1);

		time_t t = time(0); // get time now
		struct tm * now = localtime( & t );
		//cout << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << endl;

		//string imageName = "bobsgame-" + (new SimpleDateFormat("yyyy-MM-dd-HH-mm-ss"))->format(Calendar::getInstance().getTime()) + ".png";
		string fileName = string(Main::getPath())+"screenshot"+to_string(now->tm_year + 1900)+to_string(now->tm_mon + 1) +to_string(now->tm_mday)+to_string(now->tm_hour) + to_string(now->tm_min) + to_string(now->tm_sec) +".png";

		//if (System::getProperty("os.name")->contains("Win"))
		{
			log.info("Saved screenshot to " + fileName);

			Main::console->add("Saved screenshot to "+ fileName, 3000, BobColor::green);
			//getFileName = System::getProperty("user.home") + "/" + "Desktop" + "/" + imageName;
		}
		//  				else
		//  				{
		//  					Console::add("Saved screenshot in home folder.",Color::green,3000);
		//  					//getFileName = System::getProperty("user.home") + "/" + imageName;
		//  				}
#ifndef ORBIS
		int w = GLUtils::getRealWindowWidth();
		int h = GLUtils::getRealWindowHeight();


		glReadBuffer(GL_FRONT);
		u8 *buffer = new u8[w * h * 4];
		glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		u8 *flipdata = new u8[w * h * 4];

		for (int y = 0; y<h; y++)
			for (int x = 0; x<w; x++)
			{
				flipdata[(((y*w) + x) * 4) + 0] = buffer[(((((h - 1) - y)*w) + x) * 4) + 0];//bgra
				flipdata[(((y*w) + x) * 4) + 1] = buffer[(((((h - 1) - y)*w) + x) * 4) + 1];
				flipdata[(((y*w) + x) * 4) + 2] = buffer[(((((h - 1) - y)*w) + x) * 4) + 2];//bgra
				flipdata[(((y*w) + x) * 4) + 3] = buffer[(((((h - 1) - y)*w) + x) * 4) + 3];

			}
		SDL_Surface *s = SDL_CreateRGBSurfaceFrom(flipdata, w, h, 32, w * 4, GLUtils::rmask, GLUtils::gmask, GLUtils::bmask, GLUtils::amask);// 0x0000FF00, 0x00FF0000, 0xFF000000, 0x000000FF);
		IMG_SavePNG(s, fileName.c_str());
		SDL_FreeSurface(s);
		delete[] buffer;
		delete[] flipdata;
#else
		
#endif

	}

}

#ifndef ORBIS
//==========================================================================================================================
void Main::printEvent(const SDL_Event* e)
{//==========================================================================================================================
	if (e->type == SDL_WINDOWEVENT)
	{
		string wid = to_string(e->window.windowID);

		switch (e->window.event)
		{
		case SDL_WINDOWEVENT_SHOWN:
			log.debug("Window "+wid+" shown");
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			log.debug("Window "+wid+" hidden");
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			log.debug("Window "+wid+" exposed");
			break;
		case SDL_WINDOWEVENT_MOVED:
			log.debug("Window "+wid+" moved to " + to_string(e->window.data1) + " " + to_string(e->window.data2));
			break;
		case SDL_WINDOWEVENT_RESIZED:
			log.debug("Window "+wid+" resized to " + to_string(e->window.data1) + " " + to_string(e->window.data2));
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			log.debug("Window "+wid+" size changed to "+to_string(e->window.data1)+" "+to_string(e->window.data2));
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			log.debug("Window "+wid+" minimized");
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			log.debug("Window "+wid+" maximized");
			break;
		case SDL_WINDOWEVENT_RESTORED:
			log.debug("Window "+wid+" restored");
			break;
		case SDL_WINDOWEVENT_ENTER:
			log.debug("Mouse entered window "+wid);
			break;
		case SDL_WINDOWEVENT_LEAVE:
			log.debug("Mouse left window "+wid);
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			log.debug("Window "+wid+" gained keyboard focus");
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			log.debug("Window "+wid+" lost keyboard focus");
			break;
		case SDL_WINDOWEVENT_CLOSE:
			log.debug("Window "+wid+" closed");
			break;
		default:
			log.debug("Window "+wid+" got unknown event "+to_string(e->window.event));
			break;
		}
	}
}

#else

#endif


//==========================================================================================================================
void Main::processEvents()
{//==========================================================================================================================


#ifndef ORBIS
	SDL_Event event;

	//While there are events to handle
	while (SDL_PollEvent(&event))
	{

		//printEvent(&event);

		//If the user has Xed out the window
		if (event.type == SDL_QUIT)
		{
			//Quit the program
			Main::quit = true;
		}
		else
			//Window event occured
			if (event.type == SDL_WINDOWEVENT)
			{
				switch (event.window.event)
				{
					//Get new dimensions and repaint on window size change
				case SDL_WINDOWEVENT_SIZE_CHANGED:
				{
					//int width = event.window.data1;
					//int height = event.window.data2;
					resize = true;
				}
				break;

				//Repaint on exposure
				case SDL_WINDOWEVENT_EXPOSED:
					break;

					//Mouse entered window
				case SDL_WINDOWEVENT_ENTER:
					break;

					//Mouse left window
				case SDL_WINDOWEVENT_LEAVE:
					break;

					//Window has keyboard focus
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					break;

					//Window lost keyboard focus
				case SDL_WINDOWEVENT_FOCUS_LOST:
					break;

					//Window minimized
				case SDL_WINDOWEVENT_MINIMIZED:
					break;

					//Window maxized
				case SDL_WINDOWEVENT_MAXIMIZED:
					break;

					//Window restored
				case SDL_WINDOWEVENT_RESTORED:
					break;
				}
			}
			else
			{

				stateManager->getCurrentState()->getActiveControlsManager()->events.add(event);

				gwenInput->ProcessEvent(event);
				//ImGui_ImplSdl_ProcessEvent(&event);
			}

	}
#else

#endif

}


//==========================================================================================================================
ControlsManager * Main::getControlsManager()
{//==========================================================================================================================
	return stateManager->getCurrentState()->getControlsManager();
}


//void OnResize(int w, int h) {
//
//   //textureWidth = (float)w;
//   //textureHeight = (float)h;
//
//   setGLWindow(w, h, Surf_Display);
//
//}
//bool setGLWindow(int width, int height, SDL_Surface * Surf_Display)
//{
//   if ((Surf_Display = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_OPENGL | SDL_RESIZABLE)) == NULL) {
//      return false;
//   }
//
//   glClearColor(0, 0, 0, 0);
//   glClearDepth(1.0f);
//
//   glViewport(0, 0, width, height);
//
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//
//   glOrtho(0, width, height, 0, 1, -1);
//
//   glMatrixMode(GL_MODELVIEW);
//
//   glEnable(GL_TEXTURE_2D);
//
//   glLoadIdentity();
//
//   return true;
//}

//==========================================================================================================================
void Main::doLegalScreen()
{ //=========================================================================================================================

  //
  //			if ((new File(FileUtils::cacheDir + "session"))->exists() == false)
  //			{
  //
  //				{
  //				//if(BobNet.debugMode==false)
  //
  //					log.info("Legal Screen...");
  //
  //					LegalScreen *legalScreen = new LegalScreen();
  //					GUI *legalScreenGUI = new GUI(legalScreen, GLUtils::TWLrenderer);
  //					legalScreenGUI->applyTheme(GLUtils::TWLthemeManager);
  //
  //					while (legalScreen->getClickedOK_S() == false)
  //					{
  //
  //						glClear(GL_COLOR_BUFFER_BIT);
  //
  //
  //						legalScreen->update();
  //						legalScreenGUI->update();
  //
  //						if ((System::isCloseRequested() || (System::debugMode == true && Keyboard::isKeyDown(Keyboard::KEY_ESCAPE))) || legalScreen->getClickedCancel_S() == true)
  //						{
  //							legalScreen->destroy();
  //							GLUtils::TWLthemeManager->destroy();
  //							System::destroy();
  //							AL::destroy();
  //							Main::exit();
  //						}
  //
  //						System::sync(60);
  //						System::update();
  //						doResizeCheck();
  //
  //					}
  //
  //					legalScreen->destroy();
  //					glClear(GL_COLOR_BUFFER_BIT);
  //
  //					log.info("Accepted Legal Screen.");
  //
  //				}
  //
  //			}
}

//==========================================================================================================================
void Main::showControlsImage()
{ //=========================================================================================================================

  //
  //			if ((new File(FileUtils::cacheDir + "session"))->exists() == false)
  //			{
  //
  //				{
  //				//if(BobNet.debugMode==false)
  //					KeyboardScreen *keyboardScreen = new KeyboardScreen();
  //					GUI *keyboardScreenGUI = new GUI(keyboardScreen, GLUtils::TWLrenderer);
  //					keyboardScreenGUI->applyTheme(GLUtils::TWLthemeManager);
  //
  //					keyboardScreen->okButton->setVisible(true);
  //					keyboardScreen->setActivated(true);
  //
  //					while (keyboardScreen->getClickedOK_S() == false)
  //					{
  //						glClear(GL_COLOR_BUFFER_BIT);
  //
  //
  //						keyboardScreen->update();
  //						keyboardScreenGUI->update();
  //
  //
  //						System::sync(60);
  //						System::update();
  //					}
  //					keyboardScreen->destroy();
  //					glClear(GL_COLOR_BUFFER_BIT);
  //				}
  //
  //			}
}




string Main::path = "";


//==========================================================================================================================
string Main::getPath()
{//==========================================================================================================================

	if (path != "")return path;

//#ifdef ORBIS
//	path = "/app0/";
//	return path;
//#endif


	string versionTextPath = "version.txt";


	if (BobFile(versionTextPath).exists() == false)
	{
		log.warn("Could not find " + versionTextPath);

		versionTextPath = "../version.txt";

		if (BobFile(versionTextPath).exists() == false)
		{
			log.warn("Could not find " + versionTextPath);

			string exePath = string(FileUtils::getBasePath());//this is where the .exe is run from.i.e. bobsgame/DebugVS/

			versionTextPath = exePath + "version.txt";

			if (BobFile(versionTextPath).exists() == false)
			{
				log.warn("Could not find " + versionTextPath);

				string cwd = FileUtils::getWorkingDir();//this is the current working dir i.e. bobsgame/

				versionTextPath = cwd + "version.txt";

				if (BobFile(versionTextPath).exists() == false)
				{
					log.warn("Could not find " + versionTextPath);

					versionTextPath = exePath + "../" + "version.txt";

					if (BobFile(versionTextPath).exists() == false)
					{

						log.warn("Could not find " + versionTextPath);

						versionTextPath = cwd + "../" + "version.txt";

						if (BobFile(versionTextPath).exists() == false)
						{

							log.warn("Could not find " + versionTextPath);
							//log.error("Could not find version.txt in path");
							return "./";
						}
						else
						{
							path = cwd + "../";
							log.info("Found " + path + "version.txt");
							return path;
						}
					}
					else
					{
						path = exePath + "../";
						log.info("Found " + path + "version.txt");
						return path;
					}
				}
				else
				{
					path = cwd;
					log.info("Found " + path + "version.txt");
					return path;
				}
			}
			else
			{
				path = exePath;
				log.info("Found " + path + "version.txt");
				return path;
			}
		}
		else
		{
			path = "../";
			log.info("Found " + path + "version.txt");
			return path;
		}
	}
	else
	{
		path = "";
		log.info("Found " + path + "version.txt");
		return path;
	}
}

#if defined(__LINUX__)
#include "stdlib.h"
#endif

//class ZipTest
//{
//public:
//	static void onDecompressError(const void* pSender, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string>& info)
//	{
//
//
//	}
//};

//==========================================================================================================================
void Main::checkVersion()
{//==========================================================================================================================


	log.debug("Version Check");

#ifndef ORBIS
	bool windows = false;
	bool macos = false;
	bool linux = false;

#if defined(__WINDOWS__)
	windows = true;
#endif
#if defined(__LINUX__)
	linux = true;
#endif
#if defined(__MACOSX__)
	macos = true;
#endif

	int localVersion = 0;

#if defined(__WINDOWS__) || defined(__LINUX__) || defined(__MACOSX__)
    /*
     dyld: Symbol not found: _clock_gettime
     Referenced from: /usr/local/lib/libPocoFoundationd.45.dylib (which was built for Mac OS X 10.12)
     Expected in: /usr/lib/libSystem.B.dylib
     */

	//if not in itch
	string exePath = string(SDL_GetBasePath());
	log.info("SDL_GetBasePath(): " + exePath);//this is where the .exe is run from.i.e. bobsgame/DebugVS/

	string pocoPath = Path::current();
	log.info("Poco::Path::current():" + pocoPath);//this is the current working dir i.e. bobsgame/

	log.info("SDL_GetPrefPath():" + string(SDL_GetPrefPath("Bob Corporation", "bob's game")));
	log.info("Poco::Path::home():" + Path::home());

	if (exePath.find("itch") != std::string::npos)
	{
		log.debug("'itch' found in path, skipping version check.");
	}
	else
	if(exePath.find("steam") != std::string::npos)
	{
		log.debug("'steam' found in path, skipping version check.");
	}
	else
	if (exePath.find("Steam") != std::string::npos)
	{
		log.debug("'Steam' found in path, skipping version check.");
	}
	else
	{

		try
		{
			File f(exePath+"bobsgame.old");
			if (f.exists())
			{
				f.remove();
				//Caption* c =
				//((Engine*)(getMain()->stateManager->getState()))->captionManager->newManagedCaption((int)(Caption::CENTERED_SCREEN), 0, 5000, "Update installed!", BobFont::ttf_oswald_32, BobColor::green, BobColor::clear, RenderOrder::OVER_GUI);
				//doesn't go away because we're not updating captionManager??

				Caption* c = new Caption(nullptr, Caption::Position::CENTERED_SCREEN,0 , 0, -1, "Update installed!", 16, true, BobColor::white, BobColor::clear);

				for (int i = 0; i < 40; i++)
				{
					System::updateRenderTimers();
					System::updateStats();
					System::updateUpdateTimers();
					c->update();
					c->render();
					SDL_GL_SwapWindow(GLUtils::window);
					SDL_Delay(100);
				}

			}
		}
		catch (Exception)
		{
			log.error("Error deleting bobsgame.old");
		}


		string versionTextPath = getPath() + "version.txt";
		if(File(versionTextPath).exists()==false)
		{
			log.error("Could not find version.txt");
			return;
		}

		//load version.txt, read number
		string versionString = FileUtils::loadTextFileFromExePathAndTrim("version.txt");
		log.info("Local version:" + versionString);
		Main::version = versionString;
		try
		{
			localVersion = stoi(versionString);
		}
		catch (exception)
		{
			log.error("Could not parse localVersion");
			return;
		}

		string serverString = "";

		try
		{
			//check bobsgame.com/version.php?
			URI uri("http://bobsgame.com/version.php");
			string path(uri.getPathAndQuery());
			if (path.empty()) path = "/";

			HTTPClientSession session(uri.getHost(), uri.getPort());
			session.setTimeout(Poco::Timespan(4, 0));
			HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
			HTTPResponse response;

			session.sendRequest(request);
			istream& rs = session.receiveResponse(response);
			//cout << response.getStatus() << " " << response.getReason() << endl;


			StreamCopier::copyToString(rs, serverString);
			log.info("Server version:" + serverString);
		}
		catch(Exception)
		{
			log.warn("Could not check version, no network connectivity?");
			return;
		}


		int serverVersion = -1;
		try
		{
			serverVersion = stoi(serverString);
		}
		catch (exception)
		{
			log.error("Could not parse serverVersion");
			return;
		}

		if (serverVersion > localVersion)
		{
			Main::console->add("Your version is out of date!", BobColor::red);
			Main::console->add("Your version: " + versionString, BobColor::red);
			Main::console->add("Latest version: " + serverString, BobColor::red);

			//bobsgame.exe can update itself, download latest.zip, rename itself, unzip in directory and overwrite, reopen itself, exit
			//in linux it doesnt even have to rename itself
			//in mac os who knows

			string exename = "";
			string zipname = "";
			if (windows)
			{

				exename = "bobsgame.exe";
				zipname = "http://bobsgame.com/latestWindows.zip";
			}

			if (macos)
			{
				exename = "bobsgame";
				zipname = "http://bobsgame.com/latestMacOS.zip";
			}

			if(linux)
			{
				exename = "bobsgame";
				zipname = "http://bobsgame.com/latestLinux.zip";
			}

			//if not in correct path quit
			if(File(exePath + exename).exists()==false)
			{
				log.error(exename+" not found in path:"+exePath);
				return;
			}

			//Caption* c = ((Engine*)(getMain()->stateManager->getState()))->captionManager->newManagedCaption((int)(Caption::CENTERED_SCREEN), 0, -1, "Update available! Press Space to download, Esc to skip.", BobFont::ttf_oswald_16, BobColor::white, BobColor::clear);
			Caption* c = new Caption(nullptr, Caption::Position::CENTERED_SCREEN, 0, 0, -1, "Update available! Press Space to download, Esc to skip.", 16, true, BobColor::white, BobColor::clear);
			System::updateRenderTimers();
			System::updateStats();
			System::updateUpdateTimers();
			c->update();
			c->render();
			SDL_GL_SwapWindow(GLUtils::window);

			bool skip = false;
			bool stop = false;
			while (stop == false)
			{
				mainObject->processEvents();
				mainObject->stateManager->getCurrentState()->resetPressedButtons();
				mainObject->stateManager->getCurrentState()->setButtonStates();

				if(getControlsManager()->key_SPACE_Pressed())
				{
					stop = true;
				}

				if (getControlsManager()->key_ESC_Pressed())
				{
					stop = true;
					skip = true;
				}
			}

			delete c;

			if (skip)return;

			//put caption in middle of screen, updating, press esc to skip
			log.info("Downloading update...");
			//c = ((Engine*)(getMain()->stateManager->getState()))->captionManager->newManagedCaption((int)(Caption::CENTERED_SCREEN), 0, -1, "Downloading update...", BobFont::ttf_oswald_32, BobColor::white, BobColor::clear);
			c = new Caption(nullptr, Caption::Position::CENTERED_SCREEN, 0, 0, -1, "Downloading update...", 16, true, BobColor::white, BobColor::clear);
			//Caption* c = ((Engine*)(getMain()->stateManager->getState()))->captionManager->newManagedCaption((int)(Caption::CENTERED_SCREEN), 0, -1, "Downloading update...", BobFont::ttf_oswald_32, Color::white, Color::black,RenderOrder::OVER_GUI);

			glClear(GL_COLOR_BUFFER_BIT);
			//Main::delay(100); //bobsGame doesn't render captionManager
			System::updateRenderTimers();
			System::updateStats();
			System::updateUpdateTimers();
			c->update();
			c->render();
			SDL_GL_SwapWindow(GLUtils::window);

			//download bobsgame.com/latestWindows.zip to working dir
			try
			{

				HTTPStreamFactory::registerFactory();


				URI zipuri(zipname);

				HTTPClientSession session(zipuri.getHost(), zipuri.getPort());
				string path(zipuri.getPathAndQuery());
				HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
				HTTPResponse response;
				session.setTimeout(Poco::Timespan(20, 0));
				session.sendRequest(request);
				//std::istream& rs =
                session.receiveResponse(response);
				//int contentlen = (int)response.getContentLength();

				FileStream fs(exePath + "update.zip", ios::out | ios::trunc | ios::binary);
				std::auto_ptr<std::istream> pStr(URIStreamOpener::defaultOpener().open(zipuri));
				StreamCopier::copyStream(*pStr.get(), fs);
				fs.close();
			}
			catch (Exception)
			{
				//std::cerr << exc.displayText() << std::endl;
				log.error("Could not download latest zip");
				c->setToBeDeletedImmediately();
				delete c;

				return;
			}

			try
			{


				//move all files to /old

				//delete /old at start

				//rename bobsgame.exe
				File(exePath + exename).renameTo(exePath + "bobsgame.old");
				File(exePath + exename).copyTo(exePath + exename);

			}
			catch (Exception)
			{
				log.error("Could not rename "+ exename);
			}

			try
			{
				//unzip latestZip to temp

#if defined(__LINUX__)
				int result = system(string("unzip \"" + exePath + "update.zip\"").c_str());
#else
				std::ifstream inp(exePath + "update.zip", std::ios::binary);
				//log.info("Opened ifstream");
				poco_assert(inp);
				//log.info("Assert ifstream");

				Decompress dec(inp, Poco::Path(exePath));
				//log.info("Create decompress object");
				//dec.EError += Poco::Delegate<ZipTest, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string> >(this, &ZipTest::onDecompressError);
				dec.decompressAllFiles();
				//dec.EError -= Poco::Delegate<ZipTest, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string> >(this, &ZipTest::onDecompressError);
				//log.info("decompressAllFiles();");
				inp.close();
				//log.info("close()");
#endif




			}
			catch (Exception)
			{
				log.error("Could not unzip update.zip");
			}

			//delete update.zip
			try
			{
				File(exePath + "update.zip").remove();
			}
			catch (Exception)
			{
				log.error("Could not delete update.zip");
			}
			try
			{

#if defined(__LINUX__) || defined(__MACOSX__)
                //int result =
                system(string("chmod 755 "+exePath + exename).c_str());
#endif
				//open bobsgame.exe
				File f = File(exePath + exename);
				if (f.exists() && f.canExecute())
				{
					c->setToBeDeletedImmediately();
					c->update();

					//Args args;
					std::vector<std::string> args;
					Process::launch(exePath + exename, args);
					//quit
					exit(0);
				}
				else
				{
					c->setText("Something went wrong while updating.  Please download manually.");
					c->update();
					c->render();
					SDL_GL_SwapWindow(GLUtils::window);

					log.error("Something went wrong while updating.  Please download manually.");
					SDL_Delay(5000);
					exit(0);
				}

			}
			catch (Exception)
			{
				log.error("Could not run "+ exename);
			}
		}
	}
#endif


#if defined(__WINDOWS__) && defined(_DEBUG)
	//open version.txt
	//increment it
	//save it back
	if (localVersion != 0)
	{
		int newVersion = localVersion + 1;

		ofstream outputFile;
		outputFile.open("version.txt", ofstream::out);//leave this without runpath, will always be run in windows debug in the proper cwd /bobsgame/
		outputFile << newVersion;
		outputFile.close();

		log.debug("Saved new version: " + to_string(newVersion));
	}
#endif

#endif
}

//==========================================================================================================================
void Main::makeGhostThread()
{ //=========================================================================================================================

  //			//ghost thread to prevent stuttering
  //			//this is due to windows aero, for some reason creating a ghost thread prevents it for some fucking reason
  //			new Thread([&] ()
  //			{
  //					try
  //					{
  //						Thread::currentThread().setName("ClientMain_ghostThreadToPreventAeroStutter");
  //					}
  //					catch (SecurityException e)
  //					{
  //						e->printStackTrace();
  //					}
  //
  //					while (exit == false)
  //					{
  //						try
  //						{
  //							delay(16); //this only seems to work at 16
  //
  //							//Thread.yield(); //high cpu usage
  //							//if(Display.isActive()==false)Display.processMessages();
  //						}
  //						catch (exception &e)
  //						{
  //							e.printStackTrace();
  //						}
  //					}
  //			}
  //		   ).start();
}


//==========================================================================================================================
void Main::cleanup()
{//=========================================================================================================================


	log.info("Cleaning up");

	AudioManager::cleanup();


	ControlsManager::cleanup();

	if (gameEngine != nullptr)
	{
		gameEngine->cleanup();
		delete gameEngine;
	}

	if (bobsGame != nullptr)
	{
		log.info("bobsGame cleanup");
		bobsGame->cleanup();
		delete bobsGame;
	}


	BobFont::cleanup();
	GLUtils::cleanup();

	delete bobNet;

#ifndef ORBIS
	log.info("SDLNet_Quit");
	SDLNet_Quit();
	//enet_deinitialize();
#else



	finalize();


#endif

	log.info("saveGlobalSettingsToXML");
	saveGlobalSettingsToXML();

	log.info("Exiting");



#ifndef ORBIS
	SDL_Quit();
#else



#endif

}

////==========================================================================================================================
//BGClientEngine* Main::getGameEngine()
//{//==========================================================================================================================
//	return gameEngine;
//}

//==========================================================================================================================
Main* Main::getMain()
{//==========================================================================================================================
	return mainObject;
}

//==========================================================================================================================
void Main::setMain(Main* c)
{//==========================================================================================================================
	mainObject = c;
}

//
//#define USE_ZLIB_MINIZIP 1
//
//#ifdef USE_ZLIB_MINIZIP
//
//
//#define dir_delimter '/'
//#define MAX_FILENAME 2048
//#define READ_SIZE 8192
//
//void Main::unZip(string file)
//{
//	// Open the zip file
//	unzFile *zipfile = unzOpen(file);
//	if (zipfile == NULL)
//	{
//		printf("%s: not found\n");
//		return -1;
//	}
//
//	// Get info about the zip file
//	unz_global_info global_info;
//	if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
//	{
//		printf("could not read file global info\n");
//		unzClose(zipfile);
//		return -1;
//	}
//
//	// Buffer to hold data read from the zip file.
//	char read_buffer[READ_SIZE];
//
//	// Loop to extract all files
//	uLong i;
//	for (i = 0; i < global_info.number_entry; ++i)
//	{
//		// Get info about current file.
//		unz_file_info file_info;
//		char filename[MAX_FILENAME];
//		if (unzGetCurrentFileInfo(
//			zipfile,
//			&file_info,
//			filename,
//			MAX_FILENAME,
//			NULL, 0, NULL, 0) != UNZ_OK)
//		{
//			printf("could not read file info\n");
//			unzClose(zipfile);
//			return -1;
//		}
//
//		// Check if this entry is a directory or file.
//		const size_t filename_length = strlen(filename);
//		if (filename[filename_length - 1] == dir_delimter)
//		{
//			// Entry is a directory, so create it.
//			printf("dir:%s\n", filename);
//			mkdir(filename);
//		}
//		else
//		{
//			// Entry is a file, so extract it.
//			printf("file:%s\n", filename);
//			if (unzOpenCurrentFile(zipfile) != UNZ_OK)
//			{
//				printf("could not open file\n");
//				unzClose(zipfile);
//				return -1;
//			}
//
//			// Open a file to write out the data.
//			FILE *out = fopen(filename, "wb");
//			if (out == NULL)
//			{
//				printf("could not open destination file\n");
//				unzCloseCurrentFile(zipfile);
//				unzClose(zipfile);
//				return -1;
//			}
//
//			int error = UNZ_OK;
//			do
//			{
//				error = unzReadCurrentFile(zipfile, read_buffer, READ_SIZE);
//				if (error < 0)
//				{
//					printf("error %d\n", error);
//					unzCloseCurrentFile(zipfile);
//					unzClose(zipfile);
//					return -1;
//				}
//
//				// Write data to file.
//				if (error > 0)
//				{
//					fwrite(read_buffer, error, 1, out); // You should check return of fwrite...
//				}
//			} while (error > 0);
//
//			fclose(out);
//		}
//
//		unzCloseCurrentFile(zipfile);
//
//		// Go the the next entry listed in the zip file.
//		if ((i + 1) < global_info.number_entry)
//		{
//			if (unzGoToNextFile(zipfile) != UNZ_OK)
//			{
//				printf("cound not read next file\n");
//				unzClose(zipfile);
//				return -1;
//			}
//		}
//	}
//
//	unzClose(zipfile);
//}
//#endif

//
//#define USE_MINIZ
//
//#ifdef USE_MINIZ
//
//#include "../lib/miniz-master/tinfl.c"
//#include <stdio.h>
//#include <limits.h>
//
//typedef unsigned char uint8;
//typedef unsigned short uint16;
//typedef unsigned int uint;
//
//#define my_max(a,b) (((a) > (b)) ? (a) : (b))
//#define my_min(a,b) (((a) < (b)) ? (a) : (b))
//
//static int tinfl_put_buf_func(const void* pBuf, int len, void *pUser)
//{
//	return len == (int)fwrite(pBuf, 1, len, (FILE*)pUser);
//}
//
//int Main::unZip(string file)
//{
//
//	int status;
//	FILE *pInfile, *pOutfile;
//	uint infile_size, outfile_size;
//	size_t in_buf_size;
//	uint8 *pCmp_data;
//	long long file_loc;
//
////	if (argc != 3)
////	{
////		printf("Usage: example4 infile outfile\n");
////		printf("Decompresses zlib stream in file infile to file outfile.\n");
////		printf("Input file must be able to fit entirely in memory.\n");
////		printf("example3 can be used to create compressed zlib streams.\n");
////		return EXIT_FAILURE;
////	}
//
//	// Open input file.
//	pInfile = fopen(file.c_str(), "rb");
//	if (!pInfile)
//	{
//		printf("Failed opening input file!\n");
//		return EXIT_FAILURE;
//	}
//
//	// Determine input file's size.
//	fseek(pInfile, 0, SEEK_END);
//	file_loc = ftell(pInfile);
//	fseek(pInfile, 0, SEEK_SET);
//
////	if ((file_loc < 0))// || (file_loc > INT_MAX))
////	{
////		// This is not a limitation of miniz or tinfl, but this example.
////		printf("File is too large to be processed by this example.\n");
////		return EXIT_FAILURE;
////	}
//
//	infile_size = (uint)file_loc;
//
//	pCmp_data = (uint8 *)malloc(infile_size);
//	if (!pCmp_data)
//	{
//		printf("Out of memory!\n");
//		return EXIT_FAILURE;
//	}
//	if (fread(pCmp_data, 1, infile_size, pInfile) != infile_size)
//	{
//		printf("Failed reading input file!\n");
//		return EXIT_FAILURE;
//	}
//
//	// Open output file.
//	pOutfile = fopen(file.c_str(), "wb");
//	if (!pOutfile)
//	{
//		printf("Failed opening output file!\n");
//		return EXIT_FAILURE;
//	}
//
//	printf("Input file size: %u\n", infile_size);
//
//	in_buf_size = infile_size;
//	status = tinfl_decompress_mem_to_callback(pCmp_data, &in_buf_size, tinfl_put_buf_func, pOutfile, TINFL_FLAG_PARSE_ZLIB_HEADER);
//	if (!status)
//	{
//		printf("tinfl_decompress_mem_to_callback() failed with status %i!\n", status);
//		return EXIT_FAILURE;
//	}
//
//	outfile_size = ftell(pOutfile);
//
//	fclose(pInfile);
//	if (EOF == fclose(pOutfile))
//	{
//		printf("Failed writing to output file!\n");
//		return EXIT_FAILURE;
//	}
//
//	printf("Total input bytes: %u\n", (uint)in_buf_size);
//	printf("Total output bytes: %u\n", outfile_size);
//	printf("Success.\n");
//	return EXIT_SUCCESS;
//	}
//#endif







#ifdef ORBIS

//=========================================================================================================================
int Main::initialize()
{//=========================================================================================================================






	SceFiosParams params = SCE_FIOS_PARAMS_INITIALIZER;

	/*E Provide required storage buffers. */
	params.opStorage.pPtr = g_OpStorage;
	params.opStorage.length = sizeof(g_OpStorage);
	params.chunkStorage.pPtr = g_ChunkStorage;
	params.chunkStorage.length = sizeof(g_ChunkStorage);
	params.fhStorage.pPtr = g_FHStorage;
	params.fhStorage.length = sizeof(g_FHStorage);
	params.dhStorage.pPtr = g_DHStorage;
	params.dhStorage.length = sizeof(g_DHStorage);

	params.pathMax = MAX_PATH_LENGTH;

	params.pVprintf = vprintf;
	params.pMemcpy = memcpy;



	 sceFiosInitialize(&params);




	char filename[] = "/app0/fios2_simple.txt";
	char output[] = "SAMPLE OUTPUT\n";
	char *pInput = NULL;
	SceFiosSize outputSize = (SceFiosSize)(strlen(output) + 1);
	SceFiosSize inputSize = 0;
	SceFiosSize result = 0;
	SceFiosFH writeFH = 0;
	SceFiosOp op[3] = { 0,0,0 };
	SceFiosOpenParams openParams = SCE_FIOS_OPENPARAMS_INITIALIZER;
	int err;

	/*E Issue 3 async ops: open a file, write a line of text, and close it. */
	openParams.openFlags = SCE_FIOS_O_WRONLY | SCE_FIOS_O_CREAT | SCE_FIOS_O_TRUNC;

	op[0] = sceFiosFHOpen(NULL, &writeFH, filename, &openParams);
	assert(op[0] != SCE_FIOS_OP_INVALID);
	op[1] = sceFiosFHWrite(NULL, writeFH, output, outputSize);
	assert(op[1] != SCE_FIOS_OP_INVALID);
	op[2] = sceFiosFHClose(NULL, writeFH);
	assert(op[2] != SCE_FIOS_OP_INVALID);



	/*E Wait for an op to complete, get the result of it, and delete the op. */
	result = sceFiosOpSyncWait(op[0]);
	assert(result == SCE_FIOS_OK);

	/*E Wait for an op to complete, get the result of it, and then manually delete the op. */
	result = sceFiosOpWait(op[1]);
	assert(result == SCE_FIOS_OK);
	sceFiosOpDelete(op[1]);

	/*E Poll for an op to complete, get its result, and then delete it. */
	while (!sceFiosOpIsDone(op[2]))
	{
		/*E Sleep to avoid consuming too many CPU cycles */
		sceKernelUsleep(1);
	}
	result = sceFiosOpGetError(op[2]);
	assert(result == SCE_FIOS_OK);
	sceFiosOpDelete(op[2]);

	/*E Synchronously find the file size. */
	inputSize = sceFiosFileGetSizeSync(NULL, filename);
	assert(inputSize == outputSize);

	/*E Synchronously read the text from the file. */
	pInput = (char*)malloc((size_t)inputSize);
	assert(pInput != NULL);
	result = sceFiosFileReadSync(NULL, filename, pInput, inputSize, 0);
	assert(result == inputSize);
	assert(!strcmp(pInput, output));
	free(pInput);

	/*E Delete the file. */
	err = sceFiosDeleteSync(NULL, filename);
	assert(err == SCE_FIOS_OK);


	





















	int ret;
	(void)ret;

	m_previousTime = 0;

	m_selectedUserId = sss::kInvalidUserId;


//	SampleUtil::Graphics::GraphicsContextOption* graphicsOption = NULL;
//	SampleUtil::Audio::AudioContextOption* audioOption = NULL;
//	SceFiosParams*			   fios2Option = NULL;
//	SampleUtil::Input::PadContextOption*   padOption = NULL;
//
//	SceFiosParams _params;// = SCE_FIOS_PARAMS_INITIALIZER;
//
//	int32_t sizeOp = SCE_FIOS_OP_STORAGE_SIZE(256, SCE_FIOS_PATH_MAX);	/* 64 ops: */
//	int32_t sizeChunk = SCE_FIOS_CHUNK_STORAGE_SIZE(1024);					/* 1024 chunks, 64KiB: */
//	int32_t sizeFh = SCE_FIOS_FH_STORAGE_SIZE(256, SCE_FIOS_PATH_MAX);	/* 16 file handles: */
//	int32_t sizeDh = SCE_FIOS_DH_STORAGE_SIZE(256, SCE_FIOS_PATH_MAX);		/* 4 directory handles: */
//
//	int32_t sizeTotal = sizeOp + sizeChunk + sizeFh + sizeDh;
//
//	unsigned char* m_pStorageForFios2;
//	m_pStorageForFios2 = (unsigned char*)malloc(sizeTotal);
//
//	if (m_pStorageForFios2 == NULL)
//	{
//		return SCE_SAMPLE_UTIL_ERROR_OUT_OF_MEMORY;
//	}
//
//	_params.opStorage.pPtr = m_pStorageForFios2;
//	_params.opStorage.length = sizeOp;
//	_params.chunkStorage.pPtr = m_pStorageForFios2 + sizeOp;
//	_params.chunkStorage.length = sizeChunk;
//	_params.fhStorage.pPtr = m_pStorageForFios2 + sizeOp + sizeChunk;
//	_params.fhStorage.length = sizeFh;
//	_params.dhStorage.pPtr = m_pStorageForFios2 + sizeOp + sizeChunk + sizeFh;
//	_params.dhStorage.length = sizeDh;
//	_params.pathMax = SCE_FIOS_PATH_MAX;
//	_params.pMemcpy = memcpy;
//
//	SampleSkeletonOption* option;


	ret = initializeUtil
	(
		(
			//kFunctionFlagGraphics |
			//kFunctionFlagSpriteRenderer |
			kFunctionFlagAudio |
			kFunctionFlagFios2 |
			kFunctionFlagUserIdManager
		),
			-1, -1);

	
	//exit(0);


//	vector<string> files = BobFile("/app0/").list();
//
//	for (int i = 0; i<files.size(); i++)
//	{
//		log.debug(files.at(i));
//	}
//
//
//
//	char filename[] = "/app0/version.txt";
//	char *pInput = NULL;
//	SceFiosSize inputSize = 0;
//	SceFiosSize result = 0;
//
//
//
//	/*E Synchronously find the file size. */
//	inputSize = sceFiosFileGetSizeSync(NULL, filename);
//
//	log.debug(to_string(inputSize));
//
//	/*E Synchronously read the text from the file. */
//	pInput = (char*)malloc((size_t)inputSize);
//	assert(pInput != NULL);
//	result = sceFiosFileReadSync(NULL, filename, pInput, inputSize, 0);
//	assert(result == inputSize);
//	free(pInput);


	


	FileUtils::loadByteFile("/app0/version.txt");

	log.debug(to_string(sceFiosExistsSync(NULL, "version.txt")));
	log.debug(to_string(sceFiosExistsSync(NULL, "/app0/version.txt")));
	log.debug(to_string(BobFile("/app0/version.txt").exists()));





	//FileUtils::loadByteFile("/app0/data/sounds/bg.ogg");

	
	//SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	

//	m_displayWidth = getGraphicsContext()->getNextRenderTarget()->getWidth();
//	m_displayHeight = getGraphicsContext()->getNextRenderTarget()->getHeight();
//
//	GLUtils::windowWidth = m_displayWidth;
//	GLUtils::windowHeight = m_displayHeight;
//	GLUtils::monitorWidth = m_displayWidth;
//	GLUtils::monitorHeight = m_displayHeight;

	//ret = common::Service::loadSystemPrxs();
	{
		ret = sceSysmoduleLoadModule(SCE_SYSMODULE_ULT);
		SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

		/* libult initialize */
		ret = sceUltInitialize();
		SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

		ret = sceSysmoduleLoadModule(SCE_SYSMODULE_NP_COMMERCE);
		SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

		ret = sceSysmoduleLoadModule(SCE_SYSMODULE_JSON2);
		SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);
	}
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);



//	ret = sceSystemServiceHideSplashScreen();
//	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	int32_t systemParamValue = 0;
	ret = sceSystemServiceParamGetInt(SCE_SYSTEM_SERVICE_PARAM_ID_LANG, &systemParamValue);
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);
	std::string language = (systemParamValue == SCE_SYSTEM_PARAM_LANG_JAPANESE) ? "japanese" : "english_us";

	

//	ret = m_baseService.initialize("/app0/game_data/config.lua", language,
//		getGraphicsContext(), getSpriteRenderer(),
//		getUserIdManager(),
//		getAudioContext(),
//		m_displayWidth, m_displayHeight,
//		SINGLE_USER_GAME_MP4_FILE_NAME);
//	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	

//	ret = m_inputDeviceManager.initialize(getGraphicsContext(),
//		&m_baseService.m_resourceManager.m_directMemoryHeap,
//		&m_baseService.m_eventDispatcher, &m_baseService.m_userEntryManager);
//	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	
	ps4ToSDLInputConverter = new PS4InputToSDLEventConverter();
	ps4ToSDLInputConverter->initialize();
	

//	ret = m_avPlayer.initialize(getGraphicsContext(),
//		getSpriteRenderer(), getAudioContext(),
//		&m_baseService.m_resourceManager.m_directMemoryHeap);
//	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	

	//ret = m_gameLogManager.initialize(&m_baseService);
	//SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	
	

//	m_titleLogoState.init(this);
//	m_gameMenuState.init(this);
//	m_gameVideoState.init(this);
//	m_loadingSaveDataState.init(this);
//	m_savingSaveDataState.init(this);
//	m_displayResultState.init(this);
//	m_displayNpScoreRankingState.init(this);
//	m_gameState.init(this);
//
//	m_thread = NULL;
//	m_isLoaded = false;
//	//m_isShootingRangeLoaded = false;
//
//	
//
//	changeState(&m_titleLogoState);

	

//
//
//		//		FILE *fp = fopen("version.txt", "rb");
//		//		if (fp == NULL)
//		//		{
//		//			fp = fopen("./version.txt", "rb");
//		//			if (fp == NULL)
//		//			{
//		//				fp = fopen("../version.txt", "rb");
//		//				if (fp == NULL)
//		//				{
//		//					fp = fopen("/app0/version.txt", "rb");
//		//					if (fp == NULL)
//		//					{
//		//						m_baseService.m_topLevelHud.setSystemMessage(L"could not find file");
//		//					}
//		//				}
//		//			}
//		//		}
//
//		string path = "/app0/";
//		vector<string> files;
//
//		SceFiosDH dh = SCE_FIOS_DH_INVALID;
//		SceFiosBuffer buffer = SCE_FIOS_BUFFER_INITIALIZER;
//		SceFiosSize bufferSize = 0;
//
//		SceFiosOp op = sceFiosDHOpen(NULL, &dh, path.c_str(), buffer);
//		int err = sceFiosOpWait(op);
//		if (err == SCE_FIOS_ERROR_BAD_SIZE)
//			bufferSize = sceFiosOpGetActualCount(op);
//		else if (err != SCE_FIOS_OK)
//		{
//			//m_baseService.m_topLevelHud.setSystemMessage(L"sceFiosDHOpen");
//			//return;
//		}
//		sceFiosOpDelete(op);
//
//
//
//		//int err = sceFiosDHOpenSync(NULL, &dh, path.c_str(), buffer);
//
//		//if (err != SCE_FIOS_OK)
//		//{
//			//m_baseService.m_topLevelHud.setSystemMessage(L"sceFiosDHOpenSync");
//			//return;
//		//}
//
//
//
//		/*E Now allocate the buffer (if needed) and traverse the directory. */
//		//if (bufferSize != 0)
//		//{
//			buffer.set(malloc(bufferSize), bufferSize);
//		
//			err = sceFiosDHOpenSync(NULL, &dh, path.c_str(), buffer);
//		
//			if (err != SCE_FIOS_OK)
//			{
//				setErr(err);
//			}
//			
//		//}
//			else
//			{
//				for (;;)
//				{
//					SceFiosDirEntry entry = SCE_FIOS_DIRENTRY_INITIALIZER;
//					err = sceFiosDHReadSync(NULL, dh, &entry);
//
//					if (err == SCE_FIOS_ERROR_EOF)
//						break;
//
//					if (err != SCE_FIOS_OK)
//					{
//						setErr(err);
//					}
//
//					files.push_back(entry.fullPath);
//					//printf("Read directory entry %s\n", entry.fullPath);
//				}
//
//				sceFiosDHCloseSync(NULL, dh);
//
//				if (buffer.pPtr)
//				{
//					free(buffer.pPtr);
//				}
//
//
//				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//				//std::string narrow = converter.to_bytes(wide_utf16_source_string);
//				std::wstring wide = converter.from_bytes(files.at(0));
//				
//				m_baseService.m_topLevelHud.setSystemMessage(wide);
//
//			}

	return SCE_OK;


}

wstring Main::getWString(string s)
{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		//std::string narrow = converter.to_bytes(wide_utf16_source_string);
		std::wstring wide = converter.from_bytes(s);
					
		return wide;
}
void Main::setErr(int err)
{
	if (err == SCE_FIOS_ERROR_UNIMPLEMENTED)log.error("SCE_FIOS_ERROR_UNIMPLEMENTED");
	if (err == SCE_FIOS_ERROR_CANT_ALLOCATE_OP)log.error("SCE_FIOS_ERROR_CANT_ALLOCATE_OP");
	if (err == SCE_FIOS_ERROR_CANT_ALLOCATE_FH)log.error("SCE_FIOS_ERROR_CANT_ALLOCATE_FH");
	if (err == SCE_FIOS_ERROR_CANT_ALLOCATE_DH)log.error("SCE_FIOS_ERROR_CANT_ALLOCATE_DH");
	if (err == SCE_FIOS_ERROR_CANT_ALLOCATE_CHUNK)log.error("SCE_FIOS_ERROR_CANT_ALLOCATE_CHUNK");
	if (err == SCE_FIOS_ERROR_BAD_PATH)log.error("SCE_FIOS_ERROR_BAD_PATH");
	if (err == SCE_FIOS_ERROR_BAD_PTR)log.error("SCE_FIOS_ERROR_BAD_PTR");
	if (err == SCE_FIOS_ERROR_BAD_OFFSET)log.error("SCE_FIOS_ERROR_BAD_OFFSET");
	if (err == SCE_FIOS_ERROR_BAD_SIZE)log.error("SCE_FIOS_ERROR_BAD_SIZE");
	if (err == SCE_FIOS_ERROR_BAD_IOVCNT)log.error("SCE_FIOS_ERROR_BAD_IOVCNT");
	if (err == SCE_FIOS_ERROR_BAD_OP)log.error("SCE_FIOS_ERROR_BAD_OP");
	if (err == SCE_FIOS_ERROR_BAD_FH)log.error("SCE_FIOS_ERROR_BAD_FH");
	if (err == SCE_FIOS_ERROR_BAD_DH)log.error("SCE_FIOS_ERROR_BAD_DH");
	if (err == SCE_FIOS_ERROR_BAD_ALIGNMENT)log.error("SCE_FIOS_ERROR_BAD_ALIGNMENT");
	if (err == SCE_FIOS_ERROR_NOT_A_FILE)log.error("SCE_FIOS_ERROR_NOT_A_FILE");
	if (err == SCE_FIOS_ERROR_NOT_A_DIRECTORY)log.error("SCE_FIOS_ERROR_NOT_A_DIRECTORY");
	if (err == SCE_FIOS_ERROR_EOF)log.error("SCE_FIOS_ERROR_EOF");
	if (err == SCE_FIOS_ERROR_TIMEOUT)log.error("SCE_FIOS_ERROR_TIMEOUT");
	if (err == SCE_FIOS_ERROR_CANCELLED)log.error("SCE_FIOS_ERROR_CANCELLED");
	if (err == SCE_FIOS_ERROR_ACCESS)log.error("SCE_FIOS_ERROR_ACCESS");
	if (err == SCE_FIOS_ERROR_DECOMPRESSION)log.error("SCE_FIOS_ERROR_DECOMPRESSION");
	if (err == SCE_FIOS_ERROR_READ_ONLY)log.error("SCE_FIOS_ERROR_READ_ONLY");
	if (err == SCE_FIOS_ERROR_WRITE_ONLY)log.error("SCE_FIOS_ERROR_WRITE_ONLY");
	if (err == SCE_FIOS_ERROR_MEDIA_GONE)log.error("SCE_FIOS_ERROR_MEDIA_GONE");
	if (err == SCE_FIOS_ERROR_PATH_TOO_LONG)log.error("SCE_FIOS_ERROR_PATH_TOO_LONG");
	if (err == SCE_FIOS_ERROR_TOO_MANY_OVERLAYS)log.error("SCE_FIOS_ERROR_TOO_MANY_OVERLAYS");
	if (err == SCE_FIOS_ERROR_BAD_OVERLAY)log.error("SCE_FIOS_ERROR_BAD_OVERLAY");
	if (err == SCE_FIOS_ERROR_BAD_ORDER)log.error("SCE_FIOS_ERROR_BAD_ORDER");
	if (err == SCE_FIOS_ERROR_BAD_INDEX)log.error("SCE_FIOS_ERROR_BAD_INDEX");
	if (err == SCE_FIOS_ERROR_EVENT_NOT_HANDLED)log.error("SCE_FIOS_ERROR_EVENT_NOT_HANDLED");
	if (err == SCE_FIOS_ERROR_BUSY)log.error("SCE_FIOS_ERROR_BUSY");
	if (err == SCE_FIOS_ERROR_BAD_ARCHIVE)log.error("SCE_FIOS_ERROR_BAD_ARCHIVE");
	if (err == SCE_FIOS_ERROR_BAD_RESOLVE_TYPE)log.error("SCE_FIOS_ERROR_BAD_RESOLVE_TYPE");
	if (err == SCE_FIOS_ERROR_BAD_FLAGS)log.error("SCE_FIOS_ERROR_BAD_FLAGS");
	if (err == SCE_FIOS_ERROR_UNKNOWN)log.error("SCE_FIOS_ERROR_UNKNOWN");
	if (err == SCE_FIOS_ERROR_ALREADY_EXISTS)log.error("SCE_FIOS_ERROR_ALREADY_EXISTS");
	if (err == SCE_FIOS_ERROR_IN_CALLBACK)log.error("SCE_FIOS_ERROR_IN_CALLBACK");
}
//=========================================================================================================================
int Main::update()
{//=========================================================================================================================


	int ret;
	(void)ret;
	//m_baseService.m_debugWindow.notifyPhase(common::Service::DebugWindow::kBeginUpdate);


	int currentTime = sceKernelGetProcessTime();
	float frameDelta = (currentTime - m_previousTime) / 1000000.0;
	m_previousTime = currentTime;



	ret = updateUtil();


	//SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	//ret = m_baseService.update(frameDelta);
	//SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	//ret = m_inputDeviceManager.update();
	//SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	
	ps4ToSDLInputConverter->update();



	//	if (m_inputDeviceManager.isButtonDownByAnyPlayer(ssi::kButtonL1 | ssi::kButtonR1 | ssi::kButtonOptions))
	//	{
	//		printf("*-*-*-*-*  call sceSystemServiceLoadExec() \n");
	//		ret = sceSystemServiceLoadExec("/app0/eboot.bin", NULL);	// reset Shooting Game
	//		printf("*-*-*-*-*  sceSystemServiceLoadExec() : ret(0x%08x) \n", ret);
	//	}

	//	if (m_inputDeviceManager.isButtonPressedByAnyPlayer(ssi::kButtonSquare))
	//	{
	//		m_baseService.m_debugWindow.toggleDisplay();
	//	}


	//	if (m_currentState != NULL)
	//	{
	//		ret = m_currentState->onUpdate(frameDelta);
	//
	//		//SCE_SAMPLE_UTIL_ASSERT_MSG(ret == SCE_OK, "ret=%#x", ret);
	//	}
	//	else
	//	{
	//		return -1;
	//	}
	//
	//	m_baseService.m_debugWindow.notifyPhase(common::Service::DebugWindow::kEndUpdate);
	return SCE_OK;

}

sce::SampleUtil::Graphics::Texture* t = nullptr;

#include "graphics/platform_gnm/buffer_internal_gnm.h"
#include "graphics/platform_gnm/gnm_internal.h"
#include "graphics/platform_gnm/program_internal_gnm.h"
#include "graphics/platform_gnm/constant_internal_gnm.h"
#include "graphics/platform_gnm/context_internal_gnm.h"
#include "graphics/platform_gnm/font_orbis.h"
#include "graphics/platform_gnm/loader_internal_gnm.h"
#include "graphics/image.h"







bool ok = false;
//=========================================================================================================================
void Main::render()
{//=========================================================================================================================

//	m_baseService.m_debugWindow.notifyPhase(common::Service::DebugWindow::kBeginRender);
//
//	ssg::GraphicsContext *context = getGraphicsContext();
//	context->beginScene(context->getNextRenderTarget(),
//		context->getDepthStencilSurface());
//
//
//
//
//	context->setCullMode(sce::SampleUtil::Graphics::kCullNone);
//	context->clearRenderTarget(0x00000000);
//	
//	context->setDepthWriteEnable(true);
//	
//	context->setDepthFunc(sce::SampleUtil::Graphics::kDepthFuncAlways);

//	if (m_currentState == &m_titleLogoState)
//	{
//		m_titleLogoState.render(context);
//
////		float rtWidth = context->getCurrentRenderTarget()->getWidth();
////		float rtHeight = context->getCurrentRenderTarget()->getHeight();
////		context->setCullMode(sce::SampleUtil::Graphics::kCullNone);
////		context->clearRenderTarget(0x00000000);
////
////		context->setDepthWriteEnable(true);
////
////		context->setDepthFunc(sce::SampleUtil::Graphics::kDepthFuncAlways);
////
////		m_baseService.getSpriteRenderer()->drawString(context,
////			m_baseService.m_resourceManager.m_fontMB,
////			(uint16_t*)m_baseService.m_resourceManager.getTextUcs2("LOADING").c_str(),
////			sce::Vectormath::Simd::Aos::Vector2(rtWidth*0.3f, rtHeight*0.4f),
////			sce::Vectormath::Simd::Aos::Vector4(((float)(m_frame % 180) / 180),
////			((float)(m_frame % 120) / 120),
////				((float)(m_frame % 60) / 60), 1.0));
//
//	}
//	else if (m_currentState == &m_gameMenuState)
//	{
//		m_gameMenuState.render(context);
//
//	}
//	else if (m_currentState == &m_gameVideoState)
//	{
//		m_gameVideoState.render(context);
//
//	}
//	else if (m_currentState == &m_loadingSaveDataState)
//	{
//		m_loadingSaveDataState.render(context);
//
//	}
//	else if (m_currentState == &m_savingSaveDataState)
//	{
//		m_savingSaveDataState.render(context);
//
//	}
//	else if (m_currentState == &m_displayResultState)
//	{
//		m_displayResultState.render(context);
//
//	}
//	else if (m_currentState == &m_displayNpScoreRankingState)
//	{
//		m_displayNpScoreRankingState.render(context);
//
//	}
//	else if (m_currentState == &m_gameState)
//	{
//		m_gameState.render(context);
//	}

//GLUtils::drawFilledRect(255, 255, 0, 0, 100, 0, 100, 1);

//exit(0);

//	stateManager->render();
//	console->render();
//	rightConsole->render();

//vecmath::Vector2 position = vecmath::Vector2(0, 0);
//vecmath::Vector2 size = vecmath::Vector2(10, 10);
//vecmath::Vector4 rgba = vecmath::Vector4(1, 1, 1, 1);



//	if (ok == false)
//	{
//		ok = true;
//
//		FILE *fp = fopen("/app0/version.txt", "rb");
//		if (fp == NULL)
//		{
//			m_baseService.m_topLevelHud.setSystemMessage(L"could not find file");
//		}
//				
//			
//		
//	}

	//if (t == nullptr)
	//{

//		ssgi::ImageFile imageFile;
//		int ret = imageFile.open("/data/theme/keyboard.png");
//		if (ret != SCE_OK)
//		{
//			//m_baseService.m_topLevelHud.setSystemMessage(L"hi");
//		}

		
		
		//Main::getBaseService()->m_resourceManager.m_graphicsLoader->createTextureFromFile(&t, "/app0/data/theme/keyboard.png");
	//}


	//Main::getSpriteRenderer()->drawTexture(Main::getGraphicsContext(), vecmath::Vector2(0.5, 0.5), vecmath::Vector2(1, 1), t, rgba);
	//Main::getSpriteRenderer()->drawTexture(Main::getGraphicsContext(), vecmath::Vector2(0, 0), vecmath::Vector2(1, 1), t, rgba);

	

	//m_baseService.m_topLevelHud.draw(context, m_baseService.getDisplaySafeAreaRatio());

	//m_baseService.m_debugWindow.draw(getGraphicsContext(), m_baseService.getDisplaySafeAreaRatio());




	//getGraphicsContext()->endScene();

	//m_baseService.m_debugWindow.notifyPhase(common::Service::DebugWindow::kEndRender);








	//	getGraphicsContext()->beginScene(getGraphicsContext()->getNextRenderTarget(),
	//		getGraphicsContext()->getDepthStencilSurface());
	//
	//	getGraphicsContext()->clearRenderTarget(0x00000000);
	//
	//	getGraphicsContext()->setDepthWriteEnable(true);
	//	getGraphicsContext()->setDepthFunc(sce::SampleUtil::Graphics::kDepthFuncLessEqual);
	//
	//	{
	//
	//		getGraphicsContext()->setDepthFunc(sce::SampleUtil::Graphics::kDepthFuncAlways);	// for drawDebugStringf
	//
	//
	//
	//		getSpriteRenderer()->fillRect(getGraphicsContext()
	//			, vecmath::Vector2(0, 0)
	//			, vecmath::Vector2(0.5, 0.5)
	//			, g_gray);
	//
	//		getSpriteRenderer()->drawDebugStringf(getGraphicsContext(), vecmath::Vector2(0, 0), 0.05f, g_white, "test");
	//
	//
	//	}
	//	//m_debug.draw(this->getGraphicsContext(), this->getSpriteRenderer());
	//
	//	stateManager->render();
	//	console->render();
	//	rightConsole->render();
	//
	//	getGraphicsContext()->endScene();

}
//=========================================================================================================================
int Main::finalize()
{//=========================================================================================================================


	int ret;
	(void)ret;
	//	m_displayNpScoreRankingScene.finalize();
	//	m_displayResultScene.finalize();
	//	m_savingSaveDataScene.finalize();
	//	m_loadingSaveDataScene.finalize();
	//	m_gameMenuScene.finalize();
	//	m_gameScene.finalize();
	//
	//	m_singlePlayerSaveData.finalize();
	//	m_saveDataManager.finalize();
	//
	//	ret = m_gameLogManager.finalize();
	//	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);
	//
	//	ret = m_avPlayer.finalize();
	//	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);
	//
	//	ret = m_inputDeviceManager.finalize();
	//	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);
	//
	//	ret = m_baseService.finalize();
	//	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

		//ret = common::Service::unloadSystemPrxs();
	{
		ret = sceSysmoduleUnloadModule(SCE_SYSMODULE_JSON2);
		SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

		ret = sceSysmoduleUnloadModule(SCE_SYSMODULE_NP_COMMERCE);
		SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

		/* libult finalize */
		ret = sceUltFinalize();
		SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

		ret = sceSysmoduleUnloadModule(SCE_SYSMODULE_ULT);
		SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);
	}


	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	ret = finalizeUtil();
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	return SCE_OK;
}


int Main::initializeModules(void)
{//=========================================================================================================================
	int ret;


	m_baseService.load();

	ret = m_saveDataManager.initialize();
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	ret = m_singlePlayerSaveData.initialize(&m_baseService,
		&m_saveDataManager,
		&m_gameLogManager,
		m_baseService.m_config.m_enableDummySaveDataLoad);
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	return SCE_OK;
}

int Main::initializeScenes(void)
{//=========================================================================================================================
	int ret;
	common::Service::BaseService *b = &m_baseService;


//	ret = m_gameScene.initialize(b);
//	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);
//
//	ret = m_gameMenuScene.initialize(b);
//	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);
//
//	ret = m_loadingSaveDataScene.initialize(b, &m_singlePlayerSaveData);
//	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);
//
//	ret = m_savingSaveDataScene.initialize(b, &m_singlePlayerSaveData);
//	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);
//
//	ret = m_displayResultScene.initialize(b, &m_singlePlayerSaveData);
//	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);
//
//	ret = m_displayNpScoreRankingScene.initialize(b, &m_singlePlayerSaveData);
//	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);


	(void)ret;
	return SCE_OK;

}

void* Main::loadingThread(void *argc)
{//=========================================================================================================================
	int ret;
	Main *app = (Main*)argc;

	ret = app->initializeModules();
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	ret = app->initializeScenes();
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	app->m_isLoaded = true;
	return NULL;
}

void* Main::loadingThreadForShootingRange(void *argc)
{//=========================================================================================================================
	Main *app = (Main*)argc;

	app->m_baseService.m_resourceManager.loadShootingRange();

	app->m_isShootingRangeLoaded = true;
	return NULL;
}

int Main::startLoad(void)
{//=========================================================================================================================
	int ret;
	(void)ret;


	ScePthreadAttr threadAttr;
	ret = scePthreadAttrInit(&threadAttr);
	SCE_SAMPLE_UTIL_ASSERT(ret >= 0);


	ret = scePthreadCreate(&m_thread, &threadAttr, loadingThread, (void*)this, "loading_thread");
	SCE_SAMPLE_UTIL_ASSERT(ret >= 0);


	ret = scePthreadAttrDestroy(&threadAttr);
	SCE_SAMPLE_UTIL_ASSERT(ret >= 0);

	return SCE_OK;
}

bool Main::isLoaded(void)
{//=========================================================================================================================
	int ret;
	if (!m_isLoaded)
	{
		return false;
	}
	if (m_thread != NULL)
	{
		ret = scePthreadJoin(m_thread, NULL);
		SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);
		m_thread = NULL;
	}
	return true;
}

int Main::startLoadRange(void)
{//=========================================================================================================================
	int ret;
	(void)ret;

	//	ScePthreadAttr threadAttr;
	//	ret = scePthreadAttrInit(&threadAttr);
	//	SCE_SAMPLE_UTIL_ASSERT(ret >= 0);
	//
	//	ret = scePthreadCreate(&m_thread,
	//		&threadAttr,
	//		loadingThreadForShootingRange,
	//		(void*)this,
	//		"loading_thread_for_range");
	//	SCE_SAMPLE_UTIL_ASSERT(ret >= 0);
	//
	//	ret = scePthreadAttrDestroy(&threadAttr);
	//	SCE_SAMPLE_UTIL_ASSERT(ret >= 0);
	return SCE_OK;
}

bool Main::isShootingRangeLoaded(void)
{//=========================================================================================================================
	int ret;
//	if (!m_isShootingRangeLoaded)
	{
		return false;
	}
	if (m_thread != NULL)
	{
		ret = scePthreadJoin(m_thread, NULL);
		SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);
		m_thread = NULL;
	}
	return true;
}

common::Service::BaseService *Main::getBaseService(void)
{
	return &mainObject->m_baseService;
}

sce::SampleUtil::Graphics::GraphicsContext *Main::getGraphicsContext(void)
{
	return mainObject->sce::SampleUtil::SampleSkeleton::getGraphicsContext();
}

sce::SampleUtil::Graphics::SpriteRenderer *Main::getSpriteRenderer(void)
{
	return mainObject->sce::SampleUtil::SampleSkeleton::getSpriteRenderer();
}

sce::SampleUtil::Audio::AudioContext *Main::getAudioContext(void)
{
	return mainObject->sce::SampleUtil::SampleSkeleton::getAudioContext();
}

sce::SampleUtil::System::UserIdManager *Main::getUserIdManager(void)
{
	return mainObject->sce::SampleUtil::SampleSkeleton::getUserIdManager();
}

sce::SampleUtil::Input::PadContext *Main::getPadContextOfInitialUser(void)
{
	return mainObject->sce::SampleUtil::SampleSkeleton::getPadContextOfInitialUser();
}




void Main::TitleLogoState::init(Main *app)
{
	m_app = app;
	int ret = m_nowLoadingWindow.initialize(&m_app->m_baseService);
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);
	m_name = "TitleLogoState";
}

int Main::TitleLogoState::onEnter(void)
{
	int ret;
	(void)ret;



	ret = m_app->startLoad();
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);



	return SCE_OK;
}

int Main::TitleLogoState::onUpdate(float ellapseSec)
{
	int ret;
	(void)ret;

	m_nowLoadingWindow.update();
	if (m_app->isLoaded())
	{

		ret = m_app->startLoadRange();
		SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

		m_app->changeState(&m_app->m_gameMenuState);
	}
	return SCE_OK;
}

void Main::TitleLogoState::render(ssg::GraphicsContext *context)
{
	m_nowLoadingWindow.render(context);
}



void Main::GameMenuState::init(Main *app)
{
	m_app = app;
	m_name = "GameMenuState";
}

int Main::GameMenuState::onEnter(void)
{
	int ret;
	(void)ret;

	ret = m_app->m_gameMenuScene.reset();
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	return SCE_OK;
}

int Main::GameMenuState::onLeave(void)
{
	m_app->m_baseService.m_topLevelHud.clearAll();
	m_app->m_selectedUserId = m_app->m_gameMenuScene.getSelectedUserId();
	return SCE_OK;
}

int Main::GameMenuState::onUpdate(float ellapseSec)
{
	int ret;
	(void)ret;

	ret = m_app->m_gameMenuScene.update(ellapseSec, &m_app->m_inputDeviceManager);
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	if (m_app->m_gameMenuScene.isFinished())
	{
		if (m_app->m_gameMenuScene.getResult() == GameMenuScene::kMenuItemGameStart)
		{
			m_app->changeState(&m_app->m_loadingSaveDataState);
		}
		else if (m_app->m_gameMenuScene.getResult() == GameMenuScene::kMenuItemHighScore)
		{
			m_app->changeState(&m_app->m_loadingSaveDataState);
		}
		else if (m_app->m_gameMenuScene.getResult() == GameMenuScene::kMenuItemReplay)
		{
			m_app->changeState(&m_app->m_gameVideoState);
		}
	}
	return SCE_OK;
}

void Main::GameMenuState::render(ssg::GraphicsContext *context)
{
	m_app->m_gameMenuScene.render(context);
}



void Main::GameVideoState::init(Main *app)
{
	m_app = app;
	m_state = kStateInitialized;
	m_name = "GameVideoState";
}

int Main::GameVideoState::onEnter(void)
{
	int ret;
	(void)ret;
	m_app->m_baseService.m_topLevelHud.clearAll();

	ret = m_app->m_avPlayer.start(SINGLE_USER_GAME_MP4_FILE_NAME);
	if (ret == SCE_OK)
	{
//		m_app->m_baseService.m_topLevelHud.setSystemMessage(
		m_app->m_baseService.m_config.getTextUcs2("PUSH_X_BUTTON");
//		);
		m_state = kStatePlayingVideo;

	}
	else
	{
		std::string message;
		if (m_app->m_baseService.isVideoRecordingNoSpaceErrorOccurred())
		{
			message = m_app->m_baseService.m_resourceManager.getTextUtf8("MSG_DIALOG_FAILED_TO_RECORD_VIDEO_NO_SPACE").c_str();
		}
		else
		{
			message = m_app->m_baseService.m_resourceManager.getTextUtf8("MSG_DIALOG_MOVIE_FILE_NOT_EXIST").c_str();
		}

		cu::DialogRequest dialogRequest;
		dialogRequest.initAsMsgDialogOfUser(cu::DialogRequest::MessageDialog::kOk, message);
		m_app->m_baseService.m_dialogManager->addRequest(dialogRequest, &m_dialogMonitor);
		m_state = kStateErrorDialog;
	}
	return SCE_OK;
}

int Main::GameVideoState::onLeave(void)
{
	m_app->m_baseService.m_topLevelHud.clearAll();
	return SCE_OK;
}

int Main::GameVideoState::onUpdate(float ellapseSec)
{
	int ret;
	(void)ret;
	if (m_state == kStatePlayingVideo)
	{
		if (m_app->m_avPlayer.isPlaying())
		{
			ret = m_app->m_avPlayer.update();
			SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

			if (m_app->m_inputDeviceManager.isButtonPressedByAnyPlayer(ssin::kButtonCross))
			{
				m_app->m_avPlayer.stop();
			}
		}
		else
		{
			m_app->m_avPlayer.stop();
			m_state = kStateFinished;
		}

	}
	else if (m_state == kStateErrorDialog)
	{
		if (m_dialogMonitor.isDone())
		{
			m_state = kStateFinished;
		}

	}
	else if (m_state == kStateFinished)
	{
		m_app->changeState(&m_app->m_gameMenuState);
	}

	return SCE_OK;
}

void Main::GameVideoState::render(ssg::GraphicsContext *context)
{
	if (m_state == kStatePlayingVideo)
	{
		m_app->m_avPlayer.render(context, m_app->getSpriteRenderer());
	}
}



void Main::LoadingSaveDataState::init(Main *app)
{
	m_app = app;
	m_name = "LoadingSaveDataState";
}

int Main::LoadingSaveDataState::onEnter(void)
{
	int ret;
	(void)ret;

	sce::SampleUtil::System::UserId userId = m_app->m_selectedUserId;
	SCE_SAMPLE_UTIL_ASSERT(userId != sss::kInvalidUserId);

	ret = m_app->m_loadingSaveDataScene.reset(userId);
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	return SCE_OK;
}

int Main::LoadingSaveDataState::onUpdate(float ellapseSec)
{
	int ret;
	(void)ret;

	ret = m_app->m_loadingSaveDataScene.update(ellapseSec);
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	if (m_app->m_loadingSaveDataScene.isFinished())
	{
		if (m_app->m_gameMenuScene.getResult() == GameMenuScene::kMenuItemGameStart)
		{
			m_app->changeState(&m_app->m_gameState);
		}
		else if (m_app->m_gameMenuScene.getResult() == GameMenuScene::kMenuItemHighScore)
		{
			m_app->changeState(&m_app->m_displayResultState);
		}
		else
		{
			SCE_SAMPLE_UTIL_ASSERT(0);
		}
	}

	return SCE_OK;
}

void Main::LoadingSaveDataState::render(ssg::GraphicsContext *context)
{
	m_app->m_loadingSaveDataScene.render(context);
}



void Main::SavingSaveDataState::init(Main *app)
{
	m_app = app;
	m_name = "SavingSaveDataState";
}

int Main::SavingSaveDataState::onEnter(void)
{
	int ret;
	(void)ret;

	sce::SampleUtil::System::UserId userId = m_app->m_selectedUserId;
	SCE_SAMPLE_UTIL_ASSERT(userId != sss::kInvalidUserId);

	ret = m_app->m_savingSaveDataScene.setupSaveData(userId, m_app->m_selectedPlayerPlayStyle, m_app->m_selectedPlayerScore);
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	return SCE_OK;
}

int Main::SavingSaveDataState::onUpdate(float ellapseSec)
{
	int ret;
	(void)ret;

	ret = m_app->m_savingSaveDataScene.update(ellapseSec);
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	if (m_app->m_savingSaveDataScene.isFinished())
	{
		m_app->changeState(&m_app->m_displayResultState);
	}

	return SCE_OK;
}

void Main::SavingSaveDataState::render(ssg::GraphicsContext *context)
{
	m_app->m_savingSaveDataScene.render(context);
}



void Main::DisplayResultState::init(Main *app)
{
	m_app = app;
	m_name = "DisplayResultState";
}

int Main::DisplayResultState::onEnter(void)
{
	int ret;
	(void)ret;

	ret = m_app->m_displayResultScene.reset(m_app->m_selectedUserId);
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	return SCE_OK;
}

int Main::DisplayResultState::onUpdate(float ellapseSec)
{
	int ret;
	(void)ret;

	ret = m_app->m_displayResultScene.update(ellapseSec, &m_app->m_inputDeviceManager);
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	if (m_app->m_displayResultScene.isFinished())
	{
		if (m_app->m_displayResultScene.getNextScene() == DisplayResultScene::NextScene::kNpScoreRankingScene)
		{
			m_app->changeState(&m_app->m_displayNpScoreRankingState);
		}
		else
			if (m_app->m_displayResultScene.getNextScene() == DisplayResultScene::NextScene::kGameMenuScene)
			{
				m_app->changeState(&m_app->m_gameMenuState);
			}
	}

	return SCE_OK;
}

void Main::DisplayResultState::render(ssg::GraphicsContext *context)
{
	m_app->m_displayResultScene.render(context);
}



void Main::DisplayNpScoreRankingState::init(Main *app)
{
	m_app = app;
	m_name = "DisplayNpScoreRankingState";
}

int Main::DisplayNpScoreRankingState::onEnter(void)
{
	int ret;
	(void)ret;

	ret = m_app->m_displayNpScoreRankingScene.reset(m_app->m_selectedUserId);
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	return SCE_OK;
}

int Main::DisplayNpScoreRankingState::onUpdate(float ellapseSec)
{
	int ret;
	(void)ret;

	ret = m_app->m_displayNpScoreRankingScene.update(ellapseSec, &m_app->m_inputDeviceManager);
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	if (m_app->m_displayNpScoreRankingScene.isFinished())
	{
		if (m_app->m_displayNpScoreRankingScene.getNextScene() == DisplayNpScoreRankingScene::NextScene::kDisplayResultScene)
		{
			m_app->changeState(&m_app->m_displayResultState);
		}
		else if (m_app->m_displayNpScoreRankingScene.getNextScene() == DisplayNpScoreRankingScene::NextScene::kGameMenuScene)
		{
			m_app->changeState(&m_app->m_gameMenuState);
		}
	}

	return SCE_OK;
}

void Main::DisplayNpScoreRankingState::render(ssg::GraphicsContext *context)
{
	m_app->m_displayNpScoreRankingScene.render(context);
}



void Main::GameState::init(Main *app)
{
	m_app = app;
	m_name = "GameState";
}

int Main::GameState::onEnter(void)
{
	int ret;
	(void)ret;

	ret = m_app->m_gameScene.reset(m_app->m_selectedUserId);
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	return SCE_OK;
}

int Main::GameState::onLeave(void)
{
	m_app->m_selectedPlayerPlayStyle = m_app->m_gameScene.m_selectedPlayerPlayStyle;
	m_app->m_selectedPlayerScore = m_app->m_gameScene.m_selectedPlayerScore;
	return SCE_OK;
}

int Main::GameState::onUpdate(float ellapseSec)
{
	int ret;
	(void)ret;

	ret = m_app->m_gameScene.update(ellapseSec, &m_app->m_inputDeviceManager);
	SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

	if (m_app->m_gameScene.isFinished())
	{
		if (m_app->m_gameScene.getNextScene() == GameScene::NextScene::kSavingSaveDataScene)
		{
			m_app->changeState(&m_app->m_savingSaveDataState);
		}
		else if (m_app->m_gameScene.getNextScene() == GameScene::NextScene::kGameMenuScene)
		{
			m_app->changeState(&m_app->m_gameMenuState);
		}
		else
		{
			SCE_SAMPLE_UTIL_ASSERT(0);
		}
	}

	return SCE_OK;
}

void Main::GameState::render(ssg::GraphicsContext *context)
{
	m_app->m_gameScene.render(context, &m_app->m_inputDeviceManager);
}



















#endif

