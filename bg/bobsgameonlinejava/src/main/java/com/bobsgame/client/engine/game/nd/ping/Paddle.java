package com.bobsgame.client.engine.game.nd.ping;


import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;


//=========================================================================================================================
public class Paddle extends EnginePart
{//=========================================================================================================================

	public static int h = 32;
	public static int w = 8;

	//Texture texture;

	float x;
	float y;

	//float speed;

	boolean selected = false;

	//=========================================================================================================================
	public Paddle(Engine g)
	{//=========================================================================================================================
		super(g);
	}


	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

	}


	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================

		if(selected)GLUtils.drawFilledRectXYWH(x,y,w,h,0.0f,1.0f,0.0f,1.0f);
		else GLUtils.drawFilledRectXYWH(x,y,w,h,1.0f,1.0f,1.0f,1.0f);

	}


	public float left()
	{
		return x;
	}

	public float right()
	{
		return x+w;
	}

	public float top()
	{
		return y;
	}

	public float bottom()
	{
		return y+h;
	}

	public float middleX()
	{
		return x+w/2;
	}

	public float middleY()
	{
		return y+h/2;
	}




}
