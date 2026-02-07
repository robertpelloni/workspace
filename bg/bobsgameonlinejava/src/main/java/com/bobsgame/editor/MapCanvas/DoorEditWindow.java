package com.bobsgame.editor.MapCanvas;

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
import java.util.Enumeration;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
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
import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Event.Event;
import com.bobsgame.editor.Project.Event.EventEditor;
import com.bobsgame.editor.Project.Map.Door;
import com.bobsgame.editor.Project.Map.Map;


//===============================================================================================
public class DoorEditWindow extends JFrame implements  ActionListener, ItemListener, ImageObserver, KeyListener, ListSelectionListener, CaretListener
{//===============================================================================================

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;

	EditorMain E;

	JList<Door> destinationList;
	DefaultListModel<Door> destinationListModel;

	JTextField doorNameTextField, commentText, spriteNameText, destinationText;

	JCheckBox

			isRandomNPCSpawnPointCheckbox,
			randomPointOfInterestCheckbox,
			randomSpawnKidsCheckbox,
			randomSpawnAdultsCheckbox,
			randomSpawnMalesCheckbox,
			randomSpawnFemalesCheckbox
			;


	JTextField
			randomSpawnChanceTextField,
			randomSpawnDelayTextField
			;


	JTextField filterTextField;

	JList<GameObject> connectionsList;
	DefaultListModel<GameObject> connectionsListModel;


	JButton removeConnectionButton;

	JButton doneButton, cancelButton;

	JPanel listPanel;


	JList<Door> doorList;
	DefaultListModel<Door> doorListModel;

	public int editingDoorIndex=-1;

	String lastFilterString = "";



	public Event event = null;

	EventEditor eventEditor = null;

	JPanel centerPanel;

	JButton addOrEditEventButton;

	//===============================================================================================
	public DoorEditWindow(EditorMain e)
	{//===============================================================================================
		super("Door Edit Window");
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
		E = e;




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





		JPanel optionsPanel = new JPanel(new GridLayout(0,1));
		optionsPanel.setBorder(EditorMain.border);

		optionsPanel.setBackground(Color.LIGHT_GRAY);

		//optionsPanel.setLayout(new BoxLayout(optionsPanel,BoxLayout.Y_AXIS));

		JPanel doorNamePanel = new JPanel();
		JLabel doorNameLabel = new JLabel("Door Name: ");
		doorNameTextField = new JTextField("",50);
		doorNameTextField.addCaretListener(this);
		doorNameTextField.addKeyListener(this);
		doorNameTextField.setForeground(Color.GRAY);
		doorNamePanel.add(doorNameLabel);
		doorNamePanel.add(doorNameTextField);
		optionsPanel.add(doorNamePanel);

		JPanel commentPanel = new JPanel();
		JLabel commentLabel = new JLabel("Comment: ");
		commentText = new JTextField("",50);
		commentPanel.add(commentLabel);
		commentPanel.add(commentText);
		optionsPanel.add(commentPanel);

		JPanel spriteNamePanel = new JPanel();
		JLabel spriteNameLabel = new JLabel("Sprite Name: ");
		spriteNameText = new JTextField("",30);
		spriteNameText.setEnabled(false);
		spriteNamePanel.add(spriteNameLabel);
		spriteNamePanel.add(spriteNameText);
		optionsPanel.add(spriteNamePanel);

		JPanel destinationPanel = new JPanel();
		JLabel destinationLabel = new JLabel("Destination String: ");
		destinationText = new JTextField("",30);
		destinationText.setEnabled(false);
		destinationPanel.add(destinationLabel);
		destinationPanel.add(destinationText);
		optionsPanel.add(destinationPanel);


		randomPointOfInterestCheckbox = new JCheckBox("Exit For Random NPCs? (Point Of Interest)");
		randomPointOfInterestCheckbox.addItemListener(this);
		randomPointOfInterestCheckbox.setSelected(false);
		optionsPanel.add(randomPointOfInterestCheckbox);


		isRandomNPCSpawnPointCheckbox = new JCheckBox("Random NPC Spawn Point?");
		isRandomNPCSpawnPointCheckbox.addItemListener(this);
		isRandomNPCSpawnPointCheckbox.setSelected(false);
		optionsPanel.add(isRandomNPCSpawnPointCheckbox);

		JPanel randomSpawnDelayPanel = new JPanel();
		JLabel randomSpawnDelayLabel = new JLabel("Random Spawn Ticks Between Attempts");
		randomSpawnDelayTextField = new JTextField("1000",4);
		randomSpawnDelayPanel.add(randomSpawnDelayLabel);
		randomSpawnDelayPanel.add(randomSpawnDelayTextField);
		optionsPanel.add(randomSpawnDelayPanel);

		JPanel randomSpawnChancePanel = new JPanel();
		JLabel randomSpawnChanceLabel = new JLabel("Random Spawn Chance 0.0f-1.0f");
		randomSpawnChanceTextField = new JTextField("1.0f",3);
		randomSpawnChancePanel.add(randomSpawnChanceLabel);
		randomSpawnChancePanel.add(randomSpawnChanceTextField);
		optionsPanel.add(randomSpawnChancePanel);


		randomSpawnKidsCheckbox = new JCheckBox("Random Spawn Kids");
		randomSpawnKidsCheckbox.addItemListener(this);
		randomSpawnKidsCheckbox.setSelected(true);
		optionsPanel.add(randomSpawnKidsCheckbox);

		randomSpawnAdultsCheckbox = new JCheckBox("Random Spawn Adults");
		randomSpawnAdultsCheckbox.addItemListener(this);
		randomSpawnAdultsCheckbox.setSelected(true);
		optionsPanel.add(randomSpawnAdultsCheckbox);

		randomSpawnMalesCheckbox = new JCheckBox("Random Spawn Males");
		randomSpawnMalesCheckbox.addItemListener(this);
		randomSpawnMalesCheckbox.setSelected(true);
		optionsPanel.add(randomSpawnMalesCheckbox);

		randomSpawnFemalesCheckbox = new JCheckBox("Random Spawn Females");
		randomSpawnFemalesCheckbox.addItemListener(this);
		randomSpawnFemalesCheckbox.setSelected(true);
		optionsPanel.add(randomSpawnFemalesCheckbox);


		JPanel eventButtonPanel = new JPanel();
		addOrEditEventButton = new JButton("Add New Event");
		addOrEditEventButton.addActionListener(this);
		eventButtonPanel.add(Box.createHorizontalGlue());
		eventButtonPanel.add(addOrEditEventButton);
		eventButtonPanel.add(Box.createHorizontalGlue());


		optionsPanel.add(eventButtonPanel);







		listPanel = new JPanel();
		listPanel.setBorder(EditorMain.border);
		listPanel.setLayout(new BorderLayout());



		JPanel destinationListPanel = new JPanel();
		destinationListPanel.setLayout(new BoxLayout(destinationListPanel,BoxLayout.Y_AXIS));
		destinationListPanel.setBorder(EditorMain.border);

		Font listFont = new Font("Lucida Console", Font.PLAIN, 12);
		destinationListModel = new DefaultListModel<Door>();
		destinationList = new JList<Door>(destinationListModel); //data has type Object
		destinationList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		destinationList.setLayoutOrientation(JList.VERTICAL);
		destinationList.setVisibleRowCount(100);
		destinationList.setForeground(Color.BLACK);
		destinationList.setFont(listFont);
		destinationList.setFixedCellHeight(16);
		destinationList.addListSelectionListener(this);
		destinationList.setCellRenderer(new DoorDestinationNameCellRenderer());
		JScrollPane destinationListScroller = new JScrollPane(destinationList);
		destinationListScroller.setBorder(EditorMain.border);

		JPanel filterPanel = new JPanel();
		JLabel filterLabel = new JLabel("Filter");
		filterTextField = new JTextField(10);
		filterTextField.addCaretListener(this);
		filterPanel.add(filterLabel);
		filterPanel.add(filterTextField);

		destinationListPanel.add(new JLabel("Destination Door"));
		destinationListPanel.add(Box.createRigidArea(new Dimension(400,0)));
		destinationListPanel.add(destinationListScroller);
		destinationListPanel.add(filterPanel);




		JPanel connectionsPanel = new JPanel();
		connectionsPanel.setLayout(new BoxLayout(connectionsPanel,BoxLayout.Y_AXIS));
		connectionsPanel.setBorder(EditorMain.border);


		connectionsListModel = new DefaultListModel<GameObject>();
		connectionsList = new JList<GameObject>(connectionsListModel); //data has type Object
		connectionsList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		connectionsList.setLayoutOrientation(JList.VERTICAL);
		connectionsList.setVisibleRowCount(10);
		connectionsList.setForeground(Color.BLACK);
		connectionsList.setFont(listFont);
		connectionsList.setFixedCellHeight(16);
		connectionsList.addListSelectionListener(this);
		connectionsList.setCellRenderer(new DoorConnectionsListShortTypeNameCellRenderer());
		JScrollPane connectionsListScroller = new JScrollPane(connectionsList);
		connectionsListScroller.setBorder(EditorMain.border);

		JPanel removeConnectionsButtonPanel = new JPanel();
		removeConnectionButton = new JButton("Remove Selected Connection");
		removeConnectionButton.addActionListener(this);
		removeConnectionsButtonPanel.add(removeConnectionButton);


		connectionsPanel.add(new JLabel("Path Connections For Spawned Entities"));
		connectionsPanel.add(Box.createRigidArea(new Dimension(400,0)));
		connectionsPanel.add(connectionsListScroller);
		connectionsPanel.add(removeConnectionsButtonPanel);



		listPanel.add(destinationListPanel, BorderLayout.WEST);
		listPanel.add(connectionsPanel, BorderLayout.EAST);

		listPanel.setSize(new Dimension(800,200));
		listPanel.setPreferredSize(new Dimension(800,200));
		listPanel.setMaximumSize(new Dimension(800,600));
		listPanel.setMinimumSize(new Dimension(800,200));





		doorListModel = new DefaultListModel<Door>();
		doorList = new JList<Door>(doorListModel); //data has type Object
		doorList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		doorList.setLayoutOrientation(JList.VERTICAL);
		doorList.setVisibleRowCount(10);
		doorList.setForeground(Color.BLACK);
		doorList.setFont(listFont);
		doorList.setFixedCellHeight(16);
		doorList.addListSelectionListener(this);
		doorList.setCellRenderer(new DoorListNameCellRenderer());
		doorList.setFocusable(false);
		JScrollPane doorListScroller = new JScrollPane(doorList);
		doorListScroller.setBorder(EditorMain.border);
		doorListScroller.setFocusable(false);

		JPanel doorListPanel = new JPanel();
		doorListPanel.setLayout(new BoxLayout(doorListPanel,BoxLayout.Y_AXIS));
		doorListPanel.add(Box.createRigidArea(new Dimension(100,0)));
		doorListPanel.add(doorListScroller);







		everythingPanel.add(optionsPanel, BorderLayout.WEST);
		everythingPanel.add(listPanel, BorderLayout.CENTER);





		centerPanel = new JPanel(new BorderLayout());
		centerPanel.setBorder(EditorMain.border);
		centerPanel.add(everythingPanel,BorderLayout.NORTH);
		centerPanel.add(eventEditor,BorderLayout.CENTER);




		add(doorListPanel,BorderLayout.WEST);
		add(centerPanel,BorderLayout.CENTER);



		setSize(EditorMain.getScreenWidth() - 460, 770);
		setLocation(20, 800);



		setFocusable(true);
		addKeyListener(this);
		recursivelyAddKeyListener(centerPanel);



	}
	//===============================================================================================
	public void recursivelyAddKeyListener(Container container)
	{//===============================================================================================
		Component[] c = container.getComponents();
		for(int i=0;i<c.length;i++)
		{




			c[i].removeKeyListener(this);


			if(
					c[i].getClass()!=JScrollPane.class
					&&c[i].getClass()!=JList.class
			)
			{

				c[i].setFocusable(true);

				c[i].addKeyListener(this);

				if(c[i].getClass().equals(JPanel.class))
				{
					recursivelyAddKeyListener((Container) c[i]);
				}
			}
			else
			{
				c[i].setFocusable(false);
			}

		}

	}


	//===============================================================================================
	public void showDoorWindow()
	{//===============================================================================================

		if(Project.getSelectedMap().getSelectedDoorIndex()==-1)return;

		editingDoorIndex = Project.getSelectedMap().getSelectedDoorIndex();


		populateDestinationList();

		setFieldsFromDoorVars();


		refreshDoorList();


		setVisible(true);

		try
		{
			setAlwaysOnTop(true);
		}
		catch(SecurityException se){}

		doorNameTextField.setForeground(Color.GRAY);
	}



	//===============================================================================================
	public void refreshDoorList()
	{//===============================================================================================

		doorListModel.removeAllElements();

		for(int n=0;n<getMap().getNumDoors();n++)
		{
			doorListModel.addElement(getMap().getDoor(n));
		}

		doorList.setSelectedIndex(editingDoorIndex);

	}


	//===============================================================================================
	public void populateDestinationList()
	{//===============================================================================================


		Door d = Project.getSelectedMap().getDoor(editingDoorIndex);


		//fill door list
		destinationListModel.removeAllElements();


		destinationListModel.addElement(d);


		for(int i = 0; i < Project.doorIndexList.size(); i++)
		{

			if(Project.doorIndexList.get(i)!=d)destinationListModel.addElement(Project.doorIndexList.get(i));

		}

		//if(doorListModel.getSize()==0)doorListModel.addElement("none");

		filterDestinationList();

		destinationList.setSelectedIndex(0);




		//redo list layout
		//remove(listPanel);
		//add(listPanel, BorderLayout.CENTER);



	}


	//===============================================================================================
	@Override
	public void itemStateChanged(ItemEvent ie)
	{//===============================================================================================

		if(ie.getSource() == isRandomNPCSpawnPointCheckbox)
		{
			if(isRandomNPCSpawnPointCheckbox.isSelected()==true)
			{
				enableRandomFields();
				//randomPointOfInterestCheckbox.setSelected(true);//should be exit by default //disabled because is too confusing.
			}
			else disableRandomFields();
		}


		if(ie.getSource().getClass().equals(JCheckBox.class))
		{
			if(((JCheckBox)ie.getSource()).isSelected()==true)((JCheckBox)ie.getSource()).setBackground(new Color(150,225,150));
			else ((JCheckBox)ie.getSource()).setBackground(Color.LIGHT_GRAY);
		}


	}



	//===============================================================================================
	public void disableRandomFields()
	{//===============================================================================================
		randomSpawnDelayTextField.setEnabled(false);
		randomSpawnChanceTextField.setEnabled(false);
		randomSpawnKidsCheckbox.setEnabled(false);
		randomSpawnAdultsCheckbox.setEnabled(false);
		randomSpawnMalesCheckbox.setEnabled(false);
		randomSpawnFemalesCheckbox.setEnabled(false);


	}


	//===============================================================================================
	public void enableRandomFields()
	{//===============================================================================================

		randomSpawnDelayTextField.setEnabled(true);
		randomSpawnChanceTextField.setEnabled(true);
		randomSpawnKidsCheckbox.setEnabled(true);
		randomSpawnAdultsCheckbox.setEnabled(true);
		randomSpawnMalesCheckbox.setEnabled(true);
		randomSpawnFemalesCheckbox.setEnabled(true);


	}



	//===============================================================================================
	private void setFieldsFromDoorVars()
	{//===============================================================================================

		Door d = Project.getSelectedMap().getDoor(editingDoorIndex);
		//Sprite sprite = d.sprite;

		doorNameTextField.setText(d.name());
		commentText.setText(d.comment());
		spriteNameText.setText(d.getSprite().name());
		destinationText.setText(d.destinationDoor().getLongTypeName());


		isRandomNPCSpawnPointCheckbox.setSelected(d.randomNPCSpawnPoint());
		if(d.randomNPCSpawnPoint()==true)enableRandomFields();
		else disableRandomFields();


		randomPointOfInterestCheckbox.setSelected(d.randomPointOfInterestOrExit());
		randomSpawnKidsCheckbox.setSelected(d.randomSpawnKids());
		randomSpawnAdultsCheckbox.setSelected(d.randomSpawnAdults());
		randomSpawnMalesCheckbox.setSelected(d.randomSpawnMales());
		randomSpawnFemalesCheckbox.setSelected(d.randomSpawnFemales());
		randomSpawnChanceTextField.setText(""+d.randomSpawnChance());
		randomSpawnDelayTextField.setText(""+d.randomSpawnDelay());

		connectionsListModel.removeAllElements();
		for(int i=0;i<d.connectionTYPEIDList().size();i++)
		{
			connectionsListModel.addElement(Project.getMapObjectByTYPEIDName(d.connectionTYPEIDList().get(i)));
		}



		Enumeration<Door> e = destinationListModel.elements();

		for(int i=0; e.hasMoreElements(); i++)
		{
			Door temp = (Door) e.nextElement();
			if(temp.getTYPEIDString().equals(d.destinationTYPEIDString()))
			{
				destinationList.setSelectedIndex(i);
				destinationList.ensureIndexIsVisible(i);
			}
		}

		//select doorList from door
//		Object itemList[] = destinationListModel.toArray();
//		for(int n=0;n<itemList.length;n++)
//		{
//			if(itemList[n].toString().equals(d.destination.getMap().name+"."+d.destination.getName()))
//			{
//				destinationList.setSelectedIndex(n);
//				destinationList.ensureIndexIsVisible(n);
//			}
//		}




		if(d.eventData()!=null)
		{
			event = Project.getEventByID(d.eventData().id());

			if(event!=null)
			{
				if(event.name().length()==0)event.setName(Project.getSelectedMap().name()+"."+d.name());
				eventEditor.editEvent(Project.getSelectedMap(),event);
				openEventEditor();
			}
		}
		else
		{
			closeEventEditor();
			event=null;
		}




	}

	//===============================================================================================
	private void setDoorVarsFromFields()
	{//===============================================================================================


		Map m = Project.getSelectedMap();
		Door d = m.getDoor(editingDoorIndex);
		//Sprite sprite = d.sprite;

		String newName = doorNameTextField.getText();
		newName = m.createUniqueDoorName(newName, editingDoorIndex);

		//if this door already has a name, we opened an existing door and changed the name
		if(d.name()!=null)
		{
			if(d.name().equals(newName)==false)
			{
				d.setName(newName);
			}
		}
		else
		{
			//this wasn't an existing door, it has no name, so there is nothing to rename
			d.setName(newName);
		}


		d.setComment(commentText.getText());



		if(destinationList.getSelectedValue()!=null)
		{
			//if(destinationList.getSelectedValue().toString().equals("self")==false)
			if(destinationList.getSelectedValue()!=d)
			{
				//String destString = destinationList.getSelectedValue().toString();

				//Map tempMap = Project.getMapByName(destString.substring(0,destString.indexOf(".")));
				//Door tempDoor = tempMap.getDoorByName(destString.substring(destString.indexOf(".")+1));


				d.setDestinationTYPEIDString(destinationList.getSelectedValue().getTYPEIDString());
				//d.destination=tempDoor;
			}
			else
			{
				d.setDestinationTYPEIDString(d.getTYPEIDString());
			}
		}



		d.setRandomNPCSpawnPoint(isRandomNPCSpawnPointCheckbox.isSelected());
		d.setRandomSpawnChance(Float.parseFloat(randomSpawnChanceTextField.getText()));
		d.setRandomSpawnDelay(Integer.parseInt(randomSpawnDelayTextField.getText()));
		d.setRandomPointOfInterestOrExit(randomPointOfInterestCheckbox.isSelected());
		d.setRandomSpawnKids(randomSpawnKidsCheckbox.isSelected());
		d.setRandomSpawnAdults(randomSpawnAdultsCheckbox.isSelected());
		d.setRandomSpawnMales(randomSpawnMalesCheckbox.isSelected());
		d.setRandomSpawnFemales(randomSpawnFemalesCheckbox.isSelected());

		d.connectionTYPEIDList().clear();
		for(int i=0;i<connectionsListModel.getSize();i++)
		{
			d.connectionTYPEIDList().add(connectionsListModel.get(i).getTYPEIDString());
		}




		if(event!=null)
		{
			if(d.eventData()!=event.getData())d.setEventData(event.getData());

			eventEditor.storeEventTreeInString();

			closeEventEditor();
			event = null;
		}


	}



	//===============================================================================================
	public void openEventEditor()
	{//===============================================================================================
		addOrEditEventButton.setVisible(false);
		centerPanel.add(eventEditor);




		setSize(EditorMain.getScreenWidth()-20, 970);
		setLocation(20, 600);

		validate();
	}
	//===============================================================================================
	public void closeEventEditor()
	{//===============================================================================================
		addOrEditEventButton.setVisible(true);
		centerPanel.remove(eventEditor);





		validate();

	}



	//===============================================================================================
	@Override
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================
		if(ae.getSource() == doneButton)
		{

			setDoorVarsFromFields();

			editingDoorIndex = -1;

			setVisible(false);

			//slow draw because we need to redraw the door layer
			EditorMain.mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();


		}
		else if(ae.getSource() == cancelButton)
		{
			setVisible(false);
		}

		if(ae.getSource() == removeConnectionButton)
		{
			if(connectionsList.getSelectedIndex()>=0)
			{
				connectionsListModel.remove(connectionsList.getSelectedIndex());
			}
		}


		if(ae.getSource() == addOrEditEventButton)
		{

			Door d = Project.getSelectedMap().getDoor(editingDoorIndex);

			if(event==null)
			{
				d.createDefaultEvent();

				event = Project.getEventByID(d.eventData().id());
				eventEditor.editEvent(Project.getSelectedMap(),event);

				openEventEditor();

			}


		}


	}


	//===============================================================================================
	public void keyTyped(KeyEvent e)
	{//===============================================================================================


	}




	//===============================================================================================
	public void keyPressed(KeyEvent e)
	{//===============================================================================================


		if(e.getSource() == doorNameTextField && e.getKeyCode() == KeyEvent.VK_ENTER)
		{


			doorNameTextField.setForeground(Color.GRAY);

			Door d = getMap().getDoor(editingDoorIndex);
			//get var name
			String oldName = d.name();

			//find var name in name list
			int selectedItem = -1;


			Enumeration<Door> enm = doorListModel.elements();

			for(int i=0; enm.hasMoreElements(); i++)
			{
				Door temp = (Door) enm.nextElement();
				if(temp.name().equals(oldName))
				{
					selectedItem = i;
					break;
				}
			}

//			Object[] listNames = doorListModel.toArray();
//
//			for(int i=0;i<listNames.length; i++)
//			{
//				if(listNames[i].toString().equals(oldName))
//				{
//					selectedItem = i;
//					break;
//				}
//			}


			if(selectedItem!=-1)
			{
				String name = doorNameTextField.getText();
				name = getMap().createUniqueDoorName(name, editingDoorIndex);


				d.setName(name);
				//if(doorNameText.getText().equals(name)==false)doorNameText.setText(name);


				//update name to textFieldName
				doorListModel.add(selectedItem,d);
				doorListModel.remove(selectedItem+1);
				doorList.setSelectedIndex(selectedItem);

				validate();
			}

			return;
		}



		if(e.getKeyCode() == KeyEvent.VK_ENTER)
		{
			actionPerformed(new ActionEvent(doneButton,ActionEvent.ACTION_PERFORMED,""));
		}

		if(e.getKeyCode() == KeyEvent.VK_PAGE_UP)
		{
			if(doorList.getSelectedIndex()>0)doorList.setSelectedIndex(doorList.getSelectedIndex()-1);
			valueChanged(new ListSelectionEvent(doorList,0,doorListModel.size()-1, false));
			//itemStateChanged(new ItemEvent(doorList,ItemEvent.ITEM_STATE_CHANGED,doorList.getSelectedValue().toString(), ItemEvent.SELECTED));
		}


		if(e.getKeyCode() == KeyEvent.VK_PAGE_DOWN)
		{
			if(doorList.getSelectedIndex()>=0&&doorList.getSelectedIndex()<doorListModel.size()-1)doorList.setSelectedIndex(doorList.getSelectedIndex()+1);
			valueChanged(new ListSelectionEvent(doorList,0,doorListModel.size()-1, false));
			//itemStateChanged(new ItemEvent(doorList,ItemEvent.ITEM_STATE_CHANGED,doorList.getSelectedValue().toString(), ItemEvent.SELECTED));
		}

	}


	//===============================================================================================
	public void keyReleased(KeyEvent e)
	{//===============================================================================================


	}


	//===============================================================================================
	public Map getMap()
	{//===============================================================================================
		return Project.getSelectedMap();

	}


	//===============================================================================================
	@Override
	public void valueChanged(ListSelectionEvent e)
	{//===============================================================================================
		if(e.getSource() == doorList)
		{

			if(e.getValueIsAdjusting()==true)return;

			if(doorList.getSelectedIndex()==editingDoorIndex)return;

			if(doorList.getSelectedIndex()!=-1)
			{
				//save current action to vars
				setDoorVarsFromFields();

				editingDoorIndex = doorList.getSelectedIndex();

				doorList.ensureIndexIsVisible(doorList.getSelectedIndex());


				populateDestinationList();

				//update fields from selected door
				setFieldsFromDoorVars();

				//select action on map and repaint
				getMap().setSelectedDoorIndex(editingDoorIndex);
				EditorMain.mapCanvas.scrollToTop(getMap().getSelectedDoor());

				doorNameTextField.setForeground(Color.GRAY);
			}
		}

	}

	//===============================================================================================
	public void filterDestinationList()
	{//===============================================================================================



		if(filterTextField.getText().length()>0)
		{

			for(int i=0;i < destinationListModel.getSize();i++)
			{
				if(destinationListModel.getElementAt(i).toString().toLowerCase().contains((CharSequence)filterTextField.getText().toLowerCase())==false){destinationListModel.remove(i);i--;}
			}
		}
	}

	//===============================================================================================
	@Override
	public void caretUpdate(CaretEvent e)
	{//===============================================================================================
		if(e.getSource()==filterTextField)
		{
			if(e.getSource()==filterTextField)
			{

				if(filterTextField.getText().length()>lastFilterString.length())
				{
					lastFilterString=filterTextField.getText();
					filterDestinationList();

				}
				else
				{
					lastFilterString=filterTextField.getText();
					populateDestinationList();

				}


			}
		}



		if(e.getSource()==doorNameTextField)
		{
			doorNameTextField.setForeground(Color.RED);
		}





	}



//	//===============================================================================================
//	class MyListCellRenderer extends DefaultListCellRenderer
//	{//===============================================================================================
//
//
//
//
//		/**
//		 *
//		 */
//		private static final long serialVersionUID = 1L;
//
//
//
//		public MyListCellRenderer()
//		{
//
//		}
//
//
//
//		public Component getListCellRendererComponent(
//				JList<?> list,
//				Object value,
//				int index,
//				boolean isSelected,
//				boolean cellHasFocus)
//			{
//				super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);
//
//
//				if(index<getMap().getNumDoors())if(getMap().getDoor(index).eventID()!=-1)setForeground(Color.RED);
//
//
//
//				return this;
//			}
//
//
//
//
//	}

	//===============================================================================================
	class DoorDestinationNameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public DoorDestinationNameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
				super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);

				if(value!=null)
				{
					setToolTipText("");

					Door d = ((Door)value);
					Door editingDoor = Project.getSelectedMap().getDoor(editingDoorIndex);


					if(d.map()==editingDoor.map()){setForeground(Color.LIGHT_GRAY);setToolTipText("Door is on this Map.");}
					if(d==editingDoor){setForeground(Color.BLUE);setToolTipText("Door is the one you are editing.");}
					if(d.eventData()!=null && Project.getEventByID(d.eventData().id()).text().contains("enterThisDoor")==false){setForeground(Color.ORANGE);setToolTipText("Event does not contain enterThisDoor");}
					if(d.eventData()==null){setForeground(Color.RED);setToolTipText("Has no Event. eventID == -1");}

					setText(d.map().name()+"."+d.name());
				}
				else setText("null");

				return this;
		}
	}

	//===============================================================================================
	class DoorListNameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public DoorListNameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
				super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);

				if(value!=null)
				{
					setToolTipText("");

					Door d = ((Door)value);
					Door editingDoor = Project.getSelectedMap().getDoor(editingDoorIndex);


					if(d.destinationTYPEIDString() == d.getTYPEIDString()){setForeground(Color.LIGHT_GRAY);setToolTipText("Destination is self");}
					if(d.eventData()!=null && Project.getEventByID(d.eventData().id()).text().contains("enterThisDoor")==false){setForeground(Color.ORANGE);setToolTipText("Event does not contain enterThisDoor");}
					if(d.eventData()==null){setForeground(Color.RED);setToolTipText("Has no Event. eventID == -1");}

					setText(d.name());
				}
				else setText("null");
				return this;
		}
	}
	//===============================================================================================
	class DoorConnectionsListShortTypeNameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public DoorConnectionsListShortTypeNameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
				super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);

				if(value!=null)
				{
					setToolTipText("");

					Door d = ((Door)value);
					Door editingDoor = Project.getSelectedMap().getDoor(editingDoorIndex);


					if(d.destinationTYPEIDString() == d.getTYPEIDString()){setForeground(Color.LIGHT_GRAY);setToolTipText("Destination is self");}
					if(d.eventData()==null){setForeground(Color.RED);setToolTipText("Has no Event. eventID == -1");}

					setText(d.getShortTypeName());
				}
				else setText("null");
				return this;
		}
	}

}
