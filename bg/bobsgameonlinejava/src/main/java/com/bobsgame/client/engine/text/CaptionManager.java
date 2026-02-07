package com.bobsgame.client.engine.text;

import java.util.ArrayList;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.entity.Entity;
import com.bobsgame.client.engine.map.Area;
import com.bobsgame.client.engine.text.BobFont.BitmapFont;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.MapData.RenderOrder;


//=========================================================================================================================
public class CaptionManager extends EnginePart
{//=========================================================================================================================



	public static Logger log = (Logger) LoggerFactory.getLogger(CaptionManager.class);


	Caption first_CAPTION=null;
	Caption pause_CAPTION=null;


	ArrayList<Caption> captionList = new ArrayList<Caption>();

	//=========================================================================================================================
	public CaptionManager(Engine g)
	{//=========================================================================================================================
		super(g);

	}

	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================


	}

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

		long captionTicks=Engine().engineTicksPassed();

		//-----------------------------
		//update time
		//-----------------------------
		for(int n=0;n<captionList.size();n++)
		{
			Caption c = captionList.get(n);
			if(c.ticksToRemain>0)
			{
				c.ticksToRemain-=captionTicks;
				if(c.ticksToRemain<0)c.ticksToRemain=0;
			}

		}



		for(int n=0;n<captionList.size();n++)
		{
			captionList.get(n).update();
		}

	}

	//=========================================================================================================================
	public void render(RenderOrder layer)
	{//=========================================================================================================================


		//go through linked list backwards, because new captions are appended on the end.
		//in the case of the clock, we want to draw the older time over the new time so it fades nicely

		for(int n=captionList.size()-1;n>=0;n--)
		{
			Caption c = captionList.get(n);
			if(c.layer==layer)c.render();
		}

	}




	//=========================================================================================================================
	public Caption newManagedCaption(int x,int y,int ticks,String text,BitmapFont font,BobColor textColor,BobColor textBGColor,float scale)
	{//=========================================================================================================================

		if(ticks>=0&&ticks<100)log.error("Caption was made with ticks: "+ticks+". Text: "+text);
		Caption c = new Caption(Engine(),x,y,ticks,text,font,textColor,null,textBGColor,RenderOrder.ABOVE_TOP,scale,0,null,null,false,false);

		captionList.add(c);
		return c;
	}

	//=========================================================================================================================
	public Caption newManagedCaption(int x,int y,int ticks,String text,BitmapFont font,BobColor textColor,BobColor textBGColor,RenderOrder layer, float scale, int width)
	{//=========================================================================================================================

		if(ticks>=0&&ticks<100)log.error("Caption was made with ticks: "+ticks+". Text: "+text);
		Caption c = new Caption(Engine(),x,y,ticks,text,font,textColor,null,textBGColor,layer,scale,width,null,null,true,false);
		captionList.add(c);
		return c;
	}

	//=========================================================================================================================
	public Caption newManagedCaption(int x,int y,int ticks,String text,BitmapFont font,BobColor textColor,BobColor textBGColor,RenderOrder layer, float scale, int width, boolean fadeLetterColorTowardsTop, boolean centerTextOnMultipleLines)
	{//=========================================================================================================================

		if(ticks>=0&&ticks<100)log.error("Caption was made with ticks: "+ticks+". Text: "+text);
		Caption c = new Caption(Engine(),x,y,ticks,text,font,textColor,null,textBGColor,layer,scale,width,null,null,fadeLetterColorTowardsTop,centerTextOnMultipleLines);
		captionList.add(c);
		return c;
	}

	//=========================================================================================================================
	public Caption newManagedCaption(int x,int y,int ticks,String text,BitmapFont font,BobColor textColor,BobColor textAAColor, BobColor textBGColor,RenderOrder layer, float scale, int width, Entity entity, Area area, boolean fadeLetterColorTowardsTop, boolean centerTextOnMultipleLines)
	{//=========================================================================================================================

		if(ticks>=0&&ticks<100)log.error("Caption was made with ticks: "+ticks+". Text: "+text);
		Caption c = new Caption(Engine(),x,y,ticks,text,font,textColor,textAAColor,textBGColor,layer,scale,width,entity,area,fadeLetterColorTowardsTop,centerTextOnMultipleLines);
		captionList.add(c);
		return c;
	}

//	//=========================================================================================================================
//	/**
//	 * MUST USE THE RETURN VALUE
//	 */
//	public Caption fadeOutDelete_MUST_USE_RETURN(Caption c)
//	{//=========================================================================================================================
//
//		//TODO: take an array in with the external caption so it can be set to null?
//
//
//		c.toAlpha=0.0f;
//
//		return null;
//
//
//	}
//
//	//=========================================================================================================================
//	/**
//	 * MUST USE THE RETURN VALUE
//	 */
//	public Caption delete_MUST_USE_RETURN(Caption c)
//	{//=========================================================================================================================
//
//		//TODO: take an array in with the external caption so it can be set to null?
//
//		c.delete=true;
//
//		return null;
//	}

//
//	//=========================================================================================================================
//	public void CAPTION_delete_all_captions()
//	{//=========================================================================================================================
//
//		/*
//		while(first_CAPTION!=null)
//		{
//			CAPTION* current_caption=first_CAPTION;
//			while(current_caption.next!=null)current_caption=(CAPTION*)current_caption.next;
//			CAPTION_delete_caption(current_caption);
//		}
//		*/
//
//	}
//	//=========================================================================================================================
//	public void CAPTION_pause()
//	{//=========================================================================================================================
//			//delete all sprites but keep captions
//			//set pause_CAPTION to first_CAPTION
//			//set first_CAPTION to null
//
//		/*
//		pause_CAPTION= first_CAPTION;
//		first_CAPTION=null;
//
//		if(pause_CAPTION!=null)
//		{
//			Caption current_caption = pause_CAPTION;
//			bool stop=0;
//			while(stop==0)
//			{
//				u8 c=0;
//			for(c=0;c<current_caption.chunks;c++)
//			{
//				if(current_caption.sprite[c]!=null)
//					{
//						HARDWARE_delete_sprite(current_caption.sprite[c]);
//						current_caption.sprite[c]=null;
//					}
//				}
//				if(current_caption.next!=null)current_caption=(CAPTION*)current_caption.next;else stop=1;
//			}
//		}
//		*/
//	}
//
//	//=========================================================================================================================
//	public void CAPTION_unpause()
//	{//=========================================================================================================================
//		//delete all captions from first_CAPTION on
//		//set first_CAPTION back to pause_CAPTION
//		//set pause_CAPTION to null
//		//redraw all caption sprites
//
//		//CAPTION_delete_all_captions();
//
//		first_CAPTION= pause_CAPTION;
//		pause_CAPTION=null;
//
//		//u8 caption_chunks_onscreen[2]={0,0};
//
//
//		/*
//		if(first_CAPTION!=null)
//		{
//			CAPTION* current_caption = first_CAPTION;
//			bool stop=0;
//			while(stop==0)
//			{
//				u8 c=0;
//			for(c=0;c<current_caption.chunks;c++)
//			{
//				if(current_caption.sprite[c]==null)
//					{
//						//current_caption.PLAYER_id[c]=FIRST_SPRITE_ID+caption_chunks_onscreen[current_caption.screen];
//
//						current_caption.sprite[c]=HARDWARE_create_sprite(current_caption.gfx[c],0,current_caption.layer,current_caption.scale,current_caption.screen_x+64*c,current_caption.screen_y,255);
//
//						//HARDWARE_create_sprite(current_caption.screen,current_caption.PLAYER_id[c],current_caption.gfx_slot[c],64,32,1,0,0,0,0,0,current_caption.prio,current_caption.scale,current_caption.screen_x+64*c,current_caption.screen_y);
//						//caption_chunks_onscreen[current_caption.screen]++;
//					}
//				}
//				if(current_caption.next!=null)current_caption=(CAPTION*)current_caption.next;else stop=1;
//			}
//		}*/
//
//	}
//
//



}
