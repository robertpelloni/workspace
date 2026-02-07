package com.bobsgame.client;

import java.lang.management.ManagementFactory;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.console.Console;
import com.bobsgame.client.console.ConsoleText;
import com.bobsgame.client.state.State;
import com.bobsgame.net.BobNet;
import com.bobsgame.shared.BobColor;
import org.lwjgl.Version;

//=========================================================================================================================
public class StatsUtils
{//=========================================================================================================================



	public static Logger log = (Logger) LoggerFactory.getLogger(StatsUtils.class);




	//=========================================================================================================================

	static ConsoleText totalFramesText;
	static ConsoleText framePerSecondText;
	static ConsoleText framesSkippedText;
	static ConsoleText averageTicksText;
	static ConsoleText upTimeText;

	static ConsoleText ticksText0;
	static ConsoleText ticksText1;
	static ConsoleText ticksText2;
	static ConsoleText ticksText3;
	static ConsoleText ticksText4;
	static ConsoleText ticksText5;
	static ConsoleText ticksText6;
	static ConsoleText ticksText7;
	static ConsoleText ticksText8;
	static ConsoleText ticksText9;

	private static long lastFrameTicks = 0;
	private static int ticksTextCount=0;
	private static long averageTicksPerFrameLastSecond = 0;

	//=========================================================================================================================
	public static void initFrameStats()
	{//=========================================================================================================================

		totalFramesText = Console.debug("totalFramesText");
		framePerSecondText = Console.debug("framePerSecondText");
		framesSkippedText = Console.debug("framesSkippedText");

		averageTicksText = Console.debug("averageTicksText");
		upTimeText = Console.debug("upTimeText");

		if(BobNet.debugMode==true)
		{
			ticksText0 = Console.debug("ticksText0");
			ticksText1 = Console.debug("ticksText1");
			ticksText2 = Console.debug("ticksText2");
			ticksText3 = Console.debug("ticksText3");
			ticksText4 = Console.debug("ticksText4");
			ticksText5 = Console.debug("ticksText5");
			ticksText6 = Console.debug("ticksText6");
			ticksText7 = Console.debug("ticksText7");
			ticksText8 = Console.debug("ticksText8");
			ticksText9 = Console.debug("ticksText9");
		}
	}

	//=========================================================================================================================
	public static void updateFrameStats()
	{//=========================================================================================================================

		totalFramesText.text = "Frames: " + totalFrames;
		framesSkippedText.text = "Frames Skipped: " + framesSkipped;

		upTimeText.text = "Uptime: " + totalTicks/1000 + "s ("+totalTicks+"ms)";



		//if a second has passed
		if(currentTicks>=lastSecondTicks+1000)
		{

			averageTicksPerFrameLastSecond = (currentTicks-lastSecondTicks)/framesThisSecond;

			if(framesThisSecond==60)framePerSecondText.color=BobColor.white;
			else framePerSecondText.color=BobColor.red;
			framePerSecondText.text = "FPS: " + framesThisSecond;
			averageTicksText.text = "Average Ticks Per Frame (Last Second): " + averageTicksPerFrameLastSecond;

			lastSecondTicks+=1000;
			framesThisSecond=0;
		}


		if(BobNet.debugMode==true)
		{

			long thisFrameTicks = currentTicks;//System.nanoTime()/1000/1000;
			long debugTicksPassed = thisFrameTicks-lastFrameTicks;
			lastFrameTicks = thisFrameTicks;

			if(ticksTextCount==0){ticksText0.text = "Ticks Passed 0: " + debugTicksPassed;if(debugTicksPassed>17)ticksText0.color=BobColor.red;else ticksText0.color=BobColor.white;}
			if(ticksTextCount==1){ticksText1.text = "Ticks Passed 1: " + debugTicksPassed;if(debugTicksPassed>17)ticksText1.color=BobColor.red;else ticksText1.color=BobColor.white;}
			if(ticksTextCount==2){ticksText2.text = "Ticks Passed 2: " + debugTicksPassed;if(debugTicksPassed>17)ticksText2.color=BobColor.red;else ticksText2.color=BobColor.white;}
			if(ticksTextCount==3){ticksText3.text = "Ticks Passed 3: " + debugTicksPassed;if(debugTicksPassed>17)ticksText3.color=BobColor.red;else ticksText3.color=BobColor.white;}
			if(ticksTextCount==4){ticksText4.text = "Ticks Passed 4: " + debugTicksPassed;if(debugTicksPassed>17)ticksText4.color=BobColor.red;else ticksText4.color=BobColor.white;}
			if(ticksTextCount==5){ticksText5.text = "Ticks Passed 5: " + debugTicksPassed;if(debugTicksPassed>17)ticksText5.color=BobColor.red;else ticksText5.color=BobColor.white;}
			if(ticksTextCount==6){ticksText6.text = "Ticks Passed 6: " + debugTicksPassed;if(debugTicksPassed>17)ticksText6.color=BobColor.red;else ticksText6.color=BobColor.white;}
			if(ticksTextCount==7){ticksText7.text = "Ticks Passed 7: " + debugTicksPassed;if(debugTicksPassed>17)ticksText7.color=BobColor.red;else ticksText7.color=BobColor.white;}
			if(ticksTextCount==8){ticksText8.text = "Ticks Passed 8: " + debugTicksPassed;if(debugTicksPassed>17)ticksText8.color=BobColor.red;else ticksText8.color=BobColor.white;}
			if(ticksTextCount==9){ticksText9.text = "Ticks Passed 9: " + debugTicksPassed;if(debugTicksPassed>17)ticksText9.color=BobColor.red;else ticksText9.color=BobColor.white;}

			ticksTextCount++;
			if(ticksTextCount>9)ticksTextCount=0;

		}

	}



	//=========================================================================================================================

	static ConsoleText mxThreadCountText;

	//=========================================================================================================================
	public static void initThreadStats()
	{//=========================================================================================================================



		mxThreadCountText = Console.debug("mxThreadCountText");


	}

	//=========================================================================================================================
	public static void updateThreadStats()
	{//=========================================================================================================================
		mxThreadCountText.text =
				"Thread Count: "+ManagementFactory.getThreadMXBean().getThreadCount()
				+" | Daemon Thread Count: "+ManagementFactory.getThreadMXBean().getDaemonThreadCount()
				+" | Peak Thread Count: "+ManagementFactory.getThreadMXBean().getPeakThreadCount()
				+" | Total Started: "+ManagementFactory.getThreadMXBean().getTotalStartedThreadCount()
				;

	}



	//=========================================================================================================================

	static ConsoleText memoryText;

	public static int mb = 1024*1024;

	public static long usedMemory = 0;
	public static long maxUsedMemory = 0;
	public static long totalMemory = 0;
	public static long freeMemory = 0;
	public static long maxMemory = 0;

	//mxbean
	//DebugText mxBeanHeapMemoryText;
	//DebugText mxBeanNonHeapMemoryText;
	//DebugText mxBeanUnfinalizedObjectsText;
	//DebugText memPoolThresholdCountText;
	//DebugText mxOSInfoSystemLoadText;

	ConsoleText vramText;


	//mxbean
	//long committedNonHeapMemory = 0;
	//long initNonHeapMemory = 0;
	//long maxNonHeapMemory = 0;
	//long usedNonHeapMemory = 0;

	//GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
	//GraphicsDevice[] gs = ge.getScreenDevices();
	//GraphicsDevice gd = gs[0];

	//=========================================================================================================================
	public static void initMemoryStats()
	{//=========================================================================================================================

		memoryText = Console.debug("memoryText");


		//mxBeanHeapMemoryText = DebugConsole.add("mxBeanHeapMemoryText");
		//mxBeanNonHeapMemoryText = DebugConsole.add("mxBeanNonHeapMemoryText");
		//mxBeanUnfinalizedObjectsText = DebugConsole.add("mxBeanUnfinalizedObjectsText");
		//memPoolThresholdCountText = DebugConsole.add("memPoolThresholdCountText");
		//mxOSInfoSystemLoadText = DebugConsole.add("mxOSInfoSystemLoadText");

		//vramText = DebugConsole.add("vramText");



		totalMemory = rt.totalMemory();
		freeMemory = rt.freeMemory();
		maxMemory = rt.maxMemory();

	}


	//=========================================================================================================================
	public static void updateMemoryStats()
	{//=========================================================================================================================

		//if(currentTicks>=last100Ticks+100)
		{


			//TODO: checking the memory stuff each frame caused some slowdowns/crashes or something, can't remember.

			//for(int i=0;i<100;i++)
			{
				totalMemory = rt.totalMemory();
				freeMemory = rt.freeMemory();
				//maxMemory = rt.maxMemory();
				//gd.getAvailableAcceleratedMemory();

				//committedNonHeapMemory = ManagementFactory.getMemoryMXBean().getNonHeapMemoryUsage().getCommitted();
				//initNonHeapMemory = ManagementFactory.getMemoryMXBean().getNonHeapMemoryUsage().getInit();
				//maxNonHeapMemory = ManagementFactory.getMemoryMXBean().getNonHeapMemoryUsage().getMax();
				//usedNonHeapMemory = ManagementFactory.getMemoryMXBean().getNonHeapMemoryUsage().getUsed();
				//mxBeanNonHeapMemoryText.text = "NonHeap Init: "+initNonHeapMemory/mb+" MB | Committed: "+committedNonHeapMemory/mb+" MB | Used: "+usedNonHeapMemory/mb+" MB | Max: "+maxNonHeapMemory/mb+" MB";


				//mxBeanUnfinalizedObjectsText.text = "Objects Pending Finalization: "+ManagementFactory.getMemoryMXBean().getObjectPendingFinalizationCount();

				//these don't work
				//memPoolThresholdCountText.text = "Mempool Threshold Reached Count: "+ManagementFactory.getMemoryPoolMXBeans().get(0).getCollectionUsageThresholdCount();
				//mxOSInfoSystemLoadText.text = "Average System Load: "+ManagementFactory.getOperatingSystemMXBean().getSystemLoadAverage();
			}


			usedMemory = (totalMemory-freeMemory)/mb;
			if(usedMemory>maxUsedMemory)maxUsedMemory = usedMemory;

			memoryText.text =
					"Used: "+usedMemory+" MB" +
					" | Max Used: "+maxUsedMemory+" MB" +
					" | Free: "+freeMemory/mb+" MB" +
					" | Total: "+ totalMemory/mb + " MB" +
					" | Max: " + maxMemory/mb+" MB"
					;

			//vramText.text = "Available VRAM: "+gd.getAvailableAcceleratedMemory()/1024 +" KB";


			//last100Ticks+=100;
		}

	}







	//=========================================================================================================================

	public static Runtime rt;

	//=========================================================================================================================
	public static void initDebugInfo()
	{//=========================================================================================================================

		rt = Runtime.getRuntime();


		//------------------------------
		// debug console
		//------------------------------

		if(LWJGLUtils.vsync)Console.debug("Vsync: on");
		else Console.debug("Vsync: off");

//		Console.debug("Display Adapter: " + Display.getAdapter());
//		Console.debug("Display Driver Version: " + Display.getVersion());
		Console.debug("LWJGL Version: " + Version.getVersion());
//		Console.debug("LWJGL Platform: " + LWJGLUtil.getPlatformName());
//		Console.debug("Num CPUs: " +rt.availableProcessors());



		// OS Information
		Console.debug("OS Name: " + System.getProperty("os.name"));
		Console.debug("OS Arch: " + System.getProperty("os.arch"));
		Console.debug("OS Version: " + System.getProperty("os.version"));
		Console.debug("Available Processors (Cores): " + rt.availableProcessors());

		java.lang.management.OperatingSystemMXBean osBean = ManagementFactory.getOperatingSystemMXBean();
		Console.debug("System Load Average: " + osBean.getSystemLoadAverage());

        // Try to cast to com.sun.management.OperatingSystemMXBean for more info if available
        if (osBean instanceof com.sun.management.OperatingSystemMXBean) {
            com.sun.management.OperatingSystemMXBean sunOsBean = (com.sun.management.OperatingSystemMXBean) osBean;
            Console.debug("Total Physical Memory: " + sunOsBean.getTotalMemorySize() / (1024*1024) + " MB");
            Console.debug("Free Physical Memory: " + sunOsBean.getFreeMemorySize() / (1024*1024) + " MB");
            Console.debug("Process CPU Load: " + String.format("%.2f", sunOsBean.getProcessCpuLoad() * 100) + "%");
            Console.debug("System CPU Load: " + String.format("%.2f", sunOsBean.getCpuLoad() * 100) + "%");
        }

		//TODO: lwjgl can get graphics driver information, need to get more of that.
		//TODO: slick-network-game example gets sound card info, joystick info, part of slick. need to use this.

		initFrameStats();
		initMemoryStats();
		initThreadStats();

	}

	//=========================================================================================================================
	public static void updateDebugInfo()
	{//=========================================================================================================================

		updateFrameStats();
		updateMemoryStats();
		updateThreadStats();

	}




	//=========================================================================================================================

	private static int totalFrames=0;
	private static long lastTicks = System.nanoTime()/1000/1000;//Sys.getTime();
	private static long currentTicks = lastTicks;

	private static long ticksPassed = 0;

	private static int framesThisSecond=0;
	private static long lastSecondTicks=lastTicks;
	//private static long last100Ticks=lastTicks;

	private static long totalTicks = 0;
	private static int framesSkipped=0;

	//=========================================================================================================================
	public static void initTimers()
	{//=========================================================================================================================
		lastTicks = System.nanoTime()/1000/1000;

	}

	//=========================================================================================================================
	public static void updateTimers()
	{//=========================================================================================================================
		framesThisSecond++;
		totalFrames++;


		//get time passed since last frame
		currentTicks = System.nanoTime()/1000/1000;//Sys.getTime();
		ticksPassed = currentTicks-lastTicks;

		State.lastTicks = lastTicks;
		State.mainTicksPassed = ticksPassed;

		lastTicks = currentTicks;
		totalTicks+=ticksPassed;


		//if(ticksPassed>17)ticksPassed=17; //TODO: this is frameskip off, basically. game will slow down instead
		if(ticksPassed>16*2)framesSkipped++;//= ticksPassed/16;

	}








}
