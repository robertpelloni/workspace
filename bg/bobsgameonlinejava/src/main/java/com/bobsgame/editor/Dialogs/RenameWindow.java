package com.bobsgame.editor.Dialogs;

import java.awt.*;
import java.awt.event.*;

import javax.swing.JDialog;
import javax.swing.WindowConstants;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.SpriteEditor.SpriteEditor;

public class RenameWindow extends JDialog implements ActionListener, KeyListener
{

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;
	public TextField newName;
	//private BgEditor E;
	private Button ok, cancel;
	public boolean wasCancelled;


	public void init()
	{

		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);

		setSize(700, 100);
		setResizable(true);
		ok = new Button("OK");
		ok.addActionListener(this);
		cancel = new Button("Cancel");
		cancel.addActionListener(this);
		newName = new TextField("newnamegoeshere");
		newName.setFont(new Font("Tahoma",Font.PLAIN,18));

		newName.addKeyListener(this);

		add(newName, BorderLayout.NORTH);

		Panel buttonPanel = new Panel();
		buttonPanel.add(ok);
		buttonPanel.add(cancel);

		//add(ok, BorderLayout.EAST);
		add(buttonPanel, BorderLayout.EAST);


	}

	public RenameWindow(Frame f)
	{
		super(f, "Rename", true);
		init();

	}

	public RenameWindow(EditorMain e)
	{
		super(e, "Rename", true);
		init();
	}

	public RenameWindow(SpriteEditor se)
	{
		super(se, "Rename", true);
		init();

	}

	public void show(String name)
	{
		wasCancelled = true;
		newName.setText(name);


		setLocation(100,100);
		setVisible(true);
	}

	public void ok()
	{
		boolean isAcceptable = true;
		String ns = newName.getText();
		for(int i = 0; i < ns.length(); i++)
		{
			if((ns.charAt(i) < 'A' || ns.charAt(i) > 'Z') && (ns.charAt(i) < 'a' || ns.charAt(i) > 'z') && (ns.charAt(i) < '0' || ns.charAt(i) > '9')&&(ns.charAt(i)!='_'))
			{
				isAcceptable = false;
			}
		}
		if(isAcceptable)
		{
			wasCancelled = false;
			setVisible(false);
		}

	}

	public void actionPerformed(ActionEvent ae)
	{
		if(ae.getSource() == ok)
		{
			ok();
		}
		else if(ae.getSource() == cancel)
		{
			wasCancelled = true;
			setVisible(false);
		}
	}

	@Override
	public void keyTyped(KeyEvent e)
	{

	}

	@Override
	public void keyPressed(KeyEvent ke)
	{
		if(ke.getKeyCode() == KeyEvent.VK_ENTER)
		{
			ok();
		}

	}

	@Override
	public void keyReleased(KeyEvent e)
	{

	}
}