package com.bobsgame.client.engine.game;

import com.bobsgame.ClientMain;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.shared.BobColor;
//=========================================================================================================================
public class Clock extends EnginePart
{//=========================================================================================================================


	private boolean paused = false;
	private boolean unknown = false;
	private boolean fast = false;



	public int ticks=0;
	public int second=0;
	public int minute=0;
	public int hour=0;
	public int day=0;



	//=========================================================================================================================
	public Clock(Engine g)
	{//=========================================================================================================================

		super(g);
		ticks=0;
		second=0;
		minute=0;
		hour=0;
		day=0;

		//updateCaptions();

	}


	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		if(paused==false&&unknown==false&&TextManager().textEngineState==0)
		{


			ticks+=Engine().engineTicksPassed();

			if(ticks>=1000||(ticks>=1&&fast==true))
			{
				ticks-=1000;
				second++;//10 seconds per second (60 vbls)
			}

			if(second>=60)
			{
				second=0;
				minute+=1; //ten minutes per minute

				AudioManager().playSound("tick",0.25f,1.0f,1);
			}

			if(minute>=60) //six minutes per hour,one day is 6*24 = 120 = 2 hours.
			{
				minute=0;
				hour++;

				AudioManager().playSound("clockbeep",0.25f,1.0f,1);
			}

			if(hour>=24)
			{
				hour=0;
				day++;

				///mailman_came_today=0;
				///icecreamman_came_today=0;
				///jogger_came_today=0;
				///dogwalker_came_today=0;
			}

			if(day>=7 || day<0)
			{
				day=0;
			}
		}


//		if(last_clock_paused!=paused)
//		{
//			last_clock_paused=paused;
//			timeChanged=true;
//		}




		updateCaptions();

	}

	//=========================================================================================================================
	public void setTime(int day, int hour, int minute, int second)
	{//=========================================================================================================================



		if(hour>23)return;
		if(minute>59)return;
		if(second>59)return;

		this.day = day;
		this.hour = hour;
		this.minute = minute;
		this.second = second;

		//updateCaptions();
	}


	//=========================================================================================================================
	public void updateCaptions()
	{//=========================================================================================================================

		String clockString = "";
		String dayString = "";

		String minuteString = ""+minute;
		if(minute<10)minuteString = "0"+minute;


		switch(hour)
		{
			case 0:{clockString=" 12:"+minuteString+" AM "; break;}
			case 1:{clockString=" 01:"+minuteString+" AM "; break;}
			case 2:{clockString=" 02:"+minuteString+" AM "; break;}
			case 3:{clockString=" 03:"+minuteString+" AM "; break;}
			case 4:{clockString=" 04:"+minuteString+" AM "; break;}
			case 5:{clockString=" 05:"+minuteString+" AM "; break;}
			case 6:{clockString=" 06:"+minuteString+" AM "; break;}
			case 7:{clockString=" 07:"+minuteString+" AM "; break;}
			case 8:{clockString=" 08:"+minuteString+" AM "; break;}
			case 9:{clockString=" 09:"+minuteString+" AM "; break;}
			case 10:{clockString=" 10:"+minuteString+" AM "; break;}
			case 11:{clockString=" 11:"+minuteString+" AM "; break;}
			case 12:{clockString=" 12:"+minuteString+" PM "; break;}
			case 13:{clockString=" 01:"+minuteString+" PM "; break;}
			case 14:{clockString=" 02:"+minuteString+" PM "; break;}
			case 15:{clockString=" 03:"+minuteString+" PM "; break;}
			case 16:{clockString=" 04:"+minuteString+" PM "; break;}
			case 17:{clockString=" 05:"+minuteString+" PM "; break;}
			case 18:{clockString=" 06:"+minuteString+" PM "; break;}
			case 19:{clockString=" 07:"+minuteString+" PM "; break;}
			case 20:{clockString=" 08:"+minuteString+" PM "; break;}
			case 21:{clockString=" 09:"+minuteString+" PM "; break;}
			case 22:{clockString=" 10:"+minuteString+" PM "; break;}
			case 23:{clockString=" 11:"+minuteString+" PM "; break;}
			default:{break;}
		}



		switch(day)
		{
			case 0:{dayString=" Sunday "; break;}
			case 1:{dayString=" Monday "; break;}
			case 2:{dayString=" Tuesday "; break;}
			case 3:{dayString=" Wednesday "; break;}
			case 4:{dayString=" Thursday "; break;}
			case 5:{dayString=" Friday "; break;}
			case 6:{dayString=" Saturday "; break;}
			default:{break;}
		}


		if(unknown)
		{
			clockString = " ??:?? ";
			dayString=" ?????? ";
		}

		if(StatusBar().clockCaption!=null)StatusBar().clockCaption.updateCaption(clockString);
		if(StatusBar().dayCaption!=null)StatusBar().dayCaption.updateCaption(dayString);

		if(ClientMain.introMode)//TODO terrible hack
		{
			if(StatusBar().clockCaption!=null)StatusBar().clockCaption.setColors(BobColor.green,BobColor.darkGreen,BobColor.clear);
		}

	}



	//=========================================================================================================================
	public void setPaused(boolean b)
	{//=========================================================================================================================
		if(b==true)setPausedOn();
		if(b==false)setPausedOff();
	}

	//=========================================================================================================================
	public void setPausedOn()
	{//=========================================================================================================================
		paused=true;
		StatusBar().clockCaption.setPausedColor();
	}
	//=========================================================================================================================
	public void setPausedOff()
	{//=========================================================================================================================
		paused=false;
		if(unknown)StatusBar().clockCaption.setUnknownColor();
		else if(paused)StatusBar().clockCaption.setPausedColor();
		else if(fast)StatusBar().clockCaption.setFastColor();
		else StatusBar().clockCaption.setDefaultColor();
	}



	//=========================================================================================================================
	public void setUnknown(boolean b)
	{//=========================================================================================================================
		if(b==true)setUnknownOn();
		if(b==false)setUnknownOff();
	}
	//=========================================================================================================================
	public void setUnknownOn()
	{//=========================================================================================================================
		unknown=true;
		StatusBar().clockCaption.setUnknownColor();
	}
	//=========================================================================================================================
	public void setUnknownOff()
	{//=========================================================================================================================
		unknown=false;
		if(unknown)StatusBar().clockCaption.setUnknownColor();
		else if(paused)StatusBar().clockCaption.setPausedColor();
		else if(fast)StatusBar().clockCaption.setFastColor();
		else StatusBar().clockCaption.setDefaultColor();
	}



	//=========================================================================================================================
	public void setFast(boolean b)
	{//=========================================================================================================================
		if(b==true)setFastOn();
		if(b==false)setFastOff();
	}
	//=========================================================================================================================
	public void setFastOn()
	{//=========================================================================================================================
		fast=true;
		StatusBar().clockCaption.setFastColor();
	}
	//=========================================================================================================================
	public void setFastOff()
	{//=========================================================================================================================
		fast=false;
		if(unknown)StatusBar().clockCaption.setUnknownColor();
		else if(paused)StatusBar().clockCaption.setPausedColor();
		else if(fast)StatusBar().clockCaption.setFastColor();
		else StatusBar().clockCaption.setDefaultColor();
	}







}
