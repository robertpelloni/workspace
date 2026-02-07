package com.bobsgame.client.engine.game;

import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.game.gui.statusbar.StatusBar;


//=========================================================================================================================
public class Wallet extends EnginePart
{//=========================================================================================================================


	public float money = 19.99f;

	public float lastMoney = -1;


	//=========================================================================================================================
	public Wallet(ClientGameEngine g)
	{//=========================================================================================================================
		super(g);

	}

	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================


	}


	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		//TODO: use BigDecimal or that blog post on matthias blog about money types

		String moneyString = "";



		if(lastMoney!=money)
		{
			lastMoney = money;

			moneyString = ""+Float.toString(money);
			if(moneyString.indexOf('.')!=-1)
			{
				if(moneyString.indexOf('.')<(moneyString.length()-1)-2)
				{
					moneyString = moneyString.substring(0, moneyString.indexOf('.')+2);
				}
				else
				if(moneyString.indexOf('.')>(moneyString.length()-1)-2)
				{
					if(moneyString.indexOf('.')==(moneyString.length()-1)-0)moneyString = moneyString.concat("00");
					else if(moneyString.indexOf('.')==(moneyString.length()-1)-1)moneyString = moneyString.concat("0");
				}
			}
			else
			{
				moneyString = moneyString.concat(".0f0");
			}

			moneyString = " $"+moneyString+" ";


			StatusBar().moneyCaption.updateCaption(moneyString);
		}

	}




}
