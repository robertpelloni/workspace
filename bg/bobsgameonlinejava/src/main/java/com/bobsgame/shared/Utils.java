package com.bobsgame.shared;


import org.apache.commons.codec.binary.Base64;
import org.apache.commons.codec.binary.StringUtils;
import org.apache.commons.compress.archivers.zip.ZipArchiveEntry;
import org.apache.commons.compress.archivers.zip.ZipFile;
import org.apache.commons.io.IOUtils;
//import org.lwjgl.opengl.*;
//import static org.lwjgl.opengl.GL11.*;
//import static org.lwjgl.opengl.GL12.GL_CLAMP_TO_EDGE;
//import static org.lwjgl.opengl.GL12.GL_TEXTURE_BASE_LEVEL;
//import static org.lwjgl.opengl.GL12.GL_TEXTURE_MAX_LEVEL;
//import static org.lwjgl.opengl.GL12.GL_TEXTURE_WRAP_R;
//import static org.lwjgl.opengl.GL14.GL_GENERATE_MIPMAP;
//import static org.lwjgl.opengl.GL14.GL_TEXTURE_FILTER_CONTROL;
//import static org.lwjgl.opengl.GL14.GL_TEXTURE_LOD_BIAS;
//
//import org.lwjgl.opengl.GL11;
//import org.lwjgl.opengl.GL14;
//import org.lwjgl.opengl.GL32;
//import org.lwjgl.opengl.GL33;
//import org.lwjgl.opengl.GL42;
//import org.lwjgl.opengl.GLContext;
//import static org.lwjgl.opengl.EXTFramebufferObject.*;


import java.awt.FileDialog;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FilenameFilter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.StreamTokenizer;
import java.net.URL;
import java.nio.ByteBuffer;
import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import java.nio.charset.Charset;
import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipException;
import java.util.zip.ZipOutputStream;

import javax.imageio.IIOImage;
import javax.imageio.ImageIO;
import javax.imageio.ImageWriteParam;
import javax.imageio.ImageWriter;
import javax.imageio.stream.MemoryCacheImageOutputStream;

//import org.lwjgl.BufferUtils;
import org.slf4j.LoggerFactory;


import ch.qos.logback.classic.Logger;







//=========================================================================================================================
public class Utils
{//=========================================================================================================================

	public static Logger log = (Logger) LoggerFactory.getLogger(Utils.class);


	public static Utils utils;

	//=========================================================================================================================
	public Utils()
	{//=========================================================================================================================

		utils = this;

	}



	//=========================================================================================================================
	static public int distance( int x1, int y1, int x2, int y2 )
	{//=========================================================================================================================



		//Return the distance between the two points
		return (int)Math.sqrt( Math.pow( x2 - x1, 2 ) + Math.pow( y2 - y1, 2 ) );
	}

	//=========================================================================================================================
	static public float distance( float x1, float y1, float x2, float y2 )
	{//=========================================================================================================================

		//Return the distance between the two points
		return (float)Math.sqrt( Math.pow( x2 - x1, 2 ) + Math.pow( y2 - y1, 2 ) );
	}



	//=========================================================================================================================
	static public boolean isXYTouchingXY(float x, float y, float x2, float y2)
	{//=========================================================================================================================
		return isXYTouchingXYByAmount(x,y,x2,y2,0);
	}
	//=========================================================================================================================
	static public boolean isXYXYTouchingXY(float left, float top, float right, float bottom, float x, float y)
	{//=========================================================================================================================
		return isXYXYTouchingXYByAmount(left,top,right,bottom,x,y,0);
	}
	//=========================================================================================================================
	static public boolean isXYTouchingXYXY(float x, float y, float left, float top, float right, float bottom)
	{//=========================================================================================================================
		return isXYTouchingXYXYByAmount(x, y, left, top, right, bottom, 0);
	}
	//=========================================================================================================================
	static public boolean isXYXYTouchingXYXY(float myLeft, float myTop, float myRight, float myBottom, float left, float top, float right, float bottom)
	{//=========================================================================================================================
		return isXYXYTouchingXYXYByAmount(myLeft, myTop, myRight, myBottom, left, top, right, bottom, 0);
	}
	//=========================================================================================================================
	static public boolean isXYTouchingXYByAmount(float x, float y, float x2, float y2,int amt)
	{//=========================================================================================================================
		return isXYXYTouchingXYXYByAmount(x, y, x, y, x2,y2,x2,y2,amt);
	}
	//=========================================================================================================================
	static public boolean isXYXYTouchingXYByAmount(float left, float top, float right, float bottom, float x, float y, int amt)
	{//=========================================================================================================================
		return isXYXYTouchingXYXYByAmount(left, top, right, bottom,x,y,x,y,amt);
	}
	//=========================================================================================================================
	static public boolean isXYTouchingXYXYByAmount(float x, float y, float left, float top, float right, float bottom,int amt)
	{//=========================================================================================================================
		return isXYXYTouchingXYXYByAmount(x, y, x, y, left, top, right, bottom, amt);
	}
	//=========================================================================================================================
	static public boolean isXYXYTouchingXYXYByAmount(float myLeft, float myTop, float myRight, float myBottom, float left, float top, float right, float bottom,int amt)
	{//=========================================================================================================================
		myLeft = Math.round(myLeft);
		myTop = Math.round(myTop);
		myRight = Math.round(myRight);
		myBottom = Math.round(myBottom);
		left = Math.round(left);
		top = Math.round(top);
		right = Math.round(right);
		bottom = Math.round(bottom);

		if
		(
			(myTop-amt<=bottom&&myBottom+amt>=top)//above
			&&
			(myLeft-amt<=right&&myRight+amt>=left)//to left
		)
		return true;

		return false;
	}


	//=========================================================================================================================
	static public int randLessThan(int n)
	{//=========================================================================================================================
		return ((int)(Math.random()*n));
	}

	//=========================================================================================================================
	static public int randUpToIncluding(int n)
	{//=========================================================================================================================
		return ((int)(Math.random()*(n+1)));
	}

	//=========================================================================================================================
	static public int randMinMax(int from, int to)
	{//=========================================================================================================================
		return (int)(from+(int)(Math.random()*((to-from)+1)));
	}

	//=========================================================================================================================
	static public float randLessThanFloat(float n)
	{//=========================================================================================================================
		return (float)(Math.random()*n);
	}

	//=========================================================================================================================
	static public float randMinMaxFloat(float from, float to)
	{//=========================================================================================================================
		return (float)(from+(Math.random()*(to-from)));
	}


	//===========================================================================================================================
	static public int getClosestPowerOfTwo(int fold)
	{//===========================================================================================================================



		int ret = 2;
		while (ret < fold) {
			ret *= 2;
		}
		return ret;



		/*v--;
		v|=v>>1;
		v|=v>>2;
		v|=v>>4;
		v|=v>>8;
		v|=v>>16;
		v++;
		return v++;*/
	}


	//==========================================================================================================================
	static public boolean isTexturePowerOfTwo(int width, int height)// Check for non-power-of-two textures
	{//==========================================================================================================================
		if ((int)Math.pow(2.0f, Math.ceil(Math.log((float)width)/Math.log(2.0f))) != width)
			return true;
		if ((int)Math.pow(2.0f,  Math.ceil(Math.log((float)height)/Math.log(2.0f))) != height)
			return true;
		else
			return false;
	}

    public static byte[] getResourceAsBytes(String filename) {
        try (InputStream is = getResourceAsStream(filename)) {
            if (is == null) return null;
            return IOUtils.toByteArray(is);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static ByteBuffer ioResourceToByteBuffer(String resource, int bufferSize) throws IOException {
        ByteBuffer buffer;

        try (InputStream source = getResourceAsStream(resource)) {
            if (source == null) return null;

            try (ReadableByteChannel rbc = Channels.newChannel(source)) {
                buffer = ByteBuffer.allocateDirect(bufferSize);

                while (true) {
                    int bytes = rbc.read(buffer);
                    if (bytes == -1) {
                        break;
                    }
                    if (buffer.remaining() == 0) {
                        ByteBuffer newBuffer = ByteBuffer.allocateDirect(buffer.capacity() * 3 / 2);
                        buffer.flip();
                        newBuffer.put(buffer);
                        buffer = newBuffer;
                    }
                }
            }
        }

        buffer.flip();
        return buffer;
    }


	//=========================================================================================================================
	public static InputStream getResourceAsStream(String filename)
	{//=========================================================================================================================



		//don't use absolute paths starting from the folder we are in. /whatever.jpg
		if(
				filename.startsWith("/")==true
				&&
				filename.startsWith(System.getProperty("user.home"))==false //fix for linux

		)
		{
			filename = filename.substring(1);//cut off the /
			log.debug("Don't use absolute paths, fix this.");
		}


		//if we are using stuff from /res/ we should get them from the ClassLoader which gets them from inside the JAR (but removed from /res/ for some reason)
		if(filename.startsWith("res/")==true)
		{
			filename = filename.substring(4);
			InputStream is = utils.getClass().getClassLoader().getResourceAsStream(filename);

			if(is==null)log.error("Could not find file in ClassLoader: "+filename);

			return is;
		}
		else //we are accessing from the hard disk. try the resource loader which will get it as a file.
		{
			FileInputStream stream = null;
			try
			{
				File file = new File(filename);

				if (!file.exists())
				{
					file = new File(new File("."), filename);
				}

				if(!file.exists())
				{
					log.error("Could not find file: "+filename);
					return null;
				}
				else
				{
					stream = new FileInputStream(file);
				}

			}
			catch (IOException e)
			{
				log.error("Error opening file: "+filename);
				stream = null;
			}

			if(stream==null)
			{



			}


			return stream;

		}


	}
	//=========================================================================================================================
	public static URL getResource(String filename)
	{//=========================================================================================================================


		//don't use absolute paths starting from the folder we are in. /whatever.jpg
		if(
				filename.startsWith("/")==true
				&&
				filename.startsWith(System.getProperty("user.home"))==false //fix for linux

		)
		{
			filename = filename.substring(1);//cut off the /
			log.debug("Don't use absolute paths, fix this.");
		}



		//if we are using stuff from /res/ we should get them from the ClassLoader which gets them from inside the JAR (but removed from /res/ for some reason)
		if(filename.startsWith("res/")==true)
		{
			filename = filename.substring(4);
			URL is =  utils.getClass().getClassLoader().getResource(filename);

			if(is==null)log.error("Could not find file in ClassLoader: "+filename);

			return is;

		}
		else //we are accessing from the hard disk. try the resource loader which will get it as a file.
		{

			try
			{
				File file =  new File(filename);
				if(file.exists()==false)
				{
					file = new File(new File("."), filename);
				}


				if(file.exists()==false)
				{
					log.error("Could not find file: "+filename);

					//if(BobNet.debugMode)new Exception().printStackTrace();

					return null;
				}
				else
				{
					return file.toURI().toURL();
				}

			}
			catch (IOException e)
			{
				log.error("Error opening file: "+filename);
				return null;
			}


		}
	}


	//=========================================================================================================================
	public static int[] oldLoadShortIntFile(String filename)
	{//=========================================================================================================================
		File file = new File(filename);


		int[] intArray = new int[((int) file.length())/2];

		BufferedInputStream bin = new BufferedInputStream(Utils.getResourceAsStream(filename));

		try
		{
			int sbyte1=bin.read();//signed byte 1
			int sbyte2=bin.read();
			int i=0;

			while(sbyte1!=-1||sbyte2!=-1)
			{

				int ubyte1 = sbyte1 & 0xFF;
				int ubyte2 = sbyte2 & 0xFF;

				int result = (ubyte2<<8) + ubyte1;

				intArray[i]=result;
				i++;
				sbyte1=bin.read();
				sbyte2=bin.read();
			}

			bin.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}

		return intArray;

	}


	//=========================================================================================================================
	public static int[] loadIntFile(String filename)
	{//=========================================================================================================================

//		byte[] byteArray = loadByteFile(filename);
//
//		int[] intArray = new int[byteArray.length/2];
//
//		for(int x=0;x<intArray.length;x++)
//		{
//			int sbyte1=byteArray[x*2+0];//signed byte 1
//			int sbyte2=byteArray[x*2+1];
//
//
//			int ubyte1 = sbyte1 & 0xFF;
//			int ubyte2 = sbyte2 & 0xFF;
//
//			int result = (ubyte2<<8) + ubyte1;
//
//			intArray[x]=result;
//		}

		return getIntArrayFromByteArray(loadByteFile(filename));
	}


	//=========================================================================================================================
	public static byte[] oldLoadByteFile(String filename)
	{//=========================================================================================================================

		//relies on file system, no good!
		File file = new File(filename);
		byte[] byteArray = new byte[(int) file.length()];

		//BufferedInputStream bin = new BufferedInputStream(Utils.class.getClass().getClassLoader().getResourceAsStream(filename));

		BufferedInputStream bin = new BufferedInputStream(Utils.getResourceAsStream(filename));

		try
		{
			bin.read(byteArray);
			bin.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}

		return byteArray;

	}

	//=========================================================================================================================
	public static byte[] loadByteFile(String filename)
	{//=========================================================================================================================


		BufferedInputStream inputStream = new BufferedInputStream(Utils.getResourceAsStream(filename));
		//ByteArrayOutputStream outputStream = new ByteArrayOutputStream();



		try
		{
			return IOUtils.toByteArray(inputStream);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		return null;

//		byte[] byteData = null;
//
//		try
//		{
//
//			// Read bytes from the input stream in bytes.length-sized chunks and write
//			// them into the output stream
//			for(int readBytes = inputStream.read(); readBytes >= 0; readBytes = inputStream.read())
//				outputStream.write(readBytes);
//
//			// Convert the contents of the output stream into a byte array
//			byteData = outputStream.toByteArray();
//
//			// Close the streams
//			inputStream.close();
//			outputStream.close();
//		}
//		catch (IOException e)
//		{
//			e.printStackTrace();
//		}
//
//		return byteData;
	}


	//==========================================================================================================================
	int rgbatoABGRInt(char r, char g, char b, char a)
	{//==========================================================================================================================
		return ((a<<15)+((b)<<10)+((g)<<5)+(r));
	}



	//===============================================================================================
	public static int HexToDec(String hexst)
	{//===============================================================================================
		return Integer.parseInt(hexst, 16);
	}


	//===============================================================================================
	public static int DecToRed(int dec)
	{//===============================================================================================
		return (dec % 32) * 8;
	}


	//===============================================================================================
	public static int DecToGreen(int dec)
	{//===============================================================================================
		return ((dec / 32) % 32) * 8;
	}


	//===============================================================================================
	public static int DecToBlue(int dec)
	{//===============================================================================================
		return (dec / 1024) * 8;
	}



	// ===============================================================================================
	public static String zipByteArrayToString(byte[] byteArray)
	{// ===============================================================================================


		String outStr = null;
		try
		{
			ByteArrayOutputStream out = new ByteArrayOutputStream();

			GZIPOutputStream gzip=new GZIPOutputStream(out);
			gzip.write(byteArray);
			gzip.close();

			outStr=out.toString("ISO-8859-1");

		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		return outStr;
	}

	// ===============================================================================================
	public static byte[] unzipStringToByteArray(String zippedBytesAsString)
	{// ===============================================================================================

		GZIPInputStream gis = null;

		try
		{

			ByteArrayInputStream is = new ByteArrayInputStream(zippedBytesAsString.getBytes("ISO-8859-1"));

			gis = new GZIPInputStream(is);

			return IOUtils.toByteArray(new InputStreamReader(gis,"ISO-8859-1"),"ISO-8859-1");

		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		return null;
	}


	// ===============================================================================================
	public static String zipString(String s)
	{// ===============================================================================================
		if(s==null||s.length()==0){return s;}

		//System.out.println("String length : "+str.length());
		ByteArrayOutputStream out=new ByteArrayOutputStream();
		GZIPOutputStream gzip;

		String outStr = null;


		try
		{
			gzip=new GZIPOutputStream(out);
			gzip.write(s.getBytes());
			gzip.close();

			outStr=out.toString("ISO-8859-1");
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}


		//System.out.println("Output String length : "+outStr.length());
		return outStr;
	}


	// ===============================================================================================
	public static String unzipString(String s)
	{// ===============================================================================================
		if(s==null||s.length()==0){return s;}
		//System.out.println("Input String length : "+str.length());


		GZIPInputStream gis = null;
		String outStr = null;

		try
		{
			gis=new GZIPInputStream(new ByteArrayInputStream(s.getBytes("ISO-8859-1")));
			BufferedReader bf=new BufferedReader(new InputStreamReader(gis,"ISO-8859-1"));

			outStr="";
			String line;
			while((line=bf.readLine())!=null)
			{
				outStr+=line;
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}



		//System.out.println("Output String length : "+outStr.length());
		return outStr;
	}


	// ===============================================================================================
	public static String decodeBase64String(String s)
	{// ===============================================================================================
		if(s==null||s.length()==0){return s;}
		return StringUtils.newStringUtf8(Base64.decodeBase64(s));
	}


	// ===============================================================================================
	public static String encodeStringToBase64(String s)
	{// ===============================================================================================
		if(s==null||s.length()==0){return s;}
		return Base64.encodeBase64String(StringUtils.getBytesUtf8(s));
	}



	//===============================================================================================
	public static byte[] getByteArrayFromIntArray(int[] intArray)
	{//===============================================================================================
		ByteBuffer byteBuffer = ByteBuffer.allocate(intArray.length * 4);
		IntBuffer intBuffer = byteBuffer.asIntBuffer();
		intBuffer.put(intArray);

		return byteBuffer.array();
	}



	//===============================================================================================
	public static int[] getIntArrayFromByteArray(byte[] bytes)
	{//===============================================================================================


		ByteBuffer byteBuffer = ByteBuffer.wrap(bytes);
		IntBuffer intBuffer = byteBuffer.asIntBuffer();

		int[] intArray = new int[bytes.length/4];
		intBuffer.get(intArray);

		return intArray;
	}


	//===============================================================================================
	public static byte[] getByteArrayFromFileInZip(ZipFile zip, String fileName)
	{//===============================================================================================

		ZipArchiveEntry z = zip.getEntry(fileName);
		long size = z.getSize();
		byte[] bytes = new byte[(int)size];

		InputStream zin = null;

		try
		{
			zin = zip.getInputStream(z);
			IOUtils.readFully(zin,bytes);
			zin.close();
		}
		catch(ZipException e1)
		{
			e1.printStackTrace();
		}
		catch(IOException e1)
		{
			e1.printStackTrace();
		}

		return bytes;
	}


	//===============================================================================================
	public static int[] getIntArrayFromFileInZip(ZipFile zip, String fileName)
	{//===============================================================================================

		return getIntArrayFromByteArray(getByteArrayFromFileInZip(zip,fileName));
	}



	//===============================================================================================
	public static String putFileInZipAsMD5(ZipOutputStream zos, String filename)
	{//===============================================================================================

		String md5FileName = "";
		try
		{
			md5FileName = getFileMD5Checksum(filename);
			File file = new File(filename);
			FileInputStream fis = new FileInputStream(file);
			ZipEntry anEntry = new ZipEntry(md5FileName);

			boolean exists = false;
			try
			{
				zos.putNextEntry(anEntry);
			}
			catch(Exception e)
			{
				exists = true;
			}

			if(exists==false)
			{
				byte[] readBuffer = new byte[(int)file.length()];

				IOUtils.readFully(fis,readBuffer);
				IOUtils.write(readBuffer,zos);
			}
			fis.close();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}

		return md5FileName;
	}



	//===============================================================================================
	public static String getFileMD5Checksum(String filename)
	{//===============================================================================================

		byte[] md5bytes = new byte[1];
		try
		{
			InputStream fis =  new FileInputStream(filename);
			byte[] buffer = new byte[1024];
			MessageDigest complete = MessageDigest.getInstance("MD5");
			int numRead;

			do
			{
				numRead = fis.read(buffer);
				if (numRead > 0) {
					complete.update(buffer, 0, numRead);
				}
			}
			while (numRead != -1);

			fis.close();

			md5bytes = complete.digest();
		}
		catch(Exception e)
		{

		}


		String result = "";

		for (int i=0; i < md5bytes.length; i++)
		{
			result += Integer.toString( ( md5bytes[i] & 0xff ) + 0x100, 16).substring( 1 );
		}
		return result;
	}

	//===============================================================================================
	public static String getByteArrayMD5Checksum(byte[] bytes)
	{//===============================================================================================

		byte[] md5bytes = new byte[1];
		try
		{

			MessageDigest complete = MessageDigest.getInstance("MD5");

			complete.update(bytes);

			md5bytes = complete.digest();
		}
		catch(Exception e)
		{

		}


		String result = "";

		for (int i=0; i < md5bytes.length; i++)
		{
			result += Integer.toString( ( md5bytes[i] & 0xff ) + 0x100, 16).substring( 1 );
		}
		return result;
	}

	//===============================================================================================
	public static String getStringMD5(String stringToMD5)
	{//===============================================================================================
		try
		{
				java.security.MessageDigest md = java.security.MessageDigest.getInstance("MD5");
				byte[] array = md.digest(stringToMD5.getBytes(Charset.forName("UTF8")));
				StringBuffer sb = new StringBuffer();
				for (int i = 0; i < array.length; ++i)
				{
				sb.append(Integer.toHexString((array[i] & 0xFF) | 0x100).substring(1,3));
				}
				return sb.toString();
		}
		catch (java.security.NoSuchAlgorithmException e)
		{

		}
		return null;
	}




	//===============================================================================================
	public static void saveImage(String s, BufferedImage bufferedImage)
	{//===============================================================================================

//		Iterator<ImageWriter> imageWritersIterator = ImageIO.getImageWritersByFormatName("png");
//		ImageWriter imageWriter = (ImageWriter) imageWritersIterator.next();
//
//		FileOutputStream fileOutputStream = null;
//		File file = null;
//		MemoryCacheImageOutputStream memoryCacheImageOutputStream = null;
//
//		try
//		{
//			file = new File(s);
//			fileOutputStream = new FileOutputStream(file);
//			memoryCacheImageOutputStream = new MemoryCacheImageOutputStream(fileOutputStream);
//		}
//		catch(FileNotFoundException e){log.error("Could not create PNG file. Error: "+e.getMessage());e.printStackTrace();return;}
//
//		imageWriter.setOutput(memoryCacheImageOutputStream);
//		ImageWriteParam iwp = imageWriter.getDefaultWriteParam();
//		try
//		{
//			imageWriter.write(null, new IIOImage(bufferedImage, null, null), iwp);//param);
//		}
//		catch(IOException e){log.error("An error occured during writing PNG file. Error: "+e.getMessage());e.printStackTrace();return;}
//
//		imageWriter.dispose();
//
//		try
//		{
//			memoryCacheImageOutputStream.close();
//			fileOutputStream.close();
//		}
//		catch(IOException e){e.printStackTrace();}


		File f = new File(s);
		try
		{
			f.createNewFile();
		}
		catch(IOException e1)
		{
			e1.printStackTrace();
		}

		try
		{
			ImageIO.write(bufferedImage, "PNG", f);
		} catch (IOException e) { e.printStackTrace(); }


	}



	//===============================================================================================
	public static void makeDir(String s)
	{//===============================================================================================
		File file = new File(s);

		if(file.exists()==false)
		{
			try
			{
				file.mkdirs();
			}
			catch(SecurityException e){log.error("Could not create directory: "+s+" "+e.getMessage());}
		}
	}



	public static int abs(int i)
	{
		if(i<0)return i*-1;
		else return i;
	}
}
