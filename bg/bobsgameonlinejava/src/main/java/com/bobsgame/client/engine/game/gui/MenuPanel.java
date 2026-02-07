package com.bobsgame.client.engine.game.gui;
import com.bobsgame.client.LWJGLUtils;




import com.bobsgame.ClientMain;
import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.game.Clock;
import com.bobsgame.client.engine.game.FriendManager;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.client.engine.game.Player;
import com.bobsgame.client.engine.game.Wallet;
import com.bobsgame.client.engine.game.gui.gameStore.GameStore;
import com.bobsgame.client.engine.game.gui.statusbar.NotificationManager;
import com.bobsgame.client.engine.game.gui.statusbar.StatusBar;
import com.bobsgame.client.engine.game.gui.stuffMenu.StuffMenu;
import com.bobsgame.client.engine.game.nd.ND;

import com.bobsgame.client.network.GameClientTCP;
import com.bobsgame.net.GameSave;

import de.matthiasmann.twl.DialogLayout;
import de.matthiasmann.twl.ScrollPane;
import de.matthiasmann.twl.Widget;
import easing.Easing;
//=========================================================================================================================
public class MenuPanel extends Widget
{//=========================================================================================================================


	public DialogLayout mainPanelLayout;
	public ScrollPane scrollPane;
	public DialogLayout insideScrollPaneLayout;




	protected boolean isActivated = false;
	protected boolean isScrollingDown = false;
	protected boolean isScrolledUp = false;

	public int ticksSinceTurnedOn = 0;
	public int ticksSinceTurnedOff = 0;

	public float screenY = 0;


	public float fadeInTime = 600.0f;
	public float fadeOutTime = 1000.0f;




	private boolean enabled = true;

	//=========================================================================================================================
	public MenuPanel()
	{//=========================================================================================================================



		setCanAcceptKeyboardFocus(false);



		//----------------------
		//outside panel, just attached to "nothing"
		//----------------------

		mainPanelLayout = new DialogLayout();

		//if(stuffMenu().lightTheme==true)
		//mainPanelLayout.setTheme(GUIManager.lightThemeString);
		//else
		mainPanelLayout.setTheme(GUIManager.darkThemeString);


		//---------------------
		//this goes inside the scrollpane which goes inside mainPanelLayout. for the stuff menu we just attach it directly to mainPanelLayout because the submenus have scrollpanes.
		//----------------------

		insideScrollPaneLayout = new DialogLayout();
		insideScrollPaneLayout.setTheme(GUIManager.emptyDialogLayoutTheme);
		insideScrollPaneLayout.setCanAcceptKeyboardFocus(false);





	}





	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

		if(isActivated==true)
		{

			if(isScrollingDown==false)
			{
				ticksSinceTurnedOff=0;
				ticksSinceTurnedOn+=Engine.mainTicksPassed;

				scrollUp();
			}
			else
			if(isScrollingDown==true)
			{
				ticksSinceTurnedOn=0;
				ticksSinceTurnedOff+=Engine.mainTicksPassed;

				scrollDown();
			}

		}

	}


	//=========================================================================================================================
	public void setEnabled(boolean b)
	{//=========================================================================================================================
		enabled = b;

		if(b==false)if(isActivated()==true)setActivated(false);

	}
	//=========================================================================================================================
	public boolean enabled()
	{//=========================================================================================================================
		return enabled;
	}

	//=========================================================================================================================
	public boolean isActivated()
	{//=========================================================================================================================
		return isActivated;
	}

	//=========================================================================================================================
	public boolean isScrollingDown()
	{//=========================================================================================================================
		return isScrollingDown;
	}

	//=========================================================================================================================
	public boolean isScrolledUp()
	{//=========================================================================================================================
		return isScrolledUp;
	}

	//=========================================================================================================================
	public void setActivated(boolean b)
	{//=========================================================================================================================

		if(b==true&&enabled()==false)return;

		if(b==true)
		{
			isScrollingDown=false;
			isActivated=true;
			ticksSinceTurnedOn=0;

			screenY = (float) (LWJGLUtils.SCREEN_SIZE_Y);
			super.setVisible(true);
		}
		else
		if(b==false)
		{
			if(isActivated==true)
			{
				isScrolledUp = false;

				if(isScrollingDown==false)
				{
					isScrollingDown=true;
					ticksSinceTurnedOff=0;
					if(ticksSinceTurnedOn<fadeInTime)ticksSinceTurnedOff=(int)(fadeOutTime-((ticksSinceTurnedOn/fadeInTime)*fadeOutTime));
				}
			}
		}

	}


	//=========================================================================================================================
	public void toggleActivated()
	{//=========================================================================================================================

		if(isActivated==false)
		{
			setActivated(true);
		}
		else
		if(isActivated==true)
		{

			if(isScrollingDown==true)
			{
				isScrollingDown=false;
			}
			else
			setActivated(false);
		}

	}

	//=========================================================================================================================
	public void onScrolledUp()
	{//=========================================================================================================================

	}

	//=========================================================================================================================
	public void scrollUp()
	{//=========================================================================================================================
		if(ticksSinceTurnedOn<=fadeInTime)
		{
			screenY = (float) ((LWJGLUtils.SCREEN_SIZE_Y)-(Easing.easeOutCubic(ticksSinceTurnedOn, 0, LWJGLUtils.SCREEN_SIZE_Y, fadeInTime)));
			layout();
		}

		//if it's supposed to be scrolled all the way up, make sure it is.
		else
		if(isScrolledUp==false)
		{

				onScrolledUp();
				isScrolledUp=true;

				if(screenY!=0)
				{
					screenY=0;
					layout();
				}

		}

	}

	//=========================================================================================================================
	public void scrollDown()
	{//=========================================================================================================================
		if(ticksSinceTurnedOff<=fadeOutTime)
		{
			screenY = (float) (Easing.easeOutParabolicBounce(ticksSinceTurnedOff, 0, LWJGLUtils.SCREEN_SIZE_Y, fadeOutTime));
			layout();
		}
		else
		{
			isActivated=false;
			isScrollingDown=false;
			super.setVisible(false);
		}
	}



	//=========================================================================================================================
	@Override
	protected void layout()
	{//=========================================================================================================================








		mainPanelLayout.adjustSize();
		mainPanelLayout.setSize((int)(LWJGLUtils.SCREEN_SIZE_X*0.90f),(int)(LWJGLUtils.SCREEN_SIZE_Y*0.90f));



		// main panel is centered
		mainPanelLayout.setPosition(
				(getInnerX() + (getInnerWidth() - mainPanelLayout.getWidth()) / 2),
				(int)(screenY+(getInnerY() + (getInnerHeight() - mainPanelLayout.getHeight()) / 2)));



		scrollPane.setMinSize((int)(mainPanelLayout.getWidth()*0.86f), (int)(mainPanelLayout.getHeight()*0.86f));
		scrollPane.setSize((int)(mainPanelLayout.getWidth()*0.86f), (int)(mainPanelLayout.getHeight()*0.86f));




		super.layout();


	}


	//=========================================================================================================================
	public void renderBefore()
	{//=========================================================================================================================


		if(isScrollingDown==true)return;
		if(isActivated==false)return;


		GLUtils.drawFilledRect(0, 0, 0, 0, LWJGLUtils.SCREEN_SIZE_X, 0, LWJGLUtils.SCREEN_SIZE_Y, 0.5f);



	}


	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================


		if(isScrollingDown==true)return;
		if(isActivated==false)return;


	}






	public static ClientGameEngine ClientGameEngine()
	{
		if(ClientMain.clientMain==null)return null;

		return ClientMain.clientMain.clientGameEngine;
	}

	public static GameClientTCP Network()
	{
		if(ClientMain.clientMain==null)return null;
		return ClientMain.clientMain.gameClientTCP;
	}

	public static Clock Clock()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().clock;
	}
	public static GUIManager GUIManager()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().guiManager;
	}
	public static StuffMenu StuffMenu()
	{
		if(ClientGameEngine()==null)return null;
		return GUIManager().stuffMenu;
	}
	public static GameStore GameStore()
	{
		if(ClientGameEngine()==null)return null;
		return GUIManager().gameStore;
	}
	public static PlayerEditMenu PlayerEditMenu()
	{
		if(ClientGameEngine()==null)return null;
		return GUIManager().playerEditMenu;
	}
	public static Player Player()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().player;
	}
	public static ND ND()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().nD;
	}
	public static Wallet Wallet()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().wallet;
	}
	public static FriendManager FriendManager()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().friendManager;
	}
	public static StatusBar StatusBar()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().statusBar;
	}
	public static NotificationManager NotificationManager()
	{
		if(ClientGameEngine()==null)return null;
		return StatusBar().notificationManager;
	}
	public static GameSave GameSave()
	{
		if(ClientGameEngine()==null)return null;
		return ClientGameEngine().gameSave_S();
	}





}
