package com.bobsgame.client.engine.game;

import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.entity.Sprite;
import com.bobsgame.client.engine.event.ServerObject;
import com.bobsgame.client.engine.text.Caption;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.MapData.RenderOrder;
import com.bobsgame.client.engine.text.BobFont;


//=========================================================================================================================
public class Item extends ServerObject
{//=========================================================================================================================


	Sprite sprite = null;

	String spriteAssetName = null;
	int spriteAssetID = -1;

	private boolean haveItemValue_S = false;
	private long timeSet = -1;

	//=========================================================================================================================
	public Item(Engine g, String spriteAssetName)
	{//=========================================================================================================================
		super(g);

		this.spriteAssetName = spriteAssetName;

		EventManager().itemList.add(this);
	}

	//=========================================================================================================================
	public Item(Engine g, int spriteAssetID)
	{//=========================================================================================================================
		super(g);

		this.spriteAssetID = spriteAssetID;

		EventManager().itemList.add(this);
	}

	//=========================================================================================================================
	public Item(Engine g, Sprite sprite)
	{//=========================================================================================================================
		super(g);

		this.sprite = sprite;
		this.spriteAssetName = sprite.name();
		this.spriteAssetID = sprite.id();

		setInitialized_S(true);

		EventManager().itemList.add(this);
	}



	//=========================================================================================================================
	public void sendServerRequest()
	{//=========================================================================================================================
		if(getInitialized_S() == false)
		{
			Sprite sprite = null;

			if(spriteAssetName!=null)sprite = SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist(spriteAssetName);
			if(spriteAssetID!=-1)sprite = SpriteManager().getSpriteAssetByIDOrRequestFromServerIfNotExist(spriteAssetID);

			if(sprite!=null)
			{
				this.sprite = sprite;
				setInitialized_S(true);
			}
		}
	}




	public String name(){return spriteAssetName;}
	public String description(){if(_initialized)return sprite.itemGameDescription(); else return "";}
	public int id(){return spriteAssetID;}





	//=========================================================================================================================
	public synchronized void getWithCaption_S()
	{//=========================================================================================================================

		setHaveItemValue_S(true);

		String name = "Got "+this.name()+"!";

		if(Player()!=null)
		{
			CaptionManager().newManagedCaption(Caption.CENTERED_OVER_ENTITY,0,5000,name,BobFont.font_normal_11_outlined,BobColor.GREEN,BobColor.CLEAR,RenderOrder.ABOVE_TOP,1.0f,0);
		}
		else
		{
			CaptionManager().newManagedCaption(Caption.CENTERED_SCREEN,0,5000,name,BobFont.font_normal_11_outlined,BobColor.GREEN,BobColor.CLEAR,RenderOrder.ABOVE_TOP,1.0f,0);
		}
		AudioManager().playSound("gotitem",0.25f,1.0f,1);

	}


	//=========================================================================================================================
	public synchronized void setHaveItemValue_S(boolean b)
	{//=========================================================================================================================
		timeSet = System.currentTimeMillis();

		if(b==true)Network().addQueuedGameSaveUpdateRequest_S("itemsHeld:`"+id()+":true:"+timeSet+"`");
		if(b==false)Network().addQueuedGameSaveUpdateRequest_S("itemsHeld:`"+id()+":false:"+timeSet+"`");

		haveItemValue_S = b;
	}

	//=========================================================================================================================
	public synchronized void initHaveItemValue_S(boolean b,long timeSet)
	{//=========================================================================================================================
		haveItemValue_S = b;
		this.timeSet = timeSet;
	}

	//=========================================================================================================================
	public synchronized boolean getHaveItemValue_S()
	{//=========================================================================================================================
		return haveItemValue_S;
	}

	//=========================================================================================================================
	public long getTimeSet()
	{//=========================================================================================================================
		return timeSet;
	}


}
