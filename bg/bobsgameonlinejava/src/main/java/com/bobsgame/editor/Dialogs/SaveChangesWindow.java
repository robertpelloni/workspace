package com.bobsgame.editor.Dialogs;

import java.awt.*;
import java.awt.event.*;

import javax.swing.JDialog;
import javax.swing.WindowConstants;

import com.bobsgame.EditorMain;

public class SaveChangesWindow extends JDialog implements ActionListener
{

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;
	private Button yes, no;
	public boolean wasCancelled;

	public SaveChangesWindow(Frame f)
	{
		super(f, "Save Changes?", true);
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);

		setSize(20, 80);
		yes = new Button("yes");
		yes.addActionListener(this);
		no = new Button("no");
		no.addActionListener(this);

		add(no, BorderLayout.NORTH);
		add(yes, BorderLayout.SOUTH);
		setSize(20, 80);

	}

	public SaveChangesWindow(EditorMain e)
	{
		super(e, "Save Changes?", true);
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);

		setSize(20, 80);
		yes = new Button("yes");
		yes.addActionListener(this);
		no = new Button("no");
		no.addActionListener(this);

		add(no, BorderLayout.NORTH);
		add(yes, BorderLayout.SOUTH);
		setSize(20, 80);

	}

	public void actionPerformed(ActionEvent ae)
	{
		if(ae.getSource() == yes)
		{
			wasCancelled = false;
			setVisible(false);

		}
		else
		{
			wasCancelled = true;
			setVisible(false);
		}
	}
}