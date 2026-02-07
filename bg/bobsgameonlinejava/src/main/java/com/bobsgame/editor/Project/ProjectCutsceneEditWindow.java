package com.bobsgame.editor.Project;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
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
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.WindowConstants;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.Project.Event.Event;
import com.bobsgame.editor.Project.Event.EventEditor;
import com.bobsgame.shared.EventData;

public class ProjectCutsceneEditWindow extends JFrame implements ActionListener, ItemListener, ImageObserver, KeyListener, ListSelectionListener, CaretListener
{


	/**
	 *
	 */
	private static final long serialVersionUID = 1L;



	JButton doneButton, cancelButton;



	EventEditor eventEditor = null;

	JPanel centerPanel;

	JButton addNewEventButton;

	JTextField eventNameTextField;


	JLabel nameLabel, idLabel;

	JList<Event> eventsList;
	DefaultListModel<Event> eventsListModel;
	JScrollPane eventsListScroller;

	public boolean eventEditorIsOpen = false;

	public int editingEventIndex = -1;



	//===============================================================================================
	public ProjectCutsceneEditWindow()
	{//===============================================================================================

		super("Project Cutscene Edit Window");
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



		JPanel optionsPanel = new JPanel();
		optionsPanel.setLayout(new BoxLayout(optionsPanel,BoxLayout.Y_AXIS));

		JPanel namePanel = new JPanel();
			nameLabel = new JLabel("");
			namePanel.add(new JLabel("Name:"));
			namePanel.add(nameLabel);
		optionsPanel.add(namePanel);

			JPanel idPanel = new JPanel();
			idLabel = new JLabel("");
			idPanel.add(new JLabel("ID:"));
			idPanel.add(idLabel);
		optionsPanel.add(idPanel);




		JPanel eventPanel = new JPanel(new BorderLayout());
		eventPanel.setBorder(EditorMain.border);

		Font listFont = new Font("Lucida Console", Font.PLAIN, 12);

		JPanel eventListPanel = new JPanel();
		eventListPanel.setBorder(EditorMain.border);
		eventListPanel.setLayout(new BoxLayout(eventListPanel,BoxLayout.Y_AXIS));

			eventsListModel = new DefaultListModel<Event>();
				eventsList = new JList<Event>(eventsListModel);
				eventsList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
				eventsList.setLayoutOrientation(JList.VERTICAL);
				eventsList.setVisibleRowCount(10);
				eventsList.setForeground(Color.BLACK);
				eventsList.setFont(listFont);
				eventsList.setFixedCellHeight(16);
				eventsList.addListSelectionListener(this);
				eventsList.setCellRenderer(new NameCellRenderer());
			eventsListScroller = new JScrollPane(eventsList);


		eventListPanel.add(new JLabel("Events Attached To Project"));
		eventListPanel.add(Box.createRigidArea(new Dimension(380,0)));
		eventListPanel.add(eventsListScroller);


			JPanel eventButtonPanel = new JPanel();
			addNewEventButton = new JButton("Add New Event");
			addNewEventButton.addActionListener(this);
			eventButtonPanel.add(Box.createHorizontalGlue());
			eventButtonPanel.add(addNewEventButton);
			eventButtonPanel.add(Box.createHorizontalGlue());


			JPanel eventOptionsPanel = new JPanel(new GridLayout(0,1));
			eventOptionsPanel.setBorder(EditorMain.border);



			JPanel eventNamePanel= new JPanel();
				eventNameTextField = new JTextField(30);
				eventNameTextField.addCaretListener(this);
				eventNameTextField.addKeyListener(this);
				eventNameTextField.setForeground(Color.GRAY);
				eventNamePanel.add(new JLabel("Set Selected Event Name:"));
				eventNamePanel.add(eventNameTextField);
			eventOptionsPanel.add(eventNamePanel);







		eventPanel.add(eventOptionsPanel, BorderLayout.EAST);
		eventPanel.add(eventListPanel, BorderLayout.CENTER);
		eventPanel.add(eventButtonPanel, BorderLayout.SOUTH);




		everythingPanel.add(eventPanel,BorderLayout.WEST);
		everythingPanel.add(optionsPanel,BorderLayout.CENTER);


		centerPanel = new JPanel(new BorderLayout());
		centerPanel.setBorder(EditorMain.border);
		centerPanel.add(everythingPanel,BorderLayout.NORTH);
		centerPanel.add(eventEditor,BorderLayout.CENTER);


		eventEditorIsOpen = true;


		add(centerPanel,BorderLayout.CENTER);






		setSize(EditorMain.getScreenWidth()-20, 770);
		setLocation(20, 800);


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
	public void showProjectCutsceneEditorWindow()
	{//===============================================================================================





		eventsListModel.removeAllElements();
		if(Project.cutsceneEventList.size()>0)
		{
			for(int i=0;i<Project.cutsceneEventList.size();i++)
			{
				eventsListModel.addElement(Project.cutsceneEventList.get(i));
			}
			eventsList.setSelectedIndex(0);//this should open the event editor

		}
		else
		{
			Event e = new Event(EventData.TYPE_PROJECT_INITIAL_LOADER,"PROJECT"+"."+"Load","","");
			Project.cutsceneEventList.add(e);

			eventsListModel.addElement(e);

			eventsList.setSelectedValue(e, true); //will send a listchanged event and save/close/open the event editor.

		}



		eventNameTextField.setForeground(Color.GRAY);

		setVisible(true);

		try
		{
			setAlwaysOnTop(true);
		}
		catch(SecurityException se){}
	}







	//===============================================================================================
	public void openEventEditor()
	{//===============================================================================================

		centerPanel.add(eventEditor);

		eventEditorIsOpen=true;



		setSize(EditorMain.getScreenWidth()-20, 970);
		setLocation(20, 600);



		validate();
	}
	//===============================================================================================
	public void closeEventEditor()
	{//===============================================================================================

		centerPanel.remove(eventEditor);

		eventEditorIsOpen=false;





		validate();

	}



	//===============================================================================================
	@Override
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================
		if(ae.getSource() == doneButton)
		{

			if(eventEditorIsOpen==true)
			{

				eventEditor.storeEventTreeInString();
				closeEventEditor();
			}

			editingEventIndex = -1;



			setVisible(false);


		}
		else if(ae.getSource() == cancelButton)
		{
				eventEditor.currentEvent = null;
				closeEventEditor();

				editingEventIndex = -1;

			setVisible(false);
		}




		if(ae.getSource() == addNewEventButton)
		{


			Event e = new Event(EventData.TYPE_PROJECT_CUTSCENE_DONT_RUN_UNTIL_CALLED,"CUTSCENE"+"."+Project.cutsceneEventList.size(),"","");
			Project.cutsceneEventList.add(e);

			eventsListModel.addElement(e);

			eventsList.setSelectedValue(e, true); //will send a listchanged event and save/close/open the event editor.


		}


	}

	//===============================================================================================
	@Override
	public void caretUpdate(CaretEvent e)
	{//===============================================================================================

		if(e.getSource()==eventNameTextField)
		{
			eventNameTextField.setForeground(Color.RED);
		}

	}
	//===============================================================================================
	@Override
	public void valueChanged(ListSelectionEvent e)
	{//===============================================================================================



		if(e.getSource() == eventsList)
		{

			//System.out.println("valueChanged() editingAreaIndex:"+editingAreaIndex+" areaList.getSelectedIndex():"+areaList.getSelectedIndex());

			if(e.getValueIsAdjusting()==true)return;

			if(eventsList.getSelectedIndex()==editingEventIndex)return;

			if(eventsList.getSelectedIndex()==-1)return;


				if(eventEditorIsOpen==true)
				{
					if(eventEditor.currentEvent!=null)
					{
						eventEditor.storeEventTreeInString();
					}

					closeEventEditor();
				}






				editingEventIndex = eventsList.getSelectedIndex();

				Event selectedEvent = eventsList.getSelectedValue();

				if(selectedEvent.name().length()==0)selectedEvent.setName("CUTSCENE"+"."+Project.cutsceneEventList.size());
				eventNameTextField.setText(selectedEvent.name());
				eventNameTextField.setForeground(Color.GRAY);


				eventEditor.editEvent(null,selectedEvent);
				openEventEditor();

		}



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

		if(e.getSource()==eventNameTextField && e.getKeyCode() == KeyEvent.VK_ENTER)
		{
			if(eventsList.getSelectedValue()!=null)
			{



				Event selectedEvent = eventsList.getSelectedValue();

				if(selectedEvent.type()==EventData.TYPE_PROJECT_INITIAL_LOADER)
				{
					eventNameTextField.setText(selectedEvent.name());
				}
				else
				{
					if(selectedEvent.name().equals(eventNameTextField.getText())==false)
					{

						selectedEvent.setName(eventNameTextField.getText());


						int selectedIndex = eventsList.getSelectedIndex();
						eventsListModel.remove(selectedIndex);
						eventsListModel.add(selectedIndex,selectedEvent);
						eventsList.setSelectedValue(selectedEvent, true);
					}
				}

				eventNameTextField.setForeground(Color.GRAY);

			}
		}


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
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
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
