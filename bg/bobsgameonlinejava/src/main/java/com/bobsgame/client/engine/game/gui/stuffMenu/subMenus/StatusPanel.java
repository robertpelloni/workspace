package com.bobsgame.client.engine.game.gui.stuffMenu.subMenus;

import java.net.MalformedURLException;
import java.net.URL;
import java.sql.Date;
import java.text.SimpleDateFormat;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.ClientMain;
import com.bobsgame.client.engine.game.gui.stuffMenu.SubPanel;

import de.matthiasmann.twl.Button;
import de.matthiasmann.twl.DialogLayout;
import de.matthiasmann.twl.Label;


//=========================================================================================================================
public class StatusPanel extends SubPanel
{//=========================================================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(StatusPanel.class);

/*

	public int userID=-1;
	public String emailAddress = "";
	public String passwordHash = "";
	public int accountVerified = 0;
	public String verificationHash = "";
	public long lastPasswordResetTime = 0;
	public long accountCreatedTime = 0;
	public long accountVerifiedTime = 0;
	public long firstLoginTime = 0;
	public long lastLoginTime = 0;
	public long lastLoginTime = 0;
	public int timesLoggedIn = 0;
	public String firstIP = "";
	public String lastIP = "";
	public String realName = "";
	public long birthdayTime = 0;
	public String facebookID = "";
	public String facebookAccessToken = "";
	public String facebookEmail = "";
	public String facebookBirthday = "";
	public String facebookFirstName = "";
	public String facebookLastName = "";
	public String facebookGender = "";
	public String facebookLocale = "";
	public Float facebookTimeZone = 0.0f;
	public String facebookUsername = "";
	public String facebookWebsite = "";

	public String googlePlusID = "";
	public String postalCode = "";
	public String countryName = "";
	public String isoCountryCode = "";
	public String placeName = "";
	public String stateName = "";
	public float lat = 0;
	public float lon = 0;
	public int timeZone = 0;
	public String notes = "";
	public String warnings = "";
	public String avatarIcon = "";
	public String lastKnownRoom = "";
	public int lastKnownX = 0;
	public int lastKnownY = 0;
	public String startingRoom = "";
	public long timePlayed = 0;
	public long pixelsWalked = 0;
	public int money = 0;
	public int moneyPurchased = 0;
	public int realWorldTransactions = 0;
	public int inGameTransactions = 0;
	public int timesTalkedToNPCs = 0;
	public int timesTalkedToOtherPlayers = 0;
	public String characterAppearance = "";
	public String characterName = "";
	public String itemsHeld = "";
	public String itemsTotalCollected = "";
	public String itemsPurchased = "";
*/

	Button editCharacterButton = null;


	Label moneyDescriptionLabel = null;
	Label moneyLabel = null;
	Button addMoneyButton = null;
	Label addMoneyButtonQuestionMark = null;

	Label accountRankDescriptionLabel = null;
	Label accountRankLabel = null;
	Button goPremiumButton = null;
	Label goPremiumButtonQuestionMark = null;




	//public String characterName = "";
	Label characterNameDescriptionLabel = null;
	Label characterNameLabel = null;



	DialogLayout accountDialogLayout;
	Label accountPanelLabel;


	//public String emailAddress = "";
	Label emailAddressDescriptionLabel = null;
	Label emailAddressLabel = null;


	//public long accountCreatedTime = 0;
	Label accountCreatedTimeDescriptionLabel = null;
	Label accountCreatedTimeLabel = null;


	//public long lastLoginTime = 0;
	Label lastLoginTimeDescriptionLabel = null;
	Label lastLoginTimeLabel = null;


	//public int timesLoggedIn = 0;
	Label timesLoggedInDescriptionLabel = null;
	Label timesLoggedInLabel = null;


	//public String lastIP = "";
	Label lastIPDescriptionLabel = null;
	Label lastIPLabel = null;


	//public String realName = "";
	//Label realNameDescriptionLabel = null;
	//Label realNameLabel = null;


	//public long birthdayTime = 0;
	//Label birthdayTimeDescriptionLabel = null;
	//Label birthdayTimeLabel = null;





	DialogLayout facebookDialogLayout;
	Label facebookPanelLabel;

	//public String facebookEmail = "";
	Label facebookEmailDescriptionLabel = null;
	Label facebookEmailLabel = null;


	//public String facebookBirthday = "";
	//Label facebookBirthdayDescriptionLabel = null;
	//Label facebookBirthdayLabel = null;


	//public String facebookFirstName = "";
	Label facebookFirstNameDescriptionLabel = null;
	Label facebookFirstNameLabel = null;


	//public String facebookLastName = "";
	Label facebookLastNameDescriptionLabel = null;
	Label facebookLastNameLabel = null;


	//public String facebookGender = "";
	Label facebookGenderDescriptionLabel = null;
	Label facebookGenderLabel = null;


	//public String facebookLocale = "";
	//Label facebookLocaleDescriptionLabel = null;
	//Label facebookLocaleLabel = null;


	//public Float facebookTimeZone = 0.0f;
	//Label facebookTimeZoneDescriptionLabel = null;
	//Label facebookTimeZoneLabel = null;


	//public String facebookUsername = "";
	//Label facebookUsernameDescriptionLabel = null;
	//Label facebookUsernameLabel = null;


	//public String facebookWebsite = "";
	//Label facebookWebsiteDescriptionLabel = null;
	//Label facebookWebsiteLabel = null;







	DialogLayout locationDialogLayout;
	Label locationPanelLabel;

	//public String postalCode = "";
	Label postalCodeDescriptionLabel = null;
	Label postalCodeLabel = null;

	//public String countryName = "";
	Label countryNameDescriptionLabel = null;
	Label countryNameLabel = null;

	//public String isoCountryCode = "";
	Label isoCountryCodeDescriptionLabel = null;
	Label isoCountryCodeLabel = null;

	//public String placeName = "";
	Label placeNameDescriptionLabel = null;
	Label placeNameLabel = null;


	//public String stateName = "";
	Label stateNameDescriptionLabel = null;
	Label stateNameLabel = null;


	//public float lat = 0;
	Label latDescriptionLabel = null;
	Label latLabel = null;

	//public float lon = 0;
	Label lonDescriptionLabel = null;
	Label lonLabel = null;

	//public int timeZone = 0;
	Label timeZoneDescriptionLabel = null;
	Label timeZoneLabel = null;







	//Label playerFacebookNameDescriptionLabel = null;
	//Label playerFacebookNameLabel = null;

	//Label playerGooglePlusNameDescriptionLabel = null;
	//Label playerGooglePlusNameLabel = null;

	//Label playerTwitterNameDescriptionLabel = null;
	//Label playerTwitterNameLabel = null;


	//Label totalTimePlayedDescriptionLabel = null;
	//Label totalTimePlayedLabel = null;

	//Label sessionTimePlayedDescriptionLabel = null;
	//Label sessionTimePlayedLabel = null;

	//Label averageTimePlayedDescriptionLabel = null;
	//Label averageTimePlayedLabel = null;

	//Label gamesPurchasedDescriptionLabel = null;
	//Label gamesPurchasedLabel = null;

	//Label gamesSoldDescriptionLabel = null;
	//Label gamesSoldLabel = null;

	//Label friendsInGameDescriptionLabel = null;
	//Label friendsInGameLabel = null;

	//Label totalGamesPlayedDescriptionLabel = null;
	//Label totalGamesPlayedLabel = null;

	//Label timesChallengedDescriptionLabel = null;
	//Label timesChallengedLabel = null;

	//Label timesChallengerDescriptionLabel = null;
	//Label timesChallengerLabel = null;

	//Label timesWonDescriptionLabel = null;
	//Label timesWonLabel = null;

	//Label timesLostDescriptionLabel = null;
	//Label timesLostLabel = null;

	//Label betsWonDescriptionLabel = null;
	//Label betsWonLabel= null;

	//Label betsLostDescriptionLabel = null;
	//Label betsLostLabel = null;

	//Label pointsEarnedDescriptionLabel = null;
	//Label pointsEarnedLabel = null;

	//Label globalRankingDescriptionLabel = null;
	//Label globalRankingLabel = null;

	//Label regionalRankingDescriptionLabel = null;
	//Label regionalRankingLabel = null;

	//Label stepsWalkedDescriptionLabel = null;
	//Label stepsWalkedLabel= null;

	//Label buttonsPushedDescriptionLabel = null;
	//Label buttonsPushedLabel = null;



	//=========================================================================================================================
	public StatusPanel()
	{//=========================================================================================================================

		super();

		Label statusPanelLabel = new Label("Status");
		statusPanelLabel.setCanAcceptKeyboardFocus(false);
		statusPanelLabel.setTheme("bigLabel");


		//final GameEngine game = (GameEngine) g;



		String moneyToolTip = "";
//				"Support \"bob\" ( That's me! ) by adding BobCoin$ to your account to buy more nD minigames and other stuff! (Coming Soon!)\n" +
//				"\n"+
//				"The games you buy can be played by your friends, even if they don't own them!\n" +
//				"Plus, they're really cheap, and you can use them for bonuses in various places in the game.\n" +
//				"\n"+
//				"Have no money? ( That's OK, me too! ) Don't worry, you don't have to buy anything!!\n" +
//				"You can compete in minigame bets and earn money through various tasks.\n"+
//				"\n"+
//				"Hate \"bob?\" and REFUSE to give him a SINGLE RED BOBCOIN?! ( That's OK, me too! )\n"+
//				"The best revenge is to keep playing and tell everyone how terrible the game is so they come and play too!\n"+
//				"All that grinding will swamp my servers and cost me tons of money, leaving me destitute and homeless- just like I always wanted!\n" +
//				"It's win-win all around!"
//				;

		moneyDescriptionLabel = new Label("BobCoin$: ");
		moneyDescriptionLabel.setCanAcceptKeyboardFocus(false);
		moneyDescriptionLabel.setTheme("descriptionLabel");
		moneyLabel = new Label(" ");
		moneyLabel.setCanAcceptKeyboardFocus(false);
		moneyLabel.setTheme("valueLabel");

		addMoneyButton = new Button("Support \"bob!\" - Add BobCoin$");
		addMoneyButton.setCanAcceptKeyboardFocus(false);
		addMoneyButton.setTheme("smallButton");
		//addMoneyButton.setTooltipContent(moneyToolTip);
		addMoneyButton.addCallback(new Runnable()
		{
			public void run()
			{
				doAddMoneyButton();

			}
		});


		addMoneyButtonQuestionMark = new Label("?!");
		addMoneyButtonQuestionMark.setCanAcceptKeyboardFocus(false);
		addMoneyButtonQuestionMark.setTheme("bigLabel");
		addMoneyButtonQuestionMark.setTooltipContent(moneyToolTip);
		//--------



		String accountToolTip =
				"Support \"bob\" with a BobPass for a one-time price of $12 a year.\n" +
				"\n"+
				//"   - Bonus BobCoin$ Added To Your Account (Why the heck not!)\n" +
				"   - Avatar Vanity Plate* (Make everyone else jealous- the spice of life!)\n" +
				"   - More Friends* - (Make my servers explode!)\n" +
				"   - Forum Membership* - (Come and spew hatred where I could read it and ruin my day!)\n" +
				"   - Bug Reports* - (See how much crap I have to fix! Pay to do work for me!)\n" +
				"   - Beta Minigames* - (Play em' before they work!)\n" +
				"   - Make A Custom Avatar - Coming Soon!\n" +
				"   - Design And Script Your House - Coming Soon!\n" +
				"   - Whatever else I come up with!\n"+
				"\n"+
				"Plus, I'll think you're really cool, and my intense psychic energy will \n" +
				"resonate in the collective subconscious, improving your life telepathically!**\n" +
				"\n"+
				"\n"+
				"*Features will be rolled out shortly!\n"+
				"**Results may vary."
				;
		accountRankDescriptionLabel = new Label("Account Rank: ");
		accountRankDescriptionLabel.setCanAcceptKeyboardFocus(false);
		accountRankDescriptionLabel.setTheme("descriptionLabel");
		accountRankLabel = new Label(" ");
		accountRankLabel.setCanAcceptKeyboardFocus(false);
		accountRankLabel.setTheme("valueLabel");

		goPremiumButton = new Button("Support \"bob!\" - Buy A BobPass");
		goPremiumButton.setCanAcceptKeyboardFocus(false);
		goPremiumButton.setTheme("smallButton");
		//goPremiumButton.setTooltipContent(accountToolTip);
		goPremiumButton.addCallback(new Runnable()
		{
			public void run()
			{
				doGoPremiumButton();
			}
		});

		goPremiumButtonQuestionMark = new Label("?!");
		goPremiumButtonQuestionMark.setCanAcceptKeyboardFocus(false);
		goPremiumButtonQuestionMark.setTheme("bigLabel");
		goPremiumButtonQuestionMark.setTooltipContent(accountToolTip);
		//---------



		//public String characterName = "";

		characterNameDescriptionLabel = new Label("Character Name: ");
		characterNameDescriptionLabel.setCanAcceptKeyboardFocus(false);
		characterNameDescriptionLabel.setTheme("descriptionLabel");
		characterNameLabel = new Label(" ");
		characterNameLabel.setCanAcceptKeyboardFocus(false);
		characterNameLabel.setTheme("valueLabel");


		editCharacterButton = new Button("Edit Character");
		editCharacterButton.setCanAcceptKeyboardFocus(false);
		editCharacterButton.setTheme("smallButton");
		editCharacterButton.addCallback(new Runnable()
		{
			public void run()
			{
				doEditCharacterButton();

			}
		});







		//public String emailAddress = "";
		emailAddressDescriptionLabel = null;
		emailAddressLabel = null;
		emailAddressDescriptionLabel = new Label("Email Address: ");
		emailAddressDescriptionLabel.setCanAcceptKeyboardFocus(false);
		emailAddressDescriptionLabel.setTheme("descriptionLabel");
		emailAddressLabel = new Label(" ");
		emailAddressLabel.setCanAcceptKeyboardFocus(false);
		emailAddressLabel.setTheme("valueLabel");


		//public long accountCreatedTime = 0;
		accountCreatedTimeDescriptionLabel = null;
		accountCreatedTimeLabel = null;
		accountCreatedTimeDescriptionLabel = new Label("Account Created Time: ");
		accountCreatedTimeDescriptionLabel.setCanAcceptKeyboardFocus(false);
		accountCreatedTimeDescriptionLabel.setTheme("descriptionLabel");
		accountCreatedTimeLabel = new Label(" ");
		accountCreatedTimeLabel.setCanAcceptKeyboardFocus(false);
		accountCreatedTimeLabel.setTheme("valueLabel");



		//public long lastLoginTime = 0;
		lastLoginTimeDescriptionLabel = null;
		lastLoginTimeLabel = null;
		lastLoginTimeDescriptionLabel = new Label("Last Login Time: ");
		lastLoginTimeDescriptionLabel.setCanAcceptKeyboardFocus(false);
		lastLoginTimeDescriptionLabel.setTheme("descriptionLabel");
		lastLoginTimeLabel = new Label(" ");
		lastLoginTimeLabel.setCanAcceptKeyboardFocus(false);
		lastLoginTimeLabel.setTheme("valueLabel");


		//public int timesLoggedIn = 0;
		timesLoggedInDescriptionLabel = null;
		timesLoggedInLabel = null;
		timesLoggedInDescriptionLabel = new Label("Times Logged In: ");
		timesLoggedInDescriptionLabel.setCanAcceptKeyboardFocus(false);
		timesLoggedInDescriptionLabel.setTheme("descriptionLabel");
		timesLoggedInLabel = new Label(" ");
		timesLoggedInLabel.setCanAcceptKeyboardFocus(false);
		timesLoggedInLabel.setTheme("valueLabel");


		//public String lastIP = "";
		lastIPDescriptionLabel = null;
		lastIPLabel = null;
		lastIPDescriptionLabel = new Label("Last IP Address: ");
		lastIPDescriptionLabel.setCanAcceptKeyboardFocus(false);
		lastIPDescriptionLabel.setTheme("descriptionLabel");
		lastIPLabel = new Label(" ");
		lastIPLabel.setCanAcceptKeyboardFocus(false);
		lastIPLabel.setTheme("valueLabel");


		accountPanelLabel = new Label("Account Stuff");
		accountPanelLabel.setCanAcceptKeyboardFocus(false);
		accountPanelLabel.setTheme("bigLabel");

		//---------------------------------------------------------
		//account box
		//---------------------------------------------------------

		accountDialogLayout = new DialogLayout();
		accountDialogLayout.setCanAcceptKeyboardFocus(false);

		accountDialogLayout.setHorizontalGroup
		(
			accountDialogLayout.createParallelGroup
			(
				accountDialogLayout.createSequentialGroup().addGap().addWidget(accountPanelLabel).addGap()
				,
				accountDialogLayout.createSequentialGroup
				(
					accountDialogLayout.createParallelGroup
					(
						emailAddressDescriptionLabel,
						accountCreatedTimeDescriptionLabel,
						lastLoginTimeDescriptionLabel,
						timesLoggedInDescriptionLabel,
						lastIPDescriptionLabel
					)
					,
					accountDialogLayout.createParallelGroup
					(
						emailAddressLabel,
						accountCreatedTimeLabel,
						lastLoginTimeLabel,
						timesLoggedInLabel,
						lastIPLabel
					)
				)
			)
		);

		accountDialogLayout.setVerticalGroup
		(
			accountDialogLayout.createSequentialGroup
			(

				accountDialogLayout.createParallelGroup().addWidgets(accountPanelLabel),
				accountDialogLayout.createParallelGroup().addWidgets(emailAddressDescriptionLabel,emailAddressLabel),
				accountDialogLayout.createParallelGroup().addWidgets(accountCreatedTimeDescriptionLabel,accountCreatedTimeLabel),
				accountDialogLayout.createParallelGroup().addWidgets(lastLoginTimeDescriptionLabel,lastLoginTimeLabel),
				accountDialogLayout.createParallelGroup().addWidgets(timesLoggedInDescriptionLabel,timesLoggedInLabel ),
				accountDialogLayout.createParallelGroup().addWidgets(lastIPDescriptionLabel,lastIPLabel)
			)
		);


//		//public String realName = "";
//		realNameDescriptionLabel = null;
//		realNameLabel = null;
//		realNameDescriptionLabel = new Label("Real Name: ");
//		realNameDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		realNameDescriptionLabel.setTheme("descriptionLabel");
//		realNameLabel = new Label(" ");
//		realNameLabel.setCanAcceptKeyboardFocus(false);
//		realNameLabel.setTheme("valueLabel");


		//public long birthdayTime = 0;
//		birthdayTimeDescriptionLabel = null;
//		birthdayTimeLabel = null;
//		birthdayTimeDescriptionLabel = new Label("Birthday Time: ");
//		birthdayTimeDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		birthdayTimeDescriptionLabel.setTheme("descriptionLabel");
//		birthdayTimeLabel = new Label(" ");
//		birthdayTimeLabel.setCanAcceptKeyboardFocus(false);
//		birthdayTimeLabel.setTheme("valueLabel");











		//public String postalCode = "";
		postalCodeDescriptionLabel = null;
		postalCodeLabel = null;
		postalCodeDescriptionLabel = new Label("Postal/Zip Code: ");
		postalCodeDescriptionLabel.setCanAcceptKeyboardFocus(false);
		postalCodeDescriptionLabel.setTheme("descriptionLabel");
		postalCodeLabel = new Label(" ");
		postalCodeLabel.setCanAcceptKeyboardFocus(false);
		postalCodeLabel.setTheme("valueLabel");

		//public String countryName = "";
		countryNameDescriptionLabel = null;
		countryNameLabel = null;
		countryNameDescriptionLabel = new Label("Country Name: ");
		countryNameDescriptionLabel.setCanAcceptKeyboardFocus(false);
		countryNameDescriptionLabel.setTheme("descriptionLabel");
		countryNameLabel = new Label(" ");
		countryNameLabel.setCanAcceptKeyboardFocus(false);
		countryNameLabel.setTheme("valueLabel");

		//public String isoCountryCode = "";
		isoCountryCodeDescriptionLabel = null;
		isoCountryCodeLabel = null;
		isoCountryCodeDescriptionLabel = new Label("Country Code: ");
		isoCountryCodeDescriptionLabel.setCanAcceptKeyboardFocus(false);
		isoCountryCodeDescriptionLabel.setTheme("descriptionLabel");
		isoCountryCodeLabel = new Label(" ");
		isoCountryCodeLabel.setCanAcceptKeyboardFocus(false);
		isoCountryCodeLabel.setTheme("valueLabel");

		//public String placeName = "";
		placeNameDescriptionLabel = null;
		placeNameLabel = null;
		placeNameDescriptionLabel = new Label("Place Name: ");
		placeNameDescriptionLabel.setCanAcceptKeyboardFocus(false);
		placeNameDescriptionLabel.setTheme("descriptionLabel");
		placeNameLabel = new Label(" ");
		placeNameLabel.setCanAcceptKeyboardFocus(false);
		placeNameLabel.setTheme("valueLabel");


		//public String stateName = "";
		stateNameDescriptionLabel = null;
		stateNameLabel = null;
		stateNameDescriptionLabel = new Label("State Name: ");
		stateNameDescriptionLabel.setCanAcceptKeyboardFocus(false);
		stateNameDescriptionLabel.setTheme("descriptionLabel");
		stateNameLabel = new Label(" ");
		stateNameLabel.setCanAcceptKeyboardFocus(false);
		stateNameLabel.setTheme("valueLabel");


		//public float lat = 0;
		latDescriptionLabel = null;
		latLabel = null;
		latDescriptionLabel = new Label("Latitude: ");
		latDescriptionLabel.setCanAcceptKeyboardFocus(false);
		latDescriptionLabel.setTheme("descriptionLabel");
		latLabel = new Label(" ");
		latLabel.setCanAcceptKeyboardFocus(false);
		latLabel.setTheme("valueLabel");

		//public float lon = 0;
		lonDescriptionLabel = null;
		lonLabel = null;
		lonDescriptionLabel = new Label("Longitude: ");
		lonDescriptionLabel.setCanAcceptKeyboardFocus(false);
		lonDescriptionLabel.setTheme("descriptionLabel");
		lonLabel = new Label(" ");
		lonLabel.setCanAcceptKeyboardFocus(false);
		lonLabel.setTheme("valueLabel");

		//public int timeZone = 0;
		timeZoneDescriptionLabel = null;
		timeZoneLabel = null;
		timeZoneDescriptionLabel = new Label("Time Zone: ");
		timeZoneDescriptionLabel.setCanAcceptKeyboardFocus(false);
		timeZoneDescriptionLabel.setTheme("descriptionLabel");
		timeZoneLabel = new Label(" ");
		timeZoneLabel.setCanAcceptKeyboardFocus(false);
		timeZoneLabel.setTheme("valueLabel");


		locationPanelLabel = new Label("Location Stuff");
		locationPanelLabel.setCanAcceptKeyboardFocus(false);
		locationPanelLabel.setTheme("bigLabel");

		//---------------------------------------------------------
		//location box
		//---------------------------------------------------------

		locationDialogLayout = new DialogLayout();
		locationDialogLayout.setCanAcceptKeyboardFocus(false);

		locationDialogLayout.setHorizontalGroup
		(

			locationDialogLayout.createParallelGroup
			(


				locationDialogLayout.createSequentialGroup().addGap().addWidget(locationPanelLabel).addGap()
				,
				locationDialogLayout.createSequentialGroup
				(
					locationDialogLayout.createParallelGroup
					(

							postalCodeDescriptionLabel,
							countryNameDescriptionLabel,
							isoCountryCodeDescriptionLabel,
							placeNameDescriptionLabel,
							stateNameDescriptionLabel,
							latDescriptionLabel,
							lonDescriptionLabel,
							timeZoneDescriptionLabel
					)
					,
					locationDialogLayout.createParallelGroup
					(

							postalCodeLabel,
							countryNameLabel,
							isoCountryCodeLabel,
							placeNameLabel,
							stateNameLabel,
							latLabel,
							lonLabel,
							timeZoneLabel
					)
				)

			)
		);

		locationDialogLayout.setVerticalGroup
		(
			locationDialogLayout.createSequentialGroup
			(

				locationDialogLayout.createParallelGroup().addWidgets(locationPanelLabel),
				locationDialogLayout.createParallelGroup().addWidgets(postalCodeDescriptionLabel,    postalCodeLabel    ),
				locationDialogLayout.createParallelGroup().addWidgets(countryNameDescriptionLabel, countryNameLabel ),
				locationDialogLayout.createParallelGroup().addWidgets(isoCountryCodeDescriptionLabel,isoCountryCodeLabel),
				locationDialogLayout.createParallelGroup().addWidgets(placeNameDescriptionLabel, placeNameLabel ),
				locationDialogLayout.createParallelGroup().addWidgets(stateNameDescriptionLabel,   stateNameLabel   ),
				locationDialogLayout.createParallelGroup().addWidgets(latDescriptionLabel,   latLabel   ),
				locationDialogLayout.createParallelGroup().addWidgets(lonDescriptionLabel, lonLabel ),
				locationDialogLayout.createParallelGroup().addWidgets(timeZoneDescriptionLabel, timeZoneLabel )
			)
		);









		//public String facebookEmail = "";
		facebookEmailDescriptionLabel = null;
		facebookEmailLabel = null;
		facebookEmailDescriptionLabel = new Label("Facebook Email: ");
		facebookEmailDescriptionLabel.setCanAcceptKeyboardFocus(false);
		facebookEmailDescriptionLabel.setTheme("descriptionLabel");
		facebookEmailLabel = new Label(" ");
		facebookEmailLabel.setCanAcceptKeyboardFocus(false);
		facebookEmailLabel.setTheme("valueLabel");


//		//public String facebookBirthday = "";
//		facebookBirthdayDescriptionLabel = null;
//		facebookBirthdayLabel = null;
//		facebookBirthdayDescriptionLabel = new Label("Facebook Birthday: ");
//		facebookBirthdayDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		facebookBirthdayDescriptionLabel.setTheme("descriptionLabel");
//		facebookBirthdayLabel = new Label(" ");
//		facebookBirthdayLabel.setCanAcceptKeyboardFocus(false);
//		facebookBirthdayLabel.setTheme("valueLabel");


		//public String facebookFirstName = "";
		facebookFirstNameDescriptionLabel = null;
		facebookFirstNameLabel = null;
		facebookFirstNameDescriptionLabel = new Label("Facebook First Name: ");
		facebookFirstNameDescriptionLabel.setCanAcceptKeyboardFocus(false);
		facebookFirstNameDescriptionLabel.setTheme("descriptionLabel");
		facebookFirstNameLabel = new Label(" ");
		facebookFirstNameLabel.setCanAcceptKeyboardFocus(false);
		facebookFirstNameLabel.setTheme("valueLabel");


		//public String facebookLastName = "";
		facebookLastNameDescriptionLabel = null;
		facebookLastNameLabel = null;
		facebookLastNameDescriptionLabel = new Label("Facebook Last Name: ");
		facebookLastNameDescriptionLabel.setCanAcceptKeyboardFocus(false);
		facebookLastNameDescriptionLabel.setTheme("descriptionLabel");
		facebookLastNameLabel = new Label(" ");
		facebookLastNameLabel.setCanAcceptKeyboardFocus(false);
		facebookLastNameLabel.setTheme("valueLabel");


		//public String facebookGender = "";
		facebookGenderDescriptionLabel = null;
		facebookGenderLabel = null;
		facebookGenderDescriptionLabel = new Label("Facebook Gender: ");
		facebookGenderDescriptionLabel.setCanAcceptKeyboardFocus(false);
		facebookGenderDescriptionLabel.setTheme("descriptionLabel");
		facebookGenderLabel = new Label(" ");
		facebookGenderLabel.setCanAcceptKeyboardFocus(false);
		facebookGenderLabel.setTheme("valueLabel");


//		//public String facebookLocale = "";
//		facebookLocaleDescriptionLabel = null;
//		facebookLocaleLabel = null;
//		facebookLocaleDescriptionLabel = new Label("Facebook Locale: ");
//		facebookLocaleDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		facebookLocaleDescriptionLabel.setTheme("descriptionLabel");
//		facebookLocaleLabel = new Label(" ");
//		facebookLocaleLabel.setCanAcceptKeyboardFocus(false);
//		facebookLocaleLabel.setTheme("valueLabel");
//
//
//		//public Float facebookTimeZone = 0.0f;
//		facebookTimeZoneDescriptionLabel = null;
//		facebookTimeZoneLabel = null;
//		facebookTimeZoneDescriptionLabel = new Label("Facebook Time Zone: ");
//		facebookTimeZoneDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		facebookTimeZoneDescriptionLabel.setTheme("descriptionLabel");
//		facebookTimeZoneLabel = new Label(" ");
//		facebookTimeZoneLabel.setCanAcceptKeyboardFocus(false);
//		facebookTimeZoneLabel.setTheme("valueLabel");
//
//
//		//public String facebookUsername = "";
//		facebookUsernameDescriptionLabel = null;
//		facebookUsernameLabel = null;
//		facebookUsernameDescriptionLabel = new Label("Facebook Username: ");
//		facebookUsernameDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		facebookUsernameDescriptionLabel.setTheme("descriptionLabel");
//		facebookUsernameLabel = new Label(" ");
//		facebookUsernameLabel.setCanAcceptKeyboardFocus(false);
//		facebookUsernameLabel.setTheme("valueLabel");
//
//
//		//public String facebookWebsite = "";
//		facebookWebsiteDescriptionLabel = null;
//		facebookWebsiteLabel = null;
//		facebookWebsiteDescriptionLabel = new Label("Facebook Website: ");
//		facebookWebsiteDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		facebookWebsiteDescriptionLabel.setTheme("descriptionLabel");
//		facebookWebsiteLabel = new Label(" ");
//		facebookWebsiteLabel.setCanAcceptKeyboardFocus(false);
//		facebookWebsiteLabel.setTheme("valueLabel");






		facebookPanelLabel = new Label("Facebook Stuff");
		facebookPanelLabel.setCanAcceptKeyboardFocus(false);
		facebookPanelLabel.setTheme("bigLabel");

		//---------------------------------------------------------
		//facebook box
		//---------------------------------------------------------

		facebookDialogLayout = new DialogLayout();
		facebookDialogLayout.setCanAcceptKeyboardFocus(false);

		facebookDialogLayout.setHorizontalGroup
		(

			facebookDialogLayout.createParallelGroup
			(


				facebookDialogLayout.createSequentialGroup().addGap().addWidget(facebookPanelLabel).addGap()
				,
				facebookDialogLayout.createSequentialGroup
				(
					facebookDialogLayout.createParallelGroup
					(

						facebookEmailDescriptionLabel,
						//facebookBirthdayDescriptionLabel,
						facebookFirstNameDescriptionLabel,
						facebookLastNameDescriptionLabel,
						facebookGenderDescriptionLabel
						//facebookLocaleDescriptionLabel,
						//facebookTimeZoneDescriptionLabel,
						//facebookUsernameDescriptionLabel,
						//facebookWebsiteDescriptionLabel
					)
					,
					facebookDialogLayout.createParallelGroup
					(

						facebookEmailLabel,
						//facebookBirthdayLabel,
						facebookFirstNameLabel,
						facebookLastNameLabel,
						facebookGenderLabel
						//facebookLocaleLabel,
						//facebookTimeZoneLabel,
						//facebookUsernameLabel,
						//facebookWebsiteLabel
					)
				)

			)
		);

		facebookDialogLayout.setVerticalGroup
		(
			facebookDialogLayout.createSequentialGroup
			(

				facebookDialogLayout.createParallelGroup().addWidgets(facebookPanelLabel),
				facebookDialogLayout.createParallelGroup().addWidgets(facebookEmailDescriptionLabel,    facebookEmailLabel    ),
				//facebookDialogLayout.createParallelGroup().addWidgets(facebookBirthdayDescriptionLabel, facebookBirthdayLabel ),
				facebookDialogLayout.createParallelGroup().addWidgets(facebookFirstNameDescriptionLabel,facebookFirstNameLabel),
				facebookDialogLayout.createParallelGroup().addWidgets(facebookLastNameDescriptionLabel, facebookLastNameLabel ),
				facebookDialogLayout.createParallelGroup().addWidgets(facebookGenderDescriptionLabel,   facebookGenderLabel   )
				//facebookDialogLayout.createParallelGroup().addWidgets(facebookLocaleDescriptionLabel,   facebookLocaleLabel   ),
				//facebookDialogLayout.createParallelGroup().addWidgets(facebookTimeZoneDescriptionLabel, facebookTimeZoneLabel ),
				//facebookDialogLayout.createParallelGroup().addWidgets(facebookUsernameDescriptionLabel, facebookUsernameLabel ),
				//facebookDialogLayout.createParallelGroup().addWidgets(facebookWebsiteDescriptionLabel,  facebookWebsiteLabel  )
			)
		);





//		playerGooglePlusNameDescriptionLabel = new Label("Google+ Name: ");
//		playerGooglePlusNameDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		playerGooglePlusNameDescriptionLabel.setTheme("descriptionLabel");
//		playerGooglePlusNameLabel = new Label("bobsgame");
//		playerGooglePlusNameLabel.setCanAcceptKeyboardFocus(false);
//		playerGooglePlusNameLabel.setTheme("valueLabel");
//
//		playerTwitterNameDescriptionLabel = new Label("Twitter Name: ");
//		playerTwitterNameDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		playerTwitterNameDescriptionLabel.setTheme("descriptionLabel");
//		playerTwitterNameLabel = new Label("bobsgame");
//		playerTwitterNameLabel.setCanAcceptKeyboardFocus(false);
//		playerTwitterNameLabel.setTheme("valueLabel");
//
//
//		totalTimePlayedDescriptionLabel = new Label("Total Time Played: ");
//		totalTimePlayedDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		totalTimePlayedDescriptionLabel.setTheme("descriptionLabel");
//		totalTimePlayedLabel = new Label("20000:00");
//		totalTimePlayedLabel.setCanAcceptKeyboardFocus(false);
//		totalTimePlayedLabel.setTheme("valueLabel");
//
//		sessionTimePlayedDescriptionLabel = new Label("Time Played This Session: ");
//		sessionTimePlayedDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		sessionTimePlayedDescriptionLabel.setTheme("descriptionLabel");
//		sessionTimePlayedLabel = new Label("0:00");
//		sessionTimePlayedLabel.setCanAcceptKeyboardFocus(false);
//		sessionTimePlayedLabel.setTheme("valueLabel");
//
//		averageTimePlayedDescriptionLabel = new Label("Average Session Time: ");
//		averageTimePlayedDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		averageTimePlayedDescriptionLabel.setTheme("descriptionLabel");
//		averageTimePlayedLabel = new Label("0:02");
//		averageTimePlayedLabel.setCanAcceptKeyboardFocus(false);
//		averageTimePlayedLabel.setTheme("valueLabel");
//
//		gamesPurchasedDescriptionLabel = new Label("Games Purchased: ");
//		gamesPurchasedDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		gamesPurchasedDescriptionLabel.setTheme("descriptionLabel");
//		gamesPurchasedLabel = new Label("15");
//		gamesPurchasedLabel.setCanAcceptKeyboardFocus(false);
//		gamesPurchasedLabel.setTheme("valueLabel");
//
//		gamesSoldDescriptionLabel = new Label("Games Sold: ");
//		gamesSoldDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		gamesSoldDescriptionLabel.setTheme("descriptionLabel");
//		gamesSoldLabel = new Label("0");
//		gamesSoldLabel.setCanAcceptKeyboardFocus(false);
//		gamesSoldLabel.setTheme("valueLabel");
//
//		friendsInGameDescriptionLabel = new Label("Friends In Game: ");
//		friendsInGameDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		friendsInGameDescriptionLabel.setTheme("descriptionLabel");
//		friendsInGameLabel = new Label("1");
//		friendsInGameLabel.setCanAcceptKeyboardFocus(false);
//		friendsInGameLabel.setTheme("valueLabel");
//
//		totalGamesPlayedDescriptionLabel = new Label("Total Games Played: ");
//		totalGamesPlayedDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		totalGamesPlayedDescriptionLabel.setTheme("descriptionLabel");
//		totalGamesPlayedLabel = new Label("0");
//		totalGamesPlayedLabel.setCanAcceptKeyboardFocus(false);
//		totalGamesPlayedLabel.setTheme("valueLabel");
//
//		timesChallengedDescriptionLabel = new Label("Times Challenged By Others: ");
//		timesChallengedDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		timesChallengedDescriptionLabel.setTheme("descriptionLabel");
//		timesChallengedLabel = new Label("0");
//		timesChallengedLabel.setCanAcceptKeyboardFocus(false);
//		timesChallengedLabel.setTheme("valueLabel");
//
//		timesChallengerDescriptionLabel = new Label("Times Challenged Others: ");
//		timesChallengerDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		timesChallengerDescriptionLabel.setTheme("descriptionLabel");
//		timesChallengerLabel = new Label("0");
//		timesChallengerLabel.setCanAcceptKeyboardFocus(false);
//		timesChallengerLabel.setTheme("valueLabel");
//
//		timesWonDescriptionLabel = new Label("Times You Won: ");
//		timesWonDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		timesWonDescriptionLabel.setTheme("descriptionLabel");
//		timesWonLabel = new Label("99999");
//		timesWonLabel.setCanAcceptKeyboardFocus(false);
//		timesWonLabel.setTheme("valueLabel");
//
//		timesLostDescriptionLabel = new Label("Times You Lost: ");
//		timesLostDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		timesLostDescriptionLabel.setTheme("descriptionLabel");
//		timesLostLabel = new Label("0");
//		timesLostLabel.setCanAcceptKeyboardFocus(false);
//		timesLostLabel.setTheme("valueLabel");
//
//		betsWonDescriptionLabel = new Label("Bets Won: ");
//		betsWonDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		betsWonDescriptionLabel.setTheme("descriptionLabel");
//		betsWonLabel = new Label("99999");
//		betsWonLabel.setCanAcceptKeyboardFocus(false);
//		betsWonLabel.setTheme("valueLabel");
//
//		betsLostDescriptionLabel = new Label("Bets Lost: ");
//		betsLostDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		betsLostDescriptionLabel.setTheme("descriptionLabel");
//		betsLostLabel = new Label("0");
//		betsLostLabel.setCanAcceptKeyboardFocus(false);
//		betsLostLabel.setTheme("valueLabel");
//
//		pointsEarnedDescriptionLabel = new Label("Total Points Earned: ");
//		pointsEarnedDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		pointsEarnedDescriptionLabel.setTheme("descriptionLabel");
//		pointsEarnedLabel = new Label("99999999");
//		pointsEarnedLabel.setCanAcceptKeyboardFocus(false);
//		pointsEarnedLabel.setTheme("valueLabel");
//
//		globalRankingDescriptionLabel = new Label("Global Ranking: ");
//		globalRankingDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		globalRankingDescriptionLabel.setTheme("descriptionLabel");
//		globalRankingLabel = new Label("1st Place");
//		globalRankingLabel.setCanAcceptKeyboardFocus(false);
//		globalRankingLabel.setTheme("valueLabel");
//
//		regionalRankingDescriptionLabel = new Label("Regional Ranking: ");
//		regionalRankingDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		regionalRankingDescriptionLabel.setTheme("descriptionLabel");
//		regionalRankingLabel = new Label("1st Place");
//		regionalRankingLabel.setCanAcceptKeyboardFocus(false);
//		regionalRankingLabel.setTheme("valueLabel");
//
//		stepsWalkedDescriptionLabel = new Label("Total Steps Walked: ");
//		stepsWalkedDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		stepsWalkedDescriptionLabel.setTheme("descriptionLabel");
//		stepsWalkedLabel = new Label("2452757542");
//		stepsWalkedLabel.setCanAcceptKeyboardFocus(false);
//		stepsWalkedLabel.setTheme("valueLabel");
//
//		buttonsPushedDescriptionLabel = new Label("Total Buttons Pushed: ");
//		buttonsPushedDescriptionLabel.setCanAcceptKeyboardFocus(false);
//		buttonsPushedDescriptionLabel.setTheme("descriptionLabel");
//		buttonsPushedLabel = new Label("32652357");
//		buttonsPushedLabel.setCanAcceptKeyboardFocus(false);
//		buttonsPushedLabel.setTheme("valueLabel");





		insideLayout.setHorizontalGroup
		(
						insideLayout.createParallelGroup
						(
								insideLayout.createSequentialGroup
								(

										insideLayout.createSequentialGroup().addGap()
										,

										insideLayout.createParallelGroup
										(

												insideLayout.createSequentialGroup().addGap().addWidget(statusPanelLabel).addGap(),

												insideLayout.createSequentialGroup
												(

														insideLayout.createSequentialGroup
														(

																insideLayout.createParallelGroup
																(







																		characterNameDescriptionLabel
																		,accountRankDescriptionLabel
																		//,moneyDescriptionLabel




																		//realNameDescriptionLabel,
																		//birthdayTimeDescriptionLabel,


//
//																		playerFacebookNameDescriptionLabel,
//																		playerGooglePlusNameDescriptionLabel,
//																		playerTwitterNameDescriptionLabel,
//																		totalTimePlayedDescriptionLabel,
//																		sessionTimePlayedDescriptionLabel,
//																		averageTimePlayedDescriptionLabel,
//																		stepsWalkedDescriptionLabel,
//																		buttonsPushedDescriptionLabel,
//																		globalRankingDescriptionLabel,
//																		regionalRankingDescriptionLabel,
//																		pointsEarnedDescriptionLabel,
//																		gamesPurchasedDescriptionLabel,
//																		gamesSoldDescriptionLabel,
//																		friendsInGameDescriptionLabel,
//																		totalGamesPlayedDescriptionLabel,
//																		timesChallengedDescriptionLabel,
//																		timesChallengerDescriptionLabel,
//																		timesWonDescriptionLabel,
//																		timesLostDescriptionLabel,
//																		betsWonDescriptionLabel,
//																		betsLostDescriptionLabel






																)
																,
																insideLayout.createParallelGroup
																(






																		insideLayout.createSequentialGroup(characterNameLabel)
																		,insideLayout.createSequentialGroup(accountRankLabel)
																		//,insideLayout.createSequentialGroup(moneyLabel)




																		//realNameLabel,
																		//birthdayTimeLabel,



//
//																		playerFacebookNameLabel,
//																		playerGooglePlusNameLabel,
//																		playerTwitterNameLabel,
//																		totalTimePlayedLabel,
//																		sessionTimePlayedLabel,
//																		averageTimePlayedLabel,
//																		stepsWalkedLabel,
//																		buttonsPushedLabel,
//																		globalRankingLabel,
//																		regionalRankingLabel,
//																		pointsEarnedLabel,
//																		gamesPurchasedLabel,
//																		gamesSoldLabel,
//																		friendsInGameLabel,
//																		totalGamesPlayedLabel,
//																		timesChallengedLabel,
//																		timesChallengerLabel,
//																		timesWonLabel,
//																		timesLostLabel,
//																		betsWonLabel,
//																		betsLostLabel



																)
																,
																insideLayout.createParallelGroup
																(
																		insideLayout.createSequentialGroup(editCharacterButton).addGap(),
																		//insideLayout.createSequentialGroup(addMoneyButton,addMoneyButtonQuestionMark).addGap(),
																		insideLayout.createSequentialGroup(goPremiumButton,goPremiumButtonQuestionMark).addGap()
																)

														)

												)
												,
												insideLayout.createSequentialGroup(accountDialogLayout)
												,
												insideLayout.createSequentialGroup(locationDialogLayout)
												,
												insideLayout.createSequentialGroup(facebookDialogLayout)

										)
										,


										insideLayout.createSequentialGroup().addGap()


								)

						)

		);

		insideLayout.setVerticalGroup
		(
			insideLayout.createSequentialGroup
			(
				insideLayout.createParallelGroup
				(
					insideLayout.createSequentialGroup
					(

							//insideLayout.createParallelGroup(editCharacterButton)
							//,
							//insideLayout.createSequentialGroup().addGap()
					)
					,
					insideLayout.createSequentialGroup
					(





							insideLayout.createSequentialGroup(statusPanelLabel),
							insideLayout.createSequentialGroup().addGap(),


							insideLayout.createParallelGroup(characterNameDescriptionLabel,characterNameLabel,editCharacterButton),
							insideLayout.createSequentialGroup().addGap(),
							insideLayout.createParallelGroup(accountRankDescriptionLabel,accountRankLabel,goPremiumButton,goPremiumButtonQuestionMark),
							insideLayout.createSequentialGroup().addGap(),
							//insideLayout.createParallelGroup(moneyDescriptionLabel,moneyLabel,addMoneyButton,addMoneyButtonQuestionMark),

							insideLayout.createSequentialGroup().addGap(),

							insideLayout.createSequentialGroup(accountDialogLayout),
							insideLayout.createSequentialGroup().addGap(),
							insideLayout.createSequentialGroup(locationDialogLayout),
							insideLayout.createSequentialGroup().addGap(),
							//insideLayout.createParallelGroup(realNameDescriptionLabel,            realNameLabel                ),
							//insideLayout.createParallelGroup(birthdayTimeDescriptionLabel,        birthdayTimeLabel            ),


							insideLayout.createSequentialGroup(facebookDialogLayout)

//								insideLayout.createParallelGroup(playerFacebookNameDescriptionLabel,		playerFacebookNameLabel),
//								insideLayout.createParallelGroup(playerGooglePlusNameDescriptionLabel,		playerGooglePlusNameLabel),
//								insideLayout.createParallelGroup(playerTwitterNameDescriptionLabel,		playerTwitterNameLabel),
//								insideLayout.createParallelGroup(totalTimePlayedDescriptionLabel,		totalTimePlayedLabel),
//								insideLayout.createParallelGroup(sessionTimePlayedDescriptionLabel,		sessionTimePlayedLabel),
//								insideLayout.createParallelGroup(averageTimePlayedDescriptionLabel,		averageTimePlayedLabel),
//								insideLayout.createParallelGroup(stepsWalkedDescriptionLabel,			stepsWalkedLabel),
//								insideLayout.createParallelGroup(buttonsPushedDescriptionLabel,			buttonsPushedLabel),
//								insideLayout.createParallelGroup(globalRankingDescriptionLabel,			globalRankingLabel),
//								insideLayout.createParallelGroup(regionalRankingDescriptionLabel,		regionalRankingLabel),
//								insideLayout.createParallelGroup(pointsEarnedDescriptionLabel,			pointsEarnedLabel),
//								insideLayout.createParallelGroup(gamesPurchasedDescriptionLabel,		gamesPurchasedLabel),
//								insideLayout.createParallelGroup(gamesSoldDescriptionLabel,				gamesSoldLabel),
//								insideLayout.createParallelGroup(friendsInGameDescriptionLabel,			friendsInGameLabel),
//								insideLayout.createParallelGroup(totalGamesPlayedDescriptionLabel,		totalGamesPlayedLabel),
//								insideLayout.createParallelGroup(timesChallengedDescriptionLabel,		timesChallengedLabel),
//								insideLayout.createParallelGroup(timesChallengerDescriptionLabel,		timesChallengerLabel),
//								insideLayout.createParallelGroup(timesWonDescriptionLabel,				timesWonLabel),
//								insideLayout.createParallelGroup(timesLostDescriptionLabel,				timesLostLabel),
//								insideLayout.createParallelGroup(betsWonDescriptionLabel,				betsWonLabel),
//								insideLayout.createParallelGroup(betsLostDescriptionLabel,				betsLostLabel)
					)
				)
			)

		);


	}

	//=========================================================================================================================
	protected void doGoPremiumButton()
	{//=========================================================================================================================

        try
        {
            //open browser window, we can't get it with JS as a desktop client so we need to redirect to PHP or something which stores it in SQL
            String url = "http://www.bobsgame.com/buyBobPass.php?u="+GameSave().userID;

            java.awt.Desktop.getDesktop().browse(java.net.URI.create(url));
        }
        catch (java.io.IOException e)
        {
            log.error("Could not open browser: "+e.getMessage());
        }

	}

	//=========================================================================================================================
	protected void doAddMoneyButton()
	{//=========================================================================================================================
        try
        {
            //open browser window, we can't get it with JS as a desktop client so we need to redirect to PHP or something which stores it in SQL
            String url = "http://www.bobsgame.com/buyBobCoins.php?u="+GameSave().userID;

            java.awt.Desktop.getDesktop().browse(java.net.URI.create(url));
        }
        catch (java.io.IOException e)
        {
            log.error("Could not open browser: "+e.getMessage());
        }

	}

	//=========================================================================================================================
	protected void doEditCharacterButton()
	{//=========================================================================================================================
		StuffMenu().setActivated(false);

		PlayerEditMenu().setActivated(true);

	}

	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================
		super.init();
		getGUI().setTooltipDelay(1);

	}

	//=========================================================================================================================
	@Override
	public void layout()
	{//=========================================================================================================================



		//Login panel is centered

		//panel.adjustSize();
		//panel.setPosition(
				//insideScrollPaneLayout.getInnerX() + (insideScrollPaneLayout.getInnerWidth() - panel.getWidth()) / 2,
				//insideScrollPaneLayout.getInnerY() + (insideScrollPaneLayout.getInnerHeight() - panel.getHeight()) / 2);

		if(facebookDialogLayout.isVisible()==true)
		{
			facebookDialogLayout.adjustSize();
		}
		else
		{
			facebookDialogLayout.setSize(0,0);
		}

		super.layout();
	}


	//=========================================================================================================================
	public void setVisible(boolean b)
	{//=========================================================================================================================
		super.setVisible(b);

		if(b==true)
		{
			//String birthdayString = "?";
			//if(GameSave().birthdayTime>0)birthdayString = new SimpleDateFormat("yyyy-MM-dd").format(new Date(GameSave().birthdayTime));

			String accountCreatedTimeString = "?";
			if(GameSave().accountCreatedTime>0)accountCreatedTimeString = new SimpleDateFormat("yyyy-MM-dd-HH:mm").format(new Date(GameSave().accountCreatedTime));

			String lastLoginTimeString = "?";
			if(GameSave().lastLoginTime>0)lastLoginTimeString = new SimpleDateFormat("yyyy-MM-dd-HH:mm").format(new Date(GameSave().lastLoginTime));

			String accountRankString = ClientEngine().getAccountRankString(GameSave().accountRank);




			String moneyString = String.format("%1$,.2f", GameSave().money);


			//update labels
			moneyLabel.setText(""+moneyString);
			accountRankLabel.setText(""+accountRankString);

			characterNameLabel.setText(""+GameSave().characterName);
			emailAddressLabel.setText(""+GameSave().emailAddress);

			accountCreatedTimeLabel.setText(""+accountCreatedTimeString);
			lastLoginTimeLabel.setText(""+lastLoginTimeString);
			timesLoggedInLabel.setText(""+GameSave().timesLoggedIn);
			lastIPLabel.setText(""+GameSave().lastIP);
			//realNameLabel.setText(""+GameSave().realName);
			//birthdayTimeLabel.setText(""+birthdayString);
			postalCodeLabel.setText(""+GameSave().postalCode);
			countryNameLabel.setText(""+GameSave().countryName);
			isoCountryCodeLabel.setText(""+GameSave().isoCountryCode);
			placeNameLabel.setText(""+GameSave().placeName);
			stateNameLabel.setText(""+GameSave().stateName);
			latLabel.setText(""+GameSave().lat);
			lonLabel.setText(""+GameSave().lon);
			timeZoneLabel.setText(""+ClientMain.clientMain.timeZoneGMTOffset);

			postalCodeLabel.setText(""+GameSave().postalCode);
			stateNameLabel.setText(""+GameSave().stateName);
			countryNameLabel.setText(""+GameSave().countryName);


			if(GameSave().facebookID.length()>0)
			{
				facebookDialogLayout.setVisible(true);

				facebookEmailLabel.setText(""+GameSave().facebookEmail);
				//facebookBirthdayLabel.setText(""+GameSave().facebookBirthday);
				facebookFirstNameLabel.setText(""+GameSave().facebookFirstName);
				facebookLastNameLabel.setText(""+GameSave().facebookLastName);
				facebookGenderLabel.setText(""+GameSave().facebookGender);
				//facebookLocaleLabel.setText(""+GameSave().facebookLocale);
				//facebookTimeZoneLabel.setText(""+GameSave().facebookTimeZone);
				//facebookUsernameLabel.setText(""+GameSave().facebookUsername);
				//facebookWebsiteLabel.setText(""+GameSave().facebookWebsite);

			}
			else facebookDialogLayout.setVisible(false);

		}

	}







}
