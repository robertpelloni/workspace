package com.bobsgame.editor.SpriteEditor;

import java.awt.Color;
import java.awt.Frame;
import java.awt.Graphics;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.ControlPanel.PaletteCanvas;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Sprite.SpritePalette;

//===============================================================================================
public class SEPaletteCanvas extends PaletteCanvas
{//===============================================================================================


	SpriteEditor SE;
	EditorMain E;

	protected SEColorWindow SCW;



	//===============================================================================================
	public SEPaletteCanvas(SpriteEditor se)
	{//===============================================================================================


		SE=se;
		E=se.E;

		SCW = new SEColorWindow(SE);


		addMouseListener(this);
		addMouseMotionListener(this);
		addKeyListener(SpriteEditor.editCanvas);

		setColorsPerColumn();

	}

	//===============================================================================================
	public void paint(Graphics g)
	{//===============================================================================================
		super.paint(g);



		//draw outline around RANDOM colors


		g.setColor(Color.MAGENTA);

		g.drawRect(PaletteGrid_x - 1, PaletteGrid_y+(swathSize*(colorsPerColumn-((128/colorsPerRow)+1)))-1, swathSize*colorsPerRow+1, (swathSize*((128/colorsPerRow)))+1);


	}

	//===============================================================================================
	public void setColorsPerColumn()
	{//===============================================================================================
		colorsPerColumn = (getPalette().numColors/colorsPerRow)+1;
	}

	//===============================================================================================
	public SpritePalette getPalette()
	{//===============================================================================================
		return Project.getSelectedSpritePalette();

	}
	//===============================================================================================
	public void setColorPreviewPanel()
	{//===============================================================================================

		SpriteEditor.controlPanel.selectedColorPanel.setBackground(getPalette().color[colorSelected]);
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

		SpriteEditor.controlPanel.colorNumLabel.setText("Color " + colorSelected);SpriteEditor.controlPanel.colorNumLabel.validate();
		SpriteEditor.controlPanel.rgbLabel.setText("RGB:" + r1 + "," + g1 + "," + b1);SpriteEditor.controlPanel.rgbLabel.validate();
		SpriteEditor.controlPanel.hsbLabel.setText("HSB:" + h1 + "," + s1 + "," + v1);SpriteEditor.controlPanel.validate();
		SpriteEditor.controlPanel.bgrLabel.setText("BGR:" + bgr1);SpriteEditor.controlPanel.validate();
	}

	//===============================================================================================
	public void openColorWindow(int cs)
	{//===============================================================================================
		SCW.showSpriteColorWindow(cs);
		if(SCW.getExtendedState() == Frame.ICONIFIED)
		{
			SCW.setExtendedState(Frame.NORMAL);
		}
		SpriteEditor.editCanvas.repaint();
	}

	//===============================================================================================
	public void moveColor(int cs, int draggedColor)
	{//===============================================================================================
		getPalette().swapColor(cs, draggedColor);
		SE.swapSpriteColorsEverySprite(draggedColor, cs);
		SE.infoLabel.setTextSuccess("Moved Color: " + cs);
	}
	//===============================================================================================
	public void copyColor(int cs, int draggedColor)
	{//===============================================================================================
		getPalette().setColorFromColor(cs, getPalette().getColor(draggedColor));
		SE.infoLabel.setTextSuccess("Copied Color: " + draggedColor);
	}
	//===============================================================================================
	public void setText(String s)
	{//===============================================================================================
		SE.infoLabel.setText(s);
	}

	//===============================================================================================
	public void repaintCanvas()
	{//===============================================================================================
		SpriteEditor.editCanvas.repaintBufferImage();
		SpriteEditor.editCanvas.repaint();
		mouseDragged = false;
	}




}
