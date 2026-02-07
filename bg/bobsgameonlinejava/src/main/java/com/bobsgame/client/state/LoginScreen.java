package com.bobsgame.client.state;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.ClientMain;
import com.bobsgame.client.Cache;
import com.bobsgame.client.engine.game.gui.GUIManager;
import com.bobsgame.client.engine.game.gui.MenuPanel;

import de.matthiasmann.twl.Button;
import de.matthiasmann.twl.DialogLayout;
import de.matthiasmann.twl.EditField;
import de.matthiasmann.twl.EditField.Callback;
import de.matthiasmann.twl.Event;
import de.matthiasmann.twl.GUI;
import de.matthiasmann.twl.Label;
import de.matthiasmann.twl.ScrollPane;
import de.matthiasmann.twl.ToggleButton;


//=========================================================================================================================
public class LoginScreen extends MenuPanel
{//=========================================================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(LoginScreen.class);


	DialogLayout loginPanel;
	EditField emailEditField;
	EditField passwordEditField;
	Button loginWithFacebookButton;
	Button loginButton;
	Button createNewAccountButton;
	Button forgotPasswordButton;

	Label errorLabel;
	Label statusLabel;


	Label emailLabel;
	Label passwordLabel;

	boolean loggedIn = false;


	Label sendStatsQuestionMark;

	Label stayLoggedInToggleButtonLabel;
	final ToggleButton stayLoggedInToggleButton = new ToggleButton("");

	Label sendStatsToggleButtonLabel;
	final ToggleButton sendStatsToggleButton = new ToggleButton("");


	//=========================================================================================================================
	public LoginScreen()
	{//=========================================================================================================================

		super();




		loginPanel = new DialogLayout();
		loginPanel.setTheme("loginpanel");


		Label loginPanelLabel = new Label("Login");
		loginPanelLabel.setCanAcceptKeyboardFocus(false);
		loginPanelLabel.setTheme("bigLabel");


		errorLabel = new Label(" ");
		errorLabel.setTheme("errorLabel");
		errorLabel.setCanAcceptKeyboardFocus(false);

		statusLabel = new Label(" ");
		statusLabel.setTheme("statusLabel");
		statusLabel.setCanAcceptKeyboardFocus(false);






		//---------------------------------------------------------
		//login with facebook button
		//---------------------------------------------------------
		loginWithFacebookButton = new Button("Login using your Facebook account!");
		loginWithFacebookButton.setTheme("smallButton");
		loginWithFacebookButton.setCanAcceptKeyboardFocus(false);

		loginWithFacebookButton.addCallback(new Runnable()
		{
			public void run()
			{
				doLoginWithFacebook();
			}
		});

		if(ClientMain.isApplet==false)
		{
			loginWithFacebookButton.setVisible(false);
			loginWithFacebookButton.setEnabled(false);
		}



		//---------------------------------------------------------
		//name
		//---------------------------------------------------------
		emailEditField = new EditField();


		emailLabel = new Label("Email");
		//emailLabel.setLabelFor(emailEditField);
		emailLabel.setCanAcceptKeyboardFocus(false);


		//---------------------------------------------------------
		//password
		//---------------------------------------------------------

		passwordLabel = new Label("Password");
		//passwordLabel.setLabelFor(passwordEditField);
		passwordLabel.setCanAcceptKeyboardFocus(false);

		passwordEditField = new EditField();
		passwordEditField.setPasswordMasking(true);

		passwordEditField.addCallback(new EditField.Callback()
		{
			public void callback(int key)
			{
				if(key == Event.KEY_RETURN)
				{
					doLogin();
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
		//login
		//---------------------------------------------------------
		loginButton = new Button("Login");
		loginButton.setCanAcceptKeyboardFocus(false);
		loginButton.addCallback(new Runnable()
		{
			public void run()
			{
				doLogin();
			}
		});

		//---------------------------------------------------------
		//forgot pass
		//---------------------------------------------------------
		forgotPasswordButton = new Button("Forgot Password?");
		forgotPasswordButton.setCanAcceptKeyboardFocus(false);
		forgotPasswordButton.setTheme("textButton");
		forgotPasswordButton.addCallback(new Runnable()
		{
			public void run()
			{
				doForgotPassword();
			}
		});

		//---------------------------------------------------------
		//create new account
		//---------------------------------------------------------
		createNewAccountButton = new Button("Create Account");
		createNewAccountButton.setCanAcceptKeyboardFocus(false);
		createNewAccountButton.addCallback(new Runnable()
		{
			public void run()
			{
				doCreateNewAccount();
			}
		});



		//---------------------------------------------------------
		//stay logged in
		//---------------------------------------------------------
		stayLoggedInToggleButton.setTheme(GUIManager.checkboxTheme);
		stayLoggedInToggleButton.setCanAcceptKeyboardFocus(false);
		stayLoggedInToggleButton.setActive(true);

//		stayLoggedInToggleButton.addCallback(new Runnable()
//		{
//			public void run()
//			{
//
//			}
//		});

		stayLoggedInToggleButtonLabel = new Label("Stay Logged In");
		stayLoggedInToggleButtonLabel.setCanAcceptKeyboardFocus(false);
		stayLoggedInToggleButtonLabel.setLabelFor(stayLoggedInToggleButton);

		//---------------------------------------------------------
		//send stats
		//---------------------------------------------------------
		sendStatsToggleButton.setTheme(GUIManager.checkboxTheme);
		sendStatsToggleButton.setCanAcceptKeyboardFocus(false);
		sendStatsToggleButton.setActive(true);

//		sendStatsToggleButton.addCallback(new Runnable()
//		{
//			public void run()
//			{
//
//			}
//		});

		sendStatsToggleButtonLabel = new Label("Send PC Stats");
		sendStatsToggleButtonLabel.setCanAcceptKeyboardFocus(false);
		sendStatsToggleButtonLabel.setLabelFor(sendStatsToggleButton);

		sendStatsQuestionMark = new Label(" ? ");
		sendStatsQuestionMark.setCanAcceptKeyboardFocus(false);
		sendStatsQuestionMark.setTheme("descriptionLabel");
		sendStatsQuestionMark.setTooltipContent("");



		//DialogLayout.Group hLabels = loginPanel.createParallelGroup(nameLabel,passwordLabel);
		//DialogLayout.Group hFields = loginPanel.createParallelGroup(nameEditField,passwordEditField);
		//DialogLayout.Group hBtn = loginPanel.createSequentialGroup().addGap().addWidget(loginButton) ;// right align the button by using a variable gap



		loginPanel.setHorizontalGroup(

											loginPanel.createParallelGroup
											(
													loginPanel.createParallelGroup().addMinGap(400)
													,
													loginPanel.createSequentialGroup().addGap().addWidget(errorLabel).addGap()
													,
													loginPanel.createSequentialGroup().addGap().addWidget(statusLabel).addGap()
													,
													loginPanel.createSequentialGroup
													(
														loginPanel.createParallelGroup().addMinGap(50)
														,
														loginPanel.createParallelGroup
														(

															loginPanel.createSequentialGroup().addGap().addWidget(loginPanelLabel).addGap()
															,
															loginPanel.createSequentialGroup().addGap().addWidget(loginWithFacebookButton).addGap()
															,
															loginPanel.createSequentialGroup
															(
																	loginPanel.createParallelGroup().addWidgets(emailLabel,passwordLabel)
																	,
																	loginPanel.createParallelGroup().addWidgets(emailEditField,passwordEditField)
															)
															,
															loginPanel.createSequentialGroup().addGap().addWidget(forgotPasswordButton).addGap().addWidget(loginButton)
															,
															loginPanel.createSequentialGroup().addGap().addWidgets(stayLoggedInToggleButtonLabel,stayLoggedInToggleButton)
															,
															loginPanel.createSequentialGroup().addGap().addWidgets(sendStatsToggleButtonLabel,sendStatsQuestionMark,sendStatsToggleButton)
															,
															loginPanel.createSequentialGroup().addGap().addWidget(createNewAccountButton).addGap()
														)
														,
														loginPanel.createParallelGroup().addMinGap(50)
													)
											)
										);


		loginPanel.setVerticalGroup(
											loginPanel.createSequentialGroup
											(
												loginPanel.createSequentialGroup().addMinGap(20),

												loginPanel.createParallelGroup(loginPanelLabel)
												,
												loginPanel.createSequentialGroup().addMinGap(20)
												,
												loginPanel.createParallelGroup(errorLabel)
												,
												loginPanel.createParallelGroup(statusLabel)
												,
												loginPanel.createSequentialGroup().addMinGap(10)
												,
												loginPanel.createParallelGroup(loginWithFacebookButton)
												,
												loginPanel.createSequentialGroup().addMinGap(10)
												,
												loginPanel.createParallelGroup(emailLabel, emailEditField)
												,
												loginPanel.createParallelGroup(passwordLabel,passwordEditField)
												,
												loginPanel.createParallelGroup(forgotPasswordButton, loginButton)
												,
												loginPanel.createSequentialGroup().addMinGap(10)
												,
												loginPanel.createParallelGroup(stayLoggedInToggleButtonLabel, stayLoggedInToggleButton)
												,
												loginPanel.createParallelGroup(sendStatsToggleButtonLabel,sendStatsQuestionMark,sendStatsToggleButton)
												,
												loginPanel.createSequentialGroup().addMinGap(20)
												,
												loginPanel.createParallelGroup(createNewAccountButton)
												,
												loginPanel.createSequentialGroup().addMinGap(50)
											)
									);




		//---------------------------------------------------------
		//layout
		//---------------------------------------------------------

		insideScrollPaneLayout.setHorizontalGroup
		(
				insideScrollPaneLayout.createParallelGroup
				(
						insideScrollPaneLayout.createSequentialGroup().addGap().addWidget(loginPanel).addGap()
				)
		);

		insideScrollPaneLayout.setVerticalGroup
		(
				insideScrollPaneLayout.createSequentialGroup
				(
						insideScrollPaneLayout.createSequentialGroup().addGap()
						,
						insideScrollPaneLayout.createParallelGroup().addWidget(loginPanel)
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




		loginPanel.adjustSize();


		setActivated(true);



	}

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================
		super.update();


		if(loggedIn==true)
		{
			if(isActivated()==false)
				if(isScrollingDown()==false)
					ClientMain.clientMain.stateManager.setState(ClientMain.clientMain.clientGameEngine);
		}

		ClientMain.glowTileBackground.update();


	}


	//=========================================================================================================================
	public void onScrolledUp()
	{//=========================================================================================================================

		getGUI().setTooltipDelay(1);

		sendStatsQuestionMark.setTooltipContent(ClientMain.clientMain.clientInfo.printString());


		emailEditField.requestKeyboardFocus();

		checkForSessionTokenAndLogInIfExists();


	}



	//=========================================================================================================================
	@Override
	protected void layout()
	{//=========================================================================================================================

		//login panel is centered

		loginPanel.adjustSize();
		loginPanel.setPosition(
				insideScrollPaneLayout.getInnerX() + (insideScrollPaneLayout.getInnerWidth() - loginPanel.getWidth()) / 2,
				insideScrollPaneLayout.getInnerY() + (insideScrollPaneLayout.getInnerHeight() - loginPanel.getHeight()) / 2);

		super.layout();
	}

	//=========================================================================================================================
	public void setButtonsVisible(boolean b)
	{//=========================================================================================================================

		emailEditField.setVisible(b);
		passwordEditField.setVisible(b);
		loginButton.setVisible(b);
		createNewAccountButton.setVisible(b);
		forgotPasswordButton.setVisible(b);
		emailLabel.setVisible(b);
		passwordLabel.setVisible(b);
		stayLoggedInToggleButton.setVisible(b);
		stayLoggedInToggleButtonLabel.setVisible(b);
		sendStatsToggleButton.setVisible(b);
		sendStatsToggleButtonLabel.setVisible(b);
		sendStatsQuestionMark.setVisible(b);

		if(ClientMain.isApplet==true)
		{
			loginWithFacebookButton.setVisible(b);
		}

	}



	//=========================================================================================================================
	void doLoginWithFacebook()
	{//=========================================================================================================================


		new Thread //needs to be a thread because Button.doCallback only calls Runnable.run() which does NOT create a thread
		(
			new Runnable()
			{
				public void run()
				{

					try{Thread.currentThread().setName("PlayerEditMenu_linkFacebookAccount");}catch(SecurityException e){e.printStackTrace();}


					errorLabel.setText(" ");
					statusLabel.setText(" ");


					setButtonsVisible(false);



					//if we are an applet we are here




					//connect through JSObject and get these from browser
                    // Removed JSObject code
					/*if(ClientMain.browser!=null)
					{
						ClientMain.browser.eval("loginWithFacebook();");
					}*/


					//this will use the Facebook JS SDK to open an OAuth dialog
					//if they authorize, it calls the function ClientMain.setFacebookCredentials(String facebookID, String accessToken)

					//so we need to wait until that gets filled in


					int responseTries = 0;
					boolean gotResponse = false;
					while(gotResponse==false)
					{
						gotResponse = ClientMain.getGotFacebookResponse_S();

						if(gotResponse==false)
						{
							responseTries++;
							if(responseTries>10)
							{
								responseTries=0;
								statusLabel.setText(" ");
								errorLabel.setText("Error: Did not receive a response from the Facebook OAuth dialog.");

								setButtonsVisible(true);

								return;
							}

							try{Thread.sleep(1000);}catch (Exception e){e.printStackTrace();}
						}
					}

					String facebookID = ClientMain.facebookID;
					String accessToken = ClientMain.facebookAccessToken;


					if(facebookID.equals("cancelled"))
					{
						statusLabel.setText(" ");
						errorLabel.setText("Cancelled Facebook authorization?");

						setButtonsVisible(true);

						return;
					}


					//ask server to check database for facebook ID
					//if they already have an account, log them in. (set cookie, set session token file)
					//if not we insert a new account into the database based on facebookID and then send them a bobsgame account password to their email.
					//we'll assume the email address is valid because it's already verified with facebook so set verified to true and log them in.
					//also initialize facebook friends

					Network().sendFacebookLoginCreateAccountIfNotExist(facebookID,accessToken,sendStatsToggleButton.isActive());


					//this will send back a facebookLoginResponse
					statusLabel.setText("Logging in with Facebook...");
					errorLabel.setText("");


					//-------------------------------
					//check to see if password response every 1 second
					//-------------------------------
					int passwordTries = 0;
					gotResponse = false;
					while(gotResponse==false)
					{
						gotResponse = Network().getGotFacebookLoginResponse_S();

						if(gotResponse==false)
						{
							passwordTries++;
							if(passwordTries>10)
							{
								passwordTries=0;

								statusLabel.setText("Timed out. Trying again...");
								errorLabel.setText("");


								Network().sendFacebookLoginCreateAccountIfNotExist(facebookID,accessToken,sendStatsToggleButton.isActive());

							}

							try{Thread.sleep(1000);}catch (Exception e){e.printStackTrace();}
						}
					}


					//we have the response, now lets see if it was a valid login (two steps)
					boolean passValid = Network().getWasFacebookLoginResponseValid_S();

					//reset the response state in case we need to try again
					Network().setGotFacebookLoginResponse_S(false);

					if(passValid)
					{

						errorLabel.setText(" ");
						statusLabel.setText("Login successful!");

						try{Thread.sleep(1000);}catch (Exception e){e.printStackTrace();}




						//-------------------------------------------------------
						if(ClientMain.isApplet==true)
						{
							Cache.writeBrowserSessionCookieAndRefreshIFrame();
						}


						if(stayLoggedInToggleButton.isActive())
						{

							if(ClientMain.isApplet==true)
							{
								Cache.writeBrowserSessionCookieAndRefreshIFrame();
							}

							ClientMain.cacheManager.writeSessionTokenToCache(Network().getUserID_S(), Network().getSessionToken_S(), sendStatsToggleButton.isActive());
							//String temp = ClientMain.cacheManager.readSessionTokenFromCache();
							//log.debug("Read session: "+temp);
							//ClientMain.cacheManager.deleteSessionTokenFromCache();
							//temp = ClientMain.cacheManager.readSessionTokenFromCache();
							//log.debug("Deleted session: "+temp);
						}

						//-------------------------------------------------------

						setActivated(false);
						loggedIn=true;

					}
					else
					{

						//-------------------------------------------------------
						if(ClientMain.isApplet==true)
						{
							Cache.deleteBrowserSessionCookieAndRefreshIFrame();
						}

						//delete session cookie if there is one
						ClientMain.cacheManager.deleteSessionTokenFromCache();

						//-------------------------------------------------------

						statusLabel.setText(" ");
						errorLabel.setText("Something went wrong, and I have no idea why! I'll check it out.\nIf you have played before, try logging in with your email/password. If not, create an account.");

						try{Thread.sleep(2000);}catch (Exception e){e.printStackTrace();}

						setButtonsVisible(true);

						return;
					}


					Network().sendOnlineFriendListRequest();


					statusLabel.setText(" ");
					errorLabel.setText(" ");

					setButtonsVisible(true);


				}
			}
		).start();


	}




	//=========================================================================================================================
	void doCreateNewAccount()
	{//=========================================================================================================================
		ClientMain.clientMain.stateManager.setState(ClientMain.clientMain.createNewAccountState);
		ClientMain.clientMain.createNewAccountState.createNewAccount.setActivated(true);

	}



	//=========================================================================================================================
	void doForgotPassword()
	{//=========================================================================================================================
		//send forgot password request to server, wait for response


		GUI gui = getGUI();
		if(gui != null)
		{
			setButtonsVisible(false);

			//create thread, this needs to be a thread because Button.doCallback(Runnable) only calls Runnable.run() which does NOT create a thread.
			new Thread
			(
				new Runnable()
				{
					public void run()
					{

						try{Thread.currentThread().setName("LoginScreen_doForgotPassword");}catch(SecurityException e){e.printStackTrace();}

						statusLabel.setText(" ");
						errorLabel.setText(" ");

						if(emailEditField.getText().contains("`")){errorLabel.setText("Email must not contain `");setButtonsVisible(true);return;}
						if(emailEditField.getText().length()==0){errorLabel.setText("Enter your email address.");setButtonsVisible(true);return;}
						if(emailEditField.getText().contains("@")==false){errorLabel.setText("Email address must contain @");setButtonsVisible(true);return;}

						//if(passwordEditField.getText().contains("`")){errorLabel.setText("Password must not contain `");setButtonsVisible(true);return;}
						//if(passwordEditField.getText().length()==0){errorLabel.setText("Please enter a password.");setButtonsVisible(true);return;}


						//if email address blank, say "please type email address"
						//if password is blank, say "must type password"
						//check if email address is valid
						//may not contain `

						//say "trying to connect to server"
						errorLabel.setText(" ");
						statusLabel.setText("Connecting to server...");

						boolean connected = Network().getConnectedToServer_S();

						if(connected==false)
						{
							Network().connectToServer();

							//-------------------------------
							//check to see if connected every 1 second
							//when connected, proceed.
							//-------------------------------
							int tries = 0;
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
										errorLabel.setText(" ");
										statusLabel.setText("Error: Could not connect to server.");

										setButtonsVisible(true);

										return;
									}

									try{Thread.sleep(1000);}catch (Exception e){e.printStackTrace();}
								}
							}
						}

						if(connected==true)
						{
							errorLabel.setText(" ");
							statusLabel.setText("Connected! Sending account recovery request...");
						}

						Network().sendPasswordRecoveryRequest(emailEditField.getText());

						//-------------------------------
						//check to see if password response every 1 second
						//-------------------------------
						int passwordTries = 0;
						boolean gotResponse = false;
						while(gotResponse==false)
						{
							gotResponse = Network().getGotPasswordRecoveryResponse_S();

							if(gotResponse==false)
							{
								passwordTries++;
								if(passwordTries>10)
								{
									passwordTries=0;
									statusLabel.setText(" ");
									errorLabel.setText("Error: Timed out sending request. Please try again.");

									setButtonsVisible(true);

									return;
								}

								try{Thread.sleep(1000);}catch (Exception e){e.printStackTrace();}
							}
						}

						//reset the response state in case we need to try again
						Network().setGotPasswordRecoveryResponse_S(false);

						//say "an email was sent if the account was registered"
						errorLabel.setText(" ");
						statusLabel.setText("If the account exists, a recovery email was sent. Please check your email.");

						try{Thread.sleep(3000);}catch (Exception e){e.printStackTrace();}

						setButtonsVisible(true);

					}
				}
			).start();
		}

	}



	//=========================================================================================================================
	void doLogin()
	{//=========================================================================================================================
		GUI gui = getGUI();
		if(gui != null)
		{
			setButtonsVisible(false);

			//create thread, needs to be a thread because Button.doCallback only calls Runnable.run() which does NOT create a thread
			new Thread
			(
				new Runnable()
				{
					public void run()
					{

						try{Thread.currentThread().setName("LoginScreen_doLogin");}catch(SecurityException e){e.printStackTrace();}

						statusLabel.setText(" ");
						errorLabel.setText(" ");

						if(emailEditField.getText().contains("`")){errorLabel.setText("Email must not contain `");setButtonsVisible(true);return;}
						if(emailEditField.getText().length()==0){errorLabel.setText("Enter your email address.");setButtonsVisible(true);return;}
						if(emailEditField.getText().contains("@")==false){errorLabel.setText("Email address must contain @");setButtonsVisible(true);return;}

						if(passwordEditField.getText().contains("`")){errorLabel.setText("Password must not contain `");setButtonsVisible(true);return;}
						if(passwordEditField.getText().length()==0){errorLabel.setText("Please enter a password.");setButtonsVisible(true);return;}

						//if email address blank, say "please type email address"
						//if password is blank, say "must type password"
						//check if email address is valid
						//may not contain `

						//say "trying to connect to server"

						errorLabel.setText(" ");
						statusLabel.setText("Connecting to server...");

						boolean connected = Network().getConnectedToServer_S();

						if(connected==false)
						{
							Network().connectToServer();

							//-------------------------------
							//check to see if connected every 1 second
							//when connected, proceed.
							//-------------------------------
							int tries = 0;
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

									try{Thread.sleep(1000);}catch (Exception e){e.printStackTrace();}
								}
							}
						}

						if(connected==true)
						{
							errorLabel.setText(" ");
							statusLabel.setText("Connected! Checking login...");
						}

						Network().sendLoginRequest(emailEditField.getText(), passwordEditField.getText(), sendStatsToggleButton.isActive());

						//-------------------------------
						//check to see if password response every 1 second
						//-------------------------------
						int passwordTries = 0;
						boolean gotResponse = false;
						while(gotResponse==false)
						{
							gotResponse = Network().getGotLoginResponse_S();

							if(gotResponse==false)
							{
								passwordTries++;
								if(passwordTries>10)
								{
									passwordTries=0;
									statusLabel.setText(" ");
									errorLabel.setText("Error: Timed out validating password. Please try again.");

									setButtonsVisible(true);

									return;
								}

								try{Thread.sleep(1000);}catch (Exception e){e.printStackTrace();}
							}
						}

						//we have the response, now lets see if it was a valid login (two steps)
						boolean passValid = Network().getWasLoginResponseValid_S();

						//reset the response state in case we need to try again
						Network().setGotLoginResponse_S(false);

						if(passValid)
						{

							errorLabel.setText(" ");
							statusLabel.setText("Login successful!");

							try{Thread.sleep(1000);}catch (Exception e){e.printStackTrace();}




							//-------------------------------------------------------
							if(ClientMain.isApplet==true)
							{
								//TODO: write session cookie, refresh iFrame
							}


							if(stayLoggedInToggleButton.isActive())
							{

								if(ClientMain.isApplet==true)
								{
									//TODO: write browser cookie
								}

								ClientMain.cacheManager.writeSessionTokenToCache(Network().getUserID_S(), Network().getSessionToken_S(), sendStatsToggleButton.isActive());
								//String temp = ClientMain.cacheManager.readSessionTokenFromCache();
								//log.debug("Read session: "+temp);
								//ClientMain.cacheManager.deleteSessionTokenFromCache();
								//temp = ClientMain.cacheManager.readSessionTokenFromCache();
								//log.debug("Deleted session: "+temp);
							}

							//-------------------------------------------------------



							//setEnabled(false);
							setActivated(false);
							loggedIn=true;

						}
						else
						{

							//-------------------------------------------------------

							if(ClientMain.isApplet==true)
							{
								//TODO: delete browser cookie, refresh iframe
							}

							//delete session cookie if there is one
							ClientMain.cacheManager.deleteSessionTokenFromCache();


							//-------------------------------------------------------


							//say "password wrong or account doesn't exist"
							statusLabel.setText(" ");
							errorLabel.setText("Error: Password incorrect, account doesn't exist, or account isn't verified yet.\n If you just signed up, please check your email and click the verification link.");

							try{Thread.sleep(2000);}catch (Exception e){e.printStackTrace();}

							setButtonsVisible(true);

							return;
						}
					}
				}
			).start();
		}
	}


	//TODO: write these to a cookie and an applet ini if the user wants to remain logged in.

	//if we are running as an application, we should use the Preferences API or write a file to the cache dir



	//if we are running as an applet
	//browser cookies are only accessible through JSObject

	//we can use the JNLP PersistenceService

	//or use CookieManager to send an URL request and set and read cookies sent from the server (this only stays in memory in application, in applet it uses browser CookieStore)
	//it might be possible to read the browser cookies using this, i'm not sure.

	//it also may write browser cookies as an applet, because it uses the browser cookieStore, using this:
	//URLConnection conn = url.openConnection();
	//conn.setRequestProperty("cookie", cookie_val);


	//or get the cookies from the browser with JSObject
	//or pass the session in through params to the applet using JS or PHP
	//...or sign the applet and use the same as the application

	//applet login should set a browser cookie, can do this through JSObject or maybe through CookieManager? check this.





	//=========================================================================================================================
	public void checkForSessionTokenAndLogInIfExists()
	{//=========================================================================================================================


		if(ClientMain.isApplet==true)
		{
			//TODO: check for browser cookie, session or permanent
		}


		//check cache for session token
		//if session token cache exists, try to log in with that.
		//set browser cookie, refresh iframe

		log.debug("Checking for Session Token");

		final String token = ClientMain.cacheManager.readSessionTokenFromCache();

		if(token!=null)log.debug("Session Token Found");
		else log.debug("Session Token not found in cache.");

		if(token!=null)
		{

			GUI gui = getGUI();
			if(gui != null)
			{
				setButtonsVisible(false);

				//create thread
				new Thread
				(
					new Runnable()
					{
						public void run()
						{

							try{Thread.currentThread().setName("LoginScreen_checkForSessionTokenAndLogInIfExists");}catch(SecurityException e){e.printStackTrace();}

							//token = userId,`sessionToken`,statsAllowed
							String s = token;

							int userID = -1;
							try{userID = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
							s = s.substring(s.indexOf("`")+1);//sessionToken`,statsAllowed
							String sessionToken = s.substring(0,s.indexOf("`"));
							s = s.substring(s.indexOf(",")+1);//statsAllowed
							boolean statsAllowed = Boolean.parseBoolean(s);


							errorLabel.setText(" ");
							statusLabel.setText("Existing session found! Connecting to server...");

							boolean connected = Network().getConnectedToServer_S();

							if(connected==false)
							{
								Network().connectToServer();

								//-------------------------------
								//check to see if connected every 1 second
								//when connected, proceed.
								//-------------------------------
								int tries = 0;
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
										statusLabel.setText("Existing session found! Connecting to server"+dots);

										if(tries>10)
										{
											tries=0;
											statusLabel.setText(" ");
											errorLabel.setText("Error: Could not connect to server.");

											setButtonsVisible(true);

											return;
										}

										try{Thread.sleep(1000);}catch (Exception e){e.printStackTrace();}
									}
								}
							}

							if(connected==true)
							{
								errorLabel.setText(" ");
								statusLabel.setText("Connected! Checking session...");
							}

							Network().sendReconnectRequest(userID,sessionToken,statsAllowed);

							//-------------------------------
							//check to see if password response every 1 second
							//-------------------------------
							int passwordTries = 0;
							boolean gotResponse = false;
							while(gotResponse==false)
							{
								gotResponse = Network().getGotReconnectResponse_S();

								if(gotResponse==false)
								{
									passwordTries++;
									if(passwordTries>10)
									{
										passwordTries=0;
										statusLabel.setText(" ");
										errorLabel.setText("Error: Timed out validating session. Please try again.");

										setButtonsVisible(true);

										return;
									}

									try{Thread.sleep(1000);}catch (Exception e){e.printStackTrace();}
								}
							}

							//we have the response, now lets see if it was a valid login (two steps)
							boolean passValid = Network().getWasReconnectResponseValid_S();

							//reset the response state in case we need to try again
							Network().setGotReconnectResponse_S(false);

							if(passValid)
							{

								errorLabel.setText(" ");
								statusLabel.setText("Login successful!");

								try{Thread.sleep(1000);}catch (Exception e){e.printStackTrace();}


								//-------------------------------------------------------

								if(ClientMain.isApplet==true)
								{
									//TODO: write session cookie, refresh iFrame
									//TODO: write browser cookie

								}


								//-------------------------------------------------------

								//setEnabled(false);
								setActivated(false);
								loggedIn=true;

							}
							else
							{


								//-------------------------------------------------------
								if(ClientMain.isApplet==true)
								{
									//TODO: delete browser cookie, refresh iframe
								}

								//delete session cookie if there is one
								ClientMain.cacheManager.deleteSessionTokenFromCache();

								//-------------------------------------------------------





								statusLabel.setText(" ");
								errorLabel.setText("Error: Session was not valid. Please log in.");

								try{Thread.sleep(2000);}catch (Exception e){e.printStackTrace();}

								setButtonsVisible(true);

								return;
							}


						}
					}
				).start();
			}

		}

	}



	//=========================================================================================================================
	public void showStatsDialogue()
	{//=========================================================================================================================


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
