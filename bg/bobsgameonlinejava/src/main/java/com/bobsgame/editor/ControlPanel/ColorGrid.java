package com.bobsgame.editor.ControlPanel;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;

//===============================================================================================
public class ColorGrid extends Panel implements MouseListener, MouseMotionListener, ImageObserver
{//===============================================================================================
	//MouseWheelListener,


	public BufferedImage img;
	private ColorWindow cw;

	public int offsetY = 64;
	//===============================================================================================
	public ColorGrid(ColorWindow CW)
	{//===============================================================================================
		cw = CW;
		addMouseListener(this);
		addMouseMotionListener(this);
		//addMouseWheelListener(this);
		img = new BufferedImage(512, 512, BufferedImage.TYPE_INT_RGB);
		repaintColorWheelBackground(0);
	}


	//===============================================================================================
	public void repaintColorWheelBackground(int b)
	{//===============================================================================================
		for(int r = 0; r < 256; r++)
		{
			for(int g = 0; g < 256; g++)
			{
				Graphics G = img.getGraphics();
				G.setColor(new Color(r, g, b));
				G.fillRect(r*2,(g*2),2,2);
			}
		}
	}

	//===============================================================================================
	@Override
	public void paint(Graphics G)
	{//===============================================================================================
		paint(cw.redScrollbar.getValue(), cw.greenScrollbar.getValue(), cw.blueScrollbar.getValue());
	}
	//===============================================================================================
	public void paint(int r, int g, int b)
	{//===============================================================================================
		Graphics G = getGraphics();
		G.drawImage(img, 0, 0+offsetY, this);

		//draw cursor on selected color
		G.setColor(Color.WHITE);
		G.drawRect(r*2, (g*2) + offsetY, 2, 2);

		//fill color preview
		G.setColor(new Color(r, g, b));
		G.fillRect(0, 0, 512, offsetY-4);
	}
	//===============================================================================================
	public void mouseEntered(MouseEvent ME)
	{//===============================================================================================
	}
	//===============================================================================================
	public void mouseExited(MouseEvent ME)
	{//===============================================================================================
	}
	//===============================================================================================
	public void mousePressed(MouseEvent ME)
	{//===============================================================================================
	}
	//===============================================================================================
	public void mouseReleased(MouseEvent ME)
	{//===============================================================================================
	}
	//===============================================================================================
	public void mouseClicked(MouseEvent ME)
	{//===============================================================================================
		if(ME.getY() > 0 + offsetY && ME.getY() < 512 + offsetY && ME.getX() > 0 && ME.getX() < 512)
		{
			int xx = ME.getX();
			int yy = ME.getY() - offsetY;
			cw.redTextField.setText("" + xx/2);
			cw.greenTextField.setText("" + yy/2);
		}
	}
	//===============================================================================================
	public void mouseMoved(MouseEvent ME)
	{//===============================================================================================
	}
	//===============================================================================================
	public void mouseDragged(MouseEvent ME)
	{//===============================================================================================
		mouseClicked(ME);
	}

	//===============================================================================================
	@Override
	public boolean imageUpdate(Image i, int infoflags, int x, int y, int width, int height)
	{//===============================================================================================
		return false;//TODO: this was true, testing false
	}
}
