package com.bobsgame.client.engine.game.nd.ramio;



import java.util.ArrayList;

import com.bobsgame.client.console.Console;
import com.bobsgame.client.console.ConsoleText;
import com.bobsgame.client.engine.game.nd.ND;
import com.bobsgame.client.engine.game.nd.NDGameEngine;
import com.bobsgame.client.engine.text.Caption;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.Utils;
import com.bobsgame.shared.MapData.RenderOrder;
import com.bobsgame.client.engine.text.BobFont;



//=========================================================================================================================
public class Ramio extends NDGameEngine
{// =========================================================================================================================




	// =========================================================================================================================
	public Ramio(ND nD)
	{// =========================================================================================================================

		super(nD);


	}



	boolean playing=true;
	boolean won=false;

	static int timer=0;
	static int initialTimer=0;
	static int ticksToAddForMoneyBlock=0;


	Caption RAMIO_timercaption = null;

	boolean easymode=true;


	int highScore=142;
	int score=0;
	boolean gotHighScore=false;




	int deadX=0;
	int deadY=0;
	boolean dead=false;



	boolean credits=false;
	boolean creditScreenInit=false;
	boolean init=false;


	long ticks=0;


	int winSequenceStep=0;
	int dieSequenceStep=0;







	ArrayList<Boba> bobas=new ArrayList<Boba>();
	ArrayList<BrickBlock> brickBlocks=new ArrayList<BrickBlock>();
	ArrayList<MoneyBlock> moneyBlocks=new ArrayList<MoneyBlock>();


	Guy guy;





	// =========================================================================================================================
	void updateScore()
	{// =========================================================================================================================

		//
		//
		// char char_score[15];
		// sprintf(char_score,"%d",RAMIO_score);
		// int score_length=strlen(char_score);
		//
		//
		// int x=0;
		//
		// //if(RAMIO_score==0)
		// for(x=0;x<3;x++)
		// {
		// //RAMIO_set_tile(1,2,8+x-3,2,29*32);
		// //RAMIO_set_tile(1,2,8+x-3,3,29*32);
		// }
		//
		// for(x=0;x<score_length;x++)
		// {
		// //RAMIO_set_tile(1,2,8+x-score_length,2,(char_score[x]-48)+(30*32));
		// //RAMIO_set_tile(1,2,8+x-score_length,3,(char_score[x]-48)+(31*32));
		// }
		//
		// char char_hiscore[15];
		// sprintf(char_hiscore,"%d",RAMIO_high_score);
		// int hiscore_length=strlen(char_hiscore);
		//
		// //if(RAMIO_high_score==0)
		// for(x=0;x<3;x++)
		// {
		// //RAMIO_set_tile(1,2,29+x-3,2,29*32);
		// //RAMIO_set_tile(1,2,29+x-3,3,29*32);
		// }
		//
		// for(x=0;x<hiscore_length;x++)
		// {
		// //RAMIO_set_tile(1,2,29+x-hiscore_length,2,(char_hiscore[x]-48)+(30*32));
		// //RAMIO_set_tile(1,2,29+x-hiscore_length,3,(char_hiscore[x]-48)+(31*32));
		// }

	}


	//=========================================================================================================================
	public boolean checkHit(int dir)
	{//=========================================================================================================================
		return false;
	}





	//=========================================================================================================================
	public void initGame()
	{//=========================================================================================================================



		if(easymode==true)
		{
			timer=0;
			initialTimer=1000;
			ticksToAddForMoneyBlock=200;
		}
		else
		{
			timer=0;
			initialTimer=800;
			ticksToAddForMoneyBlock=140;
		}



		CaptionManager().newManagedCaption(Caption.CENTERED_X,20,3000,"Alright! It works!",BobFont.font_normal_8,BobColor.WHITE,BobColor.CLEAR,RenderOrder.ABOVE_TOP,0.5f,-1);



		MapManager().changeMap("MINIGAMERAMIOramiolevel1",16,0);

		guy=new Guy(this, CurrentMap());
		CurrentMap().activeEntityList.add(guy);

		CurrentMap().defaultDisableFloorOffset = true;

		guy.init();

		guy.setX(5*8*2);
		guy.setY(14*8*2);


		Cameraman().setTarget(guy);
		Cameraman().setXYToTarget();
		Cameraman().ZOOMto = 0.5f;

		timer=initialTimer;

		init=true;

	}


	// =========================================================================================================================
	void doWinSequence()
	{// =========================================================================================================================

		if(winSequenceStep==0)
		{

			CaptionManager().newManagedCaption(Caption.CENTERED_X,20,3000,"Yeah! I did it!",BobFont.font_normal_8,BobColor.WHITE,BobColor.CLEAR,RenderOrder.ABOVE_TOP,0.5f,-1);


			AudioManager().stopAllMusic();
			AudioManager().playSound("ramiowon",0.25f,1.0f,1);
			winSequenceStep=1;
			ticks=0;
		}
		else if(winSequenceStep==1)
		{
			if(ticks>150)
			{
				winSequenceStep=2;
			}
		}

		else if(winSequenceStep==2)
		{
			winSequenceStep=3;

			// delete sprites

			// CAPTION_delete_caption(RAMIO_timercaption);

			// TODO:glitch, end game

			init=false;
			creditScreenInit=true;

			playing=false;

		}

	}



	//=========================================================================================================================
	void doDeathSequence()
	{//=========================================================================================================================



		if(dieSequenceStep==0)
		{
			int r=Utils.randLessThan(5);
			if(r==0)CaptionManager().newManagedCaption(Caption.CENTERED_X,20,3000,"Let's try this again.",BobFont.font_normal_8,BobColor.WHITE,BobColor.CLEAR,RenderOrder.ABOVE_TOP,0.5f,-1);
			if(r==1)CaptionManager().newManagedCaption(Caption.CENTERED_X,20,3000,"I was so close!",BobFont.font_normal_8,BobColor.WHITE,BobColor.CLEAR,RenderOrder.ABOVE_TOP,0.5f,-1);
			if(r==2)CaptionManager().newManagedCaption(Caption.CENTERED_X,20,3000,"Grrr. That was stupid.",BobFont.font_normal_8,BobColor.WHITE,BobColor.CLEAR,RenderOrder.ABOVE_TOP,0.5f,-1);
			if(r==3)CaptionManager().newManagedCaption(Caption.CENTERED_X,20,3000,"One more try.",BobFont.font_normal_8,BobColor.WHITE,BobColor.CLEAR,RenderOrder.ABOVE_TOP,0.5f,-1);
			if(r==4)CaptionManager().newManagedCaption(Caption.CENTERED_X,20,3000,"Nooooooooo!",BobFont.font_normal_8,BobColor.WHITE,BobColor.CLEAR,RenderOrder.ABOVE_TOP,0.5f,-1);

			AudioManager().stopAllMusic();
			AudioManager().playSound("ramiodeath",0.25f,1.0f,1);

			guy.setCurrentAnimationByName("death");
			guy.setAnimateOnceThroughCurrentAnimation();

			dieSequenceStep=1;
		}
		else if(dieSequenceStep==1)
		{

			if(ticks>30)
			{
				dieSequenceStep=2;
				ticks=0;
			}
		}
		else if(dieSequenceStep==2)
		{
			if(ticks>30)
			{
				dieSequenceStep=3;
				ticks=0;
			}
		}
		else if(dieSequenceStep==3)
		{
			if(ticks>60)
			{
				dieSequenceStep=4;
			}
		}
		else if(dieSequenceStep==4)
		{

			AudioManager().playMusic("ramio",0.5f,1.0f,true);
			dieSequenceStep=0;
			// do death animation
			// caption probably

			guy.setX(5*8*2);
			guy.setY(14*8*2);

			// start over
			dead=false;
			timer=initialTimer;
		}
	}


	ConsoleText ramioText = Console.add("ramioText",BobColor.GREEN);
	// =========================================================================================================================
	public void update()
	{// =========================================================================================================================

		//if(guy!=null)Cameraman().setX((float)Math.floor(guy.x()+guy.width()/2));
		//if(guy!=null)Cameraman().setX((float)guy.x()+guy.width()/2);
		super.update();

		if(guy!=null)
		{

			Cameraman().setX(guy.x());

			//Cameraman().setX((float)Math.floor(((int)(guy.x())/2))*2);//clamp to whole pixels

			//guy.setX((float)Math.floor(((int)(guy.x())/4))*4);
		}

		ticks+=engineTicksPassed();

		if(credits==false)
		{
			if(init==false)initGame();

			ramioText.text = "GuyX: "+guy.x()+" GuyY: "+guy.y()+" CamX: "+Cameraman().x()+" CamY: "+Cameraman().y();

			updateScore();


//			timer--;
//			if(timer<=0)
//			{
//				dead=true;
//			}


			// timer
			String timerString = "$";
			timerString+= ""+((timer/1000)%10);
			timerString+= ""+((timer/100)%10);
			timerString+= ""+((timer/10)%10);
			timerString+= ""+(timer%10);

			if(RAMIO_timercaption==null)RAMIO_timercaption = CaptionManager().newManagedCaption(Caption.CENTERED_X,2,-1,timerString,BobFont.font_normal_16_shadow1,BobColor.GREEN,BobColor.CLEAR,RenderOrder.ABOVE_TOP,0.5f,0);
			else RAMIO_timercaption.replaceText(timerString);

			if(won==true)
			{
				doWinSequence();
			}
			else if(dead==true)
			{
				doDeathSequence();
			}
			else
			{


				//guy.update();
				//Cameraman().update();

				for(int i=0;i<bobas.size();i++)bobas.get(i).update();
				for(int i=0;i<moneyBlocks.size();i++)moneyBlocks.get(i).update();
				for(int i=0;i<brickBlocks.size();i++)brickBlocks.get(i).update();


				// check fell in pit
//				if(guy.bottom()>=22*8) dead=true;



				// end of level
//				if((guy.x())/8>=468)
//				{
//					won=true;
//
//				}

			}

		}
		else
		{
			if(creditScreenInit==false)
			{

				init=false;
				creditScreenInit=true;

			}

			if(ControlsManager().BUTTON_TAB_PRESSED)
			{
				playing=false;
			}


		}

	}


	// =========================================================================================================================
	public void render()
	{// =========================================================================================================================
		super.render();

	}



}
