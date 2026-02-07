package com.bobsgame.client.engine.game.gui.stuffMenu;


import com.bobsgame.client.engine.game.gui.GUIManager;
import com.bobsgame.client.engine.game.gui.MenuPanel;
import com.bobsgame.client.engine.game.gui.stuffMenu.subMenus.*;


import de.matthiasmann.twl.ScrollPane;
import de.matthiasmann.twl.model.OptionBooleanModel;
import de.matthiasmann.twl.model.SimpleIntegerModel;
import de.matthiasmann.twl.ToggleButton;

//=========================================================================================================================
public class StuffMenu extends MenuPanel
{//=========================================================================================================================


	public FriendsPanel friendsPanel;
	public DebugInfoPanel debugInfoPanel;
	public StatusPanel statusPanel;
	public MessagesPanel messagesPanel;
	public ItemsPanel itemsPanel;
	public LogsPanel logsPanel;
	public ControlsPanel controlsPanel;
	public SettingsPanel settingsPanel;
	public GameEditorPanel gameEditorPanel;


	public ToggleButton[] stuffMenuTabs;


	public float subPanelScreenWidthPercent = 0.80f;
	public float subPanelScreenHeightPercent = 0.86f;



	//=========================================================================================================================
	public StuffMenu()
	{//=========================================================================================================================

		super();


		setTheme("stuffmenu");



		statusPanel = new StatusPanel();
		itemsPanel = new ItemsPanel();
		messagesPanel = new MessagesPanel();
		friendsPanel = new FriendsPanel();
		logsPanel = new LogsPanel();
		controlsPanel = new ControlsPanel();
		settingsPanel = new SettingsPanel();
		debugInfoPanel = new DebugInfoPanel();
		gameEditorPanel = new GameEditorPanel();


		stuffMenuTabs = new ToggleButton[9];
		SimpleIntegerModel startMenuTabsIntModel = new SimpleIntegerModel(1, stuffMenuTabs.length, 0);

		for(int i=0 ; i<stuffMenuTabs.length; i++)
		{
			stuffMenuTabs[i] = new ToggleButton(new OptionBooleanModel(startMenuTabsIntModel, i+1));
			stuffMenuTabs[i].setCanAcceptKeyboardFocus(false);
			stuffMenuTabs[i].setTheme(GUIManager.buttonTheme);
		}


		stuffMenuTabs[0].setText("Account Status");
		stuffMenuTabs[1].setText("Items");
		stuffMenuTabs[2].setText("Messages");
		stuffMenuTabs[3].setText("Friends");
		stuffMenuTabs[4].setText("Game Logs");
		stuffMenuTabs[5].setText("Controls");
		stuffMenuTabs[6].setText("Settings");
		stuffMenuTabs[7].setText("Debug Info");
		stuffMenuTabs[8].setText("Game Editor");


		//---------------------------------------------------------
		//status
		//---------------------------------------------------------
		stuffMenuTabs[0].addCallback(new Runnable()
		{
			public void run()
			{
				setAllInvisible();
				statusPanel.setVisible(true);
			}
		});
		//---------------------------------------------------------
		//stuff
		//---------------------------------------------------------
		stuffMenuTabs[1].addCallback(new Runnable()
		{
			public void run()
			{
				setAllInvisible();
				itemsPanel.setVisible(true);

			}
		});
		//---------------------------------------------------------
		//messages
		//---------------------------------------------------------
		stuffMenuTabs[2].addCallback(new Runnable()
		{
			public void run()
			{
				setAllInvisible();
				messagesPanel.setVisible(true);
			}
		});

		//---------------------------------------------------------
		//friends
		//---------------------------------------------------------
		stuffMenuTabs[3].addCallback(new Runnable()
		{
			public void run()
			{
				setAllInvisible();
				friendsPanel.setVisible(true);
			}
		});

		//---------------------------------------------------------
		//logs
		//---------------------------------------------------------
		stuffMenuTabs[4].addCallback(new Runnable()
		{
			public void run()
			{
				setAllInvisible();
				logsPanel.setVisible(true);
			}
		});

		//---------------------------------------------------------
		//controls
		//---------------------------------------------------------
		stuffMenuTabs[5].addCallback(new Runnable()
		{
			public void run()
			{
				setAllInvisible();
				controlsPanel.setVisible(true);
			}
		});

		//---------------------------------------------------------
		//settings
		//---------------------------------------------------------
		stuffMenuTabs[6].addCallback(new Runnable()
		{
			public void run()
			{
				setAllInvisible();
				settingsPanel.setVisible(true);
			}
		});

		//---------------------------------------------------------
		//debug
		//---------------------------------------------------------
		stuffMenuTabs[7].addCallback(new Runnable()
		{
			public void run()
			{
				setAllInvisible();
				debugInfoPanel.setVisible(true);
			}
		});

		//---------------------------------------------------------
		//game editor
		//---------------------------------------------------------
		stuffMenuTabs[8].addCallback(new Runnable()
		{
			public void run()
			{
				setAllInvisible();
				gameEditorPanel.setVisible(true);
			}
		});




		insideScrollPaneLayout.setHorizontalGroup
		(
				insideScrollPaneLayout.createParallelGroup()
				.addGroup(insideScrollPaneLayout.createSequentialGroup().addGap().addWidgets(stuffMenuTabs[0],stuffMenuTabs[5],stuffMenuTabs[7],stuffMenuTabs[8]).addGap())
				//.addGroup(insideScrollPaneLayout.createSequentialGroup().addGap().addWidgets(stuffMenuTabs[0],stuffMenuTabs[1],stuffMenuTabs[2],stuffMenuTabs[3]).addGap())
				//.addGroup(insideScrollPaneLayout.createSequentialGroup().addGap().addWidgets(stuffMenuTabs[4],stuffMenuTabs[5],stuffMenuTabs[6],stuffMenuTabs[7]).addGap())

				.addGroup(insideScrollPaneLayout.createParallelGroup(debugInfoPanel,settingsPanel,controlsPanel,messagesPanel,itemsPanel,logsPanel,statusPanel,friendsPanel,gameEditorPanel))

		);

		insideScrollPaneLayout.setVerticalGroup
		(
				insideScrollPaneLayout.createSequentialGroup()
				.addGroup(insideScrollPaneLayout.createParallelGroup(stuffMenuTabs[0],stuffMenuTabs[5],stuffMenuTabs[7],stuffMenuTabs[8]))
				//.addGroup(insideScrollPaneLayout.createParallelGroup(stuffMenuTabs[0],stuffMenuTabs[1],stuffMenuTabs[2],stuffMenuTabs[3]))
				//.addGroup(insideScrollPaneLayout.createParallelGroup(stuffMenuTabs[4],stuffMenuTabs[5],stuffMenuTabs[6],stuffMenuTabs[7]))

				.addGroup(insideScrollPaneLayout.createParallelGroup(debugInfoPanel,settingsPanel,controlsPanel,messagesPanel,itemsPanel,logsPanel,statusPanel,friendsPanel,gameEditorPanel))

		);




		//---------------------
		//scrollpane
		//----------------------

		scrollPane = new ScrollPane();

		scrollPane.setTheme(GUIManager.scrollPaneTheme);
		scrollPane.setCanAcceptKeyboardFocus(false);
		scrollPane.setExpandContentSize(true);


		//---------------------
		//add scrollpane to outside panel
		//----------------------

		//i don't need it here, i am adding the subpanels directly and they contain their own scrollpane.
		//mainPanelLayout.add(scrollPane);


		mainPanelLayout.setCanAcceptKeyboardFocus(false);
		mainPanelLayout.setHorizontalGroup
		(
				mainPanelLayout.createParallelGroup(insideScrollPaneLayout)
		);

		mainPanelLayout.setVerticalGroup
		(
				mainPanelLayout.createSequentialGroup(insideScrollPaneLayout)
		);


		add(mainPanelLayout);




	}

	//=========================================================================================================================
	public void setActivated(boolean b)
	{//=========================================================================================================================

		if(b==true&&(StatusBar().stuffButton.enabled==false||enabled()==false))return;

		super.setActivated(b);

	}


	//=========================================================================================================================
	public void setAllInvisible()
	{//=========================================================================================================================
		debugInfoPanel.setVisible(false);
		settingsPanel.setVisible(false);
		controlsPanel.setVisible(false);
		messagesPanel.setVisible(false);
		statusPanel.setVisible(false);
		friendsPanel.setVisible(false);
		logsPanel.setVisible(false);
		itemsPanel.setVisible(false);
		gameEditorPanel.setVisible(false);
	}

	//=========================================================================================================================
	public void openSubMenu(SubPanel subPanel)
	{//=========================================================================================================================
		setAllInvisible();
		subPanel.setVisible(true);

	}

	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================
		//super.init();

		debugInfoPanel.init();
		settingsPanel.init();
		controlsPanel.init();
		messagesPanel.init();
		statusPanel.init();
		friendsPanel.init();
		logsPanel.init();
		itemsPanel.init();
		gameEditorPanel.init();
	}

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================
		super.update();

		if(isActivated()==false)return;

		if(debugInfoPanel.isVisible())debugInfoPanel.update();
		if(settingsPanel.isVisible())settingsPanel.update();
		if(controlsPanel.isVisible())controlsPanel.update();
		if(messagesPanel.isVisible())messagesPanel.update();
		if(statusPanel.isVisible())statusPanel.update();
		if(friendsPanel.isVisible())friendsPanel.update();
		if(logsPanel.isVisible())logsPanel.update();
		if(itemsPanel.isVisible())itemsPanel.update();
		if(gameEditorPanel.isVisible())gameEditorPanel.update();
	}


	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================

		super.render();

		if(isActivated()==false)return;

		//additional rendering calls go here (after gui is drawn)
		if(debugInfoPanel.isVisible())debugInfoPanel.render();
		if(settingsPanel.isVisible())settingsPanel.render();
		if(controlsPanel.isVisible())controlsPanel.render();
		if(messagesPanel.isVisible())messagesPanel.render();
		if(statusPanel.isVisible())statusPanel.render();
		if(friendsPanel.isVisible())friendsPanel.render();
		if(logsPanel.isVisible())logsPanel.render();
		if(itemsPanel.isVisible())itemsPanel.render();
		if(gameEditorPanel.isVisible())gameEditorPanel.render();

	}

	//=========================================================================================================================
	@Override
	protected void layout()
	{//=========================================================================================================================


		if(isActivated()==false)return;







		if(debugInfoPanel.isVisible())debugInfoPanel.layout();
		if(settingsPanel.isVisible())settingsPanel.layout();
		if(controlsPanel.isVisible())controlsPanel.layout();
		if(messagesPanel.isVisible())messagesPanel.layout();
		if(statusPanel.isVisible())statusPanel.layout();
		if(friendsPanel.isVisible())friendsPanel.layout();
		if(logsPanel.isVisible())logsPanel.layout();
		if(itemsPanel.isVisible())itemsPanel.layout();
		if(gameEditorPanel.isVisible())gameEditorPanel.layout();

		insideScrollPaneLayout.setMinSize((int)(mainPanelLayout.getWidth()*0.80f), (int)(mainPanelLayout.getHeight()*0.80f));
		insideScrollPaneLayout.setSize((int)(mainPanelLayout.getWidth()*0.80f), (int)(mainPanelLayout.getHeight()*0.80f));

		super.layout();


	}







}
