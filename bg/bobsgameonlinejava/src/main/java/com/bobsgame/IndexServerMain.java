package com.bobsgame;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.InetAddress;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.UnknownHostException;


import com.bobsgame.serverindex.IndexServerTCP;
import org.apache.commons.io.FileUtils;


import org.slf4j.LoggerFactory;



import ch.qos.logback.classic.Level;
import ch.qos.logback.classic.Logger;
import ch.qos.logback.classic.LoggerContext;
import ch.qos.logback.classic.encoder.PatternLayoutEncoder;
import ch.qos.logback.classic.html.HTMLLayout;
import ch.qos.logback.classic.spi.ILoggingEvent;
import ch.qos.logback.core.ConsoleAppender;
import ch.qos.logback.core.FileAppender;
import ch.qos.logback.core.encoder.LayoutWrappingEncoder;

import com.bobsgame.net.*;


//===============================================================================================
public class IndexServerMain
{//===============================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(IndexServerMain.class);//BobsGameServerHandler.class.getName());

	static public IndexServerTCP indexServerTCP;
	public static IndexServerMain indexServerMain = null;


	public static String myIPAddressString = "";
	public static InetAddress myIPAddress = null;

	//===============================================================================================
	public static void main(String[] args)
	{//===============================================================================================



		Logger rootLogger = (Logger) LoggerFactory.getLogger(Logger.ROOT_LOGGER_NAME);
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

		FileAppender<ILoggingEvent> fileAppender = new FileAppender<ILoggingEvent>();
		fileAppender.setContext(loggerContext);
		fileAppender.setEncoder(layoutEncoder);
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

		indexServerMain = new IndexServerMain();

		indexServerMain.run();
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



						// check for existence of /home/ubuntu/warnClients
						// check for existence of /home/ubuntu/rebootServers

						File warnClients = new File("/home/ubuntu/warnClients");

						if(warnClients.exists()==true)
						{
							warnClients.delete();

							indexServerTCP.send_Tell_All_Servers_To_Tell_All_Clients_Servers_Are_Shutting_Down();

						}



						File rebootServers = new File("/home/ubuntu/rebootServers");

						if(rebootServers.exists()==true)
						{

							rebootServers.delete();

							indexServerTCP.send_Tell_All_Servers_To_Tell_All_Clients_Servers_Have_Shut_Down();

						}





						//DONE: output master stats page every 5 seconds

						//put my own stats, iframe my logs

						//iframe each server ip address/stats.htm and log.htm

						//iframe STUN server stats.htm and log.htm




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


							String serversConnectedText = "Servers Connected: "+indexServerTCP.serverList.size();



							String statsString =
							"<html>"
							+"<head>"
							+"<title>INDEX STATS</title>"
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
							+"<br>"+serversConnectedText
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







							String indexString =
							"<html>"
							+"<head>"
							+"<title>ALL SERVER STATS</title>"
							+"</head>"
							+"<body>"
							+"<br>";


							indexString = indexString
							+"<br>"+"INDEX STATS"
							+"<br>"+"<iframe src=\"http://index.bobsgame.com/stats.html\" width=\"100%\" height=\"300\"></iframe>"
							+"<br>"
							+"<br>"+"INDEX LOG"
							+"<br>"+"<iframe src=\"http://index.bobsgame.com/log.html\" width=\"100%\" height=\"300\"></iframe>"
							+"<br>"
							+"<br>";


							indexString = indexString
							+"<br>"+"STUN STATS"
							+"<br>"+"<iframe src=\"http://stun.bobsgame.com/stats.html\" width=\"100%\" height=\"300\"></iframe>"
							+"<br>"
							+"<br>"+"STUN LOG"
							+"<br>"+"<iframe src=\"http://stun.bobsgame.com/log.html\" width=\"100%\" height=\"300\"></iframe>"
							+"<br>"
							+"<br>";

							for(int i=0;i<indexServerTCP.serverList.size();i++)
							{

								indexString = indexString
								+"<br>"+"SERVER "+i+" STATS"
								+"<br>"+"<iframe src=\"http://"+indexServerTCP.serverList.get(i).ipAddressString+"/stats.html\" width=\"100%\" height=\"300\"></iframe>"
								+"<br>"
								+"<br>"+"SERVER "+i+" LOG"
								+"<br>"+"<iframe src=\"http://"+indexServerTCP.serverList.get(i).ipAddressString+"/log.html\" width=\"100%\" height=\"300\"></iframe>"
								+"<br>"
								+"<br>";

							}


							indexString = indexString
							+"<br>"
							+"</body>"
							+"</html>"
							;

							try
							{
								FileUtils.writeStringToFile(new File("/var/www/html/index.html"),indexString,false);
							}
							catch(IOException e)
							{
								e.printStackTrace();
							}

						}



						try
						{
							Thread.sleep(5000);
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
	public IndexServerMain()
	{//===============================================================================================

		//get my IP


		if(BobNet.debugMode)
		{
			myIPAddressString = "127.0.0.1";

			try
			{
				myIPAddress = InetAddress.getByName(myIPAddressString);
			}
			catch(UnknownHostException e)
			{
				e.printStackTrace();
			}

		}
		else
		{
			try
			{
				HttpURLConnection con = (HttpURLConnection) new URL("http://checkip.amazonaws.com").openConnection();
				//con.setRequestMethod("GET");
				//con.getOutputStream().write("LOGIN".getBytes("UTF-8"));
				BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));


				myIPAddressString = in.readLine();
				myIPAddress = InetAddress.getByName(myIPAddressString);

				in.close();
				con.disconnect();


			}
			catch(MalformedURLException e)
			{
				e.printStackTrace();
			}
			catch(IOException e)
			{
				e.printStackTrace();
			}
		}


		indexServerTCP = new IndexServerTCP();

	}



}
