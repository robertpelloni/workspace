package com.bobsgame.client.engine.game.nd.ramio;

import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.entity.Entity;
//=========================================================================================================================
public class MoneyBlock extends Block
{//=========================================================================================================================
	
	
	
	//=========================================================================================================================
	public MoneyBlock(Engine g)
	{//=========================================================================================================================
		super(g);
		
	}
	
	

	public boolean open=false;
	public boolean contains=false;

	
	//=========================================================================================================================
	public void hit()
	{//=========================================================================================================================
		
		
		if(hit==true)
		{

			if(hitOffsetY==0)
			{
				
				//play sound
				if(open==true)AudioManager().playSound("ramiobrickthud",64,44100,0);
				else AudioManager().playSound("ramiomoneybrick",64,44100,0);

				if(open==false)
				{
//					int r=rand()%5;
//					if(r==0)CAPTION_make_caption(&yuu_ramio_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Got more cash!",FONT_NORMAL_ID,WHITE,BLACK,1,1);
//					if(r==1)CAPTION_make_caption(&yuu_ramio_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Alright!",FONT_NORMAL_ID,WHITE,BLACK,1,1);
//					if(r==2)CAPTION_make_caption(&yuu_ramio_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Bling!",FONT_NORMAL_ID,WHITE,BLACK,1,1);

					Ramio.timer+=Ramio.ticksToAddForMoneyBlock;
				}


			}

			if(hitOffsetY<11)
			{
				hitOffsetY++;
			}
			else
			{
				hit=false;
				open=true;
			}

		}
	}
	
}
