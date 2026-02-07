package com.bobsgame.client.engine.game;

//import org.lwjgl.input.Keyboard;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.Enumeration;

import com.bobsgame.client.ControlsManager;
//import com.bobsgame.debug.DebugConsole;
//import com.bobsgame.debug.DebugText;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.entity.Character;
import com.bobsgame.client.engine.map.Area;
import com.bobsgame.client.engine.map.Door;
import com.bobsgame.client.engine.map.Map;
import com.bobsgame.client.engine.map.MapManager;
import com.bobsgame.client.engine.map.WarpArea;
import com.bobsgame.client.engine.sound.AudioManager;
import com.bobsgame.client.engine.text.Caption;
import com.bobsgame.client.engine.text.CaptionManager;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.EntityData;
import com.bobsgame.shared.Utils;
import com.bobsgame.shared.MapData.RenderOrder;
import com.bobsgame.client.engine.text.BobFont;

//import java.io.IOException;

//import static org.lwjgl.opengl.GL11.*;


//import java.applet.Applet;
//import java.awt.BorderLayout;
//import java.awt.Canvas;
//import org.lwjgl.LWJGLException;
//import org.lwjgl.input.Keyboard;
//import org.lwjgl.input.Mouse;
//import org.lwjgl.openal.AL;
//import org.lwjgl.opengl.DisplayMode;

//import com.bobsgame.editor.BobColor;
//import org.newdawn.slick.opengl.Texture;
//import org.newdawn.slick.opengl.TextureLoader;
//import org.newdawn.slick.util.ResourceLoader;


//=========================================================================================================================
public class Player extends Character
{//=========================================================================================================================





	//public static SpriteAsset walkingSprite = SpriteAssetIndex.sprite_bob;
	//public static SpriteAsset runningSprite = SpriteAssetIndex.sprite_yuurunning;



	public int GLOBAL_main_sprite_input_off=0;
	public int GLOBAL_main_sprite_actions_off=0;
	public int GLOBAL_main_sprite_fx_off=0;


	public boolean noInput=false;


	public Caption autopilotCaption = null;





	public float forceX = 0.0f;
	public float forceY = 0.0f;

	float forceFactor = 0;//0.1f*pixelsToMoveThisFrame;
	float frictionFactor = 0;//0.0f2f*pixelsToMoveThisFrame;

	float speedLimit = 1.5f;







	//=========================================================================================================================
	public Player(Engine g, String spriteName)
	{//=========================================================================================================================

		super(g, new EntityData(-1,"Player",spriteName,0,0), null);

		setTicksPerPixelMoved(5);

		setScale(1.25f);

		rotationAnimationSpeedTicks = 100;//80;

	}

	//=========================================================================================================================
	public Player(Engine g)
	{//=========================================================================================================================
		this(g,"");
	}




	//=========================================================================================================================
	@Override
	public void update()
	{//=========================================================================================================================
		if(ClientGameEngine().playerExistsInMap==false)return;

		super.update();


		handlePlayerControls();

		//this is done here regardless of controls so that external movements still trigger animation and sound, i.e. cutscenes
		checkIfMoved();

		setSpeed();

		doPlayerSound();

		handleAreas();


		doCharacterAnimation();

	}

	//========================================================================================================================='
	@Override
	public void render(float f)
	{//=========================================================================================================================
		if(ClientGameEngine().playerExistsInMap==false)return;
		super.render(f);
	}


//	//=========================================================================================================================
//	public Map getMap()
//	{//=========================================================================================================================
//		return CurrentMap();
//	}


	boolean autopilotActive = false;//TODO: handle this

	//=========================================================================================================================
	public void setAutoPilot(boolean b)
	{//=========================================================================================================================
		autopilotActive = b;
	}

	//=========================================================================================================================
	public boolean isAutoPilotOn()
	{//=========================================================================================================================
		return autopilotActive;
	}

	//=========================================================================================================================
	public void handleAreas()
	{//=========================================================================================================================


		//go through all areas on this map
		if(getMap().currentState==null)return;

		Enumeration<Area> aEnum = getMap().currentState.areaByNameHashtable.elements();
		//areas
		while(aEnum.hasMoreElements())
		{
			Area a = aEnum.nextElement();

			if(

				a.isXYXYTouchingMyBoundary(left(),top(),right(),bottom())

			)
			{
				if(a.playerFaceDirection())
				if(a.standSpawnDirection()!=-1)
				{
					if(a.standSpawnDirection()==0)movementDirection=UP;
					if(a.standSpawnDirection()==1)movementDirection=DOWN;
					if(a.standSpawnDirection()==2)movementDirection=LEFT;
					if(a.standSpawnDirection()==3)movementDirection=RIGHT;
				}


				if(a.autoPilot()&&a.connectionTYPEIDList().size()>0)
				{
					autopilotActive = true;
				}
			}

		}


		if(isAutoPilotOn()==true)
		{

			if(autopilotCaption==null)
			{
				autopilotCaption = CaptionManager().newManagedCaption(Caption.CENTERED_OVER_ENTITY, 0, -1, "Autopilot", BobFont.font_normal_11_outlined, BobColor.RED, BobColor.CLEAR, RenderOrder.ABOVE_TOP, 1.0f, 0);
			}

		}
		else
		{
			if(autopilotCaption!=null)
			{
				autopilotCaption.deleteFadeOut();
				autopilotCaption = null;
			}
		}

	}



	public long lastPlayedFootstepSoundTicksCounter = 0;
	//=========================================================================================================================
	public void doPlayerSound()
	{//=========================================================================================================================
		if(moved==true)
		{
			lastPlayedFootstepSoundTicksCounter+=Engine().engineTicksPassed();

			if(lastPlayedFootstepSoundTicksCounter>ticksPerPixelMoved()*60)
			{
				lastPlayedFootstepSoundTicksCounter=0;

				AudioManager().playSound("footstep",1.0f,Utils.randMinMaxFloat(0.5f,1.0f),1);
			}
		}
		else
		if(moved==false)
		{
			if(standing==true)
			{
				//TODO: stop playing footsteps?
			}

		}
	}




	//=========================================================================================================================
	public void setSpeed()
	{//=========================================================================================================================

		//============here we are automatically making main sprite stand after half a second, and also turning off footstep sound.

		if(ClientGameEngine()!=null&&ClientGameEngine().controlsEnabled==false)return;


		//if player is moving
		if(moved==true)
		{


			//set running speed if running (animation is done in animation)
			if(running==true)
			{

				//walking_speed=YUU_RUNNING_SPEED;
				//if(cameraman->walking_speed>PLAYER_npc->walking_speed)cameraman->walking_speed=PLAYER_npc->walking_speed;

				//TODO: increase all of these speeds logarithmically
				setTicksPerPixelMoved(3);
				Cameraman().setTicksPerPixelMoved(ticksPerPixelMoved()-1);//TODO: should have the cameraman speed change set in the cameraman, probably

			}
			else
			if(running==false)
			{
				//accelerate to max walking speed (from standing speed) if enough time has passed
				/*

					static int last_vbl=0;
					if(last_vbl!=vbl_var)
					{
						last_vbl=vbl_var;
						//if(vbl_var%5==0&&
							if(PLAYER_npc->walking_speed>YUU_WALKING_SPEED)PLAYER_npc->walking_speed-=SPEED_ACCEL_INCREMENT_AMOUNT;
					}

				//TODO: also slow down if speed is still running speed
				 */


				setTicksPerPixelMoved(5);
				Cameraman().setTicksPerPixelMoved(6);

			}

		}
		else
		{
			if(standing==true)
			{
				//TODO: set standing speed
				//PLAYER_npc->walking_speed=YUU_STANDING_SPEED;
			}
		}

	}



	//=========================================================================================================================
	public void handlePlayerControls()
	{//=========================================================================================================================

			if(

					ClientGameEngine()!=null
					&&
					(

						ClientGameEngine().controlsEnabled==false
						||
						ClientGameEngine().areAnyMenusOpen()
					)

			)
			{
				noInput=true;
				running=false;
				forceX=0;
				forceY=0;
				return;
			}

			//TODO: move all the input stuff into the controlsManager and have it send in a direction pressed

			//Utils.distance(0, 0, 1, 1);


			//int temp_map_x = map_x;
			//int temp_map_y = map_y;

			noInput=false;

			int direction = -1;




			if(ControlsManager().BUTTON_RIGHT_HELD==true&&ControlsManager().BUTTON_DOWN_HELD==true){direction=DOWNRIGHT;}
			else
			if(ControlsManager().BUTTON_RIGHT_HELD==true&&ControlsManager().BUTTON_UP_HELD==true){direction=UPRIGHT;}
			else
			if(ControlsManager().BUTTON_LEFT_HELD==true&&ControlsManager().BUTTON_DOWN_HELD==true){direction=DOWNLEFT;}
			else
			if(ControlsManager().BUTTON_LEFT_HELD==true&&ControlsManager().BUTTON_UP_HELD==true){direction=UPLEFT;}
			else
			if(ControlsManager().BUTTON_RIGHT_HELD==true){direction=RIGHT;}
			else
			if(ControlsManager().BUTTON_LEFT_HELD==true){direction=LEFT;}
			else
			if(ControlsManager().BUTTON_UP_HELD==true){direction=UP;}
			else
			if(ControlsManager().BUTTON_DOWN_HELD==true){direction=DOWN;}
			else
			noInput=true;





			//========handle running
			if(ControlsManager().BUTTON_RBRACKET_HELD==true||ControlsManager().BUTTON_LSHIFT_HELD==true)
			{
				running=true;
			}
			else
			{
				running=false;
			}



			forceFactor = 0.1f*pixelsToMoveThisFrame;
			//frictionFactor = 0.0f2f*pixelsToMoveThisFrame;
			frictionFactor = 0.04f*pixelsToMoveThisFrame;




			if(direction==-1)
			{
				//reduce force/apply friction
				if(forceX>0)
				{
					forceX-=frictionFactor;
					if(forceX<0)forceX = 0.0f;
				}
				if(forceX<0)
				{
					forceX+=frictionFactor;
					if(forceX>0)forceX = 0.0f;
				}

				if(forceY>0)
				{
					forceY-=frictionFactor;
					if(forceY<0)forceY = 0.0f;
				}
				if(forceY<0)
				{
					forceY+=frictionFactor;
					if(forceY>0)forceY = 0.0f;
				}

			}

			if(direction==LEFT)
			{
				forceX-=forceFactor;
				if(forceX<-speedLimit)forceX=-speedLimit;

				//reduce force/apply friction
				if(forceY>0)
				{
					forceY-=frictionFactor;
					if(forceY<0)forceY = 0.0f;
				}
				if(forceY<0)
				{
					forceY+=frictionFactor;
					if(forceY>0)forceY = 0.0f;
				}
			}
			if(direction==RIGHT)
			{
				forceX+=forceFactor;
				if(forceX>speedLimit)forceX=speedLimit;

				if(forceY>0)
				{
					forceY-=frictionFactor;
					if(forceY<0)forceY = 0.0f;
				}
				if(forceY<0)
				{
					forceY+=frictionFactor;
					if(forceY>0)forceY = 0.0f;
				}
			}

			if(direction==UP)
			{
				forceY-=forceFactor;
				if(forceY<-speedLimit)forceY=-speedLimit;

				if(forceX>0)
				{
					forceX-=frictionFactor;
					if(forceX<0)forceX = 0.0f;
				}
				if(forceX<0)
				{
					forceX+=frictionFactor;
					if(forceX>0)forceX = 0.0f;
				}

			}
			if(direction==DOWN)
			{
				forceY+=forceFactor;
				if(forceY>speedLimit)forceY=speedLimit;

				if(forceX>0)
				{
					forceX-=frictionFactor;
					if(forceX<0)forceX = 0.0f;
				}
				if(forceX<0)
				{
					forceX+=frictionFactor;
					if(forceX>0)forceX = 0.0f;
				}


			}

			if(direction==UPLEFT)
			{

				forceX-=forceFactor;
				if(forceX<-speedLimit)forceX=-speedLimit;

				forceY-=forceFactor;
				if(forceY<-speedLimit)forceY=-speedLimit;

			}
			if(direction==UPRIGHT)
			{

				forceX+=forceFactor;
				if(forceX>speedLimit)forceX=speedLimit;

				forceY-=forceFactor;
				if(forceY<-speedLimit)forceY=-speedLimit;
			}
			if(direction==DOWNLEFT)
			{

				forceX-=forceFactor;
				if(forceX<-speedLimit)forceX=-speedLimit;


				forceY+=forceFactor;
				if(forceY>speedLimit)forceY=speedLimit;

			}
			if(direction==DOWNRIGHT)
			{
				forceX+=forceFactor;
				if(forceX>speedLimit)forceX=speedLimit;

				forceY+=forceFactor;
				if(forceY>speedLimit)forceY=speedLimit;
			}


			if(direction!=-1)
			{
				movementDirection = direction;
			}


			if(forceX<0)
			{
				move(LEFT, -forceX*pixelsToMoveThisFrame);
			}
			if(forceX>0)
			{
				move(RIGHT, forceX*pixelsToMoveThisFrame);
			}
			if(forceY<0)
			{
				move(UP, -forceY*pixelsToMoveThisFrame);
			}
			if(forceY>0)
			{
				move(DOWN, forceY*pixelsToMoveThisFrame);
			}

	}











	//=========================================================================================================================
	public boolean checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(int direction)
	{//=========================================================================================================================

		//this checks one pixel forward in a particular direction, not the current position



		boolean hit_wall=true;

		if(direction==UP)
		{
			if(		checkXYAgainstHitLayerAndNonWalkableEntities(left()+1,top()-1)==false
				&& 	checkXYAgainstHitLayerAndNonWalkableEntities(middleX()-1,top()-1)==false
				&& 	checkXYAgainstHitLayerAndNonWalkableEntities(middleX(),top()-1)==false
				&& 	checkXYAgainstHitLayerAndNonWalkableEntities(right()-3,top()-1)==false//right is -2 because x+size_y is outside the sprite and not inside it

					)
				hit_wall=false;
		}
		else
		if(direction==DOWN)
		{
			if(		checkXYAgainstHitLayerAndNonWalkableEntities(left()+1,bottom()+1)==false //bottom is not +1 because y+size_y is outside the sprite and not inside it
				&& 	checkXYAgainstHitLayerAndNonWalkableEntities(middleX()-1,bottom()+1)==false //put bottom+1 back because otherwise feet clip through a fraction of a pixel
				&& 	checkXYAgainstHitLayerAndNonWalkableEntities(middleX(),bottom()+1)==false
				&& 	checkXYAgainstHitLayerAndNonWalkableEntities(right()-3,bottom()+1)==false

					)
				hit_wall=false;
		}
		else
		if(direction==LEFT)
		{
			if(		checkXYAgainstHitLayerAndNonWalkableEntities(left(),bottom()-1)==false
				&& 	checkXYAgainstHitLayerAndNonWalkableEntities(left(),top()+2)==false

				//TODO: should check middle for hitBoxLeft() and hitBoxRight() too, in case the player NPC is ever big enough to "straddle" a block. actually, i should check every %8 (%16 now i guess)
					)
				hit_wall=false;
		}
		else
		if(direction==RIGHT)
		{
			if(		checkXYAgainstHitLayerAndNonWalkableEntities(right()-1,bottom()-1)==false//added +1 to fix sticking in wall
				&& checkXYAgainstHitLayerAndNonWalkableEntities(right()-1,top()+2)==false

					)
				hit_wall=false;
		}
		return hit_wall;





	}


	//=========================================================================================================================
	/**
	 * Sets walk_dir to direction.
	 * For each pixel allowed to move this frame:
	 * checks hit (which checks non-walkable entities as well) in direction (or both directions for diagonals)
	 * then moves pixel.
	 * Moving diagonally counts as one pixel.
	 */

	public void move(int direction, float pixels) //move_check_hit_animate_set_fx_layer
	{//=========================================================================================================================




		//if(direction>3)pixelsToMoveThisFrame/=Math.sqrt(2);//0.75f;//only move half speed on diagonals

		//for(int p=0;p<pixelsToMoveThisFrame;p++)
		{

			//int success=1;

			/*if(direction==UPRIGHT)//UPRIGHT
			{
				int canGoUp=0;
				int canGoRight=0;


				if(check_hit_direction(RIGHT)==0)canGoRight=1;
				if(check_hit_direction(UP)==0)canGoUp=1;

				//if(canGoUp==1&&canGoRight==1)move_pixel(UPRIGHT);
				//else if(canGoUp==1)move_pixel(UP);
				//else if(canGoRight==1)move_pixel(RIGHT);

				if(canGoUp==1)move_pixel(UP);
				if(canGoRight==1)move_pixel(RIGHT);

			}
			else
			if(direction==DOWNLEFT)//DOWNLEFT
			{
				int canGoDown=0;
				int canGoLeft=0;

				if(check_hit_direction(LEFT)==0)canGoLeft=1;
				if(check_hit_direction(DOWN)==0)canGoDown=1;

				//if(canGoDown==1&&canGoLeft==1)move_pixel(DOWNLEFT);
				//else if(canGoDown==1)move_pixel(DOWN);
				//else if(canGoLeft==1)move_pixel(LEFT);

				if(canGoDown==1)move_pixel(DOWN);
				if(canGoLeft==1)move_pixel(LEFT);

			}
			else
			if(direction==DOWNRIGHT)//DOWNRIGHT
			{
				int canGoDown=0;
				int canGoRight=0;

				if(check_hit_direction(RIGHT)==0)canGoRight=1;
				if(check_hit_direction(DOWN)==0)canGoDown=1;

				//if(canGoDown==1&&canGoRight==1)move_pixel(DOWNRIGHT);
				//else if(canGoDown==1)move_pixel(DOWN);
				//else if(canGoRight==1)move_pixel(RIGHT);

				if(canGoDown==1)move_pixel(DOWN);
				if(canGoRight==1)move_pixel(RIGHT);


			}
			else
			if(direction==UPLEFT)//UPLEFT
			{
				int canGoUp=0;
				int canGoLeft=0;

				if(check_hit_direction(LEFT)==0)canGoLeft=1;
				if(check_hit_direction(UP)==0)canGoUp=1;

				//if(canGoUp==1&&canGoLeft==1)move_pixel(UPLEFT);
				//else if(canGoUp==1)move_pixel(UP);
				//else if(canGoLeft==1)move_pixel(LEFT);

				if(canGoUp==1)move_pixel(UP);
				if(canGoLeft==1)move_pixel(LEFT);



			}
			else*/


				int wholePixels = (int)pixels;
				float pixelRemainder = (pixels-wholePixels);

				int mapXWholePixels = (int)x();
				float mapXRemainder = (x()-mapXWholePixels);

				int mapYWholePixels = (int)y();
				float mapYRemainder = (y()-mapYWholePixels);


				if(direction==RIGHT)//RIGHT
				{

					for(int i=0; i<(int)pixels; i++)if(checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT)==false)movePixelInDirection(RIGHT);

					if(mapXRemainder+pixelRemainder>=1.0f)
					{
						if(checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT)==false)setX(x()+pixelRemainder);
					}
					else setX(x()+pixelRemainder);

				}
				else
				if(direction==LEFT)//LEFT
				{

					for(int i=0; i<(int)pixels; i++)if(checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT)==false)movePixelInDirection(LEFT);

					if(mapXRemainder-pixelRemainder<0.0f)
					{
						if(checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT)==false)setX(x()-pixelRemainder);
					}
					else setX(x()-pixelRemainder);

				}
				else
				if(direction==UP)//UP
				{
					for(int i=0; i<(int)pixels; i++)if(checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP)==false)movePixelInDirection(UP);

					if(mapYRemainder-pixelRemainder<0.0f)
					{
						if(checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP)==false)setY(y()-pixelRemainder);
					}
					else setY(y()-pixelRemainder);


				}
				else
				if(direction==DOWN)//DOWN
				{
					for(int i=0; i<(int)pixels; i++)if(checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN)==false)movePixelInDirection(DOWN);

					if(mapYRemainder+pixelRemainder>=1.0f)
					{
						if(checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN)==false)setY(y()+pixelRemainder);
					}
					else setY(y()+pixelRemainder);

				}



			//else return 0;
		}


		//return success;

	}















}
