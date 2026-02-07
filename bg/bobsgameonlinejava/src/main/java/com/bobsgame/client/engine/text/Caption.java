package com.bobsgame.client.engine.text;

import static org.lwjgl.opengl.GL11.glTexImage2D;

import com.bobsgame.client.Texture;


import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.console.Console;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.entity.Entity;
import com.bobsgame.client.engine.event.ActionManager;
import com.bobsgame.client.engine.map.Area;
import com.bobsgame.client.engine.text.BobFont.BitmapFont;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.Utils;
import com.bobsgame.shared.MapData.RenderOrder;



//=========================================================================================================================
public class Caption extends EnginePart
{//=========================================================================================================================





	public String text = null;
	public BitmapFont font = BobFont.font_normal_11_outlined;

	private BobColor textBGColor = BobColor.black;
	private BobColor textColor = BobColor.white;
	private BobColor textAAColor = BobColor.gray;




	public float screenX=0;
	public float screenY=0;
	public RenderOrder layer=RenderOrder.ABOVE_TOP;
	public float scale=1.0f;
	public long ticksAge=0;
	public int ticksToRemain=0;
	private float alpha=0.0f;
	private float alphaTo = 1.0f;
	private boolean delete=false;


	public Entity entity = null;
	public float entityXWhenCreated=0;
	public float entityYWhenCreated=0;

	public int actionCaptionType = ActionManager.ACTIONCAPTIONTYPE_NONE;
	public Area area = null;
	public int actionRangeX = 0;
	public int actionRangeY = 0;


	public boolean fadeLetterColorTowardsTop = true;

	public int textCharacterLength = 0;
	private int width=0;
	private int height=0;
	public int lines=1;
	public int maxWidth=0;


	int xInLine=0;
	int line=0;
	int longestLineWidth=0;

	boolean init = false;


	public Texture texture = null;
	public ByteBuffer textureByteBuffer = null;
	public byte[] textureByteArray = null;
	public int texWidth=0;
	public int texHeight=0;


	public int fixedPosition=0;
	public boolean flashing = false;
	public int flashingTicksPerFlash = 0;
	public boolean centerTextOnMultipleLines = false;

	//x position modifiers
	static public int CENTERED_OVER_ENTITY = -1;
	static public int CENTERED_SCREEN = -2;
	static public int CENTERED_X = -3;

	//seconds modifiers
	static public int DELETE_WHEN_MAIN_SPRITE_MOVES = -2;
	static public int STAY_ONSCREEN_UNTIL_MANUALLY_DELETE = -1;






	//=========================================================================================================================
	/**
		If Engine is Client(), it will draw outside the nD. If it is Engine() inside an nD game, it will draw inside the nD.
		If screenX is Caption.CENTERED_OVER_ENTITY it will center itself over this.entity.
		If no entity is set, it will use Player() if not null.
		If screenX is Caption.CENTERED_SCREEN it will ignore Y and center both X and Y in the screen.
		If seconds is Caption.DELETE_WHEN_ENTITY_MOVES it will delete when attached entity (or player if not null) moves.
		If seconds is Caption.STAY_ONSCREEN_UNTIL_MANUALLY_DELETE it must be deleted manually.

		TODO: if layer is outside the screen, don't scale with the screen.

		Scale is default at 2X for 1.0f. for 1:1 pixels use 0.5f.
		SetWidth is the width to truncate to a newline. It won't truncate words. setWidth 0 or -1 will just default to half the screen width at maximum.

	*/
	public Caption(Engine g, float screenX, float screenY, int seconds, String text, BitmapFont font, BobColor textColor, BobColor textAAColor, BobColor textBGColor, RenderOrder layer, float scale, int maxWidth, Entity entity, Area area, boolean fadeLetterColorTowardsTop, boolean centerTextOnMultipleLines)
	{//=========================================================================================================================

		super(g);

		init(screenX, screenY, seconds, text, font, textColor, textAAColor, textBGColor, layer, scale, maxWidth, entity, area, fadeLetterColorTowardsTop, centerTextOnMultipleLines);
	}

	public Caption(Engine g, float screenX, float screenY, int seconds, String text, BitmapFont font, BobColor textColor, BobColor textAAColor, BobColor textBGColor)
	{
		super(g);

		init(screenX, screenY, seconds, text, font, textColor, textAAColor, textBGColor, layer, scale, maxWidth, entity, area, fadeLetterColorTowardsTop, centerTextOnMultipleLines);
	}

	public Caption(Engine g, float screenX, float screenY, int seconds, String text, BitmapFont font, BobColor textColor, BobColor textAAColor, BobColor textBGColor, RenderOrder layer, float scale, int maxWidth)
	{
		super(g);

		init(screenX, screenY, seconds, text, font, textColor, textAAColor, textBGColor, layer, scale, maxWidth, entity, area, fadeLetterColorTowardsTop, centerTextOnMultipleLines);
	}

	public Caption(Engine g, float screenX, float screenY, int seconds, String text, BitmapFont font, BobColor textColor, BobColor textBGColor)
	{
		super(g);

		init(screenX, screenY, seconds, text, font, textColor, textAAColor, textBGColor, layer, scale, maxWidth, entity, area, fadeLetterColorTowardsTop, centerTextOnMultipleLines);
	}

	//=========================================================================================================================
	public void replaceText(String text)
	{//=========================================================================================================================
		replaceText(text,false);
	}
	//=========================================================================================================================
	public void replaceText(String text,boolean force)
	{//=========================================================================================================================

		if(force==false&&text.equals(this.text))return;

		if(texture!=null)
		{
			texture=GLUtils.releaseTexture(texture);
		}

		textureByteBuffer = null;
		textureByteArray = null;

		init(screenX, screenY, ticksToRemain, text, font, textColor, textAAColor, textBGColor, layer, scale, maxWidth, entity, area, fadeLetterColorTowardsTop, centerTextOnMultipleLines);

	}

	//=========================================================================================================================
	public void setTextColor(BobColor textColor)
	{//=========================================================================================================================
		setTextColor(textColor,null,null);
	}

	//=========================================================================================================================
	public void setTextColor(BobColor fg, BobColor aa, BobColor bg)
	{//=========================================================================================================================


		if(fg==this.textColor && bg==this.textBGColor && aa==this.textAAColor)return;

		//-----------------------------
		//set color
		//-----------------------------

		//color 0 = bg color
		//color 1 = text color
		//color 2 = antialiasing color

		BobColor tempFG = this.textColor;
		BobColor tempBG = this.textBGColor;
		BobColor tempAA = this.textAAColor;

		if(fg!=null)tempFG=fg;
		if(bg!=null)tempBG=bg;

		if(aa!=null)tempAA=aa;
		else
		{

			if(this.font.outlined==true){tempAA=BobColor.BLACK;}
			else
			if(tempBG==BobColor.WHITE)
			{
				tempAA = fg.lighter().lighter();
//				if(textColor==BobColor.BLACK)this.textAAColor=BobColor.LIGHTERGRAY;
//				if(textColor==BobColor.GRAY)this.textAAColor=BobColor.LIGHTERGRAY;
//
//				if(textColor==BobColor.GREEN)this.textAAColor=BobColor.LIGHTGREEN;
//				if(textColor==BobColor.BLUE)this.textAAColor=BobColor.LIGHTBLUE;
//				if(textColor==BobColor.PURPLE)this.textAAColor=BobColor.LIGHTPURPLE;
//				if(textColor==BobColor.PINK)this.textAAColor=BobColor.LIGHTPINK;
//				if(textColor==BobColor.RED)this.textAAColor=BobColor.LIGHTRED;
//				if(textColor==BobColor.ORANGE)this.textAAColor=BobColor.LIGHTORANGE;
//				if(textColor==BobColor.YELLOW)this.textAAColor=BobColor.LIGHTYELLOW;
			}
			else
			if(tempBG==BobColor.BLACK)//||textBGColor==BobColor.CLEAR)
			{

				tempAA = fg.darker().darker().darker();

//				if(textColor==BobColor.WHITE)this.textAAColor=BobColor.DARKGRAY;
//				if(textColor==BobColor.GRAY)this.textAAColor=BobColor.DARKERGRAY;
//
//				if(textColor==BobColor.GREEN)this.textAAColor=BobColor.DARKERGREEN;
//				if(textColor==BobColor.BLUE)this.textAAColor=BobColor.DARKBLUE;
//				if(textColor==BobColor.PURPLE)this.textAAColor=BobColor.DARKPURPLE;
//				if(textColor==BobColor.PINK)this.textAAColor=BobColor.DARKPINK;
//				if(textColor==BobColor.RED)this.textAAColor=BobColor.DARKRED;
//				if(textColor==BobColor.ORANGE)this.textAAColor=BobColor.DARKORANGE;
//				if(textColor==BobColor.YELLOW)this.textAAColor=BobColor.DARKYELLOW;
			}
			else
			if(tempBG==BobColor.CLEAR)
			{
				BobColor c = fg;
				tempAA = new BobColor(c.r(),c.g(),c.b(),c.a()/2.0f);

			}
		}

		if(init==true)//don't replace the text if we haven't drawn the bitmap yet
		{

			if(tempFG!=this.textColor || tempBG!=this.textBGColor || tempAA!=this.textAAColor)//dont replace if the colors havent changed
			{
				this.textColor = tempFG;
				this.textBGColor = tempBG;
				this.textAAColor = tempAA;

				replaceText(text,true);
			}
		}
		else
		{
			this.textColor = tempFG;
			this.textBGColor = tempBG;
			this.textAAColor = tempAA;
		}

	}


	//=========================================================================================================================
	public void init(float screenX,float screenY,int ticks,String text,BitmapFont font,BobColor textColor,BobColor textAAColor, BobColor textBGColor, RenderOrder layer, float scale, int maxWidth, Entity entity, Area area, boolean fadeLetterColorTowardsTop, boolean centerTextOnMultipleLines)
	{//=========================================================================================================================


		this.init = false;

		//get length
		this.textCharacterLength = text.length();
		this.text = text;
		this.screenX=screenX;
		this.screenY=screenY;
		this.layer=layer;
		this.scale=scale;
		this.ticksToRemain=ticks;
		this.font = font;

		this.centerTextOnMultipleLines = centerTextOnMultipleLines;



		this.actionCaptionType = ActionManager.ACTIONCAPTIONTYPE_NONE;
		this.entity=entity;
		this.area = area;
		this.fadeLetterColorTowardsTop = fadeLetterColorTowardsTop;
		this.entityXWhenCreated=0;
		this.entityYWhenCreated=0;

		setEntity(entity);



		//handle fixed positions
		if(screenX<0)this.fixedPosition=(int)screenX;


		//TODO: width presets
		//WIDTH_FULL_SCREEN/scale*2 (default 2x scale, 0.5f scale will be actual 1x pixels)
		//WIDTH_HALF_SCREEN/scale*2
		//WIDTH_QUARTER_SCREEN/scale*2
		//if it doesn't fit, just split where necessary
		//if preferred width is 0 then put it all on a single line, unless it doesn't fit.
		if(maxWidth==0 || maxWidth == -1)
		{
			this.maxWidth = (int)(Engine().getWidth()/2/scale);
		}
		else
		{
			this.maxWidth = (int)(maxWidth);//TODO: experiment and see if i want this /scale
		}


		setTextColor(textColor,textAAColor,textBGColor);


		increaseMaxWidthToLongestWord();
		calculateTextureWidthAndHeightByParsingEachLine();

		if(width>this.maxWidth)width = this.maxWidth;

		//-----------------------------
		//allocate the indexed gfx data array, buffer, and texture
		//-----------------------------

		this.texWidth=Utils.getClosestPowerOfTwo(width);
		this.texHeight=Utils.getClosestPowerOfTwo(height);


		if(texture!=null)texture = GLUtils.releaseTexture(texture);
		textureByteArray = new byte[texWidth*texHeight*4];

		//direct method, uses ram outside of the JVM
		textureByteBuffer = ByteBuffer.allocateDirect(textureByteArray.length);
		textureByteBuffer.order(ByteOrder.nativeOrder());

		/*
		//TODO: do i need to do this here to init???
		textureByteBuffer.put(textureByteArray);
		textureByteBuffer.flip();
		*/



		for(int i=0; i<texWidth*texHeight; i++)
		{
			textureByteArray[(i*4)+0]=(byte)0;
			textureByteArray[(i*4)+1]=(byte)0;
			textureByteArray[(i*4)+2]=(byte)0;
			textureByteArray[(i*4)+3]=(byte)0;//255 for debug
		}


		boolean debug = false;
		if(debug==true)
		{
			for(int i=0; i<texWidth*texHeight; i++)
			{
				textureByteArray[(i*4)+0]=(byte)255;
				textureByteArray[(i*4)+1]=(byte)0;
				textureByteArray[(i*4)+2]=(byte)255;
				textureByteArray[(i*4)+3]=(byte)255;//255 for debug
			}

			for(int x=0; x<(maxWidth)&&x<texWidth; x++)
			{
				for(int y=0; y<(height); y++)
				{
					textureByteArray[(((y*texWidth)+x)*4)+0]=(byte)0;
					textureByteArray[(((y*texWidth)+x)*4)+1]=(byte)255;
					textureByteArray[(((y*texWidth)+x)*4)+2]=(byte)0;
					textureByteArray[(((y*texWidth)+x)*4)+3]=(byte)255;//255 for debug
				}
			}

			for(int x=0; x<(longestLineWidth); x++)
			{
				for(int y=0; y<(height); y++)
				{
					textureByteArray[(((y*texWidth)+x)*4)+0]=(byte)0;
					textureByteArray[(((y*texWidth)+x)*4)+1]=(byte)0;
					textureByteArray[(((y*texWidth)+x)*4)+2]=(byte)255;//255 for debug
					textureByteArray[(((y*texWidth)+x)*4)+3]=(byte)255;
				}
			}
		}



		drawText();

		textureByteBuffer.put(textureByteArray);
		textureByteBuffer.flip();

		this.texture = GLUtils.loadTexture(this.text, this.width, this.height, textureByteBuffer);

		this.init = true;

	}

	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================



		float tx0 = 0.0f;
		float tx1 = 1.0f;
		float ty0 = 0.0f;
		float ty1 = 1.0f;

		float x0 = 0;
		float x1 = 100;
		float y0 = 0;
		float y1 = 100;

		tx0 = 0.0f;
		tx1 = (float)width/(float)texWidth;
		ty0 = 0.0f;
		ty1 = (float)height/(float)texHeight;

		x0 = (screenX);
		x1 = ((screenX)+(width*scale));
		y0 = (screenY);
		y1 = ((screenY)+(height*scale));


		int filter=0;
		if(scale==0.5f || scale==1.0f || scale==2.0f)filter = GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING;
		else filter = GLUtils.FILTER_FBO_LINEAR_NO_MIPMAPPING;

		if(font.outlined && scale==0.5f)filter = GLUtils.FILTER_FBO_LINEAR_NO_MIPMAPPING;

		GLUtils.drawTexture(texture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,alpha,filter);
	}

	//=========================================================================================================================
	private void increaseMaxWidthToLongestWord()
	{//=========================================================================================================================

		//-----------------------------
		//go through string word by word, checking length of each word against the set width.
		//if a word won't fit, then we must increase the set width to fit that word.
		//-----------------------------

		int position=0;

		while(position<textCharacterLength)
		{
			//skip over newlines
			if(BobFont.isCurrentPositionANewline(text,position)==true)
			{
				//skip over <NEWLINE> and <NEXTLINE> and <.>
				if(text.charAt(position)=='<')
					while(text.charAt(position)!='>')position++;

				position++;//skip '\n' or '>'
				lines++;
				continue;
			}

			//skip over over tags
			if(text.charAt(position)=='<')
			{
				while(text.charAt(position)!='>')position++;
				position++;//skip '>'
				continue;
			}

			int nextWordLength=BobFont.getNextWordLength(text,position,font);

			if(text.charAt(position)==' ')
			{
				nextWordLength-=3;//skip the space (3 + 1)
				//if(font_id!=TM.FONT_OUTLINED_ID)
					nextWordLength--;
			}

			//-----------------------------
			//if any word is greater than set width, increase set width to word size
			//-----------------------------
			if(nextWordLength+1>maxWidth)
			{
				maxWidth = nextWordLength+1;//for the space at the beginning
			}

			//-----------------------------
			//skip next word, as we've added its length and we need to jump forward in the string
			//-----------------------------
			position=skipNextWord(position);
		}

	}
	//=========================================================================================================================
	private int skipNextWord(int position)
	{//=========================================================================================================================
		int nextWordPosition=position;

		while
		(
			nextWordPosition<textCharacterLength
			&&
			//we should be starting on a space or the beginning of the test. include the starting space, up to the next space
			(text.charAt(nextWordPosition)!=' '||nextWordPosition==position)//if it's the start of the string or it's not a space
			&&
			BobFont.isCurrentPositionANewline(text,nextWordPosition)==false
		)
		{
			//skip over tags
			while(text.charAt(nextWordPosition)=='<')
			{
				int x=0;
				while(nextWordPosition+x<textCharacterLength&&text.charAt(nextWordPosition+x)!='>')
				{
					x++;
				}
				nextWordPosition+=x;
			}

			nextWordPosition++;
		}

		return nextWordPosition;
	}


	//=========================================================================================================================
	private int getCurrentLineLength(int position)
	{//=========================================================================================================================

		int currentLineWidth=1;//for the space at the beginning

		while(position<textCharacterLength)
		{
			//-----------------------------
			//skip over newlines
			//-----------------------------
			if(BobFont.isCurrentPositionANewline(text,position)==true)
			{
				//skip over <NEWLINE> and <NEXTLINE> and <.>
				if(text.charAt(position)=='<')
					while(text.charAt(position)!='>')position++;

				position++;//skip '\n' or '>'

				return currentLineWidth;
			}

			//-----------------------------
			//skip over other tags
			//-----------------------------
			if(text.charAt(position)=='<')
			{
				while(text.charAt(position)!='>')position++;
				position++;//skip '>'
				continue;
			}

			int nextWordLength=BobFont.getNextWordLength(text,position,font);

			//-----------------------------
			//if the next word will fit within the set width, add it
			//-----------------------------
			if(currentLineWidth+nextWordLength<=maxWidth)
			{
				currentLineWidth+=nextWordLength;
			}
			else
			{
				return currentLineWidth;
			}


			//-----------------------------
			//skip next word, as we've added its length and we need to jump forward in the string
			//-----------------------------
			position=skipNextWord(position);

		}

		return currentLineWidth;
	}

	//=========================================================================================================================
	private void calculateTextureWidthAndHeightByParsingEachLine()
	{//=========================================================================================================================


		//-----------------------------
		//go through string word by word, checking length of each line against the set width.
		//find out how many lines we will need so we can set the graphics array size accordingly.
		//check for newlines and tags as well
		//-----------------------------

		lines=1;//we are on the first line
		longestLineWidth=0;

		{
			int position=0;
			int currentLineWidth=1;//for the space at the beginning

			while(position<textCharacterLength)
			{
				//skip over newlines
				if(BobFont.isCurrentPositionANewline(text,position)==true)
				{
					//skip over <NEWLINE> and <NEXTLINE> and <.>
					if(text.charAt(position)=='<')
						while(text.charAt(position)!='>')position++;

					position++;//skip '\n' or '>'
					lines++;
					currentLineWidth=1;
					continue;
				}

				//skip over other tags
				if(text.charAt(position)=='<')
				{
					while(text.charAt(position)!='>')position++;
					position++;//skip '>'
					continue;
				}

				int nextWordLength=BobFont.getNextWordLength(text,position,font);

				//-----------------------------
				//if the next word will fit within the set width, add it
				//-----------------------------
				if(currentLineWidth+nextWordLength<=maxWidth)
				{
					currentLineWidth+=nextWordLength;
				}
				else //add it to the next line
				{
					if(text.charAt(position)==' ')
					{
						nextWordLength-=3;//skip the space (3 + 1)
						//if(font_id!=TM.FONT_OUTLINED_ID)
							nextWordLength--;
					}

					lines++;
					currentLineWidth=nextWordLength+1;//for the space at the beginning
				}

				//-----------------------------
				//track longest line, make array size based on this
				//-----------------------------
				if(currentLineWidth>longestLineWidth)longestLineWidth=currentLineWidth;


				//-----------------------------
				//skip next word, as we've added its length and we need to jump forward in the string
				//-----------------------------
				position=skipNextWord(position);

			}
		}

		//-----------------------------
		//now temp_position should be at the end of the string
		//-----------------------------

		width=longestLineWidth;
		height=(font.maxCharHeight+2)*(lines);

		//DebugConsole.add("Caption longest line pixel width: " + caption_width);
		//DebugConsole.add("Caption lines: " + lines);


	}


	//=========================================================================================================================
	private void drawText()
	{//=========================================================================================================================

		//-----------------------------
		//fill the indexed gfx data with text
		//-----------------------------

		this.xInLine=0;
		this.line=0;




		int position=0;

		while(position<textCharacterLength)
		{

			if(xInLine==0)
			{
				//draw the space at the beginning
				drawBlankColumn();
				xInLine++;

				if(centerTextOnMultipleLines)
				{
					//get size of line remaining
					//see how many words we can fit into it
					//get the length of those words

					int lineWidthOnThisLine = getCurrentLineLength(position);

					//skip (width - length) / 2 space before start drawing
					if(lineWidthOnThisLine<maxWidth)
					{
						int leftover = maxWidth - lineWidthOnThisLine;

						for(int i=0;i<leftover/2 - 1;i++)
						{
							drawBlankColumn();
							xInLine++;
						}
					}
				}
			}


			//check each word length and start a new line if it is too long to fit
			if(position==0||text.charAt(position)==' ')//if we're on a space
			{
				int nextWordLength=BobFont.getNextWordLength(text,position, font);

				if(xInLine+nextWordLength>maxWidth)//if the next word won't fit in the remaining space
				{
					//skip the space on the newline
					if(text.charAt(position)==' ')position++;

					line++;
					xInLine=0;
					continue;
				}
			}

			if(BobFont.isCurrentPositionANewline(text,position)==true)
			{

				//skip over tags here
				if(text.charAt(position)=='<')
				while(text.charAt(position)!='>')position++;

				//now we are on '>'
				position++;//skip the '>'

				line++;
				xInLine=0;
				continue;
			}


			if(text.charAt(position)=='<')
			{
				position++;
				int optionLength=0;
				while
					(
						text.charAt(position+optionLength)!='>'
						&&
						position+optionLength<textCharacterLength
					)
					{
						optionLength++;
					}

					parseOptions(text.substring(position,position+optionLength));

					position+=optionLength;

					//string position is now on '>'
					position++;//skip the '>'

					continue;

			}



			int i = BobFont.getFontIndexForChar(text.charAt(position));
			drawLetter(i);
			position++;

		}



	}


	//=========================================================================================================================
	private void parseOptions(String optionBuffer)
	{//=========================================================================================================================

		if(optionBuffer.compareTo("BLACK")==0)
		{
			textBGColor = BobColor.WHITE;
			textColor = BobColor.BLACK;
			textAAColor = BobColor.LIGHTGRAY;

		}
		else
		if(optionBuffer.compareTo("WHITE")==0)
		{
			textBGColor = BobColor.BLACK;
			textColor = BobColor.WHITE;
			textAAColor = BobColor.GRAY;

		}
		else
		if(optionBuffer.compareTo("GRAY")==0)
		{
			textColor = BobColor.GRAY;
			if(textBGColor==BobColor.BLACK)textAAColor=BobColor.DARKGRAY;else if(textBGColor==BobColor.WHITE)textAAColor=BobColor.LIGHTGRAY;

		}
		else
		if(optionBuffer.compareTo("RED")==0)
		{
			textColor = BobColor.RED;
			if(textBGColor==BobColor.BLACK)textAAColor=BobColor.DARKRED;else if(textBGColor==BobColor.WHITE)textAAColor=BobColor.LIGHTRED;

		}
		else
		if(optionBuffer.compareTo("ORANGE")==0)
		{
			textColor = BobColor.ORANGE;
			if(textBGColor==BobColor.BLACK)textAAColor=BobColor.DARKORANGE;else if(textBGColor==BobColor.WHITE)textAAColor=BobColor.LIGHTORANGE;

		}
		else
		if(optionBuffer.compareTo("YELLOW")==0)
		{
			textColor = BobColor.YELLOW;
			if(textBGColor==BobColor.BLACK)textAAColor=BobColor.DARKYELLOW;else if(textBGColor==BobColor.WHITE)textAAColor=BobColor.LIGHTYELLOW;

		}
		else
		if(optionBuffer.compareTo("GREEN")==0)
		{
			textColor = BobColor.GREEN;
			if(textBGColor==BobColor.BLACK)textAAColor=BobColor.DARKGREEN;else if(textBGColor==BobColor.WHITE)textAAColor=BobColor.LIGHTGREEN;

		}
		else
		if(optionBuffer.compareTo("BLUE")==0)
		{
			textColor = BobColor.BLUE;
			if(textBGColor==BobColor.BLACK)textAAColor=BobColor.DARKBLUE;else if(textBGColor==BobColor.WHITE)textAAColor=BobColor.LIGHTBLUE;

		}
		else
		if(optionBuffer.compareTo("PURPLE")==0)
		{
			textColor = BobColor.PURPLE;
			if(textBGColor==BobColor.BLACK)textAAColor=BobColor.DARKPURPLE;else if(textBGColor==BobColor.WHITE)textAAColor=BobColor.LIGHTPURPLE;

		}
		else
		if(optionBuffer.compareTo("PINK")==0)
		{
			textColor = BobColor.PINK;
			if(textBGColor==BobColor.BLACK)textAAColor=BobColor.DARKPINK;else if(textBGColor==BobColor.WHITE)textAAColor=BobColor.LIGHTPINK;

		}
		else
		if(optionBuffer.compareTo("BGBLACK")==0)
		{
			textBGColor = BobColor.BLACK;
			//TODO: if(textColor==COLOR)textAAColor=DARKCOLOR;
		}
		else
		if(optionBuffer.compareTo("BGWHITE")==0)
		{
			textBGColor = BobColor.WHITE;
			//if(textColor==COLOR)textAAColor=LIGHTCOLOR;
		}
		else
		if(optionBuffer.compareTo("BGCLEAR")==0)
		{
			textBGColor = BobColor.CLEAR;
			//if(textColor==COLOR)textAAColor=LIGHTCOLOR;
		}
		else
		{
			Console.debug("Unknown text tag: "+optionBuffer);
		}
		//TODO: handle other useful tags


	}

	//=========================================================================================================================
	private int getLetterPixelColor(int letterIndex, int y, int xInLetter, int blank)
	{//=========================================================================================================================


		if(blank==1)return 0;

		int index = BobFont.getFontPixelValueAtIndex((letterIndex*font.blockHeight*font.blockWidth)+(y*font.blockWidth)+xInLetter, font);

		return index;


	}

	//=========================================================================================================================
	private void setPixel(int index, BobColor c)
	{//=========================================================================================================================


		textureByteArray[index+0] = (byte)c.getRed();
		textureByteArray[index+1] = (byte)c.getGreen();
		textureByteArray[index+2] = (byte)c.getBlue();
		textureByteArray[index+3] = (byte)c.getAlpha();


	}


	//=========================================================================================================================
	public float getAlphaTo()
	{//=========================================================================================================================
		return alphaTo;
	}

	//=========================================================================================================================
	public float getAlpha()
	{//=========================================================================================================================
		return alpha;
	}

	//=========================================================================================================================
	public void setAlphaTo(float a)
	{//=========================================================================================================================
		if(delete==false)alphaTo = a;
	}

	//=========================================================================================================================
	public void setAlphaImmediately(float a)
	{//=========================================================================================================================
		alpha = a;
	}


	//=========================================================================================================================
	public float getWidth()
	{//=========================================================================================================================
		return width*scale;
	}


	//=========================================================================================================================
	public float getHeight()
	{//=========================================================================================================================
		return height*scale;
	}

	//=========================================================================================================================
	private void drawBlankColumn()
	{//=========================================================================================================================
		drawColumn(0,0,1);
	}
	//=========================================================================================================================
	private void drawColumn(int xInLetter, int letterIndex, int blank)
	{//=========================================================================================================================

		int y;

		for(y=0; y<font.maxCharHeight+2; y++)
		{

			int index = 0;

			//set the top pixel black
			if(y==0) index = getLetterPixelColor(letterIndex,y-1,xInLetter,1);
			else index = getLetterPixelColor(letterIndex,y-1,xInLetter,blank);

			BobColor c = null;

			if(index==0)c = textBGColor;
			if(index==1)c = textColor;
			if(index==2)c = textAAColor;

			if(index>2)//additional aa pixels, use the color value to set the opacity
			{
				BobColor tc = textColor;

				//get the gray color from the text palette
				int byte1 = (int)(BobFont.font_Palette_ByteArray[index*2+0]&255);
				int byte2 = (int)(BobFont.font_Palette_ByteArray[index*2+1]&255);
				int abgr1555 = byte2<<8+byte1;
				int r = 255-(int)((((byte1&31))/32.0f)*255.0f);
				//int r = 255-(int)((((byte1&0b00011111))/32.0f)*255.0f);
				//Color gray = new BobColor(b,b,b);



				int a = r;//gray.getRed();
				if(a<0)a=0;

				a*=textAAColor.a();
				c = new BobColor(tc.getRed(),tc.getGreen(),tc.getBlue(),a);

			}


			if(fadeLetterColorTowardsTop)
			{
				if((index>0)&&y<font.maxCharHeight*0.75f&&(index!=2||font.outlined==false))
				{

					int r = (int) Math.min(255,c.getRed()+(((float)(font.maxCharHeight-y)/(float)font.maxCharHeight)*255.0f));
					int g = (int) Math.min(255,c.getGreen()+(((float)(font.maxCharHeight-y)/(float)font.maxCharHeight)*255.0f));
					int b = (int) Math.min(255,c.getBlue()+(((float)(font.maxCharHeight-y)/(float)font.maxCharHeight)*255.0f));
					int a = c.getAlpha();

					c = new BobColor(r,g,b,a);

				}
			}
			//draw each pixel 4 times (2x scale)
			//for(int yy=0;yy<2;yy++)
				//for(int xx=0;xx<2;xx++)
				{
					int lineIndex = (texWidth*line*((font.maxCharHeight+2)));
					int xIndex = ((xInLine));
					int yIndex = (texWidth*((y)));

					setPixel((lineIndex+yIndex+xIndex)*4,c);
				}


		}

	}
	//=========================================================================================================================
	private void drawLetter(int letterIndex)
	{//=========================================================================================================================

		int letterWidth = BobFont.getCharWidth(letterIndex, font);

		int xInLetter=0;
		for(xInLetter=0;xInLetter<letterWidth;xInLetter++)
		{

			drawColumn(xInLetter,letterIndex, 0);
			xInLine++;
		}

		//-----------------------------
		//insert space (blank column)
		//-----------------------------
		//if(font_id!=TM.FONT_OUTLINED_ID)
		{
			drawBlankColumn();
			xInLine++;
		}

	}


	//=========================================================================================================================
	public void updateScreenXY()
	{//=========================================================================================================================

		//TODO: track how many captions are centered over sprite, make sure they aren't covering each other

		//-----------------------------
		//set caption screen x and y
		//-----------------------------
		if(fixedPosition==Caption.CENTERED_OVER_ENTITY)
		{

			if(entity!=null)
			{
				screenX=(float)Math.floor(entity.screenLeft()+(entity.w()*Cameraman().getZoom()/2.0f))-(width*scale/2.0f);//no g.zoom on caption width, they arent affected by zoom!


				int captionOverHeadOffset = 0;
				for(int i=CaptionManager().captionList.size()-1;i>=0;i--)
				{
					Caption tempC = CaptionManager().captionList.get(i);
					if(tempC.fixedPosition==Caption.CENTERED_OVER_ENTITY)
					{
						if(tempC==this)break;

						captionOverHeadOffset+=(tempC.height+2)*tempC.scale;
					}
				}

				screenY=(float)Math.floor(entity.screenTop())-(captionOverHeadOffset+(height+2)*scale);
			}

		}
		else
		if(fixedPosition==Caption.CENTERED_SCREEN)
		{
			screenX=((Engine().getWidth()/2)-((int)(width*scale)/2));
			screenY=(Engine().getHeight()/2);

		}
		else
		if(fixedPosition==Caption.CENTERED_X)
		{
			screenX=((Engine().getWidth()/2)-((int)(width*scale)/2));
		}

		//-----------------------------
		//don't let captions wrap offscreen
		//-----------------------------
		if(screenX+width*scale>=Engine().getWidth())
		{
			screenX=Engine().getWidth()-(int)(width*scale+1);
		}
		if(screenX<0)screenX=0;

		///turned off for castroom
		//TODO: make this an option

		if(screenY+font.maxCharHeight>=Engine().getHeight())
		{
			screenY=Engine().getHeight()-(font.maxCharHeight+1);
		}

		if(screenY<0)screenY=0;
	}

	//=========================================================================================================================
	public void deleteFadeOut()
	{//=========================================================================================================================
		delete = true;

	}

	//=========================================================================================================================
	public void deleteImmediately()
	{//=========================================================================================================================
		delete = true;
		alpha = 0.0f;
	}

	//=========================================================================================================================
	public boolean getDeleteStatus()
	{//=========================================================================================================================
		return delete;
	}

	public int flashingTicksCount = 0;
	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		ticksAge += Engine().engineTicksPassed();

		updateScreenXY();

		//-----------------------------
		//delete if sprite moved
		//-----------------------------
		if(
			ticksToRemain==0
			||
			(
				ticksToRemain==Caption.DELETE_WHEN_MAIN_SPRITE_MOVES
				&&
				(
					entity!=null
					&&
					(
						entity.x()!=entityXWhenCreated//and sprite has moved
						||
						entity.y()!=entityYWhenCreated
					)
				)
			)
		)
		{
			delete=true;
		}


		if(delete==true)
		{
			alphaTo=0.0f;
		}

		if(flashing && delete==false)
		{

			flashingTicksCount += Engine().engineTicksPassed();

			if(flashingTicksCount>flashingTicksPerFlash)
			{
				flashingTicksCount = 0;
			}

			if(flashingTicksCount<flashingTicksPerFlash/2)
			{

				alpha = ((float)flashingTicksCount / ((float)flashingTicksPerFlash/3.0f)) * alphaTo;
				if(alpha>alphaTo)alpha = alphaTo;
				if(alpha<0.0f)alpha = 0.0f;
			}
			else
			{

				alpha = ((float)(flashingTicksPerFlash - flashingTicksCount) / ((float)flashingTicksPerFlash/3.0f)) * alphaTo;

				if(alpha>alphaTo)alpha = alphaTo;
				if(alpha<0.0f)alpha = 0.0f;

			}

		}
		else
		{

			//-----------------------------
			//do fade in/out
			//-----------------------------

			if(alpha!=alphaTo)
			{
				if(alpha>alphaTo)
				{
					alpha-=0.005f*Engine().engineTicksPassed();
					if(alpha<alphaTo)alpha=alphaTo;
				}

				if(alpha<alphaTo)
				{
					alpha+=0.005f*Engine().engineTicksPassed();
					if(alpha>alphaTo)alpha=alphaTo;
				}

			}
		}



		//-----------------------------
		//delete if delete is 1
		//-----------------------------
		if(delete==true&&alpha==0.0f)
		{
			alpha=0.0f;

			if(texture!=null)
			{
				texture=GLUtils.releaseTexture(texture);
			}
			textureByteBuffer = null;
			textureByteArray = null;

			CaptionManager().captionList.remove(this);

		}



	}

	public void setEntity(Entity e)
	{
		this.entity = e;

		if(e==null&&Player()!=null)
		{
			this.entity = Player();
		}

		if(this.entity!=null)
		{
			this.entityXWhenCreated=this.entity.x();
			this.entityYWhenCreated=this.entity.y();
		}
	}



}
