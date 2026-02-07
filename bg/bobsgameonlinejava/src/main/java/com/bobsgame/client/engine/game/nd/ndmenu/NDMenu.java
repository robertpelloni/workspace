package com.bobsgame.client.engine.game.nd.ndmenu;


import com.bobsgame.client.engine.game.nd.ND;
import com.bobsgame.client.engine.game.nd.NDGameEngine;
import com.bobsgame.shared.BobColor;

import static org.lwjgl.opengl.GL11.glVertexPointer;

import com.bobsgame.client.GLUtils;

//=========================================================================================================================
public class NDMenu extends NDGameEngine
{//=========================================================================================================================


	//=========================================================================================================================
	public NDMenu(ND nD)
	{//=========================================================================================================================
		super(nD);

	}



	boolean runSelectedGame=false;
	int quit=0;



	Wheel wheel = new Wheel(this);
	NDMenuBackground background = new NDMenuBackground(this);


	BobColor WHITE = new BobColor(255, 255, 255);
	BobColor BLACK = new BobColor(0, 0, 0);
	BobColor RED = new BobColor(255, 0, 0);
	BobColor GREEN = new BobColor(0, 255, 0);
	BobColor BLUE = new BobColor(0, 0, 255);
	BobColor MAGENTA = new BobColor(255, 0, 255);
	BobColor YELLOW = new BobColor(0, 127, 127);



	static boolean actionButtonPressed=false;
	long buttonHeldTicks=0;

	boolean downButtonPressed=false;
	boolean rightButtonPressed=false;
	boolean upButtonPressed=false;
	boolean leftButtonPressed=false;

	int ticksSinceDownPressed=0;
	int ticksSinceRightPressed=0;
	int ticksSinceUpPressed=0;
	int ticksSinceLeftPressed=0;

	long ticks_since_down_repeat=0;
	long ticks_since_right_repeat=0;
	long ticks_since_up_repeat=0;
	long ticks_since_left_repeat=0;

	long currentTicks=0;
	long lastTicks=0;




	static int actionFadeCountSwitch=0;





	int showMovie=0;
	int movieSelected=1;
	static boolean directionButtonPressed=false;
	boolean directionButtonUnpressed=false;


	static int actionFadeCounter=0;

	int fadeDirection=0;
	long fadeOutTicks=0;




	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================

		super.init();

		wheel.init();

		background.init();

		AudioManager().playMusic("nDMenuBackgroundMusic",1.0f,1.0f,true);

	}




	//=========================================================================================================================
	public void addGame(NDGameEngine game,String name,BobColor color)
	{//=========================================================================================================================

		wheel.addGame(game,name,color);

	}






	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

		super.update();

		currentTicks+=engineTicksPassed();

		handleInput();


		background.update();

		updateVideo();

		wheel.update();

	}

	//=========================================================================================================================
	public void cleanup()
	{//=========================================================================================================================

		background.cleanup();

	}

	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================

		background.render();

		renderVideo();


		wheel.render();

		drawScreenOverlayFade();
	}



	//=========================================================================================================================
	void handleInput()
	{//=========================================================================================================================

		//------------------------------------------
		//handle key input
		//------------------------------------------

		if(ControlsManager().BUTTON_DOWN_PRESSED==true)
		{
			downButtonPressed=true;
			ticksSinceDownPressed=0;
			wheel.spinWheel(Wheel.CLOCKWISE);
		}
		if(ControlsManager().BUTTON_RIGHT_PRESSED==true)
		{
			rightButtonPressed=true;
			ticksSinceRightPressed=0;
			wheel.spinWheel(Wheel.CLOCKWISE);
		}

		if(ControlsManager().BUTTON_UP_PRESSED==true)
		{
			upButtonPressed=true;
			ticksSinceUpPressed=0;
			wheel.spinWheel(Wheel.COUNTERCLOCKWISE);
		}
		if(ControlsManager().BUTTON_LEFT_PRESSED==true)
		{
			leftButtonPressed=true;
			ticksSinceLeftPressed=0;
			wheel.spinWheel(Wheel.COUNTERCLOCKWISE);
		}


		if(ControlsManager().BUTTON_ACTION_PRESSED==true)actionButtonPressed=true;


		if(ControlsManager().BUTTON_DOWN_HELD==false){downButtonPressed=false;}
		if(ControlsManager().BUTTON_RIGHT_HELD==false){rightButtonPressed=false;}
		if(ControlsManager().BUTTON_UP_HELD==false){upButtonPressed=false;}
		if(ControlsManager().BUTTON_LEFT_HELD==false){leftButtonPressed=false;}

		//------------------------------------------
		//handle key repeat
		//------------------------------------------

		if(currentTicks>buttonHeldTicks)
		{
			if(downButtonPressed)
			{
				ticksSinceDownPressed+=currentTicks-buttonHeldTicks;
				if(ticksSinceDownPressed>300)
				{
					if(currentTicks>ticks_since_down_repeat+50)
					{
						ticks_since_down_repeat=currentTicks;
						wheel.spinWheel(Wheel.CLOCKWISE);
					}
				}
			}

			if(rightButtonPressed)
			{
				ticksSinceRightPressed+=currentTicks-buttonHeldTicks;
				if(ticksSinceRightPressed>300)
				{
					if(currentTicks>ticks_since_right_repeat+50)
					{
						ticks_since_right_repeat=currentTicks;
						wheel.spinWheel(Wheel.CLOCKWISE);
					}
				}
			}

			if(upButtonPressed)
			{
				ticksSinceUpPressed+=currentTicks-buttonHeldTicks;
				if(ticksSinceUpPressed>300)
				{
					if(currentTicks>ticks_since_up_repeat+50)
					{
						ticks_since_up_repeat=currentTicks;
						wheel.spinWheel(Wheel.COUNTERCLOCKWISE);
					}
				}
			}

			if(leftButtonPressed)
			{
				ticksSinceLeftPressed+=currentTicks-buttonHeldTicks;
				if(ticksSinceLeftPressed>300)
				{
					if(currentTicks>ticks_since_left_repeat+50)
					{
						ticks_since_left_repeat=currentTicks;
						wheel.spinWheel(Wheel.COUNTERCLOCKWISE);
					}
				}
			}
			buttonHeldTicks=currentTicks;
		}

		//------------------------------------------


		//------------------------------------------
		//check for direction buttons being pressed
		//------------------------------------------
		if(downButtonPressed==true||leftButtonPressed==true||upButtonPressed==true||rightButtonPressed==true)
		{
			directionButtonPressed=true;

		}
		else
		{
			if(directionButtonPressed==true)
			{
				directionButtonUnpressed=true;
			}
			directionButtonPressed=false;
		}

	}










	//=========================================================================================================================
	void updateVideo()
	{//=========================================================================================================================

		/*
		//------------------------------------------
		//do movie scrolling
		//------------------------------------------
		current_ticks = SDL_GetTicks();
		if(current_ticks>movie_scroll_ticks)
		{
			movie_scroll_ticks=current_ticks;

			if(direction_button_pressed==0)
			{
				//slide up from bottom left
				//if(movie_x<0)movie_x+=16;
				//if(movie_y>240-movie_YUV_SURFACE[movie_selected]->h)movie_y-=16;
				//if(movie_x>0)movie_x=0;
				//if(movie_y<240-movie_YUV_SURFACE[movie_selected]->h)movie_y=240-movie_YUV_SURFACE[movie_selected]->h;

				//slide up from top left
				if(movie_x<0)movie_x+=16;
				if(movie_y<0)movie_y+=16;
				if(movie_x>0)movie_x=0;
				if(movie_y>0)movie_y=0;
			}

		}
		*/

	}








	//=========================================================================================================================
	void renderVideo()
	{//=========================================================================================================================



		/*

		//------------------------------------------
		//play movie
		//------------------------------------------
		current_ticks = SDL_GetTicks();
		if(current_ticks>movie_play_ticks)
		{
			movie_play_ticks=current_ticks;
			//SDL_LockMutex(movie_MUTEX);



			//step 1: render a frame from mpeg stream to YUV surface
			if(movie_render_step==0&&movie_x==0&&movie_y==0)//240-movie_YUV_SURFACE[movie_selected]->h)
			{
				SMPEG_renderFrame(movie[movie_selected],movie_frame_num);
				movie_frame_num++;

				movie_render_step++;
				if(movie_render_step>=3)movie_render_step=0;
			}
			else
			//step 2: convert YUV surface to RGBA surface
			if(movie_render_step==1)
			{

				if(movie_RGBA_SURFACE==null)
				{
					movie_RGBA_SURFACE = SDL_CreateRGBSurface(SDL_SWSURFACE, power_of_two(movie_YUV_SURFACE[movie_selected]->w), power_of_two(movie_YUV_SURFACE[movie_selected]->h), 32, rmask, gmask, bmask, amask);
				}

				int[] area = {0,0,0,0};
				area.w = movie_YUV_SURFACE[movie_selected]->w;
				area.h = movie_YUV_SURFACE[movie_selected]->h;
				SDL_SetAlpha(movie_YUV_SURFACE[movie_selected], 0, 0);
				SDL_BlitSurface(movie_YUV_SURFACE[movie_selected], &area, movie_RGBA_SURFACE, null);

				movie_render_step++;
				if(movie_render_step>=3)movie_render_step=0;
			}
			else
			//step 3: convert RGBA surface to texture
			if(movie_render_step==2)
			{

				if(movieswapframe==0){movieswapframe=1;movieswapframe_opposite=0;}
				else {movieswapframe=0;movieswapframe_opposite=1;}

				movie_TEXTURE[movieswapframe] = load_texture_directly_from_square_surface(movie_RGBA_SURFACE);
				if(movie_TEXTURE[movieswapframe_opposite]!=null)delete_texture(movie_TEXTURE[movieswapframe_opposite]);

				movie_render_step++;
				if(movie_render_step>=3)movie_render_step=0;
			}
			//SDL_UnlockMutex(movie_MUTEX);
		}

		static int movie_border_frame=0;
		static int movie_border_ticks=0;

		//draw texture onto screen if it exists
		if(movie_TEXTURE[movieswapframe]!=null)
		if(glIsTexture(movie_TEXTURE[movieswapframe]->texture_id))
		{
			draw_texture(movie_TEXTURE[movieswapframe],movie_x+4,movie_y+4);
			draw_texture(movie_border_TEXTURE[movie_border_frame],movie_x,movie_y);
		}


		current_ticks = SDL_GetTicks();
		if(current_ticks>=movie_border_ticks+100)
		{
			movie_border_ticks=current_ticks;
			movie_border_frame++;
			if(movie_border_frame>12)movie_border_frame=0;
		}

		//if the wheel item changes, set the movie offscreen so it can slide back in
		if(direction_button_pressed==1 || show_movie==0)
		{

			infopanel_x=0-infopanel_TEXTURE->image_w;
			infopanel_y=(240-infopanel_TEXTURE->image_h)+infopanel_TEXTURE->image_w;

			movie_x=0-(movie_YUV_SURFACE[movie_selected]->w+8);
			movie_y=0-(movie_YUV_SURFACE[movie_selected]->w+8);//(240-movie_YUV_SURFACE[movie_selected]->h)+movie_YUV_SURFACE[movie_selected]->w;
			movie_render_step=0;
		}

		//if the direction button is let up, set the frame to 1 and render a new frame of the selected item movie
		//set step to 1 so it makes the rgba surface next loop
		if(direction_button_unpressed==1)
		{

			if(selected_wheel_item==1)show_movie=1;else show_movie=0;

			direction_button_unpressed=0;
			//movie_selected=selected_wheel_item%4;
			movie_frame_num=1;
			SMPEG_renderFrame(movie[movie_selected],movie_frame_num);
			if(movie_RGBA_SURFACE!=null){SDL_FreeSurface(movie_RGBA_SURFACE);movie_RGBA_SURFACE=null;}
			movie_render_step=1;
		}
*/



	}




	//=========================================================================================================================
	public void fillScreenBlack(float a)
	{//=========================================================================================================================
		GLUtils.drawFilledRectXYWH(0,0,ND.SCREEN_SIZE_X,ND.SCREEN_SIZE_Y,0.0f,0.0f,0.0f,a);
	}
	//=========================================================================================================================
	public void fillScreenWhite(float a)
	{//=========================================================================================================================
		GLUtils.drawFilledRectXYWH(0,0,ND.SCREEN_SIZE_X,ND.SCREEN_SIZE_Y,1.0f,1.0f,1.0f,a);
	}


	//=========================================================================================================================
	void drawScreenOverlayFade()
	{//=========================================================================================================================

		//------------------------------------------
		//do fade out if selected item
		//------------------------------------------

			if(actionFadeCountSwitch==1)
			{
				actionFadeCounter=255;
				actionFadeCountSwitch=2;
			}

			if(actionFadeCountSwitch==2)//flash white, fade to transparent
			{

				//fill white transparent
				fillScreenWhite(actionFadeCounter/255.0f);

				actionFadeCounter-=engineTicksPassed();
				if(actionFadeCounter<0)
				{
					actionFadeCounter=0;

					/*
					Mix_PlayChannel(-1, welcome_WAV, 0);
					*/

					actionFadeCountSwitch=3;
				}
			}

			if(actionFadeCountSwitch==3)//fade to white
			{

				//fill white transparent
				fillScreenWhite(actionFadeCounter/255.0f);

				actionFadeCounter+=0.8f*engineTicksPassed();
				if(actionFadeCounter>255)
				{
					actionFadeCounter=0;
					actionFadeCountSwitch=4;
				}
			}

			if(actionFadeCountSwitch==4)//fade from white to black, fade out music
			{

				//fill white opaque
				fillScreenWhite(1.0f);

				//fill black transparent
				fillScreenBlack(actionFadeCounter/255.0f);

				actionFadeCounter+=0.8f*engineTicksPassed();
				if(actionFadeCounter>255)
				{
					actionFadeCounter=0;

					/*
					if(Mix_PlayingMusic())
					{
						Mix_FadeOutMusic(1000);
					}
					*/

					actionFadeCountSwitch=5;
				}
			}

			if(actionFadeCountSwitch==5) //draw game title on black screen and wait
			{
				//fill black opaque
				fillScreenBlack(1.0f);

				wheel.renderGameTitleCentered();

				wheel.renderGameTitleCenteredGlow();

				//set glow alpha

				if(fadeDirection==0)
				{
					actionFadeCounter+=0.4f*engineTicksPassed();
					if(actionFadeCounter>255){actionFadeCounter=255;fadeDirection=1;}
				}

				if(fadeDirection==1)
				{
					actionFadeCounter-=0.4f*engineTicksPassed();
					if(actionFadeCounter<0){actionFadeCounter=0;fadeDirection=0;}
				}



				fadeOutTicks+=engineTicksPassed();

				if(fadeOutTicks>500&&actionFadeCounter==0)
				{
					actionFadeCounter=0;
					actionFadeCountSwitch=6;
				}
			}

			if(actionFadeCountSwitch==6) //fade out game title to black
			{

				//fill black opaque
				fillScreenBlack(1.0f);

				wheel.renderGameTitleCentered();

				//fill black transparent
				fillScreenBlack(actionFadeCounter/255.0f);

				actionFadeCounter+=0.4f*engineTicksPassed();

				if(actionFadeCounter>255)
				{
					actionFadeCounter=0;
					actionFadeCountSwitch=7;
				}
			}

			if(actionFadeCountSwitch==7) //draw black, quit
			{

				//fill black opaque
				fillScreenBlack(1.0f);
				nD.setGame(Wheel.wheelItems.get(wheel.selectedWheelItem).game);

			}


	}
}














