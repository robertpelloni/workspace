package com.bobsgame.client.engine.game.nd;

import java.util.ArrayList;

//import io.netty.channel.ChannelHandlerContext;

import com.bobsgame.client.Texture;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.game.FriendCharacter;
import com.bobsgame.client.engine.game.MiniGameEngine;
import com.bobsgame.client.engine.text.BobFont;
import com.bobsgame.client.engine.text.Caption;
import com.bobsgame.client.network.UDPConnection;
import com.bobsgame.net.BobNet;
import com.bobsgame.shared.BobColor;


//=========================================================================================================================
public class NDGameEngine extends MiniGameEngine
{//=========================================================================================================================


	protected ND nD;


	public UDPConnection connection = null;

	//public boolean multiplayer = false;


	public int numTileScreenTextureFrames = 0;
	//public Texture[] titleScreenTextures;
	public Texture titleScreenTexture;
	public Texture cursorTexture = null;

	public long titleScreenFrameTicks=0;
	public int currentTitleScreenTextureFrame=0;
	public boolean showingTitleScreen = false;
	boolean showingMultiplayerScreen = false;
	Caption singlePlayerCaption = null;
	Caption multiPlayerCaption = null;
	public boolean singlePlayerMultiPlayerSwitchToggle = false;//false = singleplayer
	public long cursorInOutToggleTicks = 0;
	public boolean cursorInOutToggle = false;

	ArrayList<Caption> onlineFriendCaptions = null;
	ArrayList<FriendCharacter> onlineFriends = null;
	int multiplayerScreenCursorPosition = 0;

	protected FriendCharacter friend = null;
	protected boolean showingWaitingForFriendScreen = false;
	ArrayList<Caption> waitingForFriendCaptions = null;



	public String name = "";

	//=========================================================================================================================
	public NDGameEngine(ND nD)
	{//=========================================================================================================================
		super();

		this.nD=nD;

		setupLoadScreens();

		new GameDataLoader(this);
	}



	//=========================================================================================================================
	public void setupLoadScreens()
	{//=========================================================================================================================
		//override
	}

	//=========================================================================================================================
	public void unloadTextures()
	{//=========================================================================================================================
		if(titleScreenTexture!=null)titleScreenTexture = GLUtils.releaseTexture(titleScreenTexture);
		if(cursorTexture!=null)cursorTexture = GLUtils.releaseTexture(cursorTexture);
	}

	//=========================================================================================================================
	public String getGameName()
	{//=========================================================================================================================
		return name;
	}


	//=========================================================================================================================
	public void setConnection(UDPConnection connection)
	{//=========================================================================================================================

		this.connection = connection;
		//this.multiplayer = true;

	}



	//=========================================================================================================================
	public float getWidth()
	{//=========================================================================================================================
		return ND.SCREEN_SIZE_X;
	}
	//=========================================================================================================================
	public float getHeight()
	{//=========================================================================================================================
		return ND.SCREEN_SIZE_Y;
	}


	//=========================================================================================================================
	public void tryToCloseGame()
	{//=========================================================================================================================

		nD.setActivated(false);

		//override this!
	}

	//=========================================================================================================================
	public void handleMessage(String s)
	{//=========================================================================================================================

		//String s = (String) e.getMessage();

		//log.debug(s);


		if(s.indexOf(":")==-1)return;
		String command = s.substring(0,s.indexOf(":")+1);
		s = s.substring(s.indexOf(":")+1);



		if(command.equals(BobNet.Game_Challenge_Response)){incoming_GameChallengeResponse(s);return;}


	}



	//=========================================================================================================================
	private void incoming_GameChallengeResponse(String s)
	{//=========================================================================================================================
		//responseString

		if(s.startsWith("Decline"))setIncomingGameChallengeResponse(gameChallengeResponse_DECLINE);
		if(s.startsWith("Accept"))setIncomingGameChallengeResponse(gameChallengeResponse_ACCEPT);


	}






	boolean throttle30fps = false;
	long ticksPassed = 0;
	long frameThrottleTicks = 0;

	public boolean networkGameStarted_NonThreaded = false;
	protected long nonThreadedTicksCounter = 0;
	//=========================================================================================================================
	public long engineTicksPassed()
	{//=========================================================================================================================
		return ticksPassed;
	}

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		frameThrottleTicks += super.engineTicksPassed();
		if(throttle30fps&&frameThrottleTicks<33)return;
		ticksPassed = frameThrottleTicks;
		frameThrottleTicks = 0;


		super.update();



		titleScreenFrameTicks+= super.engineTicksPassed();
		if(titleScreenFrameTicks>30)
		{
			titleScreenFrameTicks=0;
			currentTitleScreenTextureFrame++;
			if(currentTitleScreenTextureFrame>=numTileScreenTextureFrames)currentTitleScreenTextureFrame=0;

			updateTitleScreenLogoTexture();
		}



		cursorInOutToggleTicks+= super.engineTicksPassed();
		if(cursorInOutToggleTicks>300)
		{
			cursorInOutToggleTicks=0;
			cursorInOutToggle = !cursorInOutToggle;
		}



	}


	//=========================================================================================================================
	public boolean updateLoadScreens()
	{//=========================================================================================================================


		//skip the title screen if we were initialized with a connection, either we are in the simulator or got a friend request

		if(connection==null)
		{

			if(showingTitleScreen)
			{
				updateTitleScreen();
				return true;
			}


			if(showingMultiplayerScreen)
			{
				updateMultiplayerScreen();
				return true;
			}

		}


		//unloadTitleScreenTextures();


		if(showingWaitingForFriendScreen)
		{
			updateWaitingForFriendScreen();
			return true;
		}

		return false;
	}

	//=========================================================================================================================
	public void updateTitleScreenLogoTexture()
	{//=========================================================================================================================
		//override
	}


	//=========================================================================================================================
	private void updateTitleScreen()
	{//=========================================================================================================================

		//if(titleScreenTextures==null)setupLoadScreens();



		if(singlePlayerCaption==null)singlePlayerCaption = CaptionManager().newManagedCaption(Caption.CENTERED_X,(int)(getHeight()/3*2),-1,"Single Player",BobFont.font_normal_16_outlined_smooth,BobColor.white,BobColor.clear,1.0f);



		if(onlineFriends==null)
		{

			onlineFriends = new ArrayList<FriendCharacter>();

			if(ClientGameEngine()!=null)
			{

				for(int i=0;i<FriendManager().friendCharacters.size();i++)
				{
					FriendCharacter f = FriendManager().friendCharacters.get(i);
					if(
						f.connected()==true
						&&
						f.getGotFriendData_S()==true
						&&
						f.getStatus_S()==FriendCharacter.status_AVAILABLE
					)
					{
						onlineFriends.add(f);
					}
				}
			}

		}

		if(onlineFriends.size()>0)
		{
			if(multiPlayerCaption==null)multiPlayerCaption = CaptionManager().newManagedCaption(Caption.CENTERED_X,(int)(getHeight()/3*2)+30,-1,"Multiplayer",BobFont.font_normal_16_outlined_smooth,BobColor.white,BobColor.clear,1.0f);

			if(ControlsManager().BUTTON_UP_PRESSED || ControlsManager().BUTTON_DOWN_PRESSED)
			{
				singlePlayerMultiPlayerSwitchToggle = !singlePlayerMultiPlayerSwitchToggle;
			}
		}


		if(ControlsManager().BUTTON_ACTION_PRESSED)
		{
			showingTitleScreen=false;
			if(singlePlayerMultiPlayerSwitchToggle==true)showingMultiplayerScreen=true;

			if(singlePlayerCaption!=null){singlePlayerCaption.deleteImmediately();singlePlayerCaption = null;}
			if(multiPlayerCaption!=null){multiPlayerCaption.deleteImmediately();multiPlayerCaption = null;}
		}

	}


//	//=========================================================================================================================
//	private void unloadTitleScreenTextures()
//	{//=========================================================================================================================
//		if(titleScreenTextures!=null)
//		{
//			if(titleScreenTextures[0]!=null)
//			{
//				for(int i=0;i<numTileScreenTextureFrames;i++)titleScreenTextures[i] = GLUtils.releaseTexture(titleScreenTextures[i]);
//			}
//			titleScreenTextures=null;
//		}
//	}



	//=========================================================================================================================
	private void updateMultiplayerScreen()
	{//=========================================================================================================================


		if(onlineFriendCaptions==null)
		{
			onlineFriendCaptions = new ArrayList<Caption>();

			for(int i=0;i<onlineFriends.size();i++)
			{
				FriendCharacter f = onlineFriends.get(i);
				int y = (onlineFriendCaptions.size()+1) * 20;

				Caption c = CaptionManager().newManagedCaption(Caption.CENTERED_X,y,-1,f.name(),BobFont.font_normal_16_outlined_smooth,BobColor.white,BobColor.clear,1.0f);
				onlineFriendCaptions.add(c);
			}


			int y = (onlineFriendCaptions.size()+1) * 20;
			Caption c = CaptionManager().newManagedCaption(Caption.CENTERED_X,y,-1,"Cancel",BobFont.font_normal_16_outlined_smooth,BobColor.white,BobColor.clear,1.0f);
			onlineFriendCaptions.add(c);

		}


		if(ControlsManager().BUTTON_UP_PRESSED)
		{
			multiplayerScreenCursorPosition--;
			if(multiplayerScreenCursorPosition<0)multiplayerScreenCursorPosition=onlineFriendCaptions.size()-1;
		}



		if(ControlsManager().BUTTON_DOWN_PRESSED)
		{
			multiplayerScreenCursorPosition++;
			if(multiplayerScreenCursorPosition>onlineFriendCaptions.size()-1)multiplayerScreenCursorPosition=0;
		}


		if(ControlsManager().BUTTON_ACTION_PRESSED)
		{


			showingMultiplayerScreen=false;

			if(multiplayerScreenCursorPosition==onlineFriendCaptions.size()-1)showingTitleScreen=true;
			else
			{

				FriendCharacter friend = onlineFriends.get(multiplayerScreenCursorPosition);
				this.setConnection(friend.connection);
				friend.setGameToForwardPacketsTo(this);
				this.friend = friend;

				showingWaitingForFriendScreen = true;
				setIncomingGameChallengeResponse(gameChallengeResponse_NONE);

			}

			if(onlineFriendCaptions!=null)
			{
				for(int i=0;i<onlineFriendCaptions.size();i++)
				{
					onlineFriendCaptions.get(i).deleteImmediately();
				}
			}

			onlineFriendCaptions = null;
			onlineFriends = null;
		}

		//TODO: adjust captions y to center to middle of screen

	}



	static public int gameChallengeResponse_NONE = 0;
	static public int gameChallengeResponse_ACCEPT = 1;
	static public int gameChallengeResponse_DECLINE = 2;


	private int _incomingGameChallengeResponse = gameChallengeResponse_NONE;
	public synchronized int getIncomingGameChallengeResponse(){return _incomingGameChallengeResponse;}
	public synchronized void setIncomingGameChallengeResponse(int s){_incomingGameChallengeResponse = s;}

	public long nonThreaded_SendGameChallengeRequestCounter = 0;
	public long nonThreaded_CheckForGameChallengeResponseCounter = 0;

	public long gameChallengeRequestSentTime = -1;

	//=========================================================================================================================
	private void updateWaitingForFriendScreen()
	{//=========================================================================================================================


		//we send the friendUDPConnection a "play game request"
		//it pops up a dialog
		//if they accept it, it opens their nD.
		//if they decline it or it times out we go back to the title screen

		long currentTime = System.currentTimeMillis();


		if(gameChallengeRequestSentTime==-1)
		{
			gameChallengeRequestSentTime = currentTime;
		}


		if(connection!=null)
		{
			if(connection.established())
			{
				if(currentTime-nonThreaded_SendGameChallengeRequestCounter>2000)
				{
					nonThreaded_SendGameChallengeRequestCounter=currentTime;

					//send "play game request"

					//log.debug("Game_Challenge_Request:bobsgame");
					connection.write(BobNet.Game_Challenge_Request+getGameName()+BobNet.endline);

				}
			}
		}


		if(waitingForFriendCaptions==null)
		{
			waitingForFriendCaptions = new ArrayList<Caption>();

			int y = (waitingForFriendCaptions.size()+1) * 20;
			Caption c = CaptionManager().newManagedCaption(Caption.CENTERED_X,y,-1,"Sending game request...",BobFont.font_normal_16_outlined_smooth,BobColor.white,BobColor.clear,1.0f);
			waitingForFriendCaptions.add(c);


			y = (waitingForFriendCaptions.size()+1) * 20;
			c = CaptionManager().newManagedCaption(Caption.CENTERED_X,y,-1,"Cancel",BobFont.font_normal_16_outlined_smooth,BobColor.white,BobColor.clear,1.0f);
			waitingForFriendCaptions.add(c);

		}



		if(ControlsManager().BUTTON_ACTION_PRESSED || currentTime-gameChallengeRequestSentTime>15000)
		{

			gameChallengeRequestSentTime = -1;

			if(!ControlsManager().BUTTON_ACTION_PRESSED)
			CaptionManager().newManagedCaption(Caption.CENTERED_SCREEN,0,3000,"Timed out.",BobFont.font_normal_16_outlined_smooth,BobColor.white,BobColor.clear,1.0f);


			if(waitingForFriendCaptions!=null)
			{
				for(int i=0;i<waitingForFriendCaptions.size();i++)
				{
					waitingForFriendCaptions.get(i).deleteImmediately();
				}
			}

			this.setConnection(null);
			this.friend = null;
			waitingForFriendCaptions = null;

			showingTitleScreen = true;
			showingWaitingForFriendScreen = false;
		}



		if(currentTime-nonThreaded_CheckForGameChallengeResponseCounter>300)
		{
			nonThreaded_CheckForGameChallengeResponseCounter=currentTime;

			//threaded game challenge response

			//if it is declined, go back to title screen
			//make temp caption for 5 seconds in middle of screen
			int response = getIncomingGameChallengeResponse();



			if(response!=gameChallengeResponse_NONE)
			{

				if(response==gameChallengeResponse_ACCEPT)
				{
					showingWaitingForFriendScreen = false;

					CaptionManager().newManagedCaption(Caption.CENTERED_SCREEN,0,5000,"Challenge Accepted!",BobFont.font_normal_16_outlined_smooth,BobColor.GREEN,BobColor.clear,1.0f);
				}


				if(response==gameChallengeResponse_DECLINE)
				{
					showingTitleScreen = true;
					showingWaitingForFriendScreen = false;

					CaptionManager().newManagedCaption(Caption.CENTERED_SCREEN,0,5000,"Challenge Declined",BobFont.font_normal_16_outlined_smooth,BobColor.RED,BobColor.clear,1.0f);

					this.setConnection(null);
					this.friend = null;
				}


				gameChallengeRequestSentTime = -1;

				setIncomingGameChallengeResponse(gameChallengeResponse_NONE);

				if(waitingForFriendCaptions!=null)
				{
					for(int i=0;i<waitingForFriendCaptions.size();i++)
					{
						waitingForFriendCaptions.get(i).deleteImmediately();
					}
				}

				waitingForFriendCaptions = null;

			}
		}
	}



	//=========================================================================================================================
	private void renderTitleScreen()
	{//=========================================================================================================================

		GLUtils.drawFilledRect(0,0,0,0,getWidth(),0,getHeight(),1.0f);

		//if(titleScreenTextures==null)return;

		//Texture t = titleScreenTextures[currentTitleScreenTextureFrame];
		Texture t = titleScreenTexture;

		if(t!=null)
		{

			float tx0 = 0;
			float tx1 = (float)t.getImageWidth() / (float)t.getTextureWidth();
			float ty0 = 0;
			float ty1 = (float)((float)t.getImageHeight()/(float)t.getTextureHeight());

			float ratio = (float)(getWidth()/2)/(float)t.getImageWidth();

			float sx0 = getWidth()/4;
			float sx1 = sx0+getWidth()/2;
			float sy0 = getHeight()/4;
			float sy1 = sy0+(float)(t.getImageHeight()*ratio);

			GLUtils.drawTexture(t, tx0,tx1,ty0,ty1, sx0,sx1,sy0,sy1, 1.0f, GLUtils.FILTER_NEAREST);

		}

		super.render();//captions



		t = cursorTexture;

		if(t!=null && singlePlayerCaption!=null)
		{

			float tx0 = 0;
			float tx1 = 1;
			float ty0 = 0;
			float ty1 = 1;

			float sx0 = singlePlayerCaption.screenX-16;
			if(cursorInOutToggle)sx0+=2;
			float sx1 = sx0+16;

			float sy0 = singlePlayerCaption.screenY+2;
			if(singlePlayerMultiPlayerSwitchToggle)sy0+=30;
			float sy1 = sy0+16;


			GLUtils.drawTexture(t, tx0,tx1,ty0,ty1, sx0,sx1,sy0,sy1, 1.0f, GLUtils.FILTER_NEAREST);

		}


	}


	//=========================================================================================================================
	private void renderMultiplayerScreen()
	{//=========================================================================================================================

		super.render();//captions

		Texture t = cursorTexture;

		if(t!=null && onlineFriendCaptions!=null)
		{

			float tx0 = 0;
			float tx1 = 1;

			float ty0 = 0;
			float ty1 = 1;


			float sx0 = onlineFriendCaptions.get(multiplayerScreenCursorPosition).screenX-16;
			if(cursorInOutToggle)sx0+=2;
			float sx1 = sx0+16;

			float sy0 = onlineFriendCaptions.get(multiplayerScreenCursorPosition).screenY+2;
			float sy1 = sy0+16;


			GLUtils.drawTexture(t, tx0,tx1,ty0,ty1, sx0,sx1,sy0,sy1, 1.0f, GLUtils.FILTER_NEAREST);

		}

	}

	//=========================================================================================================================
	private void renderWaitingForFriendScreen()
	{//=========================================================================================================================

		super.render();//captions

		Texture t = cursorTexture;

		if(t!=null && waitingForFriendCaptions!=null)
		{

			float tx0 = 0;
			float tx1 = 1;

			float ty0 = 0;
			float ty1 = 1;


			float sx0 = waitingForFriendCaptions.get(1).screenX-16;
			if(cursorInOutToggle)sx0+=2;
			float sx1 = sx0+16;

			float sy0 = waitingForFriendCaptions.get(1).screenY+2;
			float sy1 = sy0+16;


			GLUtils.drawTexture(t, tx0,tx1,ty0,ty1, sx0,sx1,sy0,sy1, 1.0f, GLUtils.FILTER_NEAREST);

		}

	}


	//=========================================================================================================================
	public boolean renderLoadScreens()
	{//=========================================================================================================================

		if(connection==null)
		{
			if(showingTitleScreen)
			{
				renderTitleScreen();
				return true;
			}

			if(showingMultiplayerScreen)
			{
				renderMultiplayerScreen();
				return true;
			}
		}

		if(showingWaitingForFriendScreen)
		{
			renderWaitingForFriendScreen();
			return true;
		}

		return false;
	}



}
