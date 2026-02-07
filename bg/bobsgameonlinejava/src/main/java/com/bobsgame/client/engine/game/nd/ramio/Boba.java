package com.bobsgame.client.engine.game.nd.ramio;

import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.entity.Entity;
//=========================================================================================================================
public class Boba extends Entity
{//=========================================================================================================================
	//=========================================================================================================================
	public Boba(Engine g)
	{//=========================================================================================================================
		super(g);
		
	}
	
	


	public boolean dead=false;


	
	public boolean checkHitLayerBlocksAndOtherBobas(int dir)
	{
		return false;
		
	}
	
	
	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


			if(dead==false)
			{


				//check down
				if(
						checkHitLayerBlocksAndOtherBobas(DOWN)==false
				)
				incY();
				

				if(movementDirection==LEFT)
				{
					//check hit
					if(
							checkHitLayerBlocksAndOtherBobas(LEFT)==false
					)
					{
						//move left
						decX();
					}
					else
					movementDirection=RIGHT;
				}

				if(movementDirection==RIGHT)
				{
					//heck hit
					if(
							checkHitLayerBlocksAndOtherBobas(RIGHT)==false
					)
					{
						//move right
						incX();

					}
					else
					movementDirection=LEFT;
				}
			}


			if(dead==true)
			{

				//set animation to "dead"
				if(getCurrentAnimationName().equals("dead")==false)
				{
					
					setCurrentAnimationByName("dead");
					setAnimateOnceThroughCurrentAnimation();
				
					
					//TODO: make setCurrentAnimation
				}

			}



		
	}


	public boolean checkStomp(Guy guy)
	{


		// int r=rand()%5;
		// if(r==0)CAPTION_make_caption(&yuu_ramio_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Squish!",FONT_NORMAL_ID,WHITE,BLACK,1,1);
		// if(r==1)CAPTION_make_caption(&yuu_ramio_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Take that!",FONT_NORMAL_ID,WHITE,BLACK,1,1);
		// if(r==2)CAPTION_make_caption(&yuu_ramio_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Poor guy.",FONT_NORMAL_ID,WHITE,BLACK,1,1);
		
		dead=true;
		// play sound
		AudioManager().playSound("ramiosplat",64,44100,0);
		// bounce
		Guy.jumping=true;
		
	

		return false;
	}


	public boolean checkRunningInto(Guy guy)
	{
		// TODO
		return false;
	}

}
