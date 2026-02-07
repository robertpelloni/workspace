package com.bobsgame;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.nio.charset.StandardCharsets;

import com.bobsgame.server.GameServerTCP;
import com.bobsgame.server.IndexClientTCP;
import org.apache.commons.io.FileUtils;


import org.slf4j.LoggerFactory;



//import com.esotericsoftware.kryonet.Connection;
//import com.esotericsoftware.kryonet.Listener;
//import com.esotericsoftware.kryonet.Server;


import ch.qos.logback.classic.Logger;
import ch.qos.logback.classic.LoggerContext;
import ch.qos.logback.classic.encoder.PatternLayoutEncoder;
import ch.qos.logback.classic.spi.ILoggingEvent;
import ch.qos.logback.core.ConsoleAppender;

import com.bobsgame.net.*;


import com.bobsgame.server.assets.AssetDataIndex;

//import com.esotericsoftware.minlog.Log;

import org.apache.log4j.BasicConfigurator;




//===============================================================================================
public class ServerMain
{//===============================================================================================










	public static Logger log = (Logger) LoggerFactory.getLogger(ServerMain.class);

	static public IndexClientTCP indexClientTCP;
	public static String INDEXServerAddress = BobNet.releaseINDEXServerAddress;


	public static ServerMain serverMain = null;
	static public GameServerTCP gameServerTCP;



	public static String myIPAddressString = "";




	//===============================================================================================
	public static void main(String[] args)
	{//===============================================================================================


		File f = new File("/localServer");
		if(f.exists())
		{


		}

		BasicConfigurator.configure();

		Logger rootLogger = (Logger) LoggerFactory.getLogger(Logger.ROOT_LOGGER_NAME);
		LoggerContext loggerContext = rootLogger.getLoggerContext();
		// we are not interested in auto-configuration
		loggerContext.reset();

		PatternLayoutEncoder encoder = new PatternLayoutEncoder();
		encoder.setContext(loggerContext);
		encoder.setPattern("%date{HH:mm:ss} %-50(%highlight(%-5level| %msg   )) \\(%F:%L\\) %boldMagenta(%c{2}.%M\\(\\)) %boldGreen([%thread]) \n");
		encoder.start();

		ConsoleAppender<ILoggingEvent> appender = new ConsoleAppender<ILoggingEvent>();
		appender.setWithJansi(true);
		appender.setContext(loggerContext);
		appender.setEncoder(encoder);
		appender.start();

		rootLogger.addAppender(appender);






//		HTMLLayout htmlLayout = new HTMLLayout();
//		htmlLayout.setPattern("%date{yyyy-MM-dd HH:mm:ss}%relative%thread%F%L%c{2}%M%level%msg");
//		htmlLayout.setContext(loggerContext);
//		htmlLayout.start();
//
//		LayoutWrappingEncoder<ILoggingEvent> layoutEncoder = new LayoutWrappingEncoder<ILoggingEvent>();
//		layoutEncoder.setLayout(htmlLayout);
//		layoutEncoder.setContext(loggerContext);
//		layoutEncoder.setImmediateFlush(true);
//		layoutEncoder.start();
//
//
//		ThresholdFilter filter = new ThresholdFilter();
//		filter.setLevel("WARN");
//		filter.setContext(loggerContext);
//
//
//		FileAppender<ILoggingEvent> fileAppender = new FileAppender<ILoggingEvent>();
//		fileAppender.setContext(loggerContext);
//		fileAppender.setEncoder(layoutEncoder);
//		fileAppender.addFilter(filter);
//		fileAppender.setAppend(true);
//		fileAppender.setFile("/var/www/html/log.html");
//		fileAppender.start();
//
//		rootLogger.addAppender(fileAppender);



		//LoggerContext lc = (LoggerContext) LoggerFactory.getILoggerFactory();
		//StatusPrinter.print(lc);


		//rootLogger.debug("debug test");
		//rootLogger.info("info test");
		//rootLogger.warn("warn test");
		//rootLogger.error("error test");


		//log.setLevel(Level.ALL);

//
//
//		log.debug("debug test");
//		log.info("info test");
//		log.warn("warn test");
//		log.error("error test");
//





//		//lzo and base64 string
//
//		String lzoString = null;
//
//		ByteArrayOutputStream out=new ByteArrayOutputStream();
//		LzoAlgorithm algorithm = LzoAlgorithm.LZO1X;
//		LzoCompressor compressor = LzoLibrary.getInstance().newCompressor(algorithm, null);
//		LzoOutputStream lzoStream = new LzoOutputStream(out, compressor, 256);
//
//
//		//String s = "a bunch of text a bunch of text a bunch of text a bunch of text a bunch of text a bunch of text a bunch of text a bunch of text a bunch of text a bunch of text a bunch of text a bunch of text ";
//		String s = "Server_IP_Address_Response:34.201.250.43:END:";
//		try
//		{
//			lzoStream.write(s.getBytes());
//			lzoStream.close();
//			lzoString=out.toString("ISO-8859-1");
//		}
//		catch(IOException e)
//		{
//			e.printStackTrace();
//		}
//
//		String base64 = Utils.encodeStringToBase64(lzoString);
//		log.info(base64);
//
//System.exit(0);
//






//
//		String s = "Server_IP_Address_Response:34.201.250.43"+BobNet.endline;
//
//		s = "a really long test string with repeating words to test. a really long test string with repeating words to test. a really long test string with repeating words to test.";
//
//		//log.info("SEND CLIENT: "+s.substring(0,Math.min(100,s.length()-2))+"...");
//
//		//lzo and base64 string
//
//		String lzoString = null;
//
//		ByteArrayOutputStream out=new ByteArrayOutputStream();
//		LzoAlgorithm algorithm = LzoAlgorithm.LZO1X;
//		LzoCompressor compressor = LzoLibrary.getInstance().newCompressor(algorithm, LzoConstraint.COMPRESSION);
//		LzoOutputStream lzoStream = new LzoOutputStream(out, compressor, 256);
//
//		try
//		{
//
//
//			lzoStream.write(s.getBytes());
//			lzoStream.close();
//			lzoString=out.toString("ISO-8859-1");
//
//			log.info((out.toString("ISO-8859-1")));
//			log.info((out.toString("UTF-8")));
//			log.info((out.toString("ASCII")));
//
//			log.info(Utils.encodeStringToBase64(out.toString("ISO-8859-1")));
//			log.info(Utils.encodeStringToBase64(out.toString("UTF-8")));
//			log.info(Utils.encodeStringToBase64(out.toString("ASCII")));
//
//		}
//		catch(IOException e)
//		{
//			e.printStackTrace();
//		}
//
//		String base64 = Utils.encodeStringToBase64(lzoString);
//		s = new String(base64+BobNet.endline);
//
//
//
//		System.out.println(s);
//		log.info(s);
//
////		gameServerTCP = new GameServerTCP();
////
////		gameServerTCP.write(null,"Server_IP_Address_Response:34.201.250.43"+BobNet.endline);
//
//
//		System.exit(0);











		//String s = "Server_IP_Address_Response:34.201.250.43"+BobNet.endline;

		//s = "a really long test string with repeating words to test. a really long test string with repeating words to test. a really long test string with repeating words to test.";
//
//		ByteArrayOutputStream out=new ByteArrayOutputStream();
//		DeflateCompressorOutputStream gzip;
//
//		String zip = null;
//
//
//		try
//		{
//			gzip=new DeflateCompressorOutputStream(out);
//			gzip.write(s.getBytes());
//			gzip.close();
//
//			zip=out.toString("ISO-8859-1");
//
//			log.info(Utils.encodeStringToBase64(out.toString("ISO-8859-1")));
//			log.info(Utils.encodeStringToBase64(out.toString("UTF-8")));
//			log.info(Utils.encodeStringToBase64(out.toString("ASCII")));
//		}
//		catch(Exception e)
//		{
//			e.printStackTrace();
//		}
//
//
//
//		//String zip = Utils.zipString(s);
//		String base64 = Utils.encodeStringToBase64(zip);
//		s = base64+BobNet.endline;
//
//		log.info(s);
//
//		System.exit(0);
//






//		try
//		{
//
//			LZ4Factory factory = LZ4Factory.fastestInstance();
//
//			byte[] data;
//			data=s.getBytes("UTF-8");
//
//
//			final int decompressedLength = data.length;
//
//			// compress data
//			LZ4Compressor compressor = factory.fastCompressor();
//			int maxCompressedLength = compressor.maxCompressedLength(decompressedLength);
//			byte[] compressedBuffer = new byte[maxCompressedLength];
//			int compressedLength = compressor.compress(data, 0, decompressedLength, compressedBuffer, 0, maxCompressedLength);
//
//			byte[] compressedBytes = new byte[compressedLength];
//
//			for(int i=0;i<compressedLength;i++)
//			{
//				compressedBytes[i] = compressedBuffer[i];
//			}
//
//
//
//			String base64 = Base64.encodeBase64String(compressedBytes);
//			s = new String(base64+BobNet.endline);
//
//		}
//		catch(UnsupportedEncodingException e)
//		{
//			e.printStackTrace();
//		}
//
//
//		log.info(s);
//
//		System.exit(0);




//		String s = "Server_IP_Address_Response:34.201.250.43"+BobNet.endline;
//
//		ByteArrayOutputStream out=new ByteArrayOutputStream();
//		DeflaterOutputStream gzip;
//
//		String zip = null;
//
//
//		try
//		{
//			gzip=new DeflaterOutputStream(out);
//			gzip.write(s.getBytes());
//			gzip.close();
//
//			zip=out.toString("ISO-8859-1");
//
//			log.info(Utils.encodeStringToBase64(out.toString("ISO-8859-1")));
//			log.info(Utils.encodeStringToBase64(out.toString("UTF-8")));
//			log.info(Utils.encodeStringToBase64(out.toString("ASCII")));
//		}
//		catch(Exception e)
//		{
//			e.printStackTrace();
//		}
//
//
//
//		//String zip = Utils.zipString(s);
//		String base64 = Utils.encodeStringToBase64(zip);
//		s = base64+BobNet.endline;
//
//		log.info(s);
//
//		System.exit(0);


















		if(BobNet.debugMode==true)
		{

			PrivateCredentials.AMAZON_RDS_URL = "jdbc:mysql://localhost/bobsgame";
			PrivateCredentials.AMAZON_RDS_USERNAME = "root";
			PrivateCredentials.AMAZON_RDS_PASSWORD = "";

			PrivateCredentials.DREAMHOST_SQL_URL = "jdbc:mysql://localhost/bobsgame";
			PrivateCredentials.DREAMHOST_SQL_USERNAME = "root";
			PrivateCredentials.DREAMHOST_SQL_PASSWORD = "";


			INDEXServerAddress = BobNet.debugINDEXServerAddress;


		}
		else
		{

			//logback or
			//java.util.logging
			//log.setLevel(Level.WARN);

		}




		serverMain = new ServerMain();
		serverMain.run();








	}


	static public boolean exit = false;

	public long ticksSincePublishedLog = 0;

	static public long startTime = System.currentTimeMillis();
	static public long lastTime = System.currentTimeMillis();


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



						//DONE: output html status log every 5 seconds for index server to scrape




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

							String clientsConnectedText = "Clients Connected: "+gameServerTCP.clientsByChannel.size();


							String statsString =
							"<html>"
							+"<head>"
							+"<title>SERVER STATS</title>"
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
							+"<br>"+clientsConnectedText
							+"<br>"
							+"</body>"
							+"</html>"
							;

							//DONE: write system stats out to /var/www/stats.htm
							try
							{
								FileUtils.writeStringToFile(new File("/var/www/html/stats.html"),statsString, StandardCharsets.UTF_8, false);
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
	public ServerMain()
	{//===============================================================================================

		//super("SERVER");//UbgO ULTRA-SERVER"); yay



		new AssetDataIndex();



		//get my IP

		if(BobNet.debugMode==true)
		{
			myIPAddressString = "localhost";
		}
		else
		{
			try
			{
				HttpURLConnection con = (HttpURLConnection) java.net.URI.create("http://checkip.amazonaws.com").toURL().openConnection();
				//con.setRequestMethod("GET");
				//con.getOutputStream().write("LOGIN".getBytes("UTF-8"));
				BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));


				myIPAddressString = in.readLine();

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



		//TODO: server->index connection and server->rds connection should use AWS internal IP address if possible
		//http://169.254.169.254
		//http://instance-data

		//local ip
		//curl http://169.254.169.254/latest/meta-data/local-ipv4
		//curl http://instance-data/latest/meta-data/local-ipv4

		//public ip
		//curl http://169.254.169.254/latest/meta-data/public-ipv4
		//curl http://instance-data/latest/meta-data/public-ipv4




		gameServerTCP = new GameServerTCP();
		//log.debug("got here");
		//gameServerTCP.sendAccountCreationEmail("", "test");

		indexClientTCP = new IndexClientTCP();



		//gameServerTCP.testJSON();

		//System.exit(0);

		//TODO: load log file

	}






/*
	//===============================================================================================
	@Override
	public void actionPerformed(ActionEvent e)
	{//===============================================================================================


	}

	//===============================================================================================
	@Override
	public void windowOpened(WindowEvent e)
	{//===============================================================================================


	}

	//===============================================================================================
	@Override
	public void windowClosing(WindowEvent e)
	{//===============================================================================================

		exit=true;

		serverTCP.cleanup();
		serverUDP.cleanup();

		log.info("Shutdown.");

		//TODO: save log file

		System.exit(0);
	}

	//===============================================================================================
	@Override
	public void windowClosed(WindowEvent e)
	{//===============================================================================================


	}

	//===============================================================================================
	@Override
	public void windowIconified(WindowEvent e)
	{//===============================================================================================


	}

	//===============================================================================================
	@Override
	public void windowDeiconified(WindowEvent e)
	{//===============================================================================================


	}

	//===============================================================================================
	@Override
	public void windowActivated(WindowEvent e)
	{//===============================================================================================


	}

	//===============================================================================================
	@Override
	public void windowDeactivated(WindowEvent e)
	{//===============================================================================================


	}

	//===============================================================================================
	@Override
	public void mouseWheelMoved(MouseWheelEvent e)
	{//===============================================================================================


	}

	//===============================================================================================
	@Override
	public void keyTyped(KeyEvent e)
	{//===============================================================================================


	}

	//===============================================================================================
	@Override
	public void keyPressed(KeyEvent e)
	{//===============================================================================================


	}

	//===============================================================================================
	@Override
	public void keyReleased(KeyEvent e)
	{//===============================================================================================


	}
*/



}
