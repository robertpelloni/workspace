package com.bobsgame.client.engine.event;



import java.util.ArrayList;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.ClientMain;
import com.bobsgame.client.Cache;
import com.bobsgame.client.console.Console;

import com.bobsgame.client.engine.*;
import com.bobsgame.client.engine.entity.*;
import com.bobsgame.client.engine.entity.Character;
import com.bobsgame.client.engine.map.*;
import com.bobsgame.client.engine.sound.*;
import com.bobsgame.client.engine.text.*;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.EventData;
import com.bobsgame.shared.Utils;
import com.bobsgame.shared.MapData.RenderOrder;
import com.bobsgame.client.engine.game.*;
import com.bobsgame.client.engine.game.gui.statusbar.notification.*;
import com.bobsgame.client.engine.game.stadium.BobsGameStadium;



//=========================================================================================================================
public class Event extends ServerObject
{//=========================================================================================================================

	public static Logger log = (Logger) LoggerFactory.getLogger(Event.class);



	private boolean addedToQueue = false;
	private long timeAddedToQueue = 0;


	private boolean blockWhileNotHere=false;

	private long ticksCounter=0;


	public Sprite sprite = null;
	public Map map = null;
	public Door door = null;
	public Area area = null;
	public Entity entity = null;


	public EventCommand commandTree = null;
	public EventCommand currentCommand = null;


	private EventData data;


	//=========================================================================================================================
	public Event(Engine g, int id)
	{//=========================================================================================================================

		super(g);

		this.data = new EventData(id,"",0,"","");

		for(int i=0;i<EventManager().eventList.size();i++){if(EventManager().eventList.get(i).id()==data.id()){log.error("Event already exists:"+data.name());return;}}
		EventManager().eventList.add(this);//this tracks events created for areas and entities that don't exist after the map is unloaded, so they don't have to be loaded from the server and parsed again.
	}

	public Event(Engine g, EventData eventData) {
		super(g);

		this.data = eventData;
		setInitialized_S(true);

		for (int i = 0; i < EventManager().eventList.size(); i++) {
			if (EventManager().eventList.get(i).id() == data.id()) {
				log.error("Event already exists:" + data.name());
				return;
			}
		}

		// this tracks events created for areas and entities that don't exist after the map is unloaded,
		// so they don't have to be loaded from the server and parsed again.
		EventManager().eventList.add(this);
	}
	public EventData getData(){return data;}

	public int id(){return data.id();}
	public String name(){return data.name();}
	public int type(){return data.type();}
	public String comment(){return data.comment();}
	public String text(){return data.text();}

	public String getTYPEIDString(){return data.getTYPEIDString();}

	public void setID(int id){data.setID(id);}
	public void setName(String name){data.setName(name);}
	public void setType(int type){data.setType(type);}
	public void setComment(String comment){data.setComment(comment);}
	public void setText(String text){data.setText(text);}


	//=========================================================================================================================
	public synchronized void setData_S(EventData eventData)
	{//=========================================================================================================================
		this.data = eventData;
		setInitialized_S(true);
	}


	//=========================================================================================================================
	public Map getMap()
	{//=========================================================================================================================

		if(type()==EventData.TYPE_PROJECT_INITIAL_LOADER || type()==EventData.TYPE_PROJECT_CUTSCENE_DONT_RUN_UNTIL_CALLED)
		{
			return super.CurrentMap();
		}

		if(map!=null)return map;//DONE: any event changeMap events will have to set the map.
		if(door!=null)return door.getMap();
		if(area!=null)return area.getMap();
		if(entity!=null)return entity.getMap();

		if(Player()!=null)return Player().getMap();

		return CurrentMap();
	}

	//=========================================================================================================================
	public Map CurrentMap()
	{//=========================================================================================================================
		log.warn("Don't use CurrentMap() in Events!");
		return super.CurrentMap();

	}


	//=========================================================================================================================
	public boolean getWasAddedToQueue()
	{//=========================================================================================================================
		return addedToQueue;
	}
	//=========================================================================================================================
	public void setAddedToQueue()
	{//=========================================================================================================================
		addedToQueue=true;
		timeAddedToQueue = System.currentTimeMillis();
	}

	//=========================================================================================================================
	public void reset()
	{//=========================================================================================================================

		//reset to the first command
		commandTree = null;//we're going to have to reparse it each time because the MapObjects aren't persistent and the parameters point to them.
		currentCommand = null;

		addedToQueue=false;
		blockWhileNotHere=false;


	}

	//===============================================================================================
	private void parseEventString(String s)
	{//===============================================================================================


		commandTree = new EventCommand(Engine(), "none",null,0);

		EventCommand currentParent = commandTree;


		s = s.substring(1, s.length()-1);//split off { }, string now looks like "command,command,if(qualifier == TRUE){command,command}"

		//fadeFromBlack(INT.10000),
		//if(isFlagSet(FLAG.0) == TRUE){},if(isFlagSet(FLAG.0) == FALSE){setPlayerToTempPlayerWithSprite(SPRITE.938)}


		while(s.length()>0)
		{


			//log.info("Parsing Event String: "+s);

			if(s.startsWith("}"))
			{
				if(s.startsWith("},"))s = s.substring(2);
				else if(s.startsWith("}"))s = s.substring(1);

				currentParent = (EventCommand) currentParent.getParent();

			}
			else
			if(s.startsWith("if("))
			{
				//handle qualifier

				s = s.substring(3);//split off if(, string looks like "qualifier == TRUE){command,command}"

				String qualifier = s.substring(0,s.indexOf("{")-1);//get "qualifier == TRUE"
				s = s.substring(s.indexOf("{")+1);//string now looks like "command,command}"

				EventCommand e = EventCommand.parseEventCommandFromCommandString(Engine(),this,qualifier);


				currentParent.addChild(e);


				currentParent = e;

			}
			else
			{
				if(s.indexOf(",")!=-1)//there is another instruction
				{

					if(s.indexOf("}")!=-1&&s.indexOf("}")<s.indexOf(",")) //looks like "command()},command()
					{

						String command = s.substring(0,s.indexOf("}"));//get command
						s = s.substring(s.indexOf("}"));//split off command and comma

						EventCommand e = EventCommand.parseEventCommandFromCommandString(Engine(),this,command);

						currentParent.addChild(e);

					}
					else
					if(s.indexOf("),")!=-1&&s.indexOf("),")<s.indexOf("}"))//looks like "command(),command()}"
					{

						String command = s.substring(0,s.indexOf("),")+1);//get command
						s = s.substring(s.indexOf("),")+2);//split off command and comma

						EventCommand e = EventCommand.parseEventCommandFromCommandString(Engine(),this,command);

						currentParent.addChild(e);
					}
					else//looks like "command,command}"
					{
						String command = s.substring(0,s.indexOf(","));//get command
						s = s.substring(s.indexOf(",")+1);//split off command and comma

						EventCommand e = EventCommand.parseEventCommandFromCommandString(Engine(),this,command);

						currentParent.addChild(e);

					}

				}
				else
				{

					if(s.indexOf("}")!=-1)//looks like "command}" or "command}if(thing){}" or "command}}}"
					{

						String command = s.substring(0,s.indexOf("}"));//get command
						s = s.substring(s.indexOf("}"));//split off command and comma

						EventCommand e = EventCommand.parseEventCommandFromCommandString(Engine(),this,command);

						currentParent.addChild(e);

					}
					else //looks like "command"
					{
						String command = s;

						s=s.substring(command.length());

						EventCommand e = EventCommand.parseEventCommandFromCommandString(Engine(),this,command);

						currentParent.addChild(e);
					}
				}

			}
		}



	}







	//=========================================================================================================================
	public void run()
	{//=========================================================================================================================

		if(getLoadedFromServerSendRequestIfFalse())
		{


			if(blockWhileNotHere==true)
			{
				if(area!=null)
				{
					if(Player().isAreaBoundaryTouchingMyHitBox(area)==false&&Player().isWalkingIntoArea(area)==false)return;
				}

				if(door!=null)
				{
					if(Player().isWalkingIntoEntity(door)==false)return;
				}

				if(entity!=null)
				{
					if(Player().isEntityHitBoxTouchingMyHitBox(entity)==false&&Player().isWalkingIntoEntity(entity)==false)return;
				}
			}

			if(commandTree==null)
			{
				parseEventString(text());
				currentCommand = commandTree.getNextChild();//the actual commandTree command is blank. get the first child.
			}

			if(commandTree!=null)
			{

				//this is already done automatically when the parameter objects are parsed, simply by requesting the ID we create the object which updates itself from the server in its update() function.

				//go through all commands, all parameters, load all dialogues, gamestrings from server.
				//if this event requires a button press, put an action icon.
				//do i really need to do this? it is actually better to load the dialogues on-demand, so people can't hack the memory and see dialogue they can't access...
			}


			if(currentCommand!=null)doCommand();



			if(commandTree!=null)//set to null if the command changes the map, which clears the event queue and resets this event: but it's still running!
			if(currentCommand==null)
			{
				//remove this from EventManager.eventQueue when finished
				if(
						type()==EventData.TYPE_MAP_RUN_ONCE_BEFORE_LOAD
						||
						type()==EventData.TYPE_MAP_RUN_ONCE_AFTER_LOAD
						||
						type()==EventData.TYPE_PROJECT_INITIAL_LOADER
				)
				{
					reset();
					EventManager().runningEventQueue.remove(this);
				}
				else
				{
					//reset to the first command
					commandTree.currentChildIndex=0;
					currentCommand = commandTree.getNextChild();//the actual commandTree command is blank. get the first child.
				}
			}

		}



	}

	//=========================================================================================================================
	public void getNextCommandInParent()
	{//=========================================================================================================================

		if(currentCommand!=null)
		{

			if(currentCommand.getParent()==null)//this was the last command
			{
				currentCommand = null;
			}
			else
			{
				currentCommand = currentCommand.getParent().getNextChild();
				doCommand();
			}
		}
		else
		{
			//we must have changed the map and reset this event.

		}


	}



	//=========================================================================================================================
	public void getNextCommand()
	{//=========================================================================================================================

		if(currentCommand!=null)
		{
			//increment command into currentCommand's children
			if(currentCommand.children.size()>0)
			{
				currentCommand = currentCommand.getNextChild();
				doCommand();
			}
			else getNextCommandInParent();
		}
		else
		{
			//we must have changed the map and reset this event.

		}
	}





	//===============================================================================================
	private void getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(boolean b)
	{//===============================================================================================

		if(
				(currentCommand.type==EventCommand.TYPE_QUALIFIER_TRUE&&b==true)
				||
				(currentCommand.type==EventCommand.TYPE_QUALIFIER_FALSE&&b==false)
			)
			{
				//increment command into currentCommand's children
				getNextCommand();
			}
			else
			//skip to the next command in currentCommand's parent, skipping over this block
			getNextCommandInParent();


	}

	public void doCommand() {
		if (currentCommand == null) {
			return;
		}

		//if (!Objects.equals(currentCommand.commandString, "playerDoAnimationByNameLoop")) {

			if (currentCommand.parameterList != null) {
				StringBuilder argList = new StringBuilder();
				for (int i = 0; i < currentCommand.parameterList.size(); i++) {
					argList.append(" ").append(currentCommand.parameterList.get(i).parameterString);
				}
				log.debug("Current Command: " + currentCommand.commandString + " with args " + argList);
			} else {
				log.debug("Current Command: " + currentCommand.commandString);
			}
		//}

		// qualifiers. check if TRUE or FALSE. skip children if false.
		if (currentCommand.parameterList != null) {
			for (int i = 0; i < currentCommand.parameterList.size(); i++) {
				EventParameter e = currentCommand.parameterList.get(i);
				e.updateParameterVariablesFromString(this);
			}
		}

		if(currentCommand.commandString.equals(EventData.isPlayerTouchingThisArea.getCommand())){isPlayerTouchingThisArea();}
		else if(currentCommand.commandString.equals(EventData.isPlayerWalkingIntoThisDoor.getCommand())){isPlayerWalkingIntoThisDoor();}
		else if(currentCommand.commandString.equals(EventData.isPlayerTouchingThisEntity.getCommand())){isPlayerTouchingThisEntity();}
		else if(currentCommand.commandString.equals(EventData.isPlayerTouchingAnyEntityUsingThisSprite.getCommand())){isPlayerTouchingAnyEntityUsingThisSprite();}
		else if(currentCommand.commandString.equals(EventData.isPlayerWalkingIntoDoor_DOOR.getCommand())){isPlayerWalkingIntoDoor_DOOR();}
		else if(currentCommand.commandString.equals(EventData.isPlayerWalkingIntoWarp_WARP.getCommand())){isPlayerWalkingIntoWarp_WARP();}
		else if(currentCommand.commandString.equals(EventData.isActionButtonHeld.getCommand())){isActionButtonHeld();}
		else if(currentCommand.commandString.equals(EventData.isPlayerAutoPilotOn.getCommand())){isPlayerAutoPilotOn();}
		else if(currentCommand.commandString.equals(EventData.isFlagSet_FLAG.getCommand())){isFlagSet_FLAG();}
		else if(currentCommand.commandString.equals(EventData.hasSkillAtLeast_SKILL_FLOAT1.getCommand())){hasSkillAtLeast_SKILL_FLOAT1();}
		else if(currentCommand.commandString.equals(EventData.isCurrentState_STATE.getCommand())){isCurrentState_STATE();}
		else if(currentCommand.commandString.equals(EventData.isPlayerStandingInArea_AREA.getCommand())){isPlayerStandingInArea_AREA();}
		else if(currentCommand.commandString.equals(EventData.isEntityStandingInArea_ENTITY_AREA.getCommand())){isEntityStandingInArea_ENTITY_AREA();}
		else if(currentCommand.commandString.equals(EventData.hourPastOrEqualTo_INT23.getCommand())){hourPastOrEqualTo_INT23();}
		else if(currentCommand.commandString.equals(EventData.hourLessThan_INT23.getCommand())){hourLessThan_INT23();}
		else if(currentCommand.commandString.equals(EventData.minutePastOrEqualTo_INT59.getCommand())){minutePastOrEqualTo_INT59();}
		else if(currentCommand.commandString.equals(EventData.minuteLessThan_INT59.getCommand())){minuteLessThan_INT59();}
		else if(currentCommand.commandString.equals(EventData.hasMoneyAtLeastAmount_FLOAT.getCommand())){hasMoneyAtLeastAmount_FLOAT();}
		else if(currentCommand.commandString.equals(EventData.hasMoneyLessThanAmount_FLOAT.getCommand())){hasMoneyLessThanAmount_FLOAT();}
		else if(currentCommand.commandString.equals(EventData.hasItem_ITEM.getCommand())){hasItem_ITEM();}
		else if(currentCommand.commandString.equals(EventData.hasGame_GAME.getCommand())){hasGame_GAME();}
		else if(currentCommand.commandString.equals(EventData.isPlayerMale.getCommand())){isPlayerMale();}
		else if(currentCommand.commandString.equals(EventData.isPlayerFemale.getCommand())){isPlayerFemale();}
		else if(currentCommand.commandString.equals(EventData.isAnyEntityUsingSprite_SPRITE.getCommand())){isAnyEntityUsingSprite_SPRITE();}
		else if(currentCommand.commandString.equals(EventData.isAnyEntityUsingSpriteAtArea_SPRITE_AREA.getCommand())){isAnyEntityUsingSpriteAtArea_SPRITE_AREA();}
		else if(currentCommand.commandString.equals(EventData.isEntitySpawned_ENTITY.getCommand())){isEntitySpawned_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.isEntityAtArea_ENTITY_AREA.getCommand())){isEntityAtArea_ENTITY_AREA();}
		else if(currentCommand.commandString.equals(EventData.isAreaEmpty_AREA.getCommand())){isAreaEmpty_AREA();}
		else if(currentCommand.commandString.equals(EventData.hasFinishedDialogue_DIALOGUE.getCommand())){hasFinishedDialogue_DIALOGUE();}
		else if(currentCommand.commandString.equals(EventData.isTextBoxOpen.getCommand())){isTextBoxOpen();}
		else if(currentCommand.commandString.equals(EventData.isTextAnswerBoxOpen.getCommand())){isTextAnswerBoxOpen();}
		else if(currentCommand.commandString.equals(EventData.isTextAnswerSelected_INT4.getCommand())){isTextAnswerSelected_INT4();}
		else if(currentCommand.commandString.equals(EventData.isTextAnswerSelected_STRING.getCommand())){isTextAnswerSelected_STRING();}
		else if(currentCommand.commandString.equals(EventData.randomEqualsOneOutOfLessThan_INT.getCommand())){randomEqualsOneOutOfLessThan_INT();}
		else if(currentCommand.commandString.equals(EventData.randomEqualsOneOutOfIncluding_INT.getCommand())){randomEqualsOneOutOfIncluding_INT();}
		else if(currentCommand.commandString.equals(EventData.isAnyMusicPlaying.getCommand())){isAnyMusicPlaying();}
		else if(currentCommand.commandString.equals(EventData.isMusicPlaying_MUSIC.getCommand())){isMusicPlaying();}
		else if(currentCommand.commandString.equals(EventData.isRaining.getCommand())){isRaining();}
		else if(currentCommand.commandString.equals(EventData.isWindy.getCommand())){isWindy();}
		else if(currentCommand.commandString.equals(EventData.isSnowing.getCommand())){isSnowing();}
		else if(currentCommand.commandString.equals(EventData.isFoggy.getCommand())){isFoggy();}
//		else if(currentCommand.commandString.equals(EventData.isPlayerHolding.getCommand())){isPlayerHolding();}
//		else if(currentCommand.commandString.equals(EventData.isPlayerWearing.getCommand())){isPlayerWearing();}
		else if(currentCommand.commandString.equals(EventData.isMapOutside.getCommand())){isMapOutside();}
		else if(currentCommand.commandString.equals(EventData.hasTalkedToThisToday.getCommand())){hasTalkedToThisToday();}
		else if(currentCommand.commandString.equals(EventData.hasBeenMinutesSinceFlagSet_FLAG_INT.getCommand())){hasBeenMinutesSinceFlagSet_FLAG_INT();}
		else if(currentCommand.commandString.equals(EventData.hasBeenHoursSinceFlagSet_FLAG_INT23.getCommand())){hasBeenHoursSinceFlagSet_FLAG_INT23();}
		else if(currentCommand.commandString.equals(EventData.hasBeenDaysSinceFlagSet_FLAG_INT.getCommand())){hasBeenDaysSinceFlagSet_FLAG_INT();}
		else if(currentCommand.commandString.equals(EventData.isThisActivated.getCommand())){isThisActivated();}
		else if(currentCommand.commandString.equals(EventData.haveSecondsPassedSinceActivated_INT.getCommand())){haveSecondsPassedSinceActivated_INT();}
		else if(currentCommand.commandString.equals(EventData.haveMinutesPassedSinceActivated_INT.getCommand())){haveMinutesPassedSinceActivated_INT();}
		else if(currentCommand.commandString.equals(EventData.haveHoursPassedSinceActivated_INT.getCommand())){haveHoursPassedSinceActivated_INT();}
		else if(currentCommand.commandString.equals(EventData.haveDaysPassedSinceActivated_INT.getCommand())){haveDaysPassedSinceActivated_INT();}
		else if(currentCommand.commandString.equals(EventData.hasActivatedThisEver.getCommand())){hasActivatedThisEver();}
		else if(currentCommand.commandString.equals(EventData.hasActivatedThisSinceEnterRoom.getCommand())){hasActivatedThisSinceEnterRoom();}
		else if(currentCommand.commandString.equals(EventData.hasBeenHereEver.getCommand())){hasBeenHereEver();}
		else if(currentCommand.commandString.equals(EventData.hasBeenHereSinceEnterRoom.getCommand())){hasBeenHereSinceEnterRoom();}
		else if(currentCommand.commandString.equals(EventData.haveSecondsPassedSinceBeenHere_INT.getCommand())){haveSecondsPassedSinceBeenHere_INT();}
		else if(currentCommand.commandString.equals(EventData.haveMinutesPassedSinceBeenHere_INT.getCommand())){haveMinutesPassedSinceBeenHere_INT();}
		else if(currentCommand.commandString.equals(EventData.haveHoursPassedSinceBeenHere_INT.getCommand())){haveHoursPassedSinceBeenHere_INT();}
		else if(currentCommand.commandString.equals(EventData.haveDaysPassedSinceBeenHere_INT.getCommand())){haveDaysPassedSinceBeenHere_INT();}
		else if(currentCommand.commandString.equals(EventData.isLightOn_LIGHT.getCommand())){isLightOn_LIGHT();}







		//commands
		else if(currentCommand.commandString.equals(EventData.alwaysBlockWhileNotStandingHere.getCommand())){alwaysBlockWhileNotStandingHere();}

		else if(currentCommand.commandString.equals(EventData.blockUntilActionButtonPressed.getCommand())){blockUntilActionButtonPressed();}
		else if(currentCommand.commandString.equals(EventData.blockUntilActionCaptionButtonPressed_STRING.getCommand())){blockUntilActionCaptionButtonPressed_STRING();}
		else if(currentCommand.commandString.equals(EventData.blockUntilCancelButtonPressed.getCommand())){blockUntilCancelButtonPressed();}
		else if(currentCommand.commandString.equals(EventData.blockForTicks_INT.getCommand())){blockForTicks_INT();}
		else if(currentCommand.commandString.equals(EventData.blockUntilClockHour_INT23.getCommand())){blockUntilClockHour_INT23();}
		else if(currentCommand.commandString.equals(EventData.blockUntilClockMinute_INT59.getCommand())){blockUntilClockMinute_INT59();}

		else if(currentCommand.commandString.equals(EventData.loadMapState_STATE.getCommand())){loadMapState_STATE();}
		else if(currentCommand.commandString.equals(EventData.runEvent_EVENT.getCommand())){runEvent_EVENT();}
		else if(currentCommand.commandString.equals(EventData.blockUntilEventDone_EVENT.getCommand())){blockUntilEventDone_EVENT();}
		else if(currentCommand.commandString.equals(EventData.clearThisEvent.getCommand())){clearThisEvent();}
		else if(currentCommand.commandString.equals(EventData.clearEvent_EVENT.getCommand())){clearEvent_EVENT();}

		else if(currentCommand.commandString.equals(EventData.setThisActivated_BOOL.getCommand())){setThisActivated_BOOL();}
		else if(currentCommand.commandString.equals(EventData.toggleThisActivated.getCommand())){toggleThisActivated();}

		else if(currentCommand.commandString.equals(EventData.setLastBeenHereTime.getCommand())){setLastBeenHereTime();}
		else if(currentCommand.commandString.equals(EventData.resetLastBeenHereTime.getCommand())){resetLastBeenHereTime();}

		else if(currentCommand.commandString.equals(EventData.setFlag_FLAG_BOOL.getCommand())){setFlag_FLAG_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setFlagTrue_FLAG.getCommand())){setFlagTrue_FLAG();}
		else if(currentCommand.commandString.equals(EventData.setFlagFalse_FLAG.getCommand())){setFlagFalse_FLAG();}

		else if(currentCommand.commandString.equals(EventData.giveSkillPoints_SKILL_INT.getCommand())){giveSkillPoints_SKILL_INT();}
		else if(currentCommand.commandString.equals(EventData.removeSkillPoints_SKILL_INT.getCommand())){removeSkillPoints_SKILL_INT();}
		else if(currentCommand.commandString.equals(EventData.setSkillPoints_SKILL_INT.getCommand())){setSkillPoints_SKILL_INT();}

		else if(currentCommand.commandString.equals(EventData.enterThisDoor.getCommand())){enterThisDoor();}
		else if(currentCommand.commandString.equals(EventData.enterThisWarp.getCommand())){enterThisWarp();}
		else if(currentCommand.commandString.equals(EventData.enterDoor_DOOR.getCommand())){enterDoor_DOOR();}
		else if(currentCommand.commandString.equals(EventData.enterWarp_WARP.getCommand())){enterWarp_WARP();}
		else if(currentCommand.commandString.equals(EventData.changeMap_MAP_AREA.getCommand())){changeMap_MAP_AREA();}
		else if(currentCommand.commandString.equals(EventData.changeMap_MAP_DOOR.getCommand())){changeMap_MAP_DOOR();}
		else if(currentCommand.commandString.equals(EventData.changeMap_MAP_INT_INT.getCommand())){changeMap_MAP_INT_INT();}
		else if(currentCommand.commandString.equals(EventData.changeMap_MAP_WARP.getCommand())){changeMap_MAP_WARP();}

		else if(currentCommand.commandString.equals(EventData.doDialogue_DIALOGUE.getCommand())){doDialogue_DIALOGUE();}
		else if(currentCommand.commandString.equals(EventData.doDialogueWithCaption_DIALOGUE.getCommand())){doDialogueWithCaption_DIALOGUE();}
		else if(currentCommand.commandString.equals(EventData.doDialogueIfNew_DIALOGUE.getCommand())){doDialogueIfNew_DIALOGUE();}

		else if(currentCommand.commandString.equals(EventData.setSpriteBox0_ENTITY.getCommand())){setSpriteBox0_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.setSpriteBox1_ENTITY.getCommand())){setSpriteBox1_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.setSpriteBox0_SPRITE.getCommand())){setSpriteBox0_SPRITE();}
		else if(currentCommand.commandString.equals(EventData.setSpriteBox1_SPRITE.getCommand())){setSpriteBox1_SPRITE();}

		else if(currentCommand.commandString.equals(EventData.blockUntilTextBoxClosed.getCommand())){blockUntilTextBoxClosed();}
		else if(currentCommand.commandString.equals(EventData.blockUntilTextAnswerBoxClosed.getCommand())){blockUntilTextAnswerBoxClosed();}

		else if(currentCommand.commandString.equals(EventData.doCinematicTextNoBorder_DIALOGUE_INTy.getCommand())){doCinematicTextNoBorder_DIALOGUE_INTy();}
		//else if(currentCommand.commandString.equals(EventData.playVideo_VIDEO.getCommand())){playVideo_VIDEO();}


		else if(currentCommand.commandString.equals(EventData.setDoorOpenAnimation_DOOR_BOOLopenClose.getCommand())){setDoorOpenAnimation_DOOR_BOOLopenClose();}
		else if(currentCommand.commandString.equals(EventData.setDoorActionIcon_DOOR_BOOLonOff.getCommand())){setDoorActionIcon_DOOR_BOOLonOff();}
		else if(currentCommand.commandString.equals(EventData.setDoorDestination_DOOR_DOORdestination.getCommand())){setDoorDestination_DOOR_DOORdestination();}
		else if(currentCommand.commandString.equals(EventData.setAreaActionIcon_AREA_BOOLonOff.getCommand())){setAreaActionIcon_AREA_BOOLonOff();}
		else if(currentCommand.commandString.equals(EventData.setWarpDestination_WARP_WARPdestination.getCommand())){setWarpDestination_WARP_WARPdestination();}






		else if(currentCommand.commandString.equals(EventData.setCameraNoTarget.getCommand())){setCameraNoTarget();}
		else if(currentCommand.commandString.equals(EventData.setCameraTargetToArea_AREA.getCommand())){setCameraTarget_AREA();}
		else if(currentCommand.commandString.equals(EventData.setCameraTargetToEntity_ENTITY.getCommand())){setCameraTarget_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.setCameraIgnoreBounds_BOOL.getCommand())){setCameraIgnoreBounds_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setCameraTargetToPlayer.getCommand())){setCameraTargetToPlayer();}
		else if(currentCommand.commandString.equals(EventData.blockUntilCameraReaches_AREA.getCommand())){blockUntilCameraReaches_AREA();}
		else if(currentCommand.commandString.equals(EventData.blockUntilCameraReaches_ENTITY.getCommand())){blockUntilCameraReaches_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.blockUntilCameraReachesPlayer.getCommand())){blockUntilCameraReachesPlayer();}
		else if(currentCommand.commandString.equals(EventData.pushCameraState.getCommand())){pushCameraState();}
		else if(currentCommand.commandString.equals(EventData.popCameraState.getCommand())){popCameraState();}
		else if(currentCommand.commandString.equals(EventData.setKeyboardCameraZoom_BOOL.getCommand())){setKeyboardCameraZoom_BOOL();}
		else if(currentCommand.commandString.equals(EventData.enableKeyboardCameraZoom.getCommand())){enableKeyboardCameraZoom();}
		else if(currentCommand.commandString.equals(EventData.disableKeyboardCameraZoom.getCommand())){disableKeyboardCameraZoom();}
		else if(currentCommand.commandString.equals(EventData.setCameraAutoZoomByPlayerMovement_BOOL.getCommand())){setCameraAutoZoomByPlayerMovement_BOOL();}
		else if(currentCommand.commandString.equals(EventData.enableCameraAutoZoomByPlayerMovement.getCommand())){enableCameraAutoZoomByPlayerMovement();}
		else if(currentCommand.commandString.equals(EventData.disableCameraAutoZoomByPlayerMovement.getCommand())){disableCameraAutoZoomByPlayerMovement();}
		else if(currentCommand.commandString.equals(EventData.setCameraZoom_FLOAT.getCommand())){setCameraZoom_FLOAT();}
		else if(currentCommand.commandString.equals(EventData.setCameraSpeed_FLOAT.getCommand())){setCameraSpeed_FLOAT();}


		else if(currentCommand.commandString.equals(EventData.setPlayerToTempPlayerWithSprite_SPRITE.getCommand())){setPlayerToTempPlayerWithSprite_SPRITE();}
		else if(currentCommand.commandString.equals(EventData.setPlayerToNormalPlayer.getCommand())){setPlayerToNormalPlayer();}
		else if(currentCommand.commandString.equals(EventData.setPlayerExists_BOOL.getCommand())){setPlayerExists_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setPlayerControlsEnabled_BOOL.getCommand())){setPlayerControlsEnabled_BOOL();}
		else if(currentCommand.commandString.equals(EventData.enablePlayerControls.getCommand())){enablePlayerControls();}
		else if(currentCommand.commandString.equals(EventData.disablePlayerControls.getCommand())){disablePlayerControls();}
		else if(currentCommand.commandString.equals(EventData.setPlayerAutoPilot_BOOL.getCommand())){setPlayerAutoPilot_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setPlayerShowNameCaption_BOOL.getCommand())){setPlayerShowNameCaption_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setPlayerShowAccountTypeCaption_BOOL.getCommand())){setPlayerShowAccountTypeCaption_BOOL();}

		else if(currentCommand.commandString.equals(EventData.playerSetBehaviorQueueOnOff_BOOL.getCommand())){playerSetBehaviorQueueOnOff_BOOL();}
		else if(currentCommand.commandString.equals(EventData.playerSetToArea_AREA.getCommand())){playerSetToArea_AREA();}
		else if(currentCommand.commandString.equals(EventData.playerSetToDoor_DOOR.getCommand())){playerSetToDoor_DOOR();}
		else if(currentCommand.commandString.equals(EventData.playerSetToTileXY_INTxTile1X_INTyTile1X.getCommand())){playerSetToTileXY_INTxTile1X_INTyTile1X();}
		else if(currentCommand.commandString.equals(EventData.playerWalkToArea_AREA.getCommand())){playerWalkToArea_AREA();}
		else if(currentCommand.commandString.equals(EventData.playerWalkToDoor_DOOR.getCommand())){playerWalkToDoor_DOOR();}
		else if(currentCommand.commandString.equals(EventData.playerWalkToEntity_ENTITY.getCommand())){playerWalkToEntity_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.playerWalkToTileXY_INTxTile1X_INTyTile1X.getCommand())){playerWalkToTileXY_INTxTile1X_INTyTile1X();}
//		else if(currentCommand.commandString.equals(EventData.playerMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal.getCommand())){playerMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();}
//		else if(currentCommand.commandString.equals(EventData.playerMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal.getCommand())){playerMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();}
//		else if(currentCommand.commandString.equals(EventData.playerMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal.getCommand())){playerMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();}
//		else if(currentCommand.commandString.equals(EventData.playerMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal.getCommand())){playerMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();}
		else if(currentCommand.commandString.equals(EventData.playerBlockUntilReachesArea_AREA.getCommand())){playerBlockUntilReachesArea_AREA();}
		else if(currentCommand.commandString.equals(EventData.playerBlockUntilReachesDoor_DOOR.getCommand())){playerBlockUntilReachesDoor_DOOR();}
		else if(currentCommand.commandString.equals(EventData.playerBlockUntilReachesEntity_ENTITY.getCommand())){playerBlockUntilReachesEntity_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X.getCommand())){playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X();}
		else if(currentCommand.commandString.equals(EventData.playerWalkToAreaAndBlockUntilThere_AREA.getCommand())){playerWalkToAreaAndBlockUntilThere_AREA();}
		else if(currentCommand.commandString.equals(EventData.playerWalkToEntityAndBlockUntilThere_ENTITY.getCommand())){playerWalkToEntityAndBlockUntilThere_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.playerWalkToDoorAndBlockUntilThere_DOOR.getCommand())){playerWalkToDoorAndBlockUntilThere_DOOR();}
		else if(currentCommand.commandString.equals(EventData.playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X.getCommand())){playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X();}
		else if(currentCommand.commandString.equals(EventData.playerStandAndShuffle.getCommand())){playerStandAndShuffle();}
//		else if(currentCommand.commandString.equals(EventData.playerStandAndShuffleAndFacePlayer.getCommand())){playerStandAndShuffleAndFacePlayer();}
		else if(currentCommand.commandString.equals(EventData.playerStandAndShuffleAndFaceEntity_ENTITY.getCommand())){playerStandAndShuffleAndFaceEntity_ENTITY();}
//		else if(currentCommand.commandString.equals(EventData.playerAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks.getCommand())){playerAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks();}
//		else if(currentCommand.commandString.equals(EventData.playerAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks.getCommand())){playerAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks();}
//		else if(currentCommand.commandString.equals(EventData.playerAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks.getCommand())){playerAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks();}
//		else if(currentCommand.commandString.equals(EventData.playerAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks.getCommand())){playerAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks();}
//		else if(currentCommand.commandString.equals(EventData.playerSetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks.getCommand())){playerSetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks();}
		else if(currentCommand.commandString.equals(EventData.playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame.getCommand())){playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame();}
		else if(currentCommand.commandString.equals(EventData.playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame.getCommand())){playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame();}
		else if(currentCommand.commandString.equals(EventData.playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks.getCommand())){playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks();}
		else if(currentCommand.commandString.equals(EventData.playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks.getCommand())){playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks();}
		else if(currentCommand.commandString.equals(EventData.playerStopAnimating.getCommand())){playerStopAnimating();}
		else if(currentCommand.commandString.equals(EventData.playerSetGlobalAnimationDisabled_BOOL.getCommand())){playerSetGlobalAnimationDisabled_BOOL();}
		else if(currentCommand.commandString.equals(EventData.playerSetMovementSpeed_INTticksPerPixel.getCommand())){playerSetMovementSpeed_INTticksPerPixel();}
		else if(currentCommand.commandString.equals(EventData.playerSetFaceMovementDirection_STRINGdirection.getCommand())){playerSetFaceMovementDirection_STRINGdirection();}
//		else if(currentCommand.commandString.equals(EventData.playerSetNonWalkable_BOOL.getCommand())){playerSetNonWalkable_BOOL();}
//		else if(currentCommand.commandString.equals(EventData.playerSetPushable_BOOL.getCommand())){playerSetPushable_BOOL();}
		else if(currentCommand.commandString.equals(EventData.playerSetToAlpha_FLOAT.getCommand())){playerSetToAlpha_FLOAT();}
//		else if(currentCommand.commandString.equals(EventData.playerFadeOutDelete.getCommand())){playerFadeOutDelete();}
//		else if(currentCommand.commandString.equals(EventData.playerDeleteInstantly.getCommand())){playerDeleteInstantly();}


		else if(currentCommand.commandString.equals(EventData.entitySetBehaviorQueueOnOff_ENTITY_BOOL.getCommand())){entitySetBehaviorQueueOnOff_ENTITY_BOOL();}
		else if(currentCommand.commandString.equals(EventData.entitySetToArea_ENTITY_AREA.getCommand())){entitySetToArea_ENTITY_AREA();}
		else if(currentCommand.commandString.equals(EventData.entitySetToDoor_ENTITY_DOOR.getCommand())){entitySetToDoor_ENTITY_DOOR();}
		else if(currentCommand.commandString.equals(EventData.entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X.getCommand())){entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X();}
		else if(currentCommand.commandString.equals(EventData.entityWalkToArea_ENTITY_AREA.getCommand())){entityWalkToArea_ENTITY_AREA();}
		else if(currentCommand.commandString.equals(EventData.entityWalkToDoor_ENTITY_DOOR.getCommand())){entityWalkToDoor_ENTITY_DOOR();}
		else if(currentCommand.commandString.equals(EventData.entityWalkToEntity_ENTITY_ENTITY.getCommand())){entityWalkToEntity_ENTITY_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X.getCommand())){entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X();}
		else if(currentCommand.commandString.equals(EventData.entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal.getCommand())){entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();}
		else if(currentCommand.commandString.equals(EventData.entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal.getCommand())){entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();}
		else if(currentCommand.commandString.equals(EventData.entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal.getCommand())){entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();}
		else if(currentCommand.commandString.equals(EventData.entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal.getCommand())){entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();}
		else if(currentCommand.commandString.equals(EventData.entityBlockUntilReachesArea_ENTITY_AREA.getCommand())){entityBlockUntilReachesArea_ENTITY_AREA();}
		else if(currentCommand.commandString.equals(EventData.entityBlockUntilReachesDoor_ENTITY_DOOR.getCommand())){entityBlockUntilReachesDoor_ENTITY_DOOR();}
		else if(currentCommand.commandString.equals(EventData.entityBlockUntilReachesEntity_ENTITY_ENTITY.getCommand())){entityBlockUntilReachesEntity_ENTITY_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X.getCommand())){entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X();}
		else if(currentCommand.commandString.equals(EventData.entityWalkToAreaAndBlockUntilThere_ENTITY_AREA.getCommand())){entityWalkToAreaAndBlockUntilThere_ENTITY_AREA();}
		else if(currentCommand.commandString.equals(EventData.entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY.getCommand())){entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR.getCommand())){entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR();}
		else if(currentCommand.commandString.equals(EventData.entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X.getCommand())){entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X();}

		else if(currentCommand.commandString.equals(EventData.entityStandAndShuffle_ENTITY.getCommand())){entityStandAndShuffle_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.entityStandAndShuffleAndFacePlayer_ENTITY.getCommand())){entityStandAndShuffleAndFacePlayer_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY.getCommand())){entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks.getCommand())){entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks();}
		else if(currentCommand.commandString.equals(EventData.entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks.getCommand())){entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks();}
		else if(currentCommand.commandString.equals(EventData.entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks.getCommand())){entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks();}
		else if(currentCommand.commandString.equals(EventData.entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks.getCommand())){entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks();}
		else if(currentCommand.commandString.equals(EventData.entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks.getCommand())){entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks();}
		else if(currentCommand.commandString.equals(EventData.entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName.getCommand())){entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName();}
		else if(currentCommand.commandString.equals(EventData.entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame.getCommand())){entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame();}
		else if(currentCommand.commandString.equals(EventData.entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame.getCommand())){entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame();}
		else if(currentCommand.commandString.equals(EventData.entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks.getCommand())){entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks();}
		else if(currentCommand.commandString.equals(EventData.entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks.getCommand())){entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks();}
		else if(currentCommand.commandString.equals(EventData.entityStopAnimating_ENTITY.getCommand())){entityStopAnimating_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.entitySetGlobalAnimationDisabled_ENTITY_BOOL.getCommand())){entitySetGlobalAnimationDisabled_ENTITY_BOOL();}
		else if(currentCommand.commandString.equals(EventData.entitySetMovementSpeed_ENTITY_INTticksPerPixel.getCommand())){entitySetMovementSpeed_ENTITY_INTticksPerPixel();}
		else if(currentCommand.commandString.equals(EventData.entitySetFaceMovementDirection_ENTITY_STRINGdirection.getCommand())){entitySetFaceMovementDirection_ENTITY_STRINGdirection();}
		else if(currentCommand.commandString.equals(EventData.entitySetNonWalkable_ENTITY_BOOL.getCommand())){entitySetNonWalkable_ENTITY_BOOL();}
		else if(currentCommand.commandString.equals(EventData.entitySetPushable_ENTITY_BOOL.getCommand())){entitySetPushable_ENTITY_BOOL();}
		else if(currentCommand.commandString.equals(EventData.entitySetToAlpha_ENTITY_FLOAT.getCommand())){entitySetToAlpha_ENTITY_FLOAT();}
		else if(currentCommand.commandString.equals(EventData.entityFadeOutDelete_ENTITY.getCommand())){entityFadeOutDelete_ENTITY();}
		else if(currentCommand.commandString.equals(EventData.entityDeleteInstantly_ENTITY.getCommand())){entityDeleteInstantly_ENTITY();}


		else if(currentCommand.commandString.equals(EventData.spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA.getCommand())){spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA();}
		else if(currentCommand.commandString.equals(EventData.spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA.getCommand())){spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA();}
		else if(currentCommand.commandString.equals(EventData.spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA.getCommand())){spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA();}
		else if(currentCommand.commandString.equals(EventData.spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA.getCommand())){spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA();}

		else if(currentCommand.commandString.equals(EventData.createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy.getCommand())){createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy();}
		else if(currentCommand.commandString.equals(EventData.createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy.getCommand())){createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy();}
		else if(currentCommand.commandString.equals(EventData.createScreenSpriteUnderText_SPRITE_INTx_INTy.getCommand())){createScreenSpriteUnderText_SPRITE_INTx_INTy();}
		else if(currentCommand.commandString.equals(EventData.createScreenSpriteOverText_SPRITE_INTx_INTy.getCommand())){createScreenSpriteOverText_SPRITE_INTx_INTy();}




		else if(currentCommand.commandString.equals(EventData.giveItem_ITEM.getCommand())){giveItem_ITEM();}
		else if(currentCommand.commandString.equals(EventData.takeItem_ITEM.getCommand())){takeItem_ITEM();}
		else if(currentCommand.commandString.equals(EventData.giveGame_GAME.getCommand())){giveGame_GAME();}
		else if(currentCommand.commandString.equals(EventData.takeMoney_FLOAT.getCommand())){takeMoney_FLOAT();}
		else if(currentCommand.commandString.equals(EventData.giveMoney_FLOAT.getCommand())){giveMoney_FLOAT();}


		else if(currentCommand.commandString.equals(EventData.playSound_SOUND.getCommand())){playSound_SOUND();}
		else if(currentCommand.commandString.equals(EventData.playSound_SOUND_FLOATvol.getCommand())){playSound_SOUND_FLOATvol();}
		else if(currentCommand.commandString.equals(EventData.playSound_SOUND_FLOATvol_FLOATpitch_INTtimes.getCommand())){playSound_SOUND_FLOATvol_FLOATpitch_INTtimes();}
		else if(currentCommand.commandString.equals(EventData.playMusicOnce_MUSIC.getCommand())){playMusicOnce_MUSIC();}
		else if(currentCommand.commandString.equals(EventData.playMusicLoop_MUSIC.getCommand())){playMusicLoop_MUSIC();}
		else if(currentCommand.commandString.equals(EventData.playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop.getCommand())){playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop();}
		else if(currentCommand.commandString.equals(EventData.stopMusic_MUSIC.getCommand())){stopMusic_MUSIC();}
		else if(currentCommand.commandString.equals(EventData.stopAllMusic.getCommand())){stopAllMusic();}
		else if(currentCommand.commandString.equals(EventData.fadeOutMusic_MUSIC_INT.getCommand())){fadeOutMusic_MUSIC_INT();}
		else if(currentCommand.commandString.equals(EventData.fadeOutAllMusic_INT.getCommand())){fadeOutAllMusic_INT();}
		else if(currentCommand.commandString.equals(EventData.blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC.getCommand())){blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC();}
		else if(currentCommand.commandString.equals(EventData.blockUntilMusicDone_MUSIC.getCommand())){blockUntilMusicDone_MUSIC();}
		else if(currentCommand.commandString.equals(EventData.blockUntilAllMusicDone.getCommand())){blockUntilAllMusicDone();}


		else if(currentCommand.commandString.equals(EventData.shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake.getCommand())){shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake();}
		else if(currentCommand.commandString.equals(EventData.fadeToBlack_INTticks.getCommand())){fadeToBlack_INTticks();}
		else if(currentCommand.commandString.equals(EventData.fadeFromBlack_INTticks.getCommand())){fadeFromBlack_INTticks();}
		else if(currentCommand.commandString.equals(EventData.fadeToWhite_INTticks.getCommand())){fadeToWhite_INTticks();}
		else if(currentCommand.commandString.equals(EventData.fadeFromWhite_INTticks.getCommand())){fadeFromWhite_INTticks();}

		else if(currentCommand.commandString.equals(EventData.fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha.getCommand())){fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha();}
		else if(currentCommand.commandString.equals(EventData.fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha.getCommand())){fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha();}
		else if(currentCommand.commandString.equals(EventData.fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha.getCommand())){fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha();}
		else if(currentCommand.commandString.equals(EventData.setInstantOverlay_INTr_INTg_INTb_FLOATa.getCommand())){setInstantOverlay_INTr_INTg_INTb_FLOATa();}
		else if(currentCommand.commandString.equals(EventData.clearOverlay.getCommand())){clearOverlay();}

		else if(currentCommand.commandString.equals(EventData.fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha.getCommand())){fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha();}
		else if(currentCommand.commandString.equals(EventData.setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa.getCommand())){setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa();}
		else if(currentCommand.commandString.equals(EventData.clearOverlayUnderLights.getCommand())){clearOverlayUnderLights();}
		else if(currentCommand.commandString.equals(EventData.fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha.getCommand())){fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha();}
		else if(currentCommand.commandString.equals(EventData.setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa.getCommand())){setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa();}
		else if(currentCommand.commandString.equals(EventData.clearOverlayGroundLayer.getCommand())){clearOverlayGroundLayer();}

		else if(currentCommand.commandString.equals(EventData.setLetterbox_BOOL.getCommand())){setLetterbox_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setLetterbox_BOOL_INTticks.getCommand())){setLetterbox_BOOL_INTticks();}
		else if(currentCommand.commandString.equals(EventData.setLetterbox_BOOL_INTticks_INTsize.getCommand())){setLetterbox_BOOL_INTticks_INTsize();}
		else if(currentCommand.commandString.equals(EventData.setLetterbox_BOOL_INTticks_FLOATsize.getCommand())){setLetterbox_BOOL_INTticks_FLOATsize();}
		else if(currentCommand.commandString.equals(EventData.setBlur_BOOL.getCommand())){setBlur_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setMosaic_BOOL.getCommand())){setMosaic_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setHBlankWave_BOOL.getCommand())){setHBlankWave_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setRotate_BOOL.getCommand())){setRotate_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setBlackAndWhite_BOOL.getCommand())){setBlackAndWhite_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setInvertedColors_BOOL.getCommand())){setInvertedColors_BOOL();}
		else if(currentCommand.commandString.equals(EventData.set8BitMode_BOOL.getCommand())){set8BitMode_BOOL();}

		else if(currentCommand.commandString.equals(EventData.setEngineSpeed_FLOAT.getCommand())){setEngineSpeed_FLOAT();}

		else if(currentCommand.commandString.equals(EventData.toggleLightOnOff_LIGHT.getCommand())){toggleLightOnOff_LIGHT();}
		else if(currentCommand.commandString.equals(EventData.setLightOnOff_LIGHT_BOOL.getCommand())){setLightOnOff_LIGHT_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setLightFlicker_LIGHT_BOOL.getCommand())){setLightFlicker_LIGHT_BOOL();}
		else if(currentCommand.commandString.equals(EventData.toggleAllLightsOnOff.getCommand())){toggleAllLightsOnOff();}
		else if(currentCommand.commandString.equals(EventData.setAllLightsOnOff_BOOL.getCommand())){setAllLightsOnOff_BOOL();}

		else if(currentCommand.commandString.equals(EventData.setRandomSpawn_BOOL.getCommand())){setRandomSpawn_BOOL();}
		else if(currentCommand.commandString.equals(EventData.deleteRandoms.getCommand())){deleteRandoms();}

		else if(currentCommand.commandString.equals(EventData.makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb.getCommand())){makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb();}
		else if(currentCommand.commandString.equals(EventData.makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb.getCommand())){makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb();}
		else if(currentCommand.commandString.equals(EventData.makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb.getCommand())){makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb();}
		else if(currentCommand.commandString.equals(EventData.makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb.getCommand())){makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb();}
		else if(currentCommand.commandString.equals(EventData.setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks.getCommand())){setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks();}

		else if(currentCommand.commandString.equals(EventData.setShowClockCaption_BOOL.getCommand())){setShowClockCaption_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setShowDayCaption_BOOL.getCommand())){setShowDayCaption_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setShowMoneyCaption_BOOL.getCommand())){setShowMoneyCaption_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setShowAllStatusBarCaptions_BOOL.getCommand())){setShowAllStatusBarCaptions_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setShowStatusBar_BOOL.getCommand())){setShowStatusBar_BOOL();}


		else if(currentCommand.commandString.equals(EventData.setShowNDButton_BOOL.getCommand())){setShowNDButton_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setShowGameStoreButton_BOOL.getCommand())){setShowGameStoreButton_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setShowStuffButton_BOOL.getCommand())){setShowStuffButton_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setShowAllButtons_BOOL.getCommand())){setShowAllButtons_BOOL();}


		else if(currentCommand.commandString.equals(EventData.setNDEnabled_BOOL.getCommand())){setNDEnabled_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setGameStoreMenuEnabled_BOOL.getCommand())){setGameStoreMenuEnabled_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setStuffMenuEnabled_BOOL.getCommand())){setStuffMenuEnabled_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setAllMenusAndNDEnabled_BOOL.getCommand())){setAllMenusAndNDEnabled_BOOL();}


		else if(currentCommand.commandString.equals(EventData.setClockUnknown.getCommand())){setClockUnknown();}
		else if(currentCommand.commandString.equals(EventData.setClockNormal.getCommand())){setClockNormal();}
		else if(currentCommand.commandString.equals(EventData.setTimePaused_BOOL.getCommand())){setTimePaused_BOOL();}
		else if(currentCommand.commandString.equals(EventData.setTimeFastForward.getCommand())){setTimeFastForward();}
		else if(currentCommand.commandString.equals(EventData.setTimeNormalSpeed.getCommand())){setTimeNormalSpeed();}

		else if(currentCommand.commandString.equals(EventData.setNDOpen_BOOL.getCommand())){setNDOpen_BOOL();}
		else if(currentCommand.commandString.equals(EventData.startGame.getCommand())){startGame();}
		else if(currentCommand.commandString.equals(EventData.startBobsGameOnStadiumScreen_AREA.getCommand())){startBobsGameOnStadiumScreen_AREA();}
		else if(currentCommand.commandString.equals(EventData.blockUntilBobsGameDead.getCommand())){blockUntilBobsGameDead();}
		else if(currentCommand.commandString.equals(EventData.showLoginScreen.getCommand())){showLoginScreen();}








		else if(currentCommand.commandString.equals(EventData.closeAllMenusAndND.getCommand())){closeAllMenusAndND();}

		//else if(currentCommand.commandString.equals(EventData.enableAllMenus.getCommand())){enableAllMenusAndND();}

		else if(currentCommand.commandString.equals(EventData.openStuffMenu.getCommand())){openStuffMenu();}
		else if(currentCommand.commandString.equals(EventData.openItemsMenu.getCommand())){openItemsMenu();}
		else if(currentCommand.commandString.equals(EventData.openLogMenu.getCommand())){openLogMenu();}
		else if(currentCommand.commandString.equals(EventData.openStatusMenu.getCommand())){openStatusMenu();}
		else if(currentCommand.commandString.equals(EventData.openFriendsMenu.getCommand())){openFriendsMenu();}
		else if(currentCommand.commandString.equals(EventData.openSettingsMenu.getCommand())){openSettingsMenu();}
		else if(currentCommand.commandString.equals(EventData.openGameStoreMenu.getCommand())){openGameStoreMenu();}

//		else if(currentCommand.commandString.equals(EventData.pushGameState.getCommand())){pushGameState();}
//		else if(currentCommand.commandString.equals(EventData.popGameState.getCommand())){popGameState();}
//
//		else if(currentCommand.commandString.equals(EventData.showTitleScreen.getCommand())){showTitleScreen();}
//		else if(currentCommand.commandString.equals(EventData.showCinemaEvent.getCommand())){showCinemaEvent();}
//		else if(currentCommand.commandString.equals(EventData.runGlobalEvent.getCommand())){runGlobalEvent();}


		else {log.error("Error! Unknown Command: "+currentCommand.commandString);getNextCommandInParent();}


	}






















	//===============================================================================================
	private void isPlayerTouchingThisArea()
	{//===============================================================================================


		if(this.area==null)log.error("isPlayerTouchingThisArea() in event with no area!");

		if(this.area.getClass().equals(WarpArea.class))
		{
			getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Player().isWalkingIntoArea(area));
		}
		else
		{
			getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Player().isAreaBoundaryTouchingMyHitBox(area));
		}
	}




	//===============================================================================================
	private void isPlayerWalkingIntoThisDoor()
	{//===============================================================================================

		if(this.door==null)log.error("isPlayerWalkingIntoThisDoor() in event with no door!");

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Player().isWalkingIntoEntity(door));
	}




	//===============================================================================================
	private void isPlayerTouchingThisEntity()
	{//===============================================================================================

		if(this.entity==null)log.error("isPlayerTouchingThisEntity() in event with no entity!");

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Player().isEntityHitBoxTouchingMyHitBox(entity));
	}




	//===============================================================================================
	private void isPlayerTouchingAnyEntityUsingThisSprite()
	{//===============================================================================================


		if(this.sprite==null)log.error("isPlayerTouchingAnyEntityUsingThisSprite() in event with no sprite!");

		ArrayList<Entity> e = getMap().getAllEntitiesUsingSpriteAsset(sprite);

		boolean b = false;

		for(int i=0;i<e.size();i++)
		{
			if(Player().isEntityHitBoxTouchingMyHitBox(e.get(i)))b=true;
		}

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(b);
	}





	//===============================================================================================
	private void isPlayerWalkingIntoDoor_DOOR()
	{//===============================================================================================
		int p=0;
		if(currentCommand.parameterList.size()>0)
		{
			Door d = (Door) currentCommand.parameterList.get(p++).object;

			getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Player().isWalkingIntoEntity(d));
		}

	}

	//===============================================================================================
	private void isPlayerWalkingIntoWarp_WARP()
	{//===============================================================================================
		int p=0;
		if(currentCommand.parameterList.size()>0)
		{
			WarpArea d = (WarpArea) currentCommand.parameterList.get(p++).object;

			getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Player().isWalkingIntoArea(d));
		}

	}
	//===============================================================================================
	private void isPlayerAutoPilotOn()
	{//===============================================================================================


		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Player().isAutoPilotOn());

	}

	//===============================================================================================
	private void isActionButtonHeld()
	{//===============================================================================================


		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(ControlsManager().BUTTON_ACTION_HELD);

	}


	//===============================================================================================
	private void isFlagSet_FLAG()
	{//===============================================================================================
		int p=0;

		if(currentCommand.parameterList.size()>0)
		{
			Flag f = (Flag) currentCommand.parameterList.get(p++).object; //we don't particularly need to know what the actual flag name is... ID is fine.

			//Boolean value = f.checkServerValueAndResetAfterSuccessfulReturn();
			//if(value!=null)
			boolean value = f.getValue_S();
			{
				getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(value);
			}
		}
	}



	//===============================================================================================
	private void hasSkillAtLeast_SKILL_FLOAT1()
	{//===============================================================================================
		int p=0;


		if(currentCommand.parameterList.size()>1)
		{
			Skill s = (Skill) currentCommand.parameterList.get(p++).object;
			float f = currentCommand.parameterList.get(p++).f;

			float value = s.getValue_S();

			{
				getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(value>=f);
			}

		}



	}





	//===============================================================================================
	private void isCurrentState_STATE()
	{//===============================================================================================
		int p=0;

		if(currentCommand.parameterList.size()>0)
		{
			MapState s = (MapState) currentCommand.parameterList.get(p++).object;

			if(s!=null)
			{
				getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getMap().currentState==s);
			}
		}
	}





	//===============================================================================================
	private void isPlayerStandingInArea_AREA()
	{//===============================================================================================
		int p=0;

		if(currentCommand.parameterList.size()>0)
		{
			Area area = (Area) currentCommand.parameterList.get(p++).object;

			getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Player().isAreaBoundaryTouchingMyHitBox(area));
		}
	}





	//===============================================================================================
	private void isEntityStandingInArea_ENTITY_AREA()
	{//===============================================================================================
		int p=0;

		if(currentCommand.parameterList.size()>1)
		{
			Entity entity = (Entity) currentCommand.parameterList.get(p++).object;
			Area area = (Area) currentCommand.parameterList.get(p++).object;

			getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(entity.isAreaBoundaryTouchingMyHitBox(area));
		}
	}





	//===============================================================================================
	private void hourPastOrEqualTo_INT23()
	{//===============================================================================================
		int p=0;

		int hour = currentCommand.parameterList.get(p++).i;

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Clock().hour>=hour);
	}





	//===============================================================================================
	private void hourLessThan_INT23()
	{//===============================================================================================
		int p=0;

		int hour = currentCommand.parameterList.get(p++).i;

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Clock().hour<hour);

	}





	//===============================================================================================
	private void minutePastOrEqualTo_INT59()
	{//===============================================================================================
		int p=0;

		int minute = currentCommand.parameterList.get(p++).i;

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Clock().minute>=minute);

	}





	//===============================================================================================
	private void minuteLessThan_INT59()
	{//===============================================================================================
		int p=0;
		int minute = currentCommand.parameterList.get(p++).i;

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Clock().minute<minute);

	}





	//===============================================================================================
	private void hasMoneyAtLeastAmount_FLOAT()
	{//===============================================================================================
		int p=0;
		float money = currentCommand.parameterList.get(p++).f;

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Wallet().money>=money);
	}





	//===============================================================================================
	private void hasMoneyLessThanAmount_FLOAT()
	{//===============================================================================================
		int p=0;
		float money = currentCommand.parameterList.get(p++).f;

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Wallet().money<money);
	}





	//===============================================================================================
	private void hasItem_ITEM()
	{//===============================================================================================
		int p=0;
		Item item = (Item)currentCommand.parameterList.get(p++).object;

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(item.getHaveItemValue_S());

	}





	//===============================================================================================
	private void hasGame_GAME()
	{//===============================================================================================
		int p=0;
		Item item = (Item)currentCommand.parameterList.get(p++).object;

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(item.getHaveItemValue_S());
	}





	//===============================================================================================
	private void isPlayerMale()
	{//===============================================================================================


		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Player().isMale);

	}





	//===============================================================================================
	private void isPlayerFemale()
	{//===============================================================================================


		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Player().isFemale);

	}





	//===============================================================================================
	private void isAnyEntityUsingSprite_SPRITE()
	{//===============================================================================================
		int p=0;


		Sprite sprite = (Sprite) currentCommand.parameterList.get(p++).object;

		// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
		if(sprite==null)return;//block until sprite has loaded.


		boolean b = getMap().isAnyEntityUsingSpriteAsset(sprite);

		if(sprite!=null)
		{
			getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(b);
		}

	}





	//===============================================================================================
	private void isAnyEntityUsingSpriteAtArea_SPRITE_AREA()
	{//===============================================================================================
		int p=0;

		Sprite sprite = (Sprite) currentCommand.parameterList.get(p++).object;
		Area a = (Area) currentCommand.parameterList.get(p++).object;

		// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
		if(sprite==null)return;//block until sprite has loaded.

		ArrayList<Entity> e = a.getMap().getAllEntitiesTouchingArea(a);


		boolean b = false;

		for(int i=0;i<e.size();i++)
		{
			if(e.get(i).sprite==sprite)b=true;
		}

		if(sprite!=null)
		{
			getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(b);
		}

	}





	//===============================================================================================
	private void isEntitySpawned_ENTITY()
	{//===============================================================================================
		int p=0;


		Entity e = (Entity) currentCommand.parameterList.get(p++).object;

		//will be null if it couldn't find the object ID after searching the entityList

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(e!=null);

	}





	//===============================================================================================
	private void isEntityAtArea_ENTITY_AREA()
	{//===============================================================================================
		int p=0;

		Entity e = (Entity) currentCommand.parameterList.get(p++).object;


		if(e!=null)
		{

			Area a = (Area) currentCommand.parameterList.get(p++).object;

			boolean b = a.isEntityHitBoxTouchingMyBoundary(e);

			getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(b);
		}
	}


	//===============================================================================================
	private void isAreaEmpty_AREA()
	{//===============================================================================================
		int p=0;
		Area a = (Area) currentCommand.parameterList.get(p++).object;


		if(a!=null)
		{
			boolean b = a.getMap().isAnyEntityTouchingArea(a);

			getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(b);
		}
	}





	//===============================================================================================
	private void hasFinishedDialogue_DIALOGUE()
	{//===============================================================================================
		int p=0;

		Dialogue d = (Dialogue) currentCommand.parameterList.get(p++).object;

		if(d!=null)
		{
			//Boolean value = d.checkServerValueAndResetAfterSuccessfulReturn();
			//if(value!=null)

			boolean value = d.getDialogueDoneValue_S();
			{
				getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(value);
			}
		}
	}





	//===============================================================================================
	private void isTextBoxOpen()
	{//===============================================================================================


		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(TextManager().isTextBoxOpen());

	}





	//===============================================================================================
	private void isTextAnswerBoxOpen()
	{//===============================================================================================


		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(TextManager().isTextAnswerBoxOpen());

	}





	//===============================================================================================
	private void isTextAnswerSelected_INT4()
	{//===============================================================================================

		// TODO Auto-generated method stub


		//handle both string and int, can have two different parameters

	}


	//===============================================================================================
	private void isTextAnswerSelected_STRING()
	{//===============================================================================================

		// TODO Auto-generated method stub


		//handle both string and int, can have two different parameters

	}




	//===============================================================================================
	private void randomEqualsOneOutOfLessThan_INT()
	{//===============================================================================================
		int p=0;

		int i = currentCommand.parameterList.get(p++).i;

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Utils.randLessThan(i)==1);

	}





	//===============================================================================================
	private void randomEqualsOneOutOfIncluding_INT()
	{//===============================================================================================
		int p=0;

		int i = currentCommand.parameterList.get(p++).i;

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Utils.randUpToIncluding(i)==1);

	}





	//===============================================================================================
	private void isAnyMusicPlaying()
	{//===============================================================================================


		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(AudioManager().isAnyMusicPlaying());

	}





	//===============================================================================================
	private void isMusicPlaying()
	{//===============================================================================================
		int p=0;

		Music m = (Music) currentCommand.parameterList.get(p++).object;

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(AudioManager().isMusicPlaying(m));

	}





	//===============================================================================================
	private void isRaining()
	{//===============================================================================================


		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(MapManager().isRaining());

	}





	//===============================================================================================
	private void isWindy()
	{//===============================================================================================


		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(MapManager().isWindy());

	}





	//===============================================================================================
	private void isSnowing()
	{//===============================================================================================


		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(MapManager().isSnowing());

	}



	//===============================================================================================
	private void isFoggy()
	{//===============================================================================================


		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(MapManager().isFoggy());

	}


//	//===============================================================================================
//	private void isPlayerHolding()/
//	{//===============================================================================================
//		// TODO Auto-generated method stub
//
//	}
//
//	//===============================================================================================
//	private void isPlayerWearing()
//	{//===============================================================================================
//		// TODO Auto-generated method stub
//
//	}


	//===============================================================================================
	private void isMapOutside()
	{//===============================================================================================


		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getMap().isOutside());

	}


	//===============================================================================================
	private void hasTalkedToThisToday()
	{//===============================================================================================



		boolean gotServerValue = false;
		boolean hasTalkedTo = true;

		if(area!=null)
		{
			Boolean b = area.checkServerTalkedToTodayValueAndResetAfterSuccessfulReturn();
			if(b!=null)
			{
				gotServerValue=true;
				if(b.booleanValue()==false)hasTalkedTo=false;
			}
		}
		if(door!=null)
		{
			Boolean b = door.checkServerTalkedToTodayValueAndResetAfterSuccessfulReturn();
			if(b!=null)
			{
				gotServerValue=true;
				if(b.booleanValue()==false)hasTalkedTo=false;
			}
		}
		if(entity!=null)
		{
			Boolean b = entity.checkServerTalkedToTodayValueAndResetAfterSuccessfulReturn();
			if(b!=null)
			{
				gotServerValue=true;
				if(b.booleanValue()==false)hasTalkedTo=false;
			}
		}


		if(gotServerValue)
		{
			getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(hasTalkedTo);
		}

	}



	//===============================================================================================
	private void hasBeenMinutesSinceFlagSet_FLAG_INT()
	{//===============================================================================================
		int p=0;
		Flag f = (Flag)currentCommand.parameterList.get(p++).object;

		int i = currentCommand.parameterList.get(p++).i;

		long lastTimeSet = f.getTimeSet();
		long time = System.currentTimeMillis();

		long millisecondsPassed = time-lastTimeSet;
		long secondsPassed = millisecondsPassed/1000;
		long minutesPassed = secondsPassed/60;

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(minutesPassed>=i);

	}


	//===============================================================================================
	private void hasBeenHoursSinceFlagSet_FLAG_INT23()
	{//===============================================================================================
		int p=0;
		Flag f = (Flag)currentCommand.parameterList.get(p++).object;

		int i = currentCommand.parameterList.get(p++).i;

		long lastTimeSet = f.getTimeSet();
		long time = System.currentTimeMillis();

		long millisecondsPassed = time-lastTimeSet;
		long secondsPassed = millisecondsPassed/1000;
		long minutesPassed = secondsPassed/60;
		long hoursPassed = minutesPassed/60;

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(hoursPassed>=i);

	}

	//===============================================================================================
	private void hasBeenDaysSinceFlagSet_FLAG_INT()
	{//===============================================================================================
		int p=0;
		Flag f = (Flag)currentCommand.parameterList.get(p++).object;

		int i = currentCommand.parameterList.get(p++).i;

		long lastTimeSet = f.getTimeSet();
		long time = System.currentTimeMillis();

		long millisecondsPassed = time-lastTimeSet;
		long secondsPassed = millisecondsPassed/1000;
		long minutesPassed = secondsPassed/60;
		long hoursPassed = minutesPassed/60;
		long daysPassed = hoursPassed/24;

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(daysPassed>=i);

	}

	//===============================================================================================
	private void isThisActivated()
	{//===============================================================================================

		if(sprite!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(sprite.isActivated());
		if(entity!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(entity.isActivated());
		if(door!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(door.isActivated());
		if(map!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(map.isActivated());
		if(area!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(area.isActivated());

	}


	private void haveSecondsPassedSinceActivated_INT()
	{
		// TODO

	}


	private void haveMinutesPassedSinceActivated_INT()
	{
		// TODO

	}


	private void haveHoursPassedSinceActivated_INT()
	{
		// TODO

	}


	private void haveDaysPassedSinceActivated_INT()
	{
		// TODO

	}

	//===============================================================================================
	private void hasActivatedThisEver()
	{//===============================================================================================

		// TODO rename this to "since account created"

		//TODO: have every object have a flagTime sort of deal

		//maybe an underlying time hashtable indexed by TYPEID, gets stored to and from gamesave
		//would kind of be a lot of gamesave updates, maybe update it once every time i enter or leave a room.

	}





	//===============================================================================================
	private void hasActivatedThisSinceEnterRoom()
	{//===============================================================================================


		//TODO: make this "since logged on"

		if(sprite!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(sprite.wasEverActivated());
		if(entity!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(entity.wasEverActivated());
		if(door!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(door.wasEverActivated());
		if(map!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(map.wasEverActivated());
		if(area!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(area.wasEverActivated());
	}





	//===============================================================================================
	private void hasBeenHereEver()
	{//===============================================================================================


		// TODO Auto-generated method stub
	}





	//===============================================================================================
	private void hasBeenHereSinceEnterRoom()
	{//===============================================================================================


		//TODO: make this "since logged on"


		if(sprite!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(sprite.wasEverHere());
		if(entity!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(entity.wasEverHere());
		if(door!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(door.wasEverHere());
		if(map!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(map.wasEverHere());
		if(area!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(area.wasEverHere());

	}



	private void haveSecondsPassedSinceBeenHere_INT()
	{
		// TODO

	}

	private void haveMinutesPassedSinceBeenHere_INT()
	{
		// TODO

	}


	//===============================================================================================
	private void haveDaysPassedSinceBeenHere_INT()
	{//===============================================================================================

		// TODO Auto-generated method stub

	}


	//===============================================================================================
	private void haveHoursPassedSinceBeenHere_INT()
	{//===============================================================================================

		// TODO Auto-generated method stub

	}
























	//===============================================================================================
	private void isLightOn_LIGHT()//(INT)
	{//===============================================================================================
		int p=0;
		Light s = (Light) currentCommand.parameterList.get(p++).object;
		if(s!=null)getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(s.toggleOnOffToggle);

	}

	//===============================================================================================
	private void alwaysBlockWhileNotStandingHere()
	{//===============================================================================================

		blockWhileNotHere=true;
		getNextCommand();

	}




	//===============================================================================================
	private void blockUntilActionButtonPressed()
	{//===============================================================================================

		if(ControlsManager().BUTTON_ACTION_PRESSED)getNextCommand();

	}




	//===============================================================================================
	private void blockUntilActionCaptionButtonPressed_STRING()
	{//===============================================================================================
		int p=0;
		GameString s = (GameString) currentCommand.parameterList.get(p++).object;

		if(s.getInitialized_S()==false)
		{
			return; //wait for it to receive server data in its update() function
		}
		else
		{
			if(area!=null)
			{
				if(ActionManager().area(area,s.text()))
				{
					getNextCommand();
				}

			}
			if(door!=null)
			{
				if(ActionManager().entity(door,s.text()))
				{
					getNextCommand();
				}
			}

			if(entity!=null)
			{
				if(ActionManager().entity(entity,s.text()))
				{
					getNextCommand();
				}
			}
		}

	}




	//===============================================================================================
	private void blockUntilCancelButtonPressed()
	{//===============================================================================================

		if(ControlsManager().BUTTON_LSHIFT_PRESSED)getNextCommand();
	}



	//===============================================================================================
	private void blockForTicks_INT()
	{//===============================================================================================
		int p=0;

		int i = currentCommand.parameterList.get(p++).i;


		ticksCounter+=Engine().realWorldTicksPassed();

		if(ticksCounter>=i)
		{
			ticksCounter=0;
			getNextCommand();
		}

	}




	//===============================================================================================
	private void blockUntilClockHour_INT23()
	{//===============================================================================================
		int p=0;

		int hour = currentCommand.parameterList.get(p++).i;

		if(Clock().hour<=hour)getNextCommand();

	}




	//===============================================================================================
	private void blockUntilClockMinute_INT59()
	{//===============================================================================================
		int p=0;
		int minute = currentCommand.parameterList.get(p++).i;

		if(Clock().minute<=minute)getNextCommand();

	}




	//===============================================================================================
	private void loadMapState_STATE()
	{//===============================================================================================
		int p=0;

		MapState s = (MapState)currentCommand.parameterList.get(p++).object;

		getMap().loadMapState(s);

		getNextCommand();
	}




	//===============================================================================================
	private void runEvent_EVENT()
	{//===============================================================================================
		int p=0;
		Event e = (Event)currentCommand.parameterList.get(p++).object;

		EventManager().addToEventQueueIfNotThere(e);

		getNextCommand();
	}

	//===============================================================================================
	private void blockUntilEventDone_EVENT()
	{//===============================================================================================
		int p=0;
		Event e = (Event)currentCommand.parameterList.get(p++).object;

		if(e.addedToQueue==false)getNextCommand();
	}


	//===============================================================================================
	private void clearEvent_EVENT()
	{//===============================================================================================
		int p=0;
		Event e = (Event)currentCommand.parameterList.get(p++).object;
		e.reset();
		EventManager().runningEventQueue.remove(e);

		getNextCommand();

	}
	//===============================================================================================
	private void clearThisEvent()
	{//===============================================================================================

		currentCommand = null;

	}

	//===============================================================================================
	private void setThisActivated_BOOL()
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;


		if(sprite!=null)sprite.setActivated(b);
		if(entity!=null)entity.setActivated(b);
		if(door!=null)door.setActivated(b);
		if(map!=null)map.setActivated(b);
		if(area!=null)area.setActivated(b);

		getNextCommand();
	}
	//===============================================================================================
	private void toggleThisActivated()
	{//===============================================================================================

		if(sprite!=null)sprite.toggleActivated();
		if(entity!=null)entity.toggleActivated();
		if(door!=null)door.toggleActivated();
		if(map!=null)map.toggleActivated();
		if(area!=null)area.toggleActivated();

		getNextCommand();
	}



	//===============================================================================================
	private void setLastBeenHereTime()
	{//===============================================================================================

		if(sprite!=null)sprite.setLastTimeHere();
		if(entity!=null)entity.setLastTimeHere();
		if(door!=null)door.setLastTimeHere();
		if(map!=null)map.setLastTimeHere();
		if(area!=null)area.setLastTimeHere();

		getNextCommand();
	}
	//===============================================================================================
	private void resetLastBeenHereTime()
	{//===============================================================================================

		if(sprite!=null)sprite.resetLastTimeHere();
		if(entity!=null)entity.resetLastTimeHere();
		if(door!=null)door.resetLastTimeHere();
		if(map!=null)map.resetLastTimeHere();
		if(area!=null)area.resetLastTimeHere();

		getNextCommand();
	}


	//===============================================================================================
	private void setFlag_FLAG_BOOL()
	{//===============================================================================================
		int p=0;
		Flag f = (Flag) currentCommand.parameterList.get(p++).object;
		boolean b = currentCommand.parameterList.get(p++).b;

		f.setValue_S(b);
		getNextCommand();
	}
	//===============================================================================================
	private void setFlagTrue_FLAG()
	{//===============================================================================================
		int p=0;
		Flag f = (Flag) currentCommand.parameterList.get(p++).object;
		//boolean b = currentCommand.parameterList.get(p++).b;

		f.setValue_S(true);
		getNextCommand();
	}
	//===============================================================================================
	private void setFlagFalse_FLAG()
	{//===============================================================================================
		int p=0;
		Flag f = (Flag) currentCommand.parameterList.get(p++).object;
		//boolean b = currentCommand.parameterList.get(p++).b;

		f.setValue_S(false);
		getNextCommand();
	}







	//===============================================================================================
	private void giveSkillPoints_SKILL_INT()
	{//===============================================================================================
		int p=0;
		Skill f = (Skill) currentCommand.parameterList.get(p++).object;
		int i = currentCommand.parameterList.get(p++).i;

		float value = f.getValue_S();
		value+=i;
		f.setValue_S(value);

		getNextCommand();
	}

	//===============================================================================================
	private void removeSkillPoints_SKILL_INT()
	{//===============================================================================================
		int p=0;
		Skill f = (Skill) currentCommand.parameterList.get(p++).object;
		int i = currentCommand.parameterList.get(p++).i;

		float value = f.getValue_S();
		value-=i;
		f.setValue_S(value);

		getNextCommand();
	}

	//===============================================================================================
	private void setSkillPoints_SKILL_INT()
	{//===============================================================================================
		int p=0;
		Skill f = (Skill) currentCommand.parameterList.get(p++).object;
		int i = currentCommand.parameterList.get(p++).i;

		f.setValue_S(i);

		getNextCommand();
	}





	//=========================================================================================================================
	private void enterThisDoor()
	{//=========================================================================================================================
		if(door!=null)
		{
			door.enter();
		}
		getNextCommand();
	}
	//=========================================================================================================================
	private void enterThisWarp()
	{//=========================================================================================================================
		if(area!=null)
		{
			((WarpArea)area).enter();
		}
		getNextCommand();
	}


	//===============================================================================================
	private void enterDoor_DOOR()
	{//===============================================================================================
		int p=0;
		Door d = (Door) currentCommand.parameterList.get(p++).object;


		if(d!=null)
		{
			d.enter();

		}
		getNextCommand();

	}

	//===============================================================================================
	private void enterWarp_WARP()
	{//===============================================================================================
		int p=0;
		WarpArea a = (WarpArea) currentCommand.parameterList.get(p++).object;

		if(a!=null)
		{
			((WarpArea)a).enter();
		}
		getNextCommand();

	}

	//===============================================================================================
	private void changeMap_MAP_AREA()
	{//===============================================================================================
		int p=0;

		Map m = (Map) currentCommand.parameterList.get(p++).object;

		Object o = currentCommand.parameterList.get(p++).object;

		MapManager().changeMap(m,((Area)o));
		this.map = m;

		getNextCommand();
	}

	//===============================================================================================
	private void changeMap_MAP_DOOR()
	{//===============================================================================================
		int p=0;

		Map m = (Map) currentCommand.parameterList.get(p++).object;

		Object o = currentCommand.parameterList.get(p++).object;

		MapManager().changeMap(m,((Door)o));
		this.map = m;

		getNextCommand();
	}

	//===============================================================================================
	private void changeMap_MAP_WARP()
	{//===============================================================================================
		int p=0;

		Map m = (Map) currentCommand.parameterList.get(p++).object;

		Object o = currentCommand.parameterList.get(p++).object;

		MapManager().changeMap(m,((WarpArea)o));
		this.map = m;

		getNextCommand();
	}

	//===============================================================================================
	private void changeMap_MAP_INT_INT()
	{//===============================================================================================
		int p=0;

		Map m = (Map) currentCommand.parameterList.get(p++).object;

		int mapXTiles1X = currentCommand.parameterList.get(p++).i*2;
		int mapYTiles1X = currentCommand.parameterList.get(p++).i*2;

		MapManager().changeMap(m,mapXTiles1X,mapYTiles1X);
		this.map = m;

		getNextCommand();

	}

	//===============================================================================================
	private void doDialogue_DIALOGUE()
	{//===============================================================================================
		int p=0;

		if(currentCommand.parameterList.size()>0)
		{
			Dialogue d = (Dialogue) currentCommand.parameterList.get(p++).object;

			if(d.getInitialized_S()==false)
			{
				return; //wait for it to receive server data in its update() function
			}
			else
			{

				if(area!=null)area.tellServerTalkedToToday();
				if(door!=null)door.tellServerTalkedToToday();
				if(entity!=null)entity.tellServerTalkedToToday();

				TextManager().dialogue(d);
				getNextCommand();

			}

		}

	}


	//=========================================================================================================================
	private void doDialogueWithCaption_DIALOGUE()
	{//=========================================================================================================================

		int p=0;
		if(currentCommand.parameterList.size()>0)
		{
			Dialogue d = (Dialogue) currentCommand.parameterList.get(p++).object;

			if(d.getInitialized_S()==false)
			{
				//wait for it to receive server data in its update() function
			}
			else
			{
				if(area!=null)
				{
					if(ActionManager().area(area,d.caption()))
					{
						area.tellServerTalkedToToday();
						TextManager().dialogue(d);
						getNextCommand();
					}

				}
				if(door!=null)
				{
					if(ActionManager().entity(door,d.caption()))
					{
						door.tellServerTalkedToToday();
						TextManager().dialogue(d);
						getNextCommand();
					}
				}

				if(entity!=null)
				{
					if(ActionManager().entity(entity,d.caption()))
					{
						entity.tellServerTalkedToToday();
						TextManager().dialogue(d);
						getNextCommand();
					}
				}
			}

		}

	}


	//===============================================================================================
	private void doDialogueIfNew_DIALOGUE()
	{//===============================================================================================
		int p=0;
		Dialogue d = (Dialogue) currentCommand.parameterList.get(p++).object;

		if(d.getInitialized_S()==false)
		{
			//wait for it to receive server data in its update() function
		}
		else
		{
			//Boolean value = d.checkServerValueAndResetAfterSuccessfulReturn();
			boolean value = d.getDialogueDoneValue_S();

			//if(value!=null&&value.booleanValue()==false)
			if(value==false)
			{

				if(area!=null)area.tellServerTalkedToToday();
				if(door!=null)door.tellServerTalkedToToday();
				if(entity!=null)entity.tellServerTalkedToToday();

				TextManager().dialogue(d);
				getNextCommand();

			}
		}

	}




	//===============================================================================================
	private void setSpriteBox0_ENTITY()
	{//===============================================================================================
		int p=0;
		//handle 2x overloads
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;

		TextManager().textBox[0].setSpriteWindow(((Entity)e), null, null);

		getNextCommand();
	}




	//===============================================================================================
	private void setSpriteBox1_ENTITY()
	{//===============================================================================================
		int p=0;
		//handle 2x overloads
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;

		TextManager().textBox[1].setSpriteWindow(((Entity)e), null, null);

		getNextCommand();

	}


	//===============================================================================================
	private void setSpriteBox0_SPRITE()
	{//===============================================================================================
		int p=0;
		//handle 2x overloads
		Sprite s = (Sprite) currentCommand.parameterList.get(p++).object;
		if(s==null)return;//block until loaded.

		TextManager().textBox[0].setSpriteWindow(null, ((Sprite)s).texture, ((Sprite)s).displayName());

		getNextCommand();
	}




	//===============================================================================================
	private void setSpriteBox1_SPRITE()
	{//===============================================================================================
		int p=0;
		//handle 2x overloads
		Sprite s = (Sprite) currentCommand.parameterList.get(p++).object;
		if(s==null)return;//block until loaded.

		TextManager().textBox[1].setSpriteWindow(null, ((Sprite)s).texture, ((Sprite)s).displayName());

		getNextCommand();
	}


	//===============================================================================================
	private void blockUntilTextBoxClosed()
	{//===============================================================================================

		if(TextManager().isTextBoxOpen()==false)getNextCommand();
	}




	//===============================================================================================
	private void blockUntilTextAnswerBoxClosed()
	{//===============================================================================================

		if(TextManager().isTextAnswerBoxOpen()==false)getNextCommand();
	}




	//===============================================================================================
	private void doCinematicTextNoBorder_DIALOGUE_INTy()
	{//===============================================================================================


		//TODO

		//shouldnt really need INTy, just center in middle of screen, transparent text box background

		getNextCommand();
	}


	//===============================================================================================
	private void setDoorOpenAnimation_DOOR_BOOLopenClose()//(DOOR,BOOL)
	{//===============================================================================================
		int p=0;
		Door d = (Door) currentCommand.parameterList.get(p++).object;
		boolean b = currentCommand.parameterList.get(p++).b;

		d.setOpenManually(b);

		getNextCommand();
	}


	//===============================================================================================
	private void setDoorActionIcon_DOOR_BOOLonOff()//(DOOR,BOOL)
	{//===============================================================================================
		int p=0;
		Door d = (Door) currentCommand.parameterList.get(p++).object;
		boolean b = currentCommand.parameterList.get(p++).b;

		d.showActionIcon = b;

		getNextCommand();
	}
	//===============================================================================================
	private void setDoorDestination_DOOR_DOORdestination()//(DOOR,DOORdestination)
	{//===============================================================================================
		int p=0;
		Door d = (Door) currentCommand.parameterList.get(p++).object;
		Door d2 = (Door) currentCommand.parameterList.get(p++).object;

		d.setDestinationTYPEIDString(d2.getTYPEIDString());

		getNextCommand();
	}

	//===============================================================================================
	private void setAreaActionIcon_AREA_BOOLonOff()//(DOOR,BOOL)
	{//===============================================================================================
		int p=0;
		Area a = (Area) currentCommand.parameterList.get(p++).object;
		boolean b = currentCommand.parameterList.get(p++).b;

		a.showActionIcon = b;

		getNextCommand();
	}
	//===============================================================================================
	private void setWarpDestination_WARP_WARPdestination()//(WARP,WARPdestination)
	{//===============================================================================================
		int p=0;
		WarpArea d = (WarpArea) currentCommand.parameterList.get(p++).object;
		WarpArea d2 = (WarpArea) currentCommand.parameterList.get(p++).object;

		d.setDestinationTYPEIDString(d2.getTYPEIDString());


		getNextCommand();
	}


//	//===============================================================================================
//	private void playVideo_VIDEO()//(VIDEO)
//	{//===============================================================================================
//		// TODO
//
//		getNextCommand();
//	}



	//===============================================================================================
	private void setPlayerToTempPlayerWithSprite_SPRITE()
	{//===============================================================================================
		int p=0;
		Sprite s = (Sprite) currentCommand.parameterList.get(p++).object;

		if(s==null)return;//block until sprite has loaded.

		ClientGameEngine().setPlayerToTempPlayerWithSprite(s);
		getNextCommand();
	}

	//===============================================================================================
	private void setPlayerToNormalPlayer()
	{//===============================================================================================


		ClientGameEngine().setPlayerToNormalPlayer();
		getNextCommand();
	}

	//===============================================================================================
	private void setPlayerExists_BOOL()
	{//===============================================================================================
		int p=0;

		boolean b = currentCommand.parameterList.get(p++).b;

		ClientGameEngine().playerExistsInMap = b;
		getMap().activeEntityList.remove(Player());

		getNextCommand();
	}




	//===============================================================================================
	private void setPlayerControlsEnabled_BOOL()
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		ClientGameEngine().controlsEnabled = b;
		getNextCommand();
	}
	//===============================================================================================
	private void enablePlayerControls()
	{//===============================================================================================
		//int p=0;
		//boolean b = currentCommand.parameterList.get(p++).b;
		ClientGameEngine().controlsEnabled = true;
		getNextCommand();
	}
	//===============================================================================================
	private void disablePlayerControls()
	{//===============================================================================================
		//int p=0;
		//boolean b = currentCommand.parameterList.get(p++).b;
		ClientGameEngine().controlsEnabled = false;
		getNextCommand();
	}





	//===============================================================================================
	private void setPlayerAutoPilot_BOOL()
	{//===============================================================================================
		int p=0;

		boolean b = currentCommand.parameterList.get(p++).b;

		Player().setAutoPilot(b);
		getNextCommand();
	}

	//===============================================================================================
	private void setPlayerShowNameCaption_BOOL()
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;


		Player().setShowName(b);
		getNextCommand();
	}
	//===============================================================================================
	private void setPlayerShowAccountTypeCaption_BOOL()
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;


		Player().setShowAccountType(b);
		getNextCommand();
	}












	//===============================================================================================
	private void playerSetBehaviorQueueOnOff_BOOL()//(ENTITY)
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		boolean b = currentCommand.parameterList.get(p++).b;

		Player().behaviorEnabled=b;

		getNextCommand();
	}
	//===============================================================================================
	private void playerSetToArea_AREA()
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Area a = (Area) currentCommand.parameterList.get(p++).object;

		Player().setFeetAtMapXY((int)a.middleX(),(int)a.middleY());

		getNextCommand();
	}
	//===============================================================================================
	private void playerSetToDoor_DOOR()
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Door a = (Door) currentCommand.parameterList.get(p++).object;

		Player().setFeetAtMapXY((int)(a.arrivalXPixelsHQ()+8),(int)(a.arrivalYPixelsHQ()+8));

		getNextCommand();
	}
	//===============================================================================================
	private void playerSetToTileXY_INTxTile1X_INTyTile1X()
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		int tx = currentCommand.parameterList.get(p++).i;
		int ty = currentCommand.parameterList.get(p++).i;

		Player().setFeetAtMapXY((int)(tx*2*8+8),(int)(ty*2*8+8));

		getNextCommand();
	}
	//===============================================================================================
	private void playerWalkToArea_AREA()
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Area a = (Area) currentCommand.parameterList.get(p++).object;

		//TODO need behavior queue stuff working better.

		Player().currentAreaTYPEIDTarget = a.getTYPEIDString();

		getNextCommand();
	}

	//===============================================================================================
	private void playerWalkToDoor_DOOR()
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Door a = (Door) currentCommand.parameterList.get(p++).object;

		//TODO need behavior queue stuff working better.

		//TODO: use eventBehavior and eventCurrentTargetTYPEID list and all that.

		Player().currentAreaTYPEIDTarget = a.getTYPEIDString();

		getNextCommand();
	}

	//===============================================================================================
	private void playerWalkToEntity_ENTITY()
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Entity e2 = (Entity) currentCommand.parameterList.get(p++).object;

		//TODO need behavior queue stuff working better.

		Player().currentAreaTYPEIDTarget = e2.getTYPEIDString();

		getNextCommand();
	}

	//===============================================================================================
	private void playerWalkToTileXY_INTxTile1X_INTyTile1X()
	{//===============================================================================================
		//int p=0;

		//Entity a = (Entity) currentCommand.parameterList.get(p++).object;
		//int tx = currentCommand.parameterList.get(p++).i;
		//int ty = currentCommand.parameterList.get(p++).i;
		//TODO

		getNextCommand();
	}

	//===============================================================================================
	private void playerBlockUntilReachesArea_AREA()//TODO rename these
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Area a = (Area) currentCommand.parameterList.get(p++).object;
		if(Player().isAreaBoundaryTouchingMyHitBox(a))getNextCommand();
	}

	//===============================================================================================
	private void playerBlockUntilReachesEntity_ENTITY()
	{//===============================================================================================
		int p=0;
		//Entity a = (Entity) currentCommand.parameterList.get(p++).object;
		Entity b = (Entity) currentCommand.parameterList.get(p++).object;

		if(Player().isEntityHitBoxTouchingMyHitBox(b))getNextCommand();
	}

	//===============================================================================================
	private void playerBlockUntilReachesDoor_DOOR()
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Door d = (Door) currentCommand.parameterList.get(p++).object;

		if(Player().isEntityHitBoxTouchingMyHitBox(d))getNextCommand();
	}

	//===============================================================================================
	private void playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X()
	{//===============================================================================================
		int p=0;
		//Entity a = (Entity) currentCommand.parameterList.get(p++).object;
		int tx = currentCommand.parameterList.get(p++).i;
		int ty = currentCommand.parameterList.get(p++).i;

		if(Player().isXYTouchingMyHitBox(tx*8*2,ty*8*2))getNextCommand();
	}

	//===============================================================================================
	private void playerWalkToAreaAndBlockUntilThere_AREA()
	{//===============================================================================================
		int p=0;
		Area a = (Area) currentCommand.parameterList.get(p++).object; //TODO need to rework behavior, eventBehavior, currentTargetTYPEID, thereYet, walking functions, etc.

		//walk to area, use pathfinding always
		int there=Player().walkToXYWithPathFinding(a.middleX(),a.middleY());
		if(there==-1)
		{
			if(Player().walkToXYNoCheckHit(a.middleX(),a.middleY()))
			there=1;
		}

		//block until touch area
		if(Player().isAreaBoundaryTouchingMyHitBox(a))
		{
			//wait 500 ticks to walk to center of area
			ticksCounter+=Engine().realWorldTicksPassed();

			if(ticksCounter>=500)
			{
				//continue
				ticksCounter=0;
				getNextCommand();
			}
		}

	}

	//===============================================================================================
	private void playerWalkToEntityAndBlockUntilThere_ENTITY()
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Entity a = (Entity) currentCommand.parameterList.get(p++).object;

		//walk to area, use pathfinding always
		int there=Player().walkToXYWithPathFinding(a.middleX(),a.middleY());
		if(there==-1)
		{
			if(Player().walkToXYNoCheckHit(a.middleX(),a.middleY()))
			there=1;
		}

		//block until touch area
		if(Player().isEntityHitBoxTouchingMyHitBox(a))
		{
			//wait 500 ticks to walk to center of area
			ticksCounter+=Engine().realWorldTicksPassed();

			if(ticksCounter>=500)
			{
				//continue
				ticksCounter=0;
				getNextCommand();
			}
		}
	}

	//===============================================================================================
	private void playerWalkToDoorAndBlockUntilThere_DOOR()
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Door a = (Door) currentCommand.parameterList.get(p++).object;

		//walk to area, use pathfinding always
		int there=Player().walkToXYWithPathFinding(a.middleX(),a.middleY());
		if(there==-1)
		{
			if(Player().walkToXYNoCheckHit(a.middleX(),a.middleY()))
			there=1;
		}

		//block until touch area
		if(Player().isEntityHitBoxTouchingMyHitBox(a))
		{
			//wait 500 ticks to walk to center of area
			ticksCounter+=Engine().realWorldTicksPassed();

			if(ticksCounter>=500)
			{
				//continue
				ticksCounter=0;
				getNextCommand();
			}
		}
	}

	//===============================================================================================
	private void playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X()
	{//===============================================================================================
		int p=0;
		//Entity a = (Entity) currentCommand.parameterList.get(p++).object;
		int tx = currentCommand.parameterList.get(p++).i;
		int ty = currentCommand.parameterList.get(p++).i;

		//TODO can use -1 to just walk in direction, etc

		int x = tx*8*2;
		int y = ty*8*2;


		//walk to area, use pathfinding always
		int there=Player().walkToXYWithPathFinding(x,y);
		if(there==-1)
		{
			if(Player().walkToXYNoCheckHit(x,y))
			there=1;
		}

		//block until touch area
		if(Player().isXYTouchingMyHitBox(x,y))
		{
			//wait 500 ticks to walk to center of area
			ticksCounter+=Engine().realWorldTicksPassed();

			if(ticksCounter>=500)
			{
				//continue
				ticksCounter=0;
				getNextCommand();
			}
		}
	}

	//===============================================================================================
	private void playerStandAndShuffle()//(ENTITY)
	{//===============================================================================================
		//int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;

		Player().addEventBehavior("StandAndShuffle");//TODO

		getNextCommand();
	}



	//===============================================================================================
	private void playerStandAndShuffleAndFaceEntity_ENTITY()//(ENTITY)
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Entity e2 = (Entity) currentCommand.parameterList.get(p++).object;

		Player().addEventBehavior("StandAndShuffleAndFace:ENTITY."+e2.id());//TODO:

		getNextCommand();
	}


	//===============================================================================================
	private void playerSetFaceMovementDirection_STRINGdirection()//(ENTITY,INT)
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		//int dir = currentCommand.parameterList.get(p++).i;
		//((Character)e).setAnimationByDirection(dir);
		//getNextCommand();


		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		GameString gs = (GameString)currentCommand.parameterList.get(p++).object;
		//if(gs.getInitialized_S()==false)return;

		String dirString = gs.text();


		int dir = -1;
		if(dirString.toUpperCase().equals("UP"))dir=Entity.UP;
		if(dirString.toUpperCase().equals("DOWN"))dir=Entity.DOWN;
		if(dirString.toUpperCase().equals("LEFT"))dir=Entity.LEFT;
		if(dirString.toUpperCase().equals("RIGHT"))dir=Entity.RIGHT;
		if(dirString.toUpperCase().equals("UPRIGHT"))dir=Entity.UPRIGHT;
		if(dirString.toUpperCase().equals("DOWNRIGHT"))dir=Entity.DOWNRIGHT;
		if(dirString.toUpperCase().equals("UPLEFT"))dir=Entity.UPLEFT;
		if(dirString.toUpperCase().equals("DOWNLEFT"))dir=Entity.DOWNLEFT;

		if(dir!=-1)
		{
			Player().movementDirection = dir;//TODO this should be all i need for this to work but it doesn't

			Player().setCurrentAnimationByDirection(dir);
			Player().setFrameOffsetInCurrentAnimation(0);
			//Player().doCharacterAnimation();
		}


		getNextCommand();


	}
	//===============================================================================================
	private void playerSetMovementSpeed_INTticksPerPixel()//(ENTITY,INT)
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		int speed = currentCommand.parameterList.get(p++).i;

		Player().setTicksPerPixelMoved(speed);

		getNextCommand();
	}


	//===============================================================================================
	private void playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks()//(INTticksPerFrame)
	{//===============================================================================================
		int p=0;

		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		GameString gs = (GameString) currentCommand.parameterList.get(p++).object;


		int ticksBetweenFrames = currentCommand.parameterList.get(p++).i;
		boolean randomUpToTicksBetweenFrames = currentCommand.parameterList.get(p++).b;



		if(Player()!=null&&Player().sprite!=null&&gs!=null)
		{

			//if(gs.getInitialized_S()==false)return; //wait for object to receive server data in its update() function
			//if(Player().sprite.getInitialized_S()==false)return;

			Player().setCurrentAnimationByName(gs.text());

			Player().setAnimateOnceThroughCurrentAnimation();

			Player().setRandomFrames(false);

			Player().setTicksBetweenFrames(ticksBetweenFrames);
			Player().setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);


			getNextCommand();

		}

	}

	//===============================================================================================
	private void playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks()//(INTticksPerFrame)
	{//===============================================================================================
		int p = 0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		GameString gs = (GameString) currentCommand.parameterList.get(p++).object;
		int ticksBetweenFrames = currentCommand.parameterList.get(p++).i;
		boolean randomUpToTicksBetweenFrames = currentCommand.parameterList.get(p++).b;
		int ticksBetweenLoop = currentCommand.parameterList.get(p++).i;
		boolean randomUpToTicksBetweenLoop = currentCommand.parameterList.get(p++).b;

		if (Player() != null && Player().sprite != null && gs != null) {
			//if(gs.getInitialized_S()==false) return; //wait for object to receive server data in its update() function
			//if(Player().sprite.getInitialized_S()==false) return;

			Player().setCurrentAnimationByName(gs.text());

			Player().setAnimateLoopThroughCurrentAnimation();

			Player().setRandomFrames(false);

			Player().setTicksBetweenFrames(ticksBetweenFrames);
			Player().setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);

			Player().setTicksBetweenAnimationLoop(ticksBetweenLoop);
			Player().setRandomUpToTicksBetweenAnimationLoop(randomUpToTicksBetweenLoop);

			getNextCommand();
		}
	}



	//===============================================================================================
	private void playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame()//(INTticksPerFrame)
	{//===============================================================================================
		int p=0;

		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		GameString gs = (GameString) currentCommand.parameterList.get(p++).object;
		int ticksBetweenFrames = currentCommand.parameterList.get(p++).i;


		if(Player()!=null&&Player().sprite!=null&&gs!=null)
		{

			//if(gs.getInitialized_S()==false)return; //wait for object to receive server data in its update() function
			//if(Player().sprite.getInitialized_S()==false)return;

			Player().setCurrentAnimationByName(gs.text());

			Player().setAnimateOnceThroughCurrentAnimation();

			Player().setRandomFrames(false);
			Player().setTicksBetweenFrames(ticksBetweenFrames);

			getNextCommand();

		}

	}

	//===============================================================================================
	private void playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame()//(INTticksPerFrame)
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		GameString gs = (GameString) currentCommand.parameterList.get(p++).object;
		int ticksBetweenFrames = currentCommand.parameterList.get(p++).i;

		if(Player()!=null&&Player().sprite!=null&&gs!=null)
		{

			//if(gs.getInitialized_S()==false)return; //wait for object to receive server data in its update() function
			//if(Player().sprite.getInitialized_S()==false)return;

			Player().setCurrentAnimationByName(gs.text());

			Player().setAnimateLoopThroughCurrentAnimation();

			Player().setRandomFrames(false);
			Player().setTicksBetweenFrames(ticksBetweenFrames);
			Player().setTicksBetweenAnimationLoop(ticksBetweenFrames);

			getNextCommand();

		}
	}


	//===============================================================================================
	private void playerStopAnimating()
	{//===============================================================================================
		//int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Player().stopAnimation();

		getNextCommand();
	}




	//===============================================================================================
	private void playerSetGlobalAnimationDisabled_BOOL()
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		boolean b = currentCommand.parameterList.get(p++).b;

		Player().setAnimationDisabled(b);

		getNextCommand();
	}


	//===============================================================================================
	private void playerSetToAlpha_FLOAT()
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		float f = currentCommand.parameterList.get(p++).f;

		Player().setToAlpha(f);

		getNextCommand();
	}













	//===============================================================================================
	private void entitySetBehaviorQueueOnOff_ENTITY_BOOL()//(ENTITY)
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		boolean b = currentCommand.parameterList.get(p++).b;

		e.behaviorEnabled=b;

		getNextCommand();
	}
	//===============================================================================================
	private void entitySetToArea_ENTITY_AREA()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Area a = (Area) currentCommand.parameterList.get(p++).object;

		e.setFeetAtMapXY((int)a.middleX(),(int)a.middleY());

		getNextCommand();
	}
	//===============================================================================================
	private void entitySetToDoor_ENTITY_DOOR()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Door a = (Door) currentCommand.parameterList.get(p++).object;

		e.setFeetAtMapXY((int)(a.arrivalXPixelsHQ()+8),(int)(a.arrivalYPixelsHQ()+8));

		getNextCommand();
	}
	//===============================================================================================
	private void entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		int tx = currentCommand.parameterList.get(p++).i;
		int ty = currentCommand.parameterList.get(p++).i;

		e.setFeetAtMapXY((int)(tx*2*8+8),(int)(ty*2*8+8));

		getNextCommand();
	}
	//===============================================================================================
	private void entityWalkToArea_ENTITY_AREA()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Area a = (Area) currentCommand.parameterList.get(p++).object;

		//TODO need behavior queue stuff working better.

		e.currentAreaTYPEIDTarget = a.getTYPEIDString();

		getNextCommand();
	}

	//===============================================================================================
	private void entityWalkToDoor_ENTITY_DOOR()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Door a = (Door) currentCommand.parameterList.get(p++).object;

		//TODO need behavior queue stuff working better.

		//TODO: use eventBehavior and eventCurrentTargetTYPEID list and all that.

		e.currentAreaTYPEIDTarget = a.getTYPEIDString();

		getNextCommand();
	}

	//===============================================================================================
	private void entityWalkToEntity_ENTITY_ENTITY()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Entity e2 = (Entity) currentCommand.parameterList.get(p++).object;

		//TODO need behavior queue stuff working better.

		e.currentAreaTYPEIDTarget = e2.getTYPEIDString();

		getNextCommand();
	}
	//===============================================================================================
	private void entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X()
	{//===============================================================================================
		//int p=0;

		//Entity a = (Entity) currentCommand.parameterList.get(p++).object;
		//int tx = currentCommand.parameterList.get(p++).i;
		//int ty = currentCommand.parameterList.get(p++).i;
		//TODO

		getNextCommand();
	}
	//===============================================================================================
	private void entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal()//(ENTITY,AREA,BOOLwalk,BOOLhit,BOOLpath,BOOLanim,BOOLdiag)
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Area a = (Area) currentCommand.parameterList.get(p++).object;
		boolean bWalkOrSlide = currentCommand.parameterList.get(p++).b;
		boolean bCheckHit = currentCommand.parameterList.get(p++).b;
		boolean bAvoidOthers = currentCommand.parameterList.get(p++).b;
		boolean bPushOthers = currentCommand.parameterList.get(p++).b;
		boolean bPathFind = currentCommand.parameterList.get(p++).b;
		boolean bAnimate = currentCommand.parameterList.get(p++).b;
		boolean bMoveDiagonally = currentCommand.parameterList.get(p++).b;

		e.addEventBehavior("MoveToArea:"+a.id()+","+bWalkOrSlide+","+bCheckHit+","+bAvoidOthers+","+bPushOthers+","+bPathFind+","+bAnimate+","+bMoveDiagonally);

		getNextCommand();
	}

	//===============================================================================================
	private void entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal()//(ENTITY,ENTITY,BOOLwalk,BOOLhit,BOOLpath,BOOLanim,BOOLdiag)
	{//===============================================================================================
		int p=0;

		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Door e2 = (Door) currentCommand.parameterList.get(p++).object;
		boolean bWalkOrSlide = currentCommand.parameterList.get(p++).b;
		boolean bCheckHit = currentCommand.parameterList.get(p++).b;
		boolean bAvoidOthers = currentCommand.parameterList.get(p++).b;
		boolean bPushOthers = currentCommand.parameterList.get(p++).b;
		boolean bPathFind = currentCommand.parameterList.get(p++).b;
		boolean bAnimate = currentCommand.parameterList.get(p++).b;
		boolean bMoveDiagonally = currentCommand.parameterList.get(p++).b;

		e.addEventBehavior("MoveToDoor:"+e2.id()+","+bWalkOrSlide+","+bCheckHit+","+bAvoidOthers+","+bPushOthers+","+bPathFind+","+bAnimate+","+bMoveDiagonally);

		getNextCommand();
	}

	//===============================================================================================
	private void entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal()//(ENTITY,ENTITY,BOOLwalk,BOOLhit,BOOLpath,BOOLanim,BOOLdiag)
	{//===============================================================================================
		int p=0;

		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Entity e2 = (Entity) currentCommand.parameterList.get(p++).object;
		boolean bWalkOrSlide = currentCommand.parameterList.get(p++).b;
		boolean bCheckHit = currentCommand.parameterList.get(p++).b;
		boolean bAvoidOthers = currentCommand.parameterList.get(p++).b;
		boolean bPushOthers = currentCommand.parameterList.get(p++).b;
		boolean bPathFind = currentCommand.parameterList.get(p++).b;
		boolean bAnimate = currentCommand.parameterList.get(p++).b;
		boolean bMoveDiagonally = currentCommand.parameterList.get(p++).b;

		e.addEventBehavior("MoveToEntity:"+e2.id()+","+bWalkOrSlide+","+bCheckHit+","+bAvoidOthers+","+bPushOthers+","+bPathFind+","+bAnimate+","+bMoveDiagonally);

		getNextCommand();
	}
	//===============================================================================================
	private void entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal()//(ENTITY,ENTITY,BOOLwalk,BOOLhit,BOOLpath,BOOLanim,BOOLdiag)
	{//===============================================================================================
		int p=0;

		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		int tX = currentCommand.parameterList.get(p++).i;
		int tY = currentCommand.parameterList.get(p++).i;
		boolean bWalkOrSlide = currentCommand.parameterList.get(p++).b;
		boolean bCheckHit = currentCommand.parameterList.get(p++).b;
		boolean bAvoidOthers = currentCommand.parameterList.get(p++).b;
		boolean bPushOthers = currentCommand.parameterList.get(p++).b;
		boolean bPathFind = currentCommand.parameterList.get(p++).b;
		boolean bAnimate = currentCommand.parameterList.get(p++).b;
		boolean bMoveDiagonally = currentCommand.parameterList.get(p++).b;

		e.addEventBehavior("MoveToMapXY:"+tX*8*2+","+tY*8*2+","+bWalkOrSlide+","+bCheckHit+","+bAvoidOthers+","+bPushOthers+","+bPathFind+","+bAnimate+","+bMoveDiagonally);

		getNextCommand();
	}

	//===============================================================================================
	private void entityBlockUntilReachesArea_ENTITY_AREA()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Area a = (Area) currentCommand.parameterList.get(p++).object;
		if(e.isAreaBoundaryTouchingMyHitBox(a))getNextCommand();
	}

	//===============================================================================================
	private void entityBlockUntilReachesEntity_ENTITY_ENTITY()
	{//===============================================================================================
		int p=0;
		Entity a = (Entity) currentCommand.parameterList.get(p++).object;
		Entity b = (Entity) currentCommand.parameterList.get(p++).object;

		if(a.isEntityHitBoxTouchingMyHitBox(b))getNextCommand();
	}

	//===============================================================================================
	private void entityBlockUntilReachesDoor_ENTITY_DOOR()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Door d = (Door) currentCommand.parameterList.get(p++).object;

		if(e.isEntityHitBoxTouchingMyHitBox(d))getNextCommand();
	}

	//===============================================================================================
	private void entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X()
	{//===============================================================================================
		int p=0;
		Entity a = (Entity) currentCommand.parameterList.get(p++).object;
		int tx = currentCommand.parameterList.get(p++).i;
		int ty = currentCommand.parameterList.get(p++).i;

		if(a.isXYTouchingMyHitBox(tx*8*2,ty*8*2))getNextCommand();
	}


	//===============================================================================================
	private void entityWalkToAreaAndBlockUntilThere_ENTITY_AREA()
	{//===============================================================================================
		int p=0;
		Character e = (Character) currentCommand.parameterList.get(p++).object;
		Area a = (Area) currentCommand.parameterList.get(p++).object; //TODO need to rework behavior, eventBehavior, currentTargetTYPEID, thereYet, walking functions, etc.

		//walk to area, use pathfinding always
		int there=e.walkToXYWithPathFinding(a.middleX(),a.middleY());
		if(there==-1)
		{
			if(e.walkToXYNoCheckHit(a.middleX(),a.middleY()))
			there=1;
		}

		//block until touch area
		if(e.isAreaBoundaryTouchingMyHitBox(a))
		{
			//wait 500 ticks to walk to center of area
			ticksCounter+=Engine().realWorldTicksPassed();

			if(ticksCounter>=500)
			{
				//continue
				ticksCounter=0;
				getNextCommand();
			}
		}

	}

	//===============================================================================================
	private void entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY()
	{//===============================================================================================
		int p=0;
		Character e = (Character) currentCommand.parameterList.get(p++).object;
		Entity a = (Entity) currentCommand.parameterList.get(p++).object;

		//walk to area, use pathfinding always
		int there=e.walkToXYWithPathFinding(a.middleX(),a.middleY());
		if(there==-1)
		{
			if(e.walkToXYNoCheckHit(a.middleX(),a.middleY()))
			there=1;
		}

		//block until touch area
		if(e.isEntityHitBoxTouchingMyHitBox(a))
		{
			//wait 500 ticks to walk to center of area
			ticksCounter+=Engine().realWorldTicksPassed();

			if(ticksCounter>=500)
			{
				//continue
				ticksCounter=0;
				getNextCommand();
			}
		}
	}

	//===============================================================================================
	private void entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR()
	{//===============================================================================================
		int p=0;
		Character e = (Character) currentCommand.parameterList.get(p++).object;
		Door a = (Door) currentCommand.parameterList.get(p++).object;

		//walk to area, use pathfinding always
		int there=e.walkToXYWithPathFinding(a.middleX(),a.middleY());
		if(there==-1)
		{
			if(e.walkToXYNoCheckHit(a.middleX(),a.middleY()))
			there=1;
		}

		//block until touch area
		if(e.isEntityHitBoxTouchingMyHitBox(a))
		{
			//wait 500 ticks to walk to center of area
			ticksCounter+=Engine().realWorldTicksPassed();

			if(ticksCounter>=500)
			{
				//continue
				ticksCounter=0;
				getNextCommand();
			}
		}
	}

	//===============================================================================================
	private void entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X()
	{//===============================================================================================
		int p=0;
		Character e = (Character) currentCommand.parameterList.get(p++).object;
		int tx = currentCommand.parameterList.get(p++).i;
		int ty = currentCommand.parameterList.get(p++).i;

		//TODO can use -1 to just walk in direction, etc

		int x = tx*8*2;
		int y = ty*8*2;


		//walk to area, use pathfinding always
		int there=e.walkToXYWithPathFinding(x,y);
		if(there==-1)
		{
			if(e.walkToXYNoCheckHit(x,y))
			there=1;
		}

		//block until touch area
		if(e.isXYTouchingMyHitBox(x,y))
		{
			//wait 500 ticks to walk to center of area
			ticksCounter+=Engine().realWorldTicksPassed();

			if(ticksCounter>=500)
			{
				//continue
				ticksCounter=0;
				getNextCommand();
			}
		}
	}

	//===============================================================================================
	private void entityStandAndShuffle_ENTITY()//(ENTITY)
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;

		e.addEventBehavior("StandAndShuffle");//TODO

		getNextCommand();
	}

	//===============================================================================================
	private void entityStandAndShuffleAndFacePlayer_ENTITY()//(ENTITY)
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;


		e.addEventBehavior("StandAndShuffleAndFacePlayer");//TODO:

		getNextCommand();
	}

	//===============================================================================================
	private void entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY()//(ENTITY)
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		Entity e2 = (Entity) currentCommand.parameterList.get(p++).object;

		e.addEventBehavior("StandAndShuffleAndFace:ENTITY."+e2.id());//TODO:

		getNextCommand();
	}


	//===============================================================================================
	private void entitySetFaceMovementDirection_ENTITY_STRINGdirection()//(ENTITY,INT)
	{//===============================================================================================
		int p=0;
		//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		//int dir = currentCommand.parameterList.get(p++).i;
		//((Character)e).setAnimationByDirection(dir);
		//getNextCommand();


		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		GameString gs = (GameString)currentCommand.parameterList.get(p++).object;
		//if(gs.getInitialized_S()==false)return;

		String dirString = gs.text();

		int dir = -1;
		if(dirString.toUpperCase().equals("UP"))dir=Entity.UP;
		if(dirString.toUpperCase().equals("DOWN"))dir=Entity.DOWN;
		if(dirString.toUpperCase().equals("LEFT"))dir=Entity.LEFT;
		if(dirString.toUpperCase().equals("RIGHT"))dir=Entity.RIGHT;
		if(dirString.toUpperCase().equals("UPRIGHT"))dir=Entity.UPRIGHT;
		if(dirString.toUpperCase().equals("DOWNRIGHT"))dir=Entity.DOWNRIGHT;
		if(dirString.toUpperCase().equals("UPLEFT"))dir=Entity.UPLEFT;
		if(dirString.toUpperCase().equals("DOWNLEFT"))dir=Entity.DOWNLEFT;

		if(dir!=-1)e.movementDirection = dir;

		getNextCommand();


	}
	//===============================================================================================
	private void entitySetMovementSpeed_ENTITY_INTticksPerPixel()//(ENTITY,INT)
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		int speed = currentCommand.parameterList.get(p++).i;

		e.setTicksPerPixelMoved(speed);

		getNextCommand();
	}

	//===============================================================================================
	private void entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks()//(INTticksPerFrame)
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		int ticksPerFrame = currentCommand.parameterList.get(p++).i;
		boolean randomUpToTicksBetweenFrames = currentCommand.parameterList.get(p++).b;

		e.setAnimateLoopThroughAllFrames();
		e.setRandomFrames(true);
		e.setTicksBetweenFrames(ticksPerFrame);
		e.setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);

		//dont set ticks between loop here because there is no lop

		getNextCommand();
	}

	//===============================================================================================
	private void entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		int ticks = currentCommand.parameterList.get(p++).i;
		boolean randomUpToTicksBetweenFrames = currentCommand.parameterList.get(p++).b;


		e.setAnimateOnceThroughCurrentAnimation();

		e.setRandomFrames(false);
		e.setTicksBetweenFrames(ticks);
		e.setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);


		getNextCommand();


	}

	//===============================================================================================
	private void entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks()//(INTticksPerFrame)
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		int ticksBetweenFrames = currentCommand.parameterList.get(p++).i;
		boolean randomUpToTicksBetweenFrames = currentCommand.parameterList.get(p++).b;
		int ticksBetweenLoop = currentCommand.parameterList.get(p++).i;
		boolean randomUpToTicksBetweenLoop = currentCommand.parameterList.get(p++).b;


		e.setAnimateLoopThroughCurrentAnimation();

		e.setRandomFrames(false);
		e.setTicksBetweenFrames(ticksBetweenFrames);
		e.setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);

		e.setTicksBetweenAnimationLoop(ticksBetweenLoop);
		e.setRandomUpToTicksBetweenAnimationLoop(randomUpToTicksBetweenLoop);

		getNextCommand();


	}

	//===============================================================================================
	private void entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks()//(INTticksPerFrame)
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		int ticksBetweenFrames = currentCommand.parameterList.get(p++).i;
		boolean randomUpToTicksBetweenFrames = currentCommand.parameterList.get(p++).b;


		e.setAnimateOnceThroughAllFrames();

		e.setRandomFrames(false);

		e.setTicksBetweenFrames(ticksBetweenFrames);
		e.setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);


		getNextCommand();


	}


	//===============================================================================================
	private void entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks()//(INTticksPerFrame)
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		int ticksBetweenFrames = currentCommand.parameterList.get(p++).i;
		boolean randomUpToTicksBetweenFrames = currentCommand.parameterList.get(p++).b;
		int ticksBetweenLoop = currentCommand.parameterList.get(p++).i;
		boolean randomUpToTicksBetweenLoop = currentCommand.parameterList.get(p++).b;


		e.setAnimateLoopThroughAllFrames();

		e.setRandomFrames(false);

		e.setTicksBetweenFrames(ticksBetweenFrames);
		e.setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);

		e.setTicksBetweenAnimationLoop(ticksBetweenLoop);
		e.setRandomUpToTicksBetweenAnimationLoop(randomUpToTicksBetweenLoop);

		getNextCommand();

	}

	//===============================================================================================
	private void entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName()//(INTticksPerFrame)
	{//===============================================================================================
		int p=0;

		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		GameString gs = (GameString) currentCommand.parameterList.get(p++).object;


		if(e!=null&&e.sprite!=null&&gs!=null)
		{

			//if(gs.getInitialized_S()==false)return; //wait for object to receive server data in its update() function
			//if(e.sprite.getInitialized_S()==false)return;

			e.setCurrentAnimationByName(gs.text());

			e.setFrameToCurrentAnimationStart();

			getNextCommand();

		}
	}

	//===============================================================================================
	private void entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame()//(INTticksPerFrame)
	{//===============================================================================================
		int p=0;

		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		GameString gs = (GameString) currentCommand.parameterList.get(p++).object;
		int ticksBetweenFrames = currentCommand.parameterList.get(p++).i;


		if(e!=null&&e.sprite!=null&&gs!=null)
		{

			//if(gs.getInitialized_S()==false)return; //wait for object to receive server data in its update() function
			//if(e.sprite.getInitialized_S()==false)return;

			e.setCurrentAnimationByName(gs.text());

			e.setAnimateOnceThroughCurrentAnimation();

			e.setRandomFrames(false);
			e.setTicksBetweenFrames(ticksBetweenFrames);

			getNextCommand();

		}

	}

	//===============================================================================================
	private void entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame()//(INTticksPerFrame)
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		GameString gs = (GameString) currentCommand.parameterList.get(p++).object;
		int ticksBetweenFrames = currentCommand.parameterList.get(p++).i;

		if(e!=null&&e.sprite!=null&&gs!=null)
		{

			//if(gs.getInitialized_S()==false)return; //wait for object to receive server data in its update() function
			//if(e.sprite.getInitialized_S()==false)return;

			e.setCurrentAnimationByName(gs.text());

			e.setAnimateLoopThroughCurrentAnimation();

			e.setRandomFrames(false);
			e.setTicksBetweenFrames(ticksBetweenFrames);
			e.setTicksBetweenAnimationLoop(ticksBetweenFrames);

			getNextCommand();

		}
	}
	//===============================================================================================
	private void entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks()//(INTticksPerFrame)
	{//===============================================================================================
		int p=0;

		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		GameString gs = (GameString) currentCommand.parameterList.get(p++).object;


		int ticksBetweenFrames = currentCommand.parameterList.get(p++).i;
		boolean randomUpToTicksBetweenFrames = currentCommand.parameterList.get(p++).b;



		if(e!=null&&e.sprite!=null&&gs!=null)
		{

			//if(gs.getInitialized_S()==false)return; //wait for object to receive server data in its update() function
			//if(e.sprite.getInitialized_S()==false)return;

			e.setCurrentAnimationByName(gs.text());

			e.setAnimateOnceThroughCurrentAnimation();

			e.setRandomFrames(false);

			e.setTicksBetweenFrames(ticksBetweenFrames);
			e.setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);


			getNextCommand();

		}

	}

	//===============================================================================================
	private void entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks()//(INTticksPerFrame)
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		GameString gs = (GameString) currentCommand.parameterList.get(p++).object;
		int ticksBetweenFrames = currentCommand.parameterList.get(p++).i;
		boolean randomUpToTicksBetweenFrames = currentCommand.parameterList.get(p++).b;
		int ticksBetweenLoop = currentCommand.parameterList.get(p++).i;
		boolean randomUpToTicksBetweenLoop = currentCommand.parameterList.get(p++).b;


		if(e!=null&&e.sprite!=null&&gs!=null)
		{

			//if(gs.getInitialized_S()==false)return; //wait for object to receive server data in its update() function
			//if(e.sprite.getInitialized_S()==false)return;

			e.setCurrentAnimationByName(gs.text());

			e.setAnimateLoopThroughCurrentAnimation();

			e.setRandomFrames(false);

			e.setTicksBetweenFrames(ticksBetweenFrames);
			e.setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);

			e.setTicksBetweenAnimationLoop(ticksBetweenLoop);
			e.setRandomUpToTicksBetweenAnimationLoop(randomUpToTicksBetweenLoop);

			getNextCommand();

		}
	}


	//===============================================================================================
	private void entityStopAnimating_ENTITY()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		e.stopAnimation();

		getNextCommand();
	}




	//===============================================================================================
	private void entitySetGlobalAnimationDisabled_ENTITY_BOOL()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		boolean b = currentCommand.parameterList.get(p++).b;

		e.setAnimationDisabled(b);

		getNextCommand();
	}



	//===============================================================================================
	private void entitySetNonWalkable_ENTITY_BOOL()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		boolean b = currentCommand.parameterList.get(p++).b;

		e.setNonWalkable(b);

		getNextCommand();
	}



	//===============================================================================================
	private void entitySetPushable_ENTITY_BOOL()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		boolean b = currentCommand.parameterList.get(p++).b;

		e.setPushable(b);

		getNextCommand();
	}


	//===============================================================================================
	private void entityFadeOutDelete_ENTITY()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;

		e.fadeOutAndDelete();

		getNextCommand();
	}

	//===============================================================================================
	private void entityDeleteInstantly_ENTITY()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;

		e.delete();

		getNextCommand();
	}

	//===============================================================================================
	private void entitySetToAlpha_ENTITY_FLOAT()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		float f = currentCommand.parameterList.get(p++).f;

		e.setToAlpha(f);

		getNextCommand();
	}








	//===============================================================================================
	private void spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA()//(SPRITE,STRINGentityIdent,AREA)
	{//===============================================================================================
		int p=0;
		Sprite sprite = (Sprite) currentCommand.parameterList.get(p++).object;
		GameString gameString = (GameString) currentCommand.parameterList.get(p++).object;
		Area a = (Area) currentCommand.parameterList.get(p++).object;

		// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
		if(sprite==null)return;//block until sprite has loaded.

		if(gameString.getInitialized_S()==false)
		{
			//wait for object to receive server data in its update() function
		}
		else
		{
			Entity m = getMap().createEntityAtArea(getMap(),gameString.text(),sprite,a);

			m.setAlphaImmediately(1.0f);

			getNextCommand();

		}

	}

	//===============================================================================================
	private void spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA()//(SPRITE,STRINGentityIdent,AREA)
	{//===============================================================================================
		int p=0;
		Sprite sprite = (Sprite) currentCommand.parameterList.get(p++).object;
		GameString gameString = (GameString) currentCommand.parameterList.get(p++).object;
		Area a = (Area) currentCommand.parameterList.get(p++).object;

		// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
		if(sprite==null)return;//block until sprite has loaded.

		if(gameString.getInitialized_S()==false)
		{
			//wait for object to receive server data in its update() function
		}
		else
		{
			getMap().createEntityAtArea(getMap(),gameString.text(),sprite,a);


			getNextCommand();

		}

	}

	//===============================================================================================
	private void spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA()//(SPRITE,STRINGentityIdent,AREA)
	{//===============================================================================================
		int p=0;
		Sprite sprite = (Sprite) currentCommand.parameterList.get(p++).object;
		GameString gameString = (GameString) currentCommand.parameterList.get(p++).object;
		Area a = (Area) currentCommand.parameterList.get(p++).object;

		// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
		if(sprite==null)return;//block until sprite has loaded.

		if(gameString.getInitialized_S()==false)
		{
			//wait for object to receive server data in its update() function
		}
		else
		{
			Character character = new Character(Engine(),gameString.text(),sprite,a,map);

			character.setAlphaImmediately(1.0f);

			getNextCommand();

		}

	}

	//===============================================================================================
	private void spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA()//(SPRITE,STRINGentityIdent,AREA)
	{//===============================================================================================
		int p=0;
		Sprite sprite = (Sprite) currentCommand.parameterList.get(p++).object;
		GameString gameString = (GameString) currentCommand.parameterList.get(p++).object;
		Area a = (Area) currentCommand.parameterList.get(p++).object;


		// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
		if(sprite==null)return;//block until sprite has loaded.

		if(gameString.getInitialized_S()==false)
		{
			//wait for object to receive server data in its update() function
		}
		else
		{
			new Character(Engine(),gameString.text(),sprite,a, map);

			getNextCommand();
		}

	}

	//===============================================================================================
	private void createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy()//(SPRITE,FLOATx,FLOATy)
	{//===============================================================================================
		int p=0;

		Sprite s = (Sprite) currentCommand.parameterList.get(p++).object;
		float screenX = currentCommand.parameterList.get(p++).f;
		float screenY = currentCommand.parameterList.get(p++).f;


		// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
		if(s==null)return;//block until sprite has loaded.

		ScreenSprite screenSprite = new ScreenSprite(Engine(),"SCREENSPRITE."+s.name(),s.name());

		screenSprite.useXPercent = true;
		screenSprite.useYPercent = true;

		screenSprite.screenXPercent = screenX;
		screenSprite.screenYPercent = screenY;

		if(screenX==-1)screenSprite.centerX = true;
		if(screenY==-1)screenSprite.centerY = true;

		screenSprite.setRenderOrder(RenderOrder.ABOVE_TOP);


		getNextCommand();
	}

	//===============================================================================================
	private void createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy()//(SPRITE,FLOATx,FLOATy)
	{//===============================================================================================
		int p=0;

		Sprite s = (Sprite) currentCommand.parameterList.get(p++).object;
		float screenX = currentCommand.parameterList.get(p++).f;
		float screenY = currentCommand.parameterList.get(p++).f;


		//no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
		if(s==null)return;//block until sprite has loaded.

		ScreenSprite screenSprite = new ScreenSprite(Engine(),"SCREENSPRITE."+s.name(),s.name());

		screenSprite.useXPercent = true;
		screenSprite.useYPercent = true;

		screenSprite.screenXPercent = screenX;
		screenSprite.screenYPercent = screenY;

		if(screenX==-1)screenSprite.centerX = true;
		if(screenY==-1)screenSprite.centerY = true;

		getNextCommand();

	}

	//===============================================================================================
	private void createScreenSpriteUnderText_SPRITE_INTx_INTy()//(SPRITE,INTx,INTy)
	{//===============================================================================================
		int p=0;

		Sprite s = (Sprite) currentCommand.parameterList.get(p++).object;
		int screenX = currentCommand.parameterList.get(p++).i;
		int screenY = currentCommand.parameterList.get(p++).i;


		// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
		if(s==null)return;//block until sprite has loaded.

		ScreenSprite screenSprite = new ScreenSprite(Engine(),"SCREENSPRITE."+s.name(),s.name());
		screenSprite.screenXPixelsHQ = screenX;
		screenSprite.screenYPixelsHQ = screenY;

		if(screenX==-1)screenSprite.centerX = true;
		if(screenY==-1)screenSprite.centerY = true;

		screenSprite.setRenderOrder(RenderOrder.ABOVE_TOP);


		getNextCommand();
	}

	//===============================================================================================
	private void createScreenSpriteOverText_SPRITE_INTx_INTy()//(SPRITE,INTx,INTy)
	{//===============================================================================================
		int p=0;

		//DONE: should make the screen coords floats, for percentage of screen. 0.80% x, etc.
		//also an options for centerx and centery

		Sprite s = (Sprite) currentCommand.parameterList.get(p++).object;
		int screenX = currentCommand.parameterList.get(p++).i;
		int screenY = currentCommand.parameterList.get(p++).i;


		//no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
		if(s==null)return;//block until sprite has loaded.

		ScreenSprite screenSprite = new ScreenSprite(Engine(),"SCREENSPRITE."+s.name(),s.name());
		screenSprite.screenXPixelsHQ = screenX;
		screenSprite.screenYPixelsHQ = screenY;

		if(screenX==-1)screenSprite.centerX = true;
		if(screenY==-1)screenSprite.centerY = true;

		getNextCommand();

	}

	//===============================================================================================
	private void setCameraTarget_AREA()//(AREA)
	{//===============================================================================================
		int p=0;
		Area o = (Area)currentCommand.parameterList.get(p++).object;

		Cameraman().setTarget(o);

		getNextCommand();
	}

	//===============================================================================================
	private void setCameraTarget_ENTITY()//(ENTITY)
	{//===============================================================================================
		int p=0;
		Entity o = (Entity)currentCommand.parameterList.get(p++).object;

		Cameraman().setTarget(o);

		getNextCommand();
	}


	//===============================================================================================
	private void setCameraNoTarget()
	{//===============================================================================================
		//int p=0;
		Cameraman().setDummyTarget();

		getNextCommand();
	}

	//===============================================================================================
	private void setCameraIgnoreBounds_BOOL()
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		Cameraman().ignoreCameraFXBoundaries = b;
		getNextCommand();
	}

	//===============================================================================================
	private void setCameraTargetToPlayer()
	{//===============================================================================================
		//int p=0;
		Cameraman().setTarget(Player());

		getNextCommand();
	}

	//===============================================================================================
	private void blockUntilCameraReaches_AREA()
	{//===============================================================================================
		int p=0;
		Area o = (Area)currentCommand.parameterList.get(p++).object;

		if(o.isWithinScreenBounds())getNextCommand();
	}

	//===============================================================================================
	private void blockUntilCameraReaches_ENTITY()
	{//===============================================================================================
		int p=0;
		Entity o = (Entity)currentCommand.parameterList.get(p++).object;

		if(o.isWithinScreenBounds())getNextCommand();
	}

	//===============================================================================================
	private void blockUntilCameraReachesPlayer()
	{//===============================================================================================
		//int p=0;
		//Entity o = (Entity)currentCommand.parameterList.get(p++).object;

		if(Player().isWithinScreenBounds())getNextCommand();
	}

	//===============================================================================================
	private void pushCameraState()
	{//===============================================================================================
		//int p=0;
		//Kryo kryo = new Kryo();//TODO:

		//Engine().cameramanStack.push(kryo.copy(Engine().cameraman));

		getNextCommand();
	}

	//===============================================================================================
	private void popCameraState()
	{//===============================================================================================
		//int p=0;
		Engine().cameraman = Engine().cameramanStack.pop();
		getNextCommand();
	}

	//===============================================================================================
	private void setKeyboardCameraZoom_BOOL()
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		Cameraman().setPlayerCanZoomManuallyWithKeyboard(b);
		getNextCommand();
	}
	//===============================================================================================
	private void enableKeyboardCameraZoom()
	{//===============================================================================================
		//int p=0;
		//boolean b = currentCommand.parameterList.get(p++).b;
		Cameraman().setPlayerCanZoomManuallyWithKeyboard(true);
		getNextCommand();
	}
	//===============================================================================================
	private void disableKeyboardCameraZoom()
	{//===============================================================================================
		//int p=0;
		//boolean b = currentCommand.parameterList.get(p++).b;
		Cameraman().setPlayerCanZoomManuallyWithKeyboard(false);
		getNextCommand();
	}




	//===============================================================================================
	private void setCameraAutoZoomByPlayerMovement_BOOL()//(BOOL)
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		Cameraman().setAutoZoomByPlayerMovement(b);

		getNextCommand();
	}
	//===============================================================================================
	private void enableCameraAutoZoomByPlayerMovement()//(BOOL)
	{//===============================================================================================
		//int p=0;
		//boolean b = currentCommand.parameterList.get(p++).b;
		Cameraman().setAutoZoomByPlayerMovement(true);

		getNextCommand();
	}
	//===============================================================================================
	private void disableCameraAutoZoomByPlayerMovement()//(BOOL)
	{//===============================================================================================
		//int p=0;
		//boolean b = currentCommand.parameterList.get(p++).b;
		Cameraman().setAutoZoomByPlayerMovement(false);

		getNextCommand();
	}



	//===============================================================================================
	private void setCameraZoom_FLOAT()//(FLOAT)
	{//===============================================================================================
		int p=0;

		float f = currentCommand.parameterList.get(p++).f;
		Cameraman().ZOOMto = (f);

		getNextCommand();
	}

	//===============================================================================================
	private void setCameraSpeed_FLOAT()//(FLOAT)
	{//===============================================================================================
		int p=0;
		float f = currentCommand.parameterList.get(p++).f;

		Cameraman().speedMultiplier = f;

		getNextCommand();
	}













//	//===============================================================================================
//	private void setEntityProperty_ENTITY_STRINGpropertyName_BOOL()//(ENTITY,STRINGpropertyName,BOOL)
//	{//===============================================================================================
//		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
//
//		boolean b = currentCommand.parameterList.get(p++).b;
//
//		// TODO
//
//		getNextCommand();
//
//	}



	//===============================================================================================
	private void giveItem_ITEM()//(ITEM)
	{//===============================================================================================
		int p=0;

		Item i = (Item) currentCommand.parameterList.get(p++).object;

		//TODO:ask the server if we can do this

		//confirm this action with the server
		i.getWithCaption_S();

		getNextCommand();
	}


	//===============================================================================================
	private void takeItem_ITEM()//(ITEM)
	{//===============================================================================================
		int p=0;

		Item i = (Item) currentCommand.parameterList.get(p++).object;

		//confirm this action with the server
		i.setHaveItemValue_S(false);


		getNextCommand();
	}


	//===============================================================================================
	private void giveGame_GAME()//(GAME)
	{//===============================================================================================
		int p=0;

		Item i = (Item) currentCommand.parameterList.get(p++).object;

		//TODO:ask the server if we can do this

		//confirm this action with the server
		i.getWithCaption_S();

		getNextCommand();
	}


	//===============================================================================================
	private void takeMoney_FLOAT()//(FLOAT)
	{//===============================================================================================
		//int p=0;

		//confirm this action with the server

		// TODO

		getNextCommand();
	}


	//===============================================================================================
	private void giveMoney_FLOAT()//(FLOAT)
	{//===============================================================================================
		//int p=0;

		//TODO: maybe only server can perform this command.
		//every money request should be performed on the server after activating a certain flag.
		//so each money you get should have a name.

		//ask the server if we can do this

		//confirm this action with the server


		// TODO


		getNextCommand();
	}


	//===============================================================================================
	private void playSound_SOUND()//(SOUND)
	{//===============================================================================================
		int p=0;
		Sound s = (Sound) currentCommand.parameterList.get(p++).object;

		AudioManager().playSound(s);
		getNextCommand();
	}

	//===============================================================================================
	private void playSound_SOUND_FLOATvol()
	{//===============================================================================================
		int p=0;
		Sound s = (Sound) currentCommand.parameterList.get(p++).object;
		float vol = currentCommand.parameterList.get(p++).f;

		AudioManager().playSound(s,vol);
		getNextCommand();
	}

	//===============================================================================================
	private void playSound_SOUND_FLOATvol_FLOATpitch_INTtimes()
	{//===============================================================================================
		int p=0;
		Sound s = (Sound) currentCommand.parameterList.get(p++).object;
		float vol = currentCommand.parameterList.get(p++).f;
		float pitch = currentCommand.parameterList.get(p++).f;
		int times = currentCommand.parameterList.get(p++).i;

		AudioManager().playSound(s,vol,pitch,times);
		getNextCommand();
	}

	//===============================================================================================
	private void playMusicOnce_MUSIC()
	{//===============================================================================================
		int p=0;
		Music m = (Music) currentCommand.parameterList.get(p++).object;

		AudioManager().playMusic(m,1.0f,1.0f,false);
		getNextCommand();
	}


	//===============================================================================================
	private void playMusicLoop_MUSIC()
	{//===============================================================================================
		int p=0;
		Music m = (Music) currentCommand.parameterList.get(p++).object;

		AudioManager().playMusic(m,1.0f,1.0f,true);
		getNextCommand();
	}

	//===============================================================================================
	private void playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop()
	{//===============================================================================================
		int p=0;
		Music m = (Music) currentCommand.parameterList.get(p++).object;
		float vol = currentCommand.parameterList.get(p++).f;
		float pitch = currentCommand.parameterList.get(p++).f;
		boolean loop = currentCommand.parameterList.get(p++).b;

		AudioManager().playMusic(m,vol,pitch,loop);
		getNextCommand();
	}

	//===============================================================================================
	private void stopMusic_MUSIC()
	{//===============================================================================================
		int p=0;
		Music m = (Music) currentCommand.parameterList.get(p++).object;

		AudioManager().stopMusic(m);

		getNextCommand();
	}
	//===============================================================================================
	private void stopAllMusic()
	{//===============================================================================================
		//int p=0;
		AudioManager().stopAllMusic();

		getNextCommand();
	}

	//===============================================================================================
	private void blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC()
	{//===============================================================================================
		int p=0;
		Music currentPlaying = (Music) currentCommand.parameterList.get(p++).object;
		Music replaceWith = (Music) currentCommand.parameterList.get(p++).object;

		if(currentPlaying.getLoop()==true)currentPlaying.setLoop(false);

		replaceWith.loadDataIntoChannel();

		if(currentPlaying.isPlaying()==false)
		{
			AudioManager().playMusic(replaceWith,currentPlaying.volume,currentPlaying.pitch,true);

			getNextCommand();
		}

	}

	//===============================================================================================
	private void blockUntilMusicDone_MUSIC()
	{//===============================================================================================
		int p=0;

		Music m = (Music) currentCommand.parameterList.get(p++).object;

		//if music is LOOPING this will always block
		if(m!=null)
		{
			if(m.getLoop() && m.isFadingOut()==false)
			{
				m.setLoop(false);
			}
		}

		if(m.isPlaying()==false)getNextCommand();

	}

	//===============================================================================================
	private void blockUntilAllMusicDone()
	{//===============================================================================================
		//int p=0;


		//if music is LOOPING this will always block
		AudioManager().setAllLoopingMusicThatIsNotFadingOutToNotLoop();

		if(AudioManager().isAnyMusicPlaying()==false)
		{
			getNextCommand();
		}

	}

	//===============================================================================================
	private void fadeOutMusic_MUSIC_INT()
	{//===============================================================================================
		int p=0;

		Music m = (Music) currentCommand.parameterList.get(p++).object;
		int ticks = currentCommand.parameterList.get(p++).i;

		AudioManager().fadeOutMusic(m,ticks);

		getNextCommand();
	}

	//===============================================================================================
	private void fadeOutAllMusic_INT()
	{//===============================================================================================
		int p=0;

		int ticks = currentCommand.parameterList.get(p++).i;

		AudioManager().fadeOutAllMusic(ticks);

		getNextCommand();
	}

	//===============================================================================================
	private void shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake()
	{//===============================================================================================
		int p=0;
		int ticks = currentCommand.parameterList.get(p++).i;
		int maxX = currentCommand.parameterList.get(p++).i;
		int maxY = currentCommand.parameterList.get(p++).i;
		int ticksPerShake = currentCommand.parameterList.get(p++).i;

		CinematicsManager().shakeScreenForTicksDurationEaseInAndOutToMaxAmountWithEasingBetweenShakes(ticks,maxX,maxY,ticksPerShake);

		getNextCommand();
	}


	//===============================================================================================
	private void fadeToBlack_INTticks()
	{//===============================================================================================
		int p=0;
		int ticks = currentCommand.parameterList.get(p++).i;
		CinematicsManager().fadeToBlack(ticks);

		getNextCommand();
	}


	//===============================================================================================
	private void fadeFromBlack_INTticks()
	{//===============================================================================================
		int p=0;
		int ticks = currentCommand.parameterList.get(p++).i;
		CinematicsManager().fadeFromBlack(ticks);

		getNextCommand();
	}


	//===============================================================================================
	private void fadeToWhite_INTticks()
	{//===============================================================================================
		int p=0;
		int ticks = currentCommand.parameterList.get(p++).i;
		CinematicsManager().fadeToWhite(ticks);

		getNextCommand();
	}


	//===============================================================================================
	private void fadeFromWhite_INTticks()
	{//===============================================================================================
		int p=0;
		int ticks = currentCommand.parameterList.get(p++).i;
		CinematicsManager().fadeFromWhite(ticks);

		getNextCommand();
	}

	//===============================================================================================
	private void fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha()
	{//===============================================================================================
		int p=0;
		int ticks = currentCommand.parameterList.get(p++).i;
		int ri = currentCommand.parameterList.get(p++).i;
		int gi = currentCommand.parameterList.get(p++).i;
		int bi = currentCommand.parameterList.get(p++).i;
		float toAlpha = currentCommand.parameterList.get(p++).f;

		CinematicsManager().fadeColorFromCurrentAlphaToAlpha(ticks,ri,gi,bi,toAlpha);

		getNextCommand();
	}
	//===============================================================================================
	private void fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha()
	{//===============================================================================================
		int p=0;
		int ticks = currentCommand.parameterList.get(p++).i;
		int ri = currentCommand.parameterList.get(p++).i;
		int gi = currentCommand.parameterList.get(p++).i;
		int bi = currentCommand.parameterList.get(p++).i;
		float fromAlpha = currentCommand.parameterList.get(p++).f;
		float toAlpha = currentCommand.parameterList.get(p++).f;

		CinematicsManager().fadeColorFromAlphaToAlpha(ticks,ri,gi,bi,fromAlpha,toAlpha);

		getNextCommand();
	}
	//===============================================================================================
	private void fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha()
	{//===============================================================================================
		int p=0;
		int ticks = currentCommand.parameterList.get(p++).i;
		int ri = currentCommand.parameterList.get(p++).i;
		int gi = currentCommand.parameterList.get(p++).i;
		int bi = currentCommand.parameterList.get(p++).i;
		float toAlpha = currentCommand.parameterList.get(p++).f;

		CinematicsManager().fadeColorFromTransparentToAlphaBackToTransparent(ticks,ri,gi,bi,toAlpha);

		getNextCommand();
	}
	//===============================================================================================
	private void setInstantOverlay_INTr_INTg_INTb_FLOATa()
	{//===============================================================================================
		int p=0;
		int ri = currentCommand.parameterList.get(p++).i;
		int gi = currentCommand.parameterList.get(p++).i;
		int bi = currentCommand.parameterList.get(p++).i;
		float a = currentCommand.parameterList.get(p++).f;


		CinematicsManager().setInstantOverlayColor(ri,gi,bi,a);

		getNextCommand();
	}

	//===============================================================================================
	private void clearOverlay()
	{//===============================================================================================
		//int p=0;


		CinematicsManager().clearOverlay();

		getNextCommand();
	}










	//===============================================================================================
	private void fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha()
	{//===============================================================================================
		int p=0;
		int ticks = currentCommand.parameterList.get(p++).i;
		int ri = currentCommand.parameterList.get(p++).i;
		int gi = currentCommand.parameterList.get(p++).i;
		int bi = currentCommand.parameterList.get(p++).i;
		float toAlpha = currentCommand.parameterList.get(p++).f;

		CinematicsManager().fadeColorFromCurrentAlphaToAlphaUnderLights(ticks,ri,gi,bi,toAlpha);

		getNextCommand();
	}


	//===============================================================================================
	private void setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa()
	{//===============================================================================================
		int p=0;
		int ri = currentCommand.parameterList.get(p++).i;
		int gi = currentCommand.parameterList.get(p++).i;
		int bi = currentCommand.parameterList.get(p++).i;
		float a = currentCommand.parameterList.get(p++).f;


		CinematicsManager().setInstantOverlayColorUnderLights(ri,gi,bi,a);

		getNextCommand();
	}

	//===============================================================================================
	private void clearOverlayUnderLights()
	{//===============================================================================================
		//int p=0;


		CinematicsManager().clearOverlayUnderLights();

		getNextCommand();
	}




	//===============================================================================================
	private void fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha()
	{//===============================================================================================
		int p=0;
		int ticks = currentCommand.parameterList.get(p++).i;
		int ri = currentCommand.parameterList.get(p++).i;
		int gi = currentCommand.parameterList.get(p++).i;
		int bi = currentCommand.parameterList.get(p++).i;
		float toAlpha = currentCommand.parameterList.get(p++).f;

		CinematicsManager().fadeColorFromCurrentAlphaToAlphaGroundLayer(ticks,ri,gi,bi,toAlpha);

		getNextCommand();
	}


	//===============================================================================================
	private void setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa()
	{//===============================================================================================
		int p=0;
		int ri = currentCommand.parameterList.get(p++).i;
		int gi = currentCommand.parameterList.get(p++).i;
		int bi = currentCommand.parameterList.get(p++).i;
		float a = currentCommand.parameterList.get(p++).f;


		CinematicsManager().setInstantOverlayColorGroundLayer(ri,gi,bi,a);

		getNextCommand();
	}

	//===============================================================================================
	private void clearOverlayGroundLayer()
	{//===============================================================================================
		//int p=0;


		CinematicsManager().clearOverlayGroundLayer();

		getNextCommand();
	}


	//===============================================================================================
	private void setLetterbox_BOOL()
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;

		CinematicsManager().setLetterbox(b,1000,0.25f);

		getNextCommand();
	}

	//===============================================================================================
	private void setLetterbox_BOOL_INTticks()//(BOOL_INTticks)
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		int slideDurationTicks = currentCommand.parameterList.get(p++).i;


		CinematicsManager().setLetterbox(b,slideDurationTicks,0.25f);

		getNextCommand();
	}


	//===============================================================================================
	private void setLetterbox_BOOL_INTticks_INTsize()//(BOOL)
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		int slideDurationTicks = currentCommand.parameterList.get(p++).i;
		int sizeY = currentCommand.parameterList.get(p++).i;

		CinematicsManager().setLetterbox(b,slideDurationTicks,sizeY);

		getNextCommand();
	}

	//===============================================================================================
	private void setLetterbox_BOOL_INTticks_FLOATsize()//(BOOL)
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		int slideDurationTicks = currentCommand.parameterList.get(p++).i;
		float sizePercent = currentCommand.parameterList.get(p++).f;


		CinematicsManager().setLetterbox(b,slideDurationTicks,sizePercent);

		getNextCommand();
	}

	//===============================================================================================
	private void setBlur_BOOL()//(BOOL)
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		CinematicsManager().setBlur(b);
		getNextCommand();
	}


	//===============================================================================================
	private void setMosaic_BOOL()//(BOOL)
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		CinematicsManager().setMosaic(b);
		getNextCommand();
	}


	//===============================================================================================
	private void setHBlankWave_BOOL()//(BOOL)
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		CinematicsManager().setHBlankWave(b);
		getNextCommand();
	}


	//===============================================================================================
	private void setRotate_BOOL()//(BOOL)
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		CinematicsManager().setRotate(b);
		getNextCommand();
	}


	//===============================================================================================
	private void setBlackAndWhite_BOOL()//(BOOL)
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		CinematicsManager().setBlackAndWhite(b);
		getNextCommand();
	}


	//===============================================================================================
	private void setInvertedColors_BOOL()//(BOOL)
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		CinematicsManager().setInvertedColors(b);
		getNextCommand();
	}


	//===============================================================================================
	private void set8BitMode_BOOL()//(BOOL)
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		CinematicsManager().set8BitMode(b);
		getNextCommand();
	}


	//===============================================================================================
	private void setEngineSpeed_FLOAT()//(INT)
	{//===============================================================================================
		int p=0;

		float f = currentCommand.parameterList.get(p++).f;
		Engine().setEngineSpeed(f);

		getNextCommand();
	}


	//===============================================================================================
	private void toggleLightOnOff_LIGHT()//(LIGHT)
	{//===============================================================================================
		int p=0;

		Light l = (Light) currentCommand.parameterList.get(p++).object;

		l.toggle();

		getNextCommand();
	}


	//===============================================================================================
	private void setLightOnOff_LIGHT_BOOL()//(LIGHT,BOOL)
	{//===============================================================================================
		int p=0;
		Light l = (Light) currentCommand.parameterList.get(p++).object;
		boolean b = currentCommand.parameterList.get(p++).b;

		l.setOnOff(b);

		getNextCommand();
	}

	//===============================================================================================
	private void setLightFlicker_LIGHT_BOOL()//(LIGHT,BOOL)
	{//===============================================================================================
		int p=0;
		Light l = (Light) currentCommand.parameterList.get(p++).object;
		boolean b = currentCommand.parameterList.get(p++).b;

		l.setFlicker(b);

		getNextCommand();
	}

	//===============================================================================================
	private void toggleAllLightsOnOff()
	{//===============================================================================================
		//int p=0;

		for(int i=0;i<getMap().currentState.lightList.size();i++)
		{
			getMap().currentState.lightList.get(i).toggle();
		}

		getNextCommand();
	}


	//===============================================================================================
	private void setAllLightsOnOff_BOOL()//(BOOL)
	{//===============================================================================================
		int p=0;

		boolean b = currentCommand.parameterList.get(p++).b;

		for(int i=0;i<getMap().currentState.lightList.size();i++)
		{
			getMap().currentState.lightList.get(i).setOnOff(b);
		}

		getNextCommand();
	}


	//===============================================================================================
	private void setRandomSpawn_BOOL()
	{//===============================================================================================
		int p=0;

		boolean b = currentCommand.parameterList.get(p++).b;


		getMap().randomSpawnEnabled = b;

		getNextCommand();
	}



	//===============================================================================================
	private void deleteRandoms()
	{//===============================================================================================
		//int p=0;

		for(int i=0;i<getMap().activeEntityList.size();i++)
		{
			Entity e = getMap().activeEntityList.get(i);

			if(e.getClass().equals(RandomCharacter.class))e.fadeOutAndDelete();
		}

		getNextCommand();
	}


	//===============================================================================================
	private void makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb()
	{//===============================================================================================
		int p=0;
		GameString s = (GameString) currentCommand.parameterList.get(p++).object;
		int sec = currentCommand.parameterList.get(p++).i;
		int x = currentCommand.parameterList.get(p++).i;
		int y = currentCommand.parameterList.get(p++).i;
		int r = currentCommand.parameterList.get(p++).i;
		int g = currentCommand.parameterList.get(p++).i;
		int b = currentCommand.parameterList.get(p++).i;


		if(s.getInitialized_S()==false)
		{
			return; //wait for object to receive server data in its update() function
		}
		else
		{
			CaptionManager().newManagedCaption(x, y, sec*1000, s.text(), BobFont.font_small_16_outlined_smooth, new BobColor(r,g,b), BobColor.clear, RenderOrder.ABOVE_TOP, 1.0f, 0);
			getNextCommand();
		}
	}

	//===============================================================================================
	private void makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb()
	{//===============================================================================================
		int p=0;
		GameString s = (GameString) currentCommand.parameterList.get(p++).object;
		int sec = currentCommand.parameterList.get(p++).i;
		int r = currentCommand.parameterList.get(p++).i;
		int g = currentCommand.parameterList.get(p++).i;
		int b = currentCommand.parameterList.get(p++).i;


		if(s.getInitialized_S()==false)
		{
			return; //wait for object to receive server data in its update() function
		}
		else
		{
			Caption c = CaptionManager().newManagedCaption(Caption.CENTERED_OVER_ENTITY, -20, sec*1000, s.text(), BobFont.font_small_16_outlined_smooth, new BobColor(r,g,b), BobColor.clear, RenderOrder.ABOVE_TOP, 1.0f, 0);
			c.setEntity(Player()); //not really necessary, it does this automatically
			getNextCommand();
		}
	}

	//===============================================================================================
	private void makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb()
	{//===============================================================================================
		int p=0;
		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
		GameString s = (GameString) currentCommand.parameterList.get(p++).object;
		int sec = currentCommand.parameterList.get(p++).i;
		int r = currentCommand.parameterList.get(p++).i;
		int g = currentCommand.parameterList.get(p++).i;
		int b = currentCommand.parameterList.get(p++).i;


		if(s.getInitialized_S()==false)
		{
			return; //wait for object to receive server data in its update() function
		}
		else
		{
			Caption c = CaptionManager().newManagedCaption(Caption.CENTERED_OVER_ENTITY,-20, sec*1000, s.text(), BobFont.font_small_16_outlined_smooth, new BobColor(r,g,b), BobColor.clear, RenderOrder.ABOVE_TOP, 1.0f, 0);
			c.setEntity(e);
			getNextCommand();
		}
	}
	//===============================================================================================
	private void makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb()//(STRING,INTsec,INTx,INTy,INTr,INTg,INTb)
	{//===============================================================================================
		int p=0;
		GameString s = (GameString) currentCommand.parameterList.get(p++).object;
//		int sec = currentCommand.parameterList.get(p++).i;
//		int x = currentCommand.parameterList.get(p++).i;
//		int y = currentCommand.parameterList.get(p++).i;
//		int r = currentCommand.parameterList.get(p++).i;
//		int g = currentCommand.parameterList.get(p++).i;
//		int b = currentCommand.parameterList.get(p++).i;

		//TODO: make notification stuff better, use colors and xy

		if(s.getInitialized_S()==false)
		{
			return; //wait for object to receive server data in its update() function
		}
		else
		{
			NotificationManager().add(new Notification(ClientGameEngine(), s.text()));
			getNextCommand();
		}
	}
	//===============================================================================================
	private void setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks()
	{//===============================================================================================
		int p=0;
		GameString gameString = (GameString) currentCommand.parameterList.get(p++).object;
		int r = currentCommand.parameterList.get(p++).i;
		int g = currentCommand.parameterList.get(p++).i;
		int b = currentCommand.parameterList.get(p++).i;
		int ticks = currentCommand.parameterList.get(p++).i;

		Console.add(gameString.text(),new BobColor(r,g,b),ticks);


		getNextCommand();

	}


	//===============================================================================================
	private void setShowClockCaption_BOOL()
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		StatusBar().clockCaption.setEnabled(b);
		getNextCommand();
	}
	//===============================================================================================
	private void setShowDayCaption_BOOL()
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		StatusBar().dayCaption.setEnabled(b);
		getNextCommand();
	}
	//===============================================================================================
	private void setShowMoneyCaption_BOOL()
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		StatusBar().moneyCaption.setEnabled(b);
		getNextCommand();
	}

	//===============================================================================================
	private void setShowAllStatusBarCaptions_BOOL()
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		StatusBar().moneyCaption.setEnabled(b);
		StatusBar().clockCaption.setEnabled(b);
		StatusBar().dayCaption.setEnabled(b);
		getNextCommand();
	}

	//===============================================================================================
	private void setShowStatusBar_BOOL()
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;
		StatusBar().setEnabled(b);
		getNextCommand();
	}
	//===============================================================================================
	private void setShowNDButton_BOOL()
	{//===============================================================================================
		int p=0;

		boolean b = currentCommand.parameterList.get(p++).b;
		StatusBar().ndButton.setEnabled(b);
		getNextCommand();
	}
	//===============================================================================================
	private void setShowGameStoreButton_BOOL()
	{//===============================================================================================
		int p=0;

		boolean b = currentCommand.parameterList.get(p++).b;
		StatusBar().gameStoreButton.setEnabled(b);
		getNextCommand();
	}
	//===============================================================================================
	private void setShowStuffButton_BOOL()
	{//===============================================================================================
		int p=0;

		boolean b = currentCommand.parameterList.get(p++).b;
		StatusBar().stuffButton.setEnabled(b);
		getNextCommand();
	}

	//===============================================================================================
	private void setShowAllButtons_BOOL()
	{//===============================================================================================
		int p=0;

		boolean b = currentCommand.parameterList.get(p++).b;
		StatusBar().stuffButton.setEnabled(b);
		StatusBar().gameStoreButton.setEnabled(b);
		StatusBar().ndButton.setEnabled(b);
		getNextCommand();
	}


	//===============================================================================================
	private void setNDEnabled_BOOL()
	{//===============================================================================================
		int p=0;

		boolean b = currentCommand.parameterList.get(p++).b;
		ND().setEnabled(b);
		getNextCommand();
	}

	//===============================================================================================
	private void setGameStoreMenuEnabled_BOOL()
	{//===============================================================================================
		int p=0;

		boolean b = currentCommand.parameterList.get(p++).b;
		GameStore().setEnabled(b);
		getNextCommand();
	}

	//===============================================================================================
	private void setStuffMenuEnabled_BOOL()
	{//===============================================================================================
		int p=0;

		boolean b = currentCommand.parameterList.get(p++).b;
		StuffMenu().setEnabled(b);
		getNextCommand();
	}

	//===============================================================================================
	private void setAllMenusAndNDEnabled_BOOL()
	{//===============================================================================================
		int p=0;
		boolean b = currentCommand.parameterList.get(p++).b;

		if(b)GUIManager().enableAllMenusAndND();
		else GUIManager().disableAllMenusAndND();

		getNextCommand();
	}



	//===============================================================================================
	private void setClockUnknown()
	{//===============================================================================================
		//int p=0;
		Clock().setUnknown(true);

		getNextCommand();
	}

	//===============================================================================================
	private void setClockNormal()
	{//===============================================================================================
		//int p=0;
		Clock().setUnknown(false);

		getNextCommand();
	}

	//===============================================================================================
	private void setTimePaused_BOOL()
	{//===============================================================================================
		int p=0;

		boolean b = currentCommand.parameterList.get(p++).b;


		Clock().setPaused(b);

		getNextCommand();
	}

	//===============================================================================================
	private void setTimeFastForward()
	{//===============================================================================================
		//int p=0;

		Clock().setFast(true);

		getNextCommand();
	}

	//===============================================================================================
	private void setTimeNormalSpeed()
	{//===============================================================================================
		//int p=0;
		Clock().setFast(false);

		getNextCommand();
	}

	//===============================================================================================
	private void setNDOpen_BOOL()
	{//===============================================================================================
		int p=0;

		boolean b = currentCommand.parameterList.get(p++).b;

		if(b)GUIManager().openND();
		else GUIManager().closeND();

		getNextCommand();
	}

	//===============================================================================================
	private void startGame()
	{//===============================================================================================
		//int p=0;
		GUIManager().openND();
		//ND().startGame();

		//TODO
		getNextCommand();
	}


	//===============================================================================================
	private void startBobsGameOnStadiumScreen_AREA()
	{//===============================================================================================
		int p=0;
		Area a = (Area) currentCommand.parameterList.get(p++).object;

		BobsGameStadium bobsGameStadium = new BobsGameStadium(ClientGameEngine().stadiumScreen, a);
		bobsGameStadium.init();

		Cache.writeDidIntroFile();


		getNextCommand();
	}


	//===============================================================================================
	private void blockUntilBobsGameDead()
	{//===============================================================================================
		//int p=0;


		BobsGameStadium bobsGameStadium = (BobsGameStadium)ClientGameEngine().stadiumScreen.stadiumGameStateManager.getState();

		if(bobsGameStadium!=null)
		{
			if(bobsGameStadium.ME.dead)
			{
				ClientGameEngine().stadiumScreen.setActivated(false);
				getNextCommand();
			}
		}

	}

	//===============================================================================================
	private void showLoginScreen()
	{//===============================================================================================
		//int p=0;

		//ClientMain.introMode = false;

		//ClientMain.clientMain.makeNewClientEngine();
		ClientMain.clientMain.stateManager.setState(ClientMain.clientMain.titleScreenState);


		//ClientMain.clientMain.showControlsImage();

		getNextCommand();

	}

	//===============================================================================================
	private void closeAllMenusAndND()
	{//===============================================================================================
		//int p=0;
		GUIManager().closeAllMenusAndND();

		getNextCommand();
	}

	//===============================================================================================
	private void openStuffMenu()
	{//===============================================================================================
		//int p=0;
		GUIManager().openStuffMenu();

		getNextCommand();
	}


	//===============================================================================================
	private void openItemsMenu()
	{//===============================================================================================
		//int p=0;
		GUIManager().openItemsMenu();

		getNextCommand();
	}


	//===============================================================================================
	private void openLogMenu()
	{//===============================================================================================
		//int p=0;
		GUIManager().openLogMenu();

		getNextCommand();
	}


	//===============================================================================================
	private void openStatusMenu()
	{//===============================================================================================
		//int p=0;
		GUIManager().openStatusMenu();

		getNextCommand();
	}


	//===============================================================================================
	private void openFriendsMenu()
	{//===============================================================================================
		//int p=0;
		GUIManager().openFriendsMenu();

		getNextCommand();
	}


	//===============================================================================================
	private void openSettingsMenu()
	{//===============================================================================================
		//int p=0;
		GUIManager().openSettingsMenu();

		getNextCommand();
	}


	//===============================================================================================
	private void openGameStoreMenu()
	{//===============================================================================================
		int p=0;

		GUIManager().openGameStore();

		getNextCommand();
	}


	//===============================================================================================
	private void pushGameState()
	{//===============================================================================================
		//int p=0;

		getNextCommand();//do this first so when i restore it, it doesn't push the stack again.

		//should have ClientMain.gameStack ArrayDeque

		//Kryo kryo = new Kryo();//TODO:
		//ClientMain.clientMain.gameStack.push(kryo.copy(ClientMain.clientMain.clientGameEngine));

	}


	//===============================================================================================
	private void popGameState()
	{//===============================================================================================
		//int p=0;

		if(ClientMain.clientMain.gameStack.size()>0)
		{
			ClientMain.clientMain.clientGameEngine = ClientMain.clientMain.gameStack.pop();
		}

		getNextCommand();

	}


	//===============================================================================================
	private void showTitleScreen()
	{//===============================================================================================
		//int p=0;
		// TODO

		getNextCommand();
	}


	//===============================================================================================
	private void showCinemaEvent()
	{//===============================================================================================
		//int p=0;
		// TODO

		getNextCommand();
	}


	//===============================================================================================
	private void runGlobalEvent()
	{//===============================================================================================
		//int p=0;
		// TODO

		getNextCommand();
	}















}
