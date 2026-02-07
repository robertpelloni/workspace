package com.bobsgame.client.engine.text;



import static org.lwjgl.opengl.GL11.glTexImage2D;

//import java.awt.Font;

import java.io.InputStream;

import org.slf4j.LoggerFactory;

import com.bobsgame.client.Texture;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.console.Console;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.entity.Entity;
import com.bobsgame.client.engine.entity.ScreenSprite;
import com.bobsgame.client.engine.entity.Sprite;
import com.bobsgame.client.engine.event.Dialogue;
import com.bobsgame.client.engine.text.BobFont.BitmapFont;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.Utils;


//=========================================================================================================================
public class TextManager extends EnginePart
{// =========================================================================================================================


	public static Logger log=(Logger)LoggerFactory.getLogger(TextManager.class);

	public static com.bobsgame.client.BitmapFont ttfFont;


	static public String debugtext1;
	static public String debugtext2;
	static public String debugtext3;
	static public String debugtext4;



	private boolean antiAlias=true;


	public TextWindow textBox[]={null,null};

	BobFont fonts=new BobFont();


	public int width=64*6*2; // *2 because we draw everything at 2x to allow for scaling (and higher res 1x unicode fonts)
	public int height=64*2;

	int pow2TexWidth;
	int pow2TexHeight;

	public int spriteWindowWidth=64*2;

	// public int line_size_x=size_x/2; //because the text box is drawn at 2x (so the texture scales nicely if i zoom it in or out)

	public int MAX_LINES=4;



	public String currentText=null;
	public int length=0;
	public int position=0;



	public int CLOSED=0;
	public int OPEN=1;
	public int CLOSING=2;
	public int ANSWER_BOX_ON=3;
	public int ANSWER_BOX_CLOSING=4;
	public int KEYBOARD_CLOSING=5;
	public int KEYBOARD_ON=6;

	public int textEngineState=CLOSED;


	public int BOTTOM=0;
	public int TOP=1;

	public int selectedTextbox=BOTTOM;

	public boolean topBoxActivated=false;



	public boolean keepOpenForNewText=false;
	public boolean waitingForButtonForNewPage=false;
	public boolean pausedUntilButtonPress=false;
	public boolean waitingForCancelButtonUnpress=false;
	public boolean cannotCancel=false;
	public boolean waitingForButtonPressToClose=false;
	public boolean waitingForUnpress=false;
	public boolean buttonAUnpressed=false;
	public boolean buttonIconIsOn=false;
	public boolean scrollingUp=false;



	public boolean delay=false;
	public int delayTicks=0;


	public BitmapFont font=null;// this isn't per-text window because we want to share the state across the boxes. is that right, or would per-box be better?
	public BobColor textColor=BobColor.WHITE;
	public BobColor textBGColor=BobColor.BLACK;
	public BobColor textAAColor=BobColor.GRAY;
	public BobColor textShadowColor=BobColor.DARKGRAY;



	public boolean skipText=false;



	public boolean buttonIconUpDownToggle=false;
	public int buttonTimer=0;
	public Texture buttonTexture;
	// TODO: load button texture, draw where appropriate during render


	public int MAX_ANSWER_LENGTH=255;



	public Entity optionTargetEntity1=null;
	public Entity optionTargetEntity2=null;
	public Entity optionTargetEntity3=null;
	public Entity optionTargetEntity4=null;
	public Entity optionTargetEntity5=null;
	public Entity optionTargetEntity6=null;


	public int cursorTicks=0;
	public boolean cursorPixelUpDownToggle=true;
	public float answerBoxY=0;
	public int numberOfAnswers=0;
	public int selectedAnswer=0;

	public ScreenSprite cursorScreenSprite=null;
	public float keyboardY=0;
	public ScreenSprite keyboardScreenSprite=null;
	public ScreenSprite actionIconScreenSprite=null;
	public String optionBuffer;


	//public float BOTTOM_ACTIVE_POSITION_Y=5000;
	//public float BOTTOM_INACTIVE_POSITION_Y=5000;
	//public float TOP_ACTIVE_POSITION_Y=5000;
	//public float TOP_INACTIVE_POSITION_Y=5000;
	//public float POSITION_X=5000;

	public static Texture questionMarkTexture=null;



	//public long textEngineSpeedTicksPerLetter=10;
	//public long drawLetterTicksCounter=100;


	// =========================================================================================================================
	public TextManager(Engine g)
	{// =========================================================================================================================
		super(g);


		if(actionIconScreenSprite==null)
		{
			actionIconScreenSprite = new ScreenSprite(g,"button", "actionIcon");//HARDWARE_create_sprite(TEXT_button_icon_GFX,0,1,1.0f,actionx-8,actiony+1,255);
			actionIconScreenSprite.draw=false;

			actionIconScreenSprite.setAnimateLoopThroughAllFrames();
			actionIconScreenSprite.setRandomUpToTicksBetweenAnimationLoop(false);
			actionIconScreenSprite.setTicksBetweenFrames(60);
			actionIconScreenSprite.setTicksBetweenAnimationLoop(0);
		}

	}


	// =========================================================================================================================
	public boolean isTextBoxOpen()
	{// =========================================================================================================================

		if(textEngineState!=0) return true;

		return false;
	}



	// =========================================================================================================================
	public boolean isTextAnswerBoxOpen()
	{// =========================================================================================================================

		if(textEngineState>2) return true;

		return false;
	}



	// =========================================================================================================================
	public void init()
	{// =========================================================================================================================

		/*
		 * // load a default java font
		 * try
		 * {
		 * Font awtFont = new Font("bobsgame", Font.PLAIN, 8);
		 * font = new TrueTypeFont(awtFont, antiAlias);
		 * }
		 * catch (Exception e)
		 * {
		 * e.printStackTrace();
		 * }
		 */

		// load font from file
		try
		{
			ttfFont = new com.bobsgame.client.BitmapFont("res/fonts/bobsgame.ttf", 8f);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}

		if(questionMarkTexture==null) questionMarkTexture=GLUtils.loadTexture("res/textbox/questionmark.png");


		//width = (int)((Engine().getWidth()*0.66f)/(64*2))*(64*2);

		pow2TexWidth=Utils.getClosestPowerOfTwo(width);
		pow2TexHeight=Utils.getClosestPowerOfTwo(height);

		textBox[0]=new TextWindow(Engine());
		textBox[1]=new TextWindow(Engine());

		textBox[0].init();
		textBox[1].init();

	}


	// =========================================================================================================================
	public void reset()
	{// =========================================================================================================================


		font=BobFont.font_normal_16;

		textBGColor=BobColor.BLACK;
		textColor=BobColor.WHITE;
		textAAColor=BobColor.GRAY;
		textShadowColor=BobColor.DARKGRAY;

		selectedTextbox=BOTTOM;
		topBoxActivated=false;
		delay=false;


		waitingForCancelButtonUnpress=false;
		ActionManager().deleteCaptionWithBlipSound();

		textBox[0].scrollPercent=0;
		textBox[1].scrollPercent=0;

		textBox[0].setSpriteWindow(Cameraman().targetEntity,null,"");
		textBox[1].setSpriteWindow(Cameraman().targetEntity,questionMarkTexture,"???");


		int i=0;
		for(i=0;i<2;i++)
		{
			textBox[i].clearByteArray();

			textBox[i].line=0;
			textBox[i].xInLine=0;

			textBox[i].redraw=true;
		}
	}



	// =========================================================================================================================
	public void text(String s)
	{// =========================================================================================================================
		if(currentText==null)
		{
			length=s.length();
			currentText=s;
			update();
		}
		else
		{
			// TODO: error, this should never happen, but i could handle it gracefully somehow.
		}
	}


	// =========================================================================================================================
	public void render()
	{// =========================================================================================================================

		if(textEngineState!=CLOSED)
		{
			if(textBox[0]!=null) textBox[0].render();
			if(textBox[1]!=null) textBox[1].render();
		}



	}


	// =========================================================================================================================
	public int getLineSizeX()
	{// =========================================================================================================================
		// check font. if height is greater than 12, we aren't drawing at 2x, so return full length.

		int h=TextManager().font.maxCharHeight;

		boolean draw2X=true;

		if(h>12) draw2X=false;

		// otherwise we are drawing at floatsize, so return half length.

		if(draw2X==true) return width/2;
		else return width;

	}



	// =========================================================================================================================
	public void update()
	{// =========================================================================================================================


		//BOTTOM_ACTIVE_POSITION_Y=((Engine().getHeight()-textWindowHeight)-16)-16;
		//BOTTOM_INACTIVE_POSITION_Y=Engine().getHeight()+16;
		//TOP_ACTIVE_POSITION_Y=((0+16)+16+24);
		//TOP_INACTIVE_POSITION_Y=((0-textWindowHeight)-16);
		//POSITION_X=((Engine().getWidth()-(textWindowWidth+spriteWindowWidth))/2)+spriteWindowWidth;



		//drawLetterTicksCounter+=Engine().engineTicksPassed();

		//while(drawLetterTicksCounter>=textEngineSpeedTicksPerLetter)
		{
			//drawLetterTicksCounter-=textEngineSpeedTicksPerLetter;

			// -----------------------------
			// if there's new text
			// -----------------------------
			if(currentText!=null)
			{
				// -----------------------------
				// if it's the beginning of the text
				// -----------------------------
				if(position==0)
				{
					// -----------------------------
					// if the text window is offscreen
					// -----------------------------
					if(textEngineState==CLOSED)
					{
						// -----------------------------
						// and it's not paused, start the text engine
						// -----------------------------

						reset();

						// zoom the camera to the talking NPC
						Cameraman().setTarget(textBox[0].spriteWindowEntity);
						Cameraman().setTicksPerPixelMoved(Cameraman().ticksPerPixel_CAMERA_CONVERSATION);
						Cameraman().ignoreCameraFXBoundaries=true;// avoid camera boundaries

						AudioManager().playSound("blah",0.5f,textBox[selectedTextbox].voicePitch+Utils.randLessThanFloat(2.0f),1);

						scrollingUp=true;// wait for the text box to scroll up before drawing text in it.

						textEngineState=OPEN;// text box is open


					}

					if(textEngineState==OPEN)
					{
						// -----------------------------
						// if it's set to stay open, draw the text into it
						// (this is for sending another text string into an already-open text box.)
						// -----------------------------
						if(keepOpenForNewText==true)
						{
							keepOpenForNewText=false;

							// start a new line of text.
							textBox[selectedTextbox].xInLine=0;
							textBox[selectedTextbox].line++;

							if(textBox[selectedTextbox].line>MAX_LINES)
							{
								waitingForButtonForNewPage=true;
							}
						}
					}
				}

				if(textEngineState==OPEN)
				{
					// -----------------------------
					// parse options (even if the text box is paused)
					// -----------------------------
					if(position<length)
					{
						while(position<length
								&&
								currentText.charAt(position)=='<'
								&&
								waitingForButtonForNewPage==false
								&&
								pausedUntilButtonPress==false)
						{
							parseOption();
							position++;
						}
					}

					// -----------------------------
					// draw text
					// -----------------------------
					if(scrollingUp==false&&delay==false)
					{
						drawText();
						handleInput();
					}
				}

				// TODO: what if there's text, it isn't at the beginning of the text, and the text box is closed?
				// this should never happen, but what if it does?

			}

			doScrolling();

			textBox[0].updateTextureFromByteArray();
			textBox[1].updateTextureFromByteArray();
		}


		actionIconScreenSprite.draw = buttonIconIsOn;

	}


	BobColor tC0=textBGColor;
	BobColor tC1=textColor;
	BobColor tC2=textAAColor;
	BobColor tC3=textShadowColor;


	// =========================================================================================================================
	public void drawText()
	{// =========================================================================================================================

		// -----------------------------
		// draw text
		// -----------------------------
		if(position<length&&waitingForButtonForNewPage==false&&pausedUntilButtonPress==false)
		{



			// automatically colorize "Yuu"

				if(position<length-2&&currentText.substring(position).startsWith("Yuu"))
				{

					tC0=textBGColor;
					tC1=textColor;
					tC2=textAAColor;
					tC3=textShadowColor;

					textColor=BobColor.PURPLE;
					if(textBGColor==BobColor.BLACK) textAAColor=BobColor.DARKPURPLE;
					else textAAColor=BobColor.LIGHTPURPLE;
					if(textBGColor==BobColor.BLACK) textShadowColor=BobColor.DARKERPURPLE;
					else textShadowColor=BobColor.LIGHTPURPLE;
				}

			//"bob's game"
				else
				if(position<length-11&&currentText.substring(position).startsWith("\"bob's game\""))
				{

					tC0=textBGColor;
					tC1=textColor;
					tC2=textAAColor;
					tC3=textShadowColor;

					textColor=BobColor.GREEN;
					if(textBGColor==BobColor.BLACK) textAAColor=BobColor.DARKGREEN;
					else textAAColor=BobColor.LIGHTGREEN;

					if(textBGColor==BobColor.BLACK) textShadowColor=BobColor.DARKERGREEN;
					else textShadowColor=BobColor.LIGHTGREEN;
				}
				else
				if(position<length-9&&currentText.substring(position).startsWith("bob's game") && (position>=length-10||currentText.substring(position).startsWith("bob's game\"")==false))
				{

					tC0=textBGColor;
					tC1=textColor;
					tC2=textAAColor;
					tC3=textShadowColor;

					textColor=BobColor.GREEN;
					if(textBGColor==BobColor.BLACK) textAAColor=BobColor.DARKGREEN;
					else textAAColor=BobColor.LIGHTGREEN;

					if(textBGColor==BobColor.BLACK) textShadowColor=BobColor.DARKERGREEN;
					else textShadowColor=BobColor.LIGHTGREEN;
				}
				else//bob's
				if(position<length-4&&currentText.substring(position).startsWith("bob's") && (position>=length-9||currentText.substring(position).startsWith("bob's game")==false))
				{

					tC0=textBGColor;
					tC1=textColor;
					tC2=textAAColor;
					tC3=textShadowColor;

					textColor=BobColor.GREEN;
					if(textBGColor==BobColor.BLACK) textAAColor=BobColor.DARKGREEN;
					else textAAColor=BobColor.LIGHTGREEN;

					if(textBGColor==BobColor.BLACK) textShadowColor=BobColor.DARKERGREEN;
					else textShadowColor=BobColor.LIGHTGREEN;
				}
				else//bob
				if(position<length-2&&currentText.substring(position).startsWith("bob") && (position>=length-4||currentText.substring(position).startsWith("bob's")==false))
				{

					tC0=textBGColor;
					tC1=textColor;
					tC2=textAAColor;
					tC3=textShadowColor;

					textColor=BobColor.GREEN;
					if(textBGColor==BobColor.BLACK) textAAColor=BobColor.DARKGREEN;
					else textAAColor=BobColor.LIGHTGREEN;

					if(textBGColor==BobColor.BLACK) textShadowColor=BobColor.DARKERGREEN;
					else textShadowColor=BobColor.LIGHTGREEN;
				}
				else//nD
				if(position<length-1&&currentText.substring(position).startsWith("nD"))
				{

					tC0=textBGColor;
					tC1=textColor;
					tC2=textAAColor;
					tC3=textShadowColor;

					textColor=BobColor.GREEN;
					if(textBGColor==BobColor.BLACK) textAAColor=BobColor.DARKGREEN;
					else textAAColor=BobColor.LIGHTGREEN;

					if(textBGColor==BobColor.BLACK) textShadowColor=BobColor.DARKERGREEN;
					else textShadowColor=BobColor.LIGHTGREEN;
				}

			// parse option tags
			// this should never happen, it should be parsed above.
			if(currentText.charAt(position)=='<')
			{
				parseOption();

				String e="A tag was parsed inside drawText()";
				Console.error(e);
				log.error(e);
			}

			else

			// -----------------------------
			// handle space
			// -----------------------------
			if(currentText.charAt(position)==' ')
			{

				// get next word length including the space
				int nextWordLength=BobFont.getNextWordLength(currentText,position,font);

				// THIS SKIPS WORDS LONGER THEN THE MAXIMUM LENGTH
				if(nextWordLength>getLineSizeX())
				{
					// TODO: skip next word

					String e="A word was too long for the text engine.";
					Console.error(e);
					log.error(e);

					nextWordLength=BobFont.getNextWordLength(currentText,position,font);
				}

				// see if it fits on the current line
				int pixelsLeftInLine=getLineSizeX()-textBox[selectedTextbox].xInLine;
				if(textBox[selectedTextbox].line==MAX_LINES) pixelsLeftInLine-=8; // for the text button icon

				// if it doesnt fit, go to the next line
				if(pixelsLeftInLine<nextWordLength)
				{
					textBox[selectedTextbox].xInLine=0;
					textBox[selectedTextbox].line++;

					// if we're on the last line, wait for input
					if(textBox[selectedTextbox].line>MAX_LINES)
					{
						waitingForButtonForNewPage=true;
					}
				}

				// play a sound for each word. if the last word was a question, raise voice.
				// if(text[temp_position-1]=='?')MusicAndSoundManager().playSound("blah",127,TEXT_textbox[TEXT_selected_textbox].voice_pitch+(30000),0);
				// else MusicAndSoundManager().playSound("blah",127,TEXT_textbox[TEXT_selected_textbox].voice_pitch+(rand()%20000),0);

				// only draw the space if we're not at the beginning of the text box
				if(textBox[selectedTextbox].xInLine!=0)
					drawLetter();
			}
			else
			{
				// if TEXT_font_pointer<FONT_JAPANESE
				drawLetter();
			}

			// automatically colorize "Yuu" back to white

				if(position>=2&&currentText.substring(position-2).startsWith("Yuu"))
				{
					textBGColor=tC0;
					textColor=tC1;
					textAAColor=tC2;
					textShadowColor=tC3;
				}

			//"bob's game"
				else
				if(position>=11&&currentText.substring(position-11).startsWith("\"bob's game\""))
				{
					textBGColor=tC0;
					textColor=tC1;
					textAAColor=tC2;
					textShadowColor=tC3;
				}
				else
				if(position>=9&&currentText.substring(position-9).startsWith("bob's game") && (position>=length-1||currentText.substring(position-9).startsWith("bob's game\"")==false))
				{
					textBGColor=tC0;
					textColor=tC1;
					textAAColor=tC2;
					textShadowColor=tC3;
				}
				else
				if(position>=4&&currentText.substring(position-4).startsWith("bob's") && (position>=length-5||currentText.substring(position-4).startsWith("bob's game")==false))
				{

					textBGColor=tC0;
					textColor=tC1;
					textAAColor=tC2;
					textShadowColor=tC3;
				}
				else
				if(position>=2&&currentText.substring(position-2).startsWith("bob") && (position>=length-2||currentText.substring(position-2).startsWith("bob's")==false))
				{

					textBGColor=tC0;
					textColor=tC1;
					textAAColor=tC2;
					textShadowColor=tC3;
				}
				else
				if(position>=1&&currentText.substring(position-1).startsWith("nD"))
				{

					textBGColor=tC0;
					textColor=tC1;
					textAAColor=tC2;
					textShadowColor=tC3;
				}
				else
				if(currentText.substring(position).startsWith("nD"))
				{

					textColor=BobColor.PURPLE;
					if(textBGColor==BobColor.BLACK) textAAColor=BobColor.DARKPURPLE;
					else textAAColor=BobColor.LIGHTPURPLE;
					if(textBGColor==BobColor.BLACK) textShadowColor=BobColor.DARKERPURPLE;
					else textShadowColor=BobColor.LIGHTPURPLE;
				}


				if(position+1<length-3&&currentText.substring(position+1).startsWith("<.")==false)
				{
					//auto delay on punctuation
					if((currentText.charAt(position)=='.'||currentText.charAt(position)=='?'||currentText.charAt(position)=='!'))
					{
						delay=true;
						delayTicks=500;
					}

					if(currentText.charAt(position)==',')
					{
						delay=true;
						delayTicks=300;
					}

					if(currentText.charAt(position)=='-')
					{
						delay=true;
						delayTicks=300;
					}

					if(currentText.charAt(position)=='!')
					{
						textBox[selectedTextbox].shakeTicksYTotal=300;
						//textBox[selectedTextbox].shakeTicksLeft = textBox[selectedTextbox].shakeTicksTotal;
					}

					if(currentText.charAt(position)=='?')
					{
						textBox[selectedTextbox].shakeTicksXTotal=300;
						//textBox[selectedTextbox].shakeTicksLeft = textBox[selectedTextbox].shakeTicksTotal;
					}
				}
			// increment the string
			position++;



		}
	}


	// =========================================================================================================================
	public void handleInput()
	{// =========================================================================================================================


		if(waitingForButtonForNewPage==true)
		{
			if(ControlsManager().BUTTON_LSHIFT_PRESSED==true&&waitingForCancelButtonUnpress!=true)
			{
				waitingForCancelButtonUnpress=true;
				AudioManager().playSound("blip",0.25f,0.5f,1);
			}

			if(waitingForCancelButtonUnpress==true)
			{
				if(ControlsManager().BUTTON_LSHIFT_PRESSED==false)
				{
					waitingForCancelButtonUnpress=false;
					if(cannotCancel==false)
					{
						waitingForButtonPressToClose=true;
						waitingForUnpress=true;
						pausedUntilButtonPress=false;
					}
				}
			}

			if(buttonIconIsOn==false)
			{
				if(selectedTextbox==BOTTOM)
				{
					// TEXT_textbox[0].button_sprite = HARDWARE_create_sprite(TEXT_button_icon_GFX,0,1,1.0f,TEXT_textbox[0].screen_x+(64*3)-8,TEXT_textbox[0].screen_y+64-8-2,255);
				}
				if(selectedTextbox==TOP)
				{
					// TEXT_textbox[0].button_sprite = HARDWARE_create_sprite(TEXT_button_icon_GFX,0,1,1.0f,TEXT_textbox[0].screen_x+(64*3)-8,TEXT_textbox[1].screen_y+64-8-2,255);
				}
				buttonIconIsOn=true;
			}

			if((ControlsManager().BUTTON_ACTION_PRESSED==true||skipText==true)&&waitingForUnpress==false)
			{
				waitingForUnpress=true;
				AudioManager().playSound("blip",0.25f,1.5f,1);
			}

			if(waitingForUnpress==true)
			{
				if((ControlsManager().BUTTON_ACTION_PRESSED==false)||skipText==true)
				{
					waitingForUnpress=false;
					buttonAUnpressed=true;
				}
			}

			if(buttonAUnpressed==true)
			{
				if(buttonIconIsOn==true)
				{
					buttonIconIsOn=false;
					// HARDWARE_delete_sprite(TEXT_textbox[0].button_sprite);
				}

				buttonAUnpressed=false;
				textBox[selectedTextbox].clearByteArray();

				if(waitingForButtonPressToClose==false&&textEngineState!=CLOSING)
				{
					textBox[selectedTextbox].redraw=true;
				}

				textBox[selectedTextbox].line=0;
				textBox[selectedTextbox].xInLine=0;
				waitingForButtonForNewPage=false;
			}
		}



		if(pausedUntilButtonPress==true)
		{
			if(ControlsManager().BUTTON_LSHIFT_PRESSED==true&&waitingForCancelButtonUnpress!=true)
			{
				waitingForCancelButtonUnpress=true;


				AudioManager().playSound("blip",0.25f,0.5f,1);


			}
			if(waitingForCancelButtonUnpress==true)
			{
				if(ControlsManager().BUTTON_LSHIFT_PRESSED==false)
				{
					waitingForCancelButtonUnpress=false;
					if(cannotCancel==false)
					{
						waitingForButtonPressToClose=true;
						waitingForUnpress=true;
					}
				}
			}
			if(buttonIconIsOn==false)
			{
				if(selectedTextbox==BOTTOM)
				{

					// TEXT_textbox[0].button_sprite = HARDWARE_create_sprite(TEXT_button_icon_GFX,0,1,1.0f,TEXT_textbox[0].screen_x+(64*3)-8,TEXT_textbox[0].screen_y+64-8-2,255);

				}


				if(selectedTextbox==TOP)
				{

					// TEXT_textbox[0].button_sprite = HARDWARE_create_sprite(TEXT_button_icon_GFX,0,1,1.0f,TEXT_textbox[0].screen_x+(64*3)-8,TEXT_textbox[1].screen_y+64-8-2,255);
				}


				buttonIconIsOn=true;

			}
			if((ControlsManager().BUTTON_ACTION_PRESSED==true||skipText==true)
					&&
					waitingForUnpress==false)
			{
				waitingForUnpress=true;

				AudioManager().playSound("blip",0.25f,1.5f,1);

			}
			if(waitingForUnpress==true)
			{
				if((ControlsManager().BUTTON_ACTION_PRESSED==false)||skipText==true)
				{
					waitingForUnpress=false;
					buttonAUnpressed=true;
				}
			}
			if(buttonAUnpressed==true)
			{
				pausedUntilButtonPress=false;
				if(buttonIconIsOn==true)
				{

					buttonIconIsOn=false;

					// HARDWARE_delete_sprite(TEXT_textbox[0].button_sprite);
				}

				buttonAUnpressed=false;
			}
		}



		if(position>=length&&waitingForButtonPressToClose==false)
		{
			if(keepOpenForNewText==false)
			{
				waitingForButtonForNewPage=true;
				waitingForButtonPressToClose=true;
			}
			else
			{
				// TODO: set text string to log
				currentText=null;

				// /log conversations, parse NPC names
				// /log entered room name
				// /log items, interactions

				position=0;
			}
		}



		if(waitingForButtonPressToClose==true&&waitingForButtonForNewPage==false)
		{
			waitingForButtonPressToClose=false;


			currentText=null;

			position=0;
			cannotCancel=false;
			pausedUntilButtonPress=false;


			topBoxActivated=false;// if text box 2 is on, it will scroll up

			textEngineState=CLOSING;



		}
	}


	// =========================================================================================================================
	public void doScrolling()
	{// =========================================================================================================================



		long ticksPassed=Engine().realWorldTicksPassed();

		/*
		 * TEXT_scale = 1.0f;
		 * HARDWARE_sprite_set_scale(1,TEXT_box_1_sprite_window_id,TEXT_scale*2);
		 * HARDWARE_sprite_set_scale(1,TEXT_box_2_sprite_window_id,TEXT_scale*2);
		 * HARDWARE_sprite_set_scale(1,TEXT_box_1_chunk_1_id,TEXT_scale);
		 * HARDWARE_sprite_set_scale(1,TEXT_box_1_chunk_2_id,TEXT_scale);
		 * HARDWARE_sprite_set_scale(1,TEXT_box_1_chunk_3_id,TEXT_scale);
		 * HARDWARE_sprite_set_scale(1,TEXT_box_2_chunk_1_id,TEXT_scale);
		 * HARDWARE_sprite_set_scale(1,TEXT_box_2_chunk_2_id,TEXT_scale);
		 * HARDWARE_sprite_set_scale(1,TEXT_box_2_chunk_3_id,TEXT_scale);
		 */



		textBox[0].alpha=textBox[0].scrollPercent;
		textBox[1].alpha=textBox[1].scrollPercent;


		float fastScroll=0.003f*ticksPassed;
		float mediumScroll=0.001f*ticksPassed;


		if(topBoxActivated==true&&textBox[1].scrollPercent!=1.0f)
		{
			textBox[1].scrollPercent+=fastScroll;
			if(textBox[1].scrollPercent>1.0f) textBox[1].scrollPercent=1.0f;
		}


		if(topBoxActivated==false&&textBox[1].scrollPercent!=0.0f)
		{
			textBox[1].scrollPercent-=fastScroll;
			if(textBox[1].scrollPercent<0.0f) textBox[1].scrollPercent=0.0f;
		}



		if(textEngineState==ANSWER_BOX_ON) // ANSWER BOX TURNED ON,SCROLL TEXT BOX UP,ANSWER BOX UP
		{


//			if(textBox[0].scrollPercent>BOTTOM_ACTIVE_POSITION_Y-(11*numberOfAnswers)-2)
//			{
//				textBox[0].scrollPercent-=mediumScroll;
//				if(textBox[0].scrollPercent<BOTTOM_ACTIVE_POSITION_Y-(11*numberOfAnswers)-2)
//					textBox[0].scrollPercent=BOTTOM_ACTIVE_POSITION_Y-(11*numberOfAnswers)-2;
//			}
//
//			if(textBox[0].scrollPercent==BOTTOM_ACTIVE_POSITION_Y-(11*numberOfAnswers)-2)
//			{
//				if(answerBoxY>textBox[0].scrollPercent+textWindowHeight+8-2)
//				{
//					answerBoxY-=fastScroll;
//					if(answerBoxY<textBox[0].scrollPercent+textWindowHeight+8-2) answerBoxY=textBox[0].scrollPercent+textWindowHeight+8-2;
//				}
//			}

			if(selectedAnswer!=0)
				if(cursorScreenSprite!=null)
					cursorScreenSprite.screenYPixelsHQ=answerBoxY+1+((selectedAnswer-1)*11);


			cursorTicks+=Engine().engineTicksPassed();

			if(cursorTicks>300)
			{
				cursorTicks=0;

				if(cursorPixelUpDownToggle==true)
				{
					cursorPixelUpDownToggle=false;
					//if(cursorScreenSprite!=null)
						//cursorScreenSprite.screenXPixelsHQ=textBox[0].screenX+(64*3)-(64*4)-8-1;//TODO
				}
				else
				{
					cursorPixelUpDownToggle=true;
					//if(cursorScreenSprite!=null)
						//cursorScreenSprite.screenXPixelsHQ=textBox[0].screenX+(64*3)-(64*4)-8;
				}
			}

		}
		else if(textEngineState==ANSWER_BOX_CLOSING) // ANSWER BOX TURNED OFF,SCROLL TEXT BOX DOWN,SCROLL ANSWER BOX DOWN,DELETE ANSWER BOX
		{
			if(answerBoxY<Engine().getHeight())
			{
				answerBoxY+=fastScroll;
			}

//			if(textBox[0].scrollPercent<BOTTOM_ACTIVE_POSITION_Y)
//			{
//				textBox[0].scrollPercent+=mediumScroll;
//				if(textBox[0].scrollPercent>BOTTOM_ACTIVE_POSITION_Y)
//					textBox[0].scrollPercent=BOTTOM_ACTIVE_POSITION_Y;
//			}
//			else
//			{
//				textEngineState=OPEN;
//			}
		}
		else if(textEngineState==KEYBOARD_ON) // KEYBOARD TURNED ON,SCROLL TEXT BOX UP,KEYBOARD BOX UP
		{

//			if(textBox[0].scrollPercent>BOTTOM_ACTIVE_POSITION_Y-64-2)
//			{
//				textBox[0].scrollPercent-=mediumScroll;
//				if(textBox[0].scrollPercent<BOTTOM_ACTIVE_POSITION_Y-64-2) textBox[0].scrollPercent=BOTTOM_ACTIVE_POSITION_Y-64-2;
//			}
//
//			if(textBox[0].scrollPercent==BOTTOM_ACTIVE_POSITION_Y-64-2)
//			{
//				if(keyboardY>textBox[0].scrollPercent+64+8-2)
//				{
//					keyboardY-=fastScroll;
//					if(keyboardY<textBox[0].scrollPercent+64+8-2) keyboardY=textBox[0].scrollPercent+64+8-2;
//
//					if(keyboardScreenSprite!=null) keyboardScreenSprite.screenYPixelsHQ=keyboardY;
//				}
//			}

		}
		else if(textEngineState==KEYBOARD_CLOSING) // KEYBOARD TURNED OFF,SCROLL TEXT BOX DOWN,SCROLL KEYBOARD DOWN,DELETE KEYBOARD
		{
			if(keyboardY<Engine().getHeight())
			{
				keyboardY+=fastScroll;


				if(keyboardScreenSprite!=null)
					keyboardScreenSprite.screenYPixelsHQ=keyboardY;

			}
			if(textBox[0].scrollPercent>0.0f)
			{
				textBox[0].scrollPercent-=fastScroll;
				if(textBox[0].scrollPercent<0.0f) textBox[0].scrollPercent=0.0f;
			}
			else
			{
				textEngineState=OPEN;
			}
		}
		else



		if(textEngineState==OPEN)	// ==================================TEXT BOX IS IN RUNNING STATE==============================
		{



			if(textBox[0].scrollPercent>=1.0f)
			{
				textBox[0].scrollPercent=1.0f;
				scrollingUp=false;
			}
			else if(textBox[0].scrollPercent<1.0f)
			{
				textBox[0].scrollPercent+=fastScroll;
				scrollingUp=true;
			}




			if(delay==true)
			{

				if(delayTicks>0) delayTicks-=ticksPassed;
				else
				{
					delay=false;
				}

			}

			for(int i=0;i<2;i++)
			{

				if(textBox[i].shakeTicksXTotal>0)
				{
					if(textBox[i].shakeTicksXTotal>0)textBox[i].shakeTicksXTotal-=ticksPassed;
					if(textBox[i].shakeTicksXTotal<0)textBox[i].shakeTicksXTotal=0;


					textBox[i].shakeTicksLeftRightCounter+=ticksPassed;

					if(textBox[i].shakeTicksLeftRightCounter>10)
					{
						textBox[i].shakeTicksLeftRightCounter = 0;

						if(textBox[i].shakeLeftRightToggle==true)
						{
							textBox[i].shakeX++;
							if(textBox[i].shakeX>=textBox[i].shakeMaxX)textBox[i].shakeLeftRightToggle = !textBox[i].shakeLeftRightToggle;
						}
						else
						{
							textBox[i].shakeX--;
							if(textBox[i].shakeX<=0-textBox[i].shakeMaxX)textBox[i].shakeLeftRightToggle = !textBox[i].shakeLeftRightToggle;
						}

					}
				}
				else
				{
					textBox[i].shakeX=0;
				}


				if(textBox[i].shakeTicksYTotal>0)
				{
					if(textBox[i].shakeTicksYTotal>0)textBox[i].shakeTicksYTotal-=ticksPassed;
					if(textBox[i].shakeTicksYTotal<0)textBox[i].shakeTicksYTotal=0;


					textBox[i].shakeTicksUpDownCounter+=ticksPassed;

					if(textBox[i].shakeTicksUpDownCounter>10)
					{
						textBox[i].shakeTicksUpDownCounter = 0;

						if(textBox[i].shakeUpDownToggle==true)
						{
							textBox[i].shakeY++;
							if(textBox[i].shakeY>=textBox[i].shakeMaxY)textBox[i].shakeUpDownToggle = !textBox[i].shakeUpDownToggle;
						}
						else
						{
							textBox[i].shakeY--;
							if(textBox[i].shakeY<=0-textBox[i].shakeMaxY)textBox[i].shakeUpDownToggle = !textBox[i].shakeUpDownToggle;
						}

					}
				}
				else
				{
					textBox[i].shakeY=0;
				}
			}


		}	// END IF TEXT BOX ON

		else if(textEngineState==CLOSING) // ===========================TEXT BOX IS IN SCROLLING DOWN STATE. WHEN FINISHED,DELETE TEXT BOX===================
		{

			if(textBox[0].scrollPercent>0.0f)
			{
				textBox[0].scrollPercent-=fastScroll;
			}

			if(textBox[0].scrollPercent<0.0f)
			{
				textBox[0].scrollPercent=0.0f;


				Cameraman().ignoreCameraFXBoundaries=false;// TODO: restore previous state
				Cameraman().setTarget(Player());// TODO: restore previous cameraman target and speed
				Cameraman().setTicksPerPixelMoved(Cameraman().ticksPerPixel_CAMERA_CONVERSATION);


				textEngineState=CLOSED;
			}
		}



		else if(textEngineState==CLOSED)
		{


			textBox[0].scrollPercent=0.0f;
			textBox[1].scrollPercent=0.0f;

		}


//		if(buttonIconIsOn==true)
//		{
//
//			// if(TEXT_selected_textbox==false)
//			// HARDWARE_set_sprite_xy(TEXT_textbox[0].button_sprite,TEXT_textbox[0].screen_x+(64*3)-8,TEXT_textbox[0].screen_y+64-8-(TEXT_button_icon_down*2));
//
//
//			// if(TEXT_selected_textbox==true)
//			// HARDWARE_set_sprite_xy(TEXT_textbox[0].button_sprite,TEXT_textbox[0].screen_x+(64*3)-8,TEXT_textbox[1].screen_y+64-8-(TEXT_button_icon_down*2));
//
//			if(buttonTimer>500)
//			{
//				buttonTimer=0;
//
//				if(buttonIconUpDownToggle==false)
//				{
//					buttonIconUpDownToggle=true;
//				}
//				else
//				{
//					buttonIconUpDownToggle=false;
//				}
//			}
//			buttonTimer+=Engine().engineTicksPassed();
//		}



	}


	// =========================================================================================================================
	void drawLetter()
	{// =========================================================================================================================


		int letterIndex=BobFont.getFontIndexForChar(currentText.charAt(position));
		if(letterIndex==-1) return;



		int letterWidth=BobFont.getCharWidth(letterIndex,font);



		// play sound sometimes, for vowels
		if((
				textBox[selectedTextbox].xInLine==0
				&&
				textBox[selectedTextbox].line==0
				)
				||
				(
				position%2==0
						&&
						position<length-1
						&&
				(
				BobFont.is_a_vowel(currentText.charAt(position-1))!=BobFont.is_a_vowel(currentText.charAt(position))
				||
				BobFont.is_a_vowel(currentText.charAt(position))!=BobFont.is_a_vowel(currentText.charAt(position+1))
				)
				))
		{
			if(font==BobFont.font_bob_16)
			{
				AudioManager().playSound("blah",0.5f,textBox[selectedTextbox].voicePitch+((10+Utils.randUpToIncluding(20))/10.0f),1);
			}
			else
			{
				AudioManager().playSound("blah",0.5f,textBox[selectedTextbox].voicePitch+(Utils.randUpToIncluding(20)/10.0f),1);
			}

			delay=true;// /why do i do this? slight delay on vowels so the sound has time to play?
			delayTicks=50;
		}


		boolean putInSpaceAlready=false;

		int xInLetter=0;
		for(xInLetter=0;xInLetter<letterWidth;xInLetter++)
		{

			if(textBox[selectedTextbox].xInLine>getLineSizeX())
			{
				textBox[selectedTextbox].xInLine=0;
				textBox[selectedTextbox].line++;
			}


			if(textBox[selectedTextbox].line>MAX_LINES)
			{
				// PAUSE,CLEAR,START OVER
				waitingForButtonForNewPage=true;
			}


			// it it's a space on the last tile/chunk/pixel, skip it
			if(currentText.charAt(position)==' '&&textBox[selectedTextbox].xInLine>=getLineSizeX())
			{

				textBox[selectedTextbox].xInLine=0;
				textBox[selectedTextbox].line++;

				xInLetter=letterWidth;

				putInSpaceAlready=true;

				if(textBox[selectedTextbox].line>MAX_LINES)
				{
					waitingForButtonForNewPage=true;
				}
			}

			if(waitingForButtonForNewPage==false&&putInSpaceAlready==false)
			{
				textBox[selectedTextbox].drawColumn(letterIndex,xInLetter,0);
				textBox[selectedTextbox].xInLine++;
			}
		}



		// ===================================INSERT SPACE
		// if(text[TEXT_string_position]==' ')put_in_space_already=true; breaks the pixel length count.. i'd have to make it width-1 in get_text_length



		if(textBox[selectedTextbox].line<=MAX_LINES&&textBox[selectedTextbox].xInLine<getLineSizeX()&&putInSpaceAlready==false)
		{
			textBox[selectedTextbox].drawColumn(0,0,1);
			textBox[selectedTextbox].xInLine++;
			putInSpaceAlready=true;
		}

		if(textBox[selectedTextbox].xInLine>getLineSizeX())
		{

			textBox[selectedTextbox].xInLine=0;
			textBox[selectedTextbox].line++;
		}


		if(textBox[selectedTextbox].line>MAX_LINES)
		{
			// PAUSE,CLEAR,START OVER
			waitingForButtonForNewPage=true;
		}


		// END INSERT SPACE===================================================================
		// /TEXT_update_textbox_sprite_textures();
		textBox[selectedTextbox].redraw=true;

	}



	// =========================================================================================================================
	void parseOption()
	{// =========================================================================================================================
		int optionLength=0;
		// char TEXT_option_buffer[] = new char[MAX_ANSWER_LENGTH*6+5+2];



		position++;
		while(currentText.charAt(position+optionLength)!='>'
				&&
				position+optionLength<length)
		{
			// if(TEXT_option_length<MAX_ANSWER_LENGTH*6+5+1)
			// TEXT_option_buffer.concat(TEXT_text.substring(TEXT_string_position+TEXT_option_length,TEXT_string_position+TEXT_option_length+1)); //fix fox longer than 6 longest answers


			// else {
			// TEXT_option_buffer[TEXT_option_length]=null;
			// u16 amt=0;
			// while(text[TEXT_string_position+amt]!='>')amt++;
			// TEXT_string_position+=amt-TEXT_option_length;
			// break;

			// }

//			if(currentText.charAt(position+optionLength)==':')
//			{
//				int tempAnswerLength=0;
//
//				while(currentText.charAt(position+optionLength+1+tempAnswerLength)!=':'
//						&&
//						currentText.charAt(position+optionLength+1+tempAnswerLength)!='>')
//				{
//					tempAnswerLength++;
//				}
//
//				// TODO: fix this
//				/*
//				 * if(TEXT_temp_answer_length>MAX_ANSWER_LENGTH-1)
//				 * {
//				 * //cuts off answers longer than 50. increments the length by 50,only takes 50 from the answer,increments position by the whole thing
//				 * int i=0;
//				 * for(i=0;i<MAX_ANSWER_LENGTH-1;i++)
//				 * TEXT_option_buffer[TEXT_option_length+1+i]=TEXT_text.charAt(TEXT_string_position+TEXT_option_length+1+i);
//				 * TEXT_option_length+=MAX_ANSWER_LENGTH-1; //increments below
//				 * TEXT_string_position+=(TEXT_temp_answer_length-1)-(MAX_ANSWER_LENGTH-1-1);
//				 * }
//				 */
//			}

			optionLength++;
		}

		optionBuffer=currentText.substring(position,position+optionLength);
		position+=optionLength;

		/*
		 * #define CLEAR 0
		 * #define BLACK 1
		 * #define WHITE 2
		 * #define GRAY 3
		 * #define RED 4
		 * #define ORANGE 5
		 * #define YELLOW 6
		 * #define GREEN 7
		 * #define BLUE 8
		 * #define PURPLE 9
		 * #define PINK 10
		 */
		if(optionBuffer.equals(".")) // if i change this from "." remember to change get_next_word_length above.
		{
			waitingForButtonForNewPage=true;
		}
		else if(optionBuffer.equals("0")||optionBuffer.equals("BOTTOM"))
		{
			selectedTextbox=BOTTOM;
			Cameraman().setTarget(textBox[selectedTextbox].spriteWindowEntity);	// if is not null!! else yuu
			Cameraman().setTicksPerPixelMoved(Cameraman().ticksPerPixel_CAMERA_CONVERSATION);
		}
		else if(optionBuffer.equals("1")||optionBuffer.equals("TOP"))
		{
			selectedTextbox=TOP;
			topBoxActivated=true;
			Cameraman().setTarget(textBox[selectedTextbox].spriteWindowEntity);
			Cameraman().setTicksPerPixelMoved(Cameraman().ticksPerPixel_CAMERA_CONVERSATION);
		}
		else if(optionBuffer.equals("PAUSE"))
		{
			pausedUntilButtonPress=true;
		}
		else if(optionBuffer.equals("BOB"))
		{

			font=BobFont.font_bob_16;
		}
		else if(optionBuffer.equals("SMALL"))
		{

			font=BobFont.font_small_16;
		}
		else if(optionBuffer.equals("NORMAL"))
		{

			font=BobFont.font_normal_16;
		}
		else if(optionBuffer.equals("BLACK"))
		{
			textBGColor=BobColor.WHITE;
			textColor=BobColor.BLACK;
			textAAColor=BobColor.LIGHTGRAY;
			textShadowColor=BobColor.GRAY;
		}
		else if(optionBuffer.equals("WHITE"))
		{
			textBGColor=BobColor.BLACK;
			textColor=BobColor.WHITE;
			textAAColor=BobColor.GRAY;
			textShadowColor=BobColor.DARKGRAY;
		}
		else if(optionBuffer.equals("GRAY"))
		{
			textColor=BobColor.GRAY;
			if(textBGColor==BobColor.BLACK) textAAColor=BobColor.DARKGRAY;
			else textAAColor=BobColor.LIGHTGRAY;
			if(textBGColor==BobColor.BLACK) textShadowColor=BobColor.DARKERGRAY;
			else textShadowColor=BobColor.LIGHTGRAY;
		}
		else if(optionBuffer.equals("RED"))
		{
			textColor=BobColor.RED;
			if(textBGColor==BobColor.BLACK) textAAColor=BobColor.DARKRED;
			else textAAColor=BobColor.LIGHTRED;
			if(textBGColor==BobColor.BLACK) textShadowColor=BobColor.DARKERRED;
			else textShadowColor=BobColor.LIGHTRED;
		}
		else if(optionBuffer.equals("ORANGE"))
		{
			textColor=BobColor.ORANGE;
			if(textBGColor==BobColor.BLACK) textAAColor=BobColor.DARKORANGE;
			else textAAColor=BobColor.LIGHTORANGE;
			if(textBGColor==BobColor.BLACK) textShadowColor=BobColor.DARKERORANGE;
			else textShadowColor=BobColor.LIGHTORANGE;
		}
		else if(optionBuffer.equals("YELLOW"))
		{
			textColor=BobColor.YELLOW;
			if(textBGColor==BobColor.BLACK) textAAColor=BobColor.DARKYELLOW;
			else textAAColor=BobColor.LIGHTYELLOW;
			if(textBGColor==BobColor.BLACK) textShadowColor=BobColor.DARKERYELLOW;
			else textShadowColor=BobColor.LIGHTYELLOW;
		}
		else if(optionBuffer.equals("GREEN"))
		{
			textColor=BobColor.GREEN;
			if(textBGColor==BobColor.BLACK) textAAColor=BobColor.DARKGREEN;
			else textAAColor=BobColor.LIGHTGREEN;
			if(textBGColor==BobColor.BLACK) textShadowColor=BobColor.DARKERGREEN;
			else textShadowColor=BobColor.LIGHTGREEN;
		}
		else if(optionBuffer.equals("BLUE"))
		{
			textColor=BobColor.BLUE;
			if(textBGColor==BobColor.BLACK) textAAColor=BobColor.DARKBLUE;
			else textAAColor=BobColor.LIGHTBLUE;
			if(textBGColor==BobColor.BLACK) textShadowColor=BobColor.DARKERBLUE;
			else textShadowColor=BobColor.LIGHTBLUE;
		}
		else if(optionBuffer.equals("PURPLE"))
		{
			textColor=BobColor.PURPLE;
			if(textBGColor==BobColor.BLACK) textAAColor=BobColor.DARKPURPLE;
			else textAAColor=BobColor.LIGHTPURPLE;
			if(textBGColor==BobColor.BLACK) textShadowColor=BobColor.DARKERPURPLE;
			else textShadowColor=BobColor.LIGHTPURPLE;
		}
		else if(optionBuffer.equals("PINK"))
		{
			textColor=BobColor.PINK;
			if(textBGColor==BobColor.BLACK) textAAColor=BobColor.DARKPINK;
			else textAAColor=BobColor.LIGHTPINK;
			if(textBGColor==BobColor.BLACK) textShadowColor=BobColor.DARKERPINK;
			else textShadowColor=BobColor.LIGHTPINK;
		}
		else if(optionBuffer.equals("BGBLACK"))
		{
			textBGColor=BobColor.BLACK;
			// TODO: if(textColor==COLOR)textAAColor=DARKCOLOR;
		}
		else if(optionBuffer.equals("BGWHITE"))
		{
			textBGColor=BobColor.WHITE;
			// TODO: if(textColor==COLOR)textAAColor=LIGHTCOLOR;
		}

		else if(optionBuffer.equals("CAM0")||optionBuffer.equals("CAMBOTTOM"))
		{
			Cameraman().setTarget(textBox[BOTTOM].spriteWindowEntity);
			Cameraman().setTicksPerPixelMoved(Cameraman().ticksPerPixel_CAMERA_CONVERSATION);
		}
		else if(optionBuffer.equals("CAM1")||optionBuffer.equals("CAMTOP"))
		{
			Cameraman().setTarget(textBox[TOP].spriteWindowEntity);
			Cameraman().setTicksPerPixelMoved(Cameraman().ticksPerPixel_CAMERA_CONVERSATION);
		}
		else if(optionBuffer.equals("CLOSE1")||optionBuffer.equals("CLOSETOP"))
		{
			selectedTextbox=BOTTOM;
			topBoxActivated=false;
		}
		else if(optionBuffer.equals("SHAKE1SEC"))
		{
			textBox[selectedTextbox].shakeTicksXTotal=1000;
			//textBox[selectedTextbox].shakeTicksLeft = textBox[selectedTextbox].shakeTicksTotal;
		}
		else if(optionBuffer.equals("SHAKE2SEC"))
		{

			textBox[selectedTextbox].shakeTicksXTotal=2000;
			//textBox[selectedTextbox].shakeTicksLeft = textBox[selectedTextbox].shakeTicksTotal;
		}

		else if(optionBuffer.startsWith("SHAKE:"))
		{
			int ticks = Integer.parseInt(optionBuffer.substring(optionBuffer.indexOf(":")+1));
			textBox[selectedTextbox].shakeTicksXTotal=ticks;
			//textBox[selectedTextbox].shakeTicksLeft = textBox[selectedTextbox].shakeTicksTotal;
		}
		else
		if(optionBuffer.equals("CLEAR"))
		{
			textBox[selectedTextbox].line=0;
			textBox[selectedTextbox].xInLine=0;
			textBox[selectedTextbox].clearByteArray();
			// /TEXT_update_textbox_sprite_textures();
			textBox[selectedTextbox].redraw=true;
		}
		else if(optionBuffer.equals("NEXTLINE")||optionBuffer.equals("NEWLINE"))
		{
			textBox[selectedTextbox].xInLine=0;
			textBox[selectedTextbox].line++;
			if(textBox[selectedTextbox].line>MAX_LINES)
			{
				waitingForButtonForNewPage=true;
			}
		}
		else if(optionBuffer.equals("DELAY"))
		{
			delay=true;
			delayTicks=300;
		}
		else if(optionBuffer.equals("DELAY30"))
		{
			delay=true;
			delayTicks=500;
		}
		else if(optionBuffer.equals("DELAY60"))
		{
			delay=true;
			delayTicks=1000;
		}
		else if(optionBuffer.equals("DELAY1SEC"))
		{
			delay=true;
			delayTicks=1000;
		}
		else if(optionBuffer.equals("DELAY2SEC"))
		{
			delay=true;
			delayTicks=2000;
		}
		else if(optionBuffer.startsWith("DELAY:"))
		{
			int ticks = Integer.parseInt(optionBuffer.substring(optionBuffer.indexOf(":")+1));
			delay=true;
			delayTicks=ticks;
		}
		else if(optionBuffer.equals("KEEPOPENAFTER"))
		{
			keepOpenForNewText=true;
		}
		else if(optionBuffer.equals("NOCANCEL"))
		{
			cannotCancel=true;
		}
		else if(optionBuffer.equals("YUU")||optionBuffer.equals("PLAYER"))
		{
			if(Player()!=null)
			{
				textBox[selectedTextbox].setSpriteWindow(Player(),null,null);
				Cameraman().setTarget(textBox[selectedTextbox].spriteWindowEntity);
			}
			else
			{
				textBox[selectedTextbox].setSpriteWindow(Cameraman().targetEntity,null,null);
			}
		}
		else if(optionBuffer.equals("MOM"))
		{
			Entity e=CurrentMap().getEntityByName("mom");
			if(e==null) return;
			textBox[selectedTextbox].setSpriteWindow(e,null,null);
			Cameraman().setTarget(textBox[selectedTextbox].spriteWindowEntity);
		}
		else if(optionBuffer.equals("DAD"))
		{
			Entity e=CurrentMap().getEntityByName("dad");
			if(e==null) return;
			textBox[selectedTextbox].setSpriteWindow(e,null,null);
			Cameraman().setTarget(textBox[selectedTextbox].spriteWindowEntity);
		}
		else if(optionBuffer.equals("BROTHER"))
		{
			Entity e=CurrentMap().getEntityByName("brother");
			if(e==null) return;
			textBox[selectedTextbox].setSpriteWindow(e,null,null);
			Cameraman().setTarget(textBox[selectedTextbox].spriteWindowEntity);
		}
		else if(optionBuffer.equals("NPC1"))
		{

			textBox[selectedTextbox].setSpriteWindow(optionTargetEntity1,null,null);
			Cameraman().setTarget(textBox[selectedTextbox].spriteWindowEntity);
		}
		else if(optionBuffer.equals("NPC2"))
		{

			textBox[selectedTextbox].setSpriteWindow(optionTargetEntity2,null,null);
			Cameraman().setTarget(textBox[selectedTextbox].spriteWindowEntity);
		}
		else if(optionBuffer.equals("NPC3"))
		{

			textBox[selectedTextbox].setSpriteWindow(optionTargetEntity3,null,null);
			Cameraman().setTarget(textBox[selectedTextbox].spriteWindowEntity);
		}
		else if(optionBuffer.equals("NPC4"))
		{

			textBox[selectedTextbox].setSpriteWindow(optionTargetEntity4,null,null);
			Cameraman().setTarget(textBox[selectedTextbox].spriteWindowEntity);
		}
		else if(optionBuffer.equals("NPC5"))
		{

			textBox[selectedTextbox].setSpriteWindow(optionTargetEntity5,null,null);
			Cameraman().setTarget(textBox[selectedTextbox].spriteWindowEntity);
		}
		else if(optionBuffer.equals("NPC6"))
		{

			textBox[selectedTextbox].setSpriteWindow(optionTargetEntity6,null,null);
			Cameraman().setTarget(textBox[selectedTextbox].spriteWindowEntity);
		}
		else if(optionBuffer.startsWith("SETSPRITEBOX0TOENTITY:"))
		{
			String s = optionBuffer.substring(optionBuffer.indexOf(":")+1);
			Entity e = CurrentMap().getEntityByName(s);
			if(e!=null)textBox[0].setSpriteWindow(e,null,null);
		}
		else if(optionBuffer.startsWith("SETSPRITEBOX1TOENTITY:"))
		{
			String s = optionBuffer.substring(optionBuffer.indexOf(":")+1);
			Entity e = CurrentMap().getEntityByName(s);
			if(e!=null)textBox[1].setSpriteWindow(e,null,null);
		}
		else if(optionBuffer.startsWith("SETSPRITEBOX0TOSPRITE:"))
		{
			String s = optionBuffer.substring(optionBuffer.indexOf(":")+1);
			Sprite e = SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("SPRITE."+s);
			if(e!=null)textBox[0].setSpriteWindow(null,e.texture,e.displayName());
		}
		else if(optionBuffer.startsWith("SETSPRITEBOX1TOSPRITE:"))
		{
			String s = optionBuffer.substring(optionBuffer.indexOf(":")+1);
			Sprite e = SpriteManager().getSpriteByNameOrRequestFromServerIfNotExist("SPRITE."+s);
			if(e!=null)textBox[1].setSpriteWindow(null,e.texture,e.displayName());
		}
		else if(optionBuffer.startsWith("PITCH:"))
		{
			float pitch=1.0f;
			try
			{
				pitch=Float.parseFloat(optionBuffer.substring(6));
			}
			catch(NumberFormatException e)
			{
				log.error(e.getMessage());
				return;
			}
			textBox[selectedTextbox].voicePitch=pitch;
		}
		else if(optionBuffer.startsWith("Q:"))
		{
			getAnswerToQuestionWithQuestionBox(optionBuffer,optionLength);
		}
		else if(optionBuffer.equals("KEYBOARD"))
		{
			getTextFromOnscreenKeyboard();
		}
		else if(optionBuffer.equals("NUMPAD"))
		{
			getNumberFromOnscreenNumpad();
		}
		else
		{
			String e="Unknown tag parsed in TextEngine: "+optionBuffer;
			Console.error(e);
			log.error(e);
		}

	}


	public void dialogue(Dialogue d)
	{
		// TODO

		text(d.text());
		// d.tellServerDialogueDone();//do this after text is completed.

		d.setDialogueDoneValue_S(true);// tells the server we have completed this text
		// TODO: need to set this value after the text has completed, otherwise it gets set even if we skip the text.

	}



	public void getTextFromOnscreenKeyboard()
	{
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO

	}


	public void getNumberFromOnscreenNumpad()
	{
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
	}


	public void getAnswerToQuestionWithQuestionBox(String s,int i)
	{
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO

	}



}
