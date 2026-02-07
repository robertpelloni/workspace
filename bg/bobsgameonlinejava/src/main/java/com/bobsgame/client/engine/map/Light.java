package com.bobsgame.client.engine.map;

import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.File;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import static org.lwjgl.opengl.GL11.*;


import org.slf4j.LoggerFactory;

import com.bobsgame.client.Texture;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.Cache;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.entity.Entity;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.LightData;
import com.bobsgame.shared.Utils;
//=========================================================================================================================
public class Light extends Entity
{//=========================================================================================================================



	public static Logger log = (Logger) LoggerFactory.getLogger(Light.class);




	public static int NOT_DRAWN = 0;
	public static int DRAWING = 1;
	public static int OVERLAPS_SOMETHING=2;
	public static int DRAWN=3;


	public Texture texture = null;



	public int sortingState=0;



	//private LightData data;

	//TO DO: handle these

	//public int id = -1;
	//public String stateName = "";


	public boolean isScreenLight = false;


	//=========================================================================================================================
	/**
	 * This constructor is specifically for creating lights not bound to the map, but to the screen instead. The mapX and mapY coords will be used as screen coords.
	 */
	public Light(Engine g, String name, int mapXPixels1X, int mapYPixels1X, int widthPixels1X, int heightPixels1X, int red, int green, int blue, int alpha, int radiusPixels1X, float blendFalloff, float decayExponent, int focusRadius1X, boolean isDayLight, boolean isNightLight)
	{//=========================================================================================================================


		this(g, new LightData(-1,"","",name,mapXPixels1X,mapYPixels1X, widthPixels1X, heightPixels1X, red, green, blue, alpha, radiusPixels1X, blendFalloff, decayExponent, focusRadius1X, isDayLight, isNightLight, false, false, false, -1, -1, 0, 0, false, false), null);


		isScreenLight = true;


		if(getLightTexturePNGFileExists_S()==false)
		{
			File textureFile = new File(Cache.cacheDir+"l"+Cache.slash+getFileName());
			if(textureFile.exists())
			{
				setLightTexturePNGFileExists_S(true);
			}
			else
			{

				createLightTexturePNG(Cache.cacheDir+"l"+Cache.slash+getFileName());

				setLightTexturePNGFileExists_S(true);
			}
		}

		if(getLightTexturePNGFileExists_S()==true)
		{

			File textureFile = null;

			textureFile = new File(Cache.cacheDir+"l"+Cache.slash+getFileName());


			if(textureFile.exists()==false)
			{
				new Exception().printStackTrace();
			}


			Texture t = MapManager().lightTextureHashMap.get(getFileName());

			if(t==null)
			{
				t = GLUtils.loadTexture(Cache.cacheDir+"l"+Cache.slash+getFileName());

//				if(t==null || t==GLUtils.boxTexture)
//				{
//
//					log.error("Light graphic could not be created. Retrying...");
//
//					createLightTexturePNG(Cache.cacheDir+"l"+Cache.slash+getFileName());
//
//					try
//					{
//						Thread.sleep(500);
//					}
//					catch(InterruptedException e)
//					{
//						e.printStackTrace();
//					}
//
//					t = GLUtils.loadTexture(Cache.cacheDir+"l"+Cache.slash+getFileName());
//
//				}

				MapManager().lightTextureHashMap.put(getFileName(), t);
			}



			texture = t;
		}

	}

	//=========================================================================================================================
	public Light(Engine g, LightData lightAsset, Map m)
	{//=========================================================================================================================
		super(g);

		init(lightAsset, m);

		this.data = lightAsset;



		if(lightAsset.flickerRandomUpToOnTicks())onTicks=16+Utils.randUpToIncluding(lightAsset.flickerOnTicks())+Utils.randUpToIncluding(500);
		else onTicks=16+lightAsset.flickerOnTicks()+Utils.randUpToIncluding(500);
		if(lightAsset.flickerRandomUpToOffTicks())offTicks=16+Utils.randUpToIncluding(lightAsset.flickerOffTicks())+Utils.randUpToIncluding(500);
		else offTicks=16+lightAsset.flickerOffTicks()+Utils.randUpToIncluding(500);


		movementDirection=(Utils.randLessThan(8));

	}





























	public boolean flickerOnOffToggle=true;
	public int onTicks=0;
	public int offTicks=0;
	public long ticksCounter=0;
	public boolean toggleOnOffToggle=true;

	public boolean drawLightThisFrame=true;


	//===============================================================================================
	public void update()
	{//===============================================================================================

		setTicksPerPixelMoved(1);

		updateTimers();


		if(name().contains("mover"))
		{
			bounceAroundRoom();
		}




















		if(flickers())
		{
			ticksCounter+=Engine().engineTicksPassed();

			if(flickerOnOffToggle==true)
			{
				if(ticksCounter>=onTicks)
				{
					ticksCounter=0;
					flickerOnOffToggle=false;

					if(flickerRandomUpToOnTicks())onTicks=16+Utils.randUpToIncluding(flickerOnTicks());
					else onTicks=16+flickerOnTicks()+60+Utils.randUpToIncluding(50);
				}
			}
			else
			if(flickerOnOffToggle==false)
			{
				if(ticksCounter>=offTicks)
				{
					ticksCounter=0;
					flickerOnOffToggle=true;

					if(flickerRandomUpToOffTicks())offTicks=16+Utils.randUpToIncluding(flickerOffTicks());
					else offTicks=16+flickerOffTicks();
				}

			}
		}


		if(toggleable())
		{
			//if player is in toggle area and press action, set "toggleOnOffToggle" to false
			if(
					Player().right()>=toggleXPixelsHQ()&&
					Player().left()<toggleXPixelsHQ()+16&&
					Player().bottom()>=toggleYPixelsHQ()&&
					Player().top()<toggleYPixelsHQ()+16
			)
			{
				if(ControlsManager().BUTTON_ACTION_PRESSED)
				{
					toggle();
				}
			}

		}

		if(
			(toggleOnOffToggle==false)
			||
			(flickers()==true&&flickerOnOffToggle==false)
		)
		{
			drawLightThisFrame=false;
		}
		else
		{
			drawLightThisFrame=true;
		}

		if(MapManager().isNightTime()&&isNightLight()==false)
		{
			drawLightThisFrame=false;
		}

		if(MapManager().isDayTime()&&isDayLight()==false)
		{
			drawLightThisFrame=false;
		}






	}





	//===============================================================================================
	public void toggle()
	{//===============================================================================================
		toggleOnOffToggle = !toggleOnOffToggle;

	}

	//===============================================================================================
	public void setOnOff(boolean b)
	{//===============================================================================================
		toggleOnOffToggle = b;

	}

	//===============================================================================================
	public void setFlicker(boolean b)
	{//===============================================================================================
		setFlickers(b);

	}



	//===============================================================================================
	public synchronized void setLightTexturePNGFileExists_S(boolean exists)
	{//===============================================================================================
		//set hashmap for this filename, boolean exists
		boolean[] temp = new boolean[1];
		temp[0] = exists;
		MapManager().lightTextureFileExistsHashtable.put(getFileName(), temp);

	}

	//===============================================================================================
	public synchronized boolean getLightTexturePNGFileExists_S()
	{//===============================================================================================
		//first check the hashmap for the filename. if it exists, do nothing.
		boolean existsInHashtable = false;

		//this is an array because Hashtables only accept objects
		boolean[] fileExistsArray = MapManager().lightTextureFileExistsHashtable.get(getFileName());
		if(fileExistsArray!=null)existsInHashtable = fileExistsArray[0];

		return existsInHashtable;
	}

	//===============================================================================================
	public String getFileName()
	{//===============================================================================================

		return ""+w()/2+"_"+h()/2+"_"+radiusPixelsHQ()/2+"_"+focusRadiusPixelsHQ()/2+"_"+decayExponent()+"_"+blendFalloff()+"_"+r()+"_"+g()+"_"+b()+"_"+a();

	}




	//=========================================================================================================================
	public boolean checkEdgeAgainstHitLayerAndOtherLightsInDirection(int dir)
	{//=========================================================================================================================


		float myRight 	= middleX() + radiusPixelsHQ()/2;
		float myLeft 	= middleX() - radiusPixelsHQ()/2;

		float myTop 	= middleY() - radiusPixelsHQ()/2;
		float myBottom 	= middleY() + radiusPixelsHQ()/2;


		for(int i=0;i<getMap().currentState.lightList.size();i++)
		{
			Light l = getMap().currentState.lightList.get(i);
			if(l!=this&&l.name().equals(name())==false&&l.name().contains("mover"))
			{


				int r = 8+Utils.randLessThan(16);


				float theirRight 	= l.middleX() + l.radiusPixelsHQ()/2;
				float theirLeft 	= l.middleX() - l.radiusPixelsHQ()/2;
				float theirTop 		= l.middleY() - l.radiusPixelsHQ()/2;
				float theirBottom 	= l.middleY() + l.radiusPixelsHQ()/2;


				if(dir==UP)
				{
					if(
							middleX()<theirRight
							&&middleX()>theirLeft
							&&myBottom>theirTop
							&&myTop-r<=theirBottom
						)return true;
				}
				else
				if(dir==DOWN)
				{
					if(
							middleX()<theirRight
							&&middleX()>theirLeft
							&&myTop<theirBottom
							&&myBottom+r>=theirTop
						)return true;
				}
				else
				if(dir==LEFT)
				{
					if(
							myRight>theirLeft
							&&myLeft-r<=theirRight
							&&middleY()<theirBottom
							&&middleY()>theirTop
						)return true;
				}
				else
				if(dir==RIGHT)
				{
					if(
							myLeft<theirRight
							&&myRight+r>=theirLeft
							&&middleY()<theirBottom
							&&middleY()>theirTop
						)return true;
				}
			}
		}



		if(dir==UP)
		{
			if(getMap().getHitLayerValueAtXYPixels(middleX(),myTop-1)==true)return true;
			//if(getMap().getHitLayerValueAtXYPixels(left(),top()-1)==true)return true;
			//if(getMap().getHitLayerValueAtXYPixels(right(),top()-1)==true)return true;
		}
		else
		if(dir==DOWN)
		{
			if(getMap().getHitLayerValueAtXYPixels(middleX(),myBottom+1)==true)return true;
			//if(getMap().getHitLayerValueAtXYPixels(left(),bottom()+1)==true)return true;
			//if(getMap().getHitLayerValueAtXYPixels(right(),bottom()+1)==true)return true;
		}
		else
		if(dir==LEFT)
		{
			if(getMap().getHitLayerValueAtXYPixels(myLeft-1,middleY())==true)return true;
			//if(getMap().getHitLayerValueAtXYPixels(left()-1,top())==true)return true;
			//if(getMap().getHitLayerValueAtXYPixels(left()-1,bottom())==true)return true;
		}
		else
		if(dir==RIGHT)
		{
			if(getMap().getHitLayerValueAtXYPixels(myRight+1,middleY())==true)return true;
			//if(getMap().getHitLayerValueAtXYPixels(right()+1,top())==true)return true;
			//if(getMap().getHitLayerValueAtXYPixels(right()+1,bottom())==true)return true;
		}




		return false;
	}

	//=========================================================================================================================
	public void bounceAroundRoom()
	{//=========================================================================================================================





		while(pixelsToMoveThisFrame>1)
		{

			if(ifCanMoveAPixelThisFrameSubtractAndReturnTrue()==true)
			{



				if(movementDirection==UPLEFT)
				{
					if(checkEdgeAgainstHitLayerAndOtherLightsInDirection(UP)==false)movePixelInDirection(UP);
					else movementDirection=(Utils.randLessThan(8));

					if(checkEdgeAgainstHitLayerAndOtherLightsInDirection(LEFT)==false)movePixelInDirection(LEFT);
					else movementDirection=(Utils.randLessThan(8));

				}
				else
				if(movementDirection==UPRIGHT)
				{
					if(checkEdgeAgainstHitLayerAndOtherLightsInDirection(UP)==false)movePixelInDirection(UP);
					else movementDirection=(Utils.randLessThan(8));

					if(checkEdgeAgainstHitLayerAndOtherLightsInDirection(RIGHT)==false)movePixelInDirection(RIGHT);
					else movementDirection=(Utils.randLessThan(8));

				}
				else
				if(movementDirection==DOWNLEFT)
				{
					if(checkEdgeAgainstHitLayerAndOtherLightsInDirection(DOWN)==false)movePixelInDirection(DOWN);
					else movementDirection=(Utils.randLessThan(8));

					if(checkEdgeAgainstHitLayerAndOtherLightsInDirection(LEFT)==false)movePixelInDirection(LEFT);
					else movementDirection=(Utils.randLessThan(8));

				}
				else
				if(movementDirection==DOWNRIGHT)
				{
					if(checkEdgeAgainstHitLayerAndOtherLightsInDirection(DOWN)==false)movePixelInDirection(DOWN);
					else movementDirection=(Utils.randLessThan(8));

					if(checkEdgeAgainstHitLayerAndOtherLightsInDirection(RIGHT)==false)movePixelInDirection(RIGHT);
					else movementDirection=(Utils.randLessThan(8));

				}
				else
				{
					if(checkEdgeAgainstHitLayerAndOtherLightsInDirection(movementDirection)==false)movePixelInDirection(movementDirection);
					else movementDirection=(Utils.randLessThan(8));
				}

			}

		}

	}




	//=========================================================================================================================
	public boolean isOnScreen()
	{//=========================================================================================================================


		float zoom = Cameraman().getZoom();

		float left = screenLeft();
		float middleX = screenMiddleX();
		float right = screenRight();

		float top = screenTop();
		float middleY = screenMiddleY();
		float bottom = screenBottom();


		if(left>=Engine().getWidth())return false;
		if(right<0)return false;

		if(top>=Engine().getHeight())return false;
		if(bottom<0)return false;

		return true;
	}


	//=========================================================================================================================
	public void renderDebugBoxes()
	{//=========================================================================================================================

		if(isScreenLight==true)return;

		float zoom = Cameraman().getZoom();

		float screenX = getMap().screenX()*zoom+x()*zoom;
		float screenY = getMap().screenY()*zoom+y()*zoom;

		//inner width, height
		GLUtils.drawBox(screenX,screenX+w()*zoom,screenY,screenY+h()*zoom,0,0,0);


		//radius
		GLUtils.drawBox(screenLeft(),screenRight(),screenTop(),screenBottom(),150,150,0);

		if(toggleable())
		{
			//toggle point
			float ax=getMap().getScreenX(toggleXPixelsHQ(),16);
			float ay=getMap().getScreenY(toggleYPixelsHQ(),16);

			GLUtils.drawBox(ax,ax+(16*zoom)-1,ay,ay+(16*zoom)-1,0,0,255);

			GLUtils.drawLine(screenMiddleX(), screenMiddleY(), ax+(8*zoom), ay+(8*zoom), 255, 255, 255);
		}
	}

	//=========================================================================================================================
	public void render(float alpha)
	{//=========================================================================================================================
		//don't render as entity
	}

	//=========================================================================================================================
	public boolean renderLight()
	{//=========================================================================================================================

		return renderLight(screenLeft(),screenRight(),screenTop(),screenBottom(), 1.0f);
	}

	//=========================================================================================================================
	public boolean renderLight(float screenX0,float screenX1, float screenY0, float screenY1, float alpha)
	{//=========================================================================================================================


		if(Engine().lightsLayerEnabled==false)return false;

		if(drawLightThisFrame==false)return false;

		if(texture==null)return false;



		float left = screenX0;
		float right = screenX1;
		float middleX = screenX0 + ((screenX1-screenX0)/2);


		float top = screenY0;
		float bottom = screenY1;
		float middleY = screenY0 + ((screenY1-screenY0)/2);


		if(left>=Engine().getWidth())return false;
		if(right<0)return false;

		if(top>=Engine().getHeight())return false;
		if(bottom<0)return false;

		float totalWidth = (w()/2)/2+(radiusPixelsHQ()/2);
		float totalHeight = (h()/2)/2+(radiusPixelsHQ()/2);

		float tx0 = 0.0f;
		float tx1 = ((float)totalWidth)/((float)texture.getTextureWidth());
		float ty0 = 0.0f;
		float ty1 = ((float)totalHeight)/((float)texture.getTextureHeight());


		float x0;
		float x1;
		float y0;
		float y1;


		glBindTexture(GL_TEXTURE_2D, texture.getTextureID());

		//lower right quadrant (default)

		x0 = middleX;
		x1 = right;

		y0 = middleY;
		y1 = bottom;


		//GL.drawTexture(l.texture,l.red, l.green, l.blue, tx0, tx1, ty0, ty1, x0, x1, y0, y1, 1.0f, GLUtils.FILTER_LINEAR);
		GLUtils.drawTexture(tx0, tx1, ty0, ty1, x0, x1, y0, y1, alpha, GLUtils.FILTER_LINEAR);


		//lower left

		x0 = left;
		x1 = middleX;

		y0 = middleY;
		y1 = bottom;

		//GL.drawTexture(l.texture,l.red, l.green, l.blue, tx1, tx0, ty0, ty1, x0, x1, y0, y1, 1.0f, GLUtils.FILTER_LINEAR);
		GLUtils.drawTexture(tx1, tx0, ty0, ty1, x0, x1, y0, y1, alpha, GLUtils.FILTER_LINEAR);



		//upper left quadrant (default)

		x0 = left;
		x1 = middleX;

		y0 = top;
		y1 = middleY;

		//GL.drawTexture(l.texture,l.red, l.green, l.blue, tx1, tx0, ty1, ty0, x0, x1, y0, y1, 1.0f, GLUtils.FILTER_LINEAR);
		GLUtils.drawTexture(tx1, tx0, ty1, ty0, x0, x1, y0, y1, alpha, GLUtils.FILTER_LINEAR);


		//upper right quadrant

		x0 = middleX;
		x1 = right;

		y0 = top;
		y1 = middleY;

		//GL.drawTexture(l.texture,l.red, l.green, l.blue, tx0, tx1, ty1, ty0, x0, x1, y0, y1, 1.0f, GLUtils.FILTER_LINEAR);
		GLUtils.drawTexture(tx0, tx1, ty1, ty0, x0, x1, y0, y1, alpha, GLUtils.FILTER_LINEAR);

		return true;

	}


	//===============================================================================================
	public void createLightTexturePNG(String fileName)
	{//===============================================================================================

		//Thread.yield();

		int maxBrightness=a();

		int lightBoxWidth=(int)(w()/2);
		int lightBoxHeight=(int)(h()/2);

		int maxRadius=(int)(radiusPixelsHQ()/2);

		//int red = 255;
		//int green = 255;
		//int blue = 255;

		//decay exponent 1.0f = even decay from max to 0
		//decay exponent 0.5 = decays 0.5 as fast until 0.5, then decays 1.5 to radius
		//decay exponent 1.5 = decays 1.5 as fast until 0.5, then decays 0.5 to radius
		//decay exponent 1.7 = decays 1.7 as fast until 0.7, then decays 0.3 to radius
		//decay exponent 0.1 = decays 0.1 as fast until 0.9, then decays 1.9 to radius
		//decay at 1.5 until decayRadius, then decay from there to edge normally
		//we want to multiply by decayexponent until decayradius, then from decayradius to radius we want to multiply by inverse

		// O-----)----)
		//   150%  50%

		//instead i'll just use it as an exponent :P

		//float decayExponent = decayExponent;
		float focusRadius = (focusRadiusPixelsHQ()/2);

		int lightBoxX=maxRadius;
		int lightBoxY=maxRadius;

		int centerX = 0;//lightBoxX+lightBoxWidth/2;
		int centerY = 0;//lightBoxY+lightBoxHeight/2;

		BufferedImage lightImage = new BufferedImage(maxRadius+lightBoxWidth/2,maxRadius+lightBoxHeight/2,BufferedImage.TYPE_INT_ARGB);

		Graphics lightImageGraphics = lightImage.getGraphics();

		float distanceFromBoxEdgeToXY=0;
		float totalDistanceFromCenterToXY = 0;

		//get the angle of the corner of the light box
		float cornerAngle = (float)Math.atan((float)(lightBoxWidth/2)/(float)(lightBoxHeight/2));

		float maxDistFromBox = maxRadius;

		//float maxDistFromCenter = maxRadius+lightBoxWidth/2;
		//if(lightBoxWidth>lightBoxHeight)maxDistFromCenter = maxRadius+lightBoxHeight/2;


		//if focusradius!=0
		//fade into focusradius from center, fade out

		if(focusRadius!=0)
		{

			int xFromCenter=0;
			int yFromCenter=0;

			for(xFromCenter=0;xFromCenter<maxRadius+lightBoxWidth/2;xFromCenter++)
			for(yFromCenter=0;yFromCenter<maxRadius+lightBoxHeight/2;yFromCenter++)
			{
				if(xFromCenter==0)totalDistanceFromCenterToXY=yFromCenter;
				else if(yFromCenter==0)totalDistanceFromCenterToXY=xFromCenter;
				else totalDistanceFromCenterToXY = (float)Math.hypot(yFromCenter, xFromCenter);

				float distanceFromFocusRadius = Math.abs(focusRadius - totalDistanceFromCenterToXY);

				int alpha = 0;

				//if x<=focusRadius && y<=focusRadius, calculate color distance from center to xy/center to focusdistance
				//else calculate color on distance from focusradius
				if(totalDistanceFromCenterToXY<=focusRadius)
				{
					if(totalDistanceFromCenterToXY<=focusRadius/2)
					{
						//fade from maxBrightness to maxBrightness/2 based on distance to focusRadius/2
						alpha = (int)(((float)maxBrightness/3)-(((totalDistanceFromCenterToXY/(focusRadius))*((float)maxBrightness/3)))+(2*((float)maxBrightness/3)));
						if(alpha>255)alpha=255;
						if(alpha<0)alpha=0;
					}
					else
					{
						alpha = (int)((((totalDistanceFromCenterToXY/(focusRadius))*((float)maxBrightness/3)))+(2*((float)maxBrightness/3)));
						if(alpha>255)alpha=255;
						if(alpha<0)alpha=0;
					}
				}
				else
				{

					alpha = maxBrightness-(int)(Math.pow((distanceFromFocusRadius/(maxRadius-focusRadius)),1.0f/decayExponent())*(float)maxBrightness);
					if(alpha>255)alpha=255;
					if(alpha<0)alpha=0;
				}

				lightImageGraphics.setColor(new BobColor(r(),g(),b(),alpha));
				//set pixel
				lightImageGraphics.fillRect((centerX+xFromCenter),(centerY+yFromCenter),1,1);
				//lightImageGraphics.fillRect(((centerX-1)-xFromCenter),(centerY+yFromCenter),1,1);
				//lightImageGraphics.fillRect((centerX+xFromCenter),((centerY-1)-yFromCenter),1,1);
				//lightImageGraphics.fillRect(((centerX-1)-xFromCenter),((centerY-1)-yFromCenter),1,1);
			}


		}
		else
		{
			lightImageGraphics.setColor(new BobColor(r(),g(),b(),maxBrightness));
			//lightImageGraphics.fillRect(lightBoxX, lightBoxY, lightBoxWidth, lightBoxHeight);
			lightImageGraphics.fillRect(centerX, centerY, lightBoxWidth/2, lightBoxHeight/2);

			int xFromCenter=0;
			int yFromCenter=0;

			for(xFromCenter=1;xFromCenter<maxRadius+lightBoxWidth/2;xFromCenter++)
			for(yFromCenter=1;yFromCenter<maxRadius+lightBoxHeight/2;yFromCenter++)
			{

				if(xFromCenter>=lightBoxWidth/2||yFromCenter>=lightBoxHeight/2)
				{

					//get angle from center of box to x,y

					float angle;
					float distanceFromCenterToBoxEdge;
					float adjacent=0;


					//if the angle of xy is greater than this, have to use adjacent boxwidth
					//if it's exactly the angle, it doesnt matter which
					angle = (float)Math.atan((float)xFromCenter/(float)yFromCenter);
					if(angle<cornerAngle)
					{
						adjacent = lightBoxHeight/2;

						//get hypotenuse of angle, box width
						//adjacent/hypotenuse = cos(alpha)
						//adjacent = cos(alpha)*hypot
						//adjacent/cos(alpha) = hypot
						distanceFromCenterToBoxEdge = adjacent/(float)Math.cos(angle);

						totalDistanceFromCenterToXY = (float)Math.hypot(yFromCenter, xFromCenter);
						//dist to x,y - hypotenuse length = dist from edge of box to x,y
						distanceFromBoxEdgeToXY = (totalDistanceFromCenterToXY-(distanceFromCenterToBoxEdge));
					}
					//else adjacent boxheight
					else
					{
						angle = (float)Math.atan((float)yFromCenter/(float)xFromCenter);

						adjacent=lightBoxWidth/2;

						//get hypotenuse of angle, box width
						//adjacent/hypotenuse = cos(alpha)
						//adjacent = cos(alpha)*hypot
						//adjacent/cos(alpha) = hypot
						distanceFromCenterToBoxEdge = adjacent/(float)Math.cos(angle);

						totalDistanceFromCenterToXY = (float)Math.hypot(xFromCenter, yFromCenter);
						//dist to x,y - hypotenuse length = dist from edge of box to x,y
						distanceFromBoxEdgeToXY = (totalDistanceFromCenterToXY-(distanceFromCenterToBoxEdge));
					}



					//log.debug("X: "+xFromCenter+" | Y: "+yFromCenter);
					//log.debug("Angle from center to x,y (radians): "+angle+" | Degrees: "+Math.toDegrees(angle));
					//log.debug("Distance to edge of box from center: "+distanceToEdgeFromCenter);

					if(distanceFromBoxEdgeToXY<=maxDistFromBox)
					{


						//int alpha = maxBrightness-(int)((((d/maxDistFromBox)*maxRadius)/(float)maxRadius)*(float)maxBrightness);

						int alpha = maxBrightness-(int)(Math.pow((distanceFromBoxEdgeToXY/maxDistFromBox),1.0f/decayExponent())*(float)maxBrightness);


						if(alpha>255||alpha<0)lightImageGraphics.setColor(new BobColor(255,0,255,255));
						else
						//set color
						lightImageGraphics.setColor(new BobColor(r(),g(),b(),alpha));
						//set pixel
						lightImageGraphics.fillRect((centerX+xFromCenter),(centerY+yFromCenter),1,1);
						//lightImageGraphics.fillRect(((centerX-1)-xFromCenter),(centerY+yFromCenter),1,1);
						//lightImageGraphics.fillRect((centerX+xFromCenter),((centerY-1)-yFromCenter),1,1);
						//lightImageGraphics.fillRect(((centerX-1)-xFromCenter),((centerY-1)-yFromCenter),1,1);
					}
				}

			}

			yFromCenter=0;
			for(xFromCenter=(lightBoxWidth/2);xFromCenter<maxRadius+lightBoxWidth/2;xFromCenter++)
			{
				distanceFromBoxEdgeToXY=xFromCenter-((lightBoxWidth/2));

				totalDistanceFromCenterToXY = xFromCenter;

				//int alpha = maxBrightness-(int)((((distanceFromBoxEdgeToXY/maxDistFromBox)*maxRadius)/(float)maxRadius)*(float)maxBrightness);
				int alpha = maxBrightness-(int)(Math.pow((distanceFromBoxEdgeToXY/maxDistFromBox),1.0f/decayExponent())*(float)maxBrightness);

				if(alpha>255)lightImageGraphics.setColor(new BobColor(255,0,255,255));
				else
				lightImageGraphics.setColor(new BobColor(r(),g(),b(),alpha));
				lightImageGraphics.fillRect((centerX+xFromCenter),(centerY+yFromCenter),1,1);
				//lightImageGraphics.fillRect(((centerX-1)-xFromCenter),(centerY+yFromCenter),1,1);
				//lightImageGraphics.fillRect((centerX+xFromCenter),((centerY-1)+yFromCenter),1,1);
				//lightImageGraphics.fillRect(((centerX-1)-xFromCenter),((centerY-1)+yFromCenter),1,1);
			}

			xFromCenter=0;
			for(yFromCenter=(lightBoxHeight/2);yFromCenter<maxRadius+lightBoxHeight/2;yFromCenter++)
			{
				distanceFromBoxEdgeToXY=yFromCenter-((lightBoxHeight/2));
				if(distanceFromBoxEdgeToXY>maxDistFromBox)distanceFromBoxEdgeToXY=maxDistFromBox;

				totalDistanceFromCenterToXY = yFromCenter;

				//int alpha = maxBrightness-(int)((((distanceFromBoxEdgeToXY/maxDistFromBox)*maxRadius)/(float)maxRadius)*(float)maxBrightness);
				int alpha = maxBrightness-(int)(Math.pow((distanceFromBoxEdgeToXY/maxDistFromBox),1.0f/decayExponent())*(float)maxBrightness);


				if(alpha>255)lightImageGraphics.setColor(new BobColor(255,0,255,255));
				else
				lightImageGraphics.setColor(new BobColor(r(),g(),b(),alpha));
				lightImageGraphics.fillRect((centerX+xFromCenter),(centerY+yFromCenter),1,1);
				//lightImageGraphics.fillRect((centerX+xFromCenter),((centerY-1)-yFromCenter),1,1);
				//lightImageGraphics.fillRect(((centerX-1)+xFromCenter),(centerY+yFromCenter),1,1);
				//lightImageGraphics.fillRect(((centerX-1)+xFromCenter),((centerY-1)-yFromCenter),1,1);
			}
		}

		lightImageGraphics.dispose();
		lightImageGraphics = null;


		/*
		try
		{
			texture = InternalTextureLoader.get().getTexture((ImageData)new BufferedImageData(lightImage),GL_NEAREST);
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		*/

		Utils.saveImage(fileName, lightImage);

		lightImage.flush();
		lightImage = null;

		//System.runFinalization();
		//System.gc();

		//fill alpha native bytebuffer with lightImage.getRGB
		//create alpha texture id
		//send the bytebuffer into the texture

		//set texture to texture id


		//light[i].bufferedImage = lightImage;

		//now save the light to the cache, flush the lightimage, and load it as alpha texture.
		//then figure out how to blend it with alpha shader

	}





	//===============================================================================================
	public float left()
	{//===============================================================================================
		return x()-radiusPixelsHQ();
	}
	//===============================================================================================
	public float right()
	{//===============================================================================================
		return x() + w() + radiusPixelsHQ();
	}
	//===============================================================================================
	public float top()
	{//===============================================================================================
		return y()-radiusPixelsHQ();
	}
	//===============================================================================================
	public float bottom()
	{//===============================================================================================
		return y() + h() + radiusPixelsHQ();
	}




	//===============================================================================================
	public float screenLeft()
	{//===============================================================================================
		if(isScreenLight==true)return left();

		float zoom = Cameraman().getZoom();

		return (getMap().screenX()*zoom+x()*zoom-radiusPixelsHQ()*zoom);
	}
	//===============================================================================================
	public float screenRight()
	{//===============================================================================================
		if(isScreenLight==true)return right();

		float zoom = Cameraman().getZoom();

		return (getMap().screenX()*zoom+x()*zoom+((w())*zoom)+radiusPixelsHQ()*zoom);
	}
	//===============================================================================================
	public float screenTop()
	{//===============================================================================================
		if(isScreenLight==true)return top();

		float zoom = Cameraman().getZoom();

		return (getMap().screenY()*zoom+y()*zoom-radiusPixelsHQ()*zoom);
	}
	//===============================================================================================
	public float screenBottom()
	{//===============================================================================================
		if(isScreenLight==true)return bottom();

		float zoom = Cameraman().getZoom();

		return (getMap().screenY()*zoom+y()*zoom+((h())*zoom)+radiusPixelsHQ()*zoom);
	}
	//===============================================================================================
	public float screenMiddleX()
	{//===============================================================================================
		if(isScreenLight==true)return x()+((w()/2));

		float zoom = Cameraman().getZoom();

		return (getMap().screenX()*zoom+x()*zoom+((w()/2)*zoom));
	}
	//===============================================================================================
	public float screenMiddleY()
	{//===============================================================================================
		if(isScreenLight==true)return y()+((h()/2));

		float zoom = Cameraman().getZoom();

		return (getMap().screenY()*zoom+y()*zoom+((h()/2)*zoom));
	}




	//=========================================================================================================================
	public final float hitBoxFromLeft()
	{//=========================================================================================================================
		return 0;
	}
	//=========================================================================================================================
	public final float hitBoxFromRight()
	{//=========================================================================================================================
		return 0;
	}
	//=========================================================================================================================
	public final float hitBoxFromTop()
	{//=========================================================================================================================
		return 0;
	}
	//=========================================================================================================================
	public final float hitBoxFromBottom()
	{//=========================================================================================================================
		return 0;
	}




	public LightData getData(){return (LightData)data;}




	public float w(){return getData().widthPixelsHQ();}
	public float h(){return getData().heightPixelsHQ();}


	public int radiusPixelsHQ(){return getData().radiusPixelsHQ();}
	public int focusRadiusPixelsHQ(){return getData().focusRadiusPixelsHQ();}
	public int toggleXPixelsHQ(){return getData().toggleXPixelsHQ();}
	public int toggleYPixelsHQ(){return getData().toggleYPixelsHQ();}

	public int redColorByte(){return getData().redColorByte();}
	public int greenColorByte(){return getData().greenColorByte();}
	public int blueColorByte(){return getData().blueColorByte();}
	public int alphaColorByte(){return getData().alphaColorByte();}

	public int r(){return getData().redColorByte();}
	public int g(){return getData().greenColorByte();}
	public int b(){return getData().blueColorByte();}
	public int a(){return getData().alphaColorByte();}

	public float blendFalloff(){return getData().blendFalloff();}
	public float decayExponent(){return getData().decayExponent();}
	public boolean isDayLight(){return getData().isDayLight();}
	public boolean isNightLight(){return getData().isNightLight();}
	public boolean flickers(){return getData().flickers();}
	public boolean changesColor(){return getData().changesColor();}
	public boolean toggleable(){return getData().toggleable();}
	public int flickerOnTicks(){return getData().flickerOnTicks();}
	public int flickerOffTicks(){return getData().flickerOffTicks();}
	public boolean flickerRandomUpToOnTicks(){return getData().flickerRandomUpToOnTicks();}
	public boolean flickerRandomUpToOffTicks(){return getData().flickerRandomUpToOffTicks();}

	//public String getTYPEIDString(){return getData().getTYPEIDString();}








	//set

	public void setWidthPixels(int s){getData().setWidthPixels1X(s);}
	public void setHeightPixels(int s){getData().setHeightPixels1X(s);}
	public void setRadiusPixels(int s){getData().setRadiusPixels1X(s);}
	public void setFocusRadiusPixels(int s){getData().setFocusRadiusPixels1X(s);}
	public void setToggleXPixels(int s){getData().setToggleXPixels1X(s);}
	public void setToggleYPixels(int s){getData().setToggleYPixels1X(s);}

	public void setRedColorByte(int s){getData().setRedColorByte(s);}
	public void setGreenColorByte(int s){getData().setGreenColorByte(s);}
	public void setBlueColorByte(int s){getData().setBlueColorByte(s);}
	public void setAlphaColorByte(int s){getData().setAlphaColorByte(s);}


	public void setBlendFalloff(float s){getData().setBlendFalloff(s);}
	public void setDecayExponent(float s){getData().setDecayExponent(s);}
	public void setIsDayLight(boolean s){getData().setIsDayLight(s);}
	public void setIsNightLight(boolean s){getData().setIsNightLight(s);}
	public void setFlickers(boolean s){getData().setFlickers(s);}
	public void setChangesColor(boolean s){getData().setChangesColor(s);}
	public void setToggleable(boolean s){getData().setToggleable(s);}
	public void setFlickerOnTicks(int s){getData().setFlickerOnTicks(s);}
	public void setFlickerOffTicks(int s){getData().setFlickerOffTicks(s);}
	public void setFlickerRandomUpToOnTicks(boolean s){getData().setFlickerRandomUpToOnTicks(s);}
	public void setFlickerRandomUpToOffTicks(boolean s){getData().setFlickerRandomUpToOffTicks(s);}







}
