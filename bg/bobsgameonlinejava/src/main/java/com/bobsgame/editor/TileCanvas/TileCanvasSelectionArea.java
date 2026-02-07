package com.bobsgame.editor.TileCanvas;

import java.awt.Color;
import java.awt.Graphics;

import com.bobsgame.editor.SelectionArea;
//===============================================================================================
public class TileCanvasSelectionArea extends SelectionArea
{//===============================================================================================


	private TileCanvas TC;


	public int x1Cut, y1Cut, x2Cut, y2Cut, x1Copy, y1Copy, x2Copy, y2Copy;

	public boolean isSelectedCut = false;
	public boolean isShowingCut = false;


	public boolean isSelectedCopy = false;
	public boolean isShowingCopy = false;

	//===============================================================================================
	public TileCanvasSelectionArea(TileCanvas tc)
	{//===============================================================================================
		super();
		TC = tc;
		//type = TILE_TYPE;
		setBackground(new Color(255, 255, 255, 50));//bob 20060624
		cutcolor = new Color(255, 0, 0, 75);
		copycolor = new Color(0, 255, 0, 75);
	}



	//===============================================================================================
	public void paint(Graphics G)
	{//===============================================================================================
		if(isShowing)
		{
			G.setColor(color);
			G.fillRect(x1, y1, (x2 - x1), (y2 - y1));
			G.setColor(Color.RED);
			G.drawRect(x1, y1, (x2 - x1) - 1, (y2 - y1) - 1);
		}

		if(isSelectedCut)
		{
			G.setColor(cutcolor);
			G.fillRect(x1Cut, y1Cut, (x2Cut - x1Cut), (y2Cut - y1Cut));
		}


		if(isSelectedCopy)
		{
			G.setColor(copycolor);
			G.fillRect(x1Copy, y1Copy, (x2Copy - x1Copy), (y2Copy - y1Copy));
		}

		G.dispose();
	}


	//===============================================================================================
	public void repaint()
	{//===============================================================================================



		TC.paintBuffer();
		if(isShowing || isSelectedCut || isSelectedCopy)
		{
			paint(TC.getGraphics());		// Make the selection visible
		}



	}

	//===============================================================================================
	public void copy()
	{//===============================================================================================


		if(isShowing)
		{
			copyWidth = x2 - x1;
			copyHeight = y2 - y1;
			copy = new int[copyWidth][copyHeight][1];//HYPER LAYER
			{
				for(int y = 0; y < copyHeight; y++)
				{
					for(int x = 0; x < copyWidth; x++)
					{
						//TODO: fill with tile values from tile canvas.. this is done elsewhere
					}
				}
			}
			isCopiedOrCut = true;

		}
	}

	//===============================================================================================
	public void delete()
	{//===============================================================================================

		//dont delete tiles?
	}


	//===============================================================================================
	public boolean paste()
	{//===============================================================================================

		if(isShowing && isCopiedOrCut && copyWidth <= getWidth() && copyHeight <= getHeight())
		{
			for(int y = 0; y < copyHeight; y++)
			{
				for(int x = 0; x < copyWidth; x++)
				{

					//TODO: paste tiles

				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	//===============================================================================================
	public boolean pasteReverse()
	{//===============================================================================================
		if(isShowing && isCopiedOrCut && copyWidth <= getWidth() && copyHeight <= getHeight())
		{
			for(int y = 0; y < copyHeight; y++)
			{
				for(int x = 0; x < copyWidth; x++)
				{

					//paste reversed tiles?

				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	//===============================================================================================
	public boolean pasteFlipped()
	{//===============================================================================================
		if(isShowing && isCopiedOrCut && copyWidth <= getWidth() && copyHeight <= getHeight())
		{
			for(int y = 0; y < copyHeight; y++)
			{
				for(int x = 0; x < copyWidth; x++)
				{

					//paste flipped tiles?

				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}

}
