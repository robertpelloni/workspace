package com.bobsgame.editor.SpriteEditor;




import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.image.ImageObserver;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.DefaultListCellRenderer;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.WindowConstants;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Event.Event;
import com.bobsgame.editor.Project.Event.EventEditor;


//===============================================================================================
public class SpriteEventEditor extends JFrame implements ActionListener, ItemListener, ImageObserver, KeyListener, ListSelectionListener, CaretListener
{//===============================================================================================


	JButton doneButton, cancelButton;

	EventEditor eventEditor = null;

	JPanel centerPanel;




	//===============================================================================================
	public SpriteEventEditor()
	{//===============================================================================================

		super("Sprite Event Edit Window");
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);

		eventEditor = new EventEditor(this);


		setLayout(new BorderLayout());


		JPanel everythingPanel = new JPanel(new BorderLayout());
		everythingPanel.setBorder(EditorMain.border);


			JPanel buttonPanel = new JPanel();
			buttonPanel.setBorder(EditorMain.border);
			buttonPanel.setLayout(new BoxLayout(buttonPanel,BoxLayout.X_AXIS));
				doneButton = new JButton("Done");
				doneButton.addActionListener(this);
				doneButton.setBackground(Color.GREEN);

				cancelButton = new JButton("Cancel");
				cancelButton.addActionListener(this);
				cancelButton.setBackground(Color.RED);


			buttonPanel.add(Box.createHorizontalGlue());
			buttonPanel.add(doneButton);
			buttonPanel.add(cancelButton);


		everythingPanel.add(buttonPanel,BorderLayout.NORTH);




		centerPanel = new JPanel(new BorderLayout());
		centerPanel.setBorder(EditorMain.border);
		centerPanel.add(everythingPanel,BorderLayout.NORTH);
		centerPanel.add(eventEditor,BorderLayout.CENTER);




		add(centerPanel,BorderLayout.CENTER);





		setSize(EditorMain.getScreenWidth()-20, 1000);
		setLocation(20, 600);

		recursivelyAddKeyListener(this);



	}
	//===============================================================================================
	public void recursivelyAddKeyListener(Container container)
	{//===============================================================================================
		Component[] c = container.getComponents();
		for(int i=0;i<c.length;i++)
		{
			c[i].addKeyListener(this);
			if(c[i].getClass().equals(JPanel.class))
			{
				recursivelyAddKeyListener((Container) c[i]);
			}

		}

	}


	//===============================================================================================
	public void showSpriteEventEditorWindow()
	{//===============================================================================================

		if(Project.getSelectedMapIndex()==-1)return;
		if(Project.getSelectedSpriteIndex()==-1)return;
		if(Project.getSelectedSprite().eventData()==null)return;



		Event e = Project.getEventByID(Project.getSelectedSprite().eventData().id());

		if(e==null)return;

		eventEditor.editEvent(null,e);


		setVisible(true);

		try
		{
			setAlwaysOnTop(true);
		}
		catch(SecurityException se){}
	}








	//===============================================================================================
	@Override
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================
		if(ae.getSource() == doneButton)
		{



			eventEditor.storeEventTreeInString();



			setVisible(false);


		}
		else if(ae.getSource() == cancelButton)
		{

			eventEditor.currentEvent = null;

			setVisible(false);
		}





	}



	//===============================================================================================
	@Override
	public void caretUpdate(CaretEvent e)
	{//===============================================================================================




	}


	//===============================================================================================
	@Override
	public void valueChanged(ListSelectionEvent e)
	{//===============================================================================================






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
	class NameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		public NameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
			super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);

			if(value!=null)if(((Event)value).type()==1)setForeground(Color.LIGHT_GRAY);
			if(value!=null)if(((Event)value).type()==2)setForeground(Color.RED);

			setText((value == null) ? "" : ((GameObject)value).name());
			return this;
		}
	}





}
