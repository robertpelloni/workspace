package com.bobsgame.client.engine.game.nd.ndmenu;

import java.util.ArrayList;

import com.bobsgame.client.Texture;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.game.nd.ND;
import com.bobsgame.client.engine.game.nd.NDGameEngine;
import com.bobsgame.client.engine.game.nd.ndmenu.wheelitem.WheelItem;
import com.bobsgame.shared.BobColor;
//=========================================================================================================================
public class Wheel extends EnginePart
{//=========================================================================================================================


	//=========================================================================================================================
	public Wheel(Engine g)
	{//=========================================================================================================================
		super(g);
	}



	public static ArrayList<WheelItem> wheelItems = new ArrayList<WheelItem>();





	int selectedWheelItem=0;
	int wheelSpinDirection=0;//2;

	int wheelSoundQueue=0;


	public static int CLOCKWISE=0;
	public static int COUNTERCLOCKWISE=1;


	Texture[] selectedItemColorSpinTexture = new Texture[15];


	float cartSlideX=0;

	int selectionBoxFrame=0;
	long selectionBoxTicks=0;



	long highlightTicks=0;
	public static float highlightColor=0;
	int highlightDir=0;




	boolean selectionColorSpinEnabled=true;


	boolean wheelSpinning=false;


	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================


		//------------------------------------------
		//initialize wheel item labels / highlight values
		//------------------------------------------


			selectedItemColorSpinTexture[0] = GLUtils.loadTexture("res/nD/menu/wheelItem/selectedItemColorSpin_00.png");
			selectedItemColorSpinTexture[1] = GLUtils.loadTexture("res/nD/menu/wheelItem/selectedItemColorSpin_01.png");
			selectedItemColorSpinTexture[2] = GLUtils.loadTexture("res/nD/menu/wheelItem/selectedItemColorSpin_02.png");
			selectedItemColorSpinTexture[3] = GLUtils.loadTexture("res/nD/menu/wheelItem/selectedItemColorSpin_03.png");
			selectedItemColorSpinTexture[4] = GLUtils.loadTexture("res/nD/menu/wheelItem/selectedItemColorSpin_04.png");
			selectedItemColorSpinTexture[5] = GLUtils.loadTexture("res/nD/menu/wheelItem/selectedItemColorSpin_05.png");
			selectedItemColorSpinTexture[6] = GLUtils.loadTexture("res/nD/menu/wheelItem/selectedItemColorSpin_06.png");
			selectedItemColorSpinTexture[7] = GLUtils.loadTexture("res/nD/menu/wheelItem/selectedItemColorSpin_07.png");
			selectedItemColorSpinTexture[8] = GLUtils.loadTexture("res/nD/menu/wheelItem/selectedItemColorSpin_08.png");
			selectedItemColorSpinTexture[9] = GLUtils.loadTexture("res/nD/menu/wheelItem/selectedItemColorSpin_09.png");
			selectedItemColorSpinTexture[10] = GLUtils.loadTexture("res/nD/menu/wheelItem/selectedItemColorSpin_10.png");
			selectedItemColorSpinTexture[11] = GLUtils.loadTexture("res/nD/menu/wheelItem/selectedItemColorSpin_11.png");
			selectedItemColorSpinTexture[12] = GLUtils.loadTexture("res/nD/menu/wheelItem/selectedItemColorSpin_12.png");
			selectedItemColorSpinTexture[13] = GLUtils.loadTexture("res/nD/menu/wheelItem/selectedItemColorSpin_13.png");
			selectedItemColorSpinTexture[14] = GLUtils.loadTexture("res/nD/menu/wheelItem/selectedItemColorSpin_14.png");




		//------------------------------------------
		//load wheel item textures
		//------------------------------------------

		WheelItem.wheelItemBackgroundTexture = GLUtils.loadTexture("res/nD/menu/wheelItem/itemBackground.png");
		WheelItem.wheelItemGlossyOverlayTexture = GLUtils.loadTexture("res/nD/menu/wheelItem/glossyOverlay.png");




		wheelItems.add(new WheelItem(Engine(),null,"GameStore",BobColor.magenta));
		wheelItems.add(new WheelItem(Engine(),null,"Settings",BobColor.green));



	}

	//=========================================================================================================================
	public void addGame(NDGameEngine game, String name,BobColor color)
	{//=========================================================================================================================

		wheelItems.add(new WheelItem(Engine(),game,name,color));


		//------------------------------------------
		//set up wheel items
		//------------------------------------------

//			wheelItems.get(0).labelTexture = GLUtils.loadTexture("res/nD/menu/items/gamestore/label_gamestore.png");
//			wheelItems.get(0).labelGlowTexture = GLUtils.loadTexture("res/nD/menu/items/gamestore/label_gamestore.png");
//
//			wheelItems.get(1).labelTexture = GLUtils.loadTexture("res/nD/menu/items/bobsgame/label_bobsgame.png");
//			wheelItems.get(1).labelGlowTexture = GLUtils.loadTexture("res/nD/menu/items/bobsgame/label_bobsgame_glow.png");
//
//			wheelItems.get(2).labelTexture = GLUtils.loadTexture("res/nD/menu/items/settings/label_settings.png");
//			wheelItems.get(2).labelGlowTexture = GLUtils.loadTexture("res/nD/menu/items/settings/label_settings.png");
//
//			wheelItems.get(0).name="Game Store";
//			wheelItems.get(1).name="\"bob's game\"";
//			wheelItems.get(2).name="Settings";
//
//			wheelItems.get(0).color = BobColor.red;
//			wheelItems.get(1).color = BobColor.green;
//			wheelItems.get(2).color = BobColor.yellow;
//



		//------------------------------------------
		//initialize wheel movement values
		//------------------------------------------

			//int max_wheel_items_onscreen = (SCREEN_SIZE_Y/cart_label_height)+2;

			//since the middle label will be centered on screen, the topmost label y position will be offset, not zero
			//int first_cart_y = (((SCREEN_SIZE_Y/2)-(cart_label_height/2))%cart_label_height);

			///populate the wheel starting from the middle, so the first item is always selected.


	}


	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================

		//------------------------------------------
		//draw each wheel item
		//------------------------------------------

			for(int c=0;c<wheelItems.size();c++)
			{

				wheelItems.get(c).render(c==selectedWheelItem);

			}



			WheelItem selected = wheelItems.get(selectedWheelItem);
			//------------------------------------------
			//draw selection box
			//------------------------------------------
			if(selectionColorSpinEnabled==true)
			{
				GLUtils.drawTexture(selectedItemColorSpinTexture[selectionBoxFrame],selected.x,selected.y,1.0f,GLUtils.FILTER_LINEAR);
			}



	}


	//=========================================================================================================================
	public void renderGameTitleCentered()
	{//=========================================================================================================================
		WheelItem selected = wheelItems.get(selectedWheelItem);
		//draw game title
		//NDGame.drawTexture(selected.labelTexture,ND.SCREEN_SIZE_X/2-selected.labelTexture.getImageWidth()/2,ND.SCREEN_SIZE_Y/2-selected.labelTexture.getImageHeight()/2);

	}
	//=========================================================================================================================
	public void renderGameTitleCenteredGlow()
	{//=========================================================================================================================
		WheelItem selected = wheelItems.get(selectedWheelItem);
		//draw game title glow
		//NDGame.drawTextureAlpha(selected.labelGlowTexture,ND.SCREEN_SIZE_X/2-selected.labelTexture.getImageWidth()/2,ND.SCREEN_SIZE_Y/2-selected.labelTexture.getImageHeight()/2,NDMenu.actionFadeCounter/255.0f);

	}


	//=========================================================================================================================
	void spinWheel(int dir)
	{//=========================================================================================================================

		if(dir==CLOCKWISE)
		{
			//wheelSpinDirection=wheelClockwise;
			selectedWheelItem++;

			if(selectedWheelItem>=wheelItems.size())selectedWheelItem=0;

			wheelSoundQueue++;
		}
		else
		if(dir==COUNTERCLOCKWISE)
		{
			//wheelSpinDirection=wheelCounterClockwise;
			selectedWheelItem--;

			if(selectedWheelItem<0)selectedWheelItem=wheelItems.size()-1;

			wheelSoundQueue++;
		}
	}





	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================
		//------------------------------------------
		//do wheel sound
		//------------------------------------------

		if(wheelSoundQueue>0)
		{
			AudioManager().playSound("nDMenuWheelSound",1.0f,1.0f,wheelSoundQueue-1);
			wheelSoundQueue=0;
		}
		if(NDMenu.actionButtonPressed==true)
		{
			NDMenu.actionButtonPressed=false;

			//if(selectedWheelItem==1)
			{
				AudioManager().playSound("nDMenuActionPressed",1.0f,1.0f,1);
				NDMenu.actionFadeCountSwitch=1;
			}
		}



		WheelItem selected = wheelItems.get(selectedWheelItem);


		float screenMiddleY = (ND.SCREEN_SIZE_Y/2);
		float wheelMiddleY = selected.middleY();

		//------------------------------------------
		//if the selected wheel item isnt centered on the wheel
		//------------------------------------------
		if(wheelMiddleY!=screenMiddleY)
		{
			wheelSpinning=true;

			float distance=0;

			if(wheelMiddleY<=screenMiddleY)distance = screenMiddleY-wheelMiddleY;
			else if(wheelMiddleY>screenMiddleY)distance = wheelMiddleY-screenMiddleY;


			float amt = (float) (Math.pow(Engine().engineTicksPassed(), distance/100.0f));//*(1.0f/10.0f)

			if(wheelMiddleY<screenMiddleY&&wheelMiddleY+amt>screenMiddleY)amt=screenMiddleY-wheelMiddleY;
			if(wheelMiddleY>screenMiddleY&&wheelMiddleY-amt<screenMiddleY)amt=wheelMiddleY-screenMiddleY;

			//------------------------------------------
			//move all the items up or down based on the direction the wheel is spinning
			//(this is so you can immediately change direction while the wheel is turning)
			//------------------------------------------

				if(wheelMiddleY>screenMiddleY)//wheelSpinDirection==wheelClockwise)
				{
					wheelSpinDirection = Wheel.CLOCKWISE;
					for(int c=0;c<wheelItems.size();c++)
					{
						wheelItems.get(c).y-=amt;
					}

					//SWI.y-=wheelTicksPassed*getDistanceToCenter()/300.0f;
					//if(SWI.middleY()<screenMiddleY)SWI.y=screenMiddleY-(wheelItemHeight/2.0f);
				}
				if(wheelMiddleY<screenMiddleY)//wheelSpinDirection==wheelCounterClockwise)
				{
					wheelSpinDirection = Wheel.COUNTERCLOCKWISE;
					for(int c=0;c<wheelItems.size();c++)
					{
						wheelItems.get(c).y+=amt;
					}
					//SWI.y+=wheelTicksPassed*getDistanceToCenter()/300.0f;
					//if(SWI.middleY()>screenMiddleY)SWI.y=screenMiddleY-(wheelItemHeight/2.0f);
				}
			//------------------------------------------






				//if the wheel is going clockwise
				//find the bottom-most wheel item
				//if it is less than SCREEN_SIZE_Y-cartsizey
				//take the top one, set to bottom most + cart size y
				//or for neat slide effect, move it up until it is above 0-cartsizey
				//then set it to SCREEN_SIZE_Y and catch up to the bottom-most

				//if the wheel is going counterclockwise
				//find the topmost wheel item
				//if it is more than 0+cartsizey
				//take the bottom one, move it down until it is below SCREEN_SIZE_Y
				//then set it to 0-cartsize and catch up to the topmost

				//------------------------------------------
				//find topmost and bottommost
				//------------------------------------------


					WheelItem bottomItem=wheelItems.get(0);
					WheelItem topItem=bottomItem;

					for(int c=0;c<wheelItems.size();c++)
					{
						//if(c==selectedWheelItem)continue;

						if(wheelItems.get(c).y>bottomItem.y){bottomItem=wheelItems.get(c);}
						if(wheelItems.get(c).y<topItem.y){topItem=wheelItems.get(c);}
					}
				//------------------------------------------

				//if an item wraps off the screen, wrap it on the other side
				if(wheelSpinDirection==Wheel.CLOCKWISE)
				{
					if(topItem.bottom()<0)
					{
						//if there are more items than the screen can fit, append to the bottommost item, else just append to the bottom of the screen
						//if(bottomItem.bottom()>=SCREEN_SIZE_Y)
						{
							topItem.y=bottomItem.bottom();
						}
						//else
						{
							//topItem.y=SCREEN_SIZE_Y-(1-topItem.bottom());
						}
					}
				}

				if(wheelSpinDirection==Wheel.COUNTERCLOCKWISE)
				{
					if(bottomItem.top()>=ND.SCREEN_SIZE_Y)
					{
						//if(topItem.top()<0)
						{
							bottomItem.y=topItem.top()-(WheelItem.wheelItemHeight);
						}
						//else
						{
							//bottomItem.y=(0-wheelItemHeight)+(bottomItem.top()-(SCREEN_SIZE_Y-1));
						}

					}
				}



		}
		else wheelSpinning=false;







		float overlayFadeSpeedTicksMultiplier = (2.0f/1000.0f);
		float cartSlideXSpeedTicksMultiplier = (2.0f/100.0f);


		//------------------------------------------
		//set the alpha value to fade the selected item in and out
		//------------------------------------------

		if(highlightDir==1)
		{
			highlightColor-=Engine().engineTicksPassed()*overlayFadeSpeedTicksMultiplier;
			if(highlightColor<=0){highlightColor=0;highlightDir=0;}
		}
		else
		if(highlightDir==0)
		{
			highlightColor+=Engine().engineTicksPassed()*overlayFadeSpeedTicksMultiplier;
			if(highlightColor>=1.0f){highlightColor=1.0f;highlightDir=1;}
		}


		//------------------------------------------
		//slide out cart if we aren't pressing a direction
		//------------------------------------------
		if(NDMenu.directionButtonPressed==true)
		{
			cartSlideX=0;
		}
		else
		{
			if(cartSlideX<10)cartSlideX+=Engine().engineTicksPassed()*cartSlideXSpeedTicksMultiplier;
			if(cartSlideX>10)cartSlideX=10;
		}




		for(int c=0;c<wheelItems.size();c++)
		{

			//------------------------------------------
			//set position
			//------------------------------------------

			//tempWheelItemXY.y = wheelItem[c].y;//(y%cart_size_y)+((c-1)*cart_size_y);
			wheelItems.get(c).x =
						(float)
						(
							(ND.SCREEN_SIZE_X/2.0f)
							+
							25.0f
							-
							(
								40.0f
								*
								(
									Math.sin(
												(float)(
															(
																(wheelItems.get(c).y+2.0f)
															)/66.0f
														)
												)
								)
							)
						);


		}

		//------------------------------------------
		//slide out selected item
		//------------------------------------------
		wheelItems.get(selectedWheelItem).x-=cartSlideX;



		if(selectionColorSpinEnabled==true)
		{

			long ticks = Engine().engineTicksPassed();
			selectionBoxTicks+=ticks;

			if(selectionBoxTicks>20)
			{
				selectionBoxTicks=0;

				selectionBoxFrame++;
				if(selectionBoxFrame>14)selectionBoxFrame=0;
			}
		}

	}








}
