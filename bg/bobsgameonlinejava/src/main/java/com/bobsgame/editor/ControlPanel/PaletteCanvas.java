package com.bobsgame.editor.ControlPanel;

import java.awt.Color;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import javax.swing.JComponent;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.TilesetPalette;
//===============================================================================================
public class PaletteCanvas extends JComponent implements MouseMotionListener, MouseListener, ActionListener, ItemListener
{//===============================================================================================
	/**
	 *
	 */
	private static final long serialVersionUID = 1L;

	public EditorMain E;

	public int PaletteGrid_x = 2;
	public int PaletteGrid_y = 2;//30;

	public int colorSelected = 0;

	public int swathSize=16;//pixels width and height for each color
	static public int colorsPerRow=16;//colors per row
	public int colorsPerColumn=32;

	public int maxRGBValue=255;

	public int draggedColor, prevcolor;

	protected boolean mouseDragged = false;

	public ColorWindow CW;

	//===============================================================================================
	public PaletteCanvas()
	{//===============================================================================================

	}
	//===============================================================================================
	public PaletteCanvas(EditorMain e)
	{//===============================================================================================
		E=e;

		CW = new ColorWindow(this);


		addMouseListener(this);
		addMouseMotionListener(this);
		setFocusable(true);
		addKeyListener(E);

		setColorsPerColumn();


	}
	//===============================================================================================
	public void setColorsPerColumn()
	{//===============================================================================================
		colorsPerColumn = (getPalette().numColors/colorsPerRow)+1;
	}

	//===============================================================================================
	public TilesetPalette getPalette()
	{//===============================================================================================
		return Project.getSelectedPalette();

	}
	//===============================================================================================
	public void setColorPreviewPanel()
	{//===============================================================================================

		EditorMain.controlPanel.selectedColorPanel.setBackground(getPalette().color[colorSelected]);
	}


	//===============================================================================================
	public void paint()
	{//===============================================================================================
		paint(getGraphics());
	}

	//===============================================================================================
	public void paint(Graphics G)
	{//===============================================================================================

		//super.paint(G);

		//fill whole canvas with black
		G.setColor(Color.BLACK);
		G.fillRect(0, 0, this.getWidth(), this.getHeight());

		G.setColor(Color.WHITE);
		//draw white outline
		G.drawRect(PaletteGrid_x - 1, PaletteGrid_y - 1, swathSize*colorsPerRow+1, (swathSize*colorsPerColumn)+1);

		int highlightX=0;
		int highlightY=0;

		if(getPalette() != null)
		{
			for(int y = 0; y < colorsPerColumn; y++)
			{
				for(int x = 0; x < colorsPerRow; x++)
				{

					if(y * colorsPerRow + x>=getPalette().numColors)break;

					//fill in swath
					G.setColor(getPalette().getColor(y * colorsPerRow + x));
					G.fillRect(PaletteGrid_x + x * swathSize, PaletteGrid_y + y * swathSize, swathSize, swathSize);

					//if we're currently on the selected color
					if(y * colorsPerRow + x == colorSelected)
					{
						highlightX = x;
						highlightY = y;

					}

				}

			}

			{

				int x = highlightX;
				int y = highlightY;
				G.setColor(getPalette().getColor(colorSelected));

				//fill in top indicator area with selected color
				setColorPreviewPanel();

				//fill in selection rectangle
				G.setColor(Color.BLACK);
				G.drawRect(PaletteGrid_x-1 + x * swathSize, PaletteGrid_y-1 + y * swathSize, swathSize+1, swathSize+1);
				G.setColor(Color.RED);
				G.drawRect(PaletteGrid_x + x * swathSize, PaletteGrid_y + y * swathSize, swathSize-1, swathSize-1);
				G.drawLine(PaletteGrid_x + x * swathSize, PaletteGrid_y + y * swathSize, PaletteGrid_x + ((x+1) * swathSize)-1, PaletteGrid_y + ((y+1) * swathSize)-1);
				G.setColor(Color.BLACK);
				G.drawRect(PaletteGrid_x+1 + x * swathSize, PaletteGrid_y+1 + y * swathSize, swathSize-3, swathSize-3);

			}


		}
		else
		{
			G.setColor(Color.BLACK);
			G.fillRect(PaletteGrid_x, PaletteGrid_y, swathSize*colorsPerRow, swathSize*colorsPerColumn);
		}

		//EditorMain.controlPanel.tileEditCanvas.paint();

	}


	//===============================================================================================
	public void setColorLabels()
	{//===============================================================================================
		int r1 = getPalette().data[colorSelected][0];
		int g1 = getPalette().data[colorSelected][1];
		int b1 = getPalette().data[colorSelected][2];
		int bgr1 = getPalette().data[colorSelected][3];
		int h1 = getPalette().hsbi[colorSelected][0];
		int s1 = getPalette().hsbi[colorSelected][1];
		int v1 = getPalette().hsbi[colorSelected][2];
		boolean used = getPalette().used[colorSelected];

		EditorMain.controlPanel.colorNumLabel.setText(" Color:" + colorSelected);EditorMain.controlPanel.colorNumLabel.validate();
		EditorMain.controlPanel.colorUsedLabel.setText(" Used:"+used);EditorMain.controlPanel.colorUsedLabel.validate();
		EditorMain.controlPanel.rgbLabel.setText(" RGB:" + r1 + "," + g1 + "," + b1);EditorMain.controlPanel.rgbLabel.validate();
		EditorMain.controlPanel.hsbLabel.setText(" HSB:" + h1 + "," + s1 + "," + v1);EditorMain.controlPanel.hsbLabel.validate();
		EditorMain.controlPanel.bgrLabel.setText(" BGR:" + bgr1);EditorMain.controlPanel.bgrLabel.validate();
	}

	//===============================================================================================
	public void selectColor(int cs)
	{//===============================================================================================

		if(cs<getPalette().numColors)
		{

			colorSelected = cs;

			paint();

			setColorLabels();
		}
	}

	//===============================================================================================
	public void openColorWindow(int cs)
	{//===============================================================================================
		CW.showColorWindow(cs, true);
		if(CW.getExtendedState() == Frame.ICONIFIED)
		{
			CW.setExtendedState(Frame.NORMAL);
		}
	}

	//===============================================================================================
	public void moveColor(int cs, int draggedColor)
	{//===============================================================================================
		getPalette().swapColor(cs, draggedColor);
		Project.tileset.swapTileColors(draggedColor, cs);
		setTextSuccess("PaletteCanvas: Color WAS Moved");//bob
	}
	//===============================================================================================
	public void copyColor(int cs, int draggedColor)
	{//===============================================================================================
		getPalette().setColorFromColor(cs, getPalette().getColor(draggedColor));
		setTextSuccess("PaletteCanvas: Color Copied");
	}
	//===============================================================================================
	public void setText(String s)
	{//===============================================================================================
		EditorMain.infoLabel.setTextNoConsole(s);
	}
	//===============================================================================================
	public void setTextSuccess(String s)
	{//===============================================================================================
		EditorMain.infoLabel.setTextSuccess(s);
	}
	//===============================================================================================
	public void repaintCanvas()
	{//===============================================================================================
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.paint();

		//this is only called when a color has copied or moved, which makes sense to update the mapcanvas
		EditorMain.mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();


		mouseDragged = false;
	}

	//===============================================================================================
	@Override
	public void itemStateChanged(ItemEvent e)
	{//===============================================================================================
	}
	//===============================================================================================
	@Override
	public void actionPerformed(ActionEvent e)
	{//===============================================================================================

	}
	//===============================================================================================
	@Override
	public void mouseClicked(MouseEvent me)
	{//===============================================================================================

		if(
				me.getY() > PaletteGrid_y &&
				me.getY() < PaletteGrid_y + swathSize*colorsPerColumn &&
				me.getX() > PaletteGrid_x &&
				me.getX() < PaletteGrid_x + swathSize*colorsPerRow
		)
		{

			int cs = (me.getY() - PaletteGrid_y) / swathSize * colorsPerRow + (me.getX() - PaletteGrid_x) / swathSize;

			if(cs == colorSelected && me.getClickCount() == 2)
			{
				openColorWindow(cs);
			}
			else
			{
				selectColor(cs);
			}

		}

	}
	//===============================================================================================
	@Override
	public void mousePressed(MouseEvent me)
	{//===============================================================================================
		if(
				me.getY() > PaletteGrid_y &&
				me.getY() < PaletteGrid_y + swathSize*colorsPerColumn &&
				me.getX() > PaletteGrid_x &&
				me.getX() < PaletteGrid_x + swathSize*colorsPerRow
		)
		{
			draggedColor = (me.getY() - PaletteGrid_y) / swathSize * colorsPerRow + (me.getX() - PaletteGrid_x) / swathSize;
		}
	}
	//===============================================================================================
	@Override
	public void mouseReleased(MouseEvent me)
	{//===============================================================================================
		int leftMask = InputEvent.BUTTON1_DOWN_MASK;
		int rightMask = InputEvent.BUTTON3_DOWN_MASK;
		int shiftClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK;
		int ctrlClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.CTRL_DOWN_MASK;

		if(
				me.getY() > PaletteGrid_y &&
				me.getY() < PaletteGrid_y + swathSize*colorsPerColumn &&
				me.getX() > PaletteGrid_x &&
				me.getX() < PaletteGrid_x + swathSize*colorsPerRow &&
				mouseDragged
		)
		{
			int cs = (me.getY() - PaletteGrid_y) / swathSize * colorsPerRow + (me.getX() - PaletteGrid_x) / swathSize;


			if(me.getModifiersEx() == leftMask)
			{
				setText("PaletteCanvas: Color NOT Moved- hold [SHIFT] to move");//bob
				return;
			}
			else
			if(me.getModifiersEx() == shiftClickMask)
			{
				//move
				moveColor(cs,draggedColor);
			}
			else
			if((me.getModifiersEx() == rightMask || me.getModifiersEx() == ctrlClickMask))
			{
				//copy
				copyColor(cs,draggedColor);
			}

			paint();
			repaintCanvas();

		}

	}
	//===============================================================================================
	@Override
	public void mouseEntered(MouseEvent e)
	{//===============================================================================================

	}
	//===============================================================================================
	@Override
	public void mouseExited(MouseEvent e)
	{//===============================================================================================

	}
	//===============================================================================================
	@Override
	public void mouseDragged(MouseEvent me)
	{//===============================================================================================


		if(me.getY() > PaletteGrid_y
			&& me.getY() < PaletteGrid_y + swathSize*colorsPerColumn &&
			me.getX() > PaletteGrid_x
			&& me.getX() < PaletteGrid_x + swathSize*colorsPerRow)
		{
			mouseDragged = true;
		}

	}
	//===============================================================================================
	@Override
	public void mouseMoved(MouseEvent e)
	{//===============================================================================================

	}






}
