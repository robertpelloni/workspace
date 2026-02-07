package com.bobsgame.client.engine.entity;



import java.nio.ByteBuffer;
import java.util.ArrayList;

import org.slf4j.LoggerFactory;

import com.bobsgame.client.Texture;


import ch.qos.logback.classic.Logger;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.game.Player;
import com.bobsgame.client.engine.map.Area;
import com.bobsgame.client.engine.map.Map;
import com.bobsgame.client.engine.text.Caption;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.EntityData;
import com.bobsgame.shared.Utils;
import com.bobsgame.shared.MapData.RenderOrder;
import com.bobsgame.client.engine.text.BobFont;



//=========================================================================================================================
public class Character extends Entity
{//=========================================================================================================================



	public static Logger log = (Logger) LoggerFactory.getLogger(Character.class);



	public int standing_cycles=0;

	public int pixelsToWalk;
	public int xPixelCounter; //used for setting diagonal ratio, walking in perfect diagonal line
	public int yPixelCounter;

	public int ticksToStand=0;


	public int animationDirection=0;

	public PathFinder pathfinder;



	public int pathPosition=0;

	public int pathFindWaitTicks=0;



	public float lastMapX=0;
	public float lastMapY=0;
	public int ticksSinceMoved=0;

	public boolean moved=false;//locationChanged
	public boolean standing=false;
	public boolean running=false;




	public Texture uniqueTexture=null;//if this is set it will render with this, otherwise it will try to render the normal spriteAsset.texture in Entity.render()


	public boolean showName = false;
	public Caption nameCaption=null;

	public boolean showAccountType = false;
	public Caption accountTypeCaption=null;

	public BobColor nameColor = BobColor.white;
	public BobColor accountTypeNameColor = BobColor.white;
	public String accountTypeName = null;






	public boolean isMale=false;
	public boolean isFemale=false;


	public int standingTicksBetweenFrames = 0;
	public int rotationAnimationSpeedTicks = 160;




	//=========================================================================================================================
	public Character(Engine g)
	{//=========================================================================================================================
		super(g);

	}


	//=========================================================================================================================
	public Character(Engine g,EntityData data, Map m)
	{//=========================================================================================================================


		super(g);

		init(data, m);



		clipShadow=true;

		//setScale(1.25f);
		setAnimateThroughAllFrames(false);
		setAnimateThroughCurrentAnimation(false);

		setLoopAnimation(false);
		setRandomFrames(false);

		setTicksBetweenFrames(0);//set in shouldAnimate() based on walking speed.
		setTicksBetweenAnimationLoop(0);//should always be 0 for chars
		setRandomUpToTicksBetweenAnimationLoop(false);//should always be false for chars

		setAnimationDisabled(false);

		setIsNPC(true);
		setVoicePitch(1.0f);


	}






	//=========================================================================================================================
	public Character(Engine g,String name,Sprite sprite,Area a, Map m)
	{//=========================================================================================================================
		this(g,new EntityData(-1,name,sprite.name(),a.middleX()/2,a.middleY()/2,0,false,true,255,1.25f,8,false,false,false,false,false,0,0,false,false,false,null,""), m);

		CurrentMap().currentState.characterList.add(this);
		CurrentMap().currentState.characterByNameHashtable.put(name,this);
	}

	//=========================================================================================================================
	public void initCurrentAnimationFromSprite()
	{//=========================================================================================================================

		super.initCurrentAnimationFromSprite();


		if(getCurrentAnimationName().equals("Up"))
		{
			setAnimationByDirection(UP);
			movementDirection=UP;
		}
		if(getCurrentAnimationName().equals("Down"))
		{
			setAnimationByDirection(DOWN);
			movementDirection=DOWN;
		}
		if(getCurrentAnimationName().equals("Left"))
		{
			setAnimationByDirection(LEFT);
			movementDirection=LEFT;
		}
		if(getCurrentAnimationName().equals("Right"))
		{
			setAnimationByDirection(RIGHT);
			movementDirection=RIGHT;
		}




		setX((float)(((float)getData().spawnXPixelsHQ())-((scale()-1.0f)*w()/2.0f)));//this ADJUSTS the actual placement of the npcs by scale, since in the editor they dont line up nicely without moving them per-pixel.

		setY(getData().spawnYPixelsHQ());


	}


	//=========================================================================================================================
	public void render(float alpha)
	{//=========================================================================================================================
		if(draw==false) return;


		if(uniqueTexture==null)
		{
			super.render(alpha);
		}
		else
		{
			render(alpha,uniqueTexture,sprite.shadowTexture);
		}

	}


	//=========================================================================================================================
	@Override
	public void update()
	{//=========================================================================================================================

		super.update();

		if(sprite==null)return;






		//process behaviors
		//for(int i=0;i<behaviorList.size();i++)
		{


			//if(behaviorList.get(i).equals("walkToPointsRandomly"))
			{
				//if we have a current area

				if(currentAreaTYPEIDTarget.length()>0)
				{

					//find current area
					if(currentAreaTYPEIDTarget.startsWith("DOOR.")==false)
					{
						//get current area x and y
						Area a=getMap().getAreaOrWarpAreaByTYPEID(currentAreaTYPEIDTarget);

						if(a==null){currentAreaTYPEIDTarget = ""; return;}
						//walk towards x and y
						//boolean there = walk_to_xy_nohit( a.mapXPixelsHQ + a.widthPixelsHQ/2, a.mapYPixelsHQ + a.heightPixelsHQ/2);

						int there=0;
						if(getMap().isOutside()==false&&getMap().widthTiles1X()<100&&getMap().heightTiles1X()<100) there=walkToXYWithPathFinding(a.middleX(),a.middleY());
						//else there=walkToXYNoHitAvoidOthersPushMain(a.middleX(),a.middleY());
						else if(walkToXYNoCheckHit(a.middleX(),a.middleY()))there=1;

						//boolean there = in_range_of_area_xyxy_in_direction_by_amount(a.mapXPixelsHQ, a.mapYPixelsHQ, a.mapXPixelsHQ + a.widthPixelsHQ, a.mapYPixelsHQ + a.heightPixelsHQ, anim_dir, 0);
						//if we are there, pick a new point
						if(there==1)
						{

							//check area for variables: stay here, wait x ms, face direction

							if(a.standSpawnDirection()!=-1)
							{
								if(a.standSpawnDirection()==0) setAnimationByDirection(UP);
								if(a.standSpawnDirection()==1) setAnimationByDirection(DOWN);
								if(a.standSpawnDirection()==2) setAnimationByDirection(LEFT);
								if(a.standSpawnDirection()==3) setAnimationByDirection(RIGHT);
							}

							if(ticksToStand>0) ticksToStand-=Engine().engineTicksPassed();
							else
							{
								currentAreaTYPEIDTarget = "";

								if(connectionTYPEIDList().size()>0)currentAreaTYPEIDTarget=(connectionTYPEIDList().get(Utils.randLessThan(connectionTYPEIDList().size())));
							}
						}
						else
						{
							//set standing ticks to current ticks
							if(a.waitHereTicks()>0) ticksToStand=a.waitHereTicks();
							else ticksToStand=0;
						}
					}
				}
				else
				{
					currentAreaTYPEIDTarget = "";
					//else pick a new point
					if(connectionTYPEIDList().size()>0)currentAreaTYPEIDTarget=(connectionTYPEIDList().get(Utils.randLessThan(connectionTYPEIDList().size())));

				}
			}
		}


		//this is done here regardless of controls so that external movements still trigger animation and sound, i.e. cutscenes
		//don't need to do this for player, randomcharacter, cameraman.

		//if(this instanceof Character) //this will let through Player, RandomCharacter, etc, but NOT Entity
		if(this.getClass().equals(Character.class))//this will ONLY do Character
		{

			//log.debug(""+name());
			checkIfMoved();

			doCharacterAnimation();

		}


	}




	//===========================================================================================================================
	public void setAnimationByDirection(int dir)
	{//===========================================================================================================================

		//need to figure out is sprite has 8 directions or just 4. allow movement and animation in all 8

		//DONE: if animation doesnt exist keep it the same. (logs error)

		if(canDoCharacterMovementOrStandingAnimation())
		{
			String sequenceName="";
			if(dir==UP) sequenceName="Up";
			if(dir==DOWN) sequenceName="Down";
			if(dir==LEFT) sequenceName="Left";
			if(dir==RIGHT) sequenceName="Right";

			if(sprite.getNumberOfAnimations()>4)
			{
				if(dir==UPLEFT) sequenceName="UpLeft";
				if(dir==UPRIGHT) sequenceName="UpRight";
				if(dir==DOWNLEFT) sequenceName="DownLeft";
				if(dir==DOWNRIGHT) sequenceName="DownRight";
			}

			if(sequenceName.length()>0)
			{

				int offset = getCurrentFrameOffsetInCurrentAnimation();

				setCurrentAnimationByName(sequenceName);

				setFrameOffsetInCurrentAnimation(offset);
			}

			animationDirection=dir;

		}



	}


	//=========================================================================================================================
	public boolean canDoCharacterMovementOrStandingAnimation()
	{//=========================================================================================================================
		if(
				disableMovementAnimationForAllEntities==true
				||
				movementAnimationDisabled()==true
				//||
				//loopAnimation()==true
				||
				animatingThroughAllFrames()==true
				||
				animatingThroughCurrentAnimation()==true
		)
		{
			return false;
		}
		return true;
	}








	//=========================================================================================================================
	public void doCharacterAnimation()//does animation and turns if needed
	{//=========================================================================================================================


		if(animatingThroughCurrentAnimation() || animatingThroughAllFrames())return;


		int nextAnimDirection=animationDirection;


		if(sprite.getNumberOfAnimations()<8)
		{
			nextAnimDirection = movementDirection;
		}


		if(sprite.getNumberOfAnimations()>=8)
		{

			if(movementDirection!=animationDirection)
			{
				if(movementDirection==UP)
				{
					if(animationDirection==UP)
					{
						nextAnimDirection=UP;
					}
					else if(animationDirection==DOWN)
					{
						if(Utils.randLessThan(2)==0) nextAnimDirection=DOWNLEFT;
						else nextAnimDirection=DOWNRIGHT;
					}
					else if(animationDirection==LEFT)
					{
						nextAnimDirection=UPLEFT;
					}
					else if(animationDirection==RIGHT)
					{
						nextAnimDirection=UPRIGHT;
					}
					else if(animationDirection==UPLEFT)
					{
						nextAnimDirection=UP;
					}
					else if(animationDirection==UPRIGHT)
					{
						nextAnimDirection=UP;
					}
					else if(animationDirection==DOWNLEFT)
					{
						nextAnimDirection=LEFT;
					}
					else if(animationDirection==DOWNRIGHT)
					{
						nextAnimDirection=RIGHT;
					}
				}
				else if(movementDirection==DOWN)
				{
					if(animationDirection==UP)
					{
						if(Utils.randLessThan(2)==0) nextAnimDirection=UPLEFT;
						else nextAnimDirection=UPRIGHT;
					}
					else if(animationDirection==DOWN)
					{
						nextAnimDirection=DOWN;
					}
					else if(animationDirection==LEFT)
					{
						nextAnimDirection=DOWNLEFT;
					}
					else if(animationDirection==RIGHT)
					{
						nextAnimDirection=DOWNRIGHT;
					}
					else if(animationDirection==UPLEFT)
					{
						nextAnimDirection=LEFT;
					}
					else if(animationDirection==UPRIGHT)
					{
						nextAnimDirection=RIGHT;
					}
					else if(animationDirection==DOWNLEFT)
					{
						nextAnimDirection=DOWN;
					}
					else if(animationDirection==DOWNRIGHT)
					{
						nextAnimDirection=DOWN;
					}
				}
				else if(movementDirection==LEFT)
				{
					if(animationDirection==UP)
					{
						nextAnimDirection=UPLEFT;
					}
					else if(animationDirection==DOWN)
					{
						nextAnimDirection=DOWNLEFT;
					}
					else if(animationDirection==LEFT)
					{
						nextAnimDirection=LEFT;
					}
					else if(animationDirection==RIGHT)
					{
						if(Utils.randLessThan(2)==0) nextAnimDirection=UPRIGHT;
						else nextAnimDirection=DOWNRIGHT;
					}
					else if(animationDirection==UPLEFT)
					{
						nextAnimDirection=LEFT;
					}
					else if(animationDirection==UPRIGHT)
					{
						nextAnimDirection=UP;
					}
					else if(animationDirection==DOWNLEFT)
					{
						nextAnimDirection=LEFT;
					}
					else if(animationDirection==DOWNRIGHT)
					{
						nextAnimDirection=DOWN;
					}
				}
				else if(movementDirection==RIGHT)
				{
					if(animationDirection==UP)
					{
						nextAnimDirection=UPRIGHT;
					}
					else if(animationDirection==DOWN)
					{
						nextAnimDirection=DOWNRIGHT;
					}
					else if(animationDirection==LEFT)
					{
						if(Utils.randLessThan(2)==0) nextAnimDirection=DOWNLEFT;
						else nextAnimDirection=UPLEFT;
					}
					else if(animationDirection==RIGHT)
					{
						nextAnimDirection=RIGHT;
					}
					else if(animationDirection==UPLEFT)
					{
						nextAnimDirection=UP;
					}
					else if(animationDirection==UPRIGHT)
					{
						nextAnimDirection=RIGHT;
					}
					else if(animationDirection==DOWNLEFT)
					{
						nextAnimDirection=DOWN;
					}
					else if(animationDirection==DOWNRIGHT)
					{
						nextAnimDirection=RIGHT;
					}
				}
				else if(movementDirection==UPLEFT)
				{
					if(animationDirection==UP)
					{
						nextAnimDirection=UPLEFT;
					}
					else if(animationDirection==DOWN)
					{
						nextAnimDirection=DOWNLEFT;
					}
					else if(animationDirection==LEFT)
					{
						nextAnimDirection=UPLEFT;
					}
					else if(animationDirection==RIGHT)
					{
						nextAnimDirection=UPRIGHT;
					}
					else if(animationDirection==UPLEFT)
					{
						nextAnimDirection=UPLEFT;
					}
					else if(animationDirection==UPRIGHT)
					{
						nextAnimDirection=UP;
					}
					else if(animationDirection==DOWNLEFT)
					{
						nextAnimDirection=LEFT;
					}
					else if(animationDirection==DOWNRIGHT)
					{
						if(Utils.randLessThan(2)==0) nextAnimDirection=DOWN;
						else nextAnimDirection=RIGHT;
					}
				}
				else if(movementDirection==UPRIGHT)
				{
					if(animationDirection==UP)
					{
						nextAnimDirection=UPRIGHT;
					}
					else if(animationDirection==DOWN)
					{
						nextAnimDirection=DOWNRIGHT;
					}
					else if(animationDirection==LEFT)
					{
						nextAnimDirection=UPLEFT;
					}
					else if(animationDirection==RIGHT)
					{
						nextAnimDirection=UPRIGHT;
					}
					else if(animationDirection==UPLEFT)
					{
						nextAnimDirection=UP;
					}
					else if(animationDirection==UPRIGHT)
					{
						nextAnimDirection=UPRIGHT;
					}
					else if(animationDirection==DOWNLEFT)
					{
						if(Utils.randLessThan(2)==0) nextAnimDirection=LEFT;
						else nextAnimDirection=DOWN;
					}
					else if(animationDirection==DOWNRIGHT)
					{
						nextAnimDirection=RIGHT;
					}
				}
				else if(movementDirection==DOWNLEFT)
				{
					if(animationDirection==UP)
					{
						nextAnimDirection=UPLEFT;
					}
					else if(animationDirection==DOWN)
					{
						nextAnimDirection=DOWNLEFT;
					}
					else if(animationDirection==LEFT)
					{
						nextAnimDirection=DOWNLEFT;
					}
					else if(animationDirection==RIGHT)
					{
						nextAnimDirection=DOWNRIGHT;
					}
					else if(animationDirection==UPLEFT)
					{
						nextAnimDirection=LEFT;
					}
					else if(animationDirection==UPRIGHT)
					{
						if(Utils.randLessThan(2)==0) nextAnimDirection=UP;
						else nextAnimDirection=RIGHT;
					}
					else if(animationDirection==DOWNLEFT)
					{
						nextAnimDirection=DOWNLEFT;
					}
					else if(animationDirection==DOWNRIGHT)
					{
						nextAnimDirection=DOWN;
					}
				}
				else if(movementDirection==DOWNRIGHT)
				{
					if(animationDirection==UP)
					{
						nextAnimDirection=UPRIGHT;
					}
					else if(animationDirection==DOWN)
					{
						nextAnimDirection=DOWNRIGHT;
					}
					else if(animationDirection==LEFT)
					{
						nextAnimDirection=DOWNLEFT;
					}
					else if(animationDirection==RIGHT)
					{
						nextAnimDirection=DOWNRIGHT;
					}
					else if(animationDirection==UPLEFT)
					{
						if(Utils.randLessThan(2)==0) nextAnimDirection=UP;
						else nextAnimDirection=LEFT;
					}
					else if(animationDirection==UPRIGHT)
					{
						nextAnimDirection=RIGHT;
					}
					else if(animationDirection==DOWNLEFT)
					{
						nextAnimDirection=DOWN;
					}
					else if(animationDirection==DOWNRIGHT)
					{
						nextAnimDirection=DOWNRIGHT;
					}
				}
			}

		}




		if(animationDirection!=nextAnimDirection)
		{

			//TODO: maybe figure out how many directions player needs to turn in order to get to walking direction,
			//i.e. turn faster if they have to fully turn around, in order to make a full 180 degree turn look less dumb


			//animate 8-direction characters by rotating them in between diagonal directions with a timing delay
			//EDIT: I will have 4-direction characters have a slight delay as well.
			if(haveTicksPassedSinceLastAnimated_ResetIfTrue(rotationAnimationSpeedTicks)==true)
			{
				//notice the direction isn't set until after the delay
				setAnimationByDirection(nextAnimDirection);

				if(canDoCharacterMovementOrStandingAnimation())incrementAnimationFrameInCurrentAnimation();
			}

		}
		else
		if(standing==false)
		{

			//TODO: handle running animation
			if(running==true)
			{
				//set animation to running
				//if(PLAYER_npc->gfx==GFX_KID_yuu)PLAYER_npc->gfx=GFX_KID_yuurunning;
				//else if(PLAYER_npc->gfx==GFX_KID_youngyuu)PLAYER_npc->gfx=GFX_KID_youngyuurunning;
			}
			else
			if(running==false)
			{
				//set animation to walking
				//if(PLAYER_npc->gfx==GFX_KID_yuurunning)PLAYER_npc->gfx=GFX_KID_yuu;
				//else if(PLAYER_npc->gfx==GFX_KID_youngyuurunning)PLAYER_npc->gfx=GFX_KID_youngyuu;
			}

			if(canDoCharacterMovementOrStandingAnimation())
			{

				//doMovementAnimation();
				//=========================================================================================================================
				//public void doMovementAnimation()
				{//=========================================================================================================================


					int movementTicksBetweenFrames = 0;

					if(ticksPerPixelMoved()>=ticksPerPixel_NORMAL)//slower than normal
					{
						movementTicksBetweenFrames = (int)(ticksPerPixelMoved()*(8.0f));
					}
					else
					{
						movementTicksBetweenFrames = (int)(ticksPerPixelMoved()*(10.0f));
					}

					if(haveTicksPassedSinceLastAnimated_ResetIfTrue(movementTicksBetweenFrames)==true)
					{
						incrementAnimationFrameInCurrentAnimation();
					}

				}

			}
		}
		else
		if(standing==true)
		{
			//TODO: set animation back to walking

			//doStandingAnimation();
			//=========================================================================================================================
			//public void doStandingAnimation()
			{//=========================================================================================================================


				if(haveTicksPassedSinceLastAnimated_ResetIfTrue(standingTicksBetweenFrames)==true)
				{
					boolean standRightAway=false;
					if(standingTicksBetweenFrames==0)standRightAway = true;

					//randomize ticks between standing frames
					standingTicksBetweenFrames = 200+Utils.randUpToIncluding(600);



					boolean jittered = false;

					//if standing, jitter a pixel or two. this is added in Entity.screenXY() and does not affect real position
					if(Utils.randLessThan(6)==0)
					{
						jittered=true;
						if(standJitterX!=0)
						{
							standJitterX=0;
						}
						else
						{
							if(Utils.randLessThan(2)==0)standJitterX++;
							else standJitterX--;
						}
					}
					else
					if(Utils.randLessThan(6)==1)
					{
						jittered=true;
						if(standJitterY!=0)
						{
							standJitterY=0;
						}
						else
						{
							if(Utils.randLessThan(2)==0)standJitterY++;
							else standJitterY--;
						}
					}

					if(jittered || standRightAway)
					{

						if(canDoCharacterMovementOrStandingAnimation())
						{
							//NOTICE: this is hardcoded for characters. sequence is frames-1, (frames/2)-1
							if(getCurrentFrameOffsetInCurrentAnimation()==0)
							{
								//(frames/2)-1
								setFrameOffsetInCurrentAnimation((getCurrentAnimationNumberOfFrames()/2) - 1);
							}
							else
							{
								//frames-1
								setFrameOffsetInCurrentAnimation(getCurrentAnimationNumberOfFrames()-1);
							}

							incrementAnimationFrameInCurrentAnimation();
						}
					}


				}

			}
		}


	}









	//=========================================================================================================================
	public void checkIfMoved()
	{//=========================================================================================================================

		//if player is moving
		if(lastMapX!=Math.floor(x())||lastMapY!=Math.floor(y()))
		{
			lastMapX=(float)Math.floor(x());
			lastMapY=(float)Math.floor(y());

			ticksSinceMoved=0;

			moved=true;

			standing=false;


			if(draw==true)
			{
				//if we've moved a pixel we want to set the background priority
				//setPriorityFromFXLayer();


				if(disableShadow()==false&&sprite!=null&&sprite.hasShadow()==true&&clipShadow==true) setShadowClip();
			}

		}
		else
		{
			ticksSinceMoved+=Engine().engineTicksPassed();
			//TODO: put anything here that i want to happen immediately when the sprite stops moving

			moved=false;

			if(ticksSinceMoved>100)
			{
				standing=true; //this also takes a little bit of time to animate to standing position
			}
			else
			{
				standingTicksBetweenFrames = 0;
			}
		}


		if(standing==false)
		{
			standJitterX = 0;
			standJitterY = 0;
		}



	}




	//=========================================================================================================================
	void dontLookAtEntity(Entity e)//first id is entity to be avoiding LOOKING,second id is one to NOT BE LOOKED AT
	{//=========================================================================================================================


		if(this!=Player())
		{
			float amt1=(middleX())-(e.middleX());
			float amt2=(middleY())-(e.middleY());
			if(amt1<0) amt1=amt1*-1;
			if(amt2<0) amt2=amt2*-1;

			if(amt2>=amt1)
			{
				if(middleY()<e.middleY()) setAnimationByDirection(UP);
				if(middleY()>e.middleY()) setAnimationByDirection(DOWN);
			}
			else
			{
				if(middleX()>e.middleX()) setAnimationByDirection(RIGHT);
				if(middleX()<e.middleX()) setAnimationByDirection(LEFT);
			}
		}
		else
		{
			if(middleX()<=e.middleX())
			{
				setAnimationByDirection(LEFT);
			} //hitBoxLeft()
			if(middleX()>=e.middleX())
			{
				setAnimationByDirection(RIGHT);
			}//hitBoxRight()
			if(middleY()<=e.middleY())
			{
				setAnimationByDirection(UP);
			}//up
			if(middleY()>=e.middleY())
			{
				setAnimationByDirection(DOWN);
			}//down
			if(middleX()<=e.middleX()&&middleY()<=e.middleY())
			{
				setAnimationByDirection(UPLEFT);
			}
			if(middleX()>=e.middleX()&&middleY()<=e.middleY())
			{
				setAnimationByDirection(UPRIGHT);
			}
			if(middleY()>=e.middleY()&&middleX()<=e.middleX())
			{
				setAnimationByDirection(DOWNLEFT);
			}
			if(middleY()>=e.middleY()&&middleX()>=e.middleX())
			{
				setAnimationByDirection(DOWNRIGHT);
			}
		}


	}



	//=========================================================================================================================
	void lookAtEntity(Entity e)
	{//=========================================================================================================================


		if(this!=Player())
		{
			float amt1=(middleX())-(e.middleX());
			float amt2=(middleY())-(e.middleY());
			if(amt1<0) amt1=amt1*-1;
			if(amt2<0) amt2=amt2*-1;

			if(amt2>=amt1)
			{
				if(middleY()<e.middleY()) setAnimationByDirection(DOWN);
				if(middleY()>e.middleY()) setAnimationByDirection(UP);
			}
			else
			{
				if(middleX()>e.middleX()) setAnimationByDirection(LEFT);
				if(middleX()<e.middleX()) setAnimationByDirection(RIGHT);
			}
		}
		else
		{
			if(middleX()<=e.middleX()){setAnimationByDirection(RIGHT);}
			if(middleX()>=e.middleX()){setAnimationByDirection(LEFT);}
			if(middleY()<=e.middleY()){setAnimationByDirection(DOWN);}
			if(middleY()>=e.middleY()){setAnimationByDirection(UP);}
			if(middleX()<=e.middleX()&&middleY()<=e.middleY()){setAnimationByDirection(DOWNRIGHT);}
			if(middleX()>=e.middleX()&&middleY()<=e.middleY()){setAnimationByDirection(DOWNLEFT);}
			if(middleY()>=e.middleY()&&middleX()<=e.middleX()){setAnimationByDirection(UPRIGHT);}
			if(middleY()>=e.middleY()&&middleX()>=e.middleX()){setAnimationByDirection(UPLEFT);}
		}



	}


	//=========================================================================================================================
	void lookAtEntityButNotOppositeWalkingDirection(Entity stared_at_entity)
	{//=========================================================================================================================

		float amt1=(middleX())-(stared_at_entity.middleX());
		float amt2=(middleY())-(stared_at_entity.middleY());
		if(amt1<0) amt1=amt1*-1;
		if(amt2<0) amt2=amt2*-1;

		if(amt2>=amt1)
		{
			if(middleY()<stared_at_entity.middleY()) if(movementDirection!=UP) setAnimationByDirection(DOWN);
			if(middleY()>stared_at_entity.middleY()) if(movementDirection!=DOWN) setAnimationByDirection(UP);
		}
		else
		{
			if(middleX()>stared_at_entity.middleX()) if(movementDirection!=RIGHT) setAnimationByDirection(LEFT);
			if(middleX()<stared_at_entity.middleX()) if(movementDirection!=LEFT) setAnimationByDirection(RIGHT);
		}



	}


	//=========================================================================================================================
	public void setAppearanceFromCharacterAppearanceString(String s)
	{//=========================================================================================================================

		if(s.length()>0)
		{
			int genderIndex=-1;
			int archetypeIndex=-1;
			int hairColorIndex=-1;
			int skinColorIndex=-1;
			int eyeColorIndex=-1;
			int shirtColorIndex=-1;
			int pantsColorIndex=-1;
			int shoeColorIndex=-1;


			try{genderIndex = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(",")+1);
			try{archetypeIndex = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(",")+1);
			try{hairColorIndex = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(",")+1);
			try{skinColorIndex = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(",")+1);
			try{eyeColorIndex = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(",")+1);
			try{shirtColorIndex = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(",")+1);
			try{pantsColorIndex = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(",")+1);
			try{shoeColorIndex = Integer.parseInt(s);}catch(NumberFormatException ex){ex.printStackTrace();return;}

			generateUniqueTexture(genderIndex, archetypeIndex, shoeColorIndex, shirtColorIndex, pantsColorIndex, skinColorIndex, eyeColorIndex, hairColorIndex);

		}


	}



	//=========================================================================================================================
	public void generateUniqueTexture(int genderIndex,int archetypeIndex,int shoeColorIndex,int shirtColorIndex,int pantsColorIndex,int skinColorIndex,int eyeColorIndex,int hairColorIndex)
	{//=========================================================================================================================

		SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMcarColors").loadTextures();
		SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMeyeColors").loadTextures();
		SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMskinColors").loadTextures();
		SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMhairColors").loadTextures();
		SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshirtColors").loadTextures();
		SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMpantsColors").loadTextures();
		SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshoeColors").loadTextures();


		Sprite sprite=null;



		if(genderIndex==0) //male
		{

			isMale=true;
			isFemale=false;

			if(archetypeIndex==0) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("popularboy");
			if(archetypeIndex==1) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("hipsterboy");
			if(archetypeIndex==2) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("gothboy");
			if(archetypeIndex==3) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("toughboy");
			if(archetypeIndex==4) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("athleticboy");
			if(archetypeIndex==5) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("nerdyboy");
			if(archetypeIndex==6) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("pudgyboy");
			if(archetypeIndex==7) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("punkboy");
			if(archetypeIndex==8) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("skaterboy");
			if(archetypeIndex==9) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("thugboy");
			if(archetypeIndex==10) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("pimpleboy");
			if(archetypeIndex==11) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyBuzzedHairLongSleeve");
			if(archetypeIndex==12) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyBuzzedHairShortSleeve");
			if(archetypeIndex==13) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyBuzzedHairLongSleeveShorts");
			if(archetypeIndex==14) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyBuzzedHairShortSleeveShorts");
			if(archetypeIndex==15) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyMessyHairLongSleeve");
			if(archetypeIndex==16) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyMessyHairShortSleeve");
			if(archetypeIndex==17) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyMessyHairLongSleeveShorts");
			if(archetypeIndex==18) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyMessyHairShortSleeveShorts");
			if(archetypeIndex==19) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyNormalHairLongSleeve");
			if(archetypeIndex==20) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyNormalHairShortSleeve");
			if(archetypeIndex==21) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyNormalHairLongSleeveShorts");
			if(archetypeIndex==22) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyNormalHairShortSleeveShorts");
			if(archetypeIndex==23) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyShortHairLongSleeve");
			if(archetypeIndex==24) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyShortHairShortSleeve");
			if(archetypeIndex==25) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyShortHairLongSleeveShorts");
			if(archetypeIndex==26) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyShortHairShortSleeveShorts");

		}



		if(genderIndex==1)//female
		{

			isMale=false;
			isFemale=true;

			if(archetypeIndex==0) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("populargirl");
			if(archetypeIndex==1) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("hipstergirl");
			if(archetypeIndex==2) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("gothgirl");
			if(archetypeIndex==3) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("toughgirl");
			if(archetypeIndex==4) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("athleticgirl");
			if(archetypeIndex==5) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("nerdygirl");
			if(archetypeIndex==6) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("pudgygirl");
			if(archetypeIndex==7) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("punkgirl");
			if(archetypeIndex==8) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("skatergirl");
			if(archetypeIndex==9) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("thuggirl");
			if(archetypeIndex==10) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("pimplegirl");
			if(archetypeIndex==11) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlLongHairSkirt");
			if(archetypeIndex==12) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlLongHairSkirtHalter");
			if(archetypeIndex==13) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlLongHairJeans");
			if(archetypeIndex==14) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlLongHairJeansHalter");
			if(archetypeIndex==15) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlLongHairShortsHalter");
			if(archetypeIndex==16) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlPonytailSkirt");
			if(archetypeIndex==17) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlPonytailSkirtHalter");
			if(archetypeIndex==18) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlPonytailJeans");
			if(archetypeIndex==19) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlPonytailJeansHalter");
			if(archetypeIndex==20) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlPonytailShortsHalter");
			if(archetypeIndex==21) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlShortHairSkirt");
			if(archetypeIndex==22) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlShortHairSkirtHalter");
			if(archetypeIndex==23) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlShortHairJeans");
			if(archetypeIndex==24) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlShortHairJeansHalter");
			if(archetypeIndex==25) sprite=SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlShortHairShortsHalter");

		}



		if(sprite!=null)
		{
			if(sprite.texture==null)
			{
				sprite.loadTextures();
			}
		}


		this.sprite=sprite;

		setCurrentAnimationBySpriteFrame(getFrame());


		if(uniqueTexture!=null) uniqueTexture=GLUtils.releaseTexture(uniqueTexture);

		int eyeSet=eyeColorIndex+1;
		int skinSet=skinColorIndex+1;
		int hairSet=hairColorIndex+1;
		int shirtSet=shirtColorIndex+1;
		int pantsSet=pantsColorIndex+1;
		int shoeSet=shoeColorIndex+1;

		ByteBuffer bb=sprite.createRandomSpriteTextureByteBuffer_S(eyeSet,skinSet,hairSet,shirtSet,pantsSet,shoeSet,-1);

		uniqueTexture=GLUtils.loadTexture("random"+Utils.randLessThan(500),sprite.w(),sprite.h()*sprite.frames(),bb);



		if(this.sprite!=null)
		{

			shadowClipPerPixel=new float[(int)(sprite.w())];
			for(int i=0;i<sprite.w();i++)
				shadowClipPerPixel[i]=1.0f;
		}
	}




	//=========================================================================================================================
	public void setShowName(boolean b)
	{//=========================================================================================================================

		showName = b;

		if(name()!=null && name().length()>0)
		{
			setCharacterNameAndCaption(nameColor,name(),accountTypeNameColor,accountTypeName);
		}
		else
		{
			if(sprite!=null && sprite.displayName()!=null && sprite.displayName().length()>0)
			{
				setCharacterNameAndCaption(nameColor,sprite.displayName(),accountTypeNameColor,accountTypeName);
			}
		}

	}

	//=========================================================================================================================
	public void setShowAccountType(boolean b)
	{//=========================================================================================================================

		showAccountType = b;

		if(accountTypeName!=null)
		{
			if(accountTypeName.length()>0)
			setCharacterNameAndCaption(nameColor,name(),accountTypeNameColor,accountTypeName);
		}
	}



	//=========================================================================================================================
	public void setCharacterNameAndCaption(BobColor nameColor, String name, BobColor accountTypeNameColor, String accountTypeName)
	{//=========================================================================================================================

		this.nameColor = nameColor;
		this.setName(name);
		this.accountTypeNameColor = accountTypeNameColor;
		this.accountTypeName = accountTypeName;

		if(showName==true)
		{
			if(nameCaption==null)
			{
				if(name!=null&&name.length()>0)
				nameCaption=CaptionManager().newManagedCaption(Caption.CENTERED_OVER_ENTITY,0,-1,name,BobFont.font_normal_16_outlined_smooth,nameColor,BobColor.CLEAR,RenderOrder.ABOVE_TOP,1.0f,0);
				nameCaption.setEntity(this);
			}
			else
			{
				nameCaption.replaceText(name);
			}
		}
		else
		{
			if(nameCaption!=null)
			{
				nameCaption.deleteFadeOut();
				nameCaption=null;
			}
		}


		if(showAccountType==true)
		{
			if(accountTypeCaption==null)
			{
				if(accountTypeName!=null&&accountTypeName.length()>0)
				accountTypeCaption=CaptionManager().newManagedCaption(Caption.CENTERED_OVER_ENTITY,0,-1,accountTypeName,BobFont.font_normal_8_outlined,accountTypeNameColor,BobColor.CLEAR,RenderOrder.ABOVE_TOP,1.0f,0);
				nameCaption.setEntity(this);
			}
			else
			{
				accountTypeCaption.replaceText(accountTypeName);
			}
		}
		else
		{
			if(accountTypeCaption!=null)
			{
				accountTypeCaption.deleteFadeOut();
				accountTypeCaption=null;
			}
		}
	}



//
//	//=========================================================================================================================
//	public void setPriorityFromFXLayer()
//	{//=========================================================================================================================
//
//		//this checks the current position to see if it needs to set the background priority up or down
//
//
//
//		int under2=2;
//		int over1=1;
//
//		if(getMap().getCameraBoundsFXLayerAtXYPixels(left()+2,bottom()-2)==under2
//				||getMap().getCameraBoundsFXLayerAtXYPixels(right()-2,bottom()-2)==under2
//				||getMap().getCameraBoundsFXLayerAtXYPixels(left()+2,top()+2)==under2
//				||getMap().getCameraBoundsFXLayerAtXYPixels(right()-2,top()+2)==under2
//				||getMap().getCameraBoundsFXLayerAtXYPixels(middleX(),bottom()-(hitBoxTop()/2))==under2)
//		{
//
//			setRenderOrder(RenderOrder.GROUND);
//
//		}
//		else if(getMap().getCameraBoundsFXLayerAtXYPixels(left()+2,bottom()-2)==over1
//				||getMap().getCameraBoundsFXLayerAtXYPixels(right()-2,bottom()-2)==over1
//				||getMap().getCameraBoundsFXLayerAtXYPixels(left()+2,top()+2)==over1
//				||getMap().getCameraBoundsFXLayerAtXYPixels(right()-2,top()+2)==over1
//				||getMap().getCameraBoundsFXLayerAtXYPixels(middleX(),bottom()-(hitBoxTop()/2))==over1)
//		{
//			setRenderOrder(RenderOrder.ABOVE);
//		}
//		else
//		{
//			setRenderOrder(RenderOrder.GROUND);
//		}
//
//
//	}


	//=========================================================================================================================
	public ArrayList<Entity> getOnScreenNonCharacterEntitiesWithinRangeAmount(int amt)
	{//=========================================================================================================================


		ArrayList<Entity> list=new ArrayList<Entity>();

		for(int s=0;s<getMap().zList.size();s++)//NOTICE THIS IS USING ZLIST
		{
			Entity e=getMap().zList.get(s);

			if(e.getClass().equals(Character.class)||e.getClass().equals(RandomCharacter.class)||e.nonWalkable()==false) continue;

			if(e.equals(this)) continue;


			if(right()+amt>=e.left()&&left()-amt<=e.right()&&bottom()+amt>=e.top()&&top()-amt<=e.bottom()) list.add(e);
		}

		return list;

	}
	//=========================================================================================================================
	public boolean checkTouchingAnyEntityInEntityList(ArrayList<Entity> list,float x,float y)
	{//=========================================================================================================================

		if(Engine().hitLayerEnabled==false) return false;

		for(int s=0;s<list.size();s++)
		{
			Entity e=list.get(s);

			if(e.getClass().equals(Character.class)||e.getClass().equals(RandomCharacter.class)||e.nonWalkable()==false) continue;

			if(e.equals(this)) continue;


			if(x>=e.left()&&x<=e.right()&&y>=e.top()&&y<=e.bottom()) return true;
		}

		return false;

	}


	//=========================================================================================================================
	public boolean checkHitLayerAndTouchingAnyEntityInEntityList(ArrayList<Entity> list,float x,float y)
	{//=========================================================================================================================
		if(getMap().getHitLayerValueAtXYPixels(x,y)==false
				&&checkTouchingAnyEntityInEntityList(list,x,y)==false)
			return false;

		return true;

	}

	//=========================================================================================================================
	public boolean checkTouchingAnyOnScreenNonCharacterNonWalkableEntities(float x,float y)
	{//=========================================================================================================================

		if(Engine().hitLayerEnabled==false) return false;

		for(int s=0;s<getMap().zList.size();s++)//NOTICE THIS IS USING ZLIST
		{
			Entity e=getMap().zList.get(s);

			if(e.getClass().equals(Character.class)||e.getClass().equals(RandomCharacter.class)||e.nonWalkable()==false) continue;

			if(e.equals(this)) continue;


			if(x>=e.left()&&x<=e.right()&&y>=e.top()&&y<=e.bottom()) return true;
		}

		return false;

	}







	//=========================================================================================================================
	public void setShadowClip()
	{//=========================================================================================================================
		//check from current tile downwards for any hit detection
		//if it runs into hit detection before the shadow length, clip the shadow to % of shadow start to the start of that hit block / total shadow length


		if(shadowClipPerPixel==null)
		{
			shadowClipPerPixel=new float[(int)(sprite.w())];
			for(int i=0;i<sprite.w();i++)
				shadowClipPerPixel[i]=1.0f;
		}

		//float left = left()+2;
		//float right = right()-2;
		float bottom=(y()+(h()*shadowStart()));
		//float middle = middleX();


		float shadowLength=((float)h()*shadowSize);


		//TODO: add option to put back whole sprite clipping on/off, this is resource intensive.

		//DONE: have function that returns a list of sprites this sprite might be touching. then run through that list, much faster than even just onscreen sprites.
		//also, could render all shadows first, and then sprites, wouldn't have to check against other sprites at all. just run through zlist twice on render.

		//DONE: only do this for onscreen sprites.

		//REALIZATION: i should never have to clip against other entities, ever. your shadow will always be on the ground, and any entities in front of you will always be rendered AFTER your shadow.


		//ArrayList<Entity> list = get_ONSCREEN_entities_besides_characters_within_amt(32);

		for(int x=0;x<sprite.w();x++)
		{
			int clip=0;

			for(int y=0;y<shadowLength;y++)
			{
				if(getMap().getHitLayerValueAtXYPixels(x()+(x*scale()),bottom+y)==true
				//check_shadow_clip_hit_layer_xy_and_non_walkable_entities_besides_characters(x()+(x*scale),bottom+y)==true
				)
				{
					clip=y;
					y=(int)shadowLength;
					break;
				}
			}


			if(clip>0)
			{
				shadowClipPerPixel[x]=((float)clip/(float)shadowLength);
			}
			else
			{
				shadowClipPerPixel[x]=1.0f;
			}

		}



		//DONE: i could possibly do this for each horizontal pixel of the shadow and make it totally perfect, definitely do this.

	}



	int pathTried=0;

	public float finalPathX=0;
	public float finalPathY=0;


	//=========================================================================================================================
	/**
	 * return 0 if not there.
	 * if path is blocked, will wait 500 ticks and try again (for someone to move) 3 times, and then return -1 if still fail.
	 * return 1 if there.
	 *
	 */
	public int walkToXYWithPathFinding(float x,float y)
	{//=========================================================================================================================


		float myX=roundedMiddleX();
		float myY=roundedMiddleY();


		if(x==-1) x=myX;
		if(y==-1) y=myY;

		x=Math.round(x);
		y=Math.round(y);



		int there_yet=0;

		if(finalPathX==x&&finalPathY==y) return 1;


		//TODO: need to pathfind based on all covered hit tiles of this sprite.

		//TODO: need to check for characters that are sitting down. otherwise walks through them.

		//TODO: need to send in entire area, try to center self in target area, or just reach closest edge.



		/*
		 * if(myX==x&&myY==y)
		 * {
		 * there_yet=true;
		 * pathPosition=0;
		 * pathfinder=null;
		 * }
		 * else
		 * if(myX>=x-8&&myX<=x+8&&myY>=y-8&&myY<=y+8) //if we're within a tile, just walk straight there.
		 * {
		 * if(walk_to_xy_nohit(x, y))
		 * {
		 * there_yet = true;
		 * pathPosition=0;
		 * pathfinder=null;
		 * }
		 * }
		 * else
		 */



		{

			//if i don't have a pathfinder, make one.


			//walk from path point to path point until i reach my dest.


			if(getMap().utilityLayersLoaded==false) return 0;

			if(pathfinder==null)
			{

				pathfinder=new PathFinder(this,middleX(),middleY(),x,y,getMap().widthTiles1X(),getMap().heightTiles1X());

			}

			if(pathfinder!=null)
			{

				if(pathfinder.path!=null)
				{


					if(pathPosition<pathfinder.path.pathTiles.size()-1)
					{

						float pathX=pathfinder.path.getTileXForPathIndex(pathPosition)*8*2+8;//+8 for center of tile
						float pathY=pathfinder.path.getTileYForPathIndex(pathPosition)*8*2+8;

						//skip tiles that are in a row, starting from the NEXT position
						for(int i=pathPosition+1;i<pathfinder.path.pathTiles.size();i++)
						{
							if(pathfinder.path.getTileXForPathIndex(i)*8*2+8==pathX
									&&(i+1<pathfinder.path.pathTiles.size())
									&&pathfinder.path.getTileXForPathIndex(i+1)*8*2+8==pathX)
							{
								pathfinder.path.pathTiles.remove(i);

							}
							else break;
						}

						//skip tiles that are in a column, starting from the NEXT position
						for(int i=pathPosition+1;i<pathfinder.path.pathTiles.size();i++)
						{
							if(pathfinder.path.getTileYForPathIndex(i)*8*2+8==pathY
									&&(i+1<pathfinder.path.pathTiles.size())
									&&pathfinder.path.getTileYForPathIndex(i+1)*8*2+8==pathY)
							{
								pathfinder.path.pathTiles.remove(i);

							}
							else break;
						}



						//avoid_nearest_entity(16);

						if(walkToXYNoCheckHit(pathX,pathY)) pathPosition++;



					}
					else if(walkToXYNoCheckHit(x,y))//for the last step, just walk straight to the destination
					{
						there_yet=1;
						pathPosition=0;
						pathfinder=null;

						finalPathX=x;//we are as close as we can be.
						finalPathY=y;
					}


				}
				else
				{



					pathFindWaitTicks+=Engine().engineTicksPassed();

					//doStandingAnimation();//should be handled by checkIfMoved and doCharacterAnimation now

					if(pathFindWaitTicks>500)
					{
						pathFindWaitTicks=0;

						pathTried++;

						pathPosition=0;
						pathfinder=null;

						if(pathTried>3)
						{

							finalPathX=middleX();
							finalPathY=middleY();

							pathTried=0;
							return -1;
						}
					}



				}
			}


		}



		//figure out size of hitbox of this sprite in tiles

		//go through map in chunks of this size, staggered by individual tiles


		return there_yet;
	}






	//=========================================================================================================================
	void checkHitBoxAndWalkDirection(int dir)
	{//=========================================================================================================================

		if(ifCanMoveAPixelThisFrameSubtractAndReturnTrue()==true)
		{
			checkHitBoxAndMovePixelInDirection(dir);

			if(pixelsToWalk>0&&isWalkingIntoPlayerThisFrame==false) pixelsToWalk--;
		}
	}


	//=========================================================================================================================
	void walkDirectionNoCheckHit(int direction)
	{//=========================================================================================================================

		if(ifCanMoveAPixelThisFrameSubtractAndReturnTrue()==true)
		{

			if(direction==UP) setY(y()-1);
			if(direction==DOWN) setY(y()+1);
			if(direction==LEFT) setX(x()-1);
			if(direction==RIGHT) setX(x()+1);

			if(pixelsToWalk>0) pixelsToWalk--;

			movementDirection=direction;

		}
	}


	//=========================================================================================================================
	void walkRandomlyAroundRoomAndStop()
	{//=========================================================================================================================

		if(pixelsToWalk==0)
		{
			movementDirection=Utils.randLessThan(4);
			pixelsToWalk=(Utils.randLessThan(100))+10;
			//setTicksPerPixelMoved((Utils.randLessThan(ticksPerPixel_FASTEST-ticksPerPixel_SLOWEST))+ticksPerPixel_SLOWEST);
		}
		if(pixelsToWalk==1)
		{
			//setTicksPerPixelMoved((Utils.randLessThan(ticksPerPixel_FASTEST-ticksPerPixel_SLOWEST))+ticksPerPixel_SLOWEST);
		}

		if(ifCanMoveAPixelThisFrameSubtractAndReturnTrue()==true)
		{
			checkHitBoxAndMovePixelInDirection(movementDirection);

			if(isWalkingIntoWallThisFrame==true)
			{
				pixelsToWalk=0;
			}

			if(pixelsToWalk>0&&isWalkingIntoPlayerThisFrame==false) pixelsToWalk--;
		}
	}


	//=========================================================================================================================
	void walkRandomlyAroundRoom()
	{//=========================================================================================================================

		if(pixelsToWalk==0)
		{
			movementDirection=Utils.randLessThan(4);
			pixelsToWalk=(Utils.randLessThan(100))+10;
			//setTicksPerPixelMoved((Utils.randLessThan(ticksPerPixel_FASTEST-ticksPerPixel_SLOWEST))+ticksPerPixel_SLOWEST);
		}
		checkHitBoxAndWalkDirection(movementDirection);
	}


	//=========================================================================================================================
	int walkRandomlyWithinXYXY(int x1,int y1,int x2,int y2)
	{//=========================================================================================================================


		if(pixelsToWalk==0)
		{
			movementDirection=Utils.randLessThan(4);

			if((x2-x1)>(y2-y1))
			{
				pixelsToWalk=Utils.randLessThan(x2-x1);
			}
			else
			{
				pixelsToWalk=Utils.randLessThan(y2-y1);
			}
			//setTicksPerPixelMoved((Utils.randLessThan(ticksPerPixel_FASTEST-ticksPerPixel_SLOWEST))+ticksPerPixel_SLOWEST);
		}

		int can_walk=0;



		if(movementDirection==UP&&top()>y1) can_walk=1;
		if(movementDirection==DOWN&&bottom()<y2) can_walk=1;
		if(movementDirection==LEFT&&left()>x1) can_walk=1;
		if(movementDirection==RIGHT&&right()<x2) can_walk=1;


		if(can_walk==1) walkDirectionAvoidOtherEntities(movementDirection);
		else pixelsToWalk=0;

		if(pixelsToWalk==0) return 1;
		return 0;
	}


	//=========================================================================================================================
	void twitchAroundRoom()
	{//=========================================================================================================================

		if(pixelsToWalk==0||pixelsToWalk>5)
		{
			movementDirection=Utils.randLessThan(4);
			pixelsToWalk=(Utils.randLessThan(5))+1;
			setTicksPerPixelMoved(ticksPerPixel_FAST);
		}

		setIgnoreHitPlayer(true);

		if(ifCanMoveAPixelThisFrameSubtractAndReturnTrue()==true)
		{


			checkHitBoxAndMovePixelInDirection(movementDirection);
			if(isWalkingIntoWallThisFrame==true) pixelsToWalk=0;
			if(pixelsToWalk>0&&isWalkingIntoPlayerThisFrame==false) pixelsToWalk--;


		}

		setIgnoreHitPlayer(false);

	}


	//=========================================================================================================================
	Character findNearestCharacter()
	{//=========================================================================================================================

		Character nearest=null;

		int shortestdist=65535;



		for(int n=0;n<getMap().activeEntityList.size();n++)
		{
			Entity currentEntity=getMap().activeEntityList.get(n);

			if(this!=currentEntity
					&&
					(
							currentEntity.getClass().equals(Character.class)
							||currentEntity.getClass().equals(RandomCharacter.class)
							||currentEntity.getClass().equals(Player.class)

					))
			{

				float x=middleX()-(currentEntity.middleX());
				float y=middleY()-(currentEntity.middleY());

				x=Math.abs(x);
				y=Math.abs(y);

				int dist=(int)Math.sqrt((x*x)+(y*y));

				if(dist<shortestdist)
				{
					shortestdist=dist;
					nearest=(Character)currentEntity;
				}
			}

		}

		return nearest;
	}




	//=========================================================================================================================
	int walkToXYLRToUD(int x,int y)
	{//=========================================================================================================================

		//setTicksPerPixelMoved(speed);
		int there_yet=0;



		if(middleX()<x)
		{
			checkHitBoxAndWalkDirection(RIGHT);
			there_yet=0;
		}
		else if(middleX()>x)
		{
			checkHitBoxAndWalkDirection(LEFT);
			there_yet=0;
		}
		else if(middleY()<y)
		{
			checkHitBoxAndWalkDirection(DOWN);
			there_yet=0;
		}
		else if(middleY()>y)
		{
			checkHitBoxAndWalkDirection(UP);
			there_yet=0;
		}
		else there_yet=1;

		if(isWalkingIntoWallThisFrame==true)
		{
			if(middleY()<y)
			{
				checkHitBoxAndMovePixelInDirection(DOWN);
				there_yet=0;
			}
			else if(middleY()>y)
			{
				checkHitBoxAndMovePixelInDirection(UP);
				there_yet=0;
			}
			else if(middleX()<x)
			{
				checkHitBoxAndMovePixelInDirection(RIGHT);
				there_yet=0;
			}
			else if(middleX()>x)
			{
				checkHitBoxAndMovePixelInDirection(LEFT);
				there_yet=0;
			}
		}

		return there_yet;
	}


	//=========================================================================================================================
	int walkToXYUDToLR(int toX,int toY)
	{//=========================================================================================================================

		//setTicksPerPixelMoved(speed);

		int there_yet=0;



		if(middleY()<toY)
		{
			checkHitBoxAndWalkDirection(DOWN);
			there_yet=0;
		}
		else if(middleY()>toY)
		{
			checkHitBoxAndWalkDirection(UP);
			there_yet=0;
		}
		else if(middleX()<toX)
		{
			checkHitBoxAndWalkDirection(RIGHT);
			there_yet=0;
		}
		else if(middleX()>toX)
		{
			checkHitBoxAndWalkDirection(LEFT);
			there_yet=0;
		}
		else there_yet=1;

		if(isWalkingIntoWallThisFrame==true)
		{
			if(middleX()<toX)
			{
				checkHitBoxAndMovePixelInDirection(RIGHT);
				there_yet=0;
			}
			else if(middleX()>toX)
			{
				checkHitBoxAndMovePixelInDirection(LEFT);
				there_yet=0;
			}
			else if(middleY()<toY)
			{
				checkHitBoxAndMovePixelInDirection(DOWN);
				there_yet=0;
			}
			else if(middleY()>toY)
			{
				checkHitBoxAndMovePixelInDirection(UP);
				there_yet=0;
			}
		}


		return there_yet;
	}



	//=========================================================================================================================
	public boolean walkToXYNoCheckHit(float toX,float toY)
	{//=========================================================================================================================

		//this was created for randomcharacters and overrode the old walktoXYNoCheckHit but i moved it into character

		if(toX==-1)toX=roundedMiddleX();
		if(toY==-1)toY=roundedMiddleY();

		toX = Math.round(toX);
		toY = Math.round(toY);



		boolean there=false;

		if(roundedMiddleX()==toX&&roundedMiddleY()==toY)
		{
			there=true;

		}
		else
		{

			float xDist=Math.abs(roundedMiddleX()-toX);
			float yDist=Math.abs(roundedMiddleY()-toY);


			int horizontalMovementDir = -1;
			int verticalMovementDir = -1;

			if(roundedMiddleX()>toX)
			{
				setX(x()-pixelsToMoveThisFrame);

				//if i went past it, go exactly to targetX
				if(roundedMiddleX()<toX)setX(toX-middleOffsetX());

				horizontalMovementDir=LEFT;
			}

			if(roundedMiddleX()<toX)
			{
				setX(x()+pixelsToMoveThisFrame);

				//if i went past it, go exactly to targetX
				if(roundedMiddleX()>toX)setX(toX-middleOffsetX());

				horizontalMovementDir=RIGHT;
			}


			if(roundedMiddleY()>toY)
			{
				setY(y()-pixelsToMoveThisFrame);

				if(roundedMiddleY()<toY)setY(toY-middleOffsetY());

				verticalMovementDir=UP;
			}
			if(roundedMiddleY()<toY)
			{
				setY(y()+pixelsToMoveThisFrame);

				if(roundedMiddleY()>toY)setY(toY-middleOffsetY());

				verticalMovementDir=DOWN;
			}

			if(horizontalMovementDir==LEFT&&verticalMovementDir==UP)movementDirection=UPLEFT;
			if(horizontalMovementDir==RIGHT&&verticalMovementDir==UP)movementDirection=UPRIGHT;
			if(horizontalMovementDir==LEFT&&verticalMovementDir==DOWN)movementDirection=DOWNLEFT;
			if(horizontalMovementDir==RIGHT&&verticalMovementDir==DOWN)movementDirection=DOWNRIGHT;
			if(horizontalMovementDir==RIGHT&&verticalMovementDir==-1)movementDirection=RIGHT;
			if(horizontalMovementDir==LEFT&&verticalMovementDir==-1)movementDirection=LEFT;
			if(horizontalMovementDir==-1&&verticalMovementDir==UP)movementDirection=UP;
			if(horizontalMovementDir==-1&&verticalMovementDir==DOWN)movementDirection=DOWN;

			if(sprite.getNumberOfAnimations()==4)
			{
				if(movementDirection==UPLEFT){if(xDist>yDist)movementDirection=LEFT;else movementDirection=UP;}
				if(movementDirection==UPRIGHT){if(xDist>yDist)movementDirection=RIGHT;else movementDirection=UP;}
				if(movementDirection==DOWNLEFT){if(xDist>yDist)movementDirection=LEFT;else movementDirection=DOWN;}
				if(movementDirection==DOWNRIGHT){if(xDist>yDist)movementDirection=RIGHT;else movementDirection=DOWN;}
			}

			if(pixelsToWalk>0)pixelsToWalk--;


			if(roundedMiddleX()==toX&&roundedMiddleY()==toY)there=true;

		}

		return there;
	}

	//=========================================================================================================================
	boolean walkToXYNoCheckHitOLD(float x,float y)
	{//=========================================================================================================================

		setIgnoreHitPlayer(false);



		if(x==-1) x=roundedMiddleX();
		if(y==-1) y=roundedMiddleY();

		x=Math.round(x);
		y=Math.round(y);



		boolean there_yet=false;

		if(roundedMiddleX()==x&&roundedMiddleY()==y)
		{
			there_yet=true;

			yPixelCounter=0;
			xPixelCounter=0;

			//stand();
		}
		else
		{

			int newAnimDir=-1;

			//while(can_walk()==true&&(myX!=x||myY!=y))
			{



				float xdistance=Math.abs(roundedMiddleX()-x);
				float ydistance=Math.abs(roundedMiddleY()-y);


				if(xdistance>=ydistance)
				{

					if(roundedMiddleX()>x)
					{
						setX(x()-pixelsToMoveThisFrame);

						if(roundedMiddleX()<x)
						{
							setX(x-(middleX()-x()));
						}

						movementDirection=LEFT;
						if(ydistance<=xdistance) newAnimDir=LEFT;
					}
					if(roundedMiddleX()<x)
					{
						setX(x()+pixelsToMoveThisFrame);
						if(roundedMiddleX()>x)setX(x-(middleX()-x()));
						movementDirection=RIGHT;
						if(ydistance<=xdistance) newAnimDir=RIGHT;
					}

				}
				else if(ydistance>=xdistance)
				{
					if(roundedMiddleY()>y)
					{
						setY(y()-pixelsToMoveThisFrame);
						if(roundedMiddleY()<y)setY(y-(middleY()-y()));
						movementDirection=UP;
						if(ydistance>xdistance&&Math.abs(ydistance-xdistance)>2) newAnimDir=UP;
					}
					if(roundedMiddleY()<y)
					{
						setY(y()+pixelsToMoveThisFrame);
						if(roundedMiddleY()>y)setY(y-(middleY()-y()));
						movementDirection=DOWN;
						if(ydistance>xdistance&&Math.abs(ydistance-xdistance)>2) newAnimDir=DOWN;
					}
				}


				if(pixelsToWalk>0) pixelsToWalk--;
			}

			if(roundedMiddleX()==x&&roundedMiddleY()==y) there_yet=true;


		}
		return there_yet;
	}


	//=========================================================================================================================
	boolean walkToXYUntilHitWall(float x,float y)
	{//=========================================================================================================================

		setIgnoreHitPlayer(false);



		if(x==-1) x=roundedMiddleX();
		if(y==-1) y=roundedMiddleY();

		x=Math.round(x);
		y=Math.round(y);



		boolean there_yet=false;

		if(roundedMiddleX()==x&&roundedMiddleY()==y)
		{
			there_yet=true;

			yPixelCounter=0;
			xPixelCounter=0;

			//stand();
		}
		else
		{

			int newAnimDir=-1;

			//while(can_walk()==true&&(myX!=x||myY!=y))
			{



				float xdistance=Math.abs(roundedMiddleX()-x);
				float ydistance=Math.abs(roundedMiddleY()-y);



				int moved=0;

				if(xdistance>=ydistance)
				{
					//setting movementDirection here is useless.
					if(roundedMiddleX()>x)
					{
						while(pixelsToMoveThisFrame>1.0f)
						{
							pixelsToMoveThisFrame-=1.0f;
							if(checkHitBoxAndMovePixelInDirection(LEFT))moved++;
						}

						setX(x()-pixelsToMoveThisFrame);
						if(roundedMiddleX()<x) setX(x-(middleX()-x()));//if we overshot the goal, rewind.


						movementDirection=LEFT;
						if(ydistance<=xdistance) newAnimDir=LEFT;

					}


					if(roundedMiddleX()<x)
					{

						while(pixelsToMoveThisFrame>1.0f)
						{
							pixelsToMoveThisFrame-=1.0f;
							if(checkHitBoxAndMovePixelInDirection(RIGHT))moved++;
						}

						setX(x()+pixelsToMoveThisFrame);
						if(roundedMiddleX()>x) setX(x-(middleX()-x()));

						movementDirection=RIGHT;
						if(ydistance<=xdistance) newAnimDir=RIGHT;

					}

				}
				else if(ydistance>=xdistance)
				{
					if(roundedMiddleY()>y)
					{

						while(pixelsToMoveThisFrame>1.0f)
						{
							pixelsToMoveThisFrame-=1.0f;
							if(checkHitBoxAndMovePixelInDirection(UP))moved++;
						}

						setY(y()-pixelsToMoveThisFrame);
						if(roundedMiddleY()<y) setY(y-(middleY()-y()));

						movementDirection=UP;
						if(ydistance>xdistance&&Math.abs(ydistance-xdistance)>2) newAnimDir=UP;

					}


					if(roundedMiddleY()<y)
					{
						while(pixelsToMoveThisFrame>1.0f)
						{
							pixelsToMoveThisFrame-=1.0f;
							if(checkHitBoxAndMovePixelInDirection(DOWN))moved++;
						}

						setY(y()+pixelsToMoveThisFrame);
						if(roundedMiddleY()>y) setY(y-(middleY()-y()));

						movementDirection=DOWN;
						if(ydistance>xdistance&&Math.abs(ydistance-xdistance)>2) newAnimDir=DOWN;

					}
				}


				if(pixelsToWalk>0) pixelsToWalk--;
			}

			if(roundedMiddleX()==x&&roundedMiddleY()==y) there_yet=true;

			if(moved==false) there_yet=true;


		}
		return there_yet;
	}


	//=========================================================================================================================
	int walkToXYWithBasicHitCheck(float x,float y)
	{//=========================================================================================================================

		setIgnoreHitPlayer(true);


		if(x==-1) x=middleX();
		if(y==-1) y=middleY();

		int there_yet=0;
		int direction=0;

		if(ifCanMoveAPixelThisFrameSubtractAndReturnTrue()==true)
		{



			//WALK PERFECT DIAGONAL

			float ydistance=0;
			float xdistance=0;
			if(middleY()>y) ydistance=middleY()-y;
			if(middleY()<y) ydistance=y-middleY();

			if(middleX()>x) xdistance=middleX()-x;
			if(middleX()<x) xdistance=x-middleX();



			float x_to_y_ratio=0;
			if(ydistance!=0) x_to_y_ratio=xdistance/ydistance;
			float y_to_x_ratio=0;
			if(xdistance!=0) y_to_x_ratio=ydistance/xdistance;


			if(xdistance>=ydistance||y_to_x_ratio<yPixelCounter)
			{
				if(middleX()>x)
				{
					mapX--;
					if(isWalkingIntoWallThisFrame==false&&ydistance<=xdistance) direction=LEFT;
				}
				if(middleX()<x)
				{
					mapX++;
					if(isWalkingIntoWallThisFrame==false&&ydistance<=xdistance) direction=RIGHT;
				}
				xPixelCounter++;
				yPixelCounter=0;
			}

			if(ydistance>=xdistance||x_to_y_ratio<xPixelCounter)
			{
				if(middleY()>y)
				{
					mapY--;
					if(ydistance>xdistance) direction=UP;
				}
				if(middleY()<y)
				{
					mapY++;
					if(ydistance>xdistance) direction=DOWN;
				}
				yPixelCounter++;
				xPixelCounter=0;
			}



			if(pixelsToWalk>0&&isWalkingIntoPlayerThisFrame==false) pixelsToWalk--;


		}

		if(middleX()==x&&middleY()==y)
		{
			there_yet=1;

			yPixelCounter=0;
			xPixelCounter=0;

		}

		return there_yet;
	}



	//=========================================================================================================================
	int walkToXYNoHitAvoidOthersPushMain(float x,float y)
	{//=========================================================================================================================

		if(Player()==null)
		{
			log.error("Player null in walk_to_xy_nohit_avoidothers_pushmain()");
			return 0;
		}


		setIgnoreHitPlayer(true);


		int there_yet=0;

		float myX=roundedMiddleX();
		float myY=roundedMiddleY();

		x = Math.round(x);
		y = Math.round(y);

		if(x==-1) x=myX;
		if(y==-1) y=myY;

		if(myX==x&&myY==y)
		{
			there_yet=1;
		}
		else
		{

			if(ifCanMoveAPixelThisFrameSubtractAndReturnTrue()==true)
			{




				Character nearestentity=findNearestCharacter();


				int collide=0;
				int hitPlayer=0;

				//WALK PERFECT DIAGONAL
				float xdistance=Math.abs(myX-x);
				float ydistance=Math.abs(myY-y);



				float x_to_y_ratio=0;
				if(ydistance!=0) x_to_y_ratio=xdistance/ydistance;

				float y_to_x_ratio=0;
				if(xdistance!=0) y_to_x_ratio=ydistance/xdistance;



				if(ydistance>=xdistance||x_to_y_ratio<xPixelCounter) //walk the greater distance first, up/down vs hitBoxLeft()/hitBoxRight()
				{
					if(myY<y)//walking down
					{

						if(isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity,12)==true)
						{
							if(nearestentity==Player())
							{
								hitPlayer=1;

							}
							//else
							if((animationDirection==UP&&nearestentity.middleY()<=middleY())||(animationDirection==DOWN&&nearestentity.middleY()>=middleY()))
								if(animationDirection!=nearestentity.animationDirection||ticksPerPixelMoved()<=nearestentity.ticksPerPixelMoved())
								{
									if(myX<nearestentity.middleX())
									{
										setX(x()-1);
										collide=1;
									}
									else
									{
										setX(x()+1);
										collide=1;
									}
								}
						}
						//else
						{
							mapY++;
							yPixelCounter++;
							xPixelCounter=0;
							standing_cycles=0;

						}



					}
					if(myY>y)
					{
						if(isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity,13)==true)
						{
							if(nearestentity==Player())
							{
								hitPlayer=1;
							}
							//else
							if((animationDirection==UP&&nearestentity.middleY()<=middleY())||(animationDirection==DOWN&&nearestentity.middleY()>=middleY()))
								if(animationDirection!=nearestentity.animationDirection||ticksPerPixelMoved()<=nearestentity.ticksPerPixelMoved())
								//if(standing_cycles==0&&nearestentity.standing_cycles==0)
								{
									if(myX<=nearestentity.middleX())
									{
										setX(x()-1);
										collide=1;
									} //else walk hitBoxLeft() if slightly hitBoxLeft()
									else
									{
										setX(x()+1);
										collide=1;
									}		//else walk hitBoxRight()
								}
						}
						//else
						{
							mapY--;
							yPixelCounter++;
							xPixelCounter=0;
							standing_cycles=0;

						}

					}
				}

				if(xdistance>=ydistance||y_to_x_ratio<yPixelCounter)
				{
					if(myX<x)
					{
						if(isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity,12)==true)
						{
							if(nearestentity==Player())
							{
								hitPlayer=1;
							}
							//else
							if((animationDirection==LEFT&&nearestentity.middleX()<=middleX())||(animationDirection==RIGHT&&nearestentity.middleX()>=middleX()))
								if(animationDirection!=nearestentity.animationDirection||ticksPerPixelMoved()<=nearestentity.ticksPerPixelMoved())
								//if(standing_cycles==0&&nearestentity.standing_cycles==0)
								{
									if(middleY()<nearestentity.middleY())
									{
										setY(y()-1);
										collide=1;
									} //else walk up if slightly above
									else
									{
										setY(y()+1);
										collide=1;
									}			//else walk down

								}
						}
						//else
						{

							mapX++;
							xPixelCounter++;
							yPixelCounter=0;
							standing_cycles=0;

						}

					}



					if(myX>x)
					{
						if(isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity,13)==true)
						{
							if(nearestentity==Player())
							{
								hitPlayer=1;
							}
							//else
							if((animationDirection==LEFT&&nearestentity.middleX()<=middleX())||(animationDirection==RIGHT&&nearestentity.middleX()>=middleX()))
								if(animationDirection!=nearestentity.animationDirection||ticksPerPixelMoved()<=nearestentity.ticksPerPixelMoved())
								//if(standing_cycles==0&&nearestentity.standing_cycles==0)
								{
									if(middleY()<=nearestentity.middleY())
									{
										setY(y()-1);
										collide=1;
									} //else walk up if slightly above
									else
									{
										setY(y()+1);
										collide=1;
									}			//else walk down
								}
						}
						//else
						{
							mapX--;
							xPixelCounter++;
							yPixelCounter=0;
							standing_cycles=0;

						}

					}
				}

				if(collide==1)
					if(nearestentity.animationDirection==animationDirection&&nearestentity.ticksPerPixelMoved()==ticksPerPixelMoved())
					{
						//walking_speed+=GLOBALSPEED*1;
					}

				if(hitPlayer==1)
				{
					float nx=middleX();
					float ny=middleY();
					float sx=nearestentity.middleX();
					float sy=nearestentity.middleY();

					int wd=nearestentity.movementDirection;

					if(nx>sx&&ny<sy) wd=(DOWNLEFT);
					else if(nx<sx&&ny<sy) wd=(DOWNRIGHT);
					else if(ny>sy&&nx>sx) wd=(UPLEFT);
					else if(ny>sy&&nx<sx) wd=(UPRIGHT);
					else if(nx>sx) wd=(LEFT);
					else if(nx<sx) wd=(RIGHT);
					else if(ny>sy) wd=(UP);
					else if(ny<sy) wd=(DOWN);

					//nearestentity.ms=nearestentity.walking_speed*2;
					//PLAYER_check_hit_move_pixel_animate(wd);
					//nearestentity.animateInDirection(wd);


				}

				if(pixelsToWalk>0&&isWalkingIntoPlayerThisFrame==false) pixelsToWalk--;

			}

		}
		return there_yet;


	}


	//=========================================================================================================================
	int walkToXYStopForOtherEntitiesWithinAmt(float x,float y,int amt)//walk_to_xy_stop_for_other_entitys_amt
	{//=========================================================================================================================

		setIgnoreHitPlayer(true);
		//setTicksPerPixelMoved(speed);

		int there_yet=0;



		if(x==-1) x=middleX();
		if(y==-1) y=middleY();

		if(middleX()==x&&middleY()==y)
		{
			there_yet=1;

		}
		else
		{

			if(ifCanMoveAPixelThisFrameSubtractAndReturnTrue()==true)
			{


				Entity n=findNearestEntity();

				/*
				 * if(nearest_entity!=null)
				 * {
				 * if(standing_cycles!=0)
				 * {
				 * nearestentity=(NPC*)nearest_entity;
				 * standing_cycles--;
				 * }
				 * else
				 * {
				 * nearest_entity=(struct NPC*)nearestentity;
				 * standing_cycles=Utils.r(10);
				 * }
				 * }
				 * else
				 * {
				 * nearest_entity=(struct NPC*)nearestentity;
				 * nearestentity=(NPC*)nearest_entity;
				 * }
				 */



				//WALK PERFECT DIAGONAL

				float ydistance=0;
				float xdistance=0;
				if(middleY()>y) ydistance=middleY()-y;
				if(middleY()<y) ydistance=y-middleY();

				if(middleX()>x) xdistance=middleX()-x;
				if(middleX()<x) xdistance=x-middleX();



				float x_to_y_ratio=0;
				if(ydistance!=0) x_to_y_ratio=xdistance/ydistance;

				float y_to_x_ratio=0;
				if(xdistance!=0) y_to_x_ratio=ydistance/xdistance;



				if(ydistance>=xdistance||x_to_y_ratio<xPixelCounter) //walk the greater distance first, up/down vs hitBoxLeft()/hitBoxRight()
				{
					if(middleY()<y)//walking down
					{

						if(!((
								(left()>=n.left()&&left()<=n.right())||
										(right()>=n.left()&&right()<=n.right())||
										(n.left()>=left()&&n.left()<=right())||
								(n.right()>=left()&&n.right()<=right())
								)
								&&(bottom()<=n.top())
								&&(bottom()>=n.top()-amt)))
						{
							mapY++;
							yPixelCounter++;
							xPixelCounter=0;
							standing_cycles=0;

						}


					}

					if(middleY()>y)//walking up
					{
						if(!((
								(left()>=n.left()&&left()<=n.right())||
										(right()>=n.left()&&right()<=n.right())||
										(n.left()>=left()&&n.left()<=right())||
								(n.right()>=left()&&n.right()<=right())
								)
								&&(top()>=n.bottom())
								&&(top()<=n.bottom()+amt)))
						{
							mapY--;
							yPixelCounter++;
							xPixelCounter=0;
							standing_cycles=0;

						}

					}
				}


				if(xdistance>=ydistance||y_to_x_ratio<yPixelCounter)
				{
					if(middleX()<x)//moving hitBoxRight()
					{

						if(!((
								(top()>=n.top()&&top()<=n.bottom())||
								(bottom()>=n.top()&&bottom()<=n.bottom())
								)
								&&(right()<=n.left())
								&&(right()>=n.left()-amt)))
						{

							mapX++;
							xPixelCounter++;
							yPixelCounter=0;
							standing_cycles=0;

						}

					}



					if(middleX()>x)
					{
						if(!((
								(top()>=n.top()&&top()<=n.bottom())||
								(bottom()>=n.top()&&bottom()<=n.bottom())
								)
								&&(left()>=n.right())
								&&(left()<=n.right()+amt)))
						{
							mapX--;
							xPixelCounter++;
							yPixelCounter=0;
							standing_cycles=0;

						}

					}
				}


				if(pixelsToWalk>0&&isWalkingIntoPlayerThisFrame==false) pixelsToWalk--;


			}

		}
		return there_yet;
	}


	//=========================================================================================================================
	void walkDirectionAvoidOtherEntities(int direction)
	{//=========================================================================================================================

		if(ifCanMoveAPixelThisFrameSubtractAndReturnTrue()==true)
		{




			Entity n=findNearestEntity();

			if(direction==DOWN)
			{
				if(isEntityHitBoxTouchingMyHitBoxByAmount(n,8+Utils.randLessThan(6))==true)
				{
					if(middleX()<=n.middleX()) setX(x()-Utils.randLessThan(2));
					else setX(x()+Utils.randLessThan(2));
				}
				else
				{
					checkHitBoxAndMovePixelInDirection(DOWN);
				}
				direction=DOWN;
			}

			if(direction==UP)
			{
				if(isEntityHitBoxTouchingMyHitBoxByAmount(n,8+Utils.randLessThan(6))==true)
				{
					if(middleX()<n.middleX()) setX(x()-Utils.randLessThan(2)); //else walk hitBoxLeft() if slightly hitBoxLeft()
					else setX(x()+Utils.randLessThan(2));			//else walk hitBoxRight()
				}
				else
				{
					checkHitBoxAndMovePixelInDirection(UP);
				}
				direction=UP;
			}

			if(direction==RIGHT)
			{
				if(isEntityHitBoxTouchingMyHitBoxByAmount(n,8+Utils.randLessThan(6))==true)
				{
					if(middleY()<=n.middleY()) setY(y()-Utils.randLessThan(2)); //else walk up if slightly above
					else setY(y()+Utils.randLessThan(2));			//else walk down
				}
				else
				{
					checkHitBoxAndMovePixelInDirection(RIGHT);
				}
				direction=RIGHT;
			}

			if(direction==LEFT)
			{
				if(isEntityHitBoxTouchingMyHitBoxByAmount(n,8+Utils.randLessThan(6))==true)
				{
					if(middleY()<n.middleY()) setY(y()-Utils.randLessThan(2)); //else walk up if slightly above
					else setY(y()+Utils.randLessThan(2));			//else walk down
				}
				else
				{
					checkHitBoxAndMovePixelInDirection(LEFT);
				}
				direction=LEFT;
			}


			if(pixelsToWalk>0&&isWalkingIntoPlayerThisFrame==false) pixelsToWalk--;

			movementDirection=direction;


		}
	}


	///TEMP TEMP TEMP



	//=========================================================================================================================
	boolean walkToXYIntelligentHitPushOthers(float x,float y)
	{//=========================================================================================================================

		if(Player()==null)
		{
			log.error("Player null in walk_to_xy_intelligenthit_pushothers()");
			return false;
		}


		setIgnoreHitPlayer(true);

		boolean there_yet=false;



		if(x==-1) x=middleX();
		if(y==-1) y=middleY();



		if(middleX()==x&&middleY()==y)
		{
			there_yet=true;
		}
		else
		{


			if(ifCanMoveAPixelThisFrameSubtractAndReturnTrue()==true)
			{

				float xdistance=middleX()-x;
				float ydistance=middleY()-y;

				if(xdistance<0) xdistance*=-1;
				if(ydistance<0) ydistance*=-1;

				int direction=0;


				Entity n=findNearestEntity();


				if(ydistance>=xdistance)//walk the greater distance first, up/down vs hitBoxLeft()/hitBoxRight()
				{
					if(middleY()<y)
					{
						if(isEntityHitBoxTouchingMyHitBoxByAmount(n,7)==true)
						{
							if(n==Player())
							{

								if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN)==false) Player().mapY++;

								if(middleX()<Player().middleX())
								{
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT)==false) Player().mapX++;
								}
								else
								{
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT)==false) Player().mapX--;
								}
							}
							else
							{
								n.checkHitBoxAndMovePixelInDirection(DOWN);

								if(middleX()<=n.middleX())
								{
									n.checkHitBoxAndMovePixelInDirection(RIGHT);
								}
								else
								{
									n.checkHitBoxAndMovePixelInDirection(LEFT);
								}
							}
							direction=DOWN;
						}


						if(checkHitBoxAndMovePixelInDirection(DOWN)==false||isEntityHitBoxTouchingMyHitBoxByAmount(n,7)==true)
						{
							if(movementDirection!=LEFT&&movementDirection!=RIGHT)
							{
								if(Utils.randLessThan(2)==0) movementDirection=LEFT;
								else movementDirection=RIGHT;
							}
						}
						else
						{
							movementDirection=4;
							direction=DOWN;
						}


					}

					///======
					///======
					///======
					///======


					if(middleY()>y)
					{
						if(isEntityHitBoxTouchingMyHitBoxByAmount(n,7)==true)
						{
							if(n==Player())
							{
								if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP)==false) Player().mapY--;

								if(middleX()<Player().middleX())
								{
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT)==false) Player().mapX++;
								}
								else
								{
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT)==false) Player().mapX--;
								}
							}
							else
							{

								n.checkHitBoxAndMovePixelInDirection(UP);

								if(middleX()<n.middleX())
								{
									n.checkHitBoxAndMovePixelInDirection(RIGHT);
								}
								else
								{
									n.checkHitBoxAndMovePixelInDirection(LEFT);
								}
							}

							direction=UP;
						}

						{
							if(checkHitBoxAndMovePixelInDirection(UP)==false||isEntityHitBoxTouchingMyHitBoxByAmount(n,7)==true)
							{
								if(movementDirection!=LEFT&&movementDirection!=RIGHT)
								{
									if(Utils.randLessThan(2)==0) movementDirection=LEFT;
									else movementDirection=RIGHT;
								}
							}
							else
							{
								movementDirection=4;
								direction=UP;
							}
						}
					}

				}
				///===========================================
				if(xdistance>ydistance)
				{
					if(middleX()<x)
					{
						if(isEntityHitBoxTouchingMyHitBoxByAmount(n,7)==true)
						{
							if(n==Player())
							{

								if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT)==false) n.mapX++;

								if(middleY()>Player().middleY())
								{
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP)==false) n.mapY--;
								}
								else
								{
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN)==false) n.mapY++;
								}
							}
							else
							{

								n.checkHitBoxAndMovePixelInDirection(RIGHT);

								if(middleY()>=n.middleY())
								{
									n.checkHitBoxAndMovePixelInDirection(UP);
								}
								else
								{
									n.checkHitBoxAndMovePixelInDirection(DOWN);
								}
							}

							direction=RIGHT;
						}

						{
							if(checkHitBoxAndMovePixelInDirection(RIGHT)==false||isEntityHitBoxTouchingMyHitBoxByAmount(n,7)==true)
							{
								if(movementDirection!=UP&&movementDirection!=DOWN)
								{
									if(Utils.randLessThan(2)==0) movementDirection=UP;
									else movementDirection=DOWN;
								}
							}
							else
							{
								movementDirection=4;
								direction=RIGHT;
							}
						}

					}

					if(middleX()>x)
					{
						if(isEntityHitBoxTouchingMyHitBoxByAmount(n,7)==true)
						{
							if(n==Player())
							{
								//push main sprite hitBoxLeft()
								if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT)==false) n.mapX--;

								if(middleY()>=n.middleY())
								{//push main sprite up
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP)==false) n.mapY--;
								}
								else
								{//push main sprite down
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN)==false) n.mapY++;
								}
							}
							else
							{

								n.checkHitBoxAndMovePixelInDirection(LEFT);

								if(middleY()>n.middleY())
								{
									n.checkHitBoxAndMovePixelInDirection(UP);
								}
								else
								{
									n.checkHitBoxAndMovePixelInDirection(DOWN);
								}
							}

							direction=LEFT;
						}

						{
							if(checkHitBoxAndMovePixelInDirection(LEFT)==false||isEntityHitBoxTouchingMyHitBoxByAmount(n,7)==true)
							{
								if(movementDirection!=UP&&movementDirection!=DOWN)
								{
									if(Utils.randLessThan(2)==0) movementDirection=UP;
									else movementDirection=DOWN;
								}
							}
							else
							{
								movementDirection=4;
								direction=LEFT;
							}
						}

					}
				}

				if(movementDirection==UP)
				{
					if(checkHitBoxAndMovePixelInDirection(UP)==false||isEntityHitBoxTouchingMyHitBoxByAmount(n,10+Utils.randLessThan(6))==true)
					{
						movementDirection=4;
					}
					else direction=UP;
				}
				else if(movementDirection==DOWN)
				{
					if(checkHitBoxAndMovePixelInDirection(DOWN)==false||isEntityHitBoxTouchingMyHitBoxByAmount(n,10+Utils.randLessThan(6))==true)
					{
						movementDirection=4;
					}
					else direction=DOWN;
				}
				else if(movementDirection==LEFT)
				{
					if(checkHitBoxAndMovePixelInDirection(LEFT)==false||isEntityHitBoxTouchingMyHitBoxByAmount(n,10+Utils.randLessThan(6))==true)
					{
						movementDirection=4;
					}
					else direction=LEFT;
				}
				else if(movementDirection==RIGHT)
				{
					if(checkHitBoxAndMovePixelInDirection(RIGHT)==false||isEntityHitBoxTouchingMyHitBoxByAmount(n,10+Utils.randLessThan(6))==true)
					{
						movementDirection=4;
					}
					else direction=RIGHT;
				}


				if(pixelsToWalk>0&&isWalkingIntoPlayerThisFrame==false) pixelsToWalk--;

			}


		}
		return there_yet;
	}


	//=========================================================================================================================
	boolean walkToXYIntelligentHitAvoidOthers(float x,float y)
	{//=========================================================================================================================

		setIgnoreHitPlayer(true);
		//setTicksPerPixelMoved(speed);

		boolean there_yet=false;
		int avoided=0;



		if(x==-1) x=middleX();
		if(y==-1) y=middleY();

		if(middleX()==x&&middleY()==y)
		{
			there_yet=true;
		}
		else
		{

			if(ifCanMoveAPixelThisFrameSubtractAndReturnTrue()==true)
			{

				float xdistance=middleX()-x;
				float ydistance=middleY()-y;

				if(xdistance<0) xdistance*=-1;
				if(ydistance<0) ydistance*=-1;

				int direction=0;
				Entity nearestentity=findNearestEntity();

				if(ydistance>=xdistance) //walk the greater distance first, up/down vs hitBoxLeft()/hitBoxRight()
				{
					if(middleY()<y)
					{
						if(isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity,10+Utils.randLessThan(6))==true)
						{
							{
								avoided=Utils.randLessThan(2);
								if(middleX()<=nearestentity.middleX())
								{
									if(avoided==1) checkHitBoxAndMovePixelInDirection(LEFT);
									movementDirection=4;
								}
								else
								{
									if(avoided==1) checkHitBoxAndMovePixelInDirection(RIGHT);
									movementDirection=4;
								}
							}
							direction=DOWN;
						}

						if(avoided==0)
						{
							if(checkHitBoxAndMovePixelInDirection(DOWN)==false)
							{
								if(movementDirection!=LEFT&&movementDirection!=RIGHT)
								{
									if(Utils.randLessThan(2)==0) movementDirection=LEFT;
									else movementDirection=RIGHT;
								}
							}
							else
							{
								movementDirection=4;
								direction=DOWN;
							}
						}

					}
					avoided=0;
					if(middleY()>y)
					{
						if(isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity,10+Utils.randLessThan(6))==true)
						{
							{
								avoided=Utils.randLessThan(2);
								if(middleX()<nearestentity.middleX())
								{
									if(avoided==1) checkHitBoxAndMovePixelInDirection(LEFT); //else walk hitBoxLeft() if slightly hitBoxLeft()
									movementDirection=4;
								}
								else
								{
									if(avoided==1) checkHitBoxAndMovePixelInDirection(RIGHT);			//else walk hitBoxRight()
									movementDirection=4;
								}
							}
							direction=UP;
						}

						if(avoided==0)
						{
							if(checkHitBoxAndMovePixelInDirection(UP)==false)
							{
								if(movementDirection!=LEFT&&movementDirection!=RIGHT)
								{
									if(Utils.randLessThan(2)==0) movementDirection=LEFT;
									else movementDirection=RIGHT;
								}
							}
							else
							{
								movementDirection=4;
								direction=UP;
							}
						}
					}
					avoided=0;

				}

				if(xdistance>ydistance)
				{
					if(middleX()<x)
					{
						if(isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity,10+Utils.randLessThan(6))==true)
						{
							{
								avoided=Utils.randLessThan(2);
								if(middleY()<=nearestentity.middleY())
								{
									if(avoided==1) checkHitBoxAndMovePixelInDirection(UP); //else walk up if slightly above
									movementDirection=4;
								}
								else
								{
									if(avoided==1) checkHitBoxAndMovePixelInDirection(DOWN);			//else walk down
									movementDirection=4;
								}
							}
							direction=RIGHT;
						}

						if(avoided==0)
						{
							if(checkHitBoxAndMovePixelInDirection(RIGHT)==false)
							{
								if(movementDirection!=UP&&movementDirection!=DOWN)
								{
									if(Utils.randLessThan(2)==0) movementDirection=UP;
									else movementDirection=DOWN;
								}
							}
							else
							{
								movementDirection=4;
								direction=RIGHT;
							}
						}

					}
					avoided=0;
					if(middleX()>x)
					{
						if(isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity,10+Utils.randLessThan(6))==true)
						{
							{
								avoided=Utils.randLessThan(2);
								if(middleY()<nearestentity.middleY())
								{
									if(avoided==1) checkHitBoxAndMovePixelInDirection(UP); //else walk up if slightly above
									movementDirection=4;
								}
								else
								{
									if(avoided==1) checkHitBoxAndMovePixelInDirection(DOWN);			//else walk down
									movementDirection=4;
								}
							}
							direction=LEFT;
						}

						if(avoided==0)
						{
							if(checkHitBoxAndMovePixelInDirection(LEFT)==false)
							{
								if(movementDirection!=UP&&movementDirection!=DOWN)
								{
									if(Utils.randLessThan(2)==0) movementDirection=UP;
									else movementDirection=DOWN;
								}
							}
							else
							{
								movementDirection=4;
								direction=LEFT;
							}
						}

					}
				}

				if(movementDirection==UP)
				{
					if(checkHitBoxAndMovePixelInDirection(UP)==false||isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity,10+Utils.randLessThan(6))==true)
					{
						movementDirection=4;
					}
					else direction=UP;
				}
				else if(movementDirection==DOWN)
				{
					if(checkHitBoxAndMovePixelInDirection(DOWN)==false||isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity,10+Utils.randLessThan(6))==true)
					{
						movementDirection=4;
					}
					else direction=DOWN;
				}
				else if(movementDirection==LEFT)
				{
					if(checkHitBoxAndMovePixelInDirection(LEFT)==false||isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity,10+Utils.randLessThan(6))==true)
					{
						movementDirection=4;
					}
					else direction=LEFT;
				}
				else if(movementDirection==RIGHT)
				{
					if(checkHitBoxAndMovePixelInDirection(RIGHT)==false||isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity,10+Utils.randLessThan(6))==true)
					{
						movementDirection=4;
					}
					else direction=RIGHT;
				}


				if(pixelsToWalk>0&&isWalkingIntoPlayerThisFrame==false) pixelsToWalk--;

			}


		}
		return there_yet;
	}


	//=========================================================================================================================
	int walk_to_xy_intelligenthit_stopforothers_pushmain(float x,float y)
	{//=========================================================================================================================


		if(Player()==null)
		{
			log.error("Player null in walk_to_xy_intelligenthit_stopforothers_pushmain()");
			return 0;
		}


		setIgnoreHitPlayer(true);
		//setTicksPerPixelMoved(speed);



		if(x==-1) x=middleX();
		if(y==-1) y=middleY();

		int there_yet=0;
		int noanim=0;

		if(middleX()==x&&middleY()==y)
		{
			there_yet=1;
		}
		else
		{
			if(ifCanMoveAPixelThisFrameSubtractAndReturnTrue()==true)
			{
				float xdistance=middleX()-x;
				float ydistance=middleY()-y;

				if(xdistance<0) xdistance*=-1;
				if(ydistance<0) ydistance*=-1;

				int direction=0;

				Entity n=findNearestEntity();

				if(ydistance>=xdistance) //walk the greater distance first, up/down vs hitBoxLeft()/hitBoxRight()
				{
					if(middleY()<y)
					{
						if(isHitBoxTouchingEntityInDirectionByAmount(n,DOWN,5)==true&&(x()!=n.x()||y()!=n.y()))
						{
							if(n==Player())
							{
								//push main sprite down
								if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN)==false) n.mapY++;

								if(middleX()<n.middleX())
								{//push main sprite hitBoxRight()
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT)==false) n.mapX++;
								}
								else
								{//push main sprite hitBoxLeft()
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT)==false) n.mapX--;
								}
							}

							noanim=1;
							movementDirection=4;
							direction=DOWN;

						}
						else if(checkHitBoxAndMovePixelInDirection(DOWN)==false)
						{
							if(movementDirection!=LEFT&&movementDirection!=RIGHT)
							{
								if(Utils.randLessThan(2)==0) movementDirection=LEFT;
								else movementDirection=RIGHT;
							}
						}
						else
						{
							movementDirection=4;
							direction=DOWN;
						}
					}
					if(middleY()>y)
					{
						if(isHitBoxTouchingEntityInDirectionByAmount(n,UP,5)==true&&(x()!=n.x()||y()!=n.y()))
						{
							if(n==Player())
							{
								//push main sprite up
								if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP)==false) n.mapY--;

								if(middleX()<=n.middleX())
								{//push main sprite hitBoxRight()
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT)==false) n.mapX++;
								}
								else
								{//push main sprite hitBoxLeft()
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT)==false) n.mapX--;
								}
							}
							noanim=1;
							movementDirection=4;
							direction=UP;

						}
						else if(checkHitBoxAndMovePixelInDirection(UP)==false)
						{
							if(movementDirection!=LEFT&&movementDirection!=RIGHT)
							{
								if(Utils.randLessThan(2)==0) movementDirection=LEFT;
								else movementDirection=RIGHT;
							}
						}
						else
						{
							movementDirection=4;
							direction=UP;
						}
					}
				}

				if(xdistance>=ydistance)
				{
					if(middleX()<x)
					{
						if(isHitBoxTouchingEntityInDirectionByAmount(n,RIGHT,5)==true&&(x()!=n.x()||y()!=n.y()))
						{
							if(n==Player())
							{
								//push main sprite hitBoxRight()
								if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT)==false) n.mapX++;

								if(middleY()>n.middleY())
								{//push main sprite up
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP)==false) n.mapY--;
								}
								else
								{//push main sprite down
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN)==false) n.mapY++;
								}
							}
							noanim=1;
							movementDirection=4;
							direction=RIGHT;

						}
						else if(checkHitBoxAndMovePixelInDirection(RIGHT)==false)
						{
							if(movementDirection!=UP&&movementDirection!=DOWN)
							{
								if(Utils.randLessThan(2)==0) movementDirection=UP;
								else movementDirection=DOWN;
							}
						}
						else
						{
							movementDirection=4;
							direction=RIGHT;
						}

					}
					if(middleX()>x)
					{
						if(isHitBoxTouchingEntityInDirectionByAmount(n,LEFT,5)==true&&(x()!=n.x()||y()!=n.y()))
						{
							if(n==Player())
							{
								//push main sprite hitBoxLeft()
								if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT)==false) n.mapX--;

								if(middleY()>=n.middleY())
								{//push main sprite up
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP)==false) n.mapY--;
								}
								else
								{//push main sprite down
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN)==false) n.mapY++;
								}
							}
							noanim=1;
							movementDirection=4;
							direction=LEFT;
						}
						else if(checkHitBoxAndMovePixelInDirection(LEFT)==false)
						{
							if(movementDirection!=UP&&movementDirection!=DOWN)
							{
								if(Utils.randLessThan(2)==0) movementDirection=UP;
								else movementDirection=DOWN;
							}
						}
						else
						{
							movementDirection=4;
							direction=LEFT;
						}
					}
				}

				if(movementDirection==UP)
				{
					if(checkHitBoxAndMovePixelInDirection(UP)==false||isEntityHitBoxTouchingMyHitBoxByAmount(n,10+Utils.randLessThan(6))==true)
					{
						movementDirection=4;
					}
					else direction=UP;
				}
				else if(movementDirection==DOWN)
				{
					if(checkHitBoxAndMovePixelInDirection(DOWN)==false||isEntityHitBoxTouchingMyHitBoxByAmount(n,10+Utils.randLessThan(6))==true)
					{
						movementDirection=4;
					}
					else direction=DOWN;
				}
				else if(movementDirection==LEFT)
				{
					if(checkHitBoxAndMovePixelInDirection(LEFT)==false||isEntityHitBoxTouchingMyHitBoxByAmount(n,10+Utils.randLessThan(6))==true)
					{
						movementDirection=4;
					}
					else direction=LEFT;
				}
				else if(movementDirection==RIGHT)
				{
					if(checkHitBoxAndMovePixelInDirection(RIGHT)==false||isEntityHitBoxTouchingMyHitBoxByAmount(n,10+Utils.randLessThan(6))==true)
					{
						movementDirection=4;
					}
					else direction=RIGHT;
				}


			}
		}
		return there_yet;
	}



	//=========================================================================================================================
	void walkStraightFromPointToPoint(int x1,int y1,int x2,int y2)
	{//=========================================================================================================================


		if(movementDirection>1) movementDirection=0;//this will simply be used as a movement switch in this function //no its not appropriate but fuck it
		int there_yet=0;
		if(movementDirection==0)
		{
			there_yet=walkToXYWithBasicHitCheck(x1,y1);
			if(there_yet==1) movementDirection++;
		}
		if(movementDirection==1)
		{
			there_yet=walkToXYWithBasicHitCheck(x2,y2);
			if(there_yet==1) movementDirection=0;
		}
	}



	//=========================================================================================================================
	void walkStraightFromPointToPointAndStop(int x1,int y1,int x2,int y2)
	{//=========================================================================================================================

		if(movementDirection>1) movementDirection=0;//this will simply be used as a movement switch in this function //no its not appropriate but fuck it


		int there_yet=0;
		if(movementDirection==0)
		{
			there_yet=walkToXYWithBasicHitCheck(x1,y1);
			if(there_yet==1) movementDirection++;
		}
		if(movementDirection==1)
		{
			there_yet=walkToXYWithBasicHitCheck(x2,y2);
			if(there_yet==1) movementDirection=0;
		}
	}



	//=========================================================================================================================
	void walkAwayFromPoint(int x,int y)
	{//=========================================================================================================================

		setIgnoreHitPlayer(true);
		//setTicksPerPixelMoved(speed);
		if(ifCanMoveAPixelThisFrameSubtractAndReturnTrue()==true)
		{


			if(middleY()>y)
			{

				checkHitBoxAndMovePixelInDirection(DOWN);
			}
			if(middleY()<y)
			{

				checkHitBoxAndMovePixelInDirection(UP);
			}
			if(middleX()>x)
			{
				checkHitBoxAndMovePixelInDirection(RIGHT);

			}
			if(middleX()<x)
			{
				checkHitBoxAndMovePixelInDirection(LEFT);

			}

			if(pixelsToWalk>0&&isWalkingIntoPlayerThisFrame==false) pixelsToWalk--;

		}


	}



	//=========================================================================================================================
	int walkDistance(int direction)
	{//=========================================================================================================================

		int there_yet=0;

		if(pixelsToWalk>0)
		{
			movementDirection=direction;
			//setTicksPerPixelMoved(speed);
			checkHitBoxAndWalkDirection(movementDirection);
		}
		else there_yet=1;

		return there_yet;
	}



	//=========================================================================================================================
	int avoidEntity(Entity e,int amt)//returns 1 if not in entity area,use it to do something else outside,standing,staring,walking randomly etc
	{//=========================================================================================================================

		int outside_area=0;


		//if( right()>e.left()-amt &&
		//left()<e.right()+amt &&
		//bottom()>e.top()-amt &&
		//top()<e.bottom()+amt

		if(middleX()>e.middleX()-amt&&
				middleX()<e.middleX()+amt&&
				middleY()>e.middleY()-amt&&
				middleY()<e.middleY()+amt)
		{
			outside_area=0;
			float temp_speed=ticksPerPixelMoved();
			setTicksPerPixelMoved(1);
			setIgnoreHitPlayer(true);

			if(middleX()<=e.middleX())
			{
				movementDirection=LEFT;
			} //move hitBoxLeft()
			if(middleX()>=e.middleX())
			{
				movementDirection=RIGHT;
			}//move hitBoxRight()

			if(middleY()<=e.middleY())
			{
				movementDirection=UP;
			}//move up
			if(middleY()>=e.middleY())
			{
				movementDirection=DOWN;
			}//move down

			if(ifCanMoveAPixelThisFrameSubtractAndReturnTrue()==true)
			{
				if(middleX()<=e.middleX())
				{
					checkMiddlePixelHitAndMovePixelInDirection(LEFT);
				} //move hitBoxLeft()

				if(middleX()>=e.middleX())
				{
					checkMiddlePixelHitAndMovePixelInDirection(RIGHT);
				}//move hitBoxRight()


				if(middleY()<=e.middleY())
				{
					checkMiddlePixelHitAndMovePixelInDirection(UP);
				}//move up

				if(middleY()>=e.middleY())
				{
					checkMiddlePixelHitAndMovePixelInDirection(DOWN);
				}//move down
			}

			setIgnoreHitPlayer(false);
			setTicksPerPixelMoved(temp_speed);



		}
		else outside_area=1;

		return outside_area;
	}



	//=========================================================================================================================
	int avoidNearestEntity(int avoid_amt)
	{//=========================================================================================================================

		Entity nearestentity=findNearestEntity();

		return avoidEntity(nearestentity,avoid_amt);

	}


	//=========================================================================================================================
	int avoidNearestCharacter(int avoid_amt)
	{//=========================================================================================================================

		Character nearestentity=findNearestCharacter();

		return avoidEntity(nearestentity,avoid_amt);

	}




	//=========================================================================================================================
	void pushableCrowdBehavior()
	{//=========================================================================================================================


		Entity nearestentity=findNearestEntity();

		if(avoidEntity(nearestentity,4)==1)//based on entity avoid nearest entity,send in all the entitys you want to be in the crowd
		{
			//avoiding.. hehe i could just leave this out
		}
	}




	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================BEGIN BEGIN BEGIN
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================



	//TODO: problems:

	//entity still gets stuck facing down sometimes
	//entitys are too jittery
	//walking into corners back and forth looks bad.


	//solutions:
	//entity can stop momentarily if there is someone in their way, unless they are walking faster

	//entitys can all push each other out of the way and never change direction when stuck in a corner

	//entitys should pathfind their way out of corners and not randomly decide a direction

	//jitter is caused by pushing back and forth. entitys should communicate to decide who is pushing and who is being pushed?


	//i need some fucking adderall (feb 2010)



	//here i made a huge mistake/fuckup and went to japan
	//though i guess i was supposed to


	//hi i'm back it's feb 2012, i have ritalin and modafinil, adderall sucks. i'm on just modafinil for the past few days and feel really floaty but i can function.
	//i'm smoking and patch and smoking pot, i ported this to java in like 3 months, maybe a little longer, i'm doing fucking fantastic
	//i'm listening to apoptygma berzerk electricity, being kind of sad and kind of not, as usual.



	//hi i'm back june 17, 2012, i have ritalin, modafinil, pot, not masturbating though i should, made fwber for 3 weeks, feel dumb, working on this again.

	//hi its june 19, i am on modafinil and pot and masturbating to hgames, feel amazing, getting tons of shit done.
	//strength, courage, wisdom = modafinil, nicotine, pot


	//Hi its 2012-12-27 I am on modafinil and not masturbating, locked in a room in sacramento on webcam and getting huge amounts done.
	//Wrote the server. Did aws. Did paypal/fps/google checkout. Did ec2. Oh man.
	//I think I am insane.


	//hi its 2013 1 17
	//i am the hero
	//i am a trillionaire
	//i dont care at all
	//nothing can stop me now
	//and you'll never get to me
	//i will save the world


	//hi its 2013-1-21
	//i am covered in a rash for some reason
	//i stopped modafinil and my power is weaker but still strong
	//i will start again and maybe die
	//nothing can stop me now


	//hi its 20130425
	//i am back on modafinil, ready to die
	//i have no food and no money and half a container of slop
	//no cigarettes, on the patch but i am fine
	//half a patch
	//moderate coffee

	//i got power up to maximum during easter and became jesus and a psychic warrior
	//realized i will be a billionaire
	//realized i can will power myself
	//realized it is all about wanting nothing, saying no to everything
	//no greed
	//"nobody can hold him"
	//"he's going to be the president" and i don't care
	//i realized everything in the world is psychic control and reality really is psychosomatic, confidence, pyramids, mind magic, eye of god, ec
	//and then started freaking out because my mom used a book on "success" as dominance iconography, maybe, i don't know
	//i went insane and told my mom i wished she was dead
	//now i feel bad about it, she will be ok though
	//but i called her and got it back, i got the power and the confidence back, i didn't give up
	//people are just compelled to act, i understand
	//then right before easter i couldn't handle it and snapped at my mom and snapped and felt satan get me and screamed with tongues
	//i saw a golden angel in my head
	//i saw isis talk to me
	//these beings are real
	//reality is an illusion
	//mind control
	//everything controls me
	//i can win
	//now i am fine again, getting back up
	//the world isn't real
	//god is real
	//my mom could hear me
	//when i called she said "what's wrong with your voice"
	//she knew
	//she's inside my head
	//hi mom
	//i know the game now
	//i can collapse reality
	//i can beat god's game
	//i was almost there
	//she heard me scream
	//it's real


	//hi it's 2013-05-27
	//i'm broken
	//it was my mom




	//=========================================================================================================================
	int walk_to_xy_intelligenthit_avoidothers_pushmain(float x,float y)
	{//=========================================================================================================================


		if(Player()==null)
		{
			log.error("Player null in walk_to_xy_intelligenthit_avoidothers_pushmain()");
			return 0;
		}



		setIgnoreHitPlayer(true);
		//setTicksPerPixelMoved(speed);


		int there_yet=0;
		int avoided=0;
		int facing_direction=0;
		int already_walked=0;


		if(x==-1) x=middleX();
		if(y==-1) y=middleY();

		//if already there return 1, animate standing

		if(middleX()==x&&middleY()==y)
		{
			there_yet=1;
		}

		else

		{

			if(ifCanMoveAPixelThisFrameSubtractAndReturnTrue()==true)
			{

				//if time to walk

				//calc distance x and y
				float xdistance=middleX()-x;
				float ydistance=middleY()-y;

				if(xdistance<0) xdistance*=-1;
				if(ydistance<0) ydistance*=-1;



				//find nearest entity
				Entity e=findNearestEntity();


				if(ydistance>=xdistance) //walk the greater distance first, up/down vs hitBoxLeft()/hitBoxRight()
				{


					///walking down
					if(middleY()<y)
					{



						if(isEntityHitBoxTouchingMyHitBoxByAmount(e,10)==true)
						{



							if(e==Player())
							{

								//push main sprite down
								if((middleY()<Player().middleY())&&Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN)==false) e.mapY++;

								if(middleX()<Player().middleX())
								{//push main sprite hitBoxRight()
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT)==false) e.mapX++;
								}

								else

								{//push main sprite hitBoxLeft()
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT)==false) e.mapX--;
								}

							}



							{

								avoided=Utils.randLessThan(2);
								if(middleX()<=e.middleX())
								{

									if(avoided==1) checkHitBoxAndMovePixelInDirection(LEFT);
									already_walked=1;

								}
								else
								{

									if(avoided==1) checkHitBoxAndMovePixelInDirection(RIGHT);
									already_walked=1;

								}
							}


							facing_direction=DOWN;

						}


						if(avoided==0)
						{
							if(checkHitBoxAndMovePixelInDirection(DOWN)==false)
							{
								if(movementDirection!=LEFT&&movementDirection!=RIGHT)
								{
									if(middleX()>=x) movementDirection=LEFT;
									else movementDirection=RIGHT;
								}
							}
							else
							{
								already_walked=1;
								facing_direction=DOWN;
							}
						}

					}


					avoided=0;

					///walking up
					if(middleY()>y)
					{
						if(isEntityHitBoxTouchingMyHitBoxByAmount(e,10)==true)
						{
							if(e==Player())
							{
								//push main sprite up
								if((middleY()>Player().middleY())&&Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP)==false) e.mapY--;

								if(middleX()<=Player().middleX())
								{//push main sprite hitBoxRight()
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT)==false) e.mapX++;
								}
								else
								{//push main sprite hitBoxLeft()
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT)==false) e.mapX--;
								}
							}

							{
								avoided=Utils.randLessThan(2);

								if(middleX()<e.middleX())
								{
									if(avoided==1) checkHitBoxAndMovePixelInDirection(LEFT); //else walk hitBoxLeft() if slightly hitBoxLeft()
									already_walked=1;
								}
								else
								{
									if(avoided==1) checkHitBoxAndMovePixelInDirection(RIGHT);			//else walk hitBoxRight()
									already_walked=1;
								}
							}
							facing_direction=UP;
						}

						if(avoided==0)
						{
							if(checkHitBoxAndMovePixelInDirection(UP)==false)
							{
								if(movementDirection!=LEFT&&movementDirection!=RIGHT)
								{
									if(middleX()>=x) movementDirection=LEFT;
									else movementDirection=RIGHT;
								}
							}
							else
							{
								already_walked=1;
								facing_direction=UP;
							}
						}
					}
					avoided=0;

				}



				//if walk hitBoxRight()/hitBoxLeft() first
				if(xdistance>ydistance)
				{


					///walking hitBoxRight()
					if(middleX()<x)
					{
						if(isEntityHitBoxTouchingMyHitBoxByAmount(e,10)==true)
						{
							if(e==Player())
							{

								//push main sprite hitBoxRight()
								if((middleX()<Player().middleX())&&Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT)==false) e.mapX++;

								if(middleY()>Player().middleY())
								{//push main sprite up
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP)==false) e.mapY--;
								}
								else
								{//push main sprite down
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN)==false) e.mapY++;
								}
							}

							{

								avoided=Utils.randLessThan(2);

								if(middleY()<=e.middleY())
								{
									if(avoided==1) checkHitBoxAndMovePixelInDirection(UP); //else walk up if slightly above
									already_walked=1;
								}
								else
								{
									if(avoided==1) checkHitBoxAndMovePixelInDirection(DOWN);			//else walk down
									already_walked=1;
								}
							}
							facing_direction=RIGHT;
						}

						if(avoided==0)
						{
							if(checkHitBoxAndMovePixelInDirection(RIGHT)==false)
							{
								if(movementDirection!=UP&&movementDirection!=DOWN)
								{
									if(middleY()>=y) movementDirection=UP;
									else movementDirection=DOWN;
								}
							}
							else
							{
								already_walked=1;
								facing_direction=RIGHT;
							}
						}

					}



					avoided=0;


					///walking hitBoxLeft()
					if(middleX()>x)
					{
						if(isEntityHitBoxTouchingMyHitBoxByAmount(e,10)==true)
						{
							if(e==Player())
							{
								//push main sprite hitBoxLeft()
								if((middleX()>Player().middleX())&&Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT)==false) e.mapX--;

								if(middleY()>=Player().middleY())
								{//push main sprite up
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP)==false) e.mapY--;
								}
								else
								{//push main sprite down
									if(Player().checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN)==false) e.mapY++;
								}
							}

							{
								avoided=Utils.randLessThan(2);
								if(middleY()<e.middleY())
								{
									if(avoided==1) checkHitBoxAndMovePixelInDirection(UP); //else walk up if slightly above
									already_walked=1;
								}
								else
								{
									if(avoided==1) checkHitBoxAndMovePixelInDirection(DOWN);			//else walk down
									already_walked=1;
								}
							}
							facing_direction=LEFT;
						}

						if(avoided==0)
						{
							if(checkHitBoxAndMovePixelInDirection(LEFT)==false)
							{
								if(movementDirection!=UP&&movementDirection!=DOWN)
								{
									if(middleY()>=y) movementDirection=UP;
									else movementDirection=DOWN;
								}
							}
							else
							{
								already_walked=1;
								facing_direction=LEFT;
							}
						}

					}
				}



				if(already_walked==0)
				{
					if(movementDirection==UP)
					{
						if(
								checkHitBoxAndMovePixelInDirection(UP)==false
								||
								(
									isEntityHitBoxTouchingMyHitBoxByAmount(e,10+Utils.randLessThan(6))==true
									&&middleY()>e.middleY()
								)
						)
						{
							movementDirection=4;
						}
						else facing_direction=UP;

					}
					else if(movementDirection==DOWN)
					{
						if(
								checkHitBoxAndMovePixelInDirection(DOWN)==false
								||
								(
									isEntityHitBoxTouchingMyHitBoxByAmount(e,10+Utils.randLessThan(6))==true
									&&
									middleY()<e.middleY()
								)
						)
						{
							movementDirection=4;
						}
						else facing_direction=DOWN;
					}
					else if(movementDirection==LEFT)
					{
						if(
								checkHitBoxAndMovePixelInDirection(LEFT)==false
								||
								(
									isEntityHitBoxTouchingMyHitBoxByAmount(e,10+Utils.randLessThan(6))==true
									&&
									middleX()>e.middleX()
								)
						)
						{
							movementDirection=4;
						}
						else facing_direction=LEFT;
					}
					else if(movementDirection==RIGHT)
					{
						if(
								checkHitBoxAndMovePixelInDirection(RIGHT)==false
								||
								(
									isEntityHitBoxTouchingMyHitBoxByAmount(e,10+Utils.randLessThan(6))==true
									&&
									middleX()<e.middleX()
								)
						)
						{
							movementDirection=4;
						}
						else facing_direction=RIGHT;
					}
				}

				if(pixelsToWalk>0&&isWalkingIntoPlayerThisFrame==false) pixelsToWalk--;
			}

		}
		return there_yet;
	}




	//=========================================================================================================================
	public void renderDebugBoxes()
	{//=========================================================================================================================
		super.renderDebugBoxes();

		float zoom = Cameraman().getZoom();

		if(pathfinder!=null)
			if(pathfinder.path!=null)
			{

				for(int i=0;i<pathfinder.path.pathTiles.size();i++)
				{
					GLUtils.drawBox(
							getMap().getScreenX(pathfinder.path.getTileXForPathIndex(i)*8*2,16),
							getMap().getScreenX(pathfinder.path.getTileXForPathIndex(i)*8*2+16,16),
							getMap().getScreenY(pathfinder.path.getTileYForPathIndex(i)*8*2,16),
							getMap().getScreenY(pathfinder.path.getTileYForPathIndex(i)*8*2+16,16),
							255,255,255);

				}
			}


	}



}
