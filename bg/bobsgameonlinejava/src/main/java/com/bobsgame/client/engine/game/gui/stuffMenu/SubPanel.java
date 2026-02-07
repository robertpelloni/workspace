package com.bobsgame.client.engine.game.gui.stuffMenu;

import com.bobsgame.ClientMain;
import com.bobsgame.client.engine.game.Clock;
import com.bobsgame.client.engine.game.FriendManager;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.client.engine.game.Player;
import com.bobsgame.client.engine.game.Wallet;
import com.bobsgame.client.engine.game.gui.GUIManager;
import com.bobsgame.client.engine.game.gui.PlayerEditMenu;
import com.bobsgame.client.engine.game.gui.gameStore.GameStore;
import com.bobsgame.client.engine.game.gui.statusbar.NotificationManager;
import com.bobsgame.client.engine.game.gui.statusbar.StatusBar;
import com.bobsgame.client.engine.game.nd.ND;
import com.bobsgame.net.GameSave;
import com.bobsgame.client.engine.event.EventManager;
import com.bobsgame.client.network.GameClientTCP;

import de.matthiasmann.twl.DialogLayout;
import de.matthiasmann.twl.ScrollPane;


//=========================================================================================================================
public class SubPanel extends DialogLayout
{//=========================================================================================================================

	public ScrollPane scrollPane;
	public DialogLayout insideLayout;

	public DialogLayout thisDialogLayout;


	//=========================================================================================================================
	public SubPanel()
	{//=========================================================================================================================


		thisDialogLayout = this;



		setTheme(GUIManager.subMenuPanelDialogLayoutTheme);

		//----------------------
		//setup layout inside scrollpane
		//----------------------
		insideLayout = new DialogLayout();
		insideLayout.setTheme(GUIManager.emptyDialogLayoutTheme);
		insideLayout.setCanAcceptKeyboardFocus(false);





		//----------------------
		//setup scrollpane
		//----------------------

		scrollPane = new ScrollPane(insideLayout);
		scrollPane.setTheme(GUIManager.scrollPaneTheme);
		scrollPane.setCanAcceptKeyboardFocus(false);
		scrollPane.setExpandContentSize(true);


		//----------------------
		//setup this dialoglayout
		//----------------------

		add(scrollPane);
		setVisible(false);

		setCanAcceptKeyboardFocus(false);
		setHorizontalGroup
		(
				createParallelGroup(scrollPane)
		);

		setVerticalGroup
		(
				createSequentialGroup(scrollPane)
		);
	}

	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================
		//put anything in here that you want to happen after the subpanel is created and constructed

	}

	//=========================================================================================================================
	public void setVisible(boolean b)
	{//=========================================================================================================================
		super.setVisible(b);

		//put anything in here that you want to happen when we switch to the subpanel

	}



	//=========================================================================================================================
	public void layout()
	{//=========================================================================================================================




		scrollPane.setMinSize((int)(StuffMenu().insideScrollPaneLayout.getInnerWidth()*StuffMenu().subPanelScreenWidthPercent), (int)(StuffMenu().insideScrollPaneLayout.getInnerHeight()*StuffMenu().subPanelScreenHeightPercent));
		scrollPane.setSize((int)(StuffMenu().insideScrollPaneLayout.getInnerWidth()*StuffMenu().subPanelScreenWidthPercent), (int)(StuffMenu().insideScrollPaneLayout.getInnerHeight()*StuffMenu().subPanelScreenHeightPercent));
		//scrollPane.adjustSize();

		scrollPane.updateScrollbarSizes();

		super.layout();

	}

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

		//put anything in here that you want to change every frame

	}

	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================

	}








	public static ClientGameEngine ClientEngine()
	{
		return ClientMain.clientMain.clientGameEngine;
	}
	public static EventManager EventManager()
	{
		if(ClientEngine()==null)return null;
		return ClientEngine().eventManager;
	}
	public static Clock Clock()
	{
		if(ClientEngine()==null)return null;
		return ClientEngine().clock;
	}
	public static GUIManager GUIManager()
	{
		if(ClientEngine()==null)return null;
		return ClientEngine().guiManager;
	}
	public static StuffMenu StuffMenu()
	{
		if(ClientEngine()==null)return null;
		return GUIManager().stuffMenu;
	}
	public static GameStore GameStore()
	{
		if(ClientEngine()==null)return null;
		return GUIManager().gameStore;
	}
	public static PlayerEditMenu PlayerEditMenu()
	{
		if(ClientEngine()==null)return null;
		return GUIManager().playerEditMenu;
	}
	public static Player Player()
	{
		if(ClientEngine()==null)return null;
		return ClientEngine().player;
	}
	public static ND ND()
	{
		if(ClientEngine()==null)return null;
		return ClientEngine().nD;
	}
	public static Wallet Wallet()
	{
		if(ClientEngine()==null)return null;
		return ClientEngine().wallet;
	}
	public static FriendManager FriendManager()
	{
		if(ClientEngine()==null)return null;
		return ClientEngine().friendManager;
	}
	public static StatusBar StatusBar()
	{
		if(ClientEngine()==null)return null;
		return ClientEngine().statusBar;
	}
	public static NotificationManager NotificationManager()
	{
		if(ClientEngine()==null)return null;
		return StatusBar().notificationManager;
	}
	synchronized public static GameSave GameSave()
	{
		if(ClientEngine()==null)return null;
		return ClientEngine().gameSave_S();
	}

	public static GameClientTCP GameClientTCP() {
		return ClientMain.clientMain.gameClientTCP;
	}

}
