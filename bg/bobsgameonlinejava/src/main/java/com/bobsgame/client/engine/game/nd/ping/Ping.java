package com.bobsgame.client.engine.game.nd.ping;




import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.game.nd.ND;
import com.bobsgame.client.engine.game.nd.NDGameEngine;
import com.bobsgame.shared.Utils;



//=========================================================================================================================
public class Ping extends NDGameEngine
{// =========================================================================================================================


	// =========================================================================================================================
	public Ping(ND nD)
	{// =========================================================================================================================

		super(nD);


	}


	Paddle lp=new Paddle(this);
	Paddle rp=new Paddle(this);

	Ball ball=new Ball(this);

	int LEFT=0;
	int RIGHT=1;



	boolean easyMode=true;
	boolean playingPING=false;
	boolean alreadyUpdating=false;



	boolean quit=false;

	boolean initGame=false;


	boolean gotHighScore=false;
	int highScore=0;
	int score=0;



	boolean credits=false;
	boolean creditScreenInit=false;

	int deadX=0;
	int deadY=0;
	boolean dying=false;
	boolean firstDeath=false;



	int whichPaddle=LEFT;
	int paddleSpeed=2;



	int ballDirX=LEFT;
	int ballSpeed=1;
	int ballDirY=0;

	int DOWN=1;
	int STRAIGHT=0;
	int UP=-1;


	float angle=0;

	int maxBallSpeed=0;



	int framesSincePressedA=0;
	int framesSincePressedB=0;
	int framesSincePressedRight=0;
	int framesSincePressedLeft=0;
	int framesSincePressedDown=0;
	int framesSincePressedUp=0;
	int framesSincePressedR=0;

	boolean canPressA=false;
	boolean canPressB=false;
	boolean canPressRight=false;
	boolean canPressLeft=false;
	boolean canPressDown=false;
	boolean canPressUp=false;
	boolean canPressR=false;


	Background background=new Background(this);



	// =========================================================================================================================
	public void reset()
	{// =========================================================================================================================


		lp.x=10-(Paddle.w/2);
		lp.y=(ND.SCREEN_SIZE_Y/2)-(Paddle.h/2);


		rp.x=ND.SCREEN_SIZE_X-10-(Paddle.w/2);
		rp.y=(ND.SCREEN_SIZE_Y/2)-(Paddle.h/2);


		ball.x=(ND.SCREEN_SIZE_X/2)-(Ball.w/2);
		ball.y=(ND.SCREEN_SIZE_Y/2)-(Ball.h/2);




		framesSincePressedA=0;
		framesSincePressedB=0;
		framesSincePressedRight=0;
		framesSincePressedLeft=0;
		framesSincePressedDown=0;
		framesSincePressedR=0;
		canPressA=true;
		canPressB=true;
		canPressRight=true;
		canPressLeft=true;
		canPressDown=true;
		canPressR=true;

	}



	// =========================================================================================================================
	public void initGame()
	{// =========================================================================================================================

		if(easyMode==true)
		{
			highScore=66;
			maxBallSpeed=9;

		}
		else
		{
			highScore=333;// 142
			maxBallSpeed=9;
		}



		background.init();

		reset();




		initGame=true;

	}



	// =========================================================================================================================
	public void update()
	{// =========================================================================================================================


		if(quit==false)
		{

			if(initGame==false)initGame();




				background.update();


				if(dying)
				{
					AudioManager().stopAllMusic();
					AudioManager().playMusic("tetrid_death",0.25f,1.0f,true);

					if(firstDeath==false)
					{
						firstDeath=true;

						// CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Aww.. Yuu sucks. Come on, let's see this.",FONT_NORMAL_ID,WHITE,BLACK,1,1);
					}
					else if(firstDeath==true)
					{
						firstDeath=false;
						// CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Yuu thinks there's some kind of trick?",FONT_NORMAL_ID,WHITE,BLACK,1,1);
					}
				}
				else
				{
					background.update();

					game();
				}




		}
		else
		{

			initGame=false;

			playingPING=false;

		}

	}

	// =========================================================================================================================
	public void render()
	{// =========================================================================================================================
		background.render();

		lp.render();
		rp.render();
		ball.render();

	}



	// =========================================================================================================================
	public void game()
	{// =========================================================================================================================






		if((!ControlsManager().BUTTON_UP_HELD)||(framesSincePressedUp>=0))
		{
			canPressUp=true;
		}
		else framesSincePressedUp++;


		if((!ControlsManager().BUTTON_DOWN_HELD)||(framesSincePressedDown>=0))
		{
			canPressDown=true;
		}
		else framesSincePressedDown++;



		if((ControlsManager().BUTTON_UP_HELD)&&(canPressUp))
		{
			AudioManager().playSound("tick",0.5f,1.0f+Utils.randLessThanFloat(0.5f),1);

			if(whichPaddle==LEFT)
			{
				lp.y-=paddleSpeed*(engineTicksPassed()/10.0f);
				if(lp.y<8) lp.y=8;
			}
			if(whichPaddle==RIGHT)
			{
				rp.y-=paddleSpeed*(engineTicksPassed()/10.0f);
				if(rp.top()<8) rp.y=8;
			}


			canPressUp=false;
			framesSincePressedUp=0;
		}


		if((ControlsManager().BUTTON_DOWN_HELD)&&(canPressDown))
		{
			AudioManager().playSound("tick",0.5f,1.0f+Utils.randLessThanFloat(0.5f),1);

			if(whichPaddle==LEFT)
			{
				lp.y+=paddleSpeed*(engineTicksPassed()/10.0f);
				if(lp.bottom()>=ND.SCREEN_SIZE_Y) lp.y=ND.SCREEN_SIZE_Y-(Paddle.h+1);
			}
			if(whichPaddle==RIGHT)
			{
				rp.y+=paddleSpeed*(engineTicksPassed()/10.0f);
				if(rp.bottom()>=ND.SCREEN_SIZE_Y) rp.y=ND.SCREEN_SIZE_Y-(Paddle.h+1);
			}



			canPressDown=false;
			framesSincePressedDown=0;
		}



		// move ball==============================================================================


		// move up or down based on angle
		ball.y+=ballDirY*(angle*(engineTicksPassed()/120.0f));

		// if hit ceiling, bounce
		if(ball.top()<=8) ballDirY=DOWN;
		if(ball.bottom()>ND.SCREEN_SIZE_Y) ballDirY=UP;

		boolean hitleft=false;
		boolean hitright=false;
		boolean hitwall=false;

		if(ballDirX==LEFT)
		{
			whichPaddle=LEFT;
			lp.selected=true;
			rp.selected=false;

			ball.x-=ballSpeed*(engineTicksPassed()/10.0f);

			if(ball.left()<=lp.right())
			{
				// if it's touching the paddle
				if
				(
					(ball.top()>=lp.top()&&ball.top()<=lp.bottom())
					||
					(ball.bottom()>=lp.top()&&ball.bottom()<=lp.bottom())
				)
				{
					hitleft=true;

				}
				else hitwall=true;
			}
		}
		else if(ballDirX==RIGHT)
		{
			whichPaddle=RIGHT;
			rp.selected=true;
			lp.selected=false;

			ball.x+=ballSpeed*(engineTicksPassed()/10.0f);

			if(ball.right()>=rp.left())
			{
				// if it's touching the paddle
				if
				(
					(ball.top()>=rp.top()&&ball.top()<=rp.bottom())
					||
					(ball.bottom()>=rp.top()&&ball.bottom()<=rp.bottom())
				)
				{
					hitright=true;

				}
				else hitwall=true;
			}
		}

		// handle hits======================================================
		if(hitleft||hitright)
		{
			// play sound

			AudioManager().playSound("pingbeep",0.25f,1.0f,1);

			// score
			score++;

			// if(PING_score==3)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"This is so easy.",FONT_NORMAL_ID,WHITE,BLACK,1,1);
			// if(PING_score==15)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Ok, maybe not.",FONT_NORMAL_ID,WHITE,BLACK,1,1);
			// if(PING_score==30)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"There's a rhythm to it.",FONT_NORMAL_ID,WHITE,BLACK,1,1);
			// if(PING_score==40)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"I'm starting to get it.",FONT_NORMAL_ID,WHITE,BLACK,1,1);
			// if(PING_score==50)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Yeah, I can do this.",FONT_NORMAL_ID,WHITE,BLACK,1,1);

			// increase speed
			ballSpeed++;
			if(ballSpeed>maxBallSpeed) ballSpeed=maxBallSpeed;

			float pxFromMiddleY=0;

			if(hitleft)
			{
				// change direction
				ballDirX=RIGHT;
				// if ball touching paddle, bounce depending on angle
				// set angle depending on where touched the paddle.
				// so we should calc based on the middle of the ball vs the middle of the paddle divided into chunks.
				if(ball.middleY()>lp.middleY())
				{
					if(ballDirY==STRAIGHT) ballDirY=DOWN;// down
					pxFromMiddleY=ball.middleY()-lp.middleY();
				}

				if(ball.middleY()<=lp.middleY())
				{
					if(ballDirY==STRAIGHT) ballDirY=UP;// up
					pxFromMiddleY=lp.middleY()-ball.middleY();
				}
			}

			if(hitright)
			{
				// change direction
				ballDirX=LEFT;

				// if ball touching paddle, bounce depending on angle
				if(ball.middleY()>rp.middleY())
				{
					if(ballDirY==STRAIGHT) ballDirY=DOWN;// down
					pxFromMiddleY=ball.middleY()-rp.middleY();
				}

				if(ball.middleY()<=rp.middleY())
				{
					if(ballDirY==STRAIGHT) ballDirY=UP;// up
					pxFromMiddleY=rp.middleY()-ball.middleY();
				}
			}


			angle = (pxFromMiddleY/(Paddle.h/2.0f));


		}

		if(hitwall) // reset
		{

			AudioManager().playSound("pingbad",0.25f,1.0f,1);

			// reset ball speed, direction, x, y
			ballDirX=LEFT;
			ballDirY=0;
			angle=5;
			ballSpeed=1;

			if(score>highScore)
			{
				highScore=score;
				gotHighScore=true;

				AudioManager().playSound("pinghighscore",0.25f,1.0f,1);
			}
			score=0;

			if(gotHighScore==false)
			{

				// int r=0;
				// r=rand()%5;
				// if(r==0)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Is this even possible?",FONT_NORMAL_ID,WHITE,BLACK,1,1);
				// if(r==1)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"I hate this game.",FONT_NORMAL_ID,WHITE,BLACK,1,1);
				// if(r==2)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"What a dumb game.",FONT_NORMAL_ID,WHITE,BLACK,1,1);
				// if(r==3)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"People liked this?",FONT_NORMAL_ID,WHITE,BLACK,1,1);
				// if(r==4)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"What's the point of this?",FONT_NORMAL_ID,WHITE,BLACK,1,1);

				reset();
			}
			else
			{
				reset();
				//quit=true;
			}
		}


		updateScore();


	}



	// =========================================================================================================================
	public void updateScore()
	{// =========================================================================================================================



		// char char_score[15];
		// sprintf(char_score,"%d",PING_score);
		// int score_length=strlen(char_score);
		//
		//
		// int x=0;
		//
		//
		// for(x=0;x<3;x++)
		// {
		// PING_set_tile(1,2,8+x-3,2,29*32);
		// PING_set_tile(1,2,8+x-3,3,29*32);
		// }
		//
		// for(x=0;x<score_length;x++)
		// {
		// PING_set_tile(1,2,8+x-score_length,2,(char_score[x]-48)+(30*32));
		// PING_set_tile(1,2,8+x-score_length,3,(char_score[x]-48)+(31*32));
		// }
		//
		// char char_hiscore[15];
		// sprintf(char_hiscore,"%d",PING_high_score);
		// int hiscore_length=strlen(char_hiscore);
		//
		// //if(PING_high_score==0)
		// for(x=0;x<3;x++)
		// {
		// PING_set_tile(1,2,29+x-3,2,29*32);
		// PING_set_tile(1,2,29+x-3,3,29*32);
		// }
		//
		// for(x=0;x<hiscore_length;x++)
		// {
		// PING_set_tile(1,2,29+x-hiscore_length,2,(char_hiscore[x]-48)+(30*32));
		// PING_set_tile(1,2,29+x-hiscore_length,3,(char_hiscore[x]-48)+(31*32));
		// }

	}


}
