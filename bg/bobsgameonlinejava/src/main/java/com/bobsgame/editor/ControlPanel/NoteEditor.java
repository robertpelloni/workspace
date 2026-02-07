package com.bobsgame.editor.ControlPanel;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dialog;
import java.awt.Font;
import java.awt.Frame;
import java.awt.TextArea;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.TextEvent;
import java.awt.event.TextListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.image.ImageObserver;

import javax.swing.JDialog;
import javax.swing.WindowConstants;

import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Map.Map;


//===============================================================================================
public class NoteEditor extends JDialog implements WindowListener, ActionListener, TextListener, ItemListener, ImageObserver, KeyListener
{//===============================================================================================


	public TextArea textArea;

	public Map currentMap = null;


	//===============================================================================================
	public NoteEditor(Frame f)
	{//===============================================================================================
		super(f, "Note Editor", true);


		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);

		setLayout(new BorderLayout());



		textArea = new TextArea();
		//textArea.setBackground(new Color(24,24,24));
		//textArea.setForeground(Color.LIGHT_GRAY);
		textArea.setFont(new Font("Tahoma", Font.PLAIN, 11));


		add(textArea,BorderLayout.CENTER);


		setSize(1500, 800);
		setBackground(Color.DARK_GRAY);
		addWindowListener(this);

		setLocation(400,300);

	}


	//===============================================================================================
	public void openNoteEditor()
	{//===============================================================================================

		currentMap = Project.getSelectedMap();
		textArea.setText(currentMap.mapNote().replace("\\n","\n"));

		textArea.setCaretPosition(textArea.getText().length());


		setVisible(true);

		try
		{
			setAlwaysOnTop(true);
		}
		catch(SecurityException se){}


	}



	//===============================================================================================
	@Override
	public void keyTyped(KeyEvent e)
	{//===============================================================================================


	}


	//===============================================================================================
	@Override
	public void keyPressed(KeyEvent e)
	{//===============================================================================================


	}


	//===============================================================================================
	@Override
	public void keyReleased(KeyEvent e)
	{//===============================================================================================


	}


	//===============================================================================================
	@Override
	public void itemStateChanged(ItemEvent e)
	{//===============================================================================================


	}


	//===============================================================================================
	@Override
	public void textValueChanged(TextEvent e)
	{//===============================================================================================


	}


	//===============================================================================================
	@Override
	public void actionPerformed(ActionEvent e)
	{//===============================================================================================


	}


	//===============================================================================================
	@Override
	public void windowOpened(WindowEvent e)
	{//===============================================================================================


	}


	//===============================================================================================
	@Override
	public void windowClosing(WindowEvent e)
	{//===============================================================================================


		currentMap.setMapNote(textArea.getText().replace("\r","").replace("\n", "\\n"));

		if(currentMap.mapNote().length()>0)ControlPanel.openNoteEditorButton.setBackground(Color.GREEN);
		else ControlPanel.openNoteEditorButton.setBackground(Color.GRAY);

		setVisible(false);


	}


	//===============================================================================================
	@Override
	public void windowClosed(WindowEvent e)
	{//===============================================================================================


	}


	//===============================================================================================
	@Override
	public void windowIconified(WindowEvent e)
	{//===============================================================================================


	}


	//===============================================================================================
	@Override
	public void windowDeiconified(WindowEvent e)
	{//===============================================================================================


	}


	//===============================================================================================
	@Override
	public void windowActivated(WindowEvent e)
	{//===============================================================================================


	}


	//===============================================================================================
	@Override
	public void windowDeactivated(WindowEvent e)
	{//===============================================================================================


	}

}
