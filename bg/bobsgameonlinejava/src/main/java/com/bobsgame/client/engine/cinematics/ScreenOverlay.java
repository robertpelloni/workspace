package com.bobsgame.client.engine.cinematics;
import com.bobsgame.client.LWJGLUtils;

import static org.lwjgl.opengl.GL11.glTexImage2D;



import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.shared.BobColor;

import easing.Easing;


// support color
// support better speed function

//TODO: support fading out specific layers, over/under player, textbox, etc

//TODO: need getters and setters

//TODO: need to know whether to fade in/out or instant on/off


//=========================================================================================================================
public class ScreenOverlay extends EnginePart
{//=========================================================================================================================
	//screen fadeout




	public BobColor color = BobColor.black;





	private float startAlpha=0.0f;
	private float alpha=0.0f;
	private float toAlpha = 0.0f;


	private long startTime=System.currentTimeMillis();
	private long durationTicks=0;


	//0 = one way , 1 = two-way
	private int transitionType = 0;



	private final int TYPE_ONE_WAY = 0;
	private final int TYPE_ROUNDTRIP = 1;
	private final int TYPE_INSTANT = 2;


	//=========================================================================================================================
	/**
	 * fade screen in or out to a Slick BobColor, taking in speed.
	 * speed should be low, 0.0f01f * ticks(16) = 0.0f16f* 60 fps = 0.96 seconds to full opacity.
	 */
	public ScreenOverlay(Engine g)
	{//=========================================================================================================================
		super(g);

	}

	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================

	}


	//=========================================================================================================================
	public void doTransition(BobColor color,float fromAlpha,float toAlpha,int ticks)
	{//=========================================================================================================================

		this.color = color;

		this.startTime = System.currentTimeMillis();

		if(fromAlpha!=-1)this.startAlpha = fromAlpha;
		else startAlpha = alpha;

		this.alpha = startAlpha;

		this.toAlpha = toAlpha;

		this.durationTicks = ticks;

		this.transitionType = TYPE_ONE_WAY;

	}


	//=========================================================================================================================
	public void doToAndFromTransition(BobColor color,int ticks, float toAlpha)
	{//=========================================================================================================================


		this.color = color;

		this.startTime = System.currentTimeMillis();


		this.alpha = 0;
		this.toAlpha = toAlpha;

		this.durationTicks = ticks;


		this.transitionType = TYPE_ROUNDTRIP;

	}
	//=========================================================================================================================
	public void setInstantOverlay(BobColor color, float alpha)
	{//=========================================================================================================================

		this.color = color;

		this.startTime = System.currentTimeMillis();


		this.alpha = alpha;
		this.toAlpha = alpha;

		this.durationTicks = 0;


		this.transitionType = TYPE_INSTANT;

	}

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

		float ticksPassed = (System.currentTimeMillis() - startTime)*Engine().engineSpeed;


		if(transitionType==TYPE_ONE_WAY)
		{
			if(ticksPassed<durationTicks)
			{
				alpha = (float)Easing.easeInOutQuadratic(ticksPassed,startAlpha,toAlpha-startAlpha,durationTicks);
			}
			else
			{
				alpha=toAlpha;
				//toAlpha=0;
				//startAlpha=0;
				//durationTicks=0;

			}
		}
		else
		if(transitionType==TYPE_ROUNDTRIP)
		{
			if(ticksPassed<durationTicks/2)
			{
				alpha = (float)Easing.easeInOutQuadratic(ticksPassed,0,toAlpha,durationTicks);
			}
			else
			if(ticksPassed<durationTicks)
			{
				alpha = (float)Easing.easeInOutQuadratic(ticksPassed,toAlpha,0,durationTicks);
			}
			else
			{
				alpha=0;
			}

		}
		else
		if(transitionType==TYPE_INSTANT)
		{
			alpha = toAlpha;

		}



	}
	//=========================================================================================================================
	public void clearOverlays()
	{//=========================================================================================================================
		alpha = 0;
		toAlpha = 0;
		transitionType = TYPE_INSTANT;
		color = BobColor.black;

	}


	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================
		GLUtils.drawFilledRect(color.getRed(),color.getGreen(),color.getBlue(), 0, LWJGLUtils.SCREEN_SIZE_X, 0, LWJGLUtils.SCREEN_SIZE_Y, alpha);
	}





}
