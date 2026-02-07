package com.bobsgame.editor.SpriteEditor;

import java.awt.Color;

import com.bobsgame.editor.SelectionArea;
import com.bobsgame.editor.MultipleTileEditor.MTECanvas;
import com.bobsgame.editor.MultipleTileEditor.MTESelectionArea;
import com.bobsgame.editor.Undo.*;
//===============================================================================================
public class SESelectionArea extends SelectionArea
{//===============================================================================================

	private SECanvas EA;

	protected int[][][] copy2;

	protected int copyWidth2, copyHeight2;

	public boolean isCopied2 = false;




	//===============================================================================================
	public SESelectionArea(SECanvas ea)
	{//===============================================================================================
		super();
		EA = ea;

		setBackground(new Color(255, 255, 255, 50));
	}


	//===============================================================================================
	public SECanvas getEditCanvas()
	{//===============================================================================================
		return EA;
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
						if (contains(x1 + x, y1 + y)) {
							copy[x][y][0] = getEditCanvas().getPixel(x1 + x, y1 + y); // Copy pixels within Selected Area
						} else {
							copy[x][y][0] = 0; // Transparent if outside mask
						}
					}
				}
			}
			isCopiedOrCut = true;

		}
	}


	//===============================================================================================
	public void copykeys()
	{//===============================================================================================


		if(isShowing)
		{
			copyWidth2 = x2 - x1;
			copyHeight2 = y2 - y1;
			copy2 = new int[copyWidth2][copyHeight2][1];//HYPER LAYER
			{
				for(int y = 0; y < copyHeight2; y++)
				{
					for(int x = 0; x < copyWidth2; x++)
					{

						copy2[x][y][0] = getEditCanvas().getPixel(x1 + x, y1 + y); // Copy pixels within Selected Area

					}
				}
			}
			isCopied2 = true;

		}
	}

	//===============================================================================================
	public void cut()
	{//===============================================================================================
		copy();
		delete();
	}


	//===============================================================================================
	public void cutkeys()
	{//===============================================================================================
		copykeys();
		delete();
	}


	//===============================================================================================
	public void delete()
	{//===============================================================================================
		CompoundEdit edit = new CompoundEdit();
		delete(edit);
		edit.end();
		if(edit.isSignificant()) getEditCanvas().undoManager.addEdit(edit);
	}

	public void delete(CompoundEdit edit)
	{//===============================================================================================


		if(isShowing)
		{
			for(int y = 0; y < getHeight(); y++)
			{
				for(int x = 0; x < getWidth(); x++)
				{
					if (contains(x1 + x, y1 + y)) {
						getEditCanvas().setPixel(x1 + x, y1 + y, 0, edit); // Delete pixels within Selected Area
					}
				}
			}
		}
	}


	//===============================================================================================
	public boolean paste()
	{//===============================================================================================
		CompoundEdit edit = new CompoundEdit();
		boolean result = paste(edit);
		edit.end();
		if(edit.isSignificant()) getEditCanvas().undoManager.addEdit(edit);
		return result;
	}

	public boolean paste(CompoundEdit edit)
	{//===============================================================================================


		if(isShowing && isCopiedOrCut && copyWidth <= getWidth() && copyHeight <= getHeight())
		{
			for(int y = 0; y < copyHeight; y++)
			{
				for(int x = 0; x < copyWidth; x++)
				{
					if (contains(x1 + x, y1 + y)) {
						getEditCanvas().setPixel(x1 + x, y1 + y, copy[x][y][0], edit); // Paste pixels within Selected Area
					}
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
	public boolean pastekeys()
	{//===============================================================================================
		CompoundEdit edit = new CompoundEdit();
		boolean result = pastekeys(edit);
		edit.end();
		if(edit.isSignificant()) getEditCanvas().undoManager.addEdit(edit);
		return result;
	}

	public boolean pastekeys(CompoundEdit edit)
	{//===============================================================================================

		if(isShowing && isCopied2 && copyWidth2 <= getWidth() && copyHeight2 <= getHeight())
		{
			for(int y = 0; y < copyHeight2; y++)
			{
				for(int x = 0; x < copyWidth2; x++)
				{
					getEditCanvas().setPixel(x1 + x, y1 + y, copy2[x][y][0], edit); // Paste pixels within Selected Area
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
	public boolean pastekeysNonZero()
	{//===============================================================================================
		CompoundEdit edit = new CompoundEdit();
		boolean result = pastekeysNonZero(edit);
		edit.end();
		if(edit.isSignificant()) getEditCanvas().undoManager.addEdit(edit);
		return result;
	}

	public boolean pastekeysNonZero(CompoundEdit edit)
	{//===============================================================================================

		if(isShowing && isCopied2 && copyWidth2 <= getWidth() && copyHeight2 <= getHeight())
		{
			for(int y = 0; y < copyHeight2; y++)
			{
				for(int x = 0; x < copyWidth2; x++)
				{
					if(copy2[x][y][0] != 0)
					{
						getEditCanvas().setPixel(x1 + x, y1 + y, copy2[x][y][0], edit); // Paste pixels within Selected Area
					}
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
		CompoundEdit edit = new CompoundEdit();
		boolean result = pasteReverse(edit);
		edit.end();
		if(edit.isSignificant()) getEditCanvas().undoManager.addEdit(edit);
		return result;
	}

	public boolean pasteReverse(CompoundEdit edit)
	{//===============================================================================================
		if(isShowing && isCopiedOrCut && copyWidth <= getWidth() && copyHeight <= getHeight())
		{
			for(int y = 0; y < copyHeight; y++)
			{
				for(int x = 0; x < copyWidth; x++)
				{

					getEditCanvas().setPixel(x2 - x - 1, y1 + y, copy[x][y][0], edit); // Paste pixels within Selected Area

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
		CompoundEdit edit = new CompoundEdit();
		boolean result = pasteFlipped(edit);
		edit.end();
		if(edit.isSignificant()) getEditCanvas().undoManager.addEdit(edit);
		return result;
	}

	public boolean pasteFlipped(CompoundEdit edit)
	{//===============================================================================================
		if(isShowing && isCopiedOrCut && copyWidth <= getWidth() && copyHeight <= getHeight())
		{
			for(int y = 0; y < copyHeight; y++)
			{
				for(int x = 0; x < copyWidth; x++)
				{

					getEditCanvas().setPixel(x1 + x, y2 - y - 1, copy[x][y][0], edit); // Paste pixels within Selected Area

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
