package com.bobsgame.client.engine.event;

import java.util.ArrayList;


import com.bobsgame.client.ControlsManager;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.entity.Entity;
import com.bobsgame.client.engine.entity.SpriteManager;
import com.bobsgame.client.engine.entity.ScreenSprite;
import com.bobsgame.client.engine.map.Area;
import com.bobsgame.client.engine.text.Caption;
import com.bobsgame.client.engine.text.CaptionManager;
import com.bobsgame.client.engine.text.BobFont;
import com.bobsgame.client.engine.text.TextManager;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.Utils;
import com.bobsgame.shared.MapData.RenderOrder;




//=========================================================================================================================
public class ActionManager extends EnginePart
{//=========================================================================================================================



	Caption actionCaption=null;


	ScreenSprite actionIconScreenSprite=null;


	public int ACTION_in_action_range=0;

	static public int ACTIONCAPTIONTYPE_NONE=0;
	static public int ACTIONCAPTIONTYPE_TILE=1;
	static public int ACTIONCAPTIONTYPE_XY=2;
	static public int ACTIONCAPTIONTYPE_XYXY=3;
	static public int ACTIONCAPTIONTYPE_NPC=4;
	static public int ACTIONCAPTIONTYPE_AREA=5;


	//=========================================================================================================================
	public class Coords
	{//=========================================================================================================================
		int x = 0;
		int y = 0;

		public Coords(int x, int y)
		{
			this.x=x;
			this.y=y;
		}
	}

	public ArrayList<Coords> actionsThisFrame = new ArrayList<Coords>();


	//=========================================================================================================================
	public ActionManager(Engine g)
	{//=========================================================================================================================

		super(g);



		//make text icon texture

		//send into new sprite

		//DONE: new Entity(texture filename) should add itself to the entity manager automatically.. G.entityManager.add(this)

		//new Caption() should do this too



		if(actionIconScreenSprite==null)
		{
			actionIconScreenSprite = new ScreenSprite(g,"button", "actionIcon");//HARDWARE_create_sprite(TEXT_button_icon_GFX,0,1,1.0f,actionx-8,actiony+1,255);
			actionIconScreenSprite.draw=false;

			actionIconScreenSprite.setAnimateLoopThroughAllFrames();
			actionIconScreenSprite.setRandomUpToTicksBetweenAnimationLoop(false);
			actionIconScreenSprite.setTicksBetweenFrames(60);
			actionIconScreenSprite.setTicksBetweenAnimationLoop(0);
		}

	}



	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================


	}




	//=========================================================================================================================
	public void deleteIfNoAction()
	{//=========================================================================================================================

		//if(PLAYER_check_action_dont_run(facing_direction)==0)
			if(actionCaption!=null)
				if(actionCaption.actionCaptionType==ACTIONCAPTIONTYPE_TILE)	//only delete action tile captions
				{
					actionCaption.deleteFadeOut();
					actionCaption=null;
					actionIconScreenSprite.draw=false;
				}
	}



/*
	//=========================================================================================================================
	static public boolean ACTION_check(String label)	//for action tiles. need a way to deinit.
	{//=========================================================================================================================

		if(player()==null)return false;

		if(ACTION_in_action_range==0)
		{
			ACTION_in_action_range=1;

			if(
				textMan().GLOBAL_text_engine_state==0
				&&player().GLOBAL_main_sprite_actions_off==0
			)
			{
				if(ACTION_caption!=null)
				{
					ACTION_replace_caption(label);
				}
				else
				{
					ACTION_make_caption(label);
					ACTION_caption.actioncaptiontype=ACTIONCAPTIONTYPE_TILE;
				}

				if(
					ACTION_caption!=null
					&&ControlsManager.BUTTON_ACTION_PRESSED==true
					&&label.compareTo(ACTION_caption.text)==0
					&&ACTION_caption.actioncaptiontype==ACTIONCAPTIONTYPE_TILE
				)
				{
					ACTION_delete_caption_sound();
					return true;
				}
			}
			else
			{
				if(
					ACTION_caption!=null
					&&label.compareTo(ACTION_caption.text)==0
					&&ACTION_caption.actioncaptiontype==ACTIONCAPTIONTYPE_TILE
				)
				{
					ACTION_delete_caption_no_sound();
				}
			}
		}

		return false;

	}*/

	//=========================================================================================================================
	public boolean xy(int x,int y,String label)
	{//=========================================================================================================================

		return checkAll(x,y,x+1,y+1,label,ACTIONCAPTIONTYPE_XY, null, null);
	}


	//=========================================================================================================================
	public boolean area(Area a,String label)
	{//=========================================================================================================================

		return checkAll(0,0,0,0,label,ACTIONCAPTIONTYPE_AREA, null, a);
	}

	//=========================================================================================================================
	public boolean xyxy(int x,int y,int x2,int y2,String label)
	{//=========================================================================================================================

		return checkAll(x,y,x2,y2,label, ACTIONCAPTIONTYPE_XYXY, null, null);
	}


	//=========================================================================================================================
	public boolean entity(Entity e,String label)
	{//=========================================================================================================================

		return checkAll(0,0,0,0,label,ACTIONCAPTIONTYPE_NPC, e, null);
	}

	//=========================================================================================================================
	public boolean checkAll(int x,int y,int x2,int y2,String label, int type, Entity e, Area a)
	{//=========================================================================================================================


		if(Player()==null)return false;

		boolean inRange = false;


		if(type==ACTIONCAPTIONTYPE_AREA)
		{
			x=(int)a.left();
			y=(int)a.top();
			x2=(int)a.right();
			y2=(int)a.bottom();

			if(Player().isAreaBoundaryTouchingMyHitBox(a)==true
			&&TextManager().textEngineState==0
			&&Player().GLOBAL_main_sprite_actions_off==0)inRange=true;

		}
		else
		if(type==ACTIONCAPTIONTYPE_NPC)
		{
			x=(int)a.left();
			y=(int)a.top();
			x2=(int)a.right();
			y2=(int)a.bottom();

			if(Player().isEntityHitBoxTouchingMyHitBox(e)==true
			&&TextManager().textEngineState==0
			&&Player().GLOBAL_main_sprite_actions_off==0)inRange=true;

		}
		else
		{

			if(Player().isHitBoxTouchingXYXYInDirectionByAmount(x,y,x2,y2,Player().animationDirection,7)==true
			&&TextManager().textEngineState==0
			&&Player().GLOBAL_main_sprite_actions_off==0)inRange=true;
		}


		actionsThisFrame.add(new Coords(x+(x2-x), y+(y2-y)));



		if(inRange)
		{

			if(label!=null&&label.equals("")==false)
			{
				if(actionCaption!=null)
				{
					replaceCaptionText(label);

					actionCaption.actionCaptionType=type;
					actionCaption.actionRangeX=x;
					actionCaption.actionRangeY=y;
					actionCaption.entity=e;
					actionCaption.area=a;
				}
				else
				{//doesnt exist,make new one over sprites head
					makeCaption(label);

					actionCaption.actionCaptionType=type;
					actionCaption.actionRangeX=x;
					actionCaption.actionRangeY=y;
					actionCaption.entity=e;
					actionCaption.area=a;
				}


				if(
					actionCaption!=null
					&&ControlsManager().BUTTON_ACTION_PRESSED==true
					&&label.compareTo(actionCaption.text)==0
					&&
					(
						(actionCaption.actionCaptionType==ACTIONCAPTIONTYPE_XYXY&&actionCaption.actionRangeX==x&&actionCaption.actionRangeY==y)
						||
						(actionCaption.actionCaptionType==ACTIONCAPTIONTYPE_XY&&actionCaption.actionRangeX==x&&actionCaption.actionRangeY==y)
						||
						(actionCaption.actionCaptionType==ACTIONCAPTIONTYPE_NPC&&actionCaption.entity==e)
						||
						(actionCaption.actionCaptionType==ACTIONCAPTIONTYPE_AREA&&actionCaption.area==a)
					)


				)
				{
					deleteCaptionWithBlipSound();
					return true;
				}

			}
			else
			{
				if(ControlsManager().BUTTON_ACTION_PRESSED==true)return true;
			}


		}
		else //else delete action icon and caption
		{

			if(label!=null&&label.equals("")==false)
			{
				if(
					actionCaption!=null
					&&label.compareTo(actionCaption.text)==0
					&&
					(
							(actionCaption.actionCaptionType==ACTIONCAPTIONTYPE_XYXY&&actionCaption.actionRangeX==x&&actionCaption.actionRangeY==y)
							||
							(actionCaption.actionCaptionType==ACTIONCAPTIONTYPE_XY&&actionCaption.actionRangeX==x&&actionCaption.actionRangeY==y)
							||
							(actionCaption.actionCaptionType==ACTIONCAPTIONTYPE_NPC&&actionCaption.entity==e)
							||
							(actionCaption.actionCaptionType==ACTIONCAPTIONTYPE_AREA&&actionCaption.area==a)
					)
				)
				{
					deleteCaptionNoSound();
				}
			}
		}

		return false;
	}




	//=========================================================================================================================
	public void deleteCaptionNoSound()
	{//=========================================================================================================================

		if(actionCaption!=null)
		{
			actionCaption.deleteFadeOut();
			actionCaption = null;
			actionIconScreenSprite.draw=false;
		}
	}


	//=========================================================================================================================
	public void deleteCaptionWithBlipSound()
	{//=========================================================================================================================
		AudioManager().playSound("blip",0.25f,1.6f,1);

		deleteCaptionNoSound();
	}


	//=========================================================================================================================
	public void makeCaption(String label)
	{//=========================================================================================================================

		/*
		int px = (int)(ACTION_caption.caption_width*2*ACTION_caption.scale);
		int actionx=((player().screen_x+player().size_x/2)-((px+8)/2))+8;//centered over player sprite
		if(actionx+px>LWJGLUtils.SCREEN_SIZE_X)actionx=LWJGLUtils.SCREEN_SIZE_X-px;//dont go past right
		if(actionx-8<0)actionx=0+8;//dont go past left
		int actiony=player().screen_y-16;
		*/


		actionCaption = CaptionManager().newManagedCaption(Caption.CENTERED_OVER_ENTITY,0,-1,label,BobFont.font_small_16_outlined_smooth,BobColor.WHITE,BobColor.CLEAR,RenderOrder.ABOVE_TOP,1.0f,0);

		actionIconScreenSprite.screenXPixelsHQ=actionCaption.screenX-(actionIconScreenSprite.w()+4);//move action icon sprite
		actionIconScreenSprite.screenYPixelsHQ=actionCaption.screenY-8;

		actionIconScreenSprite.draw=true;

	}

	//=========================================================================================================================
	public void replaceCaptionText(String label)
	{//=========================================================================================================================

		if(label.compareTo(actionCaption.text)!=0)	//		if action icon exists,check new label against old label
		{
			actionCaption.replaceText(label);
			//move action icon sprite
		}
		else
		{
			actionIconScreenSprite.screenXPixelsHQ=actionCaption.screenX-(actionIconScreenSprite.w()+4);//move action icon sprite
			actionIconScreenSprite.screenYPixelsHQ=actionCaption.screenY-8;
		}

	}

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================
		actionsThisFrame.clear();
	}

}
