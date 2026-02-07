package com.bobsgame.net;

public class BobNet
{

	public static String endline = ":END:\r\n";
	public static String batch = ":BATCH:";



	//=========================================================================================
	// GLOBAL DEBUG FOR BOTH CLIENT AND SERVER
	//=========================================================================================
	public static boolean debugMode = false;

	//=========================================================================================

	//=========================================================================================
	// SHARED NETWORK ADDRESSES FOR CLIENT AND SERVER
	//
	//  DO NOT PUT ANYTHING PRIVATE IN HERE - IT IS COMPILED INTO CLIENT
	//=========================================================================================







	public static String debugServerAddress = "localhost";
	public static String releaseServerAddress = "server.bobsgame.com";
	public static int serverTCPPort = 6065;




	//================================
	// used to connect to STUN and then for CLIENT P2P
	//================================
	public static int clientUDPPortStartRange = 6435;




	public static String debugSTUNServerAddress = "localhost";
	public static String releaseSTUNServerAddress = "stun.bobsgame.com";
	public static int STUNServerUDPPort = 6433;// FOR STUN SERVER





	//================================
	// BIG DATA (zips, mp3, applet + libs (jars))
	//================================

	public static String debugBigDataURL = "http://localhost/z/";
	public static String releaseBigDataURL = "https://bobsgame.s3.amazonaws.com/z/";//s3 storage.
	//cant use a CNAME for ssl on s3 because the cert comes from apache and s3.amazon.com sends its own cert,
	//but ONLY for s3.amazonaws.com, NOT assets.bobsgame.com.s3.amazonaws.com and CANT make a CNAME for s3.amazonaws.com/bobsgame
	//so i can only use https://bobsgame.s3.amazonaws.com OR s3.amazonaws.com/bobsgame, oh well.




	//================================
	// SMALL DATA (individual asset files (md5 names))
	//================================

	public static String debugSmallDataURL = "http://localhost/assets/";
	public static String releaseSmallDataURL = "http://bobsgame.com/assets/";//dreamhost storage




	//================================
	// HUB ADDRESS/PORT, should only be used by servers.
	//================================


	public static String debugINDEXServerAddress = "localhost";
	public static String releaseINDEXServerAddress = "index.bobsgame.com";
	public static int INDEXServerTCPPort = 606;







	public static final String Server_IP_Address_Request = "Server_IP_Address_Request:";
	public static final String Server_IP_Address_Response = "Server_IP_Address_Response:";


	public static final String Login_Request = "Login_Request:";
	public static final String Login_Response = "Login_Response:";


	public static final String Reconnect_Request = "Reconnect_Request:";
	public static final String Reconnect_Response = "Reconnect_Response:";

	public static final String Facebook_Login_Request = "Facebook_Login_Request:";
	public static final String Facebook_Login_Response = "Facebook_Login_Response:";


	public static final String Password_Recovery_Request = "Password_Recovery_Request:";
	public static final String Password_Recovery_Response = "Password_Recovery_Response:";


	public static final String Create_Account_Request = "Create_Account_Request:";
	public static final String Create_Account_Response = "Create_Account_Response:";


	public static final String Initial_GameSave_Request = "Initial_GameSave_Request:";
	public static final String Initial_GameSave_Response = "Initial_GameSave_Response:";


	public static final String Encrypted_GameSave_Update_Request = "Encrypted_GameSave_Update_Request:";
	public static final String Encrypted_GameSave_Update_Response = "Encrypted_GameSave_Update_Response:";


	//deprecated, client side geolookup using google/yahoo API now.
	public static final String Postal_Code_Update_Request = "Postal_Code_Update_Request:";
	public static final String Postal_Code_Update_Response = "Postal_Code_Update_Response:";



	public static final String Player_Coords = "Player_Coords:";
	//no server response


	public static final String Map_Request_By_Name = "Map_Request_By_Name:";
	public static final String Map_Request_By_ID = "Map_Request_By_ID:";
	public static final String Map_Response = "Map_Response:";


	public static final String Sprite_Request_By_Name = "Sprite_Request_By_Name:";
	public static final String Sprite_Request_By_ID = "Sprite_Request_By_ID:";
	public static final String Sprite_Response = "Sprite_Response:";



	public static final String Dialogue_Request = "Dialogue_Request:";
	public static final String Dialogue_Response = "Dialogue_Response:";

	public static final String Load_Event_Request = "Load_Event_Request:";
	public static final String Load_Event_Response = "Load_Event_Response:";


	public static final String Event_Request = "Event_Request:";
	public static final String Event_Response = "Event_Response:";



	public static final String GameString_Request = "GameString_Request:";
	public static final String GameString_Response = "GameString_Response:";

	public static final String Flag_Request = "Flag_Request:";
	public static final String Flag_Response = "Flag_Response:";

	public static final String Skill_Request = "Skill_Request:";
	public static final String Skill_Response = "Skill_Response:";

	public static final String Music_Request = "Music_Request:";
	public static final String Music_Response = "Music_Response:";



	public static final String Sound_Request = "Sound_Request:";
	public static final String Sound_Response = "Sound_Response:";



	public static final String Update_Facebook_Account_In_DB_Request = "Update_Facebook_Account_In_DB_Request:";//this is sent from the client to the server with the FB sessionToken
	public static final String Update_Facebook_Account_In_DB_Response = "Update_Facebook_Account_In_DB_Response:";


	public static final String Add_Friend_By_UserName_Request = "Add_Friend_By_UserName_Request:";
	public static final String Add_Friend_By_UserName_Response = "Add_Friend_By_UserName_Response:";



	public static final String Online_Friends_List_Request = "Online_Friends_List_Request:";
	public static final String Online_Friends_List_Response = "Online_Friends_List_Response:";



	//no client request
	public static final String Friend_Is_Online_Notification = "Friend_Is_Online_Notification:";


	//no client request
	public static final String Tell_Client_Their_Session_Was_Logged_On_Somewhere_Else = "Tell_Client_Their_Session_Was_Logged_On_Somewhere_Else:";


	//no client request
	public static final String Tell_Client_Servers_Are_Shutting_Down = "Tell_Client_Servers_Are_Shutting_Down:";
	public static final String Tell_Client_Servers_Have_Shut_Down = "Tell_Client_Servers_Have_Shut_Down:";






	//UDP
	public static final String STUN_Request = "STUN_Request:";
	public static final String STUN_Response = "STUN_Response:";



	public static final String Friend_Connect_Request = "Friend_Connect_Request:";
	public static final String Friend_Connect_Response = "Friend_Connect_Response:";


	public static final String Friend_Data_Request = "Friend_Data_Request:";
	public static final String Friend_Data_Response = "Friend_Data_Response:";



	public static final String Friend_LocationStatus_Update = "Friend_Location_Update:";


	public static final String Game_Connect_Request = "Game_Connect_Request:";
	public static final String Game_Connect_Response = "Game_Connect_Response:";

	public static final String Game_Challenge_Request = "Game_Challenge_Request:";
	public static final String Game_Challenge_Response = "Game_Challenge_Response:";



	//SERVER TO INDEX
	public static final String INDEX_Register_Server_With_INDEX_Request = "INDEX_Register_Server_With_INDEX_Request:";
	public static final String INDEX_Tell_ServerID_To_Tell_UserID_That_UserIDs_Are_Online = "INDEX_Tell_ServerID_To_Tell_UserID_That_UserIDs_Are_Online:";
	public static final String INDEX_Tell_All_Servers_To_Tell_FacebookIDs_That_UserID_Is_Online = "INDEX_Tell_All_Servers_To_Tell_FacebookIDs_That_UserID_Is_Online:";
	public static final String INDEX_Tell_All_Servers_To_Tell_UserNames_That_UserID_Is_Online = "INDEX_Tell_All_Servers_To_Tell_UserNames_That_UserID_Is_Online:";
	public static final String INDEX_UserID_Logged_On_This_Server_Log_Them_Off_Other_Servers = "INDEX_UserID_Logged_On_This_Server_Log_Them_Off_Other_Servers:";
	public static final String INDEX_Tell_All_Servers_To_Send_Activity_Update_To_All_Clients = "INDEX_Tell_All_Servers_To_Send_Activity_Update_To_All_Clients:";
	public static final String INDEX_Tell_All_Servers_To_Send_Chat_Message_To_All_Clients = "INDEX_Tell_All_Servers_To_Send_Chat_Message_To_All_Clients:";


	public static final String INDEX_Tell_All_Servers_Bobs_Game_Hosting_Room_Update = "INDEX_Tell_All_Servers_Bobs_Game_Hosting_Room_Update:";
	public static final String INDEX_Tell_All_Servers_Bobs_Game_Remove_Room = "INDEX_Tell_All_Servers_Bobs_Game_Remove_Room:";




	//INDEX TO SERVER
	public static final String Server_Register_Server_With_INDEX_Response = "Server_Registered_With_INDEX_Response:";
	public static final String Server_Tell_All_FacebookIDs_That_UserID_Is_Online = "Server_Tell_All_FacebookIDs_That_UserID_Is_Online:";
	public static final String Server_Tell_All_UserNames_That_UserID_Is_Online = "Server_Tell_All_UserNames_That_UserID_Is_Online:";
	public static final String Server_Tell_UserID_That_UserIDs_Are_Online = "Server_Tell_UserID_That_UserIDs_Are_Online:";
	public static final String Server_UserID_Logged_On_Other_Server_So_Log_Them_Off = "Server_UserID_Logged_On_Other_Server_So_Log_Them_Off:";
	public static final String Server_Tell_All_Users_Servers_Are_Shutting_Down = "Server_Tell_All_Users_Servers_Are_Shutting_Down:";
	public static final String Server_Tell_All_Users_Servers_Have_Shut_Down = "Server_Tell_All_Users_Servers_Have_Shut_Down:";

	public static final String Server_Bobs_Game_Hosting_Room_Update = "Server_Bobs_Game_Hosting_Room_Update:";
	public static final String Server_Bobs_Game_Remove_Room = "Server_Bobs_Game_Remove_Room:";
	
	public static final String Server_Send_Activity_Update_To_All_Clients = "Server_Send_Activity_Update_To_All_Clients:";
	public static final String Server_Send_Chat_Message_To_All_Clients = "Server_Send_Chat_Message_To_All_Clients:";

	//BOBS GAME
	public static final String Bobs_Game_GameTypesAndSequences_Download_Request = "Bobs_Game_GameTypesAndSequences_Download_Request:";
	public static final String Bobs_Game_GameTypesAndSequences_Download_Response = "Bobs_Game_GameTypesAndSequences_Download_Response:";

	public static final String Bobs_Game_GameTypesAndSequences_Upload_Request = "Bobs_Game_GameTypesAndSequences_Upload_Request:";
	public static final String Bobs_Game_GameTypesAndSequences_Upload_Response = "Bobs_Game_GameTypesAndSequences_Upload_Response:";

	public static final String Bobs_Game_GameTypesAndSequences_Vote_Request = "Bobs_Game_GameTypesAndSequences_Vote_Request:";
	public static final String Bobs_Game_GameTypesAndSequences_Vote_Response = "Bobs_Game_GameTypesAndSequences_Vote_Response:";

	public static final String Bobs_Game_RoomList_Request = "Bobs_Game_RoomList_Request:";
	public static final String Bobs_Game_RoomList_Response = "Bobs_Game_RoomList_Response:";
	public static final String Bobs_Game_TellRoomHostToAddMyUserID = "Bobs_Game_TellRoomHostToAddMyUserID:";
	public static final String Bobs_Game_NewRoomCreatedUpdate = "Bobs_Game_NewRoomCreatedUpdate:";

	public static final String Bobs_Game_HostingPublicRoomUpdate = "Bobs_Game_HostingPublicRoomUpdate:";
	public static final String Bobs_Game_HostingPublicRoomStarted = "Bobs_Game_HostingPublicRoomStarted:";
	public static final String Bobs_Game_HostingPublicRoomCanceled = "Bobs_Game_HostingPublicRoomCanceled:";
	public static final String Bobs_Game_HostingPublicRoomEnded = "Bobs_Game_HostingPublicRoomEnded:";

	public static final String Bobs_Game_GameStats = "Bobs_Game_GameStats:";
	public static final String Bobs_Game_GameStats_Response = "Bobs_Game_GameStats_Response:";
	
	
	public static final String Bobs_Game_ActivityStream_Request = "Bobs_Game_ActivityStream_Request:";
	public static final String Bobs_Game_ActivityStream_Response = "Bobs_Game_ActivityStream_Response:";
	public static final String Bobs_Game_ActivityStream_Update = "Bobs_Game_ActivityStream_Update:";





	public static final String Bobs_Game_GetHighScoresAndLeaderboardsRequest = "Bobs_Game_GetHighScoresAndLeaderboardsRequest:";
	public static final String Bobs_Game_UserStatsLeaderBoardsAndHighScoresBatched = "Bobs_Game_UserStatsLeaderBoardsAndHighScoresBatched:";
	public static final String Bobs_Game_UserStatsForSpecificGameAndDifficulty = "Bobs_Game_UserStatsForSpecificGameAndDifficulty:";
	public static final String Bobs_Game_LeaderBoardsByTotalTimePlayed = "Bobs_Game_LeaderBoardsByTotalTimePlayed:";
	public static final String Bobs_Game_LeaderBoardsByTotalBlocksCleared = "Bobs_Game_LeaderBoardsByTotalBlocksCleared:";
	public static final String Bobs_Game_LeaderBoardsByPlaneswalkerPoints = "Bobs_Game_LeaderBoardsByPlaneswalkerPoints:";
	public static final String Bobs_Game_LeaderBoardsByEloScore = "Bobs_Game_LeaderBoardsByEloScore:";
	public static final String Bobs_Game_HighScoreBoardsByTimeLasted = "Bobs_Game_HighScoreBoardsByTimeLasted:";
	public static final String Bobs_Game_HighScoreBoardsByBlocksCleared = "Bobs_Game_HighScoreBoardsByBlocksCleared:";



	public static final String Bobs_Game_Game_Stats_DB_Name = "bobsGameGameStats";
	public static final String Bobs_Game_User_Stats_For_Specific_Game_And_Difficulty_DB_Name = "bobsGameUserStatsForSpecificGameAndDifficulty";
	public static final String Bobs_Game_LeaderBoardsByEloScore_DB_Name = "bobsGameLeaderBoardsByEloScore";
	public static final String Bobs_Game_LeaderBoardsByPlaneswalkerPoints_DB_Name = "bobsGameLeaderBoardsByPlaneswalkerPoints";
	public static final String Bobs_Game_LeaderBoardsByTotalTimePlayed_DB_Name = "bobsGameLeaderBoardsByTotalTimePlayed";
	public static final String Bobs_Game_LeaderBoardsByTotalBlocksCleared_DB_Name = "bobsGameLeaderBoardsByTotalBlocksCleared";
	public static final String Bobs_Game_HighScoreBoardsByBlocksCleared_DB_Name = "bobsGameHighScoreBoardsByBlocksCleared";
	public static final String Bobs_Game_HighScoreBoardsByTimeLasted_DB_Name = "bobsGameHighScoreBoardsByTimeLasted";
	public static final String Bobs_Game_ActivityStream_DB_Name = "bobsGameActivityStream";





	public static final String Chat_Message = "Chat_Message:";
	public static final String Server_Stats_Request = "Server_Stats_Request:";
	public static final String Server_Stats_Response = "Server_Stats_Response:";

	public static final String Client_Location_Request = "Client_Location_Request:";
	public static final String Client_Location_Response = "Client_Location_Response:";


	public static final String Bobs_Game_Frame_Packet = "Bobs_Game_Frame_Packet:";



}
