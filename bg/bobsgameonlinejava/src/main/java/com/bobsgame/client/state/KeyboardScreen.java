package com.bobsgame.client.state;
import com.bobsgame.client.LWJGLUtils;


import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.engine.game.gui.GUIManager;
import com.bobsgame.client.engine.game.gui.MenuPanel;

import de.matthiasmann.twl.Button;
import de.matthiasmann.twl.DialogLayout;
import de.matthiasmann.twl.GUI;
import de.matthiasmann.twl.Label;
import de.matthiasmann.twl.ScrollPane;
import de.matthiasmann.twl.Widget;
import easing.Easing;


//=========================================================================================================================
public class KeyboardScreen extends MenuPanel
{//=========================================================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(KeyboardScreen.class);


	DialogLayout keyboardPanel;


	public Button okButton;





	//=========================================================================================================================
	public KeyboardScreen()
	{//=========================================================================================================================

		super();




		keyboardPanel = new DialogLayout();
		keyboardPanel.setTheme("keyboardPanel");


		Label controlsPanelLabel = new Label("Controls");
		controlsPanelLabel.setCanAcceptKeyboardFocus(false);
		controlsPanelLabel.setTheme("bigLabel");


		Widget keyboardImagePanel = new Widget()
		{
			public void layout()
			{

				//force the keyboard image to fit inside the layout/scrollpane/layout/layout

				mainPanelLayout.setBorderSize(0, 20);
				insideScrollPaneLayout.setBorderSize(0,20);
				scrollPane.setBorderSize(0,20);

				int w = (int)(mainPanelLayout.getWidth()*0.80f);
				if(w<0)w=128;

				//setMinSize(w,50);
				setMaxSize(w,390);
				//adjustSize();


			}

		};
		keyboardImagePanel.setTheme("keyboardImagePanel");


		Label pressF1Label = new Label("Press F1 to show controls at any time.");
		pressF1Label.setCanAcceptKeyboardFocus(false);
		pressF1Label.setTheme("bigLabel");








		okButton = new Button("OK");
		okButton.setCanAcceptKeyboardFocus(false);
		okButton.addCallback(new Runnable()
		{
			public void run()
			{
				doOK();
			}
		});
		okButton.setVisible(false);



		keyboardPanel.setHorizontalGroup(

											keyboardPanel.createParallelGroup
											(
													keyboardPanel.createParallelGroup().addMinGap(400)
													,
													keyboardPanel.createSequentialGroup
													(
														keyboardPanel.createParallelGroup().addMinGap(50)
														,
														keyboardPanel.createParallelGroup
														(

															keyboardPanel.createSequentialGroup().addGap().addWidget(controlsPanelLabel).addGap()
															,
															keyboardPanel.createSequentialGroup().addGap().addWidget(keyboardImagePanel).addGap()
															,
															keyboardPanel.createSequentialGroup().addGap().addWidget(pressF1Label).addGap()
															,
															keyboardPanel.createSequentialGroup().addGap().addWidget(okButton).addGap()
														)
														,
														keyboardPanel.createParallelGroup().addMinGap(50)
													)
											)
										);


		keyboardPanel.setVerticalGroup(
											keyboardPanel.createSequentialGroup
											(
												keyboardPanel.createSequentialGroup().addMinGap(20),

												keyboardPanel.createParallelGroup(controlsPanelLabel)
												,
												keyboardPanel.createSequentialGroup().addMinGap(20)
												,
												keyboardPanel.createParallelGroup(keyboardImagePanel)
												,
												keyboardPanel.createSequentialGroup().addMinGap(20)
												,
												keyboardPanel.createParallelGroup(pressF1Label),
												keyboardPanel.createParallelGroup(okButton)
												,
												keyboardPanel.createSequentialGroup().addMinGap(50)
											)
									);




		//---------------------------------------------------------
		//layout
		//---------------------------------------------------------

		insideScrollPaneLayout.setHorizontalGroup
		(
				insideScrollPaneLayout.createParallelGroup
				(
						insideScrollPaneLayout.createSequentialGroup().addGap().addWidget(keyboardPanel).addGap()
				)
		);

		insideScrollPaneLayout.setVerticalGroup
		(
				insideScrollPaneLayout.createSequentialGroup
				(
						insideScrollPaneLayout.createSequentialGroup().addGap()
						,
						insideScrollPaneLayout.createParallelGroup().addWidget(keyboardPanel)
						,
						insideScrollPaneLayout.createSequentialGroup().addGap()
				)
		);





		//---------------------
		//scrollpane
		//----------------------

		scrollPane = new ScrollPane(insideScrollPaneLayout);

		scrollPane.setTheme(GUIManager.scrollPaneTheme);
		scrollPane.setCanAcceptKeyboardFocus(false);
		scrollPane.setExpandContentSize(true);


		//---------------------
		//add scrollpane to outside panel
		//----------------------

		//mainPanelLayout.add(scrollPane);
		mainPanelLayout.setTheme("darkMenuNoMainPanel");

		mainPanelLayout.setCanAcceptKeyboardFocus(false);
		mainPanelLayout.setHorizontalGroup
		(
				mainPanelLayout.createParallelGroup(scrollPane)
		);

		mainPanelLayout.setVerticalGroup
		(
				mainPanelLayout.createSequentialGroup(scrollPane)
		);


		add(mainPanelLayout);




		keyboardPanel.adjustSize();


		//setActivated(true);

		//scrollPane.setTheme("darkPanel");
		//insideScrollPaneLayout.setTheme(GUIManager.emptyDialogLayoutTheme);

	}

	boolean _clickedOK = false;

	public synchronized boolean clickedOK_S(){return _clickedOK;}

	public synchronized void setClickedOK_S(boolean b){_clickedOK = b;}



	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================
		if(isActivated==true)
		{

			if(isScrollingDown==false)
			{
				ticksSinceTurnedOff=0;
				ticksSinceTurnedOn+=32;

				scrollUp();
			}
			else
			if(isScrollingDown==true)
			{
				ticksSinceTurnedOn=0;
				ticksSinceTurnedOff+=32;

				scrollDown();
			}

		}

	}


	//=========================================================================================================================
	public void onScrolledUp()
	{//=========================================================================================================================

		getGUI().setTooltipDelay(1);

	}

	//=========================================================================================================================
	public void scrollDown()
	{//=========================================================================================================================
		if(ticksSinceTurnedOff<=fadeOutTime)
		{
			screenY = (float) (Easing.easeOutCubic(ticksSinceTurnedOff, 0, LWJGLUtils.SCREEN_SIZE_Y, fadeOutTime));
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

		//login panel is centered

		keyboardPanel.adjustSize();
		keyboardPanel.setPosition(
				insideScrollPaneLayout.getInnerX() + (insideScrollPaneLayout.getInnerWidth() - keyboardPanel.getWidth()) / 2,
				insideScrollPaneLayout.getInnerY() + (insideScrollPaneLayout.getInnerHeight() - keyboardPanel.getHeight()) / 2);

		super.layout();
	}

	//=========================================================================================================================
	public void setButtonsVisible(boolean b)
	{//=========================================================================================================================

		okButton.setVisible(b);

	}





	//=========================================================================================================================
	void doOK()
	{//=========================================================================================================================

		GUI gui = getGUI();
		if(gui != null)
		{
			//setButtonsVisible(false);

			//create thread, this needs to be a thread because Button.doCallback(Runnable) only calls Runnable.run() which does NOT create a thread.
			new Thread
			(
				new Runnable()
				{
					public void run()
					{
						try{Thread.currentThread().setName("KeyboardScreen_clickOK");}catch(SecurityException e){e.printStackTrace();}

						setActivated(false);

						while(isScrollingDown()){try{Thread.sleep(500);}catch(Exception e){}}

						setClickedOK_S(true);


					}
				}
			).start();
		}
	}



	//=========================================================================================================================
	public void renderBefore()
	{//=========================================================================================================================


		if(isScrollingDown()==true)return;
		if(isActivated()==false)return;
		//additional rendering calls go here (after gui is drawn)


		//ClientMain.glowTileBackground.render();

	}


	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================


		if(isScrollingDown()==true)return;
		if(isActivated()==false)return;

		//additional rendering calls go here (after gui is drawn)


	}






















}
