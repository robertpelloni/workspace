package com.bobsgame.editor.SpriteEditor;

import java.awt.Button;
import java.awt.Color;
import java.awt.Dialog;
import java.awt.Label;
import java.awt.Panel;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import com.bobsgame.editor.Dialogs.SizeWindow;
import com.bobsgame.editor.Project.Project;


//===============================================================================================
public class SESizeWindow extends SizeWindow implements KeyListener
{//===============================================================================================

	SpriteEditor SE;


	//===============================================================================================
	public SESizeWindow(SpriteEditor se)
	{//===============================================================================================

		SE = se;
		dialog = new Dialog(se, "Set Size", true);
		dialog.setSize(240, 65);
		panel = new Panel();
		panel.setBackground(Color.GRAY);
		dialog.add(panel);
		dialog.addWindowListener(this);

		xTextField = new TextField("999");
		yTextField = new TextField("999");

		xByYLabel = new Label("X");
		tilesLabel = new Label(" Pixels");
		okButton = new Button("OK");
		panel.add(xTextField);
		panel.add(xByYLabel);
		panel.add(yTextField);
		panel.add(tilesLabel);
		panel.add(okButton);

		xTextField.addKeyListener(this);
		yTextField.addKeyListener(this);

		okButton.addActionListener(this);
	}


	//===============================================================================================
	public void show()
	{//===============================================================================================
		xTextField.setText("" + Project.getSelectedSprite().wP());
		yTextField.setText("" + Project.getSelectedSprite().hP());
		isRequired = false;
		//ssw.setModal(false);

		dialog.setLocation(100,100);

		dialog.setVisible(true);
	}
	//===============================================================================================
	public void showRequired()
	{//===============================================================================================
		xTextField.setText("" + Project.getSelectedSprite().wP());
		yTextField.setText("" + Project.getSelectedSprite().hP());
		isRequired = true;
		//ssw.setModal(true);

		dialog.setLocation(100,100);

		dialog.setVisible(true);
	}


	public void ok()
	{
		//int xx = Integer.parseInt(ssfx.getText());
		//int yy = Integer.parseInt(ssfy.getText());
		//if((xx==8||xx==16||xx==32||xx==64)&&(yy==8||yy==16||yy==32||yy==64))
		{
			Project.getSelectedSprite().setSize(Integer.parseInt(xTextField.getText()), Integer.parseInt(yTextField.getText()));

			SpriteEditor.editCanvas.setSize(Project.getSelectedSprite().wP() * SpriteEditor.editCanvas.zoom, Project.getSelectedSprite().hP() * SpriteEditor.editCanvas.zoom);
			//SpriteEditor.editCanvas.initUndo();
			SpriteEditor.editCanvas.editBufferImage=null;
			SpriteEditor.frameControlPanel.updateSpriteInfo();
			SpriteEditor.editCanvas.setSizeDoLayout();
			dialog.setVisible(false);
		}

	}

	//===============================================================================================
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================
		if(ae.getSource() == okButton)
		{
			ok();
		}
	}


	@Override
	public void keyTyped(KeyEvent e)
	{

	}


	@Override
	public void keyPressed(KeyEvent e)
	{
		if(e.getKeyCode() == KeyEvent.VK_ENTER)
		{
			ok();
		}
	}


	@Override
	public void keyReleased(KeyEvent e)
	{
		// TODO Auto-generated method stub

	}
}