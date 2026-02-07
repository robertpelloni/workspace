package com.bobsgame.client.engine.game.nd.ndmenu.wheelitem;

import com.bobsgame.client.Texture;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.game.nd.NDGameEngine;
import com.bobsgame.client.engine.game.nd.ndmenu.Wheel;
import com.bobsgame.client.engine.text.Caption;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.MapData.RenderOrder;
import com.bobsgame.client.engine.text.BobFont;


//=========================================================================================================================
public class WheelItem extends EnginePart
{//=========================================================================================================================


	public static Texture wheelItemBackgroundTexture;
	public static Texture wheelItemGlossyOverlayTexture;

	public static int firstCartY = 0;//((SCREEN_SIZE_Y/2)-(wheelItemHeight/2));

	public static int wheelItemHeight=38;//40;//37;//48;//cart_SURFACE->h; //size of cart image
	public static int wheelItemLabelOffsetX=6/2;//where the label "container" starts inside the cart png
	public static int wheelItemLabelOffsetY=6/2;//13;//where the label "container" starts inside the cart png







	public float x=0;
	public float y=0;

	//public Texture labelTexture = null;
	//public Texture labelGlowTexture = null;

	public int slot = 0;
	public String name = "";

	public NDGameEngine game;

	public BobColor color = BobColor.black;


	public Caption caption;




	//=========================================================================================================================
	public WheelItem(Engine g, NDGameEngine game, String name, BobColor color)
	{//=========================================================================================================================
		super(g);

		this.game = game;
		this.name = name;
		this.color = color;

		this.caption = new Caption(g,0,0,-1,name,BobFont.font_normal_16_outlined_smooth,color,null,new BobColor(0,0,0,0),RenderOrder.ABOVE_TOP,1.0f,0);
		this.caption.setAlphaImmediately(1.0f);

		y=firstCartY+(Wheel.wheelItems.size()-1)*wheelItemHeight;
		slot=Wheel.wheelItems.size()-1;

	}



	//=========================================================================================================================
	public float top()
	{//=========================================================================================================================
		return y;
	}
	//=========================================================================================================================
	public float middleY()
	{//=========================================================================================================================
		return y+wheelItemHeight/2.0f;
	}
	//=========================================================================================================================
	public float bottom()
	{//=========================================================================================================================
		return y+wheelItemHeight;
	}
	//=========================================================================================================================
	public void render(boolean isSelected)
	{//=========================================================================================================================
		//------------------------------------------
		//draw item background graphic
		//------------------------------------------
		GLUtils.drawTexture(wheelItemBackgroundTexture,x,y,1.0f,GLUtils.FILTER_LINEAR);


		//------------------------------------------
		//draw wheel item label
		//------------------------------------------

		float labelX = x+wheelItemLabelOffsetX;
		float labelY = y+wheelItemLabelOffsetY;

		//NDGame.drawTexture(labelTexture,labelX,labelY);

		if(caption!=null)
		{

			caption.screenX = x+40/2;
			caption.screenY = y+20/2;
			caption.render();
		}

		//------------------------------------------
		//draw shiny overlay
		//------------------------------------------


		if(isSelected)
		{
			//if(selectedWheelItem==1)NDGame.drawTextureAlpha(labelGlowTexture,labelX,labelY,1.0f-(float)(highlightColor/255.0f));

			GLUtils.drawTexture(wheelItemGlossyOverlayTexture,labelX,labelY,Wheel.highlightColor,GLUtils.FILTER_LINEAR);
		}
		else
		{
			GLUtils.drawTexture(wheelItemGlossyOverlayTexture,labelX,labelY,1.0f,GLUtils.FILTER_LINEAR);
		}


	}
}