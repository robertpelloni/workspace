package com.bobsgame.editor.Dialogs;

import java.awt.*;
import java.awt.event.*;

import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.WindowConstants;

import com.bobsgame.EditorMain;
//===============================================================================================
public class YesNoWindow extends JDialog implements ActionListener
{//===============================================================================================

	/**
	 *
	 */
	private static final long serialVersionUID = 3002041161977613601L;

	private JLabel messageLabel;
	private Button yes, no;
	public boolean result;
	//===============================================================================================
	public YesNoWindow(Frame f, String s)
	{//===============================================================================================
		super(f, s, true);
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);


		setLayout(new BorderLayout());

		messageLabel = new JLabel(s);
		add(messageLabel);


		Panel buttonPanel = new Panel(new FlowLayout());

		yes = new Button("yes");
		yes.addActionListener(this);
		no = new Button("no");
		no.addActionListener(this);

		buttonPanel.add(yes);
		buttonPanel.add(no);

		add(buttonPanel, BorderLayout.CENTER);

		setSize(400, 100);
		setLocation(200,200);

	}
	//===============================================================================================
	public YesNoWindow(EditorMain e, String s)
	{//===============================================================================================
		super(e, s, true);
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);

		setLayout(new BorderLayout());

		messageLabel = new JLabel(s);
		add(messageLabel);


		Panel buttonPanel = new Panel(new FlowLayout());

		yes = new Button("yes");
		yes.addActionListener(this);
		no = new Button("no");
		no.addActionListener(this);

		buttonPanel.add(yes);
		buttonPanel.add(no);

		add(buttonPanel, BorderLayout.CENTER);

		setSize(400, 100);
		setLocation(200,200);

	}
	//===============================================================================================
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================
		if(ae.getSource() == yes)
		{
			result = true;
			setVisible(false);

		}
		else
		{
			result = false;
			setVisible(false);
		}
	}
}
