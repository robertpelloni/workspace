package com.bobsgame.editor.MapCanvas;

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
public class MapSizeWindow extends SizeWindow implements KeyListener
{//===============================================================================================

	protected MapCanvas M;

	//===============================================================================================
	public MapSizeWindow(MapCanvas m)
	{//===============================================================================================
		M = m;
		dialog = new Dialog(M.E, "Set Size", true);
		dialog.setSize(240, 65);
		panel = new Panel();
		panel.setBackground(Color.GRAY);
		dialog.add(panel);
		dialog.addWindowListener(this);


		xTextField = new TextField("999");
		yTextField = new TextField("999");


		xByYLabel = new Label("X");
		tilesLabel = new Label(" Tiles");
		okButton = new Button("OK");
		okButton.addActionListener(this);


		xTextField.addKeyListener(this);
		yTextField.addKeyListener(this);

		panel.add(xTextField);
		panel.add(xByYLabel);
		panel.add(yTextField);
		panel.add(tilesLabel);
		panel.add(okButton);
	}


	//===============================================================================================
	public void show()
	{//===============================================================================================
		xTextField.setText("" + Project.getSelectedMap().wT());
		yTextField.setText("" + Project.getSelectedMap().hT());
		isRequired = false;
		//ssw.setModal(false);

		dialog.setLocation(100,100);
		dialog.setVisible(true);

	}
	//===============================================================================================
	public void showRequired()
	{//===============================================================================================
		xTextField.setText("" + Project.getSelectedMap().wT());
		yTextField.setText("" + Project.getSelectedMap().hT());
		isRequired = true;
		//ssw.setModal(true);


		dialog.setLocation(100,100);
		dialog.setVisible(true);

	}


	public void ok()
	{
		//if(Integer.parseInt(ssfx.getText())<1025&&Integer.parseInt(ssfy.getText())<1025)//bob 20060613 //MAX MAP SIZE
		{
			M.E.project.setMapSize(Integer.parseInt(xTextField.getText()), Integer.parseInt(yTextField.getText()));
			//M.setSize(M.E.project.getSelectedMap().getWidth()*8*M.zoom+20,M.E.project.getSelectedMap().getHeight()*8*M.zoom+20);
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
		// TODO Auto-generated method stub

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
