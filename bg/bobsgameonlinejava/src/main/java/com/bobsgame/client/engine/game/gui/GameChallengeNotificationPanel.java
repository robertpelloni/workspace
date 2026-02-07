package com.bobsgame.client.engine.game.gui;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.engine.game.FriendCharacter;
import com.bobsgame.client.engine.game.nd.NDGameEngine;

import de.matthiasmann.twl.Button;
import de.matthiasmann.twl.DialogLayout;
import de.matthiasmann.twl.GUI;
import de.matthiasmann.twl.Label;


//=========================================================================================================================
public class GameChallengeNotificationPanel extends MenuPanel
{//=========================================================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(GameChallengeNotificationPanel.class);


	DialogLayout notificationPanel;

	Button yesButton;
	Button noButton;

	FriendCharacter friend = null;
	String gameName = "";

	public long notificationCreatedTime = 0;

	Label timeLeftLabel = null;

	//=========================================================================================================================
	public GameChallengeNotificationPanel(FriendCharacter friend, String gameName)
	{//=========================================================================================================================

		super();

		this.notificationCreatedTime = System.currentTimeMillis();

		this.friend = friend;
		this.gameName = gameName;


		notificationPanel = new DialogLayout();
		notificationPanel.setTheme("darkLayout");


		Label notificationPanelLabel = new Label("Game Challenge!");
		notificationPanelLabel.setCanAcceptKeyboardFocus(false);
		notificationPanelLabel.setTheme("bigLabel");

		Label challengeTextLabel = new Label(""+friend.name()+" has challenged you to play "+gameName);
		challengeTextLabel.setCanAcceptKeyboardFocus(false);

		timeLeftLabel = new Label("");
		timeLeftLabel.setCanAcceptKeyboardFocus(false);

		//---------------------------------------------------------
		//yes
		//---------------------------------------------------------
		yesButton = new Button("Yes");
		yesButton.setCanAcceptKeyboardFocus(false);
		yesButton.addCallback(new Runnable()
		{
			public void run()
			{
				doYes();
			}
		});


		//---------------------------------------------------------
		//no
		//---------------------------------------------------------
		noButton = new Button("No");
		noButton.setCanAcceptKeyboardFocus(false);
		noButton.addCallback(new Runnable()
		{
			public void run()
			{
				doNo();
			}
		});




		notificationPanel.setHorizontalGroup(

											notificationPanel.createParallelGroup
											(
													notificationPanel.createParallelGroup().addMinGap(200)
													,
													notificationPanel.createSequentialGroup
													(
														notificationPanel.createParallelGroup().addMinGap(20)
														,
														notificationPanel.createParallelGroup
														(
															notificationPanel.createSequentialGroup().addGap().addWidget(notificationPanelLabel).addGap()
															,
															notificationPanel.createSequentialGroup().addGap().addWidget(timeLeftLabel).addGap()
															,
															notificationPanel.createSequentialGroup().addGap().addWidget(challengeTextLabel).addGap()
															,
															notificationPanel.createSequentialGroup().addGap().addWidget(noButton).addGap().addWidget(yesButton).addGap()

														)
														,
														notificationPanel.createParallelGroup().addMinGap(20)
													)
											)
										);


		notificationPanel.setVerticalGroup(
											notificationPanel.createSequentialGroup
											(
												notificationPanel.createSequentialGroup().addMinGap(20),

												notificationPanel.createParallelGroup(notificationPanelLabel)
												,
												notificationPanel.createSequentialGroup().addMinGap(20)
												,
												notificationPanel.createParallelGroup(challengeTextLabel)
												,
												notificationPanel.createParallelGroup(timeLeftLabel)
												,
												notificationPanel.createSequentialGroup().addMinGap(20)
												,
												notificationPanel.createParallelGroup(noButton, yesButton)
												,
												notificationPanel.createSequentialGroup().addMinGap(50)
											)
									);




//		//---------------------------------------------------------
//		//layout
//		//---------------------------------------------------------
//
//		insideScrollPaneLayout.setHorizontalGroup
//		(
//				insideScrollPaneLayout.createParallelGroup
//				(
//						insideScrollPaneLayout.createSequentialGroup().addGap().addWidget(notificationPanel).addGap()
//				)
//		);
//
//		insideScrollPaneLayout.setVerticalGroup
//		(
//				insideScrollPaneLayout.createSequentialGroup
//				(
//						insideScrollPaneLayout.createSequentialGroup().addGap()
//						,
//						insideScrollPaneLayout.createParallelGroup().addWidget(notificationPanel)
//						,
//						insideScrollPaneLayout.createSequentialGroup().addGap()
//				)
//		);
//
//
//
//
//
//		//---------------------
//		//scrollpane
//		//----------------------
//
//		scrollPane = new ScrollPane(insideScrollPaneLayout);
//
//		scrollPane.setTheme(GUIManager.scrollPaneTheme);
//		scrollPane.setCanAcceptKeyboardFocus(false);
//		scrollPane.setExpandContentSize(true);
//
//
//		//---------------------
//		//add scrollpane to outside panel
//		//----------------------
//
//		//mainPanelLayout.add(scrollPane);
//
//
		mainPanelLayout.setCanAcceptKeyboardFocus(false);
		mainPanelLayout.setHorizontalGroup
		(
				mainPanelLayout.createParallelGroup(notificationPanel)
		);

		mainPanelLayout.setVerticalGroup
		(
				mainPanelLayout.createSequentialGroup(notificationPanel)
		);


		add(mainPanelLayout);






		notificationPanel.adjustSize();


		setActivated(true);



	}

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================
		super.update();

		long currentTime = System.currentTimeMillis();

		if(currentTime - notificationCreatedTime > 20000)
		{
			setActivated(false);

			GUIManager().removeGameNotification(this);
		}

		timeLeftLabel.setText("Time Left: "+((20000 - (currentTime - notificationCreatedTime))/1000));

	}


	//=========================================================================================================================
	public void onScrolledUp()
	{//=========================================================================================================================


	}


	//=========================================================================================================================
	public void scrollUp()
	{//=========================================================================================================================

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


		isActivated=false;
		isScrollingDown=false;
		super.setVisible(false);

	}

	//=========================================================================================================================
	@Override
	protected void layout()
	{//=========================================================================================================================

		mainPanelLayout.adjustSize();

		// main panel is centered
		mainPanelLayout.setPosition(0,20);
				//(getInnerX() + (getInnerWidth() - mainPanelLayout.getWidth()) / 2),
				//(int)(screenY+(getInnerY() + (getInnerHeight() - mainPanelLayout.getHeight()) / 2)));



		notificationPanel.adjustSize();
		//notificationPanel.setPosition(0,20);
				//insideScrollPaneLayout.getInnerX() + (insideScrollPaneLayout.getInnerWidth() - notificationPanel.getWidth()) / 2,
				//insideScrollPaneLayout.getInnerY() + (insideScrollPaneLayout.getInnerHeight() - notificationPanel.getHeight()) / 2);

		//super.layout();
	}

	//=========================================================================================================================
	public void setButtonsVisible(boolean b)
	{//=========================================================================================================================

		yesButton.setVisible(b);
		noButton.setVisible(b);

	}



	//=========================================================================================================================
	void doNo()
	{//=========================================================================================================================

		GUI gui = getGUI();
		if(gui != null)
		{

			//if click yes, open nD, initialize game with this connection
			//TODO: get game by challenge name





			friend.setOutgoingGameChallengeResponse(NDGameEngine.gameChallengeResponse_DECLINE);

			friend.gameChallengeNotification = null;

			setActivated(false);

			GUIManager().removeGameNotification(this);
		}

	}



	//=========================================================================================================================
	void doYes()
	{//=========================================================================================================================

		GUI gui = getGUI();
		if(gui != null)
		{

			friend.setOutgoingGameChallengeResponse(NDGameEngine.gameChallengeResponse_ACCEPT);

			ND().getGame().setConnection(friend.connection);
			friend.setGameToForwardPacketsTo(ND().getGame());


			GUIManager().openND();

			friend.gameChallengeNotification = null;

			setActivated(false);

			GUIManager().removeGameNotification(this);
		}

	}



	//=========================================================================================================================
	public void renderBefore()
	{//=========================================================================================================================


		if(isScrollingDown()==true)return;
		if(isActivated()==false)return;
		//additional rendering calls go here (after gui is drawn)


	}


	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================


		if(isScrollingDown()==true)return;
		if(isActivated()==false)return;

		//additional rendering calls go here (after gui is drawn)


	}






















}
