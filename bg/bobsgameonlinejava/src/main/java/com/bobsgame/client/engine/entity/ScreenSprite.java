package com.bobsgame.client.engine.entity;

import com.bobsgame.client.Texture;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.shared.EntityData;
import com.bobsgame.shared.MapData.RenderOrder;
//=========================================================================================================================
public class ScreenSprite extends Entity
{//=========================================================================================================================


	public float screenXPixelsHQ = 0;
	public float screenYPixelsHQ = 0;


	public boolean useXPercent = false;
	public boolean useYPercent = false;

	public float screenXPercent = 0;
	public float screenYPercent = 0;

	public boolean centerX = false;
	public boolean centerY = false;


	//=========================================================================================================================
	public ScreenSprite(Engine g, String name, String spriteName)
	{//=========================================================================================================================

		super(g);

		init(new EntityData(-1,name,spriteName,0,0), null);

		setRenderOrder(RenderOrder.OVER_TEXT);

		SpriteManager().screenSpriteList.add(this);
	}



	//=========================================================================================================================
	public float screenLeft()
	{//=========================================================================================================================

		if(centerX)return Engine().getWidth()/2-w()/2;

		if(useXPercent)return (float)((Engine().getWidth()*screenXPercent));

		return screenXPixelsHQ;
	}


	//=========================================================================================================================
	public float screenTop()
	{//=========================================================================================================================
		if(centerY)return Engine().getHeight()/2-w()/2;

		if(useYPercent)return (float)((Engine().getHeight()*screenYPercent));

		return screenYPixelsHQ;
	}


	public void setX(float x)
	{
		useXPercent = false;
		screenXPixelsHQ = x;
	}


	public void setY(float y)
	{
		useYPercent = false;
		screenYPixelsHQ = y;
	}

	public void setXPercent(float x)
	{
		useXPercent = true;
		screenXPixelsHQ = x;
		if(x==-1)centerX = true;
	}


	public void setYPercent(float y)
	{
		useYPercent = true;
		screenYPixelsHQ = y;
		if(y==-1)centerY = true;
	}

	//=========================================================================================================================
	public void checkIfOnscreen()
	{//=========================================================================================================================
		//don't do anything, manually control draw
	}


	//=========================================================================================================================
	public boolean shouldDraw()
	{//=========================================================================================================================
		//checkIfOnscreen();

		if(draw==true)return true;
		else return false;
	}

	//=========================================================================================================================
	public void delete()
	{//=========================================================================================================================
		if(SpriteManager().screenSpriteList.contains(this))SpriteManager().screenSpriteList.remove(this);

	}

	//=========================================================================================================================
	public void render(float alpha, Texture texture, Texture shadowTexture)
	{//=========================================================================================================================


		float tx0 = 0.0f;
		float tx1 = 1.0f;
		float ty0 = 0.0f;
		float ty1 = 1.0f;

		float x0 = 0;
		float x1 = 0;
		float y0 = 0;
		float y1 = 0;



		//------------------
		//now draw actual sprite
		//------------------
		if(texture!=null)
		{

			tx0 = 0.0f;
			tx1 = ((float)w()/(float)texture.getTextureWidth());
			ty0 = (((float)h())*getFrame())/(float)texture.getTextureHeight();
			ty1 = (((float)h())*(getFrame()+1))/(float)texture.getTextureHeight();


			//x0 = (float)Math.floor(screenLeft());
			//x1 = (float)Math.floor(screenRight());
			//y0 = (float)Math.floor(screenTop());
			//y1 = (float)Math.floor(screenBottom());


			x0 = screenLeft();
			y0 = screenTop();
			x1 = (float) (x0+w());
			y1 = (float) (y0+h());


			GLUtils.drawTexture(texture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,alpha,GLUtils.FILTER_NEAREST);

		}




	}


}
