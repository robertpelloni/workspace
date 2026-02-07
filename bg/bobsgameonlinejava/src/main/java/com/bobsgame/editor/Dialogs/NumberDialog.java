package com.bobsgame.editor.Dialogs;

import java.awt.*;
import java.awt.event.*;

import com.bobsgame.EditorMain;
//===============================================================================================
public class NumberDialog extends WindowAdapter implements ActionListener
{//===============================================================================================

	protected Dialog d;
	protected Panel p;
	public TextField text;
	protected Button b;

	//===============================================================================================
	public NumberDialog()
	{//===============================================================================================

		d = new Dialog(EditorMain.frame, "Number", true);
		d.setSize(240, 65);
		p = new Panel();
		p.setBackground(Color.GRAY);
		d.add(p);
		d.addWindowListener(this);
		text = new TextField("");

		b = new Button("OK");
		b.addActionListener(this);

		p.add(text);
		p.add(b);
	}
	//===============================================================================================
	public NumberDialog(String s)
	{//===============================================================================================

		d = new Dialog(EditorMain.frame, s, true);
		d.setSize(240, 65);
		p = new Panel();
		p.setBackground(Color.GRAY);
		d.add(p);
		d.addWindowListener(this);
		text = new TextField("");

		b = new Button("OK");
		b.addActionListener(this);

		p.add(text);
		p.add(b);
	}
	//===============================================================================================
	public NumberDialog(Frame f, String s)
	{//===============================================================================================
		d = new Dialog(f, s, true);
		d.setSize(240, 65);
		p = new Panel();
		p.setBackground(Color.GRAY);
		d.add(p);
		d.addWindowListener(this);
		text = new TextField("");

		b = new Button("OK");
		b.addActionListener(this);

		p.add(text);
		p.add(b);
	}
	//===============================================================================================
	public void show()
	{//===============================================================================================
		//d.setModal(false);
		d.setVisible(true);
	}
	//===============================================================================================
	public boolean isShowing()
	{//===============================================================================================
		return d.isShowing();
	}
	//===============================================================================================
	public void windowClosing(WindowEvent we)
	{//===============================================================================================
		d.setVisible(false);
	}
	//===============================================================================================
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================
		if(ae.getSource() == b)
		{
			{
				d.setVisible(false);
			}
		}
	}
}
