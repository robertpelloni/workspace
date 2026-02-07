package com.bobsgame.shared;



import java.io.IOException;
import java.util.ArrayList;

import javax.swing.tree.DefaultMutableTreeNode;


import com.bobsgame.shared.AssetData;
import com.google.gson.Gson;



//=========================================================================================================================
public class EventData extends AssetData
{//=========================================================================================================================

	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------
	//
	//
	//
	//	WARNING! EDITING THESE NAMES WILL BREAK JSON DECODING
	//
	//
	//
	//
	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------

	private int type = 0;
	private String comment = "";
	private String text = "";






	//=========================================================================================================================
	public EventData()
	{//=========================================================================================================================

	}

	//=========================================================================================================================
	public EventData(int id, String name, int type, String comment, String text)
	{//=========================================================================================================================

		super(id,name);

		this.type = type;
		this.comment = comment;
		this.text = text;

	}



//	//===============================================================================================
//	public static EventData fromBase64ZippedJSON(String b64)
//	{//===============================================================================================
//
//		String decode64 = Utils.decodeBase64String(b64);
//		String json = Utils.unzipString(decode64);
//
//		//Gson gson = new Gson();
//		//EventData data = gson.fromJson(json,EventData.class);
//
//		return fromJSON(json);
//	}
//
//
	//===============================================================================================
	public static EventData fromJSON(String json)
	{//===============================================================================================

		Gson gson = new Gson();
		EventData data = gson.fromJson(json,EventData.class);



//		ObjectMapper mapper = new ObjectMapper();
//		EventData data = null;
//
//		try
//		{
//			data = mapper.readValue(json, EventData.class);
//		}
//		catch(JsonParseException e)
//		{
//			e.printStackTrace();
//		}
//		catch(JsonMappingException e)
//		{
//			e.printStackTrace();
//		}
//		catch(IOException e)
//		{
//			e.printStackTrace();
//		}
		return data;

	}


	//these are used for the client to preload dialogues, flags, music, etc without doing a server lookup.  USED FOR EXPORT ONLY.
	public ArrayList<DialogueData> dialogueDataList = new ArrayList<DialogueData>();
	public ArrayList<FlagData> flagDataList = new ArrayList<FlagData>();
	public ArrayList<SkillData> skillDataList = new ArrayList<SkillData>();
	public ArrayList<GameStringData> gameStringDataList = new ArrayList<GameStringData>();
	public ArrayList<MusicData> musicDataList = new ArrayList<MusicData>();
	public ArrayList<SoundData> soundDataList = new ArrayList<SoundData>();


	//===============================================================================================
	public String toString()
	{//===============================================================================================

		String s = "";

		s = super.toString();

		while(comment.contains("`"))
		{
			String front = comment.substring(0,comment.indexOf("`"));
			String back = comment.substring(comment.indexOf("`")+1);
			comment = front + back;
		}

		while(text.contains("`"))
		{
			String front = text.substring(0,text.indexOf("`"));
			String back = text.substring(text.indexOf("`")+1);
			text = front + back;
		}

		s += "type:`"+type+"`,";
		s += "comment:`"+comment+"`,";
		s += "text:`"+text+"`,";


		s += "dialogueDataList:{";
		for(int i=0;i<dialogueDataList.size();i++)
		{
			s += dialogueDataList.get(i).toString();
		}
		s += "},";


		s += "flagDataList:{";
		for(int i=0;i<flagDataList.size();i++)
		{
			s += flagDataList.get(i).toString();
		}
		s += "},";


		s += "skillDataList:{";
		for(int i=0;i<skillDataList.size();i++)
		{
			s += skillDataList.get(i).toString();
		}
		s += "},";


		s += "gameStringDataList:{";
		for(int i=0;i<gameStringDataList.size();i++)
		{
			s += gameStringDataList.get(i).toString();
		}
		s += "},";


		s += "musicDataList:{";
		for(int i=0;i<musicDataList.size();i++)
		{
			s += musicDataList.get(i).toString();
		}
		s += "},";


		s += "soundDataList:{";
		for(int i=0;i<soundDataList.size();i++)
		{
			s += soundDataList.get(i).toString();
		}
		s += "},";

		return s;
	}




	public String initFromString(String t)
	{
		t = super.initFromString(t);


		t = t.substring(t.indexOf("type:`")+1);
		t = t.substring(t.indexOf("`")+1);
		type = Integer.parseInt(t.substring(0,t.indexOf("`")));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("comment:`")+1);
		t = t.substring(t.indexOf("`")+1);
		comment = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);

		t = t.substring(t.indexOf("text:`")+1);
		t = t.substring(t.indexOf("`")+1);
		text = t.substring(0,t.indexOf("`"));
		t = t.substring(t.indexOf("`,")+2);


		//ONLY FOR USE ON CLIENT, IGNORE THIS
		if(t.startsWith("dialogueDataList"))
		{
			t = t.substring(t.indexOf("dialogueDataList:{")+1);
			t = t.substring(t.indexOf("{")+1);
			while(t.startsWith("}")==false)
			{
				DialogueData data = new DialogueData();
				t = data.initFromString(t);
				dialogueDataList.add(data);
			}
			t = t.substring(t.indexOf("}")+1);
			t = t.substring(t.indexOf(",")+1);

			t = t.substring(t.indexOf("flagDataList:{")+1);
			t = t.substring(t.indexOf("{")+1);
			while(t.startsWith("}")==false)
			{
				FlagData data = new FlagData();
				t = data.initFromString(t);
				flagDataList.add(data);
			}
			t = t.substring(t.indexOf("}")+1);
			t = t.substring(t.indexOf(",")+1);

			t = t.substring(t.indexOf("skillDataList:{")+1);
			t = t.substring(t.indexOf("{")+1);
			while(t.startsWith("}")==false)
			{
				SkillData data = new SkillData();
				t = data.initFromString(t);
				skillDataList.add(data);
			}
			t = t.substring(t.indexOf("}")+1);
			t = t.substring(t.indexOf(",")+1);

			t = t.substring(t.indexOf("gameStringDataList:{")+1);
			t = t.substring(t.indexOf("{")+1);
			while(t.startsWith("}")==false)
			{
				GameStringData data = new GameStringData();
				t = data.initFromString(t);
				gameStringDataList.add(data);
			}
			t = t.substring(t.indexOf("}")+1);
			t = t.substring(t.indexOf(",")+1);

			t = t.substring(t.indexOf("musicDataList:{")+1);
			t = t.substring(t.indexOf("{")+1);
			while(t.startsWith("}")==false)
			{
				MusicData data = new MusicData();
				t = data.initFromString(t);
				musicDataList.add(data);
			}
			t = t.substring(t.indexOf("}")+1);
			t = t.substring(t.indexOf(",")+1);

			t = t.substring(t.indexOf("soundDataList:{")+1);
			t = t.substring(t.indexOf("{")+1);
			while(t.startsWith("}")==false)
			{
				SoundData data = new SoundData();
				t = data.initFromString(t);
				soundDataList.add(data);
			}
			t = t.substring(t.indexOf("}")+1);
			t = t.substring(t.indexOf(",")+1);
		}

		return t;
	}




	//===============================================================================================
	public String getTYPEIDString()
	{//===============================================================================================
		return "EVENT."+id();
	}


	public int type(){return type;}
	public String comment(){return comment;}
	public String text(){return text;}

	public void setType(int s){this.type=s;}
	public void setComment(String s){this.comment=s;}
	public void setText(String s){this.text=s;}




	//===============================================================================================
	//===============================================================================================
	//===============================================================================================
	//===============================================================================================
	//===============================================================================================





	public static int TYPE_PROJECT_INITIAL_LOADER = -3;//project cutscene loader, one per project
	public static int TYPE_PROJECT_CUTSCENE_DONT_RUN_UNTIL_CALLED = -2;//project cutscene loader, one per project

	public static int TYPE_MAP_RUN_ONCE_BEFORE_LOAD = -1;//maps will use this for setting the map State, it is run exactly once upon map load, before any objects are created.
	public static int TYPE_NORMAL_REPEAT_WHILE_MAP_RUNNING = 0;//all object will use this (door, area, entity, sprite)
	public static int TYPE_MAP_DONT_RUN_UNTIL_CALLED = 1;//maps can set this type, which is populated in the EventEditor Events tab. it is an event that any of the objects on this map can call.
	public static int TYPE_MAP_RUN_ONCE_AFTER_LOAD = 2;//maps can set this type, it is used for cutscenes






	//===============================================================================================
	class EventScriptTree
	{//===============================================================================================

		//public String toEventText();

		//TODO: should unify all the event parsing stuff into a class here instead of having basically the same thing in both client and editor.
	}


	//TODO make comment structure for these


	//===============================================================================================
	public static class EventScriptCommand
	{//===============================================================================================

		protected String command;
		protected String comment;//for editor

		//ArrayList<EventParameter> eventParameters

		public String toString(){return getCommandWithArguments();}
		//public EventCommand toEventCommandWithParameters(){return null;}

		public EventScriptCommand()
		{
			this.command = "---";
		}

		public EventScriptCommand(String command,String comment)
		{

			this.command = command;
			this.comment = comment;

			commandList.add(this);
		}



		public String getCommand()
		{
			if(command.contains("_"))return command.substring(0,command.indexOf("_"));
			return command;
		}

		public String getCommandWithArguments()
		{
			return command;
		}

		public String getComment()//TODO: handle comments in editor event editor
		{
			return comment;

		}

	}

	//===============================================================================================
	public static class EventScriptQualifier extends EventScriptCommand
	{//===============================================================================================


		public EventScriptQualifier(String command,String comment)
		{

			this.command = command;
			this.comment = comment;

			qualifierList.add(this);
		}

	}


	public static ArrayList<EventScriptCommand> commandList = new ArrayList<EventScriptCommand>();
	public static ArrayList<EventScriptQualifier> qualifierList = new ArrayList<EventScriptQualifier>();


	public static final EventScriptQualifier isPlayerTouchingThisArea = new EventScriptQualifier("isPlayerTouchingThisArea","");
	public static final EventScriptQualifier isPlayerWalkingIntoThisDoor = new EventScriptQualifier("isPlayerWalkingIntoThisDoor","");
	public static final EventScriptQualifier isPlayerTouchingThisEntity = new EventScriptQualifier("isPlayerTouchingThisEntity","");
	public static final EventScriptQualifier isPlayerTouchingAnyEntityUsingThisSprite = new EventScriptQualifier("isPlayerTouchingAnyEntityUsingThisSprite","");
	public static final EventScriptQualifier isPlayerWalkingIntoDoor_DOOR = new EventScriptQualifier("isPlayerWalkingIntoDoor_DOOR","");
	public static final EventScriptQualifier isPlayerWalkingIntoWarp_WARP = new EventScriptQualifier("isPlayerWalkingIntoWarp_WARP","");
	public static final EventScriptQualifier isActionButtonHeld = new EventScriptQualifier("isActionButtonHeld","");
	public static final EventScriptQualifier isPlayerAutoPilotOn = new EventScriptQualifier("isPlayerAutoPilotOn","");
	public static final EventScriptQualifier isFlagSet_FLAG = new EventScriptQualifier("isFlagSet_FLAG","");
	public static final EventScriptQualifier hasSkillAtLeast_SKILL_FLOAT1 = new EventScriptQualifier("hasSkillAtLeast_SKILL_FLOAT1","");
	public static final EventScriptQualifier isCurrentState_STATE = new EventScriptQualifier("isCurrentState_STATE","");
	public static final EventScriptQualifier isPlayerStandingInArea_AREA = new EventScriptQualifier("isPlayerStandingInArea_AREA","");
	public static final EventScriptQualifier isEntityStandingInArea_ENTITY_AREA = new EventScriptQualifier("isEntityStandingInArea_ENTITY_AREA","");
	public static final EventScriptQualifier hourPastOrEqualTo_INT23 = new EventScriptQualifier("hourPastOrEqualTo_INT23","");
	public static final EventScriptQualifier hourLessThan_INT23 = new EventScriptQualifier("hourLessThan_INT23","");
	public static final EventScriptQualifier minutePastOrEqualTo_INT59 = new EventScriptQualifier("minutePastOrEqualTo_INT59","");
	public static final EventScriptQualifier minuteLessThan_INT59 = new EventScriptQualifier("minuteLessThan_INT59","");
	public static final EventScriptQualifier hasMoneyAtLeastAmount_FLOAT = new EventScriptQualifier("hasMoneyAtLeastAmount_FLOAT","");
	public static final EventScriptQualifier hasMoneyLessThanAmount_FLOAT = new EventScriptQualifier("hasMoneyLessThanAmount_FLOAT","");
	public static final EventScriptQualifier hasItem_ITEM = new EventScriptQualifier("hasItem_ITEM","");
	public static final EventScriptQualifier hasGame_GAME = new EventScriptQualifier("hasGame_GAME","");
	public static final EventScriptQualifier isPlayerMale = new EventScriptQualifier("isPlayerMale","");
	public static final EventScriptQualifier isPlayerFemale = new EventScriptQualifier("isPlayerFemale","");
	public static final EventScriptQualifier isAnyEntityUsingSprite_SPRITE = new EventScriptQualifier("isAnyEntityUsingSprite_SPRITE","");
	public static final EventScriptQualifier isAnyEntityUsingSpriteAtArea_SPRITE_AREA = new EventScriptQualifier("isAnyEntityUsingSpriteAtArea_SPRITE_AREA","");
	public static final EventScriptQualifier isEntitySpawned_ENTITY = new EventScriptQualifier("isEntitySpawned_ENTITY","");
	public static final EventScriptQualifier isEntityAtArea_ENTITY_AREA = new EventScriptQualifier("isEntityAtArea_ENTITY_AREA","");
	public static final EventScriptQualifier isAreaEmpty_AREA = new EventScriptQualifier("isAreaEmpty_AREA","");
	public static final EventScriptQualifier hasFinishedDialogue_DIALOGUE = new EventScriptQualifier("hasFinishedDialogue_DIALOGUE","");
	public static final EventScriptQualifier isTextBoxOpen = new EventScriptQualifier("isTextBoxOpen","");
	public static final EventScriptQualifier isTextAnswerBoxOpen = new EventScriptQualifier("isTextAnswerBoxOpen","");
	public static final EventScriptQualifier isTextAnswerSelected_INT4 = new EventScriptQualifier("isTextAnswerSelected_INT4","");
	public static final EventScriptQualifier isTextAnswerSelected_STRING = new EventScriptQualifier("isTextAnswerSelected_STRING","");
	public static final EventScriptQualifier randomEqualsOneOutOfLessThan_INT = new EventScriptQualifier("randomEqualsOneOutOfLessThan_INT","");
	public static final EventScriptQualifier randomEqualsOneOutOfIncluding_INT = new EventScriptQualifier("randomEqualsOneOutOfIncluding_INT","");
	public static final EventScriptQualifier isAnyMusicPlaying = new EventScriptQualifier("isAnyMusicPlaying","");
	public static final EventScriptQualifier isMusicPlaying_MUSIC = new EventScriptQualifier("isMusicPlaying_MUSIC","");
	public static final EventScriptQualifier isRaining = new EventScriptQualifier("isRaining","");
	public static final EventScriptQualifier isWindy = new EventScriptQualifier("isWindy","");
	public static final EventScriptQualifier isSnowing = new EventScriptQualifier("isSnowing","");
	public static final EventScriptQualifier isFoggy = new EventScriptQualifier("isFoggy","");
//	public static final EventScriptQualifier isPlayerHolding = new EventScriptQualifier("isPlayerHolding_ITEM","");
//	public static final EventScriptQualifier isPlayerWearing = new EventScriptQualifier("isPlayerWearing_ITEM","");
	public static final EventScriptQualifier isMapOutside = new EventScriptQualifier("isMapOutside","");
	public static final EventScriptQualifier hasTalkedToThisToday = new EventScriptQualifier("hasTalkedToThisToday","");
	public static final EventScriptQualifier hasBeenMinutesSinceFlagSet_FLAG_INT = new EventScriptQualifier("hasBeenMinutesSinceFlagSet_FLAG_INT","");
	public static final EventScriptQualifier hasBeenHoursSinceFlagSet_FLAG_INT23 = new EventScriptQualifier("hasBeenHoursSinceFlagSet_FLAG_INT23","");
	public static final EventScriptQualifier hasBeenDaysSinceFlagSet_FLAG_INT = new EventScriptQualifier("hasBeenDaysSinceFlagSet_FLAG_INT","");
	public static final EventScriptQualifier isThisActivated = new EventScriptQualifier("isThisActivated","");
	public static final EventScriptQualifier haveSecondsPassedSinceActivated_INT = new EventScriptQualifier("haveSecondsPassedSinceActivated_INT","");
	public static final EventScriptQualifier haveMinutesPassedSinceActivated_INT = new EventScriptQualifier("haveMinutesPassedSinceActivated_INT","");
	public static final EventScriptQualifier haveHoursPassedSinceActivated_INT = new EventScriptQualifier("haveHoursPassedSinceActivated_INT","");
	public static final EventScriptQualifier haveDaysPassedSinceActivated_INT = new EventScriptQualifier("haveDaysPassedSinceActivated_INT","");
	public static final EventScriptQualifier hasActivatedThisEver = new EventScriptQualifier("hasActivatedThisEver","");
	public static final EventScriptQualifier hasActivatedThisSinceEnterRoom = new EventScriptQualifier("hasActivatedThisSinceEnterRoom","");
	public static final EventScriptQualifier hasBeenHereEver = new EventScriptQualifier("hasBeenHereEver","");
	public static final EventScriptQualifier hasBeenHereSinceEnterRoom = new EventScriptQualifier("hasBeenHereSinceEnterRoom","");
	public static final EventScriptQualifier haveSecondsPassedSinceBeenHere_INT = new EventScriptQualifier("haveSecondsPassedSinceBeenHere_INT","");
	public static final EventScriptQualifier haveMinutesPassedSinceBeenHere_INT = new EventScriptQualifier("haveMinutesPassedSinceBeenHere_INT","");
	public static final EventScriptQualifier haveHoursPassedSinceBeenHere_INT = new EventScriptQualifier("haveHoursPassedSinceBeenHere_INT","");
	public static final EventScriptQualifier haveDaysPassedSinceBeenHere_INT = new EventScriptQualifier("haveDaysPassedSinceBeenHere_INT","");
	public static final EventScriptQualifier isLightOn_LIGHT = new EventScriptQualifier("isLightOn_LIGHT","");












	//commands
	public static final EventScriptCommand alwaysBlockWhileNotStandingHere = new EventScriptCommand("alwaysBlockWhileNotStandingHere","");
	//doesn't delete from the stack, checks every time, continues stack underneath normally.
			//this is an alternative to having an option for deleting the stack when not standing in area
			//instead of deleting the stack
			//this could cause state problems like NPC AI getting stuck off, etc.


	static final EventScriptCommand e00 = new EventScriptCommand();
	public static final EventScriptCommand blockUntilActionButtonPressed = new EventScriptCommand("blockUntilActionButtonPressed","");//BLOCK//doesn't delete from the stack until valid, doesn't proceed until it is.
	public static final EventScriptCommand blockUntilActionCaptionButtonPressed_STRING = new EventScriptCommand("blockUntilActionCaptionButtonPressed_STRING","");//BLOCK//this will stay in the queue checking if we are standing here, use ACTION_area
	public static final EventScriptCommand blockUntilCancelButtonPressed = new EventScriptCommand("blockUntilCancelButtonPressed","");//BLOCK
	public static final EventScriptCommand blockForTicks_INT = new EventScriptCommand("blockForTicks_INT","");//BLOCK
	public static final EventScriptCommand blockUntilClockHour_INT23 = new EventScriptCommand("blockUntilClockHour_INT23","");//BLOCK
	public static final EventScriptCommand blockUntilClockMinute_INT59 = new EventScriptCommand("blockUntilClockMinute_INT59","");//BLOCK
	static final EventScriptCommand e000 = new EventScriptCommand();
	public static final EventScriptCommand loadMapState_STATE = new EventScriptCommand("loadMapState_STATE","");
	public static final EventScriptCommand runEvent_EVENT = new EventScriptCommand("runEvent_EVENT","");
	public static final EventScriptCommand blockUntilEventDone_EVENT = new EventScriptCommand("blockUntilEventDone_EVENT","");
	public static final EventScriptCommand clearThisEvent = new EventScriptCommand("clearThisEvent","");
	public static final EventScriptCommand clearEvent_EVENT = new EventScriptCommand("clearEvent_EVENT","");
	static final EventScriptCommand e001 = new EventScriptCommand();
	public static final EventScriptCommand setThisActivated_BOOL = new EventScriptCommand("setThisActivated_BOOL","");
	public static final EventScriptCommand toggleThisActivated = new EventScriptCommand("toggleThisActivated","");
	static final EventScriptCommand e002 = new EventScriptCommand();
	public static final EventScriptCommand setLastBeenHereTime = new EventScriptCommand("setLastBeenHereTime","");
	public static final EventScriptCommand resetLastBeenHereTime = new EventScriptCommand("resetLastBeenHereTime","");
	static final EventScriptCommand e003 = new EventScriptCommand();
	public static final EventScriptCommand setFlag_FLAG_BOOL = new EventScriptCommand("setFlag_FLAG_BOOL","");
	public static final EventScriptCommand setFlagTrue_FLAG = new EventScriptCommand("setFlagTrue_FLAG","");
	public static final EventScriptCommand setFlagFalse_FLAG = new EventScriptCommand("setFlagFalse_FLAG","");
	static final EventScriptCommand e004 = new EventScriptCommand();
	public static final EventScriptCommand giveSkillPoints_SKILL_INT = new EventScriptCommand("giveSkillPoints_SKILL_INT","");
	public static final EventScriptCommand removeSkillPoints_SKILL_INT = new EventScriptCommand("removeSkillPoints_SKILL_INT","");
	public static final EventScriptCommand setSkillPoints_SKILL_INT = new EventScriptCommand("setSkillPoints_SKILL_INT","");
	static final EventScriptCommand e005 = new EventScriptCommand();

	public static final EventScriptCommand enterThisDoor = new EventScriptCommand("enterThisDoor","");
	public static final EventScriptCommand enterThisWarp = new EventScriptCommand("enterThisWarp","");
	public static final EventScriptCommand enterDoor_DOOR = new EventScriptCommand("enterDoor_DOOR","");
	public static final EventScriptCommand enterWarp_WARP = new EventScriptCommand("enterWarp_WARP","");
	public static final EventScriptCommand changeMap_MAP_AREA = new EventScriptCommand("changeMap_MAP_AREA","");
	public static final EventScriptCommand changeMap_MAP_DOOR = new EventScriptCommand("changeMap_MAP_DOOR","");
	public static final EventScriptCommand changeMap_MAP_WARP = new EventScriptCommand("changeMap_MAP_WARP","");
	public static final EventScriptCommand changeMap_MAP_INT_INT = new EventScriptCommand("changeMap_MAP_INT_INT","");
	static final EventScriptCommand e006 = new EventScriptCommand();
	public static final EventScriptCommand doDialogue_DIALOGUE = new EventScriptCommand("doDialogue_DIALOGUE","");
	public static final EventScriptCommand doDialogueWithCaption_DIALOGUE = new EventScriptCommand("doDialogueWithCaption_DIALOGUE","");
	public static final EventScriptCommand doDialogueIfNew_DIALOGUE = new EventScriptCommand("doDialogueIfNew_DIALOGUE","");
	static final EventScriptCommand e007 = new EventScriptCommand();
	public static final EventScriptCommand setSpriteBox0_ENTITY = new EventScriptCommand("setSpriteBox0_ENTITY","");
	public static final EventScriptCommand setSpriteBox1_ENTITY = new EventScriptCommand("setSpriteBox1_ENTITY","");
	public static final EventScriptCommand setSpriteBox0_SPRITE = new EventScriptCommand("setSpriteBox0_SPRITE","");
	public static final EventScriptCommand setSpriteBox1_SPRITE = new EventScriptCommand("setSpriteBox1_SPRITE","");
	static final EventScriptCommand e008 = new EventScriptCommand();
	public static final EventScriptCommand blockUntilTextBoxClosed = new EventScriptCommand("blockUntilTextBoxClosed","");
	public static final EventScriptCommand blockUntilTextAnswerBoxClosed = new EventScriptCommand("blockUntilTextAnswerBoxClosed","");
	static final EventScriptCommand e009 = new EventScriptCommand();
	public static final EventScriptCommand doCinematicTextNoBorder_DIALOGUE_INTy = new EventScriptCommand("doCinematicTextNoBorder_DIALOGUE_INTy","");

	static final EventScriptCommand e025 = new EventScriptCommand();
	public static final EventScriptCommand setDoorOpenAnimation_DOOR_BOOLopenClose = new EventScriptCommand("setDoorOpenAnimation_DOOR_BOOLopenClose","");
	public static final EventScriptCommand setDoorActionIcon_DOOR_BOOLonOff = new EventScriptCommand("setDoorActionIcon_DOOR_BOOLonOff","");
	public static final EventScriptCommand setDoorDestination_DOOR_DOORdestination = new EventScriptCommand("setDoorDestination_DOOR_DOORdestination","");
	public static final EventScriptCommand setAreaActionIcon_AREA_BOOLonOff = new EventScriptCommand("setAreaActionIcon_AREA_BOOLonOff","");
	public static final EventScriptCommand setWarpDestination_WARP_WARPdestination = new EventScriptCommand("setWarpDestination_WARP_WARPdestination","");


	//public static final EventScriptCommand playVideo_VIDEO = new EventScriptCommand("playVideo_VIDEO","");
	static final EventScriptCommand e010 = new EventScriptCommand();





	static final EventScriptCommand e012 = new EventScriptCommand();
	public static final EventScriptCommand setCameraNoTarget = new EventScriptCommand("setCameraNoTarget","");
	public static final EventScriptCommand setCameraTargetToArea_AREA = new EventScriptCommand("setCameraTargetToArea_AREA","");
	public static final EventScriptCommand setCameraTargetToEntity_ENTITY = new EventScriptCommand("setCameraTargetToEntity_ENTITY","");
	public static final EventScriptCommand setCameraIgnoreBounds_BOOL = new EventScriptCommand("setCameraIgnoreBounds_BOOL","");
	public static final EventScriptCommand setCameraTargetToPlayer = new EventScriptCommand("setCameraTargetToPlayer","");
	public static final EventScriptCommand blockUntilCameraReaches_AREA = new EventScriptCommand("blockUntilCameraReaches_AREA","");
	public static final EventScriptCommand blockUntilCameraReaches_ENTITY = new EventScriptCommand("blockUntilCameraReaches_ENTITY","");
	public static final EventScriptCommand blockUntilCameraReachesPlayer = new EventScriptCommand("blockUntilCameraReachesPlayer","");
	public static final EventScriptCommand pushCameraState = new EventScriptCommand("pushCameraState","");
	public static final EventScriptCommand popCameraState = new EventScriptCommand("popCameraState","");
	public static final EventScriptCommand setKeyboardCameraZoom_BOOL = new EventScriptCommand("setKeyboardCameraZoom_BOOL","");
	public static final EventScriptCommand enableKeyboardCameraZoom = new EventScriptCommand("enableKeyboardCameraZoom","");
	public static final EventScriptCommand disableKeyboardCameraZoom = new EventScriptCommand("disableKeyboardCameraZoom","");
	public static final EventScriptCommand setCameraAutoZoomByPlayerMovement_BOOL = new EventScriptCommand("setCameraAutoZoomByPlayerMovement_BOOL","");
	public static final EventScriptCommand enableCameraAutoZoomByPlayerMovement = new EventScriptCommand("enableCameraAutoZoomByPlayerMovement","");
	public static final EventScriptCommand disableCameraAutoZoomByPlayerMovement = new EventScriptCommand("disableCameraAutoZoomByPlayerMovement","");
	public static final EventScriptCommand setCameraZoom_FLOAT = new EventScriptCommand("setCameraZoom_FLOAT","");
	public static final EventScriptCommand setCameraSpeed_FLOAT = new EventScriptCommand("setCameraSpeed_FLOAT","");



	public static final EventScriptCommand setPlayerToTempPlayerWithSprite_SPRITE = new EventScriptCommand("setPlayerToTempPlayerWithSprite_SPRITE","");
	public static final EventScriptCommand setPlayerToNormalPlayer = new EventScriptCommand("setPlayerToNormalPlayer","");
	public static final EventScriptCommand setPlayerExists_BOOL = new EventScriptCommand("setPlayerExists_BOOL","");
	public static final EventScriptCommand setPlayerControlsEnabled_BOOL = new EventScriptCommand("setPlayerControlsEnabled_BOOL","");
	public static final EventScriptCommand enablePlayerControls = new EventScriptCommand("enablePlayerControls","");
	public static final EventScriptCommand disablePlayerControls = new EventScriptCommand("disablePlayerControls","");
	public static final EventScriptCommand setPlayerAutoPilot_BOOL = new EventScriptCommand("setPlayerAutoPilot_BOOL","");
	public static final EventScriptCommand setPlayerShowNameCaption_BOOL = new EventScriptCommand("setPlayerShowNameCaption_BOOL","");
	public static final EventScriptCommand setPlayerShowAccountTypeCaption_BOOL = new EventScriptCommand("setPlayerShowAccountTypeCaption_BOOL","");

	public static final EventScriptCommand playerSetBehaviorQueueOnOff_BOOL = new EventScriptCommand("playerSetBehaviorQueueOnOff_BOOL","");
	public static final EventScriptCommand playerSetToArea_AREA = new EventScriptCommand("playerSetToArea_AREA","");
	public static final EventScriptCommand playerSetToDoor_DOOR = new EventScriptCommand("playerSetToDoor_DOOR","");
	public static final EventScriptCommand playerSetToTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("playerSetToTileXY_INTxTile1X_INTyTile1X","");
	public static final EventScriptCommand playerWalkToArea_AREA = new EventScriptCommand("playerWalkToArea_AREA","");
	public static final EventScriptCommand playerWalkToDoor_DOOR = new EventScriptCommand("playerWalkToDoor_DOOR","");
	public static final EventScriptCommand playerWalkToEntity_ENTITY = new EventScriptCommand("playerWalkToEntity_ENTITY","");
	public static final EventScriptCommand playerWalkToTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("playerWalkToTileXY_INTxTile1X_INTyTile1X","");
//	public static final EventScriptCommand playerMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("playerMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
//	public static final EventScriptCommand playerMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("playerMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
//	public static final EventScriptCommand playerMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("playerMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
//	public static final EventScriptCommand playerMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("playerMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	public static final EventScriptCommand playerBlockUntilReachesArea_AREA = new EventScriptCommand("playerBlockUntilReachesArea_AREA","");
	public static final EventScriptCommand playerBlockUntilReachesDoor_DOOR = new EventScriptCommand("playerBlockUntilReachesDoor_DOOR","");
	public static final EventScriptCommand playerBlockUntilReachesEntity_ENTITY = new EventScriptCommand("playerBlockUntilReachesEntity_ENTITY","");
	public static final EventScriptCommand playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X","");
	public static final EventScriptCommand playerWalkToAreaAndBlockUntilThere_AREA = new EventScriptCommand("playerWalkToAreaAndBlockUntilThere_AREA","");
	public static final EventScriptCommand playerWalkToEntityAndBlockUntilThere_ENTITY = new EventScriptCommand("playerWalkToEntityAndBlockUntilThere_ENTITY","");
	public static final EventScriptCommand playerWalkToDoorAndBlockUntilThere_DOOR = new EventScriptCommand("playerWalkToDoorAndBlockUntilThere_DOOR","");
	public static final EventScriptCommand playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X = new EventScriptCommand("playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X","");
	public static final EventScriptCommand playerStandAndShuffle = new EventScriptCommand("playerStandAndShuffle","");
//	public static final EventScriptCommand playerStandAndShuffleAndFacePlayer = new EventScriptCommand("playerStandAndShuffleAndFacePlayer","");
	public static final EventScriptCommand playerStandAndShuffleAndFaceEntity_ENTITY = new EventScriptCommand("playerStandAndShuffleAndFaceEntity_ENTITY","");
//	public static final EventScriptCommand playerAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("playerAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
//	public static final EventScriptCommand playerAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("playerAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
//	public static final EventScriptCommand playerAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("playerAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
//	public static final EventScriptCommand playerAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("playerAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
//	public static final EventScriptCommand playerSetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("playerSetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
//	public static final EventScriptCommand playerDoAnimationByNameOnce_STRINGanimationName = new EventScriptCommand("playerDoAnimationByNameOnce_STRINGanimationName","");
//	public static final EventScriptCommand playerDoAnimationByNameLoop_STRINGanimationName = new EventScriptCommand("playerDoAnimationByNameLoop_STRINGanimationName","");
	public static final EventScriptCommand playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame = new EventScriptCommand("playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame","");
	public static final EventScriptCommand playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame = new EventScriptCommand("playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame","");
	public static final EventScriptCommand playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks","");
	public static final EventScriptCommand playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	public static final EventScriptCommand playerStopAnimating = new EventScriptCommand("playerStopAnimating","");
	public static final EventScriptCommand playerSetGlobalAnimationDisabled_BOOL = new EventScriptCommand("playerSetGlobalAnimationDisabled_BOOL","");
	public static final EventScriptCommand playerSetMovementSpeed_INTticksPerPixel = new EventScriptCommand("playerSetMovementSpeed_INTticksPerPixel","");
	public static final EventScriptCommand playerSetFaceMovementDirection_STRINGdirection = new EventScriptCommand("playerSetFaceMovementDirection_STRINGdirection","");
//	public static final EventScriptCommand playerSetNonWalkable_BOOL = new EventScriptCommand("playerSetNonWalkable_BOOL","");
//	public static final EventScriptCommand playerSetPushable_BOOL = new EventScriptCommand("playerSetPushable_BOOL","");
	public static final EventScriptCommand playerSetToAlpha_FLOAT = new EventScriptCommand("playerSetToAlpha_FLOAT","");
	//public static final EventScriptCommand playerFadeOutDelete = new EventScriptCommand("playerFadeOutDelete","");
	//public static final EventScriptCommand playerDeleteInstantly = new EventScriptCommand("playerDeleteInstantly","");


//	public static final EventScriptCommand thisEntitySetBehaviorQueueOnOff_BOOL = new EventScriptCommand("thisEntitySetBehaviorQueueOnOff_BOOL","");
//	public static final EventScriptCommand thisEntitySetToArea_AREA = new EventScriptCommand("thisEntitySetToArea_AREA","");
//	public static final EventScriptCommand thisEntitySetToDoor_DOOR = new EventScriptCommand("thisEntitySetToDoor_DOOR","");
//	public static final EventScriptCommand thisEntitySetToTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("thisEntitySetToTileXY_INTxTile1X_INTyTile1X","");
//	public static final EventScriptCommand thisEntityWalkToArea_AREA = new EventScriptCommand("thisEntityWalkToArea_AREA","");
//	public static final EventScriptCommand thisEntityWalkToDoor_DOOR = new EventScriptCommand("thisEntityWalkToDoor_DOOR","");
//	public static final EventScriptCommand thisEntityWalkToEntity_ENTITY = new EventScriptCommand("thisEntityWalkToEntity_ENTITY","");
//	public static final EventScriptCommand thisEntityWalkToTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("thisEntityWalkToTileXY_INTxTile1X_INTyTile1X","");
//	public static final EventScriptCommand thisEntityMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("thisEntityMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
//	public static final EventScriptCommand thisEntityMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("thisEntityMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
//	public static final EventScriptCommand thisEntityMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("thisEntityMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
//	public static final EventScriptCommand thisEntityMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("thisEntityMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
//	public static final EventScriptCommand thisEntityBlockUntilReachesArea_AREA = new EventScriptCommand("thisEntityBlockUntilReachesArea_AREA","");
//	public static final EventScriptCommand thisEntityBlockUntilReachesDoor_DOOR = new EventScriptCommand("thisEntityBlockUntilReachesDoor_DOOR","");
//	public static final EventScriptCommand thisEntityBlockUntilReachesEntity_ENTITY = new EventScriptCommand("thisEntityBlockUntilReachesEntity_ENTITY","");
//	public static final EventScriptCommand thisEntityBlockUntilReachesTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("thisEntityBlockUntilReachesTileXY_INTxTile1X_INTyTile1X","");
//	public static final EventScriptCommand thisEntityStandAndShuffle = new EventScriptCommand("thisEntityStandAndShuffle","");
//	public static final EventScriptCommand thisEntityStandAndShuffleAndFacePlayer = new EventScriptCommand("thisEntityStandAndShuffleAndFacePlayer","");
//	public static final EventScriptCommand thisEntityStandAndShuffleAndFaceEntity_ENTITY = new EventScriptCommand("thisEntityStandAndShuffleAndFaceEntity_ENTITY","");
//	public static final EventScriptCommand thisEntityAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
//	public static final EventScriptCommand thisEntityAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
//	public static final EventScriptCommand thisEntityAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
//	public static final EventScriptCommand thisEntityAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
//	public static final EventScriptCommand thisEntitySetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("thisEntitySetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
//	public static final EventScriptCommand thisEntityDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks","");
//	public static final EventScriptCommand thisEntityDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
//	public static final EventScriptCommand thisEntityStopAnimating = new EventScriptCommand("thisEntityStopAnimating","");
//	public static final EventScriptCommand thisEntitySetGlobalAnimationDisabled_BOOL = new EventScriptCommand("thisEntitySetGlobalAnimationDisabled_BOOL","");
//	public static final EventScriptCommand thisEntitySetMovementSpeed_INTticksPerPixel = new EventScriptCommand("thisEntitySetMovementSpeed_INTticksPerPixel","");
//	public static final EventScriptCommand thisEntitySetFaceMovementDirection_STRINGdirection = new EventScriptCommand("thisEntitySetFaceMovementDirection_STRINGdirection","");
//	public static final EventScriptCommand thisEntitySetNonWalkable_BOOL = new EventScriptCommand("thisEntitySetNonWalkable_BOOL","");
//	public static final EventScriptCommand thisEntitySetPushable_BOOL = new EventScriptCommand("thisEntitySetPushable_BOOL","");
//	public static final EventScriptCommand thisEntitySetToAlpha_FLOAT = new EventScriptCommand("thisEntitySetToAlpha_FLOAT","");
//	public static final EventScriptCommand thisEntityFadeOutDelete = new EventScriptCommand("thisEntityFadeOutDelete","");
//	public static final EventScriptCommand thisEntityDeleteInstantly = new EventScriptCommand("thisEntityDeleteInstantly","");


	static final EventScriptCommand e024 = new EventScriptCommand();
	public static final EventScriptCommand entitySetBehaviorQueueOnOff_ENTITY_BOOL = new EventScriptCommand("entitySetBehaviorQueueOnOff_ENTITY_BOOL","");
	public static final EventScriptCommand entitySetToArea_ENTITY_AREA = new EventScriptCommand("entitySetToArea_ENTITY_AREA","");
	public static final EventScriptCommand entitySetToDoor_ENTITY_DOOR = new EventScriptCommand("entitySetToDoor_ENTITY_DOOR","");
	public static final EventScriptCommand entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X = new EventScriptCommand("entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X","");
	public static final EventScriptCommand entityWalkToArea_ENTITY_AREA = new EventScriptCommand("entityWalkToArea_ENTITY_AREA","");
	public static final EventScriptCommand entityWalkToDoor_ENTITY_DOOR = new EventScriptCommand("entityWalkToDoor_ENTITY_DOOR","");
	public static final EventScriptCommand entityWalkToEntity_ENTITY_ENTITY = new EventScriptCommand("entityWalkToEntity_ENTITY_ENTITY","");
	public static final EventScriptCommand entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X = new EventScriptCommand("entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X","");
	public static final EventScriptCommand entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	public static final EventScriptCommand entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	public static final EventScriptCommand entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	public static final EventScriptCommand entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	public static final EventScriptCommand entityBlockUntilReachesArea_ENTITY_AREA = new EventScriptCommand("entityBlockUntilReachesArea_ENTITY_AREA","");
	public static final EventScriptCommand entityBlockUntilReachesDoor_ENTITY_DOOR = new EventScriptCommand("entityBlockUntilReachesDoor_ENTITY_DOOR","");
	public static final EventScriptCommand entityBlockUntilReachesEntity_ENTITY_ENTITY = new EventScriptCommand("entityBlockUntilReachesEntity_ENTITY_ENTITY","");
	public static final EventScriptCommand entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X = new EventScriptCommand("entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X","");
	public static final EventScriptCommand entityWalkToAreaAndBlockUntilThere_ENTITY_AREA = new EventScriptCommand("entityWalkToAreaAndBlockUntilThere_ENTITY_AREA","");
	public static final EventScriptCommand entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY = new EventScriptCommand("entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY","");
	public static final EventScriptCommand entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR = new EventScriptCommand("entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR","");
	public static final EventScriptCommand entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X = new EventScriptCommand("entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X","");
	public static final EventScriptCommand entityStandAndShuffle_ENTITY = new EventScriptCommand("entityStandAndShuffle_ENTITY","");
	public static final EventScriptCommand entityStandAndShuffleAndFacePlayer_ENTITY = new EventScriptCommand("entityStandAndShuffleAndFacePlayer_ENTITY","");
	public static final EventScriptCommand entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY = new EventScriptCommand("entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY","");
	public static final EventScriptCommand entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks","");
	public static final EventScriptCommand entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	public static final EventScriptCommand entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks","");
	public static final EventScriptCommand entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	public static final EventScriptCommand entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks","");
	public static final EventScriptCommand entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName = new EventScriptCommand("entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName","");
	public static final EventScriptCommand entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame = new EventScriptCommand("entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame","");
	public static final EventScriptCommand entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame = new EventScriptCommand("entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame","");
	public static final EventScriptCommand entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks","");
	public static final EventScriptCommand entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	public static final EventScriptCommand entityStopAnimating_ENTITY = new EventScriptCommand("entityStopAnimating_ENTITY","");
	public static final EventScriptCommand entitySetGlobalAnimationDisabled_ENTITY_BOOL = new EventScriptCommand("entitySetGlobalAnimationDisabled_ENTITY_BOOL","");
	public static final EventScriptCommand entitySetMovementSpeed_ENTITY_INTticksPerPixel = new EventScriptCommand("entitySetMovementSpeed_ENTITY_INTticksPerPixel","");
	public static final EventScriptCommand entitySetFaceMovementDirection_ENTITY_STRINGdirection = new EventScriptCommand("entitySetFaceMovementDirection_ENTITY_STRINGdirection","");
	public static final EventScriptCommand entitySetNonWalkable_ENTITY_BOOL = new EventScriptCommand("entitySetNonWalkable_ENTITY_BOOL","");
	public static final EventScriptCommand entitySetPushable_ENTITY_BOOL = new EventScriptCommand("entitySetPushable_ENTITY_BOOL","");
	public static final EventScriptCommand entitySetToAlpha_ENTITY_FLOAT = new EventScriptCommand("entitySetToAlpha_ENTITY_FLOAT","");
	public static final EventScriptCommand entityFadeOutDelete_ENTITY = new EventScriptCommand("entityFadeOutDelete_ENTITY","");
	public static final EventScriptCommand entityDeleteInstantly_ENTITY = new EventScriptCommand("entityDeleteInstantly_ENTITY","");

	static final EventScriptCommand e016 = new EventScriptCommand();
	public static final EventScriptCommand spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA = new EventScriptCommand("spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA","");
	public static final EventScriptCommand spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA = new EventScriptCommand("spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA","");
	public static final EventScriptCommand spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA = new EventScriptCommand("spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA","");
	public static final EventScriptCommand spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA = new EventScriptCommand("spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA","");
	static final EventScriptCommand e017 = new EventScriptCommand();
	public static final EventScriptCommand createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy = new EventScriptCommand("createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy","");
	public static final EventScriptCommand createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy = new EventScriptCommand("createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy","");
	public static final EventScriptCommand createScreenSpriteUnderText_SPRITE_INTx_INTy = new EventScriptCommand("createScreenSpriteUnderText_SPRITE_INTx_INTy","");
	public static final EventScriptCommand createScreenSpriteOverText_SPRITE_INTx_INTy = new EventScriptCommand("createScreenSpriteOverText_SPRITE_INTx_INTy","");


	static final EventScriptCommand e026 = new EventScriptCommand();
	public static final EventScriptCommand giveItem_ITEM = new EventScriptCommand("giveItem_ITEM","");
	public static final EventScriptCommand takeItem_ITEM = new EventScriptCommand("takeItem_ITEM","");
	public static final EventScriptCommand giveGame_GAME = new EventScriptCommand("giveGame_GAME","");
	public static final EventScriptCommand takeMoney_FLOAT = new EventScriptCommand("takeMoney_FLOAT","");
	public static final EventScriptCommand giveMoney_FLOAT = new EventScriptCommand("giveMoney_FLOAT","");

	static final EventScriptCommand e027 = new EventScriptCommand();
	public static final EventScriptCommand playSound_SOUND = new EventScriptCommand("playSound_SOUND","");
	public static final EventScriptCommand playSound_SOUND_FLOATvol = new EventScriptCommand("playSound_SOUND_FLOATvol","");
	public static final EventScriptCommand playSound_SOUND_FLOATvol_FLOATpitch_INTtimes = new EventScriptCommand("playSound_SOUND_FLOATvol_FLOATpitch_INTtimes","");
	public static final EventScriptCommand playMusicOnce_MUSIC = new EventScriptCommand("playMusicOnce_MUSIC","");
	public static final EventScriptCommand playMusicLoop_MUSIC = new EventScriptCommand("playMusicLoop_MUSIC","");
	public static final EventScriptCommand playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop = new EventScriptCommand("playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop","");
	public static final EventScriptCommand stopAllMusic = new EventScriptCommand("stopAllMusic","");
	public static final EventScriptCommand stopMusic_MUSIC = new EventScriptCommand("stopMusic_MUSIC","");
	public static final EventScriptCommand fadeOutMusic_MUSIC_INT = new EventScriptCommand("fadeOutMusic_MUSIC_INT","");
	public static final EventScriptCommand blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC = new EventScriptCommand("blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC","");
	public static final EventScriptCommand blockUntilMusicDone_MUSIC = new EventScriptCommand("blockUntilMusicDone_MUSIC","");
	public static final EventScriptCommand fadeOutAllMusic_INT = new EventScriptCommand("fadeOutAllMusic_INT","");
	public static final EventScriptCommand blockUntilAllMusicDone = new EventScriptCommand("blockUntilAllMusicDone","");

	static final EventScriptCommand e028 = new EventScriptCommand();
	public static final EventScriptCommand shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake = new EventScriptCommand("shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake","");
	public static final EventScriptCommand fadeToBlack_INTticks = new EventScriptCommand("fadeToBlack_INTticks","");
	public static final EventScriptCommand fadeFromBlack_INTticks = new EventScriptCommand("fadeFromBlack_INTticks","");
	public static final EventScriptCommand fadeToWhite_INTticks = new EventScriptCommand("fadeToWhite_INTticks","");
	public static final EventScriptCommand fadeFromWhite_INTticks = new EventScriptCommand("fadeFromWhite_INTticks","");
	static final EventScriptCommand e029 = new EventScriptCommand();
	public static final EventScriptCommand fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha = new EventScriptCommand("fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha","");
	public static final EventScriptCommand fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha = new EventScriptCommand("fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha","");
	public static final EventScriptCommand fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha = new EventScriptCommand("fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha","");
	public static final EventScriptCommand setInstantOverlay_INTr_INTg_INTb_FLOATa = new EventScriptCommand("setInstantOverlay_INTr_INTg_INTb_FLOATa","");
	public static final EventScriptCommand clearOverlay = new EventScriptCommand("clearOverlay","");

	public static final EventScriptCommand fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha = new EventScriptCommand("fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha","");
	public static final EventScriptCommand setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa = new EventScriptCommand("setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa","");
	public static final EventScriptCommand clearOverlayUnderLights = new EventScriptCommand("clearOverlayUnderLights","");

	public static final EventScriptCommand fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha = new EventScriptCommand("fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha","");
	public static final EventScriptCommand setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa = new EventScriptCommand("setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa","");
	public static final EventScriptCommand clearOverlayGroundLayer = new EventScriptCommand("clearOverlayGroundLayer","");

	static final EventScriptCommand e030 = new EventScriptCommand();
	public static final EventScriptCommand setLetterbox_BOOL = new EventScriptCommand("setLetterbox_BOOL","");
	public static final EventScriptCommand setLetterbox_BOOL_INTticks = new EventScriptCommand("setLetterbox_BOOL_INTticks","");
	public static final EventScriptCommand setLetterbox_BOOL_INTticks_INTsize = new EventScriptCommand("setLetterbox_BOOL_INTticks_INTsize","");
	public static final EventScriptCommand setLetterbox_BOOL_INTticks_FLOATsize = new EventScriptCommand("setLetterbox_BOOL_INTticks_FLOATsize","");
	public static final EventScriptCommand setBlur_BOOL = new EventScriptCommand("setBlur_BOOL","");
	public static final EventScriptCommand setMosaic_BOOL = new EventScriptCommand("setMosaic_BOOL","");
	public static final EventScriptCommand setHBlankWave_BOOL = new EventScriptCommand("setHBlankWave_BOOL","");
	public static final EventScriptCommand setRotate_BOOL = new EventScriptCommand("setRotate_BOOL","");
	public static final EventScriptCommand setBlackAndWhite_BOOL = new EventScriptCommand("setBlackAndWhite_BOOL","");
	public static final EventScriptCommand setInvertedColors_BOOL = new EventScriptCommand("setInvertedColors_BOOL","");
	public static final EventScriptCommand set8BitMode_BOOL = new EventScriptCommand("set8BitMode_BOOL","");
	static final EventScriptCommand e031 = new EventScriptCommand();
	public static final EventScriptCommand setEngineSpeed_FLOAT = new EventScriptCommand("setEngineSpeed_FLOAT","");
	static final EventScriptCommand e032 = new EventScriptCommand();
	public static final EventScriptCommand toggleLightOnOff_LIGHT = new EventScriptCommand("toggleLightOnOff_LIGHT","");
	public static final EventScriptCommand setLightOnOff_LIGHT_BOOL = new EventScriptCommand("setLightOnOff_LIGHT_BOOL","");
	public static final EventScriptCommand setLightFlicker_LIGHT_BOOL = new EventScriptCommand("setLightFlicker_LIGHT_BOOL","");
	public static final EventScriptCommand toggleAllLightsOnOff = new EventScriptCommand("toggleAllLightsOnOff","");
	public static final EventScriptCommand setAllLightsOnOff_BOOL = new EventScriptCommand("setAllLightsOnOff_BOOL","");
	static final EventScriptCommand e033 = new EventScriptCommand();
	public static final EventScriptCommand setRandomSpawn_BOOL = new EventScriptCommand("setRandomSpawn_BOOL","");
	public static final EventScriptCommand deleteRandoms = new EventScriptCommand("deleteRandoms","");
	static final EventScriptCommand e034 = new EventScriptCommand();
	public static final EventScriptCommand makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb = new EventScriptCommand("makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb","");
	public static final EventScriptCommand makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb = new EventScriptCommand("makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb","");
	public static final EventScriptCommand makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb = new EventScriptCommand("makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb","");
	public static final EventScriptCommand makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb = new EventScriptCommand("makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb","");
	public static final EventScriptCommand setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks = new EventScriptCommand("setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks","");




	static final EventScriptCommand e035 = new EventScriptCommand();
	public static final EventScriptCommand setShowClockCaption_BOOL = new EventScriptCommand("setShowClockCaption_BOOL","");
	public static final EventScriptCommand setShowDayCaption_BOOL = new EventScriptCommand("setShowDayCaption_BOOL","");
	public static final EventScriptCommand setShowMoneyCaption_BOOL = new EventScriptCommand("setShowMoneyCaption_BOOL","");
	public static final EventScriptCommand setShowAllStatusBarCaptions_BOOL = new EventScriptCommand("setShowAllStatusBarCaptions_BOOL","");
	public static final EventScriptCommand setShowStatusBar_BOOL = new EventScriptCommand("setShowStatusBar_BOOL","");

	public static final EventScriptCommand setShowNDButton_BOOL = new EventScriptCommand("setShowNDButton_BOOL","");
	public static final EventScriptCommand setShowGameStoreButton_BOOL = new EventScriptCommand("setShowGameStoreButton_BOOL","");
	public static final EventScriptCommand setShowStuffButton_BOOL = new EventScriptCommand("setShowStuffButton_BOOL","");
	public static final EventScriptCommand setShowAllButtons_BOOL = new EventScriptCommand("setShowAllButtons_BOOL","");

	public static final EventScriptCommand setNDEnabled_BOOL = new EventScriptCommand("setNDEnabled_BOOL","");
	public static final EventScriptCommand setGameStoreMenuEnabled_BOOL = new EventScriptCommand("setGameStoreMenuEnabled_BOOL","");
	public static final EventScriptCommand setStuffMenuEnabled_BOOL = new EventScriptCommand("setStuffMenuEnabled_BOOL","");
	public static final EventScriptCommand setAllMenusAndNDEnabled_BOOL = new EventScriptCommand("setAllMenusAndNDEnabled_BOOL","");


	static final EventScriptCommand e046 = new EventScriptCommand();
	public static final EventScriptCommand setClockUnknown = new EventScriptCommand("setClockUnknown","");
	public static final EventScriptCommand setClockNormal = new EventScriptCommand("setClockNormal","");
	public static final EventScriptCommand setTimePaused_BOOL = new EventScriptCommand("setTimePaused_BOOL","");
	public static final EventScriptCommand setTimeFastForward = new EventScriptCommand("setTimeFastForward","");
	public static final EventScriptCommand setTimeNormalSpeed = new EventScriptCommand("setTimeNormalSpeed","");
	static final EventScriptCommand e037 = new EventScriptCommand();


	public static final EventScriptCommand setNDOpen_BOOL = new EventScriptCommand("setNDOpen_BOOL","");
	public static final EventScriptCommand startGame = new EventScriptCommand("startGame","");
	public static final EventScriptCommand startBobsGameOnStadiumScreen_AREA = new EventScriptCommand("startBobsGameOnStadiumScreen_AREA","");
	public static final EventScriptCommand blockUntilBobsGameDead = new EventScriptCommand("blockUntilBobsGameDead","");
	public static final EventScriptCommand showLoginScreen = new EventScriptCommand("showLoginScreen","");
	//public static final EventScriptCommand closeND = new EventScriptCommand("closeND","");

	static final EventScriptCommand e038 = new EventScriptCommand();
	public static final EventScriptCommand closeAllMenusAndND = new EventScriptCommand("closeAllMenusAndND","");

	//public static final EventScriptCommand enableAllMenus = new EventScriptCommand("enableAllMenus","");
	static final EventScriptCommand e039 = new EventScriptCommand();
	public static final EventScriptCommand openStuffMenu = new EventScriptCommand("openStuffMenu","");
	public static final EventScriptCommand openItemsMenu = new EventScriptCommand("openItemsMenu","");
	public static final EventScriptCommand openLogMenu = new EventScriptCommand("openLogMenu","");
	public static final EventScriptCommand openStatusMenu = new EventScriptCommand("openStatusMenu","");
	public static final EventScriptCommand openFriendsMenu = new EventScriptCommand("openFriendsMenu","");
	public static final EventScriptCommand openSettingsMenu = new EventScriptCommand("openSettingsMenu","");
	public static final EventScriptCommand openGameStoreMenu = new EventScriptCommand("openGameStoreMenu","");

//	static final EventScriptCommand e040 = new EventScriptCommand();
//	public static final EventScriptCommand pushGameState = new EventScriptCommand("pushGameState","");
//	public static final EventScriptCommand popGameState = new EventScriptCommand("popGameState","");
//	static final EventScriptCommand e041 = new EventScriptCommand();
//	public static final EventScriptCommand showTitleScreen = new EventScriptCommand("showTitleScreen","");
//	public static final EventScriptCommand showCinemaEvent = new EventScriptCommand("showCinemaEvent","");
//	public static final EventScriptCommand runGlobalEvent = new EventScriptCommand("runGlobalEvent","");
//	static final EventScriptCommand e042 = new EventScriptCommand();




























}
