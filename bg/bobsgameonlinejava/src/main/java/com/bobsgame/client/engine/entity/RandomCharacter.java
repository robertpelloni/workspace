package com.bobsgame.client.engine.entity;

import static org.lwjgl.opengl.GL11.glTexImage2D;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.concurrent.Executors;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.map.Area;
import com.bobsgame.client.engine.map.Door;
import com.bobsgame.client.engine.map.Map;
import com.bobsgame.client.engine.map.MapManager;
import com.bobsgame.client.engine.map.WarpArea;
import com.bobsgame.shared.EntityData;
import com.bobsgame.shared.Utils;




//=========================================================================================================================
public class RandomCharacter extends Character
{//=========================================================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(RandomCharacter.class);


	public float targetX=-1;
	public float targetY=-1;

	public String cameFrom = "";
	public boolean gotThere = false;


	//public Texture shadowTexture = null; // just use the normal hq2x shadow texture in the spriteasset since it doesn't matter.


	public boolean kid = false;
	public boolean adult = false;
	public boolean male = false;
	public boolean female = false;
	public boolean car = false;










	//=========================================================================================================================
	public RandomCharacter(Engine g, Map map, float mapX, float mapY, boolean kid, boolean adult, boolean male, boolean female, boolean car)
	{//=========================================================================================================================

		//DONE: randomly decide what kind of character to create

		//spawn at mapX, mapY

		super(g, new EntityData(-1,"Random","",mapX,mapY), map);



		ArrayList<String> spriteNameList = new ArrayList<String>();

		if(kid==true)
		{
			if(male==true)
			{

				spriteNameList.add("RANDOMBoyBuzzedHairLongSleeve");
				spriteNameList.add("RANDOMBoyBuzzedHairShortSleeve");
				spriteNameList.add("RANDOMBoyBuzzedHairLongSleeveShorts");
				spriteNameList.add("RANDOMBoyBuzzedHairShortSleeveShorts");
				spriteNameList.add("RANDOMBoyMessyHairLongSleeve");
				spriteNameList.add("RANDOMBoyMessyHairShortSleeve");
				spriteNameList.add("RANDOMBoyMessyHairLongSleeveShorts");
				spriteNameList.add("RANDOMBoyMessyHairShortSleeveShorts");
				spriteNameList.add("RANDOMBoyNormalHairLongSleeve");
				spriteNameList.add("RANDOMBoyNormalHairShortSleeve");
				spriteNameList.add("RANDOMBoyNormalHairLongSleeveShorts");
				spriteNameList.add("RANDOMBoyNormalHairShortSleeveShorts");
				spriteNameList.add("RANDOMBoyShortHairLongSleeve");
				spriteNameList.add("RANDOMBoyShortHairShortSleeve");
				spriteNameList.add("RANDOMBoyShortHairLongSleeveShorts");
				spriteNameList.add("RANDOMBoyShortHairShortSleeveShorts");
				spriteNameList.add("RANDOMLittleBoyBuzzedHairLongSleeve");
				spriteNameList.add("RANDOMLittleBoyBuzzedHairShortSleeve");
				spriteNameList.add("RANDOMLittleBoyBuzzedHairLongSleeveShorts");
				spriteNameList.add("RANDOMLittleBoyBuzzedHairShortSleeveShorts");
				spriteNameList.add("RANDOMLittleBoyMessyHairLongSleeve");
				spriteNameList.add("RANDOMLittleBoyMessyHairShortSleeve");
				spriteNameList.add("RANDOMLittleBoyMessyHairLongSleeveShorts");
				spriteNameList.add("RANDOMLittleBoyMessyHairShortSleeveShorts");
				spriteNameList.add("RANDOMLittleBoyNormalHairLongSleeve");
				spriteNameList.add("RANDOMLittleBoyNormalHairShortSleeve");
				spriteNameList.add("RANDOMLittleBoyNormalHairLongSleeveShorts");
				spriteNameList.add("RANDOMLittleBoyNormalHairShortSleeveShorts");
			}



			if(female==true)
			{
				spriteNameList.add("RANDOMGirlLongHairDress");
				spriteNameList.add("RANDOMGirlLongHairSkirt");
				spriteNameList.add("RANDOMGirlLongHairSkirtHalter");
				spriteNameList.add("RANDOMGirlLongHairJeans");
				spriteNameList.add("RANDOMGirlLongHairJeansHalter");
				spriteNameList.add("RANDOMGirlLongHairShortsHalter");
				spriteNameList.add("RANDOMGirlPonytailDress");
				spriteNameList.add("RANDOMGirlPonytailSkirt");
				spriteNameList.add("RANDOMGirlPonytailSkirtHalter");
				spriteNameList.add("RANDOMGirlPonytailJeans");
				spriteNameList.add("RANDOMGirlPonytailJeansHalter");
				spriteNameList.add("RANDOMGirlPonytailShortsHalter");
				spriteNameList.add("RANDOMGirlShortHairDress");
				spriteNameList.add("RANDOMGirlShortHairSkirt");
				spriteNameList.add("RANDOMGirlShortHairSkirtHalter");
				spriteNameList.add("RANDOMGirlShortHairJeans");
				spriteNameList.add("RANDOMGirlShortHairJeansHalter");
				spriteNameList.add("RANDOMGirlShortHairShortsHalter");
				spriteNameList.add("RANDOMLittleGirlLongHairDress");
				spriteNameList.add("RANDOMLittleGirlLongHairSkirt");
				spriteNameList.add("RANDOMLittleGirlLongHairSkirtHalter");
				spriteNameList.add("RANDOMLittleGirlLongHairJeans");
				spriteNameList.add("RANDOMLittleGirlLongHairJeansHalter");
				spriteNameList.add("RANDOMLittleGirlLongHairShortsHalter");
				spriteNameList.add("RANDOMLittleGirlPonytailDress");
				spriteNameList.add("RANDOMLittleGirlPonytailSkirt");
				spriteNameList.add("RANDOMLittleGirlPonytailSkirtHalter");
				spriteNameList.add("RANDOMLittleGirlPonytailJeans");
				spriteNameList.add("RANDOMLittleGirlPonytailJeansHalter");
				spriteNameList.add("RANDOMLittleGirlPonytailShortsHalter");
				spriteNameList.add("RANDOMLittleGirlShortHairDress");
				spriteNameList.add("RANDOMLittleGirlShortHairSkirt");
				spriteNameList.add("RANDOMLittleGirlShortHairSkirtHalter");
				spriteNameList.add("RANDOMLittleGirlShortHairJeans");
				spriteNameList.add("RANDOMLittleGirlShortHairJeansHalter");
				spriteNameList.add("RANDOMLittleGirlShortHairShortsHalter");


			}

		}

		if(adult==true)
		{
			if(male==true)
			{
				spriteNameList.add("RANDOMManBaldUndershirt");
				spriteNameList.add("RANDOMManBaldShortSleeve");
				spriteNameList.add("RANDOMManBaldSuit");
				spriteNameList.add("RANDOMManBaldSweats");
				spriteNameList.add("RANDOMManBaldLongSleeve");
				spriteNameList.add("RANDOMManBaldingUndershirt");
				spriteNameList.add("RANDOMManBaldingShortSleeve");
				spriteNameList.add("RANDOMManBaldingSuit");
				spriteNameList.add("RANDOMManBaldingSweats");
				spriteNameList.add("RANDOMManBaldingLongSleeve");
				spriteNameList.add("RANDOMManBeardUndershirt");
				spriteNameList.add("RANDOMManBeardShortSleeve");
				spriteNameList.add("RANDOMManBeardSuit");
				spriteNameList.add("RANDOMManBeardSweats");
				spriteNameList.add("RANDOMManBeardLongSleeve");
				spriteNameList.add("RANDOMManNormalHairUndershirt");
				spriteNameList.add("RANDOMManNormalHairShortSleeve");
				spriteNameList.add("RANDOMManNormalHairSuit");
				spriteNameList.add("RANDOMManNormalHairSweats");
				spriteNameList.add("RANDOMManNormalHairLongSleeve");
				spriteNameList.add("RANDOMManShortHairUndershirt");
				spriteNameList.add("RANDOMManShortHairShortSleeve");
				spriteNameList.add("RANDOMManShortHairSuit");
				spriteNameList.add("RANDOMManShortHairSweats");
				spriteNameList.add("RANDOMManShortHairLongSleeve");

			}



			if(female==true)
			{

				spriteNameList.add("RANDOMWomanBunDress");
				spriteNameList.add("RANDOMWomanBunSkirt");
				spriteNameList.add("RANDOMWomanBunSkirtHalter");
				spriteNameList.add("RANDOMWomanBunJeans");
				spriteNameList.add("RANDOMWomanBunJeansHalter");
				spriteNameList.add("RANDOMWomanBunShortsHalter");
				spriteNameList.add("RANDOMWomanLongHairDress");
				spriteNameList.add("RANDOMWomanLongHairSkirt");
				spriteNameList.add("RANDOMWomanLongHairSkirtHalter");
				spriteNameList.add("RANDOMWomanLongHairJeans");
				spriteNameList.add("RANDOMWomanLongHairJeansHalter");
				spriteNameList.add("RANDOMWomanLongHairShortsHalter");
				spriteNameList.add("RANDOMWomanPonytailDress");
				spriteNameList.add("RANDOMWomanPonytailSkirt");
				spriteNameList.add("RANDOMWomanPonytailSkirtHalter");
				spriteNameList.add("RANDOMWomanPonytailJeans");
				spriteNameList.add("RANDOMWomanPonytailJeansHalter");
				spriteNameList.add("RANDOMWomanPonytailShortsHalter");
				spriteNameList.add("RANDOMWomanPoofyHairDress");
				spriteNameList.add("RANDOMWomanPoofyHairSkirt");
				spriteNameList.add("RANDOMWomanPoofyHairSkirtHalter");
				spriteNameList.add("RANDOMWomanPoofyHairJeans");
				spriteNameList.add("RANDOMWomanPoofyHairJeansHalter");
				spriteNameList.add("RANDOMWomanPoofyHairShortsHalter");
				spriteNameList.add("RANDOMWomanShortHairDress");
				spriteNameList.add("RANDOMWomanShortHairSkirt");
				spriteNameList.add("RANDOMWomanShortHairSkirtHalter");
				spriteNameList.add("RANDOMWomanShortHairJeans");
				spriteNameList.add("RANDOMWomanShortHairJeansHalter");
				spriteNameList.add("RANDOMWomanShortHairShortsHalter");


			}

		}

		if(car==true)
		{
			spriteNameList.add("RANDOMcar");
			spriteNameList.add("RANDOMmotorcycle");
			spriteNameList.add("RANDOMvan");
			spriteNameList.add("RANDOMtruck");
			spriteNameList.add("RANDOMsuv");
			spriteNameList.add("RANDOMferrari");
			spriteNameList.add("RANDOMminivan");


		}




		getData().setSpriteName(spriteNameList.get(Utils.randLessThan(spriteNameList.size())));

		this.sprite = SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist(spriteName());

		if(sprite!=null)
		{
			initCurrentAnimationFromSprite();
		}




		setTicksPerPixelMoved(8);
		//ticksPerPixelMoved = 4+Utils.randLessThan(5); //this still breaks walking.
		//TODO: find out why ticksPerPixelMoved<5 breaks walking!

		setNonWalkable(false);

		setScale(1.25f);
		setToAlpha(1.0f);


		this.kid = kid;
		this.adult = adult;
		this.male = male;
		this.female = female;
		this.car = car;


		if(car)
		{
			setNonWalkable(true);
			clipShadow = false;
			shadowSize = 1.1f;
			setScale(1.5f);
		}


		setX(mapX);
		setY(mapY);

		setX(mapX - (hitBoxFromLeft()+(middleX()-left())));
		setY(mapY - (middleY()-y()));






	}

	//=========================================================================================================================
	public Map CurrentMap()
	{//=========================================================================================================================


		log.error("Bug: Don't use CurrentMap() in Characters. Use this.map or getMap()");

		return null;

	}




	//=========================================================================================================================
	public synchronized ByteBuffer getByteBuffer_S()
	{//=========================================================================================================================
		return textureByteBuffer_S;
	}


	//=========================================================================================================================
	public synchronized void setByteBuffer_S(ByteBuffer bb)
	{//=========================================================================================================================
		textureByteBuffer_S=bb;
	}




	ByteBuffer textureByteBuffer_S;

	int eyeSet = -1;
	int skinSet = -1;
	int hairSet = -1;
	int shirtSet = -1;
	int pantsSet = -1;
	int shoeSet = -1;
	int carSet = -1;


	//=========================================================================================================================
	public int selectRandomSet(Sprite s)
	{//=========================================================================================================================

		int set = 0;

		int w = s.w()/2;//because HQ, draw at 2x, actual data is half size, etc
		int h = s.h()/2;

		if(set==0)
		{
			int maxSets = 0;
			for(int v = 1; v < h; v++)
			{
				if((s.indexDataIntArray[v*w] & 0xFF)==0)
				{
					maxSets = v-1;
					break;
				}
			}

			if(kid&&s==SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMhairColors"))set = Utils.randLessThan(maxSets-3) + 1; //dont give kids gray hair
			else set = Utils.randLessThan(maxSets-1) + 1;

		}

		return set;
	}


	public boolean createdThread=false;

	//=========================================================================================================================
	public void createRandomTexture()
	{//=========================================================================================================================

		if(createdThread==false)
		{
			if(car)
			{
				carSet = selectRandomSet(SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMcarColors"));

			}
			else
			{
				eyeSet = selectRandomSet(SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMeyeColors"));
				skinSet = selectRandomSet(SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMskinColors"));
				hairSet = selectRandomSet(SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMhairColors"));
				shirtSet = selectRandomSet(SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshirtColors"));
				pantsSet = selectRandomSet(SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMpantsColors"));
				shoeSet = selectRandomSet(SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshoeColors"));
			}

			if(MapManager.useThreads)
			{

				if(Sprite.generatePNGExecutorService==null)Sprite.generatePNGExecutorService = Executors.newFixedThreadPool(1);
				Sprite.generatePNGExecutorService.execute
				(
					new Runnable()
					{

						public void run()
						{
							try{Thread.currentThread().setName("RandomCharacter_createRandomSpriteTexture");}catch(SecurityException e){e.printStackTrace();}

							ByteBuffer bb = sprite.createRandomSpriteTextureByteBuffer_S(eyeSet, skinSet, hairSet, shirtSet, pantsSet, shoeSet, carSet);
							setByteBuffer_S(bb);
						}
					}
				);

			}
			else
			{

				ByteBuffer bb = sprite.createRandomSpriteTextureByteBuffer_S(eyeSet, skinSet, hairSet, shirtSet, pantsSet, shoeSet, carSet);
				setByteBuffer_S(bb);
			}

			createdThread=true;
		}
	}

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		//if set to action, continue towards action


		//else select new random point of interest


		super.update();


		//TODO: if my custom texture is null, check to see if spriteAsset has the indexed data md5 yet.
		//TODO: create a custom texture for randomcharacter here.
		//create a new thread, and set the texture through a synchronized call.
		//then override render() with something that uses MY texture.


		SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMcarColors").loadTextures();
		SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMeyeColors").loadTextures();
		SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMskinColors").loadTextures();
		SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMhairColors").loadTextures();
		SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshirtColors").loadTextures();
		SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMpantsColors").loadTextures();
		SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshoeColors").loadTextures();




		if(uniqueTexture==null)
		{
			if(sprite.indexDataIntArray!=null)//the indexed data is loaded
			{
				if(createdThread==false)createRandomTexture();
				else
				{
					//we're waiting for the thread to finish generating the bytebuffer

					ByteBuffer bb = getByteBuffer_S();
					if(bb!=null)
					{
						uniqueTexture = GLUtils.loadTexture("random"+Utils.randLessThan(500),sprite.w(), sprite.h() * sprite.frames(), bb);

						setByteBuffer_S(null);
						bb=null;
					}

				}
			}
		}









		//if(hitBoxTop()>(3*16))
		//hitBoxFromTopPixelsHQ = (int)((3*16)/scale);


		//DONE: need to store "where came from" and don't select that as the first currentAreaTarget if currentAreaTarget is empty.
		//this is done in Door and WarpArea upon spawn, it finds an appropriate initial target, not including itself.
		//did end up adding "cameFrom" but isn't used yet.



		//avoid_entity(player(),16);
		//avoid_nearest_character(8);

		if(ticksToStand>0)
		{
			ticksToStand-=Engine().engineTicksPassed();

			//do standing animation here
			//doStandingAnimation();//should be handled by checkIfMoved and doCharacterAnimation now
		}
		else
		if(currentAreaTYPEIDTarget.equals("stayHere")==true)
		{

			//doStandingAnimation();//should be handled by checkIfMoved and doCharacterAnimation now
		}
		else
		if(currentAreaTYPEIDTarget.length()>0)
		{

			//if we aren't there yet, let's go there.
			if(gotThere==false)
			{
				if(currentAreaTYPEIDTarget.startsWith("DOOR.")==true)
				{
					//handle walking through door.
					Door d = getMap().getDoorByTYPEID(currentAreaTYPEIDTarget);

					//walk towards x and y
					int there = 0;
					if(getMap().isOutside()==false)there = walkToXYWithPathFinding(d.middleX(), d.middleY());
					else there = walkToXYNoHitAvoidOthersPushMain(d.middleX(), d.middleY());

					//if we are there, pick a new point
					if(there==1)
					{
						d.setOpenAnimation(true);

						fadeOutAndDelete();
					}
					if(there==-1)
					{
						//no path to the door, pick another point.
						currentAreaTYPEIDTarget="";
					}

				}
				else //find current area
				if(currentAreaTYPEIDTarget.startsWith("DOOR.")==false)
				{


					//get current area x and y
					Area a = getMap().getAreaOrWarpAreaByTYPEID(currentAreaTYPEIDTarget);



					//TODO: if the area is a single tile, just touching the edge should be fine.


					//TODO: find where it checks is sprite is in the area, in pathfinding. make it if sprite is touching it at all.


					//we store the position in the area so that we can find a unique place inside large areas. don't need to do this for doors.
					if(targetX==-1&&targetY==-1)
					{

						//if this area is bigger than one tile and allows multiple people, find a suitable place inside it.
						if(a.onlyOneAllowed()==false&&(a.w()>32||a.h()>32))
						{


							//divide area into tiles, check midpoint of each tile for enough room to stand

							int w = (int)(right()-left());
							int h = (int)(bottom()-top());

							//TODO: try the middle of the edge closest to sprite.

							//first try the exact middle.
							/*
							if(
								entMan().isAnyoneOverlappingXYXY(a.mapXPixelsHQ+a.widthPixelsHQ/2-w/2, a.mapYPixelsHQ+a.heightPixelsHQ/2-h/2, a.mapXPixelsHQ+a.widthPixelsHQ/2+w/2, a.mapYPixelsHQ+a.heightPixelsHQ/2+h/2)==false
								&&
								entMan().isAnyOtherRandomCharacterTryingToGoToXY(a.mapXPixelsHQ+a.widthPixelsHQ/2, a.mapYPixelsHQ+a.heightPixelsHQ/2)==false
							)
							{
								targetX = a.mapXPixelsHQ+a.widthPixelsHQ/2;
								targetY = a.mapYPixelsHQ+a.heightPixelsHQ/2;

								//DONE: could also check all the other random characters targetX and targetY to make sure nobody is TRYING to go here


							}
							else
							*/
							{
								int[] xy = getMap().findOpenSpaceInArea(a, w, h);

								if(xy!=null)
								{
									targetX = xy[0];
									targetY = xy[1];
								}
							}

							//if there is no space available, get another point.
							if(targetX==-1&&targetY==-1)
							{
								currentAreaTYPEIDTarget = getRandomAreaWarpOrDoorTYPEID();
								targetX=-1;
								targetY=-1;


							}

						}
						else
						{

							targetX = a.middleX();//mapXPixelsHQ + a.widthPixelsHQ/2;
							targetY = a.middleY();//a.mapYPixelsHQ + a.heightPixelsHQ/2;

						}
					}



					if(targetX!=-1&&targetY!=-1)
					{


						//walk towards x and y
						//int there = walk_to_xy_pathfind(targetX, targetY);
						int there = 0;
						if(getMap().isOutside()==false && getMap().widthTiles1X()<100 && getMap().heightTiles1X()<100)there = walkToXYWithPathFinding(targetX, targetY);
						else there = walkToXYNoHitAvoidOthersPushMain(targetX, targetY);

						//if we are there, pick a new point
						if(there==1 || there==-1)
						{

							//check area for variables: stay here, wait x ms, face direction
							if(a.standSpawnDirection()!=-1)
							{
								if(a.standSpawnDirection()==0)movementDirection=UP;
								if(a.standSpawnDirection()==1)movementDirection=DOWN;
								if(a.standSpawnDirection()==2)movementDirection=LEFT;
								if(a.standSpawnDirection()==3)movementDirection=RIGHT;
							}

							//set standing ticks to current ticks
							if(a.waitHereTicks()>0)
							{

								if(a.randomWaitTime()==true)ticksToStand=Utils.randLessThan(a.waitHereTicks());
								else ticksToStand=a.waitHereTicks();

							}
							else ticksToStand=0;


							gotThere=true;


							//pushable=true;
						}
//						else
//						if(there==-1)//no path, select another point.
//						{
//							gotThere=true;
//						}

					}

				}
			}
			else
			if(gotThere==true)//this is only for areas. doors will just immediately delete the entity. this is so we can change modes and be pushable after we've reached our destination and waiting for a new one.
			{

				if(currentAreaTYPEIDTarget.startsWith("DOOR.")==false)
				{


					//get current area x and y
					Area a = getMap().getAreaOrWarpAreaByTYPEID(currentAreaTYPEIDTarget);


					//avoid_nearest_entity(32);


					//if
					//(
						//avoid_entity(player(),16)==1
						//&&
						//avoid_nearest_character(16)==1
						//&&
						//(Math.abs(middleX()-finalPathX)>4||Math.abs(middleY()-finalPathY)>4)
					//);
					//walk_to_xy_nohit(finalPathX,finalPathY);

					//walk_to_xy_intelligenthit_avoidothers_pushmain(5, targetX,targetY);


					//if randomNPCStayHere, don't pick a new target! just stay here and do whatever
					if(a.randomNPCStayHere()||a.waitHereTicks()==-1)
					{
						currentAreaTYPEIDTarget = "stayHere";
					}

					if(a.getClass().equals(WarpArea.class)&&(a.randomPointOfInterestOrExit()==true)&&a.randomNPCStayHere()==false)
					{

						fadeOutAndDelete();

					}
					else
					{

						{
							String tempTarget = currentAreaTYPEIDTarget;

							//if current target area has connections, pick a connection and go there.
							if(a.connectionTYPEIDList().size()>0)
							{
								currentAreaTYPEIDTarget = getRandomConnectionTYPEIDFromCurrentPoint();

							}
							else
							{ //go through all areas on map and randomly select one

								currentAreaTYPEIDTarget = getRandomAreaWarpOrDoorTYPEID();

							}

							//if we didn't find a new target, it must be blocked. let's stand and shuffle.
							if(currentAreaTYPEIDTarget.equals(tempTarget))
							{
								//doStandingAnimation();//should be handled by checkIfMoved and doCharacterAnimation now

							}
							else
							{
								//we have a new target, let's reset targetX and Y
								targetX=-1;
								targetY=-1;
								gotThere=false;
								//pushable=false;
							}
						}
					}
				}



			}



		}
		else
		{
			//else pick a new point

			//go through all map areas, find random point of interest.

			currentAreaTYPEIDTarget = getRandomAreaWarpOrDoorTYPEID();
			targetX=-1;
			targetY=-1;

		}



		//this is done here regardless of controls so that external movements still trigger animation and sound, i.e. cutscenes
		checkIfMoved();

		doCharacterAnimation();

	}










	//=========================================================================================================================
	public String getRandomAreaWarpOrDoorTYPEID()
	{//=========================================================================================================================


		ArrayList<String> areaTYPEIDList = getMap().getListOfRandomPointsOfInterestTYPEIDs();


		if(areaTYPEIDList.size()==0)return currentAreaTYPEIDTarget;


		int index = Utils.randLessThan(areaTYPEIDList.size());


		//don't select the target we already have
		if(areaTYPEIDList.size()>1)
		{
			while(areaTYPEIDList.get(index).equals(currentAreaTYPEIDTarget))index = Utils.randLessThan(areaTYPEIDList.size());
		}



		String nextTYPEIDTarget = areaTYPEIDList.get(index);

		//don't select targets more than a screen away
		{


			float distance = 0;

			if(nextTYPEIDTarget.startsWith("DOOR.")==true)
			{
				Door d = getMap().getDoorByTYPEID(nextTYPEIDTarget);
				distance = Utils.distance(middleX(), middleY(), d.middleX(), d.middleY());

			}
			else
			{
				Area n = getMap().getAreaOrWarpAreaByTYPEID(nextTYPEIDTarget);

				distance = Utils.distance(middleX(), middleY(), n.middleX(), n.middleY());
			}


			//TODO: make this "on screen" or "two screens away"
			if(distance>500)return currentAreaTYPEIDTarget;

		}

		//TODO: don't go to doors or warp areas that are exits AND don't spawn my type.






		if(nextTYPEIDTarget.startsWith("DOOR.")==false)
		{

			//go through all other entities, if this target is "only one allowed" and any of them have this area as a target, find another one.

			Area n = getMap().getAreaOrWarpAreaByTYPEID(nextTYPEIDTarget);

			if(n!=null&&n.onlyOneAllowed())
			{
				if(getMap().isAnyoneTryingToGoToArea(n)==true)return currentAreaTYPEIDTarget;
				//if(entMan().isAnyoneStandingInArea(n)==true)return currentAreaTarget;
			}


		}

		return nextTYPEIDTarget;

	}



	//=========================================================================================================================
	public String getRandomConnectionTYPEIDFromCurrentPoint()
	{//=========================================================================================================================


		Area a = getMap().getAreaOrWarpAreaByTYPEID(currentAreaTYPEIDTarget);
		String nextTargetTYPEID = (a.connectionTYPEIDList().get(Utils.randLessThan(a.connectionTYPEIDList().size())));


		if(nextTargetTYPEID.startsWith("DOOR.")==false)
		{

			//go through all other entities, if this target is "only one allowed" and any of them have this area as a target, find another one.

			Area n = getMap().getAreaOrWarpAreaByTYPEID(nextTargetTYPEID);

			if(n!=null&&n.onlyOneAllowed())
			{
				if(getMap().isAnyoneTryingToGoToArea(n)==true)nextTargetTYPEID=currentAreaTYPEIDTarget;
				//if(entMan().isAnyoneStandingInArea(n)==true)nextTarget=currentAreaTarget;
			}

			if(n==null)
			{
				//serious error, area doesn't exit. outputs to System.err in getAreaOrWarpAreaByName
				nextTargetTYPEID=currentAreaTYPEIDTarget;
			}
		}

		return nextTargetTYPEID;

	}

}







