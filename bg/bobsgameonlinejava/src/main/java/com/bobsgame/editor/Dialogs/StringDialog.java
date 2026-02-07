package com.bobsgame.editor.Dialogs;

import java.awt.*;
import java.awt.event.*;

public class StringDialog extends Dialog implements KeyListener
{

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;
	public TextField newName;

	public StringDialog(Frame f)
	{
		super(f, "String", true);
		setSize(700, 50);
		setResizable(false);
		setLocation(2560/2, 1600/2);
		//addKeyListener(this);
	}

	public StringDialog(Frame f, String windowname)
	{
		super(f, windowname, true);
		setSize(700, 50);
		setResizable(false);
		setSize(700, 50);
		//addKeyListener(this);
	}
	public void show(String name)
	{

		newName = new TextField("");
		add(newName, BorderLayout.NORTH);
		newName.setText(name);
		newName.addKeyListener(this);
		setVisible(true);
	}

	public void keyPressed(KeyEvent ke)
	{
		if(ke.getKeyCode() == KeyEvent.VK_ENTER)
		{
			setVisible(false);
		}
	}

	public void keyReleased(KeyEvent ke)
	{
	}

	public void keyTyped(KeyEvent ke)
	{
	}
}