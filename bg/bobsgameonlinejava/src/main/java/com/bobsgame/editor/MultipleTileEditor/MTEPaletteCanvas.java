package com.bobsgame.editor.MultipleTileEditor;

import java.awt.Frame;

import com.bobsgame.editor.ControlPanel.ColorWindow;
import com.bobsgame.editor.ControlPanel.PaletteCanvas;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.TilesetPalette;

//===============================================================================================
public class MTEPaletteCanvas extends PaletteCanvas
{//===============================================================================================

	public MultipleTileEditor MTE;


	//===============================================================================================
	public MTEPaletteCanvas(MultipleTileEditor mte)
	{//===============================================================================================
		MTE=mte;
		E=mte.E;

		CW = new ColorWindow(this);


		addMouseListener(this);
		addMouseMotionListener(this);
		addKeyListener(MTE.editCanvas);

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

		MTE.controlPanel.selectedColorPanel.setBackground(getPalette().color[colorSelected]);
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


		MTE.controlPanel.colorNumLabel.setText("Color " + colorSelected);MTE.controlPanel.colorNumLabel.validate();
		MTE.controlPanel.rgbLabel.setText("RGB:" + r1 + "," + g1 + "," + b1);MTE.controlPanel.rgbLabel.validate();
		MTE.controlPanel.hsbLabel.setText("HSB:" + h1 + "," + s1 + "," + v1);MTE.controlPanel.hsbLabel.validate();
		MTE.controlPanel.bgrLabel.setText("BGR:" + bgr1);MTE.controlPanel.bgrLabel.validate();
	}

	//===============================================================================================
	public void openColorWindow(int cs)
	{//===============================================================================================
		CW.showColorWindow(cs, false);
		if(CW.getExtendedState() == Frame.ICONIFIED)
		{
			CW.setExtendedState(Frame.NORMAL);
		}
		MTE.editCanvas.repaint();
	}

	//===============================================================================================
	public void moveColor(int cs, int draggedColor)
	{//===============================================================================================
		getPalette().swapColor(cs, draggedColor);
		E.project.tileset.swapTileColors(draggedColor, cs);
		MTE.infoLabel.setTextSuccess("Moved Color : " + cs);
	}
	//===============================================================================================
	public void copyColor(int cs, int draggedColor)
	{//===============================================================================================
		getPalette().setColorFromColor(cs, getPalette().getColor(draggedColor));
		MTE.infoLabel.setTextSuccess("Copied Color: " + draggedColor);
	}
	//===============================================================================================
	public void setText(String s)
	{//===============================================================================================
		MTE.infoLabel.setText(s);
	}

	//===============================================================================================
	public void repaintCanvas()
	{//===============================================================================================
		MTE.editCanvas.repaintBufferImage();
		MTE.editCanvas.repaint();
		mouseDragged = false;
	}




}
