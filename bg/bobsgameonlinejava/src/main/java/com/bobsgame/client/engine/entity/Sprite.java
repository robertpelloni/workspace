package com.bobsgame.client.engine.entity;

import hq2x.HQ2X;

import ch.qos.logback.classic.Logger;

import java.awt.image.BufferedImage;
import java.io.File;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import org.slf4j.LoggerFactory;

import com.bobsgame.client.Texture;


import com.bobsgame.client.GLUtils;
import com.bobsgame.client.Cache;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.event.Event;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.client.engine.game.Item;
import com.bobsgame.client.engine.map.MapManager;
import com.bobsgame.net.BobNet;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.EventData;
import com.bobsgame.shared.SpriteAnimationSequence;
import com.bobsgame.shared.SpriteData;
import com.bobsgame.shared.Utils;


//=========================================================================================================================
public class Sprite extends EnginePart
{//=========================================================================================================================

	public static Logger log = (Logger) LoggerFactory.getLogger(Sprite.class);

	static public ExecutorService generatePNGExecutorService = null;

	public int[] indexDataIntArray = null;
	public byte[] paletteRGBByteArray = null;





	public Texture texture = null;
	public Texture shadowTexture = null;




	public boolean useHQ2X = false;


	private SpriteData data;



	private boolean _isInitialized = false;
	public long lastSentDataRequestTime = 0;


	//=========================================================================================================================
	public Sprite(Engine g)
	{//=========================================================================================================================
		super(g);
	}

	//=========================================================================================================================
	public synchronized void initalizeWithSpriteData(SpriteData spriteData)
	{//=========================================================================================================================

		if(this.data!=null)return;

		_isInitialized = true;

		if(spriteData==null)
		{
			spriteData = new SpriteData(-1,"none","",0,0,1,false,false,false,false,false,false,false,false,false,false,false,false,false,false,null,"",0,0,0,"","");
			log.warn("spriteData was null in SpriteAsset.init()");
			if(BobNet.debugMode)new Exception().printStackTrace();
		}

		this.data = spriteData;


		if(name()==null||name().equals("none")||name().length()==0)this.texture = GLUtils.blankTexture;


		if(isCar())useHQ2X = true;
		if(forceHQ2X())useHQ2X = true;

		if(isItem() || isGame())new Item(Engine(),this);

	}

	//=========================================================================================================================
	public void sendDataRequest(String spriteName)
	{//=========================================================================================================================

		if((Engine() instanceof ClientGameEngine)==false)return;

		long time = System.currentTimeMillis();
		if(time-lastSentDataRequestTime>1000)
		{
			lastSentDataRequestTime = time;

			Network().sendSpriteDataRequestByName(spriteName);
		}
	}
	//=========================================================================================================================
	public void sendDataRequest(int id)
	{//=========================================================================================================================

		if((Engine() instanceof ClientGameEngine)==false)return;

		long time = System.currentTimeMillis();
		if(time-lastSentDataRequestTime>1000)
		{
			lastSentDataRequestTime = time;

			Network().sendSpriteDataRequestByID(id);
		}
	}



	//=========================================================================================================================
	public synchronized boolean getInitialized_S()
	{//=========================================================================================================================
		return _isInitialized;
	}
	//=========================================================================================================================
	protected synchronized void setInitialized_S(boolean i)
	{//=========================================================================================================================
		_isInitialized=i;
	}






	//===============================================================================================
	public void drawFrame(String animationName, float x0,float x1,float y0,float y1,float r,float g,float b,float a,int filter)
	{//===============================================================================================

		SpriteAnimationSequence s = getAnimationByName(animationName);

		if(s!=null)
		{
			drawFrame(this.texture, s.frameStart,x0,x1,y0,y1,r,g,b,a,filter);
		}
		else
		{
			//log.error("Could not find animation: "+animationName+" in Sprite: "+name());
			drawFrame(this.texture, 0,x0,x1,y0,y1,r,g,b,a,filter);
		}

	}


	//===============================================================================================
	public void drawFrame(int frame, float x0,float x1,float y0,float y1, float a,int filter)
	{//===============================================================================================
		drawFrame(this.texture,frame,x0,x1,y0,y1,1.0f,1.0f,1.0f,a,filter);
	}

	//===============================================================================================
	public void drawFrame(Texture texture, int frame, float x0,float x1,float y0,float y1, float a,int filter)
	{//===============================================================================================
		drawFrame(texture,frame,x0,x1,y0,y1,1.0f,1.0f,1.0f,a,filter);
	}

	//===============================================================================================
	public void drawFrame(int frame, float x0,float x1,float y0,float y1,float r,float g,float b,float a,int filter)
	{//===============================================================================================
		if(spriteTextureInitialized==true&&this.texture!=null)drawFrame(this.texture,frame,x0,x1,y0,y1,r,g,b,a,filter);
	}

	//===============================================================================================
	public void drawFrame(Texture texture, int frame, float x0,float x1,float y0,float y1,float r,float g,float b,float a,int filter)
	{//===============================================================================================

		if(texture!=null)
		{
			float tx0 = 0.0f;
			float tx1 = ((float)w()/(float)texture.getTextureWidth());
			float ty0 = (((float)h())*frame)/(float)texture.getTextureHeight();
			float ty1 = (((float)h())*(frame+1))/(float)texture.getTextureHeight();


			GLUtils.drawTexture(texture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,r,g,b,a,filter);
		}
	}










	private long lastCheckedSpriteTextureTime = 0;
	private boolean spriteTextureInitialized = false;

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

		if(eventData()!=null)
		{
			Event event = EventManager().getEventByIDCreateIfNotExist(eventData().id());
			EventManager().addToEventQueueIfNotThere(event);//events update their own network data inside their run function
		}



		{

			if(spriteTextureInitialized==false)
			{
				long time = System.currentTimeMillis();
				//small delay to prevent thread locking on synchronized functions.
				if(time-lastCheckedSpriteTextureTime>200)
				{
					lastCheckedSpriteTextureTime = time;

					if(texture==null)
					{
						//this has its own timer delay (when send network request)
						if(dataMD5()!=null&&dataMD5().length()>0)
						{
							loadTextures();
						}
						else
						{
							spriteTextureInitialized=true;
						}
					}
					else
					{
						spriteTextureInitialized=true;
					}

				}
			}
		}


	}



//	long lastTimeRequestedDataMD5s=0;
//
//	//=========================================================================================================================
//	public void requestDataMD5sFromServer()
//	{//=========================================================================================================================
//
//		long time = System.currentTimeMillis();
//		if(time-lastTimeRequestedDataMD5s>3000)
//		{
//			lastTimeRequestedDataMD5s = time;
//
//			//send a request to the server
//			ClientMain.clientTCP.sendSpriteDataRequestByName(name());
//			//when server sends back response, in BGClient, look up sprite asset by identifier, set textureMD5Names and build texture!!
//		}
//	}





	public boolean threadCreated=false;
	public boolean checkedIfExist=false;
	public boolean hasDataMD5 = false;//non-threaded boolean check to avoid locking on synchronized function

	//=========================================================================================================================
	public void loadTextures()
	{//=========================================================================================================================


		if(isRandom()==true)
		{


				//random bin MD5s are initialized already in the spriteAssetIndex, don't need to get them from the server.


				//we always need the bin byte arrays loaded for randoms, since we will be using them each time we make a new random

				if(indexDataIntArray==null)indexDataIntArray = Cache.loadIntFileFromCacheOrDownloadIfNotExist(""+dataMD5());
				if(paletteRGBByteArray==null)paletteRGBByteArray = Cache.loadByteFileFromCacheOrDownloadIfNotExist(""+paletteMD5());



				//TODO: check for 1x shadow png as well if not multicore


				//check if hq2x shadow png exists under md5 name folder

				//construct shadow texture if it doesn't exist (if hasShadow)

				//we don't need to construct a normal hq2x png for randoms because it will never be used.


				if(texture==null)
				{
					if(hasShadow()==true)
					{

						if(checkedIfExist==false) //only check once if file exists already
						{
							checkedIfExist=true;

							File textureFile = null;
							if(useHQ2X)textureFile = new File(Cache.cacheDir+"_"+dataMD5()+Cache.slash+"2x"+Cache.slash+dataMD5()+"s");
							else textureFile = new File(Cache.cacheDir+"_"+dataMD5()+Cache.slash+"1x"+Cache.slash+dataMD5()+"s");

							if(textureFile.exists())
							{
								setSpritePNGFileExists_S(true);
							}
						}


						if(getSpritePNGFileExists_S()==true)
						{

							texture = GLUtils.blankTexture;
							if(useHQ2X)shadowTexture = GLUtils.loadTexture(Cache.cacheDir+"_"+dataMD5()+Cache.slash+"2x"+Cache.slash+dataMD5()+"s");
							else shadowTexture = GLUtils.loadTexture(Cache.cacheDir+"_"+dataMD5()+Cache.slash+"1x"+Cache.slash+dataMD5()+"s");

							//incrementSpriteTexturesLoaded();
						}
						else
						{

							// if neither exist, load the byte arrays and make them depending on settings (cpu multicore required for hq2x)

							if(threadCreated==false)
							{

								threadCreated=true;

								Utils.makeDir(Cache.cacheDir+"_"+dataMD5());
								Utils.makeDir(Cache.cacheDir+"_"+dataMD5()+Cache.slash+"1x"+Cache.slash);
								Utils.makeDir(Cache.cacheDir+"_"+dataMD5()+Cache.slash+"2x"+Cache.slash);

								if(MapManager.useThreads==true&&generatePNGExecutorService==null)generatePNGExecutorService = Executors.newFixedThreadPool(1);

								if(MapManager.useThreads==true)
								{
										//incrementSpritePNGThreadsCreated_S();

										generatePNGExecutorService.execute
										(
											new Runnable()
											{

												public void run()
												{
													try{Thread.currentThread().setName("Sprite_createSpriteRandomShadowTexturePNG");}catch(SecurityException e){e.printStackTrace();}
													//createSpriteTexturePNG();

													if(hasShadow()==true)createSpriteShadowTexturePNG_S();

													setSpritePNGFileExists_S(true);
													//decrementSpritePNGThreadsCreated_S();
												}
											}
										);

								}
								else
								{
									//do it linearly, waiting for all chunks to finish before continuing
									//createSpriteTexturePNG();

									if(hasShadow()==true)createSpriteShadowTexturePNG_S();

									setSpritePNGFileExists_S(true);
								}
							}

						}
					}
					else
					{
						texture = GLUtils.blankTexture;
						shadowTexture = GLUtils.blankTexture;
					}
				}




		}
		else
		{

			//should always have this now since we are loading the spriteData from server instead of just the MD5
			//so if the spriteAsset exists, it has MD5s, or the texture is blankTexture if it was initialized with null


//			if(hasDataMD5==false)//unsynchronized check to avoid locking on synchronized function
//			{
//				if(dataMD5()==null)
//				{
//					requestDataMD5sFromServer();
//				}
//				else
//				{
//					hasDataMD5=true;
//				}
//			}
//			else


			if(texture==null)
			{

				//we've gotten the bin MD5s from the server. now we have to construct the PNGs

				//check if hq2x png exists under md5 name folder

				//TODO: check if 1x png exists under md5 name folder



				if(checkedIfExist==false) //only check once if file exists already
				{
					checkedIfExist=true;

					File textureFile = null;
					if(useHQ2X)textureFile = new File(Cache.cacheDir+"_"+dataMD5()+Cache.slash+"2x"+Cache.slash+dataMD5());
					else textureFile = new File(Cache.cacheDir+"_"+dataMD5()+Cache.slash+"1x"+Cache.slash+dataMD5());
					if(textureFile.exists())
					{
						setSpritePNGFileExists_S(true);
					}
				}


				if(getSpritePNGFileExists_S()==true)
				{

					if(useHQ2X==true)texture = GLUtils.loadTexture(Cache.cacheDir+"_"+dataMD5()+Cache.slash+"2x"+Cache.slash+dataMD5());
					else texture = GLUtils.loadTexture(Cache.cacheDir+"_"+dataMD5()+Cache.slash+"1x"+Cache.slash+dataMD5());

					if(hasShadow()==true)
					{
						if(useHQ2X)shadowTexture = GLUtils.loadTexture(Cache.cacheDir+"_"+dataMD5()+Cache.slash+"2x"+Cache.slash+dataMD5()+"s");
						else shadowTexture = GLUtils.loadTexture(Cache.cacheDir+"_"+dataMD5()+Cache.slash+"1x"+Cache.slash+dataMD5()+"s");
					}
					else shadowTexture = GLUtils.blankTexture;

					//incrementSpriteTexturesLoaded();
				}
				else
				{

					// if neither exist, load the byte arrays and make them depending on settings (cpu multicore required for hq2x)

					if(threadCreated==false)
					{

						threadCreated=true;


						//make thread

						if(indexDataIntArray==null)indexDataIntArray = Cache.loadIntFileFromCacheOrDownloadIfNotExist(""+dataMD5());
						if(paletteRGBByteArray==null)paletteRGBByteArray = Cache.loadByteFileFromCacheOrDownloadIfNotExist(""+paletteMD5());


						Utils.makeDir(Cache.cacheDir+"_"+dataMD5());
						Utils.makeDir(Cache.cacheDir+"_"+dataMD5()+Cache.slash+"1x"+Cache.slash);
						Utils.makeDir(Cache.cacheDir+"_"+dataMD5()+Cache.slash+"2x"+Cache.slash);



						if(MapManager.useThreads==true&&generatePNGExecutorService==null)generatePNGExecutorService = Executors.newFixedThreadPool(3);

						if(MapManager.useThreads==true)
						{
								//incrementSpritePNGThreadsCreated_S();

								generatePNGExecutorService.execute
								(
									new Runnable()
									{

										public void run()
										{
											try{Thread.currentThread().setName("Sprite_createSpriteTexturePNG");}catch(SecurityException e){e.printStackTrace();}

											createSpriteTexturePNG_S();

											if(hasShadow()==true)createSpriteShadowTexturePNG_S();

											setSpritePNGFileExists_S(true);
											//decrementSpritePNGThreadsCreated_S();
										}
									}
								);

						}
						else
						{
							//do it linearly, waiting for all chunks to finish before continuing
							createSpriteTexturePNG_S();

							if(hasShadow()==true)createSpriteShadowTexturePNG_S();

							setSpritePNGFileExists_S(true);
						}
					}

				}





			}

		}

	}


	//=========================================================================================================================
	public int[] getReplacementRGBFromSet(int r, int g, int b, Sprite s, int set)
	{//=========================================================================================================================

		int[] rgb = null;


		int w = s.w()/2;

		for(int x = 0; x < w; x++)
		{
			int oldIndex = s.indexDataIntArray[x] & 0xFF;

			int oldR = s.paletteRGBByteArray[oldIndex*3+0] & 0xFF;
			int oldG = s.paletteRGBByteArray[oldIndex*3+1] & 0xFF;
			int oldB = s.paletteRGBByteArray[oldIndex*3+2] & 0xFF;

			if(r==oldR&&g==oldG&&b==oldB)
			{
				int newIndex = s.indexDataIntArray[(w * set) + x];

				rgb = new int[3];
				rgb[0] = s.paletteRGBByteArray[newIndex*3+0] & 0xFF;
				rgb[1] = s.paletteRGBByteArray[newIndex*3+1] & 0xFF;
				rgb[2] = s.paletteRGBByteArray[newIndex*3+2] & 0xFF;

				return rgb;
			}
		}

		return rgb;


	}

	//=========================================================================================================================
	public synchronized ByteBuffer createRandomSpriteTextureByteBuffer_S(int eyeSet, int skinSet, int hairSet, int shirtSet, int pantsSet, int shoeSet, int carSet)
	{//=========================================================================================================================


		int[] data = indexDataIntArray;
		byte[] pal = paletteRGBByteArray;




		//create bytebuffer


		//-----------------------------
		//allocate the indexed gfx data array, buffer, and texture
		//-----------------------------

		int imageWidth = w();
		int imageHeight = h() * frames();

		int texWidth=Utils.getClosestPowerOfTwo(imageWidth);
		int texHeight=Utils.getClosestPowerOfTwo(imageHeight);



		byte[] textureByteArray = new byte[texWidth*texHeight*4];

		//direct method, uses ram outside of the JVM
		ByteBuffer textureByteBuffer = ByteBuffer.allocateDirect(textureByteArray.length);
		textureByteBuffer.order(ByteOrder.nativeOrder());




		//for each pixel in data
			//check palette for this index
			//if it is 0, bytebuffer is clear
			//if it is black, bytebuffer is black

		int w = w()/2; //because width is widthHQ, which is floatd because we draw everything at 2x. actual width of data is width/2
		int h = h()/2;

		BufferedImage spriteBufferedImage = null;
		if(useHQ2X)spriteBufferedImage = new BufferedImage(w, h*frames(), BufferedImage.TYPE_INT_ARGB);
		else spriteBufferedImage = new BufferedImage(w*2, h*2*frames(), BufferedImage.TYPE_INT_ARGB);

		for(int f=0;f<frames();f++)
		for(int y=0;y<h;y++)
		for(int x=0;x<w;x++)
		{

			int r = 0;
			int g = 0;
			int b = 0;
			int a = 255;


			int index = data[(f*w*h)+y*w+x];// & 0xFF;


			if(index==0)a=0;//clear
			else
			if(index==1)//black
			{
				r=0;
				g=0;
				b=0;
			}
			else
			if(index==2)//white
			{
				r=255;
				g=255;
				b=255;
			}
			else
			{
				r = pal[index*3+0] & 0xFF;
				g = pal[index*3+1] & 0xFF;
				b = pal[index*3+2] & 0xFF;


				if(r!=g||g!=b)//skip gray colors, lots of hair is this color.
				{



					//TODO: need a standard amount of variations so i can randomly select one.

					//if this color is an eye color

					//get the correct replacement color.

					//dont need to get random stuff from the server. just put the MD5s straight into SpriteAssetList
					//then i can load the random color variations on program start



					//DONE: have these in memory on load.
					//random sprites should contain their own data and pal.

					int[] rgb = null;

					if(carSet!=-1)
					{
						rgb = getReplacementRGBFromSet(r,g,b,SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMcarColors"), carSet);

						if(rgb!=null){r=rgb[0];g=rgb[1];b=rgb[2];}

					}
					else
					{

						rgb = getReplacementRGBFromSet(r,g,b,SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMeyeColors"), eyeSet);

						if(rgb!=null){r=rgb[0];g=rgb[1];b=rgb[2];}
						else
						rgb = getReplacementRGBFromSet(r,g,b,SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMskinColors"), skinSet);

						if(rgb!=null){r=rgb[0];g=rgb[1];b=rgb[2];}
						else
						rgb = getReplacementRGBFromSet(r,g,b,SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMhairColors"), hairSet);

						if(rgb!=null){r=rgb[0];g=rgb[1];b=rgb[2];}
						else
						rgb = getReplacementRGBFromSet(r,g,b,SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshirtColors"), shirtSet);

						if(rgb!=null){r=rgb[0];g=rgb[1];b=rgb[2];}
						else
						rgb = getReplacementRGBFromSet(r,g,b,SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMpantsColors"), pantsSet);

						if(rgb!=null){r=rgb[0];g=rgb[1];b=rgb[2];}
						else
						rgb = getReplacementRGBFromSet(r,g,b,SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshoeColors"), shoeSet);

						if(rgb!=null){r=rgb[0];g=rgb[1];b=rgb[2];}
					}


				}

			}

			if(useHQ2X)spriteBufferedImage.setRGB(x, y+(f*h), new BobColor(r,g,b,a).getRGB());
			else
			{
				//now fill textureByteArray with this color
				for(int yy=0;yy<2;yy++)
				for(int xx=0;xx<2;xx++)
				{
					textureByteArray[(f*texWidth*h*2+((y*2 + yy)*texWidth + (x*2 + xx)))*4+0] = (byte)r;
					textureByteArray[(f*texWidth*h*2+((y*2 + yy)*texWidth + (x*2 + xx)))*4+1] = (byte)g;
					textureByteArray[(f*texWidth*h*2+((y*2 + yy)*texWidth + (x*2 + xx)))*4+2] = (byte)b;
					textureByteArray[(f*texWidth*h*2+((y*2 + yy)*texWidth + (x*2 + xx)))*4+3] = (byte)a;
				}
			}



		}

		if(useHQ2X)
		{


			BufferedImage hq2xSpriteBufferedImage = new HQ2X().hq2x(spriteBufferedImage);

			setHQ2XAlphaFromOriginal(hq2xSpriteBufferedImage,spriteBufferedImage);

			//spriteBufferedImage.flush();
			spriteBufferedImage=null;

			antialiasBufferedImage(hq2xSpriteBufferedImage);



			//now fill textureByteArray with this bufferedimage
			for(int y=0;y<imageHeight;y++)
			for(int x=0;x<imageWidth;x++)
			{
				BobColor c = new BobColor(hq2xSpriteBufferedImage.getRGB(x, y), true);

				textureByteArray[(y*texWidth+x)*4+0] = (byte)c.getRed();
				textureByteArray[(y*texWidth+x)*4+1] = (byte)c.getGreen();
				textureByteArray[(y*texWidth+x)*4+2] = (byte)c.getBlue();
				textureByteArray[(y*texWidth+x)*4+3] = (byte)c.getAlpha();
			}

			//hq2xSpriteBufferedImage.flush();
			hq2xSpriteBufferedImage=null;

			//make texture out of the bytebuffer


		}




		textureByteBuffer.put(textureByteArray);
		textureByteBuffer.flip();





		return textureByteBuffer;



	}


	//=========================================================================================================================
	public synchronized void createSpriteTexturePNG_S()
	{//=========================================================================================================================

		// construct texture
		// construct shadow texture (if hasShadow)


		int w = w()/2;
		int h = h()/2;


		//---------------------------
		//make bufferedimage the size of all sprite frames and fill it
		//---------------------------
		BufferedImage spriteBufferedImage = null;
		if(useHQ2X)spriteBufferedImage = new BufferedImage(w, h*frames(), BufferedImage.TYPE_INT_ARGB);
		else spriteBufferedImage = new BufferedImage(w*2, h*2*frames(), BufferedImage.TYPE_INT_ARGB);

		for(int f=0;f<frames();f++)
		for(int y=0;y<h;y++)
		for(int x=0;x<w;x++)
		{

			int r = 0;
			int g = 0;
			int b = 0;
			int a = 255;


			int index = indexDataIntArray[(f*w*h)+(y*w)+x];// & 0xFF;


			if(index==0)a=0;//clear
			else
			if(index==1)//black
			{
				r=0;
				g=0;
				b=0;
			}
			else
			if(index==2)//white
			{
				r=255;
				g=255;
				b=255;
			}
			else
			{
				r = paletteRGBByteArray[index*3+0] & 0xFF;
				g = paletteRGBByteArray[index*3+1] & 0xFF;
				b = paletteRGBByteArray[index*3+2] & 0xFF;

			}

			if(useHQ2X)spriteBufferedImage.setRGB(x, y+(f*h), new BobColor(r,g,b,a).getRGB());
			else
			{

				for(int yy=0;yy<2;yy++)
				for(int xx=0;xx<2;xx++)
				{
					spriteBufferedImage.setRGB(x*2+xx, y*2+yy+(f*h*2), new BobColor(r,g,b,a).getRGB());
				}
			}


		}

		if(useHQ2X)
		{

			BufferedImage hq2xSpriteBufferedImage = new HQ2X().hq2x(spriteBufferedImage);

			setHQ2XAlphaFromOriginal(hq2xSpriteBufferedImage,spriteBufferedImage);

			//spriteBufferedImage.flush();
			spriteBufferedImage=null;

			antialiasBufferedImage(hq2xSpriteBufferedImage);

			//---------------------------
			//save to png
			//---------------------------
			Utils.saveImage(""+Cache.cacheDir+"_"+dataMD5()+Cache.slash+"2x"+Cache.slash+dataMD5(), hq2xSpriteBufferedImage);

			//hq2xSpriteBufferedImage.flush();
			hq2xSpriteBufferedImage=null;
		}
		else
		{
			Utils.saveImage(""+Cache.cacheDir+"_"+dataMD5()+Cache.slash+"1x"+Cache.slash+dataMD5(), spriteBufferedImage);
		}



	}


	//=========================================================================================================================
	public synchronized void createSpriteShadowTexturePNG_S()
	{//=========================================================================================================================

		//---------------------------
		//write shadow frames
		//---------------------------


		int width = w()/2;
		int height = h()/2;


		BufferedImage spriteBufferedImage = null;
		if(useHQ2X)spriteBufferedImage = new BufferedImage(width, height * frames(), BufferedImage.TYPE_INT_ARGB);
		else spriteBufferedImage = new BufferedImage(width*2, height*2*frames(), BufferedImage.TYPE_INT_ARGB);

			for(int f = 0; f < frames(); f++)
			{
				for(int y = 0; y < height; y++)
				{
					for(int x = 0; x < width; x++)
					{

						int index = indexDataIntArray[(f*width*height)+y*width+x];// & 0xFF;

						if(index!=0)
						{

							int bottom_pixel_y=height-1;

							//find bottom pixel to start copying shadow from so feet are exactly at the top of the frame
							for(int yy=height-1;yy>=0;yy--)
								for(int xx=0;xx<width;xx++)
								{

									if((indexDataIntArray[(f*width*height)+yy*width+xx]/* & 0xFF*/)!=0)
									{
										bottom_pixel_y = yy;
										yy=-1;
										break;
									}
								}

							//since we're not copying from the bottom, we need to stop when we reach the top, not copy the full height
							if(bottom_pixel_y-y<0)
							{
								y=height;
								break;
							}

							int nx = x;
							int ny = (height * f) + ((bottom_pixel_y)-y);
							int col = BobColor.black.getRGB();

							if(useHQ2X)spriteBufferedImage.setRGB(nx, ny, col);
							else
							{

								for(int yy=0;yy<2;yy++)
								for(int xx=0;xx<2;xx++)
								{
									spriteBufferedImage.setRGB(nx*2+xx, ny*2+yy, col);
								}
							}
						}
					}
				}
			}

			if(useHQ2X)
			{
					BufferedImage hq2xShadowBufferedImage = new HQ2X().hq2x(spriteBufferedImage);

					setHQ2XAlphaFromOriginal(hq2xShadowBufferedImage,spriteBufferedImage);

					//spriteBufferedImage.flush();
					spriteBufferedImage=null;

					antialiasBufferedImage(hq2xShadowBufferedImage);

				//---------------------------
				//save to png
				//---------------------------

					Utils.saveImage(""+Cache.cacheDir+"_"+dataMD5()+Cache.slash+"2x"+Cache.slash+dataMD5()+"s", hq2xShadowBufferedImage);

					//hq2xShadowBufferedImage.flush();
					hq2xShadowBufferedImage=null;
			}
			else
			{
				Utils.saveImage(""+Cache.cacheDir+"_"+dataMD5()+Cache.slash+"1x"+Cache.slash+dataMD5()+"s", spriteBufferedImage);
			}

	}

	//=========================================================================================================================
	public synchronized void releaseSpriteTexture_S()
	{//=========================================================================================================================
		texture = GLUtils.releaseTexture(texture);
		shadowTexture = GLUtils.releaseTexture(shadowTexture);
	}

	public boolean _texturePNGExists = false;


//	public static int spriteTexturesLoaded = 0;
//	public static int spriteThreadsCreated = 0;
//	public static int maxSpriteThreadsCreated = 0;

	//=========================================================================================================================
	public synchronized boolean getSpritePNGFileExists_S()
	{//=========================================================================================================================
		return _texturePNGExists;

	}
	//=========================================================================================================================
	public synchronized void setSpritePNGFileExists_S(boolean done)
	{//=========================================================================================================================
		_texturePNGExists = done;
	}


//	//=========================================================================================================================
//	public void incrementSpriteTexturesLoaded()
//	{//=========================================================================================================================
//		spriteTexturesLoaded++;
//	}
//	//=========================================================================================================================
//	public void decrementSpriteTexturesLoaded()
//	{//=========================================================================================================================
//		spriteTexturesLoaded--;
//	}

//	//=========================================================================================================================
//	public synchronized void incrementSpritePNGThreadsCreated_S()
//	{//=========================================================================================================================
//		spriteThreadsCreated++;
//		if(spriteThreadsCreated>maxSpriteThreadsCreated)maxSpriteThreadsCreated=spriteThreadsCreated;
//	}
//
//	//=========================================================================================================================
//	public synchronized void decrementSpritePNGThreadsCreated_S()
//	{//=========================================================================================================================
//		spriteThreadsCreated--;
//	}


	//=========================================================================================================================
	public int getNumberOfAnimations()
	{//=========================================================================================================================
		return animationList().size();
	}


	//=========================================================================================================================
	public SpriteAnimationSequence getFirstAnimation()
	{//=========================================================================================================================
		//go through animationList

		if(animationList().size()>0)return getAnimationByFrame(0);//animationList().get(0);
		else
		{
			animationList().add(new SpriteAnimationSequence("Default", 0, 0, 0, 0, 0));
			log.warn("First animation sequence not found in SpriteAsset: "+name());
		}

		return animationList().get(0);

	}
	//=========================================================================================================================
	public SpriteAnimationSequence getAnimationByName(String name)
	{//=========================================================================================================================

		for(int i=0;i<animationList().size();i++)
		{
			if(animationList().get(i).frameSequenceName.equals(name))return animationList().get(i);
		}

		return null;

	}

	//=========================================================================================================================
	public SpriteAnimationSequence getAnimationByFrame(int frame)
	{//=========================================================================================================================


		if(animationList().size()==0)return null;

		SpriteAnimationSequence a = animationList().get(0);

		for(int i=0;i<animationList().size();i++)
		{
			SpriteAnimationSequence temp = animationList().get(i);
			if
			(
				temp.frameStart<=frame
				&&
				temp.frameStart>=a.frameStart
			)
			{
				a = temp;
			}
		}

		return a;

	}



	//=========================================================================================================================
	public SpriteAnimationSequence getAnimationByIndex(int index)
	{//=========================================================================================================================
		if(index<0||index>=animationList().size())return null;

		return animationList().get(index);

	}

	//=========================================================================================================================
	public int getAnimationNumFramesByIndex(int index)
	{//=========================================================================================================================
		SpriteAnimationSequence a = getAnimationByIndex(index);

		if(a==null)
		{
			log.error("Could not get animation by index in getAnimationNumFramesByIndex");
			new Exception().printStackTrace();
			return frames();
		}

		//get animation frames
		int endFrame = frames();

		for(int i=0;i<animationList().size();i++)
		{
			SpriteAnimationSequence temp = animationList().get(i);

			if(temp.frameStart>a.frameStart&&temp.frameStart<endFrame)
			endFrame = temp.frameStart;
		}

		return endFrame-a.frameStart;

	}

	//=========================================================================================================================
	public int getAnimationNumFramesByName(String name)
	{//=========================================================================================================================

		return getAnimationNumFramesByIndex(getAnimationIndexByName(name));

	}

	//=========================================================================================================================
	public int getAnimationNumFramesByFrame(int frame)
	{//=========================================================================================================================

		return getAnimationNumFramesByIndex(getAnimationIndexByFrame(frame));

	}
	//=========================================================================================================================
	public int getAnimationNumFramesByAnimation(SpriteAnimationSequence a)
	{//=========================================================================================================================

		return getAnimationNumFramesByIndex(getAnimationIndexByAnimation(a));

	}
	//=========================================================================================================================
	public int getAnimationIndexByName(String name)
	{//=========================================================================================================================

		if(animationList().size()==0)return -1;

		for(int i=0;i<animationList().size();i++)
		{
			if(animationList().get(i).frameSequenceName.equals(name)){return i;}
		}

		return -1;
	}

	//=========================================================================================================================
	public int getAnimationIndexByAnimation(SpriteAnimationSequence a)
	{//=========================================================================================================================
		if(animationList().size()==0)return -1;

		for(int i=0;i<animationList().size();i++)
		{
			if(animationList().get(i).equals(a)){return i;}
		}

		return -1;
	}



	//=========================================================================================================================
	public int getAnimationIndexByFrame(int frame)
	{//=========================================================================================================================

		return getAnimationIndexByAnimation(getAnimationByFrame(frame));
	}


	//=========================================================================================================================
	public String getAnimationNameByIndex(int index)
	{//=========================================================================================================================
		if(index<0||index>=animationList().size())return null;

		return animationList().get(index).frameSequenceName;

	}

	//=========================================================================================================================
	public String getAnimationNameByFrame(int frame)
	{//=========================================================================================================================

		return getAnimationNameByIndex(getAnimationIndexByFrame(frame));


	}













	//===============================================================================================
	public void antialiasBufferedImage(BufferedImage bufferedImage)
	{//===============================================================================================

		//go through hq2x image
		//if pixel is transparent, and the pixel right and down, down and left, left and up, or up and right are black, this one is black

		//have to make a copy otherwise the algorithm becomes recursive
		BufferedImage copy = new BufferedImage(bufferedImage.getWidth(), bufferedImage.getHeight(), BufferedImage.TYPE_INT_ARGB);
		for(int y = 0; y < bufferedImage.getHeight(); y++)
		{
			for(int x = 0; x < bufferedImage.getWidth(); x++)
			{
				copy.setRGB(x, y, bufferedImage.getRGB(x,y));
			}
		}

		int clear = new BobColor(0,0,0,0).getRGB();

		for(int y = 0; y < bufferedImage.getHeight(); y++)
		{
			for(int x = 0; x < bufferedImage.getWidth(); x++)
			{
				if(copy.getRGB(x, y)==clear)
				{
					int black=0;

					//check right and down
					if(x+1<bufferedImage.getWidth()&&y+1<bufferedImage.getHeight())
					{
						if(
								copy.getRGB(x+1, y)!=clear&&
								copy.getRGB(x, y+1)!=clear
						)
						black=1;
					}

					//check right and up
					if(x+1<bufferedImage.getWidth()&&y-1>=0)
					{
						if(
								copy.getRGB(x+1, y)!=clear&&
								copy.getRGB(x, y-1)!=clear
						)
						black=1;
					}


					//check left and down
					if(x-1>=0&&y+1<bufferedImage.getHeight())
					{
						if(
								copy.getRGB(x-1, y)!=clear&&
								copy.getRGB(x, y+1)!=clear
						)
						black=1;
					}

					//check left and up
					if(x-1>=0&&y-1>=0)
					{
						if(
								copy.getRGB(x-1, y)!=clear&&
								copy.getRGB(x, y-1)!=clear
						)
						black=1;
					}

					if(black==1)bufferedImage.setRGB(x, y, new BobColor(0,0,0,127).getRGB());
				}

			}
		}
	}

	//===============================================================================================
	public void setHQ2XAlphaFromOriginal(BufferedImage hq2xBufferedImage, BufferedImage bufferedImage)
	{//===============================================================================================
		//now go through original image again. take each transparent pixel and set the hq2x one with it at 2x
		for(int y = 0; y < bufferedImage.getHeight(); y++)
		{
			for(int x = 0; x < bufferedImage.getWidth(); x++)
			{
				if(bufferedImage.getRGB(x, y)==0)
				{
					for(int xx=0;xx<2;xx++)
					for(int yy=0;yy<2;yy++)
						hq2xBufferedImage.setRGB((x*2)+xx, ((y*2)+yy), new BobColor(0,0,0,0).getRGB());
				}

			}
		}
	}



	/*
	 *
	//===============================================================================================
	public void outputHQ2XPNG(String dirpath)
	{//===============================================================================================

		//---------------------------
		//create directory if doesn't exist
		//---------------------------
		if(dirpath==null)dirpath = System.getProperties().getProperty("user.home")+"\\Desktop\\bgEditor_Output\\";
		CacheManager.makeDir(dirpath + "png\\sprite\\");


		int w = (widthPixelsHQ/2);
		int h = (heightPixelsHQ/2);

		//---------------------------
		//make bufferedimage the size of all sprite frames and fill it
		//---------------------------
			//BufferedImage bufferedImage = (new Frame()).getGraphicsConfiguration().createCompatibleImage(width, (height) * num_Frames, Transparency.TRANSLUCENT);
			BufferedImage bufferedImage = new BufferedImage( w, h * frames, BufferedImage.TYPE_INT_ARGB);
			for(int f = 0; f < frames; f++)
			{
				for(int y = 0; y < h; y++)
				{
					for(int x = 0; x < w; x++)
					{
						if(getPixel(f, x, y)!=0)
						bufferedImage.setRGB(x, y + (h * f), (E.project.getSelectedSpritePalette().getColor(getPixel(f, x, y))).getRGB());
					}
				}
			}

			BufferedImage hq2xBufferedImage = new HQ2X().HQ2X(bufferedImage);

			setHQ2XAlphaFromOriginal(hq2xBufferedImage,bufferedImage);

			antialiasBufferedImage(hq2xBufferedImage);

			bufferedImage = hq2xBufferedImage;

		//---------------------------
		//save to png
		//---------------------------

			CacheManager.saveImage(dirpath + "png\\sprite\\" + name + "_Sprite_HQ2X_" + width*2 + "x" + height*2 + "x" + num_Frames + ".png",bufferedImage);


		//---------------------------
		//write shadow frames
		//---------------------------

			bufferedImage = new BufferedImage(width, height* num_Frames, BufferedImage.TYPE_INT_ARGB);
			for(int f = 0; f < num_Frames; f++)
			{
				for(int y = 0; y < height; y++)
				{
					for(int x = 0; x < width; x++)
					{
						if(getPixel(f, x, y)!=0)
						{

							int bottom_pixel_y=height-1;

							//find bottom pixel to start copying shadow from so feet are exactly at the top of the frame
							for(int yy=height-1;yy>=0;yy--)
								for(int xx=0;xx<width;xx++)
								{

									if(getPixel(f, xx, yy)!=0)
									{
										bottom_pixel_y = yy;
										yy=-1;
										break;
									}
								}

							//since we're not copying from the bottom, we need to stop when we reach the top, not copy the full height
							if(bottom_pixel_y-y<0)
							{
								y=height;
								break;
							}

							int nx = x;
							int ny = (height * f) + ((bottom_pixel_y)-y);
							int col = BobColor.black.getRGB();

							bufferedImage.setRGB(nx, ny, col);
						}
					}
				}
			}

			BufferedImage hq2xShadowBufferedImage = new HQ2X().HQ2X(bufferedImage);

			setHQ2XAlphaFromOriginal(hq2xShadowBufferedImage,bufferedImage);

			antialiasBufferedImage(hq2xShadowBufferedImage);

			bufferedImage = hq2xShadowBufferedImage;
		//---------------------------
		//save to png
		//---------------------------

			CacheManager.saveImage(dirpath + "png\\sprite\\" + name + "_SpriteShadow_HQ2X_" + width*2 + "x" + height*2 + "x" + num_Frames + ".png",bufferedImage);


	}
*/

	public SpriteData getData(){return data;}

	public int id(){return getData().id();}
	public String name(){return getData().name();}
	public String getTYPEIDString(){return getData().getTYPEIDString();}
	public String dataMD5(){return getData().dataMD5();}
	public String paletteMD5(){return getData().paletteMD5();}

	public String comment(){return getData().comment();}

	public int w(){return getData().widthPixelsHQ();}
	public int h(){return getData().heightPixelsHQ();}
	public int frames(){return getData().frames();}
	public String displayName(){return getData().displayName();}
	public boolean isNPC(){return getData().isNPC();}
	public boolean isKid(){return getData().isKid();}
	public boolean isAdult(){return getData().isAdult();}
	public boolean isMale(){return getData().isMale();}
	public boolean isFemale(){return getData().isFemale();}
	public boolean isCar(){return getData().isCar();}
	public boolean isAnimal(){return getData().isAnimal();}
	public boolean hasShadow(){return getData().hasShadow();}
	public boolean isRandom(){return getData().isRandom();}
	public boolean isDoor(){return getData().isDoor();}
	public boolean isGame(){return getData().isGame();}
	public boolean isItem(){return getData().isItem();}
	public boolean forceHQ2X(){return getData().forceHQ2X();}
	public boolean forceMD5Export(){return getData().forceMD5Export();}
	//public int eventID(){return getData().eventID();}

	public EventData eventData(){return getData().eventData();}
	public String itemGameDescription(){return getData().itemGameDescription();}
	public float gamePrice(){return getData().gamePrice();}
	public int utilityOffsetXPixelsHQ(){return getData().utilityOffsetXPixelsHQ();}
	public int utilityOffsetYPixelsHQ(){return getData().utilityOffsetYPixelsHQ();}
	public ArrayList<SpriteAnimationSequence> animationList(){return getData().animationList();}



//	public void setName(String s){getData().setName(s);}
//	public void setComment(String s){getData().setComment(s);}
//	public void setID(int s){getData().setID(s);}
//	public void setWidthPixels(int s){getData().setWidthPixels1X(s);}
//	public void setHeightPixels(int s){getData().setHeightPixels1X(s);}
//	public void setFrames(int s){getData().setFrames(s);}
//	public void setDisplayName(String s){getData().setDisplayName(s);}
//	public void setIsNPC(boolean s){getData().setIsNPC(s);}
//	public void setIsKid(boolean s){getData().setIsKid(s);}
//	public void setIsAdult(boolean s){getData().setIsAdult(s);}
//	public void setIsMale(boolean s){getData().setIsMale(s);}
//	public void setIsFemale(boolean s){getData().setIsFemale(s);}
//	public void setIsCar(boolean s){getData().setIsCar(s);}
//	public void setIsAnimal(boolean s){getData().setIsAnimal(s);}
//	public void setHasShadow(boolean s){getData().setHasShadow(s);}
//	public void setIsRandom(boolean s){getData().setIsRandom(s);}
//	public void setIsDoor(boolean s){getData().setIsDoor(s);}
//	public void setIsGame(boolean s){getData().setIsGame(s);}
//	public void setIsItem(boolean s){getData().setIsItem(s);}
//	public void setForceHQ2X(boolean s){getData().setForceHQ2X(s);}
//	public void setForceMD5Export(boolean s){getData().setForceMD5Export(s);}
//	public void setEventID(int s){getData().setEventID(s);}
//	public void setItemGameDescription(String s){getData().setItemGameDescription(s);}
//	public void setGamePrice(float s){getData().setGamePrice(s);}
//	public void setUtilityOffsetXPixels1X(int s){getData().setUtilityOffsetXPixels1X(s);}
//	public void setUtilityOffsetYPixels1X(int s){getData().setUtilityOffsetYPixels1X(s);}



}
