package com.bobsgame.net;

import java.sql.ResultSet;


import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;



//===============================================================================================
public class GameSave
{//===============================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(GameSave.class);


	public long userID=-1;
	public String userName = "";
	public String emailAddress = "";
	public String passwordHash = "";
	public int accountVerified = 0;
	public String verificationHash = "";
	public long lastPasswordResetTime = 0;
	public long accountCreatedTime = 0;
	public long accountVerifiedTime = 0;
	public long firstLoginTime = 0;
	public long lastLoginTime = 0;
	public long lastSeenTime = 0;
	public int timesLoggedIn = 0;
	public long totalTimePlayed = 0;
	public String firstIP = "";
	public String lastIP = "";

	//public String realName = "";
	//public long birthdayTime = 0;


	public String facebookID = "";
	public String facebookAccessToken = "";
	public String facebookEmail = "";
	//public String facebookBirthday = "";
	public String facebookFirstName = "";
	public String facebookLastName = "";
	public String facebookGender = "";
	//public String facebookLocale = "";
	//public Float facebookTimeZone = 0.0f;
	//public String facebookUsername = "";
	//public String facebookWebsite = "";

	//public String googlePlusID = "";
	public String postalCode = "";
	public String countryName = "";
	public String isoCountryCode = "";
	public String placeName = "";
	public String stateName = "";
	public float lat = 0;
	public float lon = 0;

	public String notes = "";
	public String warnings = "";

	public String avatarIcon = "";

	public String lastKnownRoom = "";
	public int lastKnownX = 0;
	public int lastKnownY = 0;
	public String startingRoom = "";

	public long timePlayed = 0;
	public long pixelsWalked = 0;


	public int accountRank = 0;

	public float money = 0.0f;
	public float moneyPurchased = 0.0f;


	public int realWorldTransactions = 0;
	public int inGameTransactions = 0;
	public int timesTalkedToNPCs = 0;
	public int timesTalkedToOtherPlayers = 0;
	public String characterAppearance = "";
	public String characterName = "";
	public String itemsHeld = "";
	public String itemsTotalCollected = "";
	public String itemsPurchased = "";

	public int miniGamesTimesPlayed = 0;
	public int miniGamesTimesBattled = 0;
	public int miniGamesTimesChallenged = 0;
	public int miniGamesTimesChallenger = 0;
	public int miniGamesTimesWon = 0;
	public int miniGamesTimesLost = 0;
	public int miniGamesTimesTied = 0;

	public String dialoguesDone = "";
	public String flagsSet = "";
	public String skillValues = "";





	//===============================================================================================
	public GameSave(ResultSet databaseResultSet)
	{//===============================================================================================

		try
		{

			userID = databaseResultSet.getLong("userID");
			userName = databaseResultSet.getString("userName");
			emailAddress = databaseResultSet.getString("emailAddress");
			passwordHash = databaseResultSet.getString("passwordHash");

			accountVerified = databaseResultSet.getInt("accountVerified");
			verificationHash = databaseResultSet.getString("verificationHash");
			lastPasswordResetTime = databaseResultSet.getLong("lastPasswordResetTime");
			accountCreatedTime = databaseResultSet.getLong("accountCreatedTime");
			accountVerifiedTime = databaseResultSet.getLong("accountVerifiedTime");

			firstLoginTime = databaseResultSet.getLong("firstLoginTime");
			lastLoginTime = databaseResultSet.getLong("lastLoginTime");
			lastSeenTime = databaseResultSet.getLong("lastSeenTime");
			timesLoggedIn = databaseResultSet.getInt("timesLoggedIn");
			totalTimePlayed = databaseResultSet.getLong("totalTimePlayed");
			firstIP = databaseResultSet.getString("firstIP");
			lastIP = databaseResultSet.getString("lastIP");

			//realName = databaseResultSet.getString("realName");
			//birthdayTime = databaseResultSet.getInt("birthdayTime");

			facebookID = databaseResultSet.getString("facebookID");
			facebookAccessToken = databaseResultSet.getString("facebookAccessToken");
			facebookEmail = databaseResultSet.getString("facebookEmail");
			//facebookBirthday = databaseResultSet.getString("facebookBirthday");
			facebookFirstName = databaseResultSet.getString("facebookFirstName");
			facebookLastName = databaseResultSet.getString("facebookLastName");
			facebookGender = databaseResultSet.getString("facebookGender");
			//facebookLocale = databaseResultSet.getString("facebookLocale");
			//facebookTimeZone = databaseResultSet.getFloat("facebookTimeZone");
			//facebookUsername = databaseResultSet.getString("facebookUsername");
			//facebookWebsite = databaseResultSet.getString("facebookWebsite");

			//googlePlusID = databaseResultSet.getString("googlePlusID");


			postalCode = databaseResultSet.getString("postalCode");
			countryName = databaseResultSet.getString("countryName");
			isoCountryCode = databaseResultSet.getString("isoCountryCode");
			placeName = databaseResultSet.getString("placeName");
			stateName = databaseResultSet.getString("stateName");
			lat = databaseResultSet.getFloat("lat");
			lon = databaseResultSet.getFloat("lon");


			notes = databaseResultSet.getString("notes");
			warnings = databaseResultSet.getString("warnings");

			avatarIcon = databaseResultSet.getString("avatarIcon");

			lastKnownRoom = databaseResultSet.getString("lastKnownRoom");
			lastKnownX = databaseResultSet.getInt("lastKnownX");
			lastKnownY = databaseResultSet.getInt("lastKnownY");
			startingRoom = databaseResultSet.getString("startingRoom");
			timePlayed = databaseResultSet.getLong("timePlayed");
			pixelsWalked = databaseResultSet.getLong("pixelsWalked");


			accountRank = databaseResultSet.getInt("accountRank");

			money = databaseResultSet.getInt("money");
			moneyPurchased = databaseResultSet.getInt("moneyPurchased");

			realWorldTransactions = databaseResultSet.getInt("realWorldTransactions");
			inGameTransactions = databaseResultSet.getInt("inGameTransactions");

			timesTalkedToNPCs = databaseResultSet.getInt("timesTalkedToNPCs");
			timesTalkedToOtherPlayers = databaseResultSet.getInt("timesTalkedToOtherPlayers");
			characterAppearance = databaseResultSet.getString("characterAppearance");
			characterName = databaseResultSet.getString("characterName");
			itemsHeld = databaseResultSet.getString("itemsHeld");

			itemsTotalCollected = databaseResultSet.getString("itemsTotalCollected");
			itemsPurchased = databaseResultSet.getString("itemsPurchased");

			miniGamesTimesPlayed = databaseResultSet.getInt("miniGamesTimesPlayed");
			miniGamesTimesBattled = databaseResultSet.getInt("miniGamesTimesBattled");

			miniGamesTimesChallenged = databaseResultSet.getInt("miniGamesTimesChallenged");
			miniGamesTimesChallenger = databaseResultSet.getInt("miniGamesTimesChallenger");
			miniGamesTimesWon = databaseResultSet.getInt("miniGamesTimesWon");
			miniGamesTimesLost = databaseResultSet.getInt("miniGamesTimesLost");
			miniGamesTimesTied = databaseResultSet.getInt("miniGamesTimesTied");

			dialoguesDone = databaseResultSet.getString("dialoguesDone");
			flagsSet = databaseResultSet.getString("flagsSet");
			skillValues = databaseResultSet.getString("skillValues");




			if(userName==null)userName = "";
			if(emailAddress==null)emailAddress = "";
			if(passwordHash==null)passwordHash = "";
			if(verificationHash==null)verificationHash = "";
			if(firstIP==null)firstIP = "";
			if(lastIP==null)lastIP = "";
			if(facebookID==null)facebookID = "";
			if(facebookAccessToken==null)facebookAccessToken = "";
			if(facebookEmail==null)facebookEmail = "";
			if(facebookFirstName==null)facebookFirstName = "";
			if(facebookLastName==null)facebookLastName = "";
			if(facebookGender==null)facebookGender = "";
			if(postalCode==null)postalCode = "";
			if(countryName==null)countryName = "";
			if(isoCountryCode==null)isoCountryCode = "";
			if(placeName==null)placeName = "";
			if(placeName==null)placeName = "";
			if(notes==null)notes = "";
			if(warnings==null)warnings = "";
			if(avatarIcon==null)avatarIcon = "";
			if(lastKnownRoom==null)lastKnownRoom = "";
			if(startingRoom==null)startingRoom = "";
			if(characterAppearance==null)characterAppearance = "";
			if(characterName==null)characterName = "";
			if(itemsHeld==null)itemsHeld = "";
			if(itemsTotalCollected==null)itemsTotalCollected = "";
			if(itemsPurchased==null)itemsPurchased = "";
			if(dialoguesDone==null)dialoguesDone = "";
			if(flagsSet==null)flagsSet = "";
			if(skillValues==null)skillValues = "";



		}
		catch (Exception ex)
		{
			log.error("DB ERROR:"+ex.getMessage());
		}
	}



	//===============================================================================================
	public GameSave()
	{//===============================================================================================

	}


	//===============================================================================================
	public boolean wasPlayerCreatedYet()
	{//===============================================================================================


		//if(realName.length()==0)return false;
		if(postalCode.length()==0)return false;

		//public String avatarIcon = "";

		//public String characterAppearance = "";
		//public String characterName = "";


		return true;
	}





	//===============================================================================================
	public String addOrUpdateValueToCommaSeparatedList(String list, String value)
	{//===============================================================================================

		//value looks like id:thing:time
		//131:3.2:time
		//12:-1.6:time
		//-234:false:time

		//list looks like id:thing:time,id:thing:time,

		String id = value.substring(0,value.indexOf(":"));


		if(list.contains(id+":"))
		{
			//remove the old value by looking up the id
			log.debug("original list:"+list);
			String before = "";
			if(list.indexOf(id+":")>0)before = list.substring(0,list.indexOf(id+":"));


			String after = list.substring(list.indexOf(id+":"));
			after = after.substring(after.indexOf(",")+1);

			log.debug("before:"+before);
			log.debug("after:"+after);
			list = before+after+value+",";//tack it on the end, order doesn't matter.
			log.debug("resulting list:"+list);
		}
		else
		{
			log.debug("original list:"+list);
			list = list+value+",";
			log.debug("resulting list:"+list);
		}

		return list;
	}

	//===============================================================================================
	public Object updateGameSaveValue(String variableName, String value)
	{//===============================================================================================


		//log.debug("variableName:"+variableName);
		//log.debug("value:"+value);

		if(variableName.length()==0)return null;
		if(value.length()==0)return null;


			//if(variableName.equals("userID"))						{try{userID = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return new Integer(userID);}

		//if(variableName.equals("emailAddress"))				{emailAddress = new String(value); return emailAddress;}
		//else if(variableName.equals("passwordHash"))				{passwordHash = new String(value); return passwordHash;}
		//else if(variableName.equals("accountVerified"))			{try{accountVerified = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return new Integer(accountVerified);}
		//else if(variableName.equals("verificationHash"))			{verificationHash = new String(value); return verificationHash;}
		//else if(variableName.equals("lastPasswordResetTime"))		{try{lastPasswordResetTime = Long.parseLong(value);}catch(NumberFormatException ex){return null;} return new Long(lastPasswordResetTime);}
		//else if(variableName.equals("accountCreatedTime"))			{try{accountCreatedTime = Long.parseLong(value);}catch(NumberFormatException ex){return null;} return new Long(accountCreatedTime);}
		//else if(variableName.equals("accountVerifiedTime"))		{try{accountVerifiedTime = Long.parseLong(value);}catch(NumberFormatException ex){return null;} return new Long(accountVerifiedTime);}
		//else if(variableName.equals("firstLoginTime"))				{try{firstLoginTime = Long.parseLong(value);}catch(NumberFormatException ex){return null;} return new Long(firstLoginTime);}
		//else if(variableName.equals("lastLoginTime"))					{try{lastLoginTime 	= Long.parseLong(value);}catch(NumberFormatException ex){return null;} return new Long(lastLoginTime);}
		//else if(variableName.equals("lastSeenTime"))					{try{lastSeenTime 	= Long.parseLong(value);}catch(NumberFormatException ex){return null;} return new Long(lastSeenTime);}
		//else if(variableName.equals("timesLoggedIn"))				{try{timesLoggedIn = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return new Integer(timesLoggedIn);}
		//else if(variableName.equals("firstIP"))					{firstIP = new String(value); return firstIP;}
		//else if(variableName.equals("lastIP"))						{lastIP = new String(value); return lastIP;}
		//if(variableName.equals("realName"))					{realName 	= new String(value); return realName;}
		//else if(variableName.equals("birthdayTime"))				{try{birthdayTime = Long.parseLong(value);}catch(NumberFormatException ex){return null;} return new Long(birthdayTime);}
		//else if(variableName.equals("facebookID"))					{facebookID 	= new String(value); return facebookID;}
		//else if(variableName.equals("facebookAccessToken"))		{facebookAccessToken 	= new String(value); return facebookAccessToken;}

		//else if(variableName.equals("facebookEmail"))			{facebookEmail 	= new String(value); return facebookEmail;}
		//else if(variableName.equals("facebookBirthday"))		{facebookBirthday 	= new String(value); return facebookBirthday;}
		//else if(variableName.equals("facebookFirstName"))		{facebookFirstName 	= new String(value); return facebookFirstName;}
		//else if(variableName.equals("facebookLastName"))		{facebookLastName 	= new String(value); return facebookLastName;}
		//else if(variableName.equals("facebookGender"))			{facebookGender 	= new String(value); return facebookGender;}
		//else if(variableName.equals("facebookLocale"))			{facebookLocale 	= new String(value); return facebookLocale;}
		//else if(variableName.equals("facebookTimeZone"))		{try{facebookTimeZone = Float.parseFloat(value);}catch(NumberFormatException ex){return null;} return new Float(facebookTimeZone);}
		//else if(variableName.equals("facebookUsername"))		{facebookUsername 	= new String(value); return facebookUsername;}
		//else if(variableName.equals("facebookWebsite"))			{facebookWebsite 	= new String(value); return facebookWebsite;}



		//else if(variableName.equals("googlePlusID"))				{googlePlusID 	= new String(value); return googlePlusID;}


		if(variableName.equals("postalCode"))					{postalCode = new String(value); return postalCode;}
		else if(variableName.equals("countryName"))				{countryName = new String(value); return countryName;}
		else if(variableName.equals("isoCountryCode"))				{isoCountryCode = new String(value); return isoCountryCode;}
		else if(variableName.equals("placeName"))					{placeName = new String(value); return placeName;}
		else if(variableName.equals("stateName"))					{stateName = new String(value); return stateName;}
		else if(variableName.equals("lat"))						{try{lat = Float.parseFloat(value);}catch(NumberFormatException ex){return null;} return Float.valueOf(lat);}
		else if(variableName.equals("lon"))						{try{lon = Float.parseFloat(value);}catch(NumberFormatException ex){return null;} return Float.valueOf(lon);}


		else if(variableName.equals("notes"))						{notes = new String(value); return notes;}
		else if(variableName.equals("warnings"))					{warnings = new String(value); return warnings;}

		else if(variableName.equals("avatarIcon"))					{avatarIcon = new String(value); return avatarIcon;}

		else if(variableName.equals("lastKnownRoom"))				{lastKnownRoom = new String(value); return lastKnownRoom;}
		else if(variableName.equals("lastKnownX"))					{try{lastKnownX = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return Integer.valueOf(lastKnownX);}
		else if(variableName.equals("lastKnownY"))					{try{lastKnownY = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return Integer.valueOf(lastKnownY);}
		else if(variableName.equals("startingRoom"))				{startingRoom = new String(value); return startingRoom;}
		else if(variableName.equals("timePlayed"))					{try{timePlayed = Long.parseLong(value);}catch(NumberFormatException ex){return null;} return Long.valueOf(timePlayed);}
		else if(variableName.equals("pixelsWalked"))				{try{pixelsWalked = Long.parseLong(value);}catch(NumberFormatException ex){return null;} return Long.valueOf(pixelsWalked);}


		//else if(variableName.equals("accountType"))				{try{accountType = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return new Integer(money);}
		//else if(variableName.equals("money"))						{try{money = Float.parseFloat(value);}catch(NumberFormatException ex){return null;} return new Float(money);}
		//else if(variableName.equals("moneyPurchased"))			{try{moneyPurchased = Float.parseFloat(value);}catch(NumberFormatException ex){return null;} return new Float(moneyPurchased);}
		else if(variableName.equals("realWorldTransactions"))		{try{realWorldTransactions = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return Integer.valueOf(realWorldTransactions);}
		else if(variableName.equals("inGameTransactions"))			{try{inGameTransactions = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return Integer.valueOf(inGameTransactions);}
		else if(variableName.equals("timesTalkedToNPCs"))			{try{timesTalkedToNPCs = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return Integer.valueOf(timesTalkedToNPCs);}
		else if(variableName.equals("timesTalkedToOtherPlayers"))	{try{timesTalkedToOtherPlayers = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return Integer.valueOf(timesTalkedToOtherPlayers);}
		else if(variableName.equals("characterAppearance"))		{characterAppearance = new String(value); return characterAppearance;}
		else if(variableName.equals("characterName"))				{characterName = new String(value); return characterName;}
		else if(variableName.equals("itemsHeld"))					{itemsHeld = addOrUpdateValueToCommaSeparatedList(itemsHeld, value);return itemsHeld;}
		else if(variableName.equals("itemsTotalCollected"))		{itemsTotalCollected = new String(value); return itemsTotalCollected;}
		else if(variableName.equals("itemsPurchased"))				{itemsPurchased = new String(value); return itemsPurchased;}

		else if(variableName.equals("miniGamesTimesPlayed"))		{try{miniGamesTimesPlayed = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return Integer.valueOf(miniGamesTimesPlayed);}
		else if(variableName.equals("miniGamesTimesBattled"))		{try{miniGamesTimesBattled = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return Integer.valueOf(miniGamesTimesBattled);}
		else if(variableName.equals("miniGamesTimesChallenged"))	{try{miniGamesTimesChallenged = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return Integer.valueOf(miniGamesTimesChallenged);}
		else if(variableName.equals("miniGamesTimesChallenger"))	{try{miniGamesTimesChallenger = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return Integer.valueOf(miniGamesTimesChallenger);}
		else if(variableName.equals("miniGamesTimesWon"))			{try{miniGamesTimesWon = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return Integer.valueOf(miniGamesTimesWon);}
		else if(variableName.equals("miniGamesTimesLost"))			{try{miniGamesTimesLost = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return Integer.valueOf(miniGamesTimesLost);}
		else if(variableName.equals("miniGamesTimesTied"))			{try{miniGamesTimesTied = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return Integer.valueOf(miniGamesTimesTied);}
		else if(variableName.equals("dialoguesDone"))				{dialoguesDone = addOrUpdateValueToCommaSeparatedList(dialoguesDone, value);return dialoguesDone;}
		else if(variableName.equals("flagsSet"))					{flagsSet = addOrUpdateValueToCommaSeparatedList(flagsSet, value);return flagsSet;}
		else if(variableName.equals("skillValues"))				{skillValues = addOrUpdateValueToCommaSeparatedList(skillValues, value);return skillValues;}


		return null;

	}




	//===============================================================================================
	public String encodeGameSave()
	{//===============================================================================================

		String gameSaveString =
		"userID:"+                  		"`"+userID+"`"+
		",userName:"+            			"`"+userName+"`"+
		",emailAddress:"+            		"`"+emailAddress+"`"+
		//",passwordHash:"+            		"`"+passwordHash+"`"+

		//",accountVerified:"+         	 	"`"+accountVerified+"`"+
		//",verificationHash:"+          	"`"+verificationHash+"`"+
		//",lastPasswordResetTime:"+    	"`"+lastPasswordResetTime+"`"+
		",accountCreatedTime:"+          	"`"+accountCreatedTime+"`"+
		//",accountVerifiedTime:"+    		"`"+accountVerifiedTime+"`"+

		//",firstLoginTime:"+               "`"+firstLoginTime+"`"+
		",lastLoginTime:"+                  "`"+lastLoginTime+"`"+
		//",lastSeenTime:"+                 "`"+lastSeenTime+"`"+
		",timesLoggedIn:"+           		"`"+timesLoggedIn+"`"+
		",totalTimePlayed:"+           		"`"+totalTimePlayed+"`"+
		//",firstIP:"+                 		"`"+firstIP+"`"+
		",lastIP:"+                  		"`"+lastIP+"`"+

		//",realName:"+                		"`"+realName+"`"+
		//",birthdayTime:"+               	"`"+birthdayTime+"`"+

		",facebookID:"+              		"`"+facebookID+"`"+
		",facebookAccessToken:"+            "`"+facebookAccessToken+"`"+
		",facebookEmail:"+            		"`"+facebookEmail+"`"+
		//",facebookBirthday:"+            	"`"+facebookBirthday+"`"+
		",facebookFirstName:"+            	"`"+facebookFirstName+"`"+
		",facebookLastName:"+           	"`"+facebookLastName+"`"+
		",facebookGender:"+            		"`"+facebookGender+"`"+
		//",facebookLocale:"+            		"`"+facebookLocale+"`"+
		//",facebookTimeZone:"+            	"`"+facebookTimeZone+"`"+
		//",facebookUsername:"+            	"`"+facebookUsername+"`"+
		//",facebookWebsite:"+            	"`"+facebookWebsite+"`"+


		//",googlePlusID:"+            		"`"+googlePlusID+"`"+

		",postalCode:"+                 	"`"+postalCode+"`"+
		",countryName:"+                 	"`"+countryName+"`"+
		",isoCountryCode:"+                 "`"+isoCountryCode+"`"+
		",placeName:"+                 		"`"+placeName+"`"+
		",stateName:"+                 		"`"+stateName+"`"+
		",lat:"+                 			"`"+lat+"`"+
		",lon:"+                 			"`"+lon+"`"+


		",notes:"+                   		"`"+notes+"`"+
		",warnings:"+                		"`"+warnings+"`"+

		",avatarIcon:"+              		"`"+avatarIcon+"`"+

		",lastKnownRoom:"+           		"`"+lastKnownRoom+"`"+
		",lastKnownX:"+              		"`"+lastKnownX+"`"+
		",lastKnownY:"+              		"`"+lastKnownY+"`"+
		",startingRoom:"+            		"`"+startingRoom+"`"+
		",timePlayed:"+              		"`"+timePlayed+"`"+
		",pixelsWalked:"+            		"`"+pixelsWalked+"`"+


		",accountRank:"+          			"`"+accountRank+"`"+
		",money:"+          				"`"+money+"`"+

		//",moneyPurchased:"+ 				"`"+moneyPurchased+"`"+
		//",realWorldTransactions:"+   		"`"+realWorldTransactions+"`"+
		//",inGameTransactions:"+      		"`"+inGameTransactions+"`"+
		//",timesTalkedToNPCs:"+       		"`"+timesTalkedToNPCs+"`"+
		//",timesTalkedToOtherPlayers:"+	"`"+timesTalkedToOtherPlayers+"`"+
		",characterAppearance:"+     		"`"+characterAppearance+"`"+
		",characterName:"+           		"`"+characterName+"`"+
		",itemsHeld:"+           			"`"+itemsHeld+"`"+

		",dialoguesDone:"+           		"`"+dialoguesDone+"`"+
		",flagsSet:"+           			"`"+flagsSet+"`"+
		",skillValues:"+           			"`"+skillValues+"`";




		gameSaveString+=",";

		return gameSaveString;

	}


	//===============================================================================================
	public void decodeGameSave(String s)
	{//===============================================================================================

		boolean debug = false;

//		"userID:"+                  	"`"+userID+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{userID = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("userID:"+userID);
		}

//		",userName:"+            	"`"+userName+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)userName = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("userName:"+userName);
		}

//		",emailAddress:"+            	"`"+emailAddress+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)emailAddress = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("emailAddress:"+emailAddress);
		}

//		",accountCreatedTime:"+          "`"+accountCreatedTime+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{accountCreatedTime = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("accountCreated:"+accountCreatedTime);
		}

//		",lastLoginTime:"+                  "`"+lastLoginTime+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{lastLoginTime = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("lastLoginTime:"+lastLoginTime);
		}

//		",timesLoggedIn:"+           	"`"+timesLoggedIn+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{timesLoggedIn = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("timesLoggedIn:"+timesLoggedIn);
		}


//		",totalTimePlayed:"+           	"`"+totalTimePlayed+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{totalTimePlayed = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("totalTimePlayed:"+totalTimePlayed);
		}


//		",lastIP:"+                  	"`"+lastIP+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)lastIP = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("lastIP:"+lastIP);
		}

////		",realName:"+                	"`"+realName+"`"+
//		{
//			s = s.substring(s.indexOf('`')+1);
//			String t = s.substring(0, s.indexOf('`'));
//			if(t.length()>0)realName = t;
//			s = s.substring(s.indexOf('`')+1);
//			if(debug)log.debug("realName:"+realName);
//		}
//
////		",birthdayTime:"+                "`"+birthdayTime+"`"+
//		{
//			s = s.substring(s.indexOf('`')+1);
//			String t = s.substring(0, s.indexOf('`'));
//			if(t.length()>0)try{birthdayTime = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
//			s = s.substring(s.indexOf('`')+1);
//			if(debug)log.debug("birthdayTime:"+birthdayTime);
//		}

//		",facebookID:"+              	"`"+facebookID+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)facebookID = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("facebookID:"+facebookID);
		}

//		",facebookAccessToken:"+              	"`"+facebookAccessToken+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)facebookAccessToken = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("facebookAccessToken:"+facebookAccessToken);
		}

//		",facebookEmail:"+              	"`"+facebookEmail+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)facebookEmail = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("facebookEmail:"+facebookEmail);
		}
////		",facebookBirthday:"+              	"`"+facebookBirthday+"`"+
//		{
//			s = s.substring(s.indexOf('`')+1);
//			String t = s.substring(0, s.indexOf('`'));
//			if(t.length()>0)facebookBirthday = t;
//			s = s.substring(s.indexOf('`')+1);
//			if(debug)log.debug("facebookBirthday:"+facebookBirthday);
//		}
//		",facebookFirstName:"+              	"`"+facebookFirstName+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)facebookFirstName = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("facebookFirstName:"+facebookFirstName);
		}
//		",facebookLastName:"+              	"`"+facebookLastName+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)facebookLastName = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("facebookLastName:"+facebookLastName);
		}
//		",facebookGender:"+              	"`"+facebookGender+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)facebookGender = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("facebookGender:"+facebookGender);
		}
////		",facebookLocale:"+              	"`"+facebookLocale+"`"+
//		{
//			s = s.substring(s.indexOf('`')+1);
//			String t = s.substring(0, s.indexOf('`'));
//			if(t.length()>0)facebookLocale = t;
//			s = s.substring(s.indexOf('`')+1);
//			if(debug)log.debug("facebookLocale:"+facebookLocale);
//		}
////		",facebookTimeZone:"+              	"`"+facebookTimeZone+"`"+
//		{
//			s = s.substring(s.indexOf('`')+1);
//			String t = s.substring(0, s.indexOf('`'));
//			if(t.length()>0)try{facebookTimeZone = Float.parseFloat(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
//			s = s.substring(s.indexOf('`')+1);
//			if(debug)log.debug("facebookTimeZone:"+facebookTimeZone);
//		}
////		",facebookUsername:"+              	"`"+facebookUsername+"`"+
//		{
//			s = s.substring(s.indexOf('`')+1);
//			String t = s.substring(0, s.indexOf('`'));
//			if(t.length()>0)facebookUsername = t;
//			s = s.substring(s.indexOf('`')+1);
//			if(debug)log.debug("facebookUsername:"+facebookUsername);
//		}
////		",facebookWebsite:"+              	"`"+facebookWebsite+"`"+
//		{
//			s = s.substring(s.indexOf('`')+1);
//			String t = s.substring(0, s.indexOf('`'));
//			if(t.length()>0)facebookWebsite = t;
//			s = s.substring(s.indexOf('`')+1);
//			if(debug)log.debug("facebookWebsite:"+facebookWebsite);
//		}
//
////		",googlePlusID:"+            	"`"+googlePlusID+"`"+
//		{
//			s = s.substring(s.indexOf('`')+1);
//			String t = s.substring(0, s.indexOf('`'));
//			if(t.length()>0)googlePlusID = t;
//			s = s.substring(s.indexOf('`')+1);
//			if(debug)log.debug("googlePlusID:"+googlePlusID);
//		}

//		",postalCode:"+                 "`"+postalCode+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)postalCode = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("postalCode:"+postalCode);
		}

//		",countryName:"+                 "`"+countryName+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)countryName = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("countryName:"+countryName);
		}

//		",isoCountryCode:"+                 "`"+isoCountryCode+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)isoCountryCode = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("isoCountryCode:"+isoCountryCode);
		}

//		",placeName:"+                 	"`"+placeName+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)placeName = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("placeName:"+placeName);
		}

//		",stateName:"+                 	"`"+stateName+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)stateName = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("stateName:"+stateName);
		}

//		",lat:"+                		"`"+lat+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{lat = Float.parseFloat(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("lat:"+lat);
		}
//		",lon:"+                		"`"+lon+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{lon = Float.parseFloat(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("lon:"+lon);
		}

//		",timeZone:"+                	"`"+timeZone+"`"+
//		{
//			s = s.substring(s.indexOf('`')+1);
//			String t = s.substring(0, s.indexOf('`'));
//			if(t.length()>0)try{timeZone = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
//			s = s.substring(s.indexOf('`')+1);
//			if(debug)log.debug("timeZone:"+timeZone);
//		}

//		",notes:"+                   	"`"+notes+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)notes = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("notes:"+notes);
		}

//		",warnings:"+                	"`"+warnings+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)warnings = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("warnings:"+warnings);
		}

//		",avatarIcon:"+              	"`"+avatarIcon+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)avatarIcon = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("avatarIcon:"+avatarIcon);
		}

//		",lastKnownRoom:"+           	"`"+lastKnownRoom+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)lastKnownRoom = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("lastKnownRoom:"+lastKnownRoom);
		}

//		",lastKnownX:"+              	"`"+lastKnownX+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{lastKnownX = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("lastKnownX:"+lastKnownX);
		}

//		",lastKnownY:"+              	"`"+lastKnownY+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{lastKnownY = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("lastKnownY:"+lastKnownY);
		}

//		",startingRoom:"+            	"`"+startingRoom+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)startingRoom = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("startingRoom:"+startingRoom);
		}

//		",timePlayed:"+              	"`"+timePlayed+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{timePlayed = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("timePlayed:"+timePlayed);
		}

//		",pixelsWalked:"+            	"`"+pixelsWalked+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{pixelsWalked = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("pixelsWalked:"+pixelsWalked);
		}


//		",accountRank:"+          	"`"+accountRank+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{accountRank = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("accountRank:"+accountRank);
		}

		{//money
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{money = Float.parseFloat(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("money:"+money);
		}

//		",characterAppearance:"+     	"`"+characterAppearance+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)characterAppearance = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("characterAppearance:"+characterAppearance);
		}

//		",characterName:"+           	"`"+characterName+"`"
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)characterName = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("characterName:"+characterName);
		}
		{//itemsHeld
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)itemsHeld = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("itemsHeld:"+itemsHeld);
		}
		{//dialoguesDone
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)dialoguesDone = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("dialoguesDone:"+dialoguesDone);
		}
		{//flagsSet
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)flagsSet = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("flagsSet:"+flagsSet);
		}
		{//skillValues
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)skillValues = t;
			s = s.substring(s.indexOf('`')+1);
			if(debug)log.debug("skillValues:"+skillValues);
		}



	}








	private static final java.util.Map<String, String> countryNameToCodeMap = new java.util.HashMap<>();
	private static final java.util.Map<String, String> countryCodeToNameMap = new java.util.HashMap<>();

	static {
		initCountries();
	}

	private static void c(String code, String name) {
		countryNameToCodeMap.put(name, code);
		countryCodeToNameMap.put(code, name);
	}

	private static void initCountries() {
		c("US", "United States");
		c("AD", "Andorra");
		c("AE", "United Arab Emirates");
		c("AF", "Afghanistan");
		c("AG", "Antigua and Barbuda");
		c("AI", "Anguilla");
		c("AL", "Albania");
		c("AM", "Armenia");
		c("AO", "Angola");
		c("AQ", "Antarctica");
		c("AR", "Argentina");
		c("AS", "American Samoa");
		c("AT", "Austria");
		c("AU", "Australia");
		c("AW", "Aruba");
		c("AX", "Aland Islands");
		c("AZ", "Azerbaijan");
		c("BA", "Bosnia and Herzegovina");
		c("BB", "Barbados");
		c("BD", "Bangladesh");
		c("BE", "Belgium");
		c("BF", "Burkina Faso");
		c("BG", "Bulgaria");
		c("BH", "Bahrain");
		c("BI", "Burundi");
		c("BJ", "Benin");
		c("BL", "Saint Barthelemy");
		c("BM", "Bermuda");
		c("BN", "Brunei");
		c("BO", "Bolivia");
		c("BQ", "Bonaire- Saint Eustatius and Saba");
		c("BR", "Brazil");
		c("BS", "Bahamas");
		c("BT", "Bhutan");
		c("BV", "Bouvet Island");
		c("BW", "Botswana");
		c("BY", "Belarus");
		c("BZ", "Belize");
		c("CA", "Canada");
		c("CC", "Cocos Islands");
		c("CD", "Democratic Republic of the Congo");
		c("CF", "Central African Republic");
		c("CG", "Republic of the Congo");
		c("CH", "Switzerland");
		c("CI", "Ivory Coast");
		c("CK", "Cook Islands");
		c("CL", "Chile");
		c("CM", "Cameroon");
		c("CN", "China");
		c("CO", "Colombia");
		c("CR", "Costa Rica");
		c("CU", "Cuba");
		c("CV", "Cape Verde");
		c("CW", "Curacao");
		c("CX", "Christmas Island");
		c("CY", "Cyprus");
		c("CZ", "Czech Republic");
		c("DE", "Germany");
		c("DJ", "Djibouti");
		c("DK", "Denmark");
		c("DM", "Dominica");
		c("DO", "Dominican Republic");
		c("DZ", "Algeria");
		c("EC", "Ecuador");
		c("EE", "Estonia");
		c("EG", "Egypt");
		c("EH", "Western Sahara");
		c("ER", "Eritrea");
		c("ES", "Spain");
		c("ET", "Ethiopia");
		c("FI", "Finland");
		c("FJ", "Fiji");
		c("FK", "Falkland Islands");
		c("FM", "Micronesia");
		c("FO", "Faroe Islands");
		c("FR", "France");
		c("GA", "Gabon");
		c("GB", "United Kingdom");
		c("GD", "Grenada");
		c("GE", "Georgia");
		c("GF", "French Guiana");
		c("GG", "Guernsey");
		c("GH", "Ghana");
		c("GI", "Gibraltar");
		c("GL", "Greenland");
		c("GM", "Gambia");
		c("GN", "Guinea");
		c("GP", "Guadeloupe");
		c("GQ", "Equatorial Guinea");
		c("GR", "Greece");
		c("GS", "South Georgia and the South Sandwich Islands");
		c("GT", "Guatemala");
		c("GU", "Guam");
		c("GW", "Guinea-Bissau");
		c("GY", "Guyana");
		c("HK", "Hong Kong");
		c("HM", "Heard Island and McDonald Islands");
		c("HN", "Honduras");
		c("HR", "Croatia");
		c("HT", "Haiti");
		c("HU", "Hungary");
		c("ID", "Indonesia");
		c("IE", "Ireland");
		c("IL", "Israel");
		c("IM", "Isle of Man");
		c("IN", "India");
		c("IO", "British Indian Ocean Territory");
		c("IQ", "Iraq");
		c("IR", "Iran");
		c("IS", "Iceland");
		c("IT", "Italy");
		c("JE", "Jersey");
		c("JM", "Jamaica");
		c("JO", "Jordan");
		c("JP", "Japan");
		c("KE", "Kenya");
		c("KG", "Kyrgyzstan");
		c("KH", "Cambodia");
		c("KI", "Kiribati");
		c("KM", "Comoros");
		c("KN", "Saint Kitts and Nevis");
		c("KP", "North Korea");
		c("KR", "South Korea");
		c("XK", "Kosovo");
		c("KW", "Kuwait");
		c("KY", "Cayman Islands");
		c("KZ", "Kazakhstan");
		c("LA", "Laos");
		c("LB", "Lebanon");
		c("LC", "Saint Lucia");
		c("LI", "Liechtenstein");
		c("LK", "Sri Lanka");
		c("LR", "Liberia");
		c("LS", "Lesotho");
		c("LT", "Lithuania");
		c("LU", "Luxembourg");
		c("LV", "Latvia");
		c("LY", "Libya");
		c("MA", "Morocco");
		c("MC", "Monaco");
		c("MD", "Moldova");
		c("ME", "Montenegro");
		c("MF", "Saint Martin");
		c("MG", "Madagascar");
		c("MH", "Marshall Islands");
		c("MK", "Macedonia");
		c("ML", "Mali");
		c("MM", "Myanmar");
		c("MN", "Mongolia");
		c("MO", "Macao");
		c("MP", "Northern Mariana Islands");
		c("MQ", "Martinique");
		c("MR", "Mauritania");
		c("MS", "Montserrat");
		c("MT", "Malta");
		c("MU", "Mauritius");
		c("MV", "Maldives");
		c("MW", "Malawi");
		c("MX", "Mexico");
		c("MY", "Malaysia");
		c("MZ", "Mozambique");
		c("NA", "Namibia");
		c("NC", "New Caledonia");
		c("NE", "Niger");
		c("NF", "Norfolk Island");
		c("NG", "Nigeria");
		c("NI", "Nicaragua");
		c("NL", "Netherlands");
		c("NO", "Norway");
		c("NP", "Nepal");
		c("NR", "Nauru");
		c("NU", "Niue");
		c("NZ", "New Zealand");
		c("OM", "Oman");
		c("PA", "Panama");
		c("PE", "Peru");
		c("PF", "French Polynesia");
		c("PG", "Papua New Guinea");
		c("PH", "Philippines");
		c("PK", "Pakistan");
		c("PL", "Poland");
		c("PM", "Saint Pierre and Miquelon");
		c("PN", "Pitcairn");
		c("PR", "Puerto Rico");
		c("PS", "Palestinian Territory");
		c("PT", "Portugal");
		c("PW", "Palau");
		c("PY", "Paraguay");
		c("QA", "Qatar");
		c("RE", "Reunion");
		c("RO", "Romania");
		c("RS", "Serbia");
		c("RU", "Russia");
		c("RW", "Rwanda");
		c("SA", "Saudi Arabia");
		c("SB", "Solomon Islands");
		c("SC", "Seychelles");
		c("SD", "Sudan");
		c("SS", "South Sudan");
		c("SE", "Sweden");
		c("SG", "Singapore");
		c("SH", "Saint Helena");
		c("SI", "Slovenia");
		c("SJ", "Svalbard and Jan Mayen");
		c("SK", "Slovakia");
		c("SL", "Sierra Leone");
		c("SM", "San Marino");
		c("SN", "Senegal");
		c("SO", "Somalia");
		c("SR", "Suriname");
		c("ST", "Sao Tome and Principe");
		c("SV", "El Salvador");
		c("SX", "Sint Maarten");
		c("SY", "Syria");
		c("SZ", "Swaziland");
		c("TC", "Turks and Caicos Islands");
		c("TD", "Chad");
		c("TF", "French Southern Territories");
		c("TG", "Togo");
		c("TH", "Thailand");
		c("TJ", "Tajikistan");
		c("TK", "Tokelau");
		c("TL", "East Timor");
		c("TM", "Turkmenistan");
		c("TN", "Tunisia");
		c("TO", "Tonga");
		c("TR", "Turkey");
		c("TT", "Trinidad and Tobago");
		c("TV", "Tuvalu");
		c("TW", "Taiwan");
		c("TZ", "Tanzania");
		c("UA", "Ukraine");
		c("UG", "Uganda");
		c("UM", "United States Minor Outlying Islands");
		c("UY", "Uruguay");
		c("UZ", "Uzbekistan");
		c("VA", "Vatican");
		c("VC", "Saint Vincent and the Grenadines");
		c("VE", "Venezuela");
		c("VG", "British Virgin Islands");
		c("VI", "U.S. Virgin Islands");
		c("VN", "Vietnam");
		c("VU", "Vanuatu");
		c("WF", "Wallis and Futuna");
		c("WS", "Samoa");
		c("YE", "Yemen");
		c("YT", "Mayotte");
		c("ZA", "South Africa");
		c("ZM", "Zambia");
		c("ZW", "Zimbabwe");
		c("CS", "Serbia and Montenegro");
		c("AN", "Netherlands Antilles");
	}

	static public String getCountryCodeFromCountryString(String countryString)
	{
		return countryNameToCodeMap.getOrDefault(countryString, "US");
	}

	static public String getCountryStringFromCode(String countryCode)
	{
		return countryCodeToNameMap.getOrDefault(countryCode, "United States");
	}
}
