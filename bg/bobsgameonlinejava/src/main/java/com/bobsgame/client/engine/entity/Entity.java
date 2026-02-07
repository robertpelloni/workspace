package com.bobsgame.client.engine.entity;

//import static org.lwjgl.opengl.GL11.*;
//import static org.lwjgl.opengl.GL12.*;


//import static org.lwjgl.opengl.GL13.*;
//import static org.lwjgl.opengl.GL14.*;
//import static org.lwjgl.opengl.GL15.*;
//import static org.lwjgl.opengl.GL20.*;
//import static org.lwjgl.opengl.GL21.*;
//import static org.lwjgl.opengl.GL30.*;
//import static org.lwjgl.opengl.GL31.*;
//import static org.lwjgl.opengl.GL32.*;
//import static org.lwjgl.opengl.GL33.*;
//import static org.lwjgl.opengl.GL40.*;
//import static org.lwjgl.opengl.GL41.*;
//import static org.lwjgl.opengl.GL42.*;




import static org.lwjgl.opengl.GL11.GL_TEXTURE_2D;
import static org.lwjgl.opengl.GL11.glBindTexture;

import java.util.ArrayList;

//import java.nio.FloatBuffer;

//import org.lwjgl.BufferUtils;
//import org.lwjgl.input.Keyboard;
import org.slf4j.LoggerFactory;

import com.bobsgame.client.Texture;


import ch.qos.logback.classic.Logger;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.event.Event;
import com.bobsgame.client.engine.game.Player;
import com.bobsgame.client.engine.map.Area;
import com.bobsgame.client.engine.map.Door;
import com.bobsgame.client.engine.map.Map;
import com.bobsgame.net.BobNet;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.EntityData;
import com.bobsgame.shared.EventData;
import com.bobsgame.shared.SpriteAnimationSequence;
import com.bobsgame.shared.Utils;
import com.bobsgame.shared.MapData.RenderOrder;


//=========================================================================================================================
public class Entity extends EnginePart
{//=========================================================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(Entity.class);


	static public int DOWN = 0;
	static public int UP = 1;
	static public int LEFT = 2;
	static public int RIGHT = 3;

	static public int UPLEFT = 4;
	static public int DOWNRIGHT = 6;
	static public int DOWNLEFT = 7;
	static public int UPRIGHT = 5;


	public int SPEED_ACCEL_INCREMENT_AMOUNT=1;


	//these are ticks per pixel moved
	public int  ticksPerPixel_CAR=2;
	public int  ticksPerPixel_FASTEST=3;
	public int  ticksPerPixel_FASTER=4;
	public int  ticksPerPixel_FAST=5;
	public int  ticksPerPixel_NORMAL=10;
	public int  ticksPerPixel_SLOW=15;
	public int  ticksPerPixel_SLOWER=20;
	public int  ticksPerPixel_SLOWEST=30;


	public int  ticksPerPixel_CAMERA_CONVERSATION=4;
	public int  ticksPerPixel_CAMERA_STOPPED=ticksPerPixel_SLOWEST;


	public int  YUU_WALKING_SPEED_KEYBOARD=24;
	public int  YUU_RUNNING_SPEED_KEYBOARD=ticksPerPixel_FASTEST;
	public int  YUU_STANDING_SPEED_KEYBOARD=ticksPerPixel_SLOWER;

	public int  YUU_WALKING_SPEED_JOYSTICK=28;
	public int  YUU_RUNNING_SPEED_JOYSTICK=ticksPerPixel_FASTEST;
	public int  YUU_STANDING_SPEED_JOYSTICK=ticksPerPixel_SLOWER;


	public boolean disableMovementAnimationForAllEntities=false;
	public boolean isPlayerBeingDraggedThisFrame=false;
	public int numberOfEntitiesPullingPlayerThisFrame=0;
	public boolean isWalkingIntoPlayerThisFrame=false;
	public boolean isWalkingIntoWallThisFrame=false;











	public Sprite sprite = null;

	protected EntityData data;



	public float mapX = 0;
	public float mapY = 0;



	public float standJitterX = 0;//used when characters are standing to give them a little extra movement
	public float standJitterY = 0;


	public float alpha=1.0f;

	public boolean draw=false;


	private int animationTicksCounter=0; // was vbl_animation_timer
	private int frameIndexInTexture=0;//based on current sequence (getAnimDirection()) and currentAnimationFrameInSequence, this is what will be rendered
	private SpriteAnimationSequence currentAnimation = null;

	private int ticksBetweenAnimationLoopThisLoop = 0;//for storing random value between loops

	public int movementDirection=0;//was walk_dir



	public float shadowClipPerPixel[] = null;
	public boolean clipShadow = false;
	public float shadowSize = 0.65f;
	//public float shadowStart = 0.75f;
	public float shadowAlpha = 0.60f;




	protected int ticksSinceLastMovement = 0;
	public float pixelsToMoveThisFrame = 0;


	public boolean behaviorEnabled = true;

	ArrayList<String> eventBehaviorList = new ArrayList<String>();//TODO: do something with this!
	ArrayList<String> eventTargetTYPEIDList = new ArrayList<String>();//TODO: do something with this!


	public String currentAreaTYPEIDTarget = "";


	private boolean deleteWhenAlphaZero = false;



	public Map map = null;



	//=========================================================================================================================
	public Entity(Engine g)
	{//=========================================================================================================================
		super(g);

	}


	//=========================================================================================================================
	public Entity(Engine g, EntityData entityData, Map m)
	{//=========================================================================================================================

		super(g);

		init(entityData, m);



	}


	//=========================================================================================================================
	public void init(EntityData entityData, Map m)
	{//=========================================================================================================================


		if(entityData==null)
		{
			entityData = new EntityData(-1,"","",0,0,0,false,false,0,1.0f,12,false,false,false,false,false,0,0,false,false,true,null,"");
			log.warn("entityData was null in Entity.init()");
		}
		this.data = entityData;


		this.mapX = entityData.spawnXPixelsHQ();
		this.mapY = entityData.spawnYPixelsHQ();


		this.alpha=entityData.toAlpha();

		this.setFrame(entityData.initialFrame());



		if(entityData.eventData()!=null)
		{
			Event event = EventManager().getEventByIDCreateIfNotExist(entityData.eventData().id());
			event.entity = this;
		}

		map = m;

		//initSpriteAsset();
	}

	//=========================================================================================================================
	public void initCurrentAnimationFromSprite()
	{//=========================================================================================================================


		setCurrentAnimationBySpriteFrame(initialFrame());

		if(randomFrames())selectRandomFrame(getCurrentAnimationStartFrame(),getCurrentAnimationLastFrame());

		if(shadowClipPerPixel==null)
		{
			shadowClipPerPixel = new float[(int)(sprite.w())];
			for(int i=0;i<sprite.w();i++)shadowClipPerPixel[i]=1.0f;
		}

	}



















	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		//if(Engine()==null)setGame(mapAsset.Engine());


		if(eventData()!=null)
		{
			Event event = EventManager().getEventByIDCreateIfNotExist(eventData().id());

			EventManager().addToEventQueueIfNotThere(event);//events update their own network data inside their run function
		}



		if(sprite==null)
		{
			//first we check if we have the spriteAsset loaded, if not we make a server request.
			//when that request returns in a different thread, it will set the SpriteAsset in the HashMap and this will return the SpriteAsset instead of calling to the server.
			this.sprite = SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist(spriteName());

			if(sprite!=null)
			{
				initCurrentAnimationFromSprite();
			}

			return;
		}

		sprite.update();



		if(alpha!=toAlpha())
		{
			if(alpha>toAlpha())
			{
				alpha-=0.001f*Engine().engineTicksPassed();
				if(alpha<toAlpha())alpha=toAlpha();
			}
			if(alpha<toAlpha())
			{
				alpha+=0.001f*Engine().engineTicksPassed();
				if(alpha>toAlpha())alpha=toAlpha();
			}
		}

		if(deleteWhenAlphaZero==true)
		{
			if(alpha==0.0f)delete();
		}


		//TODO: handle eventBehavior
		//"MoveToArea:"+a.id()+","+bWalk+","+bHit+","+bPath+","+bAnim+","+bDiag);
		//"MoveToEntity:"+e.id()+","+bWalk+","+bHit+","+bPath+","+bAnim+","+bDiag);
		//"StandAndShuffle"
		//"StandAndShuffleAndFacePlayer"

		//TODO: handle normal behavior



		updateTimers();



		//do animation if was scripted in tools
		doAnimation();


	}


	//=========================================================================================================================
	public void updateTimers()
	{//=========================================================================================================================
		//add change in time to remaining time from last movement
		ticksSinceLastMovement += Engine().engineTicksPassed();

		if(ticksSinceLastMovement>=ticksPerPixelMoved())
		{

			pixelsToMoveThisFrame = ((float)ticksSinceLastMovement/(float)ticksPerPixelMoved());

			//now pixelsToMoveThisFrame is something like 3.24543
			//movements for Entity and Character are based on 1.0f though, so a character will move 3.0f and leave .24543

			//if we store the remainder of the ticks we didn't use in our 1.0f whole units, it will be correct.
			ticksSinceLastMovement %= ticksPerPixelMoved();

			//however, the Player uses float based values for everything and moves fractions of pixels.
			//Player should set ticksSinceLastMovement to zero for correct timing.
			if(this.getClass().equals(Player.class))ticksSinceLastMovement=0;


		}
		else
		{
			pixelsToMoveThisFrame = 0;
		}



		//if(pixelsToMoveThisFrame>20)pixelsToMoveThisFrame=1;


		animationTicksCounter+=Engine().engineTicksPassed();

	}







//	//=========================================================================================================================
//	public void addDialogue(String dialogueIDString)
//	{//=========================================================================================================================
//
//		int dialogueID = Integer.parseInt(dialogueIDString);
//
//		if(dialogueID!=-1)
//		{
//
//			Dialogue d = g.getDialogueByID(dialogueID);
//
//			if(d!=null)dialogueList.add(d);
//			else
//			dialogueList.add(new Dialogue(dialogueID));
//
//		}
//	}


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



		for(int i=0;i<connectionTYPEIDList().size();i++)
		{
			//draw connections to doors
			if(connectionTYPEIDList().get(i).startsWith("DOOR."))
			{
				//go through doorlist
				for(int d=0;d<getMap().doorList.size();d++)
				{
					Door door = getMap().doorList.get(d);

					if(connectionTYPEIDList().get(i).equals("DOOR."+door.name()))
					{
						float dx=door.screenLeft()+(door.w()/2)*zoom;
						float dy=door.screenTop()+(door.h())*zoom;

						GLUtils.drawArrowLine(screenLeft()+(w()/2)*zoom, screenMiddleHitboxY(), dx, dy, 0, 255, 0);
					}

				}
			}
			else
			//draw connections to areas
			{

				if(getMap()!=null && getMap().currentState!=null)
				{

					//go through area hashlist
//					Enumeration<Area> aEnum = getMap().currentState.areaByNameHashtable.elements();
//					while(aEnum.hasMoreElements())
//					{
//						Area a = aEnum.nextElement();

					for(int j=0;j<getMap().currentState.areaList.size();j++)
					{
						Area a = getMap().currentState.areaList.get(j);

						if(connectionTYPEIDList().get(i).equals(a.name()))
						{
							float ax = a.screenLeft()+(a.w()/2)*zoom;
							float ay = a.screenTop()+(a.h()/2)*zoom;

							GLUtils.drawArrowLine(screenLeft()+(w()/2)*zoom, screenMiddleHitboxY(), ax, ay, 0, 255, 0);
						}
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

						GLUtils.drawArrowLine(screenLeft()+(w()/2)*zoom, screenMiddleHitboxY(), ax, ay, 0, 255, 0);
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


			if(sprite.displayName().equals("No Name")==false)
			{
				GLUtils.drawOutlinedString("entityName: "+name(), x, y-36,BobColor.yellow);
				GLUtils.drawOutlinedString("displayName: "+sprite.displayName(), x, y-27,BobColor.green);
			}
			else
			{
				GLUtils.drawOutlinedString("entityName: "+name(), x, y-27,BobColor.yellow);
			}

			GLUtils.drawOutlinedString("id: "+id(), x, y-18,BobColor.white);
			GLUtils.drawOutlinedString("SpriteAsset Name: "+sprite.name(), x, y-9,BobColor.white);


			if(eventData()!=null)GLUtils.drawOutlinedString("Has Event: "+eventData().id(), x, y+(++strings*9),BobColor.red);

			//GL.drawOutlinedString("mapX: "+mapXPixelsHQ+" mapY: "+mapYPixelsHQ, x, y+(++strings*9),BobColor.white);
			//GL.drawOutlinedString("screenX: "+screenXPixelsHQ+" screenY: "+screenYPixelsHQ, x, y+(++strings*9),BobColor.white);
			//GL.drawOutlinedString("w: "+width()+" h: "+height(), x, y+(++strings*9),BobColor.white);
			//GL.drawOutlinedString("scale: "+scale, x, y+(++strings*9),BobColor.white);
			//GL.drawOutlinedString("alpha: "+alpha, x, y+(++strings*9),BobColor.white);


			//if(movementDirection==UP)GL.drawOutlinedString("movementDirection: Up", x, y+(++strings*9),BobColor.white);
			//if(movementDirection==DOWN)GL.drawOutlinedString("movementDirection: Down", x, y+(++strings*9),BobColor.white);
			//if(movementDirection==LEFT)GL.drawOutlinedString("movementDirection: Left", x, y+(++strings*9),BobColor.white);
			//if(movementDirection==RIGHT)GL.drawOutlinedString("movementDirection: Right", x, y+(++strings*9),BobColor.white);

			if(

					this.getClass().equals(Character.class)
					||this.getClass().equals(Player.class)
					||this.getClass().equals(RandomCharacter.class)
			)
			{
				GLUtils.drawOutlinedString("ticksPerPixelMoved: "+ticksPerPixelMoved(), x, y+(++strings*9),BobColor.white);
				GLUtils.drawOutlinedString("pixelsToMoveThisFrame: "+pixelsToMoveThisFrame, x, y+(++strings*9),BobColor.white);
			}

			//GL.drawOutlinedString("animationTicksCounter: "+animationTicksCounter, x, y+(++strings*9),BobColor.white);

			if(randomFrames())GLUtils.drawOutlinedString("Random Frames", x, y+(++strings*9),BobColor.red);
			if(disableShadow())GLUtils.drawOutlinedString("Disable Shadow", x, y+(++strings*9),BobColor.red);

			if(renderOrder()!=RenderOrder.GROUND)GLUtils.drawOutlinedString("RenderOrder: "+renderOrder(), x, y+(++strings*9),BobColor.red);
			if(alwaysOnTop())GLUtils.drawOutlinedString("alwaysOnTop", x, y+(++strings*9),BobColor.red);
			if(aboveWhenEqual())GLUtils.drawOutlinedString("aboveWhenEqual", x, y+(++strings*9),BobColor.red);
			if(aboveTopLayer())GLUtils.drawOutlinedString("aboveTopLayer", x, y+(++strings*9),BobColor.red);
			if(alwaysOnBottom())GLUtils.drawOutlinedString("alwaysOnBottom", x, y+(++strings*9),BobColor.red);
			if(isWalkingIntoPlayerThisFrame)GLUtils.drawOutlinedString("isWalkingIntoPlayerThisFrame", x, y+(++strings*9),BobColor.red);
			if(isWalkingIntoWallThisFrame)GLUtils.drawOutlinedString("isWalkingIntoWallThisFrame", x, y+(++strings*9),BobColor.red);
			if(ignoreHitPlayer())GLUtils.drawOutlinedString("ignoreHitPlayer", x, y+(++strings*9),BobColor.red);
			if(movementAnimationDisabled())GLUtils.drawOutlinedString("movementAnimationDisabled", x, y+(++strings*9),BobColor.red);
			if(pushable())GLUtils.drawOutlinedString("pushable", x, y+(++strings*9),BobColor.red);
			if(nonWalkable())GLUtils.drawOutlinedString("nonWalkable", x, y+(++strings*9),BobColor.red);
			if(ignoreHitLayer())GLUtils.drawOutlinedString("ignoreHitLayer", x, y+(++strings*9),BobColor.red);
			//if(ignore_fx_layer)GL.drawOutlinedString("ignore_fx_layer", x, y+(++strings*9),BobColor.red);

			GLUtils.drawOutlinedString("MiddleY: "+middleY(), x, y+(++strings*9),BobColor.green);

			if(currentAreaTYPEIDTarget!=null&&currentAreaTYPEIDTarget.length()>0)GLUtils.drawOutlinedString("Current Target TYPEID: "+currentAreaTYPEIDTarget, x, y+(++strings*9),BobColor.green);
			if(currentAreaTYPEIDTarget!=null&&currentAreaTYPEIDTarget.length()>0)GLUtils.drawOutlinedString("Current Target Name: "+getCurrentAreaTargetName(), x, y+(++strings*9),BobColor.green);



	/*
	public int voice_pitch=0;

	public int frameInSequence=0; // was anim_frame_count
	public int currentSequenceLength=8;//was amt_frames
	public int totalFrames=0;//total frames for all animations
	public int frameIndexInTexture=0;//based on current sequence (getAnimDirection()) and currentAnimationFrameInSequence, this is what will be rendered

	public int hitBoxFromLeftPixelsHQ = 0;
	public int hitBoxFromTopPixelsHQ = 0;
	public int hitBoxFromRightPixelsHQ = 0;
	public int hitBoxFromBottomPixelsHQ = 0;

	public boolean animateThroughFrames;
	public boolean randomTimeBetweenAnimation;
	public int ticksBetweenFrames;
	public int ticksBetweenAnimation;
	public int walkSpeed;
	public boolean onlyHereDuringEvent;

	public boolean pull_player=false;
	public boolean push_player=false;
	public boolean shadow = true;;
	public float shadowClip=0;

	int ticksSinceLastMovement = 0;

	int movementsThisFrame = 0;
	public float pixelsToMoveThisFrame = 0;

	ArrayList<String> behaviorList = new ArrayList<String>();
	ArrayList<String> connectionList = new ArrayList<String>();

*/



	}


	//=========================================================================================================================
	public String getCurrentAreaTargetName()
	{//=========================================================================================================================
		Area a = getMap().getAreaOrWarpAreaByTYPEID(currentAreaTYPEIDTarget);
		if(a==null)return "ERROR: Area not found.";
		return a.name();
	}


//	//=========================================================================================================================
//	public void render()
//	{//=========================================================================================================================
//		render(alpha);
//		//overrode this so i can send in arbitrary alpha, really only used for fading sprites out with the last map.
//	}

	//=========================================================================================================================
	public void render(float mapAlpha)
	{//=========================================================================================================================

		if(draw==false||sprite==null||sprite.texture==null)return;

		render(mapAlpha*this.alpha,this.sprite.texture, this.sprite.shadowTexture);

		//overrode this so i can send in arbitrary texture, really only used for random sprites which contain their own unique texture reference, and not the one contained in the spriteAsset object.


	}

	//=========================================================================================================================
	public void render(float alpha, Texture texture, Texture shadowTexture)
	{//=========================================================================================================================

		float zoom = Cameraman().getZoom();

		float tx0 = 0.0f;
		float tx1 = 1.0f;
		float ty0 = 0.0f;
		float ty1 = 1.0f;

		float x0 = 0;
		float x1 = 0;
		float y0 = 0;
		float y1 = 0;



		//YAY
		//SPRITE JITTERING IS COMPLETELY FIXED!
		//had to base it on the OFFSET of the floored scaled mapScreenX vs non-floored, since the map drawing itself is based on that to begin with to prevent shimmering

		float offsetX = (getMap().screenX()*zoom)-((float) Math.floor(getMap().screenX()*zoom));
		float offsetY = (getMap().screenY()*zoom)-((float) Math.floor(getMap().screenY()*zoom));


		//------------------------
		//draw shadow first
		//------------------------
		if(shadowTexture!=null&&disableShadow()==false)
		{

			if(clipShadow==false)
			{


				tx0 = 0.0f;
				tx1 = ((float)sprite.w()/(float)texture.getTextureWidth());
				ty0 = (((float)sprite.h())*getFrame())/texture.getTextureHeight();
				ty1 = ((((float)sprite.h())*(getFrame()+1))-1)/texture.getTextureHeight();

				x0 = screenLeft()-offsetX;
				x1 = x0+w()*zoom;
				y0 = (screenTop()-offsetY)+((h()*shadowStart())*zoom);
				y1 = y0+((h()*shadowSize)*zoom);


				GLUtils.drawTexture(shadowTexture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,shadowAlpha,GLUtils.FILTER_LINEAR);

			}
			else
			if(clipShadow==true&&shadowClipPerPixel!=null)
			{

				//bind texture here.
				glBindTexture(GL_TEXTURE_2D, shadowTexture.getTextureID());

				for(int x=0;x<sprite.w();x++)
				{
					//float w = 1.0f/(float)texture.getTextureWidth();

					tx0 = ((float)x/(float)texture.getTextureWidth());
					tx1 = ((float)(x+1.0f)/(float)texture.getTextureWidth());
					ty0 = (((float)sprite.h())*getFrame())/texture.getTextureHeight();
					ty1 = ((((float)sprite.h())*(getFrame()+1))-1)/texture.getTextureHeight();

					x0 = (screenLeft()-offsetX)+(x*scale()*zoom);
					x1 = x0+(1.0f*scale()*zoom);
					y0 = (screenTop()-offsetY)+((h()*shadowStart())*zoom);
					y1 = y0+((h()*shadowSize)*zoom);

					if(shadowClipPerPixel[x]<1.0f)
					{
						y1=(float)Math.floor(y0+((y1-y0)*shadowClipPerPixel[x]));
						ty1=((((((float)sprite.h())*(getFrame()))+((float)sprite.h()*shadowClipPerPixel[x]))-1)/texture.getTextureHeight());
					}

					//don't bind texture
					GLUtils.drawTexture(tx0,tx1,ty0,ty1,x0,x1,y0,y1,shadowAlpha,GLUtils.FILTER_LINEAR);
				}
			}
		}


		//------------------
		//now draw actual sprite
		//------------------

		x0 = screenLeft()-offsetX;
		y0 = screenTop()-offsetY;
		x1 = (float) (x0+w()*zoom);
		y1 = (float) (y0+h()*zoom);

		sprite.drawFrame(texture,getFrame(),x0,x1,y0,y1,alpha,GLUtils.FILTER_NEAREST);

//		if(texture!=null)
//		{
//			tx0 = 0.0f;
//			tx1 = ((float)sprite.w()/(float)texture.getTextureWidth());
//			ty0 = (((float)sprite.h())*frameIndexInTexture)/(float)texture.getTextureHeight();
//			ty1 = (((float)sprite.h())*(frameIndexInTexture+1))/(float)texture.getTextureHeight();
//
//
//
//			//x0 = (float)Math.floor(screenLeft());
//			//x1 = (float)Math.floor(screenRight());
//			//y0 = (float)Math.floor(screenTop());
//			//y1 = (float)Math.floor(screenBottom());
//
//
//
//
//			x0 = screenLeft()-offsetX;
//			y0 = screenTop()-offsetY;
//			x1 = (float) (x0+w()*drawScale);
//			y1 = (float) (y0+h()*drawScale);
//
//
//
//			GLUtils.drawTexture(texture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,alpha,GLUtils.FILTER_NEAREST);
//		}


		//------------------
		//special case for rendering doors action icon doorknob glow thing. maybe should override render in door for this.
		//------------------
		if(this.getClass().equals(Door.class))
		{

			Door d = (Door)this;
			d.renderActionIcon();
		}


	}




	//=========================================================================================================================
	public Map CurrentMap()
	{//=========================================================================================================================

		log.warn("CurrentMap() in Entity");
		new Exception().printStackTrace();

		return super.CurrentMap();

	}


	//=========================================================================================================================
	public Map getMap()
	{//=========================================================================================================================


		if(map == null)return super.CurrentMap();
		//if(mapID()==-1)return super.CurrentMap();

		//Map map = MapManager().getMapByIDBlockUntilLoaded(mapID());


		return map;
	}



	//=========================================================================================================================
	public boolean shouldDraw()
	{//=========================================================================================================================

		if(
			sprite==null
			||sprite.texture==null
			||isWithinScreenBounds()==false
		)
		{
			draw = false;
		}
		else
		draw=true;

		return draw;//TODO: also check to make sure it has graphics, visible flags, etc
	}



	//=========================================================================================================================
	public boolean isWithinScreenBounds()
	{//=========================================================================================================================

		float mapCameraXPixelsHQ = (float)getMap().mapCamX();
		float mapCameraYPixelsHQ = (float)getMap().mapCamY();

		//*************
		//flooring these fixes all the sprite jitter
		//nope, don't need to do this now, basing all the coords on the offset of the floored mapScreenXY in render, like the map chunk offsets.
		//*************
		float left 	= (float) (x());
		float right 	= (float) (x() + w());
		float top 	= (float) (y());
		float bottom 	= (float) (y() + h());

		float screenleft = mapCameraXPixelsHQ;
		float screenright = mapCameraXPixelsHQ+Engine().getWidthRelativeToZoom();
		float screentop = mapCameraYPixelsHQ;
		float screenbottom = mapCameraYPixelsHQ+Engine().getHeightRelativeToZoom();


		float shadowLength = ((h()*shadowStart())+(h()*shadowSize))-h();

		if(
			right<screenleft
			||
			left>screenright
			||
			bottom+shadowLength<screentop //so shadow can show even if sprite walks above screen
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











//
//	//=========================================================================================================================
//	public boolean check_collide_fx(int dir)
//	{//=========================================================================================================================
//
//		boolean return_this=true;
//
//
//
//		if(dir==UP)
//		{
//			if(
//				getMap().get_fx_layer_xy(left()+1,top())==0
//				&&getMap().get_fx_layer_xy(middleX()-1,top())==0
//				&&getMap().get_fx_layer_xy(middleX(),top())==0
//				&&getMap().get_fx_layer_xy(right()-1,top())==0
//			)return_this=false;
//		}
//		else
//		if(dir==DOWN)
//		{
//			if(
//					getMap().get_fx_layer_xy(left()+1,bottom())==0
//				&&getMap().get_fx_layer_xy(middleX()-1,bottom())==0
//				&&getMap().get_fx_layer_xy(middleX(),bottom())==0
//				&&getMap().get_fx_layer_xy(right()-1,bottom())==0
//			)return_this=false;
//		}
//		else
//		if(dir==LEFT)
//		{
//			if(
//					getMap().get_fx_layer_xy(left(),bottom()-1)==0
//				&&getMap().get_fx_layer_xy(left(),bottom()-4)==0
//			)return_this=false;
//		}
//		else
//		if(dir==RIGHT)
//		{
//			if(
//					getMap().get_fx_layer_xy(right()-1,bottom()-1)==0
//				&&getMap().get_fx_layer_xy(right()-1,bottom()-4)==0
//			)return_this=false;
//		}
//
//		if(ignore_fx_layer==true)return false;
//
//		return return_this;
//	}

	//=========================================================================================================================
	public boolean checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(int dir)
	{//=========================================================================================================================
		boolean hitting_wall=true;



		if(ignoreHitLayer()==true)return false;

		if(dir==UP)
		{
			if(
				checkXYAgainstHitLayerAndNonWalkableEntities(left()+1,top())==false
				&&checkXYAgainstHitLayerAndNonWalkableEntities(middleX()-1,top())==false
				&&checkXYAgainstHitLayerAndNonWalkableEntities(middleX(),top())==false
				&&checkXYAgainstHitLayerAndNonWalkableEntities(right()-1,top())==false
			)
			hitting_wall=false;
		}
		else
		if(dir==DOWN)
		{
			if(
				checkXYAgainstHitLayerAndNonWalkableEntities(left()+1,bottom())==false
				&&checkXYAgainstHitLayerAndNonWalkableEntities(middleX()-1,bottom())==false
				&&checkXYAgainstHitLayerAndNonWalkableEntities(middleX(),bottom())==false
				&&checkXYAgainstHitLayerAndNonWalkableEntities(right()-1,bottom())==false
			)
			hitting_wall=false;
		}
		else
		if(dir==LEFT)
		{
			if(
				checkXYAgainstHitLayerAndNonWalkableEntities(left(),bottom()-1)==false
				&&checkXYAgainstHitLayerAndNonWalkableEntities(left(),bottom()-4)==false
			)
			hitting_wall=false;
		}
		else
		if(dir==RIGHT)
		{
			if(
				checkXYAgainstHitLayerAndNonWalkableEntities(right()-1,bottom()-1)==false
				&&checkXYAgainstHitLayerAndNonWalkableEntities(right()-1,bottom()-4)==false
			)
			hitting_wall=false;
		}


		///todo: i split off the check against player() into its own function above, also need to call this separately.
		isWalkingIntoPlayerThisFrame = isTouchingPlayerInDirection(dir);

		///todo: dont combine this, find where this function is called and do both.
		//if(this!=Player()&&hitting_wall==false)hitting_wall=check_collide_fx(dir); //&&dont_walk_in_fx_layer

		isWalkingIntoWallThisFrame = hitting_wall;

		return hitting_wall;
	}




	//=========================================================================================================================
	public boolean checkMiddlePixelAgainstHitLayerAndNonWalkableEntitiesInDirection(int dir)
	{//=========================================================================================================================
		boolean hitting_wall=true;



		if(ignoreHitLayer()==true)return false;

		if(dir==UP)
		{
			if(

				checkXYAgainstHitLayerAndNonWalkableEntities(middleX()-1,top())==false
				&&checkXYAgainstHitLayerAndNonWalkableEntities(middleX(),top())==false

			)
			hitting_wall=false;
		}
		else
		if(dir==DOWN)
		{
			if(

				checkXYAgainstHitLayerAndNonWalkableEntities(middleX()-1,bottom())==false
				&&checkXYAgainstHitLayerAndNonWalkableEntities(middleX(),bottom())==false

			)
			hitting_wall=false;
		}
		else
		if(dir==LEFT)
		{
			if(
				checkXYAgainstHitLayerAndNonWalkableEntities(left(),middleY()-1)==false
				&&checkXYAgainstHitLayerAndNonWalkableEntities(left(),middleY())==false
			)
			hitting_wall=false;
		}
		else
		if(dir==RIGHT)
		{
			if(
				checkXYAgainstHitLayerAndNonWalkableEntities(right()-1,middleY()-1)==false
				&&checkXYAgainstHitLayerAndNonWalkableEntities(right()-1,middleY())==false
			)
			hitting_wall=false;
		}


		///todo: i split off the check against player() into its own function above, also need to call this separately.
		isWalkingIntoPlayerThisFrame = isTouchingPlayerInDirection(dir);

		///todo: dont combine this, find where this function is called and do both.
		//if(this!=Player()&&hitting_wall==false)hitting_wall=check_collide_fx(dir); //&&dont_walk_in_fx_layer

		isWalkingIntoWallThisFrame = hitting_wall;

		return hitting_wall;
	}




	//=========================================================================================================================
	/**
	 *
	 * this is used for PATHFINDING so it ignores doors (so sprites can go through doors) and walkable sprites!!
	 *
	 */
	public boolean checkPathBlockedXY(float x, float y)
	{//=========================================================================================================================

		boolean hit = false;
		int w = ((int)(right()-left())/2);

		//y is middleY()
		float topHit = y-((middleY()-y())-(16*3))-8;
		float bottomHit = y+(h()-(middleY()-y()));


		if(
				getMap().getHitLayerValueAtXYPixels(x,y)
				||getMap().getHitLayerValueAtXYPixels(x,y+16)
				||getMap().getHitLayerValueAtXYPixels(x,y-16)
				//hit += getMap().check_hit_layer_xy(x,topHit);
				//hit += getMap().check_hit_layer_xy(x,bottomHit);
				||getMap().getHitLayerValueAtXYPixels(x-w,y)
				||getMap().getHitLayerValueAtXYPixels(x+w,y)
		)
		hit = true;

		if(hit==false)
		{
			//go through all mapsprites, check if map characters

			for(int i=0;i<getMap().activeEntityList.size();i++)
			{

				Entity m = getMap().activeEntityList.get(i);

				if(
						m!=this
						&&m.getClass().equals(Door.class)==false
						&&m.getClass().equals(RandomCharacter.class)==false
						&&m.getClass().equals(Character.class)==false
						&&(m.nonWalkable()==true)
						&&x<m.right()//using full hitbox.
						&&x>m.left()
						&&y<m.bottom() //TODO use touching functions
						&&y>m.top()
				)return true;

				if(
						m!=this
						&&
						(
							m.getClass().equals(Character.class)
							||m.getClass().equals(RandomCharacter.class)
							||m.getClass().equals(Player.class)
						)
						&&x<m.middleX()+6//not using full hitbox.
						&&x>m.middleX()-6
						&&y<m.middleY()+6 //TODO use touching functions
						&&y>m.middleY()-6
				)return true;

			}


		}
		return hit;

	}


	//=========================================================================================================================
	public boolean checkXYAgainstNonWalkableEntities(float x, float y)
	{//=========================================================================================================================

		if(Engine().hitLayerEnabled==false)return false;

		for(int s=0;s<getMap().activeEntityList.size();s++)
		{
			Entity e = getMap().activeEntityList.get(s);

			if(e.nonWalkable()==false)continue;

			if(e.equals(this))continue;

			float left = e.left();
			float right = e.right();
			float top = e.top();
			float bottom = e.bottom();

			if(x>=left&&x<=right&&y>=top&&y<=bottom)return true; //TODO use touching functions
		}



		for(int s=0;s<getMap().doorList.size();s++)
		{
			Door e = getMap().doorList.get(s);

			if(e.nonWalkable()==false || e.isOpen())continue;

			//if(e.equals(this))continue;

			float left = e.left();
			float right = e.right();
			float top = e.top();
			float bottom = e.bottom();

			if(x>=left&&x<=right&&y>=top&&y<=bottom)return true; //TODO use touching functions
		}

		return false;

	}

	//=========================================================================================================================
	public boolean checkXYAgainstHitLayerAndNonWalkableEntities(float x, float y)
	{//=========================================================================================================================
		if(
				getMap().getHitLayerValueAtXYPixels(x,y)==false
				&& checkXYAgainstNonWalkableEntities(x,y)==false
		)
		return false;

		return true;

	}


	//=========================================================================================================================
	public boolean checkHitBoxAndMovePixelInDirection(int dir)	//returns 0 if hit wall   ( DOES HIT DETECTION/WALL DETECTION,HIT WITH SPRITE DETECTION )
	{//=========================================================================================================================
		boolean moved=true;

		if(checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(dir)==false)
		{
			if(isWalkingIntoPlayerThisFrame==false||ignoreHitPlayer()==true)
			{
				movePixelInDirection(dir);
				movementDirection=dir;
			}
		}
		else {moved=false;}

		return moved;
	}

	//=========================================================================================================================
	public boolean checkMiddlePixelHitAndMovePixelInDirection(int dir)	//returns 0 if hit wall   ( DOES HIT DETECTION/WALL DETECTION,HIT WITH SPRITE DETECTION )
	{//=========================================================================================================================
		boolean moved=true;

		if(checkMiddlePixelAgainstHitLayerAndNonWalkableEntitiesInDirection(dir)==false)
		{
			if(isWalkingIntoPlayerThisFrame==false||ignoreHitPlayer()==true)
			{
				movePixelInDirection(dir);
				movementDirection=dir;
			}
		}
		else {moved=false;}

		return moved;
	}

	//=========================================================================================================================
	public void movePixelInDirection(int dir)
	{//=========================================================================================================================

		if(dir==DOWNLEFT){decX();incY();}
		else if(dir==DOWNRIGHT){incX();incY();}
		else if(dir==UPLEFT){decX();decY();}
		else if(dir==UPRIGHT){incX();decY();}
		else if(dir==UP){decY();}
		else if(dir==DOWN){incY();}
		else if(dir==LEFT){decX();}
		else if(dir==RIGHT){incX();}
	}


	//=========================================================================================================================
	public boolean ifCanMoveAPixelThisFrameSubtractAndReturnTrue()
	{//=========================================================================================================================


		if(pixelsToMoveThisFrame<0.0f)
		{
			pixelsToMoveThisFrame=0.0f;
		}


		if(pixelsToMoveThisFrame>1.0f)
		{
			pixelsToMoveThisFrame-=1.0f;
			return true;
		}
		return false;



		/*if(can_walk()==true)
		{
			ms=0;
			return 1;
		}
		else
		return 0;*/

	}




	//=========================================================================================================================
	public boolean canCreateAtXY(int x,int y)
	{//=========================================================================================================================
	//check hit and fx for x, x-8, y, y+6.
		if(
				getMap().getHitLayerValueAtXYPixels(x-8,y+6)==false
			&&getMap().getCameraBoundsFXLayerAtXYPixels(	x-8,y+6)==0
			&&

			getMap().getHitLayerValueAtXYPixels(x-8,y)==false
			&&getMap().getCameraBoundsFXLayerAtXYPixels(	x-8,y)==0
			&&

			getMap().getHitLayerValueAtXYPixels(x+8,y)==false
			&&getMap().getCameraBoundsFXLayerAtXYPixels(	x+8,y)==0
			&&

			getMap().getHitLayerValueAtXYPixels(x+8,y+6)==false
			&&getMap().getCameraBoundsFXLayerAtXYPixels(	x+8,y+6)==0
			&&

			getMap().getHitLayerValueAtXYPixels(x,y)==false
			&&getMap().getCameraBoundsFXLayerAtXYPixels(	x,y)==0
			&&

			getMap().getHitLayerValueAtXYPixels(x,y+6)==false
			&&getMap().getCameraBoundsFXLayerAtXYPixels(	x,y+6)==0
		)
		return true;

		return false;
	}





	//===========================================================================================================================
	public void setFeetAtMapXY(int mapXPixels2X,int mapYPixels2X)
	{//===========================================================================================================================

		int tileSize=16;

		//setX((mapXPixels2X+(tileSize/2))-w()/2);
		//setY((mapYPixels2X+tileSize)-h());

		setX(mapXPixels2X-middleOffsetX());
		setY(mapYPixels2X-middleOffsetY());

	}









	//=========================================================================================================================
	public int getFrame()
	{//=========================================================================================================================
		return frameIndexInTexture;
	}

	//=========================================================================================================================
	public void setFrame(int f)
	{//=========================================================================================================================
		frameIndexInTexture = f;
	}



	//=========================================================================================================================
	protected void resetAnimationTimer()
	{//=========================================================================================================================
		animationTicksCounter=0;
	}

	//=========================================================================================================================
	public boolean haveTicksPassedSinceLastAnimated_ResetIfTrue(int ticks)
	{//=========================================================================================================================
		if(animationTicksCounter>=ticks)
		{
			resetAnimationTimer();
			return true;
		}
		else
		return false;
	}


	//=========================================================================================================================
	public SpriteAnimationSequence getCurrentAnimation()
	{//=========================================================================================================================
		if(sprite==null)return null;
		if(currentAnimation==null)return null;
		return currentAnimation;
	}

	//=========================================================================================================================
	public void setCurrentAnimation(SpriteAnimationSequence a)
	{//=========================================================================================================================
		currentAnimation = a;
	}

	//=========================================================================================================================
	public void setCurrentAnimationByName(String name)
	{//=========================================================================================================================
		if(sprite==null){log.error("Sprite is null in Entity: "+name()+" while setting AnimationByName");return;}
		SpriteAnimationSequence a = sprite.getAnimationByName(name);
		if(a==null){log.error("Animation name: "+name+" not found in Sprite: "+sprite.name()+" in Entity: "+name());return;}
		currentAnimation = a;
	}

	//=========================================================================================================================
	public void setCurrentAnimationByDirection(int dir)
	{//=========================================================================================================================
		String sequenceName="";
		if(dir==Entity.UP) sequenceName="Up";
		if(dir==Entity.DOWN) sequenceName="Down";
		if(dir==Entity.LEFT) sequenceName="Left";
		if(dir==Entity.RIGHT) sequenceName="Right";
		if(dir==Entity.UPLEFT) sequenceName="UpLeft";
		if(dir==Entity.UPRIGHT) sequenceName="UpRight";
		if(dir==Entity.DOWNLEFT) sequenceName="DownLeft";
		if(dir==Entity.DOWNRIGHT) sequenceName="DownRight";


		if(sprite==null){log.error("Sprite is null in Entity: "+name()+" while setting AnimationByName");return;}
		SpriteAnimationSequence a = sprite.getAnimationByName(sequenceName);
		if(a==null){log.error("Animation name: "+sequenceName+" not found in Sprite: "+sprite.name()+" in Entity: "+name());return;}
		currentAnimation = a;
	}


	//=========================================================================================================================
	public int getSpriteLastFrame()
	{//=========================================================================================================================
		if(sprite==null)return 0;
		if(sprite.frames()==0)return 0;
		return sprite.frames()-1;
	}

	//=========================================================================================================================
	public SpriteAnimationSequence getAnimationBySpriteFrame(int frame)
	{//=========================================================================================================================
		if(sprite==null){log.error("Sprite is null in Entity: "+name()+" while getting AnimationByFrame");}
		SpriteAnimationSequence a = sprite.getAnimationByFrame(frame);

		if(a==null&&sprite.name().equals("Camera")==false&&sprite.name().equals("none")==false)
		{
			log.error("Animation for frame: "+frame+" not found in Sprite: "+sprite.name()+" in Entity: "+name());
			if(BobNet.debugMode)new Exception().printStackTrace();
		}

		return a;
	}

	//=========================================================================================================================
	public void setCurrentAnimationBySpriteFrame(int frame)
	{//=========================================================================================================================
		currentAnimation = getAnimationBySpriteFrame(frame);
	}

	//=========================================================================================================================
	public int getCurrentAnimationNumberOfFrames()
	{//=========================================================================================================================
		if(sprite==null)return 0;
		if(currentAnimation==null)return sprite.frames();
		return sprite.getAnimationNumFramesByAnimation(currentAnimation);
	}

	//=========================================================================================================================
	public int getCurrentAnimationStartFrame()
	{//=========================================================================================================================
		if(sprite==null)return 0;
		if(currentAnimation==null)return 0;
		return currentAnimation.frameStart;
	}

	//=========================================================================================================================
	public int getCurrentAnimationLastFrame()
	{//=========================================================================================================================
		if(sprite==null)return 0;
		if(currentAnimation==null)return getSpriteLastFrame();
		return getCurrentAnimationStartFrame() + getCurrentAnimationNumberOfFrames() - 1;
	}

	//=========================================================================================================================
	public String getCurrentAnimationName()
	{//=========================================================================================================================
		if(sprite==null)return "none";
		if(currentAnimation==null)return "none";
		if(currentAnimation.frameSequenceName.length()==0)return "none";
		if(currentAnimation.frameSequenceName.equals("Frame0"))return "none";

		return currentAnimation.frameSequenceName;
	}

	//=========================================================================================================================
	public int getCurrentFrameOffsetInCurrentAnimation()
	{//=========================================================================================================================

		//this can return a negative value if the current frame is not in the current animation

		return getFrame() - getCurrentAnimationStartFrame();
	}

	//=========================================================================================================================
	public void setFrameOffsetInCurrentAnimation(int frameOffset)
	{//=========================================================================================================================
		setFrame(getCurrentAnimationStartFrame()+frameOffset);
	}

	//=========================================================================================================================
	public void setFrameInAllFrames(int frame)
	{//=========================================================================================================================

		if(frame>getSpriteLastFrame())frame=getSpriteLastFrame();

		setFrame(frame);

		setCurrentAnimationBySpriteFrame(frame);
	}

	//=========================================================================================================================
	public void selectRandomFrame(int from, int toIncluding)
	{//=========================================================================================================================
		int oldFrame = getFrame();

		if(toIncluding>from)
		{
			while(getFrame()==oldFrame)
			{
				setFrame(from + Utils.randUpToIncluding(toIncluding - from));
			}
		}

		setCurrentAnimationBySpriteFrame(getFrame());
	}

	//=========================================================================================================================
	public void selectRandomFrameInAllFrames()
	{//=========================================================================================================================
		selectRandomFrame(0, getSpriteLastFrame());
	}

	//=========================================================================================================================
	public void selectRandomFrameInCurrentAnimation()
	{//=========================================================================================================================
		selectRandomFrame(getCurrentAnimationStartFrame(), getCurrentAnimationLastFrame());
	}

	//=========================================================================================================================
	public void incrementAnimationFrame(int from, int toIncluding)//increments the frame in the current walking direction
	{//=========================================================================================================================

		setFrame(getFrame()+1);

		if(getFrame()>toIncluding)setFrame(from);
	}

	//=========================================================================================================================
	public void incrementAnimationFrameInAllFrames()//increments the frame in the current walking direction
	{//=========================================================================================================================
		incrementAnimationFrame(0, getSpriteLastFrame());
	}

	//=========================================================================================================================
	public void incrementAnimationFrameInCurrentAnimation()//increments the frame in the current walking direction
	{//=========================================================================================================================
		incrementAnimationFrame(getCurrentAnimationStartFrame(), getCurrentAnimationLastFrame());
	}






	//=========================================================================================================================
	public void stopAnimation()
	{//=========================================================================================================================
		setAnimateThroughAllFrames(false);
		setAnimateThroughCurrentAnimation(false);
		setLoopAnimation(false);
	}

	//=========================================================================================================================
	public void setAnimateLoopThroughCurrentAnimation()
	{//=========================================================================================================================
		setFrameToCurrentAnimationStart();
		setAnimateThroughCurrentAnimation(true);
		setLoopAnimation(true);
	}

	//=========================================================================================================================
	public void setAnimateLoopThroughAllFrames()
	{//=========================================================================================================================
		setAnimateThroughAllFrames(true);
		setLoopAnimation(true);

	}

	//=========================================================================================================================
	public void setFrameToAllFramesZero()
	{//=========================================================================================================================
		setFrame(0);
	}

	//=========================================================================================================================
	public void setFrameToCurrentAnimationStart()
	{//=========================================================================================================================
		setFrame(getCurrentAnimationStartFrame());
	}

	//=========================================================================================================================
	public void setAnimateOnceThroughCurrentAnimation()
	{//=========================================================================================================================
		setFrameToCurrentAnimationStart();
		setAnimateThroughCurrentAnimation(true);
		setLoopAnimation(false);

	}

	//=========================================================================================================================
	public void setAnimateOnceThroughAllFrames()
	{//=========================================================================================================================
		setFrameToAllFramesZero();
		setAnimateThroughAllFrames(true);
		setLoopAnimation(false);

	}







	//=========================================================================================================================
	public void doAnimation()
	{//=========================================================================================================================


		if(sprite==null)return;

		if(animatingThroughCurrentAnimation()==true || animatingThroughAllFrames()==true)
		{

			//if(animatingThroughCurrentAnimation()==true&&currentAnimation==null)return;

//			if(name().equals("Player"))
//			{
//				log.debug("hello");
//
//			}


			int startFrame = 0;
			int lastFrame = getSpriteLastFrame();

			if(animatingThroughCurrentAnimation()==true)
			{
				lastFrame = getCurrentAnimationLastFrame();
				startFrame = getCurrentAnimationStartFrame();
			}

			if(getFrame()<startFrame || getFrame() > lastFrame)
			{
				setFrame(startFrame);
			}


			//initialize ticks between loop for this loop (done once on the first frame)
			if(getFrame()==startFrame)
			{
				if(randomUpToTicksBetweenAnimationLoop()==true)
				{
					ticksBetweenAnimationLoopThisLoop = Utils.randUpToIncluding(ticksBetweenAnimationLoop());
				}
				else
				ticksBetweenAnimationLoopThisLoop = ticksBetweenAnimationLoop();
			}


			//set ticks to wait on this frame
			int count = ticksBetweenFrames();
			if(getFrame()==lastFrame)
			{
				if(loopAnimation()==false)return;
				else count=ticksBetweenAnimationLoopThisLoop;
			}




			if(haveTicksPassedSinceLastAnimated_ResetIfTrue(count))
			{
				if(animatingThroughAllFrames()==true)
				{
					if(randomFrames())selectRandomFrameInAllFrames();
					else incrementAnimationFrameInAllFrames();
				}
				else
				if(animatingThroughCurrentAnimation()==true)
				{
					if(randomFrames())selectRandomFrameInCurrentAnimation();
					else incrementAnimationFrameInCurrentAnimation();
				}
			}
		}


	}


	//=========================================================================================================================
	public void setAlphaImmediately(float a)
	{//=========================================================================================================================

		if(a>1.0f)a=1.0f;
		if(a<0.0f)a=0.0f;
		alpha=a;
	}


	//=========================================================================================================================
	public void fadeOutAndDelete()
	{//=========================================================================================================================
		if(alpha>0)
		{
			setToAlpha(0.0f);
		}
		else
		{
			deleteWhenAlphaZero=true;
		}
	}

	//=========================================================================================================================
	public void delete()
	{//=========================================================================================================================

		if(getMap().activeEntityList.contains(this))getMap().activeEntityList.remove(this);

		if(
				getClass().equals(RandomCharacter.class)
				|| getClass().equals(Character.class)
				|| getClass().equals(Player.class)
		)
		{
			Character r = (Character)this;
			r.uniqueTexture = GLUtils.releaseTexture(r.uniqueTexture);
		}

	}



	//=========================================================================================================================
	public void addEventBehavior(String s)
	{//=========================================================================================================================
		eventBehaviorList.add(s);//TODO: handle this stuff right!
	}

//	//=========================================================================================================================
//	public void addBehavior(String s)
//	{//=========================================================================================================================
//		behaviorList().add(s);
//	}
//
//
//	//=========================================================================================================================
//	public void addConnectionTYPEID(String s)
//	{//=========================================================================================================================
//		connectionTYPEIDList().add(s);
//	}






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
	public float getDistanceFromEntity(Entity e)
	{//=========================================================================================================================
		return Utils.distance(middleX(), middleY(), e.middleX(), e.middleY());
	}

	//=========================================================================================================================
	public Entity findNearestEntity()
	{//=========================================================================================================================

		Entity nearestEntity=null;

		int shortestdist=65535;



		for(int n=0;n<getMap().activeEntityList.size();n++)
		{
			Entity currentEntity = getMap().activeEntityList.get(n);

			if(this!=currentEntity)
			{

				float x=middleX()-(currentEntity.middleX());
				float y=middleY()-(currentEntity.middleY());

				x=Math.abs(x);
				y=Math.abs(y);

				int dist = (int)Math.sqrt((x*x)+(y*y));

				if(dist<shortestdist)
				{
					shortestdist=dist;
					nearestEntity = currentEntity;
				}
			}

		}

		return nearestEntity;
	}



	//=========================================================================================================================
	public Entity findNearestEntityInDirection(int dir)
	{//=========================================================================================================================


		//this checks a direction and finds the closest entity within the entity boundaries in that direction

		Entity nearest_entity=null;

		float shortestdist=65535;

		float radiusX = w()/2;
		float radiusY = (h()-hitBoxFromTop())/2;

		for(int n=0;n<getMap().activeEntityList.size();n++)
		{
			Entity e = getMap().activeEntityList.get(n);

			if(this!=e)
			{

				float eMiddleX = e.middleX();
				float eMiddleY = e.middleY();
				float eRadiusX = e.w()/2;
				float eRadiusY = (e.h() - e.hitBoxFromTop())/2;

				if(dir==UP)
				{
					if(middleY()>=eMiddleY&&middleX()+radiusX>=eMiddleX-eRadiusX&&middleX()-radiusX<=eMiddleX+eRadiusX)
					{
						float dist = eMiddleY-middleY();
						if(dist<shortestdist)
						{
							shortestdist=dist;
							nearest_entity=e;
						}
					}
				}
				else
				if(dir==DOWN)
				{
					if(middleY()<=eMiddleY&&middleX()+radiusX>=eMiddleX-eRadiusX&&middleX()-radiusX<=eMiddleX+eRadiusX)
					{
						float dist = middleY()-eMiddleY;
						if(dist<shortestdist)
						{
							shortestdist=dist;
							nearest_entity=e;
						}
					}
				}
				else
				if(dir==LEFT)
				{
					if(middleX()>=eMiddleX&&middleY()+radiusY>=eMiddleY-eRadiusY&&middleY()-radiusY<=eMiddleY+eRadiusY)
					{
						float dist = eMiddleX-middleX();
						if(dist<shortestdist)
						{
							shortestdist=dist;
							nearest_entity=e;
						}
					}
				}
				else
				if(dir==RIGHT)
				{
					if(middleX()<=eMiddleX&&middleY()+radiusY>=eMiddleY-eRadiusY&&middleY()-radiusY<=eMiddleY+eRadiusY)
					{
						float dist = middleX()-eMiddleX;
						if(dist<shortestdist)
						{
							shortestdist=dist;
							nearest_entity=e;
						}
					}
				}

			}
		}

		return nearest_entity;
	}



	//=========================================================================================================================
	public boolean isWalkingIntoEntity(Entity entity)
	{//=========================================================================================================================

		boolean walkingIntoDoor=false;

		if(movementDirection==UP)
		{
			if(
					entity.isXYTouchingMyHitBox(middleX()-1,top()-2)
				|| 	entity.isXYTouchingMyHitBox(middleX(),top()-2)
					)
				walkingIntoDoor=true;
		}
		else
		if(movementDirection==DOWN)
		{
			if(
					entity.isXYTouchingMyHitBox(middleX()-1,bottom()+1)
				|| 	entity.isXYTouchingMyHitBox(middleX(),bottom()+1)

					)
				walkingIntoDoor=true;
		}
		else
		if(movementDirection==LEFT)
		{
			if(		entity.isXYTouchingMyHitBox(left()-2,middleY())//bottom()-1)
				|| 	entity.isXYTouchingMyHitBox(left()-2,middleY()-1)//top()+2)
				//TODO: should check middle for hitBoxLeft() and hitBoxRight() too, in case the player NPC is ever big enough to "straddle" a block. actually, i should check every %8 (%16 now i guess)
					)
				walkingIntoDoor=true;
		}
		else
		if(movementDirection==RIGHT)
		{
			if(		entity.isXYTouchingMyHitBox(right()+1,middleY())//bottom()-1)
				|| entity.isXYTouchingMyHitBox(right()+1,middleY()-1)//top()+2)
					)
				walkingIntoDoor=true;
		}
		return walkingIntoDoor;


	}

	//=========================================================================================================================
	public boolean isWalkingIntoArea(Area area)
	{//=========================================================================================================================

		boolean walkingIntoArea=false;

		if(movementDirection==UP)
		{
			if(
					area.isXYTouchingMyBoundary(middleX()-1,top()-2)
				|| 	area.isXYTouchingMyBoundary(middleX(),top()-2)

					)
				walkingIntoArea=true;
		}
		else
		if(movementDirection==DOWN)
		{
			if(
					area.isXYTouchingMyBoundary(middleX()-1,bottom()+1)
				|| 	area.isXYTouchingMyBoundary(middleX(),bottom()+1)

					)
				walkingIntoArea=true;
		}
		else
		if(movementDirection==LEFT)
		{
			if(		area.isXYTouchingMyBoundary(left()-2,middleY())//bottom()-1)
				|| 	area.isXYTouchingMyBoundary(left()-2,middleY()-1)//top()+2)
				//TODO: should check middle for hitBoxLeft() and hitBoxRight() too, in case the player NPC is ever big enough to "straddle" a block. actually, i should check every %8 (%16 now i guess)
					)
				walkingIntoArea=true;
		}
		else
		if(movementDirection==RIGHT)
		{
			if(		area.isXYTouchingMyBoundary(right()+1,middleY())//bottom()-1)
				|| area.isXYTouchingMyBoundary(right()+1,middleY()-1)//top()+2)
					)
				walkingIntoArea=true;
		}
		return walkingIntoArea;

	}


	//=========================================================================================================================
	public boolean isEntityHitBoxTouchingMyHitBox(Entity e)
	{//=========================================================================================================================
		return isEntityHitBoxTouchingMyHitBoxByAmount(e,0);
	}
	//=========================================================================================================================
	public boolean isNearestEntityHitBoxTouchingMyHitBox()
	{//=========================================================================================================================
		return isNearestEntityHitBoxTouchingMyHitBoxByAmount(0);
	}
	//=========================================================================================================================
	public boolean isAreaCenterTouchingMyHitBox(Area a)
	{//=========================================================================================================================
		return isAreaCenterTouchingMyHitBoxByAmount(a,0);
	}
	//=========================================================================================================================
	public boolean isAreaBoundaryTouchingMyHitBox(Area a)
	{//=========================================================================================================================
		return isAreaBoundaryTouchingMyHitBoxByAmount(a,0);
	}
	//=========================================================================================================================
	public boolean isXYTouchingMyHitBox(float x, float y)
	{//=========================================================================================================================
		return isXYTouchingMyHitBoxByAmount(x,y,0);
	}
	//=========================================================================================================================
	public boolean isXYXYTouchingMyHitBox(float left, float top, float right, float bottom)
	{//=========================================================================================================================
		return isXYXYTouchingMyHitBoxByAmount(left, top, right, bottom,0);
	}
	//=========================================================================================================================
	public boolean isAreaBoundaryTouchingMyMiddleXY(Area a)
	{//=========================================================================================================================
		return isAreaBoundaryTouchingMyMiddleXYByAmount(a,0);
	}
	//=========================================================================================================================
	public boolean isEntityMiddleXYTouchingMyMiddleXY(Entity e)
	{//=========================================================================================================================
		return isEntityMiddleXYTouchingMyMiddleXYByAmount(e,1);
	}
	//=========================================================================================================================
	public boolean isAreaCenterTouchingMyMiddleXY(Area a)
	{//=========================================================================================================================
		return isAreaCenterTouchingMyMiddleXYByAmount(a,1);
	}
	//=========================================================================================================================
	public boolean isXYTouchingMyMiddleXY(float x, float y)
	{//=========================================================================================================================
		return isXYTouchingMyMiddleXYByAmount(x,y,1);
	}
	//=========================================================================================================================
	public boolean isXYXYTouchingMyMiddleXY(float left, float top, float right, float bottom)
	{//=========================================================================================================================
		return isXYXYTouchingMyMiddleXYByAmount(left, top, right, bottom,0);
	}
	//=========================================================================================================================
	public boolean isEntityHitBoxTouchingMyHitBoxByAmount(Entity e,int amt)
	{//=========================================================================================================================
		return Utils.isXYXYTouchingXYXYByAmount(left(), top(), right(), bottom(), e.left(), e.top(), e.right(), e.bottom(),amt);
	}
	//=========================================================================================================================
	public boolean isNearestEntityHitBoxTouchingMyHitBoxByAmount(int amt)
	{//=========================================================================================================================
		return isEntityHitBoxTouchingMyHitBoxByAmount(findNearestEntity(),amt);
	}
	//=========================================================================================================================
	public boolean isAreaCenterTouchingMyHitBoxByAmount(Area a,int amt)
	{//=========================================================================================================================
		return isXYTouchingMyHitBoxByAmount(a.middleX(),a.middleY(),amt);
	}
	//=========================================================================================================================
	public boolean isAreaBoundaryTouchingMyHitBoxByAmount(Area a,int amt)
	{//=========================================================================================================================
		return isXYXYTouchingMyHitBoxByAmount(a.left(),a.top(),a.right(),a.bottom(),amt);
	}
	//=========================================================================================================================
	public boolean isXYTouchingMyHitBoxByAmount(float x, float y,int amt)
	{//=========================================================================================================================
		return isXYXYTouchingMyHitBoxByAmount(x,y,x,y,amt);
	}
	//=========================================================================================================================
	public boolean isXYXYTouchingMyHitBoxByAmount(float left, float top, float right, float bottom,int amt)
	{//=========================================================================================================================
		return Utils.isXYXYTouchingXYXYByAmount(left(), top(), right(), bottom(), left, top, right, bottom,amt);
	}
	//=========================================================================================================================
	public boolean isAreaBoundaryTouchingMyMiddleXYByAmount(Area a,int amt)
	{//=========================================================================================================================
		return isXYXYTouchingMyMiddleXYByAmount(a.left(),a.top(),a.right(),a.bottom(),amt);
	}
	//=========================================================================================================================
	public boolean isEntityMiddleXYTouchingMyMiddleXYByAmount(Entity e,int amt)
	{//=========================================================================================================================
		return isXYTouchingMyMiddleXYByAmount(e.middleX(),e.middleY(),amt);
	}
	//=========================================================================================================================
	public boolean isAreaCenterTouchingMyMiddleXYByAmount(Area a,int amt)
	{//=========================================================================================================================
		return isXYTouchingMyMiddleXYByAmount(a.middleX(),a.middleY(),amt);
	}
	//=========================================================================================================================
	public boolean isXYTouchingMyMiddleXYByAmount(float x, float y,int amt)
	{//=========================================================================================================================
		return isXYXYTouchingMyMiddleXYByAmount(x,y,x,y,amt);
	}
	//=========================================================================================================================
	public boolean isXYXYTouchingMyMiddleXYByAmount(float left, float top, float right, float bottom,int amt)
	{//=========================================================================================================================
		return Utils.isXYXYTouchingXYXYByAmount(middleX(), middleY(), middleX(), middleY(), left, top, right, bottom,amt);
	}





	//=========================================================================================================================
	public boolean isTouchingPlayerInDirection(int dir)
	{//=========================================================================================================================

		if(Player()==null)return false;

		boolean touching_player_entity=false;


		float pTop = Player().top();
		float pBottom = Player().bottom();
		float pLeft = Player().left();
		float pRight = Player().right();


		if(Player()==null)return false;
		if(this==Player())return false;


		if(dir==UP)
		{
				if(
					(
						(
							left()>=pLeft //TODO use touching functions
							&&
							left()<=pRight
						)//hitBoxLeft() side of e is within sprite width
						||
						(
							right()<=pRight
							&&
							right()>=pLeft
						)//hitBoxRight() side of e is within sprite width
					)
					&&
					(
						top()-1<=pBottom
						&&
						top()-1>=pTop
					)
				)
				touching_player_entity=true;
		}
		else
		if(dir==DOWN)
		{

				if(
					(
						(
							left()>=pLeft
							&&
							left()<=pRight
						)//hitBoxLeft() side of e is within sprite width
						||
						(
							right()<=pRight
							&&
							right()>=pLeft
						)//hitBoxRight() side of e is within sprite width
					)
					&&
					(
						bottom()+1>=pTop
						&&
						bottom()+1<=pBottom
					)
				)touching_player_entity=true;

		}
		else
		if(dir==LEFT)
		{

				if(
					(
						(
							top()>=pTop
							&&
							top()<=pBottom
						)//hitBoxTop() side of e is within sprite hit height
						||
						(
							bottom()>=pTop
							&&
							bottom()<=pBottom
						)//hitBoxBottom() side of e is within sprite hit height
					)
					&&
					(
						left()<pRight
						&&
						left()>pLeft
					)
				)touching_player_entity=true;

		}
		else
		if(dir==RIGHT)
		{

				if(
					(
						(
							top()>=pTop
							&&
							top()<=pBottom
						)//hitBoxTop() side of e is within sprite hit height
						||
						(
							bottom()>=pTop
							&&
							bottom()<=pBottom
						)//hitBoxBottom() side of e is within sprite hit height
					)
					&&
					(
						right()>pLeft
						&&
						right()<pRight
					)
				)touching_player_entity=true;

		}

		return touching_player_entity;


	}


	//=========================================================================================================================
	public boolean isHitBoxTouchingEntityInDirectionByAmount(Entity e,int direction,int amt)
	{//=========================================================================================================================
		return isHitBoxTouchingXYXYInDirectionByAmount(e.left(),e.top(),e.right(),e.bottom(),direction,amt);
	}
	//=========================================================================================================================
	public boolean isHitBoxTouchingXYInDirectionByAmount(float x,float y,int direction,int amt)
	{//=========================================================================================================================

		//TODO: make this xy point shine or highlighted or something

		//TODO: should draw all hit boxes for characters

		//this uses point collision

		return isHitBoxTouchingXYXYInDirectionByAmount(x,y,x,y,direction,amt);

	}
	//=========================================================================================================================
	public boolean isHitBoxTouchingXYXYInDirectionByAmount(float left,float top,float right,float bottom,int direction,int amt)
	{//=========================================================================================================================

		if(left==-1)left=middleX();
		if(top==-1)top=middleY();
		if(right==-1)right=middleX();
		if(bottom==-1)bottom=middleY();



		boolean detected=false;

		if(direction==UP)
		{
			if(
				(left())<=(right)&&
				(right())>=(left)&& //TODO use touching functions
				(top())<=(bottom)&&
				((top()-2)-amt)>=(top)
			)detected=true;
		}

		if(direction==DOWN)
		{
			if(
				(left())<=(right)&&
				(right())>=(left)&&
				(bottom())<=(bottom)&&
				((bottom()+2)+amt)>=(top)
			)detected=true;
		}

		if(direction==LEFT)
		{
			if(
				((left()-2)-amt)<=(right)&&
				(left())>=(left)&&
				(top())<=(bottom)&&
				(bottom())>=(top)
			)detected=true;
		}
		if(direction==RIGHT)
		{
			if(
				(right())<=(right)&&
				((right()+2)+amt)>=(left)&&
				(top())<=(bottom)&&
				(bottom())>=(top)
			)detected=true;
		}

		if(direction==UPLEFT)
		{
			if(
				((left()-2)-amt)<=(right)&&
				(left())>=(left)&&
				(top())<=(bottom)&&
				((top()-2)-amt)>=(top)

			)detected=true;
		}
		if(direction==UPRIGHT)
		{
			if(
				(right())<=(right)&&
				((right()+2)+amt)>=(left)&&
				(top())<=(bottom)&&
				((top()-2)-amt)>=(top)

			)detected=true;
		}
		if(direction==DOWNLEFT)
		{
			if(
				((left()-2)-amt)<=(right)&&
				(left())>=(left)&&
				(bottom())<=(bottom)&&
				(bottom()+amt)>=(top)
			)detected=true;
		}
		if(direction==DOWNRIGHT)
		{
			if(
				(right())<=(right)&&
				((right()+2)+amt)>=(left)&&
				(bottom())<=(bottom)&&
				(bottom()+amt)>=(top)
			)detected=true;
		}
		return detected;

	}









	//=========================================================================================================================
	public float top()
	{//=========================================================================================================================
		return (y()+(hitBoxFromTop()));
	}
	//=========================================================================================================================
	public float left()
	{//=========================================================================================================================
		return (x()+(hitBoxFromLeft()));
	}
	//=========================================================================================================================
	public float right()
	{//=========================================================================================================================
		return (x()+w())-(hitBoxFromRight());
	}
	//=========================================================================================================================
	public float bottom()
	{//=========================================================================================================================
		return (y()+h())-(hitBoxFromBottom());
	}
	//=========================================================================================================================
	public final float middleX()
	{//=========================================================================================================================
		return (left()+((right()-left())/2));
	}
	//=========================================================================================================================
	public final float middleY()
	{//=========================================================================================================================
		return (
					bottom()
					-
					(
						(
							(
								h()
								-
								(
									hitBoxFromTop()
								)
							)
							-
							hitBoxFromBottom()
						)
						/2
					)
				);
	}



	public float roundedMiddleX()
	{
		return Math.round(middleX());
	}

	public float roundedMiddleY()
	{
		return Math.round(middleY());
	}

	public float middleOffsetX()
	{
		return middleX()-x();
	}

	public float middleOffsetY()
	{
		return middleY()-y();
	}


	//=========================================================================================================================
	private float screenX()
	{//=========================================================================================================================

		float zoom = Cameraman().getZoom();

		float mapCameraXPixelsHQ = getMap().mapCamX();

		float left 	= x()+standJitterX;
		float right 	= left + w();
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

		float top 	= y()+standJitterY;
		float bottom 	= top + h();
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
	public float screenTop()
	{//=========================================================================================================================
		return screenY();

	}



	//=========================================================================================================================
	public final float screenMiddleHitboxY()
	{//=========================================================================================================================
		float zoom = Cameraman().getZoom();
		return (float)((screenTop()+(h()*zoom))-((h()*zoom-(hitBoxFromTop())*zoom)/2));

	}

	//=========================================================================================================================
	/** This is the offset from x to the hitbox */
	public float hitBoxFromLeft()
	{//=========================================================================================================================
		if(sprite==null||currentAnimation==null)return 0;

		return currentAnimation.hitBoxFromLeftPixels1X*2*scale();
	}

	//=========================================================================================================================
	/** This is the offset from x + width to the hitbox, it is a positive number but subtracted: x + width - hitbox */
	public float hitBoxFromRight()
	{//=========================================================================================================================
		if(sprite==null||currentAnimation==null)return 0;

		return currentAnimation.hitBoxFromRightPixels1X*2*scale();
	}

	//=========================================================================================================================
	/** This is the offset from y to the hitbox, this is larger for people as it offsets down to the feet */
	public float hitBoxFromTop()
	{//=========================================================================================================================
		if(sprite==null||currentAnimation==null)return 0;

		return currentAnimation.hitBoxFromTopPixels1X*2*scale();
	}

	//=========================================================================================================================
	/** This is the offset from y + height to the hitbox, it is a positive number but subtracted: y + height - hitbox */
	public float hitBoxFromBottom()
	{//=========================================================================================================================
		if(sprite==null||currentAnimation==null)return 0;

		return currentAnimation.hitBoxFromBottomPixels1X*2*scale();
	}

	//=========================================================================================================================
	public float shadowStart()
	{//=========================================================================================================================
		if(sprite==null||currentAnimation==null)return 0;

		return (float)(currentAnimation.hitBoxFromTopPixels1X*2)/(float)sprite.h();

	}






	public float x(){return mapX;}
	public float y(){return mapY;}



	public void setX(float x)
	{
		mapX = x;
	}


	public void setY(float y)
	{
		mapY = y;
	}


	public void incX(){mapX++;}
	public void incY(){mapY++;}
	public void decX(){mapX--;}
	public void decY(){mapY--;}


	//=========================================================================================================================
	public float w()
	{//=========================================================================================================================

		if(sprite!=null)return (sprite.w()*scale());
		else return 0;
	}


	//=========================================================================================================================
	public  float h()
	{//=========================================================================================================================
		if(sprite!=null)return (sprite.h()*scale());
		else return 0;
	}


	public EntityData getData(){return data;}



	public String name(){return getData().name();}
	public String comment(){return getData().comment();}
	public int id(){return getData().id();}
	//public int mapID(){return getData().mapID();}
	public String spriteName(){return getData().spriteName();}


	public boolean isNPC(){return getData().isNPC();}
	public boolean pushable(){return getData().pushable();}
	public boolean nonWalkable(){return getData().nonWalkable();}
	public float toAlpha(){return getData().toAlpha();}
	public float scale(){return getData().scale();}
	public boolean disableShadow(){return getData().disableShadow();}
	public boolean aboveWhenEqual(){return getData().aboveWhenEqual();}
	public boolean alwaysOnTop(){return getData().alwaysOnTop();}
	public boolean alwaysOnBottom(){return getData().alwaysOnBottom();}
	public RenderOrder renderOrder(){return getData().renderOrder();}
	public boolean aboveTopLayer(){return getData().aboveTopLayer();}
	public int initialFrame(){return getData().initialFrame();}
	public boolean animatingThroughAllFrames(){return getData().animatingThroughAllFrames();}
	public boolean randomFrames(){return getData().randomFrames();}
	public boolean randomUpToTicksBetweenFrames(){return getData().randomUpToTicksBetweenFrames();}//TODO
	public boolean randomUpToTicksBetweenAnimationLoop(){return getData().randomUpToTicksBetweenAnimationLoop();}
	public int ticksBetweenFrames(){return getData().ticksBetweenFrames();}
	public int ticksBetweenAnimationLoop(){return getData().ticksBetweenAnimationLoop();}

	public float ticksPerPixelMoved(){return getData().ticksPerPixelMoved();}

	//public int eventID(){return getData().eventID();}
	public EventData eventData(){return getData().eventData();}
	public boolean onlyHereDuringEvent(){return getData().onlyHereDuringEvent();}
	public float voicePitch(){return getData().voicePitch();}
	public boolean movementAnimationDisabled(){return getData().movementAnimationDisabled();}
	public boolean ignoreHitLayer(){return getData().hitLayerDisabled();}
	public boolean ignoreHitPlayer(){return getData().ignoreHitPlayer();}
	public boolean pullPlayer(){return getData().pullPlayer();}
	public boolean pushPlayer(){return getData().pushPlayer();}

	public boolean animatingThroughCurrentAnimation(){return getData().animatingThroughCurrentAnimation();}
	public boolean loopAnimation(){return getData().loopAnimation();}

	public ArrayList<String> connectionTYPEIDList(){return getData().connectionTYPEIDList();}
	public ArrayList<String> behaviorList(){return getData().behaviorList();}

	public String getTYPEIDString(){return getData().getTYPEIDString();}





	//set
	public void setID(int s){getData().setID(s);}
	public void setName(String s){getData().setName(s);}
	public void setComment(String s){getData().setComment(s);}

	public void setSpawnXPixelsHQ(float s){getData().setSpawnXPixels1X(s/2.0f);}
	public void setSpawnYPixelsHQ(float s){getData().setSpawnYPixels1X(s/2.0f);}
	public void setIsNPC(boolean s){getData().setIsNPC(s);}
	public void setPushable(boolean s){getData().setPushable(s);}
	public void setNonWalkable(boolean s){getData().setNonWalkable(s);}
	public void setToAlpha(float alpha){getData().setToAlpha(alpha);}
	public void setScale(float s){getData().setScale(s);}
	public void setDisableShadow(boolean s){getData().setDisableShadow(s);}
	public void setInitialFrame(int f){getData().setInitialFrame(f);}
	public void setRandomFrames(boolean s){getData().setRandomFrames(s);}
	public void setRandomUpToTicksBetweenFrames(boolean s){getData().setRandomUpToTicksBetweenFrames(s);}//TODO
	public void setRandomUpToTicksBetweenAnimationLoop(boolean s){getData().setRandomUpToTicksBetweenAnimationLoop(s);}
	public void setTicksBetweenFrames(int s){getData().setTicksBetweenFrames(s);}
	public void setTicksBetweenAnimationLoop(int s){getData().setTicksBetweenAnimationLoop(s);}

	public void setTicksPerPixelMoved(float s){getData().setTicksPerPixelMoved(s);}
	public void setRenderOrder(RenderOrder s){getData().setRenderOrder(s);}
	public void setAboveTopLayer(boolean s){getData().setAboveTopLayer(s);}
	public void setAboveWhenEqual(boolean s){getData().setAboveWhenEqual(s);}
	public void setAlwaysOnBottom(boolean s){getData().setAlwaysOnBottom(s);}
	public void setAlwaysOnTop(boolean s){getData().setAlwaysOnTop(s);}
	public void setOnlyHereDuringEvent(boolean s){getData().setOnlyHereDuringEvent(s);}
	public void setVoicePitch(float s){getData().setVoicePitch(s);}
	public void setAnimationDisabled(boolean s){getData().setAnimationDisabled(s);}
	public void setHitLayerDisabled(boolean s){getData().setHitLayerDisabled(s);}
	public void setIgnoreHitPlayer(boolean s){getData().setIgnoreHitPlayer(s);}
	//public void setEventID(int s){getData().setEventID(s);}

	public void setAnimateThroughAllFrames(boolean s){getData().setAnimateThroughAllFrames(s);}
	public void setAnimateThroughCurrentAnimation(boolean s){getData().setAnimateThroughCurrentAnimation(s);}
	public void setLoopAnimation(boolean s){getData().setLoopAnimation(s);}



}