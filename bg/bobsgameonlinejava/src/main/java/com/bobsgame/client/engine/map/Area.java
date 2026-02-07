package com.bobsgame.client.engine.map;

import java.util.Enumeration;
import java.util.ArrayList;

import com.bobsgame.client.Texture;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.entity.Entity;
import com.bobsgame.client.engine.entity.RandomCharacter;
import com.bobsgame.client.engine.event.Event;
import com.bobsgame.shared.AreaData;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.EventData;
import com.bobsgame.shared.Utils;



//=========================================================================================================================
public class Area extends EnginePart
{//=========================================================================================================================



	protected AreaData data = null;


	public long ticksSinceSpawnTry=0;

	public boolean spawned=false;
	public boolean triedSpawn = false;


	public float mapX = 0;
	public float mapY = 0;

	public boolean showActionIcon = true;

	public Map map = null;

	//=========================================================================================================================
	public Area(Engine g)
	{//=========================================================================================================================
		super(g);


	}

	//=========================================================================================================================
	public Area(Engine g, AreaData a, Map m)
	{//=========================================================================================================================
		super(g);

		this.data = a;

		this.mapX = a.mapXPixelsHQ();
		this.mapY = a.mapYPixelsHQ();

		this.map = m;


		if(eventData()!=null)
		{
			Event event = EventManager().getEventByIDCreateIfNotExist(eventData().id());
			event.area = this;
		}

	}









	//=========================================================================================================================
	public Map getMap()
	{//=========================================================================================================================


		//Map map = MapManager().getMapByIDBlockUntilLoaded(mapID());

		return map;
	}












	public boolean fadingInOut = false;
	public float fadeAlpha = 0.0f;



	//=========================================================================================================================
	public void renderActionIcon()
	{//=========================================================================================================================

		if(showActionIcon==false)return;

		if(eventData()==null)return;
		//if(isAnAction==false)return;

		//get distance from player

		//Texture actionTexture = EntityManager.actionTexture;

		//if(actionTexture==null)return;

		float doorAlpha = 1.0f;

		if(this.inRangeOfEntityByAmount(Player(), 256)==false)return;

		doorAlpha = (256.0f-this.getDistanceFromEntity(Player()))/256.0f;
		if(doorAlpha>1.0f)doorAlpha=1.0f;

/*
		float tx0 = 0.0f;
		float tx1 = 32.0f/((float)actionTexture.getTextureWidth());
		float ty0 = (float)(32.0f*EntityManager.actionTextureFrame)/((float)actionTexture.getTextureHeight());
		float ty1 = (float)(32.0f*(EntityManager.actionTextureFrame+1))/((float)actionTexture.getTextureHeight());



		float screenMiddleX = screenLeft()+((screenRight()-screenLeft())/2);
		float screenMiddleY = screenTop()+((screenBottom()-screenTop())/2);// - 128 + entMan().actionTextureFrame*1;


		float x0 = screenMiddleX-16*Cameraman().zoom;
		float x1 = screenMiddleX+16*Cameraman().zoom;
		float y0 = screenMiddleY-16*Cameraman().zoom;
		float y1 = screenMiddleY+16*Cameraman().zoom;

		//GL.drawTexture(actionTexture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, doorAlpha, 1);




		actionTexture = ACTION_icon_sprite.spriteAsset.texture;

		if(actionTexture==null)return;


		if(this.in_range_of_entity_by_amount(Player(), 256)==false)return;

		doorAlpha = (256.0f-this.getDistanceFromEntity(Player()))/256.0f;
		if(doorAlpha>1.0f)doorAlpha=1.0f;


		tx0 = 0.0f;
		tx1 = 32.0f/((float)actionTexture.getTextureWidth());
		ty0 = (float)(32.0f*ACTION_icon_sprite.frameIndexInTexture)/((float)actionTexture.getTextureHeight());
		ty1 = (float)(32.0f*(ACTION_icon_sprite.frameIndexInTexture+1))/((float)actionTexture.getTextureHeight());



		screenMiddleX = screenLeft()+((screenRight()-screenLeft())/2);
		screenMiddleY = screenTop()+((screenBottom()-screenTop())/2);


		x0 = screenMiddleX-8*Cameraman().zoom;
		x1 = screenMiddleX+8*Cameraman().zoom;
		y0 = screenMiddleY-8*Cameraman().zoom	;
		y1 = screenMiddleY+8*Cameraman().zoom;

		//GL.drawTexture(actionTexture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, doorAlpha, 1);
*/

		float x0 = screenLeft();
		float x1 = screenRight();
		float y0 = screenTop();
		float y1 = screenBottom();

		float distanceAlpha = (255.0f-this.getDistanceFromEntity(Player()))/511.0f;
		if(distanceAlpha<0)distanceAlpha=0;

		if(fadingInOut==true)
		{
			fadeAlpha+=Engine().engineTicksPassed()*distanceAlpha*2.0f;

			if(fadeAlpha>=127.0f){fadeAlpha=127.0f;fadingInOut=false;}
		}
		else
		{
			fadeAlpha-=Engine().engineTicksPassed()*distanceAlpha*2.0f;

			if(fadeAlpha<=0.0f){fadeAlpha=0.0f;fadingInOut=true;}
		}


		doorAlpha = distanceAlpha*(fadeAlpha/63.0f);
		//doorAlpha+=(Engine.lastTicks%1000)/3000.0f;

		if(doorAlpha>1.0f)doorAlpha=1.0f;




		Texture actionTexture = SpriteManager().actionTexture;
		float tx0 = 0.0f;
		float tx1 = 32.0f/((float)actionTexture.getTextureWidth());
		float ty0 = (float)(32.0f*10)/((float)actionTexture.getTextureHeight());
		float ty1 = (float)(32.0f*(10+1))/((float)actionTexture.getTextureHeight());

		GLUtils.drawTexture(actionTexture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, doorAlpha, GLUtils.FILTER_LINEAR);

		//Utils.drawFilledRect(255, 255, 255, x0, x1, y0, y1, doorAlpha);





	}



	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		//if(Engine()==null)setGame(map.Engine());

		if(eventData()!=null)
		{
			Event event = EventManager().getEventByIDCreateIfNotExist(eventData().id());
			EventManager().addToEventQueueIfNotThere(event);//events update their own network data inside their run function
		}


		Map map = getMap();

		if(map==Engine().CurrentMap())
		{
			if(map.utilityLayersLoaded==true)//dont start spawning until hit layer exists
			{


				//handle random spawn point
				if(randomNPCSpawnPoint()&&(triedSpawn==false||randomSpawnOnlyTryOnce()==false)&&map.randomSpawnEnabled)
				{


					//TODO: make this within screen bounds AND AMOUNT, two screens over?
					if(map.isXYWithinScreenByAmt(middleX(), middleY(), 128)==true)
					{



						ticksSinceSpawnTry+=Engine().engineTicksPassed();

						if(ticksSinceSpawnTry>=randomSpawnDelay())
						{
							ticksSinceSpawnTry=0;

							triedSpawn=true;

							if(Math.random()<randomSpawnChance())//this is correct.
							{

								// Limit number of random entities
								int randomsCount = 0;
								for(Entity e : map.activeEntityList) {
									if(e instanceof RandomCharacter) randomsCount++;
								}
								if(randomsCount > 50) return; // Hard limit for now, could be configurable


								if(randomNPCStayHere()==true)
								{

									if(spawned==false)
									{
										spawned=true;
										RandomCharacter r = new RandomCharacter(Engine(),map, middleX(), middleY(), randomSpawnKids(), randomSpawnAdults(), randomSpawnMales(), randomSpawnFemales(), randomSpawnCars());

										r.currentAreaTYPEIDTarget="stayHere";
										r.cameFrom=name();
										if(standSpawnDirection()!=-1)
										{
											if(standSpawnDirection()==0)r.movementDirection=Entity.UP;
											if(standSpawnDirection()==1)r.movementDirection=Entity.DOWN;
											if(standSpawnDirection()==2)r.movementDirection=Entity.LEFT;
											if(standSpawnDirection()==3)r.movementDirection=Entity.RIGHT;

										}

									}

								}
								else
								{
									ArrayList<String> targetTYPEIDList = new ArrayList<String>();

									//if this door has connections, set target to one of this door's connections
									if(connectionTYPEIDList().size()>0)
									{
										for(int i=0;i<connectionTYPEIDList().size();i++)targetTYPEIDList.add(connectionTYPEIDList().get(i));

									}
									else
									{
										targetTYPEIDList = map.getListOfRandomPointsOfInterestTYPEIDs();
									}


									if(targetTYPEIDList.size()>0)
									{


										//don't spawn if all the possible random points are full
										while(targetTYPEIDList.size()>0)
										{
											int i = Utils.randLessThan(targetTYPEIDList.size());

											//don't count this door
											if(targetTYPEIDList.get(i).equals(getTYPEIDString()))
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
												Area a = map.getAreaOrWarpAreaByTYPEID(targetTYPEIDList.get(i));

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
												RandomCharacter r = new RandomCharacter(Engine(),map, middleX(), middleY(), randomSpawnKids(), randomSpawnAdults(), randomSpawnMales(), randomSpawnFemales(), randomSpawnCars());

												r.currentAreaTYPEIDTarget = targetTYPEIDList.get(i);
												r.cameFrom=name();



												if(standSpawnDirection()!=-1)
												{
													// set initial direction and frame.
													if(standSpawnDirection()==0)r.movementDirection=Entity.UP;
													if(standSpawnDirection()==1)r.movementDirection=Entity.DOWN;
													if(standSpawnDirection()==2)r.movementDirection=Entity.LEFT;
													if(standSpawnDirection()==3)r.movementDirection=Entity.RIGHT;
												}

												if(waitHereTicks()>0)
												{
													if(randomWaitTime()==true)
													{
														r.ticksToStand = Utils.randLessThan(waitHereTicks());

													}
													else
													{
														r.ticksToStand = waitHereTicks();

													}

												}

												targetTYPEIDList.clear();
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}





	//=========================================================================================================================
	public void renderDebugBoxes()
	{//=========================================================================================================================

		float zoom = Cameraman().getZoom();
		Map map = getMap();

		int r=0;
		int g=0;
		int b=0;

		if(this.getClass().equals(WarpArea.class)){r=200;g=0;b=255;}//purple
		else if(randomNPCSpawnPoint()){r=255;g=0;b=255;}//magenta
		else if(randomPointOfInterestOrExit()){r=255;g=255;b=255;}//white
		else {r=255;g=200;b=0;}//orange


		//outline
		GLUtils.drawBox(screenLeft(),screenRight()-1,screenTop(),screenBottom()-1,r,g,b); //-1 so the box is inside one pixel

		//warparea arrival point
		if(this.getClass().equals(WarpArea.class))
		{

			float ax=map.getScreenX(((WarpArea)this).arrivalXPixelsHQ(),16);
			float ay=map.getScreenY(((WarpArea)this).arrivalYPixelsHQ(),16);


			GLUtils.drawBox(ax,ax+(16*zoom)-1,ay,ay+(16*zoom)-1,200,0,255);

			GLUtils.drawLine(screenLeft()+(w()/2)*zoom, screenTop()+(h()/2)*zoom, ax+(8*zoom), ay+(8*zoom), 255, 255, 255);
		}


		for(int i=0;i<connectionTYPEIDList().size();i++)
		{
			//draw connections to doors
			if(connectionTYPEIDList().get(i).startsWith("DOOR."))
			{
				//go through doorlist
				for(int d=0;d<map.doorList.size();d++)
				{
					Door door = map.doorList.get(d);

					if(connectionTYPEIDList().get(i).equals(door.getTYPEIDString()))
					{
						float dx=door.screenLeft()+(door.w()/2)*zoom;
						float dy=door.screenTop()+(door.h())*zoom;

						GLUtils.drawArrowLine(screenLeft()+(w()/2)*zoom, screenTop()+(h()/2)*zoom, dx, dy, 0, 255, 0);
					}

				}
			}
			else
			//draw connections to areas
			{
				//go through area hashlist
				Enumeration<Area> aEnum = map.currentState.areaByNameHashtable.elements();
				//areas
				while(aEnum.hasMoreElements())
				{
					Area area = aEnum.nextElement();
					if(connectionTYPEIDList().get(i).equals(area.getTYPEIDString()))
					{
						float ax = area.screenLeft()+(area.w()/2)*zoom;
						float ay = area.screenTop()+(area.h()/2)*zoom;

						GLUtils.drawArrowLine(screenLeft()+(w()/2)*zoom, screenTop()+(h()/2)*zoom, ax, ay, 0, 255, 0);
					}
				}

				//if not found, go through warparea list
				for(int j=0;j<map.warpAreaList.size();j++)
				{

					Area area = map.warpAreaList.get(j);

					if(connectionTYPEIDList().get(i).equals(area.getTYPEIDString()))
					{
						float ax = area.screenLeft()+(area.w()/2)*zoom;
						float ay = area.screenTop()+(area.h()/2)*zoom;

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



		if(this.getClass().equals(WarpArea.class)==false)
		GLUtils.drawOutlinedString(name(), x, y-9,BobColor.white);


		//if(isAnAction)GL.drawOutlinedString("Is An Action", x, y+(++strings*9),BobColor.red);
		if(eventData()!=null)GLUtils.drawOutlinedString("Event ID: "+eventData().id(), x, y+(++strings*9),BobColor.white);
		if(waitHereTicks()==-1)GLUtils.drawOutlinedString("Stop Here", x, y+(++strings*9),BobColor.yellow);
		if(waitHereTicks()>0&&randomWaitTime()==false)GLUtils.drawOutlinedString("Wait "+waitHereTicks(), x, y+(++strings*9),BobColor.yellow);
		if(waitHereTicks()>0&&randomWaitTime()==true)GLUtils.drawOutlinedString("Wait Random < "+waitHereTicks(), x, y+(++strings*9),BobColor.yellow);
		if(onlyOneAllowed())GLUtils.drawOutlinedString("Only 1", x, y+(++strings*9),BobColor.green);
		if(standSpawnDirection()!=-1)
		{
			if(standSpawnDirection()==0)GLUtils.drawOutlinedString("Dir: Up", x, y+(++strings*9),BobColor.yellow);
			if(standSpawnDirection()==1)GLUtils.drawOutlinedString("Dir: Down", x, y+(++strings*9),BobColor.yellow);
			if(standSpawnDirection()==2)GLUtils.drawOutlinedString("Dir: Left", x, y+(++strings*9),BobColor.yellow);
			if(standSpawnDirection()==3)GLUtils.drawOutlinedString("Dir: Right", x, y+(++strings*9),BobColor.yellow);
		}

		if(randomPointOfInterestOrExit())GLUtils.drawOutlinedString("Random Point Of Interest Or Exit", x, y+(++strings*9),BobColor.white);

		if(randomNPCSpawnPoint())GLUtils.drawOutlinedString("Random Spawn Point | Chance: "+randomSpawnChance(), x, y+(++strings*9),BobColor.magenta);

		if(randomNPCSpawnPoint())GLUtils.drawOutlinedString("Spawn Delay: "+randomSpawnDelay(), x, y+(++strings*9),BobColor.white);


		if(randomNPCSpawnPoint())
		{
			String allowedTypes = "";
			if(randomSpawnKids())allowedTypes = allowedTypes+" Kids";
			if(randomSpawnAdults())allowedTypes = allowedTypes+" Adults";
			if(randomSpawnMales())allowedTypes = allowedTypes+" Males";
			if(randomSpawnFemales())allowedTypes = allowedTypes+" Females";
			if(randomSpawnCars())allowedTypes = allowedTypes+" Cars";
			GLUtils.drawOutlinedString("Spawn Types: "+allowedTypes, x, y+(++strings*9),BobColor.magenta);
		}
		if(randomNPCStayHere())GLUtils.drawOutlinedString("Random Stay Here", x, y+(++strings*9),BobColor.white);
		if(randomSpawnOnlyTryOnce())GLUtils.drawOutlinedString("Random Only Try Once: "+randomSpawnChance(), x, y+(++strings*9),BobColor.white);
		if(randomSpawnOnlyOffscreen())GLUtils.drawOutlinedString("Random Only Offscreen", x, y+(++strings*9),BobColor.white);
	}


	/**
	 * This gets called repeatedly in events, until it returns a non-null value, at which point the event continues and does not ask again.
	 * This function will continue asking the server for the value, returning null until the server has set the response value.
	 * Upon finding a non-null response value set by the networking thread by a server response, we reset it to null and return that value, ensuring that it is always a fresh copy from the server.
	 */
	public Boolean checkServerTalkedToTodayValueAndResetAfterSuccessfulReturn() {
		// TODO
		return null;
	}

	public void tellServerTalkedToToday() {
		// TODO

	}


	//=========================================================================================================================
	public boolean isWithinScreenBounds()
	{//=========================================================================================================================


		//float zoom = Cameraman().getZoom();

		float mapCameraXPixelsHQ = (float)getMap().mapCamX();
		float mapCameraYPixelsHQ = (float)getMap().mapCamY();

		//*************
		//flooring these fixes all the sprite jitter
		//nope, don't need to do this now, basing all the coords on the offset of the floored mapScreenXY in render, like the map chunk offsets.
		//*************
		float left 	= (float) (x());
		float right 	= (float) (x() + w());
		float top 	= (float) (y()); //we want the actual hitBoxTop() of the sprite, NOT the hit box
		float bottom 	= (float) (y() + h());

		float screenleft = mapCameraXPixelsHQ;
		float screenright = mapCameraXPixelsHQ+Engine().getWidthRelativeToZoom();//actual game rendering is done at 2x so half screen dimensions
		float screentop = mapCameraYPixelsHQ;
		float screenbottom = mapCameraYPixelsHQ+Engine().getHeightRelativeToZoom();


		if(
			right<screenleft
			||
			left>screenright
			||
			bottom<screentop //so shadow can show even if sprite walks above screen
			||
			top>screenbottom
		)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	//=========================================================================================================================
	public boolean inRangeOfEntityByAmount(Entity e,int amt)
	{//=========================================================================================================================

		float eX = e.middleX();
		float eY = e.middleY();

			if(
					middleX()+amt>=eX&&
					middleX()-amt<=eX&&
					middleY()+amt>=eY&&
					middleY()-amt<=eY)return true;
			else return false;
	}

	//=========================================================================================================================
	public float getDistanceFromEntity(Entity e)
	{//=========================================================================================================================

		float eX = e.middleX();
		float eY = e.middleY();


		return Utils.distance(middleX(), middleY(), eX, eY);

	}


	//=========================================================================================================================
	public boolean isEntityHitBoxTouchingMyBoundary(Entity e)
	{//=========================================================================================================================
		return isEntityHitBoxTouchingMyBoundaryByAmount(e,0);
	}
	//=========================================================================================================================
	public boolean isAreaCenterTouchingMyBoundary(Area a)
	{//=========================================================================================================================
		return isAreaCenterTouchingMyBoundaryByAmount(a,0);
	}
	//=========================================================================================================================
	public boolean isAreaBoundaryTouchingMyBoundary(Area a)
	{//=========================================================================================================================
		return isAreaBoundaryTouchingMyBoundaryByAmount(a,0);
	}
	//=========================================================================================================================
	public boolean isXYTouchingMyBoundary(float x, float y)
	{//=========================================================================================================================
		return isXYTouchingMyBoundaryByAmount(x,y,0);
	}
	//=========================================================================================================================
	public boolean isXYXYTouchingMyBoundary(float left, float top, float right, float bottom)
	{//=========================================================================================================================
		return isXYXYTouchingMyBoundaryByAmount(left, top, right, bottom,0);
	}
	//=========================================================================================================================
	public boolean isAreaBoundaryTouchingMyCenter(Area a)
	{//=========================================================================================================================
		return isAreaBoundaryTouchingMyCenterByAmount(a,0);
	}
	//=========================================================================================================================
	public boolean isEntityMiddleXYTouchingMyCenter(Entity e)
	{//=========================================================================================================================
		return isEntityMiddleXYTouchingMyCenterByAmount(e,1);
	}
	//=========================================================================================================================
	public boolean isAreaCenterTouchingMyCenter(Area a)
	{//=========================================================================================================================
		return isAreaCenterTouchingMyCenterByAmount(a,0);
	}
	//=========================================================================================================================
	public boolean isXYTouchingMyCenter(float x, float y)
	{//=========================================================================================================================
		return isXYTouchingMyCenterByAmount(x,y,0);
	}
	//=========================================================================================================================
	public boolean isXYXYTouchingMyCenter(float left, float top, float right, float bottom)
	{//=========================================================================================================================
		return isXYXYTouchingMyCenterByAmount(left, top, right, bottom,0);
	}
	//=========================================================================================================================
	public boolean isEntityHitBoxTouchingMyBoundaryByAmount(Entity e,int amt)
	{//=========================================================================================================================
		return Utils.isXYXYTouchingXYXYByAmount(left(), top(), right(), bottom(), e.left(), e.top(), e.right(), e.bottom(),amt);
	}
	//=========================================================================================================================
	public boolean isAreaCenterTouchingMyBoundaryByAmount(Area a,int amt)
	{//=========================================================================================================================
		return isXYTouchingMyBoundaryByAmount(a.middleX(),a.middleY(),amt);
	}
	//=========================================================================================================================
	public boolean isAreaBoundaryTouchingMyBoundaryByAmount(Area a,int amt)
	{//=========================================================================================================================
		return isXYXYTouchingMyBoundaryByAmount(a.left(),a.top(),a.right(),a.bottom(),amt);
	}
	//=========================================================================================================================
	public boolean isXYTouchingMyBoundaryByAmount(float x, float y,int amt)
	{//=========================================================================================================================
		return isXYXYTouchingMyBoundaryByAmount(x,y,x,y,amt);
	}
	//=========================================================================================================================
	public boolean isXYXYTouchingMyBoundaryByAmount(float left, float top, float right, float bottom,int amt)
	{//=========================================================================================================================
		return Utils.isXYXYTouchingXYXYByAmount(left(), top(), right(), bottom(), left, top, right, bottom,amt);
	}
	//=========================================================================================================================
	public boolean isAreaBoundaryTouchingMyCenterByAmount(Area a,int amt)
	{//=========================================================================================================================
		return isXYXYTouchingMyCenterByAmount(a.left(),a.top(),a.right(),a.bottom(),amt);
	}
	//=========================================================================================================================
	public boolean isEntityMiddleXYTouchingMyCenterByAmount(Entity e,int amt)
	{//=========================================================================================================================
		return isXYTouchingMyCenterByAmount(e.middleX(),e.middleY(),amt);
	}
	//=========================================================================================================================
	public boolean isAreaCenterTouchingMyCenterByAmount(Area a,int amt)
	{//=========================================================================================================================
		return isXYTouchingMyCenterByAmount(a.middleX(),a.middleY(),amt);
	}
	//=========================================================================================================================
	public boolean isXYTouchingMyCenterByAmount(float x, float y,int amt)
	{//=========================================================================================================================
		return isXYXYTouchingMyCenterByAmount(x,y,x,y,amt);
	}
	//=========================================================================================================================
	public boolean isXYXYTouchingMyCenterByAmount(float left, float top, float right, float bottom,int amt)
	{//=========================================================================================================================
		return Utils.isXYXYTouchingXYXYByAmount(middleX(), middleY(), middleX(), middleY(), left, top, right, bottom,amt);
	}


	//=========================================================================================================================
	public float top()
	{//=========================================================================================================================
		return (y());
	}
	//=========================================================================================================================
	public float left()
	{//=========================================================================================================================
		return (x());
	}
	//=========================================================================================================================
	public float right()
	{//=========================================================================================================================
		return (x()+w());
	}
	//=========================================================================================================================
	public float bottom()
	{//=========================================================================================================================
		return (y()+h());
	}
	//=========================================================================================================================
	public float middleX()
	{//=========================================================================================================================
		return (x()+(w()/2));
	}
	//=========================================================================================================================
	public float middleY()
	{//=========================================================================================================================
		return (y()+h()/2);
	}
	public float roundedMiddleX()
	{
		return Math.round(middleX());
	}

	public float roundedMiddleY()
	{
		return Math.round(middleY());
	}







	//=========================================================================================================================
	private float screenX()
	{//=========================================================================================================================

		float zoom = Cameraman().getZoom();

		float mapCameraXPixelsHQ = getMap().mapCamX();

		//flooring these fixes the jitter for lights
		float left 	= (float) Math.floor(x());
		float right 	= (float) Math.floor(x() + w());

		float screenleft = mapCameraXPixelsHQ;
		float screenright = mapCameraXPixelsHQ+Engine().getWidthRelativeToZoom();

		float screenXPixelsHQ = (left - screenleft);

		//if overlapping left side of screen
		if(right>=screenleft&&left<screenleft)screenXPixelsHQ =  (0.0f - (screenleft-left));

		//if onscreen and not overlapping the left side
		if(left>=screenleft&&left<screenright)screenXPixelsHQ =  (left - screenleft);

		return screenXPixelsHQ*zoom;

	}

	//=========================================================================================================================
	private float screenY()
	{//=========================================================================================================================

		float zoom = Cameraman().getZoom();

		float mapCameraYPixelsHQ = getMap().mapCamY();


		//flooring these fixes the jitter for lights
		float top 	= (float) Math.floor(y());
		float bottom 	= (float) Math.floor(y() + h());

		float screentop = mapCameraYPixelsHQ;
		float screenbottom = mapCameraYPixelsHQ+Engine().getHeightRelativeToZoom();

		float screenYPixelsHQ = top-screentop;

		//if overlapping top side of screen
		if(bottom>=screentop&&top<screentop)screenYPixelsHQ =  0.0f - (screentop-top);

		//if onscreen and not overlapping the top side
		if(top>=screentop&&top<screenbottom)screenYPixelsHQ = top-screentop;

		return screenYPixelsHQ*zoom;

	}



	//=========================================================================================================================
	public float screenLeft()
	{//=========================================================================================================================
		return screenX();
	}

	//=========================================================================================================================
	public float screenRight()
	{//=========================================================================================================================

		return screenX() + (float)w()*Cameraman().getZoom();
	}

	//=========================================================================================================================
	public float screenTop()
	{//=========================================================================================================================
		return screenY();

	}

	//=========================================================================================================================
	public float screenBottom()
	{//=========================================================================================================================
		return screenY() + (float)h()*Cameraman().getZoom();

	}





	public AreaData getData(){return data;}


	public float x(){return mapX;}
	public float y(){return mapY;}

	public int w(){return getData().widthPixelsHQ();}
	public int h(){return getData().heightPixelsHQ();}



	public String name(){return getData().name();}
	public String comment(){return getData().comment();}
	public int id(){return getData().id();}

	//public int mapID(){return getData().mapID();}


	public int arrivalXPixelsHQ(){return getData().arrivalXPixelsHQ();}
	public int arrivalYPixelsHQ(){return getData().arrivalYPixelsHQ();}

	public boolean isWarpArea(){return getData().isWarpArea();}
	public boolean randomPointOfInterestOrExit(){return getData().randomPointOfInterestOrExit();}
	public boolean randomNPCSpawnPoint(){return getData().randomNPCSpawnPoint();}
	public int standSpawnDirection(){return getData().standSpawnDirection();}
	public int waitHereTicks(){return getData().waitHereTicks();}
	public boolean randomWaitTime(){return getData().randomWaitTime();}
	public boolean onlyOneAllowed(){return getData().onlyOneAllowed();}
	public boolean randomNPCStayHere(){return getData().randomNPCStayHere();}
	public float randomSpawnChance(){return getData().randomSpawnChance();}
	public boolean randomSpawnOnlyTryOnce(){return getData().randomSpawnOnlyTryOnce();}
	public boolean randomSpawnOnlyOffscreen(){return getData().randomSpawnOnlyOffscreen();}
	public int randomSpawnDelay(){return getData().randomSpawnDelay();}
	public boolean randomSpawnKids(){return getData().randomSpawnKids();}
	public boolean randomSpawnAdults(){return getData().randomSpawnAdults();}
	public boolean randomSpawnMales(){return getData().randomSpawnMales();}
	public boolean randomSpawnFemales(){return getData().randomSpawnFemales();}
	public boolean randomSpawnCars(){return getData().randomSpawnCars();}
	public boolean autoPilot(){return getData().autoPilot();}
	public boolean playerFaceDirection(){return getData().playerFaceDirection();}
	public boolean suckPlayerIntoMiddle(){return getData().suckPlayerIntoMiddle();}
	//public int eventID(){return getData().eventID();}
	public EventData eventData(){return getData().eventData();}

	public ArrayList<String> connectionTYPEIDList(){return getData().connectionTYPEIDList();}

	public String getTYPEIDString(){return getData().getTYPEIDString();}

	public String destinationTYPEIDString()
	{
		if(getData().destinationTYPEIDString()==null||getData().destinationTYPEIDString().length()==0)getData().setDestinationTYPEIDString(getTYPEIDString());
		return getData().destinationTYPEIDString();
	}






}
