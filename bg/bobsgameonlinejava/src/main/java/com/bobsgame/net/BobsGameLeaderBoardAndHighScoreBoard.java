package com.bobsgame.net;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

import org.slf4j.LoggerFactory;


import ch.qos.logback.classic.Logger;






//===============================================================================================
//leaderboard shows the top 10 users ranked by elo score or planeswalkerpoints
//high score board shows the top 10 scores by time lasted or some other metric, blocks made, blocks cleared?
//TODO:might have to add timeSpentSpinningAtBottom and subtract that
public class BobsGameLeaderBoardAndHighScoreBoard
{//===============================================================================================




	public static class LeaderBoardScore
	{

		public double newEloScoreForThisGameAndDifficulty = 0;
		public long newPlaneswalkerPointsForThisGameAndDifficulty = 0;

		//this can't be done unless i tally all the elo scores for each userHighScore entry for a game
		public double newEloScoreForThisGame = 0;
		public long newPlaneswalkerPointsForThisGame = 0;

		//this is possible because it's contained in overall user stats
		public double newEloScoreForThisDifficulty = 0;
		public long newPlaneswalkerPointsForThisDifficulty = 0;

		public double newEloScoreOverall = 0;
		public long newPlaneswalkerPointsOverall = 0;




		public long totalTimePlayedThisGameAndDifficulty = 0;
		public long totalBlocksClearedThisGameAndDifficulty = 0;

		public long totalTimePlayedThisGame = 0;
		public long totalBlocksClearedThisGame = 0;

		public long totalTimePlayedThisDifficulty = 0;
		public long totalBlocksClearedThisDifficulty = 0;

		public long totalTimePlayedOverall = 0;
		public long totalBlocksClearedOverall = 0;


		public int mostBlocksClearedThisGameAndDifficulty = 0;
		public long longestTimeLastedThisGameAndDifficulty = 0;
		public long fastestTimeClearedThisGameAndDifficulty = 0;
	}


	public static Logger log = (Logger) LoggerFactory.getLogger(BobsGameLeaderBoardAndHighScoreBoard.class);


	public String isGameSequenceOrType = "";
	public String gameTypeName = "";
	public String gameTypeUUID = "";
	public String gameSequenceName = "";
	public String gameSequenceUUID = "";
	public String difficultyName = "";
	public String objectiveString = "";



	public class BobsGameLeaderBoardAndHighScoreBoardEntry
	{

		public String userName = "";
		public long userID = -1;

		//elo score should handle most of this
		public int totalGamesPlayed = 0;
		public int singlePlayerGamesPlayed = 0;
		public int tournamentGamesPlayed = 0;
		public int localMultiplayerGamesPlayed = 0;
		public int tournamentGamesWon = 0;
		public int tournamentGamesLost = 0;
		public int singlePlayerGamesCompleted = 0;
		public int singlePlayerGamesLost = 0;
		public int singlePlayerHighestLevelReached = 0;
		public long totalTimePlayed = 0;
		public long longestGameLength = 0;
		public long fastestClearedLength = 0;
		public long firstTimePlayed = 0;
		public long lastTimePlayed = 0;
		public long timeRecordSet = 0;
		public double eloScore = 0;
		public long planesWalkerPoints = 0;
		public long totalBlocksCleared = 0;
		public int biggestCombo = 0;
		public int mostBlocksClearedInOneGame = 0;
		public String statsUUID = "";


	}

	ArrayList<BobsGameLeaderBoardAndHighScoreBoardEntry> entries = new ArrayList<BobsGameLeaderBoardAndHighScoreBoardEntry>();

	int maxEntries = 20;







	//===============================================================================================
	public BobsGameLeaderBoardAndHighScoreBoard()
	{//===============================================================================================

		for(int i=0;i<maxEntries;i++)
		{
			entries.add(new BobsGameLeaderBoardAndHighScoreBoardEntry());
		}

	}

	//===============================================================================================
	static public BobsGameLeaderBoardAndHighScoreBoard getFromDBOrCreateNewIfNotExist(Connection databaseConnection, String databaseName, BobsGameGameStats game, boolean anyGame, boolean anyDifficulty)
	{//===============================================================================================

		BobsGameLeaderBoardAndHighScoreBoard stats = null;
		{

			String gameTypeOrSequenceQueryString = "";
			String uuid = "";
			if(game.isGameSequenceOrType.equals("GameType"))
			{
				gameTypeOrSequenceQueryString = "gameTypeUUID = ?";
				uuid = game.gameTypeUUID;
			}

			if(game.isGameSequenceOrType.equals("GameSequence"))
			{
				gameTypeOrSequenceQueryString = "gameSequenceUUID = ?";
				uuid = game.gameSequenceUUID;
			}

			if(anyGame)
			{
				gameTypeOrSequenceQueryString = "isGameTypeOrSequence = ?";
				uuid = "OVERALL";
			}
			
			String difficultyName = game.difficultyName;
			if(anyDifficulty)
			{
				difficultyName = "OVERALL";
			}

			String objectiveString = "Play To Credits";
			if(game.room.endlessMode==1)
			{
				objectiveString = "Endless Mode";
			}

			ResultSet resultSet = null;
			PreparedStatement ps = null;

			try
			{
				ps = databaseConnection.prepareStatement(
						"SELECT " +
						"* " +
						"FROM "+databaseName+" WHERE "+gameTypeOrSequenceQueryString+" AND difficultyName = ? AND objectiveString = ?");


				int n = 0;
				ps.setString(++n, uuid);
				ps.setString(++n, difficultyName);
				ps.setString(++n, objectiveString);
				resultSet = ps.executeQuery();

				if(resultSet.next())
				{
					stats = new BobsGameLeaderBoardAndHighScoreBoard(resultSet);
				}

				resultSet.close();
				ps.close();

			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();return null;}
		}

		//create it if it doesnt exist
		if(stats==null)
		{
			stats = new BobsGameLeaderBoardAndHighScoreBoard();
			stats.isGameSequenceOrType = game.isGameSequenceOrType;
		
			stats.gameTypeUUID = game.gameTypeUUID;
			stats.gameTypeName = game.gameTypeName;
			stats.gameSequenceUUID = game.gameSequenceUUID;
			stats.gameSequenceName = game.gameSequenceName;
			
						
			stats.difficultyName = game.difficultyName;
			
			stats.objectiveString = "Play To Credits";
			if(game.room.endlessMode == 1)
			{
				stats.objectiveString = "Endless Mode";
			}


			if(anyGame)
			{
				stats.isGameSequenceOrType = "OVERALL";
				stats.gameTypeUUID = "OVERALL";
				stats.gameTypeName = "OVERALL";
				stats.gameSequenceUUID = "OVERALL";
				stats.gameSequenceName = "OVERALL";
			}

			if(anyDifficulty)
			{
				stats.difficultyName = "OVERALL";
			}

			stats.initDB(databaseConnection,databaseName);
		}

		return stats;
	}


	//===============================================================================================
	public static ArrayList<BobsGameLeaderBoardAndHighScoreBoard> getAllLeaderBoardsAndHighScoreBoardsFromDB(Connection databaseConnection, String databaseName)
	{//===============================================================================================

		ArrayList<BobsGameLeaderBoardAndHighScoreBoard> leaderBoards = new ArrayList<BobsGameLeaderBoardAndHighScoreBoard>();

		ResultSet resultSet = null;
		PreparedStatement ps = null;


		//bobsGameLeaderBoardsByTotalTimePlayed
		//bobsGameLeaderBoardsByTotalBlocksCleared
		//bobsGameLeaderBoardsByPlaneswalkerPoints
		//bobsGameLeaderBoardsByEloScore

		//bobsGameHighScoreBoardsByTimeLasted
		//bobsGameHighScoreBoardsByBlocksCleared

		try
		{
			ps = databaseConnection.prepareStatement(
					"SELECT " +
					"* " +
					"FROM "+databaseName);


			resultSet = ps.executeQuery();

			while(resultSet.next())
			{
				leaderBoards.add(new BobsGameLeaderBoardAndHighScoreBoard(resultSet));
			}

			resultSet.close();
			ps.close();


		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();return null;}


		return leaderBoards;
	}

	//===============================================================================================
	public static boolean updateLeaderBoardsAndHighScoreBoards(
																Connection databaseConnection,
																BobsGameGameStats game,
																LeaderBoardScore score,
																BobsGameUserStatsForSpecificGameAndDifficulty userStatsForAnyGameAnyDifficulty,
																BobsGameUserStatsForSpecificGameAndDifficulty userStatsForAnyGameThisDifficulty,
																BobsGameUserStatsForSpecificGameAndDifficulty userStatsForThisGameAnyDifficulty,
																BobsGameUserStatsForSpecificGameAndDifficulty userStatsForThisGameThisDifficulty,
																String responseString,
																String activityString
																)
	{//===============================================================================================
		//leaderboard by game and difficulty elo score
		//leaderboard by game and difficulty planeswalker
		//leaderboard by game and difficulty total time played
		//leaderboard by game and difficulty total blocks cleared

		//leaderboard by game elo score
		//leaderboard by game planeswalker
		//leaderboard by game total time played
		//leaderboard by game total blocks cleared

		//leaderboard by difficulty elo score
		//leaderboard by difficulty planeswalker
		//leaderboard by difficulty total time played
		//leaderboard by difficulty total blocks cleared

		//leaderboard by elo score
		//leaderboard by planeswalker
		//leaderboard by total time played
		//leaderboard by total blocks cleared

		//high score board by game and difficulty blocks cleared
		//high score board by game and difficulty time lasted

		//high score board by game blocks cleared
		//high score board by game time lasted

		//high score board by difficulty blocks cleared
		//high score board by difficulty time lasted

		//high score board by blocks cleared
		//high score board by time lasted


		//databases:
		//bobsGameLeaderBoardsByTotalTimePlayed
		//bobsGameLeaderBoardsByTotalBlocksCleared
		//bobsGameLeaderBoardsByPlaneswalkerPoints
		//bobsGameLeaderBoardsByEloScore

		//bobsGameHighScoreBoardsByTimeLasted
		//bobsGameHighScoreBoardsByBlocksCleared



		//TODO: //could also do leaderboards based on:
//		public int totalGamesPlayed = 0;
//		public int singlePlayerGamesPlayed = 0;
//		public int tournamentGamesPlayed = 0;
//		public int localMultiplayerGamesPlayed = 0;
//		public int tournamentGamesWon = 0;
//		public int tournamentGamesLost = 0;
//		public int singlePlayerGamesCompleted = 0;
//		public int singlePlayerGamesLost = 0;
//		public int singlePlayerHighestLevelReached = 0;
//		public int biggestCombo = 0;

		BobsGameLeaderBoardAndHighScoreBoard stats = null;
		boolean leaderBoardsModified = false;
		boolean needToUpdate = false;

		boolean anyGame = false;
		boolean anyDifficulty = false;
		boolean compareEloScore = false;
		boolean comparePlaneswalkerPoints = false;
		boolean compareBlocksCleared = false;
		boolean compareTimeLasted = false;
		boolean compareTotalBlocksCleared = false;
		boolean compareTotalTimePlayed = false;




		//leaderboard by game and difficulty elo score
		anyGame = false;
		anyDifficulty = false;
		compareEloScore = true;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByEloScore_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByEloScore_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//leaderboard by game and difficulty planeswalker
		anyGame = false;
		anyDifficulty = false;
		compareEloScore = false;
		comparePlaneswalkerPoints = true;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByPlaneswalkerPoints_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByPlaneswalkerPoints_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//leaderboard by game and difficulty total time played
		anyGame = false;
		anyDifficulty = false;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = true;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalTimePlayed_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalTimePlayed_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//leaderboard by game and difficulty total blocks cleared
		anyGame = false;
		anyDifficulty = false;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = true;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalBlocksCleared_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalBlocksCleared_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//======================================

		//leaderboard by game ANY DIFFICULTY elo score
		anyGame = false;
		anyDifficulty = true;
		compareEloScore = true;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByEloScore_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByEloScore_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//leaderboard by game ANY DIFFICULTY planeswalker
		anyGame = false;
		anyDifficulty = true;
		compareEloScore = false;
		comparePlaneswalkerPoints = true;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByPlaneswalkerPoints_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByPlaneswalkerPoints_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//leaderboard by game ANY DIFFICULTY total time played
		anyGame = false;
		anyDifficulty = true;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = true;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalTimePlayed_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalTimePlayed_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//leaderboard by game ANY DIFFICULTY total blocks cleared
		anyGame = false;
		anyDifficulty = true;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = true;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalBlocksCleared_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalBlocksCleared_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//======================================


		//leaderboard ANY GAME by difficulty elo score
		anyGame = true;
		anyDifficulty = false;
		compareEloScore = true;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByEloScore_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByEloScore_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//leaderboard ANY GAME by difficulty planeswalker
		anyGame = true;
		anyDifficulty = false;
		compareEloScore = false;
		comparePlaneswalkerPoints = true;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByPlaneswalkerPoints_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByPlaneswalkerPoints_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//leaderboard ANY GAME by difficulty total time played
		anyGame = true;
		anyDifficulty = false;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = true;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalTimePlayed_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalTimePlayed_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//leaderboard ANY GAME by difficulty total blocks cleared
		anyGame = true;
		anyDifficulty = false;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = true;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalBlocksCleared_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalBlocksCleared_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;


		//======================================


		//leaderboard OVERALL by elo score
		anyGame = true;
		anyDifficulty = true;
		compareEloScore = true;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByEloScore_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByEloScore_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//leaderboard OVERALL by planeswalker
		anyGame = true;
		anyDifficulty = true;
		compareEloScore = false;
		comparePlaneswalkerPoints = true;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByPlaneswalkerPoints_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByPlaneswalkerPoints_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//leaderboard OVERALL by total time played
		anyGame = true;
		anyDifficulty = true;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = true;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalTimePlayed_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalTimePlayed_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//leaderboard OVERALL by total blocks cleared
		anyGame = true;
		anyDifficulty = true;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = false;
		compareTotalBlocksCleared = true;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalBlocksCleared_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_LeaderBoardsByTotalBlocksCleared_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;




		//now get highScoreBoard by blocksCleared for this game and difficulty, create it if it doesnt exist
		//go through top 10 and see if our score is better than any there, if so put it there


		//high score board by game and difficulty blocks cleared
		//high score board by game and difficulty time lasted

		//high score board by game blocks cleared
		//high score board by game time lasted

		//high score board by difficulty blocks cleared
		//high score board by difficulty time lasted

		//high score board by blocks cleared
		//high score board by time lasted



		//high score board by game and difficulty blocks cleared
		anyGame = false;
		anyDifficulty = false;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = true;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByBlocksCleared_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByBlocksCleared_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//high score board by game and difficulty time lasted
		anyGame = false;
		anyDifficulty = false;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = true;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByTimeLasted_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByTimeLasted_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;


		//======================================

		//high score board by game ANY DIFFICULTY blocks cleared
		anyGame = false;
		anyDifficulty = true;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = true;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByBlocksCleared_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByBlocksCleared_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//high score board by game ANY DIFFICULTY time lasted
		anyGame = false;
		anyDifficulty = true;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = true;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByTimeLasted_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByTimeLasted_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//======================================


		//high score board ANY GAME by difficulty blocks cleared
		anyGame = true;
		anyDifficulty = false;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = true;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByBlocksCleared_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByBlocksCleared_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//high score board ANY GAME by difficulty time lasted
		anyGame = true;
		anyDifficulty = false;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = true;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByTimeLasted_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByTimeLasted_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//======================================

		//high score board OVERALL by blocks cleared
		anyGame = true;
		anyDifficulty = true;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = true;
		compareTimeLasted = false;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByBlocksCleared_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByBlocksCleared_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		//high score board OVERALL by time lasted
		anyGame = true;
		anyDifficulty = true;
		compareEloScore = false;
		comparePlaneswalkerPoints = false;
		compareBlocksCleared = false;
		compareTimeLasted = true;
		compareTotalBlocksCleared = false;
		compareTotalTimePlayed = false;
		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByTimeLasted_DB_Name,game,anyGame,anyDifficulty);
		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStatsForAnyGameAnyDifficulty, userStatsForAnyGameThisDifficulty, userStatsForThisGameAnyDifficulty, userStatsForThisGameThisDifficulty, score, anyGame, anyDifficulty, compareEloScore, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed, responseString, activityString);
		if(needToUpdate)stats.updateDB(databaseConnection,BobNet.Bobs_Game_HighScoreBoardsByTimeLasted_DB_Name);
		if(needToUpdate)leaderBoardsModified = true;

		return leaderBoardsModified;

	}



	//===============================================================================================
	private boolean updateFromGameStatsIfNecessary(Connection databaseConnection, BobsGameGameStats game,
												BobsGameUserStatsForSpecificGameAndDifficulty userStatsForAnyGameAnyDifficulty,
												BobsGameUserStatsForSpecificGameAndDifficulty userStatsForAnyGameThisDifficulty,
												BobsGameUserStatsForSpecificGameAndDifficulty userStatsForThisGameAnyDifficulty,
												BobsGameUserStatsForSpecificGameAndDifficulty userStatsForThisGameThisDifficulty,

												LeaderBoardScore score, boolean anyGame, boolean anyDifficulty, boolean compareEloScore, boolean comparePlaneswalkerPoints, boolean compareBlocksCleared, boolean compareTimeLasted, boolean compareTotalBlocksCleared, boolean compareTotalTimePlayed, String responseString, String activityString)
	{//===============================================================================================



		//boolean compareEloScore
		//boolean comparePlaneswalkerPoints
		//boolean compareBlocksCleared
		//boolean compareTimeLasted
		//boolean compareTotalBlocksCleared
		//boolean compareTotalTimePlayed

		for(int i=0;i<entries.size();i++)
		{

			BobsGameLeaderBoardAndHighScoreBoardEntry existingEntry = entries.get(i);



//			public double newEloScoreForThisGameAndDifficulty = 0;
//			public long newPlaneswalkerPointsForThisGameAndDifficulty = 0;
//
//			//this can't be done unless i tally all the elo scores for each userHighScore entry for a game
//			//public double newEloScoreForThisGame = 0;
//			//public long newPlaneswalkerPointsForThisGame = 0;
//
//			public double newEloScoreForThisDifficulty = 0;
//			public long newPlaneswalkerPointsForThisDifficulty = 0;
//
//			public double newEloScoreOverall = 0;
//			public long newPlaneswalkerPointsOverall = 0;
//
//			public long totalTimePlayedThisGameAndDifficulty = 0;
//			public long totalBlocksClearedThisGameAndDifficulty = 0;
//
//			//public long totalTimePlayedThisGame = 0;
//			//public long totalBlocksClearedThisGame = 0;
//
//			public long totalTimePlayedThisDifficulty = 0;
//			public long totalBlocksClearedThisDifficulty = 0;
//
//			public long totalTimePlayedOverall = 0;
//			public long totalBlocksClearedOverall = 0;
//
//			public long mostBlocksClearedThisGameAndDifficulty = 0;
//			public long longestTimeLastedThisGameAndDifficulty = 0;


			BobsGameLeaderBoardAndHighScoreBoardEntry newEntry = new BobsGameLeaderBoardAndHighScoreBoardEntry();
			newEntry.userName = game.userName;
			newEntry.userID = game.userID;
			newEntry.statsUUID = game.statsUUID;
			newEntry.timeRecordSet = System.currentTimeMillis();


			if(anyGame)
			{
				BobsGameUserStatsForSpecificGameAndDifficulty stats = userStatsForAnyGameThisDifficulty;

				//use userStats.difficulty
				if(anyDifficulty)
				{
					//use userStats.overall
					stats = userStatsForAnyGameAnyDifficulty;
				}



				newEntry.totalGamesPlayed = stats.totalGamesPlayed;
				newEntry.singlePlayerGamesPlayed = stats.singlePlayerGamesPlayed;
				newEntry.tournamentGamesPlayed = stats.tournamentGamesPlayed;
				newEntry.localMultiplayerGamesPlayed = stats.localMultiplayerGamesPlayed;
				newEntry.tournamentGamesWon = stats.tournamentGamesWon;
				newEntry.tournamentGamesLost = stats.tournamentGamesLost;
				newEntry.singlePlayerGamesCompleted = stats.singlePlayerGamesCompleted;
				newEntry.singlePlayerGamesLost = stats.singlePlayerGamesLost;
				newEntry.singlePlayerHighestLevelReached = stats.singlePlayerHighestLevelReached;
				newEntry.totalTimePlayed = stats.totalTimePlayed;
				newEntry.longestGameLength = stats.longestGameLength;
				newEntry.fastestClearedLength = stats.fastestClearedLength;
				newEntry.firstTimePlayed = stats.firstTimePlayed;
				newEntry.lastTimePlayed = System.currentTimeMillis();;
				//newStats.timeRecordSet = stats.timeRecordSet;
				newEntry.eloScore = stats.eloScore;
				newEntry.planesWalkerPoints = stats.planesWalkerPoints;
				newEntry.totalBlocksCleared = stats.totalBlocksCleared;
				newEntry.biggestCombo = stats.biggestCombo;
				newEntry.mostBlocksClearedInOneGame = stats.mostBlocksCleared;
				//newStats.statsUUID = stats.statsUUID;

			}
			else
			{
				//use gameStats
				BobsGameUserStatsForSpecificGameAndDifficulty stats = userStatsForThisGameThisDifficulty;

				if(anyDifficulty)
				{
					//use userStats.overall
					stats = userStatsForThisGameAnyDifficulty;
				}

				newEntry.totalGamesPlayed = stats.totalGamesPlayed;
				newEntry.singlePlayerGamesPlayed = stats.singlePlayerGamesPlayed;
				newEntry.tournamentGamesPlayed = stats.tournamentGamesPlayed;
				newEntry.localMultiplayerGamesPlayed = stats.localMultiplayerGamesPlayed;
				newEntry.tournamentGamesWon = stats.tournamentGamesWon;
				newEntry.tournamentGamesLost = stats.tournamentGamesLost;
				newEntry.singlePlayerGamesCompleted = stats.singlePlayerGamesCompleted;
				newEntry.singlePlayerGamesLost = stats.singlePlayerGamesLost;
				newEntry.singlePlayerHighestLevelReached = stats.singlePlayerHighestLevelReached;
				newEntry.totalTimePlayed = stats.totalTimePlayed;
				newEntry.longestGameLength = stats.longestGameLength;
				newEntry.fastestClearedLength = stats.fastestClearedLength;
				newEntry.firstTimePlayed = stats.firstTimePlayed;
				newEntry.lastTimePlayed = System.currentTimeMillis();;
				//newStats.timeRecordSet = stats.timeRecordSet;
				newEntry.eloScore = stats.eloScore;
				newEntry.planesWalkerPoints = stats.planesWalkerPoints;
				newEntry.totalBlocksCleared = stats.totalBlocksCleared;
				newEntry.biggestCombo = stats.biggestCombo;
				newEntry.mostBlocksClearedInOneGame = stats.mostBlocksCleared;
				//newStats.statsUUID = stats.statsUUID;
			}




			boolean replaceScore = false;
			if(compareEloScore)
			{
				if(anyGame == false && anyDifficulty == false && score.newEloScoreForThisGameAndDifficulty>existingEntry.eloScore)
				{
					replaceScore = true;

					newEntry.eloScore = score.newEloScoreForThisGameAndDifficulty;
				}

				if(anyGame == false && anyDifficulty == true && score.newEloScoreForThisGame>existingEntry.eloScore)
				{
					replaceScore = true;
					newEntry.eloScore = score.newEloScoreForThisGame;
				}

				if(anyGame == true && anyDifficulty == false && score.newEloScoreForThisDifficulty>existingEntry.eloScore)
				{
					replaceScore = true;

					newEntry.eloScore = score.newEloScoreForThisDifficulty;
				}

				if(anyGame == true && anyDifficulty == true && score.newEloScoreOverall>existingEntry.eloScore)
				{
					replaceScore = true;

					newEntry.eloScore = score.newEloScoreOverall;
				}

			}
			if(comparePlaneswalkerPoints)
			{
				if(anyGame == false && anyDifficulty == false && score.newPlaneswalkerPointsForThisGameAndDifficulty>existingEntry.planesWalkerPoints)
				{
					replaceScore = true;

					newEntry.planesWalkerPoints = score.newPlaneswalkerPointsForThisGameAndDifficulty;

				}

				if(anyGame == false && anyDifficulty == true && score.newPlaneswalkerPointsForThisGame>existingEntry.planesWalkerPoints)
				{
					replaceScore = true;
					newEntry.planesWalkerPoints = score.newPlaneswalkerPointsForThisGame;
				}

				if(anyGame == true && anyDifficulty == false && score.newPlaneswalkerPointsForThisDifficulty>existingEntry.planesWalkerPoints)
				{
					replaceScore = true;

					newEntry.planesWalkerPoints = score.newPlaneswalkerPointsForThisDifficulty;
				}

				if(anyGame == true && anyDifficulty == true && score.newPlaneswalkerPointsOverall>existingEntry.planesWalkerPoints)
				{
					replaceScore = true;

					newEntry.planesWalkerPoints = score.newPlaneswalkerPointsOverall;
				}
			}

			if(compareBlocksCleared)
			{
				if(score.mostBlocksClearedThisGameAndDifficulty>existingEntry.mostBlocksClearedInOneGame)
				{
					replaceScore = true;

					newEntry.mostBlocksClearedInOneGame = score.mostBlocksClearedThisGameAndDifficulty;
				}

			}

			if(compareTimeLasted)
			{
				if(game.room.endlessMode==1) 
				{
					
					if(score.longestTimeLastedThisGameAndDifficulty>existingEntry.longestGameLength)
					{
						replaceScore = true;
	
						newEntry.longestGameLength = score.longestTimeLastedThisGameAndDifficulty;
	
					}				
				}
				else
				{
					if(game.complete==1 && (score.fastestTimeClearedThisGameAndDifficulty<existingEntry.fastestClearedLength || existingEntry.fastestClearedLength==0))
					{
						replaceScore = true;
	
						newEntry.fastestClearedLength = score.fastestTimeClearedThisGameAndDifficulty;
	
					}					
				}

			}

			if(compareTotalBlocksCleared)
			{
				if(anyGame == false && anyDifficulty == false && score.totalBlocksClearedThisGameAndDifficulty>existingEntry.totalBlocksCleared)
				{
					replaceScore = true;

					newEntry.totalBlocksCleared = score.totalBlocksClearedThisGameAndDifficulty;

				}

				if(anyGame == false && anyDifficulty == true && score.totalBlocksClearedThisGame>existingEntry.totalBlocksCleared)
				{
					replaceScore = true;

					newEntry.totalBlocksCleared = score.totalBlocksClearedThisGame;
				}

				if(anyGame == true && anyDifficulty == false && score.totalBlocksClearedThisDifficulty>existingEntry.totalBlocksCleared)
				{
					replaceScore = true;

					newEntry.totalBlocksCleared = score.totalBlocksClearedThisDifficulty;
				}

				if(anyGame == true && anyDifficulty == true && score.totalBlocksClearedOverall>existingEntry.totalBlocksCleared)
				{
					replaceScore = true;

					newEntry.totalBlocksCleared = score.totalBlocksClearedOverall;
				}
			}

			if(compareTotalTimePlayed)
			{
				if(anyGame == false && anyDifficulty == false && score.totalTimePlayedThisGameAndDifficulty>existingEntry.totalTimePlayed)
				{
					replaceScore = true;

					newEntry.totalTimePlayed = score.totalTimePlayedThisGameAndDifficulty;

				}

				if(anyGame == false && anyDifficulty == true && score.totalTimePlayedThisGame>existingEntry.totalTimePlayed)
				{
					replaceScore = true;

					newEntry.totalTimePlayed = score.totalTimePlayedThisGame;
				}

				if(anyGame == true && anyDifficulty == false && score.totalTimePlayedThisDifficulty>existingEntry.totalTimePlayed)
				{
					replaceScore = true;

					newEntry.totalTimePlayed = score.totalTimePlayedThisDifficulty;
				}

				if(anyGame == true && anyDifficulty == true && score.totalTimePlayedOverall>existingEntry.totalTimePlayed)
				{
					replaceScore = true;

					newEntry.totalTimePlayed = score.totalTimePlayedOverall;
				}
			}


			if(replaceScore)
			{
				
				String name = "";
				if(isGameSequenceOrType.equals("GameType"))name = gameTypeName;
				if(isGameSequenceOrType.equals("GameSequence"))name = gameSequenceName;
				if(isGameSequenceOrType.equals("OVERALL"))name = "OVERALL";
				
				String type = "";
				if(compareEloScore)type = "Top Players By ELO Score";
				if(comparePlaneswalkerPoints)type = "Top Players By Planeswalker points";

				if(compareTotalBlocksCleared)type = "Top Players By Total Blocks Cleared";
				if(compareTotalTimePlayed)type = "Top Players By Total Time Played";
				if(compareBlocksCleared)type = "Top Games By Blocks Cleared";
				if(compareTimeLasted)type = "Top Games By Time Lasted";
				
				if(i<entries.size()-1 && entries.get(i+1).userName.length()>0)
				{
					String n = entries.get(i+1).userName;
					responseString += "`You defeated "+n+" and placed #"+i+" on Leaderboard "+type+" - "+name+" - "+difficultyName+"!`,";
					activityString += "`"+game.userName+" defeated "+n+" and placed #"+i+" on Leaderboard "+type+" - "+name+" - "+difficultyName+"!`,";
				}
				else
				{
					responseString += "`You placed #"+i+" on Leaderboard "+type+" - "+name+" - "+difficultyName+"!`,";
					activityString += "`"+game.userName+" placed #"+i+" on Leaderboard "+type+" - "+name+" - "+difficultyName+"!`,";
				}
				
				
				if(compareBlocksCleared==false && compareTimeLasted==false)//can have multiple entries for these types
				{
					//don't replace a better score
					for(int n=0;n<i;n++)
					{
						BobsGameLeaderBoardAndHighScoreBoardEntry tempEntry = entries.get(n);
						if(tempEntry.userID == game.userID)
						{
							return false;
						}
					}
					
					//go through rest of entries underneath this one and if this userID is in any of them, remove them
					for(int n=i;n<entries.size();n++)
					{
						BobsGameLeaderBoardAndHighScoreBoardEntry tempEntry = entries.get(n);
						if(tempEntry.userID == game.userID){entries.remove(n);n--;}
					}
				}
				
				entries.add(i,newEntry);

				//if this puts us over, delete last entry
				while(entries.size()>maxEntries)entries.remove(entries.size()-1);

				//if we removed more than 1, add blank ones at the end
				while(entries.size()<maxEntries)entries.add(new BobsGameLeaderBoardAndHighScoreBoardEntry());

				return true;
			}

		}


		return false;

	}




	//===============================================================================================
	public BobsGameLeaderBoardAndHighScoreBoard(ResultSet databaseResultSet)
	{//===============================================================================================


		for(int i=0;i<maxEntries;i++)
		{
			entries.add(new BobsGameLeaderBoardAndHighScoreBoardEntry());
		}


		try
		{

			isGameSequenceOrType = databaseResultSet.getString("isGameTypeOrSequence");
			gameTypeName = databaseResultSet.getString("gameTypeName");
			gameTypeUUID = databaseResultSet.getString("gameTypeUUID");
			gameSequenceName = databaseResultSet.getString("gameSequenceName");
			gameSequenceUUID = databaseResultSet.getString("gameSequenceUUID");
			difficultyName = databaseResultSet.getString("difficultyName");
			objectiveString = databaseResultSet.getString("objectiveString");


			if(isGameSequenceOrType==null)isGameSequenceOrType = "";
			if(gameTypeName==null)gameTypeName = "";
			if(gameTypeUUID==null)gameTypeUUID = "";
			if(gameSequenceName==null)gameSequenceName = "";
			if(gameSequenceUUID==null)gameSequenceUUID = "";
			if(difficultyName==null)difficultyName = "";
			if(objectiveString==null)objectiveString = "";

			for(int i=0;i<maxEntries;i++)
			{
				String num = "_"+i;
				BobsGameLeaderBoardAndHighScoreBoardEntry s = entries.get(i);


				s.userName = databaseResultSet.getString("userName"+num);
				s.userID = databaseResultSet.getLong("userID"+num);
				s.totalGamesPlayed = databaseResultSet.getInt("totalGamesPlayed"+num);
				s.singlePlayerGamesPlayed = databaseResultSet.getInt("singlePlayerGamesPlayed"+num);
				s.tournamentGamesPlayed = databaseResultSet.getInt("tournamentGamesPlayed"+num);
				s.localMultiplayerGamesPlayed = databaseResultSet.getInt("localMultiplayerGamesPlayed"+num);
				s.tournamentGamesWon = databaseResultSet.getInt("tournamentGamesWon"+num);
				s.tournamentGamesLost = databaseResultSet.getInt("tournamentGamesLost"+num);
				s.singlePlayerGamesCompleted = databaseResultSet.getInt("singlePlayerGamesCompleted"+num);
				s.singlePlayerGamesLost = databaseResultSet.getInt("singlePlayerGamesLost"+num);
				s.singlePlayerHighestLevelReached = databaseResultSet.getInt("singlePlayerHighestLevelReached"+num);
				s.totalTimePlayed = databaseResultSet.getLong("totalTimePlayed"+num);
				s.longestGameLength = databaseResultSet.getLong("longestGameLength"+num);
				s.fastestClearedLength = databaseResultSet.getLong("fastestClearedLength"+num);
				s.firstTimePlayed = databaseResultSet.getLong("firstTimePlayed"+num);
				s.lastTimePlayed = databaseResultSet.getLong("lastTimePlayed"+num);
				s.timeRecordSet = databaseResultSet.getLong("timeRecordSet"+num);
				s.eloScore = databaseResultSet.getDouble("eloScore"+num);
				s.planesWalkerPoints = databaseResultSet.getLong("planesWalkerPoints"+num);
				s.totalBlocksCleared = databaseResultSet.getLong("totalBlocksCleared"+num);
				s.biggestCombo = databaseResultSet.getInt("biggestCombo"+num);
				s.mostBlocksClearedInOneGame = databaseResultSet.getInt("mostBlocksClearedInOneGame"+num);
				s.statsUUID = databaseResultSet.getString("statsUUID"+num);

				if(s.statsUUID==null)s.statsUUID = "";



			}
		}
		catch (Exception ex)
		{
			log.error("DB ERROR:"+ex.getMessage());
		}
	}


	//===============================================================================================
	public String encode()
	{//===============================================================================================

		String gameSaveString = "";


		gameSaveString+=",isGameTypeOrSequence:"+            			"`"+isGameSequenceOrType+"`";
		gameSaveString+=",gameTypeName:"+            			"`"+gameTypeName+"`";
		gameSaveString+=",gameTypeUUID:"+            			"`"+gameTypeUUID+"`";
		gameSaveString+=",gameSequenceName:"+            			"`"+gameSequenceName+"`";
		gameSaveString+=",gameSequenceUUID:"+            			"`"+gameSequenceUUID+"`";
		gameSaveString+=",difficultyName:"+            			"`"+difficultyName+"`";
		gameSaveString+=",objectiveString:"+            			"`"+objectiveString+"`";

		for(int i=0;i<maxEntries;i++)
		{
			String num = "_"+i;
			BobsGameLeaderBoardAndHighScoreBoardEntry s = entries.get(i);


			gameSaveString+=",userName"+num+":"+            			"`"+s.userName+"`";
			gameSaveString+=",userID"+num+":"+            			"`"+s.userID+"`";
			gameSaveString+=","+"totalGamesPlayed"+num+":"+s.totalGamesPlayed;
			gameSaveString+=","+"singlePlayerGamesPlayed"+num+":"+s.singlePlayerGamesPlayed;
			gameSaveString+=","+"tournamentGamesPlayed"+num+":"+s.tournamentGamesPlayed;
			gameSaveString+=","+"localMultiplayerGamesPlayed"+num+":"+s.localMultiplayerGamesPlayed;
			gameSaveString+=","+"tournamentGamesWon"+num+":"+s.tournamentGamesWon;
			gameSaveString+=","+"tournamentGamesLost"+num+":"+s.tournamentGamesLost;
			gameSaveString+=","+"singlePlayerGamesCompleted"+num+":"+s.singlePlayerGamesCompleted;
			gameSaveString+=","+"singlePlayerGamesLost"+num+":"+s.singlePlayerGamesLost;
			gameSaveString+=","+"singlePlayerHighestLevelReached"+num+":"+s.singlePlayerHighestLevelReached;
			gameSaveString+=","+"totalTimePlayed"+num+":"+s.totalTimePlayed;
			gameSaveString+=","+"longestGameLength"+num+":"+s.longestGameLength;
			gameSaveString+=","+"fastestClearedLength"+num+":"+s.fastestClearedLength;
			gameSaveString+=","+"firstTimePlayed"+num+":"+s.firstTimePlayed;
			gameSaveString+=","+"lastTimePlayed"+num+":"+s.lastTimePlayed;
			gameSaveString+=","+"timeRecordSet"+num+":"+s.timeRecordSet;
			gameSaveString+=","+"eloScore"+num+":"+s.eloScore;
			gameSaveString+=","+"planesWalkerPoints"+num+":"+s.planesWalkerPoints;
			gameSaveString+=","+"totalBlocksCleared"+num+":"+s.totalBlocksCleared;
			gameSaveString+=","+"biggestCombo"+num+":"+s.biggestCombo;
			gameSaveString+=","+"mostBlocksClearedInOneGame"+num+":"+s.mostBlocksClearedInOneGame;
			gameSaveString+=","+"statsUUID"+num+":"+s.statsUUID;



		}

		gameSaveString+=",";

		return gameSaveString;
	}

	//===============================================================================================
	public BobsGameLeaderBoardAndHighScoreBoard(String s)
	{//===============================================================================================

		for(int i=0;i<maxEntries;i++)
		{
			entries.add(new BobsGameLeaderBoardAndHighScoreBoardEntry());
		}

		decode(s);
	}


	//===============================================================================================
	public void decode(String s)
	{//===============================================================================================

		String t = "";

		s = s.substring(s.indexOf('`')+1);
		t = s.substring(0, s.indexOf('`'));
		if(t.length()>0)isGameSequenceOrType = t;
		s = s.substring(s.indexOf('`')+1);

		s = s.substring(s.indexOf('`')+1);
		t = s.substring(0, s.indexOf('`'));
		if(t.length()>0)gameTypeName = t;
		s = s.substring(s.indexOf('`')+1);

		s = s.substring(s.indexOf('`')+1);
		t = s.substring(0, s.indexOf('`'));
		if(t.length()>0)gameTypeUUID = t;
		s = s.substring(s.indexOf('`')+1);

		s = s.substring(s.indexOf('`')+1);
		t = s.substring(0, s.indexOf('`'));
		if(t.length()>0)gameSequenceName = t;
		s = s.substring(s.indexOf('`')+1);

		s = s.substring(s.indexOf('`')+1);
		t = s.substring(0, s.indexOf('`'));
		if(t.length()>0)gameSequenceUUID = t;
		s = s.substring(s.indexOf('`')+1);
		
		s = s.substring(s.indexOf('`')+1);
		t = s.substring(0, s.indexOf('`'));
		if(t.length()>0)difficultyName = t;
		s = s.substring(s.indexOf('`')+1);

		s = s.substring(s.indexOf('`')+1);
		t = s.substring(0, s.indexOf('`'));
		if(t.length()>0)objectiveString = t;
		s = s.substring(s.indexOf('`')+1);

		for(int i=0;i<maxEntries;i++)
		{
			String diff = "_"+i;
			BobsGameLeaderBoardAndHighScoreBoardEntry stats = entries.get(i);


			s = s.substring(s.indexOf('`')+1);
			t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)stats.userName = t;
			s = s.substring(s.indexOf('`')+1);


			s = s.substring(s.indexOf('`')+1);
			t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{stats.userID = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf('`')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.totalGamesPlayed = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.singlePlayerGamesPlayed = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.tournamentGamesPlayed = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.localMultiplayerGamesPlayed = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.tournamentGamesWon = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.tournamentGamesLost = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.singlePlayerGamesCompleted = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.singlePlayerGamesLost = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.singlePlayerHighestLevelReached = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);



			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.totalTimePlayed = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			
			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.longestGameLength = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.fastestClearedLength = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.firstTimePlayed = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.lastTimePlayed = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.timeRecordSet = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);



			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.eloScore = Double.parseDouble(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.planesWalkerPoints = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.totalBlocksCleared = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.biggestCombo = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{stats.mostBlocksClearedInOneGame = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)stats.statsUUID = t;
			s = s.substring(s.indexOf(',')+1);


		}




	}


	//===============================================================================================
	public void initDB(Connection databaseConnection, String databaseName)
	{//===============================================================================================


		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

		PreparedStatement ps = null;

		String query =

		"INSERT INTO "+databaseName+" SET "; //bobsGameEloScoreLeaderBoards or bobsGameMostBlocksClearedHighScoreBoards

		query +="isGameTypeOrSequence = ? , ";
		query +="gameTypeName = ? , ";
		query +="gameTypeUUID = ? , ";
		query +="gameSequenceName = ? , ";
		query +="gameSequenceUUID = ? , ";
		query +="difficultyName = ? , ";
		query +="objectiveString = ? , ";

		for(int i=0;i<maxEntries;i++)
		{
			String num = "_"+i;


			query += "userName"+num+" = ? , ";
			query += "userID"+num+" = ? , ";
			query += "totalGamesPlayed"+num+" = ? , ";
			query += "singlePlayerGamesPlayed"+num+" = ? , ";
			query += "tournamentGamesPlayed"+num+" = ? , ";
			query += "localMultiplayerGamesPlayed"+num+" = ? , ";
			query += "tournamentGamesWon"+num+" = ? , ";
			query += "tournamentGamesLost"+num+" = ? , ";
			query += "singlePlayerGamesCompleted"+num+" = ? , ";
			query += "singlePlayerGamesLost"+num+" = ? , ";
			query += "singlePlayerHighestLevelReached"+num+" = ? , ";
			query += "totalTimePlayed"+num+" = ? , ";
			query += "longestGameLength"+num+" = ? , ";
			query += "fastestClearedLength"+num+" = ? , ";
			query += "firstTimePlayed"+num+" = ? , ";
			query += "lastTimePlayed"+num+" = ? , ";
			query += "timeRecordSet"+num+" = ? , ";
			query += "eloScore"+num+" = ? , ";
			query += "planesWalkerPoints"+num+" = ? , ";
			query += "totalBlocksCleared"+num+" = ? , ";
			query += "biggestCombo"+num+" = ? , ";
			query += "mostBlocksClearedInOneGame"+num+" = ? , ";
			query += "statsUUID"+num+" = ? ";
			if(i<maxEntries-1)query +=" , ";
		}

		try
		{
			ps = databaseConnection.prepareStatement(query);

			int n=0;


			ps.setString	(++n, isGameSequenceOrType);
			ps.setString	(++n, gameTypeName);
			ps.setString	(++n, gameTypeUUID);
			ps.setString	(++n, gameSequenceName);
			ps.setString	(++n, gameSequenceUUID);
			ps.setString	(++n, difficultyName);
			ps.setString	(++n, objectiveString);


			for(int i=0;i<maxEntries;i++)
			{

				BobsGameLeaderBoardAndHighScoreBoardEntry diffStats = entries.get(i);


				ps.setString(++n, diffStats.userName);
				ps.setLong(++n, diffStats.userID);
				ps.setInt(++n, diffStats.totalGamesPlayed);
				ps.setInt(++n, diffStats.singlePlayerGamesPlayed);
				ps.setInt(++n, diffStats.tournamentGamesPlayed);
				ps.setInt(++n, diffStats.localMultiplayerGamesPlayed);
				ps.setInt(++n, diffStats.tournamentGamesWon);
				ps.setInt(++n, diffStats.tournamentGamesLost);
				ps.setInt(++n, diffStats.singlePlayerGamesCompleted);
				ps.setInt(++n, diffStats.singlePlayerGamesLost);
				ps.setInt(++n, diffStats.singlePlayerHighestLevelReached);
				ps.setLong(++n, diffStats.totalTimePlayed);
				ps.setLong(++n, diffStats.longestGameLength);
				ps.setLong(++n, diffStats.fastestClearedLength);
				ps.setLong(++n, diffStats.firstTimePlayed);
				ps.setLong(++n, diffStats.lastTimePlayed);
				ps.setLong(++n, diffStats.timeRecordSet);
				ps.setDouble(++n, diffStats.eloScore);
				ps.setLong(++n, diffStats.planesWalkerPoints);
				ps.setLong(++n, diffStats.totalBlocksCleared);
				ps.setInt(++n, diffStats.biggestCombo);
				ps.setInt(++n, diffStats.mostBlocksClearedInOneGame);
				ps.setString(++n, diffStats.statsUUID);

			}


			ps.executeUpdate();

			ps.close();

		}
		catch (Exception ex){System.err.println("DB ERROR: "+ex.getMessage());}



	}

	//===============================================================================================
	public void updateDB(Connection databaseConnection, String databaseName)
	{//===============================================================================================


		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

		String query = "";
		query += "UPDATE "+databaseName+" SET "; //bobsGameEloScoreLeaderBoards or bobsGameMostBlocksClearedHighScoreBoards

		String gameTypeOrSequenceQueryString = "";
		String uuid = "";
		if(isGameSequenceOrType.equals("GameType"))
		{
			gameTypeOrSequenceQueryString = "gameTypeUUID = ?";
			uuid = gameTypeUUID;
		}

		if(isGameSequenceOrType.equals("GameSequence"))
		{
			gameTypeOrSequenceQueryString = "gameSequenceUUID = ?";
			uuid = gameSequenceUUID;
		}

		if(isGameSequenceOrType.equals("OVERALL"))
		{
			gameTypeOrSequenceQueryString = "isGameTypeOrSequence = ?";
			uuid = "OVERALL";
		}

		if(difficultyName.equals("OVERALL"))
		{
			difficultyName = "OVERALL";
		}

		for(int i=0;i<maxEntries;i++)
		{
			String num = "_"+i;


			query += "userName"+num+" = ? , ";
			query += "userID"+num+" = ? , ";
			query += "totalGamesPlayed"+num+" = ? , ";
			query += "singlePlayerGamesPlayed"+num+" = ? , ";
			query += "tournamentGamesPlayed"+num+" = ? , ";
			query += "localMultiplayerGamesPlayed"+num+" = ? , ";
			query += "tournamentGamesWon"+num+" = ? , ";
			query += "tournamentGamesLost"+num+" = ? , ";
			query += "singlePlayerGamesCompleted"+num+" = ? , ";
			query += "singlePlayerGamesLost"+num+" = ? , ";
			query += "singlePlayerHighestLevelReached"+num+" = ? , ";
			query += "totalTimePlayed"+num+" = ? , ";
			query += "longestGameLength"+num+" = ? , ";
			query += "fastestClearedLength"+num+" = ? , ";
			query += "firstTimePlayed"+num+" = ? , ";
			query += "lastTimePlayed"+num+" = ? , ";
			query += "timeRecordSet"+num+" = ? , ";
			query += "eloScore"+num+" = ? , ";
			query += "planesWalkerPoints"+num+" = ? , ";
			query += "totalBlocksCleared"+num+" = ? , ";
			query += "biggestCombo"+num+" = ? , ";
			query += "mostBlocksClearedInOneGame"+num+" = ? , ";
			query += "statsUUID"+num+" = ? ";
			if(i<maxEntries-1)query +=" , ";
		}

		query += "WHERE "+gameTypeOrSequenceQueryString+" AND difficultyName = ? AND objectiveString = ?";

		{


			try
			{
				PreparedStatement ps = databaseConnection.prepareStatement(query);


				int n=0;
				for(int i=0;i<maxEntries;i++)
				{

					BobsGameLeaderBoardAndHighScoreBoardEntry diffStats = entries.get(i);


					ps.setString(++n, diffStats.userName);
					ps.setLong(++n, diffStats.userID);
					ps.setInt(++n, diffStats.totalGamesPlayed);
					ps.setInt(++n, diffStats.singlePlayerGamesPlayed);
					ps.setInt(++n, diffStats.tournamentGamesPlayed);
					ps.setInt(++n, diffStats.localMultiplayerGamesPlayed);
					ps.setInt(++n, diffStats.tournamentGamesWon);
					ps.setInt(++n, diffStats.tournamentGamesLost);
					ps.setInt(++n, diffStats.singlePlayerGamesCompleted);
					ps.setInt(++n, diffStats.singlePlayerGamesLost);
					ps.setInt(++n, diffStats.singlePlayerHighestLevelReached);
					ps.setLong(++n, diffStats.totalTimePlayed);
					ps.setLong(++n, diffStats.longestGameLength);
					ps.setLong(++n, diffStats.fastestClearedLength);
					ps.setLong(++n, diffStats.firstTimePlayed);
					ps.setLong(++n, diffStats.lastTimePlayed);
					ps.setLong(++n, diffStats.timeRecordSet);
					ps.setDouble(++n, diffStats.eloScore);
					ps.setLong(++n, diffStats.planesWalkerPoints);
					ps.setLong(++n, diffStats.totalBlocksCleared);
					ps.setInt(++n, diffStats.biggestCombo);
					ps.setInt(++n, diffStats.mostBlocksClearedInOneGame);
					ps.setString(++n, diffStats.statsUUID);

				}

				ps.setString(++n, uuid);
				ps.setString(++n, difficultyName);
				ps.setString(++n, objectiveString);
				ps.executeUpdate();

				ps.close();
			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

		}
	}

}