package com.bobsgame.editor.SpriteEditor;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Panel;
import java.awt.Scrollbar;
import java.awt.SystemColor;
import java.awt.TextField;
import java.awt.event.ActionEvent;

import com.bobsgame.editor.ControlPanel.ColorGrid;
import com.bobsgame.editor.ControlPanel.ColorWindow;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Sprite.SpritePalette;

//===============================================================================================
public class SEColorWindow extends ColorWindow
{//===============================================================================================

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;
	private SpriteEditor SE;


	//===============================================================================================
	public SEColorWindow(SpriteEditor se)
	{//===============================================================================================

		super();
		SE = se;

		build();

	}

	//===============================================================================================
	public SpritePalette getPalette()
	{//===============================================================================================
		return Project.getSelectedSpritePalette();
	}

	//===============================================================================================
	public void showSpriteColorWindow(int colorIndex)
	{//===============================================================================================
		showColorWindow(colorIndex,false);

	}
	//===============================================================================================
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================
		if(ae.getSource() == okButton)
		{
			getPalette().setColorDataFromRGB(index, r, g, b);
			setVisible(false);
			SpriteEditor.controlPanel.repaint();
			SpriteEditor.editCanvas.repaintBufferImage();
		}
		else if(ae.getSource() == applyButton)
		{
			getPalette().setColorDataFromRGB(index, r, g, b);

			SpriteEditor.controlPanel.repaint();
			SpriteEditor.editCanvas.repaintBufferImage();
		}
		else
		{
			super.actionPerformed(ae);
		}
	}
}