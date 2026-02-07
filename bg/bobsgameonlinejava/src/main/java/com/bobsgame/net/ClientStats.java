package com.bobsgame.net;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

public class ClientStats
{

	public static Logger log = (Logger) LoggerFactory.getLogger(ClientStats.class);

	public String sessionToken = "";




	//InetAddress addr = InetAddress.getByName(refAddr);
	//String name = addr.getHostName();


	//TODO:
	public int downloadRate = 0;
	public int uploadRate = 0;
	public int ping = 0;






	public String internetProviderString = "";

	//TODO: resolve this somehow by the IP somewhere, probably from the client is better.
	//s.internetProviderString =





	public String browserUserAgentString = "";
	public String browserAppNameVersionString = "";
	public String browserReferrerString = "";

	public String getEnvProcessorIdentifier = "";
	public String getEnvProcessorArchitecture = "";
	public String getEnvNumberOfProcessors = "";



	public float timeZoneGMTOffset = 0.0f;


	//TODO: SIGAR stuff
	//cpu clock speed
	//actual GPU hardware name, i.e. radeon hd 4700, 512 mb




	//public String operatingSystemString = "";
	//public String javaInfoString = "";
	//public String cpuString = "";
	//public String gpuString = "";
	//public String memoryString = "";
	//public String joysticksString = "";
	//public String soundDeviceString = "";
	//public String webcamString = "";
	//public String diskSpaceString = "";
	//public String homeDirString = "";
	//public String cacheSizeString = "";




	//done

	public String jreVersion = "";
	public String jreVendor = "";
	//public String jreVendorURL = "";
	public String jreHomeDir = "";
	//public String jvmSpecVersion = "";
	//public String jvmSpecVendor	 = "";
	//public String jvmSpecName = "";
	public String jvmVersion = "";
	//public String jvmVendor	 = "";
	public String jvmName = "";
	//public String jreSpecVersion = "";
	//public String jreSpecVendor	 = "";
	//public String jreSpecName = "";
	public String javaClassVersion = "";
	public String javaClassPath	 = "";
	public String javaLibraryPath = "";
	public String javaTempDir = "";
	//public String javaJITCompiler = "";
	//public String javaExtensionPath	 = "";
	public String osName = "";
	public String osArch = "";
	public String osVersion	 = "";
	public String osUserAccountName = "";
	public String osHomeDir	 = "";
	public String workingDir = "";

	public int displayWidth = -1;
	public int displayHeight = -1;
	public int displayBPP = -1;
	public int displayFreq = -1;
	public boolean shaderCompiled = false;
	public boolean canUseFBO = false;
	public boolean usingVSync = false;
	public String displayAdapter = "";
	public String displayDriver = "";
	public String lwjglVersion = "";
	public boolean lwjglIs64Bit = false;
	public String lwjglPlatformName = "";
	public int numCPUs = -1;
	public long totalMemory = -1;
	public long maxMemory = -1;
	public int numControllersFound = -1;
	public String controllersNames = "";

	public String glVendor = "";
	public String glVersion = "";
	public String glRenderer = "";
	public String shaderVersion = "";
	public String glExtensions = "";

	//=========================================================================================================================
	public String split(String in)
	{//=========================================================================================================================

//		int l = 300;
//
//		String s = "";
//		for(int i=0; i < Math.floor(in.length()/l); i++)
//		{
//			s = s + in.substring(i*l,i*l+l) + " \n ";
//		}
//		s = s + in.substring((int)Math.floor(in.length()/l)*l);
//		return s;
		if(in==null)return "null";

		if(in.length()>100)return in.substring(0,100)+"...";

		return in;




	}

	//=========================================================================================================================
	public String printString()
	{//=========================================================================================================================
		String s = ""+


				"browserUserAgentString: "+split(browserUserAgentString)+"\n"+
				"browserAppNameVersionString: "+split(browserAppNameVersionString)+"\n"+
				"browserReferrerString: "+split(browserReferrerString)+"\n"+

				"getEnvProcessorIdentifier: "+split(getEnvProcessorIdentifier)+"\n"+
				"getEnvProcessorArchitecture: "+split(getEnvProcessorArchitecture)+"\n"+
				"getEnvNumberOfProcessors: "+split(getEnvNumberOfProcessors)+"\n"+

				"internetProviderString: "+split(internetProviderString)+"\n"+

				"timeZoneGMTOffset: "+timeZoneGMTOffset+"\n"+

				"jreVersion: "+split(jreVersion)+"\n"+
				"jreVendor: "+split(jreVendor)+"\n"+
				//"jreVendorURL: "+split(jreVendorURL)+"\n"+

				"jreHomeDir: "+split(jreHomeDir)+"\n"+
				//"jvmSpecVersion: "+split(jvmSpecVersion)+"\n"+
				//"jvmSpecVendor: "+split(jvmSpecVendor	)+"\n"+
				//"jvmSpecName: "+split(jvmSpecName)+"\n"+
				"jvmVersion: "+split(jvmVersion)+"\n"+

				//"jvmVendor: "+split(jvmVendor	)+"\n"+
				"jvmName: "+split(jvmName)+"\n"+
				//"jreSpecVersion: "+split(jreSpecVersion)+"\n"+
				//"jreSpecVendor: "+split(jreSpecVendor	)+"\n"+
				//"jreSpecName: "+split(jreSpecName)+"\n"+

				"javaClassVersion: "+split(javaClassVersion)+"\n"+
				"javaClassPath: "+split(javaClassPath)+"\n"+
				"javaLibraryPath: "+split(javaLibraryPath)+"\n"+
				"javaTempDir: "+split(javaTempDir)+"\n"+
				//"javaJITCompiler: "+split(javaJITCompiler)+"\n"+

				//"javaExtensionPath: "+split(javaExtensionPath)+"\n"+
				"osName: "+split(osName)+"\n"+
				"osArch: "+split(osArch)+"\n"+
				"osVersion: "+split(osVersion)+"\n"+
				"osUserAccountName: "+split(osUserAccountName)+"\n"+

				"osHomeDir: "+split(osHomeDir)+"\n"+
				"workingDir: "+split(workingDir)+"\n"+

				"displayWidth: "+displayWidth+"\n"+
				"displayHeight: "+displayHeight+"\n"+
				"displayBPP: "+displayBPP+"\n"+
				"displayFreq: "+displayFreq+"\n"+
				"shaderCompiled: "+shaderCompiled+"\n"+
				"canUseFBO: "+canUseFBO+"\n"+
				"usingVSync: "+usingVSync+"\n"+
				"displayAdapter: "+split(displayAdapter)+"\n"+
				"displayDriver: "+split(displayDriver)+"\n"+
				"lwjglVersion: "+split(lwjglVersion)+"\n"+
				"lwjglIs64Bit: "+lwjglIs64Bit+"\n"+
				"lwjglPlatformName: "+split(lwjglPlatformName)+"\n"+
				"numCPUs: "+numCPUs+"\n"+
				"totalMemory: "+totalMemory+"\n"+
				"maxMemory: "+maxMemory+"\n"+
				"numControllersFound: "+numControllersFound+"\n"+
				"controllersNames: "+split(controllersNames)+"\n"+

				"glVendor: "+split(glVendor)+"\n"+
				"glVersion: "+split(glVersion)+"\n"+
				"glRenderer: "+split(glRenderer)+"\n"+
				"shaderVersion: "+split(shaderVersion)+"\n"+
				"glExtensions: "+split(glExtensions);


		return s;


	}


	//=========================================================================================================================
	public String encode()
	{//=========================================================================================================================

		String s = ""+
				"`"+timeZoneGMTOffset+"`"+","+

				"`"+browserUserAgentString+"`"+","+
				"`"+browserAppNameVersionString+"`"+","+
				"`"+browserReferrerString+"`"+","+

				"`"+getEnvProcessorIdentifier+"`"+","+
				"`"+getEnvProcessorArchitecture+"`"+","+
				"`"+getEnvNumberOfProcessors+"`"+","+

				"`"+internetProviderString+"`"+","+





				"`"+jreVersion+"`"+","+
				"`"+jreVendor+"`"+","+
				//"`"+jreVendorURL+"`"+","+

				"`"+jreHomeDir+"`"+","+
				//"`"+jvmSpecVersion+"`"+","+
				//"`"+jvmSpecVendor	+"`"+","+
				//"`"+jvmSpecName+"`"+","+
				"`"+jvmVersion+"`"+","+

				//"`"+jvmVendor	+"`"+","+
				"`"+jvmName+"`"+","+
				//"`"+jreSpecVersion+"`"+","+
				//"`"+jreSpecVendor	+"`"+","+
				//"`"+jreSpecName+"`"+","+

				"`"+javaClassVersion+"`"+","+
				"`"+javaClassPath+"`"+","+
				"`"+javaLibraryPath+"`"+","+
				"`"+javaTempDir+"`"+","+
				//"`"+javaJITCompiler+"`"+","+

				//"`"+javaExtensionPath+"`"+","+
				"`"+osName+"`"+","+
				"`"+osArch+"`"+","+
				"`"+osVersion+"`"+","+
				"`"+osUserAccountName+"`"+","+

				"`"+osHomeDir+"`"+","+
				"`"+workingDir+"`"+","+

				"`"+displayWidth+"`"+","+
				"`"+displayHeight+"`"+","+
				"`"+displayBPP+"`"+","+
				"`"+displayFreq+"`"+","+
				"`"+shaderCompiled+"`"+","+
				"`"+canUseFBO+"`"+","+
				"`"+usingVSync+"`"+","+
				"`"+displayAdapter+"`"+","+
				"`"+displayDriver+"`"+","+
				"`"+lwjglVersion+"`"+","+
				"`"+lwjglIs64Bit+"`"+","+
				"`"+lwjglPlatformName+"`"+","+
				"`"+numCPUs+"`"+","+
				"`"+totalMemory+"`"+","+
				"`"+maxMemory+"`"+","+
				"`"+numControllersFound+"`"+","+
				"`"+controllersNames+"`"+","+

				"`"+glVendor+"`"+","+
				"`"+glVersion+"`"+","+
				"`"+glRenderer+"`"+","+
				"`"+shaderVersion+"`"+","+
				"`"+glExtensions+"`";

		return s;

	}

	//=========================================================================================================================
	public void decode(String s)
	{//=========================================================================================================================

//		"`"+timeZoneGMTOffset+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{timeZoneGMTOffset = Float.parseFloat(t);}catch(NumberFormatException ex){}
			s = s.substring(s.indexOf('`')+1);
		}

//		"`"+browserUserAgentString+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)browserUserAgentString = t;
			s = s.substring(s.indexOf('`')+1);
		}

//		"`"+browserAppNameVersionString+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)browserAppNameVersionString = t;
			s = s.substring(s.indexOf('`')+1);
		}

//		"`"+browserReferrerString+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)browserReferrerString = t;
			s = s.substring(s.indexOf('`')+1);
		}




//		"`"+getEnvProcessorIdentifier+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)getEnvProcessorIdentifier = t;
			s = s.substring(s.indexOf('`')+1);
		}

//		"`"+getEnvProcessorArchitecture+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)getEnvProcessorArchitecture = t;
			s = s.substring(s.indexOf('`')+1);
		}

//		"`"+getEnvNumberOfProcessors+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)getEnvNumberOfProcessors = t;
			s = s.substring(s.indexOf('`')+1);
		}


//		"`"+internetProviderString+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)internetProviderString = t;
			s = s.substring(s.indexOf('`')+1);
		}



		//string----------------------

//		"`"+jreVersion+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)jreVersion = t;
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+jreVendor+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)jreVendor = t;
			s = s.substring(s.indexOf('`')+1);
		}


//		"`"+jreHomeDir+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)jreHomeDir = t;
			s = s.substring(s.indexOf('`')+1);
		}


//		"`"+jvmVersion+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)jvmVersion = t;
			s = s.substring(s.indexOf('`')+1);
		}



//		"`"+jvmName+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)jvmName = t;
			s = s.substring(s.indexOf('`')+1);
		}



//		"`"+javaClassVersion+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)javaClassVersion = t;
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+javaClassPath+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)javaClassPath = t;
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+javaLibraryPath+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)javaLibraryPath = t;
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+javaTempDir+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)javaTempDir = t;
			s = s.substring(s.indexOf('`')+1);
		}


//		"`"+osName+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)osName = t;
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+osArch+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)osArch = t;
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+osVersion+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)osVersion = t;
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+osUserAccountName+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)osUserAccountName = t;
			s = s.substring(s.indexOf('`')+1);
		}


//		"`"+osHomeDir+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)osHomeDir = t;
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+workingDir+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)workingDir = t;
			s = s.substring(s.indexOf('`')+1);
		}





		//int----------------------

//		"`"+displayWidth+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{displayWidth = Integer.parseInt(t);}catch(NumberFormatException ex){}
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+displayHeight+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{displayHeight = Integer.parseInt(t);}catch(NumberFormatException ex){}
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+displayBPP+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{displayBPP = Integer.parseInt(t);}catch(NumberFormatException ex){}
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+displayFreq+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{displayFreq = Integer.parseInt(t);}catch(NumberFormatException ex){}
			s = s.substring(s.indexOf('`')+1);
		}

		//boolean----------------------

//		"`"+shaderCompiled+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{shaderCompiled = Boolean.parseBoolean(t);}catch(NumberFormatException ex){}
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+canUseFBO+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{canUseFBO = Boolean.parseBoolean(t);}catch(NumberFormatException ex){}
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+usingVSync+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{usingVSync = Boolean.parseBoolean(t);}catch(NumberFormatException ex){}
			s = s.substring(s.indexOf('`')+1);
		}


		//string----------------------

//		"`"+displayAdapter+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)displayAdapter = t;
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+displayDriver+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)displayDriver = t;
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+lwjglVersion+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)lwjglVersion = t;
			s = s.substring(s.indexOf('`')+1);
		}



		//boolean ----------------------

//		"`"+lwjglIs64Bit+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{lwjglIs64Bit = Boolean.parseBoolean(t);}catch(NumberFormatException ex){}
			s = s.substring(s.indexOf('`')+1);
		}

		//string----------------------

//		"`"+lwjglPlatformName+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)lwjglPlatformName = t;
			s = s.substring(s.indexOf('`')+1);
		}

		//int----------------------

//		"`"+numCPUs+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{numCPUs = Integer.parseInt(t);}catch(NumberFormatException ex){}
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+totalMemory+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{totalMemory = Integer.parseInt(t);}catch(NumberFormatException ex){}
			s = s.substring(s.indexOf('`')+1);
		}
//		"`"+maxMemory+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{maxMemory = Integer.parseInt(t);}catch(NumberFormatException ex){}
			s = s.substring(s.indexOf('`')+1);
		}

//		"`"+numControllersFound+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{numControllersFound = Integer.parseInt(t);}catch(NumberFormatException ex){}
			s = s.substring(s.indexOf('`')+1);
		}




		//string----------------------

//		"`"+controllersNames+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)controllersNames = t;
			s = s.substring(s.indexOf('`')+1);
		}






//		"`"+glVendor+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)glVendor = t;
			s = s.substring(s.indexOf('`')+1);
		}

//		"`"+glVersion+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)glVersion = t;
			s = s.substring(s.indexOf('`')+1);
		}

//		"`"+glRenderer+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)glRenderer = t;
			s = s.substring(s.indexOf('`')+1);
		}

//		"`"+shaderVersion+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)shaderVersion = t;
			s = s.substring(s.indexOf('`')+1);
		}

//		"`"+glExtensions+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)glExtensions = t;
			s = s.substring(s.indexOf('`')+1);
		}

	}


	//=========================================================================================================================
	public PreparedStatement getInsertStatement(Connection databaseConnection, String emailAddress, BobsGameClient cc, String ipAddress)
	{//=========================================================================================================================


		//keep the boolean strings blank if no information is provided
		String shaderCompiledString = "";
		String canUseFBOString = "";
		String usingVSyncString = "";
		String lwjglIs64BitString = "";




//
//		InetAddress addr = null;
//		try
//		{
//			addr = InetAddress.getByName(cc.channel.getRemoteAddress().toString());
//		}
//		catch(UnknownHostException e)
//		{
//			e.printStackTrace();
//		}
//
//		if(addr!=null)
//		internetProviderString = addr.getHostName();





		if(jreVersion.length()>0)
		{
			shaderCompiledString = ""+shaderCompiled;
			canUseFBOString = ""+canUseFBO;
			usingVSyncString = ""+usingVSync;
			lwjglIs64BitString = ""+lwjglIs64Bit;
		}


		PreparedStatement ps = null;

		try
		{
			ps = databaseConnection.prepareStatement(
			"INSERT INTO connections ( "+

			"browserUserAgentString , " +
			"browserAppNameVersionString , " +
			"browserReferrerString , " +

			"getEnvProcessorIdentifier , " +
			"getEnvProcessorArchitecture , " +
			"getEnvNumberOfProcessors , " +

			"internetProviderString , " +
			"emailAddress , " +
			"userID , " +
			"sessionToken , " +
			"encryptionKey , " +
			"startTime , " +
			"ipAddress , " +

			"jreVersion , " +
			"jreVendor , " +
			"jreHomeDir , " +
			"jvmVersion , " +
			"jvmName , " +
			"javaClassVersion , " +
			"javaClassPath , " +
			"javaLibraryPath , " +
			"javaTempDir , " +

			"osName , " +
			"osArch , " +
			"osVersion , " +
			"osUserAccountName , " +
			"osHomeDir , " +
			"workingDir , " +

			"displayWidth , " +
			"displayHeight , " +
			"displayBPP , " +
			"displayFreq , " +

			"shaderCompiled , " +
			"canUseFBO , " +
			"usingVSync , " +
			"displayAdapter , " +
			"displayDriver , " +

			"lwjglVersion , " +
			"lwjglIs64Bit , " +
			"lwjglPlatformName , " +
			"numCPUs , " +
			"totalMemory , " +
			"maxMemory , " +

			"numControllersFound , " +
			"controllersNames , " +
			"timeZoneGMTOffset , " +
			"glVendor , " +
			"glVersion , " +
			"glRenderer , " +
			"shaderVersion , " +
			"glExtensions" +
			" ) VALUES ( " +
			"?, ?, ?, ?, ?, " +
			"?, ?, ?, ?, ?, " +
			"?, ?, ?, ?, ?, " +
			"?, ?, ?, ?, ?, " +
			"?, ?, ?, ?, ?, " +
			"?, ?, ?, ?, ?, " +
			"?, ?, ?, ?, ?, " +
			"?, ?, ?, ?, ?, " +
			"?, ?, ?, ?, ?, " +
			"?, ?, ?, ?, ?, " +
			"?" +
			")");

		int c = 1;

		ps.setString	(c++, browserUserAgentString);
		ps.setString	(c++, browserAppNameVersionString);
		ps.setString	(c++, browserReferrerString);

		ps.setString	(c++, getEnvProcessorIdentifier);
		ps.setString	(c++, getEnvProcessorArchitecture);
		ps.setString	(c++, getEnvNumberOfProcessors);

		ps.setString	(c++, internetProviderString);
		ps.setString	(c++, emailAddress);
		ps.setLong		(c++, cc.userID);
		ps.setString	(c++, sessionToken);
		ps.setString	(c++, cc.encryptionKey);
		ps.setLong		(c++, cc.startTime);
		ps.setString	(c++, ipAddress);

		ps.setString	(c++, jreVersion);
		ps.setString	(c++, jreVendor);
		ps.setString	(c++, jreHomeDir);
		ps.setString	(c++, jvmVersion);
		ps.setString	(c++, jvmName);
		ps.setString	(c++, javaClassVersion);
		ps.setString	(c++, javaClassPath);
		ps.setString	(c++, javaLibraryPath);
		ps.setString	(c++, javaTempDir);

		ps.setString	(c++, osName);
		ps.setString	(c++, osArch);
		ps.setString	(c++, osVersion);
		ps.setString	(c++, osUserAccountName);
		ps.setString	(c++, osHomeDir);
		ps.setString	(c++, workingDir);

		ps.setInt		(c++, displayWidth);
		ps.setInt		(c++, displayHeight);
		ps.setInt		(c++, displayBPP);
		ps.setInt		(c++, displayFreq);

		ps.setString	(c++, shaderCompiledString);
		ps.setString	(c++, canUseFBOString);
		ps.setString	(c++, usingVSyncString);
		ps.setString	(c++, displayAdapter);
		ps.setString	(c++, displayDriver);

		ps.setString	(c++, lwjglVersion);
		ps.setString	(c++, lwjglIs64BitString);
		ps.setString	(c++, lwjglPlatformName);
		ps.setInt		(c++, numCPUs);
		ps.setLong		(c++, totalMemory);
		ps.setLong		(c++, maxMemory);

		ps.setInt		(c++, numControllersFound);
		ps.setString	(c++, controllersNames);
		ps.setFloat	(c++, timeZoneGMTOffset);

		ps.setString	(c++, glVendor);
		ps.setString	(c++, glVersion);
		ps.setString	(c++, glRenderer);
		ps.setString	(c++, shaderVersion);
		ps.setString	(c++, glExtensions);

		}
		catch (Exception ex){System.err.println("DB ERROR: "+ex.getMessage());}

		//statement = statement.replace("\\", "\\\\");
		//Using PreparedStatement makes this unnecessary, dont need to escape strings
		//NEVERMIND  clean this better, clean all user input on both client and server side

		//System.out.println(statement);

		return ps;
	}

	public void log()
	{

		log.info("browserUserAgentString: "+(browserUserAgentString));
		log.info("browserAppNameVersionString: "+(browserAppNameVersionString));
		log.info("browserReferrerString: "+(browserReferrerString));

		log.info("getEnvProcessorIdentifier: "+(getEnvProcessorIdentifier));
		log.info("getEnvProcessorArchitecture: "+(getEnvProcessorArchitecture));
		log.info("getEnvNumberOfProcessors: "+(getEnvNumberOfProcessors));

		log.info("internetProviderString: "+(internetProviderString));

		log.info("timeZoneGMTOffset: "+timeZoneGMTOffset);

		log.info("jreVersion: "+(jreVersion));
		log.info("jreVendor: "+(jreVendor));
		//"jreVendorURL: "+split(jreVendorURL));

		log.info("jreHomeDir: "+(jreHomeDir));
		//"jvmSpecVersion: "+split(jvmSpecVersion));
		//"jvmSpecVendor: "+split(jvmSpecVendor	));
		//"jvmSpecName: "+split(jvmSpecName));
		log.info("jvmVersion: "+(jvmVersion));

		//"jvmVendor: "+split(jvmVendor	));
		log.info("jvmName: "+(jvmName));
		//"jreSpecVersion: "+split(jreSpecVersion));
		//"jreSpecVendor: "+split(jreSpecVendor	));
		//"jreSpecName: "+split(jreSpecName));

		log.info("javaClassVersion: "+(javaClassVersion));
		log.info("javaClassPath: "+(javaClassPath));
		log.info("javaLibraryPath: "+(javaLibraryPath));
		log.info("javaTempDir: "+(javaTempDir));
		//"javaJITCompiler: "+split(javaJITCompiler));

		//"javaExtensionPath: "+split(javaExtensionPath));
		log.info("osName: "+(osName));
		log.info("osArch: "+(osArch));
		log.info("osVersion: "+(osVersion));
		log.info("osUserAccountName: "+(osUserAccountName));

		log.info("osHomeDir: "+(osHomeDir));
		log.info("workingDir: "+(workingDir));

		log.info("displayWidth: "+displayWidth);
		log.info("displayHeight: "+displayHeight);
		log.info("displayBPP: "+displayBPP);
		log.info("displayFreq: "+displayFreq);
		log.info("shaderCompiled: "+shaderCompiled);
		log.info("canUseFBO: "+canUseFBO);
		log.info("usingVSync: "+usingVSync);
		log.info("displayAdapter: "+(displayAdapter));
		log.info("displayDriver: "+(displayDriver));
		log.info("lwjglVersion: "+(lwjglVersion));
		log.info("lwjglIs64Bit: "+lwjglIs64Bit);
		log.info("lwjglPlatformName: "+(lwjglPlatformName));
		log.info("numCPUs: "+numCPUs);
		log.info("totalMemory: "+totalMemory);
		log.info("maxMemory: "+maxMemory);
		log.info("numControllersFound: "+numControllersFound);
		log.info("controllersNames: "+(controllersNames));

		log.info("glVendor: "+(glVendor));
		log.info("glVersion: "+(glVersion));
		log.info("glRenderer: "+(glRenderer));
		log.info("shaderVersion: "+(shaderVersion));
		log.info("glExtensions: "+(glExtensions));

	}

}
