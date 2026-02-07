package com.bobsgame.client.engine.game.gui.statusbar.buttons;



import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.game.ClientGameEngine;


//=========================================================================================================================
public class StuffButton extends StatusBarButton
{// =========================================================================================================================


	// =========================================================================================================================
	public StuffButton(ClientGameEngine g)
	{// =========================================================================================================================
		super(g);


		texture=GLUtils.loadTexture("res/statusbar/stuff.png");


		offsetX0=0;// GameStoreButton.dividerX+20;//280
		offsetX1=0;// offsetX0+54;//334

		pressedOffsetY=0;
		offsetY0=3;
		offsetY1=5;


		dividerX=0;// offsetX1+20;//254

		glowX0=0;// offsetX0-60;
		glowX1=0;// offsetX1+60;

		glowY0=-40;
		glowY1=60;

		clickX0 = 260;
		clickX1 = dividerX;

	}


	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================
		setOffsets();

	}

	//=========================================================================================================================
	public void setOffsets()
	{//=========================================================================================================================

		offsetX0=StatusBar().gameStoreButton.dividerX+20;// 280
		offsetX1=offsetX0+54;// 334
		dividerX=offsetX1+20;// 254


		glowX0=offsetX0-60;
		glowX1=offsetX1+60;

		clickX0 = 260;
		clickX1 = dividerX;
	}



	//=========================================================================================================================
	public void clicked()
	{//=========================================================================================================================

		if(PlayerEditMenu().isActivated()==true) return;

		// only open/close if we're on this tab or it isn't showing
		// if(StartMenuWidget.isShowing==false||StartMenuWidget.statusPanel.isVisible()==true)
		if(GameStore().isActivated()&&GameStore().isScrollingDown()==false) GameStore().toggleActivated();

		StuffMenu().toggleActivated();

		StuffMenu().stuffMenuTabs[0].getModel().setSelected(true);
		StuffMenu().stuffMenuTabs[0].getModel().fireActionCallback();
	}
	//=========================================================================================================================
	public boolean isAssociatedMenuActive()
	{//=========================================================================================================================

		return StuffMenu().isActivated();
	}







}
