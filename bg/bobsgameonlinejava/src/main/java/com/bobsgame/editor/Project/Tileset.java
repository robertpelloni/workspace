package com.bobsgame.editor.Project;

//import java.net.*;

import java.awt.*;

import java.awt.image.*;
import java.io.File;
import javax.imageio.ImageIO;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.Dialogs.NumberDialog;
import com.bobsgame.editor.TileCanvas.TileCanvas;
import com.bobsgame.shared.Utils;

public class Tileset
{


	public int tilePaletteIndex[][][];		// [index][x][y]
	public static int num_Tiles = 1;
	public static int tileWidth = 8;
	public static int tileHeight = 8;
	
	
	
	public BufferedImage tileImage[];	// [index]
	public BufferedImage tileImageTranslucent[];
	//public BufferedImage tileImageShadow[];
	public BufferedImage tileImageLightMask[];
	public BufferedImage transTile;//bob20060625
	public BufferedImage hitTile;
	//public BufferedImage maskTile;
	//private BufferedImage blanktile;//bob20060626


	private Color CLEAR = new Color(0, 0, 0, 0);
	private Color TRANSPARENT_RED = new Color(255, 0, 0, 150); //bob 20060624


	//===============================================================================================
	public Tileset()
	{//===============================================================================================
		this(5000);
	}


	//===============================================================================================
	public Tileset(int size)
	{//===============================================================================================


		num_Tiles = size;

		if(num_Tiles < 5000)
		{
			num_Tiles = 5000;
		}

		tilePaletteIndex = new int[num_Tiles][8][8];
		tileImage = new BufferedImage[num_Tiles];
		tileImageTranslucent = new BufferedImage[num_Tiles];
		//tileImageShadow = new BufferedImage[num_Tiles];
		tileImageLightMask = new BufferedImage[num_Tiles];


		transTile = new BufferedImage(8,8,BufferedImage.TYPE_INT_ARGB);
		hitTile = new BufferedImage(8,8,BufferedImage.TYPE_INT_ARGB);
		//maskTile = new BufferedImage(8,8,BufferedImage.TYPE_INT_ARGB);
		//blanktile = (new Frame()).getGraphicsConfiguration().createCompatibleImage(8,8,Transparency.TRANSLUCENT);//bob20060626




		Graphics G = hitTile.getGraphics();
		G.setColor(TRANSPARENT_RED); //bob 20060624
		G.fillRect(0, 0, 7, 7);
		//G.drawLine(0, 0, 7, 7);
		//G.drawLine(7, 0, 0, 7);
		G.dispose();

		//G = maskTile.getGraphics();
		//G.setColor(new Color(255,180,0,150));
		//G.fillRect(0, 0, 7, 7);
		//G.dispose();


		for(int t = 0; t < num_Tiles; t++)
		{
			tileImage[t] = new BufferedImage(8, 8, BufferedImage.TYPE_INT_ARGB);
			tileImageTranslucent[t] = new BufferedImage(8, 8, BufferedImage.TYPE_INT_ARGB);
			//tileImageShadow[t] = new BufferedImage(8, 8, BufferedImage.TYPE_INT_ARGB);
			tileImageLightMask[t] = new BufferedImage(8, 8, BufferedImage.TYPE_INT_ARGB);
			for(int x = 0; x < 8; x++)
			{
				for(int y = 0; y < 8; y++)
				{
					tilePaletteIndex[t][x][y] = 0;
				}
			}
		}


	}

	//===============================================================================================
	public void buildTileImages()
	{//===============================================================================================
		for(int t = 0; t < num_Tiles; t++)
		{
			for(int y = 0; y < 8; y++)
			{
				for(int x = 0; x < 8; x++)
				{
					tileImage[t].setRGB(x, y, getColor(t, x, y).getRGB());
					tileImageTranslucent[t].setRGB(x, y, getColorTranslucent(t, x, y).getRGB());
					//tileImageShadow[t].setRGB(x, y, getColorShadow(t, x, y).getRGB());
					tileImageLightMask[t].setRGB(x, y, getColorLightMask(t, x, y).getRGB());
				}
			}
		}
	}

	//===============================================================================================
	public void setNumTiles(int n)
	{//===============================================================================================

		if(n > num_Tiles)
		{

			if(n % TileCanvas.WIDTH_TILES != 0)
			{
				n += TileCanvas.WIDTH_TILES - (n % TileCanvas.WIDTH_TILES);
			}

			int newTileData[][][] = new int[n][8][8];
			BufferedImage[] newTileImage = new BufferedImage[n];
			BufferedImage[] newTileImageTranslucent = new BufferedImage[n];
			//BufferedImage[] newTileImageShadow = new BufferedImage[n];
			BufferedImage[] newTileImageLightMask = new BufferedImage[n];

			int t = 0;
			for(t = 0; t < num_Tiles && t < n; t++)
			{
				for(int x = 0; x < 8; x++)
				{
					for(int y = 0; y < 8; y++)
					{
						newTileData[t][x][y] = tilePaletteIndex[t][x][y];
					}
				}
				newTileImage[t] = tileImage[t];
				newTileImageTranslucent[t] = tileImageTranslucent[t];
				//newTileImageShadow[t] = tileImageShadow[t];
				newTileImageLightMask[t] = tileImageLightMask[t];

			}

			for(; t < n; t++)
			{
				newTileImage[t] = new BufferedImage(8, 8, BufferedImage.TYPE_INT_ARGB);
				newTileImageTranslucent[t] = new BufferedImage(8, 8, BufferedImage.TYPE_INT_ARGB);
				//newTileImageShadow[t] = new BufferedImage(8, 8, BufferedImage.TYPE_INT_ARGB);
				newTileImageLightMask[t] = new BufferedImage(8, 8, BufferedImage.TYPE_INT_ARGB);
				for(int x = 0; x < 8; x++)
				{
					for(int y = 0; y < 8; y++)
					{
						newTileData[t][x][y] = 0;
					}
				}
			}

			tileImage = newTileImage;
			tileImageTranslucent = newTileImageTranslucent;
			//tileImageShadow = newTileImageShadow;
			tileImageLightMask = newTileImageLightMask;

			tilePaletteIndex = newTileData;

			num_Tiles = t;

		}

	}

	//===============================================================================================
	public boolean isTileBlank(int t)
	{//===============================================================================================

		for(int y = 0; y < 8; y++)
		{
			for(int x = 0; x < 8; x++)
			{
				if(tilePaletteIndex[t][x][y] != 0)
				{
					return false;
				}
			}
		}

		return true;

	}

	//===============================================================================================
	public BufferedImage getTileImage(int t)
	{//===============================================================================================
		if(t < num_Tiles)
		{
			return tileImage[t];
		}
		else
		{

			BufferedImage blacktile = (new Frame()).getGraphicsConfiguration().createCompatibleImage(8, 8, Transparency.BITMASK);

			for(int y = 0; y < 8; y++)
			{
				for(int x = 0; x < 8; x++)
				{
					blacktile.setRGB(x, y, Project.getPalette(0).getColor(0).getRGB());
				}
			}

			return blacktile;
		}
	}

	//===============================================================================================
	public BufferedImage getTileImageTranslucent(int t)
	{//===============================================================================================
		return tileImageTranslucent[t];

	}

	/*//===============================================================================================
	public BufferedImage getTileImageShadow(int t)
	{//===============================================================================================
		return tileImageShadow[t];

	}*/

	//===============================================================================================
	public BufferedImage getTileImageLightMask(int t)
	{//===============================================================================================
		return tileImageLightMask[t];

	}


	//===============================================================================================
	public int[] getAsIntArray()
	{//===============================================================================================

		int[] intArray = new int[num_Tiles*8*8];

		for(int t = 0; t < num_Tiles; t++)
		{
			for(int y = 0; y < 8; y++)
			{
				for(int x = 0; x < 8; x++)
				{
					int i = getPixel(t, x, y);

					int index = (t*8*8)+(y*8)+(x);

					intArray[index]=i;
				}
			}
		}

		return intArray;

	}

	//===============================================================================================
	public byte[] getAsByteArray()
	{//===============================================================================================
		return Utils.getByteArrayFromIntArray(getAsIntArray());
	}

	//===============================================================================================
	public void initializeFromIntArray(int[] intArray)
	{//===============================================================================================
		for(int t = 0; t < num_Tiles; t++)
		{
			for(int y = 0; y < 8; y++)
			{
				for(int x = 0; x < 8; x++)
				{
					int index = (t*8*8)+(y*8)+(x);

					int i = intArray[index];

					setPixel(t, x, y, i);

				}
			}
		}

	}


	//===============================================================================================
	public void moveUnusedTilesToBottom(EditorMain E)
	{//===============================================================================================


		EditorMain.infoLabel.setTextAndConsole("Moving Unused Tiles To Bottom...");

		int oldnumtiles = num_Tiles;
		int row = 0;
		int newrow = 0;

		int percent = 0;

		for(int t = 1; t < oldnumtiles - 1; t++)
		{

			boolean used = false;
			boolean blank = isTileBlank(t);

			if(blank == false)
			{
				for(int m = 0; m < Project.getNumMaps() && !used; m++)
				{

					if(Project.getMap(m).isTileUsed(t))
					{
						used = true;
					}

				}
			}

			if(t % TileCanvas.WIDTH_TILES == 0)
			{
				newrow = 1;
			}

			if(!used && blank == false)
			{

				if(newrow == 1)
				{
					setNumTiles(num_Tiles + TileCanvas.WIDTH_TILES);
					newrow = 0;
					row++;
				}
				if(((oldnumtiles) + row * TileCanvas.WIDTH_TILES + t % TileCanvas.WIDTH_TILES) >= num_Tiles - 1)
				{
					setNumTiles(num_Tiles + TileCanvas.WIDTH_TILES);
				}

				for(int y = 0; y < 8; y++)
				{
					for(int x = 0; x < 8; x++)
					{
						tilePaletteIndex[(oldnumtiles) + row * TileCanvas.WIDTH_TILES + t % TileCanvas.WIDTH_TILES][x][y] = tilePaletteIndex[t][x][y];
						tilePaletteIndex[t][x][y] = 0;
					}
				}

			}

			if(percent != ((t / oldnumtiles) / 5) * 5)
			{
				percent = ((t / oldnumtiles) / 5) * 5;
				System.out.print("" + percent + "%.");
			}

		}

		EditorMain.tileCanvas.setSizedoLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.paintBuffer();
		EditorMain.tileCanvas.repaint();


		EditorMain.infoLabel.setTextSuccess("Moved Unused Tiles To Bottom");


	}

	//===============================================================================================
	public void removeUnusedTiles(EditorMain E)
	{//===============================================================================================


		EditorMain.infoLabel.setTextAndConsole("Removing Unused Tiles...");

//		int percent = 0;

		for(int t = num_Tiles - 1; t > 0; t--)
		{
			boolean used = false;
			boolean blank = isTileBlank(t);

			if(blank == false)
			{
				for(int m = 0; m < Project.getNumMaps() && !used; m++)
				{

					if(Project.getMap(m).isTileUsed(t))
					{
						used = true;
					}

				}
			}

			if(!used && blank == false)
			{
				clearTile(t);
			}

//			if(percent != (((num_Tiles - t) / num_Tiles) / 5) * 5)
//			{
//				percent = (((num_Tiles - t) / num_Tiles) / 5) * 5;
//				System.out.print("" + percent + "%.");//System.out.println(E.infoLabel.getText());
//			}

		}

		buildTileImages();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.repaint();

		EditorMain.infoLabel.setTextSuccess("Removed Unused Tiles");

	}

	//===============================================================================================
	public void findFirstTileUsingSelectedColor(EditorMain E)
	{//===============================================================================================
		boolean done = false;

		for(int t = 0; t < num_Tiles - 1 && !done; t++)
		{
			for(int x = 0; x < 8 && !done; x++)
			{
				for(int y = 0; y < 8 && !done; y++)
				{
					if(tilePaletteIndex[t][x][y] == EditorMain.controlPanel.paletteCanvas.colorSelected)
					{

						EditorMain.tileCanvas.tileSelected = t;


						EditorMain.tileCanvas.scrollToSelectedTile();


						done = true;

					}
				}
			}
		}

		if(!done)
		{
			EditorMain.infoLabel.setTextError("Color not used");
		}


	}

	//===============================================================================================
	public void findLeastUsedColor(EditorMain E)
	{//===============================================================================================
		NumberDialog ndh = new NumberDialog(E, "Output colors to console used on X tiles or less");
		ndh.text.setText("5");
		ndh.show();
		int limitused = Integer.parseInt(ndh.text.getText());

		int leastused = 1000;
		int leastcolor = 0;

		int num_Colors = Project.getSelectedPalette().numColors;


		for(int c = 0; c < num_Colors; c++)
		{
			int used = 0;

			for(int t = 0; t < num_Tiles - 2; t++)
			{

				boolean tiledone = false;

				for(int x = 0; x < 8 && !tiledone; x++)
				{
					for(int y = 0; y < 8 && !tiledone; y++)
					{
						if(tilePaletteIndex[t][x][y] == c)
						{
							used++;
							tiledone = true;

						}
					}
				}

			}

			if((used <= leastused) && used > 0)
			{
				leastused = used;
				leastcolor = c;
				System.out.println("Color " + leastcolor + " used on " + leastused + " tiles");
			}
			else if((used <= limitused) && used > 0)
			{
				System.out.println("Color " + c + " used on " + used + " tiles");
			}
		}

		EditorMain.controlPanel.paletteCanvas.colorSelected = leastcolor;
		EditorMain.infoLabel.setTextSuccess("Color " + leastcolor + " used on " + leastused + " tiles");

		EditorMain.controlPanel.repaint();
	}

	//===============================================================================================
	public boolean isColorUsedInTileset(int colorIndex)
	{//===============================================================================================



		for(int t = 0; t < num_Tiles - 1; t++)
		{
			for(int x = 0; x < 8; x++)
			{
				for(int y = 0; y < 8; y++)
				{
					if(getPixel(t, x, y) == colorIndex)
					{

						return true;

					}
				}
			}
		}
		return false;
	}


	//===============================================================================================
	public void removeUnusedPaletteColors(EditorMain E)
	{//===============================================================================================

		EditorMain.infoLabel.setTextAndConsole("Removing Unused Palette Colors...");

		int num_Colors = Project.getSelectedPalette().numColors;

		for(int c = 1; c < num_Colors; c++)
		{

			boolean usedcolor = false;

			for(int t = 0; t < num_Tiles - 1; t++)
			{
				for(int x = 0; x < 8; x++)
				{
					for(int y = 0; y < 8; y++)
					{
						if(getColor(t, x, y) == Project.getSelectedPalette().color[c])//TODO: this would match duplicate colors
						{
							usedcolor = true;
						}
					}
				}
			}
			if(usedcolor == false)
			{
				Project.getSelectedPalette().setColorFromColor(c, Color.BLACK);
			}
		} //checks for unused

		E.refreshTopPanelLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.repaint();
		EditorMain.controlPanel.repaint();
		EditorMain.mapCanvas.repaint();
		EditorMain.infoLabel.setTextSuccess("Removed Unused Palette Colors");


	}

	//===============================================================================================
	public void mergeDuplicatePaletteColors(EditorMain E)
	{//===============================================================================================

		EditorMain.infoLabel.setTextAndConsole("Merging Duplicate Palette Colors...");

		//checks for dupe colors
		int num_Colors = Project.getSelectedPalette().numColors;

		int c1 = 0;
		int c2 = 0;
		for(c1 = 1; c1 < num_Colors; c1++)
		{
			for(c2 = num_Colors-1; c2 > c1; c2--)
			{
				if(Project.getSelectedPalette().getBGR(c2) == Project.getSelectedPalette().getBGR(c1) && Project.getSelectedPalette().getColor(c1) != Color.BLACK)
				{

					for(int t = 0; t < num_Tiles; t++)
					{
						for(int x = 0; x < 8; x++)
						{
							for(int y = 0; y < 8; y++)
							{
								if(getColor(t, x, y) == Project.getSelectedPalette().color[c2])
								{
									setPixel(t, x, y, c1);
								}
							}
						}
					}
					Project.getSelectedPalette().setColorFromColor(c2, Color.BLACK);
				}
			}
		}

		E.refreshTopPanelLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.repaint();
		EditorMain.controlPanel.repaint();
		EditorMain.mapCanvas.repaint();
		EditorMain.infoLabel.setTextSuccess("Merged Duplicate Palette Colors");
	}


	//===============================================================================================
	public void insertTilesetRows(EditorMain E)
	{//===============================================================================================


		NumberDialog nd = new NumberDialog(E, "Insert How Many Rows?");
		nd.text.setText("0");
		nd.show();

		int rows = Integer.parseInt(nd.text.getText());

		int oldnumtiles = num_Tiles - 1;

		setNumTiles(num_Tiles + (rows * TileCanvas.WIDTH_TILES));

		EditorMain.infoLabel.setTextNoConsole("Inserting Rows..");

		int tile = EditorMain.tileCanvas.tileSelected - EditorMain.tileCanvas.tileSelected % TileCanvas.WIDTH_TILES;

		int tilestomove = oldnumtiles - tile;

		int percent = 0;

		for(int t = oldnumtiles; t >= tile; t--)
		{
			if(isTileBlank(t) == false)
			{
				EditorMain.tileCanvas.moveTile(t + rows * TileCanvas.WIDTH_TILES, t);
			}

			if(percent != ((oldnumtiles - t) / tilestomove) / 5 * 5)
			{
				percent = ((oldnumtiles - t) / tilestomove) / 5 * 5;
				System.out.print("" + percent + "%.");
			}
		}

		EditorMain.tileCanvas.setSizedoLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.paintBuffer();
		EditorMain.tileCanvas.repaint();

		EditorMain.infoLabel.setTextSuccess("Rows Inserted. New Tileset size: "+num_Tiles);
	}

	//===============================================================================================
	public void crunchTiles(EditorMain E)
	{//===============================================================================================
		for(int t = num_Tiles - 1; t > 0; t--)
		{
			//boolean used = false;
			boolean blank = isTileBlank(t);

			if(blank == false)
			{
				moveTileToFreeSpaceTop(t, E);
			}
		}
		buildTileImages();

		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.repaint();
		EditorMain.infoLabel.setTextSuccess("Crunched Tiles (Removed blank tiles)");
	}

	//===============================================================================================
	public void mergeDuplicateTiles(EditorMain E)
	{//===============================================================================================

		EditorMain.infoLabel.setTextAndConsole("Merging Duplicate Tiles...");

		int percent = 0;

		for(int t = num_Tiles - 1; t > 0; t--)
		{
			//boolean used = false;
			boolean blank = isTileBlank(t);

			if(blank == false)
			{

				int i = 1;
				for(i = 1; i < t; i++)
				{
					boolean same = true;
					for(int y = 0; y < 8; y++)
					{
						for(int x = 0; x < 8; x++)
						{
							if(tilePaletteIndex[t][x][y] != tilePaletteIndex[i][x][y])
							{
								same = false;
								y = 8;
								x = 8;
							}
						}
					}
					if(same == true)
					{
						//move all map entries, delete original, i=t
						for(int m = 0; m < Project.getNumMaps(); m++)
						{
							Project.getMap(m).replaceTileWithNewTileOnEveryLayer(t, i);
						}
						clearTile(t);

						i = t;
						//we break on the first duplicate here because we'll find the next duplicate when we get to it.
					}
				}
			}

			if(percent != (num_Tiles - t) / num_Tiles / 5 * 5)
			{
				percent = (num_Tiles - t) / num_Tiles / 5 * 5;
				System.out.print("" + percent + "%.");
			}
		}
		buildTileImages();

		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.repaint();

		EditorMain.infoLabel.setTextSuccess("Merged Duplicate Tiles");

	}


	//===============================================================================================
	public void mergeBlankTiles(EditorMain E)
	{//===============================================================================================

		EditorMain.infoLabel.setTextAndConsole("Merging Blank Tiles...");

		int percent = 0;

		for(int t = num_Tiles - 1; t > 0; t--)
		{
			//boolean used = false;
			boolean blank = isTileBlank(t);

			if(blank == true)
			{

				//move all map entries, delete original, i=t
				for(int m = 0; m < Project.getNumMaps(); m++)
				{
					Project.getMap(m).replaceTileWithNewTileOnEveryLayer(t, 0);
				}

			}


		}
		buildTileImages();

		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.repaint();

		EditorMain.infoLabel.setTextSuccess("Merged Blank Tiles");

	}

	//===============================================================================================
	public void setBlankTilesToSelectedColor(EditorMain E)
	{//===============================================================================================

		EditorMain.infoLabel.setTextAndConsole("Setting Blank Tiles To Color...");
		//int percent = 0;

		for(int t = num_Tiles - 1; t > 0; t--)
		{
			//boolean used = false;
			boolean blank = isTileBlank(t);

			if(blank == true)
			{
				for(int y = 0; y < 8; y++)
				{
					for(int x = 0; x < 8; x++)
					{
						tilePaletteIndex[t][x][y] = (int) EditorMain.controlPanel.paletteCanvas.colorSelected;
					}
				}
			}
		}
		buildTileImages();

		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.repaint();

		EditorMain.infoLabel.setTextSuccess("Set Blank Tiles To Selected Color");

	}

	//===============================================================================================
	public void removeBlankRows(EditorMain E)
	{//===============================================================================================


		EditorMain.infoLabel.setTextAndConsole("Removing Blank Rows...");

		for(int r = 0; r < ((num_Tiles) / TileCanvas.WIDTH_TILES); r++)
		{
			boolean blankrow = true;
			int rows = 0;

			while(blankrow != false && ((r + rows) < (num_Tiles / TileCanvas.WIDTH_TILES)))
			{
				for(int c = 0; c < TileCanvas.WIDTH_TILES; c++)
				{
					if(!isTileBlank(((r + rows) * TileCanvas.WIDTH_TILES) + c))
					{
						blankrow = false;
					}
				}
				rows++;
			}
			rows--;

			if(rows > 0)
			{
				for(int i = 0; i < TileCanvas.WIDTH_TILES; i++)
				{
					if(!isTileBlank(i + ((r + rows) * TileCanvas.WIDTH_TILES)))
					{
						EditorMain.tileCanvas.moveTile(i + (TileCanvas.WIDTH_TILES * r), i + ((r + rows) * TileCanvas.WIDTH_TILES));
					}

				}
			}
		}

		int newsize = num_Tiles - 1;

		while(newsize > 0 && isTileBlank(newsize))
		{
			newsize--;
		}
		newsize++;

		setNumTiles(newsize);

		buildTileImages();

		EditorMain.tileCanvas.setSizedoLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.paintBuffer();
		EditorMain.tileCanvas.repaint();

		EditorMain.infoLabel.setTextSuccess("Removed Blank Rows");

	}


	//===============================================================================================
	public void mergeDuplicatesAndRemoveEmptySpacePastSelectedTile(EditorMain E)
	{//===============================================================================================


		EditorMain.infoLabel.setTextAndConsole("Merging Duplicates And Removing Empty Space Past Selected Tile...");

		int percent = 0;

		for(int t = num_Tiles - 1; t > EditorMain.tileCanvas.tileSelected; t--)
		{
			//boolean used = false;
			boolean blank = isTileBlank(t);

			if(blank == false)
			{

				int i = 1;
				for(i = 1; i < t; i++)
				{
					boolean same = true;
					for(int y = 0; y < 8; y++)
					{
						for(int x = 0; x < 8; x++)
						{
							if(tilePaletteIndex[t][x][y] != tilePaletteIndex[i][x][y])
							{
								same = false;
								y = 8;
								x = 8;
							}
						}
					}
					if(same == true)
					{
						//move all map entries, delete original, i=t
						for(int m = 0; m < Project.getNumMaps(); m++)
						{
							Project.getMap(m).replaceTileWithNewTileOnEveryLayer(t, i);
						}
						clearTile(t);
						i = t;
					}
				}
			}
			else
			{
				//the tile is blank, set all maps using this tile to tile 0,
				//otherwise maps will be referencing a blank tile that got deleted. (crash on start)
				//this only happens for newly made "mashed" tiles
				for(int m = 0; m < Project.getNumMaps(); m++)
				{
					Project.getMap(m).replaceTileWithNewTileOnEveryLayer(t, 0);
				}
			}

			if(percent != (num_Tiles - t) / num_Tiles / 5 * 5)
			{
				percent = (num_Tiles - t) / num_Tiles / 5 * 5;
				System.out.print("" + percent + "%.");
			}
		}



		for(int r = EditorMain.tileCanvas.tileSelected / TileCanvas.WIDTH_TILES; r < ((num_Tiles) / TileCanvas.WIDTH_TILES); r++)
		{
			boolean blankrow = true;
			int rows = 0;

			while(blankrow != false && ((r + rows) < (num_Tiles / TileCanvas.WIDTH_TILES)))
			{
				for(int c = 0; c < TileCanvas.WIDTH_TILES; c++)
				{
					if(!isTileBlank(((r + rows) * TileCanvas.WIDTH_TILES) + c))
					{
						blankrow = false;
					}
				}
				rows++;
			}
			rows--;

			if(rows > 0)
			{
				for(int i = 0; i < TileCanvas.WIDTH_TILES; i++)
				{
					if(!isTileBlank(i + ((r + rows) * TileCanvas.WIDTH_TILES)))
					{
						EditorMain.tileCanvas.moveTile(i + (TileCanvas.WIDTH_TILES * r), i + ((r + rows) * TileCanvas.WIDTH_TILES));
					}

				}
			}
		}

		int newsize = num_Tiles - 1;

		while(newsize > 0 && isTileBlank(newsize))
		{
			newsize--;
		}
		newsize++;

		setNumTiles(newsize);

		buildTileImages();

		EditorMain.tileCanvas.setSizedoLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.paintBuffer();
		EditorMain.tileCanvas.repaint();


		EditorMain.infoLabel.setTextSuccess("Merged Duplicate Tiles And Removed Space Below Selected Tile");


	}

	//===============================================================================================
	public void clearTile(int t)
	{//===============================================================================================
		for(int y = 0; y < 8; y++)
		{
			for(int x = 0; x < 8; x++)
			{
				tilePaletteIndex[t][x][y] = 0;
				tileImage[t].setRGB(x, y, getColor(t, x, y).getRGB());
				tileImageTranslucent[t].setRGB(x, y, getColorTranslucent(t, x, y).getRGB());
				//tileImageShadow[t].setRGB(x, y, getColorShadow(t, x, y).getRGB());
				tileImageLightMask[t].setRGB(x, y, getColorLightMask(t, x, y).getRGB());
			}
		}

	}

	//===============================================================================================
	public void moveTileToFreeSpaceBottom(int t)
	{//===============================================================================================
		for(int i = num_Tiles - 1; i > t; i--)
		{

			boolean blank = isTileBlank(t);

			if(blank == false)
			{
				for(int y = 0; y < 8; y++)
				{
					for(int x = 0; x < 8; x++)
					{
						tilePaletteIndex[i][x][y] = tilePaletteIndex[t][x][y];
						tilePaletteIndex[t][x][y] = 0;
					}
				}

				i = t;
			}

		}
	}
	//===============================================================================================
	public void moveTileToFreeSpaceTop(int t, EditorMain E)
	{//===============================================================================================
		for(int i = 1; i < t; i++)
		{

			boolean blank = isTileBlank(t);

			if(blank == true)
			{
				EditorMain.tileCanvas.moveTile(t, i);
				i = t;
			}

		}

	}


	//===============================================================================================
	public void setPixel(int index, int x, int y, int colorIndex)
	{//===============================================================================================
		if(index + 1 > num_Tiles)
		{
			num_Tiles = index + 1;		// Increase the tileset size if the pixel to be set is outside current size
		}
		tilePaletteIndex[index][x][y] = (int) colorIndex;
		tileImage[index].setRGB(x, y, getColor(index, x, y).getRGB());
		tileImageTranslucent[index].setRGB(x, y, getColorTranslucent(index, x, y).getRGB());
		//tileImageShadow[index].setRGB(x, y, getColorShadow(index, x, y).getRGB());
		tileImageLightMask[index].setRGB(x, y, getColorLightMask(index, x, y).getRGB());
	}

	//===============================================================================================
	public int getPixel(int index, int x, int y)
	{//===============================================================================================
		return tilePaletteIndex[index][x][y];
	}

	//===============================================================================================
	public Color getColor(int index, int x, int y)
	{//===============================================================================================
		if(Project.getSelectedPaletteIndex() >= 0)
		{
			if(tilePaletteIndex[index][x][y] != 0)
			{
				return Project.getSelectedPalette().getColor(tilePaletteIndex[index][x][y]);
			}
			else
			{
				return CLEAR;
			}
		}
		else
		{
			return Color.RED;
		}
	}

	//===============================================================================================
	public Color getColorTranslucent(int index, int x, int y)//bob20060625
	{//===============================================================================================
		if(Project.getSelectedPaletteIndex() >= 0)
		{
			if(tilePaletteIndex[index][x][y] != 0)
			{
				return Project.getSelectedPalette().getColorTranslucent(tilePaletteIndex[index][x][y]);
			}
			else
			{
				return CLEAR;
			}
		}
		else
		{
			return Color.RED;
		}
	}

	//===============================================================================================
	public Color getColorShadow(int index, int x, int y)//bob20060625
	{//===============================================================================================
		if(Project.getSelectedPaletteIndex() >= 0)
		{
			if(tilePaletteIndex[index][x][y] != 0)
			{
				return new Color(0,0,0,150);
			}
			else
			{
				return CLEAR;
			}
		}
		else
		{
			return Color.RED;
		}
	}

	//===============================================================================================
	public Color getColorLightMask(int index, int x, int y)//bob20060625
	{//===============================================================================================
		if(Project.getSelectedPaletteIndex() >= 0)
		{
			if(tilePaletteIndex[index][x][y] != 0)
			{
				return new Color(255,180,0,200);
			}
			else
			{
				return CLEAR;
			}
		}
		else
		{
			return Color.RED;
		}
	}

	//===============================================================================================
	public void swapTileColors(int color, int newcolor)
	{//===============================================================================================
		for(int t = 0; t < num_Tiles; t++)
		{
			for(int y = 0; y < 8; y++)
			{
				for(int x = 0; x < 8; x++)
				{
					if(tilePaletteIndex[t][x][y] == color)
					{
						tilePaletteIndex[t][x][y] = (int) newcolor;
					}
					else if(tilePaletteIndex[t][x][y] == newcolor)
					{
						tilePaletteIndex[t][x][y] = (int) color;
					}
				}
			}
		}
		buildTileImages();
	}


	//===============================================================================================
	public void importImageToTileset(EditorMain E)
	{//===============================================================================================
		JFileChooser fileChooser = new JFileChooser();
		if (EditorMain.fileChooser.getCurrentDirectory() != null) {
			fileChooser.setCurrentDirectory(EditorMain.fileChooser.getCurrentDirectory());
		}
		
		int result = fileChooser.showOpenDialog(E);
		if (result == JFileChooser.APPROVE_OPTION) {
			File selectedFile = fileChooser.getSelectedFile();
			try {
				BufferedImage image = ImageIO.read(selectedFile);
				if (image == null) {
					EditorMain.infoLabel.setTextError("Could not load image.");
					return;
				}

				int width = image.getWidth();
				int height = image.getHeight();

				int tilesX = width / 8;
				int tilesY = height / 8;
				int totalNewTiles = tilesX * tilesY;

				String[] options = {"Append to End", "Overwrite at Selection", "Cancel"};
				int choice = JOptionPane.showOptionDialog(E, 
						"Image size: " + width + "x" + height + " (" + totalNewTiles + " tiles).\nHow do you want to import?", 
						"Import Image", 
						JOptionPane.DEFAULT_OPTION, JOptionPane.QUESTION_MESSAGE, null, options, options[0]);

				if (choice == 2 || choice == JOptionPane.CLOSED_OPTION) return;

				int startTileIndex = 0;
				if (choice == 0) { // Append
					startTileIndex = num_Tiles;
					setNumTiles(num_Tiles + totalNewTiles);
				} else { // Overwrite
					startTileIndex = EditorMain.tileCanvas.tileSelected;
					if (startTileIndex + totalNewTiles > num_Tiles) {
						setNumTiles(startTileIndex + totalNewTiles);
					}
				}

				EditorMain.infoLabel.setTextAndConsole("Importing image...");

				TilesetPalette palette = Project.getSelectedPalette();

				for (int ty = 0; ty < tilesY; ty++) {
					for (int tx = 0; tx < tilesX; tx++) {
						int currentTile = startTileIndex + (ty * tilesX) + tx;
						
						for (int y = 0; y < 8; y++) {
							for (int x = 0; x < 8; x++) {
								int rgb = image.getRGB(tx * 8 + x, ty * 8 + y);
								Color c = new Color(rgb, true);
								if (c.getAlpha() == 0) {
									setPixel(currentTile, x, y, 0); // Transparent
									continue;
								}
								
								int r = c.getRed();
								int g = c.getGreen();
								int b = c.getBlue();
								
								int colorIndex = palette.getColorIfExistsOrAddColor(r, g, b, 0);
								
								if (colorIndex == -1) {
									// Palette full or not found, find nearest
									double minDist = Double.MAX_VALUE;
									int bestIndex = 0;
									for (int i = 1; i < palette.numColors; i++) { // Skip 0 (transparent/black usually)
										if (palette.used[i]) {
											int pr = palette.getRed(i);
											int pg = palette.getGreen(i);
											int pb = palette.getBlue(i);
											double dist = Math.pow(r - pr, 2) + Math.pow(g - pg, 2) + Math.pow(b - pb, 2);
											if (dist < minDist) {
												minDist = dist;
												bestIndex = i;
											}
										}
									}
									colorIndex = bestIndex;
								}
								
								setPixel(currentTile, x, y, colorIndex);
							}
						}
					}
				}

				buildTileImages();
				EditorMain.tileCanvas.setSizedoLayout();
				EditorMain.tileCanvas.updateAllTiles();
				EditorMain.tileCanvas.repaint();
				EditorMain.infoLabel.setTextSuccess("Imported " + totalNewTiles + " tiles.");

			} catch (Exception ex) {
				ex.printStackTrace();
				EditorMain.infoLabel.setTextError("Error importing image: " + ex.getMessage());
			}
		}
	}








}
