
package com.bobsgame.net;

import java.sql.PreparedStatement;
import java.sql.ResultSet;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

//===============================================================================================
public class BobsGameRoom
{//===============================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(BobsGameRoom.class);


	public long timeStarted = 0;
	public long timeLastGotUpdate = 0;
	

	
	
	
	public String uuid = "";
	
	public String room_IsGameSequenceOrType = "";
	public String room_GameTypeName = "";
	public String room_GameTypeUUID = "";
	public String room_GameSequenceName = "";
	public String room_GameSequenceUUID = "";
	
	
	
	public String room_DifficultyName = "Beginner";
	
	public int singleplayer_RandomizeSequence = 1;
	
	public int multiplayer_NumPlayers = 0;
	public long multiplayer_HostUserID = 0;
	
	public int multiplayer_MaxPlayers = 0;
	public int multiplayer_PrivateRoom = 0;
	public int multiplayer_TournamentRoom = 0;
	public int multiplayer_AllowDifferentDifficulties = 1;
	public int multiplayer_AllowDifferentGameSequences = 1;
	
	public int endlessMode = 0;
	public int multiplayer_GameEndsWhenOnePlayerRemains = 1;
	public int multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = 1;
	public int multiplayer_DisableVSGarbage = 0;

	public float gameSpeedStart = 0.01f;
	public float gameSpeedChangeRate = 0.02f;
	public float gameSpeedMaximum = 1.0f;//can be 0.1 to 10.0 although that won't make sense
	public float levelUpMultiplier = 1.0f;//can be negative
	public float levelUpCompoundMultiplier = 1.0f;//can be negative
	
	public int multiplayer_AllowNewPlayersDuringGame = 0;
	public int multiplayer_UseTeams = 0;
	
	public float multiplayer_GarbageMultiplier = 1.0f;
	public int multiplayer_GarbageLimit = 0;
	public int multiplayer_GarbageScaleByDifficulty = 1;//scale garbage by difficulty, beginner->insane 2x, insane->beginner 0.5x, etc.
	public int multiplayer_SendGarbageTo = 0;
	
	public int floorSpinLimit = -1;
	public int totalYLockDelayLimit = -1;
	public float lockDelayDecreaseRate = 0;
	public int lockDelayMinimum = 0;
	
	public int stackWaitLimit = -1;
	public int spawnDelayLimit = -1;
	public float spawnDelayDecreaseRate = 0;
	public int spawnDelayMinimum = 0;
	public int dropDelayMinimum = 0;

	//=========================================================================================================================
	public BobsGameRoom(String s)
	{//=========================================================================================================================
		decodeRoomData(s);
	}

	//=========================================================================================================================
	public BobsGameRoom()
	{//=========================================================================================================================

	}
	
	
	//=========================================================================================================================
	public BobsGameRoom(ResultSet databaseResultSet)
	{//=========================================================================================================================
		try 
		{
			uuid = databaseResultSet.getString("uuid");
			
			room_IsGameSequenceOrType = databaseResultSet.getString("room_IsGameSequenceOrType");
			room_GameTypeName = databaseResultSet.getString("room_GameTypeName");
			room_GameTypeUUID = databaseResultSet.getString("room_GameTypeUUID");
			room_GameSequenceName = databaseResultSet.getString("room_GameSequenceName");
			room_GameSequenceUUID = databaseResultSet.getString("room_GameSequenceUUID");
			room_DifficultyName = databaseResultSet.getString("room_DifficultyName");
			
			singleplayer_RandomizeSequence = databaseResultSet.getInt("singleplayer_RandomizeSequence");
			
			
			multiplayer_NumPlayers = databaseResultSet.getInt("");
			multiplayer_HostUserID = databaseResultSet.getLong("");
			
			multiplayer_MaxPlayers = databaseResultSet.getInt("");
			multiplayer_PrivateRoom = databaseResultSet.getInt("");
			multiplayer_TournamentRoom = databaseResultSet.getInt("");
			multiplayer_AllowDifferentDifficulties = databaseResultSet.getInt("");
			multiplayer_AllowDifferentGameSequences = databaseResultSet.getInt("");
			
			endlessMode = databaseResultSet.getInt("");
			multiplayer_GameEndsWhenOnePlayerRemains = databaseResultSet.getInt("");
			multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = databaseResultSet.getInt("");
			multiplayer_DisableVSGarbage = databaseResultSet.getInt("");

			gameSpeedStart = databaseResultSet.getFloat("");
			gameSpeedChangeRate = databaseResultSet.getFloat("");
			gameSpeedMaximum = databaseResultSet.getFloat("");
			levelUpMultiplier = databaseResultSet.getFloat("");
			levelUpCompoundMultiplier = databaseResultSet.getFloat("");
			
			multiplayer_AllowNewPlayersDuringGame = databaseResultSet.getInt("");
			multiplayer_UseTeams = databaseResultSet.getInt("");
			
			multiplayer_GarbageMultiplier = databaseResultSet.getFloat("");
			multiplayer_GarbageLimit = databaseResultSet.getInt("");
			multiplayer_GarbageScaleByDifficulty = databaseResultSet.getInt("");
			multiplayer_SendGarbageTo = databaseResultSet.getInt("");
			
			floorSpinLimit = databaseResultSet.getInt("");
			totalYLockDelayLimit = databaseResultSet.getInt("");
			lockDelayDecreaseRate = databaseResultSet.getFloat("");
			lockDelayMinimum = databaseResultSet.getInt("");
			
			stackWaitLimit = databaseResultSet.getInt("");
			spawnDelayLimit = databaseResultSet.getInt("");
			spawnDelayDecreaseRate = databaseResultSet.getFloat("");
			spawnDelayMinimum = databaseResultSet.getInt("");
			dropDelayMinimum = databaseResultSet.getInt("");
			
			

			if(uuid==null)uuid = "";	
			if(room_IsGameSequenceOrType==null)room_IsGameSequenceOrType = "";	
			if(room_GameTypeName==null)room_GameTypeName = "";	
			if(room_GameTypeUUID==null)room_GameTypeUUID = "";	
			if(room_GameSequenceName==null)room_GameSequenceName = "";	
			if(room_GameSequenceUUID==null)room_GameSequenceUUID = "";	
			if(room_DifficultyName==null)room_DifficultyName = "";		
			
		}
		catch (Exception ex)
		{
			log.error("DB ERROR:"+ex.getMessage());
		}
	}
	
	//=========================================================================================================================
	public String getDBVariables()
	{//=========================================================================================================================

		return 
		"room_IsGameSequenceOrType, " +
		"room_GameTypeName, " +
		"room_GameTypeUUID, " +
		"room_GameSequenceName, " +
		"room_GameSequenceUUID, " +
		
		"room_DifficultyName, " +
		"singleplayer_RandomizeSequence, " +
		"multiplayer_NumPlayers, " +
		"multiplayer_HostUserID, " +
		"multiplayer_MaxPlayers, " +
		
		"multiplayer_PrivateRoom, " +
		"multiplayer_TournamentRoom, " +
		"multiplayer_AllowDifferentDifficulties, " +
		"multiplayer_AllowDifferentGameSequences, " +
		"endlessMode, " +
		
		"multiplayer_GameEndsWhenOnePlayerRemains, " +
		"multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel, " +
		"multiplayer_DisableVSGarbage, " +
		"gameSpeedStart, " +
		"gameSpeedChangeRate, " +
		
		"gameSpeedMaximum, " +
		"levelUpMultiplier, " +
		"levelUpCompoundMultiplier, " +
		"multiplayer_AllowNewPlayersDuringGame, " +
		"multiplayer_UseTeams, " +
		
		"multiplayer_GarbageMultiplier, " +
		"multiplayer_GarbageLimit, " +
		"multiplayer_GarbageScaleByDifficulty, " +
		"multiplayer_SendGarbageTo, " +
		"floorSpinLimit, " +
		
		"totalYLockDelayLimit, " +
		"lockDelayDecreaseRate, " +
		"lockDelayMinimum, " +
		"stackWaitLimit, " +
		"spawnDelayLimit, " +
		
		"spawnDelayDecreaseRate, " +
		"spawnDelayMinimum, " +
		"dropDelayMinimum "
		;
	}
	
	//=========================================================================================================================
	public String getDBQuestionMarks()
	{//=========================================================================================================================
		
		return 
				"?, ?, ?, ?, ?, " +
				"?, ?, ?, ?, ?, " +
				"?, ?, ?, ?, ?, " +
				"?, ?, ?, ?, ?, " +
				"?, ?, ?, ?, ?, " +
				"?, ?, ?, ?, ?, " +
				"?, ?, ?, ?, ?, " +
				"?, ?, ? "
				;
	}
	
	//=========================================================================================================================
	public void setDBPreparedStatementVariables(int c,PreparedStatement ps)
	{//=========================================================================================================================
			
		try
		{
			ps.setString(c++,room_IsGameSequenceOrType);
			ps.setString(c++,room_GameTypeName);
			ps.setString(c++,room_GameTypeUUID);
			ps.setString(c++,room_GameSequenceName);
			ps.setString(c++,room_GameSequenceUUID);
			
			ps.setString(c++,room_DifficultyName);
			ps.setInt(c++,singleplayer_RandomizeSequence);
			ps.setInt(c++,multiplayer_NumPlayers);
			ps.setLong(c++,multiplayer_HostUserID);
			ps.setInt(c++,multiplayer_MaxPlayers);
			
			ps.setInt(c++,multiplayer_PrivateRoom);
			ps.setInt(c++,multiplayer_TournamentRoom);
			ps.setInt(c++,multiplayer_AllowDifferentDifficulties);
			ps.setInt(c++,multiplayer_AllowDifferentGameSequences);
			ps.setInt(c++,endlessMode);
			
			ps.setInt(c++,multiplayer_GameEndsWhenOnePlayerRemains);
			ps.setInt(c++,multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel);
			ps.setInt(c++,multiplayer_DisableVSGarbage);
			ps.setFloat(c++,gameSpeedStart);
			ps.setFloat(c++,gameSpeedChangeRate);
			
			ps.setFloat(c++,gameSpeedMaximum);
			ps.setFloat(c++,levelUpMultiplier);
			ps.setFloat(c++,levelUpCompoundMultiplier);
			ps.setInt(c++,multiplayer_AllowNewPlayersDuringGame);
			ps.setInt(c++,multiplayer_UseTeams);
			
			ps.setFloat(c++,multiplayer_GarbageMultiplier);
			ps.setInt(c++,multiplayer_GarbageLimit);
			ps.setInt(c++,multiplayer_GarbageScaleByDifficulty);
			ps.setInt(c++,multiplayer_SendGarbageTo);
			ps.setInt(c++,floorSpinLimit);
			
			ps.setInt(c++,totalYLockDelayLimit);
			ps.setFloat(c++,lockDelayDecreaseRate);
			ps.setInt(c++,lockDelayMinimum);
			ps.setInt(c++,stackWaitLimit);
			ps.setInt(c++,spawnDelayLimit);
			
			ps.setFloat(c++,spawnDelayDecreaseRate);
			ps.setInt(c++,spawnDelayMinimum);
			ps.setInt(c++,dropDelayMinimum);
		}
		catch (Exception ex){System.err.println("DB ERROR: "+ex.getMessage());}

	}
	
	
	//=========================================================================================================================
	public boolean isDefaultSettings()
	{//=========================================================================================================================

		BobsGameRoom r = new BobsGameRoom();

		boolean changed = false;
		if(this.gameSpeedStart != r.gameSpeedStart) {log.error("gameSpeedStart "+this.gameSpeedStart+" "+r.gameSpeedStart);changed = true;}
		if(this.gameSpeedChangeRate != r.gameSpeedChangeRate)  {log.error("gameSpeedChangeRate "+this.gameSpeedChangeRate+" "+r.gameSpeedChangeRate);changed = true;}
		if(this.gameSpeedMaximum != r.gameSpeedMaximum) {log.error("gameSpeedMaximum "+this.gameSpeedMaximum+" "+r.gameSpeedMaximum);changed = true;}
		if(this.levelUpMultiplier != r.levelUpMultiplier) {log.error("levelUpMultiplier "+this.levelUpMultiplier+" "+r.levelUpMultiplier);changed = true;}
		if(this.levelUpCompoundMultiplier != r.levelUpCompoundMultiplier) {log.error("levelUpCompoundMultiplier "+this.levelUpCompoundMultiplier+" "+r.levelUpCompoundMultiplier);changed = true;}
		if(this.multiplayer_AllowNewPlayersDuringGame != r.multiplayer_AllowNewPlayersDuringGame) {log.error("multiplayer_AllowNewPlayersDuringGame "+this.multiplayer_AllowNewPlayersDuringGame+" "+r.multiplayer_AllowNewPlayersDuringGame);changed = true;}
		if(this.multiplayer_UseTeams != r.multiplayer_UseTeams) {log.error("multiplayer_UseTeams "+this.multiplayer_UseTeams+" "+r.multiplayer_UseTeams);changed = true;}
		if(this.multiplayer_GarbageMultiplier != r.multiplayer_GarbageMultiplier) {log.error("multiplayer_GarbageMultiplier "+this.multiplayer_GarbageMultiplier+" "+r.multiplayer_GarbageMultiplier);changed = true;}
		if(this.multiplayer_GarbageLimit != r.multiplayer_GarbageLimit) {log.error("multiplayer_GarbageLimit"+this.multiplayer_GarbageLimit+" "+r.multiplayer_GarbageLimit);changed = true;}
		if(this.multiplayer_GarbageScaleByDifficulty != r.multiplayer_GarbageScaleByDifficulty) {log.error("multiplayer_GarbageScaleByDifficulty"+this.multiplayer_GarbageScaleByDifficulty+" "+r.multiplayer_GarbageScaleByDifficulty);changed = true;}
		if(this.multiplayer_SendGarbageTo != r.multiplayer_SendGarbageTo) {log.error("multiplayer_SendGarbageTo"+this.multiplayer_SendGarbageTo+" "+r.multiplayer_SendGarbageTo);changed = true;}
		if(this.floorSpinLimit != r.floorSpinLimit) {log.error("floorSpinLimit"+this.floorSpinLimit+" "+r.floorSpinLimit);changed = true;}
		if(this.totalYLockDelayLimit != r.totalYLockDelayLimit) {log.error("totalYLockDelayLimit"+this.totalYLockDelayLimit+" "+r.totalYLockDelayLimit);changed = true;}
		if(this.lockDelayDecreaseRate != r.lockDelayDecreaseRate) {log.error("lockDelayDecreaseRate"+this.lockDelayDecreaseRate+" "+r.lockDelayDecreaseRate);changed = true;}
		if(this.lockDelayMinimum != r.lockDelayMinimum) {log.error("lockDelayMinimum"+this.lockDelayMinimum+" "+r.lockDelayMinimum);changed = true;}
		if(this.stackWaitLimit != r.stackWaitLimit) {log.error("stackWaitLimit"+this.stackWaitLimit+" "+r.stackWaitLimit);changed = true;}
		if(this.spawnDelayLimit != r.spawnDelayLimit) {log.error("spawnDelayLimit"+this.spawnDelayLimit+" "+r.spawnDelayLimit);changed = true;}
		if(this.spawnDelayDecreaseRate != r.spawnDelayDecreaseRate) {log.error("spawnDelayDecreaseRate"+this.spawnDelayDecreaseRate+" "+r.spawnDelayDecreaseRate);changed = true;}
		if(this.spawnDelayMinimum != r.spawnDelayMinimum) {log.error("spawnDelayMinimum"+this.spawnDelayMinimum+" "+r.spawnDelayMinimum);changed = true;}
		if(this.dropDelayMinimum != r.dropDelayMinimum) {log.error("dropDelayMinimum"+this.dropDelayMinimum+" "+r.dropDelayMinimum);changed = true;}

		if(changed)return false;
		return true;
	}
	
	
	//=========================================================================================================================
	public String encodeRoomData()
	{//=========================================================================================================================

	//hostUserID,roomUUID,`gameSequenceOrTypeName`,isGameSequenceOrType,gameSequenceOrTypeUUID,usersInRoom,maxUsers,private,tournament,multiplayerOptions,
		String s =
			multiplayer_HostUserID +
			"," + uuid;


		s += ","+	room_IsGameSequenceOrType;
		s += ",`" + room_GameTypeName + "`";
		s += "," + 	room_GameTypeUUID;
		s += ",`" + room_GameSequenceName + "`";
		s += "," + 	room_GameSequenceUUID;
		s += "," + room_DifficultyName;




		s+=

			"," + multiplayer_NumPlayers +
			"," + multiplayer_MaxPlayers +
			"," + multiplayer_PrivateRoom +
			"," + multiplayer_TournamentRoom +
			
			"," + endlessMode +
			"," + multiplayer_AllowDifferentDifficulties +
			"," + multiplayer_AllowDifferentGameSequences +
			"," + multiplayer_GameEndsWhenOnePlayerRemains +
			"," + multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel +
			"," + multiplayer_DisableVSGarbage +

			"," + (gameSpeedStart) +
			"," + (gameSpeedChangeRate) +
			"," + (gameSpeedMaximum) +
			"," + (levelUpMultiplier) +
			"," + (levelUpCompoundMultiplier) +
			"," + (multiplayer_AllowNewPlayersDuringGame) +
			"," + (multiplayer_UseTeams) +
			"," + (multiplayer_GarbageMultiplier) +
			"," + (multiplayer_GarbageLimit) +
			"," + (multiplayer_GarbageScaleByDifficulty) +
			"," + (multiplayer_SendGarbageTo) +
			"," + (floorSpinLimit) +
			"," + (totalYLockDelayLimit) +
			"," + (lockDelayDecreaseRate) +
			"," + (lockDelayMinimum) +
			"," + (stackWaitLimit) +

			"," + (spawnDelayLimit) +
			"," + (spawnDelayDecreaseRate) +
			"," + (spawnDelayMinimum) +
			"," + (dropDelayMinimum) +


			",";


		return s;
	}

//	
//	//=========================================================================================================================
//	public BobsGameRoom decodeRoomData(String s)
//	{//=========================================================================================================================
//
//		BobsGameRoom room = new BobsGameRoom();
//		room.decodeRoomData(s);
//	}
//	
	//=========================================================================================================================
	public void decodeRoomData(String s)
	{//=========================================================================================================================


		String hostUserIDString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		uuid = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		
		
		room_IsGameSequenceOrType = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		
		s = s.substring(s.indexOf("`") + 1);
		room_GameTypeName = s.substring(0, s.indexOf("`"));
		s = s.substring(s.indexOf("`") + 1);
		s = s.substring(s.indexOf(",") + 1);
		
		room_GameTypeUUID = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		
		s = s.substring(s.indexOf("`") + 1);
		room_GameSequenceName = s.substring(0, s.indexOf("`"));
		s = s.substring(s.indexOf("`") + 1);
		s = s.substring(s.indexOf(",") + 1);
		
		room_GameSequenceUUID = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		
		room_DifficultyName = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		
		
		String playersString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String maxPlayersString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String privateRoomString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String tournamentRoomString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);






		String endlessModeString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);


		String multiplayer_AllowDifferentDifficultiesString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String multiplayer_AllowDifferentGameSequencesString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String multiplayer_GameEndsWhenAllOpponentsLoseString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String multiplayer_GameEndsWhenSomeoneCompletesCreditsLevelString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String multiplayer_DisableVSGarbageString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);




		String gameSpeedStartString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String gameSpeedIncreaseRateString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String gameSpeedMaximumString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String levelUpMultiplierString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String levelUpCompoundMultiplierString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String multiplayer_AllowNewPlayersDuringGameString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String multiplayer_UseTeamsString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String multiplayer_GarbageMultiplierString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String multiplayer_GarbageLimitString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String multiplayer_GarbageScaleByDifficultyString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String multiplayer_SendGarbageToString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String multiplayer_FloorSpinLimitString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		
		String multiplayer_LockDelayLimitString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		
		String multiplayer_LockDelayDecreaseMultiplierString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);

		String multiplayer_LockDelayMinimumString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);
		String multiplayer_StackWaitLimitString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);


		String multiplayer_SpawnDelayLimitString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);



		String multiplayer_SpawnDelayDecreaseRateString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);

		String multiplayer_SpawnDelayMinimumString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);

		String multiplayer_DropDelayMinimumString = s.substring(0, s.indexOf(","));
		s = s.substring(s.indexOf(",") + 1);



		try
		{
			multiplayer_HostUserID = Integer.parseInt(hostUserIDString);
		}
		catch (Exception e)
		{
			log.error("hostUserID could not be parsed");
			e.printStackTrace();
		}

		try
		{
			multiplayer_NumPlayers = Integer.parseInt(playersString);
		}
		catch (Exception e)
		{
			log.error("numPlayers could not be parsed");
			
		}

		try
		{
			multiplayer_MaxPlayers = Integer.parseInt(maxPlayersString);
		}
		catch (Exception e)
		{
			log.error("Could not parse maxPlayers");
		}

		try
		{
			multiplayer_PrivateRoom = Integer.parseInt(privateRoomString);
		}
		catch (Exception e)
		{
			log.error("Could not parse privateRoom");

		}

		try
		{
			multiplayer_TournamentRoom = Integer.parseInt(tournamentRoomString);
		}
		catch (Exception e)
		{
			log.error("Could not parse tournamentRoom");

		}




		try
		{
			endlessMode = Integer.parseInt(endlessModeString);
		}
		catch (Exception e)
		{
			log.error("Could not parse endlessMode");
			//return null;
		}


		try
		{
			multiplayer_AllowDifferentDifficulties = Integer.parseInt(multiplayer_AllowDifferentDifficultiesString);
		}
		catch (Exception e)
		{
			log.error("Could not parse multiplayer_AllowDifferentDifficulties");
			//return null;
		}



		try
		{
			multiplayer_AllowDifferentGameSequences = Integer.parseInt(multiplayer_AllowDifferentGameSequencesString);
		}
		catch (Exception e)
		{
			log.error("Could not parse multiplayer_AllowDifferentGameSequences");
			//return null;
		}

		try
		{
			multiplayer_GameEndsWhenOnePlayerRemains = Integer.parseInt(multiplayer_GameEndsWhenAllOpponentsLoseString);
		}
		catch (Exception e)
		{
			log.error("Could not parse multiplayer_GameEndsWhenAllOpponentsLose");
			//return null;
		}

		try
		{
			multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = Integer.parseInt(multiplayer_GameEndsWhenSomeoneCompletesCreditsLevelString);
		}
		catch (Exception e)
		{
			log.error("Could not parse multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel");
			//return null;
		}

		try
		{
			multiplayer_DisableVSGarbage = Integer.parseInt(multiplayer_DisableVSGarbageString);
		}
		catch (Exception e)
		{
			log.error("Could not parse multiplayer_DisableVSGarbage");
			//return null;
		}

		
		try
		{
			gameSpeedStart							 = Float.parseFloat(gameSpeedStartString);
		}
		catch (Exception e)
		{
			log.error("Could not parse gameSpeedStart");
			//return null;
		}
		
		try
		{
			gameSpeedChangeRate					 = Float.parseFloat(gameSpeedIncreaseRateString);
		}
		catch (Exception e)
		{
			log.error("Could not parse gameSpeedIncreaseRate");
			//return null;
		}
		
		try
		{
			gameSpeedMaximum						 = Float.parseFloat(gameSpeedMaximumString);
		}
		catch (Exception e)
		{
			log.error("Could not parse gameSpeedMaximum");
			//return null;
		}
		
		try
		{
			levelUpMultiplier						 = Float.parseFloat(levelUpMultiplierString);
		}
		catch (Exception e)
		{
			log.error("Could not parse levelUpMultiplier");
			//return null;
		}
		
		try
		{
			levelUpCompoundMultiplier				 = Float.parseFloat(levelUpCompoundMultiplierString);
		}
		catch (Exception e)
		{
			log.error("Could not parse levelUpCompoundMultiplier");
			//return null;
		}

		try
		{
			multiplayer_AllowNewPlayersDuringGame	 = Integer.parseInt(multiplayer_AllowNewPlayersDuringGameString);
		}
		catch (Exception e)
		{
			log.error("Could not parse multiplayer_AllowNewPlayersDuringGame");
			//return null;
		}

		try
		{
			multiplayer_UseTeams					 = Integer.parseInt(multiplayer_UseTeamsString);
		}
		catch (Exception e)
		{
			log.error("Could not parse multiplayer_UseTeams");
			//return null;
		}

		try
		{
			multiplayer_GarbageMultiplier			 = Float.parseFloat(multiplayer_GarbageMultiplierString);
		}
		catch (Exception e)
		{
			log.error("Could not parse multiplayer_GarbageMultiplier");
			//return null;
		}
		
		try
		{
			multiplayer_GarbageLimit				 = Integer.parseInt(multiplayer_GarbageLimitString);
		}
		catch (Exception e)
		{
			log.error("Could not parse multiplayer_GarbageLimit");
			//return null;
		}
		
		try
		{
			multiplayer_GarbageScaleByDifficulty	 = Integer.parseInt(multiplayer_GarbageScaleByDifficultyString);
		}
		catch (Exception e)
		{
			log.error("Could not parse multiplayer_GarbageScaleByDifficulty");
			//return null;
		}
		
		try
		{
			multiplayer_SendGarbageTo				 = Integer.parseInt(multiplayer_SendGarbageToString);
		}
		catch (Exception e)
		{
			log.error("Could not parse multiplayer_SendGarbageTo");
			//return null;
		}
		
		try
		{
			floorSpinLimit				 = Integer.parseInt(multiplayer_FloorSpinLimitString);
		}
		catch (Exception e)
		{
			log.error("Could not parse floorSpinLimit");
			//return null;
		}
		
		try
		{
			//if(multiplayer_LockDelayLimitString.equals("-1")) {newRoom.lockDelayLimit=-1;}
			//else
			totalYLockDelayLimit				 = Integer.parseInt(multiplayer_LockDelayLimitString);
		}
		catch (Exception e)
		{
			log.error("Could not parse lockDelayLimit");
			//return null;
		}
		
		
		try
		{
			lockDelayDecreaseRate	 = Float.parseFloat(multiplayer_LockDelayDecreaseMultiplierString);
		}
		catch (Exception e)
		{
			log.error("Could not parse lockDelayDecreaseMultiplier");
			//return null;
		}
		

		try
		{
			lockDelayMinimum			 = Integer.parseInt(multiplayer_LockDelayMinimumString);
		}
		catch (Exception e)
		{
			log.error("Could not parse lockDelayMinimum");
			//return null;
		}
		
		
		try
		{
			stackWaitLimit				 = Integer.parseInt(multiplayer_StackWaitLimitString);
		}
		catch (Exception e)
		{
			log.error("Could not parse stackWaitLimit");
			//return null;
		}
		
		
		try
		{
			spawnDelayLimit			 	 = Integer.parseInt(multiplayer_SpawnDelayLimitString);
		}
		catch (Exception e)
		{
			log.error("Could not parse spawnDelayLimit");
			//return null;
		}
		
		try
		{
			spawnDelayDecreaseRate		 = Float.parseFloat(multiplayer_SpawnDelayDecreaseRateString);
		}
		catch (Exception e)
		{
			log.error("Could not parse spawnDelayDecreaseRate");
			//return null;
		}
		
		try
		{
			spawnDelayMinimum			 = Integer.parseInt(multiplayer_SpawnDelayMinimumString);
		}
		catch (Exception e)
		{
			log.error("Could not parse spawnDelayMinimum");
			//return null;
		}
		
		
		try
		{
			//if(multiplayer_DropDelayMinimumString.equals("-1")) {newRoom.dropDelayMinimum=-1;}
			//else
			dropDelayMinimum			 = Integer.parseInt(multiplayer_DropDelayMinimumString);
		}
		catch (Exception e)
		{
			log.error("Could not parse dropDelayMinimum");
			//return null;
		}
		
		

	}




};



