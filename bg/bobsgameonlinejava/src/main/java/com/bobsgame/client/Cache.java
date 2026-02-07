package com.bobsgame.client;


import static org.lwjgl.opengl.GL11.GL_COLOR_BUFFER_BIT;
import static org.lwjgl.opengl.GL11.glClear;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.Writer;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Properties;
import java.util.StringTokenizer;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;


import com.bobsgame.ClientMain;
//import netscape.javascript.JSObject;

import org.apache.commons.io.FileUtils;
import org.apache.commons.io.IOUtils;
import org.apache.commons.io.output.CountingOutputStream;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.console.Console;
import com.bobsgame.client.console.ConsoleText;
import com.bobsgame.net.BobNet;
import com.bobsgame.shared.Utils;
import com.bobsgame.shared.BobColor;
//===============================================================================================
public class Cache
{//===============================================================================================



	public static String cacheDir = "";
	public static String slash = "";

	public static String bigDataURL = "";//for zip files
	public static String smallDataURL = "";//for individual patch files (basically the newest zip file unzipped into dir)



	public static Logger log = (Logger) LoggerFactory.getLogger(Cache.class);

	//===============================================================================================
	public Cache()
	{//===============================================================================================


		if(BobNet.debugMode==true)//DEBUG
		{
			bigDataURL = BobNet.debugBigDataURL;
			smallDataURL = BobNet.debugSmallDataURL;
		}
		else
		{
			bigDataURL = BobNet.releaseBigDataURL;
			smallDataURL = BobNet.releaseSmallDataURL;
		}

		//cacheDir = "C:\\bobsGameCache\\";

		Properties prop = System.getProperties();

		/*

		log.debug("Java Runtime Environment version: "+prop.getProperty("java.version"));
		log.debug("Java Runtime Environment vendor: "+prop.getProperty("java.vendor"));
		log.debug("Java vendor URL: "+prop.getProperty("java.vendor.url"));
		log.debug("Java installation directory: "+prop.getProperty("java.home"));
		log.debug("Java Virtual Machine specification version: "+prop.getProperty("java.vm.specification.version"));
		log.debug("Java Virtual Machine specification vendor: "+prop.getProperty("java.vm.specification.vendor"));
		log.debug("Java Virtual Machine specification name: "+prop.getProperty("java.vm.specification.name"));
		log.debug("Java Virtual Machine implementation version: "+prop.getProperty("java.vm.version"));
		log.debug("Java Virtual Machine implementation vendor: "+prop.getProperty("java.vm.vendor"));
		log.debug("Java Virtual Machine implementation name: "+prop.getProperty("java.vm.name"));
		log.debug("Java Runtime Environment specification version: "+prop.getProperty("java.specification.version"));
		log.debug("Java Runtime Environment specification vendor: "+prop.getProperty("java.specification.vendor"));
		log.debug("Java Runtime Environment specification name: "+prop.getProperty("java.specification.name"));
		log.debug("Java class format version number: "+prop.getProperty("java.class.version"));
		log.debug("Java class path: "+prop.getProperty("java.class.path"));
		log.debug("List of paths to search when loading libraries: "+prop.getProperty("java.library.path"));
		log.debug("Default temp file path: "+prop.getProperty("java.io.tmpdir"));
		log.debug("Name of JIT compiler to use: "+prop.getProperty("java.compiler"));
		log.debug("Path of extension directory or directories: "+prop.getProperty("java.ext.dirs"));
		log.debug("Operating system name: "+prop.getProperty("os.name"));
		log.debug("Operating system architecture: "+prop.getProperty("os.arch"));
		log.debug("Operating system version: "+prop.getProperty("os.version"));
		log.debug("Path separator (':' on UNIX): "+prop.getProperty("path.separator"));
		log.debug("Line separator ('\\n' on UNIX): "+prop.getProperty("line.separator"));
		log.debug("User's account name: "+prop.getProperty("user.name"));
		log.debug("User's home directory: "+prop.getProperty("user.home"));
		log.debug("User's current working directory: "+prop.getProperty("user.dir"));
		log.debug("File separator ('/' on UNIX): "+prop.getProperty("file.separator"));

		*/


		slash = prop.getProperty("file.separator");//also File.separatorChar, File.separator
		cacheDir = prop.getProperty("user.home")+slash+".bobsGame"+slash;


	}


	//===============================================================================================
	public void writeSessionTokenToCache(int userID, String sessionToken, boolean statsAllowed)
	{//===============================================================================================

		File sessionFile = new File(cacheDir+"session");

		if(sessionFile.exists()==false)
		{
			try
			{
				sessionFile.createNewFile();
			}
			catch (IOException e1)
			{
				e1.printStackTrace();
			}
		}

		Writer output;
		try
		{
			output = new BufferedWriter(new FileWriter(sessionFile));
			output.write(""+userID+",`"+sessionToken+"`,"+statsAllowed);
			output.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}


	}


	//===============================================================================================
	public String readSessionTokenFromCache()
	{//===============================================================================================

		File sessionFile = new File(cacheDir+"session");

		if(sessionFile.exists()==false)return null;

		String line = null;

		try
		{
			BufferedReader input =  new BufferedReader(new FileReader(sessionFile));
			line = input.readLine();
			input.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}

		if(line!=null)
		{
			//log.debug(line);

			if(line.length()>0)return line;
		}

		return null;
	}


	//===============================================================================================
	public void deleteSessionTokenFromCache()
	{//===============================================================================================

		File sessionFile = new File(cacheDir+"session");

		if(sessionFile.exists()==false)
		{
			try
			{
				sessionFile.createNewFile();
			}
			catch (IOException e1)
			{
				e1.printStackTrace();
			}
		}

		Writer output;
		try
		{
			output = new BufferedWriter(new FileWriter(sessionFile));
			output.write("");
			output.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}

	}





	//===============================================================================================
	public void writeCookie(String s)
	{//===============================================================================================



		String data = "test";
		String cookiename = "fooCookie";
        // Removed JSObject usage
		//JSObject win = ClientMain.browser;
		//JSObject doc = (JSObject) win.getMember("document");

		String cookie = cookiename + "=" + data + "; path=/; expires=Thu, 31-Dec-2019 12:00:00 GMT";

		//doc.setMember("cookie", cookie);


		//TODO: Don't forget to encode your data in Base64.

        /*
		if(ClientMain.browser!=null)
		{
			try
			{

				ClientMain.browser.eval("document.cookie ='"+(String)s+"';");

			}
			catch(Exception ex)
			{

			}
		}
        */

	}



	//===============================================================================================
	public StringBuffer readCookies()
	{//===============================================================================================

        /*
		if(ClientMain.browser!=null)
		{

			String data = "";
			String cookiename = "fooCookie";


			JSObject myDocument = (JSObject) ClientMain.browser.getMember("document");

			String myCookie = (String) myDocument.getMember("cookie");


			if (myCookie.length() > 0) {
				String[] cookies = myCookie.split(";");
				for (String cookie : cookies) {
					int pos = cookie.indexOf("=");
					if (cookie.substring(0, pos).trim().equals(cookiename)) {
						data = cookie.substring(pos + 1);
						break;
					}
				}
			}

		}
        */







		StringBuffer cookieStringBuffer=new StringBuffer();


        /*
		if(ClientMain.browser!=null)
		{

			try
			{

				String linesep=System.getProperty("line.separator");

				String cookie= (String) ClientMain.browser.eval("document.cookie");

				StringTokenizer st=new StringTokenizer(cookie,";",false);


				//peel apart the cookies
				while(st.hasMoreTokens())
				{
					cookieStringBuffer.append(st.nextToken().trim()+linesep);
				}

			}
			catch(Exception ex)
			{

			}
		}
        */


		return cookieStringBuffer;

	}


	//===============================================================================================
	public static void writeBrowserSessionCookieAndRefreshIFrame()
	{//===============================================================================================
		// TODO
		//write COOKIE

	}


	//===============================================================================================
	public static void deleteBrowserSessionCookieAndRefreshIFrame()
	{//===============================================================================================
		// TODO

		//delete COOKIE

	}


	//===============================================================================================
	public static void writeBrowserSessionAndRefreshIFrame()
	{//===============================================================================================
		// TODO
		//write SESSION (temp)

	}











	String downloadingDataNiceName = "";
	ConsoleText statusConsoleText = null;
	long downloadingFileSize = 0;


	//===============================================================================================
	public void setStatusText(String text)
	{//===============================================================================================


		if(statusConsoleText==null)statusConsoleText = Console.add("",LWJGLUtils.SCREEN_SIZE_X/2-50,LWJGLUtils.SCREEN_SIZE_Y/2-10);

		statusConsoleText.x = LWJGLUtils.SCREEN_SIZE_X/2-((text.length() * 16)/2); // Approximation as we don't have font width
		statusConsoleText.y = LWJGLUtils.SCREEN_SIZE_Y/2-10;

		statusConsoleText.text=text;

		glClear(GL_COLOR_BUFFER_BIT);

		ClientMain.clientMain.console.render();

		//Display.update();
        LWJGLUtils.updateDisplay();

	}


	//===============================================================================================
	public void deleteStatusText()
	{//===============================================================================================

		if(statusConsoleText!=null)
		{
			statusConsoleText.text="";
			statusConsoleText.x = LWJGLUtils.SCREEN_SIZE_X;
			statusConsoleText.y = LWJGLUtils.SCREEN_SIZE_Y;

			statusConsoleText.ticks=1;//will be deleted from the console after 1 tick

			statusConsoleText = null;

			glClear(GL_COLOR_BUFFER_BIT);
			ClientMain.clientMain.console.render();
			//Display.update();
            LWJGLUtils.updateDisplay();
		}

	}


	//===============================================================================================
	private class ProgressListener implements ActionListener
	{//===============================================================================================
		@Override
		public void actionPerformed(ActionEvent e)
		{
			// e.getSource() gives you the object of DownloadCountingOutputStream because you set it in the overriden method, afterWrite().
			setStatusText("Downloading "+downloadingDataNiceName+": "+((DownloadCountingOutputStream) e.getSource()).getByteCount()/1024+" kB / "+downloadingFileSize/1024+" kB");
		}
	}



	//===============================================================================================
	public class DownloadCountingOutputStream extends CountingOutputStream
	{//===============================================================================================
		private ActionListener listener = null;
		public DownloadCountingOutputStream(OutputStream out)
		{
			super(out);
		}
		public void setListener(ActionListener listener)
		{
			this.listener = listener;
		}

		@Override
		protected void afterWrite(int n) throws IOException
		{
			super.afterWrite(n);
			if (listener != null)
			{
				listener.actionPerformed(new ActionEvent(this, 0, null));
			}
		}

	}


	//===============================================================================================
	public void downloadFileToCacheWithProgressListener(String fileName, String niceName)
	{//===============================================================================================

		downloadingDataNiceName = niceName;

		File outputFile = new File(cacheDir + fileName);
		//download sprites.zip and maps.zip from http://localhost/z/ and save to directory

		URL fileURL = null;

		try
		{
			fileURL = java.net.URI.create(bigDataURL+fileName).toURL();
		}
		catch (MalformedURLException e1)
		{
			e1.printStackTrace();
		}

//		try
//		{
//			org.apache.commons.io.FileUtils.copyURLToFile(fileURL, file, 60000, 60000);
//		}
//		catch (IOException e1)
//		{
//			e1.printStackTrace();
//		}


		OutputStream os = null;
		InputStream is = null;
		ProgressListener progressListener = new ProgressListener();


		try
		{

			os = new FileOutputStream(outputFile);
			is = fileURL.openStream();

			DownloadCountingOutputStream dcount = new DownloadCountingOutputStream(os);

			dcount.setListener(progressListener);

			// this line give you the total length of source stream as a String.
			// you may want to convert to integer and store this value to
			// calculate percentage of the progression.

			//setStatusText("Connecting to asset server...");



			String fileSizeString = fileURL.openConnection().getHeaderField("Content-Length");

			if(fileSizeString!=null)
			{
				downloadingFileSize = -1;
				try{downloadingFileSize = Long.parseLong(fileSizeString);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			}

			// begin transfer by writing to dcount, not os.
			IOUtils.copy(is, dcount);

		}
		catch (Exception e)
		{
			log.error("Error downloading file to cache! File: "+fileName+" Error: "+e.getMessage());
			e.printStackTrace();
		}
		finally
		{

			try
			{
				if (os != null)os.close();
				if (is != null)is.close();
			}
			catch(IOException e)
			{
				e.printStackTrace();
			}

		}

		//deleteStatusText();

	}



	//===============================================================================================
	public void decompressZipInCache(String fileName, String niceName)
	{//===============================================================================================

		setStatusText("Decompressing "+niceName+"...");

		try
		{

			File inputFile = new File(cacheDir + fileName);

			ZipInputStream zipInputStream = new ZipInputStream(new FileInputStream(inputFile));
			BufferedInputStream bufferedInputStream = new BufferedInputStream(zipInputStream);

			ZipEntry zipEntry = zipInputStream.getNextEntry();

			while(zipEntry!=null)
			{

				BufferedOutputStream bufferedOutputStream = new BufferedOutputStream(new FileOutputStream(new File(cacheDir + zipEntry.getName())));

				//int zipSize = (int)zipEntry.getCompressedSize();

				int bytesRead = 0;

				byte[] b = new byte[1024];

				while((bytesRead=bufferedInputStream.read(b)) != -1)
				{
					bufferedOutputStream.write(b, 0, bytesRead);
				}
				bufferedOutputStream.close();


				zipEntry = zipInputStream.getNextEntry();
			}

			bufferedInputStream.close();
			zipInputStream.close();

		}
		catch(IOException e)
		{
			e.printStackTrace();
			return;
		}

		deleteStatusText();

	}


	//===============================================================================================
	public void deleteFileFromCache(String fileName)
	{//===============================================================================================

		File file = new File(cacheDir + fileName);

		if(file.exists()==true)file.delete();

	}


	//===============================================================================================
	public static boolean checkIfFileExistsInCache(String fileName)
	{//===============================================================================================

		File file = new File(cacheDir + fileName);

		return file.exists();
	}


	//===============================================================================================
	public long getFileSizeInCache(String fileName)
	{//===============================================================================================


		if(checkIfFileExistsInCache(fileName)==true)return FileUtils.sizeOf(new File(cacheDir + fileName));
		else return -1;
	}


	//===============================================================================================
	public long getFileSizeOnServer(String fileName)
	{//===============================================================================================

		URL fileURL = null;

		try
		{
			fileURL = java.net.URI.create(bigDataURL+fileName).toURL();
		}
		catch (MalformedURLException e1)
		{
			e1.printStackTrace();
		}


		String fileSizeString = null;



		//setStatusText("Connecting to asset server...");


		try
		{
			fileSizeString = fileURL.openConnection().getHeaderField("Content-Length");
		}
		catch(Exception ex)
		{
			//setStatusText("Timed out, retrying...");
		}



		if(fileSizeString!=null)
		{
			long size = -1;
			try{size = Long.parseLong(fileSizeString);}catch(NumberFormatException ex){ex.printStackTrace();return -1;}
			return size;
		}

		//deleteStatusText();

		return -1;
	}




	//===============================================================================================
	public void downloadAndDecompressZIPFileIfDifferentFromServer(String fileName, String niceName)
	{//===============================================================================================


		long serverSize = getFileSizeOnServer(fileName);
		long localSize = getFileSizeInCache(fileName);

		log.debug(""+fileName+" size on server: "+serverSize);
		log.debug(""+fileName+" size in cache: "+localSize);

		if(localSize!=serverSize && serverSize>16)
		{
			deleteFileFromCache(fileName);
			downloadFileToCacheWithProgressListener(fileName,niceName);
			decompressZipInCache(fileName,niceName);
			deleteStatusText();
		}

	}
	//===============================================================================================
	public void downloadFileIfDifferentFromServer(String fileName, String niceName)
	{//===============================================================================================


		long serverSize = getFileSizeOnServer(fileName);
		long localSize = getFileSizeInCache(fileName);

		log.debug(""+fileName+" size on server: "+serverSize);
		log.debug(""+fileName+" size in cache: "+localSize);

		if(localSize!=serverSize && serverSize>16)
		{
			deleteFileFromCache(fileName);
			downloadFileToCacheWithProgressListener(fileName,niceName);
			//decompressZipInCache(fileName,niceName);
			deleteStatusText();
		}

	}



	//===============================================================================================
	public void initCache()
	{//===============================================================================================

		log.info("Init Cache...");

		Utils.makeDir(cacheDir);
		Utils.makeDir(cacheDir+"l"+slash);

		//File initFile = new File(cacheDir+"init");
		//if(initFile.exists()==false)
		//{
			// check filesize of sprites.zip locally
			// check filesize of sprites.zip on server
			//if different, delete sprites.zip locally, download sprites.zip, decompress.


			downloadAndDecompressZIPFileIfDifferentFromServer("sprites.zip","Sprite Graphics");
			downloadAndDecompressZIPFileIfDifferentFromServer("maps.zip","Background Graphics");
			downloadAndDecompressZIPFileIfDifferentFromServer("sounds.zip","Sound Effects");
			downloadAndDecompressZIPFileIfDifferentFromServer("music.zip","Initial Music Data");
			downloadFileIfDifferentFromServer("gameData","Initial Game Data");

			deleteStatusText();
			//FileUtils.listFiles(new File(cacheDir),null,true);


			//delete("sprites.zip");
			//delete("maps.zip");

//			try
//			{
//				initFile.createNewFile();
//			}
//			catch (IOException e1)
//			{
//				e1.printStackTrace();
//			}
		//}

		log.info("Cache Complete.");

	}


	//===============================================================================================
	public static void downloadBigFileToCacheIfNotExist(String fileName)
	{//===============================================================================================


		if(Utils.getResource(""+Cache.cacheDir+fileName)==null)
		{

			File outputFile = new File(cacheDir + fileName);

			URL fileURL = null;

			try
			{
				fileURL = java.net.URI.create(bigDataURL+fileName).toURL();
			}
			catch (MalformedURLException e1)
			{
				e1.printStackTrace();
			}


			OutputStream os = null;
			InputStream is = null;

			try
			{

				os = new FileOutputStream(outputFile);
				is = fileURL.openStream();

				// this line give you the total length of source stream as a String.
				// you may want to convert to integer and store this value to
				// calculate percentage of the progression.
				String fileSizeString = fileURL.openConnection().getHeaderField("Content-Length");


				// begin transfer by writing to dcount, not os.
				IOUtils.copy(is,os);

			}
			catch (Exception e)
			{
				log.error("Error downloading file to cache! File: "+fileName+" Error: "+e.getMessage());
				e.printStackTrace();
			}
			finally
			{

				try
				{
					if (os != null)os.close();
					if (is != null)is.close();
				}
				catch(IOException e)
				{
					e.printStackTrace();
				}

			}


		}

	}


	//===============================================================================================
	public static void downloadSmallFileToCacheIfNotExist(String fileName)
	{//===============================================================================================


		if(Utils.getResource(""+Cache.cacheDir+fileName)==null)
		{

			URL fileURL = null;

			try
			{
				fileURL = java.net.URI.create(smallDataURL+fileName).toURL();
			}
			catch (MalformedURLException e1)
			{
				e1.printStackTrace();
			}

			try
			{

				FileUtils.copyURLToFile(fileURL, new File(""+Cache.cacheDir+fileName), 60000, 60000);
			}
			catch (IOException e1)
			{
				e1.printStackTrace();
			}

		}

	}



	//===============================================================================================
	public static byte[] loadByteFileFromCacheOrDownloadIfNotExist(String fileName)
	{//===============================================================================================

		downloadSmallFileToCacheIfNotExist(fileName);

		return Utils.loadByteFile(""+Cache.cacheDir+fileName);
	}



	//===============================================================================================
	public static int[] loadIntFileFromCacheOrDownloadIfNotExist(String fileName)
	{//===============================================================================================


		downloadSmallFileToCacheIfNotExist(fileName);

		return Utils.loadIntFile(""+Cache.cacheDir+fileName);
	}


	//===============================================================================================
	public static void saveByteArrayToCache(byte[] byteArray,String md5FileName)
	{//===============================================================================================

		File outputFile = new File(cacheDir + md5FileName);

		try
		{
			FileUtils.writeByteArrayToFile(outputFile,byteArray);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

	}


	//===============================================================================================
	public static boolean doesDidIntroFileExist()
	{//===============================================================================================
		File introCheckFile = new File(Cache.cacheDir+".didIntro");
		if(introCheckFile.exists())return true;
		return false;
	}


	//===============================================================================================
	public static void writeDidIntroFile()
	{//===============================================================================================
		File introCheckFile = new File(Cache.cacheDir+".didIntro");
		try
		{
			introCheckFile.createNewFile();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
}
