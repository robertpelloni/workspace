package com.bobsgame.editor.SpriteEditor;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;

import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Sprite.Sprite;
import com.bobsgame.editor.Project.Sprite.SpritePalette;
//===============================================================================================
public class SEBitmapSplicer extends Canvas implements ImageObserver, MouseWheelListener
{//===============================================================================================

	/**
	 *
	 */
	private static final long serialVersionUID = -4365435214593328076L;
	public int spriteSizeX;
	public int spriteSizeY;
	public int borderSize;
	public int directions;
	public int frames;
	public int totalFrames;
	private BufferedImage image;
	private int imagewidth = 0;
	private int imageheight = 0;
	private int zoom = 2;
	private ScrollPane mapScrollPane;

	public boolean isKid = false;
	public boolean isAdult = false;
	public boolean isRandom = false;
	//===============================================================================================
	public SEBitmapSplicer()
	{//===============================================================================================
		super();
		addMouseWheelListener(this);
	}
	//===============================================================================================
	public void addPane(ScrollPane p)
	{//===============================================================================================
		mapScrollPane = p;
	}
	//===============================================================================================
	public Sprite generateSprite(SpritePalette palette, SpriteEditor se)
	{//===============================================================================================
		int amtsprites = (imageheight / (spriteSizeY + borderSize)) / frames;
		int totalFrames = frames * directions;
		int width = spriteSizeX;
		int height = spriteSizeY;



		//determine if its a 16x32 or a 32x64
		if(width == 16 && height > 32)
		{
			//spriteSizeX = 32; //don't have to do this anymore, not on the DS so doesn't matter what size.
			//spriteSizeY = 64;
		}

		if(height==40)isAdult=true;
		if(height==32)isKid = true;

		for(int q = 0; q < amtsprites; q++)
		{

			Sprite s = new Sprite("BitmapSprite" + q, totalFrames, spriteSizeX, spriteSizeY);
			s.setIsNPC(true);
			s.setIsKid(isKid);
			s.setIsAdult(isAdult);
			s.setHasShadow(true);
			s.setIsRandom(isRandom);

			for(int f = 0; f < totalFrames; f++)
			{

				//initialize the full cropped sprite
				for(int x = 0; x < spriteSizeX; x++)
				{
					for(int y = 0; y < spriteSizeY; y++)
					{
						s.setPixel(f, x, y, 0);
					}
				}


				int fx = (f / frames) * (width + borderSize);
				int fy = (q * (height + borderSize)) + ((amtsprites) * (height + borderSize) * ((f % frames)));
				//for(int fy=0;fy<verticaldivisions;fy++)
				//{
				// For each pixel in the frame
				for(int y = 0; y < height; y++)
				{
					for(int x = 0; x < width; x++)
					{
						// Get the RGB values of the pixel
						int rgb = image.getRGB(fx + x, fy + y);
						Color c = new Color(rgb);
						int r = c.getRed();
						int g = c.getGreen();
						int b = c.getBlue();


						int palcol = -1;

						if(isRandom)
						{
							// Compare the values to those in the palette
							palcol = palette.findRandomColor(r, g, b);

						}
						else
						{
							palcol = palette.findColor(r, g, b);
						}

						// If palette color doesnt exist, add it
						if(palcol == -1)
						{

							if(isRandom)palcol = palette.addRandomColor(r, g, b);
							else palcol = palette.addColor(r, g, b);

							if(palcol == -1)
							{
								palcol = 0;               // If palette is full, set to background color
							}
						}
						// Set the proper pixel in the new sprite object
						s.setPixel(f, x, y, palcol);
						//frame++;
					}
				}
				//}
			}

			if(height==32)
			{

				s.getData().addAnimation("Down",0,2,1,24,0);
				s.getData().addAnimation("Up",8,2,1,24,0);
				s.getData().addAnimation("Left",16,2,1,24,0);
				s.getData().addAnimation("Right",24,2,1,24,0);

				if(directions>4)
				{
					s.getData().addAnimation("UpLeft",32,2,1,24,0);
					s.getData().addAnimation("UpRight",40,2,1,24,0);
					s.getData().addAnimation("DownRight",48,2,1,24,0);
					s.getData().addAnimation("DownLeft",56,2,1,24,0);
				}
			}
			else
			{

				s.getData().addAnimation("Down",0,0,0,31,0);
				s.getData().addAnimation("Up",8,0,0,31,0);
				s.getData().addAnimation("Left",16,0,0,31,0);
				s.getData().addAnimation("Right",24,0,0,31,0);

				if(directions>4)
				{
					s.getData().addAnimation("UpLeft",32,0,0,31,0);
					s.getData().addAnimation("UpRight",40,0,0,31,0);
					s.getData().addAnimation("DownRight",48,0,0,31,0);
					s.getData().addAnimation("DownLeft",56,0,0,31,0);
				}
			}

			Project.setSelectedSpriteIndex(Project.getNumSprites()-1);
		}
		Sprite newSprite = null;
		return newSprite;
	}
	//===============================================================================================
	public Sprite generateDitheredSprite(SpritePalette palette, SpriteEditor se)
	{//===============================================================================================
		int amtsprites = (imageheight / (spriteSizeY + borderSize)) / frames;
		int totalFrames = frames * directions;
		int width = spriteSizeX;
		int height = spriteSizeY;

		//determine if its a 16x32 or a 32x64
		if(height > 32)
		{
			//spriteSizeX = 32;
			//spriteSizeY = 64;
		}

		if(height==40)isAdult=true;
		if(height==32)isKid = true;


		for(int q = 0; q < amtsprites; q++)
		{

			Sprite newSprite = new Sprite("BitmapSpriteDithered" + q, totalFrames, spriteSizeX, spriteSizeY);

			newSprite.setIsNPC(true);
			newSprite.setIsKid(isKid);
			newSprite.setIsAdult(isAdult);
			newSprite.setHasShadow(true);
			newSprite.setIsRandom(isRandom);


			for(int f = 0; f < totalFrames; f++)
			{


				//initialize the full cropped sprite
				for(int x = 0; x < spriteSizeX; x++)
				{
					for(int y = 0; y < spriteSizeY; y++)
					{
						newSprite.setPixel(f, x, y, 0);
					}
				}


				int fx = (f / frames) * (width + borderSize);
				int fy = (q * (height + borderSize)) + ((amtsprites) * (height + borderSize) * ((f % frames)));
				//for(int fy=0;fy<verticaldivisions;fy++)
				//{
				// For each pixel in the frame
				for(int x = 0; x < width; x++)
				{
					for(int y = 0; y < height; y++)
					{
						// Get the RGB values of the pixel
						int rgb = image.getRGB(fx + x, fy + y);
						Color c = new Color(rgb);
						int r = c.getRed();
						int g = c.getGreen();
						int b = c.getBlue();
						// Compare the values to those in the palette
						int palcol = palette.getColorIfExistsOrAddColor(r, g, b, 4);

						// Set the proper pixel in the new sprite object
						newSprite.setPixel(f, x, y, palcol);
						//frame++;
					}
				}
				//}
			}
			Project.setSelectedSpriteIndex(Project.getNumSprites()-1);
		}
		Sprite newSprite = null;
		return newSprite;
	}
	/*	public boolean setVerticalDivisions(int Divisions)
	{
	if(Divisions>0 && imageheight%Divisions==0)
	{
	verticaldivisions=Divisions;
	repaint();
	return true;
	} else return false;
	}
	public boolean setHorizontalDivisions(int Divisions)
	{
	if(Divisions>0 && imagewidth%Divisions==0)
	{
	horizontaldivisions=Divisions;
	repaint();
	return true;
	} else return false;
	}*/
	//===============================================================================================
	public void setImage(BufferedImage image)
	{//===============================================================================================
		this.image = image;
		imagewidth = image.getWidth(this);
		imageheight = image.getHeight(this);
		repaint();
	}
	//===============================================================================================
	public void repaint()
	{//===============================================================================================
		setSize(imagewidth * zoom, imageheight * zoom);
		if(mapScrollPane != null)
		{
			mapScrollPane.validate();
		}
		else
		{
			paint(getGraphics());
		}
	}
	//===============================================================================================
	public void paint(Graphics G)
	{//===============================================================================================
		if(image != null)
		{
			G.drawImage(image, 0, 0, imagewidth * zoom, imageheight * zoom, this);
		}
		G.setColor(Color.RED);
		//if(horizontaldivisions>1)
		//	for(int x=imagewidth/horizontaldivisions;x<imagewidth;x+=imagewidth/horizontaldivisions)
		//	G.drawLine(x*zoom,0,x*zoom,imageheight*zoom);
		//if(verticaldivisions>1)
		//	for(int y=imageheight/verticaldivisions;y<imageheight;y+=imageheight/verticaldivisions)
		//	G.drawLine(0,y*zoom,imagewidth*zoom,y*zoom);
	}
	//===============================================================================================
	public void zoomIn()
	{//===============================================================================================
		if(zoom < 8)
		{
			zoom++;
		}
	}
	//===============================================================================================
	public void zoomOut()
	{//===============================================================================================
		if(zoom > 1)
		{
			zoom--;
		}
	}
	//===============================================================================================
	public void mouseWheelMoved(MouseWheelEvent mwe)
	{//===============================================================================================
		if(mwe.getWheelRotation() > 0)
		{
			zoomIn();
		}
		if(mwe.getWheelRotation() < 0)
		{
			zoomOut();
		}
		repaint();
	}
}