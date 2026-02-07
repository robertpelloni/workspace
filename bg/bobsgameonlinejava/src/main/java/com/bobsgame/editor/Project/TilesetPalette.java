package com.bobsgame.editor.Project;

import java.io.*;

import java.awt.*;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.Dialogs.NumberDialog;
import com.bobsgame.editor.Dialogs.YesNoWindow;
import com.bobsgame.shared.Utils;
//===============================================================================================
public class TilesetPalette
{//===============================================================================================



	public String name;
	public int data[][];		// [index][r,g,b,bgr,hsb]
	public Color color[];		// [index]
	public boolean used[];		// [index]
	public int hsbi[][];

	public int maxRGBValue=255;

	public int numColors=1024;
	//===============================================================================================
	public TilesetPalette(String n)
	{//===============================================================================================

		name = n;
		data = new int[numColors][4];
		color = new Color[numColors];
		used = new boolean[numColors];
		hsbi = new int[numColors][3];
		for(int i = 0; i < numColors; i++)
		{
			color[i] = Color.BLACK;
			data[i][0] = 0;
			data[i][1] = 0;
			data[i][2] = 0;
			data[i][3] = 0;
			used[i] = false;
			hsbi[i][0] = 0;
			hsbi[i][1] = 0;
			hsbi[i][2] = 0;

		}
	}
	//===============================================================================================
	public TilesetPalette(String name,byte[] bytes)
	{//===============================================================================================

		this.name = name;
		numColors = bytes.length/3;

		data = new int[numColors][4];
		color = new Color[numColors];
		used = new boolean[numColors];
		hsbi = new int[numColors][3];
		for(int i = 0; i < numColors; i++)
		{
			color[i] = Color.BLACK;
			data[i][0] = 0;
			data[i][1] = 0;
			data[i][2] = 0;
			data[i][3] = 0;
			used[i] = false;
			hsbi[i][0] = 0;
			hsbi[i][1] = 0;
			hsbi[i][2] = 0;
		}

		initFromByteArray(bytes);

	}


	//===============================================================================================
	public TilesetPalette duplicate()
	{//===============================================================================================
		TilesetPalette p = new TilesetPalette(name + "Copy");
		for(int i = 0; i < numColors; i++)
		{
			p.setColorDataFromRGB(i, data[i][0], data[i][1], data[i][2]);
		}
		return p;
	}

	//===============================================================================================
	public byte[] getAsByteArray()
	{//===============================================================================================
		byte[] bytes = new byte[numColors*3];

		for(int c = 0; c < numColors; c++)
		{
			bytes[c*3+0]=((byte) data[c][0]);
			bytes[c*3+1]=((byte) data[c][1]);
			bytes[c*3+2]=((byte) data[c][2]);
		}

		return bytes;
	}

	//===============================================================================================
	public void initFromByteArray(byte[] bytes)
	{//===============================================================================================
		for(int c = 0; c < numColors; c++)
		{
			int r = bytes[c*3+0] & 0xFF;
			int g = bytes[c*3+1] & 0xFF;
			int b = bytes[c*3+2] & 0xFF;

			setColorDataFromRGB(c,r,g,b);
		}

	}


	//===============================================================================================
	public void outputBIN()
	{//===============================================================================================


		String dirpath = EditorMain.exportDirectory + "htdocs\\bin\\tilemap\\";

		Utils.makeDir(dirpath);
		//Utils.makeDir(dirpath + name() + "\\");

		//if(dirpath==null)dirpath = EditorMain.getDesktopTempDirPath();
		//Utils.makeDir(dirpath + "bin\\tilemap\\");

		FileOutputStream fouts = null;
		File fout = null;

		//---------------------------
		//make bgr palette
		//---------------------------
		try
		{
			fout = new File(dirpath + name + "_Palette_BGR.bin");
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
			fout = new File(dirpath + name + "_Palette_RGB.bin");
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
	public void rename(String n)
	{//===============================================================================================
		name = n;
	}

	//===============================================================================================
	public void setColorDataFromRGB(int i, int r, int g, int b)
	{//===============================================================================================

		int rf = r;
		int gf = g;
		int bf = b;
		int bgr = (((bf / 8) * 1024) + ((gf / 8) * 32) + ((rf / 8)));

		color[i] = new Color(r, g, b);

		data[i][0] = r;
		data[i][1] = g;
		data[i][2] = b;
		data[i][3] = bgr;

		float hsbf[] = new float[3];
		Color.RGBtoHSB(r, g, b, hsbf);
		hsbi[i][0] = Math.round(hsbf[0] * (float)maxRGBValue);
		hsbi[i][1] = Math.round(hsbf[1] * (float)maxRGBValue);
		hsbi[i][2] = Math.round(hsbf[2] * (float)maxRGBValue);

		used[i] = true;
	}

	//===============================================================================================
	public void setColorFromColor(int i, Color c)
	{//===============================================================================================

		int r = c.getRed();
		int g = c.getGreen();
		int b = c.getBlue();

		data[i][0] = r;
		data[i][1] = g;
		data[i][2] = b;

		data[i][3] = (int) (((b / 8) * 1024) + ((g / 8) * 32) + ((r / 8)));

		color[i] = c;

		float hsbf[] = new float[3];
		Color.RGBtoHSB(r, g, b, hsbf);

		hsbi[i][0] = Math.round(hsbf[0] * (float)maxRGBValue);
		hsbi[i][1] = Math.round(hsbf[1] * (float)maxRGBValue);
		hsbi[i][2] = Math.round(hsbf[2] * (float)maxRGBValue);

		used[i] = true;
	}

	//===============================================================================================
	public void setColorDataFromHSBData(int i, int hi, int si, int vi)
	{//===============================================================================================


		Color hsbColor = new Color(Color.HSBtoRGB(hi/(float)maxRGBValue, si/(float)maxRGBValue, vi/(float)maxRGBValue));
		int r = hsbColor.getRed();
		int g = hsbColor.getGreen();
		int b = hsbColor.getBlue();

		data[i][0] = r;
		data[i][1] = g;
		data[i][2] = b;

		data[i][3] = (int) (((b / 8) * 1024) + ((g / 8) * 32) + ((r / 8)));

		color[i] = hsbColor;

		hsbi[i][0] = hi;
		hsbi[i][1] = si;
		hsbi[i][2] = vi;

	}

	//===============================================================================================
	public void swapColor(int i, int i2)
	{//===============================================================================================
		int temp;

		temp = data[i2][0];
		data[i2][0] = data[i][0];
		data[i][0] = temp;

		temp = data[i2][1];
		data[i2][1] = data[i][1];
		data[i][1] = temp;

		temp = data[i2][2];
		data[i2][2] = data[i][2];
		data[i][2] = temp;

		temp = data[i2][3];
		data[i2][3] = data[i][3];
		data[i][3] = temp;

		int hsbtemp;
		hsbtemp = hsbi[i2][0];
		hsbi[i2][0] = hsbi[i][0];
		hsbi[i][0] = hsbtemp;

		hsbtemp = hsbi[i2][1];
		hsbi[i2][1] = hsbi[i][1];
		hsbi[i][1] = hsbtemp;

		hsbtemp = hsbi[i2][2];
		hsbi[i2][2] = hsbi[i][2];
		hsbi[i][2] = hsbtemp;

		boolean tempbool;

		tempbool = used[i2];
		used[i2] = used[i];
		used[i] = tempbool;

		Color tempcolor;

		tempcolor = color[i2];
		color[i2] = color[i];
		color[i] = tempcolor;

	}

	//===============================================================================================
	public void deleteColor(int i)
	{//===============================================================================================
		data[i][0] = 0;
		data[i][1] = 0;
		data[i][2] = 0;
		data[i][3] = 0;
		color[i] = Color.BLACK;
		used[i] = false;
		hsbi[i][0] = 0;
		hsbi[i][1] = 0;
		hsbi[i][2] = 0;
	}

	//===============================================================================================
	public int findColor(int r, int g, int b)
	{//===============================================================================================
		int bgr = b / 8 * 1024 + g / 8 * 32 + r / 8;
		for(int i = 0; i < numColors; i++)
		{
			if(data[i][3] == bgr && used[i] == true)
			{
				return i;
			}
		}
		return -1;
	}

	//===============================================================================================
	public int getColorIfExistsOrAddColor(int r, int g, int b, int tolerance)
	{//===============================================================================================

		int color = findColor(r, g, b);

		if(color!=-1)return color;

		color = addColor(r,g,b);


		if(color!=-1)return color;


		for(int i = 0; i < numColors; i++)
		{
			if(data[i][0] >= r - tolerance && data[i][0] <= r + tolerance
				&& data[i][1] >= g - tolerance && data[i][1] <= g + tolerance
				&& data[i][2] >= b - tolerance && data[i][2] <= b + tolerance && used[i] == true)
			{
				return i;
			}
		}
		return -1;
	}

	//===============================================================================================
	public int findOpenColorSlot()
	{//===============================================================================================
		for(int i = 1; i < numColors; i++)
		{
			boolean open = true;
			for(int p=0; p<Project.palette.size(); p++)
			{
				if(Project.palette.get(p).used[i])
				{
					open = false;
					break;
				}
			}
			if(open) return i;
		}
		return -1;
	}

	//===============================================================================================
	public int addColor(int r, int g, int b)
	{//===============================================================================================
		int i = findOpenColorSlot();
		if(i > -1)
		{
			setColorDataFromRGB(i, r, g, b);
			
			// Reserve in others
			for(int p=0; p<Project.palette.size(); p++)
			{
				TilesetPalette pal = Project.palette.get(p);
				if(pal != this)
				{
					pal.used[i] = true;
					pal.setColorDataFromRGB(i, r, g, b);
				}
			}
			
			return i;
		}
		else
		{
			return -1;
		}
	}

	//===============================================================================================
	public int getRed(int i)
	{//===============================================================================================
		return data[i][0];
	}

	//===============================================================================================
	public int getGreen(int i)
	{//===============================================================================================
		return data[i][1];
	}

	//===============================================================================================
	public int getBlue(int i)
	{//===============================================================================================
		return data[i][2];
	}

	//===============================================================================================
	public int getBGR(int i)
	{//===============================================================================================
		return data[i][3];
	}

	//===============================================================================================
	public Color getColor(int i)
	{//===============================================================================================
		return color[i];
	}

	//===============================================================================================
	public Color getColorTranslucent(int i)
	{//===============================================================================================
		return new Color(data[i][0], data[i][1], data[i][2], 150);
	}


	//===============================================================================================
	public void swapColorAllPalettes(int i, int i2)
	{//===============================================================================================
		for(int p=0; p<Project.palette.size(); p++)
		{
			Project.palette.get(p).swapColor(i, i2);
		}
	}

	//===============================================================================================
	public void synchronizePalettes(EditorMain E)
	{//===============================================================================================
		
		//Union of used flags
		for(int i=0; i<numColors; i++)
		{
			boolean usedInAny = false;
			for(TilesetPalette pal : Project.palette)
			{
				if(pal.used[i]) usedInAny = true;
			}
			
			if(usedInAny)
			{
				for(TilesetPalette pal : Project.palette)
				{
					if(!pal.used[i])
					{
						pal.used[i] = true;
						// Find first palette where it is used and copy that color
						for(TilesetPalette src : Project.palette)
						{
							if(src.used[i]) // This will be true for at least one
							{
								pal.setColorDataFromRGB(i, src.getRed(i), src.getGreen(i), src.getBlue(i));
								break;
							}
						}
					}
				}
			}
		}
		
		EditorMain.infoLabel.setTextSuccess("Synchronized All Palettes");
	}

	//===============================================================================================
	public void sortPaletteHSB(EditorMain E)
	{//===============================================================================================


		NumberDialog ndh = new NumberDialog(E, "Group Hue Within Amt 1-255");
		ndh.text.setText("1");
		ndh.show();
		int hr = Integer.parseInt(ndh.text.getText());

		NumberDialog nds = new NumberDialog(E, "Group Saturation Within Amt 1-255");
		nds.text.setText("4");
		nds.show();
		int sr = Integer.parseInt(nds.text.getText());

		int c1 = 1;
		int c2 = 0;
		for(c2 = numColors-1; c2 > c1; c2--) //sort grays to beginning
		{
			if(getBlue(c2) == getRed(c2)
				&& getBlue(c2) == getGreen(c2))
			{
				swapColorAllPalettes(c1, c2);
				Project.tileset.swapTileColors(c2, c1);
				c1++;
				c2++;
			}
		}

		int startgray = c1;
		for(c1 = 1; c1 < startgray; c1++) //sort grays by bgr
		{
			for(c2 = startgray - 1; c2 > c1; c2--)
			{
				if(getBlue(c2) > getBlue(c1))
				{

					swapColorAllPalettes(c1, c2);
					Project.tileset.swapTileColors(c2, c1);
				}
			}
		}

		c1 = startgray;

		for(c1 = startgray; c1 < numColors; c1++) //sort hue
		{
			for(c2 = numColors-1; c2 > c1; c2--)
			{

				if((hsbi[c2][0] < hsbi[c1][0]))
				{

					swapColorAllPalettes(c1, c2);
					Project.tileset.swapTileColors(c2, c1);
				}
			}
		}

		for(c1 = startgray; c1 < numColors; c1++) //sort s
		{
			for(c2 = numColors-1; c2 > c1; c2--)
			{

				if(hsbi[c2][0] >= (hsbi[c1][0] - hr)
					&& hsbi[c2][0] <= (hsbi[c1][0] + hr)
					&& hsbi[c2][1] <= hsbi[c1][1])
				{
					swapColorAllPalettes(c1, c2);
					Project.tileset.swapTileColors(c2, c1);
				}
			}
		}

		for(c1 = startgray; c1 < numColors; c1++) //sort b
		{
			for(c2 = numColors-1; c2 > c1; c2--)
			{

				if(hsbi[c2][0] >= (hsbi[c1][0] - hr)
					&& hsbi[c2][0] <= (hsbi[c1][0] + hr)
					&& hsbi[c2][1] >= (hsbi[c1][1] - sr)
					&& hsbi[c2][1] <= (hsbi[c1][1] + sr)
					&& hsbi[c2][2] <= hsbi[c1][2])
				{
					swapColorAllPalettes(c1, c2);
					Project.tileset.swapTileColors(c2, c1);
				}
			}
		}

		E.refreshTopPanelLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.repaint();
		EditorMain.controlPanel.repaint();
		EditorMain.mapCanvas.repaint();
		EditorMain.infoLabel.setTextSuccess("Sorted All Palettes By HSB");
	}


	//===============================================================================================
	public void mergePaletteH(EditorMain E)
	{//===============================================================================================




		NumberDialog nd = new NumberDialog(E, "Within Amt 1-255");
		nd.text.setText("16");
		nd.show();

		int amount = Integer.parseInt(nd.text.getText());

		int c1 = 0;
		int c2 = 0;

		for(c1 = 1; c1 < numColors; c1++)
		{
			for(c2 = numColors-1; c2 >= 1; c2--)
			{
				if((hsbi[c2][0]) < (hsbi[c1][0]))
				{

					if(((hsbi[c1][0]) != 0 || (hsbi[c1][1]) != 0)
						&& ((hsbi[c2][0]) != 0 || (hsbi[c2][1]) != 0))
					{
						if(((hsbi[c1][0]) - (hsbi[c2][0])) <= amount)
						{

							hsbi[c2][0] += ((hsbi[c1][0] - hsbi[c2][0]) / 2);

							for(int a = 1; a < numColors; a++)
							{
								if(a != c1
									&& (hsbi[a][0]) == (hsbi[c1][0])
									&& ((hsbi[a][0]) != 0 || (hsbi[a][1]) != 0))
								{
									hsbi[a][0] = hsbi[c2][0];
								}
							}

							hsbi[c1][0] = hsbi[c2][0];
						}
					}
				}
			}
		}

		//for(f=startgray;f<num_Colors;f++)
		//{
		//
		//Color col=Color.getHSBColor((float)hsbi[f][0]/(float)maxRGBValue,(float)hsbi[f][1]/(float)maxRGBValue,(float)hsbi[f][2]/(float)maxRGBValue);
		//color[f]=col;
		//data[f][0]=col.getRed();
		//data[f][1]=col.getGreen();
		//data[f][2]=col.getBlue();
		//data[f][3]=col.getBlue()/8*1024+col.getGreen()/8*32+col.getRed()/8;
		//}

		for(int f = 1; f < numColors; f++)
		{

			int h = hsbi[f][0];
			int s = hsbi[f][1];
			int b = hsbi[f][2];
			if(h != 0 || s != 0)
			{
				setColorDataFromHSBData(f, h, s, b);
			}

		}

		E.refreshTopPanelLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.repaint();
		EditorMain.controlPanel.repaint();
		EditorMain.mapCanvas.repaint();
		EditorMain.infoLabel.setTextSuccess("Merged Palette H By " + amount);
	}

	//===============================================================================================
	public void mergePaletteS(EditorMain E)
	{//===============================================================================================




		NumberDialog nd = new NumberDialog(E, "Within Amt 1-255");
		nd.text.setText("32");
		nd.show();

		int amount = Integer.parseInt(nd.text.getText());

		int c1 = 0;
		int c2 = 0;

		for(c1 = 1; c1 < numColors; c1++) //sort s
		{
			for(c2 = numColors-1; c2 >= 1; c2--)
			{
				if((hsbi[c2][0]) == (hsbi[c1][0])
					&& hsbi[c2][1] < hsbi[c1][1])
				{
					if(((hsbi[c1][0]) != 0 || (hsbi[c1][1]) != 0)
						&& ((hsbi[c2][0]) != 0 || (hsbi[c2][1]) != 0))
					{
						if((((hsbi[c1][1]) - (hsbi[c2][1])) <= amount))
						{
							hsbi[c2][1] += ((hsbi[c1][1] - hsbi[c2][1]) / 2);

							for(int a = 1; a > numColors; a++)
							{
								if(a != c1
									&& (hsbi[a][0]) == (hsbi[c1][0])
									&& (hsbi[a][1]) == (hsbi[c1][1]))
								{
									hsbi[a][1] = hsbi[c2][1];
								}
							}

							hsbi[c1][1] = hsbi[c2][1];
						}
					}
				}
			}
		}

		for(int f = 1; f < numColors; f++)
		{

			int h = hsbi[f][0];
			int s = hsbi[f][1];
			int b = hsbi[f][2];
			if(h != 0 || s != 0)
			{
				setColorDataFromHSBData(f, h, s, b);
			}

		}

		E.refreshTopPanelLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.repaint();
		EditorMain.controlPanel.repaint();
		EditorMain.mapCanvas.repaint();
		EditorMain.infoLabel.setTextSuccess("Merged Palette S By " + amount);
	}

	//===============================================================================================
	public void mergePaletteB(EditorMain E)
	{//===============================================================================================




		NumberDialog nd = new NumberDialog(E, "Within Amt 1-255");
		nd.text.setText("16");
		nd.show();

		int amount = Integer.parseInt(nd.text.getText());

		int c1 = 0;
		int c2 = 0;

		for(c1 = 1; c1 < numColors; c1++) //sort s
		{
			for(c2 = numColors-1; c2 >= 1; c2--)
			{
				if((hsbi[c2][0]) == (hsbi[c1][0])
					&& (hsbi[c2][1]) == (hsbi[c1][1])
					&& hsbi[c2][2] < hsbi[c1][2])
				{
					if(((hsbi[c1][0]) != 0 || (hsbi[c1][1]) != 0)
						&& ((hsbi[c2][0]) != 0 || (hsbi[c2][1]) != 0))
					{
						if((((hsbi[c1][2]) - (hsbi[c2][2])) <= amount))
						{

							hsbi[c2][2] += ((hsbi[c1][2] - hsbi[c2][2]) / 2);
							hsbi[c1][2] = hsbi[c2][2];
						}
					}
				}
			}
		}

		for(int f = 1; f < numColors; f++)
		{

			int h = hsbi[f][0];
			int s = hsbi[f][1];
			int b = hsbi[f][2];
			if(h != 0 || s != 0)
			{
				setColorDataFromHSBData(f, h, s, b);
			}

		}

		E.refreshTopPanelLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.repaint();
		EditorMain.controlPanel.repaint();
		EditorMain.mapCanvas.repaint();

		EditorMain.infoLabel.setTextSuccess("Merged Palette B By " + amount);
	}

	//===============================================================================================
	public void brightenPaletteHSB(EditorMain E)
	{//===============================================================================================




		NumberDialog nd = new NumberDialog(E, "Add (Out of 255)");
		nd.text.setText("16");
		nd.show();
		int amount = Integer.parseInt(nd.text.getText());

		YesNoWindow ynw = new YesNoWindow(new Frame(), "Add to Gray?");
		ynw.setVisible(true);
		boolean addgray = ynw.result;

		int c1 = 0;
		for(c1 = 1; c1 < numColors; c1++)
		{

			if(((hsbi[c1][0]) != 0 || (hsbi[c1][1]) != 0) || (addgray && hsbi[c1][2] != 0))
			{
				if(hsbi[c1][2] + amount <= numColors-1)
				{
					hsbi[c1][2] += amount;
				}
				else
				{
					hsbi[c1][2] = numColors-1;
				}
			}

		}

		for(int f = 1; f < numColors; f++)
		{

			int h = hsbi[f][0];
			int s = hsbi[f][1];
			int b = hsbi[f][2];
			if(h != 0 || s != 0 || (addgray && b != 0))
			{
				setColorDataFromHSBData(f, h, s, b);
			}

		}

		E.refreshTopPanelLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.repaint();
		EditorMain.controlPanel.repaint();
		EditorMain.mapCanvas.repaint();

		EditorMain.infoLabel.setTextSuccess("Brightened Palette By " + amount);
	}


	//===============================================================================================
	public void darkenPaletteHSB(EditorMain E)
	{//===============================================================================================




		NumberDialog nd = new NumberDialog(E, "Subtract (Out of 255)");
		nd.text.setText("8");
		nd.show();
		int amount = Integer.parseInt(nd.text.getText());

		YesNoWindow ynw = new YesNoWindow(new Frame(), "Add to Gray?");
		ynw.setVisible(true);
		boolean addgray = ynw.result;

		int c1 = 0;
		for(c1 = 1; c1 < numColors; c1++)
		{

			if(((hsbi[c1][0]) != 0 || (hsbi[c1][1]) != 0) || (addgray && hsbi[c1][2] != 0))
			{
				if(hsbi[c1][2] - amount >= 0)
				{
					hsbi[c1][2] -= amount;
				}
				else
				{
					hsbi[c1][2] = 0;
				}
			}

		}

		for(int f = 1; f < numColors; f++)
		{

			int h = hsbi[f][0];
			int s = hsbi[f][1];
			int b = hsbi[f][2];
			if(h != 0 || s != 0 || (addgray && b != 0))
			{
				setColorDataFromHSBData(f, h, s, b);
			}

		}

		E.refreshTopPanelLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.repaint();
		EditorMain.controlPanel.repaint();
		EditorMain.mapCanvas.repaint();

		EditorMain.infoLabel.setTextSuccess("Darkened Palette By " + amount);
	}

	//===============================================================================================
	public void roundPaletteHSB(EditorMain E)
	{//===============================================================================================




		NumberDialog nd = new NumberDialog(E, "Round to Amt/255");
		nd.text.setText("8");
		nd.show();
		float amount = Float.parseFloat(nd.text.getText());

		NumberDialog ndhsb = new NumberDialog(E, "[0]H [1]S [2]B [3]All");
		ndhsb.text.setText("0");
		ndhsb.show();
		int hsbn = Integer.parseInt(ndhsb.text.getText());

		int c1 = 0;
		if(hsbn == 3)
		{
			for(c1 = 1; c1 < numColors; c1++) //sort hue
			{
				for(int h = 0; h < 3; h++)
				{
					float value = (float) hsbi[c1][h];

					if(((hsbi[c1][0]) != 0 || (hsbi[c1][1]) != 0))
					{
						if(value % amount != 0)
						{
							if((value % amount) < (amount / 2.0f))
							{
								hsbi[c1][h] = (int)Math.round(((value / amount) * amount));
							}
							else
							{
								hsbi[c1][h] = (int)Math.round((((value / amount) + 1.0f) * amount));
							}

							if(hsbi[c1][h] < 0)
							{
								hsbi[c1][h] = 0;
							}
							if(hsbi[c1][h] > numColors-1)
							{
								hsbi[c1][h] = numColors-1;
							}
						}
					}
				}
			}

		}
		else
		{
			for(c1 = 1; c1 < numColors; c1++) //sort hue
			{
				float value = (float) hsbi[c1][hsbn];

				if(((hsbi[c1][0]) != 0 || (hsbi[c1][1]) != 0))
				{
					if(value % amount != 0)
					{
						if((value % amount) < (amount / 2.0f))
						{
							hsbi[c1][hsbn] = (int)Math.round(((value / amount) * amount));
						}
						else
						{
							hsbi[c1][hsbn] = (int)Math.round((((value / amount) + 1.0f) * amount));
						}

						if(hsbi[c1][hsbn] < 0)
						{
							hsbi[c1][hsbn] = 0;
						}
						if(hsbi[c1][hsbn] > numColors-1)
						{
							hsbi[c1][hsbn] = numColors-1;
						}
					}
				}
			}
		}

		for(int f = 1; f < numColors; f++)
		{

			int h = hsbi[f][0];
			int s = hsbi[f][1];
			int b = hsbi[f][2];
			if(h != 0 || s != 0)
			{
				setColorDataFromHSBData(f, h, s, b);
			}

		}

		E.refreshTopPanelLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.repaint();
		EditorMain.controlPanel.repaint();
		EditorMain.mapCanvas.repaint();

		if(hsbn == 0)
		{
			EditorMain.infoLabel.setTextSuccess("Rounded Palette H By " + amount);
		}
		if(hsbn == 1)
		{
			EditorMain.infoLabel.setTextSuccess("Rounded Palette S By " + amount);
		}
		if(hsbn == 2)
		{
			EditorMain.infoLabel.setTextSuccess("Rounded Palette B By " + amount);
		}
	}

	//===============================================================================================
	public void standardizePaletteRangeHSB(EditorMain E)
	{//===============================================================================================




		NumberDialog range1 = new NumberDialog(E, "Start On Color #");
		range1.text.setText("0");
		range1.show();
		int start = Integer.parseInt(range1.text.getText());


		NumberDialog range2 = new NumberDialog(E, "End On Color # (Inclusive)");
		range2.text.setText("10");
		range2.show();
		int end = Integer.parseInt(range2.text.getText());

		NumberDialog hued = new NumberDialog(E, "Hue");
		hued.text.setText("0");
		hued.show();
		int h = Integer.parseInt(hued.text.getText());

		NumberDialog satd = new NumberDialog(E, "Saturation");
		satd.text.setText("0");
		satd.show();
		int s = Integer.parseInt(satd.text.getText());




		//get average hue

		//int avehue = 0;

		//for(c1=start;c1<=end;c1++)
		//{
		//	avehue+=hsbi[c1][0];
		//}
		//avehue/=((end+1)-start);

		////	//get average sat
		//
		//int avesat = 0;
		//
		//for(c1=start;c1<=end;c1++)
		//{
		//	avesat+=hsbi[c1][1];
		//}
		//avesat/=((end+1)-start);


		for(int f = start; f <= end; f++)
		{

			//int h=avehue;
			//int s=avesat;
			int b = hsbi[f][2];
			setColorDataFromHSBData(f, h, s, b);

		}

		E.refreshTopPanelLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.repaint();
		EditorMain.controlPanel.repaint();
		EditorMain.mapCanvas.repaint();

		EditorMain.infoLabel.setTextSuccess("Averaged Palette Hue/Saturation");
	}




}
