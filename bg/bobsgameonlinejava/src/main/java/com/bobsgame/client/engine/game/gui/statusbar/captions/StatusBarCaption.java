package com.bobsgame.client.engine.game.gui.statusbar.captions;

import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.client.engine.map.Light;
import com.bobsgame.client.engine.text.Caption;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.MapData;
import com.bobsgame.shared.MapData.RenderOrder;
import com.bobsgame.client.engine.text.BobFont;

//=========================================================================================================================
public class StatusBarCaption extends EnginePart
{//=========================================================================================================================


	public Caption caption=null;
	public Light light = null;



	BobColor defaultFGColor = BobColor.WHITE;
	BobColor defaultAAColor = BobColor.DARKERGRAY;
	BobColor defaultBGColor = BobColor.CLEAR;


	BobColor currentFGColor = defaultFGColor;
	BobColor currentAAColor = defaultAAColor;
	BobColor currentBGColor = defaultBGColor;




	public boolean enabled = true;




	//=========================================================================================================================
	public StatusBarCaption(ClientGameEngine g)
	{//=========================================================================================================================
		super(g);
	}



	//=========================================================================================================================
	public void setEnabled(boolean b)
	{//=========================================================================================================================
		enabled = b;
	}



	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================


	}



	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

	}


	//=========================================================================================================================
	public void render(int layer)
	{//=========================================================================================================================


		if(enabled==false)return;

		if(layer==0)
		{
			if(caption!=null)caption.render();
			if(light!=null)light.renderLight();
		}
	}


	//=========================================================================================================================
	public void updateCaption(String s)
	{//=========================================================================================================================

		if(caption==null)
		{
			caption=new Caption(Engine(),0,2,-1,s,BobFont.font_small_16_outlined_smooth,currentFGColor,currentAAColor,currentBGColor,RenderOrder.OVER_TEXT,1.0f,0);
		}
		else
		if(s.compareTo(caption.text)!=0)
		{
			caption.replaceText(s);
		}

	}


	//=========================================================================================================================
	public void setColors(BobColor fg, BobColor aa, BobColor bg)
	{//=========================================================================================================================

		currentFGColor = fg;
		currentAAColor = aa;
		currentBGColor = bg;


		if(caption!=null)
		{
			caption.setTextColor(fg,aa,bg);
		}

	}


	//=========================================================================================================================
	public void setDefaultColor()
	{//=========================================================================================================================
		setColors(defaultFGColor,defaultAAColor,defaultBGColor);
	}

}
