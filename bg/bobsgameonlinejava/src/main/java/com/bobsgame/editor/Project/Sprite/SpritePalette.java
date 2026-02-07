package com.bobsgame.editor.Project.Sprite;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.TilesetPalette;
import com.bobsgame.shared.Utils;

//===============================================================================================
public class SpritePalette extends TilesetPalette
{//===============================================================================================


	//===============================================================================================
	public SpritePalette(String n)
	{//===============================================================================================
		super(n);
	}


	//===============================================================================================
	public SpritePalette duplicate()
	{//===============================================================================================
		SpritePalette p = new SpritePalette(name + "Copy");
		for(int i = 0; i < numColors; i++)
		{
			p.setColorDataFromRGB(i, data[i][0], data[i][1], data[i][2]);
		}
		return p;
	}

	//===============================================================================================
	public SpritePalette(String name,byte[] bytes)
	{//===============================================================================================

		super(name,bytes);

	}


	//===============================================================================================
	public void outputBIN(String dirpath, EditorMain E)
	{//===============================================================================================
		if(dirpath==null)dirpath = EditorMain.exportDirectory;
		Utils.makeDir(dirpath + "bin\\sprite\\");

		FileOutputStream fouts = null;
		File fout = null;

		//---------------------------
		//make bgr palette
		//---------------------------
		try
		{
			fout = new File(dirpath + "bin\\sprite\\" + name + "_SpritePalette_BGR.bin");
			fouts = new FileOutputStream(fout);
		}
		catch(FileNotFoundException fnfe){System.out.println("Could not create file.");return;}

		try
		{
			for(int c = 0; c < numColors; c++)
			{
				fouts.write((byte) data[c][3]);
				fouts.write((byte) (data[c][3] >> 8));
			}
			fouts.close();
		}
		catch(IOException e){}

		//---------------------------
		//make rgb palette
		//---------------------------
		try
		{
			fout = new File(dirpath + "bin\\sprite\\" + name + "_SpritePalette_RGB.bin");
			fouts = new FileOutputStream(fout);
		}
		catch(FileNotFoundException fnfe){System.out.println("Could not create file.");}

		try
		{
			for(int c = 0; c < numColors; c++)
			{
				fouts.write((byte) data[c][0]);
				fouts.write((byte) data[c][1]);
				fouts.write((byte) data[c][2]);
			}
			fouts.close();
		}
		catch(IOException e){}
	}


	//===============================================================================================
	public int findColor(int r, int g, int b)
	{//===============================================================================================
		int bgr = b / 8 * 1024 + g / 8 * 32 + r / 8;
		for(int i = 0; i < numColors-128; i++) // - 128 for reserved random colors
		{
			if(data[i][3] == bgr && used[i] == true)
			{
				return i;
			}
		}
		return -1;
	}


	//===============================================================================================
	public void mergeDuplicateSpriteColors()
	{//===============================================================================================

		SpritePalette pal = Project.getSpritePalette(Project.getSelectedSpritePaletteIndex());

		for(int p = 0; p < pal.numColors-128; p++) // - 128 for reserved random colors
		{
			for(int q = p + 1; q < pal.numColors-128; q++) // - 128 for reserved random colors
			{
				if(pal.data[p][0] == pal.data[q][0]
					&& pal.data[p][1] == pal.data[q][1]
					&& pal.data[p][2] == pal.data[q][2])
				{
					pal.deleteColor(q);

					for(int i = 0; i < Project.getNumSprites(); i++)
					{
						for(int f = 0; f < Project.getSprite(i).frames(); f++)
						{
							for(int x = 0; x < Project.getSprite(i).wP(); x++)
							{
								for(int y = 0; y < Project.getSprite(i).hP(); y++)
								{
									if(Project.getSprite(i).getPixel(f, x, y) == q)
									{
										Project.getSprite(i).setPixel(f, x, y, p);
									}
								}
							}
						}
					}

				}
			}
		}

	}

	//===============================================================================================
	public int findRandomColor(int r, int g, int b)
	{//===============================================================================================
		int bgr = b / 8 * 1024 + g / 8 * 32 + r / 8;

		for(int i = numColors-1; i >= numColors-128; i--) // - 128 for reserved random colors
		{
			if(data[i][3] == bgr && used[i] == true)
			{
				return i;
			}
		}
		return -1;
	}
	//===============================================================================================
	public int findOpenRandomColorSlot()
	{//===============================================================================================
		for(int i = numColors-1; i >= numColors-128; i--)
		{
			if(!used[i])
			{
				return i;//||(data[i][0]==0&&data[i][1]==0&&data[i][2]==0)
			}
		}
		return -1;
	}
	//===============================================================================================
	public int addRandomColor(int r, int g, int b)
	{//===============================================================================================
		int i = findOpenRandomColorSlot();
		if(i > -1)
		{
			setColorDataFromRGB(i, r, g, b);
			return i;
		}
		else
		{
			return -1;
		}
	}




}
