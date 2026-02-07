package com.bobsgame.editor.Project.Map;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.util.ArrayList;

import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Event.Event;
import com.bobsgame.shared.EntityData;
import com.bobsgame.shared.LightData;


//===============================================================================================
public class Light implements GameMapObject
{//===============================================================================================




	//public Color color = new Color(0,0,0,0);
	public BufferedImage bufferedImage = null;


	//dont export
	private Map map = null; //this isn't really used anywhere except in renaming the light below
	private MapState state = null;


	private LightData data;

	//===============================================================================================
	public Light(Map map, MapState state)
	{//===============================================================================================


		int id = getBiggestID();

		this.data = new LightData(id,"Light"+id);

		this.setMap(map);
		this.setState(state);

		if(this.state.getData().lightDataList().contains(this.data)==false)this.state.getData().lightDataList().add(this.data);

		Project.lightIndexList.add(this);
		Project.lightIndexHashtable.put(getTYPEIDString(),this);




	}



	//===============================================================================================
	public Light(Map map, MapState state, LightData data)
	{//===============================================================================================

		this.data = data;


		this.setMap(map);
		this.setState(state);


		if(data.eventData()!=null)data.setEventData(null); //TODO: hack to fix lights getting initialized with event 0


		if(Project.lightIndexHashtable.get(getTYPEIDString())!=null)
		{
			System.err.println("Light ID for Light: "+name()+" already exists. Creating new ID.");
			int id = getBiggestID();
			setID(id);
		}

		Project.lightIndexList.add(this);
		Project.lightIndexHashtable.put(getTYPEIDString(),this);

	}



	//===============================================================================================
	public int getBiggestID()
	{//===============================================================================================
		int id = -1;

		int size=Project.lightIndexList.size();
		if(size==0)id=0;
		else
		{
			int biggest=0;
			for(int i=0;i<size;i++)
			{
				int testid = Project.lightIndexList.get(i).id();
				if(testid>biggest)biggest=testid;
			}
			id=biggest+1;
		}
		return id;

	}



	public Map map(){return map;}
	public void setMap(Map map)
	{
		this.map=map;
		//data.setMapID(map.id());
	}

	public MapState state(){return state;}
	public void setState(MapState state)
	{
		this.state=state;
		//data.setStateID(state.id());
	}


	public LightData getData(){return data;}
	public String name(){return data.name();}
	public String comment(){return data.comment();}
	public int id(){return data.id();}

	public int xP(){return (int)data.spawnXPixels1X();}
	public int yP(){return (int)data.spawnYPixels1X();}
	public int xT(){return (int)data.spawnXPixels1X()/8;}
	public int yT(){return (int)data.spawnYPixels1X()/8;}

	public int wP(){return data.widthPixels1X();}
	public int hP(){return data.heightPixels1X();}
	public int wT(){return data.widthPixels1X()/8;}
	public int hT(){return data.heightPixels1X()/8;}

	public int radiusPixels1X(){return data.radiusPixels1X();}
	public int focusRadiusPixels1X(){return data.focusRadiusPixels1X();}
	public int toggleXPixels1X(){return data.toggleXPixels1X();}
	public int toggleYPixels1X(){return data.toggleYPixels1X();}

	public int redColorByte(){return data.redColorByte();}
	public int greenColorByte(){return data.greenColorByte();}
	public int blueColorByte(){return data.blueColorByte();}
	public int alphaColorByte(){return data.alphaColorByte();}

	public float blendFalloff(){return data.blendFalloff();}
	public float decayExponent(){return data.decayExponent();}
	public boolean isDayLight(){return data.isDayLight();}
	public boolean isNightLight(){return data.isNightLight();}
	public boolean flickers(){return data.flickers();}
	public boolean changesColor(){return data.changesColor();}
	public boolean toggleable(){return data.toggleable();}
	public int flickerOnTicks(){return data.flickerOnTicks();}
	public int flickerOffTicks(){return data.flickerOffTicks();}
	public boolean flickerRandomUpToOnTicks(){return data.flickerRandomUpToOnTicks();}
	public boolean flickerRandomUpToOffTicks(){return data.flickerRandomUpToOffTicks();}

	public String getTYPEIDString(){return data.getTYPEIDString();}








	//set
	public void setID(int s){data.setID(s);}
	public void setComment(String s){data.setComment(s);}

	public void setXPixels(float s){data.setSpawnXPixels1X(s);}
	public void setYPixels(float s){data.setSpawnYPixels1X(s);}

	public void setWidthPixels(int s){data.setWidthPixels1X(s);}
	public void setHeightPixels(int s){data.setHeightPixels1X(s);}
	public void setRadiusPixels(int s){data.setRadiusPixels1X(s);}
	public void setFocusRadiusPixels(int s){data.setFocusRadiusPixels1X(s);}
	public void setToggleXPixels(int s){data.setToggleXPixels1X(s);}
	public void setToggleYPixels(int s){data.setToggleYPixels1X(s);}

	public void setRedColorByte(int s){data.setRedColorByte(s);}
	public void setGreenColorByte(int s){data.setGreenColorByte(s);}
	public void setBlueColorByte(int s){data.setBlueColorByte(s);}
	public void setAlphaColorByte(int s){data.setAlphaColorByte(s);}


	public void setBlendFalloff(float s){data.setBlendFalloff(s);}
	public void setDecayExponent(float s){data.setDecayExponent(s);}
	public void setIsDayLight(boolean s){data.setIsDayLight(s);}
	public void setIsNightLight(boolean s){data.setIsNightLight(s);}
	public void setFlickers(boolean s){data.setFlickers(s);}
	public void setChangesColor(boolean s){data.setChangesColor(s);}
	public void setToggleable(boolean s){data.setToggleable(s);}
	public void setFlickerOnTicks(int s){data.setFlickerOnTicks(s);}
	public void setFlickerOffTicks(int s){data.setFlickerOffTicks(s);}
	public void setFlickerRandomUpToOnTicks(boolean s){data.setFlickerRandomUpToOnTicks(s);}
	public void setFlickerRandomUpToOffTicks(boolean s){data.setFlickerRandomUpToOffTicks(s);}











	//===============================================================================================
	public void createLightImage()
	{//===============================================================================================


		int r=redColorByte();
		int g=greenColorByte();
		int b=blueColorByte();
		int maxBrightness=alphaColorByte();

		int lightBoxWidth=wP();
		int lightBoxHeight=hP();

		int maxRadius=radiusPixels1X();

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

		float decayExponent = decayExponent();
		int focusRadius = focusRadiusPixels1X();

		int lightBoxX=maxRadius;
		int lightBoxY=maxRadius;

		int centerX = lightBoxX+lightBoxWidth/2;
		int centerY = lightBoxY+lightBoxHeight/2;

		BufferedImage lightImage = new BufferedImage(maxRadius*2+lightBoxWidth,maxRadius*2+lightBoxHeight,BufferedImage.TYPE_INT_ARGB);

		Graphics lightImageGraphics = lightImage.getGraphics();

		float distanceFromBoxEdgeToXY=0;
		float totalDistanceFromCenterToXY = 0;

		//get the angle of the corner of the light box
		float cornerAngle = (float)Math.atan((lightBoxWidth/2)/(lightBoxHeight/2));

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

					alpha = maxBrightness-(int)(Math.pow((distanceFromFocusRadius/(maxRadius-focusRadius)),1.0f/decayExponent)*(float)maxBrightness);
					if(alpha>255)alpha=255;
					if(alpha<0)alpha=0;
				}

				lightImageGraphics.setColor(new Color(r,g,b,alpha));
				//set pixel
				lightImageGraphics.fillRect((centerX+xFromCenter),(centerY+yFromCenter),1,1);
				lightImageGraphics.fillRect(((centerX-1)-xFromCenter),(centerY+yFromCenter),1,1);
				lightImageGraphics.fillRect((centerX+xFromCenter),((centerY-1)-yFromCenter),1,1);
				lightImageGraphics.fillRect(((centerX-1)-xFromCenter),((centerY-1)-yFromCenter),1,1);
			}


		}
		else
		{
			lightImageGraphics.setColor(new Color(r,g,b,maxBrightness));
			lightImageGraphics.fillRect(lightBoxX, lightBoxY, lightBoxWidth, lightBoxHeight);

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
					angle = (float) Math.atan((float)xFromCenter/(float)yFromCenter);
					if(angle<cornerAngle)
					{
						adjacent = lightBoxHeight/2;

						//get hypotenuse of angle, box width
						//adjacent/hypotenuse = cos(a)
						//adjacent = cos(a)*hypot
						//adjacent/cos(a) = hypot
						distanceFromCenterToBoxEdge = adjacent/(float)Math.cos(angle);

						totalDistanceFromCenterToXY = (float)Math.hypot((float)yFromCenter, (float)xFromCenter);
						//dist to x,y - hypotenuse length = dist from edge of box to x,y
						distanceFromBoxEdgeToXY = (totalDistanceFromCenterToXY-(distanceFromCenterToBoxEdge));
					}
					//else adjacent boxheight
					else
					{
						angle = (float)Math.atan((float)yFromCenter/(float)xFromCenter);

						adjacent=lightBoxWidth/2;

						//get hypotenuse of angle, box width
						//adjacent/hypotenuse = cos(a)
						//adjacent = cos(a)*hypot
						//adjacent/cos(a) = hypot
						distanceFromCenterToBoxEdge = adjacent/(float)Math.cos(angle);

						totalDistanceFromCenterToXY = (float)Math.hypot((float)xFromCenter, (float)yFromCenter);
						//dist to x,y - hypotenuse length = dist from edge of box to x,y
						distanceFromBoxEdgeToXY = (totalDistanceFromCenterToXY-(distanceFromCenterToBoxEdge));
					}



					//System.out.println("X: "+xFromCenter+" | Y: "+yFromCenter);
					//System.out.println("Angle from center to x,y (radians): "+angle+" | Degrees: "+Math.toDegrees(angle));
					//System.out.println("Distance to edge of box from center: "+distanceToEdgeFromCenter);

					if(distanceFromBoxEdgeToXY<=maxDistFromBox)
					{


						//int alpha = maxBrightness-(int)((((d/maxDistFromBox)*maxRadius)/(float)maxRadius)*(float)maxBrightness);

						int alpha = maxBrightness-(int)(Math.pow((distanceFromBoxEdgeToXY/maxDistFromBox),1.0f/decayExponent)*(float)maxBrightness);


						if(alpha>255||alpha<0)lightImageGraphics.setColor(new Color(0,255,0,255));
						else
						//set color
						lightImageGraphics.setColor(new Color(r,g,b,alpha));
						//set pixel
						lightImageGraphics.fillRect((centerX+xFromCenter),(centerY+yFromCenter),1,1);
						lightImageGraphics.fillRect(((centerX-1)-xFromCenter),(centerY+yFromCenter),1,1);
						lightImageGraphics.fillRect((centerX+xFromCenter),((centerY-1)-yFromCenter),1,1);
						lightImageGraphics.fillRect(((centerX-1)-xFromCenter),((centerY-1)-yFromCenter),1,1);
					}
				}

			}

			yFromCenter=0;
			for(xFromCenter=(lightBoxWidth/2);xFromCenter<maxRadius+lightBoxWidth/2;xFromCenter++)
			{
				distanceFromBoxEdgeToXY=xFromCenter-((lightBoxWidth/2));

				totalDistanceFromCenterToXY = xFromCenter;

				//int alpha = maxBrightness-(int)((((distanceFromBoxEdgeToXY/maxDistFromBox)*maxRadius)/(float)maxRadius)*(float)maxBrightness);
				int alpha = maxBrightness-(int)(Math.pow((distanceFromBoxEdgeToXY/maxDistFromBox),1.0f/decayExponent)*(float)maxBrightness);

				if(alpha>255)lightImageGraphics.setColor(new Color(255,0,255,255));
				else
				lightImageGraphics.setColor(new Color(r,g,b,alpha));
				lightImageGraphics.fillRect((centerX+xFromCenter),(centerY+yFromCenter),1,1);
				lightImageGraphics.fillRect(((centerX-1)-xFromCenter),(centerY+yFromCenter),1,1);
				lightImageGraphics.fillRect((centerX+xFromCenter),((centerY-1)+yFromCenter),1,1);
				lightImageGraphics.fillRect(((centerX-1)-xFromCenter),((centerY-1)+yFromCenter),1,1);
			}

			xFromCenter=0;
			for(yFromCenter=(lightBoxHeight/2);yFromCenter<maxRadius+lightBoxHeight/2;yFromCenter++)
			{
				distanceFromBoxEdgeToXY=yFromCenter-((lightBoxHeight/2));
				if(distanceFromBoxEdgeToXY>maxDistFromBox)distanceFromBoxEdgeToXY=maxDistFromBox;

				totalDistanceFromCenterToXY = yFromCenter;

				//int alpha = maxBrightness-(int)((((distanceFromBoxEdgeToXY/maxDistFromBox)*maxRadius)/(float)maxRadius)*(float)maxBrightness);
				int alpha = maxBrightness-(int)(Math.pow((distanceFromBoxEdgeToXY/maxDistFromBox),1.0f/decayExponent)*(float)maxBrightness);


				if(alpha>255)lightImageGraphics.setColor(new Color(255,0,255,255));
				else
				lightImageGraphics.setColor(new Color(r,g,b,alpha));
				lightImageGraphics.fillRect((centerX+xFromCenter),(centerY+yFromCenter),1,1);
				lightImageGraphics.fillRect((centerX+xFromCenter),((centerY-1)-yFromCenter),1,1);
				lightImageGraphics.fillRect(((centerX-1)+xFromCenter),(centerY+yFromCenter),1,1);
				lightImageGraphics.fillRect(((centerX-1)+xFromCenter),((centerY-1)-yFromCenter),1,1);
			}
		}





		//lightImageGraphics.setColor(new Color(r,g,b,brightness));
		//lightImageGraphics.fillRect(x, y, 1, 1);

		//for(int d=0;d<dist;d++)
		//{
			//lightImageGraphics.setColor(new Color(r,g,b,brightness-(int)((d/(float)dist)*(float)brightness)));

			//---------
			//hard rectangle
			//---------
				//lightImageGraphics.drawRect(x-d, y-d, d*2, d*2);

			//---------
			//softer rectangle
			//---------
				//lightImageGraphics.drawLine((x-d)+1, (y-d), (x+d)-1, (y-d));//top
				//lightImageGraphics.drawLine((x-d)+1, (y+d), (x+d)-1, (y+d));//bottom
				//lightImageGraphics.drawLine((x-d), (y-d)+1, (x-d), (y+d)-1);//left
				//lightImageGraphics.drawLine((x+d), (y-d)+1, (x+d), (y+d)-1);//right

				//set the corners of the previous rectangle to this color
				//lightImageGraphics.fillRect((x-d)+1,(y-d)+1,1,1);
				//lightImageGraphics.fillRect((x+d)-1,(y-d)+1,1,1);
				//lightImageGraphics.fillRect((x-d)+1,(y+d)-1,1,1);
				//lightImageGraphics.fillRect((x+d)-1,(y+d)-1,1,1);


			//--------
			//point circle
			//--------
				//lightImageGraphics.drawOval(x-d, y-d, 2+d*2, 1+d*2);

		//}

		bufferedImage = lightImage;

	}








	//===============================================================================================
	public String toString()
	{//===============================================================================================
		return getTYPEIDString();
	}


	//===============================================================================================
	public Light duplicate(Map mapToCopyTo, MapState stateToCopyTo)
	{//===============================================================================================


		Light lightCopy = new Light(mapToCopyTo,stateToCopyTo);


		lightCopy.setXPixels(this.xP());
		lightCopy.setYPixels(this.yP());

		lightCopy.setRedColorByte(this.redColorByte());
		lightCopy.setGreenColorByte(this.greenColorByte());
		lightCopy.setBlueColorByte(this.blueColorByte());
		lightCopy.setAlphaColorByte(this.alphaColorByte());

		lightCopy.setWidthPixels(this.wP());
		lightCopy.setHeightPixels(this.hP());
		lightCopy.setRadiusPixels(this.radiusPixels1X());

		lightCopy.setFocusRadiusPixels(this.focusRadiusPixels1X());

		lightCopy.setToggleXPixels(this.toggleXPixels1X());
		lightCopy.setToggleYPixels(this.toggleYPixels1X());


		lightCopy.data.setName(new String(""+this.name()));
		lightCopy.setBlendFalloff(this.blendFalloff());
		lightCopy.setDecayExponent(this.decayExponent());
		lightCopy.setIsDayLight(this.isDayLight());
		lightCopy.setIsNightLight(this.isNightLight());
		lightCopy.setFlickers(this.flickers());
		lightCopy.setToggleable(this.toggleable());
		lightCopy.setChangesColor(this.changesColor());

		lightCopy.setFlickerOnTicks(this.flickerOnTicks());
		lightCopy.setFlickerOffTicks(this.flickerOffTicks());
		lightCopy.setFlickerRandomUpToOnTicks(this.flickerRandomUpToOnTicks());
		lightCopy.setFlickerRandomUpToOffTicks(this.flickerRandomUpToOffTicks());

		lightCopy.setComment(new String(""+this.comment()));



		lightCopy.bufferedImage = null;


		return lightCopy;

	}


	//===============================================================================================
	public String getLongTypeName()
	{//===============================================================================================


		if(map==null||state==null)
		{


			//find what map this entity is on
			for(int i=0;i<Project.getNumMaps();i++)
			{
				for(int s=0;s<Project.getMap(i).getNumStates();s++)
				{
					for(int k=0;k<Project.getMap(i).getState(s).getNumLights();k++)
					{
						if(Project.getMap(i).getState(s).getLight(k)==this)
						{
							map = Project.getMap(i);
							state = Project.getMap(i).getState(s);
						}
					}
				}
			}
		}


		return "LIGHT."+map.name()+"."+state.name()+"."+name();

	}
	//===============================================================================================
	public String getShortTypeName()
	{//===============================================================================================
		return "LIGHT."+name();
	}

	//===============================================================================================
	public void setNameNoRename(String newName)
	{//===============================================================================================
		data.setName(newName);
	}

	//===============================================================================================
	public void setName(String newName)
	{//===============================================================================================

		String oldName = name();

		data.setName(newName);



		if(map==null||state==null)
		{


			//find what map this entity is on
			for(int i=0;i<Project.getNumMaps();i++)
			{
				for(int s=0;s<Project.getMap(i).getNumStates();s++)
				{
					for(int k=0;k<Project.getMap(i).getState(s).getNumLights();k++)
					{
						if(Project.getMap(i).getState(s).getLight(k)==this)
						{
							map = Project.getMap(i);
							state = Project.getMap(i).getState(s);
						}
					}
				}
			}
		}

		if(map==null)System.err.println("Couldn't find light in maps in setName()");
		if(state==null)System.err.println("Couldn't find light in state in setName()");


		if(map!=null)
		{
			//rename any entity with the same name in any states in THIS MAP
			//have to do all states, keeping entity names synchronized between states
			for(int k=0;k<map.getNumStates();k++)
			{
				for(int n=0;n<map.getState(k).getNumLights();n++)
				{
					Light l = map.getState(k).getLight(n);
					if(l.name().equals(oldName))l.setNameNoRename(newName);
				}
			}
		}


		//don't have to do this anymore, everything is tracked by id

		//then rename this door in all events
//		for(int i = 0; i < Project.eventList.size(); i++)
//		{
//			Project.eventList.get(i).renameLightString(map.name,oldName,newName);
//		}



	}

//	//===============================================================================================
//	public Map getMap()
//	{//===============================================================================================
//
//
//		if(map==null)
//		{
//
//
//			//find what map this entity is on
//			for(int i=0;i<Project.getNumMaps();i++)
//			{
//				for(int s=0;s<Project.getMap(i).getNumStates();s++)
//				{
//					for(int k=0;k<Project.getMap(i).getState(s).getNumLights();k++)
//					{
//						if(Project.getMap(i).getState(s).getLight(k)==this)
//						{
//							map = Project.getMap(i);
//							state = Project.getMap(i).getState(s);
//						}
//					}
//				}
//			}
//		}
//
//		return map;
//
//
//
//	}



}
