package com.bobsgame.client.state;


import com.bobsgame.ClientMain;

import com.bobsgame.client.engine.game.gui.GUIManager;
import com.bobsgame.client.engine.game.gui.MenuPanel;

import de.matthiasmann.twl.DialogLayout;
import de.matthiasmann.twl.EditField;
import de.matthiasmann.twl.EditField.Callback;
import de.matthiasmann.twl.Button;
import de.matthiasmann.twl.Event;
import de.matthiasmann.twl.GUI;
import de.matthiasmann.twl.Label;
import de.matthiasmann.twl.ScrollPane;


//=========================================================================================================================
public class CreateNewAccount extends MenuPanel
{//=========================================================================================================================


	//EditField nameEditField;
	EditField emailEditField;

	EditField passwordEditField;
	EditField confirmPasswordEditField;





	Button okButton;
	Button cancelButton;

	public String nameString = "";


	DialogLayout panel;
	DialogLayout emailDialogLayout;
	DialogLayout passwordDialogLayout;
	DialogLayout socialDialogLayout;

	Label errorLabel;
	Label statusLabel;



	Label emailLabel;
	Label passwordLabel;
	Label confirmPasswordLabel;






	//=========================================================================================================================
	public CreateNewAccount()
	{//=========================================================================================================================

		super();





		panel = new DialogLayout();
		panel.setTheme("darkPanel");



		Label createAccountPanelLabel = new Label("Create Account");
		createAccountPanelLabel.setCanAcceptKeyboardFocus(false);
		createAccountPanelLabel.setTheme("bigLabel");


		errorLabel = new Label(" ");
		errorLabel.setTheme("errorLabel");
		errorLabel.setCanAcceptKeyboardFocus(false);

		statusLabel = new Label(" ");
		statusLabel.setCanAcceptKeyboardFocus(false);

		//---------------------------------------------------------
		//username
		//---------------------------------------------------------
//		nameEditField = new EditField();
//		nameEditField.setText("");
//		nameEditField.setMaxTextLength(40);
//		nameEditField.addCallback(new Callback()
//		{
//			@Override
//			public void callback(int key)
//			{
//				//username cannot contain `
//			}
//		});
//		Label nameLabel = new Label("Username");
//		nameLabel.setLabelFor(nameEditField);
//		nameLabel.setCanAcceptKeyboardFocus(false);


		//---------------------------------------------------------
		//email address
		//---------------------------------------------------------
		emailEditField = new EditField();
		emailEditField.setText("");
		emailEditField.setMaxTextLength(40);
		emailEditField.addCallback(new Callback()
		{
			@Override
			public void callback(int key)
			{

			}
		});
		emailLabel = new Label("Email Address:");
		emailLabel.setLabelFor(emailEditField);
		emailLabel.setCanAcceptKeyboardFocus(false);


		//---------------------------------------------------------
		//password
		//---------------------------------------------------------
		passwordEditField = new EditField();
		passwordEditField.setPasswordMasking(true);
		passwordLabel = new Label("Password:");
		passwordLabel.setLabelFor(passwordEditField);


		passwordEditField.addCallback(new EditField.Callback()
		{
			public void callback(int key)
			{
				if(key == Event.KEY_RETURN)
				{
					doCreateAccount();
				}
				else
				if(passwordEditField.getTextLength()>0)
				{

				}
				else
				if(passwordEditField.getTextLength()==0)
				{

				}
			}
		});



		//---------------------------------------------------------
		//confirm password
		//---------------------------------------------------------
		confirmPasswordEditField = new EditField();
		confirmPasswordEditField.setPasswordMasking(true);
		confirmPasswordLabel = new Label("Confirm Password:");
		confirmPasswordLabel.setLabelFor(confirmPasswordEditField);



		confirmPasswordEditField.addCallback(new EditField.Callback()
		{
			public void callback(int key)
			{
				if(key == Event.KEY_RETURN)
				{
					doCreateAccount();
				}
				else
				if(confirmPasswordEditField.getTextLength()>0)
				{

				}
				else
				if(confirmPasswordEditField.getTextLength()==0)
				{

				}
			}
		});


		//---------------------------------------------------------
		//email box
		//---------------------------------------------------------

		emailDialogLayout = new DialogLayout();
		emailDialogLayout.setCanAcceptKeyboardFocus(false);

		emailDialogLayout.setHorizontalGroup
		(
			emailDialogLayout.createSequentialGroup
			(
				emailDialogLayout.createParallelGroup
				(
					//usernameDialogLayout.createSequentialGroup().addGap().addWidgets(nameLabel).addGap(),
					emailDialogLayout.createSequentialGroup().addGap().addWidgets(emailLabel).addGap()
				)
				,
				emailDialogLayout.createParallelGroup
				(
					//usernameDialogLayout.createSequentialGroup().addGap().addWidgets(nameEditField).addGap(),
					emailDialogLayout.createSequentialGroup().addGap().addWidgets(emailEditField).addGap()
				)
			)
		);

		emailDialogLayout.setVerticalGroup
		(
			emailDialogLayout.createSequentialGroup
			(
				//usernameDialogLayout.createParallelGroup().addWidgets(nameLabel, nameEditField),
				emailDialogLayout.createParallelGroup().addWidgets(emailLabel, emailEditField)
			)
		);


		//---------------------------------------------------------
		//password box
		//---------------------------------------------------------

		passwordDialogLayout = new DialogLayout();
		passwordDialogLayout.setCanAcceptKeyboardFocus(false);

		passwordDialogLayout.setHorizontalGroup
		(
			passwordDialogLayout.createSequentialGroup
			(
				passwordDialogLayout.createParallelGroup
				(
					passwordDialogLayout.createSequentialGroup().addGap(),
					passwordDialogLayout.createParallelGroup().addWidgets(passwordLabel,confirmPasswordLabel),
					passwordDialogLayout.createSequentialGroup().addGap()
				)
				,
				passwordDialogLayout.createParallelGroup
				(
					passwordDialogLayout.createSequentialGroup().addGap().addWidgets(passwordEditField).addGap(),
					passwordDialogLayout.createSequentialGroup().addGap().addWidgets(confirmPasswordEditField).addGap()
				)
			)
		);

		passwordDialogLayout.setVerticalGroup
		(
			passwordDialogLayout.createSequentialGroup
			(
				passwordDialogLayout.createParallelGroup().addWidgets(passwordLabel, passwordEditField),
				passwordDialogLayout.createParallelGroup().addWidgets(confirmPasswordLabel, confirmPasswordEditField)
			)
		);







		//---------------------------------------------------------
		//ok button
		//---------------------------------------------------------
		okButton = new Button("Ok!");
		okButton.setCanAcceptKeyboardFocus(false);
		okButton.setTheme("button");
		okButton.addCallback(new Runnable()
		{
			public void run()
			{
				doCreateAccount();
			}
		});

		//---------------------------------------------------------
		//cancel button
		//---------------------------------------------------------
		cancelButton = new Button("Cancel");
		cancelButton.setCanAcceptKeyboardFocus(false);
		cancelButton.setTheme("button");
		cancelButton.addCallback(new Runnable()
		{
			public void run()
			{
				doCancel();
			}
		});


		//---------------------------------------------------------
		//layout
		//---------------------------------------------------------

		panel.setHorizontalGroup
		(
			panel.createParallelGroup
			(
					panel.createParallelGroup().addMinGap(360),

					panel.createSequentialGroup().addGap().addWidgets(createAccountPanelLabel).addGap(),
					panel.createSequentialGroup().addGap().addWidgets(errorLabel).addGap(),
					panel.createSequentialGroup().addGap().addWidgets(statusLabel).addGap(),

					panel.createParallelGroup
					(
							panel.createSequentialGroup().addGap(),
							panel.createSequentialGroup().addWidgets(emailDialogLayout),
							panel.createSequentialGroup().addWidgets(passwordDialogLayout),
							panel.createSequentialGroup().addGap()
					),

					//panel.createSequentialGroup().addGap().addWidgets(socialDialogLayout).addGap(),
					panel.createSequentialGroup().addGap().addWidgets(okButton).addGap(),
					panel.createSequentialGroup().addGap().addWidgets(cancelButton).addGap()
			)
		);



		panel.setVerticalGroup
		(
			panel.createSequentialGroup
			(
					//panel.createSequentialGroup().addGap(),
					panel.createSequentialGroup().addWidgets(createAccountPanelLabel).addGap(),
					panel.createSequentialGroup().addWidgets(errorLabel),
					panel.createSequentialGroup().addWidgets(statusLabel),
					panel.createSequentialGroup().addWidgets(emailDialogLayout),
					panel.createSequentialGroup().addWidgets(passwordDialogLayout),
					//panel.createSequentialGroup().addWidgets(socialDialogLayout),
					panel.createSequentialGroup().addWidgets(okButton),
					panel.createSequentialGroup().addWidgets(cancelButton)
					//,panel.createSequentialGroup().addGap()
			)
		);



		//---------------------------------------------------------
		//layout
		//---------------------------------------------------------

		insideScrollPaneLayout.setHorizontalGroup
		(
				insideScrollPaneLayout.createParallelGroup
				(
						insideScrollPaneLayout.createSequentialGroup().addGap().addWidget(panel).addGap()
				)
		);

		insideScrollPaneLayout.setVerticalGroup
		(
				insideScrollPaneLayout.createSequentialGroup
				(
						insideScrollPaneLayout.createSequentialGroup().addGap()
						,
						insideScrollPaneLayout.createParallelGroup().addWidget(panel)
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

		//scrollPane.setExpandContentSize(false);



		//---------------------
		//add scrollpane to outside panel
		//----------------------

		//mainPanelLayout.add(scrollPane);

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


		setActivated(true);

	}



	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================




	}


	//=========================================================================================================================
	public void setButtonsVisible(boolean b)
	{//=========================================================================================================================

		emailDialogLayout.setVisible(b);
		passwordDialogLayout.setVisible(b);
		okButton.setVisible(b);

		if(ClientMain.introMode==false)cancelButton.setVisible(b);

	}


	//=========================================================================================================================
	public void onScrolledUp()
	{//=========================================================================================================================

		emailEditField.requestKeyboardFocus();

	}



	//=========================================================================================================================
	void doCancel()
	{//=========================================================================================================================

		setActivated(false);
		setButtonsVisible(true);
		statusLabel.setText(" ");
		errorLabel.setText(" ");

	}


	//=========================================================================================================================
	void doCreateAccount()
	{//=========================================================================================================================

		GUI gui = getGUI();
		if(gui != null)
		{

			setButtonsVisible(false);


			//create thread, this needs to be a thread because Button.doCallback only creates a Runnable and calls Runnable.run() which does NOT create a thread
			new Thread
			(
				new Runnable()
				{
					public void run()
					{
						try{Thread.currentThread().setName("CreateNewAccount_doCreateAccount");}catch(SecurityException e){e.printStackTrace();}

						statusLabel.setText(" ");
						errorLabel.setText(" ");

						if(emailEditField.getText().contains("`")){errorLabel.setText("Email must not contain `");setButtonsVisible(true);return;}
						if(emailEditField.getText().length()==0){errorLabel.setText("Enter your email address.");setButtonsVisible(true);return;}
						if(emailEditField.getText().contains("@")==false){errorLabel.setText("Email address must contain @");setButtonsVisible(true);return;}

						if(passwordEditField.getText().contains("`")){errorLabel.setText("Password must not contain `");setButtonsVisible(true);return;}
						if(passwordEditField.getText().length()==0){errorLabel.setText("Please enter a password.");setButtonsVisible(true);return;}
						if(passwordEditField.getText().equals(confirmPasswordEditField.getText())==false){errorLabel.setText("Passwords do not match.");setButtonsVisible(true);return;}


						//check if email address is valid
						//may not contain `
						//make sure passwords match

						//say "trying to connect to server"

						errorLabel.setText(" ");
						statusLabel.setText("Connecting to server...");

						Network().connectToServer();

						//-------------------------------
						//check to see if connected every 1 second
						//when connected, proceed.
						//-------------------------------
						int tries = 0;
						boolean connected = false;
						while(connected==false)
						{
							connected = Network().getConnectedToServer_S();

							if(connected==false)
							{
								tries++;

								//make dots cycle
								String dots = "";
								for(int i=0;i<tries%4;i++)dots = dots.concat(".");

								errorLabel.setText(" ");
								statusLabel.setText("Connecting to server"+dots);

								if(tries>10)
								{
									tries=0;
									statusLabel.setText(" ");
									errorLabel.setText("Error: Could not connect to server.");

									setButtonsVisible(true);

									return;
								}

								try{Thread.sleep(1000);}catch(Exception e){e.printStackTrace();}
							}
						}

						if(connected==true)
						{
							errorLabel.setText(" ");
							statusLabel.setText("Connected! Creating Account...");
						}

						Network().sendCreateAccountRequest(emailEditField.getText(), passwordEditField.getText());

						//-------------------------------
						//check to see if response every 1 second
						//-------------------------------
						int createAccountTries = 0;
						boolean gotResponse = false;
						while(gotResponse==false)
						{
							gotResponse = Network().getGotCreateAccountResponse_S();

							if(gotResponse==false)
							{
								createAccountTries++;
								if(createAccountTries>10)
								{
									createAccountTries=0;
									statusLabel.setText(" ");
									errorLabel.setText("Error: Timed out creating account. The servers may be overloaded, please wait a few minutes and try again.");

									setButtonsVisible(true);

									return;
								}

								try{Thread.sleep(1000);}catch(Exception e){e.printStackTrace();}
							}
						}

						errorLabel.setText(" ");
						statusLabel.setText("Your account was created! Please check your email and confirm your account.");

						try{Thread.sleep(3000);}catch(Exception e){e.printStackTrace();}



						//setEnabled(false);
						setActivated(false);
						setButtonsVisible(true);
						//statusLabel.setText(" ");
						//errorLabel.setText(" ");



					}
				}
			).start();
		}
	}



	//=========================================================================================================================
	@Override
	protected void layout()
	{//=========================================================================================================================


		//Login panel is centered

		panel.adjustSize();

		panel.setPosition
		(
			insideScrollPaneLayout.getInnerX() + (insideScrollPaneLayout.getInnerWidth() - panel.getWidth()) / 2,
			insideScrollPaneLayout.getInnerY() + (insideScrollPaneLayout.getInnerHeight() - panel.getHeight()) / 2
		);


		super.layout();


	}


	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

		super.update();


		ClientMain.glowTileBackground.update();



		if(ClientMain.introMode)
		{
			cancelButton.setVisible(false);
			cancelButton.setEnabled(false);
		}


		if(isActivated()==false)
		if(isScrollingDown()==false)
		{
			if(ClientMain.introMode)
			{
				ClientMain.clientMain.stateManager.setState(ClientMain.clientMain.youWillBeNotifiedState);
			}
			else
			{
				ClientMain.clientMain.stateManager.setState(ClientMain.clientMain.loginState);
			}

		}


	}


	//=========================================================================================================================
	public void setActivated(boolean b)
	{//=========================================================================================================================

		if(ClientMain.introMode==true && b==false)return;
		super.setActivated(b);

	}


	//=========================================================================================================================
	public void renderBefore()
	{//=========================================================================================================================


		if(isScrollingDown()==true)return;
		if(isActivated()==false)return;
		//additional rendering calls go here (after gui is drawn)


		ClientMain.glowTileBackground.render();

	}


	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================


		if(isScrollingDown()==true)return;
		if(isActivated()==false)return;

		//additional rendering calls go here (after gui is drawn)


	}



}
