package com.bobsgame.client.console;

import java.util.ArrayList;


import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.LWJGLUtils;
import com.bobsgame.client.state.State;
import com.bobsgame.net.BobNet;
import com.bobsgame.shared.BobColor;

//=========================================================================================================================
public class Console
{//=========================================================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(Console.class);

	static public ArrayList<ConsoleText> consoleTextList;





	//=========================================================================================================================
	public Console()
	{//=========================================================================================================================

		consoleTextList = new ArrayList<ConsoleText>();

	}


	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

		for(int i=0;i<consoleTextList.size();i++)
		{
			ConsoleText d = consoleTextList.get(i);
			if(d.ticks!=-1)
			{

				d.ticks-=State.mainTicksPassed;
				if(d.ticks<=0)
				{
					consoleTextList.remove(i);
					i--;
				}
			}

		}


	}


	//=========================================================================================================================
	static public ConsoleText error(String s)
	{//=========================================================================================================================

		return add(s,BobColor.red,-1,-1,-1,true);
	}

	//=========================================================================================================================
	static public ConsoleText error(String s, int ticks)
	{//=========================================================================================================================

		return add(s,BobColor.red,-1,-1,ticks,true);
	}

	//=========================================================================================================================
	static public ConsoleText error(String s, BobColor c)
	{//=========================================================================================================================

		return add(s,c,-1,-1,-1,true);
	}

	//=========================================================================================================================
	static public ConsoleText error(String s, BobColor c, int ticks)
	{//=========================================================================================================================

		return add(s,c,-1,-1,ticks,true);
	}

	//=========================================================================================================================
	static public ConsoleText error(String s, int x, int y)
	{//=========================================================================================================================

		return add(s,BobColor.red,x,y,-1,true);
	}

	//=========================================================================================================================
	static public ConsoleText error(String s, BobColor c, int x, int y)
	{//=========================================================================================================================

		return add(s,c,x,y,-1,true);
	}








	//=========================================================================================================================
	static public ConsoleText debug(String s)
	{//=========================================================================================================================

		ConsoleText d = add(s,null,-1,-1,-1,true);

		return d;
	}
	//=========================================================================================================================
	static public ConsoleText debug(String s, int ticks)
	{//=========================================================================================================================

		ConsoleText d = add(s,null,-1,-1,ticks,true);

		return d;
	}

	//=========================================================================================================================
	static public ConsoleText debug(String s, BobColor c)
	{//=========================================================================================================================

		ConsoleText d = add(s,c,-1,-1,-1,true);

		return d;
	}

	//=========================================================================================================================
	static public ConsoleText debug(String s, BobColor c, int ticks)
	{//=========================================================================================================================

		ConsoleText d = add(s,c,-1,-1,ticks,true);

		return d;
	}

	//=========================================================================================================================
	static public ConsoleText debug(String s, int x, int y)
	{//=========================================================================================================================

		ConsoleText d = add(s,null,x,y,-1,true);

		return d;
	}

	//=========================================================================================================================
	static public ConsoleText debug(String s, BobColor c, int x, int y)
	{//=========================================================================================================================

		ConsoleText d = add(s,c,x,y,-1,true);

		return d;
	}







	//=========================================================================================================================
	static public ConsoleText add(String s)
	{//=========================================================================================================================

		return add(s,null,-1,-1,-1, false);
	}

	//=========================================================================================================================
	static public ConsoleText add(String s, int ticks)
	{//=========================================================================================================================

		return add(s,null,-1,-1,ticks, false);
	}

	//=========================================================================================================================
	static public ConsoleText add(String s, BobColor c)
	{//=========================================================================================================================

		return add(s,c,-1,-1,-1, false);
	}

	//=========================================================================================================================
	static public ConsoleText add(String s, BobColor c, int ticks)
	{//=========================================================================================================================

		return add(s,c,-1,-1,ticks, false);
	}

	//=========================================================================================================================
	/** If x OR y is -1, it is centered on that axis. If both are -1, it is displayed in the console. */
	static public ConsoleText add(String s, int x, int y)
	{//=========================================================================================================================

		return add(s,null,x,y,-1, false);
	}

	//=========================================================================================================================
	/** If x OR y is -1, it is centered on that axis. If both are -1, it is displayed in the console. */
	static public ConsoleText add(String s, int x, int y, int ticks)
	{//=========================================================================================================================

		return add(s,null,x,y,ticks, false);
	}

	//=========================================================================================================================
	/** If x OR y is -1, it is centered on that axis. If both are -1, it is displayed in the console. */
	static public ConsoleText add(String s, BobColor c, int x, int y)
	{//=========================================================================================================================

		return add(s,c,x,y,-1, false);
	}

	//=========================================================================================================================
	/** If x OR y is -1, it is centered on that axis. If both are -1, it is displayed in the console. */
	static public ConsoleText add(String s, BobColor c, int x, int y, int ticks)
	{//=========================================================================================================================

		return add(s,c,x,y,ticks, false);
	}

	//=========================================================================================================================
	/** If x OR y is -1, it is centered on that axis. If both are -1, it is displayed in the console. */
	static public ConsoleText add(String s, BobColor c, int x, int y, int ticks, boolean isDebug)
	{//=========================================================================================================================

		ConsoleText dt = new ConsoleText(s,c,x,y,ticks,isDebug);
		consoleTextList.add(dt);
		return dt;

	}


	static boolean debugConsoleOff = true;

	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================


		//SlickCallable.enterSafeBlock();
		{
			//Color.white.bind();

			int numStrings = consoleTextList.size();

			int messagesCounter=0;

			for(int n=numStrings;n>0;n--)
			{

				ConsoleText dt = consoleTextList.get(n-1);

				if( (BobNet.debugMode==false || debugConsoleOff==true) && dt.isDebug==true )continue;


				if(dt.x!=-1 || dt.y!=-1)
				{

					int x = dt.x;
					int y = dt.y;

					if(x==-1)
					{
						//x=LWJGLUtils.SCREEN_SIZE_X/2;// make this get width of string to center it
						x = LWJGLUtils.SCREEN_SIZE_X/2-((GLUtils.font.getWidth(dt.text)+3)/2);
					}


					if(y==-1)
					{
						y = LWJGLUtils.SCREEN_SIZE_Y/2;
					}


					GLUtils.drawOutlinedString(x, y, dt.text, dt.color);

				}
				else
				{
					messagesCounter++;
					GLUtils.drawOutlinedString(8, LWJGLUtils.SCREEN_SIZE_Y-(12*messagesCounter), dt.text, dt.color);
				}
			}


			//Color.white.bind();
		}
		//SlickCallable.leaveSafeBlock();

	}

}
