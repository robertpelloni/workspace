package com.bobsgame.client.console;


import com.bobsgame.shared.BobColor;

public class ConsoleText
{

	public String text;

	public int x=-1;
	public int y=-1;

	public int ticks = -1;

	public BobColor color = BobColor.white;

	public boolean isDebug = false;



	//=========================================================================================================================
	public ConsoleText(String s, BobColor c, int x, int y, int ticks, boolean isDebug)
	{//=========================================================================================================================

		this.text = s;
		if(c!=null)this.color=c;
		this.x=x;
		this.y=y;
		this.ticks=ticks;
		this.isDebug=isDebug;
	}



}
