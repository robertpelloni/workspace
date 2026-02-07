package com.bobsgame.client.engine.map;

import java.util.Enumeration;
import java.util.ArrayList;

import com.bobsgame.client.Texture;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.entity.Entity;
import com.bobsgame.client.engine.entity.RandomCharacter;
import com.bobsgame.client.engine.event.Event;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.DoorData;
import com.bobsgame.shared.Utils;
//=========================================================================================================================
public class Door extends Entity
{//=========================================================================================================================


	//private DoorData data;

	public int doorknobX;
	public int doorknobY;

	private boolean open = false;
	private boolean stayOpen = false;



	public boolean showActionIcon = true;


	//=========================================================================================================================
	public Door(Engine g, DoorData doorAsset, Map m)
	{//=========================================================================================================================

		super(g);

		init(doorAsset, m);

		this.data = doorAsset;


		if(eventData()!=null)
		{
			Event event = EventManager().getEventByIDCreateIfNotExist(eventData().id());
			event.door = this;
		}



	}


	public boolean isOpen()
	{
		return open;
	}

	public void setOpenManually(boolean b)
	{

		if(b==true)
		{
			this.open=true;
			this.stayOpen=true;

			resetAnimationTimer();
			setNonWalkable(false);
		}
		else
		{
			//update will do the closing animation

			this.stayOpen=false;

			resetAnimationTimer();
			setNonWalkable(true);
		}

	}

	public void setOpenAnimation(boolean b)
	{

		if(b==true)
		{
			this.open=true;
		}
		else
		{
			//update will do the closing animation
		}

	}

	public long lastRequestedMapDataTime = 0;

	public long ticksSinceSpawnTry=0;

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		super.update();




		//preload connecting map

		long time = System.currentTimeMillis();
		if(time-lastRequestedMapDataTime>5000)
		{
			lastRequestedMapDataTime = time;

			if(destinationMapName().length()>0)
				MapManager().requestMapDataIfNotLoadedYet(destinationMapName());
		}



		//super.update() will load and initialize the spriteAsset doorData.
		if(sprite==null)return;


		if(sprite!=null)
		{
			this.doorknobX = sprite.utilityOffsetXPixelsHQ();
			this.doorknobY = sprite.utilityOffsetYPixelsHQ();
		}





		//DONE: handle door opening animation

		if(open==true)
		{
			//if we aren't at the last frame, increment the frames until the last frame, starting at the current frame.

			if(haveTicksPassedSinceLastAnimated_ResetIfTrue(80))
			{
				if(getFrame()<getSpriteLastFrame())incrementAnimationFrameInAllFrames();
				else
				if(stayOpen==false)open=false;
			}

		}

		if(open==false)
		{
			//if we aren't at the first frame, decrement the frames until the first frame, starting at the current frame.

			if(haveTicksPassedSinceLastAnimated_ResetIfTrue(80))
			{
				if(getFrame()>0)setFrame(getFrame()-1);
			}
		}


		if(getMap()==Engine().CurrentMap())
		{


			//handle random spawn point
			if(randomNPCSpawnPoint()&&getMap().randomSpawnEnabled)
			{


				//TODO: make this within screen bounds AND AMOUNT, two screens over?
				if(getMap().isXYWithinScreenByAmt(middleX(), middleY(), 128)==true)
				{


					ticksSinceSpawnTry+=Engine().engineTicksPassed();

					if(ticksSinceSpawnTry>=randomSpawnDelay())
					{
						ticksSinceSpawnTry=0;

						if(Math.random()<randomSpawnChance()) // this is correct.
						{

							//TODO: don't spawn if there are too many randoms, have map limit?


							ArrayList<String> targetTYPEIDList = new ArrayList<String>();

							//if this door has connections, set target to one of this door's connections
							if(connectionTYPEIDList().size()>0)
							{
								for(int i=0;i<connectionTYPEIDList().size();i++)targetTYPEIDList.add(connectionTYPEIDList().get(i));

							}
							else
							{
								targetTYPEIDList = getMap().getListOfRandomPointsOfInterestTYPEIDs();
							}


							if(targetTYPEIDList.size()>0)
							{


								//don't spawn if all the possible random points are full

								while(targetTYPEIDList.size()>0)
								{
									int i = Utils.randLessThan(targetTYPEIDList.size());

									//don't count this door
									if(targetTYPEIDList.get(i).equals("DOOR."+name()))
									{
										targetTYPEIDList.remove(i);
										continue;
									}

									boolean canMakeRandom=false;

									//if there is another exit, keep pumping out randoms, they will go there.
									if(targetTYPEIDList.get(i).startsWith("DOOR."))
									{
										canMakeRandom=true;
									}
									else
									{

										//else we should check to make sure there is a random point of interest to go to, otherwise he will have nowhere to go and just stand there.
										Area a = getMap().getAreaOrWarpAreaByTYPEID(targetTYPEIDList.get(i));

										if(a!=null)
										{

											if(
													//entMan().isAnyoneStandingInArea(a)==true
													//||
													//entMan().isAnyoneTryingToGoToArea(a)==true
													//||
													getMap().findOpenSpaceInArea(a, 32, 32)==null

											)
											{
												targetTYPEIDList.remove(i);
												continue;
											}
											else
											{
												canMakeRandom=true;
											}
										}
										else
										{
											targetTYPEIDList.remove(i);
											//this is a serious error, prints out on System.err in getAreaOrWarpAreaByName
										}
									}

									if(canMakeRandom==true)
									{
										RandomCharacter r = new RandomCharacter(Engine(),getMap(), arrivalXPixelsHQ()+8, arrivalYPixelsHQ()+8, randomSpawnKids(), randomSpawnAdults(), randomSpawnMales(), randomSpawnFemales(), false);
										r.currentAreaTYPEIDTarget = targetTYPEIDList.get(i);
										r.cameFrom="DOOR."+name();
										targetTYPEIDList.clear();
										open=true;
									}

								}
							}


						}
					}

				}



			}
		}

	}


	boolean openingButtonHeld = false;



	//=========================================================================================================================
	public void enter()
	{//=========================================================================================================================

		//go through mapMan().doorList and find door.mapAsset=destinationMapAsset and door.entityNameIdentifier=destinationDoorName, get arrival x and arrival y

		//if(open==false&&spriteAsset.frames>1)setDoorAnim("opening");




		if(destinationTYPEIDString()==null||destinationTYPEIDString().length()==0||destinationTYPEIDString().equals("DOOR."+id()))
		{

			//if action held

			if(ControlsManager().BUTTON_ACTION_HELD)
			{
				if(openingButtonHeld == false)
				{
					openingButtonHeld = true;

					if(open==false)
					{

						setOpenManually(true);
					}
					else
					{
						setOpenManually(false);

					}
				}

			}
			else
			{
				openingButtonHeld = false;
			}
		}
		else
		{


			Map map = MapManager().getMapByNameBlockUntilLoaded(destinationMapName());


			for(int i=0; i<map.doorList.size();i++)
			{
				Door d = map.doorList.get(i);

				if(d.name().equals(destinationDoorName()))
				{

					open=true;

					MapManager().doorEntered = this;
					MapManager().doorExited = d;

					d.open=true;

					//TODO: do I want the other door open?
					//TODO: do I want this door to be open immediately?
					//TODO: do I want them in sync?
					//TODO: test these combinations
					setFrame(getSpriteLastFrame());//set to open frame.
					resetAnimationTimer();

					MapManager().changeMap(destinationMapName(),(d.arrivalXPixelsHQ())+8, (d.arrivalYPixelsHQ())+8);
					return;
				}

			}

		}

	}



	//=========================================================================================================================
	public void renderActionIcon()
	{//=========================================================================================================================

		if(open)return;

		if(showActionIcon==false)return;

		//get distance from player

		Texture actionTexture = SpriteManager().actionTexture;

		if(actionTexture==null)return;

		float doorAlpha = 1.0f;

		if(this.isEntityHitBoxTouchingMyHitBoxByAmount(Player(), 256)==false)return;

		doorAlpha = (256.0f-this.getDistanceFromEntity(Player()))/256.0f;
		if(doorAlpha>1.0f)doorAlpha=1.0f;


		float tx0 = 0.0f;
		float tx1 = 32.0f/((float)actionTexture.getTextureWidth());
		float ty0 = (float)(32.0f*SpriteManager().actionTextureFrame)/((float)actionTexture.getTextureHeight());
		float ty1 = (float)(32.0f*(SpriteManager().actionTextureFrame+1))/((float)actionTexture.getTextureHeight());



		float zoom = Cameraman().getZoom();

		float x0 = screenLeft()	-(16.0f*zoom)+(doorknobX*zoom);
		float x1 = screenLeft()	+(16.0f*zoom)+(doorknobX*zoom);
		float y0 = screenTop()	-(16.0f*zoom)+(doorknobY*zoom);
		float y1 = screenTop()	+(16.0f*zoom)+(doorknobY*zoom);

		GLUtils.drawTexture(actionTexture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, doorAlpha, GLUtils.FILTER_LINEAR);




	}


	//=========================================================================================================================
	public void renderDebugBoxes()
	{//=========================================================================================================================
		float zoom = Cameraman().getZoom();

		float screenRight = screenLeft()+(w()*zoom);
		float screenBottom = screenTop()+(h()*zoom);


		//outline
		GLUtils.drawBox(screenLeft(),screenRight-1,screenTop(),screenBottom-1,0,255,0); //-1 so the box is inside one pixel

		//hitbox
		GLUtils.drawBox(screenLeft()+(hitBoxFromLeft()*zoom),(screenRight-(hitBoxFromRight()*zoom))-1,screenTop()+(hitBoxFromTop()*zoom),(screenBottom-(hitBoxFromBottom()*zoom))-1,255,0,0);



		{
			//arrival point
			float ax=getMap().getScreenX(arrivalXPixelsHQ(),16);
			float ay=getMap().getScreenY(arrivalYPixelsHQ(),16);

			GLUtils.drawBox(ax,ax+(16*zoom)-1,ay,ay+(16*zoom)-1,200,0,255);

			GLUtils.drawLine(screenLeft()+(w()/2)*zoom, screenTop()+(h()/2)*zoom, ax+(8*zoom), ay+(8*zoom), 255, 255, 255);
		}


		for(int i=0;i<connectionTYPEIDList().size();i++)
		{
			//draw connections to doors
			if(connectionTYPEIDList().get(i).startsWith("DOOR."))
			{
				//go through doorlist
				for(int d=0;d<getMap().doorList.size();d++)
				{
					Door door = getMap().doorList.get(d);
					if(door.getMap()==getMap())
					{
						if(connectionTYPEIDList().get(i).equals("DOOR."+door.name()))
						{
							float dx=door.screenLeft()+(door.w()/2)*zoom;
							float dy=door.screenTop()+(door.h())*zoom;

							GLUtils.drawArrowLine(screenLeft()+(w()/2)*zoom, screenTop()+(h()/2)*zoom, dx, dy, 0, 255, 0);
						}
					}
				}
			}
			else
			//draw connections to areas
			{
				//go through area hashlist
				Enumeration<Area> aEnum = getMap().currentState.areaByNameHashtable.elements();
				//areas
				while(aEnum.hasMoreElements())
				{
					Area a = aEnum.nextElement();
					if(connectionTYPEIDList().get(i).equals(a.name()))
					{
						float ax = a.screenLeft()+(a.w()/2)*zoom;
						float ay = a.screenTop()+(a.h()/2)*zoom;

						GLUtils.drawArrowLine(screenLeft()+(w()/2)*zoom, screenTop()+(h()/2)*zoom, ax, ay, 0, 255, 0);
					}
				}

				//if not found, go through warparea list
				for(int j=0;j<getMap().warpAreaList.size();j++)
				{

					Area a = getMap().warpAreaList.get(j);

					if(connectionTYPEIDList().get(i).equals(a.name()))
					{
						float ax = a.screenLeft()+(a.w()/2)*zoom;
						float ay = a.screenTop()+(a.h()/2)*zoom;

						GLUtils.drawArrowLine(screenLeft()+(w()/2)*zoom, screenTop()+(h()/2)*zoom, ax, ay, 0, 255, 0);
					}
				}

			}
		}



	}

	//=========================================================================================================================
	public void renderDebugInfo()
	{//=========================================================================================================================


		int x = (int)screenLeft();
		int y = (int)screenTop();


			int strings = -1;



			GLUtils.drawOutlinedString("entityID: "+name(), x, y-18,BobColor.yellow);


			GLUtils.drawOutlinedString("assetName: "+sprite.name(), x, y-9,BobColor.white);



			GLUtils.drawOutlinedString("destinationTYPEIDString: "+destinationTYPEIDString(), x, y+(++strings*9),new BobColor(200,0,255));

			if(
					destinationTYPEIDString().equals("DOOR."+id())
					||
					destinationTYPEIDString().equals("")
					||
					destinationTYPEIDString().equals("none")
					||
					destinationTYPEIDString().equals("self")

			)GLUtils.drawOutlinedString("Has no destination!", x, y+(++strings*9),BobColor.red);
			//else
			GLUtils.drawOutlinedString("Goes to: "+destinationMapName()+"."+destinationDoorName(), x, y+(++strings*9),new BobColor(200,0,255));



			if(randomNPCSpawnPoint())GLUtils.drawOutlinedString("Random Spawn Point | Chance: "+randomSpawnChance(), x, y+(++strings*9),BobColor.magenta);

			if(randomNPCSpawnPoint())GLUtils.drawOutlinedString("Spawn Delay: "+randomSpawnDelay(), x, y+(++strings*9),BobColor.white);

			if(randomNPCSpawnPoint())
			{
				String allowedTypes = "";
				if(randomSpawnKids())allowedTypes = allowedTypes+" Kids";
				if(randomSpawnAdults())allowedTypes = allowedTypes+" Adults";
				if(randomSpawnMales())allowedTypes = allowedTypes+" Males";
				if(randomSpawnFemales())allowedTypes = allowedTypes+" Females";
				GLUtils.drawOutlinedString("Spawn Types: "+allowedTypes, x, y+(++strings*9),BobColor.magenta);
			}

			if(randomPointOfInterestOrExit())GLUtils.drawOutlinedString("Random Exit (Point Of Interest)", x, y+(++strings*9),BobColor.white);





	/*


	int arrivalXPixelsHQ=0;
	int arrivalYPixelsHQ=0;

	boolean isRandomNPCSpawnPoint;
	float randomSpawnChance;
	boolean randomExit;
	int randomSpawnDelay;
	boolean randomSpawnKids;
	boolean randomSpawnAdults;
	boolean randomSpawnMales;
	boolean randomSpawnFemales;


	ArrayList<String> behaviorList = new ArrayList<String>();
	ArrayList<String> connectionList = new ArrayList<String>();

*/



	}



	public DoorData getData(){return (DoorData)data;}


	public int arrivalXPixelsHQ(){return getData().arrivalXPixelsHQ();}
	public int arrivalYPixelsHQ(){return getData().arrivalYPixelsHQ();}

	public String destinationTYPEIDString()
	{
		if(getData().destinationTYPEIDString()==null||getData().destinationTYPEIDString().length()==0)getData().setDestinationTYPEIDString(getTYPEIDString());
		return getData().destinationTYPEIDString();
	}

	public String destinationMapName(){return getData().destinationMapName();}
	public String destinationDoorName(){return getData().destinationDoorName();}



	public boolean randomPointOfInterestOrExit(){return getData().randomPointOfInterestOrExit();}
	public boolean randomNPCSpawnPoint(){return getData().randomNPCSpawnPoint();}
	public float randomSpawnChance(){return getData().randomSpawnChance();}
	public int randomSpawnDelay(){return getData().randomSpawnDelay();}
	public boolean randomSpawnKids(){return getData().randomSpawnKids();}
	public boolean randomSpawnAdults(){return getData().randomSpawnAdults();}
	public boolean randomSpawnMales(){return getData().randomSpawnMales();}
	public boolean randomSpawnFemales(){return getData().randomSpawnFemales();}






	public void setDestinationTYPEIDString(String typeID){getData().setDestinationTYPEIDString(typeID);}

	public void setRandomPointOfInterestOrExit(boolean s){getData().setRandomPointOfInterestOrExit(s);}
	public void setRandomNPCSpawnPoint(boolean s){getData().setRandomNPCSpawnPoint(s);}
	public void setRandomSpawnChance(float s){getData().setRandomSpawnChance(s);}
	public void setRandomSpawnDelay(int s){getData().setRandomSpawnDelay(s);}
	public void setRandomSpawnKids(boolean s){getData().setRandomSpawnKids(s);}
	public void setRandomSpawnAdults(boolean s){getData().setRandomSpawnAdults(s);}
	public void setRandomSpawnMales(boolean s){getData().setRandomSpawnMales(s);}
	public void setRandomSpawnFemales(boolean s){getData().setRandomSpawnFemales(s);}


	public void setArrivalXPixels(int s){getData().setArrivalXPixels1X(s);}
	public void setArrivalYPixels(int s){getData().setArrivalYPixels1X(s);}




}
