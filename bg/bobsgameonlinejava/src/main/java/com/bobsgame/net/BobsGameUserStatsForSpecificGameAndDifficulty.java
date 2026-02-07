package com.bobsgame.net;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

import org.slf4j.LoggerFactory;


import ch.qos.logback.classic.Logger;


//===============================================================================================
//high score collects stats per user for a specific game or sequence at a specific difficulty in order to track their progress and high score
public class BobsGameUserStatsForSpecificGameAndDifficulty
{//===============================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(BobsGameUserStatsForSpecificGameAndDifficulty.class);


	public String userName = "";
	public long userID = -1;

	public String isGameSequenceOrType = "";
	public String gameTypeName = "";
	public String gameTypeUUID = "";
	public String gameSequenceName = "";
	public String gameSequenceUUID = "";
	public String difficultyName = "";
	public String objectiveString = "";


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
	public long averageGameLength = 0;
	public long fastestClearedLength = 0;
	public double eloScore = 0;
	public long firstTimePlayed = 0;
	public long lastTimePlayed = 0;

	public long planesWalkerPoints = 0;
	public long totalBlocksMade = 0;
	public long totalPiecesMade = 0;
	public long totalBlocksCleared = 0;
	public long totalPiecesPlaced = 0;
	public long totalCombosMade = 0;
	public int biggestCombo = 0;



	public int mostBlocksCleared = 0;
	public String longestTimeStatsUUID = "";
	public String fastestTimeClearedStatsUUID = "";
	public String mostBlocksClearedStatsUUID = "";






	//===============================================================================================
	public BobsGameUserStatsForSpecificGameAndDifficulty()
	{//===============================================================================================


	}


	//===============================================================================================
	public static ArrayList<BobsGameUserStatsForSpecificGameAndDifficulty> getAllUserStatsForGamesFromDB(Connection databaseConnection, long userID)
	{//===============================================================================================

		ArrayList<BobsGameUserStatsForSpecificGameAndDifficulty> userStatsForGames = new ArrayList<BobsGameUserStatsForSpecificGameAndDifficulty>();

		ResultSet resultSet = null;
		PreparedStatement ps = null;

		try
		{
			ps = databaseConnection.prepareStatement(
					"SELECT " +
					"* " +
					"FROM "+BobNet.Bobs_Game_User_Stats_For_Specific_Game_And_Difficulty_DB_Name+" WHERE userID = ?");


			int n = 0;
			ps.setLong(++n, userID);
			resultSet = ps.executeQuery();

			while(resultSet.next())
			{
				userStatsForGames.add(new BobsGameUserStatsForSpecificGameAndDifficulty(resultSet));
			}

			resultSet.close();
			ps.close();


		}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();return null;}


		return userStatsForGames;
	}

	//===============================================================================================
	static public BobsGameUserStatsForSpecificGameAndDifficulty getFromDBOrCreateNewIfNotExist(Connection databaseConnection, long userID, String userName, String isGameSequenceOrType, String gameTypeUUID, String gameTypeName, String gameSequenceUUID, String gameSequenceName, String difficultyName, String objectiveString)
	{//===============================================================================================

		BobsGameUserStatsForSpecificGameAndDifficulty stats = null;
		{



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




			ResultSet resultSet = null;
			PreparedStatement ps = null;

			try
			{
				ps = databaseConnection.prepareStatement(
						"SELECT " +
						"* " +
						"FROM "+BobNet.Bobs_Game_User_Stats_For_Specific_Game_And_Difficulty_DB_Name+" WHERE userID = ? AND "+gameTypeOrSequenceQueryString+" AND difficultyName = ? AND objectiveString = ?");


				int n = 0;
				ps.setLong(++n, userID);
				ps.setString(++n, uuid);
				ps.setString(++n, difficultyName);
				ps.setString(++n, objectiveString);
				resultSet = ps.executeQuery();

				if(resultSet.next())
				{
					stats = new BobsGameUserStatsForSpecificGameAndDifficulty(resultSet);
				}

				resultSet.close();
				ps.close();


			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();return null;}
		}

		//create it if it doesnt exist
		if(stats==null)
		{
			stats = new BobsGameUserStatsForSpecificGameAndDifficulty();
			stats.userID = userID;
			stats.userName = userName;
			stats.isGameSequenceOrType = isGameSequenceOrType;
			
			if(isGameSequenceOrType.equals("GameType"))
			{			
				stats.gameTypeUUID = gameTypeUUID;
				stats.gameTypeName = gameTypeName;
			}

			if(isGameSequenceOrType.equals("GameSequence"))
			{
				stats.gameSequenceUUID = gameSequenceUUID;
				stats.gameSequenceName = gameSequenceName;
			}
			
			stats.difficultyName = difficultyName;
			stats.objectiveString = objectiveString;
			stats.initDB(databaseConnection);
		}

		return stats;
	}



	//===============================================================================================
	public boolean updateFromGameStats(Connection databaseConnection,BobsGameGameStats game, BobsGameLeaderBoardAndHighScoreBoard.LeaderBoardScore score, String responseString, String activityString)
	{//===============================================================================================
		//now compare gameStats with userHighScore variables and set them

		String name = "";
		if(isGameSequenceOrType.equals("GameType"))name = gameTypeName;
		if(isGameSequenceOrType.equals("GameSequence"))name = gameSequenceName;
		if(isGameSequenceOrType.equals("OVERALL"))name = "OVERALL";
		String tempResponse = ""; 
		
		
		totalGamesPlayed++;

		if(game.numPlayers==1 && game.isLocalMultiplayer == 0 && game.isNetworkMultiplayer == 0)
		{
			singlePlayerGamesPlayed++;
			if(game.complete==1)singlePlayerGamesCompleted++;
			if(game.died==1)singlePlayerGamesLost++;

			if(game.level>singlePlayerHighestLevelReached) 
			{
				singlePlayerHighestLevelReached = game.level;
				tempResponse += "`Record: New highest level reached!`,";
			}
		}
		if(game.room.multiplayer_TournamentRoom==1)tournamentGamesPlayed++;
		if(game.isLocalMultiplayer==1)localMultiplayerGamesPlayed++;
		if(game.room.multiplayer_TournamentRoom==1 && game.won==1)
		{
			tournamentGamesWon++;
			tempResponse += "`Record: Tournament game won!`,";
		}
		if(game.room.multiplayer_TournamentRoom==1 && (game.lost==1 || game.won==0)) 
		{
			tournamentGamesLost++;
			tempResponse += "`Record: Tournament game lost...`,";
		}



		totalTimePlayed += game.timeLasted;
		if(game.timeLasted>longestGameLength)
		{
			longestGameLength = game.timeLasted;
			longestTimeStatsUUID = game.statsUUID;
			
			tempResponse += "`Record: Longest time lasted!`,";
		}
		
		if(game.complete==1 && (game.timeLasted < fastestClearedLength || fastestClearedLength == 0))
		{
			fastestClearedLength = game.timeLasted;
			fastestTimeClearedStatsUUID = game.statsUUID;
			
			tempResponse += "`Record: Fastest time cleared!`,";
		}

		averageGameLength = totalTimePlayed / totalGamesPlayed;

		if(firstTimePlayed == 0)firstTimePlayed = System.currentTimeMillis();
		lastTimePlayed = System.currentTimeMillis();

		int updatePoints = 0;
		//planeswalker points = 3 points for a win, 1 for a draw, zero for a loss
		if(game.room.multiplayer_TournamentRoom==1 && game.won==1) {planesWalkerPoints+=3;updatePoints = 3;}
		if(game.room.multiplayer_TournamentRoom==1 && game.lost==1) {planesWalkerPoints+=0;updatePoints = 0;}
		if(game.room.multiplayer_TournamentRoom==0) {planesWalkerPoints+=1;updatePoints = 1;}//1 for playing normal game
		if(updatePoints>0)
		{
			tempResponse += "`Earned "+updatePoints+" planeswalker points!`,";
		}
		
		
		
		totalBlocksMade+=game.blocksMade;
		totalPiecesMade+=game.piecesMade;
		totalBlocksCleared+=game.blocksCleared;
		totalPiecesPlaced+=game.piecesPlaced;
		totalCombosMade+=game.combosMade;
		if(game.biggestCombo>biggestCombo)biggestCombo = game.biggestCombo;
		if(game.blocksCleared>mostBlocksCleared)
		{
			mostBlocksCleared = game.blocksCleared;
			mostBlocksClearedStatsUUID = game.statsUUID;
			
			tempResponse += "`Record: Most blocks cleared!`,";
		}

		//elo score
		if(game.room.multiplayer_TournamentRoom==1)
		{
			//if it was a tournament game, parse playerIDsCSV and get other players
			//calculate elo score based on that
			//have to include other players elo scores to calculate properly, or look them up in the database for each userID


			double originalEloScore = eloScore;
			//eloApoints = 1/(1+pow(10,((oldELOB-oldELOA)/400)));
			//eloBpoints = 1/(1+pow(10,((oldELOA-oldELOB)/400)));
			//these should equal 1 when added

			ArrayList<Long> friendIDsWhoLost = new ArrayList<Long>();
			ArrayList<Long> friendIDsWhoWon = new ArrayList<Long>();
			//g.playerIDsCSV = "";//id:`userName`:lost,id:`userName`:won,:
			String p = ""+game.playerIDsCSV;
			while(p.length()>1)
			{


				String friendIDString = p.substring(0,p.indexOf(":"));
				p = p.substring(p.indexOf(":")+1);
				p = p.substring(p.indexOf(":")+1);
				String wonOrLostString = p.substring(0,p.indexOf(","));
				p = p.substring(p.indexOf(",")+1);
				long fid = -1;
				try{fid = Long.parseLong(friendIDString);}catch(NumberFormatException ex){ex.printStackTrace();return false;}
				Long friendID = Long.valueOf(fid);
				if(wonOrLostString.equals("won"))friendIDsWhoWon.add(friendID);
				if(wonOrLostString.equals("lost"))friendIDsWhoLost.add(friendID);
			}



			ResultSet resultSet = null;
			PreparedStatement ps = null;

			for(int x=0; x<2; x++)
			{
				ArrayList<Long> friendIDs = null;

				if(x==0)friendIDs = friendIDsWhoLost;
				if(x==1)friendIDs = friendIDsWhoWon;

				for(int i=0; i<friendIDs.size(); i++)
				{
					long friendUserID = friendIDs.get(i).longValue();
					double friendEloScore = -1;
					try
					{
						
						
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
						
						
						
						
						ps = databaseConnection.prepareStatement(
								"SELECT " +
								"eloScore" +
								"FROM "+BobNet.Bobs_Game_User_Stats_For_Specific_Game_And_Difficulty_DB_Name+" WHERE userID = ? AND "+gameTypeOrSequenceQueryString+" AND difficultyName = ? AND objectiveString = ? ");

						int n=0;
						ps.setLong(++n, friendUserID);
						ps.setString(++n, uuid);
						ps.setString(++n, difficultyName);
						ps.setString(++n, objectiveString);
						resultSet = ps.executeQuery();

						if(resultSet.next())
						{
							friendEloScore = resultSet.getDouble("eloScore");
						}

						resultSet.close();
						ps.close();

						if(friendEloScore!=-1)
						{

							double wikipediaEloScore = 1/(1+Math.pow(10,((friendEloScore-originalEloScore)/400)));


							double r1 = Math.pow(10,originalEloScore/400);
							double r2 = Math.pow(10,friendEloScore/400);
							double e1 = r1/(r1 + r2);
							double e2 = r2/(r1 + r2);
							double s1 = 1;
							if(x==0 && game.won==1)s1 = 1;
							if(x==0 && game.won==0)s1 = 0;
							double s2 = 0;
							if(x==1 && game.won==0)s2 = 1;
							int k = 32;
							double otherWebsiteEloScore = originalEloScore + k*(s1-e1);

							log.info("Original ELO score:"+originalEloScore);
							log.info("Wikipedia ELO score:"+wikipediaEloScore);
							log.info("Other Website ELO score:"+otherWebsiteEloScore);
							eloScore = otherWebsiteEloScore;
							
							tempResponse += "`ELO score updated from "+originalEloScore+" to "+eloScore+"!`,";
						}

					}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();return false;}
				}
			}

		}

		if(isGameSequenceOrType.equals("OVERALL") && difficultyName.equals("OVERALL") == false)
		{
			score.newEloScoreForThisDifficulty = eloScore;
			score.newPlaneswalkerPointsForThisDifficulty = planesWalkerPoints;

			score.totalTimePlayedThisDifficulty = totalTimePlayed;
			score.totalBlocksClearedThisDifficulty = totalBlocksCleared;
		}

		if(difficultyName.equals("OVERALL") && isGameSequenceOrType.equals("OVERALL") == false)
		{
			score.newEloScoreForThisGame = eloScore;
			score.newPlaneswalkerPointsForThisGame = planesWalkerPoints;

			score.totalTimePlayedThisGame = totalTimePlayed;
			score.totalBlocksClearedThisGame = totalBlocksCleared;
		}

		if(isGameSequenceOrType.equals("OVERALL") && difficultyName.equals("OVERALL"))
		{
			score.newEloScoreOverall = eloScore;
			score.newPlaneswalkerPointsOverall = planesWalkerPoints;

			score.totalTimePlayedOverall = totalTimePlayed;
			score.totalBlocksClearedOverall = totalBlocksCleared;
		}

		if(isGameSequenceOrType.equals("OVERALL") == false && difficultyName.equals("OVERALL") == false)
		{
			score.newEloScoreForThisGameAndDifficulty = eloScore;
			score.newPlaneswalkerPointsForThisGameAndDifficulty = planesWalkerPoints;

			score.totalTimePlayedThisGameAndDifficulty = totalTimePlayed;
			score.totalBlocksClearedThisGameAndDifficulty = totalBlocksCleared;

			score.mostBlocksClearedThisGameAndDifficulty = mostBlocksCleared;
			score.longestTimeLastedThisGameAndDifficulty = longestGameLength;
			score.fastestTimeClearedThisGameAndDifficulty = fastestClearedLength;
		}
		
		if(tempResponse.length()>0)
		{
			responseString += "`Results for "+name+" - "+difficultyName+"`,"+tempResponse;
			
			activityString += "`"+game.userName+" set a new record for "+name+" - "+difficultyName+"`,";
			
		}

		return true;
	}

	//===============================================================================================
	public BobsGameUserStatsForSpecificGameAndDifficulty(ResultSet databaseResultSet)
	{//===============================================================================================

		try
		{

			userID = databaseResultSet.getLong("userID");
			userName = databaseResultSet.getString("userName");
			isGameSequenceOrType = databaseResultSet.getString("isGameTypeOrSequence");
			gameTypeName = databaseResultSet.getString("gameTypeName");
			gameTypeUUID = databaseResultSet.getString("gameTypeUUID");
			gameSequenceName = databaseResultSet.getString("gameSequenceName");
			gameSequenceUUID = databaseResultSet.getString("gameSequenceUUID");
			difficultyName = databaseResultSet.getString("difficultyName");
			objectiveString = databaseResultSet.getString("objectiveString");

			if(userName==null)userName = "";
			if(isGameSequenceOrType==null)isGameSequenceOrType = "";
			if(gameTypeName==null)gameTypeName = "";
			if(gameTypeUUID==null)gameTypeUUID = "";
			if(gameSequenceName==null)gameSequenceName = "";
			if(gameSequenceUUID==null)gameSequenceUUID = "";
			if(difficultyName==null)difficultyName = "";
			if(objectiveString==null)objectiveString = "";




			totalGamesPlayed = databaseResultSet.getInt("totalGamesPlayed");
			singlePlayerGamesPlayed = databaseResultSet.getInt("singlePlayerGamesPlayed");
			tournamentGamesPlayed = databaseResultSet.getInt("tournamentGamesPlayed");
			localMultiplayerGamesPlayed = databaseResultSet.getInt("localMultiplayerGamesPlayed");
			tournamentGamesWon = databaseResultSet.getInt("tournamentGamesWon");
			tournamentGamesLost = databaseResultSet.getInt("tournamentGamesLost");
			singlePlayerGamesCompleted = databaseResultSet.getInt("singlePlayerGamesCompleted");
			singlePlayerGamesLost = databaseResultSet.getInt("singlePlayerGamesLost");
			singlePlayerHighestLevelReached = databaseResultSet.getInt("singlePlayerHighestLevelReached");
			totalTimePlayed = databaseResultSet.getLong("totalTimePlayed");
			longestGameLength = databaseResultSet.getLong("longestGameLength");
			averageGameLength = databaseResultSet.getLong("averageGameLength");
			fastestClearedLength = databaseResultSet.getLong("fastestClearedLength");
			eloScore = databaseResultSet.getDouble("eloScore");
			firstTimePlayed = databaseResultSet.getLong("firstTimePlayed");
			lastTimePlayed = databaseResultSet.getLong("lastTimePlayed");
			planesWalkerPoints = databaseResultSet.getLong("planesWalkerPoints");
			totalBlocksMade = databaseResultSet.getLong("totalBlocksMade");
			totalPiecesMade = databaseResultSet.getLong("totalPiecesMade");
			totalBlocksCleared = databaseResultSet.getLong("totalBlocksCleared");
			totalPiecesPlaced = databaseResultSet.getLong("totalPiecesPlaced");
			totalCombosMade = databaseResultSet.getLong("totalCombosMade");
			biggestCombo = databaseResultSet.getInt("biggestCombo");
			mostBlocksCleared = databaseResultSet.getInt("mostBlocksCleared");
			longestTimeStatsUUID = databaseResultSet.getString("longestTimeStatsUUID");
			fastestTimeClearedStatsUUID = databaseResultSet.getString("fastestTimeClearedStatsUUID");
			mostBlocksClearedStatsUUID = databaseResultSet.getString("mostBlocksClearedStatsUUID");

			if(longestTimeStatsUUID==null)longestTimeStatsUUID = "";
			if(fastestTimeClearedStatsUUID==null)fastestTimeClearedStatsUUID = "";
			if(mostBlocksClearedStatsUUID==null)mostBlocksClearedStatsUUID = "";



		}
		catch (Exception ex)
		{
			log.error("DB ERROR:"+ex.getMessage());
		}
	}


	//===============================================================================================
	public String encode()
	{//===============================================================================================

		String gameSaveString =
		"userID:"+                  		"`"+userID+"`"+
		",userName:"+            			"`"+userName+"`";

		gameSaveString+=",isGameTypeOrSequence:"+            			"`"+isGameSequenceOrType+"`";
		gameSaveString+=",gameTypeName:"+            			"`"+gameTypeName+"`";
		gameSaveString+=",gameTypeUUID:"+            			"`"+gameTypeUUID+"`";
		gameSaveString+=",gameSequenceName:"+            			"`"+gameSequenceName+"`";
		gameSaveString+=",gameSequenceUUID:"+            			"`"+gameSequenceUUID+"`";
		gameSaveString+=",difficultyName:"+            			"`"+difficultyName+"`";
		gameSaveString+=",objectiveString:"+            			"`"+objectiveString+"`";


		gameSaveString+=","+"totalGamesPlayed"+":"+totalGamesPlayed;
		gameSaveString+=","+"singlePlayerGamesPlayed"+":"+singlePlayerGamesPlayed;
		gameSaveString+=","+"tournamentGamesPlayed"+":"+tournamentGamesPlayed;
		gameSaveString+=","+"localMultiplayerGamesPlayed"+":"+localMultiplayerGamesPlayed;
		gameSaveString+=","+"tournamentGamesWon"+":"+tournamentGamesWon;
		gameSaveString+=","+"tournamentGamesLost"+":"+tournamentGamesLost;
		gameSaveString+=","+"singlePlayerGamesCompleted"+":"+singlePlayerGamesCompleted;
		gameSaveString+=","+"singlePlayerGamesLost"+":"+singlePlayerGamesLost;
		gameSaveString+=","+"singlePlayerHighestLevelReached"+":"+singlePlayerHighestLevelReached;
		gameSaveString+=","+"totalTimePlayed"+":"+totalTimePlayed;
		gameSaveString+=","+"longestGameLength"+":"+longestGameLength;
		gameSaveString+=","+"averageGameLength"+":"+averageGameLength;
		gameSaveString+=","+"fastestClearedLength"+":"+fastestClearedLength;
		gameSaveString+=","+"eloScore"+":"+eloScore;
		gameSaveString+=","+"firstTimePlayed"+":"+firstTimePlayed;
		gameSaveString+=","+"lastTimePlayed"+":"+lastTimePlayed;
		gameSaveString+=","+"planesWalkerPoints"+":"+planesWalkerPoints;
		gameSaveString+=","+"totalBlocksMade"+":"+totalBlocksMade;
		gameSaveString+=","+"totalPiecesMade"+":"+totalPiecesMade;
		gameSaveString+=","+"totalBlocksCleared"+":"+totalBlocksCleared;
		gameSaveString+=","+"totalPiecesPlaced"+":"+totalPiecesPlaced;
		gameSaveString+=","+"totalCombosMade"+":"+totalCombosMade;
		gameSaveString+=","+"biggestCombo"+":"+biggestCombo;
		gameSaveString+=","+"mostBlocksCleared"+":"+mostBlocksCleared;
		gameSaveString+=","+"longestTimeStatsUUID"+":"+longestTimeStatsUUID;
		gameSaveString+=","+"fastestTimeClearedStatsUUID"+":"+fastestTimeClearedStatsUUID;
		gameSaveString+=","+"mostBlocksClearedStatsUUID"+":"+mostBlocksClearedStatsUUID;





		gameSaveString+=",";

		return gameSaveString;
	}

	//===============================================================================================
	public BobsGameUserStatsForSpecificGameAndDifficulty(String s)
	{//===============================================================================================

		decode(s);
	}


	//===============================================================================================
	public void decode(String s)
	{//===============================================================================================

//		"userID:"+                  	"`"+userID+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)try{userID = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf('`')+1);

		}

//		",userName:"+            	"`"+userName+"`"+
		{
			s = s.substring(s.indexOf('`')+1);
			String t = s.substring(0, s.indexOf('`'));
			if(t.length()>0)userName = t;
			s = s.substring(s.indexOf('`')+1);

		}

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



			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{totalGamesPlayed = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{singlePlayerGamesPlayed = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{tournamentGamesPlayed = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{localMultiplayerGamesPlayed = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{tournamentGamesWon = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{tournamentGamesLost = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{singlePlayerGamesCompleted = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{singlePlayerGamesLost = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{singlePlayerHighestLevelReached = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{totalTimePlayed = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{longestGameLength = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);
			
			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{averageGameLength = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{fastestClearedLength = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{eloScore = Double.parseDouble(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{firstTimePlayed = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{lastTimePlayed = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{planesWalkerPoints = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{totalBlocksMade = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{totalPiecesMade = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{totalBlocksCleared = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{totalPiecesPlaced = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{totalCombosMade = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);


			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{biggestCombo = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)try{mostBlocksCleared = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
			s = s.substring(s.indexOf(',')+1);
			
			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)longestTimeStatsUUID = t;
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)fastestTimeClearedStatsUUID = t;
			s = s.substring(s.indexOf(',')+1);

			s = s.substring(s.indexOf(':')+1);
			t = s.substring(0, s.indexOf(','));
			if(t.length()>0)mostBlocksClearedStatsUUID = t;
			s = s.substring(s.indexOf(',')+1);


	}

	//===============================================================================================
	public void initDB(Connection databaseConnection)
	{//===============================================================================================


		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

		PreparedStatement ps = null;

		String query =

		"INSERT INTO "+BobNet.Bobs_Game_User_Stats_For_Specific_Game_And_Difficulty_DB_Name+" SET ";

		query += "userID"+" = ? , ";
		query += "userName"+" = ? , ";
		query += "isGameTypeOrSequence"+" = ? , ";
		query += "gameTypeName"+" = ? , ";
		query += "gameTypeUUID"+" = ? , ";
		query += "gameSequenceName"+" = ? , ";
		query += "gameSequenceUUID"+" = ? , ";
		query += "difficultyName"+" = ? , ";
		query += "objectiveString"+" = ? , ";

		query += "totalGamesPlayed"+" = ? , ";
		query += "singlePlayerGamesPlayed"+" = ? , ";
		query += "tournamentGamesPlayed"+" = ? , ";
		query += "localMultiplayerGamesPlayed"+" = ? , ";
		query += "tournamentGamesWon"+" = ? , ";
		query += "tournamentGamesLost"+" = ? , ";
		query += "singlePlayerGamesCompleted"+" = ? , ";
		query += "singlePlayerGamesLost"+" = ? , ";
		query += "singlePlayerHighestLevelReached"+" = ? , ";
		query += "totalTimePlayed"+" = ? , ";
		query += "longestGameLength"+" = ? , ";
		query += "averageGameLength"+" = ? , ";
		query += "fastestClearedLength"+" = ? , ";
		query += "eloScore"+" = ? , ";
		query += "firstTimePlayed"+" = ? , ";
		query += "lastTimePlayed"+" = ? , ";
		query += "planesWalkerPoints"+" = ? , ";
		query += "totalBlocksMade"+" = ? , ";
		query += "totalPiecesMade"+" = ? , ";
		query += "totalBlocksCleared"+" = ? , ";
		query += "totalPiecesPlaced"+" = ? , ";
		query += "totalCombosMade"+" = ? , ";
		query += "biggestCombo"+" = ? , ";
		query += "mostBlocksCleared"+" = ? , ";
		query += "longestTimeStatsUUID"+" = ? , ";
		query += "fastestTimeClearedStatsUUID"+" = ? , ";
		query += "mostBlocksClearedStatsUUID"+" = ? ";



		try
		{
			ps = databaseConnection.prepareStatement(query);

			int n = 0;
			ps.setLong(++n, userID);
			ps.setString(++n, userName);
			ps.setString(++n, isGameSequenceOrType);
			ps.setString(++n, gameTypeName);
			ps.setString(++n, gameTypeUUID);
			ps.setString(++n, gameSequenceName);
			ps.setString(++n, gameSequenceUUID);
			ps.setString(++n, difficultyName);
			ps.setString(++n, objectiveString);

			ps.setInt(++n, totalGamesPlayed);
			ps.setInt(++n, singlePlayerGamesPlayed);
			ps.setInt(++n, tournamentGamesPlayed);
			ps.setInt(++n, localMultiplayerGamesPlayed);
			ps.setInt(++n, tournamentGamesWon);
			ps.setInt(++n, tournamentGamesLost);
			ps.setInt(++n, singlePlayerGamesCompleted);
			ps.setInt(++n, singlePlayerGamesLost);
			ps.setInt(++n, singlePlayerHighestLevelReached);
			ps.setLong(++n, totalTimePlayed);
			ps.setLong(++n, longestGameLength);
			ps.setLong(++n, averageGameLength);
			ps.setLong(++n, fastestClearedLength);
			ps.setDouble(++n, eloScore);
			ps.setLong(++n, firstTimePlayed);
			ps.setLong(++n, lastTimePlayed);
			ps.setLong(++n, planesWalkerPoints);
			ps.setLong(++n, totalBlocksMade);
			ps.setLong(++n, totalPiecesMade);
			ps.setLong(++n, totalBlocksCleared);
			ps.setLong(++n, totalPiecesPlaced);
			ps.setLong(++n, totalCombosMade);
			ps.setInt(++n, biggestCombo);
			ps.setInt(++n, mostBlocksCleared);
			ps.setString(++n, longestTimeStatsUUID);
			ps.setString(++n, fastestTimeClearedStatsUUID);
			ps.setString(++n, mostBlocksClearedStatsUUID);


			ps.executeUpdate();

			ps.close();

		}
		catch (Exception ex){System.err.println("DB ERROR: "+ex.getMessage());}




	}


	//===============================================================================================
	public void updateDB(Connection databaseConnection, long userID)
	{//===============================================================================================

		if(databaseConnection==null){log.error("DB ERROR: Could not open DB connection!");return;}

		String query = "";
		query += "UPDATE "+BobNet.Bobs_Game_User_Stats_For_Specific_Game_And_Difficulty_DB_Name+" SET ";



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


		query += "userName"+" = ? , ";
		query += "isGameTypeOrSequence"+" = ? , ";
		query += "gameTypeName"+" = ? , ";
		query += "gameTypeUUID"+" = ? , ";
		query += "gameSequenceName"+" = ? , ";
		query += "gameSequenceUUID"+" = ? , ";
		query += "difficultyName"+" = ? , ";
		query += "objectiveString"+" = ? , ";

		query += "totalGamesPlayed"+" = ? , ";
		query += "singlePlayerGamesPlayed"+" = ? , ";
		query += "tournamentGamesPlayed"+" = ? , ";
		query += "localMultiplayerGamesPlayed"+" = ? , ";
		query += "tournamentGamesWon"+" = ? , ";
		query += "tournamentGamesLost"+" = ? , ";
		query += "singlePlayerGamesCompleted"+" = ? , ";
		query += "singlePlayerGamesLost"+" = ? , ";
		query += "singlePlayerHighestLevelReached"+" = ? , ";
		query += "totalTimePlayed"+" = ? , ";
		query += "longestGameLength"+" = ? , ";
		query += "averageGameLength"+" = ? , ";
		query += "fastestClearedLength"+" = ? , ";
		query += "eloScore"+" = ? , ";
		query += "firstTimePlayed"+" = ? , ";
		query += "lastTimePlayed"+" = ? , ";
		query += "planesWalkerPoints"+" = ? , ";
		query += "totalBlocksMade"+" = ? , ";
		query += "totalPiecesMade"+" = ? , ";
		query += "totalBlocksCleared"+" = ? , ";
		query += "totalPiecesPlaced"+" = ? , ";
		query += "totalCombosMade"+" = ? , ";
		query += "biggestCombo"+" = ? , ";
		query += "mostBlocksCleared"+" = ? , ";
		query += "longestTimeStatsUUID"+" = ? , ";
		query += "fastestTimeClearedStatsUUID"+" = ? , ";
		query += "mostBlocksClearedStatsUUID"+" = ? ";



		query += "WHERE userID = ? AND "+gameTypeOrSequenceQueryString+" AND difficultyName = ? AND objectiveString = ?";

		{


			try
			{
				PreparedStatement ps = databaseConnection.prepareStatement(query);


				int n = 0;
				ps.setString(++n, userName);
				ps.setString(++n, isGameSequenceOrType);
				ps.setString(++n, gameTypeName);
				ps.setString(++n, gameTypeUUID);
				ps.setString(++n, gameSequenceName);
				ps.setString(++n, gameSequenceUUID);
				ps.setString(++n, difficultyName);
				ps.setString(++n, objectiveString);

				ps.setInt(++n, totalGamesPlayed);
				ps.setInt(++n, singlePlayerGamesPlayed);
				ps.setInt(++n, tournamentGamesPlayed);
				ps.setInt(++n, localMultiplayerGamesPlayed);
				ps.setInt(++n, tournamentGamesWon);
				ps.setInt(++n, tournamentGamesLost);
				ps.setInt(++n, singlePlayerGamesCompleted);
				ps.setInt(++n, singlePlayerGamesLost);
				ps.setInt(++n, singlePlayerHighestLevelReached);
				ps.setLong(++n, totalTimePlayed);
				ps.setLong(++n, longestGameLength);
				ps.setLong(++n, averageGameLength);
				ps.setLong(++n, fastestClearedLength);
				ps.setDouble(++n, eloScore);
				ps.setLong(++n, firstTimePlayed);
				ps.setLong(++n, lastTimePlayed);
				ps.setLong(++n, planesWalkerPoints);
				ps.setLong(++n, totalBlocksMade);
				ps.setLong(++n, totalPiecesMade);
				ps.setLong(++n, totalBlocksCleared);
				ps.setLong(++n, totalPiecesPlaced);
				ps.setLong(++n, totalCombosMade);
				ps.setInt(++n, biggestCombo);
				ps.setInt(++n, mostBlocksCleared);
				ps.setString(++n, longestTimeStatsUUID);
				ps.setString(++n, fastestTimeClearedStatsUUID);
				ps.setString(++n, mostBlocksClearedStatsUUID);


				ps.setLong(++n, userID);
				ps.setString(++n, uuid);
				ps.setString(++n, difficultyName);
				ps.setString(++n, objectiveString);
				ps.executeUpdate();

				ps.close();
			}catch (Exception ex){log.error("DB ERROR: "+ex.getMessage());ex.printStackTrace();}

		}
	}





}
