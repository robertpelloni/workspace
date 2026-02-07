package com.bobsgame;

import java.io.File;
import java.io.IOException;


import com.bobsgame.stunserver.STUNServerUDP;
import org.apache.commons.io.FileUtils;


import org.slf4j.LoggerFactory;



import ch.qos.logback.classic.*;
import ch.qos.logback.classic.encoder.PatternLayoutEncoder;
import ch.qos.logback.classic.filter.ThresholdFilter;
import ch.qos.logback.classic.html.HTMLLayout;
import ch.qos.logback.classic.spi.ILoggingEvent;
import ch.qos.logback.core.ConsoleAppender;
import ch.qos.logback.core.FileAppender;
import ch.qos.logback.core.encoder.LayoutWrappingEncoder;


//===============================================================================================
public class STUNServerMain
{//===============================================================================================




	public static Logger log = (Logger) LoggerFactory.getLogger(STUNServerMain.class);


	public static STUNServerMain stunServerMain = null;
	public static STUNServerUDP serverUDP;




	//===============================================================================================
	public static void main(String[] args)
	{//===============================================================================================

		Logger rootLogger = (Logger)LoggerFactory.getLogger(Logger.ROOT_LOGGER_NAME);
		LoggerContext loggerContext = rootLogger.getLoggerContext();
		// we are not interested in auto-configuration
		loggerContext.reset();

		PatternLayoutEncoder encoder = new PatternLayoutEncoder();
		encoder.setContext(loggerContext);
		encoder.setPattern("%-50(%highlight(%-5level| %msg   )) \\(%F:%L\\) %boldMagenta(%c{2}.%M\\(\\)) %boldGreen([%thread]) \n");
		encoder.start();

		ConsoleAppender<ILoggingEvent> appender = new ConsoleAppender<ILoggingEvent>();
		appender.setWithJansi(true);
		appender.setContext(loggerContext);
		appender.setEncoder(encoder);
		appender.start();

		rootLogger.addAppender(appender);



		HTMLLayout htmlLayout = new HTMLLayout();
		htmlLayout.setPattern("%date{yyyy-MM-dd HH:mm:ss}%relative%thread%F%L%c{2}%M%level%msg");
		htmlLayout.setContext(loggerContext);
		htmlLayout.start();

		LayoutWrappingEncoder<ILoggingEvent> layoutEncoder = new LayoutWrappingEncoder<ILoggingEvent>();
		layoutEncoder.setLayout(htmlLayout);
		layoutEncoder.setContext(loggerContext);
		layoutEncoder.setImmediateFlush(true);
		layoutEncoder.start();

		ThresholdFilter filter = new ThresholdFilter();
		filter.setLevel("WARN");
		filter.setContext(loggerContext);

		FileAppender<ILoggingEvent> fileAppender = new FileAppender<ILoggingEvent>();
		fileAppender.setContext(loggerContext);
		fileAppender.setEncoder(layoutEncoder);
		fileAppender.addFilter(filter);
		fileAppender.setAppend(true);
		fileAppender.setFile("/var/www/html/log.html");
		fileAppender.start();

		rootLogger.addAppender(fileAppender);





		//LoggerContext lc = (LoggerContext) LoggerFactory.getILoggerFactory();
		//StatusPrinter.print(lc);


		//rootLogger.debug("debug test");
		//rootLogger.info("info test");
		//rootLogger.warn("warn test");
		//rootLogger.error("error test");


		log.setLevel(Level.ALL);

		stunServerMain = new STUNServerMain();

		stunServerMain.run();

	}




	static public boolean exit = false;


	public long ticksSincePublishedLog = 0;

	public long startTime = System.currentTimeMillis();
	public long lastTime = System.currentTimeMillis();



	static public Runtime rt = null;
	static public int mb = 1024*1024;

	static public long usedMemory = 0;
	static public long maxUsedMemory = 0;
	static public long totalMemory = 0;
	static public long freeMemory = 0;
	static public long maxMemory = 0;


	public static long totalSTUNsCompleted = 0;
	public static long totalSTUNsTimedOut = 0;
	public static long totalConnections = 0;


	//===============================================================================================
	public void run()
	{//===============================================================================================


		rt = Runtime.getRuntime();
		totalMemory = rt.totalMemory();
		freeMemory = rt.freeMemory();
		maxMemory = rt.maxMemory();


		new Thread
		(
			new Runnable()
			{
				public void run()
				{
					while(exit==false)
					{



						STUNServerMain.serverUDP.update();




						long nowTime = System.currentTimeMillis();

						long ticksPassed = nowTime-lastTime;

						lastTime = nowTime;

						ticksSincePublishedLog+=ticksPassed;

						if(ticksSincePublishedLog>5000)
						{
							ticksSincePublishedLog=0;

							totalMemory = rt.totalMemory();
							freeMemory = rt.freeMemory();

							usedMemory = (totalMemory-freeMemory)/mb;
							if(usedMemory>maxUsedMemory)maxUsedMemory = usedMemory;


							String usedMemText = "Used: "+usedMemory+" MB";
							String maxUsedMemText = "Max Used: "+maxUsedMemory+" MB";
							String freeMemText = "Free: "+freeMemory/mb+" MB";
							String totalMemText = "Total: "+ totalMemory/mb + " MB";
							String maxMemText = "Max: " + maxMemory/mb+" MB";

							String uptimeSecondsText = "Uptime Seconds: "+((lastTime-startTime) / 1000);


							String totalConnectionsText = "Total Connections: "+totalConnections;
							String totalSTUNsCompletedText = "Total STUNs Completed: "+totalSTUNsCompleted;
							String totalSTUNsTimedOutText = "Total STUNs Timed Out :"+totalSTUNsTimedOut;


							String statsString =
							"<html>"
							+"<head>"
							+"<title>STUN STATS</title>"
							+"</head>"
							+"<body>"
							+"<br>"
							+"<br>"+usedMemText
							+"<br>"+maxUsedMemText
							+"<br>"+freeMemText
							+"<br>"+totalMemText
							+"<br>"+maxMemText
							+"<br>"
							+"<br>"+uptimeSecondsText
							+"<br>"
							+"<br>"+totalConnectionsText
							+"<br>"+totalSTUNsCompletedText
							+"<br>"+totalSTUNsTimedOutText
							+"<br>"
							+"<br>"+"Queued Requests: "+serverUDP.getSTUNRequestListSize()
							+"<br>"
							+"</body>"
							+"</html>"
							;

							//DONE: write system stats out to /var/www/stats.htm
							try
							{
								FileUtils.writeStringToFile(new File("/var/www/html/stats.html"),statsString,false);
							}
							catch(IOException e)
							{
								e.printStackTrace();
							}


						}


						try
						{
							Thread.sleep(100);
						}
						catch(InterruptedException e)
						{
							e.printStackTrace();
						}

					}
				}
			}
		).start();

	}



	//===============================================================================================
	public STUNServerMain()
	{//===============================================================================================
		serverUDP = new STUNServerUDP();
	}



}
