package com.bobsgame;

import ch.qos.logback.classic.Level;
import ch.qos.logback.classic.Logger;
import ch.qos.logback.classic.LoggerContext;
import ch.qos.logback.classic.encoder.PatternLayoutEncoder;
import ch.qos.logback.classic.html.HTMLLayout;
import ch.qos.logback.classic.spi.ILoggingEvent;
import ch.qos.logback.core.ConsoleAppender;
import ch.qos.logback.core.FileAppender;
import ch.qos.logback.core.encoder.LayoutWrappingEncoder;
import com.bobsgame.audio.AudioUtils;
import com.bobsgame.client.*;
import com.bobsgame.client.console.Console;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.client.network.GameClientTCP;
import com.bobsgame.client.state.*;
import com.bobsgame.net.BobNet;
import com.bobsgame.net.ClientStats;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.Utils;
import de.matthiasmann.twl.GUI;
//import netscape.javascript.JSObject;
import org.apache.commons.io.FileUtils;
import org.apache.commons.net.ntp.NTPUDPClient;
import org.apache.commons.net.ntp.NtpV3Packet;
import org.apache.commons.net.ntp.TimeInfo;
import org.apache.commons.net.ntp.TimeStamp;
import org.lwjgl.BufferUtils;
import org.lwjgl.glfw.GLFW;
import org.lwjgl.openal.AL;
import org.slf4j.LoggerFactory;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.*;
import java.net.InetAddress;
import java.nio.charset.StandardCharsets;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.text.SimpleDateFormat;
import java.util.*;

import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL20.*;

public class ClientMain {
	public static ClientMain clientMain;

	public static void main(String[] args) {
		try {
			Thread.currentThread().setName("ClientMain_main");
		} catch (SecurityException e) {
			e.printStackTrace();
		}

		clientMain = new ClientMain();

		clientMain.mainInit();

		try {
			clientMain.mainLoop();
		} catch (Exception e) {
			e.printStackTrace();
		}

		try {
			clientMain.cleanup();
		} catch (Exception e) {
			e.printStackTrace();
		}

		ClientMain.exit();
	}

	static int lastWidth = 0;
	static int lastHeight = 0;
	static int lastDisplayWidth = 0;
	static int lastDisplayHeight = 0;
	static int canvasWidth = 0;
	static int canvasHeight = 0;

	static Thread gameThread = null;
	static Runnable gameRunnable = null;

	static boolean started = false;

	public static void exit() {
		System.exit(0);
	}

	public ClientStats clientInfo = new ClientStats();

	public void initClientInfo() {
		Properties systemProperties = System.getProperties();

		clientInfo.getEnvProcessorIdentifier = System.getenv("PROCESSOR_IDENTIFIER");
		clientInfo.getEnvProcessorArchitecture = System.getenv("PROCESSOR_ARCHITECTURE");
		clientInfo.getEnvNumberOfProcessors = System.getenv("NUMBER_OF_PROCESSORS");


		clientInfo.jreVersion			= systemProperties.getProperty("java.version");
		clientInfo.jreVendor			= systemProperties.getProperty("java.vendor");
		clientInfo.jreHomeDir			= systemProperties.getProperty("java.home");
		clientInfo.jvmVersion			= systemProperties.getProperty("java.vm.version");
		clientInfo.jvmName				= systemProperties.getProperty("java.vm.name");
		clientInfo.javaClassVersion		= systemProperties.getProperty("java.class.version");
		clientInfo.javaClassPath		= systemProperties.getProperty("java.class.path");
		clientInfo.javaLibraryPath		= systemProperties.getProperty("java.library.path");
		clientInfo.javaTempDir			= systemProperties.getProperty("java.io.tmpdir");
		clientInfo.osName				= systemProperties.getProperty("os.name");
		clientInfo.osArch				= systemProperties.getProperty("os.arch");
		clientInfo.osVersion			= systemProperties.getProperty("os.version");
		clientInfo.osUserAccountName	= systemProperties.getProperty("user.name");
		clientInfo.osHomeDir			= systemProperties.getProperty("user.home");
		clientInfo.workingDir			= systemProperties.getProperty("user.dir");

		clientInfo.displayWidth = LWJGLUtils.desktopDisplayWidth;
		clientInfo.displayHeight = LWJGLUtils.desktopDisplayHeight;
		clientInfo.displayBPP = LWJGLUtils.desktopDisplayBPP;
		clientInfo.displayFreq = LWJGLUtils.desktopDisplayFreq;

		clientInfo.shaderCompiled = LWJGLUtils.useShader;
		clientInfo.canUseFBO = LWJGLUtils.useFBO;
		clientInfo.usingVSync = LWJGLUtils.vsync;

		clientInfo.numCPUs = StatsUtils.rt.availableProcessors();
		clientInfo.totalMemory = StatsUtils.totalMemory / 1024 / 1024;
		clientInfo.maxMemory = StatsUtils.maxMemory / 1024 / 1024;

		clientInfo.numControllersFound = LWJGLUtils.numControllers;
		clientInfo.controllersNames = LWJGLUtils.controllerNames;

		clientInfo.timeZoneGMTOffset = timeZoneGMTOffset;

		clientInfo.glVendor = glGetString(GL_VENDOR);
		clientInfo.glVersion = glGetString(GL_VERSION);
		clientInfo.glRenderer = glGetString(GL_RENDERER);
		clientInfo.shaderVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
		clientInfo.glExtensions = glGetString(GL_EXTENSIONS);

		clientInfo.log();
	}

	public float timeZoneGMTOffset = 0.0f;
	public float DSTOffset = 0.0f;
	public void initTime() {
		log.info("Init Time...");

		//put timezone in connection info
		Calendar calendar = Calendar.getInstance();

		Date calendarTime = calendar.getTime();
		log.info("Local Adjusted Time: " + calendarTime);
		String gmtOffset = new SimpleDateFormat("Z").format(calendarTime);
		log.info("Local TimeZone GMT offset: " + gmtOffset);

		//get the time zone
		TimeZone timezone = calendar.getTimeZone();

		//get timezone raw millisecond offset
		int offset = timezone.getRawOffset();
		int offsetHrs = offset / 1000 / 60 / 60;
		int offsetMins = offset / 1000 / 60 % 60;
		//log.debug("TimeZone Offset Hours: " + offsetHrs);
		//log.debug("TimeZone Offset Mins: " + offsetMins);

		timeZoneGMTOffset = offsetHrs+offsetMins/100.0f;
		//log.debug("TimeZone Offset Float: " + offsetFloat);

		//add daylight savings offset
		int dstOffset = 0;
		if (timezone.inDaylightTime(new Date())) {
			dstOffset = timezone.getDSTSavings();
		}
		int dstOffsetHrs = dstOffset / 1000 / 60 / 60;
		int dstOffsetMins = dstOffset / 1000 / 60 % 60;
		//log.debug("DST Offset Hours: " + dstOffsetHrs);
		//log.debug("DST Offset Mins: " + dstOffsetMins);
		DSTOffset = dstOffsetHrs+dstOffsetMins/100.0f;

		//combined offset timezone + dst
		int combinedOffset = offset + dstOffset;
		int combinedOffsetHrs = combinedOffset / 1000 / 60 / 60;
		int combinedOffsetMins = combinedOffset / 1000 / 60 % 60;
		//log.debug("Total Offset Hours: " + combinedOffsetHrs);
		//log.debug("Total Offset Mins: " + combinedOffsetMins);

		//make an adjusted calendar to getTime from
		Calendar adjustedCalendar = Calendar.getInstance();
		adjustedCalendar.add(Calendar.HOUR_OF_DAY, (-combinedOffsetHrs));
		adjustedCalendar.add(Calendar.MINUTE, (-combinedOffsetMins));
		//log.debug("GMT Time: " + new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(adjustedCalendar.getTime()) + " + " + combinedOffsetHrs + ":" + combinedOffsetMins);

		new Thread(new Runnable() {
			@Override
			public void run() {
				try {
					Thread.currentThread().setName("ClientMain_initTime");
				} catch (SecurityException e) {
					e.printStackTrace();
				}

				String NTPhost = "time.nist.gov"; // this goes through lots of servers in round-robin, so keep trying.

				NTPUDPClient ntpUDPClient = new NTPUDPClient();
				ntpUDPClient.setDefaultTimeout(5000);

				int timeTryCount = 0;
				boolean haveTime = false;

				while (haveTime == false && timeTryCount < 5) {
					switch (timeTryCount) {
						case 0:
							NTPhost = "time.nist.gov";
							break;
						case 1:
							NTPhost = "nist1-sj.ustiming.org";
							break;
						case 2:
							NTPhost = "nisttime.carsoncity.k12.mi.us";
							break;
						case 3:
							NTPhost = "wwv.nist.gov";
							break;
						case 4:
							NTPhost = "nist1.symmetricom.com";
							break;
					}

					timeTryCount++;

					if (ntpUDPClient.isOpen() == true) {
						ntpUDPClient.close();
					}

					try {
						ntpUDPClient.open();
					} catch (SocketException e) {
						log.debug("Could not open NTP UDP Client: " + e.getMessage());
						continue;
					}

					InetAddress hostAddr = null;
					try {
						hostAddr = InetAddress.getByName(NTPhost);
					} catch (UnknownHostException e){
						log.debug("Could not resolve NTP host: " + NTPhost + " | " + e.getMessage());
						continue;
					}

					//log.debug("> " + hostAddr.getHostName() + "/" + hostAddr.getHostAddress());

					TimeInfo timeInfo = null;

					try {
						timeInfo = ntpUDPClient.getTime(hostAddr);
					} catch (IOException e) {
						log.debug("Could not get time from NTP host: " + hostAddr.getHostAddress() + " | " + e.getMessage());
						continue;
					}

					NtpV3Packet message = timeInfo.getMessage();

					// Transmit time is time reply sent by server (t3)
					TimeStamp xmitNtpTime = message.getTransmitTimeStamp();
					//log.debug(" Transmit Timestamp:\t" + xmitNtpTime + "  "+ xmitNtpTime.toDateString());

					Date serverDate = xmitNtpTime.getDate();
					log.info("Server Time (Adjusted by local TimeZone + DST): " + serverDate);
					// init game clock

					Calendar serverCalendar = Calendar.getInstance();
					serverCalendar.setTime(serverDate);

					int hour = serverCalendar.get(Calendar.HOUR_OF_DAY);
					int minute = serverCalendar.get(Calendar.MINUTE);
					int second = serverCalendar.get(Calendar.SECOND);
					int day = serverCalendar.get(Calendar.DAY_OF_WEEK) - 1;

					clientGameEngine.clock.setTime(day, hour, minute, second);

					ntpUDPClient.close();
					haveTime=true;
				}

				if(haveTime==false) {
					log.warn("Could not get time from NTP server! Falling back to local system time.");

					Calendar localCalendar = Calendar.getInstance();
					int hour = localCalendar.get(Calendar.HOUR_OF_DAY);
					int minute = localCalendar.get(Calendar.MINUTE);
					int second = localCalendar.get(Calendar.SECOND);
					int day = localCalendar.get(Calendar.DAY_OF_WEEK) - 1;

					clientGameEngine.clock.setTime(day, hour, minute, second);
				}
			}
		}).start();
	}

	public void doLegalScreen() {
		if (new File(Cache.cacheDir + "session").exists() == false) {
			//if(BobNet.debugMode==false)
			{
				log.info("Legal Screen...");

				LegalScreen legalScreen = new LegalScreen();
				GUI legalScreenGUI = new GUI(legalScreen, LWJGLUtils.TWLrenderer);
				legalScreenGUI.applyTheme(LWJGLUtils.TWLthemeManager);

				while (legalScreen.clickedOK_S() == false)  {
					glClear(GL_COLOR_BUFFER_BIT);

					legalScreen.update();
					legalScreenGUI.update();

					if((GLFW.glfwWindowShouldClose(LWJGLUtils.window) || (BobNet.debugMode == true && GLFW.glfwGetKey(LWJGLUtils.window, GLFW.GLFW_KEY_ESCAPE) == GLFW.GLFW_PRESS))
							|| legalScreen.clickedCancel_S() == true
					) {
						legalScreen.destroy();
						LWJGLUtils.TWLthemeManager.destroy();
						//Display.destroy();
						//AL.destroy();
						ClientMain.exit();
					}

					//Display.sync(60);
					//Display.update();
                    LWJGLUtils.updateDisplay();
					doResizeCheck();
				}

				legalScreen.destroy();
				glClear(GL_COLOR_BUFFER_BIT);

				log.info("Accepted Legal Screen.");
			}
		}
	}

	public void showControlsImage() {
		if (new File(Cache.cacheDir + "session").exists() == false) {
			//if(BobNet.debugMode==false)
			{
				KeyboardScreen keyboardScreen = new KeyboardScreen();
				GUI keyboardScreenGUI = new GUI(keyboardScreen, LWJGLUtils.TWLrenderer);
				keyboardScreenGUI.applyTheme(LWJGLUtils.TWLthemeManager);

				keyboardScreen.okButton.setVisible(true);
				keyboardScreen.setActivated(true);

				while (keyboardScreen.clickedOK_S() == false) {
					glClear(GL_COLOR_BUFFER_BIT);

					keyboardScreen.update();
					keyboardScreenGUI.update();

					//Display.sync(60);
					//Display.update();
                    LWJGLUtils.updateDisplay();
				}
				keyboardScreen.destroy();
				glClear(GL_COLOR_BUFFER_BIT);
			}
		}
	}

	public void makeGhostThread() {
		// ghost thread to prevent stuttering
		// this is due to windows aero, for some reason creating a ghost thread prevents it for some fucking reason
		new Thread(new Runnable() {
			@Override
			public void run() {
				try {
					Thread.currentThread().setName("ClientMain_ghostThreadToPreventAeroStutter");
				} catch (SecurityException e) {
					e.printStackTrace();
				}

				while (exit == false) {
					try {
						Thread.sleep(16);//this only seems to work at 16

						//Thread.yield(); //high cpu usage
						//if(Display.isActive()==false)Display.processMessages();
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		}).start();
	}

	public void initDebugLogger() {
		Logger rootLogger = (Logger) LoggerFactory.getLogger(Logger.ROOT_LOGGER_NAME);
		LoggerContext loggerContext = rootLogger.getLoggerContext();
		// we are not interested in auto-configuration
		loggerContext.reset();

		PatternLayoutEncoder consoleEncoder = new PatternLayoutEncoder();
		consoleEncoder.setContext(loggerContext);
		consoleEncoder.setPattern("%-50(%highlight(%-5level| %msg   )) \\(%F:%L\\) %boldMagenta(%c{2}.%M\\(\\)) %boldGreen([%thread]) \n");
		consoleEncoder.start();

		ConsoleAppender<ILoggingEvent> consoleAppender = new ConsoleAppender<ILoggingEvent>();
		consoleAppender.setWithJansi(true);
		consoleAppender.setContext(loggerContext);
		consoleAppender.setEncoder(consoleEncoder);
		consoleAppender.start();

		rootLogger.addAppender(consoleAppender);

		HTMLLayout htmlLayout = new HTMLLayout();
		htmlLayout.setPattern("%date{yyyy-MM-dd HH:mm:ss}%relative%thread%F%L%c{2}%M%level%msg");
		htmlLayout.setContext(loggerContext);
		htmlLayout.start();

		LayoutWrappingEncoder<ILoggingEvent> layoutEncoder = new LayoutWrappingEncoder<ILoggingEvent>();
		layoutEncoder.setLayout(htmlLayout);
		layoutEncoder.setContext(loggerContext);
		layoutEncoder.setImmediateFlush(false);
		layoutEncoder.start();

		FileAppender<ILoggingEvent> htmlFileAppender = new FileAppender<ILoggingEvent>();
		htmlFileAppender.setContext(loggerContext);
		htmlFileAppender.setEncoder(layoutEncoder);
		htmlFileAppender.setAppend(true);
		htmlFileAppender.setFile(Cache.cacheDir+"log.html");
		htmlFileAppender.start();

		rootLogger.addAppender(htmlFileAppender);

		PatternLayoutEncoder textEncoder = new PatternLayoutEncoder();
		textEncoder.setContext(loggerContext);
		textEncoder.setPattern("%date{yyyy-MM-dd HH:mm:ss} %-50(%-5level| %msg   ) [%thread] \n");
		textEncoder.setImmediateFlush(true);
		textEncoder.start();

		FileAppender<ILoggingEvent> textFileAppender = new FileAppender<ILoggingEvent>();
		textFileAppender.setContext(loggerContext);
		textFileAppender.setEncoder(textEncoder);
		textFileAppender.setAppend(true);
		textFileAppender.setFile(Cache.cacheDir+"log.txt");
		textFileAppender.start();

		rootLogger.addAppender(textFileAppender);

		rootLogger.setLevel(Level.ALL);
	}

	public void initReleaseLogger() {
		Logger rootLogger = (Logger) LoggerFactory.getLogger(Logger.ROOT_LOGGER_NAME);
		LoggerContext loggerContext = rootLogger.getLoggerContext();
		// we are not interested in auto-configuration
		loggerContext.reset();

		PatternLayoutEncoder consoleEncoder = new PatternLayoutEncoder();
		consoleEncoder.setContext(loggerContext);
		consoleEncoder.setPattern("%date{yyyy-MM-dd HH:mm:ss} %-50(%-5level| %msg   ) [%thread] \n");
		consoleEncoder.start();

		ConsoleAppender<ILoggingEvent> consoleAppender = new ConsoleAppender<>();
		consoleAppender.setWithJansi(false);
		consoleAppender.setContext(loggerContext);
		consoleAppender.setEncoder(consoleEncoder);
		consoleAppender.start();

		rootLogger.addAppender(consoleAppender);

		PatternLayoutEncoder textEncoder = new PatternLayoutEncoder();
		textEncoder.setContext(loggerContext);
		textEncoder.setPattern("%date{yyyy-MM-dd HH:mm:ss} %-50(%-5level| %msg   ) [%thread] \n");
		textEncoder.setImmediateFlush(true);
		textEncoder.start();

		FileAppender<ILoggingEvent> textFileAppender = new FileAppender<>();
		textFileAppender.setContext(loggerContext);
		textFileAppender.setEncoder(textEncoder);
		textFileAppender.setAppend(true);
		textFileAppender.setFile(Cache.cacheDir+"log.txt");
		textFileAppender.start();

		rootLogger.addAppender(textFileAppender);
	}

	public static Logger log = (Logger) LoggerFactory.getLogger(ClientMain.class);

	public volatile boolean exit = false;

	public static Cache cacheManager = new Cache();
	public StateManager stateManager;

	public ControlsManager controlsManager;

	public ClientGameEngine clientGameEngine;
	public ArrayDeque<ClientGameEngine> gameStack = new ArrayDeque<>();

	public Console console;

	public LoginState loginState;
	public LoggedOutState loggedOutState;
	public ServersHaveShutDownState serversHaveShutDownState;
	public CreateNewAccountState createNewAccountState;
	public TitleScreenState titleScreenState;
	public YouWillBeNotifiedState youWillBeNotifiedState;

	public static GlowTileBackground glowTileBackground;

	public boolean serversAreShuttingDown = false;

	//public SpriteAssetIndex spriteAssetManager;
	//public MapAssetIndex mapAssetManager;

	public String slash = System.getProperties().getProperty("file.separator");

	public static boolean isApplet = false;


	public Utils utils;
	public LWJGLUtils lwjglUtils;
	public StatsUtils statsUtils;
	public GLUtils glUtils;
	public static AudioUtils audioUtils;

	public GameClientTCP gameClientTCP;
	//public ClientUDP clientUDP;

	public static String serverAddress = BobNet.releaseServerAddress;
	public static String STUNServerAddress = BobNet.releaseSTUNServerAddress;

	public void mainInit() {
		boolean debugOnLiveServer = false;

		if (BobNet.debugMode == true || debugOnLiveServer) {
			System.setProperty("org.lwjgl.util.Debug", "true");
			System.setProperty("org.lwjgl.util.NoChecks", "false");

			serverAddress = BobNet.debugServerAddress;
			STUNServerAddress = BobNet.debugSTUNServerAddress;

			initDebugLogger();
		} else {
			System.setProperty("org.lwjgl.util.Debug","false");
			System.setProperty("org.lwjgl.util.NoChecks","true");

			initReleaseLogger();
		}

		log.info("Main Init...");

		lwjglUtils = new LWJGLUtils();

		LWJGLUtils.setDisplayMode();

		// this is done before init game so we can put debug stuff
		console = new Console();
		utils = new Utils();

		LWJGLUtils.initGL("Project 2");
		LWJGLUtils.initTWL();
		LWJGLUtils.initControllers();

		audioUtils = new AudioUtils();
		glUtils = new GLUtils();
		statsUtils = new StatsUtils();

		StatsUtils.initDebugInfo();

		if (previewClientInEditor == false && BobNet.debugMode == false) {
			doLegalScreen();
		}

		cacheManager.initCache();

		stateManager = new StateManager();

		// init game
		log.info("Init Client...");
		makeNewClientEngine();

		// init login GUI
		log.info("Init GUIs...");
		if (glowTileBackground == null) {
			glowTileBackground = new GlowTileBackground();
		}

		loginState = new LoginState();
		loggedOutState = new LoggedOutState();
		serversHaveShutDownState = new ServersHaveShutDownState();
		createNewAccountState = new CreateNewAccountState();
		titleScreenState = new TitleScreenState();
		youWillBeNotifiedState = new YouWillBeNotifiedState();

		// TODO: check cookie exists
		// TODO: check cache/intro
		// TODO: check registry property

		if (previewClientInEditor == false) {
			boolean didIntro = false; //Cache.doesDidIntroFileExist();

			if (didIntro == false) {
				introMode = true;

				log.info("Setup Intro...");

				clientGameEngine.statusBar.gameStoreButton.setEnabled(false);
				clientGameEngine.statusBar.ndButton.setEnabled(false);
				clientGameEngine.statusBar.stuffButton.setEnabled(false);
				clientGameEngine.statusBar.moneyCaption.setEnabled(false);
				clientGameEngine.statusBar.dayCaption.setEnabled(false);

				stateManager.setState(clientGameEngine);
				clientGameEngine.cinematicsManager.fadeFromBlack(10000);

				clientGameEngine.mapManager.changeMap("ALPHABobsApartment","atDesk");
				//clientGameEngine.mapManager.changeMap("GENERIC1UpstairsBedroom1",12*8*2,17*8*2);
				//clientGameEngine.textManager.text("Yep \"Yuu\" yay. <.><1>bob! yay, \"bob\" yay! <.><0>\"Yuu\" yay, nD. yay yay \"bob's game\" yay- bob's? yay \"bob's\" yay bob's game<1>yep");
			} else {
				if (BobNet.debugMode == false) {
					showControlsImage();
				}
				stateManager.setState(loginState);
			}
		}

		initTime();

		//-------------------
		//fill in the client session info to send to the server for debug/stats
		//this must be done after everything is initialized.
		//-------------------
		initClientInfo();
	}

	public void makeNewClientEngine() {
		if (clientGameEngine != null) {
			clientGameEngine.cleanup();
		}

		if (gameClientTCP != null) {
			gameClientTCP.cleanup();
		}

		controlsManager = new ControlsManager();
		clientGameEngine = new ClientGameEngine();

		Engine.setClientGameEngine(clientGameEngine);
		Engine.setControlsManager(controlsManager);

		//stateManager.setState(game);

		clientGameEngine.init();

		// init network
		gameClientTCP = new GameClientTCP(clientGameEngine);
	}

	public static boolean introMode = false;
	public static boolean previewClientInEditor = false;

	boolean debugKeyPressed = false;
	boolean screenShotKeyPressed = false;
	boolean resize = false;

	// this is called from the browser javascript on window.focus
	public void focus() {
		resize = true;

		//this.requestFocus();

		//if (isApplet == true) {
		//	appletCanvas.requestFocus();
		//	appletCanvas.requestFocusInWindow();
		//}
	}

	// this is called from the browser javascript on window.blur
	public void blur() {
	}

	public static String facebookID = "";
	public static String facebookAccessToken = "";
	public static boolean _gotFacebookResponse = false;


	public synchronized static void setGotFacebookResponse_S(boolean b) {
		_gotFacebookResponse = b;
	}

	public synchronized static boolean getGotFacebookResponse_S() {
		return _gotFacebookResponse;
	}

	//this is called from the browser javascript after we call the facebook JS SDK
	public void setFacebookCredentials(String facebookID, String accessToken) {
		ClientMain.facebookID = facebookID;
		ClientMain.facebookAccessToken = accessToken;
		setGotFacebookResponse_S(true);
	}

	public void mainLoop() {
		makeGhostThread();
		focus();
		StatsUtils.initTimers();

		log.info("Begin Main Loop...");

		while (exit == false) {
			if (GLFW.glfwWindowShouldClose(LWJGLUtils.window) || (BobNet.debugMode == true && GLFW.glfwGetKey(LWJGLUtils.window, GLFW.GLFW_KEY_ESCAPE) == GLFW.GLFW_PRESS)) {
				exit = true;
			}

			StatsUtils.updateTimers();
			StatsUtils.updateDebugInfo();

			//if(ticksPassed>0)
			{
				//clientTCP.update();
				controlsManager.update();

				stateManager.update();
				console.update();

				glClear(GL_COLOR_BUFFER_BIT);
				stateManager.render();

				LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				console.render();
				//LWJGLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			}

			if (serversAreShuttingDown) {
                // TODO: fix display width/height
				GLUtils.drawFilledRect(0, 0, 0, 0, 1280, 0, 720, 0.2f);
				GLUtils.drawOutlinedString("The servers are shutting down soon for updating.", 1280/2-60, 720/2-12, BobColor.white);
			}

            // TODO: Check window focus
			if (false && BobNet.debugMode == false) {
				GLUtils.drawFilledRect(0, 0, 0, 0, 1280, 0, 720, 0.5f);
				GLUtils.drawOutlinedString("Low power mode. Click to resume.", 1280 / 2 - 70, 720/  2 - 12, BobColor.white);

				//Display.sync(10);
                // TODO: sleep

				/*if (Display.isVisible()) {
					Display.update();
				} else {
					Display.processMessages();
				}*/
                LWJGLUtils.updateDisplay();

				//Display.update();
			} else {
				if (LWJGLUtils.vsync) {
					try {
						// this just lowers cpu usage
						Thread.sleep(2); // TODO: vary this based on system speed
						//System.gc();
						Thread.yield();
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
				//Display.update();
                LWJGLUtils.updateDisplay();
			}
			doScreenShotCheck();
			doResizeCheck();
			LWJGLUtils.checkForGLError();
		}
	}

	public void doResizeCheck() {
		// log.info("Display.getWidth() x Display.getHeight():"+Display.getWidth()+" x "+Display.getHeight());
		// log.info("getWidth() x getHeight():"+getWidth()+" x "+getHeight());

		/*if (Display.wasResized() == true || resize == true) {
			resize = false;

			// reset GL model matrix, etc.
			log.info("Resized window.");

			lastDisplayWidth = Display.getWidth();
			lastDisplayHeight = Display.getHeight();
			//lastWidth = getWidth();
			//lastHeight = getHeight();

			if (isApplet) {
				lastAppletCanvasWidth = appletCanvas.getWidth();
				lastAppletCanvasHeight = appletCanvas.getHeight();
			}

			LWJGLUtils.doResize();
		}*/
	}

	public void doScreenShotCheck() {
		boolean takeScreenShot = false;

		if (GLFW.glfwGetKey(LWJGLUtils.window, GLFW.GLFW_KEY_F12) == GLFW.GLFW_PRESS) {
			if (screenShotKeyPressed == false) {
				screenShotKeyPressed = true;
				takeScreenShot = true;
			}
		} else {
			screenShotKeyPressed = false;
		}

		if (takeScreenShot) {
			clientGameEngine.audioManager.playSound("screenShot", 1.0f, 1.0f, 1);

			String imageName = "bobsgame-" + new SimpleDateFormat("yyyy-MM-dd-HH-mm-ss").format(Calendar.getInstance().getTime()) + ".png";
			String fileName = "";

			if (System.getProperty("os.name").contains("Win")) {
				Console.add("Saved screenshot on Desktop.", BobColor.green, 3000);
				fileName = System.getProperty("user.home") + Cache.slash + "Desktop" + Cache.slash + imageName;
			} else {
				Console.add("Saved screenshot in home folder.", BobColor.green, 3000);
				fileName = System.getProperty("user.home") + Cache.slash + imageName;
			}

			glReadBuffer(GL_FRONT);

			int width = LWJGLUtils.SCREEN_SIZE_X;
			int height = LWJGLUtils.SCREEN_SIZE_Y;

			int bytesPerPixel = 4;

			ByteBuffer buffer = BufferUtils.createByteBuffer(width * height * bytesPerPixel);
			glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

			File file = new File(fileName);
			String format = "PNG";
			BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);

			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++) {
					int i = (x + (width * y)) * bytesPerPixel;
					int r = buffer.get(i) & 0xFF;
					int g = buffer.get(i + 1) & 0xFF;
					int b = buffer.get(i + 2) & 0xFF;
					image.setRGB(x, height - (y + 1), (0xFF << 24) | (r << 16) | (g << 8) | b);
				}
			}

			try {
				ImageIO.write(image, format, file);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		boolean printLog = false;

		if (GLFW.glfwGetKey(LWJGLUtils.window, GLFW.GLFW_KEY_F11) == GLFW.GLFW_PRESS) {
			if (debugKeyPressed == false) {
				debugKeyPressed = true;
				printLog = true;
			}
		} else {
			debugKeyPressed = false;
		}

		if (printLog) {
			String imageName = "bobsgame-" + new SimpleDateFormat("yyyy-MM-dd-HH-mm-ss").format(Calendar.getInstance().getTime()) + ".txt";
			String fileName = "";

			if (System.getProperty("os.name").contains("Win")) {
				Console.add("Saved debug log on Desktop.", BobColor.green, 3000);
				fileName = System.getProperty("user.home") + Cache.slash + "Desktop" + Cache.slash + imageName;
			} else {
				Console.add("Saved debug log in home folder.", BobColor.green, 3000);
				fileName = System.getProperty("user.home") + Cache.slash + imageName;
			}

			Writer output = null;

			try {
				output = new BufferedWriter(new FileWriter(fileName));

				String s = FileUtils.readFileToString(new File(Cache.cacheDir + "log.txt"), StandardCharsets.UTF_8);
				s = s + "\n";
				output.write(s);

				output.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	public void cleanup() throws Exception {
		// end main loop, cleanup
		log.info("Cleaning up...");

		try {
			//Display.setParent(null);
		} catch (Exception e) {
			e.printStackTrace();
		}

		try {
			//AL.destroy();
		} catch (Exception e) {
			e.printStackTrace();
		}

		try {
			gameClientTCP.cleanup();
			clientGameEngine.cleanup();
		} catch (Exception e) {
			e.printStackTrace();
		}

		try {
			loginState.cleanup();
			createNewAccountState.cleanup();
			LWJGLUtils.TWLthemeManager.destroy();
		} catch (Exception e) {
			e.printStackTrace();
		}

		//loggedOutState.cleanup();
		//serversHaveShutDownState.cleanup();
		//titleScreenState.cleanup();
		//youWillBeNotifiedState.cleanup();
		//glowTileBackground.cleanup();

		try{
			//Display.destroy();
            LWJGLUtils.destroy();
		} catch (Exception e) {
			e.printStackTrace();
		}

		log.info("Exiting...");
	}
}