package com.bobsgame.client.engine.game.nd.ping;


import com.bobsgame.client.Texture;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.game.nd.ND;

//=========================================================================================================================
public class Background extends EnginePart
{//=========================================================================================================================

	//=========================================================================================================================
	public Background(Engine g)
	{//=========================================================================================================================
		super(g);

	}




	boolean tvRolling=false;
	int scrollingBackgroundX=0;
	boolean backgroundShakeDirectionToggle=false;
	boolean tvScanlinesColorPulseToggle=false;

	boolean backgroundInit=false;
	Texture backgroundTexture=null;
	int screenX=0;
	int screenY=0;



	long pulseTicks=0;
	long rollTicks=0;







	//=========================================================================================================================
	void init()
	{//=========================================================================================================================

		//backgroundTexture = GLUtils.loadTexture(s)




		//CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Wow. This is horrible.",FONT_NORMAL_ID,WHITE,BLACK,1,1);

	}


	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		long ticks = Engine().engineTicksPassed();


		if(tvRolling)
		{

			rollTicks+=ticks;
			if(rollTicks>200)
			{
				rollTicks=0;

				if(backgroundShakeDirectionToggle==false)
				{
					scrollingBackgroundX++;
					if(scrollingBackgroundX>3)
					{
						backgroundShakeDirectionToggle=true;
						scrollingBackgroundX--;
					}
				}
				else
				{
					scrollingBackgroundX--;
					if(scrollingBackgroundX<-3)
					{
						backgroundShakeDirectionToggle=false;
						scrollingBackgroundX++;
					}
				}
			}

		}



		pulseTicks+=ticks;
		if(pulseTicks>20)
		{
			pulseTicks=0;

			// make the tv scanlines pulse


			int spritecolor=3;
			int bgcolor=28;

			if(tvScanlinesColorPulseToggle==false)
			{
				// set white to gray
				spritecolor=3;
				bgcolor=28;
				tvScanlinesColorPulseToggle=true;
			}
			else
			{
				// set gray to white
				spritecolor=2;
				bgcolor=31;
				tvScanlinesColorPulseToggle=false;
			}

			// int f=0;
			// for(f=0;f<PING_PADDLE_SIZE_X*PING_PADDLE_SIZE_Y;f++)PING_paddle_gfx[f]=spritecolor;
			// for(f=0;f<PING_BALL_SIZE*PING_BALL_SIZE;f++)PING_ball_gfx[f]=spritecolor;
			// //redraw sprites
			// HARDWARE_update_sprite_texture(PING_lpaddle_sprite,0);
			// HARDWARE_update_sprite_texture(PING_rpaddle_sprite,0);
			// HARDWARE_update_sprite_texture(PING_ball_sprite,0);
			// //set tilemap palette
			// PING_palette[PING_tileset[8*8*PING_map[(29*32)+1]]] = HARDWARE_RGB(bgcolor,bgcolor,bgcolor);
		}
	}


	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================

		GLUtils.drawFilledRectXYWH(0,8,ND.SCREEN_SIZE_X,ND.SCREEN_SIZE_Y-8,0.0f,0.0f,0.0f,1.0f);

	}





}
