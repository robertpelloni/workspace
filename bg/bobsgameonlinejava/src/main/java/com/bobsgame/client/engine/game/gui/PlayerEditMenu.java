package com.bobsgame.client.engine.game.gui;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathConstants;
import javax.xml.xpath.XPathExpressionException;
import javax.xml.xpath.XPathFactory;

import org.slf4j.LoggerFactory;
import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import com.bobsgame.client.Texture;


import ch.qos.logback.classic.Logger;

import com.bobsgame.ClientMain;
import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.entity.Entity;
import com.bobsgame.client.engine.game.Player;
import com.bobsgame.client.engine.text.Caption;
import com.bobsgame.net.BobNet;
import com.bobsgame.net.GameSave;
import com.bobsgame.shared.Utils;
import com.restfb.FacebookClient;

import de.matthiasmann.twl.ComboBox;
import de.matthiasmann.twl.DialogLayout;
import de.matthiasmann.twl.EditField;
import de.matthiasmann.twl.EditField.Callback;
import de.matthiasmann.twl.Button;
import de.matthiasmann.twl.Label;
import de.matthiasmann.twl.ScrollPane;
import de.matthiasmann.twl.ToggleButton;
import de.matthiasmann.twl.model.OptionBooleanModel;
import de.matthiasmann.twl.model.SimpleChangableListModel;
import de.matthiasmann.twl.model.SimpleIntegerModel;


//=========================================================================================================================
public class PlayerEditMenu extends MenuPanel
{//=========================================================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(PlayerEditMenu.class);



	DialogLayout editPanel;
	DialogLayout animPanel;

	Label playerEditPanelLabel;

	Label errorLabel;
	Label statusLabel;










	Label nameLabel;
	EditField nameEditField;

	Label zipCodeLabel;
	EditField zipCodeEditField;


	Label addSocialAccountsLabel;
	Label facebookAccountLabel;
	Button addFacebookAccountButton;

	Label googlePlusAccountLabel;
	//Button addGooglePlusAccountButton;

	Label genderLabel;
	Label[] genderButtonLabels;
	SimpleIntegerModel genderOptionModel;
	ToggleButton[] genderButtons;

	Label countryLabel;
	SimpleChangableListModel<String> countryStrings;
	ComboBox<String> countryComboBox;

	Label archetypeLabel;
	SimpleChangableListModel<String> archetypeStrings;
	ComboBox<String> archetypeComboBox;

	Label hairColorLabel;
	SimpleChangableListModel<String> hairColorStrings;
	ComboBox<String> hairColorComboBox;

	Label skinColorLabel;
	SimpleChangableListModel<String> skinColorStrings;
	ComboBox<String> skinColorComboBox;

	Label eyeColorLabel;
	SimpleChangableListModel<String> eyeColorStrings;
	ComboBox<String> eyeColorComboBox;

	Label shirtColorLabel;
	SimpleChangableListModel<String> shirtColorStrings;
	ComboBox<String> shirtColorComboBox;

	Label pantsColorLabel;
	SimpleChangableListModel<String> pantsColorStrings;
	ComboBox<String> pantsColorComboBox;

	Label shoeColorLabel;
	SimpleChangableListModel<String> shoeColorStrings;
	ComboBox<String> shoeColorComboBox;

	Button randomButton;
	Button okButton;







	public String nameString = "";

	public int genderIndex=0;

	public int archetypeIndex = 0;
	public int hairColorIndex = 0;
	public int skinColorIndex = 0;
	public int eyeColorIndex = 0;
	public int shirtColorIndex = 0;
	public int pantsColorIndex = 0;
	public int shoeColorIndex = 0;


	Caption playerNameCaption = null;


	public boolean initRandom=false;



	public long lastTime = 0;
	public int frame=0;

	public int direction = 0;
	public int loopCount=0;




	//=========================================================================================================================
	public PlayerEditMenu()
	{//=========================================================================================================================

		super();




		editPanel = new DialogLayout();
		editPanel.setTheme("darkPanel");



		animPanel = new DialogLayout();
		//animPanel.setTheme("loginpanel");







		playerEditPanelLabel = new Label("Edit Your Character");
		playerEditPanelLabel.setCanAcceptKeyboardFocus(false);
		playerEditPanelLabel.setTheme("bigLabel");



		errorLabel = new Label(" ");
		errorLabel.setTheme("errorLabel");
		errorLabel.setCanAcceptKeyboardFocus(false);

		statusLabel = new Label(" ");
		statusLabel.setTheme("statusLabel");
		statusLabel.setCanAcceptKeyboardFocus(false);

		//---------------------------------------------------------
		//player name
		//---------------------------------------------------------
		nameLabel = new Label("Player Name:");
		nameLabel.setCanAcceptKeyboardFocus(false);

		nameEditField = new EditField();
		nameEditField.setTheme("editfield");
		nameEditField.setText("New Player");
		nameEditField.setMaxTextLength(40);

		nameEditField.addCallback(new Callback()
		{
			@Override
			public void callback(int key)
			{
				redrawPlayer();
			}
		});









		//---------------------------------------------------------
		//zip code
		//---------------------------------------------------------
		zipCodeEditField = new EditField();
		zipCodeEditField.setText("");
		zipCodeEditField.setMaxTextLength(40);
		zipCodeEditField.addCallback(new Callback()
		{
			@Override
			public void callback(int key)
			{
				//zip cannot contain `
			}
		});
		zipCodeLabel = new Label("Zip/Postal Code:");
		zipCodeLabel.setLabelFor(zipCodeEditField);
		zipCodeLabel.setCanAcceptKeyboardFocus(false);

		//---------------------------------------------------------
		//country
		//---------------------------------------------------------
		countryLabel = new Label("Country:");
		countryLabel.setCanAcceptKeyboardFocus(false);

		countryStrings = CountryCodes.getCountryList();

		countryComboBox = new ComboBox<String>(countryStrings);

//		countryComboBox.addCallback(new Runnable()
//		{
//			public void run()
//			{
//
//			}
//		});

		//---------------------------------------------------------
		//add facebook account button
		//---------------------------------------------------------

		addSocialAccountsLabel = new Label("Link your Facebook or Google+ Account to play with your friends!");

		addFacebookAccountButton = new Button("Link Facebook Account");
		addFacebookAccountButton.setCanAcceptKeyboardFocus(false);
		addFacebookAccountButton.setTheme("button");
		addFacebookAccountButton.addCallback(new Runnable()
		{
			public void run()
			{
				linkFacebookAccount();
			}
		});
		facebookAccountLabel = new Label("Facebook: Not Connected");
		facebookAccountLabel.setLabelFor(addFacebookAccountButton);
		facebookAccountLabel.setTheme("statusLabel");
		facebookAccountLabel.setCanAcceptKeyboardFocus(false);

		//---------------------------------------------------------
		//add google plus account button
		//---------------------------------------------------------
//		addGooglePlusAccountButton = new Button("Link Google+ Account");
//		addGooglePlusAccountButton.setCanAcceptKeyboardFocus(false);
//		addGooglePlusAccountButton.setTheme("button");
//		addGooglePlusAccountButton.addCallback(new Runnable()
//		{
//			public void run()
//			{
//
//			}
//		});
//		googlePlusAccountLabel = new Label("Google+: Not Connected");
//		googlePlusAccountLabel.setLabelFor(addGooglePlusAccountButton);
//		googlePlusAccountLabel.setTheme("statusLabel");
//		googlePlusAccountLabel.setCanAcceptKeyboardFocus(false);



















		//---------------------------------------------------------
		//random button
		//---------------------------------------------------------
		randomButton = new Button("Randomize Appearance");
		randomButton.setCanAcceptKeyboardFocus(false);
		randomButton.setTheme("button");
		randomButton.addCallback(new Runnable()
		{
			public void run()
			{

				setRandomOptions();

				redrawPlayer();
			}
		});

		//---------------------------------------------------------
		//gender
		//---------------------------------------------------------
		genderLabel = new Label("Gender:");
		genderLabel.setCanAcceptKeyboardFocus(false);

		genderButtons = new ToggleButton[2];
		genderButtonLabels = new Label[2];

		genderButtonLabels[0] = new Label("Male");
		genderButtonLabels[1] = new Label("Female");

		genderOptionModel = new SimpleIntegerModel(1, genderButtons.length, 1);
		for(int i=0 ; i<genderButtons.length ; i++) {
			genderButtons[i] = new ToggleButton(new OptionBooleanModel(genderOptionModel, i+1));
			genderButtons[i].setTheme("radiobutton");

			genderButtons[i].addCallback(new Runnable()
			{
				public void run()
				{
					redrawPlayer();
				}
			});
		}
		genderButtonLabels[0].setLabelFor(genderButtons[0]);
		genderButtonLabels[1].setLabelFor(genderButtons[1]);


		//---------------------------------------------------------
		//archetype
		//---------------------------------------------------------
		archetypeLabel = new Label("Archetype:");
		archetypeLabel.setCanAcceptKeyboardFocus(false);

		archetypeStrings = new SimpleChangableListModel<String>("Popular", "Hipster", "Gothy", "Tough", "Jock", "Nerdy", "Chunky", "Punk", "Skater", "Thuggin'", "Pimply", "Normal 1", "Normal 2", "Normal 3", "Normal 4", "Normal 5", "Normal 6", "Normal 7", "Normal 8", "Normal 9", "Normal 10", "Normal 11", "Normal 12", "Normal 13", "Normal 14", "Normal 15");
		archetypeComboBox = new ComboBox<String>(archetypeStrings);

		archetypeComboBox.addCallback(new Runnable()
		{
			public void run()
			{
				redrawPlayer();
			}
		});


		//---------------------------------------------------------
		//hair color
		//---------------------------------------------------------
		hairColorLabel = new Label("Hair Color:");
		hairColorLabel.setCanAcceptKeyboardFocus(false);

		hairColorStrings = new SimpleChangableListModel<String>("Black", "Dark Brown", "Light Brown", "Blonde", "Red");
		hairColorComboBox = new ComboBox<String>(hairColorStrings);


		hairColorComboBox.addCallback(new Runnable()
		{
			public void run()
			{
				redrawPlayer();
			}
		});


		//---------------------------------------------------------
		//eye color
		//---------------------------------------------------------
		eyeColorLabel = new Label("Eye Color:");
		eyeColorLabel.setCanAcceptKeyboardFocus(false);

		eyeColorStrings = new SimpleChangableListModel<String>("Black", "Brown", "Green", "Blue", "Gray");
		eyeColorComboBox = new ComboBox<String>(eyeColorStrings);

		eyeColorComboBox.addCallback(new Runnable()
		{
			public void run()
			{
				redrawPlayer();
			}
		});

		//---------------------------------------------------------
		//skin shade
		//---------------------------------------------------------
		skinColorLabel = new Label("Skin Shade:");
		skinColorLabel.setCanAcceptKeyboardFocus(false);

		skinColorStrings = new SimpleChangableListModel<String>("Lightest", "Light", "Medium", "Dark", "Darkest");
		skinColorComboBox = new ComboBox<String>(skinColorStrings);

		skinColorComboBox.addCallback(new Runnable()
		{
			public void run()
			{

				redrawPlayer();
			}
		});

		//---------------------------------------------------------
		//shirt color
		//---------------------------------------------------------
		shirtColorLabel = new Label("Shirt Color:");
		shirtColorLabel.setCanAcceptKeyboardFocus(false);

		shirtColorStrings = new SimpleChangableListModel<String>("Black", "Gray", "White", "Brown", "Blue", "Purple", "Red", "Magenta", "Pink", "Orange", "Yellow", "Green", "Cyan");
		shirtColorComboBox = new ComboBox<String>(shirtColorStrings);


		shirtColorComboBox.addCallback(new Runnable()
		{
			public void run()
			{

				redrawPlayer();
			}
		});

		//---------------------------------------------------------
		//pants color
		//---------------------------------------------------------
		pantsColorLabel = new Label("Pants Color:");
		pantsColorLabel.setCanAcceptKeyboardFocus(false);

		pantsColorStrings = new SimpleChangableListModel<String>("Black", "Gray", "White", "Brown", "Blue", "Purple", "Red", "Magenta", "Pink", "Orange", "Yellow", "Green", "Cyan");
		pantsColorComboBox = new ComboBox<String>(pantsColorStrings);

		pantsColorComboBox.addCallback(new Runnable()
		{
			public void run()
			{

				redrawPlayer();
			}
		});

		//---------------------------------------------------------
		//shoe color
		//---------------------------------------------------------
		shoeColorLabel = new Label("Shoe Color:");
		shoeColorLabel.setCanAcceptKeyboardFocus(false);

		shoeColorStrings = new SimpleChangableListModel<String>("Black", "Gray", "White", "Brown", "Blue", "Purple", "Red", "Magenta", "Pink", "Orange", "Yellow", "Green", "Cyan");
		shoeColorComboBox = new ComboBox<String>(shoeColorStrings);

		shoeColorComboBox.addCallback(new Runnable()
		{
			public void run()
			{
				redrawPlayer();
			}
		});












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

				doOKButton();
			}
		});




		//---------------------------------------------------------
		//layout
		//---------------------------------------------------------

		animPanel.setHorizontalGroup
		(
				animPanel.createParallelGroup
				(
						animPanel.createSequentialGroup().addGap(80)
				)
		);

		animPanel.setVerticalGroup
		(
				animPanel.createSequentialGroup
				(
						animPanel.createSequentialGroup().addGap(160)
				)
		);




		//---------------------------------------------------------
		//layout
		//---------------------------------------------------------

		editPanel.setHorizontalGroup
		(
				editPanel.createParallelGroup
				(
					editPanel.createSequentialGroup().addMinGap(40),
					editPanel.createParallelGroup
					(
							editPanel.createSequentialGroup().addGap().addWidgets(playerEditPanelLabel).addGap(),
							editPanel.createSequentialGroup().addGap().addWidgets(errorLabel).addGap(),
							editPanel.createSequentialGroup().addGap().addWidgets(statusLabel).addGap(),


							editPanel.createSequentialGroup
							(
								editPanel.createSequentialGroup().addGap(),
								editPanel.createParallelGroup
								(
										editPanel.createSequentialGroup().addGap().addWidgets(zipCodeLabel),
										editPanel.createSequentialGroup().addGap().addWidgets(countryLabel),
										editPanel.createSequentialGroup().addGap().addWidgets(nameLabel),
										editPanel.createSequentialGroup().addGap().addWidgets(genderLabel),
										editPanel.createSequentialGroup().addGap().addWidgets(archetypeLabel),
										editPanel.createSequentialGroup().addGap().addWidgets(hairColorLabel),
										editPanel.createSequentialGroup().addGap().addWidgets(eyeColorLabel),
										editPanel.createSequentialGroup().addGap().addWidgets(skinColorLabel),
										editPanel.createSequentialGroup().addGap().addWidgets(shirtColorLabel),
										editPanel.createSequentialGroup().addGap().addWidgets(pantsColorLabel),
										editPanel.createSequentialGroup().addGap().addWidgets(shoeColorLabel)
								)
								,
								editPanel.createParallelGroup
								(
										editPanel.createSequentialGroup().addWidgets(zipCodeEditField),
										editPanel.createSequentialGroup().addWidgets(countryComboBox),
										editPanel.createSequentialGroup().addWidgets(nameEditField),
										editPanel.createSequentialGroup().addGap().addWidgets(genderButtonLabels[0],genderButtons[0]).addGap().addWidgets(genderButtonLabels[1],genderButtons[1]).addGap(),
										editPanel.createSequentialGroup().addWidgets(archetypeComboBox),
										editPanel.createSequentialGroup().addWidgets(hairColorComboBox),
										editPanel.createSequentialGroup().addWidgets(eyeColorComboBox),
										editPanel.createSequentialGroup().addWidgets(skinColorComboBox),
										editPanel.createSequentialGroup().addWidgets(shirtColorComboBox),
										editPanel.createSequentialGroup().addWidgets(pantsColorComboBox),
										editPanel.createSequentialGroup().addWidgets(shoeColorComboBox)
								),
								editPanel.createSequentialGroup().addGap()
							),
							//editPanel.createSequentialGroup().addGap().addWidgets(addSocialAccountsLabel).addGap(),
							//editPanel.createSequentialGroup().addGap().addWidgets(facebookAccountLabel).addGap(),
							//editPanel.createSequentialGroup().addGap().addWidgets(addFacebookAccountButton).addGap(),
							//editPanel.createSequentialGroup().addGap().addWidgets(googlePlusAccountLabel).addGap(),
							//editPanel.createSequentialGroup().addGap().addWidgets(addGooglePlusAccountButton).addGap(),

							editPanel.createSequentialGroup().addGap().addWidgets(randomButton).addGap(),
							editPanel.createSequentialGroup().addGap().addWidgets(animPanel).addGap(),

							editPanel.createSequentialGroup().addGap().addWidgets(okButton).addGap()

					),
					editPanel.createSequentialGroup().addMinGap(40)
				)
		);

		editPanel.setVerticalGroup
		(
				editPanel.createSequentialGroup
				(

					editPanel.createParallelGroup().addMinGap(20).addWidgets(playerEditPanelLabel).addMinGap(20),
					editPanel.createParallelGroup().addMinGap(10),
					editPanel.createParallelGroup().addMinGap(20).addWidgets(nameLabel, nameEditField).addMinGap(20),

					editPanel.createParallelGroup().addMinGap(10),
					editPanel.createParallelGroup().addMinGap(20).addWidgets(zipCodeLabel,zipCodeEditField).addMinGap(20),
					editPanel.createParallelGroup().addMinGap(20).addWidgets(countryLabel).addWidgets(countryComboBox).addMinGap(20),
					//editPanel.createParallelGroup().addMinGap(10),
					//editPanel.createParallelGroup().addMinGap(20).addWidgets(addSocialAccountsLabel).addMinGap(20),

					//editPanel.createParallelGroup().addMinGap(20).addWidgets(addFacebookAccountButton).addMinGap(20),
					//editPanel.createParallelGroup().addMinGap(20).addWidgets(facebookAccountLabel),

					//editPanel.createParallelGroup().addMinGap(20).addWidgets(addGooglePlusAccountButton).addMinGap(20),
					//editPanel.createParallelGroup().addMinGap(20).addWidgets(googlePlusAccountLabel),
					//editPanel.createParallelGroup().addMinGap(20),
					editPanel.createParallelGroup().addMinGap(20).addWidgets(animPanel).addMinGap(20),
					editPanel.createParallelGroup().addMinGap(20).addWidgets(randomButton).addMinGap(20),
					editPanel.createParallelGroup().addMinGap(20).addWidgets(genderLabel).addWidgets(genderButtons).addWidgets(genderButtonLabels).addMinGap(20),
					editPanel.createParallelGroup().addMinGap(20).addWidgets(archetypeLabel).addWidgets(archetypeComboBox).addMinGap(20),
					editPanel.createParallelGroup().addMinGap(20).addWidgets(hairColorLabel).addWidgets(hairColorComboBox).addMinGap(20),
					editPanel.createParallelGroup().addMinGap(20).addWidgets(eyeColorLabel).addWidgets(eyeColorComboBox).addMinGap(20),
					editPanel.createParallelGroup().addMinGap(20).addWidgets(skinColorLabel).addWidgets(skinColorComboBox).addMinGap(20),
					editPanel.createParallelGroup().addMinGap(20).addWidgets(shirtColorLabel).addWidgets(shirtColorComboBox).addMinGap(20),
					editPanel.createParallelGroup().addMinGap(20).addWidgets(pantsColorLabel).addWidgets(pantsColorComboBox).addMinGap(20),
					editPanel.createParallelGroup().addMinGap(20).addWidgets(shoeColorLabel).addWidgets(shoeColorComboBox).addMinGap(20),

					editPanel.createParallelGroup().addMinGap(20).addWidgets(statusLabel).addMinGap(20),
					editPanel.createParallelGroup().addMinGap(20).addWidgets(errorLabel).addMinGap(20),
					editPanel.createParallelGroup().addMinGap(20).addWidgets(okButton).addMinGap(20)

				)
		);


		//---------------------------------------------------------
		//layout
		//---------------------------------------------------------

		insideScrollPaneLayout.setHorizontalGroup
		(
				insideScrollPaneLayout.createParallelGroup
				(
						insideScrollPaneLayout.createSequentialGroup().addGap().addWidget(editPanel).addGap()
				)
		);

		insideScrollPaneLayout.setVerticalGroup
		(
				insideScrollPaneLayout.createSequentialGroup
				(
						insideScrollPaneLayout.createSequentialGroup().addGap()
						,
						insideScrollPaneLayout.createParallelGroup().addWidget(editPanel)
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
		//scrollPane.setExpandContentSize(true);

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



		editPanel.adjustSize();

	}




	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================

		countryComboBox.setSelected(0);


		archetypeComboBox.setSelected(0);
		hairColorComboBox.setSelected(0);
		eyeColorComboBox.setSelected(1);
		skinColorComboBox.setSelected(2);
		shirtColorComboBox.setSelected(8);

		pantsColorComboBox.setSelected(4);
		shoeColorComboBox.setSelected(2);

	}

	//=========================================================================================================================
	public void setButtonsVisible(boolean b)
	{//=========================================================================================================================



		//handle all the buttons and labels etc

		nameLabel.setVisible(b);
		nameEditField.setVisible(b);

		zipCodeLabel.setVisible(b);
		zipCodeEditField.setVisible(b);


		addSocialAccountsLabel.setVisible(b);
		facebookAccountLabel.setVisible(b);
		addFacebookAccountButton.setVisible(b);

		//googlePlusAccountLabel.setVisible(b);
		//addGooglePlusAccountButton.setVisible(b);

		genderLabel.setVisible(b);
		for(int i=0;i<genderButtonLabels.length;i++)genderButtonLabels[i].setVisible(b);

		for(int i=0;i<genderButtons.length;i++)genderButtons[i].setVisible(b);

		countryLabel.setVisible(b);

		countryComboBox.setVisible(b);

		archetypeLabel.setVisible(b);

		archetypeComboBox.setVisible(b);

		hairColorLabel.setVisible(b);

		hairColorComboBox.setVisible(b);

		skinColorLabel.setVisible(b);

		skinColorComboBox.setVisible(b);

		eyeColorLabel.setVisible(b);

		eyeColorComboBox.setVisible(b);

		shirtColorLabel.setVisible(b);

		shirtColorComboBox.setVisible(b);

		pantsColorLabel.setVisible(b);

		pantsColorComboBox.setVisible(b);

		shoeColorLabel.setVisible(b);

		shoeColorComboBox.setVisible(b);

		randomButton.setVisible(b);
		okButton.setVisible(b);


	}

	//=========================================================================================================================
	public class AddressInfo
	{//=========================================================================================================================
		String postalCode = "";
		String stateName = "";
		String placeName = "";

		float lat = 0.0f;
		float lon = 0.0f;
		float timeZone = 0.0f;

	}

	//=========================================================================================================================
	public AddressInfo queryYahooGeocodingAPI(String address)
	{//=========================================================================================================================

		AddressInfo a = new AddressInfo();


		// URL prefix to the geocoder
		String GEOCODER_REQUEST_PREFIX_FOR_XML = "where.yahooapis.com/geocode";

		// prepare a URL to the geocoder
		URL url = null;
		try
		{
			url = java.net.URI.create(GEOCODER_REQUEST_PREFIX_FOR_XML + "?q=" + URLEncoder.encode(address, "UTF-8")).toURL();
		}
		catch (MalformedURLException e1){e1.printStackTrace();return null;}
		catch (UnsupportedEncodingException e1){e1.printStackTrace();return null;}

		// prepare an HTTP connection to the geocoder
		HttpURLConnection conn = null;
		try
		{
			conn = (HttpURLConnection) url.openConnection();
		} catch (IOException e1) {e1.printStackTrace();return null;}

		Document geocoderResultDocument = null;

		try
		{
			// open the connection and get results as InputSource.
			conn.connect();
		}
		catch (IOException e1){e1.printStackTrace();return null;}

		try
		{
			InputSource geocoderResultInputSource = new InputSource(conn.getInputStream());
			// read result and parse into XML Document
			geocoderResultDocument = DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(geocoderResultInputSource);
		}
		catch (IOException e){e.printStackTrace();return null;}
		catch (SAXException e){e.printStackTrace();return null;}
		catch (ParserConfigurationException e){e.printStackTrace();return null;}
		finally{conn.disconnect();}

		// prepare XPath
		XPath xpath = XPathFactory.newInstance().newXPath();

		/*
			http://where.yahooapis.com/geocode?q=95817,%20United%20States

			<resultset xmlns:ns1=3D"http://www.yahooapis.com/v1/base.rng" version=3D"2.0f" xml:lang=3D"en-US">
			<error>0</error>
			<errormessage>No error</errormessage>
			<locale>en-US</locale>
			<found>1</found>
			<quality>60</quality>
			<result>
				<quality>60</quality>
				<latitude>38.55117</latitude>
				<longitude>-121.449264</longitude>
				<offsetlat>38.55172</offsetlat>
				<offsetlon>-121.449692</offsetlon>
				<radius>3100</radius>
				<name></name>
				<line1></line1>
				<line2>Sacramento, CA 95817</line2>
				<line3></line3>
				<line4>United States</line4>
				<house></house>
				<street></street>
				<xstreet></xstreet>
				<unittype></unittype>
				<unit></unit>
				<postal>95817</postal>
				<neighborhood></neighborhood>
				<city>Sacramento</city>
				<county>Sacramento County</county>
				<state>California</state>
				<country>United States</country>
				<countrycode>US</countrycode>
				<statecode>CA</statecode>
				<countycode></countycode>
				<uzip>95817</uzip>
				<hash></hash>
				<woeid>12798003</woeid>
				<woetype>11</woetype>
			</result>
			</resultset>


		*/


		// extract the result
		NodeList resultNodeList = null;

		//validate status
		try
		{
			resultNodeList = (NodeList) xpath.evaluate("/resultset/errormessage", geocoderResultDocument, XPathConstants.NODESET);
		}catch (XPathExpressionException e1){e1.printStackTrace();return null;}

		if(resultNodeList==null){log.debug("No errormessage in Yahoo GeoCoding API (It returned nothing?)"+geocoderResultDocument.toString());return null;}

		for(int i=0; i<resultNodeList.getLength(); ++i)
		{
			if(resultNodeList.item(i).getTextContent().equals("No error")==false)
			{
				log.debug("Error in Yahoo GeoCoding API: "+resultNodeList.item(i).getTextContent());
				return null;
			}
		}



		//get the formatted postal code
		resultNodeList = null;
		try
		{
			resultNodeList = (NodeList) xpath.evaluate("/resultset/result[1]/postal", geocoderResultDocument, XPathConstants.NODESET);
		}
		catch (XPathExpressionException e1) {e1.printStackTrace();return null;}

		if(resultNodeList==null){log.debug("No postal code in Yahoo GeoCoding API");return null;}

		for(int i=0; i<resultNodeList.getLength(); ++i)
		{
			a.postalCode = resultNodeList.item(i).getTextContent();
		}



		//get the city
		resultNodeList = null;
		try
		{
			resultNodeList = (NodeList) xpath.evaluate("/resultset/result[1]/city", geocoderResultDocument, XPathConstants.NODESET);
		}
		catch (XPathExpressionException e1) {e1.printStackTrace();return null;}

		if(resultNodeList==null){log.debug("No locality (city/placeName) in Yahoo GeoCoding API");a.placeName = "?";}

		for(int i=0; i<resultNodeList.getLength(); ++i)
		{
			a.placeName = resultNodeList.item(i).getTextContent();
		}


		//get the state
		resultNodeList = null;
		try
		{
			resultNodeList = (NodeList) xpath.evaluate("/resultset/result[1]/state", geocoderResultDocument, XPathConstants.NODESET);
		}
		catch (XPathExpressionException e1) {e1.printStackTrace();return null;}

		if(resultNodeList==null){log.debug("No state in Yahoo GeoCoding API");a.stateName = "?";}

		for(int i=0; i<resultNodeList.getLength(); ++i)
		{
			a.stateName = resultNodeList.item(i).getTextContent();
		}

		//get the lat and lon
		resultNodeList = null;
		try
		{
			resultNodeList = (NodeList) xpath.evaluate("/resultset/result[1]/latitude", geocoderResultDocument, XPathConstants.NODESET);
		}
		catch (XPathExpressionException e1){e1.printStackTrace();return null;}

		if(resultNodeList==null){log.debug("No lat in Yahoo GeoCoding API");a.stateName = "?";}

		for(int i=0; i<resultNodeList.getLength(); ++i)
		{
			try{a.lat = Float.parseFloat(resultNodeList.item(i).getTextContent());}catch(NumberFormatException ex){ex.printStackTrace();}
		}

		resultNodeList = null;
		try
		{
			resultNodeList = (NodeList) xpath.evaluate("/resultset/result[1]/longitude", geocoderResultDocument, XPathConstants.NODESET);
		}
		catch (XPathExpressionException e1){e1.printStackTrace();return null;}

		if(resultNodeList==null){log.debug("No lon in Yahoo GeoCoding API");a.stateName = "?";}

		for(int i=0; i<resultNodeList.getLength(); ++i)
		{
			try{a.lon = Float.parseFloat(resultNodeList.item(i).getTextContent());}catch(NumberFormatException ex){ex.printStackTrace();}
		}



		return a;
	}

	//=========================================================================================================================
	public AddressInfo queryGoogleGeocodingAPI(String address)
	{//=========================================================================================================================
		AddressInfo a = new AddressInfo();


		// URL prefix to the geocoder
		String GEOCODER_REQUEST_PREFIX_FOR_XML = "http://maps.google.com/maps/api/geocode/xml";

		// prepare a URL to the geocoder
		URL url = null;
		try
		{
			url = java.net.URI.create(GEOCODER_REQUEST_PREFIX_FOR_XML + "?address=" + URLEncoder.encode(address, "UTF-8") + "&sensor=false").toURL();
		}
		catch (MalformedURLException e1){e1.printStackTrace();return null;}
		catch (UnsupportedEncodingException e1){e1.printStackTrace();return null;}

		// prepare an HTTP connection to the geocoder
		HttpURLConnection conn = null;
		try
		{
			conn = (HttpURLConnection) url.openConnection();
		} catch (IOException e1) {e1.printStackTrace();return null;}

		Document geocoderResultDocument = null;

		try
		{
			// open the connection and get results as InputSource.
			conn.connect();
		}
		catch (IOException e1){e1.printStackTrace();return null;}

		try
		{
			InputSource geocoderResultInputSource = new InputSource(conn.getInputStream());
			// read result and parse into XML Document
			geocoderResultDocument = DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(geocoderResultInputSource);
		}
		catch (IOException e){e.printStackTrace();return null;}
		catch (SAXException e){e.printStackTrace();return null;}
		catch (ParserConfigurationException e){e.printStackTrace();return null;}
		finally{conn.disconnect();}

		// prepare XPath
		XPath xpath = XPathFactory.newInstance().newXPath();




		/*
			<geocoderesponse>
				<status>OK</status>

				<result>
					<address_component>
						<long_name>Sacramento</long_name>
						<short_name>Sacramento</short_name>
						<type>administrative_area_level_2</type>
						<type>political</type>
					</address_component>

					<address_component>
						<long_name>California</long_name>
						<short_name>CA</short_name>
						<type>administrative_area_level_1</type>
						<type>political</type>
					</address_component>

					<address_component>
						<long_name>95817</long_name>
						<short_name>95817</short_name>
						<type>postal_code</type>
					</address_component>

					<geometry>
						<location>
							<lat>38.5500434</lat>
							<lng>-121.4599012</lng>
						</location>
					</geometry>
				</result>

			</geocoderesponse>
		 */

		// extract the result
		NodeList resultNodeList = null;

		//validate status
		try
		{
			resultNodeList = (NodeList) xpath.evaluate("/GeocodeResponse/status", geocoderResultDocument, XPathConstants.NODESET);
		}catch (XPathExpressionException e1){e1.printStackTrace();return null;}

		if(resultNodeList==null){log.debug("No status in Google GeoCoding API (It returned nothing?)"+geocoderResultDocument.toString());return null;}

		for(int i=0; i<resultNodeList.getLength(); ++i)
		{
			if(resultNodeList.item(i).getTextContent().equals("OK")==false)
			{
				log.debug("Status Error in Google GeoCoding API: "+resultNodeList.item(i).getTextContent());
				return null;
			}
		}



		//get the formatted postal code
		resultNodeList = null;
		try
		{
			resultNodeList = (NodeList) xpath.evaluate("/GeocodeResponse/result[1]/address_component[type/text() = 'postal_code']/long_name", geocoderResultDocument, XPathConstants.NODESET);
		}
		catch (XPathExpressionException e1) {e1.printStackTrace();return null;}

		if(resultNodeList==null){log.debug("No postal code in Google GeoCoding API");return null;}

		for(int i=0; i<resultNodeList.getLength(); ++i)
		{
			a.postalCode = resultNodeList.item(i).getTextContent();
		}



		//get the city
		resultNodeList = null;
		try
		{
			resultNodeList = (NodeList) xpath.evaluate("/GeocodeResponse/result[1]/address_component[type/text() = 'locality']/long_name", geocoderResultDocument, XPathConstants.NODESET);
		}
		catch (XPathExpressionException e1) {e1.printStackTrace();return null;}

		if(resultNodeList==null){log.debug("No locality (city/placeName) in Google GeoCoding API");a.placeName = "?";}

		for(int i=0; i<resultNodeList.getLength(); ++i)
		{
			a.placeName = resultNodeList.item(i).getTextContent();
		}


		//get the state
		resultNodeList = null;
		try
		{
			resultNodeList = (NodeList) xpath.evaluate("/GeocodeResponse/result[1]/address_component[type/text() = 'administrative_area_level_1']/long_name", geocoderResultDocument, XPathConstants.NODESET);
		}
		catch (XPathExpressionException e1) {e1.printStackTrace();return null;}

		if(resultNodeList==null){log.debug("No state in Google GeoCoding API");a.stateName = "?";}

		for(int i=0; i<resultNodeList.getLength(); ++i)
		{
			a.stateName = resultNodeList.item(i).getTextContent();
		}

		//get the lat and lon
		resultNodeList = null;
		try
		{
			resultNodeList = (NodeList) xpath.evaluate("/GeocodeResponse/result[1]/geometry/location/*", geocoderResultDocument, XPathConstants.NODESET);
		}
		catch (XPathExpressionException e1){e1.printStackTrace();return null;}

		if(resultNodeList==null){log.debug("No lat/lon in Google GeoCoding API");return null;}

		for(int i=0; i<resultNodeList.getLength(); ++i)
		{
			Node node = resultNodeList.item(i);
			if("lat".equals(node.getNodeName()))try{a.lat = Float.parseFloat(node.getTextContent());}catch(NumberFormatException ex){ex.printStackTrace();}

			if("lng".equals(node.getNodeName()))try{a.lon = Float.parseFloat(node.getTextContent());}catch(NumberFormatException ex){ex.printStackTrace();}
			if("lon".equals(node.getNodeName()))try{a.lon = Float.parseFloat(node.getTextContent());}catch(NumberFormatException ex){ex.printStackTrace();}
		}




		return a;
	}

	//=========================================================================================================================
	public void doOKButton()
	{//=========================================================================================================================

		new Thread //needs to be a thread because Button.doCallback only calls Runnable.run() which does NOT create a thread
		(
			new Runnable()
			{
				public void run()
				{

					try{Thread.currentThread().setName("PlayerEditMenu_doOKButton");}catch(SecurityException e){e.printStackTrace();}

					setButtonsVisible(false);

					//make sure name is set
					errorLabel.setText(" ");
					statusLabel.setText("Validating location...");

					if(nameEditField.getText().length()==0){errorLabel.setText("Please enter a name.");return;}
					if(nameEditField.getText().contains("`")){errorLabel.setText("Name cannot contain ` ");return;}

					if(zipCodeEditField.getText().length()==0){errorLabel.setText("Please enter a Zip/Postal Code.");return;}
					if(zipCodeEditField.getText().contains("`")){errorLabel.setText("Zip/Postal Code cannot contain ` ");return;}

					//send gameSave update to server for name and styles

					//ClientMain.clientTCP.addQueuedGameSaveUpdateRequest_S("characterName:`"+nameEditField.getText()+"`");
					//Game().gameSave.characterName = nameEditField.getText();

					String characterAppearance = ""+
					genderIndex+","+
					archetypeIndex+","+
					hairColorIndex+","+
					skinColorIndex+","+
					eyeColorIndex+","+
					shirtColorIndex+","+
					pantsColorIndex+","+
					shoeColorIndex;
					Network().addQueuedGameSaveUpdateRequest_S
					(
						"characterName:`"+nameEditField.getText()+"`" +
						"," +
						"characterAppearance:`"+characterAppearance+"`"
					);
					GameSave().characterName = nameEditField.getText();
					GameSave().characterAppearance = characterAppearance;



					Player p = Player();
					if(p!=null)
					{
						p.setCharacterNameAndCaption(ClientGameEngine().getNameColor(GameSave().accountRank), nameString, ClientGameEngine().getAccountRankColor(GameSave().accountRank), ClientGameEngine().getAccountRankString(GameSave().accountRank));
					}


					boolean wasValid = true;


					if(BobNet.debugMode==false)
					{
						String countryName = countryStrings.getEntry(countryComboBox.getSelected());
						String postalCode = zipCodeEditField.getText();

						String countryCode = GameSave.getCountryCodeFromCountryString(countryName);

						//get locality info from google API
						AddressInfo a = queryGoogleGeocodingAPI(""+postalCode+", "+countryName);

						if(a==null)
						{
							//try again with yahoo
							a = queryYahooGeocodingAPI(""+postalCode+", "+countryName);
						}

						//TODO: also try open maps?


						if(a!=null)
						{
							Network().addQueuedGameSaveUpdateRequest_S
							(
									"postalCode:`"+a.postalCode+"`" +
									"," +
									"countryName:`"+countryName+"`" +
									"," +
									"isoCountryCode:`"+countryCode+"`" +
									"," +
									"stateName:`"+a.stateName+"`"+
									"," +
									"placeName:`"+a.placeName+"`"+
									"," +
									"lat:`"+a.lat+"`"+
									"," +
									"lon:`"+a.lon+"`"
							);
							GameSave().postalCode = a.postalCode;
							GameSave().countryName = countryName;
							GameSave().isoCountryCode = countryCode;
							GameSave().stateName = a.stateName;
							GameSave().placeName = a.placeName;
							GameSave().lat = a.lat;
							GameSave().lon = a.lon;
						}
						else
						{
							wasValid = false;
						}
					}

					//server side geolookup in local database:
//					{
//
//						ClientMain.clientTCP.setPostalCodeUpdateReceived_S(false);
//						ClientMain.clientTCP.setPostalCodeUpdateWasValid_S(false);
//
//						ClientMain.clientTCP.sendPostalCodeUpdateRequest(zipCodeEditField.getText(), countryStrings.getEntry(countryComboBox.getSelected()));
//
//						setButtonsVisible(false);
//
//						//wait for postal code return
//						//-------------------------------
//						//check to see if response every 1 second
//						//-------------------------------
//						int responseTries = 0;
//						boolean gotResponse = false;
//						while(gotResponse==false)
//						{
//							gotResponse = ClientMain.clientTCP.getPostalCodeUpdateReceived_S();
//
//							if(gotResponse==false)
//							{
//								responseTries++;
//								if(responseTries>5)
//								{
//									responseTries=0;
//									statusLabel.setText(" ");
//									errorLabel.setText("Error: Did not receive a response from the server.");
//
//									setButtonsVisible(true);
//
//									return;
//								}
//
//								try{Thread.sleep(1000);}catch (Exception e){e.printStackTrace();}
//							}
//						}
//
//
//						if(ClientMain.clientTCP.getPostalCodeUpdateWasValid_S()==false)
//						{
//							wasValid=false;
//							ClientMain.clientTCP.setPostalCodeUpdateReceived_S(false);
//						}
//					}



					if(wasValid==false)
					{
						statusLabel.setText(" ");
						errorLabel.setText(
								"Error: Zip/Postal Code could not be found.\n" +
								"Are you sure it is formatted correctly? Also make sure you've selected the correct Country.\n" +
								"Hint: You can also try putting your city name into the Postal Code field."
								);
						setButtonsVisible(true);

					}
					else
					{
						statusLabel.setText(" ");
						errorLabel.setText(" ");

						setButtonsVisible(true);
						setActivated(false);
					}

				}
			}
		).start();


	}

	//=========================================================================================================================
	public void linkFacebookAccount()
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


					//do we have a sessionToken already?

					String facebookAccessToken = GameSave().facebookAccessToken;
					boolean haveAccessToken = false;
					boolean accessTokenIsValid = true;

					if(facebookAccessToken.length()>0)
					{
						haveAccessToken=true;


						//check if our session token is valid
						//restFB stuff here
						FacebookClient facebookClient = null;

						//------------------------
						//log into facebook to test token
						//------------------------
						/*try
						{
							facebookClient = new DefaultFacebookClient(facebookAccessToken);
							User user = facebookClient.fetchObject("me", User.class);*/

							String facebookID = "1503421039731588"; //user.getId();
							log.debug("Facebook ID: "+facebookID);

						/*}
						catch(Exception ex)
						{
							accessTokenIsValid=false;
						}*/
					}


					//if we have facebook accessToken already, let's not bother the user


					if(haveAccessToken==false || accessTokenIsValid==false)
					{

						statusLabel.setText("Please authorize Facebook Connect in the browser window.");

						if(ClientMain.isApplet==true)
						{


							//TODO: use FB JS SDK here? don't need to do this yet.
							//can check if we are logged in and already verified though.


							//if we AREN'T authorized, the client should pop up the facebook window or load it into an iframe
							//the client will use the iframe (or javascript popup) to send a request to facebook with our app token
							//facebook redirects us back to our facebook.php which sets the accessToken in SQL.


							//check if we are logged into facebook in browser - use the JS SDK which checks our cookies i think, or we can do this with JSObject or CookieManager probably.
							//if we're not logged into facebook and we have facebook accessToken already, let's not bother the user
							//if we ARE logged into facebook and our application IS authorized, we can just automatically get a new session token by refreshing facebook.php


							//basically either way, we should just refresh the iframe to facebook.php and resize it.
							//if they've already authorized us, it should get the accessToken and hide itself.






								//open with javascript


								//TODO: have iframe redirect and expand to auth size, then remove it/resize to nothing when we are done
								//best way to do this?
								//probably have the PHP output javascript which resizes its iframe to nothing from inside, after we've got our error response or authToken.


								//$('<frame />').attr('src', 'http://example.com').attachTo('body')
								//in applet obj tag
								//<PARAM NAME="MAYSCRIPT" VALUE="true">
	//					         JSObject win = JSObject.getWindow(ClientMain.clientMain);
	//					         JSObject doc = (JSObject) win.getMember("document");
	//					         JSObject loc = (JSObject) doc.getMember("location");
	//
	//					         String s = (String) loc.getMember("href");  // document.location.href
	//					         win.call("f", null);


								//String url = "http://www.bobsgame.com/facebook.php?u="+Game().gameSave.userID;

								URL url = null;
								try
								{
									url = java.net.URI.create("http://www.bobsgame.com/facebook.php?u="+GameSave().userID).toURL();
								}
								catch (MalformedURLException e)
								{
									e.printStackTrace();
								}

                                //Applet removed
								//ClientMain.clientMain.getAppletContext().showDocument(url, "_blank");


								//TODO: pause until we have confirmation

								//could have the PHP call javascript which connects back to this applet and tells us it's done (or error)
								//could also have this check with javascript to see if the iframe has error or accessToken set.

								//could also have a pause/cancel button here.
								//or could just wait.

								try{Thread.sleep(5000);}catch (Exception e){e.printStackTrace();}

						}
						else
						{




							try
							{
								//open browser window, we can't get it with JS as a desktop client so we need to redirect to PHP or something which stores it in SQL
								String url = "http://www.bobsgame.com/facebook.php?u="+GameSave().userID;

								java.awt.Desktop.getDesktop().browse(java.net.URI.create(url));
							}
							catch (java.io.IOException e)
							{
								log.error("Could not open browser: "+e.getMessage());
							}


							//TODO: pause until we have confirmation, how to do this? ok button?
							//could also have a pause/cancel button here.
							//or could just wait.

							try{Thread.sleep(5000);}catch (Exception e){e.printStackTrace();}

						}

					}







					//if we are an applet, we can get the access token through javascript and have the server update immediately.


					//if we are a desktop app, we should just tell the server to update from the database, since the authorization happened there.
					//we could keep asking the server if we have the token yet



					statusLabel.setText("Checking to see if account was authorized. Please wait for 10 seconds...");

					//DONE: send update facebook account command
					//UpdateFacebookAccountInDB




					//TODO should do this on login if the session is still valid
					//do this on login on the server side and then send online friend list, don't even request from client.

					//refresh the session token and send to server
					Network().sendUpdateFacebookAccountInDBRequest();

					//-------------------------------
					//check to see if response every 1 second
					//-------------------------------
					int responseTries = 0;
					boolean gotResponse = false;
					while(gotResponse==false)
					{
						gotResponse = Network().getFacebookAccountUpdateResponseReceived_S();

						if(gotResponse==false)
						{
							responseTries++;
							if(responseTries>10)
							{
								responseTries=0;
								statusLabel.setText(" ");
								errorLabel.setText("Error: Did not receive a response from the server.");

								setButtonsVisible(true);

								return;
							}

							try{Thread.sleep(1000);}catch (Exception e){e.printStackTrace();}
						}
					}

					boolean wasValid =  Network().getFacebookAccountUpdateResponseWasValid_S();

					//reset the state
					Network().setFacebookAccountUpdateResponseState_S(false, false);

					if(wasValid==false)
					{
						statusLabel.setText(" ");
						errorLabel.setText("Error: Facebook session could not be validated. Please try again.");
						setButtonsVisible(true);
					}
					else
					{

						Network().sendOnlineFriendListRequest();


						statusLabel.setText(" ");
						errorLabel.setText(" ");

						setButtonsVisible(true);

						//replace the facebook button with "account linked!"
						facebookAccountLabel.setText("Facebook: Connected!");
						addFacebookAccountButton.setEnabled(false);
						addFacebookAccountButton.setVisible(false);
					}

				}
			}
		).start();



	}




	//=========================================================================================================================
	public void redrawPlayer()
	{//=========================================================================================================================

		if(isActivated()==false)return;

		nameString = nameEditField.getText();

		if(genderButtons[0].isActive())genderIndex = 0;
		else genderIndex = 1;


		archetypeIndex = archetypeComboBox.getSelected();
		shoeColorIndex = shoeColorComboBox.getSelected();
		shirtColorIndex = shirtColorComboBox.getSelected();
		pantsColorIndex = pantsColorComboBox.getSelected();
		skinColorIndex = skinColorComboBox.getSelected();
		eyeColorIndex = eyeColorComboBox.getSelected();
		hairColorIndex = hairColorComboBox.getSelected();


		Player p = Player();

		if(p!=null)
		{
			p.generateUniqueTexture(genderIndex, archetypeIndex, shoeColorIndex, shirtColorIndex, pantsColorIndex, skinColorIndex, eyeColorIndex, hairColorIndex);
			p.setCharacterNameAndCaption(ClientGameEngine().getNameColor(GameSave().accountRank), nameString, ClientGameEngine().getAccountRankColor(GameSave().accountRank), ClientGameEngine().getAccountRankString(GameSave().accountRank));
		}

	}

	//=========================================================================================================================
	public void setRandomOptions()
	{//=========================================================================================================================

		genderButtons[Utils.randLessThan(2)].setActive(true);


		archetypeComboBox.setSelected(Utils.randLessThan(archetypeStrings.getNumEntries()));
		shoeColorComboBox.setSelected(Utils.randLessThan(shoeColorStrings.getNumEntries()));
		shirtColorComboBox.setSelected(Utils.randLessThan(shirtColorStrings.getNumEntries()));
		pantsColorComboBox.setSelected(Utils.randLessThan(pantsColorStrings.getNumEntries()));
		skinColorComboBox.setSelected(Utils.randLessThan(skinColorStrings.getNumEntries()));
		eyeColorComboBox.setSelected(Utils.randLessThan(eyeColorStrings.getNumEntries()));
		hairColorComboBox.setSelected(Utils.randLessThan(hairColorStrings.getNumEntries()));

	}



	//=========================================================================================================================
	@Override
	protected void layout()
	{//=========================================================================================================================

		//edit panel is centered

		editPanel.adjustSize();
		editPanel.setPosition(
				insideScrollPaneLayout.getInnerX() + (insideScrollPaneLayout.getInnerWidth() - editPanel.getWidth()) / 2,
				insideScrollPaneLayout.getInnerY() + (insideScrollPaneLayout.getInnerHeight() - editPanel.getHeight()) / 2);

		super.layout();
	}



	//=========================================================================================================================
	public void setActivated(boolean b)
	{//=========================================================================================================================
		super.setActivated(b);

		if(b==true)
		{

			if(GameSave().characterAppearance==null||GameSave().characterAppearance.length()==0||GameSave().characterAppearance.equals(""))
			{
				setRandomOptions();
				redrawPlayer();
			}
			else
			{
				nameEditField.setText(GameSave().characterName);

				zipCodeEditField.setText(GameSave().postalCode);

				//on dialogue load, load character values from gameSave

				String s = GameSave().characterAppearance;

				try{genderIndex = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf(",")+1);
				try{archetypeIndex = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf(",")+1);
				try{hairColorIndex = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf(",")+1);
				try{skinColorIndex = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf(",")+1);
				try{eyeColorIndex = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf(",")+1);
				try{shirtColorIndex = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf(",")+1);
				try{pantsColorIndex = Integer.parseInt(s.substring(0,s.indexOf(",")));}catch(NumberFormatException ex){ex.printStackTrace();return;}
				s = s.substring(s.indexOf(",")+1);
				try{shoeColorIndex = Integer.parseInt(s);}catch(NumberFormatException ex){ex.printStackTrace();return;}

				genderButtons[genderIndex].setActive(true);
				archetypeComboBox.setSelected(archetypeIndex);
				shoeColorComboBox.setSelected(shoeColorIndex);
				shirtColorComboBox.setSelected(shirtColorIndex);
				pantsColorComboBox.setSelected(pantsColorIndex);
				skinColorComboBox.setSelected(skinColorIndex);
				eyeColorComboBox.setSelected(eyeColorIndex);
				hairColorComboBox.setSelected(hairColorIndex);

				redrawPlayer();
			}



			if(GameSave().facebookAccessToken.length()>0)
			{
				//if we have a sessionToken already, remove the facebookConnect button on load and replace with "account linked!"

				//replace the facebook button with "account linked!"
				facebookAccountLabel.setText("Facebook: Connected!");
				addFacebookAccountButton.setEnabled(false);
				addFacebookAccountButton.setVisible(false);
			}
			else
			{
				facebookAccountLabel.setText("Facebook: Not Connected");
				addFacebookAccountButton.setEnabled(true);
				addFacebookAccountButton.setVisible(true);
			}

		}

	}

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

		super.update();

		if(isScrollingDown()==true||isActivated()==false)
		{
			if(playerNameCaption!=null){playerNameCaption.deleteFadeOut(); playerNameCaption=null;}
		}
	}
	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================


		if(isScrollingDown()==true)return;
		if(isActivated()==false)return;
		if(isScrolledUp()==false)return;

		//additional rendering calls go here (after gui is drawn)

		Player p = Player();

		Texture texture = p.uniqueTexture;

		long time = System.currentTimeMillis();
		if(time-lastTime>80)
		{
			lastTime=time;
			frame++;
			if(frame>=8){frame=0;loopCount++;}

			if(loopCount>0)
			{
				loopCount=0;
				if(direction==Entity.DOWN)direction=Entity.DOWNLEFT;
				else if(direction==Entity.DOWNLEFT)direction=Entity.LEFT;
				else if(direction==Entity.LEFT)direction=Entity.UPLEFT;
				else if(direction==Entity.UPLEFT)direction=Entity.UP;
				else if(direction==Entity.UP)direction=Entity.UPRIGHT;
				else if(direction==Entity.UPRIGHT)direction=Entity.RIGHT;
				else if(direction==Entity.RIGHT)direction=Entity.DOWNRIGHT;
				else if(direction==Entity.DOWNRIGHT)direction=Entity.DOWN;
			}

		}

		int renderFrame = direction * 8 + frame;


		float drawScale = 2.0f;

		if(texture!=null)
		{

			float tx0 = 0.0f;
			float tx1 = ((float)p.sprite.w()/(float)texture.getTextureWidth());
			float ty0 = (((float)p.sprite.h())*renderFrame)/(float)texture.getTextureHeight();
			float ty1 = (((float)p.sprite.h())*(renderFrame+1))/(float)texture.getTextureHeight();

			//x0 = (float)Math.floor(screenLeft());
			//x1 = (float)Math.floor(screenRight());
			//y0 = (float)Math.floor(screenTop());
			//y1 = (float)Math.floor(screenBottom());

			float x0 = animPanel.getX() + animPanel.getWidth()/2 - p.w()*drawScale/2.0f;//LWJGLUtils.SCREEN_SIZE_X/2 - p.width()*drawScale/2.0f;
			float y0 = animPanel.getY() + animPanel.getHeight()/2 - p.h()*drawScale/2.0f;//LWJGLUtils.SCREEN_SIZE_Y/2 - p.height()*drawScale/2.0f;
			float x1 = (float) (x0+p.w()*drawScale);
			float y1 = (float) (y0+p.h()*drawScale);



			GLUtils.drawTexture(texture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,1.0f,GLUtils.FILTER_NEAREST);
		}

		//if(playerNameCaption!=null)playerNameCaption.render();


	}






}
