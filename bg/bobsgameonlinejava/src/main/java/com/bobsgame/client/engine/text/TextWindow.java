package com.bobsgame.client.engine.text;



//import static org.lwjgl.opengl.GL13.*;
//import static org.lwjgl.opengl.GL14.*;
//import static org.lwjgl.opengl.GL15.*;
//import static org.lwjgl.opengl.GL20.*;
//import static org.lwjgl.opengl.GL21.*;
//import static org.lwjgl.opengl.GL30.*;
//import static org.lwjgl.opengl.GL31.*;
//import static org.lwjgl.opengl.GL32.*;
//import static org.lwjgl.opengl.GL33.*;
//import static org.lwjgl.opengl.GL40.*;
//import static org.lwjgl.opengl.GL41.*;
//import static org.lwjgl.opengl.GL42.*;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

//import org.lwjgl.input.Keyboard;
        import org.slf4j.LoggerFactory;

import com.bobsgame.client.Texture;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.engine.game.gui.statusbar.StatusBar;
import com.bobsgame.shared.BobColor;
        import com.bobsgame.client.GLUtils;
import com.bobsgame.client.console.Console;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.entity.Entity;
import com.bobsgame.client.engine.entity.RandomCharacter;
import com.bobsgame.client.engine.game.Player;



//=========================================================================================================================
public class TextWindow extends EnginePart
{// =========================================================================================================================



	public static Logger log=(Logger)LoggerFactory.getLogger(TextWindow.class);


	public Texture textBoxTexture;
	public Texture spriteBoxTexture;
	public Texture borderTexture;


	public float scrollPercent=0;

	public byte[] textBoxTextureByteArray;
	public ByteBuffer textBoxTexturePixelsByteBuffer;

	public byte[] spriteWindowTextureByteArray;
	public ByteBuffer spriteWindowTexturePixelsByteBuffer;



	public float voicePitch=0;
	String label="";

	public int xInLine=0;
	public int line=0;

	public Entity spriteWindowEntity=null;

	public Texture spriteWindowTexture=null;

	public boolean redraw=false;

	public float alpha=1.0f;



	public int shakeTicksXTotal=0;
	//public int shakeTicksLeft=0;
	public int shakeTicksLeftRightCounter=0;
	public float shakeX = 0;
	public int shakeMaxX = 2;
	public boolean shakeLeftRightToggle = false;


	public int shakeTicksYTotal=0;
	//public int shakeTicksLeft=0;
	public int shakeTicksUpDownCounter=0;
	public float shakeY = 0;
	public int shakeMaxY = 2;
	public boolean shakeUpDownToggle = false;
	// =========================================================================================================================
	public TextWindow(Engine g)
	{// =========================================================================================================================

		super(g);

		borderTexture=GLUtils.loadTexture("res/textbox/border.png");


		spriteBoxTexture=GLUtils.loadTexture("spriteWindow",64,64,spriteWindowTexturePixelsByteBuffer);



		scrollPercent=0;

	}



	// =========================================================================================================================
	public void init()
	{// =========================================================================================================================


		spriteWindowEntity=null;

		textBoxTextureByteArray=new byte[TextManager().pow2TexWidth*TextManager().pow2TexHeight*4];


		// direct method, uses ram outside of the JVM
		textBoxTexturePixelsByteBuffer=ByteBuffer.allocateDirect(textBoxTextureByteArray.length);
		textBoxTexturePixelsByteBuffer.order(ByteOrder.nativeOrder());


//		for(int i=0;i<TextManager().textureWidth*TextManager().textureHeight;i++)
//		{
//			textBoxTextureByteArray[(i*4)+0]=(byte)0;
//			textBoxTextureByteArray[(i*4)+1]=(byte)0;
//			textBoxTextureByteArray[(i*4)+2]=(byte)0;
//			textBoxTextureByteArray[(i*4)+3]=(byte)0;
//		}

		clearByteArray();

		textBoxTexturePixelsByteBuffer.put(textBoxTextureByteArray);
		textBoxTexturePixelsByteBuffer.flip();



		textBoxTexture=GLUtils.loadTexture("textBox",TextManager().width,TextManager().height,textBoxTexturePixelsByteBuffer);



		// ----------------------------
		// sprite window
		// ----------------------------

		spriteWindowTextureByteArray=new byte[((64)*(64))*4];

		// direct method, uses ram outside of the JVM
		spriteWindowTexturePixelsByteBuffer=ByteBuffer.allocateDirect(spriteWindowTextureByteArray.length);
		spriteWindowTexturePixelsByteBuffer.order(ByteOrder.nativeOrder());

		for(int i=0;i<(64)*(64);i++)
		{
			spriteWindowTextureByteArray[(i*4)+0]=(byte)0;
			spriteWindowTextureByteArray[(i*4)+1]=(byte)0;
			spriteWindowTextureByteArray[(i*4)+2]=(byte)0;
			spriteWindowTextureByteArray[(i*4)+3]=(byte)255;
		}

		spriteWindowTexturePixelsByteBuffer.put(spriteWindowTextureByteArray);
		spriteWindowTexturePixelsByteBuffer.flip();

	}



	// =========================================================================================================================
	public void render()
	{// =========================================================================================================================



		//render text window at 25% screen height, let's make "scroll in" a float where 1.0 is height + 16px or whatever

		int screenWidth = (int)Engine().getWidth();
		int screenHeight = (int)Engine().getHeight();
		float scaledTextWindowHeight = screenHeight * 0.15f;//not including borders!

		float widthToHeightRatio = (float)TextManager().width / (float)TextManager().height;
		float scaledTextWindowWidth = scaledTextWindowHeight * widthToHeightRatio;

		float heightScale = scaledTextWindowHeight / (float)TextManager().height;

		float widthScale = scaledTextWindowWidth / (float)TextManager().width;
		float scaledSpriteWindowWidth  = TextManager().spriteWindowWidth * widthScale;

		float borderWidth = 10;
		float scaledBorderWidth =  borderWidth * widthScale;

		float borderHeight = 16;
		float scaledBorderHeight =  borderHeight * heightScale;

		float totalScaledWidth = scaledTextWindowWidth + scaledSpriteWindowWidth + scaledBorderWidth*3;
		float totalScaledHeight = scaledTextWindowHeight + scaledBorderHeight*2;

		if(totalScaledWidth > Engine().getWidth()*0.90f)
		{
			//scale width to 90%
			//scale height from that
			scaledTextWindowWidth = (float)(Engine().getWidth()*0.75f);
			widthScale = scaledTextWindowWidth / (float)TextManager().width;
			scaledSpriteWindowWidth  = TextManager().spriteWindowWidth * widthScale;

			float heightToWidthRatio = (float)TextManager().height / (float)TextManager().width;
			scaledTextWindowHeight = scaledTextWindowWidth / widthToHeightRatio;
			heightScale = scaledTextWindowHeight / (float)TextManager().height;

			scaledBorderWidth =  borderWidth * widthScale;
			scaledBorderHeight =  borderHeight * heightScale;
			totalScaledWidth = scaledTextWindowWidth + scaledSpriteWindowWidth + scaledBorderWidth*3;
			totalScaledHeight = scaledTextWindowHeight + scaledBorderHeight*2;
		}



		float tx0=0.0f;
		float tx1=1.0f;
		float ty0=0.0f;
		float ty1=1.0f;

		float x0=0;
		float x1=0;
		float y0=0;
		float y1=0;


		float y = 0;
		//scroll from bottom
		float startScrollPosition = Engine().getHeight();
		float finalScrollPosition = Engine().getHeight() - totalScaledHeight - 16;

		if(this==TextManager().textBox[1])
		{
			//scroll from top
			startScrollPosition = 0 - totalScaledHeight;
			finalScrollPosition = 0 + StatusBar.sizeY + 16;
		}
		y = (startScrollPosition + (finalScrollPosition - startScrollPosition)*scrollPercent) + shakeY;


		float x = ((screenWidth - totalScaledWidth) / 2) + shakeX;



		// -----------------------
		// border
		// ----------------------

		tx0=0.0f;// 672 x 160
		tx1=672.0f/borderTexture.getTextureWidth();
		ty0=0.0f;
		ty1=160.0f/borderTexture.getTextureHeight();


//		x0=(int)((screenX)-(TextManager().spriteWindowWidth))-16;
//		x1=(int)(screenX)+(TextManager().textWindowWidth)+16;
//		y0=(int)(screenY-16);
//		y1=(int)(screenY)+(TextManager().textWindowHeight)+16;



		x0=x;
		x1=x0+totalScaledWidth;
		y0=y;
		y1=y0+totalScaledHeight;


		GLUtils.drawTexture(borderTexture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,alpha,GLUtils.FILTER_NEAREST);

		// ------------------
		// text box itself
		// ------------------

		tx0=0.0f;
		tx1=(float)textBoxTexture.getImageWidth()/(float)textBoxTexture.getTextureWidth();
		ty0=0.0f;
		ty1=(float)textBoxTexture.getImageHeight()/(float)textBoxTexture.getTextureHeight();

//		x0=(int)(screenX);
//		x1=(int)((screenX)+(TextManager().textWindowWidth));
//		y0=(int)(screenY);
//		y1=(int)((screenY)+(TextManager().textWindowHeight));

		x0=x+scaledBorderWidth+scaledSpriteWindowWidth+scaledBorderWidth;
		x1=x0+scaledTextWindowWidth;
		y0=y+scaledBorderHeight;
		y1=y0+scaledTextWindowHeight;

		GLUtils.drawTexture(textBoxTexture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,alpha,GLUtils.FILTER_LINEAR);

		// -----------------------
		// sprite window
		// ----------------------

		/*
		 * spriteBoxTexture.bind();
		 * tx0 = 0.0f;
		 * tx1 = 1.0f;
		 * ty0 = 0.0f;
		 * ty1 = 1.0f;
		 * x0 = (int)((screen_x)-(64*2));
		 * x1 = (int)(screen_x);
		 * y0 = (int)(screen_y);
		 * y1 = (int)((screen_y)+(G.textManager.size_y));
		 * draw_texture(tx0, tx1, ty0, ty1, x0, x1, y0, y1);
		 */

		// ----------------------
		// sprite window sprite
		// ----------------------

		tx0=0.0f;
		tx1=1.0f;
		ty0=0.0f;
		ty1=1.0f;

//		x0=(int)((screenX)-((64*2)));
//		x1=(int)(screenX);
//		y0=(int)(screenY);
//		y1=(int)((screenY)+(64*2));

		x0=x+scaledBorderWidth;
		x1=x0+scaledSpriteWindowWidth;
		y0=y+scaledBorderHeight;
		y1=y0+scaledTextWindowHeight;

		// if(sprite_window_gfx==null)sprite_window_gfx = TM.questionMarkTexture;

		GLUtils.drawTexture(spriteBoxTexture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,alpha,GLUtils.FILTER_NEAREST);


		// ----------------------
		// label underneath sprite window
		// ----------------------
		/*
		 * if(sprite_window_npc==null)
		 * {
		 * sprite_window_npc = G.cameraman;
		 * }
		 * else
		 * {
		 * label = sprite_window_npc.name;
		 * }
		 * if(sprite_window_npc==G.cameraman)
		 * {
		 * label = "???";
		 * }
		 */
		//TextManager().ttfFont.drawString(x0+48,y1+10-6,label,BobColor.white);//TODO






		if(this==TextManager().textBox[TextManager().selectedTextbox])
		{
			tx0=0.0f;
			tx1=1.0f;
			ty0=0.0f;
			ty1=1.0f;


			x0=x+scaledBorderWidth+scaledSpriteWindowWidth+scaledBorderWidth+scaledTextWindowWidth;
			x1=x0+16;
			y0=y+scaledBorderHeight+scaledTextWindowHeight;
			//if(TextManager().buttonIconUpDownToggle)y0-=1;
			y1=y0+16;

			TextManager().actionIconScreenSprite.setX(x0-36);
			TextManager().actionIconScreenSprite.setY(y0-20);

			//GLUtils.drawTexture(spriteBoxTexture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,alpha,GLUtils.FILTER_NEAREST);

		}




	}



	// =========================================================================================================================
	void updateSpriteWindowTexture()
	{// =========================================================================================================================



		byte[] oldtex=spriteWindowTexture.getTextureData();
		int size_x=spriteWindowTexture.getTextureWidth();
		int size_y=spriteWindowTexture.getTextureHeight();


		// go through sprite texture data, which should be 32 x 64 or 32 x 32
		// find top pixel by shooting rays down from top to bottom for 0-32
		int top_filled_pixel=size_y;
		for(int x=0;x<32;x++)
		{
			for(int y=0;y<size_y;y++)
			{
				// skip checking y values lower than the previous known top pixel, dont need them
				if(y>=top_filled_pixel)
				{
					break;
				}

				if(oldtex[((size_x*y)+x)*4+0]!=(byte)0||	// r
				oldtex[((size_x*y)+x)*4+1]!=(byte)0||	// g
				oldtex[((size_x*y)+x)*4+2]!=(byte)0	// b
				)
				{
					if(y<top_filled_pixel) top_filled_pixel=y;
					break;
				}
			}
		}


		// make 64 * 64 pixel box
		byte newtex[]=new byte[64*64*4];

		// fill with transparent
		for(int i=0;i<64*64*4;i++)
			newtex[i]=(byte)0;


		// take 32 x 32 pixels starting at line *above* top pixel (so there is one empty line), draw them float sized into 64 * 64 box
		// if (top pixel-1) + 32 is more than bottom, break and leave transparent.

		for(int y=top_filled_pixel;y<top_filled_pixel+31&&y<size_y;y++)
		{
			for(int x=0;x<32;x++)
			{
				byte r=oldtex[((size_x*y)+x)*4+0];
				byte g=oldtex[((size_x*y)+x)*4+1];
				byte b=oldtex[((size_x*y)+x)*4+2];
				byte a=oldtex[((size_x*y)+x)*4+3];


				for(int xx=0;xx<2;xx++)
					for(int yy=0;yy<2;yy++)
					{
						int newy=(y+1)-top_filled_pixel;

						newtex[(((64*(((newy)*2)+yy))+((x*2)+xx))*4)+0]=r;
						newtex[(((64*(((newy)*2)+yy))+((x*2)+xx))*4)+1]=g;
						newtex[(((64*(((newy)*2)+yy))+((x*2)+xx))*4)+2]=b;
						newtex[(((64*(((newy)*2)+yy))+((x*2)+xx))*4)+3]=a;
					}
			}
		}



		// go through each pixel
		// if a pixel isn't transparent and isn't completely white (so it ignores already-outlined areas)
		// if the surrounding pixels are transparent, set it to white.
		for(int t=127-32;t>=0;t-=16)
		{
			for(int x=0;x<64;x++)
			{
				for(int y=0;y<64;y++)
				{
					if(newtex[((64*y)+x)*4+3]!=(byte)0
							&&
							(
							newtex[((64*y)+x)*4+0]!=(byte)t||	// r
									newtex[((64*y)+x)*4+1]!=(byte)t||	// g
							newtex[((64*y)+x)*4+2]!=(byte)t		// b
							))
					{
						for(int i=0;i<8;i++)
						{
							int xx=0;
							int yy=0;

							if(i==0)
							{
								xx=-1;
								yy=0;
							}
							if(i==1)
							{
								xx=1;
								yy=0;
							}
							if(i==2)
							{
								xx=0;
								yy=-1;
							}
							if(i==3)
							{
								xx=0;
								yy=1;
							}

							if(i==4)
							{
								xx=-1;
								yy=1;
							}
							if(i==5)
							{
								xx=1;
								yy=-1;
							}
							if(i==6)
							{
								xx=-1;
								yy=-1;
							}
							if(i==7)
							{
								xx=1;
								yy=1;
							}

							if(y+yy>=0&&y+yy<64&&x+xx>=0&&x+xx<64)
							{
								if(newtex[((64*(y+yy))+(x+xx))*4+3]==(byte)0)
								{
									newtex[((64*(y+yy))+(x+xx))*4+0]=(byte)t;
									newtex[((64*(y+yy))+(x+xx))*4+1]=(byte)t;
									newtex[((64*(y+yy))+(x+xx))*4+2]=(byte)t;
									newtex[((64*(y+yy))+(x+xx))*4+3]=(byte)t;
								}
							}
						}
					}
				}
			}
		}

		// make texture from new 64*64 array
		spriteWindowTexturePixelsByteBuffer.put(newtex);
		spriteWindowTexturePixelsByteBuffer.flip();

		spriteBoxTexture=GLUtils.releaseTexture(spriteBoxTexture);
		spriteBoxTexture=GLUtils.loadTexture("spriteWindow",64,64,spriteWindowTexturePixelsByteBuffer);

		/*
		 * int textureHandle = spriteBoxTexture.getTextureID();
		 * glBindTexture(GL_TEXTURE_2D,textureHandle);
		 * glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		 * glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		 * glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL11.GL_NEAREST);
		 * glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL11.GL_NEAREST);
		 * glTexImage2D(GL_TEXTURE_2D, //type of texture we're creating
		 * 0, //level-of-detail: use 0
		 * GL_RGBA, //texture pixel format
		 * 64, 64, //width and height of texture image (powers of 2)
		 * 0, //width of the border (either 0 or 1, use 0)
		 * GL_RGBA, //image pixel format
		 * GL_UNSIGNED_BYTE, //image pixel data type
		 * spriteWindowTexturePixelsByteBuffer//image pixel data
		 * );
		 */

	}


	// =========================================================================================================================
	public void setSpriteWindow(Entity entity,Texture texture,String newLabel)
	{// =========================================================================================================================

		if(entity!=null||texture!=null)
		{

			// if no texture is input, just take it from the entity
			if(entity!=null&&texture==null)
			{

				voicePitch=entity.voicePitch();

				if((entity.getClass().equals(Player.class))) texture=((Player)entity).uniqueTexture;
				if((entity.getClass().equals(RandomCharacter.class))) texture=((RandomCharacter)entity).uniqueTexture;


				if(texture==null&&entity.sprite!=null) texture=entity.sprite.texture;

				if(texture==null||texture==GLUtils.blankTexture) texture=TextManager.questionMarkTexture;


				if(newLabel==null)
				{
					if(entity!=null)
					{
						if(entity.sprite!=null)label=entity.sprite.displayName();
					}

				}
				else label=newLabel;

			}

			// if there isn't an entity, stay on camera. this way just putting in a gfx works, but the camera won't try to move
			if(entity==null)
			{
				entity=Cameraman();
				voicePitch=0;

				if(newLabel!=null) label=newLabel;
				else label="???";
			}

			// else, follow npc and use gfx for sprite window :)
			spriteWindowEntity=entity;
            if(entity!=null) voicePitch=entity.voicePitch();
			spriteWindowTexture=texture;




			// if(TM.GLOBAL_text_engine_state!=TM.CLOSED)
			// {
			updateSpriteWindowTexture();

			// }
		}
		else
		{

			String e="Tried to update sprite window with both npc and gfx null.";
			Console.error(e);
			log.error(e);

		}

	}


	// =========================================================================================================================
	void updateTextureFromByteArray()
	{// =========================================================================================================================

		if(redraw==true)
		{

			textBoxTexturePixelsByteBuffer.put(textBoxTextureByteArray);
			textBoxTexturePixelsByteBuffer.flip();

			// TODO: it might actually be more efficient to overwrite the previous texture, the way i had it before, instead of releasing and recreating.

			textBoxTexture=GLUtils.releaseTexture(textBoxTexture);

			textBoxTexture=GLUtils.loadTexture("textBox",TextManager().width,TextManager().height,textBoxTexturePixelsByteBuffer);

			redraw=false;
		}


	}



	// =========================================================================================================================
	void clearByteArray()
	{// =========================================================================================================================
		for(int x=0;x<TextManager().pow2TexWidth;x++)
		for(int y=0;y<TextManager().pow2TexHeight;y++)
		{
			textBoxTextureByteArray[((x+(y*TextManager().pow2TexWidth))*4)+0]=(byte)0;
			textBoxTextureByteArray[((x+(y*TextManager().pow2TexWidth))*4)+1]=(byte)0;
			textBoxTextureByteArray[((x+(y*TextManager().pow2TexWidth))*4)+2]=(byte)0;
			textBoxTextureByteArray[((x+(y*TextManager().pow2TexWidth))*4)+3]=(byte)0;

			if(x<TextManager().width && y<TextManager().height)
			textBoxTextureByteArray[((x+(y*TextManager().pow2TexWidth))*4)+3]=(byte)255;
		}
	}



	// =========================================================================================================================
	int getPixelValue(int letter_index,int y,int x_in_letter,int blank)
	{// =========================================================================================================================


		if(blank==1) return 0;

		int index=BobFont.getFontPixelValueAtIndex((letter_index*TextManager().font.blockHeight*TextManager().font.blockWidth)+(y*TextManager().font.blockWidth)+x_in_letter,TextManager().font);

		return index;


	}


	// =========================================================================================================================
	void setPixel(int index,BobColor c)
	{// =========================================================================================================================


		textBoxTextureByteArray[index+0]=(byte)c.getRed();
		textBoxTextureByteArray[index+1]=(byte)c.getGreen();
		textBoxTextureByteArray[index+2]=(byte)c.getBlue();
		textBoxTextureByteArray[index+3]=(byte)c.getAlpha();// was 255


	}


	// =========================================================================================================================
	void drawColumn(int letter_index,int x_in_letter,int blank)
	{// =========================================================================================================================


		int y=0;
		int h=TextManager().font.maxCharHeight;

		boolean draw2X=true;

		if(h>12) draw2X=false;


		int lineHeight=12;
		if(draw2X==false) lineHeight=24;// because the font is float, we don't need to draw at 2x


		for(y=0;y<lineHeight&&y<h;y++)
		{
			int index=getPixelValue(letter_index,y,x_in_letter,blank);


			if(index!=0)
			{

				BobColor pixelColor=TextManager().textColor;
				if(index==0) pixelColor=TextManager().textBGColor;
				if(index==1) pixelColor=TextManager().textColor;
				if(index==2) pixelColor=TextManager().textAAColor;
				if(index==3) pixelColor=TextManager().textShadowColor;


				if(index>2)
				{


					// get the gray color from the text palette
					int byte1=(int)(BobFont.font_Palette_ByteArray[index*2+0]&255);
					int byte2=(int)(BobFont.font_Palette_ByteArray[index*2+1]&255);
					int abgr1555=byte2<<8+byte1;
					int r=255-(int)((((byte1&31))/32.0f)*255.0f);


					// int r = 255-(int)((((byte1&0b00011111))/32.0f)*255.0f);
					// Color gray = new BobColor(b,b,b);


					// now r is the gray value (since r=g=b)

					int a=r;// gray.getRed();
					if(a<0) a=0;
					pixelColor=new BobColor(pixelColor.getRed(),pixelColor.getGreen(),pixelColor.getBlue(),a);

				}


				if(index==1&&y<h*0.75f)
				{

					int r=(int)Math.min(255,pixelColor.getRed()+(((float)(h-y)/(float)h)*255.0f));
					int g=(int)Math.min(255,pixelColor.getGreen()+(((float)(h-y)/(float)h)*255.0f));
					int b=(int)Math.min(255,pixelColor.getBlue()+(((float)(h-y)/(float)h)*255.0f));


					pixelColor=new BobColor(r,g,b);

				}



				if(draw2X)
				{
					// draw each pixel 4 times (2x scale)
					for(int yy=0;yy<2;yy++)
						for(int xx=0;xx<2;xx++)
							setPixel((TextManager().pow2TexWidth*4*line*lineHeight*2)+(((TextManager().pow2TexWidth*((y*2)+yy))+((xInLine*2)+xx))*4),pixelColor);
				}
				else
				{

					setPixel((TextManager().pow2TexWidth*4*line*lineHeight)+(((TextManager().pow2TexWidth*((y)))+((xInLine)))*4),pixelColor);
				}

			}


			// do shadow

			// if this value is 1 and the value of x_in_letter+1 is 0, set x_in_letter+1 to 3
			if(index==1)
			{
				BobColor shadowColor=TextManager().textShadowColor;

				if(draw2X)
				{
					if(getPixelValue(letter_index,y,x_in_letter+1,blank)==0)
						for(int yy=0;yy<2;yy++)
							for(int xx=0;xx<2;xx++)
								setPixel((TextManager().pow2TexWidth*4*line*lineHeight)+(((TextManager().pow2TexWidth*((y)+yy))+(((xInLine+1))+xx))*4),shadowColor);


					if(getPixelValue(letter_index,y+1,x_in_letter,blank)==0)
						for(int yy=0;yy<2;yy++)
							for(int xx=0;xx<2;xx++)
								setPixel((TextManager().pow2TexWidth*4*line*lineHeight)+(((TextManager().pow2TexWidth*(((y+1))+yy))+(((xInLine))+xx))*4),shadowColor);


					if(getPixelValue(letter_index,y+1,x_in_letter+1,blank)==0)
						for(int yy=0;yy<2;yy++)
							for(int xx=0;xx<2;xx++)
								setPixel((TextManager().pow2TexWidth*4*line*lineHeight)+(((TextManager().pow2TexWidth*(((y+1))+yy))+(((xInLine+1))+xx))*4),shadowColor);

				}
				else
				{

					if(getPixelValue(letter_index,y,x_in_letter+1,blank)==0)
						for(int yy=0;yy<2;yy++)
							for(int xx=0;xx<2;xx++)
								setPixel((TextManager().pow2TexWidth*4*line*lineHeight)+(((TextManager().pow2TexWidth*((y)+yy))+(((xInLine+1))+xx))*4),shadowColor);


					if(getPixelValue(letter_index,y+1,x_in_letter,blank)==0)
						for(int yy=0;yy<2;yy++)
							for(int xx=0;xx<2;xx++)
								setPixel((TextManager().pow2TexWidth*4*line*lineHeight)+(((TextManager().pow2TexWidth*(((y+1))+yy))+(((xInLine))+xx))*4),shadowColor);


					if(getPixelValue(letter_index,y+1,x_in_letter+1,blank)==0)
						for(int yy=0;yy<2;yy++)
							for(int xx=0;xx<2;xx++)
								setPixel((TextManager().pow2TexWidth*4*line*lineHeight)+(((TextManager().pow2TexWidth*(((y+1))+yy))+(((xInLine+1))+xx))*4),shadowColor);


					// if(TEXT_get_letter_pixel_color(letter_index,y,x_in_letter+1,blank)==0)TEXT_set_pixel((textMan().size_x*4*line*lineHeight)+(((textMan().size_x*((y)))+(((x_in_line+1))))*4),c2);
					// if(TEXT_get_letter_pixel_color(letter_index,y+1,x_in_letter,blank)==0)TEXT_set_pixel((textMan().size_x*4*line*lineHeight)+(((textMan().size_x*(((y+1))))+(((x_in_line))))*4),c2);
					// if(TEXT_get_letter_pixel_color(letter_index,y+1,x_in_letter+1,blank)==0)TEXT_set_pixel((textMan().size_x*4*line*lineHeight)+(((textMan().size_x*(((y+1))))+(((x_in_line+1))))*4),c2);
				}
			}



		}



	}



}
